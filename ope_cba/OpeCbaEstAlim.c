/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II

	ARQUIVO		: OpeCbaEstAlim.c

	CONTEUDO	: Modulo de comando de operacao. Permite ao operador mudar o 
                  estado de alimentacao da cuba.

	AUTOR		: Carlos Cezar Silva Lage

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0		  -		  DATA  : 17/01/96


$Id: OpeCbaEstAlim.c,v 1.1.2.1 2015/10/27 16:52:29 clage Exp $

$Log: OpeCbaEstAlim.c,v $
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
#include <AlimentCBA.h>
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

#define NUM_PARAM				5

/*-- Botoes da alimentacao --*/
#define ALIMENT_AUTOMATICA		1
#define ALIMENT_MANUAL			2
#define ALIMENT_CHECK			3
#define ALIMENT_SUSPENSA		4
#define ALIMENT_BASEFEED		5
#define ALIMENT_OVERFEED		6

/*-- Mensagem de duracao invalida --*/
#define MSG_DUR_ALIM_INV		"Duracao de alimentacao suspensa invalida"
#define MSG_ALIM_ALT			"Estado de alimentacao alterado"
#define MSG_ALIM_NAO_SEL		"Estado de alimentacao nao selecionado"

/*
-------------------------------------------------------------------------------
							Prototipos
-------------------------------------------------------------------------------
*/
void main ( int argc, char *argv[] );
char *NomeEstado(int Estado);
int  ConsArgs(int argc, char *argv[], int *Estado, long *Tempo, char *PMsg);
void MudaEstado(int Estado, long Tempo, char *argv[]);
int  ValidaDurAlim(char *Duracao, long *Tempo);

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
  long  Tempo;
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
	if (ConsArgs(argc, argv, &Estado, &Tempo, Msg) eq VERDADEIRO) 
	{
	  MudaEstado(Estado, Tempo, argv);
	  strcpy(Msg, MSG_ALIM_ALT);
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
int ConsArgs(int argc, char *argv[], int *Estado, long *Tempo, char *PMsg)
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
  if( filtro.Par.Total eq 0 )
  {
    strcpy(PMsg, ScoreGetStr(SCORE_MSG_356));
	return(FALSO);
  }

  *Estado = atoi(argv[2]);
  /*-- Critica os botoes de alimentacao da cuba --*/
  if ((*Estado ne ALIMENT_AUTOMATICA) and (*Estado ne ALIMENT_MANUAL) and
	  (*Estado ne ALIMENT_CHECK) and (*Estado ne ALIMENT_SUSPENSA) and 
	  (*Estado ne ALIMENT_BASEFEED) and (*Estado ne ALIMENT_OVERFEED))
  {
	strcpy(PMsg, MSG_ALIM_NAO_SEL);
	return(FALSO);
  }

  /*-- Valida a duracao do incremento de operacao. --*/
  if (ValidaDurAlim(argv[3], Tempo) eq FALSO)
  {
	strcpy(PMsg, MSG_DUR_ALIM_INV);
	return(FALSO);
  }

  return(VERDADEIRO);
}

/*
-------------------------------------------------------------------------------
  MudaEstado - Muda estado da Cuba e gera evento de mudanca de estado.
-------------------------------------------------------------------------------
*/
void MudaEstado(int Estado, long Tempo, char *argv[])
{
  int  IndCuba;
  int  CubaAtual;
  int  Cuba;
  char Operador[9];
  char PMsgParam[9];
//  char PMsgParamAnt[9];

  /*-- Aloca semaforos --*/
  AlocaSemaf(SEMAF_AVC);

  /*-- Faz loop das cubas --*/
  IndCuba = 0;
  strcpy(Operador, argv[4]);
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	Cuba	  = filtro.Par.NumCuba[IndCuba];    
	if (CubaAtual ne (-1))
	{
	  switch(Estado)
	  {
		case ALIMENT_AUTOMATICA:
			 EST_AVC(CubaAtual).Est.ManualAlimRem = FALSO;
			 EST_AVC(CubaAtual).Est.AlimSuspensa = FALSO;
			 if (AVL.HabLogOper)
		  		GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, ScoreGetStr(LOG_EST_CUBA), NomeOper(atoi(Operador)),
					 "Manual", "Auto", STR_TRACO);
			 break;
		case ALIMENT_MANUAL:
			 EST_AVC(CubaAtual).Est.ManualAlimRem = VERDADEIRO;
			 if(AVC.ParUser1[CubaAtual].HabilitaPF eq VERDADEIRO)		
  			   MudaEstadoAlim(CubaAtual, EST_ALIM_EXCECAO, MUDA_OPER);
			 if (AVL.HabLogOper)
		  		GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, ScoreGetStr(LOG_EST_CUBA), NomeOper(atoi(Operador)),
					 "Auto", "Manual", STR_TRACO);
			 break;
		case ALIMENT_CHECK:
			 EST_AVC(CubaAtual).Est.AlimCheck = VERDADEIRO;
			 if(AVC.ParUser1[CubaAtual].HabilitaPF eq VERDADEIRO)		
			   MudaEstadoAlim(CubaAtual, EST_ALIM_EXCECAO, MUDA_OPER);
	  		 sprintf(PMsgParam," %d ",  AVC.User2[Cuba].EstadoPFCBA);
			 if (AVL.HabLogOper)
		  		GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, ScoreGetStr(LOG_EST_CUBA), NomeOper(atoi(Operador)),
					 PMsgParam, "Check", STR_TRACO);
			 break;
		case ALIMENT_SUSPENSA:
			 EST_AVC(CubaAtual).Est.AlimSuspensa = VERDADEIRO;
			 AVC.User1[CubaAtual].TempoSuspende = Tempo;
			 if(AVC.ParUser1[CubaAtual].HabilitaPF eq VERDADEIRO)
			   MudaEstadoAlim(CubaAtual, EST_ALIM_SUSPENSA, MUDA_OPER);
			 MontaHoraMin(Tempo/60, PMsgParam, "%03d:%02d");
//	  		 sprintf(PMsgParam," %d ",  AVC.User2[Cuba].EstadoPFCBA);
			 if (AVL.HabLogOper)
		  		GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, ScoreGetStr(LOG_EST_CUBA), NomeOper(atoi(Operador)),
					 PMsgParam, "Suspensa", STR_TRACO);
			 break;
		case ALIMENT_BASEFEED: 
			 EST_AVC(CubaAtual).Est.ForcaEstAlim = VERDADEIRO;
			 AVC.User1[CubaAtual].TempoSuspende = Tempo;
			 AVC.User3[CubaAtual].EstForcaAlim = 2;
			 MontaHoraMin(Tempo/60, PMsgParam, "%03d:%02d");
//	  		 sprintf(PMsgParam," %d ",  AVC.User2[Cuba].EstadoPFCBA);
			 if (AVL.HabLogOper)
		  		GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, ScoreGetStr(LOG_EST_CUBA), NomeOper(atoi(Operador)),
					 PMsgParam, "Basefeed", STR_TRACO);
			 break;
		case ALIMENT_OVERFEED: 
			 EST_AVC(CubaAtual).Est.ForcaEstAlim = VERDADEIRO;
			 AVC.User1[CubaAtual].TempoSuspende = Tempo;
			 AVC.User3[CubaAtual].EstForcaAlim = 3;
			 MontaHoraMin(Tempo/60, PMsgParam, "%03d:%02d");
//	  		 sprintf(PMsgParam," %d ",  AVC.User2[Cuba].EstadoPFCBA);
			 if (AVL.HabLogOper)
		  		GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, ScoreGetStr(LOG_EST_CUBA), NomeOper(atoi(Operador)),
					 PMsgParam, "Overfeed", STR_TRACO);
			 break;
	  }
	}
	++IndCuba;
  }
  LiberaSemaf(SEMAF_AVC);
  AlteracaoTabela(TABELA_EST_AVC);
  AlteracaoTabela(TABELA_AVC);
}



/*
-------------------------------------------------------------------------------
	ValidaDurAlim - Validar a duracao da alimentacao suspensa e converte-la
			do padrao HH:MM para segundos.
-------------------------------------------------------------------------------
*/
int ValidaDurAlim(char *Duracao, long *Tempo)
{
  char	Buffer[10];
  char	*PBuf;
  char  *errostr;
  int	Valor;

  memset(Buffer, NUL, sizeof(Buffer));
  memcpy(Buffer, Duracao, strlen(Duracao));
  PBuf = strtok(Buffer,":.-");
  Valor  = 0;
  /*-- Pega a hora do alimentacao --*/
  if (PBuf ne NULL)
  {
	Valor = (int) strtol(PBuf,&errostr,10) ;
	if ((*errostr ne NULL) or (Valor < 0))
	  return(FALSO);
	*Tempo = Valor * 3600L;
	/*-- Pega o minuto do alimentacao --*/
	PBuf = strtok(NULL,":.-");
	if (PBuf ne NULL)
	{
	  Valor = (int) strtol(PBuf,&errostr,10);
	  /*-- Verifica validade do minuto da alimentacao --*/
	  if ((Valor < 0) or (Valor > 59) or (*errostr ne NULL))
		return(FALSO);
	  *Tempo += Valor * 60L;  
	}
  }
  else
	return(FALSO);


  return(VERDADEIRO);
}

/* -- fim OpeEstAlimW.c -- */
