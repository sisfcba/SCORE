#ifndef __Pt_ANIMATED_LABEL_H_INCLUDED
#define __Pt_ANIMATED_LABEL_H_INCLUDED

#include <photon/PtLabel.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtAnimatedLabel Public
 */

extern PtWidgetClassRef_t	*PtAnimatedLabel;

/* Resources */
#define Pt_ARG_FRAME_DATA		Pt_RESOURCE( 101, 0 )
#define Pt_ARG_NUM_FRAMES		Pt_RESOURCE( 101, 1 )
#define Pt_ARG_FRAME_INTERVAL	Pt_RESOURCE( 101, 2 )
#define Pt_ARG_CURRENT_FRAME	Pt_RESOURCE( 101, 3 )

/* 
 * PtAnimatedLabel Private
 */

/* Widget Structure */
typedef struct Pt_animated_label {
	PtLabelWidget_t         label;
	PhImage_t				*frame_data, *frame;
	int						num_frames;
	int						frame_interval;
	int						current_frame;
	int						repeat;
} PtAnimatedLabelWidget_t;

/* Widget Union */
typedef union Pt_animated_label_union {
	PtWidget_t              core;
	PtBasicWidget_t         basic;
	PtLabelWidget_t         label;
	PtAnimatedLabelWidget_t anim;
} PtAnimatedLabelUnion_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif /* __Pt_ANIMATED_LABEL_H_INCLUDED */
