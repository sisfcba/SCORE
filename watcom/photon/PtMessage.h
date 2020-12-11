#ifndef __Pt_MESSAGE_H_INCLUDED
#define __Pt_MESSAGE_H_INCLUDED

#ifndef __PT_WIDGET_H_INCLUDED
 #include <PtWidget.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t *PtMessage;

typedef struct {
	PtContainerWidget_t		container;
	char					*title;
	char					*text;
	char					*font;
	char					*button1_txt;
	char					*button2_txt;
	char					*button3_txt;
	short					def_button;
	PtWidget_t				*dlg;
	PtWidget_t				*msg;
	PtWidget_t				*opt;
	PtCallbackList_t		*button1;
	PtCallbackList_t		*button2;
	PtCallbackList_t		*button3;
	int						flags;
	short					esc_button;
	short						spare;
} PtMessageWidget_t;

/* resources */
#define Pt_ARG_MSG_TITLE		Pt_RESOURCE( 32, 0 )
#define Pt_ARG_MSG_TEXT       	Pt_RESOURCE( 32, 1 )
#define Pt_ARG_MSG_FONT       	Pt_RESOURCE( 32, 3 )
#define Pt_ARG_MSG_BUTTON1    	Pt_RESOURCE( 32, 4 )
#define Pt_ARG_MSG_BUTTON2    	Pt_RESOURCE( 32, 5 )
#define Pt_ARG_MSG_BUTTON3    	Pt_RESOURCE( 32, 6 )
#define Pt_ARG_MSG_DEFAULT    	Pt_RESOURCE( 32, 7 )
#define Pt_ARG_MSG_ESCAPE    	Pt_RESOURCE( 32, 2 )
#define Pt_ARG_MSG_FLAGS    	Pt_RESOURCE( 32, 11 )

/* callback resources */
#define Pt_CB_MSG_BUTTON1		Pt_RESOURCE( 32, 8 )
#define Pt_CB_MSG_BUTTON2		Pt_RESOURCE( 32, 9 )
#define Pt_CB_MSG_BUTTON3		Pt_RESOURCE( 32,10 )

// message flags
#define Pt_MSG_CENTER_ON_PARENT 0x1
#define Pt_MSG_FONT_ON_BUTTONS	0x2


#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
