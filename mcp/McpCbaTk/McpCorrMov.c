/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: McpCorrMov.c

	CONTEUDO	: Modulo para tratamento de corrida ativado pelo Modulo de
				  Calculos Primarios - MCP.
                  Funcoes relacionadas `a movimentacao de anodo.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	24/02/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
21/12/94 | Edicao inicial de migracao para o QNX 4.2			| Leonel
-------------------------------------------------------------------------------
04/02/95 | Adaptacao para versao em ingles               		| Carlos
-------------------------------------------------------------------------------
27/07/98 | Inclusao da nova logica de ajuste de camisa   		| Carlos
-------------------------------------------------------------------------------
07/09/98 | Cba-Inclusao de logica de agarramento de anodo 		| Leonel
-------------------------------------------------------------------------------
28/06/99 | Incluido tratamento de booster de corrente			| Carlos
-------------------------------------------------------------------------------
$Id: McpCorrMov.c,v 1.1.2.1 2012/09/28 17:09:38 leo Exp $

$Log: McpCorrMov.c,v $
Revision 1.1.2.1  2012/09/28 17:09:38  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

Revision 1.2  2004/10/01 18:51:31  leo
Correcao comparacao de rerro para agarramento.

******************************************************************************/
/*
-------------------------------------------------------------------------------
                           Definicao de compilacao condicional
-------------------------------------------------------------------------------
*/
#define	GERA_EVMOVIMENTACAO

#define MAX_KBPWM	500e-9

/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include	<McpCorrida.h>
#include	<math.h>
#ifdef	ATIVA_DEPURACAO
  #include	<stdio.h>
#endif
 #include	<AjusteCamisa.h>

/*
-------------------------------------------------------------------------------
                           Variaveis Globais
-------------------------------------------------------------------------------
*/
/* -- Apontadores para as tabelas comuns -- */
#include	<VarsComum.h>

/*
--------------------------------------------------------------------------------
| VerificaFaixaControle - Verifica se a resistencia de erro da Cuba dada esta  |
|                         na faixa de controle. Retorna VERDADEIRO se sim e    |
|                         FALSO caso contrario.                                |
--------------------------------------------------------------------------------
*/
int VerificaFaixaControle(int Cuba,float Rerro)
{
  float	Erro;
  float	VAlvo,VCicCont;
  int	Controle,DesvioTensao;

  /* Verifica provavel agarramento de anodo */
  if (AVC.Param[Cuba].MaxAgarraAnodo ne 0)
  {
	if ((EST_AVC(Cuba).ChaveAutMan eq AUTOMATICO) and
		(EST_AVC(Cuba).ChaveLocRem eq REMOTO) and
		/* verifica se iguais com 0.1uohms de histerese */
		(fabs(AVC.Ccont[Cuba].RErroUltMove - Rerro) <= AVC.ParUser1[Cuba].DifResAgarra) and
		/* verifica se iguais com 0.01uohms de histerese */
		(fabs(AVC.Ccont[Cuba].RAlvoUltMove - AVC.Ccont[Cuba].RAlvo) <= 0.01e-6) and
		/* verifica ultima movimentacao <= um ciclo de corrida */
		((HoraAtualSec-AVC.Ccont[Cuba].HoraUltMove) <= 
		(AVL.CicloAjCorrida/(SAD_TICKS / Comum->BaseTempoMcp))))
	{ /* A ultima movimentacao nao surtiu efeito. Provavel agarramento de anodo */
	  AVC.Ccont[Cuba].ContAgarraAnodo++;	/* Contador de provavel agarramento de anodo */
	  if (AVC.Ccont[Cuba].ContAgarraAnodo >= AVC.Param[Cuba].MaxAgarraAnodo)
	  {  /* Provavel agarramento de anodo. Passa cuba para manual */
		EST_AVC(Cuba).ProvAgarraAnodo=VERDADEIRO;

		/* -- Passa cuba para manual -- */
		EST_AVC(Cuba).ChaveAutMan = MANUAL;
		/* -- Cuba colocada em manual pelo controle -- */
		EST_AVC(Cuba).ManualControle=VERDADEIRO;

		/*-- Hora da ultima selecao manual --*/
		AVC.Cleit[Cuba].HoraUltSelMan = HoraAtualSec;
		/*-- Gera evento de selecao de modo de operacao --*/
		VAlvo=AVC.Ccont[Cuba].VAlvo;

		/* Inicio Alteracao - Carlos - 23/06/99 */
		/* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
		VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba+
		   AVC.Param[Cuba].Bemf;
#else
		VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal+
		   AVC.Param[Cuba].Bemf;
#endif
		/* Fim Alteracao - Carlos - 23/06/99 */

		GeraEvento( OPERACAO_MANUAL, Cuba, -1, ScoreGetStr(SCORE_MSG_258),
				"AGARRA",VCicCont,AVC.Cleit[Cuba].Vinst,VAlvo);
	  }
	}
  }
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
	if ((Erro >= AVC.Ccont[Cuba].BandaMortaSupAtual) and
		(Erro < AVC.Ccont[Cuba].BandaContSupAtual))
	  /* -- banda de controle superior -- */
	  Controle=VERDADEIRO;
	else
	  if (Erro >= AVC.Ccont[Cuba].BandaContSupAtual)
	  	/* -- banda proibida superior -- */
		DesvioTensao=VERDADEIRO;
  }
  
  if (EST_AVC(Cuba).Ea eq FALSO)
  {
	VAlvo=AVC.Ccont[Cuba].VAlvo;

	/* Inicio Alteracao - Carlos - 23/06/99 */
	/* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
	VCicCont=AVC.Cleit[Cuba].RCicCorr*AVC.Ccont[Cuba].INominalCuba+AVC.Param[Cuba].Bemf;
#else
	VCicCont=AVC.Cleit[Cuba].RCicCorr*AVL.INominal+AVC.Param[Cuba].Bemf;
#endif
	/* Fim Alteracao - Carlos - 23/06/99 */

	if (DesvioTensao eq VERDADEIRO)
	{
	  if (EST_AVC(Cuba).DesvioTensao eq FALSO)
	  { /* -- inicio de desvio de tensao -- */
		AVC.Ccont[Cuba].HoraUltVDesv=HoraAtualSec;
		GeraEvento(INI_DESVIO_TENSAO,Cuba,-1,ScoreGetStr(CORRIDA),STR_TRACO,
			VCicCont,STR_TRACO,VAlvo);
		EST_AVC(Cuba).DesvioTensao=VERDADEIRO;
	  }
	}
	else
	  if (EST_AVC(Cuba).DesvioTensao eq VERDADEIRO)
	  { /* -- fim de desvio de tensao -- */
		GeraEvento(FIM_DESVIO_TENSAO,Cuba,-1,ScoreGetStr(CORRIDA),STR_TRACO,
			VCicCont,STR_TRACO,VAlvo);
		EST_AVC(Cuba).DesvioTensao=FALSO;
	  }
  }

  /* -- retorna se esta na faixa de controle -- */
  return(Controle);
}

/*
--------------------------------------------------------------------------------
| EfetuaMov - Calcula duracao e sentido do movimento e movimenta o anodo.      |
--------------------------------------------------------------------------------
*/
void EfetuaMov(int Cuba,float RErro)
{
#ifdef	GERA_EVMOVIMENTACAO
  float	VAlvo,VCicCont,VInst;
#endif
  float	DuracaoMov;
  int	DurInt;
  int	SentidoMov;
  char		StrTempo[9];

  DuracaoMov=CalcEquivMotor(Cuba,RErro,&SentidoMov);
  
  if(AVL.Par.KpcCorr > 0)
  	DuracaoMov = DuracaoMov*AVL.Par.KpcCorr;

  VerifCondCamisa(Cuba, HoraAtualSec);

  if (AVC.ParUser1[Cuba].HabCamSimul eq FALSO)
	CalcMovCamisa(Cuba, DuracaoMov, HoraAtualSec);

  if (DuracaoMov >= 0.1)
  {
	/* -- comanda a movimentacao do anodo -- */
	DurInt=(int)(DuracaoMov*BASE_TEMPO_REMOTA);

    if (AVC.ParUser1[Cuba].HabCamSimul eq VERDADEIRO and SentidoMov eq DESCER_ANODO and
		EST_AVC(Cuba).Est.AbortaAjuste eq AJUSTE_NORMAL and
		AVC.User1[Cuba].ContInibAjCam <= 0 and
		EST_AVC(Cuba).Est.CamisaAlta eq FALSO)
    {
      if (ComandaSaidaRem2W(Cuba,LIGAR,AVC.Abs[Cuba].BitDesceAnodo,AVC.Abs[Cuba].BitSobeCamisaouM1,DurInt) ne 0)
	  
	    	EmiteAlarmeFor(TODOS_DISPOSITIVOS,"Falha subida camisa, Cuba %d",
			  ConvCubScoreOper(Cuba));
		  	
 	}
	else
	  MoveAnodo(Cuba,DurInt,SentidoMov);


#ifdef	GERA_EVMOVIMENTACAO
	VAlvo=AVC.Ccont[Cuba].VAlvo;
	VInst=AVC.Cleit[Cuba].Vinst;

	/* Inicio Alteracao - Carlos - 23/06/99 */
	/* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
	VCicCont=AVC.Cleit[Cuba].RCicCorr*AVC.Ccont[Cuba].INominalCuba+
			 AVC.Param[Cuba].Bemf;
#else
	VCicCont=AVC.Cleit[Cuba].RCicCorr*AVL.INominal+
			 AVC.Param[Cuba].Bemf;
#endif
	/* Fim Alteracao - Carlos - 23/06/99 */

		  if (Comum->IdentReducao eq 5)
		  {
			if (AVC.User1[Cuba].ContMovCorr > 0)
			{
			  /* -- Gera evento de movimentacao automatica do anodo -- */
			  if (SentidoMov eq DESCER_ANODO)
	  			GeraEvento(DESC_AUT_CORR,Cuba,-1,"Interm. ",
				(float)DurInt/(float)BASE_TEMPO_REMOTA,VCicCont,VInst,VAlvo);
			  else
	  			GeraEvento(SUB_AUT_CORR,Cuba,-1,"Interm. ",
				(float)DurInt/(float)BASE_TEMPO_REMOTA,VCicCont,VInst,VAlvo);
			}
			else
			if (AVC.User1[Cuba].ContMovCorr eq -1)
			{
			  /* -- Gera evento de movimentacao automatica do anodo -- */
			  if (SentidoMov eq DESCER_ANODO)
	  			GeraEvento(DESC_AUT_CORR,Cuba,-1,ScoreGetStr(CORRIDA),
				(float)DurInt/(float)BASE_TEMPO_REMOTA,VCicCont,VInst,VAlvo);
			  else
	  			GeraEvento(SUB_AUT_CORR,Cuba,-1,ScoreGetStr(CORRIDA),
				(float)DurInt/(float)BASE_TEMPO_REMOTA,VCicCont,VInst,VAlvo);
			}
		  }
		  else
		  {
			/* -- Gera evento de movimentacao automatica do anodo -- */
			if (SentidoMov eq DESCER_ANODO)
		 	{
	  		  GeraEvento(DESC_AUT_CORR,Cuba,-1,ScoreGetStr(CORRIDA),
			  (float)DurInt/(float)BASE_TEMPO_REMOTA,VCicCont,VInst,VAlvo);
	
			  if (AVC.ParUser1[Cuba].HabCamSimul eq VERDADEIRO and
				EST_AVC(Cuba).Est.AbortaAjuste eq AJUSTE_NORMAL and
				AVC.User1[Cuba].ContInibAjCam <= 0 and
				EST_AVC(Cuba).Est.CamisaAlta eq FALSO)
			  {
	  		    sprintf(StrTempo,"%5.2f", (float)DurInt/(float)BASE_TEMPO_REMOTA);

			    GeraEvento(SUBIDA_AUT_CAMISA,Cuba,-1, StrTempo, VCicCont,VInst,VAlvo);
				  EST_AVC(Cuba).Est.AjusteCamisa = FALSO;
			  }
			}
			else
	  		  GeraEvento(SUB_AUT_CORR,Cuba,-1,ScoreGetStr(CORRIDA),
			  (float)DurInt/(float)BASE_TEMPO_REMOTA,VCicCont,VInst,VAlvo);
		  }
#endif
	EST_AVC(Cuba).EfeitoMove=VERDADEIRO;
	EST_AVC(Cuba).EsperaConfMove=FALSO;
	AVC.Ccont[Cuba].HoraUltMove=HoraAtualSec;
	AVC.Ccont[Cuba].SentidoUltMove=SentidoMov;
	AVC.Ccont[Cuba].DuracaoUltMove=DuracaoMov;
	AVC.Ccont[Cuba].RAlvoUltMove=AVC.Ccont[Cuba].RAlvo;
	AVC.Ccont[Cuba].RErroUltMove=RErro;
    AvcLoc[Cuba].CalcEqMotorCorr = VERDADEIRO;
    AvcLoc[Cuba].DurUltMovCorr = DuracaoMov;
    AvcLoc[Cuba].ResUltMovCorr = AVC.Cleit[Cuba].RCicCorr;

  }
}

/*
--------------------------------------------------------------------------------
| CalcEquivMotor - Calcula o equivalente motor em segundos e o sentido de      |
|                  acionamento para o erro correspondente a Cuba dada.         |
|                  Retorna a duracao do movimento em segundos e o sentido de   |
|                  movimentacao (DESCER ou SUBIR)                              |
--------------------------------------------------------------------------------
*/
float CalcEquivMotor(int Cuba, float Rerro, int *SentidoMov)
{
  float	DuracaoMov;
  float AbsErro;
  float LimDurMovMin;
  float LimDurMovMax;

  AbsErro = fabs((double)Rerro);
  if (Rerro < 0.0)
  {
	*SentidoMov=DESCER_ANODO;

	LimDurMovMin = (float)AVL.DurMovBMin;
	LimDurMovMax = (float)AVL.DurMovBMax;

	/* Calcula equivalente motor para corrida baixo */
	if (AvcLoc[Cuba].CalcEqMotorCorr eq VERDADEIRO and
		AVC.ParUser1[Cuba].HabKbpCorrida eq VERDADEIRO)
	{
      AVC.User1[Cuba].EqMotorCorrB = (AVC.User1[Cuba].EqMotorCorrB + 
				(fabs(AvcLoc[Cuba].ResUltMovCorr - AVC.Cleit[Cuba].RCicCorr) / 
				AvcLoc[Cuba].DurUltMovCorr)) / 2;
	  
	  if (AVC.User1[Cuba].EqMotorCorrB < AVC.Param[Cuba].MinKbpwm)
		AVC.User1[Cuba].EqMotorCorrB = AVC.Param[Cuba].MinKbpwm;

	  if (AVC.User1[Cuba].EqMotorCorrB > MAX_KBPWM)
		AVC.User1[Cuba].EqMotorCorrB = MAX_KBPWM;

	  
	  AvcLoc[Cuba].CalcEqMotorCorr = FALSO;
	}

	/* calculo do tempo de movimentacao */
	if(AVC.ParUser1[Cuba].HabKbpCorrida eq VERDADEIRO)
	  DuracaoMov=AVC.Param[Cuba].KPb*(AbsErro/AVC.User1[Cuba].EqMotorCorrB);
	else
	  DuracaoMov=AVC.Param[Cuba].KPb*(AbsErro/AVC.Ccont[Cuba].Kbpwm);		

	if (DuracaoMov < LimDurMovMin)
	  DuracaoMov=0.0;
	else
	  if (DuracaoMov > LimDurMovMax)
		DuracaoMov=LimDurMovMax;
  }
  else
  {
	*SentidoMov=SUBIR_ANODO;
	/* calculo do tempo de movimentacao */

	LimDurMovMin = (float)AVL.DurMovCMin;
	LimDurMovMax = (float)AVL.DurMovCMax;

	DuracaoMov=AVC.Param[Cuba].KPc*(AbsErro/AVC.Ccont[Cuba].Kcpwm);
	if (DuracaoMov < LimDurMovMin)
	  DuracaoMov=0.0;
	else
	  if (DuracaoMov > LimDurMovMax)
		DuracaoMov=LimDurMovMax;
  }
  return(DuracaoMov);
}


int ComandaSaidaRem2W(int Cuba,int Acao,int BitAcao1, int BitAcao2,int Tempo)
{
  int				Canal,Remota,Ret;

  /* -- Canal da placa de comunicacao onde a Remota esta conectada -- */
  Canal=AVC.Abs[Cuba].CanalRemota;
  /* -- Numero do nodo da Remota na rede -- */
  Remota=AVC.Abs[Cuba].NodoRemota;
  Ret=CmdSaidaRem2W(Canal,Remota,Acao,BitAcao1,BitAcao2,Tempo);
  if (Ret ne STATUS_OK)
	EmiteAlarmeFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_ERR_5),
			ConvCubScoreOper(Cuba),COD_ERRO_30,Ret);
  return(Ret);
}


int CmdSaidaRem2W(int Canal, int Remota,int Acao,int BitAcao1,int BitAcao2,int Tempo)
{
  int				Ret;
  unsigned int		Masc, MascAux;
  t_esc_saida_dig	TmpLig[2];
  t_liga_saida_temp	TmpLigT[2];
  t_desl_saida_temp	TmpDeslT[2];

  BitAcao1--;	/* -- As saidas comecao de 1! -- */
  BitAcao2--;
  Masc=(1 shl (BitAcao1 Mod TAM_GRUPO_REM));
  MascAux=(1 shl (BitAcao2 Mod TAM_GRUPO_REM));
  
  if (Tempo ne 0)
  {
	if (Acao eq LIGAR)
	{ /* -- Liga saida temporizada -- */
	  /* -- Prepara parametros -- */
	  TmpLigT[0].Rack=0;
	  TmpLigT[0].MascaraLiga.Mascara1=0xFFFF;
	  TmpLigT[0].MascaraLiga.Mascara2=0xFFFF;
	  
	  if (BitAcao1 < TAM_GRUPO_REM and BitAcao2 < TAM_GRUPO_REM)
	  {
		Masc = Masc orb MascAux;
		Masc = notb Masc;
		TmpLigT[0].MascaraLiga.Mascara1=Masc;
	  }
	  else if (BitAcao1 >= TAM_GRUPO_REM and BitAcao2 >= TAM_GRUPO_REM)
	  {
		Masc = Masc orb MascAux;
		Masc = notb Masc;
		TmpLigT[0].MascaraLiga.Mascara2=Masc;
	  }
	  else if (BitAcao1 < TAM_GRUPO_REM and BitAcao2 >= TAM_GRUPO_REM)
	  {
		Masc = notb Masc;
		TmpLigT[0].MascaraLiga.Mascara1=Masc;
		MascAux = notb MascAux;
		TmpLigT[0].MascaraLiga.Mascara2=MascAux;
	  }
	  else if (BitAcao1>= TAM_GRUPO_REM and BitAcao2 < TAM_GRUPO_REM)
	  {
		Masc = notb Masc;
		TmpLigT[0].MascaraLiga.Mascara2=Masc;
		MascAux = notb MascAux;
		TmpLigT[0].MascaraLiga.Mascara1=MascAux;
	  }
	  TmpLigT[0].Tempo=Tempo;	/* -- tempo esta em ticks da remota -- */
	  TmpLigT[1].Rack=0xFF;
	  /* -- Envia Comando ao modulo de tratamento de comunicacao -- */
	  Ret=LigSaiTmp(Canal,Remota,0,TmpLigT);
	}
	else
	{ /* -- Desliga saida temporizada -- */
	  /* -- Prepara parametros -- */
	  TmpDeslT[0].Rack=0;
	  TmpDeslT[0].MascaraDesliga.Mascara1=0;
	  TmpDeslT[0].MascaraDesliga.Mascara2=0;
	  if (BitAcao1 < TAM_GRUPO_REM and BitAcao2 < TAM_GRUPO_REM)
	  {
		Masc = Masc andb MascAux;
		TmpDeslT[0].MascaraDesliga.Mascara1=Masc;
	  }
	  else if (BitAcao1 >= TAM_GRUPO_REM and BitAcao2 >= TAM_GRUPO_REM)
	  {
		Masc = Masc andb MascAux;
		TmpDeslT[0].MascaraDesliga.Mascara2=Masc;
	  }
	  else if (BitAcao1 < TAM_GRUPO_REM and BitAcao2 >= TAM_GRUPO_REM)
	  {
		TmpDeslT[0].MascaraDesliga.Mascara1=Masc;
		TmpDeslT[0].MascaraDesliga.Mascara2=MascAux;
	  }
	  else if (BitAcao1>= TAM_GRUPO_REM and BitAcao2 < TAM_GRUPO_REM)
	  {
		TmpDeslT[0].MascaraDesliga.Mascara2=Masc;
		TmpDeslT[0].MascaraDesliga.Mascara1=MascAux;
	  }
	  TmpDeslT[0].Tempo=Tempo;	/* -- tempo esta em ticks da remota -- */
	  TmpDeslT[1].Rack=0xFF;
	  /* -- Envia Comando ao modulo de tratamento de comunicacao -- */
	  Ret=DesSaiTmp(Canal,Remota,0,TmpDeslT);
	}
  }
  else
  { /* -- ligar ou apagar lampada -- */
	TmpLig[0].Rack=0;
	TmpLig[0].MascaraLiga.Mascara1=0xFFFF;
	TmpLig[0].MascaraLiga.Mascara2=0xFFFF;
	TmpLig[0].MascaraDesliga.Mascara1=0;
	TmpLig[0].MascaraDesliga.Mascara2=0;
	TmpLig[1].Rack=0xFF;
	if (Acao eq LIGAR)
	{
	  if (BitAcao1 < TAM_GRUPO_REM and BitAcao2 < TAM_GRUPO_REM)
	  {
		Masc = Masc andb MascAux;
		Masc = notb Masc;
		TmpLig[0].MascaraLiga.Mascara1=Masc;
	  }
	  else if (BitAcao1 >= TAM_GRUPO_REM and BitAcao2 >= TAM_GRUPO_REM)
	  {
		Masc = Masc andb MascAux;
		Masc = notb Masc;
		TmpLig[0].MascaraLiga.Mascara2=Masc;
	  }
	  else if (BitAcao1 < TAM_GRUPO_REM and BitAcao2 >= TAM_GRUPO_REM)
	  {
		Masc = notb Masc;
		TmpLig[0].MascaraLiga.Mascara1=Masc;
		MascAux = notb MascAux;
		TmpLig[0].MascaraLiga.Mascara2=MascAux;
	  }
	  else if (BitAcao1>= TAM_GRUPO_REM and BitAcao2 < TAM_GRUPO_REM)
	  {
		Masc = notb Masc;
		TmpLig[0].MascaraLiga.Mascara2=Masc;
		MascAux = notb MascAux;
		TmpLig[0].MascaraLiga.Mascara1=MascAux;
	  }
	}
	else
	{
	  if (BitAcao1 < TAM_GRUPO_REM and BitAcao2 < TAM_GRUPO_REM)
	  {
		Masc = Masc andb MascAux;
		TmpLig[0].MascaraLiga.Mascara1=Masc;
	  }
	  else if (BitAcao1 >= TAM_GRUPO_REM and BitAcao2 >= TAM_GRUPO_REM)
	  {
		Masc = Masc andb MascAux;
		TmpLig[0].MascaraLiga.Mascara2=Masc;
	  }
	  else if (BitAcao1 < TAM_GRUPO_REM and BitAcao2 >= TAM_GRUPO_REM)
	  {
		TmpLig[0].MascaraLiga.Mascara1=Masc;
		TmpLig[0].MascaraLiga.Mascara2=MascAux;
	  }
	  else if (BitAcao1>= TAM_GRUPO_REM and BitAcao2 < TAM_GRUPO_REM)
	  {
		TmpLig[0].MascaraLiga.Mascara2=Masc;
		TmpLig[0].MascaraLiga.Mascara1=MascAux;
	  }
	}
	/* -- Envia Comando ao modulo de tratamento de comunicacao -- */
	Ret=EscSaiDig(Canal,Remota,0,TmpLig);
  }
  return(Ret);
}

/* -- Fim McpCorrMov.c -- */
