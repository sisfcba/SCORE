
/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 3.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: UsuRemota.h

	CONTEUDO	: Definicoes necessarias para interface entre o usuario e
				  a rede de remotas ATN2.1

	AUTOR		: Hevelton Araujo Junior

	SISTEMA OPERACIONAL:  QNX 2.15		-		COMPILADOR: C86

	VERSAO		: 1.0			-		DATA	:	21/10/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
dd/mm/aa | descricao                                            | autor 
-------------------------------------------------------------------------------
******************************************************************************/

/*--- Verifica se ja foi incluido ---*/
#ifndef	_USU_REMOTA_H
	#define	_USU_REMOTA_H


/*--- Inclui o arquivo de definicao das estruturas de comandos ---*/

#include <Remotas.h>


/*--- Tipo de servico exclusivo do usuario: Nome da fila de interface ---*/
#define	ENVIA_NOME_FILA			0x30

/*--- Tipo de servico exclusivo do usuario: Estado atual da rede ---*/
#define	PEDIDO_ESTADO_REDE		0x31


/*--- Prototipacao das funcoes de interface com o usuario ---*/
int EscSaiDig (int Canal, int Remota, int Esperar, t_esc_saida_dig *Parametros);
int LerEntDig (int Canal, int Remota, t_le_digitais *Parametros, t_resp_le_digitais *Resposta);
int LigSaiTmp (int Canal, int Remota, int Esperar, t_liga_saida_temp *Parametros);
int DesSaiTmp (int Canal, int Remota, int Esperar, t_desl_saida_temp *Parametros);
int BlqSaiDig (int Canal, int Remota, int Esperar, t_bloq_saida_temp *Parametros);
int CnfRemota (int Canal, int Remota, int Esperar, t_config_remota *Parametros);
int EscTDados (int Canal, int Remota, int Esperar, t_tabela_dados *Parametros, int tam_dados);
int LeTDados  (int Canal, int Remota, t_tabela_dados *Cmd, int TamCmd,
				t_tabela_dados *Rsp, int TamRsp);
int LerCnfRem (int Canal, int Remota, t_le_conf_remota *Parametros, t_resp_le_config *Resposta);
int ListAcoes (int Canal, int Remota, int Esperar, t_lista_acoes *Parametros);
int PiscSaida (int Canal, int Remota, int Esperar, t_pisca_saida *Parametros);
int RecCmdRem (t_msg_rec_cmd *Mens);
int PrgRecCmd (void);
int EstRede	  (t_estado_rede *tab_nodos);
int CfgSelfH (int Canal, int Remota, int Esperar, t_config_sh *Parametros);
int EscreveNV (int NV_index, byte *ValorNV, int TamNV);

#endif	/*--- #ifndef _USU_REMOTA_H ---*/

