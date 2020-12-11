//
//  wcstack.h    Defines the WATCOM Stack Container Class
//
//  Copyright by WATCOM International Corp. 1988-1996.  All rights reserved.
//

#ifndef _WCSTACK_H_INCLUDED

#ifndef __cplusplus
#error wcstack.h is for use with C++
#endif

#include <wcdefs.h>
#include <wclist.h>




//
//  The WCStack template class defines a stack.  The template supplies
//  the type of the data maintained in the stack, and the methods for
//  manipulating the stack.
//
//  The class 'Type' should be properly defined for copy and assignment
//  operations.
//

template<class Type, class FType>
class WCStack : private FType {
public:
    inline WCStack() {};
    inline WCStack( void * (*user_alloc)( size_t ) 
                  , void (*user_dealloc)( void *, size_t )
                ) : FType( user_alloc, user_dealloc ) {};
    inline ~WCStack() {};

    inline WCbool push( const Type & data )  {
        return( FType::insert( data ) );
    };

    inline Type pop() {
        return( FType::get() );
    };

    inline Type top() const {
        return( FType::find( 0 ) );
    };

    inline WCbool isEmpty() const {
        return( FType::isEmpty() );
    };

    inline int entries() const {
        return( FType::entries() );
    };

    inline void clear() {
        FType::clear();
    };

    inline wc_state exceptions() const {
        return( FType::exceptions() );
    };

    inline wc_state exceptions( wc_state const set_flags ) {
        return( FType::exceptions( set_flags ) );
    };
};


#define _WCSTACK_H_INCLUDED
#endif
