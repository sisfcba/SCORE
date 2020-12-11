/*
 *	PtList.h
 *		Header file for the PtList widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1996. All rights reserved.
 */
#ifndef __PT_LIST_H_INCLUDED
#define __PT_LIST_H_INCLUDED

#ifndef __PT_GENLIST_H_INCLUDED
 #include <photon/PtGenList.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtList public
 */

extern PtWidgetClassRef_t *const PtList;

/* Resources */
#define Pt_ARG_ITEMS				Pt_RESOURCE( 23,  1 )
#define Pt_ARG_LIST_SPACING			Pt_RESOURCE( 23,  4 )
#define Pt_ARG_SELECTION_INDEXES	Pt_RESOURCE( 23,  6 )
#define Pt_ARG_LIST_BALLOON			Pt_RESOURCE( 23, 31 )
#define Pt_CB_SELECTION				Pt_RESOURCE( 23, 10 )
#define Pt_CB_LIST_INPUT			Pt_RESOURCE( 23, 24 )

// 		         ||-----deprecated
#define Pt_ARG_SEL_INDEXES			Pt_RESOURCE( 23,  6 )
#define Pt_ARG_SEL_MODE				Pt_RESOURCE( 23,  7 )
#define Pt_ARG_SCROLLBAR			Pt_RESOURCE( 23, 11 )
// 		         ^^-----deprecated

#define Pt_ARG_MODIFY_ITEMS			Pt_RESOURCE( 23, 29 )

/* Prototype for the Pt_ARG_LIST_BALLOON resource */

typedef PtWidget_t *PtListBalloonF_t(
	PtWidget_t *widget, PtWidget_t *parent,
	PhArea_t *area, PtListColumn_t const *col, int coln,
	const char *item, unsigned index, const char *font
	);

/* Callback structures */
typedef struct Pt_list_callback {
	unsigned	mode;
	char *      item;           /* selected item            */
	int         item_len;       /* length of selection item */
	int         item_pos;       /* item position in array   */
	char **     sel_items;   	/* selected item list       */
	ushort_t *  sel_array;		/* array of selected postns */
	int         sel_item_count; /* count of selected items  */
	char		selection_type; /* initial, modification, or addition */
	short		click_count;
	}
		PtListCallback_t;

typedef struct Pt_list_input {
	PhPoint_t pos;
	char *item;
	unsigned index;
	int consumed;
	}
		PtListInput_t;

/*
 *	Resource control structure
 */

typedef struct Pt_list_modify_items_ctrl {
	unsigned short nitems;
	unsigned short position;
	void const *old_items;
	const char **new_items;
	int result;
	}
		PtListModifyItems_t;

/* Values for "len" in Pt_ARG_MODIFY_ITEMS */
#define Pt_LIST_REMOVE_ALL_ITEMS		 0
#define Pt_LIST_INSERT_ITEMS			 1
#define Pt_LIST_MOD_STRINGS				 2
#define Pt_LIST_MOD_RANGE				 3
#define Pt_LIST_MOD_SHORT_POSITIONS		 4
#define Pt_LIST_MOD_LONG_POSITIONS		 5
#define Pt_LIST_FIND_STRING				 6
#define Pt_LIST_SELECT_POS				 7
#define Pt_LIST_UNSELECT_POS			 8
#define Pt_LIST_SHOW_POS				 9
#define Pt_LIST_GOTO_POS				10

/*
 * PtList private
 */

/* Widget structure */
typedef struct Pt_list_widget {
	PtGenListWidget_t		glist;
	char					**items,
							**sel_items;
	unsigned short			*sel_arr;
	PtCallbackList_t        *selection;
	PtCallbackList_t        *input;
	unsigned short			spacing,
							visible_count;
	PtListBalloonF_t		*inflate_f;	/* Pt_ARG_LIST_BALLOON */
	}
		PtListWidget_t;

/* Widget union */
typedef union Pt_list_union {
	PtWidget_t			core;
	PtBasicWidget_t		basic;
	PtGenListWidget_t	glist;
	PtListWidget_t		list;
	}
		PtListUnion_t;

int PtListAddItems(
	PtWidget_t *widget, const char **items, int item_count, unsigned int position
	);

int PtListItemPos( PtWidget_t *widget, const char *string );

int PtListItemExists( PtWidget_t *widget, const char *string );

int PtListReplaceItemPos(
	PtWidget_t *widget, const char **new_items, int item_count, int position
	);

int PtListReplaceItems(
	PtWidget_t *widget, const char **old_items, const char **new_items, int item_count
	);

int PtListDeleteItems( PtWidget_t *widget, const char **items, int item_count );

int PtListDeletePositions( /* Deprecated */
	PtWidget_t *widget, const int *pos_list, int pos_count
	);

int PtListRemovePositions(
	PtWidget_t *widget, const unsigned short *pos_list, int pos_count
	);

int PtListDeleteItemPos(
	PtWidget_t *widget, int item_count, int position
	);

int PtListDeleteAllItems( PtWidget_t *widget );

void PtListSelectPos( PtWidget_t *widget, int pos );
void PtListUnselectPos( PtWidget_t *widget, int pos );

void PtListShowPos( PtWidget_t *widget, int pos );
void PtListGotoPos( PtWidget_t *widget, int pos );

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
