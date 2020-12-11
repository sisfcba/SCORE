/*
 *	PtWidget.h
 *		Header file for the PtWidget widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_WIDGET_H_INCLUDED
#define __PT_WIDGET_H_INCLUDED

#ifndef _STDDEF_H_INCLUDED
 #include <stddef.h>
#endif

#ifndef __PT_T_H_INCLUDED
#include <photon/PtT.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtWidget public 
 */

extern PtWidgetClassRef_t *PtWidget;

/* Resources */
#define Pt_ARG_AREA						Pt_RESOURCE( 1, 0 )
#define Pt_ARG_BORDER_WIDTH				Pt_RESOURCE( 1, 1 )
#define Pt_ARG_CURSOR_TYPE				Pt_RESOURCE( 1, 2 )
#define Pt_ARG_CURSOR_COLOR				Pt_RESOURCE( 1, 3 )
#define Pt_ARG_DATA						Pt_RESOURCE( 1, 4 )
#define Pt_ARG_DIM						Pt_RESOURCE( 1, 5 )
#define Pt_ARG_FLAGS					Pt_RESOURCE( 1, 6 )
#define Pt_ARG_POS						Pt_RESOURCE( 1, 7 )
#define Pt_ARG_RESIZE_FLAGS				Pt_RESOURCE( 1, 8 )

#define Pt_CB_DESTROYED					Pt_RESOURCE( 1, 9 )
#define Pt_CB_HOTKEY					Pt_RESOURCE( 1, 10)
#define Pt_CB_RAW_EVENT 				Pt_RESOURCE( 1, 11 )
#define Pt_CB_REALIZED					Pt_RESOURCE( 1, 12 )
#define Pt_CB_UNREALIZED				Pt_RESOURCE( 1, 13 )

#define Pt_ARG_USER_DATA				Pt_RESOURCE( 1, 14 )
#define Pt_ARG_HELP_TOPIC				Pt_RESOURCE( 1, 15 )
#define Pt_CB_BLOCKED					Pt_RESOURCE( 1, 16 )
#define Pt_ARG_BITMAP_CURSOR			Pt_RESOURCE( 1, 17 )
#define Pt_ARG_EFLAGS					Pt_RESOURCE( 1, 18 )
#define Pt_CB_IS_DESTROYED				Pt_RESOURCE( 1, 19 )


#define Pt_ARG_RAW_CALLBACKS			Pt_RESOURCE( 1, 11 )
#define Pt_CB_RAW						Pt_RESOURCE( 1, 11 )

/* Flag bits (for use with Pt_ARG_FLAGS) */
#define Pt_REALIZED				0x00000001
#define Pt_SET					0x00000002
#define Pt_AUTOHIGHLIGHT		0x00000004
#define Pt_TOGGLE				0x00000008
#define Pt_CLIP_HIGHLIGHT		0x00000010
#define Pt_OPAQUE				0x00000020
#define Pt_DELAY_ACTIVATION		0x00000040
#define Pt_DELAY_REALIZE		Pt_DELAY_ACTIVATION
#define Pt_SELECTABLE			0x00000080
#define Pt_HIGHLIGHTED			0x00000100
#define Pt_ETCH_HIGHLIGHT		0x00000200
#define Pt_GETS_FOCUS			0x00000400
#define Pt_MENU_BUTTON			0x00000800
#define Pt_DESTROYED			0x00001000
#define Pt_DAMAGED				0x00002000
#define Pt_OBSCURED				0x00004000
#define Pt_IN_FLUX				0x00008000
#define Pt_CLEAR				0x00010000
#define Pt_BLOCKED				0x00020000
#define Pt_DAMAGE_FAMILY		0x00040000
#define Pt_SELECT_NOREDRAW		0x00080000
#define Pt_WIDGET_REBUILD       0x00100000
#define Pt_WIDGET_RESIZE		0x00200000
#define Pt_PROCREATED			0x00400000
#define Pt_ALL_BUTTONS			0x00800000
#define Pt_GHOST				0x01000000
#define Pt_FOCUS_RENDER			0x02000000
#define Pt_CALLBACKS_ACTIVE		0x04000000
#define Pt_MENUABLE				0x08000000

#define Pt_NOREDRAW_SET		 	0x10000000
#define Pt_FREE_MEMORY			0x20000000
#define Pt_REGION				0x40000000
#define Pt_REALIZING			0x80000000

/* EFlag bits (for use with Pt_ARG_EFLAGS) */
#define Pt_CONSUME_EVENTS	0x0001 
#define Pt_INTERNAL_HELP	0x0002
#define Pt_DOOMED			0x0800	/* (r/o) */ 
#define Pt_WIN_REQUEST		0x1000  /* (r/o) */
#define Pt_SKIP_CHILDREN	0x2000  /* (r/o) */
#define Pt_DAMAGE_PARENT	0x4000
#define Pt_DAMAGE_ON_FOCUS	0x8000 	/* (r/o) */
#define Pt_RO_EFLAGS (Pt_DAMAGE_ON_FOCUS | Pt_SKIP_CHILDREN | Pt_WIN_REQUEST | Pt_DOOMED )

/* RESIZE MASKS  */

#define Pt_RESIZE_BITS			0x07
#define Pt_RESIZE_Y_SHIFT		20
#define Pt_RESIZE_X_SHIFT		23
#define Pt_INITIALIZED		0x04000000
#define Pt_UCLIP			0x08000000

/* Convenience resize defines */
#define Pt_RESIZE_Y_ALWAYS			(Pt_ALWAYS 		<< Pt_RESIZE_Y_SHIFT)
// 0x00100000

#define Pt_RESIZE_Y_AS_REQUIRED		(Pt_AS_REQUIRED << Pt_RESIZE_Y_SHIFT)
// 0x00200000

#define Pt_RESIZE_Y_INITIAL			(Pt_INITIAL 	<< Pt_RESIZE_Y_SHIFT)
// 0x00400000

#define Pt_RESIZE_Y_BITS			(Pt_RESIZE_BITS	<< Pt_RESIZE_Y_SHIFT)
// 0x00700000

#define Pt_RESIZE_X_ALWAYS			(Pt_ALWAYS 		<< Pt_RESIZE_X_SHIFT)
// 0x00800000

#define Pt_RESIZE_X_AS_REQUIRED		(Pt_AS_REQUIRED << Pt_RESIZE_X_SHIFT)
// 0x01000000

#define Pt_RESIZE_X_INITIAL			(Pt_INITIAL 	<< Pt_RESIZE_X_SHIFT)
// 0x02000000

#define Pt_RESIZE_X_BITS			(Pt_RESIZE_BITS	<< Pt_RESIZE_X_SHIFT)
// 0x03800000

#define Pt_RESIZE_XY_ALWAYS			(Pt_RESIZE_X_ALWAYS |Pt_RESIZE_Y_ALWAYS)
#define Pt_RESIZE_XY_AS_REQUIRED	(Pt_RESIZE_X_AS_REQUIRED|Pt_RESIZE_Y_AS_REQUIRED)
#define Pt_RESIZE_XY_INITIAL		(Pt_RESIZE_X_INITIAL |Pt_RESIZE_Y_INITIAL)
#define Pt_RESIZE_XY_BITS			(Pt_RESIZE_X_BITS |Pt_RESIZE_Y_BITS)

/*
 * PtWidget private
 */

typedef struct pt_widget_ex_data {
	char				*help_topic;
	PhCursorDef_t		*bitmap_cursor;
	} PtWidgetExData_t;

/* Subclasses can extend this area via
 *
 * typedef struct pt_mywidget_ex_data{
 *		PtWidgetExData_t	wd;
 *		char				*myfirst_res;
 *		PtCallbackList_t	*myforgotten_callbacks;
 *		} PtMyWidgetExData_t;
 *
 *	If using this facility, the Pt_SET_EX_STATE_LEN must be set as well as the
 *	Pt_SET_EX_OFFSET in order for PtSet/GetResources to work automatically.
 *	All resources placed in this extended area need to be qualified as
 *	Pt_ARG_EXTENDED resources:
 *		i.e. Pt_ARG_IS_NUMBER( class, member ) | Pt_ARG_EXTENDED, ...
 *	PtWidget's dflts function will allocate the space for all the extended data
 *	for the new widget class.
 */

 
/* Base widget structure */
struct Pt_widget {
	struct Pt_widget_class	*class_rec;
	struct Pt_widget		*parent;
	struct Pt_widget		*child;
	struct Pt_widget		*brother;
	struct Pt_widget		*bro_behind;
	PhRid_t					rid;
	PhArea_t				area;
	PhRect_t				extent;
	long					flags;
	ushort_t				extent_valid; 
	ushort_t				border_width;
	ulong_t					region_fields;
	ulong_t					resize_flags;
	PgColor_t				cursor_color;
	PhRect_t				opaque_rect;
	PhTile_t				*damage_list;
	char					*data;
	char					*user_data;
	PtRawCallbackList_t		*callbacks;
	PtHotkeyCallbackList_t	*hotkeys;
	PtCallbackList_t		*realized;
	PtCallbackList_t		*unrealized;
	PtCallbackList_t		*destroyed; /* called immediately upon PtDestroyWidget() */
	PtCallbackList_t		*blocked;
	PtCallbackList_t		*is_destroyed;
//	char					*help_topic; Moved to new EXDATA quick ref area.... :-) to make room for is_destroyed
	PtCallbackStack_t		*cb_stack;
//	PhCursorDef_t			*bitmap_cursor; MOVED TO X DATA AREA in widget_data chain.
	PtDataHdr_t				*widget_data;
	ushort_t				cursor_type;
	ushort_t				eflags;
};

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
