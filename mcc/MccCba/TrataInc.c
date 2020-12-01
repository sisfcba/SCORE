/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: TrataInc.c

	CONTEUDO	: Modulo de Controle das Cubas - MCC - Procedimentos de calculo
                  dos incrementos de Corrida, Quebrada, Ea e do Operador.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	22/09/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
08/12/92 | Correcao funcoes de incremento de quebrada e corrida | Leonel
-------------------------------------------------------------------------------
05/07/94 | Edicao inicial de migracao para o QNX 4.2			| Leonel
-------------------------------------------------------------------------------
14/02/95 | Correcao do trat. troca de pinos ativado via painel	| Carlos
-------------------------------------------------------------------------------
28/03/95 | Incluido tratamento para tabela de incremento de ope.| Leonel
-------------------------------------------------------------------------------
28/02/96 | Incluido tratamento para incremento de usuario       | Carlos
-------------------------------------------------------------------------------
21/02/97 | Substituida tabela Param por  Ccont  para variaveis  | Carlos
         | VSetPoint e Banda*Atual                              |
-------------------------------------------------------------------------------
03/12/98 | Mantem incremento de operacao qdo partida a frio     | Leonel
-------------------------------------------------------------------------------
29/11/99 | Adequacao do tratamento de incremento de usuario ao  | Carlos
         | padrao original do Score                             | 
-------------------------------------------------------------------------------
$Id: TrataInc.c,v 1.1.2.1 2012/09/28 17:09:28 leo Exp $

$Log: TrataInc.c,v $
Revision 1.1.2.1  2012/09/28 17:09:28  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

Revision 1.3  2005/12/12 13:24:29  leo
Retirados ifdefs nao mais usados. Liberada movimentacao para baixo quando
em previsao e ocorreu quebrada.

******************************************************************************/

/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include	<MccCba.h>
#include	<time.h>

/*
-------------------------------------------------------------------------------
                           Variaveis Globais
-------------------------------------------------------------------------------
*/
/* -- Apontadores para as tabelas comuns -- */
#include	<VarsComum.h>

/*
-------------------------------------------------------------------------------
                           Prototipos
-------------------------------------------------------------------------------
*/
void	TrataIncCorr(int Cuba);
void	TrataIncQueb(int Cuba);
void	TrataIncTPinos(int Cuba);
void	TrataIncUsuario(int Cuba);
void	TrataIncOperador(int Cuba);
float	CalcRampa(float v_ini, int t_max, int cont_t);
float	CalcTriangulo(float v_ini, int t_max, int cont_t, int t_pico);


/*
-------------------------------------------------------------------------------
							Funcoes
-------------------------------------------------------------------------------
*/

/*
--------------------------------------------------------------------------------
| IniIncrementos - Inicializa variaveis referentes aos incrementos de corrida, |
|                  quebrada, Ea e do operador.                                 |
--------------------------------------------------------------------------------
*/
void IniIncrementos(int Cuba)
{
  	static int TempoParada=-1; /* em segundos */
	PosicaoGlobal = 140;
	/* Calcula tempo que o sistema ficou desativado para utilizar no tratamento
		de incremento de operacao apos partida aa frio */
	if (TempoParada eq -1)
	{ // primeira vez, calcula tempo de parada para tratamento inc. operacao
		TempoParada = (int)difftime(AVL.HoraAtualControle,AVL.HoraUltControle);
		TempoParada /= 60;	/* passa para minutos */
		if ((TempoParada Mod 2) eq 1)
			TempoParada+=1;	// arredonda para multiplo de 2 minutos
	}

	/* -- variaveis relativas aos incrementos -- */
	AVC.Ccont[Cuba].IncQueb=0;
	AVC.Ccont[Cuba].ContIncQueb=-1;
	AVC.Ccont[Cuba].IncTPinos=0;
	AVC.Ccont[Cuba].ContIncTPinos=-1;
	AVC.Ccont[Cuba].IncUsuario=0;
	AVC.Ccont[Cuba].ContIncUsuario=-1;

	/* Tratamento para manter incremento de operacao apos partida a frio
		caso seu tempo ainda nao tenha se esgotado. */
	if ((EST_AVC(Cuba).TabOpeAtiva eq FALSO) and
		(AVC.Ccont[Cuba].HabIncOper eq VERDADEIRO))
	{ /* estava em incremento quando desativou e nao era tabela */
		
		PosicaoGlobal = 141;

		AVC.Ccont[Cuba].ContIncOper += TempoParada;
		if (AVC.Ccont[Cuba].ContIncOper >= AVC.Ccont[Cuba].TIncOp)
		{ /* -- fim do incremento -- */
			AVC.Ccont[Cuba].IncOper=0;
			AVC.Ccont[Cuba].ContIncOper=-1;
			AVC.Ccont[Cuba].HabIncOper=FALSO;
		}
	}
	else
	{
		AVC.Ccont[Cuba].IncOper=0;
		AVC.Ccont[Cuba].ContIncOper=-1;
		AVC.Ccont[Cuba].HabIncOper=FALSO;
	}
	EST_AVC(Cuba).TrataTPinos=FALSO;
	EST_AVC(Cuba).TrataIncUsuario=FALSO;
	EST_AVC(Cuba).TabOpeAtiva=FALSO;

	/* -- inicializa BandaContInfAtual -- */
	AVC.Ccont[Cuba].BandaContInfAtual=AVC.Param[Cuba].BandaContInf;

	/* -- inicializa VSetPoint atual -- */
	AVC.Ccont[Cuba].VSetPoint=AVC.Param[Cuba].VSetPointCnf;

	/* -- inicializa BandaContSupAtual -- */
	AVC.Ccont[Cuba].BandaContSupAtual=AVC.Param[Cuba].BandaContSup;
	PosicaoGlobal = 142;

  /* -- Inicializacao p/ incrementos de usuario -- */
  IniExecIncUsu(Cuba);
}

/*
--------------------------------------------------------------------------------
| CalculaIncrementos - Calcula os incrementos de tensao por ruido, corrida,    |
|                      quebrada, Ea e de Operacao para a cuba dada.            |
--------------------------------------------------------------------------------
*/
void CalculaIncrementos(int Cuba)
{

PosicaoGlobal = 143;

  /* -- Executa incrementos de usuario -- */
  ExecIncUsuario(Cuba);
PosicaoGlobal = 144;
  /* -- incrementos por ruido lento e rapido -- */
  TrataIncRuido(Cuba);
PosicaoGlobal = 145;
  /* -- incremento por quebrada recente -- */
  TrataIncQueb(Cuba);
PosicaoGlobal = 146;
  /* -- incremento apos Ea recente -- */
  TrataIncTPinos(Cuba);
PosicaoGlobal = 147;
  /* -- incremento dado pelo usurario -- */
  TrataIncUsuario(Cuba);
PosicaoGlobal = 148;
  /* -- incremento fixado pelo operador -- */
  TrataIncOperador(Cuba);

}

/*
--------------------------------------------------------------------------------
| TrataIncQueb - Calcula incremento por quebrada recente para a cuba dada      |
--------------------------------------------------------------------------------
*/
void TrataIncQueb(int Cuba)
{
  int TmpInterv1,TmpInterv2;

  if (EST_AVC(Cuba).Quebrada eq VERDADEIRO)
  {
PosicaoGlobal = 149;

	TmpInterv1=75*IntervCicCont;
	TmpInterv2=15*IntervCicCont;
	/* -- Verifica se houve quebrada no ultimo ciclo de controle com uma -- */
	/* -- janela de 1/4 de ciclo. IntervCicCont esta em minutos: -- */
	/* -- (60*IntervCicCont + (60*IntervCicCont)/4) -> 75*IntervCicCont -- */
	if ( ((HoraAtualCtrl-AVC.Cleit[Cuba].HoraUltQueb) < TmpInterv1) and
		 ((HoraAtualCtrl-AVC.Cleit[Cuba].HoraUltQueb) >= TmpInterv2) and
		 (AVC.Ccont[Cuba].ContIncQueb eq -1) )
	{ /* -- inicio de quebrada -- */
	  AVC.Ccont[Cuba].ContIncQueb=0;
	  AVC.Ccont[Cuba].IncQueb=AVC.Param[Cuba].IncQuebInic;
	  
	  /* -- Ajusta a banda de controle inferior por quebrada -- */
	  AVC.Ccont[Cuba].BandaContInfAtual=AVC.Param[Cuba].BandaContInf+
										AVC.Param[Cuba].AcresBCIQueb;
	}
  }
PosicaoGlobal = 150;

  if ((HoraAtualCtrl-AVC.Cleit[Cuba].HoraUltQueb) >
	  AVC.Param[Cuba].TAcresBCIQueb)
	/* -- Restaura banda de controle inferior algum tempo apos quebrada -- */
	AVC.Ccont[Cuba].BandaContInfAtual=AVC.Param[Cuba].BandaContInf;
  if (AVC.Ccont[Cuba].ContIncQueb ne -1)
  {
	if (AVC.Ccont[Cuba].ContIncQueb < AVC.Param[Cuba].TIncQueb)
	{
	  if (AVC.Param[Cuba].TipoIncQueb eq INCREMENTO_RAMPA)
		AVC.Ccont[Cuba].IncQueb=CalcRampa(AVC.Param[Cuba].IncQuebInic,
					AVC.Param[Cuba].TIncQueb,AVC.Ccont[Cuba].ContIncQueb);
	  AVC.Ccont[Cuba].ContIncQueb=AVC.Ccont[Cuba].ContIncQueb+IntervCicCont;
	}
	else
	{
	  AVC.Ccont[Cuba].IncQueb=0.0;
	  AVC.Ccont[Cuba].ContIncQueb=-1;
	}
  }

  if (AVC.ParUser1[Cuba].InibeIncQuebAtrasoEa eq VERDADEIRO)
  {
	if ( (HoraAtualCtrl - AVC.Ea[Cuba].EaHoraInicio) > 
		((AVC.Param[Cuba].EaAtrasoMax - AVC.ParUser1[Cuba].LimSupQPrevEa) * 60) )
	{
	  AVC.Ccont[Cuba].IncQueb=0.0;
	  AVC.Ccont[Cuba].ContIncQueb=-1;
	}
  }
  if(AVC.ParUser2[Cuba].InibIncQuebTemp eq VERDADEIRO and
	AVC.User3[Cuba].Temperatura > AVC.ParUser2[Cuba].TempMaxInibInc)
  {
	AVC.Ccont[Cuba].IncQueb=0.0;
    AVC.Ccont[Cuba].ContIncQueb=-1;
  }

  if(AVC.ParUser2[Cuba].InibIncQuebDB eq VERDADEIRO and 
    EST_AVC(Cuba).Est.InibeMovDB eq VERDADEIRO)
  {
	AVC.Ccont[Cuba].IncQueb=0.0;
    AVC.Ccont[Cuba].ContIncQueb=-1;
  }

  if(AVC.User3[Cuba].ContInibeIncQueb > 0)
  {
	AVC.User3[Cuba].ContInibeIncQueb--;
	AVC.Ccont[Cuba].IncQueb=0.0;
    AVC.Ccont[Cuba].ContIncQueb=-1;
  }

}



/*
--------------------------------------------------------------------------------
| TrataIncTPinos - Calcula incremento por troca de pinos na cuba dada          |
--------------------------------------------------------------------------------
*/
void TrataIncTPinos(int Cuba)
{
  if (AVC.Param[Cuba].HabIncTPinos eq VERDADEIRO)
  {
	if (EST_AVC(Cuba).TrataTPinos eq VERDADEIRO and
		(AVC.Cleit[Cuba].HoraUltTPinos - AVC.User3[Cuba].HoraUltTPinosAnt) > AVC.ParUser1[Cuba].IntervMinTPinos)
	{
	  if (AVC.Ccont[Cuba].ContIncTPinos eq -1)
	  { /* -- Inicio de incremento -- */
		AVC.Ccont[Cuba].ContIncTPinos=0;
		AVC.Ccont[Cuba].IncTPinos=AVC.Param[Cuba].IncTPinosInic;
	  }
PosicaoGlobal = 152;

	  if (AVC.Ccont[Cuba].ContIncTPinos < AVC.Param[Cuba].TIncTPinos)
	  {
		if (AVC.Param[Cuba].TipoIncTPinos eq INCREMENTO_RAMPA)
		  AVC.Ccont[Cuba].IncTPinos=CalcRampa(AVC.Param[Cuba].IncTPinosInic,
					AVC.Param[Cuba].TIncTPinos,AVC.Ccont[Cuba].ContIncTPinos);
		if (AVC.Param[Cuba].TipoIncTPinos eq INCREMENTO_TRIANGULO)
		  AVC.Ccont[Cuba].IncTPinos=CalcTriangulo(AVC.Param[Cuba].IncTPinosInic,
					AVC.Param[Cuba].TIncTPinos,AVC.Ccont[Cuba].ContIncTPinos,
					AVC.Param[Cuba].TIncPicoTPinos);
		AVC.Ccont[Cuba].ContIncTPinos=AVC.Ccont[Cuba].ContIncTPinos+IntervCicCont;
	  }
	  else
	  {
		AVC.Ccont[Cuba].IncTPinos=0.0;
		AVC.Ccont[Cuba].ContIncTPinos=-1;
		EST_AVC(Cuba).TrataTPinos=FALSO;
	  }
	}
  }
  else
  {
	/*--Verifica se houve desabilitacao durante o tratamento --*/
	if (EST_AVC(Cuba).TrataTPinos eq VERDADEIRO)
	{
	  AVC.Ccont[Cuba].IncTPinos=0.0;
	  AVC.Ccont[Cuba].ContIncTPinos=-1;
	  EST_AVC(Cuba).TrataTPinos=FALSO;
	}
  }

  if(AVC.ParUser2[Cuba].InibIncTpTemp eq VERDADEIRO and
	AVC.User3[Cuba].Temperatura > AVC.ParUser2[Cuba].TempMaxInibInc)
  {
	AVC.Ccont[Cuba].IncTPinos=0.0;
	AVC.Ccont[Cuba].ContIncTPinos=-1;
	EST_AVC(Cuba).TrataTPinos=FALSO;
  }

}

/*
--------------------------------------------------------------------------------
| TrataIncUsuario - Calcula incremento dado pelo  usuario  atraves  de  seus   |
|		modulos desenvolvidos via toolkit.                                     |
--------------------------------------------------------------------------------
*/
void TrataIncUsuario(int Cuba)
{
  if (AVC.Param[Cuba].HabIncUsuario eq VERDADEIRO)
  {
PosicaoGlobal = 153;

	if (EST_AVC(Cuba).TrataIncUsuario eq VERDADEIRO)
	{
	  if (AVC.Ccont[Cuba].IncUsuario ne 0.0)
		AVC.Ccont[Cuba].ContIncUsuario += IntervCicCont;
	}
	else
	{
	  AVC.Ccont[Cuba].IncUsuario     = 0.0;
	  AVC.Ccont[Cuba].ContIncUsuario = -1;
	  EST_AVC(Cuba).TrataIncUsuario  = FALSO;
	}
  }
  else
  {
	AVC.Ccont[Cuba].IncUsuario     = 0.0;
	AVC.Ccont[Cuba].ContIncUsuario = -1;
	EST_AVC(Cuba).TrataIncUsuario  = FALSO;
  }

  if(AVC.ParUser2[Cuba].InibIncOpTemp eq VERDADEIRO and
	AVC.User3[Cuba].Temperatura > AVC.ParUser2[Cuba].TempMaxInibInc)
  {
	AVC.Ccont[Cuba].IncUsuario     = 0.0;
	AVC.Ccont[Cuba].ContIncUsuario = -1;
	EST_AVC(Cuba).TrataIncUsuario  = FALSO;
  }
}


/*
--------------------------------------------------------------------------------
| TrataIncOperador - Calcula incremento dado pelo Operador para a cuba dada    |
--------------------------------------------------------------------------------
*/
void TrataIncOperador(int Cuba)
{
  int passo, tab_ope;

  if (AVC.Ccont[Cuba].HabIncOper eq VERDADEIRO)
  {
PosicaoGlobal = 154;

	if (AVC.Ccont[Cuba].ContIncOper eq -1)
	{ /* -- Inicio de incremento -- */
	  AVC.Ccont[Cuba].ContIncOper=0;
	  AVC.Ccont[Cuba].IncOper=AVC.Ccont[Cuba].IncOpInic;
	}
	if (AVC.Ccont[Cuba].ContIncOper < AVC.Ccont[Cuba].TIncOp)
	{ /* -- Durante incremento -- */
	  if (AVC.Ccont[Cuba].TipoIncOp eq INCREMENTO_RAMPA)
		AVC.Ccont[Cuba].IncOper=CalcRampa(AVC.Ccont[Cuba].IncOpInic,
						AVC.Ccont[Cuba].TIncOp,AVC.Ccont[Cuba].ContIncOper);
	  AVC.Ccont[Cuba].ContIncOper=AVC.Ccont[Cuba].ContIncOper+IntervCicCont;
	}
	else
	{ /* -- fim de incremento -- */
PosicaoGlobal = 155;

	  if (EST_AVC(Cuba).TabOpeAtiva)
	  { /* -- Fim de passo de tabela de operacao -- */
		AVC.Ccont[Cuba].PassoTabOpe++;
		passo=AVC.Ccont[Cuba].PassoTabOpe;
		if (passo ne MAX_PASSOS_TAB_OPE)
		{
		  tab_ope=AVC.Param[Cuba].NumTabOpe;
		  if (PTabOpe->Tab[tab_ope].Passo[passo].TipoIncr ne -1)
		  {
PosicaoGlobal = 156;

			AVC.Ccont[Cuba].VSetPoint=
				PTabOpe->Tab[tab_ope].Passo[passo].VSetPoint;
			AVC.Ccont[Cuba].TipoIncOp  =
				PTabOpe->Tab[tab_ope].Passo[passo].TipoIncr;
			AVC.Ccont[Cuba].IncOpInic  =
				PTabOpe->Tab[tab_ope].Passo[passo].VIncr;
			AVC.Ccont[Cuba].TIncOp     =
				PTabOpe->Tab[tab_ope].Passo[passo].Tempo; /*-- min --*/
			AVC.Ccont[Cuba].HabIncOper = VERDADEIRO;
			AVC.Ccont[Cuba].ContIncOper=0;
			AVC.Ccont[Cuba].IncOper=AVC.Ccont[Cuba].IncOpInic;
			if (AVC.Ccont[Cuba].ContIncOper < AVC.Ccont[Cuba].TIncOp)
			{ /* -- Durante incremento -- */
			  if (AVC.Ccont[Cuba].TipoIncOp eq INCREMENTO_RAMPA)
				AVC.Ccont[Cuba].IncOper=CalcRampa(AVC.Ccont[Cuba].IncOpInic,
						AVC.Ccont[Cuba].TIncOp,AVC.Ccont[Cuba].ContIncOper);
			  AVC.Ccont[Cuba].ContIncOper=AVC.Ccont[Cuba].ContIncOper+IntervCicCont;
			}
		  }
		  else
		  { /* -- ultimo passo -> fim da tabela -- */
			EST_AVC(Cuba).TabOpeAtiva=FALSO;
			AVC.Ccont[Cuba].VSetPoint=AVC.Param[Cuba].VSetPointCnf;
			AVC.Ccont[Cuba].IncOper=0.0;
			AVC.Ccont[Cuba].ContIncOper=-1;
			AVC.Ccont[Cuba].HabIncOper=FALSO;
		  }
		}
		else
		{ /* -- ultimo passo -> fim da tabela -- */
		  EST_AVC(Cuba).TabOpeAtiva=FALSO;
		  AVC.Ccont[Cuba].VSetPoint=AVC.Param[Cuba].VSetPointCnf;
		  AVC.Ccont[Cuba].IncOper=0.0;
		  AVC.Ccont[Cuba].ContIncOper=-1;
		  AVC.Ccont[Cuba].HabIncOper=FALSO;
		}
	  }
	  else
	  { /* -- Fim de incremento de operacao normal -- */
		AVC.Ccont[Cuba].IncOper=0.0;
		AVC.Ccont[Cuba].ContIncOper=-1;
		AVC.Ccont[Cuba].HabIncOper=FALSO;
	  }
	}
  }

  if(AVC.ParUser2[Cuba].InibIncOpTemp eq VERDADEIRO and
	AVC.User3[Cuba].Temperatura > AVC.ParUser2[Cuba].TempMaxInibInc and
	EST_AVC(Cuba).TabOpeAtiva eq FALSO)
  {
	AVC.Ccont[Cuba].IncOper=0.0;
	AVC.Ccont[Cuba].ContIncOper=-1;
	AVC.Ccont[Cuba].HabIncOper=FALSO;
  }  
}


/*
--------------------------------------------------------------------------------
| CalcRampa - Calcula i(t)= (v_ini-(v_ini/t_max)*cont_t)              |
--------------------------------------------------------------------------------
*/
float CalcRampa(float v_ini, int t_max, int cont_t)
{
PosicaoGlobal = 157;

  return(v_ini-(v_ini/t_max)*cont_t);
}

/*
--------------------------------------------------------------------------------
| CalcTriangulo - Calcula o valor do incremento triangulo		 	          |
--------------------------------------------------------------------------------
*/
float CalcTriangulo(float v_ini, int t_max, int cont_t, int t_pico)
{
  float retorno;

  if(cont_t <= t_pico)
  {
	retorno = (v_ini/t_pico)*cont_t;	
  }
  else
  {
 	retorno = (v_ini-(v_ini/(t_max-t_pico))*(cont_t - t_pico));
  }
  return(retorno);
}


/* -- fim do arquivo TrataInc.c -- */
