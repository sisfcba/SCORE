/*
 *  timers.h    Interval timer definitions (P1003.4)
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __TIMERS_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

#ifndef __POSIX_TIMERS
#define __POSIX_TIMERS

struct timespec {
    long    tv_sec,
            tv_nsec;
    } ;

struct itimerspec {
    struct timespec it_value,
                    it_interval;
    int             notify_type,    /* Uses native int size */
                    timer_type;
    long            data;           /* Used by gettimer only */
    } ;

struct itimercb {
    struct event {
        long evt_value;     /* Will hold a proxy or a signal */
        }   itcb_event;
    int     itcb_count;
    } ;
#endif    

/*
 *  Timer operations.
 */

#define TIMEOFDAY           0

#define _TNOTIFY_SLEEP      0
#define _TNOTIFY_PROXY      1
#define _TNOTIFY_MESSENGER  1
#define _TNOTIFY_SIGNAL     2
#define DELIVERY_SIGNALS    2   /* Same as _TNOTIFY_SIGNAL (POSIX 1003.4) */

/*
 *  POSIX 1003.4 Prototypes.
 */
#ifdef __cplusplus
extern "C" {
#endif
extern int     qnx_getclock( pid_t, int, struct timespec * );
extern int     qnx_setclock( pid_t, int, struct timespec * );
extern int     getclock( int, struct timespec * );
extern int     setclock( int, struct timespec * );
extern int     qnx_clock( nid_t, int, struct timespec * );
extern timer_t mktimer ( int, int, struct itimercb * );
extern int     rmtimer ( timer_t );
extern int     gettimer( timer_t, struct itimerspec * );
extern int     reltimer( timer_t, struct itimerspec *, struct itimerspec * );
extern int     abstimer( timer_t, struct itimerspec *, struct itimerspec * );
extern long    qnx_timerperiod( long nsec );
#ifdef __cplusplus
};
#endif

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __TIMERS_H_INCLUDED
#endif
