/*
 *	PtMenuLabel.h
 *		Header file for the PtMenuLabel widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_MENULABEL_H_INCLUDED
#define __PT_MENULABEL_H_INCLUDED

#include <photon/PtLabel.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtMenuLabel public
 */

extern PtWidgetClassRef_t *PtMenuLabel;

/* Resources */
#define	Pt_ARG_ACCEL_TEXT		Pt_RESOURCE( 7, 0 )
#define	Pt_ARG_ACCEL_FONT		Pt_RESOURCE( 7, 1 )
#define	Pt_ARG_BUTTON_TYPE		Pt_RESOURCE( 7, 2 )
#define Pt_ARG_OFFSET			Pt_RESOURCE( 7, 3 )

/* Button types */
#define Pt_MENU_TEXT	0
#define	Pt_MENU_BAR     1
#define Pt_MENU_RIGHT	2
#define Pt_MENU_DOWN	3
#define Pt_MENU_UP		4


/*
 * PtMenuLabel private
 */

/* Widget structure */
typedef struct Pt_menu_label_widget {
	PtLabelWidget_t			label;
	char					*text;
	char					*font;
	ushort_t				button_type;
	ushort_t				offset;
	char					textkey;
	char					reserved[3];
} PtMenuLabelWidget_t;

/* Widget union */
typedef union Pt_menu_label_union {
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtLabelWidget_t			label;
	PtMenuLabelWidget_t		mlabel;
} PtMenuLabelUnion_t;


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
