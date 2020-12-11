/*
 *  proxy.h     Proxy process prototypes
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __PROXY_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
extern pid_t   qnx_proxy_attach( pid_t, const void *, int, int );
extern int     qnx_proxy_detach( pid_t );
extern pid_t   qnx_proxy_rem_attach( nid_t, pid_t );
extern int     qnx_proxy_rem_detach( nid_t, pid_t );
#ifdef __cplusplus
};
#endif

#define __PROXY_H_INCLUDED
#endif
