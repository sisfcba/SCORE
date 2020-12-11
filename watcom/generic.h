//
//  generic.h   Macros to support pseudo-templates
//
//  Copyright by WATCOM International Corp. 1988-1996.  All rights reserved.
//
#ifndef _GENERIC_H_INCLUDED

#ifndef __cplusplus
#error generic.h is for use with C++
#endif

#define name2(__n1,__n2)                __paste2(__n1,__n2)
#define __paste2(__p1,__p2)             __p1##__p2
#define name3(__n1,__n2,__n3)           __paste3(__n1,__n2,__n3)
#define __paste3(__p1,__p2,__p3)        __p1##__p2##__p3
#define name4(__n1,__n2,__n3,__n4)      __paste4(__n1,__n2,__n3,__n4)
#define __paste4(__p1,__p2,__p3,__p4)   __p1##__p2##__p3##__p4

#define declare(__Cls,__Typ1) \
        name2(__Cls,declare)(__Typ1)
#define implement(__Cls,__Typ1) \
        name2(__Cls,implement)(__Typ1)
#define declare2(__Cls,__Typ1,__Typ2) \
        name2(__Cls,declare)(__Typ1,__Typ2)
#define implement2(__Cls,__Typ1,__Typ2) \
        name2(__Cls,implement)(__Typ1,__Typ2)
#define callerror(__Cls,__Typ1,__Typ2,__Typ3) \
        (*errorhandler(__Cls,__Typ1))(__Typ2,__Typ3)
#define errorhandler(__Cls,__Typ1) \
        name3(__Typ1,__Cls,handler)
#define set_handler(__Cls,__Typ1,__Typ2) \
        name4(set_,__Typ1,__Cls,_handler)(__Typ2)

// undocumented AT&T function (WATCOM stub returns first argument)
extern int genericerror( int, char* );
typedef int (*GPT)( int, char* );

#define _GENERIC_H_INCLUDED
#endif
