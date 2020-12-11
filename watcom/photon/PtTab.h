/*
 *	PtTab.h
 *		Header file for the PtTab widget class
 *
 *  Copyright by QNX Software Systems Limited 1998. All rights reserved.
 */
#ifndef __PT_TAB_H_INCLUDED
#define __PT_TAB_H_INCLUDED

#ifndef __PT_BUTTON_H_INCLUDED
 #include <photon/PtButton.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtTab public
 */

extern PtWidgetClassRef_t *const PtTab;

/* Resources */
#define	Pt_ARG_TAB_FLAGS		Pt_RESOURCE( 58, 0 )

/* Flags */
#define Pt_TAB_UPSIDE_DOWN		0x1

/*
 * PtTab private
 */

/* Widget structure */
typedef struct Pt_tab_widget {
	PtButtonWidget_t		button;
	unsigned				flags;
} PtTabWidget_t;

/* Widget union */
typedef union Pt_tab_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtLabelWidget_t				label;
	PtButtonWidget_t			button;
	PtTabWidget_t				graphic;
} PtTabUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

