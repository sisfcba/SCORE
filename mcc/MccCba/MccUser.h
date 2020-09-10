/******************************************************************************

			 ACCENTURE - APAS - ACCENTURE PLANT AND AUTOMATION SOLUTIONS
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 5.0

	PROJETO		: SCORE

	SISTEMA		: CBA

	ARQUIVO		: MccUser.h

	CONTEUDO	: Prologo do Modulo MccUser.
                  Contem as constantes e tipos de dados do modulo.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 1.0			-		DATA	:	29/11/93

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
Data     | Descricao                                            | Autor 
-------------------------------------------------------------------------------
02/10/12 | Kit de desenvolvimento para a CBA                    | Leonel
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
#include	<time.h>
#include	<sys/kernel.h>

/*
-------------------------------------------------------------------------------
                           Variaveis Locais
-------------------------------------------------------------------------------
*/
DECL	time_t		HoraAtualCtrl;
DECL	struct tm	HoraAtual;
DECL	int			CubaIni,CubaFim;
DECL	int			IntervCicCont;

/*
-------------------------------------------------------------------------------
                           Definicoes
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
void		IniMccUser(void);
void		ProcessaCubas(void);
void		MovimentaAnodo(int Cuba, int Sentido, float Duracao);
t_boolean	ConsisteArgs(int Argc,char *Argv[]);

/* -- Fim do arquivo MccUser.h -- */
