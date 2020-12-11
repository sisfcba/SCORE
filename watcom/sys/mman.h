/*
 *  mma.h Memory mapping
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __MMAP_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif


/* return value: */
#define MAP_FAILED ((void *)-1)

/* Sharing types:  Must choose either SHARED or PRIVATE     */
#define MAP_SHARED      1         /* share changes          */
#define MAP_PRIVATE     2         /* changes are private    */
#define MAP_ANON        3         /* allocate memory        */
#define MAP_TYPE        0xf       /* mask for share type    */
#define MAP_PROC        0x100     /* memop another process  */

/* Flags to mmap (or-ed in to MAP_SHARED or MAP_PRIVATE)    */
#define MAP_FIXED       0x10      /* user assigns address   */
/* Page protection flags which may be or-ed together        */
#define PROT_NONE       0x0
#define PROT_READ       0x1        /* pages can be read     */
#define PROT_WRITE      0x2        /* pages can be written  */
#define PROT_EXEC       0x4        /* pages can be executed */
#define PROT_NOCACHE    0x8        /* pages are not cached  */
#define PROT_MASK       0xf        /* mask for prot bits    */
#define PROT_MAPPED     0x10       /* used by system only   */

#define NOFD    (-1)

#define __PAGESIZE 0x1000

#if defined _QNX_SOURCE || !defined(NO_EXT_KEYS)
#define PAGESIZE __PAGESIZE
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern void *mmap(void *addr, size_t len, int prot, 
                  int flags, int fd, off_t off);
extern int munmap(void *addr, size_t len);
extern int mprotect(void *addr, size_t len, int prot);
extern int shm_open(const char *path, int oflag, mode_t mode);
extern int shm_unlink(const char *path);

enum { /* mlockall */
	MCL_CURRENT  = 1,		/* lock current mappings */
	MCL_FUTURE   = 2		/* lock future mappings */
};
extern int mlockall(int flags);
extern int munlockall(void);
extern int mlock(const void *addr, size_t len);
extern int munlock(const void *addr, size_t len);
enum { /*msync()*/
	MS_SYNC      = 0,
	MS_ASYNC     = 1,
	MS_INVALIDATE=2
};

extern int msync(const void *addr, size_t len, int flags);


#if defined _QNX_SOURCE || !defined(NO_EXT_KEYS)

enum { /* bits for vector returned by mincore/getpte */
	_PE_PRESENT    = 1<<0,   /* compat with SVR4 */
	_PE_WRITABLE   = 1<<1,
	_PE_SUPERVISOR = 1<<2,
	_PE_REFERENCED = 1<<5,
	_PE_MODIFIED   = 1<<6
};

extern int   mincore(void *addr, size_t len, unsigned char *v);
extern cdecl qnx_getpte(pid_t ppid, pid_t src, unsigned long addr, unsigned n,
                 unsigned long *v);
extern cdecl qnx_getpgflags(pid_t ppid, pid_t src, unsigned long addr, unsigned n,
                 unsigned char *v);
extern cdecl qnx_setpgflags(pid_t ppid, pid_t src, unsigned long addr, unsigned n,
                 unsigned mask, unsigned char *v);

enum { /* mcntl */
	MC_SYNC      = 1, /* sync with backing store */
	MC_LOCK      = 2, /* lock pages in memory */
	MC_UNLOCK    = 3, /* unlock pages from memory */
	MC_ADVISE    = 4, /* give advice to management */
	MC_LOCKAS    = 5, /* lock address space in memory */
	MC_UNLOCKAS  = 6  /* unlock address space from memory */
};
extern int   memcntl(caddr_t, size_t, int, caddr_t, int, int);
extern cdecl qnx_memcntl(pid_t ppid, pid_t pid, caddr_t, size_t, int,
                         caddr_t, int, int);

extern cdecl qnx_mmap(pid_t ppid, pid_t pid,
                      unsigned long addr, unsigned long size,
                      int prot, int flags, int fd, off_t off);
extern cdecl qnx_munmap(pid_t procpid, pid_t spid, void *addr, size_t len);
extern cdecl qnx_mprot(pid_t procpid, pid_t spid, void *addr, size_t len,
                       int prot);


#endif

#ifdef __cplusplus
};
#endif


#define __MMAP_H_INCLUDED
#endif
