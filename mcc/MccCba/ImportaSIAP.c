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

/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/

#include	<MccCba.h>
#include	<time.h>
#include	<VarsComum.h>
#include	<stdio.h>
#include	<stdlib.h>
#include	<stddef.h>
#include	<string.h>
#include	<sys/types.h>
#include	<sys/name.h>
#include	<fcntl.h>
#include	<sys/stat.h>
#include	<Prototipos.h>

void 	ImportaSIAP();


/*
-------------------------------------------------------------------------------
ImportaSIAP - Importa dados do SIAP para score
-------------------------------------------------------------------------------
*/
void ImportaSIAP()
{
	int i,j,k, Vida, Banho, Metal, Temp, AdFluorita, AdFluoreto;
	int Reducao, Dia, Mes, Ano;
	byte ArqValido;
	float Fluorita, Acidez;
	short int SF, CubaOpe, Cuba, difvida;
	struct tm DataOpe, DataTm;
	time_t DataOperacional, HoraAtual;

	FILE *f;
	char s[81];
	char aux[7];
	char c[5];
	char valida[81];
	char titulo[81];
	char nomearq[100];
 
	ArqValido = FALSO;

	HoraAtual = time(NULL);

	SF = Comum->IdentReducao;
	if (SF >= 7)
		SF -= 2;
	sprintf(nomearq,"/score/relatorio/rpsia230_sf%1i.txt",SF);
	f=fopen(nomearq,"r");
	if ( f eq NULL)
	{
		return;
	}

  	strcpy(titulo, "PROGRAMACAODEADICAODEAlF3");

  	fgets(s,80,f);

	PosicaoGlobal = 85;

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
			if ( valida[j] eq titulo[j])
			{
				ArqValido = VERDADEIRO;
			}
			else
			{
				ArqValido = FALSO;
				break;
			}
			j++;
		}
	}  

	//  printf("\n Arquivo Valido : %d \n",ArqValido);
	//  printf("\n Validacao : %s", valida);
	//  printf("\n Validacao : %s \n", titulo);

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

	//  printf(" Reducao : %i \n", Reducao);
	//  printf("\n DataBase : %2i/%2i/%4i \n", Dia, Mes, Ano);

	PosicaoGlobal = 86;

	DataOpe.tm_mday = Dia;
	DataOpe.tm_mon = Mes - 1;
	DataOpe.tm_year = Ano - 1900;
	DataOpe.tm_hour = 12;
	DataOpe.tm_min = 0;
	DataOpe.tm_sec = 0;
	DataOpe.tm_isdst = 0;
	DataOperacional = mktime(&DataOpe);

	_localtime(&HoraAtual, &DataTm);

	//  printf("\n DataOperacional : %d \n", DataOperacional);
	//  printf("\n DataImport : %d \n", AVL.Trab.DataImport);

	if(Comum->IdentReducao eq Reducao and ArqValido eq VERDADEIRO and
		DataOperacional > AVL.Trab.DataImport)
	{
		AVL.Trab.DataOperacional = DataOperacional;
		AVL.Trab.DataAnalise = DataOperacional;
		AVL.Trab.DataImport = DataOperacional;
		PosicaoGlobal = 87;

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
				PosicaoGlobal = 88;
				if( k eq 0 )
				{
					CubaOpe = atoi(aux);
					if(CubaOpe < 100 or CubaOpe >2100)
						return;

					if((Reducao eq 1 and CubaOpe > 175 and CubaOpe < 201) or
							(Reducao eq 1 and CubaOpe > 275 and CubaOpe < 301))
					{
						k = 9;
						continue;
					}

					Cuba=ConvCubOperScore(CubaOpe);
					if (Cuba eq -1)
						return;		
					k++;
				}
				else if( k eq 1)
				{
					Vida = atoi(aux);
					if( Vida > 0 and Vida < 5000)
					{
						if(DataTm.tm_mday eq DataOpe.tm_mday)
						{
							AVC.User1[Cuba].Vida = Vida;
						}
						else
						{
							difvida = (int)((HoraAtual - DataOperacional)/86400);
							AVC.User1[Cuba].Vida = Vida + difvida;
						}
					}
					k++;
				}
				else if( k eq 2)
				{
					Banho = atoi(aux);
					if( Banho > 0 and Banho < 30)
					{
						SUPERV_AVC(Cuba).Sup.CNF_SUP.Banho = Banho;
					}
					k++;
				}
				else if( k eq 3)
				{
					Metal = atoi(aux);
					if (Metal > 0 and Metal < 60)
					{
						SUPERV_AVC(Cuba).Sup.CNF_SUP.Metal = Metal;
					}
					k++;
				}
				else if( k eq 4)
				{
					Temp = atoi(aux);
					if (Temp > 900 and Temp < 1100)
					{
						SUPERV_AVC(Cuba).Sup.CNF_SUP.Temperatura = Temp;
					}
					k++;
				}
				else if( k eq 5)
				{
					Fluorita = atof(aux);
					if( Fluorita >0 and Fluorita < 15)
					{
						SUPERV_AVC(Cuba).Sup.CNF_SUP.Fluorita = Fluorita;
					}
					k++;
				}
				else if( k eq 6)
				{
					AdFluorita = atof(aux);
					if(AdFluorita >= 0 and AdFluorita < 100)
					{

					}
					k++;
				}
				else if( k eq 7)
				{
					Acidez = atof(aux);
					if(Acidez > 0 and Acidez < 20 )
					{
						SUPERV_AVC(Cuba).Sup.CNF_SUP.Fluoreto = Acidez;
					}
					k++;
				}
				else if( k eq 8)
				{
					AdFluoreto = atoi(aux);
					if(AdFluoreto > 0 and AdFluoreto < 100)
					{
						AVC.User1[Cuba].AdFluoreto = AdFluoreto;
					}
					k++;
				}
				else 
				{
					if(fgets(s,80,f) eq NULL)
					{
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
	fclose(f);
	remove(nomearq);

	PosicaoGlobal = 89;

  	if(Comum->IdentReducao eq 3)
  	{

		ArqValido = FALSO;
		SF = 1;
		sprintf(nomearq,"/score/relatorio/rpsia230_sf%1i.txt",SF);
		f=fopen(nomearq,"r");
		if (f eq NULL)
		{
			return;
		}
		PosicaoGlobal = 90;

    	fgets(s,80,f);

		for ( j=0 ; j<5 ; j++ )
		{
		c[j] = ' ';
		}
    
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
				if ( valida[j] eq titulo[j])
				{
					ArqValido = VERDADEIRO;
				}
				else
				{
					ArqValido = FALSO;
					break;
				}
				j++;
			}
    	}  
		PosicaoGlobal = 91;

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

		PosicaoGlobal = 92;

		DataOpe.tm_mday = Dia;
		DataOpe.tm_mon = Mes - 1;
		DataOpe.tm_year = Ano - 1900;
		DataOpe.tm_hour = 12;
		DataOpe.tm_min = 0;
		DataOpe.tm_sec = 0;
		DataOpe.tm_isdst = 0;
		DataOperacional = mktime(&DataOpe);

		//	printf("\nTeste : %s\n", valida);
		//	printf("\nTest1 : %s\n", titulo);

    	if(Reducao eq 1 and ArqValido eq VERDADEIRO)
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
						if(CubaOpe <= 175 or (CubaOpe >= 201 and CubaOpe <=275) or
							(CubaOpe >= 301))
						{
							k = 9;
							continue;
						}		
						CubaOpe += 400;
						Cuba=ConvCubOperScore(CubaOpe);
						if (Cuba eq -1)
							return;		
						k++;
	      			}
					else if( k eq 1)
					{
						Vida = atoi(aux);
						if( Vida > 0 and Vida < 5000)
						{
							if(DataTm.tm_mday eq DataOpe.tm_mday)
							{
								AVC.User1[Cuba].Vida = Vida;
							}
							else
							{
								difvida = (int)((HoraAtual - DataOperacional)/86400);
								AVC.User1[Cuba].Vida = Vida + difvida;
							}
						}
						k++;
					}
					else if( k eq 2)
					{
						Banho = atoi(aux);
						if( Banho > 0 and Banho < 30)
						{
							SUPERV_AVC(Cuba).Sup.CNF_SUP.Banho = Banho;
						}
						k++;
					}
					else if( k eq 3)
					{
						Metal = atoi(aux);
						if (Metal > 0 and Metal < 60)
						{
							SUPERV_AVC(Cuba).Sup.CNF_SUP.Metal = Metal;
						}
						k++;
					}
					else if( k eq 4)
					{
						Temp = atoi(aux);
						if (Temp > 900 and Temp < 1100)
						{
							SUPERV_AVC(Cuba).Sup.CNF_SUP.Temperatura = Temp;
						}
						k++;
					}
					else if( k eq 5)
					{
						Fluorita = atof(aux);
						if( Fluorita >0 and Fluorita < 15)
						{
							SUPERV_AVC(Cuba).Sup.CNF_SUP.Fluorita = Fluorita;
						}
						k++;
					}
					else if( k eq 6)
					{
						AdFluorita = atof(aux);
						if(AdFluorita >= 0 and AdFluorita < 100)
						{

						}
						k++;
					}
					else if( k eq 7)
					{
						Acidez = atof(aux);
						if(Acidez > 0 and Acidez < 20 )
						{
							SUPERV_AVC(Cuba).Sup.CNF_SUP.Fluoreto = Acidez;
						}
						k++;
					}
					else if( k eq 8)
					{
						AdFluoreto = atoi(aux);
						if(AdFluoreto > 0 and AdFluoreto < 100)
						{

						}
						k++;
					}
					else 
					{
						if(fgets(s,80,f) eq NULL)
						{
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
		fclose(f);
		remove(nomearq);
  	}
}
