/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I-IV

	ARQUIVO		: OpeCbaSPassoTabInc.c

	CONTEUDO	: Programa para ligar/desligar a lampada de EA que compoe
                  uma das opcoes do ManutScore versao windows.

	AUTOR		: Robson Pierangeli Godinho

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 1.0		  -		  DATA  : 06/12/2002

	HISTORICO DAS EDICOES

$Id: OpeCbaSPassoTabInc.c,v 1.1.2.1 2015/10/27 16:52:30 clage Exp $

$Log: OpeCbaSPassoTabInc.c,v $
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

/*-- Acionamentos da Lampada --*/
#define LIGAR_LAMPADA			1
#define DESLIGAR_LAMPADA		2

/*-- Mensagens de erro --*/
#define LOG_SALTA				"SaltaPasso"
#define STR_INCR				"Incr."
#define STR_MSG					"Passo da Tabela de Incrementos das cubas Selecionadas descartado."


/*
-------------------------------------------------------------------------------
							Prototipos
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[]);
int  ConsArgs(int argc, char *argv[], char *PMsg);
void SaltaPassoTabelaInc(char *argv[], char *PMsg);

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
	if (ConsArgs(argc, argv, Msg) eq VERDADEIRO) 
	{
	  SaltaPassoTabelaInc(argv, Msg);
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
int ConsArgs(int argc, char *argv[], char *PMsg)
{
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

  return(VERDADEIRO);
}

/*
-------------------------------------------------------------------------------
  AcionaLampadaEa - Aciona lampada de efeito anodico
-------------------------------------------------------------------------------
*/
void SaltaPassoTabelaInc(char *argv[], char *PMsg)
{
  int	IndCuba;
  int	CubaAtual;
  char	Operador[9];
  int passo, tab_ope;

  /*-- Faz loop de cubas --*/
  IndCuba = 0;
  strcpy(Operador, argv[2]);
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	if (CubaAtual ne (-1))
	{
      // pular o passo corrente da tabela de incrementos
	  if (EST_AVC(CubaAtual).TabOpeAtiva)
	  { /* -- Fim de passo de tabela de operacao -- */
		AVC.Ccont[CubaAtual].PassoTabOpe++;
		passo=AVC.Ccont[CubaAtual].PassoTabOpe;
		if (passo ne MAX_PASSOS_TAB_OPE)
		{
		  tab_ope=AVC.Param[CubaAtual].NumTabOpe;
		  if (PTabOpe->Tab[tab_ope].Passo[passo].TipoIncr ne -1)
		  {
			AVC.Ccont[CubaAtual].VSetPoint=
				PTabOpe->Tab[tab_ope].Passo[passo].VSetPoint;
			AVC.Ccont[CubaAtual].TipoIncOp  =
				PTabOpe->Tab[tab_ope].Passo[passo].TipoIncr;
			AVC.Ccont[CubaAtual].IncOpInic  =
				PTabOpe->Tab[tab_ope].Passo[passo].VIncr;
			AVC.Ccont[CubaAtual].TIncOp     =
				PTabOpe->Tab[tab_ope].Passo[passo].Tempo; /*-- min --*/
			AVC.Ccont[CubaAtual].HabIncOper = VERDADEIRO;
			AVC.Ccont[CubaAtual].ContIncOper=0;
			AVC.Ccont[CubaAtual].IncOper=AVC.Ccont[CubaAtual].IncOpInic;
		  }
		  else
		  { /* -- ultimo passo -> fim da tabela -- */
			EST_AVC(CubaAtual).TabOpeAtiva=FALSO;
			AVC.Ccont[CubaAtual].VSetPoint=AVC.Param[CubaAtual].VSetPointCnf;
			AVC.Ccont[CubaAtual].IncOper=0.0;
			AVC.Ccont[CubaAtual].ContIncOper=-1;
			AVC.Ccont[CubaAtual].HabIncOper=FALSO;
		  }
		}
		else
		{ /* -- ultimo passo -> fim da tabela -- */
		  EST_AVC(CubaAtual).TabOpeAtiva=FALSO;
		  AVC.Ccont[CubaAtual].VSetPoint=AVC.Param[CubaAtual].VSetPointCnf;
		  AVC.Ccont[CubaAtual].IncOper=0.0;
		  AVC.Ccont[CubaAtual].ContIncOper=-1;
		  AVC.Ccont[CubaAtual].HabIncOper=FALSO;
		}
	  }
	  if (AVL.HabLogOper)
		GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, LOG_SALTA,
						STR_INCR, NomeOper(atoi(Operador)), STR_TRACO, STR_TRACO);
	}
	++IndCuba;
  }
  strcpy(PMsg, STR_MSG);
}
