/*
 *	Pg.h	
 *		Manifests and data structures for the Pg-lib
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PH_GLIB_H_INCLUDED
#define __PH_GLIB_H_INCLUDED

#ifndef __PHT_H_INCLUDED
	#include <photon/PhT.h>
#endif

#ifndef __PH_GLIB_VECTOR_H_INCLUDED
//#include <photon/PgVector.h>
#endif

#include <photon/Pf.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" 
{
#endif

#define Pg_DO_EXTENT				0x0002
#define Pg_ITEST_CURSOR_HIDE		0x0010
#define Pg_CLIPTEST_CURSOR_HIDE		0x0020
#define Pg_CURSOR_SHOW				0x0080

#define	Pg_SET		1
#define	Pg_UNSET	0

#define		__PgShmemF_Valid		1
#define		__PgShmemF_Disabled		2


/* Trend flags	*/
#define Pg_TREND_HORIZ	0x00		/* Horizontal trend				*/
#define Pg_TREND_VERT	0x01		/* Vertical trend				*/

/* PgDrawBeveled flags */
#define Pg_BEVEL_SET		0x1000
#define Pg_BEVEL_ARROW		0x2000

#define	Pg_BEVEL_SQUARE		0x0000
#define	Pg_BEVEL_ROUND		0xC000
#define	Pg_BEVEL_CLIP		0x8000

#define	Pg_BEVEL_ALEFT		0x2000
#define	Pg_BEVEL_ARIGHT		0x6000
#define	Pg_BEVEL_AUP		0xA000
#define	Pg_BEVEL_ADOWN		0xE000

#define	Pg_BEVEL_TYPE_MASK	0xE000
#define	Pg_BEVEL_MAX		15

/*
 * Mode for draw operations, all drivers 
 *	Pg_SetDrawMode
 */
//     Photon name             value       X            	Logic	Mach	MSWin
#define Pg_DRAWMODE_OPAQUE		0		// GXcopy			S		7		R2_COPYPEN
#define Pg_DRAWMODE_XOR			1		// GXxor			D ^ S	5		R2_XORPEN
#define Pg_DRAWMODE_AND			2		// GXand			D & S	C		R2_MASKPEN
#define Pg_DRAWMODE_OR			3		// GXor				D | S	B		R2_MERGEPEN

#define	Pg_DRAWMODE_COPYINV		4		// GXcopyInverted	~S		4		R2_NOTCOPYPEN
#define	Pg_DRAWMODE_XNOR		5		// GXequiv			D ^ ~S	6		R2_NOTXORPEN
#define	Pg_DRAWMODE_ANDINV		6		// GXandInverted	D & ~S	E		R2_MASKNOTPEN
#define	Pg_DRAWMODE_ORINV		7		// GXorInverted		D | ~S	9		R2_MERGENOTPEN
#define	Pg_DRAWMODE_CLEAR		8		// GXclear			zero	1		R2_BLACK
#define	Pg_DRAWMODE_NOP			9		// GXnoop			D		3		R2_NOP
#define	Pg_DRAWMODE_ANDREV		0xA		// GXandReverse		~D & S	D		R2_MASKPENNOT
#define	Pg_DRAWMODE_ORREV		0xB		// GXorReverse		~D | S	A		R2_MERGEPENNOT
#define	Pg_DRAWMODE_SET			0xC		// GXset			one		2		R2_WHITE
#define	Pg_DRAWMODE_INVERT		0xD		// GXinvert			~D		0		R2_NOT
#define	Pg_DRAWMODE_NOR			0xE		// GXnor			~D & ~S	F		R2_NOTMERGEPEN
#define	Pg_DRAWMODE_NAND		0xF		// GXnand			~D | ~S	8		R2_NOTMASKPEN

// Defines for the yet to be named super cool blt

// Chroma Key BitBlt Operations
#if 0
#define Pg_CHROMA_SRC_KEY 			0x00000000
#define Pg_CHROMA_DEST_KEY 			0x00000001
#define Pg_CHROMA_NOT_SRC_KEY 		0x00000002
#define Pg_CHROMA_NOT_DST_KEY		0x00000003
#else
#define Pg_CHROMA_SRC_MATCH		0
#define Pg_CHROMA_DEST_MATCH		1
#define Pg_CHROMA_DRAW		0
#define Pg_CHROMA_NODRAW		2
#endif
#define Pg_ENABLE_CHROMA			0x00000004

// Hardware Scaling
#define Pg_STRETCH_BLT				0x00000008

// Wait for V_SYNC
#define Pg_WAIT_VSYNC				0x00000010

/*
 * Palette Modes - PgSetPalette
 */
#define Pg_PALSET_TYPEMASK		0x0F
#define Pg_PALSET_SOFT			0x00
#define Pg_PALSET_HARD			0x01
#define Pg_PALSET_HARDLOCKED	0x02
#define Pg_PALSET_GLOBAL		0x03
#define Pg_PALSET_HARDINACTIVE	0x05
#define Pg_PALSET_FORCE_EXPOSE	0x80


/*
 * PgDrawPhImagemx flags 
 */
#define  Pg_GHOST	0x01000000
 
/*
 * Bitmap array types
 *	PgDrawBitmap
 */
#define Pg_BITMAP_TRANSPARENT	0xFF	/* Bitmap transparent backfill */
#define Pg_BITMAP_BACKFILL		0xFE	/* Bitmap backfill */

/*
 * Image array types
 *	PgDrawImage
 */
#define	Pg_IMAGE_CLASS_MASK		0x38
#define	Pg_IMAGE_CLASS_PALETTE	0x10
#define	Pg_IMAGE_CLASS_GRADIENT	0x18
#define	Pg_IMAGE_CLASS_BLEND	0x08
#define	Pg_IMAGE_CLASS_DIRECT	0x20

#define Pg_IMAGE_PALETTE_BYTE	0x10	/* IIIIIIII */
#define Pg_IMAGE_BYTE_PALETTE	Pg_IMAGE_PALETTE_BYTE
#define	Pg_IMAGE_PALETTE_NIBBLE	0x11	/* IIIIiiii (I first, i second ) */
#define	Pg_IMAGE_NIBBLE_PALETTE	Pg_IMAGE_PALETTE_NIBBLE
#define	Pg_IMAGE_GRADIENT_BYTE	0x18
#define	Pg_IMAGE_GRADIENT_NIBBLE 0x19
#define	Pg_IMAGE_GBLEND_BYTE	0x08
#define	Pg_IMAGE_GBLEND_NIBBLE	0x09
#define	Pg_IMAGE_DBLEND_SHORT	0x0A
#define	Pg_IMAGE_DBLEND_LONG	0x0B
#define	Pg_IMAGE_DIRECT_8888	0x20	/* xxxxxxxxRRRRRRRRGGGGGGGGBBBBBBBB */
#define	Pg_IMAGE_DIRECT_888		0x21	/* RRRRRRRRGGGGGGGGBBBBBBBB */
#define	Pg_IMAGE_DIRECT_565		0x22	/* RRRRRGGGGGGBBBBB */
#define	Pg_IMAGE_DIRECT_555		0x23	/* xRRRRRGGGGGBBBBB	*/
#define	Pg_IMAGE_DIRECT_444		0x24	/* xxxxRRRRGGGGBBBB	*/
#define	Pg_IMAGE_FIRST_TIME		0x10000l

typedef char const *PgPattern_t;
typedef struct {
	unsigned short	hue;
	unsigned char	sat, vid;
} PgColorHSV_t;

// #define	_PgSWAPRGB( c )		PgRGB( (c) & 0xFF, (c >> 8) & 0xFF, (c >> 16) & 0xFF )
#define	_PgSWAPRGB( c )		( ((c) & 0xFF00FF00) | ((c >> 16) & 0x000000FF) | ((c << 16) & 0x00FF0000) )

/* Macros for manipulating color values */
#define	PgRGB( r, g, b )	((PgColor_t)((b) & 0xFF) | ((PgColor_t)((g) & 0xFF) << 8) | ((PgColor_t)((r) & 0xFF) << 16))
#define	PgCMY( c, m, y )	(PgRGB( c, m, y ) ^ 0xFFFFFF)
#define	PgGrey( v )			(PgRGB( v, v, v ))
#define PgGray( v )			(PgRGB( v, v, v ))
#define PgBlueValue( c )	((int)((c) & 0xFF))
#define PgGreenValue( c )	((int)(((c) >> 8) & 0xFF))
#define PgRedValue( c )		((int)(((c) >> 16) & 0xFF))
#define	PgGreyValue( c )	( ((PgRedValue( c ) * 77) + (PgGreenValue( c ) * 151) + (PgBlueValue( c ) * 28)) >> 8)
#define	PgGrayValue( c )	( ((PgRedValue( c ) * 77) + (PgGreenValue( c ) * 151) + (PgBlueValue( c ) * 28)) >> 8)

/* Macros for manipulating 16-bit color values (565) */
#define Pg565to8888( c )		((((c) & 0x1F) << 3) | (((c) & 0x7E0) << 5) | (((c) & 0xF800) << 8))
#define Pg8888to565( c )		((((c) & 0xF8) >> 3) | (((c) & 0xFC00) >> 5) | (((c) & 0xF80000) >> 8))
#define PgRGB565( r, g, b )		((((b) & 0xF8) >> 3) | (((g) & 0xFC) << 3) | (((r) & 0xF8) << 8))
#define PgBlueValue565( c )		(((c) & 0x1F) << 3)
#define PgGreenValue565( c )	(((c) & 0x7E0) >> 3)
#define PgRedValue565( c )		(((c) & 0xF800) >> 8)

/* Macros for manipulating 16-bit color values (555) */
#define Pg555to8888( c )		((((c) & 0x1F) << 3) | (((c) & 0x3E0) << 6) | (((c) & 0x7C00) << 9))
#define Pg8888to555( c )		((((c) & 0xF8) >> 3) | (((c) & 0xF800) >> 6) | (((c) & 0xF80000) >> 9))
#define PgRGB555( r, g, b )		((((b) & 0xF8) >> 3) | (((g) & 0xF8) << 2) | (((r) & 0xF8) << 7))
#define PgBlueValue555( c )		PgBlueValue565( c )
#define PgGreenValue555( c )	(((c) & 0x3E0) >> 2)
#define PgRedValue555( c )		(((c) & 0x7C00) >> 7)

/* Macros for manipulating 16-bit color values (444) */
#define Pg444to8888( c )		((((c) & 0xF) << 4) | (((c) & 0xF0) << 8) | (((c) & 0xF00) << 12))
#define Pg8888to444( c )		((((c) & 0xF0) >> 4) | (((c) & 0xF000) >> 8) | (((c) & 0xF00000) >> 12))
#define PgRGB444( r, g, b )		((((b) & 0xF0) >> 4) | ((g) & 0xF0) | (((r) & 0xF8) << 4))
#define PgBlueValue444( c )		(((c) & 0xF) << 4)
#define PgGreenValue444( c )	((c) & 0xF0)
#define PgRedValue444( c )		(((c) & 0xF00) >> 4)

#define	PgLighterColor( c ) (PgRGB( (0xff-((0xff-PgRedValue( c )) >> 1)), \
									(0xff-((0xff-PgGreenValue( c )) >> 1)), \
									(0xff-((0xff-PgBlueValue( c )) >> 1)) ) )

#define	PgDarkerColor( c ) (PgRGB( (PgRedValue( c ) >> 1), \
									(PgGreenValue( c ) >> 1), \
									(PgBlueValue( c ) >> 1) ) )

#define	PgAverageColor( a, b ) (PgRGB( ((PgRedValue( a ) >> 1) + (PgRedValue( b ) >> 1)), \
									((PgGreenValue( a ) >> 1) + (PgGreenValue( b ) >> 1)), \
									((PgBlueValue( a ) >> 1) + (PgBlueValue( b ) >> 1)) ) )

/* Some common colors */
#define	Pg_TRANSPARENT		((PgColor_t)0xFFFFFFFF)
#define	Pg_INVERT_COLOR		((PgColor_t)0xFFFFFFFE)
#define	Pg_MIX_COLOR		((PgColor_t)0x1000000)
#define	Pg_INDEX_COLOR		((PgColor_t)0x2000000)
#define	Pg_DEVICE_COLOR		((PgColor_t)0x4000000)
#define	PgColorByIndex( v )	(Pg_INDEX_COLOR | ((v) & 0xFF))
#define	Pg_CLOSE_COLOR		((PgColor_t)0x4000000)
#define Pg_DEFAULT_WM_COLOR	((PgColor_t)0xFFFFFFFD)

#define	Pg_BLACK			PgGrey( 0 )
#define	Pg_WHITE			PgGrey( 255 )
#define	Pg_GREY				PgGrey( 192 )
#define	Pg_MGREY			PgGrey( 144 )
#define	Pg_DGREY			PgGrey( 96 )
#define	Pg_RED				PgRGB( 255, 0, 0 )
#define	Pg_GREEN			PgRGB( 0, 255, 0 ) 
#define	Pg_BLUE				PgRGB( 0, 0, 255 )
#define	Pg_YELLOW			PgRGB( 255, 255, 0 )
#define	Pg_MAGENTA			PgRGB( 255, 0, 255 )
#define	Pg_CYAN				PgRGB( 0, 255, 255 )
#define	Pg_CELIDON			(PgRGB( 39, 176, 136 ) | Pg_MIX_COLOR)

#define	Pg_WINDOWGREEN		PgRGB( 0, 128, 112 )
#define	Pg_BALLOONCOLOR		PgRGB( 254, 255, 177 )

#define Pg_GRAY				Pg_GREY
#define Pg_MGRAY			Pg_MGREY
#define Pg_DGRAY			Pg_DGREY

#define	Pg_DGREEN			PgRGB( 0, 160, 0 )
#define	Pg_DCYAN			PgRGB( 0, 128, 160 )
#define	Pg_DBLUE			PgRGB( 0, 0, 160 )
#define	Pg_BROWN			PgRGB( 96, 54, 0 )
#define	Pg_PURPLE			PgRGB( 133, 0, 182 )

/* The standard VGA palette */
#define	Pg_VGA0				PgRGB( 0, 0, 0 )
#define	Pg_VGA1				PgRGB( 0, 0, 168 )
#define	Pg_VGA2				PgRGB( 0, 168, 0 )
#define	Pg_VGA3				PgRGB( 0, 168, 168 )
#define	Pg_VGA4				PgRGB( 168, 0, 0 )
#define	Pg_VGA5				PgRGB( 168, 0, 168 )
#define	Pg_VGA6				PgRGB( 168, 84, 0 )
#define	Pg_VGA7				PgRGB( 168, 168, 168 )
#define	Pg_VGA8				PgRGB( 84, 84, 84 )
#define	Pg_VGA9				PgRGB( 84, 84, 255 )
#define	Pg_VGAA				PgRGB( 84, 255, 84 )
#define	Pg_VGAB				PgRGB( 84, 255, 255 )
#define	Pg_VGAC				PgRGB( 255, 84, 84 )
#define	Pg_VGAD				PgRGB( 255, 84, 255 )
#define	Pg_VGAE				PgRGB( 255, 255, 84 )
#define	Pg_VGAF				PgRGB( 255, 255, 255 )


/* Some useful patterns */
#define	Pg_PAT_DEFAULT		NULL
#define	Pg_PAT_NONE			((PgPattern_t) "\x00\x00\x00\x00\x00\x00\x00\x00")
#define	Pg_PAT_FULL			((PgPattern_t) "\xFF\xFF\xFF\xFF\xFF\xFF\xFF\xFF")
#define	Pg_PAT_HALF			((PgPattern_t) "\xAA\x55\xAA\x55\xAA\x55\xAA\x55")
#define	Pg_PAT_CHECKB8		((PgPattern_t) "\xF0\xF0\xF0\xF0\x0F\x0F\x0F\x0F")
#define	Pg_PAT_CHECKB4		((PgPattern_t) "\xCC\xCC\x33\x33\xCC\xCC\x33\x33")
#define	Pg_PAT_BACK_HALF	((PgPattern_t) "\x55\xAA\x55\xAA\x55\xAA\x55\xAA")
#define	Pg_PAT_DIAMOND		((PgPattern_t) "\x10\x38\x7C\xFE\x7C\x38\x10\x00")
#define	Pg_PAT_HORIZ8		((PgPattern_t) "\xFF\x00\x00\x00\x00\x00\x00\x00")
#define	Pg_PAT_HORIZ4		((PgPattern_t) "\xFF\x00\x00\x00\xFF\x00\x00\x00")
#define	Pg_PAT_HORIZ2		((PgPattern_t) "\xFF\x00\xFF\x00\xFF\x00\xFF\x00")
#define	Pg_PAT_VERT8		((PgPattern_t) "\x80\x80\x80\x80\x80\x80\x80\x80")
#define	Pg_PAT_VERT4		((PgPattern_t) "\x88\x88\x88\x88\x88\x88\x88\x88")
#define	Pg_PAT_VERT2		((PgPattern_t) "\xAA\xAA\xAA\xAA\xAA\xAA\xAA\xAA")
#define	Pg_PAT_DIAGF8		((PgPattern_t) "\x80\x01\x02\x04\x08\x10\x20\x40")
#define	Pg_PAT_DIAGF4		((PgPattern_t) "\x88\x11\x22\x44\x88\x11\x22\x44")
#define	Pg_PAT_DIAGB8		((PgPattern_t) "\x80\x40\x20\x10\x08\x04\x02\x01")
#define	Pg_PAT_DIAGB4		((PgPattern_t) "\x88\x44\x22\x11\x88\x44\x22\x11")
#define	Pg_PAT_BRICK		((PgPattern_t) "\x20\x20\xFF\x02\x02\x02\xFF\x20")
#define	Pg_PAT_WEAVE		((PgPattern_t) "\x3E\x1D\x88\xD1\xE3\xC5\x88\x5C")
#define	Pg_PAT_RXHATCH8		((PgPattern_t) "\xFF\x80\x80\x80\x80\x80\x80\x80")
#define	Pg_PAT_RXHATCH4		((PgPattern_t) "\xFF\x88\x88\x88\xFF\x88\x88\x88")
#define	Pg_PAT_RXHATCH2		((PgPattern_t) "\xFF\xAA\xFF\xAA\xFF\xAA\xFF\xAA")
#define	Pg_PAT_DXHATCH8		((PgPattern_t) "\x80\x41\x22\x14\x08\x14\x22\x41")
#define	Pg_PAT_DXHATCH4		((PgPattern_t) "\x88\x55\x22\x55\x88\x55\x22\x55")

/*
 *	Flags used for various commands
 */

#define Pg_RELATIVE		(0x01 << 8)
#define Pg_CENTER_BASED	(0x00 << 8)
#define Pg_EXTENT_BASED	(0x01 << 8)
#define Pg_CLOSED		(0x10 << 8)
#define Pg_BACK_FILL	(0x01 << 8)
#define	Pg_SMART_BLIT	(0x01 << 8)
#define	Pg_EXPOSE_SOURCE (0x02 << 8)
#define	Pg_REPBM_ALTERNATE	(0x10ul<<16)

/*
 * Stroke and Fill rules
 *	PgDrawPolygon
 */
#define 	Pg_POLY_STROKE				Pg_DRAW_STROKE
#define 	Pg_POLY_STROKE_CLOSED		Pg_DRAW_STROKE | Pg_CLOSED
#define 	Pg_POLY_FILL				Pg_DRAW_FILL
#define		Pg_POLY_RELATIVE			Pg_RELATIVE
#define		Pg_REL_POLY_STROKE			(Pg_POLY_STROKE | Pg_POLY_RELATIVE)
#define		Pg_REL_POLY_STROKE_CLOSED	(Pg_POLY_STROKE_CLOSED | Pg_POLY_RELATIVE)
#define		Pg_REL_POLY_FILL			(Pg_POLY_FILL | Pg_POLY_RELATIVE)

/*
 * Draw arc flags
 *	PgDrawArc 
 */
#define Pg_ARC_CHORD	(0x00 << 8)
#define Pg_ARC_PIE		(0x10 << 8)
#define Pg_ARC			(0x20 << 8)
#define	Pg_ARC_FILL		Pg_DRAW_FILL
#define	Pg_ARC_STROKE	Pg_DRAW_STROKE

#define		Pg_ARC_STROKE_CHORD		Pg_DRAW_STROKE | Pg_ARC_CHORD
#define		Pg_ARC_STROKE_PIE		Pg_DRAW_STROKE | Pg_ARC_PIE
#define		Pg_ARC_STROKE_ARC		Pg_DRAW_STROKE | Pg_ARC
#define		Pg_ARC_FILL_CHORD		Pg_DRAW_STROKE | Pg_ARC_CHORD
#define		Pg_ARC_FILL_PIE			Pg_DRAW_FILL | Pg_ARC_PIE

/*
 * Line Joins - only relevant for lines thicker than 1 pixel
 *	PgSetLineJoin
 */	 
#define 	Pg_MITER_JOIN				0x00		/* default */
#define 	Pg_ROUND_JOIN				0x01
#define 	Pg_BEVEL_JOIN				0x02
#define 	Pg_QROUND_JOIN				0x03
#define		Pg_BUTT_JOIN				0x04

/*
 * Line Caps - only relevant for lines thicker than 1 pixel
 *	PgSetLineCap
 */	 
#define 	Pg_BUTT_CAP					0x00		/* default */
#define 	Pg_ROUND_CAP				0x01
#define 	Pg_SQUARE_CAP				0x02
#define 	Pg_POINT_CAP				0x03

/*
 * Line dashing flags
 *	PgSetLineDash 
 */
#define		Pg_DASH_INVERT				0x40
#define		Pg_DASH_SLOPE_ADJ			0x80

/*
 * Text Underline Flags
 */

#define Pg_DOUBLE_UNDERLINE	0x10

/*
 * Text Justification Flags
 */
 
#define	Pg_TEXT_UTF2CHAR	(0x04 << 8)
//#define	Pg_TEXT_UTF4CHAR	(0x02 << 8)
#define	Pg_TEXT_WIDECHAR	(Pg_TEXT_UTF2CHAR)
//#define	Pg_TEXT_VWIDECHAR	(Pg_TEXT_UTF4CHAR)
//#define	Pg_TEXT_TERMCHAR	(0x06 << 8)
#define	Pg_TEXT_SIZE_HINT	(0x02 << 8)
#define	Pg_TEXT_AREA		(0x08 << 8)

#define Pg_TEXT_LEFT	(0x10 << 8)
#define Pg_TEXT_RIGHT	(0x20 << 8)
#define Pg_TEXT_CENTER	( Pg_TEXT_LEFT | Pg_TEXT_RIGHT )
#define Pg_TEXT_TOP		(0x40 << 8)
#define Pg_TEXT_BOTTOM	(0x80 << 8)
#define Pg_TEXT_MIDDLE	( Pg_TEXT_TOP | Pg_TEXT_BOTTOM )

typedef struct {
	unsigned int			c:16;
	unsigned int			FGColor:4;
	unsigned int			BGColor:4;
	unsigned int			Highlight:1;
	unsigned int			Blinking:1;
	unsigned int			Underline:1;
	unsigned int			ReverseVideo:1;
	unsigned int			Italic:1;
	unsigned int			Bold:1;
	unsigned int			User:1;
	unsigned int			Selected:1;
} PgTermChar_t;

/*
 * Color compare operators, Photon.mach specific
 *	PgSetAuxFn
 */
#define		Pg_OVRFN_FALSE				0		/* default */
#define		Pg_OVRFN_TRUE				1		/* don't draw */
#define		Pg_OVRFN_GE					2
#define		Pg_OVRFN_LT					3
#define		Pg_OVRFN_NE					4
#define		Pg_OVRFN_EQ					5
#define		Pg_OVRFN_LE					6
#define		Pg_OVRFN_GT					7

typedef struct {
	short		x1, x2;
	short		y;
} PgSpan_t;

typedef struct {
	signed char		x, y;
} PgTinyPoint_t;

/*
 * Cursor definition structure (for use with PgSetCursorBitmap)
 * An array of upto 2 of these may be used to define a cursor
 */
typedef struct {
	char		*Image;
	PhPoint_t	Size;
	PhPoint_t	Offset;
	PgColor_t	Color;
	char		BytesPerLine;
	char		Spare[3];
} PgCursorDef_t;

/* Limits */
#define _Pg_MAX_FONT_LEN		MAX_FONT_TAG
#define _Pg_MAX_SHMEM_NAME_LEN	16
#define _Pg_MAX_DATA_MX			63
#define _Pg_MAX_DASH_LIST		16
#define _Pg_MAX_PALETTE			256

#define	_PgGC_DitherSet			0x0001
#define	_PgGC_TranspSet			0x0002
#define _PgGC_ScaleSet			0x0004
#define _PgGC_TranslationSet	0x0008
#define _PgGC_RotationSet		0x0010
#define _PgGC_UserClipSet		0x0020
#define _PgGC_SoftPaletteSet	0x0040
#define _PgGC_AuxClipSet		0x0080
#define	_PgGC_XORColorSet		0x0100

/*
 * The graphics context
 */
typedef	struct _Pg_common_gc {
	PgColor_t		primary, secondary;
	char			dither_pattern[8];
	char			transp_pattern[8];
	unsigned long	flags;
	long			spare;
} PgCommonGC_t;

typedef struct _Pg_stroke_gc {
	PgCommonGC_t	com;
	long			width;
	char			join;
	char			cap;
	char			spareB[2];
	char			dash_list[_Pg_MAX_DASH_LIST];
	long			dash_flags;
	long			dash_scale;
	long			spare[4];
} PgStrokeGC_t;

typedef struct _Pg_fill_gc {
	PgCommonGC_t	com;
} PgFillGC_t;

typedef struct _Pg_text_gc {
	PgCommonGC_t	com;
	char			font[_Pg_MAX_FONT_LEN];
	PgColor_t		underline[2];
	unsigned short	underline_flags;
	short			spareS;
	long			BGColor;		// this WILL become a spare!
} PgTextGC_t;

typedef struct Ph_gc {
	unsigned long	gc_flags;
	PhRid_t			rid, target_rid;
	PgStrokeGC_t	stroke;
	PgFillGC_t		fill;
	PgTextGC_t		text;
	unsigned long	plane_mask;
	unsigned short	draw_mode;
	unsigned short	spareS;
	PhLpoint_t		scale;
	PhPoint_t		translation;
	unsigned short	rotation;
	PhRect_t		*clip_rects;
	unsigned short	n_clip_rects;
	unsigned short	max_clip_rects;
	PhRect_t		*user_clip_rects;
	unsigned short	n_user_clip_rects;
	unsigned short	max_user_clip_rects;
	PhRect_t		aux_clip_rect;
	int				aux_clip_valid;
	long			palette_id;
	PgColor_t		*palette;
	unsigned short	num_colors;
	unsigned short	start_color;
	unsigned short	palette_flags;
	unsigned short	context_set_flags;
	PhRect_t		event_clip_extent;
	PhRect_t		user_clip_extent;
	PhRect_t		total_clip_extent;
	long			palette_tag;
	long			spare;
} PhGC_t;

/* Simple font metrics */
/* This is also defined in PhInternal.h ??? */
struct _Ph_font_widths {
	char			face[20];
	PhRect_t		extent;
	ushort_t		valid;
	ushort_t		ascii_offset;
	ushort_t		ascii_length;
	char			widths[256];
};

struct _Ph_font_widths2 {
	char			face[20];
	PhRect_t		extent;
	ushort_t		valid;
	ushort_t		ascii_offset;
	ushort_t		ascii_length;
	char			*widths;
};

#ifdef NEW_FONT_CACHE
typedef struct {
	int 		CurFontRangeL;
	int			CurFontRangeH;
	char 		*ScriptBasePtr;
	char 		*ScriptPtr;
	char 		*ScriptRuleFlags;
	int 		ScriptNRules;
	int 		ScriptSize;
} FontAliasInfoType;
#endif

/* Graphics library state */
struct _Ph_g_info {
	unsigned long				cmd_buffer_size;
	long						*cmd_buffer;
	long						*cmd_ptr;
	long						*cmd_base_ptr;
	unsigned 					cmd_buf_limit; 
	unsigned 					data_buf_len;
	#ifdef __QNXNTO__
		struct iovec 			data_mx[_Ph_MAX_DATA_MX + 1];
	#else
		struct _mxfer_entry 	data_mx[_Ph_MAX_DATA_MX + 1];
	#endif
	unsigned					mx_offsets[_Ph_MAX_DATA_MX + 1];
	unsigned					n_data_mx;
	unsigned					context_len;
	unsigned					n_fonts;
#ifdef NEW_FONT_CACHE
	long						spare[3];
	FontAliasInfoType			*falias_ctrl;
	struct _Ph_font_widths2		*fonts;
#else
	long						spare[4];
	struct _Ph_font_widths		**fonts;
#endif
};

/*
 *  Shared memory reference record structure (embedded in the draw buffer)
 */

typedef struct {
	short			rec_size;
	short			rec_type;
	unsigned long	offset;
	unsigned long	limit;
	unsigned long	obj_size;
	long			spare;
	char			name[_Pg_MAX_SHMEM_NAME_LEN];
} _PgShmemRefStruct;

#define	Pg_XADDR_SHMEM		0
#define	Pg_XADDR_INLINE		1

/* 
 * Draw command opcodes (embedded in the draw buffer)
 */
 
// #define	Pg_CMD_ADDR_EXTENDED		0x00010000
// #define	Pg_CMD_ADDR_INDIRECT		0x00020000

#define	Pg_CMD_CMD_SIZE_MASK		0xFFFC0000
#define	Pg_CMD_CAH_COUNT_MASK		0x00030000
#define	Pg_CMD_CAH_COUNT_UNIT		0x00010000
#define	Pg_CMD_CAH_COUNT_1			0x00010000
#define	Pg_CMD_CAH_COUNT_2			0x00020000
#define	Pg_CMD_CAH_COUNT_3			0x00030000

typedef struct {
	unsigned long		flags;
	unsigned short		inline_offset;
	unsigned short		inline_size;
	char				*shmem_name;
	unsigned long		shmem_limit;
	unsigned long		shmem_offset;
	unsigned long		srce_tag;
	unsigned long		srce_offset;
	unsigned long		srce_size;
} CAHinfo_t;

#define	Pg_CAH_RECORD_SIZE_MASK		0x0000003F
#define	Pg_CAH_INLINE_OFF_SIZE		0x00000040
#define	Pg_CAH_SHMEM_NAME			0x00000080
#define	Pg_CAH_SHMEM_LIMIT			0x00000100
#define	Pg_CAH_SHMEM_OFFSET			0x00000200
#define	Pg_CAH_SRCE_TAG				0x00000400
#define	Pg_CAH_SRCE_OFFSET			0x00000800
#define	Pg_CAH_SRCE_SIZE			0x00001000
#define	Pg_CAH_RELAY_TAGGED			0x00002000


/*
 *  General set opcodes
 */

#define	Pg_END_OF_DRAW				0x00
#define	Pg_SET_DEFAULT_STATE		0x01
#define Pg_SET_DRAW_MODE			0x02
#define Pg_SET_PLANE_MASK			0x03
#define	Pg_SET_USER_CLIP			0x06
#define	Pg_SET_AUX_CLIP				0x07
#define	Pg_SET_PALETTE				0x08
#define	Pg_SET_TRANSLATION			0x09
#define	Pg_SET_SCALE				0x0A
#define	Pg_SET_ROTATION				0x0B

/*
 *  Stroke set opcodes
 */
#define	Pg_SET_STROKE_COLOR			0x10
#define	Pg_SET_STROKE_XOR_COLOR		0x11
#define	Pg_SET_STROKE_DITHER		0x12
#define	Pg_SET_STROKE_TRANSP		0x13
#define	Pg_SET_STROKE_WIDTH			0x14
#define	Pg_SET_STROKE_CAP			0x15
#define	Pg_SET_STROKE_JOIN			0x16
#define	Pg_SET_STROKE_DASH			0x17

/*
 *  Fill set opcodes
 */
#define	Pg_SET_FILL_COLOR			0x20
#define	Pg_SET_FILL_XOR_COLOR		0x21
#define	Pg_SET_FILL_DITHER			0x22
#define	Pg_SET_FILL_TRANSP			0x23

/*
 *  Text (and bitmap) set opcodes
 */
#define	Pg_SET_TEXT_COLOR			0x30
#define	Pg_SET_TEXT_XOR_COLOR		0x31
#define	Pg_SET_TEXT_DITHER			0x32
#define	Pg_SET_TEXT_TRANSP			0x33
#define	Pg_SET_TEXT_FONT			0x34
#define	Pg_SET_TEXT_UNDERLINE		0x35

/*
 *  Simple draw opcodes
 */
#define	Pg_DRAW_POINT				0x40
#define	Pg_DRAW_POINT_ARRAY			0x41
#define	Pg_DRAW_LINE				0x42
#define	Pg_DRAW_TEXT				0x43
#define	Pg_DRAW_BITMAP				0x44
#define	Pg_DRAW_IMAGE				0x45
#define	Pg_DRAW_BITBLT				0x46
#define	Pg_DRAW_BITBLIT				0x46
#define	Pg_DRAW_GRID				0x47
#define	Pg_DRAW_TREND				0x48
#define	Pg_DRAW_VECTOR				0x49
#define	Pg_DRAW_BITBLT_CHROMA		0x4A
#define Pg_MOVE_DISPLAY				0x4D
#define	Pg_DRAW_GETIMAGE			0x4F

/*
 *  Fill and/or Stroke draw opcodes
 *   OR will Pg_DRAW_FILL, Pg_DRAW_STROKE or Pg_DRAW_FILL_STROKE
 */
#define	Pg_DRAW_POLYGON				0x40
#define	Pg_DRAW_RECT				0x41
#define	Pg_DRAW_RRECT				0x42
#define	Pg_DRAW_ELLIPSE				0x43
#define	Pg_DRAW_ARC					0x44
#define	Pg_DRAW_BEVELBOX			0x45
#define	Pg_DRAW_SPAN				0x46
#define	Pg_DRAW_BEZIER				0x47

#define	Pg_DRAW_STROKE				0x10
#define	Pg_DRAW_FILL				0x20
#define	Pg_DRAW_FILL_STROKE			(Pg_DRAW_FILL | Pg_DRAW_STROKE)
#define	Pg_DRAW_STROKE_FILL			Pg_DRAW_FILL_STROKE


#define Pg_DELETE_CURSOR			0x80
#define Pg_SET_CURSOR_POSITION		0x81
#define Pg_SET_CURSOR_CHAR			0x82
#define Pg_SET_CURSOR_BITMAP		0x83
#define Pg_SET_DRAG_CURSOR			0x84


/*
 *  Extension draw commands.
  */
#define Pg_DLL_CMDS                 0xD0
#define Pg_TARGET_STREAM            0xD1
#define Pg_DRAW_GRADIENT            0xD2
#define Pg_SYNC                     0xD3
#define Pg_SWAP_DISPLAY             0xD4
#define Pg_ENDIAN_TEST              0xD5


/*
 * Printer drawstream commands.
 */
#define Pg_PRINTER_CMD				0xF1


/*
 *	What to test before drawing
 */
#define	Pg_TEST_STROKE				(Pg_DRAW_STROKE)
#define	Pg_TEST_FILL				(Pg_DRAW_FILL)
#define	Pg_TEST_FILL_STROKE			(Pg_DRAW_FILL | Pg_DRAW_STROKE)
#define Pg_TEST_TEXT				1		// 0x0100	// 0x1
#define	Pg_TEST_BITMAP				2		// 0x0200	// 0x2
// #define	Pg_TEST_PALETTE				0x1000	// unused??

#define	Pg_SETGAMMA_Factor			0x0001
#define	Pg_SETGAMMA_CFactor			0x0002
#define	Pg_SETGAMMA_CBlack			0x0004
#define	Pg_SETGAMMA_CWhite			0x0008
#pragma pack()


typedef struct Ph_grafx_detail
{
	ulong_t 	valid_fields;
	ulong_t		reserved;
	ulong_t		video_opt;
	ulong_t		driver_opt;
	ulong_t		gui_opt;
	ulong_t		cardspec_opt;
	ulong_t 	card_type;
	ulong_t 	card_sub_type;
	PhPoint_t	presolution;
	PhPoint_t	vresolution;
	ulong_t		vram_size;
	ushort_t	num_cursor;
	ushort_t	num_palette;
	ulong_t		pointbuf_size;
	ulong_t		workspace_size;
	ulong_t		spareA[2];
	ulong_t		bytes_per_line;
	ulong_t		bits_per_pixel;
	uchar_t		bits_blue, bits_green, bits_red, bits_overlay;
	uchar_t		bpos_blue, bpos_green, bpos_red, bpos_overlay;
	uchar_t		dac_size;
	uchar_t		spareC[3];
	ulong_t		spareB[2];
} PhGrafxDetail_t;

#define	Ph_GFXVAL_VOPT			0x00000001
#define	Ph_GFXVAL_DOPT			0x00000002
#define	Ph_GFXVAL_GOPT			0x00000004
#define	Ph_GFXVAL_COPT			0x00000008
#define	Ph_GFXVAL_CARDTYPE		0x00000010
#define	Ph_GFXVAL_CARDSUBTYPE	0x00000020
#define	Ph_GFXVAL_PRES			0x00000100
#define	Ph_GFXVAL_VRES			0x00000200
#define	Ph_GFXVAL_VRAMSIZE		0x00000800
#define	Ph_GFXVAL_NCURSOR		0x00001000
#define	Ph_GFXVAL_NPALETTE		0x00002000
#define	Ph_GFXVAL_POINTBS		0x00004000
#define	Ph_GFXVAL_WORKSPACES	0x00008000
#define	Ph_GFXVAL_BPL			0x00100000
#define	Ph_GFXVAL_BPP			0x00200000
#define	Ph_GFXVAL_BITPOS		0x00400000
#define	Ph_GFXVAL_DACSIZE		0x00800000

/* video_opt */
#define	Ph_GFXV_MONOCHROME		0x00000001
#define	Ph_GFXV_PALETTE16		0x00000002
#define	Ph_GFXV_PALETTE256		0x00000004
#define	Ph_GFXV_DIRECT			0x00000010
#define	Ph_GFXV_OVERLAY			0x00000020
#define	Ph_GFXV_VIDEO_READABLE	0x00001000
#define	Ph_GFXV_NONINTERLACED	0x00002000

/* driver_opt */
#define	Ph_GFXD_VPANNING		0x00000001
#define	Ph_GFXD_HARDROT			0x00000002
#define	Ph_GFXD_SCALEING		0x00000004
#define	Ph_GFXD_DITHERSTROKE	0x00000008

/* gui_opt */
#define	Ph_GFXG_HWCURSOR		 0x00000001
#define	Ph_GFXG_HWBITBLT		 0x00000002
#define	Ph_GFXG_MASKBLIT		 0x00000004
#define	Ph_GFXG_OFFSCREENMEM	 0x00000008
#define	Ph_GFXG_DMXOR			 0x00000010
#define	Ph_GFXG_DMANDOR			 0x00000020
#define	Ph_GFXG_DMEXTENDED		 0x00000040
#define Ph_GFXG_HWBITBLT_CHROMA  0x00000080
#define Ph_GFXG_HWBITBLT_STRETCH 0x00000100

typedef struct Ph_grafx_detail_region_data
{
	PhRegionDataHdr_t	hdr;
	PhGrafxDetail_t		detail;
} PhGrafxDetailRegionData_t;

typedef struct PgVidMem
{
	int type;			//How Memory is to be interpreted (8-bit palette, 16-bit Direct Color, etc)
	int bpl;			//Bytes Per Line
	int bpp;			//Bits Per Pixel
	PhDim_t size;		//Width and Height of the Video Memory
	unsigned long tag;	//ID, do not mess with this!  The Video Driver sets it up and requires it unchanged!

	volatile unsigned char *vm_ptr8;		//8-bit pointer to Video memory for this area
	volatile unsigned short *vm_ptr16;		//16-bit pointer to Video memory for this area
	volatile unsigned long *vm_ptr32;		//32-bit pointer to Video memory for this area
} PgVidMem_t;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif /* __PH_GLIB_H_ */
