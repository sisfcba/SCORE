/*
 *  time.h      Time functions
 *
 *  Copyright by WATCOM International Corp. 1988-1996.  All rights reserved.
 */
#ifndef _TIME_H_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif
#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif


#ifndef _SIZE_T_DEFINED_
#define _SIZE_T_DEFINED_
 typedef unsigned size_t;
#endif

#ifndef NULL
 #if defined(__SMALL__) || defined(__MEDIUM__) || defined(__386__)
  #define NULL   0
 #else
  #define NULL   0L
 #endif
#endif

#ifndef _TIME_T_DEFINED_
 #define _TIME_T_DEFINED_
 typedef signed long time_t;     /* time value */
#endif


#ifndef _CLOCK_T_DEFINED
 #define _CLOCK_T_DEFINED
 typedef unsigned long  clock_t;
#endif

#define CLOCKS_PER_SEC  1000

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#if defined(_POSIX_SOURCE) || defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS)
#ifndef _TIMER_T_DEFINED_
 #define _TIMER_T_DEFINED_
 typedef int timer_t;            /* timer type */
#endif

#ifndef _CLOCKID_T_DEFINED_
 #define _CLOCKID_T_DEFINED_
 typedef int clockid_t;          /* clockid type */
#endif

#define CLK_TCK     1000

/* 1003.4/D12 Clocks and Timers */
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
    struct /*event*/ {
        long evt_value;     /* Will hold a proxy or a signal */
        }   itcb_event;
    int     itcb_count;
    } ;
#endif


/*  Clock types */
#define CLOCK_REALTIME      0

/* Timer settime flags */
#define TIMER_ABSTIME           0x0001
#define TIMER_ADDREL            0x0100
#define TIMER_PRESERVE_EXEC     0x0200
#define TIMER_AUTO_RELEASE      0x0400

/* QNX msg notify types */
#define _TNOTIFY_SLEEP      0
#define _TNOTIFY_PROXY      1
#define _TNOTIFY_MESSENGER  1
#define _TNOTIFY_SIGNAL     2

/* ticksize flags */
#define _TICKSIZE_STANDARD  0
#define _TICKSIZE_CLOSEST   1
#define _TICKSIZE_EXTERNAL  2

extern int clock_gettime(clockid_t clock_id, struct timespec *tp );
extern int clock_settime(clockid_t clock_id, struct timespec *tp );
extern int clock_getres(clockid_t clock_id, struct timespec *res );
extern int clock_setres(clockid_t clock_id, struct timespec *res );
#if defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS) /*extensions enabled*/
extern int qnx_getclock( pid_t pid, clockid_t clock_id, struct timespec *tp );
extern int qnx_setclock( pid_t pid, clockid_t clock_id, struct timespec *tp );
extern int qnx_clock( nid_t nid, clockid_t clock_id, struct timespec *tp );
#endif

struct sigevent; /* for C++ */

extern timer_t timer_create ( clockid_t clock_id, struct sigevent *evp );
extern int timer_delete ( timer_t timerid );
extern int timer_gettime ( timer_t timerid, struct itimerspec *value );
extern int timer_settime ( timer_t timerid, int flags,
                 struct itimerspec *value, struct itimerspec *ovalue );
#if defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS) /*extensions enabled*/
extern long qnx_timerperiod( long );
extern long qnx_ticksize( long nsec, int flags );
extern int qnx_adj_time(long, long, long *, long *);
#endif

extern int nanosleep( const struct timespec *rqtp, struct timespec *rmtp );
#endif

struct  tm {
        int  tm_sec;    /* seconds after the minute -- [0,61] */
        int  tm_min;    /* minutes after the hour   -- [0,59] */
        int  tm_hour;   /* hours after midnight     -- [0,23] */
        int  tm_mday;   /* day of the month         -- [1,31] */
        int  tm_mon;    /* months since January     -- [0,11] */
        int  tm_year;   /* years since 1900                   */
        int  tm_wday;   /* days since Sunday        -- [0,6]  */
        int  tm_yday;   /* days since January 1     -- [0,365]*/
        int  tm_isdst;  /* Daylight Savings Time flag */
};

extern char *asctime( const struct tm *__timeptr );
extern clock_t clock( void );
extern char *ctime( const time_t *__timer );
extern double difftime( time_t __t1, time_t __t0 );
extern struct tm *gmtime( const time_t *__timer );
extern struct tm *localtime( const time_t *__timer );
extern time_t mktime( struct tm *__timeptr );
extern size_t strftime( char *__s, size_t __maxsiz, const char *__fmt,
                 const struct tm *__tp );
extern time_t time( time_t *__timer );

#ifndef __cplusplus
#define difftime(t1,t0) ((double)(t1)-(double)(t0))
#endif

#if defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS) /*extensions enabled*/
extern char *_asctime( const struct tm *__timeptr, char *__buf );
extern char *_ctime( const time_t *__timer, char *__buf );
extern struct tm *_gmtime( const time_t *__timer, struct tm *__tmbuf );
extern struct tm *_localtime( const time_t *__timer, struct tm *__tmbuf );
extern char *_strdate( char *__buf );
extern char *_strtime( char *__buf );
#endif

#if defined(_POSIX_SOURCE) || defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS)
extern void tzset( void );
extern int __CacheOSTZ( int __new_flag );

 extern char    *tzname[2]; /*  time zone names */
#if defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS) /*extensions enabled*/
 extern long    timezone;       /* # of seconds from GMT */
 extern int     daylight;       /* d.s.t. indicator */
#endif
#endif

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define _TIME_H_INCLUDED
#ifdef __cplusplus
};
#endif
#endif
