/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO  : CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA  : AUTOMACAO DA SALA 120 KA II e III

	ARQUIVO  : Macros.h

	CONTEUDO : Macros de uso geral do sistema

	AUTOR    : Joao Thomaz Pereira

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO   : 2.0		  -	  DATA  : 05/05/94

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
05/05/94 | Edicao inicial de migracao para o QNX 4.2			| Leonel
-------------------------------------------------------------------------------
21/06/94 | Criada nova InitVarsComum e alterada original		| Leonel
-------------------------------------------------------------------------------
28/03/95 | Incluido ponteiro para tabela de inc. de operacao	| Leonel
-------------------------------------------------------------------------------
28/07/98 | Y2k - Incluidas macros para tratamento ano 2 digitos	| Leonel
-------------------------------------------------------------------------------
******************************************************************************/

#ifndef		_MACROS_H


/*
------------------------------------------------------------------------------
				Definicoes e Macros 
------------------------------------------------------------------------------
*/
/* -- Controle de inclusao -- */
#define		_MACROS_H

#define	minimo(a,b)		((a) < (b) ? (a) : (b))
#define	maximo(a,b)		((a) > (b) ? (a) : (b))
#define DISABLE()		_disable()
#define ENABLE()		_enable()

/* -- Externos do compilador -- */
extern	int		_argc;
extern	char **	_argv;

#define My_name  		(FileName(_argv[0]))

/* -- Macros para o Score -- */

/* Seleciona o segmento correto do avc que contem o canal solicitado.
   As variaveis comum e comum_avc devem existir como globais no modulo
   solicitante. DESNECESSARIA NO QNX 4.2 -> MODELO FLAT */
#define	SelecionaAvc(Cuba)
/* Macro para acessar um canal no avc */
#define AVC						ComumAvc->Avc.Uavc

/* Macro para acessar um canal no est_avc */
#define EST_AVC(canal)		PAvcEst->AvcEst[(canal)].EstAvc
/* Macro para acessar um canal no supervisao_avc */
#define SUPERV_AVC(canal)		PAvcSup->AvcSuperv[(canal)].AvcS

/* Macro para acessar um canal no supervisao_avc de turno */
#define SUPERV_AVC_TURNO(canal)		PHistTurno->AvcHist.AvcSuperv[(canal)].AvcS

/* Macro para acessar o avl */
#define AVL					PAvl->Uavl.Avl

/* Macro para acessar o historico de turno do avl */
#define AVL_TURNO			PHistTurno->AvlHist.Uavl.Avl

/* -- Macro para inicializar os ponteiros para as tabelas comuns -- */
/* -- Nao chama o PegaComum -- */
#define	InitVarsComum2()	{PAvcEst=(void *)((char *)Comum + Comum->OfEstAvc); \
						 PAvcSup=(void *)((char *)Comum + Comum->OfSupAvc); \
						 PHistTurno=(void *)((char *)Comum + Comum->OfHistTur); \
						 PDescProg=(void *)((char *)Comum + Comum->OfDescProg); \
						 PAvl=(void *)((char *)Comum + Comum->OfAvl); \
						 PTabOpe=(void *)((char *)Comum + Comum->OfTabOpe); \
						 My_nid=getnid();}
/* -- Chama o PegaComum -- */
#define	InitVarsComum() {if (PegaComum(&Comum))\
						 {printf("%s->Falha no PegaComum\n",My_name); exit(-1);} \
						 PAvcEst=(void *)((char *)Comum + Comum->OfEstAvc); \
						 PAvcSup=(void *)((char *)Comum + Comum->OfSupAvc); \
						 PHistTurno=(void *)((char *)Comum + Comum->OfHistTur); \
						 PDescProg=(void *)((char *)Comum + Comum->OfDescProg); \
						 PAvl=(void *)((char *)Comum + Comum->OfAvl); \
						 PTabOpe=(void *)((char *)Comum + Comum->OfTabOpe); \
						 My_nid=getnid();}

/* -- Macro para pegar o tid de uma determinada tarefa -- */
#define PegaTid(NumTarefa) (PDescProg->Prog[NumTarefa].TidProg)
/* -- Macro para marcar alteracao de tabela -- */
#define AlteracaoTabela(Tabela) (Comum->AlterouTab[Tabela]=VERDADEIRO)
/* -- Numero do nodo complementar -- */
#define	NODO_COMPLEMENTAR	((My_nid Mod 2) eq 0 ? My_nid-1 : My_nid+1)
/* -- Copia de memoria com alocacao de semaforo antes. Utilizada para acesso
	  controlado `a base de dados. O primeiro parametro e' o numero do sema-
      foro associado `a tabela e os outros parametros sao os mesmos e na mes-
      ma ordem definida para a funcao memcpy -- */
#define	SemafMemXCpy(Semaforo,PDest,PFonte,Tamanho) \
	{AlocaSemaf(Semaforo); memcpy(PDest,PFonte,Tamanho); LiberaSemaf(Semaforo);}

/* -- Retorna proximo numero de operacao para a cuba dada -- */
/*** #define	ProxCubaOpe(CubaOpe) ((CubaOpe Mod OFFSET_INC_GRUPO) >= DEZ_FIM_GRUPO \
					? CubaOpe-DEZ_FIM_GRUPO+OFFSET_INC_GRUPO+DEZ_INI_GRUPO \
					: CubaOpe+1)
*****/
/* -- Base de tempo para as remotas -- */
#define	BASE_TEMPO_REMOTA		(Comum->BaseTempoRemota)


/* -- Y2k inicio: Macros para tratamento de ano em 2 e 4 digitos -- */

/* Macros para tratamento de ano em 2 e 4 digitos */
/* O Score utiliza datas com ano em 2 digitos em algumas de suas telas e
   relatorios por motivo de economia de espaco. Para representar corretamente
   o ano em dois digitos apartir do ano 2000 foi adotada a tecnica conhecida
   como "janelamento", onde foi fixado um limite inferior para o seculo vinte
   no ano de 1970. Desta maneira o sistema entendera anos em 2 digitos entre
   70 a 99 com sendo 1970 a 1999 e anos em dois digitos entre 00 a 69 com
   sendo 2000 a 2069.
   Foram criadas entao duas macros para permitir o correto tratamento de
   datas de 2 digitos tanto para exibicao como para a entrada de dados.
   Estas macros deverao ser utilizadas na manipulacao do campo ano (tm_year)
   na struct tm para converter de tm_year para 2 digitos e de 2 digitos para
   tm_year.
*/

/* Converte o campo tm_year para dois digitos (em 2000 tm_year=100 -> 00) */
#define		TM_YEAR_TO_2DIGIT(year)		(year >= 100 ? year-100 : year)

/* Converte ano em 2 digitos para o campo tm_year (00 (2000) ->tm_year=100) */
/* Observacao: Esta macro funcionara para datas entre 1970 e 2069 */
#define		TWO_DIGIT_TO_TM_YEAR(year)		(year < 70 ? year+100 : year)


/* Macros para conversao de/para tm_year em 4 digitos */
/* Converte o campo tm_year para quatro digitos (em 2000 tm_year=100 -> 2000) */
#define		TM_YEAR_TO_4DIGIT(year)		(year+1900)

/* Converte ano em 4 digitos para o campo tm_year (2000 ->tm_year=100) */
#define		FOUR_DIGIT_TO_TM_YEAR(year)		(year-1900)


/* -- Y2k fim -- */

#endif
/* -- fim Macros.h -- */
