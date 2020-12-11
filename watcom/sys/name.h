/*
 *  name.h
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __NAME_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

struct _nameinfo {
    nid_t           nid;
    mpid_t          pid;
    short unsigned  zero1,
                    zero2[4];
    char            name[33];
    } ;

#ifdef __cplusplus
extern "C" {
#endif
extern int      qnx_name_attach( nid_t, const char * );
extern int      qnx_name_detach( nid_t, int );
extern pid_t    qnx_name_locate( nid_t, const char *, unsigned, unsigned * );
extern int      qnx_name_locators( nid_t * );
extern int      qnx_name_query( pid_t, int, struct _nameinfo * );
extern int      qnx_name_nodes( pid_t, const char *, unsigned, nid_t * );
extern int      qnx_net_alive( char *, int );
#ifdef __cplusplus
};
#endif

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __NAME_H_INCLUDED
#endif
