/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: TrataCamisa.c

	CONTEUDO	: Biblioteca de funcoes de movimentacao de camisa do ciclo
                  de controle.

	AUTOR		: Carlos Cezar Silva Lage

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 1.0			-		DATA	:	21/07/98

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
dd/mm/aa | Descricao                                                | Autor
-------------------------------------------------------------------------------
19/10/98 | Alteracao para ajuste de camisa ocorrer apos TEfeitoCorr | Carlos
-------------------------------------------------------------------------------
28/06/99 | Incluido tratamento de booster de corrente			    | Carlos
-------------------------------------------------------------------------------
$Id: SobeCamisa.c,v 1.1.2.1 2012/09/28 17:09:28 leo Exp $

$Log: SobeCamisa.c,v $
Revision 1.1.2.1  2012/09/28 17:09:28  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

Revision 1.4  2008/07/02 20:24:28  alex
nao subir camisa junto com movimentacao de anodo
e quando sinalizar quebrada mover para cima

Revision 1.3  2007/10/10 18:54:10  leo
Correcao para contabilizar movimento < 0.1 mesmo quando nao move para permitir
o fim do tratamento.

Revision 1.2  2007/06/26 13:59:53  leo
Incluida protecao para nao permitir movimentos menores que 100 ms para evitar
comandar subida com tempo menor que 50 ms o que provoca disparo do movimento
pois sera comando tempo igual a 0! (base de tempo minima da remota eh 50ms)

******************************************************************************/

/**** #define		ATIVA_DEPURACAO  ****/

/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/

#include	<MccCba.h>
#include	<AjusteCamisa.h>
#include	<Eventos.h>
#include	<Prototipos.h>



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

/*
-------------------------------------------------------------------------------
							Funcoes
-------------------------------------------------------------------------------
*/

/*
--------------------------------------------------------------------------------
  TrataSubidaCamisa - Tratar a subida de camisa da cuba.
--------------------------------------------------------------------------------
*/
void TrataSubidaCamisa(int Cuba, time_t HoraAtual)
{
  float		DurMov;
  char		StrTempo[9];
  float		VCicCont;
  float		VInst;
  float		VAlvo;
  int	Duracao;

PosicaoGlobal = 133;
  /*-- nao sobe camisa se moveu automatico no mesmo ciclo de controle --*/
  if((EST_AVC(Cuba).ChaveAutMan eq AUTOMATICO) and
	 (EST_AVC(Cuba).ChaveLocRem eq REMOTO) and
	 (EST_AVC(Cuba).EfeitoMove eq VERDADEIRO) and
	 (AVC.Ccont[Cuba].HoraUltMove eq HoraAtual))
  {
	return;   
  }	
	  
  if (EST_AVC(Cuba).Est.AjusteCamisa eq VERDADEIRO)
  {
	if ((HoraAtual-AVC.Cleit[Cuba].HoraUltCorr) > AVC.Param[Cuba].TEfeitoCorr)
	{
	  if(AVC.ParUser1[Cuba].HabMovCamTur eq VERDADEIRO)
	  {
		AVC.User1[Cuba].ContTAjCam -= AVC.User2[Cuba].TMovCamAcumTur;
	
		if(AVC.User1[Cuba].ContTAjCam < 0)
		{
		  AVC.User1[Cuba].ContTAjCam = 0;
		}

		AVC.User2[Cuba].TMovCamAcumTur = 0;
	  }
	  else
	  {
		AVC.User2[Cuba].TMovCamAcumTur = 0;	
	  }

	  /*-- Calcula tempo de subida de camisa --*/
	  DurMov = (AVC.User1[Cuba].ContTAjCam <= AVC.ParUser1[Cuba].LimTAjMov)?
				AVC.User1[Cuba].ContTAjCam : AVC.ParUser1[Cuba].LimTAjMov;

  	  /*-- Efetua subida de camisa --*/
	  if (DurMov > 0.0)
	  {
PosicaoGlobal = 134;

	    AVC.User1[Cuba].ContTAjCam -= DurMov;

	    AVC.User1[Cuba].ContTAjAcum += (DurMov + AVC.User2[Cuba].TMovCamAcumTur);

	    VerifCondCamisa(Cuba, HoraAtual);
	  }
	  if (DurMov >= 0.1)
	  {
		if (EST_AVC(Cuba).Est.AbortaAjuste eq AJUSTE_NORMAL)
		{
		  DurMov *= BASE_TEMPO_REMOTA;
		  if (ComandaSaidaRem(Cuba,LIGAR,AVC.Abs[Cuba].BitSobeCamisaouM1,(int)DurMov) ne 0)
			EmiteAlarmeFor(TODOS_DISPOSITIVOS,"Falha subida camisa, Cuba %d",
						   ConvCubScoreOper(Cuba));

		  /*-- Gera evento de ajuste de camisa --*/
		  sprintf(StrTempo,"%5.2f", DurMov/BASE_TEMPO_REMOTA);
		  VAlvo = AVC.Ccont[Cuba].VAlvo;
		  VInst = AVC.Cleit[Cuba].Vinst;

		  /* Inicio Alteracao - Carlos - 23/06/99 */
		  /* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
		  VCicCont = AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba+
					 AVC.Param[Cuba].Bemf;
#else
		  VCicCont = AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal+
					 AVC.Param[Cuba].Bemf;
#endif
		  /* Fim Alteracao - Carlos - 23/06/99 */

		  GeraEvento(SUBIDA_AUT_CAMISA,Cuba,-1, StrTempo, VCicCont,VInst,VAlvo);

		  AVC.User2[Cuba].SubiuCamisa = VERDADEIRO;

		  AVC.User2[Cuba].UltRCicCont = AVC.CcontMcp[Cuba].RCicContlBruta;

		  AVC.User1[Cuba].HoraUltMovCam = HoraAtualCtrl;
		  
		}
	  }
	}
  }
  else
  {
	if(AVC.ParUser2[Cuba].CamisaPFAuto eq VERDADEIRO)
	{
	  if((HoraAtual-AVC.Cleit[Cuba].HoraUltCorr) > AVC.Param[Cuba].TEfeitoCorr and
		(HoraAtual-AVC.Cleit[Cuba].HoraUltCorr) < (AVC.ParUser2[Cuba].TMaxAjCamPF*60))
	  {
	  	if(AVC.CcontMcp[Cuba].RCicContlBruta >= (AVC.Ccont[Cuba].RAlvo - AVC.Param[Cuba].BandaMortaInf) and
	  		AVC.CcontMcp[Cuba].RCicContlBruta <= (AVC.Ccont[Cuba].RAlvo + AVC.Param[Cuba].BandaMortaSup))
		{
		  if(EST_AVC(Cuba).Est.CamisaBaixa eq VERDADEIRO and
	  		  EST_AVC(Cuba).Est.CamisaAlta eq FALSO and
				AVC.User2[Cuba].NumMovCamPF < AVC.ParUser2[Cuba].NMaxMovCamPF and
				AVC.User1[Cuba].ContInibAjCam <= 0)
		  {
		    EST_AVC(Cuba).Est.AbortaAjuste = AJUSTE_NORMAL;
			
		    if (ComandaSaidaRem(Cuba,LIGAR,AVC.Abs[Cuba].BitSobeCamisaouM1,
					(int)(AVC.ParUser2[Cuba].TMovCamPF*BASE_TEMPO_REMOTA)) ne 0)
			  EmiteAlarmeFor(TODOS_DISPOSITIVOS,"Falha subida camisa, Cuba %d",
				   ConvCubScoreOper(Cuba));

			  NumMov[AVC.ParUser1[Cuba].GrupoMov]++;
			  AVC.User2[Cuba].NumMovCamPF++;

		      /*-- Gera evento de ajuste de camisa --*/
		      sprintf(StrTempo,"%5.2f", (float)AVC.ParUser2[Cuba].TMovCamPF);
		      VAlvo = AVC.Ccont[Cuba].VAlvo;
		      VInst = AVC.Cleit[Cuba].Vinst;

#ifdef	BOOSTER_CORRENTE
		      VCicCont = AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba+
					 AVC.Param[Cuba].Bemf;
#else
		      VCicCont = AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal+
					 AVC.Param[Cuba].Bemf;
#endif

		      GeraEvento(SUBIDA_AUT_CAMISA,Cuba,-1, StrTempo, VCicCont,VInst,VAlvo);		
		  }
	
		  if(EST_AVC(Cuba).Est.CamisaBaixa eq FALSO and
	  		  EST_AVC(Cuba).Est.CamisaAlta eq FALSO)
		  {
		    EST_AVC(Cuba).Est.AbortaAjuste = AJUSTE_NORMAL;
			EST_AVC(Cuba).Est.CamNAjust = FALSO;
		  }
		}
	  }

	  if(EST_AVC(Cuba).Est.CamisaBaixa eq FALSO and
  		  EST_AVC(Cuba).Est.CamisaAlta eq VERDADEIRO)
	  {
		EST_AVC(Cuba).Est.AbortaAjuste = ABORTA_DESAB_CAMISA;	
	  }  
	}

	if(AVC.ParUser1[Cuba].HabMovCamTur eq VERDADEIRO) 
	{
	  if ( AVC.User1[Cuba].ContInibAjCam <= 0)
	  {
	  	if((((EST_AVC(Cuba).Est.AjusteCamTur eq VERDADEIRO) and 
			(AVL.MudancaTurno eq 0 and AVC.ParUser1[Cuba].TMovCamCorr eq 0)) or
			(((HoraAtualCtrl - AVC.User1[Cuba].HoraUltMovCam) >= AVC.ParUser1[Cuba].TMovCamCorr*60*60) and
			(AVC.ParUser1[Cuba].TMovCamCorr > 0))) and 
			(AVC.ParUser1[Cuba].HabLimMov eq VERDADEIRO and
			(NumMov[AVC.ParUser1[Cuba].GrupoMov] < AVC.ParUser1[Cuba].NumMovConsec)) )
	  	{
PosicaoGlobal = 135;

	      /*-- Calcula tempo de subida de camisa --*/
		  if(AVC.User2[Cuba].NumMovCamTur eq 0)
			AVC.User2[Cuba].TMovCamTur = AVC.ParUser1[Cuba].TempoMovCamTur;

		  if(AVC.User2[Cuba].TMovCamTur > AVC.Param[Cuba].DurMovCimaMax)
	      {
		    DurMov = (float)AVC.Param[Cuba].DurMovCimaMax;
			Duracao = AVC.Param[Cuba].DurMovCimaMax; 
			AVC.User2[Cuba].TMovCamTur = (AVC.User2[Cuba].TMovCamTur - AVC.Param[Cuba].DurMovCimaMax); 
		  }
		  else
		  {
		    DurMov = (float)AVC.User2[Cuba].TMovCamTur;
			Duracao = AVC.User2[Cuba].TMovCamTur; 
			AVC.User2[Cuba].TMovCamTur = 0; 
		  }

    	  /*-- Efetua subida de camisa --*/
	      if (DurMov > 0.0)
	      {
		    EST_AVC(Cuba).Est.AbortaAjuste = AJUSTE_NORMAL;
	       // VerifCondCamisa(Cuba, HoraAtual);
	      }
	      if (DurMov >= 0.1)
	      {
		    if (EST_AVC(Cuba).Est.AbortaAjuste eq AJUSTE_NORMAL)
		    {
PosicaoGlobal = 136;

		      DurMov *= BASE_TEMPO_REMOTA;
		      if (ComandaSaidaRem(Cuba,LIGAR,AVC.Abs[Cuba].BitSobeCamisaouM1,(int)DurMov) ne 0)
			    EmiteAlarmeFor(TODOS_DISPOSITIVOS,"Falha subida camisa, Cuba %d",
						   ConvCubScoreOper(Cuba));

			  NumMov[AVC.ParUser1[Cuba].GrupoMov]++;
		      AVC.User2[Cuba].TMovCamAcumTur += Duracao;


		      /*-- Gera evento de ajuste de camisa --*/
		      sprintf(StrTempo,"%5.2f", DurMov/BASE_TEMPO_REMOTA);
		      VAlvo = AVC.Ccont[Cuba].VAlvo;
		      VInst = AVC.Cleit[Cuba].Vinst;

#ifdef	BOOSTER_CORRENTE
		      VCicCont = AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba+
					 AVC.Param[Cuba].Bemf;
#else
		      VCicCont = AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal+
					 AVC.Param[Cuba].Bemf;
#endif

		      GeraEvento(SUBIDA_AUT_CAMISA,Cuba,-1, StrTempo, VCicCont,VInst,VAlvo);		

			  AVC.User2[Cuba].NumMovCamTur++;
			
			  if(AVC.User2[Cuba].TMovCamTur eq 0)
			  {
			    AVC.User2[Cuba].SubiuCamisa = VERDADEIRO;

  		  	    AVC.User1[Cuba].HoraUltMovCam = HoraAtualCtrl;

  			    AVC.User2[Cuba].NumMovCamTur = 0;

			    AVC.User2[Cuba].UltRCicCont = AVC.CcontMcp[Cuba].RCicContlBruta;

	  		    EST_AVC(Cuba).Est.AjusteCamTur = FALSO;
			  }
		    }
		  }
	    }
	  }
	  else if(((EST_AVC(Cuba).Est.AjusteCamTur eq VERDADEIRO) and 
			(AVL.MudancaTurno eq 0) and 
			(AVC.ParUser1[Cuba].TMovCamCorr eq 0)) or
			(((HoraAtualCtrl - AVC.User1[Cuba].HoraUltMovCam) >= AVC.ParUser1[Cuba].TMovCamCorr*60*60) and
			(AVC.ParUser1[Cuba].TMovCamCorr > 0)))
	  {
PosicaoGlobal = 137;

		EST_AVC(Cuba).Est.AjusteCamTur = FALSO;
	    GeraEvento(CAMISA_NAO_AJUSTADA,Cuba,-1,"Ajuste", "Inibido");
		AVC.User1[Cuba].HoraUltMovCam = HoraAtualCtrl;
	    AVC.User2[Cuba].SubiuCamisa = FALSO;

	  }
	}
	else
	{
PosicaoGlobal = 138;

      AVC.User2[Cuba].TMovCamAcumTur = 0.0;
	  EST_AVC(Cuba).Est.AjusteCamTur = FALSO;
	}
  }
} /*-- TrataSubidaCamisa --*/

