/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: SCORE

	SISTEMA		: TODOS QUE USEM O ALGORITMO DE CONTROLE DO SCORE (CBA etc)

	ARQUIVO		: MccSuperv.c

	CONTEUDO	: Funcao encarregada da parte de  supervisao  do
                  Modulo de Controle das Cubas - MCCScore
                  Modulo encarregado de fazer os calculos para relatorios  de
                  supervisao.  E'  ativada  pelo modulo de controle das cubas
                  (MCCScore).
                  Utiliza os dados basicos gerados pelo modulo MCP (Modulo de
                  Calculos Primarios) e de outros parametros relacionados com
                  a configuracao e o status das cubas e da linha.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 2.0		  -		  DATA  : 27/02/97

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
11/01/93 | Retirada inicializacao dos valores de supervisao do    | Leonel
         | codigo. A inicializacao sera feita pelo programa de    |       
         | partida.                                               |       
-------------------------------------------------------------------------------
19/01/93 | Retirada da contabilizacao de movimentacoes deste mo-  | Leonel
         | dulo para que a mesma so seja feita quando confirma-   |       
         | da (modulo RecChaves).                                 |       
-------------------------------------------------------------------------------
11/05/93 | Acrescentados os procedimentos para geracao das va-    | Leonel
         | riaveis para o relatorio historico de ruido e  para    |       
         | o relatorio historico resumo da linha.                 |       
-------------------------------------------------------------------------------
21/07/93 | Efetua calculos de duracao, tensao, ruido etc, ape-    | Leonel
         | nas para cubas normais (antes era para normal e par-   |       
         | tida).                                                 |       
-------------------------------------------------------------------------------
05/07/94 | Edicao inicial de migracao para o QNX 4.2			  | Leonel
-------------------------------------------------------------------------------
20/09/94 | Inclusao contabilizacao de variaveis de turno		  | Leonel
-------------------------------------------------------------------------------
21/09/94 | Incluida habilitacao de excessao por divisao por zero  | Leonel
-------------------------------------------------------------------------------
01/12/94 | Inclusao contabilizacao de variaveis de incremento do  | Carlos
		 | relatorio diario e de turno							  |
-------------------------------------------------------------------------------
13/12/94 | Inclusao tratamento de VErro e VAlvo para cuba fora de | Carlos
         | leitura ou com estado diferente de normal.             |
-------------------------------------------------------------------------------
16/12/94 | Inicializacao de  contadores de inicio de previsao  no | Carlos
         | fechamento do dia e turno                              |
-------------------------------------------------------------------------------
23/03/95 | Correcao da contabilizacao de troca de pinos           | Carlos
-------------------------------------------------------------------------------
08/06/95 | Contabilizacao de ruido independente do tratamento     | Carlos
-------------------------------------------------------------------------------
23/07/95 | Colocada tolerancia de 1 minuto alem do  intervalo  do | Carlos
         | ciclo de controle para tratamento de mudanca de dia    |
-------------------------------------------------------------------------------
10/08/95 | Alterada contabilizacao de tempo e inc. de corrida e   | Leonel
         | quebrada para so considerar quando incremento <> 0     |
-------------------------------------------------------------------------------
12/09/95 | Alterada contabilizacao de tempo  e  inc. de corrida e | Leonel
         | quebrada para ficar igual ao calculo de inc. total     |
-------------------------------------------------------------------------------
08/11/95 | Alterado calculo do incremento total para ter como base| Leonel
         | o dia ao inves do tempo em que esteve em incremento.   |
-------------------------------------------------------------------------------
06/01/96 | Substituido teste de EaPrev por EaPrevVirada na conta- | Carlos
         | bilizacao de previsao no fechamento de dia/turno       |
-------------------------------------------------------------------------------
13/03/96 | Incluido calculo de incremento de usuario              | Carlos
-------------------------------------------------------------------------------
18/02/97 | Incluida sinalizacao de AtrasoEa p/ Rel. Ctrl Proc.    | Carlos
-------------------------------------------------------------------------------
21/02/97 | Substituida tabela Param por  Ccont  para variaveis    | Carlos
         | VSetPoint e Banda*Atual                                |
-------------------------------------------------------------------------------
27/02/97 | Edicao inicial da Versao 2. Separacao do Algoritmo do  | Leonel
         | Score do kernel (MCC).                                 |
-------------------------------------------------------------------------------
01/09/98 | Alterado para nao contabilizar ruido quando o mesmo    | Leonel
         | estiver desabilitado na configuracao                   |
-------------------------------------------------------------------------------
25/08/00 | Correcao do calculo de VCicContlBruta no evento de su- | Carlos
         | pervisao especial (LIGADA/DESLIG. => sem acresc. bemf) |
-------------------------------------------------------------------------------
06/02/03 | Comparacao com as outras correntes das AtnCas (Cba     | Leonel
         | reducao 125ka)                                         |
-------------------------------------------------------------------------------
$Id: MccSuperv.c,v 1.1.2.1 2012/09/28 17:09:27 leo Exp $

$Log: MccSuperv.c,v $
Revision 1.1.2.1  2012/09/28 17:09:27  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

Revision 1.5  2008/07/08 13:28:07  leo
Incluidos novos limites para ruido. De 2 niveis para 5. Os 3 primeiros niveis
sao tratados como FRACO e os 2 ultimos como FORTE na contabilizacao historica.

Revision 1.4  2007/09/28 14:46:25  rogerio
Alteracao para incluir sala I com atn8

Revision 1.3  2004/05/11 14:30:54  leo
Incluido log de alteracao de parametros de calibracao (offset e ganho) para
os canais da atn8. Gerado arquivo csv no diretorio log para analise posterior
pela Atan.

Revision 1.2  2004/04/08 19:21:14  leo
Inclusao da sala 125 kA VI.

******************************************************************************/
/*
-------------------------------------------------------------------------------
                           Definicao de compilacao condicional
-------------------------------------------------------------------------------
*/
/*** #define		ATIVA_DEPURACAO ***/

/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include	<MccCba.h>
#include	<Eventos.h>
#include	<Prototipos.h>
#include	<UserDrvsad.h>
#include	<time.h>
#include	<sys/kernel.h>
#include	<string.h>
#include	<stdlib.h>
#include	<stddef.h>
#include	<math.h>
#include	<stdio.h>
#include	<signal.h>
#include	<setjmp.h>
#include	<float.h>


/*
-------------------------------------------------------------------------------
                           Variaveis Globais
-------------------------------------------------------------------------------
*/
/* -- Apontadores para as tabelas comuns -- */
#include	<VarsComum.h>

/*
-------------------------------------------------------------------------------
                           Variaveis Locais
-------------------------------------------------------------------------------
*/
/* Intervalo do ciclo de controle em segundos */
int		IntervCicContSeg;
  /* copia local da tabela descr_conv para verificar se houve alteracao de
     parametros */
  t_descr_conv	LocalDescrConv;
  t_descr_conv  *PDConv;

/*
-------------------------------------------------------------------------------
                           Prototipos
-------------------------------------------------------------------------------
*/
void IniMccSupCuba(int Cuba);
void TrataVarsRelInst(void);
void CalcMediasLinha(void);
void CalcMediasCubas(void);
void SupervEspecial(int Cuba);
void CalcEa(int Cuba);
void CalcVDesvForaCont(int Cuba);
void CalcDuracoes(int Cuba);
void CalcResTensDia(int Cuba);
void CalcPotEnerDia(int Cuba);
void CalcRuido(int Cuba);
void CalcIncrementos(int Cuba);
void CalcHistLinha(void);
void LogAltConv(int aCuba, char *apNome, int aIndNome, float aValNovo, float aValVelho);
void IniLogConvAtn8(void);
void TrataLogConvAtn8(void);

/*
-------------------------------------------------------------------------------
	MccSupervisao - Funcao de calculos de supervisao do modulo MccCba
-------------------------------------------------------------------------------
*/
void MccSuperv(void)
{
  int CubaOpe, Cuba;
  static int LinhaControlada=VERDADEIRO;

  /* -- Posicao para caso de f.p. exception -- */
  PosicaoGlobal=41;

  DEPURA(printf("MccSuperv-> TrataVarsRelInst");)
  TrataVarsRelInst();
  /*-- CL01 - Upgrade Red II para ATN8 --*/
  if ((Comum->IdentReducao >= 6) or (Comum->IdentReducao <= 2))
  { /* sala 86ka, 125ka 5 e 6 - atn8 */
    DEPURA(printf("MccSuperv-> TrataLogConvAtn8");)
    TrataLogConvAtn8();
  }

  PosicaoGlobal=42;

  /* -- Tratamento de excessao de ponto flutuante -- */
  CubaGlobal=-1;
  if (sigsetjmp(MccEnvBuf,1))
  { /* -- Ocorreu alguma excessao -- */
	/* -- Retira linha e todas as cubas do controle -- */
	if (CubaGlobal eq -1)
	{
	  LinhaControlada=FALSO;
	  for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
	  {
		Cuba=ConvCubOperScore(CubaOpe);
		if (Cuba eq -1)
		  continue;
		EST_AVC(Cuba).ForaControle=VERDADEIRO;
		EmiteAlarmeFor(TODOS_DISPOSITIVOS,MsgException);
		EmiteAlarmeFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_MSG_252));
	  }
	}
	LiberaSemaf(SEMAF_AVL);
  }
  PosicaoGlobal=43;

  if (LinhaControlada)
  {
    /* -- Aloca semaforos para acesso as tabelas de globais -- */
    AlocaSemaf(SEMAF_AVL);
	CubaGlobal=-1;
	/* -- Calcula valores medios relativos a linha -- */
	CalcMediasLinha();
    PosicaoGlobal=44;

	if (AVL.LinhaHabilitada eq VERDADEIRO)
	{
	  /* -- incrementa contador de ativacoes do controle com linha habilitada -- */
	  AVL.NCicContDia += 1;
	  AVL_TURNO.NCicContDia += 1;

	  AlocaSemaf(SEMAF_SUPERV_AVC);
	  AlocaSemaf(SEMAF_HIST_TURNO);
	  /* -- Calcula valores medios relativos as cubas -- */
      DEPURA(printf(" CalcMediasCubas");)
	  CalcMediasCubas();
	  LiberaSemaf(SEMAF_HIST_TURNO);
	  LiberaSemaf(SEMAF_SUPERV_AVC);
  	  PosicaoGlobal=45;
	}
	/* -- Libera semaforos -- */
	DEPURA(printf(" Fim\n");)
	LiberaSemaf(SEMAF_AVL);
  }
}

/*
-------------------------------------------------------------------------------
		Funcoes
-------------------------------------------------------------------------------
*/

/*
--------------------------------------------------------------------------------
| IniMccSupervisao - Inicializa as variaveis necessarias na partida            |
--------------------------------------------------------------------------------
*/
void IniMccSupervisao(void)
{
	int Cuba, CubaOpe;

	/* Intervalo de ciclo de controle em segundos */
	IntervCicContSeg=IntervCicCont*60;

	/* -- Posicao para caso de f.p. exception -- */
	PosicaoGlobal=46;

	AVL.IAlvo=AVL.INominal;

	/*-- CL01 - Upgrade Red II para ATN8 --*/
	if ((Comum->IdentReducao >= 6) or (Comum->IdentReducao  <= 2))
	{ /* sala 86ka, 125ka 5 e 6 - atn8 */
		IniLogConvAtn8();
	}

	/*-- Inicializa as variaveis para o relatorio instantaneo de cubas --*/
	AlocaSemaf(SEMAF_AVC);
	for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
	{
		Cuba=ConvCubOperScore(CubaOpe);
		if (Cuba eq -1)
			continue;
		IniMccSupCuba(Cuba);
	}
	LiberaSemaf(SEMAF_AVC);

}

/*
--------------------------------------------------------------------------------
| IniMccSupCuba - Inicializa as variaveis necessarias da cuba                  |
--------------------------------------------------------------------------------
*/
void IniMccSupCuba(int Cuba)
{
	PosicaoGlobal=47;

	AVC.Ccont[Cuba].VAlvo = 0.0;
	AVC.Ccont[Cuba].VErro = 0.0;

	/* -- alteracao - inicio - 21/10/02 - Leonel - Inclusao evento temperatura Atn8 -- */
	EST_AVC(Cuba).Atn8TempAlta=FALSO;
	/* -- alteracao - fim - 21/10/02 - Leonel - Inclusao evento temperatura Atn8 -- */
}

/*
--------------------------------------------------------------------------------
| TrataVarsRelInst - Trata as variaveis do relatorio instantaneo de cubas    |
--------------------------------------------------------------------------------
*/
void TrataVarsRelInst(void)
{
  int Cuba, CubaOpe;

  PosicaoGlobal=48;

  AlocaSemaf(SEMAF_AVC);
  for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
  {
	Cuba=ConvCubOperScore(CubaOpe);
	if (Cuba eq -1)
	  continue;

	/* Verifica se alterou numero do algoritmo da cuba on-line */
	if (AlterouNumAlgCtr(Cuba, ALG_SCORE01))
	{ /* -- selecionou ou desselecionou algoritmo do Score -- */
	  /* -- Inicializa variaveis do algoritmo do Score -- */
	  IniMccSupCuba(Cuba);
	}
	if (AlgControle(Cuba,ALG_SCORE01) eq VERDADEIRO)
	{
  	  PosicaoGlobal=49;

	  if ((EST_AVC(Cuba).ForaLeitura eq FALSO) and
		(EST_AVC(Cuba).ForaControle eq FALSO) and
		(AVL.LinhaHabilitada eq VERDADEIRO) and
		(EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL))
	  {
		/* Inicio Alteracao - Carlos - 23/06/99 */
		/* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
		/*-- Calcula tensao alvo e erro --*/
		AVC.Ccont[Cuba].VAlvo = AVC.Ccont[Cuba].RAlvo * AVC.Ccont[Cuba].INominalCuba +
							  AVC.Param[Cuba].Bemf;
		AVC.Ccont[Cuba].VErro = (EST_AVC(Cuba).Ea eq VERDADEIRO)? 0.0 :
							  AVC.Ccont[Cuba].Rerro * AVC.Ccont[Cuba].INominalCuba;
#else
		/*-- Calcula tensao alvo e erro --*/
		AVC.Ccont[Cuba].VAlvo = AVC.Ccont[Cuba].RAlvo * AVL.INominal +
							  AVC.Param[Cuba].Bemf;
		AVC.Ccont[Cuba].VErro = (EST_AVC(Cuba).Ea eq VERDADEIRO)? 0.0 :
							  AVC.Ccont[Cuba].Rerro * AVL.INominal;
#endif
		/* Fim Alteracao - Carlos - 23/06/99 */
	  }
	  else
	  {
	    AVC.Ccont[Cuba].VAlvo = 0.0;
	    AVC.Ccont[Cuba].VErro = 0.0;
	  }
	}
  }
  LiberaSemaf(SEMAF_AVC);
}

#ifdef CBA_120KAII_III

/*
--------------------------------------------------------------------------------
| LogAltConv - Grava em arquivo como append log de alteracao nos parametros no |
|              formato csv. Grava o arquivo no diretorio de log para garantir  |
|              atualizacao no micro reserva.                                   |
--------------------------------------------------------------------------------
*/
/* Define arquivo no diretorio de log e com nome comecando com . para nao listar */
#define		ARQUIVO_LOG_CONV_ATN8	"/score/log/.logconvatn8.csv"

	  /* Cuba (-1 se linha), NomeVariavel, indice para Nome, Valor novo, Valor velho */
void LogAltConv(int aCuba, char *apNome, int aIndNome, float aValNovo, float aValVelho)
{
  FILE *plogfile;
  char linha[100];
  char datahora[60];
  time_t now;
  PosicaoGlobal=50;


  /* Abre arquivo para append */  
  plogfile=fopen(ARQUIVO_LOG_CONV_ATN8,"a");
  if (plogfile ne NULL)
  {
    now = time(NULL);
    strftime(datahora, 60, "%d/%m/%Y %H:%M:%S", localtime(&now));
    sprintf(linha,"%s;%d;%s%d;%f;%f\n",datahora, aCuba, apNome, aIndNome, aValNovo, aValVelho);
	fputs(linha,plogfile);
    fclose(plogfile);
  }
  else
    printf("MccSuperv-> Falha abertura do arquivo: %s\n", ARQUIVO_LOG_CONV_ATN8);
}

/*
--------------------------------------------------------------------------------
| IniLogConvAtn8 - Inicializa tratamento do log de alteracao de parametros de  |
|                  conversao da atn8 para uso interno da ATAN (estudo modulos) |
--------------------------------------------------------------------------------
*/
void IniLogConvAtn8(void)
{
	PosicaoGlobal=51;
	
	/* -- Pointer to descritor in data base -- */
	PDConv=(t_descr_conv *)((char *)Comum + Comum->OfDescConv);
	SemafMemXCpy(SEMAF_COMUM, &LocalDescrConv, (void *)PDConv, sizeof(LocalDescrConv));
}

/*
--------------------------------------------------------------------------------
| TrataLogConvAtn8 - Trata o log de alteracao de parametros de conversao da    |
|                    atn8 para uso interno da ATAN (estudo modulos)            |
--------------------------------------------------------------------------------
*/
void TrataLogConvAtn8(void)
{
  int i, Cuba, CubaOpe;

  /* Verifica se alterou parametros de atn8 de cuba e loga alteracao */
  for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
  {
  PosicaoGlobal=52;
	
    Cuba=ConvCubOperScore(CubaOpe);
	if (Cuba eq -1)
	  continue;
	for(i=0; i<MAX_VALORES_POR_ATN8; i++)
	{
      if (LocalDescrConv.ConvAtn8[Cuba].Offset[i] ne 
        PDConv->ConvAtn8[Cuba].Offset[i])
	  { /* -- Fator de correcao de offset alterado, loga -- */
		/* Cuba, NomeVariavel, indice para Nome, Valor novo, Valor velho */
	    LogAltConv(CubaOpe,"Offset",i,PDConv->ConvAtn8[Cuba].Offset[i],
				LocalDescrConv.ConvAtn8[Cuba].Offset[i]);
		LocalDescrConv.ConvAtn8[Cuba].Offset[i] = PDConv->ConvAtn8[Cuba].Offset[i];
      }
      if (LocalDescrConv.ConvAtn8[Cuba].Ganho[i] ne 
        PDConv->ConvAtn8[Cuba].Ganho[i])
	  { /* -- Fator de correcao de ganho alterado, loga -- */
		/* Cuba, NomeVariavel, indice para Nome, Valor novo, Valor velho */
	    LogAltConv(CubaOpe,"Ganho",i,PDConv->ConvAtn8[Cuba].Ganho[i],
				LocalDescrConv.ConvAtn8[Cuba].Ganho[i]);
		LocalDescrConv.ConvAtn8[Cuba].Ganho[i] = PDConv->ConvAtn8[Cuba].Ganho[i];
      }
	}
    PosicaoGlobal=53;
	
  }
  /* Alterou parametros de atn8 que nao eh de cuba, loga alteracao */
  for( Cuba=0; Cuba < NUM_LEITURAS_ESP; Cuba++)
  {
    if (LocalDescrConv.ConvEspAtn8.EntEspAtn8[Cuba].OffEsp ne 
        PDConv->ConvEspAtn8.EntEspAtn8[Cuba].OffEsp)
	{ /* -- Fator de correcao de offset alterado, loga -- */
	  /* Cuba, NomeVariavel, indice para Nome, Valor novo, Valor velho */
	  LogAltConv(-1,"OffEsp",Cuba,PDConv->ConvEspAtn8.EntEspAtn8[Cuba].OffEsp,
				LocalDescrConv.ConvEspAtn8.EntEspAtn8[Cuba].OffEsp);
	  LocalDescrConv.ConvEspAtn8.EntEspAtn8[Cuba].OffEsp = PDConv->ConvEspAtn8.EntEspAtn8[Cuba].OffEsp;
	}
    if (LocalDescrConv.ConvEspAtn8.EntEspAtn8[Cuba].GanhoEsp ne 
        PDConv->ConvEspAtn8.EntEspAtn8[Cuba].GanhoEsp)
	{ /* -- Fator de correcao de ganho alterado, loga -- */
	  /* Cuba, NomeVariavel, indice para Nome, Valor novo, Valor velho */
	  LogAltConv(-1,"GanhoEsp",Cuba,PDConv->ConvEspAtn8.EntEspAtn8[Cuba].GanhoEsp,
				LocalDescrConv.ConvEspAtn8.EntEspAtn8[Cuba].GanhoEsp);
	  LocalDescrConv.ConvEspAtn8.EntEspAtn8[Cuba].GanhoEsp = PDConv->ConvEspAtn8.EntEspAtn8[Cuba].GanhoEsp;
	}
    PosicaoGlobal=54;
	
  }
}
#endif


/*
--------------------------------------------------------------------------------
| CalcMediasLinha - Calcula valores medios diarios relativos `a linha.         |
--------------------------------------------------------------------------------
*/
void CalcMediasLinha(void)
{
  float	PotLinhaCCont;
  double IDif;
  char str_index[20];
  int i;
  PosicaoGlobal=55;
  

  /* -- Inicializa IAlvo -- */
  AVL.IAlvo=AVL.INominal;

  /* -- *************** Dados medios diarios ******************* -- */
  /* -- incrementa contador de numero de ciclos de controle no ar -- */
  AVL.NCicAtivoDia += 1;
  /* -- potencia da linha no ciclo de controle -- */
  PotLinhaCCont = AVL.VLinhaCicCont * AVL.ICicContlMed;
  /* -- tensao media da linha no dia -- */
  AVL.VLinhaDia = (AVL.VLinhaDia * (AVL.NCicAtivoDia-1) + AVL.VLinhaCicCont)/
				AVL.NCicAtivoDia;
  /* -- corrente media principal da linha no dia -- */
  AVL.IMedDia = (AVL.IMedDia * (AVL.NCicAtivoDia-1) + AVL.ICicContlMed)/
				AVL.NCicAtivoDia;

  /* -- corrente alvo media da linha no dia -- */
  AVL.IAlvoDia = (AVL.IAlvoDia * (AVL.NCicAtivoDia-1) + AVL.IAlvo)/
				AVL.NCicAtivoDia;
  /* -- Potencia media da linha no dia -- */
  AVL.PotLinhaDia = (AVL.PotLinhaDia * (AVL.NCicAtivoDia-1) + PotLinhaCCont)/
				AVL.NCicAtivoDia;
  /* -- *************** Dados medios de turno ******************* -- */
  /* -- incrementa contador de numero de ciclos de controle no ar -- */
  AVL_TURNO.NCicAtivoDia += 1;
  /* -- tensao media da linha no dia -- */
  AVL_TURNO.VLinhaDia = (AVL_TURNO.VLinhaDia * (AVL_TURNO.NCicAtivoDia-1) + AVL.VLinhaCicCont)/
				AVL_TURNO.NCicAtivoDia;
  /* -- corrente media principal da linha no dia -- */
  AVL_TURNO.IMedDia = (AVL_TURNO.IMedDia * (AVL_TURNO.NCicAtivoDia-1) + AVL.ICicContlMed)/
				AVL_TURNO.NCicAtivoDia;

  /* -- corrente alvo media da linha no dia -- */
  AVL_TURNO.IAlvoDia = (AVL_TURNO.IAlvoDia * (AVL_TURNO.NCicAtivoDia-1) + AVL.IAlvo)/
				AVL_TURNO.NCicAtivoDia;
  /* -- Potencia media da linha no dia -- */
  AVL_TURNO.PotLinhaDia = (AVL_TURNO.PotLinhaDia * (AVL_TURNO.NCicAtivoDia-1) + PotLinhaCCont)/
				AVL_TURNO.NCicAtivoDia;
  PosicaoGlobal=56;


  /* -- Calcula dados relativos ao relatorio historico da linha -- */
  CalcHistLinha();
  /* -- Verifica possivel discrepancia entre a corrente principal e a -- */
  /* -- reserva e gera evento se sim -- */
  IDif=AVL.ICicContlMed-AVL.ICicContlMedRes;
  if (fabs(IDif) >= (double)AVL.IDifMax)
  {
/* -- Alteracao - inicio - 06/02/2003 - Leonel - Alterado evento para indicar qual canal -- */
 	/*-- CL01 - Upgrade Red II para ATN8 --*/
 	if ((Comum->IdentReducao >= 7) or (Comum->IdentReducao  <= 2))
	{
	  sprintf(str_index,"IIndex%d",AVL.CanalISec);
	  GeraEvento(DIF_CORRENTE,-1,-1,AVL.ICicContlMed/1000.0,AVL.ICicContlMedRes/1000.0,
		IDif/1000.0,str_index);
	}
	else
	{	
    GeraEvento(DIF_CORRENTE,-1,-1,AVL.ICicContlMed/1000.0,AVL.ICicContlMedRes/1000.0,
		IDif/1000.0,"--------");
	}
/* -- Alteracao - fim - 06/02/2003 - Leonel - Alterado evento para indicar qual canal -- */
  }
/* -- Alteracao - inicio - 06/02/2003 - Leonel - Compara outras correntes das atnCAs (que nao a secundaria) -- */
  /*-- CL01 - Upgrade Red II para ATN8 --*/
  if ((Comum->IdentReducao >= 7) or (Comum->IdentReducao  <= 2))
  {
    for(i=0; i < NUM_VAR_NMUX; i++)
    { /* verifica se nao nao eh principal nem secundaria e se esta configurado */
      if (AVL.IIndex[i] ne -1)
	    if ((i ne AVL.CanalIPrinc) and (i ne AVL.CanalISec))
		  if (AVL.StatusNMux[i] eq CONV_OK)
		  { /* verifica se dado esta sendo lido (remota online e configurada) */
		    IDif=AVL.ICicContlMed-AVL.ValorNMuxMed[i];
		    if (fabs(IDif) >= (double)AVL.IDifMax)
		    {
			  sprintf(str_index,"IIndex%d",i);
		      GeraEvento(DIF_CORRENTE,-1,-1,AVL.ICicContlMed/1000.0,AVL.ValorNMuxMed[i]/1000.0,
				IDif/1000.0,str_index);
		    }
		  }
    }
  }
/* -- Alteracao - fim - 06/02/2003 - Leonel - Compara outras correntes das atnCAs (que nao a secundaria) -- */
}


/*
--------------------------------------------------------------------------------
| CalcMediasCubas - Calcula valores medios diarios relativos `as cubas.        |
--------------------------------------------------------------------------------
*/
void CalcMediasCubas(void)
{
  int	Cuba,CubaOpe;
  double IDif;

  PosicaoGlobal=57;

  for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
  {
	Cuba=ConvCubOperScore(CubaOpe);
	if (Cuba eq -1)
	  continue;

	CubaGlobal=Cuba;	/* -- Armazema qual cuba a ser tratada em global -- */
	
	if (sigsetjmp(MccEnvBuf,1))
	{ /* -- Ocorreu alguma excessao -- */
	  /* -- Retira cuba do controle -- */
	  EST_AVC(CubaGlobal).ForaControle=VERDADEIRO;
	  EmiteAlarmeFor(TODOS_DISPOSITIVOS,MsgException);
	  EmiteAlarmeFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_MSG_251),
			ConvCubScoreOper(CubaGlobal));
	}
	if ((EST_AVC(Cuba).ForaLeitura eq FALSO) and
		(EST_AVC(Cuba).ForaControle eq FALSO) and
		(AVL.LinhaHabilitada eq VERDADEIRO))
	{
	  /* -- Duracao do controle -- */
	  /* -- *************** Dados medios diarios ******************* -- */
	  SUPERV_AVC(Cuba).DurContlDia += IntervCicContSeg;
	  /* -- *************** Dados medios de turno ******************* -- */
	  SUPERV_AVC_TURNO(Cuba).DurContlDia += IntervCicContSeg;

	  /* -- Calculos de supervisao especial -- */
	  SupervEspecial(Cuba);

	  /* -- Armazena estado principal da cuba no dia -- */
	  /* -- *************** Dados medios diarios ******************* -- */
	  if (EST_AVC(Cuba).EstadoCuba > SUPERV_AVC(Cuba).EstPrincDia)
		SUPERV_AVC(Cuba).EstPrincDia=EST_AVC(Cuba).EstadoCuba;

	  /* -- Numero de ciclos de controle para supervisao -- */
	  SUPERV_AVC(Cuba).NCContPotDia += 1;

	  /* -- *************** Dados medios de turno ******************* -- */
	  if (EST_AVC(Cuba).EstadoCuba > SUPERV_AVC_TURNO(Cuba).EstPrincDia)
		SUPERV_AVC_TURNO(Cuba).EstPrincDia=EST_AVC(Cuba).EstadoCuba;

	  /* -- Numero de ciclos de controle para supervisao -- */
	  SUPERV_AVC_TURNO(Cuba).NCContPotDia += 1;

	/* Inicio Alteracao - Carlos - 23/06/99 */
	/* Tratamento de booster de corrente */

	  /* -- *************** Dados medios diarios ******************* -- */
	  SUPERV_AVC(Cuba).Sup.ICubaMedDia = (SUPERV_AVC(Cuba).Sup.ICubaMedDia *
		(SUPERV_AVC(Cuba).NCContPotDia-1) + AVC.CcontMcp[Cuba].ICicContlMedCuba)/
		SUPERV_AVC(Cuba).NCContPotDia;

	  /* -- *************** Dados medios de turno ******************* -- */
	  SUPERV_AVC_TURNO(Cuba).Sup.ICubaMedDia = (SUPERV_AVC_TURNO(Cuba).Sup.ICubaMedDia *
		(SUPERV_AVC_TURNO(Cuba).NCContPotDia-1) + AVC.CcontMcp[Cuba].ICicContlMedCuba)/
		SUPERV_AVC_TURNO(Cuba).NCContPotDia;


#ifdef	BOOSTER_CORRENTE
	  /* -- *************** Dados medios diarios ******************* -- */
	  SUPERV_AVC(Cuba).IAlvoCubaDia = (SUPERV_AVC(Cuba).IAlvoCubaDia *
		(SUPERV_AVC(Cuba).NCContPotDia-1) + AVC.Ccont[Cuba].IAlvoCuba)/
		SUPERV_AVC(Cuba).NCContPotDia;

	  /* -- *************** Dados medios de turno ******************* -- */
	  SUPERV_AVC_TURNO(Cuba).IAlvoCubaDia = (SUPERV_AVC_TURNO(Cuba).IAlvoCubaDia *
		(SUPERV_AVC_TURNO(Cuba).NCContPotDia-1) + AVC.Ccont[Cuba].IAlvoCuba)/
		SUPERV_AVC_TURNO(Cuba).NCContPotDia;
#endif
  /* Fim Alteracao - Carlos - 23/06/99 */

	  /* -- Calcula potencia e energia medias -- */
	  CalcPotEnerDia(Cuba);

	  /* -- Calcula resistencias e tensoes medias -- */
	  CalcResTensDia(Cuba);

	  if (EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL)
	  {
		/* -- Cuba Normal -- */
		/* -- Numero de ciclos de controle para supervisao -- */
		/* -- *************** Dados medios diarios ******************* -- */
		SUPERV_AVC(Cuba).NumCContDia += 1;
		/* -- *************** Dados medios de turno ******************* -- */
		SUPERV_AVC_TURNO(Cuba).NumCContDia += 1;

		/* -- Calcula valores relativos a medias diarias de EA -- */
		CalcEa(Cuba);

		/* -- Calcula valores relativos a Desvio de tensao e fora do controle -- */
		CalcVDesvForaCont(Cuba);

		/* -- Calcula duracao de ruido e fora de leitura, numero de corridas e que-
			bradas, numero de movimentacoes de anodo e outros parametros -- */
		CalcDuracoes(Cuba);

		/* -- Calcula dados relativos ao relatorio historico de ruido -- */
		CalcRuido(Cuba);

		/* -- Calcula dados relativos ao relatorio historico de incrementos -- */
		CalcIncrementos(Cuba);
	  }
/* -- alteracao - inicio - 10/10/2002 - Leonel - Monitoracao corrente de cuba para alarme -- */
	  /*-- CL01 - Upgrade Red II para ATN8 --*/
	  if ((Comum->IdentReducao >= 7) or (Comum->IdentReducao  <= 2))
	  { /* somente para salas 125ka 5 e 6 */
/* -- alteracao - inicio - 05/12/2002 - Leonel - Disponibiliza diferenca de corrente na base de dados -- */
#ifdef	BOOSTER_CORRENTE
		IDif=AVL.ICicContlMed-AVC.CcontMcp[Cuba].ICicContlMedCuba;
#else
		IDif=AVL.ICicContlMed-AVC.Cleit[Cuba].Iinst;
#endif
		AVC.CcontMcp[Cuba].IDifCuba = IDif;
/* -- alteracao - fim - 05/12/2002 - Leonel - Disponibiliza diferenca de corrente na base de dados -- */
	    if ((EST_AVC(Cuba).EstadoCuba ne CUBA_DESLIGADA) and
		    (EST_AVC(Cuba).RtuStatus eq RTU_ON_LINE))
	    {
#ifdef	BOOSTER_CORRENTE
		  if (fabs(IDif) >= (double)AVL.IDifMax)
		    GeraEvento(DIF_CORRENTE_CUBA,Cuba,-1,AVL.ICicContlMed/1000.0,
				AVC.CcontMcp[Cuba].ICicContlMedCuba/1000.0,IDif/1000.0);
#else
		  if (fabs(IDif) >= (double)AVL.IDifMax)
		    GeraEvento(DIF_CORRENTE_CUBA,Cuba,-1,AVL.ICicContlMed/1000.0,
				AVC.Cleit[Cuba].Iinst/1000.0,IDif/1000.0);
#endif
	    }
  		PosicaoGlobal=58;

	  }
/* -- alteracao - fim - 10/10/2002 - Leonel - Monitoracao corrente de cuba para alarme -- */
	} /* -- if fora leitura -- */

	/* -- alteracao - inicio - 21/10/02 - Leonel - Inclusao evento temperatura Atn8 -- */
	/*-- CL01 - Upgrade Red II para ATN8 --*/
	if ((Comum->IdentReducao >= 7) or (Comum->IdentReducao  <= 2))
	{ /* somente para salas 125ka 5 e 6 */
	  if (AVL.Trab.Atn8Temperature[Cuba] > AVL.Atn8TempLimSup)
	  {
		if (EST_AVC(Cuba).Atn8TempAlta ne VERDADEIRO)
		{
		  EST_AVC(Cuba).Atn8TempAlta=VERDADEIRO;
	      GeraEvento(TEMP_ATN8_CUBA,Cuba,-1,"Inicio",
				(float)AVL.Trab.Atn8Temperature[Cuba],
				(float)AVL.Atn8TempLimSup); /* Temperatura interna da Atn8 */
		}
	  }
	  else
	  {
		if (EST_AVC(Cuba).Atn8TempAlta eq VERDADEIRO)
		{
		  EST_AVC(Cuba).Atn8TempAlta=FALSO;
	      GeraEvento(TEMP_ATN8_CUBA,Cuba,-1,"Fim",
				(float)AVL.Trab.Atn8Temperature[Cuba],
				(float)AVL.Atn8TempLimSup); /* Temperatura interna da Atn8 */
		}
	  }
	}
	/* -- alteracao - fim - 21/10/02 - Leonel - Inclusao evento temperatura Atn8 -- */

  } /* -- for -- */
} /* -- CalcMediasCubas -- */


/*
--------------------------------------------------------------------------------
| SupervEspecial - Calculos de supervisao especial da tensao da cuba dada      |
--------------------------------------------------------------------------------
*/
void SupervEspecial(int Cuba)
{
  float VCicContlBruta,VInst;

  /* Inicio Alteracao - Carlos - 23/06/99 */
  /* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
  VCicContlBruta=AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba;
  if ((EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL) or
	  (EST_AVC(Cuba).EstadoCuba eq CUBA_PARTIDA))
	VCicContlBruta += AVC.Param[Cuba].Bemf;
#else
  VCicContlBruta=AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal;
  if ((EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL) or
	  (EST_AVC(Cuba).EstadoCuba eq CUBA_PARTIDA))
	VCicContlBruta += AVC.Param[Cuba].Bemf;
#endif
  /* Fim Alteracao - Carlos - 23/06/99 */


  VInst=AVC.Cleit[Cuba].Vinst;
  switch (EST_AVC(Cuba).EstadoCuba)
  {
#ifdef	INCLUI_SUP_ESP_CUBA_NORMAL
	case CUBA_NORMAL:
	  if (AVC.CcontMcp[Cuba].RCicContlBruta < AVC.Param[Cuba].RMinNormalSupEsp)
		/* -- gera evento de fora de faixa -- */
		GeraEvento(SUPERV_ESPECIAL,Cuba,-1,ScoreGetStr(STR_NORMAL),STR_TRACO,
			VCicContlBruta,VInst);
	  if (AVC.CcontMcp[Cuba].RCicContlBruta >= AVC.Param[Cuba].RMaxNormalSupEsp)
		/* -- gera evento de fora de faixa -- */
		GeraEvento(SUPERV_ESPECIAL,Cuba,-1,ScoreGetStr(STR_NORMAL),STR_TRACO,
			VCicContlBruta,VInst);
	  break;
#endif
	case CUBA_PARTIDA:
	  if (AVC.CcontMcp[Cuba].RCicContlBruta < AVC.Param[Cuba].RMinPartidoSupEsp)
		/* -- gera evento de fora de faixa -- */
		GeraEvento(SUPERV_ESPECIAL,Cuba,-1,ScoreGetStr(STR_PARTIDA),STR_TRACO,
			VCicContlBruta,VInst);
	  if (AVC.CcontMcp[Cuba].RCicContlBruta >= AVC.Param[Cuba].RMaxPartidoSupEsp)
		/* -- gera evento de fora de faixa -- */
		GeraEvento(SUPERV_ESPECIAL,Cuba,-1,ScoreGetStr(STR_PARTIDA),STR_TRACO,
			VCicContlBruta,VInst);
	  break;
	case CUBA_LIGADA:
	  if (AVC.CcontMcp[Cuba].RCicContlBruta < AVC.Param[Cuba].RMinLigadoSupEsp)
		/* -- gera evento de fora de faixa -- */
		GeraEvento(SUPERV_ESPECIAL,Cuba,-1,ScoreGetStr(STR_LIGADA),STR_TRACO,
			VCicContlBruta,VInst);
	  if (AVC.CcontMcp[Cuba].RCicContlBruta >= AVC.Param[Cuba].RMaxLigadoSupEsp)
		/* -- gera evento de fora de faixa -- */
		GeraEvento(SUPERV_ESPECIAL,Cuba,-1,ScoreGetStr(STR_LIGADA),STR_TRACO,
			VCicContlBruta,VInst);
	  break;
	case CUBA_DESLIGADA:
	  if (AVC.CcontMcp[Cuba].RCicContlBruta < AVC.Param[Cuba].RMinDesligSupEsp)
		/* -- gera evento de fora de faixa -- */
		GeraEvento(SUPERV_ESPECIAL,Cuba,-1,ScoreGetStr(STR_DESLIGADA),STR_TRACO,
			VCicContlBruta,VInst);
	  if (AVC.CcontMcp[Cuba].RCicContlBruta >= AVC.Param[Cuba].RMaxDesligSupEsp)
		/* -- gera evento de fora de faixa -- */
		GeraEvento(SUPERV_ESPECIAL,Cuba,-1,ScoreGetStr(STR_DESLIGADA),STR_TRACO,
			VCicContlBruta,VInst);
	  break;
  }
}

/*
--------------------------------------------------------------------------------
| CalcPotEnerDia - Calcula potencias e energias medias diarias da cuba dada    |
--------------------------------------------------------------------------------
*/
void CalcPotEnerDia(int Cuba)
{
  int	NCicCont;
  float PotCicContlAlvo;
  float	DifAlvo;

  /* -- *************** Dados medios diarios ******************* -- */
  NCicCont = SUPERV_AVC(Cuba).NCContPotDia;

  /* Inicio Alteracao - Carlos - 23/06/99 */
  /* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
  /* -- Potencia media alvo do dia -- */
  PotCicContlAlvo=AVC.Ccont[Cuba].VAlvo*AVC.Ccont[Cuba].IAlvoCuba;
#else
  /* -- Potencia media alvo do dia -- */
  PotCicContlAlvo=AVC.Ccont[Cuba].VAlvo*AVL.IAlvo;
#endif
  /* Fim Alteracao - Carlos - 23/06/99 */

  SUPERV_AVC(Cuba).PotDiaAlvo=(SUPERV_AVC(Cuba).PotDiaAlvo*(NCicCont-1)+
					PotCicContlAlvo)/NCicCont;
  /* -- Potencia media bruta do dia -- */
  SUPERV_AVC(Cuba).PotDiaBruta=(SUPERV_AVC(Cuba).PotDiaBruta*(NCicCont-1)+
					AVC.CcontMcp[Cuba].PotCicContlBruta)/NCicCont;
  /* -- Potencia media liquida do dia -- */
  SUPERV_AVC(Cuba).PotDiaLiq=(SUPERV_AVC(Cuba).PotDiaLiq*(NCicCont-1)+
					AVC.CcontMcp[Cuba].PotCicContlLiq)/NCicCont;
  /* -- Energia bruta consumida no dia pela Cuba -- */
  SUPERV_AVC(Cuba).EnergDiaBruta=SUPERV_AVC(Cuba).PotDiaBruta *
					(NCicCont*IntervCicContSeg);
  /* -- Energia liquida consumida no dia pela Cuba -- */
  SUPERV_AVC(Cuba).EnergDiaLiq=SUPERV_AVC(Cuba).PotDiaLiq *
					(NCicCont*IntervCicContSeg);

  PosicaoGlobal=59;

  /* -- Energia consumida por falha de movimentacao -- */
  DifAlvo = AVC.CcontMcp[Cuba].VCicContlBruta - AVC.Ccont[Cuba].VAlvo;
  if(AvcLocal[Cuba].IntegraFalhaMov eq VERDADEIRO)
  {
	if(DifAlvo > 0)
	{
	  if(DifAlvo > AVC.Param[Cuba].BandaMortaSup)
	    SUPERV_AVC(Cuba).Sup.kwcimafalhamov += (DifAlvo * 
								AVC.CcontMcp[Cuba].ICicContlMedCuba) / 30;
	}
	else
	{
	  DifAlvo = fabs(DifAlvo);
	  if(DifAlvo > AVC.Param[Cuba].BandaMortaInf)
  	  SUPERV_AVC(Cuba).Sup.kwbaixofalhamov += (DifAlvo * 
								AVC.CcontMcp[Cuba].ICicContlMedCuba) / 30;
	}
  }
  else if(EST_AVC(Cuba).RtuStatus eq 1) /* -- Energia consumida por cuba fora de rede -- */
  {
	if(DifAlvo > 0)
	{
	  if(DifAlvo > AVC.Param[Cuba].BandaMortaSup)
	    SUPERV_AVC(Cuba).Sup.kwcimaforarede += (DifAlvo *
								AVC.CcontMcp[Cuba].ICicContlMedCuba) / 30;
	}
	else
	{
	  DifAlvo = fabs(DifAlvo);
	  if(DifAlvo > AVC.Param[Cuba].BandaMortaInf)
	    SUPERV_AVC(Cuba).Sup.kwbaixoforarede += (DifAlvo *
								AVC.CcontMcp[Cuba].ICicContlMedCuba) / 30;
	}
  }
  else if(EST_AVC(Cuba).ChaveLocRem eq 1) /* -- Energia consumida por cuba em manual local -- */
  {
	if(DifAlvo > 0)
	{
	  if(DifAlvo > AVC.Param[Cuba].BandaMortaSup)
	    SUPERV_AVC(Cuba).Sup.kwcimamanuallocal += (DifAlvo *
								AVC.CcontMcp[Cuba].ICicContlMedCuba) / 30;
	}
	else
	{
	  DifAlvo = fabs(DifAlvo);
	  if(DifAlvo > AVC.Param[Cuba].BandaMortaInf)
	    SUPERV_AVC(Cuba).Sup.kwbaixomanuallocal += (DifAlvo *
								AVC.CcontMcp[Cuba].ICicContlMedCuba) / 30;
	}
  }
  else /* -- Energia consumida por cuba em geral -- */
  {
	if(DifAlvo > 0)
	{
	  if(DifAlvo > AVC.Param[Cuba].BandaMortaSup)
	    SUPERV_AVC(Cuba).Sup.kwcimageral += (DifAlvo *
								AVC.CcontMcp[Cuba].ICicContlMedCuba) / 30;
	}
	else
	{
	  DifAlvo = fabs(DifAlvo);
	  if(DifAlvo > AVC.Param[Cuba].BandaMortaInf)
	    SUPERV_AVC(Cuba).Sup.kwbaixogeral += (DifAlvo *
								AVC.CcontMcp[Cuba].ICicContlMedCuba) / 30;
	}
  }

  /* -- *************** Dados medios de turno ******************* -- */
  NCicCont = SUPERV_AVC_TURNO(Cuba).NCContPotDia;

  /* -- Potencia media alvo do dia -- */
  SUPERV_AVC_TURNO(Cuba).PotDiaAlvo=(SUPERV_AVC_TURNO(Cuba).PotDiaAlvo*(NCicCont-1)+
					PotCicContlAlvo)/NCicCont;
  /* -- Potencia media bruta do dia -- */
  SUPERV_AVC_TURNO(Cuba).PotDiaBruta=(SUPERV_AVC_TURNO(Cuba).PotDiaBruta*(NCicCont-1)+
					AVC.CcontMcp[Cuba].PotCicContlBruta)/NCicCont;
  /* -- Potencia media liquida do dia -- */
  SUPERV_AVC_TURNO(Cuba).PotDiaLiq=(SUPERV_AVC_TURNO(Cuba).PotDiaLiq*(NCicCont-1)+
					AVC.CcontMcp[Cuba].PotCicContlLiq)/NCicCont;
  /* -- Energia bruta consumida no dia pela Cuba -- */
  SUPERV_AVC_TURNO(Cuba).EnergDiaBruta=SUPERV_AVC_TURNO(Cuba).PotDiaBruta *
					(NCicCont*IntervCicContSeg);
  /* -- Energia liquida consumida no dia pela Cuba -- */
  SUPERV_AVC_TURNO(Cuba).EnergDiaLiq=SUPERV_AVC_TURNO(Cuba).PotDiaLiq *
					(NCicCont*IntervCicContSeg);

  /* -- Energia consumida por falha de movimentacao -- */
  DifAlvo = AVC.CcontMcp[Cuba].VCicContlBruta - AVC.Ccont[Cuba].VAlvo;
  if(AvcLocal[Cuba].IntegraFalhaMov eq VERDADEIRO)
  {
	if(DifAlvo > 0)
	{
	  if(DifAlvo > AVC.Param[Cuba].BandaMortaSup)
	    SUPERV_AVC_TURNO(Cuba).Sup.kwcimafalhamov += (DifAlvo * 
								AVC.CcontMcp[Cuba].ICicContlMedCuba) / 30;
	}
	else
	{
	  DifAlvo = fabs(DifAlvo);
	  if(DifAlvo > AVC.Param[Cuba].BandaMortaInf)
  	  SUPERV_AVC_TURNO(Cuba).Sup.kwbaixofalhamov += (DifAlvo * 
								AVC.CcontMcp[Cuba].ICicContlMedCuba) / 30;
	}
  }
  else if(EST_AVC(Cuba).RtuStatus eq 1) /* -- Energia consumida por cuba fora de rede -- */
  {
	if(DifAlvo > 0)
	{
	  if(DifAlvo > AVC.Param[Cuba].BandaMortaSup)
	    SUPERV_AVC_TURNO(Cuba).Sup.kwcimaforarede += (DifAlvo *
								AVC.CcontMcp[Cuba].ICicContlMedCuba) / 30;
	}
	else
	{
	  DifAlvo = fabs(DifAlvo);
	  if(DifAlvo > AVC.Param[Cuba].BandaMortaInf)
	    SUPERV_AVC_TURNO(Cuba).Sup.kwbaixoforarede += (DifAlvo *
								AVC.CcontMcp[Cuba].ICicContlMedCuba) / 30;
	}
  	PosicaoGlobal=60;
	
  }
  else if(EST_AVC(Cuba).ChaveLocRem eq 1) /* -- Energia consumida por cuba em manual local -- */
  {
	if(DifAlvo > 0)
	{
	  if(DifAlvo > AVC.Param[Cuba].BandaMortaSup)
	    SUPERV_AVC_TURNO(Cuba).Sup.kwcimamanuallocal += (DifAlvo *
								AVC.CcontMcp[Cuba].ICicContlMedCuba) / 30;
	}
	else
	{
	  DifAlvo = fabs(DifAlvo);
	  if(DifAlvo > AVC.Param[Cuba].BandaMortaInf)
	    SUPERV_AVC_TURNO(Cuba).Sup.kwbaixomanuallocal += (DifAlvo *
								AVC.CcontMcp[Cuba].ICicContlMedCuba) / 30;
	}
  }
  else /* -- Energia consumida por cuba em geral -- */
  {
	if(DifAlvo > 0)
	{
	  if(DifAlvo > AVC.Param[Cuba].BandaMortaSup)
	    SUPERV_AVC_TURNO(Cuba).Sup.kwcimageral += (DifAlvo *
								AVC.CcontMcp[Cuba].ICicContlMedCuba) / 30;
	}
	else
	{
	  DifAlvo = fabs(DifAlvo);
	  if(DifAlvo > AVC.Param[Cuba].BandaMortaInf)
	    SUPERV_AVC_TURNO(Cuba).Sup.kwbaixogeral += (DifAlvo *
								AVC.CcontMcp[Cuba].ICicContlMedCuba) / 30;
	}
  }

}

/*
--------------------------------------------------------------------------------
| CalcResTensDia - Calcula resistencias e tensoes medias diarias da cuba dada  |
--------------------------------------------------------------------------------
*/
void CalcResTensDia(int Cuba)
{
  int NCicCont;

  /* -- *************** Dados medios diarios ******************* -- */
  NCicCont = SUPERV_AVC(Cuba).NCContPotDia;

  /* -- Resistencia alvo media do dia -- */
  if (EST_AVC(Cuba).EstadoCuba eq CUBA_DESLIGADA)
	/* RAlvo = 0 */
	SUPERV_AVC(Cuba).RAlvoDia=SUPERV_AVC(Cuba).RAlvoDia*(NCicCont-1)/NCicCont;
  else
	SUPERV_AVC(Cuba).RAlvoDia=(SUPERV_AVC(Cuba).RAlvoDia*(NCicCont-1)+
					AVC.Ccont[Cuba].RAlvo)/NCicCont;
  /* -- Resistencia media bruta do dia -- */
  SUPERV_AVC(Cuba).RDiaBruta=(SUPERV_AVC(Cuba).RDiaBruta*(NCicCont-1)+
					AVC.CcontMcp[Cuba].RCicContlBruta)/NCicCont;
  /* -- Resistencia media liquida do dia -- */
  SUPERV_AVC(Cuba).RDiaLiq=(SUPERV_AVC(Cuba).RDiaLiq*(NCicCont-1)+
					AVC.CcontMcp[Cuba].RCicContlLiq)/NCicCont;
  /* -- Tensao media bruta do dia -- */
  SUPERV_AVC(Cuba).VDiaBruta=(SUPERV_AVC(Cuba).VDiaBruta*(NCicCont-1)+
					AVC.CcontMcp[Cuba].VCicContlBruta)/NCicCont;
  /* -- Tensao media liquida do dia -- */
  SUPERV_AVC(Cuba).VDiaLiq=(SUPERV_AVC(Cuba).VDiaLiq*(NCicCont-1)+
					AVC.CcontMcp[Cuba].VCicContlLiq)/NCicCont;
  /* -- Tensao setpoint media do dia -- */
  SUPERV_AVC(Cuba).VSetPointDia=(SUPERV_AVC(Cuba).VSetPointDia*(NCicCont-1)+
					AVC.Ccont[Cuba].VSetPoint)/NCicCont;
  /* -- Bemf medio do dia -- */
  SUPERV_AVC(Cuba).BemfDia=(SUPERV_AVC(Cuba).BemfDia*(NCicCont-1)+
					AVC.Param[Cuba].Bemf)/NCicCont;

  /* -- Dif. VAlvo x VLiquida por Falha de Movimentacao -- */
  if(AvcLocal[Cuba].IntegraFalhaMov eq VERDADEIRO)
  {
  	SUPERV_AVC(Cuba).Sup.DifALFalhaMov = (SUPERV_AVC(Cuba).Sup.DifALFalhaMov*(NCicCont-1)-
					(AVC.Ccont[Cuba].RAlvo * AVC.CcontMcp[Cuba].ICicContlMedCuba + AVC.Param[Cuba].Bemf) +
						AVC.CcontMcp[Cuba].VCicContlLiq)/NCicCont;

  	SUPERV_AVC(Cuba).Sup.DifALInibUsu = (SUPERV_AVC(Cuba).Sup.DifALInibUsu*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALManual = (SUPERV_AVC(Cuba).Sup.DifALManual*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALInibPrev = (SUPERV_AVC(Cuba).Sup.DifALInibPrev*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALInibQueb = (SUPERV_AVC(Cuba).Sup.DifALInibQueb*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALIntervMov= (SUPERV_AVC(Cuba).Sup.DifALIntervMov*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALBandaMorta= (SUPERV_AVC(Cuba).Sup.DifALBandaMorta*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALDesvio= (SUPERV_AVC(Cuba).Sup.DifALDesvio*(NCicCont-1))/NCicCont;
  }
  /* -- Dif. VAlvo x VLiquida por Inibicao Usuario -- */
  else if(EST_AVC(Cuba).InibeControleUsu eq VERDADEIRO)
  {
  	SUPERV_AVC(Cuba).Sup.DifALInibUsu = (SUPERV_AVC(Cuba).Sup.DifALInibUsu*(NCicCont-1)-
					(AVC.Ccont[Cuba].RAlvo * AVC.CcontMcp[Cuba].ICicContlMedCuba + AVC.Param[Cuba].Bemf) +
						AVC.CcontMcp[Cuba].VCicContlLiq)/NCicCont;

  	SUPERV_AVC(Cuba).Sup.DifALFalhaMov = (SUPERV_AVC(Cuba).Sup.DifALFalhaMov*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALManual = (SUPERV_AVC(Cuba).Sup.DifALManual*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALInibPrev = (SUPERV_AVC(Cuba).Sup.DifALInibPrev*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALInibQueb = (SUPERV_AVC(Cuba).Sup.DifALInibQueb*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALIntervMov= (SUPERV_AVC(Cuba).Sup.DifALIntervMov*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALBandaMorta= (SUPERV_AVC(Cuba).Sup.DifALBandaMorta*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALDesvio= (SUPERV_AVC(Cuba).Sup.DifALDesvio*(NCicCont-1))/NCicCont;
  }
  /* -- Dif. VAlvo x VLiquida por forno em Manual -- */
  else if(EST_AVC(Cuba).ChaveAutMan eq MANUAL or EST_AVC(Cuba).ChaveLocRem eq LOCAL)
  {
  	SUPERV_AVC(Cuba).Sup.DifALManual = (SUPERV_AVC(Cuba).Sup.DifALManual*(NCicCont-1)-
					(AVC.Ccont[Cuba].RAlvo * AVC.CcontMcp[Cuba].ICicContlMedCuba + AVC.Param[Cuba].Bemf) +
						AVC.CcontMcp[Cuba].VCicContlLiq)/NCicCont;

  	SUPERV_AVC(Cuba).Sup.DifALFalhaMov = (SUPERV_AVC(Cuba).Sup.DifALFalhaMov*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALInibUsu = (SUPERV_AVC(Cuba).Sup.DifALInibUsu*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALInibPrev = (SUPERV_AVC(Cuba).Sup.DifALInibPrev*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALInibQueb = (SUPERV_AVC(Cuba).Sup.DifALInibQueb*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALIntervMov= (SUPERV_AVC(Cuba).Sup.DifALIntervMov*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALBandaMorta= (SUPERV_AVC(Cuba).Sup.DifALBandaMorta*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALDesvio= (SUPERV_AVC(Cuba).Sup.DifALDesvio*(NCicCont-1))/NCicCont;
  }
  /* -- Dif. VAlvo x VLiquida por forno em Desvio  -- */
  else if(EST_AVC(Cuba).DesvioTensao eq VERDADEIRO)
  {
  	SUPERV_AVC(Cuba).Sup.DifALDesvio = (SUPERV_AVC(Cuba).Sup.DifALDesvio*(NCicCont-1)-
					(AVC.Ccont[Cuba].RAlvo * AVC.CcontMcp[Cuba].ICicContlMedCuba + AVC.Param[Cuba].Bemf) +
						AVC.CcontMcp[Cuba].VCicContlLiq)/NCicCont;

  	SUPERV_AVC(Cuba).Sup.DifALFalhaMov = (SUPERV_AVC(Cuba).Sup.DifALFalhaMov*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALInibUsu = (SUPERV_AVC(Cuba).Sup.DifALInibUsu*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALManual = (SUPERV_AVC(Cuba).Sup.DifALManual*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALInibPrev = (SUPERV_AVC(Cuba).Sup.DifALInibPrev*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALInibQueb = (SUPERV_AVC(Cuba).Sup.DifALInibQueb*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALIntervMov= (SUPERV_AVC(Cuba).Sup.DifALIntervMov*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALBandaMorta= (SUPERV_AVC(Cuba).Sup.DifALBandaMorta*(NCicCont-1))/NCicCont;
  }
  /* -- Dif. VAlvo x VLiquida por Inibicao Previsao -- */
  else if(EST_AVC(Cuba).InibeMovEaPrev eq VERDADEIRO)
  {
  	SUPERV_AVC(Cuba).Sup.DifALInibPrev = (SUPERV_AVC(Cuba).Sup.DifALInibPrev*(NCicCont-1)-
					(AVC.Ccont[Cuba].RAlvo * AVC.CcontMcp[Cuba].ICicContlMedCuba + AVC.Param[Cuba].Bemf) +
						AVC.CcontMcp[Cuba].VCicContlLiq)/NCicCont;

  	SUPERV_AVC(Cuba).Sup.DifALFalhaMov = (SUPERV_AVC(Cuba).Sup.DifALFalhaMov*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALInibUsu = (SUPERV_AVC(Cuba).Sup.DifALInibUsu*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALManual = (SUPERV_AVC(Cuba).Sup.DifALManual*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALInibQueb = (SUPERV_AVC(Cuba).Sup.DifALInibQueb*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALIntervMov= (SUPERV_AVC(Cuba).Sup.DifALIntervMov*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALBandaMorta= (SUPERV_AVC(Cuba).Sup.DifALBandaMorta*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALDesvio= (SUPERV_AVC(Cuba).Sup.DifALDesvio*(NCicCont-1))/NCicCont;
  }
  /* -- Dif. VAlvo x VLiquida por Inibicao Quebrada -- */
  else if(EST_AVC(Cuba).Quebrada eq VERDADEIRO)
  {
  	SUPERV_AVC(Cuba).Sup.DifALInibQueb = (SUPERV_AVC(Cuba).Sup.DifALInibQueb*(NCicCont-1)-
					(AVC.Ccont[Cuba].RAlvo * AVC.CcontMcp[Cuba].ICicContlMedCuba + AVC.Param[Cuba].Bemf) +
						AVC.CcontMcp[Cuba].VCicContlLiq)/NCicCont;

  	SUPERV_AVC(Cuba).Sup.DifALFalhaMov = (SUPERV_AVC(Cuba).Sup.DifALFalhaMov*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALInibUsu = (SUPERV_AVC(Cuba).Sup.DifALInibUsu*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALManual = (SUPERV_AVC(Cuba).Sup.DifALManual*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALInibPrev = (SUPERV_AVC(Cuba).Sup.DifALInibPrev*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALIntervMov= (SUPERV_AVC(Cuba).Sup.DifALIntervMov*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALBandaMorta= (SUPERV_AVC(Cuba).Sup.DifALBandaMorta*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALDesvio= (SUPERV_AVC(Cuba).Sup.DifALDesvio*(NCicCont-1))/NCicCont;
  }
  /* -- Dif. VAlvo x VLiquida por Efeito Move -- */
  else if(EST_AVC(Cuba).EfeitoMove eq VERDADEIRO)
  {
  	SUPERV_AVC(Cuba).Sup.DifALIntervMov= (SUPERV_AVC(Cuba).Sup.DifALIntervMov*(NCicCont-1)-
					(AVC.Ccont[Cuba].RAlvo * AVC.CcontMcp[Cuba].ICicContlMedCuba + AVC.Param[Cuba].Bemf) +
						AVC.CcontMcp[Cuba].VCicContlLiq)/NCicCont;

  	SUPERV_AVC(Cuba).Sup.DifALFalhaMov = (SUPERV_AVC(Cuba).Sup.DifALFalhaMov*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALInibUsu = (SUPERV_AVC(Cuba).Sup.DifALInibUsu*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALManual = (SUPERV_AVC(Cuba).Sup.DifALManual*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALInibPrev = (SUPERV_AVC(Cuba).Sup.DifALInibPrev*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALInibQueb = (SUPERV_AVC(Cuba).Sup.DifALInibQueb*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALBandaMorta= (SUPERV_AVC(Cuba).Sup.DifALBandaMorta*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALDesvio= (SUPERV_AVC(Cuba).Sup.DifALDesvio*(NCicCont-1))/NCicCont;
  }
  /* -- Dif. VAlvo x VLiquida na Banda Morta -- */
  else
  {
  	SUPERV_AVC(Cuba).Sup.DifALBandaMorta= (SUPERV_AVC(Cuba).Sup.DifALBandaMorta*(NCicCont-1)-
					(AVC.Ccont[Cuba].RAlvo * AVC.CcontMcp[Cuba].ICicContlMedCuba + AVC.Param[Cuba].Bemf) +
						AVC.CcontMcp[Cuba].VCicContlLiq)/NCicCont;

  	SUPERV_AVC(Cuba).Sup.DifALFalhaMov = (SUPERV_AVC(Cuba).Sup.DifALFalhaMov*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALInibUsu = (SUPERV_AVC(Cuba).Sup.DifALInibUsu*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALManual = (SUPERV_AVC(Cuba).Sup.DifALManual*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALInibPrev = (SUPERV_AVC(Cuba).Sup.DifALInibPrev*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALInibQueb = (SUPERV_AVC(Cuba).Sup.DifALInibQueb*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALIntervMov= (SUPERV_AVC(Cuba).Sup.DifALIntervMov*(NCicCont-1))/NCicCont;
  	SUPERV_AVC(Cuba).Sup.DifALDesvio= (SUPERV_AVC(Cuba).Sup.DifALDesvio*(NCicCont-1))/NCicCont;
  }


  PosicaoGlobal=61;

  /* -- *************** Dados medios de turno ******************* -- */
  NCicCont = SUPERV_AVC_TURNO(Cuba).NCContPotDia;

  /* -- Resistencia alvo media do dia -- */
  if (EST_AVC(Cuba).EstadoCuba eq CUBA_DESLIGADA)
	/* RAlvo = 0 */
	SUPERV_AVC_TURNO(Cuba).RAlvoDia=SUPERV_AVC_TURNO(Cuba).RAlvoDia*
									(NCicCont-1)/NCicCont;
  else
	SUPERV_AVC_TURNO(Cuba).RAlvoDia=(SUPERV_AVC_TURNO(Cuba).RAlvoDia*
					(NCicCont-1)+AVC.Ccont[Cuba].RAlvo)/NCicCont;
  /* -- Resistencia media bruta do dia -- */
  SUPERV_AVC_TURNO(Cuba).RDiaBruta=(SUPERV_AVC_TURNO(Cuba).RDiaBruta*
					(NCicCont-1)+AVC.CcontMcp[Cuba].RCicContlBruta)/NCicCont;
  /* -- Resistencia media liquida do dia -- */
  SUPERV_AVC_TURNO(Cuba).RDiaLiq=(SUPERV_AVC_TURNO(Cuba).RDiaLiq*(NCicCont-1)+
					AVC.CcontMcp[Cuba].RCicContlLiq)/NCicCont;
  /* -- Tensao media bruta do dia -- */
  SUPERV_AVC_TURNO(Cuba).VDiaBruta=(SUPERV_AVC_TURNO(Cuba).VDiaBruta*
					(NCicCont-1)+AVC.CcontMcp[Cuba].VCicContlBruta)/NCicCont;
  /* -- Tensao media liquida do dia -- */
  SUPERV_AVC_TURNO(Cuba).VDiaLiq=(SUPERV_AVC_TURNO(Cuba).VDiaLiq*(NCicCont-1)+
					AVC.CcontMcp[Cuba].VCicContlLiq)/NCicCont;
  /* -- Tensao setpoint media do dia -- */
  SUPERV_AVC_TURNO(Cuba).VSetPointDia=(SUPERV_AVC_TURNO(Cuba).VSetPointDia*
					(NCicCont-1)+AVC.Ccont[Cuba].VSetPoint)/NCicCont;
  /* -- Bemf medio do dia -- */
  SUPERV_AVC_TURNO(Cuba).BemfDia=(SUPERV_AVC_TURNO(Cuba).BemfDia*(NCicCont-1)+
					AVC.Param[Cuba].Bemf)/NCicCont;
}

/*
--------------------------------------------------------------------------------
| CalcEa - Calcula valores medios diarios relativos a Ea da cuba dada.         |
--------------------------------------------------------------------------------
*/
void CalcEa(int Cuba)
{
  int EaNumLDia;


  SUPERV_AVC(Cuba).Sup.TotalEA24h = SUPERV_AVC(Cuba).ContIntEa[0] +
									SUPERV_AVC(Cuba).ContIntEa[1] +
									SUPERV_AVC(Cuba).ContIntEa[2];

  /* -- Tensao bruta de efeito anodico no dia -- */
  /* -- *************** Dados medios diarios ******************* -- */
  EaNumLDia = SUPERV_AVC(Cuba).EaNumLDia;
  if (EaNumLDia ne 0)
  {
	SUPERV_AVC(Cuba).EaVDiaBruta=SUPERV_AVC(Cuba).EaVDiaTotBruta/EaNumLDia;
	/* -- Tensao liquida de efeito anodico no dia -- */
	SUPERV_AVC(Cuba).EaVDiaLiq=SUPERV_AVC(Cuba).EaVDiaTotLiq/EaNumLDia;
	/* -- potencia de efeito anodico bruta no dia -- */
	SUPERV_AVC(Cuba).EaPotDiaBruta=SUPERV_AVC(Cuba).EaPotDiaTotBruta/EaNumLDia;
	/* -- potencia de efeito anodico liquida no dia -- */
	SUPERV_AVC(Cuba).EaPotDiaLiq=SUPERV_AVC(Cuba).EaPotDiaTotLiq/EaNumLDia;
  }
  /* -- *************** Dados medios de turno ******************* -- */
  EaNumLDia = SUPERV_AVC_TURNO(Cuba).EaNumLDia;
  PosicaoGlobal=62;

  if (EaNumLDia ne 0)
  {
	SUPERV_AVC_TURNO(Cuba).EaVDiaBruta=SUPERV_AVC_TURNO(Cuba).EaVDiaTotBruta/EaNumLDia;
	/* -- Tensao liquida de efeito anodico no dia -- */
	SUPERV_AVC_TURNO(Cuba).EaVDiaLiq=SUPERV_AVC_TURNO(Cuba).EaVDiaTotLiq/EaNumLDia;
	/* -- potencia de efeito anodico bruta no dia -- */
	SUPERV_AVC_TURNO(Cuba).EaPotDiaBruta=SUPERV_AVC_TURNO(Cuba).EaPotDiaTotBruta/EaNumLDia;
	/* -- potencia de efeito anodico liquida no dia -- */
	SUPERV_AVC_TURNO(Cuba).EaPotDiaLiq=SUPERV_AVC_TURNO(Cuba).EaPotDiaTotLiq/EaNumLDia;
  }

#ifdef	CBA_120KAII_III
  if ((HoraAtualCtrl - AVC.Ea[Cuba].EaHoraInicio) > (AVC.Param[Cuba].EaAtrasoMax*60L))
  {
	SUPERV_AVC(Cuba).AtrasoEa = VERDADEIRO;
	SUPERV_AVC_TURNO(Cuba).AtrasoEa = VERDADEIRO;
  }
#endif

  if ((HoraAtualCtrl - AVC.Ea[Cuba].EaHoraInicio) > (AVC.Param[Cuba].EaAtrasoMax*60L))
  {
	AVC.User1[Cuba].AtrasouEa = VERDADEIRO;
  }

}


/*
--------------------------------------------------------------------------------
| CalcVDesvForaCont - Calcula valores medios diarios relativos a Desvio de     |
|                     tensao e fora de leitura da cuba dada.                   |
--------------------------------------------------------------------------------
*/
void CalcVDesvForaCont(int Cuba)
{
  float	v_cont;

  if (((EST_AVC(Cuba).ChaveAutMan eq MANUAL) or
	   (EST_AVC(Cuba).ChaveLocRem eq LOCAL)) and
	   ((HoraAtualCtrl-AVC.Cleit[Cuba].HoraUltSelMan) > 0l))
  {
	/* Inicio Alteracao - Carlos - 23/06/99 */
	/* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
	v_cont = ((AVC.Ccont[Cuba].RAlvo-
		AVC.CcontMcp[Cuba].RCicContlLiq)*AVC.Ccont[Cuba].INominalCuba);
#else
	v_cont = ((AVC.Ccont[Cuba].RAlvo-
		AVC.CcontMcp[Cuba].RCicContlLiq)*AVL.INominal);
#endif
	/* Fim Alteracao - Carlos - 23/06/99 */

	/* -- *************** Dados medios diarios ******************* -- */
	SUPERV_AVC(Cuba).VForaContDia += v_cont;
	SUPERV_AVC(Cuba).ForaContDurDia += IntervCicContSeg;
	/* -- *************** Dados medios de turno ******************* -- */
	SUPERV_AVC_TURNO(Cuba).VForaContDia += v_cont;
	SUPERV_AVC_TURNO(Cuba).ForaContDurDia += IntervCicContSeg;
  }
  else
	if ((EST_AVC(Cuba).DesvioTensao eq VERDADEIRO) and
		(EST_AVC(Cuba).Ea eq FALSO) and
		(EST_AVC(Cuba).ChaveAutMan eq AUTOMATICO) and
		(EST_AVC(Cuba).ChaveLocRem eq REMOTO))
	{
 	 	PosicaoGlobal=63;

	  /* Inicio Alteracao - Carlos - 23/06/99 */
	  /* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
	  v_cont = ((AVC.Ccont[Cuba].RAlvo-
		  AVC.CcontMcp[Cuba].RCicContlLiq)*AVC.Ccont[Cuba].INominalCuba);
#else
	  v_cont = ((AVC.Ccont[Cuba].RAlvo-
		  AVC.CcontMcp[Cuba].RCicContlLiq)*AVL.INominal);
#endif
	  /* Fim Alteracao - Carlos - 23/06/99 */
	  /* -- *************** Dados medios diarios ******************* -- */
	  SUPERV_AVC(Cuba).VDesvDia += v_cont;
	  SUPERV_AVC(Cuba).VDesvDurDia += IntervCicContSeg;
	  /* -- *************** Dados medios de turno ******************* -- */
	  SUPERV_AVC_TURNO(Cuba).VDesvDia += v_cont;
	  SUPERV_AVC_TURNO(Cuba).VDesvDurDia += IntervCicContSeg;
	}
}

/*
--------------------------------------------------------------------------------
| CalcDuracoes - Calcula duracao de ruido e fora de leitura, numero de corridas|
|                e quebradas, numero de movimentacoes de anodo e outros parame-|
|                tros para a cuba dada.                                        |
--------------------------------------------------------------------------------
*/
void CalcDuracoes(int Cuba)
{
  if (EST_AVC(Cuba).RuidoLent eq VERDADEIRO)
  {
	/* -- *************** Dados medios diarios ******************* -- */
	SUPERV_AVC(Cuba).RLentDurDia=SUPERV_AVC(Cuba).RLentDurDia+IntervCicContSeg;
	/* -- *************** Dados medios de turno ******************* -- */
	SUPERV_AVC_TURNO(Cuba).RLentDurDia=SUPERV_AVC_TURNO(Cuba).RLentDurDia+IntervCicContSeg;
  }
  if (EST_AVC(Cuba).RuidoRap eq VERDADEIRO)
  {
	/* -- *************** Dados medios diarios ******************* -- */
	SUPERV_AVC(Cuba).RRapDurDia=SUPERV_AVC(Cuba).RRapDurDia+IntervCicContSeg;
	/* -- *************** Dados medios de turno ******************* -- */
	SUPERV_AVC_TURNO(Cuba).RRapDurDia=SUPERV_AVC_TURNO(Cuba).RRapDurDia+IntervCicContSeg;
  }

  PosicaoGlobal=64;

  /* -- Verifica se houve corrida no ultimo ciclo de controle -- */
  if ( ((HoraAtualCtrl-AVC.Cleit[Cuba].HoraUltCorr) < IntervCicContSeg) and
	   (EST_AVC(Cuba).EfeitoCorr eq VERDADEIRO) )
  {
	/* -- *************** Dados medios diarios ******************* -- */
	SUPERV_AVC(Cuba).CorrNumDia=SUPERV_AVC(Cuba).CorrNumDia+1;
	/* -- *************** Dados medios de turno ******************* -- */
	SUPERV_AVC_TURNO(Cuba).CorrNumDia=SUPERV_AVC_TURNO(Cuba).CorrNumDia+1;
  }
  /* -- Verifica se houve quebrada no ultimo ciclo de controle -- */
  if ( ((HoraAtualCtrl-AVC.Cleit[Cuba].HoraUltQueb) < IntervCicContSeg) and
	   (EST_AVC(Cuba).Quebrada eq VERDADEIRO) )
  {
	/* -- *************** Dados medios diarios ******************* -- */
	SUPERV_AVC(Cuba).QuebNumDia=SUPERV_AVC(Cuba).QuebNumDia+1;
	/* -- *************** Dados medios de turno ******************* -- */
	SUPERV_AVC_TURNO(Cuba).QuebNumDia=SUPERV_AVC_TURNO(Cuba).QuebNumDia+1;
  }

  /* -- A CONTABILIZACAO DE MOVIMENTACOES PASSOU A SER FEITA NO MODULO
		REC_CHAVES AO RECEBER A INDICACAO DE CONFIRMACAO DE MOVIMENTACAO -- */
}

/*
--------------------------------------------------------------------------------
| CalcRuido - Faz os calculos referentes aos valores utilizados no relatorio   |
|             historico de ruido para a cuba dada.                             |
--------------------------------------------------------------------------------
*/
void CalcRuido(int Cuba)
{
  int	TemRuido,ContRDia;
  float IncRuido;

  TemRuido=FALSO;
  IncRuido=0.0;
  /* -- Tratamento para Ruido Lento Fraco e Forte -- */
  if ( (EST_AVC(Cuba).RuidoLent eq VERDADEIRO) and
	   (AVC.Param[Cuba].HabIncRLent eq VERDADEIRO) )
  {
	TemRuido=VERDADEIRO;
	IncRuido=AVC.Ccont[Cuba].IncRlent;
	if (AVC.Ruido[Cuba].TipoRLent <= RUIDO_NIVEL3)
	{ /* os 3 primeiros niveis sao classificados como fracos para contabilizacao estatistica */
	  /* -- *************** Dados medios diarios ******************* -- */
	  /* -- duracao em minutos -- */
	  SUPERV_AVC(Cuba).RLentFraDurDia=SUPERV_AVC(Cuba).RLentFraDurDia+
		 (IntervCicContSeg/60);
	  ContRDia=SUPERV_AVC(Cuba).RLentFraDurDia/(IntervCicContSeg/60);
	  SUPERV_AVC(Cuba).RLentFracoDia=
		(SUPERV_AVC(Cuba).RLentFracoDia*(ContRDia-1)+
		 AVC.Ruido[Cuba].RlentCContVal)/ContRDia;
	  SUPERV_AVC(Cuba).RLentFraIncDia=
		(SUPERV_AVC(Cuba).RLentFraIncDia*(ContRDia-1)+
		 AVC.Ccont[Cuba].IncRlent)/ContRDia;

	  /* -- *************** Dados medios de turno ******************* -- */
	  /* -- duracao em minutos -- */
	  SUPERV_AVC_TURNO(Cuba).RLentFraDurDia=SUPERV_AVC_TURNO(Cuba).RLentFraDurDia+
		 (IntervCicContSeg/60);
	  ContRDia=SUPERV_AVC_TURNO(Cuba).RLentFraDurDia/(IntervCicContSeg/60);
	  SUPERV_AVC_TURNO(Cuba).RLentFracoDia=
		(SUPERV_AVC_TURNO(Cuba).RLentFracoDia*(ContRDia-1)+
		 AVC.Ruido[Cuba].RlentCContVal)/ContRDia;
	  SUPERV_AVC_TURNO(Cuba).RLentFraIncDia=
		(SUPERV_AVC_TURNO(Cuba).RLentFraIncDia*(ContRDia-1)+
		 AVC.Ccont[Cuba].IncRlent)/ContRDia;
  	PosicaoGlobal=64;

	}
	else
	{ /* os 2 ultimos niveis sao classificados como fortes para contabilizacao estatistica */
	  /* -- *************** Dados medios diarios ******************* -- */
	  /* -- duracao em minutos -- */
	  SUPERV_AVC(Cuba).RLentForDurDia=SUPERV_AVC(Cuba).RLentForDurDia+
		 (IntervCicContSeg/60);
	  ContRDia=SUPERV_AVC(Cuba).RLentForDurDia/(IntervCicContSeg/60);
	  SUPERV_AVC(Cuba).RLentForteDia=
		(SUPERV_AVC(Cuba).RLentForteDia*(ContRDia-1)+
		 AVC.Ruido[Cuba].RlentCContVal)/ContRDia;
	  SUPERV_AVC(Cuba).RLentForIncDia=
		(SUPERV_AVC(Cuba).RLentForIncDia*(ContRDia-1)+
		 AVC.Ccont[Cuba].IncRlent)/ContRDia;

	  /* -- *************** Dados medios de turno ******************* -- */
	  /* -- duracao em minutos -- */
	  SUPERV_AVC_TURNO(Cuba).RLentForDurDia=SUPERV_AVC_TURNO(Cuba).RLentForDurDia+
		 (IntervCicContSeg/60);
	  ContRDia=SUPERV_AVC_TURNO(Cuba).RLentForDurDia/(IntervCicContSeg/60);
	  SUPERV_AVC_TURNO(Cuba).RLentForteDia=
		(SUPERV_AVC_TURNO(Cuba).RLentForteDia*(ContRDia-1)+
		 AVC.Ruido[Cuba].RlentCContVal)/ContRDia;
	  SUPERV_AVC_TURNO(Cuba).RLentForIncDia=
		(SUPERV_AVC_TURNO(Cuba).RLentForIncDia*(ContRDia-1)+
		 AVC.Ccont[Cuba].IncRlent)/ContRDia;
	}
  }
  /* -- *************** Dados medios diarios ******************* -- */
  ++SUPERV_AVC(Cuba).ContRLentNormDia;
  ContRDia=SUPERV_AVC(Cuba).ContRLentNormDia;
  SUPERV_AVC(Cuba).RLentNormDia=
		(SUPERV_AVC(Cuba).RLentNormDia*(ContRDia-1)+
		 AVC.Ruido[Cuba].RlentCContVal)/ContRDia;
  SUPERV_AVC(Cuba).Sup.SigLNormDia=
		(SUPERV_AVC(Cuba).Sup.SigLNormDia*(ContRDia-1)+
		 AVC.User2[Cuba].SigmaL_2m)/ContRDia;

  /* -- *************** Dados medios de turno ******************* -- */
  ++SUPERV_AVC_TURNO(Cuba).ContRLentNormDia;
  ContRDia=SUPERV_AVC_TURNO(Cuba).ContRLentNormDia;
  SUPERV_AVC_TURNO(Cuba).RLentNormDia=
		(SUPERV_AVC_TURNO(Cuba).RLentNormDia*(ContRDia-1)+
		 AVC.Ruido[Cuba].RlentCContVal)/ContRDia;
  SUPERV_AVC_TURNO(Cuba).Sup.SigLNormDia=
		(SUPERV_AVC_TURNO(Cuba).Sup.SigLNormDia*(ContRDia-1)+
		 AVC.User2[Cuba].SigmaL_2m)/ContRDia;

  /* -- Tratamento para Ruido Rapido Fraco e Forte -- */
  if ( (EST_AVC(Cuba).RuidoRap eq VERDADEIRO) and
	   (AVC.Param[Cuba].HabIncRRap eq VERDADEIRO) )
  {
  PosicaoGlobal=65;

	TemRuido=VERDADEIRO;
	IncRuido+=AVC.Ccont[Cuba].IncRrap;
	if (AVC.Ruido[Cuba].TipoRRap <= RUIDO_NIVEL3)
	{ /* os 3 primeiros niveis sao classificados como fracos para contabilizacao estatistica */
	  /* -- *************** Dados medios diarios ******************* -- */
	  /* -- duracao em minutos -- */
	  SUPERV_AVC(Cuba).RRapFraDurDia=SUPERV_AVC(Cuba).RRapFraDurDia+
		 (IntervCicContSeg/60);
	  ContRDia=SUPERV_AVC(Cuba).RRapFraDurDia/(IntervCicContSeg/60);
	  SUPERV_AVC(Cuba).RRapFracoDia=
		(SUPERV_AVC(Cuba).RRapFracoDia*(ContRDia-1)+
		 AVC.Ruido[Cuba].RrapCContVal)/ContRDia;
	  SUPERV_AVC(Cuba).RRapFraIncDia=
		(SUPERV_AVC(Cuba).RRapFraIncDia*(ContRDia-1)+
		 AVC.Ccont[Cuba].IncRrap)/ContRDia;

	  /* -- *************** Dados medios de turno ******************* -- */
	  /* -- duracao em minutos -- */
	  SUPERV_AVC_TURNO(Cuba).RRapFraDurDia=SUPERV_AVC_TURNO(Cuba).RRapFraDurDia+
		 (IntervCicContSeg/60);
	  ContRDia=SUPERV_AVC_TURNO(Cuba).RRapFraDurDia/(IntervCicContSeg/60);
	  SUPERV_AVC_TURNO(Cuba).RRapFracoDia=
		(SUPERV_AVC_TURNO(Cuba).RRapFracoDia*(ContRDia-1)+
		 AVC.Ruido[Cuba].RrapCContVal)/ContRDia;
	  SUPERV_AVC_TURNO(Cuba).RRapFraIncDia=
		(SUPERV_AVC_TURNO(Cuba).RRapFraIncDia*(ContRDia-1)+
		 AVC.Ccont[Cuba].IncRrap)/ContRDia;
	}
	else
	{ /* os 2 ultimos niveis sao classificados como fortes para contabilizacao estatistica */
	  /* -- *************** Dados medios diarios ******************* -- */
	  /* -- duracao em minutos -- */
	  SUPERV_AVC(Cuba).RRapForDurDia=SUPERV_AVC(Cuba).RRapForDurDia+
		 (IntervCicContSeg/60);
	  ContRDia=SUPERV_AVC(Cuba).RRapForDurDia/(IntervCicContSeg/60);
	  SUPERV_AVC(Cuba).RRapForteDia=
		(SUPERV_AVC(Cuba).RRapForteDia*(ContRDia-1)+
		 AVC.Ruido[Cuba].RrapCContVal)/ContRDia;
	  SUPERV_AVC(Cuba).RRapForIncDia=
		(SUPERV_AVC(Cuba).RRapForIncDia*(ContRDia-1)+
		 AVC.Ccont[Cuba].IncRrap)/ContRDia;

	  /* -- *************** Dados medios de turno ******************* -- */
	  /* -- duracao em minutos -- */
	  SUPERV_AVC_TURNO(Cuba).RRapForDurDia=SUPERV_AVC_TURNO(Cuba).RRapForDurDia+
		 (IntervCicContSeg/60);
	  ContRDia=SUPERV_AVC_TURNO(Cuba).RRapForDurDia/(IntervCicContSeg/60);
	  SUPERV_AVC_TURNO(Cuba).RRapForteDia=
		(SUPERV_AVC_TURNO(Cuba).RRapForteDia*(ContRDia-1)+
		 AVC.Ruido[Cuba].RrapCContVal)/ContRDia;
	  SUPERV_AVC_TURNO(Cuba).RRapForIncDia=
		(SUPERV_AVC_TURNO(Cuba).RRapForIncDia*(ContRDia-1)+
		 AVC.Ccont[Cuba].IncRrap)/ContRDia;
	}
  }
  PosicaoGlobal=66;

  /* -- *************** Dados medios diarios ******************* -- */
  ++SUPERV_AVC(Cuba).ContRRapNormDia;
  ContRDia=SUPERV_AVC(Cuba).ContRRapNormDia;
  SUPERV_AVC(Cuba).RRapNormDia=
		(SUPERV_AVC(Cuba).RRapNormDia*(ContRDia-1)+
		 AVC.Ruido[Cuba].RrapCContVal)/ContRDia;
  SUPERV_AVC(Cuba).Sup.SigSNormDia=
		(SUPERV_AVC(Cuba).Sup.SigSNormDia*(ContRDia-1)+
		 AVC.User2[Cuba].SigmaS_2m)/ContRDia;

  /* -- *************** Dados medios de turno ******************* -- */
  ++SUPERV_AVC_TURNO(Cuba).ContRRapNormDia;
  ContRDia=SUPERV_AVC_TURNO(Cuba).ContRRapNormDia;
  SUPERV_AVC_TURNO(Cuba).RRapNormDia=
		(SUPERV_AVC_TURNO(Cuba).RRapNormDia*(ContRDia-1)+
		 AVC.Ruido[Cuba].RrapCContVal)/ContRDia;
  SUPERV_AVC_TURNO(Cuba).Sup.SigSNormDia=
		(SUPERV_AVC_TURNO(Cuba).Sup.SigSNormDia*(ContRDia-1)+
		 AVC.User2[Cuba].SigmaS_2m)/ContRDia;

  if (TemRuido)
  {
	/* -- *************** Dados medios diarios ******************* -- */
	++SUPERV_AVC(Cuba).ContIncRuidoDia;

	/* -- *************** Dados medios de turno ******************* -- */
	++SUPERV_AVC_TURNO(Cuba).ContIncRuidoDia;
  }
  /* -- *************** Dados medios diarios ******************* -- */
  ContRDia=SUPERV_AVC(Cuba).NumCContDia;
  SUPERV_AVC(Cuba).IncRuidoDia=
		(SUPERV_AVC(Cuba).IncRuidoDia*(ContRDia-1)+IncRuido)/ContRDia;

  /* -- *************** Dados medios de turno ******************* -- */
  ContRDia=SUPERV_AVC_TURNO(Cuba).NumCContDia;
  SUPERV_AVC_TURNO(Cuba).IncRuidoDia=
		(SUPERV_AVC_TURNO(Cuba).IncRuidoDia*(ContRDia-1)+IncRuido)/ContRDia;
}

/*
--------------------------------------------------------------------------------
| CalcIncrementos - Calcula valores medios diarios relativos a incrementos
--------------------------------------------------------------------------------
*/
void CalcIncrementos(int Cuba)
{
  int Cont;

  /*-- Calcula valores diarios e de turno de incremento de corrida --*/ 
  if ((AVC.Ccont[Cuba].ContIncCorr ne -1) and
	  (AVC.Param[Cuba].IncCorrInic ne 0.0))
  {
	SUPERV_AVC(Cuba).DurIncCorrDia += IntervCicContSeg;
	Cont = (int) (SUPERV_AVC(Cuba).DurIncCorrDia / IntervCicContSeg);
	SUPERV_AVC(Cuba).IncCorrDia = (((SUPERV_AVC(Cuba).IncCorrDia * (Cont - 1)) +
					 AVC.Ccont[Cuba].IncCorr)/Cont);
	SUPERV_AVC_TURNO(Cuba).DurIncCorrDia += IntervCicContSeg;
	Cont = (int) (SUPERV_AVC(Cuba).DurIncCorrDia / IntervCicContSeg);
	SUPERV_AVC_TURNO(Cuba).IncCorrDia = (((SUPERV_AVC_TURNO(Cuba).IncCorrDia * (Cont - 1)) +
						   AVC.Ccont[Cuba].IncCorr)/Cont);
  }

  /*-- Calcula valores diarios e de turno de incremento de quebrada --*/ 
  if ((AVC.Ccont[Cuba].ContIncQueb ne -1) and
	  (AVC.Param[Cuba].IncQuebInic ne 0.0))
  {
	SUPERV_AVC(Cuba).DurIncQuebDia += IntervCicContSeg;
	Cont = (int) (SUPERV_AVC(Cuba).DurIncQuebDia / IntervCicContSeg);
	SUPERV_AVC(Cuba).IncQuebDia = (((SUPERV_AVC(Cuba).IncQuebDia * (Cont - 1)) +
					 AVC.Ccont[Cuba].IncQueb + AVC.Ccont[Cuba].IncUsuario)/Cont);
	SUPERV_AVC_TURNO(Cuba).DurIncQuebDia += IntervCicContSeg;
	Cont = (int) (SUPERV_AVC(Cuba).DurIncQuebDia / IntervCicContSeg);
	SUPERV_AVC_TURNO(Cuba).IncQuebDia = (((SUPERV_AVC_TURNO(Cuba).IncQuebDia * (Cont - 1)) +
						   AVC.Ccont[Cuba].IncQueb + AVC.Ccont[Cuba].IncUsuario)/Cont);
  }


  PosicaoGlobal=67;

  /*-- Calcula valores diarios e de turno de incremento de troca de pinos --*/ 
  if ((EST_AVC(Cuba).TrataTPinos eq VERDADEIRO) and
	 (AVC.Param[Cuba].IncTPinosInic ne 0.0))
  {
	SUPERV_AVC(Cuba).DurIncTPinosDia += IntervCicContSeg;
	Cont = (int) (SUPERV_AVC(Cuba).DurIncTPinosDia / IntervCicContSeg);
	SUPERV_AVC(Cuba).IncTPinosDia = (((SUPERV_AVC(Cuba).IncTPinosDia * (Cont - 1)) +
					 AVC.Ccont[Cuba].IncTPinos)/Cont);
	SUPERV_AVC_TURNO(Cuba).DurIncTPinosDia += IntervCicContSeg;
	Cont = (int) (SUPERV_AVC(Cuba).DurIncTPinosDia / IntervCicContSeg);
	SUPERV_AVC_TURNO(Cuba).IncTPinosDia = (((SUPERV_AVC_TURNO(Cuba).IncTPinosDia * (Cont - 1)) +
						   AVC.Ccont[Cuba].IncTPinos)/Cont);
  }

  /*-- Calcula valores diarios e de turno de incremento de usuario --*/ 
  if ((EST_AVC(Cuba).TrataIncUsuario eq VERDADEIRO) and
	 (AVC.Param[Cuba].IncUsuarioInic ne 0.0))
  {
	SUPERV_AVC(Cuba).DurIncUsuarioDia += IntervCicContSeg;
	Cont = (int) (SUPERV_AVC(Cuba).DurIncUsuarioDia / IntervCicContSeg);
	SUPERV_AVC(Cuba).IncUsuarioDia = (((SUPERV_AVC(Cuba).IncUsuarioDia * (Cont - 1)) +
					 AVC.Ccont[Cuba].IncUsuario)/Cont);
	SUPERV_AVC_TURNO(Cuba).DurIncUsuarioDia += IntervCicContSeg;
	Cont = (int) (SUPERV_AVC(Cuba).DurIncUsuarioDia / IntervCicContSeg);
	SUPERV_AVC_TURNO(Cuba).IncUsuarioDia = (((SUPERV_AVC_TURNO(Cuba).IncUsuarioDia * (Cont - 1)) +
						   AVC.Ccont[Cuba].IncUsuario)/Cont);
  }

  /*-- Calcula valores diarios e de turno de incremento de operacao --*/ 
  if (AVC.Ccont[Cuba].HabIncOper eq VERDADEIRO or EST_AVC(Cuba).Est.FormaBanho eq VERDADEIRO)
  {
	  SUPERV_AVC(Cuba).DurIncOperDia += IntervCicContSeg;
	  Cont = (int) (SUPERV_AVC(Cuba).DurIncOperDia / IntervCicContSeg);
	  SUPERV_AVC(Cuba).IncOperDia = (((SUPERV_AVC(Cuba).IncOperDia * (Cont - 1)) +
					 (SUPERV_AVC(Cuba).Sup.IncFBDia + AVC.Ccont[Cuba].IncOper))/Cont);
	  SUPERV_AVC_TURNO(Cuba).DurIncOperDia += IntervCicContSeg;
	  Cont = (int) (SUPERV_AVC(Cuba).DurIncOperDia / IntervCicContSeg);
	  SUPERV_AVC_TURNO(Cuba).IncOperDia = (((SUPERV_AVC_TURNO(Cuba).IncOperDia * (Cont - 1)) +
				   (SUPERV_AVC(Cuba).Sup.IncFBDia + AVC.Ccont[Cuba].IncOper))/Cont);
  }

  if (EST_AVC(Cuba).Est.FormaBanho eq VERDADEIRO)
  {
	  SUPERV_AVC(Cuba).Sup.DurIncFBDia += IntervCicContSeg;
	  Cont = (int) (SUPERV_AVC(Cuba).Sup.DurIncFBDia / IntervCicContSeg);
	  SUPERV_AVC(Cuba).Sup.IncFBDia = (((SUPERV_AVC(Cuba).Sup.IncFBDia * (Cont - 1)) +
					 AVC.User2[Cuba].IncFormaBanho)/Cont);
	  SUPERV_AVC_TURNO(Cuba).Sup.DurIncFBDia += IntervCicContSeg;
	  Cont = (int) (SUPERV_AVC(Cuba).Sup.DurIncFBDia / IntervCicContSeg);
	  SUPERV_AVC_TURNO(Cuba).Sup.IncFBDia = (((SUPERV_AVC_TURNO(Cuba).Sup.IncFBDia * (Cont - 1)) +
						   AVC.User2[Cuba].IncFormaBanho)/Cont);
  }	

  if (AVC.Ccont[Cuba].Rinc ne 0)
  {
	SUPERV_AVC(Cuba).DurIncTotDia += IntervCicContSeg;
	SUPERV_AVC_TURNO(Cuba).DurIncTotDia += IntervCicContSeg;
  }
  /*-- Calcula valores diarios e de turno de incremento total --*/ 
  Cont = SUPERV_AVC(Cuba).NumCContDia;
#ifdef INCREMENTO_RESISTENCIA
  SUPERV_AVC(Cuba).IncTotDia = (((SUPERV_AVC(Cuba).IncTotDia * (Cont - 1)) +
					 (AVC.Ccont[Cuba].Rinc))/Cont);
  Cont = SUPERV_AVC_TURNO(Cuba).NumCContDia;
  SUPERV_AVC_TURNO(Cuba).IncTotDia = (((SUPERV_AVC_TURNO(Cuba).IncTotDia * (Cont - 1)) +
						   (AVC.Ccont[Cuba].Rinc))/Cont);
#else

  /* Inicio Alteracao - Carlos - 23/06/99 */
  /* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
  SUPERV_AVC(Cuba).IncTotDia = (((SUPERV_AVC(Cuba).IncTotDia * (Cont - 1)) +
					 (AVC.Ccont[Cuba].Rinc * AVC.Ccont[Cuba].INominalCuba))/Cont);
  Cont = SUPERV_AVC_TURNO(Cuba).NumCContDia;
  SUPERV_AVC_TURNO(Cuba).IncTotDia = (((SUPERV_AVC_TURNO(Cuba).IncTotDia * (Cont - 1)) +
						   (AVC.Ccont[Cuba].Rinc * AVC.Ccont[Cuba].INominalCuba))/Cont);
#else
  SUPERV_AVC(Cuba).IncTotDia = (((SUPERV_AVC(Cuba).IncTotDia * (Cont - 1)) +
					 (AVC.Ccont[Cuba].Rinc * AVL.INominal))/Cont);
  Cont = SUPERV_AVC_TURNO(Cuba).NumCContDia;
  SUPERV_AVC_TURNO(Cuba).IncTotDia = (((SUPERV_AVC_TURNO(Cuba).IncTotDia * (Cont - 1)) +
						   (AVC.Ccont[Cuba].Rinc * AVL.INominal))/Cont);
#endif
  /* Fim Alteracao - Carlos - 23/06/99 */

#endif
}

/*
--------------------------------------------------------------------------------
| CalcHistLinha - Faz os calculos referentes aos valores utilizados no relato- |
|                 rio historico da linha.                                      |
--------------------------------------------------------------------------------
*/
void CalcHistLinha(void)
{
  int Cuba,NumCubasNorm,NumCubasLigPar,NumCicAtivoDia;
  float	RCubasDiaBruta;

  /* -- corrente media reserva da linha no dia -- */
  /* -- *************** Dados medios diarios ******************* -- */
  AVL.IMedDiaRes = (AVL.IMedDiaRes * (AVL.NCicAtivoDia-1) + AVL.ICicContlMedRes)/
				AVL.NCicAtivoDia;
  /* -- *************** Dados medios de turno ******************* -- */
  AVL_TURNO.IMedDiaRes = (AVL_TURNO.IMedDiaRes * (AVL_TURNO.NCicAtivoDia-1) +
				 AVL.ICicContlMedRes)/AVL_TURNO.NCicAtivoDia;

  NumCubasNorm = 0;
  NumCubasLigPar = 0;
  RCubasDiaBruta = 0.0;
  /* -- loop para todas as cubas -- */
  for (Cuba=0; Cuba<NumCubas; Cuba++)
  {
	SelecionaAvc(Cuba);
	/* -- Contabiliza numero de cubas normais neste ciclo -- */
	if (EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL)
	  NumCubasNorm += 1;
	else
	{
	  /* -- Contabiliza numero de cubas Ligadas e ou Partidas neste ciclo -- */
	  if (EST_AVC(Cuba).EstadoCuba eq CUBA_LIGADA)
		NumCubasLigPar += 1;
	  else
		if (EST_AVC(Cuba).EstadoCuba eq CUBA_PARTIDA)
		  NumCubasLigPar += 1;
	}
	if (EST_AVC(Cuba).EstadoCuba ne CUBA_DESLIGADA)
	  /* -- Resistencia total bruta de todas as cubas menos as desligadas -- */
	  RCubasDiaBruta += AVC.CcontMcp[Cuba].RCicContlBruta;
  }
  PosicaoGlobal=68;

  /* -- *************** Dados medios diarios ******************* -- */
  NumCicAtivoDia = AVL.NCicAtivoDia;
  /* -- Contabiliza numero de cubas normais no dia -- */
  AVL.CubasNormDia = (AVL.CubasNormDia * (NumCicAtivoDia-1) + NumCubasNorm)/
				NumCicAtivoDia;
  /* -- Contabiliza numero de cubas Ligadas e ou Partidas no dia -- */
  AVL.CubasLigParDia = (AVL.CubasLigParDia*(NumCicAtivoDia-1) + NumCubasLigPar)/
				NumCicAtivoDia;
  /* -- Resistencia total bruta media de todas as cubas menos as desligadas no dia -- */
  AVL.RCubasDiaBruta = (AVL.RCubasDiaBruta*(NumCicAtivoDia-1)+RCubasDiaBruta)/
				NumCicAtivoDia;

  /* -- *************** Dados medios de turno ******************* -- */
  NumCicAtivoDia = AVL_TURNO.NCicAtivoDia;
  /* -- Contabiliza numero de cubas normais no dia -- */
  AVL_TURNO.CubasNormDia = (AVL_TURNO.CubasNormDia * (NumCicAtivoDia-1) + NumCubasNorm)/
				NumCicAtivoDia;
  /* -- Contabiliza numero de cubas Ligadas e ou Partidas no dia -- */
  AVL_TURNO.CubasLigParDia = (AVL_TURNO.CubasLigParDia*(NumCicAtivoDia-1) + NumCubasLigPar)/
				NumCicAtivoDia;
  /* -- Resistencia total bruta media de todas as cubas menos as desligadas no dia -- */
  AVL_TURNO.RCubasDiaBruta = (AVL_TURNO.RCubasDiaBruta*(NumCicAtivoDia-1)+RCubasDiaBruta)/
				NumCicAtivoDia;
}

/* -- Fim arquivo mcc_superv.c -- */
