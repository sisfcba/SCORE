/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: PrevEa.c

	CONTEUDO	: Modulo de Controle das Cubas - MCC - Procedimentos do algo-
                  ritmo de Previsao de Efeito Anodico. Versao que utiliza
                  apenas RSuaveDerivH em conjunto com um intervalo de tempo
                  para iniciar a previsao.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 2.0			-		DATA	:	07/09/94

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
07/09/94 | Edicao inicial                                         | Leonel
-------------------------------------------------------------------------------
26/10/94 | Alterado algoritmo para janelas deslisantes            | Leonel
-------------------------------------------------------------------------------
17/08/95 | Adaptacao para o score4.0 no qnx 4                     | Leonel
-------------------------------------------------------------------------------
08/11/95 | Alterada sinalizacao lampada de previsao (todo ciclo)  | Leonel
-------------------------------------------------------------------------------
06/01/96 | Alterada contabilizacao da eficiencia de previsao      | Carlos
-------------------------------------------------------------------------------
10/09/97 | Alterada condicao de entrada de previsao atraves dos   | Carlos
         | parametros DerivInibeMovAlta e DerivInibeMovBaixa.     | Carlos
-------------------------------------------------------------------------------
14/04/98 | Nao entra em previsao durante corrida e troca de pinos | Leonel
         | mas continua os calculos de derivada hist. (para CBA)  |
-------------------------------------------------------------------------------
16/04/98 | Finalizacao de quebrada preventiva na previsao         | Carlos
-------------------------------------------------------------------------------
28/06/99 | Incluido tratamento de booster de corrente			  | Carlos
-------------------------------------------------------------------------------
02/02/01 | Desliga lampada no fim de quebrada preventiva          | Carlos
-------------------------------------------------------------------------------
******************************************************************************/

/**** #define		ATIVA_DEPURACAO  ****/
/* -- Qdo. definido inibe previsao quando em corrida, quebrada e movimentacao -- */
/**** #define		INCLUI_INIBICAO_CORRIDA *****/

/* -- Valor maximo assumido por KSuave -- */
#define		MAX_KSUAVE			5

/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include	<MccCba.h>
#include	<Eventos.h>
#include	<Prototipos.h>
#include	<math.h>
#ifdef		ATIVA_DEPURACAO
	#include <stdio.h>
	#include <time.h>
#endif

/*
-------------------------------------------------------------------------------
                           Variaveis Globais
-------------------------------------------------------------------------------
*/
/* -- Apontadores para as tabelas comuns -- */
#include	<VarsComum.h>

#ifdef		ATIVA_DEPURACAO
  FILE	*PDepura=NULL;
#endif

/*
-------------------------------------------------------------------------------
                           Prototipos
-------------------------------------------------------------------------------
*/
void CalcRSuave(int Cuba);
void CalcHoraPrevEa(int Cuba);
void AnalisaPrevisao(int Cuba);
void AnalisaPrevisaoAC(int Cuba);
void AnalisaFimPrev(int Cuba);
void AnalisaInibeMov(int Cuba);

/*
-------------------------------------------------------------------------------
							Funcoes
-------------------------------------------------------------------------------
*/


/*
--------------------------------------------------------------------------------
| IniPrevisaoEa - Inicializa variaveis referentes a previsao de EA da cuba dada|
--------------------------------------------------------------------------------
*/
void IniPrevisaoEa(int Cuba)
{
	PosicaoGlobal = 110;
	/* -- inicializa variaveis da previsao de EA -- */
	AVC.Ea[Cuba].RSuave=0.0;
	AVC.Ea[Cuba].KSuave=MAX_KSUAVE;
	AVC.Ea[Cuba].RSuaveDeriv=0.0;
	AVC.Ea[Cuba].RSuaveDerivH=0.0;
	AVC.User2[Cuba].RSuaveDerivHAnt=0.0;
	AVC.User2[Cuba].DerivHTeste = 0.0;
	AVC.Ea[Cuba].DerivHMaxPrevEa=-1.0;
	AVC.Ea[Cuba].CiclosFimPrev=AVC.Param[Cuba].IntervFimEaPrevDeriv/IntervCicCont;
	AVC.Ea[Cuba].CiclosIniPrev=AVC.Param[Cuba].IntervEaPrevDeriv/IntervCicCont;
	AVC.Ea[Cuba].CiclosInibeMov=AVC.Param[Cuba].IntervDerivInibeMov/IntervCicCont;
	EST_AVC(Cuba).EaPrev=FALSO;
	EST_AVC(Cuba).InibeMovEaPrev=FALSO;
	AVC.User2[Cuba].CiclosIniPrevAc = 0;
	AVC.User2[Cuba].RSuavePrevAc[0] = 0.0;
	AVC.User2[Cuba].RSuavePrevAc[1] = 0.0;
	AVC.User2[Cuba].RSuavePrevAc[2] = 0.0;
	AVC.User2[Cuba].RSuavePrevAc[3] = 0.0;
	AVC.User2[Cuba].RSuavePrevAc[4] = 0.0;

	/* -- Estado da lampada de Ea -- */
	AvcLocal[Cuba].IndicouPrevisao=FALSO;
	AvcLocal[Cuba].IndicouQPrev=FALSO;
	#ifdef		ATIVA_DEPURACAO
		if (PDepura eq NULL)
		{
			if ((PDepura=fopen("/dev/con6","w")) eq NULL)
			{
				fprintf(stderr,"Mcc->PrevEa: Falha fopen!\n");
				exit(EXIT_FAILURE);
			}
			else
				fprintf(PDepura,"Mcc->PrevEa: Abriu canal para depuracao! \n");
		}
	#endif
}

/*
--------------------------------------------------------------------------------
| PrevisaoEa - Faz a previsao de efeito anodico para a cuba dada.              |
--------------------------------------------------------------------------------
*/
void PrevisaoEa(int Cuba)
{
  if (EST_AVC(Cuba).EfeitoEa eq FALSO)
  {	/* -- nao esta em efeito anodico -- */
    CalcRSuave(Cuba);	/* -- Calcula Rsuave atual e derivada -- */
#ifdef	INCLUI_INIBICAO_CORRIDA
    if ((EST_AVC(Cuba).Corrida eq FALSO)
		and (EST_AVC(Cuba).Quebrada eq FALSO)
		and (AVC.Ccont[Cuba].HoraUltMove <= AVC.Ea[Cuba].EaPrevT0) )
	{
#endif
PosicaoGlobal = 111;

	  /* -- Analise de inicio de previsao por aceleracao -- */
	  if (AVC.ParUser1[Cuba].HabPrevAc eq VERDADEIRO)
	    AnalisaPrevisaoAC(Cuba);

	  /* -- Analise de inicio de previsao -- */
	  AnalisaPrevisao(Cuba);

	  /* -- Analise de fim de previsao -- */
	  AnalisaFimPrev(Cuba);

	  /* -- Analise para inibir movimentacao -- */
	  AnalisaInibeMov(Cuba);

#ifdef CBA_120KAII_III
	  if (EST_AVC(Cuba).Est.QuebPrev eq VERDADEIRO)
	  { /* -- sinaliza queb. prev. a cada ciclo de controle -- */
		ComandaLampEa(Cuba,PISCAR_RAPIDO);
		AvcLocal[Cuba].IndicouQPrev = VERDADEIRO;
	  }
	  else
	  {
#endif
PosicaoGlobal = 112;

		/* -- sinaliza previsao a cada ciclo de controle -- */
		if (EST_AVC(Cuba).EaPrev eq VERDADEIRO)
		{
		  /* -- Comanda lampada de indicacao de previsao para piscar -- */
		  ComandaLampEa(Cuba,PISCAR);
		  AvcLocal[Cuba].IndicouPrevisao = VERDADEIRO;
		}
#ifdef CBA_120KAII_III
	  }
#endif

#ifdef	INCLUI_INIBICAO_CORRIDA
	}
    else	/* -- Durante corrida -- */
    {
	  if (EST_AVC(Cuba).EaPrev eq VERDADEIRO)
	  {
PosicaoGlobal = 113;

		EST_AVC(Cuba).EaPrev=FALSO;
		EST_AVC(Cuba).EaPrevVirada=FALSO;
		VRapCicCtrl = AVC.Ea[Cuba].DerivHMaxPrevEa*1e6;
		/* Inicio Alteracao - Carlos - 23/06/99 */
		/* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
		VAlvo=AVC.Ccont[Cuba].RAlvo * AVC.Ccont[Cuba].INominalCuba + AVC.Param[Cuba].Bemf;
		VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba + AVC.Param[Cuba].Bemf;
#else
		VAlvo=AVC.Ccont[Cuba].RAlvo * AVL.INominal + AVC.Param[Cuba].Bemf;
		VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal + AVC.Param[Cuba].Bemf;
#endif
		/* Fim Alteracao - Carlos - 23/06/99 */


		GeraEvento(FIM_PREV_EA,Cuba,-1,AVC.Ea[Cuba].RSuaveDerivH*1e6,
				VRapCicCtrl,VCicCont,STR_TRACO,VAlvo);
		/*-- Contabiliza fim previsao na ocorrencia de corrida --*/
		/*-- quebrada, ou movimentacao manual de anodo         --*/
		SUPERV_AVC(Cuba).NumFimOkPrevDia++;
		SUPERV_AVC_TURNO(Cuba).NumFimOkPrevDia++;
	  }
	  if (AvcLocal[Cuba].IndicouPrevisao eq VERDADEIRO)
	  {
		/* -- Apaga lampada de indicacao de previsao/efeito anodico -- */
		ComandaLampEa(Cuba,DESLIGAR);
		AvcLocal[Cuba].IndicouPrevisao=FALSO;
	  }
	  /* -- Reinicializa derivada historica -- */
	  AVC.Ea[Cuba].RSuaveDerivH=0;
	  AVC.User2[Cuba].DerivHTeste=0;

	  /* -- inicializa variaveis da previsao de EA -- */
	  AVC.Ea[Cuba].DerivHMaxPrevEa=-1.0;
	  AVC.Ea[Cuba].CiclosIniPrev=AVC.Param[Cuba].IntervEaPrevDeriv/IntervCicCont;
	  AVC.Ea[Cuba].CiclosInibeMov=AVC.Param[Cuba].IntervDerivInibeMov/IntervCicCont;
	}
#endif
  }
  else		/* -- esta em Efeito Anodico -- */
  {
	/* -- Inicializa variaveis da previsao -- */
	IniPrevisaoEa(Cuba);
  }
}


/*
--------------------------------------------------------------------------------
| CalcRSuave - Calcula Resistencia suavizada, derivada instantanea e historica |
|              da curva de resistencia suavizada da cuba dada para serem utili-|
|              das pelo algoritmo de previsao de Efeito Anodico.               |
--------------------------------------------------------------------------------
*/
void CalcRSuave(int Cuba)
{
	float	RSuaveTmp,RSuaveAntTmp, DerivCCont;
	int TmpInterv1,TmpInterv2;

	PosicaoGlobal = 114;

	/* -- Verifica se houve movimentacao no ultimo ciclo de controle -- */
	/* -- com janela de 1/4 de ciclo -- */
	TmpInterv1=75*IntervCicCont;
	TmpInterv2=15*IntervCicCont;

	if (((HoraAtualCtrl-AVC.Ccont[Cuba].HoraUltMove) < TmpInterv1) and
		((HoraAtualCtrl-AVC.Ccont[Cuba].HoraUltMove) >= TmpInterv2) )
		/* -- moveu anodo no ciclo anterior -- */
		AVC.Ea[Cuba].KSuave=0;

	if (((HoraAtualCtrl-AVC.Cleit[Cuba].HoraUltCorr) < TmpInterv1) and
		((HoraAtualCtrl-AVC.Cleit[Cuba].HoraUltCorr) >= TmpInterv2) )
		/* -- houve corrida dentro do ultimo ciclo de controle -- */
		AVC.Ea[Cuba].KSuave=0;

	/* -- salva RSuave anterior -- */
	RSuaveAntTmp=AVC.Ea[Cuba].RSuave;

	/* -- inicializa RSuave -- */
	RSuaveTmp=AVC.CcontMcp[Cuba].RCicContlBruta;

	if (RSuaveAntTmp eq 0)
		/* -- Na primeira vez derivada sera zero -- */
		RSuaveAntTmp=RSuaveTmp;

  	if (AVC.Ea[Cuba].KSuave > 2)
  	{
		PosicaoGlobal = 115;

		/* -- Calcula derivada instantanea em uohms/hora -- */
		DerivCCont=((RSuaveTmp-RSuaveAntTmp)/IntervCicCont)*60.0;
		/* Verifica se derivada dentro dos limites max e min */
		if (DerivCCont > AVC.Param[Cuba].RSuaveDerivMax)
	  		AVC.Ea[Cuba].RSuaveDeriv=AVC.Param[Cuba].RSuaveDerivMax;
		else
	  		if (DerivCCont < AVC.Param[Cuba].RSuaveDerivMin)
				AVC.Ea[Cuba].RSuaveDeriv=AVC.Param[Cuba].RSuaveDerivMin;
	  		else
				AVC.Ea[Cuba].RSuaveDeriv=DerivCCont;
  	}

	/* -- salva RSuave -- */
	AVC.Ea[Cuba].RSuave=RSuaveTmp;

	/* -- salva RSuave anterior -- */
	AVC.Ea[Cuba].RSuaveAnt=RSuaveAntTmp;

	/* -- Calcula derivada historica -- */
	AVC.User2[Cuba].RSuaveDerivHAnt = AVC.Ea[Cuba].RSuaveDerivH;
	AVC.Ea[Cuba].RSuaveDerivH=AVC.Param[Cuba].KSuaveDeriv*AVC.Ea[Cuba].RSuaveDerivH+
						(1-AVC.Param[Cuba].KSuaveDeriv)*AVC.Ea[Cuba].RSuaveDeriv;

	AVC.User2[Cuba].DerivHTeste= 0.96 * AVC.User2[Cuba].DerivHTeste+
						(1-0.96)*AVC.Ea[Cuba].RSuaveDeriv;

	if (AVC.Ea[Cuba].KSuave < MAX_KSUAVE)
		AVC.Ea[Cuba].KSuave++;
}

/*
--------------------------------------------------------------------------------
| AnalisaPrevisao - Verifica valor minimo da derivada historica no periodo de  |
|                   analise para indicacao de previsao.                        |
--------------------------------------------------------------------------------
*/
void AnalisaPrevisao(int Cuba)
{
  float VAlvo, VCicCont;

#ifdef	CBA_120KAII_III
  if ((AVC.Ea[Cuba].RSuaveDerivH >= AVC.Param[Cuba].EaPrevDeriv) and
	  (EST_AVC(Cuba).Corrida eq FALSO) and
	  ((HoraAtualCtrl-AVC.Cleit[Cuba].HoraUltTPinos) >
		(AVC.Param[Cuba].TEfeitoTPinos*60)) and
	  (EST_AVC(Cuba).TrataCruzeiro eq FALSO) )
#else
  if (AVC.Ea[Cuba].RSuaveDerivH >= AVC.Param[Cuba].EaPrevDeriv)
#endif
  {
	/* -- O valor maximo sera' utilizado para classificacao do EA -- */
	if (AVC.Ea[Cuba].RSuaveDerivH > AVC.Ea[Cuba].DerivHMaxPrevEa)
	  AVC.Ea[Cuba].DerivHMaxPrevEa=AVC.Ea[Cuba].RSuaveDerivH;
	/* -- Verifica se completou periodo de analise para previsao -- */
	AVC.Ea[Cuba].CiclosIniPrev--;
	if (AVC.Ea[Cuba].CiclosIniPrev eq 0)
	{
	  if (EST_AVC(Cuba).EaPrev eq VERDADEIRO)
	  {
PosicaoGlobal = 116;

		/* -- Calcula hora prevista de ocorrencia do EA -- */
		CalcHoraPrevEa(Cuba);
	  }
	  else
	  { /* -- inicio de previsao -- */
PosicaoGlobal = 117;

		EST_AVC(Cuba).EaPrev=VERDADEIRO;
		EST_AVC(Cuba).EaPrevVirada=VERDADEIRO;
		/* -- hora de inicio da previsao -- */
		AVC.Ea[Cuba].EaPrevT0=HoraAtualCtrl;
		/* -- Calcula hora prevista de ocorrencia do EA -- */
		CalcHoraPrevEa(Cuba);

		/* Inicio Alteracao - Carlos - 23/06/99 */
		/* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
		VAlvo=AVC.Ccont[Cuba].RAlvo * AVC.Ccont[Cuba].INominalCuba + AVC.Param[Cuba].Bemf;
		VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba + AVC.Param[Cuba].Bemf;
#else
		VAlvo=AVC.Ccont[Cuba].RAlvo * AVL.INominal + AVC.Param[Cuba].Bemf;
		VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal + AVC.Param[Cuba].Bemf;
#endif
		/* Fim Alteracao - Carlos - 23/06/99 */
	    
		GeraEvento(INICIO_PREV_EA,Cuba,-1,AVC.Ea[Cuba].RSuaveDerivH*1e6,
			STR_TRACO,VCicCont,STR_TRACO,VAlvo);
		/*-- Contabiliza inicio previsao para calcular sua eficiencia --*/
		SUPERV_AVC(Cuba).NumPrevEaDia++;
		SUPERV_AVC_TURNO(Cuba).NumPrevEaDia++;
	  }
	  /* -- inicializa variaveis da previsao de EA -- */
	  AVC.Ea[Cuba].DerivHMaxPrevEa=AVC.Ea[Cuba].RSuaveDerivH;
	  AVC.Ea[Cuba].CiclosIniPrev=AVC.Param[Cuba].IntervEaPrevDeriv/IntervCicCont;
	}
  }
  else
  {
PosicaoGlobal = 118;

	/* -- inicializa variaveis da previsao de EA -- */
	if (EST_AVC(Cuba).EaPrev eq FALSO)
	  AVC.Ea[Cuba].DerivHMaxPrevEa=-1.0;
	AVC.Ea[Cuba].CiclosIniPrev=AVC.Param[Cuba].IntervEaPrevDeriv/IntervCicCont;
  }
}

/*
--------------------------------------------------------------------------------
| AnalisaFimPrev - Verifica valor maximo da derivada historica no periodo de   |
|                  analise para indicacao de fim de previsao.                  |
--------------------------------------------------------------------------------
*/
void AnalisaFimPrev(int Cuba)
{
  float VAlvo, VCicCont, VRapCicCont;

  if (AVC.Ea[Cuba].RSuaveDerivH < AVC.Param[Cuba].EaPrevDerivFim)
  {
PosicaoGlobal = 118;

	/* -- Verifica se completou periodo de analise para previsao -- */
	AVC.Ea[Cuba].CiclosFimPrev--;
	if (AVC.Ea[Cuba].CiclosFimPrev eq 0)
	{
	  AVC.Ea[Cuba].CiclosFimPrev=AVC.Param[Cuba].IntervFimEaPrevDeriv/IntervCicCont;
	  if (EST_AVC(Cuba).EaPrev eq VERDADEIRO)
	  {
		EST_AVC(Cuba).EaPrev=FALSO;
		EST_AVC(Cuba).EaPrevVirada=FALSO;
		VRapCicCont=AVC.Param[Cuba].EaPrevDerivFim*1e6;

		/* Inicio Alteracao - Carlos - 23/06/99 */
		/* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
		VAlvo=AVC.Ccont[Cuba].RAlvo * AVC.Ccont[Cuba].INominalCuba + AVC.Param[Cuba].Bemf;
		VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba + AVC.Param[Cuba].Bemf;
#else
		VAlvo=AVC.Ccont[Cuba].RAlvo * AVL.INominal + AVC.Param[Cuba].Bemf;
		VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal + AVC.Param[Cuba].Bemf;
#endif
		/* Fim Alteracao - Carlos - 23/06/99 */

		GeraEvento(FIM_PREV_EA,Cuba,-1,AVC.Ea[Cuba].RSuaveDerivH*1e6,
				VRapCicCont,VCicCont,STR_TRACO,VAlvo);


#ifdef	INCLUI_INIBICAO_CORRIDA
		if ((EST_AVC(Cuba).Corrida eq VERDADEIRO) or
			(EST_AVC(Cuba).Quebrada eq VERDADEIRO) or
			(AVC.Ccont[Cuba].HoraUltMove > AVC.Ea[Cuba].EaPrevT0))
#else
		if ((EST_AVC(Cuba).Quebrada eq VERDADEIRO) or
			(AVC.Cleit[Cuba].HoraUltQueb > AVC.Ea[Cuba].EaPrevT0))
#endif
		{ /*-- Contabiliza fim previsao na ocorrencia de corrida --*/
		  /*-- quebrada, ou movimentacao manual de anodo         --*/
		  SUPERV_AVC(Cuba).NumFimOkPrevDia++;
		  SUPERV_AVC_TURNO(Cuba).NumFimOkPrevDia++;
		  if (EST_AVC(Cuba).Est.QuebPrev eq VERDADEIRO)
		  {
PosicaoGlobal = 119;

			EST_AVC(Cuba).Est.QuebPrev = FALSO;

			GeraEvento(FIM_QUEB_PREV, Cuba, -1, "Previsao", "Com Queb");

			if (AvcLocal[Cuba].IndicouQPrev eq VERDADEIRO)
			{
			  /* -- Apaga lampada de indicacao de quebrada preventiva -- */
			  ComandaLampEa(Cuba,DESLIGAR);
			  AvcLocal[Cuba].IndicouQPrev=FALSO;
			}

			/*-- Contabiliza previsao terminada por queb. prev. --*/
			AVC.User1[Cuba].NumPrevQPrev += 1;
			SUPERV_AVC(Cuba).Sup.NumPrevQPrev += 1;
			SUPERV_AVC_TURNO(Cuba).Sup.NumPrevQPrev += 1;

			/*-- Contabiliza quebrada preventiva --*/
			AVC.User1[Cuba].NumQuebPrev += 1;
			SUPERV_AVC(Cuba).Sup.NumQuebPrev += 1;
			SUPERV_AVC_TURNO(Cuba).Sup.NumQuebPrev += 1;

			/*-- Contabiliza duracao da quebrada preventiva --*/
			SUPERV_AVC(Cuba).Sup.ContDurQPrev += AVC.User1[Cuba].ContDurQPrev;
			SUPERV_AVC_TURNO(Cuba).Sup.ContDurQPrev += AVC.User1[Cuba].ContDurQPrev;
		  }
		}
		else
		{
		  if (EST_AVC(Cuba).Est.QuebPrev eq VERDADEIRO)
		  {
			EST_AVC(Cuba).Est.QuebPrev = FALSO;
			GeraEvento(FIM_QUEB_PREV, Cuba, -1, "Previsao", "Sem Queb");

PosicaoGlobal = 120;

			if (AvcLocal[Cuba].IndicouQPrev eq VERDADEIRO)
			{
			  /* -- Apaga lampada de indicacao de quebrada preventiva -- */
			  ComandaLampEa(Cuba,DESLIGAR);
			  AvcLocal[Cuba].IndicouQPrev=FALSO;
			}

			/*-- Contabiliza quebrada preventiva --*/
			AVC.User1[Cuba].NumQuebPrev += 1;
			SUPERV_AVC(Cuba).Sup.NumQuebPrev += 1;
			SUPERV_AVC_TURNO(Cuba).Sup.NumQuebPrev += 1;

			/*-- Contabiliza duracao da quebrada preventiva --*/
			SUPERV_AVC(Cuba).Sup.ContDurQPrev += AVC.User1[Cuba].ContDurQPrev;
			SUPERV_AVC_TURNO(Cuba).Sup.ContDurQPrev += AVC.User1[Cuba].ContDurQPrev;
		  }
		}
	  }
	  if (AvcLocal[Cuba].IndicouPrevisao eq VERDADEIRO)
	  {
PosicaoGlobal = 121;

		/* -- Apaga lampada de indicacao de previsao/efeito anodico -- */
		ComandaLampEa(Cuba,DESLIGAR);
		AvcLocal[Cuba].IndicouPrevisao=FALSO;
	  }
	}
  }
  else
  {
PosicaoGlobal = 122;

	/* -- inicializa variaveis da previsao de EA -- */
	AVC.Ea[Cuba].CiclosFimPrev=AVC.Param[Cuba].IntervFimEaPrevDeriv/IntervCicCont;
  }
}

/*
--------------------------------------------------------------------------------
| AnalisaInibeMov - Verifica valor maximo da derivada historica no periodo de  |
|                   analise para inibir movimentacao de anodo.                 |
--------------------------------------------------------------------------------
*/
void AnalisaInibeMov(int Cuba)
{
  float VAlvo, VCicCont;

  /* -- Verifica se completou periodo de analise -- */
  if ((AVC.Ea[Cuba].RSuaveDerivH <= AVC.Param[Cuba].DerivInibeMovAlta) and
	  (AVC.Ea[Cuba].RSuaveDerivH >= AVC.Param[Cuba].DerivInibeMovBaixa))
  {
	AVC.Ea[Cuba].CiclosInibeMov--;
	if (AVC.Ea[Cuba].CiclosInibeMov eq 0)
	{
PosicaoGlobal = 123;

	  AVC.Ea[Cuba].CiclosInibeMov=AVC.Param[Cuba].IntervDerivInibeMov/IntervCicCont;
	  if (EST_AVC(Cuba).InibeMovEaPrev eq VERDADEIRO)
	  { /* -- Habilita movimentacao se ficou dentro da faixa no periodo -- */
		EST_AVC(Cuba).InibeMovEaPrev=FALSO;
		VAlvo=AVC.Ccont[Cuba].VAlvo;

		/* Inicio Alteracao - Carlos - 23/06/99 */
		/* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
		VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba + AVC.Param[Cuba].Bemf;
#else
		VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal + AVC.Param[Cuba].Bemf;
#endif
		/* Fim Alteracao - Carlos - 23/06/99 */


		GeraEvento(FIM_INIBE_MOV,Cuba,-1,AVC.Ea[Cuba].RSuaveDerivH*1e6,
				STR_TRACO,VCicCont,STR_TRACO,VAlvo);
	  }
	}
  }
  else
  {
PosicaoGlobal = 124;

	AVC.Ea[Cuba].CiclosInibeMov=AVC.Param[Cuba].IntervDerivInibeMov/IntervCicCont;
	if (EST_AVC(Cuba).InibeMovEaPrev eq FALSO)
	{ /* -- Inibe movimentacao se fora da faixa -- */
	  EST_AVC(Cuba).InibeMovEaPrev=VERDADEIRO;
	  VAlvo=AVC.Ccont[Cuba].VAlvo;

	  /* Inicio Alteracao - Carlos - 23/06/99 */
	  /* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
	  VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba + AVC.Param[Cuba].Bemf;
#else
	  VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal + AVC.Param[Cuba].Bemf;
#endif
	  /* Fim Alteracao - Carlos - 23/06/99 */

	  GeraEvento(INI_INIBE_MOV,Cuba,-1,AVC.Ea[Cuba].RSuaveDerivH*1e6,
				STR_TRACO,VCicCont,STR_TRACO,VAlvo);
	}
  }
}

/*
--------------------------------------------------------------------------------
| CalcHoraPrevEa - Calcula hora prevista de ocorrencia do Efeito Anodico para  |
|                  a cuba dada.                                                |
--------------------------------------------------------------------------------
*/
void CalcHoraPrevEa(int Cuba)
{
PosicaoGlobal = 125;

  /* -- Indica previsao se ainda nao indicou -- */
  AVC.Ea[Cuba].EaHoraPrev = HoraAtualCtrl;
}
/*
--------------------------------------------------------------------------------
| AnalisaPrevisaoAC - Verifica a aceleracao da derivada em relacao ao periodo  |
 					  parametrizado e sinaliza previsao                        |
--------------------------------------------------------------------------------
*/
void AnalisaPrevisaoAC(int Cuba)
{
  float VAlvo, VCicCont;
  float MediaAc;
  int i;

  MediaAc = 0.0;

  if ((AVC.Ea[Cuba].RSuaveDerivH >= AVC.ParUser1[Cuba].EaPrevMinAc) and
	  (EST_AVC(Cuba).Corrida eq FALSO) and
	  ((HoraAtualCtrl-AVC.Cleit[Cuba].HoraUltTPinos) >
		(AVC.Param[Cuba].TEfeitoTPinos*60)) and
	  (EST_AVC(Cuba).TrataCruzeiro eq FALSO) )
  {
	/* -- O valor maximo sera' utilizado para classificacao do EA -- */
	if (AVC.Ea[Cuba].RSuaveDerivH > AVC.Ea[Cuba].DerivHMaxPrevEa)
	  AVC.Ea[Cuba].DerivHMaxPrevEa=AVC.Ea[Cuba].RSuaveDerivH;

	AVC.User2[Cuba].CiclosIniPrevAc++;

	for(i=4; i>0 ; i--)
	{	
	  AVC.User2[Cuba].RSuavePrevAc[i]  = AVC.User2[Cuba].RSuavePrevAc[i-1];
	}

	AVC.User2[Cuba].RSuavePrevAc[0] = AVC.Ea[Cuba].RSuaveDerivH - 
											AVC.User2[Cuba].RSuaveDerivHAnt;

	if ( AVC.User2[Cuba].CiclosIniPrevAc >= AVC.ParUser1[Cuba].EaPrevCiclosAc ) 
	{
	  for(i=0 ; i< AVC.ParUser1[Cuba].EaPrevCiclosAc ; i++)
	  {
		MediaAc += AVC.User2[Cuba].RSuavePrevAc[i];
	  }
	  MediaAc = MediaAc / AVC.ParUser1[Cuba].EaPrevCiclosAc;

	  if ( MediaAc >= AVC.ParUser1[Cuba].EaPrevAc )
	  {
	    if (EST_AVC(Cuba).EaPrev eq VERDADEIRO)
	    {
PosicaoGlobal = 116;

		  /* -- Calcula hora prevista de ocorrencia do EA -- */
		  CalcHoraPrevEa(Cuba);
  	    }
	    else
	    { /* -- inicio de previsao -- */
PosicaoGlobal = 117;

		  EST_AVC(Cuba).EaPrev=VERDADEIRO;
		  EST_AVC(Cuba).EaPrevVirada=VERDADEIRO;
		  /* -- hora de inicio da previsao -- */
		  AVC.Ea[Cuba].EaPrevT0=HoraAtualCtrl;
		  /* -- Calcula hora prevista de ocorrencia do EA -- */
		  CalcHoraPrevEa(Cuba);

		  /* Inicio Alteracao - Carlos - 23/06/99 */
		  /* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
		  VAlvo=AVC.Ccont[Cuba].RAlvo * AVC.Ccont[Cuba].INominalCuba + AVC.Param[Cuba].Bemf;
		  VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba + AVC.Param[Cuba].Bemf;
#else
		  VAlvo=AVC.Ccont[Cuba].RAlvo * AVL.INominal + AVC.Param[Cuba].Bemf;
		  VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal + AVC.Param[Cuba].Bemf;
#endif
		  /* Fim Alteracao - Carlos - 23/06/99 */


		  GeraEvento(INICIO_PREV_EA,Cuba,-1,AVC.Ea[Cuba].RSuaveDerivH*1e6,
			STR_TRACO,VCicCont,STR_TRACO,VAlvo);
		  /*-- Contabiliza inicio previsao para calcular sua eficiencia --*/
		  SUPERV_AVC(Cuba).NumPrevEaDia++;
		  SUPERV_AVC_TURNO(Cuba).NumPrevEaDia++;
	    }
	    /* -- inicializa variaveis da previsao de EA -- */
	    AVC.Ea[Cuba].DerivHMaxPrevEa=AVC.Ea[Cuba].RSuaveDerivH;
 	  }
	}
  }
  else
  {
PosicaoGlobal = 118;
	/* -- inicializa variaveis da previsao de EA -- */
	AVC.User2[Cuba].CiclosIniPrevAc = 0;
	AVC.User2[Cuba].RSuavePrevAc[0] = 0.0;
	AVC.User2[Cuba].RSuavePrevAc[1] = 0.0;
	AVC.User2[Cuba].RSuavePrevAc[2] = 0.0;
	AVC.User2[Cuba].RSuavePrevAc[3] = 0.0;
	AVC.User2[Cuba].RSuavePrevAc[4] = 0.0;
  }
}

/* -- fim do arquivo PrevEaNovo.c -- */
