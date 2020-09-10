/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.1

	PROJETO		: CBA - Companhia Brasileira de Aluminio SA

	SISTEMA		: SALAS 120KA II e III

	ARQUIVO		: AlimExcecao.c

	CONTEUDO	: Algoritmo de alimentacao point feeder para cuba em excecao:
                  Corrida, Quebrada ou Troca de Pinos

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
$Id: AlimExcecao.c,v 1.2 2004/07/05 19:10:24 leo Exp $

$Log: AlimExcecao.c,v $
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
  #include	<stdio.h>
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
int VerifCondAExc(int cuba);
void TerminaAlgExc(int cuba);
void InitAlimExc(int cuba);
int AlimExcEspera(int cuba);
int AlimExcEspCheck1(int cuba);
int AlimExcEspCheck2(int cuba);
int AlimExcEspCheck3(int cuba);
int AlimExcNormal(int cuba);
int AlimExcPreCheck(int cuba);
int AlimExcCheck1(int cuba);
int AlimExcCheck2(int cuba);
int AlimExcCheck3(int cuba);
int AlimExcCheck4(int cuba);
int AlimExcOver(int cuba);
int	AlimExcUsu(int cuba);

/*
-------------------------------------------------------------------------------
  AlimExcecao - Implementa o estado de alimentacao de Excecao do alg. CBA.
                Retorna proximo estado quando terminou o ciclo ou -1
                caso contrario.
-------------------------------------------------------------------------------
*/
int AlimExcecao(int cuba)
{
  int next_alg;   //proximo algoritmo de alimentacao a ser executado 
  int next_state;       //indica mudanca de estado dentro do algoritmo (1=mudou)

  /* -- incrementa tempo de permanencia no algoritmo -- */
  SUPERV_AVC(cuba).Sup.TAlimExc++;
  SUPERV_AVC_TURNO(cuba).Sup.TAlimExc++;

  /* Verifica condicoes para saida da alimentacao Excecao */
  next_alg= VerifCondAExc(cuba);
  if (next_alg ne -1)              //#2
  {
    /* Executa operacoes relativas ao fim do algoritmo */
    TerminaAlgExc(cuba);
  }
  else
  {
    if (AVC.User1[cuba].InicioAlgAtual) //#1
    {
      AVC.User1[cuba].InicioAlgAtual=FALSO;

      /* Inicializa variaveis ao entrar na alimentacao de Excecao */
      InitAlimExc(cuba);
    }

    do
    {
      /* Executa tarefas comuns a todos os estados */
      ComumEstados(cuba);

      /* Executa Rotina Referente a um estado */
      switch(AVC.User1[cuba].State)
      {
        case ALIM_EXC_ESPERA1:
          next_state= AlimExcEspera1(cuba);
          break;          
        case ALIM_EXC_ESPERA2:
          next_state= AlimExcEspera2(cuba);
          break;          
        case ALIM_EXC_ESP_CHECK1:
          next_state= AlimExcEspCheck1(cuba);
          break;          
        case ALIM_EXC_ESP_CHECK2:
          next_state= AlimExcEspCheck2(cuba);
          break;          
        case ALIM_EXC_ESP_CHECK3:
          next_state= AlimExcEspCheck3(cuba);
          break;          
        case ALIM_EXC_NORMAL:
          next_state= AlimExcNormal(cuba);
          break;          
        case ALIM_EXC_PRE_CHECK:
          next_state= AlimExcPreCheck(cuba);
          break;          
        case ALIM_EXC_CHECK1:
          next_state= AlimExcCheck1(cuba);
          break;          
        case ALIM_EXC_CHECK2:
          next_state= AlimExcCheck2(cuba);
          break;          
        case ALIM_EXC_CHECK3:
          next_state= AlimExcCheck3(cuba);
          break;          
        case ALIM_EXC_CHECK4:
          next_state= -1;
          next_alg= AlimExcCheck4(cuba); //ultimo estado do algoritmo!
          break;
        case ALIM_EXC_OVER:
          next_state= AlimExcOver(cuba); //estado de excecao durante check
          break;
        case ALIM_EXC_USU:
          next_state= AlimExcUsu(cuba); //estado de excecao usuario
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
} /* AlimExc */

/*
-------------------------------------------------------------------------------
  VerifCondAExc - Verifica condicoes para saida da alimentacao Excecao
                  Retorna proximo estado quando detecta alguma condicao
                  de saida ou -1 caso contrario.
-------------------------------------------------------------------------------
*/
int VerifCondAExc(int cuba)
{
  int next_state;

  next_state=-1;

  
  if (((HoraAtualSec-AVC.Ea[cuba].EaHoraInicio)>(AVC.ParUser1[cuba].MaxIntervEa*60)) and
	  (EST_AVC(cuba).Est.ManualAlimRem ne VERDADEIRO))
  { //entra em alimentacao suspensa para espera de EA
    next_state= EST_ALIM_SUSPENSA;
    AVC.User1[cuba].TempoSuspende= 0; //suspenso ate entrada em EA!!
  }
  else if ((EST_AVC(cuba).Est.ManualAlimLoc eq VERDADEIRO) and
      (AVC.User1[cuba].State ne ALIM_EXC_ESPERA1))
  {//Verifica chave de alimentacao manual/automatico (modificacao no campo)
	next_state=EST_ALIM_EXCECAO;
  }
  else if ((EST_AVC(cuba).Est.ManualAlimRem eq VERDADEIRO) and
          (AVC.User1[cuba].State ne ALIM_EXC_ESPERA1))
  { //verifica flag de alimentacao manual/automatico (via computador)
    next_state=EST_ALIM_EXCECAO;
  }
  else if ((EST_AVC(cuba).Ea eq VERDADEIRO) and 
           (EST_AVC(cuba).Est.ManualAlimLoc ne VERDADEIRO) and
           (EST_AVC(cuba).Est.ManualAlimRem ne VERDADEIRO))
  {
    next_state= EST_ALIM_EA;
  }
  else
  {
	//Regras de mudanca de algoritmo de acordo com o subestado atual
	switch(AVC.User1[cuba].State)
	{
	  case ALIM_EXC_ESPERA1:
	   break;          
	  case ALIM_EXC_ESPERA2:
	  case ALIM_EXC_ESP_CHECK1:
	  case ALIM_EXC_ESP_CHECK2:
	  case ALIM_EXC_ESP_CHECK3:
	  case ALIM_EXC_NORMAL:
	  case ALIM_EXC_PRE_CHECK:
	  case ALIM_EXC_CHECK1:
	  case ALIM_EXC_CHECK2:
	  case ALIM_EXC_CHECK3:
	  case ALIM_EXC_CHECK4:
      case ALIM_EXC_OVER:
       //verifica ocorrencia de excecao 
       if ((AVC.Cleit[cuba].HoraUltQueb>AVC.User1[cuba].HoraIniSubEstAtual) or
// Inserido em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
           (AVC.Cleit[cuba].HoraUltCorr>AVC.User1[cuba].HoraIniSubEstAtual))
       {
         next_state= EST_ALIM_EXCECAO; //comeca tratamento de nova excecao!
       }
	   break;
	} //switch
  }
  
  return(next_state);
} /* VerifConAExc */

/*
-------------------------------------------------------------------------------
  TerminaAlgExc - Executa operacoes relativas ao fim do algoritmo Excecao
-------------------------------------------------------------------------------
*/
void TerminaAlgExc(int cuba)
{
} /* TerminaAlgExc */

/*
-------------------------------------------------------------------------------
  InitAlimExc - Inicializa variaveis ao entrar na alimentacao Excecao
-------------------------------------------------------------------------------
*/
void InitAlimExc(int cuba)
{
} /* InitAlimExc */


/*
-------------------------------------------------------------------------------
  AlimExcEspera1 - Primeiro estado do check especial: aguarda tempo de 
                   acomodacao da cuba.
                   Durante este estado a alimentacao da cuba esta suspensa.
                   Condicao de saida: fim do tratamento da excecao
-------------------------------------------------------------------------------
*/
int AlimExcEspera1(int cuba)
{
  int next_substate;

  if (AVC.User1[cuba].InicioSubEst eq VERDADEIRO)
  {   
    /* Reseta flag de inicio de subestado */
    AVC.User1[cuba].InicioSubEst= FALSO;

    /* Habilita movimentacao do anodo */
    LiberaMoveAlim(cuba);

    /* Inicializa variavel com a hora do inicio do check */
    AVC.User1[cuba].HoraUltCheck= HoraAtualSec;

    /* Coloca flag de check como ativo */
    EST_AVC(cuba).Est.CheckAtivo=VERDADEIRO;

    //reseta numero de overfeeds em check
    AVC.User1[cuba].NumOverCheck=0;
  }

  //verifica se o tempo de estabilizacao de todas as excecoes ja foi cumprido
  if (((HoraAtualSec-AVC.Cleit[cuba].HoraUltQueb)>AVC.ParUser1[cuba].EstabQueb) and
      (EST_AVC(cuba).Est.ManualAlimLoc eq FALSO) and
// Inserido em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
	  ((HoraAtualSec-AVC.Cleit[cuba].HoraUltCorr)>AVC.ParUser1[cuba].EstabCorr) and
      (EST_AVC(cuba).Est.ManualAlimRem eq FALSO))
    next_substate= ALIM_EXC_ESPERA2;
  else    
    next_substate=-1; //permanece no estado atual

  return(next_substate);
} /* AlimExcEspera1 */

/*
-------------------------------------------------------------------------------
  AlimExcEspera2 - Aguarda tempo de estabilizacao apos movimentacao de anodo,
                   troca de pinos ou corrida. Espera tambem tempo de 
				   estabilizacao do filtro de resistencia.
                   Alimentacao: Normal feed 
-------------------------------------------------------------------------------
*/
int AlimExcEspera2(int cuba)
{
  int next_substate;

  if (AVC.User1[cuba].InicioSubEst eq VERDADEIRO)
  {   
    /* Reseta flag de inicio de estado */
    AVC.User1[cuba].InicioSubEst= FALSO;

    /* Habilita movimentacao do anodo */
    LiberaMoveAlim(cuba);

    /* Reseta integral parcial */
    AVC.User1[cuba].IntPar= 0;
  }

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

  /* Verifica se overfeed opcional esta habilitado */
  if (AVC.ParUser1[cuba].OverOpcional eq VERDADEIRO)
  {
    next_substate= ALIM_EXC_OVER;      
  }
  else if ((((HoraAtualSec-AVC.Ccont[cuba].HoraUltMove)>AVC.Param[cuba].TEfeitoMoveCima) and
            ((HoraAtualSec-AVC.Ccont[cuba].HoraUltMove)>AVC.Param[cuba].TEfeitoMoveBaixo)) and
// Alterado em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
//           ((HoraAtualSec-AVC.Cleit[cuba].HoraUltCorr)>AVC.Param[cuba].TEfeitoCorr) and
           ((HoraAtualSec-AVC.Cleit[cuba].HoraUltTPinos) > (AVC.Param[cuba].TEfeitoTPinos*60)) and
           ((HoraAtualSec-HoraPartidaMcpPF) >= T_ESTAB_FILT))
    next_substate= ALIM_EXC_ESP_CHECK1;   //verifica se tempo de estabilizacao ja foi vencido

  else    
    next_substate=-1;

  return(next_substate);
} /* AlimExcEspera2 */

/*
-------------------------------------------------------------------------------
  AlimExcEspCheck1 - Estado de monitoracao da resistencia de alimentacao
                     Alimentacao em underfeed
                     Condicao de saida: derivada da resistencia menor que
                                        parametro da base de dados

  OBS: Equivale ao segundo estado de um check normal (check2)
-------------------------------------------------------------------------------
*/
int AlimExcEspCheck1(int cuba)
{
  int next_substate;

  if (AVC.User1[cuba].InicioSubEst eq VERDADEIRO)
  {
    AVC.User1[cuba].InicioSubEst= FALSO;

    /* Inicializa variaveis utilizadas no estado
	   (equivale ao segundo estado de um check normal!) */
    InitCheck2(cuba);
  }

  /* Executa tarefas referentes aa monitoracao das derivadas da resistencia */
  Check2(cuba);

  /* Verifica transicao de estado:
      - Derivada muito negativa
      - Derivada negativa
      - Aconteceu condicao de excecao (corrida, troca de pinos, etc.) */
  next_substate= TransicaoCheck2(cuba, ALIM_EXC_OVER, ALIM_EXC_ESP_CHECK2);
  	  
  return(next_substate);
} /* AlimExcEspCheck1 */


/*
-------------------------------------------------------------------------------
  AlimExcEspCheck2 - Neste estado o algoritmo calcula as derivadas da resis-
                     tencia faltantes. 
					 Alimentacao em underfeed
					 Condicao de saida: Foi calculada a concentracao da cuba
					                    Aconteceu condicao de excecao

  OBS: Equivale ao terceiro estado de um check normal (check3)
-------------------------------------------------------------------------------
*/
int AlimExcEspCheck2(int cuba)
{
  int next_substate=-1;
  byte FimMonitDer;

  if (AVC.User1[cuba].InicioSubEst eq VERDADEIRO)
  {
    AVC.User1[cuba].InicioSubEst= FALSO;

    /* Inicializa subestado */
	InitCheck3(cuba);
  }

  /* Executa tarefas do subestado:
       - calcula derivadas e concentracao ate que o valor calculado p/
	     a concentracao seja menor ou igual a ConcValidCheck */
  FimMonitDer= Check3(cuba);
  
  /* Verifica transicao de estado:
       - Aconteceu excecao
	   - Concentracao calculada eh menor que ConcValidCheck */
  if ((AVC.Cleit[cuba].HoraUltTPinos > AVC.User1[cuba].HoraIniSubEstAtual) or
      (AVC.Cleit[cuba].HoraUltCorr > AVC.User1[cuba].HoraIniSubEstAtual) or
      (AVC.Ccont[cuba].HoraUltMove > AVC.User1[cuba].HoraIniSubEstAtual) or
  	  ((AVC.User1[cuba].DerResAlim < AVC.ParUser1[cuba].MaxDerInitCheck) and
      (AVC.User1[cuba].DerResAlimAnt < AVC.ParUser1[cuba].MaxDerInitCheck)))
  {
    next_substate= ALIM_EXC_OVER;
  }
  else if (FimMonitDer eq VERDADEIRO)
  {
    //Armazena concentracao de check
    AVC.User1[cuba].ConcCheckAnt= AVC.User1[cuba].ConcCheckAtual;
    AVC.User1[cuba].ConcCheckAtual= AVC.User1[cuba].ConcDer;

	next_substate= ALIM_EXC_ESP_CHECK3;
  }

  return(next_substate);
}

/*
-------------------------------------------------------------------------------
  AlimExcEspCheck3 - Usa over/under feed para levar a cuba para concentracao
                     nominal
                     Alimentacao: Under/over
                     Condicao de saida: chegar aa concentracao nominal

  OBS: Equivale ao quarto estado do check normal (check4)
-------------------------------------------------------------------------------
*/
int AlimExcEspCheck3(int cuba)
{
  int next_substate;
  byte fimtracking;

  
  if (AVC.User1[cuba].InicioSubEst)
  { /* primeira vez, inicializa variaveis */
    AVC.User1[cuba].InicioSubEst=FALSO;

    /* inicializa variaveis ao entrar em tracking de concentracao */
    InitCheck4(cuba);
  }

  /* Executa tarefas do subestado:
       - tracking da concentracao nominal */
  fimtracking= Check4(cuba);

  /* Verifica condicao de saida:
       - concentracao nominal foi atingida */
  next_substate= TransicaoCheck4(cuba,ALIM_EXC_NORMAL, fimtracking);	   

  return(next_substate);
}/* AlimExcEspCheck3 */

/*
-------------------------------------------------------------------------------
  AlimExcNormal - Coloca a cuba em normal feed e faz integracao da corrente
                  para finalizacao do check especial (segundo check)
                  Alimentacao: Normal feed
                  Condicao de saida: tempo de normal entre checks foi vencido
                                     ou ocorreu excecao (quebrada ou corrida)
-------------------------------------------------------------------------------
*/
int AlimExcNormal(int cuba)
{ /* retorna proximo estado ou -1 se continua no mesmo */
  int next_substate;

  /* Inicializa variaveis no inicio do subestado */
  if (AVC.User1[cuba].InicioSubEst eq VERDADEIRO)
  {
    AVC.User1[cuba].InicioSubEst= FALSO;

    /* Inicializa variaveis */
	InitNormalCE(cuba);
  }

  /* Executa tarefas referentes ao subestado de alimentacao normal:
       - Alimentar a cuba em normalfeed */
  NormalCE(cuba);
  	   
  /* Verifica transicao para check */
  next_substate= TransicaoNormalCE(cuba,ALIM_EXC_PRE_CHECK);
  
  return(next_substate);
} /* AlimExcNorm */

/*
-------------------------------------------------------------------------------
  AlimExcPreCheck -  Monitoracao de ruido na resistencia de alimentacao
                     Alimentacao em underfeed progressivo 
                     Condicao de saida: fim do ruido na resistencia
                     Retorna proximo subestado quando terminou o ciclo ou -1
                     caso contrario.
-------------------------------------------------------------------------------
*/
int AlimExcPreCheck(int cuba)
{ /* retorna proximo estado ou -1 se continua no mesmo */
  int next_substate;

  if (AVC.User1[cuba].InicioSubEst)
  { /* Reseta flag de entrada no subestado */
    AVC.User1[cuba].InicioSubEst=FALSO;

    /* Inicializa as variaveis do estado */
	InitPreCheck(cuba);
  }

  /* Executa as tarefas do PreCheck:
        - esperar pelo fim do ruido
		- fazer alimentacao underfeed progressivo */
  PreCheck(cuba);
  		
  /* Verifica condicoes de transicao do subestado:
        - Fim do ruido na resistencia de alimentacao */
  next_substate= TransicaoPreCheck(cuba, ALIM_EXC_CHECK1);
  
  return(next_substate);
} /* AlimExcPreCheck */


/*
-------------------------------------------------------------------------------
  AlimExcCheck1 - Espera que a resistencia de alimentacao estabilize 
                  Alimentacao: overfeed opcional/normal feed
                  Condicao de saida: Fim do overfeed opcional E
                                     cuba estavel
-------------------------------------------------------------------------------
*/
int AlimExcCheck1(int cuba)
{ /* retorna proximo estado ou -1 se continua no mesmo */
  int next_substate;
  byte FimTrackingOver;

  if (AVC.User1[cuba].InicioSubEst)
  { /* Reseta flag de entrada no subestado */
    AVC.User1[cuba].InicioSubEst=FALSO;

    /* Inicializa variaveis do subestado */
	InitCheck1(cuba);
  }

  /* Executa tarefas referentes ao estado atual */
  FimTrackingOver= Check1(cuba);

  /* Verifica transicao de estado:
       - balanco de alumina para overfeed opcional deve ser atingido
	   - tempo de estabilizacao deve ser respeitado */
  next_substate= TransicaoCheck1(cuba, ALIM_EXC_CHECK2, FimTrackingOver);

  return(next_substate);
} /* AlimExcCheck1 */

/*
-------------------------------------------------------------------------------
  AlimExcCheck2 - Monitora derivada da resistencia p/ calculo da derivada
                  Alimentacao: underfeed
                  Condicao de saida: obter duas derivadas da resistencia 
                                     maiores (em modulo) que a derivada minima.
-------------------------------------------------------------------------------
*/
int AlimExcCheck2(int cuba)
{ /* retorna proximo estado ou -1 se continua no mesmo */
  int next_substate;

  if (AVC.User1[cuba].InicioSubEst)
  { /* primeira vez, inicializa variaveis */
    AVC.User1[cuba].InicioSubEst=FALSO;

    //Inicializa variaveis do subestado
    InitCheck2(cuba);
  }

  //executa tarefas referentes a obtencao das derivadas iniciais
  Check2(cuba);

  /* verifica transicao de estado:
       - derivada muito negativa (overfeed)
	   - derivada negativa (mudar para proximo estado
	   - ocorreu excecao (troca de pinos ou movimentacao do anodo) */
  next_substate= TransicaoCheck2(cuba, ALIM_EXC_OVER,ALIM_EXC_CHECK3);	   

  return(next_substate);
} /* AlimExcCheck2 */

/*
-------------------------------------------------------------------------------
  AlimExcCheck3 - Obtem as derivadas faltantes e faz os calculos referentes
                  ao check.
                  Alimentacao: underfeed
                  Condicao de saida: derivadas da resistencia e calculos
                  do check foram realizados.
-------------------------------------------------------------------------------
*/
int AlimExcCheck3(int cuba)
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
       - Foi calculada a concentracao do check
	   - Ocorreu algum disturbio que altera a resistencia de alimentacao */
  next_substate= TransicaoCheck3(cuba, ALIM_EXC_OVER, ALIM_EXC_CHECK4, 
                                 FimMonitDer);
  return(next_substate);
} /* AlimExcCheck3 */

/*
-------------------------------------------------------------------------------
  AlimExcCheck4 - Levar a cuba p/ concentracao nominal
                  Alimentacao: under/over
                  Condicao de saida: chegar aa concentracao nominal 
                  Obs: Como este eh o ultimo subestado, ele retorna p/
                       o algoritmo Padrao.
-------------------------------------------------------------------------------
*/
int AlimExcCheck4(int cuba)
{ /* retorna proximo estado ou -1 se continua no mesmo */
  int next_alg;
  byte fimtracking;

  //executa inicializacoes na entrada do subestado
  if (AVC.User1[cuba].InicioSubEst)
  { /* Reseta flag que indica entrada no subestado */
    AVC.User1[cuba].InicioSubEst=FALSO;

    /* Inicializa variaveis no inicio do tracking */
    InitCheck4(cuba);
  }

  /* Faz tracking da concentracao nominal */
  fimtracking= Check4(cuba);

  /* Verifica condicao de saida:
       - Concentracao nominal foi atingida */
  next_alg= TransicaoCheck4(cuba,EST_ALIM_PADRAO,fimtracking);
	   
  return(next_alg);
} /* AlimExcCheck4 */

/*
-------------------------------------------------------------------------------
  AlimExcOver - Recomposicao da alumina na cuba em caso de interrupcao de um
                check devido aa movimentacao manual do anodo ou a uma troca
                de pinos.
                Alimentacao: overfeed
                Condicao de saida: Fim do overfeed E do tempo de estabilizacao
-------------------------------------------------------------------------------
*/
int AlimExcOver(int cuba)
{
  int next_substate;
  byte FimTrackingOver;  

  if (AVC.User1[cuba].InicioSubEst eq VERDADEIRO)
  {
    AVC.User1[cuba].InicioSubEst= FALSO;

    //Inicializa variaveis de overfeed
    InitTrackingOver(cuba);
  }

  /* Tracking p/ atingir overfeed desejado */
  FimTrackingOver= TrackingOver(cuba);

  /* verifica transicao de estado */
  if (FimTrackingOver eq VERDADEIRO) 
  {
     if ((AVC.User1[cuba].PrevState eq ALIM_EXC_ESPERA2) or
         (AVC.User1[cuba].PrevState eq ALIM_EXC_ESP_CHECK1) or
         (AVC.User1[cuba].PrevState eq ALIM_EXC_ESP_CHECK2))         
       next_substate= ALIM_EXC_ESP_CHECK1;
     else if ((AVC.User1[cuba].PrevState eq ALIM_EXC_CHECK2) or
              (AVC.User1[cuba].PrevState eq ALIM_EXC_CHECK3))
       next_substate= ALIM_EXC_CHECK2;
  }
  else    
    next_substate=-1;
  
  return(next_substate);
} /* AlimExcOver */

/*
-------------------------------------------------------------------------------
  AlimExcUsu -  Modulo de excecao ativado somente pelo operador
                Alimentacao: underfeed
                Condicao de saida: Desativacao do operador
-------------------------------------------------------------------------------
*/
int AlimExcUsu(int cuba)
{
  int next_substate;
  float interv_aux;

  if (AVC.User1[cuba].InicioSubEst eq VERDADEIRO)
  {
    AVC.User1[cuba].InicioSubEst= FALSO;
 	LiberaMoveAlim(cuba);
  }

  interv_aux= AVC.User1[cuba].IntervCurr/AVC.ParUser1[cuba].TaxaUnder;
  AVC.User2[cuba].TaxaFeedPF = AVC.ParUser1[cuba].TaxaUnder;

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
  if (AVC.ParUser2[cuba].HabExcUsuPF eq FALSO) 
  {
	next_substate= ALIM_EXC_ESPERA1;
  }
  else    
    next_substate=-1;
  
  return(next_substate);
} /* AlimExcOver */

/* -- AlimExcecao.c -- */