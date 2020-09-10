/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DAS SALA 120 KA e 125KA

	ARQUIVO		: TrataPartida.c

	CONTEUDO	: Funcoes para tratamento da tabela de partida de cuba do
				  modulo de controle.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 1.0			-		DATA	:	10/03/2003

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
$Id: TrataPartida.c,v 1.1.2.1 2012/09/28 17:09:28 leo Exp $

$Log: TrataPartida.c,v $
Revision 1.1.2.1  2012/09/28 17:09:28  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

Revision 1.2  2003/03/28 12:42:37  leo
Tratamento de tabela de partida - versao 5.01.0005.

Revision 1.1  2003/03/13 20:56:04  leo
Algoritmo de tratamento da tabela de partida de cubas.

******************************************************************************/

/**** #define		ATIVA_DEPURACAO  ****/

/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include <MccCba.h>
#include <Eventos.h>
#include <Prototipos.h>

/*
-------------------------------------------------------------------------------
                           Variaveis Globais
-------------------------------------------------------------------------------
*/

/* -- Apontadores para as tabelas comuns -- */
#include	<VarsComum.h>

/*
-------------------------------------------------------------------------------
							Funcoes
-------------------------------------------------------------------------------
*/

/*
--------------------------------------------------------------------------------
  IniTrataPartida - Inicializacoes do tratamento de tabela de partida de forno
--------------------------------------------------------------------------------
*/
void IniTrataPartida(int Cuba)
{
	if (AVC.ParUser1[Cuba].HabTabPartida eq FALSO)
	{ /* Inicializa passo atual e hora de inicio de espera */
		PosicaoGlobal = 170;
		AVC.User1[Cuba].PassoAtualTPartida=255;
		AVC.User1[Cuba].HoraIniEsperaTPartida=0;
		AVC.User1[Cuba].EaVoltLimTabPartida = AVC.Param[Cuba].EaVoltLim;
		EST_AVC(Cuba).Est.TrataTabPartida=FALSO;
	}
	else
		if (EST_AVC(Cuba).Est.TrataTabPartida eq FALSO)
		{ /* Inicializa passo atual e hora de inicio de espera */
			PosicaoGlobal = 171;
			AVC.User1[Cuba].PassoAtualTPartida=255;
			AVC.User1[Cuba].HoraIniEsperaTPartida=0;
			AVC.User1[Cuba].EaVoltLimTabPartida = AVC.Param[Cuba].EaVoltLim;
		} /* Se habilitado e em tratamento entao continua de onde estava */
}

/*
--------------------------------------------------------------------------------
  TrataPartida - Tratamento de tabela de partida de forno
--------------------------------------------------------------------------------
*/
void TrataPartida(int Cuba)
{
  if (AVC.ParUser1[Cuba].HabTabPartida eq FALSO)
  { /* Verifica se estava tratando tabela antes para gerar evento de fim */
    if (AVC.User1[Cuba].PassoAtualTPartida ne 255)
	{
PosicaoGlobal = 172;

	  GeraEvento(EV_TAB_PARTIDA,Cuba,-1,"Fim",AVC.ParUser1[Cuba].NumTabPartida,"Desab.",
	  			AVC.User1[Cuba].PassoAtualTPartida+1);
      /* Inicializa passo atual e hora de inicio de espera */
	  EST_AVC(Cuba).Est.TrataTabPartida=FALSO;
      IniTrataPartida(Cuba);
	}
  }
  else
  	if (EST_AVC(Cuba).Est.TrataTabPartida eq FALSO)
	{ /* Verifica se estava tratando tabela antes para gerar evento de fim */
	  if (AVC.User1[Cuba].PassoAtualTPartida ne 255)
	  {
PosicaoGlobal = 173;

	    GeraEvento(EV_TAB_PARTIDA,Cuba,-1,"Fim",AVC.ParUser1[Cuba].NumTabPartida,
					"Operacao",AVC.User1[Cuba].PassoAtualTPartida+1);
	    /* Inicializa passo atual e hora de inicio de espera */
	    IniTrataPartida(Cuba);
	  }
	}
	else
	{ /* Tabela de partida ativa */
	  if (AVC.User1[Cuba].PassoAtualTPartida ne 255)
	  { /* Executa todos os passos que nao tenham espera ou ate o fim.
	       Passo de espera verifica se tempo esgotou. Retorna verdadeiro
		   ate encontrar passo de espera ou terminar */
	    while ( ExecutaPasso(Cuba) );
	  }
	}
}

/*
--------------------------------------------------------------------------------
  ExecutaPasso - Executa passo corrente da tabela de partida. Retorna FALSO
                 se chegou ao fim (executou ultimo passo) e se esta em sleep.
--------------------------------------------------------------------------------
*/
int ExecutaPasso(int Cuba)
{
  int tab, passo, ret;
  
PosicaoGlobal = 174;

  tab=AVC.ParUser1[Cuba].NumTabPartida;
  passo=AVC.User1[Cuba].PassoAtualTPartida;
  /* Verifica se chegou ao ultimo passo e gera evento de fim se sim */
  if (passo >= MAX_PASSOS_TAB_PARTIDA)
  { /* fim da tabela */
PosicaoGlobal = 175;

	GeraEvento(EV_TAB_PARTIDA,Cuba,-1,"Fim",tab,"Normal",passo+1);
    /* Inicializa passo atual e hora de inicio de espera */
	EST_AVC(Cuba).Est.TrataTabPartida=FALSO;
    IniTrataPartida(Cuba);
    return(FALSO);	/* Chegou ao fim */
  }
  ret=VERDADEIRO; /* para quando executa acao que nao necessita espera e ainda
               nao terminou */

PosicaoGlobal = 176;

  switch(AVL.Par.TabPartida[tab].Passo[passo].Acao)
  {

	case TAB_PART_ACAO_NULA: /* 0 = Fim da tabela */
	  GeraEvento(EV_TAB_PARTIDA,Cuba,-1,"Fim",tab,"Normal",passo+1);
      /* Inicializa passo atual e hora de inicio de espera */
	  EST_AVC(Cuba).Est.TrataTabPartida=FALSO;
      IniTrataPartida(Cuba);
      ret = FALSO;	/* Chegou ao fim */
	  break;
	case TAB_PART_MUDA_ESTADO: /* Muda estado da cuba */
	  GeraEvento(EV_TAB_PARTIDA,Cuba,-1,"ExePasso",tab,"Estado",passo+1);
	  /* Cuba, estado e operador */
	  if (MudaEstadoCuba(Cuba,AVL.Par.TabPartida[tab].Passo[passo].Param.Ipar,-1) == 0)
	  { /* Ok, Avanca para proximo passo */
      	AVC.User1[Cuba].PassoAtualTPartida++;
	  	AVC.User1[Cuba].HoraIniEsperaTPartida=0;
	  }
	  else
	  { /* Falha. Aborta tabela */
		GeraEvento(EV_TAB_PARTIDA,Cuba,-1,"Fim",tab,"FalhaAc",passo+1);
     	/* Inicializa passo atual e hora de inicio de espera */
		EST_AVC(Cuba).Est.TrataTabPartida=FALSO;
		IniTrataPartida(Cuba);
      	ret = FALSO;	/* Chegou ao fim */
	  }
	  break;
	case TAB_PART_MUDA_AUT_MAN: /* Muda estado motor macaco */
	  GeraEvento(EV_TAB_PARTIDA,Cuba,-1,"ExePasso",tab,"AutoMan",passo+1);
	  /* Cuba, estado e operador */
	  if (MudaAutManCuba(Cuba,AVL.Par.TabPartida[tab].Passo[passo].Param.Ipar,-1) == 0)
	  { /* Ok, Avanca para proximo passo */
      	AVC.User1[Cuba].PassoAtualTPartida++;
	  	AVC.User1[Cuba].HoraIniEsperaTPartida=0;
	  }
	  else
	  { /* Falha. Aborta tabela */
		GeraEvento(EV_TAB_PARTIDA,Cuba,-1,"Fim",tab,"FalhaAc",passo+1);
     	/* Inicializa passo atual e hora de inicio de espera */
		EST_AVC(Cuba).Est.TrataTabPartida=FALSO;
		IniTrataPartida(Cuba);
      	ret = FALSO;	/* Chegou ao fim */
	  }
	  break;
	case TAB_PART_MUDA_LIM_EA: /* Muda limite EA */
	  GeraEvento(EV_TAB_PARTIDA,Cuba,-1,"ExePasso",tab,"LimEA",passo+1);
	  AVC.User1[Cuba].EaVoltLimTabPartida = AVL.Par.TabPartida[tab].Passo[passo].Param.Fpar;
      /* Avanca para proximo passo */
      AVC.User1[Cuba].PassoAtualTPartida++;
	  AVC.User1[Cuba].HoraIniEsperaTPartida=0;
	  break;
	case TAB_PART_AJUSTE_CAMISA: /* Hab/desab. ajuste de camisa */
	  GeraEvento(EV_TAB_PARTIDA,Cuba,-1,"ExePasso",tab,"AjCamisa",passo+1);
	  /* Cuba, acao (Ativa/desativa), tempo(0), operador e msg(NULL) */
	  if (AlteraAjusteCamisa(Cuba,AVL.Par.TabPartida[tab].Passo[passo].Param.Ipar,0,-1,NULL) == 0)
	  { /* Ok, Avanca para proximo passo */
      	AVC.User1[Cuba].PassoAtualTPartida++;
	  	AVC.User1[Cuba].HoraIniEsperaTPartida=0;
	  }
	  else
	  { /* Falha. Aborta tabela */
		GeraEvento(EV_TAB_PARTIDA,Cuba,-1,"Fim",tab,"FalhaAc",passo+1);
     	/* Inicializa passo atual e hora de inicio de espera */
		EST_AVC(Cuba).Est.TrataTabPartida=FALSO;
		IniTrataPartida(Cuba);
      	ret = FALSO;	/* Chegou ao fim */
	  }
	  break;
	case TAB_PART_QUEB_PREV: /* Hab/desab. quebrada preventiva */
	  GeraEvento(EV_TAB_PARTIDA,Cuba,-1,"ExePasso",tab,"QuebPrev",passo+1);
	  /* Cuba, acao (Ativa/desativa), tempo (0) e operador (-1=traco) */
	  if (MudaQuebPrevCuba(Cuba,AVL.Par.TabPartida[tab].Passo[passo].Param.Ipar,0,-1) == 0)
	  { /* Ok, Avanca para proximo passo */
      	AVC.User1[Cuba].PassoAtualTPartida++;
	  	AVC.User1[Cuba].HoraIniEsperaTPartida=0;
	  }
	  else
	  { /* Falha. Aborta tabela */
		GeraEvento(EV_TAB_PARTIDA,Cuba,-1,"Fim",tab,"FalhaAc",passo+1);
     	/* Inicializa passo atual e hora de inicio de espera */
		EST_AVC(Cuba).Est.TrataTabPartida=FALSO;
		IniTrataPartida(Cuba);
      	ret = FALSO;	/* Chegou ao fim */
	  }
	  break;
	case TAB_PART_TAB_INC_OPER: /* Hab. tabela incremento operacao */
	  GeraEvento(EV_TAB_PARTIDA,Cuba,-1,"ExePasso",tab,"TabIncOp",passo+1);
	  /* Cuba, acao (ativa/desativa) e operador (-1=traco) */
	  if (AtivaTabIncCuba(Cuba,AVL.Par.TabPartida[tab].Passo[passo].Param.Ipar,-1) == 0)
	  { /* Ok, Avanca para proximo passo */
      	AVC.User1[Cuba].PassoAtualTPartida++;
	  	AVC.User1[Cuba].HoraIniEsperaTPartida=0;
	  }
	  else
	  { /* Falha. Aborta tabela */
		GeraEvento(EV_TAB_PARTIDA,Cuba,-1,"Fim",tab,"FalhaAc",passo+1);
     	/* Inicializa passo atual e hora de inicio de espera */
		EST_AVC(Cuba).Est.TrataTabPartida=FALSO;
		IniTrataPartida(Cuba);
      	ret = FALSO;	/* Chegou ao fim */
	  }
	  break;
	case TAB_PART_ESPERA: /* Aguarda tempo */
	  if (AVC.User1[Cuba].HoraIniEsperaTPartida eq 0)
	  { /* entrou a primeira vez, pega hora atual para comparar depois */
	    AVC.User1[Cuba].HoraIniEsperaTPartida=HoraAtualCtrl;
	    GeraEvento(EV_TAB_PARTIDA,Cuba,-1,"ExePasso",tab,"Espera",passo+1);
	  }
	  if ((HoraAtualCtrl - AVC.User1[Cuba].HoraIniEsperaTPartida) >=
	  		 AVL.Par.TabPartida[tab].Passo[passo].Param.Tpar)
	  {
      	/* Avanca para proximo passo */
        AVC.User1[Cuba].PassoAtualTPartida++;
	    AVC.User1[Cuba].HoraIniEsperaTPartida=0;
	  }
	  else
	    ret=FALSO;	/* aguarda proximo ciclo para verificar se terminou */
	  break;
	default: /* Acao invalida, finaliza tabela */
	  GeraEvento(EV_TAB_PARTIDA,Cuba,-1,"Fim",tab,"FalhaAc",passo+1);
      /* Inicializa passo atual e hora de inicio de espera */
	  EST_AVC(Cuba).Est.TrataTabPartida=FALSO;
	  IniTrataPartida(Cuba);
      ret = FALSO;	/* Chegou ao fim */
	  break;
  }
  return(ret);
}

/* -- fim TrataPartida.c -- */
