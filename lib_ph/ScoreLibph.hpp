//****************************************************************************
//
//			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
//	   DSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 1.0
//
//	PROJECT		: ALL
//
//	SYSTEM		: ALL
//
//	FILE		: ScoreLibph.hpp
//
//	DESCRIPTION	: Header file for the Photon Score library.
//                Contains the prototypes of the library functions.
//
//	AUTHOR		: Leonel Vicente Mota Ivo
//
//	OPERATING SYSTEM:  QNX 4.25		-	COMPILER: WATCOM C++ - V10.6
//
//	VERSION		: 1.0			-		DATE	:	03/03/99
//
//	HISTORY
//----------------------------------------------------------------------------
//Date     | Description                                          | Author 
//----------------------------------------------------------------------------
//03/03/99 | Initial edition                                      | Leonel
//----------------------------------------------------------------------------
//****************************************************************************

#ifndef	_SCORELIBPH_H
#define _SCORELIBPH_H

/* Toolkit headers */
#include <Pt.h>

// functions prototypes
#if defined(__cplusplus)
extern "C" {

void		NoticeScoreph(PtWidget_t *aparent, char *atitle, char *aformat, ... );
void		NoticeScoreph2(PtWidget_t *aparent, char *atitle, char *aformat, ... );
int			AskQuestion( PtWidget_t *parent, char *title, char *question, char *font, 
                 		 char *btn1, char *btn2, char *btn3, int def_btn );
int			AskQuestion2( PtWidget_t *parent, char *title, char *question, char *font, 
                 		  char *btn1, char *btn2, char *btn3, int def_btn );
void        ExibeErro( char *Message  );
void        ExibeAtencao( char *Message  );
void		PtSetStringValue(PtWidget_t *widget, const char *text, long type=Pt_ARG_TEXT_STRING);
const char  *PtGetStringValue(PtWidget_t *widget, long type=Pt_ARG_TEXT_STRING);
void		PtSetNumericIntValue(PtWidget_t *widget, int value);
int			PtGetNumericIntValue(PtWidget_t *widget);
void		PtSetNumericFloatValue(PtWidget_t *widget, double value, short int=0);
double		PtGetNumericFloatValue(PtWidget_t *widget);
void		PtSetColorValue(PtWidget_t *widget, long type, PgColor_t value);
PgColor_t	PtGetColorValue(PtWidget_t *widget, long type);
void		PtSetCursorType( PtWidget_t *widget, unsigned short cursor );
void 		PtSetFlags( PtWidget_t *widget, long flags, short int action, long type=Pt_ARG_FLAGS);
long 		PtGetFlags( PtWidget_t *apWidget, long aFlags, long aType=Pt_ARG_FLAGS);
void		PtGetArea( PtWidget_t *apWidget, PhArea_t *apArea );
void		PtSetArea( PtWidget_t *apWidget, PhArea_t *apArea );
void		PtSetPos( PtWidget_t *apWidget, PhPoint_t *apPoint );
void 		PtSetPosWids( PtWidget_t *apWidPai, PtWidget_t *apWids[], short aNWids,
						  short aEspaco, short aOffset, short aExpande=0 );
int			StartWindows(int dummy);
void		EndWindows(void);
short int	PtLoadBitmap( PtWidget_t *apWidget, char *apBitmap );

};
#else //compatibility with old C code

void		NoticeScoreph(PtWidget_t *aparent, char *atitle, char *aformat, ... );
void		NoticeScoreph2(PtWidget_t *aparent, char *atitle, char *aformat, ... );
int			AskQuestion( PtWidget_t *parent, char *title, char *question, char *font, 
                 		 char *btn1, char *btn2, char *btn3, int def_btn );
void        ExibeErro( char *Message  );
void        ExibeAtencao( char *Message  );
void		PtSetStringValue(PtWidget_t *widget, const char *text, long type);
const char  *PtGetStringValue(PtWidget_t *widget, long type);
void		PtSetNumericIntValue(PtWidget_t *widget, int value);
int			PtGetNumericIntValue(PtWidget_t *widget);
void		PtSetNumericFloatValue(PtWidget_t *widget, double value, short int prefix);
double		PtGetNumericFloatValue(PtWidget_t *widget);
void		PtSetColorValue(PtWidget_t *widget, long type, PgColor_t value);
PgColor_t	PtGetColorValue(PtWidget_t *widget, long type);
void		PtSetCursorType( PtWidget_t *widget, unsigned short cursor );
void 		PtSetFlags( PtWidget_t *widget, long flags, short int action, long type);
long 		PtGetFlags( PtWidget_t *apWidget, long aFlags, long aType);
void		PtGetArea( PtWidget_t *apWidget, PhArea_t *apArea );
void		PtSetArea( PtWidget_t *apWidget, PhArea_t *apArea );
void		PtSetPos( PtWidget_t *apWidget, PhPoint_t *apPoint );
void 		PtSetPosWids( PtWidget_t *apWidPai, PtWidget_t *apWids[], short aNWids,
						  short aEspaco, short aOffset, short aExpande );
int			StartWindows(int dummy);
void		EndWindows(void);
short int	PtLoadBitmap( PtWidget_t *apWidget, char *apBitmap );

#endif
#endif