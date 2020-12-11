/*
 *  prfx.h  File prefix prototypes
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __PRFX_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#define _PREFIX_NAME_ONLY   0x0001

#ifdef __cplusplus
extern "C" {
#endif
extern int  qnx_prefix_attach( const char *, const char *, short unsigned );
extern int  qnx_prefix_detach( const char * );
extern int  qnx_prefix_query( nid_t, const char *, char *, int );
extern int  qnx_prefix_setroot( const char * );
extern char *qnx_prefix_getroot( void );
#ifdef __cplusplus
};
#endif

#define __PRFX_H_INCLUDED
#endif
