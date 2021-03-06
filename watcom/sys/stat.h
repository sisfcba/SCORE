/*
 *  stat.h      File stat structure and definitions
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __STAT_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

#ifndef _XTNT_T_DEFINED_
typedef short unsigned  _nxtnt_t;
typedef unsigned char   _ftype_t;

typedef struct _xtnt_entry {
    long    xtnt_blk,
            xtnt_size;
} _xtnt_t;
#define _XTNT_T_DEFINED_
#endif

struct stat {
    ino_t           st_ino;         /*  File serial number.                 */
    dev_t           st_dev;         /*  ID of device containing file.       */
    off_t           st_size;
    dev_t           st_rdev;        /*  Device ID, for inode that is device */
#if defined __386__
/*-

The POSIX test suite demanded the type of these fields, however due to
16-bit heritage binaries require these to be shorts, and common use of
functions like "getuid()" are best suited as ints.
The 32bit stat(), fstat() function(s) copy st_ouid, st_ogid into
st_uid, st_gid appropriately.

A 32bit io-manager (which generates these structures) should assign
to the fields st_ouid and st_ogid to operatre properly.

To keep source compatible, in 16bit these st_ouid is defined to
st_uid and st_ogid is defined to st_gid.

*/
    uid_t           st_uid;
    gid_t           st_gid;
#else
    long            st_spare1[2];   /* DO NOT USE */
#endif
    time_t          st_ftime,       /*  Time created                        */
                    st_mtime,       /*  Time of last data modification      */
                    st_atime,       /*  Time last accessed                  */
                    st_ctime;       /*  Time of last status change          */
    short unsigned  st_spare2;
    mode_t          st_mode;        /*  see below                           */
#if defined __386__
    muid_t          st_ouid;
    mgid_t          st_ogid;
#else
    muid_t          st_uid;
    mgid_t          st_gid;
#define st_ouid st_uid
#define st_ogid st_gid
#endif
    nlink_t         st_nlink;
    long            st_spare3;
    _ftype_t        st_spare0;
    unsigned char   st_status;
};

/*
 *  Extended stat structure.
 *  Contains a lot of QNX specific data.
 *  (Mainly filesystem data corresponding to data on disk.)
 */
struct _fsys_stat {
    ino_t           st_ino;         /*  File serial number.                 */
    dev_t           st_dev;         /*  ID of device containing file.       */
    off_t           st_size;
    dev_t           st_rdev;        /*  Device ID, for inode that is device */
    _xtnt_t         st_first_xtnt;
    time_t          st_ftime,       /*  Time created                        */
                    st_mtime,       /*  Time of last data modification      */
                    st_atime,       /*  Time last accessed                  */
                    st_ctime;       /*  Time of last status change          */
    _nxtnt_t        st_num_xtnts;
    mode_t          st_mode;        /*  see below                           */
    mgid_t           st_uid;
    muid_t           st_gid;
    nlink_t         st_nlink;
    long            st_spare1;      /*  Must be zero                        */
    _ftype_t        st_spare0;
    unsigned char   st_status;
    long            st_xblk,
                    st_spare2[5];
};

#define _S_IFMT     0xF000              /*  Type of file                    */
#define _S_IFIFO    0x1000              /*  FIFO                            */
#define _S_IFCHR    0x2000              /*  Character special               */
#define _S_IFDIR    0x4000              /*  Directory                       */
#define _S_IFNAM    0x5000              /*  Special named file              */
#define _S_IFBLK    0x6000              /*  Block special                   */
#define _S_IFREG    0x8000              /*  Regular                         */
#define _S_IFLNK    0xA000              /*  Symbolic link                   */
#define _S_IFSOCK   0xC000              /*  Socket                          */

#define S_ISFIFO(m) (((m)&_S_IFMT)==_S_IFIFO) /* Test for FIFO.             */
#define S_ISCHR(m)  (((m)&_S_IFMT)==_S_IFCHR) /* Test for char special file.*/
#define S_ISDIR(m)  (((m)&_S_IFMT)==_S_IFDIR) /* Test for directory file.   */
#define S_ISBLK(m)  (((m)&_S_IFMT)==_S_IFBLK) /* Test for block specl file. */
#define S_ISREG(m)  (((m)&_S_IFMT)==_S_IFREG) /* Test for regular file.     */

#if defined(_POSIX_SOURCE) || !defined(NO_EXT_KEYS)

#define S_ISLNK(m)  (((m)&_S_IFMT)==_S_IFLNK) /* Test for symbolic link.    */
#define S_ISNAM(m)  (((m)&_S_IFMT)==_S_IFNAM) /* Test for special named file*/
#define S_ISSOCK(m) (((m)&_S_IFMT)==_S_IFSOCK)/* Test for socket.           */

/*
 *  For special named files (IFNAM), the subtype is encoded in st_rdev.
 *  They subtypes are:
 */
#define _S_RSVD_1       00001           /*  Reserved for semaphore subtype  */
#define _S_RSVD_2       00002           /*  Reserved for shared mem subtype */
#define _S_QNX_SPECIAL  040000          /*  QNX special type                */
                                        /*  Use dev_info() for more detail  */
#define _S_QNX_MQUEUE   020000

/*
 *  Common filetype macros
 */
#define S_IFMT      _S_IFMT             /*  Type of file                    */
#define S_IFIFO     _S_IFIFO            /*  FIFO                            */
#define S_IFCHR     _S_IFCHR            /*  Character special               */
#define S_IFDIR     _S_IFDIR            /*  Directory                       */
#define S_IFNAM     _S_IFNAM            /*  Special named file              */
#define S_IFBLK     _S_IFBLK            /*  Block special                   */
#define S_IFREG     _S_IFREG            /*  Regular                         */
#define S_IFLNK     _S_IFLNK            /*  Symbolic link                   */
#define S_IFSOCK    _S_IFSOCK           /*  Socket                          */

#define S_IPERMS    000777              /*  Permission mask                 */
#endif

#define S_ISUID     004000              /* set user id on execution         */
#define S_ISGID     002000              /* set group id on execution        */
#define S_ISVTX     001000              /* sticky bit (does nothing yet)    */
#define S_ENFMT     002000              /* enforcement mode locking         */

/*
 *  Owner permissions
 */
#define S_IRWXU     000700              /*  Read, write, execute/search     */
#define S_IRUSR     000400              /*  Read permission                 */
#define S_IWUSR     000200              /*  Write permission                */
#define S_IXUSR     000100              /*  Execute/search permission       */
#define S_IREAD     S_IRUSR             /*  Read permission                 */
#define S_IWRITE    S_IWUSR             /*  Write permission                */
#define S_IEXEC     S_IXUSR             /*  Execute/search permission       */

/*
 *  Group permissions
 */
#define S_IRWXG     000070              /*  Read, write, execute/search     */
#define S_IRGRP     000040              /*  Read permission                 */
#define S_IWGRP     000020              /*  Write permission                */
#define S_IXGRP     000010              /*  Execute/search permission       */

/*
 *  Other permissions
 */
#define S_IRWXO     000007              /*  Read, write, execute/search     */
#define S_IROTH     000004              /*  Read permission                 */
#define S_IWOTH     000002              /*  Write permission                */
#define S_IXOTH     000001              /*  Execute/search permission       */

/*
 *  POSIX 1003.1 Prototypes.
 */
#ifdef __cplusplus
extern "C" {
#endif
extern int     chmod( const char *__path, mode_t __mode );
extern int     stat( const char * __path, struct stat * __buf );
extern int     lstat( const char * __path, struct stat * __buf );
extern int     fsys_stat( const char * __path, struct _fsys_stat * __buf );
extern int     fchmod( int __fildes, mode_t __mode );
extern int     fstat( int __fildes, struct stat * __buf );
extern int     fsys_fstat( int __fildes, struct _fsys_stat * __buf );
extern int     mkdir( const char *__path, mode_t __mode );
extern int     mkfifo( const char *__path, mode_t __mode );
extern int     mknod( const char *__path, mode_t __mode, int __dev );
extern mode_t  umask( mode_t __cmask );
extern mode_t  qnx_umask( pid_t __pid, mode_t __cmask );

/*-
 * Useful inside the shared library only:
 */
#ifdef __386__
extern int __fixstat(struct stat *);
#else
#define __fixstat(x)
#endif

#ifdef __cplusplus
};
#endif

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __STAT_H_INCLUDED
#endif
