/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: TrataMovAn.c

	CONTEUDO	: Modulo de Controle das Cubas - MCC - Procedimentos para veri-
                  ficar a necessidade de movimentacao de anodo e para solicitar
                  a movimentacao se preciso.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	23/09/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
04/12/92 | Alteracao da duracao de movimentacao de int p/ float | Leonel
-------------------------------------------------------------------------------
05/01/93 | Acrescentado tratamento para confirmacao de movimen- | Leonel
         | tacao de anodo.                                      |
-------------------------------------------------------------------------------
09/03/93 | Alteracao nas condicoes de movimentacao durante que- | Leonel
         | brada e durante acrescimo banda controle por corrida |
         | para nao esperarem por tempo efeito move.            |
-------------------------------------------------------------------------------
05/07/94 | Edicao inicial de migracao para o QNX 4.2			| Leonel
-------------------------------------------------------------------------------
16/12/94 | Substituicao da variavel VAlvo da base de dados pelo	| Carlos
         | seu calculo na geracao de eventos                    |
-------------------------------------------------------------------------------
21/08/95 | Acrescentada inibicao de movimentacao por derivada   | Leonel
         | da resistencia - Algoritmo novo de previsao          |
-------------------------------------------------------------------------------
20/11/95 | Acrescentada inibicao de movimentacao por algoritmo  | Leonel
         | de controle de usuario - InibeControleUsu.           |
-------------------------------------------------------------------------------
20/02/97 | Substituida EaHoraFimProv por EaHoraInicio na gera-  | Carlos
         | cao do evento AtrasoEa                               |
-------------------------------------------------------------------------------
21/02/97 | Substituida tabela Param por  Ccont  para variaveis  | Carlos
         | VSetPoint e Banda*Atual                              |
-------------------------------------------------------------------------------
11/09/97 | Retirado teste de InibeMovEaPrev para quebrada       | Carlos
-------------------------------------------------------------------------------
22/04/98 | Corrigida inibicao de movimentacao por movimentacao  | Leonel
         | anterior para nao agir durante quebrada e corrida.   |
-------------------------------------------------------------------------------
07/09/98 | Cba-Inclusao de logica de agarramento de anodo 		| Leonel
-------------------------------------------------------------------------------
28/06/99 | Incluido tratamento de booster de corrente			| Carlos
-------------------------------------------------------------------------------
18/04/01 | Incluido tratamento para nao mover anodo qdo tensao	| Leonel
         | ou corrente da cuba eh religada. Aguarda TAtivaLinha	|
         | CBA sala 86ka - atn8.                               	|
-------------------------------------------------------------------------------
12/11/12 | Alterado para limitar o numero de movimentacoes em   | Marco
		 | cada ciclo.											|
-------------------------------------------------------------------------------
$Id: TrataMovAn.c,v 1.1.2.1 2012/09/28 17:09:28 leo Exp $

$Log: TrataMovAn.c,v $
Revision 1.1.2.1  2012/09/28 17:09:28  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

Revision 1.5  2007/09/28 14:46:25  rogerio
Alteracao para incluir sala I com atn8

Revision 1.4  2005/12/12 13:24:29  leo
Retirados ifdefs nao mais usados. Liberada movimentacao para baixo quando
em previsao e ocorreu quebrada.

Revision 1.3  2005/03/18 14:56:59  leo
Compatibilizacao com alteracoes do branch producao Albras

Revision 1.2.2.1  2004/10/08 14:21:44  leo
Arquivos nao usados

Revision 1.2  2004/04/08 19:21:14  leo
Inclusao da sala 125 kA VI.

******************************************************************************/

/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include	<MccCba.h>
#include	<Eventos.h>
#include	<Prototipos.h>
#include	<Remotas.h>
#include	<math.h>

/*
-------------------------------------------------------------------------------
                           Definicoes
-------------------------------------------------------------------------------
*/

/*
-------------------------------------------------------------------------------
                           Variaveis Globais
-------------------------------------------------------------------------------
*/
/* -- Apontadores para as tabelas comuns -- */
#include	<VarsComum.h>

/*
-------------------------------------------------------------------------------
                           Prototipos
-------------------------------------------------------------------------------
*/
void	VerificaAtrasoEa(int Cuba);
int		VerificaFaixaControle(int Cuba,float Rerro);
void	EfetuaMov(int Cuba,float RErro);

/*
-------------------------------------------------------------------------------
							Funcoes
-------------------------------------------------------------------------------
*/

/*
--------------------------------------------------------------------------------
| IniTrataMoveAnodo - Inicializa variaveis referentes os procedimentos deste   |
|                     modulo                                                   |
--------------------------------------------------------------------------------
*/
void IniTrataMoveAnodo(int Cuba)
{
	PosicaoGlobal = 160;
	/* -- inicializa BandaMortaSupAtual -- */
	AVC.Ccont[Cuba].BandaMortaSupAtual=AVC.Param[Cuba].BandaMortaSup;
	EST_AVC(Cuba).DeuAcresBMSup=FALSO;
	EST_AVC(Cuba).DesvioTensao=FALSO;
	EST_AVC(Cuba).EsperaConfMove=FALSO;
	AVC.Ccont[Cuba].Rerro = 0.0;
}

/*
--------------------------------------------------------------------------------
| TrataMovAnodo - Para a cuba dada verifica condicoes p/ movimentar anodo,     |
|                 verifica se ha necessidade de movimentacao e movimenta se    |
|                 preciso.                                                     |
--------------------------------------------------------------------------------
*/
void TrataMovAnodo(int Cuba)
{
  int	FaixaControlavel;
  float	RErro;

PosicaoGlobal = 161;

  /* -- Verifica se a cuba esta com atraso para entrar em Ea -- */
  VerificaAtrasoEa(Cuba);
  /* -- calculo do erro -- */
  if (EST_AVC(Cuba).Ea eq VERDADEIRO)
    RErro=0.0;
  else
	RErro=AVC.Ccont[Cuba].RAlvo-AVC.CcontMcp[Cuba].RCicContlBruta;
  AVC.Ccont[Cuba].Rerro = RErro;
  /* -- Verifica se cuba esta na faixa controlavel -- */
  FaixaControlavel=VerificaFaixaControle(Cuba,RErro);

PosicaoGlobal = 162;


  /* -- Condicoes necessarias para habilitar movimentacao de anodo -- */
  if ((EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL) and
	  (EST_AVC(Cuba).ChaveAutMan eq AUTOMATICO) and
	  (EST_AVC(Cuba).ChaveLocRem eq REMOTO) and
	  (EST_AVC(Cuba).ForaLeitura eq FALSO) and
	  (EST_AVC(Cuba).Est.ReleTempoMM eq FALSO) and
	  (EST_AVC(Cuba).InibeControleUsu eq FALSO) and
	  ( (EST_AVC(Cuba).InibeControleAlim eq HABILITA_MOVE) or
		((EST_AVC(Cuba).InibeControleAlim eq DESAB_MOV_BAIXO) and (RErro > 0.0)) or
		((EST_AVC(Cuba).InibeControleAlim eq DESAB_MOV_CIMA) and (RErro < 0.0)) ) and
	  (AVL.LinhaHabilitada eq VERDADEIRO) and 
	  (	((AVC.ParUser1[Cuba].HabLimMov eq VERDADEIRO) and
		(NumMov[AVC.ParUser1[Cuba].GrupoMov] < AVC.ParUser1[Cuba].NumMovConsec)) or 
		(AVC.ParUser1[Cuba].HabLimMov eq FALSO) ) )
  {
	/* -- Alteracao - inicio - 18/04/2001 - Leonel - Atn8: Tratamento para nao mover anodo
	                  quando tensao ou corrente da cuba retorna. HoraInicDescLeit contem
					  a hora que a cuba retornou a leitura ou que a resistencia ficou
					  maior que 1 microOhm (tensao ou corrente desligadas). Aguarda tempo
					  de estabilizacao do filtro dado por AVL.TAtivaLinha para mover anodo -- */
	/* -- Alteracao - inicio - 16/12/2002 - Leonel - Inclusao da sala 125ka -- */
	/*-- CL01 - Upgrade Red II para ATN8 --*/
	if ((Comum->IdentReducao >= 6) or (Comum->IdentReducao  <= 2))
	/* -- Alteracao - inicio - 16/12/2002 - Leonel - Inclusao da sala 125ka -- */
	{ /* sala 86ka, 125ka 5 e 6 - atn8 */
	  if ( (HoraAtualCtrl-AVC.Cleit[Cuba].HoraInicDesLeit) < (AVL.TAtivaLinha*60) )
		FaixaControlavel=FALSO; /* inibe movimentacao */
	}
	/* -- Alteracao - fim - 18/04/2001 - Leonel - Tratamento para nao mover anodo -- */
	/* -- Verifica condicoes operacionais para movimentar anodo -- */
	if (FaixaControlavel eq VERDADEIRO)
	{
	  if ((EST_AVC(Cuba).EfeitoEa eq FALSO) and
 		  (EST_AVC(Cuba).EfeitoCorr eq FALSO) )
	  {
PosicaoGlobal = 163;

		/* Alterado para permitir movimentacao em Previsao logo apos quebrada */
		if ( ((HoraAtualCtrl-AVC.Cleit[Cuba].HoraUltCorr) <
				AVC.Param[Cuba].TAcresBCSCorr))
		{
		  /* -- Acrescentado para o novo algoritmo de Previsao -- */
 		  if (EST_AVC(Cuba).InibeMovEaPrev eq FALSO)
		  {
			/* Permite movimentacao para cima/baixo
			   durante corrida sem ajustar equivalente motor e sem esperar
			   tempo efeito move. PERMITE AJUSTE RAPIDO APOS CORRIDA */
			EfetuaMov(Cuba,RErro);
			/* -- nao faz ajuste do equivalente motor -- */
			AvcLocal[Cuba].AjustaEqMotor=FALSO;

		  }
		}
		else
		{
		  if (EST_AVC(Cuba).EfeitoQueb eq VERDADEIRO and
				AVC.ParUser1[Cuba].HabPrecMovQueb eq FALSO)
		  {
			if (RErro > 0)
			{
PosicaoGlobal = 164;

			  /* Permite movimentacao para cima durante quebrada sem ajustar
				 equivalente motor e sem esperar tempo efeito move.
				 PERMITE AJUSTE RAPIDO APOS QUEBRADA */
			  /* -- pode movimentar para cima durante quebrada -- */
			  EfetuaMov(Cuba,RErro);
		 	  /* -- nao faz ajuste do equivalente motor -- */
			  AvcLocal[Cuba].AjustaEqMotor=FALSO;
			}
		  }
		  else
		  {
			/* Alterado para permitir movimentacao em Previsao apos quebrada */
			/* -- Acrescentado para o novo algoritmo de Previsao -- */
			if ( (EST_AVC(Cuba).InibeMovEaPrev eq FALSO) )
			{
PosicaoGlobal = 165;

			  /* Testa se movimentou recentemente */
			  if (((RErro >= 0.0) and     /*-- Subida de anodo --*/
				   ((HoraAtualCtrl-AVC.Ccont[Cuba].HoraUltMove) > AVC.Param[Cuba].TEfeitoMoveCima)) or
				  ((RErro < 0.0)  and     /*-- Descida de anodo --*/
				   ((HoraAtualCtrl-AVC.Ccont[Cuba].HoraUltMove) > AVC.Param[Cuba].TEfeitoMoveBaixo)))
			  {
				EfetuaMov(Cuba,RErro);
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
| EfetuaMov - Calcula duracao e sentido do movimento e movimenta o anodo.      |
--------------------------------------------------------------------------------
*/
void EfetuaMov(int Cuba,float RErro)
{
  float	DuracaoMov,VAlvo,VCicCont,VInst;
  int	DurInt;
  int	SentidoMov;

  DuracaoMov=CalcEquivMotor(Cuba,RErro,&SentidoMov);
  if (DuracaoMov >= 0.1)
  {
PosicaoGlobal = 166;

    /* -- comanda a movimentacao do anodo -- */
    DurInt=(int)(DuracaoMov*BASE_TEMPO_REMOTA);
    if (MoveAnodo(Cuba,DurInt,SentidoMov) eq STATUS_OK)
    {
      VInst=AVC.Cleit[Cuba].Vinst;
	  /* Inicio Alteracao - Carlos - 23/06/99 */
	  /* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
      VAlvo=AVC.Ccont[Cuba].RAlvo * AVC.Ccont[Cuba].INominalCuba + AVC.Param[Cuba].Bemf;
      VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba+
  			 AVC.Param[Cuba].Bemf;
#else
      VAlvo=AVC.Ccont[Cuba].RAlvo * AVL.INominal + AVC.Param[Cuba].Bemf;
      VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal+
  			 AVC.Param[Cuba].Bemf;
#endif
	  /* Fim Alteracao - Carlos - 23/06/99 */

PosicaoGlobal = 167;

      /* -- Gera evento de movimentacao automatica do anodo -- */
      if (SentidoMov eq DESCER_ANODO)
	    GeraEvento(DESCIDA_AUT_ANODO,Cuba,-1,STR_TRACO,
			(float)DurInt/(float)BASE_TEMPO_REMOTA,VCicCont,VInst,VAlvo);
	  else
		GeraEvento(SUBIDA_AUT_ANODO,Cuba,-1,STR_TRACO,
			(float)DurInt/(float)BASE_TEMPO_REMOTA,VCicCont,VInst,VAlvo);
	  EST_AVC(Cuba).EfeitoMove=VERDADEIRO;
	  EST_AVC(Cuba).EsperaConfMove=VERDADEIRO;
	  AvcLocal[Cuba].MoveuAnodo = VERDADEIRO;
	  AvcLocal[Cuba].RCicContlAnt = AVC.CcontMcp[Cuba].RCicContlBruta;
	  AVC.Ccont[Cuba].HoraUltMove=HoraAtualCtrl;
	  AVC.Ccont[Cuba].SentidoUltMove=SentidoMov;
	  AVC.Ccont[Cuba].DuracaoUltMove=DuracaoMov;
	  AVC.Ccont[Cuba].RAlvoUltMove=AVC.Ccont[Cuba].RAlvo;
	  AVC.Ccont[Cuba].RErroUltMove=RErro;
	  NumMov[AVC.ParUser1[Cuba].GrupoMov]++;
	  EST_AVC(Cuba).Est.ProjetaCA = VERDADEIRO;
	  EST_AVC(Cuba).Est.ZeraCA = VERDADEIRO;
	}
	else
	  AvcLocal[Cuba].AjustaEqMotor=FALSO;
  }
  else
    AvcLocal[Cuba].AjustaEqMotor=FALSO;
}

/*
--------------------------------------------------------------------------------
| VerificaAtrasoEa - Verifica se a cuba dada esta com demora em entrar em      |
|                    efeito anodico e altera a banda morta superior se sim.    |
--------------------------------------------------------------------------------
*/
void VerificaAtrasoEa(int Cuba)
{
  if (EST_AVC(Cuba).EfeitoEa eq FALSO)
  {
	if ((HoraAtualCtrl-AVC.Ea[Cuba].EaHoraInicio) > (AVC.Param[Cuba].EaAtrasoMax*60l))
	{
	  if (EST_AVC(Cuba).DeuAcresBMSup eq FALSO)
	  {
PosicaoGlobal = 168;

		EST_AVC(Cuba).DeuAcresBMSup=VERDADEIRO;
		GeraEvento(ATRASO_EA,Cuba,-1);
	  }
	  AVC.Ccont[Cuba].BandaMortaSupAtual=AVC.Param[Cuba].BandaMortaSup +
								 AVC.Param[Cuba].AcrescBMortaSup;
	}
	else
	{
	  /* -- inicializa BandaMortaSupAtual -- */
	  AVC.Ccont[Cuba].BandaMortaSupAtual=AVC.Param[Cuba].BandaMortaSup;
	  EST_AVC(Cuba).DeuAcresBMSup=FALSO;
	}
  }
  else
  {
	/* -- inicializa BandaMortaSupAtual -- */
	AVC.Ccont[Cuba].BandaMortaSupAtual=AVC.Param[Cuba].BandaMortaSup;
	EST_AVC(Cuba).DeuAcresBMSup=FALSO;
  }
}

/*
--------------------------------------------------------------------------------
| VerificaFaixaControle - Verifica if a resistencia de erro da Cuba dada esta  |
|                         na faixa de controle. Retorna VERDADEIRO if sim e    |
|                         FALSO caso contrario.                                |
--------------------------------------------------------------------------------
*/
int VerificaFaixaControle(int Cuba,float Rerro)
{
  float	Erro;
  float	VAlvo,VCicCont;
  int	Controle,DesvioTensao;

PosicaoGlobal = 169;

  Erro = (float)fabs((double)Rerro);
  Controle=FALSO;
  DesvioTensao=FALSO;
  if (Rerro >= 0.0)
  { /* -- banda inferior -- */
	if ((Erro >= AVC.Param[Cuba].BandaMortaInf) and
		(Erro < AVC.Ccont[Cuba].BandaContInfAtual))
	  /* -- banda de controle inferior -- */
	  Controle=VERDADEIRO;
	else
	  if (Erro >= AVC.Ccont[Cuba].BandaContInfAtual)
	  	/* -- banda proibida inferior -- */
		DesvioTensao=VERDADEIRO;
  }
  else /* -- banda superior -- */
  {
PosicaoGlobal = 170;

	if ((Erro >= (AVC.Ccont[Cuba].BandaMortaSupAtual + 
			AVC.User1[Cuba].BandaSupMovel)) and
		(Erro < (AVC.Ccont[Cuba].BandaContSupAtual +
				AVC.User1[Cuba].BandaSupMovel)))
	  /* -- banda de controle superior -- */
	  Controle=VERDADEIRO;
	else
	  if (Erro >= (AVC.Ccont[Cuba].BandaContSupAtual + 
					AVC.User1[Cuba].BandaSupMovel))
	  	/* -- banda proibida superior -- */
		DesvioTensao=VERDADEIRO;
  }
  
  if (EST_AVC(Cuba).EfeitoEa eq FALSO)
  {
PosicaoGlobal = 171;

	/* Inicio Alteracao - Carlos - 23/06/99 */
	/* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
	VAlvo=AVC.Ccont[Cuba].RAlvo * AVC.Ccont[Cuba].INominalCuba + AVC.Param[Cuba].Bemf;
	VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba+
			 AVC.Param[Cuba].Bemf;
#else
	VAlvo=AVC.Ccont[Cuba].RAlvo * AVL.INominal + AVC.Param[Cuba].Bemf;
	VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal+
			 AVC.Param[Cuba].Bemf;
#endif
	/* Fim Alteracao - Carlos - 23/06/99 */
	if (DesvioTensao eq VERDADEIRO)
	{
	  if (EST_AVC(Cuba).DesvioTensao eq FALSO)
	  { /* -- inicio de desvio de tensao -- */
PosicaoGlobal = 172;

		AVC.Ccont[Cuba].HoraUltVDesv=HoraAtualCtrl;
		if (EST_AVC(Cuba).EaPrev eq VERDADEIRO)
		  GeraEvento(INI_DES_TENSAO_PR_EA,Cuba,-1,STR_TRACO,STR_TRACO,
			VCicCont,STR_TRACO,VAlvo);
		else
		  GeraEvento(INI_DESVIO_TENSAO,Cuba,-1,STR_TRACO,STR_TRACO,
			VCicCont,STR_TRACO,VAlvo);
		EST_AVC(Cuba).DesvioTensao=VERDADEIRO;
	  }
	}
	else
	  if (EST_AVC(Cuba).DesvioTensao eq VERDADEIRO)
	  { /* -- fim de desvio de tensao -- */
PosicaoGlobal = 173;

		if (EST_AVC(Cuba).EaPrev eq VERDADEIRO)
		  GeraEvento(FIM_DES_TENSAO_PR_EA,Cuba,-1,STR_TRACO,STR_TRACO,
			VCicCont,STR_TRACO,VAlvo);
		else
		  GeraEvento(FIM_DESVIO_TENSAO,Cuba,-1,STR_TRACO,STR_TRACO,
			VCicCont,STR_TRACO,VAlvo);
		EST_AVC(Cuba).DesvioTensao=FALSO;
	  }
  }

  /* -- retorna se esta na faixa de controle -- */
  return(Controle);
}

/* -- fim do arquivo TrataMovAn.c -- */
