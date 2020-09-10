/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.XX

	PROJETO  : TODOS

	SISTEMA  : TODOS

	ARQUIVO  : ScoreErros.h

	CONTEUDO : defines de todos os erros do sistema

	AUTOR    : Alexandre Bandeira

	SISTEMA OPERACIONAL:  QNX 4.22		-		COMPILADOR: WATCOM C - V9.52

	VERSAO   : 1.0		  -	  DATA  : 06/12/96

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
06/12/96 | Edicao inicial                              			| Bandeira
-------------------------------------------------------------------------------
******************************************************************************/

#ifndef		_SCOREERROS_H

/*
------------------------------------------------------------------------------
				Definicoes
------------------------------------------------------------------------------
*/
/* -- Controle de inclusao -- */
#define		_SCOREERROS_H

#define	COD_ERRO_0		0		/* falha PegaComum */
#define	COD_ERRO_1		1		/* falha PegaRelGraf */
#define	COD_ERRO_2		2		/* falha PegaRelGraf2 */
#define	COD_ERRO_3		3		/* falha ComumAlarmeCuba */
#define	COD_ERRO_4		4		/* falha ComumAlarmeLinha */
#define	COD_ERRO_5		5		/* nao e' permitido rodar o SCORE neste nodo */
#define	COD_ERRO_6		6		/* falha abertura de arquivo */
#define	COD_ERRO_7		7		/* falha leitura de arquivo */
#define	COD_ERRO_8		8		/* falha gravacao de arquivo */
#define	COD_ERRO_9		9		/* falha seek de arquivo */
#define	COD_ERRO_10		10		/* falha criacao de tarefa */
#define	COD_ERRO_11		11		/* falha qnx_proxy_attach */
#define	COD_ERRO_12		12		/* falha timer_create */
#define	COD_ERRO_13		13		/* falha system */
#define	COD_ERRO_14		14		/* falha PictureOpen */
#define	COD_ERRO_15		15		/* falha WindowOpen */
#define	COD_ERRO_16		16		/* falha ScoreBd leitura */
#define	COD_ERRO_17		17		/* falha ScoreBd gravacao */
#define	COD_ERRO_18		18		/* falha Receive */
#define	COD_ERRO_19		19		/* falha OffsetTab */
#define	COD_ERRO_20		20		/* falha shm_open */
#define	COD_ERRO_21		21		/* falha mmap */
#define	COD_ERRO_22		22		/* falha EnvTabEliminaEa */
#define	COD_ERRO_23		23		/* falha CopyElements */
#define	COD_ERRO_24		24		/* falha ElementText */
#define	COD_ERRO_25		25		/* falha abertura queue (queue_open) */
#define	COD_ERRO_26		26		/* falha escrita queue (queue_write) */
#define	COD_ERRO_27		27		/* falha leitura queue (queue_read) */
#define	COD_ERRO_28		28		/* falha PiscaSaida */
#define	COD_ERRO_29		29		/* falha EscSaiDig */
#define	COD_ERRO_30		30		/* falha CmdSaidaRem */
#define	COD_ERRO_31		31		/* falha Send */
#define	COD_ERRO_32		32		/* falha ltrunc */
#define	COD_ERRO_33		33		/* falha spawn (criacao de tarefa) */
#define	COD_ERRO_34		34		/* falha malloc */
#define	COD_ERRO_35		35		/* Limite de 30 picts Menu ultrapassado */
#define	COD_ERRO_36		36		/* falha LerEntDig */
#define	COD_ERRO_37		37		/* falha LigSaiTmp */
#define	COD_ERRO_38		38		/* falha LigSaiTmp (move anodo) */
#define	COD_ERRO_39		39		/* falha SolicitaSemaf */
#define	COD_ERRO_40		40		/* falha qnx_name_attach */
#define	COD_ERRO_41		41		/* num. entradas nao multiplexadas incorreto */
#define	COD_ERRO_42		42		/* falha fstat */
#define	COD_ERRO_43		43		/* falha StartWindows */
#define	COD_ERRO_44		44		/* falha isatty */
#define	COD_ERRO_45		45		/* base de tempo do Mcp nao definida */
#define	COD_ERRO_46		46		/* falha PrintOpen */
#define	COD_ERRO_47		47		/* falha PrintArea */
#define	COD_ERRO_48		48		/* falha qnx_name_locate */
#define	COD_ERRO_49		49		/* overflow fila de leituras do drvsad */
#define	COD_ERRO_50		50		/* erro drvsad, cod falha: 1=qnx_hint_attach
			 Interf A ou B, 2=qnx_hint_attach timer, 3=qnx_hint_detach
			 interf A ou B, 4=timeout na espera de aquisicao de dado do atn1.4
			 qdo. buffer vazio (timer da 059 nao funcionando) */
#define	COD_ERRO_51		51		/* falha qnx_hint_attach */
#define	COD_ERRO_52		52		/* falha GraphicsOpen */
#define	COD_ERRO_53		53		/* falha leitura tabela(s) nodo controle */
#define	COD_ERRO_54		54		/* falha geracao arquivo temporario de log */
#define	COD_ERRO_55		55		/* falha qnx_psinfo */
#define	COD_ERRO_56		56		/* numero invalido de argumentos */
#define	COD_ERRO_57		57		/* falha CriaAreaGlobal */
#define	COD_ERRO_58		58		/* ativacao invalida (via receive) */
#define	COD_ERRO_59		59		/* floating point exception */
#define	COD_ERRO_60		60		/* falha signal */
#define	COD_ERRO_61		61		/* tarefa nao esta ativa */
#define	COD_ERRO_62		62		/* mensagem de origem desconhecida */
#define	COD_ERRO_63		63		/* falha CfgAlimRem */
#define	COD_ERRO_64		64		/* timeout de comunicacao */
#define	COD_ERRO_65		65		/* status de erro na comunicacao */
#define	COD_ERRO_66		66		/* remota voltou a rede */
#define	COD_ERRO_67		67		/* remota saiu da rede */
#define	COD_ERRO_68		68		/* falha leitura de canal (EnvRemota) */
#define	COD_ERRO_69		69		/* falha envio comando para EnvRemota (RecRemota) */
#define	COD_ERRO_70		70		/* falha criacao do buffer de mensagens de eventos */
#define	COD_ERRO_71		71		/* codigo de evento invalido (EventosMsg) */
#define	COD_ERRO_72		72		/* falha criacao do segmento da base de dados de strings */
#define	COD_ERRO_73		73		/* falha setsid */
#define	COD_ERRO_74		74		/* falha qnx_vc_attach */
#define	COD_ERRO_75		75		/* falha qnx_get_clock */
#define	COD_ERRO_76		76		/* falha setprio */
#define	COD_ERRO_77		77		/* falha ReadMsg */
#define	COD_ERRO_78		78		/* Tamanho registro recebido invalido (WatchFCtrl) */
#define	COD_ERRO_79		79		/* falha Reply */
#define	COD_ERRO_80		80		/* falha ComumGrupoCuba */
#define	COD_ERRO_81		81		/* falha exibicao arquivo ajuda */
#define	COD_ERRO_82		82		/* falha retorno de status */
#define	COD_ERRO_83		83		/* falha leitura de arquivo descritores */
#define	COD_ERRO_84		84		/* falha gravacao do cabecalho */
#define	COD_ERRO_85		85		/* falha calloc */
#define	COD_ERRO_86		86		/* falha copia arquivo eventos nodo controle */
#define	COD_ERRO_87		87		/* falha OpenWindow */
#define	COD_ERRO_88		88		/* falha ComumValGraf */
#define	COD_ERRO_89		89		/* falha WindowFind */
#define	COD_ERRO_90		90		/* falha PictureFind */
#define	COD_ERRO_91		91		/* falha kill */
#define COD_ERRO_92		92		/* falha calculo de IndTime */
#define	COD_ERRO_93		93		/* falha ComumValMini */
#define	COD_ERRO_94		94		/* falha PutEvent */
#define	COD_ERRO_95		95		/* falha OpenComum */
#define	COD_ERRO_96		96		/* falha LeComum */
#define COD_ERRO_97		97		/* falha mktime */
#define COD_ERRO_98		98		/* argumento(s) invalido(s) */ 
#define COD_ERRO_99     99      /* falha ElementInfo */
#define COD_ERRO_100    100     /* DrvPclta buffer cheio */
#define COD_ERRO_101    101     /* Falha sinalizacao do micro reserva */
#define COD_ERRO_102    102     /* Falha de atualizacao do micro reserva */
#define COD_ERRO_103    103     /* acao invalida na tabela de supressao */
#define COD_ERRO_104    104     /* erro RedeAtn8. Codigo erro: 1=falha criacao
								   fifo Atn8, */
#define	COD_ERRO_105	105		/* falha getlogin() */
#define	COD_ERRO_106	106		/* falha LeGrupoCubas() */
#define	COD_ERRO_107	107		/* falha read_msg() */
#define	COD_ERRO_108	108		/* falha write_msg() */
#define COD_ERRO_109	109		/* numero de parametros invalido */

/*
------------------------------------------------------------------------------
				Definicoes de sinonimos
------------------------------------------------------------------------------
*/
#define STR_ERRO_QUEUE			SCORE_ERR_6
#define ERRO_PEGACOMUM			SCORE_ERR_0
#define ERRO_PEGARELGRAF		SCORE_ERR_1

#endif
/* -- fim ScoreErros.h -- */

