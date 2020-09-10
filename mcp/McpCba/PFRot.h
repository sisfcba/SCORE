/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.1

	PROJETO		: CBA - Companhia Brasileira de Aluminio SA

	SISTEMA		: SALAS 120KA II e III

	ARQUIVO		: PFRot.h

	CONTEUDO	: Prologo do Modulo PFRot.c
                  Contem os prototipos das funcoes definidas em PFRot

	AUTOR		: Ricardo Teixeira Leite Mourao / Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	02/01/97

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
Data     | Descricao                                            | Autor 
-------------------------------------------------------------------------------
02/01/97 | Edicao inicial                                       | Ricardo-Leonel
-------------------------------------------------------------------------------
******************************************************************************/

#ifndef PFROT_H_
#define PFROT_H_

/*
-------------------------------------------------------------------------------
                           Prototipos
-------------------------------------------------------------------------------
*/
float		Calc_ConcBalanco(int cuba);
float		Calc_ConcDerivada(int cuba);
float       CalcConc(int cuba,double deriv);
float       calc_deriv(int cuba);
void		armazena(int cuba,float resist);
void        armazena_deriv(int cuba,float deriv);
void		Calc_Check(int cuba,float concder,float concbal);
float       FiltroResAlim(int cuba);
void        LiberaMoveAlim(int cuba);
void        ComumEstados(int cuba);
void        InitNormalCE(int cuba);
void        NormalCE(int cuba);
int         TransicaoNormalCE(int cuba, int subestado);
void        InitPreCheck(int cuba);
void        PreCheck(int cuba);
int         TransicaoPreCheck(int cuba,int subestado);
void        InitCheck1(int cuba);
int         Check1(int cuba);
int         TransicaoCheck1(int cuba,int subestado, int fimtrack);
void        InitCheck2(int cuba);
void        Check2(int cuba);
int         TransicaoCheck2(int cuba,int subestado1, int subestado2);
void        InitCheck3(int cuba);
int         Check3(int cuba);
int         TransicaoCheck3(int cuba, int subestado1, int subestado2, int fimderiv);
void        InitCheck4(int cuba);
int         Check4(int cuba);
int         TransicaoCheck4(int cuba, int estado,int fimtrack);
void        InitTrackingOver(int cuba);
byte        TrackingOver(int cuba);

#ifdef FILTRO_ALIM_BUTTER
double		filtra(int cuba);
#endif

#endif
/* -- Fim do arquivo PFRot.h -- */
