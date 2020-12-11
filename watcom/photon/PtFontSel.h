#ifndef __Pt_FONTSEL_H_INCLUDED
#define __Pt_FONTSEL_H_INCLUDED

#ifndef __PT_CONTAINER_H_INCLUDED
#include <photon/PtContainer.h>
#endif
#include <photon/Pf.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t *PtFontSel;

typedef struct {
	PtContainerWidget_t		container;
	PtWidget_t				*family;
	PtWidget_t				*size;
	PtWidget_t				*bold;
	PtWidget_t				*italic;
	PtWidget_t				*antialias;
	PtWidget_t				*sample;
	char					*font;
	char					*text;
	PtCallbackList_t		*changed;
	FontDetails				*details;
	int						count;
	long					symbol;
	unsigned short			display;
	unsigned short			flags;
	short					match;
	struct {
		FontName	face;
		short		size;
		short		style;
		short		pfr;
	}						desc;
} PtFontSelWidget_t;

#define Pt_ARG_FONT_NAME	Pt_RESOURCE(38, 0)
#define Pt_ARG_FONT_SAMPLE	Pt_RESOURCE(38, 1)
#define Pt_ARG_FONT_SYMBOL	Pt_RESOURCE(38, 2)
#define Pt_ARG_FONT_FLAGS	Pt_RESOURCE(38, 3)
#define Pt_CB_FONT_MODIFY	Pt_RESOURCE(38, 4)
#define Pt_ARG_FONT_DISPLAY	Pt_RESOURCE(38, 5)

#define Pt_FONTSEL_AA_CHECK		0x01
#define Pt_FONTSEL_SAMPLE		0x02

#define Pt_FONTSEL_SCALABLE		PHFONT_SCALABLE
#define Pt_FONTSEL_BITMAP		PHFONT_BITMAP
#define Pt_FONTSEL_PROP			PHFONT_PROP
#define Pt_FONTSEL_FIXED		PHFONT_FIXED
#define Pt_FONTSEL_ALL_FONTS	PHFONT_ALL_FONTS

#define Pt_FONTSEL_ALL_SYMBOLS	PHFONT_ALL_SYMBOLS

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
