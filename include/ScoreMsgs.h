/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.XX

	PROJETO  : TODOS

	SISTEMA  : TODOS

	ARQUIVO  : ScoreMsgs.h

	CONTEUDO : Mensagens, strings e erros gerais do Score (para traducao)

	AUTOR    : Alexandre Bandeira

	SISTEMA OPERACIONAL:  QNX 4.22		-		COMPILADOR: WATCOM C - V9.52

	VERSAO   : 1.0		  -	  DATA  : 06/12/96

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
06/12/95 | Edicao inicial                              			| Bandeira
-------------------------------------------------------------------------------
$Id: ScoreMsgs.h,v 1.11 2008/11/27 21:26:38 marcelo Exp $

$Log: ScoreMsgs.h,v $
Revision 1.11  2008/11/27 21:26:38  marcelo
Inclusao de variaveis para novo tratamento de ruido lento da mesma forma
que o ruido rapido.

Revision 1.10  2008/07/08 13:26:52  leo
Incluidos novos limites para tratamento de ruidos.

******************************************************************************/

#ifndef		_SCOREMSGS_H

/* Inclusoes */
#include	<ScoreStr.h>

/*
------------------------------------------------------------------------------
				Definicoes
------------------------------------------------------------------------------
*/
/* -- Controle de inclusao -- */
#define		_SCOREMSGS_H

/* strings pre-definidos para erros */
#define	SCORE_ERR_0			0		/* %s->Erro=%d */
#define	SCORE_ERR_1			1		/* Erro=%d */
#define	SCORE_ERR_2			2		/* %s->Erro=%d Arq=%s */
#define	SCORE_ERR_3			3		/* %s->Erro=%d Cmd=%s */
#define	SCORE_ERR_4			4		/* %s->Erro=%d Status=%d Tabela=%d */
#define	SCORE_ERR_5			5		/* Cuba=%d Erro=%d Cod=%d */
#define	SCORE_ERR_6			6		/* %s->Erro=%d Nome=%s Cod=%d */
#define	SCORE_ERR_7			7		/* %s Erro=%d Cod=%d */
#define	SCORE_ERR_8			8		/* Erro=%d Cod=%d */
#define	SCORE_ERR_9			9		/* Erro=%d Nome=%s Cod=%d */
#define	SCORE_ERR_10		10		/* Erro=%d Cd1=%d Cd2=%d Cd3=%d */
#define	SCORE_ERR_11		11		/* Cuba=%d %s */
#define	SCORE_ERR_12		12		/* %s->Erro=%d Cd1=%d Cd2=%d Cd3=%d */
#define	SCORE_ERR_13		13		/* Canal=%d Rem=%d */

/* strings gerais de uso de todo o sistema */
#define	SCORE_MSG_0			20		/* E R R O */
#define	SCORE_MSG_1			21		/* A T E N C A O */
#define	SCORE_MSG_2			22		/* Operador %d nao tem nivel de acesso! */
#define	SCORE_MSG_3			23		/* %s->Falta o parametro 'Titulo' no ihm_config */
#define	SCORE_MSG_4			24		/* Cuba inicial invalida */
#define	SCORE_MSG_5			25		/* Cuba final invalida */
#define	SCORE_MSG_6			26		/* Cuba inicial maior que cuba final */
#define SCORE_MSG_7			27		/* EVTOTAL */
#define SCORE_MSG_8			28		/* EVPROC */
#define SCORE_MSG_9			29		/* EVSIST */
#define SCORE_MSG_10		30		/* EVLINHA */
#define SCORE_MSG_11		31		/* EVCUBA */
#define SCORE_MSG_12		32		/* EVMENS */
#define SCORE_MSG_13		33		/* Cancela|CA;Confirma|CO */
#define SCORE_MSG_14		34		/* Confirma Impressao do Relatorio ? */
#define SCORE_MSG_15		35		/* 3 Tentativas incorretas, pedido de senha abortado! */
#define SCORE_MSG_16		36		/* Operador nao cadastrado ! */
#define SCORE_MSG_17		37		/* Senha invalida ! */
#define SCORE_MSG_18		38		/* Cubas por Grupo */
#define SCORE_MSG_19		39		/* Abandona */
#define SCORE_MSG_20		40		/* Confirma */
#define SCORE_MSG_21		41		/* Impressora Nodo */
#define SCORE_MSG_22		42		/* Pre Selecao reinicializada */
#define SCORE_MSG_23		43		/* Controle de Reducoes */
#define SCORE_MSG_24		44		/* Ajuda nao disponivel */
#define SCORE_MSG_25		45		/* Limpa */
#define SCORE_MSG_26		46		/* Cubas */
#define SCORE_MSG_27		47		/* NODO */
#define SCORE_MSG_28		48		/* ATIVADO */
#define SCORE_MSG_29		49		/* DESATIVADO */
#define SCORE_MSG_30		50		/* Formato invalido ou Cuba invalida na Selecao Especial */
#define SCORE_MSG_31		51		/* Formato invalido ou Cuba invalida na Exclusao de Cubas */
#define SCORE_MSG_32		52		/* Copiando arquivo %s para %s */
#define SCORE_MSG_33		53		/* Atual */
#define SCORE_MSG_34		54		/* Data inicial invalida */
#define SCORE_MSG_35		55		/* Data final invalida */
#define SCORE_MSG_36		56		/* Data inicial maior que data final */
#define SCORE_MSG_37		57		/* Dia invalido na linha de Exclusao */
#define SCORE_MSG_38		58		/* Cuba invalida na linha de Exclusao */
#define SCORE_MSG_39		59		/* Expressao invalida [%s] */
#define SCORE_MSG_40		60		/* Expressao invalida [%s-%s] */
#define SCORE_MSG_41		61		/* Por Favor, Selecione Algoritmo(s) */
#define SCORE_MSG_42		62		/* Cuba Invalida na Linha de Selecao de Cubas */
#define SCORE_MSG_43		63		/* Nao Existe Cuba(s) Selecionada(s) */
#define SCORE_MSG_44		64		/* Nao ha' dados a exibir */
#define SCORE_MSG_45		65		/* Nao Existe Arquivo de eventos para data solicitada */
#define SCORE_MSG_46		66		/* Flag de confirmacao setado, mas nao existe argumento */
#define SCORE_MSG_47		67		/* Nao Inic */
#define SCORE_MSG_48		68		/* Todos */
#define SCORE_MSG_49		69		/* Auto */

#define SCORE_MSG_50		70		/* G   A */
#define SCORE_MSG_51		71		/* G   B */
#define SCORE_MSG_52		72		/* G   C */
#define SCORE_MSG_53		73		/* G   D */
#define SCORE_MSG_54		74		/* G   E */
#define SCORE_MSG_55		75		/* G   F */
#define SCORE_MSG_56		76		/* G   G */
#define SCORE_MSG_57		77		/* G   H */

#define SCORE_MSG_58		78		/* Faixa Cubas */
#define SCORE_MSG_59		79		/* NENHUMA */
#define SCORE_MSG_60		80		/* Especial */
#define SCORE_MSG_61		81		/* Cuba Excl */

#define SCORE_MSG_62		82		/* GA */
#define SCORE_MSG_63		83		/* GB */
#define SCORE_MSG_64		84		/* GC */
#define SCORE_MSG_65		85		/* GD */
#define SCORE_MSG_66		86		/* GE */
#define SCORE_MSG_67		87		/* GF */
#define SCORE_MSG_68		88		/* GG */
#define SCORE_MSG_69		89		/* GH */
#define SCORE_MSG_70		90		/* RESERVA */
#define SCORE_MSG_71		91		/* RESERVA */
#define SCORE_MSG_72		92		/* TODOS */
#define SCORE_MSG_73		93		/* ES */
#define SCORE_MSG_74		94		/* RESERVA */
#define SCORE_MSG_75		95		/* RESERVA */
#define SCORE_MSG_76		96		/* Versao */
#define SCORE_MSG_77		97		/* Sistema de Controle de Reducoes */

#define SCORE_MSG_78		98		/* Algoritmo  */
#define SCORE_MSG_79		99		/* Data Inicial */
#define SCORE_MSG_80		100		/* Data Final */
#define SCORE_MSG_81		101		/* Data Excl */
#define SCORE_MSG_82		102		/* Turno */

#define SCORE_MSG_83		103		/* DISPOSITIVO %s */
#define SCORE_MSG_84		104		/* FALHA ACESSO DISPOSITIVO %s */
#define SCORE_MSG_85		105		/* Erro na leitura do status da impressora */
#define SCORE_MSG_86		106		/* Impressora desconectada */
#define SCORE_MSG_87		107		/* Impressora esta desligada */

#define SCORE_MSG_88		108		/* DATA DE INICIO FORA DOS %d DIAS DISPONIVEIS */
#define SCORE_MSG_89		109		/* DATA FINAL FORA DOS %d DIAS DISPONIVEIS */
#define SCORE_MSG_90		110		/* ERRO NO FORMATO DA DATA */
#define SCORE_MSG_91		111		/* DATA INVALIDA */
#define SCORE_MSG_92		112		/* %s->Nao Achei Var=%s Tab=%s */
#define SCORE_MSG_93		113		/* %s->Nao Trate Cuba=%d TabScore=%d OffVar=%d IndVar=%d */
#define SCORE_MSG_94		114		/* Substituir;Cancela */
#define SCORE_MSG_95		115		/* Arquivo ja Existe ! Substituir ? */
#define SCORE_MSG_96		116		/* Arquivo %s Criado com Sucesso */
#define SCORE_MSG_97		117		/* Valor fora dos limites */
#define SCORE_MSG_98		118		/* Confirma;Cancela */
#define SCORE_MSG_99		119		/* DELECAO */
#define SCORE_MSG_100		120		/* Confirma a delecao da variavel %s */
#define SCORE_MSG_101		121		/* Confirma a delecao da variavel trigger */
#define SCORE_MSG_102		122		/* Entre com a(s) Cuba(s) */
#define SCORE_MSG_103		123		/* Aguarde Criacao do(s) Log(s)... */
#define SCORE_MSG_104		124		/* Log(s) Gerado(s) para Cuba(s): */
#define SCORE_MSG_105		125		/* Duracao Invalida */
#define SCORE_MSG_106		126		/* Trigger tem que ser menor que Duracao Log menos %d minutos */

#define SCORE_MSG_107		127		/* Log %d (min): Trigger %d(min) Invalido (min: %d max: %d) */
#define SCORE_MSG_108		128		/* Log %2.1f (seg): Trigger %d(min) Invalido (min: %d max: %d) */

#define SCORE_MSG_109		129		/* Log %d (min) - Duracao maximo: %d dias, minimo: %d horas */
#define SCORE_MSG_110		130		/* Log %2.1f (seg) - Duracao maximo: %d hora(s), minimo: %d min */

#define SCORE_MSG_111		131		/* Nao ha' variavel(s) Selecionada(s) */
#define SCORE_MSG_112		132		/* Cuba nao Configurada */
#define SCORE_MSG_113		133		/* Numero maximo de logs esgotado */
#define SCORE_MSG_114		134		/* Log %s ja' existe */
#define SCORE_MSG_115		135		/* Memoria insuficiente */
#define SCORE_MSG_116		136		/* Nome do arquivo invalido */
#define SCORE_MSG_117		137		/* Codigo de retorno invalido */
#define SCORE_MSG_118		138		/* Log %s nao esta ativo */
#define SCORE_MSG_119		139		/* Log %s desativado */
#define SCORE_MSG_120		140		/* Log %s deletado */
#define SCORE_MSG_121		141		/* Data inicial maior que a ultima amostra do arquivo */
#define SCORE_MSG_122		142		/* Nao ha' amostras no Log %s */
#define SCORE_MSG_123		143		/* Numero de divisoes incorreto */
#define SCORE_MSG_124		144		/* Fator de compactacao invalido */

#define SCORE_MSG_125		145		/* Impressao de Graficos de Log */
#define SCORE_MSG_126		146		/* Cuba: %d     Data criacao: %s     Duracao: %s */
#define SCORE_MSG_127		147		/*                Data inicio: %s */
#define SCORE_MSG_128		148		/*     Data fim: %s */
#define SCORE_MSG_129		149		/* Identificacao das variaveis */
#define SCORE_MSG_130		150		/*   Codigo    Nome                 minimo      maximo    Tipo */

#define SCORE_MSG_131		151		/* Fator de compactacao : %d */
#define SCORE_MSG_132		152		/*          Algoritmo de compactacao : */
#define SCORE_MSG_133		153		/* Media */
#define SCORE_MSG_134		154		/* Maior */

#define SCORE_MSG_135		155		/* Dump de um Log */
#define SCORE_MSG_136		156		/* Cuba: %d           Data criacao: %s           Duracao: %s */
#define SCORE_MSG_137		157		/*                      Data inicio: %s */ 
#define SCORE_MSG_138		158		/*           Data fim: %s */

#define SCORE_MSG_139		159		/* Programa de teste da Interface Analogica */
#define SCORE_MSG_140		160		/* Escolha uma opcao */
#define SCORE_MSG_141		161		/* Teste completo */
#define SCORE_MSG_142		162		/* Calibracao do ATN */
#define SCORE_MSG_143		163		/* Terminar */
#define SCORE_MSG_144		164		/* Opcao */
#define SCORE_MSG_145		165		/* Teste completo da Interface Analogica */
#define SCORE_MSG_146		166		/* Acione ENTER para continuar */
#define SCORE_MSG_147		167		/* Testando placa de interface com o PC (modulo 059) */
#define SCORE_MSG_148		168		/* Placa nao responde! */
#define SCORE_MSG_149		169		/* Acoes */
#define SCORE_MSG_150		170		/* Verificar estrapes */
#define SCORE_MSG_151		171		/* Verificar se velocidade do barramento para acesso de I/O */
#define SCORE_MSG_152		172		/* esta menor que 10 MHz (Bios do computador) */

#define SCORE_MSG_153		173		/* Nao existe ainda dados para serem mostrados */
#define SCORE_MSG_154		174		/* O sistema nao tem %d bytes disponiveis para abrir o grafico */
#define SCORE_MSG_155		175		/* Log 2.0 min */
#define SCORE_MSG_156		176		/* Log 0.5 seg */
#define SCORE_MSG_157		177		/* Zoom nao pode ser efetuado */
#define SCORE_MSG_158		178		/* Use: MigraHist Data PathSaida TipoHist [Turno] */

#define SCORE_MSG_159		179		/* Substituir a placa */
#define SCORE_MSG_160		180		/* Migrando arquivos historicos... */
#define SCORE_MSG_161		181		/* Placa com base de tempo errada! */
#define SCORE_MSG_162		182		/* %s->Falha copia do arquivo historico para %s */
#define SCORE_MSG_163		183		/* %s->Falha gravacao dos arquivos migrados */
#define SCORE_MSG_164		184		/* Tipo de historico invalido */
#define SCORE_MSG_165		185		/* Destino da migracao %s invalido */
#define SCORE_MSG_166		186		/* Arquivos gerados a partir de %s */
#define SCORE_MSG_167		187		/* Use: MigraLogW PathSaida */
#define SCORE_MSG_168		188		/* Use: MigraLog ArquivoEntrada PathSaida */
#define SCORE_MSG_169		189		/* Erro no nome do arquivo de saida %s */
#define SCORE_MSG_170		190		/* Migrando arquivos de Log... */
#define SCORE_MSG_171		191		/* Erro na copia do arquivo de log para %s */
#define SCORE_MSG_172		192		/* Nao existem registros no arquivo de Log */
#define SCORE_MSG_173		193		/* Esperado=%f segundos, medido=%f segundos */
#define SCORE_MSG_174		194		/* Testando modulos controladores dos conversores (062 e 063) */
#define SCORE_MSG_175		195		/* Os modulos controladores de conversores nao responderam! */
#define SCORE_MSG_176		196		/* Verificar se o equipamento esta ligado */
#define SCORE_MSG_177		197		/* Verificar coneccao do cabo de comunicacao com o computador */
#define SCORE_MSG_178		198		/* Verificar as tensoes de alimentacao do equipamento */
#define SCORE_MSG_179		199		/* Substituir o modulo controlador mestre (062), posicao XB01 */
#define SCORE_MSG_180		200		/* Substituir o modulo de interface com o PC-AT (059) */
#define SCORE_MSG_181		201		/* %s->Limite inferior >= Limite superior */
#define SCORE_MSG_182		202		/* Limites - %s */
#define SCORE_MSG_183		203		/* Variaveis */
#define SCORE_MSG_184		204		/* Superior */
#define SCORE_MSG_185		205		/* Inferior */
#define SCORE_MSG_186		206		/* Defeito em %d modulo(s) controlador(es) de conversores! */
#define SCORE_MSG_187		207		/* Acao */
#define SCORE_MSG_188		208		/* Substituir o(s) modulo(s) que indicar(am) defeito */
#define SCORE_MSG_189		209		/* Modulo controlador de conversores (063) posicao */
#define SCORE_MSG_190		210		/* LIVRE PARA USO */
#define SCORE_MSG_191		211		/* LIVRE PARA USO */
#define SCORE_MSG_192		212		/* Dado escrito=%02x   Dado lido=%02x */
#define SCORE_MSG_193		213		/* %d Conversor(es) com problema! */
#define SCORE_MSG_194		214		/* Numero de amostras no Log < 2 */
#define SCORE_MSG_195		215		/* Testando conversores */
#define SCORE_MSG_196		216		/* Numero maximo de variaveis permitidas = %d */
#define SCORE_MSG_197		217		/* Escolha apenas uma variavel para o trigger */
#define SCORE_MSG_198		218		/* Substituir placa(s) do(s) conversor(es) com problema */
#define SCORE_MSG_199		219		/* Cancela */
#define SCORE_MSG_200		220		/* Conversores A/D OK! */
#define SCORE_MSG_201		221		/* Calibracao da Interface Analogica */
#define SCORE_MSG_202		222		/* Entre com os valores */
#define SCORE_MSG_203		223		/* Sinal de entrada */
#define SCORE_MSG_204		224		/* Fundo de escala do sinal de entrada */
#define SCORE_MSG_205		225		/* Posicao */
#define SCORE_MSG_206		226		/* Formato = complemento de dois */
#define SCORE_MSG_207		227		/* Conversor (a-h) ou digite 0 p/ voltar ao menu principal */
#define SCORE_MSG_208		228		/* temporizacao invalida! */
#define SCORE_MSG_209		229		/* CfgGraf */
#define SCORE_MSG_210		230		/* Numero invalido de parametros */
#define SCORE_MSG_211		231		/* Parametros sendo configurados em outro nodo */
#define SCORE_MSG_212		232		/* CfgSenha */
#define SCORE_MSG_213		233		/* CfgCuba */
#define SCORE_MSG_214		234		/* Alteracao efetuada corretamente */
#define SCORE_MSG_215		235		/* Nome do parametro invalido */
#define SCORE_MSG_216		236		/* Cuba invalida */
#define SCORE_MSG_217		237		/* IntervJanRRap invalido (1,2,3,4,6 ou 8) -> alterado para 6 horas */
#define SCORE_MSG_218		238		/* Criando tarefa IHM_HOTSTANDBY */
#define SCORE_MSG_219		239		/* AGUARDE INICIALIZACAO! */
#define SCORE_MSG_220		240		/* Criando tarefa EVENTOS */
#define SCORE_MSG_221		241		/* Criando tarefa WATCHDOG */
#define SCORE_MSG_222		242		/* Criando tarefa ADMIN_SEMAF */
#define SCORE_MSG_223		243		/* Criando tarefa SALVA_BD */
#define SCORE_MSG_224		244		/* Criando tarefa MODULO_MCP */
#define SCORE_MSG_225		245		/* Criando tarefa TRATA_EA */
#define SCORE_MSG_226		246		/* Criando tarefa MCP */
#define SCORE_MSG_227		247		/* Criando tarefa MODULO_MCC */
#define SCORE_MSG_228		248		/* Criando tarefa LOG */
#define SCORE_MSG_229		249		/* Criando tarefa TABRELGRAF */
#define SCORE_MSG_230		250		/* Criando tarefa MCC */
#define SCORE_MSG_231		251		/* HOT STANDBY ASSUMINDO O CONTROLE! */
#define SCORE_MSG_232		252		/* Criando tarefa REDE_RTU */
#define SCORE_MSG_233		253		/* Criando tarefa INTERFACE_REMOTA */
#define SCORE_MSG_234		254		/* Criando tarefa REC_REMOTA */
#define SCORE_MSG_235		255		/* Criando tarefa RECEBE_CHAVES */
#define SCORE_MSG_236		256		/* Criando tarefa DRVSAD */
#define SCORE_MSG_237		257		/* ERRO FATAL */
#define SCORE_MSG_238		258		/* Criando tarefa GER_SAIDA */
#define SCORE_MSG_239		259		/* Criando tarefa BD_SCORE */
#define SCORE_MSG_240		260		/* Criando tarefa IHM_CONSOLE */
#define SCORE_MSG_241		261		/* SISTEMA RESERVA PRONTO! */
#define SCORE_MSG_242		262		/* SISTEMA ATIVADO! */
#define SCORE_MSG_243		263		/* FimScore */
#define SCORE_MSG_244		264		/* Painel */
#define SCORE_MSG_245		265		/* Local */
#define SCORE_MSG_246		266		/* Remoto */
#define SCORE_MSG_247		267		/* Ativa */
#define SCORE_MSG_248		268		/* Desativa */
#define SCORE_MSG_249		269		/* Const */
#define SCORE_MSG_250		270		/* Rampa */
#define SCORE_MSG_251		271		/* Cuba %d retirada do controle! */
#define SCORE_MSG_252		272		/* Linha retirada do controle! */
#define SCORE_MSG_253		273		/* Provavel falha subida anodo cuba=%d */
#define SCORE_MSG_254		274		/* Provavel falha descida anodo cuba=%d */
#define SCORE_MSG_255		275		/* Remota %d configurada com sucesso */
#define SCORE_MSG_256		276		/* Falha na comunicacao com a Remota ! [%02x] */
#define SCORE_MSG_257		277		/* CfgAtn7 */
#define SCORE_MSG_258		278		/* Controle */
#define SCORE_MSG_259		279		/* LENTO */ /* Mneumonicos */
#define SCORE_MSG_260		280		/* MRAP */
#define SCORE_MSG_261		281		/* RAPID */
#define SCORE_MSG_262		282		/* ERRO */
#define SCORE_MSG_263		283		/* FRACO */ /*Classificacao dos ruidos rapido ou lento*/
#define SCORE_MSG_264		284		/* FORTE */ /*Classificacao dos ruidos rapido ou lento*/
#define SCORE_MSG_265		285		/* Inicio */
#define SCORE_MSG_266		286		/* Fim */

#define SCORE_MSG_267		287		/* Normal */ /* estados */
#define SCORE_MSG_268		288		/* Partida */ /* estados */
#define SCORE_MSG_269		289		/* Ligada */ /* estados */
#define SCORE_MSG_270		290		/* Deslig */ /* estados */
#define SCORE_MSG_271		291		/* Abandona|Abandona;Confirma|Confirma */
#define SCORE_MSG_272		292		/* Dados nao Gravados, Confirma Saida ? */

#define SCORE_MSG_273		293		/* Confirma alteracao de %s para %s ? */
#define SCORE_MSG_274		294		/* Filtro */
#define SCORE_MSG_275		295		/* Especial */
#define SCORE_MSG_276		296		/* Exclusao */
#define SCORE_MSG_277		297		/* Algorit. */

#define SCORE_MSG_278		298		/* HabLinha */
#define SCORE_MSG_279		299		/* Tensao cuba %d acima de %2.1fV! */
#define SCORE_MSG_280		300		/* ATENCAO - GRAVACAO PARA RANGE DE CUBAS */

#define SCORE_MSG_281		301		/* Corrida  */ /* Tamanhos fixos! */
#define SCORE_MSG_282		302		/*    EA    */
#define SCORE_MSG_283		303		/* Man-Loc  */
#define SCORE_MSG_284		304		/* Man-Rem  */
#define SCORE_MSG_285		305		/* Man-Ctrl */
#define SCORE_MSG_286		306		/* Quebrada */
#define SCORE_MSG_287		307		/* Help: %s nao existe ! */

#define SCORE_MSG_288		308		/* NOME DA VARIAVEL */
#define SCORE_MSG_289		309		/* U. ENGENHARIA */
#define SCORE_MSG_290		310		/* RANGE MINIMO */
#define SCORE_MSG_291		311		/* RANGE MAXIMO */
#define SCORE_MSG_292		312		/* VALOR ATUAL */
#define SCORE_MSG_293		313		/* DESCRICAO DA VARIAVEL */
#define SCORE_MSG_294		314		/* NENHUM */
#define SCORE_MSG_295		315		/* - AJUDA - */

#define SCORE_MSG_296		316		/* Micro voltou para rede no canal %d */
#define SCORE_MSG_297		317		/* Micro saiu da rede no canal %d */
#define SCORE_MSG_298		318		/* Remota voltou a rede */
#define SCORE_MSG_299		319		/* Remota saiu da rede */

#define SCORE_MSG_300		320		/* TODAS */
#define SCORE_MSG_301		321		/* Tag %s invalido, abortando CfgParCubasW, avisar ATAN ! */
#define SCORE_MSG_302		322		/* Nenhum */
#define SCORE_MSG_303		323		/* Variavel %s, formato invalido ou fora do range */
#define SCORE_MSG_304		324		/* %s fora da faixa [%.3lf]! Configura para minimo [%.3f]? */
#define SCORE_MSG_305		325		/* Detalhe para Cuba(s) da Variavel */
#define SCORE_MSG_306		326		/* CfgLinha */
#define SCORE_MSG_307		327		/* CfgAjCam */
#define SCORE_MSG_308		328		/* Confirma impressao da tabela ? */

#define SCORE_MSG_309		329		/* Subir */
#define SCORE_MSG_310		330		/* Descer */
#define SCORE_MSG_311		331		/* Parar */
#define SCORE_MSG_312		332		/* Acao invalida */
#define SCORE_MSG_313		333		/* Duracao de ajuste invalida */

#define SCORE_MSG_314		334		/* Numero da reducao nao definido! */
#define SCORE_MSG_315		335		/* Nao localizado controle da reducao %d! */
#define SCORE_MSG_316		336		/* Numero da tabela invalido */
#define SCORE_MSG_317		337		/* CfgEliEa */
#define SCORE_MSG_318		338		/* Duracao invalida [max=%d] [min=%d] */
#define SCORE_MSG_319		339		/* Tabela invalida (0 a 9) */
#define SCORE_MSG_320		340		/* CfgTabOp */
#define SCORE_MSG_321		341		/* Constante */
#define SCORE_MSG_322		342		/* Rampa */
#define SCORE_MSG_323		343		/* -Nao Inicializado- */

#define SCORE_MSG_324		344		/* Formato invalido, use HH:MM */
#define SCORE_MSG_325		345		/* Hora invalida */
#define SCORE_MSG_326		346		/* Tempo maximo, 999 horas */
#define SCORE_MSG_327		347		/* Minuto invalido */
#define SCORE_MSG_328		348		/* Minuto maximo, 59 minutos */
#define SCORE_MSG_329		349		/* VSetPoint invalido */
#define SCORE_MSG_330		350		/* VSetPoint min=0.0 e max=20.0 */
#define SCORE_MSG_331		351		/* VIncr invalido */
#define SCORE_MSG_332		352		/* VIncr min=-999 e max=5000 */
#define SCORE_MSG_333		353		/* Tipo de incremento invalido */
#define SCORE_MSG_334		354		/* Duracao do incremento invalida */
#define SCORE_MSG_335		355		/* Nao existe cuba(s) selecionada(s), configuracao abortada */
#define SCORE_MSG_336		356		/* Cuba */
#define SCORE_MSG_337		357		/* CUBA */
#define SCORE_MSG_338		358		/* LINHA */
#define SCORE_MSG_339		359		/* ALARME */
#define SCORE_MSG_340		360		/* Falha na atualizacao dos arquivos das tabelas! */
#define SCORE_MSG_341		361		/* Falha na atualizacao dos arquivos historicos! */
#define SCORE_MSG_342		362		/* Falha na atualizacao dos arquivos de eventos! */
#define SCORE_MSG_343		363		/* Falha na atualizacao dos arquivos de log! */
#define SCORE_MSG_344		364		/* Falha na atualizacao dos arquivos auxiliares de log! */
#define SCORE_MSG_345		365		/* Atualizando arquivos das tabelas */
#define SCORE_MSG_346		366		/* Atualizando arquivos historicos diarios */
#define SCORE_MSG_347		367		/* Atualizando arquivos de eventos */
#define SCORE_MSG_348		368		/* Atualizando arquivos de log */
#define SCORE_MSG_349		369		/* Atualizando arquivos auxiliares de log */
#define SCORE_MSG_350		370		/* Estado da cuba alterado */
#define SCORE_MSG_351		371		/* Instalando arquivos lidos do principal */
#define SCORE_MSG_352		372		/* Salvando arquivos anteriores em diretorios backup */
#define SCORE_MSG_353		373		/* Estado da cuba invalido */
#define SCORE_MSG_354		374		/* Principal esta ativado mas rede nao esta funcionando! */
#define SCORE_MSG_355		375		/* DESATIVANDO HOT STANDBY... */
#define SCORE_MSG_356		376		/* Nao existe cuba selecionada, Operacao abortada */
#define SCORE_MSG_357		377		/* HOT STANDBY - AGUARDE INICIALIZACAO! */
#define SCORE_MSG_358		378		/* Falha na sinalizacao de partida ao principal! */
#define SCORE_MSG_359		379		/* Normal */
#define SCORE_MSG_360		380		/* Partido */
#define SCORE_MSG_361		381		/* Ligado */
#define SCORE_MSG_362		382		/* Desligado */
#define SCORE_MSG_363		383		/* Estado da cuba nao selecionado */
#define SCORE_MSG_364		384		/* OpEstCub */
#define SCORE_MSG_365		385		/* Terminal */
#define SCORE_MSG_366		386		/* SOLICITACAO DE TRANSFERENCIA! */
#define SCORE_MSG_367		387		/* Consulta do reserva, falha na rede! */
#define SCORE_MSG_368		388		/* Operacao de incremento efetuada */
#define SCORE_MSG_369		389		/* Ativar */
#define SCORE_MSG_370		390		/* Desativar */
#define SCORE_MSG_371		391		/* Operacao de incremento nao selecionada */
#define SCORE_MSG_372		392		/* TIMEOUT NA ESPERA DE ATIVACAO! */
#define SCORE_MSG_373		393		/* Tipo de incremento invalido */
#define SCORE_MSG_374		394		/* MORTE DA TAREFA RESIDENTE %s! */
#define SCORE_MSG_375		395		/* Tensao inicial de incremento invalida */
#define SCORE_MSG_376		396		/* %s->Numero de Grupos = 0 */
#define SCORE_MSG_377		397		/* Falha na sinalizacao do Reserva! */
#define SCORE_MSG_378		398		/* DESATIVANDO SISTEMA SCORE! */
#define SCORE_MSG_379		399		/* SCORE DESATIVADO! */
#define SCORE_MSG_380		400		/* Tensao de incremento cuba %d fora dos limites */
#define SCORE_MSG_381		401		/* Const */
#define SCORE_MSG_382		402		/* Rampa */
#define SCORE_MSG_383		403		/* HOT STANDBY NAO ESTA' ATIVADO! */
#define SCORE_MSG_384		404		/* OpIncOpe */
#define SCORE_MSG_385		405		/* Solicitacao de transferencia! Origem=%d */
#define SCORE_MSG_386		406		/* Ativa */
#define SCORE_MSG_387		407		/* Tratamento de ruido inibido temporariamente */
#define SCORE_MSG_388		408		/* Constante */
#define SCORE_MSG_389		409		/* Principal INATIVO! Comandada sua desativacao! */
#define SCORE_MSG_390		410		/* Ativando Score por timeout na espera de ativacao! */
#define SCORE_MSG_391		411		/* Timeout sinalizacao via Rede! Principal ativo via serial! */
#define SCORE_MSG_392		412		/* Mensagem invalida */
#define SCORE_MSG_393		413		/* Operacao de incremento invalida */
#define SCORE_MSG_394		414		/* Tratamento por troca de pinos desabilitado - Cuba %d */
#define SCORE_MSG_395		415		/* OpITroPi */
#define SCORE_MSG_396		416		/* Corrida sinalizada */
#define SCORE_MSG_397		417		/* Cuba %d em efeito anodico */
#define SCORE_MSG_398		418		/* OpCorIni */
#define SCORE_MSG_399		419		/* Sinaliza */
#define SCORE_MSG_400		420		/* Quebrada sinalizada */
#define SCORE_MSG_401		421		/* Hot Standby ativo! */
#define SCORE_MSG_402		422		/* Aguarde */
#define SCORE_MSG_403		423		/* OpQueIni */
#define SCORE_MSG_404		424		/* Tempo invalido (min=%d max=%d minutos) */
#define SCORE_MSG_405		425		/* OpRuiIni */
#define SCORE_MSG_406		426		/* Filtro invalido */
#define SCORE_MSG_407		427		/* Filtro nao especificado */
#define SCORE_MSG_408		428		/*  Esc-Abandona  F1-Ajuda  F10-Confirma  */
#define SCORE_MSG_409		429		/* Abandonar a operacao [S/N] ?  */
#define SCORE_MSG_410		430		/* s */ /* resposta positiva (sim) */
#define SCORE_MSG_411		431		/* n */ /* resposta negativa (nao) */
#define SCORE_MSG_412		432		/* Confirma saida [S/N]?  */
#define SCORE_MSG_413		433		/* Opcao nao disponivel */
#define SCORE_MSG_414		434		/* Identificacao */
#define SCORE_MSG_415		435		/* Senha */
#define SCORE_MSG_416		436		/* Lampada de efeito anodico desligada */
#define SCORE_MSG_417		437		/* Modo operacao alterado */
#define SCORE_MSG_418		438		/* Modo operacao invalido */
#define SCORE_MSG_419		439		/* Modo de operacao nao selecionado */
#define SCORE_MSG_420		440		/* OpAutMan */
#define SCORE_MSG_421		441		/* Manual */ /* tamanho limitado */
#define SCORE_MSG_422		442		/* Automat */ /* tamanho limitado */
#define SCORE_MSG_423		443		/* Automatico */
#define SCORE_MSG_424		444		/* Manual */
#define SCORE_MSG_425		445		/* Tempo */
#define SCORE_MSG_426		446		/* Resistencia */
#define SCORE_MSG_427		447		/* Movimentacao de anodo efetuada */
#define SCORE_MSG_428		448		/* Sentido movimentacao invalido */
#define SCORE_MSG_429		449		/* Resistencia de movimentacao nao selecionada */
#define SCORE_MSG_430		450		/* Padrao de movimentacao nao selecionado */
#define SCORE_MSG_431		451		/* Duracao movimento para cima da cuba %d fora do limite */
#define SCORE_MSG_432		452		/* Duracao movimento para baixo da cuba %d fora do limite */
#define SCORE_MSG_433		453		/* Cuba %d em modo Manual-Local */
#define SCORE_MSG_434		454		/* Cuba %d em modo automatico */
#define SCORE_MSG_435		455		/* Resistencia de movimentacao invalida */
#define SCORE_MSG_436		456		/* OpMovAno */
#define SCORE_MSG_437		457		/* Subiu */
#define SCORE_MSG_438		458		/* Desceu */
#define SCORE_MSG_439		459		/* Leitura desativada */
#define SCORE_MSG_440		460		/* %s->Grupo %d: maximo de cubas: %d */
#define SCORE_MSG_441		461		/* OpLeiDes */
#define SCORE_MSG_442		462		/* %s->Grupo %d: Cuba %s invalida */
#define SCORE_MSG_443		463		/* %s->Numero de Grupos > %d */
#define SCORE_MSG_444		464		/* Operacao executada */
#define SCORE_MSG_445		465		/* RecTodos */
#define SCORE_MSG_446		466		/* Tabela de operacao desabilitada - cuba %d */
#define SCORE_MSG_447		467		/* Tabela de operacao inativa - cuba %d */
#define SCORE_MSG_448		468		/* OpTabOpe */
#define SCORE_MSG_449		469		/* Relatorio Instantaneo Cubas */
#define SCORE_MSG_450		470		/* Corrente Primaria */
#define SCORE_MSG_451		471		/* Corrente Secundaria */
#define SCORE_MSG_452		472		/* Tensao de Linha */
#define SCORE_MSG_453		473		/* Diferenca Corrente */
#define SCORE_MSG_454		474		/* KA */
#define SCORE_MSG_455		475		/* V */
#define SCORE_MSG_456		476		/* VSetP[V] */
#define SCORE_MSG_457		477		/* VInst[V] */

#define SCORE_MSG_458		478		/* LIG  */
#define SCORE_MSG_459		479		/* DESL */
#define SCORE_MSG_460		480		/* PART */
#define SCORE_MSG_461		481		/* NORM */
#define SCORE_MSG_462		482		/* ERRO */
#define SCORE_MSG_463		483		/* Arquivo          : */
#define SCORE_MSG_464		484		/* Cuba             : */
#define SCORE_MSG_465		485		/* Variaveis Logadas: */
#define SCORE_MSG_466   	486		/* Tipo   : */
#define SCORE_MSG_467   	487		/* Atraso : */
#define SCORE_MSG_468  	    488		/* Trigger: */
#define SCORE_MSG_469  	    489		/* Compara: */
#define SCORE_MSG_470  	    490		/* Oper   : */
#define SCORE_MSG_471  	    491		/* Data de Criacao: */
#define SCORE_MSG_472  	    492		/* Duracao        : */
#define SCORE_MSG_473  	    493		/* Status */
#define SCORE_MSG_474  	    494		/*   Sair   */

#define SCORE_MSG_475  	    495		/* Relatorio do Estado das Redes */
#define SCORE_MSG_476  	    496		/* Nodo: */
#define SCORE_MSG_477  	    497		/* SubRede %d */
#define SCORE_MSG_478  	    498		/* Regulacao */
#define SCORE_MSG_479  	    499		/* Regulacao%02d */
#define SCORE_MSG_480  	    500		/* Ativo */
#define SCORE_MSG_481  	    501		/* Inativo */
#define SCORE_MSG_482  	    502		/* Nome */
#define SCORE_MSG_483  	    503		/* Duracao (HHH:MM) */
#define SCORE_MSG_484  	    504		/* Cuba */
#define SCORE_MSG_485  	    505		/* Variaveis Selecionadas */
#define SCORE_MSG_486  	    506		/* Grupos de Variaveis */
#define SCORE_MSG_487  	    507		/* Tipo do Log */
#define SCORE_MSG_488  	    508		/* Log 2.0 (min) */
#define SCORE_MSG_489  	    509		/* Log 0.5 (seg) */
#define SCORE_MSG_490  	    510		/* Teclado */
#define SCORE_MSG_491  	    511		/* Atraso */
#define SCORE_MSG_492  	    512		/* Trigger */
#define SCORE_MSG_493  	    513		/* Compara */
#define SCORE_MSG_494  	    514		/* Criacao */
#define SCORE_MSG_495  	    515		/* Arquivo        : */
#define SCORE_MSG_496  	    516		/* Cuba           : */
#define SCORE_MSG_497  	    517		/* Data de Criacao: */
#define SCORE_MSG_498  	    518		/* Duracao        : */
#define SCORE_MSG_499  	    519		/* Cor Grid: */
#define SCORE_MSG_500  	    520		/* Cor Fundo: */
#define SCORE_MSG_501  	    521		/* Variaveis Logadas: */
#define SCORE_MSG_502  	    522		/* G R A F I C O */
#define SCORE_MSG_503  	    523		/* DELECAO */
#define SCORE_MSG_504  	    524		/*  Deleta  */
#define SCORE_MSG_505  	    525		/* Desativa */
#define SCORE_MSG_506  	    526		/* Data de Criacao  : */
#define SCORE_MSG_507 	    527		/* Duracao          : */
#define SCORE_MSG_508 	    528		/* Periodo Relatorio: */
#define SCORE_MSG_509	    529		/* Data Inicio */
#define SCORE_MSG_510	    530		/* Data Fim */
#define SCORE_MSG_511	    531		/* Num. Div */
#define SCORE_MSG_512	    532		/* Fat. Compact */
#define SCORE_MSG_513	    533		/* Metodo */
#define SCORE_MSG_514    	534		/* Grafico - Impressora */
#define SCORE_MSG_515    	535		/* Dump - Impressora */
#define SCORE_MSG_516    	536		/*  Salvar  */
#define SCORE_MSG_517    	537		/* Grupo de Variaveis */
#define SCORE_MSG_518    	538		/* Limites */
#define SCORE_MSG_519    	539		/* Logs Ativados */
#define SCORE_MSG_520    	540		/* Arquivo: */
#define SCORE_MSG_521    	541		/* Cuba: */
#define SCORE_MSG_522    	542		/* Data de Criacao: */
#define SCORE_MSG_523    	543		/*  Duracao: */
#define SCORE_MSG_524    	544		/* Sair */
#define SCORE_MSG_525    	545		/* D U M P */
#define SCORE_MSG_526    	546		/* Media */
#define SCORE_MSG_527    	547		/* Maior */
#define SCORE_MSG_528    	548		/* Ativos  */
#define SCORE_MSG_529    	549		/* Status */
#define SCORE_MSG_530    	550		/*  Cria  */
#define SCORE_MSG_531    	551		/* Deleta */
#define SCORE_MSG_532    	552		/*  Dump  */
#define SCORE_MSG_533    	553		/* Grafico  */
#define SCORE_MSG_534    	554		/*  Sair  */
#define SCORE_MSG_535    	555		/* Cores */
#define SCORE_MSG_536    	556		/*   Sair   */
#define SCORE_MSG_537    	557		/* Eventos: */
#define SCORE_MSG_538    	558		/* Amostragens */
#define SCORE_MSG_539    	559		/* Fator Compactacao */
#define SCORE_MSG_540    	560		/* Cuba */
#define SCORE_MSG_541    	561		/* Grafico */
#define SCORE_MSG_542    	562		/* UnZoom */
#define SCORE_MSG_543    	563		/* Zoom */
#define SCORE_MSG_544    	564		/* Media */
#define SCORE_MSG_545    	565		/* Maior */
#define SCORE_MSG_546    	566		/* Tela;Impressora */
#define SCORE_MSG_547    	567		/* Tela;Impressora;Limites */
#define SCORE_MSG_548    	568		/* Marca Inicio;Marca Fim;Desmarca;Zoom 1;Zoom 2;Zoom 5;Zoom 10;Zoom 20 */

#define SCORE_MSG_549    	569		/* CUBA  */
#define SCORE_MSG_550    	570		/* Retrocede */
#define SCORE_MSG_551    	571		/* Prox.Cuba */
#define SCORE_MSG_552    	572		/* Cuba Ant. */
#define SCORE_MSG_553    	573		/*  Avanca   */
#define SCORE_MSG_554    	574		/* Log */
#define SCORE_MSG_555    	575		/* Cursor */
#define SCORE_MSG_556    	576		/*  Sair   */
#define SCORE_MSG_557    	577		/* Prox. Rec. */
#define SCORE_MSG_558    	578		/* Rec.Alarme */
#define SCORE_MSG_559    	579		/* CONTROLE */
#define SCORE_MSG_560    	580		/* RUIDO */
#define SCORE_MSG_561    	581		/* STATUS */
#define SCORE_MSG_562    	582		/* EVENTOS */
#define SCORE_MSG_563    	583		/* Modo Log */
#define SCORE_MSG_564    	584		/* Modo Cursor */
#define SCORE_MSG_565    	585		/* Nome Arquivo: */
#define SCORE_MSG_566    	586		/* Leitura;Gravacao;Delecao */
#define SCORE_MSG_567    	587		/* RecTod */
#define SCORE_MSG_568    	588		/* Grafico */
#define SCORE_MSG_569    	589		/* Sair  */
#define SCORE_MSG_570    	590		/* Grafico 1;Grafico 2;Grafico 3;Normal;Ajuda Alarmes */
#define SCORE_MSG_571    	591		/* Diario */
#define SCORE_MSG_572    	592		/* Dump(Tela) */
#define SCORE_MSG_573    	593		/* Dump(Impressora) */
#define SCORE_MSG_574    	594		/* Grafico(Tela) */
#define SCORE_MSG_575    	595		/* Grafico(Impressora) */
#define SCORE_MSG_576    	596		/* Variavel */

#define SCORE_MSG_577    	597		/* Dom */
#define SCORE_MSG_578    	598		/* Seg */
#define SCORE_MSG_579    	599		/* Ter */
#define SCORE_MSG_580    	600		/* Qua */
#define SCORE_MSG_581    	601 	/* Qui */
#define SCORE_MSG_582    	602		/* Sex */
#define SCORE_MSG_583    	603		/* Sab */
#define SCORE_MSG_584    	604		/* cuba invalida na linha exclusao */

#define SCORE_MSG_585    	605		/* Pag. */
#define SCORE_MSG_586    	606		/* CONFIGURACAO PARAMETROS CUBA */
#define SCORE_MSG_587    	607		/* CONFIGURACAO PARAMETROS LINHA */
#define SCORE_MSG_588    	608		/* Data invalida linha de exclusao */
#define SCORE_MSG_589    	609		/* Turno invalido */
#define SCORE_MSG_590    	610		/* Variavel: %s offsetTab retornou erro! */
#define SCORE_MSG_591		611		/* Ter-Cima */
#define SCORE_MSG_592		612		/* Ter-Baix */
#define SCORE_MSG_593    	613		/* livre */
#define SCORE_MSG_594    	614		/* Hora final invalida */
#define SCORE_MSG_595    	615		/* Hora inicial igual hora final */
#define SCORE_MSG_596    	616		/* Hora inicial maior que hora final */
#define SCORE_MSG_597    	617		/* Hora inicial invalida */
#define SCORE_MSG_598    	618		/* Deleta Variavel */
#define SCORE_MSG_599		619		/* Sair;Desativa;Deleta */

/* 80 strings - RelTela1 */
#define SCORE_MSG_600		620		/*  */

/* 80 strings - RelTela2 */
#define SCORE_MSG_680		700 	/*  */

/* 80 strings - RelTela3 */
#define SCORE_MSG_760		780 	/*  */

/* 80 strings - RelTela4 */
#define SCORE_MSG_840		860		/*  */

/* 80 strings - RelTela5 */
#define SCORE_MSG_920		940		/*  */

/* 80 strings - RelGraf1 */
#define SCORE_MSG_1000		1020   	/*  */

/* 80 strings - RelGraf2 */
#define SCORE_MSG_1080		1100    /*  */

/* 80 strings - Operacao1 */
#define SCORE_MSG_1160		1180	/*  */

/* 80 strings - Operacao2 */
#define SCORE_MSG_1240		1260	/*  */

/* 80 strings - Operacao3 */
#define SCORE_MSG_1320		1340	/*  */

/* 80 strings - Operacao4 */
#define SCORE_MSG_1400		1420	/*  */

/* 80 strings - Configura1 */
#define SCORE_MSG_1480  	1500    /*  */

/* 80 strings - Configura2 */
#define SCORE_MSG_1560  	1580    /*  */

/* 80 strings - Configura3 */
#define SCORE_MSG_1640		1660	/*  */

#define	SCORE_MSG_1720		1740	/* Selecao/Grupo  */
#define SCORE_MSG_1721		1741	/* Relatorio/Tela */
#define SCORE_MSG_1722		1742	/* Rel./Graficos */
#define SCORE_MSG_1723		1743	/* Operacao  */
#define SCORE_MSG_1724		1744	/* Configuracao  */
#define SCORE_MSG_1725		1745	/*  Sair  */

#define SCORE_MSG_1726		1746	/* Avanca  */
#define SCORE_MSG_1727		1747	/* Retrocede */
#define SCORE_MSG_1728		1748	/* Inicio  */
#define SCORE_MSG_1729		1749	/*   Fim   */
#define SCORE_MSG_1730		1750	/*  Ajuda  */
#define SCORE_MSG_1731		1751	/* Exporta */
#define SCORE_MSG_1732		1752	/* Imprimir  */
#define SCORE_MSG_1733		1753	/*  Sair    */

#define SCORE_MSG_1734		1754	/* Impressora */
#define SCORE_MSG_1735		1755	/* Login Global */
#define SCORE_MSG_1736		1756	/* Tempo Inatividade (min) */
#define SCORE_MSG_1737		1757	/* Memoria */
#define SCORE_MSG_1738		1758	/* LEITURA   */
#define SCORE_MSG_1739		1759	/* GRAVACAO  */
#define SCORE_MSG_1740		1760	/*   ATUAL   */
#define SCORE_MSG_1741		1761	/*  AVANCA   */
#define SCORE_MSG_1742		1762	/* RETROCEDE */
#define SCORE_MSG_1743		1763	/*  TODAS CUBAS   */
#define SCORE_MSG_1744		1764	/* SEL. ESPECIAL  */
#define SCORE_MSG_1745		1765	/* ENTRADA CUBAS ESPECIAIS */
#define SCORE_MSG_1746		1766	/* ENTRADA CUBAS EXCLUIDAS */
#define SCORE_MSG_1747		1767	/*    PRE-SELECOES DO SISTEMA     */
#define SCORE_MSG_1748		1768	/* Entrada Identificacao e Senha */

#define SCORE_MSG_1749		1769	/* BackSpace */
#define SCORE_MSG_1750		1770	/*  Limpa   */
#define SCORE_MSG_1751		1771	/* CapsLock */

#define SCORE_MSG_1752		1772	/* Reconhece  */
#define SCORE_MSG_1753		1773	/* Rec. Todos */
#define SCORE_MSG_1754		1774	/*  Hardcopy  */
#define SCORE_MSG_1755		1775	/* Canc. Imp. */

#define SCORE_MSG_1756		1776	/*  Avanca   */
#define SCORE_MSG_1757		1777	/* Retrocede */
#define SCORE_MSG_1758		1778	/*   Ajuda   */
#define SCORE_MSG_1759		1779	/*   Grava   */
#define SCORE_MSG_1760		1780	/*    Sair   */

#define SCORE_MSG_1761		1781	/* Prox.Cuba */
#define SCORE_MSG_1762		1782	/* Cuba Ant. */
#define SCORE_MSG_1763		1783	/*  Avanca   */
#define SCORE_MSG_1764		1784	/* Retrocede */
#define SCORE_MSG_1765		1785	/* Ajuda */
#define SCORE_MSG_1766		1786	/* Grava  */
#define SCORE_MSG_1767		1787	/* GravaTodos */
#define SCORE_MSG_1768		1788	/*  Sair  */

#define SCORE_MSG_1769		1789	/* %s->Parametro Lista Texto|Tag %d */

#define SCORE_MSG_1770		1790	/* CONFIGURACAO DE ALARMES */
#define SCORE_MSG_1771		1791	/* CUBA  */
#define SCORE_MSG_1772		1792	/* Cor Normal */
#define SCORE_MSG_1773		1793	/* Estado Normal Nao Reconhecido */

#define SCORE_MSG_1774		1794	/* Log Cuba Gravacao */
#define SCORE_MSG_1775		1795	/* Novo;Gravar;Sair */
#define SCORE_MSG_1776		1796	/* Cancelar;Substituir */

#define SCORE_MSG_1777		1797	/* Cor do nivel de prioridade */
#define SCORE_MSG_1778 		1798	/* VARIAVEIS DE ALARME */
#define SCORE_MSG_1779 		1799	/* Numero */
#define SCORE_MSG_1780		1800	/* Nome */
#define SCORE_MSG_1781		1801	/* Valor normal */
#define SCORE_MSG_1782		1802	/* Lista  variaveis  */
#define SCORE_MSG_1783		1803	/* Cancela variaveis */
#define SCORE_MSG_1784		1804	/* NIVEIS DE ALARME */
#define SCORE_MSG_1785		1805	/* Numero */
#define SCORE_MSG_1786		1806	/* Valor */
#define SCORE_MSG_1787		1807	/* Prioridade */

#define SCORE_MSG_1788		1808	/* Gravacao OK ! */
#define SCORE_MSG_1789		1809	/* Log Cuba Delecao */
#define SCORE_MSG_1790		1810	/* Log Cuba Leitura */

#define SCORE_MSG_1791		1811	/* Cuba %s invalida ! */
#define SCORE_MSG_1792		1812	/* Numero de Cubas Invalido ! */
#define SCORE_MSG_1793		1813	/* Grafico Indefinido, Assumindo Grafico 1 ! */

#define SCORE_MSG_1794		1814 	/* Variaveis */
#define SCORE_MSG_1795		1815 	/* Lim.Inf. */
#define SCORE_MSG_1796		1816	/* Lim.Sup. */
#define SCORE_MSG_1797		1817	/* Fator  */
#define SCORE_MSG_1798		1818	/* Cor   */
#define SCORE_MSG_1799		1819 	/* GRAFICO 1 */
#define SCORE_MSG_1800		1820	/* GRAFICO 2 */
#define SCORE_MSG_1801		1821	/* GRAFICO 3 */
#define SCORE_MSG_1802		1822	/* Cor da Grade     */
#define SCORE_MSG_1803		1823	/* Cor de Fundo     */

#define SCORE_MSG_1804		1824	/* LI */ // limite inferior
#define SCORE_MSG_1805		1825	/* LS */ // limite inferior
#define SCORE_MSG_1806		1826	/* Relatorio Instantaneo de Linha */
#define SCORE_MSG_1807		1827	/* RecLinha */

#define SCORE_MSG_1808		1828	/* CONFIGURACAO DOS GRAFICOS */
#define SCORE_MSG_1809		1829	/* Abandona */

/*   CfgCadOpera   */
#define SCORE_MSG_1810		1830	/* Abandona */
#define SCORE_MSG_1811		1831	/*  Grava   */

#define SCORE_MSG_1812		1832	/*  Abandona  */
#define SCORE_MSG_1813		1833	/*   Grava    */
#define SCORE_MSG_1814		1834	/*   Exibe Senha   */
#define SCORE_MSG_1815		1835	/*  Cancela   */

#define SCORE_MSG_1816		1836	/* Abandona */

#define SCORE_MSG_1817		1837	/*  Cadastro do Operador  */
#define SCORE_MSG_1818		1838	/* No.             */         
#define SCORE_MSG_1819		1839	/* Nome               */             
#define SCORE_MSG_1820		1840	/* Nivel   */

#define SCORE_MSG_1821		1841	/* Numero    */
#define SCORE_MSG_1822		1842	/* Nome      */
#define SCORE_MSG_1823		1843	/* Nivel     */
#define SCORE_MSG_1824		1844	/* Senha     */
#define SCORE_MSG_1825		1845	/* Senha     */

#define SCORE_MSG_1826		1846	/* Entrada de dados       */
#define SCORE_MSG_1827		1847	/* Exibe Senha            */

/* CfgTabEliEAW */

#define SCORE_MSG_1828		1848	/*  Abandona  */
#define SCORE_MSG_1829		1849	/*   Grava    */

#define SCORE_MSG_1830		1850	/* Passos Para Eliminacao do Efeito Anodico       */
#define SCORE_MSG_1831		1851	/*  Abandona  */
#define SCORE_MSG_1832		1852	/*   Grava    */
#define SCORE_MSG_1833		1853	/*  Entra/Insere  */
#define SCORE_MSG_1834		1854	/*  Cancela   */

#define SCORE_MSG_1835		1855	/* TABELA DE ELIMINACAO DE E.A. */
#define SCORE_MSG_1836		1856	/* Passo */
#define SCORE_MSG_1837		1857	/* Acao */
#define SCORE_MSG_1838		1858	/* Param */
#define SCORE_MSG_1839		1859	/* [seg] */

#define SCORE_MSG_1840		1860	/* Passo */
#define SCORE_MSG_1841 		1861	/* Acao */
#define SCORE_MSG_1842		1862	/* Duracao */
#define SCORE_MSG_1843		1863	/* Descer */
#define SCORE_MSG_1844		1864	/* Subir  */
#define SCORE_MSG_1845		1865	/* Parar  */

/* CfgTabEliEAW */

#define SCORE_MSG_1846		1866	/* Tabela 0 */
#define SCORE_MSG_1847		1867	/* Tabela 1 */
#define SCORE_MSG_1848		1868	/* Tabela 2 */
#define SCORE_MSG_1849		1869	/* Tabela 3 */
#define SCORE_MSG_1850		1870	/* Tabela 4 */
#define SCORE_MSG_1851		1871	/* Rotina 1 */
#define SCORE_MSG_1852		1872	/* Rotina 2 */
#define SCORE_MSG_1853		1873	/* Rotina 3 */
#define SCORE_MSG_1854		1874	/* Rotina 4 */
#define SCORE_MSG_1855		1875	/* Rotina 5 */

/* CfgTabCamW */

#define SCORE_MSG_1856		1876	/* Tabela 0 */
#define SCORE_MSG_1857		1877	/* Tabela 1 */
#define SCORE_MSG_1858		1878	/* Tabela 2 */
#define SCORE_MSG_1859		1879	/* Tabela 3 */
#define SCORE_MSG_1860		1880	/* Tabela 4 */
#define SCORE_MSG_1861		1881	/* Tabela 5 */
#define SCORE_MSG_1862		1882	/* Tabela 6 */
#define SCORE_MSG_1863		1883	/* Tabela 7 */
#define SCORE_MSG_1864		1884	/* Tabela 8 */
#define SCORE_MSG_1865		1885	/* Tabela 9 */

#define SCORE_MSG_1866		1886	/*  Abandona  */
#define SCORE_MSG_1867		1887	/*   Grava    */
#define SCORE_MSG_1868		1888	/*  Imprime   */

#define SCORE_MSG_1869		1889	/* Tabela de Ajuste de Camisa */
#define SCORE_MSG_1870		1890	/* Passo */
#define SCORE_MSG_1871		1891	/* Acao */
#define SCORE_MSG_1872		1892	/* Duracao */
#define SCORE_MSG_1873		1893	/* [hh:mm:ss] */

#define SCORE_MSG_1874		1894	/* Passos de Ajuste de Camisa */
#define SCORE_MSG_1875		1895	/*  Abandona  */
#define SCORE_MSG_1876		1896	/*   Grava    */
#define SCORE_MSG_1877		1897	/*  Entra/Insere  */
#define SCORE_MSG_1878		1898	/*  Cancela   */

#define SCORE_MSG_1879		1899	/* Passo */
#define SCORE_MSG_1880		1900	/* Acao */
#define SCORE_MSG_1881		1901	/* Duracao */

#define SCORE_MSG_1882		1902	/* Descer */
#define SCORE_MSG_1883		1903	/* Subir  */
#define SCORE_MSG_1884		1904	/* Parar  */

/* MascRelMsg */

#define SCORE_MSG_1885		1905	/*  Avanca   */
#define SCORE_MSG_1886		1906	/* Retrocede */
#define SCORE_MSG_1887		1907	/*  Inicio   */
#define SCORE_MSG_1888		1908	/*    Fim    */
#define SCORE_MSG_1889		1909	/* Abandona  */

/* MascRelDina */

#define SCORE_MSG_1890		1910	/*  Avanca   */
#define SCORE_MSG_1891		1911	/* Retrocede */
#define SCORE_MSG_1892		1912	/* Abandona  */

/*               */

#define SCORE_MSG_1893		1913	/* Tabela de Ajuste Vazia */

#define SCORE_MSG_1894		1914	/* Escolha Impressora:           */
#define SCORE_MSG_1895		1915	/* Escolha Formato:      */
#define SCORE_MSG_1896		1916	/* Tabela de Eliminacao Vazia */
#define SCORE_MSG_1897		1917	/* Tabela de Incrementos Vazia */
#define SCORE_MSG_1898		1918	/* Soprar */
#define SCORE_MSG_1899		1919	/* LaserJet  */
#define SCORE_MSG_1900		1920	/* Matricial */
#define SCORE_MSG_1901		1921	/* InkJet    */

/*  CfgTabIncOpe */


#define SCORE_MSG_1902		1922	/* Tabela 0 */
#define SCORE_MSG_1903		1923	/* Tabela 1 */
#define SCORE_MSG_1904		1924	/* Tabela 2 */
#define SCORE_MSG_1905		1925	/* Tabela 3 */
#define SCORE_MSG_1906		1926	/* Tabela 4 */
#define SCORE_MSG_1907		1927	/* Tabela 5 */
#define SCORE_MSG_1908		1928	/* Tabela 6 */
#define SCORE_MSG_1909		1929	/* Tabela 7 */
#define SCORE_MSG_1910		1930	/* Tabela 8 */
#define SCORE_MSG_1911		1931	/* Tabela 9 */

#define SCORE_MSG_1912		1932	/*  Abandona  */
#define SCORE_MSG_1913		1933	/*   Grava    */
#define SCORE_MSG_1914		1934	/*  Imprime   */

#define SCORE_MSG_1915		1935	/* Passos do Incremento de Operacao              */
#define SCORE_MSG_1916		1936	/*  Abandona  */
#define SCORE_MSG_1917		1937 	/*   Grava    */
#define SCORE_MSG_1918		1938	/*  Entra/Insere  */
#define SCORE_MSG_1919		1939	/*  Cancela   */

#define SCORE_MSG_1920		1940	/* Tabela de Incrementos de Operacao              */
#define SCORE_MSG_1921		1941	/* Passo */
#define SCORE_MSG_1922		1942	/* SetP  */
#define SCORE_MSG_1923		1943	/* Incr. */
#define SCORE_MSG_1924		1944	/* Tipo */
#define SCORE_MSG_1925		1945	/* Hora */

#define SCORE_MSG_1926		1946	/* [V] */
#define SCORE_MSG_1927		1947	/* [mV] */
#define SCORE_MSG_1928		1948	/* [hh:mm] */

#define SCORE_MSG_1929		1949	/* Passo 1  */
#define SCORE_MSG_1930		1950	/* SetPoint */
#define SCORE_MSG_1931		1951	/* Incr Ope */
#define SCORE_MSG_1932		1952	/* Tipo     */
#define SCORE_MSG_1933		1953	/* Hora     */
#define SCORE_MSG_1934		1954	/* Const.   */
#define SCORE_MSG_1935		1955	/* Rampa    */ 

#define SCORE_MSG_1936		1956	/* Confirma Gravacao da Memoria %d ? */ 
#define SCORE_MSG_1937		1957	/* Confirma;Confirma/Troca Nome;Abandona */ 
#define SCORE_MSG_1938		1958	/* Nome Memoria */ 

/* MascHelp */

#define SCORE_MSG_1939		1959	/*  Avanca   */ 
#define SCORE_MSG_1940		1960	/* Retrocede */ 
#define SCORE_MSG_1941		1961	/*  Inicio   */ 
#define SCORE_MSG_1942		1962	/*    Fim    */ 
#define SCORE_MSG_1943		1963	/* Abandona  */ 

#define SCORE_MSG_1944		1964	/* Exportacao de dados  */ 
#define SCORE_MSG_1945		1965	/* Confirma */ 
#define SCORE_MSG_1946		1966	/* Abandona */ 
#define SCORE_MSG_1947		1967	/* C */ 
#define SCORE_MSG_1948		1968	/* R */ 


#define SCORE_MSG_1949		1969	/* Destino            */ 
#define SCORE_MSG_1950		1970	/* Delimitador */ 
#define SCORE_MSG_1951		1971	/* Cores */ 


/* origem da mudanca do estado de alimentacao */

#define SCORE_MSG_1952		1972	/* Externa */ 
#define SCORE_MSG_1953		1973	/* Operador */ 
#define SCORE_MSG_1954		1974	/* Invalida */ 

/* nomes dos estados do algoritmo de alimentacao */
#define SCORE_MSG_1955		1975	/* Padrao */ 
#define SCORE_MSG_1956		1976	/* Susp EA */ 

#define SCORE_MSG_1957		1977	/* Ev */ 
#define SCORE_MSG_1958		1978	/* Parametros de Configuracao - Cuba %3d */ 
#define SCORE_MSG_1959		1979	/* Unidade */ 

/* nome e cabecalhos do relatorio instantaneo de alimentacao (barra lateral) */
#define SCORE_MSG_1960      1980    /* RELATORIO INSTANTANEO DE ALIMENTACAO - BARRA LATERAL */
#define SCORE_MSG_1961      1981    /*       ------Status------  ----Estado de Alimentacao--- */
#define SCORE_MSG_1962      1982    /* Cuba  Operacao  Aliment.  Identidade Duracao Num.Queb. */

/* erros no program de operacao de mudanca de alimentacao */
#define SCORE_MSG_1963		1983	/* Modo de alimentacao nao selecionado */
#define SCORE_MSG_1964		1984	/* Tempo de alimentacao suspensa invalido */

#define SCORE_MSG_1965		1985	/* Cuba  VPlaca  VInst */
#define SCORE_MSG_1966		1986	/* G1  */
#define SCORE_MSG_1967		1987	/* G2  */
#define SCORE_MSG_1968		1988	/* G3  */
#define SCORE_MSG_1969		1989	/* G4  */
#define SCORE_MSG_1970		1990	/* G5  */
#define SCORE_MSG_1971		1991	/* G6  */
#define SCORE_MSG_1972		1992	/* G7  */
#define SCORE_MSG_1973		1993	/* G8  */

#define SCORE_MSG_1974		1994	/* Interface A */
#define SCORE_MSG_1975		1995	/* Interface B */
#define SCORE_MSG_1976		1996	/* Selecione Interface (A ou B): */
#define SCORE_MSG_1977		1997	/* Posicao (B,C,D), 0 = Menu Principal: */
#define SCORE_MSG_1978		1998	/* Posicao (B,C), 0 = Menu Principal: */
#define SCORE_MSG_1979		1999	/* Conversor (a-h), 0 = Menu Principal, 1 = Nova Posicao: */
#define SCORE_MSG_1980		2000	/* ROMPIDA */
#define SCORE_MSG_1981		2001	/* CONSERTO */
#define SCORE_MSG_1982		2002	/* MOVEFAIL */

#define SCORE_MSG_1983		2003	/* Ajuda Alarmes */
#define SCORE_MSG_1984		2004	/* Soprar */
#define SCORE_MSG_1985		2005	/* Operation NOT Allowed: Manual-Local Feeding Selected */
#define SCORE_MSG_1986		2006	/* Operation NOT Allowed: Manual-Remote Feeding Requested */

#define SCORE_MSG_1987		2007	/* Tabela   */
#define SCORE_MSG_1988		2008	/* LinDesab */
#define SCORE_MSG_1989		2009	/* AlimMan  */
#define SCORE_MSG_1990		2010	/* EstDifNo */
#define SCORE_MSG_1991		2011	/* RemFRede */
#define SCORE_MSG_1992		2012	/* Fim EA   */
#define SCORE_MSG_1993		2013	/* TabDesab */
#define SCORE_MSG_1994		2014	/* Invalido */
#define SCORE_MSG_1995		2015	/* ForLeit  */
#define SCORE_MSG_1996		2016	/* FimTab   */
#define SCORE_MSG_1997		2017	/* TabCanc  */
#define SCORE_MSG_1998		2018	/* FalhTab  */

#define SCORE_MSG_1999		2019	/* Esperar      */
#define SCORE_MSG_2000		2020	/* Sub-Rotina_1 */
#define SCORE_MSG_2001		2021	/* Sub-Rotina_2 */
#define SCORE_MSG_2002		2022	/* Sub-Rotina_3 */
#define SCORE_MSG_2003		2023	/* Sub-Rotina_4 */
#define SCORE_MSG_2004		2024	/* Sub-Rotina_5 */
#define SCORE_MSG_2005		2025	/* Quebrada Ext */
#define SCORE_MSG_2006		2026	/* Quebrada Int */
#define SCORE_MSG_2007		2027	/* Tocar Sirene */
#define SCORE_MSG_2008		2028	/* Lista Acoes  */
#define SCORE_MSG_2009		2029	/* Sub-Rotinas  */
#define SCORE_MSG_2010		2030	/* T%dP%02d    */ 
#define SCORE_MSG_2011		2031	/* T%dP%02dP%02d */ 

#define SCORE_MSG_2012		2032	/* Interno */
#define SCORE_MSG_2013		2033	/* Externo */
#define SCORE_MSG_2014		2034	/* Fim Tabela %d inesperado - Cuba %d */
#define SCORE_MSG_2015		2035	/* Partida */
#define SCORE_MSG_2016		2036	/* Cuba - Cores / Prioridades */

#define SCORE_MSG_2017		2037	/* Alteracao do Relogio em andamento... */
#define SCORE_MSG_2018		2038	/* Alteracao do Relogio ja esta em Andamento ! */
#define SCORE_MSG_2019		2039	/* Minutos %s invalido; faixa: [-60,60] */

#define SCORE_MSG_2020		2040	/* CfgHora */

#define SCORE_MSG_2021		2041	/* Posicao (B,C,D,E), 0 = Menu principal */
#define SCORE_MSG_2022		2042	/* Grava parametros dos conversores na EEPROM */

/* mais um nome de estado de alimentacao */
#define SCORE_MSG_2023		2043	/* Excecao */

#define SCORE_MSG_2024		2044	/* Modo de alimentacao invalido [%d]! */
#define SCORE_MSG_2025		2045	/* Falha de alimentacao */

/* nome e cabecalhos do relatorio instantaneo de alimentacao (point feeder) */
#define SCORE_MSG_2026      2046    /* RELATORIO INSTANTANEO DE ALIMENTACAO - POINT FEEDER */
#define SCORE_MSG_2027      2047    /*      ------Status----- ------Algoritmo------ --------Estado--------- */
#define SCORE_MSG_2028      2048    /* Cuba Operacao Aliment. -Ident.- -Dur- --Kg-- Ident -Dur- --Kg- -Bal- EfCor */
#define SCORE_MSG_2029		2049	/* Reducao */
#define SCORE_MSG_2030		2050	/* %s->Tarefa Filha %s Travou ou Morreu ! Executando shutdown... */
#define SCORE_MSG_2031		2051	/* Datas Excluidas */
#define SCORE_MSG_2032		2052	/* Compacta */ /* grafico de cubas */
#define SCORE_MSG_2033		2053	/* Grafico 1;Grafico 2;Grafico 3;Grafico 4;Grafico 5;Grafico 6;Todos;Nenhum */
#define SCORE_MSG_2034		2054	/* Atualiza */
#define SCORE_MSG_2035		2055	/* Aquisicao a cada */
#define SCORE_MSG_2036		2056	/* Duracao Max. [hora(s)] */
#define SCORE_MSG_2037		2057	/* Min */ /* minutos */
#define SCORE_MSG_2038		2058	/* Seg */ /* segundos */
#define SCORE_MSG_2039		2059	/* ENTRADA DIAS EXCLUIDOS */
#define SCORE_MSG_2040		2060	/* Linha - Cores / Prioridades */
#define SCORE_MSG_2041		2061	/* ESTATISTICA REDE ECHELON */
#define SCORE_MSG_2042		2062	/* Confirma sair do Sistema Score ? */

/* -- Alteracao - Inicio - Robson - 02/02/2000 -- */
#define SCORE_MSG_2043		2063	/* Falha particionamento arquivo exportado */
#define SCORE_MSG_2044		2064	/* Falha transferencia arquivo exportado */
#define SCORE_MSG_2045		2065	/* Falha transferencia */
#define SCORE_MSG_2046		2066	/* Arquivos Exportados */
#define SCORE_MSG_2047		2067	/* Processando a exportacao ... */
/* -- Alteracao - Fim - Robson - 02/02/2000 -- */

#define SCORE_MSG_2048		2068	/* EVENTO */
#define SCORE_MSG_2049		2069	/* Eventos Score */
#define SCORE_MSG_2050		2070	/* Eventos Cliente */
#define SCORE_MSG_2051		2071	/* Eventos Gerais */
#define SCORE_MSG_2052		2072	/* Help de Evento */
#define SCORE_MSG_2053		2073	/* Hora Inicial */
#define SCORE_MSG_2054		2074	/* Hora Final */
#define SCORE_MSG_2055		2075	/* CUBA,LINHA */
#define SCORE_MSG_2056      2076    /* Lista Eventos */
#define SCORE_MSG_2057      2077    /* EvTotal,EvSist,EvProc,EvCuba,EvLinha,EvMens */ 
#define SCORE_MSG_2058      2078    /* EvMens */
#define SCORE_MSG_2059      2079    /* Relatorio de Mensagens de Eventos */
#define SCORE_MSG_2060      2080    /* Subir,Descer */
#define SCORE_MSG_2061      2081    /* Sentido */
#define SCORE_MSG_2062      2082    /* Duracao[seg] */
#define SCORE_MSG_2063      2083    /* Movimentacao de Anodo do Forno */
#define SCORE_MSG_2064      2084    /* Modos de Operacao */
#define SCORE_MSG_2065      2085    /* Manual,Automatico */
#define SCORE_MSG_2066      2086    /* Modo */
#define SCORE_MSG_2067      2087    /* Estado */
#define SCORE_MSG_2068      2088    /* Normal,Ligado,Desligado,Partido */
#define SCORE_MSG_2069      2089    /* Estados da Cuba */
#define SCORE_MSG_2070      2090    /* Mudanca de Estados da Cuba */
#define SCORE_MSG_2071      2091    /* Sinalizar Corrida */
#define SCORE_MSG_2072      2092    /* Sinalizacao de Corrida */
#define SCORE_MSG_2073      2093    /* Sinalizar Quebrada */
#define SCORE_MSG_2074      2094    /* Sinalizacao de Quebrada */
#define SCORE_MSG_2075      2095    /* Apaga Lampada de EA */
#define SCORE_MSG_2076      2096    /* Ativa/Desat. Incremento Operacao */
#define SCORE_MSG_2077      2097    /* Ativar,Constante */
#define SCORE_MSG_2078      2098    /* Ativar,Desativar */
#define SCORE_MSG_2079      2099    /* Constante,Rampa */
#define SCORE_MSG_2080      2100    /* Acoes Incrementos */
#define SCORE_MSG_2081      2101    /* Tipos Incrementos */
#define SCORE_MSG_2082      2102    /* Acao,Tipo */
#define SCORE_MSG_2083      2103    /* Tensao Ini[mV] */
#define SCORE_MSG_2084      2104    /* Duracao [hh:mm] */
#define SCORE_MSG_2085      2105    /* 01:00 */
#define SCORE_MSG_2086      2106    /* 50 */
#define SCORE_MSG_2087      2107    /* Operacao de Incremento */
#define SCORE_MSG_2088      2108    /* Ativa/Desat. Incremento Troca de Pinos */
#define SCORE_MSG_2089      2109    /* Acoes Incremento */
#define SCORE_MSG_2090      2110    /* Incremento de Troca de Pinos */
#define SCORE_MSG_2091      2111    /* Origem */
#define SCORE_MSG_2092      2112    /* Destino */
#define SCORE_MSG_2093      2113    /* <ATENCAO: COPIA DE TODAS AS VARIAVEIS> */
#define SCORE_MSG_2094      2114    /* RTU Ativa */
#define SCORE_MSG_2095      2115    /* RTU Inativa */
#define SCORE_MSG_2096      2116    /* RTU Temp. Anormal */
#define SCORE_MSG_2097      2117    /* Clique em qualquer remota para ver sua temperatura atual */
#define SCORE_MSG_2098      2118    /* Temperatura */
#define SCORE_MSG_2099		2119	/* Dados Nao Gravados ! */
#define SCORE_MSG_2100		2120	/* Modulo Historico */
#define SCORE_MSG_2101		2121	/* Dump Tela */
#define SCORE_MSG_2102		2122	/* Dump Imp. */
#define SCORE_MSG_2103		2123	/* Graf.Tela */
#define SCORE_MSG_2104		2124	/* Graf.Imp. */
#define SCORE_MSG_2105		2125	/* Marca Inicio */
#define SCORE_MSG_2106		2126	/* Marca Fim */
#define SCORE_MSG_2107		2127	/* Desmarca */
#define SCORE_MSG_2108		2128	/* Zoom 1 */
#define SCORE_MSG_2109		2129	/* Zoom 2 */
#define SCORE_MSG_2110		2130	/* Zoom 5 */
#define SCORE_MSG_2111		2131	/* Zoom 10 */
#define SCORE_MSG_2112		2132	/* Zoom 20 */
#define SCORE_MSG_2113		2133	/* Novo Operador */
#define SCORE_MSG_2114		2134	/* Apaga Operador */
#define SCORE_MSG_2115		2135	/* Modifica Operador */
/* Web Score */
#define SCORE_MSG_2116		2136	/* Parametros de entrada invalidos ! */
#define SCORE_MSG_2117		2137	/* Cubas Selecionadas */
#define SCORE_MSG_2118		2138	/* Menu Principal */
#define SCORE_MSG_2119		2139	/* Pre Selecao Alterada ! */
#define SCORE_MSG_2120		2140	/* Atencao: maiusculas sao diferentes de minusculas. */
#define SCORE_MSG_2121		2141	/* Usuario conectado */
#define SCORE_MSG_2122		2142	/* Voltar */
#define SCORE_MSG_2123		2143	/* Pre Selecao */
#define SCORE_MSG_2124		2144	/* Nome de operador ja existente. */
#define SCORE_MSG_2125		2145	/* Senhas digitadas nao sao iguais. */
#define SCORE_MSG_2126		2146	/* Grava Todas */
#define SCORE_MSG_2127		2147	/* Grafico 1,Grafico 2,Grafico 3 */

/* Increase Tables */
#define SCORE_MSG_2128		2148	/*            Setpoint   Incremento  Tipo        Duracao  */
#define SCORE_MSG_2129		2149	/*             [uOhm]    [uOhm] */
#define SCORE_MSG_2130		2150	/* Configuracao Incremento - Passo */
#define SCORE_MSG_2131		2151	/* Tabelas nao salvas. Confirma saida? */
#define SCORE_MSG_2132		2152	/* Acao           Parametro */
#define SCORE_MSG_2133		2153	/* Configuracao Efeito Anodico - Passo */
#define SCORE_MSG_2134		2154	/* Lista Acoes */
#define SCORE_MSG_2135		2155	/* ou */
#define SCORE_MSG_2136		2156	/* Lista Rotinas */
#define SCORE_MSG_2137		2157	/*  */
#define SCORE_MSG_2138		2158	/*  */
#define SCORE_MSG_2139		2159	/*  */
#define SCORE_MSG_2140		2160	/*  */
#define SCORE_MSG_2141		2161	/*  */
#define SCORE_MSG_2142		2162	/*  */
#define SCORE_MSG_2143		2163	/*  */
#define SCORE_MSG_2144		2164	/*  */
#define SCORE_MSG_2145		2165	/* GravaFaixa */

/* programa de calibracao */
#define SCORE_MSG_2153		2173	/* */
#define SCORE_MSG_2154		2174	/* */
#define SCORE_MSG_2155		2175	/* */
#define SCORE_MSG_2156		2176	/* */
#define SCORE_MSG_2157		2177	/* */
#define SCORE_MSG_2158		2178	/* */
#define SCORE_MSG_2159		2179	/* */
#define SCORE_MSG_2160		2180	/* */
#define SCORE_MSG_2161		2181	/* */
#define SCORE_MSG_2162		2182	/* */
#define SCORE_MSG_2163		2183	/* */
#define SCORE_MSG_2164		2184	/* */
#define SCORE_MSG_2165		2185	/* */
#define SCORE_MSG_2166		2186	/* */
#define SCORE_MSG_2167		2187	/* */
#define SCORE_MSG_2168		2188	/* */
#define SCORE_MSG_2169		2189	/* */
#define SCORE_MSG_2170		2190	/* */
#define SCORE_MSG_2171		2191	/* */
#define SCORE_MSG_2172		2192	/* */
#define SCORE_MSG_2173		2193	/* */
#define SCORE_MSG_2174		2194	/* */
#define SCORE_MSG_2175		2195	/* */
#define SCORE_MSG_2176		2196	/* */
#define SCORE_MSG_2177		2197	/* */
#define SCORE_MSG_2178		2198	/* */
#define SCORE_MSG_2179		2199	/* */
#define SCORE_MSG_2180		2200	/* */
#define SCORE_MSG_2181		2201	/* */
#define SCORE_MSG_2182		2202	/* */
#define SCORE_MSG_2183		2203	/* */
#define SCORE_MSG_2184		2204	/* */
#define SCORE_MSG_2185		2205	/* */
#define SCORE_MSG_2186		2206	/* */
#define SCORE_MSG_2187		2207	/* */
#define SCORE_MSG_2188		2208	/* */
#define SCORE_MSG_2189		2209	/* */
#define SCORE_MSG_2190		2210	/* */
#define SCORE_MSG_2191		2211	/* */
#define SCORE_MSG_2192		2212	/* */
#define SCORE_MSG_2193		2213	/* */
#define SCORE_MSG_2194		2214	/* */
#define SCORE_MSG_2195		2215	/* */

/* outros */
#define SCORE_MSG_2196		2216	/* Configuracao Alimentacao da Cuba */

#define SCORE_MSG_2204		2224	/* Libera Calibracao */

#define SCORE_MSG_2231		2251
#define SCORE_MSG_2232		2252
#define SCORE_MSG_2233		2253

/* usado ate o 2268 */

#define	SCORE_MSG_2249		2269	/* Registra, imprime e exibe */
#define	SCORE_MSG_2250		2270	/* Registra e exibe */
#define	SCORE_MSG_2251		2271	/* Registra e imprime */
#define	SCORE_MSG_2252		2272	/* Apenas registra */
#define	SCORE_MSG_2253		2273	/* Nao registra */

/* Editor do descritor de eventos */
#define	SCORE_MSG_2254		2274	/* Todos dispositivos */
#define	SCORE_MSG_2255		2275	/* Exceto Graf. Cuba */
#define	SCORE_MSG_2256		2276	/* Exceto Ev. Inst. */
#define	SCORE_MSG_2257		2277	/* Exceto Ev. e Graf. */

#define	SCORE_MSG_2258		2278	/* Char */
#define	SCORE_MSG_2259		2279	/* Int */
#define	SCORE_MSG_2260		2280	/* Long */
#define	SCORE_MSG_2261		2281	/* Float */
#define	SCORE_MSG_2262		2282	/* Str */
#define	SCORE_MSG_2263		2283	/* Nenhum */
#define	SCORE_MSG_2264		2284	/* Pesquisar */
#define	SCORE_MSG_2265		2285	/* Inicializar */
#define	SCORE_MSG_2266		2286	/* Mover */
#define	SCORE_MSG_2267		2287	/* Copiar */
#define	SCORE_MSG_2268		2288	/* Instalar */
#define	SCORE_MSG_2269		2289	/* Cod. Evento */
#define	SCORE_MSG_2270		2290	/* Mneumonico */
#define	SCORE_MSG_2271		2291	/* Mensagem */
#define	SCORE_MSG_2272		2292	/* Grupo */
#define	SCORE_MSG_2273		2293	/* Dispositivo */
#define	SCORE_MSG_2274		2294	/* Tipo Evento */
#define	SCORE_MSG_2275		2295	/* Linha */
#define	SCORE_MSG_2276		2296	/* Parametros do Evento */
#define	SCORE_MSG_2277		2297	/* Tipo Parametro */
#define	SCORE_MSG_2278		2298	/* Pesquisa por mneumonico */
#define	SCORE_MSG_2279		2299	/* Pesquisa por mensagem */
#define	SCORE_MSG_2280		2300	/* Entre com o texto */
#define	SCORE_MSG_2281		2301	/* Procura */
#define	SCORE_MSG_2282		2302	/* Proximo */
#define	SCORE_MSG_2283		2303	/* Mover Evento */
#define	SCORE_MSG_2284		2304	/* Entre com o codigo do evento de destino */
#define	SCORE_MSG_2285		2305	/* Copiar Evento */
#define	SCORE_MSG_2286		2306	/* DesabOpe */
// missing !!

#define SCORE_MSG_2292		2312	/* Susp TEMP */ 
#define SCORE_MSG_2293		2313	/* Confirma RESET Calibracao? */ 
#define SCORE_MSG_2294		2314	/* Confirma Calibracao? */ 
#define SCORE_MSG_2295		2315	/* Calibracao nao Efetuada! */ 
#define SCORE_MSG_2296		2316	/* Dados Gravados! */ 
#define SCORE_MSG_2297		2317	/* Ef. Move */ 
#define SCORE_MSG_2298		2318	/* Ef. Queb */ 
#define SCORE_MSG_2299		2319	/* Ef. Corr */ 
#define SCORE_MSG_2300		2320	/* Ef. E.A. */ 
#define SCORE_MSG_2301 		2321	/* E. A. */ 
#define SCORE_MSG_2302 		2322	/* Prev. EA */ 
#define SCORE_MSG_2303 		2323	/* T. Pinos */ 
#define SCORE_MSG_2304 		2324	/* Confirma Ativar/Desativar Quebrada Preventiva */ 
#define SCORE_MSG_2305 		2325	/* Salta Passo da Tabela de Incrementos */ 
#define SCORE_MSG_2306 		2326	/* RANGE CUBAS */ 
#define SCORE_MSG_2307 		2327	/* GOTO CUBAS */ 
#define SCORE_MSG_2308 		2328	/* CONFIGURACAO */ 
#define SCORE_MSG_2309 		2329	/* Exportação: */ 
#define SCORE_MSG_2310 		2330	/*  */ 
#define SCORE_MSG_2311 		2331	/*  */ 
#define SCORE_MSG_2312 		2332	/*  */ 
#define SCORE_MSG_2313 		2333	/*  */ 
#define SCORE_MSG_2314 		2334	/*  */ 
#define SCORE_MSG_2315 		2335	/*  */ 
#define SCORE_MSG_2316 		2336	/*  */ 
#define SCORE_MSG_2317 		2337	/*  */ 
#define SCORE_MSG_2318 		2338	/*  */ 
#define SCORE_MSG_2319 		2339	/*  */ 
#define SCORE_MSG_2320 		2340	/*  */ 
#define SCORE_MSG_2321 		2341	/*  */ 
#define SCORE_MSG_2322 		2342	/*  */ 
#define SCORE_MSG_2323 		2343	/*  */ 
#define SCORE_MSG_2324 		2344	/*  */ 
#define SCORE_MSG_2325 		2345	/*  */ 
#define SCORE_MSG_2326 		2346	/*  */ 
#define SCORE_MSG_2327 		2347	/*  */ 
#define SCORE_MSG_2328 		2348	/*  */ 
#define SCORE_MSG_2329 		2349	/*  */ 
#define SCORE_MSG_2330 		2350	/*  */ 
#define SCORE_MSG_2331		2351	/*  */ 
#define SCORE_MSG_2332 		2352	/*  */ 
#define SCORE_MSG_2333		2353	/*  */ 
#define SCORE_MSG_2334 		2354	/*  */ 
#define SCORE_MSG_2335		2355	/*  */ 
#define SCORE_MSG_2336		2356	/*  */ 
#define SCORE_MSG_2337		2357	/*  */ 
#define SCORE_MSG_2338		2358	/*  */ 
#define SCORE_MSG_2339		2359	/*  */ 
#define SCORE_MSG_2340		2360	/* Remota Invalida */ 
#define SCORE_MSG_2341		2361	/* Selecao de Canal Principal e Reserva Invalido ! */ 
#define SCORE_MSG_2342		2362	/* Parametros Gravados com Sucesso ! */ 
#define SCORE_MSG_2343		2363	/* FontCorr */ 
#define SCORE_MSG_2344		2364	/* IIndex-0 */ 
#define SCORE_MSG_2345		2365	/* IIndex-1 */ 
#define SCORE_MSG_2346		2366	/* AtnCA1 */ 
#define SCORE_MSG_2347		2367	/* AtnCA2 */ 
#define SCORE_MSG_2348		2368	/* Canal 1 */ 
#define SCORE_MSG_2349		2369	/* Canal 2 */ 
#define SCORE_MSG_2350		2370	/* Principal */ 
#define SCORE_MSG_2351		2371	/* Reserva */ 
#define SCORE_MSG_2352		2372	/* Fonte Sinal: */ 
#define SCORE_MSG_2353		2373	/* Mudanca de Fonte de Sinal de Corrente */ 

#define SCORE_MSG_2362		2382	/* Vinst maior */
#define SCORE_MSG_2363		2383	/* Vinst menor */
#define SCORE_MSG_2364		2384	/* Goto passo */
#define	SCORE_MSG_2365		2385	/* FRACO1 */
#define	SCORE_MSG_2366		2386	/* FRACO2 */
#define	SCORE_MSG_2367		2387	/* FRACO3 */
#define	SCORE_MSG_2368		2388	/* FORTE1 */
#define	SCORE_MSG_2369		2389	/* FORTE2 */
#define SCORE_MSG_2370		2390	/* IntervJanRRap invalido (1,2,3,4,6 ou 8) -> alterado para 6 horas */

/* area disponivel para strings genericos do Score procure por FREESLOT*/

/* strings relacionados com coletor de dados */

 /* tela de eventos do coletor cuba / linha */
#define SCORE_MSG_3000		3020	/* EVENTOS CUBA */
#define SCORE_MSG_3001		3021	/* EVENTOS LINHA */
#define SCORE_MSG_3002		3022	/* HOME */
#define SCORE_MSG_3003		3023	/* PGUP */
#define SCORE_MSG_3004		3024	/* PGDN */
#define SCORE_MSG_3005		3025	/* END */
#define SCORE_MSG_3006		3026	/* SAIR */
#define SCORE_MSG_3007		3027	/*  */
#define SCORE_MSG_3008		3028	/*  */
#define SCORE_MSG_3009		3029	/*  */

 /* menu principal eventos coletor */
#define SCORE_MSG_3010		3030 	/* EVENTOS CUBA/LINHA */
#define SCORE_MSG_3011		3031 	/* CUBA */
#define SCORE_MSG_3012		3032 	/* LINHA */
#define SCORE_MSG_3013		3033 	/* SAIR */
#define SCORE_MSG_3014		3034 	/*  */
#define SCORE_MSG_3015		3035 	/*  */
#define SCORE_MSG_3016		3036 	/*  */
#define SCORE_MSG_3017		3037 	/*  */
#define SCORE_MSG_3018		3038 	/*  */
#define SCORE_MSG_3019		3039 	/*  */

 /* menu principal operacao coletor */
#define SCORE_MSG_3020		3040 	/* OPERACAO */
#define SCORE_MSG_3021		3041 	/* QUEBRADA */
#define SCORE_MSG_3022		3042 	/* CORRIDA */
#define SCORE_MSG_3023		3043 	/* TROCA PINOS */
#define SCORE_MSG_3024		3044 	/* MUDA CUBA */
#define SCORE_MSG_3025		3045 	/* MENU PRINCIPAL */
#define SCORE_MSG_3026		3046 	/* */
#define SCORE_MSG_3027		3047 	/* */
#define SCORE_MSG_3028		3048 	/* */
#define SCORE_MSG_3029		3049 	/* SAIR */

 /* menu principal parametros coletor */
#define SCORE_MSG_3030		3050 	/* VARIAVEIS CUBA */
#define SCORE_MSG_3031		3051 	/* SAIR */
#define SCORE_MSG_3032		3052 	/*  */
#define SCORE_MSG_3033		3053 	/*  */
#define SCORE_MSG_3034		3054 	/*  */
#define SCORE_MSG_3035		3055 	/*  */
#define SCORE_MSG_3036		3056 	/*  */
#define SCORE_MSG_3037		3057 	/*  */
#define SCORE_MSG_3038		3058 	/*  */
#define SCORE_MSG_3039		3059 	/*  */

 /* mensagem de samaforo alocado parametros coletor */
#define SCORE_MSG_3040		3060 	/* ATENCAO */
#define SCORE_MSG_3041		3061 	/* CONFIGURACAO DE CUBAS */
#define SCORE_MSG_3042		3062 	/* ATIVADO EM */
#define SCORE_MSG_3043		3063 	/* OUTRO NODO/COLETOR */
#define SCORE_MSG_3044		3064 	/* APERTE ENT... */
#define SCORE_MSG_3045		3065 	/*  */
#define SCORE_MSG_3046		3066 	/*  */
#define SCORE_MSG_3047		3067 	/*  */
#define SCORE_MSG_3048		3068 	/*  */
#define SCORE_MSG_3049		3069 	/*  */

 /* menu de entrada de dados parametros coletor */
#define SCORE_MSG_3050		3070 	/* VARIAVEIS CUBA */
#define SCORE_MSG_3051		3071 	/* ANTERIOR */
#define SCORE_MSG_3052		3072 	/* NOVO */
#define SCORE_MSG_3053		3073 	/* APERTE ENT PARA SAIR */
#define SCORE_MSG_3054		3074 	/* OU */
#define SCORE_MSG_3055		3075 	/* ENTRE COM NOVO VALOR */
#define SCORE_MSG_3056		3076 	/*  */
#define SCORE_MSG_3057		3077 	/*  */
#define SCORE_MSG_3058		3078 	/*  */
#define SCORE_MSG_3059		3079 	/*  */

 /* valor invalido entrada parametros coletor */
#define SCORE_MSG_3060		3080 	/* ATENCAO */
#define SCORE_MSG_3061		3081 	/* VALOR */
#define SCORE_MSG_3062		3082 	/* INVALIDO */
#define SCORE_MSG_3063		3083 	/* APERTE ENT... */
#define SCORE_MSG_3064		3084 	/*  */
#define SCORE_MSG_3065		3085 	/*  */
#define SCORE_MSG_3066		3086 	/*  */
#define SCORE_MSG_3067		3087 	/*  */
#define SCORE_MSG_3068		3088 	/*  */
#define SCORE_MSG_3069		3089 	/*  */

 /* confirma valor entrada parametros coletor */
#define SCORE_MSG_3070		3090 	/* ATENCAO */
#define SCORE_MSG_3071		3091 	/* CONFIRMA ALTERACAO ? */
#define SCORE_MSG_3072		3092 	/* ANTERIOR */
#define SCORE_MSG_3073		3093 	/* NOVO */
#define SCORE_MSG_3074		3094 	/* CONFIRMA */
#define SCORE_MSG_3075		3095 	/* SAIR */
#define SCORE_MSG_3076		3096 	/*  */
#define SCORE_MSG_3077		3097 	/*  */
#define SCORE_MSG_3078		3098 	/*  */
#define SCORE_MSG_3079		3099 	/*  */

 /* fora limites valor entrada parametros coletor */
#define SCORE_MSG_3080		3100 	/* ATENCAO */
#define SCORE_MSG_3081		3101 	/* VALOR */
#define SCORE_MSG_3082		3102 	/* FORA DOS LIMITES */
#define SCORE_MSG_3083 		3103 	/* LS */
#define SCORE_MSG_3084		3104 	/* LI */
#define SCORE_MSG_3085		3105 	/* APERTE ENT... */
#define SCORE_MSG_3086		3106 	/*  */
#define SCORE_MSG_3087		3107 	/*  */
#define SCORE_MSG_3088		3108 	/*  */
#define SCORE_MSG_3089		3109 	/*  */

 /* erro liberacao samaforo parametros coletor */
#define SCORE_MSG_3090		3110 	/* ATENCAO */
#define SCORE_MSG_3091		3111 	/* NAO CONSEGUI */
#define SCORE_MSG_3092		3112 	/* LIBERAR SEMAFORO */
#define SCORE_MSG_3093		3113 	/* CONFIGURACAO CUBAS */
#define SCORE_MSG_3094		3114 	/* APERTE ENT... */
#define SCORE_MSG_3095		3115 	/*  */
#define SCORE_MSG_3096		3116 	/*  */
#define SCORE_MSG_3097		3117 	/*  */
#define SCORE_MSG_3098		3118 	/*  */
#define SCORE_MSG_3099		3119 	/*  */

 /* menu principal atualcuba coletor */
#define SCORE_MSG_3100		3120 	/* ATUAL CUBA */
#define SCORE_MSG_3101		3121 	/* CONTROLE */
#define SCORE_MSG_3102		3122 	/* RUIDO */
#define SCORE_MSG_3103		3123 	/* STATUS */
#define SCORE_MSG_3104		3124 	/* SAIR */
#define SCORE_MSG_3105		3125 	/*  */
#define SCORE_MSG_3106		3126 	/*  */
#define SCORE_MSG_3107		3127 	/*  */
#define SCORE_MSG_3108		3128 	/*  */
#define SCORE_MSG_3109		3129 	/*  */

 /* 2 menu atualcuba coletor */
#define SCORE_MSG_3110		3130 	/* CONTROLE CUBA */
#define SCORE_MSG_3111		3131 	/* RUIDO CUBA */
#define SCORE_MSG_3112		3132 	/* STATUS CUBA */
#define SCORE_MSG_3113		3133 	/* SAIR */
#define SCORE_MSG_3114		3134 	/*  */
#define SCORE_MSG_3115		3135 	/*  */
#define SCORE_MSG_3116		3136 	/*  */
#define SCORE_MSG_3117		3137 	/*  */
#define SCORE_MSG_3118		3138 	/*  */
#define SCORE_MSG_3119		3139 	/*  */

 /* hora atual sistema coletor */
#define SCORE_MSG_3120		3140 	/* HORA ATUAL */
#define SCORE_MSG_3121		3141 	/* SAIR */
#define SCORE_MSG_3122		3142 	/*  */
#define SCORE_MSG_3123		3143 	/*  */
#define SCORE_MSG_3124		3144 	/*  */
#define SCORE_MSG_3125		3145 	/*  */
#define SCORE_MSG_3126		3146 	/*  */
#define SCORE_MSG_3127		3147 	/*  */
#define SCORE_MSG_3128		3148 	/*  */
#define SCORE_MSG_3129		3149 	/*  */

 /* menu principal login coletor */
#define SCORE_MSG_3130		3150 	/* C B A */
#define SCORE_MSG_3131		3151 	/* OPERADOR */
#define SCORE_MSG_3132		3152 	/* SENHA */

 /* operador nao cadastrado login coletor */
#define SCORE_MSG_3140		3160 	/* ATENCAO */
#define SCORE_MSG_3141		3161 	/* OPERADOR NAO */
#define SCORE_MSG_3142		3162 	/* CADASTRADO */
#define SCORE_MSG_3143		3163 	/* APERTE ENT... */

 /* senha invalida login coletor */
#define SCORE_MSG_3150		3170 	/* ATENCAO */
#define SCORE_MSG_3151		3171 	/* SENHA INVALIDA */
#define SCORE_MSG_3152		3172 	/* APERTE ENT... */

 /* menu principal graficos cuba coletor */
#define SCORE_MSG_3160		3180 	/* GRAFICOS CUBA */
#define SCORE_MSG_3161		3181 	/* GRAFICO 1 */
#define SCORE_MSG_3162		3182 	/* GRAFICO 2 */
#define SCORE_MSG_3163		3183 	/* GRAFICO 3 */
#define SCORE_MSG_3164		3184 	/* SAIR */
#define SCORE_MSG_3165		3185 	/*  */
#define SCORE_MSG_3166		3186 	/*  */
#define SCORE_MSG_3167		3187 	/*  */
#define SCORE_MSG_3168		3188 	/*  */
#define SCORE_MSG_3169		3189 	/*  */

 /* menu principal quebrada cuba coletor */
#define SCORE_MSG_3170		3190 	/* QUEBRADA */
#define SCORE_MSG_3171		3191 	/* CONFIRMA */
#define SCORE_MSG_3172		3192 	/*  */
#define SCORE_MSG_3173		3193 	/*  */
#define SCORE_MSG_3174		3194 	/*  */
#define SCORE_MSG_3175		3195 	/*  */
#define SCORE_MSG_3176		3196 	/*  */
#define SCORE_MSG_3177		3197 	/*  */
#define SCORE_MSG_3178		3198 	/*  */
#define SCORE_MSG_3179		3199 	/* SAIR */

 /* sinalizacao de quebrada cuba coletor */
#define SCORE_MSG_3180		3200 	/* ATENCAO */
#define SCORE_MSG_3181		3201 	/* QUEBRADA */
#define SCORE_MSG_3182		3202 	/* SINALIZADA */
#define SCORE_MSG_3183		3203 	/* APERTE ENT... */
#define SCORE_MSG_3184		3204 	/*  */
#define SCORE_MSG_3185		3205 	/*  */
#define SCORE_MSG_3186		3206 	/*  */
#define SCORE_MSG_3187		3207 	/*  */
#define SCORE_MSG_3188		3208 	/*  */
#define SCORE_MSG_3189		3209 	/* SAIR */

 /* menu principal corrida cuba coletor */
#define SCORE_MSG_3190		3210 	/* CORRIDA */
#define SCORE_MSG_3191		3211 	/* CONFIRMA */
#define SCORE_MSG_3192		3212 	/*  */
#define SCORE_MSG_3193		3213 	/*  */
#define SCORE_MSG_3194		3214 	/*  */
#define SCORE_MSG_3195		3215 	/*  */
#define SCORE_MSG_3196		3216 	/*  */
#define SCORE_MSG_3197		3217 	/*  */
#define SCORE_MSG_3198		3218 	/*  */
#define SCORE_MSG_3199		3219 	/* SAIR */

 /* sinalizacao de corrida cuba coletor */
#define SCORE_MSG_3200		3220 	/* ATENCAO */
#define SCORE_MSG_3201		3221 	/* CORRIDA */
#define SCORE_MSG_3202		3222 	/* SINALIZADA */
#define SCORE_MSG_3203		3223 	/* APERTE ENT... */
#define SCORE_MSG_3204		3224 	/* */
#define SCORE_MSG_3205		3225 	/* */
#define SCORE_MSG_3206		3226 	/* */
#define SCORE_MSG_3207		3227 	/* */
#define SCORE_MSG_3208		3228 	/* */
#define SCORE_MSG_3209		3229 	/* */

 /* aguardando fim de corrida cuba coletor */
#define SCORE_MSG_3210		3230 	/* CORRIDA */
#define SCORE_MSG_3211		3231 	/* ACERTO */
#define SCORE_MSG_3212		3232 	/* INSTERMEDIARIO */
#define SCORE_MSG_3213		3233 	/* DA CORRIDA */
#define SCORE_MSG_3214		3234 	/* CONFIRMA FIM */
#define SCORE_MSG_3215		3235 	/* DA CORRIDA */
#define SCORE_MSG_3216		3236 	/* TENSAO */
#define SCORE_MSG_3217		3237 	/* ACERTO */
#define SCORE_MSG_3218		3238 	/* INTERMEDIARIO */
#define SCORE_MSG_3219		3239 	/* EM ANDAMENTO */

 /* corrida cuba em andamento coletor */
#define SCORE_MSG_3220		3240 	/* ATENCAO */
#define SCORE_MSG_3221		3241 	/* CORRIDA */
#define SCORE_MSG_3222		3242 	/* EM */
#define SCORE_MSG_3223		3243 	/* ANDAMENTO */
#define SCORE_MSG_3224		3244 	/* APERTE ENT... */
#define SCORE_MSG_3225		3245 	/* ACERTO */
#define SCORE_MSG_3226		3246 	/* INTERMEDIARIO */
#define SCORE_MSG_3227		3247	/* FINALIZADO */
#define SCORE_MSG_3228		3248	/*  */
#define SCORE_MSG_3229		3249	/*  */

 /* menu principal troca pinos cuba coletor */
#define SCORE_MSG_3230		3250 	/* TROCA PINOS */
#define SCORE_MSG_3231		3251 	/* ATIVA */
#define SCORE_MSG_3232		3252 	/* DESATIVA */
#define SCORE_MSG_3233		3253 	/*  */
#define SCORE_MSG_3234		3254 	/*  */
#define SCORE_MSG_3235		3255 	/*  */
#define SCORE_MSG_3236		3256 	/*  */
#define SCORE_MSG_3237		3257 	/*  */
#define SCORE_MSG_3238		3258 	/*  */
#define SCORE_MSG_3239		3259 	/* SAIR */

 /* informacoes sobre troca pinos cuba coletor */
#define SCORE_MSG_3240		3260 	/* ATENCAO */
#define SCORE_MSG_3241		3261 	/* APERTE ENT... */
#define SCORE_MSG_3242		3262 	/* TROCA PINOS */
#define SCORE_MSG_3243		3263 	/* ATIVADA */
#define SCORE_MSG_3244		3264 	/* JA ESTA */
#define SCORE_MSG_3245		3265 	/* DESATIVADA */
#define SCORE_MSG_3246		3266 	/*  */
#define SCORE_MSG_3247		3267 	/*  */
#define SCORE_MSG_3248		3268 	/*  */
#define SCORE_MSG_3249		3269 	/* SAIR */

 /* entrada numero da cuba coletor */
#define SCORE_MSG_3250		3270 	/* C B A */
#define SCORE_MSG_3251		3271 	/* CUBA */

 /* cuba invalida coletor */
#define SCORE_MSG_3260		3280 	/* ATENCAO */
#define SCORE_MSG_3261		3281 	/* CUBA */
#define SCORE_MSG_3262		3282 	/* INVALIDA */
#define SCORE_MSG_3263		3283 	/* APERTE ENT... */

 /* menu principal variaveis de processo coletor */
#define SCORE_MSG_3270		3290 	/* PROCESSO CUBA */
#define SCORE_MSG_3271		3291 	/* STATUS */
#define SCORE_MSG_3272		3292 	/* VERRO */
#define SCORE_MSG_3273		3293 	/* DERIVADA */
#define SCORE_MSG_3274		3294 	/* RUIDO LENTO */
#define SCORE_MSG_3275		3295 	/* RUIDO RAPIDO */
#define SCORE_MSG_3276		3296 	/* TEMPO DESDE ULT.EA */
#define SCORE_MSG_3277		3297 	/*  */
#define SCORE_MSG_3278		3298 	/*  */
#define SCORE_MSG_3279		3299 	/* SAIR */

/* string coletor para eventos */
#define SCORE_MSG_3280		3300 	/* Coletor */

 /* menu principal do coletor */
#define SCORE_MSG_3290		3310	/* MENU PRINCIPAL */
#define SCORE_MSG_3291		3311	/* MUDA CUBA */
#define SCORE_MSG_3292		3312	/* OPERACAO */
#define SCORE_MSG_3293		3313	/* CONFIGURACAO */
#define SCORE_MSG_3294		3314	/* GRAFICOS */
#define SCORE_MSG_3295		3315	/* PROCESSO */
#define SCORE_MSG_3296		3316	/* VALORES ATUAIS */
#define SCORE_MSG_3297		3317	/* EVENTOS */
#define SCORE_MSG_3298		3318	/* HORA ATUAL */
#define SCORE_MSG_3299		3319 	/*  */
#define SCORE_MSG_3300		3320 	/* SAIR */
#define SCORE_MSG_3301		3321 	/*  */
#define SCORE_MSG_3302		3322 	/*  */
#define SCORE_MSG_3303		3323 	/*  */
#define SCORE_MSG_3304		3324 	/*  */
#define SCORE_MSG_3305		3325 	/*  */
#define SCORE_MSG_3306		3326 	/*  */
#define SCORE_MSG_3307		3327 	/*  */
#define SCORE_MSG_3308		3328 	/*  */
#define SCORE_MSG_3309		3329 	/*  */

 /* menu condicoes da bateria */
#define SCORE_MSG_3310		3330	/* NORAND 6400 */
#define SCORE_MSG_3311		3331	/* RADIO */
#define SCORE_MSG_3312		3332	/* CONDICAO ATUAL */
#define SCORE_MSG_3313		3333	/* DA BATERIA */
#define SCORE_MSG_3314		3334	/* SAIR */

#define SCORE_MSG_3320		3340	/*  */
#define SCORE_MSG_3321		3341	/*  */
#define SCORE_MSG_3322		3342	/*  */
#define SCORE_MSG_3323		3343	/*  */

#define SCORE_MSG_3330		3350	/*  */
#define SCORE_MSG_3331		3351	/*  */
#define SCORE_MSG_3332		3352	/*  */
#define SCORE_MSG_3333		3353	/*  */
#define SCORE_MSG_3334		3354	/*  */
#define SCORE_MSG_3335		3355	/*  */
#define SCORE_MSG_3336		3356	/*  */
#define SCORE_MSG_3337		3357	/*  */
#define SCORE_MSG_3338		3358	/*  */
#define SCORE_MSG_3339		3359	/*  */

#define SCORE_MSG_3340		3360	/*  */
#define SCORE_MSG_3341		3361	/*  */
#define SCORE_MSG_3342		3362	/*  */
#define SCORE_MSG_3343		3363	/*  */
#define SCORE_MSG_3344		3364	/*  */
#define SCORE_MSG_3345		3365	/*  */
#define SCORE_MSG_3346		3366	/*  */
#define SCORE_MSG_3347		3367	/*  */
#define SCORE_MSG_3348		3368	/*  */
#define SCORE_MSG_3349		3369	/*  */

#define SCORE_MSG_3350		3370	/*  */
#define SCORE_MSG_3351		3371	/*  */
#define SCORE_MSG_3352		3372	/*  */
#define SCORE_MSG_3353		3373	/*  */
#define SCORE_MSG_3354		3374	/*  */
#define SCORE_MSG_3355		3375	/*  */
#define SCORE_MSG_3356		3376	/*  */
#define SCORE_MSG_3357		3377	/*  */
#define SCORE_MSG_3358		3378	/*  */
#define SCORE_MSG_3359		3379	/*  */

#define SCORE_MSG_3360		3380	/*  */
#define SCORE_MSG_3361		3381	/*  */
#define SCORE_MSG_3362		3382	/*  */
#define SCORE_MSG_3363		3383	/*  */
#define SCORE_MSG_3364		3384	/*  */
#define SCORE_MSG_3365		3385	/*  */
#define SCORE_MSG_3366		3386	/*  */
#define SCORE_MSG_3367		3387	/*  */
#define SCORE_MSG_3368		3388	/*  */
#define SCORE_MSG_3369		3389	/*  */

#define SCORE_MSG_3370		3390	/*  */
#define SCORE_MSG_3371		3391	/*  */
#define SCORE_MSG_3372		3392	/*  */
#define SCORE_MSG_3373		3393	/*  */
#define SCORE_MSG_3374		3394	/*  */
#define SCORE_MSG_3375		3395	/*  */
#define SCORE_MSG_3376		3396	/*  */
#define SCORE_MSG_3377		3397	/*  */
#define SCORE_MSG_3378		3398	/*  */
#define SCORE_MSG_3379		3399	/*  */

#define SCORE_MSG_3380		3400	/*  */
#define SCORE_MSG_3381		3401	/*  */
#define SCORE_MSG_3382		3402	/*  */
#define SCORE_MSG_3383		3403	/*  */
#define SCORE_MSG_3384		3404	/*  */
#define SCORE_MSG_3385		3405	/*  */
#define SCORE_MSG_3386		3406	/*  */
#define SCORE_MSG_3387		3407	/*  */
#define SCORE_MSG_3388		3408	/*  */
#define SCORE_MSG_3389		3409	/*  */

#define SCORE_MSG_3390		3410	/*  */
#define SCORE_MSG_3391		3411	/*  */
#define SCORE_MSG_3392		3412	/*  */
#define SCORE_MSG_3393		3413	/*  */
#define SCORE_MSG_3394		3414	/*  */
#define SCORE_MSG_3395		3415	/*  */
#define SCORE_MSG_3396		3416	/*  */
#define SCORE_MSG_3397		3417	/*  */
#define SCORE_MSG_3398		3418	/*  */
#define SCORE_MSG_3399		3419	/*  */

#define SCORE_MSG_3400		3420	/*  */
#define SCORE_MSG_3401		3421	/*  */
#define SCORE_MSG_3402		3422	/*  */
#define SCORE_MSG_3403		3423	/*  */
#define SCORE_MSG_3404		3424	/*  */
#define SCORE_MSG_3405		3425	/*  */
#define SCORE_MSG_3406		3426	/*  */
#define SCORE_MSG_3407		3427	/*  */
#define SCORE_MSG_3408		3428	/*  */
#define SCORE_MSG_3409		3429	/*  */

#define SCORE_MSG_3410		3430	/*  */
#define SCORE_MSG_3411		3431	/*  */
#define SCORE_MSG_3412		3432	/*  */
#define SCORE_MSG_3413		3433	/*  */
#define SCORE_MSG_3414		3434	/*  */
#define SCORE_MSG_3415		3435	/*  */
#define SCORE_MSG_3416		3436	/*  */
#define SCORE_MSG_3417		3437	/*  */
#define SCORE_MSG_3418		3438	/*  */
#define SCORE_MSG_3419		3439	/*  */

#define SCORE_MSG_3420		3440	/*  */
#define SCORE_MSG_3421		3441	/*  */
#define SCORE_MSG_3422		3442	/*  */
#define SCORE_MSG_3423		3443	/*  */
#define SCORE_MSG_3424		3444	/*  */
#define SCORE_MSG_3425		3445	/*  */
#define SCORE_MSG_3426		3446	/*  */
#define SCORE_MSG_3427		3447	/*  */
#define SCORE_MSG_3428		3448	/*  */
#define SCORE_MSG_3429		3449	/*  */

#define SCORE_MSG_3430		3450	/*  */
#define SCORE_MSG_3431		3451	/*  */
#define SCORE_MSG_3432		3452	/*  */
#define SCORE_MSG_3433		3453	/*  */
#define SCORE_MSG_3434		3454	/*  */
#define SCORE_MSG_3435		3455	/*  */
#define SCORE_MSG_3436		3456	/*  */
#define SCORE_MSG_3437		3457	/*  */
#define SCORE_MSG_3438		3458	/*  */
#define SCORE_MSG_3439		3459	/*  */

#define SCORE_MSG_3440		3460	/*  */
#define SCORE_MSG_3441		3461	/*  */
#define SCORE_MSG_3442		3462	/*  */
#define SCORE_MSG_3443		3463	/*  */
#define SCORE_MSG_3444		3464	/*  */
#define SCORE_MSG_3445		3465	/*  */
#define SCORE_MSG_3446		3466	/*  */
#define SCORE_MSG_3447		3467	/*  */
#define SCORE_MSG_3448		3468	/*  */
#define SCORE_MSG_3449		3469	/*  */

#define SCORE_MSG_3450		3470	/*  */
#define SCORE_MSG_3451		3471	/*  */
#define SCORE_MSG_3452		3472	/*  */
#define SCORE_MSG_3453		3473	/*  */
#define SCORE_MSG_3454		3474	/*  */
#define SCORE_MSG_3455		3475	/*  */
#define SCORE_MSG_3456		3476	/*  */
#define SCORE_MSG_3457		3477	/*  */
#define SCORE_MSG_3458		3478	/*  */
#define SCORE_MSG_3459		3479	/*  */

#define SCORE_MSG_3460		3480	/*  */
#define SCORE_MSG_3461		3481	/*  */
#define SCORE_MSG_3462		3482	/*  */
#define SCORE_MSG_3463		3483	/*  */
#define SCORE_MSG_3464		3484	/*  */
#define SCORE_MSG_3465		3485	/*  */
#define SCORE_MSG_3466		3486	/*  */
#define SCORE_MSG_3467		3487	/*  */
#define SCORE_MSG_3468		3488	/*  */
#define SCORE_MSG_3469		3489	/*  */

#define SCORE_MSG_3470		3490	/*  */
#define SCORE_MSG_3471		3491	/*  */
#define SCORE_MSG_3472		3492	/*  */
#define SCORE_MSG_3473		3493	/*  */
#define SCORE_MSG_3474		3494	/*  */
#define SCORE_MSG_3475		3495	/*  */
#define SCORE_MSG_3476		3496	/*  */
#define SCORE_MSG_3477		3497	/*  */
#define SCORE_MSG_3478		3498	/*  */
#define SCORE_MSG_3479		3499	/*  */

#define SCORE_MSG_3480		3500	/*  */
#define SCORE_MSG_3481		3501	/*  */
#define SCORE_MSG_3482		3502	/*  */
#define SCORE_MSG_3483		3503	/*  */
#define SCORE_MSG_3484		3504	/*  */
#define SCORE_MSG_3485		3505	/*  */
#define SCORE_MSG_3486		3506	/*  */
#define SCORE_MSG_3487		3507	/*  */
#define SCORE_MSG_3488		3508	/*  */
#define SCORE_MSG_3489		3509	/*  */

#define SCORE_MSG_3490		3510	/*  */
#define SCORE_MSG_3491		3511	/*  */
#define SCORE_MSG_3492		3512	/*  */
#define SCORE_MSG_3493		3513	/*  */
#define SCORE_MSG_3494		3514	/*  */
#define SCORE_MSG_3495		3515	/*  */
#define SCORE_MSG_3496		3516	/*  */
#define SCORE_MSG_3497		3517	/*  */
#define SCORE_MSG_3498		3518	/*  */
#define SCORE_MSG_3499		3519	/*  */
/* area livre do score, acima da area do coletor ( 3000 ) */

 /* area reservada para strings de projetos */
#define SCORE_MSG_4500		4020	/* inicio */
#define SCORE_MSG_4979		4999	/* fim */

/*
------------------------------------------------------------------------------
				Definicoes de sinonimos
------------------------------------------------------------------------------
*/
#define NOME_EV_TOTAL			SCORE_MSG_7
#define NOME_EV_PROC			SCORE_MSG_8
#define NOME_EV_SIST			SCORE_MSG_9
#define NOME_EV_LINHA			SCORE_MSG_10
#define NOME_EV_CUBA			SCORE_MSG_11
#define NOME_EV_MENS			SCORE_MSG_12
#define OPCAO_CANCELA_CONFIRMA	SCORE_MSG_13
#define NOME_ATENCAO			SCORE_MSG_1
#define STR_CONFIRMA_IMPRESSAO	SCORE_MSG_14
#define MSG_PED_SEN_ABOR		SCORE_MSG_15
#define MSG_NOME_OPER_INV		SCORE_MSG_16
#define MSG_SENHA_INV			SCORE_MSG_17
#define NOME_ABANDONA			SCORE_MSG_19
#define NOME_CONFIRMA			SCORE_MSG_20
#define NOME_CANCELA			SCORE_MSG_199
#define NOME_SALA_1				SCORE_MSG_50
#define NOME_SALA_2				SCORE_MSG_51
#define NOME_SALA_3				SCORE_MSG_52
#define NOME_SALA_4				SCORE_MSG_53
#define NOME_SALA_5				SCORE_MSG_54
#define NOME_SALA_6				SCORE_MSG_55
#define NOME_SALA_7				SCORE_MSG_56
#define NOME_SALA_8				SCORE_MSG_57
#define NOME_LIMPA				SCORE_MSG_25
#define NOME_CUBAS				SCORE_MSG_26
#define NOME_NODO				SCORE_MSG_27
#define STR_LOGIN_ATIVADO		SCORE_MSG_28
#define STR_LOGIN_DESATIVADO	SCORE_MSG_29
#define MSG_DATA_INI_INV		SCORE_MSG_34
#define MSG_DATA_FIM_INV		SCORE_MSG_35
#define NOME_ERRO				SCORE_MSG_0
#define	TEXTO_REDUCAO			SCORE_MSG_23
#define STR_NAO_ARQ_AJUDA		SCORE_MSG_24
#define NOME_RANGE_CUBAS		SCORE_MSG_58
#define NOME_NENHUMA			SCORE_MSG_59
#define NOME_ESPECIAL			SCORE_MSG_60
#define NOME_CUBA_EX			SCORE_MSG_61
#define NOME_PRE_SELECAO		SCORE_MSG_62
#define NOME_ALGORITMO			SCORE_MSG_78
#define NOME_DATA_INI			SCORE_MSG_79
#define NOME_DATA_FIM			SCORE_MSG_80
#define NOME_DATA_EX			SCORE_MSG_81
#define NOME_TURNO				SCORE_MSG_82
#define NOME_DIARIO				SCORE_MSG_571
#define MSG_OPER_NAO_PERM		SCORE_MSG_2
#define NOME_DELECAO			SCORE_MSG_99
#define LOG_CRIA_GRAF           SCORE_MSG_209
#define LOG_CFG_SENHA			SCORE_MSG_212
#define LOG_CFG_CUBA			SCORE_MSG_213
#define LOG_FIM_SCORE			SCORE_MSG_243
#define NOME_PAINEL				SCORE_MSG_244
#define NOME_LOCAL				SCORE_MSG_245
#define NOME_REMOTO				SCORE_MSG_246
#define NOME_ATIVA				SCORE_MSG_247
#define NOME_DESATIVA			SCORE_MSG_248
#define NOME_CONST				SCORE_MSG_249
#define NOME_RAMPA				SCORE_MSG_250
#define LOG_NODO_REM          	SCORE_MSG_257

#define TIPO_LENTO				SCORE_MSG_259
#define TIPO_MRAPID				SCORE_MSG_260
#define TIPO_RAPIDO				SCORE_MSG_261
#define TIPO_ERRO				SCORE_MSG_262

#define NOME_TIPO	  			SCORE_MSG_466
#define NOME_ATRASO	  			SCORE_MSG_467
#define NOME_TRIGGER  			SCORE_MSG_468
#define NOME_COMPARA  			SCORE_MSG_469
#define NOME_OPER	  			SCORE_MSG_470
#define NOME_ARQUIVO_18			SCORE_MSG_463
#define NOME_CUBA_18  			SCORE_MSG_464
#define NOME_VARIAVEIS			SCORE_MSG_465
#define NOME_VARIAVEIS_18		SCORE_MSG_465
#define NOME_DATA	  			SCORE_MSG_497
#define NOME_DATA_18  			SCORE_MSG_506
#define NOME_DURACAO  			SCORE_MSG_498
#define NOME_DURACAO_18			SCORE_MSG_507
#define NOME_SAIR_8  			SCORE_MSG_474
#define NOME_PERIODO_18			SCORE_MSG_508



/*-- Classificacao dos ruidos rapido ou lento --*/
/* os 3 primeiros niveis sao classificados como fracos para contabilizacao estatistica */
#define RUI_NIVEL1				SCORE_MSG_2365
#define RUI_NIVEL2				SCORE_MSG_2366
#define RUI_NIVEL3				SCORE_MSG_2367
/* os 2 ultimos niveis sao classificados como fortes para contabilizacao estatistica */
#define RUI_NIVEL4				SCORE_MSG_2368
#define RUI_NIVEL5				SCORE_MSG_2369

#define RUI_ERRO				SCORE_MSG_262

#define STR_INICIO				SCORE_MSG_265
#define STR_FIM					SCORE_MSG_266
#define STR_NORMAL				SCORE_MSG_267
#define STR_PARTIDA				SCORE_MSG_268
#define STR_LIGADA				SCORE_MSG_269
#define STR_DESLIGADA			SCORE_MSG_270
#define STR_CONTROLE			SCORE_MSG_258
#define STR_HAB_LINHA			SCORE_MSG_278
#define CORRIDA					SCORE_MSG_281
#define EA						SCORE_MSG_282
#define MAN_LOC					SCORE_MSG_283
#define MAN_REM					SCORE_MSG_284
#define MAN_CTR					SCORE_MSG_285
#define QUEBRADA				SCORE_MSG_286
#define NOME_NENHUM				SCORE_MSG_294
#define LOG_CFG_LINHA			SCORE_MSG_306
#define LOG_AJ_CAMISA			SCORE_MSG_307
#define MSG_CONF_IMP_TABELA		SCORE_MSG_308
#define NOME_SUBIR				SCORE_MSG_309
#define NOME_DESCER				SCORE_MSG_310
#define NOME_PARAR				SCORE_MSG_311
#define MSG_ACAO_INV			SCORE_MSG_312
#define MSG_DUR_AJUSTE_INV		SCORE_MSG_313
#define LOG_ELI_EA            	SCORE_MSG_317
#define MSG_TABELA_INV			SCORE_MSG_319
#define LOG_CFG_TOPE          	SCORE_MSG_320
#define MSG_TIPO_INC_INV		SCORE_MSG_333
#define MSG_DUR_INC_INV			SCORE_MSG_334
#define NOME_CUBA				SCORE_MSG_336
#define MSG_EST_ALT				SCORE_MSG_350
#define NOME_NORMAL				SCORE_MSG_359
#define NOME_PARTIDO			SCORE_MSG_360
#define NOME_LIGADO				SCORE_MSG_361
#define NOME_DESLIGADO			SCORE_MSG_362
#define LOG_EST_CUBA			SCORE_MSG_364
#define STR_TERMINAL			SCORE_MSG_365
#define STR_MANUAL				SCORE_MSG_421
#define NOME_ATIVAR				SCORE_MSG_369
#define NOME_DESATIVAR			SCORE_MSG_370
#define STR_CONST				SCORE_MSG_381
#define STR_RAMPA				SCORE_MSG_382
#define LOG_INC_OPE				SCORE_MSG_384
#define STR_ATIVA				SCORE_MSG_386
#define STR_DESATIVA			SCORE_MSG_248
#define NOME_CONSTANTE			SCORE_MSG_388
#define LOG_INC_TROCA_PINOS		SCORE_MSG_395
#define LOG_CORR_OPE			SCORE_MSG_398
#define STR_SINALIZA			SCORE_MSG_399
#define LOG_QUEB_OPE			SCORE_MSG_403
#define LOG_RUI_INIB			SCORE_MSG_405
#define STR_ATUAL				SCORE_MSG_33
#define LINHA_AJUDA_IHM			SCORE_MSG_408
#define RESP_SIM				SCORE_MSG_410
#define RESP_NAO				SCORE_MSG_411
#define MSG_MODO_OPER_ALT		SCORE_MSG_417
#define STR_AUTOMATICO			SCORE_MSG_422
#define NOME_MANUAL				SCORE_MSG_424
#define NOME_AUTOMATICO			SCORE_MSG_423
#define	NOME_TEMPO				SCORE_MSG_425
#define	NOME_RESISTENCIA		SCORE_MSG_426
#define MSG_MOVE_ANODO			SCORE_MSG_427
#define STR_SUBIU				SCORE_MSG_437
#define STR_DESCEU				SCORE_MSG_438
#define LOG_REC_TODOS         	SCORE_MSG_445

#define EST_LIGADA				SCORE_MSG_458
#define EST_DESLIGADA			SCORE_MSG_459
#define EST_PARTIDA				SCORE_MSG_460
#define EST_NORMAL				SCORE_MSG_461
#define EST_ERRO				SCORE_MSG_462

#define TITULO_REDE				SCORE_MSG_475
#define TITULO_NODO				SCORE_MSG_476
#define TITULO_SUBREDE			SCORE_MSG_477
#define TITULO_REGULACAO		SCORE_MSG_478
#define NOME_REGULACAO			SCORE_MSG_479
#define NOME_REDE_ATIV			SCORE_MSG_480
#define NOME_REDE_INAT			SCORE_MSG_481
#define MASC_EST_REDE			SCORE_MSG_590

/* menus do ihm_windows - 80 strings por tela */
#define PADRAO_RELTELA_1		SCORE_MSG_600
#define PADRAO_RELTELA_2		SCORE_MSG_680
#define PADRAO_RELTELA_3		SCORE_MSG_760
#define PADRAO_RELTELA_4		SCORE_MSG_840
#define PADRAO_RELTELA_5		SCORE_MSG_920
#define PADRAO_RELGRAF_1		SCORE_MSG_1000
#define PADRAO_RELGRAF_2		SCORE_MSG_1080
#define PADRAO_OPERACAO_1		SCORE_MSG_1160
#define PADRAO_OPERACAO_2		SCORE_MSG_1240
#define PADRAO_OPERACAO_3		SCORE_MSG_1320
#define PADRAO_OPERACAO_4		SCORE_MSG_1400
#define PADRAO_CONFIGURA_1		SCORE_MSG_1480
#define PADRAO_CONFIGURA_2		SCORE_MSG_1560
#define PADRAO_CONFIGURA_3		SCORE_MSG_1640

//#define PADRAO_RELGRAF_1		SCORE_MSG_1000
//#define PADRAO_RELGRAF_2		SCORE_MSG_1080
//#define PADRAO_RELGRAF_3		SCORE_MSG_1160
//#define PADRAO_RELGRAF_4		SCORE_MSG_1240
//#define PADRAO_RELGRAF_5		SCORE_MSG_1320
//#define PADRAO_OPERACAO_1		SCORE_MSG_1400
//#define PADRAO_OPERACAO_2		SCORE_MSG_1480
//#define PADRAO_CONFIGURA_1	SCORE_MSG_1560
//#define PADRAO_CONFIGURA_2	SCORE_MSG_1640

#define PADRAO_WINDOW_MENU		SCORE_MSG_1720
#define PADRAO_REL_TELA			SCORE_MSG_1726
#define NOME_SOPRAR				SCORE_MSG_1898
#define INCR_LINEAR				SCORE_MSG_1947
#define INCR_RAMPA				SCORE_MSG_1948

/* origem da mudanca do estado de alimentacao */
#define ORIGEM_CONTROLE			SCORE_MSG_258
#define ORIGEM_EXTERNA			SCORE_MSG_1952
#define ORIGEM_OPERADOR			SCORE_MSG_1953
#define ORIGEM_INVALIDA			SCORE_MSG_1954

/* Nome dos estados de alimentacao */
#define ALIM_PADRAO				SCORE_MSG_1955
/* -- Alteracao - Inicio - 01/08/2002 - Robson - EA ou Tempo ? -- */
#define ALIM_SUSPENSA_EA		SCORE_MSG_1956
#define ALIM_SUSPENSA_TEMPO		SCORE_MSG_2292
/* -- Alteracao - Fim - 01/08/2002 - Robson - EA ou Tempo ? -- */
#define ALIM_EA                 SCORE_MSG_282
#define ALIM_MANUAL             SCORE_MSG_421
#define ALIM_INVALIDA			SCORE_MSG_1954
#define ALIM_EXCECAO			SCORE_MSG_2023

/* Titulo e Cabecalho do Rel. instantaneo de Alimentacao (Point Feeder) */
#define TIT_REL_INS_ALIM_PF		SCORE_MSG_2026
#define HD1_REL_INS_ALIM_PF		SCORE_MSG_2027
#define HD2_REL_INS_ALIM_PF		SCORE_MSG_2028

/* Titulo e Cabecalho do Rel. instantaneo de Alimentacao (Barra Lateral) */
#define TIT_REL_INS_ALIM_BAR	SCORE_MSG_1960
#define HD1_REL_INS_ALIM_BAR	SCORE_MSG_1961	
#define HD2_REL_INS_ALIM_BAR	SCORE_MSG_1962	


#define CABEC_RINST				SCORE_MSG_1965

#define NOME_ROMPIDA			SCORE_MSG_1980
#define NOME_CONSERTO			SCORE_MSG_1981

#define NOME_FALHAMM			SCORE_MSG_1982

/* Acoes da tabela de supressao de EA */
#define NOME_ESPERAR			SCORE_MSG_1999
#define NOME_SUB_ROTINA_1		SCORE_MSG_2000
#define NOME_SUB_ROTINA_2		SCORE_MSG_2001
#define NOME_SUB_ROTINA_3		SCORE_MSG_2002
#define NOME_SUB_ROTINA_4		SCORE_MSG_2003
#define NOME_SUB_ROTINA_5		SCORE_MSG_2004
#define NOME_QUEBRADA_EXTERNA	SCORE_MSG_2005
#define NOME_QUEBRADA_INTERNA	SCORE_MSG_2006
#define NOME_TOCAR_SIRENE		SCORE_MSG_2007

/* Lados da cuba */
#define STR_LADO_INTERNO		SCORE_MSG_2012
#define STR_LADO_EXTERNO		SCORE_MSG_2013

#define LOG_CFG_HORA			SCORE_MSG_2020

#define NOME_TERM_CIMA			SCORE_MSG_591
#define NOME_TERM_BAIXO			SCORE_MSG_592

#endif
/* -- fim ScoreMsgs.h -- */

