/*
 *	PtRaw.h
 *		Header file for the PtRaw widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_RAW_H_INCLUDED
#define __PT_RAW_H_INCLUDED

#ifndef __PT_BASIC_H_INCLUDED
 #include <photon/PtBasic.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtRaw public
 */

extern PtWidgetClassRef_t *PtRaw;

/* Resources */
#define Pt_ARG_RAW_INIT_F		Pt_RESOURCE( 24, 3 )
#define Pt_ARG_RAW_EXTENT_F		Pt_RESOURCE( 24, 2 )
#define Pt_ARG_RAW_CONNECT_F	Pt_RESOURCE( 24, 1 )
#define Pt_ARG_RAW_DRAW_F		Pt_RESOURCE( 24, 0 )


/*
 * PtRaw private
 */

/* Widget structure */
typedef struct Pt_raw_widget {
	PtBasicWidget_t		basic;
	void				(*draw_f)( PtWidget_t *, PhTile_t *damage );
	int					(*init_f)( PtWidget_t * );
	int					(*extent_f)( PtWidget_t * );
	int					(*connect_f)( PtWidget_t * );
} PtRawWidget_t;

/* Widget union */
typedef union Pt_raw_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtRawWidget_t				raw;
} PtRawUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
