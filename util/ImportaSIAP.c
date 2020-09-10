/*

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.

	PROJETO		: Integracao processo

	SISTEMA		: SCORE

	ARQUIVO		: ImportaSIAP.c

	CONTEUDO	: Programa que importa dados do SIAP para o SCORE..

	AUTOR		: Marco Aurelio Moreira Lopes

	VERSAO		: 1.0			-		DATA	:	19/12/12

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
dd/mm/aa | descricao                                            | autor 
-------------------------------------------------------------------------------
19/12/12 | Edicao Inicial										| Marco
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
#include	<RelGraf.h>
#include	<Prototipos.h>
#include	<VarsComum.h>
#include	<Prototipos.h>
#include	<time.h>
#include	<fcntl.h>
#include	<sys/stat.h>
#include	<DescrArqVar.h>
#include	<VarsComum.h>
#include 	<BdScore.h>
#include	<ScoreMsgs.h>



/*
-------------------------------------------------------------------------------
                           Main
-------------------------------------------------------------------------------
*/
void main(void)
{

  printf("\nIMPORTANDO DADOS DO SIAP\n");

  if (qnx_name_locate(My_nid,"Atan/Score/AdmSemaf",sizeof(int),NULL) ne -1)
  {
	if (PegaComum (&Comum))
	  error("Falha no pegacomum!\n");
	ini_valores();
  }
  else
  {
    printf("Nao implementado para Score desativado.\n");
  }
}

/******************************************************************************
-------------------------------------------------------------------------------
IniValores - Faz a importacao do arquivo
-------------------------------------------------------------------------------
******************************************************************************/
/* inicializa os valores para cada cuba */
void ini_valores()
{
  int i,j,k, Vida, Banho, Metal, Temp, AdFluorita, AdFluoreto;
  int Reducao, Dia, Mes, Ano;
  byte ArqValido;
  float Fluorita, Acidez;
//  short int Cuba;
  short int CubaOpe, SF;
  struct tm DataOpe;
  time_t DataOperacional;


  FILE *f;
  char s[81];
  char aux[7];
  char c[5];
  char valida[25];
  char titulo[25];
  char nomearq[100];
 
  ArqValido = FALSO;

  SF = Comum->IdentReducao;
  if (SF >= 7)
	SF -= 2;
  printf("\n SALA FORNOS = %1i \n", SF);
  SF = sprintf(nomearq,"/score/relatorio/teste");
  f=fopen(nomearq,"r");
  if ( f eq NULL)
  {
    printf("\nArquivo %s nao localizado \n",nomearq);
	return;
  }
  fgets(s,80,f);
  j=0;
  for(i = 0; i < 81; i++)
  {
    if(s[i] eq ' ')
	  continue;
	else
	{
	  if(s[i] eq '-')
		break;
	  valida[j] = s[i];
	  j++;
	}
  }  
  strcpy(titulo, "PROGRAMACAODEADICAODEAlF3");

  if(strcmp(titulo, valida) eq 0)
	ArqValido = VERDADEIRO;
  else
	ArqValido = FALSO;

  fgets(s,80,f);
  fgets(s,80,f);
  c[0] = s[19];
  Reducao = atoi(c);
  if(Reducao >= 5)
	Reducao += 2;
  for ( j=0 ; j<5 ; j++ )
  {
    c[j] = ' ';
  }
  c[0] = s[40];
  c[1] = s[41];
  Dia = atoi(c);
  for ( j=0 ; j<5 ; j++ )
  {
    c[j] = ' ';
  }
  c[0] = s[43];
  c[1] = s[44];
  Mes = atoi(c);
  for ( j=0 ; j<5 ; j++ )
  {
    c[j] = ' ';
  }
  c[0] = s[46];
  c[1] = s[47];
  c[2] = s[48];
  c[3] = s[49];
  Ano = atoi(c);

  DataOpe.tm_mday = Dia;
  DataOpe.tm_mon = Mes - 1;
  DataOpe.tm_year = Ano - 1900;
  DataOpe.tm_hour = 12;
  DataOpe.tm_min = 0;
  DataOpe.tm_sec = 0;
  DataOpe.tm_isdst = 0;
  DataOperacional = mktime(&DataOpe);

  printf("\nReducao = %d",Reducao);
  printf("\nArqValido = %d",ArqValido);
  printf("\nDataOperacional = %d",DataOperacional);
  printf("\nDataOperacionalSCORE = %d \n",AVL.Trab.DataOperacional);

  if(Comum->IdentReducao eq Reducao and ArqValido eq VERDADEIRO and
	DataOperacional > AVL.Trab.DataOperacional)
  {
   	fgets(s,80,f);
  	k = j = 0;
	for( i = 0; i<=80 ; i++)
  	{
	  if ( ((s[i] ne ';') and (k < 9)) or ((k eq 8) and (j <=3)) )
	  {

	    if(s[i] eq ' ')
	    {
		  if((k eq 8) and (j > 1))
		    s[i+1] = ';';
	  	  continue;
	    }
	    else
	    {
		  if(s[i] eq ',')
		    aux[j] = '.';
		  else
		    aux[j] = s[i];
	      j++;
	    }
	  }
	  else 
	  {
	    if( k eq 0 )
	    {
	      CubaOpe = atoi(aux);
		  if(CubaOpe < 100 or CubaOpe >2100)
			return;
		  printf("\n CubaOpe = %d\n", CubaOpe);
		  getchar();		
	      k++;
	    }
	    else if( k eq 1)
	    {
	      Vida = atoi(aux);
		  if( Vida > 0 and Vida < 5000)
		  {
			printf("\n Vida = %d\n", Vida);
		  	getchar();		
		  }
          k++;
	    }
	    else if( k eq 2)
	    {
          Banho = atoi(aux);
		  if( Banho > 0 and Banho < 30)
		  {
		    printf("\n Banho = %d\n", Banho);
		    getchar();		
		  }
	      k++;
	    }
	    else if( k eq 3)
	    {
          Metal = atoi(aux);
		  if (Metal > 0 and Metal < 60)
		  {
		    printf("\n Metal = %d\n", Metal);
		    getchar();		
		  }
	      k++;
	    }
	    else if( k eq 4)
	    {
	      Temp = atoi(aux);
		  if (Temp > 900 and Temp < 1100)
		  {
		    printf("\n Temperatura = %d\n", Temp);
		    getchar();		
		  }
	      k++;
	    }
	    else if( k eq 5)
	    {
	      Fluorita = atof(aux);
	      if( Fluorita >0 and Fluorita < 15)
		  {
		    printf("\n Fluorita = %f\n", Fluorita);
		    getchar();		
		  }
	      k++;
	    }
	    else if( k eq 6)
	    {
		  AdFluorita = atof(aux);
	      if(AdFluorita >= 0 and AdFluorita < 100)
		  {
		    printf("\n AdFluorita = %d\n", AdFluorita);
	 	    getchar();		
		  }
	      k++;
	    }
	    else if( k eq 7)
	    {
	      Acidez = atof(aux);
		  if(Acidez > 0 and Acidez < 20 )
		  {
		    printf("\n Acidez = %f\n", Acidez);
		    getchar();		
		  }
	      k++;
	    }
	    else if( k eq 8)
	    {
	      AdFluoreto = atoi(aux);
		  if(AdFluoreto > 0 and AdFluoreto < 100)
		  {
		    printf("\n AdFluoreto = %d\n", AdFluoreto);
		    getchar();		
		  }
	      k++;
	    }
	    else 
	    {
  		  if(fgets(s,80,f) eq NULL)
		  {
		    printf("\n Encerra!!! \n");
	        break;
		  }
		  else
		  {
		    i=0;
		    k=0;
		  }
	    }
	    for ( j=0 ; j<7 ; j++ )
	    {
		  aux[j] = ' ';
	    }
        j = 0;
	  }
    }
  }
  else
  {
	printf("\n REDUCAO DIFERENTE DO SISTEMA EM EXECUCAO!!! \n");
  }
  fclose(f);
  remove(nomearq);

}
