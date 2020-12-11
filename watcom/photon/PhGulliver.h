/*
 *  Copyright by QNX Software Systems Limited 1998. All rights reserved.
 */
#ifndef __PHGULLIVER_H_INCLUDED
#define __PHGULLIVER_H_INCLUDED


#if defined(__BIGENDIAN__)
	#include <gulliver.h>

	#define PhEndianFixLong( ptr )			ENDIAN_SWAP32( ptr )
	#define PhEndianFixShort( ptr )			ENDIAN_SWAP16( ptr )
	extern void PhEndianFixImage( PhImage_t *ptr );
	extern void PhEndianFixImageData( PhImage_t const *ptr );
	extern void PhEndianFixLongArray( unsigned long *ptr, unsigned n );
	extern void PhEndianFixShortArray( unsigned short *ptr, unsigned n );
	extern void PhEndianFixDim( PhDim_t * );
	extern void PhEndianFixPoint( PhPoint_t * );
	extern void PhEndianFixArea( PhArea_t * );
	extern void PhEndianFixRect( PhRect_t * );
	#define PhEndianGetLong( val )			ENDIAN_LE32(val)
	#define PhEndianGetShort( val )			ENDIAN_LE16(val)
	#define PhEndianFixInt( ptr )			(	sizeof(*(ptr)) == sizeof(short) ? (void) PhEndianFixShort(ptr) \
											:	sizeof(*(ptr)) == sizeof(long) ?  (void) PhEndianFixLong(ptr) \
											:	(void)(ptr) )
#elif defined(__LITTLEENDIAN__) || !defined(__QNXNTO__)
	#define PhEndianFixLong( ptr )			( (void)(ptr) )
	#define PhEndianFixShort( ptr )			( (void)(ptr) )
	#define PhEndianFixImage( ptr )			( (void)(ptr) )
	#define PhEndianFixImageData( ptr )		( (void)(ptr) )
	#define PhEndianFixDim( ptr )			( (void)(ptr) )
	#define PhEndianFixPoint( ptr )			( (void)(ptr) )
	#define PhEndianFixArea( ptr )			( (void)(ptr) )
	#define PhEndianFixRect( ptr )			( (void)(ptr) )
	#define PhEndianFixLongArray( ptr, n )	( (void)(ptr), (void)(n) )
	#define PhEndianFixShortArray( ptr, n )	( (void)(ptr), (void)(n) )
	#define PhEndianFixInt( ptr )			( (void)(ptr) )
	#define PhEndianGetLong( val )			( val )
	#define PhEndianGetShort( val )			( val )
#else
	#error ENDIAN Not defined for system
#endif

#define PhEndianFixColorArray	PhEndianFixLongArray
#define PhEndianFixColor		PhEndianFixLong
#define PhEndianGetColor		PhEndianGetLong

#endif
