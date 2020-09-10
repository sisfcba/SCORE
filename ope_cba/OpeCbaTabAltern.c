/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALAS 120 KA

	ARQUIVO		: OpeCbaTabAltern.c

	CONTEUDO	: Ativa/desativa tabela alternativa de ea.

	AUTOR		: Alexandre Bandeira

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 1.0		  -		  DATA  : 20/12/2006

	HISTORICO DAS EDICOES

$Id: OpeCbaTabAltern.c,v 1.1.2.1 2015/10/27 16:52:30 clage Exp $

$Log: OpeCbaTabAltern.c,v $
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

#define NUM_PARAM						5

#define MSG_TAB_ALTER_ATIVADA			"Tabela alternativa ativada"
#define MSG_TAB_ALTER_DESATIVADA		"Tabela alternativa desativada"
#define MSG_ACAO_OPCAO_INVALIDA			"Acao,Opcao invalida"
#define MSG_TEMPO_INVALIDO				"Tempo invalido, 1->Tempo<-99"

#define	ATIVAR_ALTERN					0
#define	DESATIVAR_ALTERN				1
#define	TEMPO_ALTERN					2
#define	EA_ALTERN						3

/*
-------------------------------------------------------------------------------
							Prototipos
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[]);
int  ConsArgs(int argc, char *argv[], int *Acao, int *Opcao, int *Tempo, char *PMsg);

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
  int	Opcao;
  int	Tempo;
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
	if (ConsArgs(argc, argv, &Acao, &Opcao, &Tempo, Msg) eq VERDADEIRO) 
	{
	  AtivaTabAltern(Acao, Opcao, Tempo, argv, Msg);
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
int ConsArgs(int argc, char *argv[], int *Acao, int *Opcao, int *Tempo, char *PMsg)
{
  char aux[30];
  if(argc ne NUM_PARAM)
  {
	sprintf(PMsg, ScoreGetStr(SCORE_MSG_210));
	return(FALSO);
  }
  /*-- Le arquivo de filtro de cubas --*/
  if(LeFiltroCubas(argv[1], &filtro))
  {
    sprintf(PMsg, ScoreGetStr(SCORE_ERR_2),My_name,COD_ERRO_6, argv[1]);
	return(FALSO);
  }
  if (filtro.Par.Total eq 0)
  {
    strcpy(PMsg, ScoreGetStr(SCORE_MSG_356));
	return(FALSO);
  }
  if(strlen(argv[2])>1)
  {
	strcpy(aux,argv[2]);
	aux[1]=0x00;
    *Acao = atoi(aux);
	if(*Acao == ATIVAR_ALTERN ||
	   *Acao == DESATIVAR_ALTERN)
	{
	  strcpy(aux,argv[2]);
	  memmove(aux,&aux[2],sizeof(aux)-2);
      *Opcao = atoi(aux);
	  if(*Opcao != TEMPO_ALTERN &&
	     *Opcao != EA_ALTERN)
	  {		
    	strcpy(PMsg, MSG_ACAO_OPCAO_INVALIDA);
		return(FALSO);
	  }	 		
	}
	else
    {		
      strcpy(PMsg, MSG_ACAO_OPCAO_INVALIDA);
	  return(FALSO);
    }	 		
	if(*Acao == ATIVAR_ALTERN && *Opcao == TEMPO_ALTERN)
	{
      *Tempo = atoi(argv[3]);
	  if(*Tempo<1 || *Tempo>99)
	  {
        strcpy(PMsg, MSG_TEMPO_INVALIDO);
	    return(FALSO);
	  }	
	}
  }
  else
  {
    *Acao = atoi(argv[2]);
	if(*Acao != DESATIVAR_ALTERN)
    {		
      strcpy(PMsg, MSG_ACAO_OPCAO_INVALIDA);
	  return(FALSO);
    }	 		
  }
  return( VERDADEIRO );
}

/*
-------------------------------------------------------------------------------
AtivaTabAltern - Ativa ou desativa tabela alternativa para cubas dadas
-------------------------------------------------------------------------------
*/
void AtivaTabAltern(int Acao, int Opcao, int Tempo, char *argv[], char *PMsg)
{
  int	IndCuba;
  int	CubaAtual;
  int	Cuba;
  char	Operador[9];
  char	aux[9];

  AlocaSemaf(SEMAF_AVC);

  /*-- Faz loop de cubas --*/
  IndCuba = 0;
  strcpy(Operador, argv[4]);
  while(IndCuba < filtro.Par.Total)
  {
	Cuba = filtro.Par.IndCuba[IndCuba];    
	CubaAtual = filtro.Par.NumCuba[IndCuba];    
	if(Cuba ne -1)
	{ 
	  switch(Acao)
	  {
		case ATIVAR_ALTERN:
		  if(Opcao == TEMPO_ALTERN)
		  { 	
	        EST_AVC(Cuba).TipoTabEaAltern = 0;
		    AVC.Ea[Cuba].DurTabEaAltern = Tempo*60*60;
		    AVC.Ea[Cuba].IniTabEaAltern = time(NULL);
		    sprintf(aux,"%d",Tempo);
		    if(AVL.HabLogOper)
		      GeraEvento(LOG_OPER_CUBA, Cuba, -1, "TabAlter",
				 	     NomeOper(atoi(Operador)), "Ativada", "Tempo", aux);
	      }
		  else
		  {
	        EST_AVC(Cuba).TipoTabEaAltern = 1;
		    AVC.Ea[Cuba].DurTabEaAltern = 0;
			if(AVL.HabLogOper)
			  GeraEvento(LOG_OPER_CUBA, Cuba, -1, "TabAlter",
				 	     NomeOper(atoi(Operador)), "Ativada", "Ea", "--------");
	      }
	      EST_AVC(Cuba).AtivaTabEaAltern = VERDADEIRO;
		  strcpy(PMsg, MSG_TAB_ALTER_ATIVADA);
		  break;
		case DESATIVAR_ALTERN:
	      EST_AVC(Cuba).AtivaTabEaAltern = FALSO;
          EST_AVC(Cuba).TipoTabEaAltern = 0;
		  AVC.Ea[Cuba].DurTabEaAltern = 0;
	      AVC.Ea[Cuba].IniTabEaAltern = 0;
		  strcpy(PMsg, MSG_TAB_ALTER_DESATIVADA);
		  break;
	  }
	}
	++IndCuba;
  }
  AlteracaoTabela(TABELA_EST_AVC);
  LiberaSemaf(SEMAF_AVC);
}
