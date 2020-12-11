//
//  wcvector.h   Defines the WATCOM Container Vector Classes
//
//  Copyright by WATCOM International Corp. 1988-1996.  All rights reserved.
//

#ifndef _WCVECTOR_H_INCLUDED

#ifndef __cplusplus
#error wcvector.h is for use with C++
#endif

#include <wcdefs.h>
#include <wcexcept.h>
#include <string.h>
#include <wcvbase.h>




//
//  This defines a basic Value vector with elements of type <Type>
//

template <class Type>
class WCValVector : public WCBareVectorBase<Type> {
public:
    inline WCValVector ( size_t length = 0 )
                        : WCBareVectorBase<Type>( length ) {};
    WCValVector ( size_t, const Type& );
    inline WCValVector ( const WCValVector & orig )
                                        : WCBareVectorBase<Type> ( 0 ) {
        base_construct ( &orig );
    };

    inline virtual ~WCValVector() {};

    inline size_t length () const {
        return( vector_len );
    };

    Type& operator[] ( int index );

    const Type& operator[] ( int index ) const;

    inline WCValVector & operator= ( const WCValVector & orig ) {
        base_assign( &orig );
        return( *this );
    };
};


template <class Type>
WCValVector<Type>::WCValVector( size_t length, const Type &init_val )
                        : WCBareVectorBase<Type>( length ) {
    for( int i = 0; i < vector_len; i++ ){
        new( &( vector[ i ] ) ) Type( init_val );
    }
    num_init = length;
};
    

//
//  The non-const index operator.  If index is greater than the length of
//  the vector and the resize_required exception is disabled, then attempt to
//  resize the vector so that index is the last element.
//

template <class Type>
Type &WCValVector<Type>::operator[] ( int index ) {
    if( index < 0 ) {
        base_throw_index_range();
        index = 0;
    }
    if( index >= num_init ) {
        if( index >= vector_len ){
            // attempt to index an element greater than the vector's length
            base_throw_resize_required();
            if( !resize( index + 1 ) ){
                // resize to perform request failed.  Try and have at least one
                // valid entry
                if( vector_len == 0 ) {
                    resize( 1 );
                    index = 0;
                } else {
                    index = vector_len - 1;
                }
            }
        }
        // default initialize any unitialized entries upto index
        base_init_upto( index );
    }
    return( vector[ index ] );
};


//
// The const index operator.  If the vector is empty and exceptions are
// disabled, add a default initialized first element, and return it.
//

template <class Type>
const Type &WCValVector<Type>::operator[] ( int index ) const {
    WCValVector<Type> * const non_const_this = ( WCValVector<Type> * )this;
    if( vector_len == 0 ) {
        base_throw_empty_container();
        base_throw_index_range();
        non_const_this->resize( 1 );
        return( vector[ 0 ] );
    } else {
        int new_index = base_index_check( index );
        if( new_index >= num_init ) {
            // Even though this is a non-const operation, the user's view of
            // the vector is not being changed.  Any element the user
            // accesses must be intialized.
            non_const_this->base_init_upto( new_index );
        }
        return( vector[ new_index ] );
    }
};



//
//  This defines a basic Pointer vector with elements of type pointer to <Type>
//
// Implementation note:
// WCPtrVector inherits from WCValVector templated over <void *>.  This saves
// most of the vector code being generated for pointer vectors templated over
// different types, speeding up compile time, and reducing code size.
//

template <class Type>
class WCPtrVector : public WCValVector<void *> {
protected:
    typedef Type * __Type_Ptr;
    virtual void base_init_upto( int );
public:
    inline WCPtrVector( size_t length = 0 )
                        : WCValVector( length ) {};

    inline WCPtrVector( size_t length, const Type *init_value )
                        : WCValVector( length
                                     , (void *)init_value ) {};

    inline WCPtrVector( const WCPtrVector & orig ) : WCValVector( 0 ) {
        base_construct( &orig );
    };

    inline virtual ~WCPtrVector() {};

    void clearAndDestroy();

    inline WCPtrVector & operator=( const WCPtrVector & orig ) {
        base_assign( &orig );
        return( *this );
    };

    Type * &operator[] ( int index ) {
        return( (Type * &)WCValVector::operator[]( index ) );
    };

    Type * const &operator[] ( int index ) const {
        return( (Type * const &)WCValVector::operator[]( index ) );
    };
};


template<class Type>
void WCPtrVector<Type>::base_init_upto( int index ) {
    if( index >= num_init ){
        // intialize the vector by NULLing out unitialized elements
        memset( &vector[ num_init ], 0
              , ( index + 1 - num_init ) * sizeof( void * ) );
        num_init = index + 1;
    }
}


template <class Type>
void WCPtrVector<Type>::clearAndDestroy() {
    for( unsigned i = 0; i < num_init; i++ ) {
        delete( (Type *)( vector[ i ] ) );
    }   
    clear();
};




//
//  This defines the Value Ordered vector with elements of type <Type>
//

template <class Type>
class WCValOrderedVector : public WCOrderedVectorBase<Type> {
private:
    virtual int base_equivalent( const Type &elem1, const Type &elem2 ) const {
        return( elem1 == elem2 );
    };
public:
    inline WCValOrderedVector( size_t length = WCDEFAULT_VECTOR_LENGTH,
                unsigned default_grow = WCDEFAULT_VECTOR_RESIZE_GROW )
                        : WCOrderedVectorBase<Type>( length, default_grow ) {};

    inline WCValOrderedVector( const WCValOrderedVector& orig )
                        : WCOrderedVectorBase<Type>( 0, 0 ) {
        base_construct( &orig );
    };

    inline virtual ~WCValOrderedVector() {};

    inline WCValOrderedVector & operator=( const WCValOrderedVector& orig ) {
        base_assign( &orig );
        return( *this );
    };
};




//
//  This defines the pointer Ordered vector with elements of type
//  pointer to <Type>
//

template <class Type>
class WCPtrOrderedVector
        : public WCPtrVectorBase<Type, WCOrderedVectorBase<void *> > {
private:
    virtual int base_equivalent( const __Stored_Ptr &elem1
                               , const __Stored_Ptr &elem2 ) const {
        return( *(const Type *)elem1 == *(const Type *)elem2 );
    }
public:
    inline WCbool append( Type * new_elem ){
        return( insert( new_elem ) );
    };

    inline WCbool insert( Type * new_elem ){
        return( WCOrderedVectorBase::insert( new_elem ) );
    };

    inline WCbool insertAt( int index, Type * new_elem ){
        return( WCOrderedVectorBase::insertAt( index, new_elem ) );
    };

    inline WCbool prepend( Type * new_elem ){
        return( WCOrderedVectorBase::prepend( new_elem ) );
    };

    inline WCPtrOrderedVector( size_t length = WCDEFAULT_VECTOR_LENGTH,
                unsigned default_grow = WCDEFAULT_VECTOR_RESIZE_GROW )
                        : WCPtrVectorBase( length, default_grow ) {};

    inline WCPtrOrderedVector( const WCPtrOrderedVector & orig )
                        : WCPtrVectorBase( 0, 0 ) {
        base_construct( &orig );
    };

    inline virtual ~WCPtrOrderedVector() {};

    inline WCPtrOrderedVector & operator=( const WCPtrOrderedVector & orig ) {
        base_assign( &orig );
        return( *this );
    };
};




//
//  This defines the Value Sorted vector with elements of type <Type>
//

template <class Type>
class WCValSortedVector : public WCSortedVectorBase<Type> {
private:
    virtual int base_equivalent( const Type &elem1, const Type &elem2 ) const {
        return( elem1 == elem2 );
    };
    virtual int base_less_than( const Type& elem1, const Type& elem2 ) const {
        return( elem1 < elem2 );
    }
public:
    inline WCValSortedVector( size_t length = WCDEFAULT_VECTOR_LENGTH,
                unsigned default_grow = WCDEFAULT_VECTOR_RESIZE_GROW )
                        : WCSortedVectorBase<Type>( length, default_grow ) {};

    inline WCValSortedVector( const WCValSortedVector & orig )
                        : WCSortedVectorBase<Type>( 0, 0 ) {
        base_construct( &orig );
    };

    inline virtual ~WCValSortedVector() {};

    inline WCValSortedVector & operator=( const WCValSortedVector & orig ) {
        base_assign( &orig );
        return( *this );
    };
};




//
//  This defines the pointer Sorted vector with elements of type
//  pointer to <Type>
//

template <class Type>
class WCPtrSortedVector
                : public WCPtrVectorBase<Type, WCSortedVectorBase<void *> > {
private:
    virtual int base_equivalent( const __Stored_Ptr &elem1
                               , const __Stored_Ptr &elem2 ) const {
        return( *(const Type *)elem1 == *(const Type *)elem2 );
    }
    virtual int base_less_than( const __Stored_Ptr &elem1
                              , const __Stored_Ptr &elem2 ) const {
        return( *(const Type *)elem1 < *(const Type *)elem2 );
    }
public:
    inline WCbool insert( Type * elem ) {
        return( WCSortedVectorBase::insert( elem ) );
    }

    inline WCPtrSortedVector( size_t length = WCDEFAULT_VECTOR_LENGTH,
                unsigned default_grow = WCDEFAULT_VECTOR_RESIZE_GROW )
                        : WCPtrVectorBase( length, default_grow ) {};

    inline WCPtrSortedVector( const WCPtrSortedVector & orig )
                        : WCPtrVectorBase( 0, 0 ) {
        base_construct( &orig );
    };

    inline virtual ~WCPtrSortedVector() {};

    inline WCPtrSortedVector & operator=( const WCPtrSortedVector & orig ) {
        base_assign( &orig );
        return( *this );
    };
};


#define _WCVECTOR_H_INCLUDED
#endif
