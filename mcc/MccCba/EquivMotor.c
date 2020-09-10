/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: EquivMotor.c

	CONTEUDO	: Modulo de Controle das Cubas - MCC - Procedimentos relativos
                  aos calculos do algoritmo adaptativo do equivalente motor.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	17/09/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
23/11/92 | Correcao na funcao CalcEquivMotor no calculo da du-  | Leonel
         | racao.                                               |
-------------------------------------------------------------------------------
04/12/92 | Alteracao da duracao de movimentacao de int p/ float | Leonel
-------------------------------------------------------------------------------
05/01/93 | Acrescentado tratamento para confirmacao de movimen- | Leonel
         | tacao de anodo.                                      |
-------------------------------------------------------------------------------
04/05/93 | Alterada geracao do evento de falha_movimentacao para| Leonel
         | indicar nao confirmacao de movimentacao automatica.  |
-------------------------------------------------------------------------------
22/06/94 | Edicao inicial de migracao para o QNX 4.2			| Leonel
-------------------------------------------------------------------------------
21/09/94 | Inclusao da contabilizacao de falha de movimentacao.	| Carlos
-------------------------------------------------------------------------------
21/03/95 | Tratamento de falhas de movimentacao (coloca cuba em | Leonel
         | manual apos 3 falhas).                               |
-------------------------------------------------------------------------------
25/06/99 | Incluido tratamento de booster de corrente			| Carlos
-------------------------------------------------------------------------------
01/03/02 | Correcao: valor absoluto do erro para comparacao     | Leonel
-------------------------------------------------------------------------------
25/08/04 | Correcao: Atualiza Kpwm com tipico qdo alg. desabil. | Leonel
-------------------------------------------------------------------------------
$Id: EquivMotor.c,v 1.1.2.1 2012/09/28 17:09:27 leo Exp $

$Log: EquivMotor.c,v $
Revision 1.1.2.1  2012/09/28 17:09:27  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

Revision 1.3  2008/02/28 18:58:19  leo
Limita tratamento de erro de confirmacao de movimentacao para quando nao
esta em EA. Durante EA confirmacao eh verificada pela tabela de EA.

Revision 1.2  2004/08/25 18:22:47  leo
Atualiza variavel kxpwm com kxpwmtipico quando algoritmo de ajuste do equivalente
motor esta desabilitado (kxpwmtipico = minkxpwm). (x = b ou c)

******************************************************************************/
/*
-------------------------------------------------------------------------------
                           Defines
-------------------------------------------------------------------------------
*/
#ifdef	ALBRAS
  #define		MAX_KBPWM	350e-9
  #define		MAX_KCPWM	350e-9
#else
  #define		MAX_KBPWM	500e-9
  #define		MAX_KCPWM	500e-9
#endif

/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include	<MccCba.h>
#include	<Eventos.h>
#include	<Prototipos.h>
#include	<math.h>
#include	<time.h>

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
void AjustaEqMotor(int Cuba);
#ifdef	MANUAL_APOS_FALHA_MOVE
  void trata_erro(int cuba);
#endif

/*
-------------------------------------------------------------------------------
							Funcoes
-------------------------------------------------------------------------------
*/

/*
--------------------------------------------------------------------------------
| IniEquivMotor - Inicializa variaveis referentes aos calculos do algoritmo do |
|                 equivalente motor.                                           |
--------------------------------------------------------------------------------
*/
void IniEquivMotor(int Cuba)
{
	/* Variaveis locais */
	/* inicializa flag para ajuste do equivalente motor */
	AvcLocal[Cuba].AjustaEqMotor=FALSO;
	#ifdef	MANUAL_APOS_FALHA_MOVE
		AvcLocal[Cuba].ContConfigATN7=0;
	#endif
	AVC.Ccont[Cuba].Kbpwm=AVC.Param[Cuba].KbpwmTipico;
	AVC.Ccont[Cuba].Kcpwm=AVC.Param[Cuba].KcpwmTipico;
	EST_AVC(Cuba).ManualControle=FALSO;
	AvcLocal[Cuba].MoveuAnodo =  FALSO;
	AvcLocal[Cuba].EficMove =  0.0;
	AvcLocal[Cuba].RCicContlAnt = 0.0;
	AvcLocal[Cuba].IntegraFalhaMov = FALSO;
}
/*
--------------------------------------------------------------------------------
| TrataEquiMotor - Algoritmo adaptativo do equivalente motor                   |
--------------------------------------------------------------------------------
*/
void TrataEquiMotor(int Cuba)
{

  float EficMov;

PosicaoGlobal = 69;
  /* Atualiza Kpwm quando algoritmo de ajuste nao esta habilitado */
  if (AVC.Param[Cuba].MinKcpwm eq AVC.Param[Cuba].KcpwmTipico)
  { /* Ajuste desabilitado */
	AVC.Ccont[Cuba].Kcpwm=AVC.Param[Cuba].KcpwmTipico;
  }
  if (AVC.Param[Cuba].MinKbpwm eq AVC.Param[Cuba].KbpwmTipico)
  { /* Ajuste desabilitado */
	AVC.Ccont[Cuba].Kbpwm=AVC.Param[Cuba].KbpwmTipico;
  }
  if ((EST_AVC(Cuba).EfeitoQueb eq FALSO) and
	  (EST_AVC(Cuba).EfeitoCorr eq FALSO) and
	  (EST_AVC(Cuba).EfeitoEa eq FALSO) and
	  (EST_AVC(Cuba).Ea eq FALSO) and
	  (EST_AVC(Cuba).EaPrev eq FALSO))
  {
/******* retirado para teste - Ajusta anodo no proximo ciclo de controle
		if (EST_AVC(Cuba).EfeitoMove eq FALSO)
  ************************/
	{
/******* retirado para teste - Ajusta anodo no proximo ciclo de controle
	  if ((HoraAtualCtrl-AVC.Ccont[Cuba].HoraUltMove) <
		  AVC.Param[Cuba].TCalcEquivMotor)
  ************************/
/***** alterado para teste - Verifica se nao foi movimentado manualmente
	   entre os dois ciclos de controle *****/
	  if ((HoraAtualCtrl-AVC.Ccont[Cuba].HoraUltMove) >= (0.9*IntervCicCont*60))
/************************/
	  { /* -- pode ajustar equivalente motor -- */
		if (AvcLocal[Cuba].AjustaEqMotor eq VERDADEIRO)
		{ /* -- nao ajustou ainda apos a ultima movimentacao -- */
		  if (EST_AVC(Cuba).EsperaConfMove eq FALSO)
		  {
			/* -- Efetua ajuste do equivalente motor -- */
			AjustaEqMotor(Cuba);
		  }
		}
	  }
	  AvcLocal[Cuba].AjustaEqMotor=FALSO;
	}
  }
  else
	AvcLocal[Cuba].AjustaEqMotor=FALSO;
  /* -- Verifica se nao confirmou movimentacao automatica -- */

PosicaoGlobal = 70;

  if (AVC.ParUser1[Cuba].HabContEficMov eq VERDADEIRO)
  {
	if ((EST_AVC(Cuba).Ea eq FALSO) and (EST_AVC(Cuba).EfeitoEa eq FALSO))
	{ /* Nao trata confirmacao durante EA pois pode ser a tabela de EA */
	  /* -- Nao chegou confirmacao de movimentacao -- */

	  if (AvcLocal[Cuba].MoveuAnodo eq VERDADEIRO)
	  {
		AvcLocal[Cuba].MoveuAnodo = FALSO;

 		if (AVC.Ccont[Cuba].RErroUltMove ne 0)
		{
		  AvcLocal[Cuba].EficMove =  fabs((double)((AvcLocal[Cuba].RCicContlAnt - AVC.CcontMcp[Cuba].RCicContlBruta) /
									AVC.Ccont[Cuba].RErroUltMove)) * 100;
		}
		else
		{
		  AvcLocal[Cuba].EficMove = 100; 
		}
PosicaoGlobal = 71;

		if (AvcLocal[Cuba].EficMove > 100 and AvcLocal[Cuba].EficMove < 200)
		  EficMov = fabs(AvcLocal[Cuba].EficMove - 200);
		else if ( AvcLocal[Cuba].EficMove < 100 and AvcLocal[Cuba].EficMove > 0) 
		  EficMov = AvcLocal[Cuba].EficMove;
		else
		  EficMov = 0;
PosicaoGlobal = 72;
			
		if (AvcLocal[Cuba].EficMove >= AVC.ParUser1[Cuba].EficMovMin)
		{
		  if ( AVC.Ccont[Cuba].SentidoUltMove eq DESCER_ANODO)
		  {
			GeraEvento(CNF_DESCIDA_AUT_ANODO,Cuba,-1, AvcLocal[Cuba].EficMove);
		    SUPERV_AVC(Cuba).MovBaixoNumDia=SUPERV_AVC(Cuba).MovBaixoNumDia+1;
		    SUPERV_AVC(Cuba).MovBaixoDurDia=SUPERV_AVC(Cuba).MovBaixoDurDia+
									  AVC.Ccont[Cuba].DuracaoUltMove;
			SUPERV_AVC(Cuba).Sup.ApMovBaixoDia += EficMov;
		    /* -- *************** Dados medios de turno ******************* -- */
		    SUPERV_AVC_TURNO(Cuba).MovBaixoNumDia=SUPERV_AVC_TURNO(Cuba).MovBaixoNumDia+1;
		    SUPERV_AVC_TURNO(Cuba).MovBaixoDurDia=SUPERV_AVC_TURNO(Cuba).MovBaixoDurDia+
									  AVC.Ccont[Cuba].DuracaoUltMove;
			SUPERV_AVC_TURNO(Cuba).Sup.ApMovBaixoDia += EficMov;
			AvcLocal[Cuba].IntegraFalhaMov = FALSO;

	  		if ((HoraAtualCtrl-AVC.Ccont[Cuba].HoraUltMove) <= (1.2*IntervCicCont*60))
	  		{ /* houve movimentacao no ultimo ciclo com confirmacao */
	    	  AvcLocal[Cuba].ContConfigATN7=0;
	  		}
PosicaoGlobal = 73;

		  }
		  else
		  {
			GeraEvento(CNF_SUBIDA_AUT_ANODO,Cuba,-1, AvcLocal[Cuba].EficMove);
		    SUPERV_AVC(Cuba).MovCimaNumDia=SUPERV_AVC(Cuba).MovCimaNumDia+1;
		    SUPERV_AVC(Cuba).MovCimaDurDia=SUPERV_AVC(Cuba).MovCimaDurDia+
								 AVC.Ccont[Cuba].DuracaoUltMove;
			SUPERV_AVC(Cuba).Sup.ApMovCimaDia += EficMov;
		    /* -- *************** Dados medios de turno ******************* -- */
		    SUPERV_AVC_TURNO(Cuba).MovCimaNumDia=SUPERV_AVC_TURNO(Cuba).MovCimaNumDia+1;
		    SUPERV_AVC_TURNO(Cuba).MovCimaDurDia=SUPERV_AVC_TURNO(Cuba).MovCimaDurDia+
								 AVC.Ccont[Cuba].DuracaoUltMove;
			SUPERV_AVC_TURNO(Cuba).Sup.ApMovCimaDia += EficMov;
			AvcLocal[Cuba].IntegraFalhaMov = FALSO;

	  		if ((HoraAtualCtrl-AVC.Ccont[Cuba].HoraUltMove) <= (1.2*IntervCicCont*60))
	  		{ /* houve movimentacao no ultimo ciclo com confirmacao */
	    	  AvcLocal[Cuba].ContConfigATN7=0;
	  		}
PosicaoGlobal = 74;

		  }
		}
		else
		{
		  GeraEvento(FALHA_MOVIMENTACAO,Cuba,-1,"Geral", AvcLocal[Cuba].EficMove);
	      EST_AVC(Cuba).EfeitoMove=FALSO;
		  if (AvcLocal[Cuba].ContConfigATN7 eq 0)
	      {
		    SUPERV_AVC(Cuba).FalhaMovDia += 1;
	        SUPERV_AVC_TURNO(Cuba).FalhaMovDia += 1;
		  }
		  AvcLocal[Cuba].IntegraFalhaMov = VERDADEIRO;
PosicaoGlobal = 75;

		  if (AVC.Ccont[Cuba].SentidoUltMove eq DESCER_ANODO)
	      {
		    if (AvcLocal[Cuba].ContConfigATN7 eq 0)
	        {
		      SUPERV_AVC(Cuba).Sup.ApMovBaixoDia += EficMov;
		      SUPERV_AVC_TURNO(Cuba).Sup.ApMovBaixoDia += EficMov;
		      SUPERV_AVC(Cuba).Sup.FalhaMovBaixoDia += 1;
		      SUPERV_AVC_TURNO(Cuba).Sup.FalhaMovBaixoDia += 1;
			}
		  }
		  else
		  {
		    if (AvcLocal[Cuba].ContConfigATN7 eq 0)
	        {
	          SUPERV_AVC(Cuba).Sup.ApMovCimaDia += EficMov;
	          SUPERV_AVC_TURNO(Cuba).Sup.ApMovCimaDia += EficMov;
		      SUPERV_AVC(Cuba).Sup.FalhaMovCimaDia += 1;
		      SUPERV_AVC_TURNO(Cuba).Sup.FalhaMovCimaDia += 1;
			}
		  }
PosicaoGlobal = 75;

#ifdef	MANUAL_APOS_FALHA_MOVE
	      trata_erro(Cuba);
#endif
PosicaoGlobal = 76;

		}
	    EST_AVC(Cuba).EsperaConfMove=FALSO;
	  }
	}
  }
  else
  {
    if (EST_AVC(Cuba).EsperaConfMove eq VERDADEIRO)
    {
	  if ((EST_AVC(Cuba).Ea eq FALSO) and (EST_AVC(Cuba).EfeitoEa eq FALSO))
	  { /* Nao trata confirmacao durante EA pois pode ser a tabela de EA */
	    /* -- Nao chegou confirmacao de movimentacao -- */
#ifdef CBA_120KAII_III
	    GeraEvento(FALHA_MOVIMENTACAO,Cuba,-1,"Geral");
		AvcLocal[Cuba].IntegraFalhaMov = VERDADEIRO;
#else
	    GeraEvento(FALHA_MOVIMENTACAO,Cuba,-1);
		AvcLocal[Cuba].IntegraFalhaMov = VERDADEIRO;
#endif
	    EST_AVC(Cuba).EsperaConfMove=FALSO;
	    EST_AVC(Cuba).EfeitoMove=FALSO;
	    if (AvcLocal[Cuba].ContConfigATN7 eq 0)
	    {
	      SUPERV_AVC(Cuba).FalhaMovDia += 1;
	      SUPERV_AVC_TURNO(Cuba).FalhaMovDia += 1;
		}
PosicaoGlobal = 77;

#ifdef	MANUAL_APOS_FALHA_MOVE
	    trata_erro(Cuba);
#endif
PosicaoGlobal = 78;

	  }
    }
#ifdef	MANUAL_APOS_FALHA_MOVE
    else
	  if ((HoraAtualCtrl-AVC.Ccont[Cuba].HoraUltMove) <= (1.2*IntervCicCont*60))
	  { /* houve movimentacao no ultimo ciclo com confirmacao */
	    AvcLocal[Cuba].ContConfigATN7=0;
	  }
#endif
PosicaoGlobal = 79;

  }
}


/*
--------------------------------------------------------------------------------
| AjustaEqMotor - Executa o calculo adaptativo do equivalente motor da cuba    |
|                 dada, apos a ultima movimentacao de anodo.                   |
--------------------------------------------------------------------------------
*/
void AjustaEqMotor(int Cuba)
{
#ifndef		ALBRAS
  float	RErro;
/* -- Alteracao - inicio - 12/04/2001 - Leonel - Correcao para nao tratar mov. manual -- */
#ifdef CBA_120KAII_III
  float	VAlvo,VCicCont;
#endif
/* -- Alteracao - fim - 12/04/2001 - Leonel - Correcao para nao tratar mov. manual -- */


  RErro=AVC.Ccont[Cuba].RAlvoUltMove - AVC.CcontMcp[Cuba].RCicContlBruta;

/* -- Alteracao - inicio - 12/04/2001 - Leonel - Correcao para nao tratar mov. manual -- */
#ifdef CBA_120KAII_III
  /* Verifica provavel agarramento de anodo */
  if (AVC.Param[Cuba].MaxAgarraAnodo ne 0)
  {
	if ((EST_AVC(Cuba).ChaveAutMan eq AUTOMATICO) and
		(EST_AVC(Cuba).ChaveLocRem eq REMOTO) and
		/* verifica se iguais com 0.1uohms de histerese */
/* -- Alteracao - inicio - 01/03/2002 - Leonel - Correcao: valor absoluto do erro para comparacao -- */
		(fabs(AVC.Ccont[Cuba].RErroUltMove - RErro) <= AVC.ParUser1[Cuba].DifResAgarra /*0.3e-6*/) and
		/* verifica se iguais com 0.01uohms de histerese */
		(fabs(AVC.Ccont[Cuba].RAlvoUltMove - AVC.Ccont[Cuba].RAlvo) <= 0.01e-6) and
/* -- Alteracao - fim - 01/03/2002 - Leonel - Correcao: valor absoluto do erro para comparacao -- */
		((HoraAtualCtrl-AVC.Ccont[Cuba].HoraUltMove) <= (1.2*IntervCicCont*60)))
	{ /* A ultima movimentacao nao surtiu efeito. Provavel agarramento de anodo */
	  AVC.Ccont[Cuba].ContAgarraAnodo++;	/* Contador de provavel agarramento de anodo */
	  if (AVC.Ccont[Cuba].ContAgarraAnodo >= AVC.Param[Cuba].MaxAgarraAnodo)
	  {  /* Provavel agarramento de anodo. Passa cuba para manual */
		EST_AVC(Cuba).ProvAgarraAnodo=VERDADEIRO;

		/* -- Passa cuba para manual -- */
		EST_AVC(Cuba).ChaveAutMan = MANUAL;
		/* -- Cuba colocada em manual pelo controle -- */
		EST_AVC(Cuba).ManualControle=VERDADEIRO;

		/*-- Hora da ultima selecao manual --*/
		AVC.Cleit[Cuba].HoraUltSelMan = HoraAtualCtrl;
		/*-- Gera evento de selecao de modo de operacao --*/
		VAlvo=AVC.Ccont[Cuba].VAlvo;
		/* Inicio Alteracao - Carlos - 23/06/99 */
		/* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
		VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba+
		   AVC.Param[Cuba].Bemf;
#else
		VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal+
		   AVC.Param[Cuba].Bemf;
#endif
		/* Fim Alteracao - Carlos - 23/06/99 */
		GeraEvento( OPERACAO_MANUAL, Cuba, -1, ScoreGetStr(SCORE_MSG_258),
				"AGARRA",VCicCont,AVC.Cleit[Cuba].Vinst,VAlvo);
PosicaoGlobal = 79;

	  }
	}
  }
#endif
/* -- Alteracao - fim - 12/04/2001 - Leonel - Correcao para nao tratar mov. manual -- */

  if (AVC.Ccont[Cuba].SentidoUltMove eq SUBIR_ANODO)
  {
	if (AVC.Param[Cuba].MinKcpwm ne AVC.Param[Cuba].KcpwmTipico)
	{
	  AVC.Ccont[Cuba].Kcpwm=AVC.Ccont[Cuba].Kcpwm -
				AVC.Abs[Cuba].DeltaUp*RErro*AVC.Ccont[Cuba].DuracaoUltMove;
	  if ((AVC.Ccont[Cuba].Kcpwm <= AVC.Param[Cuba].MinKcpwm) or
		  (AVC.Ccont[Cuba].Kcpwm > MAX_KCPWM))
	  {
PosicaoGlobal = 80;
		EmiteAlarmeFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_MSG_253),
					ConvCubScoreOper(Cuba));
//		EmiteAlarmeFor(TODOS_DISPOSITIVOS,"Provavel falha subida anodo cuba=%d",
//					ConvCubScoreOper(Cuba));
		AVC.Ccont[Cuba].Kcpwm=AVC.Param[Cuba].KcpwmTipico;
		SUPERV_AVC(Cuba).FalhaMovDia += 1;
		SUPERV_AVC_TURNO(Cuba).FalhaMovDia += 1;

	  }
	}
  }
  else	/* descer */
  {
	if (AVC.Param[Cuba].MinKbpwm ne AVC.Param[Cuba].KbpwmTipico)
	{
PosicaoGlobal = 81;

	  AVC.Ccont[Cuba].Kbpwm=AVC.Ccont[Cuba].Kbpwm +
			AVC.Abs[Cuba].DeltaDown*RErro*AVC.Ccont[Cuba].DuracaoUltMove;
	  if ((AVC.Ccont[Cuba].Kbpwm <= AVC.Param[Cuba].MinKbpwm) or
		(AVC.Ccont[Cuba].Kbpwm > MAX_KBPWM))
	  {
		EmiteAlarmeFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_MSG_254),
					ConvCubScoreOper(Cuba));
//		EmiteAlarmeFor(TODOS_DISPOSITIVOS,"Provavel falha descida anodo cuba=%d",
//					ConvCubScoreOper(Cuba));
		AVC.Ccont[Cuba].Kbpwm=AVC.Param[Cuba].KbpwmTipico;
		SUPERV_AVC(Cuba).FalhaMovDia += 1;
		SUPERV_AVC_TURNO(Cuba).FalhaMovDia += 1;
	  }
	}
  }
#endif
}


/*
--------------------------------------------------------------------------------
| CalcEquivMotor - Calcula o equivalente motor em segundos e o sentido de      |
|                  acionamento para o erro correspondente a Cuba dada.         |
|                  Retorna a duracao do movimento em segundos e o sentido de   |
|                  movimentacao (DESCER ou SUBIR)                              |
--------------------------------------------------------------------------------
*/
float CalcEquivMotor(int Cuba, float Rerro, int *SentidoMov)
{
  float	DuracaoMov;
  float AbsErro;
  float LimDurMovMin;
  float LimDurMovMax;

  AvcLocal[Cuba].AjustaEqMotor=FALSO;
  AbsErro = fabs((double)Rerro);
  if (Rerro < 0.0)
  {
PosicaoGlobal = 82;

	*SentidoMov=DESCER_ANODO;
	/* calculo do tempo de movimentacao */
	if (AVC.Param[Cuba].DurMovBaixoMin eq 0)
	{
	  LimDurMovMin = AVC.ParUser1[Cuba].DurMovBaixoMinF;
	  LimDurMovMax = AVC.ParUser1[Cuba].DurMovBaixoMaxF;
	}
	else
	{
	  LimDurMovMin = (float)AVC.Param[Cuba].DurMovBaixoMin;
	  LimDurMovMax = (float)AVC.Param[Cuba].DurMovBaixoMax;
	}
	
	DuracaoMov=AVC.Param[Cuba].KPb*(AbsErro/AVC.Ccont[Cuba].Kbpwm);
	if (DuracaoMov < LimDurMovMin)
	  DuracaoMov=0.0;
	else
	  if (DuracaoMov > LimDurMovMax)
		DuracaoMov=LimDurMovMax;
	  else
		AvcLocal[Cuba].AjustaEqMotor=VERDADEIRO;
  }
  else
  {
PosicaoGlobal = 83;

	*SentidoMov=SUBIR_ANODO;
	/* calculo do tempo de movimentacao */
    if ( (((HoraAtualCtrl-AVC.Cleit[Cuba].HoraUltQueb) < 120) or
		((HoraAtualCtrl-AVC.User1[Cuba].HoraUltQPrev) < 120)) and
	   (EST_AVC(Cuba).Quebrada eq VERDADEIRO) and
	   (EST_AVC(Cuba).Ea eq FALSO) and
	   ((HoraAtualCtrl - AVC.User2[Cuba].HoraUltMovPainel)  >120))
	{	
	  if (AVC.Param[Cuba].DurMovCimaMin eq 0)
	  {
	    LimDurMovMin = AVC.ParUser1[Cuba].DurMovCimaMinF;
	    LimDurMovMax = AVC.ParUser1[Cuba].DurMovCimaMaxF;
	  }
	  else
	  {
	    LimDurMovMin = (float)AVC.Param[Cuba].DurMovCimaMin;
	    LimDurMovMax = (float)AVC.Param[Cuba].DurMovCimaMax;
	  }


	  DuracaoMov=AVC.ParUser1[Cuba].KPcQueb*(AbsErro/AVC.Ccont[Cuba].Kcpwm);
	  if (DuracaoMov < LimDurMovMin)
	    DuracaoMov=0.0;
	  else
	    if (DuracaoMov > LimDurMovMax)
		  DuracaoMov=LimDurMovMax;
	    else
		  AvcLocal[Cuba].AjustaEqMotor=VERDADEIRO;

	}
	else
	{
	  if (AVC.Param[Cuba].DurMovCimaMin eq 0)
	  {
	    LimDurMovMin = AVC.ParUser1[Cuba].DurMovCimaMinF;
	    LimDurMovMax = AVC.ParUser1[Cuba].DurMovCimaMaxF;
	  }
	  else
	  {
	    LimDurMovMin = (float)AVC.Param[Cuba].DurMovCimaMin;
	    LimDurMovMax = (float)AVC.Param[Cuba].DurMovCimaMax;
	  }

	  DuracaoMov=AVC.Param[Cuba].KPc*(AbsErro/AVC.Ccont[Cuba].Kcpwm);
	  if (DuracaoMov < LimDurMovMin)
	    DuracaoMov=0.0;
	  else
	    if (DuracaoMov > LimDurMovMax)
		  DuracaoMov=LimDurMovMax;
	    else
		  AvcLocal[Cuba].AjustaEqMotor=VERDADEIRO;
	}
  }
  return(DuracaoMov);
}

#ifdef	MANUAL_APOS_FALHA_MOVE

void trata_erro(int cuba)
{
  time_t	HoraAtual;
  float		VAlvo,VInst,VCicCont;

  if (AvcLocal[cuba].ContConfigATN7 < 3)
  {
PosicaoGlobal = 84;

	/* -- Comanda configuracao do ATN7 para reinicializar EPLD (falha move
	  porque remota esta' suceptivel a ruido e resetando EPLD sem resetar
	  CPU e passando todas as saidas para entrada -- */
	AvcLocal[cuba].ContConfigATN7++;
  }
  else
  {
PosicaoGlobal = 85;

	/* -- Apos tres configuracoes seguidas passa cuba para manual -- */
	AvcLocal[cuba].ContConfigATN7=0;
	EST_AVC(cuba).ChaveAutMan = MANUAL;
	/* -- Cuba colocada em manual pelo controle -- */
	EST_AVC(cuba).ManualControle=VERDADEIRO;

	/* -- Pega a hora atual -- */
	HoraAtual=time(NULL)/TIMES_PER_SEC; /* -- segs. apartir 1/1/1980 -- */
	/*-- Hora da ultima selecao manual --*/
	AVC.Cleit[cuba].HoraUltSelMan = HoraAtual;
	/*-- Gera evento de selecao de modo de operacao --*/
	VAlvo=AVC.Ccont[cuba].VAlvo;
	VInst=AVC.Cleit[cuba].Vinst;

	/* Inicio Alteracao - Carlos - 23/06/99 */
	/* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
	VCicCont=AVC.CcontMcp[cuba].RCicContlBruta*AVC.Ccont[cuba].INominalCuba+
		   AVC.Param[cuba].Bemf;
#else
	VCicCont=AVC.CcontMcp[cuba].RCicContlBruta*AVL.INominal+
		   AVC.Param[cuba].Bemf;
#endif
	/* Fim Alteracao - Carlos - 23/06/99 */

	GeraEvento( OPERACAO_MANUAL, cuba, -1, ScoreGetStr(SCORE_MSG_258),
				STR_TRACO,VCicCont,VInst,VAlvo);
//	GeraEvento( OPERACAO_MANUAL, cuba, -1, "Controle", STR_TRACO,
//				VCicCont,VInst,VAlvo);
  }
}

#endif

/* -- fim do arquivo EquivMotor.c -- */
