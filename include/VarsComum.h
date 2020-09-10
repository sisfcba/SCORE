/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 3.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: VarsComum.h

	CONTEUDO	: Contem a definicao dos apontadores necessarios para acessar
				  as tabelas globais do sistema.

	AUTOR		: Leonel Vicente Mota Ivo

	VERSAO		: 1.0			-		DATA	:	20/08/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
28/03/95 | Incluida definicao de ponteiro para tab_inc_ope      | Leonel
-------------------------------------------------------------------------------
19/10/95 | Reorganizacao dos prologos do IHM					| Carlos
-------------------------------------------------------------------------------
******************************************************************************/
#ifndef		_VARSCOMUM_H

#define		_VARSCOMUM_H

#include <Score.h>

/* -- Apontador para a area comum -- */
DECL t_comum		*Comum;

/* -- Apontador para a tabela AVC -- */
DECL t_comum_avc	*ComumAvc;

/* -- Apontador para a tabela AVC estado -- */
DECL t_estado_avc	*PAvcEst;

/* -- Apontador para a tabela AVC supervisao -- */
DECL t_superv_avc	*PAvcSup;

/* -- Apontador para a tabela historica de turno (AVL + AVC supervisao) -- */
DECL t_hist			*PHistTurno;

/* -- Apontador para a tabela AVL -- */
DECL t_uavl			*PAvl;

/* -- Apontador para a tabela DescProg -- */
DECL t_descprog		*PDescProg;

/* -- Apontador para a tabela de incrementos de operacao -- */
DECL t_tabs_ope		*PTabOpe;

/* -- Numero do nodo corrente -- */
DECL nid_t			My_nid;

#endif

/* -- Fim do arquivo vars_comum.h -- */

