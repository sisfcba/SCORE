/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 3.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: TrataEa.h

	CONTEUDO	: Prologo e Prototipos das funcoes usadas pelo TrataEa

	AUTOR		: Joao Thomaz Pereira

	VERSAO		: 1.0			-		DATA	:	08/09/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
dd/mm/aa | descricao                                            | autor 
-------------------------------------------------------------------------------
03/10/96 | Definicao de constantes de EA                        | Carlos
-------------------------------------------------------------------------------
******************************************************************************/

/*
-------------------------------------------------------------------------------
								Constantes
-------------------------------------------------------------------------------
*/

/*-- Classificacao do EA para relatorio hist. de controle de processos --*/
#define	EA_NORMAL		1
#define	EA_FRACO		2
#define	EA_FORTE		3

/*
-------------------------------------------------------------------------------
								Prototipos
-------------------------------------------------------------------------------
*/
void IniTrataEa(void);
void IniVarsEa(void);
void InicioEa(int Cuba);
void CalcDadosEa(int Cuba);
void AguardaFimEa(int Cuba);
int ClassificaEa(int Cuba);
void EliminaEa(int Cuba, int EfeitoAnodico);
void CalcDadosEa(int Cuba);
void AguardaFimEa(int Cuba);
void FimEa(int Cuba);
  float CalcMedDin(double Parcela1, int Cont, double Parcela2);


/*
-------------------------------------------------------------------------------
                           Tipos de dados
-------------------------------------------------------------------------------
*/
typedef 
	struct pots
	{
	  float EaMed;
	  int	NLeitEa;
	  float	LeitEa_vet[240];
	  float	EaDesvPad;
	  int 	ContSobe;
	  float	AEK_VMax;
	  float AEK_VMaxIni;
	  byte	FimMoveAEK;
	  long	HoraFimAEK;
	  int	DeltaTempo;
	  byte	ContMovCimaAEKPF;
	  byte	ContMovBaixoAEKPF;
	  long	HoraUltMovAEKPF;
	  
	  
	} calcEa;


DECL	calcEa  EaLocal[MAX_CUBAS];
