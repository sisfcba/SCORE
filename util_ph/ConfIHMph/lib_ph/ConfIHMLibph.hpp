//****************************************************************************
//
//			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
//	   DSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 1.0
//
//	PROJECT		: ALL
//
//	SYSTEM		: ALL
//
//	FILE		: ConfIHMLibph.hpp
//
//	DESCRIPTION	: Header file for the Photon Score ConfIHM library.
//                Contains the prototypes of the library functions.
//
//	AUTHOR		: Alexandre Bandeira
//
//	OPERATING SYSTEM:  QNX 4.25		-	COMPILER: WATCOM C++ - V10.6
//
//	VERSION		: 1.0			-		DATE	:	03/03/99
//
//	HISTORY
//----------------------------------------------------------------------------
//Date     | Description                                          | Author 
//----------------------------------------------------------------------------
//03/03/99 | Initial edition                                      | Bandeira
//----------------------------------------------------------------------------
//****************************************************************************

#ifndef	_CONFIHMLIBPH_H
#define _CONFIHMLIBPH_H

/* Toolkit headers */
#include <IhmPh.hpp>
#include <Pt.h>

// functions prototypes
#if defined(__cplusplus)
extern "C" {
#endif

void BuildButton( CIhmConfig & aIhm, CTelaIhm & aSIhm, CBotaoIhm & aBIhm, PtWidget_t *apButton,
			   	  PtWidget_t *apLabel, PtWidget_t *apMenu, PtWidget_t *apMain, PtWidget_t *apTitulo,
				  short int aButtonScreen );
void BuildStamp( CTelaSelo & aStamp, PtWidget_t *apList[] );
void *MemoryAllocate( long aNBytes, int aType );
void *MemoryFree( void *apMemory, int aType );
void *Warning( char *apMsg );
void *Error( char *apMsg );
void *Progress( int aPercent );

#if defined(__cplusplus)
};
#endif

#endif
