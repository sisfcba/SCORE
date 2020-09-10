/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.1

	PROJETO		: CBA - Companhia Brasileira de Aluminio SA

	SISTEMA		: SALAS 120KA II e III

	ARQUIVO		: PFLib.c

	CONTEUDO	: Biblioteca de funcoes do Algoritmo de alimentacao da CBA

	AUTOR		: Ricardo Teixeira Leite Mourao / Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	02/01/97

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
Data     | Descricao                                            | Autor 
-------------------------------------------------------------------------------
02/01/97 | Edicao inicial                                       | Ricardo-Leonel
-------------------------------------------------------------------------------
01/09/17 | TK-ALIM - Preparacão Toolkit Alimentacao             | Carlos
-------------------------------------------------------------------------------
******************************************************************************/
/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include	<AlimentCBA.h>
#include	<Prototipos.h>
#include	<ScoreMsgs.h>
#include	<Eventos.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<time.h>

/*
-------------------------------------------------------------------------------
                           Prototipos
-------------------------------------------------------------------------------
*/

static char *NomeOrig(int Origem);


/*
-------------------------------------------------------------------------------
                           Variaveis Globais
-------------------------------------------------------------------------------
*/
/* -- Apontadores para as tabelas comuns -- */
#include	<VarsComum.h>

/*
--------------------------------------------------------------------------------
| MudaEstadoAlim - Altera o estado atual do algoritmo de alimentacao.            |
--------------------------------------------------------------------------------
*/
void MudaEstadoAlim(int Cuba,int Estado, int Origem)
{
  int	ModoAnt;
  long	Ajuste;
  long	TempoAnt;
  long  hora,min;
  float	QuantAlim;
  char  SAux[12];
  char  haux[6];

  /*-- Inicializacao de parametros para geracao de eventos --*/
  ModoAnt = EstadoAtual(Cuba);
  Ajuste = (long) ((((short int) (SAD_TICKS / Comum->BaseTempoMcp)) * 60));
  TempoAnt = (long) (AVC.User1[Cuba].TempEstAtual / Ajuste);
  hora= TempoAnt/60;
  min= (TempoAnt%60);
  sprintf(haux,"%02ld:%02ld",hora,min);
  QuantAlim = AVC.User1[Cuba].QtAAlimEstAtual;

  /* Sinaliza inicio de um estado */
  AVC.User1[Cuba].InicioAlgAtual=VERDADEIRO;

  /* Inicializa Tempo no Estado Atual */
  AVC.User1[Cuba].TempEstAtual = 0;

  /* Guarda estado anterior */
  AVC.User1[Cuba].EstadoAlimAnt = AVC.User1[Cuba].EstadoAlimAtual;

  /* Atualiza o novo estado */
  AVC.User1[Cuba].EstadoAlimAtual=Estado;

  /* Coloca data e hora inicio mudanca de estado */
  AVC.User1[Cuba].HoraIniEstAtual = time ( NULL );

  /* Inicializa quantidade de alumina alimentada no estado atual */
  AVC.User1[Cuba].QtAAlimEstAtual = 0;

  /* Desativa flag indicando check */
  EST_AVC(Cuba).Est.CheckAtivo=FALSO;

/* -- Alteracao - inicio - Leonel - 16/9/2002 - So gera evento se estiver no controle -- */
  if (Comum->EstaControlando)
  {
	strcpy(SAux,NomeModoAlim(ModoAnt, Cuba));
	/*-- Geracao de evento de mudanca de estado --*/
	GeraEvento(EV_MUDA_ALIMENT, Cuba, -1, SAux, haux,
			 QuantAlim, NomeModoAlim(Estado, Cuba), NomeOrig(Origem));
  }
/* -- Alteracao - fim - Leonel - 16/9/2002 - So gera evento se estiver no controle -- */
  /* Muda para o primeiro estado do algoritmo */
  MudaEstadoSub(Cuba,1);  
}

/*
-------------------------------------------------------------------------------
NomeModoAlim - Retornar o nome do modo de alimentacao da cuba
------------------------------------------------------------------------------
*/
char *NomeModoAlim(int Modo, int Cuba)
{
  static char ModoAlim[12];

  memset(ModoAlim, 0x00, sizeof(ModoAlim));
  switch(Modo)
  {
	case EST_ALIM_PADRAO:
		 strcpy(ModoAlim, ScoreGetStr(ALIM_PADRAO));
		 break;
	case EST_ALIM_SUSPENSA:
/* -- Alteracao - Inicio - 01/08/2002 - Robson - EA ou Tempo ? -- */
		 if (AVC.User1[Cuba].TempoSuspende eq 0)
		 {
		   /* -- evento para EA -- */
		   strcpy(ModoAlim, ScoreGetStr(ALIM_SUSPENSA_EA));
		 }
		 else
		 {
		   /* -- evento para Tempo -- */
		   strcpy(ModoAlim, ScoreGetStr(ALIM_SUSPENSA_TEMPO));
		 }
/* -- Alteracao - Fim - 01/08/2002 - Robson - EA ou Tempo ? -- */
		 break;
	case EST_ALIM_EA:
		 strcpy(ModoAlim, ScoreGetStr(ALIM_EA));
		 break;
	case EST_ALIM_EXCECAO:
		 strcpy(ModoAlim, ScoreGetStr(ALIM_EXCECAO));
		 break;
	default:
		 strcpy(ModoAlim, ScoreGetStr(ALIM_INVALIDA));
		 break;
  }
  return(ModoAlim);
}

/*
-------------------------------------------------------------------------------
NomeOrig - Retornar o nome de quem ativou o muda estado
------------------------------------------------------------------------------
*/
static char *NomeOrig(int Origem)
{
  static char Orig[9];

  memset(Orig, 0x00, sizeof(Orig));
  switch(Origem)
  {
	case MUDA_CONTROLE:
		 strcpy(Orig, ScoreGetStr(ORIGEM_CONTROLE));
		 break;
	case MUDA_OPER:
		 strcpy(Orig, ScoreGetStr(ORIGEM_OPERADOR));
		 break;
	case MUDA_EXT:
		 strcpy(Orig, ScoreGetStr(ORIGEM_EXTERNA));
		 break;
	default:
		 strcpy(Orig, ScoreGetStr(ORIGEM_INVALIDA));
		 break;
  }

  return(Orig);
}

/*
--------------------------------------------------------------------------------
  MudaEstadoSub - Altera o subestado do algoritmo atual
--------------------------------------------------------------------------------
*/
void MudaEstadoSub(int Cuba, int Estado)
{
  long horatual,laux;
  int hh,mm;
  char saux[6];

  /* armazena hora atual em variavel local (c/ referencia a 1980) */
  horatual= time( NULL );
  
  /* Converte tempo no estado atual para o formato hh:mm */
  laux= horatual - AVC.User1[Cuba].HoraIniSubEstAtual;
  hh= (int) (laux/3600L);
  mm= (int) ((laux -((long)hh*3600L))/60L);
  sprintf(saux,"%02d:%02d",hh,mm);
    
  /* Sinaliza inicio de um estado */
  AVC.User1[Cuba].InicioSubEst=VERDADEIRO;

  /* Armazena ultimo estado da cuba */
  AVC.User1[Cuba].PrevState= AVC.User1[Cuba].State;

  /* Coloca a cuba no novo subestado */
  AVC.User1[Cuba].State=Estado;

/* -- Alteracao - inicio - Leonel - 16/9/2002 - So gera evento se estiver no controle -- */
  if (Comum->EstaControlando)
  { /*-- Geracao de evento de mudanca de estado --*/
	GeraEvento(EV_MUDA_EST, Cuba, -1, AVC.User1[Cuba].PrevState,
             saux, AVC.User1[Cuba].FornecSubEst, AVC.User1[Cuba].State, 
				NomeModoAlim(AVC.User1[Cuba].EstadoAlimAtual, Cuba));
  }
/* -- Alteracao - fim - Leonel - 16/9/2002 - So gera evento se estiver no controle -- */

  /* Inicializa variaveis para inicio do proximo estado */
  /* Coloca data e hora inicio mudanca de estado */
  AVC.User1[Cuba].HoraIniSubEstAtual = horatual;

  /* reseta consumo de alumina no estado atual */
  AVC.User1[Cuba].ConsumoSubEst= 0;

  /* reseta fornecimento de alumina no estado atual */
  AVC.User1[Cuba].FornecSubEst= 0;
}

/* -- fim PFLib.c -- */
