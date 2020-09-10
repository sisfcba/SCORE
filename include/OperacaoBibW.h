/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: OperacaoBibW.h

	CONTEUDO	: Prototipos das funcoes da biblioteca ConsoleW.lib do
				  diretorio /score/objs/ihm_windows/lib

	AUTOR		: Carlos Cezar Silva Lage

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0		  -		  DATA  : 01/11/95

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
******************************************************************************/

#ifndef		_OPERACAO_BIB_W_H
#define		_OPERACAO_BIB_W_H

#include <TiposOpeW.h>

					/****************************/
					/* PROTOTIPACAO DAS FUNCOES */
					/****************************/


t_boolean AbreWinIniAla( t_ihm_config *ihm );
t_boolean AbreTodasPicts( t_ihm_config *ihm );
int  StartWindows(int dummy);
void EndWindows(void);
void ExibeErro (char *Mensagem);
void EscreveAjuda( char *NomArq );
int  PedeSenha( int *Operador );
int MontaTeclado( int Wid, int Pid, char *TagCampo, int TamCampo, byte Hide );
int MontaTelaCubas( int Wid, int Pid, char *TagCampo, char *TagCampo1, int NLinhas, int NumCubas );
int MontaTelaDatas( int Wid, int Pid, char *TagCampo, int NumDatas );
int  trata_menu( t_ihm_config *ihm, int tags );
t_boolean ConfirmaComando( t_ihm_config *ihm, int tags );
void trata_acao( t_ihm_config *ihm, t_filtrosPD *filtro, int tags, char *ArqFiltro );
int  trata_tarefa( t_ihm_config *ihm, t_filtrosPD *filtro, int tags, char *arq, char *arq1, pid_t *pid );
void trata_pre_sel( t_ihm_config *ihm, t_filtrosPD *filtro, int tags, char *ArqFiltro );
void EscreveAjuda( char *nome );
t_boolean trata_lista( t_ihm_config *ihm, t_filtrosPD *filtro, int tags, char *arq );


void FimScoreRede(void);
int  PedeSenha( int *Operador );
char *OpenComumAlarme( char *nome, size_t tamanho );

void ChangeSymbol( t_ihm_config *ihm, short flag );
unsigned ChangeGrupo( unsigned flag );
void ChangeAlg( unsigned alg );


int  MontaNodos(void);
void ConsistePreSel(char *arqfiltro, t_filtrosPD *filtro);
int  TrataTelas( t_GrupoCuba *GrupoCuba );
int  compare( short int *p1, short int *p2 );

#endif		/* _OPERACAO_BIB_W_H */
