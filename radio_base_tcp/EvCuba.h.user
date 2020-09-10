/******************************************************************************

             ACCENTURE - ACPS - ACCENTURE PLANT & COMMERCIAL SERVICES
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 5

    CLIENTE     : CBA - Companhia Brasileira de Aluminio SA

	PROJETO		: Todos

	SISTEMA		: Todos

	ARQUIVO		: EvCuba.h

	CONTEUDO	: funcao que processa e gera as informacoes que compoem
				  o relatorio instantaneo de mensagens de cuba p/ coletor

	AUTOR		: Alexandre Mariz Bandeira de Morais.

	SISTEMA OPERACIONAL:  QNX 4.41		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 01 - 27/07/98

	OBSERVACAO	: 

	HISTORICO DAS EDICOES

-------------------------------------------------------------------------------
$Id: EvCuba.h,v 1.1.1.1.10.1 2014/10/27 15:23:52 leo Exp $

$Log: EvCuba.h,v $
Revision 1.1.1.1.10.1  2014/10/27 15:23:52  leo
Preparacao para criar kit de desenvolvimento do radio. Retiradas referencias
a prologo antigo da Alcan.

******************************************************************************/

	/*-- INCLUSAO DE OUTROS ARQUIVOS --*/

#include <RFComunica.h>
#include <sizes.h>
#include <global.h>
#include <rflib.h>
#include <usuarios.h>
#include <RelGraf.h>
#include <IniArqVar.h>
#include <sys/mman.h>

	/*-- DEFINICAO DE CONSTANTES --*/

/*-- Sentidos de leitura do buffer de mensagens --*/
#define	PARA_CIMA			1
#define	PARA_BAIXO			2

/*-- Opcoes de inicializacao do indice do vetor de exibicao --*/
#define	INICIALIZACAO		1
#define	ATUALIZACAO			2

/*-- Flags das teclas de funcao --*/
#define	TECL_HOME			1
#define	TECL_PAGE_UP		2
#define	TECL_PAGE_DOWN		3
#define	TECL_END			4
#define TECL_EXIT			5

/*-- Numero de linhas da area de dados --*/
#define	MAX_LINHAS_DADOS	12

/*-- tamanho total da mesagem --*/
#define TAM_MENS 19

/*-- Definicao de variaveis globais --*/
  int		PrimeiraPagina;
  int		VoltouPrimeiraPagina;
  int		AtualizaTela;
  int		PagInicialAnt;
  int		PagInicial;
  int		PagFinal;
  int		Tecla;
  int		TeclaAnterior;
  int		SentidoAnterior;

  t_cab_buf_ev	PBufLoc;

/*-- Definicao de tipos proprios --*/

/*-- Area de Dados --*/
typedef
  struct VarDados
  {
	int		Cor;
	char	Mensagem[TAM_MENS+2];
  } t_dados;

/*-- Tela de mensagens --*/
typedef
  struct TelaMsg
  {
    int	Cor;
    char		Linha[TAM_MENS];
  } t_msg_tela;

/*-- Prototipos das funcoes internas --*/
void InitVars(int *PFinal);
int  TemNovoEvento(void);
int  AtualizaBufferMensagens(void);
int  MontaPagina( t_dados *Dados, int EndFinal );
void AtualizaIndice(int Opcao, int Sentido, int *PCont);
int  DefineSentidoLeitura (int EndFinal);
int  LeEvento(t_rec_ev *PRec, int EndFinal, int Sentido);
void DataHoraEvento(time_t DataEv, char *PData, char *PHora);
void MontaMensEv(char *PMsg, t_rec_ev *PRec );
int  ExibeRelMsg( t_dados *Dados, int NumLinhas );

