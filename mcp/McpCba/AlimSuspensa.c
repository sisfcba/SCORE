/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.1

	PROJETO		: CBA - Companhia Brasileira de Aluminio SA

	SISTEMA		: SALAS 120KA II e III

	ARQUIVO		: AlimSuspensa.c

	CONTEUDO	: Suspensao do algoritmo de alimentacao point feeder para 
                  que a cuba entre em efeito anodico programado ou para
                  atender solicitacao do operador.

	AUTOR		: Ricardo Teixeira Leite Mourao / Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	02/01/97

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
Data     | Descricao                                            | Autor 
-------------------------------------------------------------------------------
02/01/97 | Edicao inicial                                       | Ricardo-Leonel
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
int VerifCondSusp(int cuba);
void TerminaAlgSusp(int cuba);
void InitAlimSusp(int cuba);
int AlimSuspensa(int cuba);
int AlimSuspEspera(int cuba);

/*
-------------------------------------------------------------------------------
  AlimSuspensa - Implementa o algoritmo de suspensao da alimentacao para 
                 ocorrencia de EA programado ou devido a solicitacao do operador.
                 Retorna proximo algoritmo ao terminar o ciclo ou -1
                 em caso de permanencia no estado.
-------------------------------------------------------------------------------
*/
int AlimSuspensa(int cuba)
{
  int next_alg;      //proximo algoritmo de alimentacao a ser executado 

  /* -- incrementa tempo de permanencia no algoritmo -- */
  SUPERV_AVC(cuba).Sup.TAlimSusp++;
  SUPERV_AVC_TURNO(cuba).Sup.TAlimSusp++;

  /* Verifica condicoes para saida da suspensao de alimentacao (espera EA) */
  next_alg= VerifCondSusp(cuba);
  if (next_alg ne -1)              //#2
  {
    /* Executa operacoes relativas ao fim do algoritmo */
    TerminaAlgSusp(cuba);
  }
  else
  {
    if (AVC.User1[cuba].InicioAlgAtual) //#1
    {
      AVC.User1[cuba].InicioAlgAtual=FALSO;

      /* Inicializa variaveis ao entrar na alimentacao EA */
      InitAlimSusp(cuba);
    }                                   //#1

	if(AVC.User1[cuba].TempoSuspende > 0)
	{
	  AVC.User2[cuba].TaxaFeedPF = -1.0;
	}
	else
	{
	  AVC.User2[cuba].TaxaFeedPF = 0.0;
	}

    /* executa unico estado peretncente ao algoritmo */
    AlimSuspEspera(cuba);
  }                                //#2

  /* Retorna `a McpPF o proximo algoritmo a ser executado */
  return(next_alg);
} /* AlimSuspensa */

/*
-------------------------------------------------------------------------------
VerifCondSusp - Verifica condicoes para saida da alimentacao suspensa
                Condicoes de saida: Cuba entrou em efeito anodico ou intervalo
                                    de alimentacao suspensa foi atingido.
                Retorna proximo algoritmo quando detecta alguma condicao
                de saida ou -1 caso contrario.
-------------------------------------------------------------------------------
*/
int VerifCondSusp(int cuba)
{
  int next_state;

  next_state=-1;

  if (EST_AVC(cuba).Ea eq VERDADEIRO)
  {
    next_state= EST_ALIM_EA;
  }
  else if (((HoraAtualSec-AVC.User1[cuba].HoraIniSubEstAtual) >=
           AVC.User1[cuba].TempoSuspende) and 
          (AVC.User1[cuba].TempoSuspende>0)) //Se (TempoSuspende == 0)
  {                                          //  esperar efeito anodico!
    next_state= EST_ALIM_EXCECAO;
  }
  
  return(next_state);
} /* VerifCondSusp */

/*
-------------------------------------------------------------------------------
  TerminaAlgSusp - Executa operacoes relativas ao fim do algoritmo 
-------------------------------------------------------------------------------
*/
void TerminaAlgSusp(int cuba)
{
  EST_AVC(cuba).Est.AlimSuspensa = FALSO;
  EST_AVC(cuba).Est.ManualAlimRem = FALSO;
} /* TerminaAlgSusp */

/*
-------------------------------------------------------------------------------
  InitAlimSusp - Inicializa variaveis ao entrar na suspensao de alimentacao 
-------------------------------------------------------------------------------
*/
void InitAlimSusp(int cuba)
{
} /* InitAlimSusp */

/*
-------------------------------------------------------------------------------
  AlimSuspEspera - Suspende a alimentacao da cuba
-------------------------------------------------------------------------------
*/
void AlimSuspEspera(int cuba)
{
  if (AVC.User1[cuba].InicioSubEst eq VERDADEIRO)
  {
    AVC.User1[cuba].InicioSubEst= FALSO;

    if (AVC.ParUser1[cuba].HabMoveSusp eq HABILITA_MOVE)
      //habilita a movimentacao do anodo
      LiberaMoveAlim(cuba); 
    else
	  //desabilita movimentacao do anodo
      EST_AVC(cuba).InibeControleAlim= AVC.ParUser1[cuba].HabMoveSusp;
	  
  }

  /* Incrementa consumo de alumina no subestado atual */
  AVC.User1[cuba].ConsumoSubEst += TRAPEZIO(AVL.Iinst,IinstOld,IntervLeit)*
                                   K_CONSUMO*AVC.User1[cuba].EfiCurr;

} /* AlimSuspEspera */

/* -- fim AlimSuspensa.c -- */