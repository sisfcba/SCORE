/*
 *  unistd.h
 *
 *  Copyright by WATCOM International Corp. 1988-1996.  All rights reserved.
 *  Copyright by QNX Software Systems Limited 1990-1996. All rights reserved.
 */
#ifndef _UNISTD_H_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif


#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#ifndef NULL
 #if defined(__SMALL__) || defined(__MEDIUM__) || defined(__386__)
  #define NULL   0
 #else
  #define NULL   0L
 #endif
#endif

/* Symbolic constants for the access() function */

#define R_OK    4       /*  Test for read permission    */
#define W_OK    2       /*  Test for write permission   */
#define X_OK    1       /*  Test for execute permission */
#define F_OK    0       /*  Test for existence of file  */

/* Symbolic constants for the lseek() function */

#ifndef _SEEKPOS_DEFINED_       /* If not already defined, define them  */
#define SEEK_SET    0           /* Seek relative to the start of file   */
#define SEEK_CUR    1           /* Seek relative to current position    */
#define SEEK_END    2           /* Seek relative to the end of the file */
#define _SEEKPOS_DEFINED_
#endif

/* Symbolic constants for stream I/O */

#define STDIN_FILENO    0
#define STDOUT_FILENO   1
#define STDERR_FILENO   2

/* Compile-time Symbolic Constants for Portability Specifications */

#undef  _POSIX_JOB_CONTROL              /* no job control                   */
#define _POSIX_SAVED_IDS    1           /* no saved-set user-ID & group-ID  */
#define _POSIX_VERSION      198808L     /* YYYYmm of POSIX std approval     */
#define _POSIX_PROCESS_SCHEDULING   1
#define _POSIX_TIMERS   1

/* Symbolic constants for sysconf */
/* caution: the module sysconf.c bound checks _SC_ARG_MAX ... _SC_PAGESIZE */
#define _SC_ARG_MAX         1
#define _SC_CHILD_MAX       2
#define _SC_CLK_TCK         3
#define _SC_NGROUPS_MAX     4
#define _SC_OPEN_MAX        5
#define _SC_JOB_CONTROL     6
#define _SC_SAVED_IDS       7
#define _SC_VERSION         8
#define _SC_STREAM_MAX      9
#define _SC_TZNAME_MAX      10
#define _SC_PAGESIZE        11
/* Execution-time Symbolic Constants for Portability Specifications */

#define _POSIX_CHOWN_RESTRICTED 0       /* restricted use of chown() */
#define _POSIX_NO_TRUNC         0       /* pathname components > NAME_MAX */
#define _POSIX_VDISABLE         0x00    /* terminal special chars can be disabled */

/* Symbolic constants for pathconf, fpathconf */

#define _PC_LINK_MAX            1
#define _PC_MAX_CANON           2
#define _PC_MAX_INPUT           3
#define _PC_NAME_MAX            4
#define _PC_PATH_MAX            5
#define _PC_PIPE_BUF            6
#define _PC_CHOWN_RESTRICTED    7
#define _PC_NO_TRUNC            8
#define _PC_VDISABLE            9
#define _PC_DOS_SHARE           10  /* test for dos share support   */
#define _PC_DOS_LOCKS           11  /* test for dos locking support */

#if defined(_POSIX_SOURCE) || !defined(NO_EXT_KEYS) /*extensions enabled*/

extern int   optind;        /*  index of current option being scanned */
extern char *optarg;        /*  points to optional argument */
extern int   opterr;        /*  print|don't print error message */
extern int   optopt;        /*  offending letter when error detected */

/* Symbolic constants for confstr */

#define _CS_PATH            1

#endif

/*
 *  POSIX 1003.1 Prototypes
 */

#if defined(_POSIX_SOURCE) || defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS)
extern void    _exit( int __status );
#endif

extern int      access( const char *__path, int __mode );
#if defined(__386__)
extern int      brk(void *endds);
extern void     *sbrk(int incr);
#endif
extern int      chdir( const char *__path );
extern int      close( int __fildes );
extern int      dup( int __fildes );
extern char     *getcwd( char *__buf, size_t __size );
extern pid_t    getpid( void );
extern int      isatty( int __fildes );
extern off_t    lseek( int __fildes, off_t __offset, int __whence );
extern ssize_t  read( int __fildes, void *__buffer, size_t __len );
extern int      rmdir( const char *__path );
#if !(defined(SYSV) || defined(BSD) || defined(XENIX) || defined(_UNIX_H_INCLUDED))
extern int      setmode( int __handle, int __mode );
#endif
extern unsigned int sleep( unsigned int __seconds );
extern int      unlink( const char *__path );
extern ssize_t  write( int __fildes, const void *__buf, size_t __len );
extern unsigned alarm( unsigned int __seconds );
extern int      chown( const char *__path, uid_t __owner, gid_t __group );
extern int      chroot(const char *__path);
extern int      dup2( int __fildes, int __fildes2 );
extern int      fchown( int __fildes, uid_t __owner, gid_t __group );
extern int      fdatasync( int __fildes );
extern int      fsync( int __fildes );
extern pid_t    fork( void );
extern long     fpathconf( int __fildes, int __name );
extern gid_t    getegid( void );
extern uid_t    geteuid( void );
extern gid_t    getgid( void );
extern int      getgroups( int __gidsetsize, gid_t __grouplist[] );
extern char     *getlogin( void );
extern pid_t    getpgrp( void );
extern pid_t    getppid( void );
extern pid_t    getsid(pid_t __pid);
extern uid_t    getuid( void );
extern int      link( const char *__path1, const char *__path2 );
extern int      mkdir( const char *__path, mode_t __mode );
extern int      mknod( const char *__path, mode_t __mode, int __dev );
extern int      mount( const char *__special, const char * __dir, int __rwflag );
extern long     pathconf( const char *__path, int __name );
extern int      pause( void );
extern int      pipe( int __fildes[2] );
extern int      readlink( const char *__path, char *__buf, size_t __bufsiz );
extern int      setegid( gid_t __newegroup );
extern int      seteuid( uid_t __newuserid );
extern int      setgid( gid_t __newgroup );
extern int      setpgid( pid_t __pid, pid_t __pgroupid );
extern int      setregid(gid_t real, uid_t effective);
extern int      setreuid(uid_t real, uid_t effective);
extern pid_t    setsid( void );
extern int      setuid( uid_t __newuserid );
extern int      symlink( const char *__pname, const char *__slink );
extern long     sysconf( int __name );
extern pid_t    tcgetpgrp( int __fildes );
extern int      tcsetpgrp( int __fildes, pid_t __pgrp_id );
extern int      tcsetct( int __fildes, pid_t pid );
extern char     *ttyname( int __fildes );
extern int      umount( const char *__special );

#if defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS) /*extensions enabled*/

extern int      chsize( int __fildes, long __size );
extern int      eof( int __fildes );
extern long     filelength( int __fildes );
extern off_t    tell( int __fildes );
extern nid_t    getnid( void );
extern int      lock( int __fildes, long __offset, long __nbytes );
extern void     qnx_display_msg( const char *__text );
extern void     qnx_display_hex( unsigned __value );
extern char     *qnx_fullpath( char * __fullpath, const char * __path );

struct _psinfo2; /* for C++ */

extern int      qnx_getids( pid_t pid, struct _psinfo2 *info);
extern int      qnx_setids( pid_t pid, int id, unsigned subtype );
extern int      qnx_sync( nid_t nid );
extern void     sync( void );
extern int      unlock( int __fildes, long __offset, long __nbytes );

#endif

#if defined(_POSIX_SOURCE) || !defined(NO_EXT_KEYS) /*extensions enabled*/
extern int      getopt( int __argc, char * const* __argv, const char * __optstring );
extern char     *basename( const char * __fname );
extern size_t   confstr( int, char*, size_t );
extern int      fnmatch( const char *__pattern, const char *__string, int __flag );
extern off_t    ltrunc( int __fildes, off_t __offset, int __origin );
extern int      putenv(const char * estring);
#endif

#if defined __386__
#define __far_read read
#define __far_write write
#else
extern ssize_t __far_read(int __fildes,void __far *__buffer,size_t __len);
extern ssize_t __far_write(int __fildes,void __far *__buffer,size_t __len);
#endif


#define _UNISTD_H_INCLUDED
#ifdef __cplusplus
};
#endif
#endif
