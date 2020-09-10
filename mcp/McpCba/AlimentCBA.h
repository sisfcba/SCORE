/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.1

	PROJETO		: CBA - Companhia Brasileira de Aluminio SA

	SISTEMA		: SALAS 120KA II e III

	ARQUIVO		: McpPF.h

	CONTEUDO	: Prologo para o algoritmo de alimentacao da CBA

	AUTOR		: Ricardo Teixeira Leite Mourao / Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	02/01/97

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
Data     | Descricao                                            | Autor 
-------------------------------------------------------------------------------
02/01/97 | Edicao inicial                                       | Ricardo-Leonel
-------------------------------------------------------------------------------
******************************************************************************/
/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include <Score.h>

/*
-------------------------------------------------------------------------------
                           Defines
-------------------------------------------------------------------------------
*/

/* -- constante para calculo da alumina consumida -- */
#define K_CONSUMO           1.76126764579e-7

/* -- Estados do algoritmo de alimentacao -- */
#define		EST_ALIM_PADRAO				1	/* -- normal -- */
#define		EST_ALIM_EA					2	/* -- tratamento de Efeito anodico -- */
#define		EST_ALIM_SUSPENSA			3	/* -- tratamento qdo alim. suspensa -- */
#define		EST_ALIM_EXCECAO			4	/* -- tratamento qdo check inicial -- */

/* -- Sub estados do algoritmo de alimentacao -- */
/* -- ALIM_PADRAO -- */
#define		PADRAO_NORMAL			1
#define		PADRAO_PRE_CHECK		2
#define		PADRAO_CHECK1			3
#define		PADRAO_CHECK2			4
#define		PADRAO_CHECK3			5
#define		PADRAO_CHECK4			6
#define     PADRAO_OVER             7

/* -- ALIM_EA -- */
#define EA_OVER_INICIAL             1
#define EA_CHECK_ESP1				2
#define EA_CHECK_ESP2				3
#define EA_CHECK_ESP3				4
#define EA_CHECK_ESP4				5
#define EA_NORMAL					6
#define EA_PRE_CHECK				7
#define EA_CHECK1					8
#define EA_CHECK2					9
#define EA_CHECK3					10
#define EA_CHECK4					11
#define EA_OVER                     12

/* -- ALIM_EXCECAO -- */
#define ALIM_EXC_ESPERA1            1
#define ALIM_EXC_ESPERA2            2
#define ALIM_EXC_ESP_CHECK1         3
#define ALIM_EXC_ESP_CHECK2         4
#define ALIM_EXC_ESP_CHECK3         5
#define ALIM_EXC_NORMAL             6
#define ALIM_EXC_PRE_CHECK          7
#define ALIM_EXC_CHECK1             8
#define ALIM_EXC_CHECK2             9
#define ALIM_EXC_CHECK3             10
#define ALIM_EXC_CHECK4             11
#define ALIM_EXC_OVER               12
#define ALIM_EXC_USU                13

/* -- ALIM_SUSPENSA -- */
#define		SUSPENSA_NORMAL			1
#define		SUSPENSA_CHECK1			2

/* -- Origens da chamada do muda estado -- */
#define		MUDA_CONTROLE			1	/* MudaEstado chamado apos termino normal */
#define		MUDA_OPER				2	/* MudaEstado chamado pela Operacao */
#define		MUDA_EXT				3	/* MudaEstado chamado por eventos externos */

/* -- Origens da mudanca de estado para geracao de eventos --*/
//#define 	ORIGEM_CONTROLE			"Controle"
//#define 	ORIGEM_OPER				"Operacao"
//#define 	ORIGEM_EXT				"Externo"
//#define 	ORIGEM_INV				"OrigInv"

/* -- Nome dos estados de alimentacao para geracao de eventos-- */
/* -- OBSERVACAO: O nome nao pode conter mais de 8 caracteres -- */
//#define		ALIM_NOME_PADRAO			" Padrao "	/* alimentacao normal */
//#define		ALIM_NOME_EA				"   EA   "	/* alimentacao Ea */
//#define		ALIM_NOME_EXCECAO			" Excecao"	/* alimentacao Excecao */
//#define		ALIM_NOME_SUSPENSA			"Suspensa"	/* alimentacao suspensa */
//#define		ALIM_NOME_ALIM_INV			"Invalida"	/* alimentacao invalida */

/*
------------------------------------------------------------------------------
                           Macros
-------------------------------------------------------------------------------
*/
#define		EstadoAtual(cuba)	    (AVC.User1[cuba].EstadoAlimAtual)
#define		EstadoIO(cuba,bit)	    ((AVC.Cleit[cuba].EstadoIO >> (bit-1)) andb 1)
#define     InibeControleAlim(cuba) (AVC.User1[cuba].InibeControleAlim=VERDADEIRO)

/*
-------------------------------------------------------------------------------
                           Tipos de dados
-------------------------------------------------------------------------------
*/

/*
-------------------------------------------------------------------------------
                           Prototipos
-------------------------------------------------------------------------------
*/
void	MudaEstadoAlim(int Cuba,int Estado, int Origem);
void	MudaEstadoSub(int Cuba,int Estado);
char	*NomeModoAlim(int Modo, int Cuba);

/* -- Fim do arquivo AlimentCBA.h -- */
