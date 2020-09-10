/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 3.0

	PROJETO		: SCORE

	SISTEMA		: TODOS QUE USEM O ALGORITMO DE CONTROLE DO SCORE (CBA etc)

	ARQUIVO		: MccScore.h

	CONTEUDO	: Prologo do Modulo de Controle das Cubas - MCCScore
                  Contem as constantes e tipos de dados do modulo.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 2.0		  -		  DATA  : 27/02/97

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
dd/mm/aa | descricao                                            | autor 
-------------------------------------------------------------------------------
03/03/99 | Acrescentada funcao ResetRuido                       | Leonel
-------------------------------------------------------------------------------
02/02/01 | Desliga lampada no fim de quebrada preventiva        | Carlos
-------------------------------------------------------------------------------
$Id: MccCba.h,v 1.1.1.1.10.1 2012/09/28 17:09:27 leo Exp $

$Log: MccCba.h,v $
Revision 1.1.1.1.10.1  2012/09/28 17:09:27  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

Revision 1.3  2004/03/16 19:08:13  leo
Incluido novo prototipo de funcao.

******************************************************************************/
/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include	<Score.h>
#include	<ScoreMsgs.h>
#include	<ScoreErros.h>
#include	<stdio.h>
#include	<signal.h>
#include	<setjmp.h>
#include	<float.h>
#include	<stdarg.h>

/*
-------------------------------------------------------------------------------
                           Compilacao condicional
-------------------------------------------------------------------------------
*/
/* -- Quando definido passa cuba para manual remota apos 3 falhas conse-
	  cutivas de movimentacao -- */
#define		MANUAL_APOS_FALHA_MOVE		1

/* -- Definicao de macro para pegar o endereco de retorno de uma funcao -- */
/* -- Baseada na funcao va_start definida em stdarg.h -- */
/*****  #define va_start_RetAdd(ap,paramn,tipo_ant) (ap=((char *)&(paramn)-_va_sizeof(tipo_ant)))
******/

/*
-------------------------------------------------------------------------------
                           Defines
-------------------------------------------------------------------------------
*/
/* -- Tal historico tipico -- */
#define		TAL_HIST_TIPICO	400

/*
-------------------------------------------------------------------------------
                           Tipos de dados
-------------------------------------------------------------------------------
*/
typedef
  struct avc_local
  {
	/* -- Digitais -- */
	int		AjustaEqMotor;
	int		IndicouPrevisao;
#ifdef	MANUAL_APOS_FALHA_MOVE
	int		ContConfigATN7;
#endif
	int		IndicouQPrev;
	byte	MoveuAnodo;
	float	EficMove;
	float	RCicContlAnt;
	byte	AlterouVida;
	byte	IntegraFalhaMov;
	long	LadoQueb;
	int		NumCiclosForaDB;
	int		NQuebDia;
    char   Lado[8];
    char   LadoUltQueb[8];
	int	   UltNQuebDia;
	int	   LadoIdx;
	int	   UltLadoIdx;
	long int  	UltDia;
	long int	Dia;
	int	  	SF_NumDeriv;
	double	SF_Coef_A;
	double	SF_Coef_B;
	double	SF_Coef_C;
	double	SF_Coef_D;	
	byte	PulaDB;
		
	float	HistDerivH[30];		/* Buffer de RSuaveDerivH para calculo de CA */	
	int	ContHistDerivH;		/* Contador do buffer de HistDerivH para calculo de CA */
	long HoraUltProvQueb;
	long IntervQueb; /* Intervalo entre última quebrada sinalizada e provável quebrada (min) */
	int	ProvQuebCond;
	
  } t_avclocal;


/*
-------------------------------------------------------------------------------
                           Variaveis globais
-------------------------------------------------------------------------------
*/
/* -- Numero de Cubas definido na base de dados (copia local) -- */
DECL int	NumCubas;
/* -- Cuba inicial e final passadas como parametro -- */
DECL int	CubaIni;
DECL int	CubaFim;
/* -- Contem a hora do ciclo de controle atual -- */
DECL time_t	HoraAtualCtrl;
/* -- Intervalo do ciclo de controle em minutos -- */
DECL int IntervCicCont;
/* -- Variaveis locais relativas as cubas -- */
DECL t_avclocal		AvcLocal[MAX_CUBAS];
/* -- Ponteiro para a hora ja' dividida do ciclo de controle atual -- */
DECL struct	tm	*PHoraAtual;
DECL struct tm	HoraAtual;

DECL short int NumMov[17];

/* -- Tratamento de excessao de ponto flutuante -- */
DECL  int			CubaGlobal;
DECL  int			PosicaoGlobal;
DECL  char			MsgException[60];
DECL  sigjmp_buf	MccEnvBuf;

/*
-------------------------------------------------------------------------------
                           Prototipos
-------------------------------------------------------------------------------
*/
void	MccControle(void);
void	IniMccControle(void);
void	MccSuperv(void);
void	IniMccSupervisao(void);
void	IniIncrementos(int Cuba);
void	CalculaIncrementos(int Cuba);
void	IniRuido(int Cuba);
void	TrataIncRuido(int Cuba);
void	IniPrevisaoEa(int Cuba);
void	PrevisaoEa(int Cuba);
void	TrataEquiMotor(int Cuba);
void	VerificaAtrasoEa(int Cuba);
void	IniTrataMoveAnodo(int Cuba);
void	TrataMovAnodo(int Cuba);
void	IniEquivMotor(int Cuba);
float	CalcEquivMotor(int Cuba, float Rerro, int *SentidoMov);
void	ComandaMovAnodo(int Cuba,int DuracaoMov,int SentidoMov);
void	IniExecIncUsu(int Cuba);
void	ExecIncUsuario(int Cuba);
void	ResetRuido(int Cuba);
void	ImportaSIAP();
void	VerificaQuebrada(int Cuba);
#ifdef	CBA_120KAII_III
  void	IniQuebPrev(int Cuba);
  void	QuebradaPreventiva(int Cuba);
  void IniTrataPartida(int Cuba);
  void TrataPartida(int Cuba);
  int  ExecutaPasso(int Cuba);
#endif
void	VerificaBSupMovel(int Cuba);
void	SmartFeed(int Cuba);
/* -- Fim do arquivo MccScore.h -- */

