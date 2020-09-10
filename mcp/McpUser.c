/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.1

	PROJETO		: ALBRAS - ALUMINIO BRASILEIRO SA

	SISTEMA		: PROTOTIPO PARA UMA SECAO DA REDUCAO II

	ARQUIVO		: McpUser.c

	CONTEUDO	: Esqueleto de exemplo de um programa de controle ativado pelo
                  Modulo de Calculos Primarios - MCP.
                  E'  ativado  pelo modulo de calculos primarios (MCP) a cada
                  ciclo de leitura, na desativacao de linha e na  partida  do
				  sistema.
				  OBS.: Para ser ativado pelo Mcp deve ser instalado no Score
						atraves do programa InstalaCtrl. Pode ser instalado
						com o sistema ativado (partida a quente) ou nao. Caso
						se deseje desativa-lo sem desativar o sistema deve-se
						utilizar tambem o programa InstalaCtrl ao inves de
						simplesmente dar um slay.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	29/11/93

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
Data     | Descricao                                            | Autor 
-------------------------------------------------------------------------------
20/11/95 | Alteracoes nos exemplos para o prototipo da Albras   | Leonel
-------------------------------------------------------------------------------
******************************************************************************/
/*
-------------------------------------------------------------------------------
                           Definicao de compilacao condicional
-------------------------------------------------------------------------------
*/
#define		PROGRAMA_PRINCIPAL

#define		EXEMPLO_INICIALIZACAO		1
#define		COMANDA_SAIDA_REMOTA		1

/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include	<McpUser.h>
#ifdef	ATIVA_DEPURACAO
  #include	<stdio.h>
#endif

/*
-------------------------------------------------------------------------------
                           Variaveis Globais
-------------------------------------------------------------------------------
*/
/* -- Apontadores para as tabelas comuns -- */
#include	<VarsComum.h>

/*
-------------------------------------------------------------------------------
	Main - McpUser - Exemplo de tarefa de controle ativada pelo MCP
-------------------------------------------------------------------------------
*/
void main(int argc, char *argv[])
{
  int 			TidMcp;
  t_mens_padrao	Mens;
  t_boolean		Responde;
  t_boolean		Partida;
  t_boolean		PartidaQuente;

  /* -- Recebe endereco da area de dados comum ao processo -- */
  Reply(Receive(0, &Comum, sizeof(Comum)), 0, 0);
      
  /* -- Inicializa apontadores para tabelas globais -- */

  InitVarsComum();

  /* -- Consiste Cuba inicial e cuba final a tratar -- */
  PartidaQuente=ConsisteArgs(argc,argv);

  if (PartidaQuente eq VAL_VERDADEIRO)
  { /* Modulo ativado com o sistema ja' rodando, nao sera' enviada mensagem
	   de inicializacao pelo Mcp. Logo inicializa oque for necessario */

DEPURA(printf("McpUser->Partida a quente\n");)
	/* -- Inicializa todas as variaveis de trabalho e executa os procedimentos 
		 necessarios a inicializacao do calculos. -- */
	IniMcpUser();
	/* -- Marca que a proxima ativacao de inicializacao nao sera' a primeira -- */
	Partida=VAL_FALSO;
  }
  else
	/* -- Marca que a proxima ativacao de inicializacao sera' a primeira -- */
	Partida=VAL_VERDADEIRO;

  /* -- Guarda hora atual em secundos -- */
  HoraAtualSec=time(NULL)/TIMES_PER_SEC; /* -- segs. apartir 1/1/1980 -- */

  loop			/*  Loop eterno */
  {
	Responde=VAL_VERDADEIRO;
	/* -- Recebe ativacao do MCP -- */
	if((TidMcp = Receive(0, &Mens, sizeof(Mens))) <= 0)
	  EmiteErroFor(TODOS_DISPOSITIVOS,"Erro receive TidMcp=%x",TidMcp);

	/* -- Guarda hora atual em secundos -- */
    HoraAtualSec=time(NULL)/TIMES_PER_SEC; /* -- segs. apartir 1/1/1980 -- */

	switch(Mens.Acao)
	{
	  case INICIALIZACAO:
DEPURA(printf("McpUser->Inicializacao\n");)
		/* -- Inicializa todas as variaveis de trabalho e executa os procedimentos 
			 necessarios a inicializacao do calculos. -- */
		IniMcpUser();
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
		break;
	
      case CICLO_LEITURA:	
DEPURA(printf("McpUser->Ciclo Leitura\n");)
		ProcessaCubas();
		break;

	  case DESABILITOU_LINHA:
		/* -- Caso necessario, executa procedimentos para linha desabilitada -- */
		break;
	
	  default:
		EmiteErroFor(TODOS_DISPOSITIVOS,"Erro Fatal - Acao nao tratada %d",
				     Mens.Acao);
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
	IniMcpUser - Inicializacao de todas as variaveis relacionadas a este modulo
--------------------------------------------------------------------------------
*/
void IniMcpUser(void)

{
  int Cuba, CubaOpe;

  /* -- Inicializar as variaveis globais de trabalho do modulo -- */

  /* -- Inicializar todas as variaveis da base de dados que forem de
        responsabilidade deste modulo (variaveis alteradas por este modulo).
		Alocar semaforo da tabela correspondente da base de dados antes de
		acessar as variaveis, conforme exemplo abaixo -- */
#ifdef	EXEMPLO_INICIALIZACAO
/************************* exemplo ***********************/
  /* -- Variavel da tabela de linha -- */
  AlocaSemaf(SEMAF_AVL);
  AVL.ResAvlGer[0] = 1;
  LiberaSemaf(SEMAF_AVL);

  /* -- Inicializa variaveis para cada cuba -- */
  AlocaSemaf(SEMAF_AVC);
  for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe=ProxCubaOpe(CubaOpe))
  {
	/* -- Converte numero de operacao da cuba para indice na tabela -- */
	Cuba=ConvCubOperScore(CubaOpe);

	AVC.Cleit[Cuba].ResLAvc[0] = 0;
	AVC.Cleit[Cuba].ResLAvc[1] = 0;
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

  AlocaSemaf(SEMAF_AVC);
  for(CubaOpe=CubaIni; CubaOpe<=CubaFim; CubaOpe=ProxCubaOpe(CubaOpe))
  {
	/* -- Converte numero de operacao da cuba para indice na tabela -- */
	Cuba=ConvCubOperScore(CubaOpe);
DEPURA(printf("McpUser->Trata cuba %d [%d]\n",CubaOpe,Cuba);)
	/* -- Verifica condicoes para tratamento da cuba -- */
	if ((EST_AVC(Cuba).ForaLeitura eq FALSO) and
		(AVL.LinhaHabilitada eq VERDADEIRO))
	{
	  if (EST_AVC(Cuba).EstadoCuba eq CUBA_NORMAL)
	  {
		/* -- Processa os calculos relativos a cada cuba -- */

#ifdef	COMANDA_SAIDA_REMOTA
		/****** exemplo de codigo para ligar uma saida da remota durante
		        10 segundos *******/
		/*-- Verifica condicoes para acionamento --*/
		if( EST_AVC(Cuba).ChaveAutMan eq AUTOMATICO )
		{ /* -- computador esta em modo automatico -- */
		  if( EST_AVC(Cuba).ChaveLocRem eq REMOTO )
		  { /* -- chave do painel esta em modo remoto -- */
			int BitAcao,Tempo;

			/* -- Bit a ser acionado (comecando de 1) -- */
			BitAcao = AVC.Abs[Cuba].BitResOut1;
			Tempo = 10*BASE_TEMPO_REMOTA; /* -- tempo na base de tempo da remota. Se tempo = 0 apenas
						liga a saida sem temporizar. Para desligar mudar acao
						para DESLIGAR ou inves de LIGAR -- */
			if (ComandaSaidaRem(Cuba,LIGAR,BitAcao,Tempo) ne 0)
			  ;/* -- Falha no acionamento da saida -- */
		  }
		}
		/**** fim exemplo de codigo para acionar uma saida na remota *****/
#endif
	  } /* -- if EstadoCuba -- */
	} /* -- if fora leitura -- */
  } /* -- for -- */
  LiberaSemaf(SEMAF_AVC);
} /* -- ProcessaCubas -- */

/* -- Fim McpUser.c -- */
