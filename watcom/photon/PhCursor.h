/*
 *	PhCursor.h	
 *		Manifests for various cursors in the system cursor font
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */

#ifndef __PH_CURSOR_H_INCLUDED
#define __PH_CURSOR_H_INCLUDED

#define	Ph_CURSOR_DEFAULT_FONT		"phcursor"
#define	Ph_CURSOR_DEFAULT_COLOR		((PgColor_t)0xFFFFE0)

#define	Ph_CURSOR_NO_INHERIT		0x01
#define	Ph_CURSOR_MANUAL_CONTROL	0xFF
#define Ph_CURSOR_NONE				0xFD
#define Ph_CURSOR_BITMAP			0xFB

#define Ph_CURSOR_INHERIT			0x00

#define	Ph_CURSOR_POINTER			0xE900
#define	Ph_CURSOR_BIG_POINTER		0xE902
#define Ph_CURSOR_MOVE				0xE904
#define Ph_CURSOR_CROSSHAIR			0xE906
#define Ph_CURSOR_CLOCK				0xE908
#define Ph_CURSOR_WAIT				0xE908
#define Ph_CURSOR_NOINPUT			0xE90A
#define Ph_CURSOR_DONT				0xE90A
#define Ph_CURSOR_FINGER			0xE90C
#define Ph_CURSOR_INSERT			0xE90E

#define	Ph_CURSOR_DRAG_VERTICAL		0xE910
#define	Ph_CURSOR_DRAG_TOP			0xE910
#define	Ph_CURSOR_DRAG_BOTTOM		0xE910

#define	Ph_CURSOR_DRAG_HORIZONTAL	0xE912
#define	Ph_CURSOR_DRAG_LEFT			0xE912
#define	Ph_CURSOR_DRAG_RIGHT		0xE912

#define	Ph_CURSOR_DRAG_BACKDIAG		0xE914
#define	Ph_CURSOR_DRAG_TL			0xE914
#define	Ph_CURSOR_DRAG_BR			0xE914

#define	Ph_CURSOR_DRAG_FOREDIAG		0xE916
#define	Ph_CURSOR_DRAG_TR			0xE916
#define	Ph_CURSOR_DRAG_BL			0xE916

#define Ph_CURSOR_POINT_WAIT		0xE918
#define Ph_CURSOR_LONG_WAIT			0xE91A
#define Ph_CURSOR_QUESTION_POINT	0xE91C
#define Ph_CURSOR_PASTE				0xE91E



#endif
