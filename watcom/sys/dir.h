#ifndef _DIR_H_INCLUDED
#define _DIR_H_INCLUDED

#include <dirent.h>
#include <limits.h>
#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

struct direct {
    unsigned long d_fileno;
    unsigned short d_reclen;
    unsigned short d_namlen;
    char d_name[NAME_MAX + 1];
};

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif
#ifdef __cplusplus
extern "C" {
#endif

extern int alphasort(struct direct **a, struct direct **b);
extern int scandir(char *dirname, struct direct *(*namelist[]),
        int (*select)(), int (*compar)());

#ifdef __cplusplus
};
#endif

#endif
