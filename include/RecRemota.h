
/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 3.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: RecRemota.h

	CONTEUDO	: Definicoes gerais da camada de aplicacao para comunicacao
				  com a camada de rede

	AUTOR		: Hevelton Araujo Junior

	VERSAO		: 00 - 25/09/92

	HISTORICO DAS EDICOES

******************************************************************************/

#ifdef	PROGRAMA_PRINCIPAL
	#define		DECL
#else
	#define		DECL	extern
#endif


#include <queue.h>

	/***************************/
	/*--- DEFINICOES GERAIS ---*/
	/***************************/

/*--- Para funcao de leitura de fila ficar esperando mensagem ---*/
#define	ESP_MSG					0x0001

/*--- Mensagens de erro ---*/
#define	STR_ERR_ABR_FILA		"Erro de abertura de fila"
#define	STR_ERR_REC_LIXO		"Recebeu tipo de servico invalido"
#define	STR_ERR_LER_FILA		"Erro de leitura de fila"
#define	STR_ERR_SRV_NOME		"Servidor nao registrou nome"
#define	STR_ERR_USU_SEND		"Send para servidor falhou"
#define	STR_ERR_USU_STTS		"Retorno do usuario com erro"
#define	STR_ERR_SERV			"Erro na localizacao do servidor"

	/***************************/
	/*--- VARIAVEIS GLOBAIS ---*/
	/***************************/

DECL t_cabecalho	CabecRede;		/*--- Cabecalho de msgs da rede ---*/
DECL t_comando		Comandos;		/*--- Comandos recebidos da rede ---*/
DECL t_resposta		Respostas;		/*--- Respostas recebidas da rede ---*/
DECL t_msg_rede		MsgRede;		/*--- Para comunicacao com a rede ---*/
DECL t_msg_usu		MsgUsuario;		/*--- Para comunicacao com o usuario ---*/

/*--- Para fazer leitura nas filas (queue) ---*/
struct
{
  char			CabecQueue[QHDR_SIZE];
  union
  {
	t_cabecalho	CabecRede;
	union
	{
	  t_comando		Comando;
	  t_resposta	Resposta;
	} CmdResp;
  } DadosQueue;
} MsgQueue;

	/**********************************/
	/*--- PROTOTIPACAO DAS FUNCOES ---*/
	/**********************************/

void main (void);
void TransfereParaUsuario (int Fila);
