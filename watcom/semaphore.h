/*
 *  semaphore.h
 *
 *  Copyright by QNX Software Systems Limited 1994. All rights reserved.
 */
#ifndef __SEMAPHORE_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1);

typedef struct {
        volatile long value;
        long          semid;
        } sem_t;

#pragma pack();



#ifdef __386__

extern int sem_init(sem_t *sem, int pshared, unsigned value);
extern int sem_destroy(sem_t *sem);
extern int sem_post(sem_t *sem);
extern int sem_wait(sem_t *sem);
extern int sem_trywait(sem_t *sem);

extern int __sem_post(sem_t *sem);
extern int __sem_wait(sem_t *sem);
extern int __sem_trywait(sem_t *sem);

extern int __kererr(int);

#pragma aux __sem_post = \
        "mov ebx,0" \
        "clc"       \
        "int 0f1h" \
        "jnc    l1" \
        "call __kererr" \
        "l1:" \
        __parm [eax] \
        __modify __exact [eax ebx edx] \
        __value [eax];

#pragma aux __sem_wait = \
        "mov ebx,1" \
        "clc" \
        "int 0f1h" \
        "jnc    l1" \
        "call __kererr" \
        "l1:" \
        __parm [eax] \
        __modify __exact [eax ebx edx] \
        __value [eax];

#pragma aux __sem_trywait = \
        "mov ebx,2" \
        "clc" \
        "int 0f1h" \
        "jnc    l1" \
        "call __kererr" \
        "l1:" \
        __parm [eax] \
        __modify __exact [eax ebx edx] \
        __value [eax];

#else

extern int sem_init(sem_t far *sem, int pshared, unsigned value);
extern int sem_destroy(sem_t far *sem);
extern int sem_post(sem_t far *sem);
extern int sem_wait(sem_t far *sem);
extern int sem_trywait(sem_t far *sem);

extern int __sem_post(sem_t far *sem);
extern int __sem_wait(sem_t far *sem);
extern int __sem_trywait(sem_t far *sem);

#pragma aux __sem_post = \
        ".386" \
        "mov ebx,0" \
        "and eax,0ffffh" \
        "push ds" \
        "mov ds,dx" \
        "int 0f1h" \
        "pop ds" \
        "and eax,0ffffh" \
        __parm [dx ax] \
        __modify __exact [ax bx dx] \
        __value [ax];

#pragma aux __sem_wait = \
        ".386" \
        "mov ebx,1" \
        "and eax,0ffffh" \
        "push ds" \
        "mov ds,dx" \
        "int 0f1h" \
        "pop ds" \
        "and eax,0ffffh" \
        __parm [dx ax] \
        __modify __exact [ax bx dx] \
        __value [ax];

#pragma aux __sem_trywait = \
        ".386" \
        "mov ebx,2" \
        "and eax,0ffffh" \
        "push ds" \
        "mov ds,dx" \
        "int 0f1h" \
        "pop ds" \
        "and eax,0ffffh" \
        __parm [dx ax] \
        __modify __exact [ax bx dx] \
        __value [ax];

#endif

#ifdef __INLINE_FUNCTIONS__
#define sem_post __sem_post
#define sem_wait __sem_wait
#define sem_trywait __sem_trywait
#endif

#ifdef __cplusplus
};
#endif


#define __SEMAPHORE_H_INCLUDED
#endif
