/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: McpCba.h

	CONTEUDO	: Prologo do Modulo McpCba.
                  Contem as constantes e tipos de dados do modulo.

	AUTOR		: Marco Aurelio M Lopes

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	06/11/2012

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
06/11/12 | Edicao inicial 											 | Marco
-------------------------------------------------------------------------------
******************************************************************************/
/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/

#include	<Score.h>
#include	<Eventos.h>
#include	<Prototipos.h>
#include	<string.h>
#include	<time.h>
#include	<sys/kernel.h>
#include	<errno.h>
#include	<ScoreMsgs.h>
#include	<ScoreErros.h>


/*
-------------------------------------------------------------------------------
                           Defines
-------------------------------------------------------------------------------
*/

#define	NUM_LEIT_4S	8
#define	NUM_LEIT_2M 30
#define NUM_LEIT_1M 15
#define NUM_LEIT_5M 75

/*
-------------------------------------------------------------------------------
                           Tipos de dados
-------------------------------------------------------------------------------
*/
typedef 
	struct pots
	{
	float res_05s,
		  res_inst,
		  res_05s_acum,
		  res_inst_acum,
		  res_05s_vet[8],
		  res_inst_vet[8],
		  res_4s,
		  res_4s_score,
		  res_4s_acum,
		  res_4s_score_acum,
		  res_4s_vet[30],
		  res_4s_score_vet[30],
		  sigmas2m,
		  sigmas2m_score,
		  sigmal,
		  sigmal_score,
		  sigmas4s[30],
		  sigmas4s_score[30],
		  res_score_2m,
		  res_score_2m_ant,
		  osc_max,
		  osc_min,
		  MaxOscil,
		  vet_Oscil[10],
		  res_score_1m,
		  res_score_1m_ant,
		  res_4s_1m_score,
		  res_4s_1m_score_acum;
	double sigmas4s_acum,
		  sigmas4s_score_acum;

	int	  num_res_05s,
		  num_res_4s,
		  num_res_4s_1m;
	byte  ContCiclos4s,
		  ContCiclos2m;
	int	  NumRes4sQueb,
		  NumMov;
	float MediaRes4sQueb;
	byte  Sirene;
	float DifCoefAng[20],
		  DifCoefCor[20],
		  CoefCorAnt,
		  CoefAngAnt;
	} calcpots;

/*
-------------------------------------------------------------------------------
                           Variaveis Locais
-------------------------------------------------------------------------------
*/
/* -- Numero de Cubas definido na base de dados (copia local) -- */
DECL	int		NumCubas;
/* -- Faixa de cubas a tratar -- */
DECL	int		CubaIni,CubaFim;
/* -- Contem a hora atual em secundos -- */
DECL	time_t	HoraAtualSec;
/* -- Variaveis de calculo Mcp --  */
DECL	calcpots  pot[MAX_CUBAS];
DECL	int		Conta4s;
DECL	int		Conta2m;
DECL	time_t	HoraInicioDia;
DECL	float	SomaTensaoCubas;
DECL 	float	MediaTensaoLinha;
DECL 	float	MediaSomaCubas;
DECL	byte	ContEaLinha;
DECL 	short int	ContCubasFR;
DECL	byte	ProvavelEfeito;
DECL	long	HoraEaLinha;
DECL	byte	ContEaSim;
DECL	long	DifHoraSirene;
/* -- Intervalo do ciclo de controle em minutos -- */
DECL int IntervCicCont;
DECL	int		Conta1m;
DECL	int		Conta5m;

/*
-------------------------------------------------------------------------------
                           Prototipos
-------------------------------------------------------------------------------
*/
void	IniCubasMcp(void);
void	ProcessaCubas(void);
void	Calculo05s(void);
void	Calculo4s(void);
void	Calculo2m(void);
void	MonitoraCalante(void);
void	VerificaChaveLocRem(void);
void	SopraChamine(void);
void	SinalizaAlarmeSala(void);
void 	AlarmeDesvio(void);
t_boolean ConsisteArgs(int Argc,char *Argv[]);
void	Calculo1m(void);
void	Calculo5m(void);

/* -- Fim do arquivo McpCba.h -- */
