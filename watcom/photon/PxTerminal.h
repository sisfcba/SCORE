/*
 *	PxTerminal.h
 *		Header file for the PtTerminal extras
 *
 *  Copyright by QNX Software Systems Limited 1998. All rights reserved.
 */
#ifndef __PX_TERMINAL_H_INCLUDED
#define __PX_TERMINAL_H_INCLUDED

#ifndef __PT_TERMINAL_H_INCLUDED
	#include <photon/PtTerm.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Px_terminal_cs_names_t {
	char *AnsiCharsetName;
	char *InternalCharsetName;
	char *FontCharsetName;
	int reserved;
	}
		PxTerminalCsNames_t;

#define Px_TERMINAL_UNICODE_FONT	( (char*) -1 )

PtTerminalCharsets_t *PxTerminalBuildCharsets( PxTerminalCsNames_t const *names );

PtTerminalCharsets_t *PxTerminalLoadCharsets(
	const char *filename, PxTerminalCsNames_t *names
	);

int PxTerminalSaveCharsets(
	PtTerminalCharsets_t *charsets,
	PxTerminalCsNames_t *names,
	const char *filename
	);

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif /* __PX_TERMINAL_H_INCLUDED */
