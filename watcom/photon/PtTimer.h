/*
 *	PtTimer.h
 *		Header file for the PtTimer widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_TIMER_H_INCLUDED
#define __PT_TIMER_H_INCLUDED

#ifndef __PT_WIDGET_H_INCLUDED
#include <photon/PtWidget.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtTimer public
 */

extern PtWidgetClassRef_t *PtTimer;

#define Pt_ARG_TIMER_INITIAL		Pt_RESOURCE( 41, 0 )
#define Pt_ARG_TIMER_REPEAT			Pt_RESOURCE( 41, 1 )
#define Pt_CB_TIMER_ACTIVATE		Pt_RESOURCE( 41, 2 )

/*
 * PtTimer public
 */

#define Pt_TIMER_INITIAL	1
#define Pt_TIMER_REPEAT		2

/* Widget structure */
typedef struct Pt_timer_widget {
	PtWidget_t				core;
	long					msec_value;
	long					msec_repeat;
	long					state;
	PtCallbackList_t        *activate;
} PtTimerWidget_t;

/* Widget union */
typedef union Pt_timer_union {
	PtWidget_t				core;
	PtTimerWidget_t			timer;
} PtTimerUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
