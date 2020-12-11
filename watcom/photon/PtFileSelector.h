/*
 *	PtFileSelector
 *		Header file for the PtFileSelector widget class
 *
 *  Copyright by QNX Software Systems Limited 1996. All rights reserved.
 */
#ifndef __PT_FILESELECTOR_H_INCLUDED
#define __PT_FILESELECTOR_H_INCLUDED

#ifndef __PT_GENTREE_H_INCLUDED
 #include <photon/PtGenTree.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t *const PtFileSelector;
// resources
#define Pt_ARG_FS_ROOT_DIR			Pt_RESOURCE( 47, 0 )
#define Pt_ARG_FS_IMAGES			Pt_RESOURCE( 47, 1 )
#define Pt_ARG_FS_FLAGS				Pt_RESOURCE( 47, 2 )
#define Pt_ARG_FS_REFRESH			Pt_RESOURCE( 47, 3 )
#define Pt_ARG_FS_TIMER_INITIAL		Pt_RESOURCE( 47, 4 )
#define Pt_ARG_FS_FILE_SPEC         Pt_RESOURCE( 47, 5 )
#define Pt_CB_FS_STATE				Pt_RESOURCE( 47, 6 )
#define Pt_CB_FS_SELECTION			Pt_RESOURCE( 47, 7 )

// PtFileSelector flags - fs_flags
#define	Pt_FS_SHOW_DIRS			0x1
#define	Pt_FS_SHOW_FILES		0x2
#define	Pt_FS_SHOW_HIDDEN		0x4
#define	Pt_FS_SHOW_ERRORS		0x8
#define	Pt_FS_FREE_ON_COLLAPSE	0x10
#define	Pt_FS_SINGLE_LEVEL		0x20
#define	Pt_FS_SEEK_KEY			0x30
#define Pt_FS_ALL_FLAGS		Pt_FS_SHOW_DIRS|Pt_FS_SHOW_FILES|Pt_FS_SHOW_HIDDEN|Pt_FS_SHOW_ERRORS|Pt_FS_FREE_ON_COLLAPSE|Pt_FS_SINGLE_LEVEL|Pt_FS_SEEK_KEY


// FileSelector item structure, see the below values
typedef struct Pt_fileselector_item
{
	PtGenTreeItem_t	gen;
	short opened;	// a value to say whether this dir was prevoiusly opened
	short type;		// a value to say whether this is a open dir, closed dir, file, link
	short root;		// a value to say whether this is the root item, 1 means it is
	char *fullpath;	// the fullpath of the item
} PtFileSelectorItem_t;

	// PtFileSelector directory values - opened - field
	#define Pt_FS_NEW_DIR	0	// dir has not been opened
	#define Pt_FS_OLD_DIR	1	// dir has been opened

	// PtFileSelector type value - type - field
	#define Pt_FS_DIR_OP	0
	#define Pt_FS_DIR_CL	1
	#define Pt_FS_DLINK_OP	2
	#define Pt_FS_DLINK_CL	3
	#define Pt_FS_FILE		4
	#define Pt_FS_FLINK		5
	#define Pt_FS_ERROR		6

// array of items to be displayed
struct dir_array
{	char *name;
	short type;
};

// FileSelector callback structure
typedef struct Pt_fileselector_callback 
{
	unsigned sel_mode;
    PtFileSelectorItem_t *item;
    unsigned nitems; // for SELECTION callbacks
    short reason;
} PtFileSelectorCallback_t;

// state callback subtypes
#define Pt_FS_STATE_START	1
#define Pt_FS_STATE_END		2

typedef struct {
    PtCallbackInfo_t cb;
    PtFileSelectorCallback_t fcb;
} fs_cb_struct;


/* Widget structure */
typedef struct Pt_fileselector_widget
{
	PtGenTreeWidget_t	gen;
	ulong_t 			fs_flags;
	char 				*root_path;
	char 				search_str[NAME_MAX + 1];
	char 				*file_spec;
	int					timer_initial;
	
	PtFileSelectorItem_t *refresh;
	PtCallbackList_t    *select_cb;
	PtCallbackList_t    *state_cb;
	PtWidget_t 			*timer;

	PhImage_t			*images[7];
	short 				img_count;
	long 				spare[4];
} PtFileSelectorWidget_t;


/* Widget union */
typedef union Pt_fileselector_union
{
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtGenListWidget_t		list;
	PtGenTreeWidget_t		gtree;
	PtFileSelectorWidget_t	fs;
} PtFileSelectorUnion_t;


// convenience functions, based on the gen-tree convenience functions
#define PtFSRootItem( fs ) \
    ( (PtFileSelectorItem_t*) PtGenTreeRootItem( (PtWidget_t *)fs ) )

#define PtFSAddFirst( fs, items, parent ) \
	PtGenTreeAddFirst( (PtWidget_t *)fs, (PtGenTreeItem_t *)(items), (PtGenTreeItem_t *)(parent))

#define PtFSAddAfter( fs, items, brother ) \
	PtGenTreeAddAfter( (PtWidget_t *)fs, (PtGenTreeItem_t *)(items), (PtGenTreeItem_t *)(brother))

#define PtFSAllItems( fs, buffer ) \
	( (PtFileSelectorItem_t**) PtGenTreeAllItems((PtWidget_t *)fs, (PtGenTreeItem_t**)(buffer)))

#define PtFSFolderExpand( fs, item, event ) \
	PtGenTreeExpand( (PtWidget_t *)fs, &(item)->gen, event )

#define PtFSFolderCollapse( fs, item, event ) \
	PtGenTreeCollapse( (PtWidget_t *)fs, &(item)->gen, event )

#define PtFSRemoveItem( fs, item ) \
    PtGenTreeRemoveItem( (PtWidget_t *)fs, &(item)->gen )

#define PtFSRemoveList( fs, item ) \
    PtGenTreeRemoveList( (PtWidget_t *)fs, &(item)->gen )

#define PtFSFreeItems( item ) \
    PtGenTreeFreeItems( &(item)->gen );

#define PtFSRemoveChildren( item ) \
    PtGenTreeFreeItems( PtGenTreeRemoveChildren( (PtGenTreeItem_t*) (item) ))

#define PtFSItemIndex( fs, item ) \
    PtGenTreeItemIndex( (PtWidget_t *)fs, (PtGenTreeItem_t*)(item) )

#define PtFSShow( fs, item ) \
    PtGenTreeShow( (PtWidget_t *)fs, (PtGenTreeItem_t*)(item) )

#define PtFSGoto( fs, item ) \
    PtGenTreeGoto( (PtWidget_t *)fs, (PtGenTreeItem_t*)(item) )

#define PtFSSelectedItems( fs, buffer ) \
    ((PtFileSelectorItem_t**) PtGenTreeSelectedItems( (PtWidget_t *)fs, (PtGenTreeItem_t**)(buffer) )) 

#define PtFSGetCurrent( fs ) \
    ( (PtFileSelectorItem_t*) PtGenTreeGetCurrent( (PtWidget_t *)fs ) )

#define PtFSSelect( fs, item ) \
    PtGenTreeSelect( (PtWidget_t *)fs, (PtGenTreeItem_t*) (item) )

#define PtFSUnselect( fs, item ) \
    PtGenTreeUnselect( (PtWidget_t *)fs, (PtGenTreeItem_t*) (item) )

#define PtFSUnselectNonBrothers( fs, item ) \
    PtGenTreeUnselectNonBrothers( (PtWidget_t *)fs, (PtGenTreeItem_t*) (item) )

#define PtFSExpandParents( fs, item, event ) \
    PtGenTreeExpandParents( (PtWidget_t *)fs, (PtGenTreeItem_t*) (item), event )

#define PtFSDamageItem( fs, item) \
    PtGenTreeDamageItem( (PtWidget_t *)fs, (PtGenTreeItem_t*) (item) )

#define PtFSFreeAllItems(fs) PtGenTreeFreeAllItems((PtWidget_t *) fs)

#define PtFSClearSelection(fs)  PtGenTreeClearSelection((PtWidget_t *) fs)

#define PtFSGetSelIndexes PtGenTreeGetSelIndexes

#define PtFSSetSelIndexes PtGenTreeSetSelIndexes

// PtFileSelection() function specifics

#define Pt_FSDIALOG_CANCEL 	1
#define Pt_FSDIALOG_OPEN 	2

#define Pt_FSDIALOG_NO_FCHECK	0x1
#define Pt_FSDIALOG_NO_FSPEC	0x4

struct fs_dialog_modal
{
	int finish;
	int ret;
	int flags;
	char *path;
};

struct fs_dialog_modal PtFileSelection(PtWidget_t *parent, PhPoint_t *pos, \
	char *title, char *root_dir, char *file_spec, char *btn1, char *btn2, int flags);


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
