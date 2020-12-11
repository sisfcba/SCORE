/*
 *	PtContainer.h
 *		Header file for the PtContainer widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_CONTAINER_H_INCLUDED
#define __PT_CONTAINER_H_INCLUDED

#ifndef __PT_BASIC_H_INCLUDED
 #include <photon/PtBasic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtContainer public
 */

extern PtWidgetClassRef_t *PtContainer;

/* Resources */
#define Pt_ARG_ANCHOR_OFFSETS	Pt_RESOURCE( 10, 0 )
#define Pt_ARG_ANCHOR_FLAGS		Pt_RESOURCE( 10, 1 )
#define Pt_ARG_FOCUS			Pt_RESOURCE( 10, 2 )

#define Pt_CB_RESIZE			Pt_RESOURCE( 10, 3 )
#define Pt_CB_BALLOONS			Pt_RESOURCE( 10, 4 )
#define Pt_ARG_CONTAINER_FLAGS  Pt_RESOURCE( 10, 5 )
#define Pt_CB_FILTER			Pt_RESOURCE( 10, 6 )

/*** ANCHOR FLAG MANIFESTS  ***/
#define Pt_LEFT_ANCHORED_RELATIVE		0x00000001
#define Pt_RIGHT_ANCHORED_RELATIVE		0x00000002
#define Pt_TOP_ANCHORED_RELATIVE		0x00000004
#define Pt_BOTTOM_ANCHORED_RELATIVE		0x00000008

#define Pt_LEFT_ANCHORED_RIGHT			0x00000010
#define Pt_RIGHT_ANCHORED_RIGHT			0x00000020
#define Pt_TOP_ANCHORED_BOTTOM			0x00000040
#define Pt_BOTTOM_ANCHORED_BOTTOM		0x00000080

#define Pt_LEFT_ANCHORED_LEFT			0x00000100
#define Pt_RIGHT_ANCHORED_LEFT			0x00000200
#define Pt_TOP_ANCHORED_TOP				0x00000400
#define Pt_BOTTOM_ANCHORED_TOP			0x00000800

#define Pt_BALLOONS_ON					0x00001000

#define Pt_CONTAINER_FLAGS_MASK			0x00001fff
#define Pt_CONTAINER_ANCHORED_RIGHT		( Pt_LEFT_ANCHOR_RIGHT | Pt_RIGHT_ANCHOR_RIGHT )
#define Pt_CONTAINER_ANCHORED_BOTTOM	( Pt_TOP_ANCHOR_BOTTOM | Pt_BOTTOM_ANCHOR_BOTTOM )

//convenience...
#define Pt_LEFT_IS_ANCHORED		(Pt_LEFT_ANCHORED_RIGHT|Pt_LEFT_ANCHORED_LEFT| Pt_LEFT_ANCHORED_RELATIVE)
#define Pt_TOP_IS_ANCHORED		(Pt_TOP_ANCHORED_TOP|Pt_TOP_ANCHORED_BOTTOM|Pt_TOP_ANCHORED_RELATIVE)
#define Pt_RIGHT_IS_ANCHORED	(Pt_RIGHT_ANCHORED_LEFT|Pt_RIGHT_ANCHORED_RIGHT|Pt_RIGHT_ANCHORED_RELATIVE)
#define Pt_BOTTOM_IS_ANCHORED	(Pt_BOTTOM_ANCHORED_TOP|Pt_BOTTOM_ANCHORED_BOTTOM|Pt_BOTTOM_ANCHORED_RELATIVE)
#define Pt_IS_ANCHORED (Pt_LEFT_IS_ANCHORED|Pt_RIGHT_IS_ANCHORED|Pt_TOP_IS_ANCHORED|Pt_BOTTOM_IS_ANCHORED)

// Private anchor flag values
#define Pt_ANCHORS_LOCKED				0x04000000 /* (r/o) */
#define Pt_BALLOONS_ACTIVE				0x02000000 /* (r/o) */
#define Pt_CONTAINER_RESIZING			0x01000000 /* (r/o) */
#define Pt_BALLOONS_LOCKED				0x80000000 /* (r/o) */
#define Pt_ANCHORS_INVALID				0x40000000 /* (r/o) */
#define Pt_CONTAINER_ANCHORING			0x20000000 /* (r/o) */

// FLAG MANIFESTS
#define Pt_BLOCK_CUA_FOCUS				0x00000001 
#define Pt_AUTO_EXTENT					0x00000002
#define Pt_HOTKEY_TERMINATOR			0x00000004
#define Pt_DISABLE_BALLOONS				0x00000008
#define Pt_ENABLE_CUA					0x00000010
#define Pt_ENABLE_CUA_ARROWS			0x00000020
#define Pt_BALLOON_PROPAGATE			0x00000040
#define Pt_HOTKEYS_FIRST				0x00000080

#define Pt_SUPER_CONSTRAINTS			0x00000800 /* (r/o) */
#define Pt_CURSOR_IN_CONTAINER			0x00001000 /* (r/o) */
#define Pt_SYSINFO_VALID				0x00002000 /* (r/o) */
#define Pt_CANVAS_INVALID				0x00004000 /* (r/o) */
#define Pt_IGNORE_CONSTRAINTS			0x00008000 /* (r/o) */

#define Pt_CHILD_REDIRECTOR				0x00400000 /* (r/o) */
#define Pt_CHILD_DESTROYED				0x00800000 /* (r/o) */
#define Pt_CHILD_CREATED				0x01000000 /* (r/o) */
#define Pt_CHILD_REALIZED				0x02000000 /* (r/o) */
#define Pt_CHILD_UNREALIZED				0x04000000 /* (r/o) */
#define Pt_CHILD_MOVED_RESIZED			0x08000000 /* (r/o) */
#define Pt_CHILD_GETTING_FOCUS			0x10000000 /* (r/o) */
#define Pt_CHILD_LOST_FOCUS				0x20000000 /* (r/o) */
#define Pt_CHILD_LOSING_FOCUS			0x20000000 /* (r/o) */
#define Pt_CHILD_SETTING_RESOURCE		0x40000000 /* (r/o) */
#define Pt_CHILD_GETTING_RESOURCE		0x80000000 /* (r/o) */

#define Pt_CONTAINER_CONSTRAINT_BITS	0xFFFF0000
#define Pt_CONTAINER_RO_FLAGS			(Pt_IGNORE_CONSTRAINTS | Pt_CANVAS_INVALID | Pt_CONTAINER_CONSTRAINT_BITS)

typedef struct pt_container_callback {
	PhRect_t new_size;
	PhRect_t old_size;
} PtContainerCallback_t;


/*
 * PtContainer private
 */

/* Widget structure */
typedef struct Pt_container_widget {
	PtBasicWidget_t				basic;
	PhTile_t					*damage_visible;
	PhTile_t					*damage_list;
	PtWidget_t					*damage_clean;
	PtWidget_t					*focus;
	PtWidget_t					*child_front;
	PtCallbackList_t			*resize;
	uint_t						anchor_flags;
	PhRect_t					anchor_offset;
	PhRect_t					old_extent;
	PtBalloonCallbackList_t		*balloons;
	PtBalloonCallback_t			*current_balloon;
	short						balloon_count;
	uchar_t						flux_count;
	char						reserved1;
	PtWidgetList_t				*ctnrs;
	long						flags;
	PtWidget_t 					*last_focus;
	PtWidget_t *			(*redirect)( PtWidget_t *widget, PtWidgetClassRef_t *);
	PhSysInfo_t				 *sysinfo;
	PtRawCallbackList_t		 *filters;
} PtContainerWidget_t;

/* Widget union */
typedef struct Pt_container_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
} PtContainerUnion_t;

/* Event types redirected by PtContainer */
#define Pt_EV_REDIRECTED	(Ph_EV_BUT_PRESS|Ph_EV_BUT_RELEASE|Ph_EV_KEY|Ph_EV_BUT_REPEAT)

typedef struct Pt_container_widget_class {
    PtBasicWidgetClass_t	basic;
	void					(*child_created_f)( PtWidget_t *widget, PtWidget_t *child );
	int						(*child_settingresource_f)(PtWidget_t *widget, PtWidget_t *child, PtArg_t const *argt);
	int						(*child_gettingresource_f)(PtWidget_t *widget, PtWidget_t *child, PtArg_t *argt );
	void					(*child_realized_f)( PtWidget_t *widget, PtWidget_t *child );
	void					(*child_unrealized_f)( PtWidget_t *widget, PtWidget_t *child );
	void					(*child_destroyed_f)( PtWidget_t *widget, PtWidget_t *child );
	void					(*child_move_resize_f)( PtWidget_t *widget, PtWidget_t *child, PhArea_t *current_area, PhRect_t *current_extent, PhArea_t *old_area, PhRect_t *old_extent );
	int						(*child_getting_focus_f)( PtWidget_t *widget, PtWidget_t *child, PhEvent_t *event );
	int					(*child_losing_focus_f)( PtWidget_t *widget, PtWidget_t *child, PhEvent_t *event );
} PtContainerClass_t;

#define Pt_SET_CHILD_SETTINGRESOURCE_F (Pt_ARG_MODE_PTR|offsetof(PtContainerClass_t, child_settingresource_f))
#define Pt_SET_CHILD_GETTINGRESOURCE_F (Pt_ARG_MODE_PTR|offsetof(PtContainerClass_t, child_gettingresource_f))
#define Pt_SET_CHILD_REALIZED_F  (Pt_ARG_MODE_PTR|offsetof(PtContainerClass_t, child_realized_f))
#define Pt_SET_CHILD_UNREALIZED_F  (Pt_ARG_MODE_PTR|offsetof(PtContainerClass_t, child_unrealized_f)) 
#define Pt_SET_CHILD_CREATED_F  (Pt_ARG_MODE_PTR|offsetof(PtContainerClass_t, child_created_f)) 
#define Pt_SET_CHILD_DESTROYED_F  (Pt_ARG_MODE_PTR|offsetof(PtContainerClass_t, child_destroyed_f)) 
#define Pt_SET_CHILD_MOVED_RESIZED_F  (Pt_ARG_MODE_PTR|offsetof(PtContainerClass_t, child_move_resize_f)) 
#define Pt_SET_CHILD_GETTING_FOCUS_F  (Pt_ARG_MODE_PTR|offsetof(PtContainerClass_t, child_getting_focus_f)) 
#define Pt_SET_CHILD_LOSING_FOCUS_F  (Pt_ARG_MODE_PTR|offsetof(PtContainerClass_t, child_losing_focus_f)) 

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
