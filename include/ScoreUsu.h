/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO  : GERAL

	SISTEMA  : TODOS

	ARQUIVO  : ScoreUsu.h

	CONTEUDO : Contem as definicoes de todas as constantes especificas do
			   Sistema de Controle de Reducoes para alg. de usuario.
			   Possui tambem as definicoes das estruturas de dados da
			   base de dados em area comum de memoria.

	AUTOR    : Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO   : 1.0		  -	  DATA  : 03/01/97

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
03/01/97 | Edicao inicial                             			| Leonel
-------------------------------------------------------------------------------
******************************************************************************/

#ifndef		_SCORE_USU_H

#define _SCORE_USU_H


/* -- ********************** DEFINICOES ******************************** -- */
/* define novas estruturas de usuario */
#define			DEF_AVC_USU		1

/* -- ********************* TIPOS DE DADOS ***************************** -- */

/* -- Tipos de dados das tabelas do usuario para o AVC -- */
/* ATENCAO : Estas tabelas nao devem ter suas reservas ultrapassadas */

/* -- Tabelas de parametros do usuario -- */
typedef
  volatile struct par1_user_avc /* 1a. tabela de parametros do usuario */
  {
	char	ResParUser[TAM_PAR_USER_AVC];
  } t_par1_user;

typedef
  volatile struct par2_user_avc /* 2a. tabela de parametros do usuario */
  {
	char	ResParUser[TAM_PAR_USER_AVC];
  } t_par2_user;

/* -- Tabelas de variaveis de trabalho -- */
typedef
  volatile struct user_avc1 /* 1a. tabela de variaveis de trabalho do usuario no AVC */
  {
	char	ResUserAvc[TAM_REG_USER_AVC];
  } t_user1_avc;

typedef
  volatile struct user_avc2 /* 2a. tabela de variaveis de trabalho do usuario no AVC */
  {
	char	ResUserAvc[TAM_REG_USER_AVC];
  } t_user2_avc;

typedef
  volatile struct user_avc3 /* 3a. tabela de variaveis de trabalho do usuario no AVC */
  {
	char	ResUserAvc[TAM_REG_USER_AVC];
  } t_user3_avc;

typedef
  volatile struct user_avc4 /* 4a. tabela de variaveis de trabalho do usuario no AVC */
  {
	char	ResUserAvc[TAM_REG_USER_AVC];
  } t_user4_avc;

/* -- Tipo de dados da tabelas do usuario para o SUPERVISAO AVC -- */
/* ATENCAO : Esta tabela nao deve ter suas reservas ultrapassadas */

/* Tabela de variaveis de supervisao diaria e de turno por cuba */
typedef
  volatile struct sup_usu_avc /* tabela de variaveis de supervisao no SUPERV_AVC */
  {
	/* -- Variaveis de supervisao do usuario -- */
	char		ResSupUsu[TAM_REG_USER_SUP];	/* Reserva para o usuario */
  } t_sup_avc_usu;

/* -- Tipo de dados da tabela de variaveis de estado do usuario - EST_AVC -- */
/* ATENCAO : Esta tabela nao deve ter suas reservas ultrapassadas */

/* Tabela de variaveis de estado do usuario - EST_AVC */
typedef
  volatile struct est_usu_avc /* tabela de variaveis de estado no EST_AVC */
  {
	/* -- Variaveis de estado do usuario -- */
	byte	ResUsuario[TAM_REG_USER_EST];	/* Area disponivel para variaveis do usuario */
  } t_est_usu;

/* -- Tipo de dados da tabelas do usuario para os parametros de Linha - AVL -- */
/* ATENCAO : Esta tabela nao deve ter suas reservas ultrapassadas */

/* Tabela de parametros de linha - AVL */
typedef
  volatile struct par_avl_usu /* tabela de parametros de linha AVL */
  {
	char	ResParAvlUser[TAM_REG_USER_AVL_PAR];	/* -- Reserva Usuario -- */
  } t_par_avl_usu;

/* -- Tipo de dados da tabelas do usuario para os valores de trabalho de Linha -- */
/* ATENCAO : Esta tabela nao deve ter suas reservas ultrapassadas */

/* Tabela de valores de trabalho de linha - AVL */
typedef
  volatile struct trab_avl_usu /* tabela de variaveis de trabalho de linha AVL */
  {
	/* -- Variaveis de trabalho de linha do usuario -- */
	char	ResGerAvlUser[TAM_REG_USER_AVL_TRAB];	/* -- Reserva Usuario -- */
  }	t_trab_avl_usu;

/* -- Tipo de dados da tabelas do usuario para os valores de supervisao diaria de Linha -- */
/* ATENCAO : Esta tabela nao deve ter suas reservas ultrapassadas */

/* Tabela de valores de supervisao diaria e turno de linha - AVL */
typedef
  volatile struct sup_avl_usu	/* tabela de variaveis de supervisao de linha AVL */
  {
	/* -- Variaveis de supervisao do usuario -- */
	byte	ResSupAvlUser[TAM_REG_USER_AVL_SUP];	/* -- Reserva Usuario -- */
  } t_sup_avl_usu;

#endif		/* #ifndef		_SCORE_USU_H */

/* -- Fim do arquivo ScoreUsu.h -- */
