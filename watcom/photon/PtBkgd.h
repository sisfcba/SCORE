/*
 *	PtBkgd.h
 *		Header file for the PtBkgd widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_BKGD_H_INCLUDED
#define __PT_BKGD_H_INCLUDED

#ifndef __PT_PANE_H_INCLUDED
 #include <photon/PtPane.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtBkgd public
 */

extern PtWidgetClassRef_t *PtBkgd;

/* Resources */
#define Pt_ARG_BKGD_BRT_FROM		Pt_RESOURCE( 14, 0 )
#define Pt_ARG_BKGD_BRT_TO			Pt_RESOURCE( 14, 1 )
#define Pt_ARG_BKGD_HUE_FROM		Pt_RESOURCE( 14, 2 )
#define Pt_ARG_BKGD_HUE_TO			Pt_RESOURCE( 14, 3 )
#define Pt_ARG_BKGD_MIX				Pt_RESOURCE( 14, 4 )
#define Pt_ARG_BKGD_ORIENTATION		Pt_RESOURCE( 14, 5 )
#define Pt_ARG_BKGD_PIXCOLORS		Pt_RESOURCE( 14, 6 )
#define Pt_ARG_BKGD_PIXMAP			Pt_RESOURCE( 14, 7 )
#define Pt_ARG_BKGD_PIX_HEIGHT		Pt_RESOURCE( 14, 8 )
#define Pt_ARG_BKGD_PIX_WIDTH		Pt_RESOURCE( 14, 9 )
#define Pt_ARG_BKGD_SAT_FROM		Pt_RESOURCE( 14, 10 )
#define Pt_ARG_BKGD_SAT_TO			Pt_RESOURCE( 14, 11 )
#define Pt_ARG_BKGD_STEPS			Pt_RESOURCE( 14, 12 )
#define Pt_ARG_BKGD_TILE			Pt_RESOURCE( 14, 13 )
#define Pt_ARG_BKGD_TYPE			Pt_RESOURCE( 14, 14 )
#define Pt_ARG_BKGD_IMAGE			Pt_RESOURCE( 14, 15 )
#define Pt_ARG_BKGD_SPACING			Pt_RESOURCE( 14, 16 )

/* type flags */
#define	Pt_BKGD_HUE					1
#define Pt_BKGD_SATURATION			2
#define Pt_BKGD_BRIGHTNESS			3
#define Pt_BKGD_PIXMAP				4
#define Pt_BKGD_IMAGE				5

/* orientation flags */
#define Pt_BKGD_HORIZONTAL			1
#define Pt_BKGD_VERTICAL			2

/* pixmap tile flags */
#define Pt_BKGD_NONE				0
#define Pt_BKGD_GRID				1
#define Pt_BKGD_ALT					2
#define Pt_BKGD_CENTER				3
#define Pt_BKGD_CENTER_GRID			4

/*
 * PtBkgd private
 */

/* Widget structure */
typedef struct Pt_bkgd_widget {
	PtPaneWidget_t				pane;
	ushort_t					type;

	/* color backgrounds related */
	ushort_t					orientation;
	ushort_t					steps;
	ushort_t					mix;
	ushort_t					hue_from;
	ushort_t					hue_to;
	ushort_t					sat_from;
	ushort_t					sat_to;
	ushort_t					brt_from;
	ushort_t					brt_to;
	PgColor_t					*step_pal;
	PhRect_t					*step_box;

	/* bitmap backgrounds related */
	PgColor_t					*colors;
	char						**data;
	ushort_t					nplanes;
	ushort_t					pix_h;
	ushort_t					pix_w;
	ushort_t					tile;
	ushort_t					spacing;
	PhPoint_t					rep;
	PhPoint_t					pos;
	PhImage_t					*image;
} PtBkgdWidget_t;

/* Widget union */
typedef union Pt_bkgd_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtPaneWidget_t				pane;
	PtBkgdWidget_t				bkgd;
} PtBkgdUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
