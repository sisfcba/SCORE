/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: FimEa.c

	CONTEUDO	: Modelo de Calculos Primarios - Mcp - Procedimentos para fim
                  de Efeito Anodico nas Cubas.

	AUTOR		: Joao Thomaz Pereira

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	24/09/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
06/04/94 | Acrescentado EsperaEa=FALSO no fim do Ea (Alcoa)         | Leonel
-------------------------------------------------------------------------------
05/07/94 | Edicao inicial de migracao para o QNX 4.2			    | Leonel
-------------------------------------------------------------------------------
16/09/94 | Inclusao de VMaxEaDia no fim do Ea (CBA) 			    | Carlos
-------------------------------------------------------------------------------
20/09/94 | Acrescentada contabilizacao para historico de turno	    | Leonel
-------------------------------------------------------------------------------
06/01/96 | Acrescentada contabilizacao de eficiencia de previsao    | Carlos
-------------------------------------------------------------------------------
03/10/96 | Incluida classificacao de EA para relatorio historico    | Carlos
-------------------------------------------------------------------------------
18/12/96 | Incluidos calculos para rel. hist. estatistica de EA     | Carlos
-------------------------------------------------------------------------------
18/02/97 | Alterada tabela de limites  de  estatistica de intervalo | Carlos
         | entre efeito anodico                                     |
-------------------------------------------------------------------------------
11/12/98 | Alterada tabela de limites  de  estatistica de intervalo | Carlos
         | entre efeito anodico                                     |
-------------------------------------------------------------------------------
08/07/02 | Incluido desab. de eliminacao de EA pelo operador		| Carlos
-------------------------------------------------------------------------------
01/06/05 | Incluidos calculos para rel. integracao de cubas e       | Carlos
         | alteracao de limites do relat. estatiscica de EA         | 
-------------------------------------------------------------------------------
$Id: FimEa.c,v 1.1.2.1 2012/09/28 17:09:37 leo Exp $

$Log: FimEa.c,v $
Revision 1.1.2.1  2012/09/28 17:09:37  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

Revision 1.12  2008/12/11 21:51:45  leo
Corrigida contabilizacao de EaContLXLim. Estava contabilizando duas vezes
durante espera de EA.

Revision 1.11  2008/08/01 20:38:42  leo
Correcao tratamento de DXLim. Acrescentado tratamento para contabilizar durante
espera de fim EA para retirar ao final do mesmo.

Revision 1.10  2007/05/04 08:06:51  rogerio
Apenas coloquei uma linha comentada (diferenca entre a vers�o 1.8 e a versao 1.9)

Revision 1.9  2007/03/23 20:57:20  rogerio
correcao de bug

Revision 1.8  2007/02/27 00:24:53  rogerio
Criacao do relatorio de estatistica de EA detalhado.

Revision 1.7  2006/12/21 18:04:18  alex
novo ope tabela alternativa

Revision 1.6  2006/01/09 19:39:59  clage
Correcao tratamento de variaveis de integracao de 1h para relatorio.

Revision 1.5  2005/06/17 12:15:41  clage
Incluido tratamento do relat. de integracao e trat VInst > VEaXLm no EA

Revision 1.4  2004/07/29 14:36:37  clage
Alterado criterio de duracao de EA para relatorio estatistica EA

******************************************************************************/


/*
-------------------------------------------------------------------------------
							Includes
-------------------------------------------------------------------------------
*/
#include	<stdio.h>
#include	<Prototipos.h>
#include	<Score.h>
#include	<Eventos.h>
#include	<TrataEa.h>

/*
-------------------------------------------------------------------------------
							Variaveis Globais
-------------------------------------------------------------------------------
*/
/* -- Apontadores para as tabelas comuns -- */
#include	<VarsComum.h>
/* -- Variaveis do modulo -- */
#include	<VarsTrataEa.h>

/*
-------------------------------------------------------------------------------
	AguardaFimEa	-	Detecta final do Efeito Anodico nas Cubas
-------------------------------------------------------------------------------
*/

void AguardaFimEa(int Cuba)
{

  SelecionaAvc(Cuba);

  AVC.Ea[Cuba].EaContL++;	
  AVC.Ea[Cuba].EaVAcumBruta += AVC.Cleit[Cuba].Vinst;
  AVC.Ea[Cuba].EaPotAcumBruta += AVC.Cleit[Cuba].Pinst;
  AVC.Ea[Cuba].EaVAcumLiq += (AVC.Cleit[Cuba].Vinst - AVC.Ccont[Cuba].VAlvo);
  AVC.Ea[Cuba].EaPotAcumLiq += ((AVC.Cleit[Cuba].Vinst - AVC.Ccont[Cuba].VAlvo) *
								AVC.Cleit[Cuba].Iinst);

/* -- Inicio - 14/06/2005 - Carlos - Tensao EA acima de VEaXLim -- */
  if (AVC.Cleit[Cuba].Vinst >= AVC.Param[Cuba].VEaXLim)
  	AVC.Ea[Cuba].EaContLXLim++;	
/* -- Fim - 14/06/2005 - Carlos - Tensao EA acima de VEaParam -- */

  if (AVC.Ea[Cuba].EaContLEsp eq 0)
	AVC.Ea[Cuba].EaHoraFimProv = HoraAtualSec;

  if(HoraAtualSec < (AVC.Ea[Cuba].EaHoraFimProv + AVC.Param[Cuba].EaTempoEspera))
  {
	if (AVC.Cleit[Cuba].Vinst >= AVC.Param[Cuba].VEaXLim)
  	  AVC.Ea[Cuba].EaContLEspXLim++;	
	AVC.Ea[Cuba].EaContLEsp++;	
    AVC.Ea[Cuba].EaVAcumEspBruta += AVC.Cleit[Cuba].Vinst;
    AVC.Ea[Cuba].EaPotAcumEspBruta += AVC.Cleit[Cuba].Pinst;
  	AVC.Ea[Cuba].EaVAcumEspLiq += (AVC.Cleit[Cuba].Vinst - AVC.Ccont[Cuba].VAlvo);
  	AVC.Ea[Cuba].EaPotAcumEspLiq += ((AVC.Cleit[Cuba].Vinst - AVC.Ccont[Cuba].VAlvo)
							  	    * AVC.Cleit[Cuba].Iinst);
	/* 08/07/02 - Inicio - Carlos */
	if((AVC.Param[Cuba].HabEliminaEa eq VERDADEIRO) and
	   (EST_AVC(Cuba).Est.HabElimEaOpe eq VERDADEIRO) and
		((EST_AVC(Cuba).ChaveLocRem eq REMOTO) and 
		 (EST_AVC(Cuba).ChaveAutMan eq AUTOMATICO)))
	/* 08/07/02 - Fim - Carlos */
	{
	  if ((AVC.Param[Cuba].TempoAtivaTEa ne 0) and
		  ((HoraAtualSec - AVC.Ea[Cuba].EaHoraInicio) >= AVC.Param[Cuba].TempoAtivaTEa))
		EliminaEa(Cuba, AVC.Ea[Cuba].EaClasse);
	}
  }
  else
	FimEa(Cuba);
}

/*
-------------------------------------------------------------------------------
	FimEa	-	Procedimentos de Fim de Efeito Anodico
-------------------------------------------------------------------------------
*/

void FimEa(int Cuba)
{
  char Par1[9];
  unsigned short int EaContxLim;

  /* verifica se tabela alternativa habilitada */
  if( EST_AVC(Cuba).AtivaTabEaAltern eq VERDADEIRO )	
  {
	/* se tabela e do tipo Ea, entao com o fim Ea reseta a ativacao */
    if( EST_AVC(Cuba).TipoTabEaAltern eq 1 ) // tipo Ea
  	  EST_AVC(Cuba).AtivaTabEaAltern = FALSO;
  }
  EST_AVC(Cuba).Ea = FALSO;
  EST_AVC(Cuba).EliminaEa = FALSO;
  EST_AVC(Cuba).ElimEaAtivo = FALSO;
  if ( AVC.ParUser1[Cuba].HabLogMovQueb eq VERDADEIRO)
	AVC.Param[Cuba].HabMovIniQueb = 1;

  /* 06/07/02 - Inicio - Carlos */
  if (AVC.User1[Cuba].EstadoSoproEspec eq SOPRO_EXECUCAO)
  {
	AVC.User1[Cuba].EstadoSoproEspec = SOPRO_FIM_EA;
	GeraEvento(SOPRO_ESPECIAL,Cuba,-1,"Fim", "EA");
	EST_AVC(Cuba).Est.OpeSoproEspec = FALSO;
  }
  /* 06/07/02 - Fim - Carlos */
  /* -- contabiliza informacoes do ultimo ea -- */
  AVC.Ea[Cuba].EaDur = AVC.Ea[Cuba].EaHoraFimProv - AVC.Ea[Cuba].EaHoraInicio;
  AVC.Ea[Cuba].EaNumL = AVC.Ea[Cuba].EaContL - AVC.Ea[Cuba].EaContLEsp;

  AVC.Ea[Cuba].EaVBruta = (AVC.Ea[Cuba].EaVAcumBruta - AVC.Ea[Cuba].EaVAcumEspBruta)
				 		  / AVC.Ea[Cuba].EaNumL; 
  AVC.Ea[Cuba].EaPotBruta = (AVC.Ea[Cuba].EaPotAcumBruta - AVC.Ea[Cuba].EaPotAcumEspBruta)
				 		    /AVC.Ea[Cuba].EaNumL; 
  AVC.Ea[Cuba].EaEnergBruta = AVC.Ea[Cuba].EaPotBruta * AVC.Ea[Cuba].EaDur;
  AVC.Ea[Cuba].EaVLiq = (AVC.Ea[Cuba].EaVAcumLiq - AVC.Ea[Cuba].EaVAcumEspLiq)
				 	    / AVC.Ea[Cuba].EaNumL; 
  AVC.Ea[Cuba].EaPotLiq = (AVC.Ea[Cuba].EaPotAcumLiq - AVC.Ea[Cuba].EaPotAcumEspLiq)
				 		  / AVC.Ea[Cuba].EaNumL; 
  AVC.Ea[Cuba].EaEnergLiq = AVC.Ea[Cuba].EaPotLiq * AVC.Ea[Cuba].EaDur;

  /***** Calculo dos valores historicos diarios e de turno **********/

  /* -- Contabiliza dados do relat. estat. de EA -- */
  ContabEstatEa(Cuba);

  /*-- Classifica EA para relatorio historico --*/
  if (AVC.Ea[Cuba].EaVMax > AVC.Param[Cuba].VEaForte)
  {
	SUPERV_AVC(Cuba).ClasseEa = EA_FORTE;
	SUPERV_AVC_TURNO(Cuba).ClasseEa = EA_FORTE;
  }
  else
  {
	if (AVC.Ea[Cuba].EaVMax < AVC.Param[Cuba].VEaFraco)
	{
	  SUPERV_AVC(Cuba).ClasseEa = EA_FRACO;
	  SUPERV_AVC_TURNO(Cuba).ClasseEa = EA_FRACO;
	}
	else
	{
	  SUPERV_AVC(Cuba).ClasseEa = EA_NORMAL;
	  SUPERV_AVC_TURNO(Cuba).ClasseEa = EA_NORMAL;
	}
  }

  if (((AVC.Ea[Cuba].EaHoraInicio - AVC.Ea[Cuba].EaHoraAnt) / 60L) >= AVC.Param[Cuba].EaAtrasoMax)
  {
	  AVL.Sup.AtrasoEA++;
	  AVL_TURNO.Sup.AtrasoEA++;
  	  AVL.Trab.AtrasoEATurno = AVL_TURNO.Sup.AtrasoEA;
  }


  /* -- *************** Dados medios diarios ******************* -- */
  if (AVC.Ea[Cuba].EaVMax > SUPERV_AVC(Cuba).EaVMaxDia)
	SUPERV_AVC(Cuba).EaVMaxDia = AVC.Ea[Cuba].EaVMax;

  SUPERV_AVC(Cuba).Sup.EaVMax = AVC.Ea[Cuba].EaVMax; 

  /* -- contabiliza informacoes do ultimo ea -- */
  SUPERV_AVC(Cuba).EaNumDia++;
  SUPERV_AVC(Cuba).EaNumLDia += AVC.Ea[Cuba].EaNumL;
  SUPERV_AVC(Cuba).EaDurDia += AVC.Ea[Cuba].EaDur;
  SUPERV_AVC(Cuba).EaVDiaTotBruta += (AVC.Ea[Cuba].EaVAcumBruta - AVC.Ea[Cuba].EaVAcumEspBruta);
  SUPERV_AVC(Cuba).EaPotDiaTotBruta += (AVC.Ea[Cuba].EaPotAcumBruta - AVC.Ea[Cuba].EaPotAcumEspBruta);
  SUPERV_AVC(Cuba).EaVDiaTotLiq += (AVC.Ea[Cuba].EaVAcumLiq - AVC.Ea[Cuba].EaVAcumEspLiq);
  SUPERV_AVC(Cuba).EaPotDiaTotLiq += (AVC.Ea[Cuba].EaPotAcumLiq - AVC.Ea[Cuba].EaPotAcumEspLiq);
  SUPERV_AVC(Cuba).EaEnergDiaBruta += AVC.Ea[Cuba].EaEnergBruta;
  SUPERV_AVC(Cuba).EaEnergDiaLiq += AVC.Ea[Cuba].EaEnergLiq;
  AVL.Sup.NumEaDia++;

  /* -- *************** Dados medios de turno ******************* -- */
  if (AVC.Ea[Cuba].EaVMax > SUPERV_AVC_TURNO(Cuba).EaVMaxDia)
	SUPERV_AVC_TURNO(Cuba).EaVMaxDia = AVC.Ea[Cuba].EaVMax;

/* -- Inicio - 14/06/2005 - Carlos - Tensao EA acima de VEaXLim -- */
  EaContxLim = (AVC.Ea[Cuba].EaContLXLim - AVC.Ea[Cuba].EaContLEspXLim) / (unsigned short int)(SAD_TICKS / Comum->BaseTempoMcp);
  if (EaContxLim > AVC.Ea[Cuba].EaDur)
    EaContxLim = AVC.Ea[Cuba].EaDur;	// garante que possiveis erros de arredondamento nao facam xLim maior que dur ea
  SUPERV_AVC(Cuba).EaDurXDia += EaContxLim;
/* -- Fim - 14/06/2005 - Carlos - Tensao EA acima de VEaParam -- */

  SUPERV_AVC_TURNO(Cuba).EaNumDia++;
  SUPERV_AVC_TURNO(Cuba).EaNumLDia += AVC.Ea[Cuba].EaNumL;
  SUPERV_AVC_TURNO(Cuba).EaDurDia += AVC.Ea[Cuba].EaDur;
  SUPERV_AVC_TURNO(Cuba).EaVDiaTotBruta += (AVC.Ea[Cuba].EaVAcumBruta - AVC.Ea[Cuba].EaVAcumEspBruta);
  SUPERV_AVC_TURNO(Cuba).EaPotDiaTotBruta += (AVC.Ea[Cuba].EaPotAcumBruta - AVC.Ea[Cuba].EaPotAcumEspBruta);
  SUPERV_AVC_TURNO(Cuba).EaVDiaTotLiq += (AVC.Ea[Cuba].EaVAcumLiq - AVC.Ea[Cuba].EaVAcumEspLiq);
  SUPERV_AVC_TURNO(Cuba).EaPotDiaTotLiq += (AVC.Ea[Cuba].EaPotAcumLiq - AVC.Ea[Cuba].EaPotAcumEspLiq);
  SUPERV_AVC_TURNO(Cuba).EaEnergDiaBruta += AVC.Ea[Cuba].EaEnergBruta;
  SUPERV_AVC_TURNO(Cuba).EaEnergDiaLiq += AVC.Ea[Cuba].EaEnergLiq;
  AVL_TURNO.Sup.NumEaDia++;
  AVL.Trab.NumEaDiaTurno = AVL_TURNO.Sup.NumEaDia;

/* -- Inicio - 14/06/2005 - Carlos - Tensao EA acima de VEaXLim -- */
  SUPERV_AVC_TURNO(Cuba).EaDurXDia += EaContxLim;
/* -- Fim - 14/06/2005 - Carlos - Tensao EA acima de VEaParam -- */

  /*-- Contabiliza sucesso previsao na ocorrencia de efeito anodico --*/
  if (EST_AVC(Cuba).EaPrevVirada eq VERDADEIRO)
  {
	EST_AVC(Cuba).EaPrevVirada = FALSO;
	SUPERV_AVC(Cuba).NumFimOkPrevDia++;
	SUPERV_AVC_TURNO(Cuba).NumFimOkPrevDia++;
	SUPERV_AVC(Cuba).EfPrevEaDia++;
	SUPERV_AVC_TURNO(Cuba).EfPrevEaDia++;
	/*-- Contabilizar Duracao entre o ea e a previsao --*/
	SUPERV_AVC(Cuba).DurPrevEaDia += AVC.Ea[Cuba].EaHoraInicio - AVC.Ea[Cuba].EaPrevT0;
	SUPERV_AVC_TURNO(Cuba).DurPrevEaDia += AVC.Ea[Cuba].EaHoraInicio - AVC.Ea[Cuba].EaPrevT0;
  }

/* -- Alteracao - inicio - 08/03/2005 - Carlos - Relat. integracao diario/turno -- */
  IntegEa1h(Cuba);
/* -- Alteracao - fim - 08/03/2005 - Carlos - Relat. integracao diario/turno -- */

/* -- Inicio - 14/06/2005 - Carlos - Tensao EA acima de VEaXLim -- */
  AVC.Ea[Cuba].EaContLXLim = 0;	
/* -- Fim - 14/06/2005 - Carlos - Tensao EA acima de VEaParam -- */

  AVC.Ea[Cuba].EaContL=0;	
  AVC.Ea[Cuba].EaVAcumEspBruta = 0;
  AVC.Ea[Cuba].EaPotAcumEspBruta = 0;
  AVC.Ea[Cuba].EaVAcumEspLiq = 0;
  AVC.Ea[Cuba].EaPotAcumEspLiq = 0;
  AVC.Ea[Cuba].EaContLEsp = 0;
  AVC.Ea[Cuba].EaContLEspXLim = 0;	/* Contador de cic. de leit. de tensao EA acima de VEaXLim em espera de fim ea */
  AVC.User1[Cuba].NumDB = 0;

  MontaHoraMinSeg(AVC.Ea[Cuba].EaDur, Par1, "%02d:%02d:%02d");
  GeraEvento(FIM_EA, Cuba, -1, Par1, AVC.Ea[Cuba].EaVMax,
			 (AVC.Ea[Cuba].EaEnergLiq/1000.0)/3600.0, AVC.Ea[Cuba].EaVBruta,
			 (AVC.Ea[Cuba].EaEnergBruta/1000.0)/3600.0);
  ComandaLampEa(Cuba,DESLIGAR);
  AlteracaoTabela(TABELA_EST_AVC);	/*Informa que houve alteracao no EST_AVC */
  AlteracaoTabela(TABELA_AVC);	/*Informa que houve alteracao no AVC */
  AlteracaoTabela(TABELA_SUPERV_AVC);	/*Informa alteracao no SUPERV_AVC */
  AlteracaoTabela(TABELA_HIST_TURNO);	/*Informa alteracao na tabela de turno */
}

/* -- Alteracao - inicio - 08/03/2005 - Carlos - Relat. integracao diario/turno -- */
void IntegEa1h(int Cuba)
{
  float EaVMed;
  float	EaDur;

  EaVMed = (AVC.Ea[Cuba].EaVAcumBruta - AVC.Ea[Cuba].EaVAcumEspBruta) / AVC.Ea[Cuba].EaNumL;
  EaDur  = (float) AVC.Ea[Cuba].EaDur;

  // Calculo de integracao diaria
  AVL.Intg1h.EaQtd1h++;
  if (AVC.Ea[Cuba].EaVMax > AVL.Intg1h.EaVMax1h)
	AVL.Intg1h.EaVMax1h = AVC.Ea[Cuba].EaVMax;

  AVL.Intg1h.EaVMed1h = CalcMedDin(AVL.Intg1h.EaVMed1h, AVL.Intg1h.EaQtd1h, EaVMed);
  AVL.Intg1h.EaDur1h  = CalcMedDin(AVL.Intg1h.EaDur1h,  AVL.Intg1h.EaQtd1h, EaDur);

  if (EST_AVC(Cuba).EaPrevVirada eq VERDADEIRO)
	AVL.Intg1h.NPrevEa1h++;
}

/*
--------------------------------------------------------------------------------
	CalcMedDin	-	Funcao auxiliar p/ calculo de media dinamica
--------------------------------------------------------------------------------
*/

float CalcMedDin(double Parcela1, int Cont, double Parcela2)
{
  double	Media;

  Media = ( (Parcela1 * (double)(Cont-1)) + Parcela2) / (double)Cont; 
  return((float)Media);
}

/* -- Alteracao - fim - 08/03/2005 - Carlos - Relat. integracao diario/turno -- */

/*
-------------------------------------------------------------------------------
  ContabEstatEa - Contabiliza dados para o relatorio de estatistica	de Efeito
		Anodico. Esse relatorio sera calculado a partir dos vetores da estru-
		tura de supervisao do AVC, os quais sao  contabilizados  conforme  os
		limites declarados nos vetores dessa funcao. Abaixo,  segue o lay-out
		do relatorio para maior facilidade de compreensao:

			Relatorio Historico de Estatistica de Efeito Anodico

		Duracao    %      VMax     %      Interv   %    Interv Prev   %
		 [Min]                            [Hora]           [Min]
		   0      xxx.x   <= 15   xxx.x    <= 8   xxx.x    <= 10     xxx.x
		   1      xxx.x   15-20   xxx.x    8-16   xxx.x    11-20     xxx.x
		   2      xxx.x   20-25   xxx.x   16-24   xxx.x    20-30     xxx.x
		   3      xxx.x   25-30   xxx.x   24-32   xxx.x    30-40     xxx.x
		   4      xxx.x   30-35   xxx.x   32-40   xxx.x    40-50     xxx.x
		   5      xxx.x   35-40   xxx.x   40-48   xxx.x    50-60     xxx.x
		   6      xxx.x   40-45   xxx.x   48-56   xxx.x    60-70     xxx.x
		   7      xxx.x    > 45   xxx.x   56-64   xxx.x    70-80     xxx.x
		   8      xxx.x                   64-72   xxx.x    80-90     xxx.x
		   9      xxx.x                   72-80   xxx.x     > 90     xxx.x
		  > 9     xxx.x                    > 80   xxx.x

-------------------------------------------------------------------------------
*/

void ContabEstatEa(int Cuba)
{
		// mm:ss =     0:30  1:30  2:30  3:30  4:30  5:30  6:30  7:30  8:30  9:30
  int   LimDur[10] = { 30,   90,   150,  210,  270,  330,  390,  450,  510,  570 };                /* Seg  */
  int   LimPrev[9] = { 10,   20,   30,   40,   50,   60,   70,   80,   90 };                       /* Min.  */
  float LimVMax[7] = { 15.0, 20.0, 25.0, 30.0, 35.0, 40.0, 45.0 };                                 /* Volts */
  int	Ind;
  int	FlagPrev=FALSO;
  int	FlagDur=FALSO;
  int	FlagVMax=FALSO;
/* -- Inicio - 14/06/2005 - Carlos - Tensao EA acima de VEaXLim -- */
  int	FlagXDur=FALSO;
  short unsigned int EaDurXLim;
  int	FlagInt=FALSO;
  int   LimInt[14] = { 8,    16,   24,   32,   40,   48,   56,   64,   72,   80,  88,  96,  104, 112 }; /* Horas */

/* -- Fim - 14/06/2005 - Carlos - Tensao EA acima de VEaParam -- */

  for (Ind = 0; Ind < 15; Ind++)
  {
	/*-- Contabiliza estatistica de previsao --*/
	if ( (FlagPrev ne VERDADEIRO) and (EST_AVC(Cuba).EaPrevVirada eq VERDADEIRO) )
	{
	  if (Ind < 9)
	  {
		if ((AVC.Ea[Cuba].EaHoraInicio - AVC.Ea[Cuba].EaPrevT0) / 60L
						 < LimPrev[Ind])
		{
		  FlagPrev = VERDADEIRO;
		  SUPERV_AVC(Cuba).ContPrevEa[Ind]++;
		  SUPERV_AVC_TURNO(Cuba).ContPrevEa[Ind]++;
		}
	  }
	  else
	  {
		FlagPrev = VERDADEIRO;
		SUPERV_AVC(Cuba).ContPrevEa[Ind]++;
		SUPERV_AVC_TURNO(Cuba).ContPrevEa[Ind]++;
	  }
	}

	/*-- Contabiliza estatistica de duracao --*/
	if (FlagDur ne VERDADEIRO)
	{
	  if (Ind < 10)
	  {
		if (AVC.Ea[Cuba].EaDur < LimDur[Ind])
		{
		  FlagDur = VERDADEIRO;
		  SUPERV_AVC(Cuba).ContDurEa[Ind]++;
		  SUPERV_AVC_TURNO(Cuba).ContDurEa[Ind]++;

		  SUPERV_AVC(Cuba).DurEa[Ind]       += AVC.Ea[Cuba].EaDur;
		  SUPERV_AVC_TURNO(Cuba).DurEa[Ind] += AVC.Ea[Cuba].EaDur;
		}
	  }
	  else
	  {
		FlagDur = VERDADEIRO;
		SUPERV_AVC(Cuba).ContDurEa[Ind]++;
		SUPERV_AVC_TURNO(Cuba).ContDurEa[Ind]++;

        SUPERV_AVC(Cuba).DurEa[Ind]       += AVC.Ea[Cuba].EaDur;
        SUPERV_AVC_TURNO(Cuba).DurEa[Ind] += AVC.Ea[Cuba].EaDur;
	  }
	}

	/*-- Contabiliza estatistica de intervalo entre EA --*/
    if (FlagInt ne VERDADEIRO)
    {
      if (Ind < 14)
      {
  	    if ((AVC.Ea[Cuba].EaHoraInicio - AVC.Ea[Cuba].EaHoraAnt) / 3600L
						 < LimInt[Ind])
	    {
	      FlagInt = VERDADEIRO;
	      SUPERV_AVC(Cuba).ContIntEa[Ind]++;
	      SUPERV_AVC_TURNO(Cuba).ContIntEa[Ind]++;
	      
		  if (Ind < 3)
		  {
		    AVL_TURNO.Sup.Ea24h++;
		    AVL.Sup.Ea24h++;
  		    AVL.Trab.Ea24hTurno = AVL_TURNO.Sup.Ea24h;
	 	  }  
	    }
	  }
 	  else
	  {
	    FlagInt = VERDADEIRO;
	    SUPERV_AVC(Cuba).ContIntEa2[Ind-14]++;
	    SUPERV_AVC_TURNO(Cuba).ContIntEa2[Ind-14]++;
	  }
    }
    

	/*-- Contabiliza estatistica de VMax --*/
	if (FlagVMax ne VERDADEIRO)
	{
	  if (Ind < 7)
	  {
		if (AVC.Ea[Cuba].EaVMax < LimVMax[Ind])
		{
		  FlagVMax = VERDADEIRO;
		  SUPERV_AVC(Cuba).ContVMaxEa[Ind]++;
		  SUPERV_AVC_TURNO(Cuba).ContVMaxEa[Ind]++;
		}
	  }
	  else
	  {
		FlagVMax = VERDADEIRO;
		SUPERV_AVC(Cuba).ContVMaxEa[Ind]++;
		SUPERV_AVC_TURNO(Cuba).ContVMaxEa[Ind]++;
	  }
	}

/* -- Inicio - 14/06/2005 - Carlos - Tensao EA acima de VEaXLim -- */
	/*-- Contabiliza estatistica de EaDurXLim --*/
	// Converte de ciclos de leitura para segundos
    EaDurXLim = (AVC.Ea[Cuba].EaContLXLim - AVC.Ea[Cuba].EaContLEspXLim) / (unsigned short int) (SAD_TICKS / Comum->BaseTempoMcp);
	if (FlagXDur ne VERDADEIRO)
	{
	  if (Ind < 10)
	  { 
//        if (EaDurXLim < LimDur[Ind])
		if (AVC.Ea[Cuba].EaDur < LimDur[Ind]) // alteracao aqui (labanca)
		{
		  FlagXDur = VERDADEIRO;
		  SUPERV_AVC(Cuba).EaDurXLim[Ind] += EaDurXLim;
		  SUPERV_AVC_TURNO(Cuba).EaDurXLim[Ind] += EaDurXLim;
		}
	  }
	  else
	  {
		FlagXDur = VERDADEIRO;
		SUPERV_AVC(Cuba).EaDurXLim[Ind] += EaDurXLim;
		SUPERV_AVC_TURNO(Cuba).EaDurXLim[Ind] += EaDurXLim;
	  }
	}
/* -- Fim - 14/06/2005 - Carlos - Tensao EA acima de VEaParam -- */

  }
}
