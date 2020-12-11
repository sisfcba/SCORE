/* PtNumeric.h - widget header file */

#ifndef __PT_NUMERIC_H_INCLUDED
#define __PT_NUMERIC_H_INCLUDED

#include <photon/PtT.h>
#include <photon/PhT.h>
#include <photon/PtGauge.h>
#include <photon/PtCompound.h>
#include <photon/PtText.h>
#include <photon/PtUpDown.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/* widget resources */
#define Pt_ARG_NUMERIC_FLAGS					Pt_RESOURCE( 53, 1 )
#define Pt_ARG_NUMERIC_UPDOWN_WIDTH				Pt_RESOURCE( 53, 2 )
#define Pt_ARG_NUMERIC_INCREMENT 				Pt_RESOURCE( 53, 3 )
#define Pt_ARG_NUMERIC_VALUE					Pt_RESOURCE( 53, 4 )
#define Pt_ARG_NUMERIC_MIN						Pt_RESOURCE( 53, 5 )
#define Pt_ARG_NUMERIC_MAX						Pt_RESOURCE( 53, 6 )
#define Pt_ARG_NUMERIC_PREFIX					Pt_RESOURCE( 53, 7 )
#define Pt_ARG_NUMERIC_SUFFIX					Pt_RESOURCE( 53, 8 )
#define Pt_ARG_NUMERIC_TEXT_BORDER				Pt_RESOURCE( 53, 9 )
#define Pt_ARG_NUMERIC_TEXT_FONT				Pt_RESOURCE( 53, 10 )
#define Pt_ARG_NUMERIC_TEXT_COLOR				Pt_RESOURCE( 53, 11 )
#define Pt_ARG_NUMERIC_TEXT_FILL_COLOR			Pt_RESOURCE( 53, 12 )
#define Pt_ARG_NUMERIC_TEXT_TOP_BORDER_COLOR	Pt_RESOURCE( 53, 13 )
#define Pt_ARG_NUMERIC_TEXT_BOT_BORDER_COLOR	Pt_RESOURCE( 53, 14 )
#define Pt_ARG_NUMERIC_PRECISION				Pt_RESOURCE( 53, 16 )
#define Pt_ARG_NUMERIC_SPACING					Pt_RESOURCE( 53, 17 )
#define Pt_ARG_NUMERIC_UPDOWN_BORDER_WIDTH		Pt_RESOURCE( 53, 18 )
#define Pt_ARG_NUMERIC_TEXT_FLAGS				Pt_RESOURCE( 53, 19 )
#define Pt_CB_NUMERIC_CHANGED					Pt_RESOURCE( 53, 15 )

/* PtNumeric Flags */
#define Pt_NUMERIC_ENABLE_UPDOWN		0x01   
#define Pt_NUMERIC_USE_SEPARATORS 		0x02
#define Pt_NUMERIC_WRAP					0x04
#define Pt_NUMERIC_AUTO_HIGHLIGHT		0x08
#define Pt_NUMERIC_HEXADECIMAL			0x10
#define Pt_NUMERIC_VALUE_CHANGED				0x80000000

#define NUMERIC_BUF				40

/* widget instance structure */
typedef struct numeric_widget{
	PtCompoundWidget_t	compound;
	int				updown_width;
	int				numeric_flags;
	int 			text_border, updown_border;
	int 			updown_border_width;
	int				spacing;
	char			*prefix, *suffix;
	char 			*text_font;
	PgColor_t		text_color, text_fill_color, text_top_bcolor, text_bot_bcolor;
	PtWidget_t		*text_wgt;
	PtWidget_t		*updown_wgt;
	int sep_flag;
	int text_flags;
	long			spare[2];
}	PtNumericWidget_t;

// callback subtypes
#define Pt_NUMERIC_CHANGED 			0x1
#define Pt_NUMERIC_ACTIVATE			0x2
#define Pt_NUMERIC_UPDOWN_REPEAT 	0x4
#define Pt_NUMERIC_UPDOWN_ACTIVATE 	0x8

extern PtWidgetClassRef_t *PtNumeric;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
