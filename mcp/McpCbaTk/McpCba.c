/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: McpCba.c

	CONTEUDO	: Modulo de Calculos Primarios CBA - MCP.
                  E'  ativado  pelo modulo de calculos primarios (MCP) a cada
                  ciclo de leitura, na desativacao de linha e na  partida  do
				  sistema.
				  OBS.: Para ser ativado pelo Mcp deve estar inicializada a ta-
						bela de programas na base de dados (campo=336 da tabela
						utilizando o programa BdScore).

	AUTOR		: Marco Aurelio M Lopes

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	06/11/2012

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
06/11/12 | Edicao inicial 										| Marco
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
#include	<McpCba.h>
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
	Main - McpCba - Modulo de controle primario alternativo
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[])
{
	int 			TidMcp;
	t_mens_padrao	Mens;
	int			Responde, Partida;
	t_boolean		PartidaQuente;
	struct timespec start, stop;
	double accum;

	/* -- Recebe endereco da area de dados comum ao processo -- */
	Reply(Receive(0, &Comum, sizeof(Comum)), 0, 0);
		
	/* -- Inicializa apontadores para tabelas globais -- */
	InitVarsComum();

	/* -- Copia NumCubas da base de dados para local -- */
	NumCubas=AVL.NumCubas;

	/* -- Guarda hora atual em secundos -- */
	HoraAtualSec=time(NULL)/TIMES_PER_SEC; /* -- segs. apartir 1/1/1980 -- */

	/* -- Intervalo do ciclo de controle em minutos -- */
	IntervCicCont=(Comum->BaseTempoMcp*Comum->BaseTempoMcc)/(SAD_TICKS*60);

	/* -- Consiste Cuba inicial e cuba final a tratar -- */
	PartidaQuente=ConsisteArgs(argc,argv);

	if (PartidaQuente eq VAL_VERDADEIRO)
	{ /* Modulo ativado com o sistema ja' rodando, nao sera' enviada mensagem
			de inicializacao pelo Mcp. Logo inicializa oque for necessario */
		/* -- Inicializa todas as variaveis de trabalho e executa os procedimentos 
			necessarios a inicializacao do calculos. -- */
		IniCubasMcp();

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
			//	  EmiteErroFor(TODOS_DISPOSITIVOS,"Erro receive [%s]",strerror(errno));

		/* -- Guarda hora atual em secundos -- */
    	HoraAtualSec=time(NULL)/TIMES_PER_SEC; /* -- segs. apartir 1/1/1980 -- */

		switch(Mens.Acao)
		{
			case INICIALIZACAO:
				DEPURA(printf("McpCba->Inicializacao\n");)
				/* -- Inicializa todas as variaveis de trabalho e executa os procedimentos 
					necessarios a inicializacao dos calculos. -- */
				IniCubasMcp();
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
				clock_gettime(CLOCK_REALTIME, &start);
				
				ProcessaCubas();

				clock_gettime(CLOCK_REALTIME,&stop);

				accum=(stop.tv_sec-start.tv_sec) + (double)(stop.tv_nsec-start.tv_nsec)
						/ 1000000000.0;
				AVL.Trab.TimerMcp = accum;
			break;

			case DESABILITOU_LINHA:
				VerificaChaveLocRem();
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
IniCubasMcp - Inicializacao de todas as variaveis relacionadas a este modulo
--------------------------------------------------------------------------------
*/
void IniCubasMcp(void)

{
  	int Cuba,CubaOpe, i;

	/* -- Inicializar as variaveis globais de trabalho do modulo -- */
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
			pot[Cuba].res_05s = 0.0;
			pot[Cuba].res_inst = 0.0;
			pot[Cuba].res_05s_acum = 0.0;
			pot[Cuba].res_inst_acum = 0.0;
			pot[Cuba].sigmas2m = 0.0;
			pot[Cuba].sigmas2m_score = 0.0;
			pot[Cuba].sigmal = 0.0;
			pot[Cuba].sigmal_score = 0.0;
			pot[Cuba].sigmas4s_acum = 0.0;
			pot[Cuba].sigmas4s_score_acum = 0.0;
			pot[Cuba].osc_min = 0.0;
			pot[Cuba].osc_max = 0.0;
			pot[Cuba].MaxOscil = 0.0;
			for (i = 0; i < 8; i++)
			{
				pot[Cuba].res_05s_vet[i] =  0.0;
				pot[Cuba].res_inst_vet[i] =  0.0;	
			}
			pot[Cuba].res_4s = 0.0;
			pot[Cuba].res_4s_score = 0.0;
			pot[Cuba].res_4s_acum = 0.0;
			pot[Cuba].res_4s_score_acum = 0.0;
			for (i = 0; i<30; i++)
			{
				pot[Cuba].res_4s_vet[i] = 0.0;
				pot[Cuba].res_4s_score_vet[i] = 0.0;
				pot[Cuba].sigmas4s[i] = 0.0;
				pot[Cuba].sigmas4s_score[i] = 0.0;
			}
			pot[Cuba].num_res_05s = 0;
			pot[Cuba].num_res_4s = 0;
			pot[Cuba].ContCiclos4s = 0;
			pot[Cuba].ContCiclos2m = 0;	

			EST_AVC(Cuba).Est.SinalChamine = FALSO;
			EST_AVC(Cuba).Est.SopraChamine = FALSO;
		}
	}

	Conta4s = 0;
	Conta2m = 0;
	MediaTensaoLinha = 0;
	MediaSomaCubas = 0;
	SomaTensaoCubas = 0;
	ContEaLinha = 0;
	ContEaSim = 0;
	ContCubasFR = 0;
	ProvavelEfeito = 0;
	EST_AVC(Cuba).Est.TensaoCunha = FALSO;	  
	EST_AVC(Cuba).Est.SireneCunha = FALSO;
	AVC.User2[Cuba].HoraTenCal = 0;	
	EST_AVC(Cuba).Est.DesligaCunha = FALSO;	  	
	AVC.User3[Cuba].ContHistResCA = 0;
	LiberaSemaf(SEMAF_AVC);
}

/*
--------------------------------------------------------------------------------
| ProcessaCubas - 	Processa os calculos necessarios para cada cuba.             |
--------------------------------------------------------------------------------
*/
void ProcessaCubas(void)
{
	int Cuba,CubaOpe, i;
	struct tm HoraIni;

  	memcpy( &HoraIni, localtime(&HoraAtualSec), sizeof(struct tm));  

	HoraIni.tm_hour = 0;
	HoraIni.tm_min = 0;
	HoraIni.tm_sec = 0;
	HoraIni.tm_isdst = 0;

  	HoraInicioDia = mktime(&HoraIni);
  
  	AlocaSemaf(SEMAF_AVC);

	SomaTensaoCubas = 0;
	ContCubasFR = 0;
	ContEaSim = 0;

  	Calculo05s(); /* -- Processa os calculos de 0.5 segundos -- */

  	SopraChamine();

	ContEaLinha++;
	MediaTensaoLinha = (MediaTensaoLinha * (ContEaLinha - 1) + AVL.VLinhaInst) / 
							ContEaLinha;
	MediaSomaCubas = (MediaSomaCubas * (ContEaLinha - 1) + SomaTensaoCubas) / 
						ContEaLinha;
	Conta4s++;

	if (Conta4s eq NUM_LEIT_4S) /* Dispara calculo de 4 segundos */
	{
		if (AVL.LinhaHabilitada eq VERDADEIRO)
		{
			Calculo4s();
			MonitoraCalante();
			AlarmeDesvio();

			//printf("\n MediaTensaoLinha : %5.2f ", MediaTensaoLinha);
			//printf("\n MediaSomaCubas : %5.2f ", MediaSomaCubas);
			//printf("\n ContCubasFR : %d ", ContCubasFR);
			//printf("\n ProvavelEfeito : %d ", ProvavelEfeito);
			//printf("\n EaVoltLinhaLim : %5.2f ", AVL.Par.EaVoltLinhaLim);
			//printf("\n NCic4sEaLinha : %d ", AVL.Par.NCic4sEaLinha);
			//printf("\n EaLinha : %d ", AVL.Trab.EaLinha);

			if (MediaTensaoLinha > (MediaSomaCubas + AVL.Par.EaVoltLinhaLim) and 
				ContCubasFR > 0)  
			{
				ProvavelEfeito++;
				if (ProvavelEfeito >= AVL.Par.NCic4sEaLinha and
						AVL.Trab.EaLinha eq FALSO)
				{
					AVL.Trab.EaLinha = VERDADEIRO;			
					HoraEaLinha = HoraAtualSec;
					GeraEvento(EV_EALINHA,-1,-1,MediaSomaCubas,MediaTensaoLinha,
								ContCubasFR,ContEaSim);
				}
			}
			else
			{
				ProvavelEfeito = 0;
			}

			if( (HoraEaLinha + AVL.Par.TEfeitoEaLinha) < HoraAtualSec)
			{
				AVL.Trab.EaLinha = FALSO;
			}

			MediaTensaoLinha = 0;
			MediaSomaCubas = 0;
			ContEaLinha = 0;
		}
		else
		{
			for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
			{
				Cuba=ConvCubOperScore(CubaOpe);
				if (Cuba eq -1)
					continue;

				pot[Cuba].num_res_05s = 0;
				pot[Cuba].res_05s_acum = 0;
				pot[Cuba].res_inst_acum = 0;
				for (i = 0; i<8; i++)
				{
				pot[Cuba].res_05s_vet[i] =  0.0;
				pot[Cuba].res_inst_vet[i] =  0.0;
				}
			}
		}
		Conta4s = 0;

		Conta1m++;
		if (Conta1m eq NUM_LEIT_1M) /* Dispara calculo de 1 minuto */
		{
			if (AVL.LinhaHabilitada eq VERDADEIRO)
			{
				Calculo1m();
			}
			else
			{
				for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
				{
					Cuba=ConvCubOperScore(CubaOpe);
					if (Cuba eq -1)
						continue;

					pot[Cuba].num_res_4s_1m = 0;
					pot[Cuba].res_4s_1m_score_acum = 0;
				}
			}
			Conta1m = 0;
		}

	Conta2m++;
	if (Conta2m eq NUM_LEIT_2M) /* Dispara calculo de 2 minutos */
	{
		if (AVL.LinhaHabilitada eq VERDADEIRO)
		{
		  Calculo2m();
		}
		else
		{
  		  for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
  		  {
			Cuba=ConvCubOperScore(CubaOpe);
			if (Cuba eq -1)
	  			continue;

			pot[Cuba].num_res_4s = 0;
			pot[Cuba].res_4s_acum = 0;
			pot[Cuba].res_4s_score_acum = 0;
			for (i = 0; i<30; i++)
			{
			  pot[Cuba].res_4s_vet[i] =  0.0;
			  pot[Cuba].res_4s_score_vet[i] =  0.0;
			}
		  }
		}
	 	Conta2m = 0;
	}

	Conta5m++;
	if (Conta5m eq NUM_LEIT_5M) /* Dispara calculo de 5 minutos */
	{
		if (AVL.LinhaHabilitada eq VERDADEIRO)
		{
		  Calculo5m();
		}
		else
		{
  		  for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
  		  {
			Cuba=ConvCubOperScore(CubaOpe);
			if (Cuba eq -1)
	  			continue;
		  }
		}
	 	Conta5m = 0;
	}

  }

  LiberaSemaf(SEMAF_AVC);


} /* -- ProcessaCubas -- */


/*
--------------------------------------------------------------------------------
| Calculo05s - 	Processa os calculos necessarios para cada cuba.             |
--------------------------------------------------------------------------------
*/
void Calculo05s(void)
{
	int Cuba,CubaOpe;

	VerificaChaveLocRem();
	
	SinalizaAlarmeSala(); 

	for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
	{
		Cuba=ConvCubOperScore(CubaOpe);
		if (Cuba eq -1)
			continue;

		/* Desativa bit de comunicacao com CLP New Soderberg */
		if (AVC.ParUser1[Cuba].AtivaBitCLP eq FALSO and EST_AVC(Cuba).Est.BitCLP eq VERDADEIRO)
		{
			ComandaSaidaRem(Cuba, DESLIGAR, 18, 0);
			EST_AVC(Cuba).Est.BitCLP = FALSO;
		}  
		
		if (EST_AVC(Cuba).EstadoCuba ne CUBA_DESLIGADA)
		{
			if (EST_AVC(Cuba).ForaLeitura eq FALSO)
			{
				// Soma Tensão Cubas adicionando Tensão Instantânea para Cubas com Leitura em Estado Normal/Partido
				SomaTensaoCubas = SomaTensaoCubas + AVC.Cleit[Cuba].Vinst;
			}
			else
			{
				// Soma Tensão Cubas adicionando Tensão de Alvo para Cubas Fora de Rede
				SomaTensaoCubas = SomaTensaoCubas + 
					(AVC.Ccont[Cuba].RAlvo * AVC.Ccont[Cuba].INominalCuba + 	
					AVC.Param[Cuba].Bemf);		
				// Incrementa Contador de Cubas Fora Rede
				ContCubasFR++;
			}
			if ( EST_AVC(Cuba).Ea eq VERDADEIRO)
			{
				// Incrementa Contador de Efeitos
				ContEaSim++;
			}
		}
		else //Cuba Desligada
		{
			if (EST_AVC(Cuba).ForaLeitura eq FALSO) //Leitura OK
			{
				if (AVC.Cleit[Cuba].Vinst < 1.0)
				{
					// Soma Tensão Cubas adicionando Tensão Instantânea para Cubas Desligadas
					SomaTensaoCubas = SomaTensaoCubas + AVC.Cleit[Cuba].Vinst;
				}
			}
		}	

		if ((EST_AVC(Cuba).EstadoCuba ne CUBA_DESLIGADA) and
			(AlgControle(Cuba,ALG_SCORE01) eq VERDADEIRO))
		{
			/* -- Verifica condicoes para tratamento da cuba -- */
			if ((EST_AVC(Cuba).ForaLeitura eq FALSO) and
				(AVL.LinhaHabilitada eq VERDADEIRO) and (EST_AVC(Cuba).Ea eq FALSO))
			{
				/* -- Verifica intervalos de quebrada -- */
				if((EST_AVC(Cuba).Quebrada eq VERDADEIRO) and (EST_AVC(Cuba).Ea eq FALSO) and
					(EST_AVC(Cuba).EaPrev eq FALSO) and (EST_AVC(Cuba).Est.QuebPrev eq FALSO) and
					(AVC.User2[Cuba].HoraEvQuebrada < AVC.Cleit[Cuba].HoraUltQueb))
				{
					if((abs(AVC.Cleit[Cuba].HoraUltQueb - AVC.User2[Cuba].HoraUltQuebReal)) <
						abs(AVC.Cleit[Cuba].HoraUltQueb - AVC.User2[Cuba].HoraProxQuebReal))
					{
						SUPERV_AVC(Cuba).Sup.NumQuebProgDia += 1;
						SUPERV_AVC(Cuba).Sup.IntervRefQuebDia = (((SUPERV_AVC(Cuba).Sup.IntervRefQuebDia - 
							AVC.ParUser1[Cuba].IntervQuebProg) * (SUPERV_AVC(Cuba).Sup.NumQuebProgDia - 1)) + 
							(AVC.Cleit[Cuba].HoraUltQueb - AVC.User2[Cuba].HoraUltQuebReal)) / 
							SUPERV_AVC(Cuba).Sup.NumQuebProgDia;
					}
					else
					{
						SUPERV_AVC(Cuba).Sup.NumQuebProgDia += 1;
						SUPERV_AVC(Cuba).Sup.IntervRefQuebDia = (((SUPERV_AVC(Cuba).Sup.IntervRefQuebDia - 
							AVC.ParUser1[Cuba].IntervQuebProg) * (SUPERV_AVC(Cuba).Sup.NumQuebProgDia - 1)) + 
							(AVC.Cleit[Cuba].HoraUltQueb - AVC.User2[Cuba].HoraProxQuebReal)) / 
							SUPERV_AVC(Cuba).Sup.NumQuebProgDia;
					}
					SUPERV_AVC(Cuba).Sup.IntervRefQuebDia += AVC.ParUser1[Cuba].IntervQuebProg;		  

					AVC.User2[Cuba].HoraEvQuebrada = AVC.Cleit[Cuba].HoraUltQueb; 
					
					if (EST_AVC(Cuba).Est.DerBaixa eq VERDADEIRO)
					{
						SUPERV_AVC(Cuba).Sup.NumDBQueb++;
					}
				}		

				/* -- Realiza calculo de resistencia -- */
				pot[Cuba].res_05s = (AVC.Cleit[Cuba].Vinst - AVC.Param[Cuba].Bemf) / 
										AVL.Iinst;
				AVC.User2[Cuba].Rinst_atnca = pot[Cuba].res_05s;
				pot[Cuba].res_inst = AVC.Cleit[Cuba].Rinst;
				if ((pot[Cuba].res_05s > 0) and (pot[Cuba].res_inst > 0))
				{
					if ( (pot[Cuba].num_res_05s >= 0) and 
						(pot[Cuba].num_res_05s < NUM_LEIT_4S))
					{
						pot[Cuba].res_05s_vet[pot[Cuba].num_res_05s] = pot[Cuba].res_05s;
						pot[Cuba].res_inst_vet[pot[Cuba].num_res_05s] = pot[Cuba].res_inst;
						pot[Cuba].res_inst_acum += pot[Cuba].res_inst;
						pot[Cuba].res_05s_acum += pot[Cuba].res_05s;
						pot[Cuba].num_res_05s++;
					}
					else
					{
						pot[Cuba].res_inst = 0;
						pot[Cuba].res_inst_acum = 0;
						pot[Cuba].num_res_05s = 0;				
						pot[Cuba].res_05s_acum = 0;
					}
				}			
			} /* -- if fora leitura -- */
		} /* -- if EstadoCuba -- */
	} /* -- for -- */
} /* -- Calculo 0.5 s -- */


/*
--------------------------------------------------------------------------------
| Calculo4s - 	Processa os calculos de 4 segundos necessarios para cada cuba.|
--------------------------------------------------------------------------------
*/
void Calculo4s(void)
{
	int Cuba,CubaOpe, i;
	double	difsigma, soma, soma_score;
	
	/* Transcreve valores de turno para variaveis OPC */
  	AVL.Trab.Ea24hTurno = AVL_TURNO.Sup.Ea24h;
  	AVL.Trab.AtrasoEATurno = AVL_TURNO.Sup.AtrasoEA;
  	AVL.Trab.NumEaDiaTurno = AVL_TURNO.Sup.NumEaDia;
  
	for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
  	{
		Cuba=ConvCubOperScore(CubaOpe);
		if (Cuba eq -1)
			continue;

		/* -- Identifica variavel StatusPainel -- */
		
		if ((EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL) and 
			(EST_AVC(Cuba).ChaveLocRem eq LOCAL))	
		{
			EST_AVC(Cuba).Est.StatusPainel = 1; //CUBA_NORMAL e LOCAL
		}

		if ((EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL) and 
			(EST_AVC(Cuba).ChaveLocRem eq REMOTO))
		{
			EST_AVC(Cuba).Est.StatusPainel = 0; //CUBA_NORMAL e REMOTO
		}	

		/* -- Identifica variavel StatusEv -- */
		AVC.User1[Cuba].StatusEv = 0;
		
		if(EST_AVC(Cuba).Ea eq VERDADEIRO)
			AVC.User1[Cuba].StatusEv |= AVC.User1[Cuba].StatusEv orb 1; 
		if(EST_AVC(Cuba).Est.DerBaixa eq VERDADEIRO)
			AVC.User1[Cuba].StatusEv |= AVC.User1[Cuba].StatusEv orb 2; 
		if(EST_AVC(Cuba).EaPrev eq VERDADEIRO)
			AVC.User1[Cuba].StatusEv |= AVC.User1[Cuba].StatusEv orb 4;
		if(EST_AVC(Cuba).Est.QuebPrev eq VERDADEIRO)
			AVC.User1[Cuba].StatusEv |= AVC.User1[Cuba].StatusEv orb 8; 
		if(EST_AVC(Cuba).ChaveLocRem eq LOCAL)
			AVC.User1[Cuba].StatusEv |= AVC.User1[Cuba].StatusEv orb 16; 
		if(EST_AVC(Cuba).ChaveLocRem eq REMOTO)
			AVC.User1[Cuba].StatusEv |= AVC.User1[Cuba].StatusEv orb 32; 
		if(EST_AVC(Cuba).RuidoLent eq VERDADEIRO)
			AVC.User1[Cuba].StatusEv |= AVC.User1[Cuba].StatusEv orb 64; 
		if(EST_AVC(Cuba).RuidoRap eq VERDADEIRO)
			AVC.User1[Cuba].StatusEv |= AVC.User1[Cuba].StatusEv orb 128; 
		if(EST_AVC(Cuba).EfeitoMove eq VERDADEIRO)
			AVC.User1[Cuba].StatusEv |= AVC.User1[Cuba].StatusEv orb 256; 
		if(EST_AVC(Cuba).EfeitoEa eq VERDADEIRO)
			AVC.User1[Cuba].StatusEv |= AVC.User1[Cuba].StatusEv orb 512;
		if(EST_AVC(Cuba).EfeitoQueb eq VERDADEIRO)
			AVC.User1[Cuba].StatusEv |= AVC.User1[Cuba].StatusEv orb 1024; 
		if(EST_AVC(Cuba).EfeitoCorr eq VERDADEIRO)
			AVC.User1[Cuba].StatusEv |= AVC.User1[Cuba].StatusEv orb 2048; 
		if(EST_AVC(Cuba).TrataTPinos eq VERDADEIRO)
			AVC.User1[Cuba].StatusEv |= AVC.User1[Cuba].StatusEv orb 4096;
		if(EST_AVC(Cuba).Est.AjusteCamisa eq VERDADEIRO)
			AVC.User1[Cuba].StatusEv |= AVC.User1[Cuba].StatusEv orb 8192;
		if(EST_AVC(Cuba).Est.CamNAjust eq VERDADEIRO)
			AVC.User1[Cuba].StatusEv |= AVC.User1[Cuba].StatusEv orb 16384; 
		if(EST_AVC(Cuba).ProvAgarraAnodo eq VERDADEIRO)
			AVC.User1[Cuba].StatusEv |= AVC.User1[Cuba].StatusEv orb 32768;
		if(EST_AVC(Cuba).Est.FormaBanho eq VERDADEIRO)
			AVC.User1[Cuba].StatusEv |= AVC.User1[Cuba].StatusEv orb 65536; 
		if(EST_AVC(Cuba).DesvioTensao eq VERDADEIRO)
			AVC.User1[Cuba].StatusEv |= AVC.User1[Cuba].StatusEv orb 131072;
 
		soma = 0;
		soma_score = 0;

		if ((EST_AVC(Cuba).EstadoCuba ne CUBA_DESLIGADA) and
			(AlgControle(Cuba,ALG_SCORE01) eq VERDADEIRO))
		{
			/* -- Verifica condicoes para tratamento da cuba -- */
			if ((EST_AVC(Cuba).ForaLeitura eq FALSO) and
				(AVL.LinhaHabilitada eq VERDADEIRO))
			{
				if ( pot[Cuba].num_res_05s > 0 and pot[Cuba].num_res_05s <= NUM_LEIT_4S)
				{
					if ( pot[Cuba].num_res_4s_1m >= 0 and pot[Cuba].num_res_4s_1m < NUM_LEIT_1M)
					{	
						pot[Cuba].res_4s_1m_score = pot[Cuba].res_inst_acum / 
												pot[Cuba].num_res_05s;

						pot[Cuba].res_4s_1m_score_acum += pot[Cuba].res_4s_1m_score;

						pot[Cuba].num_res_4s_1m++;

					}
					else
					{
						pot[Cuba].num_res_4s_1m = 0;
						pot[Cuba].res_4s_1m_score_acum = 0;
					}

					if ( pot[Cuba].num_res_4s >= 0 and pot[Cuba].num_res_4s < NUM_LEIT_2M)
					{
						pot[Cuba].res_4s = pot[Cuba].res_05s_acum /			
											pot[Cuba].num_res_05s;
						pot[Cuba].res_4s_score = pot[Cuba].res_inst_acum / 
												pot[Cuba].num_res_05s;

						/* --- Calculo de Oscilacao --- */
						if(pot[Cuba].osc_min eq 0) 
						{
							pot[Cuba].osc_min = pot[Cuba].res_4s;  
						}

						else
						{
							if(pot[Cuba].osc_min > pot[Cuba].res_4s)
							{
								pot[Cuba].osc_min = pot[Cuba].res_4s;
							}
						}

						if(pot[Cuba].osc_max eq 0) 
						{
							pot[Cuba].osc_max = pot[Cuba].res_4s;  
						}
						else
						{
							if(pot[Cuba].osc_max < pot[Cuba].res_4s)
							{
								pot[Cuba].osc_max = pot[Cuba].res_4s;
							}
						}						
				
						pot[Cuba].res_4s_vet[pot[Cuba].num_res_4s] = pot[Cuba].res_4s;
						pot[Cuba].res_4s_score_vet[pot[Cuba].num_res_4s] = pot[Cuba].res_4s_score;
						pot[Cuba].res_4s_acum += pot[Cuba].res_4s;
						pot[Cuba].res_4s_score_acum += pot[Cuba].res_4s_score;

						/* --- Calculo Sigma --- */
						for (i = 0; i < pot[Cuba].num_res_05s ; i++)
						{
							difsigma = pot[Cuba].res_05s_vet[i] - pot[Cuba].res_4s;

							soma += difsigma * difsigma;

							difsigma = pot[Cuba].res_inst_vet[i] - pot[Cuba].res_4s_score;

							soma_score += difsigma * difsigma;

							pot[Cuba].res_05s_vet[i] = 0;

							pot[Cuba].res_inst_vet[i] = 0;
						}

						soma = sqrt(( soma / pot[Cuba].num_res_05s));

						pot[Cuba].sigmas4s[pot[Cuba].num_res_4s] = (float)soma;

						soma_score = sqrt((soma_score /	pot[Cuba].num_res_05s));

						pot[Cuba].sigmas4s_score[pot[Cuba].num_res_4s] = (float)soma_score;

						pot[Cuba].sigmas4s_acum += soma;

						pot[Cuba].sigmas4s_score_acum += soma_score;

						pot[Cuba].num_res_4s++;

					}
					else
					{
						pot[Cuba].num_res_4s = 0;
						pot[Cuba].res_4s_acum = 0;
						pot[Cuba].res_4s_score_acum = 0;
						pot[Cuba].sigmas4s_score_acum = 0;		
						pot[Cuba].sigmas4s_acum = 0;					
					}
				} 

				MovQuebProg(Cuba);

			} /* -- if fora leitura -- */

			pot[Cuba].num_res_05s = 0;
			pot[Cuba].res_05s_acum = 0;
			pot[Cuba].res_inst_acum = 0;

	}
  } /* -- for -- */
} /* -- Calculo 4s -- */



/*
--------------------------------------------------------------------------------
| Calculo1m - 	Processa os calculos de 1 minutos necessarios para cada cuba.|
--------------------------------------------------------------------------------
*/
void Calculo1m(void)
{
  int Cuba,CubaOpe, i, k;
  float x[20];
  float sumx=0;
  float sumx2=0;
  float sumy=0;
  float sumxy=0;
  float sumy2=0;

  for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
  {
	Cuba=ConvCubOperScore(CubaOpe);
	if (Cuba eq -1)
	  continue;

	if ((EST_AVC(Cuba).EstadoCuba ne CUBA_DESLIGADA) and
		(AlgControle(Cuba,ALG_SCORE01) eq VERDADEIRO))
	{
	  /* -- Verifica condicoes para tratamento da cuba -- */
	  if ((EST_AVC(Cuba).ForaLeitura eq FALSO) and
		  (AVL.LinhaHabilitada eq VERDADEIRO))
	  {

		SUPERV_AVC(Cuba).Sup.NumCCtrl1mDia++;

		if(AVC.User3[Cuba].TFatorFeedRate > 0)
		{
		  AVC.User3[Cuba].TFatorFeedRate -= 60;
		  if(AVC.User3[Cuba].TFatorFeedRate <= 0)
			GeraEvento(EV_FATORPF, Cuba, -1, "Fim", 0, 1.0);
		}
		else
		{
		  AVC.User3[Cuba].TFatorFeedRate = 0;
		  AVC.User3[Cuba].FatorFeedRate = 1.0;
		}

		if(EST_AVC(Cuba).Est.Oscilacao eq VERDADEIRO and
			AVC.User2[Cuba].IncOscil > 0)
		{
		  SUPERV_AVC(Cuba).Sup.NumOscilDia++;
		  SUPERV_AVC_TURNO(Cuba).Sup.NumOscilDia++;
		  SUPERV_AVC(Cuba).Sup.DurIncOscilDia += 60;
		  SUPERV_AVC_TURNO(Cuba).Sup.DurIncOscilDia += 60;
		  SUPERV_AVC(Cuba).Sup.IncOscilDia = (((SUPERV_AVC(Cuba).Sup.IncOscilDia * (SUPERV_AVC(Cuba).Sup.NumOscilDia - 1)) +
					 AVC.User2[Cuba].IncOscil)/SUPERV_AVC(Cuba).Sup.NumOscilDia);
		  SUPERV_AVC_TURNO(Cuba).Sup.IncOscilDia = (((SUPERV_AVC_TURNO(Cuba).Sup.IncOscilDia * (SUPERV_AVC_TURNO(Cuba).Sup.NumOscilDia - 1)) +
					 AVC.User2[Cuba].IncOscil)/SUPERV_AVC_TURNO(Cuba).Sup.NumOscilDia);
		}
		
		if ( pot[Cuba].num_res_4s_1m > 0 and pot[Cuba].num_res_4s_1m <= NUM_LEIT_1M)
		{
		  pot[Cuba].res_score_1m_ant = pot[Cuba].res_score_1m;
		  pot[Cuba].res_score_1m = pot[Cuba].res_4s_1m_score_acum / pot[Cuba].num_res_4s_1m;
		  
		} 
	    if ( AVC.ParUser2[Cuba].HabCalcCoefAC eq VERDADEIRO and
			  AVC.ParUser2[Cuba].IntervCalcCA eq 1)
	    {
			if(EST_AVC(Cuba).Est.ZeraCA eq VERDADEIRO)
			{
				AVC.User3[Cuba].ContHistResCA = 0;
				EST_AVC(Cuba).Est.ZeraCA = FALSO;
			}

			/* Grava historico de resistencia para calculo de coef. angular e correlacao */
			//memmove(&pot[Cuba].HistRes1m[0],&pot[Cuba].HistRes1m[1],
			//	  (sizeof(pot[Cuba].HistRes1m)-sizeof(pot[Cuba].HistRes1m[0])));
			memmove(&AVC.User3[Cuba].HistResCA[0],&AVC.User3[Cuba].HistResCA[1],
				(sizeof(AVC.User3[Cuba].HistResCA)-sizeof(AVC.User3[Cuba].HistResCA[0])));

			AVC.User3[Cuba].HistResCA[19] = pot[Cuba].res_score_1m*1e6;
			//pot[Cuba].HistRes1m[19] = pot[Cuba].res_score_1m*1e6;

			if(AVC.User3[Cuba].ContHistResCA < AVC.ParUser2[Cuba].NCicCoefAng)
				AVC.User3[Cuba].ContHistResCA++;

			/* Calcula coeficiente angular e correlacao */
			if( AVC.User3[Cuba].ContHistResCA >= AVC.ParUser2[Cuba].MinNCicCA)
			{
				sumx = 0;
				sumx2 = 0;
				sumy = 0;
				sumy2 = 0;
				sumxy = 0;

				EST_AVC(Cuba).Est.ProjetaCA = FALSO;

				memmove(&pot[Cuba].DifCoefAng[0],&pot[Cuba].DifCoefAng[1],
					(sizeof(pot[Cuba].DifCoefAng)-sizeof(pot[Cuba].DifCoefAng[0])));

				memmove(&pot[Cuba].DifCoefCor[0],&pot[Cuba].DifCoefCor[1],
					(sizeof(pot[Cuba].DifCoefCor)-sizeof(pot[Cuba].DifCoefCor[0])));

				for (i=0;(i+(20-AVC.User3[Cuba].ContHistResCA))<20;++i)
				{
					k = i+(20-AVC.User3[Cuba].ContHistResCA); 
					x[i]= i*1;
					sumx += x[i];  
					sumx2 += x[i]*x[i]; 
					sumy += AVC.User3[Cuba].HistResCA[k];
					sumy2 += AVC.User3[Cuba].HistResCA[k]*AVC.User3[Cuba].HistResCA[k]; 
					sumxy += x[i]*AVC.User3[Cuba].HistResCA[k];
				}
				
				//(inclinacao da melhor reta (Least Square)			
				pot[Cuba].CoefAngAnt = AVC.User2[Cuba].CoefAng; 
				AVC.User2[Cuba].CoefAng = ((AVC.User3[Cuba].ContHistResCA*sumxy) - (sumx*sumy))/
				((AVC.User3[Cuba].ContHistResCA*sumx2) - (sumx*sumx));
				pot[Cuba].DifCoefAng[19] = AVC.User2[Cuba].CoefAng - pot[Cuba].CoefAngAnt;

				//Calculo Coeficiente Correlacao
				if ((AVC.User3[Cuba].ContHistResCA*sumy2-(sumy*sumy))*(AVC.User3[Cuba].ContHistResCA*sumx2-(sumx*sumx)) < 0)
				AVC.User2[Cuba].CoefCor = 0;
				else
				{
				pot[Cuba].CoefCorAnt = AVC.User2[Cuba].CoefCor; 
				AVC.User2[Cuba].CoefCor = fabs(((AVC.User3[Cuba].ContHistResCA*sumxy)-(sumx*sumy))/
					(sqrt((AVC.User3[Cuba].ContHistResCA*sumy2-(sumy*sumy))*(AVC.User3[Cuba].ContHistResCA*sumx2-(sumx*sumx)))));
				pot[Cuba].DifCoefCor[19] = AVC.User2[Cuba].CoefCor - pot[Cuba].CoefCorAnt;
				}

				AVC.User3[Cuba].DifCoefAng = 0; 
				AVC.User3[Cuba].DifCoefCor = 0;			  

				for (i=0;i<20;++i)
				{
				AVC.User3[Cuba].DifCoefAng += pot[Cuba].DifCoefAng[i]; 
				AVC.User3[Cuba].DifCoefCor += pot[Cuba].DifCoefCor[i];			  
				}

				AVC.User3[Cuba].DifCoefAng = AVC.User3[Cuba].DifCoefAng/20; 
				AVC.User3[Cuba].DifCoefCor = AVC.User3[Cuba].DifCoefCor/20;			  

				SUPERV_AVC(Cuba).Sup.CoefAngDia += (SUPERV_AVC(Cuba).Sup.CoefAngDia *
					(SUPERV_AVC(Cuba).Sup.NumCCtrl1mDia -1) + AVC.User2[Cuba].CoefAng)/
					SUPERV_AVC(Cuba).Sup.NumCCtrl1mDia;	
			}
			else
			{
				if(EST_AVC(Cuba).Est.ProjetaCA eq VERDADEIRO)
				{
				AVC.User2[Cuba].CoefAng += AVC.User3[Cuba].DifCoefAng; 
				AVC.User2[Cuba].CoefCor += AVC.User3[Cuba].DifCoefCor;
				}
				else
				{
				AVC.User2[Cuba].CoefAng = 0.0; 
				AVC.User2[Cuba].CoefCor = 0.0;
				}
			}
	    }	
		else
		{
		  AVC.User2[Cuba].CoefAng = 0.0; 
		  AVC.User2[Cuba].CoefCor = 0.0;
		}

	    if ( EST_AVC(Cuba).EfeitoEa eq FALSO and
			 EST_AVC(Cuba).EfeitoQueb eq FALSO and
			 EST_AVC(Cuba).EfeitoCorr eq FALSO and
			 EST_AVC(Cuba).EfeitoMove eq FALSO)
		{
		  AVC.User2[Cuba].Oscilacao = pot[Cuba].osc_max - pot[Cuba].osc_min;

		  SUPERV_AVC(Cuba).Sup.OscilacaoDia += (SUPERV_AVC(Cuba).Sup.OscilacaoDia *
			(SUPERV_AVC(Cuba).Sup.NumCCtrl1mDia -1) + AVC.User2[Cuba].Oscilacao)/
			SUPERV_AVC(Cuba).Sup.NumCCtrl1mDia;	

          pot[Cuba].MaxOscil = AVC.User2[Cuba].Oscilacao;

		  for(i=0; i<9; i++)
		  {
			pot[Cuba].vet_Oscil[i] = pot[Cuba].vet_Oscil[i+1]; 
		  }

		  pot[Cuba].vet_Oscil[9] = AVC.User2[Cuba].Oscilacao;

		  pot[Cuba].osc_max = 0.0;
	      pot[Cuba].osc_min = 0.0;

	    }
		else
		{
		  pot[Cuba].osc_max = 0.0;
		  pot[Cuba].osc_min = 0.0;
		}
	  } /* -- if fora leitura -- */

	  pot[Cuba].res_4s_1m_score_acum = 0;
	  pot[Cuba].num_res_4s_1m = 0;

	} /* -- if EstadoCuba -- */
  } /* -- for -- */

} /* -- Calculo 1m -- */
/*
--------------------------------------------------------------------------------
| Calculo2m - 	Processa os calculos de 2 minutos necessarios para cada cuba.|
--------------------------------------------------------------------------------
*/
void Calculo2m(void)
{
  int Cuba,CubaOpe, i, k;
  double difsigma, soma, soma_score;
  float correntebaixa, correntealta;
  float x[20];
  float sumx=0;
  float sumx2=0;
  float sumy=0;
  float sumxy=0;
  float sumy2=0;

  for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
  {
	Cuba=ConvCubOperScore(CubaOpe);
	if (Cuba eq -1)
	  continue;

	soma = 0;
  	soma_score = 0;

	if ((EST_AVC(Cuba).EstadoCuba ne CUBA_DESLIGADA) and
		(AlgControle(Cuba,ALG_SCORE01) eq VERDADEIRO))
	{
	  /* -- Verifica condicoes para tratamento da cuba -- */
	  if ((EST_AVC(Cuba).ForaLeitura eq FALSO) and
		  (AVL.LinhaHabilitada eq VERDADEIRO))
	  {
		if ( pot[Cuba].num_res_4s > 0 and pot[Cuba].num_res_4s <= NUM_LEIT_2M)
		{
			AVC.User2[Cuba].Res_2m_ant_atnca = AVC.User2[Cuba].Res_2m_atnca;
			AVC.User2[Cuba].Res_2m_atnca = pot[Cuba].res_4s_acum / pot[Cuba].num_res_4s;
			pot[Cuba].res_score_2m_ant = pot[Cuba].res_score_2m;
			pot[Cuba].res_score_2m = pot[Cuba].res_4s_score_acum / pot[Cuba].num_res_4s;
			AVC.User2[Cuba].ResScore2m = pot[Cuba].res_score_2m;
			AVC.User2[Cuba].ResScore2m_ant = pot[Cuba].res_score_2m_ant;
		  
			for (i = 0; i < pot[Cuba].num_res_4s ; i++)
			{
			  difsigma = pot[Cuba].res_4s_vet[i] - AVC.User2[Cuba].Res_2m_atnca;

			  soma += difsigma * difsigma;

			  difsigma = pot[Cuba].res_4s_score_vet[i] - pot[Cuba].res_score_2m;

			  soma_score += difsigma * difsigma;

			  pot[Cuba].res_4s_vet[i] = 0;
			  pot[Cuba].res_4s_score_vet[i] = 0;
			}

			/* --- Calculo Sigma --- */
			soma = sqrt((soma / pot[Cuba].num_res_4s));
			pot[Cuba].sigmal = (float)soma;

			soma_score = sqrt((soma_score / pot[Cuba].num_res_4s));
			pot[Cuba].sigmal_score = (float)soma_score;

			pot[Cuba].sigmas2m = (float)(pot[Cuba].sigmas4s_acum / pot[Cuba].num_res_4s);

			pot[Cuba].sigmas2m_score = (float)(pot[Cuba].sigmas4s_score_acum / pot[Cuba].num_res_4s);

		} 
	    
		if (AVC.ParUser2[Cuba].HabCalcCoefAC eq VERDADEIRO and
			  AVC.ParUser2[Cuba].IntervCalcCA eq 2)
	    {
		  AVC.User2[Cuba].SigmaS_2m  = (float)(pot[Cuba].sigmas4s_score_acum / pot[Cuba].num_res_4s); 
		  AVC.User2[Cuba].SigmaL_2m  = (float)soma_score;

		  if(EST_AVC(Cuba).Est.ZeraCA eq VERDADEIRO)
		  {
			AVC.User3[Cuba].ContHistResCA = 0;
			EST_AVC(Cuba).Est.ZeraCA = FALSO;
		  }

		/* Grava historico de resistencia para calculo de coef. angular e correlacao */
//		  memmove(&pot[Cuba].HistRes2m[0],&pot[Cuba].HistRes2m[1],
  	//		(sizeof(pot[Cuba].HistRes2m)-sizeof(pot[Cuba].HistRes2m[0])));
		  memmove(&AVC.User3[Cuba].HistResCA[0],&AVC.User3[Cuba].HistResCA[1],
  			(sizeof(AVC.User3[Cuba].HistResCA)-sizeof(AVC.User3[Cuba].HistResCA[0])));

//		  pot[Cuba].HistRes2m[19] = pot[Cuba].res_score_2m*1e6;
		  AVC.User3[Cuba].HistResCA[19] = pot[Cuba].res_score_2m*1e6;
		  if(AVC.User3[Cuba].ContHistResCA < AVC.ParUser2[Cuba].NCicCoefAng)
		  	AVC.User3[Cuba].ContHistResCA++;

		  /* Calcula coeficiente angular e correlacao */
		  if( AVC.User3[Cuba].ContHistResCA >= AVC.ParUser2[Cuba].MinNCicCA)
		  {
		    sumx = 0;
			sumx2 = 0;
			sumy = 0;
			sumy2 = 0;
			sumxy = 0;
		    for (i=0;(i+(20-AVC.User3[Cuba].ContHistResCA))<20;++i)
  		    {
			  k = i+(20-AVC.User3[Cuba].ContHistResCA); 
    		  x[i]= i*0.5;
    		  sumx += x[i];  
    		  sumx2 += x[i]*x[i]; 
    		  sumy += AVC.User3[Cuba].HistResCA[k];
			  sumy2 += AVC.User3[Cuba].HistResCA[k]*AVC.User3[Cuba].HistResCA[k]; 
    		  sumxy += x[i]*AVC.User3[Cuba].HistResCA[k];
  		    }
 		    //(inclinacao da melhor reta (Least Square)
		    AVC.User2[Cuba].CoefAng = ((AVC.User3[Cuba].ContHistResCA*sumxy) - (sumx*sumy))/
           	  ((AVC.User3[Cuba].ContHistResCA*sumx2) - (sumx*sumx));

			//Calculo Coeficiente Correlacao
			if ((AVC.User3[Cuba].ContHistResCA*sumy2-(sumy*sumy))*(AVC.User3[Cuba].ContHistResCA*sumx2-(sumx*sumx)) < 0)
			  AVC.User2[Cuba].CoefCor = 0;
			else
			  AVC.User2[Cuba].CoefCor = fabs(((AVC.User3[Cuba].ContHistResCA*sumxy)-(sumx*sumy))/
				  (sqrt((AVC.User3[Cuba].ContHistResCA*sumy2-(sumy*sumy))*(AVC.User3[Cuba].ContHistResCA*sumx2-(sumx*sumx)))));
		  }
		  else
		  {
		    AVC.User2[Cuba].CoefAng = 0.0; 
			AVC.User2[Cuba].CoefCor = 0.0;
		  }
	    }	
		
		if( AVC.ParUser2[Cuba].HabilitaPFCBA eq VERDADEIRO and
			AVC.User2[Cuba].EstadoPFCBA eq 3
			//and EST_AVC(Cuba).Corrida eq FALSO and
			//EST_AVC(Cuba).EfeitoMove eq FALSO
			)
		{
			if(AVC.User3[Cuba].ContCicOver eq 0)
			{
				AVC.User3[Cuba].TendResOver = 0.0;
				EST_AVC(Cuba).Est.TendOverCancela = FALSO;				
			}
			
			if(EST_AVC(Cuba).EfeitoCorr eq VERDADEIRO or
				EST_AVC(Cuba).EfeitoQueb eq VERDADEIRO or
				EST_AVC(Cuba).TrataCruzeiro eq VERDADEIRO or
				EST_AVC(Cuba).TrataTPinos eq VERDADEIRO)
			{
				EST_AVC(Cuba).Est.TendOverCancela = VERDADEIRO;
			}

			AVC.User3[Cuba].ContCicOver++;
			AVC.User3[Cuba].TendResOver = (AVC.User3[Cuba].TendResOver * 
				(AVC.User3[Cuba].ContCicOver-1) + 
				(AVC.User2[Cuba].ResScore2m - AVC.User2[Cuba].ResScore2m_ant))/
				AVC.User3[Cuba].ContCicOver;
		}
		

	  } /* -- if fora leitura -- */

	  pot[Cuba].res_4s_acum = 0;
	  pot[Cuba].res_4s_score_acum = 0;
	  pot[Cuba].num_res_4s = 0;
	  pot[Cuba].num_res_05s = 0;
	  pot[Cuba].res_05s_acum = 0;
	  pot[Cuba].res_inst_acum = 0;
	  pot[Cuba].sigmal = 0;
	  pot[Cuba].sigmal_score = 0;
	  pot[Cuba].sigmas2m = 0;
	  pot[Cuba].sigmas2m_score = 0;
	  pot[Cuba].sigmas4s_acum = 0;
  	  pot[Cuba].sigmas4s_score_acum = 0;
  

	} /* -- if EstadoCuba -- */
  } /* -- for -- */

  correntebaixa = AVL.IAlvo - AVL.Par.DifCorMax; 
  correntealta = AVL.IAlvo + AVL.Par.DifCorMax; 

  if ( AVL.ICicContlMed < correntebaixa )
  {
	AVL.Trab.DifCorAlta = VERDADEIRO;
	AVL.Trab.HoraDifCorAlta = HoraAtualSec;
  }
  else
  {
    if ( AVL.ICicContlMed > correntealta )
	{
	  AVL.Trab.DifCorAlta = VERDADEIRO;
	  AVL.Trab.HoraDifCorAlta = HoraAtualSec;
	}
	else
	{
	  if ((AVL.Trab.HoraDifCorAlta + AVL.Par.EfeitoDifAlta*60) < HoraAtualSec)
	  {
	    AVL.Trab.DifCorAlta = FALSO;
	  }
	}
  }

} /* -- Calculo 2m -- */


/*
--------------------------------------------------------------------------------
| Calculo5m - 	Processa os calculos de 5 minutos necessarios para cada cuba.|
--------------------------------------------------------------------------------
*/
void Calculo5m(void)
{
  int Cuba,CubaOpe, i;

  for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
  {
	Cuba=ConvCubOperScore(CubaOpe);
	if (Cuba eq -1)
	  continue;

	if ((EST_AVC(Cuba).EstadoCuba ne CUBA_DESLIGADA) and
		(AlgControle(Cuba,ALG_SCORE01) eq VERDADEIRO))
	{
	  /* -- Verifica condicoes para tratamento da cuba -- */
	  if ((EST_AVC(Cuba).ForaLeitura eq FALSO) and
		  (AVL.LinhaHabilitada eq VERDADEIRO))
	  {
	    memmove(&AVC.User2[Cuba].TipOscilReg[0],&AVC.User2[Cuba].TipOscilReg[1],
  			(sizeof(AVC.User2[Cuba].TipOscilReg)-sizeof(AVC.User2[Cuba].TipOscilReg[0])));

	    AVC.User2[Cuba].TipOscilReg[5] = 2;

	    for(i=0; i<9; i++)
		{
		  if((9-i) < AVC.ParUser2[Cuba].NCCOscil) 
			if(pot[Cuba].vet_Oscil[i] > AVC.ParUser2[Cuba].LimOscilFort and
				AVC.User2[Cuba].TipOscilReg[5] eq 2)
			  AVC.User2[Cuba].TipOscilReg[5] = 2;
			else if (pot[Cuba].vet_Oscil[i] > AVC.ParUser2[Cuba].LimOscilFrac and   
				AVC.User2[Cuba].TipOscilReg[5] > 0)
			  AVC.User2[Cuba].TipOscilReg[5] = 1;
			else
			  AVC.User2[Cuba].TipOscilReg[5] = 0;
  		}

		if (AVC.ParUser2[Cuba].HabIncOscil eq VERDADEIRO)
		{ 
			AVC.User1[Cuba].TipoOscil = 2;
			for(i=0; i<5; i++)
			{
				if((5-i) < AVC.ParUser2[Cuba].NCRegOscil) 
				if(AVC.User2[Cuba].TipOscilReg[i] eq 2 and
						AVC.User1[Cuba].TipoOscil eq 2)
					AVC.User1[Cuba].TipoOscil = 2;
				else if(AVC.User2[Cuba].TipOscilReg[i] eq 1 and
						AVC.User1[Cuba].TipoOscil > 0)
					AVC.User1[Cuba].TipoOscil = 1;
				else
					AVC.User1[Cuba].TipoOscil = 0;
			}

			if(AVC.User1[Cuba].TipoOscil eq 2)
			{
				if(AVC.User2[Cuba].IncOscil eq 0.0)
				{
					AVC.User2[Cuba].HoraIncOscil = HoraAtualSec;
					SUPERV_AVC(Cuba).Sup.NumOscilDia++;
					SUPERV_AVC_TURNO(Cuba).Sup.NumOscilDia++;			   
				}
				EST_AVC(Cuba).Est.Oscilacao = VERDADEIRO;
				AVC.User2[Cuba].IncOscil += AVC.ParUser2[Cuba].IncOscilFor;
				if(AVC.User2[Cuba].IncOscil > AVC.ParUser2[Cuba].MaxIncOscil)
					AVC.User2[Cuba].IncOscil = AVC.ParUser2[Cuba].MaxIncOscil;
				GeraEvento(EV_OSCIL,Cuba,-1, SUPERV_AVC(Cuba).Sup.NumOscilDia,
					AVC.ParUser2[Cuba].IncOscilFor, AVC.User2[Cuba].IncOscil, "FORTE");
			}
			else if(AVC.User1[Cuba].TipoOscil eq 1)
			{
				if(AVC.User2[Cuba].IncOscil eq 0.0)
				{
					AVC.User2[Cuba].HoraIncOscil = HoraAtualSec;
					SUPERV_AVC(Cuba).Sup.NumOscilDia++;
					SUPERV_AVC_TURNO(Cuba).Sup.NumOscilDia++;			   
				}
				EST_AVC(Cuba).Est.Oscilacao = VERDADEIRO;
				AVC.User2[Cuba].IncOscil += AVC.ParUser2[Cuba].IncOscilFra;
				if(AVC.User2[Cuba].IncOscil > AVC.ParUser2[Cuba].MaxIncOscil)
					AVC.User2[Cuba].IncOscil = AVC.ParUser2[Cuba].MaxIncOscil;
				GeraEvento(EV_OSCIL,Cuba,-1, SUPERV_AVC(Cuba).Sup.NumOscilDia,
					AVC.ParUser2[Cuba].IncOscilFra, AVC.User2[Cuba].IncOscil, "FRACA");
			}
			else
			{
				if(EST_AVC(Cuba).Est.Oscilacao eq VERDADEIRO and
					AVC.User2[Cuba].IncOscil > 0)
				{
				AVC.User2[Cuba].IncOscil -= AVC.ParUser2[Cuba].DecrOscil;
				}
				if(AVC.User2[Cuba].IncOscil <= 0.0 and
					EST_AVC(Cuba).Est.Oscilacao eq VERDADEIRO)
				{
				EST_AVC(Cuba).Est.Oscilacao = FALSO;
				AVC.User2[Cuba].IncOscil = 0.0;
				GeraEvento(EV_OSCIL,Cuba,-1, SUPERV_AVC(Cuba).Sup.NumOscilDia,
					AVC.ParUser2[Cuba].DecrOscil, AVC.User2[Cuba].IncOscil, "FIM");
				}
			}

		}		
		else
		{
		  EST_AVC(Cuba).Est.Oscilacao = FALSO;
		  AVC.User1[Cuba].TipoOscil = 0;
		  AVC.User2[Cuba].IncOscil = 0.0;
		}

	  } /* -- if fora leitura -- */

	} /* -- if EstadoCuba -- */
  } /* -- for -- */

} /* -- Calculo 5m -- */

/*
--------------------------------------------------------------------------------
 MonitoraCalante - Programa para monitorar tensao de cubas desligadas
--------------------------------------------------------------------------------
*/
void MonitoraCalante()
{
  int CubaOpe, Cuba;

  for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
  {
	Cuba=ConvCubOperScore(CubaOpe);
	if (Cuba eq -1)
	  continue;
	
    if (EST_AVC(Cuba).EstadoCuba eq CUBA_DESLIGADA)
    {
	  if (AVC.Cleit[Cuba].Vinst > AVC.ParUser1[Cuba].TenLimCal)
	  {
		if(EST_AVC(Cuba).Est.TensaoCunha eq FALSO and AVC.User2[Cuba].HoraTenCal eq 0)
	    {
	      EST_AVC(Cuba).Est.TensaoCunha = VERDADEIRO;
	      AVC.User2[Cuba].HoraTenCal = HoraAtualSec;
	      AVC.User2[Cuba].HoraContSirene = HoraAtualSec;
	    }
		
		if (AVC.ParUser1[Cuba].TocaSirene > 0 and AVC.User2[Cuba].HoraContSirene > 0)
		{
		  if ( ((HoraAtualSec - AVC.User2[Cuba].HoraContSirene) > 
				( AVC.ParUser1[Cuba].TocaSirene * ((AVL.INominal * AVC.ParUser1[Cuba].TenLimCal) / 
				( fabs(AVL.ICicContlMed * AVC.Cleit[Cuba].Vinst))))) and
				EST_AVC(Cuba).Est.SireneCunha eq FALSO)
		  {
		  	EST_AVC(Cuba).Est.SireneCunha = VERDADEIRO;
			AVC.User2[Cuba].HoraSireneCunha = HoraAtualSec;
			ComandaSirene(Cuba,LIGAR);
			pot[Cuba].Sirene = 1;
	 	    GeraEvento(EV_SIRENE,-1,-1,"TENSAO","ALTA",
				ConvCubScoreOper(Cuba),AVC.Cleit[Cuba].Vinst, AVL.ICicContlMed);			
		  }
		  
		/* -- Liga e Desliga a Sirene para evitar queima da Sirene -- */
		  if (EST_AVC(Cuba).Est.SireneCunha eq VERDADEIRO)
		  {
			if((AVC.User2[Cuba].HoraSireneCunha + 
				AVC.ParUser1[Cuba].IntervSirene) < HoraAtualSec)
			{
			  if (pot[Cuba].Sirene eq 1)
			  {
			  	ComandaSirene(Cuba, DESLIGAR);
				pot[Cuba].Sirene = 0;		
			  }
			  else
			  {
			  	ComandaSirene(Cuba, LIGAR);
				pot[Cuba].Sirene = 1;		
			  }			
			  AVC.User2[Cuba].HoraSireneCunha = HoraAtualSec; 
			}
		  }
		}
		if (AVC.ParUser1[Cuba].DesligaSala > 0 and
			AVC.User2[Cuba].HoraContSirene > 0 and
			EST_AVC(Cuba).Est.TensaoCunha eq VERDADEIRO and
			EST_AVC(Cuba).Est.SireneCunha eq VERDADEIRO)
		{
		  if ( ((HoraAtualSec - AVC.User2[Cuba].HoraContSirene) > 
				( AVC.ParUser1[Cuba].DesligaSala * ((AVL.INominal * AVC.ParUser1[Cuba].TenLimCal) / 
				( fabs(AVL.ICicContlMed * AVC.Cleit[Cuba].Vinst))))) and
				EST_AVC(Cuba).Est.SireneCunha eq VERDADEIRO and
				EST_AVC(Cuba).Est.DesligaCunha eq FALSO)
		  {
			/* Logica para desligar sala */
	 	    GeraEvento(EV_DESLIGASALA,-1,-1,"TENSAO","ALTA",
				ConvCubScoreOper(Cuba),AVC.Cleit[Cuba].Vinst, AVL.ICicContlMed);
			ComandaSaidaORem(0,LIGAR, 21, 100);
			ComandaSaidaORem(1,LIGAR, 21, 100);
			EST_AVC(Cuba).Est.DesligaCunha = VERDADEIRO;
		  }
		}		
	  }
	  else 
	  {

		if (EST_AVC(Cuba).Est.SireneCunha eq VERDADEIRO)
		{
	  	  ComandaSirene(Cuba, DESLIGAR);
	      EST_AVC(Cuba).Est.SireneCunha = FALSO;
  		  pot[Cuba].Sirene = 0;		
	      AVC.User2[Cuba].HoraContSirene = 0;
		}
		
		if (EST_AVC(Cuba).Est.DesligaCunha eq VERDADEIRO)
		{
		  EST_AVC(Cuba).Est.DesligaCunha = FALSO;
		}
	
		if ( (AVC.User2[Cuba].HoraTenCal + (AVC.ParUser1[Cuba].EfeitoTenCal * 60) < HoraAtualSec ) and
				EST_AVC(Cuba).Est.TensaoCunha eq VERDADEIRO)
	  	{	    
          EST_AVC(Cuba).Est.TensaoCunha = FALSO;	  
	      AVC.User2[Cuba].HoraTenCal = 0;	
	  	}	
	  }
    }
	else
	{
      EST_AVC(Cuba).Est.TensaoCunha = FALSO;	  
	  EST_AVC(Cuba).Est.SireneCunha = FALSO;
	  AVC.User2[Cuba].HoraTenCal = 0;	
      EST_AVC(Cuba).Est.DesligaCunha = FALSO;	  	
	}
  }  	

}/* -- Fim MonitoraCalante -- */

/*
--------------------------------------------------------------------------------
 MovQuebProg - Prog. para aumentar a precisao da subida da quebrada programada
--------------------------------------------------------------------------------
*/
void MovQuebProg(int Cuba)
{

float DuracaoMov, RErro, VCicCont, VInst, VAlvo;
int DurInt;

  if (AVC.ParUser1[Cuba].HabPrecMovQueb eq VERDADEIRO)
  {
    if ( ((HoraAtualSec - AVC.Cleit[Cuba].HoraUltQueb) < 120) and
	   (EST_AVC(Cuba).Ea eq FALSO) and (EST_AVC(Cuba).Est.InibeMovDB eq FALSO) )
	{	
	  pot[Cuba].NumRes4sQueb++;
	  pot[Cuba].MediaRes4sQueb = ((pot[Cuba].MediaRes4sQueb * (pot[Cuba].NumRes4sQueb-1)) +
									pot[Cuba].res_4s_score) / pot[Cuba].NumRes4sQueb;

	  if((pot[Cuba].NumRes4sQueb eq AVC.ParUser1[Cuba].NumCicRes4s) and
			(pot[Cuba].NumMov < AVC.ParUser1[Cuba].NumMovPrecQueb))
	  {

  		if (EST_AVC(Cuba).Ea eq VERDADEIRO)
    	  RErro = 0.0;
  		else
		  RErro = AVC.Ccont[Cuba].RAlvo - pot[Cuba].MediaRes4sQueb;
		  
		if(RErro > 0)
		{
  		  if ((EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL) and
	  	  (EST_AVC(Cuba).ChaveAutMan eq AUTOMATICO) and
	  	  (EST_AVC(Cuba).ChaveLocRem eq REMOTO) and
	  	  (EST_AVC(Cuba).ForaLeitura eq FALSO) and
	  	  (EST_AVC(Cuba).Est.ReleTempoMM eq FALSO) and
	  	  (EST_AVC(Cuba).InibeControleUsu eq FALSO) and
	  	  (AVL.LinhaHabilitada eq VERDADEIRO) and
	  	  (EST_AVC(Cuba).EfeitoEa eq FALSO) and
 		  (EST_AVC(Cuba).EfeitoCorr eq FALSO) )
		  {
			if ((RErro >= AVC.Param[Cuba].BandaMortaInf) and
				(RErro < AVC.Ccont[Cuba].BandaContInfAtual))
			{
			  DuracaoMov=AVC.ParUser1[Cuba].KPcQueb*(RErro/AVC.Ccont[Cuba].Kcpwm);
	  		  if (DuracaoMov < (float)AVC.Param[Cuba].DurMovCimaMin and
					DuracaoMov >= 0.7)
	    		DuracaoMov=AVC.Param[Cuba].DurMovCimaMin;
	   		  else
	    		if (DuracaoMov > (float)AVC.Param[Cuba].DurMovCimaMax)
		  		  DuracaoMov=(float)AVC.Param[Cuba].DurMovCimaMax;

			  if(DuracaoMov >= 0.1)
			  {
		      	/* -- comanda a movimentacao do anodo -- */
    		  	DurInt=(int)(DuracaoMov*BASE_TEMPO_REMOTA);
    		  	if (MoveAnodo(Cuba,DurInt,SUBIR_ANODO) eq STATUS_OK)
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

	   			  /* -- Gera evento de movimentacao automatica do anodo -- */
			  	  GeraEvento(SUBIDA_AUT_ANODO,Cuba,-1,"PMovQueb",
			  	  (float)DurInt/(float)BASE_TEMPO_REMOTA,VCicCont,VInst,VAlvo);
				  AVC.Ccont[Cuba].HoraUltMove = HoraAtualSec;
				  pot[Cuba].NumMov++;
		        }
			  }
			}
		  }
		}	
		pot[Cuba].NumRes4sQueb = 0;
		pot[Cuba].MediaRes4sQueb = 0;
	  }						
	}
	else
	{
	  pot[Cuba].NumMov = 0;
	  pot[Cuba].NumRes4sQueb = 0;
	  pot[Cuba].MediaRes4sQueb = 0;
	}
	
  }
}/* -- Fim MovQuebProg -- */

/*
--------------------------------------------------------------------------------
 VerificaChaveLocRem - Prog. para verificar estado da chave local remoto
--------------------------------------------------------------------------------
*/
void VerificaChaveLocRem()
{

	int CubaOpe, Cuba;

	for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
  	{
		Cuba=ConvCubOperScore(CubaOpe);
		if (Cuba eq -1)
			continue;

		/* ----- Verifica Chave Local Remoto da Cuba ------
			------- Logica para diminuir estouro eventos ------- */

		if ((AVC.Ccont[Cuba].HoraUltMove + 150) > HoraAtualSec)
			AVC.User2[Cuba].ContEvChaves = 0;
		if(AVC.User2[Cuba].ContEvChaves > 5)
		{
			if ( ((AVC.Cleit[Cuba].HoraUltSelMan + 1800) < HoraAtualSec))
			{
				if (((AVC.Cleit[Cuba].EstadoIO >> (AVC.Abs[Cuba].BitChaveLocRem - 1)) 
					andb 1) eq 0)
        		{
					if (EST_AVC(Cuba).ChaveLocRem ne REMOTO)
					{
						EST_AVC(Cuba).ChaveLocRem=REMOTO;
						GeraEvento(EV_CHAVE_REMOTO,Cuba,-1,"RETORNO","FALHA",
						0,0,0);
					}
        		}
				else
				{
					if (EST_AVC(Cuba).ChaveLocRem ne LOCAL)
					{
						EST_AVC(Cuba).ChaveLocRem=LOCAL;
						GeraEvento(EV_CHAVE_LOCAL,Cuba,-1,"RETORNO","FALHA",
						0,0,0);
					}
				}
	   			AVC.User2[Cuba].ContEvChaves = 0;
	  		}
    	}
		else
		{
			if ( ((AVC.Cleit[Cuba].HoraUltSelMan + 600) < HoraAtualSec))
			{
				AVC.User2[Cuba].ContEvChaves = 0;	
			}
		} 
  	}
}/* -- Fim VerificaChaveLocRem -- */


/*
--------------------------------------------------------------------------------
 SopraChamine - Prog. para soprar chamine apos quebrada programada
--------------------------------------------------------------------------------
*/
void SopraChamine()
{

	int CubaOpe, Cuba;
  	float VCicCont;

	for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
	{
		Cuba=ConvCubOperScore(CubaOpe);
		if (Cuba eq -1)
			continue;
		
		if (AVC.ParUser1[Cuba].TSopraChamine > 0)
		{

			#ifdef	BOOSTER_CORRENTE
				VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVC.Ccont[Cuba].INominalCuba+
				AVC.Param[Cuba].Bemf;
			#else
				VCicCont=AVC.CcontMcp[Cuba].RCicContlBruta*AVL.INominal+
				AVC.Param[Cuba].Bemf;
			#endif

			if ((AVC.Cleit[Cuba].HoraUltQueb + 
				(AVC.ParUser1[Cuba].IntervSoproQueb * 60)) > HoraAtualSec and
					EST_AVC(Cuba).Est.SinalChamine eq FALSO and
					EST_AVC(Cuba).Est.SopraChamine eq FALSO)
			{
				EST_AVC(Cuba).Est.SopraChamine = VERDADEIRO;
			}
			else if(EST_AVC(Cuba).Est.SopraChamine eq VERDADEIRO and 
						EST_AVC(Cuba).Est.SinalChamine eq FALSO and 
						(AVC.Cleit[Cuba].HoraUltQueb +								   
						(AVC.ParUser1[Cuba].IntervSoproQueb * 60)) < HoraAtualSec)
			{
				ComandaSaidaRem(Cuba, LIGAR, AVC.Abs[Cuba].BitSopro, 
							AVC.ParUser1[Cuba].TSinalizaSopro * BASE_TEMPO_REMOTA);	

				// GeraEvento(SOPROU,Cuba,-1, "Automat","Sinaliza",VCicCont,AVC.Cleit[Cuba].Vinst,AVC.Ccont[Cuba].VAlvo);

				EST_AVC(Cuba).Est.SinalChamine = VERDADEIRO;	
			} 
			
			if(EST_AVC(Cuba).Est.SinalChamine eq VERDADEIRO and
				EST_AVC(Cuba).Est.SopraChamine eq VERDADEIRO and
				(AVC.Cleit[Cuba].HoraUltQueb + 
				(AVC.ParUser1[Cuba].IntervSoproQueb * 60) +
				AVC.ParUser1[Cuba].IntervSinalSopro) < HoraAtualSec)
			{
				ComandaSaidaRem(Cuba, LIGAR, AVC.Abs[Cuba].BitSopro, 
							AVC.ParUser1[Cuba].TSopraChamine * BASE_TEMPO_REMOTA);	

				// GeraEvento(SOPROU,Cuba,-1, "Automat","Chamine",VCicCont,AVC.Cleit[Cuba].Vinst,AVC.Ccont[Cuba].VAlvo);

				EST_AVC(Cuba).Est.SinalChamine = FALSO;
				EST_AVC(Cuba).Est.SopraChamine = FALSO;
			}
		}

	}
}/* -- Fim SopraChamine -- */


/*
--------------------------------------------------------------------------------
 SinalizaAlarmeSala - Prog. para acionar sirenes no ligamento e desligamento
--------------------------------------------------------------------------------
*/
void SinalizaAlarmeSala(void)
{
	int BitMask = 1;
  	int i;

	if (AVL.Trab.AlarmeSala eq 0 and AVL.Trab.HoraAlarmeSala > 0) /* Desativa */
	{
		for (i=0; i <=32 ; i++)
		{
			if(((AVL.Par.BitSirenesATNCA1 >> i) andb BitMask) eq 1)
			{
				ComandaSaidaORem(0,DESLIGAR,i+1, -1);	  
			}
			if(((AVL.Par.BitSirenesATNCA2 >> i) andb BitMask) eq 1)
			{
				ComandaSaidaORem(1,DESLIGAR,i+1, -1);	  
			}

		} 

		AVL.Trab.HoraAlarmeSala = 0;
		AVL.Trab.AlarmeSala = 0;
		AVL.Trab.EstadoSireneSala = FALSO;
		DifHoraSirene = 0;
	}	
	else if (AVL.Trab.AlarmeSala eq 1) /* Sinaliza religamento de sala */
	{
		if ( HoraAtualSec < (AVL.Trab.HoraAlarmeSala + AVL.Par.TmpAlarmeSirenes) and AVL.Trab.EstadoSireneSala eq FALSO)
		{
			for (i=0; i <=32 ; i++)
			{
				if(((AVL.Par.BitSirenesATNCA1 >> i) andb BitMask) eq 1)
				{
					ComandaSaidaORem(0,LIGAR,i+1, -1);	  
				}
				if(((AVL.Par.BitSirenesATNCA2 >> i) andb BitMask) eq 1)
				{
					ComandaSaidaORem(1,LIGAR,i+1, -1);	  
				}
			} 
			AVL.Trab.EstadoSireneSala = VERDADEIRO;
		}
		if (HoraAtualSec > (AVL.Trab.HoraAlarmeSala + AVL.Par.TmpAlarmeSirenes) and AVL.Trab.EstadoSireneSala eq VERDADEIRO)
		{
			for (i=0; i <=32 ; i++)
			{
				if(((AVL.Par.BitSirenesATNCA1 >> i) andb BitMask) eq 1)
				{
					ComandaSaidaORem(0,DESLIGAR,i+1, -1);	  
				}
				if(((AVL.Par.BitSirenesATNCA2 >> i) andb BitMask) eq 1)
				{
					ComandaSaidaORem(1,DESLIGAR,i+1, -1);	  
				}
			} 
			AVL.Trab.HoraAlarmeSala = 0;
			AVL.Trab.AlarmeSala = 0;
			AVL.Trab.EstadoSireneSala = FALSO;
			DifHoraSirene = 0;
		}
	}
	else if (AVL.Trab.AlarmeSala eq 2) /* Sinaliza desligamento de sala */
	{
		if ( HoraAtualSec < (AVL.Trab.HoraAlarmeSala + AVL.Par.TmpAlarmeSirenes))
		{
			if ( ((HoraAtualSec - AVL.Trab.HoraAlarmeSala) % 5) eq 0 and 
					DifHoraSirene < (HoraAtualSec - AVL.Trab.HoraAlarmeSala))
			{
				if (AVL.Trab.EstadoSireneSala eq FALSO)
				{
					for (i=0; i <=32 ; i++)
					{
						if(((AVL.Par.BitSirenesATNCA1 >> i) andb BitMask) eq 1)
						{
							ComandaSaidaORem(0,LIGAR,i+1, -1);	  
						}
						if(((AVL.Par.BitSirenesATNCA2 >> i) andb BitMask) eq 1)
						{
							ComandaSaidaORem(1,LIGAR,i+1, -1);	  
						}
					} 
					AVL.Trab.EstadoSireneSala = VERDADEIRO;
					DifHoraSirene = HoraAtualSec - AVL.Trab.HoraAlarmeSala;
				}
				else
				{
					for (i=0; i <=32 ; i++)
					{
						if(((AVL.Par.BitSirenesATNCA1 >> i) andb BitMask) eq 1)
						{
							ComandaSaidaORem(0,DESLIGAR,i+1, -1);	  
						}
						if(((AVL.Par.BitSirenesATNCA2 >> i) andb BitMask) eq 1)
						{
							ComandaSaidaORem(1,DESLIGAR,i+1, -1);	  
						}
					} 	
					AVL.Trab.EstadoSireneSala = FALSO;
					DifHoraSirene = HoraAtualSec - AVL.Trab.HoraAlarmeSala;
				}
			}
		}
		else
		{			
			for (i=0; i <=32 ; i++)
			{
				if(((AVL.Par.BitSirenesATNCA1 >> i) andb BitMask) eq 1)
				{
					ComandaSaidaORem(0,DESLIGAR,i+1, -1);	  
				}
				if(((AVL.Par.BitSirenesATNCA2 >> i) andb BitMask) eq 1)
				{
					ComandaSaidaORem(1,DESLIGAR,i+1, -1);	  
				}
			} 
			AVL.Trab.EstadoSireneSala = FALSO;
			AVL.Trab.HoraAlarmeSala = 0;
			AVL.Trab.AlarmeSala = 0;
			DifHoraSirene = 0;
		}
	}  
}/* -- Fim SinalizaAlarmeSala -- */

/*
--------------------------------------------------------------------------------
 AlarmeDesvio - Programa para monitorar desvio de tensao prolongado
--------------------------------------------------------------------------------
*/
void AlarmeDesvio()
{
  int CubaOpe, Cuba;

  for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe++)
  {
	Cuba=ConvCubOperScore(CubaOpe);
	if (Cuba eq -1)
	  continue;
	
    if (EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL and
		AVC.ParUser1[Cuba].TMaxDesvio > 0 and
		EST_AVC(Cuba).DesvioTensao eq VERDADEIRO and
		(HoraAtualSec - AVC.Ccont[Cuba].HoraUltVDesv) > AVC.ParUser1[Cuba].TMaxDesvio and
		EST_AVC(Cuba).Est.AlarmeDesvio eq FALSO)
    {
		ComandaSirene(Cuba,LIGAR);
		EST_AVC(Cuba).Est.AlarmeDesvio = VERDADEIRO;
    }
	else
	{	
	  if (EST_AVC(Cuba).Est.AlarmeDesvio eq VERDADEIRO and
			(EST_AVC(Cuba).DesvioTensao eq FALSO or
			AVC.ParUser1[Cuba].TMaxDesvio eq 0))
	  {
		ComandaSirene(Cuba,DESLIGAR);		
		EST_AVC(Cuba).Est.AlarmeDesvio = FALSO;
	  }
	}
  }  	

}/* -- Fim AlarmeDesvio -- */



/* -- Fim McpCba.c -- */

