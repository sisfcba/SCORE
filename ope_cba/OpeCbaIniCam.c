/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: OpeCbaIniCam.c

	CONTEUDO	: Inibe o ajuste de camisa do pelo periodo definido pelo
				  operador na chamada dessa opcao. 

	AUTOR		: Carlos Cezar Silva Lage

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0		  -		  DATA  : 19/11/96

	HISTORICO DAS EDICOES

$Id: OpeCbaIniCam.c,v 1.1.2.1 2015/10/27 16:52:29 clage Exp $

$Log: OpeCbaIniCam.c,v $
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
#include <AjusteCamisa.h>

/*
-------------------------------------------------------------------------------
							Constantes
-------------------------------------------------------------------------------
*/

#define NUM_PARAM						5
#define	MAX_TEMPO_INIBE_AJ_CAMISA		48	/*-- horas --*/

#define MSG_AJ_CAM_ANDAMEN				"Ajuste de camisa da cuba %d em andamento"
#define MSG_ACAO_AJ_NAO_SEL				"Acao de ajuste nao selecionada"
#define MSG_TEMPO_INV_HOR				"Tempo invalido (min=%d max=%d horas)"

/*
-------------------------------------------------------------------------------
							Prototipos
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[]);
int  ConsArgs(int argc, char *argv[],int *Tempo, int *Acao, char *PMsg);
void AlteraAjCamisa(int Tempo, int Acao, char *argv[], char *PMsg);
int  VerifInibeAjuste(char *PMsg);

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
  int	TempoInibe;
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
	if (ConsArgs(argc, argv, &TempoInibe, &Acao, Msg) eq VERDADEIRO) 
	{
	  AlteraAjCamisa(TempoInibe, Acao, argv, Msg);
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
int ConsArgs(int argc, char *argv[], int *Tempo, int *Acao, char *PMsg)
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
  if ((*Acao ne ATIVA_AJUSTE_CAMISA) and (*Acao ne DESATIVA_AJUSTE_CAMISA) and
	  (*Acao ne INIBE_AJUSTE_CAMISA))
  {
	strcpy(PMsg, MSG_ACAO_AJ_NAO_SEL);
	return(FALSO);
  }

  if (*Acao eq INIBE_AJUSTE_CAMISA)
  {
	if (VerifInibeAjuste(PMsg) eq FALSO)
	  return(FALSO);

	/*-- Consiste o tempo --*/
	*Tempo = atoi(argv[3]);
	if ((*Tempo < 0) or (*Tempo > MAX_TEMPO_INIBE_AJ_CAMISA))
	{
	  sprintf(PMsg, MSG_TEMPO_INV_HOR, 0, MAX_TEMPO_INIBE_AJ_CAMISA);
	  return(FALSO);
	}
	/*-- Converte para minutos --*/
	*Tempo *= 60L;
  }

  return( VERDADEIRO );
}

/*
-------------------------------------------------------------------------------
AlteraAjCamisa - Ativa, desativa ou inibe por determinado tempo o ajuste de
		camisa
-------------------------------------------------------------------------------
*/
void AlteraAjCamisa(int Tempo, int Acao, char *argv[], char *PMsg)
{
  int	IndCuba;
  int	CubaAtual;
  int	Cuba;
  char	Operador[9];

  AlocaSemaf(SEMAF_AVC);

  /*-- Faz loop de cubas --*/
  IndCuba = 0;
  strcpy(Operador, argv[4]);
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	Cuba	  = filtro.Par.NumCuba[IndCuba];    
	if (CubaAtual ne -1)
	  AlteraAjusteCamisa(CubaAtual,Acao,Tempo,atoi(Operador),PMsg);
	++IndCuba;
  }

  AlteracaoTabela(TABELA_EST_AVC);
  LiberaSemaf(SEMAF_AVC);
}




/*
-------------------------------------------------------------------------------
  VerifInibeAjuste - Verifica condicoes de inibicao de ajuste
-------------------------------------------------------------------------------
*/
int VerifInibeAjuste(char *PMsg)
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
	if (CubaAtual ne -1)
	{
	  if ((EST_AVC(CubaAtual).Est.AjusteCamisa eq VERDADEIRO) and
		  (EST_AVC(CubaAtual).Est.AbortaAjuste eq AJUSTE_NORMAL))
	  {
		sprintf(PMsg, MSG_AJ_CAM_ANDAMEN, Cuba);
		return(FALSO);
	  }
	}
	++IndCuba;
  }
  return(VERDADEIRO);
}

