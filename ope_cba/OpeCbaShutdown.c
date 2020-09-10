/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: OpeCbaShutdown.c

	CONTEUDO	: Modulo de comando de operacao. Botao de desligamento de
				  emergencia da Sala.

	AUTOR		: Marco Lopes

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 2.0		  -		  DATA  : 10/01/19

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

/*-- Numero de parametros --*/
#define NUM_PARAM		3

/*-- Definicao dos tags dos botoes --*/
#define PARAMETRO_DESLIGAR			"1"

/*
-------------------------------------------------------------------------------
								Prototipos
-------------------------------------------------------------------------------
*/

void main(int argc, char *argv[]);
int  ConsArgs(int argc, char *argv[], int *Acao, char *PMsg);
void TrataShutdown(int Acao, char *argv[]);

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
	/*-- Consiste argumentos recebidos retornando mensagem de erro --*/
	if (ConsArgs(argc, argv, &Acao, Msg) eq VERDADEIRO) 
	{
	  TrataShutdown(Acao, argv);
	  strcpy(Msg, "SINALIZACAO DE DESLIGAMENTO DE EMERGENCIA ENVIADO!");
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
int ConsArgs(int argc, char *argv[], int *Acao, char *PMsg)
{

  if (argc ne NUM_PARAM)
  {
	sprintf(PMsg, ScoreGetStr(SCORE_MSG_210));
	return(FALSO);
  }

  /*-- Valida acao de incremento --*/
  if (strstr(argv[1],PARAMETRO_DESLIGAR) ne NULL)
	*Acao = ATIVAR;
  else
  {
	sprintf(PMsg, ScoreGetStr(SCORE_MSG_210));
	return(FALSO);
  }	

  return(VERDADEIRO);
}

/*
-------------------------------------------------------------------------------
  TrataShutdown - Desliga a linha e gera evento.
-------------------------------------------------------------------------------
*/
void TrataShutdown(int Acao, char *argv[])
{

  int	IndCuba;
  char	Operador[9];

  /*-- Aloca semaforos --*/
  AlocaSemaf(SEMAF_AVC);

  /*-- Faz loop dos grupos --*/
  IndCuba = 0;
  strcpy(Operador, argv[2]);

  if(Acao eq ATIVAR)
  {
    /* Logica para desligar sala */
    GeraEvento(EV_DESLIGASALA,-1,-1,"EMERGENC",NomeOper(atoi(Operador)),
	  0, AVL.VLinhaInst, AVL.ICicContlMed);

    ComandaSaidaORem(0,LIGAR, 21, 100);
    ComandaSaidaORem(1,LIGAR, 21, 100);
  }

  LiberaSemaf(SEMAF_AVC);
  AlteracaoTabela(TABELA_EST_AVC);

}

