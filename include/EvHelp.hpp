//****************************************************************************
//
//			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
//	   DSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 1.0
//
//	PROJECT		: ALL
//
//	SYSTEM		: ALL
//
//	FILE		: EvHelp.hpp    
//
//	DESCRIPTION	: Global header file for EvHelp  module
//
//	AUTHOR		: Wallace Santos Lages
//
//	OPERATING SYSTEM:  QNX 4.25		-	COMPILER: WATCOM C++ - V10.6
//
//	VERSION		: 1.0			-		DATE	:	09/04/1999
//
//	HISTORY
//----------------------------------------------------------------------------
//Date     | Description                                          | Author 
//----------------------------------------------------------------------------
//09/04/99 | Initial edition                                      | Wallace
//----------------------------------------------------------------------------
//****************************************************************************
#ifndef		_EVHELP_H_
#define		_EVHELP_H_

// ************************* Include files *************************

/* Standard headers */
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>

/* Toolkit headers */
#include <Ph.h>
#include <Pt.h>
#include <Ap.h>

/* Score headers */
extern "C" 
{
	#include <Relatorios.h>
	#include <Prototipos.h>
	#include <RelPrototipos.h>
	#include <ScoreMsgs.h>
	#include <ScoreErros.h>
	#include <OperacaoBibW.h>
	#include <ComumIHM.h>

	#ifdef	CBA_120KAII_III
	  #include <Score.h>
	  #include <VarsComum.h>
	  #include <IniArqVar.h>
	#endif


};


// ************************  Functions defined in this module  ***********************

#define EV_HELP_LINES 5 //total of lines of the help ev window

//************************************************************************************
// CLASS NAME  :  EvHelp                                                             |
// DESCRIPTION :  Provide functions to show small window containing the help for a   |
//             :  given event                                                        |  
//             :                                                                     |
// VERSION     :  1.0 - 20/05/99                                                     |
// AUTHOR      :  Wallace Santos Lages                                               |
// REMARKS     :                                                                     |
//************************************************************************************

class EvHelp
{
private:

	PtWidget_t	*WidDone;                   //pointer to the done button
	PtWidget_t	*WidWindow;                 //pointer to the window itself
	void HelpEvph( char *evento );           //fill the evhelp window

	int HelpWindow;	                        // >0 if the help window is open
	void CreateWindow(PtWidget_t *apParent );//Create the window and realize it
	PtWidget_t * EvHelpLine[EV_HELP_LINES]; //pointer to lines in the online ev help  


public:
	void DestroyWindow( void );
	int SetupHelpEv( char * event,PtWidget_t *apParent  ); //show the help window for the event
	void HideEvHelp(void);  //hide the help window

};

void ShowEvent( PtWidget_t  * apParent, char * event );

int EvHelpDone( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo );	

char *ProcEv(char *event);

// this is a callback function called when the user clicks the done button
// and must be defined somewhere in the user code
//extern int
//onHelpEv.Done( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo );



#endif