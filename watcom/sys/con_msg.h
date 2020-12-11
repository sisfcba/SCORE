/*
 *  con_msg.h   Definitions for the console driver
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __CON_MSG_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#ifndef __CONSOLE_H_INCLUDED
 #include <sys/console.h>
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

/*
 *  Message types
 */

#define _CONSOLE_OPEN           0x0380
#define _CONSOLE_CLOSE          0x0381
#define _CONSOLE_ACTIVE         0x0382
#define _CONSOLE_FLUSH          0x0383
#define _CONSOLE_QUERY          0x0384
#define _CONSOLE_WRITE          0x0385
#define _CONSOLE_READ           0x0386
#define _CONSOLE_ARM            0x0387
#define _CONSOLE_SIZE           0x0388
#define _CONSOLE_OPTIONS        0x0389
#define _CONSOLE_STATE          0x038A
#define _CONSOLE_HOTKEY         0x038B
#define _CONSOLE_GETKBMAP       0x038C
#define _CONSOLE_SETKBMAP       0x038D
#define _CONSOLE_GETFONT        0x038E
#define _CONSOLE_SETFONT        0x038F
#define _CONSOLE_SFONT          0x0390
#define _CONSOLE_INFO           0x0391
#define _CONSOLE_PROTOCOL       0x0392
#define _CONSOLE_GETCOMPOSE     0x0394
#define _CONSOLE_SETCOMPOSE             0x0395

/*
 * Message formats
 */

struct _console_open {
    msg_t                   type;
    short unsigned          mode;
    short int               fd;
    short unsigned          zero;
    } ;

struct _console_open_reply {
    msg_t                   status;
    short unsigned          handle;
    short unsigned          zero[2];
    } ;

struct _console_close {
    msg_t                   type;
    short unsigned          handle;
    short unsigned          zero[2];
    } ;

struct _console_close_reply {
    msg_t                   status;
    short unsigned          zero[2];
    } ;

struct _console_cinfo {
    msg_t                   type;
    short unsigned          handle;
    short int               console;
    short unsigned          zero[2];
    } ;

struct _console_cinfo_reply {
    msg_t                   status;
    short unsigned          zero[3];
    struct _console_info    info;
    } ;

struct _console_active {
    msg_t                   type;
    short unsigned          handle;
    short int               console;
    short unsigned          zero[2];
    } ;

struct _console_active_reply {
    msg_t                   status;
    short int               old_active;
    short int               num_open;
    short int               num_consoles;
    short int               zero[2];
    } ;

struct _console_query {
    msg_t                   type;
    short unsigned          handle;
    short int               console;
    short unsigned          zero[2];
    } ;

struct _console_query_reply {
    msg_t                   status;
    short unsigned          attributes;
    short unsigned          screen_type;
    short unsigned          screen_seg;
    short int               zero[4];
    } ;

struct _console_write {
    msg_t                   type;
    short unsigned          handle;
    short int               console;        /* 0 means visible console */
    short int               curs_row;       /* -1 means don't change */
    short int               curs_col;       /* -1 means don't change */
    short int               curs_type;      /* -1 means don't change */
    short unsigned          offset;
    short unsigned          nbytes;
    short unsigned          zero[2];
    unsigned char           data[1]; /* variable length */
    } ;

struct _console_write_reply {
    msg_t                   status;
    short int               console;        /* Real console number */
    short int               curs_row;
    short int               curs_col;
    short int               curs_type;
    short unsigned          zero[2];
    } ;

struct _console_read {
    msg_t                   type;
    short unsigned          handle;
    short int               console;
    short unsigned          offset;
    short unsigned          nbytes;
    short unsigned          zero[2];
    } ;

struct _console_read_reply {
    msg_t                   status;
    short int               console;
    short int               curs_row;
    short int               curs_col;
    short int               curs_type;
    short int               height;
    short int               width;
    short unsigned          offset;
    short unsigned          nbytes;
    short unsigned          zero[2];
    unsigned char           data[1]; /* variable length */
    } ;

struct _console_arm {
    msg_t                   type;
    short unsigned          handle;
    short int               console;
    short unsigned          events;
    mpid_t                   proxy;
    mpid_t                   proxy_spare;
    short unsigned          zero[3];
    } ;

struct _console_arm_reply {
    msg_t                   status;
    short int               console;
    short unsigned          zero[2];
    } ;

struct _console_state {
    msg_t                   type;
    short unsigned          handle;
    short int               console;
    short unsigned          mask;
    short unsigned          bits;
    short unsigned          zero[2];
    } ;

struct _console_state_reply {
    msg_t                   status;
    short int               console;
    short unsigned          oldbits;
    short unsigned          zero[2];
    } ;

struct _console_size {
    msg_t                   type;
    short int               console;
    short unsigned          handle;
    short unsigned          rows;
    short unsigned          columns;
    short unsigned          zero[2];
    } ;

struct _console_size_reply {
    msg_t                   status;
    short int               console;
    short unsigned          rows;
    short unsigned          columns;
    short unsigned          zero[2];
    } ;

struct _console_protocol {
    msg_t                   type;
    short int               console;
    short unsigned          handle;
    short int               protocol;
    short unsigned          zero[3];
    } ;

struct _console_protocol_reply {
    msg_t                   status;
    short int               console;
    short unsigned          zero[3];
    short int               protocol;
    } ;

struct _console_sfont {
    msg_t                   type;
    short int               console;
    short unsigned          handle;
    short int               font;
    short unsigned          zero[3];
    } ;

struct _console_sfont_reply {
    msg_t                   status;
    short int               console;
    short unsigned          zero[3];
    short int               font;
    } ;

struct _console_options {
    msg_t                   type;
    short unsigned          handle;
    short int               console;
    short unsigned          bits;
    short unsigned          mask;
    short unsigned          zero[2];
    } ;

struct _console_options_reply {
    msg_t                   status;
    short int               console;
    short unsigned          oldbits;
    short unsigned          zero[2];
    } ;

struct _console_hotkey {
    msg_t                   type;
    short unsigned          handle;
    short int               console;
    short unsigned          zero[2];
    } ;

struct _console_hotkey_reply {
    msg_t                   status;
    short int               console;
    short int               key;
    short unsigned          zero[2];
    } ;

struct _console_getkbmap {
    msg_t                   type;
    short unsigned          handle;
    short unsigned          zero[2];
    } ;

struct _console_getkbmap_reply {
    msg_t                   status;
    short unsigned          zero[2];
    short int               nwords;
    short unsigned          data[1];  /* variable size, 'nwords' long */
    } ;

struct _console_setkbmap {
    msg_t                   type;
    short unsigned          handle;
    short unsigned          zero[2];
    short int               nwords;
    short unsigned          data[1];  /* variable size, 'nwords' long */
    } ;

struct _console_setkbmap_reply {
    msg_t                   status;
    short unsigned          zero[3];
    } ;

struct _console_getfont {
    msg_t                   type;
    short unsigned          handle;
    short unsigned          zero[2];
    short int               font;
    } ;

struct _console_getfont_reply {
    msg_t                   status;
    short unsigned          zero[3];
    short int               font;
    struct _console_font    fontdata;
    } ;

struct _console_setfont {
    msg_t                   type;
    short unsigned          handle;
    short unsigned          zero[2];
    short int               font;
    struct _console_font    fontdata;
    } ;

struct _console_setfont_reply {
    msg_t                   status;
    short int               font;
    short unsigned          zero[2];
    } ;

struct _console_getcompose {
    msg_t                   type;
    short unsigned          handle;
    short unsigned          zero[2];
    } ;

struct _console_getcompose_reply {
    msg_t                   status;
    short unsigned          zero[2];
    short int               num;
    struct _console_compose data[1];  /* variable size, 'num' elements */
    } ;

struct _console_setcompose {
    msg_t                   type;
    short unsigned          handle;
    short unsigned          zero[2];
    short int               num;
    struct _console_compose data[1];  /* variable size, 'num' elements */
    } ;

struct _console_setcompose_reply {
    msg_t                   status;
    short unsigned          zero[3];
    } ;

struct _console_flush {
    msg_t                   type;
    short unsigned          handle;
    short unsigned          zero[2];
    } ;

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __CON_MSG_H_INCLUDED
#endif
