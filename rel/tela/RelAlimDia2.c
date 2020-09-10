/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II E III

	ARQUIVO		: RelAlimDia2.c

	CONTEUDO	: Programa que processa e gera as informacoes que compoem
				  o relatorio diario de alimentacao das cubas point feeder.

	AUTOR		: Ricardo Teixeira Leite Mourao / Robson

	SISTEMA OPERACIONAL:  QNX 4.22A		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 00 - 03/03/97

	OBSERVACAO	: 

	HISTORICO DAS EDICOES

-------------------------------------------------------------------------------
dd/mm/aa | Descricao                                                 | autor
-------------------------------------------------------------------------------
31/07/98 | Y2k - Corrigido tratamento de ano em 2 digitos            | Leonel
-------------------------------------------------------------------------------
         | Adaptacao da data para leitura dos arquivos diarios/turno | 
03/05/99 | ser feita dentro do padrao de nome de arquivo estabeleci- | Carlos
         | do pela tarefa SalvaBd ( #if 1 == 0 ) e eliminada funcao  | 
         | AcertaCabec                                               | 
-------------------------------------------------------------------------------
29/08/17 | TK-ALIM - Preparacão Toolkit Alimentacao                  | Carlos
-------------------------------------------------------------------------------
******************************************************************************/

/* INDICA QUE ESTE E' O PROGRAMA PRINCIPAL */

#define	PROGRAMA_PRINCIPAL
#define	RELATORIO_HISTORICO

/* INCLUSAO DE OUTROS ARQUIVOS */

#include <RelAlimDia2.h>
#include <ScoreMsgs.h>

/* PROTOTIPOS DAS FUNCOES INTERNAS */

void main(int argc , char *argv[]);
int  ConsisteArg(char *argv[], t_args *Arg);
int  GeraDadosRel(t_args *Arg, t_cabec *Cab, t_dados *Dad, t_rodape *Rod);
void IniDados(t_args *Arg, t_cabec *Cab, t_dados *Dad, t_rodape *Rod, t_temp *Temp);
void CalcAreaDados(t_dados *Dad, int Cuba, int Ind, t_hist *HAvlAvc, t_temp *Temp);
int  LeTab(void);
void ConvHoraMin(char* dest, long interv);

#if 1 == 0
 #ifdef REL_TURNO
  void AcertaCabec(t_args *Argm, t_cabec *Cab, time_t HoraAtual);
 #endif
#endif

/*
-------------------------------------------------------------------------------
							Variaveis Globais
-------------------------------------------------------------------------------
*/

t_filtrosPD filtro;

/*
-------------------------------------------------------------------------------
							Main
-------------------------------------------------------------------------------
*/

void main(int argc, char *argv[])
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
#ifdef	REL_TURNO
  char	 StTur[9];
  int    Turno;
#endif

  //sleep(20);

  /*-- Atualiza tabelas de dados --*/
  if (LeTab() ne 0)
	return(RET_FUNCAO_ERR);

  strcpy(DataI, argv[2]);
  strcpy(DataF, argv[3]);

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
	strcpy(StTur, argv[4]);
	Turno = (strcmp(strupr(StTur),strupr(ScoreGetStr(STR_ATUAL))) eq 0)?AVL.TurnoAtual: atoi(StTur) - 1;
	if (Turno >= AVL.NumTurnos)
	{
	  ExibeErro("Numero do turno invalido");
	  return(RET_FUNCAO_ERR);
	}
	Arg->Turno = Turno;
	/*-- Consiste exclusao de data --*/
	Arg->TabDatas[0] = -1;
	if (*argv[5] ne NUL)
	{
	  /*-- Sinaliza  exclusao de data --*/
	  Arg->TabDatas[0] = 0;
	  /*-- Valida a linha de exclusao de datas. --*/
	  if (ValidaExcDatas(Arg, argv[5]) ne VERDADEIRO)
	  {
		ExibeErro("Data invalida na linha de exclusao");
		return(RET_FUNCAO_ERR);
	  }
	}
#else
	/*-- Consiste exclusao de data --*/
	Arg->TabDatas[0] = -1;
	if (*argv[4] ne NUL)
	{
	  /*-- Sinaliza  exclusao de data --*/
	  Arg->TabDatas[0] = 0;
	  /*-- Valida a linha de exclusao de datas. --*/
	  if (ValidaExcDatas(Arg, argv[4]) ne VERDADEIRO)
	  {
		ExibeErro("Data invalida na linha de exclusao");
		return(RET_FUNCAO_ERR);
	  }
	}
#endif
  }
  else
	return(RET_FUNCAO_ERR);
  
  /*-- Le arquivo de filtro de cubas --*/
  if (LeFiltroCubas(argv[1], &filtro))
  {
	ExibeErro("Falha abertura arquivo de filtros");
	return(RET_FUNCAO_ERR);
  }
  if (filtro.Par.Total eq 0)
  {
	ExibeErro("Nao ha cubas selecionadas");
	return(RET_FUNCAO_ERR);
  }

  return(RET_FUNCAO_OK);
}

/*
------------------------------------------------------------------------------
  GeraDadosRel - Calcula as variaveis e medias a serem exibidas no relatorio,
		montando os campos variaveis do cabecalho, area de dados e rodape
------------------------------------------------------------------------------
*/
int GeraDadosRel(t_args *Arg, t_cabec *Cab, t_dados *Dad, t_rodape *Rod)
{
  struct	tm DataTm;
  t_hist	*HAvlAvc;
  t_temp	Temp[MAX_CUBAS];
  t_temp    TempRod;
  int       IndiceCuba[MAX_CUBAS];
  int		Indice;
  int		Cuba;
  int		CubaAtual;
  int		ContDia;
  int		ContMed;
  int		NumDias;
  int		ContMedPrev;
  float		PercSistema;
  float		PercLinha;
  float		Percent;
  time_t    HoraAtual;
  time_t	TimeT;
  time_t	TimeTAtual;
  int		IndCuba;


  /* pega hora atual */
  HoraAtual = time(NULL);

  /*-- Calcula hora atual para referencia --*/
  memcpy(&DataTm, localtime(&HoraAtual), sizeof(struct tm));
  DataTm.tm_sec  = 0;
  DataTm.tm_min  = 0;
  DataTm.tm_hour = 12;
  TimeTAtual = mktime(&DataTm);

  /*-- Inicializa estruturas do relatorio --*/
  IniDados(Arg, Cab, Dad, Rod, &Temp);

  /*-- Inicializa variaveis temporarias --*/
  // Inicializa area de dados para todas as cubas 
  for( Indice = 0; Indice < MAX_CUBAS; ++Indice )
  {
	Temp[Indice].DurQueb1=0L;
	Temp[Indice].DurQueb2=0L;
	Temp[Indice].DurQueb3=0L;
	Temp[Indice].DurQueb4=0L;
	Temp[Indice].DurAlim1=0L;
	Temp[Indice].DurAlim2=0L;
	Temp[Indice].DurAlim3=0L;
	Temp[Indice].DurAlim4=0L;
  }
  // Inicializa variaveis temporarios do Rodape 
  TempRod.DurQueb1=0L;
  TempRod.DurQueb2=0L;
  TempRod.DurQueb3=0L;
  TempRod.DurQueb4=0L;
  TempRod.DurAlim1=0L;
  TempRod.DurAlim2=0L;
  TempRod.DurAlim3=0L;
  TempRod.DurAlim4=0L;

  /*-- inicializa data auxiliar --*/ 
  /* inicializa data auxiliar */ 
  DataTm.tm_sec  = 0;
  DataTm.tm_min  = 0;
  DataTm.tm_hour = 12;
  DataTm.tm_mday = Arg->DiaInicial;
  DataTm.tm_mon  = Arg->MesInicial - 1;
  /* -- Y2k inicio: ano de 2 digitos -- */
  DataTm.tm_year = TWO_DIGIT_TO_TM_YEAR(Arg->AnoInicial);
  /* -- Y2k fim -- */

  TimeT = mktime(&DataTm);

  /*-- executa para todos os dias --*/
  PercSistema = 0.0;
  PercLinha   = 0.0;
  NumDias = 0;
  
  /* -- Loop por dias do relatorio: Somatorio por Dia (para cada cuba) -- */
  for(ContDia = 0; ContDia < Arg->DiasDatas; ++ContDia)
  {
	if (ValidaData(Arg, TimeT) ne VERDADEIRO)
	{
	  TimeT += (time_t)( NUM_SEGUNDOS_DIA * TIMES_PER_SEC ); /* avanca um dia */
	  memcpy(&DataTm, localtime(&TimeT), sizeof(struct tm));  /* converte para struct tm */
	  continue; /* proxima ContDia */
	}

	++NumDias; /* incrementa numero de dias para calculo das medias */

#ifdef	REL_TURNO

  #if 1 == 0

	/*====================================================================*/
	/* Trecho colocado em comentario por Carlos em 03/05/99 para compati- */
	/* bilizar a leitura dos arquivos de turno com o padrao gravado  pela */
	/* tarefa SalvaBd.                                                    */
	/*====================================================================*/

    /*-------------------------- I N I C I O -----------------------------*/
	/*-- Avanca 1 dia quando for dia anterior ao atual com turno co_ --*/
	/*-- mecado no dia anterior para pegar informacoes da area comum --*/
	if (TurnoDiaAnterior(Arg, HoraAtual, Arg->DiaAnoAtual))
	{
	  if (TimeTAtual eq (TimeT + (NUM_SEGUNDOS_DIA * TIMES_PER_SEC)))
	  {
		TimeT += (time_t)( NUM_SEGUNDOS_DIA * TIMES_PER_SEC );
		memcpy(&DataTm, localtime(&TimeT), sizeof(struct tm));
		++ContDia;	
	  }
	}
    /*----------------------------  F I M  -------------------------------*/
  #endif

    HAvlAvc = CarBufTurno(&DataTm, Arg);
#else
    HAvlAvc = CarBufCubas(&DataTm, Arg);
#endif

    if(HAvlAvc eq (void *)NULL) /*-- houve erro --*/
      return(-1);
    /*-- inicializa cuba inicial para cada dia --*/
    Cab->IAlvo += (HIST_AVL.IAlvoDia / 1000.0);
    Cab->IReal += (HIST_AVL.IMedDia / 1000.0);


    /*-- Acumula o percentual que o sistema e linha ficaram ativos no dia --*/
    /*-- para calculo do percentual medio dos dias solicitados.           --*/
#ifdef	REL_TURNO
	Percent = CalcPercTur(Arg, HIST_AVL.NCicAtivoDia, 1, HoraAtual,
						  DataTm.tm_yday);
    PercSistema += Percent;
	Percent = CalcPercTur(Arg, HIST_AVL.NCicContDia, 1, HoraAtual,
						  DataTm.tm_yday);
    PercLinha += Percent;


  #if 1 == 0

	/*====================================================================*/
	/* Trecho colocado em comentario por Carlos em 03/05/99 para eliminar */
	/* adaptacao da data inicial e final do cabecalho (desnecessario).    */
	/*====================================================================*/

	if (TurnoDiaAnterior(Arg, HoraAtual, DataTm.tm_yday))
	  AcertaCabec(Arg, Cab, HoraAtual);

  #endif

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
	/*-- Montagem da area de dados do relatorio --*/
	IndCuba = 0;
	do
	{
	  CubaAtual=filtro.Par.IndCuba[IndCuba];
	  Cuba     =filtro.Par.NumCuba[IndCuba];
	  if (AVC.Param[CubaAtual].TemPF eq TEM_PF)
	  {
	    (Dad+Indice)->NumCuba = Cuba;
		IndiceCuba[Indice]= CubaAtual; //armazena indice da cuba associada aa linha do relatorio
	    CalcAreaDados(Dad, CubaAtual, Indice, HAvlAvc, &Temp);
	    ++Indice; /* incrementa numero de linhas */
	  }	
	    ++IndCuba;
	} while (IndCuba < filtro.Par.Total);
    TimeT += (time_t)(NUM_SEGUNDOS_DIA * TIMES_PER_SEC); /* avanca um dia */
	memcpy(&DataTm, localtime(&TimeT), sizeof(struct tm));  /* converte para struct tm */
  }

  /*-- Sai da funcao quando nao houver informacoes a exibir --*/
  if (Indice eq 0 || NumDias eq 0)
	return(0);

  /* calcula media para ialvo, ireal e percativ */
  Cab->IAlvo = Cab->IAlvo / NumDias;
  Cab->IReal = Cab->IReal / NumDias;
  Cab->PercSistema = PercSistema / NumDias;
  Cab->PercLinha = PercLinha / NumDias;
  if (Cab->PercSistema > 100.0)
	Cab->PercSistema = 100.0;
  if (Cab->PercLinha > 100.0)
	Cab->PercLinha = 100.0;

  ContMed   = 0;
  ContMedPrev = 0;

  /* -- Loop por cuba do relatorio: Medias diarias e Somatorio do Rodape -- */
  /*-- gera tempos hh:mm e acumula valores para media dos dias --*/
  for (Cuba = 0; Cuba < Indice; ++Cuba)
  {
    /*-- calcula media diaria das variaveis de medicao de tempo --*/
	/* Passo 1: calcula a media diaria */
    Temp[IndiceCuba[Cuba]].DurQueb1 /= NumDias;
    Temp[IndiceCuba[Cuba]].DurQueb2 /= NumDias;
    Temp[IndiceCuba[Cuba]].DurQueb3 /= NumDias;
    Temp[IndiceCuba[Cuba]].DurQueb4 /= NumDias;
    Temp[IndiceCuba[Cuba]].DurAlim1 /= NumDias;
    Temp[IndiceCuba[Cuba]].DurAlim2 /= NumDias;
    Temp[IndiceCuba[Cuba]].DurAlim3 /= NumDias;
    Temp[IndiceCuba[Cuba]].DurAlim4 /= NumDias;
	
	/* Passo 2: Armazena valores no formato hh:mm na area de dados do relatorio */
	ConvHoraMin(&((Dad+Cuba)->DurQueb1),Temp[IndiceCuba[Cuba]].DurQueb1);
	ConvHoraMin(&((Dad+Cuba)->DurQueb2),Temp[IndiceCuba[Cuba]].DurQueb2);
	ConvHoraMin(&((Dad+Cuba)->DurQueb3),Temp[IndiceCuba[Cuba]].DurQueb3);
	ConvHoraMin(&((Dad+Cuba)->DurQueb4),Temp[IndiceCuba[Cuba]].DurQueb4);
	ConvHoraMin(&((Dad+Cuba)->DurAlim1),Temp[IndiceCuba[Cuba]].DurAlim1);
	ConvHoraMin(&((Dad+Cuba)->DurAlim2),Temp[IndiceCuba[Cuba]].DurAlim2);
	ConvHoraMin(&((Dad+Cuba)->DurAlim3),Temp[IndiceCuba[Cuba]].DurAlim3);
	ConvHoraMin(&((Dad+Cuba)->DurAlim4),Temp[IndiceCuba[Cuba]].DurAlim4);
	
    //Incrementa variaveis relacionadas a tempo 
	TempRod.DurQueb1 += Temp[IndiceCuba[Cuba]].DurQueb1;
    TempRod.DurQueb2 += Temp[IndiceCuba[Cuba]].DurQueb2;
	TempRod.DurQueb3 += Temp[IndiceCuba[Cuba]].DurQueb3;
	TempRod.DurQueb4 += Temp[IndiceCuba[Cuba]].DurQueb4;
	TempRod.DurAlim1 += Temp[IndiceCuba[Cuba]].DurAlim1;
	TempRod.DurAlim2 += Temp[IndiceCuba[Cuba]].DurAlim2;
	TempRod.DurAlim3 += Temp[IndiceCuba[Cuba]].DurAlim3;
	TempRod.DurAlim4 += Temp[IndiceCuba[Cuba]].DurAlim4;
  }

  //Calcula media (por cuba) das variaveis de medicao de tempo 
  TempRod.DurQueb1	  /= Indice;
  TempRod.DurQueb2	  /= Indice; 
  TempRod.DurQueb3	  /= Indice; 
  TempRod.DurQueb4	  /= Indice; 
  TempRod.DurAlim1	  /= Indice; 
  TempRod.DurAlim2	  /= Indice; 
  TempRod.DurAlim3	  /= Indice; 
  TempRod.DurAlim4	  /= Indice; 

  /*-- Converte variaveis de medicao de tempo do rodape para formato hh:mm --*/
  ConvHoraMin(&(Rod->DurQueb1),TempRod.DurQueb1);
  ConvHoraMin(&(Rod->DurQueb2),TempRod.DurQueb2);
  ConvHoraMin(&(Rod->DurQueb3),TempRod.DurQueb3);
  ConvHoraMin(&(Rod->DurQueb4),TempRod.DurQueb4);
  ConvHoraMin(&(Rod->DurAlim1),TempRod.DurAlim1);
  ConvHoraMin(&(Rod->DurAlim2),TempRod.DurAlim2);
  ConvHoraMin(&(Rod->DurAlim3),TempRod.DurAlim3);
  ConvHoraMin(&(Rod->DurAlim4),TempRod.DurAlim4);
  
  free (HAvlAvc);
  return(Indice);
}

/*
------------------------------------------------------------------------------
  IniDados - Inicializa cabecalho e area de dados do relatorio
------------------------------------------------------------------------------
*/
void IniDados(t_args *Arg, t_cabec *Cab, t_dados *Dad, t_rodape *Rod,
			  t_temp *Temp)
{
  MontaAlgSel(Cab->Selecao, Cab->Algorit, &filtro);

  /* inicializa Cab */
  Cab->DiaInicial  = Arg->DiaInicial;
  Cab->MesInicial  = Arg->MesInicial;
  Cab->AnoInicial  = Arg->AnoInicial;
  Cab->DiaFinal    = Arg->DiaFinal;
  Cab->MesFinal    = Arg->MesFinal;
  Cab->AnoFinal    = Arg->AnoFinal;
#ifdef	REL_TURNO
  memset(Cab->Turno, 0x00, MAX_ID_TURNO);
  strncpy(Cab->Turno,AVL.IdentTurno[Arg->Turno],MAX_ID_TURNO);
#endif
  Cab->IAlvo       = 0.0;
  Cab->IReal       = 0.0;
  Cab->PercSistema = 0.0;
  Cab->PercLinha   = 0.0;
}

/*
------------------------------------------------------------------------------
  CalcAreaDados - Calcula area de dados do relatorio
------------------------------------------------------------------------------
*/
void CalcAreaDados(t_dados *Dad, int Cuba, int Ind, t_hist *HAvlAvc,
				t_temp *Temp)
{
  long aux;
  
  /* Variavel utilizada para converter Ticks do MCP em segundos */
  aux= (long) (SAD_TICKS / Comum->BaseTempoMcp);

  /* Incrementa variaveis relacionadas com tempo */
  Temp[Cuba].DurQueb1+= (HIST_AVC(Cuba).Sup.TQuebInib[0]/aux);
  Temp[Cuba].DurQueb2+= (HIST_AVC(Cuba).Sup.TQuebInib[1]/aux);
  Temp[Cuba].DurQueb3+= (HIST_AVC(Cuba).Sup.TQuebInib[2]/aux);
  Temp[Cuba].DurQueb4+= (HIST_AVC(Cuba).Sup.TQuebInib[3]/aux);
  Temp[Cuba].DurAlim1+= (HIST_AVC(Cuba).Sup.TAlimInib[0]/aux);
  Temp[Cuba].DurAlim2+= (HIST_AVC(Cuba).Sup.TAlimInib[1]/aux);
  Temp[Cuba].DurAlim3+= (HIST_AVC(Cuba).Sup.TAlimInib[2]/aux);
  Temp[Cuba].DurAlim4+= (HIST_AVC(Cuba).Sup.TAlimInib[3]/aux);
}


#if 1 == 0

/*
------------------------------------------------------------------------------
  AcertaCabec - Acerta as datas do cabecalho para turno incompleto comecado
				no dia anterior.
------------------------------------------------------------------------------
*/
  #ifdef REL_TURNO
  void AcertaCabec(t_args *Argm, t_cabec *Cab, time_t HoraAtual)
  {
  time_t	Hora;
  struct tm	Data;

  Hora = ((HoraAtual / TIMES_PER_SEC) - NUM_SEGUNDOS_DIA) * TIMES_PER_SEC;
  memcpy(&Data, localtime(&Hora), sizeof(struct tm));
  /*-- Verifica se a data inicial e final sao iguais --*/
  if ((Argm->DiaInicial eq Argm->DiaFinal) and
	  (Argm->MesInicial eq Argm->MesFinal) and
	  (Argm->AnoInicial eq Argm->AnoFinal))
  {
	Cab->DiaInicial = Data.tm_mday;
	Cab->MesInicial = Data.tm_mon + 1;
  /* -- Y2k inicio: ano de 2 digitos -- */
	Cab->AnoInicial = TM_YEAR_TO_2DIGIT(Data.tm_year);
  /* -- Y2k fim -- */
  }
  Cab->DiaFinal = Data.tm_mday;
  Cab->MesFinal = Data.tm_mon + 1;
  /* -- Y2k inicio: ano de 2 digitos -- */
  Cab->AnoFinal = TM_YEAR_TO_2DIGIT(Data.tm_year);
  /* -- Y2k fim -- */
  }
  #endif
#endif

/*
----------------------------------------------------------------------------
| LeTab - Quando nao estiver rodando no micro de controle, le do micro que |
|         estiver no controle todas as tabelas da base de dados que forem  |
|         consultadas por ESTE relatorio. So devem ser lidas as tabelas que|
|         sofram alteracoes ON-LINE (AVC.Abs nao e' necessario).           |
|         Retorna 0 se ok, e diferente de 0 -> codigo de erro              |
----------------------------------------------------------------------------
*/
int LeTab(void)
{
  int nodo_controle, status;
  char msg_erro[80];

  nodo_controle=AVL.NodoNoControle;
  if (My_nid ne nodo_controle)
  { /* -- Estou rodando em outro nodo, entao leio tabelas do controle -- */
	/* -- Le tabela AVC.Param -- */
	if (status=ScoreBd(nodo_controle,TABELA_AVC,BD_LER,(void *)&AVC.Param,
						CalcByteOffset(&AVC,&AVC.Param),
						sizeof(AVC.Param)))
	{
	  sprintf(msg_erro,"Falha no ScoreBd (AVC.Param) [%d]!",status);
	  ExibeErro(msg_erro);
	  return(status);
	}
  }
  
  return(0);	
}

/*
-------------------------------------------------------
| ConvHoraMin - Converte um long para o formato hh:mm |
-------------------------------------------------------
*/
void ConvHoraMin(char* dest, long interv)
{
  int hh,mm;
  
  hh= (int)(interv/3600L);
  mm= (int)((interv/60L) Mod 60L);  
  sprintf(dest,"%03d:%02d",hh,mm);
}

