/*
 *  qnx_glob.h  QNX global data area
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __QNX_GLOB_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

struct _proc_spawn;     /* for C++ */

struct _qnx_spawn_globs {
    struct _proc_spawn  *msgbuf;
    nid_t            node;
    char             priority;
    char             sched_algo;
    short int        flags;
    char             iov[10];
    char             ctfd;
    char             reserved1;
    short int        reserved2[5];
    } ;

#ifdef __cplusplus
extern "C" {
#endif
extern struct _qnx_spawn_globs qnx_spawn_options;
#ifdef __cplusplus
};
#endif

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __QNX_GLOB_H_INCLUDED
#endif
