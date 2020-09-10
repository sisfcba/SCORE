/******************************************************************************

			 ACCENTURE - ACCENTURE PLANT AND AUTOMATION SOLUTIONS
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 5.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO SA

	SISTEMA		: AUTOMACAO DAS SALAS 125 KA I, II, III, IV, V, VI E VII

	ARQUIVO		: RecChavesCBA.h

	CONTEUDO	: Prologo do modulo RecChavesCBA

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 1.0		  -		  DATA  : 03/11/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
30/10/2012 | Separacao para o kit de desenvolvimento             | Leonel
-------------------------------------------------------------------------------
$Id: RecChavesCBA.h,v 1.1.2.1 2012/10/30 13:09:01 leo Exp $

$Log: RecChavesCBA.h,v $
Revision 1.1.2.1  2012/10/30 13:09:01  leo
Separacao para o kit de desenvolvimento da CBA.

******************************************************************************/
/*
-------------------------------------------------------------------------------
						   Definicao de compilacao condicional
-------------------------------------------------------------------------------
*/
#ifndef		_REC_CHAVES_CBA_H

#define		_REC_CHAVES_CBA_H

/*
-------------------------------------------------------------------------------
						   Includes
-------------------------------------------------------------------------------
*/
#include	<Score.h>
#include	<ScoreErros.h>
#include	<Eventos.h>
#include	<UsuRemota.h>
#include	<Prototipos.h>
#include	<ScoreMsgs.h>
#include	<AjusteCamisa.h>

/*
-------------------------------------------------------------------------------
						   Definicoes
-------------------------------------------------------------------------------
*/

/********************* teste para plataforma ******************/
/* Forca entrada local/auto para auto para teste em plataforma
   com remotas ligadas mas sem I/O conectados */
// ****** #define	INCLUI_SIMULACAO_PLATAFORMA

/* -- tempo manter lampada de rec. ligada -- */
#define		TEMPO_RECONHECE		(BASE_TEMPO_REMOTA)	/* -- 1 seg -- */

/* -- Estado correspondente a indicacao de quebrada -- */
#define		ESTADO_QUEB_ATIVA		0
/* -- Estado correspondente a indicacao de corrida -- */
#define		ESTADO_CORR_ATIVA		0
/* -- Estado correspondente a indicacao de movimentacao anodo -- */
#define		ESTADO_MOVEU_ANODO		0
/* -- Estado correspondente a indicacao de troca de anodo -- */
#define		ESTADO_TROCAANODO_ATIVO	0
/* -- Estado correspondente a chave manual ligada -- */
#define		ESTADO_MANUAL_ATIVO		0
/* -- Estado correspondente a chave automatico ligada -- */
#define		ESTADO_AUTOMATICO_ATIVO	0
/* -- Estado correspondente a botoeira reset ea -- */
#define		ESTADO_RESET_EA			0
/* -- Estado correspondente a botoeira de troca de anodo -- */
#define		ESTADO_TROCAPINOS_ATIVO	0
/* -- Estado correspondente a indicacao de subida de camisa -- */
#define		ESTADO_SUBIU_CAMISA		0
/* -- Estado correspondente a indicacao de descida de camisa -- */
#define		ESTADO_DESCEU_CAMISA	0
/* -- Estado correspondente a solicitacao de check up -- */
#define		ESTADO_CHECKUP_ATIVO	0
/* -- Alteracao - Inicio - 09/05/2002 - Leonel - Inclusao da sala 7 125ka -- */
#define		ESTADO_SOPRO_ATIVO		0
/* -- Alteracao - Fim - 09/05/2002 - Leonel - Inclusao da sala 7 125ka -- */
#define		ESTADO_RELE_TEMPOMM_ATIVO	0
#define		ESTADO_MCRUZEIRO_ATIVO		1

/* -- Estado de alarme ativado na remota -- */
#define		ESTADO_ALARME			1
#define		ESTADO_NORMAL			0

/* -- Estados do algoritmo de alimentacao -- */
#define		EST_ALIM_PADRAO				1	/* -- normal -- */
#define		EST_ALIM_EA					2	/* -- tratamento de Efeito anodico -- */
#define		EST_ALIM_SUSPENSA			3	/* -- tratamento qdo alim. suspensa -- */
#define		EST_ALIM_EXCECAO			4	/* -- tratamento qdo check inicial -- */

/*
-------------------------------------------------------------------------------
						   Macros
-------------------------------------------------------------------------------
*/
#define		PegaEstadoIO(Cuba,Bit)	((AVC.Cleit[Cuba].EstadoIO >> ((Bit)-1)) andb 1)
#define		LigaBit(Masc,Bit)		((1L << ((Bit)-1)) orb Masc)
#define		DesligaBit(Masc,Bit)	((notb(1L << ((Bit)-1))) andb Masc)

/*
-------------------------------------------------------------------------------
						   Prototipos
-------------------------------------------------------------------------------
*/
int		PegaBit(t_mascara_bits *Masc,int Entrada);
int		ConvRemOutras(int Canal,int Nodo);
void	CancelaAjusteCamisa(int Cuba);
/* -- Alteracao - Inicio - Robson - 16/01/2001 -- modularizacao -- */
void TrataBotoeiraQuebrada(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo);
void TrataBotoeiraCorrida(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo);
void TrataBotoeiraResetEA(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo);
void TrataChaveAutoMan(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo);
void TrataBotoeiraTrocaPinos(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo);
void TrataSubiuAnodo(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo);
void TrataDesceuAnodo(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo);
void TrataSubiuCamisa(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo,int *EnviaReconhece);
void TrataDesceuCamisa(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo);
void TrataBotoeiraChkUp(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo);
/* -- Alteracao - Inicio - 09/05/2002 - Leonel - Inclusao da sala 7 125ka -- */
void TrataMoveuAnodo125ka(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo);
void TrataMoveuCamisa125ka(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						    time_t	HoraAtual,float VCicCont,float VInst,float VAlvo,
							int *EnviaReconhece);
void TrataSopro(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						    time_t	HoraAtual,float VCicCont,float VInst,float VAlvo,
							int *EnviaReconhece);
/* -- Alteracao - Fim - 09/05/2002 - Leonel - Inclusao da sala 7 125ka -- */

void TrataChaveMCruzeiro(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo);

/********************* teste para plataforma ******************/
#ifdef	INCLUI_SIMULACAO_PLATAFORMA
void DesligaMascBit(t_mascara_bits *Masc,int Entrada);
#endif
/********************* teste para plataforma ******************/

#endif

/* -- Fim do RecChavesCBA.h -- */
