#ifndef __AW_FILE_SELECT_H_INCLUDED
#define __AW_FILE_SELECT_H_INCLUDED

#ifndef __PT_WIDGET_H_INCLUDED
 #include <PtWidget.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern PtWidgetClassRef_t *AwFileSelect;

typedef struct {
	PtWidget_t				core;
	char					*dirpath;
	char					*filespec;
	char					*filename;
	char					*action_txt;
	char					*cancel_txt;
	PtCallbackList_t		*action;
	PtCallbackList_t		*cancel;
} AwFileSelectWidget_t;

/* callback structure */
typedef struct {
	char					*dirpath;
	char					*filename;
	char					*filespec;
	} AwFileSelectCallback_t;

/* resources */
#define Aw_ARG_DIRECTORY_PATH 	Pt_RESOURCE( AB_PhAB( 2 ), 0 )
#define Aw_ARG_FILE_SPEC      	Pt_RESOURCE( AB_PhAB( 2 ), 1 )
#define Aw_ARG_FILE_NAME      	Pt_RESOURCE( AB_PhAB( 2 ), 2 )
#define Aw_ARG_ACTION_TEXT    	Pt_RESOURCE( AB_PhAB( 2 ), 3 )
#define Aw_ARG_CANCEL_TEXT    	Pt_RESOURCE( AB_PhAB( 2 ), 4 )

/* callback resources */
#define Aw_CB_FS_ACTION			Pt_RESOURCE( AB_PhAB( 2 ), 5 )
#define Aw_CB_FS_CANCEL			Pt_RESOURCE( AB_PhAB( 2 ), 6 )

/* prototypes */
extern	void			 AwDfltsFileSelect( PtWidget_t *widget );
extern	int				 AwProcreateFileSelect( PtWidget_t *widget );
extern	int				 AwFSSetup( PtWidget_t *widget, void *data, PtCallbackInfo_t *cbinfo );
extern	void			 AwFSDispDirs( );
extern	void			 AwFSDispFiles( );
extern	int 			 AwFSReadDir( );
extern	void			 AwFSNewDir( );
extern	int 			 AwFSCompare( const void *, const void * );
extern	int				 AwFSSelect( PtWidget_t *widget, void *data, PtCallbackInfo_t *cbinfo );
extern	int				 AwFSList( PtWidget_t *widget, void *data, PtCallbackInfo_t *cbinfo );
extern	int				 AwFSDirectory( PtWidget_t *widget, void *data, PtCallbackInfo_t *cbinfo );
extern	int				 AwFSPath( PtWidget_t *widget, void *data, PtCallbackInfo_t *cbinfo );
extern	int				 AwFSFileSpec( PtWidget_t *widget, void *data, PtCallbackInfo_t *cbinfo );
extern	int				 AwFSDirPath( PtWidget_t *widget, void *data, PtCallbackInfo_t *cbinfo );
extern  int				 AwFSAction( PtWidget_t *widget, void *data, PtCallbackInfo_t *cbinfo );
extern  int				 AwFSCancel( PtWidget_t *widget, void *data, PtCallbackInfo_t *cbinfo );
extern	int				 AwDestroyFileSelect( PtWidget_t *widget );
extern	PtWidgetClass_t	*AwCreateFileSelectClass( void );

#ifdef __cplusplus
};
#endif
#endif
