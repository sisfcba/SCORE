/*
 *  sys/types.h Defined system types
 *
 *  Copyright by QNX Software Systems Limited 1990-1996. All rights reserved.
 */
#ifndef __TYPES_H_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _TIME_T_DEFINED_
 #define _TIME_T_DEFINED_
 typedef signed long time_t;     /* time value */
#endif

#ifndef _SIZE_T_DEFINED_
#define _SIZE_T_DEFINED_
 typedef unsigned size_t;
#endif

#ifndef _SSIZE_T_DEFINED_
  #define _SSIZE_T_DEFINED_
  typedef signed ssize_t;
#endif

#ifndef _LIMITS_H_INCLUDED
#include <limits.h>
#endif

/* Define POSIX 1003.1 types */

typedef long        dev_t;      /* Combination of node and device   */
#ifndef _GID_T_DEFINED_
 typedef int gid_t;             /* Used for group IDs           */
 typedef short mgid_t;          /* Used for group in messages */
 #define _GID_T_DEFINED_
#endif
typedef long        ino_t;      /* Used for file serial numbers     */
typedef short unsigned  mode_t; /* Used for some file attributes    */
typedef short unsigned  nlink_t;/* Used for link counts         */
typedef long        off_t;      /* Used for file sizes, offsets     */
typedef int   pid_t;            /* Used for process IDs & group IDs */
typedef short mpid_t;           /* Used for process & group IDs in messages */
#ifndef _UID_T_DEFINED_
 typedef int uid_t;             /* Used for user IDs            */
 typedef short muid_t;          /* used in messages */
 #define _UID_T_DEFINED_
#endif
#if defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS)
typedef short unsigned  msg_t;  /* Used for message passing     */
typedef long        nid_t;      /* Used for network IDs         */
#ifndef _TIMER_T_DEFINED_
 #define _TIMER_T_DEFINED_
typedef int         timer_t;    /* Used for timer IDs           */
#endif
#ifndef _CLOCKID_T_DEFINED_
 #define _CLOCKID_T_DEFINED_
typedef int         clockid_t;  /* Used for clock IDs           */
#endif
#endif

#define minor(device)                   ((int)((device) & 0x3ff))
#define major(device)                   ((int)(((device) >> 10) & 0x3f))
#define makedev(node,major,minor)       ((dev_t)(((node) << 16) | ((major) << 10) | (minor)))

#ifndef _WCHAR_T_DEFINED
#  define _WCHAR_T_DEFINED
#  ifndef _WCHAR_T_DEFINED_
#    define _WCHAR_T_DEFINED_
#    ifdef X_LOCALE
typedef unsigned long wchar_t;
#    else
#      ifdef __cplusplus
typedef long char wchar_t;
#      else
typedef unsigned short wchar_t;
#      endif
#    endif
#  endif
#else
#  ifndef _WCHAR_T_DEFINED_
#    define _WCHAR_T_DEFINED_
#  endif
#endif

#if defined __386__
typedef char *          caddr_t;
typedef int				int32_t;
typedef unsigned int	u_int32_t;
typedef unsigned int	uint32_t;
#else
typedef char __far *    caddr_t;
typedef long			int32_t;
typedef unsigned long	u_int32_t;
typedef unsigned long	uint32_t;
#endif
typedef char __far *    faddr_t;
typedef unsigned long   paddr_t;  
typedef long            daddr_t;
typedef char			int8_t;
typedef unsigned char	u_int8_t;
typedef unsigned char	uint8_t;
typedef unsigned char   uchar_t;
typedef short			int16_t; 
typedef unsigned short  u_int16_t;
typedef unsigned short  uint16_t;
typedef unsigned short  ushort_t;
typedef unsigned int    uint_t;
typedef unsigned long   ulong_t;
typedef unsigned char   u_char;
typedef unsigned short  u_short;
typedef unsigned int    u_int;
typedef unsigned long   u_long;
typedef struct _uquad   { u_long val[2]; } u_quad;
typedef struct _quad    {   long val[2]; } quad;
typedef quad *          qaddr_t;
typedef unsigned long   fixpt_t;
typedef int             key_t;
typedef unsigned short  sel_t;

#define __TYPES_H_INCLUDED
#ifdef __cplusplus
};
#endif
#endif
