/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: OpeCbaAtivBoost.c

	CONTEUDO	: Ativa/desativa booster de corrente

	AUTOR		: Carlos Cezar Silva Lage

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 1.0		  -		  DATA  : 03/06/02

	HISTORICO DAS EDICOES

$Id: OpeCbaAtivBoost.c,v 1.1.2.1 2015/10/27 16:52:29 clage Exp $

$Log: OpeCbaAtivBoost.c,v $
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

#define NUM_PARAM						4

/*-- Acoes de qubrada preventiva --*/
#define	ATIVA_BOOSTER					1
#define DESAT_BOOSTER					2

/*-- Mensagens de ajuste --*/
#define MSG_ACAO_NAO_SEL				"Acao nao selecionada"

#define MSG_BOOSTER_ATIVADO				"Booster de corrente ativado"
#define MSG_BOOSTER_DESAT      	    	"Booster de corrente desativado"
#define LOG_BOOSTER						"BoostCor"
#define STR_ATIVADO						"Ativa"
#define STR_DESATIVADO					"Desativa"


/*
-------------------------------------------------------------------------------
							Prototipos
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[]);
int  ConsArgs(int argc, char *argv[], int *Acao, char *PMsg);
void BoosterCorrente(int Acao, char *argv[], char *PMsg);

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
	  BoosterCorrente(Acao, argv, Msg);
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
  if ((*Acao ne ATIVA_BOOSTER) and (*Acao ne DESAT_BOOSTER))
  {
	strcpy(PMsg, MSG_ACAO_NAO_SEL);
	return(FALSO);
  }

  return( VERDADEIRO );
}

/*
-------------------------------------------------------------------------------
BoosterCorrente - Inibe ajuste de camisa pelo tempo determinado pelo operador
-------------------------------------------------------------------------------
*/
void BoosterCorrente(int Acao, char *argv[], char *PMsg)
{
  int	IndCuba;
  int	CubaAtual;
  int	Cuba;
  char	Operador[9];

  AlocaSemaf(SEMAF_AVC);

  /*-- Faz loop de cubas --*/
  IndCuba = 0;
  strcpy(Operador, argv[3]);
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	Cuba	  = filtro.Par.NumCuba[IndCuba];    
	if (CubaAtual ne -1)
	{
	  switch(Acao)
	  {
		case  ATIVA_BOOSTER:
			  if (EST_AVC(CubaAtual).Est.BoosterAtivo ne VERDADEIRO)
			  {
				/*-- Gera evento --*/
				EST_AVC(CubaAtual).Est.BoosterAtivo = VERDADEIRO;
				if (AVL.HabLogOper)
				  GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, LOG_BOOSTER,
							 STR_ATIVADO, NomeOper(atoi(Operador)), STR_TRACO, STR_TRACO);
			  }
			  break;
		case  DESAT_BOOSTER:
			  if (EST_AVC(CubaAtual).Est.BoosterAtivo ne FALSO)
			  {
				/*-- Gera evento --*/
				EST_AVC(CubaAtual).Est.BoosterAtivo = FALSO;
				if (AVL.HabLogOper)
				  GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, LOG_BOOSTER,
							 STR_DESATIVADO, NomeOper(atoi(Operador)), STR_TRACO, STR_TRACO);
			  }
			  break;
	  }
	}
	++IndCuba;
  }

  switch(Acao)
  {
	case  ATIVA_BOOSTER:
		  strcpy(PMsg, MSG_BOOSTER_ATIVADO);
		  break;
	case  DESAT_BOOSTER:
		  strcpy(PMsg, MSG_BOOSTER_DESAT);
		  break;
	default:
		  strcpy(PMsg, MSG_BOOSTER_DESAT);
		  break;
  }

  AlteracaoTabela(TABELA_EST_AVC);
  LiberaSemaf(SEMAF_AVC);
}
