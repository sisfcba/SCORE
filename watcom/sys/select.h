/*
 *  sys/select.h
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */

#ifndef __SELECT_H_INCLUDED
#define __SELECT_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _SYS_TIME_H_
#include <sys/time.h>
#endif

#ifndef _STRING_H_INCLUDED
#include <string.h>
#endif

#ifndef _LIMITS_H_INCLUDED
#include <limits.h>
#endif

#ifndef FD_SETSIZE
#define FD_SETSIZE  32
#endif

#pragma pack(1)
typedef struct fd_set {
    int fds_bits[(FD_SETSIZE + sizeof(int) * CHAR_BIT - 1) / (sizeof(int) * CHAR_BIT)];
} fd_set;
#pragma pack()

#define FD_SET(fd, p)   ((p)->fds_bits[(fd)/(sizeof(int)*CHAR_BIT)] |= \
                (1 << ((fd) % ((sizeof(int))*CHAR_BIT))))

#define FD_CLR(fd, p)   ((p)->fds_bits[(fd)/(sizeof(int)*CHAR_BIT)] &= \
                ~(1 << ((fd) % (sizeof(int)*CHAR_BIT))))

#define FD_ISSET(fd, p) ((p)->fds_bits[(fd)/(sizeof(int)*CHAR_BIT)] & \
                (1 << ((fd) % (sizeof(int)*CHAR_BIT))))

#define FD_ZERO(p)  memset((p), 0, sizeof *(p))

extern int select(int width, fd_set *readfds, fd_set *writefds, fd_set *exceptfds, struct timeval *timeout);

#ifdef __cplusplus
};
#endif
#endif
