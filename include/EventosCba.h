/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO  : CBA - Companhia Brasileira de Aluminio SA

	SISTEMA  : Automacao das salas II e III

	ARQUIVO  : EventosCba.h

	CONTEUDO : Contem as definicoes de eventos para o 
			   Sistema de Controle de Reducoes CBA II e III.

	AUTOR    : Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO   : 1.0		  -	  DATA  : 18/06/96

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
$Id: EventosCba.h,v 1.6.4.1 2015/06/30 22:44:54 clage Exp $

$Log: EventosCba.h,v $
Revision 1.6.4.1  2015/06/30 22:44:54  clage
Alteracoes para sala II com ATN8 e expansao da base de dados.

Revision 1.6  2008/08/04 20:32:01  leo
Incluido evento ReleMM.

Revision 1.5  2007/03/01 18:02:17  leo
Inclusao evento de manobra de cruzeiro.

Revision 1.4  2004/07/28 19:36:24  leo
Inclusao de eventos de diferenca de leitura entre principal e reserva para
a CBA sistemas com 2 atn1.4. Gerado pelo HotStBy.

******************************************************************************/

#ifndef		_EVENTOS_CBA_H

#define _EVENTOS_CBA_H

/*
--------------------------------------------------------------------------------
						Codigo dos Eventos
--------------------------------------------------------------------------------
*/
/* -- Indice dos eventos do projeto para o descritor de eventos -- */
#define	AJUSTE_CAMISA			100 /*-- Tratamento de ajuste de camisa --*/
#define	SUBIDA_AUT_CAMISA		101 /*-- Subida automatica de camisa --*/
#define	DESCIDA_AUT_CAMISA		102 /*-- Descida automatica de camisa --*/
#define	EV_MUDA_ALIMENT			103 /*-- Mudanca de algoritmo de alimentacao --*/
#define EV_MUDA_EST             104 /*-- Mudanca de subestado de alimentacao --*/
#define EV_MUDA_EST_BARRA       105 /*-- Mudanca de estado de alimentacao (barra quebra crosta) -- */
#define EA_NAO_TERMINADO		106 /*-- Indica que nao foi possivel terminar efeito anodico automaticamente -- */
#define	TABELA_ELIM_EA          107 /*-- Evento de tabela de eliminacao de EA --*/
#define	TABELA_EA_NAO_ATIVADA   108 /*-- Tabela de elim. de EA nao ativada --*/
#define DESCIDA_MAN_CAMISA		109 /*-- Descida manual de camisa --*/
#define	INICIO_QUEB_PREV		110 /*-- Inicio da quebrada preventiva --*/
#define	FIM_QUEB_PREV			111 /*-- Fim da quebrada preventiva --*/
#define	INIB_QUEB_PREV			112 /*-- Inibicao quebrada preventiva por operacao --*/
#define	CAMISA_NAO_AJUSTADA		113 /*-- Camisa nao ajustada --*/
/* -- Alteracao - Inicio - 09/05/2002 - Leonel - Inclusao da sala 7 125ka -- */
#define	SOPROU					114 /*-- Acionado sopro --*/
/* -- Alteracao - Fim - 09/05/2002 - Leonel - Inclusao da sala 7 125ka -- */
/* -- Alteracao - Inicio - Robson - 03/12/2002 - Tempo para sinalizacao de falta de ruido -- */
#define	FALHARUIDO				115 /*-- Houve falha para calculo de ruido --*/
/* -- Alteracao - Fim - Robson - 03/12/2002 - Tempo para sinalizacao de falta de ruido -- */
#define	EV_TAB_PARTIDA			116	/*-- Tabela de partida de cubas -- */
#define	SOPRO_ESPECIAL			117	/*-- Algoritmo de sopro especial -- */
#define	DIFF_RESERVA_LINHA		118 /*-- Diferenca leitura Atn1.4 do reserva em relacao ao principal -- */
#define	DIFF_RESERVA_CUBA		119 /*-- Diferenca leitura Atn1.4 do reserva em relacao ao principal -- */
#define	EV_MANOBRA_CRUZEIRO		120 /*-- Informa inicio de manobra de cruzeiro -- */
#define	EV_RELEMM				121 /*-- Evento para indicar rele tempo MM ativo/desativo -- */
#define	EV_DB					122 /*-- Evento para indicar derivada baixa -- */
#define	EV_OSCIL				123 /*-- Evento para indicar oscilacao -- */
#define	EV_EALINHA				124 /*-- Indicacao de provavel efeito em cuba fora de rede -- */
#define	EV_FORMABANHO			125 /*-- Indica formacao de banho  -- */
#define	EV_DESLIGASALA			126 /*-- Indica desligamento de sala pelo sistema -- */
#define	EV_SIRENE				127 /*-- Indica acionamento da sirene -- */
#define	EV_SMARTFEED			128 /*-- Evento de SmartFeed acionado no momento da quebra -- */
#define	EV_CORREBANHO			129 /*-- Evento de corrida de banho -- */
#define	EV_AEK					130 /*-- Evento de trativa de efeito anodico -- */
#define	EV_AGARRACAM			131 /*-- Evento de agarramento de camisa -- */
#define	EV_FALHAPF				132 /*-- Evento de Falha de retorno de Sinal PF -- */
#define	EV_FIMCHECK				133 /*-- Evento de retorno de fim de check -- */
#define	EV_PFCBA				134 /*-- Evento de mudanca de estado soderberg futuro -- */
#define	INC_INIBIDO				135 /*-- Evento de inibicao de incremento -- */
#define	EV_FATORPF				136 /*-- Evento de alteracao de fator pf -- */
#define	EV_TENDOVER				137 /*-- Evento de alarme de tendencia over -- */
#define	INICIO_QUEBCAB			138 /*-- Evento de quebra de cabeceira -- */
#define EV_PROVQUEB				139 /*-- Evento de provável quebra sem sinalização --*/



#endif
