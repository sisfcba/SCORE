/*         Copyright (c) 1987 by  Klondike Software Inc.
MODULE:    windows.h
AUTHOR:    Dominic N. Sotirescu
RELEASE:   1.0
CONTENT:   Structure definitions and defined symbols for the
           QNX version of the Toolkit.
_______________________________________________________________ */


struct Window {
  int  x;
  int  y;
  int  dx;
  int  dy;
  unsigned char border;
  unsigned char save;
  unsigned color;
  char *zone;       /* points to a buffer */
  };

struct Menu {
  char *entry;
  int (*function)();    /* The function has 3 param: entry,x,y */
  };

struct Form {
  char *prompt;
  int  fx;
  int  fy;
  int  fdx;
  unsigned fcolor;
  char *value;
  int (*on_entry)();    /* The function has 4 param: window,value,x,y */
  int (*on_exit)();     /* The function has 4 param: window,value,x,y */
                        /* and returns 0 if OK */
  char *storage;
  char *format;
/* MIG24            error Perhaps use vfprintf() and exit().  See Function */
/* MIG24                  Library Reference Manual for details. */
  int (*error)();       /* The function has 4 param: storage,format,key,x */
  };

struct Keyset {
  char *activator;
  int (*onkey)();
  };

#ifndef IN_WINDOWS
  extern unsigned char key_return[40];
  extern int key_type;  /* Key type: 0 extended and non activator
                                     1 activator, and
                                     2 ASCII. */
  extern int term_family;     /* Terminal type */
  extern unsigned key_scan;   /* The key scan code:
                                 bits 0-7 ASCII  8-15 zero
                                 bits 0-7 zero   8-15 extended */
  extern char DELAYS[];
  extern int cursor_status, cursor_x, cursor_y;
#endif

#define NIL             0L

/* Window borders: */
#define SINGLE          1
#define DOUBLE          2
#define THICK           3
#define NOBORDER        0

#define SAVE            1
#define NOSAVE          0

/* Character attributes: */
#define BLINK           0x0001
#define BOLD            0x0002
#define REVERSE         0x0004
#define UNDER           0x0008

/* Foreground colors: */
#define BLUE            0x8140
#define GREEN           0x8240
#define CYAN            0x8340
#define RED             0x8440
#define MAGENTA         0x8540
#define BROWN           0x8640
#define WHITE           0x8740

/* Background colors: */
#define BLUE_B          0x9040
#define GREEN_B         0xa040
#define CYAN_B          0xb040
#define RED_B           0xc040
#define MAGENTA_B       0xd040
#define BROWN_B         0xe040
#define WHITE_B         0xf040

/* Requester modes */
#define START_FORM      1
#define FORM            2
#define REQUEST         3

/* Menu positions: */
#define VERTICAL        0
#define HORIZONTAL      1

/* Directory list type: */
#define DIR             0x10
#define FILEONLY        0

/* Input driver definitions */
#define key_is(MNEMONIC)        (strcmp(key_return,MNEMONIC)==0)
#define ACTIVATOR               (key_type==1)
#define ASCII                   (key_type==2)
#define EXTENDED                (key_scan & 0xff00)
#define get_key                 (key_scan)
#define DELAY                   0xff00

/* Terminal type definitions */
#define TTY                     (term_family > 3)
#define COLOR_DISPLAY           (term_family < 3)
#define BW_DISPLAY              (term_family == 3)

/* Activators:
   WARNING: you can change them, but do not remove them!
            If you change them make sure that the module
            containing keys.h is recompiled */

#define RETURN          0x000d
#define HOME            0xa000
#define END             0xa800
#define UP              0xa100
#define DOWN            0xa900
#define LEFT            0xa400
#define RIGHT           0xa600
#define PAGE_UP         0xa200
#define PAGE_DOWN       0xaa00
#define EXIT            0x001b
#define INSERT          0xab00
#define DELETE          0xac00
#define RUBOUT          0x007f
#define BACKSPACE       0x0008
#define TAB             0x0009
#define BACKTAB         0x8000
#define F1              0x8100
#define F2              0x8200
#define F3              0x8300
#define F4              0x8400
#define F5              0x8500
#define F6              0x8600
#define F7              0x8700
#define F8              0x8800
#define F9              0x8900
#define F10             0x8a00

/****************************************************************************
 *
 * WINDOWING FUNCTION PROTOTYPES
 */

int  start_windows(void);
void end_windows(void);
struct Window *open_window(int X, int Y, int DX, int DY, int BORDER, int SAVEUNDER, unsigned ATTRIBUTE);
void close_window(struct Window *W);
void KSrectangle (struct Window *W, int X, int Y, int DX, int DY, int BORDER, unsigned ATTRIBUTE);
void paint_window (struct Window *W, int X, int Y, int DX, int DY, unsigned C, unsigned ATTRIBUTE);
void clear_window (struct Window *W, unsigned C);
void abs_set_cursor (int X, int Y);
void set_cursor (struct Window *W, int X, int Y);
void cursor_on (void);
void cursor_off (void);

void display (struct Window *W, int X, int Y, char *STRING);
void displayn (struct Window *W, int X, int Y, char *STRING, int N);

void disp_c (struct Window *W, int X, int Y, unsigned C);
void disp_cn (struct Window *W, int X, int Y, unsigned C, int N);
void disp_ca (struct Window *W, int X, int Y, unsigned C, unsigned ATTRIBUTE);
void disp_can (struct Window *W, int X, int Y, unsigned C, unsigned ATTRIBUTE, int N);
void disp_s (struct Window *W, int X, int Y, char *STRING);
void disp_sn (struct Window *W, int X, int Y, char *STRING, int N);
void disp_sa (struct Window *W, int X, int Y, char *STRING, unsigned ATTRIBUTE);
void disp_san (struct Window *W, int X, int Y, char *STRING, unsigned ATTRIBUTE, int N);

void put_c (struct Window *W, int X, int Y, unsigned C);
void put_cn (struct Window *W, int X, int Y, unsigned C, int N);
void put_s (struct Window *W, int X, int Y, char *STRING);
void put_sn (struct Window *W, int X, int Y, char *STRING, int N);
void put_a (struct Window *W, int X, int Y, unsigned ATTRIBUTE);
void put_an (struct Window *W, int X, int Y, unsigned ATTRIBUTE, int N);
int  put_i (struct Window *W, int X, int Y, int I);

void scroll_up (struct Window *W, int X, int Y, int DX, int DY);
void scroll_down (struct Window *W, int X, int Y, int DX, int DY);
void scroll_left (struct Window *W, int X, int Y, int DX, int DY);
void scroll_right (struct Window *W, int X, int Y, int DX, int DY);

/****************************************************************************
 *
 * ALL OTHER FUNCTIONS
 */

int  next_key (unsigned TIME);
void define_key (struct Keyset *KEYSET);
int  requester (struct Window *W, int X, int Y, int DX, unsigned COLOR, char *PROMPT, char *Value,
                       int TYPE, int (*ONENTRY)(), int (*ONEXIT)(), unsigned TIME, char *STORAGE, char *FORMAT, int (*ERROR)());
int  menu (struct Window *W, struct Menu *MENU, unsigned COLOR, int DIRECTION, unsigned TIME);
int  smenu (struct Window *W, unsigned COLOR, char *(*GET_ENTRY)(), unsigned TIME, int (*ONSELECTION)());
void form (struct Window *W, struct Form *F, unsigned TIME, char *COMPLETE);
void edit (struct Window *W, long FIRSTLINE, int X, int Y, int (*GET)(), int (*UPDATE)(),
                  int (*DEL)(), int (*CREATE)(), unsigned Delay);
void FileEdit (char *FName, char *Save, int x, int y, int dx, int dy, int Border, unsigned Color, unsigned Delay);
void quicksort (char *LIST[], int N, int (*COMP)());
int  find_first (char *PATH, int TYPE, char *NAME);
int  find_next (char *NAME);
int  Finder (char *Path, char *Filename, int Nchar, int NType, int X, int Y, int DX, int DY,
             int Border, unsigned Color, unsigned Delay, char *Drives);
void KSdelay (unsigned TICKS);
int  KSutoa (char *STRING, unsigned U, int N);
unsigned reverse_attr (unsigned ATTRIBUTE);
