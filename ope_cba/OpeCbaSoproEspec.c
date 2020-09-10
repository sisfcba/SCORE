/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 3.0

	PROJETO		: SCORE

	SISTEMA		: TODOS

	ARQUIVO		: OpeCbaSoproEspec.c

	CONTEUDO	: Desativa algoritmo de sopro especial

	AUTOR		: Carlos Cezar Silva Lage

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM

	VERSAO		: 1.0			-		DATA	:	29/06/03

	HISTORICO DAS EDICOES

$Id: OpeCbaSoproEspec.c,v 1.1.2.1 2015/10/27 16:52:30 clage Exp $

$Log: OpeCbaSoproEspec.c,v $
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

#define NUM_PARAM				3

#define LOG_SOPRO_ESPEC			"SoproEsp"

/*
-------------------------------------------------------------------------------
							Prototipos
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[]);
int  ConsArgs(int argc, char *argv[], char *PMsg);
void DesatSoproEspec(char *argv[]);

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
  pid_t PidPai;

  /*-- Aguarda sinal do modulo AtivaOperacao --*/
  PidPai = Receive(0, NULL, 0);

  /*--- Pega segmento comum da base de dados ---*/
  if (PegaComum (&Comum))
	sprintf(Msg, ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_0 );
  else
  {
	/*-- Consiste argumentos recebidos retornando mensagem de erro --*/
	if(ConsArgs(argc, argv, Msg) eq VERDADEIRO) 
	{
	  DesatSoproEspecial(argv);
	  strcpy(Msg,ScoreGetStr(SCORE_MSG_444));
	}
  }
  /*-- Envia mensagem liberando o modulo AtivaOperacao --*/
  Reply(PidPai, Msg, sizeof(Msg));
}

/*
-------------------------------------------------------------------------------
	ConsArgs - Consiste numero de argumentos passados para o comando e
			   critica numero da Cuba.
-------------------------------------------------------------------------------
*/
int ConsArgs(int argc, char *argv[], char *PMsg)
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
  return(VERDADEIRO);
}

/*
-------------------------------------------------------------------------------
  DesatSoproEspecial - Manda soprar
-------------------------------------------------------------------------------
*/
void DesatSoproEspecial(char *argv[])
{
  int	IndCuba;
  int	CubaAtual;
  char	Operador[9];

  /*-- Faz loop de cubas --*/
  strcpy(Operador,argv[2]);
  IndCuba = 0;
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	if(CubaAtual ne (-1))
	{
	  if (EST_AVC(CubaAtual).Est.OpeSoproEspec eq VERDADEIRO)
	  {
		EST_AVC(CubaAtual).Est.OpeSoproEspec = FALSO;
		if (AVL.HabLogOper)
		  GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, LOG_SOPRO_ESPEC, NomeOper(atoi(Operador)),
		  			 ScoreGetStr(SCORE_MSG_505), "--------", "--------");
	  }
	}
	++IndCuba;
  }
}