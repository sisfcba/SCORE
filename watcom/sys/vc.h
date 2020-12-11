/*
 *  _vc.h    QNX 4.0+ net  public defines and prototypes
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __VC_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

/* the following are public values for the flags bitfield in qnx_vc_attach */
#define _VC_AT_FIRST        0x0000
#define _VC_AT_SHARE        0x0001
#define _VC_AT_REM_ZOMBIE   0x0002

/* maximum string length for qnx_vc_name_attach() */
#define _VC_MAX_NAME_LEN    32

/* data struct used by qnx_vc_poll_parm() */
#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif
struct _vc_poll_parm_set {
    long            poll_period;            /*  4 bytes */
    long            idle_time;              /*  4 bytes */
    long            max_idle_time;          /*  4 bytes */ 
    short           num_polls;              /*  2 bytes */ 
    short           num_qpkts;              /*  2 bytes */ 
    long            zero1;              /*  4 bytes */
    long            zero2;              /*  4 bytes */
    } ;
#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif
#ifdef __cplusplus
extern "C" {
#endif
extern nid_t    qnx_strtonid(const char *nodename, char **str);
extern int      qnx_nidtostr(nid_t nid, char *bufp, int maxbuf);
extern pid_t    qnx_vc_attach( nid_t, pid_t, unsigned, int );
extern int      qnx_vc_detach( pid_t );
extern pid_t    qnx_vc_name_attach( nid_t, unsigned, char * );
extern int      qnx_vc_poll_parm( pid_t, struct _vc_poll_parm_set *);
extern int      qnx_vc_refresh( void );
#ifdef __cplusplus
};
#endif

#define __VC_H_INCLUDED
#endif
