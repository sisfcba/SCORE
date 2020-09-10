/******************************************************************************
 
			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO  : TODOS

	SISTEMA  : GERAL

	ARQUIVO  : Score.h

	CONTEUDO : Contem as definicoes de todas as constantes especificas do
			   Sistema de Controle de Reducoes.
			   Possui tambem as definicoes das estruturas de dados da
			   base de dados em area comum de memoria e as definicoes
			   das estruturas usadas nas trocas de mensagens.

	AUTOR    : Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO   : 2.0		  -	  DATA  : 28/04/94

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
28/04/94 | Edicao inicial de migracao para o QNX 4.2			| Leonel
-------------------------------------------------------------------------------
14/02/95 | Criacao da variavel TrataTPinos na tabela t_est_avc	| Carlos
-------------------------------------------------------------------------------
02/03/95 | Criacao da variavel TAtivaLinha na tabela avl e das	| Leonel
         | variaveis IntervJanRRap e TEfeitoTPinos em AVC.Param.|
-------------------------------------------------------------------------------
21/03/95 | Criacao da variavel ManualControle                 	| Leonel
-------------------------------------------------------------------------------
27/03/95 | Criacao da variavel HabLogOper na tabela avl        	| Carlos
-------------------------------------------------------------------------------
27/03/95 | Criacao de variaveis e tabela para incremento de ope	| Leonel
-------------------------------------------------------------------------------
21/08/95 | Criacao de variaveis para o novo algoritmo prev. Ea 	| Leonel
-------------------------------------------------------------------------------
20/11/95 | Inclusao da variavel InibeControle no EstAvc.       	| Leonel
-------------------------------------------------------------------------------
26/12/95 | Acrescentado tratamento de alarmes para PAl          | Carlos
-------------------------------------------------------------------------------
06/01/96 | Inclusao da variavel EaPrevVirada no EstAvc.        	| Carlos
-------------------------------------------------------------------------------
07/03/96 | Adaptacao das estruturas de usuario para albras/alcan| Carlos
-------------------------------------------------------------------------------
21/05/96 | Criacao de novas estruturas para usuario             | Leonel
-------------------------------------------------------------------------------
16/09/96 | Inclusao da variavel TDesabLinha no AVL.            	| Carlos
-------------------------------------------------------------------------------
09/10/96 | Inclusao das variaveis IInteg1h e VInteg1h no AVL.  	| Carlos
-------------------------------------------------------------------------------
19/11/96 | Inclusao das variaveis de ajuste de camisa para CBA 	| Carlos
-------------------------------------------------------------------------------
17/12/96 | Inclusao das variaveis do relat. estat. Ea para CBA 	| Carlos
-------------------------------------------------------------------------------
23/05/97 | Alteracao das tabelas de conversores do Atn1.4 para 	| Leonel
         | permitir livre escolha de canais para cuba e especial|
-------------------------------------------------------------------------------
16/07/98 | Transferencia das variaveis de ajuste para ScoreCBA 	| Carlos
-------------------------------------------------------------------------------
17/07/98 | Criacao da variavel HoraCorrAnt                     	| Carlos
-------------------------------------------------------------------------------
20/08/98 | Inclusao das variaveis IIntegRes1h no AVL.          	| Carlos
-------------------------------------------------------------------------------
03/02/99 | Inclusao de variaveis p/ contabilzacao de estatisti- | Leonel
         | cas de comunicacao da rede Echelon.                  |
-------------------------------------------------------------------------------
14/05/99 | Inclusao variavel para sistema em ajuste de hora.   	| Leonel
-------------------------------------------------------------------------------
14/05/99 | Inclusao de variaveis para calculo de corrente e ten-| Leonel
         | sao da linha medias horarias para ser utilizado quan-|
         | do sistema estiver em ajuste de hora (integracao in- |
         | valida neste periodo)                                |
-------------------------------------------------------------------------------
22/06/99 | Inclusao das variaveis para booster de corrente.    	| Carlos
-------------------------------------------------------------------------------
13/09/99 | Incluidas variaveis p/ estatistica de erros de       | Leonel
         | conversao A/D (atn1.4).                              |
-------------------------------------------------------------------------------
31/01/01 | Inclusao de variaveis para calibracao da atn8 - CBA  | Leonel
-------------------------------------------------------------------------------
29/11/01 | Inclusao das variaveis NumGruposCuba, NumCubasGrupo  | Bandeira
		 | no comum, e GrupoCuba, PosGrupoCuba no Abs / IHM PH	|
-------------------------------------------------------------------------------
07/01/02 | Aumento da base de dados CBA 125ka                   | Bandeira
-------------------------------------------------------------------------------
24/01/02 | Tratamento de 2 pcltas - CBA 125ka                   | Leonel
-------------------------------------------------------------------------------
06/02/03 | Inclusao variaveis para media de correntes lidas das | Leonel
         | AtnCa (atn8 - CBA) no AVL                            |
-------------------------------------------------------------------------------
******************************************************************************/
/*********************************** Revisoes ********************************\
$Id: Score.h,v 1.30.2.4 2015/10/30 12:40:48 leo Exp $

$Log: Score.h,v $
Revision 1.30.2.4  2015/10/30 12:40:48  leo
Inclusao de novo algoritmo para utilizacao da corrente da linha de forma
emergencia quando detectado que a corrente de uma cuba desviou (exemplo:
quando abre o loop de corrente).

Revision 1.30.2.3  2015/07/02 14:08:28  clage
Alteracao para sala II com ATN8 e atualizacao dos algoritmos da CBA ate esta data.

Revision 1.1.1.1.10.1  2012/09/28 17:09:17  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

Revision 1.30  2008/11/27 21:26:37  marcelo
Inclusao de variaveis para novo tratamento de ruido lento da mesma forma
que o ruido rapido.

Revision 1.29  2008/10/13 17:49:20  leo
Variaveis para o algoritmo de manobra de cruzeiro.

Revision 1.28  2008/08/04 20:31:06  leo
Incluida variavel para bit do rele de falha MM (CBA).

Revision 1.27  2008/08/01 20:51:31  leo
Incluidas variaveis para tratamento de falha de sopro automatico.
Incluida variavel para contabilizar DxLim (EstatEa) durante espera de EA
para retirar ao final a diferenca.

Revision 1.26  2008/07/08 13:26:51  leo
Incluidos novos limites para tratamento de ruidos.

Revision 1.25  2008/07/02 20:23:43  alex
nao subir camisa junto com movimentacao de anodo

Revision 1.24  2008/07/01 13:28:09  leo
Inclusao de novos parametros para novas acoes Tabela de EA (TEaLimiteVMaior,
TEaLimiteVMenor e TEaMaxSopros).

Revision 1.23  2008/03/25 18:35:32  leo
Criado flag global para indicar quando drvana partiu para sincronizar
inicio de funcionamento do redeatn8. Antes de ligar o flag os pacotes
de analogicos das remotas sao descartados.

Revision 1.22  2008/02/07 14:15:06  leo
Correcoes durante pre-operacao sala I atn8

Revision 1.21  2007/06/15 19:54:44  rogerio
DurEa estava como byte, que e insuficiente. Foi entao alterado para short unsigned int.

Revision 1.20  2007/03/02 18:45:51  leo
Correcao tratamento para manobra de cruzeiro

Revision 1.19  2007/02/28 22:22:19  leo
Inclusao de tratamento de manobra de cruzeiro.

Revision 1.18  2007/02/27 00:24:43  rogerio
Criacao do relatorio de estatistica de EA detalhado.

Revision 1.17  2006/12/27 14:55:53  leo
Incluida variavel TUltEa para indicar tempo em relacao ao ultimo EA (grafico
de cubas - controle)

Revision 1.16  2006/12/21 18:04:15  alex
novo ope tabela alternativa

Revision 1.15  2006/01/09 19:37:12  clage
Inclusao de variaveis de trabalho para calculo de integracao de 1h

Revision 1.14  2005/06/17 12:13:59  clage
Incluidas variaveis do relat. de integracao e trat. VInst > VEaXLim no EA

Revision 1.13  2004/08/10 12:45:46  clage
Expansao de 1280 bytes na area de supervisao do AVL

Revision 1.12  2004/08/06 21:08:22  clage
Incluida expansao de 1280 bytes para area de supervisao do AVL

Revision 1.11  2004/07/28 20:00:10  leo
Inclusao variavel de percentual de erro para comparacao de valores da
Atn1.4 reserva com a principal para a CBA em sistemas com 2 Atn1.4.

Revision 1.10  2004/07/09 21:03:10  leo
Alteracao para inclusao de tratamento de retirada de cuba de leitura quando
em calibracao pelo programa CalibRemph.

Revision 1.9  2004/04/15 19:38:53  leo
Correcao comentario BitSireneEA.

Revision 1.8  2004/04/12 21:03:56  leo
Inclusao da configuracao do bit de sirene de EA por cuba para qdo remota
atn8 estiver fora de rede (sala 125kA VI).

Revision 1.7  2003/12/30 12:27:12  leo
Alteracao base de dados para relatorio estatistica de ea para incluir novas faixas

Revision 1.6  2003/06/20 17:47:13  alex
Colocado habilitacao e batentes para move e sopro nos vmi's

Revision 1.5  2003/06/18 19:54:33  alex
nova interface 1024x768

Revision 1.4  2003/04/22 16:58:33  leo
Inclusao de temperatura da atn8 no AVC.

Revision 1.3  2003/03/07 20:39:28  leo
Aumento da estrutura IHM no comum para aumentar logins phindows de 20 para 30.

\*********************************** Revisoes ********************************/

#ifndef		_SCORE_H

#define		_SCORE_H

#include <Definicao.h>
#include <Semaf.h>
#include <unistd.h>

/*
-------------------------------------------------------------------------------
							Constantes do Score
-------------------------------------------------------------------------------
*/
#include <ScoreConst.h>

/* -- Macros -- */
#include <Macros.h>

  /* -- Prologo com as estruturas especificas do projeto da Cba -- */
  #include	<ScoreCba.h>

/*
-------------------------------------------------------------------------------
						   Tipos de dados
-------------------------------------------------------------------------------
*/
#ifndef	T_MASCARA_BITS
  #define	T_MASCARA_BITS

  /* -- Mascara de bits para comandos de ligar/desligar saidas digitais -- */
  typedef
	struct MascaraBits
	{
	  unsigned int Mascara1;
	  unsigned int Mascara2;
	} t_mascara_bits;
#endif

/* *********************** Tabela de outras remotas ************************ */
/* -- Tabela para outras remotas que nao de cuba ligadas no sistema -- */
typedef
  struct OutrasRemotas
  {
/* -- Alteracao - inicio - 02/04/2002 - Leonel - Inclusao tratamento de mais de um canal (pcltas) -- */
//	byte	SubRede;
	byte	Reserva1;	/* Alterado para short int */
/* -- Alteracao - fim - 02/04/2002 - Leonel - Inclusao tratamento de mais de um canal (pcltas) -- */
	byte	Nodo;
	byte	BitWatchdogLig;	/* Bit p/ watchdog da remota. Sem watchdog -> bit=255 */
	byte	Tipo;			/* para identificar tipo de dispositivo (PAL, self healing etc) */
/* -- alteracao - inicio - 12/09/00 - Robson - Tratamento da Atn8.0 -- */
	byte	NumAnasAtn8;	// numero de entradas analogicas definidas na remota
/* -- Alteracao - Inicio - 24/01/2002 - Leonel - Sala 125ka 5 - red 7 -- */
	unsigned short int	SubRede;	/* Qual canal (placa pclta) esta conectada a remota e qual subrede
									  CCSS, onde CC=canal (0 a 7) e SS=subrede (1 a 254) )*/
	byte	Reserva[1];
//	byte	Reserva[3];
/* -- Alteracao - Fim - 24/01/2002 - Leonel - Sala 125ka 5 - red 7 -- */
/* -- alteracao - fim - 12/09/00 - Robson - Tratamento da Atn8.0 -- */
  } t_outras_rem;

/* -- Padrao de mensagem utilizado no Score -- */
typedef
  struct RegMens
  {
	int	Origem;
	int	Acao;
	int	Parametro[8];
  } t_mens_padrao;

/* ********************* Tabela de descricao dos programas ***************** */
typedef
  struct nodo_prog
	{
	  unsigned int	TidProg;
	  char			NomeProg[40];
	  int			TtyProg;
	  int			FlagsCriacao;
	  int			Prioridade;
	  char			ProgStdin[12];
	  char			ProgStdout[12];
	  char			ProgStderr[12];
	} t_reg_prog;

typedef
  struct desc_prog
  {
	t_reg_prog Prog[MAX_PROGS_SCORE];
  } t_descprog;

/* ************************ Tabela de senhas ******************************* */
typedef struct operador
{
  char		Identificacao[40];
  char		SenhaOper[8];
  int		NivelAcesso;
} t_operador;
	
typedef
  volatile struct senhas
  {
	t_operador Operador[MAX_OPERADORES];
  } t_senhas_operacao;

/* ******************** Tabela de controle dos logs ************************ */
typedef
  volatile struct LogNode
  {
	unsigned LogSonTid,
			 CountLog,
			 CubaLog,
			 NvarLog;
	char	 LogFname[40];
	int		 NextLog;
    struct {
      char	    NomeVar[20];
	  byte		TabVar;
	  byte		TabVarLim;
      char      UEvar[20];
      char      FmtVar[11];
      float     FatConv;
      float     LimInf;
      float     LimSup;
    } Var[MAX_VAR_LOG];
    char     Trigger_ON[20];
    char     Trigger_OFF[20];
    byte     Condicao_ON;
    byte     Condicao_OFF;
    float    Compara_ON;
    float    Compara_OFF;
	byte	 TipoLog;

    short int TabVarON;
    short int TabVarOFF;
	short int TempoTrigger;
    float FatConvON;
	float FatConvOFF;
	short int FatorMulti;
	byte	 AtivaAuto;
    char     reserva[32];
  } t_log_node;

typedef
  volatile struct log
  {
	t_log_node TabTid[MAX_LOGS_ATIVOS];
	int		   TidHead;
	int		   TidFree;
	int		   ResTLog[10];
  } t_log;

/* ****************** Tabelas de eliminacao de efeito anodico ************** */
typedef
  volatile struct elim_ea
  {
	struct passo
	{
	  int	Acao;
	  int	Duracao;
	} Passo[MAX_PASSOS_ELIM_EA];
  } t_elimina_ea;

typedef
  volatile struct tab_elim_ea
  {
	t_elimina_ea TabEa[NUM_TABS_EA];
  } t_tabs_elim_ea;

/* ********************** Tabela descritora de eventos ********************* */
typedef
	struct RegDescEventos
	{
	  int 		Grupo;			/*Registra, Imprime, Exibe e suas combinacoes */
	  int 		Dispositivo;	/*Todos, Console Rede, Console Rede Terminal */
	  char		Mneumonico[11];
	  char		Msg[80];
	  int		EvCuba;			/*Se Verdade evento relativo a Cuba */
	  int		TipoParEv[N_PAR_EV];
	  byte		Reserva[17];
	} t_reg_desc_ev;

typedef
  volatile struct DescEventos
  {
	t_reg_desc_ev	DescEv[MAX_EVS];
  }t_desc_ev;

/* ************************ Tabelas descritoras do SAD ********************* */
/* -- Tipo descritor de registro de entrada especial multiplexada do SAD -- */
typedef
  volatile struct reg_ent_esp
  {
	short int IndSad;	 /* Indice no Atn1.4 para esta entrada */
	float	LsbEntEsp;	 /* -- Fator de conversao p/ Unidade de engenharia -- */
	float	OffEntEsp;	 /* -- Fator de correcao de offset -- */
	float	GanhoEntEsp; /* -- Fator correcao de ganho -- */
	float	CalibEntEsp; /* -- Constante de calibracao dos valores -- */
  } t_ent_esp;

/* -- Tabela descritora de conversores para entradas especiais multiplexadas
	  do SAD -- */
typedef
  volatile struct tab_conv_esp
  {
	struct RegTabDescConv
	{
	  int		NumEntEspeciais; /* -- numero de entradas especiais
									   utilizadas no projeto -- */
	  int		Reserva;
	  t_ent_esp	EntEsp[NUM_LEITURAS_ESP];		 /* 18x16=288 bytes -- leituras especiais -- */
	} LeitEsp;
  } t_conv_esp;

/* -- Tabela descritora de conversores para entradas nao multiplexadas
	  do SAD -- */
typedef
  volatile struct tab_conv_nmux
  {
	float	CalibNaoMux[8];	/* -- Constante de calibracao dos valores nao -- */
							/* -- multiplexados (correntes) -- */
	float	OffNaoMux[8];	/* -- Fator de correcao de offset de leituras dos -- */
							/* -- valores nao multiplexados -- */
	float	GanhoNaoMux[8];	/* -- Fator correcao de ganho na leitura dos valores -- */
							/* -- nao multiplexados -- */
  } t_conv_nmux;

/* -- Tabela descritora de conversores para entradas multiplexadas
	  do SAD (cubas) -- */

typedef
  volatile struct tab_conv_mux
  {
	short int IndSad;		/* posicao no Atn1.4 para leitura desta cuba */
	float	FcOffTensao;	/* Fator de correcao de offset de leitura da tensao */
	float	FcGanhoTensao;	/* Fator correcao de ganho na leitura de tensao */
  } t_conv_mux;

/* -- alteracao - inicio - 12/09/2000 - Robson - Inclusao tratamento Atn8 -- */
typedef
  /* -- Tabela das remotas de cuba -- */
  volatile struct tab_conv_atn8
  {
	float	Lsb[MAX_VALORES_POR_ATN8]; /* -- Fator de conversao p/ Unidade de engenharia -- */
	float	Offset[MAX_VALORES_POR_ATN8]; /* -- Fator de correcao de offset -- */
	float	Ganho[MAX_VALORES_POR_ATN8]; /* -- Fator correcao de ganho -- */
	float	Calib[MAX_VALORES_POR_ATN8]; /* -- Constante de calibracao dos valores -- */
	float	Rel[MAX_VALORES_POR_ATN8]; /* -- Constante de calibracao dos valores -- */
  } t_conv_cuba_atn8;

typedef
  /* -- Tabela das remotas que nao sao de cubas -- */
  volatile struct tab_ent_esp_atn8
  {
	/* -- alteracao - inicio - 28/12/2000 - Leonel - Tratamento de ent. esp. em qualquer atn8 -- */
//	short int IndOutrasRem;	/* -- Indice para tab. outras_rem indicando qual remota (atn8) -- */
//	float	LsbEsp[MAX_VALORES_POR_ATN8]; /* -- Fator de conversao p/ Unidade de engenharia -- */
//	float	OffEsp[MAX_VALORES_POR_ATN8]; /* -- Fator de correcao de offset -- */
//	float	GanhoEsp[MAX_VALORES_POR_ATN8]; /* -- Fator correcao de ganho -- */
//	float	CalibEsp[MAX_VALORES_POR_ATN8]; /* -- Constante de calibracao dos valores -- */
//	float	RelEsp[MAX_VALORES_POR_ATN8]; /* -- Relacao de grandeza por volt -- */
	short int IndRemEsp;	/* -- Indice para a remota onde esta a entrada (0..(MAX_CUBAS+NUM_OUTRAS_REM)-1 -- */
	byte	CanalEntEsp;	/* -- Qual canal na remota (0..MAX_VALORES_POR_ATN8-1) -- */
	float	LsbEsp; /* -- Fator de conversao p/ Unidade de engenharia -- */
	float	OffEsp; /* -- Fator de correcao de offset -- */
	float	GanhoEsp; /* -- Fator correcao de ganho -- */
	float	CalibEsp; /* -- Constante de calibracao dos valores -- */
	float	RelEsp; /* -- Relacao de grandeza por volt -- */
	byte	livreesp[59];
	/* -- alteracao - fim - 28/12/2000 - Leonel - Tratamento de ent. esp. em qualquer atn8 -- */
  } t_ent_esp_atn8;

typedef
  volatile struct tab_conv_esp_atn8
  {
    /* -- O numero de entradas especiais usadas no projeto continua na 
		  antiga variavel -- */
    t_ent_esp_atn8 EntEspAtn8[NUM_LEITURAS_ESP]; /* 82*16 = 1312 bytes */ 
  } t_conv_esp_atn8;
/* -- alteracao - fim - 12/09/2000 - Robson - Inclusao tratamento Atn8 -- */

/* -- Tabela descritora de parametros dos conversores. Unica para cada micro,
	  nao e' copiada para o micro reserva -- */
typedef
  volatile struct tab_conv
  {
	t_conv_nmux	ConvNMux;	/* 96 bytes -- dados dos conversores nao multiplexados (linha) -- */
	t_conv_esp	ConvEsp;	/* 296 bytes -- dados dos conversores multiplexados para
								  entradas especiais -- */
	t_conv_mux	ConvMux[MAX_CUBAS];	/* 10x180=1800 bytes -- dados dos conversores multip. (fornos) -- */
	/* -- alteracao - inicio - 12/09/2000 - Robson - Inclusao tratamento Atn8 -- */
	t_conv_cuba_atn8 ConvAtn8[MAX_CUBAS]; /* 80x180=14400 bytes -- dados dos conversores das cubas -- */
	t_conv_esp_atn8 ConvEspAtn8;     /* 1312 bytes -- dados das remotas que nao sao de cubas -- */
	/* -- alteracao - fim - 12/09/2000 - Robson - Inclusao tratamento Atn8 -- */
  } t_descr_conv;

/* ***************** Tabelas de incremento de operacao ********************* */
typedef
  volatile struct passo_tope
  {
	short int	TipoIncr;	/* Tipo do incremento (Const. ou rampa) -1=passo livre */
	short int	Tempo;		/* tempo do incremento em minutos */
	float		VSetPoint;	/* VSetPoint p/ este passo de incremento */
	float		VIncr;		/* Tensao inicial do incremento */
  } t_passo_tope;

typedef
  volatile struct tab_incope
  {
	t_passo_tope	Passo[MAX_PASSOS_TAB_OPE];
  } t_tab_ope;

typedef
  volatile struct tabs_incope
  {
	t_tab_ope		Tab[MAX_TAB_INC_OPE];
  } t_tabs_ope;

/* ******************************* AVC ************************************* */

/* -- Registros do Arquivo de Variaveis das Cubas - AVC -- */
typedef
  volatile struct absolutos_avc /* Valores absolutos do arquivo de variaveis das cubas */
  {
	/* -- Dados associados a remota ATN2.1 -- */
/* -- Alteracao - inicio - 02/04/2002 - Leonel - Inclusao tratamento de mais de um canal (pcltas) -- */
//	byte	CanalRemota;	/* Canal de comunicacao associado a remota */
	byte	Reserva;		/* Alterado para short int */
/* -- Alteracao - fim - 02/04/2002 - Leonel - Inclusao tratamento de mais de um canal (pcltas) -- */
	byte	NodoRemota;		/* Numero do nodo da remota na rede de comunicacao */
	/* -- Bits de saida -- */
	byte	BitSobeAnodo;	/* Bit para acionar o anodo p/ cima */
	byte	BitDesceAnodo;	/* Bit para acionar o anodo p/ baixo */
	byte	BitLampEa;		/* Bit para acionar lampada de EA */
	byte	BitLampRec;		/* Bit para acionar lampada de reconhecimento */
	byte	BitAvPistaoAQuebA;		/* Bit para avancar pistao A (point feeder) ou
									   acionar quebrador A */
	byte	BitRecPistaoAQuebB;		/* Bit para recuar pistao A (point feeder)  ou
									   acionar alimentador A */
	byte	BitAvPistaoBQuebC;		/* Bit para avancar pistao B (point feeder) ou
									   acionar quebrador B */
	byte	BitRecPistaoBouM2QuebD;	/* Bit para recuar pistao B (point feeder) ou acionar M2 ou 
									   acionar alimentador B */
	byte	BitSopro;				/* Bit para ativar sopro (point feeder) */
	byte	BitSobeCamisaouM1;		/* Bit para acionar camisa p/ cima ou acionar M1 */
	byte	BitDescCamOuAvPCAlimA;	/* Bit para acionar camisa p/ baixo ou avanco
	                            	   do pistao C para cubas com barra de quebra ou
									   acionar quebrador C */
	byte	BitRecuoPistCAlimB;		/* Bit para recuar pistao C para cubas com barra de quebra ou
									   acionar alimentador C */
	byte	BitAvancoPistDAlimC;	/* Bit para avancar pistao D para cubas com barra de quebra ou
									   acionar quebrador D */
	byte	BitRecuoPistDAlimD;		/* Bit para recuar pistao D para cubas com barra de quebra ou
									   acionar alimetador D */
	byte	BitSireneEA;			/* Bit do numero da saida de acionamento da sirene de EA qdo
							 fora de rede. Comeca de 1 e contem FF se nao configurado */
	byte	BitLiberaMCruzeiro;	/* Bit da saida para liberar manobra de cruzeiro */
	/* -- Bits de entrada -- */
	byte	BitChaveQueb;	/* Bit associado a botoeira de quebrada */
	byte	BitChaveCorr;	/* Bit associado a botoeira de corrida */
	byte	BitChaveLocRem;	/* Bit associado a chave local/remoto */
	byte	BitResetEa;		/* Bit associado a botoeira de reset lampada EA */
	byte	BitSubiuAnodo;	/* Bit associado a subida de anodo */
	byte	BitDesceuAnodo;	/* Bit associado a descida de anodo */
	byte	BitSubOuMovCamisaouM2;	/* Bit associado a subida de camisa (ou movimentacao
							   quando cuba com point feeder ou retorno de M2 */
	byte	BitDesCamOuPFAutoouM1; /* Bit associado a descida de camisa (ou auto/man 
							   quando cuba com point feeder ou retorno de M1 */
	byte	BitCheckUp;		/* Bit associado a botoeira de check up */
	byte	BitTrocaPinos;	/* Bit troca pinos */
	byte	BitSoprou;		/* Bit sopro ativado */
	byte	BitReleFalhaMM;	/* Bit indicacao rele de tempo MM atuado */
	byte	BitChaveMCruzeiro;	/* Bit da chave de manobra de cruzeiro */
	byte	BitResInp1[3];	/* Bit reserva */
	/* -- Outros absolutos -- */
	int		NumeroCuba;		/* Numero de operacao da cuba */
	int		LivreAbs1;
	float	DeltaUp;		/* Delta utilizado no calculo equivalente motor p/ cima */
	float	DeltaDown;		/* Delta utilizado no calculo equivalente motor p/ baixo */
	short int	SubRedeSirene;	/* Num. da subrede da remota que contem a sirene deste grupo */
	short int	NodoSirene;		/* Num. do nodo da remota que contem a sirene do grupo */
	byte	BitSirene;		/* Bit para acionamento da sirene na cuba deste grupo */
/* -- Alteracao - inicio - 22/09/2000 - Robson - Inclusao tratamento da ATN 8.0 -- */
	byte	NumAnasAtn8;	// numero de entradas analogicas definidas na remota
	byte	CubaIrma;		// cuba que esta associada a mesma remota desta cuba
/* -- Alteracao - fim - 22/09/2000 - Robson - Inclusao tratamento da ATN 8.0 -- */
/* -- Alteracao - inicio - 03/01/2001 - Leonel - Inclusao tratamento da ATN 8.0 -- */
	byte	CanalTensaoAtn8;	/* Canal onde esta conectada a tensao da cuba na atn8 de cuba */
	byte	CanalCorrAtn8;	/* Canal onde esta conectada a corrente da linha na atn8 de cuba */
	byte	GrupoCuba;		/* Grupo de operacao que esta cuba pertence */
	byte	PosGrupoCuba;	/* Posicao no Grupo que esta cuba pertence */
//	char	ResAbsAvc[9];	/* reserva */

/* -- Alteracao - Inicio - 24/01/2002 - Leonel - Sala 125ka 5 - red 7 -- */
	unsigned short int	CanalRemota;	/* Qual canal (placa pclta) esta conectada a remota e qual subrede
									  CCSS, onde CC=canal (0 a 7) e SS=subrede (1 a 254) )*/
	char	ResAbsAvc[65];	/* expansao + 58 reserva */
//	char	ResAbsAvc[67];	/* expansao + 58 reserva */
/* -- Alteracao - fim - 02/04/2002 - Leonel - Inclusao tratamento de mais de um canal (pcltas) -- */
/* -- Alteracao - fim - 03/01/2001 - Leonel - Inclusao tratamento da ATN 8.0 -- */
  } t_abs_avc;

typedef
  volatile struct parametros_avc /* Parametros e limites de processo da cuba */
  {
	float	AcresBCIQueb;	  /* Resistencia retirada da banda de controle inf.
								 apos quebrada, por um determinado tempo */
	float	AcresBCSCorr;	  /* Resistencia adicionada a banda de controle sup.
								 apos corrida, por um determinado tempo */
	float	AcrescBMortaSup;  /* Resistencia adicionada a banda morta sup. caso
								 a cuba esteja com demora em entrar em EA. */
	float	Bemf;			  /* Potencial de reducao `a corrente nominal */
	float	BandaContInf;	  /* Banda de controle inferior (micro ohms) */
	float	Reserva1;
	float	BandaContSup;	  /* Banda de controle Superior (micro ohms) */
	float	Reserva2;
	float	BandaMortaInf;	  /* Banda morta inferior (micro ohms) */
	float	BandaMortaSup;	  /* Banda morta Superior (micro ohms) padrao */
	float	Reserva3;
	int		DurMovBaixoMin;	  /* Duracao movimento para baixo minima (segs) */
	int		DurMovBaixoMax;	  /* Duracao movimento para baixo maxima (segs) */
	int		DurMovCimaMin;	  /* Duracao movimento para cima minima (segs) */
	int		DurMovCimaMax;	  /* Duracao movimento para cima maxima (segs) */
	float	IncCorrInic;	  /* Incremento inicial de tensao devido a corrida */
	float	IncTPinosInic;	  /* Incremento inicial de tensao devido a troca de pinos */
	float	DerivInibeMovBaixa;/* Lim. inf. derivada hist. para inibir mov. */
	float	IncQuebInic;	  /* Incremento inicial de tensao devido a quebrada */
	float	KPb;			  /* Ganho para acionamento dos motores para baixo */
	float	KPc;			  /* Ganho para acionamento dos motores para cima */
	float	KbpwmTipico;	  /* Const. pwm tipica para acion. dos motores para baixo */
	float	KcpwmTipico;	  /* Const. pwm tipica para acion. dos motores para cima */
	float	MinKbpwm;		  /* Const. pwm minima para acion. dos motores para baixo */
	float	MinKcpwm;		  /* Const. pwm minima para acion. dos motores para cima */
	float	VSetPointCnf;	  /* VSetPoint definido pelo operador */
	int		HabTabOpe;		  /* Habilita tabela de operacao qdo. verdadeiro */
	float	RMinPartidoSupEsp;	/* Resistencia min. p/ superv. especial de cuba partida */
	float	RMaxPartidoSupEsp;	/* Resistencia max. p/ superv. especial de cuba partida */
	float	RMinLigadoSupEsp;	/* Resistencia min. p/ superv. especial de cuba ligada */
	float	RMaxLigadoSupEsp;	/* Resistencia max. p/ superv. especial de cuba ligada */
	float	RMinDesligSupEsp;	/* Resistencia min. p/ superv. especial de cuba desligada */
	float	RMaxDesligSupEsp;	/* Resistencia max. p/ superv. especial de cuba desligada */
	int		TAcresBCIQueb;	  /* Tempo Acrescimo Banda Controle Inferior devido
								 a quebrada (seg) */
	int		TAcresBCSCorr;	  /* Tempo Acrescimo Banda Controle Superior devido
								 a corrida (seg) */
	int		TCalcEquivMotor;  /* Tempo max. esperado p/ ajuste de equiv. motor */
	byte	HabEvRuido;			/* Habilita/desab. geracao de evento de inicio/fim de ruido */
	byte	TemPF;				/* 0=Sem alim. auto., 1=tem point feeder, 2=tem quebra crosta */
	char	Reserva5[2];		/* Livre */
	int		NumTabOpe;			/* Numero da tabela de operacao associada a esta cuba */
	int		TEfeitoCorr;		/* Tempo do efeito da Corrida na Cuba */
	int		TEfeitoEa;			/* Tempo do efeito do EA na Cuba */
	int		TEfeitoMoveCima;	/* Tempo do efeito de movimentacao para cima */
	int		TEfeitoQueb;		/* Tempo do efeito da quebrada na cuba */
	int		TIncCorr;			/* Tempo de incremento de tensao devido a corrida */
	int		TIncTPinos;			/* Tempo de incremento de tensao devido a troca de pinos */
	int		TEfeitoMoveBaixo;	/* Tempo do efeito de movimentacao para baixo */
	int		TIncQueb;			/* Tempo de incremento de tensao devido a quebrada */
	int		Reserva7;			/* Livre */
	int		TipoIncTPinos;		/* Tipo de incremento de tensao devido a troca de pinos */
	int		Reserva8;			/* livre */
	int		TipoIncQueb;		/* Tipo de incremento de tensao devido a quebrada */
	float	EaEspLim;		 	/* Tensao limite do passo espera da supressao */
	float	VIncMax;			/* Tensao maxima que o somatorio dos incrementos
								   pode atingir */
	int		NumTabEliEaLento;  	/* Numero da tabela p/ eliminacao de EA Lento */
	int		NumTabEliEaRapido;	/* Numero da tabela p/ eliminacao de EA Rapido */
	int		NumTabEliEaMRapido; /* Numero da tabela p/ eliminacao de EA M. Rapido */
	int		NumTabEliEaAltern;	/* Numero da tabela p/ eliminacao de EA Alternativa */
	int		HabIncRLent; 		/* habilita incremento devido a ruido lento */
	int		HabIncRRap; 		/* habilita incremento devido a ruido rapido */
	int		HabEliminaEa;		/* habilita extincao de EA atraves de movimentacoes */
	/* -- Parametros relativos a ruido -- */
	char	Reserva9[16];		/* Livre */
	/* -- Parametros relativos a EA -- */
	int		EaAtrasoMax;		/* Tempo de atraso maxim de EA (minutos). Define
								   acrescimo de resistencia na banda morta superior */
	int		EaTPisca;			/* Indica tempo apartir do qual a lampada indicativa
								   de previsao de EA deve ser acionada (segundos) */
	int		EaTempoEspera;		/* Tempo de espera para fim de EA (segundos) */
	float	EaPrevDeriv;		/* Patamar de RSuaveDeriv acima do qual inicia-se a
								   previsao de efeito anodico */
	float	RSuaveDerivMin;		/* Derivada instantanea minima valida uohms/hora */
	float	EaVoltLim;			/* Patamar de tensao para identificacao de EA */
	float	KSuaveDeriv;		/* Parametro de suavizacao da derivada da
								   resistencia para previsao de EA */
	float	RSuaveDerivMax;		/* Derivada instantanea maxima valida uohms/hora */
	float	DerivHEaLento;		/* derivada historica p/ classificacao de EA uohms/hora */
	float	DerivHEaRap;		/* derivada historica p/ classificacao de EA uohms/hora */
	int		HabIncTPinos; 		/* habilita incremento de troca de pinos */
	int		TMaxIncOper;		/* Tempo maximo de incremento de operacao */
	char	Reserva10[16];		/* Livre */

	int		NumJanRRap;			/* Numero de janelas de 6Hs. p/ calc. ruido rapido */
	int		IntervJanRRap;		/* Intervalo em horas p/ cada janela de ruido
								   rapido (1,2,3,4,6 ou 8 horas) */
	int		TEfeitoTPinos;		/* Tempo efeito troca de pinos p/ inibir
								   previsao (segs) */
	float	DerivInibeMovAlta;	/* Lim. sup. derivada hist. para inibir mov. */
	int		IntervDerivInibeMov; /* Intervalo para analise da derivada historica
								   para inibir movimentacao */
	int		IntervEaPrevDeriv;	/* Intervalo para analise da derivada historica
								   para inicio de previsao */
	float	EaPrevDerivFim;		/* Patamar de RSuaveDeriv abaixo do qual cancela-se
								   a previsao de efeito anodico */
	int		IntervFimEaPrevDeriv; /* Intervalo para analise da derivada historica
								   para fim de previsao */
	float	IncUsuarioInic;		/* Incremento inicial de tensao do usuario */
	int		TIncUsuario;		/* Tempo de incremento de tensao do usuario */
	int		TipoIncUsuario;		/* Tipo de incremento de tensao do usuario */
	int		HabIncUsuario; 		/* habilita incremento de usuario */
    short unsigned NumAlgCtr;   /* numero do algoritimo de controle da cuba */
	short int NCicIniEaTAnodo;	/* Numero de ciclos acima de EaVoltLim para identificar
								   inicio de EA qdo em troca de anodo/pinos */
	short int NCicIniEaNormal;	/* Numero de ciclos acima de EaVoltLim para identificar
								   inicio de EA qdo nao esta em troca de anodo/pinos */
	short int HabPrevEa;		/* Habilita algoritmo de previsao de Ea do Score */
	short int HabContResist;	/* Habilita algoritmo de controle de resistencia do Score */
	float	VEaForte;		 	/* Tensao minima para exibir VEaMax em relatorio */
	float	VEaFraco;		 	/* Tensao maxima para exibir VEaMax em relatorio */
	short int FreqEa;			/* No. minimo de Ea para exibir NumEa em relatorio */
	short int NJanRRapCons;		/* No. janelas consec. de ruido rapido p/ exibir em relatorio */
	short int NJanRLenCons;		/* No. janelas consec. de ruido lento p/ exibir em relatorio */
	short int TempoAtivaTEa;	/* Tempo a espera para ativar tabela de E. A. em segs. */
	byte	MaxAgarraAnodo;		/* Numero maximo de falhas de agarramento de anodo para passar
								   cuba para manual */
	byte	HabAtEa;			/* habilita tela p/ vmi p/ mov ou sopro quando em EA ou QPrev */

	short int TempoEvCuba;		/* tempo em minutos para analise de excesso de eventos p/ cuba */
	short int MaxEvCuba;		/* numero maximo de eventos para analise de excesso de eventos p/ cuba */

    byte	HabilitaBooster;	/* Habilita booster de corrente */
	float IBoosterNominal;	/* Corrente nominal para booster de corrente */
/* -- Inicio - 14/06/2005 - Carlos - Tensao EA acima de VEaParam -- */
	float VEaXLim;			/* Limite para contab. de tensao de EA acima de X Volts */
/* -- Fim - 14/06/2005 - Carlos - Tensao EA acima de VEaParam -- */
	int	TEfeitoCruzeiro;	/* Tempo efeito manobra de cruzeiro p/ inibir
							   previsao (segs) */
	float	TEaLimiteVMaior;	/* Tabela de EA: Acao V_MAIOR. Se Vinst >= TEaLimiteVMaior goto novo_passo */
	float	TEaLimiteVMenor;	/* Tabela de EA: Acao V_MENOR. Se Vinst < TEaLimiteVMenor goto novo_passo */
	short int	TEaMaxSopros;	/* Numero maximo de sopros na tabela de EA */
	byte	HabMovIniQueb;		/* Habilita mover p/ cima apos sinalizacao de quebrada */
	byte	TempMovIniQueb;		/* Tempo em segundos que vai subir apos sinalizacao da quebrada */
	float	RuidoL[5];			/* Limites para classificacao de ruido lento por nivel (os 3
	                               primeiros sao classificados como Fracos e os 2 restantes como fortes) */
	float	RuidoR[5];			/* Limites para classificacao de ruido rapido por nivel (os 3
	                               primeiros sao classificados como Fracos e os 2 restantes como fortes) */
	float	IncRuidoLento[5];	/* Incremento por ruido lento por nivel */
	float	IncRuidoRap[5];		/* Incremento por ruido Rapido nivel */

	int		NumJanRLent;		/* Numero de janelas de 6Hs. p/ calc. ruido lento */
	int		IntervJanRLent;		/* Intervalo em horas p/ cada janela de ruido
								   lento (1,2,3,4,6 ou 8 horas) */   
	short int	TIncPicoTPinos; /* Tempo de pico do incremento triangulo */
	byte	HabCorrEmerg;		/* Habilita tratamento de abertura do loop de corrente de cuba para usar corrente de linha */
	byte	ForcaCorrEmerg;		/* Forca uso da corrente de linha se HabCorrEmerg habilitado independente da diferenca para corrente de cuba */
	char    ResParAvc[31];      /* reserva */
  } t_param_avc;

typedef
  volatile struct ciclo_leitura_avc /* Valores de ciclo de leitura */
  {
	float	BemfInst;		/* Potencial de reducao - varia linearmente com I */
	float	Iinst;			/* corrente instantanea da linha associada a cuba */
	float	Rinst;			/* Resistencia instantanea da cuba */
	float	VetRinst[6];	/* Vetor de resistencias instantaneas para os
							   calculos dos filtros digitais */
	float	Vinst;			/* Tensao instantanea da cuba */
	float	Pinst;			/* Potencia instantanea na cuba */
	long	NumCiclosLeit;	/* Numero de ciclos de leitura validos */
	long	HoraUltQueb;	/* Hora da ultima quebrada */
	long	HoraUltCorr;	/* Hora da ultima corrida */
	long	HoraUltSelMan;	/* Hora da ultima selecao manual (chave em local ou
							   selecao de operacao manual) */
	long	HoraInicDesLeit;/* Hora de inicio da desabilitacao da leitura */

  	int		ContL;			/* contador de leituras por Cuba */
	int 	ContLInvalida;  /* contador de leituras invalidas */
	int		EstadoIO;		/* Estado atual dos pontos de I/O da remota */
	float	RCicCorr;		/* Resistencia media no ciclo de ajuste de corrida */
	int		ContLCicCorr;	/* Contador de leituras p/ ciclo de ajuste de corrida */
	long	HoraUltTPinos;	/* Hora da ultima troca de pinos */
	int		AlarmesIO;		/* Estado atual da mascara de alarmes da remota */
	char	StrGCubas1[MAX_CAR_GCUBAS];	/* String para exibicao no grafico de cubas */
	char	StrGCubas2[MAX_CAR_GCUBAS];	/* String para exibicao no grafico de cubas */
	char	StrGCubas3[MAX_CAR_GCUBAS];	/* String para exibicao no grafico de cubas */
	char	StrGCubas4[MAX_CAR_GCUBAS];	/* String para exibicao no grafico de cubas */
	char	StrGCubas5[MAX_CAR_GCUBAS];	/* String para exibicao no grafico de cubas */
	char	StrGCubas6[MAX_CAR_GCUBAS];	/* String para exibicao no grafico de cubas */
	char	StrGCubas7[MAX_CAR_GCUBAS];	/* String para exibicao no grafico de cubas */
	char	StrGCubas8[MAX_CAR_GCUBAS];	/* String para exibicao no grafico de cubas */
	char	StrGCubas9[MAX_CAR_GCUBAS];	/* String para exibicao no grafico de cubas */
	char	StrGCubas10[MAX_CAR_GCUBAS];	/* String para exibicao no grafico de cubas */
	long	HoraCorrAnt;	/* Hora da corrida anterior */
	float	IBoosterInst;	/* Corrente instantanea para booster de corrente */
/* -- Alteracao - inicio - 10/06/2002 - Leonel - Correcao tratamento de mais de um canal (pcltas) -- */
	short int RxPktsSec;	/* Numero de pacotes recebidos da rede echelon em um segundo */
	short int TxPktsSec;	/* Numero de pacotes transmitidos para a rede echelon em um segundo */
	int		TUltEa;		/* Tempo desde ultimo EA - usado no grafico de cubas (controle) */
	long	HoraUltCruzeiro;	/* Hora da ultima manobra de cruzeiro */
	char	ResLAvc[32];	/* expansao + 32 reserva */
//	char	ResLAvc[36];	/* expansao + 32 reserva */
/* -- Alteracao - fim - 10/06/2002 - Leonel - Correcao tratamento de mais de um canal (pcltas) -- */
  } t_cicleit_avc;

typedef
  volatile struct ccont_mcp_avc		/* Valores de ciclo de controle calculados pelo */
							/* modulo MCP */
  {
	float	RCicContlBruta;	/* Resistencia media bruta do ciclo de controle */
	float	RCicContlLiq;	/* Resistencia media liquida do ciclo de controle */
	float	RlentCicContl;	/* Componente de ruido lento (problemas de catodo)
							   da resistencia de ciclo de controle */
	float	RrapCicContl;	/* Componente de ruido rapido (problemas de anodo)
							   da resistencia de ciclo de controle */
	/* -- Valores para supervisao -- */
	float	PotCicContlBruta;/* Potencia media bruta do ciclo de controle */
	float	PotCicContlLiq;	/* Potencia media liquida do ciclo de controle */
	float	VCicContlBruta;	/* Tensao media bruta do ciclo de controle */
	float	VCicContlLiq;	/* Tensao media liquida do ciclo de controle */
	float	RCicContBrutaMed; /* Resistencia de ciclo controle calculada pela
							   media dos valores instantaneos */
	float	ICicContlMedCuba; /* Corrente media por cuba para o booster */
/* -- Alteracao - Inicio - 31/01/2001 - Leonel - Sala 86Ka -- */
	float	ValorEnt[MAX_VALORES_POR_ATN8];	/* valores lidos nos canais da remota de cuba */
/* -- alteracao - inicio - 05/12/2002 - Leonel - Disponibiliza diferenca de corrente na base de dados -- */
	float	IDifCuba;		/* Diferenca de corrente da cuba para principal da linha */
/* -- alteracao - inicio - 09/04/2003 - Leonel - Disponibiliza temperatura atn8 no AVC -- */
	byte	TemperaturaAtn8;	/* Temperatura da atn8 de cuba */
	float	IRapCicContl;		/* -- Componente de ruido rapido da corr. da linha -- */
	char	ResCContAvc[31]; /* reserva */
  } t_ccont_mcp_avc;

typedef
  volatile struct ciclo_controle_avc /* Valores de ciclo de controle */
  {
	float	DuracaoUltMove;	/* Duracao da ultima movimentacao de anodo */
	long	HoraUltMove;	/* Hora da ultima movimentacao de anodo */
	long	HoraUltVDesv;	/* Hora do ultimo desvio de tensao */
	float	IncCorr;		/* Incremento de tensao devido a corrida recente */
	float	IncTPinos;		/* Incremento de tensao devido a EA recente */
	float	IncOper;		/* Incremento de tensao definido pelo operador */
	float	IncQueb;		/* Incremento de tensao devido a quebrada recente */
	float	IncRlent;		/* Incremento de tensao devido a ruido lento */
	float	IncRrap;		/* Incremento de tensao devido a ruido rapido */
	int		ContIncCorr;	/* Quanto tempo a cuba esta c/ incremento devido a
							   corrida (min) */
	int		ContIncQueb;	/* Quando tempo a cuba esta c/ incremento devido a
							   Quebrada (min) */
	int		ContIncTPinos;		/* Quando tempo a cuba esta c/ incremento devido a
							   troca de pinos (min) */
	int		ContIncOper;	/* Quando tempo a cuba esta c/ incremento de
							   Operacao (min) */
	float	Kbpwm;			/* Const. pwm para acionamento dos motores para baixo */
	float	Kcpwm;			/* Const. pwm para acionamento dos motores para cima */
	float	RAlvo;			/* Resistencia alvo (Setpoint + incrementos) */
	float	RAlvoUltMove;	/* Resistencia alvo utilizada na ultima movim. de ando */
	float	Rerro;			/* RAlvo - RCicContlBruta */
	float	Rinc;			/* Resistencia de incrementos */
	int		SentidoUltMove;	/* Sentido da ultima movimentacao de anodo */
	float	VAlvo;			/* Tensao alvo (VSetPoint + incrementos) */
	float	VErro;			/* Tensao Erro (VAlvo - VCicContlBruta) */
	short int PassoTabOpe;	/* Passo atual qdo. executando tabela de inc. operacao */

	float	IncUsuario;		/* Incremento de tensao do usuario */
	int		ContIncUsuario;	/* Quando tempo a cuba esta c/ incremento devido a
							   programa de controle de usuario (min) */
	float	Vinc;			/* Resistencia de incrementos exibida em tensao */
	byte	Reserva1;		/* Livre */
	byte	ContAgarraAnodo;	/* Contador de provavel agarramento de anodo */
	float	RErroUltMove;	/* RErro da ultima movimentacao */
	int		Reserva3;		/* Livre */
	float	BandaContInfAtual; /* Banda de controle inferior atual (micro ohms) */
	float	BandaContSupAtual; /* Banda de controle Superior atual (micro ohms) */
	float	BandaMortaSupAtual; /* Banda morta Superior (micro ohms) atual */
	float	VSetPoint;		 	/* Tensao de placa da cuba */
	int		HabIncOper; 		/* habilita incremento de operacao */
	float	IncOpInic;		  /* Incremento inicial de tensao definido pelo operador */
	int		TIncOp;				/* Tempo de incremento de tensao definido pelo operador */
	int		TipoIncOp;			/* Tipo de incremento de tensao definido pelo operador */
	int		TipoIncCorr;		/* Tipo de incremento de tensao devido a corrida */
	float	IAlvoCuba;		/* Corrente alvo por cuba para o booster */
	float	INominalCuba;	/* Corrente nominal por cuba para o booster */
	char	ResCAvc[68];	/* reserva + 32 */
  } t_ciccont_avc;

typedef
  volatile struct ea_avc  /* Valores relativos a Efeito Anodico e a sua previsao */
  {
	int		EaContL;		/* Contador de leituras durante o efeito anodico */
	int		EaContLEsp;		/* Contador de leituras durante a espera do final do
							   efeito anodico */
	long	EaDur;			/* Tempo de duracao do efeito anodico (em segs) */
	float	EaEnergBruta;	/* Energia bruta dissipada no Efeito Anodico */
	float	EaEnergLiq;		/* Energia liquida dissipada no Efeito Anodico */
	long	EaHoraFimProv;	/* Hora provavel do fim do efeito anodico */
	long	EaHoraInicio;	/* Hora de inicio do efeito anodico */
	long	EaHoraPrev;		/* Hora provavel de ocorrencia do efeito anodico */
	int		EaNumL;			/* Numero de leituras em efeito anodico (do ultimo) */
	float	EaPotAcumBruta;	/* Potencia bruta acumulada durante um efeito anodico */
	float	EaPotAcumEspBruta;/* Potencia bruta acumulada de espera para fim de
								 um efeito anodico */
	float	EaPotAcumEspLiq;/* Potencia liquida acumulada de espera para fim de
							   um efeito anodico */
	float	EaPotAcumLiq;	/* Potencia liquida acumulada durante um efeito anodico */
	float	EaPotBruta;		/* Potencia media bruta do efeito anodico */
	float	EaPotLiq;		/* Potencia media liquida do efeito anodico */
	float	EaPrevLim;		/* Patamar de resitencia para inicio da previsao de
							   efeito anodico */
	long	EaPrevT0;		/* Hora de inicio da previsao de Ea */
	float	EaRLim;			/* Resistencia equivalente a EaVoltLim */
	float	EaVAcumBruta;	/* Tensao bruta acumulada de EA */
	float	EaVAcumEspBruta;/* Tensao bruta acumulada de espera para fim de EA */
	float	EaVAcumEspLiq;	/* Tensao liquida acumulada de espera para fim de EA */
	float	EaVAcumLiq;		/* Tensao liquida acumulada de EA */
	float	EaVBruta;		/* Tensao media bruta de EA */
	float	EaVLiq;			/* Tensao media liquida de EA */
	float	EaVMax;			/* Tensao maxima atingida pelo EA */
	float	EaVMin;			/* Tensao minima atingida pelo EA */
	int		EaClasse;		/* Classificacao do efeito anodico (lento,rapido e
							   muito rapido) */
	float	KSuave;			/* Parametro de suavizacao da resistencia para pre-
							   visao de EA */
	float	RSuave;			/* Resistencia suavizada do ciclo de controle para
							   previsao de EA */
	float	RSuaveAnt;		/* Resistencia suavizada do ciclo de controle
							   anterior para previsao de EA */
	float	RSuaveDeriv;	/* Derivada da resistencia suavizada (previsao EA) */
	float	RSuaveDerivH;	/* Media historica da derivada da resistencia
							   suavizada (previsao EA) */
	float	DerivHMinPrevEa; /* Menor derivada historica no periodo de analise
							    de previsao */
	float	DerivHMaxPrevEa; /* Maior derivada historica no periodo de analise
							    de previsao */
	float	DerivHFimPrevEa; /* Maior derivada historica no periodo de analise
							    para para sair de previsao */
	float	DerivHMaxInibMov; /* Maior derivada historica no periodo de analise
							    para inibir movimentacao */
	int		CiclosIniPrev;	/* Numero de ciclos de controle p/ analise de previsao */
	int		CiclosFimPrev;	/* Numero de ciclos de controle p/ fim de previsao */
	int		CiclosInibeMov;	/* Numero de ciclos de controle p/ analise de
							   inibicao de movimentacao */
	long	EaHoraAnt;		/* Hora de inicio do efeito anodico anterior */
/* -- Inicio - 14/06/2005 - Carlos - Tensao EA acima de VEaParam -- */
	unsigned short int EaContLXLim;	/* Contador de cic. de leit. de tensao EA acima de VEaXLim */
/* -- Fim - 14/06/2005 - Carlos - Tensao EA acima de VEaParam -- */
	long	DurTabEaAltern; /* tempo de ativacao da tabela alternativa de ea (seg) */
	long	IniTabEaAltern; /* inicio de ativacao da tabela alternativa de ea (seg) */
	unsigned short int EaContLEspXLim;	/* Contador de cic. de leit. de tensao EA acima de VEaXLim em espera de fim ea */
	char	ResEaAvc[84];	/* reserva */
  } t_ea_avc;

typedef
  volatile struct ruido_avc /* Valores relativos a ruido */
  {
	long	HoraInicioRLent;/* Hora que teve inicio o acrescimo por ruido lento */
	long	HoraInicioRRap;	/* Hora que teve inicio o acrescimo por ruido rapido */
	float	RlentCContVal;	/* resistencia lenta de ciclo de controle valida */
	float	RrapCContVal;	/* resistencia rapida de ciclo de controle valida */
    float	Rlent6Hs;		/* Resistencia lenta acumulada em 6 horas */
	float	Rlent48Hs;		/* Resistencia lenta acumulada nas ult. 48hs */
	float	RlentInst;		/* Componente de ruido lento da resistencia instantanea */
	float	Rrap6Hs;		/* Resistencia rapida acumulada em 6 horas */
	float	Rrap48Hs;		/* Resistencia rapida acumulada nas ult. 48hs */
	float	RrapInst;		/* Componente de ruido rapido da resistencia
							   instantanea */
	int		TipoRLent;		/* Tipo de ruido lento atual (fraco ou forte) */
	int		TipoRRap;		/* Tipo de ruido rapido atual (fraco ou forte) */
	float	VetRrap[N_AMOSTRAS_RRAP];	/* Vetor de resistencia rapida de 6 horas */
	int		ContInibeRuido;	/* inibe tratamento de ruido durante o num. de ciclos
							   indicado (0=habilita) */
	float	RInstFiltPB;	/* Resistencia instantanea filtrada pelo filtro
							   passa baixas */
	float	RlentAcum;		/* Resistencia acumulada de ruido lento para comparacao
							   com as faixas de classificacao */
    float   VetRlent[N_AMOSTRAS_RLENT]; /* Vetor de resistencia lenta de 6 horas */
	/* Copia dos parametros de ruido para detectar sua variacao */
	int		BackNumJanRLent;		/* Backup do Numero de janelas de 6Hs. p/ calc. ruido lento */
	int		BackIntervJanRLent;		/* Backup do Intervalo em horas p/ cada janela de ruido
							   lento (1,2,3,4,6 ou 8 horas) */   
	int		BackNumJanRRap;			/* Backup do Numero de janelas de 6Hs. p/ calc. ruido rapido */
	int		BackIntervJanRRap;		/* Backup do Intervalo em horas p/ cada janela de ruido
								   rapido (1,2,3,4,6 ou 8 horas) */
	/* Copia dos parametros de ruido para detectar sua variacao */
    char    ResRAvc[52];    /* reserva */
    //char    ResRAvc[68];    /* reserva */
  } t_ruido_avc;


/* -- AVC principal -- */
typedef
  volatile struct arq_var_cubas /* Arquivo de variaveis das cubas */
  {
	/* -- Valores absolutos -- */
	t_abs_avc		Abs[MAX_CUBAS];
	/* -- Parametros -- */
	t_param_avc		Param[MAX_CUBAS];
	/* -- Valores de ciclo de leitura -- */
	t_cicleit_avc	Cleit[MAX_CUBAS];
	/* -- Valores de ciclo de controle calculados pelo modulo MCP -- */
	t_ccont_mcp_avc	CcontMcp[MAX_CUBAS];
	/* -- Valores de ciclo de controle -- */
	t_ciccont_avc	Ccont[MAX_CUBAS];
	/* -- Valores relativos a Efeito Anodico -- */
	t_ea_avc		Ea[MAX_CUBAS];
	/* -- Valores relativos a ruido -- */
	t_ruido_avc		Ruido[MAX_CUBAS];
	/* -- Tabela disponivel para programas de usuario -- */
	/* -- Estas duas primeiras estao reservadas para PARAMETROS. Podem ser
	      atualizadas pelo programa de configuracao de cubas -- */
	t_par1_user		ParUser1[MAX_CUBAS];
	t_par2_user		ParUser2[MAX_CUBAS];
	/* -- Tabelas reservadas para variaveis de trabalho -- */
	t_user1_avc		User1[MAX_CUBAS];
	t_user2_avc		User2[MAX_CUBAS];
	t_user3_avc		User3[MAX_CUBAS];
	t_user4_avc		User4[MAX_CUBAS];
	/* -- Tabela disponivel para programas de usuario -- */
  } t_avc;

typedef
  volatile struct comum_avc {
	union rec_avc {
	  t_avc  Uavc;
	  char AvcBuf[MAX_AVC];  /* Espaco reservado para manutencao */
	} Avc;
  } t_comum_avc;


/* ************************* Supervisao AVC ******************************** */
typedef
  volatile struct supervisao_avc /* Tabela de valores diarios de supervisao das cubas */
  {
	float	BemfDia;		/* Media diaria do Bemf */
	int		CorrNumDia;		/* Numero de corridas no dia */
	long	DurContlDia;	/* Tempo de duracao do controle da cuba durante o
							   dia (segundos) */
	long	EaDurDia;		/* Duracao de efeito anodico acumulado no dia (segs) */
	float	EaEnergDiaBruta;/* Energia bruta de Efeito Anodico dissipada durante
							   o dia. */
	float	EaEnergDiaLiq;	/* Energia liquida de Efeito Anodico dissipada
							   durante o dia. */
	int		EaNumDia;		/* Numero de efeitos anodicos no dia */
	int		EaNumLDia;		/* Numero de leituras em efeito anodico no dia */
	float	EaPotDiaBruta;	/* Potencia media bruta de E. A. no dia */
	float	EaPotDiaLiq;	/* Potencia media liquida de E. A. no dia */
	float	EaPotDiaTotBruta;/* Potencia acumulada bruta de E. A. no dia */
	float	EaPotDiaTotLiq;	/* Potencia acumulada liquida de E. A. no dia */
	float	EaVDiaBruta;	/* Tensao media bruta de EA no dia */
	float	EaVDiaLiq;		/* Tensao media liquida de EA no dia */
	float	EaVDiaTotBruta;	/* Tensao total bruta de EA no dia */
	float	EaVDiaTotLiq;	/* Tensao total liquida de EA no dia */
	float	EnergDiaBruta;	/* Energia bruta dissipada no dia */
	float	EnergDiaLiq;	/* Energia liquida dissipada no dia */
	long	ForaLeitDurDia;	/* Tempo que a cuba esta fora de leitura (ticks sad->0.5seg) */
	long	ForaContDurDia;	/* Tempo que a cuba esta fora do controle (segs) */
	int		MovBaixoNumDia;	/* Numero de mov. p/ baixo de anodo no dia */
	float	MovBaixoDurDia;	/* Duracao acumulada de mov. p/ baixo de anodo no dia */
	int		MovCimaNumDia;	/* Numero de mov. p/ cima de anodo no dia */
	float	MovCimaDurDia;	/* Duracao acumulada de mov. p/ cima de anodo no dia */
	int		NumCContDia;	/* Numero de ciclos de controle p/ superv. no dia */
	int		NCContPotDia;	/* Numero de cic. cont. p/ calc. de potencia no dia */
	float	PotDiaAlvo;		/* Potencia alvo media do dia */
	float	PotDiaBruta;	/* Potencia media bruta do dia */
	float	PotDiaLiq;		/* Potencia media liquida do dia */
	int		QuebNumDia;		/* Numero de quebradas no dia */
	float	RDiaBruta;		/* Resistencia media bruta do dia */
	float	RDiaLiq;		/* Resistencia media liquida do dia */
	float	RAlvoDia;		/* Resistencia alvo media do dia */
	long	RLentDurDia;	/* tempo em SEGUNDOS que a cuba ficou com inc. de ruido lento */
	long	RRapDurDia;		/* tempo em SEGUNDOS que a cuba ficou com inc. de ruido rapido */
	float	VDesvDia;		/* Tensao media de desvio do dia */
	long	VDesvDurDia;	/* tempo em que a cuba ficou em desvio no dia */
	float	VDiaBruta;		/* Tensao media bruta do dia */
	float	VDiaLiq;		/* Tensao media liquida do dia */
	float	VForaContDia;	/* Tensao media fora do controle no dia */
	float	VSetPointDia;	/* Tensao media de placa da cuba no dia */
	int		EstPrincDia;	/* Estado principal que a cuba esteve no dia. Obedece
							   a seguinte ordem: DESLIGADO,LIGADO,PARTIDO,NORMAL */
	int		RLentFraDurDia;	/* duracao em MINUTOS do ruido lento fraco no dia */
	int		RLentForDurDia;	/* duracao em MINUTOS do ruido lento forte no dia */
	float	RLentFracoDia;	/* media do ruido lento fraco no dia */
	float	RLentForteDia;	/* media do ruido lento forte no dia */
	float	RLentFraIncDia;	/* Incremento medio devido a do ruido lento fraco no dia */
	float	RLentForIncDia;	/* Incremento medio devido a do ruido lento forte no dia */
	int		RRapFraDurDia;	/* duracao em MINUTOS do ruido rapido fraco no dia */
	int		RRapForDurDia;	/* duracao em MINUTOS do ruido rapido forte no dia */
	float	RRapFracoDia;	/* media do ruido rapido fraco no dia */
	float	RRapForteDia;	/* media do ruido rapido forte no dia */
	float	RRapFraIncDia;	/* Incremento medio devido a do ruido rapido fraco no dia */
	float	RRapForIncDia;	/* Incremento medio devido a do ruido rapido forte no dia */
	int		ContIncRuidoDia;/* Contador p/ medias de incremento de ruido no dia */
	float	IncRuidoDia;	/* incremento medio de ruido no dia */
	int		ContRLentNormDia;/* Contador p/ media de ruido lento normal no dia */
	float	RLentNormDia;	/* media de ruido lento normal no dia */
	int		ContRRapNormDia;/* Contador p/ media de ruido rapido normal no dia */
	float	RRapNormDia;	/* media de ruido rapido normal no dia */
	float	EaVMaxDia;		/* Maior tensao de efeito no dia */
	int		NumPrevEaDia;	/* Num. de vezes que entrou em previsao no dia */
	int		NumFimOkPrevDia; /* Num. de vezes que sai de previsao em situacoes
								conhecidas no dia */
	int		DurIncCorrDia;	/* Duracao total de incrementos de corridas no dia */
	float	IncCorrDia;		/* Tensao de incremento media por corrida no dia */
	int		DurIncQuebDia;	/* Duracao total de incrementos de quebrada no dia */
	float	IncQuebDia;		/* Tensao de incremento media por quebrada no dia */
	int		DurIncTPinosDia; /* Duracao total de incrementos de troca de pinos no dia */
	float	IncTPinosDia;	/* Tensao de incremento media por troca de pinos no dia */
	int		DurIncOperDia;	/* Duracao total de incrementos de operacao no dia */
	float	IncOperDia;		/* Tensao de incremento media por operacao no dia */
	int		DurIncTotDia;	/* Duracao total de incrementos no dia */
	float	IncTotDia;		/* Tensao de incremento media total no dia */
	int		FalhaMovDia;	/* Num. de vezes que ocorreram falhas de movimentacao */
	int		EfPrevEaDia;	/* Num. previsoes terminadas com Ea */
	int		DurPrevEaDia;	/* Duracao media entre as previsoes e os Ea realmente */
	int		DurIncUsuarioDia; /* Duracao total de incrementos de usuario no dia */
	float	IncUsuarioDia;	/* Tensao de incremento media por alg. de usuario no dia */
	byte 	AtrasoEa; 		/* Flag que indica ocorrencia de atraso de EA no dia */
	byte 	ClasseEa; 		/* Classif. do EA para o relatorio de controle de processo */
/* -- Alteracao - inicio - 15/12/2003 - Leonel - Aumentados vetores para atender solicitacao da CBA -- */
	byte 	ContDurEa[11];	/* Vetor de cont. de EA por duracao para rel. estat. EA */
/* -- Alteracao - inicio - 08/03/2005 - Carlos - Relat. estatistica EA diario/turno -- */
//	byte 	ContIntEa[11];	/* Vetor de cont. de EA por intervalos entre o anterior */
	byte 	Reserva1[11];	/* Vetor de cont. de EA por intervalos entre o anterior */
	byte 	ContVMaxEa[8];	/* Vetor de cont. de EA por VMax para rel. estat. EA */
	byte	Res1;
//	byte 	ContPrevEa[7];	/* Vetor de cont. de EA por previsao para rel. estat. EA - MOVIDO PARA FIM DA AREA */
/* -- Alteracao - fim - 15/12/2003 - Leonel - Aumentados vetores para atender solicitacao da CBA -- */
	short unsigned AlgCtrlDia; /* Algoritmos de controle que atuaram no dia */
  #ifdef	USA_REDE_ECHELON
	/* Estatistica de comunicacao para a rede ECHELON */
	int		Atn7RxBytes;		/* Contador de bytes recebidos */
	int		Atn7RxPkts;			/* Contador de pacotes recebidos */
	int		Atn7RxErrors;		/* Contador de erros de recepcao */
	float	Atn7RxPktsSecAvr;	/* Media de pacotes recebidos por segundo */
	float	Atn7RxPktsSecMax;	/* Maximo de pacotes recebidos por segundo */
	int		Atn7TxBytes;		/* Contador de bytes transmitidos */
	int		Atn7TxPkts;			/* Contador de pacotes transmitidos */
	int		Atn7TxErrors;		/* Contador de erros de recepcao */
	float	Atn7TxPktsSecAvr;	/* Media de pacotes transmitidos por segundo */
	float	Atn7TxPktsSecMax;	/* Maximo de pacotes transmitidos por segundo */
	/* fim estatistica de comunicacao para a rede ECHELON */
    float	IAlvoCubaDia;		/* Corrente alvo da cuba para booster */
	/* -- Alteracao - inicio - 13/09/99 - Leonel - Inclusao de estatistica de erro de conversao -- */
	short unsigned int ErroAD;	/* Erros de conversao de tensao de cuba */
	byte 	ContPrevEa[10];	/* Vetor de cont. de EA por previsao para rel. estat. EA */
/* -- Alteracao - inicio - 08/03/2005 - Carlos - Relat. estatistica EA diario/turno -- */
	byte 	ContIntEa[14];	/* Vetor de cont. de EA por intervalos entre o anterior */
/* -- Alteracao - fim - 08/03/2005 - Carlos - Relat. estatistica EA diario/turno -- */
/* -- Inicio - 14/06/2005 - Carlos - Tensao EA acima de VEaParam -- */
	short  unsigned int EaDurXDia; /* Contador de duracao de tensao EA acima de VEaXLim */
	short  unsigned int EaDurXLim[11]; /* Vetor Cont. Dur VInstEA > VEaXLim para rel. estat. EA */
//	 byte	ResSupAtan[239];	/* -- Reserva Atan + 256 -- */
/* -- Fim - 14/06/2005 - Carlos - Tensao EA acima de VEaParam -- */
    short  unsigned int DurEa[11];	        /* Vetor de duracao de EA para rel. estat. EA detalhado */
	byte 	ContIntEa2[5];	/* Vetor de cont. de EA por intervalos entre o anterior */
	byte	ResSupAtan[188];	/* -- Reserva Atan + 256 -- */
	// byte	ResSupAtan[263];	/* -- Reserva Atan + 256 -- */
  #else
	float	IAlvoCubaDia;		/* Corrente alvo da cuba para booster */
	byte 	ContPrevEa[10];	/* Vetor de cont. de EA por previsao para rel. estat. EA */
/* -- Alteracao - inicio - 08/03/2005 - Carlos - Relat. estatistica EA diario/turno -- */
	byte 	ContIntEa[19];	/* Vetor de cont. de EA por intervalos entre o anterior */
/* -- Alteracao - fim - 08/03/2005 - Carlos - Relat. estatistica EA diario/turno -- */

	byte	ResSupAtan[285];	/* -- Reserva Atan + 256 -- */
//	byte	ResSupAtan[305];	/* -- Reserva Atan + 256 -- */
  #endif
	/*-- Variaveis de supervisao do usuario --*/
	t_sup_avc_usu	Sup;		/* Variaveis de supervisao do usuario */
  } t_avc_supervisao;

typedef		/* Tabela de valores de supervisao diaria das cubas */
  volatile struct super_avc {
	union {
	  t_avc_supervisao  AvcS;
	  char AvcSbuf[AVC_SUP_REC];  /* Espaco reservado para manutencao de cada cuba */
	} AvcSuperv[MAX_CUBAS];
  } t_superv_avc;


/* *************************** Estados AVC ********************************* */
typedef
  volatile struct est_avc /* Variaveis discretas do processo de controle das cubas */
  {
	/* -- Valores que podem ser alterados pela operacao -- */
	byte	ForaLeitura;	/* Leitura da cuba desabilitada */
	byte	EstadoCuba;		/* Estado atual da cuba - Normal, partido, */
							/* ligado ou desligado */
	byte	ChaveAutMan;	/* Indicacao de operacao automatica ou manual */
	byte	ChaveLocRem;	/* Indicacao de operacao local ou remota */
	byte	Corrida;		/* Indica se a cuba esta em corrida */
	byte	Quebrada; 		/* Indica se a cuba esta em quebrada */
	byte	ForaControle;	/* Cuba fora do controle automatico */
	/* -- Valores alterados pelo algoritmo de controle -- */
	byte	DesvioTensao;	/* Indicacao de cuba em desvio de tensao */
	byte	Ea;				/* Efeito Anodico presente */
	byte	EaPrev;			/* Em previsao de Efeito Anodico */
	byte	RuidoLent;		/* Cuba com ruido lento */
	byte	RuidoRap;		/* Cuba com ruido rapido */
	byte	EfeitoMove;		/* Cuba instavel devido a movimentacao recente */
	byte	EfeitoEa; 		/* Cuba instavel devido a Efeito Anodico recente */
	byte	EfeitoQueb; 	/* Cuba instavel devido a quebrada recente */
	byte	EfeitoCorr; 	/* Cuba instavel devido a corrida recente */
	byte	EsperaConfMove;	/* Espera confirmacao de movimentacao automatica */
	byte	DeuAcresBMSup;	/* Deu acrescimo na Banda Morta Sup por atraso de Ea */
	byte	TrataTPinos;	/* Cuba em tratamento por troca de pinos */
	byte	ManualControle;	/* Cuba colocada em estado manual pelo controle */
	byte	TabOpeAtiva;	/* Ativa tabela de incrementos de operacao */
	byte	InibeMovEaPrev;	/* Inibe movimentacao qdo. derivada ultrapassar
							   patamar predefinido dentro de um intervalo dado */
	byte	InibeControleUsu;	/* Para inibir movimentacao por modulos de controle
							   do usuario */
	byte	EaPrevVirada;	/* Mantem sinal de previsao na virada de dia/turno */
	byte	TrataIncUsuario; /* Indica que esta com incremento de usuario (programa) */
	byte	EliminaEa;		/* Tabela de eliminacao Ea ativa */
	byte	Livre1;			/* livre, reserva */
	byte	InibeControleAlim;	/* Para inibir movimentacao pelo algoritmo
							   de alimentacao */
	byte	RtuStatus;		/* Status da remota. 0=on_line na rede, 1=off_line (fora rede) */
	byte	EvCubaMax;		/* sinaliza um numero grande de eventos em um periodo */
    byte	ElimEaAtivo;    /* Tabela de eliminacao de EA ativa */
    byte	ProvAgarraAnodo;  /* Provavel agarramento de anodo */
  /* -- alteracao - inicio - 21/10/02 - Leonel - Inclusao evento temperatura Atn8 -- */
	byte	Atn8TempAlta;	/* Temperatura da atn8 maior que maximo configurado */
	byte	EmCalibracao;	/* Cuba em modo de calibracao */
	byte	AtivaTabEaAltern; /* ativa tabela de ea alternativa */
	byte	TipoTabEaAltern; /* 0 -> Tempo, 1 -> Ea */
	byte	TrataCruzeiro;	/* Cuba em tratamento de manobra de cruzeiro */
	byte	EsperaConfSopro;	/* aguarda confirmacao de sopro automatico */
	byte	FalhaSoproAut;	/* indica falha confirmacao de sopro automatico */
	byte	FalhaIOAtn;		/* indica falha leitura de I/O da Atn8 */
	byte	CorrCubaEmerg;	/* indica que corrente de cuba esta usando Iinst da linha */
	byte	ResAtan[59];	/* reserva de uso da Atan */
//	byte	ResAtan[60];	/* reserva de uso da Atan */
  /* -- alteracao - fim - 21/10/02 - Leonel - Inclusao evento temperatura Atn8 -- */

    /* -- Valores digitais do usuario -- */
	t_est_usu	Est;		/* Variaveis digitais do usuario */
  } t_est_avc;

typedef		/* Tabela de estados discretos associados as cubas */
  volatile struct {
	union {
	  t_est_avc  EstAvc;
	  char EstAvcbuf[AVC_EST_REC];  /* Espaco reservado para manutencao de cada cuba */
	} AvcEst[MAX_CUBAS];
  } t_estado_avc;


/* -- Alteracao - inicio - 08/03/2005 - Carlos - Relat. integracao diario/turno -- */
/* -- Tipo de dados para a estrutura de dados de integracao -- */
typedef
  struct Integr
  {
	byte	HoraRef;
	float	IIntg1h;
	float	VIntg1h;
	float	VPlaca1h;
	float	VAlvo1h;
	float	VLiqui1h;
	float	VTotal1h;
	float	VInc1h;
	int		EaQtd1h;
	float   EaVMed1h;
	float   EaVMax1h;
	float   EaDur1h;
	int		NPrevEa1h;
  } t_integ_1h;
/* -- Alteracao - fim - 08/03/2005 - Carlos - Relat. integracao diario/turno -- */

/* ********************* AVL - Arquivo de variaveis da linha *************** */
typedef
  volatile struct avl { /* -- variaveis do controle de linha -- */
	/* -- Parametros da linha -- */
	int		NumCubas;		/* -- numero de cubas deste projeto -- */
	float	ILinhaAlta;		/* -- limite para indicar corrente da linha alta -- */
	float	ILinhaMin;		/* -- Corrente minima linha p/ considerar linha ativa -- */
	float	INominal;		/* -- Corrente nominal da linha -- */
	float	IdesvMax;		/* -- Corrente para inibicao de ruido -- */
	float	IRapMax;		/* -- Corrente de ruido rapido maxima -- */
	int		SadMaxErr;		/* -- Numero maximo de erros consecutivos na -- */
							/* -- conversao -- */
	int		NCanaisNMux;	/* -- Numero de canais nao multiplexados ativos -- */
	float	LsbTensao;		/* -- Fator de conversao dos valores de tensao -- */
							/* -- lidos p/ Unidade de engenharia (V) -- */
	float	LsbNaoMux[8];	/* -- Fator de conversao dos valores nao -- */
							/* -- multiplexados lidos p/ Unidade de engenharia -- */
  /* -- alteracao - inicio - 13/09/00 - Robson - Inclusao tratamento Atn8 -- */
	short int	IIndex[8];	/* index para qual remota ler corrente (indice para cuba ou cuba+outrasrem) */
	byte		ICanal[8];	/* canal na remota index de onde ler corrente (0 a 3) */
	short int	VLinhaIndex; /* index para qual remota ler tensao de linha (indice para cuba ou cuba+outrasrem) */
	byte		VLinhaCanal; /* canal na remota index de onde ler corrente (0 a 3) */
	byte	LivrePar[69];	/* -- Area livre liberada apos preenchimento da b.d. -- */
	//float	LivrePar[24];	/* -- Area livre liberada apos preenchimento da b.d. -- */
  /* -- alteracao - fim - 13/09/00 - Robson - Inclusao tratamento Atn8 -- */
	float	VMuxMax;		/* -- Valor maximo de tensao nas entradas multiplexadas -- */

	int		OffInicNCubaOp;	/* -- Offset inicial para a numeracao das cubas -- */
							/* -- (numeracao de operacao. Ex. 100 -> 1a. cuba=101 -- */
	int		CanalIPrinc;	/* -- canal do SAD onde esta a corrente principal -- */
	int		CanalISec;		/* -- canal do SAD onde esta a corrente secundaria -- */
	int		CanalVLinha;	/* -- canal do SAD onde esta a tensao de linha -- */
	float	IDifMax;		/* -- Diferenca maxima entre as correntes -- */
							/* -- principal e reserva -- */
	int		ImpSimulNodoOp[MAX_OPREDE]; /* -- Quando 1 indica impressao simultanea de eventos -- */
	int		DurMovBMin;		/* Duracao movimento para baixo minima (segs) para elimina ea */
	int		DurMovBMax;		/* Duracao movimento para baixo maxima (segs) para elimina ea */
	int		DurMovCMin;		/* Duracao movimento para cima minima (segs) para elimina ea */
	int		DurMovCMax;		/* Duracao movimento para cima maxima (segs) para elimina ea */
	float	ILinhaBaixa;	/* -- limite para indicar corrente da linha baixa -- */
	int		ImpSimulNodoPri; /* -- Quando 1 indica impressao simultanea de eventos -- */
	int		NumTurnos;		/* -- Numero de turnos configurado para relatorios -- */
	int		HoraIniTurno[MAX_TURNOS]; /* -- Hora de inicio de cada turno definido -- */
	int		HoraFechaDia;	/* -- Hora para fechamento de dia (arq. hist de dia) -- */
	int		CicloAjCorrida;	/* -- Num. de ciclos de leitura que compoe o ciclo
								  de ajuste de ACD durante corrida -- */
	int		TAtivaLinha;	/* -- Tempo a esperar na partida para ativar linha (min) -- */
	int		HabLogOper;		/* Flag de habilitacao do log de operacao */
	char	IdentTurno[MAX_TURNOS][MAX_ID_TURNO];	/* Identificacao de 2 letras para cada turno (ihm) */
	int		TDesabLinha;	/* Interv. apos linha desab. para colocar em Manual-Controle em (min)  */
	/* -- Relacoes grandeza/V para os sinais NAO multiplexados e as entradas especiais -- */
	float	RelNaoMux[8];	/* Relacao Grandeza/Volt para os 4 primeiros sinais nao multiplexados */
	float	RelEntEsp[NUM_LEITURAS_ESP]; /* Relacao Grandeza/Volt para as entradas especiais */
	float	OffSetCorrente;	/* Offset (KA) a retirar do sinal de corrente (4 a 20ma) */
	short int LimSupMovElim;	/* Limite de mov. superior para elimina ea [seg] */
	short int LimInfMovElim;	/* Limite de mov. inferior para elimina ea [seg] */
	float	Atn8TempLimInf;		/* Limite inferior de temperatura da atn8 */
	float	Atn8TempLimSup;		/* Limite superior de temperatura da atn8 */
	short int TmpMaxSinalCorr;	/* Tempo maximo sinalizacao corrida operacao */
	short int TmpMaxSinalQueb;	/* Tempo maximo sinalizacao corrida quebrada */
	short int TmpMaxSinalTrPi;	/* Tempo maximo sinalizacao corrida troca pinos */
	float	ErroMaxReserva;		/* Erro maximo admissivel na comparacao com os valores da Atn1.4
								   lidos no micro de reserva. Usado pelo modulo IhmHotStBy para
								   interfaces Atn1.4 duplas */
	short int TmpMaxSinalCruz;	/* Tempo maximo sinalizacao manobra de cruzeiro */
	float	IDifMaxLinhaCuba;	/* Diferenca maxima (kA) entre corrente de linha e de cuba para caracterizar
									problema na corrente de cuba e usar a de linha como emergencia */
	
	byte	ResParAvlAtan[264];	/* -- expansao + 256 Reserva Atan -- */

	/* Area reservada para PARAMETROS do usuario que podem ser gravados pelo
	   programa de configuracao de linha */
    /* Parametros de linha do usuario */
    t_par_avl_usu	Par;

	/* -- Outras informacoes -- */
	/* Inicio da area de trabalho do sistema. */
	/* Esta variavel (HoraPartida) deve ser a primeira da area de trabalho */
	long	HoraPartida;		/* -- Hora da partido do sistema -- */
	long	HoraAtivaLinha;		/* -- Hora em que a linha foi ativada -- */
	long	HoraDesativaLinha;	/* -- Hora em que a linha foi desativada -- */
	long	HoraUltControle;	/* -- Hora do ultimo controle -- */
	long	HoraAtualControle;	/* -- Hora corrente do controle -- */
	int		LinhaHabilitada;	/* -- Indica se a linha esta habilitada p/ controle -- */
	int		NodoNoControle;		/* -- Numero do nodo no controle -- */

	/* -- Valores de ciclo de leitura -- */
	float	Iinst;				/* -- Corrente instantanea -- */
	float	IinstRes;			/* -- Corrente instantanea reserva -- */
	float	IinstDif;			/* -- Iinst-IinstRes -- */
	float	VetIinstMed[6];		/* -- Corrente media instantanea para calculos do filtro -- */
	float	IrapInst[6];		/* -- Corrente de ruido rapido instantanea -- */
	float	VLinhaInst;			/* -- Tensao instantanea da linha -- */
	float	PotLinhaInst;		/* -- Potencia instantanea da linha -- */

	/* -- Valores de ciclo de controle -- */
	float	ICicContlMed;		/* -- Corrente media do ciclo de controle -- */
	float	ICicContlMedRes;	/* -- Corrente media do ciclo de controle reserva -- */
	float	IRapCicContl;		/* -- Componente de ruido rapido da corr. da linha -- */
	float	IAlvo;				/* -- Corrente Alvo da linha -- */
	float	VLinhaCicCont;		/* -- Tensao media do ciclo controle da linha -- */
	int		TurnoAtual;			/* -- Turno atual -- */

	/* -- Contadores Gerais -- */
	long	ContLGeral;   		/* -- Contador Geral de Leituras -- */
	int		ContCubaFora;   	/* -- Contador do numero de Cubas Fora de
									  leitura -- */

	/* -- Variaveis de integracao -- */
	float	IInteg1h;			/* -- Corrente integrada de 1h -- */
	float	VInteg1h;			/* -- Tensao integrada de 1h -- */
	byte	ReservaAtivo;		/* -- Indica que o nodo reserva esta ativo qdo = 1 -- */
	byte	LinhaAtiva;			/* -- E' ligado apos Sistema ou linha ativo por tempo
									  maior que TAtivaLinha -- */
	byte	MudancaDia;			/* -- Indica se VAI_MUDAR no ciclo corrente,
								 se MUDOU ou se esta SEM_MUDANCA prevista no ciclo corrente */
	byte	MudancaTurno;		/* -- Indica se VAI_MUDAR no ciclo corrente,
								 se MUDOU ou se esta SEM_MUDANCA prevista no ciclo corrente */

	/* -- Valores instantaneos de leituras especiais do Atn 1.4 (tensao de
		sala, secao etc -- */
	float	ValorEntEsp[NUM_LEITURAS_ESP];	/* Valor instantaneo das entradas (0=tensao de sala) */
	byte	StatusEntEsp[NUM_LEITURAS_ESP];	/* status do conversor das entradas */

	float	ValorNMux[NUM_VAR_NMUX]; /* Valor instantaneo das entradas nao multiplexadas */
	byte	StatusNMux[NUM_VAR_NMUX]; /* Status dos conversores das entradas nao multiplexadas */
	byte	CorrenteBaixa;		/* Verdadeiro quando corrente baixa */
	byte	CorrenteAlta;		/* Verdadeiro quando corrente alta */
	float	IIntegRes1h;		/* -- Corrente integrada reserva de 1h -- */

    /* Alteracao - Inicio - Leonel - 14/05/99 - Calculo de media horaria */
	byte	EmAjusteHora;		/* Verdadeiro indica ajuste de hora em andamento */
	byte	EmAjusteHora1h;		/* Verdadeiro indica que houve ajuste de hora na ultima hora */
	short int ContL1h;			/* contador leituras em 1 hora */
	float	IIntegMed1h;		/* Corrente media em uma hora */
	float	IIntegResMed1h;		/* Corrente reserva media em uma hora */
	float	VIntegMed1h;		/* tensao da linha media em uma hora */
    /* Alteracao - Fim - Leonel - 14/05/99 - Calculo de media horaria */

//	byte	ResGerAvlAtan[158];	/* -- Reserva Atan -- */
/* -- Alteracao - inicio - 10/06/2002 - Leonel - Correcao tratamento de mais de um canal (pcltas) -- */
	short int	RxPktsSecLinha;	/* Para contagem de num. pacotes rec. segundo pelas 2 pcltas */
	short int	TxPktsSecLinha;	/* Para contagem de num. pacotes tx. segundo pelas 2 pcltas */
/* -- Alteracao - inicio - 06/02/2003 - Leonel - Medias outras correntes das atnCAs -- */
	double	ValorNMuxMed[NUM_VAR_NMUX];	 /* Valores medios de corrente (atncas) para comparacao com principal */
/* -- Alteracao - fim - 06/02/2003 - Leonel - Medias outras correntes das atnCAs -- */
/* -- Alteracao - inicio - 08/03/2005 - Carlos - Relat. integracao diario/turno -- */
//	byte	ResGerAvlAtan[346];	/* -- expansao + 256 Reserva Atan -- */
	byte	IndHora;			/* -- indice do vetor  Integ1h -- */
    t_integ_1h Intg1h;			/* Dados de integracao de 1 hora */
	byte	ResGerAvlAtan[296];	/* -- expansao + 256 Reserva Atan -- */
/* -- Alteracao - fim - 08/03/2005 - Carlos - Relat. integracao diario/turno -- */
//	byte	ResGerAvlAtan[410];	/* -- expansao + 256 Reserva Atan -- */
/* -- Alteracao - fim - 10/06/2002 - Leonel - Correcao tratamento de mais de um canal (pcltas) -- */
	
	/* -- Variaveis de trabalho de linha de usuario -- */
	t_trab_avl_usu	Trab;

	/* -- Valores diarios -- */
	/* -- Obs: Os valores abaixo de IMedDia inclusive sao inicializados pela
		  funcao fontes/lib/CriaGlobal.c (CriaAreaGlobal) na partida -- */
	float	IMedDia;			/* -- Corrente media principal da linha no dia -- */
	float	IMedDiaRes;			/* -- Corrente media reserva da linha no dia -- */
	float	IAlvoDia;			/* -- Corrente Alvo media da linha no dia -- */
	float	VLinhaDia;			/* -- Tensao media diaria da linha -- */
  	int		NCicContDia;		/* Numero de ciclos de controle p/ superv. no dia */
  	int		NCicAtivoDia;		/* Numero de ciclos de controle que o sistema
								   esteve ativo no dia */
	float	PotLinhaDia;		/* -- Potencia media diaria da linha -- */
	float	CubasNormDia;		/* -- Numero medio de cubas em estado normal no dia -- */
	float	CubasLigParDia;		/* -- Numero medio de cubas em estado Ligado ou Partido no dia -- */
	float	RCubasDiaBruta;		/* -- Resistencia total bruta media de todas
									  as cubas menos as desligadas no dia -- */
  #ifdef	USA_REDE_ECHELON
	/* Estatistica de comunicacao para a rede ECHELON */
	int		Atn7AvrCounter;		/* Contador para valores medios */
	int		Atn7RxBytes;		/* Contador de bytes recebidos */
	int		Atn7RxPkts;			/* Contador de pacotes recebidos */
	int		Atn7RxErrors;		/* Contador de erros de recepcao */
	float	Atn7RxPktsSecAvr;	/* Media de pacotes recebidos por segundo */
	float	Atn7RxPktsSecMax;	/* Maximo de pacotes recebidos por segundo */
	int		Atn7TxBytes;		/* Contador de bytes transmitidos */
	int		Atn7TxPkts;			/* Contador de pacotes transmitidos */
	int		Atn7TxErrors;		/* Contador de erros de recepcao */
	float	Atn7TxPktsSecAvr;	/* Media de pacotes transmitidos por segundo */
	float	Atn7TxPktsSecMax;	/* Maximo de pacotes transmitidos por segundo */
	/* fim estatistica de comunicacao para a rede ECHELON */
	/* -- Alteracao - inicio - 13/09/99 - Leonel - Inclusao de estatistica de erro de conversao -- */
	short unsigned int ErroADNMux[8];	/* Numero de erros em conversores nao multiplexados */
	short unsigned int ErroADEntEsp[NUM_LEITURAS_ESP];	/* Numero de erros em conversores de entradas especiais */
	/* -- Alteracao - fim - 13/09/99 - Leonel -- */
/* -- Alteracao - inicio - 08/03/2005 - Carlos - Relat. integracao diario/turno -- */
	t_integ_1h Integ1h[24];		/* -- 49 bytes x 24 = 1176 bytes --*/
	byte	HoraInicDT;			/* -- hora inicio dia/turno para ref. vetor integracao --*/
	byte	ResSupAvlAtan[483];/* -- expansao + 280 Reserva Atan -- */
/* -- Alteracao - fim - 08/03/2005 - Carlos - Relat. integracao diario/turno -- */
  #else
	/* -- Alteracao - inicio - 13/09/99 - Leonel - Inclusao de estatistica de erro de conversao -- */
	short unsigned int ErroADNMux[8];	/* Numero de erros em conversores nao multiplexados */
	short unsigned int ErroADEntEsp[NUM_LEITURAS_ESP];	/* Numero de erros em conversores de entradas especiais */
	t_integ_1h Integ1h[24];			/* -- 49 bytes x 24 = 1176 bytes --*/
	byte	HoraInicDT;			/* -- hora inicio dia/turno para ref. vetor integracao --*/
/* -- Alteracao - fim - 08/03/2005 - Carlos - Relat. integracao diario/turno -- */
	byte	ResSupAvlAtan[527];		/* -- expansao + 1280 Reserva Atan -- */
	/* -- Alteracao - fim - 13/09/99 - Leonel -- */
  #endif

	/* -- Variaveis de supervisao do usuario -- */
	t_sup_avl_usu	Sup;		/* Variaveis de supervisao do usuario */
  } t_avl;


typedef		/* -- Tabela de valores da linha -- */
  volatile struct uavl {
	union {
	  t_avl Avl;
	  char AvlBuf[AVL_REC];
	} Uavl;
  } t_uavl;

/* -- Tipo de dados para o arquivo historico (AVL+SUPERVISAO_AVC) -- */
typedef
  struct Hist
  {
	t_uavl			AvlHist;
	t_superv_avc	AvcHist;
  } t_hist;


/* ****************************** Comum ************************************ */
typedef
  volatile struct comum_principal
  { /* area de dados global principal */
	/* -- Valores absolutos -- */
	/* -- Reservados para uso do Score (256 bytes) -- */
	char	ResUsoScore[168];
	int		IdentReducao;	/* -- Numero da reducao -- */
	char	ResUsoScore2[84];

	/* -- Reservados para uso do Score -- */
	pid_t	ProxyMcp;		/* -- Proxy para sinalizacao do mcp -- */
	int		BaseTempoMcp;	/* -- base de tempo para o ciclo de leitura em --*/
							/* -- unidades de 0,5 seg -- */
	int		BaseTempoMcc;	/* -- base de tempo para o ciclo de controle -- */
							/* -- em numero de ciclos de leitura -- */
	int		EstaControlando;/* -- Indica se este nodo esta no controle qdo = 1 -- */
	short int	DrvAnaPartiu; /* -- Indica que driver de analogicas (para atn8) partiu
								usado para sincronizar leituras pelo RedeAtn8 -- */
	short int	Res2;
	int		AlterouTab[MAX_TABELAS_ATUALIZACAO]; /* -- Quando = 1 indica que a
								tabela correspondente foi alterada! DEVE SER LI-
								GADO QDO. HOUVER ALTERACAO EM UMA DAS TABELAS,
								PARA PERMITIR A ATUALIZACAO DO HOTSTANDBY -- */
	/* -- Tabela de outras remotas que nao as de cuba -- */
	t_outras_rem	OutrasRem[NUM_OUTRAS_REMOTAS];
	int		Res3;
	int		BaseTempoRemota;	/* -- 1/Base de tempo da remota. Ex. 1/50ms->20 -- */
	int		NumSubredes;		/* -- numero de subredes da Echelon do projeto (por canal) -- */
    /* -- alteracao - inicio - 12/09/00 - Robson - Tratamento da Atn8.0 -- */
	byte	ScanAna;		/* -- frequencia de leitura das analogicas nas
								remotas Atn8.0. Em ticks de 50ms. Ex. 10 -> 0,5 seg -- */
/* -- Alteracao - inicio - 02/04/2002 - Leonel - Inclusao tratamento de mais de um canal (pcltas) -- */
	byte	NumCanaisSubrede;	/* Numero de canais de subrede (num. de placas pclta de um canal - CBA) */
	byte	ResAbs1[3];
/* -- Alteracao - fim - 02/04/2002 - Leonel - Inclusao tratamento de mais de um canal (pcltas) -- */

    /* -- alteracao - inicio - 03/01/01 - Bandeira - Inclusao tratamento teclado de touch no IHM */
	int		WidAtual;			/* window id da ultima window que usou o teclado */
    /* -- alteracao - fim - 03/01/01 - Bandeira - Inclusao tratamento teclado de touch no IHM */
	
    /* -- alteracao - inicio - 29/11/01 - Bandeira - */
	byte	NumGruposCuba;		/* -- Numero de grupos de cubas existentes na reducao */
	byte	NumCubasGrupo[MAX_GRUPOS_CUBAS]; /* -- numero de cubas por grupo na reducao */
    /* -- alteracao - fim - 29/11/01 - Bandeira - */
	
	/* -- alteracao - inicio - 10/07/02 - Bandeira - */
	struct	{
	  char		PhindowsName[11];	/* -- nome login p/ estacoes phindows -- */	
	  short int	Operador;			/* indice do operador p/ login global ou -1 se nao */
	  short int	NivelOper;			/* nivel do operador p/ login global ou -1 se nao */
	  byte		NodoImpOp;			/* nodo da impressora a ser utilizada */
	  byte		TamIHM;				/* -- tamanho do ihm 0 = 640x480 e 1 = 1024x768 -- */
	}IHM[MAX_LOGIN_PHINDOWS+1];
    /* -- alteracao - fim - 10/07/02 - Bandeira - */
	
	/* -- alteracao - inicio - 26/08/02 - Bandeira - */
	struct	{
	  char		RadioName[11];		/* -- nome estacoes de radio -- */	
	}IHM2[MAX_LOGIN_RADIO];
    /* -- alteracao - fim - 26/08/02 - Bandeira - */
	
	byte	ResAbs[1855];		/* -- reserva para absolutos -- */

	/* -- Offset para as tabelas deste segmento -- */
	/* -- Obs: Estes offsets nao devem ter sua ordem alterada! -- */
	unsigned	OfDescConv;	/* -- Tabela descritora de conversores do SAD -- */
	unsigned	OfLog;		/* -- Tabela de logs -- */
	unsigned	OfDescProg;	/* -- Tabela de descricao dos programas -- */
	unsigned	OfTabsEa;	/* -- Tabelas de eliminacao de Efeito Anodico -- */
	unsigned	OfSenhas;	/* -- Tabela de Senhas de Operacao -- */
	unsigned	OfDescEv;	/* -- Tabela descritora de eventos -- */
	unsigned	OfAvl;		/* -- Tabela de valores da linha -- */
	unsigned	OfEstAvc;	/* -- Tabela de valores digitais associados as
									   cubas -- */
	unsigned	OfSupAvc;	/* -- Tabela de valores de supervisao para as cubas -- */
	unsigned	OfHistTur;	/* -- Tabela de valores de supervisao de turno -- */
	unsigned	OfTabOpe;	/* -- Tabela de incrementos de operacao -- */
	unsigned	OfResTabs[18]; /* -- Reserva para novas tabelas -- */
  } t_comum;

#endif		/* #ifndef		__PROLOGO_SCORE__ */

/* -- Fim do arquivo Score.h -- */
