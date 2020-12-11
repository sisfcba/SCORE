#ifndef _FTW_H_INCLUDED
#define _FTW_H_INCLUDED

#include <sys/stat.h>

#ifdef __cplusplus
extern "C" {
#endif
extern int ftw(char *path,
    int (*fn)(const char *fname, struct stat *sbuf, int flags),
    int depth);
#ifdef __cplusplus
};
#endif

enum {
    FTW_F,              /* file type */
    FTW_D,              /* directory type */
    FTW_DNR,                /* directory type, no read perm */
    FTW_NS              /* cannot stat */
};
#endif
