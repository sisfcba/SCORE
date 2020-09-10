/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: SCORE

	SISTEMA		: CBA

	ARQUIVO		: MccCba.c

	CONTEUDO	: Modulo de Controle das Cubas - MccCba
	
				  Modulo responsavel pelo controle da posicao dos anodos  das 
				  cubas.   Este  controle e' feito com base nos dados basicos 
				  obtidos no modulo MCP (Modulo de Calculos Primarios)  e  de 
				  outros  parametros  relacionados  com  a  configuracao  e o 
				  status das cubas e da linha.  E' ativado pelo modulo MCC do 
				  kernel  do  Score  num  periodo   programavel   fixado,   a 
				  principio, em 2 minutos.

				  Este  modulo  possui  duas  funcoes principais.  Uma funcao 
				  (MccControle)  encarregada  estritamente  do   controle   e 
				  previsao  de  Efeito  Anodico  e  outra  funcao (MccSuperv) 
				  encarregada dos calculos para relatorios de supervisao.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 2.0		  -		  DATA  : 27/02/97

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
26/11/92 | Alteracao para tratamento de excessoes (divisao por    | Leonel
         | zero e erro de ponto flutuante)                        |        
-------------------------------------------------------------------------------
05/07/94 | Edicao inicial de migracao para o QNX 4.2			  | Leonel
-------------------------------------------------------------------------------
******************************************************************************/
/*
-------------------------------------------------------------------------------
                           Definicao de compilacao condicional
-------------------------------------------------------------------------------
*/
#define		PROGRAMA_PRINCIPAL

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
                           Prototipos
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[]);
void FPHandler(int Sig);
t_boolean ConsisteArgs(int Argc,char *Argv[]);

/*
-------------------------------------------------------------------------------
                           Main - MccCba
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[])
{
	t_mens_padrao Msg;
	int			Erro,TidRec;
	int			Responde;
	t_boolean		PartidaQuente;
	struct timespec start, stop;
	double accum;

	/* -- Recebe endereco da area de dados comum ao processo -- */
	Reply(Receive(0, &Comum, sizeof(Comum)), 0, 0);

	/* -- Inicializa apontadores para tabelas globais -- */
	InitVarsComum();

	/* -- Consiste Cuba inicial e cuba final a tratar -- */
	PartidaQuente=ConsisteArgs(argc,argv);

	/* -- Instala handler para tratar excessao de ponto flutuante -- */
	if (signal(SIGFPE,FPHandler) eq SIG_ERR)
		EmiteErroFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_ERR_1),COD_ERRO_60);
	/* -- Habilita geracao de excessao por divisao por zero -- */
	_control87(notb EM_ZERODIVIDE,EM_ZERODIVIDE);

	/* -- Copia NumCubas da base de dados para local -- */
	NumCubas=AVL.NumCubas;
	/* -- Intervalo do ciclo de controle em minutos -- */
	IntervCicCont=(Comum->BaseTempoMcp*Comum->BaseTempoMcc)/(SAD_TICKS*60);

	if (PartidaQuente eq VAL_VERDADEIRO)
	{ /* Modulo ativado com o sistema ja' rodando, nao sera' enviada mensagem
		de inicializacao pelo Mcc. Logo inicializa oque for necessario */
		DEPURA(printf("MccUser->Partida a quente\n");)
		/* -- inicializa  todas as variaveis de trabalho e executa os
			procedimentos necessarios a inicializacao -- */
		/* -- inicializa  todas as variaveis de trabalho e executa os
			procedimentos necessarios a inicializacao -- */
		IniMccCba();
		IniMccControle();
		IniMccSupervisao();
	}

	loop
	{ /* -- que seja eterno enquanto dure -- */
		Erro=FALSO;
		Responde=VERDADEIRO;
		TidRec=Receive(0,&Msg,sizeof(Msg));

		if (Msg.Origem eq MCC)
		{
			/* -- Hora atual = mesma hora do ciclo de controle -- */
			HoraAtualCtrl=AVL.HoraAtualControle;
			memcpy(&HoraAtual,localtime(&HoraAtualCtrl),sizeof(HoraAtual));
			HoraAtualCtrl=HoraAtualCtrl/TIMES_PER_SEC; /* -- segs. apartir 1/1/1970 -- */
			switch (Msg.Acao)
			{
				case INICIALIZACAO:
					/* -- inicializa  todas as variaveis de trabalho e executa os
							procedimentos necessarios a inicializacao -- */
					IniMccCba();
					IniMccControle();
					IniMccSupervisao();
					Msg.Origem=-1;
					Msg.Parametro[0]=Erro;
					Reply(TidRec,&Msg,sizeof(Msg));
					Responde=FALSO;
					/* -- Aguarda sinalizacao de partida do sistema -- */
					AguardaPartida();
					/* -- Pega Hora atual -- */
					HoraAtualCtrl=time(NULL);
					memcpy(&HoraAtual,localtime(&HoraAtualCtrl),sizeof(HoraAtual));
					HoraAtualCtrl=HoraAtualCtrl/TIMES_PER_SEC; /* -- segs. apartir 1/1/1970 -- */
					break;

				case CICLO_CONTROLE:
					
					clock_gettime(CLOCK_REALTIME, &start);

					/* -- Algoritmo de controle -- */
					MccControle();

					//#ifdef	DEPURA_MEDE_TEMPO
					//  clock_gettime(CLOCK_REALTIME, &start);
					//#endif

					/* -- Calculos de supervisao diaria e turno -- */
					MccSuperv();

					//#ifdef	DEPURA_MEDE_TEMPO
					//	clock_gettime(CLOCK_REALTIME,&stop);
					//	accum=(stop.tv_sec-start.tv_sec) + (double)(stop.tv_nsec-start.tv_nsec)
					//			/ 1000000000.0;
					//	/* -- Salva o tempo medido para execucao de uma ativacao na variavel
					//			VetRinst[4] para a primeira cuba -- */
					//	AVC.Cleit[0].VetRinst[4]=accum;
					//#endif

					clock_gettime(CLOCK_REALTIME,&stop);

					accum=(stop.tv_sec-start.tv_sec) + (double)(stop.tv_nsec-start.tv_nsec)
							/ 1000000000.0;

					AVL.Trab.TimerMcc = accum;

					break;

				default:
					EmiteErroFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_ERR_1),COD_ERRO_58);
					Erro=VERDADEIRO;
			}
		}
		else
		{
			EmiteErroFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_ERR_8),COD_ERRO_62,
							Msg.Origem);
			Erro=VERDADEIRO;
		}

		if (Responde)
		{
			Msg.Origem=-1;
			Msg.Parametro[0]=Erro;
			Reply(TidRec,&Msg,sizeof(Msg));
		}
	}
}

/*
-------------------------------------------------------------------------------
                           Funcoes
-------------------------------------------------------------------------------
*/
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
		printf("Numero de argumentos invalido! Use: %s cuba_ini cuba_fim [-quente]\n",
			Argv[0]);
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
| IniMccCba - Executa as acoes necessarias a inicializacao do modulo MccCba          |
--------------------------------------------------------------------------------
*/
void IniMccCba(void)
{
	/* -- Posicao para caso de f.p. exception -- */
	PosicaoGlobal=10;

	/* -- Copia NumCubas da base de dados para local -- */
	NumCubas=AVL.NumCubas;

	/* -- Intervalo do ciclo de controle em minutos -- */
	IntervCicCont=(Comum->BaseTempoMcp*Comum->BaseTempoMcc)/(SAD_TICKS*60);

	/* -- inicializa hora de inicio do ciclo de controle -- */
	HoraAtualCtrl=time(NULL);
	memcpy(&HoraAtual,localtime(&HoraAtualCtrl),sizeof(HoraAtual));

	/* -- Ponteiro para a hora do ciclo de controle atual ja dividida -- */
	PHoraAtual=&HoraAtual;
	HoraAtualCtrl=HoraAtualCtrl/TIMES_PER_SEC; /* -- segs. apartir 1/1/1970 -- */

	/* -- Inicializa numero de algoritmo -- */
	IniNumAlgCtr();
	
}

/*
--------------------------------------------------------------------------------
| FPHandler - Handler para tratamento de excessao de ponto flutuante           |
--------------------------------------------------------------------------------
*/
void FPHandler(int Sig)
{
	unsigned	FPCopStatus;

	FPCopStatus=_status87();
	sprintf(MsgException,ScoreGetStr(SCORE_ERR_5),
		ConvCubScoreOper(CubaGlobal),COD_ERRO_59,PosicaoGlobal);
	_clear87();	/* -- clear exception flags -- */
	siglongjmp(MccEnvBuf,1);
}

/* -- Fim do arquivo Mcc.c -- */

