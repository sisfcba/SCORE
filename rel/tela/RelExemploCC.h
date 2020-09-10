/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DAS SALAS 125 KA I E VII

	ARQUIVO		: RelExemploCC.h

	CONTEUDO	: Prologo do programa que processa e gera as informacoes que compoem
				  exemplo de relatorio de ciclo de control

	AUTOR		: Carlos Cezar Silva Lage.

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 01 - 19/09/2012

	HISTORICO DAS EDICOES

-------------------------------------------------------------------------------
dd/mm/aa   | Descricao                                               | autor
-------------------------------------------------------------------------------
19/09/2012 | Edicao inicial                                          | Leonel
-------------------------------------------------------------------------------

$Id: RelExemploCC.h,v 1.1.2.1 2012/09/28 17:10:11 leo Exp $

$Log: RelExemploCC.h,v $
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


	/*-- DEFINICAO DE CONSTANTES --*/


/*-- Definicao do numero de argumentos validos --*/
#ifdef OPERACAO_WINDOWS
  #define NUM_ARGS				2
#else
  #define NUM_ARGS				4
#endif

/*-- Definicao de estado nulo. --*/
#define ESTADO_NUL				"--------"

/*-- Definicoes de tempo nulo. --*/
#define TEMPO_NUL   			"--:--"
#define TEMPO_NUL3				"---:--"

/*-- Definicoes de turno nulo. --*/
#define TURNO_NUL				"-----"

/*-- Definicao de sinalizacao de previsao --*/
#define PREVISAO_ATIVA			"Prv"
#define PREVISAO_NUL			"---"

/*-- Definicao de sinalizacao de sopro especial --*/
#define EA_SOPRO				"EA+Sopro"


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
	float	IAlvo;
	float	ICicContlMed;
	int		NCicAtivoDia;
  } t_cabec;

/*-- Area de Dados --*/
typedef
  struct VarDados
  {
    int		NumCuba;
	char	SinEst[2];
	float	Inc;
	float	Placa;
	float	Alvo;
	float	Atual;
	float	Erro;
	char	TempoManual[6];
	char	TempUltEa[7];
	char	TempoAtraEa[6];
	char	HoraPrevEa[6];
	float	RSuaveDerivH;
	char	PassoTInc[3];
	char	Estado[9];
  } t_dados;

/*-- Rodape --*/
typedef
  struct VarRodape
  {
    float	MediaInc;
	float	MediaPlaca;
	float	MediaAlvo;
	float	MediaAtual;
	float	MediaErro;
  } t_rodape;

/* -- Estrutura para a CalcAreaDados -- */
typedef
  struct acum
  {
	int			NCubasAcum;
	float		IncAcum;
	float		PlacaAcum;
	float		AlvoAcum;
	float		AtualAcum;
	float		ErroAcum;
  } t_acum; 
