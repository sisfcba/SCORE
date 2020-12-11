/*
 *  PtCompound.h
 *      Header file for the PtCompound widget class
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PT_COMPOUND_H_INCLUDED
#define __PT_COMPOUND_H_INCLUDED

#ifndef __PT_CONTAINER_H_INCLUDED
 #include <photon/PtContainer.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


/*
 * PtCompound public
 */

extern PtWidgetClassRef_t *PtCompound;

/* Resources */
// NONE

/*
 * PtCompound private
 */

typedef struct anode{
	struct anode *next;
	PtWidget_t *compound;
	PtCallbackList_t *cb_list;
} cbnode_t;
/* Widget structure */
typedef struct pt_compound_widget_t{
	PtContainerWidget_t	container;
	cbnode_t 			*redirected_cbs;
} PtCompoundWidget_t;

/* Widget union */
typedef struct Pt_compound_union {
	PtWidget_t					core;
	PtBasicWidget_t				basic;
	PtContainerWidget_t			container;
	PtCompoundWidget_t			compound;
} PtCompoundUnion_t;

typedef struct Pt_compound_class {
    PtContainerClass_t		container;
    ushort_t				num_subordinates;
    ushort_t				num_blocked_resources;
    ushort_t				*subordinates;
    ulong_t					*blocked_resources;
} PtCompoundClass_t;

#define Pt_SET_NUM_SUBORDINATES			( Pt_ARG_IS_NUMBER( PtCompoundClass_t, num_subordinates ) )

#define Pt_SET_SUBORDINATES				( Pt_ARG_IS_POINTER(PtCompoundClass_t,subordinates) ) 

#define Pt_SET_NUM_BLOCKED_RESOURCES	( Pt_ARG_IS_NUMBER(PtCompoundClass_t,num_blocked_resources) ) 

#define Pt_SET_BLOCKED_RESOURCES		( Pt_ARG_IS_ARRAY(PtCompoundClass_t,blocked_resources) ) 

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
