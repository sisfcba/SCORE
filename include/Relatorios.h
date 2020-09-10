/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: Relatorios.h

	CONTEUDO	: Definicoes gerais para todos relatorios

	AUTOR		: Hevelton Araujo Junior

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0		  -		  DATA  : 03/09/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
15/01/93 | Inclusao da tabela de cubas  excluidas  na  estrutura  de | Carlos
         | argumentos e do define de seu tamanho ( MAX_EXC_CUBAS )   |
-------------------------------------------------------------------------------
28/09/93 | Inclusao da tabela de  dias  excluidos  na  estrutura  de | Carlos
         | argumentos e do define de seu tamanho ( MAX_EXC_DIAS )    |
-------------------------------------------------------------------------------
04/04/94 | Inclusao do de EV_MENS na lista de filtros predefinidos   | Carlos
-------------------------------------------------------------------------------
04/08/94 | Edicao inicial de migracao para o QNX 4.2                 | Leonel
-------------------------------------------------------------------------------
04/10/94 | Alteracoes p/ migracao para o QNX windows                 | Leonel
-------------------------------------------------------------------------------
05/10/94 | Inclusao da tabela de exclusao de datas na estrut. t_args | Carlos
-------------------------------------------------------------------------------
01/11/94 | Inclusao das definicoes de grupos de cubas				 | Carlos
-------------------------------------------------------------------------------
02/02/95 | Adaptacao para versao em ingles           				 | Carlos
-------------------------------------------------------------------------------
08/06/95 | Aumentado o numero de filtros do relatorio de eventos     | Carlos
-------------------------------------------------------------------------------
10/10/95 | Retirado os includes e os prototipos                      | Bandeira
-------------------------------------------------------------------------------
06/08/96 | Inclusao das definicoes de salas de fornos           	 | Carlos
-------------------------------------------------------------------------------
******************************************************************************/

#ifndef RELATORIOS_H

#define	RELATORIOS_H

#include <time.h>

	/*-- DEFINICAO DE CONSTANTES --*/

/*-- Macros para acessar tabelas de supervisao --*/
#define	HIST_AVC(Cuba)	HAvlAvc->AvcHist.AvcSuperv[Cuba].AvcS
#define	HIST_AVL		HAvlAvc->AvlHist.Uavl.Avl


/*-- Nome do arquivo de saida dos relatorios --*/
#define	NOME_RELAT			"//%d/tmp/score/%s.%02X"

/* -- nome do pict e wnd utilizados para exibicao de relatorio -- */
#define MASC_REL			"/score/telas/MascRel"

/*-- Numero maximo de linhas que pode conter o relatorio --*/
#define	MAX_LINHAS			(MAX_CUBAS * 2)
//#define	MAX_LINHAS			MAX_CUBAS

/*-- Cor da janela para relatorios --*/
#define	COR_JAN_REL				( CYAN_B )

/*-- Tamanho da linha de um relatorio --*/
#define	TAM_LIN					78

/*-- Chave que indica que foi pedido help --*/
#define	CHAVE_AJUDA				"-h"

/*-- Numero maximo de campos do cabecalho, area de dados e rodape --*/
#define	MAX_CAMPOS_CABEC		40
#define	MAX_CAMPOS_DADOS		40
#define	MAX_CAMPOS_RODAPE		40

/*-- Retorno de funcoes de relatorio --*/
#define	RET_FUNCAO_OK			1
#define	RET_FUNCAO_ERR			0

/*-- Definicao de uma variavel sentinela. --*/
#define	SENTINELA				-1

/*-- Definicao da sinalizacao para hora atual no parametro HoraFinal --*/
#define	HORA_ATUAL				-1

/*-- Numero maximo de filtros recebidos do relatorio de eventos --*/
#define	MAX_TAB_FILTROS			9

/*-- Numero maximo de filtros de eventos por linha na console --*/
#define	MAX_FILT_LIN_CONSOLE	3

/*-- Numero maximo de cubas a serem excluidas --*/
#define	MAX_EXC_CUBAS			44

/*-- Numero maximo de dias a serem excluidos  --*/
#define	MAX_EXC_DATAS			14

/*-- Definicao dos tipos de filtros que podem ser solicitados pelo operador --*/
#define	EV_TOTAL	1	/*-- Todos eventos gerados pelo sistema.            --*/
#define	EV_PROC		2	/*-- Todos eventos do sistema gerados pelo processo --*/
						/*-- de controle. ( EV_TOTAL - EV_SIST )            --*/
#define	EV_SIST		3	/*-- Todos eventos do sistema  gerados  por  alguma --*/
						/*-- condicao de erro. ( EV_TOTAL - EV_PROC )       --*/
#define	EV_LINHA	4	/*-- Apenas os  eventos  do  processo  de  controle --*/
						/*-- referentes a linha. ( EV_PROC - EV_CUBAS )     --*/
#define	EV_CUBA		5	/*-- Apenas os  eventos  do  processo  de  controle --*/
						/*-- referentes as cubas. ( EV_PROC - EV_LINHA )    --*/
#define	EV_LIST		6	/*-- Sinaliza especificacao de uma lista de eventos.--*/
#define	EV_MENS		7	/*-- Sinaliza que serao mostrados apenas os alarmes --*/
						/*-- exibidos na linha de mensagens.                --*/

/*-- Dezenas dos grupos de cubas --*/
#define	DEZENA_FIM_GRUPO_A		18 	/*-- Ultima dezena do grupo A (1  a 18) --*/

#define	DEZENA_FIM_GRUPO_B		36 	/*-- Ultima dezena do grupo B (19 a 36) --*/

#define	DEZENA_FIM_GRUPO_C		54 	/*-- Ultima dezena do grupo C (37 a 48) --*/

#define	DEZENA_FIM_GRUPO_D		72 	/*-- Ultima dezena do grupo D (49 a 72) --*/

/*-- Definicao dos grupos cubas --*/
#define	GRUPO_A					0

#define	GRUPO_B					1

#define	GRUPO_C					2

#define	GRUPO_D					3

/*-- Tipos possiveis para os campos variaveis --*/
#define NAO_INIC                0
#define	INTEIRO					1
#define	FLOAT					2
#define	_ASCII					3
#define	LONGO					4
#define	UNSIGNED				5
#define	DATA					6
#define	HORA					7

/*-- Tamanho de uma estrutura de descritores --*/
#define	TAM_REG_DADOS			(sizeof (struct DescrCampos))

	/*-- DEFINICAO DE TIPOS --*/

typedef
  struct DescrCampos
  {
	struct DescrCabec
	{
	  int	LinhaIni;
	  int	NumLinhas;
	  char	TextoLin[5][81];
	  int	NumCampos;
	  struct CamposCabec
	  {
		int		Linha;
		int		Coluna;
		int		Tipo;
		int		Tamanho;
		int		Decimais;
	  } Campos[MAX_CAMPOS_CABEC];
	} Cabecalho;

	struct DescrDados
	{
	  int	LinhaIni;
	  int	NumLinhas;
	  int	NumCampos;
	  struct CamposDados
	  {
		int		Coluna;
		int		Tipo;
		int		Tamanho;
		int		Decimais;
	  } Campos[MAX_CAMPOS_DADOS];
	} AreaDados;

	struct DescrRodape
	{
	  int	LinhaIni;
	  int	NumLinhas;
	  char	TextoLin[5][81];
	  int	NumCampos;
	  struct CamposRodape
	  {
		int		Linha;
		int		Coluna;
		int		Tipo;
		int		Tamanho;
		int		Decimais;
	  } Campos[MAX_CAMPOS_RODAPE];
	} Rodape;
  } t_descritores;

/*-- Argumentos --*/
typedef
  struct ArgsRec
  {
    int		CubaInicial;
    int		CubaFinal;
    int 	DiaAnoAtual;
    int 	DiaInicial;
    int 	MesInicial;
    int 	AnoInicial;
    int 	DiaAnoIni;
    int 	DiaFinal;
    int 	MesFinal;
    int 	AnoFinal;
    int 	DiaAnoFim;
    int 	DiasDatas;
    long	HoraInicial;
    long 	HoraFinal;
    int		TabIndFilt[MAX_TAB_FILTROS];
    int		TipoFiltro;
    int		TabCubas[MAX_EXC_CUBAS];
    time_t	TabDatas[MAX_EXC_DATAS];
    int		Turno;
  } t_args;

#endif
