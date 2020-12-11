/*
 *	PtClient.h
 *		Header file for the PtClient widget class
 *
 *  Copyright by QNX Software Systems Limited 1996. All rights reserved.
 */
#ifndef __PT_CLIENT_H_INCLUDED
#define __PT_CLIENT_H_INCLUDED

#ifndef __PT_CONTAINER_H_INCLUDED
 #include <photon/PtContainer.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * PtClient public
 */

extern PtWidgetClassRef_t *const PtClient;

/* Resources */

#define Pt_ARG_CLIENT_SERVER		Pt_RESOURCE( 99,  0 ) // Now read-only
#define Pt_ARG_CLIENT_SEND			Pt_RESOURCE( 99,  1 )
#define Pt_ARG_CLIENT_REPLY_LEN		Pt_RESOURCE( 99,  2 )
#define Pt_ARG_CLIENT_NAME			Pt_RESOURCE( 99,  4 ) // New
#define Pt_ARG_CLIENT_FLAGS			Pt_RESOURCE( 99,  7 ) // New
#define Pt_CB_CLIENT_EVENT			Pt_RESOURCE( 99,  3 )
#define Pt_CB_CLIENT_CONNECTED		Pt_RESOURCE( 99,  6 ) // New
#define Pt_CB_CLIENT_NOT_FOUND		Pt_RESOURCE( 99,  8 ) // New


/* Flags in Pt_ARG_CLIENT_FLAGS */
#define Pt_CLIENT_NONBLOCK	0x0001
#define Pt_CLIENT_NOEVENTS	0x0002

/* Callback structure */
typedef struct Pt_client_callback {
	void const *message;
	unsigned nbytes;
	}
		PtClientCallback_t;



/* Widget structure */

typedef struct Pt_client_widget {
	PtContainerWidget_t	cntr;
	struct Pt_connection_client *connection;
	void *reply;
	unsigned reply_len;
	int reply_nbytes;
	PtCallbackList_t *event;
	PhRect_t				old_extent;
	char *name;
	unsigned flags;
	PtWorkProcId_t *bgid;
	PtCallbackList_t *notfound;
	PtCallbackList_t *connected;
	long reserved[ 10 ];
	}
		PtClientWidget_t;

/* Widget union */
typedef union Pt_client_union {
	PtWidget_t				core;
	PtBasicWidget_t			basic;
	PtContainerWidget_t		cntnr;
	PtClientWidget_t		clnt;
	}
		PtClientUnion_t;

typedef int PtClientNotifyF_t(
	PtWidget_t *widget, long type, void const *msg, unsigned len
	);

typedef struct Pt_client_widget_class {
    PtContainerClass_t	container;
	PtClientNotifyF_t	*notify;
	}
		PtClientClass_t;

#define Pt_SET_CLIENT_NOTIFY_F	Pt_ARG_IS_POINTER( PtClientClass_t, notify )

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif

