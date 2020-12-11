/*
 *  fsysinfo.h  Non-portable file system information definitions
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __FSYSINFO_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

struct _fsysinfo {
    short unsigned  version,        /*  Correct structure if version == 2   */
                    zero0;
    time_t          reset_time;
    unsigned long   cache_lookups,
                    cache_writes,
                    cache_hits,     /*  User data only                      */
                    cache_misses,   /*  User data only                      */
                    disk_reads,
                    disk_writes,
                    namei_calls,
                    open_calls,
                    stat_calls,
                    fstat_calls,
                    read_calls,
                    write_calls,
                    cache_delayed_hits, /*  User data only                  */
                    metadata_hits,  /*  Metadata only (zero in version 1)   */
                    metadata_misses,/*  Metadata only (zero in version 1)   */
                    icache_hits,    /*  inode cache (version 3+)            */
                    icache_misses,  /*  inode cache (version 3+)            */
                    ncache_hits,    /*  name cache (version 3+)             */
                    ncache_misses,  /*  name cache (version 3+)             */
                    ncache_2long ,  /*  names too long for cache (ver 3+)   */
                    ncache_neghits, /*  name cache (version 3+)             */
                    ncache_badhits, /*  name cache (version 3+)             */
                    zero1;
    short unsigned  num_inodes_used,
                    max_inodes_used,
                    num_inodes,
                    num_files_used,
                    max_files_used,
                    num_files,
                    num_locks_used,
                    max_locks_used,
                    num_locks,
                    num_threads_active,
                    max_threads_active,
                    num_threads,
                    num_inodes_allocd,  /*  version 3+                      */
                    num_names_allocd,   /*  version 3+                      */
                    max_names,          /*  version 3+                      */
                    zero2[17];
    } ;


#ifdef __cplusplus
extern "C" {
#endif
extern int     __fsysinfo( int fd, struct _fsysinfo *buf, int reset );
extern int     fsysinfo( const char *path, struct _fsysinfo *buf, int reset );
#ifdef __cplusplus
};
#endif

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __FSYSINFO_H_INCLUDED
#endif
