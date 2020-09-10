/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DAS SALAS 125 KA I E VII

	ARQUIVO		: RelPerdEn.h

	CONTEUDO	: Relatorio de perda de energia por falhas

	AUTOR		: Marco Aurelio Moreira Lopes

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 01 - 03/12/2012

	HISTORICO DAS EDICOES

-------------------------------------------------------------------------------
dd/mm/aa   | Descricao                                               | autor
-------------------------------------------------------------------------------
03/12/2012 | Edicao inicial                                          | Marco
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
	#define	NUM_ARGS		7
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
#ifdef	REL_TURNO
	char	Turno[MAX_ID_TURNO];
#endif
  } t_cabec;

/*-- Area de Dados --*/
typedef
  struct VarDados
  {
    int		NumCuba;
	char	SinEst[2];
	float	FCima;
	float	FBaixo;
	float	RCima;
    float   RBaixo;
	float	CCima;
	float	CBaixo;
    float   GCima;
	float	GBaixo;
  } t_dados;

/*-- Rodape --*/
typedef
  struct VarRodape
  {
	float	FCima;
	float	FBaixo;
	float	RCima;
    float	RBaixo;
	float	CCima;
	float	CBaixo;
    float	GCima;
	float	GBaixo;
	float	TFCima;
	float	TFBaixo;
	float	TRCima;
    float	TRBaixo;
	float	TCCima;
	float	TCBaixo;
    float	TGCima;
	float	TGBaixo;

  } t_rodape;

