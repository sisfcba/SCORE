/*
 *	PtToggleButton.h
 *		Header file for the PtToggleButton widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_TOGGLE_BUTTON_H_INCLUDED
#define __PT_TOGGLE_BUTTON_H_INCLUDED

#ifndef __PT_LABEL_H_INCLUDED
 #include <photon/PtLabel.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtToggleButton public
 */

extern PtWidgetClassRef_t *PtToggleButton;

/* Resources */
#define Pt_ARG_INDICATOR_COLOR		Pt_RESOURCE( 9, 0 )
#define Pt_ARG_INDICATOR_TYPE		Pt_RESOURCE( 9, 2 )
#define Pt_ARG_SET_COLOR			Pt_RESOURCE( 9, 3 )
#define Pt_ARG_SET_FILL				Pt_RESOURCE( 9, 4 )
#define Pt_ARG_SPACING				Pt_RESOURCE( 9, 5 )
#define Pt_ARG_INDICATOR_DEPTH		Pt_RESOURCE( 9, 6 )
#define Pt_ARG_INDICATOR_WIDTH		Pt_RESOURCE( 9, 7 )
#define Pt_ARG_INDICATOR_HEIGHT		Pt_RESOURCE( 9, 8 )

/* Indicator types */
#define	Pt_N_OF_MANY				0
#define	Pt_ONE_OF_MANY				1
#define	Pt_RADIO					2
#define	Pt_ROUND					3
#define	Pt_TICK						4
#define	Pt_CHECK					5


/*
 * PtToggleButton private
 */

/* Widget structure */
typedef struct Pt_toggle_button_widget {
	PtLabelWidget_t			label;
	PgColor_t				set_color;
	PgColor_t				indicator_color;
	ushort_t				indicator_size;
	ushort_t				spacing;
	uchar_t 				indicator_type;
	uchar_t					set_fill;
	ushort_t				indicator_depth;
	ushort_t				indicator_width;
	ushort_t				indicator_height;
	PtCallbackList_t		*new_value;
} PtToggleButtonWidget_t;

/* Widget union */
typedef union Pt_toggle_button_union {
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtLabelWidget_t			label;
	PtToggleButtonWidget_t	toggle;
} PtToggleButtonUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
