/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: bib_operacao.h

	CONTEUDO	: Definicoes da biblioteca de operacao

	AUTOR		: Hevelton Araujo Junior

	VERSAO		: 00 - 29/05/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
10/01/95 | Alterada exibicao do texto do cabecalho  			| Leonel
-------------------------------------------------------------------------------
13/10/95 | Reorganizacao do prologo e prototipos de funcoes		| Carlos
-------------------------------------------------------------------------------
******************************************************************************/

#include <stdio.h>

#ifndef	BIBOPER_H_INCLUIDO
#define	BIBOPER_H_INCLUIDO

/* Tipos de teclado para teclas de funcao */
#define	PAGINA_TOTAL					1
#define	PAGINA_PARCIAL					2
#define	SEM_PAGINACAO					3
#define	PAGINA_RCUBAS					4
#define	PAGINA_CCUBAS					5
#define	REL_INSTANTANEO					6
#define	PAGINA_CFG						7

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
#define	PRIORIDADE_DEFAULT			8
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
//#ifdef	VERSAO_INGLES
//  #define	TEXTO_PRI_LIN				" ATAN-SCORE %d.%02d-Smelters Control System: %s - %s"
//#else
//  #define	TEXTO_PRI_LIN				" ATAN-SCORE %d.%02d-Controle de Reducoes: %s - %s"
//#endif

/* Define posicao/atributo para exibicao de erros */
#define	L_ERRO						20
#define	COR_ERRO					( RED_B orb WHITE )

/* Define cores da linha de ajuda */
#define	COR_AJUDA_1					( WHITE_B orb BLACK )
#define	COR_AJUDA_2					( WHITE_B orb RED )

/* Define funcoes da funcao de escrever linha de ajuda */
#define	INICIAR						1
#define	TERMINAR					2

					/****************************/
					/* PROTOTIPACAO DAS FUNCOES */
					/****************************/


/*****************************************************************************


			COMPOSICAO DAS BIBLIOTECAS DE INTERFACE DE OPERACAO


	- A biblioteca de funcoes da console "Console.lib" e composta pelas 
	  seguintes funcoes:

			- FUNCOES COMUNS (OperacaoBib.h e WindowsCBA.h)
			- FUNCOES ESPECIFICAS DE CHAMADA COMUM (OperacaoBib.h e
			  WindowsCBA.h)
			- FUNCOES EXCLUSIVAS DE CONSOLE (WindowsCBA.h)

	- A biblioteca de funcoes do sealtouch "Sealtouch.lib"  e  composta
	  pelas seguintes funcoes:

			- FUNCOES COMUNS
			- FUNCOES ESPECIFICAS DE CHAMADA COMUM
			- FUNCOES EXCLUSIVAS DE SEALTOUCH (Sealtouch.h)


		OBSERVACAO : Os prototipos de funcoes do sealtouch nao foram
			acertados, pois suas funcoes nao foram migradas.


*****************************************************************************/



/****************************  FUNCOES COMUNS  *******************************

	- Funcoes comuns a biblioteca de funcoes da console (Console.lib)
	  e  do  Sealtouch  (Sealtouch.lib),   encontradas   no   arquivo
	  "OperacaoBib.c". Alem dessas funcoes, existem outras declaradas 
	  nos prologos Operacao.h e WindowsCBA.h.

*****************************************************************************/

void IniArqOper (char *ArqMenus, char *ArqOpcoes);
int  ExisteArquivo (char *NomeArq);
void PegaTextoOpcao (char *ArqMenus, long NumMenu, long Num_Opcao, char *Texto);
void ExibeErroTemp (char *Mensagem);


/******************  FUNCOES ESPECIFICAS DE CHAMADA COMUM  *******************

	- Funcoes especificas das bibliotecas "Console.lib" e "Sealtouch.lib",
	  encontradas nos arquivos  "ConsoleCBA.c" e "SealtCBA.c"  respectiva-
	  mente. Essas funcoes apresentam a mesma chamada, entretanto interna-
	  mente o codigo e diferente.

*****************************************************************************/

void LimpaTela (void);
int  ConfirmaTermino (void);
void ExibeErro (char *Mensagem);
void ExibeAtencao (char *Mensagem);
void ExibeErroSav (char *Mensagem);
int  Pergunta (char *Mensagem);
void MostraTeclNumerico (int Tipo);
void ApagaTeclNumerico (void);
int  PedeSenha ( int *operador );
int  NextKey (unsigned TIME);
int  StartWindows(int Tipo);
void EndWindows(void);
void TecladoFuncao (int Tipo, int Modo);
void AguardaFimImp( int NumSeal );

#endif /* BIBOPER_H_INCLUIDO */

