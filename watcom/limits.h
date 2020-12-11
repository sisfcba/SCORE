/*
 *  limits.h    Machine and OS limits
 *
 *  Copyright by WATCOM International Corp. 1988-1996.  All rights reserved.
 *  Copyright by QNX Software Systems Limited 1990-1996. All rights reserved.
 */
#ifndef _LIMITS_H_INCLUDED

/*
 *  ANSI required limits
 */
#define CHAR_BIT    8           /*  number of bits in a byte        */
#ifdef __CHAR_SIGNED__
 #define CHAR_MIN   (-128)      /*  minimum value of a char         */
 #define CHAR_MAX   127         /*  maximum value of a char         */
#else
 #define CHAR_MIN   0           /*  minimum value of a char         */
 #define CHAR_MAX   255         /*  maximum value of a char         */
#endif
#define MB_LEN_MAX  3           /*  maximum length of multibyte char    */
#define SCHAR_MIN   (-128)      /*  minimum value of a signed char      */
#define SCHAR_MAX   127         /*  maximum value of a signed char      */
#define UCHAR_MAX   255U        /*  maximum value of an unsigned char   */

#define SHRT_MIN    (-32767-1)  /*  minimum value of a short int        */
#define SHRT_MAX    32767       /*  maximum value of a short int        */
#define USHRT_MAX   65535U      /*  maximum value of an unsigned short  */
#define LONG_MAX    2147483647L     /*  maximum value of a long int     */
#define LONG_MIN    (-2147483647L-1) /* minimum value of a long int     */
#define ULONG_MAX   4294967295UL     /* maximum value of a unsigned long    */
#ifdef __386__
 #define INT_MIN    (-2147483647-1) /*  minimum value of an int         */
 #define INT_MAX    2147483647      /*  maximum value of an int         */
 #define UINT_MAX   4294967295U     /*  maximum value of an unsigned int*/
#else
 #define INT_MIN    (-32767-1)      /*  minimum value of an int         */
 #define INT_MAX    32767           /*  maximum value of an int         */
 #define UINT_MAX   65535U          /*  maximum value of an unsigned int    */
#endif


#if defined(_POSIX_SOURCE) || defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS)
/*
 *  POSIX required limits.
 *  These are minimums values, not absolute limits,
 *  and the real value may be greater.
 */
#define _POSIX_ARG_MAX      4096    /*  Length of args for exec             */
                                    /*  functions including environment data*/
#define _POSIX_CHILD_MAX    6       /*  Number of simultaneous              */
                                    /*  processes per real user ID.         */
#define _POSIX_LINK_MAX     8       /*  Max. links per file                 */
#define _POSIX_MAX_CANON    255     /*  No. bytes in terminal               */
                                    /*  cannonical input queue.             */
#define _POSIX_MAX_INPUT    255     /*  Size of terminal input queue buffer */
#define _POSIX_NAME_MAX     14      /*  Max bytes in a filename             */
#define _POSIX_NGROUPS_MAX  0       /*  Num. simultaneous supplementary     */
                                    /*  group IDs per process               */
#define _POSIX_OPEN_MAX     16      /*  Min num. files open per process.    */
#define _POSIX_PATH_MAX     255     /*  Num. bytes in pathname (excl. NULL) */
#define _POSIX_PIPE_BUF     512     /*  Num. bytes written atomically to a  */
                                    /*  pipe.                               */
#define _POSIX_SSIZE_MAX    32767   /*  The value that can be stored in an  */
                                    /*  object of type ssize_t.             */
#define _POSIX_STREAM_MAX   8       /*  The number of streams that one      */
                                    /*  process can have open at one time.  */
#define _POSIX_SYMLOOP_MAX  8       /*  The number of loops to traverse     */
                                    /*  while resolving symbolic links      */
                                    /*  or prefix aliases.                  */
#define _POSIX_TZNAME_MAX   3       /*  The maximum number of bytes         */
                                    /*  supported for the name of a time    */
                                    /*  zone (not of the TZ variable).      */

/*
 *  Run-time increasable values
 *
 */
#define NGROUPS_MAX 1                   /*  Num. simultaneous supplementary */
                                        /*  group IDs per process           */

/*
 *  Run-time invariant values (possible indeterminate)
 *
 *  CHILD_MAX and OPEN_MAX are indeterminate.
 */
#define ARG_MAX     61440
#undef  CHILD_MAX           /* no child max             */
#undef  OPEN_MAX            /* no open max              */
#undef  STREAM_MAX          /* no stream max            */
#define TZNAME_MAX  30      /* QNX implementation maximum   */

/*
 *  Pathname variable values (may vary by pathname)
 */
#define LINK_MAX    65535u
#define MAX_CANON   _POSIX_MAX_CANON
#define MAX_INPUT   _POSIX_MAX_INPUT
#define NAME_MAX    48
#define PATH_MAX    _POSIX_PATH_MAX
#define PIPE_BUF    5120

/*
 *  Invariant values
 */
#define SSIZE_MAX   _POSIX_SSIZE_MAX
#define SYMLOOP_MAX 32      /* This is bigger than _POSIX_SYMLOOP_MAX */

/*
 *  Posix .2/9 limits.
 */
#define BC_BASE_MAX 99
#define BC_DIM_MAX  2048
#define BC_SCALE_MAX    99
#define COLL_ELEM_MAX   4
#define EXPR_NEST_MAX   32
#define LINE_MAX    2048
#define PASTE_FILES_MAX 12
#define RE_DUP_MAX  255
#define SED_PATTERN_MAX 20480
#define SENDTO_MAX  90000L
#define SORT_LINE_MAX   20480
#endif  /* _POSIX_SOURCE || _QNX_SOURCE || !NO_EXT_KEYS */

#if defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS)

#define _QNX_ROOT_PREFIX_MAX  128
#define _QNX_PROXY_SIZE_MAX   100
#define _QNX_MXTAB_LEN        255
#define _QNX_MSGLEN           65500U
#define _QNX_ATTACHEDNAME_MAX 64
#define _QNX_PREFIX_MAX       48
#define _QNX_ERRNOSTR_MAX     64
#endif

#define _LIMITS_H_INCLUDED
#endif
