#ifdef __cplusplus
extern "C" {
#endif

#ifndef _PXIMAGE_H_INCLUDED
#define _PXIMAGE_H_INCLUDED

#include <Ph.h>
#include <stdio.h>

/* Macro to calculate 16.16 percentage a of b */

#define PX_PERCENTAGE(a,b) \
	(((((a) * 100) / (b)) << 16) | (((((a) * 100) % (b)) << 16) / (b)))


/* PxImageFunct_t format definitions */
#define PX_IMAGE_BMP		0x00
#define PX_IMAGE_GIF		0x01
#define PX_IMAGE_JPG		0x02
#define PX_IMAGE_PCX		0x03
#define PX_IMAGE_TGA		0x04
#define PX_IMAGE_PNG 		0x05
#define PX_IMAGE_TIFF		0x06
#define PX_IMAGE_XBM		0x07

typedef struct pximagefunc
{
	int			(*load)( PhImage_t *image );
	int			(*write)( PhImage_t *image, int image_type );
	int			(*query)( PhImage_t *image );
	int			format;
	char		*extension;
} PxImageFunc_t;

/* PxMethods_t flag definitions */
#define PX_LOAD				0x00
#define PX_QUERY			0x01
#define PX_SUPPRESS_CRC		0x02
#define PX_SUPPRESS_TAG		0x02
#define PX_DIRECT_COLOR		0x04
#define PX_TRANSPARENT		0x08
//#define PX_SCALE			0x10
#define PX_USECOLORS		0x20
#define PX_DODITHER			0x40

/* px_alloc( ) type definitions */
#define PX_NORMAL			0x00
#define PX_IMAGE			0x01
#define PX_PALETTE			0x02
#define PX_METHODS			0x80000000

typedef struct pxmethods
{
	int			flags;
	void		*(*px_alloc)( long nbytes, int type );
	void		*(*px_free)( void *memory, int type );
	void		*(*px_error)( char *msg );
	void		*(*px_warning)( char *msg );
	void		*(*px_progress)( int );
	PhDim_t		scale;
	PgColor_t	transparent;
	void		*colors;
	int			ncolors;
} PxMethods_t;

extern FILE			*PxFp;
extern PhImage_t	*PxImage;

extern int PxLoadBMP( PhImage_t * );
extern int PxWriteBMP( PhImage_t *, int );
extern int PxQueryBMP( PhImage_t * );
extern int PxLoadGIF( PhImage_t * );
extern int PxWriteGIF( PhImage_t *, int );
extern int PxQueryGIF( PhImage_t * );
extern int PxLoadJPG( PhImage_t * );
extern int PxQueryJPG( PhImage_t * );
extern int PxLoadPCX( PhImage_t * );
extern int PxWritePCX( PhImage_t *, int );
extern int PxQueryPCX( PhImage_t * );
extern int PxLoadTGA( PhImage_t * );
extern int PxQueryTGA( PhImage_t * );
extern int PxLoadPNG( PhImage_t * );
extern int PxWritePNG( PhImage_t *, int );
extern int PxQueryPNG( PhImage_t * );
extern int PxLoadTIFF( PhImage_t * );
extern int PxQueryTIFF( PhImage_t * );
extern int PxLoadXBM( PhImage_t * );
extern int PxQueryXBM( PhImage_t * );
extern int PxWriteXBM( PhImage_t *, int );

void PxProgress( int percent );
void PxTerminate( PhImage_t *image );
void * PxAlloc( long nbytes, int type );
void PxWarning( char *msg );
void PxError( PhImage_t *image, char *msg );
void PxFree( void *memory, int type );
PhImage_t * PxLoadImage( char *filename, PxMethods_t *methods );
int PxWriteImage( char *filename, PhImage_t *image, PxMethods_t *methods, int iformat, int itype );
long PxCRC( const char *buffer, int nbytes );

#endif


#ifdef PX_IMAGE_MODULES

#ifdef __cplusplus
extern
#endif

PxImageFunc_t	PxImageFunc[ ] = {

#ifdef PX_GIF_SUPPORT
{PxLoadGIF, PxWriteGIF, PxQueryGIF, PX_IMAGE_GIF, "gif"},
#endif
#ifdef PX_PCX_SUPPORT
{PxLoadPCX, PxWritePCX, PxQueryPCX, PX_IMAGE_PCX, "pcx"},
#endif
#ifdef PX_JPG_SUPPORT
{PxLoadJPG, NULL, PxQueryJPG, PX_IMAGE_JPG, "jpg"},
#endif
#ifdef PX_BMP_SUPPORT
{PxLoadBMP, PxWriteBMP, PxQueryBMP, PX_IMAGE_BMP, "bmp"},
#endif
#ifdef PX_TGA_SUPPORT
{PxLoadTGA, NULL, PxQueryTGA, PX_IMAGE_TGA, "tga"},
#endif
#ifdef PX_PNG_SUPPORT
{PxLoadPNG, PxWritePNG, PxQueryPNG, PX_IMAGE_PNG, "png"},
#endif
#ifdef PX_TIFF_SUPPORT
{PxLoadTIFF, NULL, PxQueryTIFF, PX_IMAGE_TIFF, "tif"},
#endif
#ifdef PX_XBM_SUPPORT
{PxLoadXBM, PxWriteXBM, PxQueryXBM, PX_IMAGE_XBM, "xbm"},
#endif

{NULL, NULL, NULL, 0, NULL} };
#endif

#ifdef __cplusplus
}
#endif
