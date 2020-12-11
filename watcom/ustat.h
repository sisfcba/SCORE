#ifndef _USTAT_H_INCLUDED
#define _USTAT_H_INCLUDED
#include <sys/types.h>
#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

struct ustat {
    daddr_t f_tfree;        /* total free blocks */
    ino_t   f_tinode;       /* number of free inodes */
    char    f_fname[6];     /* file system name */
    char    f_fpack[6];     /* file system pack name */
};

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif
#ifdef __cplusplus
extern "C" {
#endif

extern int ustat(dev_t dev, struct ustat *ub);

#ifdef __cplusplus
};
#endif
#endif
