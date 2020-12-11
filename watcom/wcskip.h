//
//  wcskip.h    Definitions and implementation for the WATCOM Container Skip
//              List class
//
//  Copyright by WATCOM International Corp. 1988-1996.  All rights reserved.
//

#ifndef _WCSKIP_H_INCLUDED

#ifndef __cplusplus
#error wcskip.h is for use with C++
#endif

//
// Skip Lists are a probabilistic alternative to balanced trees, as
// described in the June 1990 issue of CACM and were invented by
// William Pugh in 1987.
//


#include <wcdefs.h>
#include <wcexcept.h>
#include <wcsbase.h>


//
// WCValSkipList - the skip list value class which allows duplicates
//

template<class Type>
class WCValSkipList : public WCSkipListDuplicatesBase<Type> {
private:
    // define equivalence and less than for the base classes
    // second parameters are really typed (Type *)
    virtual int base_equiv( node_ptr elem1, TTypePtr elem2 ) const {
        return( (const Type)base_whole_node( elem1 )->data
                == *(const Type *)elem2 );
    };

    virtual int base_less( node_ptr lhs, TTypePtr rhs ) const {
        return( (const Type)base_whole_node( lhs )->data
                < *(const Type *)rhs );
    };

public:
    inline WCValSkipList( unsigned prob = WCSKIPLIST_PROB_QUARTER
                        , unsigned max_ptrs = WCDEFAULT_SKIPLIST_MAX_PTRS
                        ) : WCSkipListDuplicatesBase( prob, max_ptrs ) {};

    inline WCValSkipList( unsigned prob, unsigned max_ptrs
                        , void * (*user_alloc)( size_t )
                        , void (*user_dealloc)( void *, size_t )
                        ) : WCSkipListDuplicatesBase( prob, max_ptrs
                                        , user_alloc, user_dealloc ) {};

    inline WCValSkipList( const WCValSkipList &orig )
                 : WCSkipListDuplicatesBase( orig.probability
                                           , orig.max_ptrs_in_node ) {
        base_construct( &orig );
    };

    inline virtual ~WCValSkipList() {};

    inline WCbool find( const Type &search, Type &return_val ) const {
        return( base_val_find( search, return_val ) );
    }

    inline WCValSkipList &operator=( const WCValSkipList &orig ) {
        base_assign( &orig );
        return( *this );
    };
};




//
// WCPtrSkipList - the skip list pointer class which allows duplicates
//

template<class Type>
class WCPtrSkipList
        : public WCPtrSkipListBase<Type,WCSkipListDuplicatesBase<void *> > {
public:
    inline WCPtrSkipList( unsigned prob = WCSKIPLIST_PROB_QUARTER
                        , unsigned max_ptrs = WCDEFAULT_SKIPLIST_MAX_PTRS
                        ) : WCPtrSkipListBase( prob, max_ptrs ) {};

    inline WCPtrSkipList( unsigned prob, unsigned max_ptrs
                        , void * (*user_alloc)( size_t )
                        , void (*user_dealloc)( void *, size_t )
                        ) : WCPtrSkipListBase( prob, max_ptrs
                                             , user_alloc, user_dealloc ) {};

    inline WCPtrSkipList( const WCPtrSkipList &orig )
                         : WCPtrSkipListBase( orig.probability
                                            , orig.max_ptrs_in_node ) {
        base_construct( &orig );
    };

    inline virtual ~WCPtrSkipList() {};
    
    inline unsigned occurrencesOf( const Type *elem ) const {
        return( WCSkipListDuplicatesBase
                        ::occurrencesOf( (const TypePtr) elem ) );
    };

    inline unsigned removeAll( const Type *elem ) {
        return( WCSkipListDuplicatesBase::removeAll( (const TypePtr) elem ) );
    };

    inline WCPtrSkipList &operator=( const WCPtrSkipList &orig ) {
        base_assign( &orig );
        return( *this );
    };
};
    



//
// WCValSkipListSet - the skip list value class which does not allow duplicates
//

template<class Type>
class WCValSkipListSet : public WCSkipListBase<Type> {
private:
    // defines equivalence and less than for the base class
    // second parameters are really typed (Type *)
    virtual int base_equiv( node_ptr elem1, TTypePtr elem2 ) const {
        return( (const Type)base_whole_node( elem1 )->data
                == *(const Type *)elem2 );
    };
    
    virtual int base_less( node_ptr lhs, TTypePtr rhs ) const {
        return( (const Type)base_whole_node( lhs )->data
                < *(const Type *)rhs );
    };

public:
    inline WCValSkipListSet( unsigned prob = WCSKIPLIST_PROB_QUARTER
                           , unsigned max_ptrs = WCDEFAULT_SKIPLIST_MAX_PTRS
                           ) : WCSkipListBase( prob, max_ptrs ) {};

    inline WCValSkipListSet( unsigned prob, unsigned max_ptrs
                           , void * (*user_alloc)( size_t )
                           , void (*user_dealloc)( void *, size_t )
                           ) : WCSkipListBase( prob, max_ptrs
                                        , user_alloc, user_dealloc ) {};

    inline WCValSkipListSet( const WCValSkipListSet &orig )
                         : WCSkipListBase( orig.probability
                                         , orig.max_ptrs_in_node ) {
        base_construct( &orig );
    };

    inline virtual ~WCValSkipListSet() {};

    inline WCbool find( const Type &search, Type &return_val ) const {
        return( base_val_find( search, return_val ) );
    }

    inline WCValSkipListSet &operator=( const WCValSkipListSet &orig ) {
        base_assign( &orig );
        return( *this );
    };
};




//
// WCPtrSkipListSet - the skip list pointer class which does not
// allow duplicates
//

template<class Type>
class WCPtrSkipListSet
        : public WCPtrSkipListBase<Type,WCSkipListBase<void *> > {
public:
    inline WCPtrSkipListSet( unsigned prob = WCSKIPLIST_PROB_QUARTER
                           , unsigned max_ptrs = WCDEFAULT_SKIPLIST_MAX_PTRS
                           ) : WCPtrSkipListBase( prob, max_ptrs ) {};

    inline WCPtrSkipListSet( unsigned prob, unsigned max_ptrs
                           , void * (*user_alloc)( size_t )
                           , void (*user_dealloc)( void *, size_t )
                           ) : WCPtrSkipListBase( prob, max_ptrs
                                             , user_alloc, user_dealloc ) {};

    inline WCPtrSkipListSet( const WCPtrSkipListSet &orig )
                         : WCPtrSkipListBase( orig.probability
                                            , orig.max_ptrs_in_node ) {
        base_construct( &orig );
    };

    inline virtual ~WCPtrSkipListSet() {};
    
    inline WCPtrSkipListSet &operator=( const WCPtrSkipListSet &orig ) {
        base_assign( &orig );
        return( *this );
    };
};




//
// WCValSkipListDict - the skip list value dictionary class.  Key-Value
// pairs are stored in a skip list, and all lookups are base on Key
//

template<class Key, class Value>
class WCValSkipListDict
        : public WCSkipListBase<WCSkipListDictKeyVal<Key, Value> > {
protected:    
    typedef WCSkipListDictKeyVal<Key, Value> KeyVal;
    // for const member functions which modify temp_key_val, but not the
    // skip list
    typedef WCValSkipListDict *const NonConstThis;

    // temp_key_val is used in finds, removes, etc., where only the key is
    // given. it is also used by the operator[] to insert.  The value must
    // remain default initialized
    KeyVal temp_key_val;

    // second parameters are really typed (KeyVal *)
    virtual int base_equiv( node_ptr elem1, TTypePtr elem2 ) const {
        return( (const Key)base_whole_node( elem1 )->data.key
                == ( (const KeyVal *)elem2 )->key );
    };
    
    virtual int base_less( node_ptr lhs, TTypePtr rhs ) const {
        return( (const Key)base_whole_node( lhs )->data.key
                < ( (const KeyVal *)rhs )->key );
    };

public:
    inline WCValSkipListDict( unsigned prob = WCSKIPLIST_PROB_QUARTER
                            , unsigned max_ptrs = WCDEFAULT_SKIPLIST_MAX_PTRS
                            ) : WCSkipListBase( prob, max_ptrs ) {};

    inline WCValSkipListDict( unsigned prob, unsigned max_ptrs
                            , void * (*user_alloc)( size_t )
                            , void (*user_dealloc)( void *, size_t )
                            ) : WCSkipListBase( prob, max_ptrs
                                              , user_alloc, user_dealloc ) {};

    inline WCValSkipListDict( const WCValSkipListDict &orig )
                 : WCSkipListBase( orig.probability, orig.max_ptrs_in_node ) {
        base_construct( &orig );
    };

    inline virtual ~WCValSkipListDict() {};

    inline WCbool contains( const Key &key ) const {
        NonConstThis This = (NonConstThis)this;
        This->temp_key_val.key = key;
        return( base_find( temp_key_val ) != 0 );
    };

    WCbool find( const Key &search, Value &ret_value ) const;

    WCbool findKeyAndValue( const Key &search, Key &ret_key
                          , Value &ret_value ) const;

    void forAll( void(*)( Key, Value, void * ), void * ) const;

    inline WCbool insert( const Key &key, const Value &value ) {
        KeyVal temp( key, value );
        return( WCSkipListBase::insert( temp ) );
    };

    inline WCbool remove( const Key &key ) {
        temp_key_val.key = key;
        return( WCSkipListBase::remove( temp_key_val ) );
    };

    inline WCValSkipListDict &operator=( const WCValSkipListDict &orig ) {
        base_assign( &orig );
        return( *this );
    };

    Value &operator[]( const Key &key );

    const Value &operator[]( const Key &key ) const;
};


template<class Key, class Value>
WCbool WCValSkipListDict<Key, Value>::find( const Key &search
                                         , Value &ret_value ) const {
    NonConstThis This = (NonConstThis)this;
    This->temp_key_val.key = search;
    node_ptr node = base_find( temp_key_val );
    if( node != 0 ) {
        ret_value = base_whole_node( node )->data.value;
        return( TRUE );
    } else {
        return( FALSE );
    }
};


template<class Key, class Value>
WCbool WCValSkipListDict<Key, Value>::findKeyAndValue( const Key &search
                                , Key &ret_key, Value &ret_value ) const {
    NonConstThis This = (NonConstThis)this;
    This->temp_key_val.key = search;
    node_ptr node = base_find( temp_key_val );
    if( node != 0 ) {
        ret_key = base_whole_node( node )->data.key;
        ret_value = base_whole_node( node )->data.value;
        return( TRUE );
    } else {
        return( FALSE );
    }
};


template<class Key, class Value>
void WCValSkipListDict<Key, Value>
                ::forAll( register void(*user_fn)( Key, Value, void * )
                        , void * data) const {
    register node_ptr curr;

    curr = header->forward[ 0 ];
    while ( curr != 0 ) {
        user_fn( base_whole_node( curr )->data.key
               , base_whole_node( curr )->data.value, data );
        curr = curr->forward[ 0 ];
    }
};


template<class Key, class Value>
Value &WCValSkipListDict<Key, Value>::operator[]( const Key &key ) {
    NonConstThis This = (NonConstThis)this;
    This->temp_key_val.key = key;
    node_ptr node = base_find( temp_key_val );
    if( node == 0 ) {
        node = base_insert( temp_key_val );
        if( !node ) {
            // insert failed because allocation failed and out_of_memory
            // exception disabled
            return( *(Value *)0 );
        }
    }
    return( base_whole_node( node )->data.value );
};


template<class Key, class Value>
const Value &WCValSkipListDict<Key, Value>
                ::operator[]( const Key &key ) const {
    NonConstThis This = (NonConstThis)this;
    This->temp_key_val.key = key;
    node_ptr node = base_find( temp_key_val );
    if( node != 0 ) {
        return( base_whole_node( node )->data.value );
    } else {
        base_throw_index_range();
        // find failed, index_range exception off, but must return reference
        return( *(Value *)0 );
    }
};




//
// WCPtrSkipListDict - the skip list value dictionary class.  Key-Value
// pairs are stored in a skip list, and all lookups are base on Key
//

template<class Key, class Value>
class WCPtrSkipListDict
        : public WCValSkipListDict<void *, void *> {
protected:    
    // for const member functions which modify temp_key_val, but not the
    // skip list
    typedef WCPtrSkipListDict *const NonConstThis;
    // the pointer stored by WCValSkipListDict
    typedef void *Stored_Ptr;  
    // the user function passed to the forAll member function is passed
    // to WCValSkipListDict::forAll using this cast type
    typedef void (*_ForAllFnCast)( void *, void *, void * );

    // defines equivalence and less than based on the keys pointed to
    // second parameters are really typed (KeyVal *)
    virtual int base_equiv( node_ptr elem1, TTypePtr elem2 ) const {
        return( *(const Key *)base_whole_node( elem1 )->data.key
                == *(const Key *)( (const KeyVal *)elem2 )->key );
    };
    
    virtual int base_less( node_ptr lhs, TTypePtr rhs ) const {
        return( *(const Key *)base_whole_node( lhs )->data.key
                < *(const Key *)( (const KeyVal *)rhs )->key );
    };

    // for the clearAndDestroy member function
    static void base_destroy( Key *key, Value *value, void * ) {
        delete( key );
        delete( value );
    };

public:
    inline WCPtrSkipListDict( unsigned prob = WCSKIPLIST_PROB_QUARTER
                            , unsigned max_ptrs = WCDEFAULT_SKIPLIST_MAX_PTRS
                            ) : WCValSkipListDict( prob, max_ptrs ) {};

    inline WCPtrSkipListDict( unsigned prob, unsigned max_ptrs
                            , void * (*user_alloc)( size_t )
                            , void (*user_dealloc)( void *, size_t )
                            ) : WCValSkipListDict( prob, max_ptrs
                                              , user_alloc, user_dealloc ) {};

    inline WCPtrSkipListDict( const WCPtrSkipListDict &orig )
             : WCValSkipListDict( orig.probability, orig.max_ptrs_in_node ) {
        base_construct( &orig );
    };

    inline virtual ~WCPtrSkipListDict() {};

    inline void clearAndDestroy() {
        forAll( base_destroy, 0 );
        clear();
    };

    inline WCbool contains( const Key *key ) const {
        return( WCValSkipListDict::contains( (const Stored_Ptr)key ) );
    };

    Value *find( const Key *search ) const;

    Value *findKeyAndValue( const Key *search, Key * &ret_key ) const;

    void forAll( void(*fn)( Key *, Value *, void * ), void * data ) const {
        WCValSkipListDict::forAll( (_ForAllFnCast)fn, data );
    };

    inline WCbool insert( Key *key, Value *value ) {
        return( WCValSkipListDict::insert( (const Stored_Ptr)key
                                         , (const Stored_Ptr)value ) );
    };

    Value* remove( const Key *key );

    inline WCPtrSkipListDict &operator=( const WCPtrSkipListDict &orig ) {
        base_assign( &orig );
        return( *this );
    };

    inline Value * &operator[]( const Key *key ) {
        return( (Value * &)WCValSkipListDict
                                ::operator[]( (const Stored_Ptr)key ) );
    };

    inline Value * const &operator[]( const Key *key ) const {
        return( (Value * const &)WCValSkipListDict
                                ::operator[]( (const Stored_Ptr)key ) );
    };
};


template<class Key, class Value>
Value *WCPtrSkipListDict<Key, Value>::find( const Key *search ) const {
    NonConstThis This = (NonConstThis)this;
    This->temp_key_val.key = (Stored_Ptr)search;
    node_ptr node = base_find( temp_key_val );
    if( node != 0 ) {
        return( (Value *)base_whole_node( node )->data.value );
    } else {
        return( 0 );
    }
};


template<class Key, class Value>
Value *WCPtrSkipListDict<Key, Value>::findKeyAndValue( const Key *search
                                , Key * &ret_key ) const {
    NonConstThis This = (NonConstThis)this;
    This->temp_key_val.key = (Stored_Ptr)search;
    node_ptr node = base_find( temp_key_val );
    if( node != 0 ) {
        ret_key = (Key *)base_whole_node( node )->data.key;
        return( (Value *)base_whole_node( node )->data.value );
    } else {
        return( 0 );
    }
};


template<class Key, class Value>
Value *WCPtrSkipListDict<Key, Value>::remove( const Key *elem ) {
    int num_ptrs_in_node;

    temp_key_val.key = (Stored_Ptr)elem;
    node_ptr node = base_remove_but_not_delete( temp_key_val
                                         , num_ptrs_in_node );
    if( node ) {
        Value *ret_ptr = (Value *)base_whole_node( node )->data.value;
        base_delete_node( node, num_ptrs_in_node );
        return( ret_ptr );
    } else {
        return( 0 );
    }
}


#define _WCSKIP_H_INCLUDED
#endif
