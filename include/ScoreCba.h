/******************************************************************************
 
			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO  : CBA - COMPANHIA BRASILEIRA DE ALUMINIO SA

	SISTEMA  : AUTOMACAO SALAS 120KA II e III

	ARQUIVO  : ScoreCba.h

	CONTEUDO : Contem as definicoes de todas as constantes especificas do
			   Sistema de Controle de Reducoes Cba.
			   Possui tambem as definicoes das estruturas de dados da
			   base de dados em area comum de memoria.

	AUTOR    : Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO   : 1.0		  -	  DATA  : 03/01/97

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
03/01/97 | Edicao inicial                             			| Leonel
-------------------------------------------------------------------------------
04/05/98 | Inclusao das variaveis de quebrada preventiva		| Carlos
-------------------------------------------------------------------------------
16/07/98 | Inclusao e transf. das variaveis de ajuste de camisa	| Carlos
-------------------------------------------------------------------------------
16/07/98 | Transferencia das variaveis de ajuste para ScoreCBA 	| Carlos
-------------------------------------------------------------------------------
22/06/99 | Inclusao do define para booster de corrente.    	    | Carlos
-------------------------------------------------------------------------------
09/07/99 | Inclusao da variavel HabQPrevOpe.               	    | Carlos
-------------------------------------------------------------------------------
28/12/00 | Incluidas variaveis para temperatura da remota Atn8  | Leonel
-------------------------------------------------------------------------------
03/07/02 | Inclusao da variavel BoosterAtivo                    | Carlos 
-------------------------------------------------------------------------------
05/07/02 | Inclusao da variavel HabElimEaOpe                    | Carlos 
-------------------------------------------------------------------------------
24/06/04 | Inclusao das variaveis de sopro especial             | Carlos 
-------------------------------------------------------------------------------
14/11/14 | Expansao 25% base dados para Score8 CBA - Sala II    | Carlos
-------------------------------------------------------------------------------
******************************************************************************/
/*********************************** Revisoes ********************************\
$Id: ScoreCba.h,v 1.11.4.2 2015/07/02 14:08:28 clage Exp $

$Log: ScoreCba.h,v $
Revision 1.11.4.2  2015/07/02 14:08:28  clage
Alteracao para sala II com ATN8 e atualizacao dos algoritmos da CBA ate esta data.

Revision 1.11.4.1  2015/06/30 22:44:55  clage
Alteracoes para sala II com ATN8 e expansao da base de dados.

Revision 1.11  2008/10/13 17:49:21  leo
Variaveis para o algoritmo de manobra de cruzeiro.

Revision 1.10  2008/08/04 20:31:42  leo
Incluido flag ReleTempoMM (CBA).

Revision 1.9  2007/01/11 18:27:39  rogerio
teste

Revision 1.8  2005/10/14 18:04:32  leo
Alteracao da unidade de engenharia dos parametros de quebrada preventiva de horas
para minutos.

Revision 1.7  2004/08/03 19:52:47  clage
Incluido parametros de flexibilizacao de quebrada preventiva

Revision 1.6  2004/07/20 18:46:29  alex
nova entrada de dados via radio analise/operacionais

Revision 1.5  2004/07/05 14:40:07  clage
Algoritmo de sopro especial

Revision 1.4  2003/06/20 17:47:13  alex
Colocado habilitacao e batentes para move e sopro nos vmi's

Revision 1.3  2003/05/30 17:09:15  alex
*** empty log message ***

Revision 1.2  2003/03/13 20:51:23  leo
Inclusao de variaveis e constantes para o tratamento da tabela de partida
de cubas. Criacao de novas funcoes e inclusao de seus prototipos.

\*********************************** Revisoes ********************************/

#ifndef		_SCORE_CBA_H

#define _SCORE_CBA_H


/* -- ********************** DEFINICOES ******************************** -- */

/* define indicador do tratamento para booster de corrente  implementado */
/* e disponivel para uso no Score. Com a existencia desse define, nao ha */
/* necessidade  de alterar  os  makefiles do sistema,  pois os programas */
/* automaticamente compilarao com a parte de booster de corrente.        */

#define	BOOSTER_CORRENTE		1

/* define novas estruturas de usuario */
#define			DEF_AVC_USU		1

#define POLI_SIZE            10  /* Maior ordem do polinomio utilizado para aproximaca da curva Conc X Der */
#define POLI_INDEX (POLI_SIZE+1) /* Indice dos vetores que armazenam os elementos do polinomio de aproximacao */

/* -- constante que indica a ausencia de alimentacao automatica na cuba -- */
#define NAO_TEM_ALIM  0
/* -- constante que indica a presenca de point feeder na cuba -- */
#define TEM_PF		  1
/* -- constante que indica a presenca de barra quebra crosta na cuba -- */
#define TEM_BARRA     2

/* -- Alteracao - inicio - Robson - 03/10/2000 - alteracao para novo PF -- */
#define MAX_PASSOS_ACIONA_ALIM	6 /* numero maximo de passos na lista de comando
									 + 1 para definir o fim da lista */
#define NUM_CONJ_ALIM			4 /* numero de conjuntos de alimentadores */
#define SEQ_COMPLETA			0 /* define programacao de seq completa */
#define SO_QUEBRADOR			1 /* define programacao somente do quebrador */
/* -- Alteracao - fim - Robson - 03/10/2000 - alteracao para novo PF -- */

/* -- definicoes referentes a inibicao de quebrada preventiva -- */
#define QPREV_SEM_INIBICAO			0
#define INIBICAO_POR_TEMPO			1
#define INIBICAO_PROXIMO_EA			2

/* -- Definicoes relativas ao ajuste de camisa -- */
/*-- Acoes de ajuste --*/
#define	ATIVA_AJUSTE_CAMISA			1
#define DESATIVA_AJUSTE_CAMISA		2
#define	INIBE_AJUSTE_CAMISA			3

/* -- Definicoes relativas a quebrada preventiva -- */
/*-- Acoes de qubrada preventiva --*/
#define	QPREV_POR_TEMPO					1
#define QPREV_PROX_EA					2
#define	ATIVA_QPREV						3
#define DESATIVA_QPREV					4

/* -- Definicoes para a tabela de partida de cubas -- */
/* Limites */
#define		MAX_PASSOS_TAB_PARTIDA	20
#define		MAX_TAB_PARTIDA			2

/* Acoes possiveis */
#define		TAB_PART_ACAO_NULA		0	/* Acao nao inicializada=Fim da tabela */
#define		TAB_PART_MUDA_ESTADO	1	/* Muda estado da cuba */
#define		TAB_PART_MUDA_AUT_MAN	2	/* Muda estado motor macaco */
#define		TAB_PART_MUDA_LIM_EA	3	/* Muda limite EA */
#define		TAB_PART_AJUSTE_CAMISA	4	/* Hab/desab. ajuste de camisa */
#define		TAB_PART_QUEB_PREV		5	/* Hab/desab. quebrada preventiva */
#define		TAB_PART_TAB_INC_OPER	6	/* Hab. tabela incremento operacao */
#define		TAB_PART_ESPERA			7	/* Aguarda tempo */

/*-- Estados de Sopro Especial --*/
#define SOPRO_INICIAL				1
#define SOPRO_EXECUCAO				2
#define SOPRO_FIM_TEMPO				3
#define SOPRO_FIM_OPERADOR			4
#define SOPRO_FIM_EA				5
#define SOPRO_DESAB_INICIAL			6
#define SOPRO_FIM_DESAB				7

/* -- Novo tipo de incremento alem dos originais do Score (INCREMENTO_LINEAR=1 e INCREMENTO_RAMPA=2) -- */
#define INCREMENTO_TRIANGULO 3

/* -- ********************* TIPOS DE DADOS ***************************** -- */

typedef
  volatile struct _cnf_sup {
		/* -- Novos dados p/ relatorio via Coletor CBA sala 64kA -- */
		float	Banho;			// dados em cm (media)
		float	Metal;			// dados em cm (media)
		int		Temperatura;	// em C (media)
		int		Producao;		// em Kg/F (totalizacao)
		int		BanhoFrio;		// em lado A,B ou AB (totalizacao)
		int		CrioSint;		// em sacos (totalizacao)
		int		CrioAciq;		// em sacos (totalizacao)
		int		CrioRecu;		// em Kg (totalizacao)
		float	Fluoreto;		// em %
		float	Fluorita;		// em %
//		int		Fluoreto;		// em sacos (totalizacao)
//		int		Fluorita;		// em sacos (totalizacao)
		int		Barrilha;		// em sacos (totalizacao)

		short	OperarTurno;	// numero do turno (totalizacao)
		short	Carvao;			// S/N (totalizacao)
		short	Atrasado;		// S/N (totalizacao)
		short	FundoSujo;		// S/N (totalizacao)
		short	Acidez;			// A(Acido),N(Normal) ou B(Baixo) (totalizacao)
		short	FornoAbrindo;	// A,B ou AB (totalizacao)

		float	VazioPasta;		// cm (media)
		float	Desfilamento;	// cm (media)
		float	AlturaAnodo;	// cm (media)
		float	Flanco;			// cm (media)
		float	QuedaCatodica;	// mV (media)
		float	QuedaAnodica;	// mV (media)
}t_cnf_sup;

/* -- Tabela de partida de cubas -- */
typedef
  volatile struct passo_partida
  {
  	byte Acao;		/* Acao a ser executa no passo. 0 indica ultimo passo */
	union par
	{
	  int	Ipar;
	  float	Fpar;
	  long	Tpar;
	} Param;			/* para os diversos tipos de parametros dos passos */
  } t_passo_partida;
  
typedef
  volatile struct tabela_partida
  {
    t_passo_partida	Passo[MAX_PASSOS_TAB_PARTIDA];
  } t_partida_cuba;


/* -- Tipos de dados das tabelas da Cba para o AVC -- */
/* ATENCAO : Estas tabelas nao devem ter suas reservas ultrapassadas */
/*
------------------------------------------------------------------------
||      Type        ||    Storage Size     ||      Value Range        ||
------------------------------------------------------------------------
||      I   N   T   E   G   E   R       T   y   p   e   s             ||
------------------------------------------------------------------------
|| char             || 1 byte              || -128 to 127 or 0 to 255 ||
|| unsigned char    || 1 byte              || 0 to 255                ||
|| signed char      || 1 byte              || -128 to 127             ||
|| int              || 2 or 4 bytes        || -32,678 to 32,767 or    ||
||                  ||                     || -2,147,483,648 to       ||
||                  ||                     || +2,147,483,647          ||
|| unsigned int     || 2 or 4 bytes        || 0 to 65,535 or          ||
||                  ||                     || 0 to 4,294,967,295      ||
|| short (int)      || 2 bytes             || -32,768 to 32,767       ||
|| unsigned short   || 2 bytes             || 0 to 65,535             ||
|| long             || 4 bytes (for 32bit) || -9223372036854775808 to ||
||                  ||                     || 9223372036854775807     ||
|| unsigned long    || 4 bytes (for 32bit) || 0 to                    ||
||                  ||                     || 18446744073709551615    ||
------------------------------------------------------------------------
||      F   L   O   A   T   I   N   G   -   P   O   I   N   T         ||
------------------------------------------------------------------------
|| float             || 4 bytes            || 1.2E-38 to 3.4E+38      ||
||                   ||                    || (6 decimal places)      ||
|| double            || 8 bytes            || 2.3E-308 to 1.7E+308    ||
||                   ||                    || (15 decimal places)     ||
|| long double       || 10 bytes           || 3.4E-4932 to 1.1E+4932  ||
||                   ||                    || (19 decimal places)     ||
------------------------------------------------------------------------ 
*/

/* -- Tabelas de parametros da Cba -- */
typedef
  volatile struct par1_user_avc /* 1a. tabela de parametros da Cba */
  {
    /* parametros do algoritmo de alimentacao point feeder */
	byte	HabilitaPF;		   /* Habilita alg. de point feeder qdo. 1 */
	float	Livre;
	float	ConcNominal;	   /* Concentracao nominal de Al2O3 (%) */
	float	DesvioCarga;	   /* Desvio da carga (%) */
	float	DesvioConNominal;  /* Desvio da concentracao nominal de Al2O3 (%) */
	long	TTipicoCheck;	   /* Tempo tipico de check */
	short int NumAcionaCheck;  /* Numero de acionamentos do PF tipico p/ check */
	float	LimMinCheck;	   /* Limite minimo para entrar em check (%) */
	float	MassaBanho;		   /* Massa do banho (Kg) */
    short int	TempoAvanco;   /* Tempo de Avanco do Point Feeder */
    short int	TempoInterv;   /* Tempo de intervalo entre Avanco/ Recuo do PF */
    short int	TempoRecuo;	   /* Tempo de Recuo do Point Feeder */
	short int	TempoCadFalta; /* Tempo (segundos) de cadencia de alimentacao
								   qdo. micro estiver fora. configurado na remota */
/* -- Alteracao - Fim - Robson - 02/10/2000 - PF Sala III -- */
    float   MaxDeltaEfiCurr;   /* Maior variacao aceitavel p/ a eficiencia de corrente (%) */
    float   TaxaUnder;         /* Indica valor normal do underfeed ( >1) */
    float   TaxaOverNorm;      /* Indica valor normal do underfeed (0<T<1) */ 
    float   ConsumoResAlim;    /* Percentual de alumina a ser consumido antes 
                                   de coletar valor da resistencia */ 
    long    MaxIntervCheck;    /* Intervalo maximo entre checks */
    float   UnderProgIni;      /* Valor inicial do underfeed progressivo */
    long    IntervUnderProg;   /* Intervalo p/ modificacao do under progressivo */
    float   DeltaUnder;        /* Variacao percentual (step) do underfeed progressivo */
    byte    OverOpcional;      /* Flag p/ habilitar overfeed opcional no inicio do check */
    float   PercOverOp;        /* Percentual de concetracao de alumina a ser fornecido no overfeed opcional */
    float   KSuaveAlim;        /* Usado na filtragem da resistencia de alimentacao */
    float   DerInitCheck;      /* Derivada p/ inicio do check */
    long    MaxIntervEa;       /* Tempo maximo de espera de EA ate entrar em alimentacao suspensa */
    byte    HabilitaOverEA;    /* Habilita alimentacao overfeed em caso de EA */
    float   TaxaOverEA;        /* Taxa de overfeed durante inicio do EA */
    long    DurNormCheck;      /* Duracao da alimentacao normal entre os checks (check especial) */
    short int PolOrd;          /* ordem do polinomio usado na aproximacao da derivada da curva */
    float   Poly[11];          /* vetor com os coeficientes do polinomio utilizado na curva %Al2O3 X Der */
    float   MinConc;           /* menor concetracao aceitavel (derivada-valores expurios) */
    float   MaxConc;           /* maior concentracao aceitavel (derivada-valores expurios) */
    float   ConcValidCheck;    /* concentracao tipica de check (concentracao 
                                  de check deve ser menor ou igual a ela) */
    long    MinIntervPF;       /* intervalo minimo entre acionamentos do point feeder */
    short int MaxOverCheck;    /* numero maximo de overfeeds dentro de um mesmo check */
    long    MaxTOverEa;        /* tempo maximo de overfeed em efeito anodico */
    long    EstabQueb;         /* tempo de estabilizacao apos quebrada */
    float   MaxDerInitCheck;   /* valor acima do qual o algoritmo entre em overfeed */
	float   ConcHabMove;       /* concentracao minima para habilitar movimentacao de anodo durante o tracking */

    /* variaveis do algoritmo de alimentacao para barra quebra crosta lateral */
	byte    HabilitaBarra; 	   /* Habilita o algoritmo de alimentacao */
	byte    TempoFixo;         /* indica se quebrada sera feita a tempo fixo ou por demanda */
	float   EfiCurrIni;        /* eficiencia de corrente da cuba */
	float   MinDer;            /* menor valor possivel para derivada (abaixo deste valor, derivada e limitada) */
	float   MaxDer;            /* maior valor possivel para derivada (acima deste valor, derivada e limitada) */ 
	float   DerAliment;        /* Derivada abaixo da qual a cuba eh alimentada */
	long    MinIntervQueb;     /* minimo intervalo entre quebradas */
	long    IntervQueb;        /* intervalo entre quebradas (tempo fixo) */
	int     MaxNumQueb;        /* maximo numero de quebradas entre efeitos anodicos */
	long    TTerminaEa;        /* tempo para indicar falha na eliminacao automatica do EA */ 

    byte    HabMoveSusp;       /* Habilita/Desabilita a movimentacao do anodo em alimentacao suspensa */
    byte    HabMovTrack;       /* Habilita/Desabilita a movimentacao do anodo durante tracking da concentracao nominal */

    /* Parametros limitrofes p/ eficiencia de corrente */
	float 	MaxEfiCurr;        /* Maxima eficiencia de corrente */
	float	MinEfiCurr;	       /* Minima eficiencia de corrente */
    byte    HabQPrev;          /* Hab./Desab. quebrada preventiva */
    short int LimInfQPrevEa;   /* Lim. inf. queb. prev. em relacao EA */
    short int LimSupQPrevEa;   /* Lim. sup. queb. prev. em relacao atraso EA */
    short int MaxQPrevEa;      /* Numero de solicitacoes permitidas entre EA */
    short int NHorRefQPrev;    /* No. minutos em relacao a ult. queb. prev. */
    short int IntMinQQPrev;    /* No. minutos em relacao a ult. quebrada */
	byte	HabAjCam;			/* Habilita/desab. ajuste de camisa */
// Inserido em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
	byte	HabNormFeedEa;		/* Habilita Normal feed no estado 2 do algoritmo de Ea */
    float	LimMaxAjCam;		/* Tempo maximo de ajuste permitido */
    float	LimTAjMov;			/* Tempo maximo de ajuste por movimento */
    short int IntAjCamCorr;		/* Intervalo em relacao a corrida anterior */
	float	DifResAgarra;		/* Diferenca para agarramento de anodo */
	int		NAjIntermCorr;		/* numero de ajustes durante a corrida */
// Inserido em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
    long    EstabCorr;          /* tempo de estabilizacao apos corrida */
    long    TSuspLinhaD;        /* tempo de linha desabilitada para passar a
								   cuba para estado alimentacao suspensa */
    long    TSaiSuspLinhaD;     /* tempo maximo a ser aguardado em alimentacao
								   suspensa apos religar a linha */
// Inserido em 15/01/99, segundo solicitacao da proposta 1006CA. Leonel
/* -- Alteracao - Inicio - Robson - 02/10/2000 - PF Sala III -- */
	byte	HabQueb[NUM_CONJ_ALIM];		/* habilita quebrador A */
	byte	HabAlim[NUM_CONJ_ALIM];		/* habilita alimentador A */
	byte	Sequencia[NUM_CONJ_ALIM];	/* sequencia de alimentacao */
	float	TempoEspera;		/* Tempo de espera depois de uma quebrada */
/* -- Alteracao - Inicio - 23/07/02 - Robson - cada quebrador/alimentador tera um tempo diferente - */
	//float	Liver1;
	byte BufferSizeRH;
	byte Livre1;
	byte Livre2;
	byte	UsaMaxAEK;		/* Habilita/desabilita teste AEKMax em quebrada preventiva */
	
	float	NivelProvQueb; /* Nível do Coeficiente Angular de RSuaveDerivH para Detecção de Provável Quebra */
//	float	TempoQuebrador;    /* Tempo de acionamento do quebrador */
//	float	TempoAlimentador;  /* Tempo de acionamento do alimentador */
/* -- Alteracao - Fim - 23/07/02 - Robson - cada quebrador/alimentador tera um tempo diferente - */
/* -- Alteracao - Inicio - Robson - 15/11/2000 - Quantidades diferentes por acionador -- */
	float	QuantAlumCarga[4];	   /* Qtd. alumina para cada acionamento do P. F. (Kg) 
									  para cada PF tem uma separada - 15/11/2000 */
/* -- Alteracao - Fim - Robson - 15/11/2000 - Quantidades diferentes por acionador -- */
    /* -- Alteracao - Inicio - 04/06/2002 - Leonel - cadencia de EA na remota -- */
	word16	CadenciaEARemota;		/* cadencia para EA qdo remota fora da rede, em segundos */
	byte	TempoFimAEARemota;		/* Tempo para fim da alimentacao de EA qdo remota fora
									 da rede, em minutos */
    /* -- Alteracao - Fim - 04/06/2002 - Leonel - cadencia de EA na remota -- */
/* -- Alteracao - Inicio - 23/07/02 - Robson - cada quebrador/alimentador tera um tempo diferente - */
	float	TempoQuebrador[NUM_CONJ_ALIM];    /* Tempo de acionamento do quebrador 16b */
	float	TempoAlimentador[NUM_CONJ_ALIM];  /* Tempo de acionamento do alimentador 16b */
/* -- Alteracao - Fim - 23/07/02 - Robson - cada quebrador/alimentador tera um tempo diferente - */
/* -- Alteracao - Inicio - Robson - 03/12/2002 - Tempo para sinalizacao de falta de ruido -- */
	long	TFalhaRuido;					  /* Tempo maximo sem calculo de ruido */
	byte	HabTabPartida;			/* Habilita tratamento de tab. de partida */
	byte	NumTabPartida;			/* Numero da tabela de partida associada a cuba */
//	char	ResParUser[169];
/* -- Alteracao - Fim - Robson - 03/12/2002 - Tempo para sinalizacao de falta de ruido -- */
/* -- Alteracao - Fim - Robson - 02/10/2000 - PF Sala III -- */
/* -- Inicio - Carlos - 24/06/2004 - Algoritmo Sopro Especial -- */
	byte	HabSoproEspec;		/* Habilita algoritmo de sopro especial */
/* --  Fim  - Carlos - 24/06/2004 - Algoritmo Sopro Especial -- */
	byte	UsaRLent;		/* Habilita/desabilita teste ruido lento em quebrada preventiva */
	byte	UsaRRap;		/* Habilita/desabilita teste ruido rapido em quebrada preventiva */
	byte	UsaIncOpe;		/* Habilita/desabilita teste incremento operador em quebrada preventiva */
	byte	UsaAtrasoEa;	/* Habilita/desabilita teste atraso EA em quebrada preventiva */
	byte	UsaMaxEa;		/* Habilita/desabilita teste EAMax em quebrada preventiva */
	
	byte	HabMCruzeiro;	/* Habilita algoritmo de manobra de cruzeiro */
	short int	TMaxPermMCruzeiro;	/* Tempo maximo para permissao de manobra de cruzeiro ativa */
	byte	HabLimMov;		/* Habilita o limitador de movimentacao por grupo */
	byte	NumMovConsec;	/* Numero maximo de movimentacoes consecutivas por grupo */
	byte	GrupoMov;		/* Numero do grupo de movimentacao da cuba */
	float	TenLimCal;		/* Tensao limite de calante para cubas desligadas */
	short int EfeitoTenCal;	/* Tempo de efeito de tensao alta da cuba desligada */
	byte	HabLogMovQueb;		/* Habilita logica de movimentacao antes da quebrada */
	byte	HabContEficMov;		/* Habilitar supervisao de movimentacao por eficiencia */
	byte	EficMovMin;			/* Percentual minimo para considerar movimentacao ok */
	byte	HabCalcHoraQueb;		/* Habilita calculo do horario da proxima quebrada */
	long	IntervQuebProg;		/* Intervalo de quebrada programada */
	long	HoraRefQuebProg;	/* Hora referencia da quebrada programada (horario da primeira quebrada do dia */	
	byte	HabCalcDN;			/* Habilita calculo de derivada negativa */
	long	TEfeitoDN;		/* Efeito da Derivada negativa */
	long	CalcDNQueb;		/* Tempo para iniciar o calculo ante da quebrada */
	long	AlarmeDNQueb;	/* Tempo para alarmar antes da quebrada */
	float	NivelDN;		/* Nivel para definir derivada negativa */
	byte	HabCalcDB;			/* Habilita calculo de derivada baixa */
	long	TEfeitoDB;		/* Efeito da Derivada baixa */
	long	CalcDBQueb;		/* Tempo para iniciar o calculo ante da quebrada */
	long	AlarmeDBQueb;	/* Tempo para alarmar antes da quebrada */
	float	NivelDB;		/* Nivel para definir derivada baixa */
	byte 	LadoRefQueb;	/* Lado de referencia da primeira quebrada */
	short int 	DelayLadoQueb1;	/* Tempo de delay para quebrada do forno */
	short int 	DelayLadoQueb2;	/* Tempo de delay para quebrada do forno */
	byte	HabMovCamTur;	/* Habilita movimentacao de camisa entre turnos */
	byte 	TempoMovCamTur;	/* tempo de movimentacao de camisa entre utrnos */
	byte	NumCiclosForaDB; /* Numero de ciclos acima de DB para cancelar DB */
	float	KPcQueb;		/* Ganho para movimentacao logo apos a quebrada */
	byte	HabPrecMovQueb; /* Habilita logica de precisao de movimento antes da quebrada */
	byte	NumCicRes4s;	/* Numero de ciclos de 4s para analise da movimentacao */
	byte	NumMovPrecQueb;	/* Numero de movimentacoes durante o ciclo de 2m */
	byte	InibeRuiPosCorr;	/*Inibe ruido pos corrida */
	byte 	InibeIncQuebAtrasoEa;	/*Inibe incremento de quebra se forno atrasado */

	char	Reserva[13];
	
//	byte	NCicOscil;		/* Numero de ciclos consecutivos para assumir oscilacao */
//	long	DurIncOscil;	/* Tempo de incremento de oscilacao */
//	float	IncOscil;		/* Incremento de Oscilacao */
//	float	LimMaxOscil;	/* Limite para assumir oscilacao */

	long	HoraRefCorr;	/* Hora de referencia para a corrida */

	byte	Reserva1;	/* Local sujo da memoria */

	float	EaPrevMinAc;	/* Valor minimo para calcular previsao por aceleracao */
	float	EaPrevAc;		/* Aceleracao da resistencia para validar previsao */
	byte	EaPrevCiclosAc;	/* Numero de ciclos com aceleracao alta para validar previsao */

	byte	Reserva2;	/* Local sujo na memoria */

	byte	HabPrevAc;	/* Habilita previsao por aceleracao de resistencia */
	float	DurMovBaixoMinF;	/* Duracao minima de movimentacao para baixo */
	float	DurMovBaixoMaxF;	/* Duracao maxima de movimentacao para baixo */
	float	DurMovCimaMinF;	/* Duracao minima de movimentacao para cima */
	float	DurMovCimaMaxF;	/* Duracao maxima de movimentacao para cima */
	long	TocaSirene;		/* Tempo para tocar sirene tensao alta cuba desligada */
	long	DesligaSala;	/* Tempo para desligar a sala por tensao alta cuba desligada */
	long	IntervSirene;	/* Intervalo de toques da sirene */
	byte 	TSopraChamine;	/* Duracao do sopro da chamine */
	byte	IntervSoproQueb;	/*Intervalo entre quebrada e sopro */
	byte 	TSinalizaSopro;	/* Duracao do primeiro sopro para sinalizar sopro de chamine */
	byte	IntervSinalSopro;	/* Intervalo entre a sinalizacao de sopro e o sopro */
	int		LadoQuebIdx;	/* Identifica o lado da quebrada programada */
	byte	InverteIdx;		/* Inverte lado da quebrada para dias pares em numero de queb impar no dia */

//	char	ResParUser[21];
	byte	TAcresBSupMovel;	/* Tempo antes da proxima quebra para iniciar a Banda Movel */
	float	AcresBSupMovel;		/* Acrescimo total da Banda superior */
	byte	HabKbpCorrida;	/* Habilita uso de equivalente motor exclusivo para corrida */
	byte	InibeQPQuebProg;	/* Inibe a QP minutos antes da quebra programada */
	byte	HabSmartFeed;		/* Habilita logica de SmartFeed */
	float	SF_KSIncDeriv;		/* Suavizador de inclinacao de derivada */
	short int	LimQPrevEaAtraso;	/* Limite inferior para qp apos atraso de EA */
	float	SF_SUFeed;		/* Limite para considerar forno em SUnderFeed */
	float	SF_UnderFeed;		/* Limite para considerar forno em UnderFeed */
	float	SF_NormalFeed;		/* Limite para considerar forno em NormalFeed */
	float	SF_OverFeed;		/* Limite para considerar forno em OverFeed */
	float	SF_PassoAcima;		/* Tempo para passo do SmartFeed para cima */
	float	SF_PassoAbaixo;		/* Tempo para passo do SmartFeed para Baixo */ 	
	float	SF_LimMovCima;		/* Tempo maximo do SmartFeed para cima */ 	
	float	SF_LimMovBaixo;		/* Tempo maximo do SmartFeed para Baixo */ 	
	byte	HabMovSmartFeed;	/* Habilita movimentacao logica de SmartFeed */
	byte	NQuebInibida;		/* Numero da quebrada programada que sera inibida */
	byte	NQuebLogica;		/* Numero de quebradas da logica */
	byte	NQuebPassadas;		/* Numero de quebradas passadas da logica */
	byte	HabAEK;				/* Habilta logica de eliminacao de EA alternativa as tabelas */
	byte	AEK_TEspera;			/* Tempo de espera por voltagem alta de EA */
	byte	AEK_TMoveCima;		/* Tempo de movimentacao para cima em caso EA baixo */
	byte	AEK_TMoveBaixo;		/* Tempo de movimentacao para baixo apos tparar */
	byte	AEK_TParar;			/* Tempo para parar apos atingir tensao alta */
	byte	AEK_MaxMoveCima;	/* Numero maximo de movimentacoes para cima */
	byte	TMovCamCorr;		/* Numero horas para subir camisa apos corrida */
	byte	HabPulaQuebProg;	/* Sinaliza pulo de queb programada em caso de ea ou qp */
	byte	IntQPQProg;			/* Intervalo minimo entre qp e queb prog */
	byte	IntEAQProg;			/* Intervalo minimo entre ea e queb prog */
	byte	MaxPassaQueb;		/* Numero de maximo de quebras programadas passadas */
	float	DifResAgarraCamisa;	/* Resistencia de agarramento de camisa */ 	
	long	TMaxDesvio;			/* Tempo maximo aceitavel de desvio de tensao antes de tocar a sirene */
	byte	AEK_ForcaSubidas;		/* Forca subidas apos AEK atingir 30V */
	short int	TForcaDesce;	/* Tempo para descida apos subidas forcadas */
	float	VForcaDesce;		/* Tensao minima para forcar descida ao final do AEK */
	byte	AEK_InibeTerminal;	/* Inibe movimentacao por terminal durante EA */
	byte	AEK_TFMoveBaixo;		/* Tempo de movimentacao para baixo apos tparar */
	short int	TVerTensao;	/* Tempo para verificar tensao apos descidas forcadas aek */
	long	IntervMinTPinos;	/* Tempo minimo entre incrementos de levantamento de pinos */	
	byte	AtivaBitCLP;		/* Ativacao do bit de comunicacao CLP New Soderberg */
	short int	AlF3Dia;		/* Carga de fluoreto a ser adicionada no dia New Soderberg */
	float	QuantAlF3Carga[2];	/* Carga por alimentacao de fluoreto */
	long	DataAlF3;			/* Data da carga de fluoreto */
	byte	NumSiloAlF3;		/* Numero de silos de AlF3 do forno */
	byte	BitAlF3[2];			/* Bit a sererm acionados para adicao de fluoreto */
	byte	BitAl2O3[2];		/* Bit a ser acionado para adicao de alumina */
	byte	HabCamSimul;		/* Ativa subida de camisa simultanea a movimentacao de anodo corrida */
	byte	NQuebAtraso;		/* Numero da quebra atrasada */
	byte	HabEsperaQP;		/* Ativa logica de espera de qp */
	byte	NQuebForcaEA;		/* Numero da quebra atrasada para forcar ea */
	byte	HabOverPadrao;		/* Habilita over e under no modo padrao */
	float	CoefAngOver;		/* Coeficiente Angular para entrar em over */
	float	CoefCorrOver;		/* Coeficiente Correlacao para entrar em over */
	byte	NCicOverPadrao;		/* Numero de ciclos para entrar em over padrao */
	float	CoefAngUnder;		/* Coeficiente Angular para entrar em over */
	float	CoefCorrUnder;		/* Coeficiente Correlacao para entrar em over */
	byte	NCicUnderPadrao;		/* Numero de ciclos para entrar em over padrao */
	byte	NCicNormPadrao;		/* Numero de ciclos para entrar em over padrao */
	byte	HabDobraPF;			/* habilita dobra PF*/
	byte	LadoDobraPF;		/* Lado da dobra PF */
	byte	NumDobraPF;			/* Numero de vezes de dobra PF */
	byte	TFalhaAlim;			/* Tempo de Falha De Alimentqacao*/
	long	TIntAlF3;			/* Tempo de intervalo para adicao total do fluoreto */
	long	HoraIniAlF3;		/* Hora do dia para inicio da adicao de fluoreto */
	int		IdxQuebMix;			/* Identificador de quebra mix */
	long	IntervQuebMix;		/* Intervalo da quebra mix */
	
//	char	ResParUser[0];   // 512 + 128 = 640   - Expansao 13/11/14 - Red 2 CBA
  } t_par1_user;

typedef
  volatile struct par2_user_avc /* 2a. tabela de parametros da Cba */
  {
	byte	HabIncOscil;		/* Habilita tratamento de oscilacao */
	byte	NCicCoefAng;		/* Numero de ciclos para calculo de coeficiente angular */
	byte	HabCalcCoefAC;		/* Habilita calculo do coeficiente angular */
	byte	HabExcUsuPF;		/* Habilita modulo excecao usuario */

	byte	HabilitaPFCBA;		/* Habilita logica EA Soderberg Futuro */
	short int	TSuspTemp;			/* Tempo de suspensao temporaria em caso de excecao */
	short int	TMinBaseF;			/* Tempo de duracao do base feed */
	byte	SOverInicial;		/* Habilita super over incial no overfeed */
	float	TaxaOverA;			/* Taxa de overfeed A */
	float	TaxaOverB;			/* Taxa de overfeed B */
	float	TaxaUnderA;			/* Taxa de underfeed A */
	float	TaxaUnderB;			/* Taxa de underfeed B */
	short int	TOverF;				/* Tempo de duracao do overfeed */
	short int	TMaxUnderA;			/* Tempo de duracao do underfeed A */
	short int	TMaxUnderB;			/* Tempo de duracao do underfeed B */
	byte	SuspEA;				/* Habilita Suspensao de alumina apos EA */
	float	CAFimUnder;			/* Coeficiente angular para fim de underfeed */
	float	CCFimUnder;			/* Coeficiente correlacao para fim de underfeed */
	float	DifResFimUnder;		/* Diferenca de resistencia para fim de underfeed */
	float	DeltaRFimCheck;		/* Delta de resistencia para finalizar o check */
	short int	TSOverInicial;		/* Tempo de super over incial no overfeed */
	short int	TLibMovOver;	/* Tempo para liberacao de movimentacao no over */
	short int	TInibMovUnder;	/* Tempo para inibicao de movimentacao no under */

	float	LimOscilFrac;		/* Limite de Oscilacao fraca */
	float	LimOscilFort;		/* Limite de Oscilcao forte*/
	byte	IntervCalcCA;		/* Intervalo de calculo de CA e CC */
	byte	BitDuploOver;		/* Bit para acionamento duplo do pistao quebrador */
	short int	TLibMovUnderB;	/* Tempo para liberacao de movimentacao no final do under B */
	float	TempMaxInibInc;		/* Temperatura maxima para inibir incrementos */
	byte	InibIncQuebTemp;	/* Inibe incremento de quebra por temperatura alta */
	byte	InibIncOscTemp;		/* Inibe incremento de oscilacao por temperatura alta */
	byte	InibIncTpTemp;		/* Inibe incremento de troca de pinos por temperatura alta */
	byte	InibIncOpTemp;		/* Inibe incremento de operacao por temperatura alta */
	byte	InibIncRRTemp;		/* Inibe incremento de ruido rapido por temperatura alta */
	byte	MinNCicCA;			/* numero minimo de ciclos para calcular CA */
	byte	TAlarmeCheck;		/* Tempo em minutos para alarmar check */

	byte	HabAEKPF;			/* Habilita AEK PF */
	byte	IntMovCimaAEKPF;	/* Intervalo de movimentacao para cima AEKPF */
	byte	IntMovBaixoAEKPF;	/* Intervalo de movimentacao para baixo AEKPF */
	byte	MaxDeltaTBaixo;		/* Tempo maximo de delta de intervalo para baixo */
	byte	TMovCimaAEKPF;		/* Tempo de movimentacao para cima AEKPF */
	byte	TMovBaixoAEKPF;		/* Tempo de movimentacao para baixo AEKPF */

	float	TaxaOverAEK;		/* Taxa de Alimentacao durante AEK */
	byte	TIniAlimAEK;		/* Tempo apos inicio EA para comecar a alimentar */
	
	byte	TMinOverEA;			/* Tempo minimo de over EA */

	byte	TLibAlarmeOver;		/* Tempo para ativar o alarme de tendencia de over */
	float	TendMaxOver;		/* Valor maximo para tendencia de resistencia em overfeed */	

	byte	CamisaPFAuto;		/* Habilita ajuste automatico de camisa com potenciometro */
	byte	TMovCamPF;			/* Tempo de movimentacao em caso de camisa baixa */
	long	TMaxAjCamPF;		/* Tempo maximo apos a corrida em que se pode corrigir */
	byte	NMaxMovCamPF;		/* Numero maximo de movimentacoes de camisa para ajuste */

	byte	NCCOscil;			/* Numero de ciclos de controle para regulacao com oscilacao */
	byte	NCRegOscil;			/* Numero de ciclos de regulacao para tratar oscilacao */
	float	IncOscilFra;		/* Step de incremento para oscilacao fraca */
	float	IncOscilFor;		/* Step de incremento para oscilacao forte */
	float	DecrOscil;			/* Decremento de oscilacao no final */
	float	MaxIncOscil;		/* Maximo de incremento de oscilacao */
	short int	TOverCorr;		/* Tempo de duracao do overfeed em caso corrida */
	byte	TipoIncPadrao[6];	/* Tipo de incremento padronizado */
	short int	DurIncPadrao[6];	/* Duracao de incremento padronizado */
	float	VIncPadrao[6];	/* Tensao de incremento padronizado */
	byte	InibIncQuebDB; /* Inibe Incremento e Movimentação em Quebra quando em DB */
	byte	HabInibeQPposDB; /* Inibe QP quando em DB */
	long	TInibQPposDB;	/* Tempo de Inibição de QP pos DB */
	long	TEfeitoInibeMovDB;	/* Tempo de Inibição de Mov apos quebra */
		
//	char	ResParUser[502];
//	char	ResParUser[476];   // 512 + 128 = 640   - Expansao 13/11/14 - Red 2 CBA	
	char	ResParUser[458];   // 476 -  18 = 458   - 2 bytes, 2 longs: Inibição de IncQueb e QP em DB
  } t_par2_user;

/* -- Tabelas de variaveis de trabalho -- */
typedef
  volatile struct user_avc1 /* 1a. tabela de variaveis de trabalho da Cba no AVC */
  {
	byte	EstadoAlimAtual; /* Qual estado atual */
	byte	EstadoAlimAnt;	 /* Estado anterior */
	byte	InicioAlgAtual;  /* Sinaliza inicio de um estado */
	int		TempEstAtual;	 /* Quanto tempo esta no estado atual */
	float	QtAAlimEstAtual; /* Quant. de alumina alim. no estado atual */
	long	HoraIniEstAtual; /* Hora de inicio do estado */
	byte	State;			 /* Sub estado do estado atual */
	byte	InicioSubEst;	 /* Sinaliza inicio de subestado */
	long	HoraIniSubEstAtual; /* Hora de inicio mudanca de subestado */
	float	IntervCurr;		 /* valor do intervalo de corrente a ser integrado p/ acionamento do PF */
    float	EfiCurr;		 /* Eficiencia de Corrente da linha (0-1) */
    float	Integral;		 /* integral da corrente */
    int		NumAciona;		 /* numero de acionamentos do point feeder */
    float	ConcCheckAnt;	 /* concentracao do ultimo ciclo de check */
    float	ConcCheckAtual;	 /* concentracao do ciclo de check atual */
    long    HoraFimCheck;    /* Hora de termino do check */
    long    HoraUltCheck;    /* Hora de inicio do check */
    float   ResAlim;         /* Resistencia filtrada (alimentacao) */
    float   DerResAlim;      /* Derivada da resistencia filtrada (alimentacao) */
    short int NumOverCheck;  /* Numero de overfeeds no check corrente */
    long    HoraUltPF;       /* Hora do ultimo acionamento do Point Feeder */
    byte    PrevState;       /* Subestado anterior */
    float   FornecSubEst;    /* Quantidade de alumina fornecida no subestado atual */
    float   ConsumoSubEst;   /* Quantidade de alumina consumida no subestado atual */
    long    TempoSuspende;   /* Tempo de alimentacao suspensa */
	long    DurInibeControle;/* Tempo em que a movimentacao ficou inibida (relatorio instantaneo) */
    byte	HabilitaPFAnt;	 // Estado anterior do flag HabilitaPF
	float	IntPar;			 //integral parcial
    float	Consumo;		 //acumula o consumo de alumina entre amostras de resistencia (derivada)
    float	alvo;			 //massa alvo de alumina (controla tempo de under/over)
    float	Resistencia[4];  //buffer circular p/ armazenar valores da resistencia (derivada)
    short	int ResIndex;	 //usado como indice do buffer circular
    byte 	Preenchido;		 //flag que indica que buffer de resistencias esta preenchido
    float	Conc[5];		 //concentracoes referentes a cada uma das derivadas obtidas
    float	ConcDer;		 //concentracao da cuba calculada pela derivada
    float	Deriv[5];		 //derivadas coletadas para o calculo da concentracao
    short	int DerIndex;	 //usado como indice do vetor de derivadas
    float	UnderProg;		 //valor do underfeed progressivo
    long 	IniEtapaUnder;	 //inicio da etapa de underfeed (underfeed progressivo)
    double	ResFilt;		 //resistencia filtrada auxiliar
    float	DerResAlimAnt;	 //derivada de alimentacao anterior 
	byte	ConcBaixa;		 //flag que indica se entrou em overfeed devido aa derivada muito alta

    /* variaveis especificas do algoritmo de alimentacao c/ barra quebra crosta */
	int     QuebSubEst;      /* Numero de quebradas no estado atual */
	int     NumQueb;		 /* Numero de quebradas computadas (utilizado para suspender alimentacao */
    byte	HabilitaBarraAnt;/* Estado anterior do flag HabilitaCB */
    long    HoraUltQPrev;    /* Hora ultima quebrada preventiva */
    long    ContInibQPrev;   /* Cont. p/ controle inib. queb. prev. operacao */
	long	ContDurQPrev;		 /* Contador de duracao de quebrada preventiva */
	short int NumQuebPrev;   /* No. quebradas preventivas solicitadas */
	short int NumPrevQPrev;  /* No. previsoes terminadas por queb. preventiva */
    float	ContTAjAcum;	 /* Contador de Tempo de ajuste acumulado */
    float	ContTAjCam;		 /* Contador de Tempo de ajuste */
	int		ContInibAjCam;	/* Inibe ajuste camisa pelo numero de ciclos indicado */
	int		ContMovCorr;	/* para ajuste do anodo durante a corrida */
/* -- Alteracao - Inicio - Robson - 02/10/2000 - PF Sala III -- */
	byte	PassoCadencia;   /* Numero do passo que ira ser executado para alimentacao */
/* -- Alteracao - Fim - Robson - 02/10/2000 - PF Sala III -- */
	byte	PassoAtualTPartida;	/* passo atual na tabela de partida de cuba */
	long	HoraIniEsperaTPartida; /* hora de inicio do passo de espera */
	float	EaVoltLimTabPartida;	/* Limite para deteccao de Ea durante execucao tab. partida */
/* -- Inicio - Carlos - 24/06/2004 - Algoritmo Sopro Especial -- */
//	char	ResUserAvc[22];
	byte	EstadoSoproEspec;	 /* Status algoritmo sopro especial */
	int		ContCicSoproEspec;	 /* Contador de ciclos de sopro especial */
	int		ContEsperaSoproEspec;/* Contador ciclos de espera sopro especial */
	short int	Vida;			/* Contabiliza a vida do forno */
	float 	RrapCContValp;		/* Ruido rapido em pico ohms */
	float 	RlentCContValp;		/* Ruido lento em pico ohms */
	byte	NumDB;				/* Numero de DB entre efeitos */
	byte	NumQuebProg;			/* Numero de quebradas entre efeitos */

	byte	AdFluoreto;			/* Adicao semanal de fluoreto */

//	char	ResUserAvc[1];  /* Esgotado */
/* --  Fim  - Carlos - 24/06/2004 - Algoritmo Sopro Especial -- */

	float	BandaSupMovel;		/* Acrescimo de Banda morta por ciclo de controle */
	byte	PulouQuebProg;		/* Detecta pulo de quebra programada para BSupMovel */
	float	EqMotorCorrB;		/* Equivalente motor de corrida para baixo */
	float	SF_IncDeriv;		/* Inclinacao da derivada no periodo entre quebras */
	float	SF_IncDerivEA;		/* Media da inclinacao da derivada entre EA */
	float	SF_TempoSobe;		/* Tempo de subida de anodo no smartfeed */
	byte	AtrasouEa;			/* Atrasou EA no ultimo ciclo */
	float	SF_IncDerivAnt;		/* Inclinacao da derivada no periodo entre quebras */
	byte	SF_Posicao;			/* Posicao atual do SmartFeed */
	byte	QuebrouDB;			/* Indica quebra realizada quando forno em derivada baixa */
	long	HoraUltMovCam;		/* Horario da ultima movimentacao automatica de camisa */
	byte	ContPassaQueb;		/* Contador de quebras passadas */
	unsigned int		StatusEv;	/* Envio de condições de eventos para o PI */
	byte	RetornoAlF3;		/* Retorno de alimentacao de fluoreto */
	byte	RetornoAl2O3;		/* Retorno de alimentacao de alumina */	
	long	HoraEsperaQP;		/* Hora inicio da espera QP */
	byte	TipoOscil;			/* Indica tipo de oscilacao no forno */
	float	CoefAngDeriv;			/* Coeficiente Angular da Derivada de RSuaveDerivH */
	float	AEKVMax				/* Tensão Máxima do AEK */

	char	ResUserAvc[12];        // 256 + 64  = 320   - Expansao 13/11/14 - Red 2 CBA
  } t_user1_avc;

typedef
  volatile struct user_avc2 /* 2a. tabela de variaveis de trabalho da Cba no AVC */
  {
/* -- Alteracao - Inicio - Robson - 19/10/00 - inclusao das variaveis de supervisao do novo PF -- */
	long    TQuebInib[NUM_CONJ_ALIM];     /* Tempo instantaneo em que o quebrador da cuba permeneceu inibido */
	long    TAlimInib[NUM_CONJ_ALIM];     /* Tempo instantaneo em que o alimentador da cuba permeneceu inibido */
/* -- Alteracao - Fim - Robson - 19/10/00 - inclusao das variaveis de supervisao do novo PF -- */
/* -- Alteracao - Inicio - Leonel - 21/11/2000 - PF Sala III -- */
	byte	HabQuebOp[NUM_CONJ_ALIM];		/* habilita quebradores */
	byte	HabAlimOp[NUM_CONJ_ALIM];		/* habilita alimentadores */
/* -- Alteracao - Fim - Leonel - 21/11/2000 - PF Sala III -- */
/* -- Alteracao - Inicio - Robson - 03/12/2002 - Tempo para sinalizacao de falta de ruido -- */
	long	TIniFalhaCalcRuido;				/* Hora inicial da falha de calculo de ruido */
//	char	ResUserAvc[224];
//	char	ResUserAvc[216];
	byte	ContEvChaves;
	long	HoraTenCal;		/* Hora da ultima medida de tensao alta de calante */

	float 	Rinst_atnca;	/* Resistencia instantanea da cuba calculada com a corrente da ATNCA */
	float	Res_2m_atnca;			/* Resistencia de 2 minutos calculada com a corrente da ATNCA */
	float	Res_2m_ant_atnca;	/* Resistencia de 2 minutos do ciclo anterior ATNCA */

	short int 	VRLentCCont;		/* Tensao de oscilacao de ruido lento */
	short int	VRRapCCont;			/* Tensao de oscilacao de ruido rapido */

	float	SigmaS_2m;		/* Ruido rapido calculado em funcao de sigmas */
	float 	SigmaL_2m;		/* Ruido lento calculado em funcao de sigmas */
	long	HoraProxQueb;	/* Hora da proxima quebrada programada */
	long	HoraUltQueb;	/* Hora da proxima quebrada programada */
	long	HoraProxQuebReal;	/* Hora da proxima quebrada programada com delay*/
	long	HoraUltQuebReal;	/* Hora da proxima quebrada programada com delay*/
	long	HoraForaDB;			/* Hora da ultima derivada acima da derivada baixa */
	double	MediaDN;		  /* Media movel da derivada negativa */
	short int	NumCiclosDN;  /* Numero de ciclos para calculo da media movel */
	byte	TMovCamAcumTur;	  /* tempo acumulado de movimentacao entre turnos */
 	long	HoraUltMovPainel;	/* Hora da ultima movimentacao por painel */
	long	HoraPrecMovQueb;		/* Hora do ciclo que atua a precisao de movimentacao */
	
	char	RESERVA[2];	  /* Numero de cliclos consecutivos de oscilacao */
//	short int	NumOscil;	/* Numero de cliclos consecutivos de oscilacao */

	long	HoraIncOscil;	/* Hora de inicio da oscilacao */
	float	IncOscil;		/* Incremento de oscilacao */

	char	RESERVA1[2];	  /* Numero de cliclos consecutivos de oscilacao */
//	short int 	ContIncOscil;	/* Numero de ciclos de incremento de oscilacao */

	long	HoraUltCorr;	/* Hora da ultima corrida */

	float	DerivHTeste;	/* Teste da Derivada */

	float 	IncFormaBanho;	/* Incremento de Formacao de banho */
	long	DurFormaBanho;	/* Duracao da formacao de banho */
	long	HoraIniFormaBanho;	/* Hora do inicio da formacao de banho */
	long	HoraEvQuebrada;	/* Hora do ultimo evento de quebrada */

	byte	CiclosIniPrevAc;	/* Contagem de ciclos com previsao Ac */
	float	RSuavePrevAc[5];	/* Historico da derivada para calculo de previsao Ac */	
	float	RSuaveDerivHAnt;	/* Derivada Historica do ciclo anterior */
	long	HoraSireneCunha;	/* Hora inicio toque sirene */
	long	HoraContSirene;		/* Hora contagem para acionar sirene */
	byte	SubiuCamisa;		/* Indicador se subiu camisa no ciclo anterior */
	float	UltRCicCont;		/* Resistencia na movimentacao de camisa */ 	
	short int	TMovCamTur;			/* Druacao de subida  de camisa */ 	
	byte	NumMovCamTur;		/* Numero de subidas de camisa */	
	short int 	TotalAcionaAlF3;	/* Numero de acionamentos necessarios de fluoreto no dia */
	long	IntervAlF3;			/* Intervalo entre adicoes de alf3 */
	long	HoraUltAlF3;		/* Hora da ultima adicao de alf3 */
	float	Oscilacao;		/* Registra oscilacao do intervalo */
	float 	CoefAng;		/* Coeficiente angular da resistencia */
	float	CoefCor;		/* Coeficiente de correlacao da resistencia */
	float	TaxaFeedPF;		/* Taxa de Alimentacao point feeder */
	byte	NCicOverPadrao;	/* Numero de ciclos para acionar over padrao */
	byte	NCicNormPadrao;	/* Numero de ciclos para acionar over padrao */
	byte	NCicUnderPadrao;	/* Numero de ciclos para acionar over padrao */
	long	HoraUltAlim;		/* indica hora do ultimo pPF */
	byte	ContCabPF;			/* Conta cabeceira de dobra pf */

	byte	HabilitaPFCBAAnt;	/* Verifica se PFCBA estava habilitado no ciclo anterior */
	long	HoraUltQuebCab;		/* Hora da ultima quebra de cabeceira */

	char	RESERVA2[18];		/* RESERVA - TRANSFERIDO P AVC3*/
	byte	TipOscilReg[6];
	short int	EstadoPFCBA;		/* Indica estado atual de alimentacao */
	
	char	RESERVA3[27];		/* RESERVA - TRANSFERIDO P AVC3*/
	short int	DurEstadoAtual;		/* duracao programada do estado atual */
	float	ResInicialUnder;	/* Resistencia no inicio do underfeed */
	float	ResMinCheck;		/* Resistencia minima de check */
	byte	EstFeedAnt;			/* Estado de Alimentacao Antereior */
	float	ResScore2m;			/* Resistencia calculada no mcp cba user */
	float	ResScore2m_ant;		/* Resistencia do ultimo ciclo de controle */	

	byte	NumMovCamPF;		/* Numero de movimetacoes de camisa */

	char	RESERVA4[19];		/* RESERVA - TRANSFERIDO P AVC3*/
	

//	char	ResUserAvc[75];
//	char	ResUserAvc[97];   // 256 + 64  = 320   - Expansao 13/11/14 - Red 2 CBA 
/* -- Alteracao - Fim - Robson - 03/12/2002 - Tempo para sinalizacao de falta de ruido -- */
  } t_user2_avc;

typedef
  volatile struct user_avc3 /* 3a. tabela de variaveis de trabalho da Cba no AVC */
  {

	char	RESERVA[4];	  /* Numero de cliclos consecutivos de oscilacao */
//	short int NCicOscilFrac;	/* Numero de ciclos consecutivos de oscilacao fraca */
//	short int NCicOscilFort;	/* Numero de ciclos consecutivos de oscilacao forte */

	float	Temperatura;		/* Temperatura atual do forno */
	int		ContInibeIncQueb;		/* Conta inibicao de incremento de quebra */
	short int	ContHistResCA;		/* Conta buffer de resistencias do calculo de CA */
	float	HistResCA[20];		/* Buffer de resistencias do calculo de CA */
	float	FatorFeedRate;		/* Fator temporario de ajuste de feedrate */
	long	TFatorFeedRate;		/* Tempo de uso do fator de ajuste do feedrate */
	long	HoraUltTPinosAnt;	/* Hora alterior a ultima troca de pinos */

	long	HoraEstAtual[9];	/* Hora de inicio do estado de alimentacao */
	float	CargaEst[9];		/* Carga atual do estado de alimentacao */
	long	TEstFeed[9];		/* Tempo do estado de alimentacao */
	
	float 	DifCoefAng;			/* Diferenca do ultimo coeficiente angular */
	float	DifCoefCor;			/* Diferenca do ultimo coeficiente de correlacao */

	byte	EstForcaAlim;		/* Estado forcado de alimentacao */

	float	TendResOver;		/* Tendencia da resistencia em overfeed */
	short int	ContCicOver;	/* Conta numero de ciclos 2m em overfeed */
	

//	char	ResUserAvc[256];
	char	ResUserAvc[91];   // 256 + 64  = 320   - Expansao 13/11/14 - Red 2 CBA
  } t_user3_avc;

typedef
  volatile struct user_avc4 /* 4a. tabela de variaveis de trabalho da Cba no AVC */
  {
//	char	ResUserAvc[256];
	char	ResUserAvc[320];   // 256 + 64  = 320   - Expansao 13/11/14 - Red 2 CBA
  } t_user4_avc;

/* -- Tipo de dados da tabelas da Cba para o SUPERVISAO AVC -- */
/* ATENCAO : Esta tabela nao deve ter suas reservas ultrapassadas */

/* Tabela de variaveis de supervisao diaria e de turno por cuba */
typedef
  volatile struct sup_usu_avc /* tabela de variaveis de supervisao no SUPERV_AVC */
  {
	/* -- Variaveis de supervisao - Alimentacao Cba -- */
	float	QtdAlumina;		 /* Qtd total de alumina alimentada na cuba (g) */
	float   QtdAluminaPadrao;/* Qtd de alumina fornecida em alimentacao Padrao */
	float   QtdAluminaEA;    /* Qtd de alumina fornecida em alimentacao de Efeito Anodico */
	float   QtdAluminaExc;   /* Qtd de alumina fornecida em alimentacao de Excecao */
	long    TAlimPadrao;     /* Tempo em que a cuba permeneceu em alimentacao Padrao */
	long    TAlimEA;         /* Tempo em que a cuba permeneceu em alimentacao de EA */
	long    TAlimSusp;       /* Tempo em que a cuba permeneceu em alimentacao Suspensa */
	long    TAlimExc;        /* Tempo em que a cuba permeneceu em alimentacao de Excecao */
	long    TInibeControle;  /* Tempo em que a movimentacao do anodo ficou inibida */
	long    TManAlimLoc;     /* Tempo em que a alimentacao permaneceu em manual local */
	long    TManAlimRem;     /* Tempo em que a alimentacao permaneceu em manual remoto */
	long    TManAlim;        /* Tempo em que a alimentacao permaneceu em manual */
	long    TAutoAlim;       /* Tempo em que a alimentacao permaneceu em automatico */

    /* variaveis do algoritmo de alimentacao c/ barra quebra crosta */
	int		NumQuebPadrao;
	int		NumQuebEA;
    long    TempoInibQPrev;		/* Tempo de inibicao de quebrada preventiva */
	short int NumTabEliEaNInt;	// Num. tab. de elim. de EA executadas sem interrupcao externa
	short int TabEliEaSucesso;	// Num. tab. de elim. de EA que terminaram com a eliminacao do EA
	short int NumQuebPrev;   /* No. quebradas preventivas solicitadas */
	short int NumPrevQPrev;  /* No. previsoes terminadas por queb. preventiva */
	long	ContDurQPrev;		 /* Contador de duracao de quebrada preventiva */

	/* -- Todos dados dentro da struct CNF_SUP sao gravados por programa de configuracao -- */ 	
	t_cnf_sup CNF_SUP;

//	struct {
//		/* -- Novos dados p/ relatorio via Coletor CBA sala 64kA -- */
//		float	Banho;			// dados em cm (media)
//		float	Metal;			// dados em cm (media)
//		int		Temperatura;	// em C (media)
//		int		Producao;		// em Kg/F (totalizacao)
//		int		BanhoFrio;		// em lado A,B ou AB (totalizacao)
//		int		CrioSint;		// em sacos (totalizacao)
//		int		CrioAciq;		// em sacos (totalizacao)
//		int		CrioRecu;		// em Kg (totalizacao)
//		int		Fluoreto;		// em sacos (totalizacao)
//		int		Fluorita;		// em sacos (totalizacao)
//		int		Barrilha;		// em sacos (totalizacao)
//
//		short	OperarTurno;	// numero do turno (totalizacao)
//		short	Carvao;			// S/N (totalizacao)
//		short	Atrasado;		// S/N (totalizacao)
//		short	FundoSujo;		// S/N (totalizacao)
//		short	Acidez;			// A(Acido),N(Normal) ou B(Baixo) (totalizacao)
//		short	FornoAbrindo;	// A,B ou AB (totalizacao)
//
//		float	VazioPasta;		// cm (media)
//		float	Desfilamento;	// cm (media)
//		float	AlturaAnodo;	// cm (media)
//		float	Flanco;			// cm (media)
//		float	QuedaCatodica;	// mV (media)
//		float	QuedaAnodica;	// mV (media)
//	} CNF_SUP;

/* -- alteracao - inicio - 11/09/00 - Robson - Inclusao tratamento do Atn8 -- */
	short unsigned int ErrorADAtn8[MAX_VALORES_POR_ATN8]; /* Erros de leitura de analogicas de cuba */
/* -- alteracao - fim - 11/09/00 - Robson - tratamento do Atn8 -- */

/* -- Alteracao - Inicio - Robson - 19/10/00 - inclusao das variaveis de supervisao do novo PF -- */
	long    TQuebInib[NUM_CONJ_ALIM];     /* Tempo instantaneo em que o quebrador da cuba permeneceu inibido */
	long    TAlimInib[NUM_CONJ_ALIM];     /* Tempo instantaneo em que o alimentador da cuba permeneceu inibido */
/* -- Alteracao - Fim - Robson - 19/10/00 - inclusao das variaveis de supervisao do novo PF -- */

/* -- Inicio - Carlos/Rogerio - 10/01/2007 - Relatorio de previsao de EA -- */
	short int NumEaQPrev;  /* No. de EA ocorridos durante queb. preventiva */
/* -- Fim - Carlos/Rogerio - 10/01/2007 - Relatorio de previsao de EA -- */
	float   ApMovBaixoDia;
	float	ApMovCimaDia;
	short int FalhaMovBaixoDia;
	short int FalhaMovCimaDia;

	float	SigSNormDia;	/* media de ruido sigma short no dia */
	float	SigLNormDia;	/* media de ruido sigma long no dia */
	float	ICubaMedDia;	/* media da corrente da cuba no dia */

	float 	kwcimafalhamov;		/* integra potencia disperdicada por falhamov */
	float 	kwbaixofalhamov;	/* integra potencia disperdicada por falhamov */
	float 	kwcimaforarede;		/* integra potencia disperdicada por fora de rede */
	float	kwbaixoforarede;	/* integra potencia disperdicada por fora de rede */
	float	kwcimamanuallocal;	/* integra potencia disperdicada por manual local */
	float	kwbaixomanuallocal;	/* integra potencia disperdicada por manual local */
	float	kwcimageral;		/* integra potencia disperdicada geral */
	float	kwbaixogeral;		/* integra potencia disperdicada geral */
	short int	NumQuebPrevDia;	/* Soma numero de qprevs no dia */
	byte	NumDBDia;			/* Numero de derivada baixa no dia */

	byte	NumOscilDia;	/* Numero de tratamentos de oscilacao dia */
	float	IncOscilDia;	/* Incremento de oscilacao do dia*/
	long	DurIncOscilDia;	/* Duracao total de incrementos de oscilacao dia */	

	long	IntervCorrDia;	/* Intervalo entre as corridas */
	byte	FormaBanho;		/* Indica que a cuba formou banho */
	long	IntervRefCorrDia;	/* Intervalo de corrida em relacao a referencia */
	long	DurIncFBDia;	/* Duracao total de incremento de formacao de banho dia */
	float	IncFBDia;		/* Incremento de Formacao de banho do dia */
	long	IntervRefQuebDia;	/* Intervalo de quebrada em relacao a referencia */
	byte	NumQuebProgDia;	/* Numero de quebradas programadas no dia */
	byte	NumDBConsec;	/* Numero de derivadas baixas consecutivas */
	byte	NumDBQueb;		/* Numero de derivadas baixas que foram quebradas */
	float	DifALFalhaMov;	/* Diferenca entre alvo e liquida por falha de mov */
	float	DifALBandaMorta; /* Diferenca entre alvo e liquida dentro da BM */
	float	DifALInibPrev;	/* Diferenca entre alvo e liquida por inib. prev. */
	float	DifALInibQueb;	/* Diferenca entre alvo e liquida por inib. queb. */
	float	DifALIntervMov;	/* Diferenca entre alvo e liquida por intervalo mov. */
	float	DifALManual;	/* Diferenca entre alvo e liquida por forno em manual */
	float	DifALInibUsu;	/* Diferenca entre alvo e liquida por inibicao usuario */
	float	DifALDesvio;	/* Diferenca entre alvo e liquida por Desvio de Tensao */
	float	EaVMax;			/* Tensao Maxima de efeito no final do ea */
	byte	TotalEA24h;		/* Totalizador de EA menor que 24h */
	float	DeltaRCorr;		/* Delta Resistencia de corrida */
	byte	AgarraCam;		/* Totalizador de agarramento de camisa */
	float	ALF3Fornecido;	/* Totalizador de ALF3 no dia */
	int		NumAcionaAlF3;		 /* numero de acionamentos do point feeder FLUORETO*/
	int		NumAciona;		 /* numero de acionamentos do point feeder alumina*/
	short int	NumTendOverDia;	/* Numero de alarme de tendencia positiva de overfeed dia */
	
	long	TempoUnder;		/* Medida de tempo que o forno ficou em underfeed */
	short int	NUnderDia;	/* Numero de vezes que o forno entrou em under no dia */
	short int	NOverDia;	/* Numero de vezes que o forno entrou em under no dia */
	float	PicoUnder;		/* Valor maximo de resitencia ao final do under */
	float	PicoOver;		/* Valor minimo de resitencia ao final do over */
	float	OscilacaoDia;	/* Acumulado da oscilacao do dia */
	float	CoefAngDia;		/* Acumulado do coeficiente angular dia */
	short int	NumCCtrl1mDia; 	/* Conta numero de ciclos de controle de 1m no dia */


//	byte	ResUsuario[558];	/* Area disponivel para variaveis do usuario */
	byte	ResUsuario[732];    // 880 + 224 = 1104  - Expansao 13/11/14 - Red 2 CBA - Area disponivel para variaveis do usuario
  } t_sup_avc_usu;

/* -- Tipo de dados da tabela de variaveis de estado da Cba - EST_AVC -- */
/* ATENCAO : Esta tabela nao deve ter suas reservas ultrapassadas */

/* Tabela de variaveis de estado da Cba - EST_AVC */
typedef
  volatile struct est_usu_avc /* tabela de variaveis de estado no EST_AVC */
  {
	/* -- Variaveis de estado da Cba -- */
	byte	CheckAtivo;		/* Esta em check */
	byte	CheckOperador;	/* Operador solicita entrada em check */
	byte	ManualAlimRem;	/* Operador passou para manual via computador */
	byte	ManualAlimLoc;	/* Operador passou para manual via chave campo */
    byte    AlimSuspensa;   /* Operador suspendeu a alimentacao via computador */
    byte    RuidoAlim;      /* Indica presenca de ruido na resistencia de alimentacao */
	byte    EaNaoTerminado; /* Indica falha em terminar EA automaticamente */
	byte    QuebPrev;       /* Indica quebrada preventiva */
	byte	AjusteCamisa;	/* Ajuste de camisa ativo */
	byte    QuebPrevInib;   /* Indica quebrada preventiva inibida */
	byte    AbortaAjuste;   /* Indica motivo do ajuste camisa ser abortado */
	byte    AtivCamOpe;     /* Indica ativacao de ajuste camisa pelo operador */
	byte    CamNAjust;      /* Alarme de camisa nao ajustada */
	byte    HabQPrevOpe;    /* Indica ativa/desat. queb. prev. pelo operador */
	byte	BoosterAtivo;	/* Indica ativa/desat. booster pelo operador */
	byte    HabElimEaOpe;   /* Indica ativa/desat. elim. EA pelo operador */
/* -- Alteracao - Inicio - Robson - 03/12/2002 - Tempo para sinalizacao de falta de ruido -- */
	byte	FalhaCalcRuido; /* Indica falha de calculo de ruido */
/* -- Alteracao - Fim - Robson - 03/12/2002 - Tempo para sinalizacao de falta de ruido -- */
	byte	TrataTabPartida;	/* Indica que tabela de partida esta ativa qdo verdadeiro */
/* -- Inicio - Carlos - 24/06/2004 - Algoritmo Sopro Especial -- */
	byte	OpeSoproEspec;	/* Ativa/Desativa algoritmo de sopro especial pelo operador */
	byte	ReleTempoMM;	/* Indica rele de tempo de MM ativado */
	byte	ChaveMCruzeiro;	/* Estado atual da chave de manobra de cruzeiro */
	byte	LiberaMCruzeiro;	/* Estado da saida de liberacao de manobra de cruzeiro */

	byte	TensaoCunha;	/* Indica tensao alta no calante do forno desligado */
	byte	DerNegativa;	/* Indica que o forno esta com derivada negativa */
	byte	DerBaixa;	/* Indica que o forno esta com derivada baixa */
	byte	AjusteCamTur;	/* Indica ajuste de camisa entre turnos */
	byte	Oscilacao;		/* Indica cuba em oscilacao */
	byte 	FormaBanho;		/* Indica que a cuba esta em formacao de banho */
	byte	SireneCunha;	/* Indica que sirene esta tocando */
	byte	DesligaCunha;	/* Indica que sala foi desligada por tensao alta de cunha */
	byte	SopraChamine;	/* Indica que chamine sera soprada */
	byte	SinalChamine;	/* Indica que sinalizou sopro de chamine */
	byte	DBUltQueb;		/* Indica que na ultima quebra programada houve DB*/
	byte	StatusEA;		/* Indica estado de alimentacao da cuba entre DB Prev QP e EA*/
	byte	BSupMovel;		/* Indica que esta com banda superior movel */
	byte 	StatusPainel;	/* Monitora Status do painel do forno */
	byte	CorridaBanho;	/* Indica corrida de banho */
	byte	QuebInibida;	/* Indica estado de quebra inibida */
	byte	FimAEK;			/* Indica Fim de AEK */
	byte	AEK;			/* Indica logica de AEK em atuacao */
	byte	PulaProxQueb;	/* Estado de pular proxima quebra */
	byte	AlarmeDesvio;	/* Estado de alarme de sirenes desvio de tensao */
	byte	ForcaAEK;		/* Movimentacoes forcadas AEK */
	byte	ForcaDesceAEK;		/* Movimentacoes forcadas AEK */
	byte 	EaAtrasado;		/* Tempo do ultimo efeito acima do EAmax */
	byte 	Queb1Passada;	/* Sinaliza quebrada de somente 1 passada */
	byte 	LadoProxPF;		/* Lado proxima quebrada PF New Soderberg */
	byte 	BitCLP;			/* Indicacao do bit de comunicacao CLP */
	byte	LadoProxALF3;	/* Lado da proxima alimentacao de fluoreto */
	byte	TabelaAlF3;		/* Indica calculo de adicao fluoreto realizado para o dia */
	byte	EsperaQP;		/* Indica estado de espera QP */
	byte	ForcaEA;		/* Indica estado de forca EA */
	byte	AlimAlF3;		/* Indica que alimentou fluoreto */
	byte	AlimAl2O3;		/* Indica que alimentou alumina */
	byte	OverPadrao;		/* Inidica que esta em over padrao */
	byte	UnderPadrao;	/* Indica que esta em under padrao */	
    byte    AlimCheck;  	 /* Operador sinalizou check */
	byte	ZeraCA;			/* Zera coeficiente angular */
	byte	AlarmeCheck;	/* Alarme de check longo */
	byte	ProjetaCA;		/* Sinaliza projecao de CA */
	byte	ForcaEstAlim;	/* Forca estado de alimentacao */
	byte	TendenciaOver;	/* Alarme de tendencia de overfeed*/
	byte	CamisaAlta;		/* Alarme de Camisa Alta */
	byte	CamisaBaixa;	/* Alarme de Camisa Baixa */
	byte	QuebCab;		/* Estado de Quebra de Cabeceira */
	byte	EfeitoQuebCab;	/* Efeito de Quebra de Cabeceira */
	byte	TendOverCancela;	/* Não-sinalização de TendOver no ciclo de Over */
	byte	InibeMovDB;		/* Inibe Movimentação e Incremento de Quebrada em DB */	
	byte	InibeQPposDB;		/* Inibe QP em DB */	
	
	//byte	ResUsuario[50];	    //  92 + 28  = 120   - Expansao 13/11/14 - Red 2 CBA	
	//byte	ResUsuario[49];	    //  50 - 1   = 49	 - ByteTendOverCancela
	byte	ResUsuario[47];	    //  49 - 2   = 49	 - Bytes InibeMovDB e InibeQPposDB

  } t_est_usu;

/* -- Tipo de dados da tabelas da Cba para os parametros de Linha - AVL -- */
/* ATENCAO : Esta tabela nao deve ter suas reservas ultrapassadas */

/* Tabela de parametros de linha - AVL */
typedef
  volatile struct par_avl_usu /* tabela de parametros de linha AVL */
  {
/* -- Alteracao - Inicio - 11/02/2003 - Leonel - Comutacao sinal de corrente atraves da AtnCA -- */
	byte	SelecaoCanalI;		/* 0=nao comanda selecao de canal, 1=seleciona canal principal, 2=seleciona reserva */
/* -- Alteracao - Fim - 11/02/2003 - Leonel - Comutacao sinal de corrente atraves da AtnCA -- */
	t_partida_cuba	TabPartida[MAX_TAB_PARTIDA];
/* -- Alteracao - Inicio - 29/05/2003 - Bandeira - comandos p/ quebrada -- */
	short int		TempoMoveCimaOpeMovel;		/* tempo em segundos p/ mover para cima */
	short int		TempoMoveBaixoOpeMovel;		/* tempo em segundos p/ mover para baixo */
	short int		TempoSoproOpeMovel;			/* tempo em segundos p/ soprar */
	short int		LimMovBAtEa;				/* limite de movimentacao p / baixo no atendimento ea */
	short int		LimMovCAtEa;				/* limite de movimentacao p / cima no atendimento ea */
	short int		LimSoproAtEa;				/* limite de sopro no atendimento ea */
/* -- Alteracao - Fim - 29/05/2003 - Bandeira - comandos p/ quebrada -- */
/* -- Inicio - Carlos - 24/06/2004 - Algoritmo Sopro Especial -- */
	short	TLimSoproEspec;			/* Limite duracao de sopro especial */
	short	TIntervSoproEspec;		/* Intervalo minimo entre acionamento de sopro especial */
	float	VLimSoproEspec;			/* Limite tensao para acionamento de sopro especial */
	short	DurAcionaSoproEspec;	/* Duracao acionamento sopro especial em segundos */
/* --  Fim  - Carlos - 24/06/2004 - Algoritmo Sopro Especial -- */
	byte	HabImportSIAP;	/* Habilita importacao automatica de dados do SIAP */

	short int	EfeitoDifAlta;	/* Tempo efeito de diferenca de corrente para o alvo alta */
	short int	DifCorMax;		/*Maxima diferenca de corrente entre alvo e principal */
	float	EaVoltLinhaLim;	/* Limite que indica efeito na linha nao identificado */
	long	TEfeitoEaLinha;	/* Tempo de efeito do alarme de efeito nao identificado na linha */
	int	TMaxCorrida; /* Tempo maximo de movimentacao de corrida */
	short int Reserva1;		/* Conflito com TMaxCorrida*/
	byte	NCic4sEaLinha;	/* Ciclos de 4s para identificacao de efeito de linha */
	unsigned int	BitSirenesATNCA1;	/* Identifica os bits de todas as sirenes */
	unsigned int	BitSirenesATNCA2;	/* Identifica os bits de todas as sirenes */
	byte	TmpAlarmeSirenes;	/* Tempo em segundos para alarme de todas as sirenes */
	float	KpcCorr;			/* Kpc de atuacao na movimetacao pos corrida */

//	char	ResParAvlUser[196];	/* -- Reserva Usuario -- */
	char	ResParAvlUser[304];	// 448 + 112 = 560   - Expansao 13/11/14 - Red 2 CBA -- Reserva Usuario --
  } t_par_avl_usu;

/* -- Tipo de dados da tabelas da Cba para os valores de trabalho de Linha -- */
/* ATENCAO : Esta tabela nao deve ter suas reservas ultrapassadas */

/* Tabela de valores de trabalho de linha - AVL */
typedef
  volatile struct trab_avl_usu /* tabela de variaveis de trabalho de linha AVL */
  {
	/* -- Variaveis de trabalho de linha da Cba -- */
	/* -- alteracao - inicio - 28/12/00 - Leonel - Inclusao temperatura Atn8 -- */
	byte	Atn8Temperature[MAX_ATN8]; /* Temperatura interna da Atn8 */
	/* -- alteracao - fim - 28/12/00 - Leonel - Inclusao temperatura Atn8 -- */
	long	DataAnalise;		/* -- Data de alteracao em qualquer cuba de fluoreto/fluorita -- */
	long	DataOperacional;	/* -- Data de alteracao em qualquer cuba de metal/banho -- */
	byte	DifCorAlta;
	long	HoraDifCorAlta;		/* Hora em que houve diferenca de corrente entre principal e alvo */
	long	HoraIniDia;			/* Hora de inicio do dia */
	long	DataImport;			/* Data em que foi importado pelo ImportaSIAP */
	byte	Reserva;		/* Antigo EaIdentificado */
	byte	EaLinha;		/* Indica que existe efeito na linha em cuba fora de rede */
	byte	AlarmeSala;		/* Tipo de alarme de sala */
	byte	EstadoSireneSala;	/* Estado de todas as sirenes para alarme de sala */
	long	HoraAlarmeSala;		/* Hora que foi sinalizado o alarme de sala */
	float	TimerMcc;			/* Contabiliza tempo de execucao do ciclo mcc  */
	float	TimerMcp;			/* Contabiliza tempo de execucao do ciclo mcp */
	short int	Ea24hTurno;
	short int	NumEaDiaTurno;
	short int	AtrasoEATurno;
	long	HoraFimDia;			/* Hora de fim do dia */

//	byte	ResGerAvlUser[521];	/* -- Reserva Usuario -- */
	byte	ResGerAvlUser[723];	  // 900 + 220 = 1120  - Expansao 13/11/14 - Red 2 CBA -- Reserva Usuario --
	// * antigo *  byte	ResGerAvlUser[900];	/* -- Reserva Usuario -- */
  }	t_trab_avl_usu;

/* -- Tipo de dados da tabelas da Cba para os valores de supervisao diaria de Linha -- */
/* ATENCAO : Esta tabela nao deve ter suas reservas ultrapassadas */

/* Tabela de valores de supervisao diaria e turno de linha - AVL */
typedef
  volatile struct sup_avl_usu	/* tabela de variaveis de supervisao de linha AVL */
  {
	/* -- Variaveis de supervisao da Cba -- */
/* -- alteracao - inicio - 11/09/00 - Robson - Inclusao tratamento do Atn8 -- */
	 short unsigned int ErrorADAtn8[NUM_OUTRAS_REMOTAS][MAX_VALORES_POR_ATN8]; /* 30x4x2=240 Erros de leitura de analogicas */
/* -- alteracao - fim - 11/09/00 - Robson - tratamento do Atn8 -- */
//	byte	ResSupAvlUser[300];	/* -- Reserva Usuario -- */
	short int	Ea24h;
	short int	NumEaDia;
	short int	AtrasoEA;
	byte	ResSupAvlUser[426];	   // 540 + 132 = 672   - Expansao 13/11/14 - Red 2 CBA -- Reserva Usuario -- */
  } t_sup_avl_usu;

#endif		/* #ifndef		_SCORE_CBA_H */

/* -- Fim do arquivo ScoreCba.h -- */
