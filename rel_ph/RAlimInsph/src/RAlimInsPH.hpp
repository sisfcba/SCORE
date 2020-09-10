/* Header "RAlimInsPH.hpp" for RAlimInsph Application */
/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 5.00

	PROJETO		: TODOS

	SISTEMA		: TODOS

	ARQUIVO		: RAlimInsPH.hpp

	CONTEUDO	:

	AUTOR		: Alexandre Mariz Bandeira de Morais.

	SISTEMA OPERACIONAL:  QNX 4.25D		-		COMPILADOR: WATCOM C++ - V10.6

	VERSAO		: 1.0		  -		  DATA  : 23/04/02

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
23/04/02 | Edicao Inicial										| A. Bandeira
-------------------------------------------------------------------------------
******************************************************************************/

#ifndef		_RAlimInsPH
	#define		_RAlimInsPH

#include <string.h>
#include <malloc.h>
#include <sys/proxy.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <signal.h>
#include <stdlib.h>

#include	<OperacaoPH.hpp>
#include	<ScoreLibph.hpp>

#if defined(__cplusplus)
extern "C" {
#endif

#include <Prototipos.h>
#include <Score.h>
#include <ScoreMsgs.h>
#include <ScoreErros.h>
#include <VarsComum.h>
#include <BdScore.h>
#include <AlimentCBA.h>

/*-- DEFINICAO DE CONSTANTES --*/
#define FREQ_TABS_PARAM		10
#define	MAX_LIN_REL_ALIM	13

/* -- Define string para estado normal da cuba -- */
#define ESTADO_NUL         	"--------"

typedef struct widgets {
	PtWidget_t *grupo[PH_MAX_GRUPOS_CUBAS];
	PtWidget_t *linha[MAX_LIN_REL_ALIM];
	struct	{
		char		linha[80];
		PgColor_t	cor;
	}rel[PH_MAX_CUBAS_GRUPO];
}t_widgets;

#if defined(__cplusplus)
};
#endif


#endif

