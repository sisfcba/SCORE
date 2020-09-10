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
//	FILE		: RAlimInsPH.cc
//
//	DESCRIPTION	:
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

#define	PROGRAMA_PRINCIPAL

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

/* Application Options string */
const char ApOptions[] =
	AB_OPTIONS ""; /* Add your options in the "" */

int ini_rel( int argc, char *argv[] )
{
  int	status;
  char	erro[160];
  char	*p;
  
  /* eliminate 'unreferenced' warnings */
  argc = argc, argv = argv;
  /* Pega area comum de memoria */
  if( PegaComum( &Comum ) )
  {
	sprintf(erro, ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_0 );
	NoticeScoreph( NULL, ScoreGetStr(NOME_ERRO), erro );
	exit(0);
  }
  /* Pega area comum RelGraf de memoria */
  if( PegaRelGraf() )
  {
	sprintf(erro, ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_1 );
	NoticeScoreph( NULL, ScoreGetStr(NOME_ERRO), erro );
	exit(0);
  }
  if( ( p = getlogin() ) == NULL )
  {
	sprintf(erro, ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_105 );
	NoticeScoreph( NULL, ScoreGetStr(NOME_ERRO), erro );
	exit(0);
  }
  sprintf( erro, "%s/%s", PH_NOME_COMUM_ALARME, p );
  /* abre estrutura de alarmes de cubas e linha */
  gpAlarme = (t_alarmePH *)LeComum( erro, sizeof( t_alarmePH ) * (MAX_CUBAS+1) );
  if( My_nid ne AVL.NodoNoControle )
  {
	/* -- Le tabela de configuracao de graficos do nodo no controle -- */
	status = ScoreBd(AVL.NodoNoControle,TABELA_CNF_REL_GRAF,BD_LER,
				     (void *)PCnfRelGraf, 0, sizeof(t_cnf_rel_graf) );
	if( status )
	{
	  sprintf( erro, ScoreGetStr(SCORE_ERR_4), My_name, COD_ERRO_16,
			   status, TABELA_CNF_REL_GRAF );
	  NoticeScoreph( NULL, ScoreGetStr(NOME_ERRO), erro );
	  exit(0);
	}
  }
  AlocaSemaf( SEMAF_CNFRELGRAF );
  memcpy( (void *)&gCnfAla, (const void *)&CNF_ALA, sizeof( t_cnf_alarme ) );
  LiberaSemaf( SEMAF_CNFRELGRAF );
  if( LeTabelas() )
    exit(0);
  gGrupo = 0;
  gPos = 0;
  return( Pt_CONTINUE );
}
