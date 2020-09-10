/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DAS SALAS 125 KA I E VII

	ARQUIVO		: RelSSF.h

	CONTEUDO	: Programa que exporta dados diarios para Sistema de Informacao
					Salas Fornos.

	AUTOR		: Marco Aurelio M. Lopes

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 01 - 24/01/13

	HISTORICO DAS EDICOES

-------------------------------------------------------------------------------
dd/mm/aa   | Descricao                                               | autor
-------------------------------------------------------------------------------
24/01/2013 | Edicao inicial                                          | Marco
-------------------------------------------------------------------------------

******************************************************************************/

	/*-- INCLUSAO DE OUTROS ARQUIVOS --*/

#include <Score.h>
#include <Prototipos.h>
#include <VarsComum.h>
#include <Relatorios.h>
#include <BdScore.h>
#include <ScoreMsgs.h>
#include <ScoreErros.h>
#include <RelPrototipos.h>

#ifdef OPERACAO_WINDOWS
  #include <OperacaoBibW.h>
#else
  #include <OperacaoBib.h>
  #include <WindowsCBA.h>
  #include <KeysCBA.h>
#endif

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

	/*-- DEFINICAO DE CONSTANTES     --*/

/*-- Numero de argumentos do relatorio --*/
#ifndef OPERACAO_WINDOWS
  #ifdef	REL_TURNO
	#define	NUM_ARGS		8
  #else
	#define	NUM_ARGS		5
  #endif
#else
  #ifdef	REL_TURNO
	#define	NUM_ARGS		6
  #else
	#define	NUM_ARGS		5
  #endif
#endif

/*-- Definicoes nulas. --*/
#define TEMPO_NUL			"0:00"

	/*-- DEFINICAO DE TIPOS PROPRIOS --*/

   /*-- Estruturas para formatacao da tela do relatorio --*/

/*-- Cabecalho --*/
typedef
  struct VarCabec
  {
#ifdef OPERACAO_WINDOWS
	char	Selecao[14];
	char	Algorit[11];
#else
    int		CubaInicial;
    int		CubaFinal;
#endif
    int		DiaInicial;
    int		MesInicial;
    int		AnoInicial;
    int		DiaFinal;
    int		MesFinal;
    int		AnoFinal;
  } t_cabec;

/*-- Area de Dados --*/
typedef
  struct VarDados
  {
    char	Dia[9];
	int		NumCuba;
	float	Placa;
	int		Inc;
    float   Total;
	float	RRap;
	float	RLen;
	int		FreqEA;
	float	VMaxEA;
	float	Fluoreto;
	float	Fluorita;
	int		Banho;
	int		Metal;
	int		Temp;
	int		Vida;
	float	Corrente;
	char	Ligada[3];
	float	DurEA;
	float 	VLiquida;
	float	VAlvo;
	int		MovCima;
	int		MovBaixo;
	int		FalhaMov;
	float	VMedEa;
	int		QP;
	int		PrevEa;
	int		EaMenor24h;
	int		EaMaior72h;
	int		EaMaior96h;	
	int		NQueb;
	int		AdFluoreto;
	long	IntervCorr;
	long	IntervRefCorr;
	long	IntervRefQueb;
	int		NumDBDia;
	int 	NumDBConsec;
	int		NumDBQueb;
	float	DifAlFalhaMov;
	float	DifAlBandaMorta;
	float	DifAlInibPrev;
	float	DifAlInibQueb;
	float	DifAlIntervMov;
	float	DifAlManual;
	float	DifAlInibUsu;
	float	DifAlDesvio;
	float 	DeltaR;	

  } t_dados;

/*-- Rodape --*/
typedef
  struct VarRodape
  {
	float	MPlaca;
	float	MAlvo;
	float	MLiqui;
    float   MTotal;
  } t_rodape;

/*-- Estrutura temporaria --*/
