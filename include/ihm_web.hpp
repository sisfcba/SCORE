/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.1

	PROJETO		: GENERICO

	SISTEMA		: GENERICO

	ARQUIVO		: ihm_web.cpp

	CONTEUDO	: Funcoes Genericas do IHM Web

	AUTOR		: Wallace Santos Lages

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0		  -		  DATA  : 15/01/1999

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
15/01/1999 | Edicao Inicial                                		| Wallace
-------------------------------------------------------------------------------

******************************************************************************/


#ifndef _IHM_WEB_
#define _IHM_WEB_

#include <CGILib.hpp>
extern "C" {
#include <OperacaoW.h>
#include <TiposOpeW.h>
#include <IniArqVar.h>
#include <math.h>
#include <unistd.h>

}

#define MAX_USER_NAME  50 //numero maximo de caracteres a serm utilizados para o login de um usuario
#define MAX_SENHA      20 //numero maximo de caracteres a serm utilizados na senha de um usuario
#define MAX_LOGIN_ID   10 //numero maximo de caracteres a serm utilizados como para a identificao de um usuario
#define MAX_OPCAO      10 //numero maximo de caracteres a serm utilizados como identificao de drop lists
#define MAX_TAG_ID     20 //numero maximo de caracteres utilizados para representar um tag em string
#define MAX_PATH       30 // numero maximo de caracters no path
#define MAX_STRING     20 //numero maximo de caracters em um botao


//arquivo onde sao escritas a mensgens de log
#define LOG_FILE        "ihm_web.log"


//classe de gerenciamento
//do ihm_web

class CWeb_HMI
{

public:

    CInput   input;
    CWebPage page;

	//write the string in the "LOG_FILE"
	void LogaEvento(char * text, ...  );

	//sends an pre-defined error message
	void EnviaPaginaErro(char * msg,...);

	//Exits the program
	void Fim(void);

	//sends the left bar menu
	void EnviaMenuLateral(char * login_id,t_ihm_config * );

};


class CScoreButton
{

private:

	char title[MAX_STRING];
	char icon[MAX_PATH];
	char bgimage[MAX_PATH];
	char string1[MAX_STRING];
	char string2[MAX_STRING];
	char string3[MAX_STRING];	


public:

	void Add(void);
	char SetTitle(char * string);
	char SetIcon( char * icon, char * bgimage );
	char SetText( char * string1, char * string2, char * string3);

};




#endif
