/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.2

	PROJETO		: CBA

	SISTEMA		: SCORE

	ARQUIVO		: RMigraDados.h

	CONTEUDO	: Contem a inclusao de arquivos, constantes, variaveis  e
				  estruturas necessarias a geracao do relatorio de 
				  Migracao de dados

	AUTOR		: Marco Aurelio M Lopes

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 01 - 02/06/19

	OBSERVACAO	:

	HISTORICO DAS EDICOES

-------------------------------------------------------------------------------
dd/mm/aa | Descricao                                                 | autor
-------------------------------------------------------------------------------
******************************************************************************/

	/*-- INCLUSAO DE OUTROS ARQUIVOS --*/

#include <Score.h>
#include <Prototipos.h>
#include <VarsComum.h>
#include <Relatorios.h>
#include <BdScore.h>
#include <ScoreMsgs.h>
#include <ScoreErros.h>
#include <RelPrototipos.h>
#include <OperacaoBibW.h>
#include <TiposOpeW.h>
#include <Eventos.h>
#include <KeysCBA.h>

#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <stddef.h>
#include <ctype.h>
#include <process.h>
#include <sys/kernel.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/proxy.h>
#include <signal.h>
#include <time.h>

/*-- Cabecalho --*/
typedef
  struct VarCabec
  {
	char	Selecao[14];
	char	Algorit[11];
  } t_cabec;

/*-- Area de Dados --*/
typedef
  struct VarDados
  {
  	char LinhaDados[79];
  } t_dados;

/*-- Rodape --*/
typedef
  struct VarRodape
  {
  	char LinhaDados[79];
  } t_rodape;

