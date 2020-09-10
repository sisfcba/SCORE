/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 3.0

	PROJETO  : CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA  : AUTOMACAO DA SALA 120 KA I

	ARQUIVO  : Comandos.h

	CONTEUDO : Contem as definicoes gerais usadas pelos modulos responsaveis
               pela execucao dos comandos de operacao.

	AUTOR    : Junia Guerra

	VERSAO   : 1.0						- DATA  : 21/10/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
dd/mm/aa | descricao                                            | autor 
-------------------------------------------------------------------------------
03/02/95 | Adaptacao para versao em ingles                      | Carlos
-------------------------------------------------------------------------------
******************************************************************************/

/*
-------------------------------------------------------------------------------
				Constantes
-------------------------------------------------------------------------------
*/

/*-- Chave que indica que foi pedido help --*/

#define CHAVE_AJUDA		"-h"		/*-- Parametro para pedido de ajuda --*/

/*-- Parametro nulo na geracao de eventos --*/
#define STR_NULL		"--------"

/*-- Definicao das acoes executadas pelo operador. --*/
#define ATIVAR			1
#define DESATIVAR		2

/*-- Definicao de constantes de varredura das cubas. --*/
#define	PRI_CUBA_OPER		101
#define	OFFSET_CUBAS		100


		/*-- Prototipos das funcoes comuns ao modulo de operacao --*/

int ConsCubasRem(int CubaInicial, int CubaFinal, char *PMsg);
time_t CriticaData(char *Data);
time_t CriticaHora(char *Hora);
