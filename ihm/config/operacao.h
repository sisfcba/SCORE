
/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: operacao.h

	CONTEUDO	: Definicoes para a interface de operacao

	AUTOR		: Hevelton Araujo Junior

	VERSAO		: 00 - 26/05/92

	HISTORICO DAS EDICOES

******************************************************************************/

#ifndef		OPERACAO_H_INCLUIDO
#define		OPERACAO_H_INCLUIDO

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
//#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <process.h>
//#include <taskmsgs.h>
#include <ctype.h>
#include "definicao.h"
//#include "/source.ci/windows.h"
//#include "/source.ci/keys.h"
#include "../../source_tkt/windows.h"
#include "../../source_tkt/keys.h"

	/***************************/
	/* DEFINICAO DE CONSTANTES */
	/***************************/

/* Verifica modelo de memoria para saber numero de bytes por ponteiro */
#ifdef	_FLAGS_As
	#define	TAM_CODE_PTR			2		/* Ponteiro para codigo */
#else
	#define	TAM_CODE_PTR			4		/* Ponteiro para codigo */
#endif

#ifdef	_FLAGS_An
	#define	TAM_DATA_PTR			2		/* Ponteiro para dados */
#else
	#define	TAM_DATA_PTR			4		/* Ponteiro para dados */
#endif

/* Nome do arquivo de descricao das opcoes */
#define	NOME_ARQ_DESC_OPCAO			"opcoes."

/* Nome do arquivo de descricao dos menus */
#define	NOME_ARQ_DESC_MENU			"menus."

/* Tipos para o proximo procedimento */
#define	MENU						1
#define	TAREFA						2
#define	FINALIZAR					3

/* Tipos de entidades para entrada */
#define	MENUS						0
#define	OPCOES						1

/* Tipos de operacoes possiveis com menus */
#define	EDITAR						0
#define	EXIBIR						1

/* Define as cores das janelas de trabalho */
#define	COR_JAN_DESC				( BLUE_B orb WHITE )
#define	COR_JAN_UTIL				( CYAN_B orb BLACK )
#define	COR_JAN_ALARME				( BLUE_B orb WHITE )
#define	COR_PED_ARGS				( WHITE_B orb BLACK )

/* Constante zero */
#define	NULO						0

/* Numero maximo de menus */
#define	MAX_MENUS					20

/* Numero maximo de opcoes */
#define MAX_OPCOES					20

/* Define a cor preta, ja que o "toolkit" a assume como default */
#define	BLACK						0
#define	BLACK_B						0

/* Tamanho maximo para os argumentos de uma funcao/programa */
#define	TAM_ARGS					30
#define	MAX_ARGS					20

/* Tamanho maximo do prompt para os argumentos */
#define	TAM_PROMPT					30

/* Tamanho do nome para tarefa */
#define	TAM_NOME					40

/* Tamanho maximo das opcoes */
#define	TAM_OPCOES					40

/* Tmanho do titulo do menu */
#define	TAM_TIT						45

/* Numero de bytes de reserva por registro */
#define	TAM_RESERVA					200

/* Tamanho da estrutura de descricao de um menu */
#define	TAM_DESC_MENU				(sizeof (struct s_desc_menu))

/* Tamanho da estrutura de descricao de uma opcao */
#define	TAM_DESC_OPCAO				(sizeof (struct s_desc_opcoes))

/* Define numero do menu principal */
#define	MENU_PRINCIPAL				0

/* Indica que ESCAPE foi pressionada */
#define	QUER_SAIR					(-1)

/* Define retorno de erro */
#define	MEM_INSF					(-2)

	/***********************/
	/* DECLARACAO DE TIPOS */
	/***********************/

/* Estrutura de um registro no arquivo de descricao dos menus */
typedef
	struct s_desc_menu
	{
		unsigned	inicializado;	/* Indica se regiatro inicializado */
		unsigned	linha;			/* Linha inicial (superior) */
		unsigned	coluna;			/* Coluna Inicial (esquerda) */
		unsigned	num_opcoes; 	/* Numero de opcoes (= numero de linhas) */
		unsigned	num_colunas;	/* Numero de colunas (calculado) */
		unsigned	atributo;		/* Atributo de cor do menu */
		unsigned	moldura;		/* Tipo de moldura */
		unsigned	direcao;		/* Direcao do menu (horiz. ou vert.) */
		unsigned	num_linhas;		/* Numero de linhas entre opcoes */
		char		titulo[TAM_TIT];/* Titulo do menu */
		struct
		{
			char	textos_opcoes[TAM_OPCOES];
		} textos[MAX_OPCOES];
	} t_menus;

/* Estrutura de um registro no arquivo de descricao das opcoes */
typedef
	struct s_desc_opcoes
	{
		unsigned	inicializado;					/* Indica se registro inicializado */
		int			tipo_proximo;					/* Proximo procedimento */
		int			nivel_senha;					/* Nivel de acesso */
		union
		{
			struct
			{
				char nome[TAM_NOME];				/* Nome do programa */
				int	 prioridade;					/* Prioridade do programa */
				int	 num_tty;						/* TTY do programa */
				int	 num_nodo;						/* Nodo do programa */
				word flags;							/* Flags de ciracao */
				int	 num_args;
				struct
				{
					char prompt[TAM_PROMPT];		/* Prompt do argumento */
					word tamanho;					/* Tamanho do argumento */
					char valor[TAM_ARGS];			/* Conteudo do argumento */
				} argumentos[MAX_ARGS];
			} tarefa;

			struct
			{
				int  num_menu;						/* Numero do menu */
			} menu;
		} proximo;
	} t_opcoes;

	/***********************************/
	/* DECLARACAO DE VARIAVEIS GLOBAIS */
	/***********************************/

DECL struct	Window *j_desc;				/* 2 primeiras linhas */
DECL struct Window *j_util;				/* janela util de trabalho */
DECL struct Window *j_alarme;			/* 2 ultimas linhas */
DECL char nome_arq_menu[40];
DECL char nome_arq_opcao[40];

	/****************************/
	/* PROTOTIPACAO DAS FUNCOES */
	/****************************/

int pede_argumentos ( long num_menu , long num_opcao , t_opcoes *dados );

#endif /* OPERACAO_H_INCLUIDO */
