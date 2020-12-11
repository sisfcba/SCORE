//
// PtHtml.h
// Photon html widget
// Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
//

#ifndef __PT_HTML_H_INCLUDED
#define __PT_HTML_H_INCLUDED

#include <photon/PtContainer.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t * PtHtml;

// Resources

#define	Pt_ARG_HTML_URL			Pt_RESOURCE( 45, 0 )
#define	Pt_ARG_HTML_TEXT_FONT		Pt_RESOURCE( 45, 1 )
#define	Pt_ARG_HTML_H1_FONT		Pt_RESOURCE( 45, 2 )
#define	Pt_ARG_HTML_H2_FONT		Pt_RESOURCE( 45, 3 )
#define	Pt_ARG_HTML_H3_FONT		Pt_RESOURCE( 45, 4 )
#define	Pt_ARG_HTML_H4_FONT		Pt_RESOURCE( 45, 5 )
#define	Pt_ARG_HTML_H5_FONT		Pt_RESOURCE( 45, 6 )
#define	Pt_ARG_HTML_H6_FONT		Pt_RESOURCE( 45, 7 )
#define	Pt_ARG_HTML_LINK_COLOR		Pt_RESOURCE( 45, 8 )
#define Pt_ARG_HTML_CURSOR_DEFAULT	Pt_RESOURCE( 45, 9 )
#define Pt_ARG_HTML_CURSOR_LINK		Pt_RESOURCE( 45, 10 )
#define Pt_ARG_HTML_CURSOR_BUSY		Pt_RESOURCE( 45, 11 )
#define Pt_ARG_HTML_SCROLL_VERTICAL	Pt_RESOURCE( 45, 12 )
#define Pt_ARG_HTML_SCROLL_HORIZONTAL	Pt_RESOURCE( 45, 13 )
#define Pt_ARG_HTML_SCROLL_WIDTH	Pt_RESOURCE( 45, 14 )

#define Pt_CB_HTML_FILE_PRE		Pt_RESOURCE( 45, 15 )
#define Pt_CB_HTML_FILE_POST		Pt_RESOURCE( 45, 16 )
#define Pt_CB_HTML_IMAGE		Pt_RESOURCE( 45, 17 )

#define Pt_ARG_HTML_PAGE_X		Pt_RESOURCE( 45, 18 )
#define Pt_ARG_HTML_PAGE_Y		Pt_RESOURCE( 45, 19 )
#define Pt_ARG_HTML_PAGE_H		Pt_RESOURCE( 45, 20 )
#define Pt_ARG_HTML_PAGE_W		Pt_RESOURCE( 45, 21 )
#define Pt_ARG_HTML_PAGE_TM		Pt_RESOURCE( 45, 22 )
#define Pt_ARG_HTML_PAGE_RM		Pt_RESOURCE( 45, 23 )
#define Pt_ARG_HTML_PAGE_BM		Pt_RESOURCE( 45, 24 )
#define Pt_ARG_HTML_PAGE_LM		Pt_RESOURCE( 45, 25 )
#define Pt_ARG_HTML_BORDER_WIDTH	Pt_RESOURCE( 45, 26 )
#define Pt_ARG_HTML_FILL_COLOR		Pt_RESOURCE( 45, 27 )
#define Pt_ARG_HTML_SCROLL_COLOR	Pt_RESOURCE( 45, 28 )
#define Pt_ARG_HTML_SCROLL_FILL_COLOR	Pt_RESOURCE( 45, 29 )

#define Pt_CB_HTML_ERROR		Pt_RESOURCE( 45, 30 )
#define Pt_ARG_HTML_FLAGS		Pt_RESOURCE( 45, 31 )

#define Pt_ARG_HTML_INCREMENT		Pt_RESOURCE( 45, 32 )
#define Pt_ARG_HTML_PAGE_INCREMENT	Pt_RESOURCE( 45, 33 )

#define Pt_ARG_HTML_PAGES		Pt_RESOURCE( 45, 34 )
#define Pt_ARG_HTML_PAGE_N		Pt_RESOURCE( 45, 35 )

// Flags

#define Pt_HTML_RELOAD		0x1
#define Pt_HTML_PAGE_MODE	0x2

// Internal Flags ( do not use )

#define Pt_HTML_DISPLAY		0x01
#define Pt_HTML_RESIZE		0x02
#define Pt_HTML_REDIRECT	0x04
#define Pt_HTML_LOAD		0x08
#define Pt_HTML_PAGE		0x10

// Callbacks

typedef struct Pt_html_callback
{
	char * url;
} PtHtmlCallback_t;

// Widget

struct _Widget;

typedef struct Pt_html_widget
{
	PtContainerWidget_t container;
	// resources

	#ifdef __QNXNTO__
	ushort_t borderwidth; // internal border width
	#endif

	int flags;
	char * url;
	PgColor_t linkcolor;
	char * textfont;
	char * h1font;
	char * h2font;
	char * h3font;
	char * h4font;
	char * h5font;
	char * h6font;
	ushort_t cursordefault; // default cursor 
	ushort_t cursorbusy; // busy cursor
	ushort_t cursorlink; // link cursor
	ushort_t scrollvertical; // vertical mode
	ushort_t scrollhorizontal; // horizontal mode
	ushort_t scrollwidth; // scrollbar width
	int pagex; // page x position
	int pagey; // page y position
	int pageh; // page height
	int pagew; // page width
	int pages; // number of pages
	int pagen; // current page
	ushort_t pagetm; // page top margin
	ushort_t pagerm; // page right margin
	ushort_t pagebm; // page bottom margin
	ushort_t pagelm; // page left margin

	#ifndef __QNXNTO__
	ushort_t borderwidth; // internal border width
	#endif

	PgColor_t fillcolor;
	PgColor_t scrollcolor;
	PgColor_t scrollfill;

	/* if the html file sets the attributes for the body tag ( bgcolor, link and text ), then these are filled and they will take precedence */
	int document_fillcolor, document_linkcolor, document_color;

	PtCallbackList_t * precallbacks;
	PtCallbackList_t * postcallbacks;
	PtCallbackList_t * imagecallbacks;
	PtCallbackList_t * errorcallbacks;
	// data
	struct _Widget * _widget;
	int action;
	int scroll_inc;
	int scroll_pg_inc;
} PtHtmlWidget_t;

typedef union Pt_html_union
{
	PtWidget_t widget;
	PtBasicWidget_t basic;
	PtContainerWidget_t container;
	PtHtmlWidget_t html;
} PtHtmlUnion_t;

// Functions

char * PtHtmlTitle( PtWidget_t * );
char * PtHtmlLink( PtWidget_t *, char * );

#ifdef __cplusplus
};
#endif
#endif
