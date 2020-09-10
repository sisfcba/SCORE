/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DAS SALAS 125 KA I E VII

	ARQUIVO		: RelExemploDia.h

	CONTEUDO	: Prologo do programa que processa e gera as informacoes que compoem
				  exemplo de relatorio historico (dia e turno)

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 01 - 19/09/2012

	HISTORICO DAS EDICOES

-------------------------------------------------------------------------------
dd/mm/aa   | Descricao                                               | autor
-------------------------------------------------------------------------------
19/09/2012 | Edicao inicial                                          | Leonel
-------------------------------------------------------------------------------

$Id: RelExemploDia.h,v 1.1.2.1 2012/09/28 17:10:11 leo Exp $

$Log: RelExemploDia.h,v $
Revision 1.1.2.1  2012/09/28 17:10:11  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

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
	float	Placa;
	float	Alvo;
	float	Liqui;
    float   Total;
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
