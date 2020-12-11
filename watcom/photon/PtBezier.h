/*
 *	PtBezier.h
 *		Header file for the PtBezier widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_BEZIER_H_INCLUDED
#define __PT_BEZIER_H_INCLUDED

#ifndef __PT_GRAPHIC_H_INCLUDED
 #include <photon/PtGraphic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtBezier public
 */

extern PtWidgetClassRef_t *PtBezier;

/* Resources */
#define Pt_ARG_BEZIER_FLAGS			Pt_RESOURCE( 42, 1 )


/*
 * PtBezier private
 */

/* Widget structure */
typedef struct Pt_bezier_widget {
	PtGraphicWidget_t			graphic;
	ushort_t					flags;
	short						reserved;
} PtBezierWidget_t;

/* Widget union */
typedef union Pt_bezier_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtGraphicWidget_t			graphic;
	PtBezierWidget_t			bezier;
} PtBezierUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
