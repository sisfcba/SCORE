/*
 *  fsys.h      Non-portable file system definitions
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __FSYS_H_INCLUDED

#ifndef _LIMITS_H_INCLUDED
 #include <limits.h>
#endif

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

/*
 *  Manifests
 */
#define _BLOCK_SIZE         512
#define _BOOT_BLOCK         1L
#define _ROOT_BLOCK         2L
#define _BITMAP_BLOCK       3L
#define _MAX_XTNTS_PER_XBLK 60
#define _MOUNT_PATH_MAX     63          /*  Excludes trailing null  */
#define _LONG_NAME_MAX      48
#ifndef _SHORT_NAME_MAX
 #define _SHORT_NAME_MAX    16
#endif


/*
 *  File status (d_status) bits.
 */
#ifndef _FILE_USED
#define _FILE_USED      0x01
#endif
#define _FILE_MODIFIED  0x02
#define _FILE_BUSY      0x04        /*  Indicates file grown or truncated   */
                                    /*  but dir_inode not updated on disk   */
#define _FILE_LINK      0x08        /*  If a link, no other flags are valid */
                                    /*  Look in the inode for real status   */
#define _FILE_INODE     0x10        /*  Target of entry flag'd _FILE_LINK   */
#define _FSYS_CLEAN     0x20        /*  No busy files.  Valid only on root. */
                                    /*  Only supported from 4.22 on         */

/*
 *  File system structures
 */

#ifndef _XTNT_T_DEFINED_
#define _XTNT_T_DEFINED_

typedef short unsigned  _nxtnt_t;
typedef unsigned char   _ftype_t;

typedef struct _xtnt_entry {
    long    xtnt_blk,                   /*  First block in extent           */
            xtnt_size;                  /*  Num blocks in extent            */
    } _xtnt_t;

#endif


struct _dir_entry {
    union {
        struct _inode_info {
            char            di_fname[_SHORT_NAME_MAX];
            off_t           di_size;
            _xtnt_t         di_first_xtnt;
            long            di_xblk;
            time_t          di_ftime,       /*  Time created                */
                            di_mtime,       /*  Time data last modified     */
                            di_atime,       /*  Time last accessed          */
                            di_ctime;       /*  Time of last status change  */
            _nxtnt_t        di_num_xtnts;
            mode_t          di_mode;        /*  see <stat.h>                */
            muid_t          di_uid;
            mgid_t          di_gid;
            nlink_t         di_nlink;
            char            di_zero[4];     /*  Reserved.  Must be zero     */
            _ftype_t        di_type;
            } inode;

        struct _link_info {
            char            dl_fname[NAME_MAX];
            long            dl_inode_blk;
            unsigned char   dl_inode_ndx,
                            dl_spare[10];   /*  To be same as _inode_info   */
            } link;
        } d_union;

    unsigned char   d_status;
    } ;


struct _inode_entry {
    char            i_reserved[_SHORT_NAME_MAX];
    off_t           i_size;
    _xtnt_t         i_first_xtnt;
    long            i_xblk;
    time_t          i_ftime,            /*  Time created                    */
                    i_mtime,            /*  Time of last data modification  */
                    i_atime,            /*  Time last accessed              */
                    i_ctime;            /*  Time of last status change      */
    _nxtnt_t        i_num_xtnts;
    mode_t          i_mode;             /*  see <sys/stat.h>                */
    muid_t          i_uid;
    mgid_t          i_gid;
    nlink_t         i_nlink;
    long            i_zero;             /*  Must be zero                    */
    _ftype_t        i_type;
    unsigned char   i_status;
    } ;


struct _xblk {
    long            xblk_next_xblk,
                    xblk_prev_xblk;
    unsigned char   xblk_num_xtnts;
    char            xblk_spare[3];
    long            xblk_num_blocks;    /*  Total blocks used by    */
                                        /*  all extents in xblk     */
    _xtnt_t         xblk_xtnts[_MAX_XTNTS_PER_XBLK];
    char            xblk_signature[8];
    _xtnt_t         xblk_first_xtnt;    /*  Only valid for first xblk   */
    } ;


struct _fsys_info_entry {
    mpid_t           pid;
    short unsigned  zero1;
    short int       fd;
    long            zero2;
    off_t           offset,             /*  Current seek position       */
                    fsize;              /*  Size of file                */
    short unsigned  fflags,             /*  Bitmask version of oflags   */
                    share;              /*  Share mode, see <share.h>   */
    char            path[PATH_MAX + 1];
    };

#ifdef __cplusplus
extern "C" {
#endif
extern int fsys_get_mount_dev( const char *__path, char *__device );
extern int fsys_get_mount_pt( const char *__path, char *__directory );
extern int fsys_fdinfo( pid_t __server, pid_t __pid, int __fd,
                                            struct _fsys_info_entry *__info);
#ifdef __cplusplus
};
#endif

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __FSYS_H_INCLUDED
#endif
