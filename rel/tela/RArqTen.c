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

#include <RArqTen.h>

/*-- PROTOTIPOS DAS FUNCOES INTERNAS --*/

void main( int argc , char *argv[] );
int  ConsisteArg(char *argv[], t_args *Arg);
void IniDados(t_args *Arg, t_cabec *Cab, t_dados *Dad, t_rodape *Rod);
void CalcAreaDados(t_dados *Dad, int CubaInicial, int CubaFinal, int Ind,
			 t_hist *HAvlAvc);
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
  char		NomeArq[20];
  char		Msg[80];
  char		NomeRel[20];
  int		NLinhas;
  FILE		*fp;
  time_t	HoraAtual;
  struct  tm DataTm;
  char sala[3];


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
  
 
  if (argc eq NUM_ARGS)
  {
	if (ConsisteArg(argv, &Arg) eq RET_FUNCAO_OK)
	{
	  sprintf(NomeArq, "/score/relatorio/RelTen_%02d_%02d_%02d", Arg.DiaInicial, Arg.MesInicial, Arg.AnoInicial);
	  fp = fopen (NomeArq, "w");
	  if (fp eq NULL)
	  {
   	    /* ERRO */
	  }  
	  fprintf(fp, " 					RELATORIO DIARIO DE TENSOES - SCORE \n");
	  fprintf(fp, "CubaInicial: %d     CubaFinal: %d   DataInicial: %02d/%02d/%02d    DataFinal: %02d/%02d/%02d \n", 
				Arg.CubaInicial, Arg.CubaFinal, Arg.DiaInicial, Arg.MesInicial, Arg.AnoInicial, Arg.DiaFinal, Arg.MesFinal,
				Arg.AnoFinal);
	  fprintf(fp, "   Data    VPlaca   VAlvo   VLiqui  VTotal \n");

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
	sprintf(NomeArq, "/score/relatorio/RelTen_%02s_%d_%d_%d", sala, Arg.DiaInicial, Arg.MesInicial, Arg.AnoInicial);
	fp = fopen (NomeArq, "w");
	if (fp eq NULL)
	{
   	  
	}  
	fprintf(fp, " 					RELATORIO DIARIO DE TENSOES - SCORE \n");
	fprintf(fp, "CubaInicial: %d     CubaFinal: %d   DataInicial: %02d/%02d/%02d    DataFinal: %02d/%02d/%02d \n", 
		Arg.CubaInicial, Arg.CubaFinal, Arg.DiaInicial, Arg.MesInicial, Arg.AnoInicial, Arg.DiaFinal, Arg.MesFinal,
		Arg.AnoFinal);
	fprintf(fp, "   Data    VPlaca   VAlvo   VLiqui  VTotal \n");
  
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

//  EndWindows ();

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
  time_t  HoraAtual;
  time_t  TimeTAtual;
  time_t  TimeT;
  struct  tm DataTm;
  t_hist  *HAvlAvc;

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

    HAvlAvc = CarBufCubas(&DataTm, Arg);

    if( HAvlAvc eq (void *) NULL ) /* houve erro */
      return(-1);
    /* inicializa cuba inicial para cada dia */
    
	CalcAreaDados(Dad, Arg->CubaInicial, Arg->CubaFinal, NumDias, HAvlAvc);

	fprintf(fp, " %02d/%02d/%02d	%2.2f	%2.2f	%2.2f	%2.2f \n", DataTm.tm_mday, 
				DataTm.tm_mon+1,TM_YEAR_TO_2DIGIT(DataTm.tm_year), (Dad+ContDia)->Placa, (Dad+ContDia)->Alvo,
				(Dad+ContDia)->Liqui, (Dad+ContDia)->Total ); 

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
	  Rod->MAlvo     += (Dad+i)->Alvo;
	  Rod->MLiqui    += (Dad+i)->Liqui;
	  Rod->MTotal    += (Dad+i)->Total;
	}
	
	Rod->MPlaca	   = Rod->MPlaca / NumDias;
	Rod->MAlvo	   = Rod->MAlvo  / NumDias;
	Rod->MLiqui	   = Rod->MLiqui / NumDias;
	Rod->MTotal	   = Rod->MTotal / NumDias;
  }

  free(HAvlAvc);
  return(NumDias);  /* numero de linhas prenchidas */
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
	(Dad+Indice)->Placa    = 0.0;
	(Dad+Indice)->Alvo     = 0.0;
	(Dad+Indice)->Liqui    = 0.0;
    (Dad+Indice)->Total    = 0.0;
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
void CalcAreaDados(t_dados *Dad, int CubaInicial, int CubaFinal, int Ind, t_hist *HAvlAvc)
{
  float Alvo, AuxAlvo;
  float Total, AuxTotal;
  float Liqui, AuxLiqui;
  float Placa;
  int 	CubaAtual, indice, Cuba;

  Alvo = 0.0;
  Liqui = 0.0;
  Total = 0.0;
  indice = 0;
  Placa = 0.0;

  for (Cuba = CubaInicial; Cuba <= CubaFinal; ++Cuba)
  {
    CubaAtual = ConvCubOperScore(Cuba);

    if ((HIST_AVC(CubaAtual).EstPrincDia eq CUBA_NORMAL) or
	    (HIST_AVC(CubaAtual).EstPrincDia eq CUBA_PARTIDA))
    {  	
	  Placa += HIST_AVC(CubaAtual).VSetPointDia;

 #ifdef	BOOSTER_CORRENTE
      AuxAlvo = (HIST_AVC(CubaAtual).RAlvoDia * HIST_AVC(CubaAtual).IAlvoCubaDia + HIST_AVC(CubaAtual).BemfDia);
      AuxAlvo = (float) (Round((double)AuxAlvo*100.0)/100.0);
      Alvo += AuxAlvo;

      AuxLiqui = HIST_AVC(CubaAtual).RDiaLiq * HIST_AVC(CubaAtual).IAlvoCubaDia;

      AuxTotal = HIST_AVC(CubaAtual).RDiaBruta * HIST_AVC(CubaAtual).IAlvoCubaDia;
 #else
      AuxAlvo = (HIST_AVC(CubaAtual).RAlvoDia * HIST_AVL.IAlvoDia + HIST_AVC(CubaAtual).BemfDia);
      AuxAlvo = (float) (Round((double)AuxAlvo*100.0)/100.0);
      Alvo += AuxAlvo;

      AuxLiqui = HIST_AVC(CubaAtual).RDiaLiq * HIST_AVL.IAlvoDia;

      AuxTotal = HIST_AVC(CubaAtual).RDiaBruta * HIST_AVL.IAlvoDia;

 #endif
    /* Fim Alteracao - Carlos - 23/06/99 */

	  AuxLiqui += HIST_AVC(CubaAtual).BemfDia;
	  AuxTotal += HIST_AVC(CubaAtual).BemfDia;

      AuxLiqui = (float) (Round((double)AuxLiqui*100.0)/100.0);
      Liqui += AuxLiqui;

      AuxTotal = (float) (Round((double)AuxTotal*100.0)/100.0);
  	  Total += AuxTotal;

	  indice++;
	}
  } /* For de cubas */

  (Dad+Ind)->Placa = Placa / indice;
  (Dad+Ind)->Alvo  = Alvo  / indice;
  (Dad+Ind)->Liqui = Liqui / indice;
  (Dad+Ind)->Total = Total / indice;
}
