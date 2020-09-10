/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: GERAL

	SISTEMA		: GERAL

	ARQUIVO		: MainRelat.c

	CONTEUDO	: Corpo principal dos programas de relatorio de ciclo de con-
				  trole do padrao do Score. Deve ser incluido dentro do main
				  de cada relatorio.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 01 - 29/05/96

	OBSERVACAO	: Arquivo incluido pelos relatorios.

	HISTORICO DAS EDICOES

-------------------------------------------------------------------------------
dd/mm/aa | Descricao                                                 | autor
-------------------------------------------------------------------------------
24/02/97 | Adaptacao para novo padrao de mensagens de erros          | Carlos
-------------------------------------------------------------------------------
*/

#include <ScoreErros.h>

/* -- Inicio -- */

  /* -- Definicao das variaveis locais -- */
  t_cabec	Cabecalho;
  t_dados	*AreaDados;
  t_rodape	Rodape;
  char		Msg[80];
  char		NomeArq[40];
  char		*PtrArq = NomeArq;
  char		NomeRel[40];
  int		NLinhas;
#ifndef OPERACAO_WINDOWS
  t_args	Argumentos;
#endif

  /*--- Inicializa ambiente para toolkit ---*/
#ifndef OPERACAO_WINDOWS
  StartWindows (PARCIAL);
#else
  StartWindows (0);
#endif
  /* Pega area de memoria comum */
  if( PegaComum( &Comum ) ) 
  {
	sprintf(Msg, ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_0 );
	ExibeErro(Msg);	
	EndWindows();
	exit(0);
  }

  if( ( AreaDados = malloc( sizeof( t_dados ) * MAX_LINHAS ) ) eq NULL )
  {
	sprintf(Msg,ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_34);
	ExibeErro(Msg);
	EndWindows();
	exit(0);
  }
  
  /*-- Nome do relatorio --*/
  strcpy (NomeRel, My_name);
 
#ifndef OPERACAO_WINDOWS
  if (argc eq 2)
  {
    /*-- Verifica se pediu exibicao de texto de ajuda --*/
    if (strcmp (argv[1], CHAVE_AJUDA) eq 0 )
	  EscreveAjuda (NomeRel);
	else
	{
	  sprintf(Msg,ScoreGetStr(SCORE_ERR_0), My_name, COD_ERRO_81);
	  ExibeErro(Msg);
	}
	EndWindows ();
	free( AreaDados );
	exit(0);
  }
#endif

  if (argc eq NUM_ARGS)
  {  
	/* -- Le as tabelas consultadas do micro no controle (quando necessario) -- */
	if (LeTabelas() eq 0)
	{
#ifndef OPERACAO_WINDOWS
	  /*-- Faz a consistencia dos argumentos recebidos --*/
	  if (ConsisteArgumentos(argv, &Argumentos) eq RET_FUNCAO_OK)
	  {
		/*-- Argumentos okay; monta dados internamente --*/
		if ((NLinhas = GeraDadosRelatorio(&Argumentos, &Cabecalho, AreaDados,
										 &Rodape)) > 0 )
		{
		  /*-- Se existem dados preparados, monta relatorio --*/
		  if ((PtrArq=GrArqRel(&Cabecalho, AreaDados, &Rodape, NomeRel, 
							   NLinhas)) ne NULL )
		  {
			/*-- Se esta montado corretamente, exibe o relatorio --*/
			ExibeRel( PtrArq, NLinhas );
			if (strstr (PtrArq, "IP") eq NULL)
			  unlink(PtrArq);
		  }
		}
		else
		  ExibeErro(ScoreGetStr(SCORE_MSG_44));
	  } /* if (ConsisteArgumentos) */
#else
	  if((NLinhas = GeraDadosRelatorio(argv, &Cabecalho,
                                    AreaDados, &Rodape)) > 0 )
	  {
		/*-- Se existem dados preparados, monta relatorio --*/
		if ((PtrArq=GrArqRel(&Cabecalho, AreaDados, &Rodape, NomeRel, 
							 NLinhas)) ne NULL)
		{
		  /*-- Se esta montado corretamente, exibe o relatorio --*/
		  ExibeRel(PtrArq, NLinhas);
		  if (strstr (PtrArq, "IP") eq NULL)
			unlink(PtrArq);
		}
	  }
	  else
		ExibeAtencao(ScoreGetStr(SCORE_MSG_44));
//		ExibeErro(ScoreGetStr(SCORE_MSG_44));
#endif
	} /* if LeTabelas */
  }
  else
	ExibeErro(ScoreGetStr(SCORE_MSG_210));
  EndWindows ();
  free(AreaDados);

/* -- Fim -- */
