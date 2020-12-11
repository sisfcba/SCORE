/*
 *	PtSeparator.h
 *		Header file for the PtSeparator widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_SEPARATOR_H_INCLUDED
#define __PT_SEPARATOR_H_INCLUDED

#ifndef __PT_BASIC_H_INCLUDED
 #include <photon/PtBasic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtSeparator public
 */

extern PtWidgetClassRef_t *PtSeparator;

/* Resources */
#define Pt_ARG_SEP_FLAGS				Pt_RESOURCE( 30, 0 )
#define Pt_ARG_SEP_ORIENTATION			Pt_RESOURCE( 30, 1 )
//depricated boolean --^ ... use flags.
#define Pt_ARG_SEP_TYPE					Pt_RESOURCE( 30, 2 )


/* Separator flags bits */
#define Pt_SEP_ORIENTATION	0x01

// Sep orientation flag bit meaning
#define Pt_SEP_HORIZONTAL		1 // default
#define Pt_SEP_VERTICAL			0 

/* Separator types */
#define Pt_SINGLE_LINE					0
#define Pt_DOUBLE_LINE					1
#define Pt_SINGLE_DASH_LINE				2
#define Pt_DOUBLE_DASH_LINE				3
#define Pt_ETCHED_IN					4
#define Pt_ETCHED_OUT					5
#define	Pt_NOLINE						6


/*
 * PtSeparator private
 */

/* Widget structure */
typedef struct Pt_separator_widget {
	PtBasicWidget_t				basic;
	ushort_t					flags;
	ushort_t					type;
} PtSeparatorWidget_t;

/* Widget union */
typedef union Pt_separator_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtSeparatorWidget_t			separator;
} PtSeparatorUnion_t;
#define Pt_SEP_HORIZONTAL_F		1


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
