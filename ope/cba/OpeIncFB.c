/******************************************************************************

             ACCENTURE - APAS - ACCENTURE PLANT AND AUTOMATION SOLUTIONS
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 5.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DAS SALAS 125 kA

	ARQUIVO		: OpeIncFB.c

	CONTEUDO	: Incremento de operacao para formacao de banho.

	AUTOR		: Marco Aurelio M. Lopes

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 1.0		  -		  DATA  : 30/09/2014

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
  #define NUM_PARAM			6
#else
  #define NUM_PARAM			7
#endif

/*
-------------------------------------------------------------------------------
							Prototipos
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[]);
#ifdef OPERACAO_WINDOWS
  int  ConsArgs(int argc, char *argv[], char *PMsg);
  void IncFormaBanho(char *argv[], char *PMsg);
  long ConverteHora(char *argv[]);
#else
  int  ConsArgs(int argc, char *argv[], int *CubaIni, int *CubaFim);
  void IncFormaBanho(int CubaIni, int CubaFim, char *argv[]);
  long ConverteHora(char *argv[]);
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
		IncFormaBanho(CubaIni, CubaFim, argv);
		ExibeErro(ScoreGetStr(SCORE_MSG_396));
	  }
	}
#else
	/*-- Consiste argumentos recebidos retornando mensagem de erro --*/
	if (ConsArgs(argc, argv, Msg) eq VERDADEIRO) 
	{
	  IncFormaBanho(argv, Msg);
//	  strcpy(Msg, "FORMACAO DE BANHO ATIVADA");
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

  /*-- Valida duracao de incremento --*/

  if (ConverteHora(argv) eq 0)
  {
    ExibeErro("Duracao de incremento invalida ");
    return(FALSO);
  }
  else
  {
	if(ConverteHora(argv) > 48*60*60)
	{
      ExibeErro("Duracao de incremento maior que tempo limite");
      return(FALSO);
	}
  } 

  /*-- Valida duracao de incremento --*/

  if (atoi(argv[4]) > 300)
  {
      ExibeErro("Incremento maior que o permitido");
      return(FALSO);
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

  /*-- Valida duracao de incremento --*/

  if (ConverteHora(argv) eq 0)
  {
    sprintf(PMsg, "Duracao de incremento invalida %s", argv[4]);
    return(FALSO);
  }
  else
  {
	if(ConverteHora(argv) > 48*60*60)
	{
      sprintf(PMsg, "Duracao de incremento maior que tempo limite");
      return(FALSO);
	}
  } 

  /*-- Valida duracao de incremento --*/

  if (atoi(argv[3]) > 300)
  {
      sprintf(PMsg, "Incremento maior que o permitido %s mV", argv[3]);
      return(FALSO);
  }

	

#endif

  return(VERDADEIRO);
}

/*
-------------------------------------------------------------------------------
IncFormaBanho - Informa ao Sistema que cuba formara banho e gera evento
-------------------------------------------------------------------------------
*/
#ifdef OPERACAO_WINDOWS
void IncFormaBanho(char *argv[], char *PMsg)
{
  int	 IndCuba;
#else
void IncFormaBanho(int CubaIni, int CubaFim, char *argv[])
{
#endif
  int	 CubaAtual;
  int	 Cuba;
  int	 Acao;
  float	 Inc;
  long	 Dur;
  float	 VAlvo;
  float	 VInst;
  float	 VCicCont;
  char	 Operador[9];
  char	 duracao[8];
  char	 incremento[8];
  time_t HoraAtual;

  /*-- Pega a hora atual --*/
  HoraAtual=time(NULL)/TIMES_PER_SEC; /*-- segs. apartir 1/1/1970 --*/

  /*-- Aloca semaforo AVC --*/
  AlocaSemaf(SEMAF_AVC);

#ifdef OPERACAO_WINDOWS
  /*-- Faz loop de cubas --*/
  IndCuba = 0;
  strcpy(Operador, argv[5]);
  strcpy(duracao, argv[4]);
  strcpy(incremento, argv[3]);
  Acao = atoi(argv[2]);
  Inc = atof(argv[3]);
  Dur = ConverteHora(argv);

  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	Cuba	  = filtro.Par.NumCuba[IndCuba];    

#else
  /*-- Faz varredura de cubas --*/
  strcpy(Operador, argv[6]);
  strcpy(duracao, argv[5]);
  strcpy(duracao, argv[4]);
  Acao = atoi(argv[3]);
  Inc = atof(argv[4]);
  Dur = ConverteHora(argv);

  for(Cuba = CubaIni; Cuba <= CubaFim; ++Cuba)
  {

	CubaAtual = ConvCubOperScore(Cuba);
	
#endif
	if (CubaAtual ne (-1))
	{

		/*-- Gera evento de corrida --*/
		VAlvo=AVC.Ccont[CubaAtual].VAlvo;
		VInst=AVC.Cleit[CubaAtual].Vinst;

		/* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
		VCicCont=AVC.CcontMcp[CubaAtual].RCicContlBruta*AVC.Ccont[CubaAtual].INominalCuba+
				 AVC.Param[CubaAtual].Bemf;
#else
		VCicCont=AVC.CcontMcp[CubaAtual].RCicContlBruta*AVL.INominal+
				 AVC.Param[CubaAtual].Bemf;
#endif

	  if( Acao eq 1)
	  {
		if(EST_AVC(CubaAtual).Est.FormaBanho eq FALSO)
		{
		  EST_AVC(CubaAtual).Est.FormaBanho  = VERDADEIRO;
		  AVC.User2[CubaAtual].IncFormaBanho = Inc / 1000;
		  AVC.User2[CubaAtual].DurFormaBanho = Dur;
		  AVC.User2[CubaAtual].HoraIniFormaBanho = HoraAtual;

		  GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, "OpeFBanho", NomeOper(atoi(Operador)),
					 "Inicio", duracao, incremento);

		  GeraEvento(EV_FORMABANHO, CubaAtual, -1, ScoreGetStr(STR_TERMINAL), "Inicio",
				   VCicCont, VInst, VAlvo);

#ifdef OPERACAO_WINDOWS
	  	  strcpy(PMsg, "FORMACAO DE BANHO ATIVADA");
#endif

		} 
		else
		{
#ifdef OPERACAO_WINDOWS
	  	  strcpy(PMsg, "NAO REALIZADO");
#endif	  		  
		}
	  }
	  else if(Acao eq 2)
	  {
		if(EST_AVC(CubaAtual).Est.FormaBanho eq VERDADEIRO)
		{
		  AVC.User2[CubaAtual].IncFormaBanho = Inc / 1000;
		  AVC.User2[CubaAtual].DurFormaBanho = Dur;

		  GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, "OpeFBanho", NomeOper(atoi(Operador)),
					 "Altera", duracao, incremento);
		  GeraEvento(EV_FORMABANHO, CubaAtual, -1, ScoreGetStr(STR_TERMINAL), "Altera",
				   VCicCont, VInst, VAlvo);

#ifdef OPERACAO_WINDOWS
	  	  strcpy(PMsg, "FORMACAO DE BANHO ALTERADA");
#endif
		} 
		else
		{
#ifdef OPERACAO_WINDOWS
	  	  strcpy(PMsg, "NAO REALIZADO");
#endif	  	  
		}
	  }
	  else if(Acao eq 3)
	  {
		if(EST_AVC(CubaAtual).Est.FormaBanho eq VERDADEIRO)
		{
		  EST_AVC(CubaAtual).Est.FormaBanho  = FALSO;
		  AVC.User2[CubaAtual].IncFormaBanho = 0.0;
		  AVC.User2[CubaAtual].DurFormaBanho = 0;

		  GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, "OpeFBanho", NomeOper(atoi(Operador)),
					 "Desativa", duracao, incremento);
		  GeraEvento(EV_FORMABANHO, CubaAtual, -1, ScoreGetStr(STR_TERMINAL), "Desativa",
				   VCicCont, VInst, VAlvo);

#ifdef OPERACAO_WINDOWS
	  	  strcpy(PMsg, "FORMACAO DE BANHO DESATIVADA");
#endif
		} 
		else
		{
#ifdef OPERACAO_WINDOWS
	  	  strcpy(PMsg, "NAO REALIZADO");
#endif	  
		}

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

/*
-------------------------------------------------------------------------------
ConverteHora - Converte hora string para long
-------------------------------------------------------------------------------
*/
long ConverteHora(char *argv[])
{
  char duracao[5], hora[2], minuto[2];

#ifdef OPERACAO_WINDOWS
  strcpy(duracao, argv[4]);

  if (strlen(argv[4]) ne 5)
  {
#else
  strcpy(duracao, argv[4]);

  if (strlen(argv[5]) ne 5)
  {
#endif
    return(0);
  }
  else
  {
    if (duracao[2] eq ':')
    {
      hora[0] = duracao[0];
      hora[1] = duracao[1];
      minuto[0] = duracao[3];
      minuto[1] = duracao[4];
      if (atoi(hora) > 0)
      {
  	    if(atoi(minuto) eq 0 and minuto[0] eq '0' and minuto[1] eq '0')
	    { 
		  return((atoi(hora)*60*60));
	    }
	    else if(atoi(minuto) > 0)
	    {
		  return((atoi(hora)*60*60) + (atoi(minuto)*60));		
	    }
	    else
	    {
		  return(0);		
	    }
      }
      else
      {
        return(0);
	  }
	}
    else
    {
      return(0);
    }
  } 

}
