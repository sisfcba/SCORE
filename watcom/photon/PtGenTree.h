/*
 *	PtGenTree.h
 *		Header file for the PtGenTree widget class
 *
 *  Copyright by QNX Software Systems Limited 1996. All rights reserved.
 */
#ifndef __PT_GENTREE_H_INCLUDED
#define __PT_GENTREE_H_INCLUDED

#ifndef __PT_GENLIST_H_INCLUDED
 #include <photon/PtGenList.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtGenTree public
 */

extern PtWidgetClassRef_t *const PtGenTree;

#define Pt_ARG_TREE_FLAGS		Pt_RESOURCE( 23, 18 )
#define Pt_CB_GEN_TREE_INPUT	Pt_RESOURCE( 23, 23 )

/* Values for the Pt_ARG_TREE_FLAGS resource */
#define Pt_TREE_HAS_BUTTONS	0x0001
#define Pt_TREE_HAS_LINES	0x0002
#define Pt_TREE_ROOT_LINES	0x0004
#define Pt_TREE_TO_RIGHT	0x0008
#define Pt_TREE_TO_LEFT		0x0010

/* Pt_CB_GEN_TREE_INPUT callback structure */

typedef struct Pt_gentree_item PtGenTreeItem_t;

typedef struct Pt_gen_tree_input {
	PhPoint_t pos;
	PtGenTreeItem_t *item;
	unsigned index;
	int consumed;
	}
		PtGenTreeInput_t;

/* Values for the state_f function reason */
#define Pt_TREE_COLLAPSING	0
#define Pt_TREE_EXPANDING	1

/* GenTree item structure */

struct Pt_gentree_item {
	PtGenListItem_t	list;
	struct Pt_gentree_item *father, *son, *brother;
	PhDim_t dim;
	};

#define Pt_TREE_ITEM_EXPANDABLE	0x0040
#define Pt_TREE_ITEM_EXPANDED	0x0080
#define Pt_GEN_TREE_ITEM_USED_FLAGS	( Pt_LIST_ITEM_USED_FLAGS | 0x00C0 )

/*
 * PtGenTree private
 */

/* Widget structure */
typedef struct Pt_gentree_widget PtGenTreeWidget_t;

struct Pt_gentree_widget {
	PtGenListWidget_t		list;
	PtCallbackList_t		*input_cb;
	PtGenTreeItem_t			*root;
	unsigned				flags;
	};

/* Widget union */
typedef union Pt_gentree_union {
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtGenListWidget_t		list;
	PtGenTreeWidget_t		tree;
	}
		PtGenTreeUnion_t;

typedef void PtGenTreeDrawItemF_t(
	PtWidget_t *widget, PtGenTreeItem_t *item,
	PhRect_t const *where, int lmargin, int rmargin
	);

typedef int PtGenTreeItemStateF_t(
	PtWidget_t *widget, PtGenTreeItem_t *item,
	PhEvent_t *event, int reason
	);

typedef struct Pt_gen_tree_widget_class {
    PtGenListClass_t		list;
	PtGenTreeDrawItemF_t	*tree_draw_item_f;
	PtGenTreeItemStateF_t	*tree_state_f;
	}
		PtGenTreeClass_t;

#define Pt_SET_TREE_DRAW_F	Pt_ARG_IS_POINTER( PtGenTreeClass_t, tree_draw_item_f )
#define Pt_SET_TREE_STATE_F	Pt_ARG_IS_POINTER( PtGenTreeClass_t, tree_state_f )

void PtSuperClassGenTreeDrawItem(
	PtWidgetClassRef_t *cref, PtWidget_t *widget,
	PtGenTreeItem_t *item, PhRect_t const *where, int lmargin, int rmargin
	);

int PtSuperClassGenTreeItemState(
	PtWidgetClassRef_t *cref, PtWidget_t *widget,
	PtGenTreeItem_t *item, PhEvent_t *event, int reason
	);




/* Functions */

PtGenTreeItem_t *PtGenTreeRootItem( PtWidget_t const *tree );
#pragma aux PtGenTreeRootItem modify nomemory

PtGenTreeItem_t *PtGenTreeItemRealloc(
	PtGenTreeItem_t *item, PtWidget_t *tree, size_t newsize
	);

void PtGenTreeItemResize(
	PtGenTreeItem_t *item, PtWidget_t *tree
	);

void PtGenTreeResize( PtWidget_t *widget );

void PtGenTreeAddFirst(
	PtWidget_t *tree,			/* The PtGenTree widget */
	PtGenTreeItem_t *items,		/* Added items */
	PtGenTreeItem_t *parent		/* The item's new parent */
	);

void PtGenTreeAddAfter(
	PtWidget_t *tree,			/* The PtGenTree widget */
	PtGenTreeItem_t *items,		/* Added items */
	PtGenTreeItem_t *brother	/* Insert the item after this brother */
	);

void PtGenTreeRemoveItem(
	PtWidget_t *tree,			/* The PtGenTree widget */
	PtGenTreeItem_t *item		/* Item (or subtree) to be removed */
	);

void PtGenTreeRemoveList(
	PtWidget_t *tree,			/* The PtGenTree widget */
	PtGenTreeItem_t *item		/* First item (or subtree) to be removed */
	);

int PtGenTreeExpand(
	PtWidget_t *tree,			/* The PtGenTree widget */
	PtGenTreeItem_t *item,		/* Item (or subtree) to be expanded */
	PhEvent_t *event			/* Event that will be passed to callbacks */
	);

void PtGenTreeCollapse(
	PtWidget_t *tree,			/* The PtGenTree widget */
	PtGenTreeItem_t *item,		/* Item (or subtree) to be collapsed */
	PhEvent_t *event			/* Event that will be passed to callbacks */
	);

int PtGenTreeExpandParents(
	PtWidget_t *tree, PtGenTreeItem_t *item, PhEvent_t *event
	);

void PtGenTreeFreeItems( PtGenTreeItem_t *item );
void PtGenTreeFreeAllItems( PtWidget_t *tree );

PtGenTreeItem_t *PtGenTreeRemoveChildren( PtGenTreeItem_t *item );

void PtGenTreeUnselectNonBrothers( PtWidget_t *wgt, PtGenTreeItem_t *item );

int PtGenTreeShow( PtWidget_t *tree, PtGenTreeItem_t *item );

int PtGenTreeGoto( PtWidget_t *tree, PtGenTreeItem_t *item );

void PtGenTreeUnselect( PtWidget_t *tree, PtGenTreeItem_t *item );

void PtGenTreeSelect( PtWidget_t *tree, PtGenTreeItem_t *item );

int PtGenTreeItemIndex( const PtWidget_t *tree, const PtGenTreeItem_t *item );

#ifdef __cplusplus

	inline void PtGenTreeClearSelection( PtWidget_t *widget ) {
		PtGenListClearSelection( widget );
		}

	inline void PtGenTreeDamageItem(
			PtWidget_t *tree, PtGenTreeItem_t *item
			) {
		PtGenListDamageItem( tree, (PtGenListItem_t*) item );
		}

	inline unsigned short *PtGenTreeGetSelIndexes( PtWidget_t *tree, unsigned short *buffer ) {
		return PtGenListGetSelIndexes( tree, buffer );
		}

	inline int PtGenTreeSetSelIndexes( PtWidget_t *tree, unsigned short const *buffer, int n ) {
		return PtGenListSetSelIndexes( tree, buffer, n );
		}

	inline PtGenTreeItem_t **PtGenTreeSelectedItems( PtWidget_t *tree, PtGenTreeItem_t **buffer ) {
		return
			(PtGenTreeItem_t**)
				PtGenListSelectedItems( tree, (PtGenListItem_t**) buffer );
		}

	inline PtGenTreeItem_t **PtGenTreeAllItems( PtWidget_t *tree, PtGenTreeItem_t **buffer ) {
		return
			(PtGenTreeItem_t**)
				PtGenListAllItems( tree, (PtGenListItem_t**) buffer );
		}

	inline PtGenTreeItem_t *PtGenTreeGetCurrent( const PtWidget_t *widget ) {
		return (PtGenTreeItem_t*) PtGenListGetCurrent( widget );
		}

#else

	#define PtGenTreeClearSelection  PtGenListClearSelection

	#define PtGenTreeDamageItem( tree, item ) \
		PtGenListDamageItem( tree, (PtGenListItem_t*)(item) )

	#define PtGenTreeGetSelIndexes PtGenListGetSelIndexes

	#define PtGenTreeSetSelIndexes PtGenListSetSelIndexes

	#define PtGenTreeSelectedItems( tree, buffer ) \
		(	(PtGenTreeItem_t**) \
			PtGenListSelectedItems( tree, (PtGenListItem_t**)(buffer) ) \
			)

	#define PtGenTreeAllItems( tree, buffer ) \
		(	(PtGenTreeItem_t**) \
			PtGenListAllItems( tree, (PtGenListItem_t**)(buffer) ) \
			)

	#define PtGenTreeGetCurrent( tree ) \
		( (PtGenTreeItem_t*) PtGenListGetCurrent( tree ) )

#endif

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
