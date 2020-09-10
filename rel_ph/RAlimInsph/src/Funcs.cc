//****************************************************************************
//
//			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
//	   SCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 1.0
//
//	PROJECT		: ALL
//
//	SYSTEM		: ALL
//
//	FILE		: Funcs.cc
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
/*********************************** Revisoes ********************************\
$Id: Funcs.cc,v 1.2 2003/08/06 13:47:50 alex Exp $

$Log: Funcs.cc,v $
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
#include "abimport.h"
#include "proto.h"

//-------------------------------------------------------------------------------------------------
//
// ExibeTela
//
//-------------------------------------------------------------------------------------------------
void ExibeTela( t_widgets & aWidgets, short int aGrupo, short int & aPos )
{
  short int	linha, aux;
  if( Comum->NumCubasGrupo[aGrupo] > MAX_LIN_REL_ALIM )
    aux = MAX_LIN_REL_ALIM;
  else
    aux = Comum->NumCubasGrupo[aGrupo];	
  if( (aPos + aux) > Comum->NumCubasGrupo[aGrupo] )
    aPos = (short int)(Comum->NumCubasGrupo[aGrupo] - aux);
  for( linha = 0; linha < aux; ++linha )
  {
    PtSetStringValue( aWidgets.linha[linha], aWidgets.rel[aPos+linha].linha );
    PtSetColorValue( aWidgets.linha[linha], Pt_ARG_FILL_COLOR, aWidgets.rel[aPos+linha].cor );
	PtRealizeWidget( aWidgets.linha[linha] );
  }
  for( linha = linha; linha < MAX_LIN_REL_ALIM; ++linha )
	PtUnrealizeWidget( aWidgets.linha[linha] );
}


//-------------------------------------------------------------------------------------------------
//
// MontaTela
//
//-------------------------------------------------------------------------------------------------
void MontaTela( t_widgets & aWidgets, t_alarmePH *apAlarme, t_cnf_alarme & aCnfAla, short int aGrupo )
{
  short int	linha, cuba;

  for( linha = 0; linha < Comum->NumCubasGrupo[aGrupo]; ++linha )
  {
	for( cuba = 0; cuba < AVL.NumCubas; ++cuba )
	{
	  if( AVC.Abs[cuba].GrupoCuba == aGrupo && AVC.Abs[cuba].PosGrupoCuba == linha )
	    break;
	}
	if( cuba != AVL.NumCubas )
	{
      MontaLinha( aWidgets, linha, cuba );
	  TrataAlarmeIns( aWidgets, apAlarme, aCnfAla, linha, cuba );
	}
	else
	  sprintf( aWidgets.rel[linha].linha, "POSICAO: %d -> CUBA NAO ENCONTRADA !", linha );
  }
}

//-------------------------------------------------------------------------------------------------
//
// MontaLinha
//
//-------------------------------------------------------------------------------------------------
void MontaLinha( t_widgets & aWidgets, short int aLinha, short int aIndCuba )
{
  long HoraAtual;
  long DurSubEst;
  size_t	car;

  HoraAtual = time(NULL);
  DurSubEst = HoraAtual - AVC.User1[aIndCuba].HoraIniSubEstAtual;

  //aproveita variavel local para calcular tempo no algoritmo atual
  HoraAtual= AVC.User1[aIndCuba].TempEstAtual/((long) (SAD_TICKS / Comum->BaseTempoMcp));


  if ((EST_AVC(aIndCuba).EstadoCuba eq CUBA_NORMAL) and
      (AVC.Param[aIndCuba].TemPF eq TEM_PF) and
      (AVC.ParUser1[aIndCuba].HabilitaPF eq VERDADEIRO) 
//      (AlgControleGlobal(aIndCuba, ALG_SCORE02)))
 		)
  {	  
	/* -- Alteracao - Inicio - Robson - 07/08/2002 -- */
    car=strlenMB(NomeModoAlim(AVC.User1[aIndCuba].EstadoAlimAtual, aIndCuba),8);
	/* -- Alteracao - Fim - Robson - 07/08/2002 -- */
	sprintf( aWidgets.rel[aLinha].linha, "%4d  %-8.8s %-8.8s %-*.*s %02d:%02d %6.1f   %02d  %02d:%02d %5.1f %5.1f %5.2f",
		   ConvCubScoreOper(aIndCuba), 
		   SinalSituacao(aIndCuba),
		   SinalSituacaoAlim(aIndCuba),
		   car, car,
		   NomeModoAlim(AVC.User1[aIndCuba].EstadoAlimAtual, aIndCuba),
		   HoraAtual/3600,
		   (HoraAtual/60) Mod 60,
		   AVC.User1[aIndCuba].QtAAlimEstAtual,
		   AVC.User1[aIndCuba].State,
		   DurSubEst/3600,
		   (DurSubEst/60) Mod 60,
		   AVC.User1[aIndCuba].FornecSubEst,
		   AVC.User1[aIndCuba].FornecSubEst - AVC.User1[aIndCuba].ConsumoSubEst,
		   AVC.User1[aIndCuba].EfiCurr*100.0);
  }
  else
  {
	sprintf( aWidgets.rel[aLinha].linha, "%4d  %-8.8s %-8.8s %-8.8s %-5.5s  %-5.5s   %-2.2s  %-5.5s   %-3.3s %-5.5s %-5.5s",
		   ConvCubScoreOper(aIndCuba), 
		   SinalSituacao(aIndCuba),
		   STR_TRACO,
		   STR_TRACO,
		   STR_TRACO,
		   STR_TRACO,
		   STR_TRACO,
		   STR_TRACO,
		   STR_TRACO,
		   STR_TRACO,
		   STR_TRACO);
  }		   
}

//-------------------------------------------------------------------------------------------------
//
// TrataAlarmeIns
//
//-------------------------------------------------------------------------------------------------
void TrataAlarmeIns( t_widgets & aWidgets, t_alarmePH *apAlarme, t_cnf_alarme & aCnfAla,
					 short int aLinha, short int aIndCuba )
{	
  PgColor_t	color1, color2;
  if( (apAlarme+aIndCuba)->EstadoAtual[0] != NORMAL )
  {
  	color1 = aWidgets.rel[aLinha].cor;
	color2 = aCnfAla.CorFaixasAlarmeC[(apAlarme+aIndCuba)->EstadoAtual[0]];
  	if( color1 != color2 )
	{
//	  PtSetColorValue( widget, Pt_ARG_NUMERIC_TEXT_FILL_COLOR, color2 );
  	  aWidgets.rel[aLinha].cor = color2;
	}
  }
  else
  {
    if( aWidgets.rel[aLinha].cor != Pg_GRAY )
    {
//      PtSetColorValue( widget, Pt_ARG_NUMERIC_TEXT_FILL_COLOR, Pg_GRAY );
  	  aWidgets.rel[aLinha].cor = Pg_GRAY;
    }
  } 
}

//-------------------------------------------------------------------------------------------------
//
// SinalSituacaoAlim
//
//-------------------------------------------------------------------------------------------------
char  *SinalSituacaoAlim( short int aIndCuba )
{
  static char condicao[9];

  /*-- Sinaliza alimentacao em Manual-Local. --*/
  memset(condicao, 0x00,sizeof(condicao));
  strcpy(condicao,ScoreGetStr(SCORE_MSG_49));
  if (EST_AVC(aIndCuba).Est.ManualAlimLoc eq VERDADEIRO) 
  {
    memset(condicao, 0x00,sizeof(condicao));
	strcpy(condicao,ScoreGetStr(MAN_LOC));
  }
  else 
  {
	/*-- Sinaliza alimentacao em Manual-Remoto. --*/
	if (EST_AVC(aIndCuba).Est.ManualAlimRem eq VERDADEIRO)
	{
      memset(condicao, 0x00,sizeof(condicao));
  	  strcpy(condicao,ScoreGetStr(MAN_REM));
	} 
  }
  return( condicao );
} /*-- SinalSituacaoAlim --*/

//-------------------------------------------------------------------------------------------------
//
// SinalSituacao
//
//-------------------------------------------------------------------------------------------------
char* SinalSituacao ( int aIndCuba )
{
  static char cond[10];
  
  /*-- Sinaliza cuba em Manual-Local. --*/
  memset(cond,0x00,sizeof(cond));
  strcpy(cond,ESTADO_NUL);
  if ( EST_AVC(aIndCuba).ChaveLocRem eq LOCAL ) 
  {
	strcpy(cond,ScoreGetStr(MAN_LOC));
  } 
  else 
  {
	/*-- Sinaliza cuba em Manual-Remoto. --*/
	if ( EST_AVC(aIndCuba).ChaveAutMan eq MANUAL ) 
	{
	  if (EST_AVC(aIndCuba).ManualControle)
		strcpy(cond,ScoreGetStr(MAN_CTR));	/* Manual pelo controle */
	  else
		strcpy(cond,ScoreGetStr(MAN_REM));
	} 
	else 
	{
	  if ( EST_AVC(aIndCuba).EstadoCuba eq CUBA_NORMAL)
	  {
		/*-- Sinaliza cuba em Efeito Anodico. --*/
		if ( EST_AVC(aIndCuba).Ea eq VERDADEIRO ) 
		  strcpy(cond,ScoreGetStr(EA));
		else
		{
		  /*-- Sinaliza cuba em Corrida. --*/
		  if ( EST_AVC(aIndCuba).Corrida eq VERDADEIRO ) 
			strcpy(cond,ScoreGetStr(CORRIDA));
		  else
		  {
			/*-- Sinaliza cuba em Quebrada --*/
			if ( EST_AVC(aIndCuba).Quebrada eq VERDADEIRO ) 
			  strcpy(cond,ScoreGetStr(QUEBRADA));
		  }
		}
 	  }
	}
  }
  
  return(cond);
} /*-- SinalSituacao --*/

//-------------------------------------------------------------------------------------------------
//
// SetaLimitesScroll
//
//-------------------------------------------------------------------------------------------------
void SetaLimitesScroll( PtWidget_t *apWidget, short int aGrupo )
{
  PtArg_t	args[6];
  int		min;
  int		max;
  min = 0;
  max = Comum->NumCubasGrupo[aGrupo];
  PtSetArg( &args[0], Pt_ARG_MINIMUM, min, 0 );
  PtSetArg( &args[1], Pt_ARG_MAXIMUM, max-1, 0 );
  PtSetArg( &args[2], Pt_ARG_SLIDER_SIZE, MAX_LIN_REL_ALIM, 0 );
  PtSetArg( &args[3], Pt_ARG_MIN_SLIDER_SIZE, MAX_LIN_REL_ALIM, 0 );
  PtSetArg( &args[4], Pt_ARG_SCROLL_POSITION, 0, 0 );
  PtSetResources( apWidget, 5, args );
}

//-------------------------------------------------------------------------------------------------
//
// PegaWidgets
//
//-------------------------------------------------------------------------------------------------
void PegaWidgets( t_widgets & aWidgets )
{
  if( Comum->IHM[GetLoginPhindows()].TamIHM == 0 ) // 640x480
  {
    /* grupos de cuba */
    aWidgets.grupo[0] = ABW_PRINCIPAL_g1;
    aWidgets.grupo[1] = ABW_PRINCIPAL_g2;
    aWidgets.grupo[2] = ABW_PRINCIPAL_g3;
    aWidgets.grupo[3] = ABW_PRINCIPAL_g4;
    aWidgets.grupo[4] = ABW_PRINCIPAL_g5;
    aWidgets.grupo[5] = ABW_PRINCIPAL_g6;
    aWidgets.grupo[6] = ABW_PRINCIPAL_g7;
    aWidgets.grupo[7] = ABW_PRINCIPAL_g8;
    /* linhas do relatorio */
    aWidgets.linha[0] = ABW_PRINCIPAL_l1;
    aWidgets.linha[1] = ABW_PRINCIPAL_l2;
    aWidgets.linha[2] = ABW_PRINCIPAL_l3;
    aWidgets.linha[3] = ABW_PRINCIPAL_l4;
    aWidgets.linha[4] = ABW_PRINCIPAL_l5;
    aWidgets.linha[5] = ABW_PRINCIPAL_l6;
    aWidgets.linha[6] = ABW_PRINCIPAL_l7;
    aWidgets.linha[7] = ABW_PRINCIPAL_l8;
    aWidgets.linha[8] = ABW_PRINCIPAL_l9;
    aWidgets.linha[9] = ABW_PRINCIPAL_l10;
    aWidgets.linha[10] = ABW_PRINCIPAL_l11;
    aWidgets.linha[11] = ABW_PRINCIPAL_l12;
    aWidgets.linha[12] = ABW_PRINCIPAL_l13;
  }
  else // 1024x768
  {
    /* grupos de cuba */
    aWidgets.grupo[0] = ABW_PRINCIPAL_X_g1;
    aWidgets.grupo[1] = ABW_PRINCIPAL_X_g2;
    aWidgets.grupo[2] = ABW_PRINCIPAL_X_g3;
    aWidgets.grupo[3] = ABW_PRINCIPAL_X_g4;
    aWidgets.grupo[4] = ABW_PRINCIPAL_X_g5;
    aWidgets.grupo[5] = ABW_PRINCIPAL_X_g6;
    aWidgets.grupo[6] = ABW_PRINCIPAL_X_g7;
    aWidgets.grupo[7] = ABW_PRINCIPAL_X_g8;
    /* linhas do relatorio */
    aWidgets.linha[0] = ABW_PRINCIPAL_X_l1;
    aWidgets.linha[1] = ABW_PRINCIPAL_X_l2;
    aWidgets.linha[2] = ABW_PRINCIPAL_X_l3;
    aWidgets.linha[3] = ABW_PRINCIPAL_X_l4;
    aWidgets.linha[4] = ABW_PRINCIPAL_X_l5;
    aWidgets.linha[5] = ABW_PRINCIPAL_X_l6;
    aWidgets.linha[6] = ABW_PRINCIPAL_X_l7;
    aWidgets.linha[7] = ABW_PRINCIPAL_X_l8;
    aWidgets.linha[8] = ABW_PRINCIPAL_X_l9;
    aWidgets.linha[9] = ABW_PRINCIPAL_X_l10;
    aWidgets.linha[10] = ABW_PRINCIPAL_X_l11;
    aWidgets.linha[11] = ABW_PRINCIPAL_X_l12;
    aWidgets.linha[12] = ABW_PRINCIPAL_X_l13;
  }
}

//-------------------------------------------------------------------------------------------------
//
// LeTabelas
//
//-------------------------------------------------------------------------------------------------
int LeTabelas(void)
{
  int nodo_controle, status;
  char msg_erro[80];
  static int cont_outras_tab=1;

  nodo_controle=AVL.NodoNoControle;
  if (My_nid ne nodo_controle)
  { /* -- Estou rodando em outro nodo, entao leio tabelas do controle -- */
	/* -- Le tabela AVC.Cleit -- */
	if(SolicitaLeitura(SEMAF_READ_CLEIT,0))
	{
	  status = ScoreBd( nodo_controle,TABELA_AVC,BD_LER,(void *)&AVC.Cleit[0],
					  CalcByteOffset(&AVC,&AVC.Cleit[0]),
					  sizeof(t_cicleit_avc)*MAX_CUBAS );
	  if( status )						
	  {
        //Sinaliza falha na abertura da base de dados
	    sprintf( msg_erro, ScoreGetStr(SCORE_ERR_4), My_name, COD_ERRO_16,
			   status, TABELA_AVC);
	    NoticeScoreph( NULL, ScoreGetStr(NOME_ERRO), msg_erro );
	    return( VERDADEIRO );
	  }		
	}
	/* -- Tabelas que podem ser lidas em uma frequencia menor -- */
	if( cont_outras_tab <= 1 )
	{
	  cont_outras_tab=FREQ_TABS_PARAM;
	  /* -- Le tabela AVC.Param -- */
	  if(SolicitaLeitura(SEMAF_READ_PARAM,0))
	  {
	    status = ScoreBd( nodo_controle,TABELA_AVC,BD_LER,(void *)&AVC.Param[0],
						CalcByteOffset(&AVC,&AVC.Param[0]),
						sizeof(t_param_avc)*MAX_CUBAS );
	    if( status )						
	    {
          //Sinaliza falha na abertura da base de dados
  	      sprintf( msg_erro, ScoreGetStr(SCORE_ERR_4), My_name, COD_ERRO_16,
		  	     status, TABELA_AVC);
	      NoticeScoreph( NULL, ScoreGetStr(NOME_ERRO), msg_erro );
		  return( VERDADEIRO );
	    }
	  }	
	  /* -- Le tabela AVC.User1 -- */
	  if(SolicitaLeitura(SEMAF_READ_USER1,0))
	  {
	    status = ScoreBd( nodo_controle,TABELA_AVC,BD_LER,(void *)&AVC.User1[0],
						CalcByteOffset(&AVC,&AVC.User1[0]),
						sizeof(t_user1_avc)*MAX_CUBAS );
	    if( status )							
	    {
          //Sinaliza falha na abertura da base de dados
  	      sprintf(msg_erro, ScoreGetStr(SCORE_ERR_4), My_name, COD_ERRO_16,
		  	    status, TABELA_AVC);
	      NoticeScoreph( NULL, ScoreGetStr(NOME_ERRO), msg_erro );
		  return( VERDADEIRO );
		}  
	  }
	}
	else
	  cont_outras_tab--;
  }
  return( FALSO );
}

//-------------------------------------------------------------------------------------------------
//
// LeComum
//
//-------------------------------------------------------------------------------------------------
char *LeComum( char *apNome, size_t aTamanho )
{
  int  fd;
  char *p;
  char erro[80];

  fd = shm_open( apNome, O_RDWR, 0 );
  if( fd ne -1 )
  {
    p = (char *)mmap( 0, aTamanho, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );
    if( p eq (char *)-1 )
    {
      close( fd );
	  sprintf( erro, ScoreGetStr(SCORE_ERR_6), My_name, COD_ERRO_21, apNome, errno );
      NoticeScoreph( NULL, ScoreGetStr(NOME_ERRO), erro );
	  exit(0);
    }
  }
  else
  {
	sprintf( erro, ScoreGetStr(SCORE_ERR_6), My_name, COD_ERRO_20, apNome, errno );
    NoticeScoreph( NULL, ScoreGetStr(NOME_ERRO), erro );
    exit(0);
  }
  close( fd );
  return( p );
}

