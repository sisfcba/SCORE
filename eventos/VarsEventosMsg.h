/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: VarsEventosMsg.h

	CONTEUDO	: Prologo do EventosMsg - Eventos
                  Contem as definicoes das variaveis globais do modulo

	AUTOR		: Joao Thomaz Pereira 

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0		  -		  DATA	: 23/09/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
dd/mm/aa | Descricao                                            | autor
-------------------------------------------------------------------------------
22/06/94 | Edicao inicial de migracao para o QNX 4.2			| Leonel
-------------------------------------------------------------------------------
******************************************************************************/

/*
--------------------------------------------------------------------------------
 Variaveis globais
--------------------------------------------------------------------------------
*/

DECL	char 	(*BufferEv)[TAM_BUF_ALA+1];
DECL	char 	*EndIniBuf[MAX_OPREDE+1];
DECL	char 	*EndFimBuf[MAX_OPREDE+1];
DECL	char	*Pini[MAX_OPREDE+1];
DECL	char	*Pfim[MAX_OPREDE+1];
DECL	int		TotLivres[MAX_OPREDE+1];
DECL	int		NMsg[MAX_OPREDE+1];
DECL	t_con_rede ConRede, *PConRede;
DECL	int		TotArea;
DECL	int		MaxTerm;
DECL	int		MaxOpRede;
DECL	int		SeqTmpEv;
DECL	t_desc_ev *PDescEv;
#ifdef	TESTA_SEMAF_REDE
DECL	int		SemafRede;
#endif

DECL	char TmpMsg[80];
