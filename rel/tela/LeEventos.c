/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO  : TODOS

	SISTEMA  : GERAL

	ARQUIVO  : LeEventos

	CONTEUDO : Tarefa para ler eventos no nodo de controle 

	AUTOR    : Alexandre Mariz Bandeira de Morais

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO   : 0.0		  -	  DATA  : 23/07/95

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
dd/mm/aa | descricao												| Autor
-------------------------------------------------------------------------------
******************************************************************************/

#define	PROGRAMA_PRINCIPAL

/*
-------------------------------------------------------------------------------
							Includes
-------------------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <sys/kernel.h>
#include <Definicao.h>
#include <Score.h>
#include <VarsComum.h>
#include <Eventos.h>
#include <Prototipos.h>
#include <TiposOpeW.h>

/*
-------------------------------------------------------------------------------
							Constantes
-------------------------------------------------------------------------------
*/

/*-- Tamanho do cache --*/
#define	MAX_REG_EV				2000
#define	MAX_SIZE				( MAX_REG_EV * sizeof( t_rec_ev ) )

/*
-------------------------------------------------------------------------------
							Prototipos
-------------------------------------------------------------------------------
*/

void InicDatas( time_t *h1, time_t *h2, time_t *h3 );
void MontaNomeHist(time_t DataAtual, time_t DataArq, char *NomeArq);
int  AchaCuba( int Cuba, t_filtrosPD *filtro );
void main(int argc, char *argv[]);

/*
-------------------------------------------------------------------------------
							Variaveis Globais
-------------------------------------------------------------------------------
*/

pid_t			Pid;
t_rec_ev		evento[MAX_REG_EV];
t_rec_ev		*Buffer;
t_LeEventos		BufEventos;

//void main(int argc, char *argv[])
void main()
{
  char			ArqEv[80];
  byte			f_loop;
  int			i, j, k, w;
  int			DescEv;
  int			Resposta;
  int			DiaInicial, DiaFinal, MesInicial, MesFinal;
  size_t		nbytes;
  size_t		nregs;
  time_t		DataArq;
  struct tm		aux;

  if( ( Pid = Receive( 0, &BufEventos, sizeof( t_LeEventos ) ) ) eq -1 )
  {
    printf( "\nLeEventos: Erro Receive 1\n" );
	exit( 0 );
  }    
  /* Pega area comum de memoria */
  if( PegaComum( &Comum ) )
  {
	printf( "\nLeEventos: Erro TABELA GLOBAL\n" );
	exit( 0 );
  }
  Buffer = (t_rec_ev *)malloc( MAX_SIZE ); /* aloca memoria necessaria por enquanto */
  if( Buffer eq NULL )
  {
	printf( "\nLeEventos: Falha malloc Buffer\n" );
    exit( 0 );				 
  }
  DataArq = BufEventos.DataInicial;
  memcpy( &aux, localtime( &DataArq ), sizeof( struct tm ) );
  DiaInicial = aux.tm_mday;
  MesInicial = aux.tm_mon;
  memcpy( &aux, localtime( &BufEventos.DataFinal ), sizeof( struct tm ) );
  DiaFinal = aux.tm_mday;
  MesFinal = aux.tm_mon;
  j = 0;
  w = 2;
  if( ( BufEventos.DataFinal - DataArq ) >= 0 )
	f_loop = VERDADEIRO;
  else
	f_loop = FALSO;
  while( f_loop ) /* executa inclusive data final */
  {
	/*-- Monta path do arquivo de eventos --*/
	MontaNomeHist( BufEventos.DataAtual, DataArq, ArqEv );
	/*-- Abre arquivo para leitura --*/
	if( ( DescEv = open( ArqEv, O_RDONLY ) ) ne -1 )
	{
	  /* registro do eventos */
	  while( ( nbytes = read( DescEv, &evento[0], MAX_SIZE ) ) > 0 )
	  {
	    nregs = nbytes / sizeof( t_rec_ev );
	    for( i = 0; i < nregs; ++i )
		{
	      /* verifica evento */
		  for( k = 0; k < BufEventos.NumEvs; ++k )
		  {
	        if( ( evento[i].CodeEv eq BufEventos.Evento[k] ) and
			    ( ( evento[i].DataEv >= BufEventos.DataInicial ) and
			      ( evento[i].DataEv <= BufEventos.DataFinal ) ) and
			    ( AchaCuba( evento[i].CubaIniEv, &BufEventos.filtros ) eq VERDADEIRO ) )
		    {			  
              memcpy( (Buffer+j), &evento[i], sizeof( t_rec_ev ) );
			  ++j;
			  if( ( j Mod MAX_REG_EV ) eq 0 ) /* completou um registro */
			  {
			    Buffer = (t_rec_ev *)realloc( Buffer, MAX_SIZE * w ); /* realoca mais um size */
			    if( Buffer eq NULL )
	            {
                  printf ( "\nLeEventos: Erro Realloc %d \n ", w );
                  Resposta = -2; /* erro no realloc */
                  Reply( Pid, &Resposta, sizeof( int ) ); /* responde erro */
				  free( Buffer );
				  exit( 0 ); /* aborta */
	            }
				++w; /* incrementa fator multiplicador */
			  }
			}
		  }
		}
	  }
	}
	else
	{
	  if( !BufEventos.NaoPara ) /* nao para mesmo se nao achar */
	  {
        Resposta = -1; /* erro, arquivo nao existe */
        Reply( Pid, &Resposta, sizeof( int ) ); /* responde erro */
		free( Buffer );
	    exit( 0 );
	  }		
	}
    close( DescEv ); /* fecha arquivo */
    if( DiaInicial eq DiaFinal and
        MesInicial eq MesFinal )
	  f_loop = FALSO;
	DataArq += NUM_SEGUNDOS_DIA; /* vai para o proximo dia */
    memcpy( &aux, localtime( &DataArq ), sizeof( struct tm ) );
    DiaInicial = aux.tm_mday;
    MesInicial = aux.tm_mon;
  }
  Resposta = j;	/* numero de registros lidos */
  if( Reply( Pid, &Resposta, sizeof( int ) ) eq -1 )
  {
    printf( "\nLeEventos: erro de Reply 1 errno=%s\n", strerror(errno) );
	free( Buffer );
	exit( 0 );
  }
  if( Resposta eq 0 )
  {
	free( Buffer );
    exit( 0 );
  }
  Resposta = -1;
  j = 0;
  while( Resposta ne 0 )
  {
    if( ( Pid = Receive( 0, &Resposta, sizeof( int ) ) ) eq -1 )
    {
      printf( "\nLeEventos: Erro Receive 2\n" );
	  free( Buffer );
	  exit( 0 );
    }    
	if( Resposta ne 0 )
	{
      if( Reply( Pid, (Buffer+j), Resposta * sizeof( t_rec_ev ) ) eq -1 )
      {
        printf( "\nLeEventos: erro de Reply 2 errno=%s\n", strerror(errno) );
	    free( Buffer );
	    exit( 0 );
      }
	  j += Resposta; /* index para buffer */
	}
	else
	{
      if( Reply( Pid, NULL, 0 ) eq -1 )
      {
        printf( "\nLeEventos: erro de Reply 3 errno=%s\n", strerror(errno) );
	    free( Buffer );
	    exit( 0 );
      }
	}  
  }	
  free( Buffer );
#ifdef	CBA_120KAII_III
  /* Aguarda tarefa receber resposta antes de morrer. Na rede com maquinas 
     486 33 e 66 misturadas com Pentium, a rede fica mais lenta algumas vezes
     e o nodo de operacao recebe a indicacao de que a tarefa morreu ANTES de
     receber seu reply, falhando o send. No entanto esta tarefa recebeu o
     send, o processou normalmente e respondeu normalmente. O sleep e' para
     dar tempo do outro micro receber o reply. */
  sleep(15);
#endif
} /*-- LeEventos --*/

/*
------------------------------------------------------------------------------
							Funcoes Locais
------------------------------------------------------------------------------
*/

/*
------------------------------------------------------------------------------
  MontaNomeHist - Monta nome do arquivo de eventos a ser pesquisado
------------------------------------------------------------------------------
*/
void MontaNomeHist( time_t DataAtual, time_t DataArq, char *NomeArq )
{
  char	 NomeHist[80];
  struct tm Data;
  struct tm Data1;

  /*-- Monta data relatorio --*/
  memcpy( &Data, localtime(&DataArq), sizeof(Data) );
  memcpy( &Data1, localtime(&DataAtual), sizeof(Data1) );

  /*-- Monta path de eventos --*/
  if ( (Data.tm_mday eq Data1.tm_mday) and
	   (Data.tm_mon eq Data1.tm_mon) )
  {
	/*-- Monta nome arquivo eventos para ramdisk --*/
	sprintf(NomeHist, ARQUIVO_EV_RAMDISK, Data.tm_mday, Data.tm_mon + 1,
			Data.tm_year);
  }
  else
  {
	/*-- Monta nome arquivo eventos do disco --*/
	sprintf(NomeHist, ARQUIVO_EV_DISCO, Data.tm_mday, Data.tm_mon + 1,
			Data.tm_year);
  }
  /*-- Monta numero nodo no path do arquivo --*/
  sprintf(NomeArq,"//%d%s",AVL.NodoNoControle, NomeHist);

} /*-- MontaNomeHist --*/

int AchaCuba( int Cuba, t_filtrosPD *filtros )
{
  int IndCuba;
  IndCuba = 0;
  if( Cuba eq -1 )
    return( VERDADEIRO ); /* nao critica, e' linha */
  if( filtros->Par.Total eq -1 ) /* nao critica cuba */
    return( VERDADEIRO ); /* nao critica, forcado */
  while( IndCuba < filtros->Par.Total )
  {
    if( Cuba eq filtros->Par.NumCuba[IndCuba] )
	  return( VERDADEIRO );
    ++IndCuba;	  
  }  
  return( FALSO );
}
