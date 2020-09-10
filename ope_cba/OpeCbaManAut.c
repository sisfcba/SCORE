/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: OpeCbaManAut.c

	CONTEUDO	: Modulo de comando de operacao. Permite ao operador selecionar
				  operacao Automatico / Manual.

	AUTOR		: Junia Guerra

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 2.0		  -		  DATA  : 12/08/94

	HISTORICO DAS EDICOES

$Id: OpeCbaManAut.c,v 1.1.2.1 2015/10/27 16:52:29 clage Exp $

$Log: OpeCbaManAut.c,v $
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

/*-- Definicao dos botoes de modos --*/
#define PARAMETRO_MANUAL			1
#define PARAMETRO_AUTOMATICO		2

#define NUM_PARAM					4

/*
-------------------------------------------------------------------------------
							Prototipos
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[]);
int  ConsArgs(int argc, char *argv[], int *Chave, char *PMsg);
void SelecionaModoOperacao(int Chave, char *argv[]);
int  MudaCtrlAutManCuba(const int aCuba, const int aEstado, const int aOperador);

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
  int	Chave;
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
	if (ConsArgs(argc, argv, &Chave, Msg) eq VERDADEIRO) 
	{
	  SelecionaModoOperacao(Chave, argv);
	  strcpy(Msg, ScoreGetStr(MSG_MODO_OPER_ALT));
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
	ConsArgs - Consiste numero de argumentos passados para o comando,
			   critica numero da Cuba e modo de operacao.
-------------------------------------------------------------------------------
*/
int ConsArgs(int argc, char *argv[], int *Chave, char *PMsg)
{
  int Tag;

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

  Tag = atoi(argv[2]);
  if (Tag eq PARAMETRO_MANUAL)
  {
	*Chave = MANUAL;
  }
  else
  {
	if (Tag eq PARAMETRO_AUTOMATICO)
	{
	  *Chave = AUTOMATICO;
	}
	else
	{
	  strcpy(PMsg, ScoreGetStr(SCORE_MSG_419));
	  return(FALSO);
	}
  }

  return(VERDADEIRO);
}

/*
-------------------------------------------------------------------------------
SelecionaModoOperacao - Seleciona modo de operacao Automatico / Manual da cuba
						e gera evento de selecao de modo de operacao.
-------------------------------------------------------------------------------
*/
void SelecionaModoOperacao(int Chave, char *argv[])
{
  int	IndCuba;
  int		CubaAtual;
  int		Cuba;
  char		Operador[9];

  AlocaSemaf(SEMAF_AVC);

  /*-- Faz loop de cubas --*/
  IndCuba = 0;
  strcpy(Operador, argv[3]);
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	Cuba	  = filtro.Par.NumCuba[IndCuba];    
	if (CubaAtual ne (-1))
	{
	  MudaCtrlAutManCuba(CubaAtual,Chave,atoi(Operador));
	}
	++IndCuba;
  }

  AlteracaoTabela(TABELA_EST_AVC);
  LiberaSemaf(SEMAF_AVC);
}
/*
-------------------------------------------------------------------------------
  MudaCtrlAutManCuba - Muda estado de controle de anodo da Cuba para automatico
                   ou manual e gera evento de mudanca de estado.
  				   Retorna 0 se ok e <> 0 se erro.
-------------------------------------------------------------------------------
*/
int MudaCtrlAutManCuba(const int aCuba, const int aEstado, const int aOperador)
{
  float		VAlvo;
  float		VInst;
  float		VCicCont;
  char      StrVInst[9];
  char      StrVAlvo[9];
  time_t	HoraAtual;

  /*-- Pega a hora atual --*/
  HoraAtual=time(NULL)/TIMES_PER_SEC; /*-- segs. apartir 1/1/1980 --*/

  if (aCuba ne (-1))
  {
	EST_AVC(aCuba).ProvAgarraAnodo=FALSO;
	AVC.Ccont[aCuba].ContAgarraAnodo=0;	/* Contador de provavel agarramento de anodo */
	if (EST_AVC(aCuba).ChaveAutMan ne aEstado)
	{
	  EST_AVC(aCuba).ChaveAutMan = aEstado;
	  VAlvo=AVC.Ccont[aCuba].VAlvo;
	  VInst=AVC.Cleit[aCuba].Vinst;
	  /* Inicio Alteracao - Carlos - 23/06/99 */
	  /* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
	  VCicCont=AVC.CcontMcp[aCuba].RCicContlBruta*AVC.Ccont[aCuba].INominalCuba+
				 AVC.Param[aCuba].Bemf;
#else
	  VCicCont=AVC.CcontMcp[aCuba].RCicContlBruta*AVL.INominal+
				 AVC.Param[aCuba].Bemf;
#endif
	  /* Fim Alteracao - Carlos - 23/06/99 */

	  if (aEstado eq MANUAL)
	  {
	    /*-- Hora da ultima selecao manual --*/
	    AVC.Cleit[aCuba].HoraUltSelMan = HoraAtual;

	    /*-- Gera eventos --*/
	    GeraEvento(OPERACAO_MANUAL, aCuba, -1, ScoreGetStr(STR_TERMINAL),
					 STR_TRACO,VCicCont,VInst,VAlvo);
	    if (AVL.HabLogOper)
	    {
		  sprintf(StrVInst, "%3.2f", VInst);
		  sprintf(StrVAlvo, "%3.2f", VAlvo);
		  GeraEvento(LOG_OPER_CUBA, aCuba, -1, ScoreGetStr(SCORE_MSG_420),
					 (aOperador eq -1 ? STR_TRACO : NomeOper(aOperador)),
					 ScoreGetStr(STR_MANUAL), StrVInst, StrVAlvo);
		}
	  }
	  else
	  {
		/*-- Cuba colocada em estado automatico --*/
		EST_AVC(aCuba).ManualControle=FALSO;

		/*-- Gera eventos --*/
		GeraEvento(OPERACAO_AUTOMATICO, aCuba, -1, ScoreGetStr(STR_TERMINAL));
		if (AVL.HabLogOper)
		  GeraEvento(LOG_OPER_CUBA, aCuba, -1, ScoreGetStr(SCORE_MSG_420),
				 (aOperador eq -1 ? STR_TRACO : NomeOper(aOperador)),
				 ScoreGetStr(STR_AUTOMATICO), STR_TRACO, STR_TRACO);
	  }
	}
	return(0);
  }
  else
    return(1);
}
