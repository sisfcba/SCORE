/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: SCORE - CONTROLE DE REDUCOES

	SISTEMA		: TODOS

	ARQUIVO		: IniArqVar.h

	CONTEUDO	: Contem as definicoes de todas as variaveis logaveis do sistema

	AUTOR		: Alexandre Bandeira

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0          -      DATA  : 05/02/95

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
03/01/2001 | Inclusao de tabelas para o Atn8                    | Leonel
-------------------------------------------------------------------------------
******************************************************************************/
/*********************************** Revisoes ********************************\
$Id: IniArqVar.h,v 1.5.4.1 2015/03/03 17:03:06 leo Exp $

$Log: IniArqVar.h,v $
Revision 1.5.4.1  2015/03/03 17:03:06  leo
Inclusao do XMLScore para comunicacao via OPC.

Revision 1.5  2008/07/03 14:32:40  alex
trocado nivel de senha da sinalizacao de corrida, troca de pinos e manobra
de cruzeiro para nivel 20. A CBA ira criar usuarios com este nivel.

Revision 1.4  2005/05/31 19:37:32  leo
Correcoes feitas durante primeira pre-operacao CBA sala 125kA VI

Revision 1.3  2003/02/20 13:35:28  alex
Correcao do comentario

Revision 1.2  2003/02/20 12:39:43  alex
Trocado o path rela do arqvar.dat para relativo

\*********************************** Revisoes ********************************/

/*--- Verifica se ja foi incluido ---*/
#ifndef	_INIARQVAR_H
	#define	_INIARQVAR_H

/*
--------------------------------------------------------------------------------
							INCLUSOES
--------------------------------------------------------------------------------
*/
#include <Score.h>

/*
--------------------------------------------------------------------------------
							DEFINICOES
--------------------------------------------------------------------------------
*/

#define SHORT_INT       0
#define	INT				1
#define FLOAT			2
#define LONG			3
#define DOUBLE          4
#define	BYTE			5

#define STRING			10
#define T_HORA			11
#define	MASC_BITS16		12
#define	T_DATA_HORA		13	/* tratamento de data e hora para xmlscore */

#define	NOME_ARQUIVO		"/score/base_dados/arqvar.dat"
#define	NOME_ARQUIVO1		"/score/base_dados/arqvar1.dat"
#define	LOCAL_NOME_ARQUIVO	"arqvar.dat"
#define	LOCAL_NOME_ARQUIVO1	"arqvar1.dat"

#define	PATH_LIMITES		"/score/base_dados/%s"
#define	LOCAL_PATH_LIMITES	"%s"

/* -- Alteracao - Inicio - 14/02/2001 - Leonel - Aumentado num. var. para sala 86ka -- */
/* **** #define MAX_VARIAVEIS   200 *** */
#define MAX_VARIAVEIS   300
/* -- Alteracao - Fim - 14/02/2001 - Leonel - Aumentado num. var. para sala 86ka -- */

#define T0   0x0000 /* nenhum */
#define T1   0x0001 /* configura graficos de cubas */
#define T2   0x0002 /* configura alarmes de cubas */
#define T3   0x0004 /* configura parametros de cubas */
#define T4   0x0008 /* somente titulo */
#define T5   0x0010 /* configura parametros de linha */
#define T6   0x0020 /* configura historico */
#define T7   0x0040 /* rel parametros de cubas */
#define T8   0x0080 /* rel parametros de linha */
#define T9   0x0100 /* migracao para planilha  */
#define T10  0x0200 /* configuracao parametros/cubas coletor  */
#define T11  0x0400 /* relatorio estatistico rede echelon  */
#define T12  0x0800 /* configura parametros metais (CBA 64KA)  */
#define T13  0x1000 /* configura alimentacao */
#define T14  0x2000 /* escrita OPC */
#define T15  0x4000 /* leitura OPC */

#define TODAS_T   	( T1 orb T2 orb T6 )
#define TITULO_1  	( T3 orb T4 )
#define TITULO_2  	( T7 orb T4 )
#define TITULO_3  	( T5 orb T4 )
#define TITULO_4  	( T8 orb T4 )
#define TITULO_5  	( T11 orb T4 )
#define TITULO_6  	( T12 orb T4 )
#define PAR_CUBAS 	( TODAS_T orb T3 )
#define PAR_LINHA 	( TODAS_T orb T5 )
#define REL_CUBAS 	( TODAS_T orb T7 )
#define REL_LINHA 	( TODAS_T orb T8 )
#define PAR_PLAN  	( TODAS_T orb T9 )
#define PAR_COLETOR ( PAR_CUBAS orb T10 )
#define REL_ECHELON ( T1 orb T6 orb T11 )
#define PAR_METAIS	( T12 )
#define	PAR_ALIMENT	( T13 )
#define	OPC_RW		( T14 orb T15 )
#define	OPC_R		( T15 )
#define	OPC_W		( T14 )

#define AT	 ALG_TODOS	/* todos algoritmos */
#define A0   ALG_NENHUM	/* nenhum algoritmo */

/* -- Algoritmos reservados para a Atan -- */
#define A1   ALG_SCORE01		/* algoritimo atan */
#define A2   ALG_SCORE02		/* algoritimo atan */
#define A3   ALG_SCORE03		/* algoritimo atan */
#define A4   ALG_SCORE04		/* algoritimo atan */
#define A5   ALG_SCORE05		/* algoritimo atan */
#define A6   ALG_SCORE06		/* algoritimo atan */
#define A7   ALG_SCORE07		/* algoritimo atan */
#define A8   ALG_SCORE08		/* algoritimo atan */

/* -- Algoritmos de usuario -- */
#define A9   ALG_USER01
#define A10  ALG_USER02
#define A11  ALG_USER03
#define A12  ALG_USER04
#define A13  ALG_USER05
#define A14  ALG_USER06
#define A15  ALG_USER07
#define A16  ALG_USER08

/* -- grupos de tabelas possiveis -- */
#define G0	 0
#define G1	 1
#define G2	 2
#define G3	 3
#define G4	 4
#define G5	 5
#define G6	 6
#define G7	 7
#define G8	 8
#define G9	 9
#define G10	 10
#define G11	 11
#define G12	 12
#define G13	 13
#define G14	 14
#define G15	 15

/* -- 1o. algoritmo atan mais 1o. algoritmo de usuario -- */
#define A1_9 	(A1 orb A9)
/* -- 2§ e 3§ algoritmos da ATAN -- */ 
#define A2_3	(A2 orb A3)

#define NIVEL_SUPER		255
#define NIVEL_CONFIG_0	200
#define NIVEL_CONFIG_1  100
#define NIVEL_CONFIG_2	75
#define NIVEL_LOG		50
#define NIVEL_OPER		25
#define NIVEL_OPER_2	20

/*--- Tabela de variaveis da estrutura com os parametros do AVC ---*/
#define TAB_PARAM_AVC			0
/*--- Tabela de variaveis da estrutura contendo o ciclo de leitura do AVC ---*/
#define TAB_CLEIT_AVC			1
/*--- Tabela de variaveis da estrutura contendo o ciclo de controle(MCP) do AVC ---*/
#define TAB_CCONT_MCP_AVC		2
/*--- Tabela de variaveis da estrutura contendo o ciclo de controle do AVC ---*/
#define TAB_CCONT_AVC			3
/*--- Tabela de variaveis da estrutura relativa a efeito anodico do AVC ---*/
#define TAB_EA_AVC				4
/*--- Tabela de variaveis da estrutura relativa a ruidos do AVC ---*/
#define TAB_RUIDO_AVC			5
/*--- Tabela de variaveis da estrutura com as variaveis de supervisao -- */
/* -- diaria do AVC ---*/
#define TAB_SUP_AVC				6
/*--- Tabela de variaveis da estrutura com as variaveis de estado do AVC ---*/
#define TAB_EST_DISC_AVC		7
/*--- Tabela de variaveis da estrutura com as variaveis de controle de linha ---*/
#define TAB_CONT_AVL			8
/*--- Tabela de variaveis da estrutura com as variaveis de usuario avc ---*/
#define TAB_PAR_USER1           9
/*--- Tabela de variaveis da estrutura com as variaveis de usuario avc ---*/
#define TAB_PAR_USER2           10
/*--- Tabela de variaveis da estrutura com as variaveis de usuario avc ---*/
#define TAB_USER1_AVC           11
/*--- Tabela de variaveis da estrutura com as variaveis de usuario avc ---*/
#define TAB_USER2_AVC           12
/*--- Tabela de variaveis da estrutura com as variaveis de usuario avc ---*/
#define TAB_USER3_AVC           13
/*--- Tabela de variaveis da estrutura com as variaveis de usuario avc ---*/
#define TAB_USER4_AVC           14

#define TAB_CONV_MUX            15

#define TAB_CONV_NMUX           16

#define TAB_ENT_ESP             17

/* -- alteracao - inicio - 03/01/2001 - Leonel - Inclusao tabelas p/ Atn8 -- */
#define TAB_CONV_CUBA_ATN8      18
#define TAB_CONV_ESP_ATN8       19

/* -- Numero maximo de tabelas do DescrArqVar -- */
// #define MAX_TABELAS     18
#define MAX_TABELAS     20
/* -- alteracao - fim - 03/01/2001 - Leonel - Inclusao tabelas p/ Atn8 -- */

/*--- Estrutura dos campos na tela de entrada de dados ---*/
typedef
  struct ParVarLog
  {
	char	 *NomeVar;
    char	 *UEvar;
	void	 *EndrVar;
    byte     NivelSenha;
	char	 TipoVar;
    char	 *FmtVar;
	float	 LimInf;
	float	 LimSup;
	float	 FatConv;
    unsigned TipoProg;
	unsigned FlagAlg;
	char	 *Rotulo;
	char	 *Tag;
	byte	 GrupoVar;
  } t_par_var_log;

typedef
  struct NomeAlgCtr
  {
	char *Algoritmo;
  } t_NomeAlgCtr;
  
typedef
  struct NomeTabelas
  {
	char *Nome;
  } t_NomeTabelas;

typedef
  struct Variavel
  {
	char     NomeVar[20];
    char     UEvar[20];
	int      OffVar;
    byte     NivelSenha;
	char     TipoVar;
    char     FmtVar[11];
    char     TamVar;
    char     PrecVar;
	float    LimInf;
	float    LimSup;
	float    FatConv;
    unsigned TipoProg;
	unsigned FlagAlg;
	char	 Rotulo[8];
	char	 Tag[11];
	byte	 GrupoVar;
  } t_variavel;

typedef
  struct ArqVar
  {
    byte f_novo;
	char NomeAlgCtr[17][9];
	char NomeTabelas[16][19];
    struct t_tabela
    {
      t_variavel Var[MAX_VARIAVEIS];
      int Tab;
    }Tabela[MAX_TABELAS];
  } t_arqvar;

typedef
  struct LimitesLog
  {
    char  NomeVar[20];
    char  UEvar[20];
    char  FmtVar[11];
    char  PrecVar;
    char  TagInf[8];
    char  TagSup[8];
    byte  NivelSenha;
	float LimInf;
	float LimSup;
	float FatConv;
  }t_lim_log;

#define TAM_LIM_LOG_REG (sizeof(t_lim_log))
#define TAM_LIM_LOG_TOT (TAM_LIM_LOG_REG*MAX_VARIAVEIS)

#define TAM_ARQVAR (sizeof(t_arqvar))

#ifdef PROGRAMA_PRINCIPAL

char *NomeTabelas[] =
{
    "Parametros AVC    ",
    "Ciclo Leitura     ",
    "Ciclo Controle MCP", /* tamanho maximo */
    "Ciclo Controle    ",
    "Efeito Anodico    ",
    "Ruido             ",
    "Supervisao Diaria ",
    "Estados Discretos ",
    "Controle Linha    ",
    "ParUser AVC 1     ",
    "ParUser AVC 2     ",
    "Usuario AVC 1     ",
    "Usuario AVC 2     ",
    "Usuario AVC 3     ",
    "Usuario AVC 4     ",
    "Conversor MUX     ",
    "Conversor NMUX    ",
    "Entrada ESP       ",
/* -- alteracao - inicio - 03/01/2001 - Leonel - Inclusao tabelas p/ Atn8 -- */
    "Conv A/D Cuba Atn8",
    "Conv A/D Esp Atn8 "
/* -- alteracao - fim - 03/01/2001 - Leonel - Inclusao tabelas p/ Atn8 -- */
};

char *ArqLimTabela[] =
{
  "ArqLim0",
  "ArqLim1",
  "ArqLim2",
  "ArqLim3",
  "ArqLim4",
  "ArqLim5",
  "ArqLim6",
  "ArqLim7",
  "ArqLim8",
  "ArqLim9",
  "ArqLim10",
  "ArqLim11",
  "ArqLim12",
  "ArqLim13",
  "ArqLim14",
  "ArqLim15"
};

/*--- Estrutura para receber as variaveis do sistema ---*/
t_param_avc		 VarParamAvc;
t_cicleit_avc	 VarCLeitAvc;
t_ccont_mcp_avc	 VarCcontMcp;
t_ciccont_avc	 VarCContAvc;
t_ea_avc		 VarEAAvc;
t_ruido_avc		 VarRuiAvc;
t_avc_supervisao VarSuperv;
t_est_avc        VarEst;
t_avl            VarAvl;
t_par1_user      VarPar1;
t_par2_user      VarPar2;
t_user1_avc      VarUser1;
t_user2_avc      VarUser2;
t_user3_avc      VarUser3;
t_user4_avc      VarUser4;
t_conv_mux       VarConvMUX;
t_conv_nmux      VarConvNMUX;
t_conv_esp       VarEntESP;
/* -- alteracao - inicio - 03/01/2001 - Leonel - Inclusao tabelas p/ Atn8 -- */
t_conv_cuba_atn8 VarConvAtn8;
t_conv_esp_atn8	 VarConvEspAtn8;
/* -- alteracao - fim - 03/01/2001 - Leonel - Inclusao tabelas p/ Atn8 -- */

#else	/* -- nao e' o programa principal -- */

extern char 		*NomeTabelas[];
extern char			*ArqLimTabela[];

extern t_arqvar      Arq;

#endif  /* -- #ifdef PROGRAMA_PRINCIPAL -- */

#endif	/*--- #ifndef _INIARQVAR_H -- */
