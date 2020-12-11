/*
 *	PtButton.h
 *		Header file for the PtButton widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_BUTTON_H_INCLUDED
#define __PT_BUTTON_H_INCLUDED

#ifndef __PT_LABEL_H_INCLUDED
 #include <photon/PtLabel.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtButton public
 */

extern PtWidgetClassRef_t *PtButton;

/* Resources */
#define	Pt_ARG_ARM_COLOR		Pt_RESOURCE( 6, 0 )
#define	Pt_ARG_ARM_DATA			Pt_RESOURCE( 6, 1 )
#define	Pt_ARG_ARM_FILL			Pt_RESOURCE( 6, 2 )

/*
 * PtButton private
 */

/* Widget structure */
typedef struct Pt_button_widget {
	PtLabelWidget_t			label;
	PgColor_t				arm_color;
	void 					*arm_data;
	void 					*unarmed_data;
	uchar_t					arm_fill;
	PtCallbackList_t		*activate;
} PtButtonWidget_t;

/* Widget union */
typedef union Pt_button_union {
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtLabelWidget_t			label;
	PtButtonWidget_t		button;
} PtButtonUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
