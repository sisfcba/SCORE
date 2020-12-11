/*
 *	PtEllipse.h
 *		Header file for the PtEllipse widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_ELLIPSE_H_INCLUDED
#define __PT_ELLIPSE_H_INCLUDED

#ifndef __PT_GRAPHIC_H_INCLUDED
 #include <photon/PtGraphic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtEllipse public
 */

extern PtWidgetClassRef_t *PtEllipse;


/*
 * PtEllipse private
 */

/* Widget structure */
typedef struct Pt_ellipse_widget {
	PtGraphicWidget_t			graphic;
} PtEllipseWidget_t;

/* Widget union */
typedef union Pt_ellipse_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtGraphicWidget_t			graphic;
	PtEllipseWidget_t			ellipse;
} PtEllipseUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
