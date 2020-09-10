
/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: TrataEa.c

	CONTEUDO	: Tarefa encarregada da identificacao, contabilizacao e sina-
				  lizacao do Efeito Anodico.

	AUTOR		: Joao Thomaz Pereira

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	08/09/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
12/02/93 | Inicializacao de EaVmax no inicio de Ea              | Leonel
-------------------------------------------------------------------------------
19/03/93 | Nao contabiliza Ea para cuba partida, apenas normal  | Leonel
-------------------------------------------------------------------------------
05/05/93 | - Acrescentado acionamento de sirene qdo. inicio_ea. | Leonel
         | - Passa a considerar fim de efeito anodico para todas|
         |   as cubas em efeito quando a linha e' desabilitada. |
-------------------------------------------------------------------------------
01/07/94 | Acrescentado  teste  da  chave do painel da cuba  na | Carlos
         | eliminacao automatica de efeito anodico.             |
-------------------------------------------------------------------------------
05/07/94 | Edicao inicial de migracao para o QNX 4.2			| Leonel
-------------------------------------------------------------------------------
10/12/94 | Alterada comparacao p/ inicio Ea de Resit. p/ Tensao	| Leonel
-------------------------------------------------------------------------------
14/06/95 | Acionada sirene de EA quando ele reincidir na espera | Carlos
         | de seu fim                                           |
-------------------------------------------------------------------------------
21/08/95 | Alterada classificacao de efeito anodico para o novo | Leonel
         | algoritmo de previsao de efeito anodico.             |
-------------------------------------------------------------------------------
03/10/96 | Incluida sinalizacao de atraso de EA para rel. hist. | Carlos
-------------------------------------------------------------------------------
18/12/96 | Incluida atualizacao de EaHoraAnt para relat. hist.  | Carlos
-------------------------------------------------------------------------------
01/09/97 | Alterada criacao da tarefa de eliminacao de EA       | Carlos
-------------------------------------------------------------------------------
19/11/97 | Adaptacao nova supressao EA para cba                 | Carlos
-------------------------------------------------------------------------------
16/04/98 | Finalizacao de quebrada preventiva na previsao       | Carlos
-------------------------------------------------------------------------------
28/06/99 | Incluido tratamento de booster de corrente			| Carlos
-------------------------------------------------------------------------------
08/07/99 | Incluido HoraEA-HoraPrev quando esta em previsao no	| Carlos
         | evento InicioEA                                     	|
-------------------------------------------------------------------------------
14/06/02 | Incluido VMax e IntervUltEa no evento Inicio			| Carlos
-------------------------------------------------------------------------------
08/07/02 | Incluido desab. de eliminacao de EA pelo operador	| Carlos
-------------------------------------------------------------------------------
26/08/05 | Correcao inic. de EaContLXLim no inicio do EA    	| Carlos
-------------------------------------------------------------------------------
$Id: TrataEa.c,v 1.1.2.1 2012/09/28 17:09:38 leo Exp $

$Log: TrataEa.c,v $
Revision 1.1.2.1  2012/09/28 17:09:38  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

Revision 1.16  2008/12/11 21:51:46  leo
Corrigida contabilizacao de EaContLXLim. Estava contabilizando duas vezes
durante espera de EA.

Revision 1.15  2008/10/13 17:49:53  leo
Alteracao tratamento de sopro.

Revision 1.14  2008/08/01 20:38:42  leo
Correcao tratamento de DXLim. Acrescentado tratamento para contabilizar durante
espera de fim EA para retirar ao final do mesmo.

Revision 1.13  2008/02/18 21:26:27  leo
Incluido 5o. parametro (DerivHMaxEaPrev) no evento InicioEa

Revision 1.12  2007/10/10 14:42:01  leo
Inclusao de tratamento de espera durante aguarda fim ea para desconsiderar
picos de duracao inferior a NCicIniEa de forma a nao indicar um EA maior do
que o real. Problema de pico de tensao durante o tempo de espera de fim EA
na CBA.

Revision 1.11  2007/01/12 17:09:32  rogerio
Criacao do relatorio de Previsao de EA

Revision 1.10  2006/12/21 18:04:18  alex
novo ope tabela alternativa

Revision 1.9  2005/12/12 13:24:46  leo
Retirados ifdefs nao mais usados.

Revision 1.8  2005/08/26 20:01:24  leo
Restauracao versao 1.6

Revision 1.7  2005/08/26 18:38:48  clage
Corrigida inicializacao de EaContLXLim no Inicio do EA

Revision 1.6  2005/06/17 12:15:41  clage
Incluido tratamento do relat. de integracao e trat VInst > VEaXLm no EA

Revision 1.5  2005/01/21 18:38:32  clage
Aumento 1 casa em Par3 evento InicioEa, acionamento da lampada junto com
sirene se tensao subir quando aguardando fim de EA

Revision 1.4  2004/07/09 14:10:49  clage
Algoritmo de Sopro Especial

Revision 1.3  2004/07/05 14:41:19  clage
Algoritmo de sopro especial

Revision 1.2  2003/03/13 20:59:19  leo
Alteracao para tratamento de tabela de partida de cubas.

******************************************************************************/

#define	 PROGRAMA_PRINCIPAL	1

#include	<stdio.h>
#include	<stdlib.h>
#include	<errno.h>
#include	<sys/kernel.h>
#include	<string.h>
#include	<time.h>
#include	<Prototipos.h>
#include	<Score.h>
#include	<ScoreMsgs.h>
#include	<ScoreErros.h>
#include	<Semaf.h>
#include	<Eventos.h>
#include	<TrataEa.h>
#include	<math.h>

/*
-------------------------------------------------------------------------------
                           Variaveis Globais
-------------------------------------------------------------------------------
*/
/* -- Apontadores para as tabelas comuns -- */
#include	<VarsComum.h>
/* -- Variaveis do modulo -- */
#include	<VarsTrataEa.h>
/************************************* teste *********************************/
#include	<UsuRemota.h>
/************************************* teste *********************************/
  void StartTabEliminaEa(int Cuba, int NumTabEa);
  void NomeParEvento(int Cuba, char *Nome);
  void IniFlagsTabSup( void ); /* inicializacao para tabela de supressao */

  short int EaNTerm[MAX_CUBAS];

  void AtivaSoproEspecial(int Cuba);
  void TrataSoproEspecial(int Cuba);

  void AEK(int Cuba);

void main(void)
{
  byte			pri_vez;
  int 			Cuba,
				TidMcp;
  t_mens_padrao	Mens;

  /* -- Recebe endereco da area de dados comum ao processo -- */

  Reply(Receive(0, &Comum, sizeof(Comum)), 0, 0);
      
  /* -- Inicializa apontadores para tabelas globais -- */

  InitVarsComum();

  /* -- Guarda hora atual em secundos -- */
  HoraAtualSec=time(NULL)/TIMES_PER_SEC; /* -- segs. apartir 1/1/1970 -- */

  /* -- Inicializa todas as variaveis de trabalho e executa os procedimentos 
	 necessarios a inicializacao do calculos. -- */
  IniTrataEa();

  pri_vez = FALSO;

  loop			/*  Loop eterno */
  {
	/* -- Recebe sinalizacao para verificacao de Efeito Anodico -- */
	if((TidMcp = Receive(0, &Mens, sizeof(Mens))) eq -1)
	  EmiteErroFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_ERR_8),COD_ERRO_18,errno);
//	  EmiteErroFor(TODOS_DISPOSITIVOS,"Erro receive TidMcp %d",errno);

	/* -- Guarda hora atual em secundos -- */
    HoraAtualSec=time(NULL)/TIMES_PER_SEC; /* -- segs. apartir 1/1/1970 -- */

	switch(Mens.Acao)
	{
	  case INICIALIZACAO:
    	/*** IniVarsEa(); retirado em 4-12-92 JTP***/
		break;
	
      case CICLO_LEITURA:	
  		AlocaSemaf(SEMAF_AVC);
		if( pri_vez eq FALSO )
		{
		  IniFlagsTabSup(); /* inicializacao para tabela de supressao */
		  pri_vez = VERDADEIRO;
		}
        TrataEa();
  		LiberaSemaf(SEMAF_AVC);
		break;

	  case DESABILITOU_LINHA:
		/* -- Considera fim de ea para as cubas que estejam em Ea -- */
		for(Cuba=0; Cuba < NumCubas; Cuba++)
		  if ( (AlgControle(Cuba,ALG_SCORE01) eq VERDADEIRO) and
			   (EST_AVC(Cuba).Ea eq VERDADEIRO) )
		  {
			if (AVC.Ea[Cuba].EaContLEsp eq 0)
			  AVC.Ea[Cuba].EaHoraFimProv = HoraAtualSec;
			FimEa(Cuba);
		  }
		break;
	
	  default:
		EmiteErroFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_ERR_8),COD_ERRO_58,
					 Mens.Acao);
//		EmiteErroFor(TODOS_DISPOSITIVOS,"Erro Fatal - Acao nao tratada %d",
//				     Mens.Acao);
		break;
	}

	Reply(TidMcp,&Mens,sizeof(Mens));

  }
}

/*
--------------------------------------------------------------------------------
	TrataEa	-	Tratamento de Efeito Anodico.
--------------------------------------------------------------------------------
*/
void TrataEa(void)
{
int Cuba;

  for(Cuba=0; Cuba < NumCubas; Cuba++)
  {
    /* Verifica se alterou numero do algoritmo da cuba on-line */
    if (AlterouNumAlgCtr(Cuba, ALG_SCORE01))
    { /* -- selecionou ou desselecionou algoritmo do Score -- */
      /* -- Inicializa variaveis do algoritmo do Score -- */
      IniTrataEaCuba(Cuba);
	  IniVarsEaCuba(Cuba);
	}
	if ( (AlgControle(Cuba,ALG_SCORE01) eq VERDADEIRO) and
	     (EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL) )
	{
	  if( EST_AVC(Cuba).ForaLeitura eq FALSO )
      {
		/* Inicio Alteracao - Carlos - 23/06/99 */
		/* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
        AVC.Ea[Cuba].EaRLim = (AVC.Param[Cuba].EaVoltLim - AVC.Param[Cuba].Bemf)/
	      AVC.Ccont[Cuba].INominalCuba;
#else
        AVC.Ea[Cuba].EaRLim = (AVC.Param[Cuba].EaVoltLim - AVC.Param[Cuba].Bemf)/
	      AVL.INominal;
#endif
		/* Fim Alteracao - Carlos - 23/06/99 */

		if (EST_AVC(Cuba).Est.TrataTabPartida)
		{ /* tabela ativa, usa Limite indicado pela tabela */
		  if( AVC.Cleit[Cuba].Vinst >= AVC.User1[Cuba].EaVoltLimTabPartida)
		    goto acimaeav;
		  else
		    goto abaixoeav;
		}
		else
	      if( AVC.Cleit[Cuba].Vinst >= AVC.Param[Cuba].EaVoltLim)
		{
acimaeav:
		  if(EST_AVC(Cuba).Ea eq FALSO)
		  {
		    if (EST_AVC(Cuba).TrataTPinos eq VERDADEIRO)
		    {
		      if ((AVC.Param[Cuba].NCicIniEaTAnodo ne 0) and
			      (ContEaTAnodo[Cuba] eq 0))
			    EmiteAlarmeFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_MSG_279),
//			  EmiteAlarmeFor(TODOS_DISPOSITIVOS,"Tensao cuba %d acima de %2.1fV!",
				ConvCubScoreOper(Cuba),
				(EST_AVC(Cuba).Est.TrataTabPartida ? AVC.User1[Cuba].EaVoltLimTabPartida : AVC.Param[Cuba].EaVoltLim ));
		    }
			else
			{
			  if ((AVC.Param[Cuba].NCicIniEaNormal ne 0) and
			      (ContEaNormal[Cuba] eq 0))
			    EmiteAlarmeFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_MSG_279),
//			  EmiteAlarmeFor(TODOS_DISPOSITIVOS,"Tensao cuba %d acima de %2.1fV!",
				ConvCubScoreOper(Cuba),
				(EST_AVC(Cuba).Est.TrataTabPartida ? AVC.User1[Cuba].EaVoltLimTabPartida : AVC.Param[Cuba].EaVoltLim ));
			}
			/* Trata delay para inicio EA */
			ContEaTAnodo[Cuba]++;
		    ContEaNormal[Cuba]++;
			if (EST_AVC(Cuba).TrataTPinos eq VERDADEIRO)
		    {
		      if (ContEaTAnodo[Cuba] > AVC.Param[Cuba].NCicIniEaTAnodo)
		      {
			    ContEaNormal[Cuba]=0;
			    ContEaTAnodo[Cuba]=0;
			    InicioEa(Cuba);
			  }
			}
			else
			  if (ContEaNormal[Cuba] > AVC.Param[Cuba].NCicIniEaNormal)
			  {
			    ContEaNormal[Cuba]=0;
			    ContEaTAnodo[Cuba]=0;
			    InicioEa(Cuba);
			  }
		  }
		  else
		  { // Durante EA
		    /* Calcula VMax e VMinEa */

		    EST_AVC(Cuba).Est.ZeraCA = VERDADEIRO;
			
			CalcVMaxMin(Cuba);

		    if (AVC.ParUser1[Cuba].HabAEK eq VERDADEIRO)
	          AEK(Cuba); 

		    if( AVC.Ea[Cuba].EaContLEsp > 0 )
            { // Estava aguardando Fim de EA e tensao voltou a subir
			  /* Trata delay para considerar fim de aguarda fim EA para evitar reset com apenas um pico */
			  ContEaTAnodo[Cuba]++;
		      ContEaNormal[Cuba]++;
			  if (EST_AVC(Cuba).TrataTPinos eq VERDADEIRO)
		      {
		        if (ContEaTAnodo[Cuba] > AVC.Param[Cuba].NCicIniEaTAnodo)
		        { // reseta contador de espera e considera fim de aguarda fim EA
			      ContEaNormal[Cuba]=0;
			      ContEaTAnodo[Cuba]=0;
	    	      AVC.Ea[Cuba].EaVAcumEspBruta = 0;
  				  AVC.Ea[Cuba].EaPotAcumEspBruta = 0;
  				  AVC.Ea[Cuba].EaVAcumEspLiq = 0;
  				  AVC.Ea[Cuba].EaPotAcumEspLiq = 0;
				  AVC.Ea[Cuba].EaContLEsp = 0;
				  AVC.Ea[Cuba].EaContLEspXLim = 0;	/* Contador de cic. de leit. de tensao EA acima de VEaXLim em espera de fim ea */
				  // Alteracao - Carlos - 19/01/05 - Liga lampada se tensao sobe quando aguarda fim de EA
	 			  ComandaLampEa(Cuba,LIGAR);
				  ComandaSirene(Cuba,LIGAR);
				}
			  }
			  else // nao esta em troca de pinos
			  {
			    if (ContEaNormal[Cuba] > AVC.Param[Cuba].NCicIniEaNormal)
		        { // reseta contador de espera e considera fim de aguarda fim EA
			      ContEaNormal[Cuba]=0;
			      ContEaTAnodo[Cuba]=0;
	    	      AVC.Ea[Cuba].EaVAcumEspBruta = 0;
  				  AVC.Ea[Cuba].EaPotAcumEspBruta = 0;
  				  AVC.Ea[Cuba].EaVAcumEspLiq = 0;
  				  AVC.Ea[Cuba].EaPotAcumEspLiq = 0;
				  AVC.Ea[Cuba].EaContLEsp = 0;
				  AVC.Ea[Cuba].EaContLEspXLim = 0;	/* Contador de cic. de leit. de tensao EA acima de VEaXLim em espera de fim ea */
				  // Alteracao - Carlos - 19/01/05 - Liga lampada se tensao sobe quando aguarda fim de EA
	 			  ComandaLampEa(Cuba,LIGAR);
				  ComandaSirene(Cuba,LIGAR);
				}
			  }
			  // Se ainda em tempo de aguarda, contabiliza valores em aguarda
			  if( AVC.Ea[Cuba].EaContLEsp > 0 )
			    AguardaFimEa(Cuba);
            }
			// Verifica se nao esta em tempo de espera para calcular os dados
		    if( AVC.Ea[Cuba].EaContLEsp eq 0 )
			{ // Nao esta aguardando fim, trata EA
			  CalcDadosEa(Cuba);
			  // Algoritmo de sopro especial
			  TrataSoproEspecial(Cuba);
			}
		  }
	    }
		else
		{ // tensao abaixo do limite de EA
abaixoeav:
		  ContEaTAnodo[Cuba]=0;
		  ContEaNormal[Cuba]=0;
		  if(EST_AVC(Cuba).Ea eq VERDADEIRO )
		  { /* Calcula VMax e VMinEa */
			CalcVMaxMin(Cuba);

		    if (AVC.ParUser1[Cuba].HabAEK eq VERDADEIRO)
	          AEK(Cuba); 

			/* Contabiliza valores em aguarda fim */
		    AguardaFimEa(Cuba);
		  }
		  else
		  {
    		EST_AVC(Cuba).Est.AEK = FALSO;
		  }
		}
	  }
	}
    /* verifica se tabela alternativa habilitada */
    if( EST_AVC(Cuba).AtivaTabEaAltern eq VERDADEIRO )	
    {
	  /* se tabela e do tipo Tempo, checa termino */
      if( EST_AVC(Cuba).TipoTabEaAltern eq 0 ) // tipo Tempo
	  {
		/* verifica se esgotou o tempo de ativacao */
		if(HoraAtualSec > (AVC.Ea[Cuba].IniTabEaAltern+AVC.Ea[Cuba].DurTabEaAltern))
  	      EST_AVC(Cuba).AtivaTabEaAltern = FALSO;
	  }
    }
  }
}


/*
--------------------------------------------------------------------------------
	IniTrataEa	-	Inicializacao de todas as variaveis pertencentes
					ao Tratamento de Efeito Anodico.
--------------------------------------------------------------------------------
*/
void IniTrataEa(void)

{
  int Cuba;

  /* -- Copia NumCubas da base de dados para local -- */
  NumCubas=AVL.NumCubas;

  /* -- Inicializa numero de algoritmo -- */
  IniNumAlgCtr();

  /* -- Inicializa todas as variaveis necessarias aos Calculos -- */
  AlocaSemaf(SEMAF_AVC);
  for(Cuba=0; Cuba<NumCubas; Cuba++)
  {
	if (AlgControle(Cuba,ALG_SCORE01) eq VERDADEIRO)
	{
	  IniTrataEaCuba(Cuba);
	  AtivaSoproEspecial(Cuba);
	}
  }
  LiberaSemaf(SEMAF_AVC);
  IniVarsEa();
}

 /*
 --------------------------------------------------------------------------------
  	IniFlagsTabSup	-	Inicializacao de variaveis tabela de supressao
 --------------------------------------------------------------------------------
 */
 void IniFlagsTabSup()
 {
   int Cuba;

   for(Cuba=0; Cuba<AVL.NumCubas; Cuba++)
   {
	 EST_AVC(Cuba).ElimEaAtivo = FALSO;
	 EaNTerm[Cuba] = FALSO;
   }
 }

/*
--------------------------------------------------------------------------------
	IniTrataEaCuba	-	Inicializacao de todas as variaveis pertencentes
						ao Tratamento de Efeito Anodico para a cuba dada.
--------------------------------------------------------------------------------
*/
void IniTrataEaCuba(int Cuba)
{
	EST_AVC(Cuba).Ea = FALSO;
	EST_AVC(Cuba).ElimEaAtivo = FALSO;
	EaNTerm[Cuba] = FALSO;
/* -- Inicio - 14/06/2005 - Carlos - Tensao EA acima de VEaXLim -- */
  	AVC.Ea[Cuba].EaContLXLim = 0;	
/* -- Fim - 14/06/2005 - Carlos - Tensao EA acima de VEaParam -- */
  	AVC.Ea[Cuba].EaContLEspXLim = 0;	/* Contador de cic. de leit. de tensao EA acima de VEaXLim em espera de fim ea */
  	AVC.Ea[Cuba].EaContL = 0;	
  	AVC.Ea[Cuba].EaContLEsp = 0;	
	AVC.Ea[Cuba].EaHoraFimProv = HoraAtualSec;
	AVC.Ea[Cuba].EaHoraAnt = HoraAtualSec;
    ContEaTAnodo[Cuba]=0;
	ContEaNormal[Cuba]=0;
}

/*
--------------------------------------------------------------------------------
	IniVarsEa	-	Inicializacao de parcial das variaveis pertencentes
					ao Tratamento de Efeito Anodico.
--------------------------------------------------------------------------------
*/
void IniVarsEa(void)
{
  int Cuba;

  /* -- Copia NumCubas da base de dados para local -- */
  NumCubas=AVL.NumCubas;

  /* -- Inicializa todas as variaveis necessarias aos Calculos -- */
  AlocaSemaf(SEMAF_AVC);
  for(Cuba=0; Cuba<NumCubas; Cuba++)
  {
	if (AlgControle(Cuba,ALG_SCORE01) eq VERDADEIRO)
	  IniVarsEaCuba(Cuba);
  }
  LiberaSemaf(SEMAF_AVC);
}

/*
--------------------------------------------------------------------------------
	IniVarsEaCuba -	Inicializacao de parcial das variaveis pertencentes
					ao Tratamento de Efeito Anodico para a cuba dada.
--------------------------------------------------------------------------------
*/
void IniVarsEaCuba(int Cuba)
{
    AVC.Ea[Cuba].EaVAcumEspBruta = 0;
  	AVC.Ea[Cuba].EaPotAcumEspBruta = 0;
  	AVC.Ea[Cuba].EaVAcumEspLiq = 0;
  	AVC.Ea[Cuba].EaPotAcumEspLiq = 0;
}

/*
--------------------------------------------------------------------------------
	InicioEa	-	Calcula parametros relativos ao Inicio de Efeito Anodico
--------------------------------------------------------------------------------
*/
void InicioEa(int Cuba)
{
  long DifPrevEa;
  char ParEv2[9];
  char ParEv3[9];
  char ParEv5[9];
  char Aux[9];
  float EaVMaxAnt;
  long  IntervUltEa;
  char ParEv1[9];
  int TipoEa, i;


  EST_AVC(Cuba).Est.ZeraCA = VERDADEIRO;
  EST_AVC(Cuba).Ea = VERDADEIRO;
  if(AVC.ParUser1[Cuba].HabAEK eq VERDADEIRO)
	EST_AVC(Cuba).Est.AEK = VERDADEIRO;
  if (AVC.ParUser1[Cuba].HabLogMovQueb eq VERDADEIRO)
	AVC.Param[Cuba].HabMovIniQueb = 0;
  /* -- liga variavel de efeito ea para o modulo Mcc -- */
  EST_AVC(Cuba).EfeitoEa=VERDADEIRO;

  AVC.Ea[Cuba].EaHoraAnt = AVC.Ea[Cuba].EaHoraInicio;  
  AVC.Ea[Cuba].EaHoraInicio = HoraAtualSec;  
  TipoEa = ClassificaEa(Cuba);
  AVC.Ea[Cuba].EaClasse=TipoEa;

  AVC.Ea[Cuba].EaVAcumBruta = AVC.Cleit[Cuba].Vinst;
  AVC.Ea[Cuba].EaPotAcumBruta = AVC.Cleit[Cuba].Pinst;
  AVC.Ea[Cuba].EaVAcumLiq = AVC.Cleit[Cuba].Vinst - AVC.Ccont[Cuba].VAlvo;
  AVC.Ea[Cuba].EaPotAcumLiq = (AVC.Cleit[Cuba].Vinst - AVC.Ccont[Cuba].VAlvo) *
							  AVC.Cleit[Cuba].Iinst;
  AVC.Ea[Cuba].EaContL = 1;	
  AVC.Ea[Cuba].EaContLEsp = 0;	
  AVC.Ea[Cuba].EaVAcumEspBruta = 0;
  AVC.Ea[Cuba].EaPotAcumEspBruta = 0;
  AVC.Ea[Cuba].EaVAcumEspLiq = 0;
  AVC.Ea[Cuba].EaPotAcumEspLiq = 0;
  AVC.Ea[Cuba].EaContLXLim = 0;
  AVC.Ea[Cuba].EaContLEspXLim = 0;	/* Contador de cic. de leit. de tensao EA acima de VEaXLim em espera de fim ea */
  AVC.User1[Cuba].NumQuebProg = 0;
  AVC.User1[Cuba].NumDB = 0;
  EaLocal[Cuba].AEK_VMax = 0.0;
  AVC.User1[Cuba].AEKVMax = 0.0;
  EaLocal[Cuba].AEK_VMaxIni = 0.0;
  EaLocal[Cuba].ContSobe = 0;
  EST_AVC(Cuba).Est.FimAEK = FALSO;
  EST_AVC(Cuba).Est.ForcaAEK = FALSO;
  EST_AVC(Cuba).Est.ForcaDesceAEK = FALSO;
  EaLocal[Cuba].EaMed = 0.0;
  EaLocal[Cuba].NLeitEa = 0;
  EaLocal[Cuba].EaDesvPad = 0.0;
  EaLocal[Cuba].FimMoveAEK = FALSO;
  EaLocal[Cuba].DeltaTempo= 0;
  EaLocal[Cuba].ContMovCimaAEKPF= 0;
  EaLocal[Cuba].ContMovBaixoAEKPF= 0;
  EaLocal[Cuba].HoraUltMovAEKPF= 0;

  for( i = 0; i < 240 ; i++)
  {
  	EaLocal[Cuba].LeitEa_vet[i] = 0;
  }

/* -- Inicio - 14/06/2005 - Carlos - Tensao EA acima de VEaXLim -- */
  if (AVC.Cleit[Cuba].Vinst >= AVC.Param[Cuba].VEaXLim)
  	AVC.Ea[Cuba].EaContLXLim = 1;	
/* -- Fim - 14/06/2005 - Carlos - Tensao EA acima de VEaParam -- */

  EaVMaxAnt = AVC.Ea[Cuba].EaVMax;
  IntervUltEa = AVC.Ea[Cuba].EaHoraInicio - AVC.Ea[Cuba].EaHoraAnt;
  if (AVC.Ea[Cuba].EaHoraAnt < AVL.HoraPartida)
  { // Alteracao - Carlos - 19/01/05 - Aumentou +1 casa na hora em ParEv3
	MontaHoraMin(IntervUltEa/60, Aux, "%03d:%02d");
	sprintf(ParEv3,"*%s", Aux);
  }
  else // Alteracao - Carlos - 19/01/05 - Aumentou +1 casa na hora em ParEv3
	MontaHoraMin(IntervUltEa/60, ParEv3, "%03d:%02d");

  if (EST_AVC(Cuba).Est.QuebPrev eq VERDADEIRO)
  { /*-- Finaliza quebrada preventiva --*/
	EST_AVC(Cuba).Est.QuebPrev = FALSO;
	GeraEvento(FIM_QUEB_PREV, Cuba, -1, "   EA   ", "--------");

	/*-- Contabiliza quebrada preventiva --*/
	AVC.User1[Cuba].NumQuebPrev += 1;
	SUPERV_AVC(Cuba).Sup.NumQuebPrev += 1;
	SUPERV_AVC_TURNO(Cuba).Sup.NumQuebPrev += 1;

	/*-- Contabiliza duracao da quebrada preventiva --*/
	SUPERV_AVC(Cuba).Sup.ContDurQPrev += AVC.User1[Cuba].ContDurQPrev;
	SUPERV_AVC_TURNO(Cuba).Sup.ContDurQPrev += AVC.User1[Cuba].ContDurQPrev;

	/*-- Contabiliza EA em quebrada preventiva --*/
	SUPERV_AVC(Cuba).Sup.NumEaQPrev += 1;
	SUPERV_AVC_TURNO(Cuba).Sup.NumEaQPrev += 1;
  }
  if (EST_AVC(Cuba).Est.QuebPrevInib eq INIBICAO_PROXIMO_EA)
  { /*-- Finaliza inibicao por ea --*/
	EST_AVC(Cuba).Est.QuebPrevInib = QPREV_SEM_INIBICAO;
  }
  AVC.User1[Cuba].NumQuebPrev = 0;
  AVC.User1[Cuba].NumPrevQPrev = 0;
 
  if(AVC.ParUser2[Cuba].HabilitaPFCBA eq VERDADEIRO)
  {
    DifPrevEa = AVC.Ea[Cuba].EaHoraInicio - AVC.User3[Cuba].HoraEstAtual[AVC.User2[Cuba].EstadoPFCBA];
    MontaHoraMinSeg(DifPrevEa, ParEv2, "%02d:%02d:%02d");
  }
  else
  {
    strcpy(ParEv2, "--------");
    if (EST_AVC(Cuba).EaPrev eq VERDADEIRO)
    {
	  DifPrevEa = AVC.Ea[Cuba].EaHoraInicio - AVC.Ea[Cuba].EaPrevT0;
	  MontaHoraMinSeg(DifPrevEa, ParEv2, "%02d:%02d:%02d");
    }
  }
  // Carlos 25/06/04 - Ativa algoritmo de sopro especial
  AtivaSoproEspecial(Cuba);
  AVC.Ea[Cuba].EaVMax = AVC.Cleit[Cuba].Vinst;


    EaNTerm[Cuba] = FALSO;

  memset(ParEv1, 0x00, sizeof(ParEv1));
  if(AVC.ParUser2[Cuba].HabilitaPFCBA eq VERDADEIRO)
  {
	if(IntervUltEa >= AVC.Param[Cuba].EaAtrasoMax or
		AVC.User2[Cuba].EstadoPFCBA eq 0) 
	  sprintf(ParEv1, "%8.8s", "PF_PROG");
	else if(AVC.User2[Cuba].EstadoPFCBA eq -1)
	  sprintf(ParEv1, "%8.8s", "PF_SUSP");
	else 
	  sprintf(ParEv1, "%8.8s", "PF_NPROG");
  }
  else
  {
    switch(TipoEa)
    {
	  case EA_LENTO:
		sprintf(ParEv1, "%8.8s", ScoreGetStr(TIPO_LENTO));
//		GeraEvento(INICIO_EA,Cuba,-1,ScoreGetStr(TIPO_LENTO));
		break;
	  case EA_RAPIDO:
		sprintf(ParEv1, "%8.8s", ScoreGetStr(TIPO_RAPIDO));
//		GeraEvento(INICIO_EA,Cuba,-1,ScoreGetStr(TIPO_RAPIDO));
		break;
	  case EA_MUITO_RAPIDO:
		sprintf(ParEv1, "%8.8s", ScoreGetStr(TIPO_MRAPID));
//		GeraEvento(INICIO_EA,Cuba,-1,ScoreGetStr(TIPO_MRAPID));
		break;
    }
  }

  if(AVC.ParUser2[Cuba].HabilitaPFCBA eq VERDADEIRO)
  {
    sprintf(ParEv5, "%5.2f", AVC.User2[Cuba].CoefAng*1.0e6);
  }
  else
  {
    if (AVC.Ea[Cuba].DerivHMaxPrevEa < 0.0)
	  sprintf(ParEv5, "-1.0");	// Para indicar que nao tem valor valido (nao detectou previsao)
    else
	  sprintf(ParEv5, "%5.2f", AVC.Ea[Cuba].DerivHMaxPrevEa*1.0e3);
  }
 
  GeraEvento(INICIO_EA,Cuba,-1, ParEv1, ParEv2, ParEv3, EaVMaxAnt, ParEv5);

  ComandaLampEa(Cuba,LIGAR);
  ComandaSirene(Cuba,LIGAR);


	if (AVC.Param[Cuba].TempoAtivaTEa eq 0 and AVC.ParUser1[Cuba].HabAEK eq FALSO)
	  EliminaEa(Cuba, TipoEa);

  AlteracaoTabela(TABELA_EST_AVC);	/*Informa que houve alteracao no EST_AVC */
  AlteracaoTabela(TABELA_AVC);	/*Informa que houve alteracao no AVC */
}

/*
--------------------------------------------------------------------------------
	ClassificaEa	-	Faz a classificacao do Efeito Anodico
--------------------------------------------------------------------------------
*/

int ClassificaEa(int Cuba)
{
  int		 TipoEa;

  if (AVC.Ea[Cuba].DerivHMaxPrevEa <= AVC.Param[Cuba].DerivHEaLento)
	TipoEa = EA_LENTO;
  else
	if(AVC.Ea[Cuba].DerivHMaxPrevEa > AVC.Param[Cuba].DerivHEaLento and
	  AVC.Ea[Cuba].DerivHMaxPrevEa <= AVC.Param[Cuba].DerivHEaRap )
		TipoEa = EA_RAPIDO;
	  else TipoEa = EA_MUITO_RAPIDO;

  return(TipoEa);
}

/*
--------------------------------------------------------------------------------
	EliminaEa	-	Envia tabela de eliminacao de Efeito Anodico
--------------------------------------------------------------------------------
*/

void EliminaEa(int Cuba, int TipoEa)
{
  int 				NumTabEliEa;

  if (EST_AVC(Cuba).ElimEaAtivo eq VERDADEIRO)
	return;
//  else
//	EST_AVC(Cuba).ElimEaAtivo = VERDADEIRO;

  if( EST_AVC(Cuba).AtivaTabEaAltern eq VERDADEIRO )	
    NumTabEliEa = AVC.Param[Cuba].NumTabEliEaAltern;
  else
  {
    switch(TipoEa)
    {
	  case EA_LENTO:
	    NumTabEliEa = AVC.Param[Cuba].NumTabEliEaLento;
	    break;
	  case EA_RAPIDO:
	    NumTabEliEa = AVC.Param[Cuba].NumTabEliEaRapido;
	    break;
	  case EA_MUITO_RAPIDO:
	    NumTabEliEa = AVC.Param[Cuba].NumTabEliEaMRapido;
	    break;
    }
  }
  StartTabEliminaEa(Cuba, NumTabEliEa);
}

/*
--------------------------------------------------------------------------------
	CalcDadosEa	-	Calcula parametros durante Efeito Anodico
--------------------------------------------------------------------------------
*/

void CalcDadosEa(int Cuba)
{
  AVC.Ea[Cuba].EaContL++;	
  AVC.Ea[Cuba].EaVAcumBruta += AVC.Cleit[Cuba].Vinst;
  AVC.Ea[Cuba].EaPotAcumBruta += AVC.Cleit[Cuba].Pinst;
  AVC.Ea[Cuba].EaVAcumLiq += (AVC.Cleit[Cuba].Vinst - AVC.Ccont[Cuba].VAlvo);
  AVC.Ea[Cuba].EaPotAcumLiq += ((AVC.Cleit[Cuba].Vinst - AVC.Ccont[Cuba].VAlvo) *
								AVC.Cleit[Cuba].Iinst);

  if (AVC.Cleit[Cuba].Vinst >= AVC.Param[Cuba].VEaXLim)
  	AVC.Ea[Cuba].EaContLXLim++;	

  if ((AVC.Param[Cuba].TempoAtivaTEa ne 0) and
	  ((HoraAtualSec - AVC.Ea[Cuba].EaHoraInicio) >= AVC.Param[Cuba].TempoAtivaTEa))
  {
	EliminaEa(Cuba, AVC.Ea[Cuba].EaClasse);
  }
}

/*
--------------------------------------------------------------------------------
	CalcVMaxMin	-	Calcula VMaxEa e VMinEa
--------------------------------------------------------------------------------
*/

void CalcVMaxMin(int Cuba)
{
  if (AVC.Cleit[Cuba].Vinst > AVC.Ea[Cuba].EaVMax)   /* Calculo da Tensao Maxima */
	AVC.Ea[Cuba].EaVMax = AVC.Cleit[Cuba].Vinst;
  if (AVC.Cleit[Cuba].Vinst < AVC.Ea[Cuba].EaVMin)   /* Calculo da Tensao Minima */
	AVC.Ea[Cuba].EaVMin = AVC.Cleit[Cuba].Vinst;
}

 #include	<process.h>
 #include	<sys/types.h>
 #include	<sys/qnx_glob.h>

 /*
 --------------------------------------------------------------------------------
	StartTabEliminaEa - Ativa tarefa para executar tabela de EA
 --------------------------------------------------------------------------------
 */
 void StartTabEliminaEa(int Cuba, int NumTabEa)
 {
   struct mens_eli
   {
	 int				cuba;
	 int				num_tab;
   } msg;
   pid_t	tid_elim;
   char  Par1[9];

   if ((AVL.LinhaHabilitada eq VERDADEIRO) and
	   (EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL) and
	   (AVC.Param[Cuba].HabEliminaEa eq VERDADEIRO) and
	   /* 08/07/02 - Inicio - Carlos */
	   (EST_AVC(Cuba).Est.HabElimEaOpe eq VERDADEIRO) and
	   /* 08/07/02 - Fim - Carlos */
	   (EST_AVC(Cuba).RtuStatus eq RTU_ON_LINE) and
	   ((EST_AVC(Cuba).ChaveLocRem eq REMOTO) and 
	   (EST_AVC(Cuba).ChaveAutMan eq AUTOMATICO)) and
	  ((HoraAtualSec-AVL.HoraDesativaLinha) > (AVL.TAtivaLinha * 60L)))
   {
	 if (EST_AVC(Cuba).ElimEaAtivo ne VERDADEIRO)
	 {
	   EST_AVC(Cuba).ElimEaAtivo = VERDADEIRO;
	   qnx_spawn_options.flags=_SPAWN_NOZOMBIE;
	   if ((tid_elim=spawnl(P_NOWAIT,"AePotTerm","AePotTerm",NULL)) eq -1)
		 EmiteAlarmeFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_ERR_9),COD_ERRO_33,"AePotTerm",errno);
	   else
	   {
		 msg.cuba=Cuba;
		 msg.num_tab= NumTabEa;
		 if (Send(tid_elim,&msg,NULL,sizeof(msg),0) eq -1)
		   EmiteAlarmeFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_ERR_8),COD_ERRO_31,
						  Cuba);
	   }
	 }
   }
   else
   {
	 if (EaNTerm[Cuba] ne VERDADEIRO)
	 {
	   EaNTerm[Cuba] = VERDADEIRO;
	   /*-- Novo --*/
	   EST_AVC(Cuba).ElimEaAtivo = VERDADEIRO;
	   NomeParEvento(Cuba, Par1);
       GeraEvento(TABELA_EA_NAO_ATIVADA, Cuba, -1, NumTabEa, Par1);
	 }
   }
 }

 /*
 -------------------------------------------------------------------------------
 NomeParEvento - Retornar o parametro de condicao do evento
 ------------------------------------------------------------------------------
 */
 void NomeParEvento(int Cuba, char *Nome)
 {
   strcpy(Nome, "--------");

   if (AVL.LinhaHabilitada ne VERDADEIRO)
   {
	 sprintf(Nome, "%8.8s", ScoreGetStr(SCORE_MSG_1988));
   }	 
   else
   {
	 if (EST_AVC(Cuba).EstadoCuba ne CUBA_NORMAL)
	 {
	   sprintf(Nome, "%8.8s", ScoreGetStr(SCORE_MSG_1990));
	 }
	 else
	 {
	   if (EST_AVC(Cuba).ForaLeitura eq VERDADEIRO)
	   {
		 sprintf(Nome, "%8.8s", ScoreGetStr(SCORE_MSG_1995));
	   }
	   else
	   {
		 if (AVC.Param[Cuba].HabEliminaEa ne VERDADEIRO)
		 {
		   sprintf(Nome, "%8.8s", ScoreGetStr(SCORE_MSG_1993));
		 }
		 else
		 {
		   if (EST_AVC(Cuba).RtuStatus ne RTU_ON_LINE)
		   {
			 sprintf(Nome, "%8.8s", ScoreGetStr(SCORE_MSG_1991));
		   }
		   else
		   {
			 /* 08/07/02 - Inicio - Carlos */
  			 if (EST_AVC(Cuba).Est.HabElimEaOpe ne VERDADEIRO)
			 {
			   sprintf(Nome, "%8.8s", ScoreGetStr(SCORE_MSG_2286));
			 }
			 /* 08/07/02 - Fim - Carlos */
			 else
			 {
			   if ( EST_AVC(Cuba).ChaveLocRem eq LOCAL ) 
			   {
				 sprintf(Nome, "%8.8s", ScoreGetStr(MAN_LOC));
			   } 
			   else 
			   {
				 /*-- Sinaliza cuba em Manual-Remoto. --*/
				 if ( EST_AVC(Cuba).ChaveAutMan eq MANUAL ) 
				 {
				   if (EST_AVC(Cuba).ManualControle)
				 	 sprintf(Nome, "%8.8s", ScoreGetStr(MAN_CTR));
				   else
					 sprintf(Nome, "%8.8s", ScoreGetStr(MAN_REM));
				 } 
				 else 
				 {
				   if ((HoraAtualSec-AVL.HoraDesativaLinha) <= (AVL.TAtivaLinha * 60L))
				   {
					 sprintf(Nome, "%8.8s", "TDesLin");
				   }
				   else
				   {
					 sprintf(Nome, "%8.8s", ScoreGetStr(SCORE_MSG_1994));
				   }
				 }
			   }
			 }
		   }
		 }
	   }
	 }
   }
 }

/*
--------------------------------------------------------------------------------
	IniSoproEspecial - Inicializa algoritmo de sopro especial
--------------------------------------------------------------------------------
*/
void AtivaSoproEspecial(int Cuba)
{
  int BaseTempo;
  
  BaseTempo = (int) (SAD_TICKS / Comum->BaseTempoMcp);
  AVC.User1[Cuba].ContCicSoproEspec = 0;	
  AVC.User1[Cuba].ContEsperaSoproEspec = AVL.Par.TIntervSoproEspec * BaseTempo;	
  AVC.User1[Cuba].EstadoSoproEspec = SOPRO_INICIAL;
  EST_AVC(Cuba).Est.OpeSoproEspec = FALSO;
}
/*
--------------------------------------------------------------------------------
	TrataSoproEspecial - Algoritmo de sopro especial
--------------------------------------------------------------------------------
*/
void TrataSoproEspecial(int Cuba)
{
  int BaseTempo;
  char Valor[9];
  float		VCicCont;

  BaseTempo = (int) (SAD_TICKS / Comum->BaseTempoMcp);
  if (EST_AVC(Cuba).Ea eq VERDADEIRO)
  {
	if (AVC.ParUser1[Cuba].HabSoproEspec eq VERDADEIRO)
	{
	  if (EST_AVC(Cuba).Est.OpeSoproEspec eq VERDADEIRO)
	  {
		  if (AVC.User1[Cuba].EstadoSoproEspec eq SOPRO_INICIAL)
		  {
			AVC.User1[Cuba].EstadoSoproEspec = SOPRO_EXECUCAO;
			GeraEvento(SOPRO_ESPECIAL,Cuba,-1,"Inicio", "Algorit");
		  }
		  if (AVC.User1[Cuba].EstadoSoproEspec eq SOPRO_EXECUCAO)
		  {
			if (AVC.Cleit[Cuba].Vinst > AVL.Par.VLimSoproEspec)
			{
			  AVC.User1[Cuba].ContCicSoproEspec = 1;
			  if (AVC.User1[Cuba].ContEsperaSoproEspec >= (int) (AVL.Par.TIntervSoproEspec * BaseTempo))
			  {
				// Comanda sopro
				if(AVC.Abs[Cuba].BitSopro ne 255)
				  ComandaSaidaRem(Cuba,LIGAR,AVC.Abs[Cuba].BitSopro,
								AVL.Par.DurAcionaSoproEspec*BASE_TEMPO_REMOTA);
				if (AVC.Abs[Cuba].BitSoprou eq 255)	/* Existe entrada de confirmacao de sopro? */
				{ /* Nao, gera evento de sopro comandado */
			#ifdef	BOOSTER_CORRENTE
				  VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba+
							 AVC.Param[Cuba].Bemf;
			#else
				  VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal+
							 AVC.Param[Cuba].Bemf;
			#endif
				  GeraEvento(SOPROU,Cuba,-1, "Automat","Comando",VCicCont,AVC.Cleit[Cuba].Vinst,AVC.Ccont[Cuba].VAlvo);
				}
				/** Depuracao **/
				sprintf(Valor, "%d", AVC.User1[Cuba].ContEsperaSoproEspec);
//				GeraEvento(SOPRO_ESPECIAL,Cuba,-1,"Comanda", Valor);
				AVC.User1[Cuba].ContEsperaSoproEspec = 1;
			  }
			  else
				AVC.User1[Cuba].ContEsperaSoproEspec++;
			}
			else
			{
			  AVC.User1[Cuba].ContEsperaSoproEspec++;
			  if (AVC.User1[Cuba].ContCicSoproEspec >= (int)(AVL.Par.TLimSoproEspec * 60 * BaseTempo))
			  {
				if (AVC.User1[Cuba].EstadoSoproEspec eq SOPRO_EXECUCAO)
				{
				  AVC.User1[Cuba].EstadoSoproEspec = SOPRO_FIM_TEMPO;
				  GeraEvento(SOPRO_ESPECIAL,Cuba,-1,"Fim", "Tempo");
				  EST_AVC(Cuba).Est.OpeSoproEspec = FALSO;
		  		}
			  }
			  else
			    AVC.User1[Cuba].ContCicSoproEspec++;	
			}
		  }
	  }
	  else
	  {
		if (AVC.User1[Cuba].EstadoSoproEspec eq SOPRO_EXECUCAO)
		{
		  AVC.User1[Cuba].EstadoSoproEspec = SOPRO_FIM_OPERADOR;
		  GeraEvento(SOPRO_ESPECIAL,Cuba,-1,"Fim", "Operador");
		  EST_AVC(Cuba).Est.OpeSoproEspec = FALSO;
		}
	  }
	}
	else
	{
	  if (AVC.User1[Cuba].EstadoSoproEspec eq SOPRO_EXECUCAO)
	  {
		AVC.User1[Cuba].EstadoSoproEspec = SOPRO_FIM_DESAB;
		GeraEvento(SOPRO_ESPECIAL,Cuba,-1,"Fim", "Desab");
		EST_AVC(Cuba).Est.OpeSoproEspec = FALSO;
	  }
	}
  }
}


/*
--------------------------------------------------------------------------------
AEK - Logica alternativa de eliminacao de EA
--------------------------------------------------------------------------------
*/
void AEK(int Cuba)
{

  float	VAlvo,VCicCont,VInst;
  int DurInt, i;

  if ((AVL.LinhaHabilitada eq VERDADEIRO) and
	   (EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL) and
	   (EST_AVC(Cuba).Est.HabElimEaOpe eq VERDADEIRO) and
	   (EST_AVC(Cuba).RtuStatus eq RTU_ON_LINE) and
	   ((EST_AVC(Cuba).ChaveLocRem eq REMOTO) and 
	   (EST_AVC(Cuba).ChaveAutMan eq AUTOMATICO)) and
	  ((HoraAtualSec-AVL.HoraDesativaLinha) > (AVL.TAtivaLinha * 60L)))
  {
	
	if ( HoraAtualSec < (AVC.Ea[Cuba].EaHoraInicio + ((EaLocal[Cuba].ContSobe+1) * AVC.ParUser1[Cuba].AEK_TEspera)))
	{
	  if (AVC.Cleit[Cuba].Vinst > EaLocal[Cuba].AEK_VMax)
	  {
		EaLocal[Cuba].AEK_VMax = AVC.Cleit[Cuba].Vinst;
		AVC.User1[Cuba].AEKVMax = EaLocal[Cuba].AEK_VMax;

		if (EaLocal[Cuba].ContSobe eq 0) 
		  EaLocal[Cuba].AEK_VMaxIni = EaLocal[Cuba].AEK_VMax;
	  }


	  if (EaLocal[Cuba].ContSobe eq 0)
	  {
 		EaLocal[Cuba].NLeitEa++;
		EaLocal[Cuba].EaMed = ((EaLocal[Cuba].EaMed * (EaLocal[Cuba].NLeitEa - 1)) + 
								AVC.Cleit[Cuba].Vinst) / EaLocal[Cuba].NLeitEa;
		EaLocal[Cuba].LeitEa_vet[EaLocal[Cuba].NLeitEa-1] = AVC.Cleit[Cuba].Vinst;
	  }
	} 
	else
	{
	  if (EaLocal[Cuba].AEK_VMax < AVC.Param[Cuba].VEaFraco and 
			EaLocal[Cuba].ContSobe < AVC.ParUser1[Cuba].AEK_MaxMoveCima and
			EST_AVC(Cuba).Est.FimAEK eq FALSO and EaLocal[Cuba].FimMoveAEK eq FALSO)
	  {
		/*	 MOVE ANODO PARA CIMA */

		DurInt=(int)(AVC.ParUser1[Cuba].AEK_TMoveCima*BASE_TEMPO_REMOTA);

		if (MoveAnodo(Cuba,DurInt,SUBIR_ANODO) eq STATUS_OK)
		{

      	  VInst=AVC.Cleit[Cuba].Vinst;
#ifdef	BOOSTER_CORRENTE
      	  VAlvo=AVC.Ccont[Cuba].RAlvo * AVC.Ccont[Cuba].INominalCuba + AVC.Param[Cuba].Bemf;
          VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba+
  			 AVC.Param[Cuba].Bemf;
#else
          VAlvo=AVC.Ccont[Cuba].RAlvo * AVL.INominal + AVC.Param[Cuba].Bemf;
          VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal+
  			 AVC.Param[Cuba].Bemf;
#endif

		  GeraEvento(SUBIDA_AUT_ANODO,Cuba,-1,"AEK",
			(float)DurInt/(float)BASE_TEMPO_REMOTA,VCicCont,VInst,VAlvo);

		  EaLocal[Cuba].ContSobe++;

		  EST_AVC(Cuba).EfeitoMove=VERDADEIRO;
	 	  EST_AVC(Cuba).EsperaConfMove=FALSO;
		  AVC.Ccont[Cuba].HoraUltMove=HoraAtualSec;

		}
	  }
	  else
	  {
		/*   FINALIZA AEK */
		if (EST_AVC(Cuba).Est.FimAEK eq FALSO and 
			AVC.ParUser1[Cuba].AEK_ForcaSubidas eq VERDADEIRO)
		{
			/* GERA EVENTO AEK */
 
		  for (i = 0; i < EaLocal[Cuba].NLeitEa; i++)
		  {
			EaLocal[Cuba].EaDesvPad += pow((EaLocal[Cuba].LeitEa_vet[i] - EaLocal[Cuba].EaMed), 2);
		  }

		  EaLocal[Cuba].EaDesvPad = sqrt(EaLocal[Cuba].EaDesvPad / EaLocal[Cuba].NLeitEa);

		  GeraEvento(EV_AEK,Cuba,-1,"Forca", EaLocal[Cuba].AEK_VMaxIni, 
				EaLocal[Cuba].AEK_VMax, EaLocal[Cuba].ContSobe, 
					EaLocal[Cuba].EaDesvPad);

		  EST_AVC(Cuba).Est.FimAEK = VERDADEIRO;

		  if(EaLocal[Cuba].ContSobe >= AVC.ParUser1[Cuba].AEK_MaxMoveCima)
		  {
		    EST_AVC(Cuba).Est.ForcaAEK = VERDADEIRO;
		    EST_AVC(Cuba).Est.ForcaDesceAEK = VERDADEIRO;	
		  }

		}


		if(EaLocal[Cuba].ContSobe < AVC.ParUser1[Cuba].AEK_MaxMoveCima and
			AVC.ParUser1[Cuba].AEK_ForcaSubidas eq VERDADEIRO and
			EST_AVC(Cuba).Est.FimAEK eq VERDADEIRO and EaLocal[Cuba].FimMoveAEK eq FALSO and
			HoraAtualSec > (AVC.Ea[Cuba].EaHoraInicio + ((EaLocal[Cuba].ContSobe+1) * AVC.ParUser1[Cuba].AEK_TEspera) + AVC.ParUser1[Cuba].AEK_TParar))
		{
			/*	 MOVE ANODO PARA CIMA */

		  DurInt=(int)(AVC.ParUser1[Cuba].AEK_TMoveCima*BASE_TEMPO_REMOTA);

  		  if (MoveAnodo(Cuba,DurInt,SUBIR_ANODO) eq STATUS_OK)
		  {

      	    VInst=AVC.Cleit[Cuba].Vinst;
#ifdef	BOOSTER_CORRENTE
      	    VAlvo=AVC.Ccont[Cuba].RAlvo * AVC.Ccont[Cuba].INominalCuba + AVC.Param[Cuba].Bemf;
            VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba+
  			   AVC.Param[Cuba].Bemf;
#else
            VAlvo=AVC.Ccont[Cuba].RAlvo * AVL.INominal + AVC.Param[Cuba].Bemf;
            VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal+
  			   AVC.Param[Cuba].Bemf;
#endif

		    GeraEvento(SUBIDA_AUT_ANODO,Cuba,-1,"AEK_F",
			  (float)DurInt/(float)BASE_TEMPO_REMOTA,VCicCont,VInst,VAlvo);

		    EaLocal[Cuba].ContSobe++;

		    EST_AVC(Cuba).EfeitoMove=VERDADEIRO;
	 	    EST_AVC(Cuba).EsperaConfMove=FALSO;
		    AVC.Ccont[Cuba].HoraUltMove=HoraAtualSec;

			if(EaLocal[Cuba].ContSobe >= AVC.ParUser1[Cuba].AEK_MaxMoveCima)
			{
			  if(AVC.ParUser1[Cuba].AEK_InibeTerminal eq FALSO)
				EST_AVC(Cuba).Est.AEK = FALSO;
			  EST_AVC(Cuba).Est.ForcaAEK = VERDADEIRO;
			  EST_AVC(Cuba).Est.ForcaDesceAEK = VERDADEIRO;

			}
		  }
		} 

		if(AVC.ParUser1[Cuba].AEK_ForcaSubidas eq VERDADEIRO and
			EST_AVC(Cuba).Est.ForcaDesceAEK eq VERDADEIRO and EaLocal[Cuba].FimMoveAEK eq FALSO and
			HoraAtualSec > (AVC.Ea[Cuba].EaHoraInicio + ((EaLocal[Cuba].ContSobe+1) * AVC.ParUser1[Cuba].AEK_TEspera) + AVC.ParUser1[Cuba].TForcaDesce))
		{
		  DurInt=(int)(AVC.ParUser1[Cuba].AEK_TFMoveBaixo*BASE_TEMPO_REMOTA);
		  
		  if (MoveAnodo(Cuba,DurInt,DESCER_ANODO) eq STATUS_OK)
		  {
      	    VInst=AVC.Cleit[Cuba].Vinst;
#ifdef	BOOSTER_CORRENTE
      	    VAlvo=AVC.Ccont[Cuba].RAlvo * AVC.Ccont[Cuba].INominalCuba + AVC.Param[Cuba].Bemf;
            VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba+
  			    AVC.Param[Cuba].Bemf;
#else
            VAlvo=AVC.Ccont[Cuba].RAlvo * AVL.INominal + AVC.Param[Cuba].Bemf;
            VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal+
  		  	     AVC.Param[Cuba].Bemf;
#endif

		    GeraEvento(DESCIDA_AUT_ANODO,Cuba,-1,"AEK_F",
			    (float)DurInt/(float)BASE_TEMPO_REMOTA,VCicCont,VInst,VAlvo);


		    EST_AVC(Cuba).EfeitoMove=VERDADEIRO;
	 	    EST_AVC(Cuba).EsperaConfMove=FALSO;
		    AVC.Ccont[Cuba].HoraUltMove=HoraAtualSec;
		    EST_AVC(Cuba).Est.ForcaDesceAEK = FALSO;
		  }
		  else
	  	  {
		    EST_AVC(Cuba).Est.ForcaDesceAEK = FALSO;
		  }
		}


		if(AVC.ParUser1[Cuba].AEK_ForcaSubidas eq VERDADEIRO and
			EST_AVC(Cuba).Est.ForcaAEK eq VERDADEIRO and EaLocal[Cuba].FimMoveAEK eq FALSO and
			HoraAtualSec > (AVC.Ea[Cuba].EaHoraInicio + ((EaLocal[Cuba].ContSobe+1) * AVC.ParUser1[Cuba].AEK_TEspera) + AVC.ParUser1[Cuba].TForcaDesce + AVC.ParUser1[Cuba].TVerTensao))
		{
		  if((AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal + AVC.Param[Cuba].Bemf) > AVC.ParUser1[Cuba].VForcaDesce)
		  {
		    DurInt=(int)(AVC.ParUser1[Cuba].AEK_TFMoveBaixo*BASE_TEMPO_REMOTA);
		  
		    if (MoveAnodo(Cuba,DurInt,DESCER_ANODO) eq STATUS_OK)
		    {
      	      VInst=AVC.Cleit[Cuba].Vinst;
#ifdef	BOOSTER_CORRENTE
      	      VAlvo=AVC.Ccont[Cuba].RAlvo * AVC.Ccont[Cuba].INominalCuba + AVC.Param[Cuba].Bemf;
              VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba+
  			    AVC.Param[Cuba].Bemf;
#else
              VAlvo=AVC.Ccont[Cuba].RAlvo * AVL.INominal + AVC.Param[Cuba].Bemf;
              VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal+
  		  	     AVC.Param[Cuba].Bemf;
#endif

		      GeraEvento(DESCIDA_AUT_ANODO,Cuba,-1,"AEK_F",
			    (float)DurInt/(float)BASE_TEMPO_REMOTA,VCicCont,VInst,VAlvo);

			  EaLocal[Cuba].FimMoveAEK = VERDADEIRO;

		  	  EST_AVC(Cuba).EfeitoMove=VERDADEIRO;
	 	  	  EST_AVC(Cuba).EsperaConfMove=FALSO;
		      AVC.Ccont[Cuba].HoraUltMove=HoraAtualSec;
			  EST_AVC(Cuba).Est.ForcaAEK = FALSO;
			}
			else
			{
			  EST_AVC(Cuba).Est.ForcaAEK = FALSO;
			  EaLocal[Cuba].FimMoveAEK = VERDADEIRO;
			}
		  }
		}

		if (EaLocal[Cuba].ContSobe > 0 and EST_AVC(Cuba).Est.FimAEK eq FALSO and
			EaLocal[Cuba].FimMoveAEK eq FALSO and
			AVC.ParUser1[Cuba].AEK_ForcaSubidas eq FALSO)
		{
		  if (HoraAtualSec > (AVC.Ea[Cuba].EaHoraInicio + ((EaLocal[Cuba].ContSobe+1) * AVC.ParUser1[Cuba].AEK_TEspera) + AVC.ParUser1[Cuba].AEK_TParar))
		  {
		    DurInt=(int)(AVC.ParUser1[Cuba].AEK_TMoveBaixo*BASE_TEMPO_REMOTA);
		  
		    if (MoveAnodo(Cuba,DurInt,DESCER_ANODO) eq STATUS_OK)
		    {
      	      VInst=AVC.Cleit[Cuba].Vinst;
#ifdef	BOOSTER_CORRENTE
      	      VAlvo=AVC.Ccont[Cuba].RAlvo * AVC.Ccont[Cuba].INominalCuba + AVC.Param[Cuba].Bemf;
              VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba+
  			     AVC.Param[Cuba].Bemf;
#else
              VAlvo=AVC.Ccont[Cuba].RAlvo * AVL.INominal + AVC.Param[Cuba].Bemf;
              VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal+
  		  	     AVC.Param[Cuba].Bemf;
#endif

		      GeraEvento(DESCIDA_AUT_ANODO,Cuba,-1,"AEK",
			    (float)DurInt/(float)BASE_TEMPO_REMOTA,VCicCont,VInst,VAlvo);

			  EaLocal[Cuba].FimMoveAEK = VERDADEIRO;

		  	  EST_AVC(Cuba).EfeitoMove=VERDADEIRO;
	 	  	  EST_AVC(Cuba).EsperaConfMove=FALSO;
		      AVC.Ccont[Cuba].HoraUltMove=HoraAtualSec;
		    }
		  }
	    }
		else if (EST_AVC(Cuba).Est.FimAEK eq FALSO and 
			AVC.ParUser1[Cuba].AEK_ForcaSubidas eq FALSO)
		{
			/* GERA EVENTO E ENCERRA AEK */
 
		  for (i = 0; i < EaLocal[Cuba].NLeitEa; i++)
		  {
			EaLocal[Cuba].EaDesvPad += pow((EaLocal[Cuba].LeitEa_vet[i] - EaLocal[Cuba].EaMed), 2);
		  }

		  EaLocal[Cuba].EaDesvPad = sqrt(EaLocal[Cuba].EaDesvPad / EaLocal[Cuba].NLeitEa);
		  EaLocal[Cuba].HoraFimAEK = HoraAtualSec;

		  GeraEvento(EV_AEK,Cuba,-1,"Fim", EaLocal[Cuba].AEK_VMaxIni, 
				EaLocal[Cuba].AEK_VMax, EaLocal[Cuba].ContSobe, 
					EaLocal[Cuba].EaDesvPad);

		  EST_AVC(Cuba).Est.FimAEK = VERDADEIRO;
		  if(AVC.ParUser1[Cuba].AEK_InibeTerminal eq FALSO)
  		    EST_AVC(Cuba).Est.AEK = FALSO;
		}
	  }
	}
	if(AVC.ParUser2[Cuba].HabAEKPF eq VERDADEIRO)
	{
	  if(EaLocal[Cuba].HoraFimAEK > AVC.Ea[Cuba].EaHoraInicio)
	  {
		if(HoraAtualSec > (EaLocal[Cuba].HoraFimAEK + AVC.ParUser2[Cuba].IntMovCimaAEKPF) and
			EaLocal[Cuba].DeltaTempo <= AVC.ParUser2[Cuba].MaxDeltaTBaixo and
			AVC.Cleit[Cuba].Vinst >= AVC.Param[Cuba].EaVoltLim) 
		{
		  if(EaLocal[Cuba].ContMovCimaAEKPF <= EaLocal[Cuba].ContMovBaixoAEKPF)
		  {
			if(HoraAtualSec > (EaLocal[Cuba].HoraUltMovAEKPF+AVC.ParUser2[Cuba].IntMovCimaAEKPF))
			{
			  /* EFETUA MOVIMENTACAO PARA CIMA */
		      DurInt=(int)(AVC.ParUser2[Cuba].TMovCimaAEKPF*BASE_TEMPO_REMOTA);
		  
		      if (MoveAnodo(Cuba,DurInt,SUBIR_ANODO) eq STATUS_OK)
		      {
      	        VInst=AVC.Cleit[Cuba].Vinst;
#ifdef	BOOSTER_CORRENTE
      	        VAlvo=AVC.Ccont[Cuba].RAlvo * AVC.Ccont[Cuba].INominalCuba + AVC.Param[Cuba].Bemf;
                VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba+
  			       AVC.Param[Cuba].Bemf;
#else
                VAlvo=AVC.Ccont[Cuba].RAlvo * AVL.INominal + AVC.Param[Cuba].Bemf;
                VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal+
  		  	       AVC.Param[Cuba].Bemf;
#endif

		        GeraEvento(SUBIDA_AUT_ANODO,Cuba,-1,"AEKPF",
			      (float)DurInt/(float)BASE_TEMPO_REMOTA,VCicCont,VInst,VAlvo);

		  	    EST_AVC(Cuba).EfeitoMove=VERDADEIRO;
	 	  	    EST_AVC(Cuba).EsperaConfMove=FALSO;
		        AVC.Ccont[Cuba].HoraUltMove=HoraAtualSec;
			    EaLocal[Cuba].HoraUltMovAEKPF = HoraAtualSec;
			    EaLocal[Cuba].ContMovCimaAEKPF++;
				EaLocal[Cuba].DeltaTempo -= AVC.ParUser2[Cuba].TMovCimaAEKPF; 
		      }
			}
		  }
		  else
		  {
			if(HoraAtualSec > (EaLocal[Cuba].HoraUltMovAEKPF+AVC.ParUser2[Cuba].IntMovBaixoAEKPF))
			{
			  /* EFETUA MOVIMENTACAO PARA BAIXO */
		      DurInt=(int)(AVC.ParUser2[Cuba].TMovBaixoAEKPF*BASE_TEMPO_REMOTA);
		  
		      if (MoveAnodo(Cuba,DurInt,DESCER_ANODO) eq STATUS_OK)
		      {
      	        VInst=AVC.Cleit[Cuba].Vinst;
#ifdef	BOOSTER_CORRENTE
      	        VAlvo=AVC.Ccont[Cuba].RAlvo * AVC.Ccont[Cuba].INominalCuba + AVC.Param[Cuba].Bemf;
                VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba+
  			       AVC.Param[Cuba].Bemf;
#else
                VAlvo=AVC.Ccont[Cuba].RAlvo * AVL.INominal + AVC.Param[Cuba].Bemf;
                VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal+
  		  	       AVC.Param[Cuba].Bemf;
#endif

		        GeraEvento(DESCIDA_AUT_ANODO,Cuba,-1,"AEKPF",
			      (float)DurInt/(float)BASE_TEMPO_REMOTA,VCicCont,VInst,VAlvo);

		  	    EST_AVC(Cuba).EfeitoMove=VERDADEIRO;
	 	  	    EST_AVC(Cuba).EsperaConfMove=FALSO;
		        AVC.Ccont[Cuba].HoraUltMove=HoraAtualSec;
			    EaLocal[Cuba].HoraUltMovAEKPF = HoraAtualSec;
			    EaLocal[Cuba].ContMovBaixoAEKPF++;
				EaLocal[Cuba].DeltaTempo += AVC.ParUser2[Cuba].TMovBaixoAEKPF; 
		      }
			}
		  }
		} 
	  }
	}
  }
  else
  {
    EST_AVC(Cuba).Est.FimAEK = VERDADEIRO;
    EST_AVC(Cuba).Est.AEK = FALSO;
  }
} 