/*
 *	PtMenuButton.h
 *		Header file for the PtMenuButton widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_MENUBUTTON_H_INCLUDED
#define __PT_MENUBUTTON_H_INCLUDED

#include <photon/PtCompound.h>

#include "PtMenuLabel.h"

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtMenuButton public
 */

extern PtWidgetClassRef_t *PtMenuButton;

/* Resources */

/*
 * PtMenuButton private
 */

/* Widget structure */
typedef struct Pt_menu_button_widget {
	PtCompoundWidget_t		compound;
	PtWidget_t				*mlabel;
	PhArea_t				area;
} PtMenuButtonWidget_t;

/* Widget union */
typedef union Pt_menu_button_union {
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtContainerWidget_t		container;
	PtCompoundWidget_t		compound;
	PtMenuButtonWidget_t	mbutton;
} PtMenuButtonUnion_t;


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
