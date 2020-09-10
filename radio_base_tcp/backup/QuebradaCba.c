/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.4

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II

	ARQUIVO		: QuebradaCba.c 

	CONTEUDO	: executa a operacao de quebrado no score

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
// QuebradaCba - executa a operacao quebrada
//
//**************************************************************
void QuebradaCba()
{
  float	 VAlvo;
  float	 VInst;
  float	 VCicCont;
  time_t HoraAtual;
  char	 Operador[9];
  int	 f_queb;

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

  f_queb = VERDADEIRO;
  while(f_queb) // loop eterno
  {
	// envia menu e espera por resposta
	  sprintf( aux, "%s\n%s\n%s [%d]\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
				ScoreGetStr(SCORE_MSG_3170),
				ScoreGetStr(SCORE_MSG_3171),
				ScoreGetStr(SCORE_MSG_3172),
				cuba_num,
				ScoreGetStr(SCORE_MSG_3173),
				ScoreGetStr(SCORE_MSG_3174),
				ScoreGetStr(SCORE_MSG_3175),
				ScoreGetStr(SCORE_MSG_3176),
				ScoreGetStr(SCORE_MSG_3177),
				ScoreGetStr(SCORE_MSG_3178),
				ScoreGetStr(SCORE_MSG_3179) );
	dwError = MandarPrompt( &sParam, aux, iAnsSpc, &sTermAnsw);
	if( dwError != 0 )
	  TrataErroColetor( dwError );
    iResposta = strtol( sTermAnsw.pcAnswStrg, &p, 10 );
  	if( *p ne NULL )
	  continue;
	switch( iResposta ) // faz tratamento da opcao do menu
	{
	  case 1:
		f_queb = FALSO;
		break;
	  case SAIR_MENU:
		return;
	}
  }
  /*-- Pega a hora atual --*/
  HoraAtual=time(NULL)/TIMES_PER_SEC;

  AlocaSemaf(SEMAF_AVC);
  sprintf( Operador, "%d", NumOperador+1 );
  if (EST_AVC(cuba_ope).Quebrada eq FALSO)
  {
	EST_AVC(cuba_ope).Quebrada = VERDADEIRO;
	AVC.Cleit[cuba_ope].HoraUltQueb = HoraAtual;

	/*-- Gera evento de quebrada --*/
	VAlvo=AVC.Ccont[cuba_ope].VAlvo;
	VInst=AVC.Cleit[cuba_ope].Vinst;

	/* Inicio Alteracao - Carlos - 23/06/99 */
	/* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
	VCicCont=AVC.CcontMcp[cuba_ope].RCicContlBruta *
			 AVC.Ccont[cuba_ope].INominalCuba + AVC.Param[cuba_ope].Bemf;
#else
	VCicCont=AVC.CcontMcp[cuba_ope].RCicContlBruta*AVL.INominal+
			 AVC.Param[cuba_ope].Bemf;
#endif
	/* Fim Alteracao - Carlos - 23/06/99 */

	GeraEvento(INICIO_QUEBRADA, cuba_ope, -1, ScoreGetStr(SCORE_MSG_3280), STR_TRACO,
			   VCicCont, VInst, VAlvo);
	if (AVL.HabLogOper)
	  GeraEvento(LOG_OPER_CUBA, cuba_ope, -1, ScoreGetStr(LOG_QUEB_OPE), Operador,
				 ScoreGetStr(STR_SINALIZA), STR_TRACO, STR_TRACO);
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
    sprintf( aux, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
			ScoreGetStr(SCORE_MSG_3180),
			ScoreGetStr(SCORE_MSG_3181),
			ScoreGetStr(SCORE_MSG_3182),
			ScoreGetStr(SCORE_MSG_3183),
			ScoreGetStr(SCORE_MSG_3184),
			ScoreGetStr(SCORE_MSG_3185),
			ScoreGetStr(SCORE_MSG_3186),
			ScoreGetStr(SCORE_MSG_3187),
			ScoreGetStr(SCORE_MSG_3188),
			ScoreGetStr(SCORE_MSG_3189) );
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
