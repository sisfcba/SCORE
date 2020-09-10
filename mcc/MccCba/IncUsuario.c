/******************************************************************************

			 ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.0

	PROJETO		: TODOS

	SISTEMA		: TODOS

	ARQUIVO		: IncUsuario.c

	CONTEUDO	: Modulo de Controle das Cubas - MCC - Procedimentos de calculo
                  dos incrementos de usuario.

	AUTOR		: Leonel Vicente Mota Ivo

	SISTEMA OPERACIONAL:  QNX 4.20		-		COMPILADOR: WATCOM C - V9.5

	VERSAO		: 1.0			-		DATA	:	13/03/97

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
dd/mm/aa | Descricao                                            | autor
-------------------------------------------------------------------------------
29/11/99 | Adequacao do tratamento de incremento de usuario ao  | Carlos
         | padrao original do Score                             | 
-------------------------------------------------------------------------------
******************************************************************************/

/*
-------------------------------------------------------------------------------
                           Includes
-------------------------------------------------------------------------------
*/
#include	<MccCba.h>

/*
-------------------------------------------------------------------------------
                           Variaveis Globais
-------------------------------------------------------------------------------
*/
/* -- Apontadores para as tabelas comuns -- */
#include	<VarsComum.h>

/*
-------------------------------------------------------------------------------
                           Prototipos
-------------------------------------------------------------------------------
*/

float	CalcRampa(float v_ini, int t_max, int cont_t);

/*
-------------------------------------------------------------------------------
							Funcoes
-------------------------------------------------------------------------------
*/

/*
--------------------------------------------------------------------------------
| IniExecIncUsu - Inicializa variaveis referentes ao incremento de usuario     |
--------------------------------------------------------------------------------
*/
void IniExecIncUsu(int Cuba)
{
  AVC.Ccont[Cuba].IncUsuario=0.0;
  AVC.Ccont[Cuba].ContIncUsuario=-1;
  EST_AVC(Cuba).TrataIncUsuario=FALSO;
}

/*
--------------------------------------------------------------------------------
| ExecIncUsurio - Calcula os incrementos de tensao por usuario                 |
--------------------------------------------------------------------------------
*/
void ExecIncUsuario(int Cuba)
{
  if (AVC.Param[Cuba].HabIncUsuario eq VERDADEIRO)
  {
	if (EST_AVC(Cuba).TrataIncUsuario eq VERDADEIRO)
	{
	  if (AVC.Ccont[Cuba].ContIncUsuario eq -1)
	  { /* -- Inicio de incremento -- */
		AVC.Ccont[Cuba].ContIncUsuario=0;
		AVC.Ccont[Cuba].IncUsuario=AVC.Param[Cuba].IncUsuarioInic;
	  }
	  if (AVC.Ccont[Cuba].ContIncUsuario < AVC.Param[Cuba].TIncUsuario)
	  {
		if (AVC.Param[Cuba].TipoIncUsuario eq INCREMENTO_RAMPA)
		  AVC.Ccont[Cuba].IncUsuario=CalcRampa(AVC.Param[Cuba].IncUsuarioInic,
					AVC.Param[Cuba].TIncUsuario,AVC.Ccont[Cuba].ContIncUsuario);
	  }
	  else
	  {
		AVC.Ccont[Cuba].IncUsuario=0.0;
		AVC.Ccont[Cuba].ContIncUsuario=-1;
		EST_AVC(Cuba).TrataIncUsuario=FALSO;
	  }

	}
	else
	{
	  AVC.Ccont[Cuba].IncUsuario     = 0.0;
	  AVC.Ccont[Cuba].ContIncUsuario = -1;
	  EST_AVC(Cuba).TrataIncUsuario  = FALSO;
	}
  }
  else
  {
	AVC.Ccont[Cuba].IncUsuario     = 0.0;
	AVC.Ccont[Cuba].ContIncUsuario = -1;
	EST_AVC(Cuba).TrataIncUsuario  = FALSO;
  }
}

/* -- fim do arquivo IncUsuario.c -- */
