/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 3.0

	PROJETO		: ALCOA

	SISTEMA		: PROTOTIPO - ATN 1.5

	ARQUIVO		: UserDrvsad.h

	CONTEUDO	: Definicao dos tipos e constantes utilizados no modulo drvsad

	AUTOR		: Leonel Vicente Mota Ivo

	VERSAO		: 1.1			-		DATA	:	05/02/93

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
dd/mm/aa | descricao                                            | autor 
-------------------------------------------------------------------------------
******************************************************************************/

#ifndef		__USER_DRVSAD__

#define		__USER_DRVSAD__

/*
--------------------------------------------------------------------------------
					Inclusoes
--------------------------------------------------------------------------------
*/
#include	<Score.h>

/*
--------------------------------------------------------------------------------
					Constantes
--------------------------------------------------------------------------------
*/

/* -- Codigo das solicitacoes de usuario -- */
#define LEITURA				1
#define CALIBRA				2
#define RESET_ALL			3

/* -- Codigo das respostas ao usuario -- */
#define OPCAO_INVALIDA			-1
#define LEITURA_COMPLETADA		1
#define CALIBRACAO_COMPLETADA	2
#define RESET_COMPLETADO		3

#ifdef	ALCOA_SAD22BITS

/*---- Status de conversao retornados pelo conversor Analog devices AD1170 ---*/
/*  B7       B6    B5    B4   B3    B2     B1    B0                           */
/* ----------------------------------------------------                       */
/* | WRMUP | ERR | OL | VAL | MOD | DAV | CONV | BUSY |                       */
/* ----------------------------------------------------                       */
#define		CONV_OK		0
#define		WARMUP		0x80
#define		OVERFLOW	0x20

#define ERRO_OPCAO	   		-2
#define INV_DATA	   		-1


/* -- Limites maximos para o ATN SAD 1.5 -- */
#define MAX_CONV_NMUX		2	/* Num. max. de conversores nao multiplexados */
/**************** TESTE COM 16 CUBAS PARA SIMULACAO ********************/
	#define MAX_CONV_MUX		16	/* Num. max. de conversores multiplexados */
	#define MAX_ENTRADAS_SAD	16	/* Num. max. de entradas possivel p/ o SAD  */

/*** #define MAX_CONV_MUX		8	****/ /* Num. max. de conversores multiplexados */
/*** #define MAX_ENTRADAS_SAD	8	****/ /* Num. max. de entradas possivel p/ o SAD  */
/**************** TESTE COM 16 CUBAS PARA SIMULACAO ********************/

#else

/* -- Status associados `a conversao -- */
#define ERRO_OPCAO	   		-2
#define INV_DATA	   		-1
#define OCUPADO				1
#define CONV_OK				2
#define OVERFLOW_CONV		6

/* -- alteracao - inicio - 11/09/00 - Robson - Inclusao tratamento do Atn8 -- */
/* -- status de dado perdido na atn8 (redeatn8) -- */
#define		DATA_LOST		0xFF
/* -- status de dado nao disponivel no fifo (drvanaatn8) -- */  
#define		NO_DATA			7
/* -- status de dado perdido pelo redeatn8 - dado invalido -- */  
#define		LOST_DATA		8
/* -- alteracao - fim - 11/09/00 - Robson - tratamento do Atn8 -- */

/* -- Limites maximos para o ATN SAD 1.4 -- */
#define MAX_CONV_NMUX		8	/* Num. max. de conversores nao multiplexados */
#define MAX_CONV_MUX		16	/* Num. max. de conversores multiplexados */


/* Observacao: Devem ser multiplos de 16 */
#define MAX_ENTRADAS_SAD	384	/* Num. max. de entradas possivel p/ o SAD  */
#define MAX_PONTOS_SCORE	384	/* Num. max. de pontos (cubas+especiais) */

#endif

/*
--------------------------------------------------------------------------------
					Tipos de dados
--------------------------------------------------------------------------------
*/
/* -- Estrutura da mensagem de resposta do drvsad para o usuario -- */
/* -- alteracao - inicio - 11/09/00 - Robson - Inclusao tratamento do Atn8 -- */
#ifdef	USA_ATN8
 typedef 
  struct msg_sad { /* -- resposta do drvsad para o usuario -- */
	t_mens_padrao	Cabec;
    struct regmux 
	  {
		 short int   Erro[MAX_VALORES_POR_ATN8];
         float		 Valor[MAX_VALORES_POR_ATN8];
      } Regsad[MAX_PONTOS_SCORE];	// Maximo de valores (cuba+especiais)
  } t_msg_resp_drvsad;
#else
 typedef 
  struct msg_sad { /* -- resposta do drvsad para o usuario -- */
	t_mens_padrao	Cabec;
    struct regnmux { /* -- conv. nao multiplexados. 1 leitura para cada grupo de 16 mux -- */
			 int   ErroNmux[MAX_CONV_MUX];
			 float ValorNmux[MAX_CONV_MUX];
		   } Regnmux[MAX_CONV_NMUX];
    struct regmux {
			 int   Erro;
             float Tensao;
           } Regsad[MAX_PONTOS_SCORE];	// Maximo de valores (cuba+especiais)
  } t_msg_resp_drvsad;
#endif
/* -- alteracao - fim - 11/09/00 - Robson - tratamento do Atn8 -- */

/* -- Estrutura da mensagem de solicitacao do usuario para o drvsad -- */
typedef		t_mens_padrao	t_msg_usuario_drvsad;

#endif		/* -- #ifndef		__USER_DRVSAD__ -- */

