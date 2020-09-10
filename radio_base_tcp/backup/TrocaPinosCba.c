/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.4

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II

	ARQUIVO		: TrocaPinos.c 

	CONTEUDO	: executa a operacao de troca de pinos no score

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
// TrocaPinosCba - executa a operacao TrocaPinos
//
//**************************************************************
void TrocaPinosCba(void)
{
  char	 *PMsgParam;
  char	 *PTipoInc;
  char	 StrVInc[9];
  char	 StrTInc[9];
  time_t HoraAtual;
  char	 Operador[9];
  int	 f_pinos;
  int	 Acao;

  int				dwError;
  int				iResposta;
  int				iAnsSpc;						// número máximo de caracteres aceitos na resposta
  SMANDAMSGPARAM	sParam;							// parâmetros da mensagem
  STERMANSW			sTermAnsw;						// resposta proveniente do coletor
  char				*p;

  memset( &sTermAnsw, 0x00, sizeof( sTermAnsw ) );
  memset( &sParam, 	  0x00, sizeof( sParam ) );

  // inicializacao das variaveis.
  sParam.iRow = 0;				// numero da linha onde a mensagem sera mostrada
  sParam.iCol = 0;				// numero da coluna onde a mensagem sera mostrada
  sParam.ulOptions = DP_ENABLE_SCAN | DP_NUMERIC_ONLY;	
  sParam.iCurRow = 0;			// numero da linha onde o dado sera recebido
  sParam.iCurCol = 0;			// numero da coluna onde o dado sera recebido
  iAnsSpc = 1;					// numero maximo de caracteres que serao lidos
	
  // exibe menu Processo
  f_pinos = VERDADEIRO;
  while(f_pinos) // loop eterno
  {
	// envia menu e espera por resposta
    sprintf( aux, "%s\n%s\n%s [%d]\n%s [%d]\n%s\n%s\n%s\n%s\n%s\n%s",
				ScoreGetStr(SCORE_MSG_3230),
				ScoreGetStr(SCORE_MSG_3231),
				ScoreGetStr(SCORE_MSG_3232), cuba_num,
				ScoreGetStr(SCORE_MSG_3233), cuba_num, 
				ScoreGetStr(SCORE_MSG_3234),
				ScoreGetStr(SCORE_MSG_3235),
				ScoreGetStr(SCORE_MSG_3236),
				ScoreGetStr(SCORE_MSG_3237),
				ScoreGetStr(SCORE_MSG_3238),
				ScoreGetStr(SCORE_MSG_3239) );
	dwError = MandarPrompt( &sParam, aux, iAnsSpc, &sTermAnsw);
	if( dwError != 0 )
	  TrataErroColetor( dwError );
    iResposta = strtol( sTermAnsw.pcAnswStrg, &p, 10 );
  	if( *p ne NULL )
	  continue;
	switch( iResposta ) // faz tratamento da opcao do menu
	{
	  case 1:
		f_pinos = FALSO;
	 	Acao = 0; // Ativar
		break;
	  case 2:
		f_pinos = FALSO;
		Acao = 1; // Desativar
		break;
	  case SAIR_MENU:
		return;
	}
  }
  /*-- Pega a hora atual --*/
  HoraAtual=time(NULL)/TIMES_PER_SEC;

  AlocaSemaf(SEMAF_AVC);
  sprintf( Operador, "%d", NumOperador+1 );
  switch(Acao)
  {
	case 0:
	 if (EST_AVC(cuba_ope).TrataTPinos ne VERDADEIRO)
	 {
	   EST_AVC(cuba_ope).TrataTPinos = VERDADEIRO;
	   AVC.Ccont[cuba_ope].ContIncTPinos = -1;
	   AVC.Cleit[cuba_ope].HoraUltTPinos=HoraAtual;
	   PMsgParam = ScoreGetStr(STR_ATIVA);
	   if (AVC.Param[cuba_ope].TipoIncTPinos eq INCREMENTO_LINEAR)
		 PTipoInc = ScoreGetStr(STR_CONST);
	   else
		 PTipoInc = ScoreGetStr(STR_RAMPA);
  #ifdef INCREMENTO_RESISTENCIA
	   sprintf(StrVInc,"%03.1f",AVC.Param[cuba_ope].IncTPinosInic * 1e6);
  #else
	   sprintf(StrVInc,"%03.1f",AVC.Param[cuba_ope].IncTPinosInic * 1000.0);
  #endif
	   sprintf(StrTInc,"%d:%02d",AVC.Param[cuba_ope].TIncTPinos/60,
			   AVC.Param[cuba_ope].TIncTPinos Mod 60);
	   GeraEvento(EV_INC_TROCA_PINOS, cuba_ope, -1, ScoreGetStr(SCORE_MSG_3280),
				  StrTInc, PTipoInc, StrVInc, PMsgParam);
	   if (AVL.HabLogOper)
		 GeraEvento(LOG_OPER_CUBA, cuba_ope, -1, ScoreGetStr(LOG_INC_TROCA_PINOS),
					Operador, StrTInc, StrVInc, PMsgParam);
       sprintf( aux, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
	   			ScoreGetStr(SCORE_MSG_3240),
	   			ScoreGetStr(SCORE_MSG_3241),
	   			" ",
	   			ScoreGetStr(SCORE_MSG_3243), 
	   			" ",
	   			ScoreGetStr(SCORE_MSG_3245),
	   			ScoreGetStr(SCORE_MSG_3246),
	   			ScoreGetStr(SCORE_MSG_3247),
	   			ScoreGetStr(SCORE_MSG_3248),
	   			ScoreGetStr(SCORE_MSG_3249) );
	 }
	 else
       sprintf( aux, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
	   			ScoreGetStr(SCORE_MSG_3240),
	   			ScoreGetStr(SCORE_MSG_3241),
	   			ScoreGetStr(SCORE_MSG_3242),
	   			ScoreGetStr(SCORE_MSG_3243), 
	   			" ",
	   			ScoreGetStr(SCORE_MSG_3245),
	   			ScoreGetStr(SCORE_MSG_3246),
	   			ScoreGetStr(SCORE_MSG_3247),
	   			ScoreGetStr(SCORE_MSG_3248),
	   			ScoreGetStr(SCORE_MSG_3249) );
	 break;
	case 1:
	 if (EST_AVC(cuba_ope).TrataTPinos ne FALSO)
	 {
	   EST_AVC(cuba_ope).TrataTPinos = FALSO;
	   AVC.Ccont[cuba_ope].IncTPinos = 0.0;
	   AVC.Ccont[cuba_ope].ContIncTPinos = -1;
	   AVC.Cleit[cuba_ope].HoraUltTPinos=HoraAtual;
	   strcpy(StrVInc, STR_TRACO);
	   PTipoInc  = STR_TRACO;
	   strcpy(StrTInc, STR_TRACO);
	   PMsgParam = ScoreGetStr(STR_DESATIVA);
	   GeraEvento(EV_INC_TROCA_PINOS, cuba_ope, -1, ScoreGetStr(SCORE_MSG_3280),
				  StrTInc, PTipoInc, StrVInc, PMsgParam);
	   if (AVL.HabLogOper)
		 GeraEvento(LOG_OPER_CUBA, cuba_ope, -1, ScoreGetStr(LOG_INC_TROCA_PINOS),
					Operador, StrTInc, StrVInc, PMsgParam);
       sprintf( aux, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
	   			ScoreGetStr(SCORE_MSG_3240),
	   			ScoreGetStr(SCORE_MSG_3241),
	   			" ",
	   			" ",
	   			ScoreGetStr(SCORE_MSG_3244), 
	   			ScoreGetStr(SCORE_MSG_3245),
	   			ScoreGetStr(SCORE_MSG_3246),
	   			ScoreGetStr(SCORE_MSG_3247),
	   			ScoreGetStr(SCORE_MSG_3248),
	   			ScoreGetStr(SCORE_MSG_3249) );
	 }
	 else
       sprintf( aux, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
	   			ScoreGetStr(SCORE_MSG_3240),
	   			ScoreGetStr(SCORE_MSG_3241),
	   			ScoreGetStr(SCORE_MSG_3242),
	   			" ",
	   			ScoreGetStr(SCORE_MSG_3244), 
	   			ScoreGetStr(SCORE_MSG_3245),
	   			ScoreGetStr(SCORE_MSG_3246),
	   			ScoreGetStr(SCORE_MSG_3247),
	   			ScoreGetStr(SCORE_MSG_3248),
	   			ScoreGetStr(SCORE_MSG_3249) );
	 break;
  }
  AlteracaoTabela(TABELA_EST_AVC);
  LiberaSemaf(SEMAF_AVC);

  sParam.iRow = 0;				// numero da linha onde a mensagem sera mostrada
  sParam.iCol = 0;				// numero da coluna onde a mensagem sera mostrada
  sParam.ulOptions = DP_ENABLE_SCAN;	
  sParam.iCurRow = 0;			// numero da linha onde o dado sera recebido
  sParam.iCurCol = 0;			// numero da coluna onde o dado sera recebido
  iAnsSpc = 1;					// numero maximo de caracteres que serao lidos
  for(;;)
  {
    dwError = MandarPrompt( &sParam, aux, iAnsSpc, &sTermAnsw);
    if( dwError ne 0 )
      TrataErroColetor( dwError );
    iResposta = strtol( sTermAnsw.pcAnswStrg, &p, 10 );
  	if( *p ne NULL )
	  continue;
	switch( iResposta ) // faz tratamento da opcao do menu
	{
	  case SAIR_MENU:
		return;
	}	
  }	  
}
