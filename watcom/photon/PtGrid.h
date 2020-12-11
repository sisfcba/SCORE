/*
 *	PtGrid.h
 *		Header file for the PtGrid widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_GRID_H_INCLUDED
#define __PT_GRID_H_INCLUDED

#ifndef __PT_BASIC_H_INCLUDED
 #include <photon/PtBasic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtGrid public
 */

extern PtWidgetClassRef_t *const PtGrid;

/* Resources */
#define Pt_ARG_DASH_LIST				Pt_RESOURCE( 25, 0 )
#define Pt_ARG_LINE_WIDTH				Pt_RESOURCE( 25, 2 )
#define Pt_ARG_LINE_JOIN				Pt_RESOURCE( 25, 3 )
#define Pt_ARG_LINE_CAP					Pt_RESOURCE( 25, 4 )
#define	Pt_ARG_DASH_SCALE				Pt_RESOURCE( 25, 8 )

#define Pt_ARG_GRID_HORIZONTAL			Pt_RESOURCE( 43, 0 )
#define Pt_ARG_GRID_VERTICAL			Pt_RESOURCE( 43, 1 )


/*
 * PtGrid private
 */

/* Widget structure */
typedef struct Pt_grid_widget {
	PtBasicWidget_t		basic;
	PhPoint_t			grid;
	long				line_width;
	unsigned short		line_cap;
	unsigned short		line_join;
	char				*dash_list;
	long				dash_scale;
	unsigned short		dash_len;
	short				reserved;
} PtGridWidget_t;

/* Widget union */
typedef union Pt_grid_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtGridWidget_t				graphic;
} PtGridUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
