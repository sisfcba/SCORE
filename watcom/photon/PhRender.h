#ifndef __PHRENDER_H
#define __PHRENDER_H
 
#ifdef __cplusplus
extern "C" {
#endif

#include <photon/PhGeom.h>
#include <photon/PhGRColor.h>

#ifndef __QNX_GENERAL_STRUCT
//
//  These are left as opaque types for the casual user.
//  The ``__QNX_GENERAL_STRUCT'' definition is for graphic-subsystem
//  definitions/development.
//
struct _render_ctrl ;	        // Undefined Forward definition
struct GR_driver_state_struct;	// Undefined Forward definition
struct GR_draw_functions;		// Undefined Forward definition
typedef struct GR_driver_state_struct GR_DriverStateStruct;

#endif //  __QNX_GENERAL_STRUCT

struct pal_entry { /* Identical to Photon GRColor_t & Windows PALETTEENTRY */
	unsigned char b;
	unsigned char g;
	unsigned char r;
	unsigned char i;
	} ;

struct rgb_entry {
	unsigned char b;
	unsigned char g;
	unsigned char r;
	} ;

#ifdef _PH_GEOM_H

#else
#error could not find PhGeom.h

struct _point {
	short x;
	short y;
	} ;

struct _dim {
	short w;
	short h;
	} ;

struct _area {
	short x;
	short y;
	short w;
	short h;
	} ;

struct _rect {
	struct _point ul;
	struct _point lr;
	} ;

#endif // _PH_GEOM

struct _slice {
	short x;
	short y;
	short w;
	short h;
	int bpl;
	int bpp;
	} ;

/*********************************************************

Photon Coordinates (24 bits/pixel)     Printer Coordinates ("N" bits/dot)

                                       (0,0)
                                       +----------------------------------+
+---------------------------------->   |  page(x,y)                       |
|   src(x,y)                           |  +----------------------------+  |
|   +----------------------------+     |  |                            |  |
|   |                            |     |  |                            |  |
|   |                            |     |  |                            |  |
|   | clip.ul(x,y)               |     |  |                            |  |
|   | +------------------------+ |     |  | pslice(x,y)                |  |
|   | |                        | |     |  | +------------------------+ |  |
| ########                     | |     |  | |(0,0)     Print Buffer  | |  |
| ########---------------------+ |     |  | |           Coordinates  | |  |
| ########          clip.lr(h,w) |     |  | |######         pbuf(h,w)| |  |
|   |                            |     |  | +------------------------+ |  |
|   |                            |     |  |                pslice(h,w) |  |
|   |                            |     |  |                            |  |
|   |                            |     |  |                            |  |
|   |                            |     |  |                            |  |
|   |                            |     |  |                            |  |
|   |                            |     |  |                            |  |
|   +----------------------------+     |  |                            |  |
|                         src(h,w)     |  |                            |  |
|                                      |  |                            |  |
|                                      |  |                            |  |
V                                      |  +----------------------------+  |
                                       |                       page(h,w)  |
                                       +----------------------------------+
                                                                 paper(h,w)
Other Mappings: src_dpi(x,y) paper_dpi(x,y)
**********************************************************/

/*
 * Bit field of values which have been specifically set in the draw
 * stream for this page
 */
#define IsSrcDim		0x00000001
#define IsSrcOff		0x00000004
#define IsPrinterDpi	0x00000010
#define IsPaperSize		0x00000040
#define IsMargins		0x00000100
#define IsBorder		0x00000200
#define IsSrcDpi		0x00001000
#define IsScale			0x00004000
#define IsCopies		0x00008000
#define IsColorMode		0x00010000
#define IsOrientation	0x00020000
#define IsPaperSource	0x00040000
#define IsPaperType		0x00080000
#define IsPaperCollate	0x00100000
#define IsDuplex		0x00200000
#define IsDither		0x00400000
#define IsIntensity		0x00800000
#define IsInkType		0x01000000
#define IsSrcColors		0x02000000
#define IsColors		0x04000000
#define IsPageRange		0x10000000

/*
 * Paper Source Codes
 */
#define PaperSourceDefault		0x0000 // Don't care
#define PaperSourceAuto			0x0001 // Auto
#define PaperSourceUpper		0x0002 // Upper
#define PaperSourceLower		0x0003 // Lower         
#define PaperSourceManual		0x0004 // Manual feed        
#define PaperSourceEnvelope		0x0005 // Envelope
#define PaperSourceManualEnv	0x0006 // Envelope (manual feed)

/*
 * Paper Type Codes
 */
#define PaperTypeDefault		 0x0000 // don't care
#define PaperTypeNormal			 0x0001 // normal quality
#define PaperTypeHighQuality	 0x0002 // high quality
#define PaperTypeDraftQuality	 0x0003 // draft quality
#define PaperTypeTransparency	 0x0004 // transparency
#define PaperTypeEnvelope		 0x0005 // envelope
#define PaperTypeTShirt			 0x0006 // t-shirt (reversed image)

/*
 * Paper Collate Codes
 */
#define PaperCollateDefault		 0x0000 // don't care
#define PaperCollateABCABCABC	 0x0001 // normal
#define PaperCollateAAABBBCCC	 0x0002 // interleaved

/*
		Orientation			SWAP_XY		REVERSE_X
	0	Pp_PORTRAIT			no			no
	1	Pp_LANDSCAPE		yes			yes
	2	Pp_TSHIRT			no			yes
	3	Pp_LANDSCAPE_TSHIRT	yes			no
 */

#define Pp_PORTRAIT			0
#define Pp_LANDSCAPE		1
#define Pp_TSHIRT			2
#define Pp_LANDSCAPE_TSHIRT	3

/*
 * Flags
 */

#define RF_DO_PALETTE				0x0001
#define RF_DO_RAM					0x0002
#define RF_FORCE_ANTIALIAS			0x0004
#define RF_DONT_FONTMAP				0x0008
#define RF_DONT_COPY				0x0010
#define RF_BUF_MALLOCED				0x0020
#define RF_FUNCS_LOADED				0x0040
#define RF_CTRL_MALLOCED			0x0080
#define RF_ONE2ONE					0x0100
#define RF_NEVER_ANTIALIAS			0x0200
#define RF_DRAWFUNCS_AVAILABLE		0x0400
#define RF_DRAWFUNCS_MALLOCED		0x0800

/*
	Bits	Palette		RGB				GREY	CMY				CMYK
	1 		pal2        ---         	k1      ---             ---
	2       pal4        ---				k2      ---				---
	4		pal16		r1,g1,b1,x1		k4		c1,m1,y1,x1		c1,y1,m1,k1
	8       Pal256		r2,g2,b2,x2		k8		c2,m2,y2,x2		c2,m2,y2,k2
	16		---			r5,g6,r5		---     c5,m6,y5		c4,m4,y4,k4
	24      ---			r8,g8,b8		---		c8,m8,y8		c6,m6,y6,k6
	32      ---			---				---		---				c8,m8,y8,k8
 */

/*
 * Color Formats
 */
#define Pp_RGB_111
#define Pp_RGB_222
#define Pp_RGB_565
#define Pp_RGB_888
#define Pp_GREY_1
#define Pp_GREY_2
#define Pp_GREY_4
#define Pp_GREY_8
#define Pp_CMY_111
#define Pp_CMY_222
#define Pp_CMY_565
#define Pp_CMY_888
#define Pp_CMYK_1111
#define Pp_CMYK_2222
#define Pp_CMYK_4444
#define Pp_CMYK_6666
#define Pp_CMYK_8888

struct _doc_ctrl {
	unsigned flags;
	unsigned specified;	// Bit field of fields which are specified in draw stream
	unsigned spare_fields;		// Spare Bit field
	/*
	 * The current print state (a result of merging local printer
	 * defaults, with command-line overrides, and print commands
	 * extracted from the draw stream). Those fields which were
	 * specified in the draw stream are identified in the 'specified'
	 * bit field.
	 */
	int src_colors;		// number of colors available per source pixel
	int colors;			// number of colors available per printer pixel
	struct Ph_areahw src;	// Source Area (Photon Coordinates)
	struct Ph_point pres;	// Printer Resolution (dots per inch)
	struct Ph_dim paper;  // Paper Size (in 1/1000 inch) 
	struct Ph_rect margins;		// User-specified margin (in 1/1000 inch)
	struct Ph_rect border;		// Non-printable area (in 1/1000 inch)
	struct Ph_point sres;	// Source Resolution (dots per inch)
	struct Ph_point scale;// in 1/1000 units. 0 means fit. -1 means maintain aspect ratio.
	int copies;			// 1..n
	int colormode;		// 0=B&W, 1=GreyScale, 2=Color
	int orientation;	// 0=Portrait, 1=Landscape
	int paper_source;	// Code
	int paper_type;		// Code
	int paper_collate;	// Code
	int duplex;			// 0=off, 1=on
	int dither;			// Code
	int intensity;		// 0 to 100,000 (0 to 100% in 1/1000 percent)
	int ink_type;		// Code
	char *printer_name;
	char *printer_location;
	char *printer_device;
	char *printer_filter;
	char *userid;
	char *job_name;
	char *submission_date;
	/*
	 * Multi-pass control info
	 */
	struct Ph_rect clip;		// Photon coordinates
	/*
	 * Current page info
	 */
	int firstpage;
	int lastpage;
	int curpage;
	/*
	 * Printer Rendering Control
	 */
	struct _slice slice;
	struct _slice page;

	char *ram_buffer;
	int ram_size;

	struct pal_entry *palette;
	int pal_colors;
	unsigned long color;	// Either a palette index or a rgb value
	unsigned long pattern;
	int drawmode;
	char mask[8];

	unsigned long bg_color;
	unsigned long fg_color;
	unsigned long *gray;	// 16 shades of gray  (0==white, F==black)

	int bits;				// #bits per pixel in ram buffer
	int color_format;		// Layout of color information in each RAM pixel

	/*
	 * Current File Info
	 */
	char *filename;
	/*
	 * Print Complete Action Info
	 */
	unsigned long action_handle;
	char *action_path;

	int curcopy;
	unsigned short sliceh;
	unsigned short slicew;
	struct _render_ctrl *RC;	// Used by render engine
	int imgtype;
	int numpages;	// 0 if not known yet.
	int nclip;
	struct Ph_rect *cliplist;
	unsigned short srch; // (c->orientation&Pp_LANDSCAPE)? c->src.w : c->src.h
	unsigned short srcw; // (c->orientation&Pp_LANDSCAPE)? c->src.h : c->src.w
	short *xmap;
	short *ymap;
	char *workbuf;
	int workbufsize;
    unsigned char string_extent_attempts;     // Number of times my_string loops
                                             // to get the right fractional_extent
	unsigned char c_zero[3];
	unsigned long zero[7];
	
	
	int (*fn_X)( int x );
	int (*fn_Y)( int y );
	int (*fn_Rect)( int x, int y, unsigned long color, int w, int h );
	int (*fn_my_fillbuffer)( unsigned long color );
	int (*fn_my_ncolors)();
	int (*fn_my_getpalette)( struct pal_entry *pbuf);
	int (*fn_my_setpalette)( int n, struct pal_entry *pbuf );
	int (*fn_my_set_transparency)( unsigned char *pattern, int xoff, int yoff );
	int (*fn_my_set_dither)( unsigned char *pattern, int xoff, int yoff );
	int (*fn_my_setcolor)(GR_Color_t color, int index1, int index2, unsigned long pattern, int pass);
	void (*fn_my_setdrawmode)(int mode);
	int (*fn_my_fillrect)(int x1, int y1, int x2, int y2);
	void (*fn_my_patline)(int x, int y, int w, int pat);
	void (*fn_my_patfillrect)(int x1, int y1, int x2, int y2, char *pat);
	int (*fn_my_bitmap)( int x, int y, char *bits, int xoff, int yoff, int xsize, int ysize, int bpl );
	int (*fn__my_bitmap)( int x, int y, char *bits, int xoff, int yoff, int xsize, int ysize, int bpl );
	int (*fn_my_image)( int x, int y, int h, int w, char *image, int bpl,
				int xoff, int yoff, int type,
				int palsize, unsigned long *palette, char *palmap,
				int trasp_bpl, char *trasp_bits );
	int (*fn_my_drawline)(int x1, int y1, int x2, int y2);
	int (*fn_my_ispalette)();
	int (*fn_my_string)( int x, int y, char *str, int len,
				char *font, unsigned long color, int bkgd,
				struct Ph_rect *sclip, int areaflag, struct Ph_rect *sextent );
	unsigned long (*fn_my_getpixel)( int x, int y );
	unsigned long (*fn_my_palcolor)( int index );
	int (*fn_my_blit)(int x1, int y1, int w, int h, int x2, int y2);
	void * (*fn_my_getdataptr)(unsigned long *CAHPtr, unsigned long *DLPtr);
	int (*fn_my_delete_cursor)(int CNum);
	int (*fn_my_set_cursor_pos)(int CNum, int x, int y);
	int (*fn_my_set_drag_pos)(int CNum, int x1, int y1, int x2, int y2);
	int (*fn_my_set_cursor_char)(int CNum, int ch1, int color1, int ch2, int color2 );
	int (*fn_my_set_cursor_bitmap)(int CNum,
		int bpl1, int color1, int w1, int h1, int x1, int y1, char *bmap1,
		int bpl2, int color2, int w2, int h2, int x2, int y2, char *bmap2);
	int (*fn_my_expose)( int nexpose, struct Ph_rect *expose_list );
	void (*fn_my_setpixel)( int x, int y, unsigned long color );
	// unsigned long spare_funs[23];
	int (*fn_my_raw_cmd)( unsigned long function, 
							int cmdspec, 
							unsigned long cmdsize, 
							unsigned long *cmd_ptr,
							GR_DriverStateStruct *DSPtr );
	int (*fn_my_draw_thickline)( struct Ph_point p1, 
							struct Ph_point p2, 
							int draw_options,
							GR_DriverStateStruct *DSPtr );
	int (*fn_my_draw_grid)( );
	int (*fn_my_draw_trend)( );
	int (*fn_my_draw_vector)( );
	int (*fn_my_draw_polygon)( unsigned long mode,
								struct Ph_point *p_array,
								int num_points,
								struct Ph_point offset,
								int draw_options,
								struct Ph_point (*PointTransform)(struct Ph_point),
								GR_DriverStateStruct *DSPtr );
								
	int (*fn_my_draw_rect)( );
	int (*fn_my_draw_rounded_rect)( );
	int (*fn_my_draw_ellipse)( struct Ph_rect R,
								struct Ph_point p,
								int draw_options,
								struct Ph_point (*PointTransform)(struct Ph_point),
								GR_DriverStateStruct *DSPtr );
	int (*fn_my_draw_arc)(struct Ph_point p,
							struct Ph_point radii,
							unsigned long start_angle,
							unsigned long end_angle,
							int mode,
							int draw_options,
							struct Ph_point (*PointScale)(struct Ph_point),
							struct Ph_point (*PointTransform)(struct Ph_point),
							GR_DriverStateStruct *DSPtr );
	int (*fn_my_draw_span)( );
	int (*fn_my_draw_bezier)(unsigned long mode,
								struct Ph_point *p_array,
								int num_points,
								struct Ph_point offset,
								int draw_options,
								struct Ph_point (*PointTransform)(struct Ph_point),
								GR_DriverStateStruct *DSPtr );
	int (*fn_my_draw_bevel)(unsigned long mode,
								struct Ph_rect box,
								struct Ph_point radii,
								int draw_options,
								struct Ph_rect (*RectTransform)(struct Ph_rect),
								struct Ph_point (*PointScaleRel)(struct Ph_point),
								GR_DriverStateStruct *DSPtr );
	unsigned long spare_funs[9];
	struct GR_draw_functions *df;
	} ;

#ifndef NO_RENDER_PROTO
#include <photon/PhT.h>

struct _doc_ctrl *PhRenderOpen( struct _doc_ctrl *c, PhImage_t *img,
		PhPoint_t *pos, PhDim_t *dim );
int PhRender( struct _doc_ctrl *c, void *buf, int len, int nclip, PhRect_t *cliplist );
int PhRenderClear( struct _doc_ctrl *c, unsigned long color );
int PhRenderGetImage( struct _doc_ctrl *c, PhImage_t *img );
int PhRenderClose( struct _doc_ctrl *c );
#endif

#ifdef __cplusplus
};
#endif

#endif
