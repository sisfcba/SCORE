/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: IncRuido.c

	CONTEUDO	: Modulo de Controle das Cubas - MCC - Procedimentos de calculo
                  de incremento devido a instabilidade nas cubas  (ruido rapido
                  e ruido lento).

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	22/09/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
15/02/93 | Correcao calculo ruido rapido (inicializacao RRap6Hs)| Leonel
-------------------------------------------------------------------------------
04/05/93 | Parametrizacao dos incrementos de ruido              | Leonel
-------------------------------------------------------------------------------
04/10/93 | Parametrizacao do periodo de tratamento de ruido rap.| Leonel
-------------------------------------------------------------------------------
22/06/94 | Edicao inicial de migracao para o QNX 4.2			| Leonel
-------------------------------------------------------------------------------
01/03/95 | Parametrizacao do intervalo da janela de ruido rapido| Leonel
-------------------------------------------------------------------------------
03/03/99 | Acrescentada funcao ResetRuido                       | Leonel
         | Alterado tratamento de ContInibeRuido p/ tratar in-  |
         | cremento como 0 e continuar os calculos.             |
-------------------------------------------------------------------------------
09/07/99 | Alterado tratamento de Ruido para que nao contabili- | Robson
         | ze em previsao de efeito.                            |
-------------------------------------------------------------------------------
$Id: IncRuido.c,v 1.1.2.1 2012/09/28 17:09:27 leo Exp $

$Log: IncRuido.c,v $
Revision 1.1.2.1  2012/09/28 17:09:27  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

Revision 1.8  2008/11/27 21:29:07  marcelo
Alterado tratamento de ruido lento para tratar janelas e intervalos configuraveis
da mesma maneira que o tratamento de ruido rapido.

Revision 1.7  2008/07/08 13:28:07  leo
Incluidos novos limites para ruido. De 2 niveis para 5. Os 3 primeiros niveis
sao tratados como FRACO e os 2 ultimos como FORTE na contabilizacao historica.

Revision 1.6  2008/02/07 14:47:07  leo
Correcao no if de tratamento de ruido de corrente.

Revision 1.5  2007/03/01 18:02:33  leo
Correcao de tratamento de manobra de cruzeiro.

Revision 1.4  2007/02/28 22:22:27  leo
Inclusao de tratamento de manobra de cruzeiro.

******************************************************************************/

/*
-------------------------------------------------------------------------------
							Includes
-------------------------------------------------------------------------------
*/
#include	<MccCba.h>
#include	<Prototipos.h>
#include	<Eventos.h>
#include	<time.h>
#include	<math.h>
#include	<string.h>

/*
-------------------------------------------------------------------------------
							Variaveis Globais
-------------------------------------------------------------------------------
*/
/* -- Apontadores para as tabelas comuns -- */
#include	<VarsComum.h>

/*
-------------------------------------------------------------------------------
							Prototipos
-------------------------------------------------------------------------------
*/
void CalcRuidoLento(int Cuba, struct tm *PHoraUltCtrl);
void CalcRuidoRapido(int Cuba, struct tm *PHoraUltCtrl);
int ClassificaRuidoLento(int aCuba, float aRAcum);
int ClassificaRuidoRapido(int aCuba, float aRAcum);

/*
-------------------------------------------------------------------------------
							Funcoes
-------------------------------------------------------------------------------
*/

/*
--------------------------------------------------------------------------------
| IniRuido - Inicializa variaveis referentes ao calculo de incremento de ruido |
|            rapido e lento para a cuba dada.                                  |
--------------------------------------------------------------------------------
*/
void IniRuido(int Cuba)
{
	int	Amostra;

	AVC.Ruido[Cuba].ContInibeRuido=0; /* -- habilita tratamento de ruido -- */
	
	PosicaoGlobal = 93;

	EST_AVC(Cuba).RuidoLent=FALSO;  
	AVC.Ruido[Cuba].RlentCContVal=0;
	AVC.Ruido[Cuba].Rlent6Hs=0; 
	AVC.Ruido[Cuba].Rlent48Hs=0; 
	AVC.Ruido[Cuba].TipoRLent=SEM_RUIDO;
  	for(Amostra=0; Amostra < N_AMOSTRAS_RLENT; ++Amostra)
		AVC.Ruido[Cuba].VetRlent[Amostra]=0;
  	AVC.Ccont[Cuba].IncRlent=0;
  
	EST_AVC(Cuba).RuidoRap=FALSO;
	AVC.Ruido[Cuba].RrapCContVal=0;
	AVC.Ruido[Cuba].Rrap6Hs=0;
	AVC.Ruido[Cuba].Rrap48Hs=0;
	AVC.Ruido[Cuba].TipoRRap=SEM_RUIDO;
	for(Amostra=0; Amostra < N_AMOSTRAS_RRAP; ++Amostra)
		AVC.Ruido[Cuba].VetRrap[Amostra]=0;
	  AVC.Ccont[Cuba].IncRrap=0;

	/* copia parametros de ruido para verificar sua variacao posterior para 
		reiniciar algoritmo */
	AVC.Ruido[Cuba].BackNumJanRLent = AVC.Param[Cuba].NumJanRLent;
	AVC.Ruido[Cuba].BackIntervJanRLent = AVC.Param[Cuba].IntervJanRLent;
	AVC.Ruido[Cuba].BackNumJanRRap = AVC.Param[Cuba].NumJanRRap;
	AVC.Ruido[Cuba].BackIntervJanRRap = AVC.Param[Cuba].IntervJanRRap;
}

/*
--------------------------------------------------------------------------------
| ResetRuido - Reinicializa ultimos acumulados de ruido rapido e lento para a  |
|              a cuba dada.                                                    |
--------------------------------------------------------------------------------
*/
void ResetRuido(int Cuba)
{
	PosicaoGlobal = 94;
	AVC.Ruido[Cuba].RlentCContVal=0;
	AVC.Ruido[Cuba].Rlent6Hs=0;
	AVC.Ruido[Cuba].RrapCContVal=0;
	AVC.Ruido[Cuba].Rrap6Hs=0;
}

/*
--------------------------------------------------------------------------------
| TrataIncRuido - Calcula os incrementos de tensao por ruido lento e rapido    |
|                 para a cuba dada                                             |
--------------------------------------------------------------------------------
*/
void TrataIncRuido(int Cuba)
{
  struct tm *PTime;
  time_t	HoraUltCtrl;
  time_t	HoraAtual;
  char		straux[9];
  int	Amostra;

  /* Verifica se parametros de ruido lento foram alterados para reiniciar algoritmo */
  if ((AVC.Ruido[Cuba].BackNumJanRLent ne AVC.Param[Cuba].NumJanRLent) or
	  (AVC.Ruido[Cuba].BackIntervJanRLent ne AVC.Param[Cuba].IntervJanRLent))
  {
PosicaoGlobal = 95;

    EST_AVC(Cuba).RuidoLent=FALSO;  
    AVC.Ruido[Cuba].RlentCContVal=0;
    AVC.Ruido[Cuba].Rlent6Hs=0; 
    AVC.Ruido[Cuba].Rlent48Hs=0; 
    AVC.Ruido[Cuba].TipoRLent=SEM_RUIDO;
    for(Amostra=0; Amostra < N_AMOSTRAS_RLENT; ++Amostra)
	  AVC.Ruido[Cuba].VetRlent[Amostra]=0;
    AVC.Ccont[Cuba].IncRlent=0;
    /* Atualiza a copia dos parametros de ruido lento */
    AVC.Ruido[Cuba].BackNumJanRLent = AVC.Param[Cuba].NumJanRLent;
    AVC.Ruido[Cuba].BackIntervJanRLent = AVC.Param[Cuba].IntervJanRLent;
  }

  /* Verifica se parametros de ruido rapido foram alterados para reiniciar algoritmo */
  if ((AVC.Ruido[Cuba].BackNumJanRRap ne AVC.Param[Cuba].NumJanRRap) or
      (AVC.Ruido[Cuba].BackIntervJanRRap ne AVC.Param[Cuba].IntervJanRRap))
  {
PosicaoGlobal = 96;

    EST_AVC(Cuba).RuidoRap=FALSO;
    AVC.Ruido[Cuba].RrapCContVal=0;
    AVC.Ruido[Cuba].Rrap6Hs=0;
    AVC.Ruido[Cuba].Rrap48Hs=0;
    AVC.Ruido[Cuba].TipoRRap=SEM_RUIDO;
    for(Amostra=0; Amostra < N_AMOSTRAS_RRAP; ++Amostra)
	  AVC.Ruido[Cuba].VetRrap[Amostra]=0;
    AVC.Ccont[Cuba].IncRrap=0;
    /* Atualiza a copia dos parametros de ruido rapido */
    AVC.Ruido[Cuba].BackNumJanRRap = AVC.Param[Cuba].NumJanRRap;
    AVC.Ruido[Cuba].BackIntervJanRRap = AVC.Param[Cuba].IntervJanRRap;
  }

  /* -- Alteracao -- Robson 09/07/99 -- */
  if ((EST_AVC(Cuba).EfeitoMove eq FALSO) and
	  (EST_AVC(Cuba).EfeitoQueb eq FALSO) and
	  (EST_AVC(Cuba).EfeitoCorr eq FALSO) and
	  (EST_AVC(Cuba).EfeitoEa eq FALSO) and
	  (EST_AVC(Cuba).Ea eq FALSO) and
	  (EST_AVC(Cuba).EaPrev eq FALSO) and
	  (EST_AVC(Cuba).TrataCruzeiro eq FALSO) and
	  ((HoraAtualCtrl-AVC.Cleit[Cuba].HoraUltTPinos) >
		(AVC.Param[Cuba].TEfeitoTPinos*60)) )
  {
	if ((fabs((double)(AVC.CcontMcp[Cuba].ICicContlMedCuba-AVL.INominal)) <= AVL.IdesvMax) and
		  (AVC.CcontMcp[Cuba].IRapCicContl <= AVL.IRapMax))
	{ /* -- Considera o mesmo nivel de ruido anterior em caso de qualquer -- */
	  /* -- disturbio na cuba -- */
	  // Reseta monitoracao
PosicaoGlobal = 97;

	  AVC.User2[Cuba].TIniFalhaCalcRuido = 0;
	  EST_AVC(Cuba).Est.FalhaCalcRuido = FALSO;
	  /* -- Ceifa valor em 2*limite da maior faixa -- */
	  if (AVC.CcontMcp[Cuba].RlentCicContl > (AVC.Param[Cuba].RuidoL[4]*2.0))
		AVC.Ruido[Cuba].RlentCContVal=AVC.Param[Cuba].RuidoL[4]*2.0;
	  else	
		AVC.Ruido[Cuba].RlentCContVal=AVC.CcontMcp[Cuba].RlentCicContl;
	  if (AVC.CcontMcp[Cuba].RrapCicContl > (AVC.Param[Cuba].RuidoR[4]*2.0))
		AVC.Ruido[Cuba].RrapCContVal=AVC.Param[Cuba].RuidoR[4]*2.0;
	  else	
		AVC.Ruido[Cuba].RrapCContVal=AVC.CcontMcp[Cuba].RrapCicContl;
	}
  }
  else
  {
PosicaoGlobal = 98;

	HoraAtual = time(NULL);
	// ja esta com falha ?
	if (AVC.User2[Cuba].TIniFalhaCalcRuido ne 0)
	{
	  if (((HoraAtual - AVC.User2[Cuba].TIniFalhaCalcRuido) > AVC.ParUser1[Cuba].TFalhaRuido) and
		  (EST_AVC(Cuba).Est.FalhaCalcRuido eq FALSO))
	  {
		// falha de calculo de ruido
		strcpy(straux, STR_TRACO);
		// se nao for nenhum dos outros casos, e troca de pinos
		strcpy(straux, ScoreGetStr(SCORE_MSG_2303));//"T. Pinos");
		EST_AVC(Cuba).Est.FalhaCalcRuido = VERDADEIRO;
		if (EST_AVC(Cuba).EfeitoMove eq VERDADEIRO)
		  strcpy(straux, ScoreGetStr(SCORE_MSG_2297));//"Ef. Move");
	    if (EST_AVC(Cuba).EfeitoQueb eq VERDADEIRO)
		  strcpy(straux, ScoreGetStr(SCORE_MSG_2298));//"Ef. Queb");
		if (EST_AVC(Cuba).EfeitoCorr eq VERDADEIRO)
		  strcpy(straux, ScoreGetStr(SCORE_MSG_2299));//"Ef. Corr");
		if (EST_AVC(Cuba).EfeitoEa eq VERDADEIRO) 
		  strcpy(straux, ScoreGetStr(SCORE_MSG_2300));//"Ef. E.A.");
		if (EST_AVC(Cuba).Ea eq VERDADEIRO)
		  strcpy(straux, ScoreGetStr(SCORE_MSG_2301));//"E.A.");
		if (EST_AVC(Cuba).EaPrev eq VERDADEIRO)
		  strcpy(straux, ScoreGetStr(SCORE_MSG_2302));//"Prev. EA");
		if (EST_AVC(Cuba).TrataCruzeiro eq VERDADEIRO)
		  strcpy(straux, "M. Cruz"); // Manobra de cruzeiro
		GeraEvento(FALHARUIDO,Cuba,-1, straux, STR_TRACO, STR_TRACO);
	  }
	}
	else
	{
	  // Inicia monitoracao
	  AVC.User2[Cuba].TIniFalhaCalcRuido = HoraAtual;
	}
  }
PosicaoGlobal = 99;

  HoraUltCtrl=AVL.HoraUltControle;
  PTime=localtime(&HoraUltCtrl);
  CalcRuidoLento(Cuba,PTime);
PosicaoGlobal = 100;

  /* -- calcula ruido rapido -- */
  CalcRuidoRapido(Cuba,PTime);
PosicaoGlobal = 101;

  if ( (AVC.Cleit[Cuba].HoraUltCorr >= HoraUltCtrl) and 
		(AVC.Cleit[Cuba].HoraUltCorr < HoraAtualCtrl) and
		(EST_AVC(Cuba).Corrida eq VERDADEIRO) )
  {
	if (AVC.Ruido[Cuba].ContInibeRuido > 0)
	{
	  if (AVC.Ruido[Cuba].ContInibeRuido < (AVC.ParUser1[Cuba].InibeRuiPosCorr * 30) )
	  {
	    AVC.Ruido[Cuba].ContInibeRuido = AVC.ParUser1[Cuba].InibeRuiPosCorr * 30;
	  }	  
	}
	else
	{
	  AVC.Ruido[Cuba].ContInibeRuido = AVC.ParUser1[Cuba].InibeRuiPosCorr * 30;
	}
  }

  /* trata inibicao de incremento de ruido por tempo como incremento=0 */
  if (AVC.Ruido[Cuba].ContInibeRuido > 0)
  {	/* -- Incremento de ruido desabilitado durante periodo indicado pelo operador -- */
  	AVC.Ruido[Cuba].ContInibeRuido--;
	/* -- Considera incremento como zero -- */
	AVC.Ccont[Cuba].IncRlent=0;
	AVC.Ccont[Cuba].IncRrap=0;
  }

  if(AVC.ParUser2[Cuba].InibIncRRTemp eq VERDADEIRO and
	AVC.User3[Cuba].Temperatura > AVC.ParUser2[Cuba].TempMaxInibInc or
	AVC.Param[Cuba].HabIncRRap eq FALSO)
  {
	AVC.Ccont[Cuba].IncRrap = 0;
  }

  if(AVC.Param[Cuba].HabIncRLent eq FALSO)
  {
	AVC.Ccont[Cuba].IncRlent = 0;
  }

}

/*
--------------------------------------------------------------------------------
| CalcRuidoLento - Calcula ruido lento para a cuba dada com uma janela de 2    |
|                  horas, com sobreposicao de 1 hora.                          |
--------------------------------------------------------------------------------
*/
void CalcRuidoLento(int Cuba, struct tm *PHoraUltCtrl)
{
  int	Amostra, NJanRLent, tipo_ruido;
  float	RlentAcum,NumCiclos48Hs;

PosicaoGlobal = 102;

  /* -- Acumula resistencias lentas -- */
  AVC.Ruido[Cuba].Rlent6Hs=AVC.Ruido[Cuba].Rlent6Hs+AVC.Ruido[Cuba].RlentCContVal;

  /* -- Converte ruido de resistencia para tensao */
   AVC.User2[Cuba].VRLentCCont = (float)(AVC.Ruido[Cuba].RlentCContVal *
									AVC.CcontMcp[Cuba].ICicContlMedCuba*1000);
 
  if ((PHoraAtual->tm_min >= 0) and (PHoraAtual->tm_min <= (2*IntervCicCont)))
  { /* -- HoraAtualCtrl="Hora cheia" com tolerancia de 2 ciclos controle -- */

    if ((24 Mod AVC.Param[Cuba].IntervJanRLent) ne 0)
    {
      AVC.Param[Cuba].IntervJanRLent=6;
      EmiteAlarmeFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_MSG_2370));
    }
PosicaoGlobal = 103;

    if ((PHoraAtual->tm_hour Mod AVC.Param[Cuba].IntervJanRLent) eq 0)
	{ /* -- HoraAtualCtrl="Hora cheia" com tolerancia de 2 ciclos controle -- */
	  if ( not((PHoraAtual->tm_hour eq PHoraUltCtrl->tm_hour) and
			 (PHoraUltCtrl->tm_min >=0) and
			 (PHoraUltCtrl->tm_min <= (2*IntervCicCont))) )
	  { /* -- Ciclo de controle anterior nao estava dentro da faixa de tolerancia -- */
		/* -- Efetua os calculos de ruido a cada intervalo de IntervJanRLent horas -- */
		/* -- Abre espaco no vetor para o novo valor -- */
        //criar N_AMOSTRAS_RLENT de forma semelhante a N_AMOSTRAS_RRAP
		for (Amostra=N_AMOSTRAS_RLENT-1; Amostra >= 1; Amostra--)
PosicaoGlobal = 104;

		  AVC.Ruido[Cuba].VetRlent[Amostra]=AVC.Ruido[Cuba].VetRlent[Amostra-1];
		/* -- Insere valor mais recente -- */
		AVC.Ruido[Cuba].VetRlent[0]=AVC.Ruido[Cuba].Rlent6Hs;
		/* -- Inicializa valor das 6 horas -- */
		AVC.Ruido[Cuba].Rlent6Hs=0;
		/* -- Calcula resistencia lenta das ultimas 48 horas -- */
		NJanRLent = AVC.Param[Cuba].NumJanRLent;
		RlentAcum=0;
		for (Amostra=0; Amostra < NJanRLent; Amostra++)
		  RlentAcum = RlentAcum + AVC.Ruido[Cuba].VetRlent[Amostra];
		/* -- Calcula numero de ciclos de controle no periodo de analise -- */
		NumCiclos48Hs=(AVC.Param[Cuba].IntervJanRLent*60.0*NJanRLent)/IntervCicCont;
		RlentAcum=RlentAcum/NumCiclos48Hs;
		/* -- Guarda na base de dados para log e relatorios -- */
		AVC.Ruido[Cuba].Rlent48Hs=RlentAcum;
	    tipo_ruido = ClassificaRuidoLento(Cuba, RlentAcum);
		switch(tipo_ruido)
		{
	  	  case RUIDO_NIVEL1:
	  	  case RUIDO_NIVEL2:
	  	  case RUIDO_NIVEL3:
	  	  case RUIDO_NIVEL4:
	  	  case RUIDO_NIVEL5:
			if (EST_AVC(Cuba).RuidoLent eq FALSO)
			{
PosicaoGlobal = 105;

		  	  if (AVC.Param[Cuba].HabEvRuido eq VERDADEIRO)
				GeraEvento(EV_RUIDO,Cuba,-1,ScoreGetStr(STR_INICIO),
					ScoreGetStr(TIPO_LENTO),ScoreGetStr(RUI_NIVEL1+(tipo_ruido-1)));
			  EST_AVC(Cuba).RuidoLent=VERDADEIRO;
			  AVC.Ruido[Cuba].HoraInicioRLent=HoraAtualCtrl;
			}
			AVC.Ccont[Cuba].IncRlent=AVC.Param[Cuba].IncRuidoLento[tipo_ruido-1];
			AVC.Ruido[Cuba].TipoRLent=tipo_ruido;
			break;
		  default: /* sem ruido */
			if (EST_AVC(Cuba).RuidoLent eq VERDADEIRO)
			{
			  if (AVC.Param[Cuba].HabEvRuido eq VERDADEIRO)
			  {
				GeraEvento(EV_RUIDO,Cuba,-1,ScoreGetStr(STR_FIM),
						ScoreGetStr(TIPO_LENTO),ScoreGetStr(RUI_NIVEL1+(AVC.Ruido[Cuba].TipoRLent-1)));
			  }
			  EST_AVC(Cuba).RuidoLent=FALSO;
			  AVC.Ccont[Cuba].IncRlent=0;
			  AVC.Ruido[Cuba].TipoRLent=SEM_RUIDO;
			}
			break;
	    }
	  }
	}
  }
}


/*
--------------------------------------------------------------------------------
| CalcRuidoRapido - Calcula ruido rapido para a cuba dada com uma janela defi- |
|                   nida por (NumJanRRap*InterJanRRap), onde o intervalo e'    |
|                   dado por InterJanRRap (entre 2 e 8 horas)                  |
--------------------------------------------------------------------------------
*/
void CalcRuidoRapido(int Cuba, struct tm *PHoraUltCtrl)
{
  int	Amostra, NJanRRap, tipo_ruido;
  float	RrapAcum,NumCiclos48Hs;
PosicaoGlobal = 106;

  /* -- Acumula resistencias rapidas -- */
  AVC.Ruido[Cuba].Rrap6Hs=AVC.Ruido[Cuba].Rrap6Hs+AVC.Ruido[Cuba].RrapCContVal;

  /* -- Converte ruido de resistencia para tensao */
  AVC.User2[Cuba].VRRapCCont	= (float)(AVC.Ruido[Cuba].RrapCContVal *
									AVC.CcontMcp[Cuba].ICicContlMedCuba*1000);
  
  if ((PHoraAtual->tm_min >=0) and (PHoraAtual->tm_min <= (2*IntervCicCont)))
  {
	if ((24 Mod AVC.Param[Cuba].IntervJanRRap) ne 0)
	{
	  AVC.Param[Cuba].IntervJanRRap=6;
	  EmiteAlarmeFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_MSG_217));
	}
PosicaoGlobal = 107;

	if ((PHoraAtual->tm_hour Mod AVC.Param[Cuba].IntervJanRRap) eq 0)
	{ /* -- HoraAtualCtrl="Hora cheia" com tolerancia de 2 ciclos controle -- */
	  if ( not((PHoraAtual->tm_hour eq PHoraUltCtrl->tm_hour) and
			 (PHoraUltCtrl->tm_min >= 0) and
			 (PHoraUltCtrl->tm_min <= (2*IntervCicCont)) ) )
	  { /* -- Ciclo de controle anterior nao estava dentro da faixa de tolerancia -- */
		/* -- Efetua os calculos de ruido a cada intervalo de IntervJanRRap horas -- */
		/* -- Abre espaco no vetor para o novo valor -- */
		for (Amostra=N_AMOSTRAS_RRAP-1; Amostra >= 1; Amostra--)
		  AVC.Ruido[Cuba].VetRrap[Amostra]=AVC.Ruido[Cuba].VetRrap[Amostra-1];
		/* -- Insere valor mais recente -- */
		AVC.Ruido[Cuba].VetRrap[0]=AVC.Ruido[Cuba].Rrap6Hs;
		/* -- Inicializa valor das 6 horas -- */
		AVC.Ruido[Cuba].Rrap6Hs=0;
		/* -- Calcula resistencia rapida das ultimas 48 horas -- */
		NJanRRap = AVC.Param[Cuba].NumJanRRap;
		RrapAcum=0;
		for (Amostra=0; Amostra < NJanRRap; Amostra++)
		  RrapAcum = RrapAcum + AVC.Ruido[Cuba].VetRrap[Amostra];
		/* -- Calcula numero de ciclos de controle no periodo de analise -- */
		NumCiclos48Hs=(AVC.Param[Cuba].IntervJanRRap*60.0*NJanRRap)/IntervCicCont;
		RrapAcum=RrapAcum/NumCiclos48Hs;
		/* -- Guarda na base de dados para log e relatorios -- */
		AVC.Ruido[Cuba].Rrap48Hs=RrapAcum;
		tipo_ruido = ClassificaRuidoRapido(Cuba, RrapAcum);
		switch(tipo_ruido)
		{
	  	  case RUIDO_NIVEL1:
	  	  case RUIDO_NIVEL2:
	  	  case RUIDO_NIVEL3:
	  	  case RUIDO_NIVEL4:
	  	  case RUIDO_NIVEL5:
			if (EST_AVC(Cuba).RuidoRap eq FALSO)
			{
		  	  if (AVC.Param[Cuba].HabEvRuido eq VERDADEIRO)
				GeraEvento(EV_RUIDO,Cuba,-1,ScoreGetStr(STR_INICIO),
					ScoreGetStr(TIPO_RAPIDO),ScoreGetStr(RUI_NIVEL1+(tipo_ruido-1)));
			  EST_AVC(Cuba).RuidoRap=VERDADEIRO;
			  AVC.Ruido[Cuba].HoraInicioRRap=HoraAtualCtrl;
			}
			AVC.Ccont[Cuba].IncRrap=AVC.Param[Cuba].IncRuidoRap[tipo_ruido-1];
			AVC.Ruido[Cuba].TipoRRap=tipo_ruido;
			break;
		  default: /* sem ruido */
			if (EST_AVC(Cuba).RuidoRap eq VERDADEIRO)
			{
			  if (AVC.Param[Cuba].HabEvRuido eq VERDADEIRO)
			  {
				GeraEvento(EV_RUIDO,Cuba,-1,ScoreGetStr(STR_FIM),
						ScoreGetStr(TIPO_RAPIDO),ScoreGetStr(RUI_NIVEL1+(AVC.Ruido[Cuba].TipoRRap-1)));
			  }
			  EST_AVC(Cuba).RuidoRap=FALSO;
			  AVC.Ccont[Cuba].IncRrap=0;
			  AVC.Ruido[Cuba].TipoRRap=SEM_RUIDO;
			}
			break;
	    }
	  }
	}
  }
}

/*
--------------------------------------------------------------------------------
| ClassificaRuidoLento - Classifica o ruido lento de acordo com o nivel.       |
--------------------------------------------------------------------------------
*/
int ClassificaRuidoLento(int aCuba, float aRAcum)
{
  int nivel;
PosicaoGlobal = 108;
  
  for (nivel = 0; nivel < 5; nivel++)
    if (aRAcum < AVC.Param[aCuba].RuidoL[nivel])
	  break;

  return( nivel );
}

/*
--------------------------------------------------------------------------------
| ClassificaRuidoRapido - Classifica o ruido rapido de acordo com o nivel.     |
--------------------------------------------------------------------------------
*/
int ClassificaRuidoRapido(int aCuba, float aRAcum)
{
  int nivel;
  
PosicaoGlobal = 109;

  for (nivel = 0; nivel < 5; nivel++)
    if (aRAcum < AVC.Param[aCuba].RuidoR[nivel])
	  break;

  return( nivel );
}

/* -- fim do arquivo IncRuido.c -- */
