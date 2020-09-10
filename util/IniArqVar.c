/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: SCORE - CONTROLE DE REDUCOES

	SISTEMA		: TODOS

	ARQUIVO		: IniArqVar.c

	CONTEUDO	: Esse programa gera o arquivo de variaveis do sistema

	AUTOR		: Alexandre Bandeira

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0		  -		  DATA  : 05/02/96

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
03/01/2001 | Inclusao de tabelas para o Atn8                    | Leonel
-------------------------------------------------------------------------------
30/01/2002 | Inclusao tratamento do tipo T_DATA_HORA            | Leonel
-------------------------------------------------------------------------------
******************************************************************************/
/*********************************** Revisoes ********************************\
$Id: IniArqVar.c,v 1.7.4.1 2015/03/03 17:03:14 leo Exp $

$Log: IniArqVar.c,v $
Revision 1.7.4.1  2015/03/03 17:03:14  leo
Inclusao do XMLScore para comunicacao via OPC.

Revision 1.7  2005/10/14 13:24:21  leo
Retirada teste para Paraibuna.

Revision 1.6  2005/10/06 18:56:42  alex
corrigido bug nas tabelas do usuario

Revision 1.5.2.2  2005/10/06 12:52:08  alex
correcao quando tem espacos vazios entre tabelas

Revision 1.5.2.1  2005/09/05 12:54:26  alex
modificacoes iniciais

Revision 1.5  2005/07/26 18:04:41  alex
colocado numero de variaveis por tabela e total

Revision 1.4  2005/03/18 14:58:33  leo
Compatibilizacao com alteracoes do branch producao Albras

Revision 1.3.4.1  2004/10/18 19:42:21  leo
Adaptacao para projeto Albras usando Score Photon

Revision 1.3  2003/02/20 13:33:32  alex
Mudanca do path real para path relativo

Revision 1.2  2003/02/20 12:38:04  alex
Trocado path real do arqvar.dat para relativo

\*********************************** Revisoes ********************************/

/*
--------------------------------------------------------------------------------
								Includes
--------------------------------------------------------------------------------
*/
#define PROGRAMA_PRINCIPAL

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <process.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/name.h>
#include <sys/mman.h>
#include <sys/kernel.h>
#include <sys/vc.h>
#include <RelGraf.h>
#include <DescrArqVar.h>
#include <VarsComum.h>
#include <Prototipos.h>
#include <BdScore.h>
#include <ScoreMsgs.h>

/*
--------------------------------------------------------------------------------
								Defines
--------------------------------------------------------------------------------
*/

/*
--------------------------------------------------------------------------------
								Prototypes
--------------------------------------------------------------------------------
*/
int MontaStructArq( void );
char *Trim( char *str );
int compare( char *p1, char *p2 );
void PegaTamPrec( int tabela, int IndVar );
int MontaDados( int tabela, int tabscore, void *P, t_par_var_log *Var, int size );

/*
--------------------------------------------------------------------------------
							Variaveis Globais
--------------------------------------------------------------------------------
*/

char *AlgScore[] = {
/* 01 */ "Score",
#ifdef KONIN
/* 02 */ "",
/* 03 */ "",
///* 02 */ "Feeding",
#else
 #ifdef	CBA_120KAII_III
/* 02 */ "Aliment",
/* 03 */ "Barra",
 #else
/* 02 */ "",
/* 03 */ "",
 #endif
#endif
/* 04 */ "",
/* 05 */ ""
};

t_arqvar  Arq;
t_arqvar  Arq1;
t_lim_log Lim[MAX_VARIAVEIS];

/*
--------------------------------------------------------------------------------
							Programa Principal
--------------------------------------------------------------------------------
*/
void main(void)
{
  FILE		*fp, *fp1;
  char		buffer[100];
  size_t	tam;
  int		i, total;

  memset( &Arq,  0x00, TAM_ARQVAR );
  memset( &Arq1, 0x00, TAM_ARQVAR );

  printf( "\nMONTANDO BASE DE DADOS...\n" );

  for( i = 0; i < 5; ++i ) /* monta algoritmos score */
  {
    if( AlgScore[i][0] ne 0x00 )
	{
	  strncpy( &Arq.NomeAlgCtr[i][0], AlgScore[i],
			   min( 8, strlen(AlgScore[i]) ) );
	  strncpy( &Arq1.NomeAlgCtr[i][0], AlgScore[i],
			   min( 8, strlen(AlgScore[i]) ) );
      printf( "\nMONTANDO Algoritmo Score[%d]: %s ...", i+1, &Arq.NomeAlgCtr[i][0] );
	}
  }
  for( i = 0; i < 5; ++i ) /* monta algoritmos usuario */
  {
    if( NAlgCtr[i].Algoritmo[0] ne 0x00 )
	{
	  strncpy( &Arq.NomeAlgCtr[i+8][0], NAlgCtr[i].Algoritmo,
			   min( 8, strlen(NAlgCtr[i].Algoritmo) ) );
	  strncpy( &Arq1.NomeAlgCtr[i+8][0], NAlgCtr[i].Algoritmo,
			   min( 8, strlen(NAlgCtr[i].Algoritmo) ) );
      printf( "\nMONTANDO Algoritmo Usuario[%d]: %s ...", i+9, &Arq.NomeAlgCtr[i+8][0] );
	}
  }
  printf( "\n" );
  for( i = 0; i < 16; ++i ) /* monta tabelas score */
  {
    if( NTabelas[i].Nome[0] ne 0x00 )
	{
	  strncpy( &Arq.NomeTabelas[i][0], NTabelas[i].Nome,
			   min( 18, strlen(NTabelas[i].Nome) ) );
	  strncpy( &Arq1.NomeTabelas[i][0], NTabelas[i].Nome,
			   min( 18, strlen(NTabelas[i].Nome) ) );
      printf( "\nMONTANDO Grupos Tabela[%d]: %s ...", i, &Arq.NomeTabelas[i][0] );
	}
  }
  printf( "\n" );
 
  total=MontaStructArq();

  Arq.f_novo = VERDADEIRO;
  Arq1.f_novo = VERDADEIRO;
  
  fp = fopen( LOCAL_NOME_ARQUIVO, "r" );
  if( fp ne NULL )
  {
    fclose( fp );
    sprintf( buffer, "rm %s", LOCAL_NOME_ARQUIVO );
    system( buffer );
  }
  else
    fclose( fp );
  fp = fopen( LOCAL_NOME_ARQUIVO, "w" );
  if( fp eq NULL )
  {
    printf( "\nNAO CONSEGUI ABRIR ARQUIVO %s\n", LOCAL_NOME_ARQUIVO );
    exit( -1 );
  }
  tam = fwrite( &Arq, (size_t)TAM_ARQVAR, 1, fp );
  if( tam ne 1 )
  {
    printf( "\nERRO GRAVACAO ARQUIVO %s\n", LOCAL_NOME_ARQUIVO );
    exit( -2 );
  }
  fclose( fp );
  printf( "\nARQUIVO %s FOI CRIADO COM %d BYTES %d VARIAVEIS(ORDENADO)", LOCAL_NOME_ARQUIVO, TAM_ARQVAR, total );

  fp1 = fopen( LOCAL_NOME_ARQUIVO1, "r" );
  if( fp1 ne NULL )
  {
    fclose( fp1 );
    sprintf( buffer, "rm %s", LOCAL_NOME_ARQUIVO1 );
    system( buffer );
  }
  else
    fclose( fp1 );
  fp1 = fopen( LOCAL_NOME_ARQUIVO1, "w" );
  if( fp1 eq NULL )
  {
    printf( "\nNAO CONSEGUI ABRIR ARQUIVO %s\n", LOCAL_NOME_ARQUIVO1 );
    exit( -3 );
  }
  tam = fwrite( &Arq1, (size_t)TAM_ARQVAR, 1, fp1 );
  if( tam ne 1 )
  {
    printf( "\nERRO GRAVACAO ARQUIVO %s\n", LOCAL_NOME_ARQUIVO1 );
    exit( -4 );
  }
  fclose( fp1 );
  printf( "\nARQUIVO %s FOI CRIADO COM %d BYTES %d VARIAVEIS(NAO ORDENADO)\n", LOCAL_NOME_ARQUIVO1, TAM_ARQVAR, total );
  exit( 0 );
}

int MontaStructArq()
{
  int		i;
  int		IndLim;
  int		tabela;
  int		indice;
  int		totalvar;
  size_t	tam;
  char		NomeArquivo[80];
  FILE		*fp;

  totalvar = 0;
  for( tabela = 0; tabela < MAX_TABELAS; ++tabela )
  {
    printf( "\nMONTANDO TABELA %-20s ", NomeTabelas[tabela] );
    switch( tabela )
    {
      case TAB_PARAM_AVC:
        totalvar+=MontaDados( tabela, TABELA_AVC_PARAM, &VarParamAvc,
					&VarParAvc, sizeof( t_param_avc ) );
	  break;
      case TAB_CLEIT_AVC:
        totalvar+=MontaDados( tabela, TABELA_AVC_CLEIT, &VarCLeitAvc,
					&VarCleitAvc, sizeof( t_cicleit_avc ) );
	  break;
      case TAB_CCONT_MCP_AVC:
        totalvar+=MontaDados( tabela, TABELA_AVC_CCONT_MCP, &VarCcontMcp,
					&VarCcontMcpAvc, sizeof( t_ccont_mcp_avc ) );
	  break;
      case TAB_CCONT_AVC:
        totalvar+=MontaDados( tabela, TABELA_AVC_CCONT, &VarCContAvc,
					&VarCcontAvc, sizeof( t_ciccont_avc ) );
	  break;
      case TAB_EA_AVC:
        totalvar+=MontaDados( tabela, TABELA_AVC_EA, &VarEAAvc,
					&VarEaAvc, sizeof( t_ea_avc ) );
	  break;
      case TAB_RUIDO_AVC:
        totalvar+=MontaDados( tabela, TABELA_AVC_RUIDO, &VarRuiAvc,
					&VarRuidoAvc, sizeof( t_ruido_avc ) );
	  break;
      case TAB_SUP_AVC:
        totalvar+=MontaDados( tabela, TABELA_SUPERV_AVC, &VarSuperv,
					&VarSupAvc, sizeof( t_avc_supervisao ) );
	  break;
      case TAB_EST_DISC_AVC:
        totalvar+=MontaDados( tabela, TABELA_EST_AVC, &VarEst,
					&VarEstDiscAvc, sizeof( t_est_avc ) );
	  break;
      case TAB_CONT_AVL:
        totalvar+=MontaDados( tabela, TABELA_AVL, &VarAvl,
					&VarContAvl, sizeof( t_avl ) );
	  break;
      case TAB_PAR_USER1:
        totalvar+=MontaDados( tabela, TABELA_AVC_PAR_USER1, &VarPar1,
					&VarParUser1, sizeof( t_par1_user ) );
	  break;
      case TAB_PAR_USER2:
        totalvar+=MontaDados( tabela, TABELA_AVC_PAR_USER2, &VarPar2,
					&VarParUser2, sizeof( t_par2_user ) );
	  break;
      case TAB_USER1_AVC:
        totalvar+=MontaDados( tabela, TABELA_AVC_USER1, &VarUser1,
					&VarUser1Avc, sizeof( t_user1_avc ) );
	  break;
      case TAB_USER2_AVC:
        totalvar+=MontaDados( tabela, TABELA_AVC_USER2, &VarUser2,
					&VarUser2Avc, sizeof( t_user2_avc ) );
	  break;
      case TAB_USER3_AVC:
        totalvar+=MontaDados( tabela, TABELA_AVC_USER3, &VarUser3,
					&VarUser3Avc, sizeof( t_user3_avc ) );
	  break;
      case TAB_USER4_AVC:
        totalvar+=MontaDados( tabela, TABELA_AVC_USER4, &VarUser4,
					&VarUser4Avc, sizeof( t_user4_avc ) );
	  break;
      case TAB_CONV_MUX:
        totalvar+=MontaDados( tabela, TABELA_CONV_MUX, &VarConvMUX,
					&VarConverMUX, sizeof( t_conv_mux ) );
	  break;
      case TAB_CONV_NMUX:
        totalvar+=MontaDados( tabela, TABELA_CONV_NMUX, &VarConvNMUX,
					&VarConverNMUX, sizeof( t_conv_nmux ) );
	  break;
      case TAB_ENT_ESP:
        totalvar+=MontaDados( tabela, TABELA_ENT_ESP, &VarEntESP,
					&VarEntradaESP, sizeof( t_conv_esp ) );
	  break;
#ifdef	CBA_120KAII_III
/* -- alteracao - inicio - 03/01/2001 - Leonel - Inclusao tabelas p/ Atn8 -- */
      case TAB_CONV_CUBA_ATN8:
        totalvar+=MontaDados( tabela, TABELA_CONV_CUBA_ATN8, &VarConvAtn8, &VarConverAtn8, sizeof(t_conv_cuba_atn8) );
	  break;
      case TAB_CONV_ESP_ATN8:
        totalvar+=MontaDados( tabela, TABELA_CONV_ESP_ATN8, &VarConvEspAtn8, &VarConverEspAtn8, sizeof(t_conv_esp_atn8) );
	  break;
/* -- alteracao - fim - 03/01/2001 - Leonel - Inclusao tabelas p/ Atn8 -- */
#endif
    }
  }
  printf( "\n" );
  for( i = 0; i < 16; ++i ) /* maximo de tabelas (grupos) */
  {
    if( NTabelas[i].Nome[0] ne 0x00 ) /* tabela valida */
	{
	  IndLim = 0;
	  memset( &Lim[0], 0x00, TAM_LIM_LOG_TOT );
	  for( tabela = 0; tabela < MAX_TABELAS; ++tabela )
	  {
	  	for( indice = 0; indice < MAX_VARIAVEIS; ++indice )
	  	{
		  if( Arq.Tabela[tabela].Var[indice].GrupoVar eq i )
		  {
		  	if( ( ( Arq.Tabela[tabela].Var[indice].TipoProg andb T4 ) eq 0 ) and
			  	( ( Arq.Tabela[tabela].Var[indice].TipoProg andb T6 ) ne 0 ) )
			{
			  strcpy( Lim[IndLim].NomeVar, Arq.Tabela[tabela].Var[indice].NomeVar );
			  strcpy( Lim[IndLim].UEvar,   Arq.Tabela[tabela].Var[indice].UEvar );
			  strcpy( Lim[IndLim].FmtVar,  Arq.Tabela[tabela].Var[indice].FmtVar );
			  Lim[IndLim].NivelSenha = Arq.Tabela[tabela].Var[indice].NivelSenha;
			  Lim[IndLim].PrecVar    = Arq.Tabela[tabela].Var[indice].PrecVar;
			  Lim[IndLim].LimInf     = Arq.Tabela[tabela].Var[indice].LimInf;
			  Lim[IndLim].LimSup     = Arq.Tabela[tabela].Var[indice].LimSup;
			  Lim[IndLim].FatConv    = Arq.Tabela[tabela].Var[indice].FatConv;
			  ++IndLim;
			  if( IndLim eq ( MAX_VARIAVEIS - 1 ) ) /* chegou no limite do arquivo */
			  {
				printf( "\n\033<ATENCAO: ARQUIVO %-20s CHEGOU EM %d VARIAVEIS!\033>\n", ArqLimTabela[i], IndLim );
				printf( "\n\033<ATENCAO: VARIAVEL %s FOI A ULTIMA INCLUIDA!\033>\n", Lim[IndLim-1].NomeVar);
				tabela = MAX_TABELAS;
				break;
			  }
			}
		  }
		}
	  }
	  qsort( &Lim[0].NomeVar[0],
	         IndLim,
    	     TAM_LIM_LOG_REG,
        	 compare );
	  sprintf( NomeArquivo, LOCAL_PATH_LIMITES, ArqLimTabela[i] );
	  fp = fopen( NomeArquivo, "r" );
	  if( fp ne NULL )
	  {
		printf( "\nArquivo %-20s ja' existe...Ok", ArqLimTabela[i] );
		fclose( fp );
		continue;
	  }
	  else
		fclose( fp );
	  fp = fopen( NomeArquivo, "w" );
	  if( fp eq NULL )
	  {
		printf( "\nNAO CONSEGUI ABRIR ARQUIVO %s\n", ArqLimTabela[i] );
		exit( -8 );
	  }
	  tam = fwrite( &Lim[0], (size_t)TAM_LIM_LOG_TOT, 1, fp );
	  if( tam ne 1 )
	  {
		printf( "\nERRO GRAVACAO ARQUIVO %s\n", ArqLimTabela[i] );
		exit( -9 );
	  }
	  fclose( fp );
	  printf( "\nArquivo %-30s nao existe, criando...Ok", ArqLimTabela[i] );
	}
//	else
//	  break; /* acabou tabelas validas */
  }
  printf( "\n" );
  return(totalvar);
}

void PegaTamPrec( tabela, IndVar )
{
  char fmt[50];
  char *p;
  int  aux;

  if( ( Arq.Tabela[tabela].Var[IndVar].TipoProg andb T4 ) ne 0 )
  {
    Arq.Tabela[tabela].Var[IndVar].TamVar = 0;
    Arq.Tabela[tabela].Var[IndVar].PrecVar = 0;
	return;
  }
  if( Arq.Tabela[tabela].Var[IndVar].TipoVar ne STRING and
      Arq.Tabela[tabela].Var[IndVar].TipoVar ne T_HORA and
      Arq.Tabela[tabela].Var[IndVar].TipoVar ne T_DATA_HORA and
      Arq.Tabela[tabela].Var[IndVar].TipoVar ne MASC_BITS16 )
  {
    strcpy( fmt, &Arq.Tabela[tabela].Var[IndVar].FmtVar[1] );
    p = strtok( fmt, "." );
    if( p ne NULL )
    {
      aux = atoi( p );
      if( aux < 0 )
        aux = aux * (-1);
      Arq.Tabela[tabela].Var[IndVar].TamVar = (char)aux;
      p = strtok( NULL, "f" );
      if( p ne NULL )
      {
        aux = atoi( p );
        Arq.Tabela[tabela].Var[IndVar].PrecVar = (char)aux;
      }
      else
      {
        Arq.Tabela[tabela].Var[IndVar].TamVar = 0;
        Arq.Tabela[tabela].Var[IndVar].PrecVar = 0;
        printf( "Variavel: %s nao tem formato ou esta invalido...\n", Arq.Tabela[tabela].Var[IndVar].NomeVar );
      }
    }
    else
    {
      Arq.Tabela[tabela].Var[IndVar].TamVar = 0;
      Arq.Tabela[tabela].Var[IndVar].PrecVar = 0;
      printf( "Variavel: %s nao tem formato ou esta invalido...\n", Arq.Tabela[tabela].Var[IndVar].NomeVar );
    }
  }
  else
  {
    strcpy( fmt, &Arq.Tabela[tabela].Var[IndVar].FmtVar[1] );
    p = strtok( fmt, "s" );
    if( p ne NULL )
    {
      aux = atoi( p );
      if( aux < 0 )
        aux = aux * (-1);
      Arq.Tabela[tabela].Var[IndVar].TamVar = (char)aux;
      Arq.Tabela[tabela].Var[IndVar].PrecVar = 0;
    }
    else
    {
      Arq.Tabela[tabela].Var[IndVar].TamVar = 0;
      Arq.Tabela[tabela].Var[IndVar].PrecVar = 0;
      printf( "Variavel: %s nao tem formato ou esta invalido...\n", Arq.Tabela[tabela].Var[IndVar].NomeVar );
    }
  }
  /* garante tamanho maximo de campo variavel */
  if( Arq.Tabela[tabela].Var[IndVar].TamVar > 10 )
    Arq.Tabela[tabela].Var[IndVar].TamVar = 10;
}

/**********************************************************\
 *                                                        *
 *  Function to trim leading and trailing blanks          *
**                                                        *
\**********************************************************/
#include <string.h>

char *Trim( char *str )
{
  int len;
  int ok;
  int sub;

  if( 0 == (len = strlen(str)) )
	return(str);
  ok = 1;
  while(ok)
  {
	if(*str == 0x20)
	{
	  memcpy(str, str+1, len);
	  len--;
	}
	else
	  ok--;
  }
  if(len > 0)
  for(sub = len-1; sub >= 0; --sub)
  {
	if( *(str+sub) == 0x20 )
	  *(str+sub) = 0x00;
	else
	  sub=0;
  }
  return (str);
}

int compare( char *p1, char *p2 )
{
  return( strcmp( p1, p2 ) );
}

int MontaDados( int tabela, int tabscore, void *P, t_par_var_log *Var, int size )
{
  int  IndVar, IndAux;
  int  Offset;
  int  tab;
  int  tam;

  IndVar = 0;

  Arq.Tabela[tabela].Tab = tabscore;
  while( (Var+IndVar)->NomeVar ne NULL )
  {
    if( IndVar eq (MAX_VARIAVEIS-1) )
    {
      printf( "\nEstouro do numero de variaveis da tabela !\n" );
      exit( -5 );
    }
	if( ( (Var+IndVar)->EndrVar eq NULL ) and
	    ( ( (Var+IndVar)->TipoProg andb T4 ) eq 0 ) )
    {
      printf( "\nAtencao: Var: %s Endereco: NULL, mas Variavel nao e' titulo !\n",
	          (Var+IndVar)->NomeVar );
      exit( -5 );
    }
	if( ( (int)(Var+IndVar)->TipoVar < SHORT_INT ) or
	    ( (int)(Var+IndVar)->TipoVar > T_DATA_HORA ) )
    {
      printf( "\nAtencao: Var: %s Tipo: %d Invalido !\n",
	          (Var+IndVar)->NomeVar, (int)(Var+IndVar)->TipoVar );
      exit( -5 );
    }
	tam = sizeof( Arq.Tabela[tabela].Var[IndVar].NomeVar );
	memset( Arq.Tabela[tabela].Var[IndVar].NomeVar, 0x00, tam );
	strncpy( Arq.Tabela[tabela].Var[IndVar].NomeVar,
			 (Var+IndVar)->NomeVar,
			 minimo( tam-1, strlen( (Var+IndVar)->NomeVar ) ) );
    
    Arq.Tabela[tabela].Var[IndVar].TipoProg = (Var+IndVar)->TipoProg;
    if( ( Arq.Tabela[tabela].Var[IndVar].TipoProg andb T4 ) eq 0 )
    { 
      for( tab = 0; tab <= tabela; ++tab )
      {
        IndAux = 0;
        if( tab eq tabela )
        {
          while( IndAux < IndVar )
          {
            if( ( Arq.Tabela[tab].Var[IndAux].TipoProg andb T4 ) eq 0 )
            {
              if( strcmp( Arq.Tabela[tabela].Var[IndVar].NomeVar,
                          Arq.Tabela[tab].Var[IndAux].NomeVar ) eq 0 )
              {
                printf( "\nERRO: %s[%s] ja' existe em [%s]\n",
                        Arq.Tabela[tabela].Var[IndVar].NomeVar,
                        NomeTabelas[tabela], NomeTabelas[tab] );
                exit( -6 );             
              }
            }
            ++IndAux;
          }
        }
        else
        {
          while( Arq.Tabela[tab].Var[IndAux].NomeVar[0] ne 0x00 )
          {
            if( ( Arq.Tabela[tab].Var[IndAux].TipoProg andb T4 ) eq 0 )
            {
              if( strcmp( Arq.Tabela[tabela].Var[IndVar].NomeVar,
                          Arq.Tabela[tab].Var[IndAux].NomeVar ) eq 0 )
              {
                printf( "\nERRO: %s[%s] ja' existe em [%s]\n",
                        Arq.Tabela[tabela].Var[IndVar].NomeVar,
                        NomeTabelas[tabela], NomeTabelas[tab] );
                exit( -7 );             
              }
            }
            ++IndAux;
          }
        }
      }
    }
	tam = sizeof( Arq.Tabela[tabela].Var[IndVar].UEvar );
	memset( Arq.Tabela[tabela].Var[IndVar].UEvar, 0x00, tam );
	strncpy( Arq.Tabela[tabela].Var[IndVar].UEvar,
             (Var+IndVar)->UEvar,
			 minimo( tam-1, strlen( (Var+IndVar)->UEvar ) ) );
	if( ( (Var+IndVar)->TipoProg andb T4 ) eq 0 )
	{
	  /* critica se endereco pertence realmente a tabela */
	  if( (char *)(Var+IndVar)->EndrVar >= (char *)P and
		  (char *)(Var+IndVar)->EndrVar < ((char *)P+size) )
	  {
	    Offset = CalcByteOffset( P, (Var+IndVar)->EndrVar );
	    Arq.Tabela[tabela].Var[IndVar].OffVar = Offset;
	  }
	  else
	  {
        printf( "\n\nERRO: %s nao pertence a tabela [%s]\n\n",
                Arq.Tabela[tabela].Var[IndVar].NomeVar,
                NomeTabelas[tabela] );
        exit( -8 );             
	  }
	}
	else  
	  Arq.Tabela[tabela].Var[IndVar].OffVar = 0;
	Arq.Tabela[tabela].Var[IndVar].NivelSenha = (Var+IndVar)->NivelSenha;
	Arq.Tabela[tabela].Var[IndVar].TipoVar    = (Var+IndVar)->TipoVar;
	/* forca so para programas de configuracao */
	if( Arq.Tabela[tabela].Var[IndVar].TipoVar eq STRING or
	    Arq.Tabela[tabela].Var[IndVar].TipoVar eq T_HORA or
	    Arq.Tabela[tabela].Var[IndVar].TipoVar eq MASC_BITS16 )
#ifdef	ALBRAS
      Arq.Tabela[tabela].Var[IndVar].TipoProg =
	              Arq.Tabela[tabela].Var[IndVar].TipoProg andb
				  ( T3 orb T4 orb T5 orb T7 orb T8 );
	/* -- Alteracao - inicio - 30/01/2002 - Leonel - Alteracao tratamento de data e hora -- */
	if( Arq.Tabela[tabela].Var[IndVar].TipoVar eq T_DATA_HORA )
      Arq.Tabela[tabela].Var[IndVar].TipoProg =
	              Arq.Tabela[tabela].Var[IndVar].TipoProg andb (T12 orb OPC_RW);	// apenas importacao e OPC
	/* -- Alteracao - fim - 30/01/2002 - Leonel - Alteracao tratamento de data e hora -- */
#else
      Arq.Tabela[tabela].Var[IndVar].TipoProg =
	              Arq.Tabela[tabela].Var[IndVar].TipoProg andb
				  ( T3 orb T4 orb T5 orb T7 orb T8 orb T13 );
	if( Arq.Tabela[tabela].Var[IndVar].TipoVar eq T_DATA_HORA )
      Arq.Tabela[tabela].Var[IndVar].TipoProg =
	              Arq.Tabela[tabela].Var[IndVar].TipoProg andb OPC_RW;	// apenas OPC
#endif
	tam = sizeof( Arq.Tabela[tabela].Var[IndVar].FmtVar );
	memset( Arq.Tabela[tabela].Var[IndVar].FmtVar, 0x00, tam );
	strncpy( Arq.Tabela[tabela].Var[IndVar].FmtVar,
			(Var+IndVar)->FmtVar,
			 minimo( tam-1, strlen( (Var+IndVar)->FmtVar ) ) );
	Arq.Tabela[tabela].Var[IndVar].LimInf  = (Var+IndVar)->LimInf;
	Arq.Tabela[tabela].Var[IndVar].LimSup  = (Var+IndVar)->LimSup;
	Arq.Tabela[tabela].Var[IndVar].FatConv = (Var+IndVar)->FatConv;
	Arq.Tabela[tabela].Var[IndVar].FlagAlg = (Var+IndVar)->FlagAlg;
	tam = sizeof( Arq.Tabela[tabela].Var[IndVar].Rotulo );
	memset( Arq.Tabela[tabela].Var[IndVar].Rotulo, 0x00, tam );
	strncpy( Arq.Tabela[tabela].Var[IndVar].Rotulo,
			(Var+IndVar)->Rotulo,
			 minimo( tam-1, strlen( (Var+IndVar)->Rotulo ) ) );
	tam = sizeof( Arq.Tabela[tabela].Var[IndVar].Tag );
	memset( Arq.Tabela[tabela].Var[IndVar].Tag, 0x00, tam );
	strncpy( Arq.Tabela[tabela].Var[IndVar].Tag,
			(Var+IndVar)->Tag,
			 minimo( tam-1, strlen( (Var+IndVar)->Tag ) ) );
	Arq.Tabela[tabela].Var[IndVar].GrupoVar = (Var+IndVar)->GrupoVar;
	PegaTamPrec( tabela, IndVar );
	++IndVar;
  }
  memcpy( &Arq1.Tabela[tabela].Var[0].NomeVar[0],
          &Arq.Tabela[tabela].Var[0].NomeVar[0],
          sizeof( Arq.Tabela[0] ) );
  qsort( &Arq.Tabela[tabela].Var[0].NomeVar[0],
         IndVar,
         sizeof( t_variavel ),
         compare );
  printf( "Indice %2d TabScore %3d NumVars %3d", tabela, Arq.Tabela[tabela].Tab, IndVar );
  return(IndVar);
}
