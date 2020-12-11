/*
 * PxProto.h	
 *		Prototypes for the Photon Extended (Px) library
 *
 *  Copyright by QNX Software Systems Limited 1990-1995. All rights reserved.
 */

#ifdef __WATCOMC__
#if __WATCOMC__ < 1000
#define __NO_MBSTRING_H__
#endif
#endif

#include <stdlib.h>

#include <photon/PtT.h>

#ifdef __cplusplus
extern "C" {
#endif

#if 0
extern int PxLoadBMP ( char *filename, PhImage_t *image);
extern int PxLoadGIF ( char *filename, PhImage_t *image);
extern int PxLoadJPEG( char *filename, PhImage_t *image);
extern int PxLoadPCX ( char *filename, PhImage_t *image);
#endif

#define PXCONFIG_READ	0x0
#define PXCONFIG_WRITE	0x1
#define PXCONFIG_CREATE	0x4
#define PXCONFIG_FMT_BOOL_ON		1
#define PXCONFIG_FMT_BOOL_YES		2
#define PXCONFIG_FMT_BOOL_TRUE		3
#define PXCONFIG_FMT_CHAR_CHAR		11
#define PXCONFIG_FMT_CHAR_HEX		12
#define PXCONFIG_FMT_INT_DECIMAL	21
#define PXCONFIG_FMT_INT_HEX		22
#define PXCONFIG_FMT_STRING			31

extern int			PxConfigOpen(const char *cfgfile, int mode);
extern int			PxConfigClose(void);
extern int			PxConfigSection(const char *section);
extern const char	*PxConfigNextSection(void);
extern const char	*PxConfigNextString(char *value, short maxlen);
extern int			PxConfigReadBool(const char *section, const char *entry, int dflt, int *value);
extern int			PxConfigReadChar(const char *section, const char *entry, char dflt, char *value);
extern int			PxConfigReadShort(const char *section, const char *entry, short dflt, short *value);
extern int			PxConfigReadInt(const char *section, const char *entry, int dflt, int *value);
extern int			PxConfigReadLong(const char *section, const char *entry, long dflt, long *value);
extern int			PxConfigReadString(const char *section, const char *entry, char *dflt, char *value, short maxlen);
extern int			PxConfigWriteBool(const char *section, const char *entry, int format, int value);
extern int			PxConfigWriteChar(const char *section, const char *entry, int format, char value);
extern int			PxConfigWriteShort(const char *section, const char *entry, int format, short value);
extern int			PxConfigWriteInt(const char *section, const char *entry, int format, int value);
extern int			PxConfigWriteLong(const char *section, const char *entry, int format, long value);
extern int			PxConfigWriteString(const char *section, const char *entry, int format, const char *value);
extern int			PxConfigForceEmptySection(const char *section);
extern int			PxConfigDeleteSection(const char *section);
extern int			PxConfigDeleteEntry(const char *section, const char *entry);

struct PxTransCtrl;
extern struct PxTransCtrl	*PxTranslateSet(struct PxTransCtrl *ctrl, const char *charset);
extern struct PxTransCtrl	*PxTranslateSetInternal(struct PxTransCtrl *ctrl, const char *charset, const char *type, const void *data, int size);
extern int					PxTranslateUnknown(struct PxTransCtrl *ctrl, wchar_t to, wchar_t from);
extern int					PxTranslateListAlloc(char ***items);
extern void					PxTranslateListFree(char **items, int num);
extern int					PxTranslateList(PtWidget_t *widget, char const *none);
extern int					PxTranslateToUTF(struct PxTransCtrl *ctrl, const char *src, int maxsrc, int *srctaken, char *dst, int maxdst, int *dstmade);
extern int					PxTranslateFromUTF(struct PxTransCtrl *ctrl, const char *src, int maxsrc, int *srctaken, char *dst, int maxdst, int *dstmade);
extern int PxTranslateStateToUTF(struct PxTransCtrl *ctrl, const char *src, int maxsrc, int *consumed, char *dst, int maxdst);
extern int	PxTranslateStateFromUTF(struct PxTransCtrl *ctrl, const char *src, int maxsrc, int *consumed, char *dst, int maxdst);

long PxCRC( const char *buffer, int nbytes );

#ifdef __cplusplus
};
#endif
