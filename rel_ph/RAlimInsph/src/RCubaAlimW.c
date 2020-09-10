/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.40

	PROJETO		: TODOS

	SISTEMA		: TODOS

	ARQUIVO		: RCubaAlimW.c

	CONTEUDO	: Programa que processa e gera as informacoes que compoem
				  o relatorio instantaneo de Alimentacao.

	AUTOR		: Alexandre Mariz Bandeira de Morais.

	SISTEMA OPERACIONAL:  QNX 4.22A		-		COMPILADOR: WATCOM C - V9.52

	VERSAO		: 3.0		  -		  DATA  : 09/01/97

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
09/01/97 | Edicao Inicial										| A. Bandeira
-------------------------------------------------------------------------------
01/03/97 | Mudanca dos parametros a serem exibidos no relatorio | R. Mourao
         | instantaneo											|
-------------------------------------------------------------------------------
23/10/97 | Adequacao do relatorio ao esquema multi-linguas      | Ricardo
		 | (strings na base de dados) e adocao do esquema de    | Mourao
		 | exibicao das cubas por secao							|
******************************************************************************/

/* INDICA QUE ESTE E' O PROGRAMA PRINCIPAL */

#define	PROGRAMA_PRINCIPAL

/* INCLUSAO DE OUTROS ARQUIVOS */

#include <windows/Qwindows.h>
#include <string.h>
#include <RCubaAlimW.h>
#include <ScoreMsgs.h>
#include <ScoreErros.h>


/* -- PROTOTIPOS DAS FUNCOES INTERNAS -- */
char *LeComum( char *nome, size_t tamanho );
/* -- Alteracao - Inicio - Robson - 31/10/00 -- */
void MontaTela( int Grupo, byte Pagina );
void AtualTela( int Grupo, byte Pagina );
void TrataAlarmeIns( int indcuba, char *tag );
void MontaLinha( int cuba, int indcuba, char *buffer );
/* -- Alteracao - Fim - Robson - 31/10/00 -- */
char *SinalSituacaoAlim( int Cuba );
char *SinalSituacao( int Cuba );

/* -- VARIAVEIS GLOBAIS -- */
t_GrupoCuba          *GrupoCuba;
t_alarme			 *Cuba;
byte				 CorCuba[MAX_CUBAS];
byte				 PaginaAtual;

void main( void /*int argc, char *argv[]*/ )
{
  QW_EVENT_MSG		event;
  char          	temp[30];
  int           	pid_P, pid_W;
  bool          	exibe;
  int				id_getev;
  int				cuba, Grupo;
  pid_t				ProxyTempo;
  struct itimerspec	timer;
  timer_t			id;
  struct sigevent	event_timer;

  if( GraphicsOpen( NULL ) eq 0 )
	exit(-1);

  /* Pega area comum de memoria */
  if( PegaComum( &Comum ) )
  {
    //Sinaliza erro pega comum
    NoticeScore( NULL, ScoreGetStr(NOME_ERRO), NULL, "E", 
	             ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_0 );
	exit(-1);
  }

  /* Pega area comum RelGraf de memoria */
  if( PegaRelGraf() )
  {
    NoticeScore( NULL, ScoreGetStr(NOME_ERRO), NULL, "E",
				 ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_1 );
	exit(-1);
  }
  /* cria estrutura de grupos de cubas */
  GrupoCuba = (t_GrupoCuba *)LeComum( "ComumGrupoCuba",
               sizeof( t_GrupoCuba ) );
  /************************ TESTE ***********************
    sleep(30);
  ************************ TESTE ***********************/

  if( GrupoCuba eq NULL )
  {
	NoticeScore( NULL, ScoreGetStr(SCORE_MSG_0), NULL, "E",
				 ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_80 );
	exit(-1);
  }
  /* mapeia area de memoria */
  Cuba = (t_alarme *)LeComum( "ComumAlarmeCuba",
                     (size_t)(sizeof( t_alarme ) * MAX_CUBAS ) );
  if( Cuba eq NULL )
  {
	NoticeScore( NULL, ScoreGetStr(SCORE_MSG_0), NULL, "E",
				 ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_3 );
	exit(-1);
  }

  for( cuba = 0; cuba < AVL.NumCubas; ++cuba )
    CorCuba[cuba] = QW_BKGD2;

  /*--- Abre picture para exibicao do relatorio ---*/
  sprintf( temp, "%s.pict", MASC_REL_DINA );
  pid_P = PictureOpen( "MascRelP", temp, NULL, 0, 0, NULL, "RW" );
  if( pid_P eq 0 ) 
  {
    //Sinaliza erro na abertura da pict
    NoticeScore( NULL, ScoreGetStr(NOME_ERRO), NULL, "E", ScoreGetStr(SCORE_ERR_2),
				 My_name, COD_ERRO_14, MASC_REL_DINA );
	exit(-1);
  }

  ChangeText( "Titulo",ScoreGetStr(TIT_REL_INS_ALIM_PF), 0, 0, 0 );
  ChangeText( "Cabecalho1",ScoreGetStr(HD1_REL_INS_ALIM_PF), 0, 0, 0 );
  ChangeText( "Cabecalho2",ScoreGetStr(HD2_REL_INS_ALIM_PF), 0, 0, 0 );

  /*--- Abre window para exibicao do relatorio ---*/
  WindowAt( 300, 0, NULL, NULL ); /* posiciona window */
  sprintf( temp,"@%s.wnd&lfD-m",MASC_REL_DINA );
  pid_W = WindowOpen( "MascRelW", 0, 0, temp, NULL, NULL, pid_P );
  if( pid_W eq 0 ) 
  {
    //Sinaliza erro na abertura da window
    NoticeScore( NULL, ScoreGetStr(NOME_ERRO), NULL, "E",
			     ScoreGetStr(SCORE_ERR_2), My_name, COD_ERRO_15, MASC_REL_DINA );
	exit(-1);
  }
  WindowBarCurrent( 'T', NULL );
  for( Grupo = 0; Grupo < GrupoCuba->NumGrupos; ++Grupo )
  {
    sprintf( temp, "Grupo%d", Grupo );      
    ChangeText( temp, ScoreGetStr(SCORE_MSG_50+Grupo),
		        0, ScoreGetStrTam(SCORE_MSG_50+Grupo,NULL), 0 );
  }
  ChangeText( "Abandona", ScoreGetStr(SCORE_MSG_1892), 0, 9, 0 );
// Alterado por Leonel
/* -- Alteracao - Inicio - Robson - 24/10/00 -- */
  ChangeState( "Grupo0", 1 );
//  ChangeState( "Grupo1", 1 );
/* -- Alteracao - Fim - Robson - 24/10/00 -- */
  WindowBarCurrent( 0, NULL );

  /* -- Atraca no port de ativacao de tempo -- */
  if( ( ProxyTempo=qnx_proxy_attach(0, 0, 0, -1) ) eq -1 )
  {
    //Sinaliza erro em atracar na proxy de tempo
    NoticeScore( NULL, ScoreGetStr(NOME_ERRO), NULL, "E",
		         ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_11 );
	exit(-1);
  }
  /* -- Cria timer para ativar proxy de tempo -- */
  event_timer.sigev_signo = -ProxyTempo;
  id = timer_create( CLOCK_REALTIME, &event_timer );
  if (id eq -1)
  {
    //Falha na criacao do timer
    NoticeScore( NULL, ScoreGetStr(NOME_ERRO), NULL, "E",
		         ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_12 );
	exit(-1);
  }
  /* -- ativa timer repetitivo com intervalo de 1 segundos -- */
  timer.it_value.tv_sec = (long)ATUAL_DINAMICA;
  timer.it_value.tv_nsec= 0L;
  timer.it_interval.tv_sec= (long)ATUAL_DINAMICA;
  timer.it_interval.tv_nsec= 0L;
  timer_settime(id, 0, &timer, NULL);

  /*--- Fica em loop exibindo o relatorio ---*/
  SetFill( "T", QW_BKGD2, QW_SOLID_PAT );
  exibe = VERDADEIRO;
/* -- Alteracao - Inicio - Robson - 24/10/00 -- */
// Alterado por Leonel  Grupo = 0;
  Grupo = 0;
  PaginaAtual = 1;
//  Grupo = 1;
/* -- Alteracao - Fim - Robson - 24/10/00 -- */
  if( LeTabelas() )
    exit(-1);
  MontaTela( Grupo, PaginaAtual );
  while( exibe )
  {
      id_getev=GetEvent( 0, &event, sizeof( QW_EVENT_MSG ) );
	if( id_getev ne ProxyTempo )
    {
	  switch( Event( &event ) )
	  {
        case QW_CLICK:
		  if( strncmp( event.hdr.key, "Grupo", 5 ) eq 0 )
          {
			if( Grupo ne atoi( &event.hdr.key[5] ) )
			  Grupo = atoi( &event.hdr.key[5] );
		    else
			  break;
			PaginaAtual = 1;
		    MontaTela( Grupo, PaginaAtual );
		    break;
          }
          if( !strcmp( event.hdr.key, "Abandona" ) )
          {
            exibe = FALSO;
            break;
          }
          if( !strcmp( event.hdr.key, "PgDown" ) )
          {
			PaginaAtual = 2;
            MontaTela( Grupo, 2 );
            break;
          }
          if( !strcmp( event.hdr.key, "PgUp" ) )
          {
			PaginaAtual = 1;
            MontaTela( Grupo, 1 );
            break;
          }
        break;
	  }
    }
	else
	{
      /* -- Le tabelas necessarias da base de dados do nodo no controle -- */
	  if( LeTabelas() )
	    exit(-1);
	  AtualTela( Grupo, PaginaAtual );
	}
  }
}

void MontaTela( Grupo, Pagina )
{
  QW_RECT_AREA area;
  int  c;
  int  l;
  int  cuba;
  int  indcuba;
  char buffer[80];
  char tag[15];
  int  MaxLinhas, linha;

  Erase( "Linha*" );
  if (ElementInfo( "Cabecalho2", NULL, NULL, &area, NULL ) eq 0)
  { //Elemento nao encontrado, abortar!!
    char errormsg[80];
	sprintf(errormsg,ScoreGetStr(SCORE_ERR_1),COD_ERRO_99);
   	ExibeErro( errormsg );
	exit(-1);
  }
  l = area.row + area.height + OFFSET_LINHA;
  c = area.col;
  SetColor( "T", QW_BLACK );
  if (Pagina eq 1)
  {
    if (GrupoCuba->Grupo[Grupo].NumCubas > MAX_LINHAS_REL)
	  MaxLinhas = MAX_LINHAS_REL;
	else
	  MaxLinhas = GrupoCuba->Grupo[Grupo].NumCubas;
	cuba = 0;
  }
  if (Pagina eq 2)
  {
    if (GrupoCuba->Grupo[Grupo].NumCubas < MAX_LINHAS_REL)
	{
/* -- Alteracao - Inicio - 02/02/2001 - Leonel - Correcao de page down -- */
	  MaxLinhas = GrupoCuba->Grupo[Grupo].NumCubas;
//	  Pagina = 1;
/* -- Alteracao - Fim - 02/02/2001 - Leonel - Correcao de page down -- */
	  cuba = 0;
	}
	else
	{
	  MaxLinhas = GrupoCuba->Grupo[Grupo].NumCubas - MAX_LINHAS_REL;
	  cuba = MAX_LINHAS_REL;
	}
  }
  for( linha = 0; linha < MaxLinhas; ++linha )
  {
	indcuba = GrupoCuba->Grupo[Grupo].Cuba[cuba].IndCuba;
	if( (AVC.Param[indcuba].TemPF eq TEM_PF ) and
  	    (AVC.ParUser1[indcuba].HabilitaPF eq VERDADEIRO) and
//	    (AlgControleGlobal(indcuba, ALG_SCORE02)) )
		)
	{
      MontaLinha( GrupoCuba->Grupo[Grupo].Cuba[cuba].NumCuba,
	  			  indcuba, buffer);
	  sprintf( tag, "Linha%d", linha );
	  CorCuba[indcuba] = QW_BKGD2;
      DrawAt( l, c );
	  DrawText( buffer, 0, 0, strlen(buffer), NULL, tag );
	  l += OFFSET_LINHA;
    }
	cuba++;
  }
  Draw();
}

void AtualTela( Grupo, Pagina )
{
  int  cuba;
  char buffer[80];
  char tag[15];
  byte linha;
  byte MaxLinhas;

  if (Pagina eq 1)
  {
    if (GrupoCuba->Grupo[Grupo].NumCubas > MAX_LINHAS_REL)
	  MaxLinhas = MAX_LINHAS_REL;
	else
	  MaxLinhas = GrupoCuba->Grupo[Grupo].NumCubas;
	cuba = 0;
  }
  if (Pagina eq 2)
  {
    if (GrupoCuba->Grupo[Grupo].NumCubas < MAX_LINHAS_REL)
	{
	  Pagina = 1;
	  cuba = 0;
	}
	else
	{
	  MaxLinhas = GrupoCuba->Grupo[Grupo].NumCubas - MAX_LINHAS_REL;
	  cuba = MAX_LINHAS_REL;
	}
  }
  for( linha = 0; linha < MaxLinhas; ++linha )
  {
    MontaLinha( GrupoCuba->Grupo[Grupo].Cuba[cuba].NumCuba,
				GrupoCuba->Grupo[Grupo].Cuba[cuba].IndCuba, buffer);
	sprintf( tag, "Linha%d", linha );
	ChangeText( tag, buffer, 0, strlen(buffer), 0 );
    TrataAlarmeIns( GrupoCuba->Grupo[Grupo].Cuba[cuba].IndCuba, tag );
	cuba++;
  }
}

void MontaLinha( int cuba, int indcuba, char *buffer )
{
  long HoraAtual;
  long DurSubEst;

  HoraAtual = time(NULL);
  DurSubEst = HoraAtual - AVC.User1[indcuba].HoraIniSubEstAtual;

  //aproveita variavel local para calcular tempo no algoritmo atual
  HoraAtual= AVC.User1[indcuba].TempEstAtual/((long) (SAD_TICKS / Comum->BaseTempoMcp));


  if ((EST_AVC(indcuba).EstadoCuba eq CUBA_NORMAL) and
      (AVC.Param[indcuba].TemPF eq TEM_PF) and
      (AVC.ParUser1[indcuba].HabilitaPF eq VERDADEIRO) and
//      (AlgControleGlobal(indcuba, ALG_SCORE02)))
	  )
  {	  
	sprintf( buffer, "%03d  %-8.8s %-8.8s %-8.8s %02d:%02d %6.1f   %02d  %02d:%02d %5.1f %5.1f %5.2f",
		   cuba, 
		   SinalSituacao(indcuba),
		   SinalSituacaoAlim(indcuba),
		   NomeModoAlim(AVC.User1[indcuba].EstadoAlimAtual, indcuba),
		   HoraAtual/3600,
		   (HoraAtual/60) Mod 60,
		   AVC.User1[indcuba].QtAAlimEstAtual,
		   AVC.User1[indcuba].State,
		   DurSubEst/3600,
		   (DurSubEst/60) Mod 60,
		   AVC.User1[indcuba].FornecSubEst,
		   AVC.User1[indcuba].FornecSubEst - AVC.User1[indcuba].ConsumoSubEst,
		   AVC.User1[indcuba].EfiCurr*100.0);
  }
  else
  {
	sprintf( buffer, "%03d  %-8.8s %-8.8s %-8.8s %-5.5s   %-5.5s  %-2.2s  %-5.5s   %-3.3s %-5.5s %-5.5s",
		   cuba, 
		   SinalSituacao(indcuba),
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

void TrataAlarmeIns( int indcuba, char *tag )
{	
  if((Cuba+indcuba)->EstadoAtual[0] ne NORMAL)
  {
  	if( CorCuba[indcuba] ne CNF_ALA.CorFaixasAlarmeC[(Cuba+indcuba)->EstadoAtual[0]] )
	{
	  ChangeFill( tag, CNF_ALA.CorFaixasAlarmeC[(Cuba+indcuba)->EstadoAtual[0]], QW_SOLID_PAT );
	  CorCuba[indcuba] = CNF_ALA.CorFaixasAlarmeC[(Cuba+indcuba)->EstadoAtual[0]];
	}
  }
  else
  {
    if( CorCuba[indcuba] ne QW_BKGD2 )
    {
      ChangeFill( tag, QW_BKGD2, QW_SOLID_PAT );
	  CorCuba[indcuba] = QW_BKGD2;
    }
  } 
}

/*
------------------------------------------------------------------------------
| SinalSituacaoAlim - Sinaliza  as situacoes  Manual-Local, Manual-Remoto ou |
|                     Automatico.                                            |
------------------------------------------------------------------------------
*/
char  *SinalSituacaoAlim( int Cuba )
{
  static char condicao[9];

  /*-- Sinaliza alimentacao em Manual-Local. --*/
  memset(condicao, 0x00,sizeof(condicao));
  strcpy(condicao,ScoreGetStr(SCORE_MSG_49));
  if (EST_AVC(Cuba).Est.ManualAlimLoc eq VERDADEIRO) 
  {
    memset(condicao, 0x00,sizeof(condicao));
	strcpy(condicao,ScoreGetStr(MAN_LOC));
  }
  else 
  {
	/*-- Sinaliza alimentacao em Manual-Remoto. --*/
	if (EST_AVC(Cuba).Est.ManualAlimRem eq VERDADEIRO)
	{
      memset(condicao, 0x00,sizeof(condicao));
  	  strcpy(condicao,ScoreGetStr(MAN_REM));
	} 
  }
  return( condicao );
} /*-- SinalSituacaoAlim --*/

/*
--------------------------------------------------------------------------------
| SinalSituacao - Sinaliza  as situacoes  Manual-Local, Manual-Remoto,  Efeito |
|                 Anodico, Corrida ou Quebrada.                                |
--------------------------------------------------------------------------------
*/
char* SinalSituacao ( int Cuba )
{
  static char cond[10];
  
  /*-- Sinaliza cuba em Manual-Local. --*/
  memset(cond,0x00,sizeof(cond));
  strcpy(cond,ESTADO_NUL);
  if ( EST_AVC(Cuba).ChaveLocRem eq LOCAL ) 
  {
	strcpy(cond,ScoreGetStr(MAN_LOC));
  } 
  else 
  {
	/*-- Sinaliza cuba em Manual-Remoto. --*/
	if ( EST_AVC(Cuba).ChaveAutMan eq MANUAL ) 
	{
	  if (EST_AVC(Cuba).ManualControle)
		strcpy(cond,ScoreGetStr(MAN_CTR));	/* Manual pelo controle */
	  else
		strcpy(cond,ScoreGetStr(MAN_REM));
	} 
	else 
	{
	  if ( EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL)
	  {
		/*-- Sinaliza cuba em Efeito Anodico. --*/
		if ( EST_AVC(Cuba).Ea eq VERDADEIRO ) 
		  strcpy(cond,ScoreGetStr(EA));
		else
		{
		  /*-- Sinaliza cuba em Corrida. --*/
		  if ( EST_AVC(Cuba).Corrida eq VERDADEIRO ) 
			strcpy(cond,ScoreGetStr(CORRIDA));
		  else
		  {
			/*-- Sinaliza cuba em Quebrada --*/
			if ( EST_AVC(Cuba).Quebrada eq VERDADEIRO ) 
			  strcpy(cond,ScoreGetStr(QUEBRADA));
		  }
		}
 	  }
	}
  }
  
  return(cond);
} /*-- SinalSituacao --*/

/*
--------------------------------------------------------------------------------
| LeTabelas - Quando nao estiver rodando no micro de controle, le do micro que |
|             estiver no controle todas as tabelas da base de dados que forem  |
|             consultadas por ESTE relatorio. So devem ser lidas as tabelas que|
|             sofram alteracoes ON-LINE (AVC.Abs nao e' necessario).           |
|             Retorna 0 se ok, e diferente de 0 -> codigo de erro              |
--------------------------------------------------------------------------------
*/
int LeTabelas(void)
{
  int nodo_controle, status;
  char msg_erro[80];
  static int cont_outras_tab=1;

  nodo_controle=AVL.NodoNoControle;
  if (My_nid ne nodo_controle)
  { /* -- Estou rodando em outro nodo, entao leio tabelas do controle -- */
	/* -- Le tabela AVC.Cleit -- */
	if (status=ScoreBd(nodo_controle,TABELA_AVC,BD_LER,(void *)&AVC.Cleit,
						CalcByteOffset(&AVC,&AVC.Cleit),
						sizeof(AVC.Cleit)))
	{
      //Sinaliza falha na abertura da base de dados
	  sprintf(msg_erro, ScoreGetStr(SCORE_ERR_4), My_name, COD_ERRO_16,
				   status, TABELA_AVC);
	  ExibeErro(msg_erro);
	  return(status);
	}
	/* -- Tabelas que podem ser lidas em uma frequencia menor -- */
	if (cont_outras_tab <= 1)
	{
	  cont_outras_tab=FREQ_TABS_PARAM;
	  /* -- Le tabela AVC.Param -- */
	  if (status=ScoreBd(nodo_controle,TABELA_AVC,BD_LER,(void *)&AVC.Param,
						CalcByteOffset(&AVC,&AVC.Param),
						sizeof(AVC.Param)))
	  {
        //Sinaliza falha na abertura da base de dados
  	    sprintf(msg_erro, ScoreGetStr(SCORE_ERR_4), My_name, COD_ERRO_16,
		  	    status, TABELA_AVC);
	    ExibeErro(msg_erro);
		return(status);
	  }
	  /* -- Le tabela AVC.User1 -- */
	  if (status=ScoreBd(nodo_controle,TABELA_AVC,BD_LER,(void *)&AVC.User1,
						CalcByteOffset(&AVC,&AVC.User1),
						sizeof(AVC.User1)))
	  {
        //Sinaliza falha na abertura da base de dados
  	    sprintf(msg_erro, ScoreGetStr(SCORE_ERR_4), My_name, COD_ERRO_16,
		  	    status, TABELA_AVC);
	    ExibeErro(msg_erro);
		return(status);
	  }
	}
	else
	  cont_outras_tab--;
  }
  return(0);
}

char *LeComum( char *nome, size_t tamanho )
{
  int  fd;
  char *p;

  fd = shm_open( nome, O_RDWR, 0 );
  if( fd ne -1 )
  {
    p = mmap( 0, tamanho, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0 );
    if( p eq (void *)-1 )
    {
      close( fd );
	  return( NULL );
    }
  }
  else
    return( NULL );
  close( fd );
  return( p );
}

