/*
 *  regex.h     Regular expression handler structures
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
 
#ifndef _REGEX_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#ifndef _LIMITS_H_INCLUDED
#include <limits.h>
#endif

/*
    The following is a summary of the regular expression syntax.
    For a more detailed description, please refer to 1003.2, Pattern Matching.

basic expressions:

    -- anchoring
    expr
        :   '^' expr.1
        |   expr.1 '$'
        |  '^' expr.1 '$'
        ;

    -- concatenation
    expr.1
        :   expr.2
        |   expr.1 expr.2
        ;

    -- replication
    expr.2
        :   expr.3
        |   expr.3 '*'
        |   expr.3 interval
        ;
    -- atomic expressions
    expr.3
        :   ordinary_char
        |   bracket_expression
        |   '.'
        |   back_reference
        |   '\' '(' expr.1 '\' ')'
        ;
    -- define an interval:
    interval
        :   '\' '{' dup_count '\' '}',
        |   '\' '{' min_dup_count ',' '\' '}'
        |   '\' '{' min_dup_count ',' max_dup_count '\' '}'
        |   '\' '{' ',' max_dup_count '\' '}'
        ;

    bracket_expression
        :   '[' bracket_list ']'
        |   '[' '^' bracket_list ']'
        ;

    bracket_list
        :   bexpr
        |   bracket_list bexpr
        ;
    bexpr
        :   char_class
        |   collate
        |   collate '-' collate
        ;
    collate
        :   ordinary_char
        |   "[." string ".]"        -- collating symbol
        |   "[=" string "=]"        -- equivalence class
        |   "[=" '.' "=]"           -- any char.
        ;
    char_class
        :   "[:alpha:]" | "[:alnum:]" | "[:graph:]" | "[:upper:]"
        |   "[:space:]" | "[:cntrl:]" | "[:lower:]" | "[:punct:]"
        |   "[:xdigit:]" | [:digit:]" | "[:print:]"
        ;


extended expressions:
    -- anchoring
    eexpr
        :   '^' eexpr.0
        |   eexpr.0 '$'
        |  '^' eexpr.0 '$'
        ;

    -- alternation
    eexpr.0
        :   eexpr.1
        |   eexpr.0 '|' eexpr.1
        ;

    -- concatenation
    eexpr.1
        :   eexpr.2
        |   eexpr.1 eexpr.2
        ;

    -- replication
    eexpr.2
        :   eexpr.3
        |   eexpr.3 '*'
        |   eexpr.3 '?'
        |   eexpr.3 '+'
        |   eexpr.3 interval
        ;

    -- atomic expressions
    eexpr.3
        :   ordinary_char
        |   '\' special_char
        |   '.'
        |   bracket_expression
        |   '(' eexpr.0 ')'
        ;

*/

/*  for regcomp()   */

#define REG_EXTENDED    0x01
#define REG_NEWLINE     0x02
#define REG_ICASE       0x04
#define REG_NOSUB       0x08

#ifndef NO_EXT_KEYS
/* preserve the expression for conversion to dfa */
#define REG_NOOPT       0x100
/* expect the first and last chars to match,
   do NOT consider them part of the expression
   handy for "/expr/" style apps.
*/
#define REG_QUOTED      0x200
#endif

/* for regexec()    */
#define REG_NOTBOL      0x01
#define REG_NOTEOL      0x02


/*  
    These are return values for regcomp().
    0 is ok, otherwise an error occurred.
    These are defined in DRAFT 11 of .2
*/
#ifndef NO_EXT_KEYS
#define REG_OK          0
#endif

#define REG_NOMATCH     1
#define REG_BADPAT      2
#define REG_ECOLLATE    3
#define REG_ECTYPE      4
#define REG_EESCAPE     5
#define REG_ESUBREG     6
#define REG_EBRACK      7
#define REG_EPAREN      8
#define REG_EBRACE      9
#define REG_BADBR       10
#define REG_ERANGE      11
#define REG_ESPACE      12
#define REG_BADRPT      13

#ifndef NO_EXT_KEYS

#define REG_EEQUIV      64
#define REG_ENEST       65
#define REG_INTERNAL    66
#define REG_CORRUPT     67
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif
typedef struct    {
        size_t          re_nsub;        /* number of sub-expressions */
        short           re_flags;       /* compilation flags */
        short           re_bol;         /* does it match begining of line */
        void            *re_mach;       /* The machine itself */
        unsigned char   *re_stch;       /* Set of start characters */
        unsigned char  **re_csets;      /* set of char classes */
        short           re_max_cset;    /* maximum number of csets */
        short           re_last_cset;   /* number in actual use */
        void            *reserved[8];   /* for future consideration */
} regex_t;

typedef struct {
    const char *rm_sp;
    const char *rm_ep;
} regmatch_t;
#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __STDC__

extern  int     regcomp( regex_t *__preg, const char *__pattern, int __cflags );
extern  int     regexec( const regex_t *__preg, const char *__str,
                         size_t __nmatch, regmatch_t *__pmatch, int __eflags );
extern  void    regfree( regex_t *__preg );
extern  size_t  regerror( int __errcode, const regex_t *preg, char *errbuf,
                            size_t errbuf_size);
                            
#else
extern  int     regcomp();
extern  int     regexec();
extern  void    regfree();
extern  size_t  regerror();

#endif
#ifdef __cplusplus
};
#endif

#define _REGEX_H_INCLUDED
#endif

