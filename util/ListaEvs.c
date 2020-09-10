
/*
Lista a tabela de eventos do Score
*/

#define	PROGRAMA_PRINCIPAL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Score.h>
#include <Prototipos.h>
#include <VarsComum.h>

t_desc_ev	*PDescEv;

#define PegaMsgEv(CodeEv) 		( &PDescEv->DescEv[CodeEv] )                                                                                                                                                                                                                                                                                                                                                                                                                                                        

void main(void)
{
  int CodeEv, Index;

  struct RegDescEventos RegEv,
						*PRegEv;
  char *PStr;
  char *NaoDef = "-----";
  char *TipoPar[N_PAR_EV] = {"CHAR","INTEIRO","LONG","FLOAT","STRING"};
  char *Grupo[]={"REGISTRA IMPRIME EXIBE","REGISTRA EXIBE","REGISTRA IMPRIME","REGISTRA"};
  char *Disp[]={"TODOS DISPOSITIVOS","CONSOLE REDE","CONSOLE REDE + TERMINAL ASSOCIADO"};
  char *ParEv[N_PAR_EV];


  PRegEv = &RegEv;

  if (PegaComum (&Comum))
  {
	printf ("Erro de pegacomum\n");
	exit(0);
  }

  /* -- Apontador para tabela de eventos -- */
  PDescEv = (t_desc_ev *)((char *)Comum + Comum->OfDescEv);

  if((PStr = calloc(200, sizeof(char))) eq NULL)
  {
    fprintf(stderr,"%s: Nao consegui allocar memoria",My_name);
	exit(EXIT_FAILURE);
  }

  printf("\n					TABELA DE EVENTOS DO SCORE \n");
  for (CodeEv=0; CodeEv < MAX_EVS; CodeEv++)
  {
    printf("\n		EVENTO NUMERO - %-02d",CodeEv);
    memcpy((struct RegDescEventos *)PRegEv, PegaMsgEv(CodeEv),sizeof(RegEv) );
	printf("\n		GRUPO: %s",Grupo[PRegEv->Grupo-1]);
	printf("\n		DISPOSITIVO: %s",Disp[PRegEv->Dispositivo-1]);
    for(Index = 0; Index < N_PAR_EV; Index++)
    {
	  if(PRegEv->TipoParEv[Index] ne -1)
		ParEv[Index] = TipoPar[(PRegEv->TipoParEv[Index])-1];
	  else
		ParEv[Index] = NaoDef;
	}
	printf("\n		MNEUMONICO: [%s]",PRegEv->Mneumonico);
	printf("\n		MENSAGEM: [%s] - [%d]",PRegEv->Msg,strlen(PRegEv->Msg));
  	printf("\n		PARAMETROS: %s %s %s %s %s",
			ParEv[0],ParEv[1],ParEv[2],ParEv[3],ParEv[4]);
    if(PRegEv->EvCuba eq VERDADEIRO)
      printf("\n		E' EVENTO DE CUBA.\n");
	else
      printf("\n		NAO E' EVENTO DE CUBA.\n");
  }
  free(PStr);
}

