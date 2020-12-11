//
//  streambu.h  Stream buffer
//
//  Copyright by WATCOM International Corp. 1988-1996.  All rights reserved.
//
#ifndef _STREAMBUF_H_INCLUDED

#ifndef __cplusplus
#error streambu.h is for use with C++
#endif

#ifndef _IOSTREAM_H_INCLUDED
#error streambu.h should only be included by iostream.h
#endif

#include <stddef.h>
#include <string.h>

// For multi-thread support.
#ifndef __lock_it

class __lock;

#ifdef __SW_BM
class __get_lock {
public:
    __get_lock( __lock * );
    ~__get_lock();
private:
    __lock *__lk;
};
#define __lock_it( __l ) __get_lock __lock_name( __LINE__ )( __l )
#define __lock_name( __ln ) __lock_glue( __lock__, __ln )
#define __lock_glue( __pre, __lin ) __pre ## __lin
#else 
#define __lock_it( __l )
#endif
#endif

// **************************** STREAMBUF ************************************
#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif
class streambuf {
public:
    int  in_avail() const;
    int  out_waiting() const;
    int  snextc();
    int  sgetn( char *__buf, int __len );
    int  speekc();
    int  sgetc();
    int  sgetchar();
    int  sbumpc();
    void stossc();
    int  sputbackc( char __c );
    int  sputc( int __c );
    int  sputn( char const *__buf, int __len );
    void dbp();

    virtual int        do_sgetn( char *__buf, int __len );
    virtual int        do_sputn( char const *__buf, int __len );
    virtual int        pbackfail( int __ignored );
    virtual int        overflow( int = EOF ) = 0;
    virtual int        underflow() = 0;
    virtual streambuf *setbuf( char *__buf, int __len );
    virtual streampos  seekoff( streamoff     __ignored1,
                                ios::seekdir  __ignored2,
                                ios::openmode __ignored3 = ios::in | ios::out );
    virtual streampos  seekpos( streampos     __position,
                                ios::openmode __mode = ios::in | ios::out );
    virtual int        sync();

    __lock *__b_lock;       // streambuf data member operations

protected:
    streambuf();
    streambuf( char *__buf, int __len );
    virtual ~streambuf();

    int   allocate();
    char *base() const;
    char *ebuf() const;
    int   blen() const;
    void  setb( char *__buf, char *__endbuf, int __autodelete = 0 );
    char *eback() const;
    char *gptr() const;
    char *egptr() const;
    void  gbump( streamoff __offset );
    void  setg( char *__eback, char *__gptr, char *__egptr );
    char *pbase() const;
    char *pptr() const;
    char *epptr() const;
    void  pbump( streamoff __offset );
    void  setp( char *__pptr, char *__epptr );
    int   unbuffered( int __unbuffered );
    int   unbuffered() const;

    virtual int doallocate();

private:
    // Declared but not defined, to prevent copying a streambuf.
    streambuf( streambuf & );
    void operator = ( streambuf & );

    char *__reserve_base;
    char *__reserve_end;
    char *__get_base;
    char *__get_end;
    char *__get_ptr;
    char *__put_base;
    char *__put_end;
    char *__put_ptr;
    unsigned  __unbuffered_state : 1;
    unsigned  __delete_reserve   : 1;
};
#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

// *********************** Reserve area inline functions *********************

inline char *streambuf::base() const {
    return( __reserve_base );
}

inline char *streambuf::ebuf() const {
    return( __reserve_end );
}

inline int streambuf::blen() const {
    __lock_it( __b_lock );
    return( (int)(__reserve_end - __reserve_base) );
}

inline int streambuf::allocate() {
    __lock_it( __b_lock );
    return( (base() != NULL || unbuffered()) ? __NOT_EOF
                                             : doallocate() );
}

inline int streambuf::unbuffered() const {
    return( __unbuffered_state );
}

inline int streambuf::unbuffered( int __unbuffered ) {
    __lock_it( __b_lock );
    int __old_unbuffered = __unbuffered_state;
    __unbuffered_state   = (char)(__unbuffered ? 1 : 0);
    return( __old_unbuffered );
}

// *********************** Get area inline functions *************************

inline char * streambuf::eback() const {
    return( __get_base );
}

inline char * streambuf::gptr() const {
    return( __get_ptr );
}

inline char * streambuf::egptr() const {
    return( __get_end );
}

inline void streambuf::gbump( streamoff __offset ) {
    __lock_it( __b_lock );
    __get_ptr += __offset;
}

inline void streambuf::setg( char *__eback, char *__gptr, char *__egptr ) {
    __lock_it( __b_lock );
    __get_base = __eback;
    __get_ptr  = __gptr;
    __get_end  = __egptr;
}

// *********************** Put area inline functions *************************

inline char * streambuf::pbase() const {
    return( __put_base );
}

inline char * streambuf::pptr() const {
    return( __put_ptr );
}

inline char * streambuf::epptr() const {
    return( __put_end );
}

inline void streambuf::pbump( streamoff __offset ) {
    __lock_it( __b_lock );
    __put_ptr += __offset;
}

inline void streambuf::setp( char *__pptr, char *__epptr ) {
    __lock_it( __b_lock );
    __put_base = __pptr;
    __put_ptr  = __pptr;
    __put_end  = __epptr;
}

// *********************** Inline input functions ****************************

inline int streambuf::in_avail() const {
    __lock_it( __b_lock );
    return( (int)(__get_end - __get_ptr) );
}

inline int streambuf::sgetchar() {
    __lock_it( __b_lock );
    return( (__get_ptr >= __get_end) && (underflow() == EOF) ? EOF
                                                             : *__get_ptr++ );
}

inline int streambuf::sbumpc() {
    return( sgetchar() );
}

inline int streambuf::snextc() {
    __lock_it( __b_lock );
    return( (__get_ptr) && (++__get_ptr < __get_end) ? *__get_ptr
                                                     : underflow() );
}

inline int streambuf::speekc() {
    __lock_it( __b_lock );
    return( (__get_ptr < __get_end) ? *__get_ptr
                                    : underflow() );
}

inline int streambuf::sgetc() {
    return( speekc() );
}

inline int streambuf::sgetn( char *__buf, int __len ) {
    __lock_it( __b_lock );
    if( __len < (int)(__get_end - __get_ptr) ) {
        ::memcpy( __buf, __get_ptr, __len );
        gbump( __len );
        return( __len );
    }
    return( do_sgetn( __buf, __len ) );
}

inline void streambuf::stossc() {
    __lock_it( __b_lock );
    if( (__get_ptr < __get_end) || (underflow() != EOF) ) {
        ++__get_ptr;
    }
}

// *********************** Inline output functions ***************************

inline int streambuf::out_waiting() const {
    __lock_it( __b_lock );
    return( (int)(__put_ptr - __put_base) );
}

inline int streambuf::sputbackc( char __c ) {
    __lock_it( __b_lock );
    return( (__get_ptr > __get_base) ? (*--__get_ptr = __c)
                                     : pbackfail( __c ) );
}

inline int streambuf::sputc( int __c ) {
    __lock_it( __b_lock );
    return( (__put_ptr >= __put_end) ? overflow( __c )
                                     : (*__put_ptr++ = (char)__c) );
}

inline int streambuf::sputn( char const *__buf, int __len ) {
    __lock_it( __b_lock );
    if( __len < (int)(__put_end - __put_ptr) ) {
        ::memcpy( __put_ptr, __buf, __len );
        pbump( __len );
        return( __len );
    }
    return( do_sputn( __buf, __len ) );
}

#define _STREAMBUF_H_INCLUDED
#endif
