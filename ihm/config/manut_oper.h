/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: manut_oper.h

	CONTEUDO	: Definicao para manutencao da base de dados de operacao

	AUTOR		: Hevelton Araujo Junior

	VERSAO		: 00 - 29/05/92

	HISTORICO DAS EDICOES

******************************************************************************/

#ifndef	MANUTOPER_H_INCLUIDO
#define	MANUTOPER_H_INCLUIDO

	/***********************************************************/
	/* ESTE E O PROGRAMA PRINCIPAL, PORTANTO DEFINE-O COMO TAL */
	/***********************************************************/

#define	PROGRAMA_PRINCIPAL

	/************************/
	/* INCLUSAO DE ARQUIVOS */
	/************************/

#include "operacao.h"
#include "bib_operacao.h"

/* Define o menu de entrada do programa */

struct Menu m_prin[] =
	{
		"MENUS", NULL,
		"OPCOES", NULL,
		NULL, NULL
	};

#define	COR_MPRIN			( BLUE_B orb WHITE )		/* atributo de cor */
#define	COL_MPRIN			30							/* coluna */
#define	LIN_MPRIN			6							/* linha */
#define	TIT_MPRIN			NULL						/* titulo */

/* Define o menu de escolha edicao/exibicao */

struct Menu m_exib[] =
	{
		"EDITAR MENU", NULL,
		"EXIBIR MENU", NULL,
		NULL, NULL
	};

#define	COR_EXIB			( BLUE_B orb WHITE )		/* atributo de cor */
#define	COL_EXIB			30							/* coluna */
#define	LIN_EXIB			6							/* linha */
#define	TIT_EXIB			NULL						/* titulo */

/* Define o menu de atributos */

struct Menu m_atr[] =
	{
		"PRETO", NULL,
		"AZUL", NULL,
		"VERDE", NULL,
		"CYAN", NULL,
		"VERMELHO", NULL,
		"MAGENTA", NULL,
		"MARROM", NULL,
		"BRANCO", NULL,
		NULL, NULL
	};

/* Define o menu de molduras */

struct Menu m_mol[] =
	{
		"SIMPLES", NULL,
		"DUPLA", NULL,
		"GROSSA", NULL,
		"SEM", NULL,
		NULL, NULL
	};

/* Define o menu de direcao */

struct Menu m_dir[] =
	{
		"VERTICAL", NULL,
		"HORIZONTAL", NULL,
		NULL, NULL
	};

/* Define o menu de sim ou nao */

struct Menu m_sim[] =
	{
		"SIM", NULL,
		"NAO", NULL,
		NULL, NULL
	};

/* Cor da jenela de escolha e do cursor no menu */
#define	COR_MENU_ESC		( BLUE_B orb WHITE )
#define	CURSOR_MENU_ESC		( COR_MENU_ESC orb REVERSE )

/* Prompt para pedir numero do menu */
#define	P_NUM_MENU			" NUMERO DO MENU:"

/* Define janela para pedir numero do menu */
#define	NUM_MENU_X			30							/* coluna */
#define	NUM_MENU_Y			0							/* linha */
#define	COR_NUM_MENU		( BLUE_B orb CYAN )			/* atributo de cor */

/* Define janela para entrada de argumentos */
#define	ARGS_X				0
#define	ARGS_Y				11
#define	COR_JAN_ARGS		( BLUE_B orb WHITE )

/* Cor/posicao/prompt para pedir prompt do argumento */
#define	P_PARGS				"PROMPT:"
#define	COR_PPARGS			( BLUE_B orb WHITE )
#define	PPARGS_X			1

/* Cor/posicao/prompt para pedir tamanho do argumento */
#define	P_TAMARGS			"TAM:"
#define	COR_PTAMARGS		( BLUE_B orb WHITE )
#define	PTAMARGS_X			( strlen (P_PARGS) + TAM_PROMPT + 3 )

/* Cor/posicao/prompt para pedir valor default do argumento */
#define	P_DEFAULT			"DEFAULT:"
#define	COR_PDEFAULT		( BLUE_B orb WHITE )
#define	PDEFAULT_X			( strlen (P_PARGS) + TAM_PROMPT + 3 + strlen (P_TAMARGS) + 2 + 3 )

/* Posicao do prompt, tamanho e default do argumento */
#define	PARGS_X				( PPARGS_X + (strlen (P_PARGS) + 1) )
#define	TAMARGS_X			( PTAMARGS_X + (strlen (P_TAMARGS) + 1) )
#define	DEFAULT_X			( PDEFAULT_X + (strlen (P_DEFAULT) + 1) )

/* Numero maximo de argumentos por pagina */
#define	MAX_ARGS_PAG		10

/* Define dados para ler proximo procedimento */
#define	PROX_X				( (80 - strlen (P_PROX)) / 2 )
#define	PROX_Y				1
#define	COR_PROX			( CYAN_B orb BLUE )
#define	P_PROX				"TIPO DO PROXIMO PROCEDIMENTO:"

/* Define qual e a ultima linha da janela util */
#define	ULT_LIN_UTIL		22

/* Define texto da linha de ajuda para tela de entrada dos menus */
#define	LINHA_AJUDA_MENU	"Esc-Sair  Setas-Move Cursor  F1-Edita Opcoes  F2-Gravar"

/* Define texto da linha de ajuda para tela de entrada de opcoes */
#define	LINHA_AJUDA_OPCAO	"Esc-Sair  Setas/TAB-Move Cursor  F2-Gravar"

/* Define numero maximo de opcoes em cada pagina */
#define	MAX_OPT_PAG			8

/* Linha para titulo das opcoes */
#define	LIN_OPCOES			10

/* Define cor de entrada de dados */
#define	COR_ENTRADA			( CYAN_B orb BLUE )

/* Define cor para entrada de opcoes */
#define	COR_ENT_OPCOES		( CYAN_B orb BLUE )

/* Define cor para entrada de argumentos */
#define	COR_ENT_ARGS		( BLUE_B orb CYAN )

/* Define cor do titulo das opcoes */
#define	COR_OPCOES			( CYAN_B orb BLACK )

	/****************************/
	/* PROTOTIPACAO DAS FUNCOES */
	/****************************/

/* Funcoes globais */
void main ( int argc , char *argv[] );
long pede_numero_menu ( void );

/* Funcoes para entrada de dados de menus */
void edita_dados_menu ( long num_menu );
void escreve_opcoes_menu ( struct s_desc_menu *dados );
int edita_opcoes_menu ( struct s_desc_menu *dados );
int recupera_form_menu ( struct s_desc_menu *dados );
void ini_form_menu ( struct s_desc_menu *dados );
int m_atrib ( struct Window *janela , char *valor , int x , int y );
int m_moldur ( struct Window *janela , char *valor , int x , int y );
int m_direc ( struct Window *janela , char *valor , int x , int y );
int m_si_no ( struct Window *janela , char *valor , int x , int y );

/* Funcoes para entrada de dados de opcoes */
void edita_dados_opcao ( long num_menu , long num_opcao );
int escolhe_tipo ( struct Window *janela , char *valor , int x , int y );
void le_tipo_proximo ( struct s_desc_opcoes *dados );
int edita_args_tarefa ( struct s_desc_opcoes *dados );
void ini_form_tarefa ( struct s_desc_opcoes *dados ); 
void recupera_form_tarefa ( struct s_desc_opcoes *dados ); 

	/*********************/
	/* VARIAVEIS GLOBAIS */
	/*********************/

/* Buffer contendo codigos de atributo para o menu de atributos */
/* IMPORTANTE: Tem que estar na mesma ordem do menu de atributos */

word attr_f[] = { 0x0000, 0x8140, 0x8240, 0x8340, 0x8440, 0x8540, 0x8640, 0x8740 };
word attr_b[] = { 0x0000, 0x9040, 0xa040, 0xb040, 0xc040, 0xd040, 0xe040, 0xf040 };

	/***********************/
	/* DECLARACAO DE FORMS */
	/***********************/

/* Define o "form" para entrada de dados do menu */
char bmenu[100];
struct Form form_menu[] =
{
	"Linha Inicial...............:",
			1, 1, 2, COR_ENTRADA, bmenu,      NULL,     NULL, NULL, "99", NULL,
	"Coluna Inicial..............:",
			1, 2, 2, COR_ENTRADA, &bmenu[ 3], NULL,     NULL, NULL, "99", NULL,
	"Atributo de Frente..........:",
			1, 3, 8, COR_ENTRADA, &bmenu[ 6], m_atrib,  NULL, NULL, "99", NULL,
	"Atributo de fundo...........:",
			1, 4, 8, COR_ENTRADA, &bmenu[15], m_atrib,  NULL, NULL, "99", NULL,
	"Tipo de Moldura.............:",
			1, 5, 7, COR_ENTRADA, &bmenu[24], m_moldur, NULL, NULL, "99", NULL,
	"Direcao do Menu.............:",
			1, 6,10, COR_ENTRADA, &bmenu[32], m_direc,  NULL, NULL, "99", NULL,
	"Linhas entre opcoes.........:",
			1, 7, 2, COR_ENTRADA, &bmenu[46], NULL,     NULL, NULL, "99", NULL,
	"Numero de Opcoes............:",
			1, 8, 2, COR_ENTRADA, &bmenu[50], NULL,     NULL, NULL, "99", NULL,
	"Titulo do Menu..............:",
			1, 9,TAM_TIT-1, COR_ENTRADA, &bmenu[53], NULL,     NULL, NULL, NULL, NULL,
//	NULL,NUL,NUL,NUL,NUL,NULL,NULL,NULL,NULL,NULL,NULL
	NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
};


/* Form para entrada de dados de tarefa */
char	bopcao[65];
struct	Form	form_tarefa[] =
{
	"Nome da Tarefa..................:",
		1, 1, TAM_NOME-1, COR_ENTRADA, bopcao, NULL, NULL, NULL, NULL, NULL,
	"Prioridade......................:",
		1, 2, 2, COR_ENTRADA, &bopcao[41], NULL, NULL, NULL, "99", NULL,
	"Numero do Nodo..................:",
		1, 3, 2, COR_ENTRADA, &bopcao[44], NULL, NULL, NULL, "99", NULL,
	"Numero do TTY...................:",
		1, 4, 2, COR_ENTRADA, &bopcao[47], NULL, NULL, NULL, "#9", NULL,
	"Numero de Argumentos............:",
		1, 5, 2, COR_ENTRADA, &bopcao[50], NULL, NULL, NULL, "99", NULL,
	"Rodar em Background.............:",
		1, 6, 3, COR_ENTRADA, &bopcao[53], m_si_no, NULL, NULL, NULL, NULL,
	"Liberar TTY para tarefa.........:",
		1, 7, 3, COR_ENTRADA, &bopcao[57], m_si_no, NULL, NULL, NULL, NULL,
	"Nivel da Senha..................:",
		1, 8, 3, COR_ENTRADA, &bopcao[61], NULL, NULL, NULL, "#99", NULL,
//	NULL,NUL,NUL,NUL,NUL,NULL,NULL,NULL,NULL,NULL,NULL
	NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL
};


#endif  /* MANUTOPER_H_INCLUIDO */
