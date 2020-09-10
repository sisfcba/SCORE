/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: OpeCbaIniQPrev.c

	CONTEUDO	: Inibe/cancela a quebrada preventiva. 

	AUTOR		: Carlos Cezar Silva Lage

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 1.0		  -		  DATA  : 17/04/98

	HISTORICO DAS EDICOES

$Id: OpeCbaIniQPrev.c,v 1.1.2.1 2015/10/27 16:52:29 clage Exp $

$Log: OpeCbaIniQPrev.c,v $
Revision 1.1.2.1  2015/10/27 16:52:29  clage
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

#define NUM_PARAM						5
#define	MAX_TEMPO_QUEB_PREV				48	/*-- horas --*/

#define MSG_QPREV_POR_TEMPO				"Quebrada preventiva inibida por tempo"
#define MSG_QPREV_PROX_EA				"Quebrada preventiva inibida ate proximo EA"
#define MSG_QPREV_ATIVADA				"Quebrada preventiva ativada"
#define MSG_QPREV_DESATIVADA			"Quebrada preventiva desativada"
#define MSG_QPREV_CUBA					"Cuba %d em quebrada preventiva"
#define MSG_ACAO_QUEB_NAO_SEL			"Acao de quebrada nao selecionada"
#define MSG_TEMPO_INV_HOR				"Tempo invalido (min=%d max=%d horas)"

/*
-------------------------------------------------------------------------------
							Prototipos
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[]);
int  ConsArgs(int argc, char *argv[],int *Tempo, int *Acao, char *PMsg);
void InibeQuebPrev(int Tempo, int Acao, char *argv[], char *PMsg);

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
  int	TempoInibe;
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
	if (ConsArgs(argc, argv, &TempoInibe, &Acao, Msg) eq VERDADEIRO) 
	{
	  InibeQuebPrev(TempoInibe, Acao, argv, Msg);
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
int ConsArgs(int argc, char *argv[], int *Tempo, int *Acao, char *PMsg)
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
  if ((*Acao ne QPREV_PROX_EA) and (*Acao ne QPREV_POR_TEMPO) and
	  (*Acao ne ATIVA_QPREV) and (*Acao ne DESATIVA_QPREV))
  {
	strcpy(PMsg, MSG_ACAO_QUEB_NAO_SEL);
	return(FALSO);
  }
  /*-- Consiste o tempo --*/
  *Tempo = atoi(argv[3]);
  if ((*Tempo < 0) or (*Tempo > MAX_TEMPO_QUEB_PREV))
  {
	sprintf(PMsg, MSG_TEMPO_INV_HOR, 0, MAX_TEMPO_QUEB_PREV);
	return(FALSO);
  }
  /*-- Converte para minutos --*/
  *Tempo = *Tempo * 60;

  return( VERDADEIRO );
}

/*
-------------------------------------------------------------------------------
InibeQuebPrev - Inibe ajuste de camisa pelo tempo determinado pelo operador
-------------------------------------------------------------------------------
*/
void InibeQuebPrev(int Tempo, int Acao, char *argv[], char *PMsg)
{
  int	IndCuba;
  int	CubaAtual;
  int	Cuba;
  char	Operador[9];


  AlocaSemaf(SEMAF_AVC);

  /*-- Faz loop de cubas --*/
  IndCuba = 0;
  strcpy(Operador, argv[4]);
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	Cuba	  = filtro.Par.NumCuba[IndCuba];    
	if (CubaAtual ne -1)
	{ /* Cuba, acao,  tempo (0) e operador (-1=traco) */
	  MudaQuebPrevCuba(CubaAtual,Acao,Tempo,atoi(Operador));
	}
	++IndCuba;
  }

  switch(Acao)
  {
	case  QPREV_POR_TEMPO:
		  strcpy(PMsg, MSG_QPREV_POR_TEMPO);
		  break;
	case  QPREV_PROX_EA:
		  strcpy(PMsg, MSG_QPREV_PROX_EA);
		  break;
	case  ATIVA_QPREV:
		  strcpy(PMsg, MSG_QPREV_ATIVADA);
		  break;
	case  DESATIVA_QPREV:
		  strcpy(PMsg, MSG_QPREV_DESATIVADA);
		  break;
  }

  AlteracaoTabela(TABELA_EST_AVC);
  LiberaSemaf(SEMAF_AVC);
}
