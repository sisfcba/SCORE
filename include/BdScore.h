/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: BdScore.h

	CONTEUDO	: Tipos e definicoes para acesso da base de dados do Score
				  atraves da tarefa BdScore.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0		  -		  DATA  : 26/09/94

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
26/09/94 | Edicao inicial                              			| Leonel
-------------------------------------------------------------------------------
******************************************************************************/

#ifndef		_BDSCORE_H

#define		_BDSCORE_H

#include <errno.h>

#define		NOME_BDSCORE		"Atan/Score/BdScore"

/* -- Macro para calcular offset dentro de uma tabela, dado o endereco inicial
	  da tabela e o endereco do membro a calcular o offset -- */
#define  CalcByteOffset(base,membro)	((unsigned long)((char *)(membro)-(char *)(base)))

/* -- Servicos do BdScore -- */
#define		BD_LER				1	/* Le tabela */
#define		BD_ESCREVER			2	/* Escreve tabela */

/* -- Status de erro -- */
#define		BD_OK				EOK
#define		BD_ACAO_INVALIDA	2000	/* -- acao solicitada invalida -- */
#define		BD_TAB_NAO_EXISTE	2001	/* -- tabela solicitada nao tratada -- */
#define		BD_FALHA_SEMAF		2002	/* -- falha tratamento de semafora -- */
#define		BD_NAO_LOCALIZADA	2003	/* -- BdScore nao localizado na rede -- */
#define		BD_TAMANHO_INVALIDO	2004	/* -- tamanho solicitado <= 0 -- */
#define		BD_FALHA_SEND_SERV	2005	/* -- falha no send para BdScore -- */
#define		BD_TAB_OFFSET_INV	2006	/* -- Offset invalido para tabela dada -- */
#define		BD_TAB_TAMANHO_INV	2007	/* -- Tamanho invalido para tabela dada -- */
#define		BD_TAB_OFF_E_TAM_INV 2008	/* -- Tamanho+offset invalido para tabela dada -- */
#define		BD_TAB_INV			2009	/* -- Erro interno BdScore (endereco_tab) -- */

/* -- Definicoes gerais do modulo -- */
#define		TAM_BLOCO_SEND	(57*1024)	/* 57 Kbytes - tamanho max. do bloco
										   para send via rede */

#define		BD_TIMEOUT_SEND		40		/* Tempo para abortar o send para o
										   bdscore se nao chegar o reply */

/* -- tipos de dados -- */
/* -- Cabecalho da mensagem enviada pelo usuario -- */
typedef struct msg_usuario
{
  int			tabela;	/* -- Numero da tabela (ScoreConst.h + TABELA_COMUM) -- */
  int			acao;	/* -- Ler ou escrever -- */
  unsigned long	offset;	/* -- Offset dentro da tabela selecionada -- */
  long int		tamanho; /* -- tamanho da tabela a ler ou escrever -- */
} t_msg_bd_usuario;

/* -- Cabecalho da mensagem de resposta para o usuario -- */
typedef struct msg_para_usu
{
  int			status_rsp;
} t_msg_bd_rsp;

/* -- uniao dos cabecalhos de mensagem -- */
typedef union msg_bd
{
  t_msg_bd_usuario	s;		/* -- mensagem de send para BdScore -- */
  t_msg_bd_rsp		r;		/* -- mensagem de resposta p/ usuario -- */
} t_msg_bd_score;

#endif

/* -- Fim do arquivo BdServer.h -- */
