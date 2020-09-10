/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 5.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II

	ARQUIVO		: RelOperacaoCba.c 

	CONTEUDO	: relatorio de operacao para sinalizar cubas em EA, QuebPrev, PrevEA e Ruido

	AUTOR		: Alexandre Mariz Bandeira de Morais

	SISTEMA OPERACIONAL:  QNX 4.25G		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 1.0		  -		  DATA  : 10/03/05

	HISTORICO DAS EDICOES

$Id$

$Log$
******************************************************************************/

#include <RFComunica.h.user>

//**************************************************************
//
// Relatorio de Operacao
//
//**************************************************************
void RelOperacaoCba(void)
{
  int				dwError;
  int				iResposta;
  int				iAnsSpc;						// número máximo de caracteres aceitos na resposta
  SMANDAMSGPARAM	sParam;							// parâmetros da mensagem
  STERMANSW			sTermAnsw;						// resposta proveniente do coletor
  char				*p;
  int				f_rel;
  int				cuba;

  for(;;) // loop eterno
  {
//*****************************************
// Efeito Anodico
//*****************************************
	f_rel=VERDADEIRO;
	while(f_rel)
	{
      memset( &sTermAnsw, 0x00, sizeof( sTermAnsw ) );
      memset( &sParam, 	  0x00, sizeof( sParam ) );

      // inicializacao das variaveis.
      sParam.iRow = 0;				// numero da linha onde a mensagem sera mostrada
      sParam.iCol = 0;				// numero da coluna onde a mensagem sera mostrada
      sParam.ulOptions = DP_ENABLE_SCAN | DP_DINAMICO;	
      sParam.iCurRow = 0;			// numero da linha onde o dado sera recebido
      sParam.iCurCol = 0;			// numero da coluna onde o dado sera recebido
      iAnsSpc = 1;					// numero maximo de caracteres que serao lidos

      memset(aux1,0x00,sizeof(aux1)); // zera linha corrente
      memset(aux2,0x00,sizeof(aux2)); // zera buffer principal
      /* verifica todas as cubas em EA */
      for(cuba=0;cuba<AVL.NumCubas;++cuba)
      {	
        if(EST_AVC(cuba).EstadoCuba eq CUBA_NORMAL)
        {
	      /*-- Sinaliza cuba em Efeito Anodico. --*/
	      if(EST_AVC(cuba).Ea eq VERDADEIRO) 
	      {
	    	sprintf(aux,"%d",ConvCubScoreOper(cuba));
			if((strlen(aux2)+strlen(aux)) >= 180) // limite da pagina
			  break;		
		    if((strlen(aux1)+strlen(aux)+1) >= 20) // fecha a linha
		    {
		      strcat(aux1,"\n"); // coloca new line
		      strcat(aux2,aux1); // atualiza linha no buffer principal
		      memset(aux1,0x00,sizeof(aux1)); // zera linha novamente
		    }
		    else
		    {
		      if(strlen(aux1) != 0) // coloca a virgula
		        strcat(aux1,",");
		    }
            strcat(aux1,aux); // coloca numero da cuba
	      }
	    }
      }
      strcat(aux2,aux1); // coloca no buffer principal restante
	  // envia menu e espera por resposta
	  sprintf( aux, ">>>EFEITO ANODICO<<<\n%s",aux2);
	  dwError = MandarPrompt( &sParam, aux, iAnsSpc, &sTermAnsw);
	  if( dwError ne 0 )
	    TrataErroColetor( dwError );
      iResposta = strtol( sTermAnsw.pcAnswStrg, &p, 10 );
  	  if( *p ne NULL )
	  {
	    if( strcmp( sTermAnsw.pcAnswStrg, "DP_DINAMICO" ) eq 0 )
	      continue;
	  }
	  switch( iResposta ) // faz tratamento da opcao do menu
	  {
	    case SAIR_MENU:
		  return;
		default:
		  f_rel=FALSO;
	  }
    }
//*****************************************
// Quebrada Preventiva
//*****************************************
	f_rel=VERDADEIRO;
	while(f_rel)
	{
      memset( &sTermAnsw, 0x00, sizeof( sTermAnsw ) );
      memset( &sParam, 	  0x00, sizeof( sParam ) );

      // inicializacao das variaveis.
      sParam.iRow = 0;				// numero da linha onde a mensagem sera mostrada
      sParam.iCol = 0;				// numero da coluna onde a mensagem sera mostrada
      sParam.ulOptions = DP_ENABLE_SCAN | DP_DINAMICO;	
      sParam.iCurRow = 0;			// numero da linha onde o dado sera recebido
      sParam.iCurCol = 0;			// numero da coluna onde o dado sera recebido
      iAnsSpc = 1;					// numero maximo de caracteres que serao lidos

      memset(aux1,0x00,sizeof(aux1)); // zera linha corrente
      memset(aux2,0x00,sizeof(aux2)); // zera buffer principal
      /* verifica todas as cubas em Quebrada Preventiva */
      for(cuba=0;cuba<AVL.NumCubas;++cuba)
      {	
        if(EST_AVC(cuba).EstadoCuba eq CUBA_NORMAL)
        {
	      /*-- Sinaliza cuba em Quebrada Preventiva --*/
	      if(EST_AVC(cuba).Est.QuebPrev eq VERDADEIRO) 
	      {
		    sprintf(aux,"%d",ConvCubScoreOper(cuba));
			if((strlen(aux2)+strlen(aux)) >= 180) // limite da pagina
			  break;		
		    if((strlen(aux1)+strlen(aux)+1) >= 20) // fecha a linha
		    {
		      strcat(aux1,"\n"); // coloca new line
		      strcat(aux2,aux1); // atualiza linha no buffer principal
		      memset(aux1,0x00,sizeof(aux1)); // zera linha novamente
		    }
		    else
		    {
		      if(strlen(aux1) != 0) // coloca a virgula
		        strcat(aux1,",");
		    }
            strcat(aux1,aux); // coloca numero da cuba
	      }
	    }
      }
      strcat(aux2,aux1); // coloca no buffer principal restante
	  // envia menu e espera por resposta
	  sprintf( aux, ">QUEBRADA PREVENTIVA\n%s",aux2);
	  dwError = MandarPrompt( &sParam, aux, iAnsSpc, &sTermAnsw);
	  if( dwError ne 0 )
	    TrataErroColetor( dwError );
      iResposta = strtol( sTermAnsw.pcAnswStrg, &p, 10 );
  	  if( *p ne NULL )
	  {
	    if( strcmp( sTermAnsw.pcAnswStrg, "DP_DINAMICO" ) eq 0 )
	      continue;
	  }
	  switch( iResposta ) // faz tratamento da opcao do menu
	  {
	    case SAIR_MENU:
		  return;
		default:
		  f_rel=FALSO;
	  }
    }
//*****************************************
// Previsao de Efeito
//*****************************************
	f_rel=VERDADEIRO;
	while(f_rel)
	{
      memset( &sTermAnsw, 0x00, sizeof( sTermAnsw ) );
      memset( &sParam, 	  0x00, sizeof( sParam ) );

      // inicializacao das variaveis.
      sParam.iRow = 0;				// numero da linha onde a mensagem sera mostrada
      sParam.iCol = 0;				// numero da coluna onde a mensagem sera mostrada
      sParam.ulOptions = DP_ENABLE_SCAN | DP_DINAMICO;	
      sParam.iCurRow = 0;			// numero da linha onde o dado sera recebido
      sParam.iCurCol = 0;			// numero da coluna onde o dado sera recebido
      iAnsSpc = 1;					// numero maximo de caracteres que serao lidos

      memset(aux1,0x00,sizeof(aux1)); // zera linha corrente
      memset(aux2,0x00,sizeof(aux2)); // zera buffer principal
      /* verifica todas as cubas em Previsao Efeito */
      for(cuba=0;cuba<AVL.NumCubas;++cuba)
      {	
        if(EST_AVC(cuba).EstadoCuba eq CUBA_NORMAL)
        {
	      /*-- Sinaliza cuba em Previsao Efeito. --*/
	      if(EST_AVC(cuba).EaPrev eq VERDADEIRO) 
	      {
		    sprintf(aux,"%d",ConvCubScoreOper(cuba));
			if((strlen(aux2)+strlen(aux)) >= 180) // limite da pagina
			  break;		
		    if((strlen(aux1)+strlen(aux)+1) >= 20) // fecha a linha
		    {
		      strcat(aux1,"\n"); // coloca new line
		      strcat(aux2,aux1); // atualiza linha no buffer principal
		      memset(aux1,0x00,sizeof(aux1)); // zera linha novamente
		    }
		    else
		    {
		      if(strlen(aux1) != 0) // coloca a virgula
		        strcat(aux1,",");
		    }
            strcat(aux1,aux); // coloca numero da cuba
	      }
	    }
      }
      strcat(aux2,aux1); // coloca no buffer principal restante
	  // envia menu e espera por resposta
	  sprintf( aux, ">>PREVISAO EFEITO<<<\n%s",aux2);
	  dwError = MandarPrompt( &sParam, aux, iAnsSpc, &sTermAnsw);
	  if( dwError ne 0 )
	    TrataErroColetor( dwError );
      iResposta = strtol( sTermAnsw.pcAnswStrg, &p, 10 );
  	  if( *p ne NULL )
	  {
	    if( strcmp( sTermAnsw.pcAnswStrg, "DP_DINAMICO" ) eq 0 )
	      continue;
	  }
	  switch( iResposta ) // faz tratamento da opcao do menu
	  {
	    case SAIR_MENU:
		  return;
		default:
		  f_rel=FALSO;
	  }
    }
//*****************************************
// Tratamento de Ruido
//*****************************************
	f_rel=VERDADEIRO;
	while(f_rel)
	{
      memset( &sTermAnsw, 0x00, sizeof( sTermAnsw ) );
      memset( &sParam, 	  0x00, sizeof( sParam ) );

      // inicializacao das variaveis.
      sParam.iRow = 0;				// numero da linha onde a mensagem sera mostrada
      sParam.iCol = 0;				// numero da coluna onde a mensagem sera mostrada
      sParam.ulOptions = DP_ENABLE_SCAN | DP_DINAMICO;	
      sParam.iCurRow = 0;			// numero da linha onde o dado sera recebido
      sParam.iCurCol = 0;			// numero da coluna onde o dado sera recebido
      iAnsSpc = 1;					// numero maximo de caracteres que serao lidos

      memset(aux1,0x00,sizeof(aux1)); // zera linha corrente
      memset(aux2,0x00,sizeof(aux2)); // zera buffer principal
      /* verifica todas as cubas em Tratamento de Ruido */
      for(cuba=0;cuba<AVL.NumCubas;++cuba)
      {	
        if(EST_AVC(cuba).EstadoCuba eq CUBA_NORMAL)
        {
	      /*-- Sinaliza cuba em Tratamento de Ruido --*/
  		  if( (EST_AVC(cuba).RuidoRap eq VERDADEIRO and 
	   		   AVC.Param[cuba].HabIncRRap eq VERDADEIRO) or
  		  	  (EST_AVC(cuba).RuidoLent eq VERDADEIRO and 
	   		   AVC.Param[cuba].HabIncRLent eq VERDADEIRO) )
	      {
		    sprintf(aux,"%d",ConvCubScoreOper(cuba));
			if((strlen(aux2)+strlen(aux)) >= 180) // limite da pagina
			  break;		
		    if((strlen(aux1)+strlen(aux)+1) >= 20) // fecha a linha
		    {
		      strcat(aux1,"\n"); // coloca new line
		      strcat(aux2,aux1); // atualiza linha no buffer principal
		      memset(aux1,0x00,sizeof(aux1)); // zera linha novamente
		    }
		    else
		    {
		      if(strlen(aux1) != 0) // coloca a virgula
		        strcat(aux1,",");
		    }
            strcat(aux1,aux); // coloca numero da cuba
	      }
	    }
      }
      strcat(aux2,aux1); // coloca no buffer principal restante
	  // envia menu e espera por resposta
	  sprintf( aux, ">>TRATAMENTO RUIDO<<\n%s",aux2);
	  dwError = MandarPrompt( &sParam, aux, iAnsSpc, &sTermAnsw);
	  if( dwError ne 0 )
	    TrataErroColetor( dwError );
      iResposta = strtol( sTermAnsw.pcAnswStrg, &p, 10 );
  	  if( *p ne NULL )
	  {
	    if( strcmp( sTermAnsw.pcAnswStrg, "DP_DINAMICO" ) eq 0 )
	      continue;
	  }
	  switch( iResposta ) // faz tratamento da opcao do menu
	  {
	    case SAIR_MENU:
		  return;
		default:
		  f_rel=FALSO;
	  }
    }
  }
}
