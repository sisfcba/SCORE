/*
 *  string.h    String functions
 *
 *  Copyright by WATCOM International Corp. 1988-1996.  All rights reserved.
 */
#ifndef _STRING_H_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#ifndef _SIZE_T_DEFINED_
#define _SIZE_T_DEFINED_
 typedef unsigned size_t;
#endif

#ifndef NULL
 #if defined(__SMALL__) || defined(__MEDIUM__) || defined(__386__)
  #define NULL   0
 #else
  #define NULL   0L
 #endif
#endif

extern void *memchr( const void *__s, int __c, size_t __n );
extern int   memcmp( const void *__s1, const void *__s2, size_t __n );
extern void *memcpy( void *__s1, const void *__s2, size_t __n );
extern void *memmove( void *__s1, const void *__s2, size_t __n );
extern void *memset( void *__s, int __c, size_t __n );
extern char *strcat( char *__s1, const char *__s2 );
extern char *strchr( const char *__s, int __c );
extern int strcmp( const char *__s1, const char *__s2 );
extern int strcoll( const char *__s1, const char *__s2 );
extern size_t strxfrm( char *__s1, const char *__s2, size_t __n );
extern char *strcpy( char *__s1, const char *__s2 );
extern size_t strcspn( const char *__s1, const char *__s2 );
extern char *strerror( int __errnum );
extern size_t strlen( const char *__s );
extern char *strncat( char *__s1, const char *__s2, size_t __n );
extern int strncmp( const char *__s1, const char *__s2, size_t __n );
extern char *strncpy( char *__s1, const char *__s2, size_t __n );
extern char *strpbrk( const char *__s1, const char *__s2 );
extern char *strrchr( const char *__s, int __c );
extern size_t strspn( const char *__s1, const char *__s2 );
extern char *strstr( const char *__s1, const char *__s2 );
extern char *strtok( char *__s1, const char *__s2 );

#if defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS) /*extensions enabled*/

/* WATCOM's Additional Functions (non-ANSI, non-POSIX) */

#if !defined(_fmemccpy) || !defined(_INC_WINDOWSX)
extern void __far *_fmemccpy(void __far *__s1,const void __far *__s2,int __c,size_t __n);
#endif
#if !defined(_fmemchr) || !defined(_INC_WINDOWSX)
extern void __far *_fmemchr( const void __far *__s, int __c, size_t __n );
#endif
#if !defined(_fmemcpy) || !defined(_INC_WINDOWSX)
extern void __far *_fmemcpy( void __far *__s1, const void __far *__s2, size_t __n );
#endif
#if !defined(_fmemmove) || !defined(_INC_WINDOWSX)
extern void __far *_fmemmove( void __far *__s1, const void __far *__s2, size_t __n );
#endif
#if !defined(_fmemset) || !defined(_INC_WINDOWSX)
extern void __far *_fmemset( void __far *__s, int __c, size_t __n );
#endif
#if !defined(_fmemcmp) || !defined(_INC_WINDOWSX)
extern int  _fmemcmp( const void __far *__s1, const void __far *__s2, size_t __n );
#endif
#if !defined(_fmemicmp) || !defined(_INC_WINDOWSX)
extern int  _fmemicmp( const void __far *__s1, const void __far *__s2, size_t __n );
#endif
#if !defined(_fstrcat) || !defined(_INC_WINDOWSX)
extern char __far *_fstrcat( char __far *__s1, const char __far *__s2 );
#endif
#if !defined(_fstrchr) || !defined(_INC_WINDOWSX)
extern char __far *_fstrchr( const char __far *__s, int __c );
#endif
#if !defined(_fstrcmp) || !defined(_INC_WINDOWSX)
extern int  _fstrcmp( const char __far *__s1, const char __far *__s2 );
#endif
#if !defined(_fstrcpy) || !defined(_INC_WINDOWSX)
extern char __far *_fstrcpy( char __far *__s1, const char __far *__s2 );
#endif
#if !defined(_fstrcspn) || !defined(_INC_WINDOWSX)
extern size_t _fstrcspn( const char __far *__s1, const char __far *__s2 );
#endif
#if !defined(_fstrdup) || !defined(_INC_WINDOWSX)
extern char __far *_fstrdup( const char __far *__string );
#endif
#if !defined(_fstricmp) || !defined(_INC_WINDOWSX)
extern int  _fstricmp( const char __far *__s1, const char __far *__s2 );
#endif
#if !defined(_fstrncat) || !defined(_INC_WINDOWSX)
extern char __far *_fstrncat( char __far *__s1, const char __far *__s2, size_t __n );
#endif
#if !defined(_fstrlen) || !defined(_INC_WINDOWSX)
extern size_t _fstrlen( const char __far *__s );
#endif
#if !defined(_fstrlwr) || !defined(_INC_WINDOWSX)
extern char __far *_fstrlwr( char __far *__string );
#endif
#if !defined(_fstrncmp) || !defined(_INC_WINDOWSX)
extern int  _fstrncmp( const char __far *__s1, const char __far *__s2, size_t __n );
#endif
#if !defined(_fstrncpy) || !defined(_INC_WINDOWSX)
extern char __far *_fstrncpy( char __far *__s1, const char __far *__s2, size_t __n );
#endif
#if !defined(_fstrnicmp) || !defined(_INC_WINDOWSX)
extern int  _fstrnicmp( const char __far *__s1, const char __far *__s2, size_t __n );
#endif
#if !defined(_fstrnset) || !defined(_INC_WINDOWSX)
extern char __far *_fstrnset( char __far *__string, int __c, size_t __len );
#endif
#if !defined(_fstrpbrk) || !defined(_INC_WINDOWSX)
extern char __far *_fstrpbrk( const char __far *__s1, const char __far *__s2 );
#endif
#if !defined(_fstrrchr) || !defined(_INC_WINDOWSX)
extern char __far *_fstrrchr( const char __far *__s, int __c );
#endif
#if !defined(_fstrrev) || !defined(_INC_WINDOWSX)
extern char __far *_fstrrev( char __far *__string );
#endif
#if !defined(_fstrset) || !defined(_INC_WINDOWSX)
extern char __far *_fstrset( char __far *__string, int __c );
#endif
#if !defined(_fstrspn) || !defined(_INC_WINDOWSX)
extern size_t _fstrspn( const char __far *__s1, const char __far *__s2 );
#endif
#if !defined(_fstrstr) || !defined(_INC_WINDOWSX)
extern char __far *_fstrstr( const char __far *__s1, const char __far *__s2 );
#endif
#if !defined(_fstrtok) || !defined(_INC_WINDOWSX)
extern char __far *_fstrtok( char __far *__s1, const char __far *__s2 );
#endif
#if !defined(_fstrupr) || !defined(_INC_WINDOWSX)
extern char __far *_fstrupr( char __far *__string );
#endif
extern void movedata( unsigned __srcseg, unsigned __srcoff,
               unsigned __tgtseg, unsigned __tgtoff, unsigned __len );
extern void *memccpy( void *__s1, const void *__s2, int __c, size_t __n );
extern int  memicmp( const void *__s1, const void *__s2, size_t __n );
extern int  _memicmp( const void *__s1, const void *__s2, size_t __n );
extern int   strcmpi( const char *__s1, const char *__s2 );
extern char *strdup( const char *__string );
extern char *_strdup( const char *__string );
extern int   stricmp( const char *__s1, const char *__s2 );
extern int   _stricmp( const char *__s1, const char *__s2 );
extern char *strlwr( char *__string );
extern char *_strlwr( char *__string );
extern int   strnicmp( const char *__s1, const char *__s2, size_t __n );
extern int   _strnicmp( const char *__s1, const char *__s2, size_t __n );
extern char *strnset( char *__string, int __c, size_t __len );
extern char *strrev( char *__string );
extern char *_strrev( char *__string );
extern char *strset( char *__string, int __c );
extern char *strupr( char *__string );
extern char *_strupr( char *__string );

/* QNX's Additional Functions (non-ANSI, non-POSIX) */

extern void __strerror( int __max, int __errnum, char *__buf );
#endif  /* EXTENSIONS */

#ifdef  __INLINE_FUNCTIONS__
#if defined(_QNX_SOURCE) || !defined(NO_EXT_KEYS) /*extensions enabled*/
 #pragma intrinsic(movedata,_fmemchr,_fmemcmp,_fmemcpy,_fmemset)
 #pragma intrinsic(_fstrcat,_fstrcmp,_fstrcpy,_fstrlen)
#endif
 #pragma intrinsic(memchr,memcmp,memcpy,strcat,strcpy,strlen,strchr)
 #ifndef __386__
 #pragma intrinsic(memset,strcmp)
 #endif
#endif  /* __INLINE_FUNCTIONS__ */

#define _STRING_H_INCLUDED
#ifdef __cplusplus
};
#endif
#endif
