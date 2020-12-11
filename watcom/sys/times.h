/*
 *  times.h     Process timing definitions (P1003.1)
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __TIMES_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

#ifndef _CLOCK_T_DEFINED
 #define _CLOCK_T_DEFINED
#ifdef __STDC__
 typedef unsigned long  clock_t;
#else
 typedef long  clock_t;
#endif
#endif

struct  tms {
        clock_t tms_utime;
        clock_t tms_stime;
        clock_t tms_cutime;
        clock_t tms_cstime;
};


#ifdef __cplusplus
extern "C" {
#endif
extern clock_t times( struct tms *__time_info );
#ifdef __cplusplus
};
#endif

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __TIMES_H_INCLUDED
#endif
