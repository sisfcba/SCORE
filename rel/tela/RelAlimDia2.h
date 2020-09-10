/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II E III

	ARQUIVO		: RelAlimDia2.h

	CONTEUDO	: Contem a inclusao de arquivos, constantes, variaveis  e
				  estruturas necessarias  a  geracao  do  relatorio diario
				  de efeito anodico das cubas.

	AUTOR		: Ricardo Teixeira Leite Mourao / Robson

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 00 - 08/09/94

	OBSERVACAO	: 

	HISTORICO DAS EDICOES

-------------------------------------------------------------------------------
dd/mm/aa | Descricao                                                 | autor
-------------------------------------------------------------------------------
27/09/94 | Adaptacao para geracao do relatorio de turno.		     | Carlos
-------------------------------------------------------------------------------
06/10/94 | Inclusao da logica para exclusao de datas.                | Carlos
-------------------------------------------------------------------------------
11/08/95 | Substituicao  de  DesvTens  e ForaLeit  por  EaEfcPrev  e | Carlos
         | EaDurPrev em AreaDados e Rodape.                          |
-------------------------------------------------------------------------------
02/11/95 | Reorganizacao das bibliotecas de console e ihm			 | Carlos
-------------------------------------------------------------------------------
30/11/95 | Eliminada quebrada para o prototipo da Albras 			 | Carlos
-------------------------------------------------------------------------------
10/09/96 | Adaptacao para nova ihm                    				 | Carlos
-------------------------------------------------------------------------------
29/08/17 | TK-ALIM - Preparacão Toolkit Alimentacao                  | Carlos
-------------------------------------------------------------------------------
******************************************************************************/

	/*-- INCLUSAO DE OUTROS ARQUIVOS --*/

#include <Score.h>
#include <Prototipos.h>
#include <VarsComum.h>
#include <Relatorios.h>
#include <BdScore.h>
#include <ScoreMsgs.h>
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
	float 	IAlvo;
	float 	IReal;
    float 	PercSistema;
    float 	PercLinha;
  } t_cabec;

/*-- Area de Dados --*/
typedef
  struct VarDados
  {
	int		NumCuba;
	char	DurQueb1[7];
	char	DurQueb2[7];
	char    DurQueb3[7];
	char    DurQueb4[7];
	char    DurAlim1[7];
	char	DurAlim2[7];
	char	DurAlim3[7];
	char	DurAlim4[7];
  } t_dados;

/*-- Rodape --*/
typedef
  struct VarRodape
  {
	char	DurQueb1[7];
	char	DurQueb2[7];
	char    DurQueb3[7];
	char    DurQueb4[7];
	char    DurAlim1[7];
	char	DurAlim2[7];
	char	DurAlim3[7];
	char	DurAlim4[7];
  } t_rodape;

/*-- Temporaria --*/
typedef
  struct VarTemp
  {
    long DurQueb1;
	long DurQueb2;
	long DurQueb3;
	long DurQueb4;
	long DurAlim1;
	long DurAlim2;
	long DurAlim3;
	long DurAlim4;
  } t_temp;
