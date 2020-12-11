/*
 * PtProto.h	
 *		Prototypes for the Photon widget (Pt) library
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */

#ifndef __PT_PROTO_H_INCLUDED
#define __PT_PROTO_H_INCLUDED

#ifndef __PT_T_H_INCLUDED
#include <photon/PtT.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidget_t * PtNextTopLevelWidget( PtWidget_t *widget );

long PtCRC( char const *buffer, int nbytes );
extern 	PtRegId_t * PtAppAddRegProc(PtAppContext_t app, int type, PtRegCallbackProc_t proc, void *data);
extern 	void PtAppRemoveRegProc(PtAppContext_t app, PtRegId_t *reg_id );

/*
 * Wed May 13 1998
 */
 
extern int PtGetControlFlags( void );
extern	int PtAddData( PtDataHdr_t **ptr, long type, long subtype, void *data, long len, PtDataRemoveF_t *remove );
extern	int PtRemoveData( PtDataHdr_t **ptr, long type, long subtype );
extern	void * PtFindNextData( PtDataHdr_t **ptr, PtDataHdr_t *data, long type, long subtype, long *len, PtDataHdr_t **_node );
extern	void * PtFindData( PtDataHdr_t **ptr, long type, long subtype, long *len, PtDataHdr_t **_node );
extern	int PtUnlinkData( PtDataHdr_t **ptr, PtDataHdr_t *node );

/*
 *Tue Apr 21  1998
 */

extern int PtBlit( PtWidget_t *widget, PhRect_t const *src, PhPoint_t const *delta );
extern const PhGrafxInfo_t *PtGetGraphicsInfo( PtWidget_t *widget );
extern void PtSuperClassRealized( PtWidgetClassRef_t *cref, PtWidget_t *widget );
extern void PtSuperClassCalcOpaque( PtWidgetClassRef_t *cref, PtWidget_t *widget );
extern void PtContainerRegister( PtWidget_t *widget );
extern void PtContainerDeregister( PtWidget_t *widget );
extern int PtApplyAnchors( PtWidget_t *widget );

/*
 * April 14, 1998
 */
 
extern int PtAddWidgetData( PtWidget_t *widget, PtWidgetClassRef_t *type, long subtype, void *data );
extern int PtRemoveWidgetData( PtWidget_t *widget, PtWidgetClassRef_t *type, long subtype );
extern void * PtFindNextWidgetData( PtWidget_t *widget, PtDataHdr_t *data, PtWidgetClassRef_t *type, long subtype, PtDataHdr_t **_node );
extern void * PtFindWidgetData( PtWidget_t *widget, PtWidgetClassRef_t *type, long subtype, PtDataHdr_t **_node );

/*
 * July 14, 1997
 */

extern unsigned long PtWidgetClassFlags( PtWidget_t *widget );
extern PtWidget_t * PtSuperConstrainer( PtWidget_t *widget );
extern void PtInvokeChildMovedResized( PtWidget_t *child, PhArea_t *oarea, PhRect_t *oextent );
extern void PtInvokeChildCreated( PtWidget_t *child );
extern void PtInvokeChildDestroyed( PtWidget_t *child );
extern int PtInvokeChildSettingResource( PtWidget_t *child, PtArg_t const *argt );
extern int PtInvokeChildGettingResource( PtWidget_t *child, PtArg_t *argt );
extern int PtInvokeChildGettingFocus( PtWidget_t *child, PhEvent_t *event );
extern int PtInvokeChildLosingFocus( PtWidget_t *child, PhEvent_t *event );
 
/*
 * July 2, 1997
 */

extern int PtChildType( PtWidget_t *parent, PtWidget_t *child );
extern PtWidget_t * PtFindGuardian( PtWidget_t *child, int superior_only );
extern void PtInvokeChildRealized( PtWidget_t *child );
extern void PtInvokeChildUnRealized( PtWidget_t *child );

/*
 * June 23, 1997
 */
 
extern int PtResizeEventMsg( PtAppContext_t app, int msg_size );
extern int PtWidgetInsert( PtWidget_t *widget, PtWidget_t *new_sibling, int behind );
extern int PtCalcAbsPosition(PtWidget_t *widget, PhPoint_t const *pos, PhDim_t const *dim, PhPoint_t *new_pos);
extern PtWidgetClass_t *PtCreateFileSelClass( void );
extern PtWidgetClass_t *PtCreateUpDownClass( void );
extern PtWidgetClass_t *PtCreateNumericClass( void );
extern PtWidgetClass_t *PtCreateNumericIntegerClass( void );
extern int PtComboBoxListOpen( PtWidget_t *widget);
extern int PtComboBoxListClose( PtWidget_t *widget);
	extern PhRect_t *
PtChildBoundingBox( PtWidget_t *widget, PhRect_t *canvas, PhRect_t *render );
	extern void 
PpPrintWidget( PpPrintContext_t *pc, PtWidget_t *widget, PhPoint_t const *trans, PhRect_t const *clip_rect, ulong_t opt );
	int
_pt_rect_direction( PhRect_t *orect, PhRect_t *irect, int direction, int nring, int prim_mult, int sec_mult, int kslope, int penalty, 
	int *slope_band, long *prim, long *sec );
	extern void
PtSuperClassChildCreated( PtWidgetClassRef_t *cref, PtWidget_t *widget, PtWidget_t *child );
	extern void
PtSuperClassChildDestroyed( PtWidgetClassRef_t *cref, PtWidget_t *widget, PtWidget_t *child );
	extern void
PtSuperClassChildRealized( PtWidgetClassRef_t *cref, PtWidget_t *widget, PtWidget_t *child );
	extern void
PtSuperClassChildUnrealized( PtWidgetClassRef_t *cref, PtWidget_t *widget, PtWidget_t *child );
	extern int
PtSuperClassChildGettingFocus( PtWidgetClassRef_t *cref, PtWidget_t *widget, PtWidget_t *child, PhEvent_t *event );
	extern int
PtSuperClassChildLosingFocus( PtWidgetClassRef_t *cref, PtWidget_t *widget, PtWidget_t *child, PhEvent_t *event );
	extern void
PtSuperClassChildMovedResized( PtWidgetClassRef_t *cref, PtWidget_t *widget, PtWidget_t *child, PhArea_t *current_area, PhRect_t *current_extent, PhArea_t *old_area, PhRect_t *old_extent );
	extern int
PtSuperClassChildSettingResources( PtWidgetClassRef_t *cref, PtWidget_t *widget, PtWidget_t *child, PtArg_t const *argt);
	extern int
PtSuperClassChildGettingResources( PtWidgetClassRef_t *cref, PtWidget_t *widget, PtWidget_t *child, PtArg_t *argt);
	extern PtWidget_t * 
PtGlobalFocusPrevContainer( PtWidget_t *widget, PhEvent_t *event );
	extern PtWidget_t * 
PtGlobalFocusPrev( PtWidget_t *widget, PhEvent_t *event );
	extern PtWidget_t * 
PtGlobalFocusNext( PtWidget_t *widget, PhEvent_t *event );
	extern PtWidget_t *
PtGlobalFocusNextContainer( PtWidget_t *widget, PhEvent_t *event );
	extern PtWidget_t * 
PtFindFocusChild( PtWidget_t *widget );
	extern PtWidget_t *
PtCompoundRedirect( PtWidget_t *widget, PtWidgetClassRef_t *a_class );

extern long PtWidgetFlags(PtWidget_t *widget);

/*
 * Sept. /96 --^
 */

//extern PtWidget_t * PtGlobalFocusNextFrom( PtWidget_t *widget, PhEvent_t *event );
//extern PtWidget_t * PtGlobalFocusPrevFrom( PtWidget_t *widget, PhEvent_t *event );

extern PtWidget_t * PtFindConditionalWidget( PtWidget_t *widget, int direction, int(*skip)(PtWidget_t *, void *) );
extern PtWidget_t * PtFindWidget( PtWidget_t *widget, int direction );
extern int PtBeep( void ); 
extern int PtIsFocused( PtWidget_t *widget );

/*
 * July /96 --^
 */

extern PtWidgetClass_t *PtCreateDividerClass( void );
extern void PtSetAnchorOffsets( PtWidgetList_t *wlp );
extern PtResourceRec_t const * PtFindResourceRecord( long type, PtWidgetClass_t const *a_class );
extern PtWidget_t *PtAllocWidget( PtWidgetClass_t *aclass );
extern void PtCompoundCallbackRedirect( PtWidget_t *widget, PtWidget_t *child, PtResourceRec_t const *rr, PtArg_t const *argt );
extern PtWidget_t * PtValidParent( PtWidget_t *widget, PtWidgetClassRef_t *a_class );
extern int PtWidgetVisibleExtent( PtWidget_t *widget, PhRect_t *rect );
extern void PtInvalidateSystemInfo( PtWidget_t *widget );
extern void PtEmitFepEvent( PtWidget_t *widget, PhEvent_t const *event, PhRect_t const *cursor_rel_rect, long type );
extern int PtFepRequest( PhKeyEvent_t const *key_event );

/*
 * June 6+/96 --^
 */

extern void PtBkgdHandlerProcess(void);
extern PhSysInfo_t *PtQuerySystemInfo( PtWidget_t *widget, PhSysInfo_t *sysinfo );
/*
 * April 22/96 --^
 */

extern PtWidget_t *PtFindDisjoint( PtWidget_t *widget );
extern int PtResizePolicy( PtWidget_t *widget );
/*
 * April 96 --^
 */

extern PtWidget_t *PtHit( PtWidget_t *widget, unsigned level, PhRect_t const *rect );
extern int PtFlagWidgetRebuild( PtWidget_t *widget );
extern int PtFlagWidgetResize( PtWidget_t *widget );
extern int PtWidgetIsRealized( PtWidget_t *widget );
extern PhDim_t *PtWidgetDim( PtWidget_t *widget, PhDim_t *dim );
extern PhArea_t *PtWidgetArea( PtWidget_t *widget , PhArea_t *area );
extern PhRect_t *PtDeTranslateRect( PhRect_t *, PhPoint_t const *);
extern PtWidgetClassRef_t *PtWidgetClass( PtWidget_t * );
extern void PtSuperClassExtent( PtWidgetClassRef_t *, PtWidget_t *);
extern int PtSuperClassInit( PtWidgetClassRef_t *, PtWidget_t *);
extern int PtSuperClassInitFrom( PtWidgetClassRef_t *, PtWidget_t *);
extern void PtSuperClassDraw( PtWidgetClassRef_t *, PtWidget_t *, PhTile_t const *damage_list);
extern int PtSuperClassRawEvent( PtWidgetClassRef_t *, PtWidget_t *, void *data, PtCallbackInfo_t *cbinfo);
extern int PtSuperClassRawEventFrom( PtWidgetClassRef_t *, PtWidget_t *, void *data, PtCallbackInfo_t *cbinfo);
extern int PtSuperClassLostFocus( PtWidgetClassRef_t *, PtWidget_t *, PhEvent_t *);
extern void PtSuperClassGotFocus( PtWidgetClassRef_t *, PtWidget_t *, PhEvent_t *);
extern int PtSuperClassGetResources( PtWidgetClassRef_t *, PtWidget_t *, int, PtArg_t *arg_list);
extern int PtSuperClassSetResources( PtWidgetClassRef_t *, PtWidget_t *, int, PtArg_t const *arg_list);
extern int PtSuperClassConnect( PtWidgetClassRef_t *, PtWidget_t * );
extern int PtSuperClassConnectFrom( PtWidgetClassRef_t *, PtWidget_t * );
extern int PtContainerChildRedirect( PtWidget_t *, PtWidget_t *(*redirect)( PtWidget_t  *, PtWidgetClassRef_t * ) );
/*
 * March 96 --^
 */

extern PtWidgetClass_t *PtCreateArcClass( void );
extern PtWidgetClass_t *PtCreateBasicClass( void );
extern PtWidgetClass_t *PtCreateBitmapClass( void );
extern PtWidgetClass_t *PtCreateBkgdClass( void );
extern PtWidgetClass_t *PtCreateButtonClass( void );
extern PtWidgetClass_t *PtCreateComboBoxClass( void );
extern PtWidgetClass_t *PtCreateContainerClass( void );
extern PtWidgetClass_t *PtCreateEllipseClass( void );
extern PtWidgetClass_t *PtCreateGaugeClass( void );
extern PtWidgetClass_t *PtCreateGraphicClass( void );
extern PtWidgetClass_t *PtCreateGroupClass( void );
extern PtWidgetClass_t *PtCreateIconClass( void );
extern PtWidgetClass_t *PtCreateLabelClass( void );
extern PtWidgetClass_t *PtCreateLineClass( void );
extern PtWidgetClass_t *PtCreateListClass( void );
extern PtWidgetClass_t *PtCreateMenuClass( void );
extern PtWidgetClass_t *PtCreateMenuButtonClass( void );
extern PtWidgetClass_t *PtCreateMultiTextClass( void );
extern PtWidgetClass_t *PtCreateOnOffButtonClass( void );
extern PtWidgetClass_t *PtCreatePaneClass( void );
extern PtWidgetClass_t *PtCreatePixelClass( void );
extern PtWidgetClass_t *PtCreateRawClass( void );
extern PtWidgetClass_t *PtCreateRectClass( void );
extern PtWidgetClass_t *PtCreateRegionClass( void );
extern PtWidgetClass_t *PtCreateScrollAreaClass( void );
extern PtWidgetClass_t *PtCreateScrollbarClass( void );
extern PtWidgetClass_t *PtCreateSeparatorClass( void );
extern PtWidgetClass_t *PtCreateSliderClass( void );
extern PtWidgetClass_t *PtCreateTextClass( void );
extern PtWidgetClass_t *PtCreateToggleButtonClass( void );
extern PtWidgetClass_t *PtCreateCoreClass( void );
extern PtWidgetClass_t *PtCreateWindowClass( void );
extern PtWidgetClass_t *PtCreateMessageClass( void );
extern PtWidgetClass_t *PtCreatePolygonClass( void );
extern PtWidgetClass_t *PtCreateCompoundClass( void );
extern PtWidgetClass_t *PtCreateBezierClass( void );
extern PtWidgetClass_t *PtCreateGenListClass( void );
extern PtWidgetClass_t *PtCreateMenuBarClass( void );
extern PtWidgetClass_t *PtCreateMenuLabelClass( void );
extern PtWidgetClass_t *PtCreateTimerClass( void );
extern PtWidgetClass_t *PtCreateGenTreeClass( void );
extern PtWidgetClass_t *PtCreateTreeClass( void );
extern PtWidgetClass_t *PtCreateGridClass( void );
extern PtWidgetClass_t *PtCreateProgressClass( void );
extern PtWidgetClass_t *PtCreateTerminalClass( void );
extern PtWidgetClass_t *PtCreateTtyClass( void );
extern PtWidgetClass_t *PtCreateTabClass( void );
extern PtWidget_t * PtAppInit( PtAppContext_t *,int *, char **, int , PtArg_t const *);
extern PhRect_t *PtWidgetCanvas( PtWidget_t *widget, PhRect_t *rect);
extern void PtLabelPos(PtWidget_t *,PhPoint_t const *,PhPoint_t *);
extern int PtLabelRepairString(PtWidget_t *,int ,char const *);
extern void PtCalcAnchorOffsets( PtWidget_t *, PhRect_t const * );
extern PhRect_t * PtSetExtentFromArea( PtWidget_t *, PhArea_t const *,PhRect_t *);
extern int PtInit(char const *);
extern int PtStartPen(PtWidget_t *);
extern int PtSetStruct( char *, PtResourceRec_t const*, PtArg_t const *);
extern PhArea_t *PtSetAreaFromExtent( PtWidget_t *, PhRect_t const *, PhArea_t *);
extern PhArea_t *PtSetAreaFromWidgetCanvas( PtWidget_t *, PhRect_t const *, PhArea_t *);
extern int PtGetStruct(char *, PtResourceRec_t const *mod, PtArg_t *);
extern int PtGetAnchoredExtent(PtWidget_t *, PhRect_t const *, PhRect_t * );
extern int PtSetValue(PtWidget_t *,PtResourceRec_t const *,PtArg_t const *);
extern int PtSetResources(PtWidget_t *,int ,PtArg_t const *);
extern int PtCoreSetResources(PtWidget_t *widget, int num, PtArg_t const *args, PtResourceRec_t const *rrec);
extern int PtCompoundSetResources(PtWidget_t *widget, int num, PtArg_t const *args, PtResourceRec_t const *rrec);
extern int PtGetResources(PtWidget_t *,int ,PtArg_t *);
extern int PtCoreGetResources(PtWidget_t *,int ,PtArg_t *);
extern int PtCompoundGetResources(PtWidget_t *,int ,PtArg_t *);
extern int PtNullWidget_f(PtWidget_t *);
extern PtWidget_t *PtSetParentWidget(PtWidget_t *);
extern PtWidget_t *PtGetParentWidget(void);
extern PhPoint_t *PtWidgetOffset(PtWidget_t *,PhPoint_t *);
extern PhRect_t *PtWidgetExtent( PtWidget_t *, PhRect_t * );
extern PtWidgetClass_t *PtCreateWidgetClass(PtWidgetClassRef_t *,unsigned int ,unsigned int ,PtArg_t const *);
extern PtWidget_t *PtWidgetSkip(PtWidget_t *,PtWidget_t *);
extern PtWidget_t *PtWidgetDrawSkip(PtWidget_t *,PtWidget_t *);
extern PtWidget_t *PtInflateBalloon( PtWidget_t *win, PtWidget_t *widget, int balloon_position, char const *message, char const *font, PgColor_t fill, PgColor_t text_color);
extern PtWidget_t *PtWidgetAbove(PtWidget_t *root,PtWidget_t *current);
extern PtWidget_t *PtWidgetDrawAbove(PtWidget_t *,PtWidget_t *);
extern PtWidget_t *PtWidgetFamily(PtWidget_t *,PtWidget_t *);
extern PtWidget_t *PtWidgetDrawFamily(PtWidget_t *,PtWidget_t *);
extern PtWidget_t *PtCreateWidget(PtWidgetClassRef_t *,PtWidget_t *,unsigned int ,PtArg_t const *);
extern PtWidget_t *PtExtentWidget(PtWidget_t *);
extern int PtRealizeWidget(PtWidget_t *);
extern int PtDrawWidget(unsigned int ,PtWidget_t *);
extern int PtDrawClippedWidget(unsigned int ,PtWidget_t *,int ,PhRect_t const *);
extern int PtUnrealizeWidget(PtWidget_t *);
extern int PtRemoveWidget( void );
extern int PtRemoveWidgetInstance(PtWidget_t *);
extern int PtDestroyWidget(PtWidget_t *);
extern int PtEventHandler(PhEvent_t *);
extern PhGC_t *PtSetGC(PhGC_t *);
extern int PtForceUpdate(void );
extern int PtHoldWidget(PtWidget_t *);
extern int PtReleaseWidget(PtWidget_t *);
extern int PtReRealizeWidget(PtWidget_t *);
extern int PtResizeWidget(PtWidget_t *);
extern int PtMoveResizeWidget(PtWidget_t *,unsigned);
extern int PtUpdateWidgetVisibility(PtWidget_t *,PhRect_t *);
extern int PtUpdateWidgetVisibilityAbs(PtWidget_t *,PhRect_t *);
extern int PtRepairFamilyVisibility(PtWidget_t *,PhRect_t *);
extern int PtRepairVisibility(PtWidget_t *,PhRect_t *);
extern int PtUpdateFamilyVisibility(PtWidget_t *,PhRect_t *);
extern int PtUpdateVisibility(PtWidget_t *,PhRect_t *);
extern void PtRemoveDamage(PtWidget_t *widget, PhPoint_t const *unused, PhTile_t *tile_list, int n_unused);
extern int PtStartFlux(PtWidget_t *);
extern int PtEndFlux(PtWidget_t *);
extern int PtIsFluxing(PtWidget_t *);
extern int PtHold(void );
extern int PtFlush(void );
extern int PtRelease(void );
extern int PtSyncWidget(PtWidget_t *);
extern int PtUpdate(void );
extern int PtDamageCleanWidget(PtWidget_t *);
extern int PtDamageWidget(PtWidget_t *);
extern void PtDamageExposed(PtWidget_t *,PhTile_t *);
extern int PtDamageExtent(PtWidget_t *,PhRect_t const *);
extern PtWidget_t *PtFindContainer(PtWidget_t *);
extern PtWidget_t *PtFindDiscontinuous(PtWidget_t *);
extern int PtWidgetIsClassMember(PtWidget_t *,PtWidgetClassRef_t *);
extern PtWidget_t *PtFindChildClass(PtWidgetClassRef_t *,PtWidget_t *);
extern PtWidget_t *PtFindChildClassMember(PtWidgetClassRef_t *,PtWidget_t *);
extern int PtWidgetIsClear(PtWidget_t *);
extern int PtWidgetIsObscured(PtWidget_t *);
extern int PtWidgetToFront(PtWidget_t *);
extern int PtWidgetToBack(PtWidget_t *);
extern int PtInvokeCallbackList(PtCallbackList_t *,PtWidget_t *,PtCallbackInfo_t *);
extern int PtDestroyCallbackList(PtCallbackList_t **);
extern void PtClipStart(PhRect_t const *);
extern int PtClipAdd(PtWidget_t *,PhRect_t *);
extern int PtClipRemove(void );
extern void PtWindowToBack(PtWidget_t *);
extern void PtWindowToFront(PtWidget_t *);
extern int PtWindowFocus(PtWidget_t *);
extern int PtForwardWindowEvent(PhWindowEvent_t const *);
extern int PtForwardWindowConfig(WmConfig_t const *, int);
extern WmConfig_t *PtGetWindowConfig(WmConfig_t *);
extern int PtForwardWindowTaskEvent(PhConnectId_t, PhWindowEvent_t const *);
extern int PtWindowConsoleSwitch(PhRid_t);
extern int PtConsoleSwitch(int);
extern void PtGetAbsPosition(PtWidget_t *,short *,short *);
extern PtWidget_t * PtGetParent(PtWidget_t *,PtWidgetClassRef_t *);
extern int PtTranslateCoord(PtWidget_t *,PhPoint_t const *,PhPoint_t *);
extern PhRect_t *PtTranslateRect( PhRect_t *rect, PhPoint_t const *point );
extern PtWidget_t *PtEventToWidget(PhEvent_t const *);
extern int PtToAscii(PhKeyEvent_t const *);
extern PtAppContext_t PtDefaultAppContext(void );
extern PtAppContext_t PtCreateAppContext(void );
extern void PtBasicActivate(PtWidget_t *,PtCallbackInfo_t *);
extern int PtBasicSetFill(PtWidget_t *);
extern PhRect_t *PtBasicInteriorExtent(PtWidget_t *,PhRect_t *);
extern PhRect_t *PtBasicWidgetCanvas(PtWidget_t *,PhRect_t *);
extern int PtBasicSetColor(PtWidget_t *);
extern int PtLabelSetColor( PtWidget_t *);
extern void PtBasicHighlight(PtWidget_t *);
extern int PtContainerHold(PtWidget_t *);
extern int PtContainerInit( PtWidget_t *);
extern int PtContainerRelease(PtWidget_t *);
extern PtWidget_t *PtContainerBox(PtWidget_t *,PtWidget_t *,PhRect_t const *);
extern PtWidget_t *PtContainerHit(PtWidget_t *,unsigned int ,PhRect_t const *);
extern PtWidget_t *PtContainerGiveFocus(PtWidget_t *,PhEvent_t *);
extern PtWidget_t *PtContainerFindFocus(PtWidget_t *);
extern PtWidget_t *PtContainerNullFocus(PtWidget_t *,PhEvent_t *);
extern PtWidget_t *PtContainerRelinquishFocus(PtWidget_t *,PhEvent_t *);
extern PtWidget_t *PtContainerFocusNext(PtWidget_t *,PhEvent_t *);
extern PtWidget_t *PtContainerFocusPrev(PtWidget_t *,PhEvent_t *);
extern PtWidget_t *PtFindFocusChild( PtWidget_t *widget ); 
extern PtWidget_t *PtFindFocusNextFrom( PtWidget_t *widget );
extern PtWidget_t *PtGlobalFocusNextFrom( PtWidget_t *widget, PhEvent_t *event );
extern PtWidget_t *PtFindFocusPrevFrom( PtWidget_t *widget );
extern PtWidget_t *PtGlobalFocusPrevFrom( PtWidget_t *widget, PhEvent_t *event );
extern PtWidget_t *PtContainerNext( PtWidget_t *widget );
extern PtWidget_t *PtContainerPrev( PtWidget_t *widget );
extern int PtInvokeResizeCallbacks(PtWidget_t *);
extern PtWorkProcId_t * PtAppAddWorkProc(PtAppContext_t ,PtWorkProc_t ,void *);
extern void PtAppRemoveWorkProc(PtAppContext_t ,PtWorkProcId_t *);
extern PtInputId_t * PtAppAddInput(PtAppContext_t ,pid_t ,PtInputCallbackProc_t ,void *);
extern void PtAppRemoveInput(PtAppContext_t ,PtInputId_t *);
extern void PtAppProcessEvent(PtAppContext_t );
extern void PtProcessEvent(void );
extern void PtAppMainLoop(PtAppContext_t );
extern void PtMainLoop(void );
extern int PtGraphicSetStroke(PtWidget_t *);
extern unsigned PtGraphicFillGC( PtWidget_t *widget, unsigned flags );
extern void PtGraphicExtendMargin(PtWidget_t *);
extern void PtLabelPos(PtWidget_t *,PhPoint_t const *,PhPoint_t *);
extern int PtLabelRepairString(PtWidget_t *,int ,char const *);
extern PhRect_t *PtLabelWidgetCanvas(PtWidget_t *,PhRect_t *);
extern int PtAttemptResize(PtWidget_t *,PhRect_t const *,PhRect_t const *);
extern int PtCalcRegion(unsigned int *,PtWidget_t *,PhRegion_t *,PhRect_t *);
extern void PtCoreChangeRegion(unsigned int ,PtWidget_t *);
extern PhRect_t *PtWidgetCanvas(PtWidget_t *,PhRect_t *);
extern PhPoint_t *PtWindowPosition(PtWidget_t *,PhPoint_t *);
extern int PtWindowSetInfo(unsigned int ,PtWidget_t *);
extern void PtFrameSize(ulong_t ,int ,int *,int *,int *,int *);
extern PhRid_t PtWidgetRid( PtWidget_t * );
extern int PtClearWidget( PtWidget_t * );
extern void PtAddCallback( PtWidget_t *, unsigned long callback_type, PtCallbackF_t *callback, void *);
extern void PtAddCallbacks( PtWidget_t *, unsigned long callback_type, PtCallback_t const *callbacks, unsigned int );
extern void PtRemoveCallback( PtWidget_t *, unsigned long callback_type, PtCallbackF_t *callback, void *data );
extern void PtRemoveCallbacks( PtWidget_t *, unsigned long callback_type, PtCallback_t const *callbacks, unsigned int );
extern void PtAddEventHandler( PtWidget_t *, unsigned long event_mask, PtCallbackF_t *callback,  void *data );
extern void PtAddEventHandlers( PtWidget_t *, PtRawCallback_t const *, unsigned int );
extern void PtRemoveEventHandler( PtWidget_t *, unsigned long , PtCallbackF_t *callback, void *);
extern void PtRemoveEventHandlers( PtWidget_t *, PtRawCallback_t const *, int );
extern void PtAddHotkeyHandler( PtWidget_t *, unsigned , unsigned , short, void *, PtCallbackF_t *event_f );
extern void PtRemoveHotkeyHandler( PtWidget_t *, unsigned , unsigned , short, void *, PtCallbackF_t *event_f );
extern int PtWidgetIsClass( PtWidget_t *, PtWidgetClassRef_t *);
extern PtWidget_t * PtWidgetParent( PtWidget_t *);
extern PtWidget_t * PtWidgetChildFront( PtWidget_t *);
extern PtWidget_t * PtWidgetChildBack( PtWidget_t *);
extern PtWidget_t * PtWidgetBrotherInFront( PtWidget_t *);
extern PtWidget_t * PtWidgetBrotherBehind( PtWidget_t *);
extern int PtRectIntersect( PhRect_t *, PhRect_t const *);
extern int PtRectUnion( PhRect_t *, PhRect_t const *);
extern PhRect_t * PtChildClipRect( PtWidget_t *, PhRect_t * );
extern PhRect_t * PtWidgetInteriorExtent( PtWidget_t *, PhRect_t * );
extern void PtAnchorWidget( PtWidget_t * );
extern int PtReattach( char * );
extern int PtAskQuestion( PtWidget_t *, char const *, char const *, char const *, char const *, char const *, char const *, int );
extern int PtMessageBox( PtWidget_t *, char const *, char const *, char const *, char const *);
extern int PtAlert( PtWidget_t *, PhPoint_t const *, char const *, PhImage_t const *, char const *, char const *, int, char const **, char const **, int, int, int );
extern int PtPrompt( PtWidget_t *, PhPoint_t const *, char const *, PhImage_t const *, char const *, char const *, int, char const **, char const **, int, int, short, char *, char const *, PhDim_t const *, int );
extern int PtNotice( PtWidget_t *, PhPoint_t const *, char const *, PhImage_t const *, char const *, char const *, char const *, char const *, int );
extern void PtSetCustomCursor(PtWidget_t *,PhCursorDef_t const *);
extern PhCursorDef_t *PtCreateCustomCursor(PtWidget_t *,PhDim_t const *,PhPoint_t const *,void const *,void const *,PgColor_t,PgColor_t);
extern void PtSyncPhoton( );
extern int PtModalStart( );
extern void PtModalEnd( int );
extern void PtPositionMenu( PtWidget_t *, PhEvent_t *);
extern int PtListAddItems( PtWidget_t *widget, const char **items, int item_count, unsigned int position ) ;
extern int PtListItemExists( PtWidget_t *widget, const char *item );
extern int PtListItemPos( PtWidget_t *widget, const char *item );
extern int PtListReplaceItemPos( PtWidget_t *widget, const char **new_items, int item_count, int position );
extern int PtListReplaceItems( PtWidget_t *widget, const char **old_items, const char **new_items, int item_count );
extern int PtListDeleteItems( PtWidget_t *widget, const char **items, int item_count );
extern int PtListDeletePositions( PtWidget_t *widget, int const *pos_list, int pos_count );
extern int PtListRemovePositions( PtWidget_t *widget, unsigned short const *pos_list, int pos_count );
extern int PtListDeleteItemPos( PtWidget_t *widget, int item_count, int position );
extern int PtListDeleteAllItems( PtWidget_t *widget );
extern int PtReParentWidget( PtWidget_t *widget, PtWidget_t *parent );
extern int PtExtentWidgetFamily( PtWidget_t *widget );
extern int PtWidgetTree( PtWidget_t *root, PtWidget_t **cur, int D );
extern int PtWidgetTreeTraverse( PtWidget_t *root, PtWidget_t **cur, int D, int (*skip_cond_f)(PtWidget_t *, void *), void * );
extern PtWidget_t * PtWidgetHelpHit( PtWidget_t *widget, PhPoint_t const *pos );
extern int _PtAnchorParent( PtWidget_t *widget, PhDim_t const *new_dim, int flag );
extern long PtWindowGetState( PtWidget_t *widget );
extern int mbstrlen( char const *, int , int * );
extern int mbstrnlen( char const *, int, int , int * );
extern int mbstrblen( char const *, int, int , int * );
extern int mbstrncmp( char const *, char const *, int , int );
extern PtWidget_t *PtValidParent( PtWidget_t *, PtWidgetClassRef_t * );
extern int PtSendEventToWidget( PtWidget_t *, PhEvent_t * );
extern int PtTimerArm( PtWidget_t *, unsigned int );
extern int PtCBoxAddItems( PtWidget_t *widget, char const **items, int item_count, unsigned int position ) ;
extern int PtCBoxItemExists( PtWidget_t *widget, char const *item );
extern int PtCBoxItemPos( PtWidget_t *widget, char const *item );
extern int PtCBoxReplaceItemPos( PtWidget_t *widget, char const **new_items, int item_count, int position );
extern int PtCBoxReplaceItems( PtWidget_t *widget, char const **old_items, const char **new_items, int item_count );
extern int PtCBoxDeleteItems( PtWidget_t *widget, char const **items, int item_count );
extern int PtCBoxDeletePositions( PtWidget_t *widget, unsigned int const *pos_list, int pos_count );
extern int PtCBoxDeleteItemPos( PtWidget_t *widget, int item_count, int position );
extern int PtCBoxDeleteAllItems( PtWidget_t *widget );
extern int PtCBoxSelectPos( PtWidget_t *widget, int pos );
extern int PtCBoxUnselectPos( PtWidget_t *widget, int pos );

extern const char *PtFontSelection(PtWidget_t *widget, const PhPoint_t *pos, const char *title, const char *font, long symbol, unsigned flags, const char *sample);
extern int PtPrintSelection(PtWidget_t *widget, PhPoint_t const *pos, const char *title, PpPrintContext_t *context, unsigned flags);

extern int  PtAppAddSignalProc(PtAppContext_t context, sigset_t const *sig, PtSignalProc_t proc, void *data);
extern int  PtAppRemoveSignalProc(PtAppContext_t context, sigset_t const *sig);
extern int PtAppRemoveSignal( PtAppContext_t app, sigset_t const *setp, PtSignalProc_t proc, void *data );
extern int PtAppCallSignalProc(PtAppContext_t context);

extern int PtChannelCreate( void );
extern pid_t PtAppCreatePulse( PtAppContext_t app, int priority );
extern struct Pt_Pulse *_PtFindPulse( PtAppContext_t app, pid_t i );
#if defined(__QNXNTO__)
	extern pid_t PtGetRcvidPid( int rcvid );
#else
	#define PtGetRcvidPid( rcvid )	(rcvid)
	extern pid_t _PtGetPulsePid( PtAppContext_t app, pid_t i );
#endif
extern int PtAppDeletePulse( PtAppContext_t app, pid_t i );
extern PtPulseMsgId_t *PtPulseArmPid( PtAppContext_t app, pid_t pulse, pid_t pid, PtPulseMsg_t *msg );
extern PtPulseMsgId_t *PtPulseArmFd( PtAppContext_t app, pid_t pulse, int fd, PtPulseMsg_t *msg );
extern void PtPulseDisarm( PtPulseMsgId_t * );
extern int PtPulseDeliver( pid_t rcvid, PtPulseMsg_t const *pulse );
extern int PtAppPulseTrigger( PtAppContext_t app, pid_t pulse );

typedef int PtFdProcF_t( int fd, void *data, unsigned mode );
typedef PtFdProcF_t *PtFdProc_t;

extern int PtAppAddFd( PtAppContext_t app, int fd, unsigned mode, PtFdProc_t fun, void *data );

extern int PtAppAddFdPri( PtAppContext_t app, int fd, unsigned mode, PtFdProc_t fun, void *data, int priority );

extern int PtAppSetFdMode( PtAppContext_t app, int fd, unsigned mode );

extern int PtAppRemoveFd( PtAppContext_t app, int fd );


extern pid_t PtSpawn(
	const char *cmd, const char *const *argv, const char *const *env,
	const PtSpawnOptions_t *opt, PtSpawnCbF_t *cb, void *data,
	PtSpawnCbId_t **idp
	);
extern void PtSpawnSetCallback( PtSpawnCbId_t *id, PtSpawnCbF_t *fun, void *data );
extern void PtSpawnDeleteCallback( PtSpawnCbId_t *id );
extern int PtSpawnWait(
	const char *cmd, const char **argv, const char **env,
	const PtSpawnOptions_t *opt, pid_t *pidp
	);

extern int PtWaitPid( pid_t pid );

/* Shared-library-safe versions of I/O functions: */
PtFILEr_t *PtFopenR( const char *path );
int PtFcloseR( PtFILEr_t *fp );
int PtGetc( PtFILEr_t *fp );
int PtSeekR( PtFILEr_t *fp, long pos, int whence );
long PtTellR( PtFILEr_t *fp );
int PtFilenoR( PtFILEr_t *fp );
unsigned PtRead( PtFILEr_t *fp, void *buf, unsigned len );
char *PtFgets( char *buf, unsigned len, PtFILEr_t *fp );

PtFILEw_t *PtFopenW( const char *path );
int PtFcloseW( PtFILEw_t *fp );
int PtWrite( PtFILEw_t *fp, void const *buf, unsigned len );
int PtPuts( const char *str, PtFILEw_t *fp );
int PtPutc( int ch, PtFILEw_t *fp );

long PtStrtol( char const **p );
unsigned long PtStrtoul( char const **p );

#ifdef __cplusplus
};

typedef void PtCallbackOldF_t(PtWidget_t*,void*,PtCallbackInfo_t*);

inline void PtAddCallback( PtWidget_t *w, unsigned long callback_type, PtCallbackOldF_t *callback, void *data ) {
	PtAddCallback( w, callback_type, (PtCallbackF_t*) callback, data );
	}

inline void PtRemoveCallback( PtWidget_t *w, unsigned long callback_type, PtCallbackOldF_t *callback, void *data ) {
	PtRemoveCallback( w, callback_type, (PtCallbackF_t*) callback, data );
	}

inline void PtAddEventHandler( PtWidget_t *w, unsigned long event_mask, PtCallbackOldF_t *callback, void *data ) {
	PtAddEventHandler( w, event_mask, (PtCallbackF_t*) callback, data );
	}

inline void PtRemoveEventHandler( PtWidget_t *w, unsigned long event_mask, PtCallbackOldF_t *callback, void *data ) {
	PtRemoveEventHandler( w, event_mask, (PtCallbackF_t*) callback, data );
	}

inline void PtAddHotkeyHandler( PtWidget_t *w, unsigned sym_cap, unsigned mods, short flags, void *data, PtCallbackOldF_t *callback ) {
	PtAddHotkeyHandler( w, sym_cap, mods, flags, data, (PtCallbackF_t*) callback );
	}

inline void PtRemoveHotkeyHandler( PtWidget_t *w, unsigned sym_cap, unsigned mods, short flags, void *data, PtCallbackOldF_t *callback ) {
	PtRemoveHotkeyHandler( w, sym_cap, mods, flags, data, (PtCallbackF_t*) callback );
	}


#endif /* __cplusplus */

#include <photon/PhPackPop.h>

#endif /* __PT_PROTO_H_INCLUDED */

