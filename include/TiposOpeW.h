/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: TiposOpeW.h

	CONTEUDO	: Definicoes para a interface de operacao windows

	AUTOR		: Alexandre Mariz Bandeira de Morais

	VERSAO		: 01 - 22/09/95

	HISTORICO DAS EDICOES
------------------------------------------------------------------------------
 Data     | Descricao												| Autor
------------------------------------------------------------------------------
 16/04/97 | Inclusao da estrutura t_grupo_cubas						| Carlos
------------------------------------------------------------------------------
******************************************************************************/

#ifndef		_TIPOS_OPE_W_H
#define		_TIPOS_OPE_W_H

	/***************************/
	/* DEFINICAO DE CONSTANTES */
	/***************************/

#define SELECAO_SALA_1 				0
#define SELECAO_SALA_2 				1
#define SELECAO_SALA_3 				2
#define SELECAO_SALA_4 				3
#define SELECAO_SALA_5				4
#define SELECAO_SALA_6 				5
#define SELECAO_SALA_7 				6
#define SELECAO_SALA_8 				7
#define SELECAO_TODAS 				10
#define SELECAO_CUBAS				11

#define	NOME_ARQ_DESCR_IHM			"/score/config/ihm_config"

#define	NOME_ARQ_FILTRO 			"/score/config/filtros"

#define	NOME_ARQ_CUBAS	 			"/score/tmp/ArqCubas"

/* Tamanho da estrutura do ihm */
#define	TAM_DESCR_IHM				( sizeof(struct ihm_config ) )

/* Tamanho do header estrutura de filtros */
#define	TAM_H_FILTRO  				( sizeof(struct header_filtrosPD ) )

/* Tamanho da estrutura de filtros */
#define	TAM_FILTRO  				( sizeof(struct filtrosPD ) )

/* Tamanho da estrutura do ihm */
#define	TAM_DESCR_TAG				( sizeof(struct descr_tag ) )

/* Tamanho do Header do ihm */
#define TAM_HEADER_IHM              ( TAM_DESCR_IHM - (TAM_DESCR_TAG*MAX_TAGS) )

#define TAM_LISTA_ALA_PEND          10

/* tamanho de estruturas */
#define MAX_TAGS                    140 /*160*/
#define MAXI_ARGS                   12 /*15*/

/* tipos de procedimentos */
#define MENU                        0
#define TAREFAS                     1
#define EXEC_ACAO                   2
#define PRE_SELECAO                 3

#define MAX_PRE						16
#define MAX_ALG						16

#define TAM_CAMPO_PRE				32
#define COL_PRE						1600
#define OFF_PRE						200
#define ALG_AUTO					0xFFFFFFFF

/* lista de argumentos */
#define ARG_FAIXA_CUBAS             0
#define ARG_ALGORITMO				1
#define ARG_DATA_INI                3
#define ARG_DATA_FIM                4
#define ARG_CUBA_EX                 5
#define ARG_DIA_EX                  6
#define ARG_TURNO                   7
#define ARG_TAG                     8
#define ARG_REDUCAO                 9
#define ARG_TITULO                  10
#define ARG_OPERADOR                11
#define ARG_LISTA                   20
#define ARG_STRING                  21
#define ARG_OUTROS                  22
#define ARG_ENT_CUBAS               23
#define ARG_ENT_CUBAS_II            24
#define ARG_CONFIRMA                100

#define ALARME_1         			0
#define ALARME_2         			1
#define ALARME_3         			2
#define ALARME_4         			3
#define ALARME_5         			4
#define ALARME_6         			5
#define ALARME_7         			6
#define ALARME_8         			7
#define ALARME_9         			8
#define ALARME_10        			9
#define NORMAL           			10

#define MEM_POR_REDUCAO	 			10
#define MAX_REDUCAO_IHM	 			10

	/***********************/
	/* DECLARACAO DE TIPOS */
	/***********************/

typedef struct ParCubas
  {
    short int Total;
    short int NumCuba[MAX_CUBAS];
    short int IndCuba[MAX_CUBAS];
  } t_ParCubas;

/* estrutura dos filtros pre-definidos */

typedef struct header_filtrosPD
  {
	char nome_mem[MEM_POR_REDUCAO*MAX_REDUCAO_IHM][11];
  }t_h_filtrosPD;
	
typedef struct filtrosPD
  {
    unsigned f_SelCubas;
	unsigned alg_ctr;
	byte	 Impressora;
    char alg_str[200];
	char cubas_selecao[200];
    char cubas_excluidas[200];
    char data_inicial[9];
    char data_final[9];
    char turno[9];
    char dias_excluidos[200];
    t_ParCubas Par;
  }t_filtrosPD;

/* estrutura do descritor de argumentos */
typedef struct descr_arg
  {
    short int tipo_arg;             /* 0=especial,1=algoritmo,3=data_inicial
                                       4=data_final,5=lista_cubas_excluidas 
                                       6=lista_dias_excluidos,7=turno,8=tag
                                       9=reducao,10=titulo,11=operador
                                       20=lista,21=string, 22=outros(tipo string)
                                       100=argumento para uso do ihm_windows para
                                       confirmar a chamada de um menu, tarefa ou acao; o
                                       texto contendo a pergunta deve estar no valor default;
                                       lembrando que a pergunta deve ser feita para um
                                       confirma ou cancela; este argumento nao e passado para tarefa ! */
    char valor_default[100];        /* ultimo valor selecionado p/ tipo >=20 */
                                    /* no caso menu colocar o tag do menu que esteja */
                                    /* relacionado, ou deixar em branco se nao tem relacao */
    char tag_default[100];          /* ultimo valor selecionado p/ tipo >=20 */
    char texto_item[32];            /* texto do item */
	byte lista_auto;				/* 0=lista pre-definida, 1=lista on-line */
	char titulo_lista1[20];			/* titulo1 - apenas para lista on-line */
	char titulo_lista2[20];			/* titulo2 - apenas para lista on-line */
	byte num_titulos;				/* 1 a 2 - apenas para lista on-line */
	char texto_tag1[100];			/* texto|tag - apenas para lista on-line */
	char texto_tag2[100];			/* texto|tag - apenas para lista on-line */
    char nome_lista[40];            /* apenas p/ tipo=lista, arquivo (.pict/.wnd) contendo a lista.
                                       o arquivo devera conter sufixo 00, 01, 02 se houver mais de
                                       um. Porem o nome passado nao devera conter o sufixo.
                                       EX: bobo.pict, nome_lista=bobo apenas */
    short int num_itens_lista;      /* numero maximo de itens selecionaveis na lista */
  }t_descr_arg;

/* estrutura do descritor de tags */
typedef struct descr_tag
  {
    byte f_grava;                   /* flag de gravacao de argumentos
                                       1=grava, 0=nao grava */
    byte f_mostra_args;				/* mostra argumentos antes de chamar tarefa */
    byte f_confirma;                /* flag de confirmacao do comando pedido
                                       1=tem confirmacao, 0=nao tem confirmacao
                                       obs.: usado como o argumento 100 */
    byte f_ajuda;                   /* flag de ajuda para o relatorio
                                       1=tem ajuda, 0=nao tem ajuda */
    int pid_p;                      /* identificacao da picture do tag */
    byte tipo;                 		/* 0xFF=nao inic,0=menu,1=tarefa,2=executa acao */
    byte pict_menu;            		/* indice do tag menu a qual este tag pertence */

    char tag[32];                   /* lembrando que e' o mesmo que foi definido na window ou pict */
    char nome[40];                  /* menu=nome pict,tarefa=nome tarefa,acao=nome acao
                                       'FIM', 'REC_EV', 'REC_TODOS_EV' */
    short int nivel_senha;
    short int prioridade;           /* apenas p/ tarefas */
    short int flags_criacao;        /* apenas p/ tarefas */
	short int index_msg;			/* indice para o MsgStr */
    short int num_args;             /* numero de argumentos p/ tarefa */
    t_descr_arg descr_arg[MAXI_ARGS];
  }t_descr_tag;
  
/* estrutura o ihm para Windows */

typedef struct ihm_config
 {
   char tela_inicial[40];           /* nome do .wnd e .pict inicial */
   int  pid_w_inicial;              /* id window */
   int  pid_p_inicial;              /* id picture */
   char opcoes[10];                 /* opcoes p/ abertura da window principal */
   char reserva[30];                /* reserva */
   int  reserva1[2];                /* reserva1 */
   char reserva2[32];               /* reserva2 */
   t_descr_tag descr_tag[MAX_TAGS];
 }t_ihm_config;
 
/* estrutura de alarmes */

typedef struct alarme
 {
   short int  EstadoAtual[TAM_LISTA_ALA_PEND+1];
   short int  VarAtual[TAM_LISTA_ALA_PEND+1];
   byte       RecAtual[TAM_LISTA_ALA_PEND+1];
   long       IndAtual[TAM_LISTA_ALA_PEND+1];
  }t_alarme;
  
typedef struct LeEventos
{
  int			Evento[10];
  int			NumEvs;
  long			DataAtual;
  long			DataInicial;
  long			DataFinal;
  byte			NaoPara;
  t_filtrosPD	filtros;  	    
}t_LeEventos;

#define MAX_CUBAS_TELA   60
#define MAX_GRUPOS_TELA  10

typedef struct _GrupoCuba
{
  short int NumGrupos;
  short int NGrupo;
  int       Sid;
  int       Wid;
  int       Wid1;
  short int	Grafico;
  struct {
    short int NumCubas;
    struct {
      short int NumCuba;
      short int IndCuba;
      short int CorCuba;
    }Cuba[MAX_CUBAS_TELA];
   
    short int AlaGrupo;
    short int AlaGrupoAnt;
    int       Pid;
    int       Pid1;
  } Grupo[MAX_GRUPOS_TELA];

} t_GrupoCuba;

typedef struct GrupoxCuba
{
  short int NumGrupos;
  struct {
    short int NumCubas;
    struct {
      short int NumCuba;
      short int IndCuba;
    }Cuba[MAX_CUBAS_TELA];
  } Grupo[MAX_GRUPOS_TELA];
} t_grupo_cuba;

#endif		/* _TIPOS_OPE_W_H */
