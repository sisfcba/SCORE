/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.40

	PROJETO  : Todos
	
	SISTEMA  : Todos
	
	ARQUIVO  : RelGraf.h

	CONTEUDO : Contem as definicoes de todas as tabelas e constantes
			   especificas dos relatorios graficos de cuba e linha.
			   Possui as definicoes das estruturas de dados da
			   base de dados em area comum de memoria que conteem as
			   configuracoes e os valores usados pelos relatorios.

	AUTOR    : Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO   : 1.0		  -	  DATA  : 01/11/94

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
01/11/94 | Edicao Inicial                                       | Leonel
-------------------------------------------------------------------------------
******************************************************************************/
/*********************************** Revisoes ********************************\
$Id: RelGraf.h,v 1.14.4.1 2012/09/28 17:09:16 leo Exp $

$Log: RelGraf.h,v $
Revision 1.14.4.1  2012/09/28 17:09:16  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

Revision 1.14  2008/10/14 14:01:30  alex
variavel de referencia para limites do grafico de cuba e linha

Revision 1.13  2007/03/01 18:08:43  alex
aumentado valrelgraf para 8 dias

Revision 1.12  2005/10/06 18:55:48  alex
colocado FATOR_COMPACTA nos prologos


Revision 1.11  2005/05/31 19:37:32  leo
Correcoes feitas durante primeira pre-operacao CBA sala 125kA VI

Revision 1.10  2005/03/08 18:44:45  alex
compatibilizacao com albras

Revision 1.9.2.3  2005/02/10 17:45:44  alex
correcoes p/ algoritimo de 1 minuto

Revision 1.9.2.2  2005/01/10 15:08:08  alex
alterado base de tempo p/ 1 minuto

Revision 1.9.2.1  2004/12/21 13:38:04  leo
Alteracoes durante pre-operacao sala II Albras

Revision 1.9  2004/07/02 19:59:41  alex
novo relatorio RelCuba 36 cubas

Revision 1.8  2004/06/15 19:39:39  alex
batida do MCC nos graficos de cuba e linha

Revision 1.7  2004/04/05 18:23:19  alex
correcoes na interface 1024x768

Revision 1.6  2003/11/06 13:24:24  alex
colocado configuracao de dial no grafico de linha

Revision 1.5  2003/09/16 13:44:36  alex
novo grafico de alarmes relcuba

Revision 1.4  2003/06/18 19:54:33  alex
nova interface 1024x768

Revision 1.3  2003/03/13 18:30:34  alex
Implementacao da interface 1024x768

\*********************************** Revisoes ********************************/

#ifndef		_RELGRAF_H

#define		_RELGRAF_H

#include <Definicao.h>
#include <ScoreConst.h>
#include <Eventos.h>

/*
-------------------------------------------------------------------------------
							Constantes
-------------------------------------------------------------------------------
*/
#define	 TEMPO_INICIAL			5e8L	/* tempo (nsec) 0.5s timer inicial */
#define	 TEMPO_RELCUBA			5e8L	/* tempo (nsec) 0.5s timer RelCuba */
#define  TEMPO_ATUALCUBA		120L	/* tempo (sec) 2.0min timer AtualCuba */
#define  TEMPO_ATUALEVCUBA	10L		/* tempo (sec) 10.0s timer AtualEvCuba */

#define  MAX_GRAF_REL_CUBA		3		/* Num. de graficos por relatorio de cuba */
#define  MAX_GRAF_REL_LINHA		1		/* Num. de graficos por relatorio de linha */
#define  MAX_GRAF_CUBA			6		/* Num. de graficos relatorio de 6 cubas */
#define  MAX_GRAF_CUBA_36		36		/* Num. de graficos relatorio de 36 cubas */
#define	 MAX_TAM_TAG_PENA		20		/* Tag para o grafico mais terminador */
#define	 MAX_TAM_TAG_ALA		20		/* Tag para tela de alarme mais terminador */
#define	 MAX_PENAS_GRAF			2		/* Num. de penas em um grafico de cuba */
#define	 MAX_PENAS_GRAF_LINHA	4		/* Num. de penas em um grafico de linha */
#define	 MAX_VAL_GRAF			300		/* Num. maximo de pontos no grafico 640x480 */
#define	 MAX_VAL_GRAF2			500		/* Num. maximo de pontos no grafico 1024x768 */
#define	 MAX_VAL_GRAF_BUF		6000	// 1500	/* Num. maximo de pontos no buffer */
#define	 MAX_VAL_GRAF_MINI2		200		/* Num. maximo de pontos no buffer e grafico p/ mini 1024x768 */
#define	 MAX_VAL_GRAF_MINI		MAX_VAL_GRAF_MINI2	/*100*/		/* Num. maximo de pontos no buffer e grafico p/ mini 640x480 */
#define  MAX_CURSOR_MOVE		30		/* Quantidade de pontos que o cursor move rapido 640x480 */
#define  MAX_CURSOR_MOVE2		50		/* Quantidade de pontos que o cursor move rapido 1024x768 */

#define  MAX_VAL_ALA_BUF		((MAX_VAL_GRAF_BUF/8)+1) /* tamanho maximo do vetor em bytes 1 bit por variavel */
#define	 MAX_PENAS_ALARME		8		/* numero maximo de penas de alarme CUIDADO PARA MUDAR !!!! */

#define	 MAX_FAIXAS_ALARME	10	/* Num. de faixas de alarme */

#define	 MAX_VAR_ALARME		20	/* Num. max. de variaveis associadas a um
								   botao de alarme */
#define	 MAX_EV_CUBA		1400	// 200	/* Num. max. de eventos por cuba */

/* -- Definicoes para os tipos de variaveis para configuracao -- */
#define	 T_SHORT_INT	0
#define	 T_INTEIRO		1
#define	 T_FLOAT		2
#define	 T_LONG			3
#define	 T_DOUBLE		4
#define	 T_BYTE			5

/* -- Nomes para abertura das memorias compartilhadas -- */
#define	 NOME_SHM_CNFRELGRAF	"Atan/Score/CnfRelGraf"
#define	 NOME_SHM_VALRELGRAF	"Atan/Score/ValRelGraf"
#define	 NOME_SHM_VALGRAFMINI	"Atan/Score/ValGrafMini"
#define	 NOME_SHM_EVCUBA		"Atan/Score/EvCuba"

/* -- Nome dos arquivos de configuracao (atualizado) e de valores (apenas p/
		inicializacao) -- */
#define  ARQUIVO_CNFRELGRAF		"/score/base_dados/cnfrelgraf"
#define  ARQUIVO_VALRELGRAF		"/score/base_dados/valrelgraf"
#define  ARQUIVO_VALGRAFMINI	"/score/base_dados/valgrafmini"
#define  ARQUIVO_EVCUBA			"/score/base_dados/evcuba"

/*
-------------------------------------------------------------------------------
						   Macros
-------------------------------------------------------------------------------
*/
#define  CNF_ALA					PCnfRelGraf->CnfAlarmeCubas
#define  CNF_GRAF_CUBA(cuba,graf,pena) \
						PCnfRelGraf->CnfGrafCuba[cuba].Graf[graf].Pena[pena]
#define  CNF_GRAF_CUBA_ALA(cuba,pena) \
						PCnfRelGraf->CnfGrafCubaAla[cuba].Pena[pena]
#define  CNF_GRAF_LINHA(pena)		PCnfRelGraf->CnfGrafLinha.Pena[pena]
#define  CNF_GRAF_LINHA_ALA(pena)	PCnfRelGraf->CnfGrafLinhaAla.Pena[pena]
#define  VAL_GRAF_CUBA(cuba)		PValRelGraf->GrafCuba[cuba]
#define  VAL_GRAF_MINI(cuba)		PValGrafMini->GrafCuba[cuba]
#define  VAL_GRAF_LINHA				PValRelGraf->GrafLinha

/*
-------------------------------------------------------------------------------
						   Tipos de dados
-------------------------------------------------------------------------------
*/
/* ********************* Tabelas de configuracao ***************************
   *************** dos relatorio graficos de cuba/linha ******************** */

/* -- Tabela de configuracao das variaveis de alarme -- */
typedef
  volatile struct cnf_var_alarme
  {
	short int	 Tabela;		/* -- Tabela onde se encontra a variavel -- */
	unsigned int OffsetVar;	/* -- Offset em bytes da variavel dentro do 
				registro da tabela (para tabelas c/ mais de um registro) -- */
    char TagVar[MAX_TAM_TAG_ALA];
	short int	 ValorNormal; /* -- Valor para estado normal -- */
	struct est_alarme
	{
	  short int	ValorFaixa;	/* -- Valor da variavel ... -- */
	  short int	Faixa;		/* -- .. para a faixa indicada -- */
	} EstAlarme[MAX_FAIXAS_ALARME];
	unsigned	Alg;		/* -- algoritmo -- */
	short int	FGrafAla;
	short int	Reserva[1];
//	short int	Reserva[2];
  } t_cnf_var_alarme;

/* -- Tabela de configuracao do relatorio grafico de alarmes de cubas/linha -- */
typedef
  volatile struct cnf_rel_alarme
  {
	/* -- Definicao das cores para cada faixa -- */
	unsigned		 CorNormalL;
	unsigned		 CorNormalNRecL;	/* -- normal nao reconhecido -- */
	unsigned		 CorFaixasAlarmeL[MAX_FAIXAS_ALARME];
	/* -- Descricao das variaveis de alarme de linha -- */
	short int		 LinhaNumVarAlar; /* -- num. de variaveis conf. p/ alarme de linha */
	t_cnf_var_alarme VarAlaLinha[MAX_VAR_ALARME];
	/* -- Definicao das cores para cada faixa -- */
	unsigned		 CorNormalC;
	unsigned		 CorNormalNRecC;	/* -- normal nao reconhecido -- */
	unsigned		 CorFaixasAlarmeC[MAX_FAIXAS_ALARME];
	/* -- Descricao das variaveis de alarme de cuba (igual para todas) -- */
	short int		 CubaNumVarAlar; /* -- num. de variaveis conf. p/ alarme de cuba */
	t_cnf_var_alarme VarAlaCuba[MAX_VAR_ALARME];
	short int		 Reserva[30];
  } t_cnf_alarme;

/* -- Tabela de configuracao de uma pena do grafico -- */
typedef
  volatile struct cnf_graf_pena
  {
	short int		Tabela;	/* -- Tabela a qual pertence a variavel desta pena -- */
	unsigned int	OffsetVar; /* -- Offset em bytes da variavel dentro da tabela -- */
	float			FatConv; /* -- Fator de conversao a multiplicar no valor p/ exibicao -- */
	short int		TipoVar; /* -- Tipo da variavel (int, short, float etc) -- */
	char			TagPena[MAX_TAM_TAG_PENA]; /* -- Tag para aparecer no grafico -- */
	float			LimInf;	/* -- Limite inferior da variavel p/ o grafico -- */
	float			LimSup; /* -- Limite superior da variavel p/ o grafico -- */
	unsigned		CorPena; /* -- Cor a ser utilizada para esta pena -- */
  } t_cnf_pena;

/* -- Tabela de configuracao de um grafico com MAX_PENAS_GRAF penas -- */
typedef
  volatile struct cnf_graf
  {
	t_cnf_pena		Pena[MAX_PENAS_GRAF_LINHA];
	t_cnf_pena		Ref;
  } t_cnf_graf;

/* -- Tabela de configuracao de um grafico com MAX_PENAS_GRAF penas -- */
typedef
  volatile struct cnf_graf_c
  {
	t_cnf_pena		Pena[MAX_PENAS_GRAF];
	t_cnf_pena		Ref;
  } t_cnf_graf_c;

/* -- Tabela de configuracao de um grafico com MAX_PENAS_GRAF penas -- */
typedef
  volatile struct cnf_graf_ala
  {
	t_cnf_pena		Pena[MAX_PENAS_ALARME];
  } t_cnf_graf_ala;

/* -- Tabela de configuracao do relatorio de cubas (3 graficos) -- */
typedef
  volatile struct cnf_graf_cuba
  {
	t_cnf_graf_c	Graf[MAX_GRAF_REL_CUBA];
  } t_cnf_graf_cuba;

/* -- Tabela de configuracao do dial do grafico de linha -- */
typedef
  volatile struct cnf_dial
  {
	t_cnf_pena		PenaDial1[2];
	t_cnf_pena		FaixaDial1[2];
	t_cnf_pena		PenaDial2[2];
	t_cnf_pena		FaixaDial2[2];
  } t_cnf_dial;

/* ************** Tabela de configuracao dos relatorios graficos *********** */
/* -- Tabela que contem todas as tabelas de configuracao de rel. graficos -- */
typedef
  volatile struct rel_graficos
  {
	/* -- Tabelas validas para toda a linha -- */
	/* -- Base de tempo para amostragem em multiplos do ciclo de controle -- */
	short int		BaseTLinha;	/* -- Grafico de linha -- */
	short int		BaseTCubas;	/* -- Graficos de cuba (mesma base de tempo) -- */
    unsigned        CorFundoLinha;
    unsigned        CorFundoCuba;
    unsigned        CorGradeLinha;
    unsigned        CorGradeCuba;
	unsigned		CorFaixa1Dial1;
	unsigned		CorFaixa2Dial1;
	unsigned		CorFaixa3Dial1;
	unsigned		CorFaixa1Dial2;
	unsigned		CorFaixa2Dial2;
	unsigned		CorFaixa3Dial2;
	/* -- Tab. de config. do relatorio grafico de alarmes de cubas/linha -- */
	t_cnf_alarme	CnfAlarmeCubas;
	/* -- Tab. de config. do relatorio grafico de linha -- */
	t_cnf_graf		CnfGrafLinha;
	t_cnf_dial		CnfGrafLinhaDial;
	t_cnf_graf_ala	CnfGrafLinhaAla;
	/* -- Tabelas de cubas -- */
	/* -- Tab. de config. do relatorio grafico de cuba -- */
	t_cnf_graf_cuba	CnfGrafCuba[MAX_CUBAS];
	t_cnf_graf_ala	CnfGrafCubaAla[MAX_CUBAS];
  } t_cnf_rel_graf;

/* ************ Tabelas com os valores amostrados das variaveis ************ */
/* -- Estrutura dos valores para uma pena do grafico -- */
typedef
  volatile struct val_pena
  {
	float	Valor[MAX_VAL_GRAF_BUF];
  } t_val_pena;

/* -- Estrutura dos valores para uma pena do grafico de alarmes -- */
typedef
  volatile struct val_pena_ala
  {
	byte	Valor[MAX_VAL_ALA_BUF];
  } t_val_pena_ala;

/* -- Estrutura dos valores para uma pena do grafico -- */
typedef
  volatile struct pena_mini
  {
	float	Valor[MAX_VAL_GRAF_MINI];
  } t_pena_mini;
  
/* -- Estrutura dos valores para um grafico -- */
typedef
  volatile struct graf
  {
	t_val_pena	Pena[MAX_PENAS_GRAF_LINHA]; /* -- Buffer por pena, usam mesmo indice
											e flag -- */
  } t_graf;

/* -- Estrutura dos valores para um grafico -- */
typedef
  volatile struct graf_c
  {
	t_val_pena	Pena[MAX_PENAS_GRAF]; /* -- Buffer por pena, usam mesmo indice
											e flag -- */
  } t_graf_c;
  
/* -- Estrutura dos valores para um grafico de alarmes -- */
typedef
  volatile struct graf_ala
  {
	t_val_pena_ala	Pena[MAX_PENAS_ALARME]; /* -- Buffer por pena, usam mesmo indice
											e flag -- */
  } t_graf_ala;

/* -- Estrutura dos valores para um grafico mini -- */
typedef
  volatile struct mini
  {
	t_pena_mini	Pena[MAX_PENAS_GRAF]; /* -- Buffer por pena, usam mesmo indice
											e flag -- */
  } t_mini;

/* -- Tabela do grafico de linha -- */
typedef
  volatile struct val_graf_linha
  {
    /* atencao: colocar outros campos somente depois do IndFim !!!!! */
	time_t		HoraUltAmostra;	/* -- Data e hora da ultima amostra -- */
	byte		BufCheio;	/* -- Indica se ja' circulou o buffer -- */
	short int	IndFim;		/* -- Indice para proxima posicao livre
								(qdo. circulou -> igual ao inicio) -- */
	t_graf		Valores;	/* -- Grafico de linha -- */
	t_graf_ala	ValAla;		/* -- Grafico de alarmes -- */
  } t_val_graf_linha;

/* -- Tabela dos graficos por cuba -- */
typedef
  volatile struct val_graf
  {
    /* atencao: colocar outros campos somente depois do IndFim !!!!! */
	time_t		HoraUltAmostra;	/* -- Data e hora da ultima amostra -- */
	byte		BufCheio;	/* -- Indica se ja' circulou o buffer -- */
	short int	IndFim;		/* -- Indice para proxima posicao livre
								(qdo. circulou -> igual ao inicio) -- */
	t_graf_c	Valores[MAX_GRAF_REL_CUBA]; /* -- Graficos por cuba -- */
	t_graf_ala	ValAla;		/* -- Grafico de alarmes -- */
  } t_val_graf_cuba;
  
/* -- Tabela dos mini graficos por cuba -- */
typedef
  volatile struct graf_mini
  {
    /* atencao: colocar outros campos somente depois do IndFim !!!!! */
	time_t		HoraUltAmostra;	/* -- Data e hora da ultima amostra -- */
	byte		BufCheio;	/* -- Indica se ja' circulou o buffer -- */
	short int	IndFim;		/* -- Indice para proxima posicao livre
								(qdo. circulou -> igual ao inicio) -- */
	t_mini		Valores[MAX_GRAF_REL_CUBA]; /* -- Graficos por cuba -- */
  } t_val_cuba_mini;

/* -- Tabela das batidas do MCC -- */
typedef
  volatile struct graf_time
  {
	short int	IndTime;
	time_t		Time[MAX_VAL_GRAF_BUF];
  } t_graf_time;

/* -- Tabela que contem todas as tabelas de valores dos graficos por cuba  e linha -- */
typedef
  volatile struct val_rel
  {
	/* -- Hora da batida do MCC -- */
	t_graf_time			GrafTime;
	/* -- Valores do grafico de linha (apenas 1 grafico) -- */
	t_val_graf_linha	GrafLinha; /* -- Grafico de linha -- */
	/* -- Valores dos graficos de cuba (3 por cuba) -- */
	t_val_graf_cuba		GrafCuba[MAX_CUBAS]; /* -- Graficos por cuba -- */
  } t_val_rel_graf;

/* -- Tabela que contem todas as tabelas de valores dos mini graficos por cuba -- */
typedef
  volatile struct val_mini
  {
	t_val_cuba_mini	GrafCuba[MAX_CUBAS]; /* -- Graficos por cuba -- */
  } t_val_graf_mini;
  
/* -- Tabela de cabecalho para arq. -- */
typedef
  volatile struct val_cab_arq
  {
	time_t		HoraUltAmostra;	/* -- Data e hora da ultima amostra -- */
	byte		BufCheio;		/* -- Indica se ja' circulou o buffer -- */
	short int	IndFim;			/* -- Indice para proxima posicao livre
									(qdo. circulou -> igual ao inicio) -- */
  } t_val_cab_arq;

/* -- Tabela do grafico de linha para arq. -- */
typedef
  volatile struct val_graf_linha_arq
  {
	float	Valor[MAX_PENAS_GRAF_LINHA];
	byte	ValorAla; /* CUIDADO!! AQUI ESTA CASADO COM MAX_PENAS_ALARME (8) OU SEJA 1 BIT POR VARIAVEL */
  } t_val_graf_linha_arq;

/* -- Tabela dos graficos por cuba para arq.-- */
typedef
  volatile struct cuba_val_graf_arq
  {
    float	Valor[MAX_GRAF_REL_CUBA * MAX_PENAS_GRAF];
	byte	ValorAla; /* CUIDADO!! AQUI ESTA CASADO COM MAX_PENAS_ALARME (8) OU SEJA 1 BIT POR VARIAVEL */
  } t_cuba_val_graf_arq;

/* -- Tabela dos graficos por cuba para arq.-- */
typedef
  volatile struct val_graf_arq
  {
	t_cuba_val_graf_arq Cuba[MAX_CUBAS];
  } t_val_graf_cuba_arq;

/* -- Tabela que contem todas as tabelas de valores dos graficos por registro -- */
typedef
  volatile struct val_rel_arq
  {
	/* -- Hora da batida do MCC -- */
	t_graf_time					GrafTime;
	/* -- Valores do grafico de linha (apenas 1 grafico) -- */
	t_val_cab_arq				CabLinha;
 	t_val_graf_linha_arq		RegLinha[MAX_VAL_GRAF_BUF]; /* -- Grafico de linha por reg. -- */
	/* -- Valores dos graficos de cuba (3 por cuba) -- */
	t_val_cab_arq				CabCuba[MAX_CUBAS];
	t_val_graf_cuba_arq			RegCuba[MAX_VAL_GRAF_BUF];  /* -- Graficos de cuba por reg. -- */
  } t_val_rel_graf_arq;

/*-- Tabela de eventos de cubas e linha --*/
typedef
  struct  CabBufEvCubas
  { 
    t_cab_msg_ev Cab;
    t_rec_ev	 Buf[MAX_EV_CUBA];
  } t_cab_buf_ev;

/*-- Tabela de eventos de cubas e linha --*/
typedef
  struct  TabEvCubas
  { 
    t_cab_buf_ev	Cuba[MAX_CUBAS];
	t_cab_buf_ev	Linha;
  } t_ev_cuba;

/*-- Tabela de valores e eventos de cubas --*/
typedef
  volatile struct ValEvCuba
  {
    char            	Data[9];
	t_cnf_graf_cuba		Cnf;
	t_val_graf_cuba		Val;
    t_cab_buf_ev		Ev;
  } t_val_ev_cuba;

/*-- Tabela de valores e eventos de Linha --*/
typedef
  volatile struct ValEvLinha
  {
    char           		Data[9];
	t_cnf_graf			Cnf;
	t_val_graf_linha	Val;
    t_cab_buf_ev		Ev;
  } t_val_ev_linha;

/*
-------------------------------------------------------------------------------
					   Ponteiros para as tabelas globais
-------------------------------------------------------------------------------
*/
/* -- Apontador para a tabela de configuracao para os relatorios graficos de
	  cuba e de linha (PCnfRelGraf) -- */
DECL t_cnf_rel_graf		*PCnfRelGraf;

/* -- Apontador para a tabela de valores para os relatorios graficos de cuba
	  e de linha (PValRelGraf) -- */
DECL t_val_rel_graf		*PValRelGraf; // apontador para memoria

/* -- Apontador para a tabela de valores para mini graficos de Cuba -- */
DECL t_val_graf_mini	*PValGrafMini;

/* -- Apontador para a tabela de valores para graficos de Cuba -- */
DECL t_val_rel_graf_arq	*PValRelGrafArq; // apontador para arquivo

/* -- Apontador para a tabela de eventos por cuba -- */
DECL t_ev_cuba			*PEvCuba;

#endif

/* -- fim do arquivo RelGraf.h -- */
