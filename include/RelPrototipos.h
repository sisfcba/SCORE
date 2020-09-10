/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: RelPrototipos.h

	CONTEUDO	: Prototipos das funcoes de relatorio

	AUTOR		: Alexandre Bandeira

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0		  -		  DATA  : 10/10/95

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
******************************************************************************/

#include <time.h>
#include <Relatorios.h>


					/****************************/
					/* PROTOTIPACAO DAS FUNCOES */
					/****************************/


/*****************************************************************************


							BIBLIOTECAS DE RELATORIO


	- As funcoes de relatorios estao organizadas em 4 bibliotecas, como
	  pode ser vista abaixo:

		- BibRel.lib : biblioteca generica de relatorios.
		- RelImpLib.lib : biblioteca de funcoes de relatorios impressos.
		- RelTelaLib.lib : biblioteca de relatorios de tela da console. 
		- RelTelaLibw.lib : biblioteca de relatorios de tela da interface
				windows.

*****************************************************************************/

/**************************** FUNCOES GENERICAS ******************************

	- A biblioteca BibRel.lib contem funcoes  genericas de consistencia,
	  montagem e exibicao utilizadas nos relatorios impressos, console e
	  interface windows. Ela fica no diretorio /score/objs/rel/lib

*****************************************************************************/

int  LeDescritores(char *NomArq, t_descritores *Dados);
char *GrArqRel(void *Cabecalho, void *AreaDados, void *Rodape, char *NomeRel,
				 int NumLinhas);
void GrArqRelDina(t_descritores *Descr, void *Cabecalho, void *AreaDados,
                  void *Rodape, int NumLinhas, char *PBuf);
void ExibeRel(char *NomeArq , int NumLinhas);
void ExibeRelDina(struct Window *JanRel, t_descritores *Descr, char *PBuf,
                   int NumLinhas);
int  ConsDatas(char *Data1, char *Data2, t_args *Arg, int MaxDias);
void ExibeErro(char *Mens);
void ExibeAtencao(char *Mens);
void ExibeErroSav(char *Mens);
int  ConsHora(char *HoraExt, long *Tempo);
#ifdef OPERACAO_WINDOWS
  int  ConsFiltrosW(char *PtStr, t_args *Argumentos, int *IndArg);
  void MontaAlgSel(char *Selecao, char *Algorit, t_filtrosPD *filtro);
#else
  int  ConsFiltros(char *PtStr, t_args *Argumentos, int *IndArg);
#endif
int  FiltPredef(char *PtStr);
int  FiltPredMsg(char *PtStr);
void ExibeHist(char *NomeArq, int NumLinhas, t_descritores *Descr);
int  GrCabHist(void *Cabecalho, t_descritores	*Descr, int DescRel);
int  GrDadosHist(void *AreaDados, t_descritores	*Descr, int DescRel, int NumLinhas,
				 int CompletaPagina);
int  ValExcCubas(char *PtStr, int *PTab);
int  ValidaCuba(int *PTab, int Cuba);
char *CarBufDias(int ContDia, struct tm *DataTm, t_args *Arg);
int  ValidaExcDatas(t_args *Argm, char *Linha);
int  ValidaData(t_args *Argm, time_t Data);
void MontaValor (void *Org, char *Dest, int Tam, int Dec, int Tipo );
#ifdef RELATORIO_HISTORICO
  t_hist *CarBufCubas(struct tm *DataTm, t_args *Arg);
  t_hist *CarBufTurno(struct tm *DataTm, t_args *Arg);
#endif
#ifdef REL_TURNO
  float CalcPercTur(t_args *Argm, int NCicAtivo, int Ajuste, time_t HoraAtual,
				  int DiaJulCor);
  int TurnoDiaAnterior(t_args *Argm, time_t HoraAtual, int DiaJulAtual);
#else
  float CalcPercDia(int NCicAtivo, int Ajuste, time_t HoraAtual, int DiaJulCor);
#endif


/********************* FUNCOES DE RELATORIOS IMPRESSOS ***********************

	- A biblioteca RelImpLib.lib contem funcoes referentes aos relatorios
	  impressos, a qual esta localizada no diretorio /score/objs/rel/lib

*****************************************************************************/

void ExibeRelImp(char *NomeArq, int NumLinhas);
void ExibeRel(char *NomeArq, int NumLinhas);
