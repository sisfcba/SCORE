/*
 *	PtPixel.h
 *		Header file for the PtPixel widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_PIXEL_H_INCLUDED
#define __PT_PIXEL_H_INCLUDED

#ifndef __PT_GRAPHIC_H_INCLUDED
 #include <photon/PtGraphic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtPixel public
 */

extern PtWidgetClassRef_t *PtPixel;

/* Resources */

/*
 * PtPixel private
 */

/* Widget structure */
typedef struct Pt_pixel_widget {
	PtGraphicWidget_t			graphic;
} PtPixelWidget_t;

/* Widget union */
typedef union Pt_pixel_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtGraphicWidget_t			graphic;
	PtPixelWidget_t				pixel;
} PtPixelUnion_t;


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
