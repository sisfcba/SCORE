/*
 *  proc.h      Process data structures and definitions
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __PROC_MSG_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#ifndef __FD_H_INCLUDED
 #include <sys/fd.h>
#endif

#ifndef __SEGINFO_H_INCLUDED
 #include <sys/seginfo.h>
#endif

#ifndef __UTSNAME_H_INCLUDED
 #include <sys/utsname.h>
#endif

#ifndef __PSINFO_H_INCLUDED
 #include <sys/psinfo.h>
#endif

#ifndef __DEBUG_H_INCLUDED
 #include <sys/debug.h>
#endif

#if 0
#ifndef __HWINFO_H_INCLUDED
#include <sys/hardware.h>
#endif
#endif
#ifndef __SYS_MSG_H_INCLUDED
 #include <sys/sys_msg.h>
#endif

#ifndef __SIDINFO_H_INCLUDED
 #include <sys/sidinfo.h>
#endif

#ifndef __OSSTAT_H_INCLUDED
 #include <sys/osstat.h>
#endif

#ifndef __TRACE_MSG_H_INCLUDED
 #include <sys/trace.h>
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif


/*
 *  type definitions.
 */

#define _PROC_SLIB          1           /*  Shared lib registering          */
#define _PROC_EMUL87        2           /*  80x87 emulator                  */
#define _PROC_SPAWN         3           /*  Spawn a new proc directly       */
#define _PROC_EXEC          4           /*  Transform into a new proc       */
#define _PROC_FORK          5           /*  Split into two procs            */
#define _PROC_THREAD        6           /*  Start a thread proc             */
#define _PROC_SETPGID       7           /*  Start a new proc group          */
#define _PROC_SIGNAL        8           /*  Set/get signal handler          */
#define _PROC_SEGMENT       9           /*  Various segment functions       */
#define _PROC_NAME          10          /*  Attach/detach a name            */
#define _PROC_TIMER         11          /*  Attach/detach a timer           */
#define _PROC_GETSETID      12          /*  Set/Get uid/gid                 */
#define _PROC_DEBUG         13          /*  Get/set memory of a proc        */
#define _PROC_TIME          14          /*  Get/Set the system time         */
#define _PROC_PFLAGS        15          /*  Set a procs flags               */
#define _PROC_SFLAGS        16          /*  Set system flags                */
#define _PROC_STATS         17          /*  Get system statistics           */
#define _PROC_PROXY         18          /*  Attach/detach messenger pid     */
#define _PROC_PRIORITY      19          /*  Change priority and algorithm   */
#define _PROC_HINT          20          /*  Catch an interrupt              */
#define _PROC_LOADED        21          /*  End of a disk load              */
#define _PROC_FD            22          /*  File descriptor functions       */
#define _PROC_OSINFO        23          /*  Get a structure of OS info      */
#define _PROC_TERMINATE     24          /*  A proc has requested terminat'n */
#define _PROC_OPEN          25          /*  A IO open request --> map path  */
#define _PROC_PREFIX        26          /*  A prefix mapping for _PROC_OPEN */
#define _PROC_WAIT          27          /*  Wait for a sons death           */
#define _PROC_UMASK         28          /*  Get/Set umask                   */
#define _PROC_REM_PROXY     29          /*  Attach/detach remote mpid       */
#define _PROC_NET_REG       30          /*  A net process wishes to registr */
#define _PROC_VC_ATTACH     31          /*  A process wants to create a vc  */
#define _PROC_VC_DETACH     32          /*  A process wants to destroy a vc */
#define _PROC_NET_ONLY      33          /*  Only net process can send these */
#define _PROC_PSINFO        34          /*  Get a structure of proc info    */
#define _PROC_DISPLAY       35          /*  Display a message on console    */
#define _PROC_POLL          36          /*  Poll/poll_ack/poll_nack/parms   */
#define _PROC_TTY           37          /*  Major device num allocation     */
#define _PROC_NET_REG41     38          /*  Net 4.10 register msg           */
#define _PROC_SHUTDOWN      39          /*  System shutdown                 */
#define _PROC_SESSION       40          /*  Set session id                  */
#define _PROC_FREEMEM       41          /*  Free memory in system           */
#define _PROC_TRACE         42          /*  Trace system                    */
#define _PROC_MMAP          43          /*  POSIX 1003.4 mmap               */
#define _PROC_SEM           44          /*  Semaphores                      */
#define _PROC_HARDWARE      45          /*  Hardware resources              */
#define _PROC_KERINFO       46          /*  Get Info ptr                    */
#define _PROC_LOG_CONTROL   47          /*  control event logging           */
#define _PROC_COUNTERS      48          /*  access internal counters        */
#define _PROC_FUNC          49          /*  internal lockout                */
#define _PROC_SSTACK        50          /*  set my signal stack             */
#define _PROC_DESCR         51          /*  sysi86 DESCRIPTOR calls         */
#define _PROC_CHECK         52          /*  check data structures           */

#ifndef __386__
#define _PROC_LAST           _PROC_HARDWARE
#else
#define _PROC_LAST          _PROC_CHECK
#endif

/*
 *  subtype definitions.
 */

#define _PROC_SUB_ATTACH        0
#define _PROC_SUB_DETACH        1
#define _PROC_SUB_QUERY         2
#define _PROC_SUB_LOCATE        3
#define _PROC_SUB_ACTION1       4
#define _PROC_SUB_ACTION2       5
#define _PROC_SUB_ACTION3       6
#define _PROC_SUB_CHS_GETNIDS   7
#define _PROC_SUB_NOTIFY        8
#define _PROC_SUB_ACTION4       9
#define _PROC_SUB_ALARM         10
#define _PROC_SUB_ACTION5       11

#define _PROC_SUB_VC_AT_RREQ    1       /*  for _PROC_NET_ONLY msgs (above) */
#define _PROC_SUB_VC_AT_RES     2
#define _PROC_SUB_NET_DREG      3
#define _PROC_SUB_VC_GET_PTR    4       /* new 05 jan 95, vidbuf interlock */

#define _PROC_SUB_NRGPR       0x01      /* new 30 jan 95, polling/lost reply */

#define _PROC_SUB_POLL_PARM     0
#define _PROC_SUB_POLL          1
#define _PROC_SUB_POLL_ACK      2
#define _PROC_SUB_POLL_NACK     3

#define _PROC_SUB_GETID         0
#define _PROC_SUB_SETUID        1
#define _PROC_SUB_SETGID        2
#define _PROC_SUB_SETEUID       3
#define _PROC_SUB_SETEGID       4
#define _PROC_SUB_SETREUID      5
#define _PROC_SUB_SETREGID      6

#define _PNAME_LEN              32
#define _PNAME_NIDS             10

#define _PROC_SUB_MEMCHECK      0

/*
 *  Message structure definitions.
 */

#pragma pack(1);
#ifdef __cplusplus
extern "C" {
#endif

struct _proc_death {
    struct _sysmsg_hdr     hdr;
    struct _sysmsg_death   data;
    } ;

struct _proc_trace {
    short unsigned  type,
                    subtype,
                    flags;
    long            nbytes;
    mpid_t          proxy;
    short unsigned  zero[2];
    } ;

struct _proc_trace_reply1 {
    short unsigned  status,
                    overruns;
    char            data[1];   /* May be up to 1K */
    } ;

struct _proc_trace_reply2 {
    short unsigned      status;
    struct _trace_info  data;
    } ;

struct _proc_tracepnt {
    struct _sysmsg_hdr     hdr;
    struct _sysmsg_trace   data;
    } ;

struct _proc_tracepnt_reply {
    struct _sysmsg_hdr_reply     hdr;
    struct _sysmsg_trace_reply   data;
    } ;

struct _proc_version {
    struct _sysmsg_hdr       hdr;
    struct _sysmsg_version   data;
    } ;

struct _proc_version_reply {
    struct _sysmsg_hdr_reply       hdr;
    struct _sysmsg_version_reply   data;
    } ;

struct _proc_slib {
    short unsigned  type,
                    subtype;
    long            offset;
    short unsigned  segment;
    struct _sysmsg_version_reply   data;
    struct {
       long offset;
       short unsigned segment;
       } vec[3];
   long             zero[2];
   } ;

struct _proc_slib_reply {
    short unsigned  status;
    } ;

struct _proc_terminate {                /*  There is no reply for this one  */
    short unsigned  type;
    short int       signum;
    long int        xstatus;
    } ;

struct _proc_emul87 {                   /*  There is no reply for this one  */
    short unsigned  type,
                    fpu;
    long            offset;
    short unsigned  segment,
                    nbytes;
    } ;

struct _proc_emul87_reply {
    short unsigned  status;
    } ;

struct _proc_spawn {                    /*  Same structure as _PROC_EXEC    */
    short unsigned  type;
    char            priority,
                    algorithm;
    short unsigned  zero1;
    short unsigned  flags;
    char            zero2,
                    ctfd;
    char            stdfds[10];
    short unsigned  argc,
                    envc;
    char            data[1];            /*  Can be up to 60K in usr program */
    } ;

struct _proc_fork {
    short unsigned  type,
                    flags;
    } ;

struct _proc_thread {
    short unsigned  type,
                    flags;
    long            eip,
                    esp,
                    arg,
                    cs,
                    zero1;
    } ;

struct _proc_loaded {
    short unsigned  type;
    } ;

struct _proc_loaded_reply {             /*  Common reply: spawn/fork/thread */
    short unsigned  status;
    mpid_t          son_pid;
    short unsigned  zero1;
    } ;

struct _proc_setpgid {
    short unsigned  type;
    mpid_t          pid,
                    pgid;
    } ;

struct _proc_setpgid_reply {
    short unsigned  status;
    } ;

struct _proc_getsetid {
    short unsigned  type,
                    subtype;
    mpid_t          pid;
    short           zero1,
                    eid,
                    rid;
    } ;

struct _proc_getsetid_reply {
    short unsigned  status,
                    zero1;
    struct _psinfo2 data;
    } ;

struct _proc_signal {
    short unsigned  type,
                    subtype,
                    signum;
    mpid_t          pid;
    short unsigned  zero1;
    long            mask,
                    bits;
    long            offset;
    short unsigned  segment;
    } ;

struct _proc_signal_reply {
    short unsigned  status,
                    zero1;
    long            old_bits,
                    new_bits;
    } ;


struct _proc_segment {
    short unsigned  type,
                    subtype;
    short           sel;
    mpid_t          srcpid;
    short unsigned  zero1;
    mpid_t          dstpid;
    short unsigned  zero2,
                    flags,
                    zero3;
    long            addr,
                    nbytes;
    } ;

struct _proc_segment_reply {
    short unsigned  status;
    struct _seginfo data;
    } ;

struct _proc_name {
    short unsigned  type,
                    subtype,
                    cookie,
                    flags;  /* added 24-jul-90 RDB */
    long            zero1;
    char            name[_PNAME_LEN+1];
    } ;

struct _proc_name_reply1 {
    short unsigned  status,
                    zero1,
                    cookie;
    mpid_t          pid;
    nid_t           nid;
    char            name[_PNAME_LEN+1];
    } ;

struct _proc_name_reply2 {
    short unsigned  status,
                    zero1,
                    cookie,
                    num_nids;
    nid_t           nids[_PNAME_NIDS];
    } ;

struct _proc_prefix {
    short unsigned  type,
                    subtype,
                    unit;
    short           replace;
    long            zero1;
    char            name[1];    /* May be up to PATH_MAX + 1 */
    } ;

struct _proc_prefix_reply1 {
    short unsigned  status;
    } ;

struct _proc_prefix_reply2 {
    short unsigned  status;
    char            data[1];
    } ;

struct _proc_timer {
    short unsigned  type,
                    subtype,
                    flags,
                    cookie;
    char            timer_type,
                    notify_type;
    long            sec1,
                    nsec1,
                    sec2,
                    nsec2,
                    data,
                    zero1;
    } ;

struct _proc_timer_reply {
    short unsigned  status;
    mpid_t          pid;
    short unsigned  flags,
                    cookie;
    char            timer_type,
                    notify_type;
    long            sec1,
                    nsec1,
                    sec2,
                    nsec2,
                    data,
                    zero1;
    } ;

struct _proc_timeradj {
    short unsigned  type,
                    subtype;
    long            rate,
                    usec;
    };

struct _proc_timeradj_reply {
    short unsigned  status,
                    zero1;
    long            count,
                    nsec;
    };

struct _proc_time {
    short unsigned  type,
                    zero1;
    long            seconds,
                    nsec;
    } ;

struct _proc_time_reply {
    short unsigned  status,
                    zero1;
    long            seconds,
                    nsec;
    } ;

struct _proc_flags {
    short unsigned  type,
                    zero1;
    long            mask,
                    bits;
    } ;

struct _proc_flags_reply {
    short unsigned  status,
                    zero1;
    long            old_bits,
                    new_bits;
    } ;

struct _proc_wait {
    short unsigned  type,
                    options;
    mpid_t          pid;
    short unsigned  zero1;
    long            xstatus;
    } ;

struct _proc_wait_reply {
    short unsigned  status,
                    zero1;
    mpid_t          pid;
    short unsigned  zero2;
    long            xstatus;
    } ;

struct _proc_proxy {
    short unsigned  type,
                    subtype;
    mpid_t          pid;
    short unsigned  zero1,
                    nbytes;
    char            priority,
                    zero2,
                    data[100];
    } ;

struct _proc_proxy_reply {
    short unsigned  status;
    mpid_t          pid;
    short unsigned  zero1;
    } ;

struct _proc_rem_proxy {
    short unsigned  type,
                    subtype;
    nid_t           nid;
    mpid_t          pid;
    short unsigned  zero1;
    short unsigned  zero2;
    short unsigned  zero3;
    } ;

struct _proc_rem_proxy_reply {
    short unsigned  status;
    mpid_t          pid;
    short unsigned  zero1;
    } ;

struct _proc_priority {
    short unsigned  type;
    mpid_t          pid;
    short unsigned  zero1;
    char            priority,
                    algorithm;
    short unsigned  zero2;
    } ;

struct _proc_priority_reply {
    short unsigned  status,
                    zero1;
    short unsigned  zero2;
    char            priority,
                    algorithm;
    short unsigned  zero3;
    } ;

struct _proc_debug {
    struct _debug_hdr   hdr;
    union _debug_data   data;
    } ;

struct _proc_debug_reply {
    struct _debug_hdr_reply hdr;
    union _debug_data       data;
    } ;

struct _proc_hint {
    short unsigned  type,
                    subtype,
                    flags,
                    cookie;
    short           intnum;
    short unsigned  ds;
    long            offset;
    short unsigned  cs;
    } ;

struct _proc_hint_reply {
    short unsigned  status;
    mpid_t          pid;
    short unsigned  zero1,
                    cookie,
                    intnum,
                    ds;
    long            offset;
    short unsigned  cs;
    } ;

struct _proc_psinfo {
    short unsigned  type;
    mpid_t          pid;
    short unsigned  zero1,
                    memindex;
    } ;

struct _proc_psinfo_reply {
    short unsigned  status;
    struct _psinfo  data1;
    struct _seginfo data2[16];
    } ;

#define _PINFO_PID_UNION        0
#define _PINFO_GET_PSINFO3      1
#define _PINFO_GET_FDPTR        2
#define _PINFO_MAXFUN           2
struct _proc_kerinfo {
    short unsigned  type, subtype;
    unsigned long   zero[7];
};

struct _proc_kerinfo_reply {
    short unsigned  status;            /* success/fail */
    short unsigned  maxfunc;           /* maximum funcno supported */
    unsigned long   info_offs;         /* address of info function */
    unsigned short  info_seg, zero;    /* segment of info function */
    unsigned long   zero1[5];
};


struct _proc_kerinfo_reply2 {
    short unsigned  status;
    short unsigned  zero;
    short unsigned  segment;
    short unsigned  pid_offset;     /* relative to active */
    short unsigned  regp_offset;    /* relative to active */
    short unsigned  ip_offset;      /* relative to regp */
    unsigned long   active_address;
    unsigned long   zero1[5];
};

#define _PCOUNT_GETALL     0
#define _PCOUNT_CLRALL     1

struct _proc_counters {
	unsigned short   type, subtype;
	unsigned long    zero[7];
};

struct _proc_counter_reply1 {
	unsigned short   status, result;
	unsigned long    intr[16];
	unsigned long    faults[32];
	unsigned long    kcalls[32];
};


struct _proc_func {
	unsigned short     type, subtype;
	unsigned long      func;
	unsigned long      fargs[4];
	unsigned long      zero[2];
};

struct _proc_func_reply {
	unsigned short     status, zero;
	unsigned long      result;
};


struct _proc_osinfo {
    short unsigned  type;
    } ;

struct _proc_osinfo_reply {
    short unsigned  status;
    struct _osinfo  data;
    } ;

struct _proc_osstat {
    short unsigned  type;
    } ;

struct _proc_osstat_reply {
    short unsigned  status;
    struct _osstat  data;
    } ;

struct _proc_fd {
    short unsigned  type,
                    subtype,
                    fd;
    mpid_t          owner_pid;
    short unsigned  zero1;
    nid_t           nid;
    mpid_t          pid;
    short unsigned  zero3;
    mpid_t          vid;
    short unsigned  zero4,
                    flags,
                    handle,
                    zero5;
    } ;

struct _proc_fd_reply1 {
    short unsigned  status,
                    fd,
                    zero1,
                    zero2;
    } ;

struct _proc_fd_reply2 {
    short unsigned  status,
                    regoff,
                    active,
                    fd1sel,
                    fd2sel,
                    num_clusters,       /* 5 oct 92 - now offsetof vproc for Net */
                    pid_mask,
                    cluster_bits;
    long            pid_off;
    short unsigned  pid_seg,
                    pid_size;
    } ;

struct _proc_fd_reply3 {
    short unsigned      status,
                        empty;
    struct _fd_entry    data[16];
    } ;

struct _proc_fd_reply4 {
    short unsigned      status;
    struct _fd_entry    data;
    short unsigned      fd;
    } ;


struct _proc_umask {
    short unsigned  type,
                    subtype,
                    umask,
                    pid,
                    zero1;
    } ;

struct _proc_umask_reply {
    short unsigned  status,
                    zero1,
                    umask,
                    zero2;
    } ;


struct _proc_display {
    short unsigned  type,
                    subtype;
    long            value;
    char            text[81];
    } ;

struct _proc_display_reply {
    short unsigned  status;
     } ;


struct _proc_tty {
    short unsigned  type,
                    subtype,
                    major,
                    zero1[7];
    } ;

struct _proc_tty_reply {
    short unsigned  status,
                    zero1,
                    major,
                    zero2[7];
    } ;


struct _net2proc_reg41 {
        short unsigned           type,          subtype;
        short unsigned           msgr_pid,      zero1;
        short unsigned           free_q,        zero2;
        short unsigned           work_q,        zero3;
        short unsigned           qpkt_seg,      zero4;
        short unsigned           zero5,         zero6;
        short unsigned           zero7,         zero8;
};
struct _net2proc_reg41_reply {
        short unsigned           status,        zero1;
};

struct _net2proc_dreg41 {
        short unsigned           type,          subtype;
        short unsigned           zero1,         zero2;
};
struct _net2proc_dreg41_reply {
        short unsigned           status,        zero1;
};


struct _proc_shutdown {
    short unsigned  type,
                    signum,
                    zero[2];
    } ;

struct _proc_shutdown_reply {
    short unsigned  status;
    } ;


struct _proc_freemem {
    short unsigned  type,
                    zero[3];
    } ;

struct _proc_freemem_reply {
    short unsigned  status,
                    npieces;
        long            nbytes[128];
    } ;

struct _proc_check {
    unsigned short  type, subtype;
    unsigned long   zero[4];
};
struct _proc_check_reply {
    unsigned short  status, count;
    unsigned long   data[16];
};

struct _proc_session {
    short unsigned  type,
                    subtype,
                    sid,
                    zero[3];
    char            name[17];
    } ;

struct _proc_session_reply {
    short unsigned  status,
                    zero;
    struct _sidinfo data;
    } ;

#define _PROC_SUB_MMAP      _PROC_SUB_ATTACH
#define _PROC_SUB_MUNMAP    _PROC_SUB_DETACH
#define _PROC_SUB_MINCORE   _PROC_SUB_QUERY
#define _PROC_SUB_GETPTE    _PROC_SUB_LOCATE
#define _PROC_SUB_MPROT     _PROC_SUB_ACTION1
#define _PROC_SUB_SETPTE    _PROC_SUB_ACTION2

struct _proc_mmap {
    short unsigned  type,
                    subtype;
    short int       fd,
                    prot,
                    flags,
                    zero1;
    long            off,
                    addr,
                    len;
    } ;

struct _proc_mmap_ext {
#if defined __cplusplus || defined NO_EXT_KEYS
     struct _proc_mmap _proc_mmap;
#else
     union { struct _proc_mmap; struct _proc_mmap _proc_mmap; };
#endif
     union {
         unsigned char  pbits[1];
         unsigned long  pent[1];
    } pte;
};


struct _proc_mmap_reply {
    short unsigned  status,
                    zero;
    short int       fd,
                    prot,
                    flags,
                    zero1;
    long            off,
                    addr,
                    len;
    } ;

struct _proc_pte_reply {
    unsigned short status,zero;
    unsigned short nents;
    unsigned short zero1;
    unsigned long  addr;
    union {
         unsigned char  pbits[1];
         unsigned long  pent[1];
    } pte;
};

struct _proc_sem {
    short unsigned  type,
                    subtype,
                    semid,
                    seg;
    long unsigned   addr,
                    zero2[2];
    } ;

struct _proc_sem_reply {
    short unsigned  status,
                    zero1,
                    semid,
                    seg;
    long unsigned   addr,
                    zero2[2];
    } ;

#ifdef __HWINFO_H_INCLUDED
struct _proc_hardware {
    unsigned short  type,
                    subtype;
    struct _hardwareinfo data;
    } ;

struct _proc_hardware_reply {
    unsigned short  status;
    struct _hardwareinfo data;
    } ;
#endif


struct _proc_log_control {
    msg_t         type, subtype;
    ulong_t       sw_mask;
    ulong_t       sw_set;
    ulong_t       irq_mask;
    ulong_t       irq_set;
};

#define _PROC_LOG_KERNEL_CALLS 01
#define _PROC_LOG_IRQ(n)  (1<<(n)+1)

struct _proc_log_control_reply {
   msg_t          status, zero;
};

struct _proc_signal_stack {
	unsigned short     type, subtype;
	unsigned long      ss_base;
	unsigned long      ss_size;
	unsigned long      ss_flags;
	unsigned short     ss_seg;
};

struct _proc_setdesc {
	unsigned short     type, subtype;
	unsigned long      sd_sel;
	unsigned long      sd_base;
	unsigned long      sd_lim;
	unsigned long      sd_acc1;
	unsigned long      sd_acc2;
};


#ifdef __cplusplus
}
#endif
#pragma pack();


/*
 *  Segment operations      _PROC_SEGMENT --> msg.sub_type
 */

#define _SEGMENT_ALLOC      1
#define _SEGMENT_OVERLAY    2
#define _SEGMENT_REALLOC    3
#define _SEGMENT_FREE       4
#define _SEGMENT_FLAGS      7
#define _SEGMENT_HUGE       8
#define _SEGMENT_GLOBAL     9
#define _SEGMENT_INFO       10
#define _SEGMENT_ARM        11
#define _SEGMENT_GET        12
#define _SEGMENT_PUT        13
#define _SEGMENT_INDEX      14
#define _SEGMENT_RAW_ALLOC  15
#define _SEGMENT_RAW_FREE   16
#define _SEGMENT_PRIV       17


/*
 *  Signal operations       _SIGACTION, ... SIGSEND --> msg.sub_type
 */

#define _SIGTABLE           0
#define _SIGACTION          1   /* Discontinued */
#define _SIGMASK            2
#define _SIGRAISE           3
#define _SIGPENDING         4
#define _SIGACT             5
#define _SIGSUSPEND         6

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __PROC_MSG_H_INCLUDED
#endif

