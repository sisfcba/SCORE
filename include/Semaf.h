/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: Semaf.h

	CONTEUDO	: Prologo com as definicoes necessarias para comunicacao com o
				  modulo AdminSemaf.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 2.0		  -		  DATA  : 21/06/94

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
dd/mm/aa | Descricao                                            | autor
-------------------------------------------------------------------------------
28/04/94 | Edicao inicial de migracao para o QNX 4.2			| Leonel
-------------------------------------------------------------------------------
******************************************************************************/
#ifndef	_SEMAF_H

#define		_SEMAF_H
/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include	<Definicao.h>
#include	<sys/types.h>

/*
-------------------------------------------------------------------------------
                           Defines
-------------------------------------------------------------------------------
*/
#define	NOME_ADMSEMAF	"Atan/Score/AdmSemaf"	/* nome para localizar tarefa */
#define	NUM_SEMAF		40			/* numero maximo de semaforos */
#define	SIZE_MSG_SEMAF	sizeof(t_msg_semaf)

/* -- Acoes solicitadas ao administrador de semaforos -- */
#define	KILL_ADMIN			-1
#define	WAIT_SEMAFORO		1
#define	SIGNAL_SEMAFORO		2
#define	TEST_SEMAFORO		3

/* -- Respostas as acoes solicitadas -- */
#define	FALHA_SEND			-1
#define	RSP_OK				0
#define	RSP_FALHA_ALLOC		1
#define	RSP_NOT_OWNER		2
#define	RSP_SEMAF_OCUPADO	3
#define	RSP_SEMAF_INVALIDO	4

/* -- Macros para comunicacao -- */
#define	TestaSemaf(NumSemaf)	SolicitaSemaf(NumSemaf,TEST_SEMAFORO)
#define	AlocaSemaf(NumSemaf)	SolicitaSemaf(NumSemaf,WAIT_SEMAFORO)
#define	LiberaSemaf(NumSemaf)	SolicitaSemaf(NumSemaf,SIGNAL_SEMAFORO)

/*
-------------------------------------------------------------------------------
                           Tipos de dados
-------------------------------------------------------------------------------
*/
typedef
  struct msg_semaf
  {
	int		type;			/* codigo da mensagem */
	int		number;			/* semaforo number */
  } t_msg_semaf;

typedef
  struct wait_list
  {
	pid_t				tid;				/* waiting task */
	struct wait_list	*next;
  } t_wait_list;

/*
-------------------------------------------------------------------------------
                           Prototipos
-------------------------------------------------------------------------------
*/
int		SolicitaSemaf(int NumSemaf,int Acao);
int		SolicitaLeitura(int NumSemaf,int Acao);

#endif

/* -- fim do arquivo Semaf.h -- */

