/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DAS SALAS 125 KA I E VII

	ARQUIVO		: RelPerdEn.c

	CONTEUDO	: Relatorio de perdas de energina por falhas

	AUTOR		: Marco Aurelio Moreira Lopes

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 01 - 03/12/2012

	HISTORICO DAS EDICOES

-------------------------------------------------------------------------------
dd/mm/aa   | Descricao                                               | autor
-------------------------------------------------------------------------------
03/12/2012 | Edicao inicial                                          | Marco
-------------------------------------------------------------------------------
******************************************************************************/

/*-- INDICA QUE ESTE E' O PROGRAMA PRINCIPAL --*/

#define	PROGRAMA_PRINCIPAL
#define	RELATORIO_HISTORICO

/*-- INCLUSAO DE OUTROS ARQUIVOS --*/

#include <RelPerdEn.h>

/*-- PROTOTIPOS DAS FUNCOES INTERNAS --*/

void main( int argc , char *argv[] );
int  ConsisteArg(char *argv[], t_args *Arg);
void IniDados(t_args *Arg, t_cabec *Cab, t_dados *Dad, t_rodape *Rod);
void CalcAreaDados(t_dados *Dad, int Cuba, int Ind, t_hist *HAvlAvc);
int GeraDadosRel(t_args *Arg, t_cabec *Cab, t_dados *Dad, t_rodape *Rod);

/*
-------------------------------------------------------------------------------
							Variaveis Globais
-------------------------------------------------------------------------------
*/

#ifdef OPERACAO_WINDOWS
  t_filtrosPD filtro;
#endif


/*
-------------------------------------------------------------------------------
							Main
-------------------------------------------------------------------------------
*/

void main( int argc, char *argv[] )
{
  /*-- Corpo padrao de todos relatorios historicos --*/
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
		/*- Gera arquivo de dados do relatorio --*/
		if ((PtrArq = GrArqRel(&Cab, Dad, &Rod, NomeRel, NLinhas)) ne NULL)
		{
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

}

/*
-------------------------------------------------------------------------------
  ConsisteArg - Faz a consistencia dos parametros recebidos
-------------------------------------------------------------------------------
*/

int ConsisteArg(char *argv[], t_args *Arg)
{
  char   DataI[9],
		 DataF[9];
  struct tm *StData;
  time_t HoraAtual;
#ifdef OPERACAO_WINDOWS
  char	 Msg[80];
#endif
#ifdef	REL_TURNO
  char	 StTur[9];
  int    Turno;
#endif

#ifndef OPERACAO_WINDOWS
  /*-- Converte cuba inicial e final --*/
  Arg->CubaInicial = atoi(argv[1]);
  Arg->CubaFinal   = atoi(argv[2]);
  /*-- Faz consistencia do numero das cubas --*/
  if (ConsisteCubas(Arg->CubaInicial, Arg->CubaFinal) eq VERDADEIRO)
  {
	/*-- Verifica existencia de cuba na linha de exclusao --*/
	Arg->TabCubas[0] = -1;
  #ifdef	REL_TURNO
	if (*argv[6] ne NUL)
  #else
	if (*argv[5] ne NUL)
  #endif
	{
	  /*-- Sinaliza exclusao de cuba --*/
	  Arg->TabCubas[0] = 0;
	  /*-- Valida a linha de exclusao de cubas --*/
  #ifdef	REL_TURNO
	  if (ValExcCubas(argv[6], Arg->TabCubas) ne VERDADEIRO)
  #else
	  if (ValExcCubas(argv[5], Arg->TabCubas) ne VERDADEIRO)
  #endif
	  {
		ExibeErro(ScoreGetStr(SCORE_MSG_584));
		return(RET_FUNCAO_ERR);
	  }
	}
  }
  else
	return(RET_FUNCAO_ERR);
#endif

#ifndef OPERACAO_WINDOWS
  strcpy(DataI, argv[3]);
  strcpy(DataF, argv[4]);
#else
  strcpy(DataI, argv[2]);
  strcpy(DataF, argv[3]);
#endif

  HoraAtual = time(NULL);
  StData = localtime(&HoraAtual);
  /*-- Verifica se a data inicial assumiu o valor default --*/
  if (strcmp(strupr(DataI), strupr(ScoreGetStr(STR_ATUAL))) eq 0)
	sprintf(DataI, "%02d/%02d/%02d",StData->tm_mday, StData->tm_mon+1,
  /* -- Y2k inicio: ano de 2 digitos -- */
			TM_YEAR_TO_2DIGIT(StData->tm_year));
  /* -- Y2k fim -- */

  /*-- Verifica se a data final assumiu o valor default --*/
  if (strcmp(strupr(DataF), strupr(ScoreGetStr(STR_ATUAL))) eq 0)
	sprintf(DataF, "%02d/%02d/%02d",StData->tm_mday, StData->tm_mon+1,
  /* -- Y2k inicio: ano de 2 digitos -- */
			TM_YEAR_TO_2DIGIT(StData->tm_year));
  /* -- Y2k fim -- */

  if (ConsDatas(DataI, DataF, Arg, MAX_DIAS_HIST) eq RET_FUNCAO_OK)
  {
#ifdef	REL_TURNO
	/*-- Pega o numero do turno --*/
  #ifndef OPERACAO_WINDOWS
	strcpy(StTur, argv[5]);
  #else
	strcpy(StTur, argv[4]);
  #endif
	Turno = (strcmp(strupr(StTur),strupr(ScoreGetStr(STR_ATUAL))) eq 0)?AVL.TurnoAtual: atoi(StTur) - 1;
	if (Turno >= AVL.NumTurnos)
	{
	  ExibeErro(ScoreGetStr(SCORE_MSG_589));
	  return(RET_FUNCAO_ERR);
	}
	Arg->Turno = Turno;
	/*-- Consiste exclusao de data --*/
	Arg->TabDatas[0] = -1;
  #ifdef OPERACAO_WINDOWS
	if (*argv[5] ne NUL)
  #else
	if (*argv[7] ne NUL)
  #endif
	{
	  /*-- Sinaliza  exclusao de data --*/
	  Arg->TabDatas[0] = 0;
	  /*-- Valida a linha de exclusao de datas. --*/
  #ifdef	OPERACAO_WINDOWS
	  if (ValidaExcDatas(Arg, argv[5]) ne VERDADEIRO)
  #else
	  if (ValidaExcDatas(Arg, argv[7]) ne VERDADEIRO)
  #endif
	  {
		ExibeErro(ScoreGetStr(SCORE_MSG_588));
		return(RET_FUNCAO_ERR);
	  }
	}
#else
	/*-- Consiste exclusao de data --*/
	Arg->TabDatas[0] = -1;
  #ifdef OPERACAO_WINDOWS
	if (*argv[4] ne NUL)
  #else
	if (*argv[6] ne NUL)
  #endif
	{
	  /*-- Sinaliza  exclusao de data --*/
	  Arg->TabDatas[0] = 0;
	  /*-- Valida a linha de exclusao de datas. --*/
  #ifdef OPERACAO_WINDOWS
	  if (ValidaExcDatas(Arg, argv[4]) ne VERDADEIRO)
  #else
	  if (ValidaExcDatas(Arg, argv[6]) ne VERDADEIRO)
  #endif
	  {
		ExibeErro(ScoreGetStr(SCORE_MSG_588));
		return(RET_FUNCAO_ERR);
	  }
	}
#endif
  }
  else
	return(RET_FUNCAO_ERR);
  
#ifdef OPERACAO_WINDOWS
  /*-- Le arquivo de filtro de cubas --*/
  if (LeFiltroCubas(argv[1], &filtro))
  {
    sprintf(Msg, ScoreGetStr(SCORE_ERR_2),My_name,COD_ERRO_6, argv[1]);
	ExibeErro(Msg);
	return(RET_FUNCAO_ERR);
  }
  if (filtro.Par.Total eq 0)
  {
	ExibeErro(ScoreGetStr(SCORE_MSG_43));
	return(RET_FUNCAO_ERR);
  }
#endif

  return(RET_FUNCAO_OK);
}

/*
-------------------------------------------------------------------------------
  GeraDadosRel - Calcula  as  variaveis e medias  a  serem  exibidas  no 
                 relatorio,montando os campos variaveis do Cab, area  de
                 Dad e Rod do relatorio.                                 
-------------------------------------------------------------------------------
*/
int GeraDadosRel(t_args *Arg, t_cabec *Cab, t_dados *Dad, t_rodape *Rod)
{
  int     ContDia;
  int     ContMed;
  int     Cuba;
  int     CubaAtual;
  int     Indice;
  int	  NumDias;
  time_t  HoraAtual;
  time_t  TimeTAtual;
  time_t  TimeT;
  struct  tm DataTm;
  t_hist  *HAvlAvc;
#ifdef OPERACAO_WINDOWS
  int     IndCuba;
#endif

  /*-- Pega hora atual --*/
  HoraAtual = time(NULL);

  /*-- Calcula hora atual para referencia --*/
  memcpy(&DataTm, localtime(&HoraAtual), sizeof(struct tm));
  DataTm.tm_sec  = 0;
  DataTm.tm_min  = 0;
  DataTm.tm_hour = 12;
  TimeTAtual = mktime(&DataTm);

#ifndef OPERACAO_WINDOWS
  /*-- Inicializa cubas de Cab --*/
  Cab->CubaInicial = Arg->CubaInicial;
  Cab->CubaFinal   = Arg->CubaFinal;
#else
  MontaAlgSel(Cab->Selecao, Cab->Algorit, &filtro);
#endif

  /*-- Inicializa estruturas do relatorio --*/
  IniDados(Arg, Cab, Dad, Rod);

  /*-- inicializa data auxiliar --*/ 
  DataTm.tm_sec  = 0;
  DataTm.tm_min  = 0;
  DataTm.tm_hour = 12;
  DataTm.tm_mday = Arg->DiaInicial;
  DataTm.tm_mon  = Arg->MesInicial - 1;
  /* -- Y2k inicio: ano de 2 digitos -- */
  DataTm.tm_year = TWO_DIGIT_TO_TM_YEAR(Arg->AnoInicial);
  /* -- Y2k fim -- */

  TimeT = mktime(&DataTm); /* converte para time_t */

  NumDias = 0;

  /* executa para todos os dias */
  for( ContDia = 0; ContDia < Arg->DiasDatas; ++ContDia )
  {
	if (ValidaData(Arg, TimeT) ne VERDADEIRO)
	{
	  TimeT += (time_t)( NUM_SEGUNDOS_DIA * TIMES_PER_SEC ); /* avanca um dia */
	  memcpy(&DataTm, localtime(&TimeT), sizeof(struct tm));  /* converte para struct tm */
	  continue; /* proxima ContDia */
	}

	++NumDias; /* incrementa numero de dias para calculo das medias */

#ifdef	REL_TURNO
    HAvlAvc = CarBufTurno(&DataTm, Arg);
#else
    HAvlAvc = CarBufCubas(&DataTm, Arg);
#endif

    if( HAvlAvc eq (void *) NULL ) /* houve erro */
      return(-1);
    
    Indice = 0; /* inicializa numero de linhas */
    /* executa para todas as cubas */
#ifndef OPERACAO_WINDOWS
	for (Cuba = Arg->CubaInicial; Cuba <= Arg->CubaFinal; ++Cuba)
	{
	  CubaAtual = ConvCubOperScore(Cuba);

	  if ((CubaAtual ne -1) and (ValidaCuba(Arg->TabCubas, CubaAtual) eq VERDADEIRO))
	  {
		CalcAreaDados(Dad, CubaAtual, Indice, HAvlAvc);
        ++Indice; /* incrementa numero de linhas */
	  }
	}
#else
	/*-- Montagem da area de dados do relatorio --*/
	IndCuba = 0;
	do
	{
	  CubaAtual=filtro.Par.IndCuba[IndCuba];
	  CalcAreaDados(Dad, CubaAtual, Indice, HAvlAvc);
	  ++Indice; /* incrementa numero de linhas */
	  ++IndCuba;
	} while (IndCuba < filtro.Par.Total);
#endif
	
    TimeT += (time_t)( NUM_SEGUNDOS_DIA * TIMES_PER_SEC ); /* avanca um dia */
    memcpy (&DataTm, localtime(&TimeT), sizeof(struct tm)); /* converte para struct tm */

  } /*-- for (ContDia ...) --*/

  /*-- Sai da funcao quando nao houver informacoes a exibir --*/
  if (Indice eq 0 || NumDias eq 0)
	return(0);

  ContMed = 0;
  for( Cuba = 0; Cuba < Indice; ++Cuba )
  {
    /* acumula valores para o calculo das medias */
	if ((Dad+Cuba)->SinEst[0] ne '+')
	{
	  Rod->TFCima	+= (Dad+Cuba)->FCima;
	  Rod->TFBaixo	+= (Dad+Cuba)->FBaixo;
	  Rod->TRCima	+= (Dad+Cuba)->RCima;
	  Rod->TRBaixo	+= (Dad+Cuba)->RBaixo;
	  Rod->TCCima	+= (Dad+Cuba)->CCima;
	  Rod->TCBaixo	+= (Dad+Cuba)->CBaixo;
	  Rod->TGCima	+= (Dad+Cuba)->GCima;
	  Rod->TGBaixo  += (Dad+Cuba)->GBaixo;
	  ++ContMed;
	}
/*	else
	{
	  (Dad+Cuba)->FCima   = 0.0;
	  (Dad+Cuba)->FBaixo  = 0.0;
	  (Dad+Cuba)->RCima   = 0.0;
	  (Dad+Cuba)->RBaixo  = 0.0;
	  (Dad+Cuba)->CCima   = 0.0;
	  (Dad+Cuba)->CBaixo  = 0.0;
	  (Dad+Cuba)->GCima   = 0.0;
  	  (Dad+Cuba)->GBaixo  = 0.0;
	}
*/
	(Dad+Cuba)->FCima  /= 1000;	
	(Dad+Cuba)->FBaixo /= 1000;
	(Dad+Cuba)->RCima /= 1000;
	(Dad+Cuba)->RBaixo /= 1000;
	(Dad+Cuba)->CCima /= 1000;
	(Dad+Cuba)->CBaixo /= 1000;
	(Dad+Cuba)->GCima /= 1000;
	(Dad+Cuba)->GBaixo /= 1000;
  }

  if ( ContMed > 0 )
  {
	/* calcula as medias montando-as no rodape */
	Rod->FCima	 = Rod->TFCima		/ ContMed;
	Rod->FBaixo	 = Rod->TFBaixo		/ ContMed;
	Rod->RCima	 = Rod->TRCima		/ ContMed;
	Rod->RBaixo	 = Rod->TRBaixo 	/ ContMed;
	Rod->CCima	 = Rod->TCCima		/ ContMed;
	Rod->CBaixo	 = Rod->TCBaixo		/ ContMed;
	Rod->GCima	 = Rod->TGCima		/ ContMed;
	Rod->GBaixo  = Rod->TGBaixo 	/ ContMed;

	Rod->FCima	 = Rod->FCima		/ 1000;
	Rod->FBaixo	 = Rod->FBaixo		/ 1000;
	Rod->RCima	 = Rod->RCima		/ 1000;
	Rod->RBaixo	 = Rod->RBaixo 		/ 1000;
	Rod->CCima	 = Rod->CCima		/ 1000;
	Rod->CBaixo	 = Rod->CBaixo		/ 1000;
	Rod->GCima	 = Rod->GCima		/ 1000;
	Rod->GBaixo  = Rod->GBaixo 		/ 1000;

  }

  Rod->TFCima	=  Rod->TFCima / 1000;
  Rod->TFBaixo	=  Rod->TFBaixo / 1000;
  Rod->TRCima	=  Rod->TRCima / 1000;
  Rod->TRBaixo	=  Rod->TRBaixo / 1000;
  Rod->TCCima	=  Rod->TCCima / 1000;
  Rod->TCBaixo	=  Rod->TCBaixo / 1000;
  Rod->TGCima	=  Rod->TGCima / 1000;
  Rod->TGBaixo	=  Rod->TGBaixo / 1000;

  free(HAvlAvc);
  return(Indice);  /* numero de linhas prenchidas */

}

/*
------------------------------------------------------------------------------
  IniDados - Inicializa cabecalho e area de dados do relatorio
------------------------------------------------------------------------------
*/
void IniDados(t_args *Arg, t_cabec *Cab, t_dados *Dad, t_rodape *Rod)
{
  int Indice;

  /*-- Inicializa cabecalho --*/
  Cab->DiaInicial = Arg->DiaInicial;
  Cab->MesInicial = Arg->MesInicial;
  Cab->AnoInicial = Arg->AnoInicial;
  Cab->DiaFinal   = Arg->DiaFinal;
  Cab->MesFinal   = Arg->MesFinal;
  Cab->AnoFinal   = Arg->AnoFinal;
#ifdef	REL_TURNO
  memset(Cab->Turno, 0x00, MAX_ID_TURNO);
  strncpy(Cab->Turno,AVL.IdentTurno[Arg->Turno],MAX_ID_TURNO);
#endif
  /*-- Inicializa area de dados --*/
  for( Indice = 0; Indice < MAX_CUBAS; ++Indice )
  {
    sprintf((Dad+Indice)->SinEst, "%1s", " ");
	(Dad+Indice)->FCima	  	= 0.0;
	(Dad+Indice)->FBaixo	= 0.0;
	(Dad+Indice)->RCima	  	= 0.0;
    (Dad+Indice)->RBaixo	= 0.0;
	(Dad+Indice)->CCima	  	= 0.0;
	(Dad+Indice)->CBaixo	= 0.0;
	(Dad+Indice)->GCima		= 0.0;
	(Dad+Indice)->GBaixo	= 0.0;
  }
  /*-- Inicializa rodape */
  Rod->FCima	   = 0.0;
  Rod->FBaixo	   = 0.0;
  Rod->RCima	   = 0.0;
  Rod->RBaixo	   = 0.0;
  Rod->CCima  	   = 0.0;
  Rod->CBaixo	   = 0.0;
  Rod->GCima	   = 0.0;
  Rod->GBaixo      = 0.0;
  Rod->TFCima	   = 0.0;
  Rod->TFBaixo	   = 0.0;
  Rod->TRCima	   = 0.0;
  Rod->TRBaixo	   = 0.0;
  Rod->TCCima  	   = 0.0;
  Rod->TCBaixo	   = 0.0;
  Rod->TGCima	   = 0.0;
  Rod->TGBaixo      = 0.0;

}


/*
------------------------------------------------------------------------------
  CalcAreaDados - Calcula area de dados do relatorio
------------------------------------------------------------------------------
*/
void CalcAreaDados(t_dados *Dad, int Cuba, int Ind, t_hist *HAvlAvc)
{

  (Dad+Ind)->NumCuba = ConvCubScoreOper(Cuba);

  if ((HIST_AVC(Cuba).EstPrincDia ne CUBA_NORMAL) and
	  ((Dad+Ind)->SinEst[0] ne '+'))
	sprintf((Dad+Ind)->SinEst, "%1s", "+");

  (Dad+Ind)->FCima += HIST_AVC(Cuba).Sup.kwcimafalhamov;
  (Dad+Ind)->FBaixo += HIST_AVC(Cuba).Sup.kwbaixofalhamov;
  (Dad+Ind)->RCima += HIST_AVC(Cuba).Sup.kwcimaforarede;
  (Dad+Ind)->RBaixo += HIST_AVC(Cuba).Sup.kwbaixoforarede;
  (Dad+Ind)->CCima += HIST_AVC(Cuba).Sup.kwcimamanuallocal;
  (Dad+Ind)->CBaixo += HIST_AVC(Cuba).Sup.kwbaixomanuallocal;
  (Dad+Ind)->GCima += HIST_AVC(Cuba).Sup.kwcimageral;
  (Dad+Ind)->GBaixo += HIST_AVC(Cuba).Sup.kwbaixogeral;
 
}
