/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.3

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: CamisaLib.c

	CONTEUDO	: Biblioteca de funcoes para tratamento de ajuste de
				  camisa.

	AUTOR		: Carlos Cezar Silva Lage

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	17/07/98

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
Data     | Descricao                                                | Autor 
-------------------------------------------------------------------------------
19/10/98 | Inibido cancelamento do ajuste por troca de  pinos       | Carlos
-------------------------------------------------------------------------------
16/11/98 | Aborta ajuste se corrida ocorrer durante  TEfeitoQueb    | Carlos
-------------------------------------------------------------------------------
         | Aborta ajuste  por  quebrada, troca de pinos  ou  desvio |
16/11/98 | de tensao  somente  se  a cuba estiver nessa condicao na | Carlos
		 | sinalizacao de corrida 									|
-------------------------------------------------------------------------------
26/11/98 | Incluida desab. pelo operador e alarme camisa nao ajust. | Carlos
-------------------------------------------------------------------------------
11/12/98 | Aborta ajuste por Queb/Troca pinos durante corrida       | Carlos
         | Se camisa desab./desat operador nao gera alarme CamNAjust| 
-------------------------------------------------------------------------------
10/05/99 | Eliminado evento CamNAjust quando ajuste automatico esti-| Carlos
         | ver desat./inib., conforme fax de 19/03/99.              | 
-------------------------------------------------------------------------------
         | Inibido  cancelamento  do  ajuste por  troca de pinos  e |
12/05/99 | quebrada, conforme solicitacao do Robatao em 11/05/99 em | Carlos
		 | contato telefonico.    									|
-------------------------------------------------------------------------------
******************************************************************************/

/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/

#include <McpCorrida.h>
#include <AjusteCamisa.h>

/*
-------------------------------------------------------------------------------
                           Variaveis Globais
-------------------------------------------------------------------------------
*/

/*-- Apontadores para as tabelas comuns --*/
#include	<VarsComum.h>


/*
-------------------------------------------------------------------------------
									Funcoes
-------------------------------------------------------------------------------
*/

/*
--------------------------------------------------------------------------------
  IniAjCamCuba - Inicializa variaveis para o ajuste de camisa por cuba
--------------------------------------------------------------------------------
*/
void IniAjCamCuba(int Cuba)
{
  /*-- Variaveis de ciclo de controle --*/
  AVC.User1[Cuba].ContTAjAcum = 0.0;
  AVC.User1[Cuba].ContTAjCam = 0.0;

//  if ((EST_AVC(Cuba).Est.AjusteCamisa eq VERDADEIRO) and
//	  (EST_AVC(Cuba).Est.AbortaAjuste eq AJUSTE_NORMAL) and
//	  (AVL.LinhaHabilitada ne VERDADEIRO))
//	GeraEvento(CAMISA_NAO_AJUSTADA,Cuba,-1,"Linha", "Desab");

  /*-- Variaveis de estado --*/
  EST_AVC(Cuba).Est.AjusteCamisa = FALSO;
  EST_AVC(Cuba).Est.AbortaAjuste = AJUSTE_NORMAL;
  EST_AVC(Cuba).Est.CamNAjust = FALSO;
}

/*
--------------------------------------------------------------------------------
  AtivaAjusteCamisa - Inicializa o ajuste de camisa da cuba apos receber
		a sinalizacao de partida do McpCorrida.
--------------------------------------------------------------------------------
*/
void AtivaAjusteCamisa(int Cuba, time_t HoraAtual)
{
  /* -- Verifica se nao esta ajustando -- */
  if (EST_AVC(Cuba).Est.AjusteCamisa eq FALSO and
		EST_AVC(Cuba).Est.AbortaAjuste ne ABORTA_DESAB_CAMISA)
  {
	EST_AVC(Cuba).Est.AbortaAjuste = AJUSTE_NORMAL;
//	EST_AVC(Cuba).Est.CamNAjust = FALSO;
  }
  /* -- Verifica se nao esta ajustando e sinalizou corrida -- */
  if ((EST_AVC(Cuba).Est.AjusteCamisa ne VERDADEIRO) and
	  (EST_AVC(Cuba).Corrida eq VERDADEIRO))
  {
	/*-- Verifica inibicao temporaria do ajuste --*/
	if (AVC.User1[Cuba].ContInibAjCam <= 0)
	{
	  if ((EST_AVC(Cuba).Est.AbortaAjuste eq AJUSTE_NORMAL))
	  {
		/*-- Inicio do ajuste de camisa --*/
		EST_AVC(Cuba).Est.AjusteCamisa = VERDADEIRO;
		AVC.User1[Cuba].ContTAjAcum = 0.0;
		AVC.User1[Cuba].ContTAjCam = 0.0;
		GeraEvento(AJUSTE_CAMISA,Cuba,-1,"Inicio", STR_TRACO, STR_TRACO);
	  }
	  VerifCondCamisa(Cuba, HoraAtual);
	}
    else
	{
	  GeraEvento(CAMISA_NAO_AJUSTADA,Cuba,-1,"Ajuste", "Inibido");
	  EST_AVC(Cuba).Est.CamNAjust = VERDADEIRO;
	}
  }
} /*-- AtivaAjusteCamisa --*/


/*
--------------------------------------------------------------------------------
  VerifCondCamisa - Verifica condicoes para ativacao do ajuste de camisa
--------------------------------------------------------------------------------
*/
void VerifCondCamisa(int Cuba, time_t HoraAtual)
{
  /*-- Sai quando ajuste ja foi cancelado --*/
  if (EST_AVC(Cuba).Est.AbortaAjuste ne AJUSTE_NORMAL)
	return;

  /*-- Aborta ativacao por desabilitacao do ajuste --*/
  if (AVC.ParUser1[Cuba].HabAjCam ne VERDADEIRO)
  {
	FimAjCamisa(Cuba, ABORTA_DESAB_CAMISA);
	return;
  }

  /*-- Aborta ativacao por operacao --*/
  if (EST_AVC(Cuba).Est.AtivCamOpe ne VERDADEIRO)
  {
	FimAjCamisa(Cuba, ABORTA_DESAB_OPERADOR);
	return;
  }

  /*-- Aborta ativacao por intervalo entre corridas --*/
  if ((HoraAtual - AVC.Cleit[Cuba].HoraCorrAnt) <=
	  (AVC.ParUser1[Cuba].IntAjCamCorr * 60))
  {
	if(AVC.ParUser1[Cuba].HabMovCamTur eq FALSO and
		EST_AVC(Cuba).Est.AjusteCamTur eq FALSO)
	{
	  FimAjCamisa(Cuba, ABORTA_INTERV_CORRIDA);
	  return;
	}
  }

  /*-- Aborta ativacao por troca de pinos - inibido 12/05/99 --*/
//if ((EST_AVC(Cuba).TrataTPinos eq VERDADEIRO) and
//	  (EST_AVC(Cuba).Corrida eq VERDADEIRO))
//{
//	FimAjCamisa(Cuba, ABORTA_TROCA_PINOS);
//	return;
//}

//if ((EST_AVC(Cuba).TrataCruzeiro eq VERDADEIRO) and
//	  (EST_AVC(Cuba).Corrida eq VERDADEIRO))
//{
//	FimAjCamisa(Cuba, ABORTA_MANOBRA_CRUZEIRO);
//	return;
//}

  /*-- Aborta ativacao por quebrada - inibido 12/05/99 --*/
//if ((EST_AVC(Cuba).Quebrada eq VERDADEIRO) and
//	  (EST_AVC(Cuba).Corrida eq VERDADEIRO))
//{
//	FimAjCamisa(Cuba, ABORTA_QUEBRADA);
//	return;
//}

  /*-- Aborta ativacao por previsao --*/
  if (EST_AVC(Cuba).EaPrev eq VERDADEIRO)
  {
	FimAjCamisa(Cuba, ABORTA_PREVISAO);
	return;
  }

  /*-- Aborta ativacao por efeito anodico --*/
  if (EST_AVC(Cuba).Ea eq VERDADEIRO)
  {
	FimAjCamisa(Cuba, ABORTA_EFEITO_ANODICO);
	return;
  }

  /*-- Aborta ativacao por desvio tensao --*/
  if ((EST_AVC(Cuba).DesvioTensao eq VERDADEIRO) and
	  (AVC.Cleit[Cuba].HoraUltCorr > AVC.Ccont[Cuba].HoraUltVDesv))
  {
	FimAjCamisa(Cuba, ABORTA_DESVIO_TENSAO);
	return;
  }

  /*-- Aborta ativacao por estouro de tempo --*/
  if (AVC.User1[Cuba].ContTAjAcum > AVC.ParUser1[Cuba].LimMaxAjCam)
  {
	FimAjCamisa(Cuba, ABORTA_EXCESSO_TEMPO);
	return;
  }

  /*-- Aborta ativacao por cuba fora de leitura --*/
  if (EST_AVC(Cuba).ForaLeitura eq VERDADEIRO)
  {
	FimAjCamisa(Cuba, ABORTA_FORA_LEITURA);
	return;
  }

  /*-- Aborta ativacao por cuba fora de controle --*/
  if (EST_AVC(Cuba).ForaControle eq VERDADEIRO)
  {
	FimAjCamisa(Cuba, ABORTA_FORA_CONTROLE);
	return;
  }

  /*-- Aborta ativacao por linha desabilitada --*/
  if (AVL.LinhaHabilitada ne VERDADEIRO)
  {
	FimAjCamisa(Cuba, ABORTA_LINHA_DESAB);
	return;
  }

} /*-- VerifCondCamisa --*/

/*
--------------------------------------------------------------------------------
  FimAjCamisa - Gera parametros para evento de camisa nao ajustada e 
		inicializa contador de movimentos.
--------------------------------------------------------------------------------
*/
void FimAjCamisa(int Cuba, int Motivo)
{
  if (EST_AVC(Cuba).Est.AbortaAjuste eq AJUSTE_NORMAL)
  {
	EST_AVC(Cuba).Est.AjusteCamTur = FALSO;
	switch (Motivo)
	{
	  case  ABORTA_TROCA_PINOS:
			GeraEvento(CAMISA_NAO_AJUSTADA,Cuba,-1,"Troca", "Pinos");
			EST_AVC(Cuba).Est.CamNAjust = VERDADEIRO;
			break;   
	  case  ABORTA_MANOBRA_CRUZEIRO:
			GeraEvento(CAMISA_NAO_AJUSTADA,Cuba,-1,"Manobra", "Cruzeiro");
			EST_AVC(Cuba).Est.CamNAjust = VERDADEIRO;
			break;   
	  case  ABORTA_QUEBRADA:
			GeraEvento(CAMISA_NAO_AJUSTADA,Cuba,-1,"Quebrada", "--------");
			EST_AVC(Cuba).Est.CamNAjust = VERDADEIRO;
			break;   
	  case  ABORTA_PREVISAO:
			GeraEvento(CAMISA_NAO_AJUSTADA,Cuba,-1,"Previsao", "--------");
			EST_AVC(Cuba).Est.CamNAjust = VERDADEIRO;
			break;   
	  case  ABORTA_EFEITO_ANODICO:
			GeraEvento(CAMISA_NAO_AJUSTADA,Cuba,-1,"Efeito", "Anodico");
			EST_AVC(Cuba).Est.CamNAjust = VERDADEIRO;
			break;   
	  case  ABORTA_DESVIO_TENSAO:
			GeraEvento(CAMISA_NAO_AJUSTADA,Cuba,-1,"Desvio", "Tensao");
			EST_AVC(Cuba).Est.CamNAjust = VERDADEIRO;
			break;   
	  case  ABORTA_EXCESSO_TEMPO:
			GeraEvento(CAMISA_NAO_AJUSTADA,Cuba,-1,"Excesso", "Tempo");
			EST_AVC(Cuba).Est.CamNAjust = VERDADEIRO;
			break;   
	  case  ABORTA_INTERV_CORRIDA:
			GeraEvento(CAMISA_NAO_AJUSTADA,Cuba,-1,"Interv.", "Corrida");
			EST_AVC(Cuba).Est.CamNAjust = VERDADEIRO;
			break;   
	  case  ABORTA_DESAB_CAMISA:
//			GeraEvento(CAMISA_NAO_AJUSTADA,Cuba,-1,"Desab", "Camisa");
			break;
	  case  ABORTA_DESAB_OPERADOR:
//			GeraEvento(CAMISA_NAO_AJUSTADA,Cuba,-1,"Desat", "Operador");
			break;
	  case  ABORTA_BARRA_QUEBRADA:
			GeraEvento(CAMISA_NAO_AJUSTADA,Cuba,-1,"Barra", "Quebrada");
			EST_AVC(Cuba).Est.CamNAjust = VERDADEIRO;
			break;   
	  case  ABORTA_FORA_CONTROLE:
			GeraEvento(CAMISA_NAO_AJUSTADA,Cuba,-1,"Fora", "Controle");
			EST_AVC(Cuba).Est.CamNAjust = VERDADEIRO;
			break;   
	  case  ABORTA_FORA_LEITURA:
			GeraEvento(CAMISA_NAO_AJUSTADA,Cuba,-1,"Fora", "Leitura");
			EST_AVC(Cuba).Est.CamNAjust = VERDADEIRO;
			break;   
	  case  ABORTA_LINHA_DESAB:
			GeraEvento(CAMISA_NAO_AJUSTADA,Cuba,-1,"Linha", "Desab");
			EST_AVC(Cuba).Est.CamNAjust = VERDADEIRO;
			break;   
	  default:
			EmiteAlarmeFor(TODOS_DISPOSITIVOS,"AjusteCamisa - Motivo %d invalido, Cuba %d",
						   Motivo, ConvCubScoreOper(Cuba));
			break;
	}

	EST_AVC(Cuba).Est.AbortaAjuste = Motivo;
	AVC.User1[Cuba].ContTAjCam = 0.0;
  }

} /*-- FimAjCamisa --*/

/*
--------------------------------------------------------------------------------
  CalcMovCamisa - acrescenta tempo do novo movimento de anodo para camisa
--------------------------------------------------------------------------------
*/
void CalcMovCamisa(int Cuba, float Duracao, time_t HoraAtual)
{
  if ((EST_AVC(Cuba).Est.AjusteCamisa eq VERDADEIRO) and
	  (AVC.User1[Cuba].ContInibAjCam <= 0))
  {
	VerifCondCamisa(Cuba, HoraAtual);
	if (EST_AVC(Cuba).Est.AbortaAjuste eq AJUSTE_NORMAL)
	{
	  /*-- Contabiliza tempo para movimento de camisa --*/
	  AVC.User1[Cuba].ContTAjCam += Duracao;
	}
  }
}

/*
--------------------------------------------------------------------------------
  VerifFimCamisa - Verifica fim do ajuste de camisa
--------------------------------------------------------------------------------
*/
void VerifFimCamisa(int Cuba)
{
  char DurMov[9];

  if ((EST_AVC(Cuba).Est.AjusteCamisa eq VERDADEIRO) and
	  (EST_AVC(Cuba).Corrida eq FALSO))
  {
	/*-- Verifica inibicao temporaria do ajuste --*/
	if (AVC.User1[Cuba].ContTAjCam <= 0)
	{
	  /*-- Fim do ajuste de camisa --*/
	  if (EST_AVC(Cuba).Est.AbortaAjuste eq AJUSTE_NORMAL)
	  {
		sprintf(DurMov, "%5.2f", AVC.User1[Cuba].ContTAjAcum);
		GeraEvento(AJUSTE_CAMISA,Cuba,-1,"Fim", DurMov, STR_TRACO);
	  }
	  else
	  {
		if(EST_AVC(Cuba).Est.AbortaAjuste ne ABORTA_DESAB_CAMISA)
		  EST_AVC(Cuba).Est.AbortaAjuste = AJUSTE_NORMAL;
	  }
	  EST_AVC(Cuba).Est.AjusteCamisa = FALSO;
	}
  }
} /*-- TrataCamisa --*/

