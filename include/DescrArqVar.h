/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.1

	PROJETO		: SCORE - CONTROLE DE REDUCOES

	SISTEMA		: TODOS

	ARQUIVO		: DescrArqVar.h

	CONTEUDO	: Contem as definicoes de todas as variaveis logaveis do sistema

	AUTOR		: Alexandre Bandeira

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0          -      DATA  : 05/02/95

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
03/01/2001 | Inclusao de tabelas para o Atn8                    | Leonel
-------------------------------------------------------------------------------
14/02/2001 | Separacao das variaveis da sala 86 KA              | Carlos
-------------------------------------------------------------------------------
$Id: DescrArqVar.h.user,v 1.1.1.1.10.1 2012/09/28 17:09:16 leo Exp $

$Log: DescrArqVar.h.user,v $
Revision 1.1.1.1.10.1  2012/09/28 17:09:16  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

Revision 1.36  2008/11/27 21:26:37  marcelo
Inclusao de variaveis para novo tratamento de ruido lento da mesma forma
que o ruido rapido.

Revision 1.35  2008/10/13 17:49:20  leo
Variaveis para o algoritmo de manobra de cruzeiro.

Revision 1.34  2008/08/05 15:09:07  leo
Alterados incrementos iniciais de quebrada, corrida e troca de pinos para permitir
valores negativos.

Revision 1.33  2008/08/04 20:31:42  leo
Incluido flag ReleTempoMM (CBA).

Revision 1.32  2008/08/01 20:51:30  leo
Incluidas variaveis para tratamento de falha de sopro automatico.
Incluida variavel para contabilizar DxLim (EstatEa) durante espera de EA
para retirar ao final a diferenca.

Revision 1.31  2008/07/08 13:26:50  leo
Incluidos novos limites para tratamento de ruidos.

Revision 1.30  2008/07/02 20:23:43  alex
nao subir camisa junto com movimentacao de anodo

Revision 1.29  2008/07/01 13:28:08  leo
Inclusao de novos parametros para novas acoes Tabela de EA (TEaLimiteVMaior,
TEaLimiteVMenor e TEaMaxSopros).

Revision 1.28  2008/02/18 21:25:05  leo
Inclusao variavel Regua

Revision 1.27  2007/03/19 14:52:14  leo
Criacao de semaforo de leitura da tabela ccont_mcp e correcoes de
formato no DescrArqVar em pre-operacao (sala VII cba)

Revision 1.26  2007/03/02 18:45:51  leo
Correcao tratamento para manobra de cruzeiro

Revision 1.25  2007/02/28 22:22:18  leo
Inclusao de tratamento de manobra de cruzeiro.

Revision 1.24  2006/12/27 14:55:53  leo
Incluida variavel TUltEa para indicar tempo em relacao ao ultimo EA (grafico
de cubas - controle)

Revision 1.23  2006/12/21 18:04:15  alex
novo ope tabela alternativa

Revision 1.22  2005/12/20 18:19:36  clage
*** empty log message ***

Revision 1.21  2005/10/14 18:04:32  leo
Alteracao da unidade de engenharia dos parametros de quebrada preventiva de horas
para minutos.

Revision 1.20  2005/09/02 14:25:48  leo
Alteracao nivel acesso para variaveis da configuracao de processo/metal.

Revision 1.19  2005/07/21 17:51:25  alex
nova configuracao metal/operacional

Revision 1.18  2005/06/17 12:13:59  clage
Incluidas variaveis do relat. de integracao e trat. VInst > VEaXLim no EA

Revision 1.17  2005/06/01 14:33:50  alex
colocado mais variaveis no controle do RelCuba

Revision 1.16  2005/05/31 19:37:32  leo
Correcoes feitas durante primeira pre-operacao CBA sala 125kA VI

Revision 1.15  2004/08/03 19:52:47  clage
Incluido parametros de flexibilizacao de quebrada preventiva

Revision 1.14  2004/07/28 20:00:09  leo
Inclusao variavel de percentual de erro para comparacao de valores da
Atn1.4 reserva com a principal para a CBA em sistemas com 2 Atn1.4.

******************************************************************************/


#include <IniArqVar.h>

#ifdef	PROGRAMA_PRINCIPAL

/* algoritmos do usuario */
t_NomeAlgCtr NAlgCtr[] =
{
/* 09 */  "",
/* 10 */  "",
/* 11 */  "",
/* 12 */  "",
/* 13 */  ""
};

/* tabelas do usuario */

t_NomeTabelas NTabelas[] =
{
/* G0  */ "Parametros Cuba",  
/* G1  */ "Ciclo leitura",
/* G2  */ "Ciclo leitura MCP", /* maximo 18 carac. */
/* G3  */ "Ciclo Controle",
/* G4  */ "Efeito Anodico",
/* G5  */ "Ruido",
/* G6  */ "Supervisao Diaria",
/* G7  */ "Status Digital",
/* G8  */ "Linha",
/* G9  */ "Alimentacao",
/* G10 */ "",
/* G11 */ "",
/* G12 */ "",
/* G13 */ "",
/* G14 */ "",
/* G15 */ ""
};

/*--- Estrutura de descricao das variaveis de parametros do AVC ---*/
t_par_var_log VarParAvc[] =
{
  "SET POINT",					"",		NULL,		NIVEL_LOG, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "VSetPoint",					"V",		&VarParamAvc.VSetPointCnf,			NIVEL_LOG, FLOAT,	"%-6.2f",	3.0,	6.0,	1.0,	PAR_COLETOR orb OPC_RW, AT, "VSetP", "Controle1", G0,
  "Bemf",						"V",		&VarParamAvc.Bemf,					NIVEL_SUPER, FLOAT,	"%-4.2f",	0.0,	100.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "INCREMENTOS",				"",			NULL,	NIVEL_LOG, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
#ifdef INCREMENTO_RESISTENCIA
  "RIncMax",					"MiOhm",	&VarParamAvc.VIncMax,				NIVEL_SUPER, FLOAT,	"%-6.3f",	-6.0,	6.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
#else
  "VIncMax",					"mV",		&VarParamAvc.VIncMax,				NIVEL_CONFIG_0, FLOAT,	"%-5.1f",	0.0,	999.0,	1000.,	PAR_CUBAS, AT, "", "", G0,
#endif
  "TMaxIncOper",				"min",		&VarParamAvc.TMaxIncOper,			NIVEL_CONFIG_0, INT,	"%-5.0f",	0.0,   28800.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "HabTabOpe",	      			"0=D/1=H", 	&VarParamAvc.HabTabOpe,       		NIVEL_LOG,		INT,	"%-2.0f",   0.0,      1.0,  1.0,	PAR_COLETOR, AT, "", "", G0,
  "NumTabOpe",        			"",    		&VarParamAvc.NumTabOpe,             NIVEL_LOG,		INT,	"%-2.0f",  	0.0,      9.0,  1.0,	PAR_CUBAS, AT, "", "", G0,
#ifdef INCREMENTO_RESISTENCIA
  "IncSifInic",					"MiOhm",	&VarParamAvc.IncCorrInic,			NIVEL_SUPER, FLOAT,	"%-6.3f",	-6.0,	6.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
#else
  "IncCorrInic",				"mV",		&VarParamAvc.IncCorrInic,			NIVEL_CONFIG_0, FLOAT,	"%-5.0f",	-300.0,	300.0,	1000.,	PAR_CUBAS, AT, "", "", G0,
#endif
  "TIncCorr",					"min",		&VarParamAvc.TIncCorr,				NIVEL_CONFIG_0, INT,	"%-5.0f",	0.0,   28800.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "TTrataCorr"	,				"seg",		&VarParamAvc.TAcresBCSCorr,			NIVEL_SUPER, INT,	"%-6.0f",	0.0,	1e6,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "TEfeitoCorr",				"seg",		&VarParamAvc.TEfeitoCorr,			NIVEL_SUPER, INT,	"%-6.0f",	0.0,	1e6,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "AcresBCSCorr",				"MiOhm",	&VarParamAvc.AcresBCSCorr,			NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	50.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  #ifdef INCREMENTO_RESISTENCIA
   "IncQuebInic",				"MiOhm",	&VarParamAvc.IncQuebInic,			NIVEL_SUPER, FLOAT,	"%-6.3f",	-6.0,	6.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  #else
   "IncQuebInic",				"mV",		&VarParamAvc.IncQuebInic,			NIVEL_SUPER, FLOAT,	"%-5.0f",	-300.0,	300.0,	1000.,	PAR_CUBAS, AT, "", "", G0,
  #endif
  "TIncQueb",					"min",		&VarParamAvc.TIncQueb,				NIVEL_SUPER, INT,	"%-5.0f",	0.0,   28800.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "TipoIncQueb",				"1=C,2=R",	&VarParamAvc.TipoIncQueb,			NIVEL_SUPER, INT,	"%-1.0f",	1.0,	2.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "TEfeitoQueb",				"seg",		&VarParamAvc.TEfeitoQueb,			NIVEL_SUPER, INT,	"%-6.0f",	0.0,	1e6,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "AcresBCIQueb",				"MiOhm",	&VarParamAvc.AcresBCIQueb,			NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	20.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "TAcresBCIQueb",				"seg",		&VarParamAvc.TAcresBCIQueb,			NIVEL_SUPER, INT,	"%-6.0f",	0.0,	1e6,	1.0,	PAR_CUBAS, AT, "", "", G0,
#ifdef INCREMENTO_RESISTENCIA
  "IncTPinosInic",      		"MiOhm",   	&VarParamAvc.IncTPinosInic,         NIVEL_SUPER, FLOAT, "%-6.3f",	-6.0,	6.0,   1e6,	PAR_CUBAS, AT, "", "", G0,
#else
  "IncTPinosInic",      		"mV",   	&VarParamAvc.IncTPinosInic,         NIVEL_CONFIG_0, FLOAT, "%-5.0f",   -1000.0,   1000.0,   1000.0,	PAR_CUBAS, AT, "", "", G0,
#endif
  "TIncTPinos",       			"min",    	&VarParamAvc.TIncTPinos,       		NIVEL_CONFIG_0, INT,	"%-5.0f",   0.0,  28800.0,  1.0,	PAR_CUBAS, AT, "", "", G0,
  "TipoIncTPinos", 				"1=C,2=R,3=T",  &VarParamAvc.TipoIncTPinos,    		NIVEL_CONFIG_0, INT, 	"%-2.0f",   1.0,      3.0,  1.0,	PAR_CUBAS, AT, "", "", G0,
  "TIncPicoTPinos",				"min",		&VarParamAvc.TIncPicoTPinos,			NIVEL_CONFIG_0, SHORT_INT,	"%-5.0f",	1.0,  28800.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "HabIncTPinos",				"0=Des,1=Hab",&VarParamAvc.HabIncTPinos,     	NIVEL_CONFIG_0, INT,  	"%-2.0f",   0.0,      1.0,  1.0,	PAR_CUBAS, AT, "", "", G0,
  "TEfeitoTPinos",				"min", 		&VarParamAvc.TEfeitoTPinos,    		NIVEL_SUPER, INT,  	"%-3.0f",   0.0,     180.0,  1.0,	PAR_CUBAS, AT, "", "", G0,
  "HabIncQPrevEa",				"0=Des,1=Hab",&VarParamAvc.HabIncUsuario,     	NIVEL_SUPER, INT,  	"%-2.0f",   0.0,      1.0,  1.0,	PAR_CUBAS, AT, "", "", G0,
#ifdef INCREMENTO_RESISTENCIA
  "IncQPrevEa",		      		"MiOhm",   	&VarParamAvc.IncUsuarioInic,        NIVEL_CONFIG_0, FLOAT, "%-6.2f",   0.0,   	6.0,   1e6,	PAR_CUBAS, AT, "", "", G0,
#else
  "IncQPrevEa",		      		"mV",   	&VarParamAvc.IncUsuarioInic,        NIVEL_CONFIG_0, FLOAT, "%-6.2f",   0.0,   300.0,   1000.0,	PAR_CUBAS, AT, "", "", G0,
#endif
  "TIncQPrevEa",       			"min",    	&VarParamAvc.TIncUsuario,       		NIVEL_CONFIG_0, INT,	"%-5.0f",   0.0,  28800.0,  1.0,	PAR_CUBAS, AT, "", "", G0,
  "TipoIncQPrevEa",				"1=C,2=R",  &VarParamAvc.TipoIncUsuario,    		NIVEL_CONFIG_0, INT, 	"%-2.0f",   1.0,      2.0,  1.0,	PAR_CUBAS, AT, "", "", G0,

  "MANOBRA DE CRUZEIRO",		"",			NULL,	NIVEL_LOG, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "TEfeitoMCruzeiro",				"min", 	&VarParamAvc.TEfeitoCruzeiro,  		NIVEL_SUPER, INT,  	"%-3.0f",   0.0,     180.0,  1.0,	PAR_CUBAS, AT, "", "", G0,

  "LOOP CORRENTE",			"",		NULL,	NIVEL_CONFIG_0, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "HabCorrEmerg",			"0=Des,1=Hab", 	&VarParamAvc.HabCorrEmerg,  		NIVEL_SUPER, BYTE,  	"%-1.0f",   0.0,     1.0,  1.0,	PAR_CUBAS, AT, "", "", G0,
  "ForcaCorEmerg",			"0=Des,1=Hab", 	&VarParamAvc.ForcaCorrEmerg,  		NIVEL_SUPER, BYTE,  	"%-1.0f",   0.0,     1.0,  1.0,	PAR_CUBAS, AT, "", "", G0,

  "BOOSTER CORRENTE",			"",		NULL,	NIVEL_CONFIG_0, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "HabBooster",					"0=Des,1=Hab",&VarParamAvc.HabilitaBooster,		NIVEL_CONFIG_0, BYTE,"%-1.0f",	0.0,	1.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "IBoosterNominal",			"kA",		&VarParamAvc.IBoosterNominal,		NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	160.0,	1e-3,	PAR_CUBAS, AT, "", "", G0,

  "BANDAS",						"",		NULL,	NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "BandaContInf",				"MiOhm",	&VarParamAvc.BandaContInf,			NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	20.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "BandaContSup",				"MiOhm",	&VarParamAvc.BandaContSup,			NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	20.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "BandaMortaInf",				"MiOhm",	&VarParamAvc.BandaMortaInf,			NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	20.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "BandaMortaSup",				"MiOhm",	&VarParamAvc.BandaMortaSup,			NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	20.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "AcrescBMortaSup",			"MiOhm",	&VarParamAvc.AcrescBMortaSup,		NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	20.0,	1e6,	PAR_CUBAS, AT, "", "", G0,

  "EFEITO ANODICO",				"",		NULL,	NIVEL_CONFIG_0, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "TEfeitoEa",				"HH:MM",		&VarParamAvc.TEfeitoEa,				NIVEL_SUPER, T_HORA,	"%-5s",		0.0,	86340,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "EaAtrasoMax",				"min",		&VarParamAvc.EaAtrasoMax,			NIVEL_CONFIG_0, INT,	"%-5.0f",	0.0,   28880.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
/* ATENCAO - este parametro eh gravado na remota da sala 125ka! Nao aumentar limite maximo sem verificar implicacoes no firmware da atn8 */
  "EaTempoEspera",				"seg",		&VarParamAvc.EaTempoEspera,			NIVEL_SUPER, INT,	"%-6.0f",	0.0,   30000.0,	1.0,	PAR_CUBAS, AT, "", "", G0,

  "EaVoltLim",					"V",		&VarParamAvc.EaVoltLim,				NIVEL_CONFIG_1, FLOAT,	"%-5.2f",	0.0,	99.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "EaEspLim",					"V",		&VarParamAvc.EaEspLim,				NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	99.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "HabEliminaEa",				"0=Des,1=Hab",&VarParamAvc.HabEliminaEa,		NIVEL_CONFIG_0, INT,	"%-1.0f",	0.0,	1.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "NumTabEliEaLento",			"",			&VarParamAvc.NumTabEliEaLento,		NIVEL_CONFIG_0, INT,	"%-1.0f",	0.0,	4.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "NumTabEliEaRapido",			"",			&VarParamAvc.NumTabEliEaRapido,		NIVEL_CONFIG_0, INT,	"%-1.0f",	0.0,	4.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "NumTabEliEaMRapido",			"",			&VarParamAvc.NumTabEliEaMRapido,	NIVEL_CONFIG_0, INT,	"%-1.0f",	0.0,	4.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "NumTabAlternativa",			"",			&VarParamAvc.NumTabEliEaAltern,		NIVEL_CONFIG_0, INT,	"%-1.0f",	0.0,	4.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "TEaLimVMaior",				"V",		&VarParamAvc.TEaLimiteVMaior,		NIVEL_SUPER, 	FLOAT,	"%-5.2f",	0.0,	99.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "TEaLimVMenor",				"V",		&VarParamAvc.TEaLimiteVMenor,		NIVEL_SUPER, 	FLOAT,	"%-5.2f",	0.0,	99.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "TEaMaxSopros",				"",			&VarParamAvc.TEaMaxSopros,			NIVEL_SUPER, SHORT_INT,	"%-3.0f",	0.0,	999.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "TempoAtivaTEa",				"seg",	&VarParamAvc.TempoAtivaTEa,	  NIVEL_SUPER, SHORT_INT, "%-4.0f",	0.0,  3600.0, 1.0,	PAR_CUBAS, AT, "", "", G0,
  "VEaForte",					"V",		&VarParamAvc.VEaForte,					NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	100.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "VEaFraco",					"V",		&VarParamAvc.VEaFraco,					NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	100.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "FreqEa",						"",			&VarParamAvc.FreqEa,					NIVEL_SUPER, SHORT_INT,	"%-2.0f",	0.0,	100.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "HabAtEa",	"0=D,1=EA,2=QP,3=1+2",		&VarParamAvc.HabAtEa,					NIVEL_SUPER, BYTE,	"%-2.0f",	0.0,	3.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "VEaXLim",					"V",		&VarParamAvc.VEaXLim,				NIVEL_CONFIG_1, FLOAT,	"%-5.2f",	0.0,	99.0,	1.0,	PAR_CUBAS, AT, "", "", G0,

  "PREVISAO E. A.",				"",		NULL,	NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "HabPrevEa",					"",			&VarParamAvc.HabPrevEa,		 		NIVEL_SUPER, SHORT_INT, "%-1.0f",	0.0,  1.0, 	1.0,	PAR_CUBAS, AT, "", "", G0,
  "EaPrevDeriv",				"MiOhm/h",	&VarParamAvc.EaPrevDeriv,			NIVEL_SUPER, FLOAT,	"%-6.3f",	0.0,	99.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "IntervEaPrevDeriv",			"min",	    &VarParamAvc.IntervEaPrevDeriv,		NIVEL_SUPER, INT,  "%-5.0f",   2.0,   32400.0, 1.0,		PAR_CUBAS, AT, "", "", G0,
  "RSuaveDerivMin",   			"MiOhm/h",	&VarParamAvc.RSuaveDerivMin,		NIVEL_SUPER, FLOAT,"%-6.3f",   -9.0,     10.0, 1e6,		PAR_CUBAS, AT, "", "", G0,
  "RSuaveDerivMax",   			"MiOhm/h",	&VarParamAvc.RSuaveDerivMax,   		NIVEL_SUPER, FLOAT,"%-6.3f",   -9.0,     10.0, 1e6,		PAR_CUBAS, AT, "", "", G0,
  "DerivHEaLento",    			"MiOhm/h",	&VarParamAvc.DerivHEaLento,    		NIVEL_SUPER, FLOAT,"%-6.3f",   0.0,      99.0, 1e6,		PAR_CUBAS, AT, "", "", G0,
  "DerivHEaRap",      			"MiOhm/h",	&VarParamAvc.DerivHEaRap,      		NIVEL_SUPER, FLOAT,"%-6.3f",   0.0,      99.0, 1e6,		PAR_CUBAS, AT, "", "", G0,
  "DerivInibeMovBaixa",			"MiOhm/h",	&VarParamAvc.DerivInibeMovBaixa,   	NIVEL_SUPER, FLOAT,"%-6.3f",   -5.0,      0.0, 1e6,		PAR_CUBAS, AT, "", "", G0,
  "DerivInibeMovAlta",			"MiOhm/h",	&VarParamAvc.DerivInibeMovAlta,    	NIVEL_SUPER, FLOAT,"%-6.3f",    0.0,      5.0, 1e6,		PAR_CUBAS, AT, "", "", G0,
  "IntervDerivInibeMov",		"min", 		&VarParamAvc.IntervDerivInibeMov,	NIVEL_SUPER, INT,  "%-5.0f",   2.0,   32400.0, 1.0,		PAR_CUBAS, AT, "", "", G0,
  "EaPrevDerivFim",    			"MiOhm/h",	&VarParamAvc.EaPrevDerivFim,		NIVEL_SUPER, FLOAT,"%-6.3f",   0.0,      99.0, 1e6,		PAR_CUBAS, AT, "", "", G0,
  "IntervFimEaPrevDeriv",		"min",  	&VarParamAvc.IntervFimEaPrevDeriv,	NIVEL_SUPER, INT,  "%-5.0f",   2.0,   32400.0, 1.0,		PAR_CUBAS, AT, "", "", G0,
  "KSuaveDeriv",				"",			&VarParamAvc.KSuaveDeriv,			NIVEL_SUPER, FLOAT,	"%-5.3f",	0.0,	  1.0,	1.0,	PAR_CUBAS, AT, "", "", G0,

  "RUIDO",						"",		NULL,	NIVEL_LOG, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "HabIncRLent",				"0=Des,1=Hab",&VarParamAvc.HabIncRLent,			NIVEL_SUPER, INT,	"%-1.0f",	0.0,	  1.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "NumJanRLent",				"",			&VarParamAvc.NumJanRLent,			NIVEL_SUPER, INT,	"%-1.0f",	1.0,	  8.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "IntervJanRLent",    			"horas",	&VarParamAvc.IntervJanRLent,   		NIVEL_SUPER, INT, 	"%-1.0f",   1.0,      8.0,  1.0,	PAR_CUBAS, AT, "", "", G0,
  "RuidoLFra1",					"MiOhm",	&VarParamAvc.RuidoL[0],				NIVEL_SUPER, FLOAT,	"%-6.3f",	0.0,	 99.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "RuidoLFra2",					"MiOhm",	&VarParamAvc.RuidoL[1],				NIVEL_SUPER, FLOAT,	"%-6.3f",	0.0,	 99.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "RuidoLFra3",					"MiOhm",	&VarParamAvc.RuidoL[2],				NIVEL_SUPER, FLOAT,	"%-6.3f",	0.0,	 99.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "RuidoLFor1",					"MiOhm",	&VarParamAvc.RuidoL[3],				NIVEL_SUPER, FLOAT,	"%-6.3f",	0.0,	 99.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "RuidoLFor2",					"MiOhm",	&VarParamAvc.RuidoL[4],				NIVEL_SUPER, FLOAT,	"%-6.3f",	0.0,	 99.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
#ifdef INCREMENTO_RESISTENCIA
  "IncRuidoLentoF1",			"MiOhm",	&VarParamAvc.IncRuidoLento[0],		NIVEL_CONFIG_0, FLOAT,	"%-6.3f",	-6.0,	6.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "IncRuidoLentoF2",			"MiOhm",	&VarParamAvc.IncRuidoLento[1],		NIVEL_SUPER, FLOAT,	"%-6.3f",	-6.0,	6.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "IncRuidoLentoF3",			"MiOhm",	&VarParamAvc.IncRuidoLento[2],		NIVEL_SUPER, FLOAT,	"%-6.3f",	-6.0,	6.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "IncRuidoLentoF4",			"MiOhm",	&VarParamAvc.IncRuidoLento[3],		NIVEL_SUPER, FLOAT,	"%-6.3f",	-6.0,	6.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "IncRuidoLentoF5",			"MiOhm",	&VarParamAvc.IncRuidoLento[4],		NIVEL_SUPER, FLOAT,	"%-6.3f",	-6.0,	6.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
#else
  "IncRuidoLentFra1",			"mV",		&VarParamAvc.IncRuidoLento[0],		NIVEL_SUPER, FLOAT,	"%-6.2f",	-300.0,	300.0,	1e3,	PAR_CUBAS, AT, "", "", G0,
  "IncRuidoLentFra2",			"mV",		&VarParamAvc.IncRuidoLento[1],		NIVEL_SUPER, FLOAT,	"%-6.2f",	-300.0,	300.0,	1e3,	PAR_CUBAS, AT, "", "", G0,
  "IncRuidoLentFra3",			"mV",		&VarParamAvc.IncRuidoLento[2],		NIVEL_SUPER, FLOAT,	"%-6.2f",	-300.0,	300.0,	1e3,	PAR_CUBAS, AT, "", "", G0,
  "IncRuidoLentFor1",			"mV",		&VarParamAvc.IncRuidoLento[3],		NIVEL_SUPER, FLOAT,	"%-6.2f",	-300.0,	300.0,	1e3,	PAR_CUBAS, AT, "", "", G0,
  "IncRuidoLentFor2",			"mV",		&VarParamAvc.IncRuidoLento[4],		NIVEL_SUPER, FLOAT,	"%-6.2f",	-300.0,	300.0,	1e3,	PAR_CUBAS, AT, "", "", G0,
#endif
  "HabIncRRap",					"0=Des,1=Hab",&VarParamAvc.HabIncRRap,			NIVEL_SUPER,	 INT,	"%-1.0f",	0.0,	  1.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "NumJanRRap",					"",			&VarParamAvc.NumJanRRap,			NIVEL_SUPER, INT,	"%-1.0f",	1.0,	  8.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "IntervJanRRap",    			"horas",	&VarParamAvc.IntervJanRRap,    		NIVEL_SUPER, INT, 	"%-1.0f",   1.0,      8.0,  1.0,	PAR_CUBAS, AT, "", "", G0,
  "RuidoRFra1",					"MiOhm",	&VarParamAvc.RuidoR[0],				NIVEL_SUPER, FLOAT,	"%-6.3f",	0.0,	 99.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "RuidoRFra2",					"MiOhm",	&VarParamAvc.RuidoR[1],				NIVEL_SUPER, FLOAT,	"%-6.3f",	0.0,	 99.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "RuidoRFra3",					"MiOhm",	&VarParamAvc.RuidoR[2],				NIVEL_SUPER, FLOAT,	"%-6.3f",	0.0,	 99.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "RuidoRFor1",					"MiOhm",	&VarParamAvc.RuidoR[3],				NIVEL_SUPER, FLOAT,	"%-6.3f",	0.0,	 99.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "RuidoRFor2",					"MiOhm",	&VarParamAvc.RuidoR[4],				NIVEL_SUPER, FLOAT,	"%-6.3f",	0.0,	 99.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
#ifdef INCREMENTO_RESISTENCIA
  "IncRuidoRapF1",				"MiOhm",	&VarParamAvc.IncRuidoRap[0],		NIVEL_SUPER, FLOAT,	"%-6.3f",	-6.0,	6.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "IncRuidoRapF2",				"MiOhm",	&VarParamAvc.IncRuidoRap[1],		NIVEL_SUPER, FLOAT,	"%-6.3f",	-6.0,	6.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "IncRuidoRapF3",				"MiOhm",	&VarParamAvc.IncRuidoRap[2],		NIVEL_SUPER, FLOAT,	"%-6.3f",	-6.0,	6.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "IncRuidoRapF4",				"MiOhm",	&VarParamAvc.IncRuidoRap[3],		NIVEL_SUPER, FLOAT,	"%-6.3f",	-6.0,	6.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "IncRuidoRapF5",				"MiOhm",	&VarParamAvc.IncRuidoRap[4],		NIVEL_SUPER, FLOAT,	"%-6.3f",	-6.0,	6.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
#else
  "IncRuidoRapFra1",			"mV",		&VarParamAvc.IncRuidoRap[0],		NIVEL_SUPER, FLOAT,	"%-6.2f",	-300.0,	300.0,	1e3,	PAR_CUBAS, AT, "", "", G0,
  "IncRuidoRapFra2",			"mV",		&VarParamAvc.IncRuidoRap[1],		NIVEL_SUPER, FLOAT,	"%-6.2f",	-300.0,	300.0,	1e3,	PAR_CUBAS, AT, "", "", G0,
  "IncRuidoRapFra3",			"mV",		&VarParamAvc.IncRuidoRap[2],		NIVEL_SUPER, FLOAT,	"%-6.2f",	-300.0,	300.0,	1e3,	PAR_CUBAS, AT, "", "", G0,
  "IncRuidoRapFor1",			"mV",		&VarParamAvc.IncRuidoRap[3],		NIVEL_SUPER, FLOAT,	"%-6.2f",	-300.0,	300.0,	1e3,	PAR_CUBAS, AT, "", "", G0,
  "IncRuidoRapFor2",			"mV",		&VarParamAvc.IncRuidoRap[4],		NIVEL_SUPER, FLOAT,	"%-6.2f",	-300.0,	300.0,	1e3,	PAR_CUBAS, AT, "", "", G0,
#endif
  "HabEvRuido",				"0=Des,1=Hab",&VarParamAvc.HabEvRuido,				NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	  1.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "NJanRRapCons",				"",			&VarParamAvc.NJanRRapCons,		 	NIVEL_SUPER, SHORT_INT, "%-1.0f",	0.0,  15.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "NJanRLenCons",				"",			&VarParamAvc.NJanRLenCons,		 	NIVEL_SUPER, SHORT_INT, "%-1.0f",	0.0,  15.0,	1.0,	PAR_CUBAS, AT, "", "", G0,

  "MOVIMENTACAO",				"",		NULL,	NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "HabContResist",				"",			&VarParamAvc.HabContResist, 		NIVEL_SUPER, SHORT_INT, "%-1.0f",	0.0,  1.0, 	1.0,	PAR_CUBAS, AT, "", "", G0,
  "TEfeitoMoveBaixo",			"seg",		&VarParamAvc.TEfeitoMoveBaixo,		NIVEL_SUPER, INT,	"%-5.0f",	0.0,  32400.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "TEfeitoMoveCima",			"seg",		&VarParamAvc.TEfeitoMoveCima,		NIVEL_SUPER, INT,	"%-5.0f",	0.0,  32400.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "DurMovBaixoMin",				"seg",		&VarParamAvc.DurMovBaixoMin,		NIVEL_SUPER, INT,	"%-2.0f",	0.0,	5.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "DurMovBaixoMax",				"seg",		&VarParamAvc.DurMovBaixoMax,		NIVEL_SUPER, INT,	"%-2.0f",	0.0,	5.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "KPb",						"",			&VarParamAvc.KPb,					NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	10.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "KbpwmTipico",				"nOhm/s",	&VarParamAvc.KbpwmTipico,			NIVEL_SUPER, FLOAT,	"%-7.2f",	1.0,  2000.0,	1e9,	PAR_CUBAS, AT, "", "", G0,
  "MinKbpwm",					"nOhm/s",	&VarParamAvc.MinKbpwm,				NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,  2000.0,	1e9,	PAR_CUBAS, AT, "", "", G0,
  "DurMovCimaMin",				"seg",		&VarParamAvc.DurMovCimaMin,			NIVEL_SUPER, INT,	"%-2.0f",	0.0,	5.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "DurMovCimaMax",				"seg",		&VarParamAvc.DurMovCimaMax,			NIVEL_SUPER, INT,	"%-2.0f",	0.0,	5.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "KPc",						"",			&VarParamAvc.KPc,					NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	10.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "KcpwmTipico",				"nOhm/s",	&VarParamAvc.KcpwmTipico,			NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,  2000.0,	1e9,	PAR_CUBAS, AT, "", "", G0,
  "MinKcpwm",					"nOhm/s",	&VarParamAvc.MinKcpwm,				NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,  2000.0,	1e9,	PAR_CUBAS, AT, "", "", G0,
  "MaxAgarraAnodo",				"",			&VarParamAvc.MaxAgarraAnodo,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	9.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "HabMovIniQueb",			"0=Des,1=Hab", 	&VarParamAvc.HabMovIniQueb,  		NIVEL_SUPER, BYTE,  	"%-1.0f",   0.0,     1.0,  1.0,	PAR_CUBAS, AT, "", "", G0,
  "TempMovIniQueb",			"seg", 	&VarParamAvc.TempMovIniQueb,  		NIVEL_SUPER, BYTE,  	"%-2.0f",   0.0,    10.0,  1.0,	PAR_CUBAS, AT, "", "", G0,

  "SUPERVISAO ESPECIAL",		"",		NULL,	NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,   0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "RMinPartidoSupEsp",			"MiOhm",  	&VarParamAvc.RMinPartidoSupEsp,		NIVEL_SUPER, FLOAT, "%-8.2f", -1000.0,  1000.0,   1e6,	PAR_CUBAS, AT, "", "", G0,
  "RMaxPartidoSupEsp",			"MiOhm",  	&VarParamAvc.RMaxPartidoSupEsp,		NIVEL_SUPER, FLOAT, "%-8.2f", -1000.0,  1000.0,   1e6,	PAR_CUBAS, AT, "", "", G0,
  "RMinLigadoSupEsp", 			"MiOhm",  	&VarParamAvc.RMinLigadoSupEsp, 		NIVEL_SUPER, FLOAT, "%-8.2f", -1000.0,  1000.0,   1e6,	PAR_CUBAS, AT, "", "", G0,
  "RMaxLigadoSupEsp", 			"MiOhm",  	&VarParamAvc.RMaxLigadoSupEsp, 		NIVEL_SUPER, FLOAT, "%-8.2f", -1000.0,  1000.0,   1e6,	PAR_CUBAS, AT, "", "", G0,
  "RMinDesligSupEsp", 			"MiOhm",  	&VarParamAvc.RMinDesligSupEsp, 		NIVEL_SUPER, FLOAT, "%-8.2f", -1000.0,  1000.0,   1e6,	PAR_CUBAS, AT, "", "", G0,
  "RMaxDesligSupEsp", 			"MiOhm",  	&VarParamAvc.RMaxDesligSupEsp, 		NIVEL_SUPER, FLOAT, "%-8.2f", -1000.0,  1000.0,   1e6,	PAR_CUBAS, AT, "", "", G0,

  "NUMERO ALGORITMO",			"",		NULL,		NIVEL_SUPER, INT,	"%-2.0f",	0.0,	99.0,	1.0,	TITULO_1, AT, "", "", G0,
  "NumAlgControle",				"",		&VarParamAvc.NumAlgCtr,		NIVEL_SUPER, MASC_BITS16,	"%-10s",	0.0,	ALG_TODOS,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "ALIMENTACAO AUTO",			"",		NULL,	NIVEL_SUPER, INT,	"%-2.0f",	0.0,	0.0,	1.0,	TITULO_1, AT, "", "", G0,
  "AlimAuto",	"0=Nao,1=PF,2=Bar",		&VarParamAvc.TemPF,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	2.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "ANALISE EVENTOS",			"",		NULL,	NIVEL_SUPER, INT,	"%-2.0f",	0.0,	0.0,	1.0,	TITULO_1, AT, "", "", G0,
  "TempoEvCuba",				"min",	&VarParamAvc.TempoEvCuba,	NIVEL_SUPER, SHORT_INT,	"%-3.0f",	0.0,	999.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "MaxEvCuba",					"",		&VarParamAvc.MaxEvCuba,		NIVEL_SUPER, SHORT_INT,	"%-3.0f",	0.0,	999.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "ATRASO INICIO EA",			"",		NULL,		NIVEL_SUPER, INT,	"%-2.0f",	0.0,	99.0,	1.0,	TITULO_1, AT, "", "", G0,
  "NCicIniEaTPinos",			"",		&VarParamAvc.NCicIniEaTAnodo, NIVEL_SUPER, SHORT_INT, "%-4.0f",	0.0,  3000.0, 1.0,	PAR_CUBAS, AT, "", "", G0,
/* ATENCAO - este parametro eh gravado na remota da sala 125ka! Nao aumentar limite maximo sem verificar implicacoes no firmware da atn8 */
  "NCicIniEaNormal",			"",		&VarParamAvc.NCicIniEaNormal, NIVEL_SUPER, SHORT_INT, "%-4.0f",	0.0,  3000.0, 1.0,	PAR_CUBAS, AT, "", "", G0,
  NULL,	NULL, 0, 0, 0,	NULL, 0.0, 0.0, 0.0, 0, 0, NULL, NULL
};

/*--- Estrutura de descricao das variaveis do ciclo de leitura do AVC ---*/
t_par_var_log VarCleitAvc[] =
{
  "BemfInst",		"V",	&VarCLeitAvc.BemfInst,			NIVEL_SUPER, FLOAT,	"%-4.2f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G1,
  "Iinst",			"kA",	&VarCLeitAvc.Iinst,			NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e-3,	TODAS_T, AT, "", "", G1,

 #ifdef	BOOSTER_CORRENTE
  "IBoosterInst",	"kA",	&VarCLeitAvc.IBoosterInst,	NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e-3,	TODAS_T, AT, "", "", G1,
 #endif

  "Rinst",			"MiOhm",&VarCLeitAvc.Rinst,			NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T orb OPC_R, AT, "", "", G1,
  "VetRinst[0]",	"MiOhm",&VarCLeitAvc.VetRinst[0],		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G1,
  "VetRinst[1]",	"MiOhm",&VarCLeitAvc.VetRinst[1],		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G1,
  "VetRinst[2]",	"MiOhm",&VarCLeitAvc.VetRinst[2],		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G1,
  "VetRinst[3]",	"MiOhm",&VarCLeitAvc.VetRinst[3],		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G1,
  "VetRinst[4]",	"MiOhm",&VarCLeitAvc.VetRinst[4],		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G1,
  "VetRinst[5]",	"MiOhm",&VarCLeitAvc.VetRinst[5],		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G1,
  "Vinst",			"V",	&VarCLeitAvc.Vinst,			NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1.0,	TODAS_T orb OPC_R, AT, "VInst", "Controle6", G1,
  "TUltimoEA",		"HH:MM", &VarCLeitAvc.TUltEa,			NIVEL_SUPER, T_HORA,"%-6s",		0.0,	360000,	1.0,	TODAS_T, AT, "TUltEA", "Controle9", G1,
  "TUltimoEAL",		"", 	&VarCLeitAvc.TUltEa,			NIVEL_SUPER, LONG,"%-7.0f",		0.0,	360000,	1.0,	TODAS_T orb OPC_R, AT, "", "", G1,
  "Pinst",			"KW",	&VarCLeitAvc.Pinst,			NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e-3,	TODAS_T, AT, "", "", G1,
  "NumCiclosLeit",	"",		&VarCLeitAvc.NumCiclosLeit,	NIVEL_SUPER, LONG,	"%-3.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G1,
  "HoraUltQueb",	"",		&VarCLeitAvc.HoraUltQueb,		NIVEL_SUPER, LONG,	"%-7.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G1,
  "HoraUltTPinos",	"",		&VarCLeitAvc.HoraUltTPinos,		NIVEL_SUPER, LONG,	"%-7.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G1,
  "HoraUltCruzeiro","",		&VarCLeitAvc.HoraUltCruzeiro,	NIVEL_SUPER, LONG,	"%-7.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G1,
  "HoraUltCorr",	"",	&VarCLeitAvc.HoraUltCorr,		NIVEL_SUPER, LONG,	"%-7.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G1,
  "ContL",			"",	&VarCLeitAvc.ContL,			NIVEL_SUPER, INT,	"%-5.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G1,
  "EstadoIO",		"",		&VarCLeitAvc.EstadoIO,			NIVEL_SUPER, INT,	"%-5.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G1,
  "RCicCorr",		"MiOhm",&VarCLeitAvc.RCicCorr,			NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G1,
  "ContLCicCorr",	"",	&VarCLeitAvc.ContLCicCorr,			NIVEL_SUPER, INT,	"%-5.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G1,
  NULL,	NULL, 0, 0, 0,	NULL, 0.0, 0.0, 0.0, 0, 0, NULL, NULL
};


/*--- Estrutura de descricao das variaveis do ciclo de controle(MCP) do AVC ---*/
t_par_var_log VarCcontMcpAvc[] =
{
  "Rmedio",				"MiOhm",&VarCcontMcp.RCicContlBruta,	NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G2,
  "RCicContlLiq",		"MiOhm",&VarCcontMcp.RCicContlLiq,		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G2,
  "RlentCicContl",		"MiOhm",&VarCcontMcp.RlentCicContl,		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G2,
  "RrapCicContl",		"MiOhm",&VarCcontMcp.RrapCicContl,		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G2,
  "RCicContBrutaMed",	"MiOhm",&VarCcontMcp.RCicContBrutaMed,	NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G2,
/* -- Alteracao - Inicio - 15/10/2002 - Leonel - Exibicao valores analogicos no relechelon -- */
 #ifdef	USA_ATN8
  "ANALOGICAS CUBA",	"",				NULL,						NIVEL_SUPER, INT,	"%-5.0f",	0.0,	1e6,	1.0,	TITULO_5, 	 AT, "", "", G2,
  "CorrenteCuba",	"kA",	&VarCcontMcp.ValorEnt[0],		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0, 999.0,		1e-3,	REL_ECHELON, AT, "CorCuba", "Controle7", G2,
  "Tensao",			"",		&VarCcontMcp.ValorEnt[1],		NIVEL_SUPER, FLOAT,	"%-6.3f",	0.0, 1000000.0,	1.0,	REL_ECHELON, AT, "", "", G2,
  "TempCarc",		"",		&VarCcontMcp.ValorEnt[2],		NIVEL_SUPER, FLOAT,	"%-6.3f",	0.0, 1000000.0,	1.0,	REL_ECHELON orb OPC_R, AT, "", "", G2,
   #ifdef	BOOSTER_CORRENTE
  "ICicContlMedCuba",	"kA",	&VarCcontMcp.ICicContlMedCuba,	NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0, 999.0,	1e-3,	REL_ECHELON, AT, "ICCMCub", "Controle8", G2,
   #endif
  "DifCorrenteCuba",	"kA",	&VarCcontMcp.IDifCuba,	NIVEL_SUPER, FLOAT,	"%-8.3f",	-999.0, 999.0,	1e-3,	REL_ECHELON, AT, "", "", G2,
  "TEMPERATURA ATN8",	"",				NULL,						NIVEL_SUPER, INT,	"%-5.0f",	0.0,	1e6,	1.0,	TITULO_5, 	 AT, "", "", G2,
  "TemperaturaAtn8",	"oC",	&VarCcontMcp.TemperaturaAtn8,	NIVEL_SUPER, BYTE,	"%-3.0f",	0.0, 999.0,	1.0,	REL_ECHELON, AT, "", "", G2,
 #else
   #ifdef	BOOSTER_CORRENTE
  "ICicContlMedCuba",	"kA",	&VarCcontMcp.ICicContlMedCuba,	NIVEL_SUPER, FLOAT,	"%-7.3f",	0.0, 999.0,	1e-3,	TODAS_T, AT, "", "", G2,
   #endif
 #endif
/* -- Alteracao - Fim - 15/10/2002 - Leonel - Exibicao valores analogicos no relechelon -- */

  /* -- Valores para supervisao -- */
  "PotCicContlBruta",	"KW",	&VarCcontMcp.PotCicContlBruta,	NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e-3,	TODAS_T, AT, "", "", G2,
  "PotCicContlLiq",		"KW",	&VarCcontMcp.PotCicContlLiq,	NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e-3,	TODAS_T, AT, "", "", G2,

  "VCicContlBruta",		"V",	&VarCcontMcp.VCicContlBruta,	NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1.0,	TODAS_T orb OPC_R, AT, "VCCont", "Controle4", G2,
  "VCicContlLiq",		"V",	&VarCcontMcp.VCicContlLiq,		NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	100.0,	1.0,	TODAS_T orb OPC_R, AT, "", "", G2,
  NULL,	NULL, 0, 0, 0,	NULL, 0.0, 0.0, 0.0, 0, 0, NULL, NULL
};

/*--- Estrutura de descricao das variaveis do ciclo de controle do AVC ---*/
t_par_var_log VarCcontAvc[] =
{
  "DuracaoUltMove",	"",	&VarCContAvc.DuracaoUltMove,	NIVEL_SUPER, FLOAT,	"%-3.3f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G3,
  #ifdef INCREMENTO_RESISTENCIA
   "IncCorr",		"MiOhm",&VarCContAvc.IncCorr,			NIVEL_SUPER, FLOAT,	"%-6.3f",	-6.0,	6.0,	1e6,	TODAS_T orb OPC_R, AT, "", "", G3,
    "IncTPinos",	"MiOhm",&VarCContAvc.IncTPinos,			NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e6,	TODAS_T orb OPC_R, AT, "", "", G3,
    "IncQueb",		"MiOhm",&VarCContAvc.IncQueb,			NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e6,	TODAS_T orb OPC_R, AT, "", "", G3,
   "IncRlent",		"MiOhm",&VarCContAvc.IncRlent,			NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e6,	TODAS_T orb OPC_R, AT, "", "", G3,
   "IncRrap",		"MiOhm",&VarCContAvc.IncRrap,			NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e6,	TODAS_T orb OPC_R, AT, "", "", G3,
   "IncUsuario",	"MiOhm",&VarCContAvc.IncUsuario,		NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e6,	TODAS_T orb OPC_R, AT, "", "", G3,
  #else
   "IncCorr",		"mV",	&VarCContAvc.IncCorr,			NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e3,	TODAS_T orb OPC_R, AT, "", "", G3,
    "IncTPinos",	"mV",	&VarCContAvc.IncTPinos,			NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e3,	TODAS_T orb OPC_R, AT, "", "", G3,
    "IncQueb",		"mV",	&VarCContAvc.IncQueb,			NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e3,	TODAS_T orb OPC_R, AT, "", "", G3,
   "IncRlent",		"mV",	&VarCContAvc.IncRlent,			NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e3,	TODAS_T orb OPC_R, AT, "", "", G3,
   "IncRrap",		"mV",	&VarCContAvc.IncRrap,			NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e3,	TODAS_T orb OPC_R, AT, "", "", G3,
   "IncUsuario",	"mV",	&VarCContAvc.IncUsuario,		NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e3,	TODAS_T orb OPC_R, AT, "", "", G3,
  #endif
  "IncOper",		"mV",	&VarCContAvc.IncOper,			NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e3,	TODAS_T orb OPC_R, AT, "", "", G3,
  "Kbpwm",			"nOhm/s",&VarCContAvc.Kbpwm,			NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	2000.0,	1e9,	TODAS_T, AT, "", "", G3,
  "Kcpwm",			"nOhm/s",&VarCContAvc.Kcpwm,			NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	2000.0,	1e9,	TODAS_T, AT, "", "", G3,
  "HabIncOper",	"0=D,1=E",  &VarCContAvc.HabIncOper,		NIVEL_SUPER, INT,	"%-1.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G3,
  "RAlvo",			"MiOhm",&VarCContAvc.RAlvo,				NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G3,
  "RAlvoUltMove",	"MiOhm",&VarCContAvc.RAlvoUltMove,		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G3,
  "Rerro",			"MiOhm",&VarCContAvc.Rerro,				NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G3,
  "Rinc",			"MiOhm",&VarCContAvc.Rinc,				NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G3,
#ifdef INCREMENTO_RESISTENCIA
  "IncOpInic",		"MiOhm",&VarCContAvc.IncOpInic,			NIVEL_SUPER, FLOAT,	"%-6.3f",	-6.0,	6.0,	1e6,	TODAS_T, AT, "", "", G0,
#else
  "IncOpInic",		"mV",	&VarCContAvc.IncOpInic,			NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1000.,	TODAS_T, AT, "", "", G0,
#endif
  "TIncOp",			"sec",	&VarCContAvc.TIncOp,			NIVEL_SUPER, INT,	"%-6.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G0,
  "TipoIncOp", "1=C,2=R",	&VarCContAvc.TipoIncOp,			NIVEL_SUPER, INT,	"%-6.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G0,
  "SentidoUltMove",	"UE",	&VarCContAvc.SentidoUltMove,	NIVEL_SUPER, INT,	"%-3.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G3,
  "VAlvo",			"V",	&VarCContAvc.VAlvo,				NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1.0,	TODAS_T orb OPC_R, AT, "VAlvo", "Controle3", G3,
  "VErro",			"V",	&VarCContAvc.VErro,				NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1.0,	TODAS_T, AT, "VErro", "Controle5", G3,
  "Vinc",			"V",	&VarCContAvc.Vinc,				NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1.0,	TODAS_T orb OPC_R, AT, "VInc", "Controle2", G3,

 #ifdef	BOOSTER_CORRENTE
  "INominalCuba",	"kA",	&VarCContAvc.INominalCuba,		NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e-3,	TODAS_T, AT, "", "", G3,
  "IAlvoCuba",		"kA",	&VarCContAvc.IAlvoCuba,			NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e-3,	TODAS_T, AT, "", "", G3,
 #endif
  NULL,	NULL, 0, 0, 0,	NULL, 0.0, 0.0, 0.0, 0, 0, NULL, NULL
};

/*--- Estrutura de descricao das variaveis relativas a efeito anodico do AVC ---*/
t_par_var_log VarEaAvc[] =
{
  "EaRLim",				"MiOhm",&VarEAAvc.EaRLim,				NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G4,
  "KSuave",				"",		&VarEAAvc.KSuave,				NIVEL_SUPER, FLOAT,	"%-4.2f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G4,
  "RSuave",				"MiOhm",&VarEAAvc.RSuave,				NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G4,
  "RSuaveDeriv",		"MiOhm/h",&VarEAAvc.RSuaveDeriv,		NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G4,
  "RSuaveDerivH",		"MiOhm/h",&VarEAAvc.RSuaveDerivH,		NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e6,	TODAS_T orb OPC_R, AT, "", "", G4,
  "CiclosIniPrev",		"UE",	&VarEAAvc.CiclosIniPrev,		NIVEL_SUPER, INT,	"%-5.0f",	0.0,	10000.0,1.0,	TODAS_T, AT, "", "", G4,
  "CiclosFimPrev",		"UE",	&VarEAAvc.CiclosFimPrev,		NIVEL_SUPER, INT,	"%-5.0f",	0.0,	10000.0,1.0,	TODAS_T, AT, "", "", G4,
  "CiclosInibeMov",		"UE",	&VarEAAvc.CiclosInibeMov,		NIVEL_SUPER, INT,	"%-5.0f",	0.0,	10000.0,1.0,	TODAS_T, AT, "", "", G4,
  "DerivHMinPrevEa",	"MiOhm/h",&VarEAAvc.DerivHMinPrevEa,	NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G4,
  "DerivHMaxPrevEa",	"MiOhm/h",&VarEAAvc.DerivHMaxPrevEa,	NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G4,
  "DerivHFimPrevEa",	"MiOhm/h",&VarEAAvc.DerivHFimPrevEa,	NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G4,
  "DerivHMaxInibMov",	"MiOhm/h",&VarEAAvc.DerivHMaxInibMov,	NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G4,
  "EaContLXLim",		"CLeit",  &VarEAAvc.EaContLXLim,		NIVEL_SUPER, SHORT_INT,	"%-5.0f",	0.0,	65000.0,	1.0,	TODAS_T, AT, "", "", G4,
  "EaVMax",				"v",  	&VarEAAvc.EaVMax,				NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1.0,	TODAS_T orb OPC_R, AT, "", "", G4,
  "EaDur",				"seg",	&VarEAAvc.EaDur,				NIVEL_SUPER, LONG,	"%-4.0f",	0.0,	9999.0,	1.0,	TODAS_T orb OPC_R, AT, "", "", G4,
  NULL,	NULL, 0, 0, 0,	NULL, 0.0, 0.0, 0.0, 0, 0, NULL, NULL
};


/*--- Estrutura de descricao das variaveis relativas a ruido do AVC ---*/
t_par_var_log VarRuidoAvc[] =
{
  "RlentCContVal",		"MiOhm",	&VarRuiAvc.RlentCContVal,	NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	999.0,	1e6,	TODAS_T orb OPC_R, AT, "", "", G5,
  "Rlent6Hs",			"MiOhm",	&VarRuiAvc.Rlent6Hs,		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G5,
  "Rlent48Hs",			"MiOhm",	&VarRuiAvc.Rlent48Hs,		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G5,
  "RlentInst",			"MiOhm",	&VarRuiAvc.RlentInst,		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G5,

  "RrapCContVal",		"MiOhm",	&VarRuiAvc.RrapCContVal,	NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	999.0,	1e6,	TODAS_T orb OPC_R, AT, "", "", G5,
  "Rrap6Hs",			"MiOhm",	&VarRuiAvc.Rrap6Hs,			NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G5,
  "Rrap48Hs",			"MiOhm",	&VarRuiAvc.Rrap48Hs,		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G5,
  "RrapInst",			"MiOhm",	&VarRuiAvc.RrapInst,		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G5,
  "RInstFiltPB",		"MiOhm",	&VarRuiAvc.RInstFiltPB,		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G5,
  "TipoRLent",			"",			&VarRuiAvc.TipoRLent,		NIVEL_SUPER, INT,	"%-1.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "TipoRL", "Ruido2", G5,
  "TipoRRap",			"",			&VarRuiAvc.TipoRRap,		NIVEL_SUPER, INT,	"%-1.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "TipoRR", "Ruido4", G5,
  NULL,	NULL, 0, 0, 0,	NULL, 0.0, 0.0, 0.0, 0, 0, NULL, NULL
};

/*--- Estrutura de descricao das variaveis de supervisao diaria do AVC ---*/
t_par_var_log VarSupAvc[] =
{
  "BemfDia",			"V",	&VarSuperv.BemfDia,				NIVEL_SUPER, FLOAT,	"%-4.2f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "CorrNumDia",			"",		&VarSuperv.CorrNumDia,			NIVEL_SUPER, INT,	"%-2.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "DurContlDia",		"seg",	&VarSuperv.DurContlDia,			NIVEL_SUPER, LONG,	"%-10.0f",	0.0,	100.0,	1.0,	PAR_PLAN, AT, "", "", G6,
  "EaDurDia",			"seg",	&VarSuperv.EaDurDia,			NIVEL_SUPER, LONG,	"%-10.0f",	0.0,	100.0,	1.0,	PAR_PLAN orb OPC_R, AT, "", "", G6,
  "EaEnergDiaBruta",	"MWh",	&VarSuperv.EaEnergDiaBruta,		NIVEL_SUPER, FLOAT,	"%-6.3f",	0.0,	100.0,	1e-6,	TODAS_T, AT, "", "", G6,
  "EaEnergDiaLiq",		"MWh",	&VarSuperv.EaEnergDiaLiq,		NIVEL_SUPER, FLOAT,	"%-6.3f",	0.0,	100.0,	1e-6,	TODAS_T, AT, "", "", G6,
  "EaNumDia",			"",		&VarSuperv.EaNumDia,			NIVEL_SUPER, INT,	"%-2.0f",	0.0,	100.0,	1.0,	PAR_PLAN orb OPC_R, AT, "", "", G6,
  "EaNumLDia",			"",		&VarSuperv.EaNumLDia,			NIVEL_SUPER, INT,	"%-5.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "EaPotDiaBruta",		"KW",	&VarSuperv.EaPotDiaBruta,		NIVEL_SUPER, FLOAT,	"%-7.3f",	0.0,	100.0,	1e-3,	TODAS_T, AT, "", "", G6,
  "EaPotDiaLiq",		"KW",	&VarSuperv.EaPotDiaLiq,			NIVEL_SUPER, FLOAT,	"%-7.3f",	0.0,	100.0,	1e-3,	TODAS_T, AT, "", "", G6,
  "EaPotDiaTotBruta",	"KW",	&VarSuperv.EaPotDiaTotBruta,	NIVEL_SUPER, FLOAT,	"%-7.3f",	0.0,	100.0,	1e-3,	TODAS_T, AT, "", "", G6,
  "EaPotDiaTotLiq",		"KW",	&VarSuperv.EaPotDiaTotLiq,		NIVEL_SUPER, FLOAT,	"%-7.3f",	0.0,	100.0,	1e-3,	TODAS_T, AT, "", "", G6,
  "EaVDiaBruta",		"V",	&VarSuperv.EaVDiaBruta,			NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "EaVDiaLiq",			"V",	&VarSuperv.EaVDiaLiq,			NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	1000.0,	1.0,	TODAS_T, AT, "", "", G6,
  "EaVDiaTotBruta",		"V",	&VarSuperv.EaVDiaTotBruta,		NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "EaVDiaTotLiq",		"V",	&VarSuperv.EaVDiaTotLiq,		NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "EnergDiaBruta",		"MWh",	&VarSuperv.EnergDiaBruta,		NIVEL_SUPER, FLOAT,	"%-6.3f",	0.0,	100.0,	1e-6,	TODAS_T, AT, "", "", G6,
  "EnergDiaLiq",		"MWh",	&VarSuperv.EnergDiaLiq,			NIVEL_SUPER, FLOAT,	"%-6.3f",	0.0,	100.0,	1e-6,	TODAS_T, AT, "", "", G6,
  "ForaLeitDurDia",		"seg",	&VarSuperv.ForaLeitDurDia,		NIVEL_SUPER, LONG,	"%-10.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "ForaContDurDia",		"seg",	&VarSuperv.ForaContDurDia,		NIVEL_SUPER, LONG,	"%-10.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "MovBaixoNumDia",		"",		&VarSuperv.MovBaixoNumDia,		NIVEL_SUPER, INT,	"%-4.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "MovBaixoDurDia",		"seg",	&VarSuperv.MovBaixoDurDia,		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "MovCimaNumDia",		"",		&VarSuperv.MovCimaNumDia,		NIVEL_SUPER, INT,	"%-4.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "MovCimaDurDia",		"seg",	&VarSuperv.MovCimaDurDia,		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "NumCContDia",		"",		&VarSuperv.NumCContDia,			NIVEL_SUPER, INT,	"%-4.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "NCContPotDia",		"",		&VarSuperv.NCContPotDia,		NIVEL_SUPER, INT,	"%-4.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "PotDiaAlvo",			"KW",	&VarSuperv.PotDiaAlvo,			NIVEL_SUPER, FLOAT,	"%-7.3f",	0.0,	100.0,	1e-3,	TODAS_T, AT, "", "", G6,
  "PotDiaBruta",		"KW",	&VarSuperv.PotDiaBruta,			NIVEL_SUPER, FLOAT,	"%-7.3f",	0.0,	100.0,	1e-3,	TODAS_T, AT, "", "", G6,
  "PotDiaLiq",			"KW",	&VarSuperv.PotDiaLiq,			NIVEL_SUPER, FLOAT,	"%-7.3f",	0.0,	100.0,	1e-3,	TODAS_T, AT, "", "", G6,
  "NumPrevEaDia",		 "",	&VarSuperv.NumPrevEaDia,		NIVEL_SUPER, INT,	"%-2.0f",	0.0,	100.0,	1.0,	PAR_PLAN orb OPC_R, AT, "", "", G6,
  "NumDBDia",		 	"",		&VarSuperv.Sup.NumDBDia,		NIVEL_SUPER, BYTE,	"%-2.0f",	0.0,	100.0,	1.0,	PAR_PLAN orb OPC_R, AT, "", "", G6,
  "EaVMaxDia",		 	"V",	&VarSuperv.EaVMaxDia,			NIVEL_SUPER, FLOAT,	"%-6.3f",	0.0,	100.0,	1.0,	PAR_PLAN orb OPC_R, AT, "", "", G6,
  "EaVMaxFimEA",		"V",	&VarSuperv.Sup.EaVMax,			NIVEL_SUPER, FLOAT,	"%-6.3f",	0.0,	100.0,	1.0,	PAR_PLAN orb OPC_R, AT, "", "", G6,
  "NumQuebPrevDia",		"",		&VarSuperv.Sup.NumQuebPrevDia,	NIVEL_SUPER, SHORT_INT,	"%-4.0f",	0.0,	100.0,	1.0,	PAR_PLAN orb OPC_R, AT, "", "", G6,
  "QtdAlumina",			"kg",	&VarSuperv.Sup.QtdAlumina,		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	99999.0,1.0,	PAR_PLAN orb OPC_R, AT, "", "", G6,
  "ALF3Fornecido",		"kg",	&VarSuperv.Sup.ALF3Fornecido,	NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	99999.0,1.0,	PAR_PLAN orb OPC_R, AT, "", "", G6,

  #ifdef	BOOSTER_CORRENTE
  "IAlvoCubaDia",		"kA",	&VarSuperv.IAlvoCubaDia,		NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e-3,	TODAS_T, AT, "", "", G6,
  #endif
  "QuebNumDia",			"",		&VarSuperv.QuebNumDia,			NIVEL_SUPER, INT,	"%-4.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "RDiaBruta",			"MiOhm",&VarSuperv.RDiaBruta,			NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	PAR_PLAN, AT, "", "", G6,
  "RDiaLiq",			"MiOhm",&VarSuperv.RDiaLiq,				NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G6,
  "RAlvoDia",			"MiOhm",&VarSuperv.RAlvoDia,			NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	PAR_PLAN, AT, "", "", G6,
  "RLentDurDia",		"seg",	&VarSuperv.RLentDurDia,			NIVEL_SUPER, LONG,	"%-10.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "RRapDurDia",			"seg",	&VarSuperv.RRapDurDia,			NIVEL_SUPER, LONG,	"%-10.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "VDesvDia",			"V",	&VarSuperv.VDesvDia,			NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "VDesvDurDia",		"seg",	&VarSuperv.VDesvDurDia,			NIVEL_SUPER, LONG,	"%-10.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "VDiaBruta",			"V",	&VarSuperv.VDiaBruta,			NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	100.0,	1.0,	PAR_PLAN, AT, "", "", G6,
  "VDiaLiq",			"V",	&VarSuperv.VDiaLiq,				NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "VForaContDia",		"V",	&VarSuperv.VForaContDia,		NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "VSetPointDia",		"V",	&VarSuperv.VSetPointDia,		NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "EstPrincDia",	"N,P,L,D",	&VarSuperv.EstPrincDia,			NIVEL_SUPER, INT,	"%-1.0f",	0.0,	4.0,	1.0,	TODAS_T orb OPC_R, AT, "", "", G6,
  "RLentFraDurDia",		"min",	&VarSuperv.RLentFraDurDia,		NIVEL_SUPER, INT,	"%-5.0f",	0.0,	32000.0,1.0,	TODAS_T, AT, "", "", G6,
  "RLentForDurDia",		"min",	&VarSuperv.RLentForDurDia,		NIVEL_SUPER, INT,	"%-5.0f",	0.0,	32000.0,1.0,	TODAS_T, AT, "", "", G6,
  "RLentFracoDia",		"MiOhm",&VarSuperv.RLentFracoDia,		NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	99.0,	1e6,	TODAS_T, AT, "", "", G6,
  "RLentForteDia",		"MiOhm",&VarSuperv.RLentForteDia,		NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	99.0,	1e6,	TODAS_T, AT, "", "", G6,
#ifdef INCREMENTO_RESISTENCIA
  "RLentFraIncDia",		"MiOhm",&VarSuperv.RLentFraIncDia,		NIVEL_SUPER, FLOAT,	"%-6.3f",	-6.0,	6.0,	1e6,	TODAS_T, AT, "", "", G6,
  "RLentForIncDia",		"MiOhm",&VarSuperv.RLentForIncDia,		NIVEL_SUPER, FLOAT,	"%-6.3f",	-6.0,	6.0,	1e6,	TODAS_T, AT, "", "", G6,
#else
  "RLentFraIncDia",		"mV",	&VarSuperv.RLentFraIncDia,		NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	99.99,	1e3,	TODAS_T, AT, "", "", G6,
  "RLentForIncDia",		"mV",	&VarSuperv.RLentForIncDia,		NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	99.99,	1e3,	TODAS_T, AT, "", "", G6,
#endif
  "RRapFraDurDia",		"min",	&VarSuperv.RRapFraDurDia,		NIVEL_SUPER, INT,	"%-5.0f",	0.0,	32000.0,1.0,	TODAS_T, AT, "", "", G6,
  "RRapForDurDia",		"min",	&VarSuperv.RRapForDurDia,		NIVEL_SUPER, INT,	"%-5.0f",	0.0,	32000.0,1.0,	TODAS_T, AT, "", "", G6,
  "RRapFracoDia",		"MiOhm",&VarSuperv.RRapFracoDia,		NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	99.0,	1e6,	TODAS_T, AT, "", "", G6,
  "RRapForteDia",		"MiOhm",&VarSuperv.RRapForteDia,		NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	99.0,	1e6,	TODAS_T, AT, "", "", G6,
#ifdef INCREMENTO_RESISTENCIA
  "RRapFraIncDia",		"MiOhm",&VarSuperv.RRapFraIncDia,		NIVEL_SUPER, FLOAT,	"%-6.3f",	-6.0,	6.0,	1e6,	TODAS_T, AT, "", "", G6,
  "RRapForIncDia",		"MiOhm",&VarSuperv.RRapForIncDia,		NIVEL_SUPER, FLOAT,	"%-6.3f",	-6.0,	6.0,	1e6,	TODAS_T, AT, "", "", G6,
  "ContIncRuidoDia",	"",		&VarSuperv.ContIncRuidoDia,		NIVEL_SUPER, INT,	"%-5.0f",	0.0,	32000.0,1.0,	TODAS_T, AT, "", "", G6,
  "IncRuidoDia",		"MiOhm",&VarSuperv.IncRuidoDia,			NIVEL_SUPER, FLOAT,	"%-6.3f",	-6.0,	6.0,	1e6,	TODAS_T, AT, "", "", G6,
#else
  "RRapFraIncDia",		"mV",	&VarSuperv.RRapFraIncDia,		NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	99.99,	1e3,	TODAS_T, AT, "", "", G6,
  "RRapForIncDia",		"mV",	&VarSuperv.RRapForIncDia,		NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	99.99,	1e3,	TODAS_T, AT, "", "", G6,
  "ContIncRuidoDia",	"",		&VarSuperv.ContIncRuidoDia,		NIVEL_SUPER, INT,	"%-5.0f",	0.0,	32000.0,1.0,	TODAS_T, AT, "", "", G6,
  "IncRuidoDia",		"mV",	&VarSuperv.IncRuidoDia,			NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	99.99,	1e3,	TODAS_T, AT, "", "", G6,
#endif
  "ContRLentNormDia",	"",		&VarSuperv.ContRLentNormDia,	NIVEL_SUPER, INT,	"%-5.0f",	0.0,	32000.0,1.0,	TODAS_T, AT, "", "", G6,
  "RLentNormDia",		"MiOhm",&VarSuperv.RLentNormDia,		NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	99.99,	1e6,	TODAS_T, AT, "", "", G6,
  "ContRRapNormDia",	"",		&VarSuperv.ContRRapNormDia,		NIVEL_SUPER, INT,	"%-5.0f",	0.0,	32000.0,1.0,	TODAS_T, AT, "", "", G6,
  "RRapNormDia",		"MiOhm",&VarSuperv.RRapNormDia,			NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	99.99,	1e6,	TODAS_T, AT, "", "", G6,
  "EfPrevEaDia",		"",		&VarSuperv.EfPrevEaDia,			NIVEL_SUPER, INT,	"%-10.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "DurPrevEaDia",		"seg",	&VarSuperv.DurPrevEaDia,		NIVEL_SUPER, INT,	"%-10.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G6,
  "EaDurXDia",			"seg",	&VarSuperv.EaDurXDia,			NIVEL_SUPER, SHORT_INT,	"%-5.0f",	0.0,	65000.0,	1.0,	TODAS_T, AT, "", "", G6,
  "TotalEA24h",			"",		&VarSuperv.Sup.TotalEA24h,		NIVEL_SUPER, BYTE,	"%-5.0f",	0.0,	65000.0,	1.0,	TODAS_T orb OPC_R, AT, "", "", G6,
  "NumTendOver",		"",		&VarSuperv.Sup.NumTendOverDia,	NIVEL_SUPER, SHORT_INT,	"%-5.0f",	0.0,	65000.0,	1.0,	TODAS_T orb OPC_R, AT, "", "", G6,

#ifdef	USA_REDE_ECHELON
  "ESTATISTICA / CUBA",	"",				NULL,							NIVEL_SUPER, INT,	"%-5.0f",	0.0,	1e6,	1.0,	TITULO_5, 	 AT, "", "", G6,
  "Recepcao",			"",				NULL,							NIVEL_SUPER, INT,	"%-5.0f",	0.0,	1e6,	1.0,	TITULO_5, 	 AT, "", "", G6,
  "RxMedia",			"Pkts/Sec",		&VarSuperv.Atn7RxPktsSecAvr,	NIVEL_SUPER, FLOAT,	"%-8.3f",	0.0,	1e6,	1.0,	REL_ECHELON, AT, "", "", G6,
  "RxMaximo",			"Pkts/Sec",		&VarSuperv.Atn7RxPktsSecMax,	NIVEL_SUPER, FLOAT,	"%-8.3f",	0.0,	1e6,	1.0,	REL_ECHELON, AT, "", "", G6,
  "RxBytesLidos",		"Bytes",		&VarSuperv.Atn7RxBytes,			NIVEL_SUPER, INT,	"%-10.0f",	0.0,	1e9,	1.0,	REL_ECHELON, AT, "", "", G6,
  "RxPcksLidos",		"Pkts",			&VarSuperv.Atn7RxPkts,			NIVEL_SUPER, INT,	"%-10.0f",	0.0,	1e9,	1.0,	REL_ECHELON, AT, "", "", G6,
  "RxErros",			"",				&VarSuperv.Atn7RxErrors,		NIVEL_SUPER, INT,	"%-5.0f",	0.0,	1e6,	1.0,	REL_ECHELON, AT, "", "", G6,
  "Transmissao",		"",				NULL,							NIVEL_SUPER, INT,	"%-5.0f",	0.0,	1e6,	1.0,	TITULO_5, 	 AT, "", "", G6,
  "TxMedia",			"Pkts/Sec",		&VarSuperv.Atn7TxPktsSecAvr,	NIVEL_SUPER, FLOAT,	"%-8.3f",	0.0,	1e6,	1.0,	REL_ECHELON, AT, "", "", G6,
  "TxMaximo",			"Pkts/Sec",		&VarSuperv.Atn7TxPktsSecMax,	NIVEL_SUPER, FLOAT,	"%-8.3f",	0.0,	1e6,	1.0,	REL_ECHELON, AT, "", "", G6,
  "TxBytesEnviados",	"Bytes",		&VarSuperv.Atn7TxBytes,			NIVEL_SUPER, INT,	"%-10.0f",	0.0,	1e9,	1.0,	REL_ECHELON, AT, "", "", G6,
  "TxPcksEnviados",		"Pkts",			&VarSuperv.Atn7TxPkts,			NIVEL_SUPER, INT,	"%-10.0f",	0.0,	1e9,	1.0,	REL_ECHELON, AT, "", "", G6,
  "TxErros",			"",				&VarSuperv.Atn7TxErrors,		NIVEL_SUPER, INT,	"%-5.0f",	0.0,	1e6,	1.0,	REL_ECHELON, AT, "", "", G6,
/* -- Alteracao - Inicio - 14/02/2001 - Carlos/Leonel - tratamento para cba sala 86ka -- */
 #ifdef	USA_ATN8
  /* -- alteracao - inicio - 13/09/00 - Robson - Inclusao tratamento  -- */
  "A/D Conversion",		"",				NULL,							NIVEL_SUPER, INT,	"%-5.0f",	0.0,	1e6,	1.0,	TITULO_5, 	 AT, "", "", G6,
  "ErrorADAtn8_0",		"",				&VarSuperv.Sup.ErrorADAtn8[0],		NIVEL_SUPER, SHORT_INT,	"%-5.0f",0.0,	32768,	1.0,	REL_ECHELON, AT, "", "", G6,
  "ErrorADAtn8_1",		"",				&VarSuperv.Sup.ErrorADAtn8[1],		NIVEL_SUPER, SHORT_INT,	"%-5.0f",0.0,	32768,	1.0,	REL_ECHELON, AT, "", "", G6,
  /* -- alteracao - fim - 13/09/00 - Robson - Inclusao tratamento Atn8 -- */
 #else
  /* -- Alteracao - inicio - 13/09/99 - Leonel - Inclusao de estatistica de erro de conversao -- */
  "ERROS A/D ATN1.4",	"",				NULL,						NIVEL_SUPER, INT,	"%-5.0f",	0.0,	1e6,	1.0,	TITULO_5, 	 AT, "", "", G6,
  "ErroAD",				"",				&VarSuperv.ErroAD,			NIVEL_SUPER, SHORT_INT, "%-5.0f", 0.0,	65535.0,1.0,	REL_ECHELON, AT, "", "", G6,
  /* -- Alteracao - fim - 13/09/99 - Leonel -- */
 #endif
/* -- Alteracao - Fim - 14/02/2001 - Carlos/Leonel - tratamento para cba sala 86ka -- */
#endif

  "METAL/OPERACIONAL",			"",				NULL,								NIVEL_SUPER,	FLOAT,		"%-5.2f",	0.0,	0.0,	1.0,	TITULO_6,	AT,	"",	"",	G6,
  "Banho",			"cm",			&VarSuperv.Sup.CNF_SUP.Banho,		NIVEL_CONFIG_1,	FLOAT,		"%-3.0f",	0.0,	30.0,	1.0,	PAR_METAIS,	AT,	"",	"Metais0",	G6,
  "Metal",			"cm",			&VarSuperv.Sup.CNF_SUP.Metal,		NIVEL_CONFIG_1,	FLOAT,		"%-3.0f",	0.0,	50.0,	1.0,	PAR_METAIS,	AT,	"",	"Metais1",	G6,
  "Temperatura",	"C",			&VarSuperv.Sup.CNF_SUP.Temperatura,	NIVEL_CONFIG_1,	INT,		"%-5.0f",	0.0,	1200.0,	1.0,	PAR_METAIS,	AT,	"",	"Metais2",	G6,
  "Fluoreto",		"%",			&VarSuperv.Sup.CNF_SUP.Fluoreto,	NIVEL_CONFIG_1,	FLOAT,		"%-5.1f",	0.0,	100.0,	1.0,	PAR_METAIS,	AT,	"",	"Metais3",	G6,
  "Fluorita",		"%",			&VarSuperv.Sup.CNF_SUP.Fluorita,	NIVEL_CONFIG_1,	FLOAT,		"%-5.1f",	0.0,	100.0,	1.0,	PAR_METAIS,	AT,	"",	"Metais4",	G6,
  NULL,	NULL, 0, 0, 0,	NULL, 0.0, 0.0, 0.0, 0, 0, NULL, NULL
};

/*--- Estrutura de descricao dos estados discretos do AVC ---*/
t_par_var_log VarEstDiscAvc[] =
{
	/* -- Valores que podem ser alterados pela operacao -- */
  "ALARMES",		"F/V",		NULL,	NIVEL_SUPER, INT,	"%-1.0f",	0.0,	0.0,	1.0,    TITULO_2,  AT, "", "", G7,
  "ForaLeitura",	"F/V",		&VarEst.ForaLeitura,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "EstadoCuba",		"N,P,L,D",	&VarEst.EstadoCuba,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "ManualRemoto",	"A/M",		&VarEst.ChaveAutMan,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "ManualLocal",	"R/L",		&VarEst.ChaveLocRem,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "Corrida",		"F/V",		&VarEst.Corrida,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "Quebrada",		"F/V",		&VarEst.Quebrada,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "Quebra", "Status8", G7,
	/* -- Valores alterados pelo algoritmo de controle -- */
  "DesvioTensao",	"F/V",		&VarEst.DesvioTensao,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "",  "", G7,
  "Ea",				"F/V",		&VarEst.Ea,				NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS orb OPC_R, AT, "EA",     "Status1", G7,
  "EaPrev",			"F/V",		&VarEst.EaPrev,			NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "PrevEA", "Status5", G7,
  "InibeMovEaPrev",	"F/V",		&VarEst.InibeMovEaPrev, NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "InibMov","Status6", G7,
  "EliminaEa",		"F/V",		&VarEst.EliminaEa,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "RuidoLent",		"F/V",		&VarEst.RuidoLent,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "RuidoL", "Ruido1", G7,
  "RuidoRap",		"F/V",		&VarEst.RuidoRap,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "RuidoR", "Ruido3", G7,
  "ElimEaAtivo",	"F/T",		&VarEst.ElimEaAtivo,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "EvCubaMax",		"F/V",		&VarEst.EvCubaMax,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "Atn7Status",		"F/V",		&VarEst.RtuStatus,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "Remota", "", G7,
  "EmCalibracao",	"F/V",		&VarEst.EmCalibracao,NIVEL_SUPER,	BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	REL_CUBAS,	AT, "",			"", G9,
  "CheckAtivo",		"F/V",		&VarEst.Est.CheckAtivo, NIVEL_SUPER,	BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	REL_CUBAS,	AT, "",	"", G9,
  "ManualAlimRem",	"F/V",		&VarEst.Est.ManualAlimRem,NIVEL_SUPER,	BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	REL_CUBAS,	AT, "",			"", G9,
  "ManualAlimLoc",	"F/V",		&VarEst.Est.ManualAlimLoc,NIVEL_SUPER,	BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	REL_CUBAS,	AT, "",			"", G9,
  "AlimSuspensa",	"F/V",		&VarEst.Est.AlimSuspensa,NIVEL_SUPER,	BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	REL_CUBAS,	AT, "",			"", G9,
  "QuebPrev",		"F/V",		&VarEst.Est.QuebPrev,	NIVEL_SUPER,	BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	REL_CUBAS,	AT, "",			"", G9,
  "RuidoAlim",		"F/V",		&VarEst.Est.RuidoAlim,	NIVEL_SUPER,	BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	REL_CUBAS,	AT, "",			"", G9,
  "QuebPrevInib",	"S,T,E",	&VarEst.Est.QuebPrevInib,NIVEL_SUPER,	BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	REL_CUBAS,	AT, "",			"", G9,
  "OpeSoproEspec",	"F/V",		&VarEst.Est.OpeSoproEspec,NIVEL_SUPER,	BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	REL_CUBAS,	AT, "",			"", G9,
  "ReleTempoMM",	"F/V",		&VarEst.Est.ReleTempoMM,NIVEL_SUPER,	BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	REL_CUBAS,	AT, "",			"", G9,
  "ChaveMCruzeiro",	"F/V",		&VarEst.Est.ChaveMCruzeiro,NIVEL_SUPER,	BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	REL_CUBAS,	AT, "",			"", G9,
  "LiberaMCruzeiro","F/V",		&VarEst.Est.LiberaMCruzeiro,NIVEL_SUPER,BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	REL_CUBAS,	AT, "",			"", G9,
  "ForaControle",	"F/V",		&VarEst.ForaControle,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "EfeitoMove",		"F/V",		&VarEst.EfeitoMove,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "EfeitoEa",		"F/V",		&VarEst.EfeitoEa,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "EfeitoQueb",		"F/V",		&VarEst.EfeitoQueb,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "EfeitoCorr",		"F/V",		&VarEst.EfeitoCorr,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "EsperaConfMove",	"F/V",		&VarEst.EsperaConfMove,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "DeuAcresBMSup",	"F/V",		&VarEst.DeuAcresBMSup, 	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "TrataTPinos",	"F/V",		&VarEst.TrataTPinos, 	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	REL_CUBAS orb OPC_R, AT, "", "", G7,
  "TrataMCruzeiro",	"F/V",		&VarEst.TrataCruzeiro, 	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "FalhaSoproAuto",	"F/V",		&VarEst.FalhaSoproAut, 	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "ManualControle",	"F/V",		&VarEst.ManualControle, NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "TabOpeAtiva",	"F/V",		&VarEst.TabOpeAtiva,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "InibeControleUsu","F/V",		&VarEst.InibeControleUsu, NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "InibeControleAlim","F/V",	&VarEst.InibeControleAlim, NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "EaPrevVirada",	"F/V",		&VarEst.EaPrevVirada,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "TrataIncUsuario", "F/V",		&VarEst.TrataIncUsuario, NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "CorrCubaEmerg",	"F/V",		&VarEst.CorrCubaEmerg, 	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "AjusteCamisa",	"F/V",		&VarEst.Est.AjusteCamisa,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "AbortaAjust",	"",			&VarEst.Est.AbortaAjuste,	NIVEL_SUPER, BYTE,	"%-2.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "CamNAjust",		"F/V",		&VarEst.Est.CamNAjust,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "AtivCamOpe",		"F/V",		&VarEst.Est.AtivCamOpe,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "ProvAgarraAnodo","F/V",		&VarEst.ProvAgarraAnodo,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "HabQPrevOpe",	"F/V",		&VarEst.Est.HabQPrevOpe,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "FalhaCalcRuido",	"F/V",		&VarEst.Est.FalhaCalcRuido,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "TensaoCunha",	"F/V",		&VarEst.Est.TensaoCunha,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "DerNegativa",	"F/V",		&VarEst.Est.DerNegativa,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "DerBaixa",		"F/V",		&VarEst.Est.DerBaixa,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "AjusteCamTur",	"F/V",		&VarEst.Est.AjusteCamTur,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "Oscilacao",		"F/V",		&VarEst.Est.Oscilacao,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "FormaBanho",		"F/V",		&VarEst.Est.FormaBanho,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "SireneCunha",	"F/V",		&VarEst.Est.SireneCunha,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "DesligaCunha",	"F/V",		&VarEst.Est.DesligaCunha,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "StatusEA",		"",			&VarEst.Est.StatusEA,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS orb OPC_R, AT, "", "", G7,
  "BSupMovel",		"",			&VarEst.Est.BSupMovel,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "StatusPainel",	"",			&VarEst.Est.StatusPainel,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS orb OPC_R, AT, "", "", G7,
  "AEK",			"",			&VarEst.Est.AEK,			NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "ForcaAEK",		"",			&VarEst.Est.ForcaAEK,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "EaAtrasado",		"",			&VarEst.Est.EaAtrasado,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "Queb1Passada",		"",		&VarEst.Est.Queb1Passada,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "BitCLP",			"",			&VarEst.Est.BitCLP,			NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "TabelaAlF3",		"",			&VarEst.Est.TabelaAlF3,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "QuebInibida",	"F/V",		&VarEst.Est.QuebInibida,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "EsperaQP",		"F/V",		&VarEst.Est.EsperaQP,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "ForcaEA",		"F/V",		&VarEst.Est.ForcaEA,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "AlarmeCheck",	"F/V",		&VarEst.Est.AlarmeCheck,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G9,
  "TendenciaOver",	"F/V",		&VarEst.Est.TendenciaOver,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G9,
  "CamisaAlta",		"F/V",		&VarEst.Est.CamisaAlta,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "CamAlta", "Status3", G9,
  "CamisaBaixa",	"F/V",		&VarEst.Est.CamisaBaixa,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "CamBaixa", "Status4", G9,
  "InibeMovDB",		"F/V",		&VarEst.Est.InibeMovDB,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,
  "InibeQPposDB",		"F/V",		&VarEst.Est.InibeQPposDB,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	100.0,	1.0,	REL_CUBAS, AT, "", "", G7,


  NULL,	NULL, 0, 0, 0,	NULL, 0.0, 0.0, 0.0, 0, 0, NULL, NULL
};

/*--- Estrutura de descricao das variaveis de controle de linha ---*/
t_par_var_log VarContAvl[] =
{
	/* -- Parametros da linha -- */
  "TempoLog",					"seg",	&VarAvl.ResGerAvlAtan[0],	NIVEL_SUPER, FLOAT,	"%-7.3f",	0.0,	150.0,	1.0,	TODAS_T, AT, "", "", G8,
  "CORRENTE",	      			"",    NULL,  	NIVEL_SUPER, FLOAT, "%-8.2f",	0.0,  0.0,   1.0, TITULO_3,    AT, "", "", G8,
  "ILinhaAlta",					"kA",	&VarAvl.ILinhaAlta,			NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	150.0,	1e-3,	PAR_LINHA, AT, "IAlta", "LinhaC6", G8,
  "ILinhaBaixa",				"kA",	&VarAvl.ILinhaBaixa, 		NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	150.0,	1e-3,	PAR_LINHA, AT, "IBaixa", "LinhaC5", G8,
  "ILinhaMin",					"kA",	&VarAvl.ILinhaMin,			NIVEL_CONFIG_0,	 FLOAT,	"%-6.2f",	0.0,	150.0,	1e-3,	PAR_LINHA, AT, "IMin", "LinhaC4", G8,
  "INominal",					"kA",	&VarAvl.INominal,			NIVEL_CONFIG_0,	 FLOAT,	"%-6.2f",	40.0,	140.0,	1e-3,	PAR_LINHA, AT, "INomin", "LinhaC3", G8,
  "IdesvMax",					"kA",	&VarAvl.IdesvMax,			NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	160.0,	1e-3,	PAR_LINHA, AT, "", "", G8,
  "IRapMax",					"kA",	&VarAvl.IRapMax,			NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	160.0,	1e-3,	PAR_LINHA, AT, "", "", G8,
  "IDifMax",					"kA",	&VarAvl.IDifMax,			NIVEL_SUPER, FLOAT,	"%-7.3f",	0.0,	160.0,	1e-3,	PAR_LINHA, AT, "", "", G8,
  "IDifMaxLinhaCuba",			"kA",	&VarAvl.IDifMaxLinhaCuba,	NIVEL_SUPER, FLOAT,	"%-7.3f",	0.0,	160.0,	1e-3,	PAR_LINHA, AT, "", "", G8,
  "CanalIPrinc",				"",		&VarAvl.CanalIPrinc,		NIVEL_SUPER, INT,	"%-1.0f",	0.0,	7.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "CanalISec",					"",		&VarAvl.CanalISec,			NIVEL_SUPER, INT,	"%-1.0f",	0.0,	7.0,	1.0,	PAR_LINHA, AT, "", "", G8,
/* -- Alteracao - Inicio - 11/02/2003 - Leonel - Comutacao sinal de corrente atraves da AtnCA -- */
#ifdef	USA_ATN8
  "SelecaoCanalI",				"0,1,2",&VarAvl.Par.SelecaoCanalI,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	2.0,	1.0,	PAR_LINHA, AT, "", "", G8,
#endif
/* -- Alteracao - Fim - 11/02/2003 - Leonel - Comutacao sinal de corrente atraves da AtnCA -- */
  "AT/DESAT. LINHA",	      			"",    NULL,  	NIVEL_SUPER, FLOAT, "%-8.2f",	0.0,  0.0,   1.0, TITULO_3,    AT, "", "", G8,
  "TAtivaLinha",	   			"min",  &VarAvl.TAtivaLinha,		NIVEL_SUPER, INT,   "%-2.0f",   0.0,    60.0,   1.0,	PAR_LINHA, AT, "", "", G8,
  "TDesabLinha",	   			"min",  &VarAvl.TDesabLinha,		NIVEL_SUPER, INT,   "%-3.0f",   0.0,    120.0,  1.0,	PAR_LINHA, AT, "", "", G8,
  "LinhaAtiva",					"V/F",	&VarAvl.LinhaAtiva,			NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	REL_LINHA orb OPC_R, AT, "", "", G8,
  "Corrida",      				 "",    NULL,  	NIVEL_SUPER, FLOAT, "%-8.2f",	0.0,  0.0,   1.0, TITULO_3,    AT, "", "", G8,
  "CicloAjCorr",				"0.5s", &VarAvl.CicloAjCorrida,	 	NIVEL_SUPER, INT,   "%-2.0f",   2.0,	60.0,   1.0,	PAR_LINHA, AT, "", "", G8,
  "KpcCorr",						"", &VarAvl.Par.KpcCorr,	 	NIVEL_SUPER, FLOAT, "%-3.1f",   0.0,	2.0,   	1.0,	PAR_LINHA, AT, "", "", G8,
  "DurMovBMinCorr",				"Tick",	&VarAvl.DurMovBMin,			NIVEL_SUPER, INT,	"%-2.0f",	0.0,	120.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "DurMovBMaxCorr",				"Tick",	&VarAvl.DurMovBMax,			NIVEL_SUPER, INT,	"%-2.0f",	0.0,	120.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "DurMovCMinCorr",				"Tick",	&VarAvl.DurMovCMin,			NIVEL_SUPER, INT,	"%-2.0f",	0.0,	120.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "DurMovCMaxCorr",				"Tick",	&VarAvl.DurMovCMax,			NIVEL_SUPER, INT,	"%-2.0f",	0.0,	120.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "TMaxCorrida",				"seg",	&VarAvl.Par.TMaxCorrida,	NIVEL_SUPER, INT,	"%-2.0f",	0.0,	99.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "Eliminacao EA",	      		"",    NULL,  	NIVEL_SUPER, FLOAT, "%-8.2f",	0.0,  0.0,   1.0, TITULO_3,    AT, "", "", G8,
  "LimInfMovElim",				"sec",	&VarAvl.LimInfMovElim,		NIVEL_SUPER, SHORT_INT,	"%-2.0f",	0.0,	10.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "LimSupMovElim",				"sec",	&VarAvl.LimSupMovElim,		NIVEL_SUPER, SHORT_INT,	"%-2.0f",	0.0,	10.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "TURNO/DIA",	      			"",    NULL,  	NIVEL_SUPER, FLOAT, "%-8.2f",	0.0,  0.0,   1.0, TITULO_3,    AT, "", "", G8,
  "NumTurnos",		   			"",     &VarAvl.NumTurnos,			NIVEL_SUPER, INT,   "%-1.0f",   0.0,    6.0,   	1.0,	PAR_LINHA, AT, "", "", G8,
  "HoraIniTurno-1",	   			"",     &VarAvl.HoraIniTurno[0],	NIVEL_SUPER, INT,   "%-2.0f",	0.0,    24.0,   1.0,	PAR_LINHA, AT, "", "", G8,
  "HoraIniTurno-2",	   			"",     &VarAvl.HoraIniTurno[1],	NIVEL_SUPER, INT,   "%-2.0f",	0.0,    24.0,   1.0,	PAR_LINHA, AT, "", "", G8,
  "HoraIniTurno-3",	   			"",     &VarAvl.HoraIniTurno[2],	NIVEL_SUPER, INT,   "%-2.0f",	0.0,    24.0,   1.0,	PAR_LINHA, AT, "", "", G8,
  "HoraIniTurno-4",	   			"",     &VarAvl.HoraIniTurno[3],	NIVEL_SUPER, INT,   "%-2.0f",	0.0,    24.0,   1.0,	PAR_LINHA, AT, "", "", G8,
  "HoraIniTurno-5",	   			"",     &VarAvl.HoraIniTurno[4],	NIVEL_SUPER, INT,   "%-2.0f",	0.0,    24.0,   1.0,	PAR_LINHA, AT, "", "", G8,
  "HoraIniTurno-6",	   			"",     &VarAvl.HoraIniTurno[5],	NIVEL_SUPER, INT,   "%-2.0f",	0.0,    24.0,   1.0,	PAR_LINHA, AT, "", "", G8,
  "IdentTurno-1",	   			"",     &VarAvl.IdentTurno[0][0],	NIVEL_SUPER, STRING, "%-1s",	0.0,    0.0,    1.0,	PAR_LINHA, AT, "", "", G8,
  "IdentTurno-2",	   			"",     &VarAvl.IdentTurno[1][0],	NIVEL_SUPER, STRING, "%-1s",	0.0,    0.0,    1.0,	PAR_LINHA, AT, "", "", G8,
  "IdentTurno-3",	   			"",     &VarAvl.IdentTurno[2][0],	NIVEL_SUPER, STRING, "%-1s",	0.0,    0.0,    1.0,	PAR_LINHA, AT, "", "", G8,
  "IdentTurno-4",	   			"",     &VarAvl.IdentTurno[3][0],	NIVEL_SUPER, STRING, "%-1s",	0.0,    0.0,    1.0,	PAR_LINHA, AT, "", "", G8,
  "IdentTurno-5",	   			"",     &VarAvl.IdentTurno[4][0],	NIVEL_SUPER, STRING, "%-1s",	0.0,    0.0,    1.0,	PAR_LINHA, AT, "", "", G8,
  "IdentTurno-6",	   			"",     &VarAvl.IdentTurno[5][0],	NIVEL_SUPER, STRING, "%-1s",	0.0,    0.0,    1.0,	PAR_LINHA, AT, "", "", G8,
  "HoraFechaDia",	   			"",     &VarAvl.HoraFechaDia,		NIVEL_SUPER, INT,   "%-2.0f",   0.0,    24.0,   1.0,	PAR_LINHA, AT, "", "", G8,
  "LOG OPERACAO",	      			"",    NULL,  	NIVEL_SUPER, FLOAT, "%-8.2f",	0.0,  0.0,   1.0, TITULO_3,    AT, "", "", G8,
  "HabLogOper",  	"0=Des,1=Hab",		&VarAvl.HabLogOper,         NIVEL_SUPER, INT,   "%-2.0f",   0.0,     1.0,   1.0,	PAR_LINHA, AT, "", "", G8,
  "IMPORTACAO SIAP",  			"",    NULL,  	NIVEL_SUPER, FLOAT, "%-8.2f",	0.0,  0.0,   1.0, TITULO_3,    AT, "", "", G8,
  "HabImportSIAP",				"",		&VarAvl.Par.HabImportSIAP,	NIVEL_SUPER, BYTE,	"%-2.0f",  	0.0,	1.0,    1.0,    PAR_LINHA, AT, "", "", G8,
  "IMP. ALARME",      			"",    NULL,  	NIVEL_SUPER, FLOAT, "%-8.2f",	0.0,  0.0,   1.0, TITULO_3,    AT, "", "", G8,
  "ImpSimulNodoPri",			"",		&VarAvl.ImpSimulNodoPri,	NIVEL_SUPER, INT,	"%-1.0f",	0.0,	1.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "ImpSimulNodoOp-1",			"",		&VarAvl.ImpSimulNodoOp[0],	NIVEL_SUPER, INT,	"%-1.0f",	0.0,	1.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "ImpSimulNodoOp-2",			"",		&VarAvl.ImpSimulNodoOp[1],	NIVEL_SUPER, INT,	"%-1.0f",	0.0,	1.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "ImpSimulNodoOp-3",			"",		&VarAvl.ImpSimulNodoOp[2],	NIVEL_SUPER, INT,	"%-1.0f",	0.0,	1.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "ImpSimulNodoOp-4",			"",		&VarAvl.ImpSimulNodoOp[3],	NIVEL_SUPER, INT,	"%-1.0f",	0.0,	1.0,	1.0,	PAR_LINHA, AT, "", "", G8,

  "DIFERENCA ALVO",  			"",    NULL,  	NIVEL_SUPER, FLOAT, "%-8.2f",	0.0,  0.0,   1.0, TITULO_3,    AT, "", "", G8,
  "DifCorMax",					"A",	&VarAvl.Par.DifCorMax,			NIVEL_SUPER, SHORT_INT,	"%-4.0i",	0.0,	9999.0,	1,	PAR_LINHA, AT, "", "", G8,
  "EfeitoDifAlta",				"min",	&VarAvl.Par.EfeitoDifAlta,		NIVEL_SUPER, SHORT_INT,	"%-2.0i",	0.0,	60.0,	1,	PAR_LINHA, AT, "", "", G8,

  "EFEITO LINHA",   			"",    NULL,  	NIVEL_SUPER, FLOAT, "%-8.2f",	0.0,  0.0,   1.0, TITULO_3,    AT, "", "", G8,
  "EaVoltLinhaLim",				"V",	&VarAvl.Par.EaVoltLinhaLim,			NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	99.0,	1,	PAR_LINHA, AT, "", "", G8,
  "TEfeitoEaLinha",				"HH:MM",	&VarAvl.Par.TEfeitoEaLinha,		NIVEL_SUPER, T_HORA,	"%-5s",		0.0,	86340,	1.0,	PAR_LINHA, AT, "", "", G8,
  "EaLinha",					"V/F",	&VarAvl.Trab.EaLinha,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	REL_LINHA, AT, "", "", G8,
  "NCic4sEaLinha",				"",		&VarAvl.Par.NCic4sEaLinha,	NIVEL_SUPER, BYTE,	"%-2.0f",	0.0,	8.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "BitSirenesATNCA1",			"",		&VarAvl.Par.BitSirenesATNCA1,		NIVEL_SUPER, INT,	"%-10.0i",	0.0,	9999999999.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "BitSirenesATNCA2",			"",		&VarAvl.Par.BitSirenesATNCA2,		NIVEL_SUPER, INT,	"%-10.0i",	0.0,	9999999999.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "TmpAlarmeSirenes",			"",		&VarAvl.Par.TmpAlarmeSirenes,		NIVEL_SUPER, BYTE,	"%-3.0f",	0.0,	120.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "Reserva1",					"",		&VarAvl.Par.Reserva1,				NIVEL_SUPER, BYTE,	"%-2.0f",	0.0,	99.0,	1.0,	PAR_LINHA, AT, "", "", G8,


/* -- Alteracao - Inicio - 14/02/2001 - Carlos/Leonel - tratamento para cba sala 86ka -- */
#ifndef	USA_ATN8
  "CONVERSAO A/D",	      			"",    NULL,  	NIVEL_SUPER, FLOAT, "%-8.2f",	0.0,  0.0,   1.0, TITULO_3,    AT, "", "", G8,
  "CanalVLinha",				"",		&VarAvl.CanalVLinha,		NIVEL_SUPER, INT,	"%-3.0f",	-7.0,	320.0,	1.0,	PAR_LINHA, AT, "", "", G8,

  "RelNaoMux-0",				"A/V",	&VarAvl.RelNaoMux[0],		NIVEL_SUPER, FLOAT,	"%-10.3f",	0.0,  99999.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "RelNaoMux-1",				"A/V",	&VarAvl.RelNaoMux[1],		NIVEL_SUPER, FLOAT,	"%-10.3f",	0.0,  99999.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "RelNaoMux-2",				"X/V",	&VarAvl.RelNaoMux[2],		NIVEL_SUPER, FLOAT,	"%-10.3f",	0.0,  99999.0,	1.0,	PAR_LINHA, AT, "", "", G8,

  "RelEntEsp-0",				"X/V",	&VarAvl.RelEntEsp[0],		NIVEL_SUPER, FLOAT,	"%-10.3f",	0.0,  99999.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "RelEntEsp-1",				"X/V",	&VarAvl.RelEntEsp[1],		NIVEL_SUPER, FLOAT,	"%-10.3f",	0.0,  99999.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "RelEntEsp-2",				"X/V",	&VarAvl.RelEntEsp[2],		NIVEL_SUPER, FLOAT,	"%-10.3f",	0.0,  99999.0,	1.0,	PAR_LINHA, AT, "", "", G8,

  "LsbTensaoCuba",				"mV",	&VarAvl.LsbTensao,			NIVEL_SUPER, FLOAT,	"%-10.7f",	0.0,	999.0,	1000.0,	PAR_LINHA, AT, "", "", G8,
  "LsbNaoMux-0",				"mV",	&VarAvl.LsbNaoMux[0],		NIVEL_SUPER, FLOAT,	"%-10.7f",	0.0,	999.0,	1000.0,	PAR_LINHA, AT, "", "", G8,
  "LsbNaoMux-1",				"mV",	&VarAvl.LsbNaoMux[1],		NIVEL_SUPER, FLOAT,	"%-10.7f",	0.0,	999.0,	1000.0,	PAR_LINHA, AT, "", "", G8,
  "LsbNaoMux-2",				"mV",	&VarAvl.LsbNaoMux[2],		NIVEL_SUPER, FLOAT,	"%-10.7f",	0.0,	999.0,	1000.0,	PAR_LINHA, AT, "", "", G8,

  "NCanaisNMux",				"",		&VarAvl.NCanaisNMux,		NIVEL_SUPER, INT,	"%-1.0f",	0.0,	8.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "VMuxMax",					"V",	&VarAvl.VMuxMax,			NIVEL_SUPER, FLOAT,	"%-6.2",	0.0,	999.0,	1.0,	REL_LINHA, AT, "", "", G8,
  "SadMaxErr",					"",		&VarAvl.SadMaxErr,			NIVEL_SUPER, INT,	"%-2.0f",	0.0,	10.0,	1.0,	REL_LINHA, AT, "", "", G8,
#endif
  "OUTRAS",	      			"",    NULL,  	NIVEL_SUPER, FLOAT, "%-8.2f",	0.0,  0.0,   1.0, TITULO_3,    AT, "", "", G8,
  "Atn8TempLimInf",				"oC",	&VarAvl.Atn8TempLimInf,		NIVEL_SUPER, FLOAT,	"%-2.0f",	  0.0,	99.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "Atn8TempLimSup",				"oC",	&VarAvl.Atn8TempLimSup,		NIVEL_SUPER, FLOAT,	"%-2.0f",	  0.0,	99.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "TmpMaxSinalCorr",			"HH",	&VarAvl.TmpMaxSinalCorr,	NIVEL_SUPER, SHORT_INT,	"%-2.0f",	  0.0,	100.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "TmpMaxSinalQueb",			"HH",	&VarAvl.TmpMaxSinalQueb,	NIVEL_SUPER, SHORT_INT,	"%-2.0f",	  0.0,	100.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "TmpMaxSinalTrPi",			"HH",	&VarAvl.TmpMaxSinalTrPi,	NIVEL_SUPER, SHORT_INT,	"%-2.0f",	  0.0,	100.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "TmpMaxSinalCruz",			"HH",	&VarAvl.TmpMaxSinalCruz,	NIVEL_SUPER, SHORT_INT,	"%-2.0f",	  0.0,	100.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "ErroMaxReserva",				"%",	&VarAvl.ErroMaxReserva,		NIVEL_SUPER, FLOAT,	"%-5.1f",	  0.0,	100.0,	100.0,	PAR_LINHA, AT, "", "", G8,
  "NumCubas",					"",		&VarAvl.NumCubas,			NIVEL_SUPER, INT,	"%-3.0f",	0.0,	320.0,	1.0,	REL_LINHA, AT, "", "", G8,
  "OffInicNCubaOp",				"",		&VarAvl.OffInicNCubaOp,		NIVEL_SUPER, INT,	"%-4.0f",	0.0,	9999.0,	1.0,	REL_LINHA, AT, "", "", G8,
  "QUEBRADA OPE MOVEL",			"",    NULL,  	NIVEL_SUPER, FLOAT, "%-8.2f",	0.0,  0.0,   1.0, TITULO_3,    AT, "", "", G8,
  "TempoMovCimaOpMovel",		"seg",	&VarAvl.Par.TempoMoveCimaOpeMovel,	NIVEL_SUPER, SHORT_INT,	"%-2.0f",	  0.0,	10.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "TempoMovBaixOpMovel",		"seg",	&VarAvl.Par.TempoMoveBaixoOpeMovel,	NIVEL_SUPER, SHORT_INT,	"%-2.0f",	  0.0,	10.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "TempoSoproOpMovel",			"seg",	&VarAvl.Par.TempoSoproOpeMovel,	NIVEL_SUPER, SHORT_INT,	"%-2.0f",	  0.0,	10.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "LimMovBAtEa",				"vezes",&VarAvl.Par.LimMovBAtEa,	NIVEL_SUPER, SHORT_INT,	"%-2.0f",	  0.0,	10.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "LimMovCAtEa",				"vezes",&VarAvl.Par.LimMovCAtEa,	NIVEL_SUPER, SHORT_INT,	"%-2.0f",	  0.0,	10.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "LimSoproAtEa",				"vezes",&VarAvl.Par.LimSoproAtEa,	NIVEL_SUPER, SHORT_INT,	"%-2.0f",	  0.0,	10.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "SOPRO ESPECIAL",				"",		NULL,  	NIVEL_SUPER, FLOAT, "%-8.2f",	0.0,  0.0,   1.0, TITULO_3,    AT, "", "", G8,
  "TLimSoproEspec",				"Min",	&VarAvl.Par.TLimSoproEspec,	NIVEL_SUPER, SHORT_INT,	"%-4.0f",	  0.0,	1440.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "TIntervSoproEspec",			"Seg",	&VarAvl.Par.TIntervSoproEspec,NIVEL_SUPER, SHORT_INT,"%-4.0f",	  0.0,	3600.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "VLimSoproEspec",				"V",	&VarAvl.Par.VLimSoproEspec,	NIVEL_SUPER, FLOAT,		"%-5.2f",	  0.0,	10.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "DurAcionaSoproEspec",		"Seg",	&VarAvl.Par.DurAcionaSoproEspec,NIVEL_SUPER, SHORT_INT,"%-3.0f",  0.0,	60.0,	1.0,	PAR_LINHA, AT, "", "", G8,
	/* -- Outras informacoes -- */
  "LinhaHabilitada",			"F/V",	&VarAvl.LinhaHabilitada,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	TODAS_T orb OPC_R, AT, "", "", G8,
  "DifCorAlta",					"",		&VarAvl.Trab.DifCorAlta,	NIVEL_SUPER, BYTE,	"%-2.0i",	0.0,	10.0,	1,		TODAS_T, AT, "", "", G8,
  "TimerMcc",					"seg",	&VarAvl.Trab.TimerMcc,		NIVEL_SUPER, FLOAT,	"%-8.6i",	0.0,	120.0,	1,		REL_LINHA, AT, "", "", G8,
  "TimerMcp",					"seg",	&VarAvl.Trab.TimerMcp,		NIVEL_SUPER, FLOAT,	"%-8.6i",	0.0,	120.0,	1,		REL_LINHA, AT, "", "", G8,

	/* -- Valores de ciclo de leitura -- */
  "IinstPri",				"kA",		&VarAvl.Iinst,				NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	140.0,	1e-3,	TODAS_T, AT, "IPrim",  "LinhaC1", G8,
  "IinstRes",				"kA",		&VarAvl.IinstRes,			NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	140.0,	1e-3,	TODAS_T, AT, "IRes",	"LinhaC2", G8,
  "VLinhaInst",				"V",		&VarAvl.VLinhaInst,			NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	1000.0,	1.0,	TODAS_T, AT, "VLinha",  "LinhaC3", G8,
  "dial1",					"kA",		&VarAvl.Iinst,				NIVEL_SUPER,	FLOAT,	"%-5.2f",		50.0,	140.0,	1e-3,	TODAS_T,	AT, "IPrim",	"Dial1", G8,
  "dial2",					"kA",		&VarAvl.IinstRes,			NIVEL_SUPER,	FLOAT,	"%-5.2f",		50.0,	140.0,	1e-3,	TODAS_T,	AT, "IRes",	    "Dial2", G8,
	/* -- Valores de ciclo de controle -- */
  "ICicContlMed",				"kA",	&VarAvl.ICicContlMed,		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	140.0,	1e-3,	TODAS_T orb OPC_R, AT, "", "", G8,
  "ICicContlMedRes",			"kA",	&VarAvl.ICicContlMedRes,	NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	140.0,	1e-3,	TODAS_T orb OPC_R, AT, "", "", G8,
  "IRapCicContl",				"kA",	&VarAvl.IRapCicContl,		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	140.0,	1e-3,	TODAS_T, AT, "", "", G8,
  "IAlvo",						"kA",	&VarAvl.IAlvo,				NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	140.0,	1e-3,	TODAS_T, AT, "", "", G8,
  "VLinhaCicCont",				"V",	&VarAvl.VLinhaCicCont,		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	1000.0,	1.0,	TODAS_T orb OPC_R, AT, "", "", G8,
  "TurnoAtual",					"",		&VarAvl.TurnoAtual,			NIVEL_SUPER, INT,	"%-1.0f",	0.0,	9.0,	1.0,	TODAS_T, AT, "", "", G8,
    /* -- Contadores Gerais -- */
  "ContLGeral",					"",		&VarAvl.ContLGeral,			NIVEL_SUPER, LONG,	"%-10.0f",	0.0,	1e10,	1.0,	TODAS_T, AT, "", "", G8,
  "ContCubaFora",				"",		&VarAvl.ContCubaFora,		NIVEL_SUPER, INT,	"%-5.0f",	0.0,	1e5,	1.0,	TODAS_T, AT, "", "", G8,

  "ReservaNAtivo",				"F/V",	&VarAvl.ReservaAtivo,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	TODAS_T, AT, "", "", G8,
/* -- Alteracao - Inicio - 14/02/2001 - Carlos/Leonel - tratamento para cba sala 86ka -- */
#ifdef	USA_ATN8
  "ANALOGICAS ATNCA",	"",				NULL,						NIVEL_SUPER, INT,	"%-5.0f",	0.0,	1e6,	1.0,	TITULO_5, 	 AT, "", "", G2,
  "TensaoLinha_CA1",				"",		&VarAvl.ValorEntEsp[0],		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	99999.0,	1.0,	REL_ECHELON, AT, "", "", G8,
  "Corrente1_CA1",					"kA",		&VarAvl.ValorEntEsp[1],		NIVEL_SUPER, FLOAT,	"%-7.3f",	0.0,	999.0,	1e-3,	REL_ECHELON, AT, "", "", G8,
  "Corrente2_CA1",					"kA",		&VarAvl.ValorEntEsp[2],		NIVEL_SUPER, FLOAT,	"%-7.3f",	0.0,	999.0,	1e-3,	REL_ECHELON, AT, "", "", G8,
  "TensaoLinha_CA2",				"",		&VarAvl.ValorEntEsp[3],		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	99999.0,	1.0,	REL_ECHELON, AT, "", "", G8,
  "Corrente1_CA2",					"kA",		&VarAvl.ValorEntEsp[4],		NIVEL_SUPER, FLOAT,	"%-7.3f",	0.0,	999.0,	1e-3,	REL_ECHELON, AT, "", "", G8,
  "Corrente2_CA2",					"kA",		&VarAvl.ValorEntEsp[5],		NIVEL_SUPER, FLOAT,	"%-7.3f",	0.0,	999.0,	1e-3,	REL_ECHELON, AT, "", "", G8,
  "ErroAdTensao_CA1",				"",		&VarAvl.Sup.ErrorADAtn8[0][0],	NIVEL_SUPER, SHORT_INT,	"%-6.0f",	0.0,	999999.0,	1.0,	REL_ECHELON, AT, "", "", G8,
  "ErroAdCorr1_CA1",				"",		&VarAvl.Sup.ErrorADAtn8[0][1],	NIVEL_SUPER, SHORT_INT,	"%-6.0f",	0.0,	999999.0,	1.0,	REL_ECHELON, AT, "", "", G8,
  "ErroAdCorr2_CA1",				"",		&VarAvl.Sup.ErrorADAtn8[0][2],	NIVEL_SUPER, SHORT_INT,	"%-6.0f",	0.0,	999999.0,	1.0,	REL_ECHELON, AT, "", "", G8,
  "ErroAdTensao_CA2",				"",		&VarAvl.Sup.ErrorADAtn8[1][0],	NIVEL_SUPER, SHORT_INT,	"%-6.0f",	0.0,	999999.0,	1.0,	REL_ECHELON, AT, "", "", G8,
  "ErroAdCorr1_CA2",				"",		&VarAvl.Sup.ErrorADAtn8[1][1],	NIVEL_SUPER, SHORT_INT,	"%-6.0f",	0.0,	999999.0,	1.0,	REL_ECHELON, AT, "", "", G8,
  "ErroAdCorr2_CA2",				"",		&VarAvl.Sup.ErrorADAtn8[1][2],	NIVEL_SUPER, SHORT_INT,	"%-6.0f",	0.0,	999999.0,	1.0,	REL_ECHELON, AT, "", "", G8,
#else
  "EntEspInst[0]",				"",		&VarAvl.ValorEntEsp[0],		NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	1000.0,	1.0,	TODAS_T, AT, "", "", G8,
#endif
/* -- Alteracao - Fim - 14/02/2001 - Carlos/Leonel - tratamento para cba sala 86ka -- */

	/* -- Valores diarios -- */
  "IMedDia",					"kA",	&VarAvl.IMedDia,			NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	140.0,	1e-3,	PAR_PLAN, AT, "", "", G8,
  "IMedDiaRes",					"kA",	&VarAvl.IMedDiaRes,			NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	140.0,	1e-3,	TODAS_T, AT, "", "", G8,
  "IAlvoDia",					"kA",	&VarAvl.IAlvoDia,			NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	140.0,	1e-3,	PAR_PLAN, AT, "", "", G8,
  "VLinhaDia",					"V",	&VarAvl.VLinhaDia,			NIVEL_SUPER, FLOAT,	"%-6.1f",   0.0,	1e3,	1.0,	PAR_PLAN, AT, "", "", G8,
  "NCicContDia",				"",		&VarAvl.NCicContDia,		NIVEL_SUPER, INT,	"%-5.0f",	0.0,	1e5,	1.0,	TODAS_T, AT, "", "", G8,
  "NCicAtivoDia",				"",		&VarAvl.NCicAtivoDia,		NIVEL_SUPER, INT,	"%-5.0f",	0.0,	1e5,	1.0,	TODAS_T, AT, "", "", G8,
  "PotLinhaDia",				"MW",	&VarAvl.PotLinhaDia,		NIVEL_SUPER, FLOAT,	"%-7.2f",   0.0,	1e5,	1e-6,	TODAS_T, AT, "", "", G8,
  "CubasNormDia",				"",		&VarAvl.CubasNormDia,		NIVEL_SUPER, FLOAT,	"%-3.0f",   0.0,	1e3,	1.0,	TODAS_T, AT, "", "", G8,
  "CubasLigParDia",				"",		&VarAvl.CubasLigParDia,		NIVEL_SUPER, FLOAT,	"%-3.0f",   0.0,	1e3,	1.0,	TODAS_T, AT, "", "", G8,
  "RCubasDiaBruta",			"MiOhm",	&VarAvl.RCubasDiaBruta,		NIVEL_SUPER, FLOAT,	"%-5.2f",   0.0,	99.0,	1e6,	TODAS_T, AT, "", "", G8,
  "NumEaDia",					"",		&VarAvl.Sup.NumEaDia,		NIVEL_SUPER, SHORT_INT,	"%-4.0f",	0.0,	9999.0,	1.0,	PAR_PLAN orb OPC_R, AT, "", "", G8,
  "Ea24h",						"",		&VarAvl.Sup.Ea24h,			NIVEL_SUPER, SHORT_INT,	"%-4.0f",	0.0,	9999.0,	1.0,	PAR_PLAN orb OPC_R, AT, "", "", G8,
  "AtrasoEA",					"",		&VarAvl.Sup.AtrasoEA,		NIVEL_SUPER, BYTE,	"%-4.0f",	0.0,	9999.0,	1.0,	PAR_PLAN orb OPC_R, AT, "", "", G8,
  "NumEaDiaTurno",				"",		&VarAvl.Trab.NumEaDiaTurno,	NIVEL_SUPER, SHORT_INT,	"%-4.0f",	0.0,	9999.0,	1.0,	PAR_PLAN orb OPC_R, AT, "", "", G8,
  "Ea24hTurno",					"",		&VarAvl.Trab.Ea24hTurno,	NIVEL_SUPER, SHORT_INT,	"%-4.0f",	0.0,	9999.0,	1.0,	PAR_PLAN orb OPC_R, AT, "", "", G8,
  "AtrasoEATurno",				"",		&VarAvl.Trab.AtrasoEATurno,	NIVEL_SUPER, SHORT_INT,	"%-4.0f",	0.0,	9999.0,	1.0,	PAR_PLAN orb OPC_R, AT, "", "", G8,


/* -- Alteracao - Inicio - 14/02/2001 - Carlos/Leonel - tratamento para cba sala 86ka -- */
#ifdef	USA_ATN8
  /* -- alteracao - inicio - 13/09/00 - Robson - Inclusao tratamento Atn8 -- */
  "CONF I ATN8",	      			"",    NULL,  	NIVEL_SUPER, FLOAT, "%-8.2f",	0.0,  0.0,   1.0, TITULO_3,    AT, "", "", G8,
  "IIndex-0",					"",		&VarAvl.IIndex[0],			NIVEL_SUPER, SHORT_INT,	"%-3.0f",	-1.0,	350.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "IChannel-0",					"",		&VarAvl.ICanal[0],			NIVEL_SUPER, BYTE,	"%-3.0f",	0.0,	3.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "IIndex-1",					"",		&VarAvl.IIndex[1],			NIVEL_SUPER, SHORT_INT,	"%-3.0f",	-1.0,	350.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "IChannel-1",					"",		&VarAvl.ICanal[1],			NIVEL_SUPER, BYTE,	"%-3.0f",	0.0,	3.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "IIndex-2",					"",		&VarAvl.IIndex[2],			NIVEL_SUPER, SHORT_INT,	"%-3.0f",	-1.0,	350.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "IChannel-2",					"",		&VarAvl.ICanal[2],			NIVEL_SUPER, BYTE,	"%-3.0f",	0.0,	3.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "IIndex-3",					"",		&VarAvl.IIndex[3],			NIVEL_SUPER, SHORT_INT,	"%-3.0f",	-1.0,	350.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "IChannel-3",					"",		&VarAvl.ICanal[3],			NIVEL_SUPER, BYTE,	"%-3.0f",	0.0,	3.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "IIndex-4",					"",		&VarAvl.IIndex[4],			NIVEL_SUPER, SHORT_INT,	"%-3.0f",	-1.0,	350.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "IChannel-4",					"",		&VarAvl.ICanal[4],			NIVEL_SUPER, BYTE,	"%-3.0f",	0.0,	3.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "IIndex-5",					"",		&VarAvl.IIndex[5],			NIVEL_SUPER, SHORT_INT,	"%-3.0f",	-1.0,	350.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "IChannel-5",					"",		&VarAvl.ICanal[5],			NIVEL_SUPER, BYTE,	"%-3.0f",	0.0,	3.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "IIndex-6",					"",		&VarAvl.IIndex[6],			NIVEL_SUPER, SHORT_INT,	"%-3.0f",	-1.0,	350.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "IChannel-6",					"",		&VarAvl.ICanal[6],			NIVEL_SUPER, BYTE,	"%-3.0f",	0.0,	3.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "IIndex-7",					"",		&VarAvl.IIndex[7],			NIVEL_SUPER, SHORT_INT,	"%-3.0f",	-1.0,	350.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "IChannel-7",					"",		&VarAvl.ICanal[7],			NIVEL_SUPER, BYTE,	"%-3.0f",	0.0,	3.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "VLineIndex",				"",		&VarAvl.VLinhaIndex,		NIVEL_SUPER, SHORT_INT,	"%-3.0f",	-1.0,	350.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  "VLineChannel",				"",		&VarAvl.VLinhaCanal,		NIVEL_SUPER, BYTE,	"%-3.0f",	0.0,	3.0,	1.0,	PAR_LINHA, AT, "", "", G8,
  /* -- alteracao - fim - 13/09/00 - Robson - Inclusao tratamento Atn8 -- */
#endif
/* -- Alteracao - Fim - 14/02/2001 - Carlos/Leonel - tratamento para cba sala 86ka -- */

#ifdef	USA_REDE_ECHELON
  "ESTATISTICA / LINHA",		"",				NULL,						NIVEL_SUPER, INT,	"%-5.0f",	0.0,	1e6,	1.0,	TITULO_5, 	 AT, "", "", G8,
  "ContadorMedia",				"",				&VarAvl.Atn7AvrCounter,		NIVEL_SUPER, INT,	"%-10.0f",	0.0,	1e9,	1.0,	REL_ECHELON, AT, "", "", G8,
  "Recepcao",					"",				NULL,						NIVEL_SUPER, INT,	"%-5.0f",	0.0,	1e6,	1.0,	TITULO_5, 	 AT, "", "", G8,
  "RxMediaTotal",				"Pkts/Sec",		&VarAvl.Atn7RxPktsSecAvr,	NIVEL_SUPER, FLOAT,	"%-8.3f",	0.0,	1e6,	1.0,	REL_ECHELON, AT, "", "", G8,
  "RxMaximoTotal",				"Pkts/Sec",		&VarAvl.Atn7RxPktsSecMax,	NIVEL_SUPER, FLOAT,	"%-8.3f",	0.0,	1e6,	1.0,	REL_ECHELON, AT, "", "", G8,
  "RxBytesTotal",				"Bytes",		&VarAvl.Atn7RxBytes,		NIVEL_SUPER, INT,	"%-10.0f",	0.0,	1e9,	1.0,	REL_ECHELON, AT, "", "", G8,
  "RxPktsTotal",				"Pkts",			&VarAvl.Atn7RxPkts,			NIVEL_SUPER, INT,	"%-10.0f",	0.0,	1e9,	1.0,	REL_ECHELON, AT, "", "", G8,
  "RxErrosTotal",				"",				&VarAvl.Atn7RxErrors,		NIVEL_SUPER, INT,	"%-5.0f",	0.0,	1e6,	1.0,	REL_ECHELON, AT, "", "", G8,
  "Transmissao",				"",				NULL,						NIVEL_SUPER, INT,	"%-5.0f",	0.0,	1e6,	1.0,	TITULO_5, 	 AT, "", "", G8,
  "TxMediaTotal",				"Pkts/Sec",		&VarAvl.Atn7TxPktsSecAvr,	NIVEL_SUPER, FLOAT,	"%-8.3f",	0.0,	1e6,	1.0,	REL_ECHELON, AT, "", "", G8,
  "TxMaximoTotal",				"Pkts/Sec",		&VarAvl.Atn7TxPktsSecMax,	NIVEL_SUPER, FLOAT,	"%-8.3f",	0.0,	1e6,	1.0,	REL_ECHELON, AT, "", "", G8,
  "TxBytesTotal",				"Bytes",		&VarAvl.Atn7TxBytes,		NIVEL_SUPER, INT,	"%-10.0f",	0.0,	1e9,	1.0,	REL_ECHELON, AT, "", "", G8,
  "TxPktsTotal",				"Pkts",			&VarAvl.Atn7TxPkts,			NIVEL_SUPER, INT,	"%-10.0f",	0.0,	1e9,	1.0,	REL_ECHELON, AT, "", "", G8,
  "TxErrosTotal",				"",				&VarAvl.Atn7TxErrors,		NIVEL_SUPER, INT,	"%-5.0f",	0.0,	1e6,	1.0,	REL_ECHELON, AT, "", "", G8,
/* -- Alteracao - Inicio - 14/02/2001 - Carlos/Leonel - tratamento para cba sala 86ka -- */
 #ifndef	USA_ATN8
  /* -- Alteracao - inicio - 13/09/99 - Leonel - Inclusao de estatistica de erro de conversao -- */
  "ERROS A/D NAO MUX",			"",				NULL,						NIVEL_SUPER, INT,	"%-5.0f",	0.0,	1e6,	1.0,	TITULO_5, 	 AT, "", "", G8,
  "ErroADNMux_0",				"",				&VarAvl.ErroADNMux[0],		NIVEL_SUPER, SHORT_INT,"%-5.0f",0.0, 65535.0,	1.0,	REL_ECHELON, AT, "", "", G8,
  "ErroADNMux_1",				"",				&VarAvl.ErroADNMux[1],		NIVEL_SUPER, SHORT_INT,"%-5.0f",0.0, 65535.0,	1.0,	REL_ECHELON, AT, "", "", G8,
  "ErroADEntEsp_0",			"",				&VarAvl.ErroADEntEsp[0],	NIVEL_SUPER, SHORT_INT,"%-5.0f",0.0, 65535.0,	1.0,	REL_ECHELON, AT, "", "", G8,
  /* -- Alteracao - fim - 13/09/99 - Leonel -- */
 #endif
/* -- Alteracao - Fim - 14/02/2001 - Carlos/Leonel - tratamento para cba sala 86ka -- */
#endif

  NULL,	NULL, 0, 0, 0,	NULL, 0.0, 0.0, 0.0, 0, 0, NULL, NULL
};


/*--- Estrutura de descricao das variaveis de parametro 1 de usuario ---*/
t_par_var_log VarParUser1[] =
{

  "BANDA SUP. MOVEL",		"",			NULL,	NIVEL_LOG, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "TAcresBSupMovel",	"min",		&VarPar1.TAcresBSupMovel,	NIVEL_SUPER, BYTE,	"%-3.0f",	0.0,	180.0,	1,		PAR_CUBAS, AT, "", "", G0,
  "AcresBSupMovel",		"MiOhm",	&VarPar1.AcresBSupMovel,	NIVEL_SUPER, FLOAT,	"%-5.3f",	0.0,	20.0,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "TMaxDesvio",			"HH:MM",	&VarPar1.TMaxDesvio,		NIVEL_SUPER, T_HORA,"%-5s",		0.0,	86340,	1.0,	PAR_CUBAS, AT, "", "", G0,

  "AEK",					"",			NULL,	NIVEL_LOG, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "HabAEK",				"V/F",		&VarPar1.HabAEK,			NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	1.0,	1,		PAR_CUBAS, AT, "", "", G0,
  "TMoveCima",				"s",	&VarPar1.AEK_TMoveCima,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	5.0,	1,		PAR_CUBAS, AT, "", "", G0,
  "TMoveBaixo",				"s",	&VarPar1.AEK_TMoveBaixo,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	5.0,	1,		PAR_CUBAS, AT, "", "", G0,
  "TParar",					"s",	&VarPar1.AEK_TParar,		NIVEL_SUPER, BYTE,	"%-3.0f",	0.0,	180.0,	1,		PAR_CUBAS, AT, "", "", G0,
  "TEspera",				"s",	&VarPar1.AEK_TEspera,		NIVEL_SUPER, BYTE,	"%-3.0f",	0.0,	30.0,	1,		PAR_CUBAS, AT, "", "", G0,
  "MaxMoveCima",			"s",	&VarPar1.AEK_MaxMoveCima,	NIVEL_SUPER, BYTE,	"%-3.0f",	0.0,	5.0,	1,		PAR_CUBAS, AT, "", "", G0,
  "ForcaSubidas",		"V/F",		&VarPar1.AEK_ForcaSubidas,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	1.0,	1,		PAR_CUBAS, AT, "", "", G0,
  "TForcaDesce",			"s",	&VarPar1.TForcaDesce,		NIVEL_SUPER, SHORT_INT,	"%-3.0f",	0.0,	500.0,	1,		PAR_CUBAS, AT, "", "", G0,
  "VForcaDesce",			"V",	&VarPar1.VForcaDesce,		NIVEL_SUPER, FLOAT,	"%-4.2f",	0.0,	30.0,	1,		PAR_CUBAS, AT, "", "", G0,
  "InibeTerminal",		"V/F",		&VarPar1.AEK_InibeTerminal,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	1.0,	1,		PAR_CUBAS, AT, "", "", G0,
  "TVerTensao",				"s",	&VarPar1.TVerTensao,		NIVEL_SUPER, SHORT_INT,	"%-3.0f",	0.0,	500.0,	1,		PAR_CUBAS, AT, "", "", G0,
  "TFMoveBaixo",			"s",	&VarPar1.AEK_TFMoveBaixo,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	5.0,	1,		PAR_CUBAS, AT, "", "", G0,
  
  "SMART FEED",		"",			NULL,	NIVEL_LOG, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "HabSmartFeed",		"V/F",		&VarPar1.HabSmartFeed,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	1.0,	1,		PAR_CUBAS, AT, "", "", G0,
  "HabMovSmartFeed",	"V/F",		&VarPar1.HabMovSmartFeed,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	1.0,	1,		PAR_CUBAS, AT, "", "", G0,
  "KSIncDeriv",				"",		&VarPar1.SF_KSIncDeriv,		NIVEL_SUPER, FLOAT,	"%-5.3f",	0.0,	1.0,	1,		PAR_CUBAS, AT, "", "", G0,
  "SUnderFeed",			"MiOhm",	&VarPar1.SF_SUFeed,			NIVEL_SUPER, FLOAT,	"%-6.3f",	-10.0,	30.0,	1,		PAR_CUBAS, AT, "", "", G0,
  "UnderFeed",			"MiOhm",	&VarPar1.SF_UnderFeed,		NIVEL_SUPER, FLOAT,	"%-6.3f",	-10.0,	30.0,	1,		PAR_CUBAS, AT, "", "", G0,
  "NormalFeed",			"MiOhm",	&VarPar1.SF_NormalFeed,		NIVEL_SUPER, FLOAT,	"%-6.3f",	-10.0,	30.0,	1,		PAR_CUBAS, AT, "", "", G0,
  "OverFeed",			"MiOhm",	&VarPar1.SF_OverFeed,		NIVEL_SUPER, FLOAT,	"%-6.3f",	-10.0,	30.0,	1,		PAR_CUBAS, AT, "", "", G0,
  "PassoAcima",			"seg",		&VarPar1.SF_PassoAcima,		NIVEL_SUPER, FLOAT,	"%-3.1f",	0.0,	2.0,	1,		PAR_CUBAS, AT, "", "", G0,
  "PassoAbaixo",		"seg",		&VarPar1.SF_PassoAbaixo,	NIVEL_SUPER, FLOAT,	"%-3.1f",	0.0,	2.0,	1,		PAR_CUBAS, AT, "", "", G0,
  "LimMovBaixo",		"seg",		&VarPar1.SF_LimMovBaixo,	NIVEL_SUPER, FLOAT,	"%-3.1f",	0.0,	6.0,	1,		PAR_CUBAS, AT, "", "", G0,
  "LimMovCima",			"seg",		&VarPar1.SF_LimMovCima,		NIVEL_SUPER, FLOAT,	"%-3.1f",	0.0,	6.0,	1,		PAR_CUBAS, AT, "", "", G0,

  "MOV. INICIO QUEBRA",		"",			NULL,	NIVEL_LOG, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "HabLogMovQueb",			"0=Des,1=Hab", 	&VarPar1.HabLogMovQueb,  		NIVEL_SUPER, BYTE,  	"%-1.0f",   0.0,     1.0,  1.0,	PAR_CUBAS, AT, "", "", G0,
  "KPcQueb",			"",			&VarPar1.KPcQueb,			NIVEL_CONFIG_1, FLOAT,	"%-3.1f",	0.0,	  5.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "HabPrecMovQueb",			"0=Des,1=Hab", 	&VarPar1.HabPrecMovQueb,  		NIVEL_SUPER, BYTE,  	"%-1.0f",   0.0,     1.0,  1.0,	PAR_CUBAS, AT, "", "", G0,
  "NumCicRes4s",			"", 	&VarPar1.NumCicRes4s,  		NIVEL_SUPER, BYTE,  	"%-2.0f",   0.0,     30.0,  1.0,	PAR_CUBAS, AT, "", "", G0,
  "NumMovPrecQueb",			"", 	&VarPar1.NumMovPrecQueb, 	NIVEL_SUPER, BYTE,  	"%-1.0f",   0.0,     4.0, 	 1.0,	PAR_CUBAS, AT, "", "", G0,
  "DurMovBaixoMinF",			"", 	&VarPar1.DurMovBaixoMinF, 	NIVEL_SUPER, FLOAT,  	"%-3.1f",   0.5,     5.0, 	 1.0,	PAR_CUBAS, AT, "", "", G0,
  "DurMovBaixoMaxF",			"", 	&VarPar1.DurMovBaixoMaxF, 	NIVEL_SUPER, FLOAT,  	"%-3.1f",   1.0,     5.0, 	 1.0,	PAR_CUBAS, AT, "", "", G0,
  "DurMovCimaMinF",			"", 	&VarPar1.DurMovCimaMinF, 	NIVEL_SUPER, FLOAT,  	"%-3.1f",   0.5,     5.0, 	 1.0,	PAR_CUBAS, AT, "", "", G0,
  "DurMovCimaMaxF",			"", 	&VarPar1.DurMovCimaMaxF, 	NIVEL_SUPER, FLOAT,  	"%-3.1f",   1.0,     5.0, 	 1.0,	PAR_CUBAS, AT, "", "", G0,

  "MONITORA CUNHA",						"",		NULL,	NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,		0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "EfeitoTenCal",		"min",		&VarPar1.EfeitoTenCal,		NIVEL_SUPER, SHORT_INT,	"%-4.0i",	0.0,	9999.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "TenLimCal",			"V",		&VarPar1.TenLimCal,			NIVEL_SUPER, FLOAT,		"%-5.2f",	0.0,	99.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "TocaSirene",			"HH:MM",	&VarPar1.TocaSirene,		NIVEL_SUPER, T_HORA,	"%-5s",		0.0,	86340,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "DesligaSala",		"HH:MM",	&VarPar1.DesligaSala,		NIVEL_SUPER, T_HORA,	"%-5s",		0.0,	86340,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "IntervSirene",		"HH:MM",	&VarPar1.IntervSirene,		NIVEL_SUPER, T_HORA,	"%-5s",		0.0,	86340,	1.0,	PAR_CUBAS, AT, "", "", G0,

  "SOPRA CHAMINE",						"",		NULL,	NIVEL_CONFIG_1, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "TSopraChamine",		"seg",		&VarPar1.TSopraChamine,		NIVEL_CONFIG_1, BYTE,	"%-2.0f",	0.0,	99.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "TSinalizaSopro",		"seg",		&VarPar1.TSinalizaSopro,	NIVEL_CONFIG_1, BYTE,	"%-2.0f",	0.0,	99.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "IntervSoproQueb",	"min",		&VarPar1.IntervSoproQueb,	NIVEL_CONFIG_1, BYTE,	"%-2.0f",	0.0,	99.0,	1.0,	PAR_CUBAS, AT, "", "", G0,	
  "IntervSinalSopro",	"seg",		&VarPar1.IntervSinalSopro,	NIVEL_CONFIG_1, BYTE,	"%-2.0f",	0.0,	99.0,	1.0,	PAR_CUBAS, AT, "", "", G0,

  "CORRIDA",						"",		NULL,	NIVEL_CONFIG_1, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "HabCamSimul",		"V/F",		&VarPar1.HabCamSimul,		NIVEL_SUPER, 	BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "HoraRefCorr",		"HH:MM",	&VarPar1.HoraRefCorr,		NIVEL_CONFIG_1, T_HORA,	"%-5s",		0.0,	86340,	1.0,	PAR_CUBAS orb OPC_R, AT, "", "", G0,
  "HabKpbCorrida",		  "V/F",	&VarPar1.HabKbpCorrida,		NIVEL_SUPER, 	BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	PAR_CUBAS, AT, "", "", G0,


  "QUEBRADA PROG.",						"",		NULL,	NIVEL_CONFIG_1, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "HabCalcHoraQueb",	"V/F",		&VarPar1.HabCalcHoraQueb,	NIVEL_CONFIG_1, BYTE,	"%-1.0f",	0.0,	1.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "HoraRefQuebProg",	"HH:MM",	&VarPar1.HoraRefQuebProg,	NIVEL_CONFIG_1, T_HORA,	"%-5s",		0.0,	86340,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "IntervQuebProg",		"HH:MM",	&VarPar1.IntervQuebProg,	NIVEL_CONFIG_1, T_HORA,	"%-5s",		1.0,	86340,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "LadoRefQueb",		"1=I/2=E",	&VarPar1.LadoRefQueb,		NIVEL_CONFIG_1, BYTE,	"%-1.0f",	1.0,	2.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "DelayLadoQueb1",		"seg",		&VarPar1.DelayLadoQueb1,	NIVEL_CONFIG_1, SHORT_INT,	"%-4.0f",	0.0,	9999.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "DelayLadoQueb2",		"seg",		&VarPar1.DelayLadoQueb2,	NIVEL_CONFIG_1, SHORT_INT,	"%-4.0f",	0.0,	9999.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "LadoQuebIdx",		"",			&VarPar1.LadoQuebIdx,		NIVEL_CONFIG_1, INT,	"%-5.0i",	0.0,	65535.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "InverteIdx",			"",			&VarPar1.InverteIdx,		NIVEL_CONFIG_1, BYTE,	"%-1.0i",	0.0,	1.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "IdxQuebMix",			"",			&VarPar1.IdxQuebMix,		NIVEL_CONFIG_1, INT,	"%-5.0i",	0.0,	99999,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "IntervQuebMix",		"HH:MM",	&VarPar1.IntervQuebMix,		NIVEL_CONFIG_1, T_HORA,	"%-5s",		0.0,	86340,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "InibeQPQuebProg",	"min",		&VarPar1.InibeQPQuebProg,	NIVEL_CONFIG_1, BYTE,	"%-2.0i",	0.0,	15.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "NQuebLogica",		"",			&VarPar1.NQuebLogica,		NIVEL_CONFIG_1, BYTE,	"%-2.0i",	0.0,	32.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "NQuebPassadas",		"",			&VarPar1.NQuebPassadas,		NIVEL_CONFIG_1, BYTE,	"%-2.0i",	0.0,	3.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "HabPulaQuebProg",	"V/F",		&VarPar1.HabPulaQuebProg,	NIVEL_CONFIG_1, BYTE,	"%-1.0i",	0.0,	1.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "IntQPQProg",			"min",		&VarPar1.IntQPQProg,		NIVEL_CONFIG_1, BYTE,	"%-3.0i",	0.0,	240.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "IntEAQProg",			"min",		&VarPar1.IntEAQProg,		NIVEL_CONFIG_1, BYTE,	"%-3.0i",	0.0,	240.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "MaxPassaQueb",		"",		&VarPar1.MaxPassaQueb,		NIVEL_CONFIG_1, BYTE,	"%-1.0i",	0.0,	5.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "HabEsperaQP",		"V/F",		&VarPar1.HabEsperaQP,		NIVEL_CONFIG_1, BYTE,	"%-1.0i",	0.0,	1.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "NQuebInibida",		"",			&VarPar1.NQuebInibida,		NIVEL_CONFIG_1, BYTE,	"%-2.0i",	0.0,	50.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "NQuebAtraso",		"",			&VarPar1.NQuebAtraso,		NIVEL_CONFIG_1, BYTE,	"%-2.0i",	0.0,	3.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "NQuebForcaEA",		"",			&VarPar1.NQuebForcaEA,		NIVEL_CONFIG_1, BYTE,	"%-2.0i",	0.0,	32.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
      
  "DER. NEGATIVA",						"",		NULL,	NIVEL_CONFIG_1, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "HabCalcDN",			"V/F",		&VarPar1.HabCalcDN,			NIVEL_CONFIG_1, BYTE,	"%-1.0f",	0.0,	  1.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "CalcDNQueb",			"HH:MM",	&VarPar1.CalcDNQueb,		NIVEL_CONFIG_1, T_HORA,	"%-5s",		0.0,	86340,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "TEfeitoDN",			"HH:MM",	&VarPar1.TEfeitoDN,			NIVEL_CONFIG_1, T_HORA,	"%-5s",		0.0,	86340,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "AlarmeDNQueb",		"HH:MM",	&VarPar1.AlarmeDNQueb,		NIVEL_CONFIG_1, T_HORA,	"%-5s",		0.0,	86340,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "NivelDN",			"MiOhm",	&VarPar1.NivelDN,			NIVEL_CONFIG_1, FLOAT,	"%-6.3f",	0.0,		99,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "DERIVADA BAIXA",						"",		NULL,	NIVEL_CONFIG_1, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "HabCalcDB",			"V/F",		&VarPar1.HabCalcDB,			NIVEL_CONFIG_1, BYTE,	"%-1.0f",	0.0,	  1.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "CalcDBQueb",			"HH:MM",	&VarPar1.CalcDBQueb,		NIVEL_CONFIG_1, T_HORA,	"%-5s",		0.0,	86340,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "TEfeitoDB",			"HH:MM",	&VarPar1.TEfeitoDB,			NIVEL_CONFIG_1, T_HORA,	"%-5s",		0.0,	86340,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "AlarmeDBQueb",		"HH:MM",	&VarPar1.AlarmeDBQueb,		NIVEL_CONFIG_1, T_HORA,	"%-5s",		0.0,	86340,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "NivelDB",			"MiOhm",	&VarPar1.NivelDB,			NIVEL_CONFIG_1, FLOAT,	"%-6.3f",	0.0,		99,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "NumCiclosForaDB",	"",			&VarPar1.NumCiclosForaDB,	NIVEL_CONFIG_1, BYTE,	"%-2.0f",	0.0,	  30.0,	1.0,	PAR_CUBAS, AT, "", "", G0,

  "AJUSTE CAMISA",		"",			NULL,	NIVEL_CONFIG_0, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "HabAjCam",		"0=Des,1=Hab",	&VarPar1.HabAjCam,			NIVEL_CONFIG_0,	BYTE,	"%-1.0f",	0.0,	  1.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "LimMaxAjCam",		"Seg",		&VarPar1.LimMaxAjCam,		NIVEL_SUPER,	FLOAT,	"%-5.2f",	0.0,	 600.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "LimTAjMov",			"Seg",		&VarPar1.LimTAjMov,			NIVEL_SUPER,	FLOAT,	"%-5.2f",	0.0,	 600.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "IntAjCamCorr",		"Min",		&VarPar1.IntAjCamCorr,		NIVEL_SUPER,	SHORT_INT,"%-4.0f",	0.0,	 2880.0,1.0,	PAR_CUBAS, AT, "", "", G0,
  "DifResAgarraAnodo",	"MiOhm",	&VarPar1.DifResAgarra,		NIVEL_SUPER,	FLOAT,	"%-4.2f",	0.0,	 9.99,	1e6,	PAR_CUBAS, AT, "", "", G0,
  "HabMovCamTur",	"0=Des,1=Hab",	&VarPar1.HabMovCamTur,		NIVEL_CONFIG_0,	BYTE,	"%-1.0f",	0.0,	  1.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "TempoMovCamTur",		"Seg",		&VarPar1.TempoMovCamTur,	NIVEL_SUPER,	BYTE,	"%-2.0f",	1.0,	 10.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "TMovCamCorr",		"HH",		&VarPar1.TMovCamCorr,		NIVEL_SUPER,	BYTE,	"%-2.0f",	0.0,	 24.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "DifResAgarraCam",	"MiOhm",	&VarPar1.DifResAgarraCamisa,NIVEL_SUPER, 	FLOAT,	"%-4.2f",	0.0,	 9.99,  1e6,	PAR_CUBAS, AT, "", "", G0,

  "TABELA PARTIDA",		"",			NULL,	NIVEL_CONFIG_0, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "HabTabPartida",		"0=Des,1=Hab",	&VarPar1.HabTabPartida,	NIVEL_SUPER,	BYTE,	"%-1.0f",	0.0,	  1.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "NumTabPartida",		"",			&VarPar1.NumTabPartida,		NIVEL_SUPER,	BYTE,	"%-1.0f",	0.0,	  1.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "ALIMENTACAO",		"",			NULL,						NIVEL_CONFIG_0,	FLOAT,	"%-5.2f",	0.0,  	 0.0,	1.0,	TITULO_1, AT, "", "",	G0,
  "HabilitaPF",      	"V/F",		&VarPar1.HabilitaPF,        NIVEL_SUPER,	BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS,	AT, "", "",	G0,
  "AtivaBitCLP",      	"V/F",		&VarPar1.AtivaBitCLP,       NIVEL_SUPER,	BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS,	AT, "", "",	G0,
  "HabilitaBarra",      "V/F",		&VarPar1.HabilitaBarra,     NIVEL_SUPER,	BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS,	AT, "", "",	G0,
  "TempoFixo",      	"V/F",		&VarPar1.TempoFixo,     	NIVEL_SUPER,	BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS,	AT, "", "",	G0,
  "MassaBanho",		    "Kg",		&VarPar1.MassaBanho,		NIVEL_SUPER,	FLOAT,	"%-7.1f",	100.0, 10000.0,	1.0,	PAR_CUBAS,AT, "", "",	G0,
  "EfiCurrIni",			"%",		&VarPar1.EfiCurrIni,		NIVEL_SUPER,    FLOAT,	"%-6.2f",	0.0, 100.0,		1e2,	PAR_CUBAS,	AT, "", "",	G0,
  "EfiCurrTip",			"%",		&VarPar1.EfiCurrIni,		NIVEL_SUPER,    FLOAT,	"%-6.2f",	0.0, 100.0,		1e2,	PAR_CUBAS,	AT, "", "",	G0,
  "MaxEfiCurr",			"%",		&VarPar1.MaxEfiCurr,		NIVEL_SUPER,    FLOAT,	"%-6.2f",	0.0, 100.0,		1e2,	PAR_CUBAS,	AT, "", "",	G0,
  "MinEfiCurr",			"%",		&VarPar1.MinEfiCurr,		NIVEL_SUPER,    FLOAT,	"%-6.2f",	0.0, 100.0,		1e2,	PAR_CUBAS,	AT, "", "",	G0,
/* -- Alteracao - Inicio - Robson - 15/11/2000 - Quantidades diferentes por acionador -- */
  "QtdAlumCarga Alim1",	"gramas",	&VarPar1.QuantAlumCarga[0],	NIVEL_SUPER,	FLOAT,	"%-5.0f",	100.0, 10000.0,	1e3,	PAR_CUBAS,	AT, "", "",	G0,
  "QtdAlumCarga Alim2",	"gramas",	&VarPar1.QuantAlumCarga[1],	NIVEL_SUPER,	FLOAT,	"%-5.0f",	100.0, 10000.0,	1e3,	PAR_CUBAS,	AT, "", "",	G0,
  "QtdAlumCarga Alim3",	"gramas",	&VarPar1.QuantAlumCarga[2],	NIVEL_SUPER,	FLOAT,	"%-5.0f",	100.0, 10000.0,	1e3,	PAR_CUBAS,	AT, "", "",	G0,
  "QtdAlumCarga Alim4",	"gramas",	&VarPar1.QuantAlumCarga[3],	NIVEL_SUPER,	FLOAT,	"%-5.0f",	100.0, 10000.0,	1e3,	PAR_CUBAS,	AT, "", "",	G0,
/* -- Alteracao - Fim - Robson - 15/11/2000 - Quantidades diferentes por acionador -- */
  "ConcentracaNominal",	"%Al2O3",	&VarPar1.ConcNominal,		NIVEL_SUPER,	FLOAT,	"%-6.2f",	0.0,	100.0,	100.0,	PAR_ALIMENT,AT, "", "",	G0,
  "DesvioBalancoCarga",	"%",		&VarPar1.DesvioCarga,		NIVEL_SUPER,	FLOAT,	"%-6.2f",	0.0,	100.0,	100.0,	PAR_ALIMENT,AT, "", "",	G0,
  "DesvioPermConcNom.",	"%Al2O3",	&VarPar1.DesvioConNominal,	NIVEL_SUPER,	FLOAT,	"%-6.2f",	0.0,	100.0,	100.0,	PAR_ALIMENT,AT, "", "",	G0,
  "TemTipicoAlimPadao",	"HH:MM",	&VarPar1.TTipicoCheck,		NIVEL_SUPER,	T_HORA,	"%-5.0f",	0.0,	5999.0,	1.0,	PAR_ALIMENT,AT, "", "",	G0,
  "LimMinCheck",	    "%Al2O3",	&VarPar1.LimMinCheck,		NIVEL_SUPER,	FLOAT,	"%-5.1f",	0.0,	100.0,	100.0,	PAR_CUBAS,	AT, "", "",	G0,
  "MinDer",				"MiOhm/%",	&VarPar1.MinDer,			NIVEL_SUPER,	FLOAT,	"%-6.3f",	-10.0, 	10.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "MaxDer",				"MiOhm/%",	&VarPar1.MaxDer,			NIVEL_SUPER,	FLOAT,	"%-6.3f",	-10.0, 	10.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "DerivQueb",			"MiOhm/%",	&VarPar1.DerAliment,		NIVEL_SUPER,	FLOAT,	"%-6.3f",	-10.0, 	10.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "MinIntervQueb",		"HH:MM",	&VarPar1.MinIntervQueb,		NIVEL_SUPER,	T_HORA,	"%-5.0f",	0.0, 999999.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "IntervQueb",			"HH:MM",	&VarPar1.IntervQueb,		NIVEL_SUPER,	T_HORA,	"%-5.0f",	0.0, 999999.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "MaxNumQueb",			"",			&VarPar1.MaxNumQueb,		NIVEL_SUPER,	INT,    "%-4.0f",	0.0,  9999.0, 	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "MinConc",		    "%Al2O3",	&VarPar1.MinConc,			NIVEL_SUPER,	FLOAT,	"%-6.2f",	0.0,	100.0,	100.0,	PAR_CUBAS,	AT, "", "",	G0,
  "MaxConc",		    "%Al2O3",	&VarPar1.MaxConc,			NIVEL_SUPER,	FLOAT,	"%-6.2f",	0.0,	100.0,	100.0,	PAR_CUBAS,	AT, "", "",	G0,
  "ConcValidCheck",     "%Al2O3",	&VarPar1.ConcValidCheck,	NIVEL_SUPER,	FLOAT,	"%-6.2f",	1.0,	10.0,	100.0,	PAR_CUBAS,	AT, "", "",	G0,
  "ConcHabMove",        "%Al2O3",	&VarPar1.ConcHabMove,	    NIVEL_SUPER,	FLOAT,	"%-6.2f",	1.0,	10.0,	100.0,	PAR_CUBAS,	AT, "", "",	G0,
  "HabMoveSusp",        "0-3",		&VarPar1.HabMoveSusp,	    NIVEL_SUPER,	BYTE,	"%-1.0f",	0.0,	3.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "HabMovTrack",        "0-3",		&VarPar1.HabMovTrack,	    NIVEL_SUPER,	BYTE,	"%-1.0f",	0.0,	3.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "NumAcionaCheck",		"",			&VarPar1.NumAcionaCheck,	NIVEL_SUPER,	SHORT_INT, "%-5.0f",	0.0,  32000.0, 1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "MaxDeltaEfiCurr",	"%",		&VarPar1.MaxDeltaEfiCurr,	NIVEL_SUPER,	FLOAT,	"%-6.2f",	0.0,	100.0,	100.0,	PAR_CUBAS,	AT, "", "",	G0,
  "TaxaUnder",			"",			&VarPar1.TaxaUnder,			NIVEL_SUPER,	FLOAT,	"%-4.2f",	0.1,	1.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "UnderProgIni",		"",			&VarPar1.UnderProgIni,		NIVEL_SUPER,	FLOAT,	"%-4.2f",	0.1,	1.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "DeltaUnder",			"",			&VarPar1.DeltaUnder,		NIVEL_SUPER,	FLOAT,	"%-4.2f",	0.0,	1.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "IntervUnderProg",	"HH:MM",	&VarPar1.IntervUnderProg,	NIVEL_SUPER,	T_HORA,	"%-5.0f",	0.0, 999999.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "TaxaOverNorm",		"",			&VarPar1.TaxaOverNorm,		NIVEL_SUPER,	FLOAT,	"%-6.2f",	1.0, 999999.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "TaxaOverEA",			"",			&VarPar1.TaxaOverEA,		NIVEL_SUPER,	FLOAT,	"%-6.2f",	1.0, 999999.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "HabilitaOverEA", 	"V/F",		&VarPar1.HabilitaOverEA,    NIVEL_SUPER,	BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS,	AT, "", "",	G0,
// Inserido em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
  "HabilitaNormEA", 	"V/F",		&VarPar1.HabNormFeedEa,	    NIVEL_SUPER,	BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS,	AT, "", "",	G0,
  "OverOpcional",     	"V/F",		&VarPar1.OverOpcional,      NIVEL_SUPER,	BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS,	AT, "", "",	G0,
  "PercOverOp",			"%Al2O3",	&VarPar1.PercOverOp,		NIVEL_SUPER,	FLOAT,	"%-6.2f",	0.0,	100.0,	100.0,	PAR_CUBAS,	AT, "", "",	G0,
  "MaxOverCheck",		"",			&VarPar1.MaxOverCheck,		NIVEL_SUPER, SHORT_INT,	"%-2.0f",	0.0, 	99.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "MaxTOverEa",		    "HH:MM",	&VarPar1.MaxTOverEa,		NIVEL_SUPER,	T_HORA,	"%-5.0f",	0.0, 999999.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "DurNormCheck",		"HH:MM",	&VarPar1.DurNormCheck,		NIVEL_SUPER,	T_HORA,	"%-5.0f",	0.0, 999999.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "ConsumoResAlim",		"%Al2O3",	&VarPar1.ConsumoResAlim,	NIVEL_SUPER,	FLOAT,	"%-6.4f",	0.0,	100.0,	100.0,	PAR_CUBAS,	AT, "", "",	G0,
  "DerInitCheck",		"MiOhm/%",	&VarPar1.DerInitCheck,		NIVEL_SUPER,	FLOAT,	"%-5.2f",	-10.0, 	10.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "MaxDerInitCheck",	"MiOhm/%",	&VarPar1.MaxDerInitCheck,	NIVEL_SUPER,	FLOAT,	"%-5.2f",	-10.0, 	10.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "KSuaveAlim",		    "",	        &VarPar1.KSuaveAlim,		NIVEL_SUPER,	FLOAT,	"%-5.3f",	0.1,	 1.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "MaxIntervCheck",		"HH:MM",	&VarPar1.MaxIntervCheck,	NIVEL_SUPER,	T_HORA,	"%-5.0f",	0.0, 999999.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "MaxIntervEa",		"min",		&VarPar1.MaxIntervEa,		NIVEL_SUPER,	LONG,	"%-5.0f",	0.0, 99999.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "TempoTerminaEa",		"HH:MM",	&VarPar1.TTerminaEa,		NIVEL_SUPER,	T_HORA,	"%-5.0f",	0.0, 999999.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "EstabQueb",		    "HH:MM",	&VarPar1.EstabQueb,			NIVEL_SUPER,	T_HORA,	"%-5.0f",	0.0, 999999.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
// Inserido em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
  "EstabCorr",		    "HH:MM",	&VarPar1.EstabCorr,			NIVEL_SUPER,	T_HORA,	"%-5.0f",	0.0, 999999.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "TSuspLinhaD",	    "HH:MM",	&VarPar1.TSuspLinhaD,		NIVEL_SUPER,	T_HORA,	"%-5.0f",	0.0, 999999999.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "TSaiSuspLinhaD",	    "HH:MM",	&VarPar1.TSaiSuspLinhaD,	NIVEL_SUPER,	T_HORA,	"%-5.0f",	0.0, 999999999.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
// Inserido em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
  "PolOrd",				"",			&VarPar1.PolOrd,			NIVEL_SUPER,	SHORT_INT, "%-2.0f", 3.0,  10.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "Poly_0",				"",			&VarPar1.Poly[0],			NIVEL_SUPER,	FLOAT,	"%-11.4f",	-999999.0, 999999.0, 1.0,PAR_CUBAS,	AT, "", "",	G0,
  "Poly_1",				"",			&VarPar1.Poly[1],			NIVEL_SUPER,	FLOAT,	"%-11.4f",	-999999.0, 999999.0, 1.0,PAR_CUBAS,	AT, "", "",	G0,
  "Poly_2",				"",			&VarPar1.Poly[2],			NIVEL_SUPER,	FLOAT,	"%-11.4f",	-999999.0, 999999.0, 1.0,PAR_CUBAS,	AT, "", "",	G0,
  "Poly_3",				"",			&VarPar1.Poly[3],			NIVEL_SUPER,	FLOAT,	"%-11.4f",	-999999.0, 999999.0, 1.0,PAR_CUBAS,	AT, "", "",	G0,
  "Poly_4",				"",			&VarPar1.Poly[4],			NIVEL_SUPER,	FLOAT,	"%-11.4f",	-999999.0, 999999.0, 1.0,PAR_CUBAS,	AT, "", "",	G0,
  "Poly_5",				"",			&VarPar1.Poly[5],			NIVEL_SUPER,	FLOAT,	"%-11.4f",	-999999.0, 999999.0, 1.0,PAR_CUBAS,	AT, "", "",	G0,
  "Poly_6",				"",			&VarPar1.Poly[6],			NIVEL_SUPER,	FLOAT,	"%-11.4f",	-999999.0, 999999.0, 1.0,PAR_CUBAS,	AT, "", "",	G0,
  "Poly_7",				"",			&VarPar1.Poly[7],			NIVEL_SUPER,	FLOAT,	"%-11.4f",	-999999.0, 999999.0, 1.0,PAR_CUBAS,	AT, "", "",	G0,
  "Poly_8",				"",			&VarPar1.Poly[8],			NIVEL_SUPER,	FLOAT,	"%-11.4f",	-999999.0, 999999.0, 1.0,PAR_CUBAS,	AT, "", "",	G0,
  "Poly_9",				"",			&VarPar1.Poly[9],			NIVEL_SUPER,	FLOAT,	"%-11.4f",	-999999.0, 999999.0, 1.0,PAR_CUBAS,	AT, "", "",	G0,
  "Poly_10",			"",			&VarPar1.Poly[10],			NIVEL_SUPER,	FLOAT,	"%-11.4f",	-999999.0, 999999.0, 1.0,PAR_CUBAS,	AT, "", "",	G0,
  "AlF3Dia",		    "kg",	    &VarPar1.AlF3Dia,			NIVEL_SUPER,	SHORT_INT,"%-5.0f",	0.0,	 9999.0,	1.0,	PAR_CUBAS orb OPC_RW,	AT, "", "",	G0,
  "DataAlF3",		    "",	        &VarPar1.DataAlF3,			NIVEL_SUPER,	LONG,	"%-10.0f",	0.0,	 2000000000.0,	1.0,	REL_CUBAS orb OPC_RW,	AT, "", "",	G0,
  "NumSiloAlF3",		    "",	    &VarPar1.NumSiloAlF3,		NIVEL_SUPER,	BYTE,	"%-1.0f",	0.0,	 2.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "QuantAlF3Carga_1",	"gramas",	&VarPar1.QuantAlF3Carga[0],	NIVEL_SUPER,	FLOAT,	"%-5.0f",	0.0,	 9999.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "QuantAlF3Carga_2",	"gramas",	&VarPar1.QuantAlF3Carga[1],	NIVEL_SUPER,	FLOAT,	"%-5.0f",	0.0,	 9999.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "HoraIniAlF3",		"HH:MM",	&VarPar1.HoraIniAlF3,		NIVEL_SUPER,	T_HORA,	"%-5.0f",	0.0, 999999.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "TIntAlF3",			"HH:MM",	&VarPar1.TIntAlF3,			NIVEL_SUPER,	T_HORA,	"%-5.0f",	0.0, 999999.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "BitSiloAlF3_1",		"",			&VarPar1.BitAlF3[0],		NIVEL_SUPER,	BYTE,	"%-3.0f",	0.0,	 255.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "BitSiloAlF3_2",		"",			&VarPar1.BitAlF3[1],		NIVEL_SUPER,	BYTE,	"%-3.0f",	0.0,	 255.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "BitSiloAl2O3_1",		"",			&VarPar1.BitAl2O3[0],		NIVEL_SUPER,	BYTE,	"%-3.0f",	0.0,	 255.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "BitSiloAl2O3_2",		"",			&VarPar1.BitAl2O3[1],		NIVEL_SUPER,	BYTE,	"%-3.0f",	0.0,	 255.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "TFalhaAlim",		    "seg",	    &VarPar1.TFalhaAlim,		NIVEL_SUPER,	BYTE,	"%-3.0f",	0.0,	 200.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "HabDobraPF",		    "V/F",	    &VarPar1.HabDobraPF,		NIVEL_SUPER,	BYTE,	"%-1.0f",	0.0,	 1.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "LadoDobraPF",		"0-A/1-B",	&VarPar1.LadoDobraPF,		NIVEL_SUPER,	BYTE,	"%-1.0f",	0.0,	 1.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "NumDobraPF",			"",			&VarPar1.NumDobraPF,		NIVEL_SUPER,	BYTE,	"%-1.0f",	0.0,	 5.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "HabOverPadrao",	    "V/F",	    &VarPar1.HabOverPadrao,		NIVEL_SUPER,	BYTE,	"%-1.0f",	0.0,	 1.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "CoefAngOver",		"MiOhm/h",	&VarPar1.CoefAngOver,		NIVEL_SUPER,	FLOAT,	"%-5.2f",	-5.0,	 5.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "CoefCorrOver",		"",			&VarPar1.CoefCorrOver,		NIVEL_SUPER,	FLOAT,	"%-5.2f",	-1.0,	 1.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "NCicOverPadrao",		"",			&VarPar1.NCicOverPadrao,	NIVEL_SUPER,	BYTE,	"%-2.0f",	0.0,	 20.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "NCicNormPadrao",		"",			&VarPar1.NCicNormPadrao,	NIVEL_SUPER,	BYTE,	"%-2.0f",	0.0,	 20.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "NCicUnderPadrao",	"",			&VarPar1.NCicUnderPadrao,	NIVEL_SUPER,	BYTE,	"%-2.0f",	0.0,	 20.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "CoefAngUnder",		"MiOhm/h",	&VarPar1.CoefAngUnder,		NIVEL_SUPER,	FLOAT,	"%-5.2f",	-5.0,	 5.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "CoefCorrUnder",		"",			&VarPar1.CoefCorrUnder,		NIVEL_SUPER,	FLOAT,	"%-5.2f",	-1.0,	 1.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  

  "CONF. PF/BARRA",	"",	NULL, NIVEL_SUPER, FLOAT,	"%-5.2f", 0.0,  0.0, 1.0,	TITULO_1,  AT, "", "",	G0,
  "MinIntervPF",	    "seg",		&VarPar1.MinIntervPF,		NIVEL_SUPER,	LONG,	"%-4.0f",	0.0,	9999.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
/* -- alteracao - Inicio - Robson - 05/10/2000 - PF novo CBA -- */
  "TempoAvanco",		"Ticks",	&VarPar1.TempoAvanco,		NIVEL_SUPER,	SHORT_INT, "%-3.0f",0.0,    600.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "TempoInterv",		"Ticks",	&VarPar1.TempoInterv,		NIVEL_SUPER,	SHORT_INT, "%-3.0f",0.0,    600.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "TempoRecuo",			"Ticks",	&VarPar1.TempoRecuo,		NIVEL_SUPER,	SHORT_INT, "%-3.0f",0.0,    600.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "TempoCadFalta",		"seg",		&VarPar1.TempoCadFalta,		NIVEL_SUPER,	SHORT_INT, "%-5.1f",0.0,    999.9,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
/* Alteracao - Robson - Inicio - 23/07/02 - Tempos quebrador/alimentador independente - */
  "TempoQueb 1",		"seg",		&VarPar1.TempoQuebrador[0],	 NIVEL_SUPER,	FLOAT, "%-4.1f",0.0,    100.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "TempoAlim 1",		"seg",		&VarPar1.TempoAlimentador[0],NIVEL_SUPER,	FLOAT, "%-4.1f",0.0,    100.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "TempoQueb 2",		"seg",		&VarPar1.TempoQuebrador[1],	 NIVEL_SUPER,	FLOAT, "%-4.1f",0.0,    100.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "TempoAlim 2",		"seg",		&VarPar1.TempoAlimentador[1],NIVEL_SUPER,	FLOAT, "%-4.1f",0.0,    100.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "TempoQueb 3",		"seg",		&VarPar1.TempoQuebrador[2],  NIVEL_SUPER,	FLOAT, "%-4.1f",0.0,    100.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "TempoAlim 3",		"seg",		&VarPar1.TempoAlimentador[2],NIVEL_SUPER,	FLOAT, "%-4.1f",0.0,    100.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "TempoQueb 4",		"seg",		&VarPar1.TempoQuebrador[3],	 NIVEL_SUPER,	FLOAT, "%-4.1f",0.0,    100.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "TempoAlim 4",		"seg",		&VarPar1.TempoAlimentador[3],NIVEL_SUPER,	FLOAT, "%-4.1f",0.0,    100.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
/* Alteracao - Robson - Fim - 23/07/02 - Tempos quebrador/alimentador independente - */
  "TempoEspera",		"seg",		&VarPar1.TempoEspera,		NIVEL_SUPER,	FLOAT, "%-4.1f",0.0,    100.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "HAB PF QUEB/ALIM",	"",	NULL, NIVEL_OPER, FLOAT,	"%-5.2f", 0.0,  0.0, 1.0,	TITULO_1,  AT, "", "",	G0,
  "Queb 1",		"V/F",		&VarPar1.HabQueb[0],		NIVEL_OPER,	BYTE, "%1.0f",0.0,    1.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "Queb 2",		"V/F",		&VarPar1.HabQueb[1],		NIVEL_OPER,	BYTE, "%1.0f",0.0,    1.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "Queb 3",		"V/F",		&VarPar1.HabQueb[2],		NIVEL_OPER,	BYTE, "%1.0f",0.0,    1.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "Queb 4",		"V/F",		&VarPar1.HabQueb[3],		NIVEL_OPER,	BYTE, "%1.0f",0.0,    1.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "Alim 1",		"V/F",		&VarPar1.HabAlim[0],		NIVEL_OPER,	BYTE, "%1.0f",0.0,    1.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "Alim 2",		"V/F",		&VarPar1.HabAlim[1],		NIVEL_OPER,	BYTE, "%1.0f",0.0,    1.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "Alim 3",		"V/F",		&VarPar1.HabAlim[2],		NIVEL_OPER,	BYTE, "%1.0f",0.0,    1.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "Alim 4",		"V/F",		&VarPar1.HabAlim[3],		NIVEL_OPER,	BYTE, "%1.0f",0.0,    1.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "SEQUENCIA QUEBRA PF","",	NULL, NIVEL_SUPER, FLOAT,	"%-5.2f", 0.0,  0.0, 1.0,	TITULO_1,  AT, "", "",	G0,
  "Passo 1",			"Conj",		&VarPar1.Sequencia[0],		NIVEL_SUPER,	BYTE, "%1.0f",0.0,    4.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "Passo 2",			"Conj",		&VarPar1.Sequencia[1],		NIVEL_SUPER,	BYTE, "%1.0f",0.0,    4.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "Passo 3",			"Conj",		&VarPar1.Sequencia[2],		NIVEL_SUPER,	BYTE, "%1.0f",0.0,    4.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "Passo 4",			"Conj",		&VarPar1.Sequencia[3],		NIVEL_SUPER,	BYTE, "%1.0f",0.0,    4.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
/* -- alteracao - Fim - Robson - 05/10/2000 - PF novo CBA -- */
/* -- Alteracao - Inicio - 04/06/2002 - Leonel - cadencia de EA na remota -- */
/* ATENCAO - estes parametros sao gravados na remota da sala 125ka! Nao aumentar limite maximo sem verificar implicacoes no firmware da atn8 */
  "EA REMOTA OFFLINE","",	NULL, NIVEL_SUPER, FLOAT,	"%-5.2f", 0.0,  0.0, 1.0,	TITULO_1,  AT, "", "",	G0,
  "CadenciaEARemota",	"seg",		&VarPar1.CadenciaEARemota,	NIVEL_SUPER,	SHORT_INT, "%4.0f",0.0,   9999.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "TempoFimAEARemota",	"min",		&VarPar1.TempoFimAEARemota,	NIVEL_SUPER,	BYTE, 	   "%3.0f",0.0,    255.0,   1.0,	PAR_CUBAS,	AT, "", "",	G0,
/* -- Alteracao - Fim - 04/06/2002 - Leonel - cadencia de EA na remota -- */

  "QUEB. PREV.",		"",			NULL,						NIVEL_CONFIG_0,	FLOAT,	"%-5.2f",	0.0,  	 0.0,	1.0,	TITULO_1, AT, "", "",	G0,
  "HabQPrev", 			"V/F",		&VarPar1.HabQPrev,			NIVEL_CONFIG_0,	BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS,	AT, "", "",	G0,
  "LimInfQPrevEa",		"Min",		&VarPar1.LimInfQPrevEa,		NIVEL_CONFIG_0,	SHORT_INT, "%-4.0f", 0.0,  5760.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "LimSupQPrevEa",		"Min",		&VarPar1.LimSupQPrevEa,		NIVEL_CONFIG_0,	SHORT_INT, "%-4.0f", 0.0,  5760.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "MaxQPrevEa",			"",			&VarPar1.MaxQPrevEa,		NIVEL_CONFIG_0,	SHORT_INT, "%-3.0f", 0.0,  96.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "NHorRefQPrev",		"Min",		&VarPar1.NHorRefQPrev,		NIVEL_CONFIG_0,	SHORT_INT, "%-4.0f", 0.0,  5760.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "IntMinQQPrev",		"Min",		&VarPar1.IntMinQQPrev,		NIVEL_CONFIG_0,	SHORT_INT, "%-4.0f", 0.0,  5760.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "UsaRLent", 			"V/F",		&VarPar1.UsaRLent,			NIVEL_CONFIG_0,	BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS,	AT, "", "",	G0,
  "UsaRRap", 			"V/F",		&VarPar1.UsaRRap,			NIVEL_CONFIG_0,	BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS,	AT, "", "",	G0,
  "UsaIncOpe", 			"V/F",		&VarPar1.UsaIncOpe,			NIVEL_CONFIG_0,	BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS,	AT, "", "",	G0,
  "UsaAtrasoEa", 		"V/F",		&VarPar1.UsaAtrasoEa,		NIVEL_CONFIG_0,	BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS,	AT, "", "",	G0,
  "UsaMaxEa", 			"V/F",		&VarPar1.UsaMaxEa,			NIVEL_CONFIG_0,	BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS,	AT, "", "",	G0,
  "UsaMaxAEK", 			"V/F",		&VarPar1.UsaMaxAEK,			NIVEL_CONFIG_0,	BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS,	AT, "", "",	G0,
  "LimQPrevEaAtraso",	"Min",		&VarPar1.LimQPrevEaAtraso,	NIVEL_CONFIG_0,	SHORT_INT, "%-4.0f", 0.0,  5760.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,

  "SOPRO ESPECIAL",		"",			NULL,						NIVEL_CONFIG_0,	FLOAT,	"%-5.2f",	0.0,  	 0.0,	1.0,	TITULO_1, AT, "", "",	G0,
  "HabSoproEspec", 		"V/F",		&VarPar1.HabSoproEspec,		NIVEL_CONFIG_0,	BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS,	AT, "", "",	G0,

  "LIM. MOVIMENTACAO",	"",			NULL,						NIVEL_SUPER,	FLOAT,	"%-5.2f",	0.0,  	 0.0,	1.0,	TITULO_1, AT, "", "",	G0,
  "HabLimMov",	 				"V/F",		&VarPar1.HabLimMov,					NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "NumMovConsec", 				"",			&VarPar1.NumMovConsec,				NIVEL_SUPER, BYTE,	"%-2.0f",   0.0,	18.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "GrupoMov", 					"",			&VarPar1.GrupoMov,					NIVEL_SUPER, BYTE,	"%-2.0f",   0.0,	16.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "HabContEficMov",				"0=Des,1=Hab", 	&VarPar1.HabContEficMov, 	NIVEL_SUPER, BYTE, 	"%-1.0f",   0.0,     1.0,   1.0,	PAR_CUBAS, AT, "", "", G0,
  "EficMovMin",					"%", 		&VarPar1.EficMovMin,  			NIVEL_SUPER, BYTE, 	"%-3.0f",   0.0,     100.0,  1.0,	PAR_CUBAS, AT, "", "", G0,

  "PREVISAO E. A.",				"",		NULL,	NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "HabPrevAc",			"V/F",		&VarPar1.HabPrevAc,			NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	  1.0,	1.0,	PAR_CUBAS, AT, "", "", G0,
  "EaPrevMinAc", 		"MiOhm/h",	&VarPar1.EaPrevMinAc,		NIVEL_SUPER, FLOAT,	"%-4.2f",   0.0,	2.0,   		1e6,    PAR_CUBAS, AT, "", "", G0,
  "EaPrevAc", 			"MiOhm/h2",	&VarPar1.EaPrevAc,			NIVEL_SUPER, FLOAT,	"%-4.2f",   0.0,	2.0,   		1e6,    PAR_CUBAS, AT, "", "", G0,
  "EaPrevCiclosAc", 		"1-5",	&VarPar1.EaPrevCiclosAc,	NIVEL_SUPER, BYTE,	"%-1.0f",   1.0,	5.0,   	1.0,    PAR_CUBAS, AT, "", "", G0,


/* -- Alteracao - Inicio - 11/12/2002 - Robson - tempo maximo de ruido invalido -- */
  "RUIDO INV.",		"",			NULL,						NIVEL_SUPER,	FLOAT,	"%-5.2f",	0.0,  	 0.0,	1.0,	TITULO_1, AT, "", "",	G0,
  "TMaxRuidoInv.",		"HH:MM",	&VarPar1.TFalhaRuido,		NIVEL_SUPER,	T_HORA, "%-5.0f", 0.0,  999999999.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
/* -- Alteracao - Fim - 11/12/2002 - Robson - tempo maximo de ruido invalido -- */

  "RUIDO",						"",		NULL,	NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "InibeRuiPosCorr",	"Horas",	&VarPar1.InibeRuiPosCorr,	NIVEL_CONFIG_0, BYTE,	"%-2.0i",	0.0,	24.0,	1.0,	PAR_CUBAS, AT, "", "", G0,

  "EFEITO ANODICO",				"",		NULL,	NIVEL_CONFIG_0, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "InibeIncQuebAtrasoEa","V/F",		&VarPar1.InibeIncQuebAtrasoEa, NIVEL_CONFIG_0,	BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS,	AT, "", "",	G0,

  "AUT. MANOBRA CRUZEIRO",		"",			NULL,						NIVEL_SUPER,	FLOAT,	"%-5.2f",	0.0,  	 0.0,	1.0,	TITULO_1, AT, "", "",	G0,
  "HabMCruzeiro", 		"V/F",		&VarPar1.HabMCruzeiro,		NIVEL_CONFIG_0,	BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS,	AT, "", "",	G0,
  "TMaxPermMCruzeiro",	"Min",		&VarPar1.TMaxPermMCruzeiro,	NIVEL_CONFIG_0,	SHORT_INT, "%-4.0f", 0.0,  180.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "IntervMinTPinos",			"HH:MM",	&VarPar1.IntervMinTPinos,			NIVEL_SUPER, T_HORA,	"%-5s",		0.0,	86340,	1.0,	PAR_CUBAS, AT, "", "", G0,
  NULL,	NULL, 0, 0, 0,	NULL, 0.0, 0.0, 0.0, 0, 0, NULL, NULL
};

/*--- Estrutura de descricao das variaveis de parametro 2 de usuario ---*/
t_par_var_log VarParUser2[] =
{
  "HabCalcCoefAC",		"V/F",		&VarPar2.HabCalcCoefAC,		NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "NCicCoefAng",		"",			&VarPar2.NCicCoefAng,		NIVEL_SUPER, BYTE,	"%-2.0f",	0.0,	 20.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "MinNCicCA",			"",			&VarPar2.MinNCicCA,			NIVEL_SUPER, BYTE,	"%-2.0f",	0.0,	 20.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "IntervCalcCA",		"",			&VarPar2.IntervCalcCA,		NIVEL_SUPER, BYTE,	"%-1.0f",	1.0,	 2.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "HabExcUsuPF",		"V/F",		&VarPar2.HabExcUsuPF,		NIVEL_CONFIG_0, BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS, AT, "", "", G0,

  "INCREMENTO PADRAO",	"",			NULL,		NIVEL_CONFIG_0,	FLOAT,	"%-5.2f",	0.0,  	 0.0,	1.0,	TITULO_1, AT, "", "",	G0,
  "TIncPadrao_1",		"1=C,2=R",	&VarPar2.TipoIncPadrao[0],	NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	2.0,   	1.0,   	PAR_CUBAS, AT, "", "", G0,
  "DurIncPadrao_1",		"min",		&VarPar2.DurIncPadrao[0],	NIVEL_SUPER, SHORT_INT,	"%-4.0f",   0.0,	1440.0,   	1.0,   	PAR_CUBAS, AT, "", "", G0,
  "VIncPadrao_1",		"mV",		&VarPar2.VIncPadrao[0],		NIVEL_SUPER, FLOAT,	"%-3.0f",   0.0,	300.0,   	1000.0,   	PAR_CUBAS, AT, "", "", G0,
  "TIncPadrao_2",		"1=C,2=R",	&VarPar2.TipoIncPadrao[1],	NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	2.0,   	1.0,   	PAR_CUBAS, AT, "", "", G0,
  "DurIncPadrao_2",		"min",		&VarPar2.DurIncPadrao[1],	NIVEL_SUPER, SHORT_INT,	"%-4.0f",   0.0,	1440.0,   	1.0,   	PAR_CUBAS, AT, "", "", G0,
  "VIncPadrao_2",		"mV",		&VarPar2.VIncPadrao[1],		NIVEL_SUPER, FLOAT,	"%-3.0f",   0.0,	300.0,   	1000.0,   	PAR_CUBAS, AT, "", "", G0,
  "TIncPadrao_3",		"1=C,2=R",	&VarPar2.TipoIncPadrao[2],	NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	2.0,   	1.0,   	PAR_CUBAS, AT, "", "", G0,
  "DurIncPadrao_3",		"min",		&VarPar2.DurIncPadrao[2],	NIVEL_SUPER, SHORT_INT,	"%-4.0f",   0.0,	1440.0,   	1.0,   	PAR_CUBAS, AT, "", "", G0,
  "VIncPadrao_3",		"mV",		&VarPar2.VIncPadrao[2],		NIVEL_SUPER, FLOAT,	"%-3.0f",   0.0,	300.0,   	1000.0,   	PAR_CUBAS, AT, "", "", G0,
  "TIncPadrao_4",		"1=C,2=R",	&VarPar2.TipoIncPadrao[3],	NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	2.0,   	1.0,   	PAR_CUBAS, AT, "", "", G0,
  "DurIncPadrao_4",		"min",		&VarPar2.DurIncPadrao[3],	NIVEL_SUPER, SHORT_INT,	"%-4.0f",   0.0,	1440.0,   	1.0,   	PAR_CUBAS, AT, "", "", G0,
  "VIncPadrao_4",		"mV",		&VarPar2.VIncPadrao[3],		NIVEL_SUPER, FLOAT,	"%-3.0f",   0.0,	300.0,   	1000.0,   	PAR_CUBAS, AT, "", "", G0,
  "TIncPadrao_5",		"1=C,2=R",	&VarPar2.TipoIncPadrao[4],	NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	2.0,   	1.0,   	PAR_CUBAS, AT, "", "", G0,
  "DurIncPadrao_5",		"min",		&VarPar2.DurIncPadrao[4],	NIVEL_SUPER, SHORT_INT,	"%-4.0f",   0.0,	1440.0,   	1.0,   	PAR_CUBAS, AT, "", "", G0,
  "VIncPadrao_5",		"mV",		&VarPar2.VIncPadrao[4],		NIVEL_SUPER, FLOAT,	"%-3.0f",   0.0,	300.0,   	1000.0,   	PAR_CUBAS, AT, "", "", G0,
  "TIncPadrao_6",		"1=C,2=R",	&VarPar2.TipoIncPadrao[5],	NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	2.0,   	1.0,   	PAR_CUBAS, AT, "", "", G0,
  "DurIncPadrao_6",		"min",		&VarPar2.DurIncPadrao[5],	NIVEL_SUPER, SHORT_INT,	"%-4.0f",   0.0,	1440.0,   	1.0,   	PAR_CUBAS, AT, "", "", G0,
  "VIncPadrao_6",		"mV",		&VarPar2.VIncPadrao[5],		NIVEL_SUPER, FLOAT,	"%-3.0f",   0.0,	300.0,   	1000.0,   	PAR_CUBAS, AT, "", "", G0,


  "OSCILACAO",			"",			NULL,		NIVEL_CONFIG_0,	FLOAT,	"%-5.2f",	0.0,  	 0.0,	1.0,	TITULO_1, AT, "", "",	G0,
  "HabIncOscil",		"V/F",		&VarPar2.HabIncOscil,		NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "NCCOscil",			"",			&VarPar2.NCCOscil,			NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	5.0,   	1.0,   	PAR_CUBAS, AT, "", "", G0,
  "NCRegOscil",			"",			&VarPar2.NCRegOscil,		NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	6.0,   	1.0,   	PAR_CUBAS, AT, "", "", G0,
  "IncOscilFra", 		"mV",		&VarPar2.IncOscilFra,		NIVEL_SUPER, FLOAT,	"%-3.0f",   0.0,	300.0,   	1000.0,	PAR_CUBAS, AT, "", "", G0,
  "IncOscilFor", 		"mV",		&VarPar2.IncOscilFor,		NIVEL_SUPER, FLOAT,	"%-3.0f",   0.0,	300.0,   	1000.0,	PAR_CUBAS, AT, "", "", G0,
  "DecrOscil", 			"mV",		&VarPar2.DecrOscil,			NIVEL_SUPER, FLOAT,	"%-3.0f",   0.0,	300.0,   	1000.0,	PAR_CUBAS, AT, "", "", G0,
  "MaxIncOscil", 		"mV",		&VarPar2.MaxIncOscil,		NIVEL_SUPER, FLOAT,	"%-3.0f",   0.0,	500.0,   	1000.0,	PAR_CUBAS, AT, "", "", G0,
  "LimOscilFrac", 		"MiOhm",	&VarPar2.LimOscilFrac,		NIVEL_SUPER, FLOAT,	"%-4.2f",   0.0,	2.0,   		1e6,    PAR_CUBAS, AT, "", "", G0,
  "LimOscilFort", 		"MiOhm",	&VarPar2.LimOscilFort,		NIVEL_SUPER, FLOAT,	"%-4.2f",   0.0,	2.0,   		1e6,    PAR_CUBAS, AT, "", "", G0,

  "SODERBERG FUTURO",		"",			NULL,						NIVEL_SUPER,	FLOAT,	"%-5.2f",	0.0,  	 0.0,	1.0,	TITULO_1, AT, "", "",	G0,

  "HabilitaPFCBA",		"V/F",		&VarPar2.HabilitaPFCBA,		NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TSuspTemp",			"min",		&VarPar2.TSuspTemp,			NIVEL_SUPER, SHORT_INT,	"%-3.0f",   0.0,	 180.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TMinBaseF",			"min",		&VarPar2.TMinBaseF,			NIVEL_SUPER, SHORT_INT,	"%-3.0f",   0.0,	 180.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TOverF",				"min",		&VarPar2.TOverF,			NIVEL_SUPER, SHORT_INT,	"%-3.0f",   0.0,	 180.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TOverCorr",			"min",		&VarPar2.TOverCorr,			NIVEL_SUPER, SHORT_INT,	"%-3.0f",   0.0,	 180.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TMaxUnderA",			"min",		&VarPar2.TMaxUnderA,		NIVEL_SUPER, SHORT_INT,	"%-3.0f",   0.0,	 180.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TMaxUnderB",			"min",		&VarPar2.TMaxUnderB,		NIVEL_SUPER, SHORT_INT,	"%-3.0f",   0.0,	 180.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TMinOverEA",			"min",		&VarPar2.TMinOverEA,		NIVEL_SUPER, BYTE,	"%-3.0f",   0.0,	 180.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "SOverInicial",		"V/F",		&VarPar2.SOverInicial,		NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TaxaOverA",				"",		&VarPar2.TaxaOverA,			NIVEL_SUPER, FLOAT,	"%-4.2f",   0.0,	 3.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TaxaOverB",				"",		&VarPar2.TaxaOverB,			NIVEL_SUPER, FLOAT,	"%-4.2f",   0.0,	 3.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TaxaUnderA",				"",		&VarPar2.TaxaUnderA,		NIVEL_SUPER, FLOAT,	"%-4.2f",   0.0,	 1.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TaxaUnderB",				"",		&VarPar2.TaxaUnderB,		NIVEL_SUPER, FLOAT,	"%-4.2f",   0.0,	 1.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "SuspEA",				"V/F",		&VarPar2.SuspEA,			NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "CAFimUnder",		"nOhm/min",		&VarPar2.CAFimUnder,		NIVEL_SUPER, FLOAT,	"%-5.2f",	-5.0,	 20.0,	1e3,	PAR_CUBAS,	AT, "", "",	G0,
  "CCFimUnder",				"",		&VarPar2.CCFimUnder,		NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	 1.0,	1.0,	PAR_CUBAS,	AT, "", "",	G0,
  "DifResFimUnder",	   "MiOhm",		&VarPar2.DifResFimUnder,	NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	 3.0,	1e6,	PAR_CUBAS,	AT, "", "",	G0,
  "DeltaRFimCheck",	   "MiOhm",		&VarPar2.DeltaRFimCheck,	NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	 3.0,	1e6,	PAR_CUBAS,	AT, "", "",	G0,
  "TSOverInicial",		"min",		&VarPar2.TSOverInicial,		NIVEL_SUPER, SHORT_INT,	"%-3.0f",   0.0,	 180.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TLibMovOver",		"min",		&VarPar2.TLibMovOver,		NIVEL_SUPER, SHORT_INT,	"%-3.0f",   0.0,	 180.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TInibMovUnder",		"min",		&VarPar2.TInibMovUnder,		NIVEL_SUPER, SHORT_INT,	"%-3.0f",   0.0,	 180.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TLibMovUnderB",		"min",		&VarPar2.TLibMovUnderB,		NIVEL_SUPER, SHORT_INT,	"%-3.0f",   0.0,	 180.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "BitDuploOver",	"0-Desat.",		&VarPar2.BitDuploOver,		NIVEL_SUPER, BYTE,	"%-2.0f",   0.0,	 30.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TAlarmeCheck",		"min",		&VarPar2.TAlarmeCheck,		NIVEL_SUPER, BYTE,	"%-3.0f",   0.0,	 180.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TLibAlarmeOver",		"min",		&VarPar2.TLibAlarmeOver,	NIVEL_SUPER, BYTE,	"%-3.0f",   0.0,	 180.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TendMaxOver",	   "PiOhm",		&VarPar2.TendMaxOver,		NIVEL_SUPER, FLOAT,	"%-5.2f",	-10.0,	 1.0,	1e9,	PAR_CUBAS,	AT, "", "",	G0,

  "CAMISA PF",		"",			NULL,						NIVEL_SUPER,	FLOAT,	"%-5.2f",	0.0,  	 0.0,	1.0,	TITULO_1, AT, "", "",	G0,
  "CamisaPFAuto",		"V/F",		&VarPar2.CamisaPFAuto,		NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TMaxAjCamPF",		"min",		&VarPar2.TMaxAjCamPF,		NIVEL_SUPER, LONG,	"%-3.0f",   0.0,	 999.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TMovCamPF",			"seg",		&VarPar2.TMovCamPF,			NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	 5.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "NMaxMovCamPF",		"",			&VarPar2.NMaxMovCamPF,		NIVEL_SUPER, BYTE,	"%-2.0f",   0.0,	 20.0,   1.0,    PAR_CUBAS, AT, "", "", G0,


  "AEK PF",					"",		NULL,								NIVEL_SUPER,	FLOAT,	"%-5.2f",	0.0,  	 0.0,	1.0,	TITULO_1, AT, "", "",	G0,
  "HabAEKPF",			"V/F",		&VarPar2.HabAEKPF,			NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TaxaOverAEK",			"",		&VarPar2.TaxaOverAEK,		NIVEL_SUPER, FLOAT,	"%-4.2f",   0.0,	 5.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TMovCimaAEKPF",		"seg",		&VarPar2.TMovCimaAEKPF,		NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	 5.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TMovBaixoAEKPF",		"seg",		&VarPar2.TMovBaixoAEKPF,	NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	 5.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "MaxDeltaTBaixo",		"seg",		&VarPar2.MaxDeltaTBaixo,	NIVEL_SUPER, BYTE,	"%-2.0f",   0.0,	 20.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "IntMovCimaAEKPF",	"seg",		&VarPar2.IntMovCimaAEKPF,	NIVEL_SUPER, BYTE,	"%-2.0f",   0.0,	 60.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "IntMovBaixoAEKPF",	"seg",		&VarPar2.IntMovBaixoAEKPF,	NIVEL_SUPER, BYTE,	"%-2.0f",   0.0,	 60.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TIniAlimAEK",		"seg",		&VarPar2.TIniAlimAEK,		NIVEL_SUPER, BYTE,	"%-3.0f",   0.0,	 120.0,   1.0,    PAR_CUBAS, AT, "", "", G0,

  "INIBICAO INCREMENTOS",		"",			NULL,						NIVEL_SUPER,	FLOAT,	"%-5.2f",	0.0,  	 0.0,	1.0,	TITULO_1, AT, "", "",	G0,

  "TempMaxInibInc",		"�C",		&VarPar2.TempMaxInibInc,	NIVEL_SUPER, FLOAT,	"%-3.0f",   0.0,	 999.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "InibIncRRTemp",		"V/F",		&VarPar2.InibIncRRTemp,		NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "InibIncQuebTemp",	"V/F",		&VarPar2.InibIncQuebTemp,	NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "InibIncTpTemp",		"V/F",		&VarPar2.InibIncTpTemp,		NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "InibIncOpTemp",		"V/F",		&VarPar2.InibIncOpTemp,		NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "InibIncQuebDB",  	"V/F",		&VarPar2.InibIncQuebDB,	NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
    
  "PROV QUEB",		"",			NULL,						NIVEL_SUPER,	FLOAT,	"%-5.2f",	0.0,  	 0.0,	1.0,	TITULO_1, AT, "", "",	G0,
  "HabProvQueb",  	"V/F",		&VarPar2.HabProvQueb,	NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "NivelProvQueb",      "MiOhm/h2",    &VarPar1.NivelProvQueb,     NIVEL_SUPER, FLOAT, "%-6.3f",   -9.0,   10.0,   1e6,    PAR_CUBAS, AT, "", "", G0,
  "BufferSizeRH",   "",   &VarPar2.BufferSizeRH,  NIVEL_SUPER,  BYTE,	"%-2.0i",   5.0,	 30.0,   1.0,    PAR_CUBAS, AT, "", "", G0,  

  "QUEB. PREV. 2",		"",			NULL,						NIVEL_CONFIG_0,	FLOAT,	"%-5.2f",	0.0,  	 0.0,	1.0,	TITULO_1, AT, "", "",	G0,
  "UsaMaxAEK", 			"V/F",		&VarPar12UsaMaxAEK,			NIVEL_CONFIG_0,	BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS,	AT, "", "",	G0,
  "HabInibeQPposDB",  	"V/F",		&VarPar2.HabInibeQPposDB,	NIVEL_SUPER, BYTE,	"%-1.0f",   0.0,	 1.0,   1.0,    PAR_CUBAS, AT, "", "", G0,
  "TInibQPposDB",		"HH:MM",	&VarPar2.TInibQPposDB,		NIVEL_SUPER, T_HORA,	"%-5s",		0.0,	86340,	1.0,	PAR_CUBAS, AT, "", "", G0,

  NULL,	NULL, 0, 0, 0,	NULL, 0.0, 0.0, 0.0, 0, 0, NULL, NULL
};

/*--- Estrutura de descricao das variaveis trabalho 1 de usuario ---*/
t_par_var_log VarUser1Avc[] =
{
  "ALIMENT. - TRABALHO",	"",		NULL,	NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,  0.0,	1.0,	TITULO_2,  AT, "", "", G9,
  "EstAlimAtual",			"",		&VarUser1.EstadoAlimAtual,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	9.0,		1.0,	REL_CUBAS orb OPC_R,	AT, "", "",	G9,
  "EstAlimAnt",				"",		&VarUser1.EstadoAlimAnt,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	9.0,		1.0,	REL_CUBAS orb OPC_R,	AT, "", "",	G9,
  "IniAlgAtual",			"",		&VarUser1.InicioAlgAtual,	NIVEL_SUPER, BYTE,	"%-1.0f",	0.0,	9.0,		1.0,	REL_CUBAS orb OPC_R,	AT, "", "",	G9,
  "State",					"",		&VarUser1.State,			NIVEL_SUPER, BYTE,	"%-2.0f",	0.0, 	99.0,		1.0,	REL_CUBAS orb OPC_R,  AT, "", "",	G9,
  "PrevState",				"",		&VarUser1.PrevState,		NIVEL_SUPER, BYTE,	"%-2.0f",	0.0, 	99.0,		1.0,	REL_CUBAS orb OPC_R,  AT, "", "",	G9,
  "TempEstAtual",			"seg",	&VarUser1.TempEstAtual,		NIVEL_SUPER, INT,	"%-6.0f",	0.0, 999999.0,		1.0,	REL_CUBAS orb OPC_R,	AT, "", "",	G9,
  "QtAlimEstAtual",			"Kg",	&VarUser1.QtAAlimEstAtual,	NIVEL_SUPER, FLOAT,	"%-6.0f",	0.0, 999999.0,		1.0,	REL_CUBAS orb OPC_R,	AT, "", "",	G9,
  "FornecSubEst",			"Kg",	&VarUser1.FornecSubEst, 	NIVEL_SUPER, FLOAT,	"%-6.0f",	0.0, 999999.0,		1.0,	REL_CUBAS orb OPC_R,	AT, "", "",	G9,
  "ConsumoSubEst",			"Kg",	&VarUser1.ConsumoSubEst,	NIVEL_SUPER, FLOAT,	"%-6.0f",	0.0, 999999.0,		1.0,	REL_CUBAS orb OPC_R,	AT, "", "",	G9,
  "QuebSubEst",				"",		&VarUser1.QuebSubEst,		NIVEL_SUPER, INT,	"%-4.0f",	0.0, 9999.0,		1.0,	REL_CUBAS orb OPC_R,	AT, "", "",	G9,
  "NumQueb",				"",		&VarUser1.NumQueb,			NIVEL_SUPER, INT,	"%-4.0f",	0.0, 9999.0,		1.0,	REL_CUBAS orb OPC_R,	AT, "", "",	G9,
  "InicioState",			"",		&VarUser1.InicioSubEst,		NIVEL_SUPER, BYTE,	"%-1.0f",	0.0, 	1.0,		1.0,	REL_CUBAS orb OPC_R,	AT, "", "",	G9,
  "IntervCurr",			"A*s",		&VarUser1.IntervCurr,		NIVEL_SUPER, FLOAT,	"%-8.0f",	0.0, 999999.0,		1.0,	REL_CUBAS orb OPC_R,	AT, "", "",	G9,
  "EfiCurr",				"%",	&VarUser1.EfiCurr,			NIVEL_SUPER, FLOAT,	"%-3.0f",	0.0, 100.0,			1e2,	REL_CUBAS orb OPC_R,	AT, "", "",	G9,
  "Integral",			"KA*s",		&VarUser1.Integral,			NIVEL_SUPER, FLOAT,	"%-9.0f",	0.0, 999999.0,		1e-3,	REL_CUBAS orb OPC_R,	AT, "", "",	G9,
  "NumAciona",				"",		&VarUser1.NumAciona,		NIVEL_SUPER, INT,	"%-6.0f",	0.0, 999999.0,		1.0,	REL_CUBAS orb OPC_R,	AT, "", "",	G9,
  "ConcCheckAnt",			"%",	&VarUser1.ConcCheckAnt,		NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0, 	100.0,		1e2,	REL_CUBAS orb OPC_R,	AT, "", "",	G9,
  "ConcCheckAtual",			"%",	&VarUser1.ConcCheckAtual,	NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0, 	100.0,		1e2,	REL_CUBAS orb OPC_R,	AT, "", "",	G9,
  "ResAlim",			"MiOhm",	&VarUser1.ResAlim,			NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0, 	30.0,		1e6,	REL_CUBAS orb OPC_R,  AT, "", "",	G9,
  "DerResAlim",			"MiOhm/%",	&VarUser1.DerResAlim,		NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0, 	30.0,		1.0,	REL_CUBAS orb OPC_R,  AT, "", "",	G9,
  "NumOverCheck",			"",		&VarUser1.NumOverCheck,		NIVEL_SUPER, SHORT_INT,"%-2.0f",0.0, 	99.0,		1.0,	REL_CUBAS orb OPC_R,	AT, "", "",	G9,
  "CAMISA - TRABALHO",		"",		NULL,						NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,  0.0,	1.0,	TITULO_2,  AT, "", "", G9,
  "ContTAjCam",				"Seg",	&VarUser1.ContTAjCam,		NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0, 999999.0,		1.0,	REL_CUBAS,	AT, "", "",	G9,
  "ContTAjAcum",			"Seg",	&VarUser1.ContTAjAcum,		NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0, 999999.0,		1.0,	REL_CUBAS,	AT, "", "",	G9,
  "ContInibAjCam",			"Seg",	&VarUser1.ContInibAjCam,	NIVEL_SUPER, INT,	"%-6.0f",	0.0, 999999.0,		1.0,	REL_CUBAS,	AT, "", "",	G9,
  "QUEB. PREV. - TRAB.",	"",		NULL,	NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,  0.0,	1.0,	TITULO_2,  AT, "", "", G9,
  "NumQuebPrev",			"",		&VarUser1.NumQuebPrev,		NIVEL_SUPER, SHORT_INT,	"%-4.0f",	0.0, 9999.0,		1.0,	REL_CUBAS,	AT, "", "",	G9,
  "NumPrevQPrev",			"",		&VarUser1.NumPrevQPrev,		NIVEL_SUPER, SHORT_INT,	"%-4.0f",	0.0, 9999.0,		1.0,	REL_CUBAS orb OPC_R,	AT, "", "",	G9,
  "ContDurQPrev",		"Seg",		&VarUser1.ContDurQPrev,		NIVEL_SUPER, LONG,		"%-8.0f",	0.0, 99999999.0,	1.0,	REL_CUBAS,	AT, "", "",	G9,
  "ContInibQPrev",		"Seg",		&VarUser1.ContInibQPrev,	NIVEL_SUPER, INT,		"%-8.0f",	0.0, 99999999.0,	1.0,	REL_CUBAS,	AT, "", "",	G9,
  "PassoCadencia",		"",			&VarUser1.PassoCadencia,	NIVEL_SUPER, BYTE,		"%-2.0f",	0.0, 99.0,		1.0,	REL_CUBAS,	AT, "PassoC", "Debug1",	G9,
  "RrapCContValp",		"MiOhm",	&VarUser1.RrapCContValp,	NIVEL_SUPER, FLOAT,		"%-7.2f",	0.0,	999.0,	1.0,	TODAS_T, AT, "", "", G5,
  "RlentCContValp",		"MiOhm",	&VarUser1.RlentCContValp,	NIVEL_SUPER, FLOAT,		"%-7.2f",	0.0,	999.0,	1.0,	TODAS_T, AT, "", "", G5,
  "BandaSupMovel",		"MiOhm",	&VarUser1.BandaSupMovel,	NIVEL_SUPER, FLOAT,		"%-5.3f",	0.0,	20.0,	1e6,	TODAS_T, AT, "", "", G5,
  "EqMotorCorrB",		 "nOhm",	&VarUser1.EqMotorCorrB,		NIVEL_SUPER, FLOAT,		"%-7.3f",	0.0,	9999.0,	1e9,	TODAS_T, AT, "", "", G5,
  "NQueb",		 		 	 "",	&VarUser1.NumQuebProg,		NIVEL_SUPER,  BYTE,		"%-2.0f",	0.0,	99.0,	1.0,	TODAS_T, AT, "", "", G5,
  "StatusEv",		 	 	 "",	&VarUser1.StatusEv,			NIVEL_SUPER,  INT,		"%-10.0f",	0.0,	9999999999.0,	1.0,	REL_CUBAS orb OPC_R, AT, "", "", G5,
  "CoefAngDeriv",		 	 	 "",	&VarUser1.CoefAngDeriv,			NIVEL_SUPER,  FLOAT,		"%-6.3f",	-9.0,	10.0,	1e6,	TODAS_T orb OPC_R, AT, "", "", G3,
	

  NULL,	NULL, 0, 0, 0,	NULL, 0.0, 0.0, 0.0, 0, 0, NULL, NULL
};

/*--- Estrutura de descricao das variaveis trabalho 2 de usuario ---*/
t_par_var_log VarUser2Avc[] =
{
  "PF - STATUS OPER.",			"",		NULL,					NIVEL_SUPER,	FLOAT,	"%-5.2f",	0.0,	0.0,		1.0,	TITULO_2,  AT, "", "", G9,
  "Alimentador 1",			"V/F",&VarUser2.HabAlimOp[0],	NIVEL_CONFIG_0,  	BYTE,	"%-1.0f",	0.0,	10.0,		1,	REL_CUBAS,	AT, "", "", G0,
  "Alimentador 2",			"V/F",&VarUser2.HabAlimOp[1],	NIVEL_CONFIG_0,  	BYTE,	"%-1.0f",	0.0,	10.0,		1,	REL_CUBAS,	AT, "", "", G0,
  "Alimentador 3",			"V/F",&VarUser2.HabAlimOp[2],	NIVEL_CONFIG_0,  	BYTE,	"%-1.0f",	0.0,	10.0,		1,	REL_CUBAS,	AT, "", "", G0,
  "Alimentador 4",			"V/F",&VarUser2.HabAlimOp[3],	NIVEL_CONFIG_0,  	BYTE,	"%-1.0f",	0.0,	10.0,		1,	REL_CUBAS,	AT, "", "", G0,
  "Quebrador 1",			"V/F",&VarUser2.HabQuebOp[0],	NIVEL_CONFIG_0,  	BYTE,	"%-1.0f",	0.0,	10.0,		1,	REL_CUBAS,	AT, "", "", G0,
  "Quebrador 2",			"V/F",&VarUser2.HabQuebOp[1],	NIVEL_CONFIG_0,  	BYTE,	"%-1.0f",	0.0,	10.0,		1,	REL_CUBAS,	AT, "", "", G0,
  "Quebrador 3",			"V/F",&VarUser2.HabQuebOp[2],	NIVEL_CONFIG_0,  	BYTE,	"%-1.0f",	0.0,	10.0,		1,	REL_CUBAS,	AT, "", "", G0,
  "Quebrador 4",			"V/F",&VarUser2.HabQuebOp[3],	NIVEL_CONFIG_0,  	BYTE,	"%-1.0f",	0.0,	10.0,		1,	REL_CUBAS,	AT, "", "", G0,

  "RInstATNCA",		"",		&VarUser2.Rinst_atnca,			NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G1,
  "R2mATNCA",		"",		&VarUser2.Res_2m_atnca,			NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G1,
  "VRlentCcontl",		"mV",	&VarUser2.VRLentCCont,		NIVEL_SUPER, SHORT_INT,	"%-6.0f",	0.0,	999.0,	1,	TODAS_T, AT, "", "", G2,
  "VRrapCcontl",		"mV",	&VarUser2.VRRapCCont,		NIVEL_SUPER, SHORT_INT,	"%-6.0f",	0.0,	999.0,	1,	TODAS_T, AT, "", "", G2,
  "SigmaShort",			"MiOhm",	&VarUser2.SigmaS_2m,	NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G5,
  "SigmaLong",			"MiOhm",	&VarUser2.SigmaL_2m,	NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T, AT, "", "", G5,
  "DerivHTeste",		"MiOhm/h",&VarUser2.DerivHTeste,	NIVEL_SUPER, FLOAT,	"%-6.2f",	0.0,	100.0,	1e6,	TODAS_T orb OPC_R, AT, "", "", G4,
  "CoefAng",			"nOhm/h",&VarUser2.CoefAng,		NIVEL_SUPER, FLOAT,	"%-6.2f",	-9999.0,	9999.0,	1e3,	TODAS_T orb OPC_R, AT, "", "", G4,
  "CoefCor",			"MiOhm/h",&VarUser2.CoefCor,		NIVEL_SUPER, FLOAT,	"%-6.2f",	-9999.0,	9999.0,	1,	TODAS_T orb OPC_R, AT, "CoefCor", "Status2", G4,
  "OscilacaoH",			"MiOhm",	&VarUser2.Oscilacao,	NIVEL_SUPER, FLOAT,	"%-7.2f",	0.0,	100.0,	1e6,	TODAS_T orb OPC_R, AT, "Oscil", "Ruido5", G5,
  "TaxaFeedPF",		 	 "",	&VarUser2.TaxaFeedPF,	NIVEL_SUPER, FLOAT,	"%-4.1f",	-1.0,	99.0,	1.0,	TODAS_T orb OPC_R, AT, "TaxaPF", "Status11", G5,
  "EstadoPFCBA",		 "",	&VarUser2.EstadoPFCBA,	NIVEL_SUPER, SHORT_INT,	"%-1.0f",	-3.0,	10.0,	1.0,	TODAS_T orb OPC_R, AT, "EstPF", "Status10", G5,
  "HoraUltQuebCab",	"",		&VarUser2.HoraUltQuebCab,		NIVEL_SUPER, LONG,	"%-7.0f",	0.0,	100.0,	1.0,	TODAS_T, AT, "", "", G1,  
  "HoraForaDB",			"HH:MM",	&VarUser2.HoraForaDB,		NIVEL_SUPER, T_HORA,	"%-5s",		0.0,	86340,	1.0,	PAR_CUBAS, AT, "", "", G3,




  NULL,	NULL, 0, 0, 0,	NULL, 0.0, 0.0, 0.0, 0, 0, NULL, NULL
};

/*--- Estrutura de descricao das variaveis trabalho 3 de usuario ---*/
t_par_var_log VarUser3Avc[] =
{
  "TempPI",		 	 "",	&VarUser3.Temperatura,	NIVEL_SUPER, FLOAT,	"%-5.1f",	0.0,	9999.0,	1.0,	TODAS_T orb OPC_RW, AT, "Temp", "Status7", G5,
  "FatorPF",		 "",	&VarUser3.FatorFeedRate,NIVEL_SUPER, FLOAT,	"%-4.1f",	0.0,	2.0,	1.0,	TODAS_T, AT, "FatorPF", "Status9", G5,
  "TendResOver",	 "",	&VarUser3.TendResOver,	NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	2.0,	1e9,	TODAS_T, AT, "", "", G9,

  NULL,	NULL, 0, 0, 0,	NULL, 0.0, 0.0, 0.0, 0, 0, NULL, NULL
};

/*--- Estrutura de descricao das variaveis trabalho 4 de usuario ---*/
t_par_var_log VarUser4Avc[] =
{
  NULL,	NULL, 0, 0, 0,	NULL, 0.0, 0.0, 0.0, 0, 0, NULL, NULL
};

/*--- Estrutura de descricao das variaveis MUX ---*/
t_par_var_log VarConverMUX[] =
{
/* -- Alteracao - Inicio - 14/02/2001 - Carlos/Leonel - tratamento para cba sala 86ka -- */
 #ifdef	USA_ATN8
  "INDICE SCORE",  			"",    NULL,  	NIVEL_SUPER, FLOAT, "%-8.2f",	0.0,  0.0,   1.0, TITULO_1,    AT, "", "", G0,
  "IndCuba",      				"",       	&VarConvMUX.IndSad,      			NIVEL_SUPER, SHORT_INT, "%-3.0f",	0.0,  300.0, 	1.0, REL_CUBAS, AT, "", "", G0,
 #else
  "CALIBRACAO A/D CUBAS",  			"",    NULL,  	NIVEL_SUPER, FLOAT, "%-8.2f",	0.0,  0.0,   1.0, TITULO_1,    AT, "", "", G0,
  "IndSad",      				"",       	&VarConvMUX.IndSad,      			NIVEL_SUPER, SHORT_INT, "%-3.0f",	0.0,  300.0, 	1.0, REL_CUBAS, AT, "", "", G0,
  "FcOffTensao",      			"mV",      	&VarConvMUX.FcOffTensao,      		NIVEL_SUPER, FLOAT, "%-8.4f", -1000.0,  1000.0,   1e3, PAR_CUBAS, AT, "", "", G0,
  "FcGanhoTensao",   			"",       	&VarConvMUX.FcGanhoTensao,    		NIVEL_SUPER, FLOAT, "%-8.4f",	0.0,  1000.0,   1.0, PAR_CUBAS, AT, "", "", G0,
 #endif
/* -- Alteracao - Fim - 14/02/2001 - Carlos/Leonel - tratamento para cba sala 86ka -- */
  NULL,	NULL, 0, 0, 0,	NULL, 0.0, 0.0, 0.0, 0, 0, NULL, NULL
};

/*--- Estrutura de descricao das variaveis NMUX ---*/
t_par_var_log VarConverNMUX[] =
{
/* -- Alteracao - Inicio - 14/02/2001 - Carlos/Leonel - tratamento para cba sala 86ka -- */
 #ifndef	USA_ATN8
  "CALIBRACAO A/D",      			"",    NULL,  	NIVEL_SUPER, FLOAT, "%-8.2f",	0.0,  0.0,   1.0, TITULO_3,    AT, "", "", G0,
  "CalibNaoMux-0", 			"",     &VarConvNMUX.CalibNaoMux[0],  NIVEL_SUPER, FLOAT,    "%-10.6f", 	0.0,   999.0,   1.0,	PAR_LINHA,	AT, "", "", G0,
  "CalibNaoMux-1", 			"",     &VarConvNMUX.CalibNaoMux[1],  NIVEL_SUPER, FLOAT,    "%-10.6f", 	0.0,   999.0,   1.0,	PAR_LINHA,	AT, "", "", G0,
  "CalibNaoMux-2", 			"",     &VarConvNMUX.CalibNaoMux[2],  NIVEL_SUPER, FLOAT,    "%-10.6f", 	0.0,   999.0,   1.0,	PAR_LINHA,	AT, "", "", G0,
  "OffNaoMux-0",	   		"mV",   &VarConvNMUX.OffNaoMux[0],    NIVEL_SUPER, FLOAT,    "%-10.4f",-9999.0,	99999.0,	1e3,	PAR_LINHA,	AT, "", "", G0,
  "OffNaoMux-1",	   		"mV",   &VarConvNMUX.OffNaoMux[1],    NIVEL_SUPER, FLOAT,    "%-10.4f",-9999.0,	99999.0,	1e3,	PAR_LINHA,	AT, "", "", G0,
  "OffNaoMux-2",	   		"mV",   &VarConvNMUX.OffNaoMux[2],    NIVEL_SUPER, FLOAT,    "%-10.4f",-9999.0, 99999.0,	1e3,	PAR_LINHA,	AT, "", "", G0,
  "GanhoNaoMux-0",	   		"",     &VarConvNMUX.GanhoNaoMux[0],  NIVEL_SUPER, FLOAT,    "%-10.6f",		0.0,   2.0,   1.0,	PAR_LINHA,	AT, "", "", G0,
  "GanhoNaoMux-1",	   		"",     &VarConvNMUX.GanhoNaoMux[1],  NIVEL_SUPER, FLOAT,    "%-10.6f",		0.0,   2.0,   1.0,	PAR_LINHA,	AT, "", "", G0,
  "GanhoNaoMux-2",	   		"",     &VarConvNMUX.GanhoNaoMux[2],  NIVEL_SUPER, FLOAT,    "%-10.6f",		0.0,   2.0,   1.0,	PAR_LINHA,	AT, "", "", G0,
 #endif
/* -- Alteracao - Fim - 14/02/2001 - Carlos/Leonel - tratamento para cba sala 86ka -- */
  NULL,	NULL, 0, 0, 0,	NULL, 0.0, 0.0, 0.0, 0, 0, NULL, NULL
};

/*--- Estrutura de descricao das variaveis ESP ---*/
t_par_var_log VarEntradaESP[] =
{
  "NumEntEspeciais",   		"",     &VarEntESP.LeitEsp.NumEntEspeciais,			 NIVEL_SUPER, INT,    "%-2.0f",   0.0,   15.0,     1.0,	PAR_LINHA,	AT, "", "", G8,
  #ifndef	USA_ATN8
  "IndSadEntEsp-0",		   	"",  &VarEntESP.LeitEsp.EntEsp[0].IndSad,      NIVEL_SUPER, SHORT_INT,    "%-3.0f", 0.0,	256.0,  1,	PAR_LINHA,	AT, "", "", G8,
  "LsbEntEsp-0",		   	"mV",  &VarEntESP.LeitEsp.EntEsp[0].LsbEntEsp,      NIVEL_SUPER, FLOAT,    "%-10.4f", -9999.0,	99999.0,  1e3,	PAR_LINHA,	AT, "", "", G8,
  "LsbEntEsp-1",		  	"mV",  &VarEntESP.LeitEsp.EntEsp[1].LsbEntEsp,      NIVEL_SUPER, FLOAT,    "%-10.4f", -9999.0,	99999.0,  1e3,	PAR_LINHA,	AT, "", "", G8,
  "LsbEntEsp-2",		   	"mV", &VarEntESP.LeitEsp.EntEsp[2].LsbEntEsp,      NIVEL_SUPER, FLOAT,    "%-10.4f", -9999.0, 99999.0,  1e3,	PAR_LINHA,	AT, "", "", G8,
  "OffEntEsp-0",		   	"mV",  &VarEntESP.LeitEsp.EntEsp[0].OffEntEsp,      NIVEL_SUPER, FLOAT,    "%-10.4f", -9999.0, 99999.0,  1e3,	PAR_LINHA,	AT, "", "", G8,
  "OffEntEsp-1",		   	"mV",  &VarEntESP.LeitEsp.EntEsp[1].OffEntEsp,      NIVEL_SUPER, FLOAT,    "%-10.4f", -9999.0, 99999.0,  1e3,	PAR_LINHA,	AT, "", "", G8,
  "OffEntEsp-2",		   	"mV", &VarEntESP.LeitEsp.EntEsp[2].OffEntEsp,      NIVEL_SUPER, FLOAT,    "%-10.4f", -9999.0, 99999.0,  1e3,	PAR_LINHA,	AT, "", "", G8,
  "GanhoEntEsp-0",	   		"",     &VarEntESP.LeitEsp.EntEsp[0].GanhoEntEsp,    NIVEL_SUPER, FLOAT,    "%-10.7f",   0.0,   5.0,	 1.0,	PAR_LINHA,	AT, "", "", G8,
  "GanhoEntEsp-1",	   		"",     &VarEntESP.LeitEsp.EntEsp[1].GanhoEntEsp,    NIVEL_SUPER, FLOAT,    "%-10.7f",   0.0,   5.0,	 1.0,	PAR_LINHA,	AT, "", "", G8,
  "GanhoEntEsp-2",	   		"",     &VarEntESP.LeitEsp.EntEsp[2].GanhoEntEsp,    NIVEL_SUPER, FLOAT,    "%-10.7f",   0.0,   5.0,	 1.0,	PAR_LINHA,	AT, "", "", G8,
  "CalibEntEsp-0",	   		"",     &VarEntESP.LeitEsp.EntEsp[0].CalibEntEsp,    NIVEL_SUPER, FLOAT,    "%-10.7f",   0.0,   5.0,	 1.0,	PAR_LINHA,	AT, "", "", G8,
  "CalibEntEsp-1",	   		"",     &VarEntESP.LeitEsp.EntEsp[1].CalibEntEsp,    NIVEL_SUPER, FLOAT,    "%-10.7f",   0.0,   5.0,	 1.0,	PAR_LINHA,	AT, "", "", G8,
  "CalibEntEsp-2",	   		"",     &VarEntESP.LeitEsp.EntEsp[2].CalibEntEsp,    NIVEL_SUPER, FLOAT,    "%-10.7f",   0.0,   5.0,	 1.0,	PAR_LINHA,	AT, "", "", G8,
  #endif
/* -- Alteracao - Fim - 14/02/2001 - Carlos/Leonel - tratamento para cba sala 86ka -- */
  NULL,	NULL, 0, 0, 0,	NULL, 0.0, 0.0, 0.0, 0, 0, NULL, NULL
};

/* -- alteracao - inicio - 04/01/2001 - Leonel - Inclusao novas tabelas p/ tratamento Atn8 -- */
/*--- Estrutura de descricao das variaveis ConvAtn8 ---*/
t_par_var_log VarConverAtn8[] =
{
/* -- Alteracao - Inicio - 14/02/2001 - Carlos/Leonel - tratamento para cba sala 86ka -- */
#ifdef	USA_ATN8
  "ATN8 A/Ds",	"",		NULL,	NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_1,    AT, "", "", G0,
  "Lsb-0",	   		"mV",     &VarConvAtn8.Lsb[0],  NIVEL_SUPER, FLOAT,    "%-10.4f",	-9999.0,   99999.0,   1e3,	PAR_CUBAS,	AT, "", "", G0,
  "Lsb-1",	   		"mV",     &VarConvAtn8.Lsb[1],  NIVEL_SUPER, FLOAT,    "%-10.4f",	-9999.0,   99999.0,   1e3,	PAR_CUBAS,	AT, "", "", G0,
  "Lsb-2",	   		"mV",     &VarConvAtn8.Lsb[2],  NIVEL_SUPER, FLOAT,    "%-10.4f",	-9999.0,   99999.0,   1e3,	PAR_CUBAS,	AT, "", "", G0,
  "Lsb-3",	   		"mV",     &VarConvAtn8.Lsb[3],  NIVEL_SUPER, FLOAT,    "%-10.4f",	-9999.0,   99999.0,   1e3,	PAR_CUBAS,	AT, "", "", G0,
  "Offset-0",	   	"mV",	  &VarConvAtn8.Offset[0],NIVEL_SUPER,FLOAT,    "%-10.4f",	-9999.0,   99999.0,   1e3,	PAR_CUBAS,	AT, "", "", G0,
  "Offset-1",	   	"mV",	  &VarConvAtn8.Offset[1],NIVEL_SUPER,FLOAT,    "%-10.4f",	-9999.0,   99999.0,   1e3,	PAR_CUBAS,	AT, "", "", G0,
  "Offset-2",	   	"mV",	  &VarConvAtn8.Offset[2],NIVEL_SUPER,FLOAT,    "%-10.4f",	-9999.0,   99999.0,   1e3,	PAR_CUBAS,	AT, "", "", G0,
  "Offset-3",	   	"mV",	  &VarConvAtn8.Offset[3],NIVEL_SUPER,FLOAT,    "%-10.4f",	-9999.0,   99999.0,   1e3,	PAR_CUBAS,	AT, "", "", G0,
  "Ganho-0",	   	"",		  &VarConvAtn8.Ganho[0], NIVEL_SUPER,FLOAT,    "%-10.7f",		0.0,   5.0,		  1.0,	PAR_CUBAS,	AT, "", "", G0,
  "Ganho-1",	   	"",		  &VarConvAtn8.Ganho[1], NIVEL_SUPER,FLOAT,    "%-10.7f",		0.0,   5.0,		  1.0,	PAR_CUBAS,	AT, "", "", G0,
  "Ganho-2",	   	"",		  &VarConvAtn8.Ganho[2], NIVEL_SUPER,FLOAT,    "%-10.7f",		0.0,   5.0,		  1.0,	PAR_CUBAS,	AT, "", "", G0,
  "Ganho-3",	   	"",		  &VarConvAtn8.Ganho[3], NIVEL_SUPER,FLOAT,    "%-10.7f",		0.0,   5.0,		  1.0,	PAR_CUBAS,	AT, "", "", G0,
  "Calib-0",	   	"",		  &VarConvAtn8.Calib[0], NIVEL_SUPER,FLOAT,    "%-10.7f",		0.0,   5.0,		  1.0,	PAR_CUBAS,	AT, "", "", G0,
  "Calib-1",	   	"",		  &VarConvAtn8.Calib[1], NIVEL_SUPER,FLOAT,    "%-10.7f",		0.0,   5.0,		  1.0,	PAR_CUBAS,	AT, "", "", G0,
  "Calib-2",	   	"",		  &VarConvAtn8.Calib[2], NIVEL_SUPER,FLOAT,    "%-10.7f",		0.0,   5.0,		  1.0,	PAR_CUBAS,	AT, "", "", G0,
  "Calib-3",	   	"",		  &VarConvAtn8.Calib[3], NIVEL_SUPER,FLOAT,    "%-10.7f",		0.0,   5.0,		  1.0,	PAR_CUBAS,	AT, "", "", G0,
  "Relacao-0",	   	"",		  &VarConvAtn8.Rel[0],	 NIVEL_SUPER,FLOAT,    "%-10.2f",		0.0,   9999999.0,  1.0,	PAR_CUBAS,	AT, "", "", G0,
  "Relacao-1",	   	"",		  &VarConvAtn8.Rel[1],	 NIVEL_SUPER,FLOAT,    "%-10.2f",		0.0,   9999999.0,  1.0,	PAR_CUBAS,	AT, "", "", G0,
  "Relacao-2",	   	"",		  &VarConvAtn8.Rel[2],	 NIVEL_SUPER,FLOAT,    "%-10.2f",		0.0,   9999999.0,  1.0,	PAR_CUBAS,	AT, "", "", G0,
  "Relacao-3",	   	"",		  &VarConvAtn8.Rel[3],	 NIVEL_SUPER,FLOAT,    "%-10.2f",		0.0,   9999999.0,  1.0,	PAR_CUBAS,	AT, "", "", G0,
#endif
/* -- Alteracao - Fim - 14/02/2001 - Carlos/Leonel - tratamento para cba sala 86ka -- */
  NULL,	NULL, 0, 0, 0,	NULL, 0.0, 0.0, 0.0, 0, 0, NULL, NULL
};

/*--- Estrutura de descricao das variaveis ConvEspAtn8 ---*/
t_par_var_log VarConverEspAtn8[] =
{
/* -- Alteracao - Inicio - 14/02/2001 - Carlos/Leonel - tratamento para cba sala 86ka -- */
#ifdef	USA_ATN8
  "ATN8 ENT ESP",	"",		NULL,	NIVEL_SUPER, FLOAT,	"%-5.2f",	0.0,	0.0,	1.0,	TITULO_3,    AT, "", "", G8,
  "IndRemEsp-0",	"",     &VarConvEspAtn8.EntEspAtn8[0].IndRemEsp,  NIVEL_SUPER, SHORT_INT, "%-3.0f",  0.0,		500.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "EntEsp-0",	"",     &VarConvEspAtn8.EntEspAtn8[0].CanalEntEsp,NIVEL_SUPER, BYTE,	  "%-1.0f",   0.0,		3.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "LsbEsp-0",       "mV",   &VarConvEspAtn8.EntEspAtn8[0].LsbEsp,     NIVEL_SUPER, FLOAT,	  "%-10.4f",  -9999.0,	99999.0,1e3, PAR_LINHA, AT, "", "", G8,
  "OffEsp-0",       "mV",   &VarConvEspAtn8.EntEspAtn8[0].OffEsp,     NIVEL_SUPER, FLOAT,	  "%-10.4f",  -9999.0,	99999.0,1e3, PAR_LINHA, AT, "", "", G8,
  "GanhoEsp-0",     "",     &VarConvEspAtn8.EntEspAtn8[0].GanhoEsp,   NIVEL_SUPER, FLOAT,	  "%-10.7f",  0.0,		5.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "CalibEsp-0",     "",     &VarConvEspAtn8.EntEspAtn8[0].CalibEsp,   NIVEL_SUPER, FLOAT,	  "%-10.7f",  0.0,		5.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "RelacaoEsp-0",   "",     &VarConvEspAtn8.EntEspAtn8[0].RelEsp,     NIVEL_SUPER, FLOAT,	  "%-10.2f",  0.0,		9999999.0,1.0, PAR_LINHA, AT, "", "", G8,
  "IndRemEsp-1",	"",     &VarConvEspAtn8.EntEspAtn8[1].IndRemEsp,  NIVEL_SUPER, SHORT_INT, "%-3.0f",  0.0,		500.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "CanalEntEsp-1",	"",     &VarConvEspAtn8.EntEspAtn8[1].CanalEntEsp,NIVEL_SUPER, BYTE,	  "%-1.0f",   0.0,		3.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "LsbEsp-1",       "mV",   &VarConvEspAtn8.EntEspAtn8[1].LsbEsp,     NIVEL_SUPER, FLOAT,	  "%-10.4f",  -9999.0,	99999.0,1e3, PAR_LINHA, AT, "", "", G8,
  "OffEsp-1",       "mV",   &VarConvEspAtn8.EntEspAtn8[1].OffEsp,     NIVEL_SUPER, FLOAT,	  "%-10.4f",  -9999.0,	99999.0,1e3, PAR_LINHA, AT, "", "", G8,
  "GanhoEsp-1",     "",     &VarConvEspAtn8.EntEspAtn8[1].GanhoEsp,   NIVEL_SUPER, FLOAT,	  "%-10.7f",  0.0,		5.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "CalibEsp-1",     "",     &VarConvEspAtn8.EntEspAtn8[1].CalibEsp,   NIVEL_SUPER, FLOAT,	  "%-10.7f",  0.0,		5.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "RelacaoEsp-1",   "",     &VarConvEspAtn8.EntEspAtn8[1].RelEsp,     NIVEL_SUPER, FLOAT,	  "%-10.2f",  0.0,		9999999.0,1.0, PAR_LINHA, AT, "", "", G8,
  "IndRemEsp-2",	"",     &VarConvEspAtn8.EntEspAtn8[2].IndRemEsp,  NIVEL_SUPER, SHORT_INT, "%-3.0f",  0.0,		500.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "CanalEntEsp-2",	"",     &VarConvEspAtn8.EntEspAtn8[2].CanalEntEsp,NIVEL_SUPER, BYTE,	  "%-1.0f",   0.0,		3.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "LsbEsp-2",       "mV",   &VarConvEspAtn8.EntEspAtn8[2].LsbEsp,     NIVEL_SUPER, FLOAT,	  "%-10.4f",  -9999.0,	99999.0,1e3, PAR_LINHA, AT, "", "", G8,
  "OffEsp-2",       "mV",   &VarConvEspAtn8.EntEspAtn8[2].OffEsp,     NIVEL_SUPER, FLOAT,	  "%-10.4f",  -9999.0,	99999.0,1e3, PAR_LINHA, AT, "", "", G8,
  "GanhoEsp-2",     "",     &VarConvEspAtn8.EntEspAtn8[2].GanhoEsp,   NIVEL_SUPER, FLOAT,	  "%-10.7f",  0.0,		5.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "CalibEsp-2",     "",     &VarConvEspAtn8.EntEspAtn8[2].CalibEsp,   NIVEL_SUPER, FLOAT,	  "%-10.7f",  0.0,		5.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "RelacaoEsp-2",   "",     &VarConvEspAtn8.EntEspAtn8[2].RelEsp,     NIVEL_SUPER, FLOAT,	  "%-10.2f",  0.0,		9999999.0,1.0, PAR_LINHA, AT, "", "", G8,
  "IndRemEsp-3",	"",     &VarConvEspAtn8.EntEspAtn8[3].IndRemEsp,  NIVEL_SUPER, SHORT_INT, "%-3.0f",  0.0,		500.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "CanalEntEsp-3",	"",     &VarConvEspAtn8.EntEspAtn8[3].CanalEntEsp,NIVEL_SUPER, BYTE,	  "%-1.0f",   0.0,		3.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "LsbEsp-3",       "mV",   &VarConvEspAtn8.EntEspAtn8[3].LsbEsp,     NIVEL_SUPER, FLOAT,	  "%-10.4f",  -9999.0,	99999.0,1e3, PAR_LINHA, AT, "", "", G8,
  "OffEsp-3",       "mV",   &VarConvEspAtn8.EntEspAtn8[3].OffEsp,     NIVEL_SUPER, FLOAT,	  "%-10.4f",  -9999.0,	99999.0,1e3, PAR_LINHA, AT, "", "", G8,
  "GanhoEsp-3",     "",     &VarConvEspAtn8.EntEspAtn8[3].GanhoEsp,   NIVEL_SUPER, FLOAT,	  "%-10.7f",  0.0,		5.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "CalibEsp-3",     "",     &VarConvEspAtn8.EntEspAtn8[3].CalibEsp,   NIVEL_SUPER, FLOAT,	  "%-10.7f",  0.0,		5.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "RelacaoEsp-3",   "",     &VarConvEspAtn8.EntEspAtn8[3].RelEsp,     NIVEL_SUPER, FLOAT,	  "%-10.2f",  0.0,		9999999.0,1.0, PAR_LINHA, AT, "", "", G8,
  "IndRemEsp-4",	"",     &VarConvEspAtn8.EntEspAtn8[4].IndRemEsp,  NIVEL_SUPER, SHORT_INT, "%-3.0f",  0.0,		500.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "CanalEntEsp-4",	"",     &VarConvEspAtn8.EntEspAtn8[4].CanalEntEsp,NIVEL_SUPER, BYTE,	  "%-1.0f",   0.0,		3.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "LsbEsp-4",       "mV",   &VarConvEspAtn8.EntEspAtn8[4].LsbEsp,     NIVEL_SUPER, FLOAT,	  "%-10.4f",  -9999.0,	99999.0,1e3, PAR_LINHA, AT, "", "", G8,
  "OffEsp-4",       "mV",   &VarConvEspAtn8.EntEspAtn8[4].OffEsp,     NIVEL_SUPER, FLOAT,	  "%-10.4f",  -9999.0,	99999.0,1e3, PAR_LINHA, AT, "", "", G8,
  "GanhoEsp-4",     "",     &VarConvEspAtn8.EntEspAtn8[4].GanhoEsp,   NIVEL_SUPER, FLOAT,	  "%-10.7f",  0.0,		5.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "CalibEsp-4",     "",     &VarConvEspAtn8.EntEspAtn8[4].CalibEsp,   NIVEL_SUPER, FLOAT,	  "%-10.7f",  0.0,		5.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "RelacaoEsp-4",   "",     &VarConvEspAtn8.EntEspAtn8[4].RelEsp,     NIVEL_SUPER, FLOAT,	  "%-10.2f",  0.0,		9999999.0,1.0, PAR_LINHA, AT, "", "", G8,
  "IndRemEsp-5",	"",     &VarConvEspAtn8.EntEspAtn8[5].IndRemEsp,  NIVEL_SUPER, SHORT_INT, "%-3.0f",  0.0,		500.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "CanalEntEsp-5",	"",     &VarConvEspAtn8.EntEspAtn8[5].CanalEntEsp,NIVEL_SUPER, BYTE,	  "%-1.0f",   0.0,		3.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "LsbEsp-5",       "mV",   &VarConvEspAtn8.EntEspAtn8[5].LsbEsp,     NIVEL_SUPER, FLOAT,	  "%-10.4f",  -9999.0,	99999.0,1e3, PAR_LINHA, AT, "", "", G8,
  "OffEsp-5",       "mV",   &VarConvEspAtn8.EntEspAtn8[5].OffEsp,     NIVEL_SUPER, FLOAT,	  "%-10.4f",  -9999.0,	99999.0,1e3, PAR_LINHA, AT, "", "", G8,
  "GanhoEsp-5",     "",     &VarConvEspAtn8.EntEspAtn8[5].GanhoEsp,   NIVEL_SUPER, FLOAT,	  "%-10.7f",  0.0,		5.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "CalibEsp-5",     "",     &VarConvEspAtn8.EntEspAtn8[5].CalibEsp,   NIVEL_SUPER, FLOAT,	  "%-10.7f",  0.0,		5.0,	1.0, PAR_LINHA, AT, "", "", G8,
  "RelacaoEsp-5",   "",     &VarConvEspAtn8.EntEspAtn8[5].RelEsp,     NIVEL_SUPER, FLOAT,	  "%-10.2f",  0.0,		9999999.0,1.0, PAR_LINHA, AT, "", "", G8,
#endif
/* -- Alteracao - Fim - 14/02/2001 - Carlos/Leonel - tratamento para cba sala 86ka -- */
  NULL,	NULL, 0, 0, 0,	NULL, 0.0, 0.0, 0.0, 0, 0, NULL, NULL
};
/* -- alteracao - fim - 04/01/2001 - Leonel - Inclusao novas tabelas p/ tratamento Atn8 -- */

#endif
