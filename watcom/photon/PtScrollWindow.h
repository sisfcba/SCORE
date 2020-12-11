
/*
 *  PtScrollWindow.h
 *      Header file for the PtScrollWindow widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_SCROLLWINDOW_H_INCLUDED
#define __PT_SCROLLWINDOW_H_INCLUDED

#ifndef __PT_COMPOUND_H_INCLUDED
 #include <photon/PtCompound.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtScrollWindow public
 */

extern PtWidgetClassRef_t *PtScrollWindow;

/* Resources */
// NONE

/*
 * PtScrollWindow private
 */

/* Widget structure */
typedef struct Pt_scrollwindow{
	PtCompoundWidget_t	compound;
	PtWidget_t		*window;
	PtWidget_t		*scroll_area;
} PtScrollWindowWidget_t;

/* Widget union */
typedef struct Pt_scrollwindow_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtCompoundWidget_t			compound;
	PtScrollWindowWidget_t		scrollwindow;
} PtScrollWindowUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
