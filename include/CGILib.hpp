/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.40

	PROJETO  : Todos
	
	SISTEMA  : Todos
	
	ARQUIVO  : CGILib.h

	CONTEUDO : Contem a definicao das duas classes utilizada 
				na programacao de CGIs


	AUTOR    : Wallace Santos Lages

	SISTEMA OPERACIONAL:  QNX 4.24		-		COMPILADOR: WATCOM C++- V10.6

	VERSAO   : 1.0		  -	  DATA  : 20/01/1999

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
01/11/94 | Edicao Inicial                                       | Wallace
-------------------------------------------------------------------------------
******************************************************************************/

#ifndef __CGILib__
#define __CGILib__

#define MAX_INPUT_STRING  100

#define BLACK  000000
#define WHITE  FFFFFF
#define SUBMIT "SUBMIT"
#define RESET  "RESET"
#define HIDDEN "HIDDEN"
#define TEXT   "TEXT"
#define ON 1
#define OFF 0

extern "C"
{
#include <stdio.h>
}


/* funcoes para produzir paginas HTML pre formatadas */
class CWebPage
{
	char bgcolor[7];
	char text[7];
	char vlink[7];
	char alink[7];


public:

	//construtor
	CWebPage();

	//Seta alguns valores para as paginas
	void SetStyle(char * bgcolor, char * text, char *  vlink, char * alink);

	//abre uma nova pagina
	void Open(char * titulo,char * background);

	//fecha a pagina aberta
	void Close();

	//insere o arquivo HTML indicado na saida
	void AddFromTemplate(FILE * file);

	//insere o texto indicado
	void AddText(char *);

	//insere um link
	void AddLink(char * label, char * location);

	//insere uma imagem
	void AddImage(char * nome);

	//abre um form
	void OpenForm(char * name, char * method, char * action);

	//fecha um form
	void CloseForm();

	//abre uma combo-box
	void OpenComboBox(char * name, int visible);

	//insere um item na combo-box
	void AddBoxItem(char * text, char * value , int selected );

	//fecha a combo-box
	void CloseComboBox();

	//cria uma entrada de usuario no formulario de acordo com o tipo indicado
	void AddInput(char * type,char * value, char * name ,char * tag=NULL);

	//insere uma nova linha
	void NewLine();	

};



/* gerencia a interpretacao da string emviada em um post */


class CInput
{

private:

	char * str_length; //comprimento da string
	FILE *input;
	int  length;
	char * inputdata;
	int num_fields; //numero de campos lidos


public:

	//construtor e destrutor
	CInput(); 

	// retorna um ponteiro para a srting de entrada
	char * GetInput();
	
	//Retorna o numero de campos lidos
	int GetNumFields();


	//copia o valor do campo indicado por name
	char GetField(char * name, char * buffer,int size);




};






#endif




