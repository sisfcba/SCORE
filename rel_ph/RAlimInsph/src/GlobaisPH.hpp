//****************************************************************************
//
//			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
//	   SCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 1.0
//
//	PROJECT		: ALL
//
//	SYSTEM		: ALL
//
//	FILE		: GlobaisPH.hpp
//
//	DESCRIPTION	: This module contain all the global variables
//
//	AUTHOR		: Alexandre Mariz Bandeira de Morais
//
//	OPERATING SYSTEM:  QNX 4.25		-	COMPILER: WATCOM C++ - V10.6
//
//	VERSION		: 1.0			-		DATE	:	23/04/02
//
//	HISTORY
//----------------------------------------------------------------------------
//Date     | Description                                          | Author 
//----------------------------------------------------------------------------
//23/04/02 | Initial edition                                      | Bandeira
//----------------------------------------------------------------------------
//****************************************************************************

#ifndef	_GLOBAISPH
	#define	_GLOBAISPH

#include "RAlimInsPH.hpp"

#if defined(__cplusplus)
extern "C" {
#endif

DECL	short int			gGrupo;
DECL	short int			gFPrincipal;
DECL	short int			gPos;
DECL	t_alarmePH			*gpAlarme;
DECL	t_arqvar			gArq;
DECL	t_widgets			gWidgets;
DECL	t_cnf_alarme		gCnfAla;

#if defined(__cplusplus)
};
#endif

#endif
