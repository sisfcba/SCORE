/*
 *  wait.h  Define system wait types
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __WAIT_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

/*
 * Defined system wait types
 */
#define WNOHANG     1
#define WUNTRACED   0

/*
 * Define 1003.1 macros.
 */
#define WIFEXITED(stat_val)   (((stat_val) & 0x7f) == 0)
#define WIFSIGNALED(stat_val) (((stat_val) & 0x7f) != 0)
#define WIFSTOPPED(stat_val)  (0)
#define WEXITSTATUS(stat_val) (((stat_val) >> 8) & 0xff)
#define WTERMSIG(stat_val)    (((stat_val) & 0x7f))
#define WSTOPSIG(stat_val)    (0)

/*
 *  POSIX 1003.1 Prototypes.
 */
#ifdef __cplusplus
extern "C" {
#endif
extern pid_t wait( int *__stat_loc );
extern pid_t waitpid( pid_t __pid, int *__stat_loc, int __options );
#ifdef __cplusplus
};
#endif

#define __WAIT_H_INCLUDED
#endif
