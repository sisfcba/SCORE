/*
 *	PtLabel.h
 *		Header file for the PtLabel widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_LABEL_H_INCLUDED
#define __PT_LABEL_H_INCLUDED

#ifndef __PT_BASIC_H_INCLUDED
 #include <photon/PtBasic.h>
#endif

#ifndef __PT_CONTAINER_H_INCLUDED
 #include <photon/PtContainer.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtLabel public
 */

extern PtWidgetClassRef_t *PtLabel;

/* Resources */
#define Pt_ARG_HORIZONTAL_ALIGNMENT	Pt_RESOURCE( 3, 0 )
#define Pt_ARG_LABEL_DATA			Pt_RESOURCE( 3, 1 )
#define Pt_ARG_LABEL_FLAGS			Pt_RESOURCE( 3, 2 )
#define Pt_ARG_LABEL_TYPE			Pt_RESOURCE( 3, 3 )
#define Pt_ARG_MARGIN_BOTTOM		Pt_RESOURCE( 3, 4 )
#define Pt_ARG_MARGIN_LEFT			Pt_RESOURCE( 3, 5 )
#define Pt_ARG_MARGIN_RIGHT			Pt_RESOURCE( 3, 6 )
#define Pt_ARG_MARGIN_TOP			Pt_RESOURCE( 3, 7 )
#define Pt_ARG_LINE_SPACING			Pt_RESOURCE( 3, 21 )

#define Pt_ARG_SELECT_SHIFT			Pt_RESOURCE( 3, 9 )
#define Pt_ARG_TEXT_FONT			Pt_RESOURCE( 3, 10 )
#define Pt_ARG_TEXT_STRING			Pt_RESOURCE( 3, 11 )
#define Pt_ARG_UNDERLINE1			Pt_RESOURCE( 3, 12 )
#define Pt_ARG_UNDERLINE2			Pt_RESOURCE( 3, 13 )
#define Pt_ARG_UNDERLINE_TYPE		Pt_RESOURCE( 3, 14 )
#define Pt_ARG_VERTICAL_ALIGNMENT	Pt_RESOURCE( 3, 15 )
#define Pt_ARG_BALLOON_POSITION		Pt_RESOURCE( 3, 16 )
#define Pt_ARG_LABEL_BALLOON		Pt_RESOURCE( 3, 17 )
#define Pt_ARG_ACCEL_KEY			Pt_RESOURCE( 3, 18 )

#define Pt_ARG_BALLOON_FILL_COLOR	Pt_RESOURCE( 3, 19 )
#define Pt_ARG_BALLOON_COLOR		Pt_RESOURCE( 3, 20 )

/* Alignment types */
#define	Pt_LEFT						0
#define	Pt_TOP						0
#define Pt_RIGHT					1
#define Pt_BOTTOM					1
#define Pt_CENTER					2

/* Underline types */
#define Pt_NO_ULINE					0
#define Pt_SINGLE_ULINE				1
#define Pt_DOUBLE_ULINE				2
#define Pt_ULINE_ETCHED_IN			3
#define Pt_ULINE_ETCHED_OUT			4

/* Label flag bits */

#define Pt_LABEL_SELECT_SHIFT		0x01
#define Pt_SHOW_BALLOON				0x04
#define Pt_BALLOON_AS_REQUIRED		0x08
#define Pt_BACKFILL_TEXT			0x10
#define Pt_USE_ELLIPSIS				0x20
#define Pt_BALLOON_REGISTERED		0x80 // (r/o)

/* Balloon Positions */
#define Pt_BALLOON_RIGHT	0
#define Pt_BALLOON_LEFT 	1
#define Pt_BALLOON_TOP		2
#define Pt_BALLOON_BOTTOM	3
#define Pt_BALLOON_INPLACE	4

/* Valid label types */
#define Pt_Z_STRING		0x01
#define Pt_BITMAP		0x02
#define Pt_IMAGE		0x04
#define Pt_TEXT_IMAGE	0x08

/*
 * PtLabel private
 */
#define Pt_POSITIONING 1


/* Widget structure */
typedef struct Pt_label_widget {
	PtBasicWidget_t				basic;
	PtWidget_t					*balloon_widget;
	ushort_t					balloon_pos;
	short 						reserved;
	uchar_t						h_alignment;
	uchar_t						v_alignment;
	uchar_t						flags;
	uchar_t						type;
	char						*font;
	char						*string;
	char						*accel_key;
	void						*data;
	ushort_t					margin_top;
	ushort_t					margin_bottom;
	ushort_t					margin_right;
	ushort_t					margin_left;
	ushort_t					twidth;
	ushort_t					theight;
	PgColor_t					uline1;
	PgColor_t					uline2;
	ushort_t					uline_type;
	short						ascender;
	PgColor_t					balloon_fill_color;
	PgColor_t					balloon_color;
	PtWidget_t					*(*inflate_f)( );
	short						line_spacing;
} PtLabelWidget_t;

/* Widget union */
typedef union Pt_label_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtLabelWidget_t				label;
} PtLabelUnion_t;

/* Proto's */
int PtLabelGetCharacterMetrics( PtLabelWidget_t *label, int character_offset, FontRender *metrics );
#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
