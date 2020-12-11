/*
 *	PtFileSel
 *		Header file for the PtFileSel widget class
 *
 *  Copyright by QNX Software Systems Limited 1996. All rights reserved.
 */
#ifndef __PT_FILESEL_H_INCLUDED
#define __PT_FILESEL_H_INCLUDED

#ifndef __PT_GENTREE_H_INCLUDED
 #include <photon/PtGenTree.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t *const PtFileSel;

// resources
#define Pt_ARG_FS_ROOT_DIR			Pt_RESOURCE( 47, 0 )
#define Pt_ARG_FS_IMAGES			Pt_RESOURCE( 47, 1 )
#define Pt_ARG_FS_FLAGS				Pt_RESOURCE( 47, 2 )
#define Pt_ARG_FS_REFRESH			Pt_RESOURCE( 47, 3 )
#define Pt_ARG_FS_FILE_SPEC         Pt_RESOURCE( 47, 4 )
#define Pt_ARG_FS_FORMAT		    Pt_RESOURCE( 47, 5 )
#define Pt_CB_FS_STATE				Pt_RESOURCE( 47, 6 )
#define Pt_CB_FS_SELECTION			Pt_RESOURCE( 47, 7 )
#define Pt_CB_FS_BKGD_HANDLER	    Pt_RESOURCE( 47, 8 )

// PtFileSel flags - fs_flags
#define	Pt_FS_SHOW_DIRS				0x1		// display directories
#define	Pt_FS_SHOW_FILES			0x2		// display files
#define	Pt_FS_SHOW_HIDDEN			0x4		// display hidden files/dirs
#define	Pt_FS_SHOW_ERRORS			0x8		// display errored files/dirs
#define	Pt_FS_FREE_ON_COLLAPSE		0x10	// display free items on a collapse
#define	Pt_FS_SINGLE_LEVEL			0x20	// display in a single level not a tree
#define	Pt_FS_SEEK_KEY				0x40	// display allow keyboard seeking
#define	Pt_FS_NO_ROOT_DISPLAY		0x80	// do not show the root item
#define Pt_FS_ALL_FLAGS		Pt_FS_SHOW_DIRS|Pt_FS_SHOW_FILES|Pt_FS_SHOW_HIDDEN|Pt_FS_SHOW_ERRORS|Pt_FS_FREE_ON_COLLAPSE|Pt_FS_SINGLE_LEVEL|Pt_FS_SEEK_KEY


// FileSel item structure, see the below values
typedef struct Pt_filesel_item
{
	PtGenTreeItem_t	gen;
	short opened;	// a value to say whether this dir was prevoiusly opened
	short type;		// a value to say whether this is a open dir, closed dir, file, link
	short root;		// a value to say whether this is the root item, 1 means it is
	char *fullpath;	// the fullpath of the item
	char *otherinfo;	
	int tag;		// TAG, DO NOT USE
} PtFileSelItem_t;

	// PtFileSel directory values - opened - field
	#define Pt_FS_NEW_DIR	0	// dir has not been opened
	#define Pt_FS_OLD_DIR	1	// dir has been opened

	// PtFileSel type value - type - field
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
	char *otherinfo;
	short type;
};

// FileSel callback structure
typedef struct Pt_filesel_callback 
{
	unsigned sel_mode;
    PtFileSelItem_t *item;
    unsigned nitems; // for SELECTION callbacks
    short reason;
} PtFileSelCallback_t;

typedef struct Pt_fileselbkgd_callback
{
    char *name;
    long spare[2];
} PtFileSelBkgdCallback_t;

typedef struct Pt_fileselection_info 
{
	short ret;
	char path[PATH_MAX + NAME_MAX + 1];
	PhDim_t dim;
	PhPoint_t pos;
	char format[80];
	char fspec[80];
} PtFileSelectionInfo_t;

// state callback subtypes
#define Pt_FS_STATE_START	1
#define Pt_FS_STATE_END		2

// bkgd callback subtypes
#define Pt_FS_NEW_ITEM 1
#define Pt_FS_OLD_ITEM -1

typedef struct {
    PtCallbackInfo_t cb;
    PtFileSelCallback_t fcb;
} fs_cb_struct;


/* Widget structure */
typedef struct Pt_filesel_widget
{
	PtGenTreeWidget_t	gen;
	ulong_t 			fs_flags;	// file selector flags
	char 				*root_path; // the root path or startng path
	char 				*file_spec; // file spec for file display
	
	PtFileSelItem_t 	*refresh; // item to be refreshed
	PtCallbackList_t    *select_cb; // select callback
	PtCallbackList_t    *state_cb; // state callback
	PtCallbackList_t    *handler_cb; // background handler callback
	PhImage_t			*images[7]; // images to diplay in the widget

	// internal stuff
	PtWidget_t 			*divider;
	PtWidget_t 			*lbl1, *lbl2, *lbl3, *lbl4, *lbl5, *lbl6;
	char 				*format;
	char 				*full_format;
	char 				*pat[10];
	short				pat_ctr;

	short 				img_count;
	int 				user_divider;
	long 				spare[3];

	// caching for the uid and gid, to speed up lookups
	char *gcache, *ocache;
	short uid_cache, gid_cache;
} PtFileSelWidget_t;


/* Widget union */
typedef union Pt_FileSel_union
{
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtGenListWidget_t		list;
	PtGenTreeWidget_t		gtree;
	PtFileSelWidget_t	fs;
} PtFileSelUnion_t;


// convenience functions, based on the gen-tree convenience functions
#define PtFSRootItem( fs ) \
    ( (PtFileSelItem_t*) PtGenTreeRootItem( (PtWidget_t *)fs ) )

#define PtFSAddFirst( fs, items, parent ) \
	PtGenTreeAddFirst( (PtWidget_t *)fs, (PtGenTreeItem_t *)(items), (PtGenTreeItem_t *)(parent))

#define PtFSAddAfter( fs, items, brother ) \
	PtGenTreeAddAfter( (PtWidget_t *)fs, (PtGenTreeItem_t *)(items), (PtGenTreeItem_t *)(brother))

#define PtFSAllItems( fs, buffer ) \
	( (PtFileSelItem_t**) PtGenTreeAllItems((PtWidget_t *)fs, (PtGenTreeItem_t**)(buffer)))

#define PtFSFolderExpand( fs, item, event ) \
	PtGenTreeExpand( (PtWidget_t *)fs, &(item)->gen, event )

#define PtFSFolderCollapse( fs, item, event ) \
	PtGenTreeCollapse( (PtWidget_t *)fs, &(item)->gen, event )

#define PtFSRemoveItem( fs, item ) \
    PtGenTreeRemoveItem( (PtWidget_t *)fs, &(item)->gen )

#define PtFSRemoveList( fs, item ) \
    PtGenTreeRemoveList( (PtWidget_t *)fs, &(item)->gen )

#define PtFSRemoveChildren( item ) \
    ( (PtFileSelItem_t*) PtGenTreeRemoveChildren( (PtGenTreeItem_t*) (item) ) )
//    PtFSFreeItems( PtGenTreeRemoveChildren( (PtGenTreeItem_t*) (item) ))

#define PtFSItemIndex( fs, item ) \
    PtGenTreeItemIndex( (PtWidget_t *)fs, (PtGenTreeItem_t*)(item) )

#define PtFSShow( fs, item ) \
    PtGenTreeShow( (PtWidget_t *)fs, (PtGenTreeItem_t*)(item) )

#define PtFSGoto( fs, item ) \
    PtGenTreeGoto( (PtWidget_t *)fs, (PtGenTreeItem_t*)(item) )

#define PtFSSelectedItems( fs, buffer ) \
    ((PtFileSelItem_t**) PtGenTreeSelectedItems( (PtWidget_t *)fs, (PtGenTreeItem_t**)(buffer) )) 

#define PtFSGetCurrent( fs ) \
    ( (PtFileSelItem_t*) PtGenTreeGetCurrent( (PtWidget_t *)fs ) )

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

#define PtFSClearSelection(fs)  PtGenTreeClearSelection((PtWidget_t *) fs)

#define PtFSGetSelIndexes PtGenTreeGetSelIndexes

#define PtFSSetSelIndexes PtGenTreeSetSelIndexes

PtFileSelItem_t * PtFSAllocItem(PtWidget_t *fs, int type, char const *info);
void PtFSFreeItems( PtFileSelItem_t *item );
void PtFSFreeAllItems( PtWidget_t *const widget );

// PtFileSelection() function specifics

#define Pt_FSDIALOG_BTN2 	1
#define Pt_FSDIALOG_BTN1 	2

#define Pt_FSDIALOG_NO_FCHECK		0x1
#define Pt_FSDIALOG_NO_FSPEC		0x2
#define Pt_FSDIALOG_NO_UP_BUTTON	0x4
#define Pt_FSDIALOG_SHOW_HIDDEN		0x8
#define Pt_FSDIALOG_NO_DIRS         0x10
#define Pt_FSDIALOG_NO_FILES        0x20

int PtFileSelection(PtWidget_t *parent, PhPoint_t const *pos,
	char const *title, char const *root_dir, char const *file_spec, char const *btn1, char const *btn2, char const *format,
	PtFileSelectionInfo_t *info, int flags);


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
