/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO  : TODOS

	SISTEMA  : GERAL

	ARQUIVO  : ScoreConst.h

	CONTEUDO : Contem as definicoes de todas as constantes especificas do
			   Sistema de Controle de Reducoes.

	AUTOR	: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO   : 2.0		  -	  DATA  : 28/04/94

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
Data     | Descricao											| Autor
-------------------------------------------------------------------------------
28/04/94 | Edicao inicial de migracao para o QNX 4.2			| Leonel
-------------------------------------------------------------------------------
28/09/94 | Definicoes de tabelas para acesso via rede			| Leonel
-------------------------------------------------------------------------------
21/03/95 | Alteracao numero de tabelas para o hotstandby		| Leonel
-------------------------------------------------------------------------------
28/03/95 | Criados defines para tabelas de inc. de operacao		| Leonel
-------------------------------------------------------------------------------
06/04/95 | Transferidos defines de dezena grupo do Relatorios.h | Carlos
-------------------------------------------------------------------------------
21/08/95 | Acrescentado define para compilacao do novo alg. prev| Leonel
-------------------------------------------------------------------------------
23/11/95 | Alterados defines para o prototipo da albras         | Leonel
-------------------------------------------------------------------------------
23/01/96 | Inclusao de ifdef para alcan/aratu                   | Bandeira
-------------------------------------------------------------------------------
20/11/96 | Inclusao de defines para ajuste de camisa            | Carlos
-------------------------------------------------------------------------------
20/11/97 | Alteracao de MAX_CUBAS 144=>160, MAX_EVS 100=>200 e  | Carlos
         | MAX_OPERADORES 30=>90                                |
-------------------------------------------------------------------------------
18/06/98 | Alteracao de MAX_CUBAS 160=>180                      | Carlos
-------------------------------------------------------------------------------
25/01/01 | Inclusao de define para a ATN8 CA da sala 86ka       | Leonel
-------------------------------------------------------------------------------
13/03/01 | Alteracao para copiar param conversores p/ sala 86ka | Leonel
-------------------------------------------------------------------------------
07/01/02 | Aumento da base de dados CBA 125ka                   | Bandeira
-------------------------------------------------------------------------------
06/02/03 | Definicao do numero de correntes de AtnCa tratadas   | Leonel
         | no AVL.                                              |
-------------------------------------------------------------------------------
14/11/14 | Expansao 25% base dados para Score8 CBA - Sala II    | Carlos
-------------------------------------------------------------------------------
*****************************************************************************/
/*********************************** Revisoes ********************************\
$Id: ScoreConst.h.user,v 1.1.1.1.10.2 2015/08/26 18:54:19 clage Exp $

$Log: ScoreConst.h.user,v $
Revision 1.1.1.1.10.2  2015/08/26 18:54:19  clage
Preparacao do kit des atual

Revision 1.11.2.1  2015/06/30 22:44:55  clage
Alteracoes para sala II com ATN8 e expansao da base de dados.

Revision 1.11  2008/11/27 21:26:38  marcelo
Inclusao de variaveis para novo tratamento de ruido lento da mesma forma
que o ruido rapido.

Revision 1.10  2008/08/04 20:57:10  alex
mudado de 35 para 65 dias eventos/historico

Revision 1.9  2008/07/08 13:26:52  leo
Incluidos novos limites para tratamento de ruidos.

Revision 1.8  2008/07/01 20:37:44  leo
Incluida definicao para acao GOTO PASSO da tabela de elimicao de EA.

Revision 1.7  2008/07/01 13:28:09  leo
Inclusao de novos parametros para novas acoes Tabela de EA (TEaLimiteVMaior,
TEaLimiteVMenor e TEaMaxSopros).

Revision 1.6  2007/03/19 14:52:14  leo
Criacao de semaforo de leitura da tabela ccont_mcp e correcoes de
formato no DescrArqVar em pre-operacao (sala VII cba)

Revision 1.5  2004/08/06 21:08:22  clage
Incluida expansao de 1280 bytes para area de supervisao do AVL

Revision 1.4  2003/09/30 19:29:40  leo
Criacao de funcoes separadas de ShmMap e ShmSize.
Inclusao de funcao para mapear segmento dummy read_only.

Revision 1.3  2003/09/29 13:17:47  alex
novo log p/ 320 logs

Revision 1.2  2003/03/07 20:39:29  leo
Aumento da estrutura IHM no comum para aumentar logins phindows de 20 para 30.

\*********************************** Revisoes ********************************/

#ifndef		_SCORECONST_H

#define		_SCORECONST_H

/* -- Compilacao condicional -- */
/* -- Qdo. definido utiliza algoritmo de previsao baseado na derivada histo-
      rica conjugada com um intervalo de tempo. Tambem utiliza filtro digital
      para gerar a resistencia bruta de ciclo de controle -- */
#define		NOVO_ALGORITMO_PREVISAO_EA		1

/* **** Compilacao condicional para alteracoes relativas a rede ECHELON
		(remota ATN 7.0) ******* */
#ifndef		USA_REDE_ECHELON
  #define		USA_REDE_ECHELON		1
#endif

/* -- Definicao de algoritmos para cada cuba, NumAlgCtr, 1 bit por algoritmo -- */
/* -- Reservado para a Atan -> algoritmos de 1 a 8 -- */
#define		ALG_SCORE01			0x0001 /* alg. de controle padrao do Score */
#define		ALG_SCORE02			0x0002 /* alg. de alimentacao do Score */
#define		ALG_SCORE03			0x0004
#define		ALG_SCORE04			0x0008
#define		ALG_SCORE05			0x0010
#define		ALG_SCORE06			0x0020
#define		ALG_SCORE07			0x0040
#define		ALG_SCORE08			0x0080
/* -- Reservado para o usuario -> algoritmos de 9 a 16 -- */
#define		ALG_USER01			0x0100
#define		ALG_USER02			0x0200
#define		ALG_USER03			0x0400
#define		ALG_USER04			0x0800
#define		ALG_USER05			0x1000
#define		ALG_USER06			0x2000
#define		ALG_USER07			0x4000
#define		ALG_USER08			0x8000
/* -- Todos os algoritmos -- */
#define		ALG_TODOS			0xFFFF
/* -- Nenhum algoritmo definido -- */
#define		ALG_NENHUM			0

/* -- tamanhos de registros -- */
#define AVC_REC			4224	/* Tamanho de um registro de cuba			*/
								/* 3712 + 2 x 128 (ParUser) + 4 x 64 (AvcUser) = 4224   - Expansao 13/11/14 - Red 2 CBA */
#define	AVC_SUP_REC		1760	/* Tamanho de um registro da tabela de sup. */
								/* 656 + 880 + 224 = 1536 + 224 = 1760  - Expansao 13/11/14 - Red 2 CBA  */
#define AVC_EST_REC		220		/* Tamanho de um registro de status de cuba */
								/* 192 + 28 = 220   - Expansao 13/11/14 - Red 2 CBA */

#define AVL_REC			5584	/* Tamanho de um registro de linha			*/
								/* 5120 + 112 + 220 + 132 = 5584   - Expansao 13/11/14 - Red 2 CBA */

/* -- tamanhos maximos para registro de parametros e trabalho de usuario p/ AVC */
#define	TAM_PAR_USER_AVC		640	   // 512 + 128 = 640   - Expansao 13/11/14 - Red 2 CBA
#define	TAM_REG_USER_AVC		320    // 256 + 64  = 320   - Expansao 13/11/14 - Red 2 CBA
#define	TAM_REG_USER_SUP		1104   // 880 + 224 = 1104  - Expansao 13/11/14 - Red 2 CBA
#define	TAM_REG_USER_EST		120    //  92 + 28  = 120   - Expansao 13/11/14 - Red 2 CBA
#define	TAM_REG_USER_AVL_PAR	560    // 448 + 112 = 560   - Expansao 13/11/14 - Red 2 CBA
#define	TAM_REG_USER_AVL_TRAB	1120   // 900 + 220 = 1120  - Expansao 13/11/14 - Red 2 CBA
#define	TAM_REG_USER_AVL_SUP	672    // 540 + 132 = 672   - Expansao 13/11/14 - Red 2 CBA

/* -- Alguns limites maximos -- */
#define MAX_EVS			200		/* Numero maximo de tipos de eventos		*/

#define N_PAR_EV		5 		/* Numero maximo de parametros por evento	*/

#define	NIVEL_SENHA_MAX	255		/* Nivel mais alto de senha                 */

#define MAX_VAR_LOG		6		/* Numero maximo de variaveis por log		*/

#define MAX_LOGS_ATIVOS		MAX_CUBAS	/*20*/      /* Numero maximo de log's ativos 			*/

  #define MAX_ERR_LEITURA	3		/* Num. max. erros na leitura de dados 		*/

#define	MAX_PASSOS_ELIM_EA	20	/* Numero de passos da tabela de elimina Ea */
#define	NUM_TABS_EA		10		/* Numero de tabelas de eliminacao de EA    */

/* -- Alteracao - inicio - 06/02/2003 - Leonel - Medias outras correntes das atnCAs -- */
#define		NUM_VAR_NMUX	8	/* Numero de valores de correntes AtnCa (atn8) tratadas no AVL */
/* -- Alteracao - fim - 06/02/2003 - Leonel - Medias outras correntes das atnCAs -- */

/* -- Indicacao de mudanca de dia ou turno -- */
#define	SEM_MUDANCA_D_T	0		/* Nao vai mudar (dia ou turno) no ciclo de
								   controle corrente */
#define	VAI_MUDAR_D_T	1		/* Vai mudar (dia ou turno) no ciclo de controle
								   corrente */
#define	MUDOU_D_T		2		/* Mudou (dia ou turno) no ultimo ciclo de
								   controle */

  #define	MAX_PASSOS_AJ_CAMISA	20	/* Numero de passos da tabela de ajuste de camisa */
  #define	NUM_TABS_CAMISA		10		/* Numero de tabelas de ajuste de camisa    */

#define	N_AMOSTRAS_RRAP	 8		/* 8 Amostras resistência rápida acum. a cada 6 Hs -> 48 horas */
#define N_AMOSTRAS_RLENT 8      /* 8 Amostras resistência lenta acum. a cada 6 Hs -> 48 horas */ 

#define	MAX_GRUPOS_CUBAS	16	/* Num. max. de grupos de cubas */

	#define MAX_CUBAS	320	/*180*/		/* Num. max. de cubas desse projeto			*/

#define MAX_AVC			(MAX_CUBAS*AVC_REC)	/* Tam. max. do avc				*/
#define NSEG_CUBAS		8		/* Num. max. de segmentos de cubas          */

#define	NUM_OUTRAS_REMOTAS	30	/* Num. de remotas alem das de cuba			*/

/* -- alteracao - inicio - 11/09/00 - Robson - Inclusao mensagem Atn8 -- */
/* Numero maximo de valores analogicos lidos de uma atn8 */
#define		MAX_VALORES_POR_ATN8	4

#define		MAX_ATN8		(MAX_CUBAS+NUM_OUTRAS_REMOTAS)	/* Numero maximo de remotas Atn8 */
/* -- alteracao - fim - 11/09/00 - Robson - Inclusao mensagem Atn8 -- */

/* -- tipos de outras remotas -- */
#define		REMOTA_SELF_HEALING_MASTER		1
#define		REMOTA_SELF_HEALING_SLAVE		2
  #define	REMOTA_REGULACAO				3
/* -- Alteracao - Inicio - 25/01/2001 - Leonel - Tratamento sala 86Ka -- */
  #define	REMOTA_ATN8CA					4
/* -- Alteracao - Fim - 25/01/2001 - Leonel - Tratamento sala 86Ka -- */

#define	MAX_OPERADORES	90		/* Num. max. de operadores cadastrados		*/

#define MAX_PROGS_SCORE	50		/* Num. max. programas cadastrados no Score */

#define	MAX_OPREDE		20		/* Num. max. de nodos p/ operacao via rede  */

#define	TAM_NOME_DISP	20		/* Tamanho max. para nome de dispositivo	*/
#define	TAM_REG_HIST	8192    /* Tamanho do regitro p/ leit. e esc. em disco*/
#define	MAX_DIAS_HIST		65	/* Num. max. de dias armazenados p/ historico */
#define	MAX_DIAS_EVENTOS	65	/* Num. max. de dias armazenados p/ eventos */
//******* #define	MAX_DIAS_HIST		35	/* Num. max. de dias armazenados p/ historico */
//******* #define	MAX_DIAS_EVENTOS	35	/* Num. max. de dias armazenados p/ eventos */
#define	NUM_SEGUNDOS_DIA 86400L /* Num. de segundos em um dia */

/* -- Limites para tabelas de incremento de operacao -- */
#define	MAX_PASSOS_TAB_OPE	20	/* Num. max. de passos por tabela */
#define	MAX_TAB_INC_OPE		10	/* Num. max. de tabelas de incremento de operacao */

/* -- Numero de leituras especiais do SAD disponiveis para entradas multiplexadas -- */
/* -- E numero de remotas ATN 8.0 que nao sao de cubas -- */
#define	NUM_LEITURAS_ESP		16

/* -- Base de tempo do Sad -- */
#define		SAD_TICKS			2	/* -- 1/2 segs -- */

/* -- Status das remotas -- */
#define		RTU_ON_LINE			0	/* remota on line na rede */
#define		RTU_OFF_LINE		1	/* remota fora da rede */

/* -- Numero maximo de caracteres para o string de exibicao no grafico de cubas
	  incluido o NUL -- */
#define		MAX_CAR_GCUBAS			8

/* -- Numero maximo de tabelas atualizaveis no hot standby -- */
#define		MAX_TABELAS_ATUALIZACAO		15

/* -- Numero maximo de turnos -- */
#define		MAX_TURNOS				6
#define		MAX_ID_TURNO			2

/* -- Definicao do numero de atn1.4 do projeto -- */
  /* dois atn1.4, um para cada micro de controle, arquivos de calibracao
     diferentes em cada micro */
  #define		UM_UNICO_ATN1_4		0

/* -- Tabelas a serem atualizadas no hotstandby -- */
#define		TABELA_AVC				0	/* -- AVC -- */
#define		TABELA_EST_AVC			1	/* -- EST_AVC -- */
#define		TABELA_SUPERV_AVC		2	/* -- SUPERV_AVC -- */
#define		TABELA_AVL				3	/* -- AVL -- */
#define		TABELA_LOG				4	/* -- LOG -- */
#define		TABELA_ELIMINAEA		5	/* -- ELIMINA_EA -- */
#define		TABELA_SENHAS			6	/* -- SENHAS -- */
#define		TABELA_HIST_TURNO		7	/* -- AVL E SUPERV_AVC TURNO -- */
#define		TABELA_CNF_REL_GRAF		8	/* -- CONFIGURACAO DOS RELAT. GRAFICOS -- */
#define		TABELA_VAL_REL_GRAF		9	/* -- tabela de valores dos relat. graficos -- */
#define		TABELA_INC_OPER    		10	/* -- tabela de incrementos de operacao -- */
#define		TABELA_EV_CUBA   		11	/* -- tabela de eventos do relat. de cubas -- */
  /* -- Alteracao - inicio - 13/03/2001 - Leonel - Alteracao para sala 86Ka -- */
  // #define		TABELA_AJ_CAMISA   	12	/* -- tabela de ajuste de camisa -- */
  /* sala 86ka (atn8) -> copiar parametros para o reserva. As outras salas nao copiam */
  #define		TABELA_CONV_SAD   		12	/* -- tabela de conversores do sad -- */
  // #define		TABELA_AJ_CAMISA   		13	/* -- tabela de ajuste de camisa -- */
  /* -- Alteracao - fim - 13/03/2001 - Leonel - Alteracao para sala 86Ka -- */
/* -- Numero atual de tabelas atualizaveis no hot standby -- */
 /* -- Alteracao - inicio - 13/03/2001 - Leonel - Alteracao para sala 86Ka -- */
  // #define		TABELA_AJ_CAMISA   	12	/* -- tabela de ajuste de camisa -- */
  /* sala 86ka (atn8) -> copiar parametros para o reserva. As outras salas nao copiam */
  #define		NUM_TABELAS_ATUALIZACAO	13
 /* -- Alteracao - fim - 13/03/2001 - Leonel - Alteracao para sala 86Ka -- */

/* -- Definicoes de tabelas para acesso via rede (BdScore) -- */
#define		TABELA_COMUM			20	/* para acesso a toda tabela comum */
#define		TABELA_EVENTOS			21	/* tabela de mensagens de eventos */
#define		TABELA_VAL_GRAF_MINI	22	/* -- tabela de valores dos relat. graficos -- */

/* -- Sub-tabelas do avc -- */
#define		TABELA_AVC_ABS			100
#define		TABELA_AVC_PARAM		101
#define		TABELA_AVC_CLEIT		102
#define		TABELA_AVC_CCONT_MCP	103
#define		TABELA_AVC_CCONT		104
#define		TABELA_AVC_EA			105
#define		TABELA_AVC_RUIDO		106
#define		TABELA_AVC_PAR_USER1 	107
#define		TABELA_AVC_PAR_USER2	108
#define		TABELA_AVC_USER1		109
#define		TABELA_AVC_USER2	 	110
#define		TABELA_AVC_USER3		111
#define		TABELA_AVC_USER4		112

/* -- Sub-tabelas para o descritor de parametros dos conversores -- */
#define		TABELA_CONV_MUX			150
#define		TABELA_CONV_NMUX		151
#define		TABELA_ENT_ESP			152
/* -- alteracao - inicio - 03/01/2001 - Leonel - Inclusao tabelas p/ Atn8 -- */
#define		TABELA_CONV_CUBA_ATN8	153
#define		TABELA_CONV_ESP_ATN8	154
/* -- alteracao - fim - 03/01/2001 - Leonel - Inclusao tabelas p/ Atn8 -- */

/* -- Solicitacoes de usuario para a watchdog -- */
#define		ATUALIZAR_HOTSTANDBY	1
#define		TRANSFERIR_SISTEMA		2

#define QUEUE_HEADER	8

/* -- Acoes enviadas pelo modulo de partida (Score) -- */
#define		PARTIDA_SCORE	1

/* -- Acoes solicitadas ao modulo de partida (Score) -- */
#define		ENVIAR_COMUM		1
#define		ASSUMIR_CONTROLE	2

/* -- Acoes enviadas pelos modulos Mcp, Mcc, McpCorrida e RecChaves -- */
#define		INICIALIZACAO		1
#define		CICLO_LEITURA		2
#define		CICLO_CONTROLE		3
#define		DESABILITOU_LINHA	4

/* -- Acoes enviadas ao modulo SalvaBd -- */
#define		SALVA_TABELAS	1
#define		MUDANCA_DIA		2	/* -- Salva tabelas c/ mudanca de dia -- */
#define		MUDANCA_TURNO	3	/* -- Salva tabelas c/ mudanca de turno -- */

/* -- Tipo do servico solicitado ao modulo SalvaBd -- */
#define		NAO_ESPERA_GRAVACAO		0
#define		ESPERA_GRAVACAO			1

/*-- Valores para deslocamento na exibicao de relatorios por grupo de cubas --*/
   #define	OFFSET_INC_GRUPO	100 	/*-- Diferenca entre o  No. da 1a. cuba --*/
                                    /*-- Redefinido do RelCuba.h -- */
									/*-- de cada grupo.Ex.: 201 - 101 = 100 --*/
   #define	DEZ_INI_GRUPO		1		/*-- Diferenca entre o  No. da 1a. cuba --*/
									/*-- e OFFSET_INC_GRUPO (101 - 100).    --*/
   #define	DEZ_FIM_GRUPO		72  	/*-- Diferenca  entre  o  No. da ultima --*/
									/*-- cuba e OFFSET_INC_GRUPO (172 - 100)--*/
   #define	NUM_GRUPOS_SALA		2		/*-- No. de grupos que compoem a sala.  --*/

/* -- Estados de operacao (selecionados via terminal de operacao) -- */
#define		AUTOMATICO		0
#define		MANUAL			1
/* -- Estados de operacao (chave do campo) -- */
#define		REMOTO			0
#define		LOCAL			1

/* -- Comandos para as remotas -- */
#define		MOVIMENTAR_ANODO	1

/* -- definicoes referentes aa habilitacao/desabilitacao da movimentacao do anodo -- */
#define HABILITA_MOVE    0
#define DESABILITA_MOVE  1
#define DESAB_MOV_BAIXO  2
#define DESAB_MOV_CIMA   3

/* -- Definicoes de acoes para tabela de supressao de EA -- */
#define	SUBIR_ANODO			1
#define	DESCER_ANODO		2
#define	PARAR				3
#define	SOPRAR				4
#define	ESPERAR				5
#define	SUB_ROTINA_1		6
#define	SUB_ROTINA_2		7
#define	SUB_ROTINA_3		8
#define	SUB_ROTINA_4		9
#define	SUB_ROTINA_5		10
#define	QUEBRADA_EXTERNA	11
#define	QUEBRADA_INTERNA	12
#define	TOCAR_SIRENE		13
#define	V_MAIOR				14		/* Se tensao >= TEaLimiteVMaior */
#define	V_MENOR				15		/* Se tensao < TEaLimiteVMenor */
#define	GOTO_PASSO			16

#define	MAX_ACAO_STEP		16		/* limite de acoes disponiveis */

/*-- Tabelas de Sub-Rotinas --*/
#define TABELA_SUP_EA_1				0
#define TABELA_SUP_EA_2				1
#define TABELA_SUP_EA_3				2
#define TABELA_SUP_EA_4				3
#define TABELA_SUP_EA_5				4
#define TABELA_ROTINA_1				5
#define TABELA_ROTINA_2				6
#define TABELA_ROTINA_3				7
#define TABELA_ROTINA_4				8
#define TABELA_ROTINA_5				9

/* -- Definicoes para ajuste de camisa -- */
#define	SUBIR_CAMISA		1
#define	DESCER_CAMISA		2
#define	PARAR_CAMISA		3

/* -- Definicoes para comandar as lampadas/sirenes indicativas de efeito anodico -- */
#define	DESLIGAR			1
#define	LIGAR				2
#define	PISCAR				3
#define	PISCAR_RAPIDO		4

/* -- formas possiveis de incrementos -- */
#define	INCREMENTO_LINEAR	1
#define	INCREMENTO_RAMPA	2

/* -- Classificacao de Efeito Anodico -- */
#define EA_LENTO			1
#define EA_RAPIDO			2
#define EA_MUITO_RAPIDO		3

/* -- Definicoes relativas a ruido -- */
#define	SEM_RUIDO			0
#define	RUIDO_NIVEL1		1
#define	RUIDO_NIVEL2		2
#define	RUIDO_NIVEL3		3
#define	RUIDO_NIVEL4		4
#define	RUIDO_NIVEL5		5

/* -- Estados possiveis das cubas -- */
#define	CUBA_NORMAL			1
#define	CUBA_PARTIDA		2
#define	CUBA_LIGADA			3
#define	CUBA_DESLIGADA		4

/* -- Identificacao dos modulos do Score -- */
#define DRVSAD				0
#define MCP					1
#define TRATA_EA			2
#define MCC					3
#define TABRELGRAF			4
#define	EVENTOS				5
#define IHM_SEALTOUCH		6
#define IHM_CONSOLE			7
#define SALVA_BD			8
#define WATCHDOG			9
#define LOG					10
#define INTERFACE_REMOTA	11
#define REC_REMOTA     		12
#define RECEBE_CHAVES		13
#define REDE0				14
#define REDE1				15
#define REDE2				16
#define REDE3				17
#define REDE4				18
#define REDE5				19
#define REDE6				20
#define REDE7				21
#define ADMIN_SEMAF			22
#define IHM_HOTSTANDBY		23
#define	BD_SCORE			24
  #define IHM_WINDOWS		25
  #define RADIO_BASE		26
#define MODULO_MCP0			38
#define MODULO_MCP1			39
#define MODULO_MCP2			40
#define MODULO_MCP3			41
#define MODULO_MCP4			42
#define MODULO_MCP5			43
#define MODULO_MCC0			44
#define MODULO_MCC1			45
#define MODULO_MCC2			46
#define MODULO_MCC3			47
#define MODULO_MCC4			48
#define MODULO_MCC5			49

/* -- Numero de programas residentes testados pelo modulo Watchdog (0 a REDE7) -- */
#define NUM_PROG_RESID		MAX_PROGS_SCORE

/* -- Num. max. de programas que podem ser ativados pelo modulo Mcc -- */
#define	MAX_MODULOS_ATIVACAO_MCC	6

/* -- Num. max. de programas que podem ser ativados pelo modulo Mcp -- */
#define	MAX_MODULOS_ATIVACAO_MCP	6

/* -- Semaforos utilizados no Score -- */
#define	SEMAF_SALVABD			1
#define	SEMAF_CONFIGURACAO		2
#define	SEMAF_AVL				3
#define	SEMAF_AVC				4
#define	SEMAF_SUPERV_AVC		5
#define	SEMAF_COMUM				6
#define SEMAF_HIST_TURNO		7
#define	SEMAF_REDE1				8
#define	SEMAF_REDE2				9
#define	SEMAF_CNFRELGRAF		10
#define	SEMAF_VALRELGRAF		11
#define	SEMAF_CONFIGURA_HORA	12
#define	SEMAF_EVCUBA			13

/* -- Semaforos utilizados p/ controlar a duplicidade de leitura em uma mesma maquina de supervisao -- */
#define SEMAF_READ_CLEIT		20
#define	SEMAF_READ_PARAM		21
#define	SEMAF_READ_CNFRELGRAF	22
#define	SEMAF_READ_SUPERV_AVC	23
#define	SEMAF_READ_USER1		24
#define	SEMAF_READ_USER2		25
#define	SEMAF_READ_PARUSER1		26
#define	SEMAF_READ_CCONT		27
#define	SEMAF_READ_CCONT_MCP	28

/* semaforos para bloquear alguem em outro nodo */
#define	MAX_SEMAF_REDE			20
#define	SEMAF_CONF_CUBA			0
#define SEMAF_CONF_LINHA		1
#define SEMAF_CONF_METAIS		2
#define SEMAF_CALIB_REM			3
#define SEMAF_CONF_OPER			4
#define SEMAF_CONF_TAB_INC		5
#define SEMAF_CONF_TAB_EA		6
#define SEMAF_CONF_REMOTA		7

/* -- Nome do spooler -- */
#define	NOME_SPOOLER		"/qnx/spooler"	/* acrescentar nodo ao fim */

/* -- Nomes para abertura das memorias compartilhadas -- */
#define	NOME_SHM_COMUM		"Atan/Score/Comum"
#define NOME_SHM_AVC		"Atan/Score/Avc"
#define NOME_SHM_ARQVAR		"Atan/Score/ArqVar"
/* Usado apenas para intercalar os outros segmentos (read_only) e melhorar
   tolerancia a falta. */
#define NOME_SHM_DUMMY		"Atan/Score/Dummy"

/* -- Nome do Score na base de dados de nomes do QNX (como nome global) -- */
/* -- Deve ser acompanhado do numero da reducao -- */
#define	NOME_SCORE			"/Atan/Score%02d"


/* -- Path dos arquivos da base de dados -- */
#define	ARQUIVO_COMUM		"/score/base_dados/comum"
#define	ARQUIVO_AVC			"/score/base_dados/avc"
#define	ARQUIVO_SUPERV_AVC	"/score/base_dados/superv_avc"
#define	ARQUIVO_DESCR_CONV	"/score/base_dados/conv/descr_conv"
#define	ARQUIVO_HISTORICO   "/score/hist/hist_%02d_%02d_%02d"
#define	ARQUIVO_HIST_TURNO  "/score/hist/turno%d_%02d_%02d_%02d"

/* -- Path dos arquivos de descritores de relatorio -- */
#define PATH_DESCRITORES    "/score/descr"

/* -- para compatibilidade com CLOCKS_PER_SEC do qnx2 -- */
#define		TIMES_PER_SEC		1l

/* -- numero maximo de estacoes phindows -- */
#define		MAX_LOGIN_PHINDOWS	30
#define		MAX_LOGIN_RADIO		8

#endif		/* #ifndef		_SCORECONST.H */

/* -- Fim do arquivo ScoreConst.h -- */
