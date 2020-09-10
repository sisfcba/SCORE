/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.40

	PROJETO		: TODOS

	SISTEMA		: TODOS

	ARQUIVO		: RCubaAlimW.h

	CONTEUDO	:

	AUTOR		: Alexandre Mariz Bandeira de Morais.

	SISTEMA OPERACIONAL:  QNX 4.22A		-		COMPILADOR: WATCOM C - V9.52

	VERSAO		: 3.0		  -		  DATA  : 09/01/97

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
09/01/97 | Edicao Inicial										| A. Bandeira
-------------------------------------------------------------------------------
******************************************************************************/

	/*-- INCLUSAO DE OUTROS ARQUIVOS --*/

#include <Prototipos.h>
#include <Score.h>
#include <ScoreMsgs.h>
#include <VarsComum.h>
#include <Relatorios.h>
#include <RelPrototipos.h>
#include <OperacaoBibW.h>
#include <BdScore.h>
#include <RelGraf.h>
#include <AlimentCBA.h>

#include <string.h>
#include <malloc.h>
#include <sys/proxy.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>

/*-- DEFINICAO DE CONSTANTES --*/
#define MASC_REL_DINA		"/score/telas/MascRelAlim"
#define FREQ_TABS_PARAM		10
#define ATUAL_DINAMICA		1
#define OFFSET_LINHA		143
#define MAX_LINHAS_REL		22

/*-- Modos da chave de alimentacao --*/
#define MODO_LOCAL			"Man-Loc "
#define MODO_REMOTO			"Man-Rem "
#define MODO_AUTOMAT		"  Auto  " 


/* -- Define string para estado normal da cuba -- */
#define ESTADO_NUL         "--------"

