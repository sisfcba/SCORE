/*
 *  dumper.h    Dumper file structure
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __DUMPER_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#ifndef __SEGINFO_H_INCLUDED
 #include <sys/seginfo.h>
#endif

#ifndef __OSINFO_H_INCLUDED
 #include <sys/osinfo.h>
#endif

#ifndef __PSINFO_H_INCLUDED
 #include <sys/psinfo.h>
#endif

#ifndef __OSINFO_H_INCLUDED
 #include <sys/osinfo.h>
#endif

#ifndef __DEBUG_H_INCLUDED
 #include <sys/debug.h>
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

/*
 * The dump file starts with this header.
 */
struct _dumper_hdr {
    long                signature;  /* 0x64756d70 (dump)                    */
    short int           version;    /* Version number * 100                 */
    short int           zero;       /* Reserved                             */
    short int           numsegs;    /* Number of segment records            */
    short int           errnum;     /* Should be zero unless dumper failed  */
    char                errstr[32]; /* String if errnum non-zero            */
    long                cmdtime;    /* Date of the command at dump time     */
    struct _osinfo      osdata;     /* Machine environment at dump time     */
    short unsigned      numthreads; /* This should be 1 for now             */
    struct _psinfo      psdata;     /* Process environment at dump time     */
    struct _reg_struct  reg;        /* CPU registers at dump time           */
    char                x87[108];   /* 80x87 registers at dump time         */
    char                weitek[128];/* Weitek registers at dump time        */
    } ;

/*
 * One or more of these records follow the hdr.
 * The segdata field is variable length but will be a multiple of 256.
 * The number of bytes is kept in seghdr.nbytes.
 */
struct _dumper_rec {
    struct _seginfo seghdr;         /* Segment state at dump time           */
    char            segdata[256];   /* Segment data at dump time            */
    } ;

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __DUMPER_H_INCLUDED
#endif
