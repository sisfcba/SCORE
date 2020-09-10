/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: OpeCbaIncPadrao.c

	CONTEUDO	: Modulo de comando de operacao. Permite ao operador ativar ou 
				  desativar incrementos por operacao nas cubas.

	AUTOR		: Marco Aurelio Moreira Lopes

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 2.0		  -		  DATA  : 13/11/18

	HISTORICO DAS EDICOES

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

/*-- Numero maximo de cubas a serem excluidas --*/
#define	MAX_EXC_CUBAS			15

/*-- Numero de parametros --*/
#define NUM_PARAM		4

/*-- Definicao dos tags dos botoes --*/
#define PARAMETRO_ATIVAR			"1"
#define PARAMETRO_DESATIVAR			"2"
#define PARAMETRO_TIPO1				"3"
#define PARAMETRO_TIPO2				"4"
#define PARAMETRO_TIPO3				"5"
#define PARAMETRO_TIPO4				"6"
#define PARAMETRO_TIPO5				"7"
#define PARAMETRO_TIPO6				"8"

/*
-------------------------------------------------------------------------------
								Prototipos
-------------------------------------------------------------------------------
*/

void main(int argc, char *argv[]);
int  ConsArgs(int argc, char *argv[], int *Acao, int *TipoInc, char *PMsg);
int  ValidaIncOper(float VInc, char *PMsg);
void TrataIncOper(int Acao, int TipoInc, char *argv[]);
int  ValidaDurInc(char *PtStr, int *Tempo);

/*
-------------------------------------------------------------------------------
								Variaveis Globais
-------------------------------------------------------------------------------
*/

int TabCubas[MAX_EXC_CUBAS];
t_filtrosPD filtro;

/*
-------------------------------------------------------------------------------
								Main
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[])
{
  int	Acao;
  int	TipoInc;
  char  Msg[80];
  pid_t PidPai;

  /*-- Aguarda sinal do modulo AtivaOperacao --*/
  PidPai = Receive(0, NULL, 0);

  /*--- Pega segmento comum da base de dados ---*/
  if (PegaComum(&Comum))
	sprintf(Msg, ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_0 );
  else
  {
	/*-- Consiste argumentos recebidos retornando mensagem de erro --*/
	if (ConsArgs(argc, argv, &Acao, &TipoInc, Msg) eq VERDADEIRO) 
	{
	  TrataIncOper(Acao, TipoInc, argv);
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
	ConsArgs - Consiste  numero de  argumentos  passados  para o comando,
			   cuba inicial e final, acao, tipo, tensao inicial, duracao
			   e limite do incremento.
-------------------------------------------------------------------------------
*/
  int ConsArgs(int argc, char *argv[], int *Acao, int *TipoInc, char *PMsg)
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

  /*-- Valida acao de incremento --*/
  if (strstr(argv[2],PARAMETRO_ATIVAR) ne NULL)
	*Acao = ATIVAR;
  else
  {
	if (strstr(argv[2],PARAMETRO_DESATIVAR) ne NULL)
	  *Acao = DESATIVAR;
	else
	{
	  strcpy(PMsg, ScoreGetStr(SCORE_MSG_371));
	  return(FALSO);
	}
  }

  /*-- Valida tipo de incremento --*/
  if (*Acao eq ATIVAR)
  {
	/*-- Valida tipo de incremento --*/
	if (strstr(argv[2],PARAMETRO_TIPO1) ne NULL)
	  *TipoInc = 0;
	else
	{
	  if (strstr(argv[2],PARAMETRO_TIPO2) ne NULL)
		*TipoInc = 1;
	  else
	  {
	    if (strstr(argv[2],PARAMETRO_TIPO3) ne NULL)
		  *TipoInc = 2;
		else
		  if (strstr(argv[2],PARAMETRO_TIPO4) ne NULL)
			*TipoInc = 4;
		  else
	  	    if (strstr(argv[2],PARAMETRO_TIPO5) ne NULL)
			  *TipoInc = 4;
			else
	  		  if (strstr(argv[2],PARAMETRO_TIPO6) ne NULL)
				*TipoInc = 5;
			  else
			  {	
				strcpy(PMsg, ScoreGetStr(SCORE_MSG_373));
				return(FALSO);
	  		  }
	  }
	}
  }

  return(VERDADEIRO);
}

/*
-------------------------------------------------------------------------------
	ValidaIncOper - Valida os limites de incremento por operacao.
-------------------------------------------------------------------------------
*/
int ValidaIncOper(float VInc, char *PMsg)
{
  int	IndCuba;
  int	CubaAtual;
  int	Cuba;

  IndCuba = 0;
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	Cuba	  = filtro.Par.NumCuba[IndCuba];    
	if (CubaAtual ne -1)
	{
	  /*-- Valida a tensao de incremento da cuba. --*/
	  if ((VInc >  AVC.Param[CubaAtual].VIncMax) or
		  (VInc < ((-1) * AVC.Param[CubaAtual].VIncMax)))
	  {
		sprintf(PMsg, ScoreGetStr(SCORE_MSG_380), Cuba);
		return(FALSO);
	  }
	} /*-- if (CubaAtual ...) --*/
	++IndCuba;
  } /*-- for (Cuba ...) --*/

  return(VERDADEIRO);
}

/*
-------------------------------------------------------------------------------
  TrataIncOper - Ativa / Desativa incremento de operacao das cubas
				   e gera evento.
-------------------------------------------------------------------------------
*/
void TrataIncOper(int Acao, int TipoInc, char *argv[])
{
  int	IndCuba;
  char	*PMsgParam;
  char	*PTipoInc;
  char	StrTInc[9];
  char	StrVInc[9];
  char	Operador[9];
  int	CubaAtual;
  int	Cuba;

  /*-- Aloca semaforos --*/
  AlocaSemaf(SEMAF_AVC);

  /*-- Faz loop dos grupos --*/
  IndCuba = 0;
  strcpy(Operador, argv[3]);
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	Cuba	  = filtro.Par.NumCuba[IndCuba];    
	if (CubaAtual ne -1)
	{

    strcpy(Operador, argv[3]);

	  switch (Acao)
	  {
		case ATIVAR:
			 AVC.Ccont[CubaAtual].HabIncOper = VERDADEIRO;
			 AVC.Ccont[CubaAtual].TipoIncOp  = AVC.ParUser2[CubaAtual].TipoIncPadrao[TipoInc];
			 AVC.Ccont[CubaAtual].IncOpInic  = AVC.ParUser2[CubaAtual].VIncPadrao[TipoInc];
			 AVC.Ccont[CubaAtual].TIncOp     = AVC.ParUser2[CubaAtual].DurIncPadrao[TipoInc];
			 PMsgParam = ScoreGetStr(STR_ATIVA);
			 switch (TipoInc)
			 {
 			   case 0:
			 	 PTipoInc = "TIPO_1";
			   case 1:
			 	 PTipoInc = "TIPO_2";
			   case 2:
			 	 PTipoInc = "TIPO_3";
			   case 3:
			 	 PTipoInc = "TIPO_4";
			   case 4:
			 	 PTipoInc = "TIPO_5";
			   case 5:
			 	 PTipoInc = "TIPO_6";
			 }
			 sprintf(StrVInc,"%03.1f",AVC.Ccont[CubaAtual].IncOpInic * 1000);
			 sprintf(StrTInc,"%3d:%02d",AVC.Ccont[CubaAtual].TIncOp/60, AVC.Ccont[CubaAtual].TIncOp Mod 60);
			 break;
		case DESATIVAR:
			 AVC.Ccont[CubaAtual].HabIncOper = FALSO;
			 AVC.Ccont[CubaAtual].IncOper    = 0.0;
			 PMsgParam = ScoreGetStr(STR_DESATIVA);
			 PTipoInc  = STR_NULL;
			 strcpy(StrVInc, STR_NULL);
			 strcpy(StrTInc, STR_NULL);
			 break;
	  }
	  AVC.Ccont[CubaAtual].ContIncOper = -1;

	  /*-- Gera eventos de incremento --*/
	  GeraEvento(EVENTO_INC_OPERACAO, CubaAtual, -1, NomeOper(atoi(Operador)),
				 StrTInc, PTipoInc, StrVInc, PMsgParam);

	  if (AVL.HabLogOper)
		GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, ScoreGetStr(LOG_INC_OPE),
				   NomeOper(atoi(Operador)), StrTInc, StrVInc, PMsgParam);
	}
	++IndCuba;
  }
  LiberaSemaf(SEMAF_AVC);
  AlteracaoTabela(TABELA_EST_AVC);

}

/*
-------------------------------------------------------------------------------
	ValidaDurInc - Validar a duracao do incremento e converte-la do padrao
				   HH:MM para minutos.
-------------------------------------------------------------------------------
*/
int ValidaDurInc(char *Duracao, int *Tempo)
{
  int	IndCuba;
  char	Buffer[10];
  char	*PBuf;
  int	Valor;
  int	CubaAtual;

  memset(Buffer, NUL, sizeof(Buffer));
  memcpy(Buffer, Duracao, strlen(Duracao));
  PBuf = strtok(Buffer,":.-");
  Valor  = 0;
  /*-- Pega a hora do incremento --*/
  if (PBuf ne NULL)
  {
	Valor = atoi(PBuf) ;
	if (Valor < 0)
	  return(FALSO);
	*Tempo = Valor * 60;
	/*-- Pega o minuto do incremento --*/
	PBuf = strtok(NULL,":.-");
	if (PBuf ne NULL)
	{
	  Valor = atoi(PBuf);
	  /*-- Verifica validade do minuto do incremento --*/
	  if ((Valor < 0) or (Valor > 59))
		return(FALSO);
	  *Tempo += Valor;  
	}
  }
  else
	return(FALSO);

  IndCuba = 0;
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	if (CubaAtual ne -1)
	{
	  if (*Tempo > AVC.Param[CubaAtual].TMaxIncOper)
		return(FALSO);
	}
	++IndCuba;
  }

  return(VERDADEIRO);
}
