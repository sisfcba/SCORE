/*
 *  dev.h       "Public" Device Administrator Definitions
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __DEV_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

#define MAX_TTY_NAME 32

struct _dev_info_entry {
    short int       tty;
    nid_t           nid;
    short unsigned  driver_pid;
    short unsigned  driver_pid_spare;
    short unsigned  nature;
    short unsigned  attributes;
    short unsigned  capabilities;
    char            driver_type[16];
    char            tty_name[MAX_TTY_NAME];
    short unsigned          unit;
    short unsigned          open_count;
    mpid_t          pgrp;
    short unsigned          pgrp_spare;
    mpid_t          session;
    short unsigned          session_spare;
    short unsigned          flags;
    short unsigned          major;
    } ;

/*
 * Dev_info flags bits
 */
#define _DEV_IS_READERS         0x0001
#define _DEV_IS_WRITERS         0x0002
#define _DEV_WILL_WINCH         0x0004
#define _DEV_WILL_FWD           0x0008
#define _DEV_NBLOCK_PROXY       0x0010

/*
 * Events recognized by dev_arm() and dev_state()
 */
#define _DEV_EVENT_INPUT        0x0001
#define _DEV_EVENT_DRAIN        0x0002
#define _DEV_EVENT_LOGIN        0x0004
#define _DEV_EVENT_EXRDY        0x0008
#define _DEV_EVENT_OUTPUT       0x0010
#define _DEV_EVENT_TXRDY        0x0020
#define _DEV_EVENT_RXRDY        0x0040
#define _DEV_EVENT_HANGUP       0x0080
#define _DEV_EVENT_INTR         0x0100
#define _DEV_EVENT_WINCH        0x0200

/*
 * Special "proxy" value to disarm pending armed proxies
 **/
#define _DEV_DISARM                     (-1)

/*
 * Modes recognized by dev_mode()
 */
#define _DEV_ECHO       0x0001
#define _DEV_EDIT       0x0002
#define _DEV_ISIG       0x0004
#define _DEV_OPOST      0x0008
#define _DEV_OSFLOW 0x0010
#define _DEV_MODES      (_DEV_ECHO|_DEV_EDIT|_DEV_ISIG|_DEV_OPOST|_DEV_OSFLOW)

#ifdef __cplusplus
extern "C" {
#endif
extern int      dev_info( int __fd, struct _dev_info_entry *__info );
extern int      dev_fdinfo( pid_t __server, pid_t __pid,
                    int __fd, struct _dev_info_entry *__info );
extern int      dev_insert_chars( int __fd, int __n, const char *__buf );
extern unsigned dev_state( int __fd, unsigned __bits, unsigned __mask );
extern unsigned dev_mode( int __fd, unsigned __mask, unsigned __mode );
extern int      dev_arm( int __fd, pid_t __proxy, unsigned __events );
extern int      dev_read( int __fd, void *__buf, unsigned __nbytes,
                  unsigned __minimum, unsigned __time, unsigned __timeout,
                  pid_t __proxy, int *__triggered );
extern int      dev_ischars( int __fd );
extern int      dev_size( int __fd, int __set_rows, int __set_columns,
                  int *__rows, int *__cols );
extern int      dev_osize(int __fd, int __size);
extern int      dev_readex(int __fd, char *__buf, int __nbytes);
#ifdef __cplusplus
};
#endif

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __DEV_H_INCLUDED
#endif
