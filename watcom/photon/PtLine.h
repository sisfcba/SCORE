/*
 *	PtLine.h
 *		Header file for the PtLine widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_LINE_H_INCLUDED
#define __PT_LINE_H_INCLUDED

#ifndef __PT_GRAPHIC_H_INCLUDED
 #include <photon/PtGraphic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtLine public
 */

extern PtWidgetClassRef_t *PtLine;


/*
 * PtLine private
 */

/* Widget structure */
typedef struct Pt_line_widget {
	PtGraphicWidget_t			graphic;
} PtLineWidget_t;

/* Widget union */
typedef union Pt_line_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtGraphicWidget_t			graphic;
	PtLineWidget_t				line;
} PtLineUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
