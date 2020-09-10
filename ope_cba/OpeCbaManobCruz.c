/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DAS SALAS 125 KA

	ARQUIVO		: OpeCbaManubCruz.c

	CONTEUDO	: Modulo de comando de operacao. Informa manobra de cruzeiro
	              para as cubas.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C - V10.1

	VERSAO		: 1.0		  -		  DATA  : 01/03/07

	HISTORICO DAS EDICOES

$Id: OpeCbaManobCruz.c,v 1.1.2.1 2015/10/27 16:52:29 clage Exp $

$Log: OpeCbaManobCruz.c,v $
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

#define NUM_PARAM				3

/*
-------------------------------------------------------------------------------
							Prototipos
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[]);
int  ConsArgs(int argc, char *argv[], char *PMsg);
void InformaManobra(char *argv[]);

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
  char	Msg[80];
  pid_t	PidPai;

  /*-- Aguarda sinal do modulo AtivaOperacao --*/
  PidPai = Receive(0, NULL, 0);

  /*--- Pega segmento comum da base de dados ---*/
  if (PegaComum(&Comum))
	sprintf(Msg, ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_0 );
  else
  {
	/*-- Consiste argumentos recebidos retornando mensagem de erro --*/
	if (ConsArgs(argc, argv, Msg) eq VERDADEIRO) 
	{
	  InformaManobra(argv);
	  strcpy(Msg, "Sinalizacao de Manobra de Cruzeiro efetuada");
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
ConsArgs - Consiste numero de argumentos passados para o comando, critica
		   numero da Cuba Inicial e Final
-------------------------------------------------------------------------------
*/
int ConsArgs(int argc, char *argv[], char *PMsg)
{
  int	 IndCuba;
  int	 CubaAtual;
  int	 Cuba;

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
  /*-- Faz loop dos grupos --*/
  IndCuba = 0;
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];
	Cuba	  = filtro.Par.NumCuba[IndCuba];
	if (CubaAtual ne (-1))
	{
	  if ((AVC.ParUser1[CubaAtual].HabMCruzeiro) and (AVC.Abs[CubaAtual].BitChaveMCruzeiro ne 255))
	  { /* habilitado algoritmo de manobra de cruzeiro, verifica condicao para habilitar */
	    if (EST_AVC(CubaAtual).Est.ChaveMCruzeiro eq VERDADEIRO)
	    { /* Chave de manobra ligada -> Erro: Nao permite habilitar manobra */
	      sprintf(PMsg, "Cuba=%d Chave de manobra cruzeiro ligada!", Cuba);
		  return(FALSO);
	    }
	    if (EST_AVC(CubaAtual).ChaveLocRem ne LOCAL)
	    { /* Chave de MM em automatico -> Erro: Nao permite habilitar manobra */
	      sprintf(PMsg, "Cuba=%d Chave de MM em automatico!", Cuba);
		  return(FALSO);
	    }
	  }
	}
	IndCuba++;
  }

  return(VERDADEIRO);
}

/*
-------------------------------------------------------------------------------
InformaManobra - Informa ativacao de manobra de cruzeiro para as cubas e
				 gera evento.
-------------------------------------------------------------------------------
*/
void InformaManobra(char *argv[])
{
  int	 IndCuba;
  char	 Operador[9];
  int	 CubaAtual;
  int	 Cuba, bit_acao;
  time_t HoraAtual;
  float		VCicCont, VInst, VAlvo;

  HoraAtual=time(NULL)/TIMES_PER_SEC; /* -- segs. apartir 1/1/1970 -- */

  /*-- Aloca semaforo --*/
  AlocaSemaf(SEMAF_AVC);

  /*-- Faz loop dos grupos --*/
  IndCuba = 0;
  strcpy(Operador, argv[2]);
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	Cuba	  = filtro.Par.NumCuba[IndCuba];    

	if (CubaAtual ne (-1))
	{
	  EST_AVC(CubaAtual).TrataCruzeiro = VERDADEIRO;
	  AVC.Cleit[CubaAtual].HoraUltCruzeiro=HoraAtual;

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

	  GeraEvento(EV_MANOBRA_CRUZEIRO, CubaAtual, -1, ScoreGetStr(STR_TERMINAL),
						  STR_NULL, VCicCont,VInst,VAlvo);

	  if ((AVC.ParUser1[CubaAtual].HabMCruzeiro) and (AVC.Abs[CubaAtual].BitChaveMCruzeiro ne 255))
	  { /* habilitado algoritmo de manobra de cruzeiro, verifica condicao para habilitar */
	    if ((EST_AVC(CubaAtual).Est.ChaveMCruzeiro eq FALSO) and 
			(EST_AVC(CubaAtual).ChaveLocRem eq LOCAL))
	    { /* Da permissao de manobra de cruzeiro */
		  EST_AVC(CubaAtual).Est.LiberaMCruzeiro=VERDADEIRO;
		  bit_acao=AVC.Abs[CubaAtual].BitLiberaMCruzeiro;
		  if (bit_acao ne 255)
			ComandaSaidaRem(CubaAtual,LIGAR,bit_acao,0);
		  GeraEvento(EV_MANOBRA_CRUZEIRO, CubaAtual, -1, "Habilita",
					  ScoreGetStr(SCORE_MSG_401), VCicCont,VInst,VAlvo);
	    }
	  }

	  if (AVL.HabLogOper)
		 GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, "ManoCruz",
						NomeOper(atoi(Operador)), STR_NULL, STR_NULL, STR_NULL);
	}
	++IndCuba;
	
  }
  AlteracaoTabela(TABELA_EST_AVC);
  LiberaSemaf(SEMAF_AVC);
}
