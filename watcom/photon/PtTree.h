/*
 *	PtTree.h
 *		Header file for the PtTree widget class
 *
 *  Copyright by QNX Software Systems Limited 1996. All rights reserved.
 */
#ifndef __PT_TREE_H_INCLUDED
#define __PT_TREE_H_INCLUDED

#ifndef __PT_GENTREE_H_INCLUDED
 #include <photon/PtGenTree.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtTree public
 */

extern PtWidgetClassRef_t *const PtTree;

#define Pt_ARG_TREE_IMAGES			Pt_RESOURCE( 23, 19 )
#define Pt_ARG_TREE_IMGMASK			Pt_RESOURCE( 23, 20 )
#define Pt_ARG_TREE_BALLOON			Pt_RESOURCE( 23, 30 )
#define Pt_CB_TREE_STATE			Pt_RESOURCE( 23, 21 )
#define Pt_CB_TREE_SELECTION		Pt_RESOURCE( 23, 22 )

/* Some new flags for the Pt_ARG_TREE_FLAGS resource */
#define Pt_TREE_BALLOON_ON_IMAGE	0x0100
#define Pt_TREE_BALLOON_ON_TREE		0x0200

/* Tree item structure */

typedef struct Pt_tree_item {
	PtGenTreeItem_t	gen;
	short set_img, unset_img;
	void *data;     //	user data, not used by the widget
	char string[1];	//	The actual string will be longer
	}
		PtTreeItem_t;


#define Pt_TREE_ITEM_USED_FLAGS Pt_GEN_TREE_ITEM_USED_FLAGS

/* Prototype for the Pt_ARG_TREE_BALLOON resource */

typedef PtWidget_t *PtTreeBalloonF_t(
	PtWidget_t *widget, PtWidget_t *parent,
	PhArea_t *area, PtListColumn_t *column,
	PtTreeItem_t *item, int coln, const char *font
	);

typedef struct Pt_tree_callback {
	unsigned sel_mode;
	PtTreeItem_t *item;
	unsigned nitems; // for SELECTION callbacks
	int expand; // for EXPANDING subtype STATE callbacks: put Pt_END here
				// to suppress expansion
	int click_count;
	}
		PtTreeCallback_t;

/*
 * PtTree private
 */

/* Widget structure */
typedef struct Pt_tree_widget {
	PtGenTreeWidget_t	gen;
	PhImage_t			*images;	/* Pt_ARG_TREE_IMAGES */
	short				img_count;	/* Pt_ARG_TREE_IMAGES .length */
	short 				reserved;
	unsigned 			imgmask;	/* Pt_ARG_TREE_IMGMASK */
	PtCallbackList_t	*state_cb;	/* Pt_CB_TREE_STATE */
	PtCallbackList_t	*sel_cb;	/* Pt_CB_TREE_SELECTION */
	PtTreeBalloonF_t	*inflate_f;	/* Pt_ARG_TREE_BALLOON */
	}
		PtTreeWidget_t;

/* Widget union */
typedef union Pt_tree_union {
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtGenListWidget_t		list;
	PtGenTreeWidget_t		gtree;
	PtTreeWidget_t			tree;
	}
		PtTreeUnion_t;

int PtTreeAddImages( PtWidget_t *widget, PhImage_t const *images, int n );

PtTreeItem_t *PtTreeAllocItem(
	PtWidget_t const *tree, const char *string,
	short set_img, short unset_img
	);

PtTreeItem_t *PtTreeModifyItem(
	PtWidget_t *tree, PtTreeItem_t *item, const char *string,
	short sel_img, short unsel_img
	);

#ifdef __cplusplus

	inline PtTreeItem_t *PtTreeRootItem( PtWidget_t const *tree ) {
		return (PtTreeItem_t*) PtGenTreeRootItem( tree );
		}

	inline void PtTreeAddFirst(
			PtWidget_t *tree, PtTreeItem_t *items, PtTreeItem_t *parent
			) {
		PtGenTreeAddFirst( tree, &items->gen, &parent->gen );
		}

	inline void PtTreeAddAfter(
			PtWidget_t *tree, PtTreeItem_t *items, PtTreeItem_t *brother
			) {
		PtGenTreeAddAfter( tree, &items->gen, &brother->gen );
		}

	inline void PtTreeRemoveItem(
			PtWidget_t *tree, PtTreeItem_t *item
			) {
		PtGenTreeRemoveItem( tree, &item->gen );
		}

	inline void PtTreeRemoveList(
			PtWidget_t *tree, PtTreeItem_t *item
			) {
		PtGenTreeRemoveList( tree, &item->gen );
		}

	inline int PtTreeExpand(
			PtWidget_t *tree, PtTreeItem_t *item, PhEvent_t *event
			) {
		return PtGenTreeExpand( tree, &item->gen, event );
		}

	inline void PtTreeCollapse(
			PtWidget_t *tree, PtTreeItem_t *item, PhEvent_t *event
			) {
		PtGenTreeCollapse( tree, &item->gen, event );
		}

	inline void PtTreeFreeItems( PtTreeItem_t *item ) {
		PtGenTreeFreeItems( &item->gen );
		}

	inline void PtTreeFreeChildren( PtTreeItem_t *item ) {
		PtGenTreeFreeItems( PtGenTreeRemoveChildren( &item->gen ) );
		}

	inline int PtTreeItemIndex(
			const PtWidget_t *tree, const PtTreeItem_t *item
			) {
		return PtGenTreeItemIndex( tree, (PtGenTreeItem_t*) item );
	 	}

	inline void PtTreeClearSelection( PtWidget_t *widget ) {
		PtGenTreeClearSelection( widget );
		}

	inline int PtTreeShow( PtWidget_t *tree, PtTreeItem_t *item ) {
		return PtGenTreeShow( tree, (PtGenTreeItem_t*) item );
		}

	inline int PtTreeGoto( PtWidget_t *tree, PtTreeItem_t *item ) {
		return PtGenTreeGoto( tree, (PtGenTreeItem_t*) item );
		}

	inline unsigned short *PtTreeGetSelIndexes( PtWidget_t *widget, unsigned short *buffer ) {
		return PtGenTreeGetSelIndexes( widget, buffer );
		}

	inline int PtTreeSetSelIndexes( PtWidget_t *widget, const unsigned short *buffer, int n ) {
		return PtGenTreeSetSelIndexes( widget, buffer, n );
		}

	inline PtTreeItem_t **PtTreeSelectedItems( PtWidget_t *tree, PtTreeItem_t **buffer ) {
		return
			(PtTreeItem_t**)
				PtGenTreeSelectedItems( tree, (PtGenTreeItem_t**) buffer );
		}

	inline PtTreeItem_t **PtTreeAllItems( PtWidget_t *tree, PtTreeItem_t **buffer ) {
		return
			(PtTreeItem_t**)
				PtGenTreeAllItems( tree, (PtGenTreeItem_t**) buffer );
		}

	inline PtTreeItem_t *PtTreeGetCurrent( const PtWidget_t *widget ) {
		return (PtTreeItem_t*) PtGenTreeGetCurrent( widget );
		}

	inline void PtTreeSelect( PtWidget_t *tree, PtTreeItem_t *item ) {
		PtGenTreeSelect( tree, (PtGenTreeItem_t*) item );
		}

	inline void PtTreeUnselect( PtWidget_t *tree, PtTreeItem_t *item ) {
		PtGenTreeUnselect( tree, (PtGenTreeItem_t*) item );
		}

	inline void PtTreeUnselectNonBrothers(
			PtWidget_t *tree, PtTreeItem_t *item
			) {
		PtGenTreeUnselectNonBrothers( tree, (PtGenTreeItem_t*) item );
		}

	inline void PtTreeFreeAllItems( PtWidget_t *tree ) {
		PtGenTreeFreeAllItems( tree );
		}

	inline PtTreeItem_t *PtTreeRemoveChildren( PtTreeItem_t *item ) {
		return (PtTreeItem_t*) PtGenTreeRemoveChildren( (PtGenTreeItem_t*) item );
		}

#else

	#define PtTreeRootItem( tree ) \
		( (PtTreeItem_t*) PtGenTreeRootItem( tree ) )

	#define PtTreeAddFirst( tree, items, parent ) \
		PtGenTreeAddFirst( tree, \
			(PtGenTreeItem_t*)(items), (PtGenTreeItem_t*)(parent) \
			)

	#define PtTreeAddAfter( tree, items, brother ) \
		PtGenTreeAddAfter( tree, \
			(PtGenTreeItem_t*)(items), (PtGenTreeItem_t*)(brother) \
			)

	#define PtTreeRemoveItem( tree, item ) \
		PtGenTreeRemoveItem( tree, &(item)->gen )

	#define PtTreeRemoveList( tree, item ) \
		PtGenTreeRemoveList( tree, &(item)->gen )

	#define PtTreeExpand( tree, item, event ) \
		PtGenTreeExpand( tree, &(item)->gen, event )

	#define PtTreeCollapse( tree, item, event ) \
		PtGenTreeCollapse( tree, &(item)->gen, event )

	#define PtTreeFreeItems( item ) \
		PtGenTreeFreeItems( &(item)->gen );

	#define PtTreeFreeChildren( item ) \
		PtGenTreeFreeItems( \
			PtGenTreeRemoveChildren( (PtGenTreeItem_t*) (item) ) \
			)

	#define PtTreeItemIndex( tree, item ) \
		PtGenTreeItemIndex( tree, (PtGenTreeItem_t*)(item) )

	#define PtTreeClearSelection  PtGenTreeClearSelection

	#define PtTreeShow( tree, item ) \
		PtGenTreeShow( tree, (PtGenTreeItem_t*)(item) )

	#define PtTreeGoto( tree, item ) \
		PtGenTreeGoto( tree, (PtGenTreeItem_t*)(item) )

	#define PtTreeGetSelIndexes PtGenTreeGetSelIndexes

	#define PtTreeSetSelIndexes PtGenTreeSetSelIndexes

	#define PtTreeSelectedItems( tree, buffer ) \
		(	(PtTreeItem_t**) \
			PtGenTreeSelectedItems( tree, (PtGenTreeItem_t**)(buffer) ) \
			)

	#define PtTreeAllItems( tree, buffer ) \
		(	(PtTreeItem_t**) \
			PtGenTreeAllItems( tree, (PtGenTreeItem_t**)(buffer) ) \
			)

	#define PtTreeGetCurrent( tree ) \
		( (PtTreeItem_t*) PtGenTreeGetCurrent( tree ) )

	#define PtTreeSelect( tree, item ) \
		PtGenTreeSelect( tree, (PtGenTreeItem_t*) (item) )

	#define PtTreeUnselect( tree, item ) \
		PtGenTreeUnselect( tree, (PtGenTreeItem_t*) (item) )

	#define PtTreeUnselectNonBrothers( tree, item ) \
		PtGenTreeUnselectNonBrothers( tree, (PtGenTreeItem_t*) (item) )

	#define PtTreeFreeAllItems PtGenTreeFreeAllItems

	#define PtTreeRemoveChildren( item ) \
		(	(PtTreeItem_t*) \
			PtGenTreeRemoveChildren( (PtGenTreeItem_t*) (item) ) \
			)

#endif


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
