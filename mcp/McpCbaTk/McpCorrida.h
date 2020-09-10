/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: McpCorrida.h

	CONTEUDO	: Prologo do Modulo McpCorrida.
                  Contem as constantes e tipos de dados do modulo.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	24/02/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
21/12/94 | Edicao inicial de migracao para o QNX 4.2				 | Leonel
-------------------------------------------------------------------------------
04/02/95 | Adaptacao para versao em ingles               			 | Carlos
-------------------------------------------------------------------------------
27/01/97 | Incluida variavel RCicCorr em t_avc_loc					 | Carlos
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
#include	<UsuRemota.h>
#include	<RemotaAtn7.h>
#include	<stdio.h>


/*
-------------------------------------------------------------------------------
                           Defines
-------------------------------------------------------------------------------
*/

/*
-------------------------------------------------------------------------------
                           Tipos de dados
-------------------------------------------------------------------------------
*/
typedef
  struct avc_loc
  {
	float	Vmax;
	float	VAlvo;
	float	RCicCorr;
	float	TMaxCorr;
	byte	CalcEqMotorCorr;
	float	DurUltMovCorr;
	float	ResUltMovCorr;
	float 	UltVCicCtrl;
  } t_avc_loc;

/*
-------------------------------------------------------------------------------
                           Variaveis Locais
-------------------------------------------------------------------------------
*/
/* -- Numero de ciclos de leitura para ajuste de corrida -- */
DECL	int		NumCicCorr;
/* -- Numero de Cubas definido na base de dados (copia local) -- */
DECL	int		NumCubas;
/* -- Faixa de cubas a tratar -- */
DECL	int		CubaIni,CubaFim;
/* -- Contem a hora atual em secundos -- */
DECL	time_t	HoraAtualSec;
/* -- Variaveis locais por cuba -- */
DECL	t_avc_loc	AvcLoc[MAX_CUBAS];

DECL  long Depurar;

/*
-------------------------------------------------------------------------------
                           Prototipos
-------------------------------------------------------------------------------
*/
void	IniMcpCorrida(void);
void	IniMcpCorCuba(int Cuba);
t_boolean ConsisteArgs(int Argc,char *Argv[]);
void	ProcessaCubas(void);
void	IniCorrida(int Cuba);
void	DuranteCorr(int Cuba);
void	CalcRCicCorr(int Cuba);
void	VerificaResist(int Cuba);
void	DuranteEfCorr(int Cuba);
int		VerificaFaixaControle(int Cuba,float Rerro);
void	EfetuaMov(int Cuba,float RErro);
float	CalcEquivMotor(int Cuba, float Rerro, int *SentidoMov);
void	CalculaRAlvo(int Cuba);

/* -- Fim do arquivo McpCorrida.h -- */
