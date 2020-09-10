/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 3.0

	PROJETO		: SCORE

	SISTEMA		: KONIN

	ARQUIVO		: SobeCamisa.c

	CONTEUDO	: SobeCamisa o tempo indicado
				  Deve ser ser ativado com o Score NO AR.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.21		-		COMPILADOR: WATCOM

	VERSAO		: 1.0			-		DATA	:	22/09/97

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
dd/mm/aa | descricao                                            | autor
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
						   Constantes
-------------------------------------------------------------------------------
*/
#define		MIN_TIME		1.0		//Minimum time to activate blow output (seconds)
#define		MAX_TIME		5.0		//Maximum time to activate blow output (seconds)

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
#include	<Prototipos.h>
#include	<VarsComum.h>

/*
-------------------------------------------------------------------------------
						   Prototipos
-------------------------------------------------------------------------------
*/

/*
-------------------------------------------------------------------------------
						   Principal
-------------------------------------------------------------------------------
*/
void main(int argc,char *argv[])
{
  int Cuba,CubaOper;
  int tempo;
  float argtempo;

  if (argc eq 3)
  {
	argtempo=atof(argv[1]);
	CubaOper=atoi(argv[2]);
	if (qnx_name_locate(My_nid,"Atan/Score/Controle",sizeof(int),NULL) ne -1)
	{
	  if (PegaComum (&Comum))
		error("Falha no pegacomum!\n");
	}
	else
	  error("So pode executar no computador de controle!\n");
	if ((Cuba=ConvCubOperScore(CubaOper)) eq -1)
	{
	  fprintf(stderr,"Cuba invalida [%s]\n",argv[2]);
	  exit(EXIT_FAILURE);
	}
	else
	{
	  if ((argtempo >= MIN_TIME) and (argtempo <= MAX_TIME))
	  {
		tempo=(int)(argtempo*20);
//		printf("ComandaSaidaRem(%d,LIGAR,%d,%d)\n",Cuba,AVC.Abs[Cuba].BitBlow,tempo);
		ComandaSaidaRem(Cuba,LIGAR,AVC.Abs[Cuba].BitSobeCamisaouM1,tempo);
		printf("Cuba %s->Subiu camisa %3.1f segundos.\n",argv[2],(float)tempo/20.0);
	  }
	  else
		printf("Tempo invalido [%3.1f]! Deve ser >= %3.1f e <= %3.1f\n",
				argtempo,MIN_TIME,MAX_TIME);
	}
  }
  else
  {
	fprintf(stderr,"Use: SobeCamisa tempo cuba\nOnde tempo esta em segundos e deve ser >= %3.1f e <= %3.1f\n",
				MIN_TIME,MAX_TIME);
	exit(EXIT_FAILURE);
  }
}
