/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO		: EventosMsg.h

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
26/12/95 | Acrescentado tratamento de alarmes para PAl			| Carlos
-------------------------------------------------------------------------------
******************************************************************************/

/*
--------------------------------------------------------------------------------
                         Declaracao de Constantes do Programa
--------------------------------------------------------------------------------
*/

/* -- Compilacao condicional -- */
#define		INCLUI_IMP_NODO_OPERCAO

#define 	TAM_BUF_ALA			2048	/* Tamanho do buffer para eventos */
#define		EVENTO_INTERNO		1
#define		EVENTO_SISTEMA		2
#define		EVENTO_PRIORITARIO	3

#define		INDEFINIDO			-1
#define		CONSOLE_OPREDE		3
#define		TERMINAL_ST			4

#define	  	TAM_NOME_FILE		60
#define	  	TAM_MSG				67

#define  	ARQ_EV_TMP 			"/tmp/score/MsgEvTmp%d"

/*
--------------------------------------------------------------------------------
                         Definicao de macros
--------------------------------------------------------------------------------
*/

#define PegaDispositivo(CodeEv) ( PDescEv->DescEv[CodeEv].Dispositivo)
#define PegaGrupo(CodeEv) ( PDescEv->DescEv[CodeEv].Grupo)
#define PegaMsgEv(CodeEv)		( &PDescEv->DescEv[CodeEv] )
#define PegaEvCuba(CodeEv) ( PDescEv->DescEv[CodeEv].EvCuba)

/*
--------------------------------------------------------------------------------
                         Definicao de Tipos
--------------------------------------------------------------------------------
*/
typedef
  struct IdentConsoleRede
  {
	struct LocConsoleRede
	{
	  int		IndBufEv;
	  char		Nome[TAM_NOME_FILE];
	}IdCon[MAX_OPREDE + 1];
  } t_con_rede;

/*
--------------------------------------------------------------------------------
                         Definicao de prototipos das funcoes
--------------------------------------------------------------------------------
*/
void ClrMsg(char *PNomeDisp, int Device);
void ShowEvento (char *Buf, char *PNomeDisp, int Device);
void WriteMessage(t_rec_ev *PMsgEv, int TipoEv);
void InitEvMsg(void);
void TiraBufAla(char *Msg, int IndBufEv);
void ReconheceAlarme(int Tipo, char *PNomeDisp);
void PoemBufAla(char *Msg, int Ncar, int IndBufEv);
void MontaMsgEv(char *PStr, t_rec_ev *PMsgEv);
void TrataEv(int IndBufEv,char *Msg,char *PNomeDisp,int Device);
char *PosLinCol(int Linha, int Coluna);
void ImprimeEv(int IndFila, char *PMsg, char *NomeLpt,int Semaforo);
int NodoOpAtivo(int Nodo);
void Bell(char *PNomeDisp);
