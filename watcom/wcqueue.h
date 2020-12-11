//
//  wcqueue.h    Defines the WATCOM Queue Container Class
//
//  Copyright by WATCOM International Corp. 1988-1996.  All rights reserved.
//

#ifndef _WCQUEUE_H_INCLUDED

#ifndef __cplusplus
#error wcqueue.h is for use with C++
#endif

#include <wcdefs.h>
#include <wclist.h>




//
//  The WCQueue template class defines a queue.  The template supplies
//  the type of the data maintained in the queue, and the methods for
//  manipulating the queue.
//
//  The insert operation does an append.  This is because an item
//  inserted into a queue is actually the last item removed.
//
//  The class 'Type' should be properly defined for copy and assignment
//  operations.
//

template<class Type, class FType>
class WCQueue : private FType {
public:
    inline WCQueue() {};
    inline WCQueue( void * (*user_alloc)( size_t )
                  , void (*user_dealloc)( void *, size_t )
                ) : FType( user_alloc, user_dealloc ) {};
    inline ~WCQueue() {};

    inline WCbool insert( const Type & data )  {
        return( FType::append( data ) );
    };

    inline WCbool isEmpty() const {
        return( FType::isEmpty() );
    };

    inline int entries() const {
        return( FType::entries() );
    };

    inline Type get() {
        return( FType::get() );
    };

    inline Type first() const {
        return( FType::find( 0 ) );
    };

    inline Type last() const {
        return( FType::findLast() );
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


#define _WCQUEUE_H_INCLUDED
#endif