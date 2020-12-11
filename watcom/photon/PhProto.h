/*
 * PhProto.h	
 *		Prototypes for the Photon Ph and Pg libraries
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#include <sys/types.h>
#include <photon/PhInternal.h>
#include <photon/PhT.h>
#include <photon/PmT.h>
#include <photon/PpT.h>
#include <photon/PhWm.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern	void	 	PhFreeTiles( PhTile_t *tiles );
extern	PhTile_t * 	PhAddMergeTiles( PhTile_t *tiles, PhTile_t *add_tiles, int *added );
extern	PhTile_t *	PhCoalesceTiles( PhTile_t *tiles );
extern	PhTile_t *	PhCopyTiles( PhTile_t const * const tile );
extern	PhTile_t *	PhDeTranslateTiles( PhTile_t *tile, PhPoint_t const *point_subtract );
extern	PhTile_t * 	PhMergeTiles( PhTile_t *tiles );
extern	PhTile_t *	PhRectsToTiles( PhRect_t *rects, int num_rects );
extern	PhTile_t * 	PhSortTiles( PhTile_t *tiles );
extern	PhRect_t *	PhTilesToRects( PhTile_t *tiles, int *num_rects );
extern	PhTile_t *	PhTranslateTiles( PhTile_t *tile, PhPoint_t const *point_add );


/*
 *	1998/10/15
 */

extern int PhNotify (const struct sigevent *notification);
extern	int _PhTestDrawCmd( int size );
extern	struct _Ph_ctrl *__free_Ph_( struct _Ph_ctrl *Ph );
extern	struct _Ph_g_info * PmMemGetGin( PmMemoryContext_t *mc );
extern	int PmMemGetType( PmMemoryContext_t *mc );
extern	int PmMemGetMaxBufSize( PmMemoryContext_t *mc );
extern	void PmMemSetMaxBufSize( PmMemoryContext_t *mc, int size );
extern	int PmMemGetChunkSize( PmMemoryContext_t *mc );
extern	void PmMemSetChunkSize( PmMemoryContext_t *mc, int size );
extern void PmMemSetType( PmMemoryContext_t *mc, int type );
extern void PgDefaultText( PhGC_t *GC );
extern void PgBackgroundShadings( PgColor_t bg, PgColor_t *ts, PgColor_t *bs );
extern int PhDCGetType( PhDrawContext_t *dc );
extern struct _Ph_g_info * PhDCGetGin( PhDrawContext_t *dc );

/*
Wed July 02 16:49:51 EDT 1997
*/

extern PmMemoryContext_t * __PmCreateMC( PhImage_t *image, PhDim_t *dim, PhPoint_t *pos,
	struct _doc_ctrl *(*mc_open)( struct _doc_ctrl *c, PhImage_t *img, PhPoint_t *pos, PhDim_t *dim ),
	int (*mc_render)( struct _doc_ctrl *c, void *buf, int len, int nclips, PhRect_t *clip_list  ), 
	int (*mc_clear)( struct _doc_ctrl *c, unsigned long color ), 
	int (*mc_getimage)( struct _doc_ctrl *c, PhImage_t *img ), 
	int (*mc_close)( struct _doc_ctrl *c ) 
	);
extern void PmMemReleaseMC( PmMemoryContext_t *mc );
extern int PmMemFlush( PmMemoryContext_t *mc, PhImage_t *image );
extern PhDrawContext_t * PmMemStart( PmMemoryContext_t *mc );
extern PhDrawContext_t * PmMemStop( PmMemoryContext_t *mc );

/*
Mon Jun 02 16:49:51 EDT 1997
*/

extern void PhReleaseImage(PhImage_t *image);
extern int PhMakeGhostBitmap(PhImage_t *image);
extern int PhMakeTransBitmap(PhImage_t *image, PgColor_t trans_color);
extern int PhDCInit( void *DC, int type, long flags, int (*flush)(int Subtype), int (*modify)(PhDrawContext_t *dc, int acquire, void *data )  );
extern int PpLoadPrinter( PpPrintContext_t *pc, char const *printer_name );
extern PpPrintContext_t * PpPrintAllocatePC( void );
extern PhDrawContext_t * PhDCGetCurrent( void );

/* 
Mon Apr 14 08:48:13 EDT 1997
*/

/* Misc printing support */
extern int PpPrintLookupConfig(const char *config);
extern const char *PpPrintLookupMember(int member);

/*
 * Printer draw stream support
 */
extern int _PhDCSetFlags( void *dc, int bits, int mask );
extern int PhTestDrawCmd( int size );
extern int PpPrintSetPC( PpPrintContext_t *pc, int level, int lock, int member, void const * const data );
extern void *PpPrintGetPC( PpPrintContext_t *pc, int member, const void ** const data );
extern void _PpSetSourceOffset( ushort_t x, ushort_t y );
extern void _PpSetJobName( char const *job );
extern void _PpSetSubmissionDate( char const *date );
extern void _PpSetNonPrintMargins( ushort_t left, ushort_t right, ushort_t top, ushort_t bottom );
extern void _PpSetPrinterName( char const *printer );
extern void _PpSetUserID( char const *user );
extern void _PpSetPrinterLocation( char const *user );
extern void _PpSetPrinterFilter( char const *filter_app );
extern void _PpAbort( void );
extern int PhTestDrawBuffer( int size );
extern PhDrawContext_t *PhDCSetCurrent( void *DC );
extern PhDrawContext_t *PhDCCreate( int type, long flags, int (*flush)(int Subtype), int (*modify)(PhDrawContext_t *dc, int acquire, void *data )  );
extern int PhDCRelease( void *DC );
extern int PhTargetStream( PhDrawContext_t *dc, int acquire, void *data );
extern int	PpPrintNewPage( PpPrintContext_t *PC );
extern PhDrawContext_t *PpPrintTarget( PhDrawContext_t *dc, int acquire, void *data );
extern PpPrintContext_t *PpPrintCreatePC( void );
extern void PpPrintReleasePC( PpPrintContext_t *pc );
extern PhDrawContext_t *PpPrintStart( PpPrintContext_t *PC );
extern int PpPrintOpen( PpPrintContext_t *pc );
extern void PpPrintStop( PpPrintContext_t *PC );
extern int PpPrintClose( PpPrintContext_t *pc );
extern int PpPrintFFlush( unsigned int SubType );
extern int PgGraphicFFlush( unsigned int Subtype );
extern PhDrawContext_t *PhTargetDrawStream( PhDrawContext_t *dc );
extern void _PpSetSourceResolution( ushort_t xdpi, ushort_t ydpi );
extern void _PpSetSourceSize( ushort_t w, ushort_t h  );
extern void _PpSetPrinterResolution( ushort_t xdpi, ushort_t ydpi );
extern void _PpSetPaperSize( ushort_t w, ushort_t h );
extern void _PpSetBorder( ushort_t left, ushort_t right, ushort_t top, ushort_t bottom );
extern void _PpSetMargins( ushort_t left, ushort_t right, ushort_t top, ushort_t bottom );
extern void _PpSetOrientation( ushort_t nw );
extern void _PpSetColorMode( ulong_t color_mode );
extern void _PpSetSourceColors( ulong_t colors );
extern void _PpSetNumCopies( ulong_t num );
extern void _PpSetPageRange( ushort_t from, ushort_t to );
extern void _PpSetScale( ushort_t w, ushort_t h );
extern void _PpSetPaperSource( ulong_t c );
extern void _PpSetPaperType( ulong_t type );
extern void _PpSetCollatingMode( ulong_t mode );
extern void _PpSetDuplexPrinting( ulong_t type );
extern void _PpSetDithering( ulong_t type );
extern void _PpSetIntensity( ulong_t val );
extern void _PpSetInkType( ulong_t type );
extern void _PpSetInkType( ulong_t type );
extern void _PpSetClipRect( short left, short right, short top, short bottom );

/*
extern int PgDrawMultiBitmap(void *,int ,PhPoint_t *,PhPoint_t *,int ,long,PhPoint_t *,int );
extern int PgDrawMultiImage(void *,int ,PhPoint_t *,PhPoint_t *,int ,long,PhPoint_t *,int );
*/

extern  char *mbstrirchr( char const *string_base, char const *start_char, char const *mbchar, int *count );
extern	char *mbstrrchr( char const *string_base, char const *start_char, char const *mbchar, int *count );
extern	char *mbstrichr( char const *string, char const *mbchar, int *count );
extern	char *mbstrnichr( char const *string, char const *mbchar, int num, int *count );
extern	char *mbstrchr( char const *string, char const *mbchar, int *count );
extern	char *mbstrnchr( char const *string, char const *mbchar, int num, int *count );
extern 	int mbstrlen( char const *text, int char_width, int *bytes );
extern	int mbstrnlen( char const *text, int max_len, int char_width, int *num );
extern	int mbstrblen( char const *text, int max_bytes, int char_width, int *bytes );
extern	int mbstrncmp( char const *text, char const *text2, int len, int char_width );
extern	wchar_t wctolower( wchar_t );
void PgDrawRoundBorder( PhRect_t const *rect, PgColor_t top_color, PgColor_t bot_color, ushort_t roundness, int dflags ); 
void PgDrawClipBorder( PhRect_t const *rect, PgColor_t top_color, PgColor_t bot_color, ushort_t roundness, int dflags ); 

/*
 *	June. 96 --^
 */

extern PhRect_t *PgExtentTextChars( PhRect_t *extent, PhPoint_t const *pos, char const *font, char const *str, unsigned int num_characters);
extern PhRect_t *PgExtentTextBytes( PhRect_t *extent, PhPoint_t const *pos, char const *font, char const *str, unsigned int num_bytes);

extern void PhMoveCursorRel( int input_group, int x, int y );
extern void PhMoveCursorAbs( int input_group, int x, int y );

/*
 *	May. 96 --^
 */

extern int PgShmemAttach( char const *, unsigned long , void *);
extern int PgShmemDetach( void *);
extern void *PgShmemCreate( unsigned long , char const *);
extern int PgShmemDestroy( void *);
extern void PgShmemCleanup();
extern int PgShmemCtrl( void *Addr, int State );
/*
 *	Apr. 96 --^
 */

void PhObjectFree( PhSoul_t *, void *);
void *PhObjectGrow( PhSoul_t * );
void *PhObjectAlloc( PhSoul_t * );

int PgSetMultiClip( int , PhRect_t const *);
extern int PtRectIntersect( PhRect_t *, PhRect_t const *);
extern int PtRectUnion( PhRect_t *, PhRect_t const *);

extern long _Pk_TranslateKeyAno(char const *);
extern PhTile_t *PhGetTile(void );
extern void PhFreeTile(PhTile_t *);
extern PhTile_t *PhAddTilePnts(PhTile_t *,int ,int ,int ,int );
extern PhTile_t *PhAddTileRect(PhTile_t *,PhRect_t *);
extern PhTile_t *PtClipExtents(PhRect_t const * const clip_out,PhRect_t const * const base);
extern PhTile_t *PhIntersectTilings( PhTile_t const * const tile1, PhTile_t const *tile2, unsigned short *num_intersect_tiles );
extern PhTile_t *PhClipTilings(PhTile_t *tiles, PhTile_t const * const clip_tiles, PhTile_t **intersection);
extern void PgDrawBorder(PhRect_t const *,PgColor_t ,PgColor_t,int );
extern void PgDrawFillBorder(PhRect_t const *,PgColor_t ,PgColor_t );
extern void PgDrawBox(PhRect_t const *,int, PgColor_t, PgColor_t );
extern void PgDrawFillBox(PhRect_t const *,int, PgColor_t, PgColor_t );
extern void PgDrawIBox(int ,int ,int ,int ,int, PgColor_t, PgColor_t );
extern void PgDrawSeparator(PhRect_t const *, PgColor_t, PgColor_t);
extern void PgDrawISeparator(int ,int ,int, PgColor_t, PgColor_t );
extern void PgDrawArrowUp(PhRect_t const *,int,int,  PgColor_t, PgColor_t );
extern void PgDrawArrowDown(PhRect_t const *,int,int, PgColor_t, PgColor_t );
extern void PgDrawArrowRight(PhRect_t const *,int,int, PgColor_t, PgColor_t );
extern void PgDrawArrowLeft(PhRect_t const *,int,int, PgColor_t, PgColor_t );
extern void PgSetTargetRid( PhRid_t );
extern PgColor_t PgHSV(unsigned int ,int ,int );
extern PgColor_t PgHSV2RGB(PgColorHSV_t );
extern PgColorHSV_t PgRGB2HSV(PgColor_t );
extern int PgColorMatch(int, PgColor_t const *, PgColor_t *);
extern int PgGetPalette(PgColor_t *);
extern void __PgAppendData(void const *,unsigned short );
extern int _PgBuildDrawCommand(unsigned int ,int );
extern int PgFFlush( unsigned int );
extern int PgFlush(void );
extern void PgClearDrawBuffer(void);
extern int PgSetDrawBufferSize(unsigned short );
extern void PgExtentInit(void );
extern PhRect_t *PgExtentText(PhRect_t *,PhPoint_t const *,char const *,char const *,unsigned int );
extern void PgSetRegion(PhRid_t );
extern PhGC_t *PgCreateGC( int );
extern void PgDestroyGC(PhGC_t *);
extern PhGC_t *PgSetGC(PhGC_t *);
extern PhGC_t *PgGetGC(void);
extern PgColor_t PgSetStrokeColor(PgColor_t );
extern void PgSetStrokeXORColor(PgColor_t, PgColor_t );
extern void PgSetStrokeDither(PgColor_t ,PgColor_t ,PgPattern_t);
extern void PgSetStrokeTransPat(PgPattern_t);
extern long PgSetStrokeFWidth(long );
extern int PgSetStrokeWidth(int );
extern int PgSetStrokeCap(int );
extern int PgSetStrokeJoin(int );
extern void PgSetStrokeDash(unsigned char const *,int ,long );
extern PgColor_t PgSetFillColor(PgColor_t );
extern void PgSetFillXORColor(PgColor_t, PgColor_t );
extern void PgSetFillDither(PgColor_t ,PgColor_t ,PgPattern_t);
extern void PgSetFillTransPat(PgPattern_t);
extern PgColor_t PgSetTextColor(PgColor_t );
extern void PgSetTextXORColor(PgColor_t, PgColor_t );
extern void PgSetTextDither(PgColor_t ,PgColor_t ,PgPattern_t);
extern void PgSetTextTransPat(PgPattern_t);
extern void PgSetFont(char const *);
extern void PgSetUnderline(PgColor_t ,PgColor_t ,int );
extern int PgSetPalette(PgColor_t const *,long, short ,short ,int, long );
extern void PgResetState(void );
extern unsigned long PgSetPlaneMask(unsigned long );
extern int PgSetDrawMode(int );
extern void PgSetClipping(unsigned short ,PhRect_t const *);
extern void PgSetUserClip(PhRect_t const *);
extern void PgSetUserClipAbsolute(PhRect_t const *);
extern void PgSetTranslation(PhPoint_t const *,int );
extern void PgClearTranslation(void );
extern void PgSetScale(PhLpoint_t const *,int );
extern void PgSetRotation(long ,int );
extern void PgDefaultStroke( PhGC_t *GC );
extern void PgDefaultFill( PhGC_t *GC );
extern void PgDefaultMode( PhGC_t *GC );
extern void PgDefaultGC( PhGC_t *GC );
extern int PgDrawPixel(PhPoint_t const *);
extern int PgDrawIPixel(int ,int );
extern int PgDrawGrid(PhRect_t const *,PhPoint_t const *);
extern int PgDrawLine(PhPoint_t const *,PhPoint_t const *);
extern int PgDrawILine(int ,int ,int ,int );
extern int PgDrawRect(PhRect_t const *,unsigned int );
extern int PgDrawIRect(int ,int ,int ,int ,unsigned int );
extern int PgDrawRoundRect(PhRect_t const *,PhPoint_t const *,unsigned int );
extern int PgDrawBevelBox(PhRect_t const *,PgColor_t ,short ,int );
extern int PgDrawIBevelBox(int ,int ,int ,int ,PgColor_t ,short ,int );
extern int PgDrawEllipse(PhPoint_t const *,PhPoint_t const *,unsigned int );
extern int PgDrawArc(PhPoint_t const *,PhPoint_t const *,unsigned int ,unsigned int ,int );
extern int PgDrawPolygon(PhPoint_t const *,int ,PhPoint_t const *,int );
extern int PgDrawPolygonmx(PhPoint_t const *,int ,PhPoint_t const *,int );
extern int PgDrawPixelArray(PhPoint_t const *,int ,PhPoint_t const *);
extern int PgDrawPixelArraymx(PhPoint_t const *,int ,PhPoint_t const *);
extern int PgDrawSpan( PgSpan_t const *ptr, int num, PhPoint_t const *pos, int flags );
extern int PgDrawSpanmx( PgSpan_t const *ptr, int num, PhPoint_t const *pos, int flags );
extern int PgDrawBezier( PhPoint_t const *ptr, int num, PhPoint_t const *pos, int flags );
extern int PgDrawBeziermx( PhPoint_t const *ptr, int num, PhPoint_t const *pos, int flags );
extern int PgDrawTrend( short const *, PhPoint_t const *, int, int, int, int, unsigned int);
extern int PgDrawTrendmx( short const *, PhPoint_t const *, int, int, int, int, unsigned int);
extern int PgDrawBitmap(void const *,int ,PhPoint_t const *,PhPoint_t const *,int,long );
extern int PgDrawBitmapmx(void const *,int ,PhPoint_t const *,PhPoint_t const *,int,long );
extern int PgDrawImage(void const *,int ,PhPoint_t const *,PhDim_t const *,int,long );
extern int PgDrawImagemx(void const *,int ,PhPoint_t const *,PhDim_t const *,int,long );
extern int PgDrawPhImagemx( PhPoint_t const *pos_p, PhImage_t const *image_p, int flags );
extern int PgDrawTImage( void const *_ptr, int flag, PhPoint_t const *pos_p, PhDim_t const *size, int bpl, long TAG, void const *_Tptr, int Tbpl );
extern int PgDrawTImagemx( void const *_ptr, int flag, PhPoint_t const *pos_p, PhDim_t const *size, int bpl, long TAG, void const *_Tptr, int Tbpl );
extern int PgDrawBeveled( PhRect_t const *rect, PhPoint_t const *radii, PgColor_t secondary, short width, int flags );
extern int PgDrawBezier( PhPoint_t const *ptr, int num, PhPoint_t const *pos, int flags );
extern int PgDrawBeziermx( PhPoint_t const *ptr, int num, PhPoint_t const *pos, int flags );
extern int PgDrawRepBitmap( void const *_ptr, int flag, PhPoint_t const *pos_p, PhPoint_t const *area_p, int bpl, PhPoint_t const *rep, PhPoint_t const *space, long TAG );
extern int PgDrawRepBitmapmx( void const *_ptr, int flag, PhPoint_t const *pos_p, PhPoint_t const *area_p, int bpl, PhPoint_t const *rep, PhPoint_t const *space, long TAG );
extern int PgDrawRepImage( void const *_ptr, int flag, PhPoint_t const *pos_p, PhPoint_t const *area_p, int bpl, PhPoint_t const *rep, PhPoint_t const *space, long TAG );
extern int PgDrawRepImagemx( void const *_ptr, int flag, PhPoint_t const *pos_p, PhPoint_t const *area_p, int bpl, PhPoint_t const *rep, PhPoint_t const *space, long TAG );
extern int PgDrawText(char const *,int ,PhPoint_t const *,int );
extern int PgDrawTextChars(char const *,int ,PhPoint_t const *,int );
// extern int PgDrawTextJustify(char const *,int ,PhPoint_t const *,PhRect_t const *,int );
extern int PgDrawTextArea(char const *,int ,PhRect_t const *,int );
extern int PgDrawTextmx(char const *,int ,PhPoint_t const *,int );
extern int PgDrawString(char const *,PhPoint_t const *);
extern int PgDrawStringmx(char const *,PhPoint_t const *);
extern int PgDrawLimitedString( const char *txt, PhPoint_t const *pos, int maxwidth, PhRect_t *extent );
extern struct _Ph_ctrl *PhReattachRaw(struct _Ph_ctrl *);
extern int PhDetach(struct _Ph_ctrl *);
extern int _PhEventCtrl(unsigned ,void const *,unsigned );
extern PhRid_t PhRegionOpen(unsigned,PhRegion_t const *,PhRect_t const *,void const *);
extern int PhRegionClose(PhRid_t );
extern int PhRegionChange(unsigned long, unsigned long, PhRegion_t const *,PhRect_t const *,void const *);
extern int PhEventEmitmx(PhEvent_t const *,PhRect_t const *,int , iov_t *);
extern int PhEventEmit(PhEvent_t const *,PhRect_t const *,void const *);
extern int _PhRegisterService(unsigned);
extern int _PhDeregisterService(unsigned);
extern PhRect_t *PhGetRects(PhEvent_t const *);
extern void *PhGetData(PhEvent_t const *);
extern unsigned int PhGetMsgSize(PhEvent_t const *);
extern struct _Ph_ctrl *PhAttach(char const *,PhChannelParms_t const *);
extern struct _Ph_ctrl *PhReattach(struct _Ph_ctrl *);
extern int PhInfo(struct _Ph_ctrl *,unsigned int ,void *,int );
extern int PhEventNext(void *,unsigned );
extern int PhEventPeek(void *,unsigned);
extern int PhEventArm(void );
extern int PhEventRead(pid_t ,void *,unsigned);
extern PhRid_t PhWindowOpen(unsigned ,const PhRegion_t *,const PhRect_t *,const PhWindowInfo_t *);
extern int PhWindowChange(unsigned, unsigned,const PhRegion_t *,const PhRect_t *,const PhWindowInfo_t *);
extern int PhWindowClose(PhRid_t );
extern int PhWindowEvent(const PhWindowEvent_t *);
extern int PhInitDrag(PhRid_t ,unsigned ,const PhRect_t *,const PhRect_t *,unsigned int ,const PhDim_t *,const PhDim_t *,const PhDim_t *);
extern int PhBlit(PhRid_t ,const PhRect_t *,const PhPoint_t *);
extern int PhWindowQueryVisible(unsigned flags, PhRid_t rid, unsigned input_group, PhRect_t *rect);
extern int PhQueryRids(unsigned flags, PhRid_t rid, unsigned input_group, unsigned type, unsigned sense, PhRid_t emitter, const PhRect_t *rect, PhRid_t rids[], int num);
extern int PhRegionQuery(PhRid_t ,PhRegion_t *,PhRect_t *,void *,unsigned int );
extern int PhQueryCursor( unsigned short ig, PhCursorInfo_t *buf );
extern PhRegionDataHdr_t *
	PhRegionDataFindType( PhRegion_t const*, PhRegionDataHdr_t const*, short );
extern PhRegionDataHdr_t *
	PhRegionDataNext( PhRegion_t const *, void const *, PhRegionDataHdr_t const * );
extern pid_t video_locate(void );
extern int video_on(pid_t ,short ,short ,short ,short ,short );
extern int video_off(pid_t );
extern int video_move(pid_t ,short ,short ,short ,short );
extern int video_freeze(pid_t ,short );
// extern int video_adjust(pid_t ,VMC2_CONFIG *,char );
extern int video_save(pid_t );
extern int video_load(pid_t );
extern int video_channel(pid_t ,short );
extern int video_color_key(pid_t ,short );
extern int PhTo8859_1( PhKeyEvent_t const * );
extern int PhKeyToMb( char *, PhKeyEvent_t const * );
// extern int video_get_config(pid_t ,VMC2_CONFIG *);
extern struct _Ph_ctrl *PhOpen( char const *device, PhChannelParms_t const *parms );
PhSysInfo_t * PhQuerySystemInfo( PhRid_t rid, PhRect_t const *rect, PhSysInfo_t *sysinfo );
extern int PhTimerArm( PhRid_t, long, unsigned );
extern pid_t PhRegisterName(const char *photon, const char *id);

extern int PhClipboardCopy(unsigned short ig, int n, PhClipHeader const clip[]);
extern void *PhClipboardPasteStart(unsigned short ig);
extern PhClipHeader *PhClipboardPasteType(void *cbdata, PhClipType type);
extern PhClipHeader *PhClipboardPasteTypeN(void *cbdata, int type);
extern void PhClipboardPasteFinish(void *cbdata);
extern int PhClipboardCopyString(unsigned short ig, const char *string);
extern char *PhClipboardPasteString(unsigned short ig);

int PgDeleteCursor( int id );
int PgSetCursorPos( int id, int x, int y );
int PgSetDragPos( int id, int x1, int y1, int x2, int y2 );
int PgSetCursorChar( int id, PgColor_t colr1, PgColor_t colr2, int char1, int char2 );
int PgSetCursorBitmap( int id, int num, PgCursorDef_t const CD[] );

/*
 *	Dec. 96 --^
 */

#if defined(__QNXNTO__)
	int PhChannelAttach( int channel, int connection, struct sigevent const *ev );
#endif

PhConnectId_t PhGetConnectId( void );
PhConnectId_t PhGetConnectInfo( PhConnectId_t coid, PhConnectInfo_t *buf );

unsigned PhLibVersion( void );

/*
 *	March 97
 */

#ifdef PgOld
	extern void PgSetDrawColor(PgColor_t );
	extern void PgSetDither(PgColor_t ,PgColor_t ,char *);
	extern void PgSetTransPattern(char *);
	extern void PgDrawStrokeRect(PhRect_t *);
	extern void PgDrawIStrokeRect(int ,int ,int ,int );
	extern void PgDrawFillRect(PhRect_t *);
	extern void PgDrawIFillRect(int ,int ,int ,int );
	extern void PgDrawStrokeRoundRect(PhRect_t *,PhPoint_t *);
	extern void PgDrawFillRoundRect(PhRect_t *,PhPoint_t *);
	extern void PgDrawStrokeEllipse(PhPoint_t *,PhPoint_t *);
	extern void PgDrawFillEllipse(PhPoint_t *,PhPoint_t *);
	extern int PgSetLineWidth(int );
	extern int PgSetLineCap(int );
	extern int PgSetLineJoin(int );
	extern PgColor_t PgSetBGColor(PgColor_t );
#endif

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>


