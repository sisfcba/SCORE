#ifndef __PF_H_INCLUDED
#define __PF_H_INCLUDED

#include <stdlib.h>
#include <photon/PhT.h>
#include <limits.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PHFONT_ENVVAR			"PHFONT"
#define PHFONT_FDNAME			"/dev/phfont"
#define PHFONT_MEM_ENVVAR		"PHFONTMEM"
#define PHFONT_MEM_ROUND(sz)	(((sz) + 3) & ~3)

#define PHFONT_LOAD_METRICS	0x01
#define PHFONT_LOAD_IMAGES	0x02

#define PHFONT_INFO_PLAIN	0x01
#define PHFONT_INFO_BOLD	0x02
#define PHFONT_INFO_ITALIC	0x04
#define PHFONT_INFO_BLDITC	0x08
#define PHFONT_INFO_FIXED	0x10
#define PHFONT_INFO_PROP	0x20

#define PHFONT_SCALABLE		0x01
#define PHFONT_BITMAP		0x02
#define PHFONT_PROP			0x10
#define PHFONT_FIXED		0x20
#define PHFONT_ALL_FONTS	0x33
#define PHFONT_ALL_SYMBOLS	(-1L)

#if defined(__QNXNTO__)

#define MAX_FONT_TAG 80

typedef char FontName[MAX_FONT_TAG];
typedef char FontFilename[NAME_MAX + 16];

#else

#define MAX_FONT_TAG 16

typedef char FontName[MAX_FONT_TAG];
typedef char FontFilename[20];

#endif

typedef char FontDescription[32];

typedef struct {
#if defined(__QNXNTO__)
    short         	losize;
    short         	hisize;
    unsigned short  flags;
    unsigned short  unSpare[1];
    unsigned int    ulSpare[2];
    FontDescription desc;
    FontName        stem;
#else
    FontDescription desc;
    FontName        stem;
    short         	losize;
    short         	hisize;
    unsigned short  flags;
#endif
} FontDetails;

typedef struct {
#if defined(__QNXNTO__)
    short         	size;
    unsigned short  style;
    short         	ascender;
    short         	descender;
    short         	width;
    unsigned short  nSpare[1];
    int         	lochar;
    int         	hichar;
    unsigned int    ulSpare[2];
    FontName        font;
    FontDescription desc;
#else
    FontName        font;
    FontDescription desc;
    short         	size;
    unsigned short  style;
    short         	ascender;
    short         	descender;
    short         	width;
    int         	lochar;
    int         	hichar;
#endif
} FontQueryInfo;

typedef struct {
	PhPoint_t		size;
	PhPoint_t		offset;
	int				width;
	short			bpl;
	short			bpp;
#if defined(__QNXNTO__)
    unsigned int    ulSpare[2];
#endif
	unsigned char	*bmptr;
} FontRender;

typedef struct {
	short		width;
	short		size;
	short		leftbearing;
} FontWidths;  // deprecated

typedef struct {
	long		width;
	long		size;
	long		leftbearing;
} FontWidthsLong;  // Can't add spare, because it will break.

typedef struct FontLocalMetrics {
#if defined(__QNXNTO__)
    int                 	hash;
    int                 	start;
    int                 	end;
    unsigned int           	ulSpare[3];
    PhRect_t                extent;
    FontName                font;
    struct FontLocalMetrics *link;
    FontWidthsLong          widths[1];
#else
    struct FontLocalMetrics *link;
    int                 	hash;
    FontName                font;
    PhRect_t                extent;
    int                 	start;
    int                 	end;
    FontWidthsLong          widths[1];
#endif
} FontLocalMetrics;

typedef struct FONT_STAT
{  unsigned long ulCacheHits;
   unsigned long ulTotalAttempts;
   unsigned long ulSpare[4];
} FontStatReply;

typedef struct FONT_DYNAMIC_REPLY
{  long lID;
   unsigned long ulSpare[3];
} FontDynamicLoadReply;

typedef struct FONT_DYNAMIC
{  unsigned long ulFileNameLength;
   unsigned long ulSpare[3]; 
} FontDynamicLoad;

typedef struct FONT_DYNAMIC_UNLOAD
{  long lID;
   unsigned long ulSpare[3];
} FontDynamicUnload;

struct _Pf_ctrl {
#if defined(__QNXNTO__)
    int             	server;
    int             	size;
    unsigned int        ulSpare[4];
    unsigned char       *shmem;
    FontLocalMetrics    *local;
#else
    int             	server;
    unsigned char       *shmem;
    int             	size;
    FontLocalMetrics    *local;
#endif
};

extern struct _Pf_ctrl	*PfAttach(const char *device, long size);
extern void		PfDetach(struct _Pf_ctrl *pf);
extern int		PfLoadFont(const char *font, unsigned flags, FontName fontused);
extern int		PfQueryFont(const char *font, FontQueryInfo *info);
extern int		PfQueryFonts(long symbol, unsigned flags, FontDetails list[], int n);
extern PhRect_t	*	PfExtentText(PhRect_t *extent, PhPoint_t const *pos, const char *font, const char *str, int len);
extern PhRect_t	*	PfExtentWideText(PhRect_t *extent, PhPoint_t const *pos, const char *font, const wchar_t *str, int len);
extern PhRect_t	*	PfExtentComponents(PhRect_t *extent, PhPoint_t const *pos, const char *font, const char *str, int len, void (*func)(PhRect_t *, const char *, const char *, int));
extern PhRect_t	*	PfFractionalExtentText(PhRect_t *extent, PhPoint_t const *pos, const char *font, long xsize, long ysize, const char *str, int len);
extern int		PfRenderText(const char *font, const char *str, int len, PhPoint_t const *pos, PhRect_t const *clip, void (*func)(const PhPoint_t *, const FontRender *));
extern int		PfRenderWideText(const char *font, const wchar_t *str, int len, PhPoint_t const *pos, PhRect_t const *clip, void (*func)(const PhPoint_t *, const FontRender *));
extern int		PfFractionalRenderText(const char *font, long xsize, long ysize, const char *str, int len, PhPoint_t const *pos, PhRect_t const *clip, void (*func)(const PhPoint_t *, const FontRender *));
extern int		PfGlyph(const char *font, long symbol, FontRender *metrics, unsigned char *bitmap, int size, FontName fontused);
extern int		PfLoadMetrics(const char *font);
extern int		PfUnloadMetrics(const char *font);
extern int		PfTextWidth(const char *font, const char *str, int len);
extern int		PfTextWidthBytes(const char *font, const char *str, int len);
extern int		PfTextWidthChars(const char *font, const char *str, int len);
extern int		PfWideTextWidth(const char *font, const wchar_t *str, int len);
extern int		PfWideTextWidthBytes(const char *font, const wchar_t *str, int len);
extern int		PfWideTextWidthChars(const char *font, const wchar_t *str, int len);
extern long		PfDynamicLoad(char const * pkcFontFile);
extern long		PfDynamicUnload(long lDynamicFontID);

#define PHF_STATS 0x01
#define PFR_STATS 0x02
#define TTF_STATS 0x03

extern int		PfGetCacheStats(unsigned long * pulCacheHits, unsigned long * pulTotalAttempts, unsigned long ulFlags);

#define PfTextWidth(font, str, len) PfTextWidthChars(font, str, len)
#define PfWideTextWidth(font, str, len) PfWideTextWidthChars(font, str, len)

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
