/*
 *  mqueue.h: POSIX 1003.4/D12 message queues and access functions
 *
 *  Copyright (C) by Quantum Software Systems 1992.  All rights reserved.
 */

#if !defined _MQUEUE_H_INCLUDED
#define _MQUEUE_H_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#if !defined __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#if !defined _SIGNAL_H_INCLUDED
#include <signal.h>
#endif

#if !defined _FCNTL_H_INCLUDED
#include <fcntl.h>
#endif

struct mq_attr {
	long	mq_maxmsg;   /* maximum number of messages stored */
	long	mq_msgsize;  /* maximum message length */
	long	mq_flags;    /* OR of following */

#define MQ_NONBLOCK          0x0001
// The following flags are QNX implementation-specific
#define MQ_MULT_NOTIFY       0x0002
#define MQ_PRIO_RESTRICT     0x0004
#define MQ_PRIO_BOOST        0x0008
#define MQ_READBUF_DYNAMIC   0x0010
#define MQ_NOTIFY_ALWAYS     0x0020

	long	mq_curmsgs;  /* current number of messages stored */
	long	mq_sendwait; /* number of processes waiting to send */
	long	mq_recvwait; /* number of processes waiting to receive */

};

#define MQ_PRIO_MAX          32

typedef short int mqd_t;

extern mqd_t mq_open(const char *name, int oflag, ...);
extern int   mq_close(mqd_t mqdes);
extern int   mq_send(mqd_t mqdes, void *msg_ptr, size_t msg_len, 
                      uint_t msg_prio);
extern int   mq_receive(mqd_t mqdes, void *msg_ptr, size_t msg_len,
                      uint_t *msg_prio);
extern int   mq_notify(mqd_t qdes, const struct sigevent * notification);
extern int   mq_getattr(mqd_t qdes, struct mq_attr *mqstat);
extern int   mq_setattr(mqd_t mqdes, const struct mq_attr *mqstat,
                      struct mq_attr *omqstat);
extern int   mq_unlink( const char *name );

#ifdef __cplusplus
};
#endif
#endif
