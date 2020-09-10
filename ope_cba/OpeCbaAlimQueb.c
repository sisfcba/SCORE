/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DAS SALAS 120 KA II,III E IV

	ARQUIVO		: OpeCbaQuebAlim.c

	CONTEUDO	: Programa 

	AUTOR		: Carlos Cezar Silva Lage

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C - V10.6B

	VERSAO		: 1.0		  -		  DATA  : 21/11/2000

	HISTORICO DAS EDICOES

$Id: OpeCbaAlimQueb.c,v 1.1.2.1 2015/10/27 16:52:29 clage Exp $

$Log: OpeCbaAlimQueb.c,v $
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

/*-- Numero de parametros --*/
#define NUM_PARAM		4

/*-- Numero de dispositivos de PF --*/
#define MAX_DISP		8

/*-- Mapeamento de dispositivos acionados pelo point feeder--*/
#define ALIM_1			1 // 1o. Alimentador
#define ALIM_2			2 // 2o. Alimentador
#define ALIM_3			3 // 3o. Alimentador
#define ALIM_4			4 // 4o. Alimentador
#define QUEB_1			5 // 1o. Quebrador
#define QUEB_2			6 // 2o. Quebrador
#define QUEB_3			7 // 3o. Quebrador
#define QUEB_4			8 // 4o. Quebrador

/*
-------------------------------------------------------------------------------
								Prototipos
-------------------------------------------------------------------------------
*/


typedef
  struct DispAcion
  {
	int			Disp;
	byte		Status;
  } t_disp_ac;

typedef
  struct MapDisp
  {
	int			MaxDisp;
	t_disp_ac 	StatDisp[MAX_DISP];
  } t_map_ac;


/*
-------------------------------------------------------------------------------
								Prototipos
-------------------------------------------------------------------------------
*/

void main(int argc, char *argv[]);
int  ConsArgs(int argc, char *argv[], t_map_ac *MapAc, char *Msg);
void TrataAlimQueb(t_map_ac *MapAc, char *argv[]);
int  InsereDisp(int disp, byte acao, t_map_ac * MapAc);
char *TipoDisp(int d);
char *TipoDispCompl(int d);

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
  t_map_ac	MapAc;
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
	if (ConsArgs(argc, argv, &MapAc, Msg) eq VERDADEIRO) 
	{
	  TrataAlimQueb(&MapAc, argv);
	  sprintf(Msg, ScoreGetStr(SCORE_MSG_444));
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
	ConsArgs - Consiste  os argumentos de chamada do programa
-------------------------------------------------------------------------------
*/
int ConsArgs(int argc, char *argv[], t_map_ac *MapAc, char *Msg)
{
  char *dup,*p,oper[5],var[3];
  int  disp,cod_err,i;
  byte acao;

  if (argc ne NUM_PARAM)
  {
	sprintf(Msg, ScoreGetStr(SCORE_MSG_210));
	return(FALSO);
  }

  /*-- Le arquivo de filtro de cubas --*/
  if (LeFiltroCubas(argv[1], &filtro))
  {
    sprintf(Msg, ScoreGetStr(SCORE_ERR_2),My_name,COD_ERRO_6, argv[1]);
	return(FALSO);
  }
  if (filtro.Par.Total eq 0)
  {
    strcpy(Msg, ScoreGetStr(SCORE_MSG_356));
	return(FALSO);
  }

  /*-- Inicializacao da tabela de dispositivos --*/
  MapAc->MaxDisp = 0;
  for (i=0; i < MAX_DISP; i++)
  {
	MapAc->StatDisp[i].Disp = 0;
	MapAc->StatDisp[i].Status = FALSO;
  }

  dup = strdup(argv[2]);
  p = strtok(dup,",");

  if (p eq NULL)
  {
	strcpy (Msg, ScoreGetStr(SCORE_MSG_2051));
	return(FALSO);
  }
  else
  {
	while (p ne NULL)
	{
	  strcpy(oper,p);
	  sprintf(var,"%c",oper[1]);
	  disp = atoi((char *) var);
	  acao = (oper[0] eq 'A')? VERDADEIRO:FALSO;
	  if ((cod_err = InsereDisp(disp, acao, MapAc)) < 0)
	  {
		if (cod_err eq -1)
		  strcpy(Msg, ScoreGetStr(SCORE_MSG_2051));
		else
		{
		  if (cod_err eq -2)
			sprintf (Msg, ScoreGetStr(SCORE_MSG_2052),TipoDispCompl(disp));
		}
		return(FALSO);
	  }
	  p = strtok(NULL,",");
	}
  }
  
  return(VERDADEIRO);
}


/*
-------------------------------------------------------------------------------
  TrataAlimQueb - Trata acionamento de alimentacao e quebrada
-------------------------------------------------------------------------------
*/
void TrataAlimQueb(t_map_ac *MapAc, char *argv[])
{
  int	IndCuba;
  char	Operador[9];
  char	StrStatus[9];
  int	CubaAtual;
  int	i,d;
  byte	Status;

  /*-- Aloca semaforos --*/
  AlocaSemaf(SEMAF_AVC);

  /*-- Faz loop dos grupos --*/
  IndCuba = 0;
  strcpy(Operador, argv[3]);
  while(IndCuba < filtro.Par.Total)
  {
	CubaAtual = filtro.Par.IndCuba[IndCuba];    
	if (CubaAtual ne -1)
	{
	  for (i=0; i < MapAc->MaxDisp; i++)
	  {
		Status = MapAc->StatDisp[i].Status;
		d = MapAc->StatDisp[i].Disp;
		switch (d)
		{
		   case ALIM_1:
		   case ALIM_2:
		   case ALIM_3:
		   case ALIM_4:
				if (AVC.User2[CubaAtual].HabAlimOp[d-1] ne Status)
				{
				  AVC.User2[CubaAtual].HabAlimOp[d-1] = Status;
				  if (Status eq VERDADEIRO)
					strcpy(StrStatus, "Ativado");
				  else
					strcpy(StrStatus, "Desativ");

				  if (AVL.HabLogOper)
					GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, "AlimQueb",
								NomeOper(atoi(Operador)), TipoDisp(d), StrStatus, "--------");
				}
				break;

		   case QUEB_1:
		   case QUEB_2:
		   case QUEB_3:
		   case QUEB_4:
				if (AVC.User2[CubaAtual].HabQuebOp[d-5] ne Status)
				{
				  AVC.User2[CubaAtual].HabQuebOp[d-5] = Status;
				  if (Status eq VERDADEIRO)
					strcpy(StrStatus, "Ativado");
				  else
					strcpy(StrStatus, "Desativ");

				  if (AVL.HabLogOper)
					GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, "AlimQueb",
								NomeOper(atoi(Operador)), TipoDisp(d), StrStatus, "--------");
				}
				break;
	    }
	  }
	} 

	++IndCuba;
  }

  LiberaSemaf(SEMAF_AVC);
  AlteracaoTabela(TABELA_AVC);
}

/*
-------------------------------------------------------------------------------
	InsereDisp - Mapeia dispositivo acionado
-------------------------------------------------------------------------------
*/
int InsereDisp(int disp, byte acao, t_map_ac * MapAc)
{
  int i;

  if (MapAc->MaxDisp eq 0)
  {
	if ((disp >= 1) and (disp <= 8))
	{
	  MapAc->StatDisp[0].Disp = disp;
	  MapAc->StatDisp[0].Status = acao;
	  MapAc->MaxDisp = 1;
	}
	else
	  return(-1);
  }
  else
  {
	/*-- Verifica se nao existe acionamento repetido --*/
	for (i=0; i < MAX_DISP; i++)
	{
	  if (MapAc->StatDisp[i].Disp eq disp)
		return(-2);
	}
	i = MapAc->MaxDisp;
	MapAc->StatDisp[i].Disp = disp;
	MapAc->StatDisp[i].Status = acao;
	MapAc->MaxDisp += 1;
  }

  return(0);
}

/*
-------------------------------------------------------------------------------
  TipoDisp - Retorna o nome do dispositivo acionado
-------------------------------------------------------------------------------
*/
char *TipoDisp(int d)
{
  static char Nome[9];

  memset(Nome, 0x00, sizeof(Nome));
  switch(d)
  {
	case ALIM_1:
	case ALIM_2:
	case ALIM_3:
	case ALIM_4:
		 sprintf(Nome,"Alim. %d", d);
		 break;

	case QUEB_1:
	case QUEB_2:
	case QUEB_3:
	case QUEB_4:
		 sprintf(Nome,"Queb. %d", d-4);
		 break;
  }

  return(Nome);
}
/*
-------------------------------------------------------------------------------
  TipoDispCompl - Retorna o nome completo do dispositivo acionado
-------------------------------------------------------------------------------
*/
char *TipoDispCompl(int d)
{
  static char Nome[20];

  memset(Nome, 0x00, sizeof(Nome));
  switch(d)
  {
	case ALIM_1:
	case ALIM_2:
	case ALIM_3:
	case ALIM_4:
		 sprintf(Nome,"Alimentador %d", d);
		 break;

	case QUEB_1:
	case QUEB_2:
	case QUEB_3:
	case QUEB_4:
		 sprintf(Nome,"Quebrador %d", d-4);
		 break;
  }

  return(Nome);
}
