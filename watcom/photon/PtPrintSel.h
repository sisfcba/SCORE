#ifndef __Pt_PRINTSEL_H_INCLUDED
#define __Pt_PRINTSEL_H_INCLUDED

#ifndef __PT_CONTAINER_H_INCLUDED
#include <PtContainer.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t *PtPrintSel;

enum print_tags {
	LOCATION = 0,
	NUM_COPIES,
	COLLATE_METHOD,
	SEL_TITLE,
	PRINTER,
	PRINT_RANGE,
	COPIES,
	};

typedef struct {
	PtContainerWidget_t		container;
	PtWidget_t				*printer;
	PtWidget_t				*location;
	PtWidget_t				*properties;
	PtWidget_t				*tofile;
	PtWidget_t				*extensions;
	PtWidget_t				*all, *pages, *selection;
	PtWidget_t				*range;
	PtWidget_t				*copies;
	PtWidget_t				*up, *down;
	PtWidget_t				*nocollate, *collate;
	PtWidget_t				*labels[7];
	struct {
		PtWidget_t		*timer;
		PtInputId_t		*xfer;
		pid_t			pid;
	}						application;
	PtCallbackList_t		*propcbs, *filecbs;
	char					ncopies;
	char					collation;
	short					source;
	char					*tofilename;
	unsigned long			modified;
	short					count;
	short					selprinter;
	PpPrintContext_t		**prtlist;
	PpPrintContext_t		*user;
	unsigned short			flags;
	char					*filename_label;
	char					*location_label;
} PtPrintSelWidget_t;

#define Pt_ARG_PRINT_CONTEXT	Pt_RESOURCE(46, 0)
#define Pt_ARG_PRINT_FLAGS		Pt_RESOURCE(46, 1)
#define Pt_CB_PRINT_PROPS		Pt_RESOURCE(46, 2)
#define Pt_CB_PRINT_TOFILE		Pt_RESOURCE(46, 3)
#define Pt_ARG_PS_SEL_TITLE	Pt_RESOURCE(46, 4)
#define Pt_ARG_PS_NUM_COPIES_LABEL	Pt_RESOURCE(46, 5)
#define Pt_ARG_PS_COLLATE_METHOD_LABEL		Pt_RESOURCE(46, 6)
#define Pt_ARG_PS_LOCATION_LABEL	Pt_RESOURCE(46, 7)
#define Pt_ARG_PS_PRINTER_LABEL	Pt_RESOURCE(46, 8)
#define Pt_ARG_PS_PRINT_RANGE_LABEL Pt_RESOURCE(46, 9)
#define Pt_ARG_PS_COPIES_LABEL		Pt_RESOURCE(46, 10)
#define Pt_ARG_PS_PROPERTIES_LABEL	Pt_RESOURCE(46, 11)
#define Pt_ARG_PS_ALL_PAGES_LABEL	Pt_RESOURCE(46, 12)
#define Pt_ARG_PS_PAGES_LABEL		Pt_RESOURCE(46, 13)
#define Pt_ARG_PS_TOFILE_LABEL		Pt_RESOURCE(46, 14)
#define Pt_ARG_PS_SELECTION_LABEL	Pt_RESOURCE(46, 15)
#define Pt_ARG_PS_FILENAME_LABEL	Pt_RESOURCE(46, 16)

#define Pt_PRINTSEL_ALL_PAGES	0
#define Pt_PRINTSEL_SOME_PAGES	1
#define Pt_PRINTSEL_SELECTION	2

#define Pt_PRINTSEL_COLLATE_DFLT	0
#define Pt_PRINTSEL_COLLATE_1212	1
#define Pt_PRINTSEL_COLLATE_1122	2

#define Pt_PRINTSEL_ALL_PANES		0x0001
#define Pt_PRINTSEL_PROP_APP		0x0002
#define Pt_PRINTSEL_NO_PAGE_RANGE	0x0010
#define Pt_PRINTSEL_NO_SELECT_RANGE	0x0020
#define Pt_PRINTSEL_NO_COPIES		0x0040
#define Pt_PRINTSEL_NO_COLLATE		0x0080
#define Pt_PRINTSEL_NO_PREVIEW      0x0100
#define Pt_PRINTSEL_USER_SET_FILE	0x2000 // internal R/O
#define Pt_PRINTSEL_WAS_TOFILE		0x4000 // internal R/O
#define Pt_PRINTSEL_IS_FILEONLY		0x8000 // internal R/O

#define Pt_PRINTSEL_PROPERTIES	0
#define Pt_PRINTSEL_ADDNEW		1
#define Pt_PRINTSEL_RETURNED	2

#define Pt_PRINTSEL_CANCEL		0
#define Pt_PRINTSEL_PRINT		1
#define Pt_PRINTSEL_PREVIEW		2

#define Pt_PRINTSEL_DFLT_LOOK	(Pt_PRINTSEL_ALL_PANES | Pt_PRINTSEL_PROP_APP)

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
