/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: OpeCbaInfCab.c

	CONTEUDO	: Modulo de comando de operacao. Permite ao operador informar
                  quebrada na CUBA.

	AUTOR		: Marco Aurelio Moreira Lopes

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 2.0		  -		  DATA  : 13/11/18

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

#define NUM_PARAM			3

/*
-------------------------------------------------------------------------------
							Prototipos
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[]);
int  ConsArgs(int argc, char *argv[], char *PMsg);
void InformaQuebCab(char *argv[], char *PMsg);

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
  if (PegaComum (&Comum))
	  sprintf(Msg, ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_0 );
  else
  {
    /*-- Consiste argumentos recebidos retornando mensagem de erro --*/
    if (ConsArgs(argc, argv, Msg) eq VERDADEIRO) 
    {
      InformaQuebCab(argv, Msg);
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
ConsArgs - Consiste numero de argumentos passados para o comando e critica
		   numero da Cuba.
-------------------------------------------------------------------------------
*/
int ConsArgs(int argc, char *argv[], char *PMsg)
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
  return(VERDADEIRO);
}

/*
-------------------------------------------------------------------------------
InformaQuebCab - Informa ao Sistema quebrada de cabeceira da cuba e 
				gera evento de quebrada
-------------------------------------------------------------------------------
*/
void InformaQuebCab(char *argv[], char *PMsg)
{
  int	IndCuba;
  int	CubaAtual;
  int	Cuba;
  float	VAlvo;
  float	VInst;
  float	VCicCont;
  char	Operador[9];
  time_t HoraAtual;
  char	Msg[80];
  char	ParEv[9];
  
  strcpy(Msg, ScoreGetStr(SCORE_MSG_400));

  /*-- Pega a hora atual --*/
  HoraAtual=time(NULL)/TIMES_PER_SEC;

  AlocaSemaf(SEMAF_AVC);

  /*-- Faz loop de cubas --*/
  IndCuba = 0;
  strcpy(Operador, argv[2]);
  while(IndCuba < filtro.Par.Total)
  {
    CubaAtual = filtro.Par.IndCuba[IndCuba];    
    Cuba	  = filtro.Par.NumCuba[IndCuba];    
    if (CubaAtual ne (-1))
    {
        if (EST_AVC(CubaAtual).Est.QuebCab eq FALSO)
        {
          EST_AVC(CubaAtual).Est.QuebCab = VERDADEIRO;
          EST_AVC(CubaAtual).Est.EfeitoQuebCab = VERDADEIRO;
          AVC.User2[CubaAtual].HoraUltQuebCab = HoraAtual;
          EST_AVC(CubaAtual).Est.ZeraCA = VERDADEIRO;

          /*-- Gera evento de quebrada --*/
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

          GeraEvento(INICIO_QUEBCAB, CubaAtual, -1, ScoreGetStr(STR_TERMINAL), STR_TRACO,
                VCicCont, VInst, VAlvo);

          strcpy(ParEv, STR_NULL);
          strcpy(Msg, ScoreGetStr(SCORE_MSG_400));
          if (AVL.HabLogOper)
            GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, ScoreGetStr(LOG_QUEB_OPE), NomeOper(atoi(Operador)),
                ScoreGetStr(STR_SINALIZA), "QuebCab", ParEv);
        }
        strcpy(PMsg, Msg);
      }
    ++IndCuba;
  }
  AlteracaoTabela(TABELA_EST_AVC);
  LiberaSemaf(SEMAF_AVC);
}

