/*
 *  sendmx.h
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __SENDMX_H_INCLUDED

#ifndef _I86_H_INCLUDED
 #include <i86.h>
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

struct _mxfer_entry16 {
    short unsigned  mxfer_off,
            mxfer_zero,
            mxfer_seg,
            mxfer_len;
    } ;

struct _mxfer_entry32 {
    long unsigned   mxfer_off;
    short unsigned  mxfer_seg,
                    mxfer_zero;
    long unsigned   mxfer_len;
    } ;

#if defined(__386__)
#define _mxfer_entry _mxfer_entry32
#else
#define _mxfer_entry _mxfer_entry16
#endif

#define _setmx(mx, data, len)   {\
                    (mx)->mxfer_off  = FP_OFF(data);\
                    (mx)->mxfer_zero = 0;\
                    (mx)->mxfer_seg  = FP_SEG(data);\
                    (mx)->mxfer_len  = len; }

/* maximum size of mx vector */
#define MAX_MX_TAB  255
#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __SENDMX_H_INCLUDED
#endif
