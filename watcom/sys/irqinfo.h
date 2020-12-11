/*
 *  irqinfo.h
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __IRQINFO_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

struct _irqinfo {
    mpid_t          pid;
    short unsigned  flags;
    short unsigned  intnum,
                    ds;
    long            offset;
    short unsigned  cs;
    } ;

#define _PIF_ANCHOR   0x0001
#define _PIF_32BIT    0x8000

#ifdef __cplusplus
extern "C" {
#endif
extern int     qnx_hint_attach( unsigned, void __far *, unsigned );
extern int     qnx_hint_detach( int );
extern int     qnx_hint_query( pid_t, int, struct _irqinfo * );
extern int     qnx_hint_mask( unsigned, unsigned );
#ifdef __cplusplus
};
#endif

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __IRQINFO_H_INCLUDED
#endif
