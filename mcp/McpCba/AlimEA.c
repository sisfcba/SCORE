/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.1

	PROJETO		: CBA - Companhia Brasileira de Aluminio SA

	SISTEMA		: SALAS 120KA II e III

	ARQUIVO		: AlimEA.c

	CONTEUDO	: Algoritmo de alimentacao point feeder para cuba em Efeito
                  Anodico.

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
29/08/17 | TK-ALIM - Preparacão Toolkit Alimentacao             | Carlos
-------------------------------------------------------------------------------
$Id: AlimEA.c,v 1.2 2004/07/05 19:10:24 leo Exp $

$Log: AlimEA.c,v $
Revision 1.2  2004/07/05 19:10:24  leo
Correcao comparacao com TEfeitoTPinos (de segundos para minutos).

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
int VerifCondAEA(int cuba);
void TerminaAlgEA(int cuba);
void InitAlimEA(int cuba);
int AlimEAOverIni(int cuba);
int AlimEAPreCheckEsp(int cuba);
int AlimEAEspCheck1(int cuba);
int AlimEAEspCheck2(int cuba);
int AlimEAEspCheck3(int cuba);
int AlimEAEspCheck4(int cuba);
int AlimEANorm(int cuba);
int AlimEAPreCheck(int cuba);
int AlimEACheck1(int cuba);
int AlimEACheck2(int cuba);
int AlimEACheck3(int cuba);
int AlimEACheck4(int cuba);
int AlimEAOver(int cuba);

/*
-------------------------------------------------------------------------------
  AlimEA - Implementa o estado de alimentacao de EA do alg. CBA.
           Retorna proximo estado quando terminou o ciclo ou -1
	       caso contrario.
-------------------------------------------------------------------------------
*/
int AlimEA(int cuba)
{
  int next_alg;    //proximo algoritmo de alimentacao a ser executado 
  int next_state;  //indica mudanca de estado dentro do algoritmo (1=mudou)


  /* -- incrementa tempo de permanencia no algoritmo -- */
  SUPERV_AVC(cuba).Sup.TAlimEA++;
  SUPERV_AVC_TURNO(cuba).Sup.TAlimEA++;

  /* Verifica condicoes para saida da alimentacao EA */
  next_alg= VerifCondAEA(cuba);
  if (next_alg ne -1)              //#2
  {
    /* Executa operacoes relativas ao fim do algoritmo */
    TerminaAlgEA(cuba);
  }
  else
  {
    if (AVC.User1[cuba].InicioAlgAtual) //#1
    {
      AVC.User1[cuba].InicioAlgAtual=FALSO;

      /* Inicializa variaveis ao entrar na alimentacao EA */
      InitAlimEA(cuba);
    }
    do
    {
      /* Executa tarefas que sao comuns a todos os estados do algoritmo */
      ComumEstados(cuba);
      
      /* Executa Rotina Referente a um estado */
      switch(AVC.User1[cuba].State)
      {
        case EA_OVER_INICIAL:
          next_state=AlimEAOverIni(cuba);
          break;
        case EA_CHECK_ESP1:
          next_state=AlimEAEspCheck1(cuba);
          break;
        case EA_CHECK_ESP2:
          next_state=AlimEAEspCheck2(cuba);
          break;
        case EA_CHECK_ESP3:
          next_state=AlimEAEspCheck3(cuba);
          break;
        case EA_CHECK_ESP4:
          next_state=AlimEAEspCheck4(cuba);
          break;
        case EA_NORMAL:
          next_state=AlimEANorm(cuba);
          break;
        case EA_PRE_CHECK:
          next_state=AlimEAPreCheck(cuba);
          break;
        case EA_CHECK1:
          next_state=AlimEACheck1(cuba);
          break;
        case EA_CHECK2:
          next_state=AlimEACheck2(cuba);
          break;
        case EA_CHECK3:
          next_state=AlimEACheck3(cuba);
          break;
        case EA_CHECK4:
          next_state= -1;
          next_alg=AlimEACheck4(cuba);
          break;
        case EA_OVER:
          next_state=AlimEAOver(cuba);
          break;
      } //switch

      /* Faz mudanca de estado interno ao algoritmo EA */
      if (next_state ne -1)
        /* -- Muda para o novo estado -- */
        MudaEstadoSub(cuba,next_state);
    } while(next_state ne -1);
  }                                //#1

  /* Retorna `a McpPF o proximo algoritmo a ser executado */
  return(next_alg);
} /* AlimEA */

/*
-------------------------------------------------------------------------------
  VerifCondAEA - Verifica condicoes para saida da alimentacao EA
                Retorna proximo estado quando detecta alguma condicao
                de saida ou -1 caso contrario.
-------------------------------------------------------------------------------
*/
int VerifCondAEA(int cuba)
{
  int next_state;

  next_state=-1;

  if (((HoraAtualSec-AVC.Ea[cuba].EaHoraInicio)>(AVC.ParUser1[cuba].MaxIntervEa*60)) and
	  (EST_AVC(cuba).Est.ManualAlimRem ne VERDADEIRO))
  { //entra em alimentacao suspensa para espera de EA
    next_state= EST_ALIM_SUSPENSA;
    AVC.User1[cuba].TempoSuspende= 0; //suspenso ate entrada em EA!!
  }
  if (EST_AVC(cuba).Est.ManualAlimLoc eq VERDADEIRO)
  {//Verifica chave de alimentacao manual/automatico (modificacao no campo)
	next_state=EST_ALIM_EXCECAO;
  }
  else if (EST_AVC(cuba).Est.ManualAlimRem eq VERDADEIRO)
  { //verifica flag de alimentacao manual/automatico (via computador)
    next_state=EST_ALIM_EXCECAO;
  }
  else
  {
	//Regras de mudanca de algoritmo de acordo com o subestado atual
	switch(AVC.User1[cuba].State)
	{
	 case EA_OVER_INICIAL:
	   break;
	 case EA_CHECK_ESP1:
// Inserido em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
       if (EST_AVC(cuba).Corrida eq VERDADEIRO)
       {
         next_state= EST_ALIM_EXCECAO; //trata corrida a qualquer hora
       }
	   break;
	 case EA_CHECK_ESP2:
	 case EA_CHECK_ESP3:
	 case EA_CHECK_ESP4:
	 case EA_NORMAL:
	 case EA_PRE_CHECK:
	 case EA_CHECK1:
	 case EA_CHECK2:
	 case EA_CHECK3:
	 case EA_CHECK4:
	   if (EST_AVC(cuba).Ea eq VERDADEIRO)
	   {
		 next_state= EST_ALIM_EA;
	   }
       else if (EST_AVC(cuba).Quebrada eq VERDADEIRO)
       {
         next_state= EST_ALIM_EXCECAO; //trata quebrada a qualquer hora
       }
// Inserido em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
       else if (EST_AVC(cuba).Corrida eq VERDADEIRO)
       {
         next_state= EST_ALIM_EXCECAO; //trata corrida a qualquer hora
       }
	   break;
	} //switch
  }
  
  return(next_state);
} /* VerifConAEA */

/*
-------------------------------------------------------------------------------
  TerminaAlgEA - Executa operacoes relativas ao fim do algoritmo EA
-------------------------------------------------------------------------------
*/
void TerminaAlgEA(int cuba)
{
} /* TerminaAlgEA */

/*
-------------------------------------------------------------------------------
  InitAlimEA - Inicializa variaveis ao entrar na alimentacao EA
-------------------------------------------------------------------------------
*/
void InitAlimEA(int cuba)
{
} /* InitAlimEA */

/*
-------------------------------------------------------------------------------
  AlimEAOverIni - Executa overfeed na entrada em EA, quando habilitado
-------------------------------------------------------------------------------
*/
int AlimEAOverIni(int cuba)
{
  int next_substate;
  float interv_aux;

  if (AVC.User1[cuba].InicioSubEst eq VERDADEIRO)
  {
    AVC.User1[cuba].InicioSubEst= FALSO;

    /* Inicializa variavel com a hora do inicio do check */
    AVC.User1[cuba].HoraUltCheck= HoraAtualSec;

    /* Coloca flag de check como ativo */
    EST_AVC(cuba).Est.CheckAtivo=VERDADEIRO;

    /* Desabilita movimentacao do anodo */
    EST_AVC(cuba).InibeControleAlim=VERDADEIRO; 

    /* Reseta numero de overfeeds em check */
    AVC.User1[cuba].NumOverCheck= 0;
    if (AVC.ParUser1[cuba].HabilitaOverEA eq VERDADEIRO)
      AVC.User1[cuba].NumOverCheck++;

    /* Reseta integral parcial */
    AVC.User1[cuba].IntPar=0;
  }

  //Executa overfeed se este estiver habilitado e se uma quebrada nao tiver
  //sido sinalizada
  if ((AVC.ParUser1[cuba].HabilitaOverEA eq VERDADEIRO) and
      (AVC.User1[cuba].NumOverCheck <= AVC.ParUser1[cuba].MaxOverCheck) and
      (AVC.Cleit[cuba].HoraUltQueb < AVC.User1[cuba].HoraIniSubEstAtual))
  {
    /* calcula valor a ser integrado em overfeed */
    interv_aux= AVC.User1[cuba].IntervCurr/AVC.ParUser1[cuba].TaxaOverEA;
	AVC.User2[cuba].TaxaFeedPF = AVC.ParUser1[cuba].TaxaOverEA;

    /* Verifica se e' hora de acionar o Point Feeder */
    if ((AVC.User1[cuba].IntPar >= interv_aux) and
       ((HoraAtualSec-AVC.User1[cuba].HoraUltPF) >= AVC.ParUser1[cuba].MinIntervPF))
    {
      /* Reseta valor da integral parcial */
      AVC.User1[cuba].IntPar -= interv_aux;

      /* Comanda acionamento do point feeder */
      TrataAcionaPF(cuba);
    }
  }

  /* Verifica transicao de estado */
  //espera sinalizacao de quebrada!!!
  if ((EST_AVC(cuba).Ea eq FALSO) and
      ((AVC.Cleit[cuba].HoraUltQueb > AVC.User1[cuba].HoraIniSubEstAtual) or
       ((HoraAtualSec-AVC.User1[cuba].HoraIniSubEstAtual) >= AVC.ParUser1[cuba].MaxTOverEa)))
    next_substate= EA_CHECK_ESP1;
  else    
    next_substate=-1; //permanece em alimentacao normal

  return(next_substate);
} /* AlimEAOverIni */


/*
-------------------------------------------------------------------------------
  AlimEAEspCheck1 - Primeiro estado do check especial: aguarda tempo de 
                    acomodacao da cuba (nao ha alimentacao durante este 
                    estado, de modo a possibilitar o consumo da alumina
                    despejada na quebrada)
-------------------------------------------------------------------------------
*/
int AlimEAEspCheck1(int cuba)
{
  int next_substate;

  if (AVC.User1[cuba].InicioSubEst eq VERDADEIRO)
  {   
    AVC.User1[cuba].InicioSubEst= FALSO;

// Inserido em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
    //reseta integral parcial
    AVC.User1[cuba].IntPar= 0;

    //habilita movimentacao do anodo
    LiberaMoveAlim(cuba); 
  }

// Inserido em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
  /* Alimentar a cuba em normalfeed */
  if (AVC.ParUser1[cuba].HabNormFeedEa eq VERDADEIRO)
	NormalCE(cuba);

  if (((HoraAtualSec-AVC.Cleit[cuba].HoraUltTPinos) > (AVC.Param[cuba].TEfeitoTPinos*60)) and
      (((HoraAtualSec-AVC.Ccont[cuba].HoraUltMove)>AVC.Param[cuba].TEfeitoMoveCima) and
       ((HoraAtualSec-AVC.Ccont[cuba].HoraUltMove)>AVC.Param[cuba].TEfeitoMoveBaixo)) and
// Retirado em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
//      ((HoraAtualSec-AVC.Cleit[cuba].HoraUltCorr)>AVC.Param[cuba].TEfeitoCorr) and
      ((HoraAtualSec-AVC.Cleit[cuba].HoraUltQueb)>AVC.ParUser1[cuba].EstabQueb))
    next_substate= EA_CHECK_ESP2;
  else    
    next_substate=-1; //permanece em alimentacao suspensa

  return(next_substate);
} /* AlimEAEspCheck1 */

/*
-------------------------------------------------------------------------------
  AlimEAEspCheck2 - Monitoracao da derivada da resistencia
                    Alimentacao: underfeed
                    Condicao de saida: Derivadas menores que limite definido
                                       ou ocorrencia de excecao
-------------------------------------------------------------------------------
*/
int AlimEAEspCheck2(int cuba)
{
  int next_substate;

  if (AVC.User1[cuba].InicioSubEst eq VERDADEIRO)
  {
    //Reseta flag de inicio de subestado
    AVC.User1[cuba].InicioSubEst= FALSO;

    //reseta integral parcial
    AVC.User1[cuba].IntPar= 0;

    //Inicializa variaveis a serem utilizadas no subestado
    InitCheck2(cuba);
  }

  /* Armazena reistencias e calcula novas derivadas */
  Check2(cuba);

  /* Verifica transicao de estado:
       - Derivada muito negativa
	   - Derivada negativa
	   - Excecao (troca de pinos, corrida ou movimentacao do anodo) */
  next_substate= TransicaoCheck2(cuba, EA_OVER, EA_CHECK_ESP3);

  return(next_substate);
} /* AlimEAEspCheck2 */


/*
-------------------------------------------------------------------------------
  AlimEAEspCheck3 - Obtencao das derivadas da resistencia de alimentacao 
                    faltantes. Calculos do check (concentracao, eficiencia de
					corrente e intervalo de integracao)
                    Alimentacao: underfeed
                    Condicao de saida: obtencao das derivadas ou excecao
-------------------------------------------------------------------------------
*/
int AlimEAEspCheck3(int cuba)
{
  int next_substate=-1;
  byte FimMonitDer;

  if (AVC.User1[cuba].InicioSubEst eq VERDADEIRO)
  {
    /* Reseta Flag de inicio de subestado */
    AVC.User1[cuba].InicioSubEst= FALSO;

    /* Inicializa subestado */
    InitCheck3(cuba);
  }

  /* Monitora derivada da resistencia para obter concentracao de fim de check */
  FimMonitDer= Check3(cuba);
  
  //verifica transicao de estado
  if ((AVC.Cleit[cuba].HoraUltTPinos > AVC.User1[cuba].HoraIniSubEstAtual) or
      (AVC.Ccont[cuba].HoraUltMove > AVC.User1[cuba].HoraIniSubEstAtual) or
      (AVC.Cleit[cuba].HoraUltCorr > AVC.User1[cuba].HoraIniSubEstAtual))
  {
    next_substate= EA_OVER;
  }
  else if (FimMonitDer eq VERDADEIRO)
  {
    //Armazena concentracao de check
    AVC.User1[cuba].ConcCheckAnt= AVC.User1[cuba].ConcCheckAtual;
    AVC.User1[cuba].ConcCheckAtual= AVC.User1[cuba].ConcDer;

    next_substate= EA_CHECK_ESP4;
  }

  return(next_substate);
}

/*
-------------------------------------------------------------------------------
  AlimEAEspCheck4 - Leva a cuba para concentracao nominal
                    Alimentacao: Over/Under
                    Condicao de saida: concentracao da cuba igual a concen-
                                       tracao nominal
-------------------------------------------------------------------------------
*/
int AlimEAEspCheck4(int cuba)
{
  int next_substate;
  byte FimTracking;

  if (AVC.User1[cuba].InicioSubEst)
  { /* primeira vez, inicializa variaveis */
    AVC.User1[cuba].InicioSubEst=FALSO;

    /* Inicializa variaveis usadas no tracking da concetracao nominal */
    InitCheck4(cuba);
  }

  /* Executa as terefas do subestado:
       - Tracking da concentracao nominal */
  FimTracking= Check4(cuba);

  /* Verifica condicoes de transicao */
  next_substate= TransicaoCheck4(cuba, EA_NORMAL, FimTracking);

  return(next_substate);
}/* AlimEAEspCheck4 */

/*
-------------------------------------------------------------------------------
  AlimEANorm - Implementa o subestado normal do estado de alimentacao
				   EA CBA.
                   Retorna proximo subestado quando terminou o ciclo ou -1
                   caso contrario.
-------------------------------------------------------------------------------
*/
int AlimEANorm(int cuba)
{ /* retorna proximo estado ou -1 se continua no mesmo */
  int next_substate;

  /* Inicializa variaveis no inicio do subestado */
  if (AVC.User1[cuba].InicioSubEst eq VERDADEIRO)
  {
    /* Reseta flag de inicio de subestado */
    AVC.User1[cuba].InicioSubEst= FALSO;

    /* Inicializa subestado */
	InitNormalCE(cuba);
  }

  /* Executa tarefas referentes ao subestado:
      - Alimentar a cuba em normalfeed */
  NormalCE(cuba);	  

  /* Verifica transicao para check */
  next_substate= TransicaoNormalCE(cuba, EA_PRE_CHECK);

  return(next_substate);
} /* AlimEANorm */

/*
-------------------------------------------------------------------------------
  AlimEACheck1 - Verifica presenca de ruido de alimentacao na cuba
                 Alimentacao: Under progressivo
                 Condicao de saida: Cuba sem ruido de alimentacao                  
-------------------------------------------------------------------------------
*/
int AlimEAPreCheck(int cuba)
{ /* retorna proximo estado ou -1 se continua no mesmo */
  int next_substate;

  if (AVC.User1[cuba].InicioSubEst)
  { /* Reseta flag de inicio de subestado */
    AVC.User1[cuba].InicioSubEst=FALSO;

    /* Inicializa subestado */
	InitPreCheck(cuba);
  }

  /* Executa tarefas referentes ao subestado:
      - alimentar a cuba em underfeed pregressivo */
  PreCheck(cuba);
  	  
  /* Verifica presenca de ruido na cuba */
  next_substate= TransicaoPreCheck(cuba, EA_CHECK1);

  return(next_substate);
} /* AlimEACheck1 */


/*
-------------------------------------------------------------------------------
  AlimEACheck1 - Espera estabilizacao da cuba (movimentacao ou troca de pinos)
                 Alimentacao: Overfeed ou normal feed
                 Condicao de saida: fim do overfeed e curva estavel
-------------------------------------------------------------------------------
*/
int AlimEACheck1(int cuba)
{ /* retorna proximo estado ou -1 se continua no mesmo */
  int next_substate;
  byte FimTrackingOver;

  if (AVC.User1[cuba].InicioSubEst)
  { /* primeira vez, inicializa variaveis */
    AVC.User1[cuba].InicioSubEst=FALSO;

    /* Inicializa subestado */
	InitCheck1(cuba);
  }

  /* calcula balanco de alumina no estado */
  FimTrackingOver= Check1(cuba);

  /* Verifica transicao de estado:
       - balanco de alumina deve atingir percentual desejado de overfeed 
	   - tempo de estabilizacao deve ser respeitado */
  next_substate= TransicaoCheck1(cuba, EA_CHECK2, FimTrackingOver);

  return(next_substate);
} /* AlimEACheck1 */

/*
-------------------------------------------------------------------------------
  AlimEACheck2 - Monitora derivada da resistencia de alimentacao
                 Alimentacao: underfeed
                 Condicao de saida: derivadas sao maiores (modulo) do que a
                                    derivada de inicio de check ou ocorreu
                                    excecao 
-------------------------------------------------------------------------------
*/
int AlimEACheck2(int cuba)
{ /* retorna proximo estado ou -1 se continua no mesmo */
  int next_substate;

  if (AVC.User1[cuba].InicioSubEst)
  { /* primeira vez, inicializa variaveis */
    AVC.User1[cuba].InicioSubEst=FALSO;

    //Inicializa variaveis do subestado
    InitCheck2(cuba);
  }

  /* Armazena resistencias e monitora derivada */
  Check2(cuba);


  /* Verifica transicao de estado:
       - derivada muito negativa
	   - derivada negativa
	   - excecao (corrida, movimentacao do anodo ou troca de pinos */
  next_substate= TransicaoCheck2(cuba, EA_OVER, EA_CHECK3);

  return(next_substate);
} /* AlimEACheck2 */

/*
-------------------------------------------------------------------------------
  AlimEACheck3 - Calculo das derivadas faltantes mais calculos de check
                 Alimentacao: underfeed
                 Condicao de saida: fim dos calculos de check ou excecao
-------------------------------------------------------------------------------
*/
int AlimEACheck3(int cuba)
{ /* retorna proximo estado ou -1 se continua no mesmo */
  int next_substate;
  byte FimMonitDer;

  if (AVC.User1[cuba].InicioSubEst eq VERDADEIRO)
  {
    /* Reseta flag de inicio de subestado */
    AVC.User1[cuba].InicioSubEst= FALSO;

    /* Inicializa subestado */
	InitCheck3(cuba);   
  }

  /* Monitora derivada da resistencia para obter concentracao de fim de check */
  FimMonitDer= Check3(cuba);
  
  /* Verifica transicao de estado:
       - excecao
	   - Concentracao de check encontrada */
  next_substate= TransicaoCheck3(cuba, EA_OVER, EA_CHECK4, FimMonitDer);

  return(next_substate);
} /* AlimEACheck3 */

/*
-------------------------------------------------------------------------------
  AlimEACheck4 - Retornar a cuba p/ concentracao nominal
                 Alimentacao: under/over
                 Condicao de saida: chegar a concentracao nominal
                 obs: Ultimo estado deste algoritmo -> na saida, muda p/
                      Algoritmo de Alimentacao Padrao
-------------------------------------------------------------------------------
*/
int AlimEACheck4(int cuba)
{ /* retorna proximo estado ou -1 se continua no mesmo */
  int next_alg;
  byte FimTracking;

  if (AVC.User1[cuba].InicioSubEst)
  { /* primeira vez, inicializa variaveis */
    AVC.User1[cuba].InicioSubEst=FALSO;

    /* Inicializa variaveis usadas no tracking da concetracao nominal */
    InitCheck4(cuba);
  }

  /* Executa tracking da concetracao nominal */
  FimTracking= Check4(cuba);

  /* Verifica condicao de saida:
       - concentracao de check atingida */
  next_alg= TransicaoCheck4(cuba, EST_ALIM_PADRAO, FimTracking);
  	   
  return(next_alg);
} /* AlimEACheck4 */

/*
-------------------------------------------------------------------------------
  AlimEAOver - Recomposicao da alumina na cuba em caso de interrupcao de um
               check devido aa movimentacao manual do anodo ou a uma troca
               de pinos.
               Alimentacao: overfeed
               Condicao de saida: Fim do overfeed E do tempo de estabilizacao
-------------------------------------------------------------------------------
*/
int AlimEAOver(int cuba)
{
  int next_substate;
  byte FimTrackingOver;

  if (AVC.User1[cuba].InicioSubEst eq VERDADEIRO)
  {
    AVC.User1[cuba].InicioSubEst= FALSO;

    //Inicializa variaveis do overfeed
    InitTrackingOver(cuba);
  }

  /* Executa tracking do percentual de overfeed */
  FimTrackingOver= TrackingOver(cuba);

  /* verifica transicao de estado */
  if (FimTrackingOver eq VERDADEIRO)
  {
     if ((AVC.User1[cuba].PrevState eq EA_CHECK_ESP2) or
         (AVC.User1[cuba].PrevState eq EA_CHECK_ESP3))         
       next_substate= EA_CHECK_ESP2;
     else if ((AVC.User1[cuba].PrevState eq EA_CHECK2) or
              (AVC.User1[cuba].PrevState eq EA_CHECK3))
       next_substate= EA_CHECK2;
     else
       next_substate= EA_CHECK_ESP1; //esta condicao nunca deve acontecer!!! 
  }
  else    
    next_substate=-1;
  
  return(next_substate);
} /* AlimEAOver */

/* -- fim AlimEA.c -- */