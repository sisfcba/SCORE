/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: OpeCbaIncTPinos.c

	CONTEUDO	: Modulo de comando de operacao. Permite ao operador ativar ou 
				  desativar incremento por troca de pinos das cubas.

	AUTOR		: Carlos Cezar Silva Lage

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 2.0		  -		  DATA  : 12/08/94

	HISTORICO DAS EDICOES

$Id: OpeCbaIncTPinos.c,v 1.1.2.1 2015/10/27 16:52:29 clage Exp $

$Log: OpeCbaIncTPinos.c,v $
Revision 1.1.2.1  2015/10/27 16:52:29  clage
Entrega dos fontes dos programas de operacao do Score para a CBA


******************************************************************************/

#define PROGRAMA_PRINCIPAL

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
#include <Eventos.h>

/*
-------------------------------------------------------------------------------
							Constantes
-------------------------------------------------------------------------------
*/

 #define NUM_PARAM				4

/*-- Definicao dos tags dos botoes --*/
#define PARAMETRO_ATIVAR			1
#define PARAMETRO_DESATIVAR			2

/*
-------------------------------------------------------------------------------
							Prototipos
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[]);
int  ConsArgs(int argc, char *argv[], int *Acao, char *PMsg);
int  ConsHabTPinos(char *PMsg);
void AcaoIncremento(int Acao, char *argv[]);

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
  int	Acao;
  char	Msg[80];
  pid_t	PidPai;

  /*-- Aguarda sinal do modulo AtivaOperacao --*/
  PidPai = Receive(0, NULL, 0);


  /*--- Pega segmento comum da base de dados ---*/
  if (PegaComum(&Comum))
	sprintf(Msg, ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_0 );
  else
  {
	/*-- Consiste argumentos recebidos retornando mensagem de erro --*/
	if (ConsArgs(argc, argv, &Acao, Msg) eq VERDADEIRO) 
	{
	  AcaoIncremento(Acao, argv);
	  strcpy(Msg, ScoreGetStr(SCORE_MSG_368));
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
ConsArgs - Consiste numero de argumentos passados para o comando, critica
		   numero da Cuba Inicial e Final e acao (ativa/desativa)
-------------------------------------------------------------------------------
*/
int ConsArgs(int argc, char *argv[], int *Acao, char *PMsg)
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
  if (filtro.Par.Total eq 0)
  {
    strcpy(PMsg, ScoreGetStr(SCORE_MSG_356));
	return(FALSO);
  }

  /*-- Valida o modo de operacao da cuba --*/
  Tag = atoi(argv[2]);
  if (Tag eq PARAMETRO_ATIVAR)
  {
	if (ConsHabTPinos(PMsg) ne VERDADEIRO)
	  return(FALSO); 
	*Acao = ATIVAR;
  }
  else
  {
	if (Tag eq PARAMETRO_DESATIVAR)
	{
	  *Acao = DESATIVAR;
	}
	else
	{
	  strcpy(PMsg, ScoreGetStr(SCORE_MSG_371));
	  return(FALSO);
	}
  }
  return(VERDADEIRO);
}


/*
-------------------------------------------------------------------------------
ConsHabTPinos - Verifica se esta habilitado o tratamento de troca de pinos
				para a faixa de cubas pedidas.
-------------------------------------------------------------------------------
*/
int ConsHabTPinos(char *PMsg)
{
  int  IndCuba;
  int  CubaAtual;
  int  Cuba;

  /*-- Faz loop dos grupos --*/
  IndCuba = 0;
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	Cuba	  = filtro.Par.NumCuba[IndCuba];    
	if (CubaAtual ne (-1))
	{
	  /*-- Verifica se tratamento de troca de pinos esta habilitado --*/
	  if (AVC.Param[CubaAtual].HabIncTPinos ne VERDADEIRO)
	  {
		sprintf(PMsg, ScoreGetStr(SCORE_MSG_394), Cuba);
		return(FALSO);
	  }
	}
	++IndCuba;
  }

  return(VERDADEIRO);
}

/*
-------------------------------------------------------------------------------
AcaoIncremento - Ativa / Desativa incremento de troca de pinos das  cubas  e
				 gera evento.
-------------------------------------------------------------------------------
*/
void AcaoIncremento(int Acao, char *argv[])
{
  int	 IndCuba;
  char	 *PMsgParam;
  char	 *PTipoInc;
  char	 StrVInc[9];
  char	 StrTInc[9];
  char	 Operador[9];
  int	 CubaAtual;
  int	 Cuba;
  time_t HoraAtual;

  HoraAtual=time(NULL)/TIMES_PER_SEC; /* -- segs. apartir 1/1/1970 -- */

  /*-- Aloca semaforo --*/
  AlocaSemaf(SEMAF_AVC);

  /*-- Faz loop dos grupos --*/
  IndCuba = 0;
  strcpy(Operador, argv[3]);
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	Cuba	  = filtro.Par.NumCuba[IndCuba];    

	if (CubaAtual ne (-1))
	{
	  switch(Acao)
	  {
		case ATIVAR:
			 if (EST_AVC(CubaAtual).TrataTPinos ne VERDADEIRO)
			 {
			   EST_AVC(CubaAtual).TrataTPinos = VERDADEIRO;
			   AVC.Ccont[CubaAtual].ContIncTPinos = -1;
			   AVC.User3[CubaAtual].HoraUltTPinosAnt = AVC.Cleit[CubaAtual].HoraUltTPinos;
			   AVC.Cleit[CubaAtual].HoraUltTPinos=HoraAtual;
			   PMsgParam = ScoreGetStr(STR_ATIVA);
			   if (AVC.Param[CubaAtual].TipoIncTPinos eq INCREMENTO_LINEAR)
				 PTipoInc = ScoreGetStr(STR_CONST);
			   else
				 PTipoInc = ScoreGetStr(STR_RAMPA);
			   sprintf(StrVInc,"%03.1f",AVC.Param[CubaAtual].IncTPinosInic * 1000.0);
			   sprintf(StrTInc,"%d:%02d",AVC.Param[CubaAtual].TIncTPinos/60,
					   AVC.Param[CubaAtual].TIncTPinos Mod 60);
			   GeraEvento(EV_INC_TROCA_PINOS, CubaAtual, -1, ScoreGetStr(STR_TERMINAL),
						  StrTInc, PTipoInc, StrVInc, PMsgParam);
			   if (AVL.HabLogOper)
				 GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, ScoreGetStr(LOG_INC_TROCA_PINOS),
							NomeOper(atoi(Operador)), StrTInc, StrVInc, PMsgParam);
			 }
			 break;
		case DESATIVAR:
			 if (EST_AVC(CubaAtual).TrataTPinos ne FALSO)
			 {
			   EST_AVC(CubaAtual).TrataTPinos = FALSO;
			   AVC.Ccont[CubaAtual].IncTPinos = 0.0;
			   AVC.Ccont[CubaAtual].ContIncTPinos = -1;
	/* -- alteracao - inicio - 15/10/2002 - Leonel - Retirado para nao renicializar hora da ult. troca -- */
	//****		   AVC.Cleit[CubaAtual].HoraUltTPinos=HoraAtual;
	/* -- alteracao - fim - 15/10/2002 - Leonel - Retirado para nao renicializar hora da ult. troca -- */
			   strcpy(StrVInc, STR_NULL);
			   PTipoInc  = STR_NULL;
			   strcpy(StrTInc, STR_NULL);
			   PMsgParam = ScoreGetStr(STR_DESATIVA);
			   GeraEvento(EV_INC_TROCA_PINOS, CubaAtual, -1, ScoreGetStr(STR_TERMINAL),
						  StrTInc, PTipoInc, StrVInc, PMsgParam);
			   if (AVL.HabLogOper)
				 GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, ScoreGetStr(LOG_INC_TROCA_PINOS),
							NomeOper(atoi(Operador)), StrTInc, StrVInc, PMsgParam);
			 }
			 break;
	  }
	}
	++IndCuba;
	
  }
  AlteracaoTabela(TABELA_EST_AVC);
  LiberaSemaf(SEMAF_AVC);
}
