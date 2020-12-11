/*
 *	PtConnectionServer.h
 *
 *  Copyright by QNX Software Systems Limited 1996. All rights reserved.
 */

#if !defined(__PT_CONNECTION_SERVER_H_INCLUDED)
#define __PT_CONNECTION_SERVER_H_INCLUDED

#include <signal.h>
#include <photon/PtT.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Pt_connection_server PtConnectionServer_t;
typedef struct Pt_connector PtConnector_t;

#ifndef _PTCONNECTORID_T_DEFINED
    #define _PTCONNECTORID_T_DEFINED
    typedef long PtConnectorId_t;
#endif

typedef void PtConnectorCallbackFunc_t(
	PtConnector_t *connector,
	PtConnectionServer_t *connection,
	void *user_data
	);

typedef void const *PtConnectionMsgFunc_t(
	PtConnectionServer_t *connection, void *user_data,
	unsigned long type, void const *msg, unsigned len,
	unsigned *reply_len
	);

typedef int PtConnectionServerErrorFunc_t(
	PtConnectionServer_t *connection, int err
	);

typedef struct Pt_connection_msg_handler {
	unsigned long type;
	PtConnectionMsgFunc_t *fun;
	}
		PtConnectionMsgHandler_t;

/* Flags for PtConnectionNotify */
#define Pt_CONNECTION_NOTIFY_RESIZE  1	/* Resize buffer if necessary */
#define Pt_CONNECTION_NOTIFY_NOFLUSH 2	/* Don't flush if buffer too small */
#define Pt_CONNECTION_NOTIFY_FLUSH   4	/* Force a flush */

PtConnector_t *PtConnectorCreate( const char *name, PtConnectorCallbackFunc_t *cb, void *data );
PtConnectorId_t PtConnectorGetId( PtConnector_t const *connector );
int PtConnectorDestroy( PtConnector_t *ctor );

void PtConnectionServerDestroy( PtConnectionServer_t *connection );

int PtConnectionFlush( PtConnectionServer_t *connection );

int PtConnectionNotify(
        PtConnectionServer_t *connection, unsigned long type,
        void const *message, unsigned length, unsigned flags
        );

int PtConnectionAddMsgHandlers(
	PtConnectionServer_t *connection,
	PtConnectionMsgHandler_t const handlers[], unsigned nhandlers
	);

int PtConnectionResizeEventBuffer(
	PtConnectionServer_t *connection, unsigned length
	);

PtConnectionServerErrorFunc_t *PtConnectionServerSetError(
	PtConnectionServer_t *connection,
	PtConnectionServerErrorFunc_t *func
	);

void PtConnectionServerSetUserData(
	PtConnectionServer_t *connection, void *data
	);

void *PtConnectionServerGetUserData(
	PtConnectionServer_t *connection
	);

int PtConnectionReply(
	PtConnectionServer_t *connection, int len, void const *buf
	);

int PtConnectionReplymx(
	PtConnectionServer_t *connection, int n, iov_t *iov
	);

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>
#endif
