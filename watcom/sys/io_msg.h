/*
 *  io_msg.h    Non-portable low-level IO definitions
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __IO_MSG_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#ifndef __STAT_H_INCLUDED
 #include <sys/stat.h>
#endif

#ifndef _LIMITS_H_INCLUDED
 #include <limits.h>
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

/*
 *  Size of path buffer needed for path resolution.
 *  The 386 buffer is big enough to deal with a deep working directory
 *  and still resolve a long relative pathname.
 *  The 16-bit version will get another buffer on the stack if needed.
 *  Both versions must resolve the path down to PATH_MAX or ENAMETOOLONG.
 */
#ifdef __386__
#define _QNX_PATH_MAX   PATH_MAX + 100
#else
#define _QNX_PATH_MAX   PATH_MAX
#endif

/*
 *  Message types
 */
#define _IO_OPEN        0x0101
#define _IO_CLOSE       0x0102
#define _IO_READ        0x0103
#define _IO_WRITE       0x0104
#define _IO_LSEEK       0x0105
#define _IO_RENAME      0x0106
#define _IO_GET_CONFIG  0x0107          /*  fpathconf()                 */
#define _IO_DUP         0x0108          /*  Also used for inheritence   */
#define _IO_HANDLE      0x0109
#define _IO_FSTAT       0x010A
#define _IO_CHMOD       0x010B
#define _IO_CHOWN       0x010C
#define _IO_UTIME       0x010D
#define _IO_FLAGS       0x010E          /*  fcntl() F_GETFL/F_SETFL     */
#define _IO_LOCK        0x010F
#define _IO_CHDIR       0x0110
#define _IO_READDIR     0x0112
#define _IO_REWINDDIR   0x0113
#define _IO_IOCTL       0x0114          /*  Discontinued; use _IO_QIOCTL */
#define _IO_STAT        0x0115          /*  Atomic stat & lstat message  */
#define _IO_SELECT      0x0116          /*  Not supported in 4.0X & 4.10 */
#define _IO_QIOCTL      0x0117

/*
 *  Open modes (oflag) for _IO_HANDLE message.
 */
#define _IO_HNDL_INFO   1       /*  STAT, PATHCONF (not much else)  */
#define _IO_HNDL_RDDIR  2       /*  OPENDIR                         */
#define _IO_HNDL_CHANGE 3       /*  CHMOD/CHOWN (to  owner)         */
#define _IO_HNDL_UTIME  4       /*  UTIME (Any writer)              */
#define _IO_HNDL_LOAD   5       /*  Loader thread opening executable */
#define _IO_HNDL_CLOAD  6       /*  Loader thread caching executable */

/*
 *  Extended flags (eflag)
 */
#define _IO_EFLAG_DIR   0x01    /*  Path referenced a directory     */
#define _IO_EFLAG_DOT   0x02    /*  Last component was . or ..      */

/*
 * Definitions for 'flag' field in _select_set
 * Note that the top 4 bits are reserved for server "internal" use
 */
#define _SEL_INPUT        0x0001
#define _SEL_OUTPUT       0x0002
#define _SEL_EXCEPT       0x0004
#define _SEL_POLLED       0x0008
#define _SEL_IS_INPUT     0x0010
#define _SEL_IS_OUTPUT    0x0020
#define _SEL_IS_EXCEPT    0x0040
#define _SEL_ARMED        0x0080

/*
 * Definitions for 'mode' field in _select
 */
#define _SEL_ARM          0x0001
#define _SEL_POLL         0x0002

/*
 *  Message structures
 */

/*
 *  Also used the following message types:
 *      _IO_HANDLE          Uses struct _io_open_reply for reply
 *      _IO_RENAME          Uses struct _io_open_reply for reply
 *      _IO_CHDIR           Uses struct _io_open_reply for reply
 *      _IO_STAT            Uses struct _io_fstat_reply for reply
 *                          Returns lstat() info if mode == S_IFLNK
 *
 *  May be used by some manager specific messages (esp. see <sys/fsys_msg.h>)
 *
 *  dir_flag is set to 1 if the original path explicitly named a directory
 *  by having a trailing / or /. or /..
 *  Those trailing names are stripped off before the message is sent.
 *  However the distintion is sometimes important, esp. notable in:
 *      lstat("/symlink/.");
 *  vs.
 *      lstat("/symlink");
 */
struct _io_open {
    msg_t       type;
    short int   fd,
                unit;
    char        version_cycle,         /*  eflag and zero2 invalid if   */
                                       /*  this field is 0.             */
                                       /*  It is zeroed by 4.10 proc    */
                eflag;                 /*  Extended flags (see above)   */
    nid_t       nid;
    mpid_t       pid;
    short int   sflag,
                oflag;
    mode_t      mode;
    long        zero2;
    char        path[1];
    } ;

struct _io_open_reply {
    msg_t   status;
    } ;


struct _io_close {
    msg_t       type;
    short int   fd;
    long        zero;
    } ;

struct _io_close_reply {
    msg_t   status;
    } ;


struct _io_read {
    msg_t           type;
    short int       fd,
                    nbytes;
    short unsigned  zero;
    } ;

struct _io_read_reply {
    msg_t       status;
    short int   nbytes;
    long        zero;
    char        data[1];
    } ;


struct _io_write {
    msg_t           type;
    short int       fd,
                    nbytes;
    short unsigned  zero;
    char            data[1];
    } ;

struct _io_write_reply {
    msg_t       status;
    short int   nbytes;
    long        zero;
    } ;


struct _io_lseek {
    msg_t           type;
    short int       fd;
    off_t           offset;
    short int       whence;
    short unsigned  zero;
    } ;

struct _io_lseek_reply {
    msg_t           status;
    short unsigned  zero;
    off_t           offset;
    } ;


struct _io_config {
    msg_t           type;
    short int       fd,
                    name;
    short unsigned  zero;
    } ;

struct _io_config_reply {
    msg_t       status;
    short int   zero;
    long        value;
    } ;


struct _io_dup {
    msg_t           type;
    short int       src_fd;
    mpid_t           src_pid;
    short unsigned  zero1;
    short int       dst_fd;
    short unsigned  zero2;
    } ;

struct _io_dup_reply {
    msg_t   status;
    } ;


struct _io_fstat {
    msg_t       type;
    short int   fd;
    long        zero;
    } ;

struct _io_fstat_reply {
    msg_t           status;
    short unsigned  zero;
    struct stat     stat;
    } ;


struct _io_chmod {
    msg_t       type;
    short int   fd;
    mode_t      mode;
    } ;

struct _io_chmod_reply {
    msg_t   status;
    } ;


struct _io_chown {
    msg_t       type;
    short int   fd;
    mgid_t       gid;
    muid_t       uid;
    } ;

struct _io_chown_reply {
    msg_t   status;
    } ;


struct _io_utime {
    msg_t       type;
    short int   fd;
    time_t      actime,
                modtime;
    short int   cur_flag;   /*  If set, ignore times and set to "now"   */
    short int   zero;       /*  32-bit apps send this, old 16-bit apps don't */
    } ;

struct _io_utime_reply {
    msg_t   status;
    } ;


struct _io_flags {
    msg_t       type;
    short int   fd,
                mask,
                bits;
    } ;

struct _io_flags_reply {
    msg_t   status,
            flags;
    } ;


/*
 *  Replies with the same structure.
 */
struct _io_lock {
    msg_t       type;
    short int   fd,
                cmd,
                l_type,
                l_whence;
    off_t       l_start,
                l_len;
    mpid_t       l_pid;
    short int   zero;
    } ;


struct _io_readdir {
    msg_t       type;
    short int   fd;
    char        ndirs,
                zero[3];
    } ;

struct _io_readdir_reply {
    msg_t   status;
    char    ndirs,
            zero[5],    /*  So its the same size as the request */
            data[1];
    } ;


struct _io_rewinddir {
    msg_t       type;
    short int   fd;
    } ;

struct _io_rewinddir_reply {
    msg_t   status;
    } ;


struct _io_ioctl {
    msg_t       type;
    short int   fd,
                request,
                nbytes;
    long        zero;
    char        data[1];
    } ;

struct _io_ioctl_reply {
    msg_t           status;
    short unsigned  ret_val;
    long            zero;
    char            data[1];
    } ;

struct _io_qioctl {
    msg_t       type;
    short int   fd,
                request,
                nbytes;
    long        zero;
    char        data[1];
    } ;

struct _io_qioctl_reply {
    msg_t           status;
    short unsigned  ret_val;
    long            zero[2];
    char            data[1];
    } ;


struct _select_set {
    short unsigned  flag;
    short int       fd;
    } ;

struct _io_select {
    msg_t           type;
    short unsigned  mode;
    mpid_t           proxy;
    short unsigned  proxy_spare;
    mpid_t           pid;       /* unused */
    short unsigned  pid_spare; /* unused */
    short unsigned  zero[2];
    short int       nfds;
#ifdef __cplusplus
    struct _select_set set[1];  /* variable length */
#else
    struct _select_set set[];  /* variable length */
#endif
    } ;

struct _io_select_reply {
    msg_t           status;
    short unsigned  zero[7];   /* keep send & reply aligned */
    short int       nfds;
#ifdef __cplusplus
    struct _select_set set[1];  /* variable length */
#else
    struct _select_set set[];  /* variable length */
#endif
    } ;

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __IO_MSG_H_INCLUDED
#endif
