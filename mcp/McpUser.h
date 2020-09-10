/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.1

	PROJETO		: ALBRAS - ALUMINIO BRASILEIRO SA

	SISTEMA		: PROTOTIPO PARA UMA SECAO DA REDUCAO II

	ARQUIVO		: McpUser.h

	CONTEUDO	: Prologo do Modulo McpUser.
                  Contem as constantes e tipos de dados do modulo.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	09/12/93

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
Data     | Descricao                                            | Autor 
-------------------------------------------------------------------------------
07/11/95 | Alteracoes nos exemplos para o prototipo da Albras   | Leonel
-------------------------------------------------------------------------------
******************************************************************************/
/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/

#include	<Score.h>
#include	<Eventos.h>
#include	<Prototipos.h>
#include	<string.h>
#include	<stdlib.h>
#include	<sys/kernel.h>
#include	<time.h>

/*
-------------------------------------------------------------------------------
                           Variaveis Locais
-------------------------------------------------------------------------------
*/
/* -- Contem a hora atual em secundos -- */
DECL	long	HoraAtualSec;
/* -- Faixa de cubas a tratar -- */
DECL	int			CubaIni,CubaFim;


/*
-------------------------------------------------------------------------------
                           Defines
-------------------------------------------------------------------------------
*/

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
void IniMcpUser(void);
void ProcessaCubas(void);
t_boolean ConsisteArgs(int Argc,char *Argv[]);

/* -- Fim do arquivo McpUser.h -- */

