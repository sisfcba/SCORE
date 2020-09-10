/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 3.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: Log.h

	CONTEUDO	: Constantes e tipos de dados relativos ao modulo de log

	AUTOR		: Leonel Vicente Mota Ivo
				  Eduardo Pereira

	VERSAO		: 1.0			-		DATA	:	20/08/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
dd/mm/aa | descricao                                            | autor 
-------------------------------------------------------------------------------
******************************************************************************/

#ifndef		_LOG_H
  #define		_LOG_H

#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/name.h>
#include <sys/vc.h>
#include <sys/osinfo.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <sys/kernel.h>
#include <Definicao.h>
#include <Score.h>
#include <ScoreConst.h>
#include <Prototipos.h>
#include <CopiaDir.h>
#include <VarsComum.h>
#include <Eventos.h>
#include <IniArqVar.h>
#include <RelGraf.h>
#include <ScoreMsgs.h>
#include <ScoreErros.h>

/*
 * 			Codigos de retorno do modulo log
 *			--------------------------------
 */

#define OK_LOG				0	/* Okay!...									*/
#define FILE_ALREADY_EXISTS	1	/* Arquivo ja existe						*/
#define TOO_MANY_LOGS		2	/* muitos logs executando concorrentemente	*/
#define NO_MEM   			3	/* memoria insuficiente						*/
#define CUBA_INV			4	/* Cuba nao inicializada					*/ 
#define NOME_INV			5   /* Nome de arquivo invalido					*/ 


/*
 * 			Funcoes do modulo log
 *			---------------------
 */

#define CREATE_LOG		0		/* Pedido de criacao de log_son				*/
#define SIGNAL_LOG		1		/* Pedido de sinalizacao de log_son (2min)	*/
#define QUERY_LOG		2		/* Pedido de status dos logs ativos			*/
#define DELETE_LOG		3		/* Pedido de exclusao de um log				*/
/* -- o modulo historico requisita a tarefa log as seguintes informacoes -- */
/* -- da base de dados: numero de segs por batida e tab. desc. eventos -- */
#define INFO_BD_SCORE	4
#define SIGNAL_LOG_1	5		/* Pedido de sinalizacao de log_son (0.5s)	*/


/*
 * 			Constantes relacionadas ao modulo log
 *			-------------------------------------
 */

#define LOG_2M				0
#define LOG_05S				1
#define OPERADOR_1			0    /* trata >= */
#define OPERADOR_2			1    /* trata <= */
#define OPERADOR_3			2    /* trata >  */
#define OPERADOR_4			3    /* trata <  */
#define OPERADOR_5			4    /* trata == */
#define	MAX_REG_HIST		57600
#define MAX_REGS_TRIGGER	1800

//#define	MAX_VALOR_2M		240

#define MAX_BUF_EV_LOCAL	20
#define TRIGGER_PRONTO		0
#define TRIGGER_EM_CURSO	1
#define TRIGGER_FINALIZADO	2

#define MAX_DIAS_LOG		15	/* -- 15 dias -- */
/* -- diretorio em que sao criados os logs -- */
#define DIR_LOGS			"/score/log"
#define DIR_LOGS_AUX		"/score/log/aux"

#define KILLED		0
/* -- 600 K e' o minimo de memoria disponivel para que se crie o LogSon -- */
#define MEMORIA_DISPONIVEL	(600*3)	
#define MAX_LOGS	MAX_LOGS_ATIVOS
#define	NODO_COMPL_CTL(Nodo)	((Nodo Mod 2) eq 0 ? Nodo-1 : Nodo+1)
#define MAX_LOGS_PARTIDA		20

/* -- mensagem entre as tarefas que manipulam os logs -- */
/* -- Log, LogSon, CriaLog, DeletaLog -- */
typedef
  struct MsgLog
  { /* mensagem entre os programas que usam LOG */
	int			CodLog;
	union
    {
	  char		NomeArq[40];
	  unsigned	TidLogDel;
	} Ulog;
    unsigned Cuba;
	unsigned NumVarLog;
	unsigned NumBatidas;
    struct {
      char	    NomeVar[20];
	  byte		TabVar;
	  byte		TabVarLim;
      char      UEvar[20];
      char      FmtVar[11];
      float     FatConv;
      float     LimInf;
      float     LimSup;
    } Var[MAX_VAR_LOG];
    char     Trigger_ON[20];
    char     Trigger_OFF[20];
    byte     Condicao_ON;
    byte     Condicao_OFF;
    float    Compara_ON;
    float    Compara_OFF;
	byte	 TipoLog;

    short int TabVarON;
    short int TabVarOFF;
	short int TempoTrigger;
    float	 FatConvON;
	float	 FatConvOFF;
	byte	 AtivaAuto;
	short int FatorMulti;
    char     reserva[32];
  } t_msg_log;

/* -- estrutura a ser utilizada na troca de mensagens entre a tarefa Log e -- */
/* -- a tarefa que informa os logs ativos do sistema -- */
typedef
  struct MsgQuery
  {
    int NumLogsAtivos;
    struct
    {
      char NomeArqDel[40];
      int  TidLogDel;
    } Log[MAX_LOGS_ATIVOS];
  } t_msg_query;

/* -- cabecalho do arquivo de log -- */
typedef
  struct HeaderLog
  {
    int     Versao;
	long	NregsLog,
			InicioLog,
			FimLog;		/* ????? acho que nao precisa ??????? */
	int		NticksLog,
			NvarsLog;
    int		CubaLog;
    struct {
      char	    NomeVar[20];
	  byte		TabVar;
	  byte		TabVarLim;
      char      UEvar[20];
      char      FmtVar[11];
      float     FatConv;
      float     LimInf;
      float     LimSup;
    } Var[MAX_VAR_LOG];
    char    Trigger_ON[20];
    char    Trigger_OFF[20];
    byte    Condicao_ON;
    byte    Condicao_OFF;
    float   Compara_ON;
    float   Compara_OFF;
	byte	TipoLog;

    short int TabVarON;
    short int TabVarOFF;
	short int TempoTrigger;
    float FatConvON;
	float FatConvOFF;
	short int FatorMulti;
	byte	 AtivaAuto;
	int		 NticksLogAux;
    char     reserva[28];
  } t_header_log;

/* -- cabecalho do arquivo de log -- */
typedef
  struct HeaderLogAnt
  {
	long	NregsLog,
			InicioLog,
			FimLog;		/* ????? acho que nao precisa ??????? */
	int		NticksLog,
			NvarsLog,
			IndVar[MAX_VAR_LOG],
			GrupoVar[MAX_VAR_LOG],
			CubaLog;
  } t_header_log_ant;

/* -- formato de um registro do arquivo de log -- */
typedef
  struct RegLog
  {
	long	DataLog;
	float	VarsLog[MAX_VAR_LOG];
  } t_reg_log;

/* -- formato da estrutura do arquivo de trigger */
typedef
  struct Trigger
  {
	byte		f_situacao;
	long		hora_inicio;
	long		hora_criacao;
	int			num_regs;
	int			ind_reg;
	byte		f_circulou;
	t_reg_log	reg[MAX_REGS_TRIGGER];
  } t_trigger;

/* -- formato do registro que contem os dados sobre um evento ocorrido -- */
//typedef
//  struct EventosLog
//  {
//	long DataEv;
//    int  CodEv;
//  } t_evento_log;

/* -- mensagem enviado da tarefa log para o modulo historico contendo -- */
/* -- as informacoes necessarias a este modulo -- */
typedef
  struct MsgBD
  {
    int IntervCicCont;
    t_desc_ev TdescEv;
  } t_msg_bd;

/* -- no estrutura p/ logo_novo sem o LogSon, toda implementacao no proprio log -- */
typedef	struct	_logs {
  int			FileTrigger;
  int			Funcao;
  int			conta_2m;		/* conta o ciclo p/ gravar */
  int			conta_2m_t;		/* conta o ciclo p/ gravar trigger */
  int			conta_fator;	/* conta numeros de fatores */
  int			conta_partida;  /* contador p/ escalonar partida */
  int			f_acha_eventos;
  int			Cuba;
  int			ContaEv;
  int			LogSonTid;
  time_t		HoraAnt;
  t_msg_log		MsgLog;
  t_header_log 	HeaderLog;
  t_trigger		*reg_t;
  t_reg_log		*RegLogAux;
  t_rec_ev		*evento;
}t_logs;

/*
--------------------------------------------------------------------------------
                         Prototipos
--------------------------------------------------------------------------------
*/
void	IniLogs(void);
int		Install(int, t_msg_log *);
void	UnInstallKilled(void);
void	LeArqVar( void );
int		PegaLogFree( void );
int		IniLogSon( t_logs *Logs, time_t HoraAtual );
void	MainLogSon( t_logs *Logs, int *Funcao, int *Batida, time_t HoraAtual );
int		CriaTrigger( t_logs *Logs, time_t HoraAtual );
int 	TrataTrigger( t_logs *Logs, time_t HoraAtual );
char 	*LeComum( char *nome, size_t tamanho );
float	ValorVar( char *NomeVar, int Tabela, int Cuba );
int		AtivaAuto( t_log_node *Ptid, t_logs *Logs, time_t HoraAtual );
void	ErroLog( char *Erro );
void	MontaNomeTrigger( t_logs *Logs, char *p );
void	AchaEvento( t_logs *Logs, time_t HoraAtual );

/*
--------------------------------------------------------------------------------
                         Variaveis globais
--------------------------------------------------------------------------------
*/
/* -- Apontador para a tabela de logs -- */
DECL	t_arqvar	*Arqvar;
DECL	t_log		*PcomumLog;
DECL	t_msg_bd	MsgBD;
DECL	byte		NumLogFree[MAX_LOGS];
DECL	t_logs		Logs[MAX_LOGS+1];

#endif
