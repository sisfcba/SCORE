/******************************************************************************

             ACCENTURE - ACPS - ACCENTURE PLANT & COMMERCIAL SERVICES
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 5

    CLIENTE     : CBA - Companhia Brasileira de Aluminio SA

	PROJETO		: GENERICO

	SISTEMA		: GENERICO

	ARQUIVO		: MenuPrincipal.c 

	CONTEUDO	: Funcao que gerencia o menu principal do radio

	AUTOR		: Alexandre Mariz Bandeira de Morais

	SISTEMA OPERACIONAL:  QNX 4.25B		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 1.0		  -		  DATA  : 31/07/01

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
31/07/01 | Edicao Inicial                                		| Bandeira
-------------------------------------------------------------------------------
$Id: MenuPrincipal.c,v 1.2.8.1 2014/10/27 15:23:52 leo Exp $

$Log: MenuPrincipal.c,v $
Revision 1.2.8.1  2014/10/27 15:23:52  leo
Preparacao para criar kit de desenvolvimento do radio. Retiradas referencias
a prologo antigo da Alcan.

******************************************************************************/
#include <RFCBA.h>

//**************************************************************
//
// MenuPrincipal - Monta Menu Principal do radio
//
//**************************************************************
void MenuPrincipal( void )
{
  int				dwError;
  int				iResposta;
  int				iAnsSpc;						// numero maximo de caracteres aceitos na resposta
  SMANDAMSGPARAM	sParam;							// parametros da mensagem
  STERMANSW			sTermAnsw;						// resposta proveniente do coletor
  char				*p;

  
  for(;;) // loop eterno cuba
  {
    memset( &sTermAnsw, 0x00, sizeof( sTermAnsw ) );
    memset( &sParam, 	  0x00, sizeof( sParam ) );

    // inicializacao das variaveis.
    sParam.iRow = 0;				// numero da linha onde a mensagem sera mostrada
    sParam.iCol = 0;				// numero da coluna onde a mensagem sera mostrada
    sParam.ulOptions = DP_ENABLE_SCAN;	
    sParam.iCurRow = 0;			// numero da linha onde o dado sera recebido
    sParam.iCurCol = 0;			// numero da coluna onde o dado sera recebido
    iAnsSpc = 1;					// numero maximo de caracteres que serao lidos
    // exibe menu principal, mostrado apos o login
    // envia menu e espera por resposta
    sprintf( aux, "%s\n%s [%d]\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
					 ScoreGetStr(SCORE_MSG_3290),
					 ScoreGetStr(SCORE_MSG_3291),
					 cuba_num,
					 ScoreGetStr(SCORE_MSG_3292),
					 ScoreGetStr(SCORE_MSG_3293),
					 ScoreGetStr(SCORE_MSG_3294),
					 ScoreGetStr(SCORE_MSG_3295),
					 ScoreGetStr(SCORE_MSG_3296),
					 ScoreGetStr(SCORE_MSG_3297),
					 ScoreGetStr(SCORE_MSG_3298),
					 ScoreGetStr(SCORE_MSG_3299) );
	dwError = MandarPrompt( &sParam, aux, iAnsSpc, &sTermAnsw);
	if( dwError ne 0 )
	  TrataErroColetor( dwError );
    iResposta = strtol( sTermAnsw.pcAnswStrg, &p, 10 );
  	if( *p ne NULL )
	{
      cuba(sTermAnsw.pcAnswStrg);
	  continue;
	}
	switch( iResposta ) // faz tratamento da opcao do menu
	{
	  case 1:
		  cuba(NULL);
		break;
	  case 2:
		  Operacao1Cba();
//		  Operacao1();
//		  Operacao2();
		break;
	  case 3:
		  Parametros();
	    break;
	  case 4:
	      Graficos();
	    break;
	  case 5:
	      ProcessoCba();
//	      Processo();
	    break;
  	  case 6:
	      AtualVar();
	    break;
  	  case 7:
	      Eventos();
	    break;
  	  case 8:
	      MenuCalibExib();
	    break;
  	  case 9:
		  TrataMetal1Cba();
//		  TrataMetal1();
//	      HoraSistema();
	    break;
  	  case 0:
	      Bateria();
	    break;
  	  case SAIR_MENU:
	   	  Abandona();
		break;  
	}
  }
}
