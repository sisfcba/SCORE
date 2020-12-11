/*
 *	PtGroup.h
 *		Header file for the PtGroup widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_GROUP_H_INCLUDED
#define __PT_GROUP_H_INCLUDED

#ifndef __PT_CONTAINER_H_INCLUDED
 #include <photon/PtContainer.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/* 
 * PtGroup public
 */

extern PtWidgetClassRef_t *PtGroup;

/* Resources */
#define Pt_ARG_GROUP_FLAGS		 	Pt_RESOURCE( 11, 0 )
#define Pt_ARG_GROUP_HORZ_ALIGN	 	Pt_RESOURCE( 11, 1 )
#define Pt_ARG_GROUP_ORIENTATION	Pt_RESOURCE( 11, 2 )
#define Pt_ARG_GROUP_SPACING		Pt_RESOURCE( 11, 3 )
#define Pt_ARG_GROUP_VERT_ALIGN		Pt_RESOURCE( 11, 4 )
#define Pt_ARG_GROUP_ROWS_COLS	 	Pt_RESOURCE( 11, 5 )
#define Pt_ARG_GROUP_SPACING_X		Pt_RESOURCE( 11, 6 )
#define Pt_ARG_GROUP_SPACING_Y		Pt_RESOURCE( 11, 7 )

/* flag bits */
#define Pt_GROUP_EXCLUSIVE				0x00000001
#define Pt_GROUP_EQUAL_SIZE				0x00000002
#define Pt_GROUP_NO_SELECT_ALLOWED  	0x00000004
#define Pt_GROUP_NO_KEYS				0x00000008
#define Pt_GROUP_NO_KEY_WRAP_HORIZONTAL	0x00000010
#define Pt_GROUP_NO_KEY_WRAP_VERTICAL	0x00000020
#define Pt_GROUP_NO_KEY_WRAP			(Pt_GROUP_NO_KEY_WRAP_HORIZONTAL | Pt_GROUP_NO_KEY_WRAP_VERTICAL )
#define Pt_GROUP_EQUAL_SIZE_HORIZONTAL	0x00000100
#define Pt_GROUP_EQUAL_SIZE_VERTICAL	0x00000200
#define Pt_GROUP_STRETCH_HORIZONTAL		0x00000400
#define Pt_GROUP_STRETCH_VERTICAL		0x00000800
#define Pt_GROUP_STRETCH				(Pt_GROUP_STRETCH_VERTICAL|Pt_GROUP_STRETCH_HORIZONTAL)
#define Pt_GROUP_STRETCH_FILL			0x00001000


/* vertical alignment */
#define Pt_GROUP_VERT_NONE			-1
#define Pt_GROUP_VERT_CENTER		0
#define Pt_GROUP_VERT_TOP 			1
#define Pt_GROUP_VERT_BOTTOM		2

/* horizontal alignment */
#define Pt_GROUP_HORZ_NONE			-1
#define Pt_GROUP_HORZ_CENTER		0
#define Pt_GROUP_HORZ_LEFT			1
#define Pt_GROUP_HORZ_RIGHT			2

/* orientation */
#define Pt_GROUP_HORIZONTAL			0
#define Pt_GROUP_VERTICAL			1
#define Pt_GROUP_ASIS				2

/*
 * PtGroup private
 */

/* Widget structure */
typedef struct Pt_group_widget {
	PtContainerWidget_t			container;
	ulong_t						group_flags;
	ushort_t					orientation;
	ushort_t					spacing_x;
	ushort_t					vert_align;
	ushort_t					horz_align;
	ushort_t					number_of_opts; //matrix size
	ushort_t					spacing_y;
} PtGroupWidget_t;

/* Widget union */
typedef union Pt_group_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtGroupWidget_t				group;
} PtGroupUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
