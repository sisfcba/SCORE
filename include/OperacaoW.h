/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: OperacaoW.h

	CONTEUDO	: Definicoes para a interface de operacao windows

	AUTOR		: Alexandre Mariz Bandeira de Morais

	VERSAO		: 01 - 20/09/94

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
02/02/95 | Adaptacao para versao em ingles                      | Carlos
-------------------------------------------------------------------------------
******************************************************************************/

#ifndef		OPERACAOW_H_INCLUIDO
#define		OPERACAOW_H_INCLUIDO

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

#include <windows/Qwindows.h>
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

#endif /* OPERACAOW_H_INCLUIDO */
