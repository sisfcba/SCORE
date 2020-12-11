/*
 *	PgRamScreen.h	
 *		Manifests and data structures for the PgRS-lib
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PH_GLIB_RAM_SCREEN_H_INCLUDED
#define __PH_GLIB_RAM_SCREEN_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#ifndef __PH_GLIB_H_INCLUDED
#include <photon/Pg.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" 
{
#endif

#define	Pgrs_RelParent			0x0000
#define	Pgrs_RelInFront			0x0001
#define	Pgrs_RelBehind			0x0002

#define	PgrsI_CreatedShmem		0x0001

typedef struct {
	ushort_t		flags;
	ushort_t		Iflags;
	PhRid_t			rid;
	PhRid_t			relation;
	pid_t			driver_pid;
	pid_t			notify_proxy;
	PhPoint_t		size;
	PhPoint_t		origin;
	short			bytes_per_line;
	short			bits_per_pixel;
	short			image_type;
	short			spare;
	char			*ibuffer;
	PgColor_t		*pbuffer;
	char			ShmemName[_Pg_MAX_SHMEM_NAME_LEN];
} PgRamScreenCtrlStruct;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif /* __PH_GLIB_RAM_SCREEN_H_INCLUDED */
