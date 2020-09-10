
/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: bib_operacao.h

	CONTEUDO	: Definicoes da biblioteca de operacao

	AUTOR		: Hevelton Araujo Junior

	VERSAO		: 00 - 29/05/92

	HISTORICO DAS EDICOES

******************************************************************************/

#ifndef	BIBOPER_H_INCLUIDO
#define	BIBOPER_H_INCLUIDO

	/************************/
	/* INCLUSAO DE ARQUIVOS */
	/************************/

#include "operacao.h"

/* Valores defult para inicializacao do arquivo de descricao de menus */
#define	LINHA_DEFAULT				1
#define	COLUNA_DEFAULT				1
#define	NUM_OPT_DEFAULT				0
#define	NUM_COLS_DEFAULT			5
#define	ATRIBUTO_DEFAULT			WHITE
#define	MOLDURA_DEFAULT				NOBORDER
#define	DIRECAO_DEFAULT				VERTICAL
#define	NUM_LINS_DEFAULT			0

/* Valores defult para inicializacao do arquivo de descricao de opcoes */
#define	PRIORIDADE_DEFAULT			0
#define	NUM_TTY_DEFAULT				-1
#define	NODO_DEFAULT				0
#define	NUM_ARGS_DEFAULT			0
#define	FLAGS_DEFAULT				0
#define	NIVEL_SENHA_DEFAULT			-1

/* Define posicao/atributo para perguntas */
#define	PERG_Y						18
#define	COR_JAN_PERG				( WHITE_B orb BLUE )

/* Define posicao/atributo para confirmacao de saida */
#define	C_CONF						23
#define	L_CONF						18
#define	COR_CONF					( WHITE_B orb BLUE )

/* Define texto da primeira linha */
#define	TEXTO_PRI_LIN				" ATAN - SCORE - Sistema de Controle de Reducoes"

/* Define posicao/atributo para exibicao de erros */
#define	L_ERRO						20
#define	COR_ERRO					( RED_B orb WHITE )

/* Define cores da linha de ajuda */
#define	COR_AJUDA_1					( WHITE_B orb BLACK )
#define	COR_AJUDA_2					( WHITE_B orb RED )

/* Define funcoes da funcao de escrever linha de ajuda */
#define	INICIAR						1
#define	TERMINAR					2

#define	NUL							'\0'

	/****************************/
	/* PROTOTIPACAO DAS FUNCOES */
	/****************************/

void inicializa_arquivos_operacao ( void );
void inicializa_tela_padrao ( void );
int le_registro_menu ( long num_menu , struct s_desc_menu *dados );
int le_registro_opcao ( long num_menu , long num_opcao , struct s_desc_opcoes *dados );
int grava_registro_menu ( long num_menu , struct s_desc_menu *dados );
int grava_registro_opcao ( long num_menu , long num_opcao , struct s_desc_opcoes *dados );
int existe_arquivo ( char *nome );
void limpa_tela ( void );
int confirma_termino ( void );
void mens_erro ( char *mensagem );
void escreve_linha_ajuda ( int coluna , int linha , int ncols , char *texto , int escolha );
int le_string ( struct Window *janela, int x , int y , int tam , char *dado , char *prompt , unsigned cor);
int exibe_menu_operacao ( struct s_desc_menu *dados );
int exibe_menu ( struct Menu *pmenu , int cor , int direc , int nlins , int x , int y , char *titulo );
void sai_educadamente ( void );
int pergunta ( char *mensagem );
void pega_texto_opcao ( long num_menu , long num_opcao , char *texto );

#endif /* BIBOPER_H_INCLUIDO */

