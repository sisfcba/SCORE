
/*
 *	PtBasic.h
 *		Header file for the PtBasic widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_BASIC_H_INCLUDED
#define __PT_BASIC_H_INCLUDED

#ifndef __PT_WIDGET_H_INCLUDED
 #include <photon/PtWidget.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtBasic public
 */

extern PtWidgetClassRef_t *PtBasic;

/* Resources */
#define	Pt_ARG_BOT_BORDER_COLOR			Pt_RESOURCE( 2, 0 )
#define Pt_ARG_COLOR       				Pt_RESOURCE( 2, 1 )
#define Pt_ARG_FILL_COLOR				Pt_RESOURCE( 2, 2 )
#define Pt_ARG_FILL_PATTERN				Pt_RESOURCE( 2, 3 )
#define Pt_ARG_MARGIN_HEIGHT			Pt_RESOURCE( 2, 4 )
#define Pt_ARG_MARGIN_WIDTH				Pt_RESOURCE( 2, 5 )
#define Pt_ARG_TOP_BORDER_COLOR			Pt_RESOURCE( 2, 6 )
#define Pt_ARG_TRANS_PATTERN			Pt_RESOURCE( 2, 13 )
#define Pt_ARG_HIGHLIGHT_ROUNDNESS		Pt_RESOURCE( 2, 14 )
#define Pt_ARG_BASIC_FLAGS				Pt_RESOURCE( 2, 15 )

#define Pt_ARG_BANDWIDTH_THRESHOLD		Pt_RESOURCE( 2, 17 )

#define Pt_CB_ARM						Pt_RESOURCE( 2, 7 )
#define Pt_CB_DISARM					Pt_RESOURCE( 2, 8 )
#define Pt_CB_ACTIVATE					Pt_RESOURCE( 2, 9 )
#define Pt_CB_GOT_FOCUS					Pt_RESOURCE( 2, 10 )
#define Pt_CB_LOST_FOCUS				Pt_RESOURCE( 2, 11 )
#define Pt_CB_REPEAT					Pt_RESOURCE( 2, 12 )
#define Pt_CB_MENU						Pt_RESOURCE( 2, 16 )

/* Basic Flags */
#define Pt_BASIC_RO_FLAGS	0xffffffff

/* Callback structure */
typedef struct {
	int		value;
} PtBasicCallback_t;


/*
 * PtBasic private
 */

/* Widget structure */
typedef struct Pt_basic_widget {
	PtWidget_t					core;
	PgColor_t					color;
	PgColor_t					fill_color;
	char						fill_pattern[8];
	char						trans_pattern[8];
	PgColor_t					top_border_color;
	PgColor_t					bot_border_color;
	ushort_t					margin_height;
	ushort_t					margin_width;
	ushort_t					roundness;
	long						flags;
	PtCallbackList_t			*arm;
	PtCallbackList_t			*repeat;
	PtCallbackList_t			*disarm;
	PtCallbackList_t			*activate;
	PtCallbackList_t			*menu;
	PtCallbackList_t			*got_focus;
	PtCallbackList_t			*lost_focus;
} PtBasicWidget_t;

/* Widget union */
typedef union Pt_basic_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
} PtBasicUnion_t;


/*
 * PtBasic class structure additions
 */

typedef struct Pt_basic_widget_class {
	PtWidgetClass_t		core;
	void				(*got_focus_f)( PtWidget_t *, PhEvent_t * );
	int					(*lost_focus_f)( PtWidget_t *, PhEvent_t * );
	void				(*calc_opaque_f)( PtWidget_t * );
} PtBasicWidgetClass_t;

#define Pt_SET_GOT_FOCUS_F			(Pt_ARG_MODE_PTR|offsetof(PtBasicWidgetClass_t,got_focus_f))
#define Pt_SET_LOST_FOCUS_F			(Pt_ARG_MODE_PTR|offsetof(PtBasicWidgetClass_t,lost_focus_f))
#define Pt_SET_CALC_OPAQUE_F		(Pt_ARG_MODE_PTR|offsetof(PtBasicWidgetClass_t,calc_opaque_f))


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
