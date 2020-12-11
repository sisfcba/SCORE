/*
 *  stdlib.h    Standard Library functions
 *
 *  Copyright by WATCOM International Corp. 1988-1996.  All rights reserved.
 *  Copyright by QNX Software Systems Limited 1990-1996. All rights reserved.
 */
#ifndef _STDLIB_H_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif
#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif


#ifndef _SIZE_T_DEFINED_
#define _SIZE_T_DEFINED_
 typedef unsigned size_t;
#endif

#ifndef _WCHAR_T_DEFINED
#define _WCHAR_T_DEFINED
#ifndef _WCHAR_T_DEFINED_
#define _WCHAR_T_DEFINED_
#ifdef __cplusplus
typedef long char wchar_t;
#else
typedef unsigned short wchar_t;
#endif
#else
#ifndef _WCHAR_T_DEFINED_
#define _WCHAR_T_DEFINED_
#endif
#endif
#endif
#ifndef NULL
 #if defined(__SMALL__) || defined(__MEDIUM__) || defined(__386__)
  #define NULL   0
 #else
  #define NULL   0L
 #endif
#endif


#define RAND_MAX        32767u
#define EXIT_SUCCESS    0
#define EXIT_FAILURE    1
#ifndef MB_CUR_MAX
    #define MB_CUR_MAX  3
#endif

typedef struct  {
        int     quot;
        int     rem;
} div_t;

typedef struct  {
        long    quot;
        long    rem;
} ldiv_t;

extern void      abort( void );
extern int       abs( int __j );
extern int       atexit( register void ( *__func )( void ) );
extern double    atof( const char *__nptr );
extern int       atoi( const char *__nptr );
extern long int  atol( const char *__nptr );
extern void     *bsearch( const void *__key, const void *__base,
                    size_t __nmemb, size_t __size,
                    int ( *__compar )( const void *__pkey, const void *__pbase ) );
extern void      break_on( void );
extern void      break_off( void );
extern void     *calloc( size_t __n, size_t __size );
extern div_t     div( int __numer, int __denom );
extern void      exit( int __status );
extern void      free( void *__ptr );
extern char     *getenv( const char *__name );
extern long int  labs( long int __j );
extern ldiv_t    ldiv( long int __numer, long int __denom );
extern void     *malloc( size_t __size );
extern int       mblen( const char *__s, size_t __n );
extern size_t    mbstowcs( wchar_t *__pwcs, const char *__s, size_t __n );
extern int       mbtowc( wchar_t *__pwc, const char *__s, size_t __n );
extern size_t    wcstombs( char *__s, const wchar_t *__pwcs, size_t __n );
extern int       wctomb( char *__s, wchar_t __wchar );
extern void      qsort( void *__base, size_t __nmemb, size_t __size,
                    int (*__compar)( const void *, const void * ) );
extern int       rand( void );
extern void     *realloc( void *__ptr, size_t __size );
extern void      srand( unsigned int __seed );
extern double    strtod( const char *__nptr, char **__endptr );
extern long int  strtol( const char *__nptr, char **__endptr, int __base );
extern unsigned long     strtoul( const char *__nptr, char **__endptr, int __base );
extern int       system( const char *__string );

#ifdef  __INLINE_FUNCTIONS__
 #pragma intrinsic(abs,div,labs)
 #ifdef __386__
  #pragma intrinsic(ldiv)
 #endif
#endif

#ifndef __cplusplus
#define atof(p)  strtod(p,(char **)NULL)
#endif

#if defined(_POSIX_SOURCE) || defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS)
void             _exit( int __status );
#endif

#if defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS) /*extensions enabled*/

extern unsigned  atoh( const char *__nptr );
extern char     *ecvt( double __val, int __ndig, int *__dec, int *__sign );
extern char     *_ecvt( double __val, int __ndig, int *__dec, int *__sign );
extern char     *fcvt( double __val, int __ndig, int *__dec, int *__sign );
extern char     *_fcvt( double __val, int __ndig, int *__dec, int *__sign );
extern char     *_fullpath( char *__buf, const char *__path, size_t __size );
extern char     *gcvt( double __val, int __ndig, char *__buf );
extern char     *_gcvt( double __val, int __ndig, char *__buf );
extern char     *itoa( int __value, char *__buf, int __radix );
extern char     *_itoa( int __value, char *__buf, int __radix );
extern unsigned long _lrotl( unsigned long __value, unsigned int __shift );
extern unsigned long _lrotr( unsigned long __value, unsigned int __shift );
extern char     *ltoa( long int __value, char *__buf, int __radix );
extern char     *_ltoa( long int __value, char *__buf, int __radix );
extern void      _makepath( char *__path, const char *__drive,
                    const char *__dir, const char *__fname,
                    const char *__ext );
extern unsigned int _rotl( unsigned int __value, unsigned int __shift );
extern unsigned int _rotr( unsigned int __value, unsigned int __shift );
extern int       putenv( const char *__string );
extern void      _searchenv( const char *__name, const char *__env_var,
                    char *__buf );
extern int       need_usage( char **argv );
extern int       print_usage( char **argv );
extern void      searchenv( const char *__name, const char *__env_var,
                    char *__buf );
extern void      _splitpath2( const char *__inp, char *__outp,
                    char **__drive, char **__dir, char **__fn, char **__ext );
extern void      _splitpath( const char *__path, char *__drive,
                    char *__dir, char *__fname, char *__ext );
extern void      swab( char *__src, char *__dest, int __num );
extern char     *ultoa( unsigned long int __value, char *__buf, int __radix );
extern char     *utoa( unsigned int __value, char *__buf, int __radix );

#ifdef  __INLINE_FUNCTIONS__
 #pragma intrinsic(_rotl,_rotr)
 #ifdef __386__
  #pragma intrinsic(_lrotl,_lrotr)
 #endif
#endif

/* min and max macros */
#if !defined(__max)
#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#endif
#if !defined(max) && !defined(__cplusplus)
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#endif
#if !defined(__min)
#define __min(a,b)  (((a) < (b)) ? (a) : (b))
#endif
#if !defined(min) && !defined(__cplusplus)
#define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif


/*
 * The following sizes are the maximum sizes of buffers used by the _fullpath()
 * _makepath() and _splitpath() functions.  They include space for the '\0'
 * terminator.
 */
#define _MAX_PATH       256     /*  maximum length of path name         */
#define _MAX_DRIVE      48      /*  maximum length of node name w/ '\0' */
#define _MAX_NODE    _MAX_DRIVE /*  maximum length of node name w/ '\0' */
#define _MAX_DIR        256     /*  maximum length of subdirectory      */
#define _MAX_FNAME      48      /*  maximum length of a file name       */
#define _MAX_EXT        48      /*  maximum length of a file extension  */

#define _MAX_PATH2 (_MAX_PATH+3) /* maximum size of output buffer
                                    for _splitpath2() */

extern char **environ;   /*  pointer to environment table        */

#ifndef errno
    #define errno (*__get_errno_ptr())
#endif
extern int errno;
extern unsigned char __near _osmajor;   /*  O/S version #                   */
extern unsigned char __near _osminor;   /*  O/S version #                   */
extern unsigned __near      _amblksiz;  /*  mallocs done in multiples of    */

#ifndef alloca
extern void  *alloca(size_t __size);
extern void  *_alloca(size_t __size);
extern void  *__doalloca(size_t __size);
extern unsigned stackavail( void );
#pragma aux stackavail __modify __nomemory;

#define __ALLOCA_ALIGN( s )     (((s)+(sizeof(int)-1))&~(sizeof(int)-1))
#define __alloca( s )           __doalloca(__ALLOCA_ALIGN(s))

#if defined(__386__)
extern void __GRO(size_t __size);
#pragma aux __GRO "*" __parm __routine [];
#define alloca( s )  ((__ALLOCA_ALIGN(s)<stackavail())?(__GRO(__ALLOCA_ALIGN(s)),__alloca(s)):NULL)
#define _alloca( s ) ((__ALLOCA_ALIGN(s)<stackavail())?(__GRO(__ALLOCA_ALIGN(s)),__alloca(s)):NULL)
#else
#define alloca( s )  ((__ALLOCA_ALIGN(s)<stackavail())?__alloca(s):NULL)
#define _alloca( s ) ((__ALLOCA_ALIGN(s)<stackavail())?__alloca(s):NULL)
#endif

#if defined(__386__)
#pragma aux     __doalloca =                            \
            "sub esp,eax"                               \
            __parm __nomemory [eax] __value [esp] __modify __exact __nomemory [esp];
#elif defined(__SMALL__) || defined(__MEDIUM__) /* small data models */
#pragma aux     __doalloca =    \
            "sub sp,ax"         \
            __parm __nomemory [ax] __value [sp] __modify __exact __nomemory [sp];
#else                                           /* large data models */
#pragma aux     __doalloca =    \
            "sub sp,ax"         \
            "mov ax,sp"         \
            "mov dx,ss"         \
            __parm __nomemory [ax] __value [dx ax] __modify __exact __nomemory [dx ax sp];
#endif
#endif

#if defined(__386__)
extern int brk(void *endds);
extern void *sbrk(int incr);
#else
extern void __near *__brk(unsigned __new_brk_value);
extern void __near *sbrk(int __increment);
#endif

 typedef void (*onexit_t)();
extern onexit_t onexit(onexit_t __func);
#endif

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif
#define _STDLIB_H_INCLUDED
#ifdef __cplusplus
};
#endif
#endif
