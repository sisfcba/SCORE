/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DAS SALAS 125 KA I E VII

	ARQUIVO		: RelExemploDia.c

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

$Id: RelExemploDia.c,v 1.1.2.1 2012/09/28 17:10:11 leo Exp $

$Log: RelExemploDia.c,v $
Revision 1.1.2.1  2012/09/28 17:10:11  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

******************************************************************************/

/*-- INDICA QUE ESTE E' O PROGRAMA PRINCIPAL --*/

#define	PROGRAMA_PRINCIPAL
#define	RELATORIO_HISTORICO

/*-- INCLUSAO DE OUTROS ARQUIVOS --*/

#include <RelExemploDia.h>

/*-- PROTOTIPOS DAS FUNCOES INTERNAS --*/

void main( int argc , char *argv[] );
int  ConsisteArg(char *argv[], t_args *Arg);
void IniDados(t_args *Arg, t_cabec *Cab, t_dados *Dad, t_rodape *Rod,
			  t_tempo *Temp);
void CalcAreaDados(t_dados *Dad, int Cuba, int Ind, t_tempo *Temp,
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
  long    MDesvTempo;
  long    MForaTempo;
  float   PercSistema;
  float   PercLinha;
  float   Percent;
  t_tempo Temp;
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
  IniDados(Arg, Cab, Dad, Rod, &Temp);

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
    Cab->VLinha += (HIST_AVL.VLinhaDia);
    
    if ((HIST_AVL.CubasNormDia + HIST_AVL.CubasLigParDia) > 0.0)
      Cab->VCuba = HIST_AVL.VLinhaDia/(HIST_AVL.CubasNormDia + HIST_AVL.CubasLigParDia);
    else
      Cab->VCuba = 0.0;    
    
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
#ifndef OPERACAO_WINDOWS
	for (Cuba = Arg->CubaInicial; Cuba <= Arg->CubaFinal; ++Cuba)
	{
	  CubaAtual = ConvCubOperScore(Cuba);
	  if ((CubaAtual ne -1) and (ValidaCuba(Arg->TabCubas, CubaAtual) eq VERDADEIRO))
	  {
		CalcAreaDados(Dad, CubaAtual, Indice, &Temp, HAvlAvc);
        ++Indice; /* incrementa numero de linhas */
	  }
	}
#else
	/*-- Montagem da area de dados do relatorio --*/
	IndCuba = 0;
	do
	{
	  CubaAtual=filtro.Par.IndCuba[IndCuba];
	  CalcAreaDados(Dad, CubaAtual, Indice, &Temp, HAvlAvc);
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

  /* calcula media para ialvo, ireal,, VCuba, PercSistema e PercLinha */
  Cab->IAlvo    = Cab->IAlvo / NumDias;
  Cab->IReal    = Cab->IReal / NumDias;
  Cab->VLinha   = Cab->VLinha / NumDias;
  Cab->VCuba = Cab->VCuba / NumDias;
  Cab->PercSistema = PercSistema / NumDias;
  Cab->PercLinha = PercLinha / NumDias;
  if (Cab->PercSistema > 100.0)
	Cab->PercSistema = 100.0;
  if (Cab->PercLinha > 100.0)
	Cab->PercLinha = 100.0;

  MDesvTempo = 0L;
  MForaTempo = 0L;
  ContMed = 0;
  for( Cuba = 0; Cuba < Indice; ++Cuba )
  {
    /* monta valores da area de dados */
	(Dad+Cuba)->Placa    = ((Dad+Cuba)->Placa / NumDias);
	(Dad+Cuba)->Alvo     = ((Dad+Cuba)->Alvo  / NumDias);
    (Dad+Cuba)->Liqui    = ((Dad+Cuba)->Liqui / NumDias);
    (Dad+Cuba)->Total    = ((Dad+Cuba)->Total / NumDias);
    (Dad+Cuba)->ErroTot  = ((Dad+Cuba)->ErroTot / NumDias);
    (Dad+Cuba)->ErroCtrl = ((Dad+Cuba)->ErroCtrl / NumDias);
    (Dad+Cuba)->Desv     = ((Dad+Cuba)->Desv / NumDias);
    (Dad+Cuba)->Fora     = ((Dad+Cuba)->Fora  / NumDias);
	Temp.DesvTempo[Cuba] = (Temp.DesvTempo[Cuba] / NumDias);
    MontaHoraMin(Temp.DesvTempo[Cuba], (Dad+Cuba)->DesvTempo, "%3d:%02d");
	Temp.ForaTempo[Cuba] = (Temp.ForaTempo[Cuba] / NumDias);
    MontaHoraMin(Temp.ForaTempo[Cuba], (Dad+Cuba)->ForaTempo, "%3d:%02d");

    /* acumula valores para o calculo das medias */
	if ((Dad+Cuba)->SinEst[0] ne '+')
	{
	  Rod->MPlaca    += (Dad+Cuba)->Placa;
	  Rod->MAlvo     += (Dad+Cuba)->Alvo;
	  Rod->MLiqui    += (Dad+Cuba)->Liqui;
	  Rod->MTotal    += (Dad+Cuba)->Total;
	  Rod->MErroTot  += (Dad+Cuba)->ErroTot;
	  Rod->MErroCtrl += (Dad+Cuba)->ErroCtrl;
	  Rod->MDesv     += (Dad+Cuba)->Desv;
	  Rod->MFora     += (Dad+Cuba)->Fora;
	  MDesvTempo     += Temp.DesvTempo[Cuba];
	  MForaTempo     += Temp.ForaTempo[Cuba];
	  ++ContMed;
	}
	else
	{
	  (Dad+Cuba)->Placa = 0.0;
	  (Dad+Cuba)->Alvo  = 0.0;
	  (Dad+Cuba)->ErroTot = 0.0;
	  (Dad+Cuba)->ErroCtrl = 0.0;
	  (Dad+Cuba)->Desv = 0.0;
	  (Dad+Cuba)->Fora = 0.0;
	  Temp.DesvTempo[Cuba] = 0;
	  MontaHoraMin(Temp.DesvTempo[Cuba], (Dad+Cuba)->DesvTempo, "%3d:%02d");
	  Temp.ForaTempo[Cuba] = 0;
	  MontaHoraMin(Temp.ForaTempo[Cuba], (Dad+Cuba)->ForaTempo, "%3d:%02d");
	}
  }

  if ( ContMed > 0 )
  {
	/* calcula as medias montando-as no rodape */
	Rod->MPlaca    = Rod->MPlaca / ContMed;
	Rod->MAlvo     = Rod->MAlvo  / ContMed;
	Rod->MLiqui    = Rod->MLiqui / ContMed;
	Rod->MTotal    = Rod->MTotal / ContMed;
	Rod->MErroTot  = Rod->MErroTot / ContMed;
	Rod->MErroCtrl = Rod->MErroCtrl / ContMed;
	Rod->MDesv     = Rod->MDesv  / ContMed;
	Rod->MFora     = Rod->MFora  / ContMed;
	MDesvTempo     = MDesvTempo  / ContMed;
	MontaHoraMin(MDesvTempo, Rod->MDesvTempo, "%3d:%02d");
	MForaTempo     = MForaTempo / ContMed;
	MontaHoraMin(MForaTempo, Rod->MForaTempo, "%3d:%02d");
}

/*--- ALTERADO POR HEVELTON JUNIOR EM 23/10/92:
	     Libera o buffer alocado na funcao CarBufCubas ---*/
  free(HAvlAvc);
  return(Indice);  /* numero de linhas prenchidas */

}

/*
------------------------------------------------------------------------------
  IniDados - Inicializa cabecalho e area de dados do relatorio
------------------------------------------------------------------------------
*/
void IniDados(t_args *Arg, t_cabec *Cab, t_dados *Dad, t_rodape *Rod,
			  t_tempo *Temp)
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
  Cab->VLinha     = 0.0;
  Cab->VCuba     = 0.0;
#ifdef	REL_TURNO
  memset(Cab->Turno, 0x00, MAX_ID_TURNO);
  strncpy(Cab->Turno,AVL.IdentTurno[Arg->Turno],MAX_ID_TURNO);
#endif
  /*-- Inicializa area de dados --*/
  for( Indice = 0; Indice < MAX_CUBAS; ++Indice )
  {
    sprintf((Dad+Indice)->SinEst, "%1s", " ");
	(Dad+Indice)->Placa    = 0.0;
	(Dad+Indice)->Alvo     = 0.0;
	(Dad+Indice)->Liqui    = 0.0;
    (Dad+Indice)->Total    = 0.0;
	(Dad+Indice)->ErroTot  = 0.0;
	(Dad+Indice)->ErroCtrl = 0.0;
    (Dad+Indice)->Desv     = 0.0;
    (Dad+Indice)->Fora     = 0.0;
	Temp->DesvTempo[Indice]= 0;
    Temp->ForaTempo[Indice]= 0;
  }
  /*-- Inicializa rodape */
  Rod->MPlaca    = 0.0;
  Rod->MAlvo     = 0.0;
  Rod->MLiqui    = 0.0;
  Rod->MTotal    = 0.0;
  Rod->MErroTot  = 0.0;
  Rod->MErroCtrl = 0.0;
  Rod->MDesv     = 0.0;
  Rod->MFora     = 0.0;
  sprintf(Rod->MDesvTempo, "%s", TEMPO_NUL);
  sprintf(Rod->MForaTempo, "%s", TEMPO_NUL);
}


/*
------------------------------------------------------------------------------
  CalcAreaDados - Calcula area de dados do relatorio
------------------------------------------------------------------------------
*/
void CalcAreaDados(t_dados *Dad, int Cuba, int Ind, t_tempo *Temp, t_hist *HAvlAvc)
{
  float Alvo;
  float Desv;
  float Total;
  float ErroTot;
  float Fora;
  float Liqui;

  (Dad+Ind)->NumCuba = ConvCubScoreOper(Cuba);

  if ((HIST_AVC(Cuba).EstPrincDia ne CUBA_NORMAL) and
	  ((Dad+Ind)->SinEst[0] ne '+'))
	sprintf((Dad+Ind)->SinEst, "%1s", "+");

  (Dad+Ind)->Placa += HIST_AVC(Cuba).VSetPointDia;

  /* Inicio Alteracao - Carlos - 23/06/99 */
  /* Tratamento de booster de corrente */
 #ifdef	BOOSTER_CORRENTE
  Alvo = (HIST_AVC(Cuba).RAlvoDia * HIST_AVC(Cuba).IAlvoCubaDia + HIST_AVC(Cuba).BemfDia);
  Alvo = (float) (Round((double)Alvo*100.0)/100.0);
  (Dad+Ind)->Alvo += Alvo;

  Liqui = HIST_AVC(Cuba).RDiaLiq * HIST_AVC(Cuba).IAlvoCubaDia;

  Total = HIST_AVC(Cuba).RDiaBruta * HIST_AVC(Cuba).IAlvoCubaDia;
 #else
  Alvo = (HIST_AVC(Cuba).RAlvoDia * HIST_AVL.IAlvoDia + HIST_AVC(Cuba).BemfDia);
  Alvo = (float) (Round((double)Alvo*100.0)/100.0);
  (Dad+Ind)->Alvo += Alvo;

  Liqui = HIST_AVC(Cuba).RDiaLiq * HIST_AVL.IAlvoDia;

  Total = HIST_AVC(Cuba).RDiaBruta * HIST_AVL.IAlvoDia;
 #endif
  /* Fim Alteracao - Carlos - 23/06/99 */

  if ((HIST_AVC(Cuba).EstPrincDia eq CUBA_NORMAL) or
	  (HIST_AVC(Cuba).EstPrincDia eq CUBA_PARTIDA))
  {
	Liqui += HIST_AVC(Cuba).BemfDia;
	Total += HIST_AVC(Cuba).BemfDia;
  }

  Liqui = (float) (Round((double)Liqui*100.0)/100.0);
  (Dad+Ind)->Liqui += Liqui;

  Total = (float) (Round((double)Total*100.0)/100.0);
  (Dad+Ind)->Total += Total;

  ErroTot = (Alvo - Liqui);
  ErroTot = (float) (Round((double)ErroTot*100.0)/100.0);
  (Dad+Ind)->ErroTot += ErroTot;
  if (HIST_AVC(Cuba).NumCContDia ne 0)
  {
	Desv = (HIST_AVC(Cuba).VDesvDia / HIST_AVC(Cuba).NumCContDia);
	Desv = (float) (Round((double)Desv*100.0)/100.0);
	(Dad+Ind)->Desv += Desv;
	Temp->DesvTempo[Ind] += (HIST_AVC(Cuba).VDesvDurDia / 60 );
	Fora = (HIST_AVC(Cuba).VForaContDia / HIST_AVC(Cuba).NumCContDia);
	Fora = (float) (Round((double)Fora*100.0)/100.0);
	(Dad+Ind)->Fora += Fora;
	Temp->ForaTempo[Ind] += ( HIST_AVC(Cuba).ForaContDurDia / 60 );
	(Dad+Ind)->ErroCtrl += (float) ((Round((double)ErroTot*100.0) -
			(Round((double)Desv*100.0) + Round((double)Fora*100.0))) / 100.0);
  }
}
