/*
 *	PtMenuBar.h
 *		Header file for the PtMenu widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_MENUBAR_H_INCLUDED
#define __PT_MENUBAR_H_INCLUDED

#ifndef __PT_WINDOW_H_INCLUDED 
#include <photon/PtGroup.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtMenu public
 */

extern PtWidgetClassRef_t *PtMenuBar;

 
/* Resources */
#define Pt_ARG_MENUBAR_FLAGS			Pt_RESOURCE( 37, 0 )

/* PtMenuBar Flag */

#define Pt_MENUBAR_LAST_R_ALIGNED	0x0001
#define Pt_MENUBAR_MENU_OPEN		0x8000

/*
 * PtMenuBar private
 */

/* Widget structure */

typedef struct Pt_menubar_widget {
	PtGroupWidget_t				group;
	short						flags;
	PtWidget_t					*mbutton;
} PtMenuBarWidget_t;

/* Widget union */
typedef union Pt_menubar_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtGroupWidget_t				group;
	PtMenuBarWidget_t			menubar;
} PtMenuBarUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
