/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: OpeCbaLampEa.c

	CONTEUDO	: Modulo de comando de operacao. Permite ao operador desligar
                  lampada de EA.

	AUTOR		: Junia Guerra

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 2.0		  -		  DATA  : 12/08/94

	HISTORICO DAS EDICOES

$Id: OpeCbaLampEa.c,v 1.1.2.1 2015/10/27 16:52:29 clage Exp $

$Log: OpeCbaLampEa.c,v $
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

#define NUM_PARAM		3	//2

/*
-------------------------------------------------------------------------------
							Prototipos
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[]);
int  ConsArgs(int argc, char *argv[], int *Comando, int *Disp, char *PMsg);
void ApagaLampadaEa(int Comando, int Disp);

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
  int	Comando;
  int	Disp;
  pid_t PidPai;

  /*-- Aguarda sinal do modulo AtivaOperacao --*/
  PidPai = Receive(0, NULL, 0);

  /*--- Pega segmento comum da base de dados ---*/
  if (PegaComum (&Comum))
	sprintf(Msg, ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_0 );
  else
  {
	/*-- Consiste argumentos recebidos retornando mensagem de erro --*/
	if (ConsArgs(argc, argv, &Comando, &Disp, Msg) eq VERDADEIRO) 
	{
	  ApagaLampadaEa(Comando,Disp);
	  strcpy(Msg, ScoreGetStr(SCORE_MSG_444));
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
int ConsArgs(int argc, char *argv[], int *Comando, int *Disp, char *PMsg)
{
  char Msg[80];
  char *p;

  if (argc ne NUM_PARAM)
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
  *Comando=-1;
  *Disp=-1;
  strcpy(Msg,argv[2]);
  p=strtok(Msg,",\0");
  if(p ne NULL)
  {
    *Comando=atoi(p);
    p=strtok(NULL,",\0");
    if(p ne NULL)
      *Disp=atoi(p);
  }
  if((*Comando < 0 or *Comando > 1) or (*Disp < 2 or *Disp > 4))
  {
    strcpy(PMsg, ScoreGetStr(SCORE_MSG_413));
	return(FALSO);
  }
  return(VERDADEIRO);
}

/*
-------------------------------------------------------------------------------
  ApagaLampadaEa - Apaga sirene e lampada de efeito anodico
-------------------------------------------------------------------------------
*/
void ApagaLampadaEa(int Comando, int Disp)
{
  int	IndCuba;
  int	CubaAtual;
  int	Cuba;

  /*-- Faz loop de cubas --*/
  IndCuba = 0;
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	Cuba	  = filtro.Par.NumCuba[IndCuba];    

	if (CubaAtual ne (-1))
	{
	  if( Comando eq 0 ) // desliga
	  {
		switch( Disp ) // dispositivo
		{
		  case 3: // sirene
	    	/*-- Comanda desligamento da sirene --*/
	    	ComandaSirene(CubaAtual, DESLIGAR);
			break;
		  case 2: // lampada
	    	/*-- Comanda desligamento da lampada --*/
	    	ComandaLampEa(CubaAtual, DESLIGAR);
			break;
		  case 4: // sirene e lampada
	    	/*-- Comanda desligamento da sirene --*/
	    	ComandaSirene(CubaAtual, DESLIGAR);
	    	/*-- Comanda desligamento da lampada --*/
	    	ComandaLampEa(CubaAtual, DESLIGAR);
		    break;
		}
	  }
	  else // liga
	  {
		switch( Disp )  // dispositivo
		{
		  case 3: // sirene
	    	/*-- Comanda desligamento da sirene --*/
	    	ComandaSirene(CubaAtual, LIGAR);
			break;
		  case 2: // lampada
	    	/*-- Comanda desligamento da lampada --*/
	    	ComandaLampEa(CubaAtual, LIGAR);
			break;
		  case 4: // sirene e lampada
	    	/*-- Comanda desligamento da sirene --*/
	    	ComandaSirene(CubaAtual, LIGAR);
	    	/*-- Comanda desligamento da lampada --*/
	    	ComandaLampEa(CubaAtual, LIGAR);
		    break;
		}
	  }
	}
	++IndCuba;
  }
}
