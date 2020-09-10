/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.4

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II

	ARQUIVO		: ProcessaMetalCba.c 

	CONTEUDO	: Menu de entrada de dados de Processo

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
// ProcessaMetalCba - menu principal de dados de Porcesso CBA
//
//**************************************************************
void ProcessaMetalCba()
{
  // Declaracao de variaveis
  int				f_loop;
  int				dwError;
  int				iResposta;
  int				iAnsSpc;						// número máximo de caracteres aceitos na resposta
  SMANDAMSGPARAM	sParam;							// parâmetros da mensagem
  STERMANSW			sTermAnsw;						// resposta proveniente do coletor
  char				*p;
  
  memset( &sTermAnsw, 0x00, sizeof( sTermAnsw ) );
  memset( &sParam, 	  0x00, sizeof( sParam ) );

  f_loop = VERDADEIRO;
  while( f_loop )
  {
  	// inicializacao das variaveis.
  	sParam.iRow = 0;		// numero da linha onde a mensagem sera mostrada
  	sParam.iCol = 0;		// numero da coluna onde a mensagem sera mostrada
  	sParam.ulOptions = DP_ENABLE_SCAN;	
 	sParam.iCurRow = 0;		// numero da linha onde o dado sera recebido
  	sParam.iCurCol = 0;		// numero da coluna onde o dado sera recebido
  	iAnsSpc = 1;			// numero maximo de caracteres que serao lidos
	sprintf( aux, "%s[%d]\n1>%s\n2>%s\n3>%s\n4>%s",
		ScoreGetStr(SCORE_MSG_3300),cuba_num,				
		ScoreGetStr(SCORE_MSG_3301),
		ScoreGetStr(SCORE_MSG_3302),
		ScoreGetStr(SCORE_MSG_3303),
		ScoreGetStr(SCORE_MSG_3304) );
	sprintf( aux1, "%s\n%s\n%s\n%s\n8>%s[%d]\n9>%s",
		aux,		
		ScoreGetStr(SCORE_MSG_3305),
		ScoreGetStr(SCORE_MSG_3306),
		ScoreGetStr(SCORE_MSG_3307),
		ScoreGetStr(SCORE_MSG_3308),cuba_num,
		ScoreGetStr(SCORE_MSG_3309) );
	dwError = MandarPrompt( &sParam, aux1, iAnsSpc, &sTermAnsw );
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
	  case 1: // Metal 1
		TrataMetal1Cba();
		break;
	  case 2: // Materias Primas
		TrataMateriasPrimasCba();
		break;
	  case 3: // Metal 2
		TrataMetal2Cba();
		break;
	  case 4: // Anodo
		TrataAnodoCba();
		break;
	  case 8:
		cuba(NULL);
		break; 
	  case 9:
		return;
	}
  }
}

//**************************************************************
//
// TrataMetal1Cba 
//
//**************************************************************
void TrataMetal1Cba()
{
  // Declaracao de variaveis
  int				aux_int;
  int				aux_float;
  int				f_loop;
  int				dwError;
  int				iResposta;
  int				iAnsSpc;						// número máximo de caracteres aceitos na resposta
  SMANDAMSGPARAM	sParam;							// parâmetros da mensagem
  STERMANSW			sTermAnsw;						// resposta proveniente do coletor
  char				*p;
  
  memset( &sTermAnsw, 0x00, sizeof( sTermAnsw ) );
  memset( &sParam, 	  0x00, sizeof( sParam ) );

  f_loop = VERDADEIRO;
  while( f_loop )
  {
  	// inicializacao das variaveis.
  	sParam.iRow = 0;		// numero da linha onde a mensagem sera mostrada
  	sParam.iCol = 0;		// numero da coluna onde a mensagem sera mostrada
  	sParam.ulOptions = DP_ENABLE_SCAN;	
 	sParam.iCurRow = 0;		// numero da linha onde o dado sera recebido
  	sParam.iCurCol = 0;		// numero da coluna onde o dado sera recebido
  	iAnsSpc = 1;			// numero maximo de caracteres que serao lidos
	sprintf( aux, "%s[%d]\n1>%-11.11s:%1.*f\n2>%-11.11s:%1.*f\n3>%-11.11s:%1.*f\n4>%-11.11s:%1.*f\n5>%-11.11s:%1.*f\n\n\n8>%s[%d]\n%s",
		ScoreGetStr(SCORE_MSG_3490),cuba_num,				
		GetNomeArqVar(0),GetPrecArqVar(0),SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Banho,
		GetNomeArqVar(1),GetPrecArqVar(1),SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Metal,
		GetNomeArqVar(2),GetPrecArqVar(2),(float)SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Temperatura,
		GetNomeArqVar(3),GetPrecArqVar(3),SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Fluoreto,
		GetNomeArqVar(4),GetPrecArqVar(4),SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Fluorita,
		ScoreGetStr(SCORE_MSG_3498),cuba_num,
		ScoreGetStr(SCORE_MSG_3499) );
	dwError = MandarPrompt( &sParam, aux, iAnsSpc, &sTermAnsw );
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
	  case 1: // banho
		aux_float = SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Banho;
		TrataProcessoMetalCba( 0, (byte *)&SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Banho );
		if(aux_float != SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Banho)
		  AVL.Trab.DataOperacional = time(NULL); // atualiza a data operacional
		break;
	  case 2: // metal
		aux_float = SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Metal;
		TrataProcessoMetalCba( 1, (byte *)&SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Metal );
		if(aux_float != SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Metal)
		  AVL.Trab.DataOperacional = time(NULL); // atualiza a data operacional
		break;
	  case 3: // temperatura
		aux_int = SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Temperatura;
		TrataProcessoMetalCba( 2, (byte *)&SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Temperatura );
		if(aux_int != SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Temperatura)
		  AVL.Trab.DataOperacional = time(NULL); // atualiza a data operacional
		break;
	  case 4: // fluoreto
		aux_float = SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Fluoreto;
		TrataProcessoMetalCba( 3, (byte *)&SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Fluoreto );
		if(aux_float != SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Fluoreto)
		  AVL.Trab.DataAnalise = time(NULL); // atualiza a data analise
		break;
	  case 5: // fluorita
		aux_float = SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Fluorita;
		TrataProcessoMetalCba( 4, (byte *)&SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Fluorita );
		if(aux_float != SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Fluorita)
		  AVL.Trab.DataAnalise = time(NULL); // atualiza a data analise
	    break;
	  case 8:
		cuba(NULL);
		break; 
	  case SAIR_MENU:
		return;
	}
  }
}

//**************************************************************
//
// TrataMateriasPrimasCba 
//
//**************************************************************
void TrataMateriasPrimasCba()
{
  // Declaracao de variaveis
  int				f_loop;
  int				dwError;
  int				iResposta;
  int				iAnsSpc;						// número máximo de caracteres aceitos na resposta
  SMANDAMSGPARAM	sParam;							// parâmetros da mensagem
  STERMANSW			sTermAnsw;						// resposta proveniente do coletor
  char				*p;
  
  memset( &sTermAnsw, 0x00, sizeof( sTermAnsw ) );
  memset( &sParam, 	  0x00, sizeof( sParam ) );

  f_loop = VERDADEIRO;
  while( f_loop )
  {
  	// inicializacao das variaveis.
  	sParam.iRow = 0;		// numero da linha onde a mensagem sera mostrada
  	sParam.iCol = 0;		// numero da coluna onde a mensagem sera mostrada
  	sParam.ulOptions = DP_ENABLE_SCAN;	
 	sParam.iCurRow = 0;		// numero da linha onde o dado sera recebido
  	sParam.iCurCol = 0;		// numero da coluna onde o dado sera recebido
  	iAnsSpc = 1;			// numero maximo de caracteres que serao lidos
	sprintf( aux, "%s[%d]\n1>%-11.11s:%1.*f\n2>%-11.11s:%1.*f\n3>%-11.11s:%1.*f\n4>%-11.11s:%1.*f\n5>%-11.11s:%1.*f\n6>%-11.11s:%1.*f\n\n8>%s[%d]\n9>%s",
		ScoreGetStr(SCORE_MSG_3302),cuba_num,				
		GetNomeArqVar(5),GetPrecArqVar(5),(float)SUPERV_AVC(cuba_ope).Sup.CNF_SUP.CrioSint,
		GetNomeArqVar(6),GetPrecArqVar(6),(float)SUPERV_AVC(cuba_ope).Sup.CNF_SUP.CrioAciq,
		GetNomeArqVar(7),GetPrecArqVar(7),(float)SUPERV_AVC(cuba_ope).Sup.CNF_SUP.CrioRecu,
		GetNomeArqVar(8),GetPrecArqVar(8),(float)SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Fluoreto,
		GetNomeArqVar(9),GetPrecArqVar(9),(float)SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Fluorita,
		GetNomeArqVar(10),GetPrecArqVar(10),(float)SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Barrilha,
		ScoreGetStr(SCORE_MSG_3308),cuba_num,
		ScoreGetStr(SCORE_MSG_3309) );
	dwError = MandarPrompt( &sParam, aux, iAnsSpc, &sTermAnsw );
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
	  case 1: // criosint
		TrataProcessoMetalCba( 5, (byte *)&SUPERV_AVC(cuba_ope).Sup.CNF_SUP.CrioSint );
		break;
	  case 2: // crioaciq
		TrataProcessoMetalCba( 6, (byte *)&SUPERV_AVC(cuba_ope).Sup.CNF_SUP.CrioAciq );
		break;
	  case 3: // criorecu
		TrataProcessoMetalCba( 7, (byte *)&SUPERV_AVC(cuba_ope).Sup.CNF_SUP.CrioRecu );
		break;
	  case 4: // fluoreto
		TrataProcessoMetalCba( 8, (byte *)&SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Fluoreto );
		break;
	  case 5: // fluorita
		TrataProcessoMetalCba( 9, (byte *)&SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Fluorita );
	    break;
	  case 6: // barrilha
		TrataProcessoMetalCba( 10, (byte *)&SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Barrilha );
	    break;
	  case 8:
		cuba(NULL);
		break; 
	  case 9:
		return;
	}
  }
}

//**************************************************************
//
// TrataMetal2Cba 
//
//**************************************************************
void TrataMetal2Cba()
{
  // Declaracao de variaveis
  int				f_loop;
  int				dwError;
  int				iResposta;
  int				iAnsSpc;						// número máximo de caracteres aceitos na resposta
  SMANDAMSGPARAM	sParam;							// parâmetros da mensagem
  STERMANSW			sTermAnsw;						// resposta proveniente do coletor
  char				*p;
  
  memset( &sTermAnsw, 0x00, sizeof( sTermAnsw ) );
  memset( &sParam, 	  0x00, sizeof( sParam ) );

  f_loop = VERDADEIRO;
  while( f_loop )
  {  	// inicializacao das variaveis.
  	sParam.iRow = 0;		// numero da linha onde a mensagem sera mostrada
  	sParam.iCol = 0;		// numero da coluna onde a mensagem sera mostrada
  	sParam.ulOptions = DP_ENABLE_SCAN;	
 	sParam.iCurRow = 0;		// numero da linha onde o dado sera recebido
  	sParam.iCurCol = 0;		// numero da coluna onde o dado sera recebido
  	iAnsSpc = 1;			// numero maximo de caracteres que serao lidos
	sprintf( aux, "%s[%d]\n1>%-11.11s:%s\n2>%-11.11s:%s\n3>%-11.11s:%s\n4>%-11.11s:%s\n5>%-11.11s:%s\n6>%-11.11s:%s\n\n8>%s[%d]\n9>%s",
		ScoreGetStr(SCORE_MSG_3303),cuba_num,				
		GetNomeArqVar(11),condicao4(SUPERV_AVC(cuba_ope).Sup.CNF_SUP.OperarTurno),
		GetNomeArqVar(12),condicao(SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Carvao),
		GetNomeArqVar(13),condicao(SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Atrasado),
		GetNomeArqVar(14),condicao(SUPERV_AVC(cuba_ope).Sup.CNF_SUP.FundoSujo),
		GetNomeArqVar(15),condicao3(SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Acidez),
		GetNomeArqVar(16),condicao2(SUPERV_AVC(cuba_ope).Sup.CNF_SUP.FornoAbrindo),
		ScoreGetStr(SCORE_MSG_3308),cuba_num,
		ScoreGetStr(SCORE_MSG_3309) );
	dwError = MandarPrompt( &sParam, aux, iAnsSpc, &sTermAnsw );
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
	  case 1: // Operar/turno
		++SUPERV_AVC(cuba_ope).Sup.CNF_SUP.OperarTurno;
		if( SUPERV_AVC(cuba_ope).Sup.CNF_SUP.OperarTurno > AVL.NumTurnos )
		  SUPERV_AVC(cuba_ope).Sup.CNF_SUP.OperarTurno = 0;
		break;
	  case 2: // carvao
		++SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Carvao;
		if( SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Carvao > (short)GetMaxArqVar(12) )
		  SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Carvao = 0;
		break;
	  case 3: // atrasado
		++SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Atrasado;
		if( SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Atrasado > (short)GetMaxArqVar(13) )
		  SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Atrasado = 0;
		break;
	  case 4: // fundo sujo
		++SUPERV_AVC(cuba_ope).Sup.CNF_SUP.FundoSujo;
		if( SUPERV_AVC(cuba_ope).Sup.CNF_SUP.FundoSujo > (short)GetMaxArqVar(14) )
		  SUPERV_AVC(cuba_ope).Sup.CNF_SUP.FundoSujo = 0;
		break;
	  case 5: // acidez
		++SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Acidez;
		if( SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Acidez > (short)GetMaxArqVar(15) )
		  SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Acidez = 0;
		break;
	  case 6: // forno abrindo
		++SUPERV_AVC(cuba_ope).Sup.CNF_SUP.FornoAbrindo;
		if( SUPERV_AVC(cuba_ope).Sup.CNF_SUP.FornoAbrindo > (short)GetMaxArqVar(16) )
		  SUPERV_AVC(cuba_ope).Sup.CNF_SUP.FornoAbrindo = 0;
		break;
	  case 8:
		cuba(NULL);
		break; 
	  case 9:
		return;
	}
  }
}

//**************************************************************
//
// TrataAnodoCba
//
//**************************************************************
void TrataAnodoCba()
{
  // Declaracao de variaveis
  int				f_loop;
  int				dwError;
  int				iResposta;
  int				iAnsSpc;						// número máximo de caracteres aceitos na resposta
  SMANDAMSGPARAM	sParam;							// parâmetros da mensagem
  STERMANSW			sTermAnsw;						// resposta proveniente do coletor
  char				*p;
  
  memset( &sTermAnsw, 0x00, sizeof( sTermAnsw ) );
  memset( &sParam, 	  0x00, sizeof( sParam ) );

  f_loop = VERDADEIRO;
  while( f_loop )
  {
  	// inicializacao das variaveis.
  	sParam.iRow = 0;		// numero da linha onde a mensagem sera mostrada
  	sParam.iCol = 0;		// numero da coluna onde a mensagem sera mostrada
  	sParam.ulOptions = DP_ENABLE_SCAN;	
 	sParam.iCurRow = 0;		// numero da linha onde o dado sera recebido
  	sParam.iCurCol = 0;		// numero da coluna onde o dado sera recebido
  	iAnsSpc = 1;			// numero maximo de caracteres que serao lidos
	sprintf( aux, "%s[%d]\n1>%-11.11s:%1.*f\n2>%-11.11s:%1.*f\n3>%-11.11s:%1.*f\n4>%-11.11s:%1.*f\n5>%-11.11s:%1.*f\n6>%11.11s:%1.*f\n\n8>%s[%d]\n9>%s",
		ScoreGetStr(SCORE_MSG_3304),cuba_num,				
		GetNomeArqVar(17),GetPrecArqVar(17),SUPERV_AVC(cuba_ope).Sup.CNF_SUP.VazioPasta,
		GetNomeArqVar(18),GetPrecArqVar(18),SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Desfilamento,
		GetNomeArqVar(19),GetPrecArqVar(19),SUPERV_AVC(cuba_ope).Sup.CNF_SUP.AlturaAnodo,
		GetNomeArqVar(20),GetPrecArqVar(20),SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Flanco,
		GetNomeArqVar(21),GetPrecArqVar(21),SUPERV_AVC(cuba_ope).Sup.CNF_SUP.QuedaCatodica,
		GetNomeArqVar(22),GetPrecArqVar(22),SUPERV_AVC(cuba_ope).Sup.CNF_SUP.QuedaAnodica,
		ScoreGetStr(SCORE_MSG_3308),cuba_num,
		ScoreGetStr(SCORE_MSG_3309) );
	dwError = MandarPrompt( &sParam, aux, iAnsSpc, &sTermAnsw );
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
	  case 1: // vazio de pasta
		TrataProcessoMetalCba( 17, (byte *)&SUPERV_AVC(cuba_ope).Sup.CNF_SUP.VazioPasta );
		break;
	  case 2: // desfilamento
		TrataProcessoMetalCba( 18, (byte *)&SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Desfilamento );
		break;
	  case 3: // altura anodo
		TrataProcessoMetalCba( 19, (byte *)&SUPERV_AVC(cuba_ope).Sup.CNF_SUP.AlturaAnodo );
		break;
	  case 4: // flanco
		TrataProcessoMetalCba( 20, (byte *)&SUPERV_AVC(cuba_ope).Sup.CNF_SUP.Flanco );
		break;
	  case 5: // queda catodica
		TrataProcessoMetalCba( 21, (byte *)&SUPERV_AVC(cuba_ope).Sup.CNF_SUP.QuedaCatodica );
	    break;
	  case 6: // queda anodica
		TrataProcessoMetalCba( 22, (byte *)&SUPERV_AVC(cuba_ope).Sup.CNF_SUP.QuedaAnodica );
	    break;
	  case 8:
		cuba(NULL);
		break; 
	  case 9:
		return;
	}
  }
}

//**************************************************************
//
// TrataProcessoMetalCba
//
//**************************************************************
void TrataProcessoMetalCba( int Var, byte *Valor )
{
  // Declaracao de variaveis
  int				f_loop;
  int				dwError;
  double			iResposta;
  int				iAnsSpc;						// número máximo de caracteres aceitos na resposta
  SMANDAMSGPARAM	sParam;							// parâmetros da mensagem
  STERMANSW			sTermAnsw;						// resposta proveniente do coletor
  char				*p;
  float				valor;
  short				v_short;
  int				v_int;
  float				v_float;
  long				v_long;
  double			v_double;
  byte				v_byte;
  
  memset( &sTermAnsw, 0x00, sizeof( sTermAnsw ) );
  memset( &sParam, 	  0x00, sizeof( sParam ) );

  f_loop = VERDADEIRO;
  while( f_loop )
  {
  	// inicializacao das variaveis.
  	sParam.iRow = 0;		// numero da linha onde a mensagem sera mostrada
  	sParam.iCol = 0;		// numero da coluna onde a mensagem sera mostrada
  	sParam.ulOptions = DP_CURSOR | DP_DISPLAY_DATA | DP_ENABLE_SCAN;	
 	sParam.iCurRow = 3;		// numero da linha onde o dado sera recebido
  	sParam.iCurCol = 12;	// numero da coluna onde o dado sera recebido
  	iAnsSpc = 6;			// numero maximo de caracteres que serao lidos
	switch( GetTipoArqVar(Var) )
	{
	  case SHORT_INT:
		memcpy( &v_short,Valor,sizeof(short));
		valor = (float)v_short;
		break;
	  case INT:
		memcpy(&v_int,Valor,sizeof(int));
		valor = (float)v_int;
		break;
	  case FLOAT:
		memcpy(&v_float,Valor,sizeof(float));
		valor = (float)v_float;
		break;
	  case LONG:
		memcpy(&v_long,Valor,sizeof(long));
		valor = (float)v_long;
		break;
	  case DOUBLE:
		memcpy(&v_double,Valor,sizeof(double));
		valor = (float)v_double;
		break;
	  case BYTE:
		memcpy(&v_byte,Valor,sizeof(char));
		valor = (float)v_byte;
		break;
	}
	sprintf( aux, "%s[%d]\n(%s) %1.*f - %1.*f\n%s:%1.*f\n%s:\n\n%s\n%s",
		GetNomeArqVar(Var),cuba_num,GetUEArqVar(Var),
		GetPrecArqVar(Var),GetMinArqVar(Var),GetPrecArqVar(Var),GetMaxArqVar(Var),
		ScoreGetStr(SCORE_MSG_3320),
		GetPrecArqVar(Var),valor,
		ScoreGetStr(SCORE_MSG_3321),
		ScoreGetStr(SCORE_MSG_3322),
		ScoreGetStr(SCORE_MSG_3323) ); 
	dwError = MandarPrompt( &sParam, aux, iAnsSpc, &sTermAnsw );
	if( dwError ne 0 )
	  TrataErroColetor( dwError );
    if( strlen( sTermAnsw.pcAnswStrg ) == 0 )
	  break; // aborta o loop
   	iResposta = strtod( sTermAnsw.pcAnswStrg, &p );
	if( *p ne NULL )
  	  continue;
	else
	{
	  if( iResposta < GetMinArqVar(Var) || iResposta > GetMaxArqVar(Var) )
	    continue;
	}
	switch( GetTipoArqVar(Var) )
	{
	  case SHORT_INT:
		v_short = (short)iResposta;
		memcpy( Valor,(void *)&v_short,sizeof(short));
		return;
	  case INT:
		v_int = (int)iResposta;
		memcpy( Valor,(void *)&v_int,sizeof(int));
		return;
	  case FLOAT:
		v_float = (float)iResposta;
		memcpy( Valor,(void *)&v_float,sizeof(float));
		return;
	  case LONG:
		v_long = (long)iResposta;
		memcpy( Valor,(void *)&v_long,sizeof(long));
		return;
	  case DOUBLE:
		v_double = (double)iResposta;
		memcpy( Valor,(void *)&v_double,sizeof(double));
		return;
	  case BYTE:
		v_byte = (byte)iResposta;
		memcpy( Valor,(void *)&v_byte,sizeof(char));
		return;
	}
  }
} 

//**************************************************************
//
// GetNomeArqVarCba 
//
//**************************************************************
char *GetNomeArqVarCba(int Campo)
{
  int	i;
  char	label[20];
  sprintf( label, "Metais%d", Campo );
  for( i = 0; i < MAX_VARIAVEIS; ++i )
  {
    if( strcmp( Arqvar->Tabela[TAB_SUP_AVC].Var[i].Tag, label ) == 0 )
      return( Arqvar->Tabela[TAB_SUP_AVC].Var[i].NomeVar );
  }
  return( Arqvar->Tabela[TAB_SUP_AVC].Var[0].NomeVar );
}

//**************************************************************
//
// GetUEArqVarCba 
//
//**************************************************************
char *GetUEArqVarCba(int Campo)
{
  int	i;
  char	label[20];
  sprintf( label, "Metais%d", Campo );
  for( i = 0; i < MAX_VARIAVEIS; ++i )
  {
    if( strcmp( Arqvar->Tabela[TAB_SUP_AVC].Var[i].Tag, label ) == 0 )
      return( Arqvar->Tabela[TAB_SUP_AVC].Var[i].UEvar );
  }
  return( Arqvar->Tabela[TAB_SUP_AVC].Var[0].UEvar );
}

//**************************************************************
//
// GetPrecArqVarCba
//
//**************************************************************
short GetPrecArqVarCba(int Campo)
{
  int	i;
  char	label[20];
  sprintf( label, "Metais%d", Campo );
  for( i = 0; i < MAX_VARIAVEIS; ++i )
  {
    if( strcmp( Arqvar->Tabela[TAB_SUP_AVC].Var[i].Tag, label ) == 0 )
      return( (short)Arqvar->Tabela[TAB_SUP_AVC].Var[i].PrecVar );
  }
  return( 0 );
}

//**************************************************************
//
// GetMaxArqVarCba 
//
//**************************************************************
float GetMaxArqVarCba(int Campo)
{
  int	i;
  char	label[20];
  sprintf( label, "Metais%d", Campo );
  for( i = 0; i < MAX_VARIAVEIS; ++i )
  {
    if( strcmp( Arqvar->Tabela[TAB_SUP_AVC].Var[i].Tag, label ) == 0 )
      return( Arqvar->Tabela[TAB_SUP_AVC].Var[i].LimSup );
  }
  return( 0.0 );
}

//**************************************************************
//
// GetMinArqVarCba 
//
//**************************************************************
float GetMinArqVarCba(int Campo)
{
  int	i;
  char	label[20];
  sprintf( label, "Metais%d", Campo );
  for( i = 0; i < MAX_VARIAVEIS; ++i )
  {
    if( strcmp( Arqvar->Tabela[TAB_SUP_AVC].Var[i].Tag, label ) == 0 )
      return( Arqvar->Tabela[TAB_SUP_AVC].Var[i].LimInf );
  }
  return( 0.0 );
}

//**************************************************************
//
// GetTipoArqVarCba
//
//**************************************************************
short GetTipoArqVarCba(int Campo)
{
  int	i;
  char	label[20];
  sprintf( label, "Metais%d", Campo );
  for( i = 0; i < MAX_VARIAVEIS; ++i )
  {
    if( strcmp( Arqvar->Tabela[TAB_SUP_AVC].Var[i].Tag, label ) == 0 )
      return( (short)Arqvar->Tabela[TAB_SUP_AVC].Var[i].TipoVar );
  }
  return( 0 );
}
