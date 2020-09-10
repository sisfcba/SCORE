
/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.

	PROJETO		: TERMINAL SEALTOUCH

	SISTEMA		: GERAL

	ARQUIVO		: WindowsCBA.h

	CONTEUDO	: Definicoes gerais para as funcoes de tratamento dos
				  terminais SealTouch

	AUTOR		: Hevelton Araujo Junior

	VERSAO		: 00 - 09/07/92

	OBSERVACOES : Este arquivo foi gerado a partir do arquivo "windows.h"
				  da Klondike Software Inc.

	HISTORICO DAS EDICOES

-------------------------------------------------------------------------------
13/10/95 | Reorganizacao do prologo e prototipos de funcoes		| Carlos
-------------------------------------------------------------------------------
$Id: WindowsCBA.h,v 1.2 2004/07/28 20:00:10 leo Exp $

$Log: WindowsCBA.h,v $
Revision 1.2  2004/07/28 20:00:10  leo
Inclusao variavel de percentual de erro para comparacao de valores da
Atn1.4 reserva com a principal para a CBA em sistemas com 2 Atn1.4.

******************************************************************************/

#ifndef	WINDOWS_H_INCLUIDO
#define	WINDOWS_H_INCLUIDO

#include <Definicao.h>

/*--- Para acessar a ultima tecla digitada ---*/
#define	KeyScan		(key_scan)

/*--- Estrutura de uma janela ---*/
struct Window
{
	int		x;
	int		y;
	int		dx;
	int		dy;
	byte	border;
	byte	save;
	word	color;
	char	*zone;				/* points to a buffer */
};

/*--- Estrutura para exibicao de menus ---*/
struct Menu
{
	char	*entry;
	int		(*function)();    /* The function has 3 param: entry,x,y */
};

/*--- Estrutura para tratamento de entrada de dados ---*/
struct Form 
{
	char	*prompt;
	int		fx;
	int		fy;
	int		fdx;
	word	fcolor;
	char	*value;
	int		(*on_entry)();    /* The function has 4 param: window,value,x,y */
	int		(*on_exit)();     /* The function has 4 param: window,value,x,y */
	char	*storage;
	char	*format;
	int		(*error)();       /* The function has 4 param: storage,format,key,x */
};

/*--- Estrutura para teclas de funcao programaveis ---*/
struct Keyset
{
	char	*activator;
	int		(*onkey)();
};

#ifndef IN_WINDOWS
  extern byte	key_return[40];
  extern int	key_type;			/* Key type: 0 extended and non activator
												 1 activator, and
												 2 ASCII. */
  extern int	term_family;		/* Terminal type */
  extern word	key_scan;			/* The key scan code:
											bits 0-7 ASCII  8-15 zero
											bits 0-7 zero   8-15 extended */
  extern char	DELAYS[];
  extern int	CursorStatus;
  extern int	cursor_x;
  extern int	cursor_y;
#endif

#define NIL				0L

/* Tipos para inicializacao do ambiente TOOLKIT */
#define	PARCIAL			1
#define	TOTAL			2

/* Window borders: */
#define SINGLE			1
#define DOUBLE			2
#define THICK			3
#define NOBORDER		0

#define SAVE			1
#define NOSAVE			0

#define BLACK           0
#define BLACK_B         0

/* Character attributes: */
#define BLINK			0x0001
#define BOLD			0x0002
#define REVERSE			0x0004
#define UNDER			0x0008

/* Foreground colors: */
#define BLUE			0x8140
#define GREEN			0x8240
#define CYAN			0x8340
#define RED				0x8440
#define MAGENTA			0x8540
#define BROWN			0x8640
#define WHITE			0x8740

/* Background colors: */
#define BLUE_B			0x9040
#define GREEN_B			0xa040
#define CYAN_B			0xb040
#define RED_B			0xc040
#define MAGENTA_B		0xd040
#define BROWN_B			0xe040
#define WHITE_B			0xf040

/* Requester modes */
#define START_FORM		1
#define FORM			2
#define REQUEST			3

/* Menu positions: */
#define VERTICAL		0
#define HORIZONTAL		1

/* Directory list type: */
#define DIR				0x10
#define FILEONLY		0

/* Input driver definitions */
#define key_is(MNEMONIC)		(strcmp(key_return,MNEMONIC)==0)
#define ACTIVATOR				(key_type==1)
#define ASCII					(key_type==2)
#define EXTENDED				(key_scan & 0xff00)
#define get_key					(key_scan)
#define DELAY					0xff00

/* Terminal type definitions */
#define TTY						(term_family > 3)
#define COLOR_DISPLAY			(term_family < 3)
#define BW_DISPLAY				(term_family == 3)

/* Activators:
   WARNING: you can change them, but do not remove them!
            If you change them make sure that the module
            containing keys.h is recompiled */

/*--- tipo para acesso as janelas ---*/
typedef struct Window t_janela;


/****************************  FUNCOES COMUNS  *******************************

	- Funcoes comuns a biblioteca de funcoes da console (Console.lib)
	  e  do  Sealtouch  (Sealtouch.lib),   encontradas   no   arquivo
	  "OperacaoBib.c".

*****************************************************************************/

int LeString (t_janela *Janela, int X, int Y, int Tam,
									char *Dado, char *Prompt, unsigned Cor);
int ExibeMenu (struct Menu *PMenu, int Cor, int Direc,
									int NLins, int X, int Y, char *Titulo);
int LeSenha (t_janela *Jan, int X, int Y, int Tam, char *Dado);


/******************  FUNCOES ESPECIFICAS DE CHAMADA COMUM  *******************

	- Funcoes especificas das bibliotecas "Console.lib" e "Sealtouch.lib",
	  encontradas nos arquivos  "ConsoleCBA.c" e "SealtCBA.c"  respectiva-
	  mente. Essas funcoes apresentam a mesma chamada, entretanto interna-
	  mente o codigo e diferente.

*****************************************************************************/

t_janela *TrataTelaPadrao (int Funcao);
void EntDados (t_janela *W, struct Form *F, unsigned TIME, char *COMPLETE);
int  ExMenu (t_janela *W, struct Menu *Menu, unsigned Color, int Direction,
	 unsigned Time, unsigned Nlines, char *Title, int Confirm);
t_janela *OpenWindow(int X, int Y, int DX, int DY, int BORDER, int SAVEUNDER,
	 unsigned ATTRIBUTE);
void CloseWindow(t_janela *W);
void PaintWindow (t_janela *W, int X, int Y, int DX, int DY, unsigned C,
	 unsigned ATTRIBUTE);
void ClearWindow (t_janela *W, unsigned C);
void ClearFrame (t_janela *W, unsigned C);
void AbsSetCursor (int X, int Y);
void SetCursor (t_janela *W, int X, int Y);
void CursorOn (void);
void CursorOff (void);
void Display (t_janela *W, int X, int Y, char *STRING);
void DisplayN (t_janela *W, int X, int Y, char *STRING, int N);
void DispC (t_janela *W, int X, int Y, unsigned C);
void DispCN (t_janela *W, int X, int Y, unsigned C, int N);
void DispCA (t_janela *W, int X, int Y, unsigned C, unsigned ATTRIBUTE);
void DispCAN (t_janela *W, int X, int Y, unsigned C, unsigned ATTRIBUTE, int N);
void DispS (t_janela *W, int X, int Y, char *STRING);
void DispSN (t_janela *W, int X, int Y, char *STRING, int N);
void DispSA (t_janela *W, int X, int Y, char *STRING, unsigned ATTRIBUTE);
void DispSAN (t_janela *W, int X, int Y, char *STRING, unsigned ATTRIBUTE, int N);
void PutC (t_janela *W, int X, int Y, unsigned C);
void PutCN (t_janela *W, int X, int Y, unsigned C, int N);
void PutS (t_janela *W, int X, int Y, char *STRING);
void PutSN (t_janela *W, int X, int Y, char *STRING, int N);
void PutA (t_janela *W, int X, int Y, unsigned ATTRIBUTE);
void PutAN (t_janela *W, int X, int Y, unsigned ATTRIBUTE, int N);
int  PutI (t_janela *W, int X, int Y, int I);
void ScrollUp (t_janela *W, int X, int Y, int DX, int DY);
void ScrollDown (t_janela *W, int X, int Y, int DX, int DY);
void ScrollLeft (t_janela *W, int X, int Y, int DX, int DY);
void ScrollRight (t_janela *W, int X, int Y, int DX, int DY);
int  Requester (t_janela *W, int X, int Y, int DX, unsigned COLOR, char *PROMPT,
	 char *Value, int TYPE, int (*ONENTRY)(), int (*ONEXIT)(), unsigned TIME,
	 char *STORAGE, char *FORMAT, int (*ERROR)());


/********************** FUNCOES EXCLUSIVAS DE CONSOLE ************************

	- Funcoes exclusivas que fazem parte apenas da biblioteca
	  "Console.lib"

*****************************************************************************/

void define_key (struct Keyset *KEYSET);
void KSdelay (unsigned TICKS);
void KSrectangle (t_janela *W, int X, int Y, int DX, int DY, int BORDER,
	 unsigned ATTRIBUTE);
void EscreveAjuda(char *NomArq);
int KBhit (void);


#endif /* ifndef WINDOWS_H_INCLUIDO */
