/*
 *  osstat.h
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __OSSTAT_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

struct _osstat {
     unsigned short cpu_ready[32],
                    zero1[32],
                    cpu_load[32],
                    zero2[32];
     struct _oslimits {
          unsigned short xids[3],
                         pids[3],
                         mids[3],
                         vids[3],
                         names[3],
                         sessions[3],
                         timers[3],
                         devices[3],
                         events[3],
                         qpkts[3];
                    } limits;
     unsigned short zero3[98];
    } ;


#ifdef __cplusplus
extern "C" {
#endif
extern int      qnx_osstat( nid_t, struct _osstat * );
#ifdef __cplusplus
};
#endif

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __OSSTAT_H_INCLUDED
#endif
