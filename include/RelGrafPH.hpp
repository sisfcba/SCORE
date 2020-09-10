/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.43

	PROJETO  : Todos
	
	SISTEMA  : Todos
	
	ARQUIVO  : RelGrafPH.hpp

	CONTEUDO : Contem as definicoes de todas as classes e constantes
			   especificas dos relatorios graficos de cuba e linha.
			   Possui as definicoes das estruturas de dados da
			   base de dados em area comum de memoria que conteem as
			   configuracoes e os valores usados pelos relatorios.

	AUTOR    : Alexandre Bandeira

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C/C++ - V10.6

	VERSAO   : 1.0		  -	  DATA  : 07/06/99

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
07/06/99 | Edicao Inicial                                       | Bandeira
-------------------------------------------------------------------------------
******************************************************************************/

#ifndef		_RELGRAFPH
  #define		_RELGRAFPH

#include <string.h>

#if defined(__cplusplus)
extern "C" {
#endif

#include <Definicao.h>
#include <ScoreConst.h>
#include <Eventos.h>
#include <RelGraf.h>

#define	REL_PAG_HOME	0
#define	REL_PAG_PGDN	1
#define	REL_PAG_PGUP	2
#define	REL_PAG_END		3

#if defined(__cplusplus)
};
#endif

//
//  **** Definicao das constantes ****
//

//
//  **** Declaracao das classes ****
//

//
// Classe CPena - Classe de uma pena do Grafico Cubas/Linha
//
class	CPena
{
  private:
	time_t			cmBaseT;				// base de tempo em segundos
	time_t			cmBaseT2;				// base de tempo auxiliar em segundos
	time_t			cmHoraUltAmostra;		// hora da ultima amostra de 2m 
	short int		cmTamTelaVal;			// numero de pontos em tela
	short int		cmTamBufVal;			// numero de pontos no buffer maximo
	short int		cmTamBufValReal;		// numero de pontos no buffer real
	short int		cmTamBufEv;				// numero de eventos
	short int		cmIndAtualTela;			// indice atual cursor
	short int		cmIndAtualBuf;			// indice atual no buffer
	short int		cmIncTela;				// incremento para movimentacao do cursor
	short int		cmNumEvs;				// numero de eventos no buffer
	short int		cmNumEvsAux;			// numero de eventos no buffer auxiliar
	short int		cmFCompacta;			// fator de compactacao
	t_cnf_pena		cmCfgPena;				// configuracao para pena
	float			*cmpVal;				// ponteiro para a area de valores
	t_rec_ev		*cmpRecEv;				// ponteiro para a area de eventos
	t_rec_ev		*cmpRecEvAux;			// ponteiro para a area de eventos auxiliar
 	time_t			*cmpTime;				// ponteiro p/ buffer de batidas do MCC

	short int		AlocaVal()				{ cmpVal = new float[cmTamBufVal];
											  if(!cmpVal) return 0;
												else return 1; }
	short int		AlocaEv()				{ cmpRecEv = new t_rec_ev[cmTamBufEv];
											  if(!cmpRecEv) return 0;
												else return 1; }
	short int		AlocaEvAux()			{ cmpRecEvAux = new t_rec_ev[cmTamBufEv];
											  if(!cmpRecEvAux) return 0;
												else return 1; }
  public:
	time_t			BaseT()							{ return cmBaseT; }
	time_t			HoraUltAmostra()				{ return cmHoraUltAmostra; }
	time_t			HoraUltAmostra2()				{ return *cmpTime; }
	void			HoraUltAmostra( time_t Hora )	{ cmHoraUltAmostra = Hora; }
	short int		TamTelaVal()					{ return cmTamTelaVal; }
	short int		TamBufVal()						{ return cmTamBufVal; }
	void			TamBufValReal(short int aTam)	{ cmTamBufValReal = aTam; }
	short int		TamBufEv()						{ return cmTamBufEv; }
	short int		IndAtualTela()					{ return cmIndAtualTela; }
	void			IndAtualTela( short int Ind )	{ cmIndAtualTela = Ind; }
	short int		IndAtualBuf()					{ return cmIndAtualBuf; }
	void			IndAtualBuf( short int Ind )	{ cmIndAtualBuf = Ind; }
	short int		IncTela()						{ return cmIncTela; }
	short int		NumEvs()						{ return cmNumEvs; }
	void			NumEvs( short int Num )			{ cmNumEvs = Num; }
	short int		NumEvsAux()						{ return cmNumEvsAux; }
	void			NumEvsAux( short int Num )		{ cmNumEvsAux = Num; }
	void			FCompacta( short int aFat )		{ cmFCompacta = aFat; }
	/* inicio configuracao da pena */
	short int		Tabela()						{ return cmCfgPena.Tabela; }
	unsigned int	OffsetVar()						{ return cmCfgPena.OffsetVar; }
	float			FatConv()						{ return cmCfgPena.FatConv; }
	short int		TipoVar()						{ return cmCfgPena.TipoVar; }
	const char		*TagPena()						{ return (char const *)cmCfgPena.TagPena; }
	float			LimInf()						{ return cmCfgPena.LimInf; }
	float			LimSup()						{ return cmCfgPena.LimSup; }
	unsigned		CorPena()						{ return cmCfgPena.CorPena; }
	void			CfgPena( const void *p )		{ memcpy((void*)&cmCfgPena,p,sizeof(t_cnf_pena)); }
	void			CfgPena2( void *p )				{ memcpy((void*)p,(const void *)&cmCfgPena,sizeof(t_cnf_pena)); }
	/* fim configuracao da pena */
	float			Valor( short int Ind )			{ return *(cmpVal+Ind); }
	void			Valor( short int Ind, float Val )	{ *(cmpVal+Ind) = Val; }
	t_rec_ev		*RecEv( short int Ind )			{ return (cmpRecEv+Ind); }
	t_rec_ev		*RecEvAux( short int Ind )		{ return (cmpRecEvAux+Ind); }
	void			RecEv( short int Ind, t_rec_ev *RecEv )	{ memcpy((void*)(cmpRecEv+Ind),(const void*)RecEv,sizeof(t_rec_ev)); }
	float			*Pagina( short int Acao )		{ float *pVal;
													  cmIndAtualTela=0;
 													  switch(Acao){
														case REL_PAG_HOME:cmIndAtualBuf=0;
														  break;
														case REL_PAG_PGDN:
														  cmIndAtualBuf=(short int)(cmIndAtualBuf+cmTamTelaVal);
														  if(cmIndAtualBuf>=cmTamBufValReal)
															cmIndAtualBuf=(short int)(cmTamBufValReal-cmTamTelaVal);
														  break;
														case REL_PAG_PGUP:
														  cmIndAtualBuf=(short int)(cmIndAtualBuf-cmTamTelaVal);
														  if(cmIndAtualBuf<0)
														    cmIndAtualBuf=0;
														  break;
														case REL_PAG_END:cmIndAtualBuf=(short int)(cmTamBufValReal-cmTamTelaVal);
														  break; }
													  pVal=(cmpVal+cmIndAtualBuf); return pVal; }
	float			*Cursor1( short int Acao )		{ float *pVal;
													  switch(Acao){
														case 0:cmIndAtualTela++;
														  if(cmIndAtualTela>=cmTamTelaVal)
														    cmIndAtualTela=0;
														  break;
														case 1:cmIndAtualTela--;
														  if(cmIndAtualTela<0)
														    cmIndAtualTela=(short int)(cmTamTelaVal-1);
														  break; }
													  pVal=(cmpVal+cmIndAtualBuf+cmIndAtualTela); return pVal; }
	float			*Cursor2( short int Acao )		{ float *pVal;
													  switch(Acao){
														case 0:cmIndAtualTela+=cmIncTela;
														  if(cmIndAtualTela>=cmTamTelaVal)
														    cmIndAtualTela=0;
														  break;
														case 1:cmIndAtualTela-=cmIncTela;
														  if(cmIndAtualTela<0)
														    cmIndAtualTela=(short int)(cmTamTelaVal-1);
														  break; }
													  pVal=(cmpVal+cmIndAtualBuf+cmIndAtualTela); return pVal; }
	time_t			HoraPosicao()					{ time_t hora;
											          hora=*(cmpTime+cmIndAtualBuf+cmIndAtualTela);
													  return hora;
													}
	time_t			HoraIni()						{ time_t hora;
													  hora=*(cmpTime+cmIndAtualBuf);
													  return hora; }
	time_t			HoraFim()						{ time_t hora;
												      hora=*(cmpTime+cmIndAtualBuf+cmTamTelaVal-1);
													  return hora; }
	void			EvsPosicao()					{
		 											  short int i;
													  cmNumEvsAux=0;
												  	  if(HoraPosicao()!=0)
												  	  {
													    for(i=0;i<cmTamBufEv;++i)
													    {
													      if((cmpRecEv+i)->DataEv<=HoraPosicao()&&
														     (cmpRecEv+i)->DataEv>(HoraPosicao()-cmBaseT*cmFCompacta))
														  {
														     memcpy((void*)(cmpRecEvAux+cmNumEvsAux),
																    (const void*)(cmpRecEv+i),sizeof(t_rec_ev));
														     ++cmNumEvsAux;
														  }
														}
													  }
													}

	CPena()							{ cmpVal=NULL;
									  cmpRecEv=NULL;
									  cmpRecEvAux=NULL; }
	IniPena( time_t *apTime, short int aTamTelaVal, short int aTamBufVal,
		   	 short int aTamBufEv, short int aIncTela,
		   	 time_t aBaseT, short int aFCompacta )
									{ if(cmpVal!=NULL)
										delete [] cmpVal;
									  if(cmpRecEv!=NULL)
										delete [] cmpRecEv;
									  if(cmpRecEvAux!=NULL)
										delete [] cmpRecEvAux;
									  cmTamTelaVal=aTamTelaVal;
									  cmTamBufVal=aTamBufVal;
									  cmTamBufValReal=aTamBufVal;
									  cmTamBufEv=aTamBufEv;
									  cmIncTela=aIncTela;
									  cmBaseT=aBaseT;
									  cmFCompacta=aFCompacta;
								  	  cmIndAtualTela=0;
								  	  cmIndAtualBuf=0;
									  cmCfgPena.Tabela=-1;
									  cmpTime = apTime;
									  if(cmTamBufEv!=0){ AlocaEv(); AlocaEvAux(); }
									  AlocaVal(); }															

	~CPena()						{ if(cmpVal!=NULL)
										delete [] cmpVal;
									  if(cmpRecEv!=NULL)
										delete [] cmpRecEv;
									  if(cmpRecEvAux!=NULL)
										delete [] cmpRecEvAux; }
};

//
// Classe CGrafico - Classe de um Grafico Generica
//
class	CGrafico 
{
  private:
    unsigned        cmCorFundo;
    unsigned        cmCorGrade;
	short int		cmNumPenas;
	short int		cmTipoGraf;	// 0 Trend, 1 Alarmes
	short int		cmFCompacta; // fator de compactacao
	CPena			*cmpPenas;
  public:
	unsigned		CorFundo()						{ return cmCorFundo; }
	void			CorFundo( unsigned aCor )		{ cmCorFundo = aCor; }
	unsigned		CorGrade()						{ return cmCorGrade; }
	void			CorGrade( unsigned aCor )		{ cmCorGrade = aCor; }
	short int		NumPenas()						{ return cmNumPenas; }
	void			NumPenas( short int aTam )		{ cmNumPenas = aTam; }
	short int		TipoGraf()						{ return cmTipoGraf; }
	void			FCompacta(short int aFat)		{ short int i;
													  cmFCompacta = aFat;
										  			  for(i=0;i<cmNumPenas;++i) {
										  				Pena(i)->FCompacta(aFat); } }
	CPena			*Pena( short int aPena )		{ return (cmpPenas+aPena); }
	short int		AlocaPenas()					{ cmpPenas = new CPena[cmNumPenas+1];
													  if(!cmpPenas) return 0;
														else return 1; }
	CGrafico()							{ cmpPenas=NULL; }
	IniGrafico( time_t *apTime, short int aNumPenas,
				short int aTamTelaVal, short int aTamBufVal,
		   		short int aTamBufEv, short int aIncTela,
		   		time_t aBaseT, short int aTipo, short int aFCompacta )
										{ short int i;
										  if(cmpPenas!=NULL)
										    delete [] cmpPenas;
										  cmNumPenas = aNumPenas;
										  cmTipoGraf = aTipo;
										  cmFCompacta = aFCompacta;
										  AlocaPenas();
										  for(i=0;i<aNumPenas;++i) {
										  	Pena(i)->IniPena(apTime,aTamTelaVal,
												aTamBufVal,aTamBufEv,
												aIncTela,aBaseT,aFCompacta); } }
	~CGrafico()							{ if(cmpPenas!=NULL)
										    delete [] cmpPenas; }
};

//
// Classe CRelGraf - Classe de um Relatorio Grafico Generico
//
class	CRelGraf
{
  private:
	short int		cmNumGraf;
	short int		cmTamBufVal;
	CGrafico		*cmpGraf;
	time_t			*cmpGrafTime;
	short int		cmFCompacta;
  public:
	short int		NumGraf()						{ return cmNumGraf; }
	void			NumGraf( short int aTam )		{ cmNumGraf = aTam; }
	CGrafico		*Graf( short int aGraf )			{ return (cmpGraf+aGraf); }
	short int		AlocaGraf()						{ cmpGraf = new CGrafico[cmNumGraf];
													  if(!cmpGraf) return 0;
														else return 1; }
	short int		AlocaGrafTime()			{ cmpGrafTime = new time_t[cmTamBufVal];
											  if(!cmpGrafTime) return 0;
												else return 1; }
	time_t			GrafTime(short int Index)	{ return *(cmpGrafTime+Index); }
	void			GrafTime(time_t Hora,short int Index)	{ *(cmpGrafTime+Index) = Hora; }
	short int		TamBufVal()			{ return cmTamBufVal; }
	CRelGraf()							{ cmpGraf=NULL; cmpGrafTime=NULL; }
	short int		FCompacta()						{ return cmFCompacta; }
	void			FCompacta(short int aFat)		{ short int i;
													  cmFCompacta = aFat;
										  			  for(i=0;i<cmNumGraf;++i) {
										  				Graf(i)->FCompacta(aFat); } }
	IniRelGraf( short int aNumGraf, short int aNumPenas,
				short int aTamTelaVal, short int aTamBufVal,
		   		short int aTamBufEv, short int aIncTela,
		   		time_t aBaseT, short int aAlarme, short int aFCompacta )
										{ short int i;
										  if(cmpGraf != NULL)
										    delete [] cmpGraf;
										  if(cmpGrafTime != NULL)
										    delete [] cmpGrafTime;
										  cmNumGraf = aNumGraf;
										  cmTamBufVal = aTamBufVal;
										  AlocaGraf();
										  AlocaGrafTime();
										  for(i=0;i<cmNumGraf;++i) {
											if(aAlarme==1&&(i+1)==cmNumGraf)
											  Graf(i)->IniGrafico(cmpGrafTime,MAX_PENAS_ALARME/*aNumPenas*/,
												aTamTelaVal,aTamBufVal,
		   										aTamBufEv,aIncTela,
		   										aBaseT,1,aFCompacta);
											else
											  Graf(i)->IniGrafico(cmpGrafTime,aNumPenas,
												aTamTelaVal,aTamBufVal,
		   										aTamBufEv,aIncTela,
		   										aBaseT,0,aFCompacta); } }
	~CRelGraf()							{ if(cmpGraf!=NULL)
										    delete [] cmpGraf;
										  if(cmpGrafTime!=NULL)
											delete [] cmpGrafTime; }
};

#endif

/* -- fim do arquivo RelGrafPH.hpp -- */
