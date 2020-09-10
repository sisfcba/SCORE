/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: OpeCbaIniIncQueb.c

	CONTEUDO	: Inibe calculo de ruido pelo periodo indicado pelo operador. 

	AUTOR		: Marco Aurelio Moreira Lopes

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0		  -		  DATA  : 25/04/18

	HISTORICO DAS EDICOES


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
#define NUM_PARAM					4

#define	MAX_TEMPO_INIBE_INC_QUEB		168	/* horas */

/*
-------------------------------------------------------------------------------
							Prototipos
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[]);
int  ConsArgs(int argc, char *argv[],int *Tempo, char *PMsg);
void InibeIncQueb(int Tempo, char *argv[]);

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
	if (ConsArgs(argc, argv, &TempoInibe, Msg) eq VERDADEIRO) 
	{
	  InibeIncQueb(TempoInibe, argv);
	  strcpy(Msg, "Incremento de Quebra Inibido Temporariamente");
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
 int ConsArgs(int argc, char *argv[], int *Tempo, char *PMsg)
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

  /*-- Consiste o tempo --*/
  *Tempo = atoi(argv[2]);
  if ((*Tempo < 2) or (*Tempo > MAX_TEMPO_INIBE_INC_QUEB))
  {
	sprintf(PMsg, ScoreGetStr(SCORE_MSG_404), 2, MAX_TEMPO_INIBE_INC_QUEB);
	return(FALSO);
  }

  return( VERDADEIRO );
}

/*
-------------------------------------------------------------------------------
InibeIncQueb - Inibe incremento de quebra para a faixa de cubas dada pelo periodo
             especificado.
-------------------------------------------------------------------------------
*/
void InibeIncQueb(int Tempo, char *argv[])
{
  int	IndCuba;
  int	CubaAtual;
  int	Cuba;
  int	IntervCicCont;
  char	Operador[9];
  char  str_tempo[9];

  /*-- Intervalo do ciclo de controle em minutos --*/
  IntervCicCont=(Comum->BaseTempoMcp*Comum->BaseTempoMcc)/(SAD_TICKS*60);

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
	  AVC.User3[CubaAtual].ContInibeIncQueb = (Tempo*60)/IntervCicCont;
	  AVC.Ccont[CubaAtual].IncQueb=0.0;

	  /*-- Gera evento --*/
	  GeraEvento(INC_INIBIDO, CubaAtual, -1,"QUEBRA", "Operador", Tempo);
	  sprintf(str_tempo, "%d", Tempo);
	  if (AVL.HabLogOper)
		GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, "OpIniInc", NomeOper(atoi(Operador)),
				   str_tempo, STR_TRACO, STR_TRACO);
	}
	++IndCuba;
  }

  AlteracaoTabela(TABELA_EST_AVC);
  LiberaSemaf(SEMAF_AVC);

}
