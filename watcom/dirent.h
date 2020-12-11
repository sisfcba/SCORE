/*
 *  dirent.h    Portable directory entry definitions
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 *  Copyright by WATCOM International Corp. 1988-1993.  All rights reserved.
 */
#ifndef _DIRENT_H_INCLUDED

#define _DIRBUF  8  /*  Max number of dir entries buffered  */

#ifndef __STAT_H_INCLUDED
 #include <sys/stat.h>
#endif

#ifndef _LIMITS_H_INCLUDED
 #include <limits.h>
#endif

/*
 *  File status (d_status) bits.
 */
#ifndef _FILE_USED
 #define _FILE_USED 0x01
#endif
#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif
/*
 *  The d_stat data is valid if d_stat.st_status & _FILE_USED
 *  If it is not flagged as used, you must call stat() to get the data.
 */
struct dirent {
    struct stat d_stat;
    char        d_name[1 + NAME_MAX];
};


typedef struct _dir {
    short   dd_fd,          /*  file descriptor     */
            dd_loc,         /*  index into array    */
            dd_size;        /*  num array elements  */
    struct dirent   dd_buf[_DIRBUF];    /*  _dir_entry array    */
    char        dd_prefixes[PATH_MAX + 1];  /*  qnx_prefix_query    */
} DIR;
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
extern DIR      *opendir( const char *__dirname );
extern struct dirent    *readdir( DIR *__dirp );
extern void      rewinddir( DIR *__dirp );
extern int       closedir( DIR *__dirp );
#ifdef __cplusplus
};
#endif

#define _DIRENT_H_INCLUDED
#endif
