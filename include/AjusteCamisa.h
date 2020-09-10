/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.1

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: AjusteCamisa.h

	CONTEUDO	: Prologo do algoritmo de ajuste de camisa.
                  Contem as constantes e prototipos de funcoes do algoritmo
				  de ajuste de camisa da CBA

	AUTOR		: Carlos Cezar Silva Lage

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	28/07/98

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
Data     | Descricao                                            | Autor 
-------------------------------------------------------------------------------
******************************************************************************/
/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<time.h>
#include	<sys/kernel.h>
#include	<Score.h>
#include	<ScoreMsgs.h>
#include	<Eventos.h>
#include	<Prototipos.h>

/*
-------------------------------------------------------------------------------
                           Definicoes
-------------------------------------------------------------------------------
*/

/*-- Definicoes de cancelamento do ajuste camisa -- */
#define AJUSTE_NORMAL				0
#define ABORTA_CAMISA_MANUAL		1
#define ABORTA_TROCA_PINOS			2
#define ABORTA_QUEBRADA				3
#define ABORTA_PREVISAO				4
#define ABORTA_EFEITO_ANODICO		5
#define ABORTA_FALHA_MOV			6
#define ABORTA_DESVIO_TENSAO		7
#define ABORTA_EXCESSO_TEMPO		8
#define ABORTA_INTERV_CORRIDA		9
#define ABORTA_DESAB_CAMISA			10
#define ABORTA_DESAB_OPERADOR		11
#define ABORTA_BARRA_QUEBRADA		12
#define ABORTA_FORA_CONTROLE		13
#define ABORTA_FORA_LEITURA			14
#define ABORTA_LINHA_DESAB			15
#define ABORTA_MANOBRA_CRUZEIRO		16

/*
-------------------------------------------------------------------------------
                           Tipos de dados
-------------------------------------------------------------------------------
*/


/*
-------------------------------------------------------------------------------
                           Prototipos
-------------------------------------------------------------------------------
*/

void  IniAjCamCuba(int Cuba);
void  AtivaAjusteCamisa(int Cuba, time_t HoraAtual);
void  VerifCondCamisa(int Cuba, time_t HoraAtual);
void  FimAjCamisa(int Cuba, int Motivo);
void  CalcMovCamisa(int Cuba, float Duracao, time_t HoraAtual);
void  VerifFimCamisa(int Cuba);
void  TrataSubidaCamisa(int Cuba, time_t HoraAtual);

/*-- AjusteCamisa.h --*/
