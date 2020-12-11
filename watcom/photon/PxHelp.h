// PxHelp.h
// Photon Help System
// Aug 95
// Copyright QNX Software Systems Ltd

#ifndef _PX_HELP_INCLUDED
#define _PX_HELP_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#include <photon/PtHelp.h>

//
// Prototypes
//

extern void PxHelpQuit( void );
extern int PxHelpUrl( char * url  );
extern void PxHelpUrlRoot( char * url );
extern int PxHelpTopic( char * topic );
extern void PxHelpTopicRoot( char * topic );
extern int PxHelpTopicTree( char * path );
extern int PxHelpSearch( char * string, int mode, int scope, int method );

#ifdef __cplusplus
};
#endif
#endif
