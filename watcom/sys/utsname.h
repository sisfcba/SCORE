/*
 *  utsname.h   UTSNAME info
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __UTSNAME_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#ifndef __OSINFO_H_INCLUDED
 #include <sys/osinfo.h>
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

struct utsname {
    char    *sysname,
        *nodename,
        *release,
        *version,
        *machine,
        *bits;
};

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#ifdef __cplusplus
extern "C" {
#endif
extern int  uname( struct utsname *name );
#ifdef __cplusplus
};
#endif

#define __UTSNAME_H_INCLUDED
#endif
