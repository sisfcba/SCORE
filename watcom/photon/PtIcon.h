/*
 *	PtIcon.h
 *		Header file for the PtIcon widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_ICON_H_INCLUDED
#define __PT_ICON_H_INCLUDED

#ifndef __PT_WINDOW_H_INCLUDED
 #include <photon/PtWindow.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtIcon public
 */

extern PtWidgetClassRef_t *PtIcon;


/* 
 * PtIcon private
 */

/* Widget structure */
typedef struct Pt_icon_widget {
	PtWindowWidget_t			window;
} PtIconWidget_t;

/* Widget union */
typedef union Pt_icon_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtWindowWidget_t			window;
	PtIconWidget_t				icon;
} PtIconUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
