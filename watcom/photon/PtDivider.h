/*
 *	PtDivider.h
 *		Divider file for the PtDivider widget class
 *
 *  Copyright by QNX Software Systems Limited 1996. All rights reserved.
 */
#ifndef __PT_DIVIDER_H_INCLUDED
#define __PT_DIVIDER_H_INCLUDED

#ifndef __PT_GROUP_H_INCLUDED
 #include <photon/PtGroup.h>
#endif

#ifndef __PT_COMPOUND_H_INCLUDED
 #include <photon/PtCompound.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtDivider public
 */

extern PtWidgetClassRef_t *const PtDivider;

/* Resources */
#define Pt_ARG_DIVIDER_FLAGS		Pt_RESOURCE( 44,  1 )
#define Pt_ARG_DIVIDER_SIZES		Pt_RESOURCE( 44,  2 )
#define Pt_ARG_DIVIDER_OFFSET		Pt_RESOURCE( 44,  4 )
#define Pt_ARG_BANDWIDTH_THRESHOLD	Pt_RESOURCE(  2, 17 )
#define Pt_CB_DIVIDER_DRAG			Pt_RESOURCE( 44,  3 )


/* Callback subtypes -- equal to Ph_EV_DRAG event subtypes */
#define Ph_EV_DRAG_INIT				0
#define Ph_EV_DRAG_MOVE				1
#define Ph_EV_DRAG_COMPLETE			2
#define Ph_EV_DRAG_KEY_EVENT		3
#define Ph_EV_DRAG_MOTION_EVENT		4
#define Ph_EV_DRAG_BOUNDARY			5
#define Ph_EV_DRAG_START			6

/* One more callback subtype */
#define Pt_CB_DIVIDER_SETRESOURCES	9

/* Pt_ARG_DIVIDER_FLAGS values */
#define Pt_DIVIDER_NORESIZE			0x0001
#define Pt_DIVIDER_RESIZE_BOTH		0x0002
#define Pt_DIVIDER_INVISIBLE		0x0004
#define Pt_DIVIDER_CASCADE			0x0008 // Not supported yet

/* Pt_ARG_DIVIDER_SIZES structure */
typedef struct Pt_divider_sizes {
	short from, to;
	}
		PtDividerSizes_t;

/* Callback structure */
typedef struct Pt_divider_callback {
	PtWidget_t *left, *right;
	int moved, resized;
	PtDividerSizes_t const *sizes;
	int nsizes, index;
	}
		PtDividerCallback_t;



/* Widget structure */

typedef struct Pt_divider_widget {
	PtCompoundWidget_t	cmpnd;
	PtWidget_t *group;
	unsigned short nchildren;
	unsigned short flags;
	PtDividerSizes_t *sizes;
	short initpos, initsize, offset, marg, hlen, index;
	PtWidget_t *left, *right, *handle;
	unsigned threshold;
	PtCallbackList_t *drag;
	}
		PtDividerWidget_t;

/* Widget union */
typedef union Pt_header_union {
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtContainerWidget_t		cntnr;
	PtCompoundWidget_t		cmpnd;
	PtDividerWidget_t		dvdr;
	}
		PtDividerUnion_t;


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
