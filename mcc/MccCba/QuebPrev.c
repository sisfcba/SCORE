/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: PrevQueb.c

	CONTEUDO	: Modulo de Controle das Cubas - MCC - Procedimentos do algo-
                  ritmo de solicitacao de quebrada preventiva.

	AUTOR		: Carlos Cezar Silva Lage

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 1.0			-		DATA	:	15/04/98

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
dd/mm/aa | Descricao                                              | Autor
-------------------------------------------------------------------------------
09/07/99 | Incluida desativacao via programa do operador          | Carlos
-------------------------------------------------------------------------------
30/11/99 | Corrigido ativacao increm. queb. prev. para nao gerar  | Carlos
         | mais de um ciclo desse increm. durante efeito queb.    |
-------------------------------------------------------------------------------
02/02/01 | Desliga lampada no fim de quebrada preventiva          | Carlos
-------------------------------------------------------------------------------
******************************************************************************/

/******************************** Revisoes ***********************************
$Id: QuebPrev.c,v 1.1.2.1 2012/09/28 17:09:28 leo Exp $

$Log: QuebPrev.c,v $
Revision 1.1.2.1  2012/09/28 17:09:28  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

Revision 1.4  2005/10/14 18:04:36  leo
Alteracao da unidade de engenharia dos parametros de quebrada preventiva de horas
para minutos.

Revision 1.3  2005/05/31 19:37:34  leo
Correcoes feitas durante primeira pre-operacao CBA sala 125kA VI

Revision 1.2  2004/08/03 19:53:13  clage
Alteracao para flexibilizacao de quebrada preventiva

******************************************************************************/



/**** #define		ATIVA_DEPURACAO  ****/

// Definicao de constantes de teste
#define USA_RLENT					1
#define USA_RRAP					2
#define USA_INC_OPER				3
#define USA_ATRASO_EA				4
#define USA_EA_MAX					5
#define USA_AEK_MAX					6

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

time_t HoraUltQueb[MAX_CUBAS];

/*
-------------------------------------------------------------------------------
                           Prototipos
-------------------------------------------------------------------------------
*/
void IniQuebPrev(int Cuba);
void QuebradaPreventiva(int Cuba);
int  TesteStatus(int Cuba, int Condicao);

/*
-------------------------------------------------------------------------------
							Funcoes
-------------------------------------------------------------------------------
*/

/*
--------------------------------------------------------------------------------
| IniQuebPrev - Inicializa variaveis referentes a quebrada preventiva da cuba  |
--------------------------------------------------------------------------------
*/
void IniQuebPrev(int Cuba)
{
	PosicaoGlobal = 126;
	/* -- inicializa variaveis da quebrada preventiva -- */
	EST_AVC(Cuba).Est.QuebPrev     = FALSO;
	AVC.User1[Cuba].NumQuebPrev    = 0;
	AVC.User1[Cuba].NumPrevQPrev   = 0;
	AVC.User1[Cuba].ContDurQPrev   = 0L;
	EST_AVC(Cuba).Est.QuebPrevInib = QPREV_SEM_INIBICAO;
	AVC.User1[Cuba].ContInibQPrev  = 0L;
	HoraUltQueb[Cuba] = 0L;
}

/*
--------------------------------------------------------------------------------
| QuebradaPreventiva - Executa a quebrada preventiva da cuba                   |
--------------------------------------------------------------------------------
*/
void QuebradaPreventiva(int Cuba)
{
	int IntervCicContSeg;
	char TempoUltEA[7];
	long	HoraUltimoEA;
	int	HoraEA, MinEA;

	PosicaoGlobal = 127;

  	IntervCicContSeg = IntervCicCont * 60;
	if ((AVC.ParUser1[Cuba].HabQPrev eq VERDADEIRO) and
		(EST_AVC(Cuba).Est.HabQPrevOpe eq VERDADEIRO))
	{
		if (EST_AVC(Cuba).Est.QuebPrev eq FALSO)
		{
			if (
				
				(EST_AVC(Cuba).EaPrev eq VERDADEIRO) and
				(EST_AVC(Cuba).Est.QuebPrevInib eq QPREV_SEM_INIBICAO) and
				(
					(
					AVC.User1[Cuba].AtrasouEa eq VERDADEIRO and                        
					((HoraAtualCtrl - AVC.Ea[Cuba].EaHoraInicio) >=                    
										AVC.ParUser1[Cuba].LimQPrevEaAtraso*60) and
					((HoraAtualCtrl - AVC.Cleit[Cuba].HoraUltQueb) <=
											AVC.ParUser1[Cuba].IntMinQQPrev*60L) and
					((HoraAtualCtrl - AVC.Ea[Cuba].EaHoraInicio) <= 
											AVC.ParUser1[Cuba].IntervQuebProg)
					)
					
					or
					
					((TesteStatus(Cuba,USA_RLENT) eq VERDADEIRO) and
					(TesteStatus(Cuba,USA_RRAP) eq VERDADEIRO) and
					(TesteStatus(Cuba,USA_INC_OPER) eq VERDADEIRO) and
					(AVC.ParUser1[Cuba].MaxQPrevEa > AVC.User1[Cuba].NumQuebPrev) and
					((HoraAtualCtrl - AVC.Cleit[Cuba].HoraUltQueb) >=
											(AVC.ParUser1[Cuba].IntMinQQPrev*60L)) and
					((HoraAtualCtrl - AVC.User1[Cuba].HoraUltQPrev) >=
											(AVC.ParUser1[Cuba].NHorRefQPrev*60L)) and
					(TesteStatus(Cuba,USA_ATRASO_EA) eq VERDADEIRO) and
					(TesteStatus(Cuba,USA_EA_MAX) eq VERDADEIRO) and
					(TesteStatus(Cuba,USA_AEK_MAX) eq VERDADEIRO) and
					EST_AVC(Cuba).Est.ForcaEA eq FALSO and
					(fabs(AVC.User2[Cuba].HoraProxQuebReal - HoraAtualCtrl) >= 
										(AVC.ParUser1[Cuba].InibeQPQuebProg*60)))
				)
				)
	  		{ /*-- Inicializacao da quebrada preventiva --*/
				PosicaoGlobal = 128;
				if(AVC.User1[Cuba].AtrasouEa eq VERDADEIRO)
	 			{
		  			AVC.User1[Cuba].AtrasouEa = FALSO;	
				}
				ComandaLampEa(Cuba,PISCAR_RAPIDO);
				AvcLocal[Cuba].IndicouQPrev=VERDADEIRO;
				EST_AVC(Cuba).Est.QuebPrev = VERDADEIRO;
				SUPERV_AVC(Cuba).Sup.NumQuebPrevDia++;
				SUPERV_AVC_TURNO(Cuba).Sup.NumQuebPrevDia++;
				HoraUltimoEA = HoraAtualCtrl - AVC.Ea[Cuba].EaHoraInicio;
				HoraEA = HoraUltimoEA / 3600;
				MinEA = (HoraUltimoEA - (HoraEA * 3600)) / 60;
				sprintf(TempoUltEA, "%03d:%02d", HoraEA, MinEA);  
				AVC.User1[Cuba].HoraUltQPrev = HoraAtualCtrl;
				AVC.User1[Cuba].ContDurQPrev = IntervCicContSeg;
				GeraEvento(INICIO_QUEB_PREV, Cuba, -1, AVC.User1[Cuba].NumQuebPrev+1, 
							SUPERV_AVC(Cuba).Sup.NumQuebPrevDia, 
							AVC.CcontMcp[Cuba].RCicContlBruta * 1000000, TempoUltEA);
			}
		}
		else
		{ /*-- Tratamento durante quebrada preventiva --*/
			PosicaoGlobal = 129;
			AVC.User1[Cuba].ContDurQPrev += IntervCicContSeg;
			if ((EST_AVC(Cuba).Quebrada eq VERDADEIRO) and 
				(HoraUltQueb[Cuba] ne AVC.Cleit[Cuba].HoraUltQueb) and 
				(EST_AVC(Cuba).TrataIncUsuario eq FALSO)) 
			{
				EST_AVC(Cuba).TrataIncUsuario = VERDADEIRO;
				HoraUltQueb[Cuba] = AVC.Cleit[Cuba].HoraUltQueb;
			}
		}
  	}
  	else
  	{ /*-- Desabilitacao da quebrada preventiva --*/
		if (EST_AVC(Cuba).Est.QuebPrev eq VERDADEIRO)
		{
			PosicaoGlobal = 130;
	  		EST_AVC(Cuba).Est.QuebPrev = FALSO;
			if (AVC.ParUser1[Cuba].HabQPrev ne VERDADEIRO)
				GeraEvento(FIM_QUEB_PREV, Cuba, -1, "Desab.", "Config");
			else
				GeraEvento(FIM_QUEB_PREV, Cuba, -1, "Desat.", "Operador");

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

	if (EST_AVC(Cuba).Est.QuebPrevInib eq INIBICAO_POR_TEMPO)
	{
		if (AVC.User1[Cuba].ContInibQPrev > 0L)
		{
			PosicaoGlobal = 131;
			AVC.User1[Cuba].ContInibQPrev  -= IntervCicContSeg;
			SUPERV_AVC(Cuba).Sup.TempoInibQPrev += IntervCicContSeg;
			SUPERV_AVC_TURNO(Cuba).Sup.TempoInibQPrev += IntervCicContSeg;
		}
		else
		{
			AVC.User1[Cuba].ContInibQPrev  = 0L;
			EST_AVC(Cuba).Est.QuebPrevInib = QPREV_SEM_INIBICAO;
		}
  	}
  	else
  	{
		if (EST_AVC(Cuba).Est.QuebPrevInib eq INIBICAO_PROXIMO_EA)
		{
			SUPERV_AVC(Cuba).Sup.TempoInibQPrev += IntervCicContSeg;
			SUPERV_AVC_TURNO(Cuba).Sup.TempoInibQPrev += IntervCicContSeg;
		}
  	}
}

/*
--------------------------------------------------------------------------------
| TesteStatus - Flexibiliza testes de condicoes de quebrada preventiva         |
--------------------------------------------------------------------------------
*/
int TesteStatus(int Cuba, int Condicao)
{
	int  Status;

	Status = VERDADEIRO;
	PosicaoGlobal = 132;

	switch(Condicao)
	{
			case USA_RLENT:
				if (AVC.ParUser1[Cuba].UsaRLent eq VERDADEIRO)
					Status = (EST_AVC(Cuba).RuidoLent eq FALSO)? VERDADEIRO : FALSO;
				break;

			case USA_RRAP:
				if (AVC.ParUser1[Cuba].UsaRRap eq VERDADEIRO)
					Status = (EST_AVC(Cuba).RuidoRap eq FALSO)? VERDADEIRO : FALSO;
				break;

			case USA_INC_OPER:
				if (AVC.ParUser1[Cuba].UsaIncOpe eq VERDADEIRO)
					Status = (AVC.Ccont[Cuba].HabIncOper eq FALSO)? VERDADEIRO : FALSO;
				break;

			case USA_ATRASO_EA:
				if (AVC.ParUser1[Cuba].UsaAtrasoEa eq VERDADEIRO)
				{
					if ((HoraAtualCtrl - AVC.Ea[Cuba].EaHoraInicio) <=
											(AVC.Param[Cuba].EaAtrasoMax*60L))
						Status = VERDADEIRO;
					else
						Status = FALSO;
				}
				break;

			case USA_EA_MAX:
				if (AVC.ParUser1[Cuba].UsaMaxEa eq VERDADEIRO)
				{
					if (AVC.Ea[Cuba].EaVMax >= AVC.Param[Cuba].VEaFraco) and
						((HoraAtualCtrl - AVC.Ea[Cuba].EaHoraInicio) >=
											(AVC.ParUser1[Cuba].LimInfQPrevEa*60L)) and
						((HoraAtualCtrl - AVC.Ea[Cuba].EaHoraInicio) <=
							((AVC.Param[Cuba].EaAtrasoMax - AVC.ParUser1[Cuba].LimSupQPrevEa) * 60L)))
						Status = VERDADEIRO;
					else
						Status = FALSO;
				}
				break;
			
			case USA_AEK_MAX:
				if (AVC.ParUser1[Cuba].UsaMaxAEK eq VERDADEIRO)
				{
					if (AVC.User1[Cuba].AEKVMax >= AVC.Param[Cuba].VEaFraco)
						((HoraAtualCtrl - AVC.Ea[Cuba].EaHoraInicio) >=
											(AVC.ParUser1[Cuba].LimInfQPrevEa*60L)) and
						((HoraAtualCtrl - AVC.Ea[Cuba].EaHoraInicio) <=
							((AVC.Param[Cuba].EaAtrasoMax - AVC.ParUser1[Cuba].LimSupQPrevEa) * 60L)))
						Status = VERDADEIRO;
					else
						Status = FALSO;
				}
				break;
	}
	return(Status);
}