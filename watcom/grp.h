/*
 *  grp.h   Group operations
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 *  Copyright by WATCOM International Corp. 1988-1993.  All rights reserved.
 */
#ifndef _GRP_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif
#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif
struct group {
    char  *gr_name;
    char  *gr_passwd;
    gid_t  gr_gid;
    char **gr_mem;
};
#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif
/*
 *  POSIX 1003.1 Prototypes.
 */
#ifdef __cplusplus
extern "C" {
#endif
extern struct group *getgrnam( const char * name );
extern struct group *getgrgid( gid_t gid );
extern struct group *getgrent( void );
extern int setgrent( void );
extern int endgrent( void );
#ifdef __cplusplus
};
#endif

#define _GRP_H_INCLUDED
#endif
