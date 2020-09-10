/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: OpeCbaTabOpe.c

	CONTEUDO	: Programa de operacao para ativar/desativar tabelas de
				  incremento de operacao

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 2.0		  -		  DATA  : 28/03/95

	HISTORICO DAS EDICOES

$Id: OpeCbaTabOpe.c,v 1.1.2.1 2015/10/27 16:52:30 clage Exp $

$Log: OpeCbaTabOpe.c,v $
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

#ifndef OPERACAO_WINDOWS
  /*-- Numero maximo de cubas a serem excluidas --*/
  #define MAX_EXC_CUBAS				15
#endif

/*-- Numero de parametros do comando --*/
#define NUM_PARAM					4

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
int  ValidaIncOper(char *PMsg);
void TrataIncOper(int Acao, char *PMsg, char *argv[]);

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
  char  Msg[80];
  pid_t PidPai;

  /*-- Aguarda sinal do modulo AtivaOperacao --*/
  PidPai = Receive(0, NULL, 0);

  /*--- Pega segmento comum da base de dados ---*/
  if (PegaComum(&Comum))
	sprintf(Msg, ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_0 );
  else
  {
	/*-- Consiste argumentos recebidos exibindo mensagem de erro --*/
	if (ConsArgs(argc, argv, &Acao, Msg) eq VERDADEIRO)
	  TrataIncOper(Acao, Msg, argv);

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
 int ConsArgs(int argc, char *argv[], int *Acao, char *PMsg)
 {
  int	IndCuba;
  int	Tag;
  int	CubaAtual;
  int	Cuba;

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
	*Acao = ATIVAR;
  else
  {
	if (Tag eq PARAMETRO_DESATIVAR)
	  *Acao = DESATIVAR;
	else
	{
	  strcpy(PMsg, ScoreGetStr(SCORE_MSG_393));
	  return(FALSO);
	}
  }

  /*-- Faz loop de cubas --*/
  IndCuba = 0;
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	Cuba	  = filtro.Par.NumCuba[IndCuba];    
	if (CubaAtual ne (-1))
	{
	  switch (*Acao)
	  {
		case ATIVAR:
	  	  if (EST_AVC(CubaAtual).EstadoCuba != CUBA_NORMAL)
	  	  {
			sprintf(PMsg, "CUBA %d nao esta em ESTADO NORMAL!",Cuba);
			return( FALSO );
	  	  }
			 if (AVC.Param[CubaAtual].HabTabOpe ne VERDADEIRO)
			 {
			   sprintf(PMsg, ScoreGetStr(SCORE_MSG_446), Cuba);
			   return(FALSO);
			 }
			 break;

		case DESATIVAR:
			 if (EST_AVC(CubaAtual).TabOpeAtiva ne VERDADEIRO)
			 {
			   sprintf(PMsg, ScoreGetStr(SCORE_MSG_447), Cuba);
			   return(FALSO);
			 }
			 break;
	  }
	}
	++IndCuba;
  }

  return(VERDADEIRO);
}

/*
-------------------------------------------------------------------------------
	TrataIncOper - Ativa / Desativa incremento de operacao das cubas
				   e gera evento.
-------------------------------------------------------------------------------
*/
 void TrataIncOper(int Acao, char *PMsg, char *argv[])
 {
  int	IndCuba;
  char  Operador[9];
  int	CubaAtual;
  int	Cuba;

  AlocaSemaf( SEMAF_AVC );

  /*-- Faz loop de cubas --*/
  IndCuba = 0;
  strcpy(Operador, argv[3]);
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	Cuba	  = filtro.Par.NumCuba[IndCuba];    
	if (CubaAtual ne (-1))
	{
	  AtivaTabIncCuba(CubaAtual, Acao, atoi(Operador));
	}
	++IndCuba;
  } /*-- for(Cuba ...) --*/

  AlteracaoTabela(TABELA_EST_AVC);
  AlteracaoTabela(TABELA_AVC);
  LiberaSemaf(SEMAF_AVC);

  strcpy(PMsg, ScoreGetStr(SCORE_MSG_444));
}

/*-- fim do arquivo OpeTabOpe.c --*/
