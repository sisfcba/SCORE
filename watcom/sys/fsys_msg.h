/*
 *  fsys_msg.h  Non-portable file system message definitions
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __FSYS_MSG_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#ifndef __STAT_H_INCLUDED
 #include <sys/stat.h>
#endif

#ifndef _LIMITS_H_INCLUDED
 #include <limits.h>
#endif

#ifndef __FSYSINFO_H_INCLUDED
 #include <sys/fsysinfo.h>
#endif

#ifndef __FSYS_H_INCLUDED
 #include <sys/fsys.h>
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

#define _FSYS_OLD_CHDIR         0x0201  /*  Deprecated message type         */
                                        /*  May not be supported later      */
                                        /*  _IO_CHDIR is preferred          */
                                        /*  See <sys/io_msg.h> for details  */
#define _FSYS_MKSPECIAL         0x0202  /*  mkdir() or mkfifo() or symlink()*/
#define _FSYS_REMOVE            0x0203  /*  unlink() or rmdir()             */
#define _FSYS_LINK              0x0204
#define _FSYS_MOUNT_RAMDISK     0x0205
#define _FSYS_UNMOUNT_RAMDISK   0x0206
#define _FSYS_BLOCK_READ        0x0207
#define _FSYS_BLOCK_WRITE       0x0208
#define _FSYS_DISK_GET_ENTRY    0x0209
#define _FSYS_SYNC              0x020A
#define _FSYS_MOUNT_PART        0x020B
#define _FSYS_MOUNT             0x020C
#define _FSYS_GET_MOUNT         0x020D
#define _FSYS_DISK_SPACE        0x020E
#define _FSYS_PIPE              0x020F
#define _FSYS_TRUNC             0x0210
#define _FSYS_OLD_MOUNT_DRIVER  0x0211  /*  Ignore fields after vers_offset */
#define _FSYS_XSTAT             0x0212
#define _FSYS_MOUNT_EXT_PART    0x0213
#define _FSYS_UMOUNT            0x0214
#define _FSYS_RESERVED          0x0215
#define _FSYS_READLINK          0x0216
#define _FSYS_MOUNT_DRIVER      0x0217
#define _FSYS_FSYNC             0x0218
#define _FSYS_INFO              0x0219
#define _FSYS_FDINFO            0x021A
#define _FSYS_MOUNT_DRIVER32    0x021B


#ifdef __cplusplus
extern "C" {
#endif
/*
 *  Message structures
 */

struct _fsys_gen_reply {
    msg_t   status;
    } ;


/*
 *  _FSYS_MKSPECIAL         0x0202  ( mkdir() or mkfifo() or symlink() )
 */
struct _fsys_mkspecial {
    msg_t       type;
    short int   fd,
                unit;
    char        version_cycle,     /*  eflag and zero2 invalid if           */
                                   /*  this field is 0.                     */
                                   /*  It is zeroed by 4.10 proc            */
                eflag;             /*  Extended flags (see <sys/io_msg.h>)  */
    nid_t       nid;
    mpid_t       pid;
    short int   sflag,
                oflag;
    mode_t      mode;
    long        zero2;
    char        path[1];
    } ;

struct _fsys_mkspecial_reply {
    msg_t       status;
    } ;


/*
 *  _FSYS_REMOVE            0x0203  ( unlink() or rmdir() )
 */
struct _fsys_remove {
    msg_t       type;
    short int   fd,
                unit;
    char        version_cycle,     /*  eflag and zero2 invalid if           */
                                   /*  this field is 0.                     */
                                   /*  It is zeroed by 4.10 proc            */
                eflag;             /*  Extended flags (see <sys/io_msg.h>)  */
    nid_t       nid;
    mpid_t       pid;
    short int   sflag,
                oflag;
    mode_t      mode;
    long        zero2;
    char        path[1];
    } ;

struct _fsys_remove_reply {
    msg_t       status;
    } ;


/*
 *  _FSYS_LINK              0x0204
 */
struct _fsys_link {
    msg_t       type;
    short int   fd,
                unit;
    char        version_cycle,     /*  eflag and zero2 invalid if           */
                                   /*  this field is 0.                     */
                                   /*  It is zeroed by 4.10 proc            */
                eflag;             /*  Extended flags (see <sys/io_msg.h>)  */
    nid_t       nid;
    mpid_t       pid;
    short int   sflag,
                oflag;
    mode_t      mode;
    long        zero2;
    char        path[1];
    } ;

struct _fsys_link_reply {
    msg_t       status;
    } ;


/*
 *  _FSYS_MOUNT_RAMDISK     0x0205
 */
struct _fsys_ramdisk {
    msg_t           type;
    short unsigned  nblocks;
    long            zero;
    } ;

struct _fsys_ramdisk_reply {
    msg_t       status;
    } ;


/*
 *  _FSYS_BLOCK_READ        0x0207
 */
struct _fsys_block_read {
    msg_t           type;
    short int       fd;
    long            block;
    short unsigned  num_blks,
                    zero;
    } ;

struct _fsys_block_read_reply {
    msg_t           status;
    short unsigned  blks_read;
    long            zero[2];        /*  So its the same size as the request */
    char            data[1];
    } ;


/*
 *  _FSYS_BLOCK_WRITE       0x0208
 */
struct _fsys_block_write {
    msg_t           type;
    short int       fd;
    long            block;
    short unsigned  num_blks,
                    zero;
    char            data[1];
    } ;

struct _fsys_block_write_reply {
    msg_t           status;
    short unsigned  blks_written;
    } ;


/*
 *  _FSYS_DISK_GET_ENTRY    0x0209
 */
struct _fsys_get_entry {
    msg_t           type;
    short int       fd;
    } ;

struct _fsys_get_entry_reply {
    msg_t           status;
    short unsigned  zero;
    char            data[1];
    } ;


/*
 *  _FSYS_SYNC              0x020A
 */
struct _fsys_sync {
    msg_t           type;
    };

struct _fsys_sync_reply {
    msg_t       status;
    } ;


/*
 *  _FSYS_MOUNT_PART        0x020B
 */
struct _fsys_mount_part {
    msg_t           type;
    short unsigned  special_unit;
    unsigned char   part_type,
                    extension_num;      /*  Always zero for this message    */
                                        /*  See also _FSYS_MOUNT_EXT_PART   */
    short unsigned  zero;
    long            num_sectors,        /*  Size of partition               */
                    blk_offset;         /*  Partition offset starting block */
    };

struct _fsys_mount_part_reply {
    msg_t           status;
    } ;


/*
 *  _FSYS_MOUNT             0x020C
 */
struct _fsys_mount {
    msg_t       type;
    short int   fd,
                unit;
    char        version_cycle,     /*  eflag and zero2 invalid if           */
                                   /*  this field is 0.                     */
                                   /*  It is zeroed by 4.10 proc            */
                eflag;             /*  Extended flags (see <sys/io_msg.h>)  */
    nid_t       nid;
    mpid_t       pid;
    short int   sflag,
                oflag;
    mode_t      mode;
    long        zero2;
    char        path[1];
    } ;

struct _fsys_mount_reply {
    msg_t       status;
    } ;


/*
 *  _FSYS_GET_MOUNT         0x020D
 */
struct _fsys_get_mount {
    msg_t       type;
    short int   fd,
                unit;
    char        version_cycle,     /*  eflag and zero2 invalid if           */
                                   /*  this field is 0.                     */
                                   /*  It is zeroed by 4.10 proc            */
                eflag;             /*  Extended flags (see <sys/io_msg.h>)  */
    nid_t       nid;
    mpid_t       pid;
    short int   sflag,
                oflag;
    mode_t      mode;
    long        zero2;
    char        path[1];
    } ;

struct _fsys_get_mount_reply {
    msg_t           status;
    short unsigned  zero;
    char            name[1];
    } ;


/*
 *  _FSYS_DISK_SPACE        0x020E
 */
struct _fsys_disk_space {
    msg_t       type;
    short int   fd;
    long        zero;
    } ;

struct _fsys_disk_space_reply {
    msg_t           status;
    short unsigned  zero;
    long            free_blocks,
                    total_blocks;
    } ;


/*
 *  _FSYS_PIPE              0x020F
 */
struct _fsys_pipe {
    msg_t       type;
    short int   unit,
                fd_in,
                fd_out;
    } ;

struct _fsys_pipe_reply {
    msg_t       status;
    } ;


/*
 *  _FSYS_TRUNC             0x0210
 */
struct _fsys_trunc {
    msg_t           type;
    short int       fd;
    off_t           offset;
    short int       whence;
    short unsigned  zero;
    } ;

struct _fsys_trunc_reply {
    msg_t           status;
    short unsigned  zero;
    off_t           offset;
    } ;


/*
 *  _FSYS_XSTAT             0x0212
 */
struct _fsys_xstat {
    msg_t           type;
    short int       fd;
    long            zero;
    } ;

struct _fsys_xstat_reply {
    msg_t               status;
    short unsigned      zero;
    struct _fsys_stat   xstat;
    } ;


/*
 *  _FSYS_MOUNT_EXT_PART    0x0213
 */
struct _fsys_mount_ext_part {
    msg_t           type;
    short unsigned  special_unit;
    unsigned char   part_type,
                    extension_num;      /*  Extension number for extended   */
                                        /*  DOS partitions.                 */
    short unsigned  zero;
    long            num_sectors,        /*  Size of partition               */
                    blk_offset;         /*  Partition offset starting block */
    };

struct _fsys_mount_ext_part_reply {
    msg_t           status;
    } ;


/*
 *  _FSYS_UMOUNT            0x0214
 */
struct _fsys_umount {
    msg_t       type;
    short int   fd,
                unit;
    char        version_cycle,     /*  eflag and zero2 invalid if           */
                                   /*  this field is 0.                     */
                                   /*  It is zeroed by 4.10 proc            */
                eflag;             /*  Extended flags (see <sys/io_msg.h>)  */
    nid_t       nid;
    mpid_t       pid;
    short int   sflag,
                oflag;
    mode_t      mode;
    long        zero2;
    char        path[1];
    } ;

struct _fsys_umount_reply {
    msg_t       status;
    } ;


/*
 *  _FSYS_READLINK          0x0216
 */
struct _fsys_readlink {
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

struct _fsys_readlink_reply {
    msg_t           status;
    short unsigned  zero;
    char            path[1];
    } ;


/*
 *  _FSYS_MOUNT_DRIVER      0x0217
 */
struct _fsys_driver {
    msg_t           type;
    short unsigned  num_devs,
                    jmp_tbl_off,        /*  Jump table offset (in "ds")     */
                    dev_tbl_off,        /*  Device table offset (in "ds")   */
                    ds,                 /*  DS for jmp_tbl and dev_tbl      */
                    cs,                 /*  CS for functions in jmp_tbl     */
                    sp,                 /*  SP for far calls into driver    */
                    max_seq_blocks,
                    max_parallel_ops,
                    version_off,    /*  Offset of version struct (in "ds")  */
                    drvr_flags,
                    zero1;
    long            zero2[2];
    } ;

struct _fsys_driver_reply {
    msg_t   status;
    } ;


/*
 *  _FSYS_FSYNC             0x0218
 */
struct _fsys_fsync {
    msg_t       type;
    short int   fd;
    char        datasync_flag,          /*  Non-zero if to sync data only   */
                zero[3];
    } ;

struct _fsys_fsync_reply {
    msg_t   status;
    } ;


/*
 *  _FSYS_INFO              0x0219
 */
struct _fsys_info {
    msg_t           type;
    short unsigned  reset;              /*  Reset counters if non-zero  */
    long            zero;
    } ;

struct _fsys_info_reply {
    msg_t               status;
    short unsigned      zero;
    struct _fsysinfo    data;
    };


/*
 *  _FSYS_FDINFO            0x021A
 */
struct _fsys_fdinfo {
    msg_t           type;
    mpid_t           pid;
    short unsigned  zero1;
    short int       fd;
    long            zero2;
    };

struct _fsys_fdinfo_reply {
    msg_t                   status;
    struct _fsys_info_entry info;
    };


/*
 *  _FSYS_MOUNT_DRIVER32    0x021B
 */
struct _fsys_driver32 {
    msg_t           type;
    long unsigned   num_devs,
                    jmp_tbl_off,        /*  Jump table offset (in "ds")     */
                    dev_tbl_off,        /*  Device table offset (in "ds")   */
                    ds,                 /*  DS for jmp_tbl and dev_tbl      */
                    cs,                 /*  CS for functions in jmp_tbl     */
                    sp,                 /*  SP for far calls into driver    */
                    max_seq_blocks,
                    max_parallel_ops,
                    version_off,    /*  Offset of version struct (in "ds")  */
                    drvr_flags,
                    zero1;
    long            zero2[2];
    } ;

struct _fsys_driver32_reply {
    msg_t   status;
    } ;
#ifdef __cplusplus
}
#endif
#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __FSYS_MSG_H_INCLUDED
#endif
