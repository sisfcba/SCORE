/******************************************************************************
             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 3.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: Remotas.h

	CONTEUDO	: Definicoes gerais da camada de aplicacao para comunicacao
				  com as remotas

	AUTOR		: Eduardo Pereira / Hevelton Araujo

	VERSAO		: 01 - 30/09/92

	HISTORICO DAS EDICOES

00 - Edicao Inicial									24/09/92		Pereira
01 - Alteracao nas estruturas de interface			30/09/92		H.Junior
02 - Inclusao de alteracoes para remota Atn7.0		18/11/94		Leonel
03 - Inclusao das alteracoes para a ALBRAS          05/01/96        Leonel
04 - CBA - Adaptacao para remota ATN7.0A da sala I  07/05/99        Leonel
05 - CBA - 125Ka aumento do numero de subredes > 16 08/01/02        Bandeira
06 - CBA - 125Ka Tratamento de 2 pcltas sala V      02/04/02        Leonel
-------------------------------------------------------------------------------
$Id: Remotas.h,v 1.4.4.2 2017/12/12 18:23:30 leo Exp $

$Log: Remotas.h,v $
Revision 1.4.4.2  2017/12/12 18:23:30  leo
Alteracao a pedido do Marco para usar entradas 1, 2 e 4 para teste do PF.
Alterada mascara da Atn7 para enviar valor da entrada de 0->1->0.

Revision 1.4.4.1  2015/06/30 22:44:54  clage
Alteracoes para sala II com ATN8 e expansao da base de dados.

Revision 1.4  2007/09/28 14:46:14  rogerio
Alteracao para incluir sala I com atn8

Revision 1.3  2004/04/26 14:23:25  leo
Inclusao de versao do firmware na mensagem de leitura de configuracao
da remota.

Revision 1.2  2004/04/08 19:20:59  leo
Inclusao da sala 125 kA VI.

******************************************************************************/

/*--- Verifica se ja foi incluido ---*/

#ifndef	_REMOTAS_H
	#define	_REMOTAS_H

#ifdef	ALCAN_ARATU_HS
  /* **** Compilacao condicional para alteracoes relativas a utilizacao de
		  um plc ao inves de uma rede de remotas ******* */
  #define		USA_PLC		1
#else
  /* **** Compilacao condicional para alteracoes relativas a rede ECHELON
		(remota ATN 7.0) ******* */
  #define		USA_REDE_ECHELON		1
#endif

#ifdef PROGRAMA_PRINCIPAL
	#define		DECL
#else
	#define		DECL	extern
#endif

#ifndef		CBA_120KAII_III
  #define		REMOTA_32_PONTOS		1
#endif

/* -- alteracao - inicio - 11/09/00 - Robson - Inclusao mensagem Atn8 -- */
/* -- Quando definido compila o codigo condicional para a remota ATN8.0 -- */
//#ifndef		USA_ATN8
//  #define		USA_ATN8	1
//  #ifndef	REMOTA_32_PONTOS
//	#define		REMOTA_32_PONTOS		1
//  #endif
//#endif
/* -- alteracao - fim - 11/09/00 - Robson - Inclusao mensagem Atn8 -- */

	/******************************/
	/*--- INCLUSAO DE ARQUIVOS ---*/
	/******************************/

#include <Definicao.h>
#include <queue.h>

	/***************************/
	/*------- MACROS GERAIS ---*/
	/***************************/

/* -- Alteracao - inicio - 02/04/2002 - Leonel - Inclusao tratamento de mais de um canal (pcltas) -- */
/* Macros para pegar canal e subrede da remota composto no formato CCSS em um short unsigned */
#define	PEGACANAL(canal)	((canal >> 8) andb 0xFF)
#define	PEGASUBREDE(canal)	(canal andb 0xFF)
/* -- Alteracao - fim - 02/04/2002 - Leonel - Inclusao tratamento de mais de um canal (pcltas) -- */

	/***************************/
	/*--- DEFINICOES GERAIS ---*/
	/***************************/

/*--- Numero maximo de racks por remota ---*/
#define MAX_RACKS					8
/* -- Numero de subredes definidas -- */
#define	MAX_SUBREDES				16	/*8*/

/*--- Numero maximo de canais por aplicacao ---*/
#ifdef	ALCOA_PROTOTIPO
  #define	MAX_CANAIS					1
#else
  #ifdef	USA_REDE_ECHELON
	#ifdef		ALBRAS
	  #define	MAX_CANAIS					1
	  /* -- Numero de nodos por subrede -- */
	  #define	NUM_MAX_NODOS_SUBREDE		60
	#else
	 #ifdef		CBA_120KAII_III
	  /* -- Cba -- */
/* -- Alteracao - inicio - 02/04/2002 - Leonel - Inclusao tratamento de mais de um canal (pcltas) -- */
	/* -- Para atender a sala V o numero de canais e' 2. Para as outras salas
	so' e' utilizado no entanto um canal -- */
/* -- Alteracao - inicio - 05/09/2002 - bandeira - aumentado para 4 pcltas -- */
	  #define	MAX_CANAIS					4
//	  #define	MAX_CANAIS					2
/* -- Alteracao - fim - 05/09/2002 - bandeira - aumentado para 4 pcltas -- */
  /* CBA - Fim: Alterado para tratar ATN7.0A na sala I - Leonel */
/* -- Alteracao - fim - 02/04/2002 - Leonel - Inclusao tratamento de mais de um canal (pcltas) -- */
	 #else
	  #define	MAX_CANAIS					1
	 #endif
	  #ifdef KONIN
	    /* -- Numero de nodos por subrede -- */
	    #define	NUM_MAX_NODOS_SUBREDE		50
	  #else
	    /* -- Numero de nodos por subrede -- */
	    #define	NUM_MAX_NODOS_SUBREDE		48
	  #endif
	#endif
  #else
	#define	MAX_CANAIS					1
  #endif
#endif

/*--- Numero maximo de comandos em uma lista de comandos ---*/
#define	MAX_CMD_LISTA				20

/*--- Tamanho maximo da area de dados ---*/
#define	MAX_TAM_DADOS				100

/*--- Nome da fila para transmissao DAS remotas PARA o host ---*/
#define	Q_LEIT_REDE					"QRRede00"

/*--- Nome das filas de transmissao DO host PARA remotas ---*/
/*--- Sera acrescentado o numero do canal logico no formato XX ---*/
#define	Q_ESCR_REDE					"QWRede"

/*--- Nome da tarefa de interface com o usuario ---*/
#define	TSK_INTERF_USU				"Atan/Score/InterUsu"

/*--- Codigos de erro ---*/
#define	REMOTA_FORA_LINHA		0x50
#define	ERRO_ESCR_FILA			0x51
#define	ERRO_ABRE_FILA			0x52
#define	FILA_NAO_PASSADA		0x53
#define	ERRO_SEND				0x54
#define	TSK_INTERF_AUSENTE		0x55
#define	REMOTA_VOLTOU			0x56
#define	ERRO_TAM_DADOS			0x57

/*--- Numero do nodo para o computador ---*/
#define	NUM_NODO_HOST			0xFF


#ifdef	USA_REDE_ECHELON

  /* Definicoes para variaveis de rede do tipo SNVT_LEV_DISC */
  #define		LEV_DISC_OFF		0
  #define		LEV_DISC_LOW		1
  #define		LEV_DISC_MEDIUM		2
  #define		LEV_DISC_HIGH		3
  #define		LEV_DISC_ON			4

  /* Tempos para remota self healing (mestre) */
  #define	TEMPO_VERIF_REDE_SH		150		/* Tempo entre tentativas de comunicacao
											entre master e slave (segs) */
  #define	TEMPO_VERIF_CONSERTO_SH	7200	/* Tempo para verificar se rede foi consertada (segs) */

 #ifdef	CBA_120KAII_III

  /*--- Define numero de pontos por grupo para a remota Atn 7.0 ---*/
  #define	TAM_GRUPO_REM			12

  /*--- Definicao de parametros de configuracao da remota Atn 7.0 ---*/
  #define	MAX_NODO_REMOTA			47		/* -- Maior no. de nodo de remota -- */
  #define	MASC_HAB_ENV_LIG1		0x03FF	/* -- Mascara p/ habilitar envio de
											  entrada ligada (16 primeiras) -- */
  #define	MASC_HAB_ENV_LIG2		0x0000	/* -- Mascara p/ habilitar envio de
											  entrada ligada (16 ultimas) -- */
  #define	MASC_HAB_ENV_DESLIG1	0x000F	/* -- Mascara p/ habilitar envio de
											  entrada desligada (16 primeiras) -- */
  #define	MASC_HAB_ENV_DESLIG2	0x0000	/* -- Mascara p/ habilitar envio de
	 										  entrada desligada (16 ultimas) -- */
  #define	MASC_HAB_SINAL_LIG1		0x0314	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada ligada (16 primeiras) -- */
  #define	MASC_HAB_SINAL_LIG2		0x0000	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada ligada (16 ultimas) -- */
  #define	MASC_HAB_SINAL_DESLIG1	0x0104	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada desligada (16 primeiras) -- */
  #define	MASC_HAB_SINAL_DESLIG2	0x0000	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada desligada (16 ultimas) -- */
  #define	MASC_SINALIZACAO1		0x0000	/* -- Mascara p/ definir saida a sinalizar
											  qdo. entrada variar (16 primeiras) -- */
  #define	MASC_SINALIZACAO2		0x0002	/* -- Mascara p/ definir saida a sinalizar
											  qdo. entrada variar (16 ultimas) -- */
  #define	CONF_I_O1				0x0C00	/* -- Configuracao de I/0 - bit=1->saida
											  bit=0->entrada -- */
  #define	CONF_I_O2				0x0FFF	/* -- Configuracao de I/0 - bit=1->saida
											  bit=0->entrada -- */
  #define	TEMPO_ENT_CHAVES		00		/* -- Tempo para considerar variacao
											  das entradas da chave (4 segundos) -- */

  #define	TEMPO_WATCHDOG_ATN7		90		/* -- Tempo em segundos para a remota
											  detectar que o micro esta fora da rede -- */

  #define	TEMPO_LIGA_PISCA_LAMP	BASE_TEMPO_REMOTA	/* -- Tempo de liga do pisca qdo. micro fora */
  #define	TEMPO_DESL_PISCA_LAMP	BASE_TEMPO_REMOTA	/* -- Tempo de desliga do pisca qdo. micro fora */

  /* -- definicoes apenas para as remotas de regulacao -- */
  #define	MASC_WATCHDOG_DESL1		0x0000	/* -- Mascara para desligar bits qdo.
											  micro sai da rede -- */
  #define	MASC_WATCHDOG_DESL2		0x0078	/* -- Mascara para desligar bits qdo.
											  micro sai da rede -- */
  #define	MASC_WATCHDOG_DESL1_S5	0x0c00	/* -- Mascara para desligar bits qdo.
											  micro sai da rede -- */
  #define	MASC_WATCHDOG_DESL2_S5	0x000F	/* -- Mascara para desligar bits qdo.
											  micro sai da rede -- */

  /* -- definicoes apenas para as remotas com point feeder -- */
  #define	MASC_PF_HAB_ENV_DESLIG1	0x010F	/* -- Mascara p/ habilitar envio de
											  entrada desligada (16 primeiras) -- */
  #define	MASC_PF_HAB_SINAL_LIG1		0x0314	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada ligada (16 primeiras) -- */
  #define	MASC_PF_HAB_SINAL_DESLIG1	0x0104	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada desligada (16 primeiras) -- */

  /* -- definicoes para remotas da Sala IV -- */
  /* -- Alteracao - Inicio - 24/09/2002 - Robson - Inclusao da botoeira de quebrada para sala IV -- */
  //#define	MASC_S4_HAB_ENV_LIG1		0x00F4	/* -- Mascara p/ habilitar envio de
  //				  								  entrada ligada (16 primeiras) -- */
  #define	MASC_S4_HAB_ENV_LIG1		0x00F5	/* -- Mascara p/ habilitar envio de
				  								  entrada ligada (16 primeiras) -- */
  /* -- Alteracao - Fim - 24/09/2002 - Robson - Inclusao da botoeira de quebrada para sala IV -- */
  #define	MASC_S4_HAB_ENV_LIG2		0x0000	/* -- Mascara p/ habilitar envio de
												  entrada ligada (16 ultimas) -- */
  #define	MASC_S4_HAB_ENV_DESLIG1		0x0004	/* -- Mascara p/ habilitar envio de
												  entrada desligada (16 primeiras) -- */
  #define	MASC_S4_HAB_ENV_DESLIG2		0x0000	/* -- Mascara p/ habilitar envio de
	 											  entrada desligada (16 ultimas) -- */
  /* -- Alteracao - Inicio - 24/09/2002 - Robson - Inclusao da botoeira de quebrada para sala IV -- */
  //#define	MASC_S4_HAB_SINAL_LIG1		0x0014	/* -- Mascara p/ habilitar sinalizacao
  //												  qdo. entrada ligada (16 primeiras) -- */
  #define	MASC_S4_HAB_SINAL_LIG1		0x0015	/* -- Mascara p/ habilitar sinalizacao
												  qdo. entrada ligada (16 primeiras) -- */
  /* -- Alteracao - Fim - 24/09/2002 - Robson - Inclusao da botoeira de quebrada para sala IV -- */
  #define	MASC_S4_HAB_SINAL_LIG2		0x0000	/* -- Mascara p/ habilitar sinalizacao
												  qdo. entrada ligada (16 ultimas) -- */
  #define	MASC_S4_HAB_SINAL_DESLIG1	0x0004	/* -- Mascara p/ habilitar sinalizacao
												  qdo. entrada desligada (16 primeiras) -- */
  #define	MASC_S4_HAB_SINAL_DESLIG2	0x0000	/* -- Mascara p/ habilitar sinalizacao
												  qdo. entrada desligada (16 ultimas) -- */
  #define	TEMPO_ESPERA_FALHA_MOVE	20		/* -- Tempo para verificar falha move em ticks */
  #define	TEMPO_ESPERA_ATIVA_MM	5		/* -- Tempo para esperar confirmacao de acionamento MM em ticks */

  /* -- definicoes apenas para sala 64KA  -- */
  /* -- Alteracao - Inicio - 01/11/2001 - habilitacao da chave de quebrada para sala 64ka --*/
  #define	MASC_S5_HAB_SINAL_LIG1		0x0017	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada ligada (16 primeiras) -- */
  /* -- Alteracao - Fim - 01/11/2001 - habilitacao da chave de quebrada para sala 64ka --*/
  #define	MASC_S5_HAB_SINAL_LIG2		0x0000	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada ligada (16 ultimas) -- */

/* -- Alteracao - Inicio - 26/01/2001 - Leonel - Tratamento atn8 para sala 86 ka -- */
/* -- alteracao - inicio - 11/09/00 - Robson - Inclusao mensagem Atn8 -- */
// definicoes para sala 86 Ka ATN 8.0
/*################################ ATN 8.0 ###########################*/
  /*--- Definicao de parametros de configuracao da remota Atn 7.0 ---*/
  #define	MASC_S6_HAB_ENV_LIG1		0x0EBF	/* -- Mascara p/ habilitar envio de
											  entrada ligada (16 primeiras) -- */
  #define	MASC_S6_HAB_ENV_LIG2		0x0000	/* -- Mascara p/ habilitar envio de
											  entrada ligada (16 ultimas) -- */
  #define	MASC_S6_HAB_ENV_DESLIG1		0x0401	/* -- Mascara p/ habilitar envio de
											  entrada desligada (16 primeiras) -- */
  #define	MASC_S6_HAB_ENV_DESLIG2		0x0000	/* -- Mascara p/ habilitar envio de
	 										  entrada desligada (16 ultimas) -- */
  #define	MASC_S6_HAB_SINAL_LIG1		0x0E83	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada ligada (16 primeiras) -- */
  #define	MASC_S6_HAB_SINAL_LIG2		0x0000	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada ligada (16 ultimas) -- */
  #define	MASC_S6_HAB_SINAL_DESLIG1	0x0401	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada desligada (16 primeiras) -- */
  #define	MASC_S6_HAB_SINAL_DESLIG2	0x0000	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada desligada (16 ultimas) -- */
  #define	MASC_S6_SINALIZACAO1		0x0000	/* -- Mascara p/ definir saida a sinalizar
												  qdo. entrada variar (16 primeiras) -- */
  #define	MASC_S6_SINALIZACAO2		0x0044	/* -- Mascara p/ definir saida a sinalizar
												  qdo. entrada variar (16 ultimas) -- */
  #define	CONF_I_O1_S6				0x0000	/* -- Configuracao de I/0 - bit=1->saida
												  bit=0->entrada -- */
  #define	CONF_I_O2_S6				0x0FFF	/* -- Configuracao de I/0 - bit=1->saida
												  bit=0->entrada -- */
//  #define	TEMPO_ENT_CHAVES_S6			00		/* -- Tempo para considerar variacao
//												  das entradas da chave (4 segundos) -- */
//
//  #define	TEMPO_WATCHDOG_ATN7_S6		5		/* -- Tempo em segundos para a remota
//												  detectar que o micro esta fora da rede -- */
//
//  #define	TEMPO_LIGA_PISCA_LAMP_S6	BASE_TEMPO_REMOTA	/* -- Tempo de liga do pisca qdo. micro fora */
//  #define	TEMPO_DESL_PISCA_LAMP_S6	BASE_TEMPO_REMOTA	/* -- Tempo de desliga do pisca qdo. micro fora */

  /* -- definicoes apenas para as remotas de regulacao -- */
  #define	MASC_WATCHDOG_DESL1_S6		0x0000	/* -- Mascara para desligar bits qdo.
												  micro sai da rede -- */
  #define	MASC_WATCHDOG_DESL2_S6		0x00FF	/* -- Mascara para desligar bits qdo.
												  micro sai da rede -- */

/* -- Alteracao - Inicio - 16/03/2001 - Leonel - Sala 86Ka AtnCA -- */
  #define	CONF_I_O1_S6_ATNCA			0x0FFF	/* -- Configuracao de I/0 - bit=1->saida
												  bit=0->entrada -- */
  #define	CONF_I_O2_S6_ATNCA			0x0FFF	/* -- Configuracao de I/0 - bit=1->saida
												  bit=0->entrada -- */
  /* -- Configuracao do pisca da saida de alimentacao qdo micro fora -- */
  #define	MASC_PISC1_WATCH_S6_ATNCA	0x0000	/* Pisca sirenes */
  #define	MASC_PISC2_WATCH_S6_ATNCA	0x00CF
  #define	TEMPO_LIGA_PISCWATCH_S6_ATNCA		(BASE_TEMPO_REMOTA*2) /* 2 segundos */
  #define	TEMPO_DESLIGA_PISCWATCH_S6_ATNCA	(BASE_TEMPO_REMOTA*8) /* 8 segundos */
/* -- Alteracao - Fim - 16/03/2001 - Leonel - Sala 86Ka AtnCA -- */

/*################################ ATN 8.0 ###########################*/
/* -- alteracao - fim - 11/09/00 - Robson - Inclusao mensagem Atn8 -- */
/* -- Alteracao - Fim - 26/01/2001 - Leonel - Tratamento atn8 para sala 86 ka -- */
/* -- alteracao - inicio - 09/04/02 - Robson - Inclusao mensagem Atn8 -- */
// definicoes para sala 125Ka ATN 8.0
/*################################ ATN 8.0 ###########################*/
/* -- Alteracao - Inicio - Robson - 22/04/2002 - algoritmo de PF na Atn8.0 -- */
  #define	NUM_PASSOS_SEQ				4	// passos de alimentacao na remota
/* -- Alteracao - Fim - Robson - 22/04/2002 - algoritmo de PF na Atn8.0 -- */


  /*--- Definicao de parametros de configuracao da remota Atn 7.0 ---*/
  #define	MASC_S7_HAB_ENV_LIG1		0x00FF	/* -- Mascara p/ habilitar envio de
											  entrada ligada (16 primeiras) -- */
  #define	MASC_S7_HAB_ENV_LIG2		0x0000	/* -- Mascara p/ habilitar envio de
											  entrada ligada (16 ultimas) -- */
  #define	MASC_S7_HAB_ENV_DESLIG1		0x00FE	/* -- Mascara p/ habilitar envio de
											  entrada desligada (16 primeiras) -- */
  #define	MASC_S7_HAB_ENV_DESLIG2		0x0000	/* -- Mascara p/ habilitar envio de
	 										  entrada desligada (16 ultimas) -- */
/* -- alteracao - inicio - 25/11/2002 - Leonel - separacao sobe e desce anodo -- */
  //  #define	MASC_S7_HAB_SINAL_LIG1		0x00F3	/* -- Mascara p/ habilitar sinalizacao
  #define	MASC_S7_HAB_SINAL_LIG1		0x00D3	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada ligada (16 primeiras) -- */
  #define	MASC_S7_HAB_SINAL_LIG2		0x0000	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada ligada (16 ultimas) -- */
  // #define	MASC_S7_HAB_SINAL_DESLIG1	0x0072	/* -- Mascara p/ habilitar sinalizacao
  #define	MASC_S7_HAB_SINAL_DESLIG1	0x0052	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada desligada (16 primeiras) -- */
/* -- alteracao - fim - 25/11/2002 - Leonel - separacao sobe e desce anodo -- */
  #define	MASC_S7_HAB_SINAL_DESLIG2	0x0000	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada desligada (16 ultimas) -- */
  #define	MASC_S7_SINALIZACAO1		0x0000	/* -- Mascara p/ definir saida a sinalizar
												  qdo. entrada variar (16 primeiras) -- */
  #define	MASC_S7_SINALIZACAO2		0x0004	/* -- Mascara p/ definir saida a sinalizar
												  qdo. entrada variar (16 ultimas) -- */
  #define	CONF_I_O1_S7				0x0F00	/* -- Configuracao de I/0 - bit=1->saida
												  bit=0->entrada -- */
  #define	CONF_I_O2_S7				0x0FFF	/* -- Configuracao de I/0 - bit=1->saida
												  bit=0->entrada -- */
//  #define	TEMPO_ENT_CHAVES_S7			00		/* -- Tempo para considerar variacao
//												  das entradas da chave (4 segundos) -- */
//
//  #define	TEMPO_WATCHDOG_ATN7_S7		5		/* -- Tempo em segundos para a remota
//												  detectar que o micro esta fora da rede -- */
//
//  #define	TEMPO_LIGA_PISCA_LAMP_S7	BASE_TEMPO_REMOTA	/* -- Tempo de liga do pisca qdo. micro fora */
//  #define	TEMPO_DESL_PISCA_LAMP_S7	BASE_TEMPO_REMOTA	/* -- Tempo de desliga do pisca qdo. micro fora */

  /* -- definicoes apenas para as remotas de regulacao -- */
  #define	MASC_WATCHDOG_DESL1_S7		0x0F00	/* -- Mascara para desligar bits qdo.
												  micro sai da rede -- */
  #define	MASC_WATCHDOG_DESL2_S7		0x0FFF	/* -- Mascara para desligar bits qdo.
												  micro sai da rede -- */

/* -- Alteracao - Inicio - 16/03/2001 - Leonel - Sala 125Ka AtnCA -- */
  #define	CONF_I_O1_S7_ATNCA			0x0F00	/* -- Configuracao de I/0 - bit=1->saida
												  bit=0->entrada -- */
  #define	CONF_I_O2_S7_ATNCA			0x0FFF	/* -- Configuracao de I/0 - bit=1->saida
												  bit=0->entrada -- */
  /* -- Configuracao do pisca da saida de alimentacao qdo micro fora -- */
  #define	MASC_PISC1_WATCH_S7_ATNCA	0x0F00	/* Pisca sirenes */
  #define	MASC_PISC2_WATCH_S7_ATNCA	0x008F
  #define	TEMPO_LIGA_PISCWATCH_S7_ATNCA		(BASE_TEMPO_REMOTA*2) /* 2 segundos */
  #define	TEMPO_DESLIGA_PISCWATCH_S7_ATNCA	(BASE_TEMPO_REMOTA*8) /* 8 segundos */

  #define	TEMPO_WATCHDOG_ATN8_S7		5		/* -- Tempo em segundos para a remota
											  detectar que o micro esta fora da rede -- */
/* -- Alteracao - Fim - 16/03/2001 - Leonel - Sala 125Ka AtnCA -- */

  /* ####################### Sala 125 kA I, VI, VII - reducao 1, 8, 9 ############################ */
  /*--- Definicao de parametros de configuracao da remota Atn 8.0 ---*/
  #define	MASC_S8_HAB_ENV_LIG1		0x00FF	/* -- Mascara p/ habilitar envio de
											  entrada ligada (12 primeiras) -- */
  #define	MASC_S8_HAB_ENV_LIG2		0x0000	/* -- Mascara p/ habilitar envio de
											  entrada ligada (12 ultimas) -- */
  #define	MASC_S8_HAB_ENV_DESLIG1		0x00FE	/* -- Mascara p/ habilitar envio de
											  entrada desligada (12 primeiras) -- */
  #define	MASC_S8_HAB_ENV_DESLIG2		0x0000	/* -- Mascara p/ habilitar envio de
	 										  entrada desligada (12 ultimas) -- */
  #define	MASC_S8_HAB_SINAL_LIG1		0x00D3	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada ligada (12 primeiras) -- */
  #define	MASC_S8_HAB_SINAL_LIG2		0x0000	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada ligada (12 ultimas) -- */
  #define	MASC_S8_HAB_SINAL_DESLIG1	0x0052	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada desligada (12 primeiras) -- */
  #define	MASC_S8_HAB_SINAL_DESLIG2	0x0000	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada desligada (12 ultimas) -- */
  #define	MASC_S8_SINALIZACAO1		0x0000	/* -- Mascara p/ definir saida a sinalizar
												  qdo. entrada variar (12 primeiras) -- */
  #define	MASC_S8_SINALIZACAO2		0x0004	/* -- Mascara p/ definir saida a sinalizar
												  qdo. entrada variar (12 ultimas) -- */
  #define	CONF_I_O1_S8				0x0F00	/* -- Configuracao de I/0 - bit=1->saida
												  bit=0->entrada -- */
  #define	CONF_I_O2_S8				0x0FFF	/* -- Configuracao de I/0 - bit=1->saida
												  bit=0->entrada -- */
  /* -- definicoes apenas para as remotas de regulacao -- */
  #define	MASC_WATCHDOG_DESL1_S8		0x0F00	/* -- Mascara para desligar bits qdo.
												  micro sai da rede -- */
  #define	MASC_WATCHDOG_DESL2_S8		0x0FFF	/* -- Mascara para desligar bits qdo.
												  micro sai da rede -- */

/* -- Alteracao - Inicio - 16/03/2001 - Leonel - Sala 125Ka AtnCA -- */
  #define	CONF_I_O1_S8_ATNCA			0x0F00	/* -- Configuracao de I/0 - bit=1->saida
												  bit=0->entrada -- */
  #define	CONF_I_O2_S8_ATNCA			0x0FFF	/* -- Configuracao de I/0 - bit=1->saida
												  bit=0->entrada -- */
  /* -- Configuracao do pisca da saida de alimentacao qdo micro fora -- */
  #define	MASC_PISC1_WATCH_S8_ATNCA	0x0F00	/* Pisca sirenes */
  #define	MASC_PISC2_WATCH_S8_ATNCA	0x008F
  #define	TEMPO_LIGA_PISCWATCH_S8_ATNCA		(BASE_TEMPO_REMOTA*2) /* 2 segundos */
  #define	TEMPO_DESLIGA_PISCWATCH_S8_ATNCA	(BASE_TEMPO_REMOTA*8) /* 8 segundos */

  #define	TEMPO_WATCHDOG_ATN8_S8		5		/* -- Tempo em segundos para a remota
											  detectar que o micro esta fora da rede -- */

  /* ####################### Sala 125 kA II - reducao 2 ############################ */
  /*--- Definicao de parametros de configuracao da remota Atn 8.0 ---*/
  #define	MASC_S2_HAB_ENV_LIG1		0x0FFF	/* -- Mascara p/ habilitar envio de
											  entrada ligada (12 primeiras) -- */
  #define	MASC_S2_HAB_ENV_LIG2		0x0000	/* -- Mascara p/ habilitar envio de
											  entrada ligada (12 ultimas) -- */
  #define	MASC_S2_HAB_ENV_DESLIG1		0x0FFE	/* -- Mascara p/ habilitar envio de
											  entrada desligada (12 primeiras) -- */
  #define	MASC_S2_HAB_ENV_DESLIG2		0x0000	/* -- Mascara p/ habilitar envio de
	 										  entrada desligada (12 ultimas) -- */
  #define	MASC_S2_HAB_SINAL_LIG1		0x0043	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada ligada (12 primeiras) -- */
  #define	MASC_S2_HAB_SINAL_LIG2		0x0000	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada ligada (12 ultimas) -- */
  #define	MASC_S2_HAB_SINAL_DESLIG1	0x0002	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada desligada (12 primeiras) -- */
  #define	MASC_S2_HAB_SINAL_DESLIG2	0x0000	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada desligada (12 ultimas) -- */
  #define	MASC_S2_SINALIZACAO1		0x0000	/* -- Mascara p/ definir saida a sinalizar
												  qdo. entrada variar (12 primeiras) -- */
  #define	MASC_S2_SINALIZACAO2		0x0040	/* -- Mascara p/ definir saida a sinalizar
												  qdo. entrada variar (12 ultimas) -- */
  #define	CONF_I_O1_S2				0x0000	/* -- Configuracao de I/0 - bit=1->saida
												  bit=0->entrada -- */
  #define	CONF_I_O2_S2				0x0FFF	/* -- Configuracao de I/0 - bit=1->saida
												  bit=0->entrada -- */
  /* -- definicoes apenas para as remotas de regulacao -- */
  #define	MASC_WATCHDOG_DESL1_S2		0x0000	/* -- Mascara para desligar bits qdo.
												  micro sai da rede -- */
  #define	MASC_WATCHDOG_DESL2_S2		0x0FFF	/* -- Mascara para desligar bits qdo.
												  micro sai da rede -- */

/* -- Alteracao - Inicio - 16/03/2001 - Leonel - Sala 125Ka AtnCA -- */
  #define	CONF_I_O1_S2_ATNCA			0x0000	/* -- Configuracao de I/0 - bit=1->saida
												  bit=0->entrada -- */
  #define	CONF_I_O2_S2_ATNCA			0x0FFF	/* -- Configuracao de I/0 - bit=1->saida
												  bit=0->entrada -- */
  /* -- Configuracao do pisca da saida de alimentacao qdo micro fora -- */
  #define	MASC_PISC1_WATCH_S2_ATNCA	0x0000	/* Pisca sirenes */
  #define	MASC_PISC2_WATCH_S2_ATNCA	0x008F
  #define	TEMPO_LIGA_PISCWATCH_S2_ATNCA		(BASE_TEMPO_REMOTA*2) /* 2 segundos */
  #define	TEMPO_DESLIGA_PISCWATCH_S2_ATNCA	(BASE_TEMPO_REMOTA*8) /* 8 segundos */

  #define	TEMPO_WATCHDOG_ATN8_S2		5		/* -- Tempo em segundos para a remota
											  detectar que o micro esta fora da rede -- */

/*################################ ATN 8.0 ###########################*/

 #else
  #ifdef	KONIN
  /*--- Define numero de pontos por grupo para a remota Atn 7.0 ---*/
  #define	TAM_GRUPO_REM			16

  /*--- Definicao de parametros de configuracao da remota Atn 7.0 ---*/
  #define	MAX_NODO_REMOTA			52		/* -- Maior no. de nodo de remota -- */
  #define	MASC_HAB_ENV_LIG1		0x0FFF	/* -- Mascara p/ habilitar envio de
											  entrada ligada (16 primeiras) -- */
  #define	MASC_HAB_ENV_LIG2		0x0000	/* -- Mascara p/ habilitar envio de
											  entrada ligada (16 ultimas) -- */
  #define	MASC_HAB_ENV_DESLIG1	0x0CC4	/* -- Mascara p/ habilitar envio de
											  entrada desligada (16 primeiras) -- */
  #define	MASC_HAB_ENV_DESLIG2	0x0000	/* -- Mascara p/ habilitar envio de
	 										  entrada desligada (16 ultimas) -- */
  #define	MASC_HAB_SINAL_LIG1		0x03FC	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada ligada (16 primeiras) -- */
  #define	MASC_HAB_SINAL_LIG2		0x0000	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada ligada (16 ultimas) -- */
  #define	MASC_HAB_SINAL_DESLIG1	0x0084	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada desligada (16 primeiras) -- */
  #define	MASC_HAB_SINAL_DESLIG2	0x0000	/* -- Mascara p/ habilitar sinalizacao
											  qdo. entrada desligada (16 ultimas) -- */
  #define	MASC_SINALIZACAO1		0x4000	/* -- Mascara p/ definir saida a sinalizar
											  qdo. entrada variar (16 primeiras) -- */
  #define	MASC_SINALIZACAO2		0x0000	/* -- Mascara p/ definir saida a sinalizar
											  qdo. entrada variar (16 ultimas) -- */
  #define	CONF_I_O1				0xF000	/* -- Configuracao de I/0 - bit=1->saida
											  bit=0->entrada -- */
  #define	CONF_I_O2				0x00FF	/* -- Configuracao de I/0 - bit=1->saida
											  bit=0->entrada -- */
  #define	MASC_ENT_TEMP1			0x0C84	/* -- Mascara p/ definir entrada temporizada
											  (16 primeiras) -- */
  #define	MASC_ENT_TEMP2			0x0000	/* -- Mascara p/ definir entrada temporizada
	 										  (16 ultimas) -- */
  #define	TEMPO_ENT_CHAVES		60		/* -- Tempo para considerar variacao
											  das entradas da chave (3 segundos) -- */

  #define	TEMPO_WATCHDOG_ATN7		90		/* -- Tempo em segundos para a remota
											  detectar que o micro esta fora da rede -- */
  #define	MASC_WATCHDOG_DESL1		0x0000	/* -- Mascara para desligar bits qdo.
											  micro sai da rede -- */
  #define	MASC_WATCHDOG_DESL2		0x0000	/* -- Mascara para desligar bits qdo.
											  micro sai da rede -- */

  #define	TEMPO_LIGA_PISCA_LAMP	10		/* -- Tempo de liga do pisca qdo. micro fora */
  #define	TEMPO_DESL_PISCA_LAMP	10		/* -- Tempo de desliga do pisca qdo. micro fora */
  #define	TEMPO_ESPERA_FALHA_MOVE	12		/* -- Tempo para verificar falha move em ticks */
  #define	TEMPO_ESPERA_ATIVA_MM	4		/* -- Tempo para esperar confirmacao de acionamento MM em ticks */

  #else
	#ifdef	ALBRAS
	  /*--- Define numero de pontos por grupo para a remota Atn 7.0 ---*/
	  #define	TAM_GRUPO_REM			16

	  /* -- Tempo em segundos para a remota detectar que o micro esta fora da rede -- */
	  #define	TEMPO_WATCHDOG_ATN7		90

	  /*--- Definicao de parametros de configuracao da remota Atn 7.0 ---*/
	  #define	MAX_NODO_REMOTA			62		/* -- Maior no. de nodo de remota -- */

	  /* -- Definicoes para remota de CUBA -- */
	  #define	MASC_HAB_ENV_LIG1		0x0FFF	/* -- Mascara p/ habilitar envio de
												  entrada ligada (16 primeiras) -- */
	  #define	MASC_HAB_ENV_LIG2		0x0002	/* -- Mascara p/ habilitar envio de
												  entrada ligada (16 ultimas) -- */
	  #define	MASC_HAB_ENV_DESLIG1	0x00BF	/* -- Mascara p/ habilitar envio de
												  entrada desligada (16 primeiras) -- */
	  #define	MASC_HAB_ENV_DESLIG2	0x0000	/* -- Mascara p/ habilitar envio de
		 										  entrada desligada (16 ultimas) -- */
	  #define	MASC_HAB_SINAL_LIG1		0x003F	/* -- Mascara p/ habilitar sinalizacao
												  qdo. entrada ligada (16 primeiras) -- */
	  #define	MASC_HAB_SINAL_LIG2		0x0000	/* -- Mascara p/ habilitar sinalizacao
												  qdo. entrada ligada (16 ultimas) -- */
	  #define	MASC_HAB_SINAL_DESLIG1	0x0027	/* -- Mascara p/ habilitar sinalizacao
												  qdo. entrada desligada (16 primeiras) -- */
	  #define	MASC_HAB_SINAL_DESLIG2	0x0000	/* -- Mascara p/ habilitar sinalizacao
												  qdo. entrada desligada (16 ultimas) -- */
	  #define	MASC_SINALIZACAO1		0x0000	/* -- Mascara p/ definir saida a sinalizar
												  qdo. entrada variar (16 primeiras) -- */
	  #define	MASC_SINALIZACAO2		0x0004	/* -- Mascara p/ definir saida a sinalizar
												  qdo. entrada variar (16 ultimas) -- */
	  #define	CONF_I_O1				0xF000	/* -- Configuracao de I/0 - bit=1->saida
												  bit=0->entrada -- */
	  #define	CONF_I_O2				0x00FF	/* -- Configuracao de I/0 - bit=1->saida
												  bit=0->entrada -- */
	  #define	MASC_ENT_TEMP1			0x0018	/* -- Mascara p/ definir entrada temporizada
												  (16 primeiras) -- */
	  #define	MASC_ENT_TEMP2			0x0000	/* -- Mascara p/ definir entrada temporizada
		 										  (16 ultimas) -- */
	  #define	TEMPO_ENT_CHAVES		80		/* -- Tempo para considerar variacao
												  das entradas da chave (4 segundos) -- */
	
	  #define	MASC_WATCHDOG_DESL1		0x0000	/* -- Mascara para desligar bits qdo.
												  micro sai da rede -- */
	  #define	MASC_WATCHDOG_DESL2		0x0000	/* -- Mascara para desligar bits qdo.
												  micro sai da rede -- */
	  /* Desliga lampada de check qdo. sair de rede */
	  #define	CUBA_MASC_WATCHDOG_DESL1	0x0000	/* -- Mascara para desligar bits qdo.
											  micro sai da rede -- */
	  #define	CUBA_MASC_WATCHDOG_DESL2	0x0020	/* -- Mascara para desligar bits qdo.
												  micro sai da rede -- */
	  #define	TEMPO_LIGA_PISCA_LAMP	10		/* -- Tempo de liga do pisca qdo. micro fora */
	  #define	TEMPO_DESL_PISCA_LAMP	10		/* -- Tempo de desliga do pisca qdo. micro fora */
	  #define	TEMPO_ESPERA_FALHA_MOVE	12		/* -- Tempo para verificar falha move em ticks */
	  #define	TEMPO_ESPERA_FALHA_ALIM	8		/* -- Tempo para verificar falha alimentacao em ticks */

	  /* -- Definicoes para remota de PAL -- */
	  #define	PAL_MASC_HAB_ENV_LIG1		0x0007	/* -- Mascara p/ habilitar envio de
												  entrada ligada (16 primeiras) -- */
	  #define	PAL_MASC_HAB_ENV_LIG2		0x0000	/* -- Mascara p/ habilitar envio de
												  entrada ligada (16 ultimas) -- */
	  #define	PAL_MASC_HAB_ENV_DESLIG1	0x0000	/* -- Mascara p/ habilitar envio de
												  entrada desligada (16 primeiras) -- */
	  #define	PAL_MASC_HAB_ENV_DESLIG2	0x0000	/* -- Mascara p/ habilitar envio de
		 										  entrada desligada (16 ultimas) -- */
	  #define	PAL_MASC_HAB_SINAL_LIG1		0x0000	/* -- Mascara p/ habilitar sinalizacao
												  qdo. entrada ligada (16 primeiras) -- */
	  #define	PAL_MASC_HAB_SINAL_LIG2		0x0000	/* -- Mascara p/ habilitar sinalizacao
												  qdo. entrada ligada (16 ultimas) -- */
	  #define	PAL_MASC_HAB_SINAL_DESLIG1	0x0000	/* -- Mascara p/ habilitar sinalizacao
												  qdo. entrada desligada (16 primeiras) -- */
	  #define	PAL_MASC_HAB_SINAL_DESLIG2	0x0000	/* -- Mascara p/ habilitar sinalizacao
												  qdo. entrada desligada (16 ultimas) -- */
	  #define	PAL_MASC_SINALIZACAO1		0x0000	/* -- Mascara p/ definir saida a sinalizar
												  qdo. entrada variar (16 primeiras) -- */
	  #define	PAL_MASC_SINALIZACAO2		0x0000	/* -- Mascara p/ definir saida a sinalizar
												  qdo. entrada variar (16 ultimas) -- */
	  #define	PAL_CONF_I_O1				0xFF00	/* -- Configuracao de I/0 - bit=1->saida
												  bit=0->entrada -- */
	  #define	PAL_CONF_I_O2				0xFFFF	/* -- Configuracao de I/0 - bit=1->saida
												  bit=0->entrada -- */
	  #define	PAL_MASC_WATCHDOG_DESL1		0xFF00	/* -- Mascara para desligar bits qdo.
												  micro sai da rede -- */
	  #define	PAL_MASC_WATCHDOG_DESL2		0x7F00	/* -- Mascara para desligar bits qdo.
												  micro sai da rede -- */

	  /* -- Mascaras para piscar sirene e lampada parada de controle qdo micro
			sair fora de rede nos PALs -- */
	  #define	PAL_MASC_PISCA_1			0x0000
	  #define	PAL_MASC_PISCA_2			0x8010
	  #define	PAL_TEMPO_PISCA_LIGA		40		//2 segundos
	  #define	PAL_TEMPO_PISCA_DESL		160		//8 segundos

	  /* -- Mascara para desligar sirene e lampada de parada qdo micro volta a rede -- */
	  #define	PAL_MASC_WATCHDOG_LIG1		0x0000	/* -- Mascara para ligar bits qdo.
												  	micro sai da rede e desligar qdo volta -- */
	  #define	PAL_MASC_WATCHDOG_LIG2		0x8010	/* -- Mascara para ligar bits qdo.
												  	micro sai da rede e desligar qdo volta -- */
	#endif
  #endif
 #endif
#else
  #ifdef	ALCAN_ARATU_HS
	  /*--- Define numero de pontos por grupo para a remota Atn 7.0 ---*/
	  #define	TAM_GRUPO_REM			16

	  /* -- Tempo em segundos para a remota detectar que o micro esta fora da rede -- */
	  #define	TEMPO_WATCHDOG_ATN7		90

	  /*--- Definicao de parametros de configuracao da remota Atn 7.0 ---*/
	  #define	MAX_NODO_REMOTA			32		/* -- Maior no. de nodo de remota -- */

  #endif
#endif


	/*****************************************/
	/*--- TIPOS POSSIVEIS PARA AS REMOTAS ---*/
	/*****************************************/

#define	MODULO_49					0
#define	MODULO_50					1
#define	MODULO_51					2
#define	MODULO_77					3
#define	MODULO_78					4
#define	MODULO_79					5
#define	RESERVADO					6
#define	MODULO_AUSENTE				7


	/***********************************/
	/*--- COMANDOS MICRO --> REMOTA ---*/
	/***********************************/

#define ESCREVE_SAIDA_DIG			0x01
#define LE_RACK_DIG					0x02
#define LIGA_SAIDA_TEMP				0x03
#define DESLIGA_SAIDA_TEMP			0x04
#define PISCA_SAIDA					0x05
#define BLOQUEIA_SAIDA_TEMP			0x06
#define LISTA_ACOES					0x07
#define CONFIGURA_REMOTA			0x08
#define LE_CONFIGURACAO_REMOTA		0x09
#define	ESCREVE_TAB_DADOS			0x0A
#ifdef	USA_REDE_ECHELON
  #define	WATCHDOG_REMOTA			0x0B
#endif
#define	CONFIGURA_SH				0x0C

	/*********************************************************************/
	/* -- SUB_COMANDOS DA TABELA DE DADOS, MICRO --> REMOTA           -- */
	/* -- PARA IMPLEMENTAR SEQUENCIAMENTO DE ALIMENTACAO POINT FEEDER -- */
	/*********************************************************************/
#ifdef		ALBRAS
  #define		CONFIGURA_PASSOS_SEQ	0x01
  #define		CONFIGURA_RESTO_SEQ		0x02
  #define		EXECUTA_SEQUENCIA		0x03
  #define		SELECIONA_QUEBRADOR		0x04
#endif
#ifdef		CBA_120KAII_III
  #define		CONFIGURA_PASSOS_SEQ	0x01 // este tb e o comando de configuracao
  #define		EXECUTA_SEQUENCIA		0x02
  #define		HABILITA_PISTAO			0x03
  #define		DESABILITA_PISTAO		0x04
  #define		CONFIGURA_ESPECIAL		0x05
  #define		LE_CONF_ESPECIAL		0x06
  #define		LE_CONF_ALIMENT			0x07
#endif
#ifdef		KONIN
  #define		CONFIGURA_BARRA_LATERAL	0x01
  #define		EXECUTA_SEQUENCIA		0x02
  #define		HABILITA_PISTAO			0x03
  #define		DESABILITA_PISTAO		0x04
  #define		CONFIGURA_ESPECIAL		0x05
  #define		FALTA_MOTOR_MACACO		0x06
  #define		LE_CONF_ESPECIAL		0x07
  #define		LE_CONF_ALIMENT			0x08
#endif
/* -- alteracao - inicio - 11/09/00 - Robson - Inclusao mensagem Atn8 -- */
  #define		CONFIGURA_ATN8			0x10
  #define		LE_CONFIGURA_ATN8		0x11
/* -- alteracao - fim - 11/09/00 - Robson - Inclusao mensagem Atn8 -- */


	/********************************************************/
	/*--- RESPOSTAS REMOTA --> MICRO ( comando orb 0x40) ---*/
	/********************************************************/

#define RESP_ESCREVE_SAIDA_DIG		0x41
#define RESP_LE_RACK_DIG			0x42
#define RESP_LIGA_SAIDA_TEMP		0x43
#define RESP_DESLIGA_SAIDA_TEMP		0x44
#define RESP_PISCA_SAIDA			0x45
#define RESP_BLOQUEIA_SAIDA_TEMP	0x46
#define RESP_LISTA_ACOES			0x47
#define RESP_CONFIGURA_REMOTA		0x48
#define RESP_LE_CONFIGURACAO_REMOTA	0x49
#define	RESP_ESCREVE_TAB_DADOS		0x4A
#ifdef	USA_REDE_ECHELON
  #define	RESP_WATCHDOG_REMOTA	0x4B
#endif
#define	RESP_CONFIGURA_SH			0x4C
#ifdef		KONIN
	/*********************************************************************/
	/* -- SUB_COMANDOS DA TABELA DE DADOS, REMOTA --> MICRO           -- */
	/*********************************************************************/
  #define	RESP_LE_CONF_ESPECIAL	0x47
  #define	RESP_LE_CONF_ALIMENTE	0x48
#endif

	/***********************************/
	/*--- COMANDOS REMOTA --> MICRO ---*/
	/***********************************/

#define INF_ALTERACAO_ENT_DIG		0x10
#define	REMOTA_ESC_TAB_DADOS		0x11
#define	ESTADO_ATUAL_REDE			0x12
#define	FALHA_REDE_SH				0x13
/* -- alteracao - inicio - 11/09/00 - Robson - Inclusao mensagem Atn8 -- */
#define	INF_ANA_DIG					0x14
/* -- alteracao - fim - 11/09/00 - Robson - Inclusao mensagem Atn8 -- */
/* -- alteracao - inicio - 23/11/00 - Leonel - Inclusao mensagem INF_TEMP_ANA -- */
#define	INF_TEMP_ANA				0x15
/* -- alteracao - fim - 23/11/00 - Leonel - Inclusao mensagem INF_TEMP_ANA -- */

	/*******************************************************/
	/*--- RESPOSTAS MICRO --> REMOTA (comando orb 0x40) ---*/
	/*******************************************************/

#define RESP_INF_ALTERACAO_ENT_DIG	0x50
#define	RESP_REMOTA_ESC_TAB_DADOS	0x51

	/*******************************************************************/
	/*--- MASCARA PARA ACESSAR OS BITS ESPECIAIS DO BYTE DE COMANDO ---*/
	/*******************************************************************/

#ifdef		ALBRAS
  /* -- Marca comando liga/desliga temporizado para ciranda de bits -- */
  #define	BIT_CIRANDA				0x80
#endif
#define	BIT_RESPOSTA				0x40
#define	BIT_BROADCAST				0x20

	/*******************************/
	/*--- STATUS DAS TRANSACOES ---*/
	/*******************************/

#define STATUS_OK					0
#define STATUS_ERRO					1
#define	STATUS_TIMEOUT				2


	/**************************************/
	/*--- TIPOS DE SERVICO DISPONIVEIS ---*/
	/**************************************/

#define	ENVIA_PACOTE			0
#define	RECEBE_PACOTE			1
#define	REC_NODOS_ATIVOS		2

#ifdef	USA_REDE_ECHELON
  #define	ENVIA_ECHELON_NV	3
  #define	RECEBE_ECHELON_NV	4
#endif

	/*******************************************/
	/*--- TAMANHO DAS ESTRUTURAS DE COMANDO ---*/
	/*******************************************/

#define	TAM_CAB_MSG				(sizeof (struct Cabecalho))
#define	TAM_CAB_CMD				(sizeof (struct CabComando))
#define	TAM_CAB_RSP				(sizeof (struct CabResposta))
#define	TAM_COMANDO				(sizeof (struct Comando))
#define	TAM_RESPOSTA			(sizeof (struct Resposta))
#define	TAM_MSG_REDE			(sizeof (struct ComunicRede))
#define	TAM_MSG_USU				(sizeof (struct ComunicUsuario))
#define	TAM_ESC_DIG				(sizeof (struct EscreveSaidaDig))
#define	TAM_LER_DIG				(sizeof (struct RespostaLeRackDig))
#define TAM_LIG_TMP				(sizeof (struct LigaSaidaTemp))
#define TAM_DES_TMP				(sizeof (struct DesligaSaidaTemp))
#define TAM_PIS_SAI				(sizeof (struct PiscaSaida))
#define TAM_BLQ_SAI				(sizeof (struct BloqueiaSaidaTemp))
#define	TAM_CNF_REM				(sizeof (struct ConfiguraRemota))
#define	TAM_LER_CNF				(sizeof (struct LeConfRemota))
#define	TAM_RSP_CNF				(sizeof (struct RespostaLeConfig))
#define	TAM_LST_COM				(sizeof (struct ListaAcoes))
#define	TAM_T_DADOS				(sizeof (struct TabelaDeDados))
#define	TAM_INF_DIG				(sizeof (struct InfAltEntDig))
#define	TAM_CNF_SH				(sizeof (struct ConfigSelfHeal))


	/****************************/
	/*--- DEFINICAO DE TIPOS ---*/
	/****************************/


/*--- Cabecalho da mensagem de interface entre USUARIO/APLICACAO/REDE ---*/
typedef
  struct Cabecalho
  {
	char		TipoServico;
	int			TamFrame;
	int			Canal;
	unsigned	char NumNodoSrc;
	unsigned	char NumNodoDst;
	char		Reserva[10];
  } t_cabecalho;

#ifndef	T_MASCARA_BITS
  #define	T_MASCARA_BITS

  /*--- Mascara de bits para comandos de ligar/desligar saidas ---*/
  typedef
	struct MascaraBits
	{
	  unsigned int Mascara1;
	  unsigned int Mascara2;
	} t_mascara_bits;
#endif

/*--- Data para comandos de configuracao da remota ---*/
typedef
  struct Data
  {
	char	Seg;
	char	Min;
	char	Hora;
	char	DiaMes;
	char	Mes;
	char	Ano;
	char	DiaSemana;
  } t_data;

/*--- Cabecalho dos comandos enviados para a remota ---*/
typedef
  struct CabComando
  {
	unsigned char Cmd;
	unsigned char Tamanho;
	unsigned char Transacao;
  } t_cab_cmd;

/*--- Comando para escrever saidas digitais ---*/
typedef
  struct EscreveSaidaDig
  {
	unsigned char	Rack;
	t_mascara_bits	MascaraLiga;
	t_mascara_bits	MascaraDesliga;
  } t_esc_saida_dig;

/*--- Comando para ler entradas/saidas digitais ---*/
typedef
  struct LeRackDig
  {
	unsigned char RackInicio;
	unsigned char RackFim;
  } t_le_digitais;

/*--- Comando para ligar saida temporizada ---*/
typedef
  struct LigaSaidaTemp
  {
	unsigned char	Rack;
	t_mascara_bits	MascaraLiga;
	unsigned int	Tempo;
  } t_liga_saida_temp;

/*--- Comando para desligar saida temporizada ---*/
typedef
  struct DesligaSaidaTemp
  {
	unsigned char	Rack;
	t_mascara_bits	MascaraDesliga;
	unsigned int	Tempo;
  } t_desl_saida_temp;

/*--- Comando para piscar saida digital ---*/
typedef
  struct PiscaSaida
  {
	unsigned char	Rack;
	unsigned int	TempoLiga;
	unsigned int	TempoDesliga;
	t_mascara_bits	Mascara;
  } t_pisca_saida;

/*--- Comando para bloquear saidas ---*/
typedef
  struct BloqueiaSaidaTemp
  {
	unsigned int	Tempo;
  } t_bloq_saida_temp;

/*--- Comando de configuracao da remota ---*/
typedef
  struct ConfiguraRemota
  {
	byte			AtualizaIO;
#ifndef		CBA_120KAII_III
	byte			SizeIO;			//Num. de pontos de i/o x 8
#endif
	t_mascara_bits	HabEnvLig;
	t_mascara_bits	HabEnvDesl;
	t_mascara_bits	HabSinalLig;
	t_mascara_bits	HabSinalDesl;
	t_mascara_bits	MascSinal;
	t_mascara_bits	ConfigIO;
#ifdef	USA_REDE_ECHELON
	t_mascara_bits	WatchdogLig;
	t_mascara_bits	WatchdogDesl;
#else
	t_mascara_bits	Watchdog;
#endif
	t_mascara_bits	EntradaTemp;
	byte			TempoEntrada;
	t_pisca_saida	SaidaAlimenta;
	t_data			Data;
	int				NodoRemota;
#ifdef	USA_REDE_ECHELON
	/* -- Tempo em segundos para a remota dar timeout micro fora da rede -- */
	byte			TempoWatchdog;
#endif
	int				Reserva1;
	int				Reserva2;
  } t_config_remota;

/*--- Comando para ler configuracao da remota ---*/
typedef
  struct LeConfRemota
  {
	unsigned char	NumNodo;
  } t_le_conf_remota;

/*--- Comando de lista de acoes; varios comandos em um so' ---*/
typedef
  struct ListaAcoes
  {
	t_cab_cmd				Cabecalho;
	union
	{
	  t_esc_saida_dig		EscSaidaDig;
	  t_liga_saida_temp		LigaSaidaTemp;
	  t_desl_saida_temp		DesligaSaidaTemp;
	  t_bloq_saida_temp		BloqueiaSaidaTemp;
	} ListaCmd;
  } t_lista_acoes;

/*--- Comando de tabela de dados - enviado pela remota ou pelo host ---*/
typedef
  struct TabelaDeDados
  {
	char Dados[MAX_TAM_DADOS];
  } t_tabela_dados;

/*--- Configuracao para remota SelfHealing ---*/
typedef
  struct ConfigSelfHeal
  {
	word16		NodoSlave;		// Numero do nodo do slave
	word16		VerifRede;		// tempo entre comunicacao master<->slave
	word16		VerifConserto;	// tempo para verificacao de conserto em caso de falha
  } t_config_sh;

/*--- Comando de alteracao em entrada digital (enviado pela remota) ---*/
typedef
  struct InfAltEntDig
  {
	unsigned char	Rack;
	t_mascara_bits	Mascara;
//#ifndef		CBA_120KAII_III
	t_mascara_bits	Alarmes;
//#endif
  } t_altera_ent_dig;

/*--- Estrutura com o estado atual dos nos da rede (enviado pela remota) ---*/
typedef
  struct EstadoNodosRede
  {
#ifdef		USA_REDE_ECHELON
	struct EstSubRede
	{
	  unsigned long	Estado[2];
	} SubRede[MAX_SUBREDES];
#else
	unsigned long	Estado;
#endif
  } t_estado_rede;

/*--- Cabecalho das respostas enviada para qualquer comando ---*/
typedef
  struct CabResposta
  {
	unsigned char	Cmd;
	unsigned char	Tamanho;
	unsigned char	Transacao;
	char			Status;
  } t_cab_rsp;

/*--- Resposta a comando de leitura de entradas/saidas digitais ---*/
typedef
  struct RespostaLeRackDig
  {
	unsigned char	Rack;
	t_mascara_bits	Mascara;
	t_mascara_bits	Alarmes;
  } t_resp_le_digitais;

/*--- Resposta a comando de leitura da configuracao da remota ---*/
typedef
  struct RespostaLeConfig
  {
	char			TipoRemota;
	byte			AtualizaIO;
#ifndef		CBA_120KAII_III
	byte			SizeIO;			//Num. de pontos de i/o x 8
#endif
	t_mascara_bits	HabEnvLig;
	t_mascara_bits	HabEnvDesl;
	t_mascara_bits	HabSinalLig;
	t_mascara_bits	HabSinalDesl;
	t_mascara_bits	MascSinal;
	t_mascara_bits	ConfigIO;
#ifdef	USA_REDE_ECHELON
	t_mascara_bits	WatchdogLig;
	t_mascara_bits	WatchdogDesl;
#else
	t_mascara_bits	Watchdog;
#endif
	t_mascara_bits	EntradaTemp;
	byte			TempoEntrada;
	t_pisca_saida	SaidaAlimenta;
	t_data			Data;
	int				NodoRemota;
#ifdef	USA_REDE_ECHELON
	/* -- Tempo em segundos para a remota dar timeout micro fora da rede -- */
	byte			TempoWatchdog;
#endif
	word16			VersaoFirmware;	/* 0 a 65535 */
	word16			Reserva1;
	int				Reserva2;
  } t_resp_le_config;

/*--- Estrutura de um comando ---*/
typedef
  struct Comando
  {
	t_cab_cmd	CabComando;
	union		
	{
	  /*--- Comandos enviados PARA as remotas ---*/
	  t_esc_saida_dig		EscSaidaDig[MAX_RACKS];
	  t_le_digitais			LeRackDig;
	  t_liga_saida_temp		LigaSaidaTemp[MAX_RACKS];
	  t_desl_saida_temp		DesligaSaidaTemp[MAX_RACKS];
	  t_pisca_saida			PiscaSaida[MAX_RACKS];
	  t_bloq_saida_temp		BloqueiaSaidaTemp;
	  t_config_remota		ConfiguraRemota;
	  t_le_conf_remota		LeConfRemota;
	  t_lista_acoes			ListaComandos[MAX_CMD_LISTA];
	  t_tabela_dados		EscTabDadosRemota;
	  t_config_sh			ConfSH;

	  /*--- Comandos enviados PELAS remotas ---*/
	  t_altera_ent_dig		InfAltEntDig[MAX_RACKS];
	  t_estado_rede			EstadoRede;
	  t_tabela_dados		EscTabDadosHost;
	} TipoCom;
  } t_comando;

/*--- Estrutura de uma resposta ---*/
typedef
  struct Resposta
  {
	t_cab_rsp	CabResposta;
	union
	{
	  t_resp_le_digitais	RespostaLeRackDig[MAX_RACKS];
	  t_resp_le_config		RespostaLeConfig;
	  t_tabela_dados		RespostaTabDados;
	} TipoResp;
  } t_resposta;

#ifdef	USA_REDE_ECHELON
/*--- Estrutura para receber/escrever variaveis de rede ---*/
typedef
  struct AltNV
  {
	int			NV_index;	// indice da variavel de rede na tabela interna
							// do RedeAtn7
	byte		Valor[40];	// Valor (tamanho depende do tipo)
	byte		Reserva[40];
  } t_alt_NV;
#endif

/*--- Estrutura de comunicacao com o usuario ---*/
typedef
  struct ComunicUsuario
  {
	int			Esperar;
	t_cabecalho CabecMsg;
	union
	{
	  t_resposta	Resposta;
	  t_comando		Comando;
#ifdef	USA_REDE_ECHELON
	  t_alt_NV		AltNV;
#endif
	} CmdResp;
  } t_msg_usu;

/*--- Estrutura de comunicacao com a rede ---*/
typedef
  struct ComunicRede
  {
	t_cabecalho CabecMsg;
	union
	{
	  t_resposta	Resposta;
	  t_comando		Comando;
#ifdef	USA_REDE_ECHELON
	  t_alt_NV		AltNV;
#endif
	} CmdResp;
  } t_msg_rede;

/*--- Estrutura de comunicacao com o usuario atraves de fila ---*/
typedef
  struct RecCmd
  {
	char			QueueHeader[QHDR_SIZE];	/* -- Area de trabalho para o queue -- */
    t_msg_usu		MsgUsu;
  } t_msg_rec_cmd;

#endif	/*--- #ifndef _REMOTAS.H ---*/
