/*
 *	PtImageTree.h
 *		Header file for the PtImageTree widget class
 *
 *  Copyright by QNX Software Systems Limited 1996. All rights reserved.
 */
#ifndef __PT_IMAGE_TREE_H_INCLUDED
#define __PT_IMAGE_TREE_H_INCLUDED

#ifndef __PT_TREE_H_INCLUDED
#include <photon/PtTree.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtImageTree public
 */

#define Pt_ARG_IMAGETREE_COLUMNS      Pt_RESOURCE( 49, 2 )
#define Pt_CB_IMAGETREE_COLUMN_SEL    Pt_RESOURCE( 49, 3 )

extern PtWidgetClassRef_t *const PtImageTree;

/* Tree item structure */

typedef struct Pt_image_tree_item {
	PtGenTreeItem_t	gen;
	int 			type;
	short 			set_img, unset_img;
	void 			*data;     //	user data, not used by the widget
	char 			string[1];	//	The actual string will be longer
} PtImageTreeItem_t;

/* Prototype for the Pt_ARG_TREE_BALLOON resource */

typedef PtWidget_t *PtImageTreeBalloonF_t( PtWidget_t *widget, 
				PtWidget_t *parent, PhArea_t *area, PtListColumn_t *column,
				PtImageTreeItem_t *item, int coln, const char *font );

typedef struct Pt_image_column {
	int type;
	short set_img, unset_img;
} PtImageColumn_t;

typedef struct Pt_image_tree_callback {
	unsigned 			sel_mode;
	PtImageTreeItem_t 	*item;
	unsigned 	nitems; // for SELECTION callbacks
	int 		expand; // for EXPANDING subtype STATE callbacks: put Pt_END here
						// to suppress expansion
	int 		click_count;
	int			column;
	int			state;
	PtImageColumn_t *imgcol;
} PtImageTreeCallback_t;

/*
 * PtImageTree private
 */

/* Widget structure */
typedef struct Pt_image_tree_widget {
	PtGenTreeWidget_t		gen;
	PhImage_t				*images;	/* Pt_ARG_TREE_IMAGES */
	short					img_count;	/* Pt_ARG_TREE_IMAGES .length */
	PtImageColumn_t			*image_columns; /* Pt_ARG_IMAGE_COLUMNS */
	short					img_col_count;	/* Pt_ARG_IMAGE_COLUMNS .length */
	short 					reserved;
	unsigned 				imgmask;	/* Pt_ARG_TREE_IMGMASK */
	PtCallbackList_t		*state_cb;	/* Pt_CB_TREE_STATE */
	PtCallbackList_t		*sel_cb;	/* Pt_CB_TREE_SELECTION */
	PtCallbackList_t		*imgcol_sel_cb;	/* Pt_CB_IMAGETREE_COLUMN_SEL */
	PtImageTreeBalloonF_t	*inflate_f;	/* Pt_ARG_TREE_BALLOON */
} PtImageTreeWidget_t;

/* Widget union */
typedef union Pt_image_tree_union {
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtGenListWidget_t		list;
	PtGenTreeWidget_t		gtree;
	PtImageTreeWidget_t		tree;
} PtImageTreeUnion_t;

int PtImageTreeAddImages( PtWidget_t *widget, PhImage_t const *images, int n );
int PtImageTreeAddImageColumns( PtWidget_t *widget, PtImageColumn_t const *cols, int n );

void PtImageTreeDamageItem( PtWidget_t *widget, PtImageTreeItem_t *item, PtListColumn_t const *col );

int PtImageTreeSetColumnState( PtImageTreeItem_t *item, int column, int state );
int PtImageTreeGetColumnState( PtImageTreeItem_t *item, int column );
int PtImageTreeSetColumnStateImage( PtImageTreeItem_t *item, int column, int state, int image );

PtImageTreeItem_t *PtImageTreeAllocItem(
	PtWidget_t const *tree, const char *string,
	short set_img, short unset_img
	);

PtImageTreeItem_t *PtImageTreeModifyItem(
	PtWidget_t *tree, PtImageTreeItem_t *item, const char *string,
	short sel_img, short unsel_img
	);

#ifdef __cplusplus

	inline PtImageTreeItem_t *PtImageTreeRootItem( PtWidget_t const *tree ) {
		return (PtImageTreeItem_t*) PtGenTreeRootItem( tree );
		}

	inline void PtImageTreeAddFirst(
			PtWidget_t *tree, PtImageTreeItem_t *items, PtImageTreeItem_t *parent
			) {
		PtGenTreeAddFirst( tree, &items->gen, &parent->gen );
		}

	inline void PtImageTreeAddAfter(
			PtWidget_t *tree, PtImageTreeItem_t *items, PtImageTreeItem_t *brother
			) {
		PtGenTreeAddAfter( tree, &items->gen, &brother->gen );
		}

	inline void PtImageTreeRemoveItem(
			PtWidget_t *tree, PtImageTreeItem_t *item
			) {
		PtGenTreeRemoveItem( tree, &item->gen );
		}

	inline void PtImageTreeRemoveList(
			PtWidget_t *tree, PtImageTreeItem_t *item
			) {
		PtGenTreeRemoveList( tree, &item->gen );
		}

	inline int PtImageTreeExpand(
			PtWidget_t *tree, PtImageTreeItem_t *item, PhEvent_t *event
			) {
		return PtGenTreeExpand( tree, &item->gen, event );
		}

	inline void PtImageTreeCollapse(
			PtWidget_t *tree, PtImageTreeItem_t *item, PhEvent_t *event
			) {
		PtGenTreeCollapse( tree, &item->gen, event );
		}

	inline void PtImageTreeFreeItems( PtImageTreeItem_t *item ) {
		PtGenTreeFreeItems( &item->gen );
		}

	inline void PtImageTreeFreeChildren( PtImageTreeItem_t *item ) {
		PtGenTreeFreeItems( PtGenTreeRemoveChildren( &item->gen ) );
		}

	inline int PtImageTreeItemIndex(
			const PtWidget_t *tree, const PtImageTreeItem_t *item
			) {
		return PtGenTreeItemIndex( tree, (PtGenTreeItem_t*) item );
	 	}

	inline void PtImageTreeClearSelection( PtWidget_t *widget ) {
		PtGenTreeClearSelection( widget );
		}

	inline int PtImageTreeShow( PtWidget_t *tree, PtImageTreeItem_t *item ) {
		return PtGenTreeShow( tree, (PtGenTreeItem_t*) item );
		}

	inline int PtImageTreeGoto( PtWidget_t *tree, PtImageTreeItem_t *item ) {
		return PtGenTreeGoto( tree, (PtGenTreeItem_t*) item );
		}

	inline unsigned short *PtImageTreeGetSelIndexes( PtWidget_t *widget, unsigned short *buffer ) {
		return PtGenTreeGetSelIndexes( widget, buffer );
		}

	inline int PtImageTreeSetSelIndexes( PtWidget_t *widget, const unsigned short *buffer, int n ) {
		return PtGenTreeSetSelIndexes( widget, buffer, n );
		}

	inline PtImageTreeItem_t **PtImageTreeSelectedItems( PtWidget_t *tree, PtImageTreeItem_t **buffer ) {
		return
			(PtImageTreeItem_t**)
				PtGenTreeSelectedItems( tree, (PtGenTreeItem_t**) buffer );
		}

	inline PtImageTreeItem_t **PtImageTreeAllItems( PtWidget_t *tree, PtImageTreeItem_t **buffer ) {
		return
			(PtImageTreeItem_t**)
				PtGenTreeAllItems( tree, (PtGenTreeItem_t**) buffer );
		}

	inline PtImageTreeItem_t *PtImageTreeGetCurrent( const PtWidget_t *widget ) {
		return (PtImageTreeItem_t*) PtGenTreeGetCurrent( widget );
		}

	inline void PtImageTreeSelect( PtWidget_t *tree, PtImageTreeItem_t *item ) {
		PtGenTreeSelect( tree, (PtGenTreeItem_t*) item );
		}

	inline void PtImageTreeUnselect( PtWidget_t *tree, PtImageTreeItem_t *item ) {
		PtGenTreeUnselect( tree, (PtGenTreeItem_t*) item );
		}

	inline void PtImageTreeUnselectNonBrothers(
			PtWidget_t *tree, PtImageTreeItem_t *item
			) {
		PtGenTreeUnselectNonBrothers( tree, (PtGenTreeItem_t*) item );
		}

	inline void PtImageTreeFreeAllItems( PtWidget_t *tree ) {
		PtGenTreeFreeAllItems( tree );
		}

#else

	#define PtImageTreeRootItem( tree ) \
		( (PtImageTreeItem_t*) PtGenTreeRootItem( tree ) )

	#define PtImageTreeAddFirst( tree, items, parent ) \
		PtGenTreeAddFirst( tree, \
			(PtGenTreeItem_t*)(items), (PtGenTreeItem_t*)(parent) \
			)

	#define PtImageTreeAddAfter( tree, items, brother ) \
		PtGenTreeAddAfter( tree, \
			(PtGenTreeItem_t*)(items), (PtGenTreeItem_t*)(brother) \
			)

	#define PtImageTreeRemoveItem( tree, item ) \
		PtGenTreeRemoveItem( tree, &(item)->gen )

	#define PtImageTreeRemoveList( tree, item ) \
		PtGenTreeRemoveList( tree, &(item)->gen )

	#define PtImageTreeExpand( tree, item, event ) \
		PtGenTreeExpand( tree, &(item)->gen, event )

	#define PtImageTreeCollapse( tree, item, event ) \
		PtGenTreeCollapse( tree, &(item)->gen, event )

	#define PtImageTreeFreeItems( item ) \
		PtGenTreeFreeItems( &(item)->gen );

	#define PtImageTreeFreeChildren( item ) \
		PtGenTreeFreeItems( \
			PtGenTreeRemoveChildren( (PtGenTreeItem_t*) (item) ) \
			)

	#define PtImageTreeItemIndex( tree, item ) \
		PtGenTreeItemIndex( tree, (PtGenTreeItem_t*)(item) )

	#define PtImageTreeClearSelection  PtGenTreeClearSelection

	#define PtImageTreeShow( tree, item ) \
		PtGenTreeShow( tree, (PtGenTreeItem_t*)(item) )

	#define PtImageTreeGoto( tree, item ) \
		PtGenTreeGoto( tree, (PtGenTreeItem_t*)(item) )

	#define PtImageTreeGetSelIndexes PtGenTreeGetSelIndexes

	#define PtImageTreeSetSelIndexes PtGenTreeSetSelIndexes

	#define PtImageTreeSelectedItems( tree, buffer ) \
		(	(PtImageTreeItem_t**) \
			PtGenTreeSelectedItems( tree, (PtGenTreeItem_t**)(buffer) ) \
			)

	#define PtImageTreeAllItems( tree, buffer ) \
		(	(PtImageTreeItem_t**) \
			PtGenTreeAllItems( tree, (PtGenTreeItem_t**)(buffer) ) \
			)

	#define PtImageTreeGetCurrent( tree ) \
		( (PtImageTreeItem_t*) PtGenTreeGetCurrent( tree ) )

	#define PtImageTreeSelect( tree, item ) \
		PtGenTreeSelect( tree, (PtGenTreeItem_t*) (item) )

	#define PtImageTreeUnselect( tree, item ) \
		PtGenTreeUnselect( tree, (PtGenTreeItem_t*) (item) )

	#define PtImageTreeUnselectNonBrothers( tree, item ) \
		PtGenTreeUnselectNonBrothers( tree, (PtGenTreeItem_t*) (item) )

	#define PtImageTreeFreeAllItems PtGenTreeFreeAllItems

#endif

const char *PtImageTreeFindColumnString(
		const char *string, int column, unsigned *length );

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
