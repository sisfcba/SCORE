 /******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: SCORE

	SISTEMA		: TODOS QUE USEM O ALGORITMO DE CONTROLE DO SCORE (CBA etc)

	ARQUIVO		: MccControle.c

	CONTEUDO	: Modulo do algoritmo de Controle das Cubas - MccControle
	
				  Modulo responsavel pelo controle da posicao dos anodos  das 
				  cubas.   Este  controle e' feito com base nos dados basicos 
				  obtidos no modulo MCP (Modulo de Calculos Primarios)  e  de 
				  outros  parametros  relacionados  com  a  configuracao  e o 
				  status das cubas e  da  linha.  E'  chamado  pelo  programa
				  MccCba.

				  Este modulo e'  encarregado  estritamente  do   controle  e 
				  previsao  de  Efeito  Anodico.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 2.0		  -		  DATA  : 04/03/97

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
05/07/94 | Edicao inicial de migracao para o QNX 4.2			  | Leonel
-------------------------------------------------------------------------------
21/09/94 | Incluida habilitacao de excessao por divisao por zero  | Leonel
-------------------------------------------------------------------------------
13/12/94 | Inclusao tratamento de VAlvo para cuba fora de leitura | Carlos
         | ou em estado diferente de normal.                      |
-------------------------------------------------------------------------------
16/12/94 | Substituicao da variavel VAlvo da base de dados pelo	  | Carlos
         | seu calculo na geracao de eventos                      |
-------------------------------------------------------------------------------
03/03/95 | Inibe controle por periodo parametrizado, na partida   | Leonel
         | do sistema e apos linha religada.                      |
-------------------------------------------------------------------------------
28/03/95 | Incluido tratamento para tabela de operacao.           | Leonel
-------------------------------------------------------------------------------
06/07/95 | Desconsiderado  limite  de  incremento maximo quando a | Carlos
         | tabela de incrementos de operacao estiver atuando.	  |
-------------------------------------------------------------------------------
06/01/96 | Inicializada EaPrevVirada na funcao IniMccScore.       | Carlos
-------------------------------------------------------------------------------
01/10/96 | Acrescentada variavel VInc (RInc*INominal) para Grafic.| Leonel
-------------------------------------------------------------------------------
21/02/97 | Substituida tabela Param por  Ccont  para variaveis    | Carlos
         | VSetPoint e Banda*Atual                                |
-------------------------------------------------------------------------------
04/03/97 | Edicao inicial da Versao 2. Separacao do Algoritmo do  | Leonel
         | Score do kernel (MCC).                                 |
-------------------------------------------------------------------------------
16/12/97 | Desmembrado teste de TEfeitoMove para TEfeitoMoveCima  | Carlos
         | e TEfeitoMoveBaixo.                                    |
-------------------------------------------------------------------------------
20/04/98 | Inclusao da chamada da funcao de quebrada preventiva   | Carlos
-------------------------------------------------------------------------------
03/08/98 | Inclusao da chamada da funcao de subida de camisa      | Carlos
-------------------------------------------------------------------------------
03/03/99 | Acrescentada reinicializacao dos ultimos acumulados de | Leonel
         | ruido quando LinhaAtiva == FALSO                       |
-------------------------------------------------------------------------------
25/06/99 | Incluido tratamento de booster de corrente			  | Carlos
-------------------------------------------------------------------------------
03/07/02 | Incluido ativa/desat. booster pelo operador atraves da | Carlos
         | variavel BoosterAtivo                                  |
-------------------------------------------------------------------------------
29/11/02 | Inclusao ajuste camisa para sala 125ka.                | Leonel
-------------------------------------------------------------------------------
12/11/12 | Alterado para limitar o numero de movimentacoes por 	  | Marco
		 | ciclo.												  |
-------------------------------------------------------------------------------
$Id: MccControle.c,v 1.1.2.1 2012/09/28 17:09:27 leo Exp $

$Log: MccControle.c,v $
Revision 1.1.2.1  2012/09/28 17:09:27  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

Revision 1.9  2008/10/13 17:49:37  leo
Algoritmo de manobra de cruzeiro.

Revision 1.8  2008/07/02 20:24:27  alex
nao subir camisa junto com movimentacao de anodo
e quando sinalizar quebrada mover para cima

Revision 1.7  2007/09/28 14:46:25  rogerio
Alteracao para incluir sala I com atn8

Revision 1.6  2007/03/01 18:02:33  leo
Correcao de tratamento de manobra de cruzeiro.

Revision 1.4.2.1  2004/10/08 14:21:43  leo
Arquivos nao usados

Revision 1.4  2004/04/08 19:21:14  leo
Inclusao da sala 125 kA VI.

Revision 1.3  2003/03/28 12:42:37  leo
Tratamento de tabela de partida - versao 5.01.0005.

Revision 1.2  2003/03/13 20:55:07  leo
Inclusao do tratamento da tabela de partida de cubas.

******************************************************************************/
/*
-------------------------------------------------------------------------------
                           Definicao de compilacao condicional
-------------------------------------------------------------------------------
*/

/**** #define		ATIVA_DEPURACAO *******/

/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include	<MccCba.h>
#include	<Eventos.h>
#include	<Prototipos.h>
#include	<time.h>
#include	<sys/kernel.h>
#include	<string.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include	<AjusteCamisa.h>
/*
-------------------------------------------------------------------------------
                           Variaveis Globais
-------------------------------------------------------------------------------
*/
/* -- Apontadores para as tabelas comuns -- */
#include	<VarsComum.h>

/*
-------------------------------------------------------------------------------
                           Variaveis Locais
-------------------------------------------------------------------------------
*/
/*
-------------------------------------------------------------------------------
                           Tipos de dados
-------------------------------------------------------------------------------
*/

/*
-------------------------------------------------------------------------------
                           Prototipos
-------------------------------------------------------------------------------
*/
void IniMccCtrlCuba(int Cuba);
void CalculaRAlvo(int Cuba);
void CalcTempoEfeitos(int Cuba);
void VerificaBSupMovel(int Cuba);
void VerificaAgarraCamisa(int Cuba);
/*
-------------------------------------------------------------------------------
                           MccControle
-------------------------------------------------------------------------------
*/
void MccControle(void)
{
	
	int CubaOpe, Cuba;
	int zeramov;

	DEPURA(printf("Mcc-> Recebi ativacao ciclo controle\n");)

	/* -- Posicao para caso de f.p. exception -- */
	PosicaoGlobal=20;
	
	for(zeramov=0; zeramov<=16 ; zeramov++)
	{
		NumMov[zeramov] = 0;
	}

	if(AVL.Par.HabImportSIAP eq VERDADEIRO)
	{
		AlocaSemaf(SEMAF_AVC);
		ImportaSIAP();
		LiberaSemaf(SEMAF_AVC);
	}

	PosicaoGlobal=21;

	/* -- Executa os calculos de controle -- */
	for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
	{
		Cuba=ConvCubOperScore(CubaOpe);
		if (Cuba eq -1)
			continue;

		PosicaoGlobal=22;

		/* -- Aloca semaforo para acesso a tabela de cubas -- */
		AlocaSemaf(SEMAF_AVC);

		if (AVL.MudancaDia > 0 and AvcLocal[Cuba].AlterouVida eq 0)
		{
			AVC.User1[Cuba].Vida++;
			AvcLocal[Cuba].AlterouVida = 1;
			EST_AVC(Cuba).Est.TabelaAlF3 = FALSO;
		}
		else
		{
			AvcLocal[Cuba].AlterouVida = 0;
		}

		if(AVL.MudancaTurno > 0)
		{
			EST_AVC(Cuba).Est.AjusteCamTur = VERDADEIRO;
		}

		/* Ativa Bit de comunicacao CLP New Soderberg */
		if (AVC.ParUser1[Cuba].AtivaBitCLP eq VERDADEIRO)
		{
			ComandaSaidaRem(Cuba, LIGAR, 18, 0);
			EST_AVC(Cuba).Est.BitCLP = VERDADEIRO;
		} 


		if( (HoraAtualCtrl > (AVC.User2[Cuba].HoraIniFormaBanho + AVC.User2[Cuba].DurFormaBanho)) and
		EST_AVC(Cuba).Est.FormaBanho eq VERDADEIRO)		 
		{
			EST_AVC(Cuba).Est.FormaBanho = FALSO;
			AVC.User2[Cuba].IncFormaBanho = 0.0;
			AVC.User2[Cuba].DurFormaBanho = 0;  
			GeraEvento(EV_FORMABANHO, Cuba, -1, "Controle", "Fim", AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal+AVC.Param[Cuba].Bemf,
					AVC.Cleit[Cuba].Vinst,AVC.Ccont[Cuba].RAlvo);
		}
		else if(EST_AVC(Cuba).Est.FormaBanho eq VERDADEIRO)
		{
			if( SUPERV_AVC(Cuba).Sup.FormaBanho eq FALSO)
			{
				SUPERV_AVC(Cuba).Sup.FormaBanho = VERDADEIRO;	
			}

			if( SUPERV_AVC_TURNO(Cuba).Sup.FormaBanho eq FALSO)
			{
				SUPERV_AVC_TURNO(Cuba).Sup.FormaBanho = VERDADEIRO;	
			}
		}

		AVC.User1[Cuba].RrapCContValp = AVC.Ruido[Cuba].RrapCContVal * 1000000000;
		AVC.User1[Cuba].RlentCContValp = AVC.Ruido[Cuba].RlentCContVal * 1000000000;

		PosicaoGlobal=23;

		if (AVL.LinhaAtiva)
		{
			/* -- Tratamento de excessao de ponto flutuante -- */
			CubaGlobal=Cuba;	/* -- Armazema qual cuba a ser tratada em global -- */
			if (sigsetjmp(MccEnvBuf,1))
			{ /* -- Ocorreu alguma excessao -- */
				/* -- Retira cuba do controle -- */
				EST_AVC(CubaGlobal).ForaControle=VERDADEIRO;
				EmiteAlarmeFor(TODOS_DISPOSITIVOS,MsgException);
				EmiteAlarmeFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_MSG_251),
				ConvCubScoreOper(CubaGlobal));
			}

			/* Verifica se alterou numero do algoritmo da cuba on-line */
			if (AlterouNumAlgCtr(Cuba, ALG_SCORE01))
			{ /* -- selecionou ou desselecionou algoritmo do Score -- */
				/* -- Inicializa variaveis do algoritmo do Score -- */
				IniMccCtrlCuba(Cuba);
				PosicaoGlobal=24;
			}
			if ((AlgControle(Cuba,ALG_SCORE01) eq VERDADEIRO) and
				(EST_AVC(Cuba).ForaLeitura eq FALSO) and
				(EST_AVC(Cuba).ForaControle eq FALSO) and
				(AVL.LinhaHabilitada eq VERDADEIRO))
			{
				if ((EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL) or
					(EST_AVC(Cuba).EstadoCuba eq CUBA_PARTIDA))
				{

					PosicaoGlobal=25;

					VerificaQuebrada(Cuba);

					DEPURA(printf(" Cuba=%d",Cuba);)

					CalcTempoEfeitos(Cuba); /* -- Calcula tempo de efeitos de corrida, quebrada etc -- */

					if (EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL)
					{
						PosicaoGlobal=26;
						
						DEPURA(printf("-CI");)
						CalculaIncrementos(Cuba); /* -- Calcula incrementos de tensao -- */
						PosicaoGlobal=27;

						DEPURA(printf("-CA");)
						CalculaRAlvo(Cuba); /* -- Calcula RAlvo apartir dos incrementos -- */
						PosicaoGlobal=28;

						VerificaBSupMovel(Cuba);

						DEPURA(printf("-EA");)
						if (AVC.Param[Cuba].HabPrevEa eq VERDADEIRO)
							PrevisaoEa(Cuba);	/* -- Faz a previsao de Efeito Anodico -- */
						else /* -- inicializa variaveis da previsao de EA -- */
							IniPrevisaoEa(Cuba);
						PosicaoGlobal=29;

						DEPURA(printf("-QP");)
						QuebradaPreventiva(Cuba);
						PosicaoGlobal=30;

						SmartFeed(Cuba);

						if (AVC.Param[Cuba].HabContResist eq VERDADEIRO)
						{ /* habilitado controle de resistencia do Score */
							
							DEPURA(printf("-EM");)
							TrataEquiMotor(Cuba);/* -- Algoritmo adaptativo do equivalente motor -- */
							PosicaoGlobal=31;
							DEPURA(printf("-MA");)
							TrataMovAnodo(Cuba);/* -- Verifica necessidade de movimentacao de anodo -- */
												/* -- e movimenta se preciso -- */
						}
						else
						{
							PosicaoGlobal=32;
							
							/* -- inicializa variaveis relativas aos calculos do equivalente motor -- */
							IniEquivMotor(Cuba);
							/* -- variaveis relativas a modulo de movimentacao de anodo -- */
							IniTrataMoveAnodo(Cuba);
						}

						if ( ((Comum->IdentReducao >= 1) and
							(Comum->IdentReducao <= 4)) or (Comum->IdentReducao >= 7))
						{
							PosicaoGlobal=33;
							VerificaAgarraCamisa(Cuba);
							TrataSubidaCamisa(Cuba, HoraAtualCtrl);
						}
					}
					/* -- Tratamento de tabela de partida de cuba -- */
					TrataPartida(Cuba);
					PosicaoGlobal=34;
			
				}
			}
		} /* if LinhaAtiva */
		else
		{  /* LinhaAtiva == falso, linha foi desligada ou partida ou comutacao */
			ResetRuido(Cuba);		/* reseta ultimos acumulados de ruido para nao
						acumular duplamente caso linhaativa == falso quando da hora
						de analise do perido da janela */
			PosicaoGlobal=35;
				
		}
		/* -- Libera semaforo para acesso a tabela de cubas -- */
		LiberaSemaf(SEMAF_AVC);
		PosicaoGlobal=36;
	} /* for */
}

/*
-------------------------------------------------------------------------------
                           Funcoes
-------------------------------------------------------------------------------
*/
/*
--------------------------------------------------------------------------------
| IniMccControle - Executa as acoes necessarias a inicializacao do modulo      |
|                  MccControle                                                 |
--------------------------------------------------------------------------------
*/
void IniMccControle(void)
{
	int CubaOpe, Cuba;

	/* -- Aloca semaforo para acesso a tabela de cubas -- */
	AlocaSemaf(SEMAF_AVC);

	/* -- Inicializa numero de algoritmo -- */
	IniNumAlgCtr();

	for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
	{
		Cuba=ConvCubOperScore(CubaOpe);
		if (Cuba eq -1)
			continue;
		/* -- Inicializa variaveis para cada cuba -- */
		IniMccCtrlCuba(Cuba);
	}

	/* -- Libera semaforo para acesso a tabela de cubas -- */
	LiberaSemaf(SEMAF_AVC);
}

/*
--------------------------------------------------------------------------------
| IniMccCtrlCuba - Inicializa variaveis para cada cuba                         |
--------------------------------------------------------------------------------
*/
void IniMccCtrlCuba(int Cuba)
{
	int	i;
	
	/* -- variaveis relativas a ruido -- */
	IniRuido(Cuba);

	/* -- variaveis relativas aos incrementos -- */
	IniIncrementos(Cuba);

	/* -- variaveis relativas a modulo de movimentacao de anodo -- */
	IniTrataMoveAnodo(Cuba);

	/* -- inicializa cuba no controle -- */
	EST_AVC(Cuba).ForaControle=FALSO;

	/* -- inicializa variaveis de estado indicativas de efeito presente -- */
	EST_AVC(Cuba).EfeitoMove=FALSO;
	EST_AVC(Cuba).EfeitoEa=FALSO;
	EST_AVC(Cuba).EfeitoQueb=FALSO;
	/* -- inicializa rinc e ralvo -- */
	AVC.Ccont[Cuba].Rinc=0.0;
	AVC.Ccont[Cuba].Vinc=0.0;
	AVC.User1[Cuba].SF_IncDeriv = 0.0;
	AVC.User1[Cuba].SF_IncDerivEA = 0.0;

  	AVC.User2[Cuba].NumMovCamTur = 0;

	/* Inicio Alteracao - Carlos - 23/06/99 */
	/* Tratamento de booster de corrente */
 	#ifdef	BOOSTER_CORRENTE
  		AVC.Ccont[Cuba].RAlvo=(AVC.Param[Cuba].VSetPointCnf-AVC.Param[Cuba].Bemf)/AVC.Ccont[Cuba].INominalCuba;
 	#else
  		AVC.Ccont[Cuba].RAlvo=(AVC.Param[Cuba].VSetPointCnf-AVC.Param[Cuba].Bemf)/AVL.INominal;
 	#endif
  	/* Fim Alteracao - Carlos - 23/06/99 */

	/* -- inicializa variaveis da previsao de EA -- */
	IniPrevisaoEa(Cuba);

	/* -- inicializa variaveis de quebrada preventiva -- */
	IniQuebPrev(Cuba);
  
	/* -- Inicializa tratamento de tabela de partida de cuba -- */
	IniTrataPartida(Cuba);

	/* -- inicializa sinal de previsao de EA para virada de dia/turno -- */
	EST_AVC(Cuba).EaPrevVirada=FALSO;

	/* -- inicializa variaveis relativas aos calculos do equivalente motor -- */
	IniEquivMotor(Cuba);

    /* -- inicializa variaveis relativas ao calculo de provável quebra -- */
	AvcLocal[Cuba].HoraUltProvQueb = 0L;
	AvcLocal[Cuba].ContHistDerivH = 0;
	AvcLocal[Cuba].ProvQuebCond = 4;
	for(i=0; i<30; i++)
		AvcLocal[Cuba].HistDerivH[i]=0.0;
	
}

/*
--------------------------------------------------------------------------------
| CalcTempoEfeitos - Calcula tempo de efeitos de corrida, quebrada, movimenta- |
|                    cao de anodo e apos Ea, para desligar as variaveis de es- |
|                    tado associadas a cada tempo.                             |
--------------------------------------------------------------------------------
*/
void CalcTempoEfeitos(int Cuba)
{
	float VCicCont,VInst,VAlvo;
	int bit_acao;

  if (EST_AVC(Cuba).Ea eq VERDADEIRO)
	EST_AVC(Cuba).EfeitoEa=VERDADEIRO;
  else
	if ((EST_AVC(Cuba).EfeitoEa eq VERDADEIRO) and
	   ((HoraAtualCtrl-AVC.Ea[Cuba].EaHoraFimProv) > AVC.Param[Cuba].TEfeitoEa))
	  EST_AVC(Cuba).EfeitoEa=FALSO;

  if ((EST_AVC(Cuba).EfeitoQueb eq FALSO) and
	  (EST_AVC(Cuba).Quebrada eq VERDADEIRO))
	EST_AVC(Cuba).EfeitoQueb=VERDADEIRO;

  if ((EST_AVC(Cuba).EfeitoMove eq VERDADEIRO) and
	  (((HoraAtualCtrl-AVC.Ccont[Cuba].HoraUltMove) > AVC.Param[Cuba].TEfeitoMoveCima) and
	   ((HoraAtualCtrl-AVC.Ccont[Cuba].HoraUltMove) > AVC.Param[Cuba].TEfeitoMoveBaixo)))
	EST_AVC(Cuba).EfeitoMove=FALSO;

  /* Inicio Alteracao - Carlos - 23/06/99 */
  /* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
  /* Inicio Alteracao BoosterAtivo - Carlos - 03/07/02 */
  if ((AVC.Param[Cuba].HabilitaBooster eq VERDADEIRO) and
	  (EST_AVC(Cuba).Est.BoosterAtivo eq VERDADEIRO))
	/* Fim Alteracao - Carlos - 03/07/02 */
  {
	AVC.Ccont[Cuba].INominalCuba = AVL.INominal + AVC.Param[Cuba].IBoosterNominal;
	AVC.Ccont[Cuba].IAlvoCuba = AVL.IAlvo + AVC.Param[Cuba].IBoosterNominal;
  }
  else
  {
	AVC.Ccont[Cuba].INominalCuba = AVL.INominal;
	AVC.Ccont[Cuba].IAlvoCuba = AVL.IAlvo;
  }
  VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba+AVC.Param[Cuba].Bemf;
  VAlvo=AVC.Ccont[Cuba].RAlvo * AVC.Ccont[Cuba].INominalCuba + AVC.Param[Cuba].Bemf;
#else
  VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal+AVC.Param[Cuba].Bemf;
  VAlvo=AVC.Ccont[Cuba].RAlvo * AVL.INominal + AVC.Param[Cuba].Bemf;
#endif
  /* Fim Alteracao - Carlos - 23/06/99 */

  VInst=AVC.Cleit[Cuba].Vinst;
  if ((EST_AVC(Cuba).EfeitoQueb eq VERDADEIRO) and
	  ((HoraAtualCtrl-AVC.Cleit[Cuba].HoraUltQueb) > AVC.Param[Cuba].TEfeitoQueb))
  {
	EST_AVC(Cuba).EfeitoQueb=FALSO;
	EST_AVC(Cuba).Quebrada=FALSO;
	GeraEvento(FIM_QUEBRADA,Cuba,-1,STR_TRACO,STR_TRACO,VCicCont,VInst,VAlvo);	
  }
  if ((EST_AVC(Cuba).Est.EfeitoQuebCab eq VERDADEIRO) and
	  ((HoraAtualCtrl-AVC.User2[Cuba].HoraUltQuebCab) > AVC.Param[Cuba].TEfeitoQueb))
  {
	EST_AVC(Cuba).Est.EfeitoQuebCab=FALSO;
	EST_AVC(Cuba).Est.QuebCab=FALSO;
  }

  if ((EST_AVC(Cuba).TrataCruzeiro eq VERDADEIRO) and
	   ((HoraAtualCtrl-AVC.Cleit[Cuba].HoraUltCruzeiro) > (AVC.Param[Cuba].TEfeitoCruzeiro*60)))
	  EST_AVC(Cuba).TrataCruzeiro=FALSO;

  if ((AVC.ParUser1[Cuba].HabMCruzeiro) and (AVC.Abs[Cuba].BitChaveMCruzeiro ne 255))
  {
	if (((HoraAtualCtrl-AVC.Cleit[Cuba].HoraUltCruzeiro) > (AVC.ParUser1[Cuba].TMaxPermMCruzeiro*60))
	     and (EST_AVC(Cuba).Est.LiberaMCruzeiro))
	{ /* Retira permissao de manobra caso ela exista */
	  EST_AVC(Cuba).Est.LiberaMCruzeiro=FALSO;
	  bit_acao=AVC.Abs[Cuba].BitLiberaMCruzeiro;
	  if (bit_acao ne 255)
	    ComandaSaidaRem(Cuba,DESLIGAR,bit_acao,0);
	  GeraEvento(EV_MANOBRA_CRUZEIRO, Cuba, -1, "Habilita", ScoreGetStr(SCORE_MSG_402), VCicCont,VInst,VAlvo);
	}
  }
}


/*
--------------------------------------------------------------------------------
| CalculaRAlvo - Calcula RAlvo para a cuba dada, apartir dos incrementos       |
--------------------------------------------------------------------------------
*/
void CalculaRAlvo(int Cuba)
{
  double Incr,RIncr,Rsetpoint,RincMax;

  if (EST_AVC(Cuba).TabOpeAtiva eq FALSO)
	/* -- inicializa VSetPoint atual -- */
	AVC.Ccont[Cuba].VSetPoint=AVC.Param[Cuba].VSetPointCnf;

  /* Inicio Alteracao - Carlos - 23/06/99 */
  /* Tratamento de booster de corrente */
 #ifdef	BOOSTER_CORRENTE
  /* -- calcula Rsetpoint -- */
  Rsetpoint=(AVC.Ccont[Cuba].VSetPoint-AVC.Param[Cuba].Bemf)/AVC.Ccont[Cuba].INominalCuba;
 #else
  /* -- calcula Rsetpoint -- */
  Rsetpoint=(AVC.Ccont[Cuba].VSetPoint-AVC.Param[Cuba].Bemf)/AVL.INominal;
 #endif
  /* Fim Alteracao - Carlos - 23/06/99 */

  /* -- calcula Resistencia de incremento -- */
  Incr=(AVC.Ccont[Cuba].IncCorr+AVC.Ccont[Cuba].IncQueb+
		AVC.Ccont[Cuba].IncTPinos+AVC.Ccont[Cuba].IncOper+
		AVC.Ccont[Cuba].IncUsuario+AVC.User2[Cuba].IncOscil);
  if (AVC.Param[Cuba].HabIncRRap eq VERDADEIRO)
	Incr=Incr+AVC.Ccont[Cuba].IncRrap;
  if (AVC.Param[Cuba].HabIncRLent eq VERDADEIRO)
	Incr=Incr+AVC.Ccont[Cuba].IncRlent;
  if (EST_AVC(Cuba).Est.FormaBanho eq VERDADEIRO)
	Incr=Incr+AVC.User2[Cuba].IncFormaBanho;
#ifdef INCREMENTO_RESISTENCIA
  /* -- calcula Resistencia de incremento maxima -- */
  RIncr=Incr;
  RincMax=AVC.Param[Cuba].VIncMax;
#else

  /* Inicio Alteracao - Carlos - 23/06/99 */
  /* Tratamento de booster de corrente */
 #ifdef	BOOSTER_CORRENTE
  /* -- calcula Resistencia de incremento maxima -- */
  RIncr=Incr/AVC.Ccont[Cuba].INominalCuba;
  RincMax=AVC.Param[Cuba].VIncMax/AVC.Ccont[Cuba].INominalCuba;
 #else
  /* -- calcula Resistencia de incremento maxima -- */
  RIncr=Incr/AVL.INominal;
  RincMax=AVC.Param[Cuba].VIncMax/AVL.INominal;
 #endif
  /* Fim Alteracao - Carlos - 23/06/99 */

#endif
  if ((RIncr > RincMax) and (EST_AVC(Cuba).TabOpeAtiva eq FALSO))
	RIncr=RincMax;
  AVC.Ccont[Cuba].Rinc=RIncr;


  /* Inicio Alteracao - Carlos - 23/06/99 */
  /* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
  AVC.Ccont[Cuba].Vinc=RIncr*AVC.Ccont[Cuba].INominalCuba;
#else
  AVC.Ccont[Cuba].Vinc=RIncr*AVL.INominal;
#endif
  /* Fim Alteracao - Carlos - 23/06/99 */

  /* -- calcula resistencia alvo de controle -- */
  AVC.Ccont[Cuba].RAlvo=Rsetpoint+RIncr;

  if (AVC.Cleit[Cuba].TUltEa > ((AVC.Param[Cuba].EaAtrasoMax - AVC.ParUser1[Cuba].LimSupQPrevEa) * 60))
  {
    if (AVC.Param[Cuba].HabMovIniQueb eq VERDADEIRO) 
	  AVC.Param[Cuba].HabMovIniQueb = 0;

	if (EST_AVC(Cuba).Est.EaAtrasado eq FALSO)
	  EST_AVC(Cuba).Est.EaAtrasado = VERDADEIRO;
  }
  else
  {
	if (EST_AVC(Cuba).Est.EaAtrasado eq VERDADEIRO)
 	  EST_AVC(Cuba).Est.EaAtrasado = FALSO;	
  }
}

/*
--------------------------------------------------------------------------------
| Verifica Quebrada - Realiza os calculos relativos a quebrada programada     |
--------------------------------------------------------------------------------
*/
void VerificaQuebrada(int Cuba)
{

	int BitMask;
	int nquebdia;
	int PassaQueb;
	byte	PulaQuebProg;
	int	NumQuebDia;
	int	BuffSize;
	int	i, k;
	float	x[30];
	float	sumx;
	float	sumx2;
	float	sumy;
	float	sumxy;
	float	sumy2;
	char	Par1[8]; //Variável aux. - Atraso EA [hhh:mm] %03d:%02d
	char	Par2[8]; //Horário de Provável Quebra
	//char	Par3[8]; //Status da cuba durante provável quebra
	
	BitMask = 1;
	AvcLocal[Cuba].Dia = (int)((HoraAtualCtrl - 10800) / 86400);
	NumQuebDia = 0;
	//BuffSize = sizeof(AvcLocal[Cuba].HistDerivH)/sizeof(AvcLocal[Cuba].HistDerivH[0]);
	BuffSize = (int)AVC.ParUser1[Cuba].BufferSizeRH;
	//ProvQuebCond = 4; //Condicao que a cuba se encontra durante evento ProvQueb
	
	/* -- Calcula o horario da proxima quebrada programada -- */
	if ( AVC.ParUser1[Cuba].HabCalcHoraQueb eq VERDADEIRO)
	{
		if ( AVC.User2[Cuba].HoraProxQuebReal < HoraAtualCtrl)
		{
			AVC.User2[Cuba].HoraUltQueb = AVC.User2[Cuba].HoraProxQueb;
			AVC.User2[Cuba].HoraUltQuebReal = AVC.User2[Cuba].HoraProxQuebReal;
			AVC.User2[Cuba].HoraProxQueb = AVC.ParUser1[Cuba].HoraRefQuebProg 
												+ AVL.Trab.HoraIniDia;
			strcpy(AvcLocal[Cuba].LadoUltQueb,AvcLocal[Cuba].Lado);	    
			AvcLocal[Cuba].UltNQuebDia = AvcLocal[Cuba].NQuebDia;
			AvcLocal[Cuba].UltLadoIdx = AvcLocal[Cuba].LadoIdx;
			AvcLocal[Cuba].UltDia = AvcLocal[Cuba].Dia;
			AvcLocal[Cuba].LadoQueb = ((HoraAtualCtrl - AVC.ParUser1[Cuba].HoraRefQuebProg) + (AVC.ParUser1[Cuba].IntervQuebProg / 2)) /
										AVC.ParUser1[Cuba].IntervQuebProg;
			AvcLocal[Cuba].LadoQueb = AvcLocal[Cuba].LadoQueb + (AVC.ParUser1[Cuba].LadoRefQueb - 1);
			AvcLocal[Cuba].LadoQueb = AvcLocal[Cuba].LadoQueb % 2; 

			AVC.User1[Cuba].NumQuebProg++;
			EST_AVC(Cuba).Est.PulaProxQueb = FALSO;

			AVC.User2[Cuba].HoraProxQueb = AVC.ParUser1[Cuba].HoraRefQuebProg + AVL.Trab.HoraIniDia; 

			for(;;)
			{
				if (((AVC.ParUser1[Cuba].IdxQuebMix >> NumQuebDia) andb BitMask) eq 1)
					AVC.User2[Cuba].HoraProxQueb += AVC.ParUser1[Cuba].IntervQuebMix; 		  
				else
					AVC.User2[Cuba].HoraProxQueb += AVC.ParUser1[Cuba].IntervQuebProg; 		  
				if ( AVC.User2[Cuba].HoraProxQueb > HoraAtualCtrl)
				{
					break;
				}
				NumQuebDia++;
			}
		}	

		if (AVC.ParUser1[Cuba].LadoQuebIdx eq 0)
		{
			if(AvcLocal[Cuba].LadoQueb eq 1)
			{
				AVC.User2[Cuba].HoraProxQuebReal = AVC.User2[Cuba].HoraProxQueb + 
													AVC.ParUser1[Cuba].DelayLadoQueb1;
			}
			else if(AvcLocal[Cuba].LadoQueb eq 0)
			{
				AVC.User2[Cuba].HoraProxQuebReal = AVC.User2[Cuba].HoraProxQueb + 
													AVC.ParUser1[Cuba].DelayLadoQueb2;
			}
		}
		else
		{
			if (AVC.User2[Cuba].HoraProxQueb < AVL.Trab.HoraIniDia)
			{
				AvcLocal[Cuba].Dia--;	
			}

			if(AVC.ParUser1[Cuba].InverteIdx eq 1)
			{
				if((AvcLocal[Cuba].Dia % 2) eq 1) 
				{
					nquebdia = 86400 / AVC.ParUser1[Cuba].IntervQuebProg;
					nquebdia = (pow(2,nquebdia) - 1);
					AvcLocal[Cuba].LadoIdx = AVC.ParUser1[Cuba].LadoQuebIdx ^ nquebdia;
				}
				else
				{	
					AvcLocal[Cuba].LadoIdx = AVC.ParUser1[Cuba].LadoQuebIdx;
				}
			}
			else
			{	
				AvcLocal[Cuba].LadoIdx = AVC.ParUser1[Cuba].LadoQuebIdx;
			}

			if (AVC.User2[Cuba].HoraProxQueb >= (AVC.ParUser1[Cuba].HoraRefQuebProg + AVL.Trab.HoraIniDia))
			{
				AvcLocal[Cuba].NQuebDia = (((AVC.User2[Cuba].HoraProxQueb - AVL.Trab.HoraIniDia) - AVC.ParUser1[Cuba].HoraRefQuebProg)) /
										AVC.ParUser1[Cuba].IntervQuebProg;
			}
			else
			{
				AvcLocal[Cuba].NQuebDia = abs((((AVC.User2[Cuba].HoraProxQueb - (AVL.Trab.HoraIniDia-86400)) - AVC.ParUser1[Cuba].HoraRefQuebProg)) /
										AVC.ParUser1[Cuba].IntervQuebProg);
			}

			if( ((AvcLocal[Cuba].LadoIdx >> (AvcLocal[Cuba].NQuebDia)) andb BitMask) eq 0)
			{
				AVC.User2[Cuba].HoraProxQuebReal = AVC.User2[Cuba].HoraProxQueb + 
													AVC.ParUser1[Cuba].DelayLadoQueb1;
				strcpy(AvcLocal[Cuba].Lado,"INTERNO");
			}
			else if(((AvcLocal[Cuba].LadoIdx >> (AvcLocal[Cuba].NQuebDia)) andb BitMask) eq 1)
			{
				AVC.User2[Cuba].HoraProxQuebReal = AVC.User2[Cuba].HoraProxQueb + 
													AVC.ParUser1[Cuba].DelayLadoQueb2;
				strcpy(AvcLocal[Cuba].Lado,"EXTERNO");
			} 	
		}
  	}
 
	/* -- Calcula a derivada negativa -- */
	if ( AVC.ParUser1[Cuba].HabCalcDN eq VERDADEIRO and 
			AVC.ParUser1[Cuba].HabCalcHoraQueb eq VERDADEIRO)
	{
		if ( HoraAtualCtrl > (AVC.User2[Cuba].HoraProxQuebReal - AVC.ParUser1[Cuba].CalcDNQueb))
		{
			AVC.User2[Cuba].NumCiclosDN++;
			AVC.User2[Cuba].MediaDN = ((AVC.User2[Cuba].MediaDN * (AVC.User2[Cuba].NumCiclosDN - 1)) + 
										AVC.Ea[Cuba].RSuaveDerivH) / AVC.User2[Cuba].NumCiclosDN;
			if(AVC.User2[Cuba].MediaDN < AVC.ParUser1[Cuba].NivelDN)
			{
				if ( HoraAtualCtrl > (AVC.User2[Cuba].HoraProxQuebReal - AVC.ParUser1[Cuba].AlarmeDNQueb))	
				{
					EST_AVC(Cuba).Est.DerNegativa = VERDADEIRO;
				}
			}
			else
			{
				EST_AVC(Cuba).Est.DerNegativa = FALSO;	
			}
		}
		else
		{
			AVC.User2[Cuba].NumCiclosDN = 0;
			AVC.User2[Cuba].MediaDN = 0;
			if( HoraAtualCtrl > (AVC.User2[Cuba].HoraUltQuebReal + AVC.ParUser1[Cuba].TEfeitoDN))
			{
				EST_AVC(Cuba).Est.DerNegativa = FALSO;
			}
		}
	}
	else
	{
		EST_AVC(Cuba).Est.DerNegativa = FALSO;	
	}

	/* -- Calcula Derivada Baixa -- */
	if(AVC.ParUser1[Cuba].HabCalcDB eq VERDADEIRO and
		AVC.ParUser1[Cuba].HabCalcHoraQueb eq VERDADEIRO)
	{
		if (AVC.ParUser1[Cuba].HabSmartFeed eq FALSO)
		{
			if ( HoraAtualCtrl >= (AVC.User2[Cuba].HoraProxQuebReal - AVC.ParUser1[Cuba].CalcDBQueb))
			{
				if(AVC.Ea[Cuba].RSuaveDerivH > AVC.ParUser1[Cuba].NivelDB)
				{
					AvcLocal[Cuba].NumCiclosForaDB++;
					if(AvcLocal[Cuba].NumCiclosForaDB >= AVC.ParUser1[Cuba].NumCiclosForaDB) 
						AVC.User2[Cuba].HoraForaDB = HoraAtualCtrl;
				}
				else
				{
					AvcLocal[Cuba].NumCiclosForaDB = 0;
				}
	
				if ( HoraAtualCtrl >= (AVC.User2[Cuba].HoraProxQuebReal - AVC.ParUser1[Cuba].AlarmeDBQueb))	
				{
					if((AVC.User2[Cuba].HoraForaDB + AVC.ParUser1[Cuba].CalcDBQueb) < AVC.User2[Cuba].HoraProxQuebReal and
							AVC.User1[Cuba].ContPassaQueb < AVC.ParUser1[Cuba].MaxPassaQueb)
					{
						EST_AVC(Cuba).Est.DerBaixa = VERDADEIRO;
					}
					else
					{
						EST_AVC(Cuba).Est.DerBaixa = FALSO;	
					}
				}
				else if( HoraAtualCtrl > (AVC.User2[Cuba].HoraUltQuebReal + AVC.ParUser1[Cuba].TEfeitoDB))
				{
					EST_AVC(Cuba).Est.DerBaixa = FALSO;
				}
			}

			if(AVC.ParUser1[Cuba].HabPulaQuebProg eq VERDADEIRO)
			{
				if(AVC.User1[Cuba].NumQuebProg +1 > AVC.ParUser1[Cuba].NQuebLogica)
				{
					PassaQueb = (AVC.User1[Cuba].NumQuebProg +1 - AVC.ParUser1[Cuba].NQuebLogica) % (AVC.ParUser1[Cuba].NQuebPassadas + AVC.ParUser1[Cuba].NQuebAtraso);

					if(PassaQueb <= AVC.ParUser1[Cuba].NQuebPassadas and PassaQueb ne 0)
					{
					//Pula
						PulaQuebProg = VERDADEIRO;	
					}
					else
					{
					//Quebra
						PulaQuebProg = FALSO;	
					}

					if ( HoraAtualCtrl >= (AVC.User2[Cuba].HoraProxQuebReal - AVC.ParUser1[Cuba].AlarmeDBQueb))	
					{
						if(PulaQuebProg eq VERDADEIRO)
						{
							EST_AVC(Cuba).Est.QuebInibida = VERDADEIRO;
						}
						else
						{
							EST_AVC(Cuba).Est.QuebInibida = FALSO;
						}
					}
					else if( HoraAtualCtrl > (AVC.User2[Cuba].HoraUltQuebReal + AVC.ParUser1[Cuba].TEfeitoDB))
					{
						EST_AVC(Cuba).Est.QuebInibida = FALSO;
					}
				}
			}

			if(AVC.ParUser1[Cuba].HabEsperaQP eq VERDADEIRO)
			{
				if(AVC.User1[Cuba].NumQuebProg +1 >= AVC.ParUser1[Cuba].NQuebInibida and
					AVC.User1[Cuba].HoraEsperaQP < AVC.Ea[Cuba].EaHoraInicio)
				{
					AVC.User1[Cuba].HoraEsperaQP = HoraAtualCtrl;
				}

				if(AVC.User1[Cuba].NumQuebProg +1 <= AVC.ParUser1[Cuba].NQuebInibida)
				{
					EST_AVC(Cuba).Est.ForcaEA = FALSO;
					EST_AVC(Cuba).Est.EsperaQP = FALSO;
				}		

				if(AVC.User1[Cuba].HoraEsperaQP > AVC.Ea[Cuba].EaHoraInicio)
				{
					if ( HoraAtualCtrl >= (AVC.User2[Cuba].HoraProxQuebReal - AVC.ParUser1[Cuba].AlarmeDBQueb))	
					{
						if(AVC.User1[Cuba].HoraUltQPrev <= AVC.User1[Cuba].HoraEsperaQP)
						{
							EST_AVC(Cuba).Est.EsperaQP = VERDADEIRO;
						}
						else
						{
							EST_AVC(Cuba).Est.EsperaQP = FALSO;
						}	
					}
					else if( HoraAtualCtrl > (AVC.User2[Cuba].HoraUltQuebReal + AVC.ParUser1[Cuba].TEfeitoDB))
					{
						EST_AVC(Cuba).Est.EsperaQP = FALSO;
					}

					if(AVC.User1[Cuba].NumQuebProg >= (AVC.ParUser1[Cuba].NQuebInibida + AVC.ParUser1[Cuba].NQuebForcaEA) and
							AVC.User1[Cuba].HoraUltQPrev <= AVC.User1[Cuba].HoraEsperaQP)
					{
						EST_AVC(Cuba).Est.ForcaEA = VERDADEIRO;
					}
					else
						EST_AVC(Cuba).Est.ForcaEA = FALSO;
				}
				else
				{
					EST_AVC(Cuba).Est.ForcaEA = FALSO;
					EST_AVC(Cuba).Est.EsperaQP = FALSO;
				}
			}

			if( HoraAtualCtrl >= AVC.User2[Cuba].HoraUltQuebReal and 
				HoraAtualCtrl < (AVC.User2[Cuba].HoraUltQuebReal + 120) and
				EST_AVC(Cuba).Est.DerBaixa eq FALSO)
			{
				EST_AVC(Cuba).Est.DBUltQueb = FALSO;
				AVC.User1[Cuba].ContPassaQueb = 0;
			} 	

			if( HoraAtualCtrl >= AVC.User2[Cuba].HoraUltQuebReal and 
				HoraAtualCtrl < (AVC.User2[Cuba].HoraUltQuebReal + 120) and
				EST_AVC(Cuba).Est.DerBaixa eq VERDADEIRO)
			{
				AVC.User1[Cuba].ContPassaQueb++;
			} 	

			if( HoraAtualCtrl >= AVC.User2[Cuba].HoraUltQuebReal and 
				HoraAtualCtrl < (AVC.User2[Cuba].HoraUltQuebReal + 120) and
				EST_AVC(Cuba).Est.DerBaixa eq VERDADEIRO)
			{
				SUPERV_AVC(Cuba).Sup.NumDBDia++;
				AVC.User1[Cuba].NumDB++;

				GeraEvento(EV_DB,Cuba,-1,SUPERV_AVC(Cuba).Sup.NumDBDia,
				AvcLocal[Cuba].UltNQuebDia + 1, AVC.User1[Cuba].NumDB, 
					AVC.User1[Cuba].NumQuebProg, AvcLocal[Cuba].LadoUltQueb);

				if (EST_AVC(Cuba).Est.DBUltQueb eq VERDADEIRO) 
				{
					SUPERV_AVC(Cuba).Sup.NumDBConsec++;
				}
				EST_AVC(Cuba).Est.DBUltQueb = VERDADEIRO;
			}
		}
		else
		{
			if ( HoraAtualCtrl >= (AVC.User2[Cuba].HoraProxQuebReal - AVC.ParUser1[Cuba].AlarmeDBQueb))	
			{
				if ((AVC.User1[Cuba].SF_Posicao eq 5) and 
					(AVC.User1[Cuba].SF_IncDeriv < AVC.ParUser1[Cuba].SF_OverFeed))
				{		
					if ((SUPERV_AVC(Cuba).Sup.NumDBDia % 2) eq 1 and 
							AVC.User1[Cuba].QuebrouDB eq FALSO)
					{
						AvcLocal[Cuba].PulaDB = VERDADEIRO;	  
						EST_AVC(Cuba).Est.DerBaixa = FALSO;
					}
					else
					{
						AvcLocal[Cuba].PulaDB = FALSO;	  
						EST_AVC(Cuba).Est.DerBaixa = VERDADEIRO;
					}
				}
				else
				{
					EST_AVC(Cuba).Est.DerBaixa = FALSO;		  
					AvcLocal[Cuba].PulaDB = FALSO;	  
				}

				if( HoraAtualCtrl >= AVC.User2[Cuba].HoraUltQuebReal and 
				HoraAtualCtrl < (AVC.User2[Cuba].HoraUltQuebReal + 120) and
					EST_AVC(Cuba).Est.DerBaixa eq FALSO)
				{
					EST_AVC(Cuba).Est.DBUltQueb = FALSO;
					AVC.User1[Cuba].QuebrouDB = FALSO;
				}  	

				if( HoraAtualCtrl >= AVC.User2[Cuba].HoraUltQuebReal and 
				HoraAtualCtrl < (AVC.User2[Cuba].HoraUltQuebReal + 120) and
					(EST_AVC(Cuba).Est.DerBaixa eq VERDADEIRO or
					AvcLocal[Cuba].PulaDB eq VERDADEIRO))
				{
					SUPERV_AVC(Cuba).Sup.NumDBDia++;
					AVC.User1[Cuba].NumDB++;

					GeraEvento(EV_DB,Cuba,-1,SUPERV_AVC(Cuba).Sup.NumDBDia,
						AvcLocal[Cuba].UltNQuebDia + 1, AVC.User1[Cuba].NumDB, 
						AVC.User1[Cuba].NumQuebProg, AvcLocal[Cuba].LadoUltQueb);

					if (EST_AVC(Cuba).Est.DBUltQueb eq VERDADEIRO) 
					{
						SUPERV_AVC(Cuba).Sup.NumDBConsec++;
					}
					EST_AVC(Cuba).Est.DBUltQueb = VERDADEIRO;
				}
			}
		}
	}
	else
	{
		EST_AVC(Cuba).Est.DerBaixa = FALSO;	
		AvcLocal[Cuba].NumCiclosForaDB = 0;
		EST_AVC(Cuba).Est.DBUltQueb = FALSO;
	}

	/* -- Calcula Provável Quebra sem Sinalização -- */
	if ( EST_AVC(Cuba).EfeitoQueb eq FALSO and
		 ((HoraAtualCtrl-AVC.Cleit[Cuba].HoraUltQueb) > 2700L) and //45 minutos apos ultima quebrada
		 EST_AVC(Cuba).EfeitoCorr eq FALSO and
		 (HoraAtualCtrl-AvcLocal[Cuba].HoraUltProvQueb) > 3600L and //60 minutos apos ultima provavel quebrada
		 ((BuffSize>=5) and (BuffSize<=30)))
		 //and ((HoraAtualCtrl-AVC.Cleit[Cuba].HoraInicDesLeit) > (60*60L))) //60 minutos apos desligamento
	{		
		//HistDerivH array circular shifting: HistDerivH[Last] to HistDerivH[Last-1]
		memmove(&AvcLocal[Cuba].HistDerivH[0],&AvcLocal[Cuba].HistDerivH[1],
			(sizeof(AvcLocal[Cuba].HistDerivH)-sizeof(AvcLocal[Cuba].HistDerivH[0])));

		//RSuaveDerivH to HistDerivH[Last]
		AvcLocal[Cuba].HistDerivH[BuffSize-1] = AVC.Ea[Cuba].RSuaveDerivH;
		
		if(AvcLocal[Cuba].ContHistDerivH < BuffSize)
			AvcLocal[Cuba].ContHistDerivH++;
		
		if (EST_AVC(Cuba).Est.QuebPrev eq VERDADEIRO)
			AvcLocal[Cuba].ProvQuebCond = 1;
		else if (EST_AVC(Cuba).EaPrev eq VERDADEIRO)
			AvcLocal[Cuba].ProvQuebCond = 2;
		else if (EST_AVC(Cuba).Est.DerBaixa eq VERDADEIRO)
			AvcLocal[Cuba].ProvQuebCond = 3;

		/* Calcula coeficiente angular de RSuaveDerivH */
		if( AvcLocal[Cuba].ContHistDerivH >= BuffSize)
		{
			i = 0;
			sumx = 0;
			sumx2 = 0;
			sumy = 0;
			sumy2 = 0;
			sumxy = 0;
			AVC.ParUser1[Cuba].Livre1 = 0;

			for (i=0;(i+(BuffSize-AvcLocal[Cuba].ContHistDerivH))<BuffSize;++i)
			{
				k = i+(BuffSize-AvcLocal[Cuba].ContHistDerivH); 
				x[i]= i*1;
				sumx += x[i];  
				sumx2 += x[i]*x[i]; 
				sumy += AvcLocal[Cuba].HistDerivH[k];
				sumy2 += AvcLocal[Cuba].HistDerivH[k]*AvcLocal[Cuba].HistDerivH[k]; 
				sumxy += x[i]*AvcLocal[Cuba].HistDerivH[k];
			}
					
			AVC.User1[Cuba].CoefAngDeriv = ((AvcLocal[Cuba].ContHistDerivH*sumxy) - (sumx*sumy))/
				((AvcLocal[Cuba].ContHistDerivH*sumx2) - (sumx*sumx));

			if (AVC.User1[Cuba].CoefAngDeriv < AVC.ParUser1[Cuba].NivelProvQueb)
			{
				AvcLocal[Cuba].HoraUltProvQueb = HoraAtualCtrl;
				//AvcLocal[Cuba].IntervQueb = (long)((HoraAtualCtrl - AVC.User2[Cuba].HoraEvQuebrada)/60L);
				AvcLocal[Cuba].IntervQueb = (long)((HoraAtualCtrl - AVC.Cleit[Cuba].HoraUltQueb)/60L);
				MontaHoraMin((long)AVC.Cleit[Cuba].TUltEa/60L, Par1, "%03d:%02d"); //Tempo em min desde Ult. EA
				
				//Hora da Prov Queb
				SecProvQueb = (long)(HoraAtualCtrl-(BuffSize*2*60));
				HoraProvQueb = SecProvQueb / 3600;
				MinProvQueb = (SecProvQueb - (HoraProvQueb * 3600)) / 60;
				sprintf(Par2, "%03d:%02d", HoraProvQueb, MinProvQueb);

				if(AvcLocal[Cuba].ProvQuebCond==1)
					GeraEvento(EV_PROVQUEB,Cuba,-1,	AvcLocal[Cuba].IntervQueb,"QuebPrev",Par1,Par2);
				else if(AvcLocal[Cuba].ProvQuebCond==2)
					GeraEvento(EV_PROVQUEB,Cuba,-1,	AvcLocal[Cuba].IntervQueb,"EaPrev  ",Par1,Par2);
				else if(AvcLocal[Cuba].ProvQuebCond==3)
					GeraEvento(EV_PROVQUEB,Cuba,-1,	AvcLocal[Cuba].IntervQueb,"DerBaixa",Par1,Par2);
				else
					GeraEvento(EV_PROVQUEB,Cuba,-1,	AvcLocal[Cuba].IntervQueb,STR_TRACO,Par1,Par2);				
			}
		}		
	}	
	else
	{ //Zerar buffer da derivada histórica quando em quebrada e corrida
		
		memset(Par1,0,strlen(Par1));
		memset(Par2,0,strlen(Par2));
		//memset(Par3,0,strlen(Par3));
		//strcpy(Par3,STR_TRACO);
		AvcLocal[Cuba].ProvQuebCond = 4;

		AvcLocal[Cuba].ContHistDerivH = 0;
		for(i=0;i<30;i++)
			AvcLocal[Cuba].HistDerivH[i]=0.0;
		
	}
}

/*
--------------------------------------------------------------------------------
| VerificaBSupMovel - Calcula as bandas de controle superior moveis            |
--------------------------------------------------------------------------------
*/
void VerificaBSupMovel(int Cuba)
{
  if (EST_AVC(Cuba).Quebrada eq VERDADEIRO)
  {
	EST_AVC(Cuba).Est.BSupMovel = FALSO; 
	AVC.User1[Cuba].PulouQuebProg = FALSO;
  }

  if (AVC.ParUser1[Cuba].TAcresBSupMovel > 0 and
		SUPERV_AVC(Cuba).AtrasoEa eq FALSO)
  {
	if ( ((AVC.User2[Cuba].HoraProxQuebReal - (AVC.ParUser1[Cuba].TAcresBSupMovel * 60)) <=
			 HoraAtualCtrl) and	(AVC.User1[Cuba].PulouQuebProg eq FALSO))
	{
	  AVC.User1[Cuba].BandaSupMovel = (AVC.ParUser1[Cuba].AcresBSupMovel / 
					(AVC.ParUser1[Cuba].TAcresBSupMovel / 2)) *
					((AVC.ParUser1[Cuba].TAcresBSupMovel - 
					((AVC.User2[Cuba].HoraProxQuebReal - HoraAtualCtrl) / 60)) / 2);	
	  if ( AVC.User1[Cuba].BandaSupMovel > AVC.ParUser1[Cuba].AcresBSupMovel)
	  {
		AVC.User1[Cuba].BandaSupMovel = AVC.ParUser1[Cuba].AcresBSupMovel;	
	  } 
	  EST_AVC(Cuba).Est.BSupMovel = VERDADEIRO; 
	}
	else 
	{
	  if (EST_AVC(Cuba).Est.BSupMovel eq VERDADEIRO)
	  {
 	    AVC.User1[Cuba].BandaSupMovel = AVC.ParUser1[Cuba].AcresBSupMovel;
	    AVC.User1[Cuba].PulouQuebProg = VERDADEIRO;
	  }
	  else
	  {
	    AVC.User1[Cuba].BandaSupMovel = 0.0;
	  }
	}		
  }
  else
  {
	AVC.User1[Cuba].BandaSupMovel = 0.0;
	EST_AVC(Cuba).Est.BSupMovel = FALSO; 
	AVC.User1[Cuba].PulouQuebProg = FALSO;
  }
}


/*
--------------------------------------------------------------------------------
| SmartFeed - Logica de calculo de subida de anodo na quebra programada            |
--------------------------------------------------------------------------------
*/
void SmartFeed(int Cuba)
{

	if (AVC.ParUser1[Cuba].HabSmartFeed eq VERDADEIRO)
	{
		if (EST_AVC(Cuba).EfeitoQueb eq FALSO)
		{
			AvcLocal[Cuba].SF_NumDeriv++;
			AvcLocal[Cuba].SF_Coef_A += AvcLocal[Cuba].SF_NumDeriv * AVC.Ea[Cuba].RSuaveDerivH; 
			AvcLocal[Cuba].SF_Coef_B += AVC.Ea[Cuba].RSuaveDerivH; 
			AvcLocal[Cuba].SF_Coef_C += pow(AvcLocal[Cuba].SF_NumDeriv, 2); 
			AvcLocal[Cuba].SF_Coef_D += AvcLocal[Cuba].SF_NumDeriv;

			if((AvcLocal[Cuba].SF_NumDeriv * AvcLocal[Cuba].SF_Coef_C) - (pow(AvcLocal[Cuba].SF_NumDeriv, 2)) ne 0)
			{ 
				AVC.User1[Cuba].SF_IncDeriv = (((AvcLocal[Cuba].SF_NumDeriv * AvcLocal[Cuba].SF_Coef_A) -
												(AvcLocal[Cuba].SF_Coef_D * AvcLocal[Cuba].SF_Coef_B)) /
												((AvcLocal[Cuba].SF_NumDeriv * AvcLocal[Cuba].SF_Coef_C) -
												(pow(AvcLocal[Cuba].SF_NumDeriv, 2)))) * pow(10,9); 

				AVC.User1[Cuba].SF_IncDeriv = ((1 - AVC.ParUser1[Cuba].SF_KSIncDeriv) * AVC.User1[Cuba].SF_IncDeriv) +
												(AVC.ParUser1[Cuba].SF_KSIncDeriv * AVC.User1[Cuba].SF_IncDerivAnt);
			}
		}
		else
		{
			AVC.User1[Cuba].SF_IncDerivAnt = AVC.User1[Cuba].SF_IncDeriv;	  
			AvcLocal[Cuba].SF_Coef_A = 0.0;
			AvcLocal[Cuba].SF_Coef_B = 0.0;
			AvcLocal[Cuba].SF_Coef_C = 0.0;
			AvcLocal[Cuba].SF_Coef_D = 0.0;
			AvcLocal[Cuba].SF_NumDeriv = 0;
		}
	}
	else
	{
		AVC.User1[Cuba].SF_TempoSobe = 0.0;
		AVC.User1[Cuba].SF_IncDerivAnt = 0.0;
		AVC.User1[Cuba].SF_IncDeriv = 0.0;	  
		AvcLocal[Cuba].SF_Coef_A = 0.0;
		AvcLocal[Cuba].SF_Coef_B = 0.0;
		AvcLocal[Cuba].SF_Coef_C = 0.0;
		AvcLocal[Cuba].SF_Coef_D = 0.0;
		AvcLocal[Cuba].SF_NumDeriv = 0;
  	}
}

/*
--------------------------------------------------------------------------------
| VerificaAgarraCamisa - Verifica se camisa agarrou no ultimo ciclo de controle            |
--------------------------------------------------------------------------------
*/
void VerificaAgarraCamisa(int Cuba)
{

  float VDif;

  if(AVC.User2[Cuba].SubiuCamisa eq VERDADEIRO)
  {
	if ((EST_AVC(Cuba).ChaveAutMan eq AUTOMATICO) and
		(EST_AVC(Cuba).ChaveLocRem eq REMOTO) and
		((AVC.CcontMcp[Cuba].RCicContlBruta - AVC.User2[Cuba].UltRCicCont) >= AVC.ParUser1[Cuba].DifResAgarraCamisa)  and
		((HoraAtualCtrl-AVC.User1[Cuba].HoraUltMovCam) <= (1.2*IntervCicCont*60)))
	{
	  VDif = (AVC.CcontMcp[Cuba].RCicContlBruta - AVC.User2[Cuba].UltRCicCont) * AVL.INominal;		

	  SUPERV_AVC(Cuba).Sup.AgarraCam++;

	  GeraEvento(EV_AGARRACAM,Cuba,-1, SUPERV_AVC(Cuba).Sup.AgarraCam, VDif);
		
	  AVC.User2[Cuba].SubiuCamisa = FALSO;
	} 
  }
}
/* -- Fim do arquivo MccControle.c -- */
