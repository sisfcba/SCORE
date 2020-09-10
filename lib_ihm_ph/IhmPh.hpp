//*****************************************************************************
//
//		ATAN SISTEMAS DE AUTOMACAO LTDA
//		SCORE - SISTEMA DE CONTROLE DE REDUCOES
//
//	CLIENTE:	Programa de uso geral para todos clientes
//
//	PROJETO:	Programa de uso geral para todos projetos
//
//	CONTEUDO:	Programa de configuracao do Ihm Photon; configura todas chama-
//				das de tarefas, menus e dados relativos ao Ihm.
//
//	AUTOR:		Alexandre Mariz Bandeira de Morais
//
//	SISTEMA OPERACIONAL: QNX 4.25 - COMPILADOR: Watcom C++ v10.6
//
//	VERSAO:		1.0				DATA:	02/03/1999
//
//	HISTORICO DAS EDICOES:
//-----------------------------------------------------------------------------
//	           |                                                   |
//-----------------------------------------------------------------------------
//*****************************************************************************

#ifndef		_CONFIHM_HPP
  #define	_CONFIHM_HPP

#include <Definicao.h>
#include <Ph.h>
#include <Pt.h>

void	GetLoginPassword( short int & aOperador, short int & aNivel, PtWidget_t *apParent=NULL );
void 	BuildAlfaKeyboard( char *apLabel, PtWidget_t *apLine, short int aNCars, short int aSenha, PtWidget_t *apParent=NULL );
void	BuildGetPots( PtWidget_t *apLine1, PtWidget_t *apLine2, short int & aGroupGetPots,
					  short int aNumPotsGetPots, short int aNumLinesGetPots, PtWidget_t *apParent=NULL );
void	BuildGetPots2( char *apLine1, char *apLine2, short int & aGroupGetPots,
					  short int aNumPotsGetPots, short int aNumLinesGetPots, PtWidget_t *apParent=NULL );

//
//  **** Definicao das constantes ****
//
// Path do arquivo que contem o objeto CIhmConfig
//const char * const PH_ARQUIVO_IHM_CONFIG="/usr/score/config/ihm_configPH";
#define		PH_ARQUIVO_IHM_CONFIG	"/usr/score/config/ihm_configPH"
#define		PH_ARQUIVO_EXPORTA		"/usr/score/exporta_dados"

// Numero maximo de telas do ihm
const int MAX_TELAS_IHM=15;

// Numero maximo de botoes por tela do ihm
const int MAX_BOTOES_TELA_IHM=20;

// Numero maximo de botoes na linha de Menu
const int MAX_BOTOES_LINHA_MENU=8;

// Numero maximo de argumentos para uma tarefa
const int MAX_ARGS_TAREFA=12;

// button types
const int				BUTTON_DISABLE=-1;
const int				BUTTON_MENU=0;
const int				BUTTON_TASK=1;
const int				BUTTON_ACTION=2;
const int				BUTTON_STAMP=3;
const int				BUTTON_TASK_WEB=4;
const unsigned long 	NO_COLOR=Pg_GRAY;

// task args types
const int				ARG_NOT_INITIALIZED=1;
const int				ARG_POTS_SELECTION=2;
const int				ARG_POTS_STRING=3;
const int				ARG_POTS_KEYBOARD=4;
const int				ARG_ALGORITM=5;
const int				ARG_DATE_INITIAL=6;
const int				ARG_DATE_END=7;
const int				ARG_POTS_EXCLUDED=8;
const int				ARG_DAY_EXCLUDED=9;
const int				ARG_SHIFT=10;
const int				ARG_REDUCTION=11;
const int				ARG_OPERATOR=12;
const int				ARG_LIST=13;
const int				ARG_TEXT_STRING=14;
const int				ARG_TEXT_STRING_FIXED=15;
const int				ARG_TEXT_STRING_FIXED_HIDDEN=16;
const int				ARG_POTS_GROUP=17;
// ihm args types
const int				ARG_TITLE=102;
const int				ARG_CONFIRMS_QUESTION=103;
const int				ARG_HELP=104;

// type lists
const int				LIST_AUTO=0;
const int				LIST_EVENTS=1;

// type actions
const int				ACTION_SELECTION=1;
const int				ACTION_END_SYSTEM=2;

//
// strutura de argumentos para tarefa
//
typedef struct args_tar
{
	unsigned char	TipoArg;			// tipo do argumento ver Lista-1 abaixo
	short int		IndItem;			// indice p/ base de strings do nome do campo
	short int		IndDefault;			// indice p/ base de strings texto default
	char			Default[80];		// texto default p/ argumentos string, lista
	char			DefaultVal[80];		// valor default p/ argumentos string, lista
	unsigned char	ListaAuto;			// 0=lista on-line, 1=lista especial eventos
	unsigned char	NumTitulos;			// 1=default, 2=dois titulos
	short int		IndTit1Lista;		// indice p/ base de strings titulo 1 lista
	short int		IndTit2Lista;		// indice p/ base de strings titulo 2 lista
	short int		IndLista1;			// indice p/ base de strings lista 1
	short int		IndLista2;			// indice p/ base de strings lista 2
	char			Lista1[80];			// valores da lista 1
	char			Lista2[80];			// valores da lista 2
	unsigned char	NItensLista;		// numero de itens selecionaveis na lista 1=default
	char			reserva[30];		// reserva
} t_args_tar;

//
//  **** Declaracao das classes ****
//

//
// Classe CBotaoIhm - Classe do botao generico da ihm
//
class CBotaoIhm
{
  private:
	/********** variaveis default da classe botao ihm **************/
  	short int		cmIndTitulo;		// indice na base de dados de string para titulo
	unsigned long	cmCorTituloB;		// cor da base do titulo do botao
	unsigned long	cmCorTituloT;		// cor do texto do titulo do botao
  	short int		cmIndTexto;			// indice na base de dados de string para texto
	unsigned long	cmCorTextoB;		// cor da base do botao
	unsigned long	cmCorTextoT;		// cor do texto da base do botao
	short int		cmTipo;				// tipo do botao: -1=nao inic, 0=menu, 1=tarefa, 2=acao
	unsigned char	cmNivelSenha;		// nivel de acesso para este botao
	char			cmBitmap[80];		// path completo + nome do arquivo bmp
	
	/********** variaveis usadas apenas para o tipo acao *********/
  	short int		cmTipoAcao;			// 0=sair IHM, 1=rec ev, 2=rec todos ev
	
	/********** variaveis usadas apenas para o tipo menu *********/
  	short int		cmIndMenu;			// indice da tela de menu
	
	/********** variaveis usadas apenaso para o tipo tarefa *******/
  	int				cmTid;				// tid da tarefa criada
	unsigned char	cmGrava;			// flag de gravacao de args, 0=n~grava, 1=grava
	unsigned char	cmMostraArg;		// flag p/ mostrar args antes de criar tarefa, 0=n~mostra, 1=mostra
	unsigned char	cmAjuda;			// flag p/ habilitar help para a tarefa a ser criada
	unsigned char	cmPrio;				// prioridade de criacao da tarefa
	unsigned char	cmFCriacao;			// flags de criacao para tarefa
	unsigned char	cmNArgs;			// numero de argumentos para tarefa
	char			cmNome[80];			// path+nome da tarefa a ser criada
	
	unsigned char	cmExporta;			// flag se relatorio é exportável ou não
	unsigned char	cmAtivaExporta;		// flag p/ habilitar a exportacao automatica
	unsigned char	cmDiaExporta;		// dia da exportacao automática
	unsigned char	cmMemExporta;		// memoria da pre-selecao a ser utilizada na exportacao
	unsigned char	cmFlagExporta;		// flag para marcar que exportacao ja foi feita no dia
	
	char			reserva[25];		// reserva
//	char			reserva[26];		// reserva
//	char			reserva[30];		// reserva
	t_args_tar		cmArgs[MAX_ARGS_TAREFA];
  public:
	/********** metodos default da classe botao ihm **************/
    short int		IndTitulo() const				{ return cmIndTitulo; }
    void			IndTitulo(short int ind)		{ cmIndTitulo = ind; }
    unsigned long	CorTituloB() const				{ return cmCorTituloB; }
    void			CorTituloB(unsigned long cor)  	{ cmCorTituloB = cor; }
    unsigned long	CorTituloT() const				{ return cmCorTituloT; }
    void			CorTituloT(unsigned long cor)	{ cmCorTituloT = cor; }
    short int		IndTexto() const				{ return cmIndTexto; }
    void			IndTexto(short int ind)			{ cmIndTexto = ind; }
    unsigned long	CorTextoB() const				{ return cmCorTextoB; }
    void			CorTextoB(unsigned long cor)	{ cmCorTextoB = cor; }
    unsigned long	CorTextoT() const				{ return cmCorTextoT; }
    void			CorTextoT(unsigned long cor)	{ cmCorTextoT = cor; }
    short int		Tipo() const					{ return cmTipo; }
    void			Tipo(short int ind)				{ cmTipo = ind; }
    unsigned char	NivelSenha() const				{ return cmNivelSenha; }
    void			NivelSenha(unsigned char nivel) { cmNivelSenha = nivel; }
	const char *	Bitmap()						{ return cmBitmap; }
	void			Bitmap(char const *nome)		{ strncpy(cmBitmap,nome,sizeof(cmBitmap));
													  cmBitmap[sizeof(cmBitmap)-1]=0x00; }
	void			InitBotao()						{ InitDefault();
													  InitMenu();													  
													  InitAcao();													  
													  InitTarefa(); }
	void			InitDefault()					{ IndTitulo(-1);
													  IndTexto(-1);
													  Tipo(BUTTON_DISABLE);
													  CorTituloB(NO_COLOR);
													  CorTituloT(NO_COLOR);
													  CorTextoB(NO_COLOR);
													  CorTextoT(NO_COLOR);
													  NivelSenha(0);
													  Bitmap("\0"); }
	/********** metodos utilizados apenas para botao tipo acao **************/
    short int	TipoAcao() const					{ return cmTipoAcao; }
    void 		TipoAcao(short int tipo)			{ cmTipoAcao = tipo; }
	void		InitAcao()							{ TipoAcao(ACTION_SELECTION); }
	
	/********** metodos utilizados apenas para botao tipo menu **************/
    short int	IndMenu() const						{ return cmIndMenu; }
    void		IndMenu(short int menu)				{ cmIndMenu = menu; }
	void		InitMenu()							{ IndMenu(-1); }
	
	/********** metodos utilizados apenas para botao tipo tarefa **************/
    int				Tid() const							{ return cmTid; }
    void			Tid(int tid)						{ cmTid = tid; }
	unsigned char	Grava() const						{ return cmGrava; }
	void			Grava(unsigned char grava)			{ cmGrava = grava; }
	unsigned char	MostraArg() const					{ return cmMostraArg; }
	void			MostraArg(unsigned char mostra)		{ cmMostraArg = mostra; }
	unsigned char	Ajuda() const						{ return cmAjuda; }
	void			Ajuda(unsigned char ajuda)			{ cmAjuda = ajuda; }
	unsigned char	Prio() const						{ return cmPrio; }
	void			Prio(unsigned char prio)			{ cmPrio = prio; }
	unsigned char	FCriacao() const					{ return cmFCriacao; }
	void			FCriacao(unsigned char flags)		{ cmFCriacao = flags; }
	unsigned char	NArgs() const						{ return cmNArgs; }
	void			NArgs(unsigned char nargs)			{ cmNArgs = nargs; }
	const char *	Nome()								{ return cmNome; }
	void			Nome(char const *nome)				{ strncpy(cmNome,nome,sizeof(cmNome));
														  cmNome[sizeof(cmNome)-1]=0x00; }
														  
	unsigned char	Exporta() const						{ return cmExporta; }														  
	void			Exporta(unsigned char exporta)		{ cmExporta = exporta; }
	unsigned char	AtivaExporta() const				{ return cmAtivaExporta; }														  
	void			AtivaExporta(unsigned char ativae)	{ cmAtivaExporta = ativae; }
	unsigned char	DiaExporta() const					{ return cmDiaExporta; }														  
	void			DiaExporta(unsigned char diae)		{ cmDiaExporta = diae;
														  if(cmDiaExporta<1||cmDiaExporta>28)
														    cmDiaExporta=1; }
	unsigned char	MemExporta() const					{ return cmMemExporta; }														  
	void			MemExporta(unsigned char meme)		{ cmMemExporta = meme;
														  if(cmMemExporta<0||cmMemExporta>9)
														    cmMemExporta=0; }
	unsigned char	FlagExporta() const					{ return cmFlagExporta; }														  
	void			FlagExporta(unsigned char flage)	{ cmFlagExporta = flage; }
	
	void			InitTarefa()						{ InitTarefaCab();
													  	  short int i;
													  	  for(i=0;i<MAX_ARGS_TAREFA;++i)
													    	InitTarefaArg(i); }
	void			InitTarefaCab()						{ Tid(-1);
													  	  Grava(0);
													  	  MostraArg(0);
													  	  Ajuda(0);
													  	  Prio(10);
													  	  FCriacao(0);
													  	  NArgs(0);
													  	  Nome( "\0" );	}
	/********** metodos utilizados apenas para botao tipo tarefa argumentos **************/
	unsigned char	TipoArg(short int arg) const					{ return cmArgs[arg].TipoArg; }	
	void			TipoArg(short int arg, unsigned char tipo)		{ cmArgs[arg].TipoArg = tipo; }
	short int		IndItem(short int arg) const					{ return cmArgs[arg].IndItem; }
	void			IndItem(short int arg, short int ind )			{ cmArgs[arg].IndItem = ind; }
	short int		IndDefault(short int arg) const					{ return cmArgs[arg].IndDefault; }
	void			IndDefault(short int arg, short int ind )		{ cmArgs[arg].IndDefault = ind; }
	const char *	Default(short int arg)							{ return cmArgs[arg].Default; }
	void			Default(short int arg, char const *texto )		{ strncpy(cmArgs[arg].Default,texto,sizeof(cmArgs[arg].Default));
																  	  cmArgs[arg].Default[sizeof(cmArgs[arg].Default)-1]=0x00; }
	const char *	DefaultVal(short int arg)						{ return cmArgs[arg].DefaultVal; }
	void			DefaultVal(short int arg, char const *texto )	{ strncpy(cmArgs[arg].DefaultVal,texto,sizeof(cmArgs[arg].DefaultVal));
																  	  cmArgs[arg].DefaultVal[sizeof(cmArgs[arg].DefaultVal)-1]=0x00;	}
	unsigned char	ListaAuto(short int arg) const					{ return cmArgs[arg].ListaAuto; }	
	void			ListaAuto(short int arg, unsigned char lista)	{ cmArgs[arg].ListaAuto = lista; }
	unsigned char	NumTitulos(short int arg) const					{ return cmArgs[arg].NumTitulos; }	
	void			NumTitulos(short int arg, unsigned char num)	{ cmArgs[arg].NumTitulos = num; }
	short int		IndTit1Lista(short int arg) const				{ return cmArgs[arg].IndTit1Lista; }
	void			IndTit1Lista(short int arg, short int ind )		{ cmArgs[arg].IndTit1Lista = ind; }
	short int		IndTit2Lista(short int arg) const				{ return cmArgs[arg].IndTit2Lista; }
	void			IndTit2Lista(short int arg, short int ind )		{ cmArgs[arg].IndTit2Lista = ind; }
	short int		IndLista1(short int arg) const					{ return cmArgs[arg].IndLista1; }
	void			IndLista1(short int arg, short int ind )		{ cmArgs[arg].IndLista1 = ind; }
	short int		IndLista2(short int arg) const					{ return cmArgs[arg].IndLista2; }
	void			IndLista2(short int arg, short int ind )		{ cmArgs[arg].IndLista2 = ind; }
	const char *	Lista1(short int arg)							{ return cmArgs[arg].Lista1; }
	void			Lista1(short int arg, char const * lista )		{ strncpy(cmArgs[arg].Lista1,lista,sizeof(cmArgs[arg].Lista1));
																  	  cmArgs[arg].Lista1[sizeof(cmArgs[arg].Lista1)-1]=0x00;	}
	const char * 	Lista2(short int arg)							{ return cmArgs[arg].Lista2; }
	void			Lista2(short int arg, char const * lista )		{ strncpy(cmArgs[arg].Lista2,lista,sizeof(cmArgs[arg].Lista2));
																  	  cmArgs[arg].Lista2[sizeof(cmArgs[arg].Lista2)-1]=0x00;	}
	unsigned char	NItensLista(short int arg) const				{ return cmArgs[arg].NItensLista; }	
	void			NItensLista(short int arg, unsigned char itens)	{ cmArgs[arg].NItensLista = itens; }
	void			InitTarefaArg(short int arg)					{ TipoArg(arg,ARG_NOT_INITIALIZED);
			  														  IndItem(arg,-1);
			  														  IndDefault(arg,-1);
			  														  Default(arg,"\0");
			  														  DefaultVal(arg,"\0");
			  														  ListaAuto(arg,LIST_AUTO);
			  														  NumTitulos(arg,1);
			  														  IndTit1Lista(arg,-1);
			  														  IndTit2Lista(arg,-1);
			  														  IndLista1(arg,-1);
		  															  IndLista2(arg,-1);
			  														  Lista1(arg,"\0");
			  														  Lista2(arg,"\0");
			  														  NItensLista(arg,1); }
};

//
// Classe TelaIhm - Configuracao de uma tela da ihm
//
class CTelaIhm
{
  private:
    char				cmNomeTela[20];				// nome da tela
	short int			cmIndNomeTela;				// indice p/ base de strings p/ nome tela
	unsigned long		cmCorBase;					// cor da base da tela
  public:
  	CBotaoIhm			Botao[MAX_BOTOES_TELA_IHM];	// configuracao dos botoes da tela
	const char *		NomeTela()					{ return cmNomeTela; }
	void				NomeTela(char const *nome)	{ strncpy(cmNomeTela,nome,sizeof(cmNomeTela));
													  cmNomeTela[sizeof(cmNomeTela)-1]=0x00; }
    short int			IndNomeTela() const			{ return cmIndNomeTela; }
    void				IndNomeTela(short int ind)	{ cmIndNomeTela = ind; }
    unsigned long		CorBase() const				{ return cmCorBase; }
    void				CorBase(unsigned long cor)  { cmCorBase = cor; }
	void				InitTela()					{ short int i;
													  IndNomeTela(-1);
													  CorBase(NO_COLOR);
													  NomeTela("\0");
	    											  for(i=0;i<MAX_BOTOES_TELA_IHM;++i)
	      												Botao[i].InitBotao(); }
	short int			Vazia()						{ if( *NomeTela() == 0x00 )
														return 1; return 0; }
};

//
// Classe TelaSelo - Configuracao da tela selo do sistema
//
class CTelaSelo
{
  private:
	char			cmClienteBMP[80];			// path completo + nome do bmp p/ cliente
	char			cmAtanBMP[80];				// path completo + nome do bmp p/ atan
	short int		cmIndTexto1;				// ind. base de strings p/ nome sistema
	short int		cmIndTexto2;				// ind. base de strings p/ versao sistema
	short int		cmIndTexto3;				// ind. base de strings p/ nome do cliente
	unsigned long	cmCorBase;					// cor base da tela selo
	unsigned long	cmCorTexto1;				// cor texto1 da tela selo
	unsigned long	cmCorTexto2;				// cor texto2 da tela selo
	unsigned long	cmCorTexto3;				// cor texto3 da tela selo
  public:
	const char *	ClienteBMP()					{ return cmClienteBMP; }
	void			ClienteBMP(char const *nome)	{ strncpy(cmClienteBMP,nome,sizeof(cmClienteBMP));
												  	  cmClienteBMP[sizeof(cmClienteBMP)-1]=0x00; }
	const char *	AtanBMP()						{ return cmAtanBMP; }
	void			AtanBMP(char const *nome)		{ strncpy(cmAtanBMP,nome,sizeof(cmAtanBMP));
												  	  cmAtanBMP[sizeof(cmAtanBMP)-1]=0x00; }
    short int		IndTexto1() const				{ return cmIndTexto1; }
    void			IndTexto1(short int ind)		{ cmIndTexto1 = ind; }
    short int		IndTexto2() const				{ return cmIndTexto2; }
    void			IndTexto2(short int ind)		{ cmIndTexto2 = ind; }
    short int		IndTexto3() const				{ return cmIndTexto3; }
    void			IndTexto3(short int ind)		{ cmIndTexto3 = ind; }
    unsigned long	CorBase() const					{ return cmCorBase; }
    void			CorBase(unsigned long cor)  	{ cmCorBase = cor; }
    unsigned long	CorTexto1() const				{ return cmCorTexto1; }
    void			CorTexto1(unsigned long cor)	{ cmCorTexto1 = cor; }
    unsigned long	CorTexto2() const				{ return cmCorTexto2; }
    void			CorTexto2(unsigned long cor)	{ cmCorTexto2 = cor; }
    unsigned long	CorTexto3() const				{ return cmCorTexto3; }
    void			CorTexto3(unsigned long cor)	{ cmCorTexto3 = cor; }
	void			InitSelo()						{ ClienteBMP("\0");
													  AtanBMP("\0");
													  IndTexto1(-1);
													  IndTexto2(-1);
													  IndTexto3(-1);
													  CorBase(NO_COLOR);
													  CorTexto1(NO_COLOR);
													  CorTexto2(NO_COLOR);
													  CorTexto3(NO_COLOR); }
};

//
// Classe IhmConfig - Contem a configuracao do ihm do Score
//
class CIhmConfig
{
  private:
	unsigned long	cmCorTituloB;						// cor da base do titulo
	unsigned long	cmCorTituloT;						// cor do texto do titulo
  public:
  	CTelaIhm		Telas[MAX_TELAS_IHM];				// configuracao das telas do ihm
	CBotaoIhm		MenuBotao[MAX_BOTOES_LINHA_MENU];	// configuracao da linha de menu
	CTelaSelo		TelaSelo;							// configuracao da tela selo
    CIhmConfig();
	void			GravaBotaoIhm(int tela, int bt, int aReducao);
	void			GravaIhm(int aReducao);
	void			GravaIhm2(char *aNome);
	void			LeIhm(int aReducao);
	void			LeIhm2(char *aNome);
    unsigned long	CorTituloB() const				{ return cmCorTituloB; }
    void			CorTituloB(unsigned long cor)  	{ cmCorTituloB = cor; }
    unsigned long	CorTituloT() const				{ return cmCorTituloT; }
    void			CorTituloT(unsigned long cor)  	{ cmCorTituloT = cor; }
	short int		AchaTelaVazia()					{ short int tela;
													  for(tela=0;tela<MAX_TELAS_IHM;++tela)
														if(Telas[tela].Vazia())
														  return tela; return -1; }
	void			InitMenuBotao()					{ short int i;														  
	  												  for(i=0;i<MAX_BOTOES_LINHA_MENU;++i)	
	    												MenuBotao[i].InitBotao(); }
	void			InitGeral()						{ short int i;
													  CorTituloB(NO_COLOR);
													  CorTituloT(NO_COLOR);
	  												  for(i=0;i<MAX_TELAS_IHM;++i)	
	    												Telas[i].InitTela();
													  TelaSelo.InitSelo();
													  InitMenuBotao(); }
};

//
//  **** Declaracao dos prototipos ****
//

#endif		/* _CONFIHM_HPP */
