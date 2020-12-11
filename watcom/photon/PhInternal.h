/*
 * PhInternal.h	
 *
 *		Photon library control structure
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PHCTRL_H_INCLUDED
#define __PHCTRL_H_INCLUDED

#ifndef _LIMITS_H_INCLUDED
 #include <limits.h>
#endif

//#ifndef __MOUSE_H_INCLUDED
// #include <sys/mouse.h>
//#endif

#ifndef __PH_GLIB_H_INCLUDED
#include <photon/Pg.h>
#endif

#include <photon/Pf.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __PH_GLIB_H_INCLUDED
/* Simple font metrics */
/* This is also defined in Pg.h ??? */
struct _Ph_font_widths {
	char			face[20];
	PhRect_t		extent;
	ushort_t		valid;
	ushort_t		ascii_offset;
	ushort_t		ascii_length;
	char			widths[256];
};
#endif

struct Ph_soul_entry {
	void					*next;
	unsigned short			 total;		// Total allocated (free or in use).
	unsigned short			 num_souls;	// Number in this list.
	unsigned short			 size;		// Size of object in the list.
	unsigned short			 inc;		// Alloc more by this increment.
	unsigned short			 min;		// total >= min
	unsigned short			 max;		// total <= max
	unsigned short			 largest;	// Largest number in use
	ushort_t				 reserved;
};

typedef struct Ph_soul_entry			PhSoul_t;
typedef struct Ph_vector_entry			PhVector_t;

typedef struct _Ph_Draw_Context PhDrawContext_t;
struct _Ph_Draw_Context
    {
    	int		(*flush)( int subtype );
    	int		(*modify)( PhDrawContext_t *dc, int acquire, void *data );
    	int 	type;
		long    flags;
		int		cur_cmd_len;
		PhGC_t	*gc, *buf_gc;
		struct _Ph_g_info gin;
    };

typedef struct VidMemDC 
{
	PhDrawContext_t		dc;			//Draw Context
	PgVidMem_t			vidmem;		//Description of memory
} PgVidMemDC_t;

// Draw context flags
#define Ph_INLINE_SHMEM_OBJECTS	0x00000001
#define Ph_TEXT_EXTENTS			0x00000002
#define Ph_SUPRESS_PARENT_CLIP	0x00000004
#define Ph_SYNC_GCS				0x00000008 // swaps gc-> bug_gc of activating gc.

// modify acquire values.
#define Ph_QUERY_DC_GRAFX_INFO	0x80000000

// Draw target manifests for PhCreateDC ( Draw context TYPEs )
#define Ph_DRAW_TO_PHOTON			0
#define Ph_DRAW_TO_PRINT_CONTEXT	1
#define Ph_DRAW_TO_MEMORY_CONTEXT	2
// Not yet supported
#define Ph_DRAW_TO_SERVICE			3

/* The channel control structure */
struct _Ph_ctrl {
	int							fd;
	#if defined(__QNXNTO__)
		int						channel;
		int						connection;
		int						pulse_code;
		int						pulse_value;
	#else
		pid_t					proxy;
		pid_t					vproxy;
	#endif
	long						id;
#if !defined( __QNXNTO__ )
	struct _Ph_g_info			gin_n_tonic;
#endif
	PhTile_t					temp_tile;
	PhGC_t						*grc, *dflt_gc, *buf_grc;
	PhSoul_t					tile_souls;
	char						*device;
	struct _Pf_ctrl				*font;
	PhDrawContext_t				*draw_context;
	PhDrawContext_t				*dflt_draw_context;
	void						*data;
};
// manifests for use in draw context modify functions
// modify state
#define Ph_ACTIVATE_DC		0
#define Ph_DEACTIVATE_DC	1
#define Ph_DESTROYING_DC	2
// Context specific >1

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
