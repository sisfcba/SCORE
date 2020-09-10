/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: RemotaAtn7.h

	CONTEUDO	: Prologo do programa de interface com a rede ECHELON
				  (LONTALK) atraves do SLTA (Serial LONTALK Adapter).
				  Contem as definicoes de tipos do protocolo da remota
				  Atn7.0. O protocolo foi alterado em relacao ao original
				  devido a problemas de falta de memoria na remota.
				  Estas definicoes de tipo devem ser exatamente iguais as
				  definicoes utilizadas pelo programa da remota.
				  Foi acrescentado um sufixo ATN7 aos tipos de dados para
				  nao conflitar com os originais definidos em Remotas.h

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0		  -		  DATA  : 09/11/94

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
05/01/95 | Inclusao das alteracoes para a ALBRAS                | Leonel
-------------------------------------------------------------------------------
$Id: RemotaAtn7.h,v 1.4.8.1 2012/09/28 17:09:17 leo Exp $

$Log: RemotaAtn7.h,v $
Revision 1.4.8.1  2012/09/28 17:09:17  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

Revision 1.4  2004/04/26 14:23:25  leo
Inclusao de versao do firmware na mensagem de leitura de configuracao
da remota.

Revision 1.3  2004/04/15 19:38:53  leo
Correcao comentario BitSireneEA.

Revision 1.2  2004/04/12 21:03:56  leo
Inclusao da configuracao do bit de sirene de EA por cuba para qdo remota
atn8 estiver fora de rede (sala 125kA VI).

******************************************************************************/

#ifndef		_REMOTA_ATN7_H

#define		_REMOTA_ATN7_H

  /*--- Tamanho maximo da area de dados da tabela ---*/
#define	MAX_TAM_DADOS_ATN7			100

/* -- Definicoes -- */
/* -- Codigo da mensagem explicita (protocolo LONTALK)
	  Generic application message (0 a 62) -- */
#define		CODIGO_MSG_ECHELON_CMD		0
#define		CODIGO_MSG_ECHELON_RSP		1

/* -- Numero maximo de comandos em uma lista para a remota Atn7.x -- */
/* -- Limitacao de memoria da remota -- */
#define		MAX_CMD_LISTA_ATN7			5

 /* -- Tipo de remota -- */
#define DEF_REMOTA_CUBA					1
#define DEF_OUTRAS_REM 					2

	/*******************************************/
	/*--- TAMANHO DAS ESTRUTURAS DE COMANDO ---*/
	/*******************************************/

#define	TAM_CAB_CMD_ATN7	(sizeof (struct CabComandoATN7))
#define	TAM_CAB_RSP_ATN7	(sizeof (struct CabRespostaATN7))
#define	TAM_COMANDO_ATN7	(sizeof (struct ComandoATN7))
#define	TAM_RESPOSTA_ATN7	(sizeof (struct RespostaATN7))
#define	TAM_MSG_REDE_ATN7	(sizeof (struct ComunicRedeATN7))
#define	TAM_MSG_USU_ATN7	(sizeof (struct ComunicUsuarioATN7))
#define	TAM_ESC_DIG_ATN7	(sizeof (struct EscreveSaidaDigATN7))
#define	TAM_LER_DIG_ATN7	(sizeof (struct RespostaLeRackDigATN7))
#define TAM_LIG_TMP_ATN7	(sizeof (struct LigaSaidaTempATN7))
#define TAM_DES_TMP_ATN7	(sizeof (struct DesligaSaidaTempATN7))
#define TAM_PIS_SAI_ATN7	(sizeof (struct PiscaSaidaATN7))
#define TAM_BLQ_SAI_ATN7	(sizeof (struct BloqueiaSaidaTempATN7))
#define	TAM_CNF_REM_ATN7	(sizeof (struct ConfiguraRemotaATN7))
#define	TAM_LER_CNF_ATN7	(sizeof (struct LeConfRemotaATN7))
#define	TAM_RSP_CNF_ATN7	(sizeof (struct RespostaLeConfigATN7))
#define	TAM_LST_COM_ATN7	(sizeof (struct ListaAcoesATN7))
#define	TAM_T_DADOS_ATN7	(sizeof (struct TabelaDeDadosATN7))
#define	TAM_INF_DIG_ATN7	(sizeof (struct InfAltEntDigATN7))

        /****************************/
        /*--- DEFINICAO DE TIPOS ---*/
        /****************************/

/*--- Mascara de bits para comandos de ligar/desligar saidas ---*/
typedef
  struct MascaraBitsATN7
  {
        byte    Mascara1;    /* Contem os bits 0 a 7 */
        byte    Mascara2;    /* Contem os bits 8 a 15 */
        byte    Mascara3;    /* Contem os bits 16 a 23 */
#ifdef	REMOTA_32_PONTOS
        byte    Mascara4;    /* Contem os bits 24 a 31 */
#endif
  } t_mascara_bitsATN7;


/*--- Cabecalho dos comandos enviados para a remota ---*/
typedef
  struct CabComandoATN7
  {
        byte  Cmd;
        byte  Tamanho;
        byte  Transacao;
  } t_cab_cmdATN7;

/*--- Comando para escrever saidas digitais ---*/
typedef
  struct EscreveSaidaDigATN7
  {
        t_mascara_bitsATN7  MascaraLiga;
        t_mascara_bitsATN7  MascaraDesliga;
  } t_esc_saida_digATN7;

/*--- Comando para ligar saida temporizada ---*/

typedef
  struct LigaSaidaTempATN7
  {
        t_mascara_bitsATN7  MascaraLiga;
        word16    Tempo;
  } t_liga_saida_tempATN7;

/*--- Comando para desligar saida temporizada ---*/
typedef
  struct DesligaSaidaTempATN7
  {
        t_mascara_bitsATN7  MascaraDesliga;
        word16    Tempo;
  } t_desl_saida_tempATN7;

/*--- Comando para piscar saida digital ---*/
typedef
  struct PiscaSaidaATN7
  {
        word16    TempoLiga;
        word16    TempoDesliga;
        t_mascara_bitsATN7  Mascara;
  } t_pisca_saidaATN7;

/*--- Comando para bloquear saidas ---*/
typedef
  struct BloqueiaSaidaTempATN7
  {
        word16    Tempo;
  } t_bloq_saida_tempATN7;

/*--- Comando de configuracao da remota ---*/
typedef
  struct ConfiguraRemotaATN7
  {
        byte            AtualizaIO;
        t_mascara_bitsATN7  HabEnvLig;
        t_mascara_bitsATN7  HabEnvDesl;
        t_mascara_bitsATN7  HabSinalLig;  // mascara para sinalizacao qdo ent. liga
        t_mascara_bitsATN7  HabSinalDesl; // mascara para sinalizacao qdo ent. desliga
        t_mascara_bitsATN7  MascSinal;    // quais bits serao ligados caso haja variacao nas ent.
        t_mascara_bitsATN7  ConfigIO;
/****** Inserido em 23/02/94 ******/
		/* bits a serem ligados qdo micro sair rede e desligados qdo voltar */
        t_mascara_bitsATN7  WatchdogLig;
		/* bits a serem desligados qdo micro sair rede */
        t_mascara_bitsATN7  WatchdogDesl;
        t_mascara_bitsATN7  EntradaTemp;  /* entradas cuja leitura e' temporizada */
        byte   TempoEntrada; /* temporizacao - multiplo 50 ms */
        t_pisca_saidaATN7   SaidaAlimenta; /* pisca saidas qdo micro sair rede */
/****** Inserido em 23/02/94 ******/
		/* -- Tempo em segundos para a remota dar timeout micro fora da rede -- */
		byte				TempoWatchdog;
  } t_config_remotaATN7;

/*--- Comando de lista de acoes; varios comandos em um so' ---*/
typedef
  struct ListaAcoesATN7
  {
        t_cab_cmdATN7           Cabecalho;
        union
        {
          t_esc_saida_digATN7       EscSaidaDig;
          t_liga_saida_tempATN7     LigaSaidaTemp;
          t_desl_saida_tempATN7     DesligaSaidaTemp;
          t_bloq_saida_tempATN7     BloqueiaSaidaTemp;
        } ListaCmd;
  } t_lista_acoesATN7;

/*--- Comando para avisar remota que micro esta vivo ---*/
typedef
  struct WatchdogATN7
  {
	byte	TamGrupo;
	byte	TempoGrupo;
  } t_watchdogATN7;

/* -- alteracao - inicio - 11/09/00 - Robson - Tratamento da Atn8.0 -- */
/*--- Comando para avisar remota que micro esta vivo ---*/
typedef
  struct WatchdogATN8
  {
	byte	TamGrupo;
	byte	TempoGrupo;
    byte	BcastNum;		// numero do broadcast corrente
  } t_watchdogATN8;
/* -- alteracao - fim - 11/09/00 - Robson - Tratamento da Atn8.0 -- */

/*--- Comando de tabela de dados - enviado pela remota ou pelo host ---*/
typedef
  struct TabelaDeDadosATN7
  {
	byte Dados[MAX_TAM_DADOS_ATN7];
  } t_tabela_dadosATN7;

/* -- alteracao - inicio - 05/09/00 - Robson - Inclusao mensagem Atn8 -- */
#define		MAX_ANAREG_PER_MSG	6	/* numero maximo de registros por mensagem */
#define		MAX_CONV_ATN8	(MAX_VALORES_POR_ATN8)	/* numero de conversores da atn8 */

/* -- Estrutura da configuracao de analogicas da remota atn8. Eh enviada para
      o atn8 na configuracao e pode ser lida pelo programa de testes -- */
typedef
struct conf_ana_atn8
{
  byte		SubComando;
  byte		ScanAna;		/* frequencia de leitura das analogicas. Em ticks
  							   da remota */
  byte		NumConvAna;		/* Numero de conversores A/D montados na remota */
} t_conf_atn8;

typedef
struct le_conf_ana_atn8
{
  byte		SubComando;
} t_le_conf_atn8;

/* -- Estruturas dos dados enviados pela remota atn8 -- */
typedef
struct conv_atn8
{
  byte	data[2];
} t_conv_atn8;

typedef
struct conv_data_atn8
{
  byte	conv_status;	// status for all A/D converters
  t_conv_atn8	conv[MAX_CONV_ATN8];	// data for each converter
} t_conv_data_atn8;

typedef
struct msg_ana_atn8
{
  byte	last_reading;	// Reading count of the last sample in the message
  byte	bcast;			// Broadcast number this message is reply for
  byte	temperature;	// Remote terminal unit temperature
  t_conv_data_atn8	samples[MAX_ANAREG_PER_MSG];	// received A/D data
} t_msg_ana_atn8;

typedef
  struct InfAltAnaDigATN8
  {
     t_mascara_bitsATN7	Mascara;
     byte				Alarmes;
	 t_msg_ana_atn8		DadosAna;
  } t_inf_ana_digATN8;
/* -- alteracao - fim - 05/09/00 - Robson - Inclusao mensagem Atn8 -- */

/************************* REMOTA PARA CBA *****************************/

/*--- Estruturas para implementar a comunicacao necessaria a execucao do
	  sequenciamento de alimentacao dos point feeders. Estarao embutidas
	  dentro da tabela de dados ---*/

/*--- Comando de configuracao dos passos da sequencia ---*/
// Configuracao especial do Point Feeder CBA
typedef
  struct ConfigPointFeeder
  {
	byte				SubComando; /* CONFIGURA_PASSOS_SEQ */
    t_mascara_bitsATN7	AutoMan;    /* Mascara de modo de operacao */
/* -- Alteracao - inicio - Robson - 03/10/2000 - alteracao para novo PF -- */
//    t_mascara_bitsATN7	Pistao_A;   /* Mascara c/ bits de Avanco/Recuo do Pistao A */
//    t_mascara_bitsATN7	Pistao_B;   /* Mascara c/ bits de Avanco/Recuo do Pistao B */
//    word16				TempoAvanco; /* Tempo de Avanco do Point Feeder */
//    word16				TempoInterv; /* Tempo de intervalo entre Avanco/ Recuo do PF */
//    word16				TempoRecuo;  /* Tempo de Recuo do Point Feeder */
//    word16				CadenciaFalta; /* Temporizacao da remota quando o
    t_mascara_bitsATN7	QuebA;			/* Mascara c/ bits de quebrador A */
    t_mascara_bitsATN7	QuebB;			/* Mascara c/ bits de quebrador B */
    t_mascara_bitsATN7	QuebC;			/* Mascara c/ bits de quebrador C */
    t_mascara_bitsATN7	QuebD;			/* Mascara c/ bits de quebrador D */
    t_mascara_bitsATN7	AlimA;			/* Mascara c/ bits de quebrador A */
    t_mascara_bitsATN7	AlimB;			/* Mascara c/ bits de quebrador B */
    t_mascara_bitsATN7	AlimC;			/* Mascara c/ bits de quebrador C */
    t_mascara_bitsATN7	AlimD;			/* Mascara c/ bits de quebrador D */
    word16				TempoQuebrador; /* Tempo de acionamento do quebrador */
    word16				TempoEspera; 	/* Tempo de intervalo quebra e alimentacao */
    word16				TempoAlimentador;/* Tempo de acionamento do alimentador */
    word16				CadenciaFalta; 	/* Temporizacao da remota quando o
										  computador sai da rede */
  } t_config_pf;

/* -- Alteracao - Inicio - Robson - 22/04/2002 - algoritmo de PF na Atn8.0 -- */
// Configuracao especial do Point Feeder CBA ATN 8.0
typedef
  struct ConfigPointFeederAtn8
  {
	byte				SubComando; /* CONFIGURA_PF_ATN8 */
    t_mascara_bitsATN7	AutoMan;    /* Mascara de modo de operacao */
    t_mascara_bitsATN7	QuebA;			/* Mascara c/ bits de quebrador A */
    t_mascara_bitsATN7	QuebB;			/* Mascara c/ bits de quebrador B */
    t_mascara_bitsATN7	QuebC;			/* Mascara c/ bits de quebrador C */
    t_mascara_bitsATN7	QuebD;			/* Mascara c/ bits de quebrador D */
    t_mascara_bitsATN7	AlimA;			/* Mascara c/ bits de quebrador A */
    t_mascara_bitsATN7	AlimB;			/* Mascara c/ bits de quebrador B */
    t_mascara_bitsATN7	AlimC;			/* Mascara c/ bits de quebrador C */
    t_mascara_bitsATN7	AlimD;			/* Mascara c/ bits de quebrador D */
    word16				TempoQuebrador; /* Tempo de acionamento do quebrador */
    word16				TempoEspera; 	/* Tempo de intervalo quebra e alimentacao */
    word16				TempoAlimentador;/* Tempo de acionamento do alimentador */
    word16				CadenciaFalta; 	/* Temporizacao da remota quando o
										  computador sai da rede */
	byte				Sequencia[NUM_CONJ_ALIM];
    /* -- Alteracao - Inicio - 22/05/2002 - cadencia de EA na remota -- */
	word16				EAVoltLimite;	/* tensao limite para EA */
	word16				CadenciaEA;		/* cadencia para EA em segundos */
	byte				CanalTensao;	/* canal onde esta a tensao de cuba */
	byte				TempoInicioEA;	/* Tempo para efetivacao do EA em segundos */
	byte				TempoFimEA;		/* Tempo para fim EA em minutos */
	byte				TempoFimAEA;	/* Tempo para da alimentacao de EA em minutos */
    /* -- Alteracao - Fim - 22/05/2002 - cadencia de EA na remota -- */
	byte				SaidaSireneEA;	/* Numero da saida de acionamento da sirene
			qdo fora de rede e em EA. Comeca de 1 e contem FF se nao configurado */
    t_mascara_bitsATN7	ResetEA;		/* Mascara c/ bit da botoeira de reset da sirene de EA */
  } t_config_pf_atn8; // 52 bytes
/* -- Alteracao - Fim - Robson - 22/04/2002 - algoritmo de PF na Atn8.0 -- */

/* Falha de movimentacao -> Confere desligamento da entrada indicada, TempoEspera
   segundos apos o desligamento de qualquer uma das saidas indicadas. Caso a
   mesma esteja ligada envia alarme para o computador no 1o. bit da mascara de
   ALARMES.
   Falha de alimentacao -> Confere ligamento da entrada indicada, TempoEspera
   segundos apos o ligamento de qualquer uma das saidas indicacadas. Caso a
   mesma esteja desligaca envia alarme para o micro no 2o. bit da mascara de
   ALARMES. */
typedef
  struct AlarmeIO
  {
	t_mascara_bitsATN7	MascSaida;	/* Indica saidas associadas ao bit de entrada, bit=1.
									   Todos os bits = 0 -> desabilita */
	t_mascara_bitsATN7	MascEnt;	/* Indica entrada a ser monitorada, bit=1.
									   Todos os bits = 0 -> desabilita */
	word16				TempoEspera; /* Ticks da remota a esperar para checar desligamento
										da entrada apos desligamento de uma das saidas. */
  } t_alarme_io;

// Configuracao especial p/ CBA
typedef
  struct ConfigEspecial
  {
	byte				SubComando;		/* CONFIGURA_PASSOS_SEQ */
    t_mascara_bitsATN7	AutoMan;		/* 3 bytes - Mascara de modo de operacao do MM (indicar apenas bit auto) */
    t_mascara_bitsATN7	MascTrigger1;	/* 3 bytes - Trigger alimentador 1 */
    t_mascara_bitsATN7	MascTrigger2;	/* 3 bytes - Trigger alimentador 2 */
	t_alarme_io			VerifAgarra;	/* 8 bytes - Verifica agarramento do MM */
/* -- alteracao - inicio - 22/09/00 - Robson - Inclusao mensagem Atn8 -- */
// ######################### Acrescentar para tratamento da cuba irma
//	t_alarme_io			VerifAgarra2;	/* 8 bytes - Mascara para configuracao do IO da outra cuba */
// ##################################################################
/* -- alteracao - fim - 22/09/00 - Robson - Inclusao mensagem Atn8 -- */

	t_alarme_io			ConfAciona;		/* Confirma acionamento do MM */
  } t_config_especial;

// Armazena mensagem de execucao de sequencia
typedef
  struct ExecSeq
  {
    byte SubComando;          /* EXECUTA_SEQUENCIA */
    word16 TempoSeq;              /* Tempo entre sequencias (em segundos)
                                   Qdo == 0 ->remota inicia sequencia imediatamente
                                   Qdo != 0 ->intervalo para que a remota execute uma sequencia
                                   Obs.: Se for igual ao valor anterior trata-se de um "refresh"
                                         e a remota nao faz nada */
    byte Quebrador;              /* Usado apenas qdo Temposeq==0
                                   Se Quebrador==0, remota escolhe pistao
                                   Qdo != 0 -> indica no. do pistao a ser acionado:
                                        1- Acionar Pistao A
                                        2- Acionar Pistao B
                                */
  } t_exec_seq;

// Armazena mensagem de reconfiguracao dos quebradores (ativa/desativa quebradores)
typedef
  struct SelecPistao
  {
    byte SubComando;   /* HABILITA_PISTAO/DESABILITA_PISTAO */
    byte Pistao;       /* Pistao=1 => A; 
                          Pistao=2 => B */
  } t_selec_pistao;

// Comanda leitura configuracao
typedef
  struct LeConfg
  {
    byte SubComando;   /* LE_CONF_ESPECIAL ou LE_CONF_ALIMENT */
  } t_le_confg;

/*--- Estrutura de comando, embutida dentro da tabela de dados ---*/
typedef
  union		
  { /*--- Comandos enviados ---*/
    t_config_pf			ConfPF;		// configuracao dos point feeders
/* -- Alteracao - Inicio - Robson - 24/04/2002 - algoritmo de PF na Atn8.0 -- */
    t_config_pf_atn8	ConfPFAtn8;	// configuracao dos point feeders
/* -- Alteracao - Fim - Robson - 24/04/2002 - algoritmo de PF na Atn8.0 -- */
    t_exec_seq			ExecMsg;	// comando para executar sequencia
    t_selec_pistao		SelQueb;	// exclui/inclui pistao
	t_config_especial 	ConfEsp;	// configuracao de outros parametros
    t_le_confg			LeConfg;	// Le configuracao especial ou de alimentacao
  } t_cmd_alim;

/*--- Estrutura de resposta, embutida dentro da tabela de dados ---*/
typedef
  union		
  { /*--- Comandos enviados ---*/
    t_config_pf		ConfPF;		// configuracao dos point feeders
/* -- Alteracao - Inicio - Robson - 24/04/2002 - algoritmo de PF na Atn8.0 -- */
    t_config_pf_atn8	ConfPFAtn8;	// configuracao dos point feeders
	t_conf_atn8			ConfAna;	// configuracao scan analogicas
/* -- Alteracao - Fim - Robson - 24/04/2002 - algoritmo de PF na Atn8.0 -- */
	t_config_especial ConfEsp;	// configuracao de outros parametros
  } t_rsp_alim;

/************************* REMOTA PARA CBA *****************************/

/*--- Comando de alteracao em entrada digital (enviado pela remota) ---*/
typedef
  struct InfAltEntDigATN7
  {
        t_mascara_bitsATN7  Mascara;
        byte				Alarmes;
  } t_altera_ent_digATN7;
  
/*--- Cabecalho das respostas enviada para qualquer comando ---*/
typedef
  struct CabRespostaATN7
  {
        byte   Cmd;
        byte   Tamanho;
        byte   Transacao;
        byte   Status;
  } t_cab_rspATN7;

/*--- Resposta a comando de leitura de entradas/saidas digitais ---*/
typedef
  struct RespostaLeRackDigATN7
  {
        t_mascara_bitsATN7  Mascara;
        byte				Alarmes;
  } t_resp_le_digitaisATN7;

/*--- Resposta a comando de leitura da configuracao da remota ---*/
typedef
  struct RespostaLeConfigATN7
  {
        byte          TipoRemota;
        byte          AtualizaIO;
        t_mascara_bitsATN7  HabEnvLig;
        t_mascara_bitsATN7  HabEnvDesl;
        t_mascara_bitsATN7  HabSinalLig;
        t_mascara_bitsATN7  HabSinalDesl;
        t_mascara_bitsATN7  MascSinal;
        t_mascara_bitsATN7  ConfigIO;
/****** Inserido em 23/02/94 ******/
		/* bits a serem ligados qdo micro sair rede e desligados qdo voltar */
        t_mascara_bitsATN7  WatchdogLig;
		/* bits a serem desligados qdo micro sair rede */
        t_mascara_bitsATN7  WatchdogDesl;
        t_mascara_bitsATN7  EntradaTemp;  /* entradas cuja leitura e' temporizada */
        byte                    TempoEntrada; /* temporizacao - multiplo 50 ms */
        t_pisca_saidaATN7   SaidaAlimenta; /* pisca saidas qdo micro sair rede */
/****** Inserido em 23/02/94 ******/
		/* -- Tempo em segundos para a remota dar timeout micro fora da rede -- */
		byte				TempoWatchdog;
		word16				VersaoFirmware;	/* 0 a 65535 */
  } t_resp_le_configATN7;

/*--- Estrutura de um comando ---*/
typedef
  struct ComandoATN7
  {
	t_cab_cmdATN7	CabComando;
	union		
	{
	  /*--- Comandos enviados PARA as remotas ---*/
	  t_esc_saida_digATN7		EscSaidaDig[MAX_RACKS];
	  t_liga_saida_tempATN7		LigaSaidaTemp[MAX_RACKS];
	  t_desl_saida_tempATN7		DesligaSaidaTemp[MAX_RACKS];
	  t_pisca_saidaATN7			PiscaSaida[MAX_RACKS];
	  t_bloq_saida_tempATN7		BloqueiaSaidaTemp;
	  t_config_remotaATN7		ConfiguraRemota;
	  t_lista_acoesATN7			ListaComandos[MAX_CMD_LISTA_ATN7];
	  t_watchdogATN7			WatchATN7;
/* -- alteracao - inicio - 11/09/00 - Robson - Inclusao mensagem Atn8 -- */
	  t_watchdogATN8			WatchATN8;
/* -- alteracao - fim - 11/09/00 - Robson - Inclusao mensagem Atn8 -- */
	  t_tabela_dadosATN7		EscTabDados;
	  t_config_sh				ConfSH;

	  /*--- Comandos enviados PELAS remotas ---*/
	  t_altera_ent_digATN7		InfAltEntDig[MAX_RACKS];
/* -- alteracao - inicio - 11/09/00 - Robson - Inclusao mensagem Atn8 -- */
	  t_inf_ana_digATN8			InfAnaDig[MAX_RACKS];
/* -- alteracao - fim - 11/09/00 - Robson - Inclusao mensagem Atn8 -- */
	} TipoCom;
  } t_comandoATN7;

/*--- Estrutura de uma resposta ---*/
typedef
  struct RespostaATN7
  {
	t_cab_rspATN7	CabResposta;
	union
	{
	  t_resp_le_digitaisATN7	RespostaLeRackDig[MAX_RACKS];
	  t_resp_le_configATN7		RespostaLeConfig;
	  t_tabela_dadosATN7		RespostaTabDados;
	} TipoResp;
  } t_respostaATN7;

/* -- Estrutura das mensagens de comando/resposta da remota -- */
typedef
  struct MsgRemota
  {
	union
	{
	  t_respostaATN7	Resposta;
	  t_comandoATN7		Comando;
    } Dados;
  } t_msg_remota;

#endif		/* -- ifndef _REMOTA_ATN7_H -- */

/* -- fim do arquivo RemotaAtn7.h -- */
