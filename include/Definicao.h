/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 3.0

	PROJETO  : CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA  : AUTOMACAO DA SALA 120 KA I

	ARQUIVO  : Definicao.h

	CONTEUDO : Macros para substituicao de tokens da linguagem C

	AUTOR    : Constantino Seixas Filho / Leonel Vicente Mota Ivo

	VERSAO   : 2.0          -      DATA  :28/08/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
01/11/94 | Incluida definicao do tipo boolean						| Leonel
-------------------------------------------------------------------------------
02/11/95 | Eliminadas definicoes de Begin e End devido a conflito	| Carlos
		 | com o prologo Qwindows.h									|
-------------------------------------------------------------------------------
******************************************************************************/

#ifndef		_DEFINICAO_H

/*
------------------------------------------------------------------------------
				Definicoes e Macros 
------------------------------------------------------------------------------
*/

/* -- Controle de inclusao -- */
#define		_DEFINICAO_H

/* -- Compilacao condicional -- */
#ifdef	PROGRAMA_PRINCIPAL
  #define	DECL
  #define	INIT(x)		=x
#else
  #define	DECL		extern
  #define	INIT(x)
#endif


#ifdef	ATIVA_DEPURACAO
  #define	DEPURA(x)	x
#else
  #define	DEPURA(x)
#endif

/* -- Macros para substituicao de tokens -- */
#define		then
//#define		begin	{
//#define		end		}
#define		Mod		%
#define		and		&&
#define		or		||
#define		not		!
#define		andb	&
#define		orb		|
#define		notb	~
#define		xorb	^
#define		eq		==
#define		ne		!=
#define		shr		>>
#define		shl		<<

/* -- Teclas especiais -- */
#define		TECLA_CR			0x1E
#define		TECLA_ESC			0x1b
#define		TECLA_BELL			0x07
#define		TECLA_BS			0x08
#define		TECLA_NL			0x0D
#define		TECLA_DEL			0xAC
#define		TECLA_RUBOUT		0x7F
#define		TECLA_UP_ARROW		0xA1
#define		TECLA_DOWN_ARROW	0xA9
#define		TECLA_LEFT_ARROW	0xA4
#define		TECLA_RIGHT_ARROW	0xA6
#define		TECLA_CTRL_LF_ARROW	0xB4
#define		TECLA_CTRL_RG_ARROW	0xB6
#define		TECLA_CTRL_UP_ARROW	0xB1
#define		TECLA_CTRL_DN_ARROW	0xB9
#define		TECLA_HOME			0xA0
#define		TECLA_INS 			0xAB
#define		TECLA_ERASE_LINE	0x18
#define		TECLA_PG_UP			0xA2
#define		TECLA_PG_DN			0xAA
#define		TECLA_END			0xA8
#define		TECLA_F1			0x81
#define		TECLA_F2			0x82
#define		TECLA_F3			0x83
#define		TECLA_F4			0x84
#define		TECLA_F5			0x85
#define		TECLA_F6			0x86
#define		TECLA_F7			0x87
#define		TECLA_F8			0x88
#define		TECLA_F9			0x89
#define		TECLA_F10			0x8A

/* -- Gerais -- */
#define		VERDADEIRO		1
#define		FALSO			0
#define		TRUE_VAL		1
#define		FALSE_VAL		0
#define		NUL				'\0'

/* -- Outras Macros -- */
#define	loop		  while(1)
#define	ZeraBit(Pal, Bit)		(Pal = (Pal andb (notb (1 << Bit))))
#define	SetaBit(Pal, Bit)		(Pal = (Pal orb (1 << Bit)))
#define	TestaBit(Pal, Bit)		((Pal andb (1 << Bit)) >> Bit)
#define	ZeraLBit(Pal, Bit)		(Pal = (Pal andb (notb (1L << Bit))))
#define	SetaLBit(Pal, Bit)		(Pal = (Pal orb (1L << Bit)))

/*
------------------------------------------------------------------------------
				Tipos de dados
------------------------------------------------------------------------------
*/
typedef unsigned char byte;
typedef unsigned int  word;
typedef unsigned long lword;
typedef unsigned short int word16;    /* 16 bits */

typedef enum
{
  VAL_FALSO=0,
  VAL_VERDADEIRO=1
} t_boolean;

#endif
/* -- fim Definicao.h -- */
