/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: ComumIHM.h

	CONTEUDO	: Definicoes para as funcoes da biblioteca ComumIHM

	AUTOR		: Alexandre Mariz Bandeira de Morais

	VERSAO		: 01 - 20/09/94

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
02/02/95 | Adaptacao para versao em ingles                      | Carlos
-------------------------------------------------------------------------------
******************************************************************************/

#ifndef		COMUM_IHM_H_INCLUIDO
#define		COMUM_IHM_H_INCLUIDO

	/***********************************************/
	/* INDICA SE ESTA OU NAO NO PROGRAMA PRINCIPAL */
	/***********************************************/

#ifdef PROGRAMA_PRINCIPAL
	#define	DECL
#else
	#define	DECL			extern
#endif

	/************************/
	/* INCLUSAO DE ARQUIVOS */
	/************************/

#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <process.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/proxy.h>
#include <malloc.h>
#include <sys/name.h>
#include <Score.h>
#include <VarsComum.h>
#include <ScoreMsgs.h>
#include <ScoreErros.h>
#include <Relatorios.h>
#include <Prototipos.h>

#define	LINHA_LISTA			121
#define	LINHA_LISTA_INI		99
#define	COLUNA_LISTA_INI	550

/* funcoes do Comum IHM.c */
t_boolean ConsCubas( char *DataIni, char *DataFim, char *CubaEx,
	                char *CubaSel, char *DiaEx, unsigned flag,
	                t_filtrosPD *filtro,unsigned AlgCtr, t_GrupoCuba  *GrupoCuba);
t_boolean ConsCubas2( char *DataIni, char *DataFim, char *CubaEx,
	                char *CubaSel, char *DiaEx, unsigned flag,
	                t_filtrosPD *filtro,unsigned AlgCtr, t_grupo_cuba  *GrupoCuba);


int ChecaExclusao( int cuba, int *cubaexc, int cont, unsigned alg );
time_t PegaData( char *Data, int *Dia, int *Mes, int *Ano );
t_boolean ValExCubas( char *PtStr );
int ValExcDatas(char *Linha);
time_t ValDiaMes(char *PData);
char *data_ant_pos( char *data, int tipo );
int critica_data( int dia, int mes, int ano );
int divide_linha( char *texto, char *linha1, char *linha2, int num_itens );
char *AchaNomeTurno(char *IndTurno);
char *AchaIndTurno(char *NomeTurno);
char *TiraBrancos( char *str );
void CriaTimer(timer_t id);
void DeletaTimer(timer_t  id);
t_boolean LeFiltro( char *nome, t_h_filtrosPD *header,
					t_filtrosPD *filtro, int registro );
t_boolean GravaFiltro( char *nome, t_h_filtrosPD *header,
					   t_filtrosPD *filtro, int registro );

t_boolean GravaTagIhm( char *nome, t_ihm_config *ihm, int num_tag );
t_boolean LeIhm( char *nome, t_ihm_config *ihm );

/* funcoes do misc.c */
unsigned tirabits( unsigned pal, unsigned biti, unsigned bitf );
void insbits( unsigned *pal, unsigned biti, unsigned bitf, unsigned valor );
byte checanum( char *p );
char *trim( char *str );
char *PoeNull( char *str, int tam );



#endif /* COMUM_IHM_H_INCLUIDO */
