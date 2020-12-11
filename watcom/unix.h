#ifndef _UNIX_H_INCLUDED
#define _UNIX_H_INCLUDED

#include <unistd.h>
#include <time.h>
#include <termcap.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <process.h>
#include <fcntl.h>
#include <errno.h>

#ifndef __VALIST
 #ifdef  __HUGE__
  typedef char __far *__va_list[1];
 #else
  typedef char *__va_list[1];
 #endif
 #define __VALIST
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif
union wait {
        int     w_status;                       /* used in syscall */
        /*
         * Terminated process status.
         */
#define w_termsig       w_T.w_Termsig
#define w_coredump      w_T.w_Coredump
#define w_retcode       w_T.w_Retcode
        struct {
                unsigned short  w_Termsig:7;    /* termination signal */
                unsigned short  w_Coredump:1;   /* core dump indicator */
                unsigned short  w_Retcode:8;    /* exit code if w_termsig==0 */
        } w_T;
        /*
         * Stopped process status.  Returned
         * only for traced children unless requested
         * with the WUNTRACED option bit.
         */
#define w_stopval       w_S.w_Stopval
#define w_stopsig       w_S.w_Stopsig
        struct {
                unsigned short  w_Stopval:8;    /* == W_STOPPED if stopped */
                unsigned short  w_Stopsig:8;    /* signal that stopped us */
        } w_S;
};
#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif
typedef void (*sig_t)(int);

#define ftruncate       chsize
#define killpg(p,s)     kill(-(p),s)
#define nap             delay
#define napms           delay
#define realpath(p,r)   qnx_fullpath(r,p)
#define sigmask(s)      (1L<<((s)-1))

#ifndef HZ
#define HZ              CLK_TCK
#endif

#define L_SET           SEEK_SET
#define L_INCR          SEEK_CUR
#define L_XTND          SEEK_END

#ifndef MAXNAMLEN
#define MAXNAMLEN       NAME_MAX
#endif
#ifndef MAXPATHLEN
#define MAXPATHLEN      PATH_MAX
#endif

#ifndef NOFILE
#define NOFILE          20
#endif

#ifndef O_NDELAY
#define O_NDELAY        O_NONBLOCK
#endif

#define NSIG            _SIGMAX
#define SIGCLD          SIGCHLD

#ifdef __cplusplus
extern "C" {
#endif
#ifndef alloca
extern void *  alloca(unsigned size);
#endif
#ifndef bcmp
extern int     bcmp(const void *d, const void *s, size_t n);
#endif
#ifndef bcopy
extern void    bcopy(const void *s, void *d, size_t n);
#endif
extern int     brk(void *top);
#ifndef bzero
extern void    bzero(void *d, size_t n);
#endif
extern int     eaccess(const char *filename, int mode);
extern int     flock(int fd, int operation);
extern int     getdtablesize(void);
extern int     gethostname(char *buffer, int buffer_length);
extern char *  getpass(const char *prompt);
extern pid_t   getpgid(pid_t pid);
extern int     getsid(int pid);
extern char *  getwd(char *buffer);
extern int     openpty(int *amaster,int *aslave,char *name,struct termios *termp,struct winsize *winp);
extern int     forkpty(int *amaster,char *name,struct termios *termp,struct winsize *winp);
extern int     login_tty(int fd);
#ifndef index
extern char *  index(const char *s, int c);
#endif
extern int     lockf(int fd, int cmd, long size);
extern char *  mktemp(char *_template);
extern int     mkstemp(char *_template);
extern int     nice(int value);
extern char *  re_comp(char *s);
extern int     re_exec(char *s);
#ifndef rindex
extern char *  rindex(const char *s, int c);
#endif
extern int     setlinebuf(FILE *stream);
extern int     setlogin(const char *name);
extern int     setpgrp(void);
extern int     snprintf(char *buffer, size_t bufsize, const char *format, ...);
extern int     vsnprintf(char *buffer, size_t bufsize, const char *format, __va_list vl);
#ifndef strcasecmp
extern int     strcasecmp(const char *s1, const char *s2);
#endif
#ifndef strcasencmp
extern int     strcasencmp(const char *s1, const char *s2, size_t n);
#endif
extern char *  tempnam(const char *directory, char *prefix);
extern int     tgetent(char *, char *);
extern char *  tgetstr(char *, char **);
extern int     tgetnum(char *);
extern int     tgetflag(char *);
extern char *  tgoto(char *, int, int);
#ifndef toascii
#define toascii( c )                    ((unsigned)(c) & 0x007f)
#endif
extern int     tputs(char *, int, int (*)());
extern int     truncate(char *path, off_t length);
extern int     vfork(void);

extern int     sighold(int sig);
extern int     sigignore(int sig);
extern int     sigrelse(int sig);
extern void    (*sigset(int sig, void (*handler)(int)))(int);

extern sigset_t sigblock(sigset_t mask);
extern sigset_t sigpause(sigset_t mask);
extern sigset_t sigsetmask(sigset_t mask);
extern sigset_t sigunblock(sigset_t mask);

extern double  drand48(void);
extern double  erand48(unsigned short x[3]);
extern unsigned long lrand48(void);
extern unsigned long nrand48(unsigned short x[3]);
extern unsigned short *seed48(unsigned short seed[3]);
extern void    lcong48(unsigned short param[7]);
extern void    srand48(long seed);
#ifdef __cplusplus
};
#endif

#if defined __SW_3R
#  pragma library (unix3r)
#elif defined __SW_3S
#  pragma library (unix3s)
#elif defined __SMALL__
#  pragma library (unixs)
#elif defined __COMPACT__
#  pragma library (unixc)
#elif defined __MEDIUM__
#  pragma library (unixm)
#elif defined __LARGE__
#  pragma library (unixl)
# endif

#endif
