/*
 *  process.h   Process spawning and related routines
 *
 *  Copyright by WATCOM International Corp. 1988-1996.  All rights reserved.
 *  Copyright by QNX Software Systems Limited 1990-1996. All rights reserved.
 */
#ifndef _PROCESS_H_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

/*
 *  POSIX 1003.1 Prototypes
 */
extern int execl( const char *__path, const char *__arg0, ... );
extern int execle( const char *__path, const char *__arg0, ... );
extern int execlp( const char *__file, const char *__arg0, ... );
extern int execv( const char *__path, const char *const __argv[] );
extern int execve( const char *__path, const char *const __argv[], const char *const __envp[] );
extern int execvp( const char *__file, const char *const __argv[] );

#if defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS)
/*
 *  Spawn flags passed to qnx_spawn()
 *  These are unique to QNX
 */

#define _SPAWN_DEBUG        0x0001
#define _SPAWN_HOLD         0x0002
#define _SPAWN_BGROUND      0x0004
#define _SPAWN_NEWPGRP      0x0008
#define _SPAWN_TCSETPGRP    0x0010
#define _SPAWN_NOZOMBIE     0x0020
#define _SPAWN_XCACHE       0x0040
#define _SPAWN_SIGCLR       0x0080
#define _SPAWN_SETSID       0x0100
#define _SPAWN_NOHUP        0x0200

struct _proc_spawn;     /* for C++ */

extern pid_t qnx_spawn( int __mode, struct _proc_spawn *__msgbuf, nid_t __node,
                 int __prio, int __sched_algo, int __flags,
                 const char *__path, char **__argv, char **__envp,
                 char *__iov, int __ctfd );
                 
#ifdef __386__
extern pid_t tfork( char *__stk_addr, unsigned __stk_size, int (*__func)(void*),
                        void *__arg, int __flags );
#endif

/* mode flags for spawnxxx routines */
extern int __p_overlay;

#define P_WAIT      0
#define P_NOWAIT    1
#define P_OVERLAY   __p_overlay
#define P_NOWAITO   3

/*
 *  Prototypes for non-POSIX functions
 */

extern int execlpe( const char *__file, const char *__arg0, ... );
extern int execvpe( const char *__file, const char *const __argv[], const char *const __envp[] );

#ifdef __386__
extern int _beginthread( register void (*__start_address)(void *),
     void *__stack_bottom, unsigned __stack_size, void *__arglist );
extern void _endthread();
#endif
extern void abort(void);
extern void exit(int __status);
extern void _exit(int __status);
#if !(defined(SYSV) || defined(BSD) || defined(XENIX) || defined(_UNIX_H_INCLUDED))
extern char *getcmd(char *__buffer);
extern int _bgetcmd(char *__buffer, int __len);
extern char *_cmdname(char *__name);
#endif
extern char *getenv(const char *__name);
extern int putenv(const char *__string);
extern int spawnl(int __mode,const char *__path, const char *__arg0,...);
extern int spawnle(int __mode,const char *__path, const char *__arg0,...);
extern int spawnlp(int __mode,const char *__path, const char *__arg0,...);
extern int spawnlpe(int __mode,const char *__path, const char *__arg0,...);
extern int spawnv(int __mode,const char *__path,const char * const *__argv);
extern int spawnve(int __mode,const char *__path,const char * const *__argv,const char * const *__envp);
extern int spawnvp(int __mode,const char *__path,const char * const *__argv);
extern int spawnvpe(int __mode,const char *__path,const char * const *__argv,const char * const *__envp);
extern int system(const char *__cmd);

extern pid_t getpid(void);
extern pid_t wait(int *__status);

#endif

#define _PROCESS_H_INCLUDED
#ifdef __cplusplus
};
#endif
#endif
