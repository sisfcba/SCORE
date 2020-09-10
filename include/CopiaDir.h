/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 3.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: CopiaDir.h

	CONTEUDO	: Prologo com as definicoes necessarias para a utilizacao das 
				  funcoes CopiaDir, CopiaArq, ApagaArq e Open da biblioteca do
                  Score.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 2.15		-		COMPILADOR: C86

	VERSAO		: 1.0			-		DATA	:	16/10/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
23/11/93 | Criada opcao DIF_ARQUIVO_LOG para copiar diferenca e | Leonel
         | cabecalho dos arquivos de log.                       |
-------------------------------------------------------------------------------
******************************************************************************/

#ifndef		_COPIADIR_H

#define		_COPIADIR_H

/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include	<Definicao.h>

/*
-------------------------------------------------------------------------------
                           Defines
-------------------------------------------------------------------------------
*/
#define		TODO_ARQUIVO		1
#define		DIF_ARQUIVO			2
#define		DIF_ARQUIVO_LOG		3

/*
-------------------------------------------------------------------------------
                           Prototipos
-------------------------------------------------------------------------------
*/
int		CopiaDir(char *DirFonte, char *DirDestino, int TipoCopia, int Verbose);
int		CopiaArq(char *ArqFonte, char *ArqDestino, int TipoCopia);
int		Open(char *Arquivo, int Acesso, int Permissao);
int		ApagaArq(char *Arquivo);

#endif

/* -- fim do arquivo CopiaDir.h -- */

