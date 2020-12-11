/*
 *	PtRect.h
 *		Header file for the PtRect widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_RECT_H_INCLUDED
#define __PT_RECT_H_INCLUDED

#ifndef __PT_GRAPHIC_H_INCLUDED
 #include <photon/PtGraphic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtRect public
 */

extern PtWidgetClassRef_t *PtRect;

/* Resources */
#define Pt_ARG_RECT_ROUNDNESS		Pt_RESOURCE( 28, 0 )

/*
 * PtRect private
 */

/* Widget structure */
typedef struct Pt_rect_widget {
	PtGraphicWidget_t			graphic;
	ushort_t					roundness;
} PtRectWidget_t;

/* Widget union */
typedef union Pt_rect_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtGraphicWidget_t			graphic;
	PtRectWidget_t				rect;
} PtRectUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
