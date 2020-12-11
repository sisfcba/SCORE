/*
 *	PtWindow.h
 *		Header file for the PtWindow widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_WINDOW_H_INCLUDED
#define __PT_WINDOW_H_INCLUDED

#ifndef __PT_CONTAINER_H_INCLUDED
 #include <photon/PtContainer.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtWindow public
 */

extern PtWidgetClassRef_t *PtWindow;

/* Resources */
#define Pt_ARG_DEFAULT_ACTION			Pt_RESOURCE( 18, 0 )
#define Pt_ARG_ICON_FLAGS				Pt_RESOURCE( 18, 1 )
#define Pt_ARG_ICON_POS					Pt_RESOURCE( 18, 2 )
#define Pt_ARG_ICON_WINDOW				Pt_RESOURCE( 18, 3 )
#define Pt_ARG_MAX_HEIGHT				Pt_RESOURCE( 18, 4 )
#define Pt_ARG_MAX_WIDTH				Pt_RESOURCE( 18, 5 )
#define Pt_ARG_MIN_HEIGHT				Pt_RESOURCE( 18, 6 )
#define Pt_ARG_MIN_WIDTH				Pt_RESOURCE( 18, 7 )
#define Pt_ARG_WIN_PARENT				Pt_RESOURCE( 18, 8 )
#define Pt_ARG_WINDOW_CURSOR_OVERRIDE	Pt_RESOURCE( 18, 9 )
#define Pt_ARG_WINDOW_FORCE_FRONT		Pt_RESOURCE( 18, 10 )
#define Pt_ARG_WINDOW_MANAGED_FLAGS		Pt_RESOURCE( 18, 11 )
#define Pt_ARG_WINDOW_NOTIFY_FLAGS		Pt_RESOURCE( 18, 12 )
#define Pt_ARG_WINDOW_RENDER_FLAGS		Pt_RESOURCE( 18, 13 )
#define Pt_ARG_WINDOW_STATE				Pt_RESOURCE( 18, 14 )
#define Pt_ARG_WINDOW_TITLE				Pt_RESOURCE( 18, 15 )
#define Pt_ARG_WINDOW_TITLE_COLOR		Pt_RESOURCE( 18, 16 )
#define Pt_ARG_WINDOW_HELP_ROOT			Pt_RESOURCE( 18, 20 )
#define Pt_ARG_WINDOW_FRONT_WINDOW		Pt_RESOURCE( 18, 22 )

#define Pt_CB_WINDOW					Pt_RESOURCE( 18, 17 )
#define Pt_CB_WINDOW_OPENING			Pt_RESOURCE( 18, 23 )
#define Pt_CB_WINDOW_CLOSING			Pt_RESOURCE( 18, 24 )
#define Pt_CB_WINDOW_TRANSPORT			Pt_RESOURCE( 18, 21 )

#define Pt_ARG_WINDOW_ACTIVE_COLOR		Pt_RESOURCE( 18, 18 )
#define Pt_ARG_WINDOW_INACTIVE_COLOR	Pt_RESOURCE( 18, 19 )

/* Window key array element */
typedef struct Pt_window_key {
	unsigned long				state;
	ushort_t					code;
	PtWidget_t					*widget;
} PtWindowKey_t;


/* 
 * PtWindow private
 */

/* Widget structure */
typedef struct Pt_window_widget {
	PtContainerWidget_t			container;
	ulong_t						set_flags;
	ulong_t						render_flags;
	ulong_t						managed_flags;
	ulong_t						notify_flags;
	char						*title;
	char						*sender;
	PtWidget_t					*dflt_action;
	PtCallbackList_t			*window_cb;
	PtWindowKey_t				*keys;
	PhRid_t						override_rid;
	PtWidget_t					*icon;
	ushort_t					state;
	ushort_t					win_flags;
	ushort_t					key_count;

	ushort_t					max_height;
	ushort_t					min_height;
	ushort_t					max_width;
	ushort_t					min_width;
	PgColor_t					frame_active_color;
	PgColor_t					frame_inactive_color;
	char 						*help_root;
	PtCallbackList_t			*window_transport_cb;
	PhRid_t						win_in_front;
	PtCallbackList_t			*window_opening;
	PgColor_t					title_color;
	PtCallbackList_t			*window_closing;
} PtWindowWidget_t;

/* Widget union */
typedef union Pt_window_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtWindowWidget_t			window;
} PtWindowUnion_t;

#define Pt_WINDOW_MAXING				0x8000
#define Pt_WINDOW_FORCE_FRONT			0x0001
#define Pt_WINDOW_CURSOR_OVERRIDE		0x0002
#define Pt_WINDOW_TASKBAR				0x0004
#define Pt_WINDOW_EXTENTING				0x0008
#define Pt_WINDOW_SETTING				0x0010

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
