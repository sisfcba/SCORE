/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.1

	PROJETO		: CBA - Companhia Brasileira de Aluminio SA

	SISTEMA		: SALAS 120KA II e III

	ARQUIVO		: McpPF.c

	CONTEUDO	: Algoritmo de alimentacao point feeder conforme especifica-
                  cao no documento "Algoritmo de Alimentacao (37501)" de
				  16/12/96.

                  E'  ativado  pelo modulo de calculos primarios (MCP) a cada
                  ciclo de leitura, na desativacao de linha e na  partida  do
				  sistema.

				  OBS.: Para ser ativado pelo Mcp deve ser instalado no Score
						atraves do programa InstalaCtrl. Pode ser instalado
						com o sistema ativado (partida a quente) ou nao. Caso
						se deseje desativa-lo sem desativar o sistema deve-se
						utilizar tambem o programa InstalaCtrl ao inves de
						simplesmente dar um slay.

	AUTOR		: Ricardo Teixeira Leite Mourao / Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	02/01/97

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
Data     | Descricao                                            | Autor 
-------------------------------------------------------------------------------
02/01/97 | Edicao inicial                                       | Ricardo-Leonel
-------------------------------------------------------------------------------
15/01/99 | Alteracao conforme proposta 1006CA                   | Leonel
-------------------------------------------------------------------------------
21/11/00 | Inclusao de PF para salas II a IV                    | Leonel/Robson
-------------------------------------------------------------------------------
01/09/17 | TK-ALIM - Preparac�o Toolkit Alimentacao             | Carlos
-------------------------------------------------------------------------------
$Id: McpPF.c,v 1.2 2004/04/26 14:23:54 leo Exp $

$Log: McpPF.c,v $
Revision 1.2  2004/04/26 14:23:54  leo
Inclusao de controle de alteracao.

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
#include	<sys/kernel.h>
#include	<time.h>
#include    <string.h>
#include	<ScoreMsgs.h>
#include	<ScoreErros.h>
#include	<McpPF.h>
#include	<UsuRemota.h>
#include	<RemotaAtn7.h>

/*
-------------------------------------------------------------------------------
                           Variaveis Globais
-------------------------------------------------------------------------------
*/
/* -- Apontadores para as tabelas comuns -- */
#include	<VarsComum.h>

#ifdef ATIVA_SIMULACAO
/********************************* teste teste **************************/
int ManAlimLoc= FALSO;
/********************************* teste teste **************************/
#endif


/*
-------------------------------------------------------------------------------
	Main - McpPF - Implementa o algoritmo de alimentacao
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[])
{
	#ifndef ATIVA_SIMULACAO
		int			TidMcp;
	#else
		int			ContSegundo;
		int			ContMinuto;
		int			ContHora;
		int			Faz;
	#endif

	t_mens_padrao	Mens;
	t_boolean		Responde;
	t_boolean		Partida;
	t_boolean		PartidaQuente;

	#ifndef ATIVA_SIMULACAO
		/* -- Recebe endereco da area de dados comum ao processo -- */
		Reply(Receive(0, &Comum, sizeof(Comum)), 0, 0);
			
		/* -- Inicializa apontadores para tabelas globais -- */
		InitVarsComum();
	#else
		/*-- Pega area de memoria comum --*/
		if (PegaComum(&Comum))
		{
			printf("/n/n NAO CONSEGUI LOCALIZAR TABELA GLOBAL \n");
			exit(0);
		}
		ContSegundo = 0;
		ContMinuto  = 0;
		ContHora    = 0;
		Faz		  = 0;
	#endif

	/* -- Guarda hora atual em segundos -- */
	HoraAtualSec=time(NULL)/TIMES_PER_SEC; /* -- segs. apartir 1/1/1980 -- */

	// Inserido em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
	LinhaDesligada=VAL_FALSO;

	/* -- Consiste Cuba inicial e Cuba final a tratar -- */
	PartidaQuente=ConsisteArgs(argc,argv);

	if (PartidaQuente eq VAL_VERDADEIRO)
	{ /* Modulo ativado com o sistema ja' rodando, nao sera' enviada mensagem
		de inicializacao pelo Mcp. Logo inicializa oque for necessario */

		DEPURA(printf("McpPF->Partida a quente\n"));
		/* -- Inicializa todas as variaveis de trabalho e executa os procedimentos 
			necessarios a inicializacao dos calculos. -- */
		IniMcpPFHot();
		/* -- Marca que a proxima ativacao de inicializacao nao sera' a primeira -- */
		Partida=VAL_FALSO;
	}
	else
		/* -- Marca que a proxima ativacao de inicializacao sera' a primeira -- */
		Partida=VAL_VERDADEIRO;

	loop	/*  Loop eterno */
	{
		Responde=VAL_VERDADEIRO;
		#ifndef ATIVA_SIMULACAO
		/* -- Recebe ativacao do MCP -- */
			if((TidMcp = Receive(0, &Mens, sizeof(Mens))) <= 0)
				EmiteErroFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_ERR_8),COD_ERRO_18,errno);
				//	  EmiteErroFor(TODOS_DISPOSITIVOS,"Erro receive TidMcp=%x",TidMcp);
		#else
			if ( ContSegundo eq 120 )
			{
			ContMinuto += 1;
			printf("Hora = %d   Minuto =  %d \n",ContHora,ContMinuto);
			sleep (1);
			ContSegundo = 0;
			if ( ContMinuto eq 60 )
			{
				ContHora += 1;
				ContMinuto = 0;
			}	
			if ( ContHora eq 24 )
			{
				ContHora = 0;
			}	
			}
			Mens.Parametro[0]=ContSegundo; /* Numero do ciclo de leitura atual */
			ContSegundo +=1;
			if ( Faz < 2 )
			{
			printf("\n Acao [1-Inic,2-CLeit,4-DesLin]: ");
			scanf("%d", &Mens.Acao);
			Faz += 1;
			}
		#endif

		/* -- Guarda hora atual em secundos -- */
		HoraAtualSec=time(NULL)/TIMES_PER_SEC; /* -- segs. apartir 1/1/1980 -- */

		switch(Mens.Acao)
		{			
			case INICIALIZACAO:
				DEPURA(printf("McpPF->Inicializacao\n"));
				// Inserido em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
				if ((AVL.LinhaHabilitada eq FALSO) or (LinhaDesligada eq VAL_FALSO))
				{ // so reinicializa quando linha nao foi religada agora
				/* -- Inicializa todas as variaveis de trabalho e executa os procedimentos 
					necessarios a inicializacao do calculos. -- */
					IniMcpPF();
				}
				#ifndef ATIVA_SIMULACAO
					if (Partida)
					{
						Partida=VAL_FALSO;
						Reply(TidMcp,&Mens,sizeof(Mens));
						Responde=VAL_FALSO;
						/* -- Aguarda sinalizacao de partida do sistema -- */
						/* -- O micro que estiver em hot standby ficara' bloqueado aqui ate'
								assumir o controle. -- */
						AguardaPartida();
						/* -- Pega Hora atual -- */
						HoraAtualSec=time(NULL)/TIMES_PER_SEC; /* -- segs. apartir 1/1/1980 -- */
					}
				#endif
			break;
			
			case CICLO_LEITURA:	
				DEPURA(printf("McpPF->Ciclo Leitura\n"));
				ProcessaCubas(Mens.Parametro[0]); /* Numero do ciclo de leitura atual */
				// Inserido em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
				LinhaDesligada=VAL_FALSO;
			break;

			case DESABILITOU_LINHA:
				/* -- Caso necessario, executa procedimentos para linha desabilitada -- */
				// Inserido em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
				LinhaDesligada=VAL_VERDADEIRO;
			break;
			
			default:
				EmiteErroFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_ERR_8),COD_ERRO_58,
							Mens.Acao);
				//		EmiteErroFor(TODOS_DISPOSITIVOS,"Erro Fatal - Acao nao tratada %d",
				//				     Mens.Acao);
			break;
		}

		#ifndef ATIVA_SIMULACAO
			if (Responde)
			Reply(TidMcp,&Mens,sizeof(Mens));
		#endif
	}
}

/*
--------------------------------------------------------------------------------
| ConsisteArgs - Consiste Cuba inicial e final. Retorna verdadeiro se partida  |
|                a quente (switch -quente). Nao retorna se erro.               |
--------------------------------------------------------------------------------
*/
t_boolean ConsisteArgs(int Argc,char *Argv[])
{
	t_boolean partida_quente;

	if ((Argc ne 3) and (Argc ne 4))
  	{
		printf("Numero de argumentos invalido! Use: %s Cuba_ini Cuba_fim [-quente]\n",
			Argv[0]);
		exit(EXIT_FAILURE);
  	}
	CubaIni=atoi(Argv[1]);
	CubaFim=atoi(Argv[2]);
	if (ConsCubasOpe(CubaIni,CubaFim) ne ERRO_OK)
	{
		printf("Argumentos invalidos! Use: %s Cuba_ini Cuba_fim\n",Argv[0]);
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
	IniMcpPF - Inicializacao de todas as variaveis relacionadas a este modulo
--------------------------------------------------------------------------------
*/
void IniMcpPF (void)
{
  	int Cuba, CubaOpe;

  	/* -- Inicializar as variaveis globais de trabalho do modulo -- */

  	/* Armazena hora da partida da tarefa */
  	HoraPartidaMcpPF= HoraAtualSec;

	/* -- Inicializar todas as variaveis da base de dados que forem de
			responsabilidade deste modulo (variaveis alteradas por este modulo).
			Alocar semaforo da tabela correspondente da base de dados antes de
			acessar as variaveis -- */

	/* -- Inicializa numero de algoritmo -- */
	IniNumAlgCtr();

	/* -- Inicializa variaveis para cada Cuba -- */
	#ifndef ATIVA_SIMULACAO
		AlocaSemaf(SEMAF_AVC);
	#endif
	for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
	{
		/* -- Converte numero de operacao da Cuba para indice na tabela -- */
		Cuba=ConvCubOperScore(CubaOpe);
		if (Cuba eq -1)
			continue;

		//	if (AlgControle(Cuba,ALG_SCORE02) eq VERDADEIRO)
		//	if (AVC.ParUser1[Cuba].HabilitaPF eq VERDADEIRO)
		//	  IniPFCuba(Cuba);
	}

	/* inicializa corrente da linha no ciclo anterior */
	IinstOld=AVL.Iinst;

	/* Intervalo de leitura em segundos */
	IntervLeit=Comum->BaseTempoMcp*0.5;

	#ifndef ATIVA_SIMULACAO
		LiberaSemaf(SEMAF_AVC);
	#endif
}


/*
--------------------------------------------------------------------------------
 IniPFCuba - Inicializacao de todas as variaveis da Cuba
--------------------------------------------------------------------------------
*/
void IniPFCuba(int Cuba)
{
byte i, Seq;

  /* Inicializa intervalo de corrente.
     Nota: A variavel AVC.User1[Cuba].EfiCurr eh inicializada pelo 
	       programa IniBd. A partir dai, o algoritmo de alimentacao se 
		   encarrega de atualiza-la. */    
  
/* -- Alteracao - Inicio - Robson - 15/11/2000 - Quantidades diferentes por acionador -- */
  //Seq = AVC.ParUser1[Cuba].Sequencia[AVC.User1[Cuba].PassoCadencia] - 1;
	Seq = abs(EST_AVC(Cuba).Est.LadoProxPF - 1);
  AVC.User1[Cuba].IntervCurr=   AVC.ParUser1[Cuba].QuantAlumCarga[Seq]/ 
                                (AVC.User1[Cuba].EfiCurr*K_CONSUMO);
/* -- Alteracao - Fim - Robson - 15/11/2000 - Quantidades diferentes por acionador -- */
  
  /* inicializa eficiencia de corrente */
  /* AVC.User1[Cuba].EfiCurr= AVL.Par.EfiCurr; */

  EST_AVC(Cuba).Est.CheckAtivo=FALSO;
  EST_AVC(Cuba).Est.CheckOperador=FALSO;	/* Operador solicita entrada em check */

  EST_AVC(Cuba).InibeControleAlim= FALSO;   /* habilita movimentacao de anodo */

  /* Controla numero de overfeeds em Check */
  AVC.User1[Cuba].NumOverCheck=0;

  /* -- Desabilita ruido de alimentacao -- */
  EST_AVC(Cuba).Est.RuidoAlim= FALSO;
  
  /* -- Coloca valor inicial para flag que indica concentracao 
        (utilizado no overfeed para saber se pode habilitar movimentacao
		 do anodo -> se verdadeiro entao desabilitar a movimentacao) -- */
  AVC.User1[Cuba].ConcBaixa= FALSO;

  /* Inicializa Tempo no Estado Atual */
  AVC.User1[Cuba].TempEstAtual = 0;
  /* Guarda estado anterior */
  //AVC.User1[Cuba].EstadoAlimAnt = EST_ALIM_EXCECAO;
  /* Atualiza o novo estado */
  AVC.User1[Cuba].EstadoAlimAtual=EST_ALIM_EXCECAO;
  /* Coloca data e hora inicio mudanca de estado */
  //AVC.User1[Cuba].HoraIniEstAtual = HoraAtualSec;
  /* Inicializa quantidade de alumina alimentada no estado atual */
  AVC.User1[Cuba].QtAAlimEstAtual = 0.0;

  /* inicializa valores de subestado */
  AVC.User1[Cuba].State=ALIM_EXC_ESPERA1;	 /* Sub estado do estado atual */
  //AVC.User1[Cuba].InicioSubEst=VERDADEIRO;	 /* Sinaliza inicio de subestado */
  AVC.User1[Cuba].HoraIniSubEstAtual=HoraAtualSec; /* Hora de inicio mudanca de subestado */

/* -- Alteracao - Inicio - Robson - 23/10/2000 - alteracao PF CBA -- */
  for (i=0; i<NUM_CONJ_ALIM; i++)
  {
	AVC.User2[Cuba].TQuebInib[i] = 0;
	AVC.User2[Cuba].TAlimInib[i] = 0;
  }
/* -- Alteracao - Fim - Robson - 23/10/2000 - alteracao PF CBA -- */

  /* -- Muda para o novo estado -- */
  MudaEstadoAlim(Cuba,EST_ALIM_EXCECAO,MUDA_CONTROLE);

} /* IniPFCuba */

/*
--------------------------------------------------------------------------------
	IniMcpPFHot - Inicializacao de todas as variaveis qdo partida a quente
--------------------------------------------------------------------------------
*/
void IniMcpPFHot(void)
{
  int Cuba, CubaOpe;

  /* -- Inicializar as variaveis globais de trabalho do modulo -- */

  /* Armazena hora da partida da tarefa */
  HoraPartidaMcpPF= HoraAtualSec;

  /* -- Inicializar todas as variaveis da base de dados que forem de
        responsabilidade deste modulo (variaveis alteradas por este modulo).
		Alocar semaforo da tabela correspondente da base de dados antes de
		acessar as variaveis -- */

  /* -- Inicializa numero de algoritmo -- */
  IniNumAlgCtr();

  /* -- Inicializa variaveis para cada Cuba -- */
#ifndef ATIVA_SIMULACAO
  AlocaSemaf(SEMAF_AVC);
#endif
  for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
  {
	/* -- Converte numero de operacao da Cuba para indice na tabela -- */
	Cuba=ConvCubOperScore(CubaOpe);
	if (Cuba eq -1)
	  continue;
//	if (AlgControle(Cuba,ALG_SCORE02) eq VERDADEIRO)
//	if (AVC.ParUser1[Cuba].HabilitaPF eq VERDADEIRO)
//	  IniPFCuba(Cuba);
  }

  IinstOld=AVL.Iinst;

  /* Intervalo de leitura em segundos */
  IntervLeit=Comum->BaseTempoMcp*0.5;

#ifndef ATIVA_SIMULACAO
  LiberaSemaf(SEMAF_AVC);
#endif
}

/*
--------------------------------------------------------------------------------
| ProcessaCubas - Processa os calculos necessarios para cada Cuba.             |
--------------------------------------------------------------------------------
*/
void ProcessaCubas(int NumCicLeit)
{
	int	      Cuba, CubaOpe;
	int		  prox_estado;

	#ifndef ATIVA_SIMULACAO
  		AlocaSemaf(SEMAF_AVC);
  		AlocaSemaf(SEMAF_SUPERV_AVC);
  		AlocaSemaf(SEMAF_HIST_TURNO);
	#endif

	// Alterado em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
	/* -- Sincronismo com o controle de 2 minutos -- */
	//  if (NumCicLeit eq SINC_CONTRL )
	//	ControleAtivo = VERDADEIRO;
	//  else
	//    ControleAtivo = FALSO;

	/* verifica se sistema ou linha ativado recentemente e espera estabilizar */
	//  if (AVL.LinhaHabilitada eq FALSO)
	//  {
	//		LinhaAtiva=FALSO;
	//		HoraPartida=HoraAtualSec;
	//  }
	//  if (LinhaAtiva eq VAL_FALSO)
	//	if ((HoraAtualSec-HoraPartida) >= (AVL.TAtivaLinha*60))
	//	{
	//	  LinhaAtiva=VERDADEIRO;
	//	}

  	for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
  	{
		/* -- Converte numero de operacao da Cuba para indice na tabela -- */
		Cuba=ConvCubOperScore(CubaOpe);
		if (Cuba eq -1)
		  continue;

		/* Verifica se tem point feeder para esta Cuba */
		if (AVC.Param[Cuba].TemPF ne TEM_PF)
		  continue; /* nao tem PF, nao trata */

		/* Ativa Bit de comunicacao CLP New Soderberg */
		if (AVC.ParUser1[Cuba].AtivaBitCLP eq VERDADEIRO and EST_AVC(Cuba).Est.BitCLP eq FALSO)
		{
			ComandaSaidaRem(Cuba, LIGAR, 18, 0);
			EST_AVC(Cuba).Est.BitCLP = VERDADEIRO;
		} 
		
		/* Calcula resistencia filtrada */
		AVC.User1[Cuba].ResAlim= FiltroResAlim(Cuba);

		//	/* Verifica se alterou numero do algoritmo da Cuba on-line */
		//	if (AlterouNumAlgCtr(Cuba, ALG_SCORE02))
		//	{ /* -- selecionou ou desselecionou algoritmo do Score -- */
		//	  /* -- Inicializa variaveis do algoritmo do Alimentacao se este
		//            tiver sido selecionado -- */
		//	  if (AlgControle(Cuba,ALG_SCORE02) eq VERDADEIRO)
		//	    IniPFCuba(Cuba);
		//	}

	
		/* Calculo do intervalo de adicao de fluoreto do dia */
		if ( EST_AVC(Cuba).Est.TabelaAlF3 eq FALSO and 
			(AVC.ParUser1[Cuba].DataAlF3 + 43200) > AVL.Trab.HoraIniDia and 
			AVC.ParUser1[Cuba].AlF3Dia > 0 )
		{
			AVC.User2[Cuba].TotalAcionaAlF3 = (AVC.ParUser1[Cuba].AlF3Dia*1000) / ((AVC.ParUser1[Cuba].QuantAlF3Carga[0] + AVC.ParUser1[Cuba].QuantAlF3Carga[1])/2);
			if(AVC.User2[Cuba].TotalAcionaAlF3 > 0)
			{
				AVC.User2[Cuba].IntervAlF3 = AVC.ParUser1[Cuba].TIntAlF3 / (AVC.User2[Cuba].TotalAcionaAlF3+1);
				EST_AVC(Cuba).Est.TabelaAlF3 = VERDADEIRO;
			}
		}

		if(EST_AVC(Cuba).Est.TabelaAlF3 eq VERDADEIRO)
		{
			AVC.User2[Cuba].TotalAcionaAlF3 = ((AVC.ParUser1[Cuba].AlF3Dia*1000)-SUPERV_AVC(Cuba).Sup.ALF3Fornecido) / ((AVC.ParUser1[Cuba].QuantAlF3Carga[0] + AVC.ParUser1[Cuba].QuantAlF3Carga[1])/2);
			if(AVC.User2[Cuba].HoraUltAlF3 > (AVL.Trab.HoraIniDia + AVC.ParUser1[Cuba].HoraIniAlF3) and
				AVC.User2[Cuba].TotalAcionaAlF3 > 0)
			{
				AVC.User2[Cuba].IntervAlF3 = ((AVL.Trab.HoraIniDia + AVC.ParUser1[Cuba].HoraIniAlF3 + AVC.ParUser1[Cuba].TIntAlF3) - AVC.User2[Cuba].HoraUltAlF3) / (AVC.User2[Cuba].TotalAcionaAlF3+1);
			}
		}

		if(AVC.ParUser1[Cuba].NumSiloAlF3 eq 0)
		{
			EST_AVC(Cuba).Est.TabelaAlF3 = FALSO;
		}

    	/* Verifica se o operador passou a alimentacao para manual (campo) */
		/* Desativado New Soderberg *
		if (EstadoIO(Cuba, AVC.Abs[Cuba].BitDesCamOuPFAutoouM1) eq ALIMENTACAO_MANUAL) 
		{ 
			EST_AVC(Cuba).Est.ManualAlimLoc= VERDADEIRO;
		}
		else
		{ 
			EST_AVC(Cuba).Est.ManualAlimLoc= FALSO;
		}
		*/

		DEPURA(printf("McpPF->Trata Cuba %d [%d]\n",CubaOpe,Cuba));
		/* -- Verifica condicoes para tratamento da Cuba -- */
		if ( 
		//(AlgControle(Cuba,ALG_SCORE02) eq VERDADEIRO) and
		(EST_AVC(Cuba).ForaLeitura eq FALSO) and
		(EST_AVC(Cuba).RtuStatus eq FALSO) and
		(AVL.LinhaHabilitada eq VERDADEIRO))
		{
	  		if (EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL)
	  		{ 
				/* -- Nao alimenta Cuba desabilitada -- */
				if (AVC.ParUser1[Cuba].HabilitaPF eq VERDADEIRO)
				{ 
          			// Se acabou de habilitar point feeder, comecar check especial
          			if (AVC.User1[Cuba].HabilitaPFAnt ne VERDADEIRO)
          			{
            			/* -- Inicializa variaveis do algoritmo do Score -- */
	        			IniPFCuba(Cuba);
            			AVC.User1[Cuba].HabilitaPFAnt= VERDADEIRO;
					}
					
					// Inserido em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
					if (LinhaDesligada eq VAL_VERDADEIRO)
		  			{  // linha acabou de ser religada apos um desligamento
		    			if ((AVL.HoraAtivaLinha-AVL.HoraDesativaLinha) > AVC.ParUser1[Cuba].TSuspLinhaD)
						{ // Forca estado de alimentacao suspensa
			  				EST_AVC(Cuba).Est.AlimSuspensa = VERDADEIRO;
			  				// por tempo configurado em TSaiSuspLinhaD
			  				AVC.User1[Cuba].TempoSuspende=AVC.ParUser1[Cuba].TSaiSuspLinhaD;
			  				MudaEstadoAlim(Cuba,EST_ALIM_SUSPENSA,MUDA_CONTROLE);
						}
		  			}
					
					// Inserido em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
					do
					{
						/* Atualiza tempo do estado atual ( usado para ESTATISTICA ) */ 
						AVC.User1[Cuba].TempEstAtual +=  1L;
		    			/* Atualiza variaveis de supervisao */
						SupervPF(Cuba);
						AcionaFluoreto(Cuba);
			
						switch(EstadoAtual(Cuba))
						{
							case EST_ALIM_PADRAO:	/* -- normal -- */
								prox_estado=AlimPadrao(Cuba);
								break;

							case EST_ALIM_EA:	/* -- Efeito anodico -- */
								prox_estado=AlimEA(Cuba);
								break;

							case EST_ALIM_EXCECAO:
								prox_estado=AlimExcecao(Cuba);
								break;

							case EST_ALIM_SUSPENSA:
								prox_estado=AlimSuspensa(Cuba);
								break;

							default:
								{
								char aux_msg[50];

								sprintf(aux_msg,ScoreGetStr(SCORE_MSG_2024),
										EstadoAtual(Cuba));
								aux_msg[49]='0'; //restringe tamanho da string
								
								EmiteErroFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_ERR_11),
											CubaOpe,aux_msg);
								}
								break;
						}
			
						if(AVC.ParUser2[Cuba].HabExcUsuPF eq VERDADEIRO and 
							AVC.User1[Cuba].EstadoAlimAtual ne EST_ALIM_SUSPENSA)
						{
							if(AVC.User1[Cuba].EstadoAlimAtual ne EST_ALIM_EXCECAO)
								MudaEstadoAlim(Cuba,EST_ALIM_EXCECAO,MUDA_CONTROLE);
							else
							{
								if(AVC.User1[Cuba].State ne ALIM_EXC_USU)
								MudaEstadoSub(Cuba,ALIM_EXC_USU);  
							}
						}
						else
						{
							if (prox_estado ne -1)
								/* -- Muda para o novo estado -- */
								MudaEstadoAlim(Cuba,prox_estado,MUDA_CONTROLE);
						}

		  			}while(prox_estado ne -1);
				} //Finaliza (AVC.ParUser1[Cuba].HabilitaPF eq VERDADEIRO)
				
        		else // (AVC.ParUser1[Cuba].HabilitaPF eq FALSE)
        		{
					if (AVC.User1[Cuba].HabilitaPFAnt eq VERDADEIRO)
					{
						/* -- Inicializa variaveis do algoritmo do Score -- */
						AVC.User1[Cuba].HabilitaPFAnt= FALSO;
					}

		  			if(AVC.ParUser2[Cuba].HabilitaPFCBA eq VERDADEIRO)
		  			{
						if(AVC.User2[Cuba].HabilitaPFCBAAnt eq FALSO)
						{
							// Inicialização de variáveis PF CBA
							AVC.User1[Cuba].IntPar = 0; //Integral Parcial
							AVC.User1[Cuba].NumAciona = 0; //Número de Acionamentos do Point Feeder
							AVC.User3[Cuba].HoraEstAtual[2] = HoraAtualSec; //Hora de ínicio do estado de alimentação
							AVC.User2[Cuba].EstadoPFCBA = 2; //Basefeed
							AVC.User2[Cuba].TaxaFeedPF = 1.0; //Taxa de Alimentação PF
							AVC.User3[Cuba].CargaEst[2] = 0.0; //Carga atual do estado de alimentação
							AVC.User2[Cuba].DurEstadoAtual = AVC.ParUser2[Cuba].TMinBaseF * 60; //Duração programada do estado
							LiberaMoveAlim(Cuba); //Libera movimentação do anodo e reseta tempo de movimentação inibida
							AVC.User2[Cuba].HabilitaPFCBAAnt = VERDADEIRO; //Habilita PFCBA do para próximo ciclo
							GeraEvento(EV_PFCBA,Cuba,-1, AVC.User2[Cuba].EstadoPFCBA,
														AVC.User2[Cuba].EstFeedAnt, 
														(int)(AVC.User3[Cuba].TEstFeed[AVC.User2[Cuba].EstFeedAnt]/60),
														AVC.User3[Cuba].CargaEst[AVC.User2[Cuba].EstFeedAnt]);
							EST_AVC(Cuba).Est.AlarmeCheck = FALSO; //Zera alarme de check longo
						} //Finaliza if(AVC.User2[Cuba].HabilitaPFCBAAnt eq FALSO)

						else
						{
			  				switch(Prox_Estado(Cuba, AVC.User2[Cuba].EstadoPFCBA)) //Verifica se haverá transição de estado
			  				{

								case 0: // SUSPEA - Inibicao para espera de EA (Suspensão em Atraso)

									AVC.User1[Cuba].IntPar = 0;
									AVC.User3[Cuba].HoraEstAtual[0] = HoraAtualSec;
									AVC.User2[Cuba].EstadoPFCBA = 0;
									AVC.User2[Cuba].TaxaFeedPF = 0.0;
									LiberaMoveAlim(Cuba);
									AVC.User2[Cuba].DurEstadoAtual = 0;
									GeraEvento(EV_PFCBA,Cuba,-1, AVC.User2[Cuba].EstadoPFCBA, 
														AVC.User2[Cuba].EstFeedAnt, 
														(int)(AVC.User3[Cuba].TEstFeed[AVC.User2[Cuba].EstFeedAnt]/60),
														AVC.User3[Cuba].CargaEst[AVC.User2[Cuba].EstFeedAnt]);
									EST_AVC(Cuba).Est.AlarmeCheck = FALSO;
									AVC.User3[Cuba].CargaEst[0] = 0.0;
									AVC.User1[Cuba].NumAciona = 0;
									
									if(EST_AVC(Cuba).Est.TendenciaOver eq VERDADEIRO)
									{
										EST_AVC(Cuba).Est.TendenciaOver = FALSO;
										ComandaLampEa(Cuba, DESLIGAR);
									}

								break;

								case 1: // Suspensao temporaria
									AVC.User1[Cuba].IntPar = 0;
									AVC.User3[Cuba].HoraEstAtual[1] = HoraAtualSec;
									AVC.User2[Cuba].EstadoPFCBA = 1;
									AVC.User2[Cuba].TaxaFeedPF = -1.0;
									LiberaMoveAlim(Cuba);
									if(AVC.User1[Cuba].TempoSuspende > 0)
									{
										AVC.User2[Cuba].DurEstadoAtual = AVC.User1[Cuba].TempoSuspende;
										AVC.User1[Cuba].TempoSuspende = 0;
									}
									else
										AVC.User2[Cuba].DurEstadoAtual = AVC.ParUser2[Cuba].TSuspTemp * 60;
									
									GeraEvento(EV_PFCBA,Cuba,-1, AVC.User2[Cuba].EstadoPFCBA, 
															AVC.User2[Cuba].EstFeedAnt, 
															(int)(AVC.User3[Cuba].TEstFeed[AVC.User2[Cuba].EstFeedAnt]/60),
															AVC.User3[Cuba].CargaEst[AVC.User2[Cuba].EstFeedAnt]);
									
									EST_AVC(Cuba).Est.AlarmeCheck = FALSO;
									
									AVC.User3[Cuba].CargaEst[1] = 0.0;
									AVC.User1[Cuba].NumAciona = 0;

									if(EST_AVC(Cuba).Est.TendenciaOver eq VERDADEIRO)
									{
										EST_AVC(Cuba).Est.TendenciaOver = FALSO;
										ComandaLampEa(Cuba, DESLIGAR);
									}				
								break;

								case 2: //Basefeed
									AVC.User1[Cuba].IntPar = 0;
									AVC.User3[Cuba].HoraEstAtual[2] = HoraAtualSec;
									AVC.User2[Cuba].EstadoPFCBA = 2;
									AVC.User2[Cuba].TaxaFeedPF = 1.0;
									LiberaMoveAlim(Cuba);

									if(EST_AVC(Cuba).Est.ForcaEstAlim eq FALSO)
										AVC.User2[Cuba].DurEstadoAtual = AVC.ParUser2[Cuba].TMinBaseF * 60;
									else
									{
										AVC.User2[Cuba].DurEstadoAtual = AVC.User1[Cuba].TempoSuspende;
										EST_AVC(Cuba).Est.ForcaEstAlim = FALSO;
									}

									GeraEvento(EV_PFCBA,Cuba,-1, AVC.User2[Cuba].EstadoPFCBA, 
															AVC.User2[Cuba].EstFeedAnt, 
															(int)(AVC.User3[Cuba].TEstFeed[AVC.User2[Cuba].EstFeedAnt]/60),
															AVC.User3[Cuba].CargaEst[AVC.User2[Cuba].EstFeedAnt]);
									EST_AVC(Cuba).Est.AlarmeCheck = FALSO;
									AVC.User1[Cuba].NumAciona = 0;
									AVC.User3[Cuba].CargaEst[2] = 0.0;

									if(EST_AVC(Cuba).Est.TendenciaOver eq VERDADEIRO)
									{
										EST_AVC(Cuba).Est.TendenciaOver = FALSO;
										ComandaLampEa(Cuba, DESLIGAR);
									}
								break;

								case 3: //Overfeed
									AVC.User1[Cuba].IntPar = 0;
									AVC.User3[Cuba].HoraEstAtual[3] = HoraAtualSec;
									AVC.User2[Cuba].EstadoPFCBA = 3;
									AVC.User3[Cuba].ContCicOver = 0;
									EST_AVC(Cuba).Est.TendOverCancela = FALSO;
									EST_AVC(Cuba).InibeControleAlim = VERDADEIRO; //Desabilita movimentação do anodo
									
									if(EST_AVC(Cuba).Corrida eq VERDADEIRO or EST_AVC(Cuba).Est.ChaveMCruzeiro eq VERDADEIRO)
									{
										AVC.User2[Cuba].TaxaFeedPF = AVC.ParUser2[Cuba].TaxaOverB;

										if(EST_AVC(Cuba).Est.ForcaEstAlim eq FALSO)
											AVC.User2[Cuba].DurEstadoAtual = AVC.ParUser2[Cuba].TOverCorr * 60;
										else
										{
											AVC.User2[Cuba].DurEstadoAtual = AVC.User1[Cuba].TempoSuspende;
											EST_AVC(Cuba).Est.ForcaEstAlim = FALSO;
										}
									}
									else
									{
										if(AVC.ParUser2[Cuba].SOverInicial eq VERDADEIRO)
											AVC.User2[Cuba].TaxaFeedPF = AVC.ParUser2[Cuba].TaxaOverA; //2,5
										else
											AVC.User2[Cuba].TaxaFeedPF = AVC.ParUser2[Cuba].TaxaOverB; //1,3

										if(EST_AVC(Cuba).Est.ForcaEstAlim eq FALSO)
											AVC.User2[Cuba].DurEstadoAtual = AVC.ParUser2[Cuba].TOverF * 60;
										else
										{
											AVC.User2[Cuba].DurEstadoAtual = AVC.User1[Cuba].TempoSuspende;
											EST_AVC(Cuba).Est.ForcaEstAlim = FALSO;
										}
									}
									AVC.User1[Cuba].TempoSuspende = 0;

									GeraEvento(EV_PFCBA,Cuba,-1, AVC.User2[Cuba].EstadoPFCBA, 
															AVC.User2[Cuba].EstFeedAnt, 
															(int)(AVC.User3[Cuba].TEstFeed[AVC.User2[Cuba].EstFeedAnt]/60),
															AVC.User3[Cuba].CargaEst[AVC.User2[Cuba].EstFeedAnt]);
									EST_AVC(Cuba).Est.AlarmeCheck = FALSO;
									AVC.User3[Cuba].CargaEst[3] = 0.0;
									AVC.User1[Cuba].NumAciona = 0;

									if(EST_AVC(Cuba).Est.TendenciaOver eq VERDADEIRO)
									{
										EST_AVC(Cuba).Est.TendenciaOver = FALSO;
										ComandaLampEa(Cuba, DESLIGAR);
									}
								break;

								case 4: //Underfeed A
									AVC.User1[Cuba].IntPar = 0;
									AVC.User3[Cuba].HoraEstAtual[4] = HoraAtualSec;
									AVC.User2[Cuba].EstadoPFCBA = 4;
									AVC.User2[Cuba].TaxaFeedPF = AVC.ParUser2[Cuba].TaxaUnderA; //0,50
									LiberaMoveAlim(Cuba);
									AVC.User2[Cuba].DurEstadoAtual = AVC.ParUser2[Cuba].TMaxUnderA * 60; //90 min
									if(AVC.User2[Cuba].EstFeedAnt ne 3)
									{
										AVC.User2[Cuba].ResInicialUnder = 0.0;
									}
									else
									{
										AVC.User2[Cuba].ResInicialUnder = AVC.CcontMcp[Cuba].RCicContlBruta;
									}
									//AVC.User2[Cuba].ResInicialUnder = 1.0;
									GeraEvento(EV_PFCBA,Cuba,-1, AVC.User2[Cuba].EstadoPFCBA, 
															AVC.User2[Cuba].EstFeedAnt, 
															(int)(AVC.User3[Cuba].TEstFeed[AVC.User2[Cuba].EstFeedAnt]/60),
															AVC.User3[Cuba].CargaEst[AVC.User2[Cuba].EstFeedAnt]);
									EST_AVC(Cuba).Est.AlarmeCheck = FALSO;
									AVC.User1[Cuba].NumAciona = 0;
									AVC.User3[Cuba].CargaEst[4] = 0.0;

									if(EST_AVC(Cuba).Est.TendenciaOver eq VERDADEIRO)
									{
										EST_AVC(Cuba).Est.TendenciaOver = FALSO;
										ComandaLampEa(Cuba, DESLIGAR);
									}
								break;

								case 5: //Underfeed B
									AVC.User1[Cuba].IntPar = 0;
									AVC.User3[Cuba].HoraEstAtual[5] = HoraAtualSec;
									AVC.User2[Cuba].EstadoPFCBA = 5;
									AVC.User2[Cuba].TaxaFeedPF = AVC.ParUser2[Cuba].TaxaUnderB;
									EST_AVC(Cuba).InibeControleAlim = DESAB_MOV_BAIXO;
									AVC.User2[Cuba].DurEstadoAtual = AVC.ParUser2[Cuba].TMaxUnderB * 60;
									if(AVC.User2[Cuba].ResInicialUnder eq 1.0)
										AVC.User2[Cuba].ResInicialUnder = 0.0;

									GeraEvento(EV_PFCBA,Cuba,-1, AVC.User2[Cuba].EstadoPFCBA, 
															AVC.User2[Cuba].EstFeedAnt, 
															(int)(AVC.User3[Cuba].TEstFeed[AVC.User2[Cuba].EstFeedAnt]/60),
															AVC.User3[Cuba].CargaEst[AVC.User2[Cuba].EstFeedAnt]);
									EST_AVC(Cuba).Est.AlarmeCheck = FALSO;
									AVC.User1[Cuba].NumAciona = 0;
									AVC.User3[Cuba].CargaEst[5] = 0.0;

									if(EST_AVC(Cuba).Est.TendenciaOver eq VERDADEIRO)
									{
										EST_AVC(Cuba).Est.TendenciaOver = FALSO;
										ComandaLampEa(Cuba, DESLIGAR);
									}
								break;

								case 6: //Check
									AVC.User1[Cuba].IntPar = 0;
									AVC.User3[Cuba].HoraEstAtual[6] = HoraAtualSec;
									AVC.User2[Cuba].EstadoPFCBA = 6;
									AVC.User2[Cuba].TaxaFeedPF = -2.0;
									EST_AVC(Cuba).InibeControleAlim = DESAB_MOV_BAIXO;
									AVC.User2[Cuba].ResMinCheck = 1.0;
									GeraEvento(EV_PFCBA,Cuba,-1, AVC.User2[Cuba].EstadoPFCBA, 
															AVC.User2[Cuba].EstFeedAnt, 
															(int)(AVC.User3[Cuba].TEstFeed[AVC.User2[Cuba].EstFeedAnt]/60),
															AVC.User3[Cuba].CargaEst[AVC.User2[Cuba].EstFeedAnt]);
									EST_AVC(Cuba).Est.AlarmeCheck = FALSO;
									AVC.User1[Cuba].NumAciona = 0;
									AVC.User3[Cuba].CargaEst[6] = 0.0;

									if(EST_AVC(Cuba).Est.TendenciaOver eq VERDADEIRO)
									{
										EST_AVC(Cuba).Est.TendenciaOver = FALSO;
										ComandaLampEa(Cuba, DESLIGAR);
									}
								break;

								case 7: //OverAEK
									AVC.User1[Cuba].IntPar = 0;
									AVC.User3[Cuba].HoraEstAtual[7] = HoraAtualSec;
									AVC.User2[Cuba].EstadoPFCBA = 7;
									AVC.User2[Cuba].TaxaFeedPF = 0.0;
									AVC.User2[Cuba].DurEstadoAtual = AVC.ParUser2[Cuba].TMinOverEA * 60;
									LiberaMoveAlim(Cuba);
									GeraEvento(EV_PFCBA,Cuba,-1, AVC.User2[Cuba].EstadoPFCBA, 
															AVC.User2[Cuba].EstFeedAnt, 
															(int)(AVC.User3[Cuba].TEstFeed[AVC.User2[Cuba].EstFeedAnt]/60),
															AVC.User3[Cuba].CargaEst[AVC.User2[Cuba].EstFeedAnt]);
									EST_AVC(Cuba).Est.AlarmeCheck = FALSO;
									AVC.User1[Cuba].NumAciona = 0;
									AVC.User3[Cuba].CargaEst[7] = 0.0;

									if(EST_AVC(Cuba).Est.TendenciaOver eq VERDADEIRO)
									{
										EST_AVC(Cuba).Est.TendenciaOver = FALSO;
										ComandaLampEa(Cuba, DESLIGAR);
									}
								break;

			  				} //Finaliza switch(Prox_Estado(Cuba, AVC.User2[Cuba].EstadoPFCBA))

			  				VerificaAlim(Cuba);

						} //Finaliza if(AVC.User2[Cuba].HabilitaPFCBAAnt eq TRUE)

		  			} //Finaliza if(AVC.ParUser2[Cuba].HabilitaPFCBA eq VERDADEIRO)
					else // (AVC.ParUser2[Cuba].HabilitaPFCBA eq FALSE)
					{
						AVC.User2[Cuba].HabilitaPFCBAAnt = FALSO;
						EST_AVC(Cuba).InibeControleAlim = HABILITA_MOVE;
					}
        		}
	  		}
		}

  	} /* -- for -- Finaliza for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++) */

	/* guarda corrente instantanea para proximo ciclo */
	IinstOld=AVL.Iinst;

	#ifndef ATIVA_SIMULACAO
		LiberaSemaf(SEMAF_AVC);
		LiberaSemaf(SEMAF_SUPERV_AVC);
		LiberaSemaf(SEMAF_HIST_TURNO);
	#endif

} /* -- ProcessaCubas -- */

/*
-------------------------------------------------------------------------------
  Prox_Estado - Verifica se havera transicao de estado 
-------------------------------------------------------------------------------
*/
int Prox_Estado(int Cuba, int EstadoAtual)
{
	int EstAtual;
	EstAtual = EstadoAtual;
	
	//Operador sinalizou força estado de alimentacao para Overfeed
	if(EST_AVC(Cuba).Est.ForcaEstAlim eq VERDADEIRO and
		 EST_AVC(Cuba).Ea eq FALSO and
	 	AVC.User3[Cuba].EstForcaAlim eq 3)
	{
		AVC.User3[Cuba].TEstFeed[EstadoAtual] = HoraAtualSec - AVC.User3[Cuba].HoraEstAtual[EstadoAtual];
		AVC.User2[Cuba].EstFeedAnt = EstadoAtual;
		return AVC.User3[Cuba].EstForcaAlim; //OVERFEED
  	}
	 
	//Operador sinalizou Alimentacao SUSPENSA
	if(EST_AVC(Cuba).Est.AlimSuspensa eq VERDADEIRO and
		 EstadoAtual ne 0)
  	{
		EST_AVC(Cuba).Est.AlimSuspensa = FALSO;
		AVC.User3[Cuba].TEstFeed[EstadoAtual] = HoraAtualSec - AVC.User3[Cuba].HoraEstAtual[EstadoAtual];
		AVC.User2[Cuba].EstFeedAnt = EstadoAtual;
		if(AVC.User1[Cuba].TempoSuspende > 0)
			return 1; //SUSPTEMP
		else
			return 0; //SUSPEA
	}

  	//Operador sinalizou CHECK
	if(EST_AVC(Cuba).Est.AlimCheck eq VERDADEIRO and
		EstadoAtual ne 6 and
		EST_AVC(Cuba).Corrida eq FALSO)
  	{
		EST_AVC(Cuba).Est.AlimCheck = FALSO;
		AVC.User3[Cuba].TEstFeed[EstadoAtual] = HoraAtualSec - AVC.User3[Cuba].HoraEstAtual[EstadoAtual];
		AVC.User2[Cuba].EstFeedAnt = EstadoAtual;
		return 6; //CHECK
  	}

	//Efeito Anodico
	if(EST_AVC(Cuba).Ea eq VERDADEIRO)
	{
		if(AVC.ParUser2[Cuba].HabAEKPF eq VERDADEIRO)
			//OverAEK
			EstAtual = 7; //OVER AEK
		else
			//SUSPEA
			EstAtual = 0; //SUSPEA
	}

	//Corrida ou Manobra de Cruzeiro -> OverFeed
	if((EST_AVC(Cuba).Corrida eq VERDADEIRO or EST_AVC(Cuba).Est.ChaveMCruzeiro eq VERDADEIRO) and
			(EstadoAtual ne 3 and EstadoAtual ne 0 and EstadoAtual ne 1))
	{
		AVC.User3[Cuba].TEstFeed[EstadoAtual] = HoraAtualSec - AVC.User3[Cuba].HoraEstAtual[EstadoAtual];
		AVC.User2[Cuba].EstFeedAnt = EstadoAtual;
		return 3; //OVERFEED
	}

	//Quebrada -> SUSPTEMP
	if(EST_AVC(Cuba).Quebrada eq VERDADEIRO and 
		(AVC.Cleit[Cuba].HoraUltQueb + 10) > HoraAtualSec and
		EST_AVC(Cuba).Ea eq FALSO and
		EstadoAtual ne 1 and
		EstadoAtual ne 0)
	{
		AVC.User2[Cuba].EstFeedAnt = EstadoAtual;
		AVC.User3[Cuba].TEstFeed[EstadoAtual] = HoraAtualSec - AVC.User3[Cuba].HoraEstAtual[EstadoAtual];
		return 1; //SUSPTEMP
	}

	//Tempo maximo de espera de EA ate entrar em alimentacao SUSPENSA	
	if ((HoraAtualSec-AVC.Ea[Cuba].EaHoraInicio)>(AVC.ParUser1[Cuba].MaxIntervEa*60) and
			EstadoAtual ne 0)
	{
		AVC.User2[Cuba].EstFeedAnt = EstadoAtual;
		AVC.User3[Cuba].TEstFeed[EstadoAtual] = HoraAtualSec - AVC.User3[Cuba].HoraEstAtual[EstadoAtual];
		return 0; //SUSPEA
	}

	switch(EstAtual)
	{
		case 0: //SUSPEA
		if(EST_AVC(Cuba).Ea eq VERDADEIRO)
		{
			AVC.User3[Cuba].TEstFeed[EstadoAtual] = HoraAtualSec - AVC.User3[Cuba].HoraEstAtual[EstadoAtual];
			AVC.User2[Cuba].EstFeedAnt = EstadoAtual;
			if(AVC.ParUser2[Cuba].SuspEA eq VERDADEIRO and EstadoAtual ne 1)
				return 1; //SUSPTEMP
			else if(EstadoAtual ne 3 and AVC.ParUser2[Cuba].SuspEA eq FALSO)
				return 3; //OVERFEED
		}
		break;
		
		case 1: //SUSPTEMP
		if(AVC.User3[Cuba].HoraEstAtual[EstadoAtual] + AVC.User2[Cuba].DurEstadoAtual <= HoraAtualSec) 
		{
			AVC.User3[Cuba].TEstFeed[EstadoAtual] = HoraAtualSec - AVC.User3[Cuba].HoraEstAtual[EstadoAtual];
			AVC.User2[Cuba].EstFeedAnt = EstadoAtual;
			//AVC.User2[Cuba].ResInicialUnder = AVC.CcontMcp[Cuba].RCicContlBruta;
			return 4; //UNDERFEED A
		}
		break;

		case 2: //BASEFEED
		if((AVC.User3[Cuba].HoraEstAtual[EstadoAtual] + AVC.User2[Cuba].DurEstadoAtual <= HoraAtualSec) and
			(AVC.CcontMcp[Cuba].RCicContlBruta >= (AVC.Ccont[Cuba].RAlvo - AVC.Param[Cuba].BandaMortaInf)) and
			(AVC.CcontMcp[Cuba].RCicContlBruta <= (AVC.Ccont[Cuba].RAlvo + AVC.Param[Cuba].BandaMortaSup)) and
			AVC.User1[Cuba].TipoOscil eq 0 and EST_AVC(Cuba).Est.Oscilacao eq FALSO)
		{
			AVC.User3[Cuba].TEstFeed[EstadoAtual] = HoraAtualSec - AVC.User3[Cuba].HoraEstAtual[EstadoAtual];
			AVC.User2[Cuba].EstFeedAnt = EstadoAtual;
			return 3; //OVERFEED
		}
		break;

		case 3: //OVERFEED
		if(AVC.User3[Cuba].HoraEstAtual[EstadoAtual] + AVC.User2[Cuba].DurEstadoAtual <= HoraAtualSec)
		{
			EST_AVC(Cuba).Est.TendenciaOver = FALSO;

			SUPERV_AVC(Cuba).Sup.PicoOver += AVC.CcontMcp[Cuba].RCicContlBruta - AVC.Ccont[Cuba].RAlvo;
			SUPERV_AVC_TURNO(Cuba).Sup.PicoOver += AVC.CcontMcp[Cuba].RCicContlBruta - AVC.Ccont[Cuba].RAlvo;
			SUPERV_AVC(Cuba).Sup.NOverDia++;
			SUPERV_AVC_TURNO(Cuba).Sup.NOverDia++;
			
			if(EST_AVC(Cuba).Est.ForcaEstAlim eq VERDADEIRO and
			EST_AVC(Cuba).Ea eq FALSO and
			AVC.User3[Cuba].EstForcaAlim eq 2)
			{
				AVC.User3[Cuba].TEstFeed[EstadoAtual] = HoraAtualSec - AVC.User3[Cuba].HoraEstAtual[EstadoAtual];
				AVC.User2[Cuba].EstFeedAnt = EstadoAtual;
				return AVC.User3[Cuba].EstForcaAlim; //BASEFEED
			}
			else
			{
				AVC.User3[Cuba].TEstFeed[EstadoAtual] = HoraAtualSec - AVC.User3[Cuba].HoraEstAtual[EstadoAtual];
				AVC.User2[Cuba].EstFeedAnt = EstadoAtual;
				return 4; //UNDERFEED A
			}
		}
		else if(AVC.User1[Cuba].TipoOscil eq 2)
		{
			AVC.User3[Cuba].TEstFeed[EstadoAtual] = HoraAtualSec - AVC.User3[Cuba].HoraEstAtual[EstadoAtual];
			AVC.User2[Cuba].EstFeedAnt = EstadoAtual;
			return 2; //BASEFEED
		}
		break;

		case 4: //UNDERFEED A
		if(AVC.User3[Cuba].HoraEstAtual[EstadoAtual] + AVC.User2[Cuba].DurEstadoAtual <= HoraAtualSec)
		{
			AVC.User3[Cuba].TEstFeed[EstadoAtual] = HoraAtualSec - AVC.User3[Cuba].HoraEstAtual[EstadoAtual];
			AVC.User2[Cuba].EstFeedAnt = EstadoAtual;
			return 5; //UNDERFEED B
		}
		else if(AVC.User1[Cuba].TipoOscil eq 2)
		{
			AVC.User3[Cuba].TEstFeed[EstadoAtual] = HoraAtualSec - AVC.User3[Cuba].HoraEstAtual[EstadoAtual];
			AVC.User2[Cuba].EstFeedAnt = EstadoAtual;
			return 2; //BASEFEED
		}
		else if((AVC.User2[Cuba].CoefAng >= AVC.ParUser2[Cuba].CAFimUnder and
			AVC.User2[Cuba].CoefCor >= AVC.ParUser2[Cuba].CCFimUnder and
			AVC.CcontMcp[Cuba].RCicContlBruta >= (AVC.Ccont[Cuba].RAlvo - AVC.Param[Cuba].BandaMortaInf)) and
			(AVC.CcontMcp[Cuba].RCicContlBruta >= AVC.User2[Cuba].ResInicialUnder + AVC.ParUser2[Cuba].DifResFimUnder))
		{

			SUPERV_AVC(Cuba).Sup.PicoUnder += AVC.CcontMcp[Cuba].RCicContlBruta - AVC.Ccont[Cuba].RAlvo;
			SUPERV_AVC_TURNO(Cuba).Sup.PicoUnder += AVC.CcontMcp[Cuba].RCicContlBruta - AVC.Ccont[Cuba].RAlvo;
			SUPERV_AVC(Cuba).Sup.NUnderDia++;
			SUPERV_AVC_TURNO(Cuba).Sup.NUnderDia++;

			AVC.User3[Cuba].TEstFeed[EstadoAtual] = HoraAtualSec - AVC.User3[Cuba].HoraEstAtual[EstadoAtual];
			AVC.User2[Cuba].EstFeedAnt = EstadoAtual;

			SUPERV_AVC(Cuba).Sup.TempoUnder += AVC.User3[Cuba].TEstFeed[EstadoAtual];
			SUPERV_AVC_TURNO(Cuba).Sup.TempoUnder += AVC.User3[Cuba].TEstFeed[EstadoAtual];

			return 3; //OVERFEED
		}
		break;

		case 5: //UNDERFEED B
		if(AVC.User3[Cuba].HoraEstAtual[EstadoAtual] + AVC.User2[Cuba].DurEstadoAtual <= HoraAtualSec)
		{
			AVC.User3[Cuba].TEstFeed[EstadoAtual] = HoraAtualSec - AVC.User3[Cuba].HoraEstAtual[EstadoAtual];
			AVC.User2[Cuba].EstFeedAnt = EstadoAtual;
			return 6; //CHECK
		}
		else if(AVC.User1[Cuba].TipoOscil eq 2)
		{
			AVC.User3[Cuba].TEstFeed[EstadoAtual] = HoraAtualSec - AVC.User3[Cuba].HoraEstAtual[EstadoAtual];
			AVC.User2[Cuba].EstFeedAnt = EstadoAtual;
			return 2; //BASEFEED
		}
		else if((AVC.User2[Cuba].CoefAng >= AVC.ParUser2[Cuba].CAFimUnder and
			AVC.User2[Cuba].CoefCor >= AVC.ParUser2[Cuba].CCFimUnder and
			AVC.CcontMcp[Cuba].RCicContlBruta >= (AVC.Ccont[Cuba].RAlvo - AVC.Param[Cuba].BandaMortaInf)))
			// (AVC.CcontMcp[Cuba].RCicContlBruta >= AVC.User2[Cuba].ResInicialUnder + AVC.ParUser2[Cuba].DifResFimUnder))
		{
			SUPERV_AVC(Cuba).Sup.PicoUnder += AVC.CcontMcp[Cuba].RCicContlBruta - AVC.Ccont[Cuba].RAlvo;
			SUPERV_AVC_TURNO(Cuba).Sup.PicoUnder += AVC.CcontMcp[Cuba].RCicContlBruta - AVC.Ccont[Cuba].RAlvo;
			SUPERV_AVC(Cuba).Sup.NUnderDia++;
			SUPERV_AVC_TURNO(Cuba).Sup.NUnderDia++;

			AVC.User3[Cuba].TEstFeed[EstadoAtual] = HoraAtualSec - AVC.User3[Cuba].HoraEstAtual[EstadoAtual];
			AVC.User2[Cuba].EstFeedAnt = EstadoAtual;

			SUPERV_AVC(Cuba).Sup.TempoUnder += AVC.User3[Cuba].TEstFeed[EstadoAtual] + AVC.User3[Cuba].TEstFeed[4];
			SUPERV_AVC_TURNO(Cuba).Sup.TempoUnder += AVC.User3[Cuba].TEstFeed[EstadoAtual] + AVC.User3[Cuba].TEstFeed[4];

			return 3; //OVERFEED
		}
		break;

		case 6: //CHECK
		// if((AVC.CcontMcp[Cuba].RCicContlBruta - AVC.User2[Cuba].ResMinCheck) >=
		//		AVC.ParUser2[Cuba].DeltaRFimCheck)
		if((AVC.User2[Cuba].CoefAng >= AVC.ParUser2[Cuba].CAFimUnder and
			AVC.User2[Cuba].CoefCor >= AVC.ParUser2[Cuba].CCFimUnder and
			AVC.CcontMcp[Cuba].RCicContlBruta >= (AVC.Ccont[Cuba].RAlvo - AVC.Param[Cuba].BandaMortaInf))) 
			//(AVC.CcontMcp[Cuba].RCicContlBruta >= AVC.User2[Cuba].ResInicialUnder + AVC.ParUser2[Cuba].DifResFimUnder))
		{
			SUPERV_AVC(Cuba).Sup.PicoUnder += AVC.CcontMcp[Cuba].RCicContlBruta - AVC.Ccont[Cuba].RAlvo;
			SUPERV_AVC_TURNO(Cuba).Sup.PicoUnder += AVC.CcontMcp[Cuba].RCicContlBruta - AVC.Ccont[Cuba].RAlvo;
			SUPERV_AVC(Cuba).Sup.NUnderDia++;
			SUPERV_AVC_TURNO(Cuba).Sup.NUnderDia++;

			AVC.User3[Cuba].TEstFeed[EstadoAtual] = HoraAtualSec - AVC.User3[Cuba].HoraEstAtual[EstadoAtual];
			AVC.User2[Cuba].EstFeedAnt = EstadoAtual;

			SUPERV_AVC(Cuba).Sup.TempoUnder += AVC.User3[Cuba].TEstFeed[EstadoAtual] + 
												AVC.User3[Cuba].TEstFeed[4] + 
												AVC.User3[Cuba].TEstFeed[5];
			SUPERV_AVC_TURNO(Cuba).Sup.TempoUnder += AVC.User3[Cuba].TEstFeed[EstadoAtual] + 
													AVC.User3[Cuba].TEstFeed[4] + 
													AVC.User3[Cuba].TEstFeed[5];

			return 3; //OVERFEED
		}
		else if(AVC.User1[Cuba].TipoOscil eq 2)
		{
			AVC.User3[Cuba].TEstFeed[EstadoAtual] = HoraAtualSec - AVC.User3[Cuba].HoraEstAtual[EstadoAtual];
			AVC.User2[Cuba].EstFeedAnt = EstadoAtual;
			return 2; //BASEFEED
		}
		break;

		case 7: //OVERAEK
		if(EST_AVC(Cuba).Ea eq VERDADEIRO and EstadoAtual ne 7) //AEK
		{
			AVC.User3[Cuba].TEstFeed[EstadoAtual] = HoraAtualSec - AVC.User3[Cuba].HoraEstAtual[EstadoAtual];
			AVC.User2[Cuba].EstFeedAnt = EstadoAtual;
			return 7; //OVERAEK
		}
		if(EST_AVC(Cuba).Ea eq FALSO and EstadoAtual eq 7) //Terminou AEK
		{
			if(AVC.User3[Cuba].HoraEstAtual[EstadoAtual] + AVC.User2[Cuba].DurEstadoAtual <= HoraAtualSec)
			{
				AVC.User3[Cuba].TEstFeed[EstadoAtual] = HoraAtualSec - AVC.User3[Cuba].HoraEstAtual[EstadoAtual];
				AVC.User2[Cuba].EstFeedAnt = EstadoAtual;
				return 2; //BASEFEED
			}
		}
		break;
	}

	return -1;
}

/*
-------------------------------------------------------------------------------
  VerificaAlim - Funcao para verificar a hora de alimentacao e checar excecoes
-------------------------------------------------------------------------------
*/
void VerificaAlim(int Cuba)
{
	float interv_aux;
	
	ComumEstados(Cuba); //Definido em PFRot - Biblioteca de Funções PF
	
	if(EST_AVC(Cuba).Est.ManualAlimRem eq FALSO) //ManualAlimRem=FALSO (ALIMENT_AUTOMATICA) , ManualAlimRem=VERDADEIRO (ALIMENT_MANUAL)
		AcionaFluoreto(Cuba); 

	if(AVC.User2[Cuba].TaxaFeedPF > 0 and EST_AVC(Cuba).Est.ManualAlimRem eq FALSO)
	{
		interv_aux = AVC.User1[Cuba].IntervCurr/(AVC.User2[Cuba].TaxaFeedPF * AVC.User3[Cuba].FatorFeedRate);

		/* Verifica se e' hora de acionar o Point Feeder */
		if ((AVC.User1[Cuba].IntPar >= interv_aux) and
			((HoraAtualSec-AVC.User1[Cuba].HoraUltPF) >= AVC.ParUser1[Cuba].MinIntervPF))
		{
			/* Reseta valor da integral parcial */
			AVC.User1[Cuba].IntPar -= interv_aux;

			/* Comanda acionamento do point feeder */
			TrataAcionaPF(Cuba);
		}
	}
  
	switch(AVC.User2[Cuba].EstadoPFCBA)
	{
		case 0: //SUSPEA
			break;

		case 1: //SUSPTEMP
			break;

		case 2: // BASEFEED
			break;

		case 3: // OVERFEED
			if(AVC.ParUser2[Cuba].SOverInicial eq VERDADEIRO and 
				(AVC.User3[Cuba].HoraEstAtual[AVC.User2[Cuba].EstadoPFCBA] + 
				(AVC.ParUser2[Cuba].TSOverInicial*60)) <= HoraAtualSec and
				AVC.User2[Cuba].TaxaFeedPF ne AVC.ParUser2[Cuba].TaxaOverB)
			{
				AVC.User1[Cuba].IntPar = 0;
				AVC.User2[Cuba].TaxaFeedPF = AVC.ParUser2[Cuba].TaxaOverB;
			}
			
			if((AVC.User3[Cuba].HoraEstAtual[AVC.User2[Cuba].EstadoPFCBA] +
				(AVC.ParUser2[Cuba].TLibAlarmeOver*60)) <= HoraAtualSec)
			{
				if(AVC.User3[Cuba].TendResOver > AVC.ParUser2[Cuba].TendMaxOver and
					EST_AVC(Cuba).Est.TendenciaOver eq FALSO and
					EST_AVC(Cuba).Est.TendOverCancela eq FALSO)
				{
					EST_AVC(Cuba).Est.TendenciaOver = VERDADEIRO;
					GeraEvento(EV_TENDOVER,Cuba,-1, AVC.User3[Cuba].TendResOver*1e9);
					SUPERV_AVC(Cuba).Sup.NumTendOverDia++;
					SUPERV_AVC_TURNO(Cuba).Sup.NumTendOverDia++;
					ComandaLampEa(Cuba, PISCAR);
					//Movimentação 1MoveCima com Dur 3seg (parametrizados)
				}
			}
			else
			{
				if(EST_AVC(Cuba).Est.TendenciaOver eq VERDADEIRO)
				{
					EST_AVC(Cuba).Est.TendenciaOver = FALSO;
					ComandaLampEa(Cuba, DESLIGAR);
				}
			}

			if((AVC.User3[Cuba].HoraEstAtual[AVC.User2[Cuba].EstadoPFCBA] + 
				(AVC.ParUser2[Cuba].TLibMovOver*60)) <= HoraAtualSec)
			{
				LiberaMoveAlim(Cuba);
			}			
			break;
		
		case 4: // UNDERFEED A
			if((AVC.User3[Cuba].HoraEstAtual[AVC.User2[Cuba].EstadoPFCBA] + 
				(AVC.ParUser2[Cuba].TInibMovUnder*60)) <= HoraAtualSec and
				EST_AVC(Cuba).InibeControleAlim ne DESAB_MOV_BAIXO)
			{
				if(AVC.CcontMcp[Cuba].RCicContlBruta >= (AVC.Ccont[Cuba].RAlvo - AVC.Param[Cuba].BandaMortaInf) and
					AVC.CcontMcp[Cuba].RCicContlBruta <= (AVC.Ccont[Cuba].RAlvo + AVC.Param[Cuba].BandaMortaSup))
				{
					EST_AVC(Cuba).InibeControleAlim = DESAB_MOV_BAIXO;
					if(AVC.User2[Cuba].EstFeedAnt eq 3)
						AVC.User2[Cuba].ResInicialUnder = AVC.CcontMcp[Cuba].RCicContlBruta;
				}
			}
			if(EST_AVC(Cuba).Corrida eq VERDADEIRO or
					EST_AVC(Cuba).TrataTPinos eq VERDADEIRO)
				AVC.User2[Cuba].ResInicialUnder = 0.0;
			break;
			
			case 5: // UNDERFEED B
				if((AVC.User3[Cuba].HoraEstAtual[AVC.User2[Cuba].EstadoPFCBA] + 
					(AVC.ParUser2[Cuba].TLibMovUnderB*60)) <= HoraAtualSec)
				{
					LiberaMoveAlim(Cuba);
				}
				break;
		
		case 6: // CHECK
			if(AVC.CcontMcp[Cuba].RCicContlBruta < AVC.User2[Cuba].ResMinCheck)
				AVC.User2[Cuba].ResMinCheck = AVC.CcontMcp[Cuba].RCicContlBruta;

			if((AVC.User3[Cuba].HoraEstAtual[AVC.User2[Cuba].EstadoPFCBA] +
				(AVC.ParUser2[Cuba].TAlarmeCheck*60)) <= HoraAtualSec and
				EST_AVC(Cuba).Est.AlarmeCheck eq FALSO)
			{
				EST_AVC(Cuba).Est.AlarmeCheck = VERDADEIRO;
			}	
			break;

		case 7: // OVER AEK
			if((AVC.User3[Cuba].HoraEstAtual[AVC.User2[Cuba].EstadoPFCBA] +
				(AVC.ParUser2[Cuba].TIniAlimAEK)) <= HoraAtualSec)
			{
				AVC.User2[Cuba].TaxaFeedPF = AVC.ParUser2[Cuba].TaxaOverAEK;
			}	
			break;
	}
  
  /* Atualiza variaveis de supervisao */
  SupervPF(Cuba);

}

/*
-------------------------------------------------------------------------------
  TrataAcionaPF - Executa a ativacao dos point feeders na cadencia indicada
				  em AVC.ParUser1[Cuba].FreqAtiva.
-------------------------------------------------------------------------------
*/
void TrataAcionaPF(int Cuba)
{
  byte Falha;
  
  if(EST_AVC(Cuba).Est.AlimAl2O3 eq FALSO and
	  EST_AVC(Cuba).Est.AlimAlF3 eq FALSO)
  {

    /* Comando para remota ativa PF */
    //Falha= AcionaPF(Cuba);
    Falha= AcionaPFCBA(Cuba);

    /* Verifica se houve falha no acionamento do PFeeder */
    if (Falha == STATUS_OK)
    {
      /* So' faz contabilidade caso nao tenha ocorrido falha no acionamento */
  
    }	/* if */
  }
}

/*
-------------------------------------------------------------------------------
  AcionaPF - Funcao para simular o acionamento do point feeder na remota
-------------------------------------------------------------------------------
*/
byte AcionaPF(int Cuba)
{

  short int	Falha;

DEPURA(printf("Acionando point feeder, Cuba %d \n", ConvCubScoreOper(Cuba));)
  if ((Falha=ComandaAlimRem(Cuba, 0, 0)) ne STATUS_OK)
  { 
	if (Falha ne ERRO_ALIMENTACAO)
	  EmiteAlarmeFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_ERR_11),
				 ConvCubScoreOper(Cuba),ScoreGetStr(SCORE_MSG_2025));
	else
	  EmiteAlarmeFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_ERR_11),
				 ConvCubScoreOper(Cuba),"Todos alimentadores desabilitados.");
  } 

#ifndef ATIVA_SIMULACAO
  return(Falha);
#else
  return(STATUS_OK);
#endif  
}

/*
-------------------------------------------------------------------------------
  AcionaPFCBA - Funcao para simular o acionamento do point feeder na remota do
				new Soderberg CBA
-------------------------------------------------------------------------------
*/
byte AcionaPFCBA(int Cuba)
{

  short int	Falha;
  byte LadoPF, Seq;

  DEPURA(printf("Acionando point feeder, Cuba %d \n", ConvCubScoreOper(Cuba));)
  if(EST_AVC(Cuba).Est.LadoProxPF eq 0)
  {
	LadoPF = AVC.ParUser1[Cuba].BitAl2O3[0]; //BitAl2O3[0] = BitSiloAl2O3_1 = 22 = Opto21
  }
  else
  {
	LadoPF = AVC.ParUser1[Cuba].BitAl2O3[1]; //BitAl2O3[1] = BitSiloAl2O3_2 = 21 = Opto20
  }

  if(AVC.ParUser2[Cuba].BitDuploOver eq 0 or AVC.ParUser2[Cuba].HabilitaPFCBA eq FALSO or
		AVC.User2[Cuba].EstadoPFCBA ne 3)
  {
    if ((Falha=ComandaSaidaRem(Cuba, LIGAR, LadoPF, 2 * BASE_TEMPO_REMOTA)) ne STATUS_OK)
    {   
      if (Falha ne ERRO_ALIMENTACAO)
          EmiteAlarmeFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_ERR_11),
				 ConvCubScoreOper(Cuba),ScoreGetStr(SCORE_MSG_2025));
	  else
	      EmiteAlarmeFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_ERR_11),
				 ConvCubScoreOper(Cuba),"Todos alimentadores desabilitados.");
    }
    else
    {
      EST_AVC(Cuba).Est.AlimAl2O3 = VERDADEIRO;
	  AVC.User2[Cuba].HoraUltAlim = HoraAtualSec;
      AVC.User1[Cuba].HoraUltPF= HoraAtualSec;  

	  if (EST_AVC(Cuba).Est.LadoProxPF eq AVC.ParUser1[Cuba].LadoDobraPF)
	    AVC.User2[Cuba].ContCabPF++;
	  
	  if(AVC.ParUser1[Cuba].HabDobraPF eq VERDADEIRO)
	  {
	    if(AVC.User2[Cuba].ContCabPF < AVC.ParUser1[Cuba].NumDobraPF)
	    {
	  	  EST_AVC(Cuba).Est.LadoProxPF = AVC.ParUser1[Cuba].LadoDobraPF;	  
	    }
	    else
	    {
	      EST_AVC(Cuba).Est.LadoProxPF = abs(AVC.ParUser1[Cuba].LadoDobraPF -1);		  
		  AVC.User2[Cuba].ContCabPF = 0;
	    } 	
	  }
	  else
	  {
	    if (EST_AVC(Cuba).Est.LadoProxPF eq 0)
	      EST_AVC(Cuba).Est.LadoProxPF = 1;
	    else
	      EST_AVC(Cuba).Est.LadoProxPF = 0;
	  }
    }
  }	  
  else
  {
    if (ComandaSaidaRem2W(Cuba,LIGAR, LadoPF, AVC.ParUser2[Cuba].BitDuploOver,(int)(2 * BASE_TEMPO_REMOTA)) ne 0) 
          EmiteAlarmeFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_ERR_11),
				 ConvCubScoreOper(Cuba),ScoreGetStr(SCORE_MSG_2025));
	else
	{
      EST_AVC(Cuba).Est.AlimAl2O3 = VERDADEIRO;
	  AVC.User2[Cuba].HoraUltAlim = HoraAtualSec;
      AVC.User1[Cuba].HoraUltPF= HoraAtualSec;  

	  if (EST_AVC(Cuba).Est.LadoProxPF eq 0)
	    EST_AVC(Cuba).Est.LadoProxPF = 1;
	  else
	    EST_AVC(Cuba).Est.LadoProxPF = 0;
	}
  }
  
  Seq = EST_AVC(Cuba).Est.LadoProxPF;
  if(AVC.ParUser2[Cuba].HabilitaPFCBA eq VERDADEIRO)
  	AVC.User1[Cuba].IntervCurr=   AVC.ParUser1[Cuba].QuantAlumCarga[Seq]/ 
                                (AVC.ParUser1[Cuba].EfiCurrIni*K_CONSUMO);
  else
  	AVC.User1[Cuba].IntervCurr=   AVC.ParUser1[Cuba].QuantAlumCarga[Seq]/ 
                                (AVC.User1[Cuba].EfiCurr*K_CONSUMO);

  #ifndef ATIVA_SIMULACAO
    return(Falha);
  #else
    return(STATUS_OK);
  #endif  
}

/*
-------------------------------------------------------------------------------
  AcionaFluoreto - Funcao para acionamento do fluoreto do
				new Soderberg CBA
-------------------------------------------------------------------------------
*/
void AcionaFluoreto(int Cuba)
{

	short int Falha;
	byte LadoAlF3;

	DEPURA(printf("Acionando point feeder, Cuba %d \n", ConvCubScoreOper(Cuba));)
	if(EST_AVC(Cuba).Est.LadoProxPF eq 0) //Lado Proxima Quebrada PF New Soderberg
	{
		LadoAlF3 = AVC.ParUser1[Cuba].BitAlF3[0]; //BitAlF3[0] -> BitSiloAlF3_1 = 24
	}
  	else
  	{
		LadoAlF3 = AVC.ParUser1[Cuba].BitAlF3[1]; //BitAlF3[1] -> BitSiloAlF3_2 = 23
  	}

	if ( HoraAtualSec >= AVC.User2[Cuba].HoraUltAlF3 + AVC.User2[Cuba].IntervAlF3 and
			(AVC.ParUser1[Cuba].AlF3Dia * 1000) > SUPERV_AVC(Cuba).Sup.ALF3Fornecido and
			AVC.ParUser1[Cuba].NumSiloAlF3 > 0 and EST_AVC(Cuba).Est.TabelaAlF3 eq VERDADEIRO and
			HoraAtualSec >= (AVL.Trab.HoraIniDia + AVC.ParUser1[Cuba].HoraIniAlF3) and
			HoraAtualSec <= (AVL.Trab.HoraIniDia + AVC.ParUser1[Cuba].HoraIniAlF3 + AVC.ParUser1[Cuba].TIntAlF3) and
			EST_AVC(Cuba).Est.AlimAl2O3 eq FALSO and EST_AVC(Cuba).Est.AlimAlF3 eq FALSO)
	{
		if ((Falha=ComandaSaidaRem(Cuba, LIGAR, LadoAlF3, 2 * BASE_TEMPO_REMOTA)) ne STATUS_OK)
		{ 
			if (Falha ne ERRO_ALIMENTACAO)
				EmiteAlarmeFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_ERR_11),
						ConvCubScoreOper(Cuba),ScoreGetStr(SCORE_MSG_2025));
			else
				EmiteAlarmeFor(TODOS_DISPOSITIVOS,ScoreGetStr(SCORE_ERR_11),
						ConvCubScoreOper(Cuba),"Todos alimentadores desabilitados.");
		}
		else
		{
			EST_AVC(Cuba).Est.AlimAlF3 = VERDADEIRO;
			AVC.User2[Cuba].HoraUltAlF3 = HoraAtualSec;
			AVC.User1[Cuba].HoraUltPF= HoraAtualSec;  
			AVC.User2[Cuba].HoraUltAlim = HoraAtualSec;
		}
	}
}

/*
-------------------------------------------------------------------------------
  SupervPF - Faz o update das variaveis de supervisao
  
  OBS: Todos os tempos sao calculados em ticks do ciclo de leitura. Na hora
       de exibi-los, estes devem ser propriamente corrigidos.
-------------------------------------------------------------------------------
*/
void SupervPF(int cuba)
{
  int	i;
  byte Seq;

  /* Incrementa o tempo em que a movimentacao do anodo permaneceu inibida */
  if (EST_AVC(cuba).InibeControleAlim eq VERDADEIRO)
  {
    SUPERV_AVC(cuba).Sup.TInibeControle++;
    SUPERV_AVC_TURNO(cuba).Sup.TInibeControle++;
  }

  if(EST_AVC(cuba).Est.AlimAlF3 eq VERDADEIRO and
	  (HoraAtualSec - AVC.User2[cuba].HoraUltAlim) > AVC.ParUser1[cuba].TFalhaAlim) //30 segundos
  {
	  //    if(EST_AVC(cuba).ChaveLocRem eq REMOTO)
	  GeraEvento(EV_FALHAPF,cuba,-1, "ALF3", abs(EST_AVC(cuba).Est.LadoProxPF - 1)+1);
	  EST_AVC(cuba).Est.AlimAlF3 = FALSO;	  
  }

  if(EST_AVC(cuba).Est.AlimAl2O3 eq VERDADEIRO and
	  (HoraAtualSec - AVC.User2[cuba].HoraUltAlim) > AVC.ParUser1[cuba].TFalhaAlim) //30 segundos
  {
	  //    if(EST_AVC(cuba).ChaveLocRem eq REMOTO)
      GeraEvento(EV_FALHAPF,cuba,-1, "AL2O3", abs(EST_AVC(cuba).Est.LadoProxPF - 1)+1);
	  EST_AVC(cuba).Est.AlimAl2O3 = FALSO;			
  }

  if(AVC.User1[cuba].RetornoAlF3 eq VERDADEIRO)
  {
    /* ************* TRATA ALIMENTACAO PF FLUORETO********************* */
	/* Alumina alimentada na maquina de estados em execucao */
	Seq = abs(EST_AVC(cuba).Est.LadoProxPF - 1);

	/* Incrementa numero de acionamentos (usado no calculo da incerteza acumulada)*/
	SUPERV_AVC(cuba).Sup.NumAcionaAlF3++;
	SUPERV_AVC_TURNO(cuba).Sup.NumAcionaAlF3++;

	/* ESTATISTICA */
	/* incrementa quantidade de alumina total */
	SUPERV_AVC(cuba).Sup.ALF3Fornecido += AVC.ParUser1[cuba].QuantAlF3Carga[Seq];
	SUPERV_AVC_TURNO(cuba).Sup.ALF3Fornecido += AVC.ParUser1[cuba].QuantAlF3Carga[Seq];

	if (EST_AVC(cuba).ChaveLocRem eq LOCAL)
	{ /* alimentacao manual alf3 */

	}
	else
	{ /* -- alimentacao em remoto alf3 -- */
	
	}
	AVC.User1[cuba].RetornoAlF3 = FALSO;
	EST_AVC(cuba).Est.AlimAlF3 = FALSO;
  }


  if(AVC.User1[cuba].RetornoAl2O3 eq VERDADEIRO)
  {
  
    /* ************* TRATA ALIMETACAO PF ALUMINA********************* */

    /* Alumina alimentada na maquina de estados em execucao */
    Seq = abs(EST_AVC(cuba).Est.LadoProxPF - 1);
	if(AVC.ParUser1[cuba].HabilitaPF eq VERDADEIRO)
      AVC.User1[cuba].QtAAlimEstAtual += AVC.ParUser1[cuba].QuantAlumCarga[Seq];

    /* Incrementa numero de acionamentos (usado no calculo da incerteza acumulada)*/
    AVC.User1[cuba].NumAciona++;
    SUPERV_AVC(cuba).Sup.NumAciona++;
    SUPERV_AVC_TURNO(cuba).Sup.NumAciona++;
 
    /* Incrementa fornecimento de alumina no estado atual */
	if(AVC.ParUser1[cuba].HabilitaPF eq VERDADEIRO)
      AVC.User1[cuba].FornecSubEst += AVC.ParUser1[cuba].QuantAlumCarga[Seq];

    /* ESTATISTICA */
    /* incrementa quantidade de alumina total */
    SUPERV_AVC(cuba).Sup.QtdAlumina += AVC.ParUser1[cuba].QuantAlumCarga[Seq];
    SUPERV_AVC_TURNO(cuba).Sup.QtdAlumina += AVC.ParUser1[cuba].QuantAlumCarga[Seq];
    AVC.User3[cuba].CargaEst[AVC.User2[cuba].EstadoPFCBA] += AVC.ParUser1[cuba].QuantAlumCarga[Seq];

    /* incrementa quantidade de alumina de acordo com algoritmo */
	if(AVC.ParUser1[cuba].HabilitaPF eq VERDADEIRO)
	{
      switch(AVC.User1[cuba].EstadoAlimAtual)
      {
        case EST_ALIM_PADRAO:
          SUPERV_AVC(cuba).Sup.QtdAluminaPadrao += AVC.ParUser1[cuba].QuantAlumCarga[Seq];
   	      SUPERV_AVC_TURNO(cuba).Sup.QtdAluminaPadrao += AVC.ParUser1[cuba].QuantAlumCarga[Seq];
	      break;
        case EST_ALIM_EA:
	      SUPERV_AVC(cuba).Sup.QtdAluminaEA += AVC.ParUser1[cuba].QuantAlumCarga[Seq];
	      SUPERV_AVC_TURNO(cuba).Sup.QtdAluminaEA += AVC.ParUser1[cuba].QuantAlumCarga[Seq];
	      break;
        case EST_ALIM_SUSPENSA: //nunca deve acontecer!!!
	      break;
        case EST_ALIM_EXCECAO:
	      SUPERV_AVC(cuba).Sup.QtdAluminaExc += AVC.ParUser1[cuba].QuantAlumCarga[Seq];
	      SUPERV_AVC_TURNO(cuba).Sup.QtdAluminaExc += AVC.ParUser1[cuba].QuantAlumCarga[Seq];
	      break;
      } /* switch */
	}

    if (EST_AVC(cuba).ChaveLocRem eq LOCAL)
    { /* alimentacao manual */

    }
    else
    { /* -- alimentacao em remoto -- */

    }
	AVC.User1[cuba].RetornoAl2O3 = FALSO;
	EST_AVC(cuba).Est.AlimAl2O3 = FALSO;
  }
  
  /* Incrementa o tempo em que a alimentacao ficou em manual local (campo) */
  if (EST_AVC(cuba).Est.ManualAlimLoc eq VERDADEIRO)
  {
    SUPERV_AVC(cuba).Sup.TManAlimLoc++;
    SUPERV_AVC_TURNO(cuba).Sup.TManAlimLoc++;
  }

  /* Incrementa o tempo em que a alimentacao ficou em manual remoto (computador) */
  if (EST_AVC(cuba).Est.ManualAlimRem eq VERDADEIRO)
  {
    SUPERV_AVC(cuba).Sup.TManAlimRem++;
    SUPERV_AVC_TURNO(cuba).Sup.TManAlimRem++;
  }

  /* Incrementa o tempo em que a alimentacao ficou em manual local ou remoto */
  if ((EST_AVC(cuba).Est.ManualAlimRem eq VERDADEIRO) or
      (EST_AVC(cuba).Est.ManualAlimLoc eq VERDADEIRO))
  {
    SUPERV_AVC(cuba).Sup.TManAlim++;
    SUPERV_AVC_TURNO(cuba).Sup.TManAlim++;
  }

  /* Incrementa o tempo em que a alimentacao ficou em automatico */
  if ((EST_AVC(cuba).Est.ManualAlimLoc ne VERDADEIRO) and    
      (EST_AVC(cuba).Est.ManualAlimRem ne VERDADEIRO))
  {
    SUPERV_AVC(cuba).Sup.TAutoAlim++;
    SUPERV_AVC_TURNO(cuba).Sup.TAutoAlim++;
  }

/* -- Alteracao - Inicio - Robson - 19/10/00 - inclusao das variaveis de supervisao do novo PF -- */
  if (AVC.ParUser1[cuba].HabilitaPF eq VERDADEIRO)
  {
	for (i=0; i<NUM_CONJ_ALIM; i++)
	{
	  /* -- Alteracao - inicio - Leonel - 21/11/2000 - Inclusao programa de operacao -- */
	  /** if (AVC.ParUser1[cuba].HabQueb[i] eq FALSO)  **/
	  if ( (AVC.ParUser1[cuba].HabQueb[i] eq FALSO) or
		   (AVC.User2[cuba].HabQuebOp[i] eq FALSO) )
	  /* -- Alteracao - fim - Leonel - 21/11/2000 - Inclusao programa de operacao -- */
	  {
		SUPERV_AVC(cuba).Sup.TQuebInib[i]++;
		SUPERV_AVC_TURNO(cuba).Sup.TQuebInib[i]++;
		AVC.User2[cuba].TQuebInib[i]++;
		/* quando quebrada desabilitada, automaticamente o alimentador sera desabilitado */
		SUPERV_AVC(cuba).Sup.TAlimInib[i]++;
		SUPERV_AVC_TURNO(cuba).Sup.TAlimInib[i]++;
		AVC.User2[cuba].TAlimInib[i]++;
	  }
	  else
	  {
		AVC.User2[cuba].TQuebInib[i]=0;
		/* -- Alteracao - inicio - Leonel - 21/11/2000 - Inclusao programa de operacao -- */
		/** if (AVC.ParUser1[cuba].HabAlim[i] eq FALSO) ***/
		if ( (AVC.ParUser1[cuba].HabAlim[i] eq FALSO) or
			 (AVC.User2[cuba].HabAlimOp[i] eq FALSO) )
		/* -- Alteracao - fim - Leonel - 21/11/2000 - Inclusao programa de operacao -- */
		{
		  SUPERV_AVC(cuba).Sup.TAlimInib[i]++;
		  SUPERV_AVC_TURNO(cuba).Sup.TAlimInib[i]++;
		  AVC.User2[cuba].TAlimInib[i]++;
		}
		else
		{
		  AVC.User2[cuba].TAlimInib[i]=0;
		}
	  }
	}
  }
/* -- Alteracao - Fim - Robson - 19/10/00 - inclusao das variaveis de supervisao do novo PF -- */

} /* SupervPF */

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

/* -- Fim McpPF.c -- */
