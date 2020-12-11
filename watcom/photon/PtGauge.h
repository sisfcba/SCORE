/*
 *	PtGauge.h
 *		Header file for the PtGauge widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */

#ifndef __PT_GAUGE_H_INCLUDED
#define __PT_GAUGE_H_INCLUDED

#ifndef __PT_BASIC_H_INCLUDED
 #include <photon/PtBasic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtGauge public
 */

extern PtWidgetClassRef_t *PtGauge;

/* Resources */
#define Pt_ARG_GAUGE_FLAGS			Pt_RESOURCE( 21, 0 )
#define Pt_ARG_GAUGE_FONT			Pt_RESOURCE( 21, 1 )
#define Pt_ARG_GAUGE_MINIMUM		Pt_RESOURCE( 21, 2 )
#define Pt_ARG_GAUGE_MAXIMUM		Pt_RESOURCE( 21, 3 )
#define Pt_ARG_GAUGE_VALUE			Pt_RESOURCE( 21, 4 )
#define Pt_ARG_GAUGE_ORIENTATION	Pt_RESOURCE( 21, 5 )
#define Pt_ARG_GAUGE_VALUE_PREFIX	Pt_RESOURCE( 21, 6 )
#define Pt_ARG_GAUGE_VALUE_SUFFIX	Pt_RESOURCE( 21, 7 )
#define Pt_ARG_GAUGE_H_ALIGN		Pt_RESOURCE( 21, 8 )
#define Pt_ARG_GAUGE_V_ALIGN		Pt_RESOURCE( 21, 9 )

/* Orientation related */
#define Pt_VERTICAL					0
#define Pt_HORIZONTAL				1

/* Alignment types */
#define	Pt_LEFT						0
#define	Pt_TOP						0
#define Pt_RIGHT					1
#define Pt_BOTTOM					1
#define Pt_CENTER					2

/* Possible flags */
/* direction related */
#define Pt_GAUGE_MAX_ON_TOP			0
#define Pt_GAUGE_MAX_ON_RIGHT		0
#define Pt_GAUGE_MAX_ON_LEFT		1
#define Pt_GAUGE_MAX_ON_BOTTOM		1

/* display related */
#define Pt_SHOW_VALUE				0x10
#define Pt_VALUE_XOR				0x20

typedef struct Pt_gauge_widget {
	PtBasicWidget_t     basic;
	long                value;
	long                maximum;
	long                minimum;
	ushort_t			flags;
	char				orientation;
	char				reserved;
	char				*font;
	char				*suffix;
	char				*prefix;
	ushort_t			twidth;
	ushort_t			theight;
	short				ascender;
	uchar_t				decimal_pts;
	uchar_t				h_alignment;
	uchar_t				v_alignment;
} PtGaugeWidget_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
