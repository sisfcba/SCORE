/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.4

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II

	ARQUIVO		: MCruzeiroCba.c 

	CONTEUDO	: executa a operacao de manobra de cruzeiro

	AUTOR		: Alexandre Mariz Bandeira de Morais

	SISTEMA OPERACIONAL:  QNX 4.25B		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 1.0		  -		  DATA  : 14/03/07

	HISTORICO DAS EDICOES

$Id$

$Log$
******************************************************************************/

#include <RFComunica.h.user>

typedef struct p_cubasPH
{
  short int		Total;
  short int		NumCuba[MAX_CUBAS];    
  short int		IndCuba[MAX_CUBAS];    
}t_p_cubasPH;

typedef struct b_filtrosPH
{
  unsigned		SelCubas;
  unsigned		AlgCtr;
  unsigned char Impressora;
  char 			AlgStr[200];
  char			CubasSelecao[200];
  char			CubasExcluidas[200];
  char			DataInicial[9];
  char 			DataFinal[9];
  char			Turno[9];
  char			DiasExcluidos[200];
  t_p_cubasPH	Par;
}t_b_filtrosPH;

t_b_filtrosPH	Filtros1;

#define	MAX_PARAM		10

//**************************************************************
//
// MCruzeiroCba
//
//**************************************************************
void MCruzeiroCba()
{
  int				dwError;
  int				iResposta;
  int				iAnsSpc;						// numero maximo de caracteres aceitos na resposta
  SMANDAMSGPARAM	sParam;							// parametros da mensagem
  STERMANSW			sTermAnsw;						// resposta proveniente do coletor
  char				*p;
  char				operador[20];
  char				name_arq[100];
  FILE				*pfp;
  int				ret;
  char  			*Argv[MAX_PARAM + 1];
  static unsigned	control=0;

  memset( operador,	  0x00, sizeof( operador ) );

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
    sprintf( aux, "%s\n%s [%d]\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
				 "Manobra Cruzeiro",
				 "1>Cuba", cuba_num,
				 " ",
				 " ",
				 " ",
				 " ",
				 " ",
				 " ",
				 "8>Sinaliza",
				 "ENT>Sair" );
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
      case 8:
  		++control;
        sprintf( name_arq, "%s.%s.%04X", "/usr/score/tmp/arqcubas", getlogin(), control );
        pfp = fopen( name_arq, "w" );
        if( pfp eq NULL )
          sprintf(aux2, ScoreGetStr(SCORE_ERR_2), My_name, COD_ERRO_6, name_arq );
		else
		{
		  memset( &Filtros1, 0x00, sizeof( t_b_filtrosPH ) );
		  Filtros1.Par.Total = 1;
		  Filtros1.Par.NumCuba[0] = cuba_num;
		  Filtros1.Par.IndCuba[0] = cuba_ope;
          ret = fwrite( &Filtros1, sizeof( t_b_filtrosPH ), 1, pfp );
          if( ret ne 1 )
		  {
            sprintf(aux2, ScoreGetStr(SCORE_ERR_2), My_name, COD_ERRO_8, name_arq );
			fclose( pfp );
		  }
		  else
		  {		
            fclose( pfp );
			Argv[0] = "/score/exec/OpeManobCruzPH";
			Argv[1] = name_arq;
			sprintf(operador,"%d",NumOperador+1);
			Argv[2] = operador; 
		    strcpy(aux2,(char *)AtivaOperacao(3,Argv));
		  }
		}
		ExibeMensCba(aux2);
	  break;
	  case SAIR_MENU:
		if(strlen(name_arq) != 0)
		{
		  sprintf(aux2,"rm %s >/dev/null",name_arq);
		  system(aux2);
		}	
	    return;
	}
  }
}

//**************************************************************
//
// ExibeMensCba
//
//**************************************************************
void ExibeMensCba(char *mens)
{
  int				dwError;
  int				iResposta;
  int				iAnsSpc;						// numero maximo de caracteres aceitos na resposta
  SMANDAMSGPARAM	sParam;							// parametros da mensagem
  STERMANSW			sTermAnsw;						// resposta proveniente do coletor
  char				*p;
  char				buf[100];
  int				i, j;

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

	j = 0;
	memset(buf,0x00,sizeof(buf));
	for(i=0;i<strlen(mens);++i)
	{
	  if((i % 20) == 0)
	  {
		strncpy(&buf[j],"\n",1);
		++j;
	  }
	  strncpy(&buf[j],&mens[i],1);
	  ++j;
	}
    sprintf( aux, "A T E N C A O\n%s\nENT>Sair",buf);
	dwError = MandarPrompt( &sParam, aux, iAnsSpc, &sTermAnsw);
	if( dwError ne 0 )
	  TrataErroColetor( dwError );
    iResposta = strtol( sTermAnsw.pcAnswStrg, &p, 10 );
  	if( *p ne NULL )
	{
	  continue;
	}
	switch( iResposta ) // faz tratamento da opcao do menu
	{
	  case SAIR_MENU:
		return;
	}
  }
}
