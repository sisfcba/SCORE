/*
 *  sys/utime.h utimbuf structure and prototypes
 *
 *  Copyright by WATCOM International Corp. 1988-1996.  All rights reserved.
 *  Copyright by QNX Software Systems Limited 1990-1996. All rights reserved.
 */
#ifndef _UTIME_H_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif


#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

#ifndef _TIME_T_DEFINED_
 #define _TIME_T_DEFINED_
 typedef signed long time_t;     /* time value */
#endif

struct utimbuf {
    time_t      actime;         /* access time */
    time_t      modtime;        /* modification time */
};

/*
 *  POSIX 1003.1 Prototype
 */
extern int utime( const char *__path, const struct utimbuf * __times );
extern int __futime( int __fildes, const struct utimbuf * __times );

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif
#define _UTIME_H_INCLUDED
#ifdef __cplusplus
};
#endif
#endif
