/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 3.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: VarsTrataEa.h

	CONTEUDO	: Prologo do Modelo de Calculos Primarios - MCP
                  Contem as definicoes das variaveis globais do modulo TrataEa

	AUTOR		: Joao Thomaz Pereira


	VERSAO		: 1.0			-		DATA	:	23/09/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
dd/mm/aa | descricao                                            | autor 
-------------------------------------------------------------------------------
******************************************************************************/
/*
-------------------------------------------------------------------------------
                           Inclusoes
-------------------------------------------------------------------------------
*/
#include	<time.h>

/*
-------------------------------------------------------------------------------
                           Variaveis globais
-------------------------------------------------------------------------------
*/
#define		TRATA_DELAY_INICIO_EA		1

/* -- Numero de Cubas definido na base de dados (copia local) -- */
DECL int	NumCubas;
/* -- Contem a hora atual em secundos -- */
DECL long	HoraAtualSec;
/* -- Ponteiro para a hora ja' dividida do ciclo de controle atual -- */
DECL struct	tm	*PHoraAtual;

/* -- Delay programavel para inicio EA em ticks de leitura qdo em troca de
      anodo/pinos e qdo. nao esta em troca de anodo/pinos -- */
DECL short int ContEaTAnodo[MAX_CUBAS];
DECL short int ContEaNormal[MAX_CUBAS];
