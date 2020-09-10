/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.1

	PROJETO		: CBA - Companhia Brasileira de Aluminio SA

	SISTEMA		: SALAS 120KA II e III

	ARQUIVO		: McpPF.h

	CONTEUDO	: Prologo do Modulo McpPF.c
                  Contem as constantes e tipos de dados do modulo.

	AUTOR		: Ricardo Teixeira Leite Mourao / Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	02/01/97

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
Data     | Descricao                                            | Autor 
-------------------------------------------------------------------------------
02/01/97 | Edicao inicial                                       | Ricardo-Leonel
-------------------------------------------------------------------------------
******************************************************************************/
/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/

#include	<AlimentCBA.h>
#include    <PFRot.h>
#include	<Eventos.h>
#include	<Prototipos.h>


/*
-------------------------------------------------------------------------------
                           Defines
-------------------------------------------------------------------------------
*/

/*-- Estados da chave automatico/manual --*/
#define ALIMENTACAO_AUTO	 0
#define ALIMENTACAO_MANUAL	 1

#define	SINC_CONTRL			 60	 /* 30 segundos apos ativacao do MCC */

#define NUM_DERIV_RES        5   /* Cinco derivadas p/ calculo da concentracao pela derivada */
#define TAM_BUF_RES          4   /* Numero de pontos de resistencia usados no calculo da concentracao */

/* -- Definicoes do filtro de resistencia de alimentacao -- */
#define B0 4.985456492079266e-012
#define B1 2.492761552730372e-011
#define B2 4.985345469776803e-011
#define B3 4.985523105460743e-011
#define B4 2.492583917046432e-011
#define B5 4.985678536684191e-012

#define A0 -4.964344114211365
#define A1	9.858011301243086
#define A2 -9.787962243876970
#define A3	4.859267088123280
#define A4 -0.964972031118499

#define T_ESTAB_FILT  720        /* Tempo de estabilizacao do filtro (segundos) */


/*
-------------------------------------------------------------------------------
                              Macros
-------------------------------------------------------------------------------
*/
#define TRAPEZIO(B_MAIOR,B_MENOR,ALT) ((((B_MAIOR)+(B_MENOR))*(ALT))/2.0)


/*
-------------------------------------------------------------------------------
                           Tipos de dados
-------------------------------------------------------------------------------
*/
#ifdef USA_AVC_LOC
typedef
  struct avcloc
  {  
    byte  HabilitaPFAnt;            // estado anterior do flag HabilitaPF
	float IntPar;		            // integral parcial
    float Consumo;                  // acumula o consumo de alumina entre amostras de resistencia (derivada)
    float alvo;                     // massa alvo de alumina (controla tempo de under/over)
    float Resistencia[TAM_BUF_RES]; // buffer circular p/ armazenar valores da resistencia (derivada)
    short int ResIndex;             // usado como indice do buffer circular
    byte  Preenchido;				// flag que indica que buffer de resistencias esta preenchido
    float Conc[NUM_DERIV_RES];      // concentracoes referentes a cada uma das derivadas obtidas
    float ConcDer;                  // concentracao da cuba calculada pela derivada
    float Deriv[NUM_DERIV_RES];     // derivadas coletadas para o calculo da concentracao
    short int DerIndex;             // usado como indice do vetor de derivadas
    float UnderProg;                // valor do underfeed progressivo
    long  IniEtapaUnder;            // inicio da etapa de underfeed (underfeed progressivo)
#ifdef FILTRO_ALIM_BUTTER
    double res_inst[6];             // vetor com as ultimas resistencias instantaneas (usado no filtro)
    double res_filt[5];             // vetor com as ultimas resistencias filtradas (usado no filtro) 
#else
    double ResFilt;
#endif
    float DerResAlimAnt;            // derivada de alimentacao anterior 
	byte  ConcBaixa;                //flag que indica se entrou em overfeed devido aa derivada muito alta
  } t_avc_loc;
#endif

/*
-------------------------------------------------------------------------------
                           Variaveis Locais
-------------------------------------------------------------------------------
*/
/* -- Contem a hora atual em segundos -- */
DECL	long	HoraAtualSec;
/* -- Contem a hora da partida da tarefa McpPF em segundos -- */
DECL	long	HoraPartidaMcpPF;
/* -- Faixa de cubas a tratar -- */
DECL	int		CubaIni,CubaFim;
/* Linha ja' ativada apos partida a frio */
DECL	int		LinhaAtiva;
/* Controle sincronizado com MCC */
DECL	int		ControleAtivo;
/* Hora da partida do sistema */
DECL	time_t	HoraPartida;
/* -- Intervalo (em segundos) entre ciclos de leitura -- */
DECL	float	IntervLeit;
/* -- Valor da Corrente da linha no ultimo Ciclo de Leitura -- */
DECL	float	IinstOld;
// Inserido em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
/* -- Marca desligamento da linha -- */
DECL	t_boolean	LinhaDesligada;


/*
-------------------------------------------------------------------------------
                           Prototipos
-------------------------------------------------------------------------------
*/
void		IniMcpPF(void);
void		IniMcpPFHot(void);
void		ProcessaCubas(int NumCicLeit);
t_boolean	ConsisteArgs(int Argc,char *Argv[]);
int			AlimPadrao(int cuba);
int			AlimEA(int cuba);
int			AlimExcecao(int cuba);
int			AlimSuspensa(int cuba);
void        SupervPF(int cuba);
void        TrataAcionaPF(int cuba);
byte		AcionaPF(int Cuba);
byte		AcionaPFCBA(int Cuba);
int			Prox_Estado(int Cuba, int EstadoAtual);
void		AcionaFluoreto(int Cuba);

/* -- Fim do arquivo McpPF.h -- */
