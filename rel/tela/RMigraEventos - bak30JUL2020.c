/******************************************************************************

             ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
	   SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 4.2

	PROJETO		: CBA

	SISTEMA		: SCORE

	ARQUIVO		: RMigraEventos.c

	CONTEUDO	: Esse programa gera arq. de eventos em txt.

	AUTOR		: Marco Aurelio M Lopes

	SISTEMA OPERACIONAL:  QNX 4.25		-		COMPILADOR: WATCOM C - V10.6

	VERSAO		: 01 - 02/06/19

	OBSERVACAO	: 

	HISTORICO DAS EDICOES

-------------------------------------------------------------------------------
dd/mm/aa | Descricao												| autor
-------------------------------------------------------------------------------
02/06/19 | Edicao inicial											| Marco
-------------------------------------------------------------------------------
*/

/*
--------------------------------------------------------------------------------
            			 Definicao de DEFINE's
--------------------------------------------------------------------------------
*/
#define	PROGRAMA_PRINCIPAL
#define	RELATORIO_HISTORICO

/*
--------------------------------------------------------------------------------
						Inclusao de outros arquivos
--------------------------------------------------------------------------------
*/
//#include <windows/Qwindows.h>
#include <RMigraEventos.h>

/*
--------------------------------------------------------------------------------

            			 Definicao de Variaveis Globais do Score
--------------------------------------------------------------------------------
*/

t_LeEventos	BufEv;
int		nregs;
t_rec_ev	*evento;
t_filtrosPD	filtro;
t_hist		*HAvlAvc;

/*
--------------------------------------------------------------------------------
            			 Definicao de Variaveis Globais Locais
--------------------------------------------------------------------------------
*/

/*
--------------------------------------------------------------------------------
            			 Definicao de Estruturas
--------------------------------------------------------------------------------
*/
struct {
  long 	hora_ae;
  byte	apreq;
} hist[MAX_CUBAS];
/*
-------------------------------------------------------------------------------
  main - Funcao principal
-------------------------------------------------------------------------------
*/

void main( int argc, char *argv[] )
{
  t_cabec	Cab;
  t_dados	*Dad;
  t_rodape  Rod;
  t_args	Arg;
  char   DataI[9];
  time_t HoraAtual;
  struct tm *StData;
  char	 dia[3], mes[3], ano[3];

  /*-- Pega area de memoria comum --*/
  if (PegaComum(&Comum))
  {
	ExibeErro("NAO CONSEGUI LOCALIZAR TABELA GLOBAL");
	exit(0);
  }


  if( ( Dad = malloc( sizeof( t_dados ) * MAX_LINHAS ) ) eq NULL )
                                                                                                                                                                                                                                                                                                                                                                                             {
	ExibeErro( "ERRO MALLOC AREADADOS REL" );
	exit(0);
  }

  if (argc ne 1)
  {
    strcpy(DataI, argv[1]);
    HoraAtual = time(NULL);
    StData = localtime(&HoraAtual);

    dia[0] = DataI[0];
    dia[1] = DataI[1];
    mes[0] = DataI[3];
    mes[1] = DataI[4];
    ano[0] = DataI[6];
    ano[1] = DataI[7];
    Arg.DiaInicial = atoi(dia);
    Arg.MesInicial = atoi(mes)-1;
    Arg.AnoInicial = atoi(ano);
  
  }
  else
  {
    HoraAtual = time(NULL) - 86400;
    StData = localtime(&HoraAtual);
    Arg.DiaInicial = StData->tm_mday;
    Arg.MesInicial = StData->tm_mon;
    Arg.AnoInicial = StData->tm_year;

  }

  GeraDadosRel(&Arg, &Cab, Dad, &Rod);


  free(Dad);

} /*--- main ---*/

/*
-------------------------------------------------------------------------------
  GeraDadosRel - Seleciona eventos e monta o arquivo 
-------------------------------------------------------------------------------
*/
int GeraDadosRel( t_args *Arg, t_cabec *Cab, t_dados *Dad, t_rodape *Rod )
{
  int			Cuba,
				NumCuba,
				nodo_controle,
				sala;

  long			i;

  time_t		HoraAtual,
				HoraFinal,
				HoraInicial,
				hora_relatorio;

  struct tm		data_aux;

  char			NomeArq[80];

  FILE *fp;

  /*-- Pega hora atual --*/
  HoraAtual = time(NULL);

  /* Inicializa estrutura */
  for (Cuba=0; Cuba<MAX_CUBAS; Cuba++)
  {
	hist[Cuba].apreq = FALSO;
	hist[Cuba].hora_ae = 0;
  }

    /* Calcula a hora do inicio do turno atual */
    memset( &data_aux, 0x00, sizeof( struct tm ) );
    memcpy( &data_aux, localtime( &HoraAtual ), sizeof( struct tm ) );
    data_aux.tm_mday  = Arg->DiaInicial;
    data_aux.tm_mon  = Arg->MesInicial;
	data_aux.tm_year = TWO_DIGIT_TO_TM_YEAR(Arg->AnoInicial);
    data_aux.tm_sec  = 0;
    data_aux.tm_min  = 0;
    data_aux.tm_hour  = 0;
    hora_relatorio = mktime( &data_aux );

    /* Calcula a hora do relatorio p/ pesquisa */
    HoraInicial = hora_relatorio;
    memset( &data_aux, 0x00, sizeof( struct tm ) );
    memcpy( &data_aux, localtime( &HoraInicial ), sizeof( struct tm ) );
    HoraFinal = HoraInicial + 86400;

  sala = Comum->IdentReducao;
  if(sala>4)
	sala = sala -2;
  nodo_controle=AVL.NodoNoControle;
  sprintf(NomeArq, "//%1d/usr/score/relatorio/EvSF%d_%02d%02d%02d", 
			nodo_controle,sala,
			data_aux.tm_mday, data_aux.tm_mon+1,
			TM_YEAR_TO_2DIGIT(data_aux.tm_year));

  filtro.Par.Total = 0;


  for( Cuba = 0; Cuba < AVL.NumCubas; Cuba++ )
  {
	  NumCuba = ConvCubScoreOper( Cuba );
	  filtro.Par.NumCuba[filtro.Par.Total] = NumCuba; 
	  filtro.Par.IndCuba[filtro.Par.Total] = ConvCubOperScore( NumCuba );
	  filtro.Par.Total ++;
  }

  fp = fopen (NomeArq, "w");
  if (fp eq NULL)
  {
	/* Erro */ 
  }
  
  BufEv.Evento[0]  = EV_DB;
  BufEv.Evento[1]  = INICIO_EA;
  BufEv.Evento[2]  = FIM_EA;
  BufEv.Evento[3]  = INICIO_QUEBRADA;
  BufEv.Evento[4]  = INICIO_CORRIDA;
  BufEv.Evento[5]  = EV_CHAVE_REMOTO;
  BufEv.Evento[6]  = EV_CHAVE_LOCAL;
  BufEv.NumEvs = 7;
  BufEv.DataAtual = HoraAtual; 
  BufEv.DataFinal = HoraFinal;
  BufEv.DataInicial = HoraInicial;
  BufEv.NaoPara = VERDADEIRO;
  memcpy( &BufEv.filtros, &filtro, sizeof( t_filtrosPD ) );
  
  nregs = 0;

  evento = (t_rec_ev *)IniLeArqEv( &BufEv, evento, &nregs );

  i = 0;
  if (nregs > 0)
  {
	while (i < nregs)
	{
	  if ((evento+i)->DataEv < HoraFinal)
      {
		memset( &data_aux, 0x00, sizeof( struct tm ) );
		memcpy( &data_aux, localtime( &((evento+i)->DataEv) ), sizeof( struct tm ) );

		switch ((evento+i)->CodeEv)
		{
		  case EV_DB:
				fprintf (fp, "%02d/%02d/%02d;%02d:%02d:%02d;%03d;DerivBaixa;%d;%d;%d;%d;%d;\n",
						data_aux.tm_mday,
						data_aux.tm_mon+1,
						/* -- Y2k inicio: ano de 2 digitos -- */
						TM_YEAR_TO_2DIGIT(data_aux.tm_year),
						/* -- Y2k fim -- */
						data_aux.tm_hour,
						data_aux.tm_min,
						data_aux.tm_sec,
						(evento+i)->CubaIniEv,
						(evento+i)->TipoMsg.ParEv[0].IntEv,
						(evento+i)->TipoMsg.ParEv[1].IntEv,
						(evento+i)->TipoMsg.ParEv[2].IntEv,
						(evento+i)->TipoMsg.ParEv[3].IntEv,
						(evento+i)->TipoMsg.ParEv[4].IntEv);
		  break;
		  case INICIO_EA:
				fprintf (fp, "%02d/%02d/%02d;%02d:%02d:%02d;%03d;InicioEa;%8s;%8s;%8s;%6.3f;%8s;\n",
						data_aux.tm_mday,
						data_aux.tm_mon+1,
						/* -- Y2k inicio: ano de 2 digitos -- */
						TM_YEAR_TO_2DIGIT(data_aux.tm_year),
						/* -- Y2k fim -- */
						data_aux.tm_hour,
						data_aux.tm_min,
						data_aux.tm_sec,
						(evento+i)->CubaIniEv,
						(evento+i)->TipoMsg.ParEv[0].StringEv,
						(evento+i)->TipoMsg.ParEv[1].StringEv,
						(evento+i)->TipoMsg.ParEv[2].StringEv,
						(evento+i)->TipoMsg.ParEv[3].FloatEv,
						(evento+i)->TipoMsg.ParEv[4].StringEv);
		  break;
		  case FIM_EA:
				fprintf (fp, "%02d/%02d/%02d;%02d:%02d:%02d;%03d;FimEa;%8s;%6.3f;%6.3f;%6.3f;%6.3f;\n",
						data_aux.tm_mday,
						data_aux.tm_mon+1,
						/* -- Y2k inicio: ano de 2 digitos -- */
						TM_YEAR_TO_2DIGIT(data_aux.tm_year),
						/* -- Y2k fim -- */
						data_aux.tm_hour,
						data_aux.tm_min,
						data_aux.tm_sec,
						(evento+i)->CubaIniEv,
						(evento+i)->TipoMsg.ParEv[0].StringEv,
						(evento+i)->TipoMsg.ParEv[1].FloatEv,
						(evento+i)->TipoMsg.ParEv[2].FloatEv,
						(evento+i)->TipoMsg.ParEv[3].FloatEv,
						(evento+i)->TipoMsg.ParEv[4].FloatEv);
		  break;
		  case INICIO_QUEBRADA:
				fprintf (fp, "%02d/%02d/%02d;%02d:%02d:%02d;%03d;IniQuebrad;%8s;%8s;%6.3f;%6.3f;%6.3f;\n",
						data_aux.tm_mday,
						data_aux.tm_mon+1,
						/* -- Y2k inicio: ano de 2 digitos -- */
						TM_YEAR_TO_2DIGIT(data_aux.tm_year),
						/* -- Y2k fim -- */
						data_aux.tm_hour,
						data_aux.tm_min,
						data_aux.tm_sec,
						(evento+i)->CubaIniEv,
						(evento+i)->TipoMsg.ParEv[0].StringEv,
						(evento+i)->TipoMsg.ParEv[1].StringEv,
						(evento+i)->TipoMsg.ParEv[2].FloatEv,
						(evento+i)->TipoMsg.ParEv[3].FloatEv,
						(evento+i)->TipoMsg.ParEv[4].FloatEv);
		  break;
		  case INICIO_CORRIDA:
				fprintf (fp, "%02d/%02d/%02d;%02d:%02d:%02d;%03d;IniCorrida;%8s;%8s;%6.3f;%6.3f;%6.3f;\n",
						data_aux.tm_mday,
						data_aux.tm_mon+1,
						/* -- Y2k inicio: ano de 2 digitos -- */
						TM_YEAR_TO_2DIGIT(data_aux.tm_year),
						/* -- Y2k fim -- */
						data_aux.tm_hour,
						data_aux.tm_min,
						data_aux.tm_sec,
						(evento+i)->CubaIniEv,
						(evento+i)->TipoMsg.ParEv[0].StringEv,
						(evento+i)->TipoMsg.ParEv[1].StringEv,
						(evento+i)->TipoMsg.ParEv[2].FloatEv,
						(evento+i)->TipoMsg.ParEv[3].FloatEv,
						(evento+i)->TipoMsg.ParEv[4].FloatEv);
		  break;
		  case EV_CHAVE_LOCAL:
				fprintf (fp, "%02d/%02d/%02d;%02d:%02d:%02d;%03d;ChaveLocal;%8s;%8s;%6.3f;%6.3f;%6.3f;\n",
						data_aux.tm_mday,
						data_aux.tm_mon+1,
						/* -- Y2k inicio: ano de 2 digitos -- */
						TM_YEAR_TO_2DIGIT(data_aux.tm_year),
						/* -- Y2k fim -- */
						data_aux.tm_hour,
						data_aux.tm_min,
						data_aux.tm_sec,
						(evento+i)->CubaIniEv,
						(evento+i)->TipoMsg.ParEv[0].StringEv,
						(evento+i)->TipoMsg.ParEv[1].StringEv,
						(evento+i)->TipoMsg.ParEv[2].FloatEv,
						(evento+i)->TipoMsg.ParEv[3].FloatEv,
						(evento+i)->TipoMsg.ParEv[4].FloatEv);
		  break;
		  case EV_CHAVE_REMOTO:
				fprintf (fp, "%02d/%02d/%02d;%02d:%02d:%02d;%03d;ChaveRemot;%8s;%8s;%6.3f;%6.3f;%6.3f;\n",
						data_aux.tm_mday,
						data_aux.tm_mon+1,
						/* -- Y2k inicio: ano de 2 digitos -- */
						TM_YEAR_TO_2DIGIT(data_aux.tm_year),
						/* -- Y2k fim -- */
						data_aux.tm_hour,
						data_aux.tm_min,
						data_aux.tm_sec,
						(evento+i)->CubaIniEv,
						(evento+i)->TipoMsg.ParEv[0].StringEv,
						(evento+i)->TipoMsg.ParEv[1].StringEv,
						(evento+i)->TipoMsg.ParEv[2].FloatEv,
						(evento+i)->TipoMsg.ParEv[3].FloatEv,
						(evento+i)->TipoMsg.ParEv[4].FloatEv);
		  break;
		
		  default:
		  break;
		}
		i++;
	  }
    }
  }

  free( evento );

  BufEv.Evento[0]  = ATRASO_EA;
  BufEv.Evento[1]  = EV_AEK;
  BufEv.Evento[2]  = INICIO_QUEBCAB;
  BufEv.Evento[3]  = INICIO_QUEB_PREV;
  BufEv.Evento[4]  = INICIO_PREV_EA;
  BufEv.Evento[5]  = FIM_QUEB_PREV;
  BufEv.NumEvs = 6;
  BufEv.DataAtual = HoraAtual; 
  BufEv.DataFinal = HoraFinal;
  BufEv.DataInicial = HoraInicial;
  BufEv.NaoPara = VERDADEIRO;
  memcpy( &BufEv.filtros, &filtro, sizeof( t_filtrosPD ) );
  
  nregs = 0;

  evento = (t_rec_ev *)IniLeArqEv( &BufEv, evento, &nregs );

  i = 0;
  if (nregs > 0)
  {
	while (i < nregs)
	{
	  if ((evento+i)->DataEv < HoraFinal)
      {
		memset( &data_aux, 0x00, sizeof( struct tm ) );
		memcpy( &data_aux, localtime( &((evento+i)->DataEv) ), sizeof( struct tm ) );

		switch ((evento+i)->CodeEv)
		{
		  case ATRASO_EA:
				fprintf (fp, "%02d/%02d/%02d;%02d:%02d:%02d;%03d;AtrasoEa;;;;;;\n",
						data_aux.tm_mday,
						data_aux.tm_mon+1,
						/* -- Y2k inicio: ano de 2 digitos -- */
						TM_YEAR_TO_2DIGIT(data_aux.tm_year),
						/* -- Y2k fim -- */
						data_aux.tm_hour,
						data_aux.tm_min,
						data_aux.tm_sec,
						(evento+i)->CubaIniEv);
		  break;
		  case EV_AEK:
				fprintf (fp, "%02d/%02d/%02d;%02d:%02d:%02d;%03d;AEK;%8s;%6.3f;%6.3f;%d;%6.3f;\n",
						data_aux.tm_mday,
						data_aux.tm_mon+1,
						/* -- Y2k inicio: ano de 2 digitos -- */
						TM_YEAR_TO_2DIGIT(data_aux.tm_year),
						/* -- Y2k fim -- */
						data_aux.tm_hour,
						data_aux.tm_min,
						data_aux.tm_sec,
						(evento+i)->CubaIniEv,
						(evento+i)->TipoMsg.ParEv[0].StringEv,
						(evento+i)->TipoMsg.ParEv[1].FloatEv,
						(evento+i)->TipoMsg.ParEv[2].FloatEv,
						(evento+i)->TipoMsg.ParEv[3].IntEv,
						(evento+i)->TipoMsg.ParEv[4].FloatEv);
		  break;
		  case INICIO_QUEBCAB:
				fprintf (fp, "%02d/%02d/%02d;%02d:%02d:%02d;%03d;IniQuebCab;%8s;%8s;%6.3f;%6.3f;%6.3f;\n",
						data_aux.tm_mday,
						data_aux.tm_mon+1,
						/* -- Y2k inicio: ano de 2 digitos -- */
						TM_YEAR_TO_2DIGIT(data_aux.tm_year),
						/* -- Y2k fim -- */
						data_aux.tm_hour,
						data_aux.tm_min,
						data_aux.tm_sec,
						(evento+i)->CubaIniEv,
						(evento+i)->TipoMsg.ParEv[0].StringEv,
						(evento+i)->TipoMsg.ParEv[1].StringEv,
						(evento+i)->TipoMsg.ParEv[2].FloatEv,
						(evento+i)->TipoMsg.ParEv[3].FloatEv,
						(evento+i)->TipoMsg.ParEv[4].FloatEv);
		  break;
		  case INICIO_QUEB_PREV:
				fprintf (fp, "%02d/%02d/%02d;%02d:%02d:%02d;%03d;InicQPrev;%d;%d;%6.3f;%8s;;\n",
						data_aux.tm_mday,
						data_aux.tm_mon+1,
						/* -- Y2k inicio: ano de 2 digitos -- */
						TM_YEAR_TO_2DIGIT(data_aux.tm_year),
						/* -- Y2k fim -- */
						data_aux.tm_hour,
						data_aux.tm_min,
						data_aux.tm_sec,
						(evento+i)->CubaIniEv,
						(evento+i)->TipoMsg.ParEv[0].IntEv,
						(evento+i)->TipoMsg.ParEv[1].IntEv,
						(evento+i)->TipoMsg.ParEv[2].FloatEv,
						(evento+i)->TipoMsg.ParEv[3].StringEv);
		  break;
		  case INICIO_PREV_EA:
				fprintf (fp, "%02d/%02d/%02d;%02d:%02d:%02d;%03d;IniPrevEa;%6.3f;%8s;%6.3f;%8s;%6.3f;\n",
						data_aux.tm_mday,
						data_aux.tm_mon+1,
						/* -- Y2k inicio: ano de 2 digitos -- */
						TM_YEAR_TO_2DIGIT(data_aux.tm_year),
						/* -- Y2k fim -- */
						data_aux.tm_hour,
						data_aux.tm_min,
						data_aux.tm_sec,
						(evento+i)->CubaIniEv,
						(evento+i)->TipoMsg.ParEv[0].FloatEv,
						(evento+i)->TipoMsg.ParEv[1].StringEv,
						(evento+i)->TipoMsg.ParEv[2].FloatEv,
						(evento+i)->TipoMsg.ParEv[3].StringEv,
						(evento+i)->TipoMsg.ParEv[4].FloatEv);
		  break;
		  case FIM_QUEB_PREV:
				fprintf (fp, "%02d/%02d/%02d;%02d:%02d:%02d;%03d;FimQPrev;%8s;%8s;;;;\n",
						data_aux.tm_mday,
						data_aux.tm_mon+1,
						/* -- Y2k inicio: ano de 2 digitos -- */
						TM_YEAR_TO_2DIGIT(data_aux.tm_year),
						/* -- Y2k fim -- */
						data_aux.tm_hour,
						data_aux.tm_min,
						data_aux.tm_sec,
						(evento+i)->CubaIniEv,
						(evento+i)->TipoMsg.ParEv[0].StringEv,
						(evento+i)->TipoMsg.ParEv[1].StringEv);
		  break;

		  default:
		  break;

		}
		i++;
	  }
    }
  }
  free( evento );

  BufEv.Evento[0]  = INI_DESVIO_TENSAO;
  BufEv.Evento[1]  = LOG_OPER_CUBA;
  BufEv.Evento[2]  = FIM_DESVIO_TENSAO;
  BufEv.Evento[3]  = CFG_PAR_CUBA;
  BufEv.Evento[4]  = EVENTO_INC_OPERACAO;
  BufEv.Evento[5]  = EV_AGARRACAM;
  BufEv.Evento[6]  = EV_PROVQUEB;
  BufEv.NumEvs = 7;
  BufEv.DataAtual = HoraAtual; 
  BufEv.DataFinal = HoraFinal;
  BufEv.DataInicial = HoraInicial;
  BufEv.NaoPara = VERDADEIRO;
  memcpy( &BufEv.filtros, &filtro, sizeof( t_filtrosPD ) );
  
  nregs = 0;

  evento = (t_rec_ev *)IniLeArqEv( &BufEv, evento, &nregs );

  i = 0;
  if (nregs > 0)
  {
	while (i < nregs)
	{
	  if ((evento+i)->DataEv < HoraFinal)
      {
		memset( &data_aux, 0x00, sizeof( struct tm ) );
		memcpy( &data_aux, localtime( &((evento+i)->DataEv) ), sizeof( struct tm ) );

		switch ((evento+i)->CodeEv)
		{
		  case INI_DESVIO_TENSAO:
				fprintf (fp, "%02d/%02d/%02d;%02d:%02d:%02d;%03d;IniDesTens;%8s;%8s;%6.3f;%8s;%6.3f;\n",
						data_aux.tm_mday,
						data_aux.tm_mon+1,
						/* -- Y2k inicio: ano de 2 digitos -- */
						TM_YEAR_TO_2DIGIT(data_aux.tm_year),
						/* -- Y2k fim -- */
						data_aux.tm_hour,
						data_aux.tm_min,
						data_aux.tm_sec,
						(evento+i)->CubaIniEv,
						(evento+i)->TipoMsg.ParEv[0].StringEv,
						(evento+i)->TipoMsg.ParEv[1].StringEv,
						(evento+i)->TipoMsg.ParEv[2].FloatEv,
						(evento+i)->TipoMsg.ParEv[3].StringEv,
						(evento+i)->TipoMsg.ParEv[4].FloatEv);
		  break;
		  case FIM_DESVIO_TENSAO:
				fprintf (fp, "%02d/%02d/%02d;%02d:%02d:%02d;%03d;FimDesTens;%8s;%8s;%6.3f;%8s;%6.3f;\n",
						data_aux.tm_mday,
						data_aux.tm_mon+1,
						/* -- Y2k inicio: ano de 2 digitos -- */
						TM_YEAR_TO_2DIGIT(data_aux.tm_year),
						/* -- Y2k fim -- */
						data_aux.tm_hour,
						data_aux.tm_min,
						data_aux.tm_sec,
						(evento+i)->CubaIniEv,
						(evento+i)->TipoMsg.ParEv[0].StringEv,
						(evento+i)->TipoMsg.ParEv[1].StringEv,
						(evento+i)->TipoMsg.ParEv[2].FloatEv,
						(evento+i)->TipoMsg.ParEv[3].StringEv,
						(evento+i)->TipoMsg.ParEv[4].FloatEv);
		  break;
		  case LOG_OPER_CUBA:
				fprintf (fp, "%02d/%02d/%02d;%02d:%02d:%02d;%03d;LogCuba;%8s;%8s;%8s;%8s;%8s;\n",
						data_aux.tm_mday,
						data_aux.tm_mon+1,
						/* -- Y2k inicio: ano de 2 digitos -- */
						TM_YEAR_TO_2DIGIT(data_aux.tm_year),
						/* -- Y2k fim -- */
						data_aux.tm_hour,
						data_aux.tm_min,
						data_aux.tm_sec,
						(evento+i)->CubaIniEv,
						(evento+i)->TipoMsg.ParEv[0].StringEv,
						(evento+i)->TipoMsg.ParEv[1].StringEv,
						(evento+i)->TipoMsg.ParEv[2].StringEv,
						(evento+i)->TipoMsg.ParEv[3].StringEv,
						(evento+i)->TipoMsg.ParEv[4].StringEv);
		  break;
		  case CFG_PAR_CUBA:
				fprintf (fp, "%02d/%02d/%02d;%02d:%02d:%02d;%03d;CfgParCuba;%8s;%8s;%8s;%8s;%8s;\n",
						data_aux.tm_mday,
						data_aux.tm_mon+1,
						/* -- Y2k inicio: ano de 2 digitos -- */
						TM_YEAR_TO_2DIGIT(data_aux.tm_year),
						/* -- Y2k fim -- */
						data_aux.tm_hour,
						data_aux.tm_min,
						data_aux.tm_sec,
						(evento+i)->CubaIniEv,
						(evento+i)->TipoMsg.ParEv[0].StringEv,
						(evento+i)->TipoMsg.ParEv[1].StringEv,
						(evento+i)->TipoMsg.ParEv[2].StringEv,
						(evento+i)->TipoMsg.ParEv[3].StringEv,
						(evento+i)->TipoMsg.ParEv[4].StringEv);
		  break;
		  case EVENTO_INC_OPERACAO:
				fprintf (fp, "%02d/%02d/%02d;%02d:%02d:%02d;%03d;EvIncOper;%8s;%8s;%8s;%8s;%8s;\n",
						data_aux.tm_mday,
						data_aux.tm_mon+1,
						/* -- Y2k inicio: ano de 2 digitos -- */
						TM_YEAR_TO_2DIGIT(data_aux.tm_year),
						/* -- Y2k fim -- */
						data_aux.tm_hour,
						data_aux.tm_min,
						data_aux.tm_sec,
						(evento+i)->CubaIniEv,
						(evento+i)->TipoMsg.ParEv[0].StringEv,
						(evento+i)->TipoMsg.ParEv[1].StringEv,
						(evento+i)->TipoMsg.ParEv[2].StringEv,
						(evento+i)->TipoMsg.ParEv[3].StringEv,
						(evento+i)->TipoMsg.ParEv[4].StringEv);
		  break;
		  case EV_AGARRACAM:
				fprintf (fp, "%02d/%02d/%02d;%02d:%02d:%02d;%03d;CamAgarrad;%d;%6.3f;;;;\n",
						data_aux.tm_mday,
						data_aux.tm_mon+1,
						/* -- Y2k inicio: ano de 2 digitos -- */
						TM_YEAR_TO_2DIGIT(data_aux.tm_year),
						/* -- Y2k fim -- */
						data_aux.tm_hour,
						data_aux.tm_min,
						data_aux.tm_sec,
						(evento+i)->CubaIniEv,
						(evento+i)->TipoMsg.ParEv[0].StringEv,
						(evento+i)->TipoMsg.ParEv[1].StringEv,
						(evento+i)->TipoMsg.ParEv[2].StringEv,
						(evento+i)->TipoMsg.ParEv[3].StringEv,
						(evento+i)->TipoMsg.ParEv[4].StringEv);
		  break;
		  case EV_PROVQUEB:
				fprintf (fp, "%02d/%02d/%02d;%02d:%02d:%02d;%03d;PROVQUEB;%4.0f;%9s;%7s;%7s;;\n",
						data_aux.tm_mday,
						data_aux.tm_mon+1,
						/* -- Y2k inicio: ano de 2 digitos -- */
						TM_YEAR_TO_2DIGIT(data_aux.tm_year),
						/* -- Y2k fim -- */
						data_aux.tm_hour,
						data_aux.tm_min,
						data_aux.tm_sec,
						(evento+i)->CubaIniEv,
						(evento+i)->TipoMsg.ParEv[0].LongEv,
						(evento+i)->TipoMsg.ParEv[1].StringEv,
						(evento+i)->TipoMsg.ParEv[2].StringEv,
						(evento+i)->TipoMsg.ParEv[3].StringEv);
		  break;
		  default:
		  break;

		}
		i++;
	  }
    }
  }
  free( evento );

  fclose (fp);
  return (0);
}
