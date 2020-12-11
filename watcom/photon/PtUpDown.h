/* PtUpDown.h - widget header file */

#ifndef __PT_UPDOWN_H_INCLUDED
#define __PT_UPDOWN_H_INCLUDED

#include <photon/PtT.h>
#include <photon/PhT.h>
#include <photon/PtGauge.h>
#include <photon/PtContainer.h>
#include <photon/PtButton.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/* widget resources */
#define Pt_ARG_UPDOWN_ORIENTATION 	Pt_RESOURCE( 52, 1 )
#define Pt_ARG_UPDOWN_SPACING		Pt_RESOURCE( 52, 2 )
#define Pt_ARG_UPDOWN_DATA_TOP 		Pt_RESOURCE( 52, 3 )

#define Pt_ARG_UPDOWN_DATA_BOT 		Pt_RESOURCE( 52, 4 )
#define Pt_ARG_UPDOWN_DATA_BOTTOM	Pt_RESOURCE( 52, 4 )

#define Pt_ARG_UPDOWN_DATA_LEF 		Pt_RESOURCE( 52, 5 )
#define Pt_ARG_UPDOWN_DATA_LEFT		Pt_RESOURCE( 52, 5 )

#define Pt_ARG_UPDOWN_DATA_RIT 		Pt_RESOURCE( 52, 6 )
#define Pt_ARG_UPDOWN_DATA_RIGHT	Pt_RESOURCE( 52, 6 )

#define Pt_ARG_UPDOWN_ARM_DATA_TOP 	Pt_RESOURCE( 52, 7 )

#define Pt_ARG_UPDOWN_ARM_DATA_BOT 	Pt_RESOURCE( 52, 8 )
#define Pt_ARG_UPDOWN_ARM_DATA_BOTTOM 	Pt_RESOURCE( 52, 8 )

#define Pt_ARG_UPDOWN_ARM_DATA_LEF 	Pt_RESOURCE( 52, 9 )
#define Pt_ARG_UPDOWN_ARM_DATA_LEFT	Pt_RESOURCE( 52, 9 )

#define Pt_ARG_UPDOWN_ARM_DATA_RIT 	Pt_RESOURCE( 52, 10 )
#define Pt_ARG_UPDOWN_ARM_DATA_RIGHT 	Pt_RESOURCE( 52, 10 )

//#define Pt_ARG_UPDOWN_BORDER_WIDTH 	Pt_RESOURCE( 52, 11 )

#define Pt_ARG_UPDOWN_BOT_BDR_COLOR	Pt_RESOURCE( 52, 12 )
#define Pt_ARG_UPDOWN_BOTTOM_BORDER_COLOR	Pt_RESOURCE( 52, 12 )

#define Pt_ARG_UPDOWN_TOP_BDR_COLOR	Pt_RESOURCE( 52, 13 )
#define Pt_ARG_UPDOWN_TOP_BORDER_COLOR	Pt_RESOURCE( 52, 13 )

#define Pt_ARG_UPDOWN_HIGHLGHT_ROUND Pt_RESOURCE( 52, 14 )
#define Pt_ARG_UPDOWN_HIGHLIGHT_ROUND Pt_RESOURCE( 52, 14 )

#define Pt_ARG_UPDOWN_FLAGS 		Pt_RESOURCE( 52, 15 )
#define Pt_ARG_UPDOWN_FILL_COLOR 	Pt_RESOURCE( 52, 16 )
#define Pt_ARG_UPDOWN_MARGIN_HEIGHT Pt_RESOURCE( 52, 17 )
#define Pt_ARG_UPDOWN_MARGIN_WIDTH 	Pt_RESOURCE( 52, 18 )

#define UPDOWN_TOP		1

#define UPDOWN_BOT		2
#define UPDOWN_BOTTOM	2
	
#define UPDOWN_LEF		3
#define UPDOWN_LEFT		3

#define UPDOWN_RIT		4
#define UPDOWN_RIGHT	4

/* widget instance structure */
typedef struct updown_widget{
	PtContainerWidget_t	container;
	int						orientation;
	PgColor_t	top_border_color, bot_border_color;
	unsigned				spacing;
	PtWidget_t 				*top_but;
	PtWidget_t 				*bot_but;
	PtWidget_t 				*lef_but;
	PtWidget_t 				*rit_but;
}	PtUpDownWidget_t;

extern PtWidgetClassRef_t *PtUpDown;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
