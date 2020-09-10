/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO  : TODOS

	SISTEMA  : GERAL

	ARQUIVO  : WatchMsg.h

	CONTEUDO : Contem as definicoes de para comunicacao com o modulo
			   Watchdog para desativar o sistema.

	AUTOR    : Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO   : 1.0		  -	  DATA  : 08/10/96

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
08/10/96 | Edicao inicial                            			| Leonel
-------------------------------------------------------------------------------
******************************************************************************/

#ifndef		_WATCH_MSG_H

#define		_WATCH_MSG_H

/*
-------------------------------------------------------------------------------
							Constantes
-------------------------------------------------------------------------------
*/
/* Arquivo com os textos de diagnostico */
#define		ARQUIVO_WATCH_DIAG		"/score/config/Watchdog.diag"

/* Codigos de informar o motivo da desativacao. Estao associados ao texto
   no arquivo /score/config/Watchdog.diag. */
#define		WATCH_OPERADOR			0	/* Solicitacao do operador */
#define		WATCH_MORTE_TRESID		1	/* Morte de tarefa residente */
#define		WATCH_TIMEOUT			2	/* Timeout na espera de ativacao */
#define		WATCH_ERRO_INT			3	/* Erro interno watchdog */
#define		WATCH_ERRO_CORRENTE		4	/* Erro leitura de corrente */
#define		WATCH_ERRO_SLTA			5	/* Erro inicializacao do Slta */
#define		WATCH_ERRO_CTI			6	/* Erro inicializacao do canal cti */
#define		WATCH_ERRO_CLP			7	/* Erro comunicacao com clp */
#define		WATCH_ERRO_INI_CLP		8	/* Erro inicializacao do canal do clp */

/*
-------------------------------------------------------------------------------
						   Tipos de dados
-------------------------------------------------------------------------------
*/
/* -- Padrao de mensagem utilizado pela funcao FimScore -- */
typedef
  struct FimScore
  {
	int	Origem;
	int	Acao;
	int	Parametro[8];	/* O codigo para informar o motivo da desativacao e' o
						   parametro 0 */
	char Par1[80];		/* Parametros opcionais. Contem NUL qdo. nao usados */
	char Par2[80];
	char Par3[80];
  } t_mens_fimscore;

#endif

/* -- fim WatchMsg.h -- */
