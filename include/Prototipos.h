/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO  : CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA  : AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO  : Prototipos.h

	CONTEUDO : Contem os prototipos de todas as funcoes de biblioteca do
               SCORE

	AUTOR    : Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO   : 2.0		  -	  DATA  : 05/05/94

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
05/05/94 | Edicao inicial de migracao para o QNX 4.2				| Leonel
-------------------------------------------------------------------------------
09/11/95 | Acrescentada funcao ConsCubasOpe e alguns defines		| Leonel
-------------------------------------------------------------------------------
17/11/95 | Transferidas variaveis RET_FUNCAO_OK e RET_FUNCAO_ERR do	| Carlos
         | prologo Relatorios.h										| 
-------------------------------------------------------------------------------
11/05/99 | Incluido prototipo da funcao GeraMascRem                	| Leonel
-------------------------------------------------------------------------------
******************************************************************************/
/*********************************** Revisoes ********************************\
$Id: Prototipos.h,v 1.6.4.1 2012/09/28 17:09:16 leo Exp $

$Log: Prototipos.h,v $
Revision 1.6.4.1  2012/09/28 17:09:16  leo
Alteracoes para criacao do kit de desenvolvimento para a CBA usando como base
a versao 5.03.0015. Criado branch no CVS com nome PRODUCAO_CBA125KA a partir
da versao indicada. Criado diretorio de runtime /usr/score_cba_125ka.

Revision 1.6  2008/07/02 20:23:43  alex
nao subir camisa junto com movimentacao de anodo

Revision 1.5  2008/04/24 18:50:53  leo
Incluido prototipos das funcoes divididas do PegaRelGraf.

Revision 1.4  2003/09/30 19:29:40  leo
Criacao de funcoes separadas de ShmMap e ShmSize.
Inclusao de funcao para mapear segmento dummy read_only.

Revision 1.3  2003/09/25 19:24:07  leo
Inclusao da funcao ImprimeTamanhos na lib.

Revision 1.2  2003/03/13 20:51:22  leo
Inclusao de variaveis e constantes para o tratamento da tabela de partida
de cubas. Criacao de novas funcoes e inclusao de seus prototipos.

\*********************************** Revisoes ********************************/

#ifndef		_PROTOTIPOS_H

#define		_PROTOTIPOS_H

/* -- Inclui prologo_score para definicao de tipos -- */
#include	<Score.h>
#include	<Remotas.h>
#include	<TiposOpeW.h>
#include	<Eventos.h>

/* -- Algumas definicoes das funcoes -- */
#define		ERRO_OK				0

/* -- ConsCubasOpe -- */
#define		ECUBAINIMFIM		2000	/* cuba inicial > final */
#define		ECUBAINIINV			2001	/* cuba inicial invalida */
#define		ECUBAFIMINV			2002	/* cuba final invalida */

/* -- Acoes para AtualBufMensIns -- */
#define		EVMSGINS_HOME		0
#define		EVMSGINS_END		1
#define		EVMSGINS_PGUP		2
#define		EVMSGINS_PGDN		3
#define		EVMSGINS_SCROLL		4
#define		EVMSGINS_EXIT		5

/* -- CfgRem e CfgAlimRem -- */
#define		REMOTA_CUBA			0
#define		REMOTA_OUTRAS		1
#define		OUTROS_NODOS		2

/* -- Acoes para a funcao InsereMascBits -- */
#define		RESET_BIT		0
#define		SET_BIT			1

/* -- Alteracao - inicio - Robson - 04/10/2000 - acionamento do PF novo -- */
/* -- Retorno de erro da funcao EnviaSequencia -- */
#define		ERRO_ALIMENTACAO	-2
/* -- Alteracao - fim - Robson - 04/10/2000 - acionamento do PF novo -- */


/* -- Prototipos -- */
int			  MontaTelaEv( char *evento );
void		  HelpEv( char *evento );
void		  EmiteAlarme(char *format, int dispositivo);
void		  EmiteErro(char *format, int dispositivo);
char		  *DataHora(void);
char		  *DataHoraMin(void);
int			  CriaAreaGlobal(int nodo_controle,t_comum **PComum);
void		  EmiteAlarmeFor(int Dispositivo,char *Formato, ...);
void		  EmiteErroFor(int Dispositivo,char *Formato, ...);
void		  AguardaPartida(void);
int			  MoveAnodo(int Cuba,int DuracaoMov,int SentidoMov);
int			  GeraEvento(int Evento, int CubaIni, int CubaFim, ...);
int			  ComandaLampEa(int Cuba,int Acao);
int			  ComandaSaidaRem(int Cuba,int Acao,int BitAcao,int Tempo);
int			  ComandaSaidaORem(int Ind,int Acao,int BitAcao,int Tempo);
int			  CmdSaidaRem(int Canal, int Remota,int Acao,int BitAcao,int Tempo);
int			  ComandaSirene(int Cuba,int Acao);
void		  ComandaSirenes(int CubaIni,int CubaFim,int Acao);
void		  ComandaSalvaBd(int Acao,int TipoResp);
int 		  ConsCubasOpe(int CubaInicial, int CubaFinal);
int			  CriaTarefa(int Modulo,int InformaBd);
int			  PegaComum(t_comum **PComum);
int			  PegaComumLeitura(t_comum **PComum);
void		  SoundAlarm(void);
void		  SoundAlarm2(void);
void		  SoundSiren(void);
void		  SoftAlarm(void);
void		  Siren(void);
void		  Play(int Octave, int Note, int Duration);
int			  EnvTabEliminaEa(int Cuba, t_elimina_ea *PTab);
int			  LeEntRem(int Cuba,t_mascara_bits *Masc);
char		  *FileName(char *Path);
int			  ConvRemCuba(int Canal,int Nodo);
int			  ConvRemOutras(int Canal,int Nodo);
int			  ConvCubOperScore(int CubaOperador);
int			  ConvCubScoreOper(int CubaScore);
int			  ConsisteCubas(int CubaInicial, int CubaFinal);
int			  ValExcCubas(char *PtStr, int *PTab);
int			  ValidaCuba(int *PTab, int Cuba);
char		  *NomeSpoolOp(void);
void		  RecEvento(int Tipo, char *PNomeDisp);
void		  FimScore(int codigo, char *par1, char *par2, char *par3);
void		  error(char *format,...);
double		  Round(double Valor);
int			  ScoreBd(nid_t nodo,int tabela,int acao,void *ptab,
					unsigned long offset,long int tamanho);
void		  MontaHoraMin(long Valor, char *Str, char *Formato);
int			  LocalizaScore(int IdentReducao);
int			  CubaScoreGrupo(int Indice);
void		  *EnderTab(int tabela, unsigned long offset, int *semaf);
unsigned long OffsetTab(int tabela, unsigned long offset, int registro);
int			  PegaRelGraf(void);
int			  PegaRelGraf2(void);
int			  PegaRelGrafCnf(void);
int			  PegaRelGrafVal(void);
int			  PegaRelGrafEvCuba(void);
int			  PegaRelGrafMini(void);
char		  *MontaCabecScore(void);
int			  CfgRem(int TipoRem, int Indice);
int			  CfgRemCuba(int Canal, int Remota);
int			  CfgRemOutras(int Canal, int Remota);
int			  LigSaiTmpGSai(int Canal, int Remota, int Esperar, t_liga_saida_temp *Parametros);
int			  BlqSaiDigGSai(int Canal, int Remota, int Esperar, t_bloq_saida_temp *Parametros);
void		  InsereMascBits(t_mascara_bits *Masc,int Bit,int Acao);
int 		  ConsHoraMin(char *Duracao, int *Tempo);
void		  MontaHoraMinSeg(long Valor, char *Str, char *Formato);
int 		  ConsHoraMinSeg(char *Duracao, int *Tempo);
int			  ComandaAlimRem(int Cuba,int Tempo,int Quebrador);
int			  CfgAlimRem(int TipoRem, int Indice);
int			  CfgAlimCuba(int Canal, int Remota);
int			  CfgAlimOutras(int Canal, int Remota);
int			  SeletorQueb(int Cuba,int Acao, int Pistao);
int			  LeFiltroCubas(char *arq, t_filtrosPD *filtro);
char		  *NoticeScore( char *label, char *title, char *buttons,
                   char *options, char *format, ... );
int 		  MontaTeclado( int Wid, int Pid, char *TagCampo, int TamCampo, byte Hide );
void		  IniNumAlgCtr(void);
int			  AlgControle(int Cuba, short unsigned Alg);
int			  AlgControleGlobal(int Cuba, short unsigned Alg);
int			  AlterouNumAlgCtr(int Cuba, short unsigned Alg);
int			  InseriuNumAlgCtr(int Cuba, short unsigned Alg);
int			  RetirouNumAlgCtr(int Cuba, short unsigned Alg);
int			  AlgFicouAtivo(short unsigned AlgCtrlDia, short unsigned Alg);
t_rec_ev	  *IniLeArqEv( t_LeEventos *BufEv, t_rec_ev *Eventos, int *NumRegs );
int			  CriaSegmento(char *NomeSeg, unsigned Tamanho, void **PDados);
int			  CriaSegmentoRead(char *NomeSeg, unsigned Tamanho, void **PDados);
int			  LeArq(char *NomeArquivo, unsigned Tamanho, void *PDados, long offset);
int			  LeArqSegmento(char *NomeArquivo, unsigned Tamanho, void **PDados,
					  char *NomeSeg);
int			  LeValGraf(int nodo);
int			  GravaValGraf( long reg_linha, long reg_cuba, long cuba_ini, long cuba_fim, short int operacao );
int			  LeGrupoCubas(t_grupo_cuba *PGrupo);
int 		  SemafConf(int Semaf, int Oper);
int 		  AtualBufMensIns( t_rec_ev *PRec,	t_buf_ev *PBufGlo,
					  			int NumRegs, 		int NumLinhas,
					  			int *Ini,			int *Fim,
					  			int Tecla, 		int Filtro, void *P );
int			  MonitoraCiclo(int TempoTimeout);
void		  GeraMascRem(int Subrede, unsigned long *Masc1, unsigned long *Masc2);
size_t		  strlenMB( char *apS, size_t aJust );
char		  *NomeOper(int Operador);
int			  GetLoginPhindows(void);
void		  MontaParm( void *Org, char *Dest, int Tam, int Dec, int Tipo );
int			  MudaEstadoCuba(const int aCuba, const int aEstado, const int aOperador);
int			  MudaAutManCuba(const int aCuba, const int aEstado, const int aOperador);
int			  MudaMoveAnodoCuba(const int aCuba, const double aDuracao,
				   			const int aSentido, const int aOperador);
int			  ImprimeTamanhos(int lista);
int			  ShmSize(char const *NomeMem);
int			  ShmMap(void **PMem, char const *NomeMem, int TamMem);
int			  ShmMapRead(void **PMem, char const *NomeMem, int TamMem);
int			  ShmMapDummy(void);
int			  AlteraAjusteCamisa(const int aCuba, const int aAcao, const int aTempo,
								 const int aOperador, char *aPMsg);
int			  MudaQuebPrevCuba(const int aCuba, const int aEstado, const int aTempo,
								 const int aOperador);
int			  AtivaTabIncCuba(const int aCuba, const int aAcao, const int aOperador);

#endif
