
/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: ImprimeRel.h

	CONTEUDO	: Contem constantes, variaveis  e includes

	AUTOR		: Alexandre Mariz Bandeira de Morais.

	VERSAO		: 00 - 30/10/92

	OBSERVACAO	:

	HISTORICO DAS EDICOES

-------------------------------------------------------------------------------
24/09/02 | Eliminada pag. em branco na impressao do relatorio	| Carlos
-------------------------------------------------------------------------------
******************************************************************************/

	/*-- INCLUSAO DE OUTROS ARQUIVOS --*/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/qioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#ifdef	VERSAO_PHOTON
 #include	<Ph.h>
 #include	<Pt.h>
 #include	<Ap.h>
 #include	<ScoreLibph.hpp>
#endif

#include <KeysCBA.h>
#include <RelPrototipos.h>
#include <Relatorios.h>
#include <Score.h>
#include <Operacao.h>
#include <VarsComum.h>
#include <Prototipos.h>

#ifdef	VERSAO_WINDOWS
 #include <windows/Qwindows.h>
#endif

#define  MAX_LINHAS_PAG  55 // Cabecalho + AreaDados + Rodape
//#define  MAX_LINHAS_PAG  52
#define  TIPO_CONSOLE    1
#define  TIPO_SEAL       2
#define  TIT_REL_IMPR    "ATAN SISTEMAS DE AUTOMACAO - SCORE"
