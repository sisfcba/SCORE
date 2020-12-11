/*
 *  debug.h     Debugger data structures
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __DEBUG_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#pragma pack(1);

struct _debug_hdr {
    short unsigned  type,
                    subtype;
    mpid_t          pid;
    short unsigned  zero1,
                    segment,
                    size;
    long            offset;
    } ;

struct _debug_hdr_reply {
    short unsigned  status,
                    zero1;
    mpid_t          pid;
    short unsigned  zero2,
                    zero3,
                    zero4;
    long            zero5;
    } ;


/*
 *  _debug_data follows immediately (byte aligned) after a
 *  _debug_hdr or _debug_hdr_reply
 */
union    _port_struct {
    char    byte;
    short   word;
    long    dword;
    };

struct  _debug_info {
    mpid_t          messenger,
                    zero1,
                    debugger,
                    zero2;
    short unsigned  step_count;
    char            debug_state,
                    watch_items;
    short           signo;
    };

struct  _debug_psinfo {
    long unsigned   codeoff;   /* For flat model only */
    long unsigned   codesize;  /* For flat model only */
    long unsigned   zero[14];
    };

struct _reg_struct {
    long            gs, fs, es, ds, di, si,
                    bp, sp, bx, dx,
                    cx, ax, ip, cs,
                    fl, ss;
    };

struct  _watch_struct {
    long            off;
    short unsigned  seg;
    char            byte;
    char            zero;
    };

union _debug_data {
    mpid_t                      mid;
    long                        opcode;
    char                        mem[512];
    char                        x87[108];
    union  _port_struct         port;
    struct _debug_info          info;
    struct _debug_psinfo        psinfo;
    struct _reg_struct          reg;
    struct _watch_struct        watch_table[32];        
    } ;


/*
 *  Debug operations        _PROC_DEBUG --> msg.sub_type
 */

#define _DEBUG_ATTACH       0
#define _DEBUG_DETACH       1
#define _DEBUG_STOP         2
#define _DEBUG_CONT         3
#define _DEBUG_INFO         4
#define _DEBUG_SIG_CLR      5
#define _DEBUG_BRK_SET      6
#define _DEBUG_BRK_CLR      7
#define _DEBUG_MEM_RD       8
#define _DEBUG_MEM_WR       9
#define _DEBUG_IO_RD        10
#define _DEBUG_IO_WR        11
#define _DEBUG_REG_RD       12
#define _DEBUG_REG_WR       13
#define _DEBUG_WATCH_RD     14
#define _DEBUG_WATCH_WR     15
#define _DEBUG_80X87_RD     16
#define _DEBUG_80X87_WR     17
#define _DEBUG_PSINFO       18

#define _DEBUG_WRITE_FLAG   1


/*
 *  Debug process states (returned with the read register call).
 */

#define _DEBUG_STATE_CONT   0       /*  Free to run till held by following  */
#define _DEBUG_STATE_HELD   1       /*  Held via debugger                   */
#define _DEBUG_STATE_TRACE  2       /*  Held via trace count                */
#define _DEBUG_STATE_BRK    3       /*  Held via swi                        */
#define _DEBUG_STATE_WATCH  4       /*  Held via watch mismatch             */
#define _DEBUG_STATE_DEAD   5       /*  Task has died                       */
#define _DEBUG_STATE_SIGNAL 6       /*  Held via a signal                   */
#define _DEBUG_STATE_FORK   7       /*  Held because it forked              */
#define _DEBUG_STATE_THREAD 8       /*  Held because new thread started     */
/*
 * For STATE_FORK and STATE_THREAD, messenger is the new pid
 */

#ifdef __cplusplus
extern "C" {
#endif
extern int  __qnx_debug_attach( pid_t, pid_t, pid_t );
extern int  __qnx_debug_detach( pid_t, pid_t );
extern int  __qnx_debug_xfer( pid_t, pid_t, int, void __far *, unsigned, unsigned long, unsigned );
extern int  __qnx_debug_brk( pid_t, pid_t, unsigned, long __far *, unsigned long, unsigned );
extern int  __qnx_debug_sigclr( pid_t, pid_t, int );
extern int  __qnx_debug_cont( pid_t, pid_t, unsigned );
extern int  __qnx_debug_hold( pid_t, pid_t );
#ifdef __cplusplus
};
#endif

#pragma pack();

#define __DEBUG_H_INCLUDED
#endif
