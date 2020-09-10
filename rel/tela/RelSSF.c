/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DAS SALAS 125 KA I E VII

	ARQUIVO		: RelSSF.c

	CONTEUDO	: Programa que exporta dados diarios para o Sistema de Informacao
					Salas Fornos

	AUTOR		: Marco Aurelio M. Lopes

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 01 - 24/01/13

	HISTORICO DAS EDICOES

-------------------------------------------------------------------------------
dd/mm/aa   | Descricao                                               | autor
-------------------------------------------------------------------------------
24/01/2013 | Edicao inicial                                          | Marco
-------------------------------------------------------------------------------

******************************************************************************/

/*-- INDICA QUE ESTE E' O PROGRAMA PRINCIPAL --*/

#define	PROGRAMA_PRINCIPAL
#define	RELATORIO_HISTORICO

/*-- INCLUSAO DE OUTROS ARQUIVOS --*/

#include <RelSSF.h>

/*-- PROTOTIPOS DAS FUNCOES INTERNAS --*/

void main( int argc , char *argv[] );
int  ConsisteArg(char *argv[], t_args *Arg);
void IniDados(t_args *Arg, t_cabec *Cab, t_dados *Dad, t_rodape *Rod);
void CalcAreaDados(t_dados *Dad, int CubaAtual, int Ind, t_hist *HAvlAvc, t_args *Arg);
int GeraDadosRel(t_args *Arg, t_cabec *Cab, t_dados *Dad, t_rodape *Rod, FILE *fp);

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
#include <ScoreErros.h>
#include <ScoreMsgs.h>

/*-- Inicio --*/

  t_cabec	Cab;
  t_dados	*Dad;
  t_rodape  Rod;
  t_args	Arg;
  char		NomeArq[32];
  char		Msg[80];
  char		NomeRel[32];
  int		NLinhas;
  FILE		*fp;
  time_t	HoraAtual;
  struct  tm DataTm;
  char sala[3];
  short int SF;


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

  strcpy(NomeRel, My_name);
  
  SF = Comum->IdentReducao;

  if (SF > 5)
	SF -= 2;


  if (argc eq NUM_ARGS)
  {
	if (ConsisteArg(argv, &Arg) eq RET_FUNCAO_OK)
	{
	  sprintf(NomeArq, "/score/relatorio/RelSSF%1i_%d_%d_%02d", SF, 
				Arg.DiaInicial, Arg.MesInicial, Arg.AnoInicial);
	  fp = fopen (NomeArq, "w");
	  if (fp eq NULL)
	  {
   	    /* ERRO */
	  }  
	  fprintf(fp, " 					RELATORIO DIARIO DE EXPORTACAO - SCORE \n");
	  fprintf(fp, "CubaInicial: %04d     CubaFinal: %04d   DataInicial: %02d/%02d/%02d    DataFinal: %02d/%02d/%02d \n", 
				Arg.CubaInicial, Arg.CubaFinal, Arg.DiaInicial, Arg.MesInicial, Arg.AnoInicial, Arg.DiaFinal, Arg.MesFinal,
				Arg.AnoFinal);
	  fprintf(fp, "   Data   Cuba    VPlaca   Incr.   VTotal   R.Rap   R.Len   FreqEA   VMaxEA   DurEA	AlF3   CaF2   Banho   Metal   Temp	Vida   Corr. Ligada\n");

	  if ((NLinhas = GeraDadosRel(&Arg, &Cab, Dad, &Rod, fp)) > 0)
	  {
		fclose (fp);

	  }
	  else
	  {
		if (NLinhas eq 0)
		  ExibeErro(ScoreGetStr(SCORE_MSG_44));
	  }
	}
  }
  else if (argc eq 1)
  {
  
    HoraAtual = time(NULL) - 86400;
    
    memcpy(&DataTm, localtime(&HoraAtual), sizeof(struct tm));

	if (Comum->IdentReducao eq 1)
	{
	  Arg.CubaInicial = 101;
	  Arg.CubaFinal = 275;
	  Arg.MesInicial = DataTm.tm_mon + 1;
	  Arg.DiaInicial = DataTm.tm_mday;
	  Arg.AnoInicial = TM_YEAR_TO_2DIGIT(DataTm.tm_year);
	  Arg.DiaFinal = DataTm.tm_mday;
	  Arg.MesFinal = DataTm.tm_mon + 1;
	  Arg.AnoFinal = TM_YEAR_TO_2DIGIT(DataTm.tm_year); 
	  strcpy(sala,"S1");
	}
	if (Comum->IdentReducao eq 2)
	{
	  Arg.CubaInicial = 301;
	  Arg.CubaFinal = 480;
	  Arg.MesInicial = DataTm.tm_mon + 1;
	  Arg.DiaInicial = DataTm.tm_mday;
	  Arg.AnoInicial = TM_YEAR_TO_2DIGIT(DataTm.tm_year);
	  Arg.DiaFinal = DataTm.tm_mday;
	  Arg.MesFinal = DataTm.tm_mon + 1;
	  Arg.AnoFinal = TM_YEAR_TO_2DIGIT(DataTm.tm_year); 
	  strcpy(sala,"S2");
	}
	if (Comum->IdentReducao eq 3)
	{
	  Arg.CubaInicial = 501;
	  Arg.CubaFinal = 679;
	  Arg.MesInicial = DataTm.tm_mon + 1;
	  Arg.DiaInicial = DataTm.tm_mday;
	  Arg.AnoInicial = TM_YEAR_TO_2DIGIT(DataTm.tm_year);
	  Arg.DiaFinal = DataTm.tm_mday;
	  Arg.MesFinal = DataTm.tm_mon + 1;
	  Arg.AnoFinal = TM_YEAR_TO_2DIGIT(DataTm.tm_year); 
	  strcpy(sala,"S3");
	}
	if (Comum->IdentReducao eq 4)
	{
	  Arg.CubaInicial = 701;
	  Arg.CubaFinal = 880;
	  Arg.MesInicial = DataTm.tm_mon + 1;
	  Arg.DiaInicial = DataTm.tm_mday;
	  Arg.AnoInicial = TM_YEAR_TO_2DIGIT(DataTm.tm_year);
	  Arg.DiaFinal = DataTm.tm_mday;
	  Arg.MesFinal = DataTm.tm_mon + 1;
	  Arg.AnoFinal = TM_YEAR_TO_2DIGIT(DataTm.tm_year); 
	  strcpy(sala,"S4");
	}
	if (Comum->IdentReducao eq 7)
	{
	  Arg.CubaInicial = 901;
	  Arg.CubaFinal = 1272;
	  Arg.MesInicial = DataTm.tm_mon + 1;
	  Arg.DiaInicial = DataTm.tm_mday;
	  Arg.AnoInicial = TM_YEAR_TO_2DIGIT(DataTm.tm_year);
	  Arg.DiaFinal = DataTm.tm_mday;
	  Arg.MesFinal = DataTm.tm_mon + 1;
	  Arg.AnoFinal = TM_YEAR_TO_2DIGIT(DataTm.tm_year); 
	  strcpy(sala,"S5");
	}
	if (Comum->IdentReducao eq 8)
	{
	  Arg.CubaInicial = 1301;
	  Arg.CubaFinal = 1641;
	  Arg.MesInicial = DataTm.tm_mon + 1;
	  Arg.DiaInicial = DataTm.tm_mday;
	  Arg.AnoInicial = TM_YEAR_TO_2DIGIT(DataTm.tm_year);
	  Arg.DiaFinal = DataTm.tm_mday;
	  Arg.MesFinal = DataTm.tm_mon + 1;
	  Arg.AnoFinal = TM_YEAR_TO_2DIGIT(DataTm.tm_year); 
	  strcpy(sala,"S6");
	}
	if (Comum->IdentReducao eq 9)
	{
	  Arg.CubaInicial = 1701;
	  Arg.CubaFinal = 2049;
	  Arg.MesInicial = DataTm.tm_mon + 1;
	  Arg.DiaInicial = DataTm.tm_mday;
	  Arg.AnoInicial = TM_YEAR_TO_2DIGIT(DataTm.tm_year);
	  Arg.DiaFinal = DataTm.tm_mday;
	  Arg.MesFinal = DataTm.tm_mon + 1;
	  Arg.AnoFinal = TM_YEAR_TO_2DIGIT(DataTm.tm_year); 
	  strcpy(sala,"S7");
	}
  sprintf(NomeArq, "/score/relatorio/RelSSF%1i_%d_%d_%02d", SF, 
			Arg.DiaInicial, Arg.MesInicial, Arg.AnoInicial);
  fp = fopen (NomeArq, "w");
  if (fp eq NULL)
  {
  	    /* ERRO */
  }  
  fprintf(fp, " 					RELATORIO DIARIO DE EXPORTACAO - SCORE \n");
  fprintf(fp, "CubaInicial: %04d     CubaFinal: %04d   DataInicial: %02d/%02d/%02d    DataFinal: %02d/%02d/%02d \n", 
			Arg.CubaInicial, Arg.CubaFinal, Arg.DiaInicial, Arg.MesInicial, Arg.AnoInicial, Arg.DiaFinal, Arg.MesFinal,
			Arg.AnoFinal);
  fprintf(fp, "   Data   Cuba    VPlaca   Incr.   VTotal   R.Rap   R.Len   FreqEA   VMaxEA   DurEA	AlF3   CaF2   Banho   Metal   Temp	Vida   Corr. Ligada\n");
  
	Arg.DiasDatas = 1;

    if ((NLinhas = GeraDadosRel(&Arg, &Cab, Dad, &Rod, fp)) > 0)
	{
	  fclose (fp);
	}
	else
	{
	  if (NLinhas eq 0)
		  ExibeErro(ScoreGetStr(SCORE_MSG_44));
	}
  }
  else
  {
	ExibeErro(ScoreGetStr(SCORE_MSG_210));
  }

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
  struct  tm DataTm;
  struct tm *StData;
  time_t HoraAtual;
  time_t DataIni, DataFim;
  char	 dia[3], mes[3], ano[3];

  /*-- Converte cuba inicial e final --*/
  Arg->CubaInicial = atoi(argv[1]);
  Arg->CubaFinal   = atoi(argv[2]);
  /*-- Faz consistencia do numero das cubas --*/
  if (ConsisteCubas(Arg->CubaInicial, Arg->CubaFinal) eq VERDADEIRO)
  {
	/*-- Verifica existencia de cuba na linha de exclusao --*/
	Arg->TabCubas[0] = -1;
  }
  else
	return(RET_FUNCAO_ERR);

  strcpy(DataI, argv[3]);
  strcpy(DataF, argv[4]);

  HoraAtual = time(NULL);
  StData = localtime(&HoraAtual);

  dia[0] = DataI[0];
  dia[1] = DataI[1];
  mes[0] = DataI[3];
  mes[1] = DataI[4];
  ano[0] = DataI[6];
  ano[1] = DataI[7];
  Arg->DiaInicial = atoi(dia);
  Arg->MesInicial = atoi(mes);
  Arg->AnoInicial = atoi(ano);
  
  dia[0] = DataF[0];
  dia[1] = DataF[1];
  mes[0] = DataF[3];
  mes[1] = DataF[4];
  ano[0] = DataF[6];
  ano[1] = DataF[7];
  Arg->DiaFinal = atoi(dia);
  Arg->MesFinal = atoi(mes);
  Arg->AnoFinal = atoi(ano);
  if ((Arg->MesInicial eq Arg->MesFinal) and
		(Arg->DiaFinal >= Arg->DiaInicial) )
  	Arg->DiasDatas = Arg->DiaFinal - Arg->DiaInicial +1;
  else
  {

    /*-- inicializa data auxiliar --*/ 
    DataTm.tm_sec  = 0;
    DataTm.tm_min  = 0;
    DataTm.tm_hour = 12;
    DataTm.tm_mday = Arg->DiaInicial;
    DataTm.tm_mon  = Arg->MesInicial - 1;
    DataTm.tm_year = TWO_DIGIT_TO_TM_YEAR(Arg->AnoInicial);

    DataIni = mktime(&DataTm); /* converte para time_t */

    /*-- inicializa data auxiliar --*/ 
    DataTm.tm_sec  = 0;
    DataTm.tm_min  = 0;
    DataTm.tm_hour = 12;
    DataTm.tm_mday = Arg->DiaFinal;
    DataTm.tm_mon  = Arg->MesFinal - 1;
    DataTm.tm_year = TWO_DIGIT_TO_TM_YEAR(Arg->AnoFinal);

    DataFim = mktime(&DataTm); /* converte para time_t */

	DataFim -= DataIni;	

	DataFim = DataFim / 86400;
	
	DataFim = DataFim - Arg->DiaFinal + 1;

    Arg->DiasDatas = Arg->DiaFinal - Arg->DiaInicial + 1;
	Arg->DiasDatas += DataFim;
  }

	/*-- Consiste exclusao de data --*/
	Arg->TabDatas[0] = -1;
  

  return(RET_FUNCAO_OK);
}

/*
-------------------------------------------------------------------------------
  GeraDadosRel - Calcula  as  variaveis e medias  a  serem  exibidas  no 
                 relatorio,montando os campos variaveis do Cab, area  de
                 Dad e Rod do relatorio.                                 
-------------------------------------------------------------------------------
*/
int GeraDadosRel(t_args *Arg, t_cabec *Cab, t_dados *Dad, t_rodape *Rod, FILE *fp)
{
  int     ContDia;
  int	  NumDias;
  int	  i;
  int	  Cuba;
  int	  CubaAtual;
  int	  Indice;
  time_t  HoraAtual;
  time_t  TimeTAtual;
  time_t  TimeT;
  struct  tm DataTm;
  t_hist  *HAvlAvc;
  time_t  DataAnalise;
  struct tm *DataAna;
  time_t difsecs;
  int     difdias;	

  /*-- Pega hora atual --*/
  HoraAtual = time(NULL);

  /*-- Calcula hora atual para referencia --*/
  memcpy(&DataTm, localtime(&HoraAtual), sizeof(struct tm));
  DataTm.tm_sec  = 0;
  DataTm.tm_min  = 0;
  DataTm.tm_hour = 12;
  TimeTAtual = mktime(&DataTm);

  /*-- Inicializa cubas de Cab --*/
  Cab->CubaInicial = Arg->CubaInicial;
  Cab->CubaFinal   = Arg->CubaFinal;

  /*-- Inicializa estruturas do relatorio --*/
  IniDados(Arg, Cab, Dad, Rod);

  /*-- inicializa data auxiliar --*/ 
  DataTm.tm_sec  = 0;
  DataTm.tm_min  = 0;
  DataTm.tm_hour = 12;
  DataTm.tm_mday = Arg->DiaInicial;
  DataTm.tm_mon  = Arg->MesInicial - 1;
  DataTm.tm_year = TWO_DIGIT_TO_TM_YEAR(Arg->AnoInicial);

  TimeT = mktime(&DataTm); /* converte para time_t */

  difsecs = HoraAtual - TimeT - 43200;
  difdias = difsecs / 86400;

  NumDias = 0;
  Indice = 0;

  /* executa para todos os dias */
  for( ContDia = 0; ContDia < Arg->DiasDatas; ++ContDia )
  {

	if (ValidaData(Arg, TimeT) ne VERDADEIRO)
	{
	  TimeT += (time_t)( NUM_SEGUNDOS_DIA * TIMES_PER_SEC ); /* avanca um dia */
	  memcpy(&DataTm, localtime(&TimeT), sizeof(struct tm));  /* converte para struct tm */
	  continue; /* proxima ContDia */
	}

    HAvlAvc = CarBufCubas(&DataTm, Arg);

    if( HAvlAvc eq (void *) NULL ) /* houve erro */
      return(-1);
    /* inicializa cuba inicial para cada dia */

	DataAnalise = HIST_AVL.Trab.DataImport;

	DataAna = localtime(&DataAnalise);
	
  	fprintf(fp, "DataAnalise: %02d/%02d/%04d\n", DataAna->tm_mday, DataAna->tm_mon + 1, DataAna->tm_year + 1900);
  	fprintf(fp, "Corrente: %06.2f Tensao: %07.2f \n", HIST_AVL.IMedDia / 1000, HIST_AVL.VLinhaDia );

	for (Cuba = Arg->CubaInicial; Cuba <= Arg->CubaFinal; ++Cuba)
	{
	  CubaAtual = ConvCubOperScore(Cuba);
	  if ((CubaAtual ne -1))
	  {
    	CalcAreaDados(Dad, CubaAtual, Indice, HAvlAvc, Arg);
	    
		(Dad+Indice)->Vida -= difdias;
	    if ( (Dad+Indice)->Total < 10)
		{
		  fprintf(fp, " %02d/%02d/%04d	%04i	%04.2f	%03i	%04.2f	%05.1f	%05.1f	%02i	%05.2f	%04.0f	%05.2f	%05.2f	%02i	%02i	%04i	%04i	%06.2f	%3s	%04.2f	%04.2f	%02i	%02i	%02i	%05.2f	%02i	%02i	%02i	%02i	%02i	%02i	%02i	%010i	%010i	%010i	%02i	%02i	%02i	%05.3f	%05.3f	%05.3f	%05.3f	%05.3f	%05.3f	%05.3f	%05.3f	%07.3f\n", DataTm.tm_mday, 
				DataTm.tm_mon+1,DataTm.tm_year + 1900, (Dad+Indice)->NumCuba, (Dad+Indice)->Placa, (Dad+Indice)->Inc,
				(Dad+Indice)->Total, (Dad+Indice)->RRap, (Dad+Indice)->RLen, (Dad+Indice)->FreqEA, (Dad+Indice)->VMaxEA, 
				(Dad+Indice)->DurEA, (Dad+Indice)->Fluoreto, (Dad+Indice)->Fluorita, (Dad+Indice)->Banho, (Dad+Indice)->Metal, 
				(Dad+Indice)->Temp, (Dad+Indice)->Vida, (Dad+Indice)->Corrente/1000, (Dad+Indice)->Ligada, (Dad+Indice)->VLiquida, 
				(Dad+Indice)->VAlvo, (Dad+Indice)->MovCima, (Dad+Indice)->MovBaixo, (Dad+Indice)->FalhaMov, (Dad+Indice)->VMedEa, 
				(Dad+Indice)->QP, (Dad+Indice)->PrevEa, (Dad+Indice)->NQueb, (Dad+Indice)->EaMenor24h, (Dad+Indice)->EaMaior72h, 
				(Dad+Indice)->EaMaior96h, (Dad+Indice)->AdFluoreto, (Dad+Indice)->IntervCorr, (Dad+Indice)->IntervRefCorr, (Dad+Indice)->IntervRefQueb,
				(Dad+Indice)->NumDBDia, (Dad+Indice)->NumDBConsec, (Dad+Indice)->NumDBQueb, (Dad+Indice)->DifAlFalhaMov, (Dad+Indice)->DifAlBandaMorta,
				(Dad+Indice)->DifAlInibPrev, (Dad+Indice)->DifAlInibQueb, (Dad+Indice)->DifAlIntervMov, (Dad+Indice)->DifAlManual, 
				(Dad+Indice)->DifAlInibUsu, (Dad+Indice)->DifAlDesvio, (Dad+Indice)->DeltaR); 
		}
		else
		{
		  fprintf(fp, " %02d/%02d/%04d	%04i	%04.2f	%03i	%04.1f	%05.1f	%05.1f	%02i	%05.2f	%04.0f	%05.2f	%05.2f	%02i	%02i	%04i	%04i	%06.2f	%3s	%04.2f	%04.2f	%02i	%02i	%02i	%05.2f	%02i	%02i	%02i	%02i	%02i	%02i	%02i	%010i	%010i	%010i	%02i	%02i	%02i	%05.3f	%05.3f	%05.3f	%05.3f	%05.3f	%05.3f	%05.3f	%05.3f,	%07.3f\n", DataTm.tm_mday, 
				DataTm.tm_mon+1,DataTm.tm_year + 1900, (Dad+Indice)->NumCuba, (Dad+Indice)->Placa, (Dad+Indice)->Inc,
				(Dad+Indice)->Total, (Dad+Indice)->RRap, (Dad+Indice)->RLen, (Dad+Indice)->FreqEA, (Dad+Indice)->VMaxEA, 
				(Dad+Indice)->DurEA, (Dad+Indice)->Fluoreto, (Dad+Indice)->Fluorita, (Dad+Indice)->Banho, (Dad+Indice)->Metal, 
				(Dad+Indice)->Temp, (Dad+Indice)->Vida, (Dad+Indice)->Corrente/1000, (Dad+Indice)->Ligada, (Dad+Indice)->VLiquida, 
				(Dad+Indice)->VAlvo, (Dad+Indice)->MovCima, (Dad+Indice)->MovBaixo, (Dad+Indice)->FalhaMov, (Dad+Indice)->VMedEa, 
				(Dad+Indice)->QP, (Dad+Indice)->PrevEa, (Dad+Indice)->NQueb, (Dad+Indice)->EaMenor24h, (Dad+Indice)->EaMaior72h, 
				(Dad+Indice)->EaMaior96h, (Dad+Indice)->AdFluoreto, (Dad+Indice)->IntervCorr, (Dad+Indice)->IntervRefCorr, (Dad+Indice)->IntervRefQueb,
				(Dad+Indice)->NumDBDia, (Dad+Indice)->NumDBConsec, (Dad+Indice)->NumDBQueb, (Dad+Indice)->DifAlFalhaMov, (Dad+Indice)->DifAlBandaMorta,
				(Dad+Indice)->DifAlInibPrev, (Dad+Indice)->DifAlInibQueb, (Dad+Indice)->DifAlIntervMov, (Dad+Indice)->DifAlManual, 
				(Dad+Indice)->DifAlInibUsu, (Dad+Indice)->DifAlDesvio, (Dad+Indice)->DeltaR); 
		}
		++Indice;
	  }
		
	}

    TimeT += (time_t)( NUM_SEGUNDOS_DIA * TIMES_PER_SEC ); /* avanca um dia */
    memcpy (&DataTm, localtime(&TimeT), sizeof(struct tm)); /* converte para struct tm */
	
	++NumDias; /* incrementa numero de dias para calculo das medias */

  } /*-- for (ContDia ...) --*/

  /*-- Sai da funcao quando nao houver informacoes a exibir --*/
  if ( NumDias eq 0)
	return(0);

  if ( NumDias > 0 )
  {
	/* calcula as medias montando-as no rodape */
	for( i = 0 ; i <= NumDias ; i++)
	{
	  Rod->MPlaca    += (Dad+i)->Placa;
	  Rod->MTotal    += (Dad+i)->Total;
	}
	
	Rod->MPlaca	   = Rod->MPlaca / NumDias;
	Rod->MAlvo	   = Rod->MAlvo  / NumDias;
	Rod->MLiqui	   = Rod->MLiqui / NumDias;
	Rod->MTotal	   = Rod->MTotal / NumDias;
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
  /*-- Inicializa area de dados --*/
  for( Indice = 0; Indice < MAX_CUBAS; ++Indice )
  {
	(Dad+Indice)->NumCuba = 0;
	(Dad+Indice)->Placa = 0;
	(Dad+Indice)->Inc = 0;
	(Dad+Indice)->Total = 0;
	(Dad+Indice)->RRap = 0;
	(Dad+Indice)->RLen = 0;
	(Dad+Indice)->FreqEA = 0;
	(Dad+Indice)->VMaxEA = 0;
	(Dad+Indice)->Fluoreto = 0;
	(Dad+Indice)->Fluorita = 0;
	(Dad+Indice)->Banho = 0;
	(Dad+Indice)->Metal = 0;
	(Dad+Indice)->Temp = 0;
	(Dad+Indice)->Vida = 0;
	(Dad+Indice)->Corrente = 0;
	(Dad+Indice)->DurEA = 0;
	(Dad+Indice)->VLiquida = 0;
	(Dad+Indice)->VAlvo = 0;
	(Dad+Indice)->MovCima = 0;
	(Dad+Indice)->MovBaixo = 0;
	(Dad+Indice)->FalhaMov = 0;
	(Dad+Indice)->VMedEa = 0;
	(Dad+Indice)->QP = 0;
	(Dad+Indice)->PrevEa = 0;
	(Dad+Indice)->EaMenor24h = 0;
	(Dad+Indice)->EaMaior72h = 0;
	(Dad+Indice)->EaMaior96h = 0;
	(Dad+Indice)->NQueb = 0;
	(Dad+Indice)->AdFluoreto = 0;
	(Dad+Indice)->IntervCorr = 0;   
	(Dad+Indice)->IntervRefCorr = 0;   
	(Dad+Indice)->IntervRefQueb = 0;   
	(Dad+Indice)->NumDBDia = 0;
	(Dad+Indice)->NumDBConsec = 0;
	(Dad+Indice)->NumDBQueb = 0;
	(Dad+Indice)->DifAlFalhaMov = 0;
	(Dad+Indice)->DifAlBandaMorta = 0;
	(Dad+Indice)->DifAlInibPrev = 0;
	(Dad+Indice)->DifAlInibQueb = 0;
	(Dad+Indice)->DifAlIntervMov = 0;
	(Dad+Indice)->DifAlManual = 0;
	(Dad+Indice)->DifAlInibUsu = 0;
	(Dad+Indice)->DifAlDesvio = 0;
	(Dad+Indice)->DeltaR = 0;
	sprintf((Dad+Indice)->Ligada, "Nao");
  }	
  /*-- Inicializa rodape */
  Rod->MPlaca    = 0.0;
  Rod->MAlvo     = 0.0;
  Rod->MLiqui    = 0.0;
  Rod->MTotal    = 0.0;
}


/*
------------------------------------------------------------------------------
  CalcAreaDados - Calcula area de dados do relatorio
------------------------------------------------------------------------------
*/
void CalcAreaDados(t_dados *Dad, int CubaAtual, int Ind, t_hist *HAvlAvc, t_args *Arg)
{
  double AuxTotal, AuxAlvo, AuxInc, AuxRRap, AuxRLen, RLen, RRap;
  int Inc;

  (Dad+Ind)->NumCuba = ConvCubScoreOper(CubaAtual);
  if ((HIST_AVC(CubaAtual).EstPrincDia eq CUBA_NORMAL) or
     (HIST_AVC(CubaAtual).EstPrincDia eq CUBA_PARTIDA))
  {  	
	  (Dad+Ind)->Placa = HIST_AVC(CubaAtual).VSetPointDia;
	  (Dad+Ind)->VLiquida = HIST_AVC(CubaAtual).VDiaLiq;

 #ifdef	BOOSTER_CORRENTE
      AuxTotal = HIST_AVC(CubaAtual).RDiaBruta * HIST_AVC(CubaAtual).IAlvoCubaDia;
      AuxAlvo = HIST_AVC(CubaAtual).RAlvoDia * HIST_AVC(CubaAtual).IAlvoCubaDia;
      AuxInc = HIST_AVC(CubaAtual).IncTotDia * 1000;
	  AuxRRap = HIST_AVC(CubaAtual).RRapNormDia * HIST_AVC(CubaAtual).IAlvoCubaDia; 
	  AuxRLen = HIST_AVC(CubaAtual).RLentNormDia * HIST_AVC(CubaAtual).IAlvoCubaDia; 
 #else
      AuxTotal = HIST_AVC(CubaAtual).RDiaBruta * HIST_AVL.IAlvoDia + ;
      AuxAlvo = HIST_AVC(CubaAtual).RAlvoDia * HIST_AVL.IAlvoDia;
      AuxInc = HIST_AVC(CubaAtual).IncTotDia * 1000;
	  AuxRRap = HIST_AVC(CubaAtual).RRapNormDia * HIST_AVC(CubaAtual).IAlvoDia; 
	  AuxRLen =  HIST_AVC(CubaAtual).RLentNormDia * HIST_AVC(CubaAtual).IAlvoDia; 
 #endif
    /* Fim Alteracao - Carlos - 23/06/99 */

	  AuxTotal += HIST_AVC(CubaAtual).BemfDia;
	  AuxAlvo += HIST_AVC(CubaAtual).BemfDia;

      AuxTotal = (float) (Round((double)AuxTotal*100.0)/100.0);
      AuxAlvo = (float) (Round((double)AuxAlvo*100.0)/100.0);
      AuxInc = (float) (Round((double)AuxInc*100.0)/100.0);
      AuxRRap = (AuxRRap * 1000);
      AuxRLen = (AuxRLen * 1000);
	  RRap = AuxRRap;
	  RLen = AuxRLen;
	  Inc = (int)AuxInc;

  	  (Dad+Ind)->Total  = AuxTotal;
  	  (Dad+Ind)->VAlvo  = AuxAlvo;

	  if((AuxInc - Inc) >= 0.5)
	  {
	    (Dad+Ind)->Inc	= (int)AuxInc + 1; 
	  }
	  else
	  {
	    (Dad+Ind)->Inc	= (int)AuxInc; 
	  }
	  if((AuxRRap - RRap) >= 0.5)
	  {
	    (Dad+Ind)->RRap	= AuxRRap + 1;
	  }
	  else
	  {
	    (Dad+Ind)->RRap	= AuxRRap;
  	  }
	  if((AuxRLen - RLen) >= 0.5)
	  {
	    (Dad+Ind)->RLen	= AuxRLen + 1;
	  }
	  else
	  {
	    (Dad+Ind)->RLen	= AuxRLen;
	  }
	  (Dad+Ind)->FreqEA	= HIST_AVC(CubaAtual).EaNumDia;
	  (Dad+Ind)->VMaxEA	= HIST_AVC(CubaAtual).EaVMaxDia;
	  if ((Dad+Ind)->FreqEA > 0)
	  {
		(Dad+Ind)->DurEA = HIST_AVC(CubaAtual).EaDurDia / (Dad+Ind)->FreqEA;
	    (Dad+Ind)->VMedEa	= HIST_AVC(CubaAtual).EaVDiaTotBruta / HIST_AVC(CubaAtual).EaNumLDia;
	  }	
//	  else
//	  	(Dad+Ind)->DurEA  = 0;	
//		(Dad+Ind)->VMedEa = 0;

	  (Dad+Ind)->MovBaixo	= HIST_AVC(CubaAtual).MovBaixoNumDia;
	  (Dad+Ind)->MovCima	= HIST_AVC(CubaAtual).MovCimaNumDia; 	
	  (Dad+Ind)->FalhaMov	= HIST_AVC(CubaAtual).FalhaMovDia; 	

	  (Dad+Ind)->Corrente = HIST_AVL.IMedDia; 
	  sprintf((Dad+Ind)->Ligada, "Sim");

	  (Dad+Ind)->EaMenor24h = HIST_AVC(CubaAtual).ContIntEa[0] + 
								HIST_AVC(CubaAtual).ContIntEa[1] +
								HIST_AVC(CubaAtual).ContIntEa[2];

	  (Dad+Ind)->EaMaior72h = HIST_AVC(CubaAtual).ContIntEa[11] + 
								HIST_AVC(CubaAtual).ContIntEa[12] +
								HIST_AVC(CubaAtual).ContIntEa[13] +
								HIST_AVC(CubaAtual).ContIntEa2[0] +
								HIST_AVC(CubaAtual).ContIntEa2[1];

	  (Dad+Ind)->EaMaior96h = HIST_AVC(CubaAtual).ContIntEa[13] + 
								HIST_AVC(CubaAtual).ContIntEa2[0] + 
								HIST_AVC(CubaAtual).ContIntEa2[1];

	(Dad+Ind)->PrevEa = HIST_AVC(CubaAtual).NumPrevEaDia; 
	(Dad+Ind)->QP = HIST_AVC(CubaAtual).Sup.NumQuebPrevDia;	
	(Dad+Ind)->NQueb = HIST_AVC(CubaAtual).QuebNumDia;	
	(Dad+Ind)->IntervCorr = HIST_AVC(CubaAtual).Sup.IntervCorrDia;	
	(Dad+Ind)->IntervRefCorr = HIST_AVC(CubaAtual).Sup.IntervRefCorrDia;	
	(Dad+Ind)->IntervRefQueb = HIST_AVC(CubaAtual).Sup.IntervRefQuebDia;	
	(Dad+Ind)->NumDBDia = HIST_AVC(CubaAtual).Sup.NumDBDia;		
	(Dad+Ind)->NumDBConsec = HIST_AVC(CubaAtual).Sup.NumDBConsec;		
	(Dad+Ind)->NumDBQueb = HIST_AVC(CubaAtual).Sup.NumDBQueb;		
	if(HIST_AVC(CubaAtual).Sup.DeltaRCorr >= 0)
	  (Dad+Ind)->DeltaR = HIST_AVC(CubaAtual).Sup.DeltaRCorr;		
	if(HIST_AVC(CubaAtual).Sup.DifALFalhaMov > 0)
	  (Dad+Ind)->DifAlFalhaMov = HIST_AVC(CubaAtual).Sup.DifALFalhaMov;		
	if(HIST_AVC(CubaAtual).Sup.DifALBandaMorta > 0)
 	  (Dad+Ind)->DifAlBandaMorta = HIST_AVC(CubaAtual).Sup.DifALBandaMorta;		
	if(HIST_AVC(CubaAtual).Sup.DifALInibPrev > 0)
	  (Dad+Ind)->DifAlInibPrev = HIST_AVC(CubaAtual).Sup.DifALInibPrev;		
	if(HIST_AVC(CubaAtual).Sup.DifALInibQueb > 0)
	  (Dad+Ind)->DifAlInibQueb = HIST_AVC(CubaAtual).Sup.DifALInibQueb;		
	if(HIST_AVC(CubaAtual).Sup.DifALInibUsu > 0)
	  (Dad+Ind)->DifAlInibUsu = HIST_AVC(CubaAtual).Sup.DifALInibUsu;		
	if(HIST_AVC(CubaAtual).Sup.DifALIntervMov > 0)
	  (Dad+Ind)->DifAlIntervMov = HIST_AVC(CubaAtual).Sup.DifALIntervMov;		
	if(HIST_AVC(CubaAtual).Sup.DifALManual > 0)
	  (Dad+Ind)->DifAlManual = HIST_AVC(CubaAtual).Sup.DifALManual;		
	if(HIST_AVC(CubaAtual).Sup.DifALDesvio > 0)
	  (Dad+Ind)->DifAlDesvio = HIST_AVC(CubaAtual).Sup.DifALDesvio;		
  }
  else
  {
	sprintf((Dad+Ind)->Ligada, "Nao");

	(Dad+Ind)->Vida = AVC.User1[CubaAtual].Vida;
  }
  (Dad+Ind)->Fluoreto	= HIST_AVC(CubaAtual).Sup.CNF_SUP.Fluoreto;
  (Dad+Ind)->Fluorita	= HIST_AVC(CubaAtual).Sup.CNF_SUP.Fluorita;
  (Dad+Ind)->Banho	= HIST_AVC(CubaAtual).Sup.CNF_SUP.Banho;
  (Dad+Ind)->Metal	= HIST_AVC(CubaAtual).Sup.CNF_SUP.Metal;
  (Dad+Ind)->Temp	= HIST_AVC(CubaAtual).Sup.CNF_SUP.Temperatura;
  (Dad+Ind)->AdFluoreto	= AVC.User1[CubaAtual].AdFluoreto;

}
