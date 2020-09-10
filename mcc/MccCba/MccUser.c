/******************************************************************************

			 ACCENTURE - APAS - ACCENTURE PLANT AND AUTOMATION SOLUTIONS
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 5.0

	PROJETO		: SCORE

	SISTEMA		: CBA

	ARQUIVO		: MccUser.c

	CONTEUDO	: Esqueleto de exemplo de um programa de controle ativado pelo
                  Modulo de Controle das Cubas - MCC.
                  E'  ativado  pelo modulo de controle das cubas (MCC) a  cada
                  ciclo de controle e  na  partida  do  sistema.
				  OBS.: Para ser ativado pelo Mcc deve ser instalado no Score
						atraves do programa InstalaCtrl. Pode ser instalado
						com o sistema ativado (partida a quente) ou nao. Caso
						se deseje desativa-lo sem desativar o sistema deve-se
						utilizar tambem o programa InstalaCtrl ao inves de
						simplesmente dar um slay.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 1.0			-		DATA	:	29/11/93

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
Data     | Descricao                                            | Autor 
-------------------------------------------------------------------------------
02/10/12 | Kit de desenvolvimento para a CBA                    | Leonel
-------------------------------------------------------------------------------
******************************************************************************/
/*
-------------------------------------------------------------------------------
                           Definicao de compilacao condicional
-------------------------------------------------------------------------------
*/
#define		PROGRAMA_PRINCIPAL

/********* Compilacao condicional de codigos de exemplo ************/
#define		MOVIMENTACAO_ANODO
#define		COMANDA_SAIDA_REMOTA
/********* Compilacao condicional de codigos de exemplo ************/

/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include	<MccUser.h>
#include	<stdlib.h>
#include	<stdio.h>

/*
-------------------------------------------------------------------------------
                           Variaveis Globais
-------------------------------------------------------------------------------
*/
/* -- Apontadores para as tabelas comuns -- */
#include	<VarsComum.h>

/*
-------------------------------------------------------------------------------
	Main - MccUser - Exemplo de tarefa de controle ativada pelo MCC
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[])
{
  t_mens_padrao Msg;
  int			TidRec;
  int			Responde;
  t_boolean		PartidaQuente;

  /* -- Recebe endereco da area de dados comum ao processo -- */
  Reply(Receive(0, &Comum, sizeof(Comum)), 0, 0);

  /* -- Inicializa apontadores para tabelas globais -- */
  InitVarsComum();

  /* -- Consiste Cuba inicial e cuba final a tratar -- */
  PartidaQuente=ConsisteArgs(argc,argv);

  /* -- Intervalo do ciclo de controle em segundos -- */
  /* -- Pode ser utilizado para calculos de duracao baseados no numero de
		ciclos de controle -- */
  IntervCicCont=((Comum->BaseTempoMcp*Comum->BaseTempoMcc)/SAD_TICKS);

  if (PartidaQuente eq VAL_VERDADEIRO)
  { /* Modulo ativado com o sistema ja' rodando, nao sera' enviada mensagem
	   de inicializacao pelo Mcc. Logo inicializa oque for necessario */

DEPURA(printf("MccUser->Partida a quente\n");)
	/* -- inicializa  todas as variaveis de trabalho e executa os
		procedimentos necessarios a inicializacao -- */
	IniMccUser();
  }

  loop
  { /* -- que seja eterno enquanto dure -- */
	Responde=VERDADEIRO;
	TidRec=Receive(0,&Msg,sizeof(Msg));

	if (Msg.Origem eq MCC)
	{
	  /* -- Hora atual = mesma hora do ciclo de controle -- */
	  /* -- Pode ser utilizada para comparacoes de horario -- */
	  HoraAtualCtrl=AVL.HoraUltControle;
	  memcpy(&HoraAtual,localtime(&HoraAtualCtrl),sizeof(HoraAtual));

	  switch (Msg.Acao)
	  {
		case INICIALIZACAO:
DEPURA(printf("MccUser->Inicializacao\n");)
		  /* -- inicializa  todas as variaveis de trabalho e executa os
				procedimentos necessarios a inicializacao -- */
		  IniMccUser();
		  Msg.Origem=MODULO_MCC0;
		  Reply(TidRec,&Msg,sizeof(Msg));
		  Responde=FALSO;
          /* -- Aguarda sinalizacao de partida do sistema -- */
		  /* -- O micro que estiver em hot standby ficara' bloqueado aqui ate'
				assumir o controle. -- */
		  AguardaPartida();
		  /* -- Pega Hora atual -- */
		  HoraAtualCtrl=time(NULL)/TIMES_PER_SEC; /* -- segs. apartir 1/1/1980 -- */
		  memcpy(&HoraAtual,localtime(&HoraAtualCtrl),sizeof(HoraAtual));
		  break;

		case CICLO_CONTROLE:
		  if (AVL.LinhaHabilitada eq VERDADEIRO)
		  {
			/* -- Processa cada cuba -- */
			/* -- Esta funcao NAO PODE FICAR BLOQUEADA pois esta' de posse
				da memoria compartilhada e o controle esta' aguardando a res-
				posta para prosseguir o seu processamento -- */
DEPURA(printf("MccUser->Ciclo Controle\n");)
			ProcessaCubas();
		  }
		  break;

		default:
		  EmiteAlarmeFor(TODOS_DISPOSITIVOS,"Acao [%d] nao esperada!",Msg.Acao);
	  }
	}
	else
	{
	  EmiteAlarmeFor(TODOS_DISPOSITIVOS,"Mensagem de origem [%d] desconhecida!",
					Msg.Origem);
	}

	if (Responde)
	{
	  Msg.Origem=MODULO_MCC0;
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
| IniMccUser - Inicializa as variaveis necessarias na partida                  |
--------------------------------------------------------------------------------
*/
void IniMccUser(void)
{
#ifdef	EXEMPLO_INICIALIZACAO
/************************* exemplo ***********************/
  int CubaOpe, Cuba;

  /* -- Inicializar as variaveis globais de trabalho do modulo -- */

  /* -- Inicializar todas as variaveis da base de dados que forem de
        responsabilidade deste modulo (variaveis alteradas por este modulo).
		Alocar semaforo da tabela correspondente da base de dados antes de
		acessar as variaveis, conforme exemplo abaixo -- */

  /* -- Variavel da tabela de linha -- */
  AlocaSemaf(SEMAF_AVL);
  AVL.ResAvlGer[0] = 1;
  LiberaSemaf(SEMAF_AVL);

  /* -- Aloca semaforo de base de dados - ATENCAO: para um codigo muito grande no loop for
        eh recomendado alocar e desalocar dentro do loop para evitar "prender" a base de dados
		por muito tempo -- */
  AlocaSemaf(SEMAF_AVC);
  /* -- Executa os calculos de controle -- */
  for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
  {
	/* -- Converte numero de operacao da cuba para indice na tabela -- */
	Cuba=ConvCubOperScore(CubaOpe);
	if (Cuba eq -1)
		continue;

	/* -- Inicializa variaveis para cada cuba -- */
	AVC.Ccont[Cuba].ResCAvc[0] = 0;
	AVC.Ccont[Cuba].ResCAvc[1] = 0;
  }
  LiberaSemaf(SEMAF_AVC);
/*********************** fim exemplo *********************/
#endif
}


/*
--------------------------------------------------------------------------------
| ProcessaCubas - Processa os calculos necessarios para cada cuba.             |
--------------------------------------------------------------------------------
*/
void ProcessaCubas(void)
{
  int	Cuba, CubaOpe;

  /* -- Executa os calculos de controle -- */
  for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
  {
	/* -- Converte numero de operacao da cuba para indice na tabela -- */
	Cuba=ConvCubOperScore(CubaOpe);
	if (Cuba eq -1)
		continue;
	/* -- Aloca semaforo de base de dados - Neste caso eh recomendado alocar e
	      desalocar dentro do loop para evitar "prender" a base de dados
	      por muito tempo -- */
	AlocaSemaf(SEMAF_AVC);

DEPURA(printf("MccUser->Trata cuba %d [%d]\n",CubaOpe,Cuba);)
	/* -- Verifica condicoes para controle da cuba -- */
	if ((EST_AVC(Cuba).ForaLeitura eq FALSO) and
		(EST_AVC(Cuba).ForaControle eq FALSO) and
		(AVL.LinhaHabilitada eq VERDADEIRO))
	{
	  if (EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL)
	  {
		/* -- Processa os calculos relativos a cada cuba -- */

#ifdef MOVIMENTACAO_ANODO
		/* -- Caso seja necessario inibir a movimentacao automatica de anodo
			  pelo algoritmo de controle, seguir o exemplo abaixo: -- */
		
		/******** exemplo de codigo para inibir movimentacao de anodo ********/
#ifdef	INIBE_MOVIMENTACAO
		/* -- Inibir movimentacao do controle -- */
		EST_AVC(Cuba).InibeControleUsu=VERDADEIRO;
#endif
		/****** fim exemplo de codigo para inibir movimentacao de anodo ******/

		/* -- Caso seja necessaria a movimentacao de anodo, deve ser seguido
			  o seguinte exemplo: -- */
		/********** exemplo de codigo para movimentacao de anodo ********/
		MovimentaAnodo(Cuba,SUBIR_ANODO,2.5);	/* -- duracao em segundos -- */
		/********* fim exemplo de codigo para movimentacao de anodo *******/
#endif
#ifdef	COMANDA_SAIDA_REMOTA
		/****** exemplo de codigo para ligar uma saida da remota durante
		        5 segundos *******/
		/*-- Verifica condicoes para acionamento --*/
		if( EST_AVC(Cuba).ChaveAutMan eq AUTOMATICO )
		{ /* -- computador esta em modo automatico -- */
		  if( EST_AVC(Cuba).ChaveLocRem eq REMOTO )
		  { /* -- chave do painel esta em modo remoto -- */
			int BitAcao,Tempo;

			BitAcao = AVC.Abs[Cuba].BitLampEa; /* -- Bit a ser acionado -- */
			Tempo = 5*BASE_TEMPO_REMOTA; /* -- tempo em ticks da remota.
						Se tempo = 0 apenas	liga a saida sem temporizar.
						Para desligar mudar acao para DESLIGAR ou inves de
						LIGAR -- */
			if (ComandaSaidaRem(Cuba,LIGAR,BitAcao,Tempo) ne 0)
			  ;/* -- Falha no acionamento da saida -- */
		  }
		}
		/**** fim exemplo de codigo para acionar uma saida na remota *****/
#endif
		/******** exemplo de codigo para habilitar movimentacao de anodo ********/
#ifdef	INIBE_MOVIMENTACAO
		/* -- Habilitando movimentacao novamente -- */
		EST_AVC(Cuba).InibeControleUsu=FALSO;
#endif
		/****** fim exemplo de codigo para habilitar movimentacao de anodo ******/

	  } /* -- if EstadoCuba -- */
	} /* -- if fora leitura -- */
	LiberaSemaf(SEMAF_AVC);
  } /* -- for -- */
} /* -- ProcessaCubas -- */


#ifdef MOVIMENTACAO_ANODO
void MovimentaAnodo(int Cuba, int Sentido, float Duracao)
{
	int DurInt;
	float VAlvo, VInst, VCicCont;

	/********** exemplo de codigo para movimentacao de anodo ********/
	/*-- Verifica condicoes para executar movimentacao de anodo --*/
	if( EST_AVC(Cuba).ChaveAutMan eq AUTOMATICO )
	{ /* -- computador esta em modo automatico -- */
	  if( EST_AVC(Cuba).ChaveLocRem eq REMOTO )
	  { /* -- chave do painel esta em modo remoto -- */
		/* -- Critica a duracao do movimento (em segundos) -- */
		if( Sentido eq SUBIR_ANODO )
		{
		  if ( Duracao < AVC.Param[Cuba].DurMovCimaMin or	
			   Duracao > AVC.Param[Cuba].DurMovCimaMax )
		  {
			/* -- Duracao invalida! -- */
			EmiteAlarmeFor(TODOS_DISPOSITIVOS,"Cuba %d - Duracao subida invalida!",Cuba);
			return;
		  }
		}
		else
		{ /* -- Descer anodo -- */
		  if ( Duracao < AVC.Param[Cuba].DurMovBaixoMin or	
			   Duracao > AVC.Param[Cuba].DurMovBaixoMax )
		  {
			/* -- Duracao invalida! -- */
			EmiteAlarmeFor(TODOS_DISPOSITIVOS,"Cuba %d - Duracao descida invalida!",Cuba);
			return;
		  }
		}
		/* -- comanda a movimentacao do anodo (a duracao esta em multiplos de
			 50 mseg) -- */
		DurInt = (int)(Duracao*BASE_TEMPO_REMOTA);
		MoveAnodo( Cuba, DurInt, Sentido );

		/* -- Gera evento de movimentacao automatica -- */
		VAlvo=AVC.Ccont[Cuba].VAlvo;
		VInst=AVC.Cleit[Cuba].Vinst;
		VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal+
			 AVC.Param[Cuba].Bemf;
		/* -- Gera evento de movimentacao automatica do anodo -- */
		if (Sentido eq DESCER_ANODO)
		  GeraEvento(DESCIDA_AUT_ANODO,Cuba,-1,"APLIC01",(float)Duracao,
					 VCicCont,VInst,VAlvo);
		else
		  GeraEvento(SUBIDA_AUT_ANODO,Cuba,-1,"APLIC01",(float)Duracao,
					 VCicCont,VInst,VAlvo);
		EST_AVC(Cuba).EfeitoMove=VERDADEIRO;
		AVC.Ccont[Cuba].HoraUltMove=HoraAtualCtrl;
		AVC.Ccont[Cuba].SentidoUltMove=Sentido;
		AVC.Ccont[Cuba].DuracaoUltMove=Duracao;
	  }
	}
	/********* fim exemplo de codigo para movimentacao de anodo *******/
}
#endif

/* -- Fim arquivo MccUser.c -- */
