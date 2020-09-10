/******************************************************************************


             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: OpeEstCuba.c

	CONTEUDO	: Modulo de comando de operacao. Permite ao operador mudar o 
                  estado da CUBA.

	AUTOR		: Junia Guerra

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 2.0		  -		  DATA  : 12/08/94

	HISTORICO DAS EDICOES

$Id: OpeCbaEstCuba.c,v 1.1.2.1 2015/10/27 16:52:29 clage Exp $

$Log: OpeCbaEstCuba.c,v $
Revision 1.1.2.1  2015/10/27 16:52:29  clage
Entrega dos fontes dos programas de operacao do Score para a CBA


******************************************************************************/

#define PROGRAMA_PRINCIPAL

/*-- Definicao dos tags dos botoes --*/
#define PARAMETRO_NORMAL			1
#define PARAMETRO_LIGADO			2
#define PARAMETRO_DESLIGADO			3
#define PARAMETRO_PARTIDO			4

/*
-------------------------------------------------------------------------------
							Includes
-------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/kernel.h>
#include <Comandos.h>
#include <Score.h>
#include <VarsComum.h>
#include <ScoreMsgs.h>
#include <ScoreErros.h>
#include <Prototipos.h>
#include <AjusteCamisa.h>

/*
-------------------------------------------------------------------------------
							Constantes
-------------------------------------------------------------------------------
*/

#define NUM_PARAM		4

/*
-------------------------------------------------------------------------------
							Prototipos
-------------------------------------------------------------------------------
*/
void main ( int argc, char *argv[] );
void InicializaVarsGeral(int Cuba);
int MudaEstCuba(const int aCuba, const int aEstado, const int aOperador);
char *NomeEstado(int Estado);
void InicializaVarsGeral(int Cuba);

int  ConsArgs(int argc, char *argv[], int *Estado, char *PMsg);
void MudaEstado(int Estado, char *argv[]);

/*
-------------------------------------------------------------------------------
							Variaveis Globais
-------------------------------------------------------------------------------
*/

t_filtrosPD filtro;

/*
-------------------------------------------------------------------------------
							Main
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[])
{
  int   Estado;
  char  Msg[80];
  pid_t PidPai;

  /*-- Aguarda sinal do modulo AtivaOperacao --*/
  PidPai = Receive(0, NULL, 0);

  /*-- Pega segmento comum da base de dados --*/
  if (PegaComum(&Comum))
	sprintf(Msg, ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_0 );
  else
  {
	/*-- Consiste argumentos recebidos retornando mensagem de erro --*/
	if (ConsArgs(argc, argv, &Estado, Msg) eq VERDADEIRO) 
	{
	  MudaEstado(Estado, argv);
	  strcpy(Msg, ScoreGetStr(MSG_EST_ALT));
	}
  }

  /*-- Envia mensagem liberando o modulo AtivaOperacao --*/
  Reply(PidPai, Msg, sizeof(Msg));
  /* Aguarda tarefa receber resposta antes de morrer. Na rede com maquinas 
     486 33 e 66 misturadas com Pentium, a rede fica mais lenta algumas vezes
     e o nodo de operacao recebe a indicacao de que a tarefa morreu ANTES de
     receber seu reply, falhando o send. No entanto esta tarefa recebeu o
     send, o processou normalmente e respondeu normalmente. O sleep e' para
     dar tempo do outro micro receber o reply. */
  sleep(15);
}

/*
-------------------------------------------------------------------------------
  ConsArgs - Consiste argumentos passados para o programa de operacao
-------------------------------------------------------------------------------
*/
int ConsArgs(int argc, char *argv[], int *Estado, char *PMsg)
{
  int	Tag;

  if (argc ne NUM_PARAM)
  {
	sprintf(PMsg, ScoreGetStr(SCORE_MSG_210));
	return(FALSO);
  }

  /*-- Le arquivo de filtro de cubas --*/
  if (LeFiltroCubas(argv[1], &filtro))
  {
    sprintf(PMsg, ScoreGetStr(SCORE_ERR_2),My_name,COD_ERRO_6, argv[1]);
	return(FALSO);
  }
  if( filtro.Par.Total eq 0 )
  {
    strcpy(PMsg, ScoreGetStr(SCORE_MSG_356));
	return(FALSO);
  }

  /*-- Critica o estado da cuba --*/
  Tag = atoi(argv[2]);
  if (Tag eq PARAMETRO_NORMAL)
  {
	*Estado = CUBA_NORMAL;
  }
  else
  {
	if (Tag eq PARAMETRO_PARTIDO)
	{
	  *Estado = CUBA_PARTIDA;
	}
	else
	{
	  if (Tag eq PARAMETRO_LIGADO)
	  {
		*Estado = CUBA_LIGADA;
	  }
	  else
	  {
		if (Tag eq PARAMETRO_DESLIGADO)
		{
		  *Estado = CUBA_DESLIGADA;
		}
		else
		{
		  strcpy(PMsg, ScoreGetStr(SCORE_MSG_363));
		  return(FALSO);
		}
	  }
	}
  }

  return(VERDADEIRO);
}

/*
-------------------------------------------------------------------------------
  MudaEstado - Muda estado da Cuba e gera evento de mudanca de estado.
-------------------------------------------------------------------------------
*/
void MudaEstado(int Estado, char *argv[])
{
  int  IndCuba;
  int  CubaAtual;
  int  Cuba;
  char Operador[9];

  /*-- Aloca semaforos --*/
  AlocaSemaf(SEMAF_AVC);
  AlocaSemaf(SEMAF_AVL);

  /*-- Faz loop das cubas --*/
  IndCuba = 0;
  strcpy(Operador, argv[3]);
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	Cuba	  = filtro.Par.NumCuba[IndCuba];    
	if (CubaAtual ne (-1))
	  MudaEstCuba(CubaAtual,Estado,atoi(Operador));
	++IndCuba;
  }
  LiberaSemaf(SEMAF_AVL);
  LiberaSemaf(SEMAF_AVC);
  AlteracaoTabela(TABELA_EST_AVC);
  AlteracaoTabela(TABELA_AVC);
  AlteracaoTabela(TABELA_AVL);
}

/*
-------------------------------------------------------------------------------
  MudaEstCuba - Muda estado da Cuba e gera evento de mudanca de estado.
  				Retorna 0 se ok e <> 0 se erro.
-------------------------------------------------------------------------------
*/
int MudaEstCuba(const int aCuba, const int aEstado, const int aOperador)
{
  char PMsgParam[9];
  char PMsgParamAnt[9];

  if (aCuba ne (-1))
  {
	if (EST_AVC(aCuba).EstadoCuba ne aEstado)
	{
		strcpy(PMsgParamAnt, NomeEstado(EST_AVC(aCuba).EstadoCuba));
		EST_AVC(aCuba).EstadoCuba = aEstado;
		/*-- Inicializa variaveis da cuba qdo mudanca de estado --*/
		InicializaVarsGeral(aCuba);

		/* -- Inicializacoes especificas para cada estado -- */
		switch(aEstado)
		{
		  case CUBA_NORMAL:
			break;
		  case CUBA_PARTIDA:
			break;
		  case CUBA_LIGADA:
			break;
		  case CUBA_DESLIGADA:
			break;
		  default: /* erro */
		    return(1);
		}

		/*-- Gera evento de mudanca de estado --*/
		strcpy(PMsgParam, NomeEstado(aEstado));
		GeraEvento(EVENTO_MUDA_ESTADO, aCuba, -1, PMsgParam, ScoreGetStr(STR_TERMINAL));
		if (AVL.HabLogOper)
		  GeraEvento(LOG_OPER_CUBA, aCuba, -1, ScoreGetStr(LOG_EST_CUBA),
		  			 (aOperador eq -1 ? STR_TRACO : NomeOper(aOperador)),
					 PMsgParamAnt, PMsgParam, STR_TRACO);
	}
	return(0);
  }
  else
    return(2);
}

/*
-------------------------------------------------------------------------------
InicializaVarsGeral - Inicializa variaveis da cuba qdo. de mudanca de estado
-------------------------------------------------------------------------------
*/
void InicializaVarsGeral(int Cuba)
{
  int	IntervCicCont;

  /* -- inicializa variaveis da previsao de EA -- */
  /* -- Intervalo do ciclo de controle em minutos -- */
  IntervCicCont=(Comum->BaseTempoMcp*Comum->BaseTempoMcc)/(SAD_TICKS*60);

  AVC.Ea[Cuba].DerivHMaxPrevEa=-1.0;
  AVC.Ea[Cuba].CiclosFimPrev=AVC.Param[Cuba].IntervFimEaPrevDeriv/IntervCicCont;
  AVC.Ea[Cuba].CiclosIniPrev=AVC.Param[Cuba].IntervEaPrevDeriv/IntervCicCont;
  AVC.Ea[Cuba].CiclosInibeMov=AVC.Param[Cuba].IntervDerivInibeMov/IntervCicCont;
  AVC.Ea[Cuba].KSuave=0;
  AVC.Ea[Cuba].RSuave=0.0;
  AVC.Ea[Cuba].RSuaveDeriv=0.0;
  AVC.Ea[Cuba].RSuaveDerivH=0.0;

  /* -- inicializa BandaMortaSupAtual -- */
  AVC.Ccont[Cuba].BandaMortaSupAtual=AVC.Param[Cuba].BandaMortaSup;
  AVC.Ccont[Cuba].Rerro = 0.0;
  /*-- Inicializa as variaveis para o relatorio instantaneo de cubas --*/
  AVC.Ccont[Cuba].VAlvo = 0.0;
  AVC.Ccont[Cuba].VErro = 0.0;

  /* Inicio Alteracao - Carlos - 23/06/99 */
  /* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
  AVC.Ccont[Cuba].IAlvoCuba=AVC.Ccont[Cuba].INominalCuba;
#endif
  /* Fim Alteracao - Carlos - 23/06/99 */

  AVL.IAlvo=AVL.INominal;

  /* -- inicializa rinc e ralvo -- */
  AVC.Ccont[Cuba].Rinc=0.0;
  AVC.Ccont[Cuba].RAlvo=0.0;

  EST_AVC(Cuba).DesvioTensao = FALSO;
  EST_AVC(Cuba).DeuAcresBMSup= FALSO;
  EST_AVC(Cuba).EaPrev		 = FALSO;
  EST_AVC(Cuba).EfeitoEa	 = FALSO;
  EST_AVC(Cuba).EfeitoMove	 = FALSO;
  EST_AVC(Cuba).EsperaConfMove=FALSO;
  EST_AVC(Cuba).ForaControle = FALSO;
  EST_AVC(Cuba).EaPrev		 = FALSO;
  EST_AVC(Cuba).InibeMovEaPrev=FALSO;

  EST_AVC(Cuba).Ea			 = FALSO;
  EST_AVC(Cuba).ElimEaAtivo = FALSO;
  /* -- inicializa variaveis da quebrada preventiva -- */
  EST_AVC(Cuba).Est.QuebPrev     = FALSO;
  AVC.User1[Cuba].NumQuebPrev    = 0;
  AVC.User1[Cuba].NumPrevQPrev   = 0;
  AVC.User1[Cuba].ContDurQPrev   = 0L;
  EST_AVC(Cuba).Est.QuebPrevInib = QPREV_SEM_INIBICAO;
  AVC.User1[Cuba].ContInibQPrev  = 0L;
  if  ((Comum->IdentReducao ne 5) and
	  (Comum->IdentReducao ne 6))
  { /* 120kA I a IV, 125 kA V a VII */
	/* -- inicializa variaveis de ajuste de camisa -- */
	EST_AVC(Cuba).Est.AjusteCamisa = FALSO;
	EST_AVC(Cuba).Est.AbortaAjuste = AJUSTE_NORMAL;
	EST_AVC(Cuba).Est.CamNAjust = FALSO;
	AVC.User1[Cuba].ContTAjAcum    = 0.0;
	AVC.User1[Cuba].ContTAjCam     = 0.0;
	AVC.User1[Cuba].ContInibAjCam  = 0;
  }

  /*-- Elimina tratamento de manobra de cruzeiro --*/
  EST_AVC(Cuba).TrataCruzeiro = FALSO;
  /* -- Inicializa variaveis para verificacao de atraso EA -- */
  AVC.Ea[Cuba].EaHoraFimProv = time(NULL)/TIMES_PER_SEC;
  AVC.Ea[Cuba].EaHoraInicio = time(NULL)/TIMES_PER_SEC;

  /*-- Elimina incremento de usuario ativo --*/
  AVC.Ccont[Cuba].IncUsuario = 0.0;
  AVC.Ccont[Cuba].ContIncUsuario = -1;
  EST_AVC(Cuba).TrataIncUsuario = FALSO;

  /*-- Elimina incremento por quebrada ativo --*/
  EST_AVC(Cuba).Quebrada= FALSO;
  EST_AVC(Cuba).EfeitoQueb   = FALSO;
  AVC.Ccont[Cuba].IncQueb=0.0;
  AVC.Ccont[Cuba].ContIncQueb=-1;

  /*-- Elimina incremento de operacao ativo --*/
  AVC.Ccont[Cuba].HabIncOper = FALSO;
  AVC.Ccont[Cuba].IncOper = 0.0;
  AVC.Ccont[Cuba].ContIncOper = -1;

  /*-- Elimina incremento por troca de pinos ativo --*/
  EST_AVC(Cuba).TrataTPinos = FALSO;
  AVC.Ccont[Cuba].IncTPinos = 0.0;
  AVC.Ccont[Cuba].ContIncTPinos = -1;

  /*-- Elimina incremento por corrida ativo --*/
  EST_AVC(Cuba).EfeitoCorr = FALSO;
  EST_AVC(Cuba).Corrida = FALSO;
  AVC.Ccont[Cuba].IncCorr = 0.0;
  AVC.Ccont[Cuba].ContIncCorr = -1;

  /*-- Elimina incremento por ruido lento --*/
  EST_AVC(Cuba).RuidoLent=FALSO;
  AVC.Ccont[Cuba].IncRlent=0;
  AVC.Ruido[Cuba].TipoRLent=SEM_RUIDO;

  /*-- Elimina incremento por ruido rapido --*/
  EST_AVC(Cuba).RuidoRap=FALSO;
  AVC.Ccont[Cuba].IncRrap=0;
  AVC.Ruido[Cuba].TipoRRap=SEM_RUIDO;
}

/*
-------------------------------------------------------------------------------
  NomeEstado - Retorna o nome do estado recebido como parametro
-------------------------------------------------------------------------------
*/
char *NomeEstado(int Estado)
{
  static char Nome[9];

  memset(Nome, 0x00, sizeof(Nome));
  switch(Estado)
  {
	case CUBA_NORMAL:
		 strcpy(Nome, ScoreGetStr(STR_NORMAL));
		 break;

	case CUBA_PARTIDA:
		 strcpy(Nome, ScoreGetStr(STR_PARTIDA));
		 break;

	case CUBA_LIGADA:
		 strcpy(Nome, ScoreGetStr(STR_LIGADA));
		 break;

	case CUBA_DESLIGADA:
		 strcpy(Nome, ScoreGetStr(STR_DESLIGADA));
		 break;
  }

  return(Nome);
}

/* -- fim OpeEstCuba.c -- */
