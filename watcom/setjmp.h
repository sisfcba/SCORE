/*
 *  setjmp.h
 *
 *  Copyright by WATCOM International Corp. 1988-1996.  All rights reserved.
 *  Copyright by QNX Software Systems Limited 1990-1996. All rights reserved.
 */
#ifndef _SETJMP_H_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int jmp_buf[13];

extern int  _setjmp( jmp_buf __env );
#define setjmp(__env)     _setjmp(__env)
#if defined(__386__)
 #pragma aux _setjmp __parm __caller [eax] __modify [8087];
#else
 #pragma aux _setjmp __modify [8087];
#endif

extern void longjmp( jmp_buf __env, int __val );

#pragma aux     longjmp __aborts;
#if defined(_POSIX_SOURCE) || defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS)
#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif
typedef struct {
    int         __flg;
    long        __msk;
    jmp_buf     __buf;
} sigjmp_buf[1];
#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

extern void __sigjmpsave( sigjmp_buf __env, int __msk );
extern void siglongjmp( sigjmp_buf __env, int __val );

#define sigsetjmp( __env, __msk ) ( __sigjmpsave( __env, __msk ), \
                                    _setjmp( (__env)[0].__buf ) )

#pragma aux siglongjmp __aborts;

#endif

#define _SETJMP_H_INCLUDED
#ifdef __cplusplus
};
#endif
#endif
