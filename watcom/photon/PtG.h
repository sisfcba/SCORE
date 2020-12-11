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

/* Orientation related */
#define Pt_VERTICAL					0
#define Pt_HORIZONTAL				1

/* Possible flags */
/* display related */
#define Pt_SHOW_VALUE_TOP			0x10
#define Pt_SHOW_VALUE_BOTTOM		0x20
#define Pt_SHOW_VALUE_LEFT			0x40
#define Pt_SHOW_VALUE_RIGHT			0x80
#define Pt_SHOW_VALUE_CENTER		0xc0

#define Pt_SHOW_VALUE_MASK			0xf0

typedef struct Pt_gauge_widget {
	PtBasicWidget_t     basic;
	long                value;
	long                maximum;
	long                minimum;
	ushort_t			flags;
	char				orientation;
	char				reserved;
	char				*font;
} PtGaugeWidget_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
