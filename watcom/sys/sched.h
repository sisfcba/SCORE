/*
 *  sched.h
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __SCHED_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#define SCHED_FIFO      0
#define SCHED_RR        1
#define SCHED_OTHER     2
#define SCHED_FAIR      2   /* Friendly name for POSIX name of OTHER */

#define PRIO_FIFO_MIN    0
#define PRIO_FIFO_MAX   29
#define PRIO_RR_MIN      0
#define PRIO_RR_MAX     29
#define PRIO_OTHER_MIN   0
#define PRIO_OTHER_MAX  29
#define PRIO_USER_DFLT  10
#define _NUM_PRIORITIES 32
#define RR_INTERVAL     struct timespec

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif
struct sched_param {
    int sched_priority;
    int sched_reserved;
    } ;
#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif
#ifdef __cplusplus
extern "C" {
#endif
/* D1003.4 D9 */
extern int  setprio( pid_t, int );
extern int  getprio( pid_t );
extern int  setscheduler( pid_t, int, int );
extern int  getscheduler( pid_t );
extern void yield( void );
/* D1003.4 D12 */
extern int  sched_setparam( pid_t, struct sched_param * );
extern int  sched_getparam( pid_t, struct sched_param * );
extern int  sched_setscheduler( pid_t, int, struct sched_param * );
extern int  sched_getscheduler( pid_t );
extern void sched_yield( void );

extern int  qnx_scheduler( pid_t, pid_t, int, int, int );
#ifdef __cplusplus
};
#endif


#ifdef __INLINE_FUNCTIONS__

#ifndef __KERNEL_H_INCLUDED
#include <sys/kernel.h>
#endif

#define sched_yield __yield

#endif

#define __SCHED_H_INCLUDED
#endif
