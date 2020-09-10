/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.4

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II

	ARQUIVO		: OperacaoCba.c 

	CONTEUDO	: Funcao que gerencia o menus de operacao

	AUTOR		: Alexandre Mariz Bandeira de Morais

	SISTEMA OPERACIONAL:  QNX 4.25B		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 1.0		  -		  DATA  : 31/07/01

	HISTORICO DAS EDICOES

$Id$

$Log$
******************************************************************************/
#include <RFComunica.h.user>

//**************************************************************
//
// Operacao1Cba - Menu P/ chamada de programas de operacao do Score
//
//**************************************************************
void Operacao1Cba(void)
{
  int				dwError;
  int				iResposta;
  int				iAnsSpc;						// numero maximo de caracteres aceitos na resposta
  SMANDAMSGPARAM	sParam;							// parametros da mensagem
  STERMANSW			sTermAnsw;						// resposta proveniente do coletor
  char				*p;

  memset( &sTermAnsw, 0x00, sizeof( sTermAnsw ) );
  memset( &sParam, 	  0x00, sizeof( sParam ) );

  // inicializacao das variaveis.
  sParam.iRow = 0;				// numero da linha onde a mensagem sera mostrada
  sParam.iCol = 0;				// numero da coluna onde a mensagem sera mostrada
  sParam.ulOptions = DP_ENABLE_SCAN;	
  sParam.iCurRow = 0;			// numero da linha onde o dado sera recebido
  sParam.iCurCol = 0;			// numero da coluna onde o dado sera recebido
  iAnsSpc = 1;					// numero maximo de caracteres que serao lidos

  for(;;) // loop eterno cuba
  {
    sprintf( aux, "%s\n%s [%d]\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
					ScoreGetStr(SCORE_MSG_3020),
					ScoreGetStr(SCORE_MSG_3021),
					cuba_num,
					ScoreGetStr(SCORE_MSG_3022),
					ScoreGetStr(SCORE_MSG_3023),
					ScoreGetStr(SCORE_MSG_3024),
					"5>MANOBRA CRUZEIRO",
					"6>EA,QPREV,PEA,RUIDO",
					"7>ANALISE/OPERACIONA",
					"8>SISTEMA",
					"9>M.PRINC. ENT>SAIR");
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
		QuebradaCba();
	    break;
	  case 3:
		CorridaCba();
	    break;
	  case 4:
		TrocaPinosCba();
	    break;
	  case 5:
		MCruzeiroCba();
	    break;
	  case 6:
		RelOperacaoCba();
//		MenuCalibExib();
	    break;
	  case 7:
		TrataMetal1Cba();		
	    break;
  	  case 8:
        HoraSistema();
		break;
	  case 9:
		MenuPrincipal();		
	    break;
	  case SAIR_MENU:
	    Abandona();
		break;
	}
  }
}

//**************************************************************
//
// Operacao2Cba - Menu P/ chamada de programas de operacao do Score
//
//**************************************************************
void Operacao2Cba(void)
{
  int				dwError;
  int				iResposta;
  int				iAnsSpc;						// numero maximo de caracteres aceitos na resposta
  SMANDAMSGPARAM	sParam;							// parametros da mensagem
  STERMANSW			sTermAnsw;						// resposta proveniente do coletor
  char				*p;

  memset( &sTermAnsw, 0x00, sizeof( sTermAnsw ) );
  memset( &sParam, 	  0x00, sizeof( sParam ) );

  // inicializacao das variaveis.
  sParam.iRow = 0;				// numero da linha onde a mensagem sera mostrada
  sParam.iCol = 0;				// numero da coluna onde a mensagem sera mostrada
  sParam.ulOptions = DP_ENABLE_SCAN;	
  sParam.iCurRow = 0;			// numero da linha onde o dado sera recebido
  sParam.iCurCol = 0;			// numero da coluna onde o dado sera recebido
  iAnsSpc = 1;					// numero maximo de caracteres que serao lidos

  for(;;) // loop eterno cuba
  {
    sprintf( aux, "%s\n%s [%d]\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
					ScoreGetStr(SCORE_MSG_3390),
					ScoreGetStr(SCORE_MSG_3391),
					cuba_num,
					ScoreGetStr(SCORE_MSG_3392),
					ScoreGetStr(SCORE_MSG_3393),
					ScoreGetStr(SCORE_MSG_3394),
					ScoreGetStr(SCORE_MSG_3395),
					ScoreGetStr(SCORE_MSG_3396),
					ScoreGetStr(SCORE_MSG_3397),
					ScoreGetStr(SCORE_MSG_3398),
					ScoreGetStr(SCORE_MSG_3399) );
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
		QuebradaCba();
	    break;
	  case 3:
		CorridaCba();
	    break;
	  case 4:
		TrocaPinosCba();
	    break;
	  case 5:
		MCruzeiroCba();
	    break;
	  case SAIR_MENU:
		return;
	}
  }
}
