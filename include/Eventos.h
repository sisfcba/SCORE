/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 3.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II E III

	ARQUIVO		: Eventos.h

	CONTEUDO	: Constantes e tipos de dados do modulo eventos

	AUTOR		: Joao Thomaz Pereira

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	20/08/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
05/01/93 | Acrescentado Evento FALHA_MOVIMENTACAO					 | Leonel 
-------------------------------------------------------------------------------
04/04/94 | Incluida estrutura para relatorio instantaneo de			 | Carlos 
         | mensagens de eventos.									 |
-------------------------------------------------------------------------------
25/07/94 | Acrescentado Evento SISTEMA_ATIVADO						 | Carlos 
-------------------------------------------------------------------------------
08/03/95 | Acrescentado Eventos LINHA_ATIVADA e RUIDO_INIBIDO		 | Leonel
-------------------------------------------------------------------------------
13/10/95 | Incluido o arquivo ScoreConst.h							 | Carlos
-------------------------------------------------------------------------------
22/12/95 | Acrescentado tratamento de alarmes para PAl				 | Carlos
-------------------------------------------------------------------------------
04/03/96 | Acrescentados eventos do usuario							 | Carlos
-------------------------------------------------------------------------------
24/07/96 | Acrescentado definicoes de retorno das funcoes de leitura | Carlos
         | de eventos de relatorio do arquivo LeArqEv.c na lib_score |
-------------------------------------------------------------------------------
$Id: Eventos.h,v 1.2.8.2 2015/10/30 12:40:48 leo Exp $

$Log: Eventos.h,v $
Revision 1.2.8.2  2015/10/30 12:40:48  leo
Inclusao de novo algoritmo para utilizacao da corrente da linha de forma
emergencia quando detectado que a corrente de uma cuba desviou (exemplo:
quando abre o loop de corrente).

Revision 1.2.8.1  2015/06/30 22:44:54  clage
Alteracoes para sala II com ATN8 e expansao da base de dados.

Revision 1.2  2004/07/28 19:36:24  leo
Inclusao de eventos de diferenca de leitura entre principal e reserva para
a CBA sistemas com 2 atn1.4. Gerado pelo HotStBy.

******************************************************************************/

#ifndef _EVENTOS_H

#define _EVENTOS_H

#include <Definicao.h>
#include <ScoreConst.h>
#include <queue.h>
#ifdef	ALBRAS
  #include <EventosAlbras.h>
#endif
#ifdef	ALCAN_ARATU_HS
  #include <EventosAlcan.h>
#endif
#ifdef	CBA_120KAII_III
  #include <EventosCba.h>
#endif
#ifdef	KONIN
  #include <EventosKonin.h>
#endif

/* Quando definido nao utiliza ramdisk para os eventos do dia corrente */
#define 		NAO_USA_EV_RAMDISK		1

/*
--------------------------------------------------------------------------------
						Codigo dos Eventos
--------------------------------------------------------------------------------
*/
#define	SUBIDA_AUT_ANODO	  1	  /* -- Subida automatica de anodo comandada -- */
#define	SUBIDA_MAN_ANODO	  2	  /* -- Subida manual de anodo executada -- */
#define	CNF_SUBIDA_AUT_ANODO  3	  /* -- Subida automatica de anodo confirmada -- */
#define	INI_DES_TENSAO_PR_EA  4	  /* -- Inicio desvio de tensao em previsao de Ea -- */
#define	INI_DESVIO_TENSAO	  5	  /* -- Incio desvio de tensao -- */
#define INICIO_EA			  6	  /* -- Inicio de Efeito Anodico -- */
#define FIM_EA				  7	  /* -- Fim de Efeito Anodico -- */
#define CORRENTE_INVALIDA	  8	  /* -- Erro leitura de Corrente da Linha -- */
#define SUPERV_ESPECIAL		  9	  /* -- Valor de resistencia fora da faixa -- */
#define CUBA_FORA_LEITURA	  10  /* -- Cuba foi retirada de leitura -- */
#define LINHA_HABILITADA	  11  /* -- Linha foi ativada -- */
#define LINHA_DESABILITADA	  12  /* -- linha foi desativada -- */
#define DIF_CORRENTE		  13  /* -- diferenca entre as leituras da -- */
								  /* -- corrente de linha (princ. e reserva) -- */
#define RESERVA_ATIVO		  14  /* -- micro reserva ativo -- */
#define RESERVA_DESATIVADO	  15  /* -- micro reserva desativado -- */
#ifdef	ALBRAS
 #define INTEGRACAO_LINHA	  16  /* -- Integracao de linha/corrente da linha -- */
#else
 #define INICIO_QUEBRADA	  16  /* -- inicio de quebrada -- */
#endif
#define INICIO_CORRIDA		  17  /* -- inicio de corrida -- */
#define EV_CHAVE_LOCAL		  18  /* -- alteracao chave para modo local -- */
#ifdef	ALBRAS
 #define DESC_AUT_CORR		  19  /* -- Descida automatica em corrida -- */
#else
 #define SUBIDA_MAN_CAMISA	  19  /* -- Livre - Substituido por MOVE_MAN_CAMISA -- */
#endif
#define	VLINHA_INV			  20  /* -- Erro leitura de tensao de linha -- */
#define	OPERACAO_MANUAL		  21  /* -- Selecao modo de operacao para manual -- */
#define	EVENTO_MUDA_ESTADO	  22  /* -- Mudanca estado da cuba pela operacao -- */
#define	EVENTO_INC_OPERACAO   23  /* -- Ativa/Desativa incremento de operacao -- */
#define	CORRENTE_BAIXA		  24  /* -- Corrente de linha < ILinhaBaixa -- */
#define	CORRENTE_ALTA		  25  /* -- Corrente de linha > ILinhaAlta -- */
#define	DESCIDA_AUT_ANODO	  26  /* -- Descida automatica de anodo comandada -- */
#ifdef	ALBRAS
 #define SUB_AUT_CORR		  27  /* -- Subida automatica em corrida -- */
#else
 #define DESCIDA_MAN_ANODO	  27  /* -- Descida manual de anodo executada -- */
#endif
#define	CNF_DESCIDA_AUT_ANODO 28  /* -- Descida automatica de anodo confirmada-- */
#define	FIM_DES_TENSAO_PR_EA  29  /* -- Fim desvio de tensao em previsao de Ea -- */
#define	FIM_DESVIO_TENSAO	  30  /* -- Fim desvio de tensao -- */
#ifdef	ALBRAS
 #define	FALHA_REDE		  31  /* -- Rompimento de cabo na subrede echelon -- */
#else
 #define FIM_QUEBRADA		  31  /* -- Fim de quebrada -- */
#endif
#define FIM_CORRIDA		  	  32  /* -- Fim de corrida -- */
#define EV_CHAVE_REMOTO		  33  /* -- alteracao chave para modo remoto -- */
#define CFG_PAR_CUBA		  34  /* -- Livre - Substituido por MOVE_MAN_CAMISA -- */
#define	OPERACAO_AUTOMATICO	  35  /* -- Selecao modo de operacao para automatico -- */
#define	INICIO_PREV_EA		  36  /* -- Inicio de previsao de EA -- */
#define	FIM_PREV_EA			  37  /* -- Fim de previsao de EA -- */
#define	ATRASO_EA			  38  /* -- Cuba em atraso para entrar em EA -- */
#define	FALHA_MOVIMENTACAO	  39  /* -- Falha na movimentacao de anodo da Cuba -- */
#define	EV_INC_TROCA_PINOS	  40  /* -- Ativa/Desativa inc. troca de pinos -- */
#define	SISTEMA_ATIVADO   	  41  /* -- Sistema Ativado -- */
#define	LINHA_ATIVADA   	  42  /* -- Linha no controle -- */
#define	RUIDO_INIBIDO   	  43  /* -- Tratamento de ruido inibido por tempo indicado -- */
#define	EVENTO_TAB_OPERACAO	  44  /* -- Ativa/Desativa tabela de operacao w -- */
#define	LOG_OPER_CUBA		  45  /* -- Geracao de evento de log de cuba  -- */
#define	LOG_OPER_LINHA		  46  /* -- Geracao de evento de log de linha -- */
#define	INI_INIBE_MOV	  47  /* -- Movimentacao inibida por derivada resistencia -- */
#define	FIM_INIBE_MOV	  48  /* -- Movimentacao habilitada por derivada resistencia -- */
#define	EV_RUIDO			  49  /* -- Evento de inicio/fim tratamento de ruido -- */
#ifdef	ALBRAS
 #define	FALHA_MMACACO		50 /* -- Falha no acionamento de motor macaco -- */
 #define	FALHA_ALIMENTACAO	51 /* -- Falha no alimentador da cuba -- */
 #define	CHAVE_CORR_NAO_REP	52 /* -- Chave de corrida nao reposicionada -- */
 #define	CIRCUITO_MM_ABERTO	53 /* -- Circuito de comando do Anodo aberto -- */
 #define	CHAVE_TANODO_NAO_REP 54 /* -- Chave de troca de anodo nao reposicionada -- */
 #define	FALHA_QUEBRADOR		55 /* -- Falha do quebrador -- */
 #define	REC_ALARME_PAL		56 /* -- Evento para reconhecer alarme do PAl.
									 O 1o. parametro e' o cod. do evento a reconhecer -- */
 #define	TROCA_ANODO			57 /* -- Evento troca de anodo -- */
 #define	PARADA_CONTROLE		58 /* -- Parada do controle automatico -- */
 #define	CORRIDA_IMPOSSIVEL	59 /* -- Corrida impossivel por limitacao de acionamentos -- */
#else
 #define	INTEGRACAO_LINHA	50 /* -- Integracao de linha/corrente da linha -- */
 #define	DESC_AUT_CORR		51  /* -- Descida automatica em corrida -- */
 #define	SUB_AUT_CORR		52  /* -- Subida automatica em corrida -- */
 #define	FALHA_REDE			53  /* -- Rompimento de cabo na subrede echelon -- */
/* -- alteracao - inicio - 10/10/2002 - Leonel - Monitoracao corrente de cuba para alarme -- */
#ifdef	CBA_120KAII_III
 #define	DIF_CORRENTE_CUBA	54	/* -- diferenca entre as leituras da -- */
								  /* -- corrente de linha (principal) e a de cada cuba -- */
 #define	TEMP_ATN8_CUBA		55	/* -- temperatura alta na Atn8 de cuba -- */
 #define	FALHA_IO_ATN8		56	/* -- falha de leitura de I/O da Atn8 -- */
 #define	CORRENTE_EMERG_CUBA	57	/* -- Corrente de emergencia (linha) usada para cuba -- */
#else
/* -- alteracao - fim - 10/10/2002 - Leonel - Monitoracao corrente de cuba para alarme -- */
#ifndef	KONIN
 #define	TABELA_EA_NAO_ATIVADA 54 /*-- Tabela de elim. de EA nao ativada --*/
 #define	TABELA_ELIM_EA      55 /*-- Evento de tabela de eliminacao de EA --*/
#endif
#endif
#endif

#ifdef	ALBRAS
 /* -- Inicio dos eventos de usuario -- */
 #define	EV_USUARIO			75 /* -- Inicio de evento de usuario -- */
 
 /* codigo para limpar lista do PAl atraves do REC_ALARME_PAL */
 #define	LIMPA_FILA_PAL		1000
#else
 /* -- Inicio dos eventos de usuario -- */
 #define	EV_USUARIO			65 /* -- Inicio de evento de usuario -- */
#endif

/* -- Grupos -- */
#define 	REG_IMPRIME_EXIBE		1	/* -- Registra Imprime e Exibe -- */
#define 	REG_EXIBE				2	/* -- Registra e Exibe -- */
#define 	REG_IMPRIME				3	/* -- Registra e Imprime -- */
#define 	REGISTRA				4	/* -- Apenas Registra -- */
#define 	NAO_REGISTRA			5	/* -- Nao registra (uso interno) -- */

/* -- Dispositivos -- */
#define		TODOS_DISPOSITIVOS		1	/* -- Para geracao de eventos -- */
#define		NAO_EXIBE_GRAF_CUBA		2   /* -- So nao exibe no grafico de cubas e log --*/
#define		NAO_EXIBE_EV_INST		3   /* -- So nao exibe no instantaneo de eventos --*/
#define		NAO_EXIBE_EV_INST_GRAF	4   /* -- So nao exibe no instantaneo de eventos
											  e no grafico de cubas e log --*/

/* -- 	Definicao de tipo de dados -- */

#define		TIPO_CHAR		1
#define		TIPO_INTEIRO	2
#define		TIPO_LONG		3
#define		TIPO_FLOAT		4
#define		TIPO_STRING		5
#define		TIPO_NAO_INIC	-1

/* --	Definicao de constantes  -- */

#define 	CONSOLE			0		/* Define o periferico console */
#define 	SEALTOUCH		1		/* Define o tipo de periferico sealtouch */
#define 	TERM_QNX		2		/* Define o tipo de periferico terminal QNX */
#define 	LIN_EVENTO		24		/* Define linha para apresentacao do evento */
#define 	COL_EVENTO		0		/* Define coluna para apresentacao do evento */
#define 	QUEUE_MSG_SIZE	600		/* Numero de mensagens antes do bloqueio */

/* --	Definicao do arquivo historico de eventos -- */

#define		ARQUIVO_EV_DISCO 	"/score/eventos/Evs_%02d_%02d_%02d"

#ifdef	NAO_USA_EV_RAMDISK
 /* Nao usa ramdisk para eventos do dia corrente */
 #define		ARQUIVO_EV_RAMDISK	ARQUIVO_EV_DISCO
#else
 /* Usa ramdisk para eventos do dia corrente */
 #define		ARQUIVO_EV_RAMDISK	"/tmp/score/eventos/Evs_%02d_%02d_%02d"
#endif

#define		TASK_IHM			"Atan/Score/Ihm_%02d"
#define		TASK_IHM_ST			"Atan/Score/IhmST%02d"

/* --   Modos de escrita de eventos no SealTouch -- */
#define		ESC_EV				1				/*Escreve evento recebido*/
#define		REP_EV				2				/*Repete o ultimo evento escrito*/

/* --	Definicao de filas para eventos -- */
#define		FILA_EV_GERAL 		"[%d]EvGeral"    /*Fila para uso geral */
#define		FILA_EV_MSG			"[%d]EvMsg"      /*Fila para uso interno */
#define		FILA_SP_CON			"[%d]LPT%d"      /*Fila spooler p/ console */
#define		FILA_SP_ST			"[%d]IST%d"      /*Fila spoller p/ sealtouch */

/* --	Definicao do string para parametro vazio -- */
#define		STR_TRACO			"--------"

/* --	Definicao do nome do buffer de mensagens -- */
#define		NOME_MSG_BUFFER		"Atan/Score/Eventos"

/* --	Definicao do numero maximo de mensagens do buffer -- */
#define		MAX_MSG_BUFFER		1000	/*500*/

/* --	Definicao do sinal de buffer vazio -- */
#define		BUFFER_VAZIO		-1

/* -- Retorno das funcoes de leitura de eventos -- */
#define	EVENTO_VALIDO			0
#define	FALHA_ABERTURA			1
#define	FIM_CACHE				2
#define	FALHA_LEITURA			3
#define	PASSOU_FAIXA			4
#define	FALHA_BUSCA				5
#define	FIM_LEITURA				6
#define	FIM_ARQUIVO				7
#define	CACHE_MONTADO			8

/*                              
-----------------------------------------------------------------------------
		Definicao de codigos para apresentacao dos alarmes 
-----------------------------------------------------------------------------
*/

#define 	ERROR_PROG		-1		/* Erro interno de programas */
#define 	REC_TODOS_EV   	-2		/* Reconhece todos os alarmes pendentes */
#define 	REC_UM_EV		-3		/* Reconhece o primeiro alarme pendente */
#define 	ALARME_PROG		-4		/* Erro interno de programas */
#ifdef	ALBRAS
  #define 	REC_EV_PAL		-5		/* Reconhece alarme do PAl */
#endif

#define TAM_MSG_ERR		(10+(N_PAR_EV*sizeof(double))+1)	/* tamanho maximo para mensagem de erro */

/*---------------------- Registro de eventos ---------------------------------*/
typedef
  struct RegistroEventos
  {
	long 	 DataEv;		/* Data em segundos da Geracao do Evento */

    int		 CubaIniEv,     /* Cuba inicial para evento */
	         CubaFimEv;     /* Cuba final para Evento */
	int      CodeEv,        /* Numero do evento do sistema */
	     	 Dispositivo;	/* So utilizado quando for mensagem interna de tarefas */
    char	 NomeDisp[TAM_NOME_DISP];  /*Nome do Dispositivo usado p/ reconhecimento de eventos */

	union
	{
	  char MsgErrSis[TAM_MSG_ERR];
	  union 
	  {
	  	char  CharEv;
	  	int   IntEv;
	  	float FloatEv;
	  	long  LongEv;
	  	char  StringEv[10];
	  }ParEv[N_PAR_EV];
	}TipoMsg;
  }t_rec_ev;
  
/*---------------------- Mensagem de eventos ---------------------------------*/
typedef
  struct  MensagemEventos
  { /* mensagem de pedido de evento */
	char QueueHeader[QHDR_SIZE];
	t_rec_ev RecEv;
  } t_msg_ev;

/*---------------------- Buffer de mensagem de eventos -----------------------*/

/*-- Cabecalho --*/
typedef
  struct  CabecEventos
  { 
	int	CirculouBuffer;
	int	EndDisp;
  } t_cab_msg_ev;

/*-- Buffer --*/
typedef
  struct  BufferEventos
  { 
	t_cab_msg_ev	CabEv;
	t_rec_ev		RecEv[MAX_MSG_BUFFER];
  } t_buf_ev;

#endif	/* _EVENTOS_H */

