 /******************************************************************************

             ACCENTURE - ACPS - ACCENTURE PLANT & COMMERCIAL SERVICES
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 5

    CLIENTE     : CBA - Companhia Brasileira de Aluminio SA

	PROJETO		: GENERICO

	SISTEMA		: GENERICO

	ARQUIVO		: RFComunica.c 

	CONTEUDO	: Tarefa que opera o terminal da radio base via TCPIP

	AUTOR		: Alexandre Mariz Bandeira de Morais

	SISTEMA OPERACIONAL:  QNX 4.25B		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 1.0		  -		  DATA  : 31/07/01

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
31/07/01 | Edicao Inicial                                		| Bandeira
-------------------------------------------------------------------------------
$Id: RFComunica.c,v 1.1.1.1.10.1 2014/10/27 15:23:53 leo Exp $

$Log: RFComunica.c,v $
Revision 1.1.1.1.10.1  2014/10/27 15:23:53  leo
Preparacao para criar kit de desenvolvimento do radio. Retiradas referencias
a prologo antigo da Alcan.

******************************************************************************/

#define PROGRAMA_PRINCIPAL

#include <RFCBA.h>

//**************************************************************
//
// Main - RFComunica
//
//**************************************************************
void main( int argc, char *argv[] )
{
  ExecutaMain();
}
