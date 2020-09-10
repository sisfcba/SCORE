/******************************************************************************

			 ACCENTURE - ACCENTURE PLANT AND AUTOMATION SOLUTIONS
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 5.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO SA

	SISTEMA		: AUTOMACAO DAS SALAS 125 KA I, II, III, IV, V, VI E VII

	ARQUIVO		: FuncRecChavesCBA.c

	CONTEUDO	: Modulo encarregado de receber as mensagens enviadas pelas
				  remotas e processa-las. Estas mensagens contem a indicacao
				  de que alguma botoeira ou chave foi acionada no campo. Este
				  modulo marca entao na base de dados a acao ocorrida.
				  Na partida le as chaves de todas as remotas se o primeiro
				  parametro da mensagem de partida for igual a verdadeiro.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 1.0		  -		  DATA  : 30/10/2012

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
30/10/2012 | Separacao das funcoes para kit de desenvolvimento    | Leonel
-------------------------------------------------------------------------------
04/09/2015 | Integracao para sala II com ATN8                     | Leonel/Marco
-------------------------------------------------------------------------------
$Id: FuncRecChavesCBA.c,v 1.1.2.3 2015/07/02 14:12:34 clage Exp $

$Log: FuncRecChavesCBA.c,v $
Revision 1.1.2.3  2015/07/02 14:12:34  clage
Alteracao para sala II com ATN8.

Revision 1.1.2.2  2015/06/30 22:33:06  clage
Alteracoes para expansao de bd e troca de atn7 para atn8 na sala II

Revision 1.1.2.1  2012/10/30 13:09:00  leo
Separacao para o kit de desenvolvimento da CBA.

******************************************************************************/

/*
-------------------------------------------------------------------------------
						   Includes
-------------------------------------------------------------------------------
*/
#include	<RecChavesCBA.h>
#include	<stdarg.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<time.h>
#include	<sys/kernel.h>

/* -- Apontadores para as tabelas comuns -- */
#include	<VarsComum.h>

/*
-------------------------------------------------------------------------------
						   Funcoes
-------------------------------------------------------------------------------
*/
/*
--------------------------------------------------------------------------------
| trata_inc_tpinos - Ativa incremento de troca de pinos                        |
--------------------------------------------------------------------------------
*/
void trata_inc_tpinos(int Cuba)
{
  char	*PMsgParam;
  char	*PTipoInc;
  char	StrVInc[10];
  char	StrTInc[10];

  AVC.Ccont[Cuba].ContIncTPinos = -1;
  EST_AVC(Cuba).TrataTPinos = VERDADEIRO;

  /*-- Gera evento de selecao de modo de operacao --*/
  PMsgParam = ScoreGetStr(NOME_ATIVA);
  if ( AVC.Param[Cuba].TipoIncTPinos eq INCREMENTO_LINEAR )
	PTipoInc = ScoreGetStr(NOME_CONST);
  else
	PTipoInc = ScoreGetStr(NOME_RAMPA);
#ifdef INCREMENTO_RESISTENCIA
  sprintf( StrVInc,"%03.1f",AVC.Param[Cuba].IncTPinosInic * 1e6 );
#else
  sprintf( StrVInc,"%03.1f",AVC.Param[Cuba].IncTPinosInic * 1000.0 );
#endif
  sprintf( StrTInc,"%d:%02d",AVC.Param[Cuba].TIncTPinos/60,
			AVC.Param[Cuba].TIncTPinos Mod 60);
  GeraEvento( EV_INC_TROCA_PINOS, Cuba, -1, ScoreGetStr(NOME_PAINEL),
			  StrTInc, PTipoInc, StrVInc, PMsgParam );
}

/*
--------------------------------------------------------------------------------
| CancelaAjusteCamisa - Cancela o ajuste de camisa
--------------------------------------------------------------------------------
*/
void CancelaAjusteCamisa(int Cuba)
{
  if ((EST_AVC(Cuba).Est.AjusteCamisa eq VERDADEIRO) and
	  (EST_AVC(Cuba).Est.AbortaAjuste eq AJUSTE_NORMAL))
  {
	GeraEvento(CAMISA_NAO_AJUSTADA,Cuba,-1,"Operador", "Painel");
	EST_AVC(Cuba).Est.AbortaAjuste = ABORTA_CAMISA_MANUAL;
	AVC.User1[Cuba].ContTAjCam = 0.0;
  }

  EST_AVC(Cuba).Est.CamNAjust = FALSO;

} /*-- CancelaAjusteCamisa --*/

/* -- Alteracao - Inicio - Robson - 15/01/2001 - Modularizacao do recchaves -- */
/*
--------------------------------------------------------------------------------
| TrataBotoeiraQuebrada - Trata Acionamento de botoeira de quebrada
--------------------------------------------------------------------------------
*/
void TrataBotoeiraQuebrada(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo)
{
  int tmp_bit_old, tmp_bit_new;

  /* -- ***************** QUEBRADA **************** -- */
  tmp_bit_old=PegaEstadoIO(Cuba,AVC.Abs[Cuba].BitChaveQueb);
  tmp_bit_new=PegaBit(Masc, AVC.Abs[Cuba].BitChaveQueb);
  /* liga bit para proxima variacao (remota so envia qdo 0) */
  /* -- Alteracao - Inicio - 15/03/2001 - Leonel - correcao para sala 86 ka -- */
  if (Comum->IdentReducao ne 6)
	*EstAtual=LigaBit(*EstAtual,AVC.Abs[Cuba].BitChaveQueb);
  /* -- Alteracao - Fim - 15/03/2001 - Leonel - correcao para sala 86 ka -- */
  if ((tmp_bit_old ne tmp_bit_new) and (tmp_bit_new eq ESTADO_QUEB_ATIVA))
  {
	//	if (EST_AVC(Cuba).Quebrada eq FALSO)
	//	{
	//	  /* Reseta Incremento de quebrada para iniciar novamente */
	//	  AVC.Ccont[Cuba].IncQueb=0;
	//	  AVC.Ccont[Cuba].ContIncQueb=-1;
	//
	//	  EST_AVC(Cuba).Quebrada=VERDADEIRO;
	//	  AVC.Cleit[Cuba].HoraUltQueb=HoraAtual;	/* Hora da ultima quebrada */
	//	  GeraEvento(INICIO_QUEBRADA,Cuba,-1,ScoreGetStr(NOME_PAINEL),STR_TRACO,
	//				VCicCont,VInst,VAlvo);
	//	  *AlterouTab=TABELA_EST_AVC;
	//	}

    if(AVC.ParUser1[Cuba].HabilitaPF eq VERDADEIRO or 
    	AVC.ParUser2[Cuba].HabilitaPFCBA eq VERDADEIRO)
	{
	  AVC.User1[Cuba].RetornoAlF3 = VERDADEIRO;
 	}
  }

  /* -- ***************** CAMISA ALTA POTENCIOMETRO **************** -- */
  tmp_bit_old=PegaEstadoIO(Cuba,9);
  tmp_bit_new=PegaBit(Masc, 9);
  if ((tmp_bit_old ne tmp_bit_new) and (tmp_bit_new eq 0))
  {
    if(AVC.ParUser1[Cuba].HabilitaPF eq VERDADEIRO or 
    	AVC.ParUser2[Cuba].HabilitaPFCBA eq VERDADEIRO)
	{
	  EST_AVC(Cuba).Est.CamisaAlta = VERDADEIRO;
	}
  }
  if ((tmp_bit_old ne tmp_bit_new) and (tmp_bit_new eq 1))
  {
    if(AVC.ParUser1[Cuba].HabilitaPF eq VERDADEIRO or 
    	AVC.ParUser2[Cuba].HabilitaPFCBA eq VERDADEIRO)
	{
	  EST_AVC(Cuba).Est.CamisaAlta = FALSO;
	}
  }


  /* -- ***************** CAMISA BAIXA POTENCIOMETRO **************** -- */
  tmp_bit_old=PegaEstadoIO(Cuba,10);
  tmp_bit_new=PegaBit(Masc, 10);
  if ((tmp_bit_old ne tmp_bit_new) and (tmp_bit_new eq 0))
  {
    if(AVC.ParUser1[Cuba].HabilitaPF eq VERDADEIRO or 
    	AVC.ParUser2[Cuba].HabilitaPFCBA eq VERDADEIRO)
	{
	  EST_AVC(Cuba).Est.CamisaBaixa = VERDADEIRO;
	}
  }
  if ((tmp_bit_old ne tmp_bit_new) and (tmp_bit_new eq 1))
  {
    if(AVC.ParUser1[Cuba].HabilitaPF eq VERDADEIRO or 
    	AVC.ParUser2[Cuba].HabilitaPFCBA eq VERDADEIRO)
	{
	  EST_AVC(Cuba).Est.CamisaBaixa = FALSO;
	}
  }
}
/*
--------------------------------------------------------------------------------
| TrataBotoeiraCorrida - Trata Acionamento de botoeira de corrida
--------------------------------------------------------------------------------
*/
void TrataBotoeiraCorrida(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo)
{
int tmp_bit_old, tmp_bit_new;
  /* -- ***************** CORRIDA **************** -- */
  tmp_bit_old=PegaEstadoIO(Cuba,AVC.Abs[Cuba].BitChaveCorr);
  tmp_bit_new=PegaBit(Masc, AVC.Abs[Cuba].BitChaveCorr);
  /* liga bit para proxima variacao (remota so envia qdo 0) */
/* -- Alteracao - Inicio - 15/03/2001 - Leonel - correcao para sala 86 ka -- */
  if (Comum->IdentReducao ne 6)
	*EstAtual=LigaBit(*EstAtual,AVC.Abs[Cuba].BitChaveCorr);
/* -- Alteracao - Fim - 15/03/2001 - Leonel - correcao para sala 86 ka -- */
  if (tmp_bit_old ne tmp_bit_new)
  {
	if (tmp_bit_new eq ESTADO_CORR_ATIVA)
	{ /* acionada chave de corrida */
//	  if (EST_AVC(Cuba).Corrida eq FALSO)
//	  { /* permite corrida */
//		EST_AVC(Cuba).Corrida=VERDADEIRO;
//		AVC.Cleit[Cuba].HoraCorrAnt=AVC.Cleit[Cuba].HoraUltCorr;	/* Salva hora da ultima corrida */
//		AVC.Cleit[Cuba].HoraUltCorr=HoraAtual;	/* Hora da ultima corrida */
//		GeraEvento(INICIO_CORRIDA,Cuba,-1,ScoreGetStr(NOME_PAINEL),STR_TRACO,
//						VCicCont,VInst,VAlvo);
//		*AlterouTab=TABELA_EST_AVC;
//	  }
  	  if(AVC.ParUser1[Cuba].HabilitaPF eq VERDADEIRO or
    	AVC.ParUser2[Cuba].HabilitaPFCBA eq VERDADEIRO)
	  {
		AVC.User1[Cuba].RetornoAl2O3 = VERDADEIRO;
	  }
	}
  }

}
/*
--------------------------------------------------------------------------------
| TrataBotoeiraResetEA - Trata Acionamento de botoeira de reset EA
--------------------------------------------------------------------------------
*/
void TrataBotoeiraResetEA(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo)
{
int tmp_bit_old, tmp_bit_new;

  /* -- ***************** RESET EA ****************** -- */
  tmp_bit_old=PegaEstadoIO(Cuba,AVC.Abs[Cuba].BitResetEa);
  tmp_bit_new=PegaBit(Masc, AVC.Abs[Cuba].BitResetEa);
  /* liga bit para proxima variacao (remota so envia qdo 0) */
/* -- Alteracao - Inicio - 15/03/2001 - Leonel - correcao para sala 86 ka -- */
/* -- Alteracao - Inicio - 11/06/2002 - Leonel - correcao para sala 125ka -- */
/* -- CL01 - Upgrade para ATN8 na reducao II -- */
  if ( (Comum->IdentReducao > 2) and (Comum->IdentReducao < 6) )
/* -- Alteracao - Fim - 11/06/2002 - Leonel - correcao para sala 125ka -- */
	*EstAtual=LigaBit(*EstAtual,AVC.Abs[Cuba].BitResetEa); // so para as ATN7
/* -- Alteracao - Fim - 15/03/2001 - Leonel - correcao para sala 86 ka -- */
  if ((tmp_bit_old ne tmp_bit_new) and (tmp_bit_new eq ESTADO_RESET_EA))
  {  /* -- Verifica se e' para comandar reset de lampada de ea -- */
	ComandaLampEa(Cuba,DESLIGAR);
	if (EST_AVC(Cuba).ChaveLocRem ne LOCAL)
	  ComandaSirene(Cuba,DESLIGAR);
  }
}

/*
--------------------------------------------------------------------------------
| TrataChaveAutoMan - Trata Acionamento de botoeira de Auto-Man
--------------------------------------------------------------------------------
*/
void TrataChaveAutoMan(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo)
{
  int tmp_bit_old, tmp_bit_new, bit_acao;
 

  /* -- ************** CHAVE AUTOMATICO ************* -- */
/********************* teste para plataforma ******************/
/* gera valores de tensao e corrente de cuba mesmo com remotas
   ligadas pois as mesmas nao tem sinais analogicos conectados */
#ifdef	INCLUI_SIMULACAO_PLATAFORMA
  DesligaMascBit(Masc,AVC.Abs[Cuba].BitChaveLocRem);
#endif
/********************* teste para plataforma ******************/
  
  tmp_bit_old=PegaEstadoIO(Cuba,AVC.Abs[Cuba].BitChaveLocRem);
  tmp_bit_new=PegaBit(Masc, AVC.Abs[Cuba].BitChaveLocRem);

  if (AVC.User2[Cuba].ContEvChaves < 5)
  {
  	if (tmp_bit_old ne tmp_bit_new)
  	{
	  if (tmp_bit_new eq ESTADO_AUTOMATICO_ATIVO)
	  {
	  	if (EST_AVC(Cuba).ChaveLocRem ne REMOTO)
	    {
		  EST_AVC(Cuba).ChaveLocRem=REMOTO;
		  AVC.User2[Cuba].ContEvChaves++;
		  GeraEvento(EV_CHAVE_REMOTO,Cuba,-1,ScoreGetStr(NOME_PAINEL),STR_TRACO,
				VCicCont,VInst,VAlvo);
		  if ((AVC.ParUser1[Cuba].HabMCruzeiro) and (AVC.Abs[Cuba].BitChaveMCruzeiro ne 255)
		     and (EST_AVC(Cuba).Est.LiberaMCruzeiro))
		  { /* Retira permissao de manobra caso ela exista */
		  	EST_AVC(Cuba).Est.LiberaMCruzeiro=FALSO;
		  	bit_acao=AVC.Abs[Cuba].BitLiberaMCruzeiro;
		  	if (bit_acao ne 255)
		      ComandaSaidaRem(Cuba,DESLIGAR,bit_acao,0);
		  	GeraEvento(EV_MANOBRA_CRUZEIRO, Cuba, -1, "Habilita",
						  ScoreGetStr(SCORE_MSG_402), VCicCont,VInst,VAlvo);
		  }
		  *AlterouTab=TABELA_EST_AVC;
	    }
	  }
	  else
	  { /* -- **************** CHAVE LOCAL **************** -- */
	    if (EST_AVC(Cuba).ChaveLocRem ne LOCAL)
	    {
		  EST_AVC(Cuba).ChaveLocRem=LOCAL;
		  AVC.Cleit[Cuba].HoraUltSelMan=HoraAtual; /* Hora da ultima selecao manual */
		  GeraEvento(EV_CHAVE_LOCAL,Cuba,-1,ScoreGetStr(NOME_PAINEL),STR_TRACO,
				VCicCont,VInst,VAlvo);
		  *AlterouTab=TABELA_EST_AVC;
	    }
	  }
    }
  }
  if (AVC.User2[Cuba].ContEvChaves eq 5)
  {
	  GeraEvento(EV_CHAVE_LOCAL,Cuba,-1,"FALHA","L / R",
			  VCicCont,VInst,VAlvo);
	  EST_AVC(Cuba).ChaveLocRem=LOCAL;
	  AVC.Cleit[Cuba].HoraUltSelMan=HoraAtual; /* Hora da ultima selecao manual */
	  *AlterouTab=TABELA_EST_AVC;
	  AVC.User2[Cuba].ContEvChaves++;
  }
}

/*
--------------------------------------------------------------------------------
| TrataBotoeiraTrocaPinos - Trata Acionamento de botoeira de troca de pinos
--------------------------------------------------------------------------------
*/
void TrataBotoeiraTrocaPinos(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo)
{
int tmp_bit_old, tmp_bit_new;

  /* -- ************* TROCA DE PINOS **************** -- */
  /* CBA - Inicio: Alterado para tratar ATN7.0A na sala I - Leonel */
  /* Apenas invertido o teste para torna-lo mais claro */
  /* -- CL01 - Upgrade para ATN8 na reducao II -- */
  if (Comum->IdentReducao eq 3)
  /* CBA - Fim: Alterado para tratar ATN7.0A na sala I - Leonel */
  { /* reducao III possue botoeira de troca de pinos */
	tmp_bit_old=PegaEstadoIO(Cuba,AVC.Abs[Cuba].BitTrocaPinos);
	tmp_bit_new=PegaBit(Masc, AVC.Abs[Cuba].BitTrocaPinos);
	/* liga bit para proxima variacao (remota so envia qdo 0) */
	*EstAtual=LigaBit(*EstAtual,AVC.Abs[Cuba].BitTrocaPinos);
//	if (tmp_bit_old ne tmp_bit_new)
//	{
//	  if (tmp_bit_new eq ESTADO_TROCAPINOS_ATIVO)
//	  { /* acionada chave de troca de pinos */
//	    if (AVC.Param[Cuba].HabIncTPinos eq VERDADEIRO)
//	    {
//	      AVC.Cleit[Cuba].HoraUltTPinos=HoraAtual;	/* Hora da ultima troca de pinos */
//	      if (EST_AVC(Cuba).TrataTPinos eq FALSO)
//	      {
//		    trata_inc_tpinos(Cuba);
//		    *AlterouTab=TABELA_EST_AVC;
//	      }
//	    }
//	  }
//	}
  }
}

/*
--------------------------------------------------------------------------------
| TrataSubiuAnodo - Trata subida de anodo
--------------------------------------------------------------------------------
*/
void TrataSubiuAnodo(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo)
{
int tmp_bit_old, tmp_bit_new;

  /* -- ************* SUBIU ANODO **************** -- */
  tmp_bit_old=PegaEstadoIO(Cuba,AVC.Abs[Cuba].BitSubiuAnodo);
  tmp_bit_new=PegaBit(Masc, AVC.Abs[Cuba].BitSubiuAnodo);

  /* liga bit para proxima variacao (remota so envia qdo 0) */
  *EstAtual=LigaBit(*EstAtual,AVC.Abs[Cuba].BitSubiuAnodo);
  if ((tmp_bit_old ne tmp_bit_new) and (tmp_bit_new eq ESTADO_MOVEU_ANODO))
  {
	if (EST_AVC(Cuba).ChaveLocRem eq LOCAL)
	{
  	  EST_AVC(Cuba).Est.ZeraCA = VERDADEIRO;
	  EST_AVC(Cuba).EfeitoMove=VERDADEIRO;
	  AVC.Ccont[Cuba].HoraUltMove=HoraAtual;
	  AVC.Ccont[Cuba].SentidoUltMove=SUBIR_ANODO;
	  /* -- Subiu anodo manualmente -- */
	  GeraEvento(SUBIDA_MAN_ANODO,Cuba,-1,ScoreGetStr(NOME_PAINEL),STR_TRACO,
				VCicCont,VInst,VAlvo);
	}
	else
	{ /* -- chave em remoto -- */
	  if (EST_AVC(Cuba).ChaveAutMan eq MANUAL)
	  {
		EST_AVC(Cuba).EfeitoMove=VERDADEIRO;
		AVC.Ccont[Cuba].HoraUltMove=HoraAtual;
		AVC.Ccont[Cuba].SentidoUltMove=SUBIR_ANODO;
	  }
	  else
	  { /* -- Remoto/automatico -- */
		if ((HoraAtual-AVC.Ccont[Cuba].HoraUltMove) < 20)
		{ /* Confirmacao nos ultimos 20 segundos */
		  /* -- Contabiliza subida automatica de anodo -- */
		  /* -- *************** Dados medios diarios ******************* -- */
		  if (AVC.ParUser1[Cuba].HabContEficMov eq FALSO) 
		  {
			if (EST_AVC(Cuba).Ea eq FALSO)
			{
		      SUPERV_AVC(Cuba).MovCimaNumDia=SUPERV_AVC(Cuba).MovCimaNumDia+1;
		      SUPERV_AVC(Cuba).MovCimaDurDia=SUPERV_AVC(Cuba).MovCimaDurDia+
								 AVC.Ccont[Cuba].DuracaoUltMove;
		      /* -- *************** Dados medios de turno ******************* -- */
		      SUPERV_AVC_TURNO(Cuba).MovCimaNumDia=SUPERV_AVC_TURNO(Cuba).MovCimaNumDia+1;
		      SUPERV_AVC_TURNO(Cuba).MovCimaDurDia=SUPERV_AVC_TURNO(Cuba).MovCimaDurDia+
								 AVC.Ccont[Cuba].DuracaoUltMove;
		    }

		    GeraEvento(CNF_SUBIDA_AUT_ANODO,Cuba,-1);
	/* -- Alteracao - inicio - 25/11/2002 - Leonel - Separacao sobe e desce anodo -- */
		    /* -- Confirmacao movimentacao automatica de anodo -- */
		    EST_AVC(Cuba).EsperaConfMove=FALSO;
	/* -- Alteracao - fim - 25/11/2002 - Leonel - Separacao sobe e desce anodo -- */
		  }
		}
		else
		{ /* Moveu anodo manualmente */
  		  EST_AVC(Cuba).Est.ZeraCA = VERDADEIRO;
		  EST_AVC(Cuba).EfeitoMove=VERDADEIRO;
		  AVC.Ccont[Cuba].HoraUltMove=HoraAtual;
		  AVC.Ccont[Cuba].SentidoUltMove=SUBIR_ANODO;
		  /* -- Subiu anodo manualmente -- */
		  GeraEvento(SUBIDA_MAN_ANODO,Cuba,-1,ScoreGetStr(NOME_PAINEL),STR_TRACO,
			VCicCont,VInst,VAlvo);
		}
	  }
	}
/* -- Alteracao - inicio - 25/11/2002 - Leonel - Separacao sobe e desce anodo -- */
	/* -- Confirmacao movimentacao automatica de anodo -- */
	// *** retirado * confirma so em auto *** EST_AVC(Cuba).EsperaConfMove=FALSO;
/* -- Alteracao - fim - 25/11/2002 - Leonel - Separacao sobe e desce anodo -- */
  }
}

/*
--------------------------------------------------------------------------------
| TrataDesceuAnodo - Trata descida de anodo
--------------------------------------------------------------------------------
*/
void TrataDesceuAnodo(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo)
{
int tmp_bit_old, tmp_bit_new;

  /* -- ************* DESCEU ANODO **************** -- */
  tmp_bit_old=PegaEstadoIO(Cuba,AVC.Abs[Cuba].BitDesceuAnodo);
  tmp_bit_new=PegaBit(Masc, AVC.Abs[Cuba].BitDesceuAnodo);
  /* liga bit para proxima variacao (remota so envia qdo 0) */
  *EstAtual=LigaBit(*EstAtual,AVC.Abs[Cuba].BitDesceuAnodo);
  if ((tmp_bit_old ne tmp_bit_new) and (tmp_bit_new eq ESTADO_MOVEU_ANODO))
  {
	if (EST_AVC(Cuba).ChaveLocRem eq LOCAL)
	{
  	  EST_AVC(Cuba).Est.ZeraCA = VERDADEIRO;
	  EST_AVC(Cuba).EfeitoMove=VERDADEIRO;
	  AVC.Ccont[Cuba].HoraUltMove=HoraAtual;
	  AVC.Ccont[Cuba].SentidoUltMove=DESCER_ANODO;
	  /* -- Desceu anodo manualmente -- */
	  GeraEvento(DESCIDA_MAN_ANODO,Cuba,-1,ScoreGetStr(NOME_PAINEL),STR_TRACO,
				VCicCont,VInst,VAlvo);
	}
	else
	{ /* -- chave em remoto -- */
	  if (EST_AVC(Cuba).ChaveAutMan eq MANUAL)
	  {
		EST_AVC(Cuba).EfeitoMove=VERDADEIRO;
		AVC.Ccont[Cuba].HoraUltMove=HoraAtual;
		AVC.Ccont[Cuba].SentidoUltMove=DESCER_ANODO;
	  }
	  else
	  { /* -- Remoto/automatico -- */
		if ((HoraAtual-AVC.Ccont[Cuba].HoraUltMove) < 20)
		{ /* Confirmacao nos ultimos 20 segundos */
		  /* -- Contabiliza descida automatica de anodo -- */
		  /* -- *************** Dados medios diarios ******************* -- */
		  if ( AVC.ParUser1[Cuba].HabContEficMov eq FALSO)
		  {
			if (EST_AVC(Cuba).Ea eq FALSO)
			{
		      SUPERV_AVC(Cuba).MovBaixoNumDia=SUPERV_AVC(Cuba).MovBaixoNumDia+1;
		      SUPERV_AVC(Cuba).MovBaixoDurDia=SUPERV_AVC(Cuba).MovBaixoDurDia+
									  AVC.Ccont[Cuba].DuracaoUltMove;
		      /* -- *************** Dados medios de turno ******************* -- */
		      SUPERV_AVC_TURNO(Cuba).MovBaixoNumDia=SUPERV_AVC_TURNO(Cuba).MovBaixoNumDia+1;
		      SUPERV_AVC_TURNO(Cuba).MovBaixoDurDia=SUPERV_AVC_TURNO(Cuba).MovBaixoDurDia+
									  AVC.Ccont[Cuba].DuracaoUltMove;
			}
		    GeraEvento(CNF_DESCIDA_AUT_ANODO,Cuba,-1);
	/* -- Alteracao - inicio - 25/11/2002 - Leonel - Separacao sobe e desce anodo -- */
		    /* -- Confirmacao movimentacao automatica de anodo -- */
		    EST_AVC(Cuba).EsperaConfMove=FALSO;
	/* --   Alteracao - fim - 25/11/2002 - Leonel - Separacao sobe e desce anodo -- */
		  }
		}
		else
		{ /* Moveu anodo manualmente */
  		  EST_AVC(Cuba).Est.ZeraCA = VERDADEIRO;
		  EST_AVC(Cuba).EfeitoMove=VERDADEIRO;
		  AVC.Ccont[Cuba].HoraUltMove=HoraAtual;
		  AVC.Ccont[Cuba].SentidoUltMove=DESCER_ANODO;
		  /* -- Desceu anodo manualmente -- */
		  GeraEvento(DESCIDA_MAN_ANODO,Cuba,-1,ScoreGetStr(NOME_PAINEL),STR_TRACO,
				VCicCont,VInst,VAlvo);
		}
	  }
	}
/* -- Alteracao - inicio - 25/11/2002 - Leonel - Separacao sobe e desce anodo -- */
	/* -- Confirmacao movimentacao automatica de anodo -- */
// *** confirma so qdo em auto ***	EST_AVC(Cuba).EsperaConfMove=FALSO;
/* -- Alteracao - fim - 25/11/2002 - Leonel - Separacao sobe e desce anodo -- */
  }
}

/*
--------------------------------------------------------------------------------
| TrataSubiuCamisa - Trata subida de camisa
--------------------------------------------------------------------------------
*/
void TrataSubiuCamisa(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						    time_t	HoraAtual,float VCicCont,float VInst,float VAlvo,
							int *EnviaReconhece)
{
int tmp_bit_old, tmp_bit_new;

  /* -- ************* SUBIU CAMISA **************** -- */
  tmp_bit_old=PegaEstadoIO(Cuba,AVC.Abs[Cuba].BitSubOuMovCamisaouM2);
  tmp_bit_new=PegaBit(Masc, AVC.Abs[Cuba].BitSubOuMovCamisaouM2);
  /* liga bit para proxima variacao (remota so envia qdo 0) */
  *EstAtual=LigaBit(*EstAtual,AVC.Abs[Cuba].BitSubOuMovCamisaouM2);
  if ((tmp_bit_old ne tmp_bit_new) and (tmp_bit_new eq ESTADO_SUBIU_CAMISA))
  {
	if (AVC.Param[Cuba].TemPF eq FALSO)
	{ /* cuba sem point feeder */
	  if (EST_AVC(Cuba).ChaveLocRem eq LOCAL)
	  {
		GeraEvento(SUBIDA_MAN_CAMISA,Cuba,-1,ScoreGetStr(NOME_PAINEL),STR_TRACO,
				VCicCont,VInst,VAlvo);

//		GeraEvento(MOVE_MAN_CAMISA,Cuba,-1,ScoreGetStr(NOME_PAINEL),STR_TRACO,
//				VCicCont,VInst,VAlvo);
		/*-- Cancela ajuste de camisa --*/
		CancelaAjusteCamisa(Cuba);
	  }
	}
	else
    { /* **** Cuba com Point feeder ***** */
	  if (EST_AVC(Cuba).ChaveLocRem eq LOCAL)
	  {
	    GeraEvento(SUBIDA_MAN_CAMISA,Cuba,-1,ScoreGetStr(NOME_PAINEL),STR_TRACO,
				VCicCont,VInst,VAlvo);

	    /*-- Cancela ajuste de camisa --*/
	    CancelaAjusteCamisa(Cuba);
	  }
	  /* Cuba com point feeder sempre envia o reconhece por causa da chave
	     auto/man */
	  *EnviaReconhece=VERDADEIRO;
    }
  }
}

/*
--------------------------------------------------------------------------------
| TrataDesceuCamisa - Trata descida de camisa/auto man do point feeder
--------------------------------------------------------------------------------
*/
void TrataDesceuCamisa(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo)
{
int tmp_bit_old, tmp_bit_new;

  tmp_bit_old=PegaEstadoIO(Cuba,AVC.Abs[Cuba].BitDesCamOuPFAutoouM1);
  tmp_bit_new=PegaBit(Masc, AVC.Abs[Cuba].BitDesCamOuPFAutoouM1);
//  if (AVC.Param[Cuba].TemPF eq FALSO)
//  { /* cuba sem point feeder */
//	/* -- ************* DESCEU CAMISA **************** -- */
//	/* liga bit para proxima variacao (remota so envia qdo 0) */
//	*EstAtual=LigaBit(*EstAtual,AVC.Abs[Cuba].BitDesCamOuPFAutoouM1);
//	if ((tmp_bit_old ne tmp_bit_new) and (tmp_bit_new eq ESTADO_DESCEU_CAMISA))
//	{
//	  if (EST_AVC(Cuba).ChaveLocRem eq LOCAL)
//	  {
//		GeraEvento(DESCIDA_MAN_CAMISA,Cuba,-1,ScoreGetStr(NOME_PAINEL),STR_TRACO,
//		GeraEvento(MOVE_MAN_CAMISA,Cuba,-1,ScoreGetStr(NOME_PAINEL),STR_TRACO,
//				VCicCont,VInst,VAlvo);
//
//		/*-- Cancela ajuste de camisa --*/
//		CancelaAjusteCamisa(Cuba);
//	  }
//	}
//  }
/* -- Alteracao - Inicio - Robson - 14/11/2000 - Acionamento do novo PF -- */
//  else // Chave automatico manual do PF
//  {
//	/* -- ************* CHAVE MANUAL/AUTO PF **************** -- */
//	if (tmp_bit_old ne tmp_bit_new) 
//	{
//	  if (tmp_bit_new eq ESTADO_AUTOMATICO_ATIVO)
//		GeraEvento(EV_CHAVE_REMOTO,Cuba,-1,ScoreGetStr(NOME_PAINEL),"Aliment",
//				VCicCont,VInst,VAlvo);
//	  else
//		GeraEvento(EV_CHAVE_LOCAL,Cuba,-1,ScoreGetStr(NOME_PAINEL),"Aliment",
//				VCicCont,VInst,VAlvo);
//	}
//  }
/* -- Alteracao - Fim - Robson - 14/11/2000 - Acionamento do novo PF -- */
}

/*
--------------------------------------------------------------------------------
| TrataBotoeiraChkUp - Trata botoeira de check-up
--------------------------------------------------------------------------------
*/
void TrataBotoeiraChkUp(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo)
{
int tmp_bit_old, tmp_bit_new;

  /* -- ***************** BOTOEIRA CHECK UP ****************** -- */
  tmp_bit_old=PegaEstadoIO(Cuba,AVC.Abs[Cuba].BitCheckUp);
  tmp_bit_new=PegaBit(Masc, AVC.Abs[Cuba].BitCheckUp);
  /* liga bit para proxima variacao (remota so envia qdo 0) */
  *EstAtual=LigaBit(*EstAtual,AVC.Abs[Cuba].BitCheckUp);
  if ((tmp_bit_old ne tmp_bit_new) and (tmp_bit_new eq ESTADO_CHECKUP_ATIVO))
  {
	  if (AVC.Abs[Cuba].BitLampEa ne 255) 
		ComandaSaidaRem(Cuba,LIGAR,AVC.Abs[Cuba].BitLampEa,5*TEMPO_RECONHECE);
  }
}

/******************** Versao com subiu e desceu anodo separados ***************/
/*
--------------------------------------------------------------------------------
| TrataMoveuAnodo125ka - Trata movimento de anodo para sala 125ka (red 7)
--------------------------------------------------------------------------------
*/
void TrataMoveuAnodo125ka(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo)
{
  int tmp_bit_new, tmp_bit_old;

  /* ************* TRATA DESCIDA DE ANODO ********************* */
  tmp_bit_new=PegaBit(Masc, AVC.Abs[Cuba].BitDesceuAnodo);  /* O bit de desceu e subiu eh o mesmo */
  tmp_bit_old=PegaEstadoIO(Cuba,AVC.Abs[Cuba].BitDesceuAnodo);
  if ((tmp_bit_old ne tmp_bit_new) and (tmp_bit_new eq ESTADO_MOVEU_ANODO))
  { /* moveu */
	if (EST_AVC(Cuba).ChaveLocRem eq LOCAL)
	{ /* movimentacao manual */
  	  EST_AVC(Cuba).Est.ZeraCA = VERDADEIRO;
	  EST_AVC(Cuba).EfeitoMove=VERDADEIRO;
	  AVC.Ccont[Cuba].HoraUltMove=HoraAtual;
	  AVC.User2[Cuba].HoraUltMovPainel=HoraAtual;
	  AVC.Ccont[Cuba].SentidoUltMove=DESCER_ANODO;
	  /* -- Desceu anodo manualmente -- */
	  GeraEvento(DESCIDA_MAN_ANODO,Cuba,-1,ScoreGetStr(NOME_PAINEL),STR_TRACO,
				VCicCont,VInst,VAlvo);
	}
	else
	{ /* -- chave em remoto -- */
	  if (EST_AVC(Cuba).ChaveAutMan eq MANUAL)
	  { /* comando manual pelo computador */
		EST_AVC(Cuba).EfeitoMove=VERDADEIRO;
		AVC.Ccont[Cuba].HoraUltMove=HoraAtual;
		AVC.Ccont[Cuba].SentidoUltMove=DESCER_ANODO;
	  }
	  else
	  { /* -- Remoto/automatico -- */
		if ((HoraAtual-AVC.Ccont[Cuba].HoraUltMove) < 20)
		{ /* Confirmacao nos ultimos 20 segundos */
		  /* -- Contabiliza descida automatica de anodo -- */
		  /* -- *************** Dados medios diarios ******************* -- */
		  if ( AVC.ParUser1[Cuba].HabContEficMov eq FALSO)
		  {
			if (EST_AVC(Cuba).Ea eq FALSO)
			{			
		      SUPERV_AVC(Cuba).MovBaixoNumDia=SUPERV_AVC(Cuba).MovBaixoNumDia+1;
		      SUPERV_AVC(Cuba).MovBaixoDurDia=SUPERV_AVC(Cuba).MovBaixoDurDia+
									  AVC.Ccont[Cuba].DuracaoUltMove;
		      /* -- *************** Dados medios de turno ******************* -- */
		      SUPERV_AVC_TURNO(Cuba).MovBaixoNumDia=SUPERV_AVC_TURNO(Cuba).MovBaixoNumDia+1;
		      SUPERV_AVC_TURNO(Cuba).MovBaixoDurDia=SUPERV_AVC_TURNO(Cuba).MovBaixoDurDia+
									  AVC.Ccont[Cuba].DuracaoUltMove;
			}
			
			if (EST_AVC(Cuba).EsperaConfMove eq VERDADEIRO)
		    {
			  GeraEvento(CNF_DESCIDA_AUT_ANODO,Cuba,-1);
		      /* -- Confirmacao movimentacao automatica de anodo -- */
		      EST_AVC(Cuba).EsperaConfMove=FALSO;
			}
	  	  }
		}
		else
		{ /* Moveu anodo manualmente */
  		  EST_AVC(Cuba).Est.ZeraCA = VERDADEIRO;
		  EST_AVC(Cuba).EfeitoMove=VERDADEIRO;
		  AVC.Ccont[Cuba].HoraUltMove=HoraAtual;
		  AVC.Ccont[Cuba].SentidoUltMove=DESCER_ANODO;
		  /* -- Desceu anodo manualmente -- */
		  GeraEvento(DESCIDA_MAN_ANODO,Cuba,-1,ScoreGetStr(NOME_PAINEL),STR_TRACO,
				VCicCont,VInst,VAlvo);
		}
	  }
	}
  }

  /* ************* TRATA SUBIDA DE ANODO ********************* */
  tmp_bit_old=PegaEstadoIO(Cuba,AVC.Abs[Cuba].BitSubiuAnodo);
  tmp_bit_new=PegaBit(Masc, AVC.Abs[Cuba].BitSubiuAnodo);
  if ((tmp_bit_old ne tmp_bit_new) and (tmp_bit_new eq ESTADO_MOVEU_ANODO))
  { /* moveu */
	if (EST_AVC(Cuba).ChaveLocRem eq LOCAL)
	{ /* movimentacao manual */
  	  EST_AVC(Cuba).Est.ZeraCA = VERDADEIRO;
	  EST_AVC(Cuba).EfeitoMove=VERDADEIRO;
	  AVC.Ccont[Cuba].HoraUltMove=HoraAtual;
	  AVC.Ccont[Cuba].SentidoUltMove=SUBIR_ANODO;
	  AVC.User2[Cuba].HoraUltMovPainel=HoraAtual;
	  /* -- Subiu anodo manualmente -- */
	  GeraEvento(SUBIDA_MAN_ANODO,Cuba,-1,ScoreGetStr(NOME_PAINEL),STR_TRACO,
				VCicCont,VInst,VAlvo);
	}
	else
	{ /* -- chave em remoto -- */
	  if (EST_AVC(Cuba).ChaveAutMan eq MANUAL)
	  { /* comando manual pelo computador */
		EST_AVC(Cuba).EfeitoMove=VERDADEIRO;
		AVC.Ccont[Cuba].HoraUltMove=HoraAtual;
		AVC.Ccont[Cuba].SentidoUltMove=SUBIR_ANODO;
	  }
	  else
	  { /* -- Remoto/automatico -- */
		if ((HoraAtual-AVC.Ccont[Cuba].HoraUltMove) < 20)
		{ /* Confirmacao nos ultimos 20 segundos */
		  /* -- Contabiliza subida automatica de anodo -- */
		  /* -- *************** Dados medios diarios ******************* -- */
		  if ( AVC.ParUser1[Cuba].HabContEficMov eq FALSO) 
		  {
			if (EST_AVC(Cuba).Ea eq FALSO)
			{			
		      SUPERV_AVC(Cuba).MovCimaNumDia=SUPERV_AVC(Cuba).MovCimaNumDia+1;
		      SUPERV_AVC(Cuba).MovCimaDurDia=SUPERV_AVC(Cuba).MovCimaDurDia+
								 AVC.Ccont[Cuba].DuracaoUltMove;
		      /* -- *************** Dados medios de turno ******************* -- */
		      SUPERV_AVC_TURNO(Cuba).MovCimaNumDia=SUPERV_AVC_TURNO(Cuba).MovCimaNumDia+1;
		      SUPERV_AVC_TURNO(Cuba).MovCimaDurDia=SUPERV_AVC_TURNO(Cuba).MovCimaDurDia+
								 AVC.Ccont[Cuba].DuracaoUltMove;
			}

			if (EST_AVC(Cuba).EsperaConfMove eq VERDADEIRO)
		    {
			  GeraEvento(CNF_SUBIDA_AUT_ANODO,Cuba,-1);
		      /* -- Confirmacao movimentacao automatica de anodo -- */
		      EST_AVC(Cuba).EsperaConfMove=FALSO;
 			}
		  }
		}
		else
		{ /* Moveu anodo manualmente */
  		  EST_AVC(Cuba).Est.ZeraCA = VERDADEIRO;
		  EST_AVC(Cuba).EfeitoMove=VERDADEIRO;
		  AVC.Ccont[Cuba].HoraUltMove=HoraAtual;
		  AVC.Ccont[Cuba].SentidoUltMove=SUBIR_ANODO;
		  /* -- Subiu anodo manualmente -- */
		  GeraEvento(SUBIDA_MAN_ANODO,Cuba,-1,ScoreGetStr(NOME_PAINEL),STR_TRACO,
				VCicCont,VInst,VAlvo);
		}
	  }
	} /* chave em remoto */
  } 

}
/* -- Alteracao - fim - 25/11/2002 - Leonel - Separacao sobe e desce anodo -- */

/*
--------------------------------------------------------------------------------
| TrataMoveuCamisa125ka - Trata movimentacao de camisa da sala 125ka (red 7)
--------------------------------------------------------------------------------
*/
void TrataMoveuCamisa125ka(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						    time_t	HoraAtual,float VCicCont,float VInst,float VAlvo,
							int *EnviaReconhece)
{
  int tmp_bit_old, tmp_bit_new;

  tmp_bit_old=PegaEstadoIO(Cuba,AVC.Abs[Cuba].BitSubOuMovCamisaouM2);
  tmp_bit_new=PegaBit(Masc, AVC.Abs[Cuba].BitSubOuMovCamisaouM2);
  if ((tmp_bit_old ne tmp_bit_new) and (tmp_bit_new eq ESTADO_SUBIU_CAMISA))
  { /* -- ************* MOVEU CAMISA **************** -- */
	if (EST_AVC(Cuba).ChaveLocRem eq LOCAL)
	{
	  GeraEvento(DESCIDA_MAN_CAMISA,Cuba,-1,ScoreGetStr(NOME_PAINEL),STR_TRACO,
				VCicCont,VInst,VAlvo);

	  /*-- Cancela ajuste de camisa --*/
	  CancelaAjusteCamisa(Cuba);
	}
	*EnviaReconhece=VERDADEIRO;
  }
}

/*
--------------------------------------------------------------------------------
| TrataSopro - Trata indicacao de sopro
--------------------------------------------------------------------------------
*/
void TrataSopro(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						    time_t	HoraAtual,float VCicCont,float VInst,float VAlvo,
							int *EnviaReconhece)
{
  int tmp_bit_old, tmp_bit_new;

  if (AVC.Abs[Cuba].BitSoprou ne 255)
  { /* Existe entrada configurada */
	tmp_bit_old=PegaEstadoIO(Cuba,AVC.Abs[Cuba].BitSoprou);
	tmp_bit_new=PegaBit(Masc, AVC.Abs[Cuba].BitSoprou);
	if ((tmp_bit_old ne tmp_bit_new) and (tmp_bit_new eq ESTADO_SOPRO_ATIVO))
	{ /* -- ************* SOPROU **************** -- */
	  /*-- Inicio - 19/09/06 - Carlos --*/
	  if (EST_AVC(Cuba).ChaveLocRem eq LOCAL)
	    GeraEvento(SOPROU,Cuba,-1,ScoreGetStr(NOME_PAINEL),STR_TRACO,
				 VCicCont,VInst,VAlvo);
	  else
	    GeraEvento(SOPROU,Cuba,-1, "Automat",STR_TRACO,VCicCont,VInst,VAlvo);
	  EST_AVC(Cuba).FalhaSoproAut = FALSO;	/* reseta falha de sopro */
	  EST_AVC(Cuba).EsperaConfSopro = FALSO;	/* confirma retorno de acionamento */
	  /*-- Fim - 19/09/06 - Carlos --*/
	  *EnviaReconhece=VERDADEIRO;
	}
  }
}

/* -- Alteracao - Fim - 09/05/2002 - Leonel - Inclusao da sala 7 125ka -- */

/*
--------------------------------------------------------------------------------
| TrataChaveMCruzeiro - Trata chave de manobra de cruzeiro
--------------------------------------------------------------------------------
*/
void TrataChaveMCruzeiro(int Cuba,t_mascara_bits *Masc,int *EstAtual,int *AlterouTab, 
						     time_t	HoraAtual,float VCicCont,float VInst,float VAlvo)
{
  int tmp_bit_old, tmp_bit_new, bit_acao;

  if ((AVC.ParUser1[Cuba].HabMCruzeiro) and (AVC.Abs[Cuba].BitChaveMCruzeiro ne 255))
  { /* habilitado algoritmo de manobra de cruzeiro */
	tmp_bit_old=PegaEstadoIO(Cuba,AVC.Abs[Cuba].BitChaveMCruzeiro);
	tmp_bit_new=PegaBit(Masc, AVC.Abs[Cuba].BitChaveMCruzeiro);
	if (tmp_bit_old ne tmp_bit_new)
	{
	  if (tmp_bit_new eq ESTADO_MCRUZEIRO_ATIVO)
	  { /* -- *************** Chave Ativa ********************* -- */
		if (EST_AVC(Cuba).Est.ChaveMCruzeiro ne VERDADEIRO)
		{
		  EST_AVC(Cuba).Est.ChaveMCruzeiro=VERDADEIRO;
		  GeraEvento(EV_MANOBRA_CRUZEIRO, Cuba, -1, ScoreGetStr(NOME_PAINEL),
						  ScoreGetStr(SCORE_MSG_401), VCicCont,VInst,VAlvo);
		  EST_AVC(Cuba).TrataCruzeiro = VERDADEIRO;
		  AVC.Cleit[Cuba].HoraUltCruzeiro=HoraAtual;

		  *AlterouTab=TABELA_EST_AVC;
		}
	  }
	  else
	  { /* -- **************** Chave desligada **************** -- */
		if (EST_AVC(Cuba).Est.ChaveMCruzeiro ne FALSO)
		{
		  EST_AVC(Cuba).Est.ChaveMCruzeiro=FALSO;
		  GeraEvento(EV_MANOBRA_CRUZEIRO, Cuba, -1, ScoreGetStr(NOME_PAINEL),
						  ScoreGetStr(SCORE_MSG_402), VCicCont,VInst,VAlvo);
		  if (EST_AVC(Cuba).Est.LiberaMCruzeiro)
		  { /* Retira permissao de manobra caso ela exista */
			EST_AVC(Cuba).Est.LiberaMCruzeiro=FALSO;
			bit_acao=AVC.Abs[Cuba].BitLiberaMCruzeiro;
			if (bit_acao ne 255)
			  ComandaSaidaRem(Cuba,DESLIGAR,bit_acao,0);
			GeraEvento(EV_MANOBRA_CRUZEIRO, Cuba, -1, "Habilita",
						  ScoreGetStr(SCORE_MSG_402), VCicCont,VInst,VAlvo);
		  }
		  *AlterouTab=TABELA_EST_AVC;
		}
	  }
    }
	if ((EST_AVC(Cuba).Est.ChaveMCruzeiro eq VERDADEIRO) and (EST_AVC(Cuba).ChaveLocRem ne LOCAL))
	{ /* Ativa chave de cruzeiro em automatico com MM em auto -> passa para manual controle pois rele de tempo nao atua */
	  if (EST_AVC(Cuba).ManualControle eq FALSO)
	  {  /* Retira cuba do controle */
		/* -- passa cuba para manual -- */
		EST_AVC(Cuba).ChaveAutMan = MANUAL;
		/* -- Cuba colocada em manual pelo controle -- */
		EST_AVC(Cuba).ManualControle=VERDADEIRO;
		/*-- Hora da ultima selecao manual --*/
		AVC.Cleit[Cuba].HoraUltSelMan = HoraAtual;
		/*-- Gera evento de selecao de modo de operacao --*/
		GeraEvento( OPERACAO_MANUAL, Cuba, -1, "MCruz",
			STR_TRACO,VCicCont,VInst,VAlvo);
	  }
	}
  }
  else
  { /* Algoritmo nao habilitado */
	EST_AVC(Cuba).Est.ChaveMCruzeiro=FALSO;
  }
}

/* -- Fim do FuncRecChavesCBA.c -- */
