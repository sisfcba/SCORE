
/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.

	PROJETO		: GERAL

	SISTEMA		: GERAL

	ARQUIVO		: ListasEnvRemota.h

	CONTEUDO	: Definicoes para primitivas de tratamento de lista circular

	AUTOR		: Hevelton Araujo Junior

	VERSAO		: 02 - 28/09/92

	HISTORICO DAS EDICOES

00 - Edicao Inicial									07/01/92		H.Junior
01 - Passar de DOS para QNX							25/09/92		H.Junior
02 - Modificacao para lista circular				28/09/92		H.Junior

******************************************************************************/


   /*--- VERIFICA SE JA FOI INCLUIDO ---*/

#ifndef INCL_LISTA_CIRCULAR
	#define INCL_LISTA_CIRCULAR


	/******************************/
	/*--- ARQUIVOS DE INCLUSAO ---*/
	/******************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Definicao.h>


	/***************************/
	/*--- DEFINICOES GERAIS ---*/
	/***************************/

/*--- Tamanho maximo da lista ---*/
#define  TAM_MAX_LISTA				1500 /*256*/

/*--- Tamanho do elemento da lista ---*/
#define	TAM_ELEMENTO				(sizeof (t_elem))

/*--- Operacoes possiveis com a lista ---*/
#define	INSERIR						1
#define	RETIRAR						2
#define	SUBSTITUIR					3
#define	CONSULTAR					4


	/**************************************/
	/*--- DEFINICOES DE TIPOS PROPRIOS ---*/
	/**************************************/

/*--- Define o tipo que sera considerado como elemento da lista; caso ---*/
/*--- queira utilizar a lista com um elemento diferente, modifique  a ---*/
/*--- definicao deste tipo e nao e' necessario fazer mais nada !!!!!! ---*/
typedef
  struct ElementoLista
  {
	byte	Cmd;
	byte	Tamanho;
	byte	Transacao;
	byte	NumNodo;
	word	Canal;
	int		Responder;
	word	TidCliente;
	word	Temporizador;
  } t_elem;

/*--- Define a estrutura de uma lista circular ---*/
typedef
  struct ListaCircular
  {
	int		NElementos;				/*--- numero de elementos na lista ---*/
	int		Retirar;				/*--- ponteiro para retirada da lista ---*/
	int		Inserir;				/*--- ponteiro para insercao na lista ---*/
	t_elem	Dados[TAM_MAX_LISTA];	/*--- os elementos prorpiamente ditos ---*/
  } t_lista;


	/**********************************/
	/*--- PROTOTIPACAO DAS FUNCOES ---*/
	/**********************************/

int ManipulaLista (t_lista *Lista, t_elem *Dado, int Posicao, int Acao);
int ListaCheia (t_lista *Lista);
int ListaVazia (t_lista *Lista);
int PriEleLista (t_lista *Lista);
int UltEleLista (t_lista *Lista);
int RetiraElemento (t_lista *Lista, t_elem *Dado, int Posicao);
int InsereElemento (t_lista *Lista, t_elem *Dado, int Posicao);
int SubstElemento (t_lista *Lista, t_elem *Dado, int Posicao);
int ConsultaElemento (t_lista *Lista, t_elem *Dado, int Posicao);
int NumElementos (t_lista *Lista);
void InitLista  (t_lista *Lista);

#endif /*--- ifdef INCL_LISTA_CIRCULAR ---*/

