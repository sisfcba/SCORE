/*
 *	PtRegion.h
 **		Header file for the PtRegion widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_REGION_H_INCLUDED
#define __PT_REGION_H_INCLUDED

#ifndef __PT_CONTAINER_H_INCLUDED
 #include <photon/PtContainer.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtRegion public
 */

extern PtWidgetClassRef_t *PtRegion;

/* Resources */
#define Pt_ARG_REGION_CURSOR			Pt_RESOURCE( 1, 2 )
#define Pt_ARG_REGION_CURSOR_COLOR		Pt_RESOURCE( 1, 3 )
// depricated... use Pt_ARG_CURSOR_TYPE
//				 and Pt_ARG_CURSOR_COLOR
#define Pt_ARG_REGION_FIELDS			Pt_RESOURCE( 15, 2 )
#define Pt_ARG_REGION_FLAGS				Pt_RESOURCE( 15, 3 )
#define Pt_ARG_REGION_HANDLE			Pt_RESOURCE( 15, 4 )
#define Pt_ARG_REGION_OPAQUE			Pt_RESOURCE( 15, 5 )
#define Pt_ARG_REGION_OWNER				Pt_RESOURCE( 15, 6 )
#define Pt_ARG_REGION_PARENT			Pt_RESOURCE( 15, 7 )
#define Pt_ARG_REGION_SENSE				Pt_RESOURCE( 15, 8 )
#define Pt_ARG_REGION_DATA				Pt_RESOURCE( 15, 9 )
#define Pt_ARG_REGION_INFRONT			Pt_RESOURCE( 15, 10 )
#define Pt_ARG_REGION_INPUT_GROUP		Pt_RESOURCE( 15, 11 )


/*
 * PtRegion private
 */

/* Widget structure */
typedef struct Pt_region_widget {
	PtContainerWidget_t			container;
	PhRid_t						parent;
	PhConnectId_t				owner;
	#if !defined(__QNXNTO__)
		short					reserved1;
	#endif
	ulong_t						handle;
	ulong_t						fields;
	ulong_t						flags;
	ulong_t						sense;
	ulong_t						opaque;
	PhRegionDataHdr_t			*reg_data;
	PhRid_t						infront;
	ushort_t					inputgrp;
	#if defined(__QNXNTO__)
		short					reserved;
	#else
		char					reserved;
	#endif
} PtRegionWidget_t;

/* Widget union */
typedef union Pt_region_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtRegionWidget_t			region;
} PtRegionUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
