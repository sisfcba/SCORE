/*
 *	PtScrollbar.h
 *		Header file for the PtScrollbar widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_SCROLLBAR_H_INCLUDED
#define __PT_SCROLLBAR_H_INCLUDED

#ifndef __PT_BASIC_H_INCLUDED
 #include <photon/PtBasic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtScrollbar public
 */

extern PtWidgetClassRef_t *PtScrollbar;

/* Resources */
#define Pt_ARG_DIRECTION			Pt_RESOURCE( 29, 0 )
#define Pt_ARG_INCREMENT			Pt_RESOURCE( 29, 1 )
#define Pt_ARG_MINIMUM				Pt_RESOURCE( 29, 2 )
#define Pt_ARG_MAXIMUM				Pt_RESOURCE( 29, 3 )
#define Pt_ARG_ORIENTATION			Pt_RESOURCE( 29, 4 )
#define Pt_ARG_PAGE_INCREMENT		Pt_RESOURCE( 29, 5 )
#define Pt_ARG_SHOW_ARROWS			Pt_RESOURCE( 29, 6 )
#define Pt_ARG_SLIDER_SIZE			Pt_RESOURCE( 29, 7 )
#define Pt_ARG_SCROLL_POSITION		Pt_RESOURCE( 29, 8 )
#define Pt_ARG_SCROLLBAR_FLAGS		Pt_RESOURCE( 29, 9 )
#define Pt_ARG_MIN_SLIDER_SIZE		Pt_RESOURCE( 29, 11 )

#define Pt_CB_SCROLL_MOVE			Pt_RESOURCE( 29, 10 )

/* Possible resource values */
#define Pt_VERTICAL					0
#define Pt_HORIZONTAL				1

/* Possible directions */
#define Pt_MAX_ON_TOP				0
#define Pt_MAX_ON_LEFT				0
#define Pt_MAX_ON_BOTTOM			1
#define Pt_MAX_ON_RIGHT				1

/* Scrollbar flag bits */
#define Pt_SCROLLBAR_HORIZONTAL		0x0001
#define Pt_SCROLLBAR_SHOW_ARROWS	0x0002
#define Pt_SCROLLBAR_INVERTED		0x0004
#define Pt_SCROLLBAR_FOCUSED		0x0080 
#define Pt_SCROLLBAR_NOTIFY_ONLY	0x0008

/* Callback structure */
typedef struct Pt_scrollbar_callback {
	unsigned	action;
	int			position;
} PtScrollbarCallback_t;

/* Callback actions */
#define Pt_SCROLL_DECREMENT			1
#define Pt_SCROLL_INCREMENT			2
#define Pt_SCROLL_PAGE_INCREMENT	3
#define Pt_SCROLL_PAGE_DECREMENT	4
#define Pt_SCROLL_TO_MAX			5
#define Pt_SCROLL_TO_MIN			6
#define Pt_SCROLL_DRAGGED			7
#define Pt_SCROLL_RELEASED			8
#define Pt_SCROLL_SET				9


/*
 * PtScrollbar private
 */

/* Widget structure */
typedef struct Pt_scrollbar_widget {
	PtBasicWidget_t				basic;
	ushort_t					flags;
	ushort_t					min_slider_size;
	int							increment;
	int							min;
	int							max;
	int							page_increment;
	int							slider_size;
	int							slider_height;
	int							position;
	PtCallbackList_t			*moved;
	int							saved_slider_size;
	short						inp_grp;
	long						band_threshold;
} PtScrollbarWidget_t;

/* Widget union */
typedef union Pt_scrollbar_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtScrollbarWidget_t			scrollbar;
} PtScrollbarUnion_t;

/* Scrollbar flag bit positions */
#define Pt_SCROLL_HORIZONTAL		0
#define Pt_SCROLL_SHOW_ARROWS		1
#define Pt_SCROLL_INVERTED			2

#define Pt_SCROLL_SLIDER_PRESSED	0x8000
#define Pt_SCROLL_INCREMENT_PRESSED	0x4000
#define Pt_SCROLL_DECREMENT_PRESSED	0x2000
#define Pt_SCROLL_RESTART_DRAG		0x1000
#define Pt_SCROLL_PRESSED_MASK		0xe000


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
