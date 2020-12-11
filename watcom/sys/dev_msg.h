/*
 *  devmsgs.h   "Public" Device Driver Messages
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __DEV_MSG_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#ifndef _TERMIOS_H_INCLUDED
 #include <termios.h>
#endif

#ifndef __DEV_H_INCLUDED
 #include <sys/dev.h>
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

/*
 *  Message types
 */

#define _DEV_TCGETATTR          0x0310
#define _DEV_TCSETATTR          0x0311
#define _DEV_TCSENDBREAK        0x0312
#define _DEV_TCDRAIN            0x0313
#define _DEV_TCFLUSH            0x0314
#define _DEV_TCFLOW             0x0315
#define _DEV_TCGETPGRP          0x0316
#define _DEV_TCSETPGRP          0x0317
#define _DEV_INSERTCHARS        0x0318
#define _DEV_MODE               0x0319
#define _DEV_WAITING            0x031A
#define _DEV_INFO               0x031B
#define _DEV_ARM                0x031C
#define _DEV_STATE              0x031D
#define _DEV_READ               0x031E
#define _DEV_WRITE              0x031F
#define _DEV_FDINFO             0x0320
#define _DEV_TCSETCT            0x0321
#define _DEV_TCDROPLINE         0x0322
#define _DEV_SIZE               0x0323
#define _DEV_READEX             0x0324
#define _DEV_OSIZE              0x0325
#define _DEV_RESET              0x0326

struct _dev_tcgetattr {
    msg_t       type;
    short       fd;
    } ;

struct _dev_tcgetattr_reply {
    msg_t           status;
    struct termios  state;
    } ;

struct _dev_tcsetattr {
    msg_t           type;
    short           fd;
    struct termios  state;
    short           optional_actions;
    } ;

struct _dev_tcsetattr_reply {
    msg_t           status;
    } ;

struct _dev_mode {
    msg_t           type;
    short           fd;
    unsigned short          mode;
    unsigned short          mask;
    unsigned short          zero[2];
    } ;

struct _dev_mode_reply {
    msg_t           status;
    unsigned short          oldmode;
    unsigned short          zero[2];
    } ;

struct _dev_tcsendbreak {
    msg_t           type;
    short           fd;
    short           duration;
    } ;

struct _dev_tcsendbreak_reply {
    msg_t           status;
    } ;

struct _dev_tcdropline {
    msg_t           type;
    short           fd;
    short           duration;
    } ;

struct _dev_tcdropline_reply {
    msg_t           status;
    } ;

struct _dev_tcdrain {
    msg_t           type;
    short           fd;
    } ;

struct _dev_tcdrain_reply {
    msg_t           status;
    } ;

struct _dev_tcflush {
    msg_t           type;
    short           fd;
    short           queue_selector;
    } ;

struct _dev_tcflush_reply {
    msg_t           status;
    } ;

struct _dev_tcflow {
    msg_t           type;
    short           fd;
    short           action;
    } ;

struct _dev_tcflow_reply {
    msg_t           status;
    } ;

struct _dev_tcgetpgrp {
    msg_t           type;
    short           fd;
    } ;

struct _dev_tcgetpgrp_reply {
    msg_t           status;
    mpid_t          pgrp_id;
    unsigned short          pgrp_id_spare;
    } ;

struct _dev_tcsetpgrp {
    msg_t           type;
    short           fd;
    mpid_t          pgrp_id;
    unsigned short          pgrp_id_spare;
    } ;

struct _dev_tcsetpgrp_reply {
    msg_t           status;
    } ;

struct _dev_tcsetct {
    msg_t           type;
    short           fd;
    mpid_t          pid;
    unsigned short          pid_spare;
    } ;

struct _dev_tcsetct_reply {
    msg_t           status;
    } ;

struct _dev_insert_chars {
    msg_t           type;
    short           fd;
    short           nbytes;
    char            data[256];
    } ;

struct _dev_insert_chars_reply {
    msg_t           status;
    } ;

struct _dev_waiting {
    msg_t           type;
    short           fd;
    } ;

struct _dev_waiting_reply {
    msg_t           status;
    short           nbytes;
    } ;

struct _dev_info {
    msg_t           type;
    short           fd;
    } ;

struct _dev_info_reply {
    msg_t           status;
    struct _dev_info_entry info;
    } ;

struct _dev_fdinfo {
    msg_t           type;
    short           fd;
    mpid_t          pid;
    unsigned short          pid_spare;
    } ;

struct _dev_fdinfo_reply {
    msg_t           status;
    struct _dev_info_entry info;
    } ;

struct _dev_arm {
    msg_t           type;
    short           fd;
    mpid_t          proxy;
    unsigned short          proxy_spare;
    unsigned short          events;
    } ;

struct _dev_arm_reply {
    msg_t           status;
    } ;

struct _dev_state {
    msg_t           type;
    short           fd;
    unsigned short          bits;
    unsigned short          mask;
    } ;

struct _dev_state_reply {
    msg_t           status;
    unsigned short          oldbits;
    } ;


struct _dev_read {
    msg_t           type;
    short           fd;
    short           nbytes;
    unsigned short          minimum;
    unsigned short          time;
    unsigned short          timeout;
    mpid_t          proxy;
    unsigned short          proxy_spare;
    unsigned short          zero;
    } ;

struct _dev_read_reply {
    msg_t           status;
    short           nbytes;
    unsigned short          timeout;
    unsigned short          empty;
    char            data[1];
    } ;


struct _dev_write {
    msg_t           type;
    short           fd;
    short           nbytes;
    unsigned short          timeout;
    unsigned short          zero;
    char            data[1];
    } ;

struct _dev_write_reply {
    msg_t           status;
    short           nbytes;
    unsigned short          timeout;
    unsigned short          zero;
    } ;

struct _dev_size {
    msg_t           type;
    short           fd;
    unsigned short rows; /* -1 = don't change, 0 means unknown */
    unsigned short cols; /* -1 = don't change, 0 means unknown */
        unsigned short zero[8];
    } ;

struct _dev_size_reply {
    msg_t           status;
    unsigned short oldrows;
    unsigned short oldcols;
        unsigned short zero[8];
    } ;

struct _dev_readex {
    msg_t           type;
    short           fd;
    short           nbytes;
    unsigned short zero[3];
    } ;

struct _dev_readex_reply {
    msg_t           status;
    short           nbytes;
    unsigned short zero[3];
    char            data[1];  /* variable length */
    } ;

struct _dev_osize {
    msg_t           type;
    short           fd;
    unsigned short size; /* -1 = don't change */
        unsigned short zero[5];
    } ;

struct _dev_osize_reply {
    msg_t           status;
    unsigned short oldsize;
        unsigned short zero[6];
    } ;

struct _dev_reset {
    msg_t           type;
    short           fd;
    unsigned short  zero[4];
    } ;

struct _dev_reset_reply {
    msg_t           status;
    unsigned short zero[3];
    } ;

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __DEV_MSG_H_INCLUDED
#endif
