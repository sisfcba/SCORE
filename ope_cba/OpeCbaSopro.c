/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 3.0

	PROJETO		: SCORE

	SISTEMA		: TODOS

	ARQUIVO		: OpeCbaSopro.c

	CONTEUDO	: Aciona Sopro tempo indicado

	AUTOR		: Alexandre Bandeira

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM

	VERSAO		: 1.0			-		DATA	:	30/05/03

	HISTORICO DAS EDICOES

$Id: OpeCbaSopro.c,v 1.1.2.1 2015/10/27 16:52:30 clage Exp $

$Log: OpeCbaSopro.c,v $
Revision 1.1.2.1  2015/10/27 16:52:30  clage
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

#define NUM_PARAM		4

/*
-------------------------------------------------------------------------------
							Prototipos
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[]);
int  ConsArgs(int argc, char *argv[], int *tempo, char *PMsg);
void AtivaSopro(int tempo, char *argv[]);

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
  char  Msg[80];
  int	tempo;
  pid_t PidPai;

  /*-- Aguarda sinal do modulo AtivaOperacao --*/
  PidPai = Receive(0, NULL, 0);

  /*--- Pega segmento comum da base de dados ---*/
  if (PegaComum (&Comum))
	sprintf(Msg, ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_0 );
  else
  {
	/*-- Consiste argumentos recebidos retornando mensagem de erro --*/
	if(ConsArgs(argc, argv, &tempo, Msg) eq VERDADEIRO) 
	{
	  AtivaSopro(tempo,argv);
	  strcpy(Msg,ScoreGetStr(SCORE_MSG_444));
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
	ConsArgs - Consiste numero de argumentos passados para o comando e
			   critica numero da Cuba.
-------------------------------------------------------------------------------
*/
int ConsArgs(int argc, char *argv[], int *tempo, char *PMsg)
{

  if(argc ne NUM_PARAM)
  {
	sprintf(PMsg, ScoreGetStr(SCORE_MSG_210));
	return( FALSO );
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
  *tempo = atoi(argv[2]);
  return(VERDADEIRO);
}

/*
-------------------------------------------------------------------------------
  AtivaSopro - Manda soprar
-------------------------------------------------------------------------------
*/
void AtivaSopro(int tempo, char *argv[])
{
  int	IndCuba;
  int	CubaAtual;
  int	Cuba;
  float	VCicCont, VInst, VAlvo;
  char	operador[10];

  /*-- Faz loop de cubas --*/
  strcpy(operador,argv[3]);
  IndCuba = 0;
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	Cuba	  = filtro.Par.NumCuba[IndCuba];    
	if(CubaAtual ne (-1))
	{
	  if(tempo ne 0)
	  {
		if(AVC.Abs[CubaAtual].BitSopro ne 255)
		{
		  VAlvo=AVC.Ccont[CubaAtual].VAlvo;
		  VInst=AVC.Cleit[CubaAtual].Vinst;
  		  /* Inicio Alteracao - Carlos - 23/06/99 */
  		  /* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
  		  VCicCont=AVC.CcontMcp[CubaAtual].RCicContlBruta*AVC.Ccont[CubaAtual].INominalCuba+
			 	   AVC.Param[CubaAtual].Bemf;
#else
  		  VCicCont=AVC.CcontMcp[CubaAtual].RCicContlBruta*AVL.INominal+
			 	   AVC.Param[CubaAtual].Bemf;
#endif
		  ComandaSaidaRem(CubaAtual,LIGAR,AVC.Abs[CubaAtual].BitSopro,tempo*BASE_TEMPO_REMOTA);
		  GeraEvento(SOPROU,CubaAtual,-1,NomeOper(atoi(operador)),STR_TRACO,VCicCont,VInst,VAlvo);
		}
	  }
	}
	++IndCuba;
  }
}
