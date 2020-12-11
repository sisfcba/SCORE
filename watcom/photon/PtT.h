/*
 * 	PtT.h	
 *		Manifests and structure definitions for the Photon widget lib
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */

#ifndef __PT_T_H_INCLUDED
#define __PT_T_H_INCLUDED

#include <signal.h>
#include <stddef.h>
#if defined(__QNXNTO__)
	#include <spawn.h>
#else
	#include <sys/qnx_glob.h>
#endif

#ifndef __PH_H_INCLUDED
 #include <Ph.h>
#endif

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

#if 0 /* Sorry Brian, I don't think these should be here... - wojtek */
/* min and max macros */
#if !defined(__max)
#define __max(a,b)  (((a) > (b)) ? (a) : (b))
#endif
#if !defined(max) && !defined(__cplusplus)
#define max(a,b)  (((a) > (b)) ? (a) : (b))
#endif
#if !defined(__min)
#define __min(a,b)  (((a) < (b)) ? (a) : (b))
#endif
#if !defined(min) && !defined(__cplusplus)
#define min(a,b)  (((a) < (b)) ? (a) : (b))
#endif
#endif

/* General-purpose constants */

#define Pt_VERTICAL		0
#define Pt_HORIZONTAL	1

#define Pt_ALIGN_CENTER	0x2
#define Pt_ALIGN_TOP	0x10
#define Pt_ALIGN_BOTTOM	0x20
#define Pt_ALIGN_LEFT	0x40
#define Pt_ALIGN_RIGHT	0x80


typedef struct Pt_widget PtWidget_t;
typedef struct Pt_widget_class PtWidgetClass_t;

typedef struct Pt_widget_class_ref{
	PtWidgetClass_t *wclass;
	PtWidgetClass_t * (*init)(void);
} PtWidgetClassRef_t;


/*
 * General-purpose structures
 */

typedef struct Pt_arg_entry {
	long				type;
	long				value;
	long				len;
} PtArg_t;

typedef struct Pt_callback_info {
	unsigned long		reason;
	unsigned long		reason_subtype;
	PhEvent_t 			*event;
	void				*cbdata;
} PtCallbackInfo_t;

typedef struct Pt_callback {
	int			(*event_f)( PtWidget_t *, void *, PtCallbackInfo_t * );
	void			*data;
} PtCallback_t;

typedef struct Pt_callback_list {
	struct Pt_callback_list		*next;
	PtCallback_t				cb;
} PtCallbackList_t;

typedef struct Pt_balloon_callback {
	PtWidget_t			*widget;
	void		(*event_f)( PtWidget_t *, void *, PtCallbackInfo_t * );
} PtBalloonCallback_t;

	typedef struct Pt_callback_stack 
PtCallbackStack_t;
struct Pt_callback_stack {
	PtCallbackStack_t	*next;
	PtWidget_t			*widget;
	PtCallbackList_t	*next_cb;
	};
	
typedef int PtCallbackF_t( PtWidget_t *widget, void *data, PtCallbackInfo_t *cbinfo );

// Reason Codes passed to callback in PtCallbackInfo_t parm.
#define Pt_INFLATE_BALLOON	0
#define Pt_POP_BALLOON		1

typedef struct Pt_balloon_callback_list {
	struct Pt_balloon_callback_list		*next;
	PtBalloonCallback_t			cb;
} PtBalloonCallbackList_t;

typedef struct Pt_hotkey_callback {
	unsigned short		key_sym_cap;
	short				flags;
	unsigned long		key_mods;
	PtWidget_t			*widget;
	void 				*data;
	int					(*event_f)( PtWidget_t *, void *, PtCallbackInfo_t * );
} PtHotkeyCallback_t;
// Hotkey flags...
#define Pt_HOTKEY_SYM 			0x0001
#define Pt_HOTKEY_IGNORE_MODS 	0x0002

typedef struct Pt_hotkey_callback_list {
	struct Pt_hotkey_callback_list		*next;
	PtHotkeyCallback_t			cb;
} PtHotkeyCallbackList_t;

typedef struct Pt_raw_callback {
	unsigned long	event_mask;
	int				(*event_f)( PtWidget_t *, void *, PtCallbackInfo_t * );
	void			*data;
} PtRawCallback_t;

typedef struct Pt_raw_callback_list {
	struct Pt_raw_callback_list		*next;
	PtRawCallback_t  				cb;
} PtRawCallbackList_t;


typedef struct Pt_widget_list {
	struct Pt_widget_list	*next;
	PtWidget_t				*widget;
	int 					flags;
} PtWidgetList_t;

/* Used by PtNotice(), PtPrompt() and PtAlert() (note that these values must
   not conflict with Pt_LEFT, Pt_CENTER or Pt_RIGHT as defined in PtLabel.h) */
#define Pt_MODAL		0x4
#define Pt_ESC_DISABLE	0x8
#define Pt_RELATIVE		0x10
#define Pt_MULTITEXT	0x20

typedef int PtDataRemoveF_t( const int type, const int subtype, void * const data, const unsigned int len );

typedef struct pthetdata PtDataHdr_t;
struct pthetdata 
	{
	long type, subtype;
	PtDataHdr_t *next;
	void *data;
	unsigned int len;
	PtDataRemoveF_t *remove;
	};


#if defined(__cplusplus)
	#define PtSetArg( _arg, _type, _value, _len ) \
		PtSetArg( _arg, _type, (long)(_value), (long)(_len) )
#else
	#if defined(_NO_INLINE_DO_WHILE0)
	#define PtSetArg( arg, _type, _value, _len ) ( 	\
		(arg)->type = (long)(_type),  	 			\
		(arg)->value = (long)(_value),				\
		(arg)->len = (long)(_len)					\
	)
	#else
	#define PtSetArg( arg, _type, _value, _len ) do{  	\
		PtArg_t *__ptargtptr = (arg);	 				\
		__ptargtptr->type = (long)(_type);  			\
		__ptargtptr->value = (long)(_value);			\
		__ptargtptr->len = (long)(_len);				\
	} while( 0 )
	#endif
#endif

/* Static initializer for PtArg_t */
#define Pt_ARG( _type, _value, _len ) \
		{ (_type), (long)(_value), (long)(_len) }

/*
 *
 * Interface to PtSetStruct
 *
 */
	
#define Pt_ARG_OFFSET_MASK			0x0000FFFF
//#define Pt_ARG_MODE_MASK			0x003F0000
#define Pt_ARG_MODE_MASK			0x000F0000
#define Pt_ARG_EXTENDED_TYPES_MASK	0x00300000
#define Pt_ARG_SIZE_MASK			0xFFC00000
#define Pt_ARG_SIZE_SHIFT			22
#define Pt_ARG_EXTENDED_SHIFT		20

#define Pt_CHANGE_INVISIBLE			NULL
#define Pt_CHANGE_REDRAW			((void(*)(PtWidget_t*,PtArg_t const*)) 1)
#define Pt_CHANGE_RESIZE			((void(*)(PtWidget_t*,PtArg_t const*)) 2)
#define Pt_CHANGE_REBUILD			((void(*)(PtWidget_t*,PtArg_t const*)) 3)
#define Pt_CHANGE_INTERIOR			((void(*)(PtWidget_t*,PtArg_t const*)) 4)
#define Pt_CHANGE_RESIZE_REDRAW		((void(*)(PtWidget_t*,PtArg_t const*)) 5)
#define Pt_CHANGE_PREVENT			((void(*)(PtWidget_t*,PtArg_t const*)) 6)
#define Pt_QUERY_PREVENT			((int(*)(PtWidget_t*,PtArg_t*)) 6)

#define Pt_ARG_SIZE( x )			( (long)x << Pt_ARG_SIZE_SHIFT )

#define Pt_ARG_PARM( x )			( (long)x << Pt_ARG_SIZE_SHIFT )
// depricated--^ use Pt_ARG_SIZE

#define _Pt_SET_PTR( base, arg ) ( (char *)base + ( arg & Pt_ARG_OFFSET_MASK ) )
#define _Pt_GET_SIZE( type )	 ( ( type & Pt_ARG_SIZE_MASK ) >> Pt_ARG_SIZE_SHIFT )

#define _Pt_GET_EXTENDED_TYPE( arg ) (arg & Pt_ARG_EXTENDED_TYPES_MASK)

#define _Pt_GET_PARM( type )	 ( ( type & Pt_ARG_SIZE_MASK ) >> Pt_ARG_SIZE_SHIFT )
//depricated --^, use Pt_GET_SIZE

#define Pt_ARG_IN_EXDATA			0x00100000
#define Pt_ARG_IN_WDATA				0x00200000

/*
 * Pt_ARG_MODE_CHAR, SHORT, LONG and INT:
 *	assign arg->value to structure member if arg->len == 0
 *	otherwise treat arg->len as a bitmask 
 */
#define Pt_ARG_MODE_CHAR			0x00010000
#define Pt_ARG_MODE_SHORT			0x00020000
#define Pt_ARG_MODE_LONG			0x00030000
#define Pt_ARG_MODE_INT			Pt_ARG_MODE_LONG

//#define PtGlobalFocusPrev( a, e ) PtGlobalFocusPrevFrom( PtContainerFindFocus( a ), e )
//#define PtGlobalFocusNext( a, e ) PtGlobalFocusNextFrom( PtContainerFindFocus( a ), e )

/*
 * Pt_ARG_MODE_CHAR_FLAGS, SHORT_FLAGS and LONG_FLAGS:
 *	assign arg->value to structure member if arg->len == 0
 *	otherwise treat arg->len as a bitmask 
 */
#define Pt_ARG_MODE_CHAR_FLAGS		0x00040000
#define Pt_ARG_MODE_SHORT_FLAGS		0x00050000
#define Pt_ARG_MODE_LONG_FLAGS		0x00060000
/*
 * Pt_ARG_MODE_PTR
 *	assign ptr to structure member
 */
#define Pt_ARG_MODE_PTR				0x00070000
/*
 * Pt_ARG_MODE_BOOLEAN
 *	assign boolean variable, length member is bit mask.
 */
#define Pt_ARG_MODE_BOOLEAN			0x00080000

/*
 * Pt_ARG_MODE_STRUCT
 *	copy SIZE bytes from (char *)arg->value into structure at offset
 */
#define Pt_ARG_MODE_STRUCT			0x00090000

#define Pt_ARG_MODE_VARIABLE		0x00090000
//depricated --^

/*
 * Pt_ARG_MODE_ALLOC
 *	allocate arg->len bytes at assign ptr to structure member
 *	copy arg->len bytes from (char *)arg->value to ptr
 */
#define Pt_ARG_MODE_ALLOC			0x000A0000

/*
 * Pt_ARG_MODE_STRALLOC
 *	same as Pt_ARG_MODE_ALLOC but length is determined by taking
 *	length of string referred to by (char *)arg->value... + 1
 */
#define Pt_ARG_MODE_STRING			0x000B0000

#define Pt_ARG_MODE_STRALLOC		0x000B0000
//depricated --^

/*
 * Pt_ARG_MODE_ARRAY
 *	alloc but with length * ARG_SIZE
 *	next unsigned receives length
 */
#define Pt_ARG_MODE_ARRAY			0x000C0000

/*
 * Pt_ARG_MODE_LINKED
 *	structure member is a pointer to first member of a linked list
 *	first item in linked list must be ptr to next item
 *	SIZE is length of data following the "next" member.
 */
#define Pt_ARG_MODE_LINKED			0x000D0000

/*
 * Pt_ARG_EXTENDED
 *  Modifier which indicates the resource resides
 *	in the widget extended resources block.
 */
// defined earlier as...
//#define Pt_ARG_MODE_EXTENDED		0x00200000

/*
 * length argument for Pt_ARG_MODE_LINKED
 */
#define Pt_LINK_INSERT				-1
#define Pt_LINK_DELETE				-2

typedef struct Pt_linked_list
{
	struct Pt_linked_list *next;
	char data[1];
} PtLinkedList_t;

/*
 * Pt_ARG_MODE_CALLBACKS
 *	linked list of callbacks
 */
#define Pt_ARG_MODE_CALLBACKS		(Pt_ARG_MODE_LINKED | Pt_ARG_SIZE( sizeof( PtCallback_t ) ) )

/*
 *
 * Some Manifests to make changes to header file types less bothersome.
 * ( don't need to remember to change the widget resource definition
 *   in the class creation function if you use these :-)
 *
 */
#define Pt_STRUCT_SIZEOF( type, field ) sizeof( ( (type*) 0 ) -> field )
#define Pt_PTR_SIZEOF( type, field ) sizeof( * ( (type*) 0 ) -> field )

#define Pt_ARG_IS_NUMBER( type, field ) \
		(	(	Pt_STRUCT_SIZEOF( type, field ) == sizeof(long)			\
				?	Pt_ARG_MODE_LONG									\
				:	Pt_STRUCT_SIZEOF( type, field ) == sizeof(short)	\
					?	Pt_ARG_MODE_SHORT								\
					:	Pt_ARG_MODE_CHAR								\
				)														\
		|	offsetof( type, field ) 									\
			)

#define Pt_ARG_IS_FLAGS( type, field ) \
		(	(	Pt_STRUCT_SIZEOF( type, field ) == sizeof(long)			\
				?	Pt_ARG_MODE_LONG_FLAGS								\
				:	Pt_STRUCT_SIZEOF( type, field ) == sizeof(short)	\
					?	Pt_ARG_MODE_SHORT_FLAGS							\
					:	Pt_ARG_MODE_CHAR_FLAGS							\
				)														\
		|	offsetof( type, field ) 									\
			)

#define Pt_ARG_IS_POINTER( type, field ) \
		(	Pt_ARG_MODE_PTR				\
		|	offsetof( type, field ) 	\
			)

#define Pt_ARG_IS_ALLOC( type, field ) \
		(	Pt_ARG_MODE_ALLOC			\
		|	offsetof( type, field ) 	\
			)

#define Pt_ARG_IS_STRUCT( type, field ) \
		(	Pt_ARG_MODE_STRUCT \
		|	offsetof( type, field ) \
		|	Pt_ARG_SIZE( Pt_STRUCT_SIZEOF( type, field ) ) \
			)

#define Pt_ARG_IS_CALLBACK Pt_ARG_IS_CALLBACK_LIST

#define Pt_ARG_IS_CALLBACK_LIST( type, field ) \
		(	Pt_ARG_MODE_CALLBACKS \
		|	offsetof( type, field ) \
			)

#define Pt_ARG_IS_ARRAY( type, field ) \
		(	Pt_ARG_MODE_ARRAY \
		|	offsetof( type, field ) \
		|	Pt_ARG_SIZE( Pt_PTR_SIZEOF( type, field ) ) \
			)

#define Pt_ARG_IS_STRING( type, field ) \
		(	Pt_ARG_MODE_STRING \
		|	offsetof( type, field ) \
			)

#define Pt_ARG_IS_BOOLEAN( type, field ) \
		(	Pt_ARG_MODE_BOOLEAN \
		|	offsetof( type, field ) \
		|	Pt_ARG_SIZE( Pt_STRUCT_SIZEOF( type, field ) ) \
			)
			
#define Pt_ARG_IS_LINK( type, field ) \
		(	Pt_ARG_MODE_LINKED | offsetof( type, field )\
		| 	Pt_ARG_SIZE( Pt_PTR_SIZEOF( type, field ) - sizeof(void*) ) )
		
/*
 *
 * Miscellaneous manifests
 *
 */

/* 
 * Arg types for creating widget classes 
 */
#define Pt_SET_VERSION				Pt_ARG_IS_NUMBER(PtWidgetClass_t,version)
#define Pt_SET_STATE_LEN			Pt_ARG_IS_NUMBER(PtWidgetClass_t,state_len)
#define Pt_SET_WD_STATE_LEN			Pt_ARG_IS_NUMBER(PtWidgetClass_t,wd_state_len)
#define Pt_SET_DFLTS_F				Pt_ARG_IS_POINTER(PtWidgetClass_t,dflts_f)
#define Pt_SET_CONNECT_F			Pt_ARG_IS_POINTER(PtWidgetClass_t,connect_f)
#define Pt_SET_EXTENT_F				Pt_ARG_IS_POINTER(PtWidgetClass_t,extent_f)
#define Pt_SET_INIT_F				Pt_ARG_IS_POINTER(PtWidgetClass_t,init_f)
#define Pt_SET_DRAW_F     			Pt_ARG_IS_POINTER(PtWidgetClass_t,draw_f)
#define Pt_SET_UNREALIZE_F			Pt_ARG_IS_POINTER(PtWidgetClass_t,unrealize_f)
#define Pt_SET_REALIZED_F			Pt_ARG_IS_POINTER(PtWidgetClass_t,realized_f)
#define Pt_SET_DESTROY_F			Pt_ARG_IS_POINTER(PtWidgetClass_t,destroy_f)
#define Pt_SET_FLAGS				Pt_ARG_IS_FLAGS(PtWidgetClass_t,flags)
#define Pt_SET_RAW_CALLBACKS		Pt_ARG_IS_LINK(PtWidgetClass_t,callbacks)
#define Pt_SET_RESOURCES			Pt_ARG_IS_POINTER(PtWidgetClass_t,resources)
#define Pt_SET_NUM_RESOURCES		Pt_ARG_IS_NUMBER(PtWidgetClass_t, num_resources)
#define Pt_SET_STATIC_RESOURCES		Pt_SET_RESOURCES
#define Pt_SET_PRESORT_RESOURCES	Pt_SET_RESOURCES

#define Pt_SET_SETRESOURCES_F			Pt_ARG_IS_POINTER(PtWidgetClass_t,setres_f)
#define Pt_SET_GETRESOURCES_F			Pt_ARG_IS_POINTER(PtWidgetClass_t,getres_f)

/*
 * Widget drawing modes (PtDrawClippedWidget)
 */
#define Pt_DRAW_DEFAULT			0x0000
#define Pt_DRAW_OVERWRITE		0x0001
#define Pt_DRAW_RAW				0x0002
#define Pt_DRAW_START			0x0003
#define Pt_DRAW_COPY_RECTS		0x0010

#define Pt_DRAW_MODE_MASK		0x000F

/*
 * Return codes for chained functions (raw callbacks,realize_f's,etc.)
 */
#define Pt_CONTINUE					0
#define Pt_HALT						1
#define Pt_END						2
#define Pt_PASS_END					3

/* 
 * Boolean flags 
 */
#define Pt_TRUE						-1
#define Pt_FALSE					0


/*
 * "Generally useful flags"
 */
#define Pt_NEVER					0x00
#define Pt_ALWAYS					0x01
#define Pt_AS_REQUIRED				0x02
#define Pt_INITIAL					0x04

#define Pt_DYNAMIC					0
#define Pt_BLIT						0xFFFF
#define Pt_BLIT_FORCE				0xFFFE

/*
 * for PtHasCustody()...(return values)
 */
#define Pt_IMMEDIATE_CHILD		1
#define Pt_SUBORDINATES_CHILD	2
/*
 *  Flags and values for PtWidgetTree* ( (D)irection flag )
 */
// reserved bits            0x0000000F
#define Pt_TRAVERSE_START	0		 // a value
#define Pt_TRAVERSE_DONE	0		 // a value
#define Pt_TRAVERSE_ROOT	0x00000001
#define Pt_TRAVERSE_LAST	0x00000002
#define Pt_TRAVERSE_BACK	0x00000004
#define Pt_TRAVERSE_FORCE	0x00000008 

/*
 * Widget specific colors
 */
 
#define	Pt_WINDOWACTIVECOLOR		PgRGB(0, 128, 112)
#define	Pt_BALLOONCOLOR				PgRGB( 254, 255, 177 )

#define Pt_DEFAULT_COLOR			(-3)
#define Pt_INHERIT_COLOR			(-4)

#define Pt_DEFAULT_FONT				((char *)0)
#define Pt_INHERIT_FONT				((char *)-1)


/*
 *
 * Resources
 *
 */

/* 
 * Macro to order resource number allocation
 *	Pt_RESOURCE( unsigned level, unsigned index )
 */
#define Pt_RESOURCE_RANGE		1000
#define Pt_RESOURCE( a, b )		( Pt_RESOURCE_RANGE * a + b )
#define Pt_CONTRIB( a )		( 1000 + a )
#define Pt_USER( a )		( 5000 + a )
#define Pt_RTIME( a )		( 11000 + a )

/*
// reserved resource value for indicating widget version #
// { Pt_VERSION, 11, 0, 0, 0} (must be first resource of widget
// to be recognized.  If this record is present, it indicates
// how this widget's resources are to be handled.  If absent
// the resources are treated as Photon 1.0 release widget resources.
*/
#define Pt_VERSION			1


/*
 * The resource record 
 */
typedef struct Pt_resource_rec {
	unsigned long			type;
	void					(*mod_f)( PtWidget_t *, PtArg_t const * );
	int						(*query_f)( PtWidget_t *, PtArg_t * );
	unsigned long			arg_value;
	unsigned long			arg_len;	
} PtResourceRec_t;

/*
 * The old resource record 
 *
typedef struct Pt_1_0resource_rec {
	unsigned long			type;
	void					(*mod_f)( PtWidget_t *, PtArg_t const * );
	unsigned long			arg_value;
	unsigned long			arg_len;	
} Pt1_0ResourceRec_t;
 */

/*
 * Base widget class structure
 */
struct Pt_widget_class {
	struct Pt_widget_class	*superclass;
	PtWidgetClassRef_t		*class_ref;
	unsigned				class_len;
	unsigned 				state_len;
	unsigned long			flags;
	void					(*dflts_f)( PtWidget_t * );
	int						(*init_f)( PtWidget_t * );
	void					(*extent_f)( PtWidget_t * );
	int						(*connect_f)( PtWidget_t * );
	void					(*draw_f)( PtWidget_t *, PhTile_t const * );
	void					(*unrealize_f)( PtWidget_t * );
	void					(*destroy_f)( PtWidget_t * );
	PtResourceRec_t			*resources;
	void					(*realized_f)( PtWidget_t * );
	unsigned				num_resources;
	PtRawCallbackList_t		*callbacks;
	PhSoul_t				widget_souls;
	int						(*setres_f)( PtWidget_t *, int, PtArg_t const *, PtResourceRec_t const *rrec );
	int						(*getres_f)( PtWidget_t const *, int, PtArg_t * );
	short					version;
	unsigned short			wd_state_len;
};

/* Flags for PtWidgetClass_t */
#define	Pt_CONTAINER				0x00000001	/* Children should be drawn within */
#define Pt_RECTANGULAR				0x00000002	/* If filled, is opaque */
#define Pt_DISCONTINUOUS			0x00000004	/* gets own expose */
#define Pt_UNUSED					0x00000008
#define Pt_CLEAN_RESOURCES			0x00000010
#define Pt_INDEX_RESOURCES			0x00000020
#define Pt_FORCE_UNREALIZE			0x00000040
#define Pt_DISJOINT					0x00000080	/* menus/windows (co-ords irrelevant) */
#define Pt_COMPOUND					0x00000100
#define Pt_UNCLEAN_RESOURCES		0x00000200
#define Pt_NO_INHERITED_RESOURCES	0x00000400
#define Pt_OCCLUSIVE				0x00000800

#define PT_INPUT_ID		1
#define PT_WORKPROC_ID	2

typedef int PtRegCallbackProcF_t(void *data, PhConnectId_t client, void *fwd_msg, size_t msg_len, int type );
typedef int PtInputCallbackProcF_t(void *, pid_t, void *, size_t);
typedef int PtWorkProcF_t(void *);
typedef int PtSignalProcF_t(int, void *);

typedef PtRegCallbackProcF_t *PtRegCallbackProc_t;
typedef PtInputCallbackProcF_t *PtInputCallbackProc_t;
typedef PtWorkProcF_t *PtWorkProc_t;
typedef PtSignalProcF_t *PtSignalProc_t;

typedef struct Pt_reg {
	struct Pt_reg		*next;
	PtRegCallbackProc_t func;
	int					type;
	void				*data;
} PtRegRec_t, PtRegId_t;

typedef struct Pt_reg_list {
	PtRegRec_t		*head;
	void				*reserved;
} PtRegList_t;

typedef struct Pt_input {
	struct Pt_input			*next;
	PtInputCallbackProc_t	func;
	pid_t					pid;
	void					*data;
	unsigned short			active;
} PtInputRec_t, PtInputId_t;

typedef struct Pt_work {
	struct Pt_work		*next;
	PtWorkProc_t		func;
	void				*data;
} PtWorkProcRec_t, PtWorkProcId_t;

typedef struct Pt_input_list {
	PtInputRec_t		*head;
	void				*reserved;
} PtInputList_t;


typedef struct Pt_work_proc_list {
	PtWorkProcRec_t		*head;
	void				*reserved;
} PtWorkProcList_t;

struct Pt_signal_proc_list_el {
	struct Pt_signal_proc_list_el	*next;
	sigset_t						sigset;
	PtSignalProc_t					func;
	void							*data;
};

typedef struct Pt_signal_proc_list {
	struct Pt_signal_proc_list_el	*procs;
	unsigned short		level;
	unsigned short		flags;
	sigset_t volatile	pending;
	sigset_t			handled;
} PtSignalProcList_t;


struct Pt_Pulse {
	#if defined(__QNXNTO__)
		int prio;
	#else
		pid_t proxy;
	#endif
	};

/* The context for an application shell and its descendents.
 * Here to allow multi-threading -- eventually.
 * The library control structure information should be here to
 * eliminate conflicts between threads.
 */
struct Pt_Fd;
struct Pt_AppContext {
	PhEvent_t			*event;
	int					event_size;
	PtInputList_t		inputs;
	PtWorkProcList_t	work_procs;
	PtSignalProcList_t	signal_procs;
	struct Pt_Pulse		*pulses;
	ulong_t				pulse_count;
	struct Pt_Fd		**fds;
	ulong_t				fd_count;
	PtRegList_t			reg;
};

#if defined(__QNXNTO__)
	typedef struct sigevent PtPulseMsg_t;
#else
	typedef pid_t PtPulseMsg_t;
#endif

typedef struct Pt_pulse_msg_id PtPulseMsgId_t;

typedef struct Pt_AppContext *PtAppContext_t;

/* PtAppAddFd() flags */
#if defined(__QNXNTO__)
	#define Pt_FD_READ		0x10000000
	#define Pt_FD_WRITE		0x20000000
	#define Pt_FD_OBAND		0x40000000
	#define Pt_FD_NOPOLL	0x00000000
	#define Pt_FD_DRAIN		0x00000001
#else
	#define Pt_FD_READ		0x1
	#define Pt_FD_WRITE		0x2
	#define Pt_FD_OBAND		0x4
	#define Pt_FD_NOPOLL	0x8
	#define Pt_FD_DRAIN		0x0
#endif

/* typedefs for PtSpawn() */
#if defined(__QNXNTO__)
	typedef struct {
		struct inheritance options;
		int iov[ 10 ];
		}
			PtSpawnOptions_t;
#else
	typedef struct _qnx_spawn_globs PtSpawnOptions_t;
#endif

extern const PtSpawnOptions_t PtSpawnDefaults;

typedef void PtSpawnCbF_t( void *data, int status );

extern PtSpawnCbF_t PtSpawnNoCb;

typedef struct PtSpawnCbId PtSpawnCbId_t;

/* The widget lib control structure */
struct _Pt_sellist;
struct _Pt_evlist;
struct _Pt_ctrl {
	PtWidget_t				*parent, *current;
	int		 				hold_count;
	int						flux_count;
	unsigned				clip_stack_level;
	PhRect_t 				clip_stack[30];
	unsigned long			flags;
	unsigned long			in_update;
	PhRect_t				*rects;
	unsigned				n_rects;
	PtWidgetList_t			*damaged_containers;
	PtWidgetList_t			*destroyed_widgets;
	PhSoul_t				wl_souls;
	PhSoul_t				callback_souls;
	PtWidgetList_t			*top_level;
	PtWidget_t				*cur_menu;
	unsigned long			fep_active;
	int						depth;
	struct _Pt_evlist		*ev_top;
	struct _Pt_sellist		*sel_top;
	int						event_depth;
//	PtCallbackStack_t		*cb_stack;
	PtWidgetList_t			*doomed;
	int						callback_depth;
};

/* _Pt_ctrl flags */
#define Pt_PEN_PRESENT		0x00000001
#define Pt_FEP_PRESENT		0x00000002
#define Pt_FEP_QUERIED		0x00000004
#define Pt_IN_EXPOSE		0x00000008

extern struct _Pt_ctrl *_Pt_;


typedef struct Pt_FILEr PtFILEr_t;
typedef struct Pt_FILEw PtFILEw_t;

#ifdef __cplusplus
};


	inline void
	(PtSetArg)( PtArg_t *_arg, ulong_t _type, ulong_t _value, ulong_t _len )
		{
		_arg->type = _type;
		_arg->value = _value;
		_arg->len = _len;
		}
#endif

#include <photon/PhPackPop.h>

#include <photon/PtProto.h>

#endif
