/*
 *	PtGraphic.h
 *		Header file for the PtGraphic widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_GRAPHIC_H_INCLUDED
#define __PT_GRAPHIC_H_INCLUDED

#ifndef __PT_BASIC_H_INCLUDED
 #include <photon/PtBasic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtGraphic public
 */

extern PtWidgetClassRef_t *PtGraphic;

/* Resources */
#define Pt_ARG_DASH_LIST				Pt_RESOURCE( 25, 0 )
#define Pt_ARG_GRAPHIC_FLAGS			Pt_RESOURCE( 25, 1 )
#define Pt_ARG_LINE_WIDTH				Pt_RESOURCE( 25, 2 )
#define Pt_ARG_LINE_JOIN				Pt_RESOURCE( 25, 3 )
#define Pt_ARG_LINE_CAP					Pt_RESOURCE( 25, 4 )
#define Pt_ARG_ORIGIN					Pt_RESOURCE( 25, 5 )
#define Pt_ARG_POINTS					Pt_RESOURCE( 25, 6 )
#define	Pt_ARG_DASH_SCALE				Pt_RESOURCE( 25, 8 )

#define Pt_CB_RESCALE					Pt_RESOURCE( 25, 7 )


/*** Valid flag bits ****/
#define Pt_FLOAT_POS		0x01
#define Pt_FLOAT_ORIGIN		0x02

/*
 * PtGraphic private
 */

/* Widget structure */
typedef struct Pt_graphic_widget {
	PtBasicWidget_t		basic;
	PhPoint_t			origin;
	PhPoint_t			*point_array;
	PtCallbackList_t	*rescale;
	long				line_width;
	ushort_t			line_cap;
	ushort_t			line_join;
	char				*dash_list;
	ushort_t			npoints;
	char				flags;
	char				reserved;
	short				dash_len;
	long				dash_scale;
} PtGraphicWidget_t;

/* Widget union */
typedef union Pt_graphic_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtGraphicWidget_t			graphic;
} PtGraphicUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
