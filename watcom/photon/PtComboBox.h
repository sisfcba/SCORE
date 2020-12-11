/*
 *	PtComboBox.h
 *		Header file for the PtComboBox widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_COMBOBOX_H_INCLUDED
#define __PT_COMBOBOX_H_INCLUDED

#ifndef __PT_COMPOUND_H_INCLUDED
#include <photon/PtCompound.h>
#endif

#ifndef __PT_TEXT_H_INCLUDED
#include <photon/PtText.h>
#endif

#ifndef __PT_LIST_H_INCLUDED
#include <photon/PtList.h>
#endif

#ifndef __PT_RAW_H_INCLUDED
#include <photon/PtRaw.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif
/*
 * PtComboBox Convenience Functions
 */

extern int PtComboBoxListOpen( PtWidget_t * );
extern int PtComboBoxListClose( PtWidget_t * );

/*
 * PtComboBox public
 */
extern PtWidgetClassRef_t *PtComboBox;

#define Pt_ARG_CBOX_FLAGS						Pt_RESOURCE( 31, 0 )
#define Pt_ARG_CBOX_SEL_ITEM					Pt_RESOURCE( 31, 1 )
#define Pt_ARG_CBOX_SELECTION_ITEM				Pt_RESOURCE( 31, 1 )

#define Pt_ARG_CBOX_BUTTON_BORDER_WIDTH			Pt_RESOURCE( 31, 15 )
#define Pt_ARG_CBOX_BUTTON_TOP_BORDER_COLOR		Pt_RESOURCE( 31, 16 )
#define Pt_ARG_CBOX_BUTTON_BOT_BORDER_COLOR		Pt_RESOURCE( 31, 17 )
#define Pt_ARG_CBOX_BUTTON_COLOR				Pt_RESOURCE( 31, 18 )
#define Pt_ARG_CBOX_MAX_VISIBLE_COUNT			Pt_RESOURCE( 31, 19)
#define Pt_ARG_CBOX_BUTTON_WIDTH				Pt_RESOURCE( 31, 6 )
#define Pt_CB_CBOX_ACTIVATE						Pt_RESOURCE( 31, 14 )
#define Pt_CB_CBOX_CLOSE						Pt_RESOURCE( 31, 20 )

/* Old Manifests */
#define Pt_ARG_CBOX_ITEMS					Pt_ARG_ITEMS
#define Pt_ARG_CBOX_SPACING					Pt_ARG_LIST_SPACING
#define Pt_ARG_CBOX_SEL_MODE				Pt_ARG_SELECTION_MODE
#define Pt_ARG_CBOX_SELECTION_MODE			Pt_ARG_SELECTION_MODE
#define Pt_ARG_CBOX_VISIBLE_COUNT			Pt_ARG_VISIBLE_COUNT
#define Pt_ARG_CBOX_SELECTION_FILL_COLOR 	Pt_ARG_SELECTION_FILL_COLOR
#define Pt_ARG_CBOX_SELECTION_TEXT_COLOR    Pt_ARG_SELECTION_TEXT_COLOR

#define Pt_ARG_CBOX_MAX_LENGTH				Pt_ARG_MAX_LENGTH
#define Pt_ARG_CBOX_CURSOR_POSITION			Pt_ARG_CURSOR_POSITION
#define Pt_ARG_CBOX_EDIT_MASK				Pt_ARG_EDIT_MASK
#define Pt_ARG_CBOX_TEXT_FONT				Pt_ARG_TEXT_FONT
#define Pt_ARG_CBOX_TEXT_STRING				Pt_ARG_TEXT_STRING


/* ComboBox flags */
#define Pt_COMBOBOX_STATIC					0x00000020
#define Pt_COMBOBOX_TOP						0x00000040
#define Pt_COMBOBOX_MAX_WIDTH				0x00000080
#define Pt_COMBOBOX_ALT_DOWN 				0x00000100
#define	Pt_COMBOBOX_OPEN					0x80000000 // ( r/o )
#define Pt_COMBOBOX_ON_BOTTOM				0x40000000 // ( r/o )
#define Pt_COMBOBOX_EXTENTING				0x20000000 // ( r/o )

/* Callback structure */
typedef PtTextCallback_t PtComboBoxTextCallback_t;
typedef PtListCallback_t PtComboBoxListCallback_t;

/*
 * PtComboBox private
 */

/* Widget structure */
typedef struct Pt_combobox_widget {
	PtCompoundWidget_t		compound;
	ulong_t		           	flags;
	ulong_t					resize_flags;			
	short					sel_item;
	PhDim_t					butn_size;
	short					butn_border_width;
	PgColor_t				butn_bot_border_color;
	PgColor_t				butn_top_border_color;
	PgColor_t				butn_color;
	short					border_width;
	short					max_visible;

	PtCallbackList_t		*text_changed;
	PtCallbackList_t		*modify_verify;
	PtCallbackList_t		*motion_verify;
	PtCallbackList_t        *selection;
	PtCallbackList_t		*list_input;
	PtCallbackList_t        *combobox_activate;

	PtWidget_t				*text_wgt;
	PtWidget_t				*list_wgt;
	PtWidget_t				*list_region_ff;
	PtWidget_t				*list_region;
	PtWidget_t				*butn_wgt;
	PtCallbackList_t        *combobox_close;
} PtComboBoxWidget_t;

/* Widget union */
typedef union Pt_combobox_union {
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtContainerWidget_t		container;
	PtCompoundWidget_t		compound;
	PtComboBoxWidget_t		combobox;
} PtComboBoxUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
