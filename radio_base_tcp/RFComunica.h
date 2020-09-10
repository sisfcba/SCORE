/******************************************************************************

             ACCENTURE - ACPS - ACCENTURE PLANT & COMMERCIAL SERVICES
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 5

    CLIENTE     : CBA - Companhia Brasileira de Aluminio SA

	PROJETO		: GENERICO

	SISTEMA		: GENERICO

	ARQUIVO		: RFComunica.h 

	CONTEUDO	: Defines, include da RFComunica

	AUTOR		: Alexandre Mariz Bandeira de Morais

	SISTEMA OPERACIONAL:  QNX 4.23A		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 1.0		  -		  DATA  : 17/11/97

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
17/11/97 | Edicao Inicial                                		| Bandeira
-------------------------------------------------------------------------------
$Id: RFComunica.h,v 1.11.4.1 2014/10/27 15:23:53 leo Exp $

$Log: RFComunica.h,v $
Revision 1.11.4.1  2014/10/27 15:23:53  leo
Preparacao para criar kit de desenvolvimento do radio. Retiradas referencias
a prologo antigo da Alcan.

******************************************************************************/

#ifndef __CONTROLADOR__
  #define __CONTROLADOR__

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <ctype.h>
#include <stdarg.h>
#include <sys/mman.h>
#include <sys/dev.h>
#include <sys/proxy.h>
#include <sys/kernel.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/name.h>
#include <sys/qnx_glob.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <process.h>
#include <errno.h>
#include <Prototipos.h>
#include <Definicao.h>
#include <Macros.h>
#include <Score.h>
#include <VarsComum.h>
#include <ScoreMsgs.h>
#include <ScoreErros.h>
#include <BdScore.h>
#include <RelGraf.h>
#include <IniArqVar.h>
#include <EventosMsg.h>

#define 	TERMTYPE			32
#define 	RECEIVE_TIMEOUT		30				// em segundos
#define		RADIO_WATCHDOG		"EU ESTOU VIVO"
#define		RADIO_SCORE			"EU ESTOU FORA"
#define		RADIO_ABORTAR		"EU VOU CAIR FORA"
#define 	MAX_MSG_SIZE		512				// Tamanho maximo de uma mensagem para a RB
#define		COLETOR_LINHAS		16/*10*/
#define		COLETOR_LINHAS_2	10
#define		COLETOR_LINHAS_3	8
#define		COLETOR_COLUNAS		20
#define		COLETOR_COLUNAS_2	16
#define		MAX_BYTES_TELA		(COLETOR_COLUNAS*COLETOR_LINHAS_2)
#define		COLETOR_TIMEOUT		600	/* tempo em segundos para powerup automatico */
#define		COLETOR_DINAMICO	1	/* tempo em segundos para atualizacao dinamica */
#define		COLETOR_TIMEOUT_ON	1	/* timeout powerup ativado */
#define		COLETOR_LIGHT_ON	30	/* tempo em segundos para light on */
#define		NUM_TAGS_PAGINA		8
#define 	SIZE_TELA_COLETOR	128	// numero total de caracteres na tela do coletor
#define 	USUARIO_INVALIDO	0
#define 	SENHA_INVALIDA		1
#define 	OK					2
#define		SAIR_MENU			(-999999999L)
//#define		DEBUG_RADIO			1

// Definicao das opcoes para mostrar dados (comuns a data e table)
#define 	DP_CURSOR			0x0001	// liga cursor
#define 	DP_SOUND			0x0002	// liga som
#define 	DP_DISPLAY_DATA		0x0004	// ecoa dados
#define 	DP_NUMERIC_ONLY		0x0008	// dados numericos
#define 	DP_ENABLE_SCAN		0x0010	// espera resposta
#define 	DP_NO_TIMEOUT		0x0020  // sem timeout
#define 	DP_DINAMICO			0x0040  // atualizacao dinamica
#define 	DP_GRAPHICS			0x0080  // monta graficos
#define 	DP_CONFIGURA		0x0100  // configuracao de parametros
#define 	DP_BATERIA			0x0200	// condicoes da bateria (6400)
#define 	DP_ABORTA 			0x0400	// pede ao radio p/ abortar

#define		condicao(var)	( (var==1)?"S":"N" )
#define		condicao2(var)	( (var==0)?" ":(var==1)?"A":(var==2)?"B":"AB" )
#define		condicao3(var)	( (var==0)?" ":(var==1)?"A":(var==2)?"N":"B" )
#define		condicao4(var)	( (var==0)?" ":(var==1)?"1":(var==2)?"2":(var==3)?"3":"4" )

DECL t_grupo_cuba		Grupo;
DECL t_arqvar			*Arqvar;
DECL t_descr_conv 		*PDescConv;
DECL t_val_graf_cuba	*ValGraf;
DECL time_t				HoraInicio;
DECL int				iTermNumber;
DECL int				NumOperador;
DECL int				cuba_num, cuba_ope;
DECL int				Nivel;
DECL int				Controle[NUM_TAGS_PAGINA*2];
DECL int				Ruido[NUM_TAGS_PAGINA*2];
DECL int				Status[NUM_TAGS_PAGINA*2];
DECL char				aux[MAX_MSG_SIZE];
DECL char				aux1[MAX_MSG_SIZE];
DECL char				aux2[MAX_MSG_SIZE];

typedef struct _sTermAnsw
{
	int		bScanner;	// TRUE se a resposta veio do scanner, senao eh do teclado
	char	pcAnswStrg[MAX_MSG_SIZE];
} STERMANSW, *PSTERMANSW;

typedef struct _sMostraTableParm
{
	unsigned long ulCtrlChar;
	unsigned long ulStartField;
	unsigned long ulFirstDspField;
} SMOSTRATABLEPARAM, *PSMOSTRATABLEPARAM;

typedef struct _MandaMsgParam
{
	int		iRow;
	int		iCol;
	unsigned long ulOptions;
	int		iCurRow;
	int		iCurCol;
} SMANDAMSGPARAM, *PSMANDAMSGPARAM;

// Estrutura da mensagem passada entre as aplicacoes e o driver
typedef struct _msgdrvapp
{
	int		iCommand;
	int		iTermNum;
	char	pcMsg[MAX_MSG_SIZE];
	int		dwNewProcessId;
} SMSGDRVAPP, *PSMSGDRVAPP;

void PoeNUL( char *str, int tam, int lim );
void Quebrada(void);
void Corrida(void);
void TrocaPinos(void);
void Processo(void);
int	 cuba(char *p);
int  login(void);
int  SinalSituacao(int Cuba);
void HoraSistema(void);
void Graficos(void);
void Parametros(void);
void AtualVar(void);
void MontaConfiguracao(int tipo, int par1, int par2, int par3);
unsigned tirabits( unsigned pal, unsigned biti, unsigned bitf );
int  AchaTagValido( int CubaScore, int tab, int ind, int tipo, int *aux );
void MontaVariavel( int CubaScore, int tab, int ind, char *buffer );
void Operacao1( void );
void Operacao2( void );
void GravaTabelas(int CubaScore);
void LeTabelas(int CubaScore);
void GeraEvenLog( void *PVarCom, void *PVarNew, int tab, int Ind, int CubaScore );
void LogConfigCuba( int CubaScore, int tab, int Ind );
void MontaVarColetor( int CubaScore, int tab, int ind, char *buffer1, char *buffer2 );
void Parametros(void);
int  CopyValor( int tab, int ind, int checa, char *buf );
void GeraEvenLog( void *PVarCom, void *PVarNew, int tab, int Ind, int CubaScore );
void insbits( unsigned *pal, unsigned biti, unsigned bitf, unsigned valor );
char *trim( char *str );
void Eventos(void);
void EvLinha(void);
void EvCuba(int Cuba, int NumCuba);
char *LeComum( char *nome, size_t tamanho );
int  MarcaAtual( int tag, int tipo );
void DesmarcaAtual(void);
void Bateria(void);
void MenuPrincipal(void);
void ProcessaMetal(void);
void TrataMetal1(void);
void TrataMateriasPrimas(void);
void TrataMetal2(void);
void TrataAnodo(void);
void TrataProcessaMetal(int var, byte *valor);
char *GetNomeArqVar(int Campo);
char *GetUEArqVar(int Campo);
float GetMaxArqVar(int Campo);
float GetMinArqVar(int Campo);
short GetTipoArqVar(int Campo);
short GetPrecArqVar(int Campo);
void  ExecutaMain(void);
void AlarmHand(int aSigNumber);
void PipeHand(int aSigNumber);
void print_debug(char *apFormat, ... );
void exit_debug(int ret,int erro);
int	MandarPrompt (PSMANDAMSGPARAM psParam, char* pcMsg, int iAnsSpc, PSTERMANSW psTermResp);
void TrataErroColetor( int dwError );
int read_msg(byte *apMsg, int aMsize);
int write_msg(byte *apMsg, int aMsize);
int	Comunica(char *psAppMsg, char *pcDados, byte WaitResp);
float ChecaHora( char *str );
void Calibracao(void);
void Abandona(void);
void MenuCalibExib(void);
void RelOperacao(void);
char *AtivaOperacao( int argc, char *argv[] );
void MCruzeiro(void);
byte AchaVarRef( int aGraf, int aCuba );

// Prototipos fontes CBA
void CorridaCba(void);
void CorridaBanho(void);
void ProcessoCba(void);
int  SinalSituacaoCba(int Cuba);
void MCruzeiroCba(void);
void ExibeMensCba(char *mens);
void Operacao1Cba(void);
void Operacao2Cba(void);
void ProcessaMetalCba(void);
void TrataMetal1Cba(void);
void TrataMateriasPrimasCba(void);
void TrataMetal2Cba(void);
void TrataAnodoCba(void);
void TrataProcessoMetalCba(int Var, byte *Valor);
char *GetNomeArqVarCba(int Campo);
char *GetUEArqVarCba(int Campo);
short GetPrecArqVarCba(int Campo);
float GetMaxArqVarCba(int Campo);
float GetMinArqVarCba(int Campo);
short GetTipoArqVarCba(int Campo);
void QuebradaCba(void);
void RelOperacaoCba(void);
void TrocaPinosCba(void);

#endif
