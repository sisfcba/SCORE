/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.1

	PROJETO		: CBA - Companhia Brasileira de Aluminio SA

	SISTEMA		: SALAS 120KA II e III

	ARQUIVO		: PFRot.c

	CONTEUDO	: Biblioteca de funcoes do Algoritmo de alimentacao da CBA

	AUTOR		: Ricardo Teixeira Leite Mourao / Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	02/01/97

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
Data     | Descricao                                            | Autor 
-------------------------------------------------------------------------------
02/01/97 | Edicao inicial                                       | Ricardo-Leonel
-------------------------------------------------------------------------------
16/12/97 | Desmembrado teste de TEfeitoMove para TEfeitoMoveCima| Carlos
         | e TEfeitoMoveBaixo.                                  |
-------------------------------------------------------------------------------
15/01/99 | Alteracao conforme proposta 1006CA                   | Ricardo-Leonel
-------------------------------------------------------------------------------
01/09/17 | TK-ALIM - Preparac�o Toolkit Alimentacao             | Carlos
-------------------------------------------------------------------------------
$Id: PFRot.c,v 1.2 2004/07/05 19:10:24 leo Exp $

$Log: PFRot.c,v $
Revision 1.2  2004/07/05 19:10:24  leo
Correcao comparacao com TEfeitoTPinos (de segundos para minutos).

******************************************************************************/
/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include	<McpPF.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<time.h>
#include    <math.h>

/*
-------------------------------------------------------------------------------
                           Variaveis Globais
-------------------------------------------------------------------------------
*/
/* -- Apontadores para as tabelas comuns -- */
#include	<VarsComum.h>

/*
-------------------------------------------------------------------------------
                               Rotinas
-------------------------------------------------------------------------------
*/


/*
--------------------------------------------------------------------------------
  Calc_ConcBalanco - Calcula concentracao a partir do balanco de alumina
--------------------------------------------------------------------------------
*/
float Calc_ConcBalanco(int cuba)
{
  float consumido;
  float fornecido;
  float concentracao;
  byte Seq;

  //calcula quantidade de alumina consumida
  consumido= AVC.User1[cuba].Integral * AVC.User1[cuba].EfiCurr * K_CONSUMO;
  //calcula quantidade de alumina fornecida
  /* -- Alteracao - Inicio - Robson - 15/11/2000 - Quantidades diferentes por acionador -- */
  //Seq = AVC.ParUser1[cuba].Sequencia[AVC.User1[cuba].PassoCadencia] - 1;
  Seq = abs(EST_AVC(cuba).Est.LadoProxPF - 1);
  fornecido= AVC.ParUser1[cuba].QuantAlumCarga[Seq] * AVC.User1[cuba].NumAciona;
  /* -- Alteracao - Fim - Robson - 15/11/2000 - Quantidades diferentes por acionador -- */

  //calcula concentracao baseado no balanco de alumina
  concentracao= AVC.User1[cuba].ConcCheckAnt +
                ((fornecido-consumido)/AVC.ParUser1[cuba].MassaBanho);

  return(concentracao);
} /* Calc_ConcBalanco */


/*
--------------------------------------------------------------------------------
  Calc_ConcDerivada - Calcula concentracao a partir da derivada da resistencia
--------------------------------------------------------------------------------
*/
float Calc_ConcDerivada(int cuba)
{
  int i,pontos=NUM_DERIV_RES;
  float media=0;

  
  /* Referencia todas as derivadas a um mesmo instante e calcula a media 
     das mesmas */
  for (i=0; i<NUM_DERIV_RES; ++i)
  {
    AVC.User1[cuba].Conc[i]= CalcConc(cuba,(double)AVC.User1[cuba].Deriv[i]); 
    AVC.User1[cuba].Conc[i]-= ((NUM_DERIV_RES-1)-i)*AVC.ParUser1[cuba].ConsumoResAlim;

    /* Verifica se o valor da concetracao e aceitavel */    
    if (AVC.User1[cuba].Conc[i] < AVC.ParUser1[cuba].MinConc)
    {
      AVC.User1[cuba].Conc[i]= AVC.ParUser1[cuba].MinConc;
      pontos--;
    }
    else if (AVC.User1[cuba].Conc[i] > AVC.ParUser1[cuba].MaxConc)
    {
      AVC.User1[cuba].Conc[i]= AVC.ParUser1[cuba].MaxConc;
      pontos--;
    }

    media+= AVC.User1[cuba].Conc[i];
  }

  media /= NUM_DERIV_RES;

  /* Para validar concentracao calculada, no maximo dois pontos calculados
     podem estar fora da faixa aceitavel */
  if (pontos >= (NUM_DERIV_RES - 2))
    return(media);

  return(1000.0);  
} /* Calc_ConcDerivada */


/*
--------------------------------------------------------------------------------
  CalcConc - Calcula a concetracao da cuba com base na derivada da resistencia
             de alimentacao.
--------------------------------------------------------------------------------
*/
float CalcConc(int cuba,double deriv)
{
  int i,j,index;
  double aux;
  double concentra=0;

  for(i=0;i<=AVC.ParUser1[cuba].PolOrd;++i)
  {
    index= AVC.ParUser1[cuba].PolOrd-i;

    aux=1;
    for(j=0;j<index;++j)
      aux *= deriv;

    concentra += aux*AVC.ParUser1[cuba].Poly[i];//Poly[index];
  }

  concentra /=100.0; //muda p/ intervalo (0-1)

  return((float)concentra);
} /* CalcConc */


/*
--------------------------------------------------------------------------------
  armazena - Coloca resistencias p/ calcula da derivada em buffer circular
--------------------------------------------------------------------------------
*/
void armazena(int cuba,float resist)
{
  //armazena valor da resistencia no buffer circular
  memmove(&AVC.User1[cuba].Resistencia[0],&AVC.User1[cuba].Resistencia[1],
  (sizeof(AVC.User1[cuba].Resistencia)-sizeof(AVC.User1[cuba].Resistencia[0])));

  //armazena resistencia em milivolts
  AVC.User1[cuba].Resistencia[3]= resist*1e6;//armazena resistencia em uOhms
  AVC.User1[cuba].ResIndex++;

  //quando o buffer for preenchido pela primeira vez, sinaliza por variavel
  if (AVC.User1[cuba].ResIndex >= TAM_BUF_RES)
  {
    AVC.User1[cuba].Preenchido= VERDADEIRO;
  }

  //limita indice do buffer para tamanho do buffer circular
  AVC.User1[cuba].ResIndex %= TAM_BUF_RES;
} /* armazena */

/*
--------------------------------------------------------------------------------
  Calc_Check - Calcula novo intervalo p/ acionamento do point feeder e nova 
               eficiencia de corrente. Calcula tambem concentracao valida p/ 
               o check e o numero de bateladas para chegar novamente na 
               concentracao nominal
--------------------------------------------------------------------------------
*/
void Calc_Check(int cuba,float concder,float concbal)
{
  float EfiCurrAux;
  float DeltaEfiCurr;
  byte Seq;

  //Calcula nova eficiencia de corrente
  EfiCurrAux= (((concbal-concder)*AVC.ParUser1[cuba].MassaBanho)/
              (AVC.User1[cuba].Integral*K_CONSUMO))+AVC.User1[cuba].EfiCurr;

  //Calcula variacao relativa da eficiencia de corrente
  DeltaEfiCurr= (EfiCurrAux-AVC.User1[cuba].EfiCurr)/AVC.User1[cuba].EfiCurr;

  //Limitar variacoes grandes da eficiencia de corrente
  if (fabs((double)DeltaEfiCurr) > (double)AVC.ParUser1[cuba].MaxDeltaEfiCurr)
  {
    if (DeltaEfiCurr < 0) //verifica sinal do erro
    {
      EfiCurrAux = (1-AVC.ParUser1[cuba].MaxDeltaEfiCurr)*
                   AVC.User1[cuba].EfiCurr;
    }
    else
    {
      EfiCurrAux = (1+AVC.ParUser1[cuba].MaxDeltaEfiCurr)*
                   AVC.User1[cuba].EfiCurr;
    }
  }

  /* Verifica se a nova eficiencia de corrente esta dentro dos limites
     estipulados */
  if ((EfiCurrAux > AVC.ParUser1[cuba].MaxEfiCurr) or 
      (EfiCurrAux < AVC.ParUser1[cuba].MinEfiCurr))
  {
    EfiCurrAux= AVC.ParUser1[cuba].EfiCurrIni; //valor tipico para Eficiencia de Corrente
	/* Gerar evento para problema c/ EfiCurr??????????????? RTLM */
  }

  GeraEvento(EV_FIMCHECK,cuba,-1, (float)(concder*100), (float)(AVC.User1[cuba].ConcCheckAtual*100),
				(float)(concbal*100), (float)(EfiCurrAux*100), (float)(AVC.User1[cuba].EfiCurr*100));

  //Armazena nova eficiencia de corrente na base de dados
  AVC.User1[cuba].EfiCurr= EfiCurrAux;

  //Armazena concentracao de check
  AVC.User1[cuba].ConcCheckAnt= AVC.User1[cuba].ConcCheckAtual;
  AVC.User1[cuba].ConcCheckAtual= concder;

  //recalcula integral da corrente entre acionamentos sucessivos do point feeder
/* -- Alteracao - Inicio - Robson - 15/11/2000 - Quantidades diferentes por acionador -- */
//  Seq = AVC.ParUser1[cuba].Sequencia[AVC.User1[cuba].PassoCadencia] - 1;
  Seq = abs(EST_AVC(cuba).Est.LadoProxPF - 1);
  AVC.User1[cuba].IntervCurr= AVC.ParUser1[cuba].QuantAlumCarga[Seq]/
                 (K_CONSUMO*EfiCurrAux);
/* -- Alteracao - Fim - Robson - 15/11/2000 - Quantidades diferentes por acionador -- */
  
} /* Calc_Check */

/*
--------------------------------------------------------------------------------
  calc_deriv - calcula a derivada da resistencia filtrada com base nas ulti-
               mas TAM_BUF_RES resistencias medidas
--------------------------------------------------------------------------------
*/
float calc_deriv(int cuba)
{
  int i;
  float x[4];
  float sumx=0;
  float sumx2=0;
  float sumy=0;
  float sumxy=0;
  float deriv;
  
  for (i=0;i<TAM_BUF_RES;++i)
  {
    x[i]= -i*AVC.ParUser1[cuba].ConsumoResAlim*100.0;//transforma consumo de (0-1) em (0-100)%
    sumx += x[i];  
    sumx2 += x[i]*x[i]; 
    sumy += AVC.User1[cuba].Resistencia[i];
    sumxy += x[i]*AVC.User1[cuba].Resistencia[i];
  }

  //calcula a derivada (inclinacao da melhor reta (Least Square)
  deriv= ((TAM_BUF_RES*sumxy) - (sumx*sumy))/
         ((TAM_BUF_RES*sumx2) - (sumx*sumx));

  return(deriv);  
} /* calc_deriv */

/*
--------------------------------------------------------------------------------
  armazena_deriv - Coloca derivadas para calculo do check no buffer
--------------------------------------------------------------------------------
*/
void armazena_deriv(int cuba,float deriv)
{
  //armazena valor da resistencia no buffer circular
  memmove(&AVC.User1[cuba].Deriv[0],&AVC.User1[cuba].Deriv[1],
  (sizeof(AVC.User1[cuba].Deriv)-sizeof(AVC.User1[cuba].Deriv[0])));

  //armazena derivada no buffer
  AVC.User1[cuba].Deriv[NUM_DERIV_RES-1]= deriv;
  AVC.User1[cuba].DerIndex++;

} /* armazena_deriv */

/*
--------------------------------------------------------------------------------
  FiltroResAlim - Implementa o filtro utilizado para calcular a resistencia
                  de alimentacao
--------------------------------------------------------------------------------
*/
float FiltroResAlim(int cuba)
{
  AVC.User1[cuba].ResFilt *= AVC.ParUser1[cuba].KSuaveAlim;
  AVC.User1[cuba].ResFilt += ((1.0-AVC.ParUser1[cuba].KSuaveAlim)*
                            ((double)AVC.Cleit[cuba].Rinst));

  return((float)AVC.User1[cuba].ResFilt);
} /* FiltroResAlim */

/*
-------------------------------------------------------------------------------
  ComumEstados - Executa calculos relacionados aa integral da corrente. Estes
                 calculos sao comuns aos estados do algoritmo.
-------------------------------------------------------------------------------
*/
void ComumEstados(int cuba)
{
  float trapezio;

  /* Calcula parcela a ser acrescentada na integral da corrente */
  trapezio= TRAPEZIO(AVL.Iinst,IinstOld,IntervLeit);

  /* Incrementa integral parcial */   
  AVC.User1[cuba].IntPar += trapezio;

  /* Incrementa integral da corrente */
  AVC.User1[cuba].Integral +=trapezio;

  /* Transforma parcela da integral em quilogramas */
  trapezio *=K_CONSUMO*AVC.User1[cuba].EfiCurr;

  /* Incrementa consumo de alumina no subestado atual */
  AVC.User1[cuba].ConsumoSubEst += trapezio; 

  /* Incrementa consumo de alumina p/ calculo da derivada */
  AVC.User1[cuba].Consumo += trapezio;
} /* ComumEstados */


/*
-------------------------------------------------------------------------------
  LiberaMoveAlim - Libera movimentacao do anodo e reseta tempo de movimentacao 
                   inibida
-------------------------------------------------------------------------------
*/
void LiberaMoveAlim(int cuba)
{
  /* Libera a movimentacao do anodo */
  EST_AVC(cuba).InibeControleAlim=FALSO;

  /* reseta tempo em que a movimentacao permaneceu inibida */
  AVC.User1[cuba].DurInibeControle= 0;
} /* LiberaMoveAlim */


/*
-------------------------------------------------------------------------------
  TrackingOver - executa tracking para atingir overfeed 
-------------------------------------------------------------------------------
*/
byte TrackingOver(int cuba)
{
  float balanco, interv_aux;

  /* calcula balanco de alumina no estado */
  balanco= AVC.User1[cuba].FornecSubEst-AVC.User1[cuba].ConsumoSubEst;

  /* Verifica se ainda esta em overfeed opcional */
  if (balanco >= AVC.User1[cuba].alvo)
  {
	interv_aux= AVC.User1[cuba].IntervCurr;
	AVC.User2[cuba].TaxaFeedPF = 1.0;
  }
  else
  {
	interv_aux= AVC.User1[cuba].IntervCurr/AVC.ParUser1[cuba].TaxaOverNorm;
	AVC.User2[cuba].TaxaFeedPF = AVC.ParUser1[cuba].TaxaOverNorm;
  }
  /* Verifica se e' hora de acionar o Point Feeder */
  if ((AVC.User1[cuba].IntPar >= interv_aux) and
     ((HoraAtualSec-AVC.User1[cuba].HoraUltPF) >= AVC.ParUser1[cuba].MinIntervPF))
  {
	/* Reseta valor da integral parcial */
	AVC.User1[cuba].IntPar -= interv_aux;

	/* Comanda acionamento do point feeder */
	TrataAcionaPF(cuba);
  }

  /* verifica transicao de estado */
  if ((balanco >= AVC.User1[cuba].alvo) and
      (((HoraAtualSec-AVC.Ccont[cuba].HoraUltMove) > AVC.Param[cuba].TEfeitoMoveCima) and
       ((HoraAtualSec-AVC.Ccont[cuba].HoraUltMove) > AVC.Param[cuba].TEfeitoMoveBaixo)) and
      ((HoraAtualSec-AVC.Cleit[cuba].HoraUltTPinos) > (AVC.Param[cuba].TEfeitoTPinos*60) ))
// Retirado em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
//    ((HoraAtualSec-AVC.Cleit[cuba].HoraUltCorr)>AVC.Param[cuba].TEfeitoCorr))
    return(VERDADEIRO);

  return(FALSO);
} /* TrackingOver */

/*
-------------------------------------------------------------------------------
  InitTrackingOver - inicializa variaveis ao comecar overfeed
-------------------------------------------------------------------------------
*/
void InitTrackingOver(int cuba)
{
  /* Incrementa numero de overfeeds em check */
  AVC.User1[cuba].NumOverCheck++;
    
  /* Calcula balanco de alumina a ser atingido */
  AVC.User1[cuba].alvo= -1000.0;
  if (AVC.User1[cuba].NumOverCheck <= AVC.ParUser1[cuba].MaxOverCheck)
    AVC.User1[cuba].alvo= AVC.ParUser1[cuba].MassaBanho*
                        AVC.ParUser1[cuba].PercOverOp;

  /* Verifica se entrou no estado devido aa derivada muito negativa */
  if (AVC.User1[cuba].ConcBaixa == VERDADEIRO)
  {
    AVC.User1[cuba].ConcBaixa= FALSO;

    /* Desabilita movimentacao do anodo */
    EST_AVC(cuba).InibeControleAlim=VERDADEIRO;
  }						
  else
  {
    /* Habilita movimentacao do anodo */
    LiberaMoveAlim(cuba);
  }
						
} /* Init_TrackingOver */


/***************************************************************************/
/* Rotinas usadas na implementacao da alimentacao normal do Check Especial */
/***************************************************************************/
/*
-------------------------------------------------------------------------------
  InitNormalCE - Inicializa as variaveis ao entrar no NORMal do Check Especial
-------------------------------------------------------------------------------
*/
void InitNormalCE(int cuba)
{
  /* Desativa flag indicando check */
  EST_AVC(cuba).Est.CheckAtivo=FALSO;

  /* Habilita movimentacao do anodo */
  LiberaMoveAlim(cuba);
} /* InitNormalCE */

/*
-------------------------------------------------------------------------------
  NormalCE - Executa tarefas do ciclo normal de check:
               - Alimentar a cuba em normal feed
-------------------------------------------------------------------------------
*/
void NormalCE(int cuba)
{
  /* Verifica se e' hora de acionar o Point Feeder */
  if ((AVC.User1[cuba].IntPar >= AVC.User1[cuba].IntervCurr) and
     ((HoraAtualSec-AVC.User1[cuba].HoraUltPF) >= AVC.ParUser1[cuba].MinIntervPF))
  {
	AVC.User2[cuba].TaxaFeedPF = 1.0;
    /* Reseta valor da integral parcial */
    AVC.User1[cuba].IntPar -= AVC.User1[cuba].IntervCurr;

    /* Comanda acionamento do point feeder */
    TrataAcionaPF(cuba);
  }
} /* NormalCE */

/*
-------------------------------------------------------------------------------
  NormalCE - Executa tarefas do ciclo normal de check:
               - Alimentar a cuba em normal feed
-------------------------------------------------------------------------------
*/
int TransicaoNormalCE(int cuba, int subestado)
{
  int next_substate=-1;

  /* Verifica transicao para check */
  if ((AVC.User1[cuba].NumAciona >= AVC.ParUser1[cuba].NumAcionaCheck) ||
      ((HoraAtualSec-AVC.User1[cuba].HoraFimCheck) > 
        AVC.ParUser1[cuba].MaxIntervCheck) ||
      ((HoraAtualSec-AVC.User1[cuba].HoraIniSubEstAtual) > 
        AVC.ParUser1[cuba].DurNormCheck))
    next_substate= subestado;

  return(next_substate);
} /* TransicaoNormalCE */

/*******************************************************/
/* Rotinas utilizadas na implementacao do CHECK normal */
/*******************************************************/
/*
-------------------------------------------------------------------------------
  InitPreCheck - Inicializa as variaveis ao entrar no Pre Check
-------------------------------------------------------------------------------
*/
void InitPreCheck(int cuba)
{
  /* Desabilita movimentacao do anodo */
  EST_AVC(cuba).InibeControleAlim=VERDADEIRO;

  /* Coloca flag de check como ativo */
  EST_AVC(cuba).Est.CheckAtivo=VERDADEIRO;
      
  /* Inicializa variavel com a hora do inicio do check */
  AVC.User1[cuba].HoraUltCheck= HoraAtualSec;

  /* Inicializa valor do underfeed progressivo */
  AVC.User1[cuba].UnderProg= AVC.ParUser1[cuba].UnderProgIni;

  /* Armazena hora de inicio do underfeed */
  AVC.User1[cuba].IniEtapaUnder= HoraAtualSec;

  /* Reseta numero de overfeeds em check */
  AVC.User1[cuba].NumOverCheck=0;
} /* InitPreCheck */


/*
-------------------------------------------------------------------------------
  PreCheck - executa as tarefas referentes ao PreCheck
-------------------------------------------------------------------------------
*/
void PreCheck(int cuba)
{
  /* Verifica se e' hora de acionar o Point Feeder */
  if ((AVC.User1[cuba].IntPar >= (AVC.User1[cuba].IntervCurr/AVC.User1[cuba].UnderProg)) and
     ((HoraAtualSec-AVC.User1[cuba].HoraUltPF) >= AVC.ParUser1[cuba].MinIntervPF))
  {
    /* Reseta valor da integral parcial */
   AVC.User1[cuba].IntPar -= AVC.User1[cuba].IntervCurr/AVC.User1[cuba].UnderProg;
	AVC.User2[cuba].TaxaFeedPF = AVC.User1[cuba].UnderProg;
    /* Comanda acionamento do point feeder */
    TrataAcionaPF(cuba);
  }

  /* Verifica se e' hora de intensificar o underfeed */
  if ((HoraAtualSec-AVC.User1[cuba].IniEtapaUnder) >= 
       AVC.ParUser1[cuba].IntervUnderProg)
  {
    /* Reinicializa hora de inicio da etapa de under progressivo */
    AVC.User1[cuba].IniEtapaUnder= HoraAtualSec;

    /* Aumenta o intervalo de integracao */
    AVC.User1[cuba].UnderProg -= AVC.ParUser1[cuba].DeltaUnder;
    if (AVC.User1[cuba].UnderProg < 0.1)
      AVC.User1[cuba].UnderProg= 0.1; 
  }
} /* PreCheck */

/*
-------------------------------------------------------------------------------
  TransicaoPreCheck - verifica condicoes de saida do estado:
                        + Fim do ruido na resistencia de alimentacao
-------------------------------------------------------------------------------
*/
int TransicaoPreCheck(int cuba,int subestado)
{
 int next_substate;
 
  /* Verifica presenca de ruido na cuba */
  if (EST_AVC(cuba).Est.RuidoAlim eq FALSO)
    next_substate= subestado; 
  else    
    next_substate=-1;
	
  return(next_substate);	
}

/*
-------------------------------------------------------------------------------
  InitCheck1 - Inicializa as variaveis ao entrar no Check1
-------------------------------------------------------------------------------
*/
void InitCheck1(int cuba)
{
  /* Habilita movimentacao do anodo */
  LiberaMoveAlim(cuba);

  /* Inicializa flag desabilitando o overfeed opcional */
  AVC.User1[cuba].alvo= -1000.0;

  /* Verifica se overfeed opcional esta habilitado */
  if (AVC.ParUser1[cuba].OverOpcional eq VERDADEIRO)
  {
    //incrementa numero de overfeeds em check
    AVC.User1[cuba].NumOverCheck++;
    
    //calcula balanco de overfeed alvo
    if (AVC.User1[cuba].NumOverCheck <= AVC.ParUser1[cuba].MaxOverCheck)
      AVC.User1[cuba].alvo= AVC.ParUser1[cuba].MassaBanho*
	                      AVC.ParUser1[cuba].PercOverOp;
  }
    
} /* InitCheck1 */

/*
-------------------------------------------------------------------------------
  Check1 - Executa tarefas referente ao primeiro estado do check:
             + Espera estabilizacao da resistencia de alimentacao 
			    (troca de pinos, movimentacao do anodo e corrida)
             + Executa overfeed opcional, quando habilitado				 
-------------------------------------------------------------------------------
*/
int Check1(int cuba)
{
  float balanco, interv_aux;

  /* calcula balanco de alumina no estado */
  balanco= AVC.User1[cuba].FornecSubEst-AVC.User1[cuba].ConsumoSubEst;

  /* Verifica se ainda esta em overfeed opcional */
  if (balanco >= AVC.User1[cuba].alvo)
  {
	interv_aux= AVC.User1[cuba].IntervCurr;
	AVC.User2[cuba].TaxaFeedPF = 1.0;
  }
  else
  {
	interv_aux= AVC.User1[cuba].IntervCurr/AVC.ParUser1[cuba].TaxaOverNorm;
	AVC.User2[cuba].TaxaFeedPF = AVC.ParUser1[cuba].TaxaOverNorm;
  }

  /* Verifica se e' hora de acionar o Point Feeder */
  if ((AVC.User1[cuba].IntPar >= interv_aux) and
     ((HoraAtualSec-AVC.User1[cuba].HoraUltPF) >= AVC.ParUser1[cuba].MinIntervPF))
  {
	/* Reseta valor da integral parcial */
	AVC.User1[cuba].IntPar -= interv_aux;

	/* Comanda acionamento do point feeder */
	TrataAcionaPF(cuba);
  }

  /* verifica transicao de estado */
  if (balanco >= AVC.User1[cuba].alvo)
    return(VERDADEIRO);

  return(FALSO);
} /* Check1 */

/*
-------------------------------------------------------------------------------
  TransicaoCheck1 - verifica condicoes de saida do estado:
                        + Percentual de overfeed foi atingido (fimtrack=1)
						+ Resistencia de alimentacao esta estabilizada 
						  (troca de pinos, movimentacao do anodo e corrida)
-------------------------------------------------------------------------------
*/
int TransicaoCheck1(int cuba,int subestado, int fimtrack)
{
 int next_substate=-1;

 if ((fimtrack == VERDADEIRO) and
     (((HoraAtualSec-AVC.Ccont[cuba].HoraUltMove) > AVC.Param[cuba].TEfeitoMoveCima) and
      ((HoraAtualSec-AVC.Ccont[cuba].HoraUltMove) > AVC.Param[cuba].TEfeitoMoveBaixo)) and
     ((HoraAtualSec-AVC.Cleit[cuba].HoraUltTPinos) > (AVC.Param[cuba].TEfeitoTPinos*60) ))
// Retirado em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
//     ((HoraAtualSec-AVC.Cleit[cuba].HoraUltCorr) > AVC.Param[cuba].TEfeitoCorr) and
   next_substate= subestado;	 

 return(next_substate);   
} /* TransicaoCheck1 */
 
/*
-------------------------------------------------------------------------------
  InitCheck2 - Inicializa as variaveis ao entrar no Check2
-------------------------------------------------------------------------------
*/
void InitCheck2(int cuba)
{
  /* Desabilita movimentacao do anodo */
  EST_AVC(cuba).InibeControleAlim=VERDADEIRO;

  //indica que o buffer de resistencias ainda nao esta preenchido
  AVC.User1[cuba].Preenchido= FALSO;

  //Indice com o numero de resistencias ja obtidas
  AVC.User1[cuba].ResIndex=0;

  //Indice com o numero de derivadas ja obtidas
  AVC.User1[cuba].DerIndex=0;

  //Zera variavel que armazena o consumo de alumina p/ aquisicao da resistencia
  AVC.User1[cuba].Consumo= 0;

  //Coloca primeiro valor da resistencia no buffer de resistencias (calculo da derivada)
  armazena(cuba,AVC.User1[cuba].ResAlim);
    
  //iniciliza valor da derivada da resistencia
  AVC.User1[cuba].DerResAlim= 1000.0;
  AVC.User1[cuba].DerResAlimAnt= 1000.0;
}

/*
-------------------------------------------------------------------------------
  Check2 - Executa tarefas referente ao segundo estado do check:
             + Monitora resistencia de alimentacao atraves das derivadas da
			   mesma.
             + Executa underfeed
-------------------------------------------------------------------------------
*/
void Check2(int cuba)
{
byte Seq;

  /* Armazena resistencia da cuba toda vez que o consumo de alumina igualar
     o consumo desejado entre resistencias durante o calculo da derivada */
  if (AVC.User1[cuba].Consumo >= (AVC.ParUser1[cuba].ConsumoResAlim*AVC.ParUser1[cuba].MassaBanho))
  {  
    // Coloca resistencia filtrada no buffer de resistencias 
    armazena(cuba,AVC.User1[cuba].ResAlim);

    // Reseta valor do consumo
    AVC.User1[cuba].Consumo -= AVC.ParUser1[cuba].ConsumoResAlim*
                             AVC.ParUser1[cuba].MassaBanho;
    
    // Recalcula derivada da resistencia
    if (AVC.User1[cuba].Preenchido eq VERDADEIRO)
    {
      AVC.User1[cuba].DerResAlimAnt= AVC.User1[cuba].DerResAlim;
      AVC.User1[cuba].DerResAlim= calc_deriv(cuba); //calcula derivada da resistencia
    }
  }

  /* Verifica se e' hora de acionar o Point Feeder */
  if ((AVC.User1[cuba].IntPar >= (AVC.User1[cuba].IntervCurr/AVC.ParUser1[cuba].TaxaUnder)) and
     ((HoraAtualSec-AVC.User1[cuba].HoraUltPF) >= AVC.ParUser1[cuba].MinIntervPF))  
  {
	AVC.User2[cuba].TaxaFeedPF = AVC.ParUser1[cuba].TaxaUnder;
    /* Reseta valor da integral parcial */
    AVC.User1[cuba].IntPar -= AVC.User1[cuba].IntervCurr/AVC.ParUser1[cuba].TaxaUnder;

    /* Decrementa consumo de alumina p/ calculo da derivada */
/* -- Alteracao - Inicio - Robson - 15/11/2000 - Quantidades diferentes por acionador -- */
//	Seq = AVC.ParUser1[cuba].Sequencia[AVC.User1[cuba].PassoCadencia] - 1;
	Seq = abs(EST_AVC(cuba).Est.LadoProxPF - 1);
    AVC.User1[cuba].Consumo -= AVC.ParUser1[cuba].QuantAlumCarga[Seq];
/* -- Alteracao - Fim - Robson - 15/11/2000 - Quantidades diferentes por acionador -- */

    /* Comanda acionamento do point feeder */
    TrataAcionaPF(cuba);
  }
}

/*
-------------------------------------------------------------------------------
  TransicaoCheck2 - verifica condicoes de saida do estado:
                        + Derivada muito negativa
						+ Derivada negativa
						+ Resistencia de alimentacao esta estabilizada 
						  (troca de pinos, movimentacao do anodo e corrida)
-------------------------------------------------------------------------------
*/
int TransicaoCheck2(int cuba,int subestado1, int subestado2)
{
  int next_substate=-1;

  /* Se a derivada for negativa e muito alta -> overfeed para evitar efeito
     anodico durante o check */
  if ((AVC.User1[cuba].DerResAlim < AVC.ParUser1[cuba].MaxDerInitCheck) and
      (AVC.User1[cuba].DerResAlimAnt < AVC.ParUser1[cuba].MaxDerInitCheck)) 
  {
    next_substate= subestado1;
	AVC.User1[cuba].ConcBaixa= VERDADEIRO;
    return(next_substate);
  }	  
  if ((AVC.Cleit[cuba].HoraUltTPinos > AVC.User1[cuba].HoraIniSubEstAtual) or
// Retirado em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
//    (AVC.Cleit[cuba].HoraUltCorr > AVC.User1[cuba].HoraIniSubEstAtual) or
      (AVC.Ccont[cuba].HoraUltMove > AVC.User1[cuba].HoraIniSubEstAtual))
  {
    next_substate= subestado1;
  }
  else if ((AVC.User1[cuba].DerResAlim < AVC.ParUser1[cuba].DerInitCheck) and
           (AVC.User1[cuba].DerResAlimAnt < AVC.ParUser1[cuba].DerInitCheck))
  {
    //armazena derivadas no vetor 
    armazena_deriv(cuba,AVC.User1[cuba].DerResAlimAnt);
    armazena_deriv(cuba,AVC.User1[cuba].DerResAlim);

    next_substate= subestado2;
  }

  return(next_substate);
} /* TransicaoCheck2 */ 

/*
-------------------------------------------------------------------------------
  InitCheck3 - Inicializa as variaveis ao entrar no Check3
-------------------------------------------------------------------------------
*/
void InitCheck3(int cuba)
{
  /* Desabilita movimentacao do anodo */
  EST_AVC(cuba).InibeControleAlim=VERDADEIRO;

  /* Inicializa variavel */
  AVC.User1[cuba].ConcDer= 1000.0;
} /* InitCheck3 */

/*
-------------------------------------------------------------------------------
  Check3 - Executa tarefas referente ao terceiro estado do check:
             + Armazena demais derivadas da resistencia
			 + Calcula concentracao de alumina no banho
             + Executa underfeed
-------------------------------------------------------------------------------
*/
int Check3(int cuba)
{
byte Seq;

  /* Armazena resistencia da cuba toda vez que o consumo de alumina igualar
     o consumo desejado entre resistencias durante o calculo da derivada */
  if (AVC.User1[cuba].Consumo >= (AVC.ParUser1[cuba].ConsumoResAlim*AVC.ParUser1[cuba].MassaBanho))
  {  
    // Coloca resistencia filtrada no buffer de resistencias 
    armazena(cuba,AVC.User1[cuba].ResAlim);

    // Reseta valor do consumo
    AVC.User1[cuba].Consumo -= AVC.ParUser1[cuba].ConsumoResAlim*
                             AVC.ParUser1[cuba].MassaBanho;
    
    // Recalcula derivada da resistencia
    AVC.User1[cuba].DerResAlimAnt= AVC.User1[cuba].DerResAlim;
    AVC.User1[cuba].DerResAlim= calc_deriv(cuba);
    armazena_deriv(cuba, AVC.User1[cuba].DerResAlim);

    
    //verifica se ha derivadas suficientes
    if (AVC.User1[cuba].DerIndex >= NUM_DERIV_RES)
    {
      /* calcula concentracao a partir das derivadas */
      AVC.User1[cuba].ConcDer= Calc_ConcDerivada(cuba);
    }

  }

  /* Verifica se e' hora de acionar o Point Feeder */
  if ((AVC.User1[cuba].IntPar >= (AVC.User1[cuba].IntervCurr/AVC.ParUser1[cuba].TaxaUnder)) and
     ((HoraAtualSec-AVC.User1[cuba].HoraUltPF) >= AVC.ParUser1[cuba].MinIntervPF))
  {
	AVC.User2[cuba].TaxaFeedPF = AVC.ParUser1[cuba].TaxaUnder;
    /* Reseta valor da integral parcial */
    AVC.User1[cuba].IntPar -= AVC.User1[cuba].IntervCurr/AVC.ParUser1[cuba].TaxaUnder;

    /* Decrementa consumo de alumina p/ calculo da derivada */
/* -- Alteracao - Inicio - Robson - 15/11/2000 - Quantidades diferentes por acionador -- */
//	Seq = AVC.ParUser1[cuba].Sequencia[AVC.User1[cuba].PassoCadencia] - 1;
	Seq = abs(EST_AVC(cuba).Est.LadoProxPF - 1);
    AVC.User1[cuba].Consumo -= AVC.ParUser1[cuba].QuantAlumCarga[Seq];
/* -- Alteracao - Fim - Robson - 15/11/2000 - Quantidades diferentes por acionador -- */

    /* Comanda acionamento do point feeder */
    TrataAcionaPF(cuba);
  }

  if (AVC.User1[cuba].ConcDer <= AVC.ParUser1[cuba].ConcValidCheck)
    return(VERDADEIRO);

  return(FALSO);
} /* Check3 */

/*
-------------------------------------------------------------------------------
  TransicaoCheck3 - verifica condicoes de saida do estado:
                        + Derivada muito negativa
						+ Derivada negativa
						+ Resistencia de alimentacao esta estabilizada 
						  (troca de pinos, movimentacao do anodo e corrida)
-------------------------------------------------------------------------------
*/
int TransicaoCheck3(int cuba, int subestado1, int subestado2, int fimderiv)
{
  int next_substate=-1;
  float ConcBal;

  //verifica transicao de estado
  if ((AVC.Cleit[cuba].HoraUltTPinos > AVC.User1[cuba].HoraIniSubEstAtual) or
// Retirado em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
//      (AVC.Cleit[cuba].HoraUltCorr > AVC.User1[cuba].HoraIniSubEstAtual) or
      (AVC.Ccont[cuba].HoraUltMove > AVC.User1[cuba].HoraIniSubEstAtual) or
  	  ((AVC.User1[cuba].DerResAlim < AVC.ParUser1[cuba].MaxDerInitCheck) and
      (AVC.User1[cuba].DerResAlimAnt < AVC.ParUser1[cuba].MaxDerInitCheck)))
  {
    next_substate= subestado1;
  }
  else if (fimderiv eq VERDADEIRO)
  {

    /* calcula concentracao a partir do balanco de alumina */
    ConcBal= Calc_ConcBalanco(cuba);

    /* Calcula novo intervalo p/ acionamento do point feeder e nova 
       eficiencia de corrente. Calcula tambem concentracao valida p/ o check
       e o numero de bateladas para chegar novamente na concentracao nominal*/
    Calc_Check(cuba,AVC.User1[cuba].ConcDer,ConcBal);

    /* habilita mudanca do estado */
    next_substate= subestado2;
  }
  
  return(next_substate);
} /* TransicaoCheck3 */

/*
-------------------------------------------------------------------------------
  InitCheck4 - Inicializa as variaveis ao entrar no Check4
-------------------------------------------------------------------------------
*/
void InitCheck4(int cuba)
{
  /* Controla inibicao da movimentacao do anodo */
  EST_AVC(cuba).InibeControleAlim= AVC.ParUser1[cuba].HabMovTrack;

  //Reseta numero de acionamentos do Point Feeder 
  AVC.User1[cuba].NumAciona= 0;
    
  //Reseta integral da corrente
  AVC.User1[cuba].Integral=0;

  //calcula balanco alvo para calculo do tracking de concentracao
  AVC.User1[cuba].alvo= AVC.ParUser1[cuba].MassaBanho*
                     (AVC.ParUser1[cuba].ConcNominal-
                      AVC.User1[cuba].ConcCheckAtual);
} /* InitCheck4 */

/*
-------------------------------------------------------------------------------
  Check4 - Executa tarefas referente ao quarto estado do check:
             + Leva a concentracao de alumina no banho para seu valor nominal
             + Executa Overfeed/underfeed (depende da concentracao calculada 
			                               e da concentracao nominal)
-------------------------------------------------------------------------------
*/
int Check4(int cuba)
{
  float interv_aux,balanco;

  //Inicializa intervalo de corrente alvo
  interv_aux= AVC.User1[cuba].IntervCurr;

  /* Verifica se deve executar overfeed ou underfeed */
  if (AVC.User1[cuba].alvo < 0)
  {
    interv_aux /= AVC.ParUser1[cuba].TaxaUnder;
	AVC.User2[cuba].TaxaFeedPF = AVC.ParUser1[cuba].TaxaUnder;
  }
  else
  {
    interv_aux /= AVC.ParUser1[cuba].TaxaOverNorm;
	AVC.User2[cuba].TaxaFeedPF = AVC.ParUser1[cuba].TaxaOverNorm;
  }
  /* Verifica se e' hora de acionar o Point Feeder */
  if ((AVC.User1[cuba].IntPar >= interv_aux) and
     ((HoraAtualSec-AVC.User1[cuba].HoraUltPF) >= AVC.ParUser1[cuba].MinIntervPF))
  {
    /* Reseta valor da integral parcial */
    AVC.User1[cuba].IntPar -= interv_aux;

    /* Comanda acionamento do point feeder */
    TrataAcionaPF(cuba);
  }

  /* calcula balanco de alumina */
  balanco= AVC.User1[cuba].FornecSubEst-AVC.User1[cuba].ConsumoSubEst;

  /* Habilita a movimentacao do anodo quando uma concentracao minima 
     definida pelo usuario for atingida */
  if ((AVC.User1[cuba].ConcCheckAtual+(balanco/AVC.ParUser1[cuba].MassaBanho))  
      >= AVC.ParUser1[cuba].ConcHabMove)
  {	  
    EST_AVC(cuba).InibeControleAlim= FALSO;
  }	

  //sair do estado quando atingir a massa alvo (concentracao nominal)
  if (((AVC.User1[cuba].alvo < 0) and (balanco <= AVC.User1[cuba].alvo)) or
      ((AVC.User1[cuba].alvo >= 0) and (balanco >= AVC.User1[cuba].alvo)))
    return(VERDADEIRO);

  return(FALSO);
} /* Check4 */

/*
-------------------------------------------------------------------------------
  TransicaoCheck4 - verifica condicoes de saida do estado:
                        + Concentracao nominal foi atingida
-------------------------------------------------------------------------------
*/
int TransicaoCheck4(int cuba, int estado,int fimtrack)
{
  int next_alg=-1;

  //verifica condicao de saida
  if (fimtrack eq VERDADEIRO)
  {
    /* Armazena na base de dados hora do termino do check */
    AVC.User1[cuba].HoraFimCheck= HoraAtualSec;

    next_alg= estado;
  }

  return(next_alg);
}
/* -- fim PFRot.c -- */

