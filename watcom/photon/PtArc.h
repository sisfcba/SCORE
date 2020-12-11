/*
 *	PtArc.h
 *		Header file for the PtArc widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_ARC_H_INCLUDED
#define __PT_ARC_H_INCLUDED

#ifndef __PT_GRAPHIC_H_INCLUDED
 #include <photon/PtGraphic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtArc public
 */

extern PtWidgetClassRef_t *PtArc;

/* Resources */
#define Pt_ARG_ARC_END					Pt_RESOURCE( 26, 0 )
#define Pt_ARG_ARC_START				Pt_RESOURCE( 26, 1 )
#define Pt_ARG_ARC_TYPE					Pt_RESOURCE( 26, 2 )


#define Pt_ARC_CURVE		Pg_ARC
#define Pt_ARC_PIE			Pg_ARC_PIE
#define Pt_ARC_CHORD		Pg_ARC_CHORD
/*
 * PtArc private
 */

/* Widget structure */
typedef struct Pt_arc_widget {
	PtGraphicWidget_t			graphic;
	ushort_t					start;
	ushort_t					end;
	ushort_t					type;
} PtArcWidget_t;

/* Widget union */
typedef union Pt_arc_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtGraphicWidget_t			graphic;
	PtArcWidget_t				arc;
} PtArcUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
