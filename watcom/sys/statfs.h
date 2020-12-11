#ifndef _STATFS_H_INCLUDED
#define _STATFS_H_INCLUDED
#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif
struct statfs {
    short   f_fstype;   /* file system type */
    short   f_bsize;    /* block size */
    short   f_frsize;   /* fragment size */
    long    f_blocks;   /* total number of blocks */
    long    f_bfree;    /* count of free blocks */
#   define f_inodes f_files
    long    f_files;    /* total number of file nodes */
#   define f_ffree  f_ifree
    long    f_ffree;    /* count of free nodes */
    char    f_fname[6]; /* volume name */
    char    f_fpack[6]; /* pack name */
};
#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#ifdef __cplusplus
extern "C" {
#endif
extern int fstatfs(int fd, struct statfs *fs, int fl, int flag);
extern int statfs(char *path, struct statfs *fs, int fl, int flag);
#ifdef __cplusplus
};
#endif

#endif
