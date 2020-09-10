
/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: operacao.h

	CONTEUDO	: Definicoes para a interface de operacao

	AUTOR		: Hevelton Araujo Junior

	VERSAO		: 00 - 26/05/92

	HISTORICO DAS EDICOES

-------------------------------------------------------------------------------
13/10/95 | Reorganizacao do prologo e prototipos de funcoes		| Carlos
-------------------------------------------------------------------------------
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

#include <Definicao.h>


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
#define	NOME_ARQ_DESC_OPCAO			"/score/config/opcoes."

/* Nome do arquivo de descricao dos menus */
#define	NOME_ARQ_DESC_MENU			"/score/config/menus."

/* Nome do arquivo de respostas dos menus */
#define	NOME_ARQ_RSP				"5:/RspBotoesST"

/* Tipos para o proximo procedimento */
#define	_MENU						1
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
#define	COR_JAN_ALARME				( WHITE )
#define	COR_PED_ARGS				( WHITE_B orb BLACK )

/*-- Chave que indica que foi pedido help --*/
#define	CHAVE_AJUDA					"-h"

/* Constante zero */
#define	NULO						0

/* Numero maximo de menus */
#define	MAX_MENUS					20

/* Numero maximo de opcoes */
#define MAX_OPCOES					20

/* Define a cor preta, ja que o "toolkit" a assume como default */
//#define	BLACK						0
//#define	BLACK_B						0

/* Tamanho maximo para os argumentos de uma funcao/programa */
#define	TAM_ARGS					30
#define	MAX_ARGS					20

/* Tamanho maximo do prompt para os argumentos */
#define	TAM_PROMPT					30

/* Linha de ajuda para entrada dos argumentos */
//#ifdef	VERSAO_INGLES
//  #define	LIN_AJUDA_ARGS				" Esc-Quit   F1-Help   F10-Apply "
//#else
//  #define	LIN_AJUDA_ARGS				" Esc-Abandona  F1-Ajuda  F10-Confirma "
//#endif

/* Tamanho do nome para tarefa */
#define	TAM_NOME					40

/* Tamanho maximo das opcoes */
#define	TAM_OPCOES					40

/* Tmanho do titulo do menu */
#define	TAM_TIT						45

/* Numero de bytes de reserva por registro */
#define	TAM_RESERVA					200

/* Tamanho da estrutura de descricao de um menu */
#define	TAM_DESC_MENU				(sizeof (struct SDescMenu))

/* Tamanho da estrutura de descricao de uma opcao */
#define	TAM_DESC_OPCAO				(sizeof (struct SDescOpcoes))

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
  struct SDescMenu
  {
	unsigned	Inicializado;		/* Indica se registro inicializado */
	unsigned	Linha;				/* Linha inicial (superior) */
	unsigned	Coluna;				/* Coluna Inicial (esquerda) */
	unsigned	NumOpcoes;			/* Numero de opcoes (= numero de linhas) */
	unsigned	NumColunas;			/* Numero de colunas (calculado) */
	unsigned	Atributo;			/* Atributo de cor do menu */
	unsigned	Moldura;			/* Tipo de moldura */
	unsigned	Direcao;			/* Direcao do menu (horiz. ou vert.) */
	unsigned	NumLinhas;			/* Numero de linhas entre opcoes */
	char		Titulo[TAM_TIT];	/* Titulo do menu */
	struct
	{
	  char		TextosOpcoes[TAM_OPCOES];
	} Textos[MAX_OPCOES];
  } t_menus;

/* Estrutura de um registro no arquivo de descricao das opcoes */
typedef
  struct SDescOpcoes
  {
	unsigned	Inicializado;					/* Indica se registro inicializado */
	int			TipoProximo;					/* Proximo procedimento */
	int			NivelSenha;						/* Nivel de acesso */
	union
	{
	  struct DescrTarefa
	  {
		char	Nome[TAM_NOME];				/* Nome do programa */
		int		Prioridade;					/* Prioridade do programa */
		int		NumTTY;						/* TTY do programa */
		int		NumNodo;					/* Nodo do programa */
		word	Flags;						/* Flags de criacao */
		int		NumArgs;
		struct	DescrArgs
		{
		  char	Prompt[TAM_PROMPT];			/* Prompt do argumento */
		  word	Tamanho;					/* Tamanho do argumento */
		  char	Valor[TAM_ARGS];			/* Conteudo do argumento */
		} Args[MAX_ARGS];
	  } Tarefa;

	  struct DescrMenus
	  {
		int  NumMenu;						/* Numero do menu */
	  } Menu;
	} Proximo;
  } t_opcoes;


/****************************  FUNCOES COMUNS  *******************************

	- Funcoes comuns a biblioteca de funcoes da console (Console.lib)
	  e  do  Sealtouch  (Sealtouch.lib),   encontradas   no   arquivo
	  "OperacaoBib.c".

*****************************************************************************/

int LeRegMenu (char *ArqMenus, long NumMenu, t_menus *Dados);
int LeRegOpcao (char *ArqOpcoes, long NumMmenu, long NumOpcao,
				t_opcoes *Dados);
int GravaRegMenu (char *ArqMenus, long NumMenu, t_menus *Dados);
int GravaRegOpcao (char *Arqopcoes, long NumMenu, long NumOpcao,
				   t_opcoes *Dados);
int ExibeMenuOperacao (t_menus *Dados);

#endif /* OPERACAO_H_INCLUIDO */
