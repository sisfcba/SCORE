// PxHelp.h
// Photon Help System
// Aug 95
// Copyright QNX Software Systems Ltd

#ifndef _PT_HELP_INCLUDED
#define _PT_HELP_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

//
// Defines
//

#define HELPMSG	0xbeef
#define HELPMSG_SUBTYPE_ERROR	0x0
#define HELPMSG_SUBTYPE_OK	0x1
#define HELPMSG_SUBTYPE_URL	0x2
#define HELPMSG_SUBTYPE_TOC	0x3
#define HELPMSG_SUBTYPE_TREE 	0x4
#define HELPMSG_SUBTYPE_QUIT 	0x5
#define HELPMSG_SUBTYPE_SEARCH 	0x6

#define HELPCMD "helpviewer"
#define HELPPATH "/usr/photon/bin/helpviewer"
//#define HELPPATH "/src/photon/helpviewer1.1/helpviewer/src/default/helpviewer"
#define HELPROOT "/usr/help/product/"
#define MSGSIZE sizeof( HelpMsg )
#define MSG2SIZE sizeof( HelpMsg2 )

#define HELP_SEARCH_MODE_TITLE		0
#define HELP_SEARCH_MODE_TEXT		1
#define HELP_SEARCH_MODE_DISPLAYED	2

#define HELP_SEARCH_SCOPE_ALL		0
#define HELP_SEARCH_SCOPE_SELECTED	1

#define HELP_SEARCH_METHOD_EXACT	0
#define HELP_SEARCH_METHOD_WORD		1
#define HELP_SEARCH_METHOD_SUBSTRING	2

//
// Structures
//

typedef struct
{
	unsigned short type;
	unsigned short subtype;
	char string[1];
} HelpMsg;

typedef struct
{
	unsigned short type;
	unsigned short subtype;
	int arg1;
	int arg2;
	int arg3;
	char string[1];
} HelpMsg2;

//
// Globals
//

//
// Prototypes
//

extern void PtHelpQuit( void );
extern int PtHelpUrl( char * url  );
extern void PtHelpUrlRoot( char * url );
extern int PtHelpTopic( char * topic );
extern void PtHelpTopicRoot( char * topic );
extern int PtHelpTopicTree( char * path );
extern int PtHelpSearch( char * string, int mode, int scope, int method );

#ifdef __cplusplus
};
#endif
#endif
