#ifndef __PT_ONOFF_BUTTON_H_INCLUDED
#define __PT_ONOFF_BUTTON_H_INCLUDED

#ifndef __PT_TOGGLE_BUTTON_H_INCLUDED
 #include <photon/PtToggleButton.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t *PtOnOffButton;

typedef struct Pt_onoff_button_widget {
	PtToggleButtonWidget_t	tbutton;
	ushort_t				state;
	char					reserved[2];
	PtCallbackList_t		*new_value;
} PtOnOffButtonWidget_t;

/* callback structure */
typedef struct {
	int		state;
} PtOnOffButtonCallback_t;

#define Pt_ARG_ONOFF_STATE    	Pt_RESOURCE( 8, 0 )
#define Pt_CB_ONOFF_NEW_VALUE	Pt_RESOURCE( 8, 1 )

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
