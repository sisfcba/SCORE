/*
 *  fnmatch.h
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */

#ifndef _FNMATCH_H_INCLUDED
#define _FNMATCH_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif
extern int fnmatch(const char *expr, const char *str, int flags);
#ifdef __cplusplus
};
#endif

#define FNM_PATHNAME 001
#define FNM_PERIOD   002
#define FNM_QUOTE    004

#define FNM_NOMATCH  1

#endif
