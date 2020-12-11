#ifndef __AW_ONOFF_BUTTON_H_INCLUDED
#define __AW_ONOFF_BUTTON_H_INCLUDED

#ifndef __PT_TOGGLE_BUTTON_H_INCLUDED
 #include <PtToggleButton.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClass_t *AwOnOffButton;

typedef struct Aw_onoff_button_widget {
	PtToggleButtonWidget_t	tbutton;
	uchar_t					state;
	PtCallbackList_t		*new_value;
} AwOnOffButtonWidget_t;

/* callback structure */
typedef struct {
	int		state;
	} AwOnOffButtonCallback_t;

#define Aw_CB_ONOFF_NEW_VALUE	Pt_RESOURCE( 5, 0 )
#define Aw_ARG_ONOFF_STATE    	Pt_RESOURCE( 5, 1 )

/* prototypes */
extern	void			 AwDfltsOnOffButton( PtWidget_t *widget );
extern	int				 AwInitOnOffButton( PtWidget_t *widget );
extern	void			 AwDrawOnOffButton( PtWidget_t *widget );
extern	int				 AwDestroyOnOffButton( PtWidget_t *widget );
extern	void			 AwOnOffButtonValue( PtWidget_t *widget, void *data, PtCallbackInfo_t *cbinfo );
extern	PtWidgetClass_t	*AwCreateOnOffButtonClass( void );

#ifdef __cplusplus
};
#endif
#endif
