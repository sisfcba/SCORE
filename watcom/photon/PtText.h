/*
 *	PtText.h
 *		Header file for the PtText widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_TEXT_H_INCLUDED
#define __PT_TEXT_H_INCLUDED

#ifndef __PT_LABEL_H_INCLUDED
 #include <photon/PtLabel.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtText public
 */

extern PtWidgetClassRef_t *PtText;

/* Resources */
#define Pt_ARG_COLUMNS				Pt_RESOURCE( 4, 1 )
#define Pt_ARG_CURSOR_POSITION		Pt_RESOURCE( 4, 3 )
#define Pt_ARG_EDIT_MASK			Pt_RESOURCE( 4, 4 )
#define Pt_ARG_MAX_LENGTH			Pt_RESOURCE( 4, 5 )
#define Pt_ARG_TEXT_FLAGS			Pt_RESOURCE( 4, 8 )
#define Pt_ARG_SELECTION_RANGE		Pt_RESOURCE( 4, 12 )
#define Pt_ARG_TEXT_SUBSTRING		Pt_RESOURCE( 4, 13 )
#define Pt_ARG_HIGHLIGHT_COLOR		Pt_RESOURCE( 4, 15 )
#define Pt_ARG_TEXT_HIGHLIGHT_TEXT_COLOR Pt_RESOURCE( 4, 16 )
#define Pt_ARG_TEXT_HIGHLIGHT_BACKGROUND_COLOR Pt_RESOURCE( 4, 17 )
#define Pt_ARG_TEXT_CURSOR_WIDTH Pt_RESOURCE( 4, 18 )
#define Pt_ARG_CURSOR_OFFSET		Pt_RESOURCE( 4, 19)

#define Pt_CB_MODIFY_VERIFY			Pt_RESOURCE( 4, 9 )
#define Pt_CB_TEXT_CHANGED			Pt_RESOURCE( 4, 10)
#define Pt_CB_MODIFY_NOTIFY			Pt_RESOURCE( 4, 10)
#define Pt_CB_MOTION_VERIFY			Pt_RESOURCE( 4, 11)
#define Pt_CB_MOTION_NOTIFY			Pt_RESOURCE( 4, 14)

//and for backwards compatability
#define Pt_CB_STRING_CHANGED		Pt_RESOURCE( 4, 10)


/* Flags bits */
#define Pt_CURSOR_VISIBLE			0x00000001 
#define Pt_EDITABLE					0x00000002
#define Pt_RESIZE_WIDTH				0x00000004
#define Pt_INSERT_MODE				0x00000008
#define Pt_TEXT_FULL				0x00000010
#define Pt_CHANGE_ACTIVATE			0x00000020
#define Pt_NO_RANGE_SELECTION		0x00000040
#define Pt_TEXT_AUTO_HIGHLIGHT		0x00000080

#define Pt_TEXT_RANGE_ACTIVE		0x40000000  // *** r/o ***
#define Pt_TEXT_CHANGED				0x80000000  // *** r/o ***

/* Callback structure */
typedef struct Pt_text_callback_t {
	int	start_pos, end_pos;	
	int	cur_insert, new_insert;
	int				length;	
	short			reserved;
	char *			text;
	int				doit;
} PtTextCallback_t;
typedef PtTextCallback_t PtTextControl_t;
typedef PtTextControl_t PtTextControlInfo_t;

/*** Reason Subtypes ***/
#define Pt_EDIT_ACTIVATE	1
//      Pt_CHANGE_ACTIVATE  2 ;defined in flags.

/*
 * PtText private
 */

// Widget data subtypes
#define Pt_TEXT_X1_RESOURCES	1
	typedef struct
		{
		PgColor_t highlight_background_color;
		PgColor_t highlight_text_color;
		char	cursor_width;
		} PtTextX1Resources_t;

/* Widget structure */
typedef struct Pt_text_widget {
	PtLabelWidget_t			label;
	short					columns;
	PhRect_t				cursor_offset;
	ulong_t					flags;
	int						max_length;
	int						scroll_pos;
	char					*mask;
	PtTextControlInfo_t		*control;
	PtCallbackList_t		*changed;
	PtCallbackList_t		*modify_verify;
	PtCallbackList_t		*motion_verify;
	PtCallbackList_t		*motion_notify;
	int (*highlight_range)( PtWidget_t *, PtCallbackInfo_t *);
	int (*modify_text)( PtWidget_t *, PtCallbackInfo_t *);
} PtTextWidget_t;

extern int PtTextGetSelection( PtWidget_t *, int *start, int *end );
extern int PtTextSetSelection( PtWidget_t *, int *start, int *end );
extern int PtTextModifyText( PtWidget_t *, int start, int end, int cur_insert, char const *text, int characters ); 

/* Widget union */
typedef union Pt_text_union {
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtLabelWidget_t			label;
	PtTextWidget_t			text;
} PtTextUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
