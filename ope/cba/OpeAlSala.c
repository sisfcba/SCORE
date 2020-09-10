/******************************************************************************

             ACCENTURE - APAS - ACCENTURE PLANT AND AUTOMATION SOLUTIONS
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 5.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DAS SALAS 125 kA

	ARQUIVO		: OpeAlSala.c

	CONTEUDO	: Ativa todas as sirenes para alarmar desligamento ou 
				  religamento de sala.

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
  void AlarmeSala(char *argv[], char *PMsg);
  long ConverteHora(char *argv[]);
#else
  int  ConsArgs(int argc, char *argv[]);
  void AlarmeSala(char *argv[]);
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
	  if (ConsArgs(argc, argv) eq VERDADEIRO) 
	  {
		AlarmeSala(argv);
		ExibeErro(ScoreGetStr(SCORE_MSG_396));
	  }
	}
#else
	/*-- Consiste argumentos recebidos retornando mensagem de erro --*/
	if (ConsArgs(argc, argv, Msg) eq VERDADEIRO) 
	{
	  AlarmeSala(argv, Msg);
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
int ConsArgs(int argc, char *argv[])
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

  return(VERDADEIRO);
}

/*
-------------------------------------------------------------------------------
AlarmeSala - Sinaliza o alarme para desligament ou religamento de sala
-------------------------------------------------------------------------------
*/
#ifdef OPERACAO_WINDOWS
void AlarmeSala(char *argv[], char *PMsg)
{
#else
void AlarmeSala(char *argv[])
{
#endif
  int	 Acao;
  char	 Operador[9];
  time_t HoraAtual;

  /*-- Pega a hora atual --*/
  HoraAtual=time(NULL)/TIMES_PER_SEC; /*-- segs. apartir 1/1/1970 --*/

  /*-- Aloca semaforo AVC --*/
  AlocaSemaf(SEMAF_AVC);

#ifdef OPERACAO_WINDOWS
  strcpy(Operador, argv[2]);
  Acao = atoi(argv[1]);
#else
  /*-- Faz varredura de cubas --*/
  strcpy(Operador, argv[3]);
  Acao = atoi(argv[2]);

#endif
  if( Acao eq 1)
  {
	if(AVL.Trab.AlarmeSala eq 0)
	{
	  AVL.Trab.HoraAlarmeSala = HoraAtual;
	  AVL.Trab.AlarmeSala = 1;
	  AVL.Trab.EstadoSireneSala = FALSO;
	  GeraEvento(EV_SIRENE, -1, -1, "LIGAR", NomeOper(atoi(Operador)),
				 0000, AVL.VLinhaCicCont, AVL.ICicContlMed / 1000);
#ifdef OPERACAO_WINDOWS
  	  strcpy(PMsg, "SINALIZACAO RELIGAMENTO DE SALA ATIVADA!");
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
	if(AVL.Trab.AlarmeSala eq 0)
	{
	  AVL.Trab.HoraAlarmeSala = HoraAtual;
	  AVL.Trab.AlarmeSala = 2;
	  AVL.Trab.EstadoSireneSala = FALSO;
	  GeraEvento(EV_SIRENE, -1, -1, "DESLIGAR", NomeOper(atoi(Operador)),
				 0000, AVL.VLinhaCicCont, AVL.ICicContlMed / 1000);
#ifdef OPERACAO_WINDOWS
  	  strcpy(PMsg, "SINALIZACAO DESLIGAMENTO DE SALA ATIVADA!");
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
	  AVL.Trab.HoraAlarmeSala = HoraAtual;
	  AVL.Trab.AlarmeSala = 0;
	  GeraEvento(EV_SIRENE, -1, -1, "DESATIVA", NomeOper(atoi(Operador)),
				 0000, AVL.VLinhaCicCont, AVL.ICicContlMed / 1000);
#ifdef OPERACAO_WINDOWS
  	  strcpy(PMsg, "SINALIZACAO DE SALA DESATIVADA!");
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
