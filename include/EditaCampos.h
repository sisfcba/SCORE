/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 3.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: EditaCampos.h

	CONTEUDO	: Definicoes para entrada de dados em tela

	AUTOR		: Hevelton Araujo Junior

	VERSAO		: 00 - 14/10/92


	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
06/01/93 | Alterado descritor dos  campos  para  incluir Unidade de | Leonel
         | engenharia, formato, limites  sup.  e  inf. e  fator  de |
         | conversao.                                               |
-------------------------------------------------------------------------------
28/03/95 | Definicao das classes dos campos e inclusao no descritor | Carlos
-------------------------------------------------------------------------------
******************************************************************************/

	/********************************************/
	/*--- TESTA E INDICA QUE JA FOI INCLUIDO ---*/
	/********************************************/

#ifndef	_EDITA_CAMPOS

#define	_EDITA_CAMPOS

#include <WindowsCBA.h>

	/********************/
	/*--- DEFINICOES ---*/
	/********************/

#define STEP_LIN 190
#define STEP_COL 90
#define COL_INI  10

/*--- Caracteres de senha ---*/
#define	CARAC_SENHA		"##########"

/*--- Tipos de dado ---*/
#define	INTEIRO			1
#define	FLOAT			2
#define	_ASCII			3
#define	LONGO			4
#define	UNSIGNED		5
#define	BYTE			6
#define	SHORT			7

/*--- Tipos de caracteres validos para edicao ---*/
#define	ALFALETRAS		1
#define	ALFABETICOS		2
#define	NUMERICOS		3
#define	NUM_FLOAT		4
#define	ALFANUMERICOS	5
#define	QUALQUER		6

/*--- Atributos possiveis para os campos ---*/
#define	SOMENTE_EXIBIR	1
#define	EXIBIR_EDITAR	2
#define	NAO_EXIBIR		3
#define	EXIB_ED_SENHA	4

/*--- Classes possiveis para os campos ---*/
#define	PARAM_CUBA		1
#define	PARAM_LINHA		2
#define	CONV_CUBA		3
#define	CONV_LINHA		4
#define	ESTADO_CUBA		5
#define	ENT_ESP_LINHA	6
#define PARAM_USER1		7
#define PARAM_USER2		8

/*--- Tamanho maximo do nome do campo na tela ---*/
#define	TAM_NOME_CAMPO	25

/*--- Linha inicial para os campos de entrada ---*/
#define	LINHA_INICIAL	2

/*--- Numero de colunas de campos de dados por tela de entrada de dados --*/
#define	NUM_COLUNAS		2

/*--- Posicao da primeira coluna na tela de entrada de dados ---*/
#define	COL_INICIAL		1

/*--- Distancia entra as colunas de entrada de dados ---*/
#define	OFFSET_COLS		39

/*--- Numero maximo de paginas de edicao ---*/
#define	MAX_PAGINAS		20

/*--- Teclas para avancar/retroceder numero da cuba ---*/
#define	AVANCA_CUBA		F2
#define	RETROCEDE_CUBA	F3

/*--- Tecla para gravacao dos dados ---*/
#define	TECLA_GRAVAR	F10

/*--- Cores dos textos dos parametros ---*/
#define	COR_TEXTOS		(CYAN_B)


	/************************/
	/*--- TIPOS DE DADOS ---*/
	/************************/

/*--- Estrutura dos campos na tela de entrada de dados ---*/
typedef
  struct EntradaDeDados
  {
	char	*NomeCampo;
	char	*UnidEng;
	void	*EndrCampo;
	int		TipoCampo;
	int		FrmtCampo;
	int		TamhCampo;
	int		PrecCampo;
	float	LimInfCampo;
	float	LimSupCampo;
	float	FatorConv;
	int		ClasCampo;
  } t_ent_dados;

	/**********************************/
	/*--- PROTOTIPACAO DAS FUNCOES ---*/
	/**********************************/

void ExibeErro (char *Mens);
void ExibeErroSav (char *Mens);
int ExibePagina (t_janela *Jan, t_ent_dados *Dados,
										int CampoInicial, int NumLinhas);
int EditaPagina (t_janela *Jan, t_ent_dados *Dados,
								int CampoInicial, int NumCampos, int NLins);
int EditaCampo (t_janela *Jan, void *Valor, int Tipo, int Tam, int Prec,
		int Fmt, float LimInf, float LimSup, float FConv, int Lin, int Col);
int EditaValor (t_janela *Jan, char *Valor, int Tam, int Lin, int Col, int Tipo,
		int CaracVal, int Fmt, float LimInf, float LimSup);
void AsciiPara (char *Origem, void *Destino, int Formato, float FConv);
char *ParaAscii (void *Origem, int *Padrao, int Formato, int Tamanho,
		int Precisao, float FConv);

#endif	/*--- ifndef _EDITA_CAMPOS ---*/

