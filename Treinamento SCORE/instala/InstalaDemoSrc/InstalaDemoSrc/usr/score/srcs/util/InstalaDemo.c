/******************************************************************************

			                  ACCENTURE - APAS
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 5.0

	PROJETO		: CBA

	SISTEMA		: Salas 125 KA I a VII

	ARQUIVO		: InstalaDemo.c

	CONTEUDO	: Programa para alterar os drivers do Score para os de
	              demonstracao transformando uma base de dados de runtime
				  em base de dados de demonstracao.
				  Altera Drvsad para DrvsadDemo, Watchdog para WatchdogDemo
				  e RedeAtn7 para RedeAtn7demo.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 1.0			-		DATA	:	21/09/2012

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
$Id: InstalaDemo.c,v 1.1.4.2 2012/10/16 12:32:30 leo Exp $

$Log: InstalaDemo.c,v $
Revision 1.1.4.2  2012/10/16 12:32:30  leo
Incluida configuracao dos nodos 3 e 4 como nodos de operacao atraves de
parametro ( -o ). Se definido parametro na chamada configura os nodos alem
de alterar programas para demo.

Revision 1.1.4.1  2012/09/28 17:10:17  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

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
#include	<string.h>
#include	<sys/name.h>
#include	<process.h>
#include	<fcntl.h>
#include	<signal.h>
#include	<Score.h>
#include	<RelGraf.h>
#include	<Prototipos.h>
#include	<VarsComum.h>

/*
-------------------------------------------------------------------------------
						   Prototipos
-------------------------------------------------------------------------------
*/
int IniBdScore(void);
void InstalaDemo(t_boolean Operacao);
void InstalaModulo(int Modulo, char *NomeMod);
void SalvaModulo(int Modulo);
t_boolean ConsisteArgs(int Argc,char *Argv[]);
void SalvaNodos(void);

/*
-------------------------------------------------------------------------------
						   Principal
-------------------------------------------------------------------------------
*/
void main(int argc,char *argv[])
{
  t_boolean operacao_demo;

  operacao_demo=ConsisteArgs(argc,argv);
  printf("Alterando base de dados para demonstracao. Aguarde...\n");
  if (IniBdScore())
  {
    printf("Sistema Score ativo! Desative-o primeiro!\n");
	exit(1);
  }
  InstalaDemo(operacao_demo);
  printf("Base de dados convertida para demonstracao.\n");
}

/*
--------------------------------------------------------------------------------
| ConsisteArgs - Verifica se e' para inicializar nodos de operacao como 3 e 4. |
|                Retorna verdadeiro se sim  (switch -o). Nao retorna se erro.  |
--------------------------------------------------------------------------------
*/
t_boolean ConsisteArgs(int Argc,char *Argv[])
{
  t_boolean operacao;

  operacao=VAL_FALSO;
  if (Argc eq 2)
  {
	if (strcmp(Argv[1],"-o") eq 0)
		operacao=VAL_VERDADEIRO;
	  else
	  {
		fprintf(stderr,"Use: %s [-o] onde: -o=configura nodos 3 e 4 como operacao\n",Argv[0]);
		exit(EXIT_FAILURE);
	  }
  }
  else
	if (Argc ne 1)
	{
	  fprintf(stderr,"Use: %s [-o] onde: -o=configura nodos 3 e 4 como operacao\n",Argv[0]);
	  exit(EXIT_FAILURE);
	}

  return(operacao);
}


/*
--------------------------------------------------------------------------------
| IniBdScore - Localiza ou instala base de dados do Score. Retorna verdadeiro  |
|			   se o score esta ativado e falso caso contrario.                 |
--------------------------------------------------------------------------------
*/
int IniBdScore(void)
{
  int score_ativo;

  if (qnx_name_locate(My_nid,"Atan/Score/Controle",sizeof(int),NULL) ne -1)
  {
	if (PegaComum (&Comum))
	{
	  fprintf(stderr,"Falha no PegaComum!\n");
	  exit(EXIT_FAILURE);
	}
	score_ativo=VERDADEIRO;
  }
  else
  {
	if (CriaAreaGlobal(0,&Comum))
	{
	  fprintf(stderr,"Falha cria area global!\n");
	  exit(EXIT_FAILURE);
	}
	score_ativo=FALSO;
  }
  return(score_ativo);
}

/*
--------------------------------------------------------------------------------
| InstalaDemo - Instala modulos de demo no lugar dos de runtime                |
--------------------------------------------------------------------------------
*/
void InstalaDemo(t_boolean Operacao)
{
  switch (Comum->IdentReducao)
  {
  	case 2: /* Atn1.4 e atn7 */
	case 3: /* Atn1.4 e atn7 */
	case 4: /* Atn1.4 e atn7 */
	  InstalaModulo(DRVSAD, "/score/exec/DrvsadDemo");
	  InstalaModulo(WATCHDOG, "/score/exec/WatchdogDemo");
	  InstalaModulo(REDE0, "/score/exec/RedeAtn2 1 0 /dev/con4 1");
	  break;
	case 1: /* sala I - Com atn8 */
	  InstalaModulo(DRVSAD, "/score/exec/DrvAnaAtn8Demo");
//	  InstalaModulo(TABRELGRAF, "/score/exec/TabRelGrafDemo");
	  InstalaModulo(WATCHDOG, "/score/exec/WatchdogDemo");
	  InstalaModulo(REDE0, "/score/exec/RedeAtn7demo 0");
	  InstalaModulo(REDE1, "/score/exec/RedeAtn7demo 1");
	  InstalaModulo(REDE2, "/score/exec/RedeAtn7demo 2");
	  break;
	case 7: /* sala V - Com atn8 */
	  InstalaModulo(DRVSAD, "/score/exec/DrvAnaAtn8Demo");
//	  InstalaModulo(TABRELGRAF, "/score/exec/TabRelGrafDemo");
	  InstalaModulo(WATCHDOG, "/score/exec/WatchdogDemo");
	  InstalaModulo(REDE0, "/score/exec/RedeAtn7demo 0");
	  InstalaModulo(REDE1, "/score/exec/RedeAtn7demo 1");
	  InstalaModulo(REDE2, "/score/exec/RedeAtn7demo 2");
	  InstalaModulo(REDE3, "/score/exec/RedeAtn7demo 3");
	  break;
	case 8: /* sala VI - Com atn8 */
	  InstalaModulo(DRVSAD, "/score/exec/DrvAnaAtn8Demo");
//	  InstalaModulo(TABRELGRAF, "/score/exec/TabRelGrafDemo");
	  InstalaModulo(WATCHDOG, "/score/exec/WatchdogDemo");
	  InstalaModulo(REDE0, "/score/exec/RedeAtn7demo 0");
	  InstalaModulo(REDE1, "/score/exec/RedeAtn7demo 1");
	  break;
	case 9: /* sala VII - Com atn8 */
	  InstalaModulo(DRVSAD, "/score/exec/DrvAnaAtn8Demo");
//	  InstalaModulo(TABRELGRAF, "/score/exec/TabRelGrafDemo");
	  InstalaModulo(WATCHDOG, "/score/exec/WatchdogDemo");
	  InstalaModulo(REDE0, "/score/exec/RedeAtn7demo 0");
	  InstalaModulo(REDE1, "/score/exec/RedeAtn7demo 1");
	  InstalaModulo(REDE2, "/score/exec/RedeAtn7demo 2");
	  break;
	default:
	  printf("\nSala nao tratada! Red=%d \n", Comum->IdentReducao);
	  exit(EXIT_FAILURE);
	  break;
  }
  if (Operacao)
  { /* Forca nodos 3 e 4 como nodos de operacao */
  	Comum->NodoOpRede[0]=3;
  	Comum->NodoOpRede[1]=4;
	SalvaNodos();
	printf("Nodos 3 e 4 definidos como nodos de operacao!\n");
  }
}

/*
--------------------------------------------------------------------------------
| InstalaModulo - Instala parametros do modulo na base de dados.               |
--------------------------------------------------------------------------------
*/
void InstalaModulo(int Modulo, char *NomeMod)
{
  PDescProg->Prog[Modulo].TidProg=-1;
  strcpy(PDescProg->Prog[Modulo].NomeProg,NomeMod);
  SalvaModulo(Modulo);
}

/*
--------------------------------------------------------------------------------
| SalvaModulo - Grava registro do modulo no arquivo.                         |
--------------------------------------------------------------------------------
*/
void SalvaModulo(int Modulo)
{
  int		FildesHist;
  char 		FName[50];
  unsigned long 	Offset;

  /* -- Salva tabelas apontadas pelo Comum -- */
  sprintf (FName, ARQUIVO_COMUM);
  if( (FildesHist = open (FName,O_RDWR) ) eq -1 )
	error("Erro na abertura do arquivo %s", FName);
  else
  {
	/* -- Tabela de Descricao de Programas -- */
	Offset = (long)Comum->OfDescProg + Modulo*sizeof(t_reg_prog);
	lseek(FildesHist, Offset, SEEK_SET);
	if(write(FildesHist,(char *)&PDescProg->Prog[Modulo].TidProg,
		(long)sizeof(t_reg_prog)) ne sizeof(t_reg_prog))
	  error("Erro de escrita arquivo %s",FName);
  }
  close(FildesHist);
}

/*
--------------------------------------------------------------------------------
| SalvaNodos - Grava nodos de operacao no comum                                |
--------------------------------------------------------------------------------
*/
void SalvaNodos(void)
{
  int		FildesHist;
  char 		FName[50];

  /* -- Salva tabelas apontadas pelo Comum -- */
  sprintf (FName, ARQUIVO_COMUM);
  if( (FildesHist = open (FName,O_RDWR) ) eq -1 )
	error("Erro na abertura do arquivo %s", FName);
  else
  {
	/* -- Area inicial do comum (primeiros 256 bytes) contem a tabela de nodos -- */
	if(write(FildesHist,(char *)&Comum->TamComum,256l) ne 256)
	  error("Erro de escrita arquivo %s",FName);
  }
  close(FildesHist);
}

/* -- fim InstalaDemo.c -- */
