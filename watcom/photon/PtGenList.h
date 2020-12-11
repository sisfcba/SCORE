/*
 *	PtGenList.h
 *		Header file for the PtGenList widget class
 *
 *  Copyright by QNX Software Systems Limited 1996. All rights reserved.
 */
#ifndef __PT_GENLIST_H_INCLUDED
#define __PT_GENLIST_H_INCLUDED

#ifndef __PT_COMPOUND_H_INCLUDED
 #include <photon/PtCompound.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtGenList public
 */

extern PtWidgetClassRef_t *const PtGenList;

/* Resources */
#define Pt_ARG_LIST_FLAGS			Pt_RESOURCE( 23,  2 )
#define Pt_ARG_LIST_FONT			Pt_RESOURCE( 23,  3 )
#define Pt_ARG_SCROLLBAR_WIDTH		Pt_RESOURCE( 23,  5 )
#define Pt_ARG_SELECTION_MODE		Pt_RESOURCE( 23,  7 )
#define Pt_ARG_TOP_ITEM_POS			Pt_RESOURCE( 23,  8 )
#define Pt_ARG_VISIBLE_COUNT		Pt_RESOURCE( 23,  9 )
#define Pt_ARG_SELECTION_FILL_COLOR Pt_RESOURCE( 23, 12 )
#define Pt_ARG_SELECTION_TEXT_COLOR Pt_RESOURCE( 23, 13 )
#define Pt_ARG_LIST_ITEM_COUNT		Pt_RESOURCE( 23, 14 )
#define Pt_ARG_LIST_SEL_COUNT		Pt_RESOURCE( 23, 15 )
#define Pt_ARG_LIST_TOTAL_HEIGHT	Pt_RESOURCE( 23, 16 )
#define Pt_ARG_LIST_SB_RES			Pt_RESOURCE( 23, 25 )
#define Pt_ARG_LIST_SCROLL_RATE		Pt_RESOURCE( 23, 26 )
#define Pt_ARG_LIST_COLUMN_POS		Pt_RESOURCE( 23, 27 )
#define Pt_ARG_LIST_COLUMN_ATTR		Pt_RESOURCE( 23, 28 )
#define Pt_ARG_BALLOON_FILL_COLOR	Pt_RESOURCE(  3, 19 )
#define Pt_ARG_BALLOON_COLOR		Pt_RESOURCE(  3, 20 )


#define Pt_CB_SCROLL_MOVE			Pt_RESOURCE( 29, 10 )

#define Pt_ARG_SCROLLBAR			Pt_RESOURCE( 23, 11 )
// 		         ^^-----deprecated

/* Selection Callback Subtypes */
#define	Pt_LIST_SELECTION_FINAL		0x00
#define	Pt_LIST_SELECTION_BROWSE	0x01
#define	Pt_LIST_SELECTION_CANCEL	0x02

/* Scroll Move Callback Subtypes */
#define	Pt_LIST_SCROLL_LIST			0x00	//	The keyboard or mouse was used
#define	Pt_LIST_SCROLL_SCROLLBAR	0x01	//	The scrollbar was used

/* Actions for the Scroll Move callback: */
#define Pt_SCROLL_DECREMENT			1
#define Pt_SCROLL_INCREMENT			2
#define Pt_SCROLL_PAGE_INCREMENT	3
#define Pt_SCROLL_PAGE_DECREMENT	4
#define Pt_SCROLL_TO_MAX			5
#define Pt_SCROLL_TO_MIN			6
#define Pt_SCROLL_DRAGGED			7
#define Pt_SCROLL_RELEASED			8
#define Pt_SCROLL_SET				9

/* Photon 1.0 and PhAB-compatible selection modes */
#define Pt_SINGLE_MODE		1
#define Pt_MULTIPLE_MODE	2
#define Pt_BROWSE_MODE		3
/* New PhAB-compatible modes */
#define Pt_EXTENDED_MODE	4
#define Pt_RANGE_MODE		5

/* Compose selection modes */
#define Pt_SELECTION_MODE_MULTIPLE	0x8000
#define Pt_SELECTION_MODE_RANGE		0x8010
#define Pt_SELECTION_MODE_SINGLE	0x8020
#define Pt_SELECTION_MODE_NONE		0x8030

/* Compose selection mode flags */
#define Pt_SELECTION_MODE_NOSCROLL	0x8040
#define Pt_SELECTION_MODE_NOMOVE	0x8080
#define Pt_SELECTION_MODE_NOREST	0x8100
#define Pt_SELECTION_MODE_AUTO		0x8200
#define Pt_SELECTION_MODE_NOCLEAR	0x8400
#define Pt_SELECTION_MODE_TOGGLE	0x8800
#define Pt_SELECTION_MODE_NOFOCUS	0x9000

#define Pt_SELECTION_MODE_COMPOSE_FLAG	0x8000
#define Pt_SELECTION_MODE_COMPOSE_MASK	0x9FF0
/* Macros that calculate values for sel_xmode and sel_flags */
#define Pt_SELECTION_MODE( mode )	( (mode) >> 4 & 0x03 ) /* sel_xmode */
#define Pt_SELECTION_FLAGS( mode )	( (mode) >> 6 & 0xFF ) /* sel_flags */

/* List flags */
#define Pt_LIST_SCROLLBAR_NEVER			0x0000
#define Pt_LIST_SCROLLBAR_ALWAYS		0x0001
#define Pt_LIST_SCROLLBAR_AS_REQUIRED	0x0002
#define Pt_LIST_SCROLLBAR_MASK			0x0003
#define Pt_LIST_INACTIVE				0x0004
#define Pt_LIST_NON_SELECT				0x0008
#define Pt_LIST_SNAP					0x0010
/* New flags */
#define Pt_LIST_BALLOON_NEVER			0x0000
#define Pt_LIST_SHOW_BALLOON			0x0020
#define Pt_LIST_BALLOON_AS_REQUIRED		0x0040
#define Pt_LIST_BALLOON_MASK			0x0060
#define Pt_LIST_BALLOON_REGISTERED		0x0080 /* RO */
#define Pt_LIST_SCROLLBAR_GETS_FOCUS	0x0100
#define Pt_LIST_NOBLIT					0x0200
#define Pt_LIST_HEADER_AUTORESIZE		0x0400
#define Pt_LIST_SCROLLBAR_AUTORESIZE	0x0800
#define Pt_LIST_BALLOONS_IN_COLUMNS		0x1000
#define Pt_LIST_BOUNDARY_KEY_EVENTS		0x2000

/* Column flags */
#define Pt_LIST_COLUMN_LEFT				Pg_TEXT_LEFT
#define Pt_LIST_COLUMN_RIGHT			Pg_TEXT_RIGHT
#define Pt_LIST_COLUMN_CENTER			Pg_TEXT_CENTER
#define Pt_LIST_COLUMN_ALIGNMENT		( Pg_TEXT_LEFT | Pg_TEXT_RIGHT | Pg_TEXT_CENTER ) /* Mask */
#define Pt_LIST_COLUMN_DAMAGE_ALWAYS	0x0001

/* Balloon alignment types for PtGenListCreateTextBalloon() */
#define	Pt_LIST_BALLOON_LEFT		(-1)
#define	Pt_LIST_BALLOON_RIGHT		(-2)
#define	Pt_LIST_BALLOON_CENTER		(-3)

/* gflags */

#define Pt_GEN_LIST_NO_BACKGROUND			0x01
#define Pt_GEN_LIST_NO_CLIPPING				0x02
#define Pt_GEN_LIST_SHOW_DAMAGED			0x04
#define Pt_GEN_LIST_FULL_WIDTH				0x08
#define Pt_GEN_LIST_NO_AUTOFOCUS			0x10
#define Pt_GEN_LIST_ITEM_BACKGROUND			0x20

/* Item flags */

#define Pt_LIST_ITEM_SELECTED		0x001
#define Pt_LIST_ITEM_CURRENT		0x002
#define Pt_LIST_ITEM_DISABLED		0x004
#define Pt_LIST_ITEM_DAMAGED		0x008
#define Pt_LIST_ITEM_ABOVE			0x010	//	do NOT modify
#define Pt_LIST_ITEM_BELOW			0x020	//	do NOT modify
#define Pt_LIST_ITEM_SAVED			0x100	//	do NOT modify
#define Pt_LIST_ITEM_NOCOLUMNS		0x200
#define Pt_LIST_ITEM_USED_FLAGS		0x33F	//	Flags used by the GenList widget

/* Columns */

typedef struct Pt_list_column {
	short from, to;
	}
		PtListColumn_t;

typedef struct Pt_list_columns_attrs {
	unsigned flags;
	}
		PtListColumnAttributes_t;

/* Callback structure */
typedef struct Pt_list_scroll_callback {
	unsigned	action;
	int			position;
	}
		PtListScrollCallback_t;

/* List item structure */

typedef struct Pt_genlist_item {
	unsigned flags;
	PhDim_t size;
	struct Pt_genlist_item *next, *prev;
	}
		PtGenListItem_t;

/*
 * PtGenList private
 */

/* Widget structure */
struct Pt_gen_list_sel_state;

typedef struct Pt_genlist_widget {
	PtCompoundWidget_t	cmpnd;

	char				*font;				/* Pt_ARG_LIST_FONT */
	unsigned short		gflags;
	short				reserved;
	PtGenListItem_t		*first_item,		/* First item on list (NULL if list empty) */
						*last_item,			/* Last item on list (NULL if list empty) */
						*current_item,		/* NULL or the only item that has the CURRENT flag set */
						*first_displayed,	/* First of visible items (NULL if list empty) */
						*last_displayed,	/* Last of visible items (NULL if none is visible) */
						*range_item;		/* The beginning of range */
	unsigned			total_height;		/* Total height of all items */
	PgColor_t			selection_fill_color; /* Pt_ARG_SELECTION_FILL_COLOR */
	PgColor_t			selection_text_color; /* Pt_ARG_SELECTION_TEXT_COLOR */
	unsigned short		item_count,			/* Total number of items */
						displayed_count,	/* Number of visible items */
						sel_count,			/* Number of selected items */
						top_item,			/* Pt_ARG_TOP_ITEM_POS */
						rng_ndx,			/* Index of the range_item */
						cur_ndx,			/* Index of the current_item */
						max_top,			/* The maximal value of top_item */
						displayed_height,	/* Total height of visible items */
						slider_width,		/* Pt_ARG_SLIDER_WIDTH */
						sel_mode,			/* Pt_ARG_SELECTION_MODE */
						flags;				/* Pt_ARG_LIST_FLAGS */
	unsigned char		sel_xmode,			/* Selection mode */
						sel_flags;			/* Selection mode flags */
	short				scroll_rate;
	unsigned short		ncolumns;			/* Pt_ARG_COLUMN_POS.length */
	PtListColumn_t		*columns;			/* Pt_ARG_COLUMN_POS */
	PtCallbackList_t	*scroll;			/* Pt_CB_SCROLL_MOVE */
	PgColor_t			balloon_fg,			/* Pt_ARG_BALLOON_COLOR */
						balloon_bg;			/* Pt_ARG_BALLOON_FILL_COLOR */
	PtWidget_t			*balloon;
	PtListColumnAttributes_t *col_attrs;	/* Pt_ARG_COLUMN_ATTR */
	unsigned short		ncol_attrs;			/* Pt_ARG_COLUMN_ATTR.length */

	short				font_height;
	PtWidget_t			*divider;
	PtListColumn_t		damage;

	PtWidget_t			*scrollbar;
	PhDim_t				locked_size;
	unsigned short		top_margin;
	unsigned short		bot_margin;
	PtListColumn_t		vmarg;
	PtGenListItem_t		*inflated;
	short				will_damage;
	signed short		inflated_col;
	struct Pt_gen_list_sel_state
						*selst;
	}
		PtGenListWidget_t;

/* Widget union */
typedef union Pt_genlist_union {
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtContainerWidget_t		cntnr;
	PtCompoundWidget_t		cmpnd;
	PtGenListWidget_t		glist;
	}
		PtGenListUnion_t;

typedef void PtGenListDrawF_t(
	PtWidget_t *widget,
	PtGenListItem_t *item, unsigned index,
	unsigned nitems,
	PhRect_t *where /* Modify *where if needed */
	);

typedef int PtGenListMouseF_t(
	PtWidget_t *wgt,
	PtGenListItem_t *item,
	unsigned index,
	PhPoint_t *where, /* relative to the item, can modify */
	PhEvent_t *ev
	);

typedef int PtGenListKeyF_t(
	PtWidget_t *wgt,
	PhEvent_t *ev, PhKeyEvent_t *kev,
	PtGenListItem_t *newcur, unsigned newpos
	);

typedef void PtGenListSelectF_t(
	PtWidget_t *wgt, PtGenListItem_t *item, int pos,
	int nitems, int subtype, PhEvent_t *ev
	);

typedef PtWidget_t *PtGenListInflateF_t(
	PtWidget_t *widget, PtWidget_t *parent,
	PtGenListItem_t *item, unsigned index,
	int column, PhArea_t *area
	);

typedef struct Pt_gen_list_widget_class {
    PtCompoundClass_t	compound;
	PtGenListDrawF_t	*list_draw_f;
	PtGenListMouseF_t	*list_mouse_f;
	PtGenListKeyF_t		*list_key_f;
	PtGenListSelectF_t	*list_select_f;
	PtGenListInflateF_t	*list_inflate_f;
	}
		PtGenListClass_t;

#define Pt_SET_LIST_DRAW_F		Pt_ARG_IS_POINTER( PtGenListClass_t, list_draw_f )
#define Pt_SET_LIST_MOUSE_F		Pt_ARG_IS_POINTER( PtGenListClass_t, list_mouse_f )
#define Pt_SET_LIST_KEY_F		Pt_ARG_IS_POINTER( PtGenListClass_t, list_key_f )
#define Pt_SET_LIST_SELECT_F	Pt_ARG_IS_POINTER( PtGenListClass_t, list_select_f )
#define Pt_SET_LIST_INFLATE_F	Pt_ARG_IS_POINTER( PtGenListClass_t, list_inflate_f )

void PtSuperClassGenListDraw(
	PtWidgetClassRef_t *cref, PtWidget_t *widget,
	PtGenListItem_t *item, unsigned index,
	unsigned nitems, PhRect_t *where
	);

int PtSuperClassGenListMouse(
	PtWidgetClassRef_t *cref, PtWidget_t *wgt,
	PtGenListItem_t *item, unsigned index,
	PhPoint_t *where, PhEvent_t *ev
	);

int PtSuperClassGenListKey(
	PtWidgetClassRef_t *cref, PtWidget_t *wgt,
	PhEvent_t *ev, PhKeyEvent_t *kev,
	PtGenListItem_t *newcur, unsigned newpos
	);

void PtSuperClassGenListSelect(
	PtWidgetClassRef_t *cref, PtWidget_t *wgt,
	PtGenListItem_t *item, int pos,
	int nitems, int subtype, PhEvent_t *ev
	);

PtWidget_t *PtSuperClassGenListInflate(
	PtWidgetClassRef_t *cref, PtWidget_t *wgt,
	PtWidget_t *parent, PtGenListItem_t *item,
	unsigned index, int column, PhArea_t *area
	);


void PtGenListDrawBackground( 
	PtWidget_t *list, PtGenListItem_t const *item,
	unsigned nitems, PhRect_t const *where,
	int lmarg, int rmarg
	);

void PtGenListDrawString( 
	PtWidget_t *list, const char *string,
	PhRect_t const *where, int lmarg, int rmarg
	);

void PtGenListDrawStringNoColumns( 
	PtWidget_t *widget, const char *string,
	PhRect_t const *where, int lmarg, int rmarg
	);

unsigned PtGenListSetGflags(
	PtWidget_t *widget, unsigned gflags, unsigned mask
	);

void PtGenListHold( PtWidget_t *widget );
void PtGenListRelease( PtWidget_t *widget );

void PtGenListDamageItem( PtWidget_t *list, PtGenListItem_t *item );
void PtGenListLockItem( PtWidget_t *list, PtGenListItem_t *item );
void PtGenListUnlockItem( PtWidget_t *list, PtGenListItem_t *item );
void PtGenListResize( PtWidget_t *widget );

void PtGenListAddItems(
	PtWidget_t *list, PtGenListItem_t *items, PtGenListItem_t *after
	);

PtGenListItem_t *PtGenListRemoveItems(
	PtWidget_t *widget, PtGenListItem_t *first, PtGenListItem_t *last
	);

PtGenListItem_t *PtGenListItemRealloc(
	PtGenListItem_t *item, PtWidget_t *list, size_t size
	);

int PtGenListItemIndex(
	PtWidget_t const *list, PtGenListItem_t const *item
	);
	#pragma aux PtGenListItemIndex modify nomemory

void PtGenListShow( PtWidget_t *list, PtGenListItem_t *item );
void PtGenListShowPos( PtWidget_t *list, int pos );
void PtGenListGoto( PtWidget_t *list, PtGenListItem_t *item );
void PtGenListGotoPos( PtWidget_t *list, int pos );

void PtGenListClearSelection( PtWidget_t *widget );

PtGenListItem_t *PtGenListGetCurrent( PtWidget_t const *widget );
	#pragma aux PtGenListGetCurrent modify nomemory

void PtGenListSelect( PtWidget_t *widget, PtGenListItem_t *item );
void PtGenListUnselect( PtWidget_t *widget, PtGenListItem_t *item );

short PtGenListSelectedCount( PtWidget_t const *widget );
	#pragma aux PtGenListSelectedCount modify nomemory

unsigned short *PtGenListGetSelIndexes(
	PtWidget_t *widget, unsigned short *buffer
	);

int PtGenListSetSelIndexes(
	PtWidget_t *widget, const unsigned short *buffer, int count
	);

PtGenListItem_t **PtGenListSelectedItems(
	PtWidget_t *widget, PtGenListItem_t **buffer
	);

PtGenListItem_t **PtGenListAllItems(
	PtWidget_t *widget, PtGenListItem_t **buffer
	);

PhArea_t *PtGenListSetColumnBalloon( PhArea_t *area, PtListColumn_t const *col );

PtWidget_t *PtGenListCreateTextBalloon(
	PtWidget_t *widget, PtWidget_t *parent, const PhArea_t *area,
	const char *string, int column, const char *font
	);

void PtGenListDestroyBalloon( PtWidget_t *list );

const char *PtGenListFindColumnString(
	const char *string, int column, unsigned *length
	);

PtGenListItem_t *PtGenListFirstItem( PtWidget_t const *list );
	#pragma aux PtGenListFirstItem modify nomemory

PtGenListItem_t *PtGenListLastItem( PtWidget_t const *list );
	#pragma aux PtGenListLastItem modify nomemory

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
