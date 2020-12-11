/*
 *	PtSlider.h
 *		Header file for the PtSlider widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */

#ifndef __PT_SLIDER_H_INCLUDED
#define __PT_SLIDER_H_INCLUDED

#ifndef __PT_BASIC_H_INCLUDED
 #include <photon/PtBasic.h>
#endif

#ifndef __PT_GAUGE_H_INCLUDED
 #include <photon/PtGauge.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtSlider public
 */

extern PtWidgetClassRef_t *PtSlider;

/* Resources */
#define Pt_ARG_SLIDER_FLAGS				Pt_RESOURCE( 22, 0 )
#define Pt_ARG_SLIDER_INCREMENT			Pt_RESOURCE( 22, 1 )
#define Pt_ARG_SLIDER_LABEL_TL			Pt_RESOURCE( 22, 2 )
#define Pt_ARG_SLIDER_LABEL_BR			Pt_RESOURCE( 22, 3 )
#define Pt_ARG_SLIDER_LABEL_TL_COL		Pt_RESOURCE( 22, 4 )
#define Pt_ARG_SLIDER_LABEL_BR_COL		Pt_RESOURCE( 22, 5 )
#define Pt_ARG_SLIDER_MULTIPLE			Pt_RESOURCE( 22, 6 )
#define Pt_ARG_SLIDER_HANDLE_WIDTH		Pt_RESOURCE( 22, 7 )
#define Pt_ARG_SLIDER_HANDLE_HEIGHT		Pt_RESOURCE( 22, 8 )
#define Pt_ARG_SLIDER_IMAGE				Pt_RESOURCE( 22, 9 )
#define Pt_ARG_SLIDER_TICK_MAJOR_COL	Pt_RESOURCE( 22, 10 )
#define Pt_ARG_SLIDER_TICK_MINOR_COL	Pt_RESOURCE( 22, 11 )
#define Pt_ARG_SLIDER_TICK_MINOR_DIV	Pt_RESOURCE( 22, 12 )
#define Pt_ARG_SLIDER_TICK_MAJOR_DIV	Pt_RESOURCE( 22, 13 )
#define Pt_ARG_SLIDER_TICK_MAJOR_LEN	Pt_RESOURCE( 22, 14 )
#define Pt_ARG_SLIDER_TICK_MINOR_LEN	Pt_RESOURCE( 22, 15 )
#define Pt_ARG_SLIDER_TROUGH_SIZE		Pt_RESOURCE( 22, 16 )
#define Pt_ARG_SLIDER_ORIENTATION		Pt_RESOURCE( 22, 19 )

#define Pt_CB_SLIDER_MOVE				Pt_RESOURCE( 22, 17 )

#define Pt_ARG_SLIDER_TROUGH_COL		Pt_RESOURCE( 22, 18 )

#define Pt_SLIDER_X1_RESOURCES    1
typedef struct
{
	short orientation;
} PtSliderX1Resources_t;

/* Possible flags */
#define Pt_TICKS_ON_TOP				0x01
#define Pt_TICKS_ON_LEFT			0x01
#define Pt_TICKS_ON_BOTTOM			0x02
#define Pt_TICKS_ON_RIGHT			0x02
#define Pt_TICKS_MASK				0x03
#define Pt_TICKS_TOUCH_TROUGH		0x04
#define Pt_TICKS_ETCHED_OUT			0x08
#define Pt_TICKS_ETCHED_IN			0x10

#define Pt_SLIDER_POINT_LEFT		0x20
#define Pt_SLIDER_POINT_UP			0x20
#define Pt_SLIDER_POINT_RIGHT		0x40
#define Pt_SLIDER_POINT_DOWN		0x40
#define Pt_SLIDER_IMAGE				0x80
#define Pt_SLIDER_MASK				0x70

// slider orientation values
#define Pt_SLIDER_MIN_ON_TOP	0
#define Pt_SLIDER_MIN_ON_BOTTOM	1
#define Pt_SLIDER_MIN_ON_LEFT	0
#define Pt_SLIDER_MIN_ON_RIGHT	1

typedef struct Pt_slider_widget {
	PtGaugeWidget_t     gauge;
	ushort_t			flags;
	ushort_t            slider_width;
	ushort_t            slider_height;
	ushort_t			trough_size;
	PgColor_t			trough_col;
	ushort_t			increment;
	ushort_t			multiple;
	ushort_t			tick_major_len;
	ushort_t			tick_minor_len;
	long				tick_major_div;
	long				tick_minor_div;
	PgColor_t			tick_major_col;
	PgColor_t			tick_minor_col;
	char				*label_br;
	char				*label_tl;
	PhDim_t				label_dim_tl;
	PhDim_t				label_dim_br;
	PgColor_t			label_tl_col;
	PgColor_t			label_br_col;
	PhDim_t				show_val_dim;
	void				*data;
	long				minimum;
	long				maximum;
	long				value;
	long				step;
	PtCallbackList_t	*cb_move;
} PtSliderWidget_t;

/* Callback structure */
typedef struct Pt_slider_callback {
	int			position;
} PtSliderCallback_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
