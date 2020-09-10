/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.4

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II

	ARQUIVO		: GeralProcessoCba.c 

	CONTEUDO	: relatorio geral p/ uma cuba (macro)
	
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
// ProcessoCba - relatorio geral
//
//**************************************************************
void ProcessoCba(void)
{
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
  for(;;) // loop eterno
  {
	// envia menu e espera por resposta
	  sprintf( aux, "%s %d\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
				ScoreGetStr(SCORE_MSG_3270), cuba_num,		
				ScoreGetStr(SCORE_MSG_3271),
				ScoreGetStr(SCORE_MSG_3272),
				ScoreGetStr(SCORE_MSG_3273),
				ScoreGetStr(SCORE_MSG_3274),
				ScoreGetStr(SCORE_MSG_3275),
				ScoreGetStr(SCORE_MSG_3276),
				ScoreGetStr(SCORE_MSG_3277),
				ScoreGetStr(SCORE_MSG_3278),
				ScoreGetStr(SCORE_MSG_3279) );
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
		while( SinalSituacaoCba(cuba_ope) );
		break;
	  case SAIR_MENU:
		return;
	}
  }
}

//**************************************************************
//
// SinalSituacaoCba
//
//**************************************************************
int SinalSituacaoCba(int Cuba)
{
  char	Estado[10];
  float	VErro;
  float	Derivada;
  long	TempoUltEa;
  long	TempoRLent;
  long	TempoRRap;
  long	HoraAtual;
  char	TempoRLentS[6];
  char	TempoRRapidS[6];
  char  ClasRLent[6];
  char  ClasRRapid[6];
  char	TempoUltEaS[7];
  char	DerivadaS[8];
  char  VErroS[8];

  int				dwError;
  int				iResposta;
  int				iAnsSpc;						// número máximo de caracteres aceitos na resposta
  SMANDAMSGPARAM	sParam;							// parâmetros da mensagem
  STERMANSW			sTermAnsw;						// resposta proveniente do coletor
  char				*p;

  HoraAtual = time(NULL)/TIMES_PER_SEC;

  /*-- Sinaliza cuba em Manual-Local. --*/
  strcpy(Estado,"--------");
  if ( EST_AVC(Cuba).ChaveLocRem eq LOCAL ) 
  {
	strcpy(Estado,ScoreGetStr(MAN_LOC));
  } 
  else 
  {
	/*-- Sinaliza cuba em Manual-Remoto. --*/
	if ( EST_AVC(Cuba).ChaveAutMan eq MANUAL ) 
	{
	  if (EST_AVC(Cuba).ManualControle)
		strcpy(Estado,ScoreGetStr(MAN_CTR));	/* Manual pelo controle */
	  else
		strcpy(Estado,ScoreGetStr(MAN_REM));
	} 
	else 
	{
	  if ( EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL)
	  {
		/*-- Sinaliza cuba em Efeito Anodico. --*/
		if ( EST_AVC(Cuba).Ea eq VERDADEIRO ) 
		  strcpy(Estado, ScoreGetStr(EA));
		else
		{
		  /*-- Sinaliza cuba em Corrida. --*/
		  if ( EST_AVC(Cuba).Corrida eq VERDADEIRO ) 
			strcpy(Estado,ScoreGetStr(CORRIDA));
		  else
		  {
			/*-- Sinaliza cuba em Quebrada --*/
			if ( EST_AVC(Cuba).Quebrada eq VERDADEIRO ) 
			  strcpy(Estado,ScoreGetStr(QUEBRADA));
		  }
		}
 	  }
	}
  }
  VErro = AVC.Ccont[Cuba].VErro;
  sprintf( VErroS, "%5.2f", VErro );

  TempoUltEa = HoraAtual - AVC.Ea[Cuba].EaHoraInicio;
  MontaHoraMin(TempoUltEa/60, TempoUltEaS, "%03d:%02d");

  Derivada = AVC.Ea[Cuba].RSuaveDerivH*1e6;
  sprintf( DerivadaS, "%5.2f", Derivada );

  if( EST_AVC(Cuba).RuidoLent eq VERDADEIRO and
	  AVC.Param[Cuba].HabIncRLent eq VERDADEIRO )
  {
	switch( AVC.Ruido[Cuba].TipoRLent )
	{
	  case RUIDO_NIVEL1:
	  case RUIDO_NIVEL2:
	  case RUIDO_NIVEL3:
	  case RUIDO_NIVEL4:
	  case RUIDO_NIVEL5:
		   strcpy(ClasRLent,ScoreGetStr(RUI_NIVEL1+(AVC.Ruido[Cuba].TipoRLent-1)));
		   break;
	  case SEM_RUIDO:
		   strcpy(ClasRLent,"-----");
		   break;
	  default:
		   strcpy(ClasRLent,"Erro ");
	}
  }
  else
	strcpy(ClasRLent, "-----" );

  /*-- Calculo da duracao do Ruido Lento da cuba --*/
  if ( EST_AVC(Cuba).RuidoLent eq VERDADEIRO and
	   AVC.Param[Cuba].HabIncRLent eq VERDADEIRO )
  {
	TempoRLent = HoraAtual - AVC.Ruido[Cuba].HoraInicioRLent;  
	MontaHoraMin(TempoRLent/60, TempoRLentS, "%02d:%02d");
  }
  else
	strcpy(TempoRLentS, "--:--" );

  if ( EST_AVC(Cuba).RuidoRap eq VERDADEIRO and
	   AVC.Param[Cuba].HabIncRRap eq VERDADEIRO )
  {
	switch ( AVC.Ruido[Cuba].TipoRRap )
	{
	  case RUIDO_NIVEL1:
	  case RUIDO_NIVEL2:
	  case RUIDO_NIVEL3:
	  case RUIDO_NIVEL4:
	  case RUIDO_NIVEL5:
		   strcpy(ClasRRapid,ScoreGetStr(RUI_NIVEL1+(AVC.Ruido[Cuba].TipoRRap-1)));
		   break;
	  case SEM_RUIDO:
		   strcpy(ClasRRapid,"-----");
		   break;
	  default:
		   strcpy(ClasRRapid,"Erro ");
	}
  }
  else
	strcpy(ClasRRapid,"-----");

  /*-- Calculo da duracao do Ruido Rapido da cuba --*/
  if ( EST_AVC(Cuba).RuidoRap eq VERDADEIRO and
	   AVC.Param[Cuba].HabIncRRap eq VERDADEIRO )
  {
	TempoRRap = HoraAtual - AVC.Ruido[Cuba].HoraInicioRRap;  
	MontaHoraMin(TempoRRap/60, TempoRRapidS, "%02d:%02d");
  }
  else
	strcpy(TempoRRapidS,"--:--");

  memset( &sTermAnsw, 0x00, sizeof( sTermAnsw ) );
  memset( &sParam, 	  0x00, sizeof( sParam ) );

  // inicializacao das variaveis.
  sParam.iRow = 0;				// numero da linha onde a mensagem sera mostrada
  sParam.iCol = 0;				// numero da coluna onde a mensagem sera mostrada
  sParam.ulOptions = DP_ENABLE_SCAN | DP_NUMERIC_ONLY;	
  sParam.iCurRow = 0;			// numero da linha onde o dado sera recebido
  sParam.iCurCol = 0;			// numero da coluna onde o dado sera recebido
  iAnsSpc = 1;					// numero maximo de caracteres que serao lidos
	
  for(;;) // loop eterno
  {
	// envia menu e espera por resposta
	  sprintf( aux, "%s %d\n%s\n%s%s\n%s%s\n%s%s\n%s%s %s\n%s%s %s\n%s%s\n%s\n%s",
			 ScoreGetStr(SCORE_MSG_3420), cuba_num,
			 ScoreGetStr(SCORE_MSG_3421),
			 ScoreGetStr(SCORE_MSG_3422), Estado,
			 ScoreGetStr(SCORE_MSG_3423), VErroS,
			 ScoreGetStr(SCORE_MSG_3424), DerivadaS,
		  	 ScoreGetStr(SCORE_MSG_3425), ClasRLent, TempoRLentS,
		  	 ScoreGetStr(SCORE_MSG_3426), ClasRRapid, TempoRRapidS,
			 ScoreGetStr(SCORE_MSG_3427), TempoUltEaS,
			 ScoreGetStr(SCORE_MSG_3428),
			 ScoreGetStr(SCORE_MSG_3279) );
	dwError = MandarPrompt( &sParam, aux, iAnsSpc, &sTermAnsw);
	if( dwError ne 0 )
	  TrataErroColetor( dwError );
    iResposta = strtol( sTermAnsw.pcAnswStrg, &p, 10 );
  	if( *p ne NULL )
	  continue;
	switch( iResposta ) // faz tratamento da opcao do menu
	{
	  case 1:
		return( 1 );
	  case SAIR_MENU:
		return( 0 );
	}
  }
}
