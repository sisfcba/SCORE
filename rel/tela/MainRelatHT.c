/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: GERAL

	SISTEMA		: GERAL

	ARQUIVO		: MainRelatHT.c

	CONTEUDO	: Corpo principal dos programas de relatorios historicos do
				  padrao do Score. Deve ser incluido dentro do main de cada
				  relatorio.

	AUTOR		: Carlos Cezar Silva Lage

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 01 - 05/06/96

	OBSERVACAO	: Arquivo incluido pelos relatorios.

	HISTORICO DAS EDICOES

-------------------------------------------------------------------------------
dd/mm/aa | Descricao                                                 | autor
-------------------------------------------------------------------------------
*/

#include <ScoreErros.h>
#include <ScoreMsgs.h>

/*-- Inicio --*/

  t_cabec	Cab;
  t_dados	*Dad;
  t_rodape  Rod;
  t_args	Arg;
  char		NomeArq[20];
  char		Msg[80];
  char		*PtrArq = NomeArq;
  char		NomeRel[20];
  int		NLinhas;

  /*-- Inicializa ambiente grafico --*/
#ifndef OPERACAO_WINDOWS
  StartWindows(PARCIAL);
#else
  StartWindows(0);
#endif

  /*-- Pega area de memoria comum --*/
  if (PegaComum(&Comum))
  {
	sprintf(Msg, ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_0 );
	ExibeErro(Msg);	
	EndWindows();
	exit(0);
  }
  if( ( Dad = malloc( sizeof( t_dados ) * MAX_LINHAS ) ) eq NULL )
  {
	sprintf(Msg,ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_34);
	ExibeErro(Msg);
	EndWindows();
	exit(0);
  }
  /*-- Pega nome do relatorio --*/
  strcpy(NomeRel, My_name);
  
#ifndef OPERACAO_WINDOWS
  if (argc eq 2)
  {
	if (strcmp(argv[1], CHAVE_AJUDA) eq 0)
	  EscreveAjuda(NomeRel);
	else
	{
	  sprintf(Msg,ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_81);
	  ExibeErro(Msg);
	}
	EndWindows();
    free( Dad );
	exit(0);
  }
#endif

  if (argc eq NUM_ARGS)
  {
	/*-- Faz consistencia dos parametros recebidos --*/
	if (ConsisteArg(argv, &Arg) eq RET_FUNCAO_OK)
	{
	  /*-- Monta dados do relatorio --*/
	  if ((NLinhas = GeraDadosRel(&Arg, &Cab, Dad, &Rod)) > 0)
	  {
//	sprintf(Msg,"NLINHAS %d", NLinhas);
//		ExibeErro(Msg);
		/*- Gera arquivo de dados do relatorio --*/
		if ((PtrArq = GrArqRel(&Cab, Dad, &Rod, NomeRel, NLinhas)) ne NULL)
		{
//		  ExibeErro(PtrArq);
		  /*- Exibe dados do relatorio --*/
		  ExibeRel(PtrArq, NLinhas);
		  if (strstr(PtrArq, "IP") eq NULL)
			unlink(PtrArq);
		}
	  }
	  else
	  {
		if (NLinhas eq 0)
#ifndef OPERACAO_WINDOWS
		  ExibeErro(ScoreGetStr(SCORE_MSG_44));
#else
		  ExibeAtencao(ScoreGetStr(SCORE_MSG_44));
//		  ExibeErro(ScoreGetStr(SCORE_MSG_44));
#endif		  
	  }
	}
  }
  else
  {
	ExibeErro(ScoreGetStr(SCORE_MSG_210));
  }

  EndWindows ();

/*-- Fim --*/
