/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DAS SALAS 125 KA I E VII

	ARQUIVO		: RRuiSigDia.c

	CONTEUDO	: Relatorio de comparacao entre ruido filtrado e simga

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

#include <RRuiSigDia.h>

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
printf("\n Cheguei Aqui!!!\n");

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
	(Dad+Cuba)->RLent    = ((Dad+Cuba)->RLent / NumDias);
	(Dad+Cuba)->RRap     = ((Dad+Cuba)->RRap  / NumDias);
    (Dad+Cuba)->VRLent   = ((Dad+Cuba)->VRLent / NumDias);
    (Dad+Cuba)->VRRap    = ((Dad+Cuba)->VRRap / NumDias);
    (Dad+Cuba)->SigS     = ((Dad+Cuba)->SigS / NumDias);
    (Dad+Cuba)->SigL     = ((Dad+Cuba)->SigL / NumDias);
    (Dad+Cuba)->VSigS    = ((Dad+Cuba)->VSigS / NumDias);
    (Dad+Cuba)->VSigL    = ((Dad+Cuba)->VSigL / NumDias);

    /* acumula valores para o calculo das medias */
	if ((Dad+Cuba)->SinEst[0] ne '+')
	{
	  Rod->RLent  += (Dad+Cuba)->RLent;
	  Rod->RRap	  += (Dad+Cuba)->RRap;
	  Rod->VRLent += (Dad+Cuba)->VRLent;
	  Rod->VRRap  += (Dad+Cuba)->VRRap;
	  Rod->SigS   += (Dad+Cuba)->SigS;
	  Rod->SigL   += (Dad+Cuba)->SigL;
	  Rod->VSigS  += (Dad+Cuba)->VSigS;
	  Rod->VSigL  += (Dad+Cuba)->VSigL;
	  ++ContMed;
	}
	else
	{
	  (Dad+Cuba)->RLent	 = 0.0;
	  (Dad+Cuba)->RRap	 = 0.0;
	  (Dad+Cuba)->VRLent = 0.0;
	  (Dad+Cuba)->VRRap  = 0.0;
	  (Dad+Cuba)->SigS	 = 0.0;
	  (Dad+Cuba)->SigL	 = 0.0;
	  (Dad+Cuba)->VSigS  = 0.0;
  	  (Dad+Cuba)->VSigL	 = 0.0;
	}
  }

  if ( ContMed > 0 )
  {
	/* calcula as medias montando-as no rodape */
	Rod->RLent  = Rod->RLent / ContMed;
	Rod->RRap	= Rod->RRap	 / ContMed;
	Rod->VRLent = Rod->VRLent/ ContMed;
	Rod->VRRap	= Rod->VRRap / ContMed;
	Rod->SigS	= Rod->SigS	 / ContMed;
	Rod->SigL	= Rod->SigL	 / ContMed;
	Rod->VSigS	= Rod->VSigS / ContMed;
	Rod->VSigL  = Rod->VSigL / ContMed;
  }

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
	(Dad+Indice)->RLent    = 0.0;
	(Dad+Indice)->RRap     = 0.0;
	(Dad+Indice)->SigS     = 0.0;
    (Dad+Indice)->SigL     = 0.0;
	(Dad+Indice)->VSigS    = 0.0;
	(Dad+Indice)->VSigL    = 0.0;
  }
  /*-- Inicializa rodape */
  Rod->RLent     = 0.0;
  Rod->RRap      = 0.0;
  Rod->SigS      = 0.0;
  Rod->SigL      = 0.0;
  Rod->VRLent    = 0.0;
  Rod->VRRap     = 0.0;
  Rod->VSigS     = 0.0;
  Rod->VSigL     = 0.0;
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

  (Dad+Ind)->RLent += HIST_AVC(Cuba).RLentNormDia * 1000000000;
  (Dad+Ind)->RRap += HIST_AVC(Cuba).RRapNormDia * 1000000000;
  (Dad+Ind)->SigS += HIST_AVC(Cuba).Sup.SigSNormDia * 1000000000;
  (Dad+Ind)->SigL += HIST_AVC(Cuba).Sup.SigLNormDia * 1000000000;
  (Dad+Ind)->VRLent += HIST_AVC(Cuba).RLentNormDia * HIST_AVC(Cuba).Sup.ICubaMedDia * 1000;
  (Dad+Ind)->VRRap += HIST_AVC(Cuba).RRapNormDia * HIST_AVC(Cuba).Sup.ICubaMedDia * 1000;
  (Dad+Ind)->VSigS += HIST_AVC(Cuba).Sup.SigSNormDia * HIST_AVC(Cuba).Sup.ICubaMedDia * 1000;
  (Dad+Ind)->VSigL += HIST_AVC(Cuba).Sup.SigLNormDia * HIST_AVC(Cuba).Sup.ICubaMedDia * 1000;


}
