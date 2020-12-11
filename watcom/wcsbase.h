//
//  wcsbase.h    Definitions and base implementation for the WATCOM Container
//               Skip List class
//
//  Copyright by WATCOM International Corp. 1988-1996.  All rights reserved.
//

#ifndef _WCSBASE_H_INCLUDED

#ifndef __cplusplus
#error wcsbase.h is for use with C++
#endif

#include <stddef.h>

//
// Skip Lists are a probabilistic alternative to balanced trees, as
// described in the June 1990 issue of CACM and were invented by
// William Pugh in 1987.
//


//
// constants
//

//
// The probability one more pointer being added to a skip list node
// one quarter and one half.  One of these constants may be passed to
// constructor as the optional prob parameter, WCSKIPLIST_PROB_QUARTER
// is used by default.
//

const unsigned WCSKIPLIST_PROB_QUARTER = 3;
const unsigned WCSKIPLIST_PROB_HALF = 1;

//
// The default maximum number of pointers in each node.  This is used as
// a default value for the max_ptrs constructor parameter.  The default
// prob and max_ptrs constructor parameters are suitable for skip lists
// with upto about 100,000 elements.
//

const unsigned WCDEFAULT_SKIPLIST_MAX_PTRS = 8;

//
// The maximum value for the max_ptrs constructor parameter.  If a value
// greater than WCSKIPLIST_MAX_PTRS is passed to the max_ptrs constructor
// parameter, then WCSKIPLIST_MAX_PTRS will be used as the maximum number
// of pointers.  With WCSKIPLIST_PROB_QUARTER, WCSKIPLIST_MAX_POINTERS is
// suitable for a skip list containing over four billion elements.  With
// WCSKIPLIST_PROB_HALF, WCSKIPLIST_MAX_POINTERS is suitable for a skip
// list containing over one million elements.
//

const unsigned WCSKIPLIST_MAX_PTRS = 20;



//
// WCSkipListPtrs and WCSkipListNode are used internally by the SkipList
// classes to store an element and its pointers into the skip list.
//

struct WCSkipListPtrs {
    WCSkipListPtrs *forward[ 1 ];       // variable sized array of forward ptrs
};

template <class Type>
class WCSkipListNode {
public:
    Type data;
    WCSkipListPtrs ptrs;

    inline void * operator new( size_t, void * ptr ){
        return ptr;
    }

    inline WCSkipListNode( const Type &elem ) : data( elem ) {};
    inline ~WCSkipListNode() {};
};



//
// Skip List Dictionary implementation object:
// Combines the Key and Value into one object (used internally)
//

template <class Key, class Value>
class WCSkipListDictKeyVal{
public:
    Key key;
    Value value;

    inline WCSkipListDictKeyVal( const WCSkipListDictKeyVal &orig )
            : key( orig.key ), value( orig.value ) {};
    inline WCSkipListDictKeyVal( const Key &new_key, const Value &new_value ) 
            : key( new_key ), value( new_value ) {};
    inline WCSkipListDictKeyVal( const Key &new_key ) : key( new_key ) {};
    inline WCSkipListDictKeyVal() {};
    inline ~WCSkipListDictKeyVal() {};
};


// Macros to give the user the size of allocated objects
#define WCValSkipListItemSize( Type, num_ptrs )                         \
    ( sizeof( WCSkipListNode<Type> ) + ( num_ptrs - 1 ) * sizeof( void * ) )
#define WCPtrSkipListItemSize( Type, num_ptrs )                         \
    WCValSkipListItemSize( void *, num_ptrs )
#define WCValSkipListSetItemSize( Type, num_ptrs )                      \
    WCValSkipListItemSize( Type, num_ptrs )
#define WCPtrSkipListSetItemSize( Type, num_ptrs )                      \
    WCPtrSkipListItemSize( Type, num_ptrs )
#define WCValSkipListDictItemSize( Key, Value, num_ptrs )               \
    ( sizeof( WCSkipListNode<WCSkipListDictKeyVal<Key, Value> > )       \
      + ( num_ptrs - 1 ) * sizeof( void * ) )
#define WCPtrSkipListDictItemSize( Key, Value, num_ptrs )               \
    WCValSkipListDictItemSize( void *, void *, num_ptrs )



//
// This base class provides skip list base functionality which does not
// require the templated Type.
//
// WCExcept is a base class to provide exception handling.
//
// This is an abstract class to prevent objects of this type being created.
//

class WCSkipNonTempBase : public WCExcept {
private:
    // raw memory for the header element pointers
    char header_mem[ sizeof( void * ) * WCSKIPLIST_MAX_PTRS ];
    // if FALSE, insert will not insert a duplicate value
    const WCbool allowDuplicates;

    void base_init( unsigned prob, unsigned max_ptrs );

protected:
    // user allocator and deallocator functions
    void * (* alloc_fn)( size_t );
    void (* dealloc_fn)( void *, size_t );

    // for base_random_level
    static unsigned randomsLeft;
    static unsigned randomBits;
    unsigned max_ptrs_in_node;
    unsigned probability;

    // the current greatest level of elements in the list
    // (1 more than the number of levels in the list)
    int level;          
    // a pointer to the header link in the skip list
    // (points to initialized header_mem)
    WCSkipListPtrs *header;
    unsigned num_entries;


    // pointer to the nodes stored in the skiplist
    typedef WCSkipListPtrs* node_ptr;

    // non-templated pointers to the templated Type
    typedef const void *TTypePtr;


    // true if elements are equivalence
    virtual int base_equiv( node_ptr elem1, TTypePtr elem2 ) const = 0;

    // true if lhs < rhs
    virtual int base_less( node_ptr lhs, TTypePtr rhs ) const = 0;

    // equivalents of new and delete
    virtual node_ptr base_new_node( TTypePtr elem
                                  , unsigned level_less_1 ) = 0;

    virtual void base_delete_node( node_ptr node, unsigned level_less_1 ) = 0;

    // the assignment operator base
    void base_assign( const WCSkipNonTempBase * orig );

    // the copy constructor base
    void base_construct( const WCSkipNonTempBase * orig );

    node_ptr base_find( TTypePtr elem ) const;

    node_ptr base_find_with_update( TTypePtr elem, node_ptr update[] ) const;

// this should be private eventually
    inline void base_init_header() {
        header = (node_ptr)header_mem;
        for( int i = 0; i < max_ptrs_in_node; i++ ){
            header->forward[ i ] = 0;
        }
    };

    node_ptr base_insert( TTypePtr elem );

    // insert a copy of the data contained in this node
    // (used by base_construct)
    virtual int base_insert_copy( node_ptr ) = 0;

    // for WCSkipListDuplicatesBase
    unsigned base_occurrencesOf( TTypePtr elem ) const;

    int base_random_level();

    // for WCSkipListDuplicatesBase
    unsigned base_removeAll( TTypePtr elem );

    node_ptr base_remove_but_not_delete( TTypePtr elem, int &num_ptrs );

public:
    WCSkipNonTempBase( unsigned prob, unsigned max_ptrs
                     , WCbool duplicates );

    WCSkipNonTempBase( unsigned prob, unsigned max_ptrs
                     , void * (*user_alloc)( size_t )
                     , void (*user_dealloc)( void *, size_t )
                     , WCbool duplicates );

    inline virtual ~WCSkipNonTempBase() {};

    void clear();

    WCbool remove( TTypePtr elem );
};




//
// WCSkipListBase provides the skip list functionality
//
// This is an abstract class to prevent objects of this type being created.
//

template<class Type>
class WCSkipListBase : public WCSkipNonTempBase {
protected:
    // the nodes stored in the skip list
    typedef WCSkipListNode<Type> NodeType;


    inline node_ptr base_find( const Type &elem ) const {
        return( WCSkipNonTempBase::base_find( &elem ) );
    };

    // given a node_ptr (which points to the forward pointers in a node),
    // return a pointer to the whole node (WCSkipListNode<Type>)
    // this WILL NOT WORK if sizeof( char ) != 1
    static inline WCSkipListNode<Type> *base_whole_node( node_ptr node_ptrs ) {
        return( (NodeType *)( (char *)node_ptrs
                            - offsetof( NodeType, ptrs ) ) );
    };

    inline node_ptr base_insert( const Type &elem ) {
        return( WCSkipNonTempBase::base_insert( &elem ) );
    }
        
    // insert a copy of the data contained in node
    virtual int base_insert_copy( node_ptr node ) {
        return( base_insert( base_whole_node( node )->data ) != 0 );
    };

    inline node_ptr base_remove_but_not_delete( const Type &elem
                                              , int &num_ptrs ) {
        return( WCSkipNonTempBase::base_remove_but_not_delete( &elem
                                                             , num_ptrs ) );
    };

    WCbool base_val_find( const Type &search, Type &return_val ) const;

    // Create a new node containing elem, and with (level_less_1 + 1)
    // forward pointers.  Uses the user_allocator function if provided.
    virtual node_ptr base_new_node( TTypePtr elem, unsigned level_less_1 );

    // Delete a node, using either delete or the user deallocator function.
    // If there a user deallocator function, then level_less_1 is correct.
    virtual void base_delete_node( node_ptr node, unsigned level_less_1 );

public:
    inline WCSkipListBase( unsigned prob, unsigned max_ptrs
                         , WCbool duplicates = FALSE )
              : WCSkipNonTempBase( prob, max_ptrs, duplicates ) {};

    inline WCSkipListBase( unsigned prob, unsigned max_ptrs
                         , void * (*user_alloc)( size_t )
                         , void (*user_dealloc)( void *, size_t )
                         , WCbool duplicates = FALSE )
              : WCSkipNonTempBase( prob, max_ptrs, user_alloc, user_dealloc
                                 , duplicates ) {};

    // clear can not be called by WCSkipNonTempBase, since it calls the
    // funtion base_delete_node, which is pure virtual in WCSkipNonTempBase's
    // destructor.
    virtual ~WCSkipListBase() {
        if( num_entries != 0 ) {
            base_throw_not_empty();
        };
        clear();
    };

    inline WCbool contains( const Type &elem ) const {
        return( base_find( elem ) != 0 );
    };

    inline unsigned entries() const {
        return( num_entries );
    };

    void forAll( void(*)( Type, void * ), void * ) const;

    inline WCbool insert( const Type &elem ) {
        return( base_insert( elem ) != 0 );
    };

    inline WCbool isEmpty() const {
        return( num_entries == 0 );
    };

    inline WCbool remove( const Type & elem ) {
        return( WCSkipNonTempBase::remove( &elem ) );
    };

    inline int operator==( const WCSkipListBase &rhs ) const {
        return( this == &rhs );
    };

    friend class WCSkipListIterBase;
};
    


// if dealloc_fn == 0, base_delete_node is assumed to ignore level_less_1
template<class Type>
void WCSkipListBase<Type>::base_delete_node( node_ptr node
                                           , unsigned level_less_1 ) {
    if( node ) {
        NodeType *whole_node = base_whole_node( node );
        whole_node->~NodeType();
        if( dealloc_fn ) {
            size_t size = WCValSkipListItemSize( Type, level_less_1 + 1 );
            dealloc_fn( whole_node, size );
        } else {
            delete [] (char *)whole_node;
        }
    }
};


template<class Type>
WCSkipListPtrs *WCSkipListBase<Type>::base_new_node( TTypePtr elem
                                            , unsigned level_less_1 ) {
    NodeType *new_node;
    size_t size = WCValSkipListItemSize( Type, level_less_1 + 1 );

    // get raw memory
    if( alloc_fn ) {
        new_node = (NodeType *)alloc_fn( size );
    } else {
        new_node = (NodeType *)new char[ size ];
    }
    if( new_node ) {
        // call WCSkipListNode's constructor with the raw chunk of memory
        new( new_node ) NodeType( *(const Type *)elem );
        return( &new_node->ptrs );
    } else {
        return( 0 );
    }
};


template<class Type>
WCbool WCSkipListBase<Type>::base_val_find( const Type &search
                                          , Type &return_val ) const {
    node_ptr found_node = base_find( search );
    if( found_node ) {
        return_val = base_whole_node( found_node )->data;
        return( TRUE );
    } else {
        return( FALSE );
    }
}


template<class Type>
void WCSkipListBase<Type>::forAll( register void(*user_fn)( Type, void * )
                                 , void * data) const {
    register node_ptr curr;

    curr = header->forward[ 0 ];
    while ( curr != 0 ) {
        user_fn( base_whole_node( curr )->data, data );
        curr = curr->forward[ 0 ];
    }
};



//
// WCSkipListDuplicatesBase provides skip list functionality for
// WCValSkipList and WCPtrSkipList where duplicates are allowed
//

template<class Type>
class WCSkipListDuplicatesBase : public WCSkipListBase<Type> {
public:
    inline WCSkipListDuplicatesBase( unsigned prob, unsigned max_ptrs
                         ) : WCSkipListBase( prob, max_ptrs, TRUE ) {};

    inline WCSkipListDuplicatesBase( unsigned prob, unsigned max_ptrs
                                   , void * (*user_alloc)( size_t )
                                   , void (*user_dealloc)( void *, size_t )
                         ) : WCSkipListBase( prob, max_ptrs, user_alloc
                                           , user_dealloc, TRUE ) {};

    inline ~WCSkipListDuplicatesBase() {};

    unsigned occurrencesOf( const Type &elem ) const {
        return( base_occurrencesOf( &elem ) );
    };

    inline unsigned removeAll( const Type &elem ) {
        return( base_removeAll( &elem ) );
    };
};


//
// WCPtrSkipListBase provides the skip list interface for pointers.
//
// This is an abstract class to prevent objects of this type being created.
//
// Type is the type pointed to, and SkipListBase is either
// WCSkipListDuplicatesBase<void *> or WCSkipListBase<void *>.
//

template<class Type, class SkipListBase >
class WCPtrSkipListBase : public SkipListBase {
protected:
    // the pointers stored in the skip list by SkipListBase
    typedef void *StoredPtr;
    // the real type of the pointers
    typedef Type *TypePtr;
    // the user function passed to the forAll member function is passed
    // to SkipListBase::forAll using this cast type
    typedef void (*forAll_fn)( StoredPtr, void * );

    // define equivalence and less than based on the == and < operator of
    // the object pointed to
    virtual int base_equiv( node_ptr elem1, TTypePtr elem2 ) const {
        return( *(const Type *)base_whole_node( elem1 )->data
                == **(const Type * *)elem2 );
    };
    virtual int base_less( node_ptr lhs, TTypePtr rhs ) const {
        return( *(const Type *)base_whole_node( lhs )->data
                < **(const Type * *)rhs );
    };

public:
    inline WCPtrSkipListBase( unsigned prob, unsigned max_ptrs )
              : SkipListBase( prob, max_ptrs ) {};

    inline WCPtrSkipListBase( unsigned prob, unsigned max_ptrs
                            , void * (*user_alloc)( size_t )
                            , void (*user_dealloc)( void *, size_t ) )
              : SkipListBase( prob, max_ptrs, user_alloc, user_dealloc ) {};

    inline virtual ~WCPtrSkipListBase() = 0;

    void clearAndDestroy();

    inline WCbool contains( const Type *elem ) const {
        return( SkipListBase::contains( (const TypePtr)elem ) );
    };

    Type *find( const Type *elem ) const;

    inline void forAll( void(*fn)( Type *, void * ), void * data ) const {
        SkipListBase::forAll( (forAll_fn)fn, data );
    };

    inline WCbool insert( Type *elem ) {
        return( SkipListBase::insert( (const TypePtr)elem ) );
    };

    Type *remove( const Type *elem );
};
    

template<class Type, class SkipListBase>
WCPtrSkipListBase<Type, SkipListBase>::~WCPtrSkipListBase() {};


template<class Type, class SkipListBase >
void WCPtrSkipListBase<Type, SkipListBase>::clearAndDestroy() {
    register node_ptr curr;

    curr = header->forward[ 0 ];
    while ( curr != 0 ) {
        delete( (Type *)base_whole_node( curr )->data );
        curr = curr->forward[ 0 ];
    }
    clear();
};


template<class Type, class SkipListBase >
Type *WCPtrSkipListBase<Type, SkipListBase>::find( const Type *elem ) const {
    node_ptr found_node = base_find( (const TypePtr)elem );
    if( found_node ) {
        return( (Type *)base_whole_node( found_node )->data );
    } else {
        return( 0 );
    }
};


template<class Type, class SkipListBase>
Type *WCPtrSkipListBase<Type, SkipListBase>::remove( const Type *elem ) {
    int num_ptrs_in_node;

    node_ptr node = base_remove_but_not_delete( (const TypePtr)elem
                                         , num_ptrs_in_node );
    if( node ) {
        Type *ret_ptr = (Type *)base_whole_node( node )->data;
        base_delete_node( node, num_ptrs_in_node );
        return( ret_ptr );
    } else {
        return( 0 );
    }
}




#define _WCSBASE_H_INCLUDED
#endif
