/*
 *	PtPane.h
 *		Header file for the PtPane widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_PANE_H_INCLUDED
#define __PT_PANE_H_INCLUDED

#ifndef __PT_CONTAINER_H_INCLUDED
 #include <photon/PtContainer.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtPane public
 */

extern PtWidgetClassRef_t *PtPane;

/* Pane flags */

/*** OLD FLAG DEFS ***/
#define Pt_PANE_XUL_REL					0x0001
#define Pt_PANE_XLR_REL					0x0002
#define Pt_PANE_YUL_REL					0x0004
#define Pt_PANE_YLR_REL					0x0008

#define Pt_PANE_XUL_ANCHOR_RIGHT		0x0010
#define Pt_PANE_XLR_ANCHOR_RIGHT		0x0020
#define Pt_PANE_YUL_ANCHOR_BOTTOM		0x0040
#define Pt_PANE_YLR_ANCHOR_BOTTOM		0x0080

/* Resources */
#define Pt_ARG_PANE_FLAGS				Pt_RESOURCE( 12, 0 )
#define Pt_ARG_PANE_RECT				Pt_RESOURCE( 12, 1 )


/*
 * PtPane private
 */

/* Widget structure */
typedef struct Pt_pane_widget {
	PtContainerWidget_t			container;
	ulong_t						flags;
	PhRect_t					rect;
} PtPaneWidget_t;

/* Widget union */
typedef union Pt_pane_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtPaneWidget_t				pane;
} PtPaneUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
