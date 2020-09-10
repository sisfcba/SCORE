/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DAS SALAS 125 KA I E VII

	ARQUIVO		: RelExemploCC.c

	CONTEUDO	: Programa que processa e gera as informacoes que compoem
				  exemplo de relatorio de ciclo de control

	AUTOR		: Carlos Cezar Silva Lage.

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 01 - 19/09/2012

	HISTORICO DAS EDICOES

-------------------------------------------------------------------------------
dd/mm/aa   | Descricao                                               | autor
-------------------------------------------------------------------------------
19/09/2012 | Edicao inicial                                          | Leonel
-------------------------------------------------------------------------------

$Id: RelExemploCC.c,v 1.1.2.1 2012/09/28 17:10:11 leo Exp $

$Log: RelExemploCC.c,v $
Revision 1.1.2.1  2012/09/28 17:10:11  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.


******************************************************************************/

			/*-- INDICA QUE ESTE E' O PROGRAMA PRINCIPAL --*/

#define	PROGRAMA_PRINCIPAL

					/*-- INCLUSAO DE OUTROS ARQUIVOS --*/

#include <RelExemploCC.h>
#include <TiposOpeW.h>

	/*-- PROTOTIPACAO DAS FUNCOES INTERNAS --*/

void main(int argc, char *argv[]);

#ifdef OPERACAO_WINDOWS
  int GeraDadosRelatorio(char *argv[], t_cabec *Cabecalho,
						 t_dados *AreaDados, t_rodape *Rodape);
  void MontaCabAlgSelecao(t_cabec *Cabecalho,t_filtrosPD *filtro);
#else
  int GeraDadosRelatorio(t_args *Arg, t_cabec *Cabecalho,
						 t_dados *AreaDados, t_rodape *Rodape);
  int ConsisteArg(char *argv[], t_args *Arg);
#endif 

void CalcAreaDados(t_dados *AreaDados,int Cuba,int Indice,long HoraAtual,
				   t_acum *Acum);
void IniAreaDados(t_dados *AreaDados, int Indice);

void CalcTensoes ( t_dados *AreaDados, int Cuba, int Indice );
void CalcHoraPrevEa ( t_dados *AreaDados, int Cuba, int Indice );

void CalcTempoEa ( t_dados *AreaDados, int Cuba, int Indice, long HoraAtual );
void CalcTempoManual ( t_dados *AreaDados, int Cuba, int Indice, long HoraAtual );
void CalcAtrasoEa ( t_dados *AreaDados, int Cuba, int Indice, long HoraAtual );
void PegaPassoTInc(t_dados *AreaDados, int Cuba, int Indice);
void SinalSituacao ( t_dados *AreaDados, int Cuba, int Indice );
void CalcMedias ( t_rodape *Rodape, t_acum *Acum );
int	 LeTabelas(void);
unsigned tirabits( unsigned pal, byte biti, byte bitf );

/*
-------------------------------------------------------------------------------
  main - Funcao principal
-------------------------------------------------------------------------------
*/

void main ( int argc , char *argv[] )
{
  /* Corpo do relatorio. E' o mesmo para todos os relatorios de ciclo controle
     do padrao do Score */
  #include	"MainRelatCC.c"

} /*--- main ---*/


#ifndef	OPERACAO_WINDOWS

/*
--------------------------------------------------------------------------------
| ConsisteArg - Faz  a  consistencia  dos   Arg  recebidos  pelo |
|                sistema, no  caso  desse  relatorio, faz  a  consistencia  de |
|                Cuba Inicial e Cuba Final.                                    |
--------------------------------------------------------------------------------
*/
int ConsisteArgumentos(char *argv[], t_args *Arg)
{
  int	CubaInicial;
  int	CubaFinal;
  int	Retorno;
  
  /*-- Converte o numero da Cuba Inicial para o tipo inteiro --*/
  CubaInicial = atoi(argv[1]);
  /*-- Converte o numero da Cuba Final para o tipo inteiro   --*/
  CubaFinal = atoi (argv[2]);

  /*-- Verifica se o valor de CubaInicial e CubaFinal estao corretos --*/
  if (( Retorno = ConsisteCubas ( CubaInicial, CubaFinal )) eq VERDADEIRO )    
  {
	/*-- Coloca os valores na estrutura se eles estao corretos --*/
	Arg->CubaInicial = CubaInicial;
	Arg->CubaFinal = CubaFinal;
	/*-- Verifica existencia de cuba excluida --*/
	Arg->TabCubas[0] = -1;
	if (*argv[3] ne NUL)
	{
	  /*-- Sinaliza cuba excluida --*/
	  Arg->TabCubas[0] = 0;
	  /*-- Valida a linha de exclusao de cubas. --*/
	  if ( ValExcCubas(argv[3], Arg->TabCubas) ne VERDADEIRO )
	  {
		ExibeErro(ScoreGetStr(SCORE_MSG_584));
		Retorno = RET_FUNCAO_ERR;
	  }
	}
  }
  return ( Retorno );
}
#endif

/*
--------------------------------------------------------------------------------
| GeraDadosRelatorio - Calcula  as  variaveis e medias  a  serem  exibidas  no |
|                relatorio,montando os campos variaveis do cabecalho, area  de |
|                dados e rodape do relatorio.                                  |
--------------------------------------------------------------------------------
*/
#ifdef OPERACAO_WINDOWS
  int GeraDadosRelatorio( char *argv[], t_cabec *Cabecalho,
						t_dados *AreaDados, t_rodape *Rodape )
#else
  int GeraDadosRelatorio( t_args *Arg, t_cabec *Cabecalho,
						t_dados *AreaDados, t_rodape *Rodape)
#endif 
{
  int		Cuba;
  int		CubaAtual;
  long		HoraAtual;
  int		Indice;
  t_acum	Acum;

#ifdef	OPERACAO_WINDOWS
  char		Msg[80];
  int		IndCuba;
  t_filtrosPD filtro;

  /* Le arquivo de filtro de cubas */
  if (LeFiltroCubas(argv[1],&filtro))
  {
    sprintf(Msg, ScoreGetStr(SCORE_ERR_2),My_name,COD_ERRO_6, argv[1]);
	ExibeErro(Msg);
	exit(0);
  }

  if( filtro.Par.Total eq 0 )
  {
	ExibeErro(ScoreGetStr(SCORE_MSG_43));
	exit(0);
  }
#endif
  
  /*-- Inicializacao dos acumuladores para calculo de media --*/
  Acum.NCubasAcum = 0;
  Acum.IncAcum   = 0.0;
  Acum.PlacaAcum = 0.0;
  Acum.AlvoAcum  = 0.0;
  Acum.AtualAcum = 0.0;
  Acum.ErroAcum   = 0.0;

  /*-- Calculo da hora atual --*/
  HoraAtual = time(NULL)/TIMES_PER_SEC; 

#ifndef	OPERACAO_WINDOWS
  /*-- Montagem do cabecalho do relatorio --*/
  Cabecalho->CubaInicial = Arg->CubaInicial;
  Cabecalho->CubaFinal   = Arg->CubaFinal;
#else
  MontaAlgSel(Cabecalho->Selecao, Cabecalho->Algorit, &filtro);
#endif

  /* -- Calculo do Cabecalho -- */
  Cabecalho->NCicAtivoDia = AVL.NCicAtivoDia;
  Cabecalho->IAlvo = (AVL.IAlvo/1000.0);
  Cabecalho->ICicContlMed = (AVL.ICicContlMed/1000.0);

  /* Inicio do loop de cubas */
#ifndef OPERACAO_WINDOWS

  /*-- Montagem da area de dados do relatorio --*/
  Indice = 0;
  for ( Cuba = Arg->CubaInicial; Cuba <= Arg->CubaFinal; ++Cuba)
  {
	CubaAtual = ConvCubOperScore(Cuba);
	if ((CubaAtual ne -1) and (ValidaCuba(Arg->TabCubas, CubaAtual)
		   eq VERDADEIRO))
	{
	  /*-- Calculo dos dados para cada cuba --*/
	  CalcAreaDados(AreaDados,CubaAtual,Indice,HoraAtual,&Acum);
	  Indice++;

	}
  }
#else
  /*-- Montagem da area de dados do relatorio --*/
  Indice = 0;
  IndCuba = 0;
  do
  {
	CubaAtual=filtro.Par.IndCuba[IndCuba];
	Cuba     =filtro.Par.NumCuba[IndCuba];
	/*-- Calculo dos dados para cada cuba --*/
	CalcAreaDados(AreaDados,CubaAtual,Indice,HoraAtual,&Acum);
	Indice++;
    ++IndCuba;

  } while (IndCuba < filtro.Par.Total);
#endif

  /*-- Montagem do rodape do relatorio --*/
  /*-- Calculo das medias de tensoes --*/
  CalcMedias ( Rodape, &Acum );

  /*-- Retorna o numero de linhas do relatorio --*/
  return(Indice);

} /*-- GeraDadosRelatorio --*/

/*
--------------------------------------------------------------------------------
| CalcAreaDados - Calculo dos dados por cuba                                   |
--------------------------------------------------------------------------------
*/
void CalcAreaDados(t_dados *AreaDados,int Cuba,int Indice,long HoraAtual,
				   t_acum *Acum)
{
  IniAreaDados(AreaDados, Indice);

  /*-- Numero da cuba --*/
  (AreaDados+Indice)->NumCuba = ConvCubScoreOper(Cuba);

  /*-- Sinalizacao da cuba quando estiver Fora de Leitura, --*/
  /*-- ou seu estado for Desligado, Ligado ou Partido.     --*/
  if ((EST_AVC(Cuba).ForaLeitura eq VERDADEIRO) or
	  (EST_AVC(Cuba).EstadoCuba ne CUBA_NORMAL))
	sprintf((AreaDados+Indice)->SinEst, "%1s", "+");

  /*-- Calculo das tensoes da cuba --*/
  CalcTensoes(AreaDados, Cuba, Indice);

  /*-- Calculo da hora prevista para ocorrencia de efeito anodico --*/
  CalcHoraPrevEa (AreaDados, Cuba, Indice);

   /*-- Calculo do tempo desde o último EA --*/
   CalcTempoEa (AreaDados, Cuba, Indice, HoraAtual);

   /*-- Calculo da duracao da cuba em Manual-Local ou Manual-Remoto --*/
   CalcTempoManual (AreaDados, Cuba, Indice, HoraAtual);

   /*-- Coloca RSuaveDerivH na area de dados --*/
   (AreaDados+Indice)->RSuaveDerivH = AVC.Ea[Cuba].RSuaveDerivH*1e6;

   /*-- Calculo do tempo de atraso de efeito anodico --*/
   CalcAtrasoEa (AreaDados, Cuba, Indice, HoraAtual);

   /*-- Pega o passo da tabela de incrementos e sinaliza-a --*/
   PegaPassoTInc(AreaDados, Cuba, Indice);

   /*-- Sinalizacao de Manual-Local, Manual-Remoto, Efeito Anodico, --*/
   /*-- Quebrada ou Corrida.                                        --*/
   SinalSituacao (AreaDados, Cuba, Indice);

   /*-- Acumulo de valores para o calculo das medias --*/
   if (( EST_AVC(Cuba).ForaLeitura eq FALSO ) and 
	   ( EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL ))
   {
	 Acum->IncAcum   = Acum->IncAcum + (AreaDados+Indice)->Inc;
	 Acum->PlacaAcum = Acum->PlacaAcum + (AreaDados+Indice)->Placa;
	 Acum->AlvoAcum  = Acum->AlvoAcum + (AreaDados+Indice)->Alvo;
	 Acum->AtualAcum = Acum->AtualAcum + (AreaDados+Indice)->Atual;
	 Acum->ErroAcum  = Acum->ErroAcum + (AreaDados+Indice)->Erro;
	 ++Acum->NCubasAcum;
   }
}


/*
--------------------------------------------------------------------------------
| IniAreaDados - Inicializa registro da area de dados da cuba                |
--------------------------------------------------------------------------------
*/
void IniAreaDados(t_dados *AreaDados, int Indice)
{
  sprintf((AreaDados+Indice)->SinEst, "%1s", " ");
  (AreaDados+Indice)->Inc   = 0.0;
  (AreaDados+Indice)->Placa = 0.0;
  (AreaDados+Indice)->Alvo  = 0.0;
  (AreaDados+Indice)->Atual = 0.0;
  (AreaDados+Indice)->Erro  = 0.0;
  memset((AreaDados+Indice)->TempUltEa, 0x00, sizeof((AreaDados+Indice)->TempUltEa));
  memset((AreaDados+Indice)->TempoManual, 0x00, sizeof((AreaDados+Indice)->TempoManual));
  memset((AreaDados+Indice)->TempoAtraEa, 0x00, sizeof((AreaDados+Indice)->TempoAtraEa));
  memset((AreaDados+Indice)->HoraPrevEa, 0x00, sizeof((AreaDados+Indice)->HoraPrevEa));
  (AreaDados+Indice)->RSuaveDerivH = 0.0;
  memset((AreaDados+Indice)->PassoTInc, 0x00, sizeof((AreaDados+Indice)->PassoTInc));
  memset((AreaDados+Indice)->Estado, 0x00, sizeof((AreaDados+Indice)->Estado));

} /*-- IniAreaDados --*/

/*
--------------------------------------------------------------------------------
| CalcTensoes - Calcula as tensoes  de  Incremento, Placa, Alvo, Atual e Erro, |
|               montando essas variaveis na area de dados do relatorio.        |
--------------------------------------------------------------------------------
*/
void CalcTensoes ( t_dados *AreaDados, int Cuba, int Indice )
{
  if ((AreaDados+Indice)->SinEst[0] ne '+')
  {
	/*-- Leitura da tensao de placa da cuba --*/
	(AreaDados+Indice)->Placa = AVC.Ccont[Cuba].VSetPoint;

	if (AVL.LinhaHabilitada eq VERDADEIRO)
	{
	  /* Inicio Alteracao - Carlos - 23/06/99 */
	  /* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
	  /*-- Calculo e conversao da tensao de incremento da cuba para mV --*/
	  (AreaDados+Indice)->Inc = (AVC.Ccont[Cuba].Rinc * AVC.Ccont[Cuba].INominalCuba) * 1000;
#else
	  /*-- Calculo e conversao da tensao de incremento da cuba para mV --*/
	  (AreaDados+Indice)->Inc = (AVC.Ccont[Cuba].Rinc * AVL.INominal) * 1000;
#endif
	  /* Fim Alteracao - Carlos - 23/06/99 */
	
	  /*-- Leitura da tensao alvo da cuba --*/
	  (AreaDados+Indice)->Alvo = AVC.Ccont[Cuba].VAlvo;

	  /*-- Calculo da tensao de erro da cuba --*/
	  (AreaDados+Indice)->Erro = AVC.Ccont[Cuba].VErro;
	}
  }

  if (AVL.LinhaHabilitada eq VERDADEIRO)
  {
	/* Inicio Alteracao - Carlos - 23/06/99 */
	/* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
 	/*-- Leitura da tensao atual da cuba --*/
	(AreaDados+Indice)->Atual = AVC.CcontMcp[Cuba].RCicContlLiq *
											 AVC.Ccont[Cuba].INominalCuba;
#else
 	/*-- Leitura da tensao atual da cuba --*/
	(AreaDados+Indice)->Atual = AVC.CcontMcp[Cuba].RCicContlLiq * AVL.INominal;
#endif
	/* Fim Alteracao - Carlos - 23/06/99 */

	if (((EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL) or
		(EST_AVC(Cuba).EstadoCuba eq CUBA_PARTIDA)) and
		(AVC.CcontMcp[Cuba].RCicContlLiq ne 0.0))
	  (AreaDados+Indice)->Atual += AVC.Param[Cuba].Bemf;
  }
} /*-- CalcTensoes --*/

/*
--------------------------------------------------------------------------------
| CalcTempoEa - Calcula o tempo desde o último EA                              |
--------------------------------------------------------------------------------
*/
void CalcTempoEa (t_dados *AreaDados, int Cuba, int Indice, long HoraAtual)
{
  /*-- Calculo da duracao do desvio de tensao da cuba --*/
  memset((AreaDados+Indice)->TempUltEa,' ',6);
  if ((AreaDados+Indice)->SinEst[0] ne '+')
	MontaHoraMin(AVC.Cleit[Cuba].TUltEa/60, (AreaDados+Indice)->TempUltEa, "%03d:%02d");
  else
	strcpy((AreaDados+Indice)->TempUltEa,TEMPO_NUL3);
} /*-- CalcTempoEa --*/

/*
--------------------------------------------------------------------------------
| CalcTempoManual - Calcula o tempo  que  a  cuba  esta  em  Manual-Local  ou  |
|               Manual-Remoto, montando-o na area de dados do relatorio.       |
--------------------------------------------------------------------------------
*/
void CalcTempoManual (t_dados *AreaDados, int Cuba, int Indice, long HoraAtual)
{
  long	TempoManual;

  memset((AreaDados+Indice)->TempoManual,' ',5);
  /*-- Verifica se a cuba esta em Manual-Local ou Manual-Remoto --*/
  if ( ( EST_AVC(Cuba).ChaveLocRem eq LOCAL ) or
	   ( EST_AVC(Cuba).ChaveAutMan eq MANUAL ) ) 
  {
	TempoManual = HoraAtual - AVC.Cleit[Cuba].HoraUltSelMan;  
	MontaHoraMin(TempoManual/60,(AreaDados+Indice)->TempoManual,"%02d:%02d");
  } 
  else 
	strcpy((AreaDados+Indice)->TempoManual,TEMPO_NUL);
} /*-- CalcTempoManual --*/

/*
--------------------------------------------------------------------------------
| SinalSituacao - Sinaliza  as situacoes  Manual-Local, Manual-Remoto,  Efeito |
|                 Anodico, Corrida ou Quebrada.                                |
--------------------------------------------------------------------------------
*/
void SinalSituacao ( t_dados *AreaDados, int Cuba, int Indice )
{

  /*-- Sinaliza cuba em Manual-Local. --*/
  memset((AreaDados+Indice)->Estado,' ',8);
  strcpy((AreaDados+Indice)->Estado,ESTADO_NUL);
  if ( EST_AVC(Cuba).ChaveLocRem eq LOCAL ) 
  {
	strcpy((AreaDados+Indice)->Estado,ScoreGetStr(MAN_LOC));
  } 
  else 
  {
	/*-- Sinaliza cuba em Manual-Remoto. --*/
	if ( EST_AVC(Cuba).ChaveAutMan eq MANUAL ) 
	{
	  if (EST_AVC(Cuba).ManualControle)
		strcpy((AreaDados+Indice)->Estado,ScoreGetStr(MAN_CTR));	/* Manual pelo controle */
	  else
		strcpy((AreaDados+Indice)->Estado,ScoreGetStr(MAN_REM));
	} 
	else 
	{
	  if ( EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL)
	  {
		/*-- Sinaliza cuba em Efeito Anodico. --*/
		if ( EST_AVC(Cuba).Ea eq VERDADEIRO )
		{
		  if (AVC.User1[Cuba].EstadoSoproEspec eq SOPRO_EXECUCAO)
		    strcpy((AreaDados+Indice)->Estado, EA_SOPRO);
		  else
		    strcpy((AreaDados+Indice)->Estado, ScoreGetStr(EA));
		}
		else
		{
		  /*-- Sinaliza cuba em Corrida. --*/
		  if ( EST_AVC(Cuba).Corrida eq VERDADEIRO ) 
			strcpy((AreaDados+Indice)->Estado,ScoreGetStr(CORRIDA));
		  else
		  {
			/*-- Sinaliza cuba em Quebrada --*/
			if ( EST_AVC(Cuba).Quebrada eq VERDADEIRO ) 
			  strcpy((AreaDados+Indice)->Estado,ScoreGetStr(QUEBRADA));
		  }
		}
 	  }
	}
  }
}/*-- SinalSituacao --*/

/*
--------------------------------------------------------------------------------
| CalcHoraPrevEa - Calcula o tempo  que  a  cuba  esta  em  Previsao de Efeito |
|               Anodico, montando-o na area de dados do relatorio.             |
--------------------------------------------------------------------------------
*/
void CalcHoraPrevEa ( t_dados *AreaDados, int Cuba, int Indice )
{
  long		HoraPrevEa;
  struct tm StData;

  /*-- Calculo do duracao da previsao de efeito anodico da cuba --*/
  memset((AreaDados+Indice)->HoraPrevEa,' ',sizeof((AreaDados+Indice)->HoraPrevEa));
  if ((EST_AVC(Cuba).EaPrev eq VERDADEIRO) and 
	  ((AreaDados+Indice)->SinEst[0] ne '+'))
  {
	HoraPrevEa = AVC.Ea[Cuba].EaPrevT0;  
	memcpy(&StData,localtime(&HoraPrevEa),sizeof(StData));
	sprintf((AreaDados+Indice)->HoraPrevEa,"%02d:%02d",StData.tm_hour,StData.tm_min);
  }
  else
	strcpy((AreaDados+Indice)->HoraPrevEa,TEMPO_NUL);

} /*-- CalcHoraPrevEa --*/

/*
------------------------------------------------------------------------------
| PegaPassoTInc - Pega o passo corrente que a cuba esta executando na tabela |
|                 de incrementos e sinaliza sua ativacao                     |
------------------------------------------------------------------------------
*/
void PegaPassoTInc(t_dados *AreaDados, int Cuba, int Indice)
{

  if ((EST_AVC(Cuba).TabOpeAtiva eq VERDADEIRO) and 
	  ((AreaDados+Indice)->SinEst[0] ne '+'))
  {
	sprintf((AreaDados+Indice)->SinEst, "%1s", "t");
	sprintf((AreaDados+Indice)->PassoTInc, "%02d", AVC.Ccont[Cuba].PassoTabOpe + 1);
  }
  else
	strcpy((AreaDados+Indice)->PassoTInc, "--");

} /*-- PegaPassoTInc --*/

/*
--------------------------------------------------------------------------------
| CalcAtrasoEa - Calcula o tempo de atraso  de  efeito anodico, montando-o  na |
|                area de dados do relatorio.                                   |
--------------------------------------------------------------------------------
*/
void CalcAtrasoEa(t_dados *AreaDados, int Cuba, int Indice, long HoraAtual)
{
  long	TempoAtraEa;

  strcpy((AreaDados+Indice)->TempoAtraEa,TEMPO_NUL);

  /*-- Calculo do tempo de atraso de efeito anodico da cuba --*/
  if ((AreaDados+Indice)->SinEst[0] ne '+')
  {
	if ((HoraAtual - AVC.Ea[Cuba].EaHoraInicio) > (AVC.Param[Cuba].EaAtrasoMax*60L))
	{
	  TempoAtraEa = (HoraAtual - AVC.Ea[Cuba].EaHoraInicio) -
					 (AVC.Param[Cuba].EaAtrasoMax * 60L);
	  MontaHoraMin(TempoAtraEa/60L, (AreaDados+Indice)->TempoAtraEa, "%02d:%02d");
	}
  }

} /*-- CalcAtrasoEa --*/

/*
--------------------------------------------------------------------------------
| CalcMedias - Calcula a media das tensoes de Incremento, Placa, Alvo, Atual e |
|               Erro, montando-as no rodape do relatorio.                      |
--------------------------------------------------------------------------------
*/
void CalcMedias ( t_rodape *Rodape, t_acum *Acum )
{

  /*-- Calculo das medias de tensoes --*/
  if ( Acum->NCubasAcum  ne  0 )
  {
	Rodape->MediaInc   = Acum->IncAcum / Acum->NCubasAcum;
	Rodape->MediaPlaca = Acum->PlacaAcum / Acum->NCubasAcum;
	Rodape->MediaAlvo  = Acum->AlvoAcum / Acum->NCubasAcum;
	Rodape->MediaAtual = Acum->AtualAcum / Acum->NCubasAcum;
	Rodape->MediaErro  = Acum->ErroAcum / Acum->NCubasAcum;
  } 
  else
  {
	Rodape->MediaInc   = 0.0;
	Rodape->MediaPlaca = 0.0;
	Rodape->MediaAlvo  = 0.0;
	Rodape->MediaAtual = 0.0;
	Rodape->MediaErro  = 0.0;
  }
}

/*
--------------------------------------------------------------------------------
| LeTabelas - Quando nao estiver rodando no micro de controle, le do micro que |
|             estiver no controle todas as tabelas da base de dados que forem  |
|             consultadas por ESTE relatorio. So devem ser lidas as tabelas que|
|             sofram alteracoes ON-LINE (AVC.Abs nao e' necessario).           |
|             Retorna 0 se ok, e diferente de 0 -> codigo de erro              |
--------------------------------------------------------------------------------
*/
int LeTabelas(void)
{
  int nodo_controle, status;
  char msg_erro[80];

  nodo_controle=AVL.NodoNoControle;
  if (My_nid ne nodo_controle)
  { /* -- Estou rodando em outro nodo, entao leio tabelas do controle -- */

	/* -- Le tabela AVL -- */
	if (status=ScoreBd(nodo_controle,TABELA_AVL,BD_LER,&AVL,0,
				sizeof(t_uavl)))
	{
	  sprintf(msg_erro, ScoreGetStr(SCORE_ERR_4), My_name, COD_ERRO_16,
				   status, TABELA_AVL);
	  ExibeErro(msg_erro);
	  return(status);
	}

	/* -- Le tabela EST_AVC -- */
	if (status=ScoreBd(nodo_controle,TABELA_EST_AVC,BD_LER,&EST_AVC(0),0,
				sizeof(t_estado_avc)))
	{
	  sprintf(msg_erro, ScoreGetStr(SCORE_ERR_4), My_name, COD_ERRO_16,
				   status, TABELA_EST_AVC);
	  ExibeErro(msg_erro);
	  return(status);
	}

	/* -- Le tabela AVC.Param -- */
	if (status=ScoreBd(nodo_controle,TABELA_AVC,BD_LER,(void *)&AVC.Param,
						CalcByteOffset(&AVC,&AVC.Param),
						sizeof(AVC.Param)))
	{
	  sprintf(msg_erro, ScoreGetStr(SCORE_ERR_4), My_name, COD_ERRO_16,
				   status, TABELA_AVC);
	  ExibeErro(msg_erro);
	  return(status);
	}

	/* -- Le tabela AVC.Cleit -- */
	if (status=ScoreBd(nodo_controle,TABELA_AVC,BD_LER,(void *)&AVC.Cleit,
						CalcByteOffset(&AVC,&AVC.Cleit),
						sizeof(AVC.Cleit)))
	{
	  sprintf(msg_erro, ScoreGetStr(SCORE_ERR_4), My_name, COD_ERRO_16,
				   status, TABELA_AVC);
	  ExibeErro(msg_erro);
	  return(status);
	}
	/* -- Le tabela AVC.Ccont -- */
	if (status=ScoreBd(nodo_controle,TABELA_AVC,BD_LER,(void *)&AVC.Ccont,
						CalcByteOffset(&AVC,&AVC.Ccont),
						sizeof(AVC.Ccont)))
	{
	  sprintf(msg_erro, ScoreGetStr(SCORE_ERR_4), My_name, COD_ERRO_16,
				   status, TABELA_AVC);
	  ExibeErro(msg_erro);
	  return(status);
	}

	/* -- Le tabela AVC.Ea -- */
	if (status=ScoreBd(nodo_controle,TABELA_AVC,BD_LER,(void *)&AVC.Ea,
						CalcByteOffset(&AVC,&AVC.Ea),
						sizeof(AVC.Ea)))
	{
	  sprintf(msg_erro, ScoreGetStr(SCORE_ERR_4), My_name, COD_ERRO_16,
				   status, TABELA_AVC);
	  ExibeErro(msg_erro);
	  return(status);
	}

	/* -- Le tabela AVC.CcontMcp -- */
	if (status=ScoreBd(nodo_controle,TABELA_AVC,BD_LER,(void *)&AVC.CcontMcp,
						CalcByteOffset(&AVC,&AVC.CcontMcp),
						sizeof(AVC.CcontMcp)))
	{
	  sprintf(msg_erro, ScoreGetStr(SCORE_ERR_4), My_name, COD_ERRO_16,
				   status, TABELA_AVC);
	  ExibeErro(msg_erro);
	  return(status);
	}


  }
  return(0);
}

/*-- RelGerAtual.c --*/
