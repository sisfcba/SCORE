
/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.

	PROJETO		: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA		: AUTOMACAO DA SALA 120 KA I

	ARQUIVO		: definicao.h

	CONTEUDO	: Definicoes gerais para todos os programas

	AUTOR		: Constantino Seixas Filho / Leonel Vicente Mota Ivo

	VERSAO		: 1.1

	HISTORICO DAS EDICOES

******************************************************************************/

#ifndef		DEFINICAO_INCLUIDO

/*--------------------- Para controle de inclusao --------------------------*/
#define		DEFINICAO_INCLUIDO		1

/*--------------------- Tipos de dados gerais ------------------------------*/
typedef unsigned char byte;
typedef unsigned int  word;

/*--------- Macros para substituicao de tokens -----------------------------*/

#define		then
#define		begin		{
#define		end			}
#define		div			/
#define		mod			%
#define		and			&&
#define		or			||
#define		not			!
#define		andb		&
#define		orb			|
#define		notb		~
#define		xorb		^
#define		eq			==
#define		ne			!=

/*---------------- Teclas especiais -----------------------------------------*/
/**#define		CR		0x1E**/
/**#define		ESC		0x1b**/
/******************************************
#define     BELL    0x07
#define     BS      0x08
#define     NL      0x0D
#define     DEL     0xAC
#define		RUBOUT	0x7F
#define		UP_ARROW	0xA1
#define		DOWN_ARROW	0xA9
#define		LEFT_ARROW	0xA4
#define		RIGHT_ARROW	0xA6
#define		CTRL_LF_ARROW	0xB4
#define		CTRL_RG_ARROW	0xB6
#define		CTRL_UP_ARROW	0xB1
#define		CTRL_DN_ARROW	0xB9
#define		HOME		0xA0
#define		INS 		0xAB
#define		ERASE_LINE	0x18
#define		PG_UP		0xA2
#define		PG_DN		0xAA
#define		END		0xA8
#define		F1		0x81
#define		F2		0x82
#define		F3		0x83
#define		F4		0x84
#define		F5		0x85
#define		F6		0x86
#define		F7		0x87
#define		F8		0x88
#define		F9		0x89
#define		F10		0x8A
                                          ****************************/

/*--------------------------- Gerais ----------------------------------------*/
#define		VERDADEIRO	1
#define		FALSO		0

/* -------------------------------- MACROS --------------------------------- */
#define push_es()     asm("		push  es")
#define pop_es()      asm("		pop   es")


#endif
