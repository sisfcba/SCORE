#ifndef __PFMSG_H_INCLUDED
#define __PFMSG_H_INCLUDED

#include <sys/types.h>
#include <photon/PhMsg.h>
#include "Pf.h"

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif


#define PHFONT_MSG_NEWFONTS					1	/* Reload 'fontdir' and 'fontext' files */
#define PHFONT_MSG_LOAD						2	// Load metrics/image data for a font
#define PHFONT_MSG_LIST						3	// List suitable fonts
#define PHFONT_MSG_QUERY					4	// Query attributes of a font
#define PHFONT_MSG_EXTENT					5	// Calculate extent of a string
#define PHFONT_MSG_CEXTENT1					6	// Calculate multi-part extent of a string
#define PHFONT_MSG_RENDER					7	// Render bitmap of a string
#define PHFONT_MSG_SHMEM					8	// Create shmem for bitmap transfer
#define PHFONT_MSG_GLYPH					9	// Return character metrics and bitmap
#define PHFONT_MSG_LOCAL1					10	// Return character metrics pre-info
#define PHFONT_MSG_LOCAL2					11	// Return character metrics info
#define PHFONT_MSG_ANTIALIAS				12	// Set global antialias mode
#define PHFONT_MSG_RENDER2					13	// Continuation of string bitmap render
#define PHFONT_MSG_CEXTENT2					14	// Continuation of multi-part extent
#define PHFONT_MSG_WEXTENT					15	// Calculate extent of widechar string
#define PHFONT_MSG_WRENDER					16	// Render bitmap of a widechar string
#define PHFONT_MSG_WRENDER2					17	// Continuation of wide string bitmap render
#define PHFONT_MSG_FEXTENT					18	// Calculate extent of a string (fract)
#define PHFONT_MSG_FRENDER					19	// Render bitmap of a string (fract)
#define PHFONT_MSG_FRENDER2					20	// Continuation of string bitmap render (fract)
#define PHFONT_MSG_FRENDER_WIDE				25	// Render fractional wide characters.
#define PHFONT_MSG_FEXTENT_WIDE 			26	// Extent fractional wide characters.
#define PHFONT_MSG_FRENDER_WIDE2			27	// Render fractional wide characters (Continuation).
#define PHFONT_MSG_STAT_PHF					28	// Get cache stats for PHF fonts.
#define PHFONT_MSG_STAT_PFR					29	// Get cache stats for PFR fonts.
#define PHFONT_MSG_STAT_TTF					30	// Get cache stats for TTF fonts.
#define PHFONT_MSG_LOCAL2_V20               31  // Return character metrics info (v2.0)

#define	PHFONT_MSG_DYNAMIC_LOAD				0x1000 // Dynamically install a font file.
#define PHFONT_MSG_DYNAMIC_UNLOAD			0x1001 // Dynamically uninstall a font file.

typedef struct {
	msg_t		type;				// Always _PHFONT_REQUEST
	msg_t		subtype;			// One of PHFONT_MSG_*
	short int	fd;
	short int	strlen;
	union {							// OK, so I screwed up ... :-(
		struct {
			FontName	font;
			short int	n;
			long		symbol;
		} a;
		struct {
			char		font[sizeof(FontName) - sizeof(short int)];
			long		xscale, yscale;
		} b;
	} data;
	union {
		PhRect_t	extent;
		FontRender	render;
	} size;
} PfServerMessage;

#define PHFONT_MAX_XFER_SZ (4096 - sizeof(PfServerMessage))
#define PHFONT_MAX_STRLEN  (PHFONT_MAX_XFER_SZ / sizeof(char))
#define PHFONT_MAX_WIDTHS  (PHFONT_MAX_XFER_SZ / sizeof(FontWidths))
#define PHFONT_MAX_WIDTHS_LONG ((PHFONT_MAX_WIDTHS / 2) - 1)

typedef struct {
    FontWidthsLong 	widths[PHFONT_MAX_WIDTHS_LONG];
    long        	lType;
} FontLocalWidths;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
