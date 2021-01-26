/*

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.

	PROJETO		: Geral

	SISTEMA		: Geral

	ARQUIVO		: AlteraBit.c

	CONTEUDO	: Programa alterar variaveis das cubas on-line.

	AUTOR		: Leonel Vicente Mota Ivo

	VERSAO		: 1.0			-		DATA	:	29/08/96

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
dd/mm/aa | descricao                                            | autor 
-------------------------------------------------------------------------------
29/12/05 | Unificado a zona do move e previsao (Elias verificou | EHT001
		 | que varios valores e lim_reslop1 = 0.022 e 0.025
		 |						lim_reslop2 = 0.028 e 0.032
		 |						lim_resinc1 = 0.86 e 1.07
		 |						lim_resinc2 = 1.00 e 1.21
		 |						lim_move_reslop1 = 0.019 e 0.22
		 |						lim_move_reslop2 = 0.024 e 0.028
		 |						lim_move_resinc1 = 0.65 e 0.86
		 |						lim_move_resinc2 = 0.79 e 1.00
		 | Obs.: Alterar tambem no /score3.0/fontes/ope/alcan/OpeNewEaVS
-------------------------------------------------------------------------------
******************************************************************************/

/*
-------------------------------------------------------------------------------
                           Definicao de compilacao condicional
-------------------------------------------------------------------------------
*/
#define		PROGRAMA_PRINCIPAL

/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include	<stdio.h>
#include	<stdlib.h>
#include	<stddef.h>
#include	<string.h>
#include	<sys/types.h>
#include	<sys/name.h>
#include	<Score.h>
#include	<RelGraf.h>
#include	<Prototipos.h>
#include	<VarsComum.h>
#include	<Prototipos.h>
#include	<time.h>
#include	<fcntl.h>
#include	<sys/stat.h>
#include	<DescrArqVar.h>
#include	<VarsComum.h>
#include 	<BdScore.h>
#include	<ScoreMsgs.h>
#include	<math.h>
#include	<UsuRemota.h>
#include	<RemotaAtn7.h>
#include	<ScoreErros.h>
/*
-------------------------------------------------------------------------------
                           Prototipos
-------------------------------------------------------------------------------
*/
void le_valores();

/*
-------------------------------------------------------------------------------
                           Main
-------------------------------------------------------------------------------
*/
void main(void)
{

  printf("\nInicializa base dados\n");

  if (qnx_name_locate(My_nid,"Atan/Score/AdmSemaf",sizeof(int),NULL) ne -1)
  {
	fprintf(stderr,"SCORE ATIVO! ACIONE <ENTER> PARA CONTINUAR OU <CTRL><BREAK> PARA PARAR\n");
	getchar();
	if (PegaComum (&Comum))
	  error("Falha no pegacomum!\n");
    printf("\nPara interromper acione <CTRL><BREAK>\n\n");
	ini_valores();
  }
  else
  {
    printf("Nao implementado para Score desativado.\n");
//	if (CriaAreaGlobal(0,&Comum))
//	{
//	  fprintf(stderr,"Falha cria area global!\n");
//	  exit(EXIT_FAILURE);
//	}
//  printf("\nPara interromper acione <CTRL><BREAK>\n\n");
//	ini_valores();
//	grava_vars();
  }
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

/*
-------------------------------------------------------------------------------
	WriteArq	- Grava os dados no arquivo efetivamente
-------------------------------------------------------------------------------
*/
int WriteArq(int Fildes,char *PBuff,long OffsetIni,long Tamanho)
{
  lseek(Fildes, OffsetIni, SEEK_SET);
  if( (write(Fildes, PBuff, Tamanho)) ne Tamanho)
	return(0);
  return(1);
}

/* -- Funcao para gravar tabelas na base de dados -- */
void grava_vars(void)
{
  int		FildesHist;
  char 		FName[50];


  /* -- Salva tabelas apontadas pelo AVC -- */
  sprintf (FName, ARQUIVO_AVC);
  if( (FildesHist = open (FName,O_RDWR) ) eq -1 )
	error("Erro na abertura do arquivo %s", FName);
  else
  {
	if((WriteArq(FildesHist,(char *)(&(AVC.ParUser1)),
				 offsetof(struct arq_var_cubas,ParUser1),
				 (long) sizeof(t_par1_user) * MAX_CUBAS)) eq 0)
	  error("Erro de escrita arquivo %s",FName);

	if((WriteArq(FildesHist,(char *)(&(AVC.ParUser2)),
				 offsetof(struct arq_var_cubas,ParUser2),
				 (long) sizeof(t_par2_user) * MAX_CUBAS)) eq 0)
	  error("Erro de escrita arquivo %s",FName);

	if((WriteArq(FildesHist,(char *)(&(AVC.User1)),
				 offsetof(struct arq_var_cubas,User1),
				 (long) sizeof(t_user1_avc) * MAX_CUBAS)) eq 0)
	  error("Erro de escrita arquivo %s",FName);

	if((WriteArq(FildesHist,(char *)(&(AVC.User2)),
				 offsetof(struct arq_var_cubas,User2),
				 (long) sizeof(t_user2_avc) * MAX_CUBAS)) eq 0)
	  error("Erro de escrita arquivo %s",FName);

	if((WriteArq(FildesHist,(char *)(&(AVC.User3)),
				 offsetof(struct arq_var_cubas,User3),
				 (long) sizeof(t_user3_avc) * MAX_CUBAS)) eq 0)
	  error("Erro de escrita arquivo %s",FName);

	if((WriteArq(FildesHist,(char *)(&(AVC.User4)),
				 offsetof(struct arq_var_cubas,User4),
				 (long) sizeof(t_user4_avc) * MAX_CUBAS)) eq 0)
	  error("Erro de escrita arquivo %s",FName);

  }
  close(FildesHist);

}


/* -- Fim do arquivo AlteraTodasCubasVS.c -- */

/* inicializa os valores para cada cuba */
void ini_valores()
{
 short int Cuba;
 int CubaOpe;
 int i;
 int k;
//byte sobe, desce, quebrada;


//  long hora_qca;
//  struct tm	DataTm;


//	Cuba = ConvCubOperScore(176);
//	EST_AVC(Cuba).Est.forno_anel = FALSO;
//	EST_AVC(Cuba).Est.forno_novo = FALSO;
//	EST_AVC(Cuba).Est.forno_rem = FALSO;
//	Cuba = ConvCubOperScore(265);
//	EST_AVC(Cuba).Est.forno_anel = FALSO;
//	EST_AVC(Cuba).Est.forno_novo = FALSO;
//	EST_AVC(Cuba).Est.forno_rem = FALSO;
//	Cuba = ConvCubOperScore(281);
//	EST_AVC(Cuba).Est.forno_anel = FALSO;
//	EST_AVC(Cuba).Est.forno_novo = FALSO;
//	EST_AVC(Cuba).Est.forno_rem = FALSO;

//  for( CubaOpe = 301; CubaOpe <= 308; ++CubaOpe )
//  {
//	Cuba = ConvCubOperScore(CubaOpe);
//	AVC.User4[Cuba].int_iniae_sopro = 210;
//  }
//  for( CubaOpe = 389; CubaOpe <= 396; ++CubaOpe )
//  {
//	Cuba = ConvCubOperScore(CubaOpe);
//	AVC.User4[Cuba].int_iniae_sopro = 210;
//  }

//  for( Cuba = 0; Cuba < MAX_CUBAS; ++Cuba )
//	EST_AVC(Cuba).Est.motdef = FALSO;
//	Cuba = ConvCubOperScore(319);
//	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
//	Cuba = ConvCubOperScore(378);
//	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
//	Cuba = ConvCubOperScore(412);
//	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
//	Cuba = ConvCubOperScore(373);
//	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
//	Cuba = ConvCubOperScore(380);
//	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
//	for( Cuba = 0; Cuba < MAX_CUBAS; ++Cuba )
//	{
//	  AVC.User4[Cuba].lim_queb_scb = 21600;
//	}
//	Cuba = ConvCubOperScore(405);
//	AVC.User3[Cuba].ten_inc_banho =0.0;
//	Cuba = ConvCubOperScore(488);
//	AVC.User3[Cuba].ten_inc_banho =0.0;
//	Cuba = ConvCubOperScore(483);
//	AVC.User3[Cuba].ten_inc_banho =0.0;
//	Cuba = ConvCubOperScore(417);
//	AVC.User3[Cuba].ten_inc_banho =0.0;
//	Cuba = ConvCubOperScore(421);
//	AVC.User3[Cuba].ten_inc_banho =0.0;
//	Cuba = ConvCubOperScore(480);
//	AVC.User3[Cuba].ten_inc_banho =0.0;
//	Cuba = ConvCubOperScore(321);
//	AVC.User4[Cuba].lim_queb_eq[1] = 9;
//	AVC.User4[Cuba].seq_normal[1] = 63;
//	Cuba = ConvCubOperScore(322);
//	AVC.User4[Cuba].lim_queb_eq[1] = 9;
//	AVC.User4[Cuba].seq_normal[1] = 63;

//	for( Cuba = 0; Cuba < MAX_CUBAS; ++Cuba )
//	{
//	  AVC.User4[Cuba].lim_queb_eq[1] = 12;
//	  AVC.User4[Cuba].lim_queb_eq[2] = 5;
//	  AVC.User4[Cuba].lim_queb_eq[3] = 6;
//	}
//	Cuba = ConvCubOperScore(382);
//	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

//  for( CubaOpe = 301; CubaOpe <= 396; ++CubaOpe )
//  {
//	Cuba = ConvCubOperScore(CubaOpe);
//	AVC.User1[Cuba].num_queb_eq = 0;
//  }

//	for( Cuba = 0; Cuba < MAX_CUBAS; ++Cuba )
//	{
//		AVC.User4[Cuba].ResC = 0.0;
//		AVC.User4[Cuba].Rf = 0.0; 
//		AVC.User4[Cuba].pente = 0.0;
//		AVC.User4[Cuba].Aceleracao = 0.0;
//		AVC.User4[Cuba].Rfmin = 0.0; 
//	}

//	for( Cuba = 0; Cuba < MAX_CUBAS; ++Cuba )
//	{
//	  AVC.User4[Cuba].res2m_calob = AVC.User1[Cuba].res_2m;
//	  AVC.User4[Cuba].ResC = 0.0;
//	  AVC.User4[Cuba].Rf = 0.0;
//	  AVC.User4[Cuba].pente = 0.0;
//	  AVC.User4[Cuba].Aceleracao = 0.0;
//	}

//	for( Cuba = 0; Cuba < MAX_CUBAS; ++Cuba )
//	{
//	  if (AVC.User4[Cuba].Rf ne 0)
//		AVC.User4[Cuba].Rfmin = AVC.User4[Cuba].Rf;
//	}
//	Cuba = ConvCubOperScore(110);
//	EST_AVC(Cuba).Est.fusivel = FALSO;

//	Cuba = ConvCubOperScore(301);
//	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
//	Cuba = ConvCubOperScore(306);
//	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

//	for( Cuba = 0; Cuba < MAX_CUBAS; ++Cuba )
//	{
//	  EST_AVC(Cuba).Est.previsao_ativo = FALSO;
//	}

//for( CubaOpe = 401; CubaOpe <= 496; ++CubaOpe )
//{
//	Cuba = ConvCubOperScore(CubaOpe);
//	AVC.User4[Cuba].lim_pcb_pcb = 4*3600;
//  }

//	for( Cuba = 0; Cuba < MAX_CUBAS; ++Cuba )
//	{
//	  EST_AVC(Cuba).Est.desvio_tensao = FALSO;
//	}

//	Cuba = ConvCubOperScore(304);
//	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

//	Cuba = ConvCubOperScore(404);
//	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

//	Cuba = ConvCubOperScore(324);
//	EST_AVC(Cuba).Est.long_ae = FALSO;
//	Cuba = ConvCubOperScore(387);
//	EST_AVC(Cuba).Est.long_ae = FALSO;
//	Cuba = ConvCubOperScore(380);
//	EST_AVC(Cuba).Est.long_ae = FALSO;
//	Cuba = ConvCubOperScore(381);
//	EST_AVC(Cuba).Est.long_ae = FALSO;
//	Cuba = ConvCubOperScore(414);
//	EST_AVC(Cuba).Est.long_ae = FALSO;
//	Cuba = ConvCubOperScore(373);
//	EST_AVC(Cuba).Est.long_ae = FALSO;

//	Cuba = ConvCubOperScore(306);
//	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

//	Cuba = ConvCubOperScore(416);
//	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

//	Cuba = ConvCubOperScore(316);
//	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

//	Cuba = ConvCubOperScore(393);
//	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

//	Cuba = ConvCubOperScore(324);
//	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

//	Cuba = ConvCubOperScore(311);
//	AVC.User3[Cuba].tipo_forno_prob = NOVO;
//	Cuba = ConvCubOperScore(391);
//	AVC.User3[Cuba].tipo_forno_prob = NOVO;
//	Cuba = ConvCubOperScore(408);
//	AVC.User3[Cuba].tipo_forno_prob = NOVO;
//	Cuba = ConvCubOperScore(475);
//	AVC.User3[Cuba].tipo_forno_prob = NOVO;
//	Cuba = ConvCubOperScore(486);
//	AVC.User3[Cuba].tipo_forno_prob = NOVO;

//	Cuba = ConvCubOperScore(481);
//	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

//	Cuba = ConvCubOperScore(494);
//	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
//	Cuba = ConvCubOperScore(496);
//	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

//   AVL.Trab.linha_move = FALSO;
//   AVL.Trab.linha_move = VERDADEIRO;

//	for( Cuba = 0; Cuba < MAX_CUBAS; ++Cuba )
//	{
//	EST_AVC(Cuba).Est.desvio_tensao = FALSO;

//	EST_AVC(Cuba).Est.alarme_ae = FALSO;
//	  AVC.User4[Cuba].int_esp_quebae = 60;
//	  AVC.User4[Cuba].lim_reslop1 = ???;
//	  AVC.User4[Cuba].lim_resinc1 = ???;
//	}
//	Cuba = ConvCubOperScore(242);
//	EST_AVC(Cuba).Est.alarme_ae = FALSO;
//	Cuba = ConvCubOperScore(105);
//	AVC.User4[Cuba].lim_ae_longo = 3*60;

//	for( Cuba = 0; Cuba < MAX_CUBAS; ++Cuba )
//	{
//	  EST_AVC(Cuba).Est.ev_espera = FALSO;
//	}

//	for( CubaOpe = 201; CubaOpe <= 223; ++CubaOpe )
//	{
//	  Cuba = ConvCubOperScore(CubaOpe);
//	  AVC.User4[Cuba].lim_queb_scb = 8*3600;
//	  AVC.User4[Cuba].lim_queb_eq[0] = 3;
//	  AVC.User4[Cuba].hora_queb_ref = 2*3600;
//	}
//	for( Cuba = 0; Cuba < MAX_CUBAS; ++Cuba )
//	{
//	  EST_AVC(Cuba).Est.efeito_manual = VERDADEIRO;
//	}
//	for( Cuba = 0; Cuba < MAX_CUBAS; ++Cuba )
//	{
//	  AVC.User1[Cuba].ciclo_alumina = 0;
//	  AVC.User4[Cuba].num_queb = 0;
//	}
//	for( CubaOpe = 201; CubaOpe <= 223; ++CubaOpe )
//	{
//	  Cuba = ConvCubOperScore(CubaOpe);
//	  AVC.User3[Cuba].side_break = CORREDOR;
//	}
//	  Cuba = ConvCubOperScore(205);
//	  AVC.User3[Cuba].side_break = JANELA;
//	  Cuba = ConvCubOperScore(206);
//	  AVC.User3[Cuba].side_break = JANELA;
//	  Cuba = ConvCubOperScore(208);
//	  AVC.User3[Cuba].side_break = JANELA;

//	  Cuba = ConvCubOperScore(207);
//	  AVC.User3[Cuba].side_break = JANELA;
//	  Cuba = ConvCubOperScore(208);
//	  AVC.User3[Cuba].side_break = JANELA;
//	  Cuba = ConvCubOperScore(220);
//	  AVC.User3[Cuba].side_break = JANELA;
//	for( CubaOpe = 160; CubaOpe <= 165; ++CubaOpe )
//	{
//	  Cuba = ConvCubOperScore(CubaOpe);
//	  AVC.User3[Cuba].hora_queb_qca = 986827480;
//	}
//	for( CubaOpe = 224; CubaOpe <= 229; ++CubaOpe )
//	{
//	  Cuba = ConvCubOperScore(CubaOpe);
//	  AVC.User3[Cuba].hora_queb_qca = 986822240;
//	}
//
//	memset( &DataTm, 0x00, sizeof( struct tm ) );
//	DataTm.tm_sec  = 0;
//	DataTm.tm_min  = 50;
//	DataTm.tm_hour = 14;
//	DataTm.tm_mday = 10;
//	DataTm.tm_mon  = 04;
//	/* -- Y2k inicio: ano de 2 digitos -- */
//	DataTm.tm_year = 101;
//	hora_qca = mktime(&DataTm); /* converte para time_t */
//	for( CubaOpe = 124; CubaOpe <= 135; ++CubaOpe )
//	{
//	  Cuba = ConvCubOperScore(CubaOpe);
//	  AVC.User3[Cuba].hora_queb_qca = hora_qca;
//	}
//
//	memset( &DataTm, 0x00, sizeof( struct tm ) );
//	DataTm.tm_sec  = 0;
//	DataTm.tm_min  = 9;
//	DataTm.tm_hour = 15;
//	DataTm.tm_mday = 8;
//	DataTm.tm_mon  = 04;
//	/* -- Y2k inicio: ano de 2 digitos -- */
//	DataTm.tm_year = 101;
//	hora_qca = mktime(&DataTm); /* converte para time_t */
//	for( CubaOpe = 136; CubaOpe <= 141; ++CubaOpe )
//	{
//	  Cuba = ConvCubOperScore(CubaOpe);
//	  AVC.User3[Cuba].hora_queb_qca = hora_qca;
//	}

//	memset( &DataTm, 0x00, sizeof( struct tm ) );
//	DataTm.tm_sec  = 0;
//	DataTm.tm_min  = 20;
//	DataTm.tm_hour = 11;
//	DataTm.tm_mday = 8;
//	DataTm.tm_mon  = 4;
//	/* -- Y2k inicio: ano de 2 digitos -- */
//	DataTm.tm_year = 101;
//	hora_qca = mktime(&DataTm); /* converte para time_t */
//	for( CubaOpe = 143; CubaOpe <= 147; ++CubaOpe )
//	{
//	  Cuba = ConvCubOperScore(CubaOpe);
//	  AVC.User3[Cuba].hora_queb_qca = hora_qca;
//	}
//
//	memset( &DataTm, 0x00, sizeof( struct tm ) );
//	DataTm.tm_sec  = 0;
//	DataTm.tm_min  = 50;
//	DataTm.tm_hour = 14;
//	DataTm.tm_mday = 7;
//	DataTm.tm_mon  = 4;
//	/* -- Y2k inicio: ano de 2 digitos -- */
//	DataTm.tm_year = 101;
//	hora_qca = mktime(&DataTm); /* converte para time_t */
//	for( CubaOpe = 148; CubaOpe <= 153; ++CubaOpe )
//	{
//	  Cuba = ConvCubOperScore(CubaOpe);
//	  AVC.User3[Cuba].hora_queb_qca = hora_qca;
//	}
//
//	memset( &DataTm, 0x00, sizeof( struct tm ) );
//	DataTm.tm_sec  = 0;
//	DataTm.tm_min  = 8;
//	DataTm.tm_hour = 15;
//	DataTm.tm_mday = 4;
//	DataTm.tm_mon  = 4;
//	/* -- Y2k inicio: ano de 2 digitos -- */
//	DataTm.tm_year = 101;
//	hora_qca = mktime(&DataTm); /* converte para time_t */
//	for( CubaOpe = 154; CubaOpe <= 159; ++CubaOpe )
//	{
//	  Cuba = ConvCubOperScore(CubaOpe);
//	  AVC.User3[Cuba].hora_queb_qca = hora_qca;
//	}
//
//	memset( &DataTm, 0x00, sizeof( struct tm ) );
//	DataTm.tm_sec  = 0;
//	DataTm.tm_min  = 06;
//	DataTm.tm_hour = 14;
//	DataTm.tm_mday = 4;
//	DataTm.tm_mon  = 4;
//	/* -- Y2k inicio: ano de 2 digitos -- */
//	DataTm.tm_year = 101;
//	hora_qca = mktime(&DataTm); /* converte para time_t */
//	for( CubaOpe = 160; CubaOpe <= 165; ++CubaOpe )
//	{
//	  Cuba = ConvCubOperScore(CubaOpe);
//	  AVC.User3[Cuba].hora_queb_qca = hora_qca;
//	}

/*
	for( CubaOpe = 166; CubaOpe <= 170; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  EST_AVC(Cuba).Est.preveu  = VERDADEIRO;
	}
*/

/* Foi colocado este trecho para gerar dados abaixo p/ o Bandeira */

/*
  fp = fopen ("/usr/score/Bandeira", "w");

  if (fp eq NULL)
  {
	  error("Erro de escrita arquivo /usr/score/Bandeira");
  }

	  CubaOpe = 495;
	  Cuba = ConvCubOperScore(CubaOpe);
	  fprintf (fp, "Cuba: %d - ini: %ld fim: %ld\n",
			   CubaOpe,
AVC.User4[Cuba].hora_ini_aepcb_off,
AVC.User4[Cuba].hora_fim_aepcb_off);

	for( CubaOpe = 101; CubaOpe <= 188; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  fprintf (fp, "Cuba: %3d - %3d %3d\n",
			   CubaOpe,
			   AVC.Abs[Cuba].BitSobeAnodo,
			   AVC.Abs[Cuba].BitDesceAnodo);
			 
	}

	for( CubaOpe = 201; CubaOpe <= 288; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  fprintf (fp, "Cuba: %3d - %3d %3d\n",
			   CubaOpe,
			   AVC.Abs[Cuba].BitSobeAnodo,
			   AVC.Abs[Cuba].BitDesceAnodo);
			 
	}

	fclose (fp);
*/

//	  Cuba = ConvCubOperScore(101);
//	  EST_AVC(Cuba).Est.sinal_queb = FALSO;

/*
	for( CubaOpe = 107; CubaOpe <= 109; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = 1001514600;
	}

	for( CubaOpe = 111; CubaOpe <= 123; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = 1001514600;
	}

	for( CubaOpe = 124; CubaOpe <= 126; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = 1001517000;
	}
	for( CubaOpe = 102; CubaOpe <= 103; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = 1000733624;
	}
	  Cuba = ConvCubOperScore(104);
	  AVC.User3[Cuba].hora_queb_qca = 1000824740;
	for( CubaOpe = 166; CubaOpe <= 167; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = 1001001495;
	}
	  Cuba = ConvCubOperScore(110);
	  AVC.User3[Cuba].hora_queb_qca = 1000820166;
	for( CubaOpe = 168; CubaOpe <= 170; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = 1000924563;
	}
	  Cuba = ConvCubOperScore(171);
	  AVC.User3[Cuba].hora_queb_qca = 1001001495;
	for( CubaOpe = 173; CubaOpe <= 175; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = 1001092989;
	}
	for( CubaOpe = 176; CubaOpe <= 177; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = 1000924563;
	}
	for( CubaOpe = 178; CubaOpe <= 187; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = 1000820599;
	}
	for( CubaOpe = 128; CubaOpe <= 129; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = 1001345879;
	}
	for( CubaOpe = 130; CubaOpe <= 141; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = 1001342850;
	}
	  Cuba = ConvCubOperScore(142);
	  AVC.User3[Cuba].hora_queb_qca = 1001173580;
	for( CubaOpe = 144; CubaOpe <= 147; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = 1001173580;
	}
	for( CubaOpe = 149; CubaOpe <= 151; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = 1001173580;
	}
	  Cuba = ConvCubOperScore(153);
	  AVC.User3[Cuba].hora_queb_qca = 1001173580;
	for( CubaOpe = 154; CubaOpe <= 159; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = 1001084944;
	}
	for( CubaOpe = 160; CubaOpe <= 165; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = 1001001588;
	}
	for( CubaOpe = 101; CubaOpe <= 288; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_temp_baixa = 0;
	}
	  Cuba = ConvCubOperScore(166);
	  AVC.User1[Cuba].eqmotor_down = 0.24e-6;

	  Cuba = ConvCubOperScore(495);
	  AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	  EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

	for( CubaOpe = 101; CubaOpe <= 288; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  EST_AVC(Cuba).Est.atua_acao_prev = FALSO;
	  EST_AVC(Cuba).Est.ini_acao_prev = FALSO;
	  AVC.User4[Cuba].cod_julg = 0;
	  EST_AVC(Cuba).Est.fim_acao_prev = FALSO;
	  EST_AVC(Cuba).Est.correcao_prev = FALSO;
	}

	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_sec  = 16;
	DataTm.tm_min  = 31;
	DataTm.tm_hour = 15;
	DataTm.tm_mday = 12;
	DataTm.tm_mon  = 10;
	DataTm.tm_year = 101;
	hora_qca = mktime(&DataTm);

	for( CubaOpe = 166; CubaOpe <= 171; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = hora_qca;
	}
	  Cuba = ConvCubOperScore(170);
	  EST_AVC(Cuba).Est.atua_acao_prev = FALSO;

	for( CubaOpe = 101; CubaOpe <= 288; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  EST_AVC(Cuba).Est.instavel = FALSO;
	}

	  Cuba = ConvCubOperScore(170);
	  EST_AVC(Cuba).Est.atua_acao_prev = FALSO;
	  EST_AVC(Cuba).Est.ini_correcao_ruido = FALSO;
	  EST_AVC(Cuba).Est.ini_acao_prev = FALSO;
	  EST_AVC(Cuba).Est.correcao_prev = FALSO;
	  Cuba = ConvCubOperScore(152);
	  EST_AVC(Cuba).Est.instavel = VERDADEIRO;

	 Desabilita Dia de modulacao - terca
	AVL.Par.cor_modul_dia[2] = 0;

	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_sec  = 0;
	DataTm.tm_min  = 30;
	DataTm.tm_hour = 6;
	DataTm.tm_mday = 25;
	DataTm.tm_mon  = 0;
	 -- Y2k inicio: ano de 2 digitos -- 
	DataTm.tm_year = 102;
	hora_qca = mktime(&DataTm);  converte para time_t 
	Cuba = ConvCubOperScore(168);
	AVC.User3[Cuba].hora_queb_qca = hora_qca;

	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_sec  = 0;
	DataTm.tm_min  = 19;
	DataTm.tm_hour = 10;
	DataTm.tm_mday = 04;
	DataTm.tm_mon  = 01;
	DataTm.tm_year = 102;
	hora_qca = mktime(&DataTm);
	for( CubaOpe = 111; CubaOpe <= 116; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = hora_qca;
	}

	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_sec  = 0;
	DataTm.tm_min  = 03;
	DataTm.tm_hour = 15;
	DataTm.tm_mday = 05;
	DataTm.tm_mon  = 01;
	DataTm.tm_year = 102;
	hora_qca = mktime(&DataTm);
	for( CubaOpe = 101; CubaOpe <= 103; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = hora_qca;
	}
	for( CubaOpe = 185; CubaOpe <= 187; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = hora_qca;
	}

	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_sec  = 0;
	DataTm.tm_min  = 18;
	DataTm.tm_hour = 13;
	DataTm.tm_mday = 05;
	DataTm.tm_mon  = 01;
	DataTm.tm_year = 102;
	hora_qca = mktime(&DataTm);
	for( CubaOpe = 104; CubaOpe <= 106; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = hora_qca;
	}
	for( CubaOpe = 108; CubaOpe <= 110; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = hora_qca;
	}

	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_sec  = 0;
	DataTm.tm_min  = 28;
	DataTm.tm_hour = 10;
	DataTm.tm_mday = 05;
	DataTm.tm_mon  = 01;
	DataTm.tm_year = 102;
	hora_qca = mktime(&DataTm);
	Cuba = ConvCubOperScore(166);
	AVC.User3[Cuba].hora_queb_qca = hora_qca;

	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_sec  = 0;
	DataTm.tm_min  = 24;
	DataTm.tm_hour = 14;
	DataTm.tm_mday = 06;
	DataTm.tm_mon  = 01;
	DataTm.tm_year = 102;
	hora_qca = mktime(&DataTm);
	for( CubaOpe = 178; CubaOpe <= 184; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = hora_qca;
	}

	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_sec  = 0;
	DataTm.tm_min  = 27;
	DataTm.tm_hour = 15;
	DataTm.tm_mday = 06;
	DataTm.tm_mon  = 01;
	DataTm.tm_year = 102;
	hora_qca = mktime(&DataTm);
	for( CubaOpe = 171; CubaOpe <= 172; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = hora_qca;
	}
	for( CubaOpe = 174; CubaOpe <= 175; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = hora_qca;
	}
	Cuba = ConvCubOperScore(177);
	AVC.User3[Cuba].hora_queb_qca = hora_qca;

	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_sec  = 0;
	DataTm.tm_min  = 46;
	DataTm.tm_hour = 10;
	DataTm.tm_mday = 07;
	DataTm.tm_mon  = 01;
	DataTm.tm_year = 102;
	hora_qca = mktime(&DataTm);
	for( CubaOpe = 169; CubaOpe <= 170; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = hora_qca;
	}
	Cuba = ConvCubOperScore(167);
	AVC.User3[Cuba].hora_queb_qca = hora_qca;

	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_sec  = 0;
	DataTm.tm_min  = 0;
	DataTm.tm_hour = 13;
	DataTm.tm_mday = 9;
	DataTm.tm_mon  = 01;
	DataTm.tm_year = 102;
	hora_qca = mktime(&DataTm);
	for( CubaOpe = 117; CubaOpe <= 121; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = hora_qca;
	}
	Cuba = ConvCubOperScore(123);
	AVC.User3[Cuba].hora_queb_qca = hora_qca;


	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_sec  = 0;
	DataTm.tm_min  = 38;
	DataTm.tm_hour = 12;
	DataTm.tm_mday = 25;
	DataTm.tm_mon  = 01;
	DataTm.tm_year = 102;
	hora_qca = mktime(&DataTm);
	for( CubaOpe = 147; CubaOpe <= 156; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = hora_qca;
	}
	for( CubaOpe = 158; CubaOpe <= 159; ++CubaOpe )
	{
	  AVC.User3[Cuba].hora_queb_qca = hora_qca;
	}

	  Cuba = ConvCubOperScore(263);
	  AVC.User1[Cuba].eqmotor_down = 1.8e-6;
	  AVC.User1[Cuba].eqmotor_up = 1.8e-6;

	for( CubaOpe = 301; CubaOpe <= 396; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User4[Cuba].hora_queb_ref = 9*3600;
	}

	for( CubaOpe = 401; CubaOpe <= 496; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User4[Cuba].hora_queb_ref = 9*3600;
	}
	  Cuba = ConvCubOperScore(376);
	  AVC.User4[Cuba].hora_queb_ref = 9*3600;
	  AVC.User4[Cuba].seq_normal[1] = 63;
	  AVC.User4[Cuba].seq_normal[2] = 362;

	for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User1[Cuba].tipo_forno_scb = 1;
	  AVC.User4[Cuba].lim_queb_eq[0] = 9;
	  AVC.User4[Cuba].seq_normal[0] = 511;
	  AVC.User4[Cuba].sequencia_queb = 436;
	  AVC.User4[Cuba].int_scb_ae[0] = 1*MIN*SEC;
	  AVC.User4[Cuba].lim_queb_scb = 2*MIN*SEC + 40*SEC;
	  AVC.User4[Cuba].lim_scb_qca = 2*MIN*SEC + 40*SEC;
	  AVC.User4[Cuba].hora_queb_ref = 9*MIN*SEC;
	}

	Cuba = ConvCubOperScore(301);
	AVC.User4[Cuba].carcaca = 61;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(302);
	AVC.User4[Cuba].carcaca = 26;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(303);
	AVC.User4[Cuba].carcaca = 14;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(304);
	AVC.User4[Cuba].carcaca = 34;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(305);
	AVC.User4[Cuba].carcaca = 2;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(306);
	AVC.User4[Cuba].carcaca = 85;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(307);
	AVC.User4[Cuba].carcaca = 54;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(308);
	AVC.User4[Cuba].carcaca = 62;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(309);
	AVC.User4[Cuba].carcaca = 36;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(310);
	AVC.User4[Cuba].carcaca = 7;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(311);
	AVC.User4[Cuba].carcaca = 49;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(312);
	AVC.User4[Cuba].carcaca = 19;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(313);
	AVC.User4[Cuba].carcaca = 67;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(314);
	AVC.User4[Cuba].carcaca = 89;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(315);
	AVC.User4[Cuba].carcaca = 84;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(316);
	AVC.User4[Cuba].carcaca = 77;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(317);
	AVC.User4[Cuba].carcaca = 32;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(318);
	AVC.User4[Cuba].carcaca = 56;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(319);
	AVC.User4[Cuba].carcaca = 97;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(320);
	AVC.User4[Cuba].carcaca = 22;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(321);
	AVC.User4[Cuba].carcaca = 63;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(322);
	AVC.User4[Cuba].carcaca = 78;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(323);
	AVC.User4[Cuba].carcaca = 31;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(324);
	AVC.User4[Cuba].carcaca = 55;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(373);
	AVC.User4[Cuba].carcaca = 74;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(374);
	AVC.User4[Cuba].carcaca = 33;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(375);
	AVC.User4[Cuba].carcaca = 28;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(376);
	AVC.User4[Cuba].carcaca = 20;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(377);
	AVC.User4[Cuba].carcaca = 23;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(378);
	AVC.User4[Cuba].carcaca = 69;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(379);
	AVC.User4[Cuba].carcaca = 10;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(380);
	AVC.User4[Cuba].carcaca = 68;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(381);
	AVC.User4[Cuba].carcaca = 58;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(382);
	AVC.User4[Cuba].carcaca = 52;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(383);
	AVC.User4[Cuba].carcaca = 44;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(384);
	AVC.User4[Cuba].carcaca = 8;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(385);
	AVC.User4[Cuba].carcaca = 80;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(386);
	AVC.User4[Cuba].carcaca = 53;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(387);
	AVC.User4[Cuba].carcaca = 40;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(388);
	AVC.User4[Cuba].carcaca = 91;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(389);
	AVC.User4[Cuba].carcaca = 59;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(390);
	AVC.User4[Cuba].carcaca = 3;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(391);
	AVC.User4[Cuba].carcaca = 35;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(392);
	AVC.User4[Cuba].carcaca = 76;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(393);
	AVC.User4[Cuba].carcaca = 73;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(394);
	AVC.User4[Cuba].carcaca = 81;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(395);
	AVC.User4[Cuba].carcaca = 17;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(396);
	AVC.User4[Cuba].carcaca = 90;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(401);
	AVC.User4[Cuba].carcaca = 94;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(402);
	AVC.User4[Cuba].carcaca = 92;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(403);
	AVC.User4[Cuba].carcaca = 15;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(404);
	AVC.User4[Cuba].carcaca = 83;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(405);
	AVC.User4[Cuba].carcaca = 27;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(406);
	AVC.User4[Cuba].carcaca = 64;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(407);
	AVC.User4[Cuba].carcaca = 30;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(408);
	AVC.User4[Cuba].carcaca = 65;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(309);
	AVC.User4[Cuba].carcaca = 38;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(410);
	AVC.User4[Cuba].carcaca = 75;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(411);
	AVC.User4[Cuba].carcaca = 51;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(412);
	AVC.User4[Cuba].carcaca = 57;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(413);
	AVC.User4[Cuba].carcaca = 43;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(414);
	AVC.User4[Cuba].carcaca = 4;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(415);
	AVC.User4[Cuba].carcaca = 21;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(416);
	AVC.User4[Cuba].carcaca = 11;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(417);
	AVC.User4[Cuba].carcaca = 13;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(418);
	AVC.User4[Cuba].carcaca = 41;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(419);
	AVC.User4[Cuba].carcaca = 95;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(420);
	AVC.User4[Cuba].carcaca = 24;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(421);
	AVC.User4[Cuba].carcaca = 12;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(422);
	AVC.User4[Cuba].carcaca = 42;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(423);
	AVC.User4[Cuba].carcaca = 60;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(424);
	AVC.User4[Cuba].carcaca = 70;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(473);
	AVC.User4[Cuba].carcaca = 87;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(474);
	AVC.User4[Cuba].carcaca = 6;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(475);
	AVC.User4[Cuba].carcaca = 5;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(476);
	AVC.User4[Cuba].carcaca = 46;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(477);
	AVC.User4[Cuba].carcaca = 66;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(478);
	AVC.User4[Cuba].carcaca = 72;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(479);
	AVC.User4[Cuba].carcaca = 86;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(480);
	AVC.User4[Cuba].carcaca = 48;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(481);
	AVC.User4[Cuba].carcaca = 79;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(482);
	AVC.User4[Cuba].carcaca = 96;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(483);
	AVC.User4[Cuba].carcaca = 47;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(484);
	AVC.User4[Cuba].carcaca = 71;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(485);
	AVC.User4[Cuba].carcaca = 50;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(486);
	AVC.User4[Cuba].carcaca = 18;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(487);
	AVC.User4[Cuba].carcaca = 82;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(488);
	AVC.User4[Cuba].carcaca = 25;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(489);
	AVC.User4[Cuba].carcaca = 29;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(490);
	AVC.User4[Cuba].carcaca = 88;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(491);
	AVC.User4[Cuba].carcaca = 1;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(492);
	AVC.User4[Cuba].carcaca = 16;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(493);
	AVC.User4[Cuba].carcaca = 98;
	AVC.User4[Cuba].geracao = 2;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(494);
	AVC.User4[Cuba].carcaca = 37;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(495);
	AVC.User4[Cuba].carcaca = 39;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(496);
	AVC.User4[Cuba].carcaca = 9;
	AVC.User4[Cuba].geracao = 3;
	AVC.User4[Cuba].fase_remendo = 0;

	  Cuba = ConvCubOperScore(185);
	  AVC.User1[Cuba].eqmotor_down = 1.8e-6;
	  AVC.User1[Cuba].eqmotor_up = 1.8e-6;

	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_sec  = 0;
	DataTm.tm_min  = 00;
	DataTm.tm_hour = 10;
	DataTm.tm_mday = 26;
	DataTm.tm_mon  = 9;
	 -- Y2k inicio: ano de 2 digitos -- 
	DataTm.tm_year = 102;
	hora_qca = mktime(&DataTm);  converte para time_t 
	for( CubaOpe = 266; CubaOpe <= 288; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = hora_qca;
	}

	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_sec  = 0;
	DataTm.tm_min  = 00;
	DataTm.tm_hour = 10;
	DataTm.tm_mday = 28;
	DataTm.tm_mon  = 9;
	 -- Y2k inicio: ano de 2 digitos -- 
	DataTm.tm_year = 102;
	hora_qca = mktime(&DataTm);  converte para time_t 
	for( CubaOpe = 236; CubaOpe <= 244; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = hora_qca;
	}

	for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User4[Cuba].lim_scb_qca = 4*MIN*SEC;
	}


	for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User4[Cuba].hora_queb_ref = 9*3600+20*SEC;
	}

	  Cuba = ConvCubOperScore(101);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.53;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.52;

	  Cuba = ConvCubOperScore(102);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.49;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.80;

	  Cuba = ConvCubOperScore(103);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.02;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.31;

	  Cuba = ConvCubOperScore(104);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.03;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.30;

	  Cuba = ConvCubOperScore(105);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.86;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.89;

	  Cuba = ConvCubOperScore(106);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 5.05;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.98;

	  Cuba = ConvCubOperScore(107);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.84;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.29;

	  Cuba = ConvCubOperScore(108);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.82;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.86;

	  Cuba = ConvCubOperScore(109);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.86;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.13;

	  Cuba = ConvCubOperScore(110);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 1.29;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.24;

	  Cuba = ConvCubOperScore(111);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.64;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.67;

	  Cuba = ConvCubOperScore(112);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.95;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.97;

	  Cuba = ConvCubOperScore(113);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 5.08;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.27;

	  Cuba = ConvCubOperScore(114);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.34;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.08;

	  Cuba = ConvCubOperScore(115);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.17;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.0;

	  Cuba = ConvCubOperScore(116);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.03;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.05;

	  Cuba = ConvCubOperScore(117);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.55;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.78;

	  Cuba = ConvCubOperScore(118);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.69;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.1;

	  Cuba = ConvCubOperScore(119);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.64;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.73;

	  Cuba = ConvCubOperScore(120);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.91;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.14;

	  Cuba = ConvCubOperScore(121);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.27;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.12;

	  Cuba = ConvCubOperScore(122);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.13;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.11;

	  Cuba = ConvCubOperScore(123);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.21;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.05;

	  Cuba = ConvCubOperScore(124);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.19;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.03;

	  Cuba = ConvCubOperScore(125);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.83;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.43;

	  Cuba = ConvCubOperScore(126);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.04;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.14;

	  Cuba = ConvCubOperScore(127);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.08;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.29;

	  Cuba = ConvCubOperScore(128);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.68;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.42;

	  Cuba = ConvCubOperScore(129);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.5;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.25;

	  Cuba = ConvCubOperScore(130);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.62;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.07;

	  Cuba = ConvCubOperScore(131);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 1.29;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 1.29;

	  Cuba = ConvCubOperScore(132);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.90;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.77;

	  Cuba = ConvCubOperScore(133);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.84;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.96;

	  Cuba = ConvCubOperScore(134);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.91;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.07;

	  Cuba = ConvCubOperScore(135);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 2.53;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.11;

	  Cuba = ConvCubOperScore(136);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.0;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.68;

	  Cuba = ConvCubOperScore(137);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.87;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.63;

	  Cuba = ConvCubOperScore(138);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.08;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.09;

	  Cuba = ConvCubOperScore(139);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.52;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.49;

	  Cuba = ConvCubOperScore(140);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.49;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.82;

	  Cuba = ConvCubOperScore(141);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.24;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.69;

	  Cuba = ConvCubOperScore(142);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.29;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.06;

	  Cuba = ConvCubOperScore(143);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.61;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.48;

	  Cuba = ConvCubOperScore(144);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.03;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.89;

	  Cuba = ConvCubOperScore(145);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.15;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.27;

	  Cuba = ConvCubOperScore(146);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.35;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.19;

	  Cuba = ConvCubOperScore(147);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.96;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.30;

	  Cuba = ConvCubOperScore(148);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.92;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.27;

	  Cuba = ConvCubOperScore(149);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.57;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.52;

	  Cuba = ConvCubOperScore(150);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.3;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.0;

	  Cuba = ConvCubOperScore(151);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.90;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.1;

	  Cuba = ConvCubOperScore(152);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.36;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.12;

	  Cuba = ConvCubOperScore(153);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.22;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.5;

	  Cuba = ConvCubOperScore(154);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.73;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.49;

	  Cuba = ConvCubOperScore(155);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.1;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.15;

	  Cuba = ConvCubOperScore(156);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.59;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.31;

	  Cuba = ConvCubOperScore(157);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.88;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.19;

	  Cuba = ConvCubOperScore(158);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.88;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.83;

	  Cuba = ConvCubOperScore(159);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.09;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 5.76;

	  Cuba = ConvCubOperScore(160);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.15;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.0;

	  Cuba = ConvCubOperScore(161);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.99;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.47;

	  Cuba = ConvCubOperScore(162);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.25;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.96;

	  Cuba = ConvCubOperScore(163);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.33;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.55;

	  Cuba = ConvCubOperScore(164);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.02;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.03;

	  Cuba = ConvCubOperScore(165);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.85;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.21;

	  Cuba = ConvCubOperScore(166);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.09;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.0;

	  Cuba = ConvCubOperScore(167);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.82;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.70;

	  Cuba = ConvCubOperScore(168);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.08;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.38;

	  Cuba = ConvCubOperScore(169);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.05;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.23;

	  Cuba = ConvCubOperScore(170);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.0;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.1;

	  Cuba = ConvCubOperScore(171);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.02;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.48;

	  Cuba = ConvCubOperScore(172);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.07;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.41;

	  Cuba = ConvCubOperScore(173);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.84;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.22;

	  Cuba = ConvCubOperScore(174);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.35;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.13;

	  Cuba = ConvCubOperScore(175);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.9;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.09;

	  Cuba = ConvCubOperScore(176);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.3;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.3;

	  Cuba = ConvCubOperScore(177);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.27;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.0;

	  Cuba = ConvCubOperScore(178);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.78;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.28;

	  Cuba = ConvCubOperScore(179);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.7;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.37;

	  Cuba = ConvCubOperScore(180);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.32;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.23;

	  Cuba = ConvCubOperScore(181);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.26;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.96;

	  Cuba = ConvCubOperScore(182);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.67;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.75;

	  Cuba = ConvCubOperScore(183);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.4;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.92;

	  Cuba = ConvCubOperScore(184);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.69;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.57;

	  Cuba = ConvCubOperScore(185);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.98;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.4;

	  Cuba = ConvCubOperScore(186);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.97;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.3;

	  Cuba = ConvCubOperScore(187);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.31;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.07;

	  Cuba = ConvCubOperScore(188);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.9;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.27;

	  Cuba = ConvCubOperScore(201);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.79;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.22;

	  Cuba = ConvCubOperScore(202);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.71;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.99;

	  Cuba = ConvCubOperScore(203);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.37;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.35;

	  Cuba = ConvCubOperScore(204);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.31;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.8;

	  Cuba = ConvCubOperScore(205);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.17;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.43;

	  Cuba = ConvCubOperScore(206);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.04;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.16;

	  Cuba = ConvCubOperScore(207);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.51;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.9;

	  Cuba = ConvCubOperScore(208);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 1.88;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.37;

	  Cuba = ConvCubOperScore(209);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.92;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.99;

	  Cuba = ConvCubOperScore(210);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.27;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.28;

	  Cuba = ConvCubOperScore(211);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.9;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.3;

	  Cuba = ConvCubOperScore(212);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.32;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.87;

	  Cuba = ConvCubOperScore(213);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.63;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.65;

	  Cuba = ConvCubOperScore(214);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.85;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.29;

	  Cuba = ConvCubOperScore(215);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.17;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.99;

	  Cuba = ConvCubOperScore(216);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.12;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.09;

	  Cuba = ConvCubOperScore(217);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.56;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.19;

	  Cuba = ConvCubOperScore(218);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.24;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.3;

	  Cuba = ConvCubOperScore(219);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.22;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.22;

	  Cuba = ConvCubOperScore(220);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.59;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.49;

	  Cuba = ConvCubOperScore(221);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.35;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.27;

	  Cuba = ConvCubOperScore(222);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.96;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.64;

	  Cuba = ConvCubOperScore(223);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.43;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.27;

	  Cuba = ConvCubOperScore(224);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.14;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.97;

	  Cuba = ConvCubOperScore(225);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.21;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.28;

	  Cuba = ConvCubOperScore(226);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 2.0 - 1.28;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 2.0 - 1.04;

	  Cuba = ConvCubOperScore(227);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.89;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.87;

	  Cuba = ConvCubOperScore(228);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.28;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.03;

	  Cuba = ConvCubOperScore(229);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.88;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.07;

	  Cuba = ConvCubOperScore(230);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.1;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.13;

	  Cuba = ConvCubOperScore(231);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 5.01;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.24;

	  Cuba = ConvCubOperScore(232);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.02;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.91;

	  Cuba = ConvCubOperScore(233);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.94;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.23;

	  Cuba = ConvCubOperScore(234);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.29;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.65;

	  Cuba = ConvCubOperScore(235);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.1;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.19;

	  Cuba = ConvCubOperScore(236);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.32;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.03;

	  Cuba = ConvCubOperScore(237);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.3;

	  Cuba = ConvCubOperScore(238);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.43;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.46;

	  Cuba = ConvCubOperScore(239);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.7;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 1.6;

	  Cuba = ConvCubOperScore(240);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.22;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.77;

	  Cuba = ConvCubOperScore(241);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.17;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.34;

	  Cuba = ConvCubOperScore(242);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 2.0 - 1.77;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 2.0 - 1.99;

	  Cuba = ConvCubOperScore(243);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.69;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 5.37;

	  Cuba = ConvCubOperScore(244);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.06;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.96;

	  Cuba = ConvCubOperScore(245);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.13;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 5.44;

	  Cuba = ConvCubOperScore(246);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.19;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.17;

	  Cuba = ConvCubOperScore(247);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.68;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.17;

	  Cuba = ConvCubOperScore(248);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.31;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.35;

	  Cuba = ConvCubOperScore(249);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.16;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.0;

	  Cuba = ConvCubOperScore(250);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.27;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.99;

	  Cuba = ConvCubOperScore(251);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.72;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.10;

	  Cuba = ConvCubOperScore(252);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.19;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.17;

	  Cuba = ConvCubOperScore(253);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.49;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.93;

	  Cuba = ConvCubOperScore(254);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.91;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.51;

	  Cuba = ConvCubOperScore(255);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.07;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.87;

	  Cuba = ConvCubOperScore(256);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.78;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.36;

	  Cuba = ConvCubOperScore(257);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.97;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.72;

	  Cuba = ConvCubOperScore(258);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.96;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.74;

	  Cuba = ConvCubOperScore(259);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0;

	  Cuba = ConvCubOperScore(260);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.03;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.02;

	  Cuba = ConvCubOperScore(261);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.15;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.8;

	  Cuba = ConvCubOperScore(262);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.36;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.4;

	  Cuba = ConvCubOperScore(263);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 2.0 - 1.39;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 2.0 - 1.35;

	  Cuba = ConvCubOperScore(264);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.27;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.17;

	  Cuba = ConvCubOperScore(265);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.04;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.97;

	  Cuba = ConvCubOperScore(266);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 2.0 - 1.4;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 2.0 - 1.79;

	  Cuba = ConvCubOperScore(267);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.32;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.22;

	  Cuba = ConvCubOperScore(268);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.08;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.99;

	  Cuba = ConvCubOperScore(269);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.33;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 5.24;

	  Cuba = ConvCubOperScore(270);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.77;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.47;

	  Cuba = ConvCubOperScore(271);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.5;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.49;

	  Cuba = ConvCubOperScore(272);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.06;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.69;

	  Cuba = ConvCubOperScore(273);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.23;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.08;

	  Cuba = ConvCubOperScore(274);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.74;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.16;

	  Cuba = ConvCubOperScore(275);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.98;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.57;

	  Cuba = ConvCubOperScore(276);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.79;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.07;

	  Cuba = ConvCubOperScore(277);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 3.98;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 3.26;

	  Cuba = ConvCubOperScore(278);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.48;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.49;

	  Cuba = ConvCubOperScore(279);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.39;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.79;

	  Cuba = ConvCubOperScore(280);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.22;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.71;

	  Cuba = ConvCubOperScore(281);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.59;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.9;

	  Cuba = ConvCubOperScore(282);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.79;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.29;

	  Cuba = ConvCubOperScore(283);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 5.16;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.18;

	  Cuba = ConvCubOperScore(284);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.56;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.17;

	  Cuba = ConvCubOperScore(285);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.04;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.05;

	  Cuba = ConvCubOperScore(286);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.09;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.67;

	  Cuba = ConvCubOperScore(287);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 4.79;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 4.19;

	  Cuba = ConvCubOperScore(288);
	  AVC.ParUser1[Cuba].dur_nulo_move_cima = 6.0 - 2.69;
	  AVC.ParUser1[Cuba].dur_nulo_move_baixo = 6.0 - 2.40;
	  for (CubaOpe=101; CubaOpe<=288; CubaOpe++)
	  {
		Cuba = ConvCubOperScore(CubaOpe);
		AVC.ParUser1[Cuba].min_move_cima = AVC.ParUser1[Cuba].dur_nulo_move_cima;
		AVC.ParUser1[Cuba].min_move_baixo = AVC.ParUser1[Cuba].dur_nulo_move_baixo;
	  }

	  Cuba = ConvCubOperScore(181);
	  EST_AVC(Cuba).Est.alarme_aek = FALSO;
*/


/* VALIDADE  ************************************************************

	Cuba = ConvCubOperScore(101);
	AVC.User4[Cuba].carcaca = 142;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 3;

	Cuba = ConvCubOperScore(102);
	AVC.User4[Cuba].carcaca = 210;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(103);
	AVC.User4[Cuba].carcaca = 249;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(104);
	AVC.User4[Cuba].carcaca = 151;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(105);
	AVC.User4[Cuba].carcaca = 109;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(106);
	AVC.User4[Cuba].carcaca = 138;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(107);
	AVC.User4[Cuba].carcaca = 262;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(108);
	AVC.User4[Cuba].carcaca = 279;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(109);
	AVC.User4[Cuba].carcaca = 208;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(110);
	AVC.User4[Cuba].carcaca = 132;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(111);
	AVC.User4[Cuba].carcaca = 217;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(112);
	AVC.User4[Cuba].carcaca = 250;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(113);
	AVC.User4[Cuba].carcaca = 219;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(114);
	AVC.User4[Cuba].carcaca = 5;
	AVC.User4[Cuba].geracao = 1;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(115);
	AVC.User4[Cuba].carcaca = 212;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(116);
	AVC.User4[Cuba].carcaca = 157;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(117);
	AVC.User4[Cuba].carcaca = 267;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(118);
	AVC.User4[Cuba].carcaca = 176;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(119);
	AVC.User4[Cuba].carcaca = 237;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(120);
	AVC.User4[Cuba].carcaca = 150;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(121);
	AVC.User4[Cuba].carcaca = 173;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(122);
	AVC.User4[Cuba].carcaca = 163;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(123);
	AVC.User4[Cuba].carcaca = 186;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(166);
	AVC.User4[Cuba].carcaca = 214;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(167);
	AVC.User4[Cuba].carcaca = 156;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(168);
	AVC.User4[Cuba].carcaca = 274;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(169);
	AVC.User4[Cuba].carcaca = 104;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(170);
	AVC.User4[Cuba].carcaca = 247;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(171);
	AVC.User4[Cuba].carcaca = 234;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(172);
	AVC.User4[Cuba].carcaca = 6;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(173);
	AVC.User4[Cuba].carcaca = 164;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(174);
	AVC.User4[Cuba].carcaca = 204;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(175);
	AVC.User4[Cuba].carcaca = 154;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(176);
	AVC.User4[Cuba].carcaca = 232;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(177);
	AVC.User4[Cuba].carcaca = 128;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(178);
	AVC.User4[Cuba].carcaca = 272;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(179);
	AVC.User4[Cuba].carcaca = 233;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(180);
	AVC.User4[Cuba].carcaca = 148;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(181);
	AVC.User4[Cuba].carcaca = 118;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 4;

	Cuba = ConvCubOperScore(182);
	AVC.User4[Cuba].carcaca = 126;
	AVC.User4[Cuba].geracao = 7;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(183);
	AVC.User4[Cuba].carcaca = 117;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(184);
	AVC.User4[Cuba].carcaca = 168;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(185);
	AVC.User4[Cuba].carcaca = 273;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(186);
	AVC.User4[Cuba].carcaca = 183;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(187);
	AVC.User4[Cuba].carcaca = 106;
	AVC.User4[Cuba].geracao = 7;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(188);
	AVC.User4[Cuba].carcaca = 169;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(124);
	AVC.User4[Cuba].carcaca = 240;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(125);
	AVC.User4[Cuba].carcaca = 158;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 3;

	Cuba = ConvCubOperScore(126);
	AVC.User4[Cuba].carcaca = 283;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(127);
	AVC.User4[Cuba].carcaca = 172;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(128);
	AVC.User4[Cuba].carcaca = 114;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(129);
	AVC.User4[Cuba].carcaca = 275;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(130);
	AVC.User4[Cuba].carcaca = 261;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(131);
	AVC.User4[Cuba].carcaca = 111;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(132);
	AVC.User4[Cuba].carcaca = 264;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(133);
	AVC.User4[Cuba].carcaca = 257;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(134);
	AVC.User4[Cuba].carcaca = 259;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(135);
	AVC.User4[Cuba].carcaca = 241;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(136);
	AVC.User4[Cuba].carcaca = 235;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(137);
	AVC.User4[Cuba].carcaca = 221;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 4;

	Cuba = ConvCubOperScore(138);
	AVC.User4[Cuba].carcaca = 260;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(139);
	AVC.User4[Cuba].carcaca = 287;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(140);
	AVC.User4[Cuba].carcaca = 152;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(141);
	AVC.User4[Cuba].carcaca = 253;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 4;

	Cuba = ConvCubOperScore(142);
	AVC.User4[Cuba].carcaca = 266;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 3;

	Cuba = ConvCubOperScore(143);
	AVC.User4[Cuba].carcaca = 231;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 3;

	Cuba = ConvCubOperScore(144);
	AVC.User4[Cuba].carcaca = 223;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 4;

	Cuba = ConvCubOperScore(145);
	AVC.User4[Cuba].carcaca = 254;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(146);
	AVC.User4[Cuba].carcaca = 139;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 4;

	Cuba = ConvCubOperScore(147);
	AVC.User4[Cuba].carcaca = 149;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(148);
	AVC.User4[Cuba].carcaca = 211;
	AVC.User4[Cuba].geracao = 7;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(149);
	AVC.User4[Cuba].carcaca = 140;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(150);
	AVC.User4[Cuba].carcaca = 181;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(151);
	AVC.User4[Cuba].carcaca = 215;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(152);
	AVC.User4[Cuba].carcaca = 218;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(153);
	AVC.User4[Cuba].carcaca = 119;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(154);
	AVC.User4[Cuba].carcaca = 216;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(155);
	AVC.User4[Cuba].carcaca = 276;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(156);
	AVC.User4[Cuba].carcaca = 144;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(157);
	AVC.User4[Cuba].carcaca = 185;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(158);
	AVC.User4[Cuba].carcaca = 107;
	AVC.User4[Cuba].geracao = 7;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(159);
	AVC.User4[Cuba].carcaca = 131;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(160);
	AVC.User4[Cuba].carcaca = 282;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(161);
	AVC.User4[Cuba].carcaca = 179;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(162);
	AVC.User4[Cuba].carcaca = 171;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(163);
	AVC.User4[Cuba].carcaca = 256;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(164);
	AVC.User4[Cuba].carcaca = 136;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(165);
	AVC.User4[Cuba].carcaca = 206;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(201);
	AVC.User4[Cuba].carcaca = 178;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(202);
	AVC.User4[Cuba].carcaca = 162;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 4;

	Cuba = ConvCubOperScore(203);
	AVC.User4[Cuba].carcaca = 113;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(204);
	AVC.User4[Cuba].carcaca = 220;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(205);
	AVC.User4[Cuba].carcaca = 165;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(206);
	AVC.User4[Cuba].carcaca = 265;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 5;

	Cuba = ConvCubOperScore(207);
	AVC.User4[Cuba].carcaca = 115;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(208);
	AVC.User4[Cuba].carcaca = ;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(209);
	AVC.User4[Cuba].carcaca = 278;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(210);
	AVC.User4[Cuba].carcaca = 166;
	AVC.User4[Cuba].geracao = 8;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(211);
	AVC.User4[Cuba].carcaca = 170;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(212);
	AVC.User4[Cuba].carcaca = 108;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(213);
	AVC.User4[Cuba].carcaca = 227;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(214);
	AVC.User4[Cuba].carcaca = 143;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(215);
	AVC.User4[Cuba].carcaca = 145;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(216);
	AVC.User4[Cuba].carcaca = 269;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(217);
	AVC.User4[Cuba].carcaca = 175;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(218);
	AVC.User4[Cuba].carcaca = 226;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(219);
	AVC.User4[Cuba].carcaca = 244;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(220);
	AVC.User4[Cuba].carcaca = 153;
	AVC.User4[Cuba].geracao = 7;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(221);
	AVC.User4[Cuba].carcaca = 116;
	AVC.User4[Cuba].geracao = 7;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(222);
	AVC.User4[Cuba].carcaca = 160;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(223);
	AVC.User4[Cuba].carcaca = 141;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(266);
	AVC.User4[Cuba].carcaca = 120;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 4;

	Cuba = ConvCubOperScore(267);
	AVC.User4[Cuba].carcaca = 242;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 4;

	Cuba = ConvCubOperScore(268);
	AVC.User4[Cuba].carcaca = 122;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(269);
	AVC.User4[Cuba].carcaca = 245;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(270);
	AVC.User4[Cuba].carcaca = 8;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(271);
	AVC.User4[Cuba].carcaca = 229;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 4;

	Cuba = ConvCubOperScore(272);
	AVC.User4[Cuba].carcaca = 134
	AVC.User4[Cuba].geracao = 7;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(273);
	AVC.User4[Cuba].carcaca = 209;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(274);
	AVC.User4[Cuba].carcaca = 263;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(275);
	AVC.User4[Cuba].carcaca = 258;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(276);
	AVC.User4[Cuba].carcaca = 127;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(277);
	AVC.User4[Cuba].carcaca = 228;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(278);
	AVC.User4[Cuba].carcaca = 224;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(279);
	AVC.User4[Cuba].carcaca = 124;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(280);
	AVC.User4[Cuba].carcaca = 252;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(281);
	AVC.User4[Cuba].carcaca = 161;
	AVC.User4[Cuba].geracao = 7;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(282);
	AVC.User4[Cuba].carcaca = 248;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(283);
	AVC.User4[Cuba].carcaca = 159;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 5;

	Cuba = ConvCubOperScore(284);
	AVC.User4[Cuba].carcaca = 222;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(285);
	AVC.User4[Cuba].carcaca = 102;
	AVC.User4[Cuba].geracao = 7;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(286);
	AVC.User4[Cuba].carcaca = 213;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 3;

	Cuba = ConvCubOperScore(287);
	AVC.User4[Cuba].carcaca = 103;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(288);
	AVC.User4[Cuba].carcaca = 243;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(224);
	AVC.User4[Cuba].carcaca = 105;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(225);
	AVC.User4[Cuba].carcaca = 205;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(226);
	AVC.User4[Cuba].carcaca = 184;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(227);
	AVC.User4[Cuba].carcaca = 203;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 3;

	Cuba = ConvCubOperScore(228);
	AVC.User4[Cuba].carcaca = 277;
	AVC.User4[Cuba].geracao = 7;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(229);
	AVC.User4[Cuba].carcaca = 4;
	AVC.User4[Cuba].geracao = 2;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(230);
	AVC.User4[Cuba].carcaca = 155;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 0;

	Cuba = ConvCubOperScore(231);
	AVC.User4[Cuba].carcaca = 177;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(232);
	AVC.User4[Cuba].carcaca = 286;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(233);
	AVC.User4[Cuba].carcaca = 147;
	AVC.User4[Cuba].geracao = 7;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(234);
	AVC.User4[Cuba].carcaca = 255;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(235);
	AVC.User4[Cuba].carcaca = 284;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(236);
	AVC.User4[Cuba].carcaca = 121;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(237);
	AVC.User4[Cuba].carcaca = 246;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(238);
	AVC.User4[Cuba].carcaca = 239;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(239);
	AVC.User4[Cuba].carcaca = 230;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(240);
	AVC.User4[Cuba].carcaca = 146;
	AVC.User4[Cuba].geracao = 7;
	AVC.User4[Cuba].fase_remendo = 3;

	Cuba = ConvCubOperScore(241);
	AVC.User4[Cuba].carcaca = 133;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(242);
	AVC.User4[Cuba].carcaca = 207;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(243);
	AVC.User4[Cuba].carcaca = 270;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(244);
	AVC.User4[Cuba].carcaca = 285;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(245);
	AVC.User4[Cuba].carcaca = 280;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(246);
	AVC.User4[Cuba].carcaca = 101;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(247);
	AVC.User4[Cuba].carcaca = 202;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(248);
	AVC.User4[Cuba].carcaca = 201;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 4;

	Cuba = ConvCubOperScore(249);
	AVC.User4[Cuba].carcaca = 110;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(250);
	AVC.User4[Cuba].carcaca = 180;
	AVC.User4[Cuba].geracao = 4;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(251);
	AVC.User4[Cuba].carcaca = 271;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(252);
	AVC.User4[Cuba].carcaca = 218;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(253);
	AVC.User4[Cuba].carcaca = 187;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(254);
	AVC.User4[Cuba].carcaca = 3;
	AVC.User4[Cuba].geracao = 2;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(255);
	AVC.User4[Cuba].carcaca = 129;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 3;

	Cuba = ConvCubOperScore(256);
	AVC.User4[Cuba].carcaca = 251;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(257);
	AVC.User4[Cuba].carcaca = 288;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(258);
	AVC.User4[Cuba].carcaca = 112;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(259);
	AVC.User4[Cuba].carcaca = 188;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(260);
	AVC.User4[Cuba].carcaca = 174;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(261);
	AVC.User4[Cuba].carcaca = 225;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 2;

	Cuba = ConvCubOperScore(262);
	AVC.User4[Cuba].carcaca = 123;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 1;

	Cuba = ConvCubOperScore(263);
	AVC.User4[Cuba].carcaca = 125;
	AVC.User4[Cuba].geracao = 6;
	AVC.User4[Cuba].fase_remendo = 3;

	Cuba = ConvCubOperScore(264);
	AVC.User4[Cuba].carcaca = 268;
	AVC.User4[Cuba].geracao = 5;
	AVC.User4[Cuba].fase_remendo = 4;

	Cuba = ConvCubOperScore(265);
	AVC.User4[Cuba].carcaca = 7;
	AVC.User4[Cuba].geracao = 1;
	AVC.User4[Cuba].fase_remendo = 0;
	  Cuba = ConvCubOperScore(234);
	  AVC.User4[Cuba].num_queb = 1;
	  AVC.User1[Cuba].ciclo_alumina = 0;

for (i=0; i<3; i++)
{
	  AVC.User1[Cuba].ciclo_alumina =
										AVC.User1[Cuba].ciclo_alumina << 1;

	  AVC.User1[Cuba].ciclo_alumina |= 1;
	  AVC.User4[Cuba].num_queb ++;
}
	  AVC.User1[Cuba].ciclo_alumina = 
									AVC.User1[Cuba].ciclo_alumina << 1;
	  AVC.User4[Cuba].num_queb ++;

	  AVC.User1[Cuba].ciclo_alumina =
									AVC.User1[Cuba].ciclo_alumina << 1;

	  AVC.User1[Cuba].ciclo_alumina |= 1;
	  AVC.User4[Cuba].num_queb ++;

	  AVC.User1[Cuba].ciclo_alumina = 
									AVC.User1[Cuba].ciclo_alumina << 1;
	  AVC.User4[Cuba].num_queb ++;
//
// CODIGO VALIDO
//
	  EST_AVC(Cuba).Est.forno_novo = FALSO;
	  AVC.User3[Cuba].hora_forno_rem = 1041273000;

	  Cuba = ConvCubOperScore(381);
	  AVC.User1[Cuba].tipo_forno_novo = NOVO;
	  EST_AVC(Cuba).Est.forno_rem =	FALSO;
	  EST_AVC(Cuba).Est.forno_novo = VERDADEIRO;
	  AVC.User1[Cuba].hora_forno_novo = 1039716000;
	  Cuba = ConvCubOperScore(309);
	  AVC.User1[Cuba].tipo_forno_novo = REMENDO;

	for( CubaOpe = 301; CubaOpe <= 304; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User4[Cuba].lim_queb_scb = 2*MIN*SEC + 40*SEC;
	}
	  Cuba = ConvCubOperScore(309);
  	  EST_AVC(Cuba).Est.forno_rem_local = FALSO;
	for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User4[Cuba].seq_normal[1] = 4095;
	  AVC.User4[Cuba].lim_queb_eq[2] = 5;
	  AVC.User4[Cuba].int_scb_ae[2] = 3*3600;
	  AVC.User4[Cuba].int_scb_ae[1] = 45*SEC;
	  AVC.User4[Cuba].lim_scb_qca  = 2*MIN*SEC + 40*SEC;
	  AVC.User3[Cuba].dur_inc_qca  = 2*MIN*SEC + 40*SEC;
	}
	for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User4[Cuba].lim_scb_qca  = 4*MIN*SEC;
	  AVC.User3[Cuba].dur_inc_qca  = 4*MIN*SEC;
	}
	  Cuba = ConvCubOperScore(373);
	  AVC.User4[Cuba].lim_scb_qca  = 5*MIN*SEC + 20*SEC;
	  AVC.User3[Cuba].dur_inc_qca  = 5*MIN*SEC + 20*SEC;

	  Cuba = ConvCubOperScore(383);
	  AVC.User4[Cuba].lim_scb_qca  = 5*MIN*SEC + 20*SEC;
	  AVC.User3[Cuba].dur_inc_qca  = 5*MIN*SEC + 20*SEC;
	for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User1[Cuba].salva_tipo_scb = 4;
	}
	  Cuba = ConvCubOperScore(278);
	  EST_AVC(Cuba).Est.efe_anod = FALSO;
	for( CubaOpe = 101; CubaOpe <= 288; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  for( i = 0; i <10; ++i )
	  {
		SUPERV_AVC(Cuba).Sup.RESERVA_DR_calob[i] = 0;
		SUPERV_AVC_TURNO(Cuba).Sup.RESERVA_DR_calob[i] = 0;
	  }
	}
	Cuba = ConvCubOperScore(204);
	EST_AVC(Cuba).Est.forno_rem = FALSO;
	EST_AVC(Cuba).Est.forno_anel = FALSO;
	EST_AVC(Cuba).Est.forno_novo = FALSO;
	EST_AVC(Cuba).Est.forno_partida = FALSO;
	EST_AVC(Cuba).Est.forno_limpeza = FALSO;
	EST_AVC(Cuba).Est.forno_rem_local = FALSO;

  for( CubaOpe = 301; CubaOpe <= 302 ; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
  }

  for( CubaOpe = 310; CubaOpe <= 312; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
  }

  for( CubaOpe = 388; CubaOpe <= 389; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
  }

  for( CubaOpe = 391; CubaOpe <= 394; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
  }
  for( CubaOpe = 313; CubaOpe <= 314; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
  }

  for( CubaOpe = 317; CubaOpe <= 320; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
  }

  for( CubaOpe = 322; CubaOpe <= 323; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
  }


  for( CubaOpe = 373; CubaOpe <= 374; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
  }
  for( CubaOpe = 379; CubaOpe <= 380; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
  }

  for( CubaOpe = 383; CubaOpe <= 384; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
  }

  for( CubaOpe = 406; CubaOpe <= 407; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
  }

  for( CubaOpe = 409; CubaOpe <= 411; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
  }
  for( CubaOpe = 486; CubaOpe <= 491; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
  }
  for( CubaOpe = 494; CubaOpe <= 496; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
  }

  for( CubaOpe = 413; CubaOpe <= 414; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
  }

  for( CubaOpe = 416; CubaOpe <= 420; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
  }

  for( CubaOpe = 422; CubaOpe <= 423; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
  }
  for( CubaOpe = 477; CubaOpe <= 480; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
  }
  for( CubaOpe = 482; CubaOpe <= 484; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
  }

 	Cuba = ConvCubOperScore(304);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
 	Cuba = ConvCubOperScore(307);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
 	Cuba = ConvCubOperScore(376);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
 	Cuba = ConvCubOperScore(475);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;

  for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 2*3600;
  }

 	Cuba = ConvCubOperScore(490);
	AVC.User4[Cuba].hora_queb_ref = 9*3600;
 	Cuba = ConvCubOperScore(496);
	AVC.User4[Cuba].hora_queb_ref = 9*3600;
  for( CubaOpe = 489; CubaOpe <= 496; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].hora_queb_ref = 9*3600;
  }
 	Cuba = ConvCubOperScore(377);
	AVC.User3[Cuba].tipo_forno_prob = NOVO;

 	Cuba = ConvCubOperScore(313);
	AVC.User3[Cuba].tipo_forno_prob = NOVO;
 	Cuba = ConvCubOperScore(321);
	AVC.User3[Cuba].tipo_forno_prob = NOVO;
 	Cuba = ConvCubOperScore(383);
	AVC.User3[Cuba].tipo_forno_prob = NOVO;
 	Cuba = ConvCubOperScore(401);
	AVC.User3[Cuba].tipo_forno_prob = NOVO;
 	Cuba = ConvCubOperScore(405);
	AVC.User3[Cuba].tipo_forno_prob = NOVO;
 	Cuba = ConvCubOperScore(476);
	AVC.User3[Cuba].tipo_forno_prob = NOVO;
 	Cuba = ConvCubOperScore(485);
	AVC.User3[Cuba].tipo_forno_prob = NOVO;

 	Cuba = ConvCubOperScore(491);
	AVC.User3[Cuba].tipo_forno_prob = REMENDO;
 	Cuba = ConvCubOperScore(384);
	AVC.User3[Cuba].tipo_forno_prob = REMENDO;
	AVC.User1[Cuba].hora_forno_novo = 885994200;

 	Cuba = ConvCubOperScore(384);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(323);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(320);
	EST_AVC(Cuba).Est.cozimento = FALSO;
 	Cuba = ConvCubOperScore(377);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(424);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(303);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(384);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(405);
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
 	Cuba = ConvCubOperScore(323);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(384);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(424);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(313);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(377);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_hour = 15;
	DataTm.tm_mday = 19;
	DataTm.tm_mon  = 10;
	DataTm.tm_year = 103;
	hora_qca = mktime(&DataTm); 
 	Cuba = ConvCubOperScore(267);
	AVC.User1[Cuba].tipo_forno_novo = NOVO;
	EST_AVC(Cuba).Est.forno_novo = VERDADEIRO;
	AVC.User1[Cuba].hora_forno_novo = hora_qca;

	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_hour = 15;
	DataTm.tm_mday = 21;
	DataTm.tm_mon  = 10;
	DataTm.tm_year = 103;
	hora_qca = mktime(&DataTm);
 	Cuba = ConvCubOperScore(257);
	AVC.User1[Cuba].tipo_forno_novo = NOVO;
	EST_AVC(Cuba).Est.forno_novo = VERDADEIRO;
	AVC.User1[Cuba].hora_forno_novo = hora_qca;

	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_hour = 15;
	DataTm.tm_mday = 24;
	DataTm.tm_mon  = 11;
	DataTm.tm_year = 103;
	hora_qca = mktime(&DataTm);
	Cuba = ConvCubOperScore(270);
	AVC.User1[Cuba].tipo_forno_novo = REMENDO;
    EST_AVC(Cuba).Est.forno_rem = VERDADEIRO;
    AVC.User3[Cuba].hora_forno_rem = hora_qca;
  for( CubaOpe = 401; CubaOpe <= 408; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].hora_queb_ref = 9*3600;
  }
 	Cuba = ConvCubOperScore(312);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(377);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(384);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(424);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(378);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_hour = 15;
	DataTm.tm_mday = 19;
	DataTm.tm_mon  = 8;
	DataTm.tm_year = 103;
	hora_qca = mktime(&DataTm); 
	AVC.User1[Cuba].hora_forno_novo = hora_qca;
	AVC.User3[Cuba].hora_forno_rem = hora_qca;
 	Cuba = ConvCubOperScore(313);
	AVC.User3[Cuba].tipo_forno_prob = NOVO;

	for( CubaOpe = 101; CubaOpe <= 288; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User4[Cuba].lim_queb_scb = 6*3600;
	}
 	Cuba = ConvCubOperScore(323);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(384);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(424);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(412);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
 	Cuba = ConvCubOperScore(412);
	EST_AVC(Cuba).Est.previsao_manual = FALSO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
 	Cuba = ConvCubOperScore(424);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(378);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_hour = 17;
	DataTm.tm_mday = 15;
	DataTm.tm_mon  = 02;
	DataTm.tm_year = 104;
 	Cuba = ConvCubOperScore(401);
	AVC.User3[Cuba].hora_faz_banho = mktime(&DataTm);
  for( CubaOpe = 401; CubaOpe <= 406; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].hora_queb_ref = 9*3600 + 20*60;
  }
  for( CubaOpe = 489; CubaOpe <= 494; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].hora_queb_ref = 9*3600 + 20*60;
  }
 	Cuba = ConvCubOperScore(322);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
 	Cuba = ConvCubOperScore(384);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
 	Cuba = ConvCubOperScore(316);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
	EST_AVC(Cuba).Est.ev_excecao = FALSO;
 	Cuba = ConvCubOperScore(378);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(307);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(310);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(424);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(376);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(324);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(374);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(402);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(317);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(380);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(382);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(474);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(482);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(487);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(305);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(316);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(414);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;
 	Cuba = ConvCubOperScore(473);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User1[Cuba].tipo_forno_novo = FNORMAL;

 	Cuba = ConvCubOperScore(308);
	AVC.User3[Cuba].ten_inc_sigs2h = 0;
 	Cuba = ConvCubOperScore(309);
	AVC.User3[Cuba].ten_inc_sigs2h = 0;
 	Cuba = ConvCubOperScore(324);
	AVC.User3[Cuba].ten_inc_sigs2h = 0;
 	Cuba = ConvCubOperScore(386);
	AVC.User3[Cuba].ten_inc_sigs2h = 0;
 	Cuba = ConvCubOperScore(392);
	AVC.User3[Cuba].ten_inc_sigs2h = 0;
 	Cuba = ConvCubOperScore(396);
	AVC.User3[Cuba].ten_inc_sigs2h = 0;
 	Cuba = ConvCubOperScore(402);
	AVC.User3[Cuba].ten_inc_sigs2h = 0;
 	Cuba = ConvCubOperScore(409);
	AVC.User3[Cuba].ten_inc_sigs2h = 0;
 	Cuba = ConvCubOperScore(416);
	AVC.User3[Cuba].ten_inc_sigs2h = 0;
 	Cuba = ConvCubOperScore(481);
	AVC.User3[Cuba].ten_inc_sigs2h = 0;
 	Cuba = ConvCubOperScore(486);
	AVC.User3[Cuba].ten_inc_sigs2h = 0;
  for( CubaOpe = 407; CubaOpe <= 408; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].hora_queb_ref = 9*3600 + 20*60;
  }
  for( CubaOpe = 495; CubaOpe <= 496; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].hora_queb_ref = 9*3600 + 20*60;
  }

 	Cuba = ConvCubOperScore(304);
	AVC.User3[Cuba].ten_inc_sigs2h = 0.10;
 	Cuba = ConvCubOperScore(310);
	AVC.User3[Cuba].ten_inc_sigs2h = 0.10;
 	Cuba = ConvCubOperScore(314);
	AVC.User3[Cuba].ten_inc_sigs2h = 0.10;
 	Cuba = ConvCubOperScore(321);
	AVC.User3[Cuba].ten_inc_sigs2h = 0.10;
 	Cuba = ConvCubOperScore(390);
	AVC.User3[Cuba].ten_inc_sigs2h = 0.10;
 	Cuba = ConvCubOperScore(392);
	AVC.User3[Cuba].ten_inc_sigs2h = 0.10;
 	Cuba = ConvCubOperScore(485);
	AVC.User3[Cuba].ten_inc_sigs2h = 0.10;
 	Cuba = ConvCubOperScore(308);
	AVC.User3[Cuba].ten_inc_sigs2h = 0.025;
 	Cuba = ConvCubOperScore(315);
	AVC.User3[Cuba].ten_inc_sigs2h = 0.05;
 	Cuba = ConvCubOperScore(486);
	AVC.User3[Cuba].ten_inc_sigs2h = 0.05;
 	Cuba = ConvCubOperScore(488);
	AVC.User3[Cuba].ten_inc_sigs2h = 0.05;
 	Cuba = ConvCubOperScore(309);
	AVC.User3[Cuba].ten_inc_sigs2h = 0.075;
 	Cuba = ConvCubOperScore(476);
	AVC.User3[Cuba].ten_inc_sigs2h = 0.025;

  for( CubaOpe = 266; CubaOpe <= 271; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
    AVC.User4[Cuba].lim_reslop1 = 0.030e-6;
    AVC.User4[Cuba].lim_reslop2 = 0.040e-6;
    AVC.User4[Cuba].lim_resinc1 = 0.07e-6;
  }
	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_sec  = 0;
	DataTm.tm_min  = 0;
	DataTm.tm_hour = 0;
	DataTm.tm_mday = 31;
	DataTm.tm_mon  = 11;
	DataTm.tm_year = 201;
	hora_qca = mktime(&DataTm); 

  for( CubaOpe = 101; CubaOpe <= 288; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User1[Cuba].hora_filres = hora_qca; 
  }

  for( CubaOpe = 389; CubaOpe <= 396; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 2*3600;
  }
  for( CubaOpe = 489; CubaOpe <= 496; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 2*3600;
  }

  for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	EST_AVC(Cuba).Est.Ea_redefinido = FALSO;
  }

  Cuba = ConvCubOperScore(268);
  AVC.User1[Cuba].eqmotor_up = 0.30e-6;

  Cuba = ConvCubOperScore(274);
  AVC.User1[Cuba].eqmotor_up = 0.80e-6;
  AVC.User1[Cuba].eqmotor_down = 0.80e-6;
  Cuba = ConvCubOperScore(273);
  AVC.User1[Cuba].eqmotor_up = 0.80e-6;
  AVC.User1[Cuba].eqmotor_down = 0.80e-6;
  Cuba = ConvCubOperScore(216);
  AVC.User1[Cuba].eqmotor_up = 0.80e-6;
	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_sec  = 0;
	DataTm.tm_min  = 0;
	DataTm.tm_hour = 0;
	DataTm.tm_mday = 31;
	DataTm.tm_mon  = 11;
	DataTm.tm_year = 95;
	hora_qca = mktime(&DataTm); 

  for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	EST_AVC(Cuba).Est.opera_forno = FALSO;
	AVC.User1[Cuba].hora_opera_forno = hora_qca;
  }

  Cuba = ConvCubOperScore(274);
  AVC.User1[Cuba].eqmotor_up = 0.20e-6;
  AVC.User1[Cuba].eqmotor_down = 0.28e-6;
  Cuba = ConvCubOperScore(273);
  AVC.User1[Cuba].eqmotor_up = 0.20e-6;
  Cuba = ConvCubOperScore(273);
  AVC.User1[Cuba].eqmotor_down = 0.30e-6;

	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_sec  = 0;
	DataTm.tm_min  = 48;
	DataTm.tm_hour = 16;
	DataTm.tm_mday = 25;
	DataTm.tm_mon  = 11;
	DataTm.tm_year = 104;
	hora_qca = mktime(&DataTm); 
  Cuba = ConvCubOperScore(324);
  AVC.User1[Cuba].hora_ini_ae = hora_qca;
  AVC.User1[Cuba].hora_fim_ae = hora_qca + 120;
  Cuba = ConvCubOperScore(232);
  AVC.User1[Cuba].motivo_aek_off = 4;

  for( CubaOpe = 301; CubaOpe <= 308; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
  }

  for( CubaOpe = 389; CubaOpe <= 396; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 3*3600;
  }

  for( CubaOpe = 317; CubaOpe <= 324; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 4*3600;
  }

  for( CubaOpe = 373; CubaOpe <= 380; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 4*3600;
  }
 	Cuba = ConvCubOperScore(384);
	EST_AVC(Cuba).Est.ev_espera = FALSO;
	EST_AVC(Cuba).Est.ev_excecao = FALSO;
  for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_pcb_pcb = 8*3600;
  }

	Cuba = ConvCubOperScore(403);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_sec  = 0;
	DataTm.tm_min  = 0;
	DataTm.tm_hour = 0;
	DataTm.tm_mday = 1;
	DataTm.tm_mon  = 0;
	DataTm.tm_year = 101;
	hora_qca = mktime(&DataTm);
	AVC.User1[Cuba].hora_forno_novo = hora_qca;

  for( CubaOpe = 101; CubaOpe <= 288; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	EST_AVC(Cuba).Est.porta_corredor = FALSO;
	EST_AVC(Cuba).Est.porta_janela = FALSO;
  }

	for( CubaOpe = 401; CubaOpe <= 496; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User4[Cuba].hora_queb_ref = 9*3600+20*SEC;
	}
	for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User4[Cuba].lim_pcb_pcb  = AVC.ParUser2[Cuba].lim_pcb;
	}

	  Cuba = ConvCubOperScore(303);
	  EST_AVC(Cuba).Est.previsao_lateral = FALSO;
	  Cuba = ConvCubOperScore(304);
	  EST_AVC(Cuba).Est.previsao_lateral = FALSO;
	  Cuba = ConvCubOperScore(375);
	  EST_AVC(Cuba).Est.previsao_lateral = FALSO;
	  Cuba = ConvCubOperScore(381);
	  EST_AVC(Cuba).Est.previsao_lateral = FALSO;
	  Cuba = ConvCubOperScore(377);
	  EST_AVC(Cuba).Est.previsao_lateral = FALSO;
	  Cuba = ConvCubOperScore(482);
	AVC.User3[Cuba].tipo_forno_prob = FRIO;
	  Cuba = ConvCubOperScore(495);
	AVC.User3[Cuba].tipo_forno_prob = FRIO;
	  Cuba = ConvCubOperScore(403);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	Cuba = ConvCubOperScore(318);
    AVC.ParUser1[Cuba].dur_pcb_ponta = 3;
	Cuba = ConvCubOperScore(314);
    AVC.ParUser1[Cuba].dur_pcb_ponta = 3;

  for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
  {
 Obs.: Alterar tambem no /score3.0/fontes/ope/alcan/OpeNewEaVS 29/12/05
 	Cuba = ConvCubOperScore(CubaOpe);
    AVC.User4[Cuba].lim_reslop1 = 0.0221e-6;
    AVC.User4[Cuba].lim_reslop2 = 0.0281e-6;
    AVC.User4[Cuba].lim_resinc1 = 0.861e-6;
    AVC.User4[Cuba].lim_resinc2 = 1.001e-6;
    AVC.User4[Cuba].lim_move_reslop1 = 0.0191e-6;
    AVC.User4[Cuba].lim_move_reslop2 = 0.0241e-6;
    AVC.User4[Cuba].lim_move_resinc1 = 0.651e-6;
    AVC.User4[Cuba].lim_move_resinc2 = 0.791e-6;
  }
 Alterar horario de quebrada, a pedido de Elias 
     Sala 300 - 00:40 e Sala 400 01:30 

  for( CubaOpe = 301; CubaOpe <= 396; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].hora_queb_ref = 8*3600+40*SEC;
  }
  for( CubaOpe = 401; CubaOpe <= 496; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].hora_queb_ref = 9*3600+30*SEC;
  }
 Alterei os valores de 1.35 e 1.21 p/ os abaixo, grafico c/ dentes 
 	Cuba = ConvCubOperScore(155);
	AVC.User1[Cuba].eqmotor_up = 1.95e-6;
	AVC.User1[Cuba].eqmotor_down = 1.81e-6;
 Alterei os valores de 1.41 e 2.00 p/ os abaixo, grafico c/ dentes 
 	Cuba = ConvCubOperScore(146);
	AVC.User1[Cuba].eqmotor_up = 1.95e-6;
	AVC.User1[Cuba].eqmotor_down = 2.5e-6;
	 Alterei os valores de 1.95 e 1.76 p/ os abaixo, grafico c/ dentes
 	Cuba = ConvCubOperScore(155);
	AVC.User1[Cuba].eqmotor_up = 1.95e-6;
	AVC.User1[Cuba].eqmotor_down = 1.76e-6;

 Efeito longo p/ HS a pedido de Druso - 25/07/06 
  for( CubaOpe = 101; CubaOpe <= 288; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_ae_longo = 9*SEC;
  }
	 Alterar horario de quebrada, a pedido de Rilson - 28/09/06/
     Sala 300 e Sala 400 - 01:20 

  for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].hora_queb_ref = 9*3600+20*SEC;
  }

     Normalizar dados do 496, a pedido de Rilson 
 	Cuba = ConvCubOperScore(496);
 	AVC.User1[Cuba].res_control = (AVC.ParUser1[Cuba].tensao_target - 
								   AVC.ParUser1[Cuba].ten_fem ) /
								   AVC.ParUser1[Cuba].cor_target_forno;

 	AVC.User1[Cuba].ten_control = AVC.ParUser1[Cuba].tensao_target;
  Zona da previsao e move iguais p/ todas as cubas, a pedido de Druso 10/10/06 
  for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
    AVC.User4[Cuba].lim_reslop1 = 0.0221e-6;
    AVC.User4[Cuba].lim_reslop2 = 0.0281e-6;
    AVC.User4[Cuba].lim_resinc1 = 0.861e-6;
    AVC.User4[Cuba].lim_resinc2 = 1.001e-6;
    AVC.User4[Cuba].lim_move_reslop1 = 0.0191e-6;
    AVC.User4[Cuba].lim_move_reslop2 = 0.0241e-6;
    AVC.User4[Cuba].lim_move_resinc1 = 0.651e-6;
    AVC.User4[Cuba].lim_move_resinc2 = 0.791e-6;
  }
   Zona da previsao e move iguais p/ todas as cubas, a pedido de Druso 13/10/06
  for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
    AVC.User4[Cuba].lim_reslop1 = 0.018e-6;
    AVC.User4[Cuba].lim_reslop2 = 0.0241e-6;
    AVC.User4[Cuba].lim_resinc1 = 0.861e-6;
    AVC.User4[Cuba].lim_resinc2 = 1.001e-6;
    AVC.User4[Cuba].lim_move_reslop1 = 0.0151e-6;
    AVC.User4[Cuba].lim_move_reslop2 = 0.0211e-6;
    AVC.User4[Cuba].lim_move_resinc1 = 0.651e-6;
    AVC.User4[Cuba].lim_move_resinc2 = 0.791e-6;
  }
   Habilitar forno 301, para AEPCB. Qdo foi desabilitado 	a log. de rank,
	estava com Rank 7. Pedido de Rilson, 26/10/06 
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	Cuba = ConvCubOperScore(480);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	Cuba = ConvCubOperScore(315);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	Cuba = ConvCubOperScore(319);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	Cuba = ConvCubOperScore(375);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	Cuba = ConvCubOperScore(382);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	Cuba = ConvCubOperScore(383);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	Cuba = ConvCubOperScore(390);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	Cuba = ConvCubOperScore(395);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	Cuba = ConvCubOperScore(403);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	Cuba = ConvCubOperScore(418);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	Cuba = ConvCubOperScore(420);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	Cuba = ConvCubOperScore(485);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

	Cuba = ConvCubOperScore(414);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
	AVC.User1[Cuba].hora_fim_ae = AVC.User1[Cuba].hora_ini_ae + 120;
  for( CubaOpe = 301; CubaOpe <= 306; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
  }
  for( CubaOpe = 308; CubaOpe <= 311; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
  }
  for( CubaOpe = 317; CubaOpe <= 320; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
  }
  for( CubaOpe = 322; CubaOpe <= 324; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
  }
  for( CubaOpe = 374; CubaOpe <= 376; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
  }
  for( CubaOpe = 382; CubaOpe <= 387; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
  }
  for( CubaOpe = 389; CubaOpe <= 394; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
  }
  for( CubaOpe = 396; CubaOpe <= 411; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
  }
  for( CubaOpe = 413; CubaOpe <= 417; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
  }
  for( CubaOpe = 419; CubaOpe <= 421; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
  }
  for( CubaOpe = 423; CubaOpe <= 474; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
  }
  for( CubaOpe = 478; CubaOpe <= 495; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
  }
	Cuba = ConvCubOperScore(313);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
	Cuba = ConvCubOperScore(315);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
	Cuba = ConvCubOperScore(378);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
	Cuba = ConvCubOperScore(380);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
	Cuba = ConvCubOperScore(476);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
	Cuba = ConvCubOperScore(322);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
	EST_AVC(Cuba).Est.ev_excecao = FALSO;
	Cuba = ConvCubOperScore(412);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
	EST_AVC(Cuba).Est.ev_excecao = FALSO;
	Cuba = ConvCubOperScore(418);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
	EST_AVC(Cuba).Est.ev_excecao = FALSO;
	Cuba = ConvCubOperScore(422);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
	EST_AVC(Cuba).Est.ev_excecao = FALSO;
	Cuba = ConvCubOperScore(477);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
	EST_AVC(Cuba).Est.ev_excecao = FALSO;
	Cuba = ConvCubOperScore(307);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
	EST_AVC(Cuba).Est.ev_espera = FALSO;
	EST_AVC(Cuba).Est.ev_excecao = FALSO;

  for( CubaOpe = 266; CubaOpe <= 277; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User1[Cuba].par1_rod = 0.571;
	AVC.User1[Cuba].par2_rod = 0.444;
	AVC.User1[Cuba].par3_rod = 0.388;
	AVC.User1[Cuba].par4_rod = 0.0765;
	AVC.User1[Cuba].hora_max_inc_const = 6;
  }

  Parametrizado tempo maximo da curva de levantamento - 08/12/06 
  for( CubaOpe = 101; CubaOpe <= 288; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	if (AVC.User1[Cuba].tipo_rodding eq BOOSTER_R3 or
		AVC.User1[Cuba].tipo_rodding eq CURVA_R3 or
		AVC.User1[Cuba].tipo_rodding eq BOOSTER_HS or
		AVC.User1[Cuba].tipo_rodding eq CURVA_HS)
	  AVC.User1[Cuba].dur_max_inc_lev = 180;
  }

	   Forno 144 com motor novo - 15/12/2006, a pedido de Geraldo Sossego 
	  Cuba = ConvCubOperScore(144);
	  AVC.User1[Cuba].eqmotor_down = 0.85e-6;
	  AVC.User1[Cuba].eqmotor_up = 0.85e-6;
 Nova logica de quebrada - a cada 4 horas, a pedido de Elias - 24/04/07 
  for( CubaOpe = 101; CubaOpe <= 288; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_queb_scb = 4*3600;
  }
A pedido de Rilson, 01/06/2007, 11:23:01h, na VS, foi alterada
	 tensao_minima de 4.10V p/ 4.15V 

  19/06/07 - a pedido de Generoso motor pequeno p/ grande 
  Cuba = ConvCubOperScore(259);
  AVC.User1[Cuba].eqmotor_up = 1.00e-6;
  AVC.User1[Cuba].eqmotor_down = 1.00e-6;

  Cuba = ConvCubOperScore(248);
  AVC.User1[Cuba].eqmotor_up = 1.00e-6;
  AVC.User1[Cuba].eqmotor_down = 1.00e-6;


  23/07/07 - a pedido de Joao Alberto, motor pequeno p/ grande 
  Cuba = ConvCubOperScore(181);
  AVC.User1[Cuba].eqmotor_up = 1.00e-6;
  AVC.User1[Cuba].eqmotor_down = 1.00e-6;

  08/08/07 - a pedido de Ildeu, extendido para linha a CURVA HS, exceto
fornos alongados e booster. Fornos 101-112, 114-143, 145, 147-149, 161-162,
164-179, 181-182, 184-186, 224-232, 234-247, 249-252, 254-257, 260-265 


  16/08/07 - a pedido de Geraldo Sossego (Joao Alberto), pedido para alterar a
  zona morta dos fornos 266 ao 288, para 500 mV, para corrente de 
  66500 KA (266 ao 277) e 62800 KA (278 ao 288)
    De:
    266 ao 271 - dead_band_inf = 1.0
    272 ao 288 - dead_band_inf = 1.2
    266 ao 288 - dead_band_sup = 1.2
    Para:
    266 ao 277 (booster) - dead_band_inf e dead_band_sup = 0.75
    278 ao 288           - dead_band_inf e dead_band_sup = 0.80


  31/08/07 - a pedido de Flavio, da Instrumentacao, (colocado durante
			 reuniao das 8h, ha HS) motor pequeno p/ grande 
  Cuba = ConvCubOperScore(282);
  AVC.User1[Cuba].eqmotor_up = 1.00e-6;
  AVC.User1[Cuba].eqmotor_down = 1.00e-6;
  Cuba = ConvCubOperScore(285);
  AVC.User1[Cuba].eqmotor_up = 1.00e-6;
  AVC.User1[Cuba].eqmotor_down = 1.00e-6;

	 dia 10/10/2007 
 	Cuba = ConvCubOperScore(314);
    AVC.User4[Cuba].lim_reslop1 = 0.018e-6;
    AVC.User4[Cuba].lim_reslop2 = 0.0241e-6;
    AVC.User4[Cuba].lim_resinc1 = 0.861e-6;
    AVC.User4[Cuba].lim_resinc2 = 1.001e-6;
    AVC.User4[Cuba].lim_move_reslop1 = 0.0151e-6;
    AVC.User4[Cuba].lim_move_reslop2 = 0.0211e-6;
    AVC.User4[Cuba].lim_move_resinc1 = 0.651e-6;
    AVC.User4[Cuba].lim_move_resinc2 = 0.791e-6;
 	Cuba = ConvCubOperScore(377);
    AVC.User4[Cuba].lim_reslop1 = 0.018e-6;
    AVC.User4[Cuba].lim_reslop2 = 0.0241e-6;
    AVC.User4[Cuba].lim_resinc1 = 0.861e-6;
    AVC.User4[Cuba].lim_resinc2 = 1.001e-6;
    AVC.User4[Cuba].lim_move_reslop1 = 0.0151e-6;
    AVC.User4[Cuba].lim_move_reslop2 = 0.0211e-6;
    AVC.User4[Cuba].lim_move_resinc1 = 0.651e-6;
    AVC.User4[Cuba].lim_move_resinc2 = 0.791e-6;
 	Cuba = ConvCubOperScore(415);
    AVC.User4[Cuba].lim_reslop1 = 0.018e-6;
    AVC.User4[Cuba].lim_reslop2 = 0.0241e-6;
    AVC.User4[Cuba].lim_resinc1 = 0.861e-6;
    AVC.User4[Cuba].lim_resinc2 = 1.001e-6;
    AVC.User4[Cuba].lim_move_reslop1 = 0.0151e-6;
    AVC.User4[Cuba].lim_move_reslop2 = 0.0211e-6;
    AVC.User4[Cuba].lim_move_resinc1 = 0.651e-6;
    AVC.User4[Cuba].lim_move_resinc2 = 0.791e-6;
 	Cuba = ConvCubOperScore(475);
    AVC.User4[Cuba].lim_reslop1 = 0.018e-6;
    AVC.User4[Cuba].lim_reslop2 = 0.0241e-6;
    AVC.User4[Cuba].lim_resinc1 = 0.861e-6;
    AVC.User4[Cuba].lim_resinc2 = 1.001e-6;
    AVC.User4[Cuba].lim_move_reslop1 = 0.0151e-6;
    AVC.User4[Cuba].lim_move_reslop2 = 0.0211e-6;
    AVC.User4[Cuba].lim_move_resinc1 = 0.651e-6;
    AVC.User4[Cuba].lim_move_resinc2 = 0.791e-6;

	 dia 10/10/2007 
 	Cuba = ConvCubOperScore(320);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;

	dia 14/11/2007 a pedido de Rilson (alterar de novo p/ remendo) -
	informado errado  
 	Cuba = ConvCubOperScore(315);
	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_hour = 11;
	DataTm.tm_mday = 3;
	DataTm.tm_mon  = 10;
	DataTm.tm_year = 107;
	hora_qca = mktime(&DataTm);
    AVC.User3[Cuba].hora_forno_rem = hora_qca;
	AVC.ParUser1[Cuba].tensao_target =	4.20;
	EST_AVC(Cuba).Est.forno_rem = VERDADEIRO;

	12/11/07 - A pedido de Danilo, forno 185 motor novo p/ velho 
    Cuba = ConvCubOperScore(185);
    AVC.User1[Cuba].eqmotor_up = 0.30e-6;
    AVC.User1[Cuba].eqmotor_down = 0.30e-6;

	 23/11/07 - 15:30h pedido de Geraldo Sossego, forno 214 motor velho p/ novo 
    Cuba = ConvCubOperScore(214);
    AVC.User1[Cuba].eqmotor_up = 1.00e-6;
    AVC.User1[Cuba].eqmotor_down = 1.00e-6;

	03/12/07 alterado de 5 p/ 8 min, a pedido de Rilson 
    Cuba = ConvCubOperScore(322);
	AVC.User4[Cuba].lim_ae_longo = 8*60;
    Cuba = ConvCubOperScore(323);
	AVC.User4[Cuba].lim_ae_longo = 8*60;
    Cuba = ConvCubOperScore(324);
	AVC.User4[Cuba].lim_ae_longo = 8*60;
	
    Ficou faltando alterar este parametro, qdo foi alterado de novo p/ remendo
 	Cuba = ConvCubOperScore(315);
	AVC.User3[Cuba].tipo_forno_prob = REMENDO;
	 05/12/07 - voltagem padrao de 5.50V, a pedido de Elias Portela 
 	Cuba = ConvCubOperScore(149);
	AVC.ParUser1[Cuba].tensao_target = 5.50;

	 20/12/07 - Redefinir EA p/ 484, a pedido de Rilson 
 	Cuba = ConvCubOperScore(484);
	EST_AVC(Cuba).Est.Ea_redefinido = FALSO;
	 18/02/08 - Alterar data 02/11/07 10:00h (1194008400) de hora_forno_novo
				  pois foi inputado erradamente. Forno 315 remendo 
 	Cuba = ConvCubOperScore(315);
	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_mday = 1;
	DataTm.tm_mon  = 0;
	DataTm.tm_year = 105;
	hora_qca = mktime(&DataTm);
	AVC.User1[Cuba].hora_forno_novo = hora_qca;
 	Cuba = ConvCubOperScore(315);
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	EST_AVC(Cuba).Est.forno_rem = FALSO;

	 Colocado forno fora da logica de forno remendo, a pedido de Afonso Lage
	   p/ poder colocar voltagem padrao de 4.90 e 477 p/ 6.0V e alterar data
	de partida forno 373 partido como remendo dia 20/02/08 14:30h
	           forno 477 partido como remendo dia 10/02/08 13:00h

 	Cuba = ConvCubOperScore(373);
	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_mday = 10;
	DataTm.tm_mon  = 1;
	DataTm.tm_year = 108;
	hora_qca = mktime(&DataTm);
    AVC.User3[Cuba].hora_forno_rem = hora_qca;
	EST_AVC(Cuba).Est.forno_rem = FALSO;

	AVC.ParUser1[Cuba].tensao_target = 4.9;
	SUPERV_AVC(Cuba).Sup.mudou_tensao_target = VERDADEIRO;
	SUPERV_AVC_TURNO(Cuba).Sup.mudou_tensao_target = VERDADEIRO;

	SUPERV_AVC(Cuba).Sup.tensao_target_acum += 
										  AVC.ParUser1[Cuba].tensao_target;
	SUPERV_AVC_TURNO(Cuba).Sup.tensao_target_acum += 
										  AVC.ParUser1[Cuba].tensao_target;
 	Cuba = ConvCubOperScore(477);
	AVC.ParUser1[Cuba].tensao_target = 6.0;

	SUPERV_AVC(Cuba).Sup.mudou_tensao_target = VERDADEIRO;
	SUPERV_AVC_TURNO(Cuba).Sup.mudou_tensao_target = VERDADEIRO;
	SUPERV_AVC(Cuba).Sup.tensao_target_acum += 
										  AVC.ParUser1[Cuba].tensao_target;
	SUPERV_AVC_TURNO(Cuba).Sup.tensao_target_acum += 
										  AVC.ParUser1[Cuba].tensao_target;
	Cuba = ConvCubOperScore(373);
	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_mday = 10;
	DataTm.tm_mon  = 0;
	DataTm.tm_year = 108;
	hora_qca = mktime(&DataTm);
    AVC.User3[Cuba].hora_forno_rem = hora_qca;
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
    AVC.User3[Cuba].hora_forno_rem = hora_qca;
	Mudar voltagem padrao do forno 477 de 6.0V p/ 5.80V, a pedido de Afonso
	Cuba = ConvCubOperScore(477);
	AVC.ParUser1[Cuba].tensao_target = 5.8;
	SUPERV_AVC(Cuba).Sup.mudou_tensao_target = VERDADEIRO;
	SUPERV_AVC_TURNO(Cuba).Sup.mudou_tensao_target = VERDADEIRO;

	SUPERV_AVC(Cuba).Sup.tensao_target_acum += 
										  AVC.ParUser1[Cuba].tensao_target;
	SUPERV_AVC_TURNO(Cuba).Sup.tensao_target_acum += 
										  AVC.ParUser1[Cuba].tensao_target;

  Forno 140 motor novo p/ velho - 14/03/2008 
  Cuba = ConvCubOperScore(140);
  AVC.User1[Cuba].eqmotor_up = 0.24e-6;


  fp = fopen ("/usr/score/relatorio/vs/Levcam_on", "w");

  if (fp eq NULL)
  {
	  error("Erro de escrita arquivo //6/usr/score/relatorio/vs/Levcam_on");
  }

  for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
	memset( &DataTm, 0x00, sizeof( struct tm ) );
	memcpy( &DataTm, localtime( &AVC.User3[Cuba].hora_levcam_on ), sizeof( struct tm ) );
    fprintf (fp, "Cuba: %d - %02d/%02d/%4d %02d:%02d\n",
			 CubaOpe,
			 DataTm.tm_mday,
			 DataTm.tm_mon,
			 DataTm.tm_year,
			 DataTm.tm_hour,
			 DataTm.tm_min);
  }
  fclose (fp);
  Cuba = ConvCubOperScore(483);
  EST_AVC(Cuba).Est.alarme_reslop = FALSO;

  Forno 152 motor novo p/ velho e 103 de velho p/ novo- 07/07/2008,
  a pedido de Elias

  Forno 127 pequeno p/ grande e 242 de grande p/ pequeno- 18/07/2008,
  a pedido de Jair

  Foi inputado errado, forno 404 como forno remendo parcial, no dia 18/07/08
	 12:30h. Dia 22/07, mudei para forno novo, a pedido de Afonso Lage
  Cuba = ConvCubOperScore(404);
  AVC.User3[Cuba].hora_forno_rem = AVC.User1[Cuba].hora_forno_novo - 100*3600;

  Forno 226 motor grande p/ pequeno - 23/07/2008, a pedido de Elias
  Forno 281 motor pequeno p/ grande - 24/07/2008, a pedido de Passe'
  Habilitado a logica de disparo de anodo, para Red.2, pois o relatorio de
    operacao esta dando erro - para atender pedido de Adalton - 28/08/2008
  AVL.Trab.log_disparo_anodo = VERDADEIRO;

  Foi inputado errado, fornos 479, 492 como forno novo, nos dias 15/06/08 11h e 21/06/08 15h,
  respectivamente. Dia 01/08/08 08:10h, mudei p/ remendo parcial, a pedido de
  Druso
  Cuba = ConvCubOperScore(479);
  AVC.User1[Cuba].hora_forno_novo = AVC.User3[Cuba].hora_forno_rem - 100*3600;
  Cuba = ConvCubOperScore(492);
  AVC.User1[Cuba].hora_forno_novo = AVC.User3[Cuba].hora_forno_rem - 100*3600;
  Cuba = ConvCubOperScore(479);
  EST_AVC(Cuba).Est.cozimento = FALSO;
  AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
  Cuba = ConvCubOperScore(492);
  EST_AVC(Cuba).Est.cozimento = FALSO;
  AVC.User3[Cuba].tipo_forno_prob = FNORMAL;

   19/08/08 - Normalizar forno 479 
  Cuba = ConvCubOperScore(479);
  EST_AVC(Cuba).Est.cozimento = FALSO;
  AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
  Cuba = ConvCubOperScore(492);
  EST_AVC(Cuba).Est.cozimento = FALSO;
  AVC.User3[Cuba].tipo_forno_prob = FNORMAL;

  Forno 216 motor novo p/ velho 22/08/2008,  a pedido de Virginio
   28/08/08 - Normalizar forno 479 - Tem que ser < tempo_pcb_novo 
  Cuba = ConvCubOperScore(479);
  AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
  AVC.User1[Cuba].hora_forno_novo = AVC.User3[Cuba].hora_forno_rem - 150*24*3600;
  EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

  Cuba = ConvCubOperScore(303);
  AVC.User3[Cuba].tipo_forno_prob = NOVO;
   02/10/08 - Quebrada de 4h, passa p 6 em 6 horas, a pedido de Elias
     carga_manual foi alterado de 54Kg para 70Kg 

  for( CubaOpe = 101; CubaOpe <= 188; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_queb_scb = 6*MIN*SEC;
	AVC.User4[Cuba].hora_queb_ref = 30*SEC;
  }

  for( CubaOpe = 201; CubaOpe <= 288; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_queb_scb = 6*MIN*SEC;
	AVC.User4[Cuba].hora_queb_ref = 4*MIN*SEC + 30*SEC;
  }
  06/10/08 - Atualizar variaveis de supervisao 
  
	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_sec  = 0;
	DataTm.tm_min  = 0;
	DataTm.tm_hour = 0;   05/10/2008 
	DataTm.tm_mday = 5;
	DataTm.tm_mon  = 9;
	 -- Y2k inicio: ano de 2 digitos -- 
	DataTm.tm_year = 108;
	hora_qca = mktime(&DataTm);  converte para time_t

??? Mudar a identificacao dos fornos para Reducao2 e Reducao3 e a data acima

  for( CubaOpe = 101; CubaOpe <= 288; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	if (AVC.User1[Cuba].motivo_aek_off ne AEKNORMAL)
	{
	  SUPERV_AVC(Cuba).Sup.hora_aek_off = hora_qca;
	  SUPERV_AVC(Cuba).Sup.motivo_aek_off = AVC.User1[Cuba].motivo_aek_off;

	  Variaveis de supervisao de TURNO 
	  SUPERV_AVC_TURNO(Cuba).Sup.hora_aek_off = hora_qca;
	  SUPERV_AVC_TURNO(Cuba).Sup.motivo_aek_off = AVC.User1[Cuba].motivo_aek_off;
	}
  }
	Cuba = ConvCubOperScore(303);
	AVC.User3[Cuba].tipo_forno_prob = NOVO;
    17/10/08 - Quebrada de 6h, passa p 4 em 4 horas, a pedido de Elias
     carga_manual foi alterado de 70Kg para 54Kg 

  for( CubaOpe = 101; CubaOpe <= 188; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_queb_scb = 4*MIN*SEC;
	AVC.User4[Cuba].hora_queb_ref = 30*SEC;
  }

  for( CubaOpe = 201; CubaOpe <= 288; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_queb_scb = 4*MIN*SEC;
	AVC.User4[Cuba].hora_queb_ref = 2*MIN*SEC + 30*SEC;
  }
	11/11/08 - Fornos sem previsao 
	Cuba = ConvCubOperScore(317);
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	Cuba = ConvCubOperScore(492);
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

  11/11/08 - alterado corrente padrao dos fornos 266-280 de 66KA p/ 68KA 
  a pedido de Danilo Brito
  ??/11/08 - alterado corrente padrao dos fornos 266-280 de 68KA p/ 67KA 
  a pedido de Danilo Brito
  18/11/08 - alterado corrente padrao dos fornos 266-280 de 67KA p/ 67,8KA 
  a pedido de Danilo Brito
  Cuba = ConvCubOperScore(493);
  AVC.User3[Cuba].tipo_forno_prob = NOVO;

   Inicializa AVC.User4[Cuba].hora_ref_prox_scb_apos_ae, que e a referencia
	 para calcular a proxima quebrada programada apos AE 

  for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].hora_ref_prox_scb_apos_ae = 8*MIN*SEC + 20*SEC;
  }

  Horario e intervalo de quebrada alterados a pedido de Danilo
  for( CubaOpe = 101; CubaOpe <= 188; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_queb_scb = 6*MIN*SEC;
	AVC.User4[Cuba].hora_queb_ref = 2*MIN*SEC + 30*SEC;
  }

  for( CubaOpe = 201; CubaOpe <= 288; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].lim_queb_scb = 6*MIN*SEC;
	AVC.User4[Cuba].hora_queb_ref = 4*MIN*SEC;
  }

  Alterei valores de ten_inc_sigs de 50mV p/ 25mV, a pedido de Mr. Tandom
  28/01/09 16:00h
	Cuba = ConvCubOperScore(373);
	AVC.User3[Cuba].ten_inc_sigs = 0.025;
	Cuba = ConvCubOperScore(375);
	AVC.User3[Cuba].ten_inc_sigs = 0.025;
	Cuba = ConvCubOperScore(374);
	AVC.User3[Cuba].ten_inc_sigs = -0.05;

	05/02/09 -  Habilitar previsao
 	Cuba = ConvCubOperScore(308);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(315);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(317);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(321);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(322);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(385);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(387);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(391);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(395);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(408);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(409);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(487);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(489);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(495);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;

 	Cuba = ConvCubOperScore(304);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;
 	Cuba = ConvCubOperScore(319);
	EST_AVC(Cuba).Est.previsao_manual = VERDADEIRO;

	12/02/09 - espera de efeito fornos 307, 390, 413, 422, 423 mudado de 40h
    para 32h, a pedido de Rilson

	20/02/09 atualizado var. ten_inc_sigl, do forno 378, pois este acrescimo
	comecou antes de ser alterado de tab_inc_sigl de 50mV para 25mV
 	Cuba = ConvCubOperScore(378);
	AVC.User3[Cuba].ten_inc_sigl = 0.025;

	20/02/09 zerar ten_inc_qca fornos 317-324 e 373-380
  for( CubaOpe = 317; CubaOpe <= 324; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User3[Cuba].ten_inc_qca = 0;
  }

  for( CubaOpe = 373; CubaOpe <= 380; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User3[Cuba].ten_inc_qca = 0;
  }

  for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User3[Cuba].aepcb_ult_24h  = 0;
  }

	26/02/09 - Redefinir EA p/ 313, a pedido de Rilson 
 	Cuba = ConvCubOperScore(313);
	EST_AVC(Cuba).Est.Ea_redefinido = FALSO;

	02/03/09 Zerar var. da User3, que foram definidas em area que ja
	foram utilizadas anteriormente 
  for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	for (i=0; i<24; i++)
	{
	  AVC.User3[Cuba].tab_quebrada[i] = 0;
	}
    AVC.User3[Cuba].queb_ult_24h = 0;
    AVC.User3[Cuba].aepcb_ult_24h = 0;
    AVC.User3[Cuba].desvio_up_ult_24h = 0;
    AVC.User3[Cuba].desvio_down_ult_24h = 0;
  }

  04/03/09 16h, alterado cor_target_forno de 61.50KA p/ 61.80KA a pedido de
  Danilo 

  10/03/09 Alterei data de QCA de alguns fornos para aparecer na sequencia de
           24 fornos, a pedido de Elias
  for( CubaOpe = 101; CubaOpe <= 123; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User3[Cuba].hora_queb_qca = AVC.User3[Cuba1].hora_queb_qca+48*MIN*SEC;
  }
  for( CubaOpe = 285; CubaOpe <= 288; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User3[Cuba].hora_queb_qca = AVC.User3[Cuba].hora_queb_qca-24*MIN*SEC;
  }

	13/03/09 - Redefinir EA p/ 490, a pedido de Rilson 
 	Cuba = ConvCubOperScore(490);
	EST_AVC(Cuba).Est.Ea_redefinido = FALSO;

	26/03/09 - Desabilitar trat. sigmas (2h) para forno desligado
 	Cuba = ConvCubOperScore(102);
	EST_AVC(Cuba).Est.sigs_2h_ini = FALSO;
   	Cuba = ConvCubOperScore(241);
	EST_AVC(Cuba).Est.sigs_2h_ini = FALSO;

	27/03/09 atualizado var. ten_inc_sigl, dos fornos 421, 422, 475, 476, 478,
	pois este acrescimo comecou antes de ser alterado de tab_inc_sigl de 50mV
    para 25mV
 	Cuba = ConvCubOperScore(421);
	AVC.User3[Cuba].ten_inc_sigl = 0.025;
 	Cuba = ConvCubOperScore(422);
	AVC.User3[Cuba].ten_inc_sigl = 0.025;
 	Cuba = ConvCubOperScore(475);
	AVC.User3[Cuba].ten_inc_sigl = 0.025;
 	Cuba = ConvCubOperScore(476);
	AVC.User3[Cuba].ten_inc_sigl = 0.025;
 	Cuba = ConvCubOperScore(478);
	AVC.User3[Cuba].ten_inc_sigl = 0.025;

	27/03/09 atualizado var. ten_inc_sigs, dos fornos 417, 420-423, 476,
    478-480, de 50 p/ 25mV, e do forno 424 de 100 p/ 50mV, pois este acrescimo
	comecou antes de ser alterado a tabela de acrescimo por rank
	Cuba = ConvCubOperScore(417);
	AVC.User3[Cuba].ten_inc_sigs = 0.025;
	Cuba = ConvCubOperScore(420);
	AVC.User3[Cuba].ten_inc_sigs = 0.025;
	Cuba = ConvCubOperScore(421);
	AVC.User3[Cuba].ten_inc_sigs = 0.025;
	Cuba = ConvCubOperScore(422);
	AVC.User3[Cuba].ten_inc_sigs = 0.025;
	Cuba = ConvCubOperScore(423);
	AVC.User3[Cuba].ten_inc_sigs = 0.025;
	Cuba = ConvCubOperScore(476);
	AVC.User3[Cuba].ten_inc_sigs = 0.025;
	Cuba = ConvCubOperScore(478);
	AVC.User3[Cuba].ten_inc_sigs = 0.025;
	Cuba = ConvCubOperScore(479);
	AVC.User3[Cuba].ten_inc_sigs = 0.025;
	Cuba = ConvCubOperScore(480);
	AVC.User3[Cuba].ten_inc_sigs = 0.025;
	Cuba = ConvCubOperScore(424);
	AVC.User3[Cuba].ten_inc_sigs = 0.05;

	01/04/09 - Atualizar data de partida do forno 424, pois foi lancado como forno novo
	erradamente 
	memset( &DataTm, 0x00, sizeof( struct tm ) );
	DataTm.tm_hour = 15;
	DataTm.tm_mday = 28;
	DataTm.tm_mon  = 11;
	DataTm.tm_year = 104;
	hora_qca = mktime(&DataTm); 
	Cuba = ConvCubOperScore(424);
	AVC.User1[Cuba].hora_forno_novo = hora_qca;

	Atualizar hora da quebrada de cabeceira 
	Cuba1 = ConvCubOperScore(251);
	for( CubaOpe = 255; CubaOpe <= 259; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = AVC.User3[Cuba1].hora_queb_qca;
	}

	17/04/09 - Desabilitar trat. sigmas (2h) para forno desligado
 	Cuba = ConvCubOperScore(182);
	EST_AVC(Cuba).Est.sigs_2h_ini = FALSO;

	20/04/09 - Atualizar hora da quebrada de cabeceira 
	Cuba1 = ConvCubOperScore(254);
	for( CubaOpe = 255; CubaOpe <= 259; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = AVC.User3[Cuba1].hora_queb_qca;
	}

	Cuba1 = ConvCubOperScore(106);
	Cuba = ConvCubOperScore(101);
	AVC.User3[Cuba].hora_queb_qca = AVC.User3[Cuba1].hora_queb_qca;
	11/05/09 - Atualizar hora da quebrada de cabeceira 
	Cuba1 = ConvCubOperScore(224);
	for( CubaOpe = 218; CubaOpe <= 223; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_queb_qca = AVC.User3[Cuba1].hora_queb_qca;
	}

	13/05/09 - Resetado alarme de alarme_anodo
	Cuba = ConvCubOperScore(144);
	EST_AVC(Cuba).Est.alarme_anodo = FALSO;
	AVC.User3[Cuba].hora_prob_anodo -= (120*24*60*60);
	Cuba = ConvCubOperScore(219);
	EST_AVC(Cuba).Est.alarme_anodo = FALSO;
	AVC.User3[Cuba].hora_prob_anodo -= (120*24*60*60);
	Cuba = ConvCubOperScore(244);
	EST_AVC(Cuba).Est.alarme_anodo = FALSO;
	AVC.User3[Cuba].hora_prob_anodo -= (120*24*60*60);

	14/05/09 - Normalizou fornos para previsao, a pedido de Rilson
	Cuba = ConvCubOperScore(313);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	Cuba = ConvCubOperScore(373);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	Cuba = ConvCubOperScore(389);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	Cuba = ConvCubOperScore(392);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	Cuba = ConvCubOperScore(396);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

	15/05/09 - Resetar var. ParUser2.nao_quebrar_aepcb e User3.aepcb_nao_quebra
	for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].aepcb_nao_quebra = FALSO;
	  AVC.ParUser1[Cuba].nao_quebrar_aepcb = FALSO;
	}

	15/05/09 - Normalizou forno para previsao, apos teste OpeInibePrevisao
	Cuba = ConvCubOperScore(302);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;


	18/05/09 - Rilson pediu p/ alterar intervalo entre previsoes de 4h p/ 3h

	20/05/09 - Joao Alberto pediu para desabilitar fornos com quebrada
			   alternada (307, 390, 413, 422, 423)


	//26/05/09 - (MARCO) Normalilzou fornos 478 e 388 para previsao a pedido de Rilson
	
	Cuba = ConvCubOperScore(478);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

	Cuba = ConvCubOperScore(388);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;


	//29/05/09 - (MARCO) Normalilzou fornos 413 e 414 para previsao a pedido de Rilson
														
	Cuba = ConvCubOperScore(413);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

	Cuba = ConvCubOperScore(414);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

	04/06/09 - Retirar fornos do acrescimo de sigma short 2 horas, a pedido
				de Elias Portela - Elisa
	for( CubaOpe = 101; CubaOpe <= 288; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.ParUser2[Cuba].acrescimo_sigs2h = FALSO;
	  AVC.User3[Cuba].ten_inc_sigs2h = 0.0;
	  EST_AVC(Cuba).Est.sigs_2h_ini = FALSO;
	  EST_AVC(Cuba).Est.sigs_2h_fim = FALSO;
	}

	  jun/09 - Alteracao horario de referencia para quebrada programada da
			   sala 400 a pedido de Rilson e Joao Alberto
	  for( CubaOpe = 401; CubaOpe <= 496; ++CubaOpe )
	  {
		Cuba = ConvCubOperScore(CubaOpe);
		AVC.User4[Cuba].hora_queb_ref = 8*3600+30*60;
	  }

	  jun/09 - Alteracao horario de referencia para quebrada programada da
			   sala 400 a pedido de Fernanda
	  for( CubaOpe = 401; CubaOpe <= 496; ++CubaOpe )
	  {
		Cuba = ConvCubOperScore(CubaOpe);
		AVC.User4[Cuba].hora_queb_ref = 9*3600+20*60;
	  }

	09/07/09 - Retirar forno do acrescimo de sigma short 2 horas, foi desligado
	Cuba = ConvCubOperScore(156);
	AVC.ParUser2[Cuba].acrescimo_sigs2h = FALSO;
	AVC.User3[Cuba].ten_inc_sigs2h = 0.0;
	EST_AVC(Cuba).Est.sigs_2h_ini = FALSO;
	EST_AVC(Cuba).Est.sigs_2h_fim = FALSO;

	09/07/09 15:45 - Retornar forno 381 para previsao a pedido de Rilson. Forno
	estava fora da AEPCB por ponta. Alterei dur_pcb_ponta de 8 para 3 dias.

	28/07/09 15:45h - Retornar forno 480 para previsao a pedido de Rilson.
	Estava fora por frio

	Cuba = ConvCubOperScore(480);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

	31/07/09 14:20h - Retornar fornos 303, 373, 377, 384, 478, 483, 485, 486
					  para previsao a pedido de Rilson.	Estava fora por ponta
	
	Cuba = ConvCubOperScore(303);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

	Cuba = ConvCubOperScore(373);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

	Cuba = ConvCubOperScore(377);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

	Cuba = ConvCubOperScore(384);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

	Cuba = ConvCubOperScore(478);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

	Cuba = ConvCubOperScore(483);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

	Cuba = ConvCubOperScore(485);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

	Cuba = ConvCubOperScore(486);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

	19/08/09 - Voltar forno 483 para carga normal, apos EA redefinido, a pedido
               de Rilson 

 	Cuba = ConvCubOperScore(483);
	EST_AVC(Cuba).Est.Ea_redefinido = FALSO;
	EST_AVC(Cuba).Est.Ea_apos_redefinido = FALSO;

	21/08/09 - Voltar fornos 373, 384, 416 e 473 para funcionamento normal, a pedido
				de Rilson

	Cuba = ConvCubOperScore(373);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

	Cuba = ConvCubOperScore(384);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
		
	Cuba = ConvCubOperScore(416);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

	Cuba = ConvCubOperScore(473);
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

  Cuba = ConvCubOperScore(485);
  EST_AVC(Cuba).Est.alarme_reslop = FALSO;

  Cuba = ConvCubOperScore(320);
  EST_AVC(Cuba).Est.risco_vazar = FALSO;
  Cuba = ConvCubOperScore(481);
  EST_AVC(Cuba).Est.risco_vazar = FALSO;
  Cuba = ConvCubOperScore(494);
  EST_AVC(Cuba).Est.risco_vazar = FALSO;

  18/09/2009 16:00h - Fornos 304, 308, 386, 395 habilitados para previsao com
		              quebrada, a pedido de Rilson
  24/09/2009 16:00h - Fornos 306, 388, 386, 396 habilitados para previsao com
		              quebrada, a pedido de Rilson
*/

/*  13/10/09 - Voltar fornos 311,321,375,378,405,408,409,415,482,484,486 para 
	carga normal, apos EA redefinido, a pedido de Rilson  

	Cuba = ConvCubOperScore(311);
	EST_AVC(Cuba).Est.Ea_redefinido = FALSO;
	EST_AVC(Cuba).Est.Ea_apos_redefinido = FALSO;							  
	Cuba = ConvCubOperScore(321);
	EST_AVC(Cuba).Est.Ea_redefinido = FALSO;	   
	EST_AVC(Cuba).Est.Ea_apos_redefinido = FALSO;
	Cuba = ConvCubOperScore(375);
	EST_AVC(Cuba).Est.Ea_redefinido = FALSO;
	EST_AVC(Cuba).Est.Ea_apos_redefinido = FALSO;
	Cuba = ConvCubOperScore(378);
	EST_AVC(Cuba).Est.Ea_redefinido = FALSO;
	EST_AVC(Cuba).Est.Ea_apos_redefinido = FALSO;
	Cuba = ConvCubOperScore(405);
	EST_AVC(Cuba).Est.Ea_redefinido = FALSO;
	EST_AVC(Cuba).Est.Ea_apos_redefinido = FALSO;
    Cuba = ConvCubOperScore(408);
	EST_AVC(Cuba).Est.Ea_redefinido = FALSO;
	EST_AVC(Cuba).Est.Ea_apos_redefinido = FALSO;
	Cuba = ConvCubOperScore(409);
	EST_AVC(Cuba).Est.Ea_redefinido = FALSO;
	EST_AVC(Cuba).Est.Ea_apos_redefinido = FALSO;
	Cuba = ConvCubOperScore(415);
	EST_AVC(Cuba).Est.Ea_redefinido = FALSO;
	EST_AVC(Cuba).Est.Ea_apos_redefinido = FALSO;
	Cuba = ConvCubOperScore(482);
	EST_AVC(Cuba).Est.Ea_redefinido = FALSO;
	EST_AVC(Cuba).Est.Ea_apos_redefinido = FALSO;
	Cuba = ConvCubOperScore(484);
	EST_AVC(Cuba).Est.Ea_redefinido = FALSO;
	EST_AVC(Cuba).Est.Ea_apos_redefinido = FALSO;
	Cuba = ConvCubOperScore(486);
	EST_AVC(Cuba).Est.Ea_redefinido = FALSO;
	EST_AVC(Cuba).Est.Ea_apos_redefinido = FALSO;

  jun/09 - Alteracao horario de referencia para quebrada programada da
  sala 300 a pedido de Rilson e Fernanda 
  for( CubaOpe = 301; CubaOpe <= 396; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].hora_queb_ref = 8*3600+40*60;
  }
 												  

	// 22/10/09 - (MARCO) A Pedido de Rilson normalizou o forno 421
	Cuba = ConvCubOperScore(421);
	EST_AVC(Cuba).Est.Ea_redefinido = FALSO;	
	EST_AVC(Cuba).Est.Ea_apos_redefinido = FALSO;
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;


	// Marco - (10/11/2009) - Altera referencia de quebradas, a pedido de Rilson e Spock!

	i = 0;
	for( CubaOpe = 396 ; CubaOpe <= 389; --CubaOpe)
	{
		Cuba = ConvCubOperScore(CubaOpe);
		AVC.ParUser1[Cuba].off_queb_f = i;
		i += 38;
	}

	i += 60;
	for( CubaOpe = 308; CubaOpe <= 301; --CubaOpe)
	{
		Cuba = ConvCubOperScore(CubaOpe);
		AVC.ParUser1[Cuba].off_queb_f = i;
		i += 38;
	}

	i += 60;
	for( CubaOpe = 388; CubaOpe <= 381; --CubaOpe)
	{
		Cuba = ConvCubOperScore(CubaOpe);
		AVC.ParUser1[Cuba].off_queb_f = i;
		i += 38;
	}

	i += 60;
	for( CubaOpe = 316; CubaOpe <= 309; --CubaOpe)
	{
		Cuba = ConvCubOperScore(CubaOpe);
		AVC.ParUser1[Cuba].off_queb_f = i;
		i += 38;
	}

	i += 60;
	for( CubaOpe = 380; CubaOpe <= 373; --CubaOpe)
	{
		Cuba = ConvCubOperScore(CubaOpe);
		AVC.ParUser1[Cuba].off_queb_f = i;
		i += 38;
	}

	i += 60;
	for( CubaOpe = 324; CubaOpe <= 317; --CubaOpe)
	{											  
		Cuba = ConvCubOperScore(CubaOpe);
		AVC.ParUser1[Cuba].off_queb_f = i;
		i += 38;
	}

	i = 0;
	for( CubaOpe = 496 ; CubaOpe <= 489; --CubaOpe)
	{
		Cuba = ConvCubOperScore(CubaOpe);
		AVC.ParUser1[Cuba].off_queb_f = i;
		i += 38;
	}

	i += 60;
	for( CubaOpe = 408; CubaOpe <= 401; --CubaOpe)
	{
		Cuba = ConvCubOperScore(CubaOpe);
		AVC.ParUser1[Cuba].off_queb_f = i;
		i += 38;
	}

	i += 60;
	for( CubaOpe = 488; CubaOpe <= 481; --CubaOpe)
	{
		Cuba = ConvCubOperScore(CubaOpe);
		AVC.ParUser1[Cuba].off_queb_f = i;
		i += 38;
	}

	i += 60;
	for( CubaOpe = 416; CubaOpe <= 409; --CubaOpe)
	{
		Cuba = ConvCubOperScore(CubaOpe);
		AVC.ParUser1[Cuba].off_queb_f = i;
		i += 38;
	}

	i += 60;
	for( CubaOpe = 480; CubaOpe <= 473; --CubaOpe)
	{
		Cuba = ConvCubOperScore(CubaOpe);
		AVC.ParUser1[Cuba].off_queb_f = i;
		i += 38;
	}

	i += 60;
	for( CubaOpe = 424; CubaOpe <= 417; --CubaOpe)
	{											  
		Cuba = ConvCubOperScore(CubaOpe);
		AVC.ParUser1[Cuba].off_queb_f = i;
		i += 38;
	}


	i = 0;
	for( CubaOpe = 373; CubaOpe <= 396; ++CubaOpe)
	{
		Cuba=ConvCubOperScore(CubaOpe);
		AVC.ParUser1[Cuba].off_queb_f = i;
		AVC.ParUser1[Cuba].off_queb_b = 1868 - i;
		i += 38;
	}

	i = 994;
	for( CubaOpe = 301; CubaOpe <= 324; ++CubaOpe)
	{
		Cuba=ConvCubOperScore(CubaOpe);
		AVC.ParUser1[Cuba].off_queb_f = i;
		AVC.ParUser1[Cuba].off_queb_b = 874 - (i - 994);
		i += 38;
	}

	i = 0;
	for( CubaOpe = 473; CubaOpe <= 496; ++CubaOpe)
	{
		Cuba=ConvCubOperScore(CubaOpe);
		AVC.ParUser1[Cuba].off_queb_f = i;
		AVC.ParUser1[Cuba].off_queb_b = 1868 - i;
		i += 38;
	}

	i = 994;
	for( CubaOpe = 401; CubaOpe <= 424; ++CubaOpe)
	{
		Cuba=ConvCubOperScore(CubaOpe);
		AVC.ParUser1[Cuba].off_queb_f = i;
		AVC.ParUser1[Cuba].off_queb_b = 874 - (i - 994);
		i += 38;
	}




  Out/09 - Alteracao horario de referencia para quebrada programada da
  sala 400 a pedido de Rilson e Fernanda 
  for( CubaOpe = 401; CubaOpe <= 496; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].hora_queb_ref = 9*3600+40*60;
  }

  // Coloca forno 324 na quebrada de 4h em 4h.

  Cuba=ConvCubOperScore(324);
  AVC.User1[Cuba].tipo_forno_scb = 4;

  Cuba=ConvCubOperScore(324);
  AVC.User3[Cuba].side_break = JANELA;

  14/12/2009 - Alterado zona da previsao, a pedido de Rilson Santana
  0.018e-6 p/ 0.016e-6;  0.024e-6 p/ 0.022e-6
  0.86e-6 p/  0.84e-6;   1.00e-6 p/  0.98e-6

  for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
    AVC.User4[Cuba].lim_reslop1 = 0.0161e-6;
    AVC.User4[Cuba].lim_reslop2 = 0.0221e-6;
    AVC.User4[Cuba].lim_resinc1 = 0.841e-6;
    AVC.User4[Cuba].lim_resinc2 = 0.981e-6;
  }

  i = 0;

  for( CubaOpe = 473; CubaOpe <= 496; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].hora_queb_ref = 9*3600+20*60;
	AVC.User1[Cuba].tipo_forno_scb = 1;	
    AVC.User4[Cuba].int_scb_ae[0] = 1*MIN*SEC;
	AVC.User4[Cuba].seq_normal[0] = 511;
	AVC.User4[Cuba].lim_queb_eq[0] = 9;
	AVC.User4[Cuba].sequencia_queb = 436;
	AVC.User4[Cuba].lim_scb_qca	 = 2*MIN*SEC + 40*SEC;
	AVC.User3[Cuba].dur_inc_qca	 = 2*MIN*SEC + 40*SEC;
	AVC.User4[Cuba].lim_queb_scb = 2*MIN*SEC + 40*SEC;
	AVC.ParUser1[Cuba].off_queb_f = i;	  
	AVC.ParUser1[Cuba].off_queb_b = 1808 - i;
 	i += 38;
  }

  i += 22;

  for( CubaOpe = 401; CubaOpe <= 424; ++CubaOpe )
  {
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User4[Cuba].hora_queb_ref = 9*3600+20*60;
	AVC.User1[Cuba].tipo_forno_scb = 1;
	AVC.User4[Cuba].int_scb_ae[0] = 1*MIN*SEC;
	AVC.User4[Cuba].seq_normal[0] = 511;
	AVC.User4[Cuba].lim_queb_eq[0] = 9;
	AVC.User4[Cuba].sequencia_queb = 436;
	AVC.User4[Cuba].lim_scb_qca	 = 2*MIN*SEC + 40*SEC;
	AVC.User3[Cuba].dur_inc_qca	 = 2*MIN*SEC + 40*SEC;
	AVC.User4[Cuba].lim_queb_scb = 2*MIN*SEC + 40*SEC;
	AVC.ParUser1[Cuba].off_queb_f = i;
	AVC.ParUser1[Cuba].off_queb_b = 1808 - i;
    i += 38;
  }


Cuba = ConvCubOperScore(169);
AVC.User4[Cuba].CicloAnodicoAnt = 17*(24*60)+ 21*(60); 

  

	// 15/03/10 - (MARCO) A Pedido de Fabio Silva normalizou o forno 411
	Cuba = ConvCubOperScore(411);
	EST_AVC(Cuba).Est.Ea_redefinido = FALSO;
	EST_AVC(Cuba).Est.Ea_apos_redefinido = FALSO;
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;


    for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].ten_inc_qca  = 0.10;
	  AVC.User3[Cuba].dur_inc_qca  = 1*MIN*SEC;
	}


	CubaOpe = 307;
	Cuba = ConvCubOperScore(CubaOpe);
	EST_AVC(Cuba).Est.forno_rem = FALSO;

	CubaOpe = 311;
	Cuba = ConvCubOperScore(CubaOpe);
	EST_AVC(Cuba).Est.forno_rem = FALSO;



// Altera horario e referencia das quebradas programadas da sala 300 a pedido e Denilso e Fabio

	i = 0;
	for( CubaOpe = 373; CubaOpe <= 396; ++CubaOpe)
	{
		Cuba=ConvCubOperScore(CubaOpe);
		AVC.User4[Cuba].hora_queb_ref = 8*3600 + 20*60;
		AVC.ParUser1[Cuba].off_queb_f = i;
		i += 38;
	}


	for( CubaOpe = 301; CubaOpe <= 324; ++CubaOpe)
	{
		Cuba=ConvCubOperScore(CubaOpe);
		AVC.User4[Cuba].hora_queb_ref = 8*3600 + 20*60;
		AVC.ParUser1[Cuba].off_queb_f = i;
		i += 38;
	}
    
    i = 0;
	for( CubaOpe = 324; CubaOpe >= 301; --CubaOpe)
	{
		Cuba=ConvCubOperScore(CubaOpe);
		AVC.ParUser1[Cuba].off_queb_b = i;
		i += 38;
	}


	for( CubaOpe = 396; CubaOpe >= 373; --CubaOpe)
	{
		Cuba=ConvCubOperScore(CubaOpe);
		AVC.ParUser1[Cuba].off_queb_b = i;
		i += 38;
	}

    for( CubaOpe = 401; CubaOpe <= 496; ++CubaOpe)
	{
		Cuba=ConvCubOperScore(CubaOpe);
		AVC.User4[Cuba].hora_queb_ref = 9*3600 + 40*60;	
	}


	14/12/2009 - Alterado zona da previsao, a pedido de Fabio Silva


	for( CubaOpe = 301; CubaOpe <= 396; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User4[Cuba].lim_reslop1 = 0.031e-6;
	  AVC.User4[Cuba].lim_reslop2 = 0.041e-6;
	  AVC.User4[Cuba].lim_resinc1 = 1.341e-6;
	  AVC.User4[Cuba].lim_resinc2 = 1.511e-6;
	}

	for( CubaOpe = 301; CubaOpe <=396; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User4[Cuba].lim_move_reslop1 = 0.0281e-6;	
	  AVC.User4[Cuba].lim_move_reslop2 = 0.0351e-6;
	  AVC.User4[Cuba].lim_move_resinc1 = 1.071e-6;
	  AVC.User4[Cuba].lim_move_resinc2 = 1.251e-6;
	}

	CubaOpe = 323;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User1[Cuba].tipo_forno_scb = 1;


//	14/05/2010 - Alterado zona da previsao, a pedido de Fabio Silva


	for( CubaOpe = 301; CubaOpe <= 396; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User4[Cuba].lim_reslop1 = 0.0161e-6;
	  AVC.User4[Cuba].lim_reslop2 = 0.0221e-6;
	  AVC.User4[Cuba].lim_resinc1 = 0.841e-6;
	  AVC.User4[Cuba].lim_resinc2 = 0.981e-6;
	}

	CubaOpe = 323;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User1[Cuba].tipo_forno_scb = 4;
	AVC.User3[Cuba].hora_forno_rem_local = AVC.User1[Cuba].hora_forno_novo;
	EST_AVC(Cuba).Est.forno_rem_local = VERDADEIRO;
	EST_AVC(Cuba).Est.forno_novo = FALSO;	

	CubaOpe = 307;
	Cuba = ConvCubOperScore(CubaOpe);
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;  

	for( CubaOpe = 301; CubaOpe <= 396; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.ParUser1[Cuba].espera_ae = 19;
	}

	CubaOpe = 323;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.User1[Cuba].tipo_forno_novo = 4;	
	AVC.User3[Cuba].tipo_forno_prob = 4;
	EST_AVC(Cuba).Est.forno_rem_local = VERDADEIRO;

	for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
	{
		Cuba = ConvCubOperScore(CubaOpe);
		AVC.User3[Cuba].ten_inc_sigs = 0;
	}

	for( CubaOpe = 401; CubaOpe <= 496; ++CubaOpe)
	{
		Cuba=ConvCubOperScore(CubaOpe);
		AVC.User4[Cuba].hora_queb_ref = 8*3600 + 20*60;
		AVC.ParUser1[Cuba].espera_ae = 19;
	}


	for( CubaOpe = 401; CubaOpe <=496; ++CubaOpe )
	{
  	  Cuba = ConvCubOperScore(CubaOpe);
      AVC.User4[Cuba].lim_move_reslop1 = 0.0281e-6;
      AVC.User4[Cuba].lim_move_reslop2 = 0.0351e-6;
  	  AVC.User4[Cuba].lim_move_resinc1 = 1.071e-6;
 	  AVC.User4[Cuba].lim_move_resinc2 = 1.251e-6;
    }

	for( CubaOpe = 301; CubaOpe <=496; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].aepcb_nao_quebra = FALSO;
	}
	for( CubaOpe = 401; CubaOpe <=496; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User4[Cuba].hora_queb_ref = 8*3600+52*60;
	}

	24/06/2010 Elisa - Alterado zona do move. Estava maior do que a zona da 
				  previsao.  
	De 0.028 p/ 0.0014; 0.035 p/ 0.019; 1.07 p/ 0.67; 1.25 p/ 0.81

	Cuba = ConvCubOperScore(391);
	AVC.User4[Cuba].lim_move_reslop1 = 0.0141e-6;	
	AVC.User4[Cuba].lim_move_reslop2 = 0.0191e-6;
	AVC.User4[Cuba].lim_move_resinc1 = 0.671e-6;
	AVC.User4[Cuba].lim_move_resinc2 = 0.811e-6;

	for( CubaOpe = 393; CubaOpe <=395; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User4[Cuba].lim_move_reslop1 = 0.0141e-6;	
	  AVC.User4[Cuba].lim_move_reslop2 = 0.0191e-6;
	  AVC.User4[Cuba].lim_move_resinc1 = 0.671e-6;
	  AVC.User4[Cuba].lim_move_resinc2 = 0.811e-6;
	}

	for( CubaOpe = 301; CubaOpe <=496; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User4[Cuba].lim_move_reslop1 = 0.0141e-6;	
	  AVC.User4[Cuba].lim_move_reslop2 = 0.0191e-6;
	  AVC.User4[Cuba].lim_move_resinc1 = 0.671e-6;
	  AVC.User4[Cuba].lim_move_resinc2 = 0.811e-6;
	}

//	 Voltar fornos 305,388,491 a pedido de Rilson 
	Cuba = ConvCubOperScore(305);
	EST_AVC(Cuba).Est.Ea_redefinido = FALSO;
	EST_AVC(Cuba).Est.Ea_apos_redefinido = FALSO;

	Cuba = ConvCubOperScore(388);
	EST_AVC(Cuba).Est.Ea_redefinido = FALSO;
	EST_AVC(Cuba).Est.Ea_apos_redefinido = FALSO;

	Cuba = ConvCubOperScore(491);
	EST_AVC(Cuba).Est.Ea_redefinido = FALSO;
	EST_AVC(Cuba).Est.Ea_apos_redefinido = FALSO;


	for( CubaOpe = 301; CubaOpe <=496; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User1[Cuba].ult_ciclo = FALSO;
	  AVC.User1[Cuba].num_queb_ciclo = 0;
	  AVC.User1[Cuba].num_ciclo = 1;
	  AVC.ParUser1[Cuba].ativa_smart_feed = VERDADEIRO;
	  AVC.ParUser1[Cuba].num_queb_ciclo = 3;
	  AVC.ParUser1[Cuba].num_ciclos = 2;
	}

	for( CubaOpe = 301; CubaOpe <=496; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_aepcb = 1280078132;
	}

	10/08/10 - Voltar o forno 310 p/ previsao apos anormalidade, pedido de Fabio Silva

	
	CubaOpe = 310;
	Cuba = ConvCubOperScore(CubaOpe);   
	AVC.User3[Cuba].hora_prob_anodo -= (120*24*60*60);


	for( CubaOpe = 301; CubaOpe <=496; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User1[Cuba].ult_ciclo = FALSO;
	  AVC.User1[Cuba].num_queb_ciclo = 0;
	  AVC.User1[Cuba].num_ciclo = 1;
	  AVC.ParUser1[Cuba].ativa_smart_feed = VERDADEIRO;
	  AVC.ParUser1[Cuba].num_queb_ciclo = 3;
	  AVC.ParUser1[Cuba].num_ciclos = 2;
	}


	CubaOpe = 322;
	Cuba = ConvCubOperScore(CubaOpe);
	ComandaSaidaRem(Cuba, LIGAR, BIT_ENVIA_QUEBRA, QUEBRA_CORREDOR);

    i=0;
	for( CubaOpe = 373; CubaOpe <=380; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User4[Cuba].hora_queb_ref = 9*3600;
	  AVC.ParUser1[Cuba].off_queb_f = i;
	  AVC.ParUser1[Cuba].off_queb_b = 570 - i;
	  i += 38; 
	  AVC.User1[Cuba].tipo_forno_scb = 4;
	  AVC.User1[Cuba].salva_tipo_scb = 4; 
	  AVC.User4[Cuba].seq_normal[3] = 63;
	  AVC.User4[Cuba].int_scb_ae[3] = 1*MIN*SEC;
	  AVC.User4[Cuba].lim_queb_eq[3] = 6; 
	  AVC.User4[Cuba].sequencia_queb = 42;
	  AVC.User4[Cuba].lim_scb_qca = 4*MIN*SEC;
	  AVC.User3[Cuba].dur_inc_qca = 4*MIN*SEC;
	  AVC.User4[Cuba].lim_queb_scb = 2*MIN*SEC + 40*SEC;
	}

	for( CubaOpe = 317; CubaOpe <=324; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User4[Cuba].hora_queb_ref = 9*3600;
	  AVC.ParUser1[Cuba].off_queb_f = i;
	  AVC.ParUser1[Cuba].off_queb_b = 570 - i;
	  i +=38;
	  AVC.User1[Cuba].tipo_forno_scb = 4;
	  AVC.User1[Cuba].salva_tipo_scb = 4;
	  AVC.User4[Cuba].seq_normal[3] = 63;
	  AVC.User4[Cuba].int_scb_ae[3] = 1*MIN*SEC;
	  AVC.User4[Cuba].lim_queb_eq[3] = 6; 
	  AVC.User4[Cuba].sequencia_queb = 42;
	  AVC.User4[Cuba].lim_scb_qca = 4*MIN*SEC;
	  AVC.User3[Cuba].dur_inc_qca = 4*MIN*SEC;
	  AVC.User4[Cuba].lim_queb_scb = 2*MIN*SEC + 40*SEC;
	}

	for( CubaOpe = 317; CubaOpe <=380; ++CubaOpe )
	{
		Cuba = ConvCubOperScore(CubaOpe);
		AVC.User1[Cuba].num_ciclo = 1;
	}

	Cuba = ConvCubOperScore(323);
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;

	Cuba = ConvCubOperScore(324);
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;
	AVC.User3[Cuba].tipo_forno_prob = FNORMAL;


	for( CubaOpe = 317; CubaOpe <=380; ++CubaOpe )
	{
		Cuba = ConvCubOperScore(CubaOpe);
		AVC.User4[Cuba].lim_ae_longo = 8*60;
	}


	Cuba = ConvCubOperScore(321);
	AVC.User3[Cuba].tipo_forno_prob = 14;
	EST_AVC(Cuba).Est.previsao_ativo = VERDADEIRO;

	for( CubaOpe = 301; CubaOpe <=496; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
 	  AVC.User4[Cuba].int_scb_ae[3] = 30*SEC;
	}

 02/11/2010 Mudanca de resinc e reslop p/ previsao na VS, a pedido de Rilson
        Resinc           Reslop
        0,98 p/ 1,07     0,016 p/ 0,025
        0,84 p/ 1,21     0,022 p/ 0,032
        Move Resinc      Move Reslop
        0,67 p/ 0,86     0,014 p/ 0,022
        0,81 p/ 1,00     0,019 p/ 0,028
  for( CubaOpe = 301; CubaOpe <= 496; ++CubaOpe )
  {
 	Cuba = ConvCubOperScore(CubaOpe);
    AVC.User4[Cuba].lim_reslop1 = 0.0251e-6;
    AVC.User4[Cuba].lim_reslop2 = 0.0321e-6;
    AVC.User4[Cuba].lim_resinc1 = 1.071e-6;
    AVC.User4[Cuba].lim_resinc2 = 1.211e-6;
    AVC.User4[Cuba].lim_move_reslop1 = 0.0221e-6;
    AVC.User4[Cuba].lim_move_reslop2 = 0.0281e-6;
    AVC.User4[Cuba].lim_move_resinc1 = 0.861e-6;
    AVC.User4[Cuba].lim_move_resinc2 = 1.001e-6;
  }

	08/11/2010 08:00h - Logica de smart feed para os fornos 301-316 e 381-396.
                 Estava habilitado para os fornos 317-324 e 373-380. Pedido de
                 Rilson
    i=0;
	for( CubaOpe = 373; CubaOpe <=396; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.ParUser1[Cuba].off_queb_f = i;
	  AVC.ParUser1[Cuba].off_queb_b = 1798 - i;
	  i += 38; 
	}

	i += 12; 
	for( CubaOpe = 301; CubaOpe <=324; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.ParUser1[Cuba].off_queb_f = i;
	  AVC.ParUser1[Cuba].off_queb_b = 1798 - i;
	  i += 38; 
	}

	for( CubaOpe = 301; CubaOpe <=316; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User4[Cuba].hora_queb_ref = 9*3600;
	  AVC.User1[Cuba].tipo_forno_scb = 4;
	  AVC.User1[Cuba].salva_tipo_scb = 4; 
	  AVC.User4[Cuba].seq_normal[3] = 63;
	  AVC.User4[Cuba].int_scb_ae[3] = 1*MIN*SEC;
	  AVC.User4[Cuba].lim_queb_eq[3] = 6; 
	  AVC.User4[Cuba].sequencia_queb = 42;
	  AVC.User4[Cuba].lim_scb_qca = 4*MIN*SEC;
	  AVC.User3[Cuba].dur_inc_qca = 4*MIN*SEC;
	  AVC.User4[Cuba].lim_queb_scb = 2*MIN*SEC + 40*SEC;
	  AVC.ParUser1[Cuba].ativa_smart_feed = VERDADEIRO;
	  AVC.ParUser1[Cuba].move_dur_ae= 10;
	  AVC.ParUser1[Cuba].move_dur_pcb= 10;
	  AVC.ParUser1[Cuba].dur_analise_ae = 4*SEC;
	  AVC.ParUser1[Cuba].overfed = -0.0051e-6;
	  AVC.ParUser1[Cuba].s_overfed = 0.0061e-6;
	  AVC.ParUser1[Cuba].good_slope = 0.0121e-6;
	  AVC.ParUser1[Cuba].step_inc_up = 0.060;
	  AVC.ParUser1[Cuba].step_inc_down = 0.040;
	  AVC.ParUser1[Cuba].lim_move_ae = 30*SEC;
	  AVC.ParUser1[Cuba].lim_move_pcb = 1*MIN*SEC;
	  AVC.ParUser2[Cuba].lim_pcb = 6*MIN*SEC;
	  AVC.User1[Cuba].num_ciclo = 1;
	  AVC.User4[Cuba].lim_ae_longo = 8*60;
	}

	for( CubaOpe = 381; CubaOpe <=396; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User4[Cuba].hora_queb_ref = 9*3600;
	  AVC.User1[Cuba].tipo_forno_scb = 4;
	  AVC.User1[Cuba].salva_tipo_scb = 4;
	  AVC.User4[Cuba].seq_normal[3] = 63;
	  AVC.User4[Cuba].int_scb_ae[3] = 1*MIN*SEC;
	  AVC.User4[Cuba].lim_queb_eq[3] = 6; 
	  AVC.User4[Cuba].sequencia_queb = 42;
	  AVC.User4[Cuba].lim_scb_qca = 4*MIN*SEC;
	  AVC.User3[Cuba].dur_inc_qca = 4*MIN*SEC;
	  AVC.User4[Cuba].lim_queb_scb = 2*MIN*SEC + 40*SEC;
	  AVC.ParUser1[Cuba].ativa_smart_feed = VERDADEIRO;
	  AVC.ParUser1[Cuba].move_dur_ae= 10;
	  AVC.ParUser1[Cuba].move_dur_pcb= 10;
	  AVC.ParUser1[Cuba].dur_analise_ae = 4*SEC;
	  AVC.ParUser1[Cuba].overfed = -0.0051e-6;
	  AVC.ParUser1[Cuba].s_overfed = 0.0061e-6;
	  AVC.ParUser1[Cuba].good_slope = 0.0121e-6;
	  AVC.ParUser1[Cuba].step_inc_up = 0.060;
	  AVC.ParUser1[Cuba].step_inc_down = 0.040;
	  AVC.ParUser1[Cuba].lim_move_ae = 30*SEC;
	  AVC.ParUser1[Cuba].lim_move_pcb = 1*MIN*SEC;
	  AVC.ParUser2[Cuba].lim_pcb = 6*MIN*SEC;
	  AVC.User1[Cuba].num_ciclo = 1;
	  AVC.User4[Cuba].lim_ae_longo = 8*60;
	}

	for( CubaOpe = 317; CubaOpe <=380; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.ParUser1[Cuba].lim_move_ae = 30*SEC;
	  AVC.ParUser1[Cuba].lim_move_pcb = 1*MIN*SEC;
	}

    08/11/10 09:00h - Intervalo p/ o primeiro sopro. Pedido p/ Rilson
	for( CubaOpe = 301; CubaOpe <=396; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User4[Cuba].int_iniae_sopro = 90;
	}

	08/11/10 10:49h - Intervalo entre AE e SCB a pedido de Rilson
	for( CubaOpe = 301; CubaOpe <=396; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User4[Cuba].int_scb_ae[3] = 30*SEC;
	}

	08/11/10 11:17h - Intervalo entre previsoes com quebrada a pedido de Rilson
	for( CubaOpe = 301; CubaOpe <=396; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.ParUser2[Cuba].lim_pcb = 4*MIN*SEC;
	}

	08/11/10 11:32h Atualizar lim_pcb_pcb porque os fornos abaixo estao 
					desligados 
	  Cuba = ConvCubOperScore(301);
	  AVC.User4[Cuba].lim_pcb_pcb = 4*MIN*SEC;
	  Cuba = ConvCubOperScore(314);
	  AVC.User4[Cuba].lim_pcb_pcb = 4*MIN*SEC;
	  Cuba = ConvCubOperScore(319);
	  AVC.User4[Cuba].lim_pcb_pcb = 4*MIN*SEC;

	08/11/10 11:36h - Acrescimo apos previsao a pedido de Rilson
	for( CubaOpe = 301; CubaOpe <=396; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.ParUser2[Cuba].inc_apos_pcb = 200;
	}

	08/11/10 12:15h Desativado levantamento de camisa a pedido de Rilson
	for( CubaOpe = 301; CubaOpe <=396; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  EST_AVC(Cuba).Est.levcam_ativo = FALSO;
	}

	09/11/10 08:15h Atualizar var. hora_levcam_on p/ manter levantamento de
                    camisa desabilitado (Obs: Pelo programa de operacao, so 
                    desabilita por 9 dias ). Forno 316, foi habilitado, dia 
                    08/11/10 12:50h

	 -- inicializa 09/11/10 00:00:00 
	memset( &DataTm, 0x00, sizeof( struct tm ));
	DataTm.tm_sec = 0;
	DataTm.tm_min = 0;
	DataTm.tm_hour = 0;
	DataTm.tm_mday = 9;
	DataTm.tm_mon = 10;
	DataTm.tm_year = 110;
	hora_qca = mktime(&DataTm); converte para time_t 
	hora_qca += (365*NUM_SEGUNDOS_DIA);  Atribui 09/11/2011 00:00:00 

	for( CubaOpe = 301; CubaOpe <=315; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_levcam_on = hora_qca;
	}

	for( CubaOpe = 317; CubaOpe <=396; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_levcam_on = hora_qca;
	}

	  Cuba = ConvCubOperScore(315);
	  AVC.User1[Cuba].num_queb_ciclo = 6;
	  AVC.User1[Cuba].ult_ciclo = VERDADEIRO;

	16/11/10 11:02h Atualizar var. hora_levcam_on p/ manter levantamento de
                    camisa desabilitado (Obs: Pelo programa de operacao, so 
                    desabilita por 9 dias ). Alguns fornos foram habilitados
					Pedido por Rilson

	 -- inicializa 16/11/10 00:00:00 
	memset( &DataTm, 0x00, sizeof( struct tm ));
	DataTm.tm_sec = 0;
	DataTm.tm_min = 0;
	DataTm.tm_hour = 0;
	DataTm.tm_mday = 16;
	DataTm.tm_mon = 10;
	DataTm.tm_year = 110;
	hora_qca = mktime(&DataTm); /converte para time_t
	hora_qca += (365*NUM_SEGUNDOS_DIA);   Atribui 16/11/2011 00:00:00

	for( CubaOpe = 301; CubaOpe <=396; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_levcam_on = hora_qca;
	  EST_AVC(Cuba).Est.levcam_ativo = FALSO;
	}

	19/11/10 08:35h Atualizar var. hora_levcam_on p/ manter levantamento de
                    camisa desabilitado (Obs: Pelo programa de operacao, so 
                    desabilita por 9 dias ). Alguns fornos foram habilitados
					Pedido por Rilson


	 -- inicializa 19/11/11 00:00:00 
	memset( &DataTm, 0x00, sizeof( struct tm ));
	DataTm.tm_sec = 0;
	DataTm.tm_min = 0;
	DataTm.tm_hour = 0;
	DataTm.tm_mday = 19;
	DataTm.tm_mon = 10;
	DataTm.tm_year = 111;
	hora_qca = mktime(&DataTm); converte para time_t 

	for( CubaOpe = 301; CubaOpe <=396; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_levcam_on = hora_qca;
	  EST_AVC(Cuba).Est.levcam_ativo = FALSO;
	}

	Logica Previsao HS - p/ simular alterei os limites de reslop
	for( CubaOpe = 101; CubaOpe <=288; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
      AVC.User4[Cuba].lim_reslop1 = 0.0012*1e-6;
      AVC.User4[Cuba].lim_reslop2 = 0.0016*1e-6;
      AVC.User4[Cuba].lim_move_reslop1 = 0.001*1e-6;
      AVC.User4[Cuba].lim_move_reslop2 = 0.0012*1e-6;
	}

	23/11/10 09:45h - Logica Previsao HS, a pedido de Gilberto Silva
	for( CubaOpe = 101; CubaOpe <=288; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
      AVC.User4[Cuba].lim_reslop1 = 0.04*1e-6;
      AVC.User4[Cuba].lim_reslop2 = 0.05*1e-6;
      AVC.User4[Cuba].lim_move_reslop1 = 0.03*1e-6;
      AVC.User4[Cuba].lim_move_reslop2 = 0.04*1e-6;
	}

	23/11/10 10:51 h - Alterado a zona de movimentacao
								
				  move_band_inf 		9.82			8.00
				  move_band_sup 		8.18			9.00
				  pre_desvio_band_inf	8.98			7.68
				 	 para sala 3, a pedido de Gilberto Silva

	 -- inicializa 23/11/11 00:00:00 
	memset( &DataTm, 0x00, sizeof( struct tm ));
	DataTm.tm_sec = 0;
	DataTm.tm_min = 0;
	DataTm.tm_hour = 0;
	DataTm.tm_mday = 23;
	DataTm.tm_mon = 10;
	DataTm.tm_year = 111;
	hora_qca = mktime(&DataTm);

	for( CubaOpe = 301; CubaOpe <=396; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  AVC.User3[Cuba].hora_levcam_on = hora_qca;
	  EST_AVC(Cuba).Est.levcam_ativo = FALSO;
	}

	26/11/10 09:34h Varios fornos estavam sem mover, coloquei p/ MOVER a pedido
                    de Gilberto Silva
	for( CubaOpe = 101; CubaOpe <=288; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  if (EST_AVC(Cuba).Est.move_reslop eq VERDADEIRO)
	  {
		AVC.User3[Cuba].hora_move_reslop = AVC.User3[Cuba].hora_aepnb;
		EST_AVC(Cuba).Est.move_reslop = FALSO;
	  }
	}
	  Cuba = ConvCubOperScore(144);
	  EST_AVC(Cuba).Est.ocorreu_aepnb = FALSO;
	  Cuba = ConvCubOperScore(144);
	  EST_AVC(Cuba).Est.ocorreu_aepnb = FALSO;

	26/11/10 15:09h Resetar ocorreu_aepnb
	for( CubaOpe = 101; CubaOpe <=288; ++CubaOpe )
	{
	  Cuba = ConvCubOperScore(CubaOpe);
	  if (EST_AVC(Cuba).Est.ocorreu_aepnb eq VERDADEIRO and
		  AVC.User3[Cuba].hora_aepnb ne AVC.User3[Cuba].hora_move_off_aepnb)
		EST_AVC(Cuba).Est.ocorreu_aepnb = FALSO;
	}
	29/11/10 10:05 - Logica Previsao HS, a pedido de Gilberto Silva

	for (CubaOpe = 501; CubaOpe <=675; CubaOpe++)
	{	
	  Cuba = ConvCubOperScore(CubaOpe);
	  printf(" \n Estado Atual Cuba %d %d = %d \n",CubaOpe, Cuba ,  ((AVC.Cleit[Cuba].EstadoIO >> (AVC.Abs[Cuba].BitChaveLocRem - 1)) andb 1));
	}

	  EST_AVC(Cuba).TabOpeAtiva = FALSO;
	  EST_AVC(Cuba).EstadoCuba = CUBA_NORMAL;
	  EST_AVC(Cuba).ForaLeitura = FALSO;
	  EST_AVC(Cuba).ForaControle = FALSO;
	  AVC.Param[Cuba].NumAlgCtr = 1;	  
  	  EST_AVC(Cuba).EfeitoMove=FALSO;
 	  EST_AVC(Cuba).EfeitoEa=FALSO;
  	  EST_AVC(Cuba).EfeitoQueb=FALSO;


  CubaOpe = 311;
  Cuba = ConvCubOperScore(CubaOpe);
  printf("\n Falha Cima : %f \n" , SUPERV_AVC(Cuba).Sup.kwcimafalhamov);
  printf(" Falha Baixo : %f \n" , SUPERV_AVC(Cuba).Sup.kwbaixofalhamov);
  printf(" Rede Cima : %f \n" , SUPERV_AVC(Cuba).Sup.kwcimaforarede);
  printf(" Rede Baixo : %f \n" , SUPERV_AVC(Cuba).Sup.kwbaixoforarede);
  printf(" Chav Cima : %f \n" , SUPERV_AVC(Cuba).Sup.kwcimamanuallocal);
  printf(" Chav Baixo : %f \n" , SUPERV_AVC(Cuba).Sup.kwbaixomanuallocal);
  printf(" Geral Cima : %f \n" , SUPERV_AVC(Cuba).Sup.kwcimageral);
  printf(" Geral Baixo : %f \n" , SUPERV_AVC(Cuba).Sup.kwbaixogeral);
  printf(" FORAREDE : %d, %d \n", EST_AVC(Cuba).RtuStatus, RTU_ON_LINE);


 printf("\n Red: %d ", Comum->IdentReducao);
 CubaOpe = 101;
 Cuba = ConvCubOperScore(CubaOpe);

 printf("\n EstPrincDia: %d",	SUPERV_AVC(Cuba).EstPrincDia);
 printf("\n VSetPointDia: %f",	SUPERV_AVC(Cuba).VSetPointDia);
 printf("\n EaNumDia   : %d",	SUPERV_AVC(Cuba).EaNumDia);
 printf("\n EaVMaxDia  : %f",	SUPERV_AVC(Cuba).EaVMaxDia);
 printf("\n RDiaBruta  : %f",	SUPERV_AVC(Cuba).RDiaBruta);
 printf("\n IncTotDia  : %f",	SUPERV_AVC(Cuba).IncTotDia);
 printf("\n RRapNormDia: %f",	SUPERV_AVC(Cuba).RRapNormDia * 1000);
 printf("\n RLentNormDia: %f",	SUPERV_AVC(Cuba).RLentNormDia* 1000);
 printf("\n IAlvo      : %f",	SUPERV_AVC(Cuba).IAlvoCubaDia   );
 printf("\n BemfDia    : %f",	SUPERV_AVC(Cuba).BemfDia);
 printf("\n ICubaMedDia: %f",	SUPERV_AVC(Cuba).Sup.ICubaMedDia);


 CubaOpe = 301;
 Cuba = ConvCubOperScore(CubaOpe);

 printf("\n horaProxQueb: %d",	AVC.User2[Cuba].HoraProxQueb);
 printf("\n horainidia: %d",	AVL.Trab.HoraIniDia);
 printf("\n IntervQueb: %d",	AVC.ParUser1[Cuba].IntervQuebProg);
 printf("\n HoraRefQueb: %d",	AVC.ParUser1[Cuba].HoraRefQuebProg);

for(CubaOpe = 0; CubaOpe < 2100; CubaOpe++)
{
  Cuba = ConvCubOperScore(CubaOpe);
  
  EST_AVC(Cuba).EstadoCuba = CUBA_NORMAL;
  EST_AVC(Cuba).ForaLeitura = FALSO;
  EST_AVC(Cuba).ForaControle = FALSO;
}


	sobe = ((AVC.Cleit[Cuba].EstadoIO >> ((AVC.Abs[Cuba].BitSubOuMovCamisaouM2)-1)) andb 1);
	desce= ((AVC.Cleit[Cuba].EstadoIO >> ((AVC.Abs[Cuba].BitDesCamOuPFAutoouM1)-1)) andb 1);
	quebrada = ((AVC.Cleit[Cuba].EstadoIO >> ((AVC.Abs[Cuba].BitChaveQueb)-1)) andb 1);
	printf("\nSobe Camisa : %d\n", ((AVC.Cleit[Cuba].EstadoIO >> ((AVC.Abs[Cuba].BitSubOuMovCamisaouM2)-1)) andb 1));
	printf("\nDesce Camisa : %d\n", ((AVC.Cleit[Cuba].EstadoIO >> ((AVC.Abs[Cuba].BitDesCamOuPFAutoouM1)-1)) andb 1));
	printf("\nQuebrada : %d\n", ((AVC.Cleit[Cuba].EstadoIO >> ((AVC.Abs[Cuba].BitChaveQueb)-1)) andb 1));


	for(;;)
	{
	  if( sobe ne ((AVC.Cleit[Cuba].EstadoIO >> ((AVC.Abs[Cuba].BitSubOuMovCamisaouM2)-1)) andb 1))
	  {
  		printf("EstadoIO : %i \n", AVC.Cleit[Cuba].EstadoIO);
	  	printf("\nSobe Camisa : %d\n", ((AVC.Cleit[Cuba].EstadoIO >> ((AVC.Abs[Cuba].BitSubOuMovCamisaouM2)-1)) andb 1));
	  }
	  if( desce ne ((AVC.Cleit[Cuba].EstadoIO >> ((AVC.Abs[Cuba].BitDesCamOuPFAutoouM1)-1)) andb 1))
	  {
	    printf("EstadoIO : %i \n", AVC.Cleit[Cuba].EstadoIO); 	
		printf("\nDesce Camisa : %d\n", ((AVC.Cleit[Cuba].EstadoIO >> ((AVC.Abs[Cuba].BitDesCamOuPFAutoouM1)-1)) andb 1));
	  }
	  if( quebrada ne ((AVC.Cleit[Cuba].EstadoIO >> ((AVC.Abs[Cuba].BitChaveQueb)-1)) andb 1))
	  {
	    printf("EstadoIO : %i \n", AVC.Cleit[Cuba].EstadoIO); 	
		printf("\nQuebrada : %d\n", ((AVC.Cleit[Cuba].EstadoIO >> ((AVC.Abs[Cuba].BitChaveQueb)-1)) andb 1));
	  }
	}


    CubaOpe = 1236;
    Cuba = ConvCubOperScore(CubaOpe);

    printf("EstadoIO : %i \n", AVC.Cleit[Cuba].EstadoIO);

	printf("\nBitSobeAnodo : %d", AVC.Abs[Cuba].BitSobeAnodo);
	printf("\nBitDesceAnodo : %d", AVC.Abs[Cuba].BitDesceAnodo);
	printf("\nBitLampEa : %d", AVC.Abs[Cuba].BitLampEa);
	printf("\nBitLampRec : %d", AVC.Abs[Cuba].BitLampRec);
	printf("\nBitAvPistaoAQuebA : %d", AVC.Abs[Cuba].BitAvPistaoAQuebA);
	printf("\nBitRecPistaoAQuebB : %d", AVC.Abs[Cuba].BitRecPistaoAQuebB);
	printf("\nBitAvPistaoBQuebC : %d", AVC.Abs[Cuba].BitAvPistaoBQuebC);
	printf("\nBitRecPistaoBouM2QuebD : %d", AVC.Abs[Cuba].BitRecPistaoBouM2QuebD);
	printf("\nBitSopro : %d", AVC.Abs[Cuba].BitSopro);
	printf("\nBitSobeCamisaouM1 : %d", AVC.Abs[Cuba].BitSobeCamisaouM1);
	printf("\nBitDescCamOuAvPCAlimA : %d", AVC.Abs[Cuba].BitDescCamOuAvPCAlimA);
	printf("\nBitRecuoPistCAlimB : %d", AVC.Abs[Cuba].BitRecuoPistCAlimB);
	printf("\nBitAvancoPistDAlimC : %d", AVC.Abs[Cuba].BitAvancoPistDAlimC);
	printf("\nBitRecuoPistDAlimD : %d", AVC.Abs[Cuba].BitRecuoPistDAlimD);
	printf("\nBitSireneEA : %d", AVC.Abs[Cuba].BitSireneEA);
	printf("\nBitLiberaMCruzeiro : %d", AVC.Abs[Cuba].BitLiberaMCruzeiro);
	printf("\nBitChaveQueb : %d", AVC.Abs[Cuba].BitChaveQueb);
	printf("\nBitChaveCorr : %d", AVC.Abs[Cuba].BitChaveCorr);
	printf("\nBitChaveLocRem : %d", AVC.Abs[Cuba].BitChaveLocRem);
	printf("\nBitResetEa : %d", AVC.Abs[Cuba].BitResetEa);
	printf("\nBitSubiuAnodo : %d", AVC.Abs[Cuba].BitSubiuAnodo);
	printf("\nBitDesceuAnodo : %d", AVC.Abs[Cuba].BitDesceuAnodo);
	printf("\nBitSubOuMovCamisaouM2 : %d", AVC.Abs[Cuba].BitSubOuMovCamisaouM2);
	printf("\nBitDesCamOuPFAutoouM1 : %d", AVC.Abs[Cuba].BitDesCamOuPFAutoouM1);
	printf("\nBitCheckUp : %d", AVC.Abs[Cuba].BitCheckUp);
	printf("\nBitTrocaPinos : %d", AVC.Abs[Cuba].BitTrocaPinos);
	printf("\nBitSoprou : %d", AVC.Abs[Cuba].BitSoprou);
	printf("\nBitReleFalhaMM : %d", AVC.Abs[Cuba].BitReleFalhaMM);
	printf("\nBitChaveMCruzeiro : %d", AVC.Abs[Cuba].BitChaveMCruzeiro);

    for(CubaOpe = 101; CubaOpe <= 175; CubaOpe++)
	{
      Cuba = ConvCubOperScore(CubaOpe);
	  AVC.Abs[Cuba].BitDesCamOuPFAutoouM1 = 255;	
	  printf("\n BitDesCam %d = %d \n",CubaOpe, AVC.Abs[Cuba].BitDesCamOuPFAutoouM1);
	}
    for(CubaOpe = 201; CubaOpe <= 275; CubaOpe++)
	{
      Cuba = ConvCubOperScore(CubaOpe);
	  AVC.Abs[Cuba].BitDesCamOuPFAutoouM1 = 255;	
	  printf("\n BitDesCam %d = %d \n",CubaOpe, AVC.Abs[Cuba].BitDesCamOuPFAutoouM1);
	}

  CubaOpe = 1522;	
  Cuba = ConvCubOperScore(CubaOpe);
  EST_AVC(Cuba).Est.AbortaAjuste = 0;

  i=0;
  for(CubaOpe = 2009; CubaOpe >= 2001 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    i += 50;
  }

  for(CubaOpe = 2019; CubaOpe >= 2010 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    i += 50;
  }
  for(CubaOpe = 2029; CubaOpe >= 2020 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    i += 50;
  }
  for(CubaOpe = 2039; CubaOpe >= 2030 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    i += 50;
  }
  for(CubaOpe = 2049; CubaOpe >= 2040 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    i += 50;
  }


  CubaOpe = 249;	
  Cuba = ConvCubOperScore(CubaOpe);
  EST_AVC(Cuba).RuidoLent=FALSO;  
  AVC.Ruido[Cuba].RlentCContVal=0;
  AVC.Ruido[Cuba].Rlent6Hs=0; 
  AVC.Ruido[Cuba].Rlent48Hs=0; 
  AVC.Ruido[Cuba].TipoRLent=SEM_RUIDO;
  for(Amostra=0; Amostra < N_AMOSTRAS_RLENT; ++Amostra)
	AVC.Ruido[Cuba].VetRlent[Amostra]=0;
  AVC.Ccont[Cuba].IncRlent=0;


  i=0;
  for(CubaOpe = 1309; CubaOpe >= 1301 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe + 200);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    i += 60;
  }

  for(CubaOpe = 1318; CubaOpe >= 1310 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe + 200);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    i += 60;
  }
  for(CubaOpe = 1327; CubaOpe >= 1319 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe + 200);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    i += 60;
  }
  for(CubaOpe = 1341; CubaOpe >= 1328 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe + 200);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    i += 60;
  }

  i=0;
  for(CubaOpe = 1301; CubaOpe <= 1341; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    Cuba = ConvCubOperScore(CubaOpe + 200);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    i += 60;

  }  


  for(CubaOpe = 1418; CubaOpe >= 1410 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    Cuba = ConvCubOperScore(CubaOpe + 200);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    i += 60;
  }
  for(CubaOpe = 1427; CubaOpe >= 1419 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    Cuba = ConvCubOperScore(CubaOpe + 200);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    i += 60;
  }
  for(CubaOpe = 1441; CubaOpe >= 1428 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    Cuba = ConvCubOperScore(CubaOpe + 200);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    i += 60;
  }

  i=0;
  for(CubaOpe = 1401; CubaOpe <= 1441; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe + 200);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    i += 60;

  }  

  printf("DataOperacional : %d", AVL.Trab.DataOperacional);
  AVL.Trab.DataOperacional -= (10 * (60*60*24));
  printf("DataOperacional : %d", AVL.Trab.DataOperacional);
   
  CubaOpe = 1305;
  Cuba = ConvCubOperScore(CubaOpe);
  printf("HoraUltMovManual = %d", AVC.User2[Cuba].HoraUltMovPainel);


  i=0;
  for(CubaOpe = 318; CubaOpe >= 301 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    Cuba = ConvCubOperScore(CubaOpe+100);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    i += 40;
  }

  for(CubaOpe = 336; CubaOpe >= 319 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    Cuba = ConvCubOperScore(CubaOpe+100);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    i += 40;
  }
  i=0;
  for(CubaOpe = 354; CubaOpe >= 337 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    Cuba = ConvCubOperScore(CubaOpe+100);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    i += 40;
  }

  i = 0;
  for(CubaOpe = 301; CubaOpe <= 336 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe+100);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    i += 40;
  }

  i = 0;
  for(CubaOpe = 337; CubaOpe <= 380 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe+100);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    i += 40;
  }

  CubaOpe = 301;
  Cuba = ConvCubOperScore(CubaOpe);
  printf("HoraRefQuebProg %d \n",AVC.ParUser1[Cuba].HoraRefQuebProg); 
  i = (time(NULL) - AVC.ParUser1[Cuba].HoraRefQuebProg); 
  printf(" Primeira conta %d \n", i);
  i = i + (AVC.ParUser1[Cuba].IntervQuebProg / 2);
  printf(" Segunda conta %d \n", i);
  i = i / AVC.ParUser1[Cuba].IntervQuebProg;
  printf(" Terceira conta %d \n", i);
  printf(" Quarta conta %d \n", i + (AVC.ParUser1[Cuba].LadoRefQueb - 1));
  printf(" Quinta conta %d \n", i % 2); 

  i = 0;

  for(CubaOpe = 1701; CubaOpe <= 1749 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe+100);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    Cuba = ConvCubOperScore(CubaOpe+200);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe+300);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    i += 24;
  }

  i = 0;

  for(CubaOpe = 1749; CubaOpe >= 1701 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    Cuba = ConvCubOperScore(CubaOpe+100);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe+200);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    Cuba = ConvCubOperScore(CubaOpe+300);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    i += 24;
  }

  i = 7;
  for(CubaOpe = 1701; CubaOpe <= 2049 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].NumCicRes4s = i;
	i++;
	if (i > 9)
	  i = 7;

  }

  i=0;
  CubaOpe = 765;
  Cuba = ConvCubOperScore(CubaOpe);
  printf("\n HoraForaDB : %d \n", AVC.User2[Cuba].HoraForaDB);
  printf("\n HoraProxQueb  : %d \n", AVC.User2[Cuba].HoraProxQueb);
  printf("\n HoraUltQueb : %d \n", AVC.User2[Cuba].HoraUltQueb);
  printf("\n HoraProxQuebReal  : %d \n", AVC.User2[Cuba].HoraProxQuebReal);
  printf("\n HoraUltQuebReal  : %d \n", AVC.User2[Cuba].HoraUltQuebReal);
  printf("\n HoraIniDia  : %d \n", AVL.Trab.HoraIniDia);
  printf("\n HoraAtual: %d \n",time(NULL));


  i = 7;
  for(CubaOpe = 701; CubaOpe <= 880 ; CubaOpe++)
  {													

	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].NumCicRes4s = i;
	i++;
	if (i > 9)
	  i = 7;

  }

 i=0;
 CubaOpe = 509;
 Cuba = ConvCubOperScore(CubaOpe);

 for(i=0; i<11; i++)
 {
	printf("\nContPrevEA %d   %i\n", i , SUPERV_AVC(Cuba).ContPrevEa[i]);
	printf("\nDurEA %d   %i\n", i , SUPERV_AVC(Cuba).DurEa[i]);

 }

  i=0;
  for(CubaOpe = 1301; CubaOpe >= 1641 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
	i = AVC.ParUser1[Cuba].DelayLadoQueb1;
    AVC.ParUser1[Cuba].DelayLadoQueb1 = AVC.ParUser1[Cuba].DelayLadoQueb2;
	AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
  }


  CubaOpe = 925;	
  Cuba = ConvCubOperScore(CubaOpe);
  EST_AVC(Cuba).RuidoLent=FALSO;  
  AVC.Ruido[Cuba].RlentCContVal=0;
  AVC.Ruido[Cuba].Rlent6Hs=0; 
  AVC.Ruido[Cuba].Rlent48Hs=0; 
  AVC.Ruido[Cuba].TipoRLent=SEM_RUIDO;
  for(i=0; i < N_AMOSTRAS_RLENT; ++i)
	AVC.Ruido[Cuba].VetRlent[i]=0;
  AVC.Ccont[Cuba].IncRlent=0;

  CubaOpe = 1031;	
  Cuba = ConvCubOperScore(CubaOpe);
  EST_AVC(Cuba).RuidoLent=FALSO;  
  AVC.Ruido[Cuba].RlentCContVal=0;
  AVC.Ruido[Cuba].Rlent6Hs=0; 
  AVC.Ruido[Cuba].Rlent48Hs=0; 
  AVC.Ruido[Cuba].TipoRLent=SEM_RUIDO;
  for(i=0; i < N_AMOSTRAS_RLENT; ++i)
	AVC.Ruido[Cuba].VetRlent[i]=0;
  AVC.Ccont[Cuba].IncRlent=0;


  CubaOpe = 1106;	
  Cuba = ConvCubOperScore(CubaOpe);
  EST_AVC(Cuba).RuidoLent=FALSO;  
  AVC.Ruido[Cuba].RlentCContVal=0;
  AVC.Ruido[Cuba].Rlent6Hs=0; 
  AVC.Ruido[Cuba].Rlent48Hs=0; 
  AVC.Ruido[Cuba].TipoRLent=SEM_RUIDO;
  for(i=0; i < N_AMOSTRAS_RLENT; ++i)
	AVC.Ruido[Cuba].VetRlent[i]=0;
  AVC.Ccont[Cuba].IncRlent=0;


  CubaOpe = 1107;	
  Cuba = ConvCubOperScore(CubaOpe);
  EST_AVC(Cuba).RuidoLent=FALSO;  
  AVC.Ruido[Cuba].RlentCContVal=0;
  AVC.Ruido[Cuba].Rlent6Hs=0; 
  AVC.Ruido[Cuba].Rlent48Hs=0; 
  AVC.Ruido[Cuba].TipoRLent=SEM_RUIDO;
  for(i=0; i < N_AMOSTRAS_RLENT; ++i)
	AVC.Ruido[Cuba].VetRlent[i]=0;
  AVC.Ccont[Cuba].IncRlent=0;


  CubaOpe = 1108;	
  Cuba = ConvCubOperScore(CubaOpe);
  EST_AVC(Cuba).RuidoLent=FALSO;  
  AVC.Ruido[Cuba].RlentCContVal=0;
  AVC.Ruido[Cuba].Rlent6Hs=0; 
  AVC.Ruido[Cuba].Rlent48Hs=0; 
  AVC.Ruido[Cuba].TipoRLent=SEM_RUIDO;
  for(i=0; i < N_AMOSTRAS_RLENT; ++i)
	AVC.Ruido[Cuba].VetRlent[i]=0;
  AVC.Ccont[Cuba].IncRlent=0;

 i = 0;

  for(CubaOpe = 1301; CubaOpe <= 1341 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 960 - i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe+100);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 960 - i;
	i+=24;
  }

 i = 0;
 CubaOpe = 1301;
  for(CubaOpe = 1301; CubaOpe <= 1341 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
	i = i + AVC.Cleit[Cuba].Vinst;
    printf("\n Tensao Forno : %f", AVC.Cleit[Cuba].Vinst);
  }
  for(CubaOpe = 1401; CubaOpe <= 1441 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
	i = i + AVC.Cleit[Cuba].Vinst;
    printf("\n Tensao Forno : %f", AVC.Cleit[Cuba].Vinst);
  }
  for(CubaOpe = 1501; CubaOpe <= 1541 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
	i = i + AVC.Cleit[Cuba].Vinst;
    printf("\n Tensao Forno : %f", AVC.Cleit[Cuba].Vinst);
  }
  for(CubaOpe = 1601; CubaOpe <= 1641 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
	i = i + AVC.Cleit[Cuba].Vinst;
    printf("\n Tensao Forno : %f", AVC.Cleit[Cuba].Vinst);
  }

  printf("\n Tensao Somada : %f", i);
  printf("\n Tensao Linha  : %f", AVL.VLinhaInst);

  printf("\n NCIC : %d \n ", AVL.Par.NCic4sEaLinha);

 // AVL.Par.NCic4sEaLinha = 0;

//	AVL.Trab.DataImport = 0;

 i = 0;

  for(CubaOpe = 1701; CubaOpe <= 1749 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 1152 - i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe+100);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 1152 - i;

    Cuba = ConvCubOperScore(CubaOpe+200);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 1152 - i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe+300);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 1152 - i;

	i+=24;
  }

i=0;
	  CubaOpe = 709;
	  Cuba = ConvCubOperScore(CubaOpe);

	  printf("\n HoraIniDia	 = %d \n", AVL.Trab.HoraIniDia);

	  printf("\n HoraDiaAtual	 = %d \n", 
	abs(time(NULL) - (AVL.Trab.HoraIniDia + AVC.ParUser1[Cuba].HoraRefCorr)));
	  printf("\n HoraDiaAnterior	 = %d \n", 
	abs(time(NULL) - (AVL.Trab.HoraIniDia - 86400 + AVC.ParUser1[Cuba].HoraRefCorr)));
	  printf("\n HoraDiaSeguinte	 = %d \n", 
	abs(time(NULL) - (AVL.Trab.HoraIniDia + 86400 + AVC.ParUser1[Cuba].HoraRefCorr)));

	  printf("\n HoraRef = %d \n",AVC.ParUser1[Cuba].HoraRefCorr);


i=0;
	  CubaOpe = 709;

  for(CubaOpe = 701; CubaOpe <= 880 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].EaPrevDeriv = 0.00000075;
	AVC.Param[Cuba].DerivInibeMovAlta = 0.00000065;
	AVC.Param[Cuba].EaPrevDerivFim = 0.00000060;
  }


  i=0;

  CubaOpe=102;
  Cuba = ConvCubOperScore(CubaOpe);
  printf("\n EstadoSireneSirene = %i \n", AVL.Trab.EstadoSireneSala);
  printf("\n HoraAlarmeSala = %d \n", AVL.Trab.HoraAlarmeSala);
  printf("\n AlarmeSala = %i \n", AVL.Trab.AlarmeSala);
  ComandaSaidaORem(0,DESLIGAR,9,-1);
  ComandaSaidaORem(1,DESLIGAR,9,-1);


 i = 0;

  for(CubaOpe = 1701; CubaOpe <= 1749 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 2640 - i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe+200);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 2640 - i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
	i += 55;
  }

  i = 0;
  for(CubaOpe = 1801; CubaOpe <= 1849 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 2640 - i;
    Cuba = ConvCubOperScore(CubaOpe+200);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 2640 - i;
	i += 55;
  }


  i=0;

  CubaOpe=337;
//  for(CubaOpe = 1901; CubaOpe <= 2049 ; CubaOpe++)
//  {
     Cuba = ConvCubOperScore(CubaOpe);


    CubaOpe = 337;
    Cuba = ConvCubOperScore(CubaOpe);

    printf("EstadoIO : %i \n", AVC.Cleit[Cuba].EstadoIO);

	printf("\nBitSobeAnodo : %d", AVC.Abs[Cuba].BitSobeAnodo);
	printf("\nBitDesceAnodo : %d", AVC.Abs[Cuba].BitDesceAnodo);
	printf("\nBitLampEa : %d", AVC.Abs[Cuba].BitLampEa);
	printf("\nBitLampRec : %d", AVC.Abs[Cuba].BitLampRec);
	printf("\nBitAvPistaoAQuebA : %d", AVC.Abs[Cuba].BitAvPistaoAQuebA);
	printf("\nBitRecPistaoAQuebB : %d", AVC.Abs[Cuba].BitRecPistaoAQuebB);
	printf("\nBitAvPistaoBQuebC : %d", AVC.Abs[Cuba].BitAvPistaoBQuebC);
	printf("\nBitRecPistaoBouM2QuebD : %d", AVC.Abs[Cuba].BitRecPistaoBouM2QuebD);
	printf("\nBitSopro : %d", AVC.Abs[Cuba].BitSopro);
	printf("\nBitSobeCamisaouM1 : %d", AVC.Abs[Cuba].BitSobeCamisaouM1);
	printf("\nBitDescCamOuAvPCAlimA : %d", AVC.Abs[Cuba].BitDescCamOuAvPCAlimA);
	printf("\nBitRecuoPistCAlimB : %d", AVC.Abs[Cuba].BitRecuoPistCAlimB);
	printf("\nBitAvancoPistDAlimC : %d", AVC.Abs[Cuba].BitAvancoPistDAlimC);
	printf("\nBitRecuoPistDAlimD : %d", AVC.Abs[Cuba].BitRecuoPistDAlimD);
	printf("\nBitSireneEA : %d", AVC.Abs[Cuba].BitSireneEA);
	printf("\nBitLiberaMCruzeiro : %d", AVC.Abs[Cuba].BitLiberaMCruzeiro);
	printf("\nBitChaveQueb : %d", AVC.Abs[Cuba].BitChaveQueb);
	printf("\nBitChaveCorr : %d", AVC.Abs[Cuba].BitChaveCorr);
	printf("\nBitChaveLocRem : %d", AVC.Abs[Cuba].BitChaveLocRem);
	printf("\nBitResetEa : %d", AVC.Abs[Cuba].BitResetEa);
	printf("\nBitSubiuAnodo : %d", AVC.Abs[Cuba].BitSubiuAnodo);
	printf("\nBitDesceuAnodo : %d", AVC.Abs[Cuba].BitDesceuAnodo);
	printf("\nBitSubOuMovCamisaouM2 : %d", AVC.Abs[Cuba].BitSubOuMovCamisaouM2);
	printf("\nBitDesCamOuPFAutoouM1 : %d", AVC.Abs[Cuba].BitDesCamOuPFAutoouM1);
	printf("\nBitCheckUp : %d", AVC.Abs[Cuba].BitCheckUp);
	printf("\nBitTrocaPinos : %d", AVC.Abs[Cuba].BitTrocaPinos);
	printf("\nBitSoprou : %d", AVC.Abs[Cuba].BitSoprou);
	printf("\nBitReleFalhaMM : %d", AVC.Abs[Cuba].BitReleFalhaMM);
	printf("\nBitChaveMCruzeiro : %d", AVC.Abs[Cuba].BitChaveMCruzeiro);

//  }



  i = 0;
  for(CubaOpe = 1301; CubaOpe <= 1341 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 1000 - i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe+200);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 1000 - i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;

	i += 25;
  }

 i=0;
 printf(" \n TimerMcc %f \n ", AVL.Trab.TimerMcc);
 CubaOpe=101;
 Cuba = 101;


  i=0;
  for(CubaOpe = 901; CubaOpe <= 936 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 700 - i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe + 200);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 700 - i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
	i += 20;
  }

  i=0;
  for(CubaOpe = 937; CubaOpe <= 972 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 700 -i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe + 200);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 700 - i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
	i += 20;
  }


  i=0;
  for(CubaOpe = 1001; CubaOpe <= 1036 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 720 + i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 1420 - i;
    Cuba = ConvCubOperScore(CubaOpe + 200);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 720 + i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 1420 - i;
	i += 20;
  }

  i=0;
  for(CubaOpe = 1037; CubaOpe <= 1072 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 720 + i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 1420 - i;
    Cuba = ConvCubOperScore(CubaOpe + 200);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 720 + i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 1420 - i;
	i += 20;
  }

	i=0;
    
	CubaOpe=845;
  for(CubaOpe = 701; CubaOpe <= 780 ; CubaOpe++)
  {
	Cuba = ConvCubOperScore(CubaOpe);

	AVC.Abs[Cuba].BitTrocaPinos = 255;
	AVC.Abs[Cuba].BitReleFalhaMM = 4;
	printf("\n Cuba : %d \n", CubaOpe); 
  }

  for(CubaOpe = 801; CubaOpe <= 880 ; CubaOpe++)
  {
	Cuba = ConvCubOperScore(CubaOpe);

	AVC.Abs[Cuba].BitTrocaPinos = 255;
	AVC.Abs[Cuba].BitReleFalhaMM = 4;
	printf("\n Cuba : %d \n", CubaOpe); 
  }


  i=0;
  for(CubaOpe = 701; CubaOpe <= 736 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 700 - i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
	i += 20;
  }

  i=0;
  for(CubaOpe = 737; CubaOpe <= 780 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 860 - i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
	i += 20;
  }


  i=0;
  for(CubaOpe = 801; CubaOpe <= 836 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 700 - i;
	i += 20;
  }


  i=0;
  for(CubaOpe = 837; CubaOpe <= 880 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 860 - i;
	i += 20;
  }


  i=0;
  for(CubaOpe = 1701; CubaOpe <= 1749 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 1440 - i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 1470 + i;
    Cuba = ConvCubOperScore(CubaOpe + 200);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 1440 - i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 1470 + i;
	i += 30;
  }

   i=0;
  for(CubaOpe = 1801; CubaOpe <= 1849 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 1470 + i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 1440 - i;
    Cuba = ConvCubOperScore(CubaOpe + 200);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 1470 + i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 1440 - i;
	i += 30;
  }


 i=0;
 CubaOpe = 510;
 Cuba = ConvCubOperScore(CubaOpe);
 printf(" \n BSup %f \n ", AVC.User1[Cuba].BandaSupMovel * 1000000);
 printf(" \n Pulou %d \n ", AVC.User1[Cuba].PulouQuebProg);
 printf(" \n Est %d \n ", EST_AVC(Cuba).Est.BSupMovel);
 printf(" \n TAcres %d \n ", AVC.ParUser1[Cuba].TAcresBSupMovel);
 printf(" \n HoraProxQuebReal %d \n ", AVC.User2[Cuba].HoraProxQuebReal);
 printf(" \n HoraUltQueb %d \n ", AVC.Cleit[Cuba].HoraUltQueb);
 printf(" \n KSIncDeriv %f \n ", AVC.ParUser1[Cuba].SF_KSIncDeriv);
 printf("\n HoraAtual: %d \n",time(NULL));



  i=0;
  k=0;
  for(CubaOpe = 601; CubaOpe <= 636 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.Banho = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.Banho);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.Metal = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.Metal);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.Temperatura = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.Temperatura);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.Producao = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.Producao);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.BanhoFrio = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.BanhoFrio);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.CrioSint = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.CrioSint);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.CrioAciq = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.CrioAciq);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.CrioRecu = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.CrioRecu);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.Fluoreto = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.Fluoreto);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.Fluorita = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.Fluorita);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.Barrilha = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.Barrilha);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.OperarTurno = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.OperarTurno);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.Carvao = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.Carvao);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.Atrasado = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.Atrasado);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.FundoSujo = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.FundoSujo);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.Acidez = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.Acidez);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.FornoAbrindo = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.FornoAbrindo);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.VazioPasta = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.VazioPasta);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.Desfilamento = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.Desfilamento);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.AlturaAnodo = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.AlturaAnodo);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.Flanco = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.Flanco);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.QuedaCatodica = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.QuedaCatodica);
	printf("SUPERV_AVC(%d).Sup.CNF_SUP.QuedaAnodica = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.CNF_SUP.QuedaAnodica);
	printf("AVC.ParUser1[%d].HabilitaPF = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabilitaPF);
	printf("AVC.ParUser1[%d].Livre = %f \n", CubaOpe, AVC.ParUser1[Cuba].Livre);
	printf("AVC.ParUser1[%d].ConcNominal = %f \n", CubaOpe, AVC.ParUser1[Cuba].ConcNominal);
	printf("AVC.ParUser1[%d].DesvioCarga = %f \n", CubaOpe, AVC.ParUser1[Cuba].DesvioCarga);
	printf("AVC.ParUser1[%d].DesvioConNominal = %f \n", CubaOpe, AVC.ParUser1[Cuba].DesvioConNominal);
	printf("AVC.ParUser1[%d].TTipicoCheck = %d \n", CubaOpe, AVC.ParUser1[Cuba].TTipicoCheck);
	printf("AVC.ParUser1[%d].NumAcionaCheck = %d \n", CubaOpe, AVC.ParUser1[Cuba].NumAcionaCheck);
	printf("AVC.ParUser1[%d].LimMinCheck = %f \n", CubaOpe, AVC.ParUser1[Cuba].LimMinCheck);
	printf("AVC.ParUser1[%d].MassaBanho = %f \n", CubaOpe, AVC.ParUser1[Cuba].MassaBanho);
	printf("AVC.ParUser1[%d].TempoAvanco = %d \n", CubaOpe, AVC.ParUser1[Cuba].TempoAvanco);
	printf("AVC.ParUser1[%d].TempoInterv = %d \n", CubaOpe, AVC.ParUser1[Cuba].TempoInterv);
	printf("AVC.ParUser1[%d].TempoRecuo = %d \n", CubaOpe, AVC.ParUser1[Cuba].TempoRecuo);
	printf("AVC.ParUser1[%d].TempoCadFalta = %d \n", CubaOpe, AVC.ParUser1[Cuba].TempoCadFalta);
	printf("AVC.ParUser1[%d].MaxDeltaEfiCurr = %f \n", CubaOpe, AVC.ParUser1[Cuba].MaxDeltaEfiCurr);
	printf("AVC.ParUser1[%d].TaxaUnder = %f \n", CubaOpe, AVC.ParUser1[Cuba].TaxaUnder);
	printf("AVC.ParUser1[%d].TaxaOverNorm = %f \n", CubaOpe, AVC.ParUser1[Cuba].TaxaOverNorm);
	printf("AVC.ParUser1[%d].ConsumoResAlim = %f \n", CubaOpe, AVC.ParUser1[Cuba].ConsumoResAlim);
	printf("AVC.ParUser1[%d].MaxIntervCheck = %d \n", CubaOpe, AVC.ParUser1[Cuba].MaxIntervCheck);
	printf("AVC.ParUser1[%d].UnderProgIni = %f \n", CubaOpe, AVC.ParUser1[Cuba].UnderProgIni);
	printf("AVC.ParUser1[%d].IntervUnderProg = %d \n", CubaOpe, AVC.ParUser1[Cuba].IntervUnderProg);
	printf("AVC.ParUser1[%d].DeltaUnder = %f \n", CubaOpe, AVC.ParUser1[Cuba].DeltaUnder);
	printf("AVC.ParUser1[%d].OverOpcional = %d \n", CubaOpe, AVC.ParUser1[Cuba].OverOpcional);
	printf("AVC.ParUser1[%d].PercOverOp = %f \n", CubaOpe, AVC.ParUser1[Cuba].PercOverOp);
	printf("AVC.ParUser1[%d].KSuaveAlim = %f \n", CubaOpe, AVC.ParUser1[Cuba].KSuaveAlim);
	printf("AVC.ParUser1[%d].DerInitCheck = %f \n", CubaOpe, AVC.ParUser1[Cuba].DerInitCheck);
	printf("AVC.ParUser1[%d].MaxIntervEa = %d \n", CubaOpe, AVC.ParUser1[Cuba].MaxIntervEa);
	printf("AVC.ParUser1[%d].HabilitaOverEA = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabilitaOverEA);
	printf("AVC.ParUser1[%d].TaxaOverEA = %f \n", CubaOpe, AVC.ParUser1[Cuba].TaxaOverEA);
	printf("AVC.ParUser1[%d].DurNormCheck = %d \n", CubaOpe, AVC.ParUser1[Cuba].DurNormCheck);
	printf("AVC.ParUser1[%d].PolOrd = %d \n", CubaOpe, AVC.ParUser1[Cuba].PolOrd);
	printf("AVC.ParUser1[%d].Poly[11] = %f \n", CubaOpe, AVC.ParUser1[Cuba].Poly[11]);
	printf("AVC.ParUser1[%d].MinConc = %f \n", CubaOpe, AVC.ParUser1[Cuba].MinConc);
	printf("AVC.ParUser1[%d].MaxConc = %f \n", CubaOpe, AVC.ParUser1[Cuba].MaxConc);
	printf("AVC.ParUser1[%d].ConcValidCheck = %f \n", CubaOpe, AVC.ParUser1[Cuba].ConcValidCheck);
	printf("AVC.ParUser1[%d].MinIntervPF = %d \n", CubaOpe, AVC.ParUser1[Cuba].MinIntervPF);
	printf("AVC.ParUser1[%d].MaxOverCheck = %d \n", CubaOpe, AVC.ParUser1[Cuba].MaxOverCheck);
	printf("AVC.ParUser1[%d].MaxTOverEa = %d \n", CubaOpe, AVC.ParUser1[Cuba].MaxTOverEa);
	printf("AVC.ParUser1[%d].EstabQueb = %d \n", CubaOpe, AVC.ParUser1[Cuba].EstabQueb);
	printf("AVC.ParUser1[%d].MaxDerInitCheck = %f \n", CubaOpe, AVC.ParUser1[Cuba].MaxDerInitCheck);
	printf("AVC.ParUser1[%d].ConcHabMove = %f \n", CubaOpe, AVC.ParUser1[Cuba].ConcHabMove);
	printf("AVC.ParUser1[%d].HabilitaBarra = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabilitaBarra);
	printf("AVC.ParUser1[%d].TempoFixo = %d \n", CubaOpe, AVC.ParUser1[Cuba].TempoFixo);
	printf("AVC.ParUser1[%d].EfiCurrIni = %f \n", CubaOpe, AVC.ParUser1[Cuba].EfiCurrIni);
	printf("AVC.ParUser1[%d].MinDer = %f \n", CubaOpe, AVC.ParUser1[Cuba].MinDer);
	printf("AVC.ParUser1[%d].MaxDer = %f \n", CubaOpe, AVC.ParUser1[Cuba].MaxDer);
	printf("AVC.ParUser1[%d].DerAliment = %f \n", CubaOpe, AVC.ParUser1[Cuba].DerAliment);
	printf("AVC.ParUser1[%d].MinIntervQueb = %d \n", CubaOpe, AVC.ParUser1[Cuba].MinIntervQueb);
	printf("AVC.ParUser1[%d].IntervQueb = %d \n", CubaOpe, AVC.ParUser1[Cuba].IntervQueb);
	printf("AVC.ParUser1[%d].MaxNumQueb = %d \n", CubaOpe, AVC.ParUser1[Cuba].MaxNumQueb);
	printf("AVC.ParUser1[%d].TTerminaEa = %d \n", CubaOpe, AVC.ParUser1[Cuba].TTerminaEa);
	printf("AVC.ParUser1[%d].HabMoveSusp = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabMoveSusp);
	printf("AVC.ParUser1[%d].HabMovTrack = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabMovTrack);
	printf("AVC.ParUser1[%d].MaxEfiCurr = %f \n", CubaOpe, AVC.ParUser1[Cuba].MaxEfiCurr);
	printf("AVC.ParUser1[%d].MinEfiCurr = %f \n", CubaOpe, AVC.ParUser1[Cuba].MinEfiCurr);
	printf("AVC.ParUser1[%d].HabQPrev = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabQPrev);
	printf("AVC.ParUser1[%d].LimInfQPrevEa = %d \n", CubaOpe, AVC.ParUser1[Cuba].LimInfQPrevEa);
	printf("AVC.ParUser1[%d].LimSupQPrevEa = %d \n", CubaOpe, AVC.ParUser1[Cuba].LimSupQPrevEa);
	printf("AVC.ParUser1[%d].MaxQPrevEa = %d \n", CubaOpe, AVC.ParUser1[Cuba].MaxQPrevEa);
	printf("AVC.ParUser1[%d].NHorRefQPrev = %d \n", CubaOpe, AVC.ParUser1[Cuba].NHorRefQPrev);
	printf("AVC.ParUser1[%d].IntMinQQPrev = %d \n", CubaOpe, AVC.ParUser1[Cuba].IntMinQQPrev);
	printf("AVC.ParUser1[%d].HabAjCam = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabAjCam);
	printf("AVC.ParUser1[%d].HabNormFeedEa = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabNormFeedEa);
	printf("AVC.ParUser1[%d].LimMaxAjCam = %f \n", CubaOpe, AVC.ParUser1[Cuba].LimMaxAjCam);
	printf("AVC.ParUser1[%d].LimTAjMov = %f \n", CubaOpe, AVC.ParUser1[Cuba].LimTAjMov);
	printf("AVC.ParUser1[%d].IntAjCamCorr = %d \n", CubaOpe, AVC.ParUser1[Cuba].IntAjCamCorr);
	printf("AVC.ParUser1[%d].DifResAgarra = %f \n", CubaOpe, AVC.ParUser1[Cuba].DifResAgarra);
	printf("AVC.ParUser1[%d].NAjIntermCorr = %d \n", CubaOpe, AVC.ParUser1[Cuba].NAjIntermCorr);
	printf("AVC.ParUser1[%d].EstabCorr = %d \n", CubaOpe, AVC.ParUser1[Cuba].EstabCorr);
	printf("AVC.ParUser1[%d].TSuspLinhaD = %d \n", CubaOpe, AVC.ParUser1[Cuba].TSuspLinhaD);
	printf("AVC.ParUser1[%d].TSaiSuspLinhaD = %d \n", CubaOpe, AVC.ParUser1[Cuba].TSaiSuspLinhaD);
	printf("AVC.ParUser1[%d].HabQueb[NUM_CONJ_ALIM] = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabQueb[NUM_CONJ_ALIM]);
	printf("AVC.ParUser1[%d].HabAlim[NUM_CONJ_ALIM] = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabAlim[NUM_CONJ_ALIM]);
	printf("AVC.ParUser1[%d].Sequencia[NUM_CONJ_ALIM] = %d \n", CubaOpe, AVC.ParUser1[Cuba].Sequencia[NUM_CONJ_ALIM]);
	printf("AVC.ParUser1[%d].TempoEspera = %f \n", CubaOpe, AVC.ParUser1[Cuba].TempoEspera);
	printf("AVC.ParUser1[%d].Liver1 = %f \n", CubaOpe, AVC.ParUser1[Cuba].Liver1);
	printf("AVC.ParUser1[%d].Livre2 = %f \n", CubaOpe, AVC.ParUser1[Cuba].Livre2);
	printf("AVC.ParUser1[%d].QuantAlumCarga[4] = %f \n", CubaOpe, AVC.ParUser1[Cuba].QuantAlumCarga[4]);
	printf("AVC.ParUser1[%d].CadenciaEARemota = %d \n", CubaOpe, AVC.ParUser1[Cuba].CadenciaEARemota);
	printf("AVC.ParUser1[%d].TempoFimAEARemota = %d \n", CubaOpe, AVC.ParUser1[Cuba].TempoFimAEARemota);
	printf("AVC.ParUser1[%d].TempoQuebrador[NUM_CONJ_ALIM] = %f \n", CubaOpe, AVC.ParUser1[Cuba].TempoQuebrador[NUM_CONJ_ALIM]);
	printf("AVC.ParUser1[%d].TempoAlimentador[NUM_CONJ_ALIM] = %f \n", CubaOpe, AVC.ParUser1[Cuba].TempoAlimentador[NUM_CONJ_ALIM]);
	printf("AVC.ParUser1[%d].TFalhaRuido = %d \n", CubaOpe, AVC.ParUser1[Cuba].TFalhaRuido);
	printf("AVC.ParUser1[%d].HabTabPartida = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabTabPartida);
	printf("AVC.ParUser1[%d].NumTabPartida = %d \n", CubaOpe, AVC.ParUser1[Cuba].NumTabPartida);
	printf("AVC.ParUser1[%d].HabSoproEspec = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabSoproEspec);
	printf("AVC.ParUser1[%d].UsaRLent = %d \n", CubaOpe, AVC.ParUser1[Cuba].UsaRLent);
	printf("AVC.ParUser1[%d].UsaRRap = %d \n", CubaOpe, AVC.ParUser1[Cuba].UsaRRap);
	printf("AVC.ParUser1[%d].UsaIncOpe = %d \n", CubaOpe, AVC.ParUser1[Cuba].UsaIncOpe);
	printf("AVC.ParUser1[%d].UsaAtrasoEa = %d \n", CubaOpe, AVC.ParUser1[Cuba].UsaAtrasoEa);
	printf("AVC.ParUser1[%d].UsaMaxEa = %d \n", CubaOpe, AVC.ParUser1[Cuba].UsaMaxEa);
	printf("AVC.ParUser1[%d].HabMCruzeiro = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabMCruzeiro);
	printf("AVC.ParUser1[%d].TMaxPermMCruzeiro = %d \n", CubaOpe, AVC.ParUser1[Cuba].TMaxPermMCruzeiro);
	printf("AVC.ParUser1[%d].HabLimMov = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabLimMov);
	printf("AVC.ParUser1[%d].NumMovConsec = %d \n", CubaOpe, AVC.ParUser1[Cuba].NumMovConsec);
	printf("AVC.ParUser1[%d].GrupoMov = %d \n", CubaOpe, AVC.ParUser1[Cuba].GrupoMov);
	printf("AVC.ParUser1[%d].TenLimCal = %f \n", CubaOpe, AVC.ParUser1[Cuba].TenLimCal);
	printf("AVC.ParUser1[%d].EfeitoTenCal = %d \n", CubaOpe, AVC.ParUser1[Cuba].EfeitoTenCal);
	printf("AVC.ParUser1[%d].HabLogMovQueb = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabLogMovQueb);
	printf("AVC.ParUser1[%d].HabContEficMov = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabContEficMov);
	printf("AVC.ParUser1[%d].EficMovMin = %d \n", CubaOpe, AVC.ParUser1[Cuba].EficMovMin);
	printf("AVC.ParUser1[%d].HabCalcHoraQueb = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabCalcHoraQueb);
	printf("AVC.ParUser1[%d].IntervQuebProg = %d \n", CubaOpe, AVC.ParUser1[Cuba].IntervQuebProg);
	printf("AVC.ParUser1[%d].HoraRefQuebProg = %d \n", CubaOpe, AVC.ParUser1[Cuba].HoraRefQuebProg);
	printf("AVC.ParUser1[%d].HabCalcDN = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabCalcDN);
	printf("AVC.ParUser1[%d].TEfeitoDN = %d \n", CubaOpe, AVC.ParUser1[Cuba].TEfeitoDN);
	printf("AVC.ParUser1[%d].CalcDNQueb = %d \n", CubaOpe, AVC.ParUser1[Cuba].CalcDNQueb);
	printf("AVC.ParUser1[%d].AlarmeDNQueb = %d \n", CubaOpe, AVC.ParUser1[Cuba].AlarmeDNQueb);
	printf("AVC.ParUser1[%d].NivelDN = %f \n", CubaOpe, AVC.ParUser1[Cuba].NivelDN);
	printf("AVC.ParUser1[%d].HabCalcDB = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabCalcDB);
	printf("AVC.ParUser1[%d].TEfeitoDB = %d \n", CubaOpe, AVC.ParUser1[Cuba].TEfeitoDB);
	printf("AVC.ParUser1[%d].CalcDBQueb = %d \n", CubaOpe, AVC.ParUser1[Cuba].CalcDBQueb);
	printf("AVC.ParUser1[%d].AlarmeDBQueb = %d \n", CubaOpe, AVC.ParUser1[Cuba].AlarmeDBQueb);
	printf("AVC.ParUser1[%d].NivelDB = %f \n", CubaOpe, AVC.ParUser1[Cuba].NivelDB);
	printf("AVC.ParUser1[%d].LadoRefQueb = %d \n", CubaOpe, AVC.ParUser1[Cuba].LadoRefQueb);
	printf("AVC.ParUser1[%d].DelayLadoQueb1 = %d \n", CubaOpe, AVC.ParUser1[Cuba].DelayLadoQueb1);
	printf("AVC.ParUser1[%d].DelayLadoQueb2 = %d \n", CubaOpe, AVC.ParUser1[Cuba].DelayLadoQueb2);
	printf("AVC.ParUser1[%d].HabMovCamTur = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabMovCamTur);
	printf("AVC.ParUser1[%d].TempoMovCamTur = %d \n", CubaOpe, AVC.ParUser1[Cuba].TempoMovCamTur);
	printf("AVC.ParUser1[%d].NumCiclosForaDB = %d \n", CubaOpe, AVC.ParUser1[Cuba].NumCiclosForaDB);
	printf("AVC.ParUser1[%d].KPcQueb = %f \n", CubaOpe, AVC.ParUser1[Cuba].KPcQueb);
	printf("AVC.ParUser1[%d].HabPrecMovQueb = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabPrecMovQueb);
	printf("AVC.ParUser1[%d].NumCicRes4s = %d \n", CubaOpe, AVC.ParUser1[Cuba].NumCicRes4s);
	printf("AVC.ParUser1[%d].NumMovPrecQueb = %d \n", CubaOpe, AVC.ParUser1[Cuba].NumMovPrecQueb);
	printf("AVC.ParUser1[%d].InibeRuiPosCorr = %d \n", CubaOpe, AVC.ParUser1[Cuba].InibeRuiPosCorr);
	printf("AVC.ParUser1[%d].InibeIncQuebAtrasoEa = %d \n", CubaOpe, AVC.ParUser1[Cuba].InibeIncQuebAtrasoEa);
	//printf("AVC.ParUser1[%d].NCicOscil = %d \n", CubaOpe, AVC.ParUser1[Cuba].NCicOscil);
	//printf("AVC.ParUser1[%d].DurIncOscil = %d \n", CubaOpe, AVC.ParUser1[Cuba].DurIncOscil);
	//printf("AVC.ParUser1[%d].IncOscil = %f \n", CubaOpe, AVC.ParUser1[Cuba].IncOscil);
	//printf("AVC.ParUser1[%d].LimMaxOscil = %f \n", CubaOpe, AVC.ParUser1[Cuba].LimMaxOscil);
	printf("AVC.ParUser1[%d].HoraRefCorr = %d \n", CubaOpe, AVC.ParUser1[Cuba].HoraRefCorr);
	//printf("AVC.ParUser1[%d].Sujeira1 = %d \n", CubaOpe, AVC.ParUser1[Cuba].Sujeira1);
	printf("AVC.ParUser1[%d].EaPrevMinAc = %f \n", CubaOpe, AVC.ParUser1[Cuba].EaPrevMinAc);
	printf("AVC.ParUser1[%d].EaPrevAc = %f \n", CubaOpe, AVC.ParUser1[Cuba].EaPrevAc);
	printf("AVC.ParUser1[%d].EaPrevCiclosAc = %d \n", CubaOpe, AVC.ParUser1[Cuba].EaPrevCiclosAc);
	//printf("AVC.ParUser1[%d].Sujeira2 = %d \n", CubaOpe, AVC.ParUser1[Cuba].Sujeira2);
	printf("AVC.ParUser1[%d].HabPrevAc = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabPrevAc);
	printf("AVC.ParUser1[%d].DurMovBaixoMinF = %f \n", CubaOpe, AVC.ParUser1[Cuba].DurMovBaixoMinF);
	printf("AVC.ParUser1[%d].DurMovBaixoMaxF = %f \n", CubaOpe, AVC.ParUser1[Cuba].DurMovBaixoMaxF);
	printf("AVC.ParUser1[%d].DurMovCimaMinF = %f \n", CubaOpe, AVC.ParUser1[Cuba].DurMovCimaMinF);
	printf("AVC.ParUser1[%d].DurMovCimaMaxF = %f \n", CubaOpe, AVC.ParUser1[Cuba].DurMovCimaMaxF);
	printf("AVC.ParUser1[%d].TocaSirene = %d \n", CubaOpe, AVC.ParUser1[Cuba].TocaSirene);
	printf("AVC.ParUser1[%d].DesligaSala = %d \n", CubaOpe, AVC.ParUser1[Cuba].DesligaSala);
	printf("AVC.ParUser1[%d].IntervSirene = %d \n", CubaOpe, AVC.ParUser1[Cuba].IntervSirene);
	printf("AVC.ParUser1[%d].TSopraChamine = %d \n", CubaOpe, AVC.ParUser1[Cuba].TSopraChamine);
	printf("AVC.ParUser1[%d].IntervSoproQueb = %d \n", CubaOpe, AVC.ParUser1[Cuba].IntervSoproQueb);
	printf("AVC.ParUser1[%d].TSinalizaSopro = %d \n", CubaOpe, AVC.ParUser1[Cuba].TSinalizaSopro);
	printf("AVC.ParUser1[%d].IntervSinalSopro = %d \n", CubaOpe, AVC.ParUser1[Cuba].IntervSinalSopro);
	printf("AVC.ParUser1[%d].LadoQuebIdx = %d \n", CubaOpe, AVC.ParUser1[Cuba].LadoQuebIdx);
	printf("AVC.ParUser1[%d].InverteIdx = %d \n", CubaOpe, AVC.ParUser1[Cuba].InverteIdx);
	printf("AVC.ParUser1[%d].TAcresBSupMovel = %d \n", CubaOpe, AVC.ParUser1[Cuba].TAcresBSupMovel);
	printf("AVC.ParUser1[%d].AcresBSupMovel = %f \n", CubaOpe, AVC.ParUser1[Cuba].AcresBSupMovel);
	printf("AVC.ParUser1[%d].HabKbpCorrida = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabKbpCorrida);
	printf("AVC.ParUser1[%d].InibeQPQuebProg = %d \n", CubaOpe, AVC.ParUser1[Cuba].InibeQPQuebProg);
	printf("AVC.ParUser1[%d].HabSmartFeed = %d \n", CubaOpe, AVC.ParUser1[Cuba].HabSmartFeed);
	printf("AVC.ParUser1[%d].LimQPrevEaAtraso = %d \n", CubaOpe, AVC.ParUser1[Cuba].LimQPrevEaAtraso);
	printf("AVC.ParUser1[%d].SF_SUFeed = %f \n", CubaOpe, AVC.ParUser1[Cuba].SF_SUFeed);
	printf("AVC.ParUser1[%d].SF_UnderFeed = %f \n", CubaOpe, AVC.ParUser1[Cuba].SF_UnderFeed);
	printf("AVC.ParUser1[%d].SF_NormalFeed = %f \n", CubaOpe, AVC.ParUser1[Cuba].SF_NormalFeed);
	printf("AVC.ParUser1[%d].SF_OverFeed = %f \n", CubaOpe, AVC.ParUser1[Cuba].SF_OverFeed);
	printf("AVC.ParUser1[%d].SF_PassoAcima = %f \n", CubaOpe, AVC.ParUser1[Cuba].SF_PassoAcima);
	printf("AVC.ParUser1[%d].SF_PassoAbaixo = %f \n", CubaOpe, AVC.ParUser1[Cuba].SF_PassoAbaixo);
	printf("AVC.ParUser1[%d].SF_LimMovCima = %f \n", CubaOpe, AVC.ParUser1[Cuba].SF_LimMovCima);
	printf("AVC.ParUser1[%d].SF_LimMovBaixo = %f \n", CubaOpe, AVC.ParUser1[Cuba].SF_LimMovBaixo);
	printf("AVC.User1[%d].EstadoAlimAtual = %d \n", CubaOpe, AVC.User1[Cuba].EstadoAlimAtual);
	printf("AVC.User1[%d].EstadoAlimAnt = %d \n", CubaOpe, AVC.User1[Cuba].EstadoAlimAnt);
	printf("AVC.User1[%d].InicioAlgAtual = %d \n", CubaOpe, AVC.User1[Cuba].InicioAlgAtual);
	printf("AVC.User1[%d].TempEstAtual = %d \n", CubaOpe, AVC.User1[Cuba].TempEstAtual);
	printf("AVC.User1[%d].QtAAlimEstAtual = %f \n", CubaOpe, AVC.User1[Cuba].QtAAlimEstAtual);
	printf("AVC.User1[%d].HoraIniEstAtual = %d \n", CubaOpe, AVC.User1[Cuba].HoraIniEstAtual);
	printf("AVC.User1[%d].State = %d \n", CubaOpe, AVC.User1[Cuba].State);
	printf("AVC.User1[%d].InicioSubEst = %d \n", CubaOpe, AVC.User1[Cuba].InicioSubEst);
	printf("AVC.User1[%d].HoraIniSubEstAtual = %d \n", CubaOpe, AVC.User1[Cuba].HoraIniSubEstAtual);
	printf("AVC.User1[%d].IntervCurr = %f \n", CubaOpe, AVC.User1[Cuba].IntervCurr);
	printf("AVC.User1[%d].EfiCurr = %f \n", CubaOpe, AVC.User1[Cuba].EfiCurr);
	printf("AVC.User1[%d].Integral = %f \n", CubaOpe, AVC.User1[Cuba].Integral);
	printf("AVC.User1[%d].NumAciona = %d \n", CubaOpe, AVC.User1[Cuba].NumAciona);
	printf("AVC.User1[%d].ConcCheckAnt = %f \n", CubaOpe, AVC.User1[Cuba].ConcCheckAnt);
	printf("AVC.User1[%d].ConcCheckAtual = %f \n", CubaOpe, AVC.User1[Cuba].ConcCheckAtual);
	printf("AVC.User1[%d].HoraFimCheck = %d \n", CubaOpe, AVC.User1[Cuba].HoraFimCheck);
	printf("AVC.User1[%d].HoraUltCheck = %d \n", CubaOpe, AVC.User1[Cuba].HoraUltCheck);
	printf("AVC.User1[%d].ResAlim = %f \n", CubaOpe, AVC.User1[Cuba].ResAlim);
	printf("AVC.User1[%d].DerResAlim = %f \n", CubaOpe, AVC.User1[Cuba].DerResAlim);
	printf("AVC.User1[%d].NumOverCheck = %d \n", CubaOpe, AVC.User1[Cuba].NumOverCheck);
	printf("AVC.User1[%d].HoraUltPF = %d \n", CubaOpe, AVC.User1[Cuba].HoraUltPF);
	printf("AVC.User1[%d].PrevState = %d \n", CubaOpe, AVC.User1[Cuba].PrevState);
	printf("AVC.User1[%d].FornecSubEst = %f \n", CubaOpe, AVC.User1[Cuba].FornecSubEst);
	printf("AVC.User1[%d].ConsumoSubEst = %f \n", CubaOpe, AVC.User1[Cuba].ConsumoSubEst);
	printf("AVC.User1[%d].TempoSuspende = %d \n", CubaOpe, AVC.User1[Cuba].TempoSuspende);
	printf("AVC.User1[%d].DurInibeControle = %d \n", CubaOpe, AVC.User1[Cuba].DurInibeControle);
	printf("AVC.User1[%d].HabilitaPFAnt = %d \n", CubaOpe, AVC.User1[Cuba].HabilitaPFAnt);
	printf("AVC.User1[%d].IntPar = %f \n", CubaOpe, AVC.User1[Cuba].IntPar);
	printf("AVC.User1[%d].Consumo = %f \n", CubaOpe, AVC.User1[Cuba].Consumo);
	printf("AVC.User1[%d].alvo = %f \n", CubaOpe, AVC.User1[Cuba].alvo);
	printf("AVC.User1[%d].Resistencia[4] = %f \n", CubaOpe, AVC.User1[Cuba].Resistencia[4]);
	printf("AVC.User1[%d].ResIndex = %d \n", CubaOpe, AVC.User1[Cuba].ResIndex);
	printf("AVC.User1[%d].Preenchido = %d \n", CubaOpe, AVC.User1[Cuba].Preenchido);
	printf("AVC.User1[%d].Conc[5] = %f \n", CubaOpe, AVC.User1[Cuba].Conc[5]);
	printf("AVC.User1[%d].ConcDer = %f \n", CubaOpe, AVC.User1[Cuba].ConcDer);
	printf("AVC.User1[%d].Deriv[5] = %f \n", CubaOpe, AVC.User1[Cuba].Deriv[5]);
	printf("AVC.User1[%d].DerIndex = %d \n", CubaOpe, AVC.User1[Cuba].DerIndex);
	printf("AVC.User1[%d].UnderProg = %f \n", CubaOpe, AVC.User1[Cuba].UnderProg);
	printf("AVC.User1[%d].IniEtapaUnder = %d \n", CubaOpe, AVC.User1[Cuba].IniEtapaUnder);
	printf("AVC.User1[%d].ResFilt = %f \n", CubaOpe, AVC.User1[Cuba].ResFilt);
	printf("AVC.User1[%d].DerResAlimAnt = %f \n", CubaOpe, AVC.User1[Cuba].DerResAlimAnt);
	printf("AVC.User1[%d].ConcBaixa = %d \n", CubaOpe, AVC.User1[Cuba].ConcBaixa);
	printf("AVC.User1[%d].QuebSubEst = %d \n", CubaOpe, AVC.User1[Cuba].QuebSubEst);
	printf("AVC.User1[%d].NumQueb = %d \n", CubaOpe, AVC.User1[Cuba].NumQueb);
	printf("AVC.User1[%d].HabilitaBarraAnt = %d \n", CubaOpe, AVC.User1[Cuba].HabilitaBarraAnt);
	printf("AVC.User1[%d].HoraUltQPrev = %d \n", CubaOpe, AVC.User1[Cuba].HoraUltQPrev);
	printf("AVC.User1[%d].ContInibQPrev = %d \n", CubaOpe, AVC.User1[Cuba].ContInibQPrev);
	printf("AVC.User1[%d].ContDurQPrev = %d \n", CubaOpe, AVC.User1[Cuba].ContDurQPrev);
	printf("AVC.User1[%d].NumQuebPrev = %d \n", CubaOpe, AVC.User1[Cuba].NumQuebPrev);
	printf("AVC.User1[%d].NumPrevQPrev = %d \n", CubaOpe, AVC.User1[Cuba].NumPrevQPrev);
	printf("AVC.User1[%d].ContTAjAcum = %f \n", CubaOpe, AVC.User1[Cuba].ContTAjAcum);
	printf("AVC.User1[%d].ContTAjCam = %f \n", CubaOpe, AVC.User1[Cuba].ContTAjCam);
	printf("AVC.User1[%d].ContInibAjCam = %d \n", CubaOpe, AVC.User1[Cuba].ContInibAjCam);
	printf("AVC.User1[%d].ContMovCorr = %d \n", CubaOpe, AVC.User1[Cuba].ContMovCorr);
	printf("AVC.User1[%d].PassoCadencia = %d \n", CubaOpe, AVC.User1[Cuba].PassoCadencia);
	printf("AVC.User1[%d].PassoAtualTPartida = %d \n", CubaOpe, AVC.User1[Cuba].PassoAtualTPartida);
	printf("AVC.User1[%d].HoraIniEsperaTPartida = %d \n", CubaOpe, AVC.User1[Cuba].HoraIniEsperaTPartida);
	printf("AVC.User1[%d].EaVoltLimTabPartida = %f \n", CubaOpe, AVC.User1[Cuba].EaVoltLimTabPartida);
	printf("AVC.User1[%d].EstadoSoproEspec = %d \n", CubaOpe, AVC.User1[Cuba].EstadoSoproEspec);
	printf("AVC.User1[%d].ContCicSoproEspec = %d \n", CubaOpe, AVC.User1[Cuba].ContCicSoproEspec);
	printf("AVC.User1[%d].ContEsperaSoproEspec = %d \n", CubaOpe, AVC.User1[Cuba].ContEsperaSoproEspec);
	printf("AVC.User1[%d].Vida = %d \n", CubaOpe, AVC.User1[Cuba].Vida);
	printf("AVC.User1[%d].RrapCContValp = %f \n", CubaOpe, AVC.User1[Cuba].RrapCContValp);
	printf("AVC.User1[%d].RlentCContValp = %f \n", CubaOpe, AVC.User1[Cuba].RlentCContValp);
	printf("AVC.User1[%d].NumDB = %d \n", CubaOpe, AVC.User1[Cuba].NumDB);
	printf("AVC.User1[%d].NumQuebProg = %d \n", CubaOpe, AVC.User1[Cuba].NumQuebProg);
	printf("AVC.User1[%d].AdFluoreto = %d \n", CubaOpe, AVC.User1[Cuba].AdFluoreto);
	printf("AVC.User1[%d].BandaSupMovel = %f \n", CubaOpe, AVC.User1[Cuba].BandaSupMovel);
	printf("AVC.User1[%d].PulouQuebProg = %d \n", CubaOpe, AVC.User1[Cuba].PulouQuebProg);
	printf("AVC.User1[%d].EqMotorCorrB = %f \n", CubaOpe, AVC.User1[Cuba].EqMotorCorrB);
	printf("AVC.User1[%d].SF_IncDeriv = %f \n", CubaOpe, AVC.User1[Cuba].SF_IncDeriv);
	printf("AVC.User1[%d].SF_IncDerivEA = %f \n", CubaOpe, AVC.User1[Cuba].SF_IncDerivEA);
	printf("AVC.User1[%d].SF_TempoSobe = %f \n", CubaOpe, AVC.User1[Cuba].SF_TempoSobe);
	printf("AVC.User1[%d].AtrasouEa = %d \n", CubaOpe, AVC.User1[Cuba].AtrasouEa);
	printf("AVC.User1[%d].SF_IncDerivAnt = %f \n", CubaOpe, AVC.User1[Cuba].SF_IncDerivAnt);
	printf("AVC.User1[%d].SF_Posicao = %d \n", CubaOpe, AVC.User1[Cuba].SF_Posicao);
	printf("AVC.User1[%d].QuebrouDB = %d \n", CubaOpe, AVC.User1[Cuba].QuebrouDB);
	printf("AVC.User2[%d].TQuebInib[NUM_CONJ_ALIM] = %d \n", CubaOpe, AVC.User2[Cuba].TQuebInib[NUM_CONJ_ALIM]);
	printf("AVC.User2[%d].TAlimInib[NUM_CONJ_ALIM] = %d \n", CubaOpe, AVC.User2[Cuba].TAlimInib[NUM_CONJ_ALIM]);
	printf("AVC.User2[%d].HabQuebOp[NUM_CONJ_ALIM] = %d \n", CubaOpe, AVC.User2[Cuba].HabQuebOp[NUM_CONJ_ALIM]);
	printf("AVC.User2[%d].HabAlimOp[NUM_CONJ_ALIM] = %d \n", CubaOpe, AVC.User2[Cuba].HabAlimOp[NUM_CONJ_ALIM]);
	printf("AVC.User2[%d].TIniFalhaCalcRuido = %d \n", CubaOpe, AVC.User2[Cuba].TIniFalhaCalcRuido);
	printf("AVC.User2[%d].ContEvChaves = %d \n", CubaOpe, AVC.User2[Cuba].ContEvChaves);
	printf("AVC.User2[%d].HoraTenCal = %d \n", CubaOpe, AVC.User2[Cuba].HoraTenCal);
	printf("AVC.User2[%d].Rinst_atnca = %f \n", CubaOpe, AVC.User2[Cuba].Rinst_atnca);
	printf("AVC.User2[%d].Res_2m_atnca = %f \n", CubaOpe, AVC.User2[Cuba].Res_2m_atnca);
	printf("AVC.User2[%d].Res_2m_ant_atnca = %f \n", CubaOpe, AVC.User2[Cuba].Res_2m_ant_atnca);
	printf("AVC.User2[%d].VRLentCCont = %d \n", CubaOpe, AVC.User2[Cuba].VRLentCCont);
	printf("AVC.User2[%d].VRRapCCont = %d \n", CubaOpe, AVC.User2[Cuba].VRRapCCont);
	printf("AVC.User2[%d].SigmaS_2m = %f \n", CubaOpe, AVC.User2[Cuba].SigmaS_2m);
	printf("AVC.User2[%d].SigmaL_2m = %f \n", CubaOpe, AVC.User2[Cuba].SigmaL_2m);
	printf("AVC.User2[%d].HoraProxQueb = %d \n", CubaOpe, AVC.User2[Cuba].HoraProxQueb);
	printf("AVC.User2[%d].HoraUltQueb = %d \n", CubaOpe, AVC.User2[Cuba].HoraUltQueb);
	printf("AVC.User2[%d].HoraProxQuebReal = %d \n", CubaOpe, AVC.User2[Cuba].HoraProxQuebReal);
	printf("AVC.User2[%d].HoraUltQuebReal = %d \n", CubaOpe, AVC.User2[Cuba].HoraUltQuebReal);
	printf("AVC.User2[%d].HoraForaDB = %d \n", CubaOpe, AVC.User2[Cuba].HoraForaDB);
	printf("AVC.User2[%d].MediaDN = %f \n", CubaOpe, AVC.User2[Cuba].MediaDN);
	printf("AVC.User2[%d].NumCiclosDN = %d \n", CubaOpe, AVC.User2[Cuba].NumCiclosDN);
	printf("AVC.User2[%d].TMovCamAcumTur = %d \n", CubaOpe, AVC.User2[Cuba].TMovCamAcumTur);
	printf("AVC.User2[%d].HoraUltMovPainel = %d \n", CubaOpe, AVC.User2[Cuba].HoraUltMovPainel);
	printf("AVC.User2[%d].HoraPrecMovQueb = %d \n", CubaOpe, AVC.User2[Cuba].HoraPrecMovQueb);
	//printf("AVC.User2[%d].NumOscil = %d \n", CubaOpe, AVC.User2[Cuba].NumOscil);
	printf("AVC.User2[%d].HoraIncOscil = %d \n", CubaOpe, AVC.User2[Cuba].HoraIncOscil);
	printf("AVC.User2[%d].IncOscil = %f \n", CubaOpe, AVC.User2[Cuba].IncOscil);
	//printf("AVC.User2[%d].ContIncOscil = %d \n", CubaOpe, AVC.User2[Cuba].ContIncOscil);
	printf("AVC.User2[%d].HoraUltCorr = %d \n", CubaOpe, AVC.User2[Cuba].HoraUltCorr);
	printf("AVC.User2[%d].DerivHTeste = %f \n", CubaOpe, AVC.User2[Cuba].DerivHTeste);
	printf("AVC.User2[%d].IncFormaBanho = %f \n", CubaOpe, AVC.User2[Cuba].IncFormaBanho);
	printf("AVC.User2[%d].DurFormaBanho = %d \n", CubaOpe, AVC.User2[Cuba].DurFormaBanho);
	printf("AVC.User2[%d].HoraIniFormaBanho = %d \n", CubaOpe, AVC.User2[Cuba].HoraIniFormaBanho);
	printf("AVC.User2[%d].HoraEvQuebrada = %d \n", CubaOpe, AVC.User2[Cuba].HoraEvQuebrada);
	printf("AVC.User2[%d].CiclosIniPrevAc = %d \n", CubaOpe, AVC.User2[Cuba].CiclosIniPrevAc);
	printf("AVC.User2[%d].RSuavePrevAc[5] = %f \n", CubaOpe, AVC.User2[Cuba].RSuavePrevAc[5]);
	printf("AVC.User2[%d].RSuaveDerivHAnt = %f \n", CubaOpe, AVC.User2[Cuba].RSuaveDerivHAnt);
	printf("AVC.User2[%d].HoraSireneCunha = %d \n", CubaOpe, AVC.User2[Cuba].HoraSireneCunha);
	printf("AVC.User2[%d].HoraContSirene = %d \n", CubaOpe, AVC.User2[Cuba].HoraContSirene);
	printf("SUPERV_AVC(%d).Sup.QtdAlumina = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.QtdAlumina);
	printf("SUPERV_AVC(%d).Sup.QtdAluminaPadrao = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.QtdAluminaPadrao);
	printf("SUPERV_AVC(%d).Sup.QtdAluminaEA = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.QtdAluminaEA);
	printf("SUPERV_AVC(%d).Sup.QtdAluminaExc = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.QtdAluminaExc);
	printf("SUPERV_AVC(%d).Sup.TAlimPadrao = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.TAlimPadrao);
	printf("SUPERV_AVC(%d).Sup.TAlimEA = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.TAlimEA);
	printf("SUPERV_AVC(%d).Sup.TAlimSusp = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.TAlimSusp);
	printf("SUPERV_AVC(%d).Sup.TAlimExc = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.TAlimExc);
	printf("SUPERV_AVC(%d).Sup.TInibeControle = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.TInibeControle);
	printf("SUPERV_AVC(%d).Sup.TManAlimLoc = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.TManAlimLoc);
	printf("SUPERV_AVC(%d).Sup.TManAlimRem = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.TManAlimRem);
	printf("SUPERV_AVC(%d).Sup.TManAlim = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.TManAlim);
	printf("SUPERV_AVC(%d).Sup.TAutoAlim = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.TAutoAlim);
	printf("SUPERV_AVC(%d).Sup.NumQuebPadrao = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.NumQuebPadrao);
	printf("SUPERV_AVC(%d).Sup.NumQuebEA = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.NumQuebEA);
	printf("SUPERV_AVC(%d).Sup.TempoInibQPrev = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.TempoInibQPrev);
	printf("SUPERV_AVC(%d).Sup.NumTabEliEaNInt = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.NumTabEliEaNInt);
	printf("SUPERV_AVC(%d).Sup.TabEliEaSucesso = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.TabEliEaSucesso);
	printf("SUPERV_AVC(%d).Sup.NumQuebPrev = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.NumQuebPrev);
	printf("SUPERV_AVC(%d).Sup.NumPrevQPrev = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.NumPrevQPrev);
	printf("SUPERV_AVC(%d).Sup.ContDurQPrev = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.ContDurQPrev);
	printf("SUPERV_AVC(%d).Sup.ErrorADAtn8[MAX_VALORES_POR_ATN8] = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.ErrorADAtn8[MAX_VALORES_POR_ATN8]);
	printf("SUPERV_AVC(%d).Sup.TQuebInib[NUM_CONJ_ALIM] = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.TQuebInib[NUM_CONJ_ALIM]);
	printf("SUPERV_AVC(%d).Sup.TAlimInib[NUM_CONJ_ALIM] = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.TAlimInib[NUM_CONJ_ALIM]);
	printf("SUPERV_AVC(%d).Sup.NumEaQPrev = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.NumEaQPrev);
	printf("SUPERV_AVC(%d).Sup.ApMovBaixoDia = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.ApMovBaixoDia);
	printf("SUPERV_AVC(%d).Sup.ApMovCimaDia = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.ApMovCimaDia);
	printf("SUPERV_AVC(%d).Sup.FalhaMovBaixoDia = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.FalhaMovBaixoDia);
	printf("SUPERV_AVC(%d).Sup.FalhaMovCimaDia = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.FalhaMovCimaDia);
	printf("SUPERV_AVC(%d).Sup.SigSNormDia = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.SigSNormDia);
	printf("SUPERV_AVC(%d).Sup.SigLNormDia = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.SigLNormDia);
	printf("SUPERV_AVC(%d).Sup.ICubaMedDia = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.ICubaMedDia);
	printf("SUPERV_AVC(%d).Sup.kwcimafalhamov = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.kwcimafalhamov);
	printf("SUPERV_AVC(%d).Sup.kwbaixofalhamov = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.kwbaixofalhamov);
	printf("SUPERV_AVC(%d).Sup.kwcimaforarede = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.kwcimaforarede);
	printf("SUPERV_AVC(%d).Sup.kwbaixoforarede = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.kwbaixoforarede);
	printf("SUPERV_AVC(%d).Sup.kwcimamanuallocal = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.kwcimamanuallocal);
	printf("SUPERV_AVC(%d).Sup.kwbaixomanuallocal = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.kwbaixomanuallocal);
	printf("SUPERV_AVC(%d).Sup.kwcimageral = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.kwcimageral);
	printf("SUPERV_AVC(%d).Sup.kwbaixogeral = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.kwbaixogeral);
	printf("SUPERV_AVC(%d).Sup.NumQuebPrevDia = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.NumQuebPrevDia);
	printf("SUPERV_AVC(%d).Sup.NumDBDia = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.NumDBDia);
	printf("SUPERV_AVC(%d).Sup.NumOscilDia = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.NumOscilDia);
	printf("SUPERV_AVC(%d).Sup.IncOscilDia = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.IncOscilDia);
	printf("SUPERV_AVC(%d).Sup.DurIncOscilDia = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.DurIncOscilDia);
	printf("SUPERV_AVC(%d).Sup.IntervCorrDia = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.IntervCorrDia);
	printf("SUPERV_AVC(%d).Sup.FormaBanho = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.FormaBanho);
	printf("SUPERV_AVC(%d).Sup.IntervRefCorrDia = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.IntervRefCorrDia);
	printf("SUPERV_AVC(%d).Sup.DurIncFBDia = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.DurIncFBDia);
	printf("SUPERV_AVC(%d).Sup.IncFBDia = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.IncFBDia);
	printf("SUPERV_AVC(%d).Sup.IntervRefQuebDia = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.IntervRefQuebDia);
	printf("SUPERV_AVC(%d).Sup.NumQuebProgDia = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.NumQuebProgDia);
	printf("SUPERV_AVC(%d).Sup.NumDBConsec = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.NumDBConsec);
	printf("SUPERV_AVC(%d).Sup.NumDBQueb = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.NumDBQueb);
	printf("SUPERV_AVC(%d).Sup.DifALFalhaMov = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.DifALFalhaMov);
	printf("SUPERV_AVC(%d).Sup.DifALBandaMorta = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.DifALBandaMorta);
	printf("SUPERV_AVC(%d).Sup.DifALInibPrev = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.DifALInibPrev);
	printf("SUPERV_AVC(%d).Sup.DifALInibQueb = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.DifALInibQueb);
	printf("SUPERV_AVC(%d).Sup.DifALIntervMov = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.DifALIntervMov);
	printf("SUPERV_AVC(%d).Sup.DifALManual = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.DifALManual);
	printf("SUPERV_AVC(%d).Sup.DifALInibUsu = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.DifALInibUsu);
	printf("SUPERV_AVC(%d).Sup.DifALDesvio = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.DifALDesvio);
	printf("SUPERV_AVC(%d).Sup.EaVMax = %f \n", CubaOpe, SUPERV_AVC(Cuba).Sup.EaVMax);
	printf("SUPERV_AVC(%d).Sup.TotalEA24h = %d \n", CubaOpe, SUPERV_AVC(Cuba).Sup.TotalEA24h);
	printf("EST_AVC(%d).Est.CheckAtivo = %d \n", CubaOpe, EST_AVC(Cuba).Est.CheckAtivo);
	printf("EST_AVC(%d).Est.CheckOperador = %d \n", CubaOpe, EST_AVC(Cuba).Est.CheckOperador);
	printf("EST_AVC(%d).Est.ManualAlimRem = %d \n", CubaOpe, EST_AVC(Cuba).Est.ManualAlimRem);
	printf("EST_AVC(%d).Est.ManualAlimLoc = %d \n", CubaOpe, EST_AVC(Cuba).Est.ManualAlimLoc);
	printf("EST_AVC(%d).Est.AlimSuspensa = %d \n", CubaOpe, EST_AVC(Cuba).Est.AlimSuspensa);
	printf("EST_AVC(%d).Est.RuidoAlim = %d \n", CubaOpe, EST_AVC(Cuba).Est.RuidoAlim);
	printf("EST_AVC(%d).Est.EaNaoTerminado = %d \n", CubaOpe, EST_AVC(Cuba).Est.EaNaoTerminado);
	printf("EST_AVC(%d).Est.QuebPrev = %d \n", CubaOpe, EST_AVC(Cuba).Est.QuebPrev);
	printf("EST_AVC(%d).Est.AjusteCamisa = %d \n", CubaOpe, EST_AVC(Cuba).Est.AjusteCamisa);
	printf("EST_AVC(%d).Est.QuebPrevInib = %d \n", CubaOpe, EST_AVC(Cuba).Est.QuebPrevInib);
	printf("EST_AVC(%d).Est.AbortaAjuste = %d \n", CubaOpe, EST_AVC(Cuba).Est.AbortaAjuste);
	printf("EST_AVC(%d).Est.AtivCamOpe = %d \n", CubaOpe, EST_AVC(Cuba).Est.AtivCamOpe);
	printf("EST_AVC(%d).Est.CamNAjust = %d \n", CubaOpe, EST_AVC(Cuba).Est.CamNAjust);
	printf("EST_AVC(%d).Est.HabQPrevOpe = %d \n", CubaOpe, EST_AVC(Cuba).Est.HabQPrevOpe);
	printf("EST_AVC(%d).Est.BoosterAtivo = %d \n", CubaOpe, EST_AVC(Cuba).Est.BoosterAtivo);
	printf("EST_AVC(%d).Est.HabElimEaOpe = %d \n", CubaOpe, EST_AVC(Cuba).Est.HabElimEaOpe);
	printf("EST_AVC(%d).Est.FalhaCalcRuido = %d \n", CubaOpe, EST_AVC(Cuba).Est.FalhaCalcRuido);
	printf("EST_AVC(%d).Est.TrataTabPartida = %d \n", CubaOpe, EST_AVC(Cuba).Est.TrataTabPartida);
	printf("EST_AVC(%d).Est.OpeSoproEspec = %d \n", CubaOpe, EST_AVC(Cuba).Est.OpeSoproEspec);
	printf("EST_AVC(%d).Est.ReleTempoMM = %d \n", CubaOpe, EST_AVC(Cuba).Est.ReleTempoMM);
	printf("EST_AVC(%d).Est.ChaveMCruzeiro = %d \n", CubaOpe, EST_AVC(Cuba).Est.ChaveMCruzeiro);
	printf("EST_AVC(%d).Est.LiberaMCruzeiro = %d \n", CubaOpe, EST_AVC(Cuba).Est.LiberaMCruzeiro);
	printf("EST_AVC(%d).Est.TensaoCunha = %d \n", CubaOpe, EST_AVC(Cuba).Est.TensaoCunha);
	printf("EST_AVC(%d).Est.DerNegativa = %d \n", CubaOpe, EST_AVC(Cuba).Est.DerNegativa);
	printf("EST_AVC(%d).Est.DerBaixa = %d \n", CubaOpe, EST_AVC(Cuba).Est.DerBaixa);
	printf("EST_AVC(%d).Est.AjusteCamTur = %d \n", CubaOpe, EST_AVC(Cuba).Est.AjusteCamTur);
	printf("EST_AVC(%d).Est.Oscilacao = %d \n", CubaOpe, EST_AVC(Cuba).Est.Oscilacao);
	printf("EST_AVC(%d).Est.FormaBanho = %d \n", CubaOpe, EST_AVC(Cuba).Est.FormaBanho);
	printf("EST_AVC(%d).Est.SireneCunha = %d \n", CubaOpe, EST_AVC(Cuba).Est.SireneCunha);
	printf("EST_AVC(%d).Est.DesligaCunha = %d \n", CubaOpe, EST_AVC(Cuba).Est.DesligaCunha);
	printf("EST_AVC(%d).Est.SopraChamine = %d \n", CubaOpe, EST_AVC(Cuba).Est.SopraChamine);
	printf("EST_AVC(%d).Est.SinalChamine = %d \n", CubaOpe, EST_AVC(Cuba).Est.SinalChamine);
	printf("EST_AVC(%d).Est.DBUltQueb = %d \n", CubaOpe, EST_AVC(Cuba).Est.DBUltQueb);
	printf("EST_AVC(%d).Est.StatusEA = %d \n", CubaOpe, EST_AVC(Cuba).Est.StatusEA);
	printf("EST_AVC(%d).Est.BSupMovel = %d \n", CubaOpe, EST_AVC(Cuba).Est.BSupMovel);
	printf("EST_AVC(%d).Est.StatusPainel = %d \n", CubaOpe, EST_AVC(Cuba).Est.StatusPainel);
	printf("AVL.Par.SelecaoCanalI = %d \n", AVL.Par.SelecaoCanalI);
	printf("AVL.Par.TempoMoveCimaOpeMovel = %d \n", AVL.Par.TempoMoveCimaOpeMovel);
	printf("AVL.Par.TempoMoveBaixoOpeMovel = %d \n", AVL.Par.TempoMoveBaixoOpeMovel);
	printf("AVL.Par.TempoSoproOpeMovel = %d \n", AVL.Par.TempoSoproOpeMovel);
	printf("AVL.Par.LimMovBAtEa = %d \n", AVL.Par.LimMovBAtEa);
	printf("AVL.Par.LimMovCAtEa = %d \n", AVL.Par.LimMovCAtEa);
	printf("AVL.Par.LimSoproAtEa = %d \n", AVL.Par.LimSoproAtEa);
	printf("AVL.Par.TLimSoproEspec = %d \n", AVL.Par.TLimSoproEspec);
	printf("AVL.Par.TIntervSoproEspec = %d \n", AVL.Par.TIntervSoproEspec);
	printf("AVL.Par.VLimSoproEspec = %f \n", AVL.Par.VLimSoproEspec);
	printf("AVL.Par.DurAcionaSoproEspec = %d \n", AVL.Par.DurAcionaSoproEspec);
	printf("AVL.Par.HabImportSIAP = %d \n", AVL.Par.HabImportSIAP);
	printf("AVL.Par.EfeitoDifAlta = %d \n", AVL.Par.EfeitoDifAlta);
	printf("AVL.Par.DifCorMax = %d \n", AVL.Par.DifCorMax);
	printf("AVL.Par.EaVoltLinhaLim = %f \n", AVL.Par.EaVoltLinhaLim);
	printf("AVL.Par.TEfeitoEaLinha = %d \n", AVL.Par.TEfeitoEaLinha);
	printf("AVL.Par.TMaxCorrida = %d \n", AVL.Par.TMaxCorrida);
	printf("AVL.Par.Reserva1 = %d \n", AVL.Par.Reserva1);
	printf("AVL.Par.NCic4sEaLinha = %d \n", AVL.Par.NCic4sEaLinha);
	printf("AVL.Par.BitSirenesATNCA1 = %d \n", AVL.Par.BitSirenesATNCA1);
	printf("AVL.Par.BitSirenesATNCA2 = %d \n", AVL.Par.BitSirenesATNCA2);
	printf("AVL.Par.TmpAlarmeSirenes = %d \n", AVL.Par.TmpAlarmeSirenes);
	printf("AVL.Trab.Atn8Temperature[MAX_ATN8] = %d \n", AVL.Trab.Atn8Temperature[MAX_ATN8]);
	printf("AVL.Trab.DataAnalise = %d \n", AVL.Trab.DataAnalise);
	printf("AVL.Trab.DataOperacional = %d \n", AVL.Trab.DataOperacional);
	printf("AVL.Trab.DifCorAlta = %d \n", AVL.Trab.DifCorAlta);
	printf("AVL.Trab.HoraDifCorAlta = %d \n", AVL.Trab.HoraDifCorAlta);
	printf("AVL.Trab.HoraIniDia = %d \n", AVL.Trab.HoraIniDia);
	printf("AVL.Trab.DataImport = %d \n", AVL.Trab.DataImport);
	printf("AVL.Trab.Reserva = %d \n", AVL.Trab.Reserva);
	printf("AVL.Trab.EaLinha = %d \n", AVL.Trab.EaLinha);
	printf("AVL.Trab.AlarmeSala = %d \n", AVL.Trab.AlarmeSala);
	printf("AVL.Trab.EstadoSireneSala = %d \n", AVL.Trab.EstadoSireneSala);
	printf("AVL.Trab.HoraAlarmeSala = %d \n", AVL.Trab.HoraAlarmeSala);
	printf("AVL.Trab.TimerMcc = %f \n", AVL.Trab.TimerMcc);
	printf("AVL.Trab.TimerMcp = %f \n", AVL.Trab.TimerMcp);
	
  }

   for(i = 0; i <  NUM_OUTRAS_REMOTAS; i++)
   {
      for(k = 0; k <  MAX_VALORES_POR_ATN8; k++)
      {
	    printf("AVL.Sup.ErrorADAtn8[i][k] = %d \n", AVL.Sup.ErrorADAtn8[i][k]);
	  }
	}	
  }

   i=0;
   k=0;
  for(CubaOpe = 301; CubaOpe <= 336 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 700 - i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe+100);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 720 + i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 1420 - i;

	i += 20;
  }

   i=0;
   k=0;
  for(CubaOpe = 337; CubaOpe <= 380 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 860 - i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe+100);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 880 + i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 1740 - i;
	i += 20;
  }
   i=0;
   k=0;
  for(CubaOpe = 701; CubaOpe <= 736 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 700 - i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe+100);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 720 + i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 1420 - i;

	i += 20;
  }

   i=0;
   k=0;
  for(CubaOpe = 737; CubaOpe <= 780 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 860 - i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe+100);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 880 + i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 1740 - i;
	i += 20;
  }

   i=0;
   k=0;
  for(CubaOpe = 1337; CubaOpe <= 1341 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 100 - i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe+100);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 125 + i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 225 - i;
	i += 25;
  }

   i=0;
   k=0;

  for(CubaOpe = 1301; CubaOpe <= 1336 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 875 - i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
    Cuba = ConvCubOperScore(CubaOpe+100);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 900 + i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 1775 - i;
	i += 25;
  }


   i=0;
   k=0;
CubaOpe=0;
Cuba=0;

  printf("LinhaHabilitada %d \n", AVL.LinhaHabilitada);
  printf("EstadoCuba %d \n", EST_AVC(Cuba).EstadoCuba);
  printf("HabElimEaOpe %d \n", EST_AVC(Cuba).Est.HabElimEaOpe);
  printf("RtuStatus %d \n", EST_AVC(Cuba).RtuStatus);
  printf("ChaveLocRem %d \n", EST_AVC(Cuba).ChaveLocRem);
  printf("ChaveAutMan %d \n", EST_AVC(Cuba).ChaveAutMan);
  printf("HoraDesativaLinha %d \n", AVL.HoraDesativaLinha);
  printf("HoraAtualSec %d \n", time(NULL));
  printf("TAtivaLinha %d \n", AVL.TAtivaLinha);

   i=0;
   k=0;

  for(CubaOpe = 301; CubaOpe <= 480 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.User1[Cuba].NumQuebProg = (int)(AVC.Cleit[Cuba].TUltEa / (160*60));
  	printf("NumQuebProg %d \n", AVC.User1[Cuba].NumQuebProg);

  }

   i=0;
   k=0;

  for(CubaOpe = 701; CubaOpe <= 880 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    EST_AVC(Cuba).Est.DerBaixa = FALSO;
  }


   i=0;
   k=0;

  for(CubaOpe = 1301; CubaOpe <= 1641 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    printf("Cuba %d\n",CubaOpe);
    printf("HoraUltMove %d\n",AVC.Ccont[Cuba].HoraUltMove);
	printf("KSuave %d\n",AVC.Ea[Cuba].KSuave);

  	printf("HoraUltCorr %d\n",AVC.Cleit[Cuba].HoraUltCorr);
  	printf("RSuave %f\n",AVC.Ea[Cuba].RSuave);

	printf("RSuaveDeriv %d\n",AVC.Ea[Cuba].RSuaveDeriv);
  	printf("RSuaveAnt %f\n",AVC.Ea[Cuba].RSuaveAnt);

  	printf("RSuaveDerivH %f\n",AVC.User2[Cuba].RSuaveDerivHAnt);
   	printf("RSuaveDerivHEA %f\n",AVC.Ea[Cuba].RSuaveDerivH);
  }


   i=0;
   k=0;
	CubaOpe = 1607;
    Cuba = ConvCubOperScore(CubaOpe);

  EST_AVC(Cuba).ForaControle=FALSO;
  EST_AVC(Cuba).ForaLeitura=FALSO;
  EST_AVC(Cuba).EstadoCuba=CUBA_NORMAL;


  EST_AVC(Cuba).EfeitoMove=FALSO;
  EST_AVC(Cuba).EfeitoEa=FALSO;
  EST_AVC(Cuba).EfeitoQueb=FALSO;
  AVC.Ccont[Cuba].Rinc=0.0;
  AVC.Ccont[Cuba].Vinc=0.0;
  AVC.User1[Cuba].SF_IncDeriv = 0.0;
  AVC.User1[Cuba].SF_IncDerivEA = 0.0;
  AVC.Ruido[Cuba].RrapCContVal = 0.0;
  AVC.Ruido[Cuba].RlentCContVal = 0.0;

  AVC.Ccont[Cuba].RAlvo=(AVC.Param[Cuba].VSetPointCnf-AVC.Param[Cuba].Bemf)/AVL.INominal;
  EST_AVC(Cuba).EaPrevVirada=FALSO;



   i=0;
   k=0;
    CubaOpe = 607;
    Cuba = ConvCubOperScore(CubaOpe);

  for(CubaOpe = 1501; CubaOpe <= 1541 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
	i = i+25;
  }	
  for(CubaOpe = 1609; CubaOpe >= 1601 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
	i = i+25;
  }	
  for(CubaOpe = 1618; CubaOpe >= 1610 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
	i = i+25;
  }	
  for(CubaOpe = 1627; CubaOpe >= 1619 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
	i = i+25;
  }	
  for(CubaOpe = 1641; CubaOpe >= 1628 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
	i = i+25;
  }	

 

  i=0;
  for(CubaOpe = 1509; CubaOpe >= 1501 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
	i = i+25;
  }	
  for(CubaOpe = 1518; CubaOpe >= 1510 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
	i = i+25;
  }	
  for(CubaOpe = 1527; CubaOpe >= 1519 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
	i = i+25;
  }	
  for(CubaOpe = 1541; CubaOpe >= 1528 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
	i = i+25;
  }	
  for(CubaOpe = 1601; CubaOpe <= 1641 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
	i = i+25;
  }	


   i=0;
   k=0;

    CubaOpe = 701;
    Cuba = ConvCubOperScore(CubaOpe);

    printf("EstadoIO : %i \n", AVC.Cleit[Cuba].EstadoIO);

	printf("\nBitSobeAnodo : %d", AVC.Abs[Cuba].BitSobeAnodo);
	printf("\nBitDesceAnodo : %d", AVC.Abs[Cuba].BitDesceAnodo);
	printf("\nBitLampEa : %d", AVC.Abs[Cuba].BitLampEa);
	printf("\nBitLampRec : %d", AVC.Abs[Cuba].BitLampRec);
	printf("\nBitAvPistaoAQuebA : %d", AVC.Abs[Cuba].BitAvPistaoAQuebA);
	printf("\nBitRecPistaoAQuebB : %d", AVC.Abs[Cuba].BitRecPistaoAQuebB);
	printf("\nBitAvPistaoBQuebC : %d", AVC.Abs[Cuba].BitAvPistaoBQuebC);
	printf("\nBitRecPistaoBouM2QuebD : %d", AVC.Abs[Cuba].BitRecPistaoBouM2QuebD);
	printf("\nBitSopro : %d", AVC.Abs[Cuba].BitSopro);
	printf("\nBitSobeCamisaouM1 : %d", AVC.Abs[Cuba].BitSobeCamisaouM1);
	printf("\nBitDescCamOuAvPCAlimA : %d", AVC.Abs[Cuba].BitDescCamOuAvPCAlimA);
	printf("\nBitRecuoPistCAlimB : %d", AVC.Abs[Cuba].BitRecuoPistCAlimB);
	printf("\nBitAvancoPistDAlimC : %d", AVC.Abs[Cuba].BitAvancoPistDAlimC);
	printf("\nBitRecuoPistDAlimD : %d", AVC.Abs[Cuba].BitRecuoPistDAlimD);
	printf("\nBitSireneEA : %d", AVC.Abs[Cuba].BitSireneEA);
	printf("\nBitLiberaMCruzeiro : %d", AVC.Abs[Cuba].BitLiberaMCruzeiro);
	printf("\nBitChaveQueb : %d", AVC.Abs[Cuba].BitChaveQueb);
	printf("\nBitChaveCorr : %d", AVC.Abs[Cuba].BitChaveCorr);
	printf("\nBitChaveLocRem : %d", AVC.Abs[Cuba].BitChaveLocRem);
	printf("\nBitResetEa : %d", AVC.Abs[Cuba].BitResetEa);
	printf("\nBitSubiuAnodo : %d", AVC.Abs[Cuba].BitSubiuAnodo);
	printf("\nBitDesceuAnodo : %d", AVC.Abs[Cuba].BitDesceuAnodo);
	printf("\nBitSubOuMovCamisaouM2 : %d", AVC.Abs[Cuba].BitSubOuMovCamisaouM2);
	printf("\nBitDesCamOuPFAutoouM1 : %d", AVC.Abs[Cuba].BitDesCamOuPFAutoouM1);
	printf("\nBitCheckUp : %d", AVC.Abs[Cuba].BitCheckUp);
	printf("\nBitTrocaPinos : %d", AVC.Abs[Cuba].BitTrocaPinos);
	printf("\nBitSoprou : %d", AVC.Abs[Cuba].BitSoprou);
	printf("\nBitReleFalhaMM : %d", AVC.Abs[Cuba].BitReleFalhaMM);
	printf("\nBitChaveMCruzeiro : %d", AVC.Abs[Cuba].BitChaveMCruzeiro);


   i=0;
   k=0;

   CubaOpe = 1247;
   Cuba = ConvCubOperScore(CubaOpe);


 //  SUPERV_AVC_TURNO(Cuba).ContVMaxEa[1] = 1;

   printf("EaNumDia : %i \n", SUPERV_AVC_TURNO(Cuba).EaNumDia);
   printf("ContIntEa : %i \n", SUPERV_AVC_TURNO(Cuba).ContIntEa[0]);
   printf("ContVMaxEa0 : %i \n", SUPERV_AVC_TURNO(Cuba).ContVMaxEa[0]);
   printf("ContVMaxEa1 : %i \n", SUPERV_AVC_TURNO(Cuba).ContVMaxEa[1]);
   printf("ContVMaxEa2 : %i \n", SUPERV_AVC_TURNO(Cuba).ContVMaxEa[2]);
   printf("ContVMaxEa3 : %i \n", SUPERV_AVC_TURNO(Cuba).ContVMaxEa[3]);
   printf("ContVMaxEa4 : %i \n", SUPERV_AVC_TURNO(Cuba).ContVMaxEa[4]);
   printf("ContVMaxEa5 : %i \n", SUPERV_AVC_TURNO(Cuba).ContVMaxEa[5]);
   printf("ContVMaxEa6 : %i \n", SUPERV_AVC_TURNO(Cuba).ContVMaxEa[6]);
   printf("ContVMaxEa7 : %i \n", SUPERV_AVC_TURNO(Cuba).ContVMaxEa[7]);
   printf("EaVMax : %f \n", AVC.Ea[Cuba].EaVMax);
   printf("EaContLXLim : %f \n", AVC.Ea[Cuba].EaContLXLim);
   printf("EaContLEspXLim : %f \n", AVC.Ea[Cuba].EaContLEspXLim);
   printf("EaDurXDia : %f \n", SUPERV_AVC(Cuba).EaDurXDia);
   printf("EaVMaxDia : %f \n", SUPERV_AVC(Cuba).EaVMaxDia);


   i=0;
   k=0;


   CubaOpe = 701;
  for(CubaOpe = 701; CubaOpe <= 736 ; CubaOpe++)
  {
   Cuba = ConvCubOperScore(CubaOpe);
   AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
   AVC.ParUser1[Cuba].DelayLadoQueb2 = 720+i;
	i=i+20;
  }	  
   i=0;
   k=0;
  for(CubaOpe = 801; CubaOpe <= 836 ; CubaOpe++)
  {
   Cuba = ConvCubOperScore(CubaOpe);
   AVC.ParUser1[Cuba].DelayLadoQueb1 = 1420-i;
   AVC.ParUser1[Cuba].DelayLadoQueb2 = 700-i;
	i=i+20;
  }	  

   i=0;
   k=0;
  CubaOpe = 1901;
  for(CubaOpe = 1901; CubaOpe <= 1949 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
	i=i+25;
  }
  i=0;
  for(CubaOpe = 1909; CubaOpe >= 1901 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
	i=i+25;
  }
  for(CubaOpe = 1919; CubaOpe >= 1910 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
	i=i+25;
  }
  for(CubaOpe = 1929; CubaOpe >= 1920 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
	i=i+25;
  }
  for(CubaOpe = 1939; CubaOpe >= 1930 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
	i=i+25;
  }
  for(CubaOpe = 1949; CubaOpe >= 1940 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
	i=i+25;
  }

   i=0;
   k=0;
  CubaOpe = 901;
  for(CubaOpe = 901; CubaOpe <= 936 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 875 -i;
    Cuba = ConvCubOperScore(CubaOpe+200);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 875 -i;
	i=i+25;
  }

   i=0;
  for(CubaOpe = 1001; CubaOpe <= 1036 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 1775- i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 900+i;
    Cuba = ConvCubOperScore(CubaOpe+200);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 1775- i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 900+i;
	i=i+25;
  }
   i=0;
  CubaOpe = 936;
  for(CubaOpe = 937; CubaOpe <= 972 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 875 -i;
    Cuba = ConvCubOperScore(CubaOpe+200);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 875 -i;
	i=i+25;
  }

   i=0;
  for(CubaOpe = 1037; CubaOpe <= 1072 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 1775- i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 900+i;
    Cuba = ConvCubOperScore(CubaOpe+200);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 1775- i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 900+i;
	i=i+25;
  }


   i=0;
   k=0;
  CubaOpe = 301;
  for(CubaOpe = 301; CubaOpe <= 336 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 700 -i;
	i=i+25;
  }
  for(CubaOpe = 401; CubaOpe <= 436 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = 1420-i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
	i=i+25;
  }

  i=0;
  for(CubaOpe = 337; CubaOpe <= 380 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
    AVC.ParUser1[Cuba].DelayLadoQueb2 = 860 -i;
	i=i+25;
  }

   i=0;
   k=0;
  CubaOpe = 2001;
  for(CubaOpe = 2001; CubaOpe <= 2049 ; CubaOpe++)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb1 = i;
	i=i+25;
  }
  i=0;
  for(CubaOpe = 2009; CubaOpe >= 2001 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
	i=i+25;
  }
  for(CubaOpe = 2019; CubaOpe >= 2010 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
	i=i+25;
  }
  for(CubaOpe = 2029; CubaOpe >= 2020 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
	i=i+25;
  }
  for(CubaOpe = 2039; CubaOpe >= 2030 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
	i=i+25;
  }
  for(CubaOpe = 2049; CubaOpe >= 2040 ; CubaOpe--)
  {
    Cuba = ConvCubOperScore(CubaOpe);
    AVC.ParUser1[Cuba].DelayLadoQueb2 = i;
	i=i+25;
  }


   i=0;
   k=0;
  CubaOpe = 525;
  Cuba = ConvCubOperScore(CubaOpe);
  for(CubaOpe = 525; CubaOpe <= 530 ; CubaOpe++)
  {
  Cuba = ConvCubOperScore(CubaOpe);
	 EST_AVC(Cuba).Est.ForcaEstAlim = VERDADEIRO;
	 AVC.User1[Cuba].TempoSuspende = 3600;
	 AVC.User3[Cuba].EstForcaAlim = 3;
  }
  for(CubaOpe = 625; CubaOpe <= 630 ; CubaOpe++)
  {
  Cuba = ConvCubOperScore(CubaOpe);
	 EST_AVC(Cuba).Est.ForcaEstAlim = VERDADEIRO;
	 AVC.User1[Cuba].TempoSuspende = 3600;
	 AVC.User3[Cuba].EstForcaAlim = 3;
  }
   i=0;
   k=0;

    CubaOpe = 626;
    Cuba = ConvCubOperScore(CubaOpe);

    printf("EstadoIO : %i \n", AVC.Cleit[Cuba].EstadoIO);

	printf("\nBitSobeAnodo : %d", AVC.Abs[Cuba].BitSobeAnodo);
	printf("\nBitDesceAnodo : %d", AVC.Abs[Cuba].BitDesceAnodo);
	printf("\nBitLampEa : %d", AVC.Abs[Cuba].BitLampEa);
	printf("\nBitLampRec : %d", AVC.Abs[Cuba].BitLampRec);
	printf("\nBitAvPistaoAQuebA : %d", AVC.Abs[Cuba].BitAvPistaoAQuebA);
	printf("\nBitRecPistaoAQuebB : %d", AVC.Abs[Cuba].BitRecPistaoAQuebB);
	printf("\nBitAvPistaoBQuebC : %d", AVC.Abs[Cuba].BitAvPistaoBQuebC);
	printf("\nBitRecPistaoBouM2QuebD : %d", AVC.Abs[Cuba].BitRecPistaoBouM2QuebD);
	printf("\nBitSopro : %d", AVC.Abs[Cuba].BitSopro);
	printf("\nBitSobeCamisaouM1 : %d", AVC.Abs[Cuba].BitSobeCamisaouM1);
	printf("\nBitDescCamOuAvPCAlimA : %d", AVC.Abs[Cuba].BitDescCamOuAvPCAlimA);
	printf("\nBitRecuoPistCAlimB : %d", AVC.Abs[Cuba].BitRecuoPistCAlimB);
	printf("\nBitAvancoPistDAlimC : %d", AVC.Abs[Cuba].BitAvancoPistDAlimC);
	printf("\nBitRecuoPistDAlimD : %d", AVC.Abs[Cuba].BitRecuoPistDAlimD);
	printf("\nBitSireneEA : %d", AVC.Abs[Cuba].BitSireneEA);
	printf("\nBitLiberaMCruzeiro : %d", AVC.Abs[Cuba].BitLiberaMCruzeiro);
	printf("\nBitChaveQueb : %d", AVC.Abs[Cuba].BitChaveQueb);
	printf("\nBitChaveCorr : %d", AVC.Abs[Cuba].BitChaveCorr);
	printf("\nBitChaveLocRem : %d", AVC.Abs[Cuba].BitChaveLocRem);
	printf("\nBitResetEa : %d", AVC.Abs[Cuba].BitResetEa);
	printf("\nBitSubiuAnodo : %d", AVC.Abs[Cuba].BitSubiuAnodo);
	printf("\nBitDesceuAnodo : %d", AVC.Abs[Cuba].BitDesceuAnodo);
	printf("\nBitSubOuMovCamisaouM2 : %d", AVC.Abs[Cuba].BitSubOuMovCamisaouM2);
	printf("\nBitDesCamOuPFAutoouM1 : %d", AVC.Abs[Cuba].BitDesCamOuPFAutoouM1);
	printf("\nBitCheckUp : %d", AVC.Abs[Cuba].BitCheckUp);
	printf("\nBitTrocaPinos : %d", AVC.Abs[Cuba].BitTrocaPinos);
	printf("\nBitSoprou : %d", AVC.Abs[Cuba].BitSoprou);
	printf("\nBitReleFalhaMM : %d", AVC.Abs[Cuba].BitReleFalhaMM);
	printf("\nBitChaveMCruzeiro : %d", AVC.Abs[Cuba].BitChaveMCruzeiro);

//	AVC.Abs[Cuba].BitDesCamOuPFAutoouM1 = 255;
//	AVC.Abs[Cuba].BitCheckUp = 255;

   i=0;
   k=0;

    CubaOpe = 626;
    for(CubaOpe = 619; CubaOpe <= 636 ; CubaOpe++)
    {
  	  Cuba = ConvCubOperScore(CubaOpe);
	  EST_AVC(Cuba).Est.CamisaAlta = FALSO;
	  EST_AVC(Cuba).Est.CamisaBaixa = FALSO;
	  AVC.Abs[Cuba].BitDesCamOuPFAutoouM1 = 255;
	  AVC.Abs[Cuba].BitCheckUp = 255;

	}
    for(CubaOpe = 519; CubaOpe <= 536 ; CubaOpe++)
    {
  	  Cuba = ConvCubOperScore(CubaOpe);
	  EST_AVC(Cuba).Est.CamisaAlta = FALSO;
	  EST_AVC(Cuba).Est.CamisaBaixa = FALSO;
	  AVC.Abs[Cuba].BitDesCamOuPFAutoouM1 = 255;
	  AVC.Abs[Cuba].BitCheckUp = 255;

	}


   i=0;
   k=0;

    CubaOpe = 927;
  	Cuba = ConvCubOperScore(CubaOpe);
	printf("\nValorEnt1 %f \n", AVC.CcontMcp[Cuba].ValorEnt[0]);
	printf("\nValorEnt2 %f \n", AVC.CcontMcp[Cuba].ValorEnt[1]);
	printf("\nValorEnt3 %f \n", AVC.CcontMcp[Cuba].ValorEnt[2]);

   	i=0;
   	k=0;
		
	CubaOpe = 1301;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.15;

	CubaOpe = 1304;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.19;

	CubaOpe = 1305;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.3;

	CubaOpe = 1311;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.22;

	CubaOpe = 1316;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.2;

	CubaOpe = 1317;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.2;

	CubaOpe = 1318;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.14;

	CubaOpe = 1319;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.14;

	CubaOpe = 1324;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.25;

	CubaOpe = 1326;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.28;

	CubaOpe = 1327;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.18;

	CubaOpe = 1328;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.18;

	CubaOpe = 1329;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.16;

	CubaOpe = 1330;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.225;

	CubaOpe = 1331;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.2;

	CubaOpe = 1338;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.2;

	CubaOpe = 1340;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.23;

	CubaOpe = 1404;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.14;

	CubaOpe = 1411;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.22;

	CubaOpe = 1412;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.23;

	CubaOpe = 1416;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.22;

	CubaOpe = 1418;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.24;

	CubaOpe = 1423;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.25;

	CubaOpe = 1428;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.19;

	CubaOpe = 1429;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.22;

	CubaOpe = 1430;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.15;

	CubaOpe = 1431;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.15;

	CubaOpe = 1436;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.16;

	CubaOpe = 1438;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.3;

	CubaOpe = 1439;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.15;

	CubaOpe = 1503;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.35;

	CubaOpe = 1521;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.24;

	CubaOpe = 1524;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.2;

	CubaOpe = 1526;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.2;

	CubaOpe = 1529;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.27;

	CubaOpe = 1538;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.2;

	CubaOpe = 1604;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.15;

	CubaOpe = 1611;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.24;

	CubaOpe = 1613;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.21;

	CubaOpe = 1619;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.2;

	CubaOpe = 1624;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.21;

	CubaOpe = 1630;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.2;

	CubaOpe = 1634;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.21;

	CubaOpe = 1635;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].VSetPointCnf = 4.24;

   for(CubaOpe = 737; CubaOpe <= 772 ; CubaOpe++)
   {
     Cuba = ConvCubOperScore(CubaOpe);
	 AVC.Param[Cuba].VSetPointCnf-= 0.01;
   }

   for(CubaOpe = 837; CubaOpe <= 872 ; CubaOpe++)
   {
     Cuba = ConvCubOperScore(CubaOpe);
	 AVC.Param[Cuba].VSetPointCnf-= 0.01;
   }

	i=0;
	k=0;
    CubaOpe = 927;
    Cuba = ConvCubOperScore(CubaOpe);
	printf("\nNumAnasAtn8 : %d", AVC.Abs[Cuba].NumAnasAtn8);

    CubaOpe = 1206;
    Cuba = ConvCubOperScore(CubaOpe);
	printf("\nNumAnasAtn8 : %d", AVC.Abs[Cuba].NumAnasAtn8);
	AVC.Abs[Cuba].NumAnasAtn8 = 3;

	i = 0;
	k = 0;

	CubaOpe = 519;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].EaAtrasoMax = 28800;
	CubaOpe = 520;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].DifResFimUnder = 0.23;
	CubaOpe = 521;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].EaAtrasoMax = 28800;
	CubaOpe = 522;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].DifResFimUnder = 0.23;
	CubaOpe = 523;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AtivaBitCLP = 1;
	CubaOpe = 524;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].EaAtrasoMax = 28800;
	CubaOpe = 525;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].BitDuploOver = 17;
	CubaOpe = 526;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AtivaBitCLP = 1;
	CubaOpe = 527;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].EaAtrasoMax = 28800;
	CubaOpe = 535;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].DifResFimUnder = 0.23;
	CubaOpe = 621;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AtivaBitCLP = 1;
	CubaOpe = 628;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AlF3Dia = 30;
	CubaOpe = 519;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].BitDuploOver = 17;
	CubaOpe = 520;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AtivaBitCLP = 1;
	CubaOpe = 521;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].DifResFimUnder = 0.23;
	CubaOpe = 522;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AtivaBitCLP = 1;
	CubaOpe = 523;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].DifResFimUnder = 0.23;
	CubaOpe = 524;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].EaAtrasoMax = 28800;
	CubaOpe = 525;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].CAFimUnder = 9.00;
	CubaOpe = 526;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AtivaBitCLP = 1;
	CubaOpe = 527;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].BitDuploOver = 17;
	CubaOpe = 623;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AlF3Dia = 20;
	CubaOpe = 626;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].CAFimUnder = 9.00;
	CubaOpe = 627;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].BitDuploOver = 17;
	CubaOpe = 628;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].EaAtrasoMax = 1440;
	CubaOpe = 629;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].DifResFimUnder = 0.23;
	CubaOpe = 631;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AlF3Dia = 20;
	CubaOpe = 519;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].CAFimUnder = 9.00;
	CubaOpe = 520;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].CAFimUnder = 9.00;
	CubaOpe = 521;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].DifResFimUnder = 0.23;
	CubaOpe = 522;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].EaAtrasoMax = 28800;
	CubaOpe = 523;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].DifResFimUnder = 0.23;
	CubaOpe = 524;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].EaAtrasoMax = 28800;
	CubaOpe = 525;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].DifResFimUnder = 0.23;
	CubaOpe = 526;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].DifResFimUnder = 0.23;
	CubaOpe = 527;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].CAFimUnder = 9.00;
	CubaOpe = 619;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].BitDuploOver = 17;
	CubaOpe = 621;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AtivaBitCLP = 1;
	CubaOpe = 627;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AlF3Dia = 20;
	CubaOpe = 629;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].EaAtrasoMax = 28800;
	CubaOpe = 519;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].DifResFimUnder = 0.23;
	CubaOpe = 520;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].CAFimUnder = 9.00;
	CubaOpe = 521;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].BitDuploOver = 17;
	CubaOpe = 522;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AtivaBitCLP = 1;
	CubaOpe = 523;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AlF3Dia = 20;
	CubaOpe = 524;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].EaAtrasoMax = 28800;
	CubaOpe = 525;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].DifResFimUnder = 0.23;
	CubaOpe = 526;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].CAFimUnder = 9.00;
	CubaOpe = 527;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].BitDuploOver = 17;
	CubaOpe = 533;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AtivaBitCLP = 1;
	CubaOpe = 534;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AlF3Dia = 20;
	CubaOpe = 620;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].EaAtrasoMax = 28800;
	CubaOpe = 623;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].DifResFimUnder = 0.23;
	CubaOpe = 502;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].CAFimUnder = 9.00;
	CubaOpe = 502;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].BitDuploOver = 17;
	CubaOpe = 503;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AtivaBitCLP = 1;
	CubaOpe = 503;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AlF3Dia = 15;
	CubaOpe = 504;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].EaAtrasoMax = 28800;
	CubaOpe = 504;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].DifResFimUnder = 0.23;
	CubaOpe = 505;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].CAFimUnder = 9.00;
	CubaOpe = 505;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].BitDuploOver = 17;
	CubaOpe = 506;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AtivaBitCLP = 1;
	CubaOpe = 506;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AlF3Dia = 20;
	CubaOpe = 507;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].EaAtrasoMax = 28800;
	CubaOpe = 507;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].DifResFimUnder = 0.23;
	CubaOpe = 508;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].CAFimUnder = 9.00;
	CubaOpe = 508;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].BitDuploOver = 17;
	CubaOpe = 509;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AtivaBitCLP = 1;
	CubaOpe = 509;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AlF3Dia = 15;
	CubaOpe = 510;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].EaAtrasoMax = 28800;
	CubaOpe = 510;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].DifResFimUnder = 0.23;
	CubaOpe = 511;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].CAFimUnder = 9.00;
	CubaOpe = 511;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].BitDuploOver = 17;
	CubaOpe = 512;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AtivaBitCLP = 1;
	CubaOpe = 512;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AlF3Dia = 15;
	CubaOpe = 513;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].EaAtrasoMax = 28800;
	CubaOpe = 513;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].DifResFimUnder = 0.23;
	CubaOpe = 514;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].CAFimUnder = 9.00;
	CubaOpe = 514;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].BitDuploOver = 17;
	CubaOpe = 515;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AtivaBitCLP = 1;
	CubaOpe = 515;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AlF3Dia = 10;
	CubaOpe = 516;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].EaAtrasoMax = 28880;
	CubaOpe = 516;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].DifResFimUnder = 0.23;
	CubaOpe = 517;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].CAFimUnder = 9.00;
	CubaOpe = 517;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser2[Cuba].BitDuploOver = 17;
	CubaOpe = 518;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AtivaBitCLP = 1;
	CubaOpe = 518;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.ParUser1[Cuba].AlF3Dia = 10;
	CubaOpe = 519;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].EaAtrasoMax = 28880;
	CubaOpe = 519;
	Cuba = ConvCubOperScore(CubaOpe);
	AVC.Param[Cuba].EaAtrasoMax = 1440;

*/

	i=0;
	k=0;

	printf("\n Reducao: %d \n\n", Comum->IdentReducao);

	switch(Comum->IdentReducao)
	{
		case 2:
			
			CubaOpe = 301;
			Cuba = ConvCubOperScore(CubaOpe);

			printf("EstadoIO : %i \n", AVC.Cleit[Cuba].EstadoIO);

			printf("\nBitSobeAnodo : %d", AVC.Abs[Cuba].BitSobeAnodo);
			printf("\nBitDesceAnodo : %d", AVC.Abs[Cuba].BitDesceAnodo);
			printf("\nBitLampEa : %d", AVC.Abs[Cuba].BitLampEa);
			printf("\nBitLampRec : %d", AVC.Abs[Cuba].BitLampRec);
			printf("\nBitAvPistaoAQuebA : %d", AVC.Abs[Cuba].BitAvPistaoAQuebA);
			printf("\nBitRecPistaoAQuebB : %d", AVC.Abs[Cuba].BitRecPistaoAQuebB);
			printf("\nBitAvPistaoBQuebC : %d", AVC.Abs[Cuba].BitAvPistaoBQuebC);
			printf("\nBitRecPistaoBouM2QuebD : %d", AVC.Abs[Cuba].BitRecPistaoBouM2QuebD);
			printf("\nBitSopro : %d", AVC.Abs[Cuba].BitSopro);
			printf("\nBitSobeCamisaouM1 : %d", AVC.Abs[Cuba].BitSobeCamisaouM1);
			printf("\nBitDescCamOuAvPCAlimA : %d", AVC.Abs[Cuba].BitDescCamOuAvPCAlimA);
			printf("\nBitRecuoPistCAlimB : %d", AVC.Abs[Cuba].BitRecuoPistCAlimB);
			printf("\nBitAvancoPistDAlimC : %d", AVC.Abs[Cuba].BitAvancoPistDAlimC);
			printf("\nBitRecuoPistDAlimD : %d", AVC.Abs[Cuba].BitRecuoPistDAlimD);
			printf("\nBitSireneEA : %d", AVC.Abs[Cuba].BitSireneEA);
			printf("\nBitLiberaMCruzeiro : %d", AVC.Abs[Cuba].BitLiberaMCruzeiro);
			printf("\nBitChaveQueb : %d", AVC.Abs[Cuba].BitChaveQueb);
			printf("\nBitChaveCorr : %d", AVC.Abs[Cuba].BitChaveCorr);
			printf("\nBitChaveLocRem : %d", AVC.Abs[Cuba].BitChaveLocRem);
			printf("\nBitResetEa : %d", AVC.Abs[Cuba].BitResetEa);
			printf("\nBitSubiuAnodo : %d", AVC.Abs[Cuba].BitSubiuAnodo);
			printf("\nBitDesceuAnodo : %d", AVC.Abs[Cuba].BitDesceuAnodo);
			printf("\nBitSubOuMovCamisaouM2 : %d", AVC.Abs[Cuba].BitSubOuMovCamisaouM2);
			printf("\nBitDesCamOuPFAutoouM1 : %d", AVC.Abs[Cuba].BitDesCamOuPFAutoouM1);
			printf("\nBitCheckUp : %d", AVC.Abs[Cuba].BitCheckUp);
			printf("\nBitTrocaPinos : %d", AVC.Abs[Cuba].BitTrocaPinos);
			printf("\nBitSoprou : %d", AVC.Abs[Cuba].BitSoprou);
			printf("\nBitReleFalhaMM : %d", AVC.Abs[Cuba].BitReleFalhaMM);
			printf("\nBitChaveMCruzeiro : %d", AVC.Abs[Cuba].BitChaveMCruzeiro);

		break;

		case 3:
			
			CubaOpe = 501;
			Cuba = ConvCubOperScore(CubaOpe);

			printf("EstadoIO : %i \n", AVC.Cleit[Cuba].EstadoIO);

			printf("\nBitSobeAnodo : %d", AVC.Abs[Cuba].BitSobeAnodo);
			printf("\nBitDesceAnodo : %d", AVC.Abs[Cuba].BitDesceAnodo);
			printf("\nBitLampEa : %d", AVC.Abs[Cuba].BitLampEa);
			printf("\nBitLampRec : %d", AVC.Abs[Cuba].BitLampRec);
			printf("\nBitAvPistaoAQuebA : %d", AVC.Abs[Cuba].BitAvPistaoAQuebA);
			printf("\nBitRecPistaoAQuebB : %d", AVC.Abs[Cuba].BitRecPistaoAQuebB);
			printf("\nBitAvPistaoBQuebC : %d", AVC.Abs[Cuba].BitAvPistaoBQuebC);
			printf("\nBitRecPistaoBouM2QuebD : %d", AVC.Abs[Cuba].BitRecPistaoBouM2QuebD);
			printf("\nBitSopro : %d", AVC.Abs[Cuba].BitSopro);
			printf("\nBitSobeCamisaouM1 : %d", AVC.Abs[Cuba].BitSobeCamisaouM1);
			printf("\nBitDescCamOuAvPCAlimA : %d", AVC.Abs[Cuba].BitDescCamOuAvPCAlimA);
			printf("\nBitRecuoPistCAlimB : %d", AVC.Abs[Cuba].BitRecuoPistCAlimB);
			printf("\nBitAvancoPistDAlimC : %d", AVC.Abs[Cuba].BitAvancoPistDAlimC);
			printf("\nBitRecuoPistDAlimD : %d", AVC.Abs[Cuba].BitRecuoPistDAlimD);
			printf("\nBitSireneEA : %d", AVC.Abs[Cuba].BitSireneEA);
			printf("\nBitLiberaMCruzeiro : %d", AVC.Abs[Cuba].BitLiberaMCruzeiro);
			printf("\nBitChaveQueb : %d", AVC.Abs[Cuba].BitChaveQueb);
			printf("\nBitChaveCorr : %d", AVC.Abs[Cuba].BitChaveCorr);
			printf("\nBitChaveLocRem : %d", AVC.Abs[Cuba].BitChaveLocRem);
			printf("\nBitResetEa : %d", AVC.Abs[Cuba].BitResetEa);
			printf("\nBitSubiuAnodo : %d", AVC.Abs[Cuba].BitSubiuAnodo);
			printf("\nBitDesceuAnodo : %d", AVC.Abs[Cuba].BitDesceuAnodo);
			printf("\nBitSubOuMovCamisaouM2 : %d", AVC.Abs[Cuba].BitSubOuMovCamisaouM2);
			printf("\nBitDesCamOuPFAutoouM1 : %d", AVC.Abs[Cuba].BitDesCamOuPFAutoouM1);
			printf("\nBitCheckUp : %d", AVC.Abs[Cuba].BitCheckUp);
			printf("\nBitTrocaPinos : %d", AVC.Abs[Cuba].BitTrocaPinos);
			printf("\nBitSoprou : %d", AVC.Abs[Cuba].BitSoprou);
			printf("\nBitReleFalhaMM : %d", AVC.Abs[Cuba].BitReleFalhaMM);
			printf("\nBitChaveMCruzeiro : %d", AVC.Abs[Cuba].BitChaveMCruzeiro);
			
		break;

		case 4:
			
			CubaOpe = 701;
			Cuba = ConvCubOperScore(CubaOpe);

			printf("EstadoIO : %i \n", AVC.Cleit[Cuba].EstadoIO);

			printf("\nBitSobeAnodo : %d", AVC.Abs[Cuba].BitSobeAnodo);
			printf("\nBitDesceAnodo : %d", AVC.Abs[Cuba].BitDesceAnodo);
			printf("\nBitLampEa : %d", AVC.Abs[Cuba].BitLampEa);
			printf("\nBitLampRec : %d", AVC.Abs[Cuba].BitLampRec);
			printf("\nBitAvPistaoAQuebA : %d", AVC.Abs[Cuba].BitAvPistaoAQuebA);
			printf("\nBitRecPistaoAQuebB : %d", AVC.Abs[Cuba].BitRecPistaoAQuebB);
			printf("\nBitAvPistaoBQuebC : %d", AVC.Abs[Cuba].BitAvPistaoBQuebC);
			printf("\nBitRecPistaoBouM2QuebD : %d", AVC.Abs[Cuba].BitRecPistaoBouM2QuebD);
			printf("\nBitSopro : %d", AVC.Abs[Cuba].BitSopro);
			printf("\nBitSobeCamisaouM1 : %d", AVC.Abs[Cuba].BitSobeCamisaouM1);
			printf("\nBitDescCamOuAvPCAlimA : %d", AVC.Abs[Cuba].BitDescCamOuAvPCAlimA);
			printf("\nBitRecuoPistCAlimB : %d", AVC.Abs[Cuba].BitRecuoPistCAlimB);
			printf("\nBitAvancoPistDAlimC : %d", AVC.Abs[Cuba].BitAvancoPistDAlimC);
			printf("\nBitRecuoPistDAlimD : %d", AVC.Abs[Cuba].BitRecuoPistDAlimD);
			printf("\nBitSireneEA : %d", AVC.Abs[Cuba].BitSireneEA);
			printf("\nBitLiberaMCruzeiro : %d", AVC.Abs[Cuba].BitLiberaMCruzeiro);
			printf("\nBitChaveQueb : %d", AVC.Abs[Cuba].BitChaveQueb);
			printf("\nBitChaveCorr : %d", AVC.Abs[Cuba].BitChaveCorr);
			printf("\nBitChaveLocRem : %d", AVC.Abs[Cuba].BitChaveLocRem);
			printf("\nBitResetEa : %d", AVC.Abs[Cuba].BitResetEa);
			printf("\nBitSubiuAnodo : %d", AVC.Abs[Cuba].BitSubiuAnodo);
			printf("\nBitDesceuAnodo : %d", AVC.Abs[Cuba].BitDesceuAnodo);
			printf("\nBitSubOuMovCamisaouM2 : %d", AVC.Abs[Cuba].BitSubOuMovCamisaouM2);
			printf("\nBitDesCamOuPFAutoouM1 : %d", AVC.Abs[Cuba].BitDesCamOuPFAutoouM1);
			printf("\nBitCheckUp : %d", AVC.Abs[Cuba].BitCheckUp);
			printf("\nBitTrocaPinos : %d", AVC.Abs[Cuba].BitTrocaPinos);
			printf("\nBitSoprou : %d", AVC.Abs[Cuba].BitSoprou);
			printf("\nBitReleFalhaMM : %d", AVC.Abs[Cuba].BitReleFalhaMM);
			printf("\nBitChaveMCruzeiro : %d", AVC.Abs[Cuba].BitChaveMCruzeiro);
			
		break;

		case 7:
			
			CubaOpe = 901;
			Cuba = ConvCubOperScore(CubaOpe);

			printf("EstadoIO : %i \n", AVC.Cleit[Cuba].EstadoIO);

			printf("\nBitSobeAnodo : %d", AVC.Abs[Cuba].BitSobeAnodo);
			printf("\nBitDesceAnodo : %d", AVC.Abs[Cuba].BitDesceAnodo);
			printf("\nBitLampEa : %d", AVC.Abs[Cuba].BitLampEa);
			printf("\nBitLampRec : %d", AVC.Abs[Cuba].BitLampRec);
			printf("\nBitAvPistaoAQuebA : %d", AVC.Abs[Cuba].BitAvPistaoAQuebA);
			printf("\nBitRecPistaoAQuebB : %d", AVC.Abs[Cuba].BitRecPistaoAQuebB);
			printf("\nBitAvPistaoBQuebC : %d", AVC.Abs[Cuba].BitAvPistaoBQuebC);
			printf("\nBitRecPistaoBouM2QuebD : %d", AVC.Abs[Cuba].BitRecPistaoBouM2QuebD);
			printf("\nBitSopro : %d", AVC.Abs[Cuba].BitSopro);
			printf("\nBitSobeCamisaouM1 : %d", AVC.Abs[Cuba].BitSobeCamisaouM1);
			printf("\nBitDescCamOuAvPCAlimA : %d", AVC.Abs[Cuba].BitDescCamOuAvPCAlimA);
			printf("\nBitRecuoPistCAlimB : %d", AVC.Abs[Cuba].BitRecuoPistCAlimB);
			printf("\nBitAvancoPistDAlimC : %d", AVC.Abs[Cuba].BitAvancoPistDAlimC);
			printf("\nBitRecuoPistDAlimD : %d", AVC.Abs[Cuba].BitRecuoPistDAlimD);
			printf("\nBitSireneEA : %d", AVC.Abs[Cuba].BitSireneEA);
			printf("\nBitLiberaMCruzeiro : %d", AVC.Abs[Cuba].BitLiberaMCruzeiro);
			printf("\nBitChaveQueb : %d", AVC.Abs[Cuba].BitChaveQueb);
			printf("\nBitChaveCorr : %d", AVC.Abs[Cuba].BitChaveCorr);
			printf("\nBitChaveLocRem : %d", AVC.Abs[Cuba].BitChaveLocRem);
			printf("\nBitResetEa : %d", AVC.Abs[Cuba].BitResetEa);
			printf("\nBitSubiuAnodo : %d", AVC.Abs[Cuba].BitSubiuAnodo);
			printf("\nBitDesceuAnodo : %d", AVC.Abs[Cuba].BitDesceuAnodo);
			printf("\nBitSubOuMovCamisaouM2 : %d", AVC.Abs[Cuba].BitSubOuMovCamisaouM2);
			printf("\nBitDesCamOuPFAutoouM1 : %d", AVC.Abs[Cuba].BitDesCamOuPFAutoouM1);
			printf("\nBitCheckUp : %d", AVC.Abs[Cuba].BitCheckUp);
			printf("\nBitTrocaPinos : %d", AVC.Abs[Cuba].BitTrocaPinos);
			printf("\nBitSoprou : %d", AVC.Abs[Cuba].BitSoprou);
			printf("\nBitReleFalhaMM : %d", AVC.Abs[Cuba].BitReleFalhaMM);
			printf("\nBitChaveMCruzeiro : %d", AVC.Abs[Cuba].BitChaveMCruzeiro);
			
		break;

		case 8:
			
			CubaOpe = 1301;
			Cuba = ConvCubOperScore(CubaOpe);

			printf("EstadoIO : %i \n", AVC.Cleit[Cuba].EstadoIO);

			printf("\nBitSobeAnodo : %d", AVC.Abs[Cuba].BitSobeAnodo);
			printf("\nBitDesceAnodo : %d", AVC.Abs[Cuba].BitDesceAnodo);
			printf("\nBitLampEa : %d", AVC.Abs[Cuba].BitLampEa);
			printf("\nBitLampRec : %d", AVC.Abs[Cuba].BitLampRec);
			printf("\nBitAvPistaoAQuebA : %d", AVC.Abs[Cuba].BitAvPistaoAQuebA);
			printf("\nBitRecPistaoAQuebB : %d", AVC.Abs[Cuba].BitRecPistaoAQuebB);
			printf("\nBitAvPistaoBQuebC : %d", AVC.Abs[Cuba].BitAvPistaoBQuebC);
			printf("\nBitRecPistaoBouM2QuebD : %d", AVC.Abs[Cuba].BitRecPistaoBouM2QuebD);
			printf("\nBitSopro : %d", AVC.Abs[Cuba].BitSopro);
			printf("\nBitSobeCamisaouM1 : %d", AVC.Abs[Cuba].BitSobeCamisaouM1);
			printf("\nBitDescCamOuAvPCAlimA : %d", AVC.Abs[Cuba].BitDescCamOuAvPCAlimA);
			printf("\nBitRecuoPistCAlimB : %d", AVC.Abs[Cuba].BitRecuoPistCAlimB);
			printf("\nBitAvancoPistDAlimC : %d", AVC.Abs[Cuba].BitAvancoPistDAlimC);
			printf("\nBitRecuoPistDAlimD : %d", AVC.Abs[Cuba].BitRecuoPistDAlimD);
			printf("\nBitSireneEA : %d", AVC.Abs[Cuba].BitSireneEA);
			printf("\nBitLiberaMCruzeiro : %d", AVC.Abs[Cuba].BitLiberaMCruzeiro);
			printf("\nBitChaveQueb : %d", AVC.Abs[Cuba].BitChaveQueb);
			printf("\nBitChaveCorr : %d", AVC.Abs[Cuba].BitChaveCorr);
			printf("\nBitChaveLocRem : %d", AVC.Abs[Cuba].BitChaveLocRem);
			printf("\nBitResetEa : %d", AVC.Abs[Cuba].BitResetEa);
			printf("\nBitSubiuAnodo : %d", AVC.Abs[Cuba].BitSubiuAnodo);
			printf("\nBitDesceuAnodo : %d", AVC.Abs[Cuba].BitDesceuAnodo);
			printf("\nBitSubOuMovCamisaouM2 : %d", AVC.Abs[Cuba].BitSubOuMovCamisaouM2);
			printf("\nBitDesCamOuPFAutoouM1 : %d", AVC.Abs[Cuba].BitDesCamOuPFAutoouM1);
			printf("\nBitCheckUp : %d", AVC.Abs[Cuba].BitCheckUp);
			printf("\nBitTrocaPinos : %d", AVC.Abs[Cuba].BitTrocaPinos);
			printf("\nBitSoprou : %d", AVC.Abs[Cuba].BitSoprou);
			printf("\nBitReleFalhaMM : %d", AVC.Abs[Cuba].BitReleFalhaMM);
			printf("\nBitChaveMCruzeiro : %d", AVC.Abs[Cuba].BitChaveMCruzeiro);
			
		break;

		case 9:
			
			CubaOpe = 1701;
			Cuba = ConvCubOperScore(CubaOpe);

			printf("EstadoIO : %i \n", AVC.Cleit[Cuba].EstadoIO);

			printf("\nBitSobeAnodo : %d", AVC.Abs[Cuba].BitSobeAnodo);
			printf("\nBitDesceAnodo : %d", AVC.Abs[Cuba].BitDesceAnodo);
			printf("\nBitLampEa : %d", AVC.Abs[Cuba].BitLampEa);
			printf("\nBitLampRec : %d", AVC.Abs[Cuba].BitLampRec);
			printf("\nBitAvPistaoAQuebA : %d", AVC.Abs[Cuba].BitAvPistaoAQuebA);
			printf("\nBitRecPistaoAQuebB : %d", AVC.Abs[Cuba].BitRecPistaoAQuebB);
			printf("\nBitAvPistaoBQuebC : %d", AVC.Abs[Cuba].BitAvPistaoBQuebC);
			printf("\nBitRecPistaoBouM2QuebD : %d", AVC.Abs[Cuba].BitRecPistaoBouM2QuebD);
			printf("\nBitSopro : %d", AVC.Abs[Cuba].BitSopro);
			printf("\nBitSobeCamisaouM1 : %d", AVC.Abs[Cuba].BitSobeCamisaouM1);
			printf("\nBitDescCamOuAvPCAlimA : %d", AVC.Abs[Cuba].BitDescCamOuAvPCAlimA);
			printf("\nBitRecuoPistCAlimB : %d", AVC.Abs[Cuba].BitRecuoPistCAlimB);
			printf("\nBitAvancoPistDAlimC : %d", AVC.Abs[Cuba].BitAvancoPistDAlimC);
			printf("\nBitRecuoPistDAlimD : %d", AVC.Abs[Cuba].BitRecuoPistDAlimD);
			printf("\nBitSireneEA : %d", AVC.Abs[Cuba].BitSireneEA);
			printf("\nBitLiberaMCruzeiro : %d", AVC.Abs[Cuba].BitLiberaMCruzeiro);
			printf("\nBitChaveQueb : %d", AVC.Abs[Cuba].BitChaveQueb);
			printf("\nBitChaveCorr : %d", AVC.Abs[Cuba].BitChaveCorr);
			printf("\nBitChaveLocRem : %d", AVC.Abs[Cuba].BitChaveLocRem);
			printf("\nBitResetEa : %d", AVC.Abs[Cuba].BitResetEa);
			printf("\nBitSubiuAnodo : %d", AVC.Abs[Cuba].BitSubiuAnodo);
			printf("\nBitDesceuAnodo : %d", AVC.Abs[Cuba].BitDesceuAnodo);
			printf("\nBitSubOuMovCamisaouM2 : %d", AVC.Abs[Cuba].BitSubOuMovCamisaouM2);
			printf("\nBitDesCamOuPFAutoouM1 : %d", AVC.Abs[Cuba].BitDesCamOuPFAutoouM1);
			printf("\nBitCheckUp : %d", AVC.Abs[Cuba].BitCheckUp);
			printf("\nBitTrocaPinos : %d", AVC.Abs[Cuba].BitTrocaPinos);
			printf("\nBitSoprou : %d", AVC.Abs[Cuba].BitSoprou);
			printf("\nBitReleFalhaMM : %d", AVC.Abs[Cuba].BitReleFalhaMM);
			printf("\nBitChaveMCruzeiro : %d", AVC.Abs[Cuba].BitChaveMCruzeiro);
			
		break;

	}	

}