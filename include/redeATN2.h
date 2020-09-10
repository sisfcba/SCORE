/******************************************************************************

			ATAN - SISTEMAS DE AUTOMACAO E TELECOMUNICACOES LTDA.
       SSCORE - SOFTWARE DO SISTEMA DE CONTROLE DE REDUCOES - VERSAO 3.0

	PROJETO	: CBA - COMPANHIA BRASILEIRA DE ALUMINIO

	SISTEMA	: AUTOMACAO DA SALA 120 KA I

	ARQUIVO	: redeATN2.h

	CONTEUDO: Definicoes, constantes e estruturas referentes a norma
			  IEEE 802.4 ( Implementacao de uma rede Token Passing Bus )

	AUTOR	: Eduardo Pereira

	SISTEMA OPERACIONAL	: QNX 2.15		-		COMPILADOR: C86

	VERSAO	: 1.0						-		DATA	:	14/05/92

	HISTORICO DAS EDICOES
-------------------------------------------------------------------------------
dd/mm/aa | descricao                                            | autor 
-------------------------------------------------------------------------------
******************************************************************************/

#ifdef PROGRAMA_PRINCIPAL
  #define DECL
#else
  #define DECL	extern
#endif

/*
--------------------------------------------------------------------------------
				Constantes Gerais
--------------------------------------------------------------------------------
*/
#define FALSE							0
#define TRUE							1

/* -- Numero maximo de redes em paralelo no micro -- */
#define MAX_NET_MICRO					8

/* -- Estados dos timers -- */
#define	DESATIVADO				0
#define	ARMADO					1
#define	ARMADO_SEM_SINAL		2
#define	ESGOTADO				3

#define ADDRESS_LENGTH					8
#define MAX_PASS_COUNT					((ADDRESS_LENGTH/2)+1)
#define MAX_INTER_SOLICIT_COUNT			50					/* -- 16..255 -- */
#define MAX_DATA_UNIT_LENGTH			1000
#define MAX_TRANSMITTER_FAULT_COUNT		7
#define MAX_RETRY_LIMIT					3
#define MAX_PENDING_FRAMES				1
#define IN_RING_DESIRED					TRUE
/*
--------------------------------------------------------------------------------
				Access Control Machine States
--------------------------------------------------------------------------------
*/
#define  OFFLINE				0
#define  IDLE_ST				9  /* -- trocado por causa do pass_token -- */
#define  DEMAND_IN				2
#define  DEMAND_DELAY			3
#define  CLAIM_TOKEN			4
#define  USE_TOKEN				5
#define  AWAIT_IFM_RESPONSE		6
#define  CHECK_ACCESS_CLASS		7
#define  PASS_TOKEN				1
#define  CHECK_TOKEN_PASS		8
#define  AWAIT_RESPONSE			10

/*
--------------------------------------------------------------------------------
				Timers( Numero de Ticks)
--------------------------------------------------------------------------------
*/
#define TICK						(1.0/20.0)
#define OCTET_TIME					(12.0/9600.0)
/*
#define SLOT_TIME					(unsigned)((160.0*OCTET_TIME)/TICK)
*/
#define SLOT_TIME					3
#define SLOT_TIME_OCTET				150
#define MAX_RING_MAINTENANCE_TIME	(10*SLOT_TIME)
#define HI_PRI_TOKEN_HOLD_TIME		3
#define RING_MAINTENANCE_TIMER_INITIAL_VALUE	0 

/*
--------------------------------------------------------------------------------
				Token passing process
--------------------------------------------------------------------------------
*/
#define  SOLICIT_SUCC			0
/* --    PASS_TOKEN				1	ja definido na maquina de estados -- */
#define  REPEAT_PASS_TOKEN		2
#define  SEND_WHO_FOLLOWS		3
#define  REPEAT_WHO_FOLLOWS		4
#define  SOLICIT_ANY			5
#define  TOTAL_FAILURE			6

/*
--------------------------------------------------------------------------------
				Frame Types
--------------------------------------------------------------------------------
*/
#define  MAC_CONTROL				0
#define  LLC_DATA					1
#define  STATION_MANAGEMENT_DATA	2
#define  SPECIAL_PURPOSE_DATA		3

/*
--------------------------------------------------------------------------------
				States of MAC_control
--------------------------------------------------------------------------------
*/
#define  CLAIM_TOKEN_FC				0
#define  SOLICIT_SUCC_1				1
#define  SOLICIT_SUCC_2				2
#define  WHO_FOLLOWS				3
#define  RESOLVE_CONTENTION			4
#define  TOKEN						8
#define  SET_SUCCESSOR				12

/*
--------------------------------------------------------------------------------
				States of access_class
--------------------------------------------------------------------------------
*/
#define  MAX_ACCESS_CLASS			4  /* -- modificado -- */
#define  RINGMAINTENANCE			0  /* -- modificado -- */

/*
--------------------------------------------------------------------------------
				States of the process of heard
--------------------------------------------------------------------------------
*/
#define  NOTHING					0
#define  COLLISION					1
#define  SUCCESSOR					2

/*
--------------------------------------------------------------------------------
				MAC_actions
--------------------------------------------------------------------------------
*/
#define  REQUEST_WITH_NO_RESPONSE	0
#define  REQUEST_WITH_RESPONSE		1
#define  RESPONSE					2
#define  NOTHING_RECEIVED			3

/*
--------------------------------------------------------------------------------
				Frame bytes
--------------------------------------------------------------------------------
*/
#define START_BYTE					0XFF
#define CAR_EXPAND					0XF0
#define NUM_BYTES_CONTROL			9

/*
--------------------------------------------------------------------------------
				Transmit Machine
--------------------------------------------------------------------------------
*/
#define TAM_BUFFER_TX				1000                                         

/*
--------------------------------------------------------------------------------
				Receive Machine
--------------------------------------------------------------------------------
*/
#define TAM_BUFFER_RX				1000
#define NBYTES_BEFORE_NB			5
#define CONTROL_AREA				0
#define NB_AREA						1
#define DATA_AREA					2
#define FCS_AREA					3
#define UNDEFINED_AREA				4

/*
--------------------------------------------------------------------------------
				Tipos
--------------------------------------------------------------------------------
*/
typedef
  struct MAC_control_frame
  {
	unsigned char Frame_type;
	unsigned char MAC_control;
  } t_MAC_control_frame;

typedef
  struct MAC_data_frame
  {
	unsigned char Frame_type;
	unsigned char MAC_action;
  } t_MAC_data_frame;

union frame_ctrl_typ
{
  t_MAC_control_frame control;
  t_MAC_data_frame    data;
};

typedef
  struct general_frame
  {
	unsigned char			SD;
	union frame_ctrl_typ	FC;
	unsigned char			DA;
	unsigned char			SA;
	unsigned				NB;
	char					data_unit[MAX_DATA_UNIT_LENGTH];
	unsigned				FCS;
  } t_general_frame;

typedef
  struct timer_net
  {
	int bus_quiet_timer;
	int bus_idle_timer;
	int contention_timer;
	int claim_timer;
	int response_window_timer;
	int token_pass_timer;
	int token_hold_timer;
	int token_rotation_timer[MAX_ACCESS_CLASS];		/* -- modificado -- */
  } t_timer_net;

typedef
  struct rede_comum
  {
	/* -- Numero de redes em paralelo -- */
	int				NumRedes;
	/* -- Bit correspondente ao port para cada rede -- */
	/* -- Bit 0=port 17 e Bit 15=port 32. O bit deve estar em 1 -- */
	unsigned int	PortRede[MAX_NET_MICRO];
	/* -- Timer para cada rede -- */
	t_timer_net 	Timer[MAX_NET_MICRO];
	/* -- Ativacao de timer para cada rede -- */
	t_timer_net 	Active[MAX_NET_MICRO];
  } t_rede_comum;

typedef
  struct diagnostic
  {
	unsigned int cont_noise_burst;
  } t_diagnostic;


DECL char	access_class,
			bus_quiet,
			Current_State,
			first_time,
			heard,
			in_ring,
			just_had_token,
			lowest_address,
			noise_burst,
			NS_known,
			pass_state,
			power_ok,            /* indica que o hardware esta' OK */
			random_counter,      /* contador do numero randomico */
			Rx_protocol_frame,
			Rx_data_frame,
			sole_active_station;

DECL unsigned char	TS,
					NS,
					PS,
					TH;

DECL int	claim_pass_count,
			contend_pass_count,
			inter_solicit_count,
			remaining_retries,
			resolution_pass_count,
			target_rotation_time[MAX_ACCESS_CLASS],   /* -- modificado -- */
			transmitter_fault_count;

DECL t_general_frame	Rx_pending_frames[MAX_PENDING_FRAMES],
						Rx_frame,
						Tx_frame;

DECL t_diagnostic		diag;

#ifdef PROGRAMA_PRINCIPAL
	char aux_aux = 0;
#else
	extern char aux_aux;
#endif

/*
--------------------------------------------------------------------------------
				Prototipos
--------------------------------------------------------------------------------
*/
void check(void);
void demand(void);
void idle(void);
void off_claim_use(void);
void pass(void);

