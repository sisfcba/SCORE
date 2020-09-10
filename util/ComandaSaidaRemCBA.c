/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO  : CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA  : AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO  : ComSaiRem.c

	CONTEUDO : Funcao que comanda qualquer saida da remota associada a cuba
			   dada.

	AUTOR    : Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO   : 2.0		  -	  DATA  : 20/05/94

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------

-------------------------------------------------------------------------------
******************************************************************************/
/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include	<Score.h>
#include	<ScoreMsgs.h>
#include	<ScoreErros.h>
#include	<UsuRemota.h>
#include	<RemotaAtn7.h>
#include	<Eventos.h>
#include	<Prototipos.h>
#include	<stdio.h>

/*
-------------------------------------------------------------------------------
                           Variaveis Globais
-------------------------------------------------------------------------------
*/
/* -- Apontadores para as tabelas comuns -- */
#include	<VarsComum.h>

/*
--------------------------------------------------------------------------------
| NOME        :  ComandaSaidaRem                                               |
| OBJETIVO    :  Comanda um bit de saida da remota associada a cuba dada.      |
| CHAMADA     :  ComandaSaidaRem(Cuba,Acao,Tempo);                             |
| PARAMETROS  :  Cuba - Numero da cuba                                         |
|                Acao - LIGAR, DESLIGAR                                        |
|                BitAcao - Bit a comandar (comecando de 1)                     |
|                Tempo - Tempo em ticks da remota a manter a saida ligada ou   |
|                        desligada. Se 0 apenas liga ou desliga a saida.       |
| RETORNO     :  0 = ok. <> 0 => Erro de comunicacao                           |
| VERSAO      :  1.0 - 29/11/93            EDICAO: 01 - 29/11/93               |
| AUTOR       :  Leonel Vicente Mota Ivo                                       |
| OBSERVACOES :                                                                |
--------------------------------------------------------------------------------
*/
int ComandaSaidaRem2W(int Cuba,int Acao,int BitAcao1.int BitAcao2,int Tempo)
{
  int				Canal,Remota,Ret;

  /* -- Canal da placa de comunicacao onde a Remota esta conectada -- */
  Canal=AVC.Abs[Cuba].CanalRemota;
  /* -- Numero do nodo da Remota na rede -- */
  Remota=AVC.Abs[Cuba].NodoRemota;
  Ret=CmdSaidaRem(Canal,Remota,Acao,BitAcao1,BitAcao2,Tempo);
  if (Ret ne STATUS_OK)
	EmiteAlarmeFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_ERR_5),
			ConvCubScoreOper(Cuba),COD_ERRO_30,Ret);
  return(Ret);
}

/*
--------------------------------------------------------------------------------
| NOME        :  CmdSaidaRem                                                   |
| OBJETIVO    :  Comanda um bit de saida da remota indicada.                   |
| CHAMADA     :  CmdSaidaRem(Canal,Remota,Acao,Tempo);                         |
| PARAMETROS  :  Canal - Canal da remota                                       |
|                Remota - Nodo da remota                                       |
|                Acao - LIGAR, DESLIGAR                                        |
|                BitAcao - Bit a comandar (comecando de 1)                     |
|                Tempo - Tempo em ticks da remota a manter a saida ligada ou   |
|                        desligada. Se 0 apenas liga ou desliga a saida.       |
| RETORNO     :  0 = ok. <> 0 => Erro de comunicacao                           |
| VERSAO      :  1.0 - 29/11/93            EDICAO: 01 - 29/11/93               |
| AUTOR       :  Leonel Vicente Mota Ivo                                       |
| OBSERVACOES :                                                                |
--------------------------------------------------------------------------------
*/
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
		Masc = Masc andb MascAux;
		Masc = notb Masc;
		TmpLigT[0].MascaraLiga.Mascara1=Masc;
	  }
	  else if (BitAcao1 >= TAM_GRUPO_REM and BitAcao2 >= TAM_GRUPO_REM)
	  {
		Masc = Masc andb MascAux;
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
		TmpDeslT[0].MascaraLiga.Mascara1=Masc;
	  }
	  else if (BitAcao1 >= TAM_GRUPO_REM and BitAcao2 >= TAM_GRUPO_REM)
	  {
		Masc = Masc andb MascAux;
		TmpDeslT[0].MascaraLiga.Mascara2=Masc;
	  }
	  else if (BitAcao1 < TAM_GRUPO_REM and BitAcao2 >= TAM_GRUPO_REM)
	  {
		TmpDeslT[0].MascaraLiga.Mascara1=Masc;
		TmpDeslT[0].MascaraLiga.Mascara2=MascAux;
	  }
	  else if (BitAcao1>= TAM_GRUPO_REM and BitAcao2 < TAM_GRUPO_REM)
	  {
		TmpDeslT[0].MascaraLiga.Mascara2=Masc;
		TmpDeslT[0].MascaraLiga.Mascara1=MascAux;
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
