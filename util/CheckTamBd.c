/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.

	PROJETO		: SCORE

	SISTEMA		: Todos

	ARQUIVO		: CheckTamBd.c

	CONTEUDO	: Verifica limites dos tamanho dos tipos de dados globais
				  do Score com os defines de maximos.

	AUTOR		: Leonel Vicente Mota Ivo

	VERSAO		: 1.0			-		DATA	:	26/08/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
$Id: CheckTamBd.c,v 1.3 2005/04/27 13:16:59 leo Exp $

$Log: CheckTamBd.c,v $
Revision 1.3  2005/04/27 13:16:59  leo
Incluida funcao ImprimeTamanhos para permitir compilacao no cliente.

Revision 1.2  2003/09/25 19:25:17  leo
Retirada da funcao ImprimeTamanhos e sua inclusao na lib_score.

******************************************************************************/

/*
-------------------------------------------------------------------------------
                           Definicao de compilacao condicional
-------------------------------------------------------------------------------
*/
#define		PROGRAMA_PRINCIPAL

/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include	<stdio.h>
#include	<Score.h>
#include	<Eventos.h>
#include	<RelGraf.h>

/*
-------------------------------------------------------------------------------
                           Variaveis Globais
-------------------------------------------------------------------------------
*/
/* -- Define apontadores para as tabelas comuns -- */
#include	<VarsComum.h>

/*
-------------------------------------------------------------------------------
                           Prototipos
-------------------------------------------------------------------------------
*/
#include	<Prototipos.h>

// Incluida funcao para permitir compilacao nos clientes
#include	"../lib_score/ImprimeTamanhos.c"

/*
-------------------------------------------------------------------------------
                           Main
-------------------------------------------------------------------------------
*/
void main(void)
{
  if (ImprimeTamanhos(FALSO) eq VERDADEIRO)
	printf("\n\n\007\033<ERRO DE TAMANHO NA BASE DE DADOS!\033>\n");
  else
	printf("\nTamanho da base de dados OK!\n");
}
