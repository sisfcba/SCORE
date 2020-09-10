/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: OpeCbaInfQueb.c

	CONTEUDO	: Modulo de comando de operacao. Permite ao operador informar
                  quebrada na CUBA.

	AUTOR		: Junia Guerra

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 2.0		  -		  DATA  : 12/08/94

	HISTORICO DAS EDICOES

$Id: OpeCbaInfQueb.c,v 1.1.2.1 2015/10/27 16:52:29 clage Exp $

$Log: OpeCbaInfQueb.c,v $
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

#define NUM_PARAM			3

/*
-------------------------------------------------------------------------------
							Prototipos
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[]);
int  ConsArgs(int argc, char *argv[], char *PMsg);
void InformaQuebrada(char *argv[], char *PMsg);

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
	  InformaQuebrada(argv, Msg);
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
InformaQuebrada - Informa ao Sistema quebrada na cuba e gera evento de quebrada
-------------------------------------------------------------------------------
*/
void InformaQuebrada(char *argv[], char *PMsg)
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
  char	SF_Pos[9];
  
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
	  if (EST_AVC(CubaAtual).Quebrada eq FALSO)
//		(AVC.ParUser2[CubaAtual].HabilitaPFCBA eq FALSO or EST_AVC(CubaAtual).Ea eq VERDADEIRO))
	  {
		EST_AVC(CubaAtual).Quebrada = VERDADEIRO;
		AVC.Cleit[CubaAtual].HoraUltQueb = HoraAtual;
		EST_AVC(CubaAtual).Est.ZeraCA = VERDADEIRO;

		if(AVC.ParUser1[CubaAtual].HabPrecMovQueb eq VERDADEIRO and
			(AVC.User3[CubaAtual].Temperatura <= AVC.ParUser2[CubaAtual].TempMaxInibInc or 
			AVC.ParUser2[CubaAtual].InibIncQuebTemp eq FALSO) and
			((HoraAtual - AVC.Ea[CubaAtual].EaHoraInicio) < 
			((AVC.Param[CubaAtual].EaAtrasoMax - AVC.ParUser1[CubaAtual].LimSupQPrevEa) * 60) ))
		{
 		  AVC.User2[CubaAtual].HoraPrecMovQueb = HoraAtual;
		  AVC.Ccont[CubaAtual].HoraUltMove = HoraAtual;

		  if(((AVC.Ccont[CubaAtual].VSetPoint-AVC.Param[CubaAtual].Bemf+AVC.Param[CubaAtual].VIncMax)/AVL.INominal) > 
		  	(AVC.Ccont[CubaAtual].RAlvo + (AVC.Param[CubaAtual].IncQuebInic / AVL.INominal)))	
		  {
		  	AVC.Ccont[CubaAtual].RAlvo = AVC.Ccont[CubaAtual].RAlvo + 
				(AVC.Param[CubaAtual].IncQuebInic / AVL.INominal);
		  }
		  else
		  {
			AVC.Ccont[CubaAtual].RAlvo = ((AVC.Ccont[CubaAtual].VSetPoint-AVC.Param[CubaAtual].Bemf+AVC.Param[CubaAtual].VIncMax)/AVL.INominal);
		  }
		}

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

		GeraEvento(INICIO_QUEBRADA, CubaAtual, -1, ScoreGetStr(STR_TERMINAL), STR_TRACO,
				   VCicCont, VInst, VAlvo);


	    if(((EST_AVC(CubaAtual).Ea eq VERDADEIRO and 
				AVC.User1[CubaAtual].AtrasouEa eq FALSO and 
				((AVC.User2[CubaAtual].HoraProxQuebReal - AVC.Cleit[CubaAtual].HoraUltQueb) < AVC.ParUser1[CubaAtual].IntEAQProg*60)) or
			(EST_AVC(CubaAtual).Est.QuebPrev eq VERDADEIRO and 
			((AVC.User2[CubaAtual].HoraProxQuebReal - AVC.Cleit[CubaAtual].HoraUltQueb) < AVC.ParUser1[CubaAtual].IntQPQProg*60))) and 
			AVC.ParUser1[CubaAtual].HabPulaQuebProg eq VERDADEIRO)
	 	{
		  EST_AVC(CubaAtual).Est.PulaProxQueb = VERDADEIRO;
		}

		if (AVC.ParUser1[CubaAtual].HabSmartFeed eq VERDADEIRO and EST_AVC(CubaAtual).Ea eq FALSO)
		{
		  if(AVC.User1[CubaAtual].SF_IncDeriv >= AVC.ParUser1[CubaAtual].SF_SUFeed)
		  {
		    AVC.User1[CubaAtual].SF_TempoSobe += AVC.ParUser1[CubaAtual].SF_PassoAcima; 
		    AVC.User1[CubaAtual].SF_Posicao = 5; 
		  	strcpy(SF_Pos, "S_Under");			
		  }
		  else if(AVC.User1[CubaAtual].SF_IncDeriv >= AVC.ParUser1[CubaAtual].SF_UnderFeed)
		  {
 		    if(AVC.User1[CubaAtual].SF_Posicao <= 4)
			  AVC.User1[CubaAtual].SF_TempoSobe += AVC.ParUser1[CubaAtual].SF_PassoAcima;

		    AVC.User1[CubaAtual].SF_Posicao = 4; 
		  	strcpy(SF_Pos, "Under");			
		  }
		  else if(AVC.User1[CubaAtual].SF_IncDeriv >= AVC.ParUser1[CubaAtual].SF_NormalFeed)
		  {
		    AVC.User1[CubaAtual].SF_Posicao = 3; 
		  	strcpy(SF_Pos, "Normal");			
		  }
		  else if(AVC.User1[CubaAtual].SF_IncDeriv >= AVC.ParUser1[CubaAtual].SF_OverFeed)
		  {
 		    if(AVC.User1[CubaAtual].SF_Posicao >= 2)
			  AVC.User1[CubaAtual].SF_TempoSobe -= AVC.ParUser1[CubaAtual].SF_PassoAbaixo;
		    AVC.User1[CubaAtual].SF_Posicao = 2; 
		  	strcpy(SF_Pos, "OverFeed");			
		  }
		  else 
		  {
		    AVC.User1[CubaAtual].SF_TempoSobe -= AVC.ParUser1[CubaAtual].SF_PassoAbaixo;
		    AVC.User1[CubaAtual].SF_Posicao = 1; 
		  	strcpy(SF_Pos, "S_Over");			
		  }
		
//		  AVC.User1[CubaAtual].SF_IncDerivEA = (AVC.User1[CubaAtual].SF_IncDerivEA * (AVC.User1[CubaAtual].NumQuebProg) + 
//							AVC.User1[CubaAtual].SF_IncDeriv) / (AVC.User1[CubaAtual].NumQuebProg+1);

		  if (AVC.User1[CubaAtual].SF_TempoSobe > AVC.ParUser1[CubaAtual].SF_LimMovCima)	
		  {
		    AVC.User1[CubaAtual].SF_TempoSobe = AVC.ParUser1[CubaAtual].SF_LimMovCima;		  
		  }

		  if (AVC.User1[CubaAtual].SF_TempoSobe < AVC.ParUser1[CubaAtual].SF_LimMovBaixo)	
		  {
		    AVC.User1[CubaAtual].SF_TempoSobe = AVC.ParUser1[CubaAtual].SF_LimMovBaixo;		  
		  }
			
		  if (EST_AVC(CubaAtual).Est.DerBaixa eq VERDADEIRO)
		  {
		    AVC.User1[CubaAtual].SF_TempoSobe = 0.0;
			AVC.User1[CubaAtual].QuebrouDB = VERDADEIRO;
		  }		  
		  else
		  {
			AVC.User1[CubaAtual].QuebrouDB = FALSO;
		  }
		  
/*		  
		  if ( (((AVC.CcontMcp[CubaAtual].RCicContlBruta + ((AVC.User1[CubaAtual].SF_TempoSobe * AVC.Ccont[CubaAtual].Kcpwm))) * AVL.INominal) + AVC.Param[CubaAtual].Bemf) >
		  		(AVC.Ccont[CubaAtual].VSetPoint + AVC.Param[CubaAtual].VIncMax) )		  
			AVC.User1[CubaAtual].SF_TempoSobe = ((AVC.Ccont[CubaAtual].VSetPoint + AVC.Param[CubaAtual].VIncMax) - ((AVC.CcontMcp[CubaAtual].RCicContlBruta * AVL.INominal) + AVC.Param[CubaAtual].Bemf)) / AVC.Ccont[CubaAtual].Kcpwm;
*/
  	      GeraEvento(EV_SMARTFEED, CubaAtual, -1, SF_Pos, AVC.User1[CubaAtual].SF_IncDeriv,
	  		AVC.User1[CubaAtual].SF_TempoSobe, AVC.User1[CubaAtual].SF_IncDerivEA );
		}

		strcpy(ParEv, STR_NULL);
		strcpy(Msg, ScoreGetStr(SCORE_MSG_400));
		if ((EST_AVC(CubaAtual).Ea eq VERDADEIRO) and (AVC.ParUser1[CubaAtual].HabSoproEspec eq VERDADEIRO) and
			(EST_AVC(CubaAtual).Est.OpeSoproEspec ne VERDADEIRO) and
			(AVC.User1[CubaAtual].EstadoSoproEspec eq SOPRO_INICIAL))
		{
		  EST_AVC(CubaAtual).Est.OpeSoproEspec = VERDADEIRO;
		  GeraEvento(SOPRO_ESPECIAL,CubaAtual,-1,"Sinaliza", "Sopro");
		  strcpy(Msg, "Quebrada + Sopro Sinal.");
		  strcpy(ParEv, "+  Sopro");
		}
		if (AVL.HabLogOper)
		  GeraEvento(LOG_OPER_CUBA, CubaAtual, -1, ScoreGetStr(LOG_QUEB_OPE), NomeOper(atoi(Operador)),
					 ScoreGetStr(STR_SINALIZA), "Quebrada", ParEv);

	    if((EST_AVC(CubaAtual).ChaveLocRem eq REMOTO) and
  		   (EST_AVC(CubaAtual).ChaveAutMan eq AUTOMATICO) and
		   (AVC.Param[CubaAtual].HabMovIniQueb eq 1) and
		   (AVC.Param[CubaAtual].TempMovIniQueb > 0) and
			AVC.ParUser1[CubaAtual].HabSmartFeed eq FALSO)
  		{ 
			if( (AVC.User3[CubaAtual].Temperatura <= AVC.ParUser2[CubaAtual].TempMaxInibInc or 
				AVC.ParUser2[CubaAtual].InibIncQuebTemp eq FALSO) and
				((HoraAtual - AVC.Ea[CubaAtual].EaHoraInicio) < 
				((AVC.Param[CubaAtual].EaAtrasoMax - AVC.ParUser1[CubaAtual].LimSupQPrevEa) * 60) ))
			{		
		      MudaAutManCuba(CubaAtual, MANUAL, atoi(Operador));
  		      MudaMoveAnodoCuba(CubaAtual, (double)AVC.Param[CubaAtual].TempMovIniQueb,
	  					    SUBIR_ANODO, atoi(Operador));
		      MudaAutManCuba(CubaAtual, AUTOMATICO, atoi(Operador));
	          	strcat(Msg," + Move Cima");
			}
  		}
		  if ((EST_AVC(CubaAtual).ChaveLocRem eq REMOTO) and
		  	  (EST_AVC(CubaAtual).ChaveAutMan eq AUTOMATICO) and
			   AVC.ParUser1[CubaAtual].HabSmartFeed eq VERDADEIRO and 
			   AVC.ParUser1[CubaAtual].HabMovSmartFeed eq VERDADEIRO and 
			   EST_AVC(CubaAtual).Ea eq FALSO)
		  {
		    MudaAutManCuba(CubaAtual, MANUAL, atoi(Operador));
  		    MudaMoveAnodoCuba(CubaAtual, (double)AVC.User1[CubaAtual].SF_TempoSobe,
	  					    SUBIR_ANODO, atoi(Operador));
		    MudaAutManCuba(CubaAtual, AUTOMATICO, atoi(Operador));
	        strcat(Msg," + Move Cima");
		  }

	  }
	  strcpy(PMsg, Msg);
	}
	++IndCuba;
  }
  AlteracaoTabela(TABELA_EST_AVC);
  LiberaSemaf(SEMAF_AVC);
}

