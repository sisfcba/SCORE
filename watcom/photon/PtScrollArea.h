/*
 *	PtScrollArea.h
 *		Header file for the PtScrollArea widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_SCROLL_AREA_H_INCLUDED
#define __PT_SCROLL_AREA_H_INCLUDED

#ifndef __PT_CONTAINER_H_INCLUDED
 #include <photon/PtContainer.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtScrollArea public
 */

extern PtWidgetClassRef_t *PtScrollArea;

/* Resources */
#define Pt_ARG_SCROLL_AREA_INCREMENT_X		Pt_RESOURCE( 13, 0 )
#define Pt_ARG_SCROLL_AREA_INCREMENT_Y		Pt_RESOURCE( 13, 1 )
#define Pt_ARG_SCROLL_AREA_MAX_X			Pt_RESOURCE( 13, 2 )
#define Pt_ARG_SCROLL_AREA_MAX_Y			Pt_RESOURCE( 13, 3 )
#define Pt_ARG_SCROLL_AREA_POS_Y			Pt_RESOURCE( 13, 4 )
#define Pt_ARG_SCROLL_AREA_POS_X			Pt_RESOURCE( 13, 5 )
#define Pt_ARG_SCROLLBAR_X_DISPLAY			Pt_RESOURCE( 13, 6 )
#define Pt_ARG_SCROLLBAR_X_HEIGHT			Pt_RESOURCE( 13, 7 )
#define Pt_ARG_SCROLLBAR_Y_DISPLAY			Pt_RESOURCE( 13, 8 )
#define Pt_ARG_SCROLLBAR_Y_WIDTH			Pt_RESOURCE( 13, 9 )
#define Pt_ARG_SCROLL_AREA_FLAGS			Pt_RESOURCE( 13, 12 )

#define Pt_CB_SCROLLED_X					Pt_RESOURCE( 13, 10 )
#define Pt_CB_SCROLLED_Y					Pt_RESOURCE( 13, 11 )

/*
 * PtScrollArea flags
 */
#define Pt_SCROLL_AREA_IGNORE_KEYS 	0x0001
#define Pt_SCROLL_AREA_TRACK_FOCUS 	0x0002

#define Pt_SCROLL_AREA_RO_FLAGS		0x0000

/*
 * PtScrollArea private 
 */

/* Widget structure */
typedef struct Pt_scroll_area_widget {
	PtContainerWidget_t			container;
	ushort_t					flags;
	ushort_t					max_y;
	ushort_t					pos_y;
	ushort_t					given_y;
	ushort_t					max_x;
	ushort_t					pos_x;
	ushort_t					given_x;
	ushort_t					scrollbar_x_display;
	PtCallbackList_t 			*scrolled_x;
	PtWidget_t					*scrollbar_x;
	ushort_t					scrollbar_y_display;
	PtCallbackList_t 			*scrolled_y;
	PtWidget_t					*scrollbar_y;
	PtWidget_t 					*viewport;
	PtWidget_t					*my_virtual;
	PtWidget_t					*spacer;
	long						reserved;
} PtScrollAreaWidget_t;

// valid DISPLAY values
// Pt_NEVER 	 //default for X scrollbar
// Pt_ALWAYS	 //default for Y scrollbar
// Pt_AS_REQUIRED

/** Private **/
#define Pt_SCROLLAREA_EXTENTING 0x8000

/* Widget union */

typedef union Pt_scroll_area_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtScrollAreaWidget_t		scarea;
} PtScrollAreaUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
