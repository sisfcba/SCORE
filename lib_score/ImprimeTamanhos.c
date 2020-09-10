/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.

	PROJETO		: SCORE

	SISTEMA		: TODOS

	ARQUIVO		: Imprime tamanhos das tabelas da base de dados do Score.

	CONTEUDO	: Exibe tamanho dos tipos de dados globais do score fazendo
				  um teste de consistencia com os defines de maximos.

	AUTOR		: Leonel Vicente Mota Ivo

	VERSAO		: 1.0			-		DATA	:	26/08/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
dd/mm/aa | descricao                                            | autor 
-------------------------------------------------------------------------------
05/07/02 | Incluido tamanho esperado nas mensagens de erro      | Carlos
-------------------------------------------------------------------------------
$Id: ImprimeTamanhos.c,v 1.1.8.1 2015/07/02 14:12:25 clage Exp $

$Log: ImprimeTamanhos.c,v $
Revision 1.1.8.1  2015/07/02 14:12:25  clage
Alteracao para sala II com ATN8.

Revision 1.1  2003/09/25 19:24:35  leo
Melhoria no CriaGlobal para consistir tamanho do arquivo comum declarado
na variavel TamComum com tamanho das estrutura no prologo.
Inclusao da funcao ImprimeTamanhos na lib.

******************************************************************************/

/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include	<stdio.h>
#include	<Prototipos.h>
#include	<Eventos.h>
#include	<RelGraf.h>

/*
--------------------------------------------------------------------------------
| ImprimeTamanhos - Imprime na saida padrao os tamanhos das estruturas de      |
|                   dados globais                                              |
--------------------------------------------------------------------------------
*/
int ImprimeTamanhos(int lista)
{
  long total_comum;
  int ret=FALSO;
  size_t	t;
//  unsigned long 	Offset;

 if (lista eq VERDADEIRO)
 {
  printf("TAMANHO DOS TIPOS DE DADOS DEFINIDOS NA BASE DE DADOS\n\n");
  printf("t_comum=%u [%05xH] \n",sizeof(t_comum),sizeof(t_comum));
  printf("  t_descr_conv=%u [%04xH] \n",sizeof(t_descr_conv),sizeof(t_descr_conv));
  printf("  t_log=%u [%04xH] \n",sizeof(t_log),sizeof(t_log));
  printf("  t_descprog=%u [%04xH] \n",sizeof(t_descprog),sizeof(t_descprog));
  printf("  t_tabs_elim_ea=%u [%04xH] \n",sizeof(t_tabs_elim_ea),sizeof(t_tabs_elim_ea));
  printf("  t_senhas_operacao=%u [%04xH] \n",sizeof(t_senhas_operacao),sizeof(t_senhas_operacao));
  printf("  t_desc_ev=%u [%04xH] \n",sizeof(t_desc_ev),sizeof(t_desc_ev));
  printf("  t_uavl=%u [%04xH] \n",sizeof(t_uavl),sizeof(t_uavl));


  printf("  t_estado_avc=%u [%04xH] \n",sizeof(t_estado_avc),sizeof(t_estado_avc));
  printf("  t_superv_avc=%u [%xH] \n",sizeof(t_superv_avc),sizeof(t_superv_avc));
  printf("  t_hist_turno=%u [%xH] \n",sizeof(t_hist),sizeof(t_hist));
  printf("  t_tabs_ope=%u [%xH] \n",sizeof(t_tabs_ope),sizeof(t_tabs_ope));

//#ifndef	CBA_120KAII_III
  total_comum=sizeof(t_comum)+sizeof(t_descr_conv)+
			  sizeof(t_log)+sizeof(t_descprog)+sizeof(t_tabs_elim_ea)+
			  sizeof(t_senhas_operacao)+sizeof(t_desc_ev)+
			  sizeof(t_uavl)+sizeof(t_estado_avc)+sizeof(t_superv_avc)+
			  sizeof(t_hist)+sizeof(t_tabs_ope);
  printf("t_comum+tabelas=%d [%xH]\n\n",total_comum,total_comum);

//#else
//  printf("  t_tabs_aj_camisa=%u [%xH] \n",sizeof(t_tabs_aj_camisa),sizeof(t_tabs_aj_camisa));
//  total_comum=sizeof(t_comum)+sizeof(t_descr_conv)+
//			  sizeof(t_log)+sizeof(t_descprog)+sizeof(t_tabs_elim_ea)+
//			  sizeof(t_senhas_operacao)+sizeof(t_desc_ev)+
//			  sizeof(t_uavl)+sizeof(t_estado_avc)+sizeof(t_superv_avc)+
//			  sizeof(t_hist)+sizeof(t_tabs_ope)+sizeof(t_tabs_aj_camisa);
//  printf("t_comum+tabelas=%d [%xH]\n\n",total_comum,total_comum);
//#endif

  printf("t_avc_supervisao=%u [%04xH] - AVC_SUP_REC=%u [%04xH]\n",
		  sizeof(t_avc_supervisao),sizeof(t_avc_supervisao),AVC_SUP_REC,AVC_SUP_REC);
  printf("t_est_avc=%u [%04xH] - AVC_EST_REC=%u [%04xH]\n",
		  sizeof(t_est_avc),sizeof(t_est_avc),AVC_EST_REC,AVC_EST_REC);
  printf("t_avl=%u [%04xH] - AVL_REC=%d [%04xH]\n\n",sizeof(t_avl),sizeof(t_avl),
		  AVL_REC,AVL_REC);
#ifdef	ALCAN_ARATU_HS
  printf("  t_par_avl_usu=%u [%xH]\n",sizeof(t_par_avl_usu),sizeof(t_par_avl_usu));
  printf("  t_trab_avl_usu=%u [%xH]\n",sizeof(t_trab_avl_usu),sizeof(t_trab_avl_usu));
  printf("  t_sup_avl_usu=%u [%xH]\n\n",sizeof(t_sup_avl_usu),sizeof(t_sup_avl_usu));
#endif

  printf("t_avc=%u [%xH] - MAX_AVC=%u [%x] - t_comum_avc=%d [%xH]\n",
		  sizeof(t_avc),sizeof(t_avc),MAX_AVC,MAX_AVC,
		  sizeof(t_comum_avc),sizeof(t_comum_avc));
  printf("  t_abs_avc=%u [%xH]\n",sizeof(t_abs_avc),sizeof(t_abs_avc));
  printf("  t_param_avc=%u [%xH]\n",sizeof(t_param_avc),sizeof(t_param_avc));
  printf("  t_cicleit_avc=%u [%xH]\n",sizeof(t_cicleit_avc),sizeof(t_cicleit_avc));
  printf("  t_ccont_mcp_avc=%u [%xH]\n",sizeof(t_ccont_mcp_avc),sizeof(t_ccont_mcp_avc));
  printf("  t_ciccont_avc=%u [%xH]\n",sizeof(t_ciccont_avc),sizeof(t_ciccont_avc));
  printf("  t_ea_avc=%u [%xH]\n",sizeof(t_ea_avc),sizeof(t_ea_avc));
  printf("  t_ruido_avc=%u [%xH]\n",sizeof(t_ruido_avc),sizeof(t_ruido_avc));
  printf("  t_par1_user=%u [%xH]\n",sizeof(t_par1_user),sizeof(t_par1_user));
  printf("  t_par2_user=%u [%xH]\n",sizeof(t_par2_user),sizeof(t_par2_user));
  printf("  t_user1_avc=%u [%xH]\n",sizeof(t_user1_avc),sizeof(t_user1_avc));
  printf("  t_user2_avc=%u [%xH]\n",sizeof(t_user2_avc),sizeof(t_user2_avc));
  printf("  t_user3_avc=%u [%xH]\n",sizeof(t_user3_avc),sizeof(t_user3_avc));
  printf("  t_user4_avc=%u [%xH]\n",sizeof(t_user4_avc),sizeof(t_user4_avc));
//#ifdef	ALCAN_ARATU_HS
//  printf("  t_par_alc1=%u [%xH]\n",sizeof(t_par_alc1),sizeof(t_par_alc1));
//  printf("  t_alc1_avc=%u [%xH]\n",sizeof(t_alc1_avc),sizeof(t_alc1_avc));
//  printf("  t_alc2_avc=%u [%xH]\n",sizeof(t_alc2_avc),sizeof(t_alc2_avc));
//#endif

  printf("Eventos: t_rec_ev=%u [%xH] \n",sizeof(t_rec_ev),sizeof(t_rec_ev));
  printf("CnfRelGraf: t_cnf_alarme=%u [%xH] t_cnf_graf=%u [%xH] \n",sizeof(t_cnf_alarme),
			sizeof(t_cnf_alarme),sizeof(t_cnf_graf),sizeof(t_cnf_graf));
  printf("CnfRelGraf: t_cnf_graf_cuba=%u [%xH] \n",sizeof(t_cnf_graf_cuba)*MAX_CUBAS,
			sizeof(t_cnf_graf_cuba)*MAX_CUBAS);
  printf("CnfRelGraf: t_cnf_rel_graf=%u [%xH] \n",sizeof(t_cnf_rel_graf),
			sizeof(t_cnf_rel_graf));
  printf("ValRelGraf: t_val_rel_graf=%u [%xH] \n",sizeof(t_val_rel_graf),
			sizeof(t_val_rel_graf));
 }

  /* Consiste alguns tamanhos */
  if ((t=sizeof(t_avc_supervisao)) > AVC_SUP_REC)
  {
	printf("\007\033<ATENCAO: t_avc_supervisao TAMANHO=%u [%xH] INVALIDO - ESPERADO=%u [%xH] !\033>\n",
				sizeof(t_avc_supervisao),sizeof(t_avc_supervisao),AVC_SUP_REC,AVC_SUP_REC);
	ret=VERDADEIRO;
  }

  if ((t=sizeof(t_est_usu)) > TAM_REG_USER_EST)
  {
	printf("\007\033<ATENCAO: t_est_usu TAMANHO=%u [%xH] INVALIDO - ESPERADO=%u [%xH] !\033>\n",
				sizeof(t_est_usu),sizeof(t_est_usu),TAM_REG_USER_EST,TAM_REG_USER_EST);
	ret=VERDADEIRO;
  }

  if ((t=sizeof(t_est_avc)) > AVC_EST_REC)
  {
	printf("\007\033<ATENCAO: t_est_avc TAMANHO=%u [%xH] INVALIDO - ESPERADO=%u [%xH] !\033>\n",
				sizeof(t_est_avc),sizeof(t_est_avc),AVC_EST_REC,AVC_EST_REC);
	ret=VERDADEIRO;
  }

  if ((t=sizeof(t_par_avl_usu)) > TAM_REG_USER_AVL_PAR)
  {
	printf("\007\033<ATENCAO: t_par_avl_usu TAMANHO=%u [%xH] INVALIDO - ESPERADO=%u [%xH] !\033>\n",
				sizeof(t_par_avl_usu),sizeof(t_par_avl_usu),TAM_REG_USER_AVL_PAR,TAM_REG_USER_AVL_PAR);
	ret=VERDADEIRO;
  }
  if ((t=sizeof(t_trab_avl_usu)) > TAM_REG_USER_AVL_TRAB)
  {
	printf("\007\033<ATENCAO: t_trab_avl_usu TAMANHO=%u [%xH] INVALIDO - ESPERADO=%u [%xH] !\033>\n",
				sizeof(t_trab_avl_usu),sizeof(t_trab_avl_usu),TAM_REG_USER_AVL_TRAB,TAM_REG_USER_AVL_TRAB);
	ret=VERDADEIRO;
  }
  if ((t=sizeof(t_sup_avl_usu)) > TAM_REG_USER_AVL_SUP)
  {
	printf("\007\033<ATENCAO: t_sup_avl_usu TAMANHO=%u [%xH] INVALIDO - ESPERADO=%u [%xH] !\033>\n",
				sizeof(t_sup_avl_usu),sizeof(t_sup_avl_usu),TAM_REG_USER_AVL_SUP,TAM_REG_USER_AVL_SUP);
	ret=VERDADEIRO;
  }

  if ((t=sizeof(t_avl)) > AVL_REC)
  {
	printf("\007\033<ATENCAO: t_avl TAMANHO=%u [%xH] INVALIDO - ESPERADO=%u [%xH] !\033>\n",
				sizeof(t_avl),sizeof(t_avl), AVL_REC, AVL_REC);
	ret=VERDADEIRO;
  }

  if (TAM_PAR_USER_AVC ne (t=sizeof(t_par1_user)))
  {
	printf("\007\033<ATENCAO: t_par1_user TAMANHO=%u [%xH] INVALIDO - ESPERADO=%u [%xH] !\033>\n",
				sizeof(t_par1_user),sizeof(t_par1_user),TAM_PAR_USER_AVC,TAM_PAR_USER_AVC);
	ret=VERDADEIRO;
  }
  if (TAM_PAR_USER_AVC ne (t=sizeof(t_par2_user)))
  {
	printf("\007\033<ATENCAO: t_par2_user TAMANHO=%u [%xH] INVALIDO - ESPERADO=%u [%xH] !\033>\n",
				sizeof(t_par2_user),sizeof(t_par2_user),TAM_PAR_USER_AVC,TAM_PAR_USER_AVC);
	ret=VERDADEIRO;
  }

  if (TAM_REG_USER_AVC ne (t=sizeof(t_user1_avc)))
  {
	printf("\007\033<ATENCAO: t_user1_avc TAMANHO=%u [%xH] INVALIDO - ESPERADO=%u [%xH] !\033>\n",
				sizeof(t_user1_avc),sizeof(t_user1_avc),TAM_REG_USER_AVC,TAM_REG_USER_AVC);
	ret=VERDADEIRO;
  }
  if (TAM_REG_USER_AVC ne (t=sizeof(t_user2_avc)))
  {
	printf("\007\033<ATENCAO: t_user2_avc TAMANHO=%u [%xH] INVALIDO - ESPERADO=%u [%xH] !\033>\n",
				sizeof(t_user2_avc),sizeof(t_user2_avc),TAM_REG_USER_AVC,TAM_REG_USER_AVC);
	ret=VERDADEIRO;
  }
  if (TAM_REG_USER_AVC ne (t=sizeof(t_user3_avc)))
  {
	printf("\007\033<ATENCAO: t_user3_avc TAMANHO=%u [%xH] INVALIDO - ESPERADO=%u [%xH] !\033>\n",
				sizeof(t_user3_avc),sizeof(t_user3_avc),TAM_REG_USER_AVC,TAM_REG_USER_AVC);
	ret=VERDADEIRO;
  }
  if (TAM_REG_USER_AVC ne (t=sizeof(t_user4_avc)))
  {
	printf("\007\033<ATENCAO: t_user4_avc TAMANHO=%u [%xH] INVALIDO - ESPERADO=%u [%xH] !\033>\n",
				sizeof(t_user4_avc),sizeof(t_user4_avc),TAM_REG_USER_AVC,TAM_REG_USER_AVC);
	ret=VERDADEIRO;
  }
  if (TAM_REG_USER_SUP ne (t=sizeof(t_sup_avc_usu)))
  {
	printf("\007\033<ATENCAO: t_sup_avc_usu TAMANHO=%u [%xH] INVALIDO - ESPERADO=%u [%xH] !\033>\n",
				sizeof(t_sup_avc_usu),sizeof(t_sup_avc_usu),TAM_REG_USER_SUP,TAM_REG_USER_SUP);
	ret=VERDADEIRO;
  }

  if ((t=sizeof(t_avc)) > MAX_AVC)
  {
	printf("\007\033<ATENCAO: t_avc TAMANHO=%u [%xH] INVALIDO - ESPERADO=%u [%xH] !\033>\n",
				sizeof(t_avc),sizeof(t_avc),MAX_AVC,MAX_AVC);
	ret=VERDADEIRO;
  }
  return(ret);
}

