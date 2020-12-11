/*
 *	PtConnectionClient.h
 *
 *  Copyright by QNX Software Systems Limited 1996. All rights reserved.
 */

#if !defined(__PT_CONNECTION_CLIENT_H_INCLUDED)
#define __PT_CONNECTION_CLIENT_H_INCLUDED

#include <photon/PtT.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Pt_connection_client PtConnectionClient_t;

#ifndef _PTCONNECTORID_T_DEFINED
    #define _PTCONNECTORID_T_DEFINED
    typedef long PtConnectorId_t;
#endif

typedef int PtConnectionClientErrorFunc_t(
	PtConnectionClient_t *connection, int err
	);

typedef int PtConnectionEventFunc_t(
	PtConnectionClient_t *connection, void *user_data,
	unsigned long type, void const *msg, unsigned len
	);

typedef struct Pt_connection_event_handler {
	unsigned long type;
	PtConnectionEventFunc_t *fun;
	}
		PtConnectionEventHandler_t;

// Flags
#define Pt_CLIENT_GETEVENTS		0x0001
#define Pt_CLIENT_NEEDEVENTS	0x0002

PtConnectionClient_t *PtConnectionFindId( PtConnectorId_t id, int subtype, unsigned flags );
PtConnectionClient_t *PtConnectionFindName( const char *name, int subtype, unsigned flags );
char *PtConnectionTmpName( char name[32] );

void PtConnectionClientDestroy( PtConnectionClient_t *connection );

int PtConnectionSendmx(
		PtConnectionClient_t *connection, unsigned long type,
		int sparts, iov_t *siov, int rparts, iov_t *riov
		);

int PtConnectionSend(
		PtConnectionClient_t *connection,
		unsigned long type, const void *smsg, void *rmsg,
		unsigned snbytes, unsigned rnbytes
		);

int PtConnectionAddEventHandlers(
		PtConnectionClient_t *connection,
		PtConnectionEventHandler_t const *handlers, unsigned nhandlers
		);

PtConnectionClientErrorFunc_t *PtConnectionClientSetError(
		PtConnectionClient_t *connection,
		PtConnectionClientErrorFunc_t *func
		);

void PtConnectionClientSetUserData(
		PtConnectionClient_t *connection, void *data
		);

void *PtConnectionClientGetUserData(
		PtConnectionClient_t *connection
		);

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif
