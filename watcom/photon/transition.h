

/*
 *
 * TO BE REMOVED BEFORE BETA
 *
 */

#ifndef Ph_TRANSITION
	#define Ph_TRANSITION 1
#endif

#if Ph_TRANSITION
	#define Ph_TRIGGER_UP			0x0001
	#define Ph_TRIGGER_DOWN			0x0000
	#define src emitter
	#define dest collector
	#define events_select events_sense
	#define bro_above bro_in_front
	#define Ph_VISIBLE				Ph_FORCE_BOUNDARY
	#define PhOpenRegion PhRegionOpen
	#define PhChangeRegion PhRegionChange
	#define PhCloseRegion PhRegionClose
	#define PhOpenWindow PhWindowOpen
	#define PhChangeWindow PhWindowChange
	#define PhCloseWindow PhWindowClose
	#define PgInitExtent PgExtentInit
	#define PgQueryExtent PgExtentQuery
	#define receiver collector
	#define TRIGGER EMIT
	#define trigger emit
	#define PtUninitWidget PtUnrealizeWidget
	#define uninit_f unrealize_f
	#define Pt_SET_UNINIT_F Pt_SET_UNREALIZE_F
	#define Pt_FORCE_UNINIT Pt_FORCE_UNREALIZE
	#define _Ph_RSET_OWNER			Ph_REGION_OWNER
	#define _Ph_RSET_HANDLE			Ph_REGION_HANDLE
	#define _Ph_RSET_FLAGS			Ph_REGION_FLAGS
	#define _Ph_RSET_EV_OPAQUE		Ph_REGION_EV_OPAQUE
	#define _Ph_RSET_EV_SELECT		Ph_REGION_EV_SENSE
	#define _Ph_RSET_STATE			Ph_REGION_STATE
	#define _Ph_RSET_ORIGIN			Ph_REGION_ORIGIN
	#define _Ph_RSET_PARENT			Ph_REGION_PARENT
	#define _Ph_RSET_ABOVE			Ph_REGION_ABOVE
	#define _Ph_RSET_BEHIND			Ph_REGION_BEHIND
	#define _Ph_RSET_TILES			Ph_REGION_RECT
	#define _Ph_RSET_DATA			Ph_REGION_DATA
	#define _Ph_RSET_CURSOR			Ph_REGION_CURSOR
	#define Ph_EV_RELEASE_PHANTASMAGORIC	Ph_EV_RELEASE_PHANTOM
	#define Ph_REGION_ABOVE			0x0100
	#define EmitEvent EventEmit
	#define BGFillColor BGColor
#endif
