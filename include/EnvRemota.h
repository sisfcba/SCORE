/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 3.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: EnvRemota.h

	CONTEUDO	: Definicoes gerais da camada de aplicacao para comunicacao
				  com o usuario

	AUTOR		: Hevelton Araujo Junior

	VERSAO		: 01 - 28/09/92

	HISTORICO DAS EDICOES

00 - Edicao inicial									26/09/92		H.Junior
01 - Inclusao do tratamento de timeout				28/09/92		H.Junior
02 - Inclusao de constantes p/ remota Atn2.2		25/01/94		Leonel
03 - Inclusao de constantes p/ remota Atn7.0		18/11/94		Leonel
04 - Inclusao das alteracoes para a ALBRAS          05/01/96        Leonel
******************************************************************************/

/*--- Verifica se ja foi incluido ---*/

#ifndef	ENV_REMOTA_H
	#define	ENV_REMOTA_H


#ifdef	PROGRAMA_PRINCIPAL
	#define	DECL
#else
	#define	DECL	extern
#endif

#include <ListasEnvRem.h>

	/***************************/
	/*--- DEFINICOES GERAIS ---*/
	/***************************/

/*--- Para funcao de leitura de fila ficar esperando mensagem ---*/
#define	ESP_MSG					0x0001

/*--- Tempo para ser ativado na contagem de timeout (em ticks de 50ms) ---*/
#define	TICKS_TEMPOR			10	/*--- (10 * 50ms) = 500ms = 0,5 seg ---*/

/*--- Tempo maximo de timeout para esperar resposta (em ticks de 0,5ms) ---*/
//#define	MAX_TIMEOUT				120	/*--- (120 * 0,5s) = 60 seg ---*/
#define	MAX_TIMEOUT				50	/*--- (50 * 0,5s) = 25 seg ---*/

///*--- Mensagens de erro ---*/
//#define	STR_ERR_REC_LIXO		"Recebeu tipo de servico invalido"
//#define	STR_ERR_REG_NOME		"Erro de registro de nome"
//#define	STR_ERR_TMO_CUBA		"Timeout remota cuba"

	/***************************/
	/*--- VARIAVEIS GLOBAIS ---*/
	/***************************/

DECL t_cabecalho	CabecRede;		/*--- Cabecalho de msgs da rede ---*/
DECL t_comando		Comandos;		/*--- Comandos recebidos da rede ---*/
DECL t_resposta		Respostas;		/*--- Respostas recebidas da rede ---*/
DECL t_msg_rede		MsgRede;		/*--- Para comunicacao com a rede ---*/
DECL t_msg_usu		MsgUsuario;		/*--- Para comunicacao com usuario ---*/
DECL t_lista		TabResp;		/*--- Tabela de respostas pendentes ---*/
DECL t_estado_rede	TabNodos[MAX_CANAIS];	/*--- Estado atual da rede ---*/

#ifdef	USA_REDE_ECHELON
  /* -- proxy para avisar redeatn7 que tem dado na fila -- */
/* -- Alteracao - inicio - 02/04/2002 - Leonel - Inclusao tratamento de mais de um canal (pcltas) -- */
// ***  DECL	pid_t		ProxyRedeAtn7;
  DECL	pid_t		ProxyRedeAtn7[MAX_CANAIS];
/* -- Alteracao - fim - 02/04/2002 - Leonel - Inclusao tratamento de mais de um canal (pcltas) -- */
#endif
#ifdef	USA_PLC
  /* -- proxy para avisar DrvClp que tem dado na fila -- */
  DECL	pid_t		ProxyDrvClp;
#endif

	/**********************************/
	/*--- PROTOTIPACAO DAS FUNCOES ---*/
	/**********************************/

void TrataTimeout (void);
void TrataUsuario (int Tid);
void EnviaPacote (int Tid);
void RecebePacote (int Tid, char *NomeDaFila);
void RecebeTabNodos (int Tid, char *NomeDaFila);
/* -- Alteracao - inicio - 02/04/2002 - Leonel - Inclusao tratamento de mais de um canal (pcltas) -- */
// *** int EnviaFrame (char *NomeFila);
int EnviaFrame (char *NomeFila, int aCanal);
/* -- Alteracao - fim - 02/04/2002 - Leonel - Inclusao tratamento de mais de um canal (pcltas) -- */
char *ErroStr (int Status);
int PriBit1 (long Palavra);
int RemotaAtiva (byte Nodo, word Canal);
void LeEstadoRede (void);
#ifdef	USA_REDE_ECHELON
  void RecebeNV (int Tid, char *NomeDaFila);
  void EnviaNV (int Tid);
#endif

#endif	/*--- #ifndef ENV_REMOTA_H ---*/
