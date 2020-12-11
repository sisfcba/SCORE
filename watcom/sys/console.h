/*
 *  console.h    "Public" Definitions for the console driver
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __CONSOLE_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif
#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

struct _console_ctrl {
    mpid_t           driver;
    short unsigned  driver_spare;
    short unsigned  handle;
    short unsigned  mode;
    short unsigned  console;
    mpid_t           driver_pid;
    short unsigned  driver_pid_spare;
    nid_t           driver_nid;
    short int       fd;
    short unsigned  zero[6];
    } ;

struct _console_info {
    /*
     * The following are available in 4.10+
     */
    short unsigned  console;    /* Console number [1..N] */
    unsigned char   type;       /* Type of console device */
    unsigned char   protocol;   /* Type of esc sequences supported */
    short unsigned  flags;      /* Miscellaneous flag bits */
    short int       max_fonts;  /* Maximum number of loadable fonts */
    short int       font;       /* current font [0..N-1] */
    short int       rows;       /* current # rows */
    short int       cols;       /* current # columns */
    short unsigned  zero[8];
    } ;

struct _console_font {
    short int       srows;
    short int       scols;
    short int       crows;
    short unsigned  ctype[3];
#ifdef __386__
    unsigned short  cg_lo_off;
    unsigned short  cg_lo_seg;
    unsigned short  cg_hi_off;
    unsigned short  cg_hi_seg;
#else
    char            far *cg_lo;
    char            far *cg_hi;
#endif
    short unsigned  flags;
    short unsigned  gmode;
    short unsigned  zero[4];
    } ;

struct _console_compose {
    unsigned char   key1;       /* First char of compose sequence */
    unsigned char   key2;       /* Second char of compose sequence */
    unsigned char   pckey;      /* Resulting char for PC charset */
    unsigned char   ansikey;    /* Resulting char for ANSI/ISO charset */
    } ;

/*
 * Types allowed for console_info()
 */
#define _CON_TYPE_STANDARD  0   /* Is a standard text-mode console device */
#define _CON_TYPE_QWIN      1   /* Is a QNX Windows console device */

/*
 * Protocol supported in console_info()
 */
#define _CON_PROT_QNX4      0   /* Suppoprts standard QNX4 escape sequences */
#define _CON_PROT_ANSI      1   /* Supports ANSI escape sequences */

/*
 * Flag bits in console_info()
 */
#define _CON_FLAG_NOKEYBOARD   0x0001  /* No physical keyboard attached */
#define _CON_FLAG_NOMONITOR    0x0002  /* No physical display adapter/monitor  */
#define _CON_FLAG_BEEPADJUST   0x0010  /* Supports ESC sequence to adjust beep */

/*
 * Types of console events which will cause console_arm() to return
 */
#define _CON_EVENT_OUTPUT   0x0001
#define _CON_EVENT_SIZE     0x0002
#define _CON_EVENT_INACTIVE 0x0004
#define _CON_EVENT_ACTIVE   0x0008
#define _CON_EVENT_DEBUG    0x0010

/*
 * Cursor types
 */
#define CURSOR_OFF          0
#define CURSOR_UNDERLINE    1
#define CURSOR_BLOCK        2

/*
 * Console font flags
 */
#define _CON_FONT_ANSI      0x0001

/*
 * Console control options
 */
#define CONSOLE_NOBOOT      0x0001
#define CONSOLE_NOSWITCH    0x0002
#define CONSOLE_NODEBUG     0x0004
#define CONSOLE_NORESIZE    0x0008
#define CONSOLE_NOHOTKEY    0x0010
#define CONSOLE_INVISIBLE   0x0020
#define CONSOLE_NOHSCROLL   0x0040
#define CONSOLE_NOCOLOR     0x0100
#define CONSOLE_MONOCURS    0x0200
#define CONSOLE_SCANMODE    0x0400
#define CONSOLE_EXTMODE     0x0800

#ifdef __cplusplus
extern "C" {
#endif
extern struct _console_ctrl *console_open( int fd, unsigned mode );
extern int console_close( struct _console_ctrl *cc );
extern int console_active( struct _console_ctrl *cc, int console );
extern int console_font( struct _console_ctrl *cc, int console, int font );
extern int console_info( struct _console_ctrl *cc, int console, struct _console_info *info );
extern int console_size( struct _console_ctrl *cc, int console,
                  int set_rows, int set_cols, int *rows, int *cols );
extern int console_arm( struct _console_ctrl *cc, int console,
                 pid_t proxy, unsigned events );
extern unsigned console_state( struct _console_ctrl *cc, int console,
                        unsigned bits, unsigned mask );
extern unsigned console_ctrl( struct _console_ctrl *cc, int console,
                       unsigned bits, unsigned mask );
extern int console_read( struct _console_ctrl *cc, int console,
                  unsigned offset, unsigned char *buf, int n,
                  int *row, int *col, int *type );
extern int console_write( struct _console_ctrl *cc, int console,
                   unsigned offset, const unsigned char *buf, int n,
                   int *row, int *col, int *type );
extern int console_protocol( struct _console_ctrl *cc, int console, int protocol );
#ifdef __cplusplus
};
#endif

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __CONSOLE_H_INCLUDED
#endif
