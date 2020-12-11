/*-
 *  shadow.h       Shadow file operations.
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 *  Copyright by WATCOM International Corp. 1988-1993.  All rights reserved.
 */

#if !defined _SHADOW_H_INCLUDED
#define _SHADOW_H_INCLUDED

#ifndef _PWD_H_INCLUDED
#include <pwd.h>
#endif

#ifndef _STDIO_H_INCLUDED
#include <stdio.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

struct    spwd {
        char    *sp_namp;     /* name */
        char    *sp_pwdp;     /* encrypted password */
        long    sp_lstchg;    /* last changed */
        long    sp_max;       /* #days (min) to change */
        long    sp_min;       /* #days (max) to change */
        long    sp_warn;      /* #days to warn */
        long    sp_inact;     /* #days of inactivity */
        long    sp_expire;    /* date to auto-expire */
        long    sp_flag;      /* reserved */
};

#define SPFIELDS 9


#define SHADOW        "/etc/shadow"
#define OSHADOW       "/etc/oshadow"
#define NSHADOW       "/etc/nshadow"

#define PASSWD        "/etc/passwd"
#define OPASSWD        "/etc/opasswd"
#define NPASSWD        "/etc/npasswd"



extern void  setspent();
extern void  endspent();
extern int   putspent(const struct spwd *,FILE *);

extern struct spwd   *getspent(void);
extern struct spwd   *getspnam(char *name);
extern struct spwd   *sgetspent(char *string);
extern struct spwd   *fgetspent(FILE *f);

#ifdef __cplusplus
}
#endif

#endif
