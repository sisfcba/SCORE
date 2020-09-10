/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 3.0

	PROJETO		: SCORE

	SISTEMA		: TODOS

	ARQUIVO		: AcionaSirene.c

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
  int acao;

  if (argc eq 3)
  {
	acao=atoi(argv[1]);
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
	  if (acao eq LIGAR)
	  {
		ComandaSirene(Cuba,LIGAR);
		printf("Cuba %s->Ligou sirene.\n",argv[2]);
	  }
	  else
	  {
		ComandaSirene(Cuba,DESLIGAR);
		printf("Cuba %s->desligou sirene.\n",argv[2]);
	  }
	}
  }
  else
  {
	fprintf(stderr,"Use: AcionaSirene acao cuba\nOnde acao=2 ligar e 1=desligar\n");
	exit(EXIT_FAILURE);
  }
}
