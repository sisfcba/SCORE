/*
 *  fcntl.h     File control options used by open
 *
 *  Copyright by WATCOM International Corp. 1988-1996.  All rights reserved.
 *  Copyright by QNX Software Systems Limited 1990-1996. All rights reserved.
 */
#ifndef _FCNTL_H_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif
#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif


#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

/*
 *  Flag values accessible to both open() and fcntl()
 *  (The first three can only be set by open)
 */

/*
 *  File access modes.
 */

#define O_RDONLY    000000  /*  Read-only mode  */
#define O_WRONLY    000001  /*  Write-only mode */
#define O_RDWR      000002  /*  Read-Write mode */

/*
 *  Mask for file access modes.
 */

#define O_ACCMODE   000003

/*
 *  File status flags used for open() and fcntl().
 */

#define O_NONBLOCK  000200  /*  Non-blocking I/O                */
#define O_APPEND    000010  /*  Append (writes guaranteed at the end)   */

/*
 *  The synchronous I/O status flags are taken from POSIX.4 (draft).
 *  This implementation doesn't fully support sync I/O (yet)
 *  (no function RTFSYNCH),
 *  but it does support the status flags for READ and WRITE.
 */

#if defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS)
#if 0
/*
 *  Old definitions based on early POSIX.4 draft.
 */
#define O_DSYNCH    000020  /*  Data integrity synch    */
#define O_FSYNCH    000040  /*  File integrity synch    */
#define O_SYNC      000020
#else
#define O_DSYNC     000020  /*  Data integrity synch    */
#define O_SYNC      000040  /*  File integrity synch    */
#endif
#endif

#define O_PRIV      010000

/*
 *  oflag values for open()
 */

#define O_CREAT     000400  /*  Opens with file create      */
#define O_TRUNC     001000  /*  Open with truncation        */
#define O_EXCL      002000  /*  Exclusive open          */
#define O_NOCTTY    004000  /*  Don't assign a controlling terminal */

#if defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS)
#define O_TEMP      010000  /*  Temporary file, don't put to disk   */
#define O_CACHE     020000  /*  Cache sequential files too      */
#define O_TEXT      000000  /*  Text file   (DOS thing)     */
#define O_BINARY    000000  /*  Binary file (DOS thing)     */
#endif

/*
 *  fcntl() requests
 */

#define F_DUPFD     0       /*  Duplicate file descriptor   */
#define F_GETFD     1       /*  Get file descriptor flags   */
#define F_SETFD     2       /*  Set file descriptor flags   */
#define F_GETFL     3       /*  Get file status flags   */
#define F_SETFL     4       /*  Set file status flags   */

/*#define F_GETOWN    35*/  /* get SIGIO/SIGURG proc/pgrp */
/*#define F_SETOWN    36*/  /* set SIGIO/SIGURG proc/pgrp */

#define F_SETLK     6       /*  Set record locking info */
#define F_SETLKW    7       /*  Set record locking info;    */
                /*  wait if blocked     */
#define F_CHKFL     8       /*              */
#define F_ALLOCSP   10      /*              */
#define F_FREESP    11      /*              */
#define F_ISSTREAM  13      /*              */
#define F_GETLK     14      /*  Get record locking info */
#define F_PRIV      15      /*              */
#define F_NPRIV     16      /*              */
#define F_QUOTACTL  17      /*              */
#define F_BLOCKS    18      /*              */
#define F_BLKSIZE   19      /*              */

#define F_RSETLK    20      /*              */
#define F_RGETLK    21      /*              */
#define F_RSETLKW   22      /*              */

/*
 *  File descriptor flags used for fcntl()
 */

#define FD_CLOEXEC  0x01    /*  Close on exec       */

/*
 *  l_type values for record locking with fcntl()
 */

#define F_RDLCK     1       /*  Shared or read lock     */
#define F_WRLCK     2       /*  Exclusive or write lock */
#define F_UNLCK     3       /*  Unlock          */

/*
 *  flock structure.
 */

typedef struct flock {
    short int   l_type;
    short int   l_whence;
    off_t       l_start;
    off_t       l_len;
    long        l_sysid;
    pid_t       l_pid;
#if !defined __386__
    short int   l_pid_pad;
#endif
    short int   zero[3];
} flock_t;

/*
 *  POSIX 1003.1 Prototypes.
 */
extern int open( const char *__path, int __oflag, ... );
extern int sopen( const char *__path, int __oflag, int __share, ... );
extern int creat( const char *__path, mode_t __mode );

struct _io_open; /* for C++ */

extern int fcntl( int __fildes, int __cmd, ... );
extern int __fcntl_slib( int, int, int, struct flock * );
extern int __open_slib( const char *__path, int __oflag, mode_t __mode );
extern int __sopen_slib( const char *__path, int __oflag, int __share, mode_t __mode );
extern int __resolve_net( unsigned, int, struct _io_open *, const char *, unsigned, char * );

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define _FCNTL_H_INCLUDED
#ifdef __cplusplus
};
#endif
#endif
