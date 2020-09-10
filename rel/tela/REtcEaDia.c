/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DAS SALAS 125 KA I E VII

	ARQUIVO		: REtcEaDia.c

	CONTEUDO	: Programa que processa e gera as informacoes que compoem
				  exemplo de relatorio historico (dia e turno)

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 01 - 19/09/2012

	HISTORICO DAS EDICOES

-------------------------------------------------------------------------------
dd/mm/aa   | Descricao                                               | autor
-------------------------------------------------------------------------------
19/09/2012 | Edicao inicial                                          | Leonel
-------------------------------------------------------------------------------
******************************************************************************/

/*-- INDICA QUE ESTE E' O PROGRAMA PRINCIPAL --*/

#define	PROGRAMA_PRINCIPAL
#define	RELATORIO_HISTORICO

/*-- INCLUSAO DE OUTROS ARQUIVOS --*/

#include <REtcEaDia.h>

/*-- PROTOTIPOS DAS FUNCOES INTERNAS --*/

void main( int argc , char *argv[] );
int  ConsisteArg(char *argv[], t_args *Arg);
void IniDados(t_args *Arg, t_cabec *Cab, t_dados *Dad, t_rodape *Rod,
			  t_aux *Aux);
void CalcAreaDados(t_aux *Aux, int Cuba, t_hist *HAvlAvc);
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
  int     Cuba;
  int     CubaAtual;
  int     Indice;
  int	  NumDias;
  float   PercSistema;
  float   PercLinha;
  float   Percent;
  time_t  HoraAtual;
  time_t  TimeTAtual;
  time_t  TimeT;
  struct  tm DataTm;
  t_hist  *HAvlAvc;
#ifdef OPERACAO_WINDOWS
  int     IndCuba;
#endif
  char   LimDur[11][4] = { " 0 ", " 1 ", " 2 ", " 3 ", " 4 ", " 5 ", " 6 ", " 7 ", " 8 ", " 9 ", "> 9" };
  char   LimPrev[10][6] = { " <=10", "10-20", "20-30", "30-40", "40-50", "50-60", "60-70", "70-80", "80-90", " >90 " };                       /* Min.  */
  char   LimInt[15][9] = { "  <=8  ", " 08-16 ", " 16-24 ", " 24-32 ", " 32-40 ", " 40-48 ", " 48-56 ", " 56-64 ", " 64-72 ", " 72-80 ", " 80-88 ", " 88-96 ", " 96-104", "104-112", "  >112 " }; /* Horas */
  char LimVMax[8][6] = { " <=15", "15-20", "20-25", "25-30", "30-35", "35-40", "40-45", "  >45" };                                 /* Volts */
  t_aux Aux;


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
  IniDados(Arg, Cab, Dad, Rod, &Aux);

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
  PercSistema = 0.0;
  PercLinha = 0.0;

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
    /* inicializa cuba inicial para cada dia */
    Cab->IAlvo += (HIST_AVL.IAlvoDia/1000.0);
    Cab->IReal += (HIST_AVL.IMedDia/1000.0);
    
    /* Acumula o percentual que o sistema e a linha ficaram ativos no dia */
    /* para calculo do percentual medio dos dias solicitados.             */
#ifdef	REL_TURNO
	Percent = CalcPercTur(Arg, HIST_AVL.NCicAtivoDia, 1, HoraAtual,
					DataTm.tm_yday);
    PercSistema += Percent;
	Percent = CalcPercTur(Arg, HIST_AVL.NCicContDia, 1, HoraAtual,
					DataTm.tm_yday);
    PercLinha += Percent;
#else
    /*-- Somados 3 ciclos de variacao ao inves de 1 para historicos ate --*/
    /*-- seja corrigido o problema de variacao do relogio do sistema    --*/
	Percent = CalcPercDia(HIST_AVL.NCicAtivoDia, 3, HoraAtual,
					DataTm.tm_yday);
    PercSistema += Percent;
	Percent = CalcPercDia(HIST_AVL.NCicContDia, 3, HoraAtual,
					DataTm.tm_yday);
    PercLinha += Percent;
#endif

    Indice = 0; /* inicializa numero de linhas */
    /* executa para todas as cubas */

	Cuba = Arg->CubaInicial;
#ifndef OPERACAO_WINDOWS
	for (Cuba = Arg->CubaInicial; Cuba <= Arg->CubaFinal; ++Cuba)
	{
	  CubaAtual = ConvCubOperScore(Cuba);
	  if ((CubaAtual ne -1) and (ValidaCuba(Arg->TabCubas, CubaAtual) eq VERDADEIRO))
	  {
		CalcAreaDados(&Aux, CubaAtual, HAvlAvc);
	  }
	}
#else
	/*-- Montagem da area de dados do relatorio --*/
	IndCuba = 0;
	do
	{
	  CubaAtual=filtro.Par.IndCuba[IndCuba];
	  CalcAreaDados(&Aux, CubaAtual, HAvlAvc);
	  ++IndCuba;
	} while (IndCuba < filtro.Par.Total);
#endif
	
    TimeT += (time_t)( NUM_SEGUNDOS_DIA * TIMES_PER_SEC ); /* avanca um dia */
    memcpy (&DataTm, localtime(&TimeT), sizeof(struct tm)); /* converte para struct tm */

  } /*-- for (ContDia ...) --*/

  Indice = 15;

  /*-- Sai da funcao quando nao houver informacoes a exibir --*/
  if (Indice eq 0 || NumDias eq 0)
	return(0);

  /* calcula media para ialvo, ireal,, VCuba, PercSistema e PercLinha */
  Cab->IAlvo    = Cab->IAlvo / NumDias;
  Cab->IReal    = Cab->IReal / NumDias;
  Cab->PercSistema = PercSistema / NumDias;
  Cab->PercLinha = PercLinha / NumDias;
  if (Cab->PercSistema > 100.0)
	Cab->PercSistema = 100.0;
  if (Cab->PercLinha > 100.0)
	Cab->PercLinha = 100.0;

  for( Indice=0; Indice < 16; ++Indice )
  {
	if(Indice < 15)
	  if(Aux.TotContInterv > 0)
	    Aux.PercContInterv[Indice] = ((float)(Aux.IndContInterv[Indice] / (float)Aux.TotContInterv) * 100);
	if(Indice < 11)
	{
	  if(Aux.TotContDurEa > 0)	  
	  {
	    Aux.PercContDurEa[Indice] = ((float)Aux.IndContDurEa[Indice] / (float)Aux.TotContDurEa) * 100;
		if(Aux.IndDurEa[Indice] > 0)
  	  	  Aux.PercDxLim[Indice] = ((float)Aux.IndDurXLimEa[Indice] / (float)Aux.IndDurEa[Indice]) * 100;
	  }
	}
	if (Indice < 10)
	  if(Aux.TotContIntervPrev > 0)	  
  	    Aux.PercContIntervPrev[Indice] = ((float)Aux.IndContIntervPrev[Indice] / (float)Aux.TotContIntervPrev) * 100;

	if (Indice < 8)
	  if(Aux.TotContVMaxEa > 0)	  
		Aux.PercVMaxEa[Indice] = ((float)Aux.IndContVMaxEa[Indice] / (float)Aux.TotContVMaxEa) * 100;

	if (Indice < 11)
      sprintf((Dad+Indice)->Texto, " %3s    %5.1f     %3.0f", LimDur[Indice], Aux.PercContDurEa[Indice], Aux.PercDxLim[Indice]);
	else
      sprintf((Dad+Indice)->Texto, "                     ");

	if (Indice < 8)
      sprintf((Dad+Indice)->Texto, "%s     %5s   %5.1f", (Dad+Indice)->Texto, LimVMax[Indice], Aux.PercVMaxEa[Indice]);
	else
      sprintf((Dad+Indice)->Texto, "%s                  ", (Dad+Indice)->Texto);

	if (Indice < 15)
      sprintf((Dad+Indice)->Texto, "%s    %7s   %5.1f", (Dad+Indice)->Texto, LimInt[Indice], Aux.PercContInterv[Indice]);
	else
      sprintf((Dad+Indice)->Texto, "%s                   ", (Dad+Indice)->Texto);

	if (Indice < 10)
      sprintf((Dad+Indice)->Texto, "%s     %5s   %5.1f", (Dad+Indice)->Texto, LimPrev[Indice], Aux.PercContIntervPrev[Indice]);
	else
      sprintf((Dad+Indice)->Texto, "%s                 ", (Dad+Indice)->Texto);

	if (Indice > 14)
	  sprintf((Dad+Indice)->Texto, "         Total de Efeitos : %3i        Efeitos com Previsao : %3i", Aux.TotContVMaxEa, Aux.TotContIntervPrev);
	

  }


  free(HAvlAvc);
  return(Indice);  /* numero de linhas prenchidas */

}

/*
------------------------------------------------------------------------------
  IniDados - Inicializa cabecalho e area de dados do relatorio
------------------------------------------------------------------------------
*/
void IniDados(t_args *Arg, t_cabec *Cab, t_dados *Dad, t_rodape *Rod,
			  t_aux *Aux)
{
  int Indice;

  /*-- Inicializa cabecalho --*/
  Cab->DiaInicial = Arg->DiaInicial;
  Cab->MesInicial = Arg->MesInicial;
  Cab->AnoInicial = Arg->AnoInicial;
  Cab->DiaFinal   = Arg->DiaFinal;
  Cab->MesFinal   = Arg->MesFinal;
  Cab->AnoFinal   = Arg->AnoFinal;
  Cab->IAlvo      = 0.0;
  Cab->IReal      = 0.0;
#ifdef	REL_TURNO
  memset(Cab->Turno, 0x00, MAX_ID_TURNO);
  strncpy(Cab->Turno,AVL.IdentTurno[Arg->Turno],MAX_ID_TURNO);
#endif
  /*-- Inicializa area de dados --*/
  for( Indice = 0; Indice < MAX_CUBAS; ++Indice )
  {
    sprintf((Dad+Indice)->Texto, "%1s", " ");

	if(Indice < 15)
	{
		Aux->IndContInterv[Indice] = 0;
		Aux->PercContInterv[Indice] = 0;
	}
	if(Indice < 12)
	{
		Aux->IndContDurEa[Indice]= 0;
		Aux->PercContDurEa[Indice] = 0;
		Aux->IndDurEa[Indice] = 0;
		Aux->IndDurXLimEa[Indice] = 0;
		Aux->PercDxLim[Indice] = 0;
	}
	if ( Indice < 11 )
	{
		Aux->IndContIntervPrev[Indice] = 0;
		Aux->PercContIntervPrev[Indice] = 0;
	}
	if (Indice < 9)
	{
		Aux->IndContVMaxEa[Indice] = 0;
		Aux->PercVMaxEa[Indice] = 0;
	}
	Aux->TotContDurEa = 0;
	Aux->TotContVMaxEa = 0;
	Aux->TotContInterv = 0;
	Aux->TotContIntervPrev = 0;
	
	
  }
  /*-- Inicializa rodape */
}


/*
------------------------------------------------------------------------------
  CalcAreaDados - Calcula area de dados do relatorio
------------------------------------------------------------------------------
*/
void CalcAreaDados(t_aux *Aux, int Cuba, t_hist *HAvlAvc)
{

  int Indice;
//  char string[20];

  for(Indice = 0; Indice < 15; Indice++)
  {
	if (Indice < 15)
	{
	  if(Indice >= 14)
	  {
	    Aux->IndContInterv[Indice] += HIST_AVC(Cuba).ContIntEa2[Indice-14];
	    Aux->TotContInterv += HIST_AVC(Cuba).ContIntEa2[Indice-14];
	  }
	  else
	  {
	    Aux->IndContInterv[Indice] += HIST_AVC(Cuba).ContIntEa[Indice];
	    Aux->TotContInterv += HIST_AVC(Cuba).ContIntEa[Indice];
	  }
		
	}
	
	if (Indice < 11)
	{
	  Aux->IndContDurEa[Indice] += HIST_AVC(Cuba).ContDurEa[Indice];
	  Aux->TotContDurEa += HIST_AVC(Cuba).ContDurEa[Indice];
	  Aux->IndDurEa[Indice] += HIST_AVC(Cuba).DurEa[Indice]; 
	  Aux->IndDurXLimEa[Indice] += HIST_AVC(Cuba).EaDurXLim[Indice];

	}

	if (Indice < 10)
	{
	  Aux->IndContIntervPrev[Indice] += HIST_AVC(Cuba).ContPrevEa[Indice];
	  Aux->TotContIntervPrev += HIST_AVC(Cuba).ContPrevEa[Indice];
	}

	if (Indice < 8)
	{
	  Aux->IndContVMaxEa[Indice] += HIST_AVC(Cuba).ContVMaxEa[Indice];
	  Aux->TotContVMaxEa	+= HIST_AVC(Cuba).ContVMaxEa[Indice];


	}

//	sprintf(string,"%d  %d",Aux->IndContIntervPrev[Indice],HIST_AVC(Cuba).ContPrevEa[Indice]);
//	ExibeErro(string);


  }

}
