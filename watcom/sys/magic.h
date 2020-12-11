/*
 *  magic.h
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 *
 */
#ifndef __MAGIC_H_INCLUDED
#ifndef __PROC_MSG_H_INCLUDED
 #include <sys/proc_msg.h>
#endif

#ifndef __SENDMX_H_INCLUDED
 #include <sys/sendmx.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

/*-

 IMPORTANT-- The 'old' method of accessing magic is obsolete and
 may cause your program to be incompatable with a future release
 of QNX.

 Magic may only safely be accessed using the functions:
         __getmagicvar()
         __setmagicvar()
 Using the symbolic names enumerated below to access particular
 variables.

 These are the "magic" variables which my be accessed via
 __getmagicvar, __setmagicvar.

 In the comment proceeding each symbol name is a
         (type, access).
 type   ::  A pointer to this type must be provided in order to
            read or write the magic variable.

 access :: RO = ReadOnly
         | RW = ReadWrite.

 The absense of this specification or the string (obsolete) indicates
 the variable should not be relied upon.

 The definition of "struct _magic" and "__MAGIC" are only retained in
 this file to ease the conversion of 'old' programs, and may be removed
 or altered without notice.   They layout or location of this structure
 should not be assumed by any program.
 Portable programs will use the functions __getmagicvar() and
 __setmagicvar() only.

*/

#ifdef __386__

typedef enum {
        _m_my_pid,      /* (pid_t, RO)  process id */
        _m_dads_pid,    /* (pid_t, RO)  process id of father */
        _m_my_nid,      /* (nid_t, RO)  node id */
        _m_Errno,       /* (int,   RW)  Errno (obsolete) */
        _m_sptrtab,     /* Not Used -- reserved */
        _m_sigtab,      /* (void *, RW) signal action table */
        _m_cmd,         /* (void *, RW) spawn command */
        _m_cwd,         /* (char *, RO) current working directory */
        _m_root_prefix, /* (char *, RO) root prefix */
        _m_termst,      /* (void *, RW) term library info */
        _m_kernel_emt,  /* (void *, RO) kernel emulator trap */
        _m_qw,          /* (void *, RO) Q-Windows Shared Library (obsolete) */
        _m_efgfmt_far,  /* (void far *, RW) points to float format */
        _m_efgfmt_cs,   /* (int, RW) Breakdown of efgfmt */
        _m_efgfmt_off,  /* (void *, RW) Breakdown of efgfmt */
        _m_errno_ptr,   /* (void *, RW) Points to variable errno */
        _m_thread_data, /* (void *, RW) Pointer to Clib thread specific data */  
        _m_reserved_1,  /* Reserved for future, do not use */
        _m_reserved_2,
        _m_reserved_3,
        _m_reserved_4,
        _m_reserved_5,
        _m_reserved_6,
        _m_reserved_7,
        _m_reserved_8,
        _m_reserved_9
}  __magicid_t;


#define __MAGIC (*__getmagicptr())

/* #define __MAGIC (*(*(struct _magic * __far *)MK_FP(0x0078, 0000))) */

#else

typedef enum {
        _m_my_pid,      /* (pid_t, RO)  process id */
        _m_dads_pid,    /* (pid_t, RO)  process id of father */
        _m_my_nid,      /* (nid_t, RO)  node id */
        _m_Errno,       /* (int,   RW)  Errno (obsolete) */
        _m_malloc,      /* (void far *, RW) points to malloc() */
        _m_realloc,     /* (void far *, RW) points to realloc() */
        _m_free,        /* (void far *, RW) points to free() */
        _m_getenv,      /* (void far *, RW) points to getenv() */
        _m_calloc,      /* (void far *, RW) points to calloc() */
        _m_unknown0,    /* DO NOT USE */
#define _m_slib16ptr _m_unknown0
        _m_efgfmt,      /* (void far *, RW) points to efgfmt() */
        _m_cmd,         /* (void far *, RW) points to spawn cmd */
        _m_cwd,         /* (char far *, RO) current working directory */
        _m_root_prefix, /* (char far *, RO) root prefix */
        _m_termst,      /* (void far *, RW) term library info */
        _m_kernel_emt,  /* (void far *, RO) kernel emulator trap */
        _m_qw,          /* (void far *, RO) Q-Windows Shared Library */
        _m_32_0,        /* DO NOT USE */
        _m_32_1,        /* DO NOT USE */
        _m_reserved_0,  /* DO NOT USE */
        _m_reserved_1,  /* DO NOT USE */
        _m_reserved_2,  /* DO NOT USE */
        _m_reserved_3,  /* DO NOT USE */
        _m_reserved_4,  /* DO NOT USE */
        _m_reserved_5,  /* DO NOT USE */
        _m_reserved_6,  /* DO NOT USE */
        _m_reserved_7,  /* DO NOT USE */
        _m_reserved_8,  /* DO NOT USE */
        _m_reserved_9,  /* DO NOT USE */
        _m_dgroup       /* (int,  RO)      Data-Group of process */
}  __magicid_t;

#define __MAGIC (*(*(struct _magic far * far *)0x00780000))

#endif


#ifdef __386__
typedef struct { ushort_t __off; ushort_t __seg; } __farvoidptr;
#else
typedef void __far *__farvoidptr;
#endif


struct _magic16 {
    short int                Errno;
    mpid_t                   my_pid;
    mpid_t                   dads_pid;
    short int                waiting;       /* anybody waiting */
    nid_t                    my_nid;
    unsigned short           dgroup;
    short int                zero2[2];
    short int                my_tid;
    __farvoidptr             malloc,
                             realloc,
                             free,
                             getenv,
                             calloc,
                             sptrs[20];

#define _SPTRS_UNKNOWN          0
#define _SPTRS_SLIB16PTR        _SPTRS_UNKNOWN
#define _SPTRS_EFGFMT           1
#define _SPTRS_CMD              2
#define _SPTRS_CWD              3
#define _SPTRS_ROOT_PRFX        4
#define _SPTRS_TERM_STATE       5
#define _SPTRS_KER_NDP          6
#define _SPTRS_QWINDOWS         7
#define _SPTRS_32_0             8
#define _SPTRS_32_1             9
#define _SPTRS_RSVD_0       10
#define _SPTRS_RSVD_1       11
#define _SPTRS_RSVD_2       12
#define _SPTRS_RSVD_3       13
#define _SPTRS_RSVD_4       14
#define _SPTRS_RSVD_5       15
#define _SPTRS_RSVD_6       16
#define _SPTRS_RSVD_7       17
#define _SPTRS_RSVD_8       18
#define _SPTRS_RSVD_9       19
    struct _mxfer_entry      xmsg;
        long unsigned                    xmsg_pad;              /* So same size as _mxfer_entry32 */
    struct _proc_terminate   msg;
    char                     fpsave[1];     /* Variable length */
    } ;

struct _magic32 {
    mpid_t                   my_pid;
    short int                zero0;
    mpid_t                   dads_pid;
    short int                waiting;      /* anybody waiting? */
    nid_t                    my_nid;
    long int                 Errno;
    short int                my_tid;
    short int                zero2[1];
    void                    *zero4[5];          /* offset = 20(0x14) */
 /*-
  * The 16-bit version never declared these members, so programs and
  * lib routines went merily off using strange constants.
  * I changed the declaration to more intuitive names, however some programs
  * (esp sin) were too convoluted to go and ifdef __386__, so sptrs was brought
  * back, however it is only declared as length == 1, so that the other names
  * could remain, with sptrs[n, where n >= 1] would map as:
  *         sptrs[0]     == sptrs[0].
  *         sptrs[1]     == signal table.
  *         sptrs[2]     == cmd
  *         sptrs[3]     == cwd
  *         sptrs[4]     == root_prefix
  *         sptrs[5]     == term state
  *         sptrs[6]     == kernel_ndp_something
  *         sptrs[7]     == windows shared lib global data pointer
  *         sptrs[8]     == codeseg
  *         sptrs[9]     == data/stack seg
  *         sptrs[10]    == &errno.
  *         sptrs[10..20] == unknown_sptrs[0..11]
  */
    void                    *sptrs[1];  /* offset 40 (0x28) */
    void                    *sigtab;    /* signal table */
    void                    *cmd;               /* pointer to command */
    char                    *cwd;
    char                    *root_prefix;
    void                    *termst;
    void                    *kernel_emt;
    void                    *qw;
    int                     _cs;
    void                    *_efgfmt;
    int                     *errno_ptr;
    void                    *unknown_sptrs[9];
    /*
     * this area is used by the termination routines to shut the process
     * down.
     */
    struct _mxfer_entry      xmsg;
    struct _proc_terminate   msg;
    /*
     * this is either the emulator save area, or the 80x87 save area,
     * depending upon which you are running.
     */
    char                     fpsave[1];         /* Variable length */
    } ;

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#ifdef __386__
#define _magic _magic32
#else
#define _magic _magic16
#endif


extern struct _magic *__magicp(void);
extern struct _magic __far *__getmagicptr(void);
extern int __getmagicvar(void *__bufp, __magicid_t __magicid);
extern int __setmagicvar(void *__bufp, __magicid_t __magicid);

#ifdef __cplusplus
};
#endif
#define __MAGIC_H_INCLUDED
#endif
