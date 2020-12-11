/*
 *  sidinfo.h   Session information data structures
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __SIDINFO_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

struct _sidinfo {
    mpid_t           pid;
    short int       zero1;
    short unsigned  sid;
    short int       zero2,
                    links;
    long            zero3;
    char            name[15];
    char            tty_name[32];
    } ;

#ifdef __cplusplus
extern "C" {
#endif
extern int     qnx_sid_query( pid_t, int, struct _sidinfo * );
#ifdef __cplusplus
};
#endif

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __SIDINFO_H_INCLUDED
#endif
