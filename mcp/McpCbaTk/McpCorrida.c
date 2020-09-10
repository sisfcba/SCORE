/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: McpCorrida.c

	CONTEUDO	: Modulo para tratamento de corrida ativado pelo Modulo de
				  Calculos Primarios - MCP.
                  E'  ativado  pelo modulo de calculos primarios (MCP) a cada
                  ciclo de leitura, na desativacao de linha e na  partida  do
				  sistema.
				  Faz o ajuste de resistencia durante corrida. O intervalo de
				  atuacao esta' definido em base de dados.
				  OBS.: Para ser ativado pelo Mcp deve estar inicializada a ta-
						bela de programas na base de dados (campo=336 da tabela
						utilizando o programa BdScore).

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	23/02/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
21/12/94 | Edicao inicial de migracao para o QNX 4.2			| Leonel
-------------------------------------------------------------------------------
04/02/95 | Adaptacao para versao em ingles               		| Carlos
-------------------------------------------------------------------------------
22/11/96 | Incluida ativacao do ajuste de camisa         		| Carlos
-------------------------------------------------------------------------------
27/01/97 | Incluido tratamento da variavel RCicCorr para geracao| Carlos
         | do evento FimCorrida sem VCicContl = Bemf            |
-------------------------------------------------------------------------------
20/03/97 | Incluido tratamento de algoritmo              		| Leonel
-------------------------------------------------------------------------------
17/07/98 | Inclusao da nova logica de ajuste de camisa   		| Carlos
-------------------------------------------------------------------------------
07/09/98 | Cba-Inclusao de logica de agarramento de anodo 		| Leonel
-------------------------------------------------------------------------------
07/09/98 | Inclusao do alarme de camisa nao ajustada      		| Carlos
-------------------------------------------------------------------------------
11/12/98 | Alarme CamNAjust desat. so em mov. manual de camisa	| Carlos
-------------------------------------------------------------------------------
28/06/99 | Incluido tratamento de booster de corrente			| Carlos
-------------------------------------------------------------------------------
29/11/02 | Inclusao ajuste camisa para sala 125ka.              | Leonel
-------------------------------------------------------------------------------
$Id: McpCorrida.c,v 1.1.2.1 2012/09/28 17:09:37 leo Exp $

$Log: McpCorrida.c,v $
Revision 1.1.2.1  2012/09/28 17:09:37  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

Revision 1.3  2007/09/28 14:46:30  rogerio
Alteracao para incluir sala I com atn8

Revision 1.2  2004/04/08 19:21:18  leo
Inclusao da sala 125 kA VI.

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
#include	<McpCorrida.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<AjusteCamisa.h>
#include	<math.h>

/*
-------------------------------------------------------------------------------
                           Variaveis Globais
-------------------------------------------------------------------------------
*/
/* -- Apontadores para as tabelas comuns -- */
#include	<VarsComum.h>

/*
-------------------------------------------------------------------------------
                           Prototipo do main
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[]);

/*
-------------------------------------------------------------------------------
	Main - McpCorrida - Modulo de ajuste de resistencia durante corrida
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[])
{
	int 			TidMcp;
	t_mens_padrao	Mens;
	int			Responde, Partida;
	t_boolean		PartidaQuente;

	/* -- Recebe endereco da area de dados comum ao processo -- */
	Reply(Receive(0, &Comum, sizeof(Comum)), 0, 0);
      
	/* -- Inicializa apontadores para tabelas globais -- */
	InitVarsComum();

	/* -- Copia NumCubas da base de dados para local -- */
	NumCubas=AVL.NumCubas;

	/* -- Guarda hora atual em secundos -- */
	HoraAtualSec=time(NULL)/TIMES_PER_SEC; /* -- segs. apartir 1/1/1980 -- */

	/* -- Consiste Cuba inicial e cuba final a tratar -- */
	PartidaQuente=ConsisteArgs(argc,argv);

	if (PartidaQuente eq VAL_VERDADEIRO)
	{ /* Modulo ativado com o sistema ja' rodando, nao sera' enviada mensagem
		de inicializacao pelo Mcp. Logo inicializa oque for necessario */
		/* -- Inicializa todas as variaveis de trabalho e executa os procedimentos 
			necessarios a inicializacao do calculos. -- */
		IniMcpCorrida();
		/* -- Marca que a proxima ativacao de inicializacao nao sera' a primeira -- */
		Partida=FALSO;
	}
	else
		/* -- Marca que a proxima ativacao de inicializacao sera' a primeira -- */
		Partida=VERDADEIRO;

  	loop			/*  Loop eterno */
  	{
		Responde=VERDADEIRO;
		/* -- Recebe ativacao do MCP -- */
		if((TidMcp = Receive(0, &Mens, sizeof(Mens))) eq -1)
			EmiteErroFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_ERR_8),COD_ERRO_18,errno);
			//EmiteErroFor(TODOS_DISPOSITIVOS,"Erro receive [%s]",strerror(errno));

		/* -- Guarda hora atual em secundos -- */
		HoraAtualSec=time(NULL)/TIMES_PER_SEC; /* -- segs. apartir 1/1/1980 -- */

		switch(Mens.Acao)
		{
			case INICIALIZACAO:
				DEPURA(printf("McpCorrida->Inicializacao\n");)
				/* -- Inicializa todas as variaveis de trabalho e executa os procedimentos 
							necessarios a inicializacao dos calculos. -- */
				IniMcpCorrida();
				if (Partida)
				{
					Partida=FALSO;
					Reply(TidMcp,&Mens,sizeof(Mens));
					Responde=FALSO;
					/* -- Aguarda sinalizacao de partida do sistema -- */
					/* -- O micro que estiver em hot standby ficara' bloqueado aqui ate'
							assumir o controle. -- */
					AguardaPartida();
					/* -- Pega Hora atual -- */
					HoraAtualSec=time(NULL)/TIMES_PER_SEC; /* -- segs. apartir 1/1/1980 -- */
				}
				break;
		
			case CICLO_LEITURA:	
				ProcessaCubas();
				break;

			case DESABILITOU_LINHA:
				/* -- Caso necessario, executa procedimentos para linha desabilitada -- */
				break;
		
			default:
				EmiteErroFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_ERR_8),COD_ERRO_58,
						Mens.Acao);
				//		EmiteErroFor(TODOS_DISPOSITIVOS,"Erro Fatal - Acao nao tratada %d",
				//				     Mens.Acao);
				break;
		}

		if (Responde)
			Reply(TidMcp,&Mens,sizeof(Mens));

  	}
}

/*
--------------------------------------------------------------------------------
| ConsisteArgs - Consiste cuba inicial e final. Retorna verdadeiro se partida  |
|                a quente (switch -quente). Nao retorna se erro.               |
--------------------------------------------------------------------------------
*/
t_boolean ConsisteArgs(int Argc,char *Argv[])
{
	t_boolean partida_quente;

	if ((Argc ne 3) and (Argc ne 4))
	{
		printf("Numero de argumentos invalido! Use: %s cuba_ini cuba_fim [-quente]\n",Argv[0]);
		exit(EXIT_FAILURE);
	}
	CubaIni=atoi(Argv[1]);
	CubaFim=atoi(Argv[2]);
	if (ConsCubasOpe(CubaIni,CubaFim) ne ERRO_OK)
	{
		printf("Argumentos invalidos! Use: %s cuba_ini cuba_fim\n",Argv[0]);
		exit(EXIT_FAILURE);
	}
	if (Argc eq 4)
	{ /* -- O ultimo argumento e' o switch -q (quente) ? -- */
		if ( (*(Argv[3]+1) eq 'q') or (*(Argv[3]+1) eq 'Q'))
		partida_quente=VAL_VERDADEIRO;
		else
		partida_quente=VAL_FALSO;
	}
	return(partida_quente);
}

/*
--------------------------------------------------------------------------------
	IniMcpCorrida - Inicializacao de todas as variaveis relacionadas a este modulo
--------------------------------------------------------------------------------
*/
void IniMcpCorrida(void)

{
	int Cuba,CubaOpe;

	/* -- Inicializar as variaveis globais de trabalho do modulo -- */
	/* -- Inicializa tempo de ciclo de corrida -- */
	NumCicCorr = AVL.CicloAjCorrida;

	/* -- Inicializa numero de algoritmo -- */
	IniNumAlgCtr();

	/* -- Inicializa variaveis para cada cuba -- */
	AlocaSemaf(SEMAF_AVC);

	for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
	{
		Cuba=ConvCubOperScore(CubaOpe);
		if (Cuba eq -1)
		continue;
		if (AlgControle(Cuba,ALG_SCORE01) eq VERDADEIRO)
		{
			IniMcpCorCuba(Cuba);

			/* -- Alteracao - inicio - 29/11/2002 - Leonel - Inclusao tratamento de camisa para sala 125ka -- */
			if ( ((Comum->IdentReducao >= 1) and
					(Comum->IdentReducao <= 4)) or (Comum->IdentReducao >= 7))
			/* -- Alteracao - fim - 29/11/2002 - Leonel - Inclusao tratamento de camisa para sala 125ka -- */
			{
				IniAjCamCuba(Cuba);

			}
		}
	}
	LiberaSemaf(SEMAF_AVC);
}

/*
--------------------------------------------------------------------------------
	IniMcpCorCuba - Inicializacao de todas as variaveis relacionadas a cuba
--------------------------------------------------------------------------------
*/
void IniMcpCorCuba(int Cuba)
{
	EST_AVC(Cuba).EfeitoCorr=FALSO;
	AVC.Cleit[Cuba].RCicCorr = 0.0;
	AVC.Cleit[Cuba].ContLCicCorr = 0;
	AVC.Ccont[Cuba].IncCorr=0;

	/* Forca incremento como sendo linear */
	AVC.Ccont[Cuba].TipoIncCorr=INCREMENTO_LINEAR;
	
	AVC.Ccont[Cuba].ContIncCorr=-1;
	AvcLoc[Cuba].Vmax=-1.0;
	AvcLoc[Cuba].RCicCorr = 0.0;
	AvcLoc[Cuba].TMaxCorr = 0.0;
	AvcLoc[Cuba].CalcEqMotorCorr = FALSO;
	AvcLoc[Cuba].DurUltMovCorr = 0.0;
	AvcLoc[Cuba].ResUltMovCorr = 0.0;

	if (Comum->IdentReducao eq 5)
		AVC.User1[Cuba].ContMovCorr = -1;
	EST_AVC(Cuba).ProvAgarraAnodo=FALSO;
	AVC.Ccont[Cuba].RErroUltMove=0.0;
	AVC.Ccont[Cuba].ContAgarraAnodo=0;	/* Contador de provavel agarramento de anodo */
	AVC.User1[Cuba].EqMotorCorrB = AVC.Param[Cuba].KbpwmTipico;

}

/*
--------------------------------------------------------------------------------
| ProcessaCubas - Processa os calculos necessarios para cada cuba.             |
--------------------------------------------------------------------------------
*/
void ProcessaCubas(void)
{
	int Cuba,CubaOpe;
	long HoraRefCorrida;
	struct tm HoraDia;

	AlocaSemaf(SEMAF_AVC);

	memcpy(&HoraDia, localtime(&HoraAtualSec), sizeof(struct tm));
		
	/*-- inicializa data auxiliar --*/ 
	HoraDia.tm_sec  = 0;
	HoraDia.tm_min  = 0;
	HoraDia.tm_hour = 0;
		
	AVL.Trab.HoraIniDia = mktime(&HoraDia); /* converte para time_t */

	memcpy(&HoraDia, localtime(&HoraAtualSec), sizeof(struct tm));
	
	/*-- inicializa data auxiliar --*/ 
	HoraDia.tm_sec  = 59;
	HoraDia.tm_min  = 59;
	HoraDia.tm_hour = 23;
		
  	AVL.Trab.HoraFimDia = mktime(&HoraDia); /* converte para time_t */

	for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
	{
		Cuba=ConvCubOperScore(CubaOpe);
		if (Cuba eq -1)
		continue;

		/* Verifica se alterou numero do algoritmo da cuba on-line */
		if (AlterouNumAlgCtr(Cuba, ALG_SCORE01))
		{ 
			/* -- selecionou ou desselecionou algoritmo do Score -- */
			/* -- Inicializa variaveis do algoritmo do Score -- */
			IniMcpCorCuba(Cuba);
			
			/* -- Alteracao - inicio - 29/11/2002 - Leonel - Inclusao tratamento de camisa para sala 125ka -- */
			if ( ((Comum->IdentReducao >= 1) and
					(Comum->IdentReducao <= 4)) or (Comum->IdentReducao >= 7))
			/* -- Alteracao - fim - 29/11/2002 - Leonel - Inclusao tratamento de camisa para sala 125ka -- */
			{
				IniAjCamCuba(Cuba);

			}
		}
		
		if ((EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL) and
			(AlgControle(Cuba,ALG_SCORE01) eq VERDADEIRO))
		{
		/* -- Verifica condicoes para tratamento da cuba -- */
			if ((EST_AVC(Cuba).ForaLeitura eq FALSO) and
				(AVL.LinhaHabilitada eq VERDADEIRO))
			{
				if (EST_AVC(Cuba).Corrida eq VERDADEIRO or EST_AVC(Cuba).Est.CorridaBanho eq VERDADEIRO)
				{
				if (EST_AVC(Cuba).EfeitoCorr eq FALSO)
				{
					/* Verificacao se corrida ocorreu dentro do programado */
					if ((AVC.User2[Cuba].HoraUltCorr < (HoraAtualSec + AVC.Param[Cuba].TEfeitoCorr)) and
						((HoraAtualSec - AVC.User2[Cuba].HoraUltCorr) > 1800) and EST_AVC(Cuba).Corrida eq VERDADEIRO )
					{
						
						SUPERV_AVC(Cuba).Sup.IntervCorrDia = HoraAtualSec - 
															AVC.User2[Cuba].HoraUltCorr;

						if(abs(HoraAtualSec - (AVL.Trab.HoraIniDia + AVC.ParUser1[Cuba].HoraRefCorr)) >
							abs(HoraAtualSec - (AVL.Trab.HoraIniDia - 86400 + AVC.ParUser1[Cuba].HoraRefCorr))	)
						{
							HoraRefCorrida = AVL.Trab.HoraIniDia - 86400 + AVC.ParUser1[Cuba].HoraRefCorr;
						}
						else 
						{
							if(abs(HoraAtualSec - (AVL.Trab.HoraIniDia + AVC.ParUser1[Cuba].HoraRefCorr)) >
							abs(HoraAtualSec - (AVL.Trab.HoraIniDia + 86400 + AVC.ParUser1[Cuba].HoraRefCorr)))
							{
								HoraRefCorrida = AVL.Trab.HoraIniDia + 86400 + AVC.ParUser1[Cuba].HoraRefCorr;
							}
							else
							{
								HoraRefCorrida = AVL.Trab.HoraIniDia + AVC.ParUser1[Cuba].HoraRefCorr;
							}
						}

						SUPERV_AVC(Cuba).Sup.IntervRefCorrDia = HoraAtualSec - HoraRefCorrida;
						SUPERV_AVC(Cuba).Sup.IntervRefCorrDia += 86400;						
						AVC.User2[Cuba].HoraUltCorr = HoraAtualSec;
					}

					IniCorrida(Cuba);
					/* -- Alteracao - inicio - 29/11/2002 - Leonel - Inclusao tratamento de camisa para sala 125ka -- */
					if ( ((Comum->IdentReducao >= 1) and
						(Comum->IdentReducao <= 4)) or (Comum->IdentReducao >= 7))
					/* -- Alteracao - fim - 29/11/2002 - Leonel - Inclusao tratamento de camisa para sala 125ka -- */
					{
						/*-- Ativa ajuste de camisa --*/
						if(EST_AVC(Cuba).Est.CorridaBanho eq FALSO)
							AtivaAjusteCamisa(Cuba, HoraAtualSec);
					}
				}
				else
					DuranteEfCorr(Cuba);


				}
				else
				{  /* -- Atualiza banda de controle superior atual com parametro -- */
					AVC.Ccont[Cuba].BandaContSupAtual=AVC.Param[Cuba].BandaContSup;
					/* -- Reseta IncCorrida apos TIncCorr -- */
					if ((HoraAtualSec-AVC.Cleit[Cuba].HoraUltCorr) > (AVC.Param[Cuba].TIncCorr*60))
					{
						AVC.Ccont[Cuba].IncCorr=0.0;
						AVC.Ccont[Cuba].ContIncCorr=-1;
					}
				}
			} /* -- if fora leitura -- */
	
			/* -- Alteracao - inicio - 29/11/2002 - Leonel - Inclusao tratamento de camisa para sala 125ka -- */
			if ( ((Comum->IdentReducao >= 1) and
					(Comum->IdentReducao <= 4)) or (Comum->IdentReducao >= 7))
			/* -- Alteracao - fim - 29/11/2002 - Leonel - Inclusao tratamento de camisa para sala 125ka -- */
			{
				/*-- Trata inibicao temporaria do ajuste --*/
				if (AVC.User1[Cuba].ContInibAjCam > 0)
				{
					AVC.User1[Cuba].ContInibAjCam -= 1;
				}
				else
				{
					if (EST_AVC(Cuba).Est.AjusteCamisa eq VERDADEIRO)
					{
						VerifCondCamisa(Cuba, HoraAtualSec);
						VerifFimCamisa(Cuba);

					}
				}
			}

		} /* -- if EstadoCuba -- */
	} /* -- for -- */
	LiberaSemaf(SEMAF_AVC);
} /* -- ProcessaCubas -- */

/*
--------------------------------------------------------------------------------
| IniCorrida - Inicio de corrida                                               |
--------------------------------------------------------------------------------
*/
void IniCorrida(int Cuba)
{
DEPURA(printf("McpCorrida->Inicio corrida cuba=%d\n",Cuba);)


  EST_AVC(Cuba).EfeitoCorr=VERDADEIRO;
  /* -- Inicializa tempo de ciclo de corrida -- */
  NumCicCorr = AVL.CicloAjCorrida;
  /* -- Inicializa Resistencia media -- */
  AVC.Cleit[Cuba].RCicCorr = 0.0;
  AvcLoc[Cuba].RCicCorr = 0.0;
  AVC.Cleit[Cuba].ContLCicCorr = 0;
  AvcLoc[Cuba].TMaxCorr = 0.0;
  EST_AVC(Cuba).Est.ZeraCA = VERDADEIRO;
  EST_AVC(Cuba).Est.ProjetaCA = VERDADEIRO;
  AVC.User2[Cuba].NumMovCamPF = 0;

  /* -- Inicializa Vmax e VAlvo -- */
  AvcLoc[Cuba].Vmax=-1.0;

  /* Inicio Alteracao - Carlos - 23/06/99 */
  /* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
  AvcLoc[Cuba].VAlvo=(AVC.Ccont[Cuba].RAlvo*AVC.Ccont[Cuba].INominalCuba)
					 + AVC.Param[Cuba].Bemf;
  AvcLoc[Cuba].UltVCicCtrl=(AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba)
					 + AVC.Param[Cuba].Bemf;
#else
  AvcLoc[Cuba].VAlvo=(AVC.Ccont[Cuba].RAlvo*AVL.INominal)
					 + AVC.Param[Cuba].Bemf;
  AvcLoc[Cuba].UltVCicCtrl=(AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba)
					 + AVC.Param[Cuba].Bemf;
#endif
  /* Fim Alteracao - Carlos - 23/06/99 */

  if(EST_AVC(Cuba).Est.CorridaBanho eq FALSO)
  {
    /* -- Soma acrescimo a banda de controle superior por corrida -- */
    AVC.Ccont[Cuba].BandaContSupAtual=AVC.Param[Cuba].BandaContSup+
									  AVC.Param[Cuba].AcresBCSCorr;
    /* -- Incremento de corrida -- */
    AVC.Ccont[Cuba].ContIncCorr=0;
    AVC.Ccont[Cuba].IncCorr=AVC.Param[Cuba].IncCorrInic;
  }
}

/*
--------------------------------------------------------------------------------
| DuranteCorr - Ajusta resistencia enquanto chave ainda esta em corrida        |
--------------------------------------------------------------------------------
*/
void DuranteCorr(int Cuba)
{


  CalcRCicCorr(Cuba);
  AvcLoc[Cuba].RCicCorr = AVC.Cleit[Cuba].RCicCorr;
DEPURA(printf("McpCorrida->Durante corrida cuba=%d Contl=%d\n",Cuba,AVC.Cleit[Cuba].ContLCicCorr);)
  if (AVC.Cleit[Cuba].ContLCicCorr >= NumCicCorr)
  {
	VerificaResist(Cuba);
	/* -- Inicializa Resistencia media -- */
	AVC.Cleit[Cuba].RCicCorr = 0.0;
	AVC.Cleit[Cuba].ContLCicCorr = 0;
  }
}


/*
--------------------------------------------------------------------------------
| CalcRCicCorr - Calcula resistencia media para o ciclo de corrida             |
--------------------------------------------------------------------------------
*/
void CalcRCicCorr(int Cuba)
{
  double RCicCorrida,ContCicCorr;


  AVC.Cleit[Cuba].ContLCicCorr++;
  ContCicCorr = (double)AVC.Cleit[Cuba].ContLCicCorr;
  RCicCorrida = (double)AVC.Cleit[Cuba].RCicCorr;
  RCicCorrida = ((RCicCorrida * (ContCicCorr-1.0))+AVC.Cleit[Cuba].Rinst)/
				ContCicCorr;
  AVC.Cleit[Cuba].RCicCorr = (float)RCicCorrida;
  if (AVC.Cleit[Cuba].Vinst > AvcLoc[Cuba].Vmax)
	AvcLoc[Cuba].Vmax=AVC.Cleit[Cuba].Vinst;
}

/*
--------------------------------------------------------------------------------
| VerificaResist - Verifica se e' necessario mover anodo                       |
--------------------------------------------------------------------------------
*/
void VerificaResist(int Cuba)
{
  int	FaixaControlavel, SentidoMov;
  float	RErro;


  /* -- calcula ralvo com os incrementos -- */
  CalculaRAlvo(Cuba);
  /* -- calculo do erro -- */

  RErro=AVC.Ccont[Cuba].RAlvo-AVC.Cleit[Cuba].RCicCorr;
  /* -- Verifica se cuba esta na faixa controlavel -- */
  FaixaControlavel=VerificaFaixaControle(Cuba,RErro);

  /* -- Condicoes necessarias para habilitar movimentacao de anodo -- */
  if ((EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL) and
	  (EST_AVC(Cuba).ChaveAutMan eq AUTOMATICO) and
	  (EST_AVC(Cuba).ChaveLocRem eq REMOTO) and
	  (EST_AVC(Cuba).ForaLeitura eq FALSO) and
	  (EST_AVC(Cuba).Est.ReleTempoMM eq FALSO) and
	  (AVL.LinhaHabilitada eq VERDADEIRO))
  {
	/* -- Verifica condicoes operacionais para movimentar anodo -- */
	if (FaixaControlavel eq VERDADEIRO)
	{
	  if (EST_AVC(Cuba).Ea eq FALSO)
	  {
		if (RErro < 0)
		{ 
		  if (Comum->IdentReducao eq 5)
		  {
			if (AVC.User1[Cuba].ContMovCorr > 0)
			{
			  /* Permite movimentacao apenas para baixo durante corrida */
			  EfetuaMov(Cuba,RErro);
			  AVC.User1[Cuba].ContMovCorr--;
			}
			else
			if (AVC.User1[Cuba].ContMovCorr eq -1)
			{
			  /* Permite movimentacao apenas para baixo durante corrida */
			  EfetuaMov(Cuba,RErro);
			}
		  }
		  else
		  {
			/* Permite movimentacao apenas para baixo durante corrida */
			EfetuaMov(Cuba,RErro);
  	    	AvcLoc[Cuba].TMaxCorr += CalcEquivMotor(Cuba,RErro,&SentidoMov);
		  }
		}
	  }
	}
  }

}

/*
--------------------------------------------------------------------------------
| DuranteEfCorr - Ajusta resistencia apos chave ter sido retornada a automatico|
|                 durante o periodo especificado por TEfeitoCorr.              |
--------------------------------------------------------------------------------
*/
void DuranteEfCorr(int Cuba)
{
  float	VAlvo,VCicCont,VInst;
  char diff[12];


DEPURA(printf("McpCorrida->Durante efeito corrida cuba=%d Contl=%d\n",Cuba,AVC.Cleit[Cuba].ContLCicCorr);)
  if ((HoraAtualSec-AVC.Cleit[Cuba].HoraUltCorr) > AVC.Param[Cuba].TEfeitoCorr or
		AvcLoc[Cuba].TMaxCorr >= AVL.Par.TMaxCorrida)
  { /* -- Fim tempo efeito corrida. Fim tratamento de corrida. -- */
	EST_AVC(Cuba).EfeitoCorr=FALSO;
	EST_AVC(Cuba).Corrida=FALSO;
    /* -- Restaura banda de controle superior no fim da corrida -- */
	AVC.Ccont[Cuba].BandaContSupAtual=AVC.Param[Cuba].BandaContSup;
/* Retirado. Permite que o incremento de corrida continue mesmo apos corrida */
/* durante TIncCorr. */
//	AVC.Ccont[Cuba].IncCorr=0.0;
//	AVC.Ccont[Cuba].ContIncCorr=-1;
	/* -- Gera evento de fim de corrida -- */
	VAlvo=AVC.Ccont[Cuba].VAlvo;
	VInst=AVC.Cleit[Cuba].Vinst;
	if (Comum->IdentReducao eq 5)
	  AVC.User1[Cuba].ContMovCorr = -1;

	/* Inicio Alteracao - Carlos - 23/06/99 */
	/* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
	VCicCont=AvcLoc[Cuba].RCicCorr*AVC.Ccont[Cuba].INominalCuba + AVC.Param[Cuba].Bemf;
#else
	VCicCont=AvcLoc[Cuba].RCicCorr*AVL.INominal + AVC.Param[Cuba].Bemf;
#endif
	/* Fim Alteracao - Carlos - 23/06/99 */

	sprintf(diff,"%5.2f",AvcLoc[Cuba].Vmax-AvcLoc[Cuba].UltVCicCtrl);

    EST_AVC(Cuba).Est.ZeraCA = VERDADEIRO;
    EST_AVC(Cuba).Est.ProjetaCA = VERDADEIRO;

	if(EST_AVC(Cuba).Est.CorridaBanho eq FALSO)
	{
	  SUPERV_AVC(Cuba).Sup.DeltaRCorr =  ((AvcLoc[Cuba].Vmax-AvcLoc[Cuba].UltVCicCtrl)/ AVL.INominal) * pow(10,6);
	  GeraEvento(FIM_CORRIDA,Cuba,-1,ScoreGetStr(CORRIDA),diff,VCicCont,VInst,VAlvo);
	}
	else
	  GeraEvento(FIM_CORRIDA,Cuba,-1,"CorBanho",diff,VCicCont,VInst,VAlvo);

    EST_AVC(Cuba).Est.CorridaBanho = FALSO;
  }
  else
  { /* -- Dentro do tempo de efeito corrida. Continua ajustando resistencia -- */
	DuranteCorr(Cuba);
  }
}

/*
--------------------------------------------------------------------------------
| CalculaRAlvo - Calcula RAlvo para a cuba dada, apartir dos incrementos       |
--------------------------------------------------------------------------------
*/
void CalculaRAlvo(int Cuba)
{
  float Incr,RIncr,Rsetpoint,RincMax;

  if (EST_AVC(Cuba).TabOpeAtiva eq FALSO)
	/* -- inicializa VSetPoint atual -- */
	AVC.Ccont[Cuba].VSetPoint=AVC.Param[Cuba].VSetPointCnf;

  /* Inicio Alteracao - Carlos - 23/06/99 */
  /* Tratamento de booster de corrente */
 #ifdef BOOSTER_CORRENTE
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
		AVC.Ccont[Cuba].IncUsuario);
  if (AVC.Param[Cuba].HabIncRRap eq VERDADEIRO)
	Incr=Incr+AVC.Ccont[Cuba].IncRrap;
  if (AVC.Param[Cuba].HabIncRLent eq VERDADEIRO)
	Incr=Incr+AVC.Ccont[Cuba].IncRlent;
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
  /* -- calcula resistencia alvo de controle -- */
  AVC.Ccont[Cuba].RAlvo=Rsetpoint+RIncr;

  /* Inicio Alteracao - Carlos - 23/06/99 */
  /* Tratamento de booster de corrente */
#ifdef	BOOSTER_CORRENTE
  AVC.Ccont[Cuba].VAlvo=(AVC.Ccont[Cuba].RAlvo*AVC.Ccont[Cuba].INominalCuba)
					 + AVC.Param[Cuba].Bemf;
#else
  AVC.Ccont[Cuba].VAlvo=(AVC.Ccont[Cuba].RAlvo*AVL.INominal)
					 + AVC.Param[Cuba].Bemf;
#endif
  /* Fim Alteracao - Carlos - 23/06/99 */

}

/* -- Fim McpCorrida.c -- */
