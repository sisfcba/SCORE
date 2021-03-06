/*
 *  signal.h    Signal definitions
 *
 *  Copyright by WATCOM International Corp. 1988-1996.  All rights reserved.
 *  Copyright by QNX Software Systems Limited 1990-1996. All rights reserved.
 */
#ifndef _SIGNAL_H_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif
typedef int     sig_atomic_t;

#ifdef __386__
#define __SIG_FAR
#else
#define __SIG_FAR __far
#endif

#if defined(_POSIX_SOURCE) || defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS)
#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif
#ifdef __NEUTRINO__
typedef struct {
    long    nrt;
    long   rt;
    } sigset_t;
#else
typedef long    sigset_t;       /* Used for signal sets             */
#endif
struct sigaction {
    void        (__SIG_FAR *sa_handler)(int);
    sigset_t    sa_mask;
    int         sa_flags;
};
struct _sigaction {
    void        (__SIG_FAR *sa_handler)(int);
    sigset_t sa_mask;
    short int sa_flags;
};

union sigval {
    int         sigval_int;
    void       *sigval_ptr;
};

#ifdef __386__
typedef struct stack_t stack_t;
struct stack_t {
	void         *ss_sp;
	size_t        ss_size;
	int           ss_flags;
	ushort_t      ss_seg;   /* should always be zero; but incase */
};

#define SS_ONSTACK        (1<<0)
#define SS_DISABLE        (1<<1)

#define _SS_SETSEG         (1<<8)

extern int sigaltstack(const stack_t *ss, stack_t *oss);

#endif

#ifndef __NEUTRINO__
struct sigevent {
    int          sigev_signo;
    union sigval sigev_value;
};
struct msigevent {
    long         sigev_signo;
    union sigval sigev_value;
};
#endif
#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif
#endif  /* _POSIX_SOURCE || _QNX_SOURCE || !NO_EXT_KEYS */

typedef void (__SIG_FAR *__far_sig_func)( int );
typedef void (*__sig_func)( int );

#define __FAR_SIG_ERR       ((__far_sig_func)(unsigned)-1)
#define __FAR_SIG_DFL       ((__far_sig_func)(unsigned)0)
#define __FAR_SIG_IGN       ((__far_sig_func)(unsigned)1)
#define __FAR_SIG_HOLD      ((__far_sig_func)(unsigned)2)

#define SIG_ERR             ((__sig_func)__FAR_SIG_ERR)
#define SIG_DFL             ((__sig_func)__FAR_SIG_DFL)
#define SIG_IGN             ((__sig_func)__FAR_SIG_IGN)
#define SIG_HOLD            ((__sig_func)__FAR_SIG_HOLD)

#define SIGHUP      1   /* hangup */
#define SIGINT      2   /* interrupt */
#define SIGQUIT     3   /* quit */
#define SIGILL      4   /* illegal instruction (not reset when caught) */
#define SIGTRAP     5   /* trace trap (not reset when caught) */
#define SIGIOT      6   /* IOT instruction */
#define SIGABRT     6   /* used by abort */
#define SIGEMT      7   /* EMT instruction */
#define SIGFPE      8   /* floating point exception */
#define SIGKILL     9   /* kill (cannot be caught or ignored) */
#define SIGBUS      10  /* bus error */
#define SIGSEGV     11  /* segmentation violation */
#define SIGSYS      12  /* bad argument to system call */
#define SIGPIPE     13  /* write on pipe with no reader */
#define SIGALRM     14  /* real-time alarm clock */
#define SIGTERM     15  /* software termination signal from kill */
#define SIGUSR1     16  /* user defined signal 1 */
#define SIGUSR2     17  /* user defined signal 2 */
#define SIGCHLD     18  /* death of child */
#define SIGPWR      19  /* power-fail restart */
#define SIGWINCH    20  /* window change */
#define SIGURG      21  /* urgent condition on I/O channel */
#define SIGPOLL     22  /* System V name for SIGIO */
#define SIGIO       22  /* Asynchronus I/O */
#define SIGSTOP     23  /* sendable stop signal not from tty */
#define SIGTSTP     24  /* stop signal from tty */
#define SIGCONT     25  /* continue a stopped process */
#define SIGTTIN     26  /* attempted background tty read */
#define SIGTTOU     27  /* attempted background tty write */
#define SIGDEV      28  /* Dev event */

#define _SIGMAX     32
#define _SIGMIN     1

/* sigprocmask() flags */
#define SIG_BLOCK   0
#define SIG_UNBLOCK 1
#define SIG_SETMASK 2

#define SA_NOCLDSTOP    1

int  raise( int __sig );
extern void     (*signal( int __sig, void (*__func)(int) ))(int);
#if defined(_POSIX_SOURCE) || defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS)
extern int      kill( pid_t __pid, int __signum );
extern int      sigaction( int __signo, const struct sigaction *__act, struct sigaction *__oact );
extern int      sigaddset( sigset_t *__set, int __signo );
extern int      sigdelset( sigset_t *__set, int __signo );
extern int      sigemptyset( sigset_t *__set );
extern int      sigfillset( sigset_t *__set );
extern int      sigismember( sigset_t *__set, int __signo );
extern int      sigpending( sigset_t *__set );
extern int      sigprocmask( int __how, const sigset_t *__set, sigset_t *__oset );
extern int      sigsuspend( const sigset_t *sigmask );
#endif  /* _POSIX_SOURCE || _QNX_SOURCE || !NO_EXT_KEYS */

#define _SIGNAL_H_INCLUDED
#ifdef __cplusplus
};
#endif
#endif
