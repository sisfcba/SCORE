/*
 *  kernel.h    kernel function calls/pragmas
 *
 *  Copyright by WATCOM International Corp. 1988-1993.  All rights reserved.
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __KERNEL_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#ifndef __SENDMX_H_INCLUDED
 #include <sys/sendmx.h>
#endif

#define PROC_PID    1

/*
 * Task States
 */

#define STATE_DEAD              0
#define STATE_READY             1
#define STATE_SEND_BLOCKED      2
#define STATE_RECEIVE_BLOCKED   3
#define STATE_REPLY_BLOCKED     4
#define STATE_HELD              5
#define STATE_SIGNAL_BLOCKED    6
#define STATE_WAIT_BLOCKED      7
#define STATE_SEM_BLOCKED       8

/*
 *  virtual processes substates.  Note that the vid's state must be
 *  reply blocked on 0 for any of these blocked substates to be valid
 */
#define _VCS_READY          1   /* idle (could be txing reply, also)    */
#define _VCS_VA_NET_BLK     2   /* initially attaching, blkd on network */
#define _VCS_VAS_NET_BLK    3   /* shared attaching, blkd on network    */
#define _VCS_GS_PROC_BLK    4   /* growing on send, blkd on local proc  */
#define _VCS_GS_NET_BLK     5   /* growing on send, blkd on network     */
#define _VCS_S_NET_BLK      6   /* sending, blkd on network (normal)    */
#define _VCS_GR_PROC_BLK    7   /* growing on reply, blkd on local proc */
#define _VCS_GR_NET_BLK     8   /* growing on reply, blkd on network    */
#define _VCS_GW_PROC_BLK    9   /* growing on writemsg, blkd on proc    */


#ifdef __cplusplus
extern "C" {
#endif
#if defined(__386__)

#define Send( a,b,c,d,e ) __send( a,b,c,d,e )

extern int __send(
            pid_t           __pid,
            const void      *__msg1,
            void            *__msg2,
            unsigned        __nbytes1,
            unsigned        __nbytes2 );

#define Sendfd( a,b,c,d,e ) __sendfd( a,b,c,d,e )

extern int __sendfd(
            int             __fd,
            const void     *__msg1,
            void           *__msg2,
            unsigned        __nbytes1,
            unsigned        __nbytes2 );

#define Receive( a,b,c ) __receive( a,b,c )

extern pid_t __receive(
            pid_t           __pid,
            void           *__msg,
            unsigned        __nbytes );

#define Reply( a,b,c ) __reply( a,b,c )

extern int __reply(
            pid_t           __pid,
            const void     *__msg,
            unsigned        __nbytes );

#define Creceive( a,b,c ) __creceive( a,b,c )

extern pid_t __creceive(
            pid_t           __pid,
            void           *__msg,
            unsigned        __nbytes );

#define Readmsg( a,b,c,d ) __readmsg( a,b,c,d )

extern unsigned __readmsg(
            pid_t           __pid,
            unsigned        __offset,
            void           *__msg,
            unsigned        __nbytes );

#define Writemsg( a,b,c,d ) __writemsg( a,b,c,d )

extern unsigned __writemsg(
            pid_t           __pid,
            unsigned        __offset,
            const void     *__msg,
            unsigned        __nbytes );

extern int __kererr(int errcode);

#if defined(__WATCOMC__) && __WATCOMC__ >= 900
#define Sendmx( a,b,c,d,e ) __sendmx( a,b,c,d,e )

extern int __sendmx(
            int                   __pid,
            unsigned              __smsg_xparts,
            unsigned              __rmsg_xparts,
            const struct _mxfer_entry  *__smsg,
            const struct _mxfer_entry  *__rmsg );
#pragma aux __sendmx =                   \
    "mov al,00h"                         \
    "clc"                                \
    "int 0f2h"                           \
    "jnc l1"                             \
    "call __kererr"                      \
    "l1:"                                \
    __parm [edx] [ah] [ch] [ebx] [esi]   \
    __modify __exact [eax]               \
    __value [eax]                        \
    ;

#define Receivemx( a,b,c ) __receivemx( a,b,c )

extern int __receivemx(
            pid_t                 __pid,
            unsigned              __rmsg_xparts,
            struct _mxfer_entry  *__rmsg );
#pragma aux __receivemx =                \
    "mov al,01h"                         \
    "clc"                                \
    "int 0f2h"                           \
    "jnc l1"                             \
    "call __kererr"                      \
    "l1:"                                \
    __parm [edx] [ah] [ebx]              \
    __modify __exact [eax]               \
    __value [eax]                        \
    ;

#define Replymx( a,b,c ) __replymx( a,b,c )

extern int __replymx(
            pid_t                 __pid,
            unsigned              __rmsg_xparts,
            struct _mxfer_entry  *__rmsg );
#pragma aux __replymx =                  \
    "mov al,02h"                         \
    "clc"                                \
    "int 0f2h"                           \
    "jnc l1"                             \
    "call __kererr"                      \
    "l1:"                                \
    __parm [edx] [ah] [ebx]              \
    __modify __exact [eax]               \
    __value [eax]                        \
    ;

#define Creceivemx( a,b,c ) __creceivemx( a,b,c )

extern int __creceivemx(
            pid_t                 __pid,
            unsigned              __rmsg_xparts,
            struct _mxfer_entry  *__rmsg );
#pragma aux __creceivemx =               \
    "mov al,03h"                         \
    "clc"                                \
    "int 0f2h"                           \
    "jnc l1"                             \
    "call __kererr"                      \
    "l1:"                                \
    __parm [edx] [ah] [ebx]              \
    __modify __exact [eax]               \
    __value [eax]                        \
    ;

#define Readmsgmx( a,b,c,d ) __readmsgmx( a,b,c,d )

extern unsigned __readmsgmx(
            pid_t                 __pid,
            unsigned              __offset,
            unsigned              __rmsg_xparts,
            struct _mxfer_entry  *__rmsg);
#pragma aux __readmsgmx =                \
    "mov al,04h"                         \
    "clc"                                \
    "int 0f2h"                           \
    "jnc l1"                             \
    "call __kererr"                      \
    "l1:"                                \
    __parm [edx] [ecx] [ah] [ebx]        \
    __modify __exact [eax]               \
    __value [eax]                        \
    ;

#define Writemsgmx( a,b,c,d ) __writemsgmx( a,b,c,d )

extern unsigned __writemsgmx(
            pid_t                 __pid,
            unsigned              __offset,
            unsigned              __wmsg_xparts,
            struct _mxfer_entry  *__wmsg );
#pragma aux __writemsgmx =               \
    "mov al,05h"                         \
    "clc"                                \
    "int 0f2h"                           \
    "jnc l1"                             \
    "call __kererr"                      \
    "l1:"                                \
    __parm [edx] [ecx] [ah] [ebx]        \
    __modify __exact [eax]               \
    __value [eax]                        \
    ;

#define Relay( a,b ) __relay( a,b )

extern int __relay(
            pid_t           __pid1,
            pid_t           __pid2 );
#pragma aux __relay =                    \
    "mov al,06h"                         \
    "clc"                                \
    "int 0f2h"                           \
    "jnc l1"                             \
    "call __kererr"                      \
    "l1:"                                \
    __parm [edx] [ebx]                   \
    __modify __exact [eax]               \
    __value [eax]                        \
    ;

#define Kill( a,b ) __kill( a,b )

extern int __kill(
            pid_t           __pid,
            int             signo );
#pragma aux __kill =                     \
    "mov eax,000eh"                      \
    "clc"                                \
    "int 0f2h"                           \
    "jnc l1"                             \
    "call __kererr"                      \
    "l1:"                                \
    __parm [edx] [ebx]                   \
    __modify __exact [eax]               \
    __value [eax]                        \
    ;

#define Sigsuspend( a ) __sigsuspend( a )

extern int __sigsuspend(
            long            __mask);
#pragma aux __sigsuspend =               \
    "mov eax,010eh"                      \
    "clc"                                \
    "int 0f2h"                           \
    "jnc l1"                             \
    "call __kererr"                      \
    "l1:"                                \
    __parm [edx]                         \
    __modify __exact [eax]               \
    __value [eax]                        \
    ;

#define __Sret() __sret()

extern void __sret( void );
#pragma aux __sret =                     \
    "mov al,07h"                         \
    "int 0f2h"                           \
    __modify __exact __nomemory []       \
    ;

#define Priority( a,b ) __priority( a,b )

extern int __priority(
            pid_t           __pid1,
            int             __pri );
#pragma aux __priority =                 \
    "mov al,08h"                         \
    "clc"                                \
    "int 0f2h"                           \
    "jnc l1"                             \
    "call __kererr"                      \
    "l1:"                                \
    __parm [edx] [ebx]                   \
    __modify __exact [eax]               \
    __value [eax]                        \
    ;

#define Netdata( a,b ) __netdata( a,b )

extern int __netdata(
            pid_t           __pid1,
            unsigned        __type );
#pragma aux __netdata =                  \
    "mov al,09h"                         \
    "clc"                                \
    "int 0f2h"                           \
    "jnc l1"                             \
    "call __kererr"                      \
    "l1:"                                \
    __parm [edx] [ebx]                   \
    __modify __exact [eax]               \
    __value [eax]                        \
    ;

#define Yield() __yield()

extern void __yield( void );
#pragma aux __yield =                    \
    "mov al,0ah"                         \
    "int 0f2h"                           \
    __modify __exact __nomemory [al]     \
    ;

#define Sendfdmx( a,b,c,d,e ) __sendfdmx( a,b,c,d,e )

extern int __sendfdmx(
            int                   __fd,
            unsigned              __smsg_xparts,
            unsigned              __rmsg_xparts,
            struct _mxfer_entry  *__smsg,
            struct _mxfer_entry  *__rmsg );
#pragma aux __sendfdmx =                 \
    "mov al,0bh"                         \
    "clc"                                \
    "int 0f2h"                           \
    "jnc l1"                             \
    "call __kererr"                      \
    "l1:"                                \
    __parm [edx] [ah] [ch] [ebx] [esi]   \
    __modify __exact [eax]               \
    __value [eax]                        \
    ;

#define Trigger( a ) __trigger( a )

extern int __trigger( pid_t __pid );
#pragma aux __trigger =                  \
    "mov al,0ch"                         \
    "clc"                                \
    "int 0f2h"                           \
    "jnc l1"                             \
    "call __kererr"                      \
    "l1:"                                \
    __parm [edx]                         \
    __modify __exact [eax]               \
    __value [eax]                        \
    ;

#define Semaphore( a,b ) __semaphore( a,b )

extern int __semaphore(
            int             id,
            int             semaction );
#pragma aux __semaphore =                \
    "mov eax,0010h"                      \
    "clc"                                \
    "int 0f2h"                           \
    "jnc l1"                             \
    "call __kererr"                      \
    "l1:"                                \
    __parm [edx] [ebx]                   \
    __modify __exact [eax]               \
    __value [eax]                        \
    ;
#endif

#else

#pragma aux qnx_int "*_" far __parm __routine []         \
    __value __struct __float __struct __routine [ax] __modify __exact [ax];

#define Send( a,b,c,d,e ) __send( a,b,c,d,e )

extern int __send(
            pid_t           __pid,
            void __far      *__msg1,
            void __far      *__msg2,
            unsigned        __nbytes1,
            unsigned        __nbytes2 );

#define Sendfd( a,b,c,d,e ) __sendfd( a,b,c,d,e )

extern int __sendfd(
            int             __fd,
            void __far      *__msg1,
            void __far      *__msg2,
            unsigned        __nbytes1,
            unsigned        __nbytes2 );

#define Receive( a,b,c ) __receive( a,b,c )

extern pid_t __receive(
            pid_t           __pid,
            void __far      *__msg,
            unsigned        __nbytes );

#define Reply( a,b,c ) __reply( a,b,c )

extern int __reply(
            pid_t           __pid,
            void __far      *__msg,
            unsigned        __nbytes );

#define Creceive( a,b,c ) __creceive( a,b,c )

extern pid_t __creceive(
            pid_t           __pid,
            void __far      *__msg,
            unsigned        __nbytes );

#define Readmsg( a,b,c,d ) __readmsg( a,b,c,d )

extern unsigned __readmsg(
            pid_t           __pid,
            unsigned        __offset,
            void __far      *__msg,
            unsigned        __nbytes );

#define Writemsg( a,b,c,d ) __writemsg( a,b,c,d )

extern unsigned __writemsg(
            pid_t           __pid,
            unsigned        __offset,
            void __far      *__msg,
            unsigned        __nbytes );

#define Sendmx( a,b,c,d,e ) __sendmx( a,b,c,d,e )

extern int __sendmx(
            pid_t           __pid,
            unsigned        __smsg_xparts,
            unsigned        __rmsg_xparts,
            struct _mxfer_entry __far *__smsg,
            struct _mxfer_entry __far *__rmsg );
#pragma aux (qnx_int) __sendmx =                            \
0xB8 0x00 0x00          /*  mov     ax,0000h            */  \
0x50                    /*  push    ax                  */  \
0xCD 0xF0               /*  int     f0                  */  \
0x83 0xC4 0x10          /*  add     sp,10h              */  \
    ;

#define Receivemx( a,b,c ) __receivemx( a,b,c )

extern pid_t __receivemx(
            pid_t           __pid,
            unsigned        __rmsg_xparts,
            struct _mxfer_entry __far *__rmsg );
#pragma aux (qnx_int) __receivemx =                         \
0xB8 0x01 0x00          /*  mov     ax,0001h            */  \
0x50                    /*  push    ax                  */  \
0xCD 0xF0               /*  int     f0                  */  \
0x83 0xC4 0x0A          /*  add     sp,0ah              */  \
    ;

#define Replymx( a,b,c ) __replymx( a,b,c )

extern int __replymx(
            pid_t           __pid,
            unsigned        __rmsg_xparts,
            struct _mxfer_entry __far *__rmsg );
#pragma aux (qnx_int) __replymx =                           \
0xB8 0x02 0x00          /*  mov     ax,0002h            */  \
0x50                    /*  push    ax                  */  \
0xCD 0xF0               /*  int     f0                  */  \
0x83 0xC4 0x0A          /*  add     sp,0ah              */  \
    ;

#define Creceivemx( a,b,c ) __creceivemx( a,b,c )

extern pid_t __creceivemx(
            pid_t           __pid,
            unsigned        __rmsg_xparts,
            struct _mxfer_entry __far *__rmsg );
#pragma aux (qnx_int) __creceivemx =                        \
0xB8 0x03 0x00          /*  mov     ax,0003h            */  \
0x50                    /*  push    ax                  */  \
0xCD 0xF0               /*  int     f0                  */  \
0x83 0xC4 0x0A          /*  add     sp,0ah              */  \
    ;

#define Readmsgmx( a,b,c,d ) __readmsgmx( a,b,c,d )

extern unsigned __readmsgmx(
            pid_t           __pid,
            unsigned        __offset,
            unsigned        __rmsg_xparts,
            struct _mxfer_entry __far *__rmsg);
#pragma aux (qnx_int) __readmsgmx =                         \
0xB8 0x04 0x00          /*  mov     ax,0004h            */  \
0x50                    /*  push    ax                  */  \
0xCD 0xF0               /*  int     f0                  */  \
0x83 0xC4 0x0C          /*  add     sp,0ch              */  \
    ;

#define Writemsgmx( a,b,c,d ) __writemsgmx( a,b,c,d )

extern unsigned __writemsgmx(
            pid_t           __pid,
            unsigned        __offset,
            unsigned        __wmsg_xparts,
            struct _mxfer_entry __far *__wmsg );
#pragma aux (qnx_int) __writemsgmx =                        \
0xB8 0x05 0x00          /*  mov     ax,0005h            */  \
0x50                    /*  push    ax                  */  \
0xCD 0xF0               /*  int     f0                  */  \
0x83 0xC4 0x0C          /*  add     sp,0ch              */  \
    ;

#define Relay( a,b ) __relay( a,b )

extern int __relay(
            pid_t           __pid1,
            pid_t           __pid2 );
#pragma aux (qnx_int) __relay =                             \
0xB8 0x06 0x00          /*  mov     ax,0006h            */  \
0x50                    /*  push    ax                  */  \
0xCD 0xF0               /*  int     f0                  */  \
0x83 0xC4 0x06          /*  add     sp,06h              */  \
    ;

#define __Sret() __sret()

extern void __sret( void );
#pragma aux (qnx_int) __sret =                              \
0xB8 0x07 0x00          /*  mov     ax,0007h            */  \
0x50                    /*  push    ax                  */  \
0xCD 0xF0               /*  int     f0                  */  \
0x83 0xC4 0x02          /*  add     sp,02h              */  \
    ;

#define Priority( a,b ) __priority( a,b )

extern int __priority(
            pid_t           __pid1,
            int             __pri );
#pragma aux (qnx_int) __priority =                          \
0xB8 0x08 0x00          /*  mov     ax,0008h            */  \
0x50                    /*  push    ax                  */  \
0xCD 0xF0               /*  int     f0                  */  \
0x83 0xC4 0x06          /*  add     sp,06h              */  \
    ;

#define Netdata( a,b ) __netdata( a,b )

extern int __netdata(
            pid_t           __pid1,
            unsigned        __type );
#pragma aux (qnx_int) __netdata =                           \
0xB8 0x09 0x00          /*  mov     ax,0009h            */  \
0x50                    /*  push    ax                  */  \
0xCD 0xF0               /*  int     f0                  */  \
0x83 0xC4 0x06          /*  add     sp,06h              */  \
    ;

#define Yield() __yield()

extern void __yield( void );
#pragma aux (qnx_int) __yield =                             \
0xB8 0x0a 0x00          /*  mov     ax,000ah            */  \
0x50                    /*  push        ax              */  \
0xCD 0xF0               /*  int     f0                  */  \
0x83 0xC4 0x02          /*  add     sp,02h              */  \
    ;

#define Sendfdmx( a,b,c,d,e ) __sendfdmx( a,b,c,d,e )

extern int __sendfdmx(
            int             __fd,
            unsigned        __smsg_xparts,
            unsigned        __rmsg_xparts,
            struct _mxfer_entry __far *__smsg,
            struct _mxfer_entry __far *__rmsg );
#pragma aux (qnx_int) __sendfdmx =                          \
0xB8 0x0b 0x00          /*  mov     ax,000bh            */  \
0x50                    /*  push    ax                  */  \
0xCD 0xF0               /*  int     f0                  */  \
0x83 0xC4 0x10          /*  add     sp,10h              */  \
    ;

#define Trigger( a ) __trigger( a )

extern pid_t __trigger( pid_t __pid );
#pragma aux (qnx_int) __trigger =                           \
0xB8 0x0c 0x00          /*  mov     ax,000ch            */  \
0x50                    /*  push    ax                  */  \
0xCD 0xF0               /*  int     f0                  */  \
0x83 0xC4 0x04          /*  add     sp,04h              */  \
    ;

#define Semaphore( a,b ) __semaphore( a,b )

extern int __semaphore(
            int             semid,
            int             semaction );
#pragma aux (qnx_int) __semaphore =      \
    "mov ax,0010h"                       \
    "push ax"                            \
    "int 0f0h"                           \
    "add sp,6"                           \
    ;

#endif
#ifdef __cplusplus
};
#endif

#define __KERNEL_H_INCLUDED
#endif
