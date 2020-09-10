
/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.

	PROJETO		: TERMINAL SEALTOUCH

	SISTEMA		: GERAL

	ARQUIVO		: sealtouch.h

	CONTEUDO	: Definicoes gerais para o SealTouch

	AUTOR		: Hevelton Araujo Junior

	VERSAO		: 00 - 12/08/92

	HISTORICO DAS EDICOES
	00 - Edicao Inicial										09/07/92 - H.Junior
	01 - Padronizacao para console/SealTouch				12/08/92 - H.Junior

-------------------------------------------------------------------------------
13/10/95 | Reorganizacao do prologo e prototipos de funcoes		| Carlos
-------------------------------------------------------------------------------
******************************************************************************/

#ifndef	SEALTOUCH_H_INCLUIDO
#define	SEALTOUCH_H_INCLUIDO

	/************************/
	/* INCLUSAO DE ARQUIVOS */
	/************************/

//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
//#include <errno.h>
//#include <WindowsCBA.h>
//#include <Definicao.h>


	/**********************************/
	/* DEFINICAO DE CONSTANTES/MACROS */
	/**********************************/

/* Numero das paginas de operacao no SealTouch */
#define	PAGINA_LIVRE						13
#define	PAG_TECL_NUMERICO					14
#define	PAG_REL_PAGINA_TOTAL				15
#define	PAG_REL_PAGINA_PARCIAL				16
#define	PAG_REL_SEM_PAGINACAO				17
#define	PAG_REL_PAGINA_CUBAS				18
#define	PAG_REL_INSTANTANEO					19

/* Tipos de teclado numerico */
#define	ST_VERTICAL							1
#define	ST_HORIZONTAL						2

/* Codigo da tecla para reinicializas o SealTouch */
#define	ST_COD_REINICIALIZAR				0x9A

/* Tamanho dos caracteres disponiveis */
#define	ST_CARACTERE_NORMAL					1
#define	ST_CARACTERE_DUPLO					2
#define	ST_CARACTERE_TRIPLO					3
#define	ST_CARACTERE_QUATRO					4

/* Numero de colunas para cada tipo de caractere */
#define	ST_NUM_COLS_NORMAL					80
#define	ST_NUM_COLS_DUPLO					40
#define	ST_NUM_COLS_TRIPLO					24
#define	ST_NUM_COLS_QUATRO					12

/* Numero de linhas para cada tipo de caractere */
#define	ST_NUM_LINS_NORMAL					24
#define	ST_NUM_LINS_DUPLO					12
#define	ST_NUM_LINS_TRIPLO					 6
#define	ST_NUM_LINS_QUATRO					 3

/* Numero do primeiro botao para o teclado numerico */
#define	ST_PRI_BOT_TEC						20

/* Numero de botoes do teclado numerico */
#define	ST_NUM_BOTOES_TECLADO				18

/* Indica o que foi recebido do SealTouch */
#define	ST_ASCII							2
#define	ST_BOTAO							3
#define	ST_CONTROL							4

/* Iniciaador/terminador de resposta */
#define	ST_INI_RSP							"\020\002"
#define	ST_FIM_RSP							"\020\003"

/* CR e LF */
#define	ST_CR_LF							"\015\012"

/* Comandos para o SealTouch */

/* Iniciadores de comando */
#define	CSI						"\033["
#define	DCS						"\033P"

/* Terminador de comandos */
#define	ST						"\033\\"

/* Posicionar o cursor na linha/coluna 0 */
#define	ST_CURSOR_HOME			"\033[H"

/* Limpar a tela */
#define	ST_LIMPAR_TELA			"\033[2J"

/* Definir um botao */
#define	ST_DEF_BOTAO			"\033[>"

/* Definir resposta/label para um botao */
#define	ST_DEF_RESP				"\033P~"

/* Programar os modos de um botao */
#define	ST_PROG_BOT				"\033[>"

/* Apagar um botao */
#define	ST_APAGA_BOT			"\033[>"

/* Apagar todos botoes/respostas/paginas */
#define	ST_APAGA_TODOS_BOT		"\033[>B"

/* Mudar o caractere para escrita */
#define	ST_MUDA_CARAC			"\033[<"

/* Desligar o cursor */
#define	ST_DESL_CURSOR			"\033[?25l"

/* Ler status da impressora do SealTouch */
#define	ST_LE_STTS_IMP			"?15n"

/* Habilitar impressora para imprimir */
#define	ST_HAB_IMPRESSAO		"5i"

/* Desabilitar impressora para imprimir */
#define	ST_DESABILITA_IMP		"4i"

/* Modo grafico - PARA DESABILITAR IMPRESSAO DO SEALTOUCH SEM TRAVAR */
#define	ST_MODO_GRAFICO			"\033K\004\000"

/* Ligar o cursor */
#define	ST_LIGA_CURSOR			"\033[?25h"

/* Desenhar uma linha */
#define	ST_DRAW_LINE_ABS		"\033P2G"

/* Escrever no modo complemento (tela = novo XOR velho) grafico */
#define	ST_GRAPH_MODE_COMPL		"\033P20G1\033\\"

/* Modo de preenchimento de objetos graficos  - todo branco */
#define	ST_GRAPH_FILL_WHITE		"\033P19G1\033\\"

/* Escrever no modo substituicao (tela = novo) grafico */
#define	ST_GRAPH_MODE_REPLACE	"\033P20G0\033\\"

/* Modo de preenchimento de objetos graficos  - todo preto */
#define	ST_GRAPH_FILL_BLACK		"\033P19G0\033\\"

/* Programa habilitacao ou nao do teclado alfanumerico */
#define	ST_PROG_TECLADO			"\033[>33"

/* Liga/desliga o teclado alfanumerico */
#define	ST_TECLADO_ON_OFF		"\033[>32"

/* Comando para desenhar um retangulo preenchido */
#define	ST_BLOCK_FILL			"\033P8G"

/* Modificar o tipo de linha */
#define	ST_GRAPH_LINE_STYLE		"\033P18G"

/* Modos de programacao para varios comandos */
#define	SET						"h"
#define	CLEAR					"l"

/* Modos de programacao dos botoes */
#define	BUTTON_ENABLE			23
#define	BUTTON_AUTODRAW			24
#define	BUTTON_MODE				25
#define	BUTTON_HIGHLIGHT		26
#define	BUTTON_BEEP				27
#define	CLEAR_ON_PAGE			28
#define	BUTTON_ZERO				29
#define	BUTTON_LABEL_PACK		40


/* DEFINICOES PARA TERMINAL SEALTOUCH */

/* Caractere espaco */
#define	ST_TECLA_ESPACO						" "

/* Linha para titulo dos menus */
#define	ST_LIN_TITULO_MENUS					1

/* Linha inicial e final do primeiro botao de cada menu */
#define	ST_LIN_INI_MENU						36
#define	ST_LIN_FIM_MENU						40

/* Numero de caracteres a acrescentar para textos das opcoes */
#define	ST_OFFSET_TAMANHO					20

/* Numero de caracters a subtrair para alinhar opcoes */
#define	ST_OFFSET_ESPACOS					5

/* Offset a partir da margem esquerda para escrever opcao */
#define	ST_OFFSET_OPCAO						14

/* Tamanho de cada botao em linhas - 1 */
#define	ST_OFFSET_TAM_BOTAO					4

/* Tamanho do caractere para escrever numeros do menu */
#define	ST_TAM_LBL_MENU						0

/* Numero do botao de confirmacao */
#define	ST_BOT_CNF							9

/* Numero do botao de reconhece todos */
#define ST_BOT_RECT							10
#define ST_BOT_REC							11

/* Numero dos botoes de SIM/NAO */
#define	ST_BOT_SIM							12
#define	ST_BOT_NAO							13

/* Numero do botao para continuar */
#define	ST_BOT_CNT							14

/* Posicao do botao de confirma */
#define	ST_X1_CNF							65
#define	ST_X2_CNF							75
#define	ST_Y1_CNF							20
#define	ST_Y2_CNF							28

/* Posicao do botao de reconhece todos */
#define	ST_X1_RECT							66
#define	ST_X2_RECT							73
#define	ST_Y1_RECT							 1
#define	ST_Y2_RECT							 5

/* Posicao do botao de reconhece individual */
#define	ST_X1_REC							73
#define	ST_X2_REC							80
#define	ST_Y1_REC							 1
#define	ST_Y2_REC							 5

/* Posicao do botao de SIM */
#define	ST_SIM_X1							35
#define	ST_SIM_X2							43
#define	ST_SIM_Y1							5
#define	ST_SIM_Y2							10

/* Posicao do botao de NAO */
#define	ST_NAO_X1							45
#define	ST_NAO_X2							53
#define	ST_NAO_Y1							5
#define	ST_NAO_Y2							10

/* Posicao do botao de CONTINUAR */
#define	ST_CNT_X1							50
#define	ST_CNT_X2							65
#define	ST_CNT_Y1							5
#define	ST_CNT_Y2							10

/* Tamanho do caractere para escrever no botao de confirma */
#define	ST_TAM_CNF							0

/* Tamanho do caractere para escrever nos botoes de reconhecimento */
#define	ST_TAM_REC							0
#define	ST_TAM_RECT							0

/* Resposta do botao de confirma */
#define	ST_RSP_CNF							"\\BB"

/* Reposta do botao de reconhece todos */
#define	ST_RESP_RECT						"\\B9"
#define	ST_RECONHECE_TODOS					0xB9

/* Reposta do botao de reconhece indivudual */
#define	ST_RESP_REC							"\\BA"
#define	ST_RECONHECE						0xBA

/* Label do botao de confirma */
#define	ST_LBL_CNF							"CONFIRMA^M^MOPCAO"

/* Label do botao de reconhece todos */
#define	ST_LABEL_RECT						"REC^MTODOS"

/* Label do botao de reconhece individual */
#define	ST_LABEL_REC						"REC"

/* Macro para indicar se escolha foi de opcao do menu */
#define	ST_ESCOLHA_MENU						( get_key <= 0x08 )

/* Macro para indicar se escolha foi do botao de confirmacao */
#define	ST_ESCOLHA_CONFIRMACAO				( get_key eq 0xBB )

/* Macro para indicar se escolha foi do botao de reconhece todos */
#define	ST_ESCOLHA_REC_TODOS				( get_key eq 0xB9 )

/* Macro para indicar se escolha foi do botao de reconhece individual */
#define	ST_ESCOLHA_REC_INDIVIDUAL			( get_key eq 0xBA )

/* Caracteres do protocolo do SealTouch */
#define	_DLE								0x10
#define	_STX								0x02
#define	_ETX								0x03

/* Estados do automato do SealTouch */
#define	REPOUSO								0
#define	ESP_STX								1
#define	ESP_TXT								2
#define	ESP_ETX								3
#define	ESP_CTR								4


	/*************************************************************/
	/* VARIAVEIS GLOBAIS - SO DEFINE SE FOR NO PROGRAM PRINCIPAL */
	/*************************************************************/

#ifdef PROGRAMA_PRINCIPAL

/* Posicao/tamanho/resposta/label do teclado numerico */

int ST_VER_X1_BOT_TEC[] =
	{ 59, 59, 59, 59, 59, 59, 64, 64, 64, 64, 64, 64, 69, 69, 69, 69, 69, 69 };
int ST_VER_X2_BOT_TEC[] =
	{ 64, 64, 64, 64, 64, 64, 69, 69, 69, 69, 69, 69, 74, 74, 74, 74, 74, 74 };
int ST_VER_Y1_BOT_TEC[] =
	{  5, 12, 19, 26, 33, 40,  5, 12, 19, 26, 33, 40,  5, 12, 19, 26, 33, 40 };
int ST_VER_Y2_BOT_TEC[] =
	{ 12, 19, 26, 33, 40, 47, 12, 19, 26, 33, 40, 47, 12, 19, 26, 33, 40, 47 };
int ST_HOR_X1_BOT_TEC[] =
	{ 59, 59, 59, 59, 59, 59, 64, 64, 64, 64, 64, 64, 69, 69, 69, 69, 69, 69 };
int ST_HOR_X2_BOT_TEC[] =
	{ 64, 64, 64, 64, 64, 64, 69, 69, 69, 69, 69, 69, 74, 74, 74, 74, 74, 74 };
int ST_HOR_Y1_BOT_TEC[] =
	{  5, 12, 19, 26, 33, 40,  5, 12, 19, 26, 33, 40,  5, 12, 19, 26, 33, 40 };
int ST_HOR_Y2_BOT_TEC[] =
	{ 12, 19, 26, 33, 40, 47, 12, 19, 26, 33, 40, 47, 12, 19, 26, 33, 40, 47 };
int ST_TAM_LABEL_BOT_TEC[] =
	{  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  0,  0,  1,  1,  1 };
char *ST_RESPOSTA_BOT_TEC[] =
	{ "\\ff\\00", "\\1b", "\\ff\\a1", "7", "4", "1",
			 "-",    ".",        "0", "8", "5", "2",
	  "\\ff\\b8", "\\ff\\af", "\\ff\\a9", "9", "6", "3"
	};
char *ST_LABEL_BOT_TEC[] =
	{ "LMP", "SAI", "ANT", "7", "4", "1",
	    "-",   ".",   "0", "8", "5", "2",
	  "CNF", "AJD", "PRX", "9", "6", "3"
	};

int _CursorX, _CursorY;

#else

extern int _CursorX, _CursorY;
extern int ST_VER_X1_BOT_TEC[];
extern int ST_VER_X2_BOT_TEC[];
extern int ST_VER_Y1_BOT_TEC[];
extern int ST_VER_Y2_BOT_TEC[];
extern int ST_HOR_X1_BOT_TEC[];
extern int ST_HOR_X2_BOT_TEC[];
extern int ST_HOR_Y1_BOT_TEC[];
extern int ST_HOR_Y2_BOT_TEC[];
extern int ST_TAM_LABEL_BOT_TEC[];
extern char *ST_RESPOSTA_BOT_TEC[];
extern char *ST_LABEL_BOT_TEC[];

#endif	/* ifdef PROGRAMA_PRINCIPAL */

//#ifdef _CURSOR_XY_EXTERN
//  extern int _CursorX, _CursorY;
//#else
//  int _CursorX, _CursorY;
//#endif

/********************** FUNCOES EXCLUSIVAS DO SEALTOUCH **********************

	- Funcoes exclusivas que fazem parte apenas da biblioteca
	  "Sealtouch.lib"

*****************************************************************************/

int PutsST (char *Texto);
int PutST (char *Buffer, word NBytes);
void ClrScr (void);
void PosicionaCursor (int X , int Y);
void Home (void);
void DefBotao (int Num, int X1, int Y1, int X2, int Y2, int Tam, char *Resp, char *Label, int Tipo);
void ProgramaBotoes (int Programa , char *Modo);
void ApagaBotao (int Num);
void ApagaTodosBotoes (void);
void MudaCaractere (int Modo);
void DesligaCursor (void);
void LigaCursor (void);
void MudaAtributo (int Attr);
void ReverteArea (int X1 , int Y1 , int X2 , int Y2);
void MudaTipoLinha (int Tipo);
void ProgramaTeclado (char *Modo);
void TecladoOnOff (char *Modo);
int EscLinhaST (int Lin, int Col, char *Texto, char *Disp);
int OpenImpST (char *Disp, char *Texto);
int OpenImpLnST (char *Disp, char *Texto);
int ImprimeST (FILE *FDisp, int Semaforo, char *Texto);
int ImprimeLnST (FILE *FDisp, int Semaforo, char *Texto);
void EscreveXY (t_janela *Jan, int Col, int Lin, char *Texto);
void EscreveXYN (t_janela *Jan, int Col, int Lin, char *Texto, int NCars);
int EscAlarmeST (int Lin, int Col, char *Texto, char *Disp, int Modo);
void EscXYGrande (t_janela *Jan, int Col, int Lin, char *Texto);
void EsperaLiberacao (void);
void CriaTecladoFuncao (int Tipo);
void SetCurPage (int Page);


#endif /* IFDEF SEALTOUCH_H_INCLUIDO */

