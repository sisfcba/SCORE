/*
 *	PtDBContainer.h
 *		Header file for the PtDBContainer widget class 
 *
 *	Copyright by QNX Software Systems Limited 1997-2001. All rights reserved
 */

#ifndef _PTDBCONTAINER_INCLUDED
#define _PTDBCONTAINER_INCLUDED
#include <photon/PmT.h>
#include <photon/PtContainer.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

// Public

extern PtWidgetClassRef_t *PtDBContainer;

#define Pt_ARG_DB_IMAGE_TYPE				Pt_RESOURCE( 48, 0 )
#define Pt_ARG_DB_MEMORY_CONTEXT_TYPE		Pt_RESOURCE( 48, 1 )

// Private

// Db Container flags
#define Pt_DB_INLINE_IMAGE 0x00000001

typedef struct pt_db_container
	{
	PtContainerWidget_t	container;
	PmMemoryContext_t *mc;
	PhImage_t	image;
	PhImage_t	def_image;
	int			type;
	int			flags;
	int			spare[4];
	} PtDBContainerWidget_t;

typedef union pt_db_container_union
	{
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtContainerWidget_t		container;
	PtDBContainerWidget_t 	dbcontainer;
	}PtDBContainerUnion_t;
#ifdef __cplusplus
}
#endif

#include <photon/PhPackPop.h>

#endif

