/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DAS SALAS 125 KA I E VII

	ARQUIVO		: RelMovDia.c

	CONTEUDO	: Relatorio de movimentacoes diarias.

	AUTOR		: Marco Aurelio M. Lopes

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 01 - 17/12/12

	HISTORICO DAS EDICOES

-------------------------------------------------------------------------------
dd/mm/aa   | Descricao                                               | autor
-------------------------------------------------------------------------------
17/12/2012 | Edicao inicial                                          | Marco
-------------------------------------------------------------------------------
******************************************************************************/
/*-- INDICA QUE ESTE E' O PROGRAMA PRINCIPAL --*/

#define	PROGRAMA_PRINCIPAL
#define	RELATORIO_HISTORICO

/*-- INCLUSAO DE OUTROS ARQUIVOS --*/

#include <RelMovDia.h>

/*-- PROTOTIPOS DAS FUNCOES INTERNAS --*/

void main( int argc , char *argv[] );
int  ConsisteArg(char *argv[], t_args *Arg);
void IniDados(t_args *Arg, t_cabec *Cab, t_dados *Dad, t_rodape *Rod);
void CalcAreaDados(t_dados *Dad, int Cuba, int Ind,
				   t_hist *HAvlAvc);
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
  #include	"MainRelatHT.c"

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
    /* monta valores da area de dados */
	(Dad+Cuba)->NumMovCima	 = ((Dad+Cuba)->NumMovCima	  / NumDias);
	(Dad+Cuba)->NumFalhaCima	 = ((Dad+Cuba)->NumFalhaCima	  / NumDias);
	(Dad+Cuba)->ApMovCima		 = ((Dad+Cuba)->ApMovCima		  / NumDias);
	(Dad+Cuba)->NumMovBaixo	 = ((Dad+Cuba)->NumMovBaixo	  / NumDias);
	(Dad+Cuba)->NumFalhaBaixo	 = ((Dad+Cuba)->NumFalhaBaixo	  / NumDias);
	(Dad+Cuba)->ApMovBaixo	 = ((Dad+Cuba)->ApMovBaixo	  / NumDias);
	(Dad+Cuba)->NumMovTot		 = ((Dad+Cuba)->NumMovTot		  / NumDias);
	(Dad+Cuba)->NumFalhaTot	 = ((Dad+Cuba)->NumFalhaTot     / NumDias);
	(Dad+Cuba)->ApMovTot		 = ((Dad+Cuba)->ApMovTot		  / NumDias);

	
	Rod->MNumMovCima	 += (Dad+Cuba)->NumMovCima;
	Rod->MNumFalhaCima	 += (Dad+Cuba)->NumFalhaCima;
	Rod->MApMovCima		 += (Dad+Cuba)->ApMovCima;
	Rod->MNumMovBaixo	 += (Dad+Cuba)->NumMovBaixo;
	Rod->MNumFalhaBaixo	 += (Dad+Cuba)->NumFalhaBaixo;
	Rod->MApMovBaixo	 += (Dad+Cuba)->ApMovBaixo;
	Rod->MNumMovTot		 += (Dad+Cuba)->NumMovTot;
	Rod->MNumFalhaTot    +=	(Dad+Cuba)->NumFalhaTot;
	Rod->MApMovTot		 +=	(Dad+Cuba)->ApMovTot;
	++ContMed;
  }

  if ( ContMed > 0 )
  {
	/* calcula as medias montando-as no rodape */
	Rod->MNumMovCima	  = Rod->MNumMovCima / ContMed;
	Rod->MNumFalhaCima	  = Rod->MNumFalhaCima / ContMed;
	Rod->MApMovCima		  = Rod->MApMovCima / ContMed;
	Rod->MNumMovBaixo	  = Rod->MNumMovBaixo / ContMed;
	Rod->MNumFalhaBaixo	  = Rod->MNumFalhaBaixo / ContMed;
	Rod->MApMovBaixo	  = Rod->MApMovBaixo / ContMed;
	Rod->MNumMovTot		  = Rod->MNumMovTot / ContMed;
	Rod->MNumFalhaTot	  = Rod->MNumFalhaTot / ContMed;
	Rod->MApMovTot		  =	Rod->MApMovTot / ContMed;
  }
  /*---   Libera o buffer alocado na funcao CarBufCubas ---*/
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
	(Dad+Indice)->NumCuba		 = 0;
	(Dad+Indice)->NumMovCima	 = 0;
	(Dad+Indice)->NumFalhaCima	 = 0;
    (Dad+Indice)->ApMovCima  	 = 0;
	(Dad+Indice)->NumMovBaixo	 = 0;
	(Dad+Indice)->NumFalhaBaixo  = 0;
    (Dad+Indice)->ApMovBaixo	 = 0;
    (Dad+Indice)->NumMovTot	 	 = 0;
	(Dad+Indice)->NumFalhaTot	 = 0;
    (Dad+Indice)->ApMovTot		 = 0;
  }
  /*-- Inicializa rodape */
	Rod->MNumMovCima	 = 0;
	Rod->MNumFalhaCima	 = 0;
    Rod->MApMovCima  	 = 0;
	Rod->MNumMovBaixo	 = 0;
	Rod->MNumFalhaBaixo  = 0;
    Rod->MApMovBaixo	 = 0;
    Rod->MNumMovTot	 	 = 0;
	Rod->MNumFalhaTot	 = 0;
    Rod->MApMovTot		 = 0;
}


/*
------------------------------------------------------------------------------
  CalcAreaDados - Calcula area de dados do relatorio
------------------------------------------------------------------------------
*/
void CalcAreaDados(t_dados *Dad, int Cuba, int Ind, t_hist *HAvlAvc)
{
  (Dad+Ind)->NumCuba = ConvCubScoreOper(Cuba);

  (Dad+Ind)->NumMovCima += HIST_AVC(Cuba).MovCimaNumDia;
  (Dad+Ind)->NumMovBaixo += HIST_AVC(Cuba).MovBaixoNumDia;
  (Dad+Ind)->NumMovTot += HIST_AVC(Cuba).MovBaixoNumDia + HIST_AVC(Cuba).MovCimaNumDia;

  (Dad+Ind)->NumFalhaBaixo += HIST_AVC(Cuba).Sup.FalhaMovBaixoDia;
  (Dad+Ind)->NumFalhaCima += HIST_AVC(Cuba).Sup.FalhaMovCimaDia;
  (Dad+Ind)->NumFalhaTot += HIST_AVC(Cuba).FalhaMovDia;

  if ((HIST_AVC(Cuba).EstPrincDia eq CUBA_NORMAL) or
	  (HIST_AVC(Cuba).EstPrincDia eq CUBA_PARTIDA))
  {
    if ( (HIST_AVC(Cuba).MovCimaNumDia + HIST_AVC(Cuba).Sup.FalhaMovCimaDia) > 0)
	  (Dad+Ind)->ApMovCima += HIST_AVC(Cuba).Sup.ApMovCimaDia / (HIST_AVC(Cuba).MovCimaNumDia + 
								HIST_AVC(Cuba).Sup.FalhaMovCimaDia);
	else
	  (Dad+Ind)->ApMovCima += 0;
    if ( (HIST_AVC(Cuba).MovBaixoNumDia + HIST_AVC(Cuba).Sup.FalhaMovBaixoDia) > 0)
      	(Dad+Ind)->ApMovBaixo += HIST_AVC(Cuba).Sup.ApMovBaixoDia / (HIST_AVC(Cuba).MovBaixoNumDia +
								HIST_AVC(Cuba).Sup.FalhaMovBaixoDia);
	else
	 (Dad+Ind)->ApMovBaixo += 0; 
	if( (HIST_AVC(Cuba).MovCimaNumDia + HIST_AVC(Cuba).MovBaixoNumDia +
		HIST_AVC(Cuba).Sup.FalhaMovCimaDia + HIST_AVC(Cuba).Sup.FalhaMovBaixoDia) > 0)
      (Dad+Ind)->ApMovTot += (HIST_AVC(Cuba).Sup.ApMovBaixoDia + HIST_AVC(Cuba).Sup.ApMovCimaDia) / 
							 (HIST_AVC(Cuba).MovCimaNumDia + HIST_AVC(Cuba).MovBaixoNumDia + 
							 HIST_AVC(Cuba).Sup.FalhaMovCimaDia + HIST_AVC(Cuba).Sup.FalhaMovBaixoDia);
	else
	  (Dad+Ind)->ApMovTot += 0;   
  }
  else
  {
    (Dad+Ind)->ApMovCima += 0.0;
    (Dad+Ind)->ApMovBaixo += 0.0;
    (Dad+Ind)->ApMovTot += 0.0;
  }
	
}
