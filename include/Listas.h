/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.1

	PROJETO		: ALBRAS - ALUMINIO BRASILEIRO SA

	SISTEMA		: PROTOTIPO PARA UMA SECAO DA REDUCAO II

	ARQUIVO		: Listas.h

	CONTEUDO	: Prologo das funcoes para manipulacao de listas encadeadas.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	21/12/95

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
21/12/95 | Edicao da versao 1.0                                 | Leonel
-------------------------------------------------------------------------------
******************************************************************************/
/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include	<Definicao.h>

/*
-------------------------------------------------------------------------------
                           Definicoes
-------------------------------------------------------------------------------
*/
#define		ERRO_LISTA_NOMEMORY				1
#define		ERRO_LISTA_ELEMENTOINVALIDO		2
#define		ERRO_LISTA_CHEIA				3

/*
-------------------------------------------------------------------------------
                           Macros
-------------------------------------------------------------------------------
*/
/*
--------------------------------------------------------------------------------
| PROTOTIPO   :  void *DadoElemLista(t_elem *plem);                            |
| OBJETIVO    :  Retorna um ponteiro para o dado de um elemento da lista.      |
|                O elemento fica intacto na lista. Normalmente utilizada para  |
|                pesquisar um elemento na lista.                               |
| CHAMADA     :  pdado=DadoElemLista(pelem);                                   |
| PARAMETROS  :  pelem - Ponteiro para o elemento da lista.                    |
| RETORNO     :  Ponteiro para o dado do elemento indicado.                    |
| AUTOR       :  Leonel Vicente Mota Ivo                                       |
--------------------------------------------------------------------------------
*/
#define		DadoElemLista(pelem)	(pelem->pdados)

/*
--------------------------------------------------------------------------------
| PROTOTIPO   :  t_elem *PrimeiroLista(t_lista *plista);                       |
| OBJETIVO    :  Retorna um ponteiro para o primeiro elemento da lista.        |
| CHAMADA     :  pelem=PrimeiroLista(plista);                                  |
| PARAMETROS  :  plista - ponteiro para a lista (retorno de CriaLista).        |
| RETORNO     :  Ponteiro para o primeiro elemento da lista. NULL se vazia.    |
| AUTOR       :  Leonel Vicente Mota Ivo                                       |
--------------------------------------------------------------------------------
*/
#define		PrimeiroLista(plista)	(plista->pinicio)

/*
--------------------------------------------------------------------------------
| PROTOTIPO   :  t_elem *UltimoLista(t_lista *plista);                         |
| OBJETIVO    :  Retorna um ponteiro para o ultimo elemento da lista.          |
| CHAMADA     :  pelem=UltimoLista(plista);                                    |
| PARAMETROS  :  plista - ponteiro para a lista (retorno de CriaLista).        |
| RETORNO     :  Ponteiro para o ultimo elemento da lista. NULL se vazia.      |
| AUTOR       :  Leonel Vicente Mota Ivo                                       |
--------------------------------------------------------------------------------
*/
#define		UltimoLista(plista)		(plista->pfim)

/*
--------------------------------------------------------------------------------
| PROTOTIPO   :  t_elem *ProxElemLista(t_elem *pelem);                         |
| OBJETIVO    :  Retorna um ponteiro para o proximo elemento da lista.         |
| CHAMADA     :  pelem_next=ProxElemLista(pelem);                              |
| PARAMETROS  :  pelem - ponteiro para a elemento do qual se quer o proximo.   |
| RETORNO     :  Ponteiro para o proximo elemento da lista. NULL se nao existe.|
| AUTOR       :  Leonel Vicente Mota Ivo                                       |
--------------------------------------------------------------------------------
*/
#define		ProxElemLista(pelem)	(pelem->pprox)

/*
--------------------------------------------------------------------------------
| PROTOTIPO   :  t_elem *AntElemLista(t_elem *pelem);                          |
| OBJETIVO    :  Retorna um ponteiro para o elemento anterior da lista.        |
| CHAMADA     :  pelem_ant=AntElemLista(pelem);                                |
| PARAMETROS  :  pelem - ponteiro para a elemento do qual se quer o anterior.  |
| RETORNO     :  Ponteiro para o elemento anterior da lista. NULL se nao existe|
| AUTOR       :  Leonel Vicente Mota Ivo                                       |
--------------------------------------------------------------------------------
*/
#define		AntElemLista(pelem)		(pelem->pant)

/*
-------------------------------------------------------------------------------
                           Tipos de dados
-------------------------------------------------------------------------------
*/

/* -- tipo padrao de elemento para lista -- */
typedef struct elem_lista
{
  struct elem_lista	*pant;	 /* link para o elemento anterior. NULL=1o. elem */
  struct elem_lista	*pprox;	 /* link para o proximo elemento. NULL=ult. elem */
  void				*pdados; /* ponteiro para os dados do elemento corrente */
} t_elem;

/* -- tipo para uma lista generica -- */
typedef struct lista
{
  t_elem	*pinicio;		/* inicio da lista. NULL=lista vazia */
  t_elem	*pfim;			/* fim da lista. NULL=lista vazia */
  int		max_elementos;	/* numero maximo de elementos para esta lista */
  int		num_elementos;	/* numero de elementos corrente da lista */
  int		tam_elemento;	/* tamanho do dado de cada elemento da lista */
} t_lista;

/*
-------------------------------------------------------------------------------
                           Prototipos
-------------------------------------------------------------------------------
*/
t_lista		*CriaLista(int MaxElementos, int TamElemento);
int			InsereElemLista(t_lista *plista, t_elem *pelem, void *pdado);
void		LeDadoLista(t_lista *plista, t_elem *pelem, void *pdado);
int			DeletaElemLista(t_lista *plista, t_elem *pelem);
int			RetiraElemLista(t_lista *plista, t_elem *pelem, void *pdados);
int			DeletaLista(t_lista *plista);

/* -- Fim do arquivo Listas.h -- */
