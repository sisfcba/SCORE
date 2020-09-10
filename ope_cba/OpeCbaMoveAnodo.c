/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: OpeCbaMoveAnodo

	CONTEUDO	: Modulo de comando de operacao. Permite ao operador movimentar
                  anodo manualmente.

	AUTOR		: Junia Guerra

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 2.0		  -		  DATA  : 12/08/94

	HISTORICO DAS EDICOES

$Id: OpeCbaMoveAnodo.c,v 1.1.2.1 2015/10/27 16:52:30 clage Exp $

$Log: OpeCbaMoveAnodo.c,v $
Revision 1.1.2.1  2015/10/27 16:52:30  clage
Entrega dos fontes dos programas de operacao do Score para a CBA


******************************************************************************/


#define PROGRAMA_PRINCIPAL

/*-- Definicao dos tags dos botoes --*/
#define PARAMETRO_SUBIR				"1"
#define PARAMETRO_DESCER			"2"
#define PARAMETRO_RESISTENCIA		"3"
#define PARAMETRO_TEMPO				"4"


/*
-------------------------------------------------------------------------------
							Includes
-------------------------------------------------------------------------------
*/

#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/kernel.h>
#include <Comandos.h>
#include <Score.h>
#include <VarsComum.h>
#include <ScoreMsgs.h>
#include <ScoreErros.h>
#include <Prototipos.h>
#include <Eventos.h>

/*
-------------------------------------------------------------------------------
							Constantes
-------------------------------------------------------------------------------
*/

#define NUM_PARAM				5		/*-- Numero de parametros do comando --*/

/*
-------------------------------------------------------------------------------
							Prototipos
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[]);

int  ConsArgs(int argc, char *argv[], int *Sentido, double *Duracao, char *PMsg);
void MoveAnodoManual(int Sentido, double *Duracao, char *argv[]);
int  ValidaCondMove(int Sentido, double Duracao, char *PMsg);
int  MudaOperMoveAnodoCuba(const int aCuba, const double aDuracao,
				           const int aSentido, const int aOperador);

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
  int	 Sentido;
  double Duracao;
  char   Msg[80];
  pid_t  PidPai;

  /*-- Aguarda sinal do modulo AtivaOperacao --*/
  PidPai = Receive(0, NULL, 0);

  /*--- Pega segmento comum da base de dados ---*/
  if (PegaComum(&Comum))
	sprintf(Msg, ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_0 );
  else
  {
	/*-- Consiste argumentos recebidos retornando mensagem de erro --*/
	if (ConsArgs(argc, argv, &Sentido, &Duracao, Msg) eq VERDADEIRO) 
	{
	  MoveAnodoManual(Sentido, &Duracao, argv);
	  strcpy(Msg, ScoreGetStr(MSG_MOVE_ANODO));
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
  ConsArgs - Consiste os argumentos passados para o programa de operacao
-------------------------------------------------------------------------------
*/
int ConsArgs(int argc, char *argv[], int *Sentido, double *Duracao, char *PMsg)
{

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
  if (filtro.Par.Total eq 0)
  {
    strcpy(PMsg, ScoreGetStr(SCORE_MSG_356));
	return(FALSO);
  }

  /*-- Critica o sentido do movimento --*/
  if (strstr(argv[2], PARAMETRO_SUBIR) ne NULL)
  {
	*Sentido = SUBIR_ANODO;
  }
  else
  {
	if (strstr(argv[2], PARAMETRO_DESCER) ne NULL)
	{
	  *Sentido = DESCER_ANODO;
	}
	else
	{
	  strcpy(PMsg, ScoreGetStr(SCORE_MSG_428));
	  return(FALSO);
	}
  }

  if (argv[3] eq NULL)
  {
    strcpy(PMsg, ScoreGetStr(SCORE_MSG_313));
	return(FALSO);
  }
  else
  {
	*Duracao = atof(argv[3]);
	if (ValidaCondMove(*Sentido, *Duracao, PMsg) ne VERDADEIRO)
	  return(FALSO);
  }

  return(VERDADEIRO);
}

/*
--------------------------------------------------------------------------------
	ValidaCondMove - Verifica condicoes para movimentar manualmente anodo da
					 Cuba
--------------------------------------------------------------------------------
*/
int ValidaCondMove(int Sentido, double Duracao, char *PMsg)
{
  int	IndCuba;
  char	Msg[80];
  int	Cuba;
  int	CubaAtual;

  /*-- Faz loop de cubas --*/
  IndCuba = 0;
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	Cuba	  = filtro.Par.NumCuba[IndCuba];    
	if (CubaAtual ne (-1))
	{
	  /*-- Verifica se chave no campo esta em remoto e a cuba --*/
	  /*-- em modo Manual-Remoto --*/
	  if ((EST_AVC(CubaAtual).ChaveLocRem eq REMOTO) and
		  (EST_AVC(CubaAtual).ChaveAutMan eq MANUAL) and
		   (EST_AVC(CubaAtual).Est.AEK eq FALSO))
	  {
		/*-- Critica a duracao do movimento --*/
		if (Sentido eq SUBIR_ANODO)
		{
		  if ((Duracao < AVC.Param[CubaAtual].DurMovCimaMin) or
			  (Duracao > AVC.Param[CubaAtual].DurMovCimaMax) or
			  (Duracao eq 0.0) )
		  {
			sprintf(Msg, ScoreGetStr(SCORE_MSG_431), Cuba);
			strcpy(PMsg, Msg);
			return(FALSO);
		  }
		}
		else
		{
		  if ((Duracao < AVC.Param[CubaAtual].DurMovBaixoMin) or
			  (Duracao > AVC.Param[CubaAtual].DurMovBaixoMax) or
			  (Duracao eq 0.0) )
		  {
			sprintf(Msg, ScoreGetStr(SCORE_MSG_432), Cuba);
			strcpy(PMsg, Msg);
			return(FALSO);
		  }
		}
	  }
	  else
	  {
		if (EST_AVC(CubaAtual).ChaveLocRem ne REMOTO)
		{
		  /*-- Monta mensagem de cuba em modo manual-local --*/
		  sprintf(Msg, ScoreGetStr(SCORE_MSG_433), Cuba);
		}
		else if (EST_AVC(CubaAtual).ChaveAutMan eq AUTOMATICO)
		{
		  /*-- Monta mensagem de cuba em automatico --*/
		  sprintf(Msg, ScoreGetStr(SCORE_MSG_434), Cuba);
		}
		else if (EST_AVC(CubaAtual).Est.AEK eq VERDADEIRO)
		{
		  /*-- Monta mensagem de cuba em automatico --*/
		  sprintf(Msg, "Cuba %d Tabela em atuacao.", Cuba);
		}

		strcpy(PMsg, Msg);
		return(FALSO);
	  }
	} /*-- if (CubaAtual ne (-1)) --*/
	++IndCuba;
  } /*-- for (Cuba ...) --*/

  return(VERDADEIRO);
}

/*
--------------------------------------------------------------------------------
  MoveAnodoManual - Efetua movimentacao de anodo gerando seu evento.
--------------------------------------------------------------------------------
*/
void MoveAnodoManual(int Sentido, double *Duracao, char *argv[])
{
  int	 IndCuba;
  char	 Operador[9];
  int	 CubaAtual;
  int	 Cuba;
  time_t HoraAtual;

  /*-- Pega a hora atual --*/
  HoraAtual=time(NULL)/TIMES_PER_SEC;

  /*-- Faz loop de cubas --*/
  IndCuba = 0;
  strcpy(Operador, argv[4]);
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	Cuba	  = filtro.Par.NumCuba[IndCuba];    
	if (CubaAtual ne (-1))
	{
	  MudaOperMoveAnodoCuba(CubaAtual, *Duracao, Sentido, atoi(Operador));
	} /*-- if (CubaAtual ne (-1)) --*/
	++IndCuba;
  } /*-- for (Cuba ...) --*/
}

/*
-------------------------------------------------------------------------------
  MudaOperMoveAnodoCuba - Faz movimentacao de anodo via operacao
  				   	  Retorna 0 se ok e <> 0 se erro.
-------------------------------------------------------------------------------
*/
int MudaOperMoveAnodoCuba(const int aCuba, const double aDuracao,
				   const int aSentido, const int aOperador)
{
  char	 TemMov[9];
  char   str_vinst[9];
  float  VAlvo;
  float  VInst;
  float	 VCicCont;
  time_t HoraAtual;

  /*-- Pega a hora atual --*/
  HoraAtual = time(NULL) / TIMES_PER_SEC;

  if(aCuba ne (-1))
  {
    /*-- comanda a movimentacao do anodo --*/
	MoveAnodo(aCuba, (int)(aDuracao * BASE_TEMPO_REMOTA), aSentido);
	AVC.Ccont[aCuba].HoraUltMove = HoraAtual;
	AVC.Ccont[aCuba].SentidoUltMove = aSentido;

	/*-- Gera evento de movimentacao manual de anodo --*/
	sprintf(TemMov, "%4.1f", (float)aDuracao);
	VAlvo = AVC.Ccont[aCuba].VAlvo;
	VInst = AVC.Cleit[aCuba].Vinst;

    /* Inicio Alteracao - Carlos - 23/06/99 */
	/* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
	VCicCont = AVC.CcontMcp[aCuba].RCicContlBruta * AVC.Ccont[aCuba].INominalCuba +
		       AVC.Param[aCuba].Bemf;
#else
	VCicCont = AVC.CcontMcp[aCuba].RCicContlBruta * AVL.INominal +
			   AVC.Param[CubaAtual].Bemf;
#endif
    /* Fim Alteracao - Carlos - 23/06/99 */

	sprintf(str_vinst, "%3.2f", VInst);
	if(aSentido eq SUBIR_ANODO)
	{
	  GeraEvento(SUBIDA_MAN_ANODO, aCuba, -1, ScoreGetStr(STR_TERMINAL),
			     TemMov, VCicCont, VInst, VAlvo);
	  if(AVL.HabLogOper)
		GeraEvento(LOG_OPER_CUBA, aCuba, -1, ScoreGetStr(SCORE_MSG_436),
			 	   NomeOper(aOperador), ScoreGetStr(STR_SUBIU), TemMov, str_vinst);
    }
	else
	{
   	  GeraEvento(DESCIDA_MAN_ANODO, aCuba, -1, ScoreGetStr(STR_TERMINAL),
				 TemMov, VCicCont, VInst, VAlvo);
      if(AVL.HabLogOper)
	    GeraEvento(LOG_OPER_CUBA, aCuba, -1, ScoreGetStr(SCORE_MSG_436),
                   NomeOper(aOperador), ScoreGetStr(STR_DESCEU), TemMov, str_vinst);
	}
	return(0);
  } /*-- if (aCuba ne (-1)) --*/
  return(1);
}
/* -- fim MudaMoveAnodoCuba.c -- */

