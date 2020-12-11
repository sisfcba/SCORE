/*
 *  pwd.h       Password operations
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 *  Copyright by WATCOM International Corp. 1988-1993.  All rights reserved.
 */
#ifndef _PWD_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif
#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif
struct passwd {
    char  *pw_name;     /*  User's login name           */
    char  *pw_passwd;
    uid_t  pw_uid;      /*  User ID number              */
    gid_t  pw_gid;      /*  Group ID number             */
    char  *pw_age;
    char  *pw_comment;
    char  *pw_gecos;
    char  *pw_dir;      /*  Initial Working Directory   */
    char  *pw_shell;    /*  Initial User Program        */
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
#ifdef __STDC__
extern struct passwd *getpwuid( uid_t uid );
extern struct passwd *getpwnam( const char * name );
extern struct passwd *getpwent( void );
extern int setpwent( void );
extern int endpwent( void );
#endif
#ifdef __cplusplus
};
#endif

#define _PWD_H_INCLUDED
#endif
