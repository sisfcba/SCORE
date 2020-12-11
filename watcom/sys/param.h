#ifndef PARAM_H_INCLUDED
#define PARAM_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>
#include <limits.h>

#define HZ              CLK_TCK
#define MAXHOSTNAMELEN  64
#define MAXPATHLEN      PATH_MAX
#define MAXSYMLINKS     8
#define NBBY		8
#define	NCARGS		_POSIX_ARG_MAX	/* max bytes for an exec function */

#ifdef __cplusplus
} ;
#endif

#endif
