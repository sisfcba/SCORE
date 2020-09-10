/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.4

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II

	ARQUIVO		: CorridaCba.c 

	CONTEUDO	: executa a operacao de corrida no score

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
// CorridaCba - executa a operacao corrida
//
//**************************************************************
void CorridaCba(void)
{
  float	 VAlvo;
  float	 VInst;
  float	 VCicCont;
  time_t HoraAtual;
  char	 Operador[9];
  int	 f_corr;

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
  sParam.ulOptions = DP_ENABLE_SCAN;	
  sParam.iCurRow = 0;			// numero da linha onde o dado sera recebido
  sParam.iCurCol = 0;			// numero da coluna onde o dado sera recebido
  iAnsSpc = 1;					// numero maximo de caracteres que serao lidos
	
  // exibe menu Processo
  f_corr = VERDADEIRO;
  while(f_corr) // loop eterno
  {
	// envia menu e espera por resposta
	  sprintf( aux, "%s\n%s\n%s [%d]\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
				ScoreGetStr(SCORE_MSG_3190),
				ScoreGetStr(SCORE_MSG_3191),
				ScoreGetStr(SCORE_MSG_3192),
				cuba_num,
				ScoreGetStr(SCORE_MSG_3193),
				ScoreGetStr(SCORE_MSG_3194),
				ScoreGetStr(SCORE_MSG_3195),
				ScoreGetStr(SCORE_MSG_3196),
				ScoreGetStr(SCORE_MSG_3197),
				ScoreGetStr(SCORE_MSG_3198),
				ScoreGetStr(SCORE_MSG_3199) );
	dwError = MandarPrompt( &sParam, aux, iAnsSpc, &sTermAnsw);
	if( dwError != 0 )
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
		f_corr = FALSO;
		break;
	  case SAIR_MENU:
		return;
	}
  }
  /*-- Pega a hora atual --*/
  HoraAtual=time(NULL)/TIMES_PER_SEC;

  AlocaSemaf(SEMAF_AVC);
  sprintf( Operador, "%d", NumOperador+1 );
  if (EST_AVC(cuba_ope).Corrida eq FALSO)
  {
	VAlvo=AVC.Ccont[cuba_ope].VAlvo;
	VInst=AVC.Cleit[cuba_ope].Vinst;

  /* Inicio Alteracao - Carlos - 23/06/99 */
  /* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
	VCicCont=AVC.CcontMcp[cuba_ope].RCicContlBruta *
			 AVC.Ccont[cuba_ope].INominalCuba + AVC.Param[cuba_ope].Bemf;
#else
	VCicCont=AVC.CcontMcp[cuba_ope].RCicContlBruta * AVL.INominal +
			 AVC.Param[cuba_ope].Bemf;
#endif
  /* Fim Alteracao - Carlos - 23/06/99 */

    if( EST_AVC(cuba_ope).ManualControle eq FALSO )
	{
	  if( EST_AVC(cuba_ope).ChaveAutMan ne MANUAL )
	  {
	    EST_AVC(cuba_ope).ManualControle = 2;   /* sinaliza manual corrida */
	    EST_AVC(cuba_ope).ChaveAutMan = MANUAL; /* coloca chave em manual */
	    GeraEvento(OPERACAO_MANUAL, cuba_ope, -1, "Corrida ",/* ScoreGetStr(STR_TERMINAL),*/
				   STR_TRACO,VCicCont,VInst,VAlvo);
	  }
	}
	EST_AVC(cuba_ope).Corrida = VERDADEIRO;
	AVC.Cleit[cuba_ope].HoraUltCorr = HoraAtual;
	/*-- Gera evento de corrida --*/
	GeraEvento(INICIO_CORRIDA, cuba_ope, -1, ScoreGetStr(SCORE_MSG_3280), STR_TRACO,
			   VCicCont, VInst, VAlvo);
	if (AVL.HabLogOper)
	  GeraEvento(LOG_OPER_CUBA, cuba_ope, -1, ScoreGetStr(LOG_CORR_OPE), Operador,
				 ScoreGetStr(STR_SINALIZA), STR_TRACO, STR_TRACO);
    AlteracaoTabela(TABELA_EST_AVC);
    LiberaSemaf(SEMAF_AVC);

	sParam.iRow = 0;				// numero da linha onde a mensagem sera mostrada
	sParam.iCol = 0;				// numero da coluna onde a mensagem sera mostrada
	sParam.ulOptions = DP_ENABLE_SCAN;	
	sParam.iCurRow = 0;			// numero da linha onde o dado sera recebido
	sParam.iCurCol = 0;			// numero da coluna onde o dado sera recebido
	iAnsSpc = 1;					// numero maximo de caracteres que serao lidos
    f_corr = VERDADEIRO;
	while(f_corr)
	{
      sprintf( aux, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
				ScoreGetStr(SCORE_MSG_3200),
				ScoreGetStr(SCORE_MSG_3201),
				ScoreGetStr(SCORE_MSG_3202),
				ScoreGetStr(SCORE_MSG_3203),
				ScoreGetStr(SCORE_MSG_3204),
				ScoreGetStr(SCORE_MSG_3205),
				ScoreGetStr(SCORE_MSG_3206),
				ScoreGetStr(SCORE_MSG_3207),
				ScoreGetStr(SCORE_MSG_3208),
				ScoreGetStr(SCORE_MSG_3209) );
	  dwError = MandarPrompt( &sParam, aux, iAnsSpc, &sTermAnsw);
	  if( dwError ne 0 )
	    TrataErroColetor( dwError );
      iResposta = strtol( sTermAnsw.pcAnswStrg, &p, 10 );
  	  if( *p ne NULL )
	    continue;
	  switch( iResposta ) // faz tratamento da opcao do menu
	  {
	    case SAIR_MENU:
		  f_corr = FALSO;
		  break;
	  }
	}		
    AlocaSemaf(SEMAF_AVC);
    if( EST_AVC(cuba_ope).ManualControle eq 2 ) /* coloca estado anterior */
	{
      EST_AVC(cuba_ope).ManualControle = FALSO;
      EST_AVC(cuba_ope).ChaveAutMan = AUTOMATICO; /* coloca chave em automatico */
	  GeraEvento(OPERACAO_AUTOMATICO, cuba_ope, -1, "Corrida "/*ScoreGetStr(STR_TERMINAL)*/);
	}
    AlteracaoTabela(TABELA_EST_AVC);
    LiberaSemaf(SEMAF_AVC);
  }
  else
  {
    LiberaSemaf(SEMAF_AVC);
	sParam.iRow = 0;				// numero da linha onde a mensagem sera mostrada
	sParam.iCol = 0;				// numero da coluna onde a mensagem sera mostrada
	sParam.ulOptions = DP_ENABLE_SCAN;	
	sParam.iCurRow = 0;			// numero da linha onde o dado sera recebido
	sParam.iCurCol = 0;			// numero da coluna onde o dado sera recebido
	iAnsSpc = 1;					// numero maximo de caracteres que serao lidos
	f_corr = VERDADEIRO;
	while(f_corr)
	{
	  sprintf( aux, "\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
			 ScoreGetStr(SCORE_MSG_3220),
			 ScoreGetStr(SCORE_MSG_3221),
			 ScoreGetStr(SCORE_MSG_3222),
			 ScoreGetStr(SCORE_MSG_3223),
			 ScoreGetStr(SCORE_MSG_3224),
			 ScoreGetStr(SCORE_MSG_3225),
			 ScoreGetStr(SCORE_MSG_3226),
			 ScoreGetStr(SCORE_MSG_3227),
			 ScoreGetStr(SCORE_MSG_3228),
			 ScoreGetStr(SCORE_MSG_3229) );
	  dwError = MandarPrompt( &sParam, aux, iAnsSpc, &sTermAnsw);
	  if( dwError ne 0 )
	    TrataErroColetor( dwError );
      iResposta = strtol( sTermAnsw.pcAnswStrg, &p, 10 );
  	  if( *p ne NULL )
	    continue;
	  switch( iResposta ) // faz tratamento da opcao do menu
	  {
	    case SAIR_MENU:
		  f_corr = FALSO;
		  break;
	  }
	}		
    AlocaSemaf(SEMAF_AVC);
    if( EST_AVC(cuba_ope).ManualControle eq 2 ) /* coloca estado anterior */
	{
      EST_AVC(cuba_ope).ManualControle = FALSO;
      EST_AVC(cuba_ope).ChaveAutMan = AUTOMATICO; /* coloca chave em automatico */
	  GeraEvento(OPERACAO_AUTOMATICO, cuba_ope, -1, "Corrida "/*ScoreGetStr(STR_TERMINAL)*/);
	}
    AlteracaoTabela(TABELA_EST_AVC);
    LiberaSemaf(SEMAF_AVC);
  }
}
