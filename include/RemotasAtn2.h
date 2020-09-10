/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: RemotasAtn2.h

	CONTEUDO	: Contem as definicoes de tipos do protocolo da remota
				  Atn2.1. Este prologo reflete o protocolo como definido
				  originalmente em Remotas.h, apenas mantendo os tipos
				  inteiros da remota com 16 bits (short) por causa da
				  utilizacao da versao 32 bits do QNX (4.xx)
				  Estas definicoes de tipo devem ser exatamente iguais as
				  definicoes utilizadas pelo programa da remota.
				  Foi acrescentado um sufixo Atn2 aos tipos de dados para
				  nao conflitar com os originais definidos em Remotas.h

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0		  -		  DATA  : 16/09/96

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
         |                                                      |
-------------------------------------------------------------------------------
******************************************************************************/

/*--- Verifica se ja foi incluido ---*/

#ifndef	_REMOTAS_ATN2_H
	#define	_REMOTAS_ATN2_H

#ifdef PROGRAMA_PRINCIPAL
	#define		DECL
#else
	#define		DECL	extern
#endif

	/******************************/
	/*--- INCLUSAO DE ARQUIVOS ---*/
	/******************************/

#include <Remotas.h>

	/*******************************************/
	/*--- TAMANHO DAS ESTRUTURAS DE COMANDO ---*/
	/*******************************************/

#define	TAM_CAB_MSG_ATN2		(sizeof (struct CabeAtn2))
#define	TAM_COMANDO_ATN2		(sizeof (struct ComandoAtn2))
#define	TAM_RESPOSTA_ATN2		(sizeof (struct RespostaAtn2))
#define	TAM_ESC_DIG_ATN2		(sizeof (struct EscreveSaidaDigAtn2))
#define	TAM_LER_DIG_ATN2		(sizeof (struct RespostaLeRackDigAtn2))
#define TAM_LIG_TMP_ATN2		(sizeof (struct LigaSaidaTempAtn2))
#define TAM_DES_TMP_ATN2		(sizeof (struct DesligaSaidaTempAtn2))
#define TAM_PIS_SAI_ATN2		(sizeof (struct PiscaSaidaAtn2))
#define TAM_BLQ_SAI_ATN2		(sizeof (struct BloqueiaSaidaTempAtn2))
#define	TAM_CNF_REM_ATN2		(sizeof (struct ConfiguraRemotaAtn2))
#define	TAM_RSP_CNF_ATN2		(sizeof (struct RespostaLeConfigAtn2))
#define	TAM_LST_COM_ATN2		(sizeof (struct ListaAcoesAtn2))
#define	TAM_INF_DIG_ATN2		(sizeof (struct InfAltEntDigAtn2))


	/****************************/
	/*--- DEFINICAO DE TIPOS ---*/
	/****************************/

/* -- Criado para reproduzir o frame do Atn2 (int=16bits) para versao
      QNX4 32 bits (TamFrame e Canal -> short int no Atn2 e int no Score -- */

/*--- Cabecalho da mensagem de interface entre USUARIO/APLICACAO/REDE ---*/
typedef
  struct CabeAtn2
  {
	char		TipoServico;
	short int	TamFrame;
	short int	Canal;
	unsigned	char NumNodoSrc;
	unsigned	char NumNodoDst;
	char		Reserva[10];
  } t_cabec_atn2;

#ifndef	T_MASCARA_BITS_ATN2
  #define	T_MASCARA_BITS_ATN2

  /*--- Mascara de bits para comandos de ligar/desligar saidas ---*/
  typedef
	struct MascaraBitsAtn2
	{
	  short unsigned int Mascara1;
	  short unsigned int Mascara2;
	} t_mascara_bitsAtn2;
#endif

/*--- Comando para escrever saidas digitais ---*/
typedef
  struct EscreveSaidaDigAtn2
  {
	unsigned char	Rack;
	t_mascara_bitsAtn2	MascaraLiga;
	t_mascara_bitsAtn2	MascaraDesliga;
  } t_esc_saida_digAtn2;

/*--- Comando para ligar saida temporizada ---*/
typedef
  struct LigaSaidaTempAtn2
  {
	unsigned char		Rack;
	t_mascara_bitsAtn2	MascaraLiga;
	short unsigned int	Tempo;
  } t_liga_saida_tempAtn2;

/*--- Comando para desligar saida temporizada ---*/
typedef
  struct DesligaSaidaTempAtn2
  {
	unsigned char		Rack;
	t_mascara_bitsAtn2	MascaraDesliga;
	short unsigned int	Tempo;
  } t_desl_saida_tempAtn2;

/*--- Comando para piscar saida digital ---*/
typedef
  struct PiscaSaidaAtn2
  {
	unsigned char		Rack;
	short unsigned int	TempoLiga;
	short unsigned int	TempoDesliga;
	t_mascara_bitsAtn2	Mascara;
  } t_pisca_saidaAtn2;

/*--- Comando para bloquear saidas ---*/
typedef
  struct BloqueiaSaidaTempAtn2
  {
	short unsigned int	Tempo;
  } t_bloq_saida_tempAtn2;

/*--- Comando de configuracao da remota ---*/
typedef
  struct ConfiguraRemotaAtn2
  {
	char				AtualizaIO;
	t_mascara_bitsAtn2	HabEnvLig;
	t_mascara_bitsAtn2	HabEnvDesl;
	t_mascara_bitsAtn2	HabSinalLig;
	t_mascara_bitsAtn2	HabSinalDesl;
	t_mascara_bitsAtn2	MascSinal;
	t_mascara_bitsAtn2	ConfigIO;
	t_mascara_bitsAtn2	Watchdog;
	t_mascara_bitsAtn2	EntradaTemp;
	byte			TempoEntrada;
	t_pisca_saidaAtn2	SaidaAlimenta;
	t_data				Data;
	short int			NodoRemota;
	short int			Reserva1;
	short int			Reserva2;
  } t_config_remotaAtn2;

/*--- Comando de lista de acoes; varios comandos em um so' ---*/
typedef
  struct ListaAcoesAtn2
  {
	t_cab_cmd				Cabecalho;
	union
	{
	  t_esc_saida_digAtn2		EscSaidaDig;
	  t_liga_saida_tempAtn2		LigaSaidaTemp;
	  t_desl_saida_tempAtn2		DesligaSaidaTemp;
	  t_bloq_saida_tempAtn2		BloqueiaSaidaTemp;
	} ListaCmd;
  } t_lista_acoesAtn2;

/*--- Comando de alteracao em entrada digital (enviado pela remota) ---*/
typedef
  struct InfAltEntDigAtn2
  {
	unsigned char	Rack;
	t_mascara_bitsAtn2	Mascara;
  } t_altera_ent_digAtn2;

/*--- Resposta a comando de leitura de entradas/saidas digitais ---*/
typedef
  struct RespostaLeRackDigAtn2
  {
	unsigned char	Rack;
	t_mascara_bitsAtn2	Mascara;
  } t_resp_le_digitaisAtn2;

/*--- Resposta a comando de leitura da configuracao da remota ---*/
typedef
  struct RespostaLeConfigAtn2
  {
	char			TipoRemota;
	char			AtualizaIO;
	t_mascara_bitsAtn2	HabEnvLig;
	t_mascara_bitsAtn2	HabEnvDesl;
	t_mascara_bitsAtn2	HabSinalLig;
	t_mascara_bitsAtn2	HabSinalDesl;
	t_mascara_bitsAtn2	MascSinal;
	t_mascara_bitsAtn2	ConfigIO;
	t_mascara_bitsAtn2	Watchdog;
	t_mascara_bitsAtn2	EntradaTemp;
	byte				TempoEntrada;
	t_pisca_saidaAtn2	SaidaAlimenta;
	t_data				Data;
	short int			NodoRemota;
	short int			Reserva1;
	short int			Reserva2;
  } t_resp_le_configAtn2;

/*--- Estrutura de um comando ---*/
typedef
  struct ComandoAtn2
  {
	t_cab_cmd	CabComando;
	union		
	{
	  /*--- Comandos enviados PARA as remotas ---*/
	  t_esc_saida_digAtn2		EscSaidaDig[MAX_RACKS];
	  t_le_digitais				LeRackDig;
	  t_liga_saida_tempAtn2		LigaSaidaTemp[MAX_RACKS];
	  t_desl_saida_tempAtn2		DesligaSaidaTemp[MAX_RACKS];
	  t_pisca_saidaAtn2			PiscaSaida[MAX_RACKS];
	  t_bloq_saida_tempAtn2		BloqueiaSaidaTemp;
	  t_config_remotaAtn2		ConfiguraRemota;
	  t_le_conf_remota			LeConfRemota;
	  t_lista_acoesAtn2			ListaComandos[MAX_CMD_LISTA];
	  t_tabela_dados			EscTabDadosRemota;

	  /*--- Comandos enviados PELAS remotas ---*/
	  t_altera_ent_digAtn2		InfAltEntDig[MAX_RACKS];
	  t_estado_rede				EstadoRede;
	  t_tabela_dados			EscTabDadosHost;
	} TipoCom;
  } t_comandoAtn2;

/*--- Estrutura de uma resposta ---*/
typedef
  struct RespostaAtn2
  {
	t_cab_rsp	CabResposta;
	union
	{
	  t_resp_le_digitaisAtn2	RespostaLeRackDig[MAX_RACKS];
	  t_resp_le_configAtn2		RespostaLeConfig;
	} TipoResp;
  } t_respostaAtn2;

/* -- Tipo para comunicacao com as remotas -- */
typedef
  struct FrameAtn2
  {
	t_cabec_atn2  CabecMsg;
	union
	{
	  t_respostaAtn2	Resposta;
	  t_comandoAtn2		Comando;
	} CmdResp;
  } t_frame_atn2;

#endif	/*--- #ifndef _REMOTAS_ATN2.H ---*/
