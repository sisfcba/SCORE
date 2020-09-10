//****************************************************************************
//
//			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
//	   SCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 1.0
//
//	PROJECT		: ALL
//
//	SYSTEM		: ALL
//
//	FILE		: OperacaoPH.hpp
//
//	DESCRIPTION	: This module contain IHM Photon typedef structs and variables
//
//	AUTHOR		: Alexandre Mariz Bandeira de Morais
//
//	OPERATING SYSTEM:  QNX 4.25		-	COMPILER: WATCOM C++ - V10.6
//
//	VERSION		: 1.0			-		DATE	:	24/05/99
//
//	HISTORY
//----------------------------------------------------------------------------
//Date     | Description                                          | Author 
//----------------------------------------------------------------------------
//24/05/99 | Initial edition                                      | Bandeira
//----------------------------------------------------------------------------
//****************************************************************************

#ifndef		_OperacaoPH
#define		_OperacaoPH

#include	<fcntl.h>
#include	<ctype.h>
#include	<process.h>
#include	<math.h>
#include	<stdarg.h>
#include	<sys/name.h>
#include	<sys/proxy.h>
#include	<sys/qnx_glob.h>
#include	<sys/mman.h>
#include	<sys/stat.h>
#include	<sys/types.h>
#include	<sys/wait.h>

#if defined(__cplusplus)
extern "C" {
#endif

#include	<Definicao.h>
#include	<ScoreConst.h>
#include	<ScoreMsgs.h>
#include	<ScoreErros.h>
#include	<Score.h>
#include	<VarsComum.h>
#include	<Prototipos.h>
#include	<IniArqVar.h>
#include    <Eventos.h>
#include    <RelGraf.h>
#include	<BdScore.h>

#if defined(__cplusplus)
};
#endif

#include 	<ConfIHMLibph.hpp>
#include	<ScoreLibph.hpp>
#include	<IhmPh.hpp>

//#define						PH_NOME_ARQ_FILTRO		"/usr/score/config/filtrosPH"
#define						PH_NOME_ARQ_FILTRO		"filtrosPH"
#define						PH_DIR_ARQ_FILTRO		"/home/"
#define						PH_NOME_ARQ_CUBAS		"/usr/score/tmp/arqcubas"
#define						PH_NOME_COMUM_ALARME	"Atan/Score/ComumAlarme"
const int					PH_TAM_LISTA_ALA_PEND=10;
const int					PH_MEM_POR_REDUCAO=10;
const int					PH_MAX_REDUCAO_IHM=10;
const int					PH_SELECAO_SALA_1=0;
const int					PH_SELECAO_SALA_2=1;
const int					PH_SELECAO_SALA_3=2;
const int					PH_SELECAO_SALA_4=3;
const int					PH_SELECAO_SALA_5=4;
const int					PH_SELECAO_SALA_6=5;
const int					PH_SELECAO_SALA_7=6;
const int					PH_SELECAO_SALA_8=7;
const int					PH_SELECAO_TODAS=10;
const int					PH_SELECAO_CUBAS=11;
const int					PH_MAX_PRE=16;
const int					PH_MAX_ALG=16;
const int					PH_TAM_CAMPO_PRE=32;
const int					PH_ALG_AUTO=0xFFFFFFFF;
const int					PH_ALG_TODOS=0x0000FFFF;
const int					PH_ALG_NENHUM=0x00000000;
const int					PH_MAX_EXC_DATAS=14;
const int					PH_MAX_EXC_CUBAS=44;
const int					PH_MAX_CUBAS_GRUPO=60;
const int					PH_MAX_GRUPOS_CUBAS=16;
const int					PH_MAX_LINES_HELP=80;
const int					PH_MAX_CARS_HELP=82;
const int					PH_LINES_PAG_HELP=20;
const int					MAX_ERRO_SCORE_BD=3;
const int					PH_NUM_CUBAS_LINHA=15;
const int					MAX_CALLBACKS_LISTVALUETASK=300;

/* estrutura dos filtros pre-definidos */
typedef struct p_cubasPH
{
  short int		Total;
  short int		NumCuba[MAX_CUBAS];    
  short int		IndCuba[MAX_CUBAS];    
}t_p_cubasPH;

typedef struct h_filtrosPH
{
  char NomeMem[11];
}t_h_filtrosPH;
	
typedef struct b_filtrosPH
{
  unsigned		SelCubas;
  unsigned		AlgCtr;
  unsigned char Impressora;
  char 			AlgStr[200];
  char			CubasSelecao[200];
  char			CubasExcluidas[200];
  char			DataInicial[9];
  char 			DataFinal[9];
  char			Turno[9];
  char			DiasExcluidos[200];
  t_p_cubasPH	Par;
}t_b_filtrosPH;

typedef struct r_filtrosPH
{
  t_h_filtrosPH	Header;
  t_b_filtrosPH	Body;
}t_r_filtrosPH;

typedef struct filtrosPH
{
  t_b_filtrosPH	Body;
  struct {
	struct {
  	  t_r_filtrosPH	Reg;
	}Mem[PH_MEM_POR_REDUCAO];
  }Red[PH_MAX_REDUCAO_IHM];
}t_filtrosPH;

typedef	struct {
	struct {
		PtWidget_t			*keyboard_wid;
		char				keyboard_l[30];
		short int			keyboard_arg;
		short int			keyboard_itens;
	}key;
	struct {
		PtWidget_t			*list_wid1;
		PtWidget_t			*list_wid2;
		PtWidget_t			*list_wid_clear;
		PtWidget_t			*list_wid_avanca;
		PtWidget_t			*list_wid_retro;
		short int			list_arg;
		short int			list_itens;
		short int			list_itens_get1;
		short int			list_itens_get2;
		short int			n_pags;
		struct {
			short int	n_buttons;
			PtWidget_t	*widget;
			struct {
				PtWidget_t	*widget;
			}button[40];
		} pag[10];
	}list;
	struct {
		PtWidget_t			*string_wid[5];
		char				string_l[5][30];
		short int			string_arg[5];
	}str;
} InfoGets_t;

typedef struct {
  struct	RegDescEventos	reg[MAX_EVS];
} RegEv_t;

/* estrutura de alarmes */
typedef struct alarmePH
{
  short int			EstadoAtual[PH_TAM_LISTA_ALA_PEND+1];
  short int			VarAtual[PH_TAM_LISTA_ALA_PEND+1];
  long				IndAtual[PH_TAM_LISTA_ALA_PEND+1];
  unsigned char		RecAtual[PH_TAM_LISTA_ALA_PEND+1];
}t_alarmePH;

typedef struct	_selecao
{
    PtWidget_t *selecao;
	PtWidget_t *pListGroups[MAX_GRUPOS_CUBAS];
	PtWidget_t *pListAlgs[PH_MAX_ALG];
    PtWidget_t *titulo;
    PtWidget_t *all_pots;
    PtWidget_t *special_pots;
    PtWidget_t *get_special_pots;
    PtWidget_t *get_exclusion_pots;
    PtWidget_t *label_exclusion;
    PtWidget_t *line1_exclusion;
    PtWidget_t *line2_exclusion;
    PtWidget_t *label_special;
    PtWidget_t *line1_special;
    PtWidget_t *line2_special;
    PtWidget_t *label_date_ini;
    PtWidget_t *date_ini;
    PtWidget_t *label_date_end;
    PtWidget_t *date_end;
    PtWidget_t *label_shift;
    PtWidget_t *shift;
    PtWidget_t *actual;
    PtWidget_t *next;
    PtWidget_t *before;
    PtWidget_t *get_excluded_days;
    PtWidget_t *label_excluded_days;
    PtWidget_t *excluded_days;
    PtWidget_t *label_alg;
    PtWidget_t *label_mem;
    PtWidget_t *mem_read;
    PtWidget_t *mem_write;
    PtWidget_t *nodo_printer;
    PtWidget_t *label_nodo_printer;
    PtWidget_t *label_logon;
    PtWidget_t *logon;
    PtWidget_t *label_time_inactivity;
    PtWidget_t *time_inactivity;
    PtWidget_t *alg_all;
    PtWidget_t *alg_auto;
    PtWidget_t *cancel;
    PtWidget_t *done;
    PtWidget_t *exporta_auto;
    PtWidget_t *label_exp;
}t_selecao;
	
typedef struct _ihm
{
	CIhmConfig				Ihm;				// class ihm
	CIhmConfig				*IhmAux;			// class ihm auxiliar
  	CBotaoIhm				ButtonAux;			// class button auxiliar
	t_filtrosPH				Filtros;			// struct filtros
	t_b_filtrosPH			FiltrosAux;			// auxiliar para geracao de arquivo p/ tarefa
	t_b_filtrosPH			FiltrosAux2;		// auxiliar p/ salvar body original no caso de exportacao
	t_arqvar				Arq;
	PtWidget_t				*pListButton[MAX_BOTOES_TELA_IHM];
	PtWidget_t				*pListLabel[MAX_BOTOES_TELA_IHM];
	PtWidget_t				*pListMenu[MAX_BOTOES_LINHA_MENU];
	PtWidget_t				*pListStamp[7];
	PtWidget_t				*pListDays[MAX_DIAS_HIST];
	PtWidget_t				*pListGroups[MAX_GRUPOS_CUBAS];
	PtWidget_t				*pListAlgs[PH_MAX_ALG];
	PtWidget_t				*pListMem[11];
	PtWidget_t				*pFocusWidget;
	PtWidget_t				*pWidgetsHelp[PH_LINES_PAG_HELP];
	
	PtWidget_t				*pGrupo[PH_MAX_GRUPOS_CUBAS];
	PtWidget_t				*pCuba[MAX_CUBAS];
//	PtWidget_t				*pCuba[PH_MAX_CUBAS_GRUPO];
	PtWidget_t				*pWidAux;

	PtWidget_t				*pCallGetFocusTask1;
	PtWidget_t				*pCallGetFocusTask2;
	PtWidget_t				*pCallGetListValueTask[MAX_CALLBACKS_LISTVALUETASK];
	PtWidget_t				*pCallDoneTask;
	PtWidget_t				*pCallHelpTask;
	PtWidget_t				*pCallKeyboardTask;
	PtWidget_t				*pCallCancelTask;
    short int				PosGetListValueTask;
	
	t_selecao				selecao;	// todos widgets da pre-selecao
	
	PgColor_t				Cor[MAX_CUBAS];
	short int				FSinalCuba[MAX_CUBAS];
	short int				NumCuba[MAX_CUBAS];
	
	short int				ListButtonAux[MAX_BOTOES_TELA_IHM];
	short int				ListMenuAux[MAX_BOTOES_TELA_IHM];
	short int				GroupActual;
	short int				Screen;
	short int				Operador;			// aux get password
	short int				AnswerEDays;		// modal exclusao de dias
	short int				AnswerSel;			// modal pre-selecao
	short int				AnswerMem;			// modal memoria
	short int				AnswerMemSel;		// modal selecao memoria
	short int				AnswerTask;			// modal criacao tarefas
//	short int				AnswerListEv;		// modal lista de eventos
	short int				AnswerHelp;			// modal help
	short int				TimeOut;			// time out for operator
	short int				ContTimeOut;		// cont time out 
	short int				NumPotsGetPots;	// use get pots
	short int				NumLinesGetPots;	// use get pots
	short int				NumDaysExcDays;	// use get excluded days
	short int				MenuAnt;
	short int				PosLineHelp;
	short int				NumLineHelp;
	short int				AutoGrupoCuba;
	short int				GrupoCuba;
	short int				FGrupoCuba;
	short int				FScoreBd;
	short int				FExporta;
	short int				TelaExporta;
	short int				BotaoExporta;
	short int				IdentIHM;
	short int				MemNumero;
	short int				Selecao;
	short int				ArgConfirma;
	short int				TamIHM;
	int						My_nid;			// nid actual
	int						PidTarefa;			// pid task actual
	int						TempoVar;
	char					ArqFiltros[40];	// nome do arquivo de filtros
	char					NameHelpTask[80];
	char					*pLinha[PH_MAX_LINES_HELP];
	char					TextoCuba[10];
	char					NomeVar[60];
	char					NomeVar2[30];
	char					TextoTitulo[80];
	char					BitmapTask[80];
	InfoGets_t				InfoGets;
	RegEv_t					RegEv;
}t_ihm;

#endif

