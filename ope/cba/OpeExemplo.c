/******************************************************************************

             ACCENTURE - APAS - ACCENTURE PLANT AND AUTOMATION SOLUTIONS
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 5.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DAS SALAS 125 kA

	ARQUIVO		: OpeExemplo.c

	CONTEUDO	: Exemplo de modulo de comando de operacao. Permite ao operador informar
                  corrida na CUBA.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 1.0		  -		  DATA  : 20/09/2012

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
dd/mm/aa | descricao                                                 | autor 
-------------------------------------------------------------------------------
$Id: OpeExemplo.c,v 1.1.2.1 2012/09/28 17:09:57 leo Exp $

$Log: OpeExemplo.c,v $
Revision 1.1.2.1  2012/09/28 17:09:57  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

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

#ifndef OPERACAO_WINDOWS
  #include <OperacaoBib.h>
  #include <WindowsCBA.h>
  #include <KeysCBA.h>
#endif

/*
-------------------------------------------------------------------------------
							Constantes
-------------------------------------------------------------------------------
*/

#ifdef OPERACAO_WINDOWS
  #define NUM_PARAM			3
#else
  #define NUM_PARAM			4
#endif

/*
-------------------------------------------------------------------------------
							Prototipos
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[]);
#ifdef OPERACAO_WINDOWS
  int  ConsArgs(int argc, char *argv[], char *PMsg);
  void InformaCorrida(char *argv[]);
#else
  int  ConsArgs(int argc, char *argv[], int *CubaIni, int *CubaFim);
  void InformaCorrida(int CubaIni, int CubaFim, char *argv[]);
#endif

/*
-------------------------------------------------------------------------------
							Variaveis Globais
-------------------------------------------------------------------------------
*/

#ifdef OPERACAO_WINDOWS
  t_filtrosPD filtro;
#endif

/*
-------------------------------------------------------------------------------
							Main
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[])
{
  char	Msg[80];
#ifndef OPERACAO_WINDOWS
  int	CubaIni;
  int	CubaFim;
  char	NomeOper[25];
#else
  pid_t	PidPai;

  /*-- Aguarda sinal do modulo AtivaOperacao --*/
  PidPai = Receive(0, NULL, 0);
#endif

#ifndef OPERACAO_WINDOWS
  /*-- Inicializa ambiente para toolkit --*/
  StartWindows(PARCIAL);
#endif

  /*--- Pega segmento comum da base de dados ---*/
  if (PegaComum (&Comum))
#ifdef OPERACAO_WINDOWS
	sprintf(Msg, ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_0 );
#else
  {
	sprintf(Msg, ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_0 );
	ExibeErro(Msg);	
  }
#endif
  else
  {
#ifndef OPERACAO_WINDOWS
	/*-- Verifica se pediu exibicao de texto de ajuda --*/
	if( strcmp( argv[1], CHAVE_AJUDA ) eq 0 )
	{
	  /*-- Pega nome do arquivo --*/
	  strcpy(NomeOper, My_name);
	  EscreveAjuda(NomeOper);
	}
	else
	{
	  /*-- Consiste argumentos recebidos exibindo mensagem de erro --*/
	  if (ConsArgs(argc, argv, &CubaIni, &CubaFim) eq VERDADEIRO) 
	  {
		InformaCorrida(CubaIni, CubaFim, argv);
		ExibeErro(ScoreGetStr(SCORE_MSG_396));
	  }
	}
#else
	/*-- Consiste argumentos recebidos retornando mensagem de erro --*/
	if (ConsArgs(argc, argv, Msg) eq VERDADEIRO) 
	{
	  InformaCorrida(argv);
	  strcpy(Msg, ScoreGetStr(SCORE_MSG_396));
	}
#endif

  }

#ifdef OPERACAO_WINDOWS
  /*-- Envia mensagem liberando o modulo AtivaOperacao --*/
  Reply(PidPai, Msg, sizeof(Msg));
  /* Aguarda tarefa receber resposta antes de morrer. Na rede com maquinas 
     lentas misturadas com maquinas mais rapidas algumas vezes
     o nodo de operacao recebe a indicacao de que a tarefa morreu ANTES de
     receber seu reply, falhando o send. No entanto esta tarefa recebeu o
     send, o processou normalmente e respondeu normalmente. O sleep e' para
     dar tempo do outro micro receber o reply. */
  sleep(15);
#else
  EndWindows();
#endif
}

/*
-------------------------------------------------------------------------------
ConsArgs - Consite os argumentos passados para o modulo de operacao
-------------------------------------------------------------------------------
*/
#ifdef OPERACAO_WINDOWS
int ConsArgs(int argc, char *argv[], char *PMsg)
{
#else
int ConsArgs(int argc, char *argv[], int *CubaIni, int *CubaFim)
{
  char Msg[80];
#endif

  if (argc ne NUM_PARAM)
  {
#ifdef OPERACAO_WINDOWS
	sprintf(PMsg, ScoreGetStr(SCORE_MSG_210));
#else
	sprintf(Msg, ScoreGetStr(SCORE_MSG_210));
	ExibeErro(Msg);
#endif
	return(FALSO);
  }

#ifndef OPERACAO_WINDOWS
  /*-- Converte tipo do numero da cuba --*/
  *CubaIni = atoi(argv[1]);
  *CubaFim = atoi(argv[2]);

  /*-- Verifica se foi passada faixa de cubas. --*/
  if (*CubaFim ne -1)
  {
	/*-- Faz consistencia de faixa de cubas --*/
	if (ConsisteCubas(*CubaIni, *CubaFim) eq FALSO)
	  return(FALSO);
  }
  else
  {
	*CubaFim = *CubaIni;
	/*-- Faz consistencia de apenas uma cuba. --*/
	if (ConvCubOperScore(*CubaIni) eq -1)
	{
	  ExibeErro(ScoreGetStr(SCORE_MSG_4));
	  return(FALSO);
	}
  }
#else
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
#endif

  return(VERDADEIRO);
}

/*
-------------------------------------------------------------------------------
InformaCorrida - Informa ao Sistema corrida na cuba e gera evento de corrida
-------------------------------------------------------------------------------
*/
#ifdef OPERACAO_WINDOWS
void InformaCorrida(char *argv[])
{
  int	 IndCuba;
#else
void InformaCorrida(int CubaIni, int CubaFim, char *argv[])
{
#endif
  int	 CubaAtual;
  int	 Cuba;
  float	 VAlvo;
  float	 VInst;
  float	 VCicCont;
  char	 Operador[9];
  time_t HoraAtual;

  /*-- Pega a hora atual --*/
  HoraAtual=time(NULL)/TIMES_PER_SEC; /*-- segs. apartir 1/1/1970 --*/

  /*-- Aloca semaforo AVC --*/
  AlocaSemaf(SEMAF_AVC);

#ifdef OPERACAO_WINDOWS
  /*-- Faz loop de cubas --*/
  IndCuba = 0;
  strcpy(Operador, argv[2]);
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	Cuba	  = filtro.Par.NumCuba[IndCuba];    
#else
  /*-- Faz varredura de cubas --*/
  strcpy(Operador, argv[3]);
  for(Cuba = CubaIni; Cuba <= CubaFim; ++Cuba)
  {
	CubaAtual = ConvCubOperScore(Cuba);
#endif
	if (CubaAtual ne (-1))
	{
	  if (EST_AVC(CubaAtual).Corrida eq FALSO)
	  {
		EST_AVC(CubaAtual).Corrida = VERDADEIRO;
		if (Comum->IdentReducao eq 5)
		  AVC.User1[Cuba].ContMovCorr = -1;
		AVC.Cleit[CubaAtual].HoraCorrAnt=AVC.Cleit[CubaAtual].HoraUltCorr;
		AVC.Cleit[CubaAtual].HoraUltCorr = HoraAtual;

		/*-- Gera evento de corrida --*/
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
		/* Fim Alteracao - Carlos - 23/06/99 */

		GeraEvento(INICIO_CORRIDA, CubaAtual, -1, ScoreGetStr(STR_TERMINAL), STR_TRACO,
				   VCicCont, VInst, VAlvo);
		if (AVL.HabLogOper)
		  GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, ScoreGetStr(LOG_CORR_OPE), NomeOper(atoi(Operador)),
					 ScoreGetStr(STR_SINALIZA), STR_NULL, STR_NULL);
	  }
	}
#ifdef OPERACAO_WINDOWS
	++IndCuba;
#endif
  }

  /*-- Libera semaforo --*/
  AlteracaoTabela(TABELA_EST_AVC);
  LiberaSemaf(SEMAF_AVC);
}
