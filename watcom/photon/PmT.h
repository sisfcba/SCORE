
/*
 * PmT.h	
 *
 *		Photon Memory context structures
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */

#ifndef __PMCTRL_H_INCLUDED
#define __PMCTRL_H_INCLUDED
#include <photon/PhInternal.h>
#ifndef _LIMITS_H_INCLUDED
#include <limits.h>
#endif
#ifndef __PH_GLIB_H_INCLUDED
#include <photon/Pg.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PmMemCreateMC( a, b, c ) __PmCreateMC( a, b, c, PhRenderOpen, PhRender, PhRenderClear, PhRenderGetImage, PhRenderClose )

struct _doc_ctrl;

typedef struct memory_context PmMemoryContext_t;
struct memory_context 
	{
	PhDrawContext_t		dc;		// low level control... see PhDraw.c and PhInternal.h
	char				type; // Pm_PHS_CONTEXT, Pm_IMAGE_CONTEXT
	#ifdef __QNXNTO__
		char			spare1[3];
	#endif
	struct _doc_ctrl 	*ctrl;
	
	PhImage_t		*image;			// The context image 
	PhImage_t		*delta_image;	// The image describing the area of the whole
						// modified by processing the last draw stream
						// ... used for querying portions of a PHS memimage.
	PhPoint_t		origin; // like PpPrintContext_t source offset, used to translate the draw stream
	PhDim_t			dim;	// the dimension of the memory context... not explicitly required for PHS.
	
	int 				(*render_f)( struct _doc_ctrl *c, void *buf, int len, int nclips, PhRect_t *clip_list  );
	int 				(*open_f)( struct _doc_ctrl *c, PhImage_t *image, PhPoint_t *trans, PhDim_t *dim );
	int 				(*close_f)( struct _doc_ctrl *c );
	int				(*clear_f)( struct _doc_ctrl *c, unsigned long color );
	int				(*getimage_f)( struct _doc_ctrl *c, PhImage_t *img );
	ulong_t			changed;	// tbd ... although this is what cur_gc and buf_gc are for.
	int				phs_buf_chunk_size;
	int				phs_buf_max_size;
	char			dithering;
	#ifdef __QNXNTO__
		char		spare2[3];
	#endif
	long			flags;
	int				(*flush_verify)( PmMemoryContext_t *mc, int flush_subtype );
	PhGrafxInfo_t	graphics_info;
	void			*data;
	};

#define Pm_PHS_CONTEXT 		0
#define Pm_IMAGE_CONTEXT 	1

// memory context flags
#define Pm_CONTEXT_FLUSHED	0x00000001

// modify type extention....
#define Ph_QUERY_MEMORY_GRAFX_INFO	0x80000000

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
