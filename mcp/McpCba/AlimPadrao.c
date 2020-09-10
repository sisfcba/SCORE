/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.1

	PROJETO		: CBA - Companhia Brasileira de Aluminio SA

	SISTEMA		: SALAS 120KA II e III

	ARQUIVO		: AlimPadrao.c

	CONTEUDO	: Algoritmo de alimentacao point feeder para cuba em alimen-
                  tacao padrao: Normal + Check padrao

	AUTOR		: Ricardo Teixeira Leite Mourao / Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	02/01/97

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
Data     | Descricao                                            | Autor 
-------------------------------------------------------------------------------
02/01/97 | Edicao inicial                                       | Ricardo-Leonel
-------------------------------------------------------------------------------
15/01/99 | Alteracao conforme proposta 1006CA                   | Ricardo-Leonel
-------------------------------------------------------------------------------
29/08/17 | TK-ALIM - Preparacão Toolkit Alimentacao             | Carlos
-------------------------------------------------------------------------------
******************************************************************************/
/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include	<McpPF.h>
#include	<time.h>
#ifdef	ATIVA_DEPURACAO
  #include	<stdio.h>
#endif

/*
-------------------------------------------------------------------------------
                           Variaveis Globais
-------------------------------------------------------------------------------
*/
/* -- Apontadores para as tabelas comuns -- */
#include	<VarsComum.h>


/*
-------------------------------------------------------------------------------
                           Prototipos internos
-------------------------------------------------------------------------------
*/
int VerifCondAP(int cuba);
void TerminaAlgPadrao(int cuba);
void InitAlimPadrao(int cuba);
int AlimPadraoNorm(int cuba);
int AlimPadraoPreCheck(int cuba);
int AlimPadraoCheck1(int cuba);
int AlimPadraoCheck2(int cuba);
int AlimPadraoCheck3(int cuba);
int AlimPadraoCheck4(int cuba);
int AlimPadraoOver(int cuba);


/*
-------------------------------------------------------------------------------
  AlimPadrao - Implementa o estado de alimentacao normal do alg. CBA.
               Alimentacao: normal
			   Condicao de saida: excecao ou check normal
-------------------------------------------------------------------------------
*/
int AlimPadrao(int cuba)
{
  int    next_alg;              //proximo algoritmo de alimentacao a ser executado 
  int    next_state;            //indica mudanca de estado dentro do algoritmo (1=mudou)

  /* -- incrementa tempo de permanencia no algoritmo -- */
  SUPERV_AVC(cuba).Sup.TAlimPadrao++;
  SUPERV_AVC_TURNO(cuba).Sup.TAlimPadrao++;

  /* Verifica condicoes para saida da alimentacao padrao */
  next_alg= VerifCondAP(cuba);
  if (next_alg ne -1)              //#2
  {
    /* Executa operacoes relativas ao fim do algoritmo */
    TerminaAlgPadrao(cuba);
  }
  else
  {
    if (AVC.User1[cuba].InicioAlgAtual) //#1
    {
      AVC.User1[cuba].InicioAlgAtual=FALSO;
      /* Inicializa variaveis ao entrar na alimentacao padrao */
      InitAlimPadrao(cuba);
    }
    do
    {
      /* Executa tarefas comuns a todos os estados */
      ComumEstados(cuba);

      /* Executa Rotina Referente a um estado */
      switch(AVC.User1[cuba].State)
      {
        case PADRAO_NORMAL:
          next_state=AlimPadraoNorm(cuba);
          break;
        case PADRAO_PRE_CHECK:
          next_state=AlimPadraoPreCheck(cuba);
          break;
        case PADRAO_CHECK1:
          next_state=AlimPadraoCheck1(cuba);
          break;
        case PADRAO_CHECK2:
          next_state=AlimPadraoCheck2(cuba);
          break;
        case PADRAO_CHECK3:
          next_state=AlimPadraoCheck3(cuba);
          break;
        case PADRAO_CHECK4:
          next_state=AlimPadraoCheck4(cuba);
          break;
        case PADRAO_OVER:
          next_state=AlimPadraoOver(cuba);
          break;
      } //switch

      /* Faz mudanca de estado interno ao algoritmo padrao */
      if (next_state ne -1)
        /* -- Muda para o novo estado -- */
        MudaEstadoSub(cuba,next_state);
    } while(next_state ne -1);
  }                                //#1

  /* Retorna `a McpPF o proximo algoritmo a ser executado */
  return(next_alg);
} /* AlimPadrao */

/*
-------------------------------------------------------------------------------
  VerifCondAP - Verifica condicoes para saida da alimentacao padrao
                Retorna proximo estado quando detecta alguma condicao
                de saida ou -1 caso contrario.
-------------------------------------------------------------------------------
*/
int VerifCondAP(int cuba)
{
  int next_state;

  next_state=-1; //Por default, permanecer no estado

  if ((HoraAtualSec - AVC.Ea[cuba].EaHoraInicio) > 
      (AVC.ParUser1[cuba].MaxIntervEa*60))
  {
    next_state= EST_ALIM_SUSPENSA;
    AVC.User1[cuba].TempoSuspende= 0; //Suspensa ate chegada de EA
  }
  else if (EST_AVC(cuba).Est.ManualAlimLoc eq VERDADEIRO)
  {//Verifica chave de alimentacao manual/automatico (modificacao no campo)
	next_state=EST_ALIM_EXCECAO;
  }
  else if (EST_AVC(cuba).Ea eq VERDADEIRO)
  {
    next_state= EST_ALIM_EA;
  }
  else if (EST_AVC(cuba).Quebrada eq VERDADEIRO)
  { //verifica se a cuba foi quebrada
    next_state= EST_ALIM_EXCECAO; //trata quebrada a qualquer hora
  }
// Inserido em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
  else if (EST_AVC(cuba).Corrida eq VERDADEIRO)
  { //verifica se a cuba foi corrida
    next_state= EST_ALIM_EXCECAO; //trata corrida a qualquer hora
  }
 
  return(next_state);
} /* VerifConAP */

/*
-------------------------------------------------------------------------------
  TerminaAlgPadrao - Executa operacoes relativas ao fim do algoritmo padrao
-------------------------------------------------------------------------------
*/
void TerminaAlgPadrao(int cuba)
{
} /* TerminaAlgPadrao */

/*
-------------------------------------------------------------------------------
  InitAlimPadrao - Inicializa variaveis ao entrar na alimentacao padrao
-------------------------------------------------------------------------------
*/
void InitAlimPadrao(int cuba)
{
} /* InitAlimPadrao */

/*
-------------------------------------------------------------------------------
  AlimPadraoNorm - Implementa o subestado normal do estado de alimentacao
				   padrao CBA.
                   Retorna proximo subestado quando terminou o ciclo ou -1
                   caso contrario.
-------------------------------------------------------------------------------
*/
int AlimPadraoNorm(int cuba)
{ /* retorna proximo estado ou -1 se continua no mesmo */
  int next_substate;
  float interv_aux;

  if (AVC.User1[cuba].InicioSubEst)
  { /* primeira vez, inicializa variaveis */
    AVC.User1[cuba].InicioSubEst=FALSO;

    //Desativa flag indicando 
    EST_AVC(cuba).Est.CheckAtivo=FALSO;

    //habilita movimentacao
    LiberaMoveAlim(cuba); 
  }

  if(AVC.ParUser1[cuba].HabOverPadrao eq VERDADEIRO)
  {
	if(AVC.User2[cuba].CoefAng <= AVC.ParUser1[cuba].CoefAngOver and
		AVC.User2[cuba].CoefCor >= AVC.ParUser1[cuba].CoefCorrOver)
	{
	  AVC.User2[cuba].NCicOverPadrao++;
	  AVC.User2[cuba].NCicNormPadrao= 0;
	  AVC.User2[cuba].NCicUnderPadrao= 0;
	  if(AVC.User2[cuba].NCicOverPadrao >= AVC.ParUser1[cuba].NCicOverPadrao)
	  {
		EST_AVC(cuba).Est.OverPadrao = VERDADEIRO;
		EST_AVC(cuba).Est.UnderPadrao = FALSO;
	  }
	}
	else if(AVC.User2[cuba].CoefAng >= AVC.ParUser1[cuba].CoefAngUnder and
		AVC.User2[cuba].CoefCor >= AVC.ParUser1[cuba].CoefCorrUnder)
	{
	  AVC.User2[cuba].NCicOverPadrao = 0;
	  AVC.User2[cuba].NCicNormPadrao = 0;
	  AVC.User2[cuba].NCicUnderPadrao++;
	  if(AVC.User2[cuba].NCicUnderPadrao >= AVC.ParUser1[cuba].NCicUnderPadrao)
	  {
		EST_AVC(cuba).Est.OverPadrao = FALSO;
		EST_AVC(cuba).Est.UnderPadrao = VERDADEIRO;
	  }
	}
	else
	{
	  AVC.User2[cuba].NCicOverPadrao = 0;
	  AVC.User2[cuba].NCicNormPadrao++;
	  if(AVC.User2[cuba].NCicNormPadrao >= AVC.ParUser1[cuba].NCicNormPadrao)
	  {
		EST_AVC(cuba).Est.OverPadrao = FALSO;
		EST_AVC(cuba).Est.UnderPadrao = FALSO;
	  }
	}

	if(EST_AVC(cuba).Est.OverPadrao eq VERDADEIRO)
	{
	  interv_aux = AVC.User1[cuba].IntervCurr/AVC.ParUser1[cuba].TaxaOverNorm;
	  AVC.User2[cuba].TaxaFeedPF = AVC.ParUser1[cuba].TaxaOverNorm;
	}
	else if(EST_AVC(cuba).Est.UnderPadrao eq VERDADEIRO)
	{
	  interv_aux = AVC.User1[cuba].IntervCurr/AVC.ParUser1[cuba].TaxaUnder;
	  AVC.User2[cuba].TaxaFeedPF = AVC.ParUser1[cuba].TaxaUnder;
	}
	else
	{
 	  interv_aux = AVC.User1[cuba].IntervCurr;
	  AVC.User2[cuba].TaxaFeedPF = 1.0;
	}

  }
  else
  {
 	interv_aux = AVC.User1[cuba].IntervCurr;
	AVC.User2[cuba].TaxaFeedPF = 1.0;
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

  /* Verifica transicao para check */
  if (((AVC.User1[cuba].NumAciona >= AVC.ParUser1[cuba].NumAcionaCheck) or
      ((HoraAtualSec-AVC.User1[cuba].HoraFimCheck) > 
       AVC.ParUser1[cuba].MaxIntervCheck)) and
		EST_AVC(cuba).Est.Oscilacao eq FALSO) 
  {
    next_substate= PADRAO_PRE_CHECK;
  }
  else    
    next_substate=-1; //permanece em alimentacao normal

  return(next_substate);
} /* AlimPadraoNorm */

/*
-------------------------------------------------------------------------------
  AlimPadraoPreCheck - Implementa o subestado PreCheck do estado de alimentacao
                       padrao CBA.
                       Alimentacao: underfeed
                       Retorna proximo subestado quando terminou o ciclo ou -1
                       caso contrario.
-------------------------------------------------------------------------------
*/
int AlimPadraoPreCheck(int cuba)
{ /* retorna proximo estado ou -1 se continua no mesmo */
  int next_substate;

  if (AVC.User1[cuba].InicioSubEst)
  { /* primeira vez, inicializa variaveis */
    AVC.User1[cuba].InicioSubEst=FALSO;

    /* Inicializa estado */
	InitPreCheck(cuba);
  }

  /* Executa tarefas do subestado:
       - Alimentacao em underfeed progressivo */
  PreCheck(cuba);	   

  /* Verifica mudanca de estado:
       - fim de ruido na resistencia de alimentacao */
  next_substate= TransicaoPreCheck(cuba,PADRAO_CHECK1);	   

  return(next_substate);
} /* AlimPadraoPreCheck */

/*
-------------------------------------------------------------------------------
  AlimPadraoCheck1 - Espera overfeed (opcional) e estabilizacao da cuba
                     Alimentacao: Overfeed (opcional)/normal
                     Condicao de saida: cuba estavel e overfeed atingido
-------------------------------------------------------------------------------
*/
int AlimPadraoCheck1(int cuba)
{ /* retorna proximo estado ou -1 se continua no mesmo */
  int next_substate;
  byte FimTrackingOver;

  if (AVC.User1[cuba].InicioSubEst)
  { /* Reseta flag de inicio de subestado */
    AVC.User1[cuba].InicioSubEst=FALSO;

    /* Inicializa subestado */
	InitCheck1(cuba);
  }

  /* Faz traking de overfeed opcional e espera estabilizacao da cuba */
  FimTrackingOver= Check1(cuba);

  /* Verifica transicao de estado:
      - Cuba esta estavel (corrida, movimentaco de anodo e troca de pinos)
	  - Percentual de overfeed desejado foi atingido */
  next_substate= TransicaoCheck1(cuba, PADRAO_CHECK2, FimTrackingOver);	  

  return(next_substate);
} /* AlimPadraoCheck1 */

/*
-------------------------------------------------------------------------------
  AlimPadraoCheck2 - Monitora derivada da resistencia de alimentacao (check)
                     Alimentacao: underfeed
                     Condicao de saida:Obtencao de duas derivadas ok ou
                                       excecao
-------------------------------------------------------------------------------
*/
int AlimPadraoCheck2(int cuba)
{ /* retorna proximo estado ou -1 se continua no mesmo */
  int next_substate;

  if (AVC.User1[cuba].InicioSubEst)
  { /* primeira vez, inicializa variaveis */
    AVC.User1[cuba].InicioSubEst=FALSO;

    /* Inicializa variaveis do subestado */
    InitCheck2(cuba);
  }

  /* monitora resistencia e pega duas primeiras derivadas */
  Check2(cuba);

  /* Verifica transicao de estado:
      - Derivada muito negativa
	  - Derivada negativa
	  - Condicao de excecao */
  next_substate= TransicaoCheck2(cuba, PADRAO_OVER, PADRAO_CHECK3);	  
  
  return(next_substate);
} /* AlimPadraoCheck2 */

/*
-------------------------------------------------------------------------------
  AlimPadraoCheck3 - Obtencao das derivadas faltantes e calculos do check
                     Alimentacao: underfeed
                     Condicao de saida: fim dos calculos do check
-------------------------------------------------------------------------------
*/
int AlimPadraoCheck3(int cuba)
{ /* retorna proximo estado ou -1 se continua no mesmo */
  int next_substate;
  byte FimMonitDer;

  if (AVC.User1[cuba].InicioSubEst eq VERDADEIRO)
  {
    AVC.User1[cuba].InicioSubEst= FALSO;

    /* Inicializa subestado */
	InitCheck3(cuba);
  }

  /* Monitora derivada da resistencia para obter concentracao de fim de check */
  FimMonitDer= Check3(cuba);

  /* Verifica transicao de estado:
       - Condicao de excecao
	   - Concentracao de check foi achada */
  next_substate= TransicaoCheck3(cuba, PADRAO_OVER, PADRAO_CHECK4, 
                                 FimMonitDer);	   
  return(next_substate);
} /* AlimPadraoCheck3 */

/*
-------------------------------------------------------------------------------
  AlimPadraoCheck4 - Faz o tracking da concentracao nominal
                     Alimentacao: under ou over
                     Condicao de saida: concentracao nominal atingida
-------------------------------------------------------------------------------
*/
int AlimPadraoCheck4(int cuba)
{ /* retorna proximo estado ou -1 se continua no mesmo */
  int next_substate;
  byte FimTracking;

  if (AVC.User1[cuba].InicioSubEst)
  { /* primeira vez, inicializa variaveis */
    AVC.User1[cuba].InicioSubEst=FALSO;

    /* Inicializa variaveis utilizadas no tracking da concentracao nominal */
    InitCheck4(cuba);
  }

  /* Executa tarefas do subestado:
       - Tracking da concentracao nominal */
  FimTracking= Check4(cuba);

  /* Verifica condicao de saida do estado:
       - Concentracao nominal foi atingida */
  next_substate= TransicaoCheck4(cuba, PADRAO_NORMAL, FimTracking);

  return(next_substate);
} /* AlimPadraoCheck4 */

/*
-------------------------------------------------------------------------------
  AlimPadraoOver - Recomposicao da alumina na cuba em caso de interrupcao de 
                   um check devido aa movimentacao manual do anodo ou a uma 
                   troca de pinos.
                   Alimentacao: overfeed (normal feed)
                   Condicao de saida: Fim do overfeed E do tempo de estabilizacao
-------------------------------------------------------------------------------
*/
int AlimPadraoOver(int cuba)
{
  int next_substate;
  byte FimTrackingOver;

  if (AVC.User1[cuba].InicioSubEst eq VERDADEIRO)
  {
    AVC.User1[cuba].InicioSubEst= FALSO;

    //Inicializa variaveis de overfeed
    InitTrackingOver(cuba);
  }

  /* Tracking para atingir overfeed desejado */
  FimTrackingOver= TrackingOver(cuba);

  /* verifica transicao de estado */
  if (FimTrackingOver eq VERDADEIRO)
  {
    next_substate= PADRAO_CHECK2;
  }
  else    
    next_substate=-1;
  
  return(next_substate);
} /* AlimPadraoOver */

/* -- fim AlimPadrao.c -- */
