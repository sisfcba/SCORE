/*
 *	PtPolygon.h
 *		Header file for the PtPolygon widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_POLYGON_H_INCLUDED
#define __PT_POLYGON_H_INCLUDED

#ifndef __PT_GRAPHIC_H_INCLUDED
 #include <photon/PtGraphic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtPolygon public
 */

extern PtWidgetClassRef_t *PtPolygon;

/* Resources */
#define Pt_ARG_POLYGON_FLAGS			Pt_RESOURCE( 27, 1 )


/*
 * PtPolygon private
 */

/* Widget structure */
typedef struct Pt_polygon_widget {
	PtGraphicWidget_t			graphic;
	ushort_t					flags;
	short						reserved;
} PtPolygonWidget_t;

/* Widget union */
typedef union Pt_polygon_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtGraphicWidget_t			graphic;
	PtPolygonWidget_t			polygon;
} PtPolygonUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
