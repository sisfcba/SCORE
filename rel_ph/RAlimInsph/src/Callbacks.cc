/* Y o u r   D e s c r i p t i o n                       */
/*                            AppBuilder Photon Code Lib */
/*                                         Version 1.14C */
//****************************************************************************
//
//			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
//	   SCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 1.0
//
//	PROJECT		: ALL
//
//	SYSTEM		: ALL
//
//	FILE		: Callbacks.cc
//
//	DESCRIPTION	: This module contain all calbacks functions
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
/*********************************** Revisoes ********************************\
$Id: Callbacks.cc,v 1.2 2003/08/06 13:47:50 alex Exp $

$Log: Callbacks.cc,v $
Revision 1.2  2003/08/06 13:47:50  alex
interface 1024x768

\*********************************** Revisoes ********************************/

/* Standard headers */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

/* Toolkit headers */
#include <Ph.h>
#include <Pt.h>
#include <Ap.h>

/* Local headers */
#include "RAlimInsPH.hpp"
#include "GlobaisPH.hpp"
#include "abimport.h"
#include "proto.h"

//-------------------------------------------------------------------------------------------------
//
// StartPrincipal
//
//-------------------------------------------------------------------------------------------------
int StartPrincipal( PtWidget_t *link_instance, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )
{
  int			count;
  PtWidget_t	*aux[20];
  
  /* eliminate 'unreferenced' warnings */
  link_instance = link_instance, apinfo = apinfo, cbinfo = cbinfo;

  ApModuleParent(ABM_PRINCIPAL,AB_NO_PARENT,ABW_base);
  ApModuleParent(ABM_PRINCIPAL_X,AB_NO_PARENT,ABW_base);

  if( Comum->IHM[GetLoginPhindows()].TamIHM == 0 ) // 640x480
    ApCreateModule( ABM_PRINCIPAL, NULL, NULL );
  else // 1024x768
    ApCreateModule( ABM_PRINCIPAL_X, NULL, NULL );

  PegaWidgets( gWidgets );
  for( count = 0; count < Comum->NumGruposCuba; ++count )
  {
    aux[count] = gWidgets.grupo[count];
    PtSetStringValue( gWidgets.grupo[count], ScoreGetStr(SCORE_MSG_50+count) );
  }	
  for( ; count < PH_MAX_GRUPOS_CUBAS; ++count )
  {
    if( gWidgets.grupo[count] != NULL )
	  PtDestroyWidget( gWidgets.grupo[count] );
  }

  if( Comum->IHM[GetLoginPhindows()].TamIHM == 0 ) // 640x480
  {
    aux[Comum->NumGruposCuba] = ABW_PRINCIPAL_sair;
    PtSetPosWids( ABW_PRINCIPAL, aux, (short)(Comum->NumGruposCuba+1), 0, 0 );
  
    PtSetStringValue( ABW_PRINCIPAL_sair, ScoreGetStr(SCORE_MSG_474) );
    PtSetStringValue( ABW_PRINCIPAL_titulo, ScoreGetStr(TIT_REL_INS_ALIM_PF) );
    PtSetStringValue( ABW_PRINCIPAL_cab1, ScoreGetStr(HD1_REL_INS_ALIM_PF) );
    PtSetStringValue( ABW_PRINCIPAL_cab2, ScoreGetStr(HD2_REL_INS_ALIM_PF) );
    SetaLimitesScroll( ABW_PRINCIPAL_scrollbar, gGrupo );
  }
  else // 1024x768
  {
    aux[Comum->NumGruposCuba] = ABW_PRINCIPAL_X_sair;
    PtSetPosWids( ABW_PRINCIPAL_X, aux, (short)(Comum->NumGruposCuba+1), 0, 0 );
  
    PtSetStringValue( ABW_PRINCIPAL_X_sair, ScoreGetStr(SCORE_MSG_474) );
    PtSetStringValue( ABW_PRINCIPAL_X_titulo, ScoreGetStr(TIT_REL_INS_ALIM_PF) );
    PtSetStringValue( ABW_PRINCIPAL_X_cab1, ScoreGetStr(HD1_REL_INS_ALIM_PF) );
    PtSetStringValue( ABW_PRINCIPAL_X_cab2, ScoreGetStr(HD2_REL_INS_ALIM_PF) );
    SetaLimitesScroll( ABW_PRINCIPAL_X_scrollbar, gGrupo );
  }
  MontaTela( gWidgets, gpAlarme, gCnfAla, gGrupo );
  ExibeTela( gWidgets, gGrupo, gPos );
  return( Pt_CONTINUE );
}

//-------------------------------------------------------------------------------------------------
//
// Pagina
//
//-------------------------------------------------------------------------------------------------
int Pagina( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )
{
  PtArg_t	args[3];
  int		*pos;
  /* eliminate 'unreferenced' warnings */
  widget = widget, apinfo = apinfo, cbinfo = cbinfo;
  PtSetArg( &args[0], Pt_ARG_SCROLL_POSITION, &pos, 0 );
  if( Comum->IHM[GetLoginPhindows()].TamIHM == 0 ) // 640x480
    PtGetResources( ABW_PRINCIPAL_scrollbar, 1, args );
  else // 1024x768
    PtGetResources( ABW_PRINCIPAL_X_scrollbar, 1, args );
  if( *pos >= 0 && *pos < Comum->NumCubasGrupo[gGrupo] )
  {
    gPos = (short int)*pos;
    ExibeTela( gWidgets, gGrupo, gPos );
  }	
  return( Pt_CONTINUE );
}

//-------------------------------------------------------------------------------------------------
//
// Timer
//
//-------------------------------------------------------------------------------------------------
int Timer( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )
{
  /* eliminate 'unreferenced' warnings */
  widget = widget, apinfo = apinfo, cbinfo = cbinfo;
  if( LeTabelas() )
  {
    gFPrincipal = FALSO;
    return( Pt_CONTINUE );
  }	
  MontaTela( gWidgets, gpAlarme, gCnfAla, gGrupo );
  ExibeTela( gWidgets, gGrupo, gPos );
  return( Pt_CONTINUE );
}

//-------------------------------------------------------------------------------------------------
//
// Grupo
//
//-------------------------------------------------------------------------------------------------
int Grupo( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )
{
  short int	i;
  /* eliminate 'unreferenced' warnings */
  widget = widget, apinfo = apinfo, cbinfo = cbinfo;
  for( i = 0; i < PH_MAX_GRUPOS_CUBAS; ++i )
  {
	if( widget == gWidgets.grupo[i] )
	  PtSetFlags( gWidgets.grupo[gGrupo], Pt_SET, FALSO );
  }
  for( i = 0; i < PH_MAX_GRUPOS_CUBAS; ++i )
  {
	if( widget == gWidgets.grupo[i] )
	{
	  gGrupo = i;
	  gPos = 0;
  	  if( Comum->IHM[GetLoginPhindows()].TamIHM == 0 ) // 640x480
  	    SetaLimitesScroll( ABW_PRINCIPAL_scrollbar, gGrupo );
  	  else // 1024x768
  	    SetaLimitesScroll( ABW_PRINCIPAL_X_scrollbar, gGrupo );
  	  MontaTela( gWidgets, gpAlarme, gCnfAla, gGrupo );
  	  ExibeTela( gWidgets, gGrupo, gPos );
	  break;
	}
  }
  PtSetFlags( gWidgets.grupo[gGrupo], Pt_SET, VERDADEIRO );
  return( Pt_CONTINUE );
}

//-------------------------------------------------------------------------------------------------
//
// Sair
//
//-------------------------------------------------------------------------------------------------
int Sair( PtWidget_t *widget, ApInfo_t *apinfo, PtCallbackInfo_t *cbinfo )
{
  /* eliminate 'unreferenced' warnings */
  widget = widget, apinfo = apinfo, cbinfo = cbinfo;
  SolicitaLeitura(SEMAF_READ_CLEIT,1);
  SolicitaLeitura(SEMAF_READ_PARAM,1);
  SolicitaLeitura(SEMAF_READ_USER1,1);
  exit(0);  
  return( Pt_CONTINUE );
}
