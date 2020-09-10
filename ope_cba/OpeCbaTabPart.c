/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALAS 120 KA

	ARQUIVO		: OpeCbaTabPart.c

	CONTEUDO	: Ativa/desativa tabela de partida de cubas.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 1.0		  -		  DATA  : 13/03/2003

	HISTORICO DAS EDICOES

$Id: OpeCbaTabPart.c,v 1.1.2.1 2015/10/27 16:52:30 clage Exp $

$Log: OpeCbaTabPart.c,v $
Revision 1.1.2.1  2015/10/27 16:52:30  clage
Entrega dos fontes dos programas de operacao do Score para a CBA


******************************************************************************/


#define PROGRAMA_PRINCIPAL

/*
-------------------------------------------------------------------------------
							Includes
-------------------------------------------------------------------------------
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
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

#define NUM_PARAM						4

#define MSG_TAB_PART_ATIVADA			"Tabela de partida ativada"
#define MSG_TAB_PART_DESATIVADA			"Tabela de partida desativada"
#define MSG_ACAO_NAO_SEL				"Acao nao selecionada"

/*
-------------------------------------------------------------------------------
							Prototipos
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[]);
int  ConsArgs(int argc, char *argv[], int *Acao, char *PMsg);

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
void main( int argc, char *argv[] )
{
  int	Acao;
  char  Msg[80];
  pid_t PidPai;

  /*-- Aguarda sinal do modulo AtivaOperacao --*/
  PidPai = Receive(0, NULL, 0);

  /*-- Pega segmento comum da base de dados --*/
  if (PegaComum (&Comum))
	sprintf(Msg, ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_0 );
  else
  {
	/*-- Consiste argumentos recebidos retornando mensagem de erro --*/
	if (ConsArgs(argc, argv, &Acao, Msg) eq VERDADEIRO) 
	{
	  AtivaTabPartida(Acao, argv, Msg);
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
  ConsArgs - Consiste os argumentos passados para a opcao de operacao
-------------------------------------------------------------------------------
*/
int ConsArgs(int argc, char *argv[], int *Acao, char *PMsg)
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
  *Acao = atoi(argv[2]);
  if ((*Acao ne ATIVAR) and (*Acao ne DESATIVAR))
  {
	strcpy(PMsg, MSG_ACAO_NAO_SEL);
	return(FALSO);
  }

  return( VERDADEIRO );
}

/*
-------------------------------------------------------------------------------
AtivaTabPartida - Ativa ou desativa tabela de partida para cubas dadas
-------------------------------------------------------------------------------
*/
void AtivaTabPartida(int Acao, char *argv[], char *PMsg)
{
  int	IndCuba;
  int	CubaAtual;
  int	Cuba;
  char	Operador[9];
  char	*PMsgParam;
  char  MsgTab[9];
  char  MsgPasso[9];


  AlocaSemaf(SEMAF_AVC);

  /*-- Faz loop de cubas --*/
  strcpy(PMsg, "Acao nao executada!");
  IndCuba = 0;
  strcpy(Operador, argv[3]);
  while(IndCuba < filtro.Par.Total)
  {
	Cuba = filtro.Par.IndCuba[IndCuba];    
	CubaAtual	  = filtro.Par.NumCuba[IndCuba];    
	if (Cuba ne -1)
	{ 
	  switch(Acao)
	  {
		case  ATIVAR:
		  if (AVC.ParUser1[Cuba].HabTabPartida)
		  { /* Trata permitido para esta cuba */
		    if (EST_AVC(Cuba).Est.TrataTabPartida eq FALSO)
			{ /* Ainda nao esta ativa */
			    /* Ativa tabela */
				EST_AVC(Cuba).Est.TrataTabPartida=VERDADEIRO;
				AVC.User1[Cuba].PassoAtualTPartida=0; /* inicializa primeiro passo */
				GeraEvento(EV_TAB_PARTIDA,Cuba,-1,"Inicio",AVC.ParUser1[Cuba].NumTabPartida,"Operacao",
	 	 			AVC.User1[Cuba].PassoAtualTPartida);
				sprintf(MsgTab,"%02d",AVC.ParUser1[Cuba].NumTabPartida);
				strcpy(MsgPasso,"01");
				PMsgParam = ScoreGetStr(STR_ATIVA);
				if (AVL.HabLogOper)
				  GeraEvento(LOG_OPER_CUBA, Cuba, -1, ScoreGetStr(SCORE_MSG_448),
					 NomeOper(atoi(Operador)), PMsgParam, MsgTab, MsgPasso);
				strcpy(PMsg, MSG_TAB_PART_ATIVADA);
			}
		  }
		  else
		  {
			sprintf(PMsg, "Cuba %d nao habilitada",CubaAtual);
			goto fim;
		  }
		  break;
		case  DESATIVAR:
		  if (AVC.ParUser1[Cuba].HabTabPartida)
		  { /* Trata permitido para esta cuba */
			PMsgParam = ScoreGetStr(STR_DESATIVA);
			sprintf(MsgTab,"%02d",AVC.ParUser1[Cuba].NumTabPartida);
			sprintf(MsgPasso,"%d",(AVC.User1[Cuba].PassoAtualTPartida eq 255 ? -1 : AVC.User1[Cuba].PassoAtualTPartida+1));
			EST_AVC(Cuba).Est.TrataTabPartida=FALSO;
			if (AVL.HabLogOper)
			  GeraEvento(LOG_OPER_CUBA, Cuba, -1, ScoreGetStr(SCORE_MSG_448),
				    NomeOper(atoi(Operador)), PMsgParam, MsgTab, MsgPasso);
			strcpy(PMsg, MSG_TAB_PART_DESATIVADA);
		  }
		  else
		  {
			sprintf(PMsg, "Cuba %d nao habilitada",CubaAtual);
			goto fim;
		  }
		  break;
	  }
	}
	++IndCuba;
  }

fim:

  AlteracaoTabela(TABELA_EST_AVC);
  LiberaSemaf(SEMAF_AVC);
}
