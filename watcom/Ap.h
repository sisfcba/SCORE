/***********************************************************/
/*                                                         */
/*   Application Builder Library Header: PHOTON Version    */
/*                                                         */
/***********************************************************/

#ifndef _APPLIB_H_INCLUDED
#define _APPLIB_H_INCLUDED

#include <stdio.h>
#include <limits.h>
#include <photon/PtWidget.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*********************************/
/* Constants                     */
/*********************************/

/* menu item types */
#define AB_ITEM_COMMAND			0x0001
#define AB_ITEM_MENU			0x0002
#define AB_ITEM_TOGGLE			0x0004
#define	AB_ITEM_FUNCTION		0x0008
#define AB_ITEM_LINE			0x0010
#define AB_ITEM_COLUMN			0x0020

/* menu item states */
#define	AB_ITEM_NORMAL			0x0000
#define AB_ITEM_DEFAULT			0x0100
#define AB_ITEM_DIM				0x0200
#define AB_ITEM_SET				0x0400

/* locations */
#define AB_LOC_DEFAULT			0
#define AB_LOC_BELOW_WGT		1
#define AB_LOC_ABOVE_WGT		2	
#define AB_LOC_RIGHT_WGT		3
#define AB_LOC_LEFT_WGT			4
#define AB_LOC_TOP_LEFT			5
#define AB_LOC_BOT_LEFT			6
#define AB_LOC_TOP_RIGHT		7
#define AB_LOC_BOT_RIGHT		8
#define AB_LOC_CENTER			9
#define AB_LOC_REL_CURSOR		10
#define AB_LOC_REL_MODULE		11 
#define AB_LOC_ABSOLUTE			12

/* realize flags */
#define AB_FUNC_PRE_REALIZE		0
#define AB_FUNC_POST_REALIZE	1
#define AB_FUNC_BOTH			2

/* menu actions */
#define	AB_ENABLE				1
#define	AB_DISABLE				2

/* module parent indicators */
#define	AB_PARENT				0
#define	AB_NO_PARENT			1

/* processing actions */
#define	AB_EXIT					1
#define	AB_DONE					2
#define AB_CONTINUE				3
#define AB_LOCKED			   -2

/* link types */
#define AB_RAPPL				1
#define AB_RMODULE  			2
#define AB_RWINDOW  			3
#define AB_RDIALOG  			4
#define AB_RMENU	 			5
#define AB_RHELP  				6
#define AB_RRULE  	 			7
#define	AB_CALLBACK				8
#define	AB_OK					9
#define	AB_CANCEL				10
#define	AB_RVIEW				11
#define AB_EDIT					12
#define AB_FILEMENU				13
#define AB_POPLIST				14
#define AB_KEYBOARD				15

/* callback reason codes */
#define ABR_PRE_REALIZE			1
#define ABR_POST_REALIZE		2
#define ABR_CODE				3
#define ABR_DONE				4
#define ABR_CANCEL				5

#define AB_LITEMS				1000
#define AB_MAX_ITEMS			1000
#define AB_PhAB(x)				( 10000 + x )

/*********************************/
/* Typedefs                      */
/*********************************/

/* AB callback info structure */
typedef struct {
	short			reason;
	PtWidget_t		*widget;
	} ApInfo_t;

/* Callback function type */
typedef int ApCallbackF_t( PtWidget_t *widget, ApInfo_t *data, PtCallbackInfo_t *cbinfo );

/* bitmap resource Structure */
typedef struct {
	short			nplanes;
	short			nbytes;
	PgColor_t	    colors[1];
	/* bitmap data follows colors */
	} ApBitmapRes_t;

/* bitmap widget Structure */
typedef struct {
	short			nplanes;
	short			nbytes;
	PgColor_t	   *colors;
	char		  **data;
	} ApBitmap_t;

/* resource structure */
typedef struct {
	int			   value;
	char		   *type;
	char		   *data;
	} ApResource_t;

/* widget structure */
typedef struct {
	char		   *dclass;
	char			level;
	char		   *name;
	ushort_t		res_ctr;
	ApResource_t   *res_tab;
	} ApDBWidget_t;

/* widget data */
typedef struct AB_WIDGET_DATA {
	int			 data_ndx;
	char		*data_name;
	} ApWidgetData_t;

/* class table */
typedef struct AB_CLASS_TABLE {
	const char			*class_text;
	PtWidgetClassRef_t	*const *wclass;
	} ApClassTab_t;

/* appbuilder widget structure */
typedef struct AB_WIDGET_STRUCTURE {
	PtWidget_t *wgt;
	} ApWidget_t;

/* menu item structure */
typedef struct AB_ITEM_STRUCT {
	int			ilevel;				/* item level 1=top, 2=second, etc	*/
	int			istate;				/* item state						*/
	char		iaccelerator;		/* keyboard equivalent key			*/
	char		*iaccel_text;		/* keyboard text description		*/
	short		isep_type;			/* item separator type				*/
	char		*itag;				/* item tag							*/
	void 		*ivalue;			/* item text or object pointer		*/
	} ApItem_t;

/* menu link data */
typedef struct AB_MENU_LINK {
	char		*label;				/* menu label						*/
	char		*title;				/* menu title						*/
	char		*title_font;		/* menu title font					*/
	char		*item_font;			/* menu item font					*/
	short		item_spacing;		/* menu item spacing				*/
	ApItem_t	*item_list;			/* array of item objects			*/
	} ApMenuLink_t;

/* linked item list header */
typedef struct AB_LIST_HEADER {
	struct AB_LIST_HEADER	*next;	/* owll - next pointer				*/
	int						size;	/* size of data area				*/
	} ApListHdr_t;

/* event link data */
typedef struct AB_EVENT_LINK {
	int				type;			/* type of link						*/
	int				cb_style;  		/* style (widget, event, hotkey)	*/
	ulong_t			key_cap;		/* key cap 							*/
	ulong_t			key_mods;		/* keyboard modifiers				*/
	ulong_t			event_mask;		/* raw event mask					*/
	void			*linkobj;		/* pointer to link					*/
	void const		*linkevt;		/* pointer to link events			*/
	char			*tag;			/* link tag identifier				*/
	long			cb_type;      	/* link callback type				*/
	ApCallbackF_t	*lfunction;		/* associated callback function     */
	int				lfunc_ind;		/* cb before/after indicator		*/
	int				loc_pos;		/* location position code			*/
	int				loc_row;		/* y offset	for location			*/
	int				loc_col;		/* x offset for location			*/
	void			*dsdata;		/* data associated to link			*/
	} ApEventLink_t;
 	
/* database structure */
typedef struct {
	int					wgt_ctr;
	ApDBWidget_t		**wgt_list;
	ApEventLink_t const	*links;
	} ApDBase_t;

/* list of events info */
typedef struct AB_EVENT_LIST {
	ApEventLink_t	llist[1];		/* array of links					*/
	} ApEventList_t;

/* list of links info */
typedef struct AB_LINK_LIST {      	
	int				wid;			/* window id for window/dialog		*/
	int				pid[4];			/* one pid for each pane 			*/
	char			label[49];		/* menu labels						*/
	ApEventList_t	*elist;			/* header to list of events			*/
	} ApLinkList_t;

/* window link data */
typedef struct AB_WINDOW_LINK {
	char		wgt_path[PATH_MAX];
	char		icn_path[PATH_MAX];
	char		name[49];
	} ApWindowLink_t;

/* dialog link data */
typedef struct AB_DIALOG_LINK {
	char					wgt_path[PATH_MAX];
	PtWidget_t				*wgt;
	struct Pt_widget_class	*dclass;
	unsigned short			rid;
	PtWidget_t				*child;
	struct Pt_widget_class	*child_class;
	} ApDialogLink_t;

/* picture link data */
typedef struct PICTURE_LINK {
	char		wgt_path[PATH_MAX];
	int			wfunc_ind;
	int			(*wfunction)();
	} ApPictureLink_t;

/* help link data */
typedef struct AB_HELP_LINK {
	char		hlp_path[PATH_MAX];
	char		hlp_name[49];
	} ApHelpLink_t;

/* Extended link data */
typedef struct AB_EXTD_LINK {
	char		target_tag[49];
	char		file_dir[PATH_MAX+1];
	char		file_pat[20];
	long		type_mask;
	int			loc_pos;
	int			loc_row;
	int			loc_col;
	} ApExtdLink_t;

/* Global data structure */
typedef struct Ap_ctrl {
	char			*Ap_exe_path;
	PhPoint_t		Ap_winpos;
	PhPoint_t		Ap_winsize;
	PtWidget_t		*Ap_base_wgt;
	PtFILEr_t		*Ap_resfp;
	long			Ap_resbase;
	char			Ap_lang[16];
	unsigned		spare[2];
	int				Ap_names;
	char			Ap_focus;
	ApClassTab_t	*Ap_classtab;
	int				Ap_classtab_ctr;
	PtWidget_t		*Ap_LIcon, *Ap_SIcon;
	int				Ap_winstate;
	}
		ApCtrl_t;

/*********************************/
/* Externals                     */
/*********************************/

extern const char ApOptions[];

#if !defined(_APSHLIB)
	extern char ab_exe_path[];
#endif

extern ApCtrl_t _Ap_;
#define abbase_wgt	( _Ap_.Ap_base_wgt )
#define ab_names	( _Ap_.Ap_names )
#define ab_winpos	( _Ap_.Ap_winpos )
#define ab_winsize	( _Ap_.Ap_winsize )
#define ab_winstate	( _Ap_.Ap_winstate )
#define ABW_LIcon	( _Ap_.Ap_LIcon )
#define ABW_SIcon	( _Ap_.Ap_SIcon )


/*********************************/
/* Prototypes                    */
/*********************************/

void			   	*ApAlloc( int n, int size, char const *location );
int					ApInitialize( int argc, char *argv[] );
void			    ApError( PtWidget_t *widget, int errvalue, char const *app, char const *msg, char const *location );
char				*ApNLErase( char *string );
int					ApAddClass( char const *class_name, PtWidgetClassRef_t *const *wclass );
int					ApAppendTranslation( char const *fname, char const *lang_ext );
ApDBase_t			*ApOpenDBase( ApEventLink_t const *ld );
ApDBase_t			*ApOpenDBaseFile( char const *path );
ApDBase_t			*ApOpenExecDBaseFile( char const *exec, char const *modname );
int          		ApCloseDBase( ApDBase_t *dbase );
PtWidget_t			*ApCreateWidget( ApDBase_t const *dbase, char const *wname, int x, int y, int nargs, PtArg_t const *args );
PtWidget_t			*ApCreateWidgetFamily( ApDBase_t const *dbase, char const *wname, int x, int y, int nargs, PtArg_t const *args );
int					ApCopyWidget( ApDBase_t const *from_dbase, char const *wname, ApDBase_t *to_dbase, char const *tname );
int					ApDeleteWidget( ApDBase_t *dbase, char const *wname );
int					ApSaveDBaseFile( ApDBase_t const *dbase, char const *path );
ApBitmap_t		   	*ApGetBitmapRes( ApDBase_t const *db, char const *wname );
void				ApFreeBitmapRes( ApBitmap_t *bitmap );
PhImage_t		   	*ApGetImageRes( ApDBase_t const *db, char const *wname );
char			   	*ApGetTextRes( ApDBase_t const *db, char const *wname );
void				ApResClose( void );
int				   	ApSetTranslation( char const *lang_ext );
int					ApCreateModule( ApEventLink_t const *ld, PtWidget_t *w, PtCallbackInfo_t *cbinfo );
PtWidget_t			*ApWidget( PtCallbackInfo_t *cbinfo );
int					ApName( PtWidget_t *widget );
char *				ApInstanceName( PtWidget_t *widget );
PtWidget_t		   	*ApGetWidgetPtr( PtWidget_t *link_instance, int data_value );
PtWidget_t		   	*ApGetInstance( PtWidget_t *widget );
int					ApLinkWindow( PtWidget_t *widget, ApEventLink_t const *l, PtCallbackInfo_t *cbinfo );

void				ApModuleLocation( ApEventLink_t *ld, int loc_type, int x_offset, int y_offset );
void				ApModuleFunction( ApEventLink_t *ld, int (*function)(), int realize_flags );
void				ApModuleParent( ApEventLink_t *ld, int parent, PtWidget_t *widget );

int					ApModifyItemState( ApMenuLink_t *menu, int state, ... );
int					ApModifyItemText( ApMenuLink_t *menu, int item_no, char const *new_text );
char *				ApGetItemText( ApMenuLink_t *menu, int item_no );

int					ApLoadMessageDatabase( const char *name );
char *				ApGetMessage( const char *tag );
void				ApTranslateStrings( PtWidget_t *widget, const char *tag );
char 				*ApMultiStrcat( char *dst, ... );
char 				*ApGetString( char *buf, PtFILEr_t *fp, unsigned len );

#ifdef __cplusplus
}
#endif

#include <photon/PhPackPop.h>

#include <photon/AwFileSelect.h>
#include <photon/AwMessage.h>

#endif
