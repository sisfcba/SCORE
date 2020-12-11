/*
 *	PtMenu.h
 *		Header file for the PtMenu widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_MENU_H_INCLUDED
#define __PT_MENU_H_INCLUDED

#ifndef __PT_GROUP_H_INCLUDED 
#include <photon/PtGroup.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtMenu public
 */

extern PtWidgetClassRef_t *PtMenu;

 
/* Resources */
#define Pt_ARG_MENU_FLAGS			Pt_RESOURCE( 19, 0 )
#define Pt_ARG_MENU_SPACING			Pt_RESOURCE( 19, 1 )
#define Pt_ARG_MENU_TEXT_FONT		Pt_RESOURCE( 19, 2 )
#define Pt_ARG_MENU_TITLE			Pt_RESOURCE( 19, 3 )
#define Pt_ARG_MENU_TITLE_FONT		Pt_RESOURCE( 19, 4 )

/* flag bits */
#define Pt_MENU_AUTO			0x00000001
#define Pt_MENU_TRANSIENT		0x00000002
#define Pt_MENU_TEAR_OFF		0x00000004
#define Pt_MENU_CHILD   		0x00000008


/*
 * PtMenu private
 */

#define Pt_MENU_ON_TOP			0x04000000
#define Pt_MENU_ON_LEFT			0x08000000
#define Pt_MENU_GOT_FOCUS		0x10000000
#define Pt_MENU_FOCUS			0x20000000
#define Pt_MENU_END_RELEASE		0x40000000
#define Pt_MENU_PDR_ON			0x80000000

/* Widget structure */
typedef struct Pt_menu_widget {
	PtGroupWidget_t				group;
	ulong_t						flags;
	PtWidget_t					*ff_wgt;
	short						spacing;
	ushort_t					init_done;
	PtWidget_t					*child_menu;
	char						*title;
	char						*title_font;
	char						*text_font;
	ushort_t					title_sep;
	int							num_cols;
	int							base_col_num_items;
	short						reserved;
	PtWidget_t					*prev_focus;
} PtMenuWidget_t;

// Private widget data subtypes
#define 	Pt_MENU_NAVIGATE	1

/* Widget union */
typedef union Pt_menu_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtGroupWidget_t				group;
	PtMenuWidget_t				menu;
} PtMenuUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
