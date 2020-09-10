/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: GERAL

	SISTEMA		: GERAL

	ARQUIVO		: ScoreStr.h

	CONTEUDO	: Tipos e definicoes para acesso da base de dados de
				  strings do Score.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0		  -		  DATA  : 06/12/96

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
06/12/96 | Edicao inicial                              			| Leonel
-------------------------------------------------------------------------------
******************************************************************************/

#ifndef		_SCORESTR_H

#define		_SCORESTR_H

#include <Definicao.h>

/* -- Nome do arquivo da base de dados -- */
#define		ARQUIVO_STRMSG		"/score/base_dados/MsgStr"

/* -- Nome do segmento de memoria compartilhada -- */
#define		NOME_SHM_STRMSG		"Atan/Score/MsgStr"

/* -- Definicoes gerais do modulo -- */
#define		TAM_MAX_MSG_SCORE		81	/* Tamanho maximo incluindo NUL */
#define		MAX_MSG_SCORE		5000	/* Numero maximo de mensagens da tabela */

/* -- tipos de dados -- */
typedef struct msg_score
{
  byte		MaxStr;		/* -- Tamanho maximo do string (para traducao) -- */
  char		StrMsg[TAM_MAX_MSG_SCORE];	/* -- string -- */
} t_msgstr;

typedef struct tab_msg_score
{
  t_msgstr	Msg[MAX_MSG_SCORE];
} t_tab_strmsg;

/* -- Prototipos -- */
char			*ScoreGetStr(int CodStr);
char			*ScoreGetNStr(int CodStr,int TamMax);
int				ScoreGetStrTam(int CodStr, int *TamAtual);
t_tab_strmsg	*PegaScoreStr(void);
int				CriaBdStr(void);
int				InitBdStr(void);

#endif

/* -- Fim do arquivo ScoreStr.h -- */
