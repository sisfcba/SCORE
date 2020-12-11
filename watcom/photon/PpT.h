/*
 * PpT.h	
 *
 *		Photon Printer context structure
 *
 *  Copyright by QNX Software Systems Limited 1990-1994. All rights reserved.
 */
#ifndef __PPCTRL_H_INCLUDED
#define __PPCTRL_H_INCLUDED
#include <photon/PhInternal.h>
#ifndef _LIMITS_H_INCLUDED
#include <limits.h>
#endif

#include <photon/PhPack.h>

// PpPrintContext_t.control.changed[]
enum { PRINTER_GLOBAL, PRINTER_LOCAL, INITIAL_PC, INTERACTIVE_PC };


typedef struct 
	{
	char 		*name;
	char		*location;
	char 		*device;
	char		*filter;
	PhRect_t 	non_printable_area;
	char		*properties_app;
	char		*preview_app;
	ulong_t		spare;
	} PpPCPrinter_spec_t;

typedef struct 
	{
	char 		*filename;
	char 		*job_name;
	char 		*comment;
	char		*date;
	char		*user_id;
	char		*page_range;		// "all", "selection", "1,3-4,8,10-"
	ulong_t		spare;
	} PpPCSession_t;

typedef struct 
	{
	ulong_t		changed[4];
	ulong_t		locked;
	int 		fd;
	char 		*tmp_target;
	char 		do_preview;
	char		flags;
	char		spare1[2];
	ulong_t		emitted;
	ulong_t		cur_dest_size; // this many bytes written to the target.
	} PpPCControl_t;
#define Pp_CF_SHMEM_TARGET	0x80 /*(r/o)*/
#define Pp_CF_ABORTED		0x40 /*(r/o)*/
typedef struct 
	{
	PhPoint_t	source_offset;
	PhDim_t		source_dim;
	PhDim_t		source_resolution; //dpi ( w & h )
	ulong_t		source_colors; 
	PhPoint_t	scale;
	PhRect_t	margins;
	ulong_t		intensity; // (0 - 100000) in thousanths of a percent
	PhDim_t		printer_resolution; // dpi ( w & h )
	PhDim_t		paper_size;
	char		collating_mode;
	char		dithering;
	char		copies;
	char		orientation;
	char		duplex;
	char		paper_type;
	char		paper_source;
	char		inktype;
	char		color_mode;
	char		spare1;
	ushort_t	pagenum;
	ulong_t		max_dest_size; // Dont allow cur_dest_size to exceed this.
	} PpPCOutput_spec_t;

typedef struct printer_context PpPrintContext_t;
struct printer_context {
	PhDrawContext_t		dc;
	PhGrafxInfo_t 		*graphics_info;
	PpPCPrinter_spec_t  printer_spec;
	PpPCSession_t 		session;
	PpPCControl_t		control;
	PpPCOutput_spec_t 	output_spec;
	};

// Printer control draw stream commands.
#define Pp_SET_SOURCE_SIZE		 	0x01f1
#define Pp_SET_PRINTER_RESOLUTION 	0x02f1
#define Pp_SET_PAPER_SIZE 			0x03f1
#define Pp_SET_SOURCE_OFFSET	 	0x04f1
#define Pp_SET_MARGINS				0x05f1
#define Pp_SET_ORIENTATION		 	0x06f1
#define Pp_SET_COLOR_MODE		 	0x07f1
#define Pp_SET_NUM_COPIES		 	0x08f1
#define Pp_SET_PAGE_RANGE		 	0x09f1
#define Pp_SET_SCALE			 	0x0af1
#define Pp_SET_SOURCE_RESOLUTION 	0x0bf1
#define Pp_SET_SOURCE_COLORS 		0x0cf1

#define Pp_SET_PRINTER_COLORS 		0x0df1
#define Pp_SET_CLIP_RECT 			0x0ef1

#define Pp_SET_NON_PRINT_MARGINS	0x0ff1
#define Pp_SET_PAPER_SOURCE		 	0x10f1
#define Pp_SET_PAPER_TYPE		 	0x11f1
#define Pp_SET_COLLATING_MODE	 	0x12f1
#define Pp_SET_DUPLEX_PRINTING	 	0x13f1
#define Pp_SET_DITHERING		 	0x20f1
#define Pp_SET_INTENSITY		 	0x21f1
#define Pp_SET_INK_TYPE			 	0x22f1
#define Pp_SET_PRINTER_NAME		 	0x33f1
#define Pp_SET_PRINTER_LOCATION	 	0x34f1
#define Pp_SET_PRINTER_DEVICE	 	0x35f1
#define Pp_SET_PRINTER_FILTER	 	0x36f1
#define Pp_SET_PRINTER_DRIVER	 	0x36f1
#define Pp_SET_USER_ID			 	0x37f1
#define Pp_SET_AUTHOR			 	0x38f1
#define Pp_SET_SUBMISSION_DATE	 	0x39f1
#define Pp_START_OF_DOCUMENT	 	0x01f2
#define Pp_END_OF_DOCUMENT		 	0x02f2
#define Pp_VPAGE				 	0x03f2
#define Pp_COMPLETE_ACTION		 	0x04f2
#define Pp_ABORTED				 	0x05f2
#define Pp_TOTAL_PAGES			 	0x06f2

#define Pp_SET_NONPRINT_MARGINS		0x0ff1
#define Pp_SET_JOB_NAME				0x38f1

// For Printer context modify function
#define Pp_PC_MODIFY 3

// Printer Context changed bits
// used in PpPrintModifyPC() to specify which member
// is to be modified in the provide PC.
#define Pp_PC_NAME 					0 
#define Pp_PC_LOCATION		 		1
#define Pp_PC_DEVICE 				2
#define Pp_PC_FILTER 				3
#define Pp_PC_DRIVER 				3
#define Pp_PC_NONPRINT_MARGINS 		4
#define Pp_PC_PROP_APP		 		5
#define Pp_PC_PREVIEW_APP			6
#define Pp_PC_FILENAME				7
#define Pp_PC_COMMENT 				8
#define Pp_PC_DATE 					9
#define Pp_PC_USER_ID	 			10
#define Pp_PC_PAGE_RANGE			11
#define Pp_PC_SOURCE_OFFSET 		12
#define Pp_PC_SOURCE_SIZE 			13
#define Pp_PC_SOURCE_RESOLUTION 	14
#define Pp_PC_SOURCE_COLORS 		15
#define Pp_PC_SCALE 				16
#define Pp_PC_MARGINS 				17
#define Pp_PC_INTENSITY 			18
#define Pp_PC_PRINTER_RESOLUTION	19
#define Pp_PC_PAPER_SIZE	 		20
#define Pp_PC_COLLATING_MODE 		21
#define Pp_PC_DITHERING 			22
#define Pp_PC_COPIES 				23
#define Pp_PC_ORIENTATION 			24
#define Pp_PC_DUPLEX 				25
#define Pp_PC_PAPER_TYPE 			26
#define Pp_PC_PAPER_SOURCE 			27
#define Pp_PC_INKTYPE	 			28
#define Pp_PC_COLOR_MODE 			29
#define Pp_PC_DO_PREVIEW 			30
#define Pp_PC_JOB_NAME	 			31
#define Pp_PC_CONTROL	 			32 // read only, and no changed bit.
#define Pp_PC_MAX_DEST_SIZE			33 // no changed bit

// Printer Dithering modes  use with Pp_PC_DITHERING
#define Pp_DT_DONT_CARE		0
#define Pp_DT_NONE			1
#define Pp_DT_HALFTONE1		2
#define Pp_DT_PHOTO1		3

// PpPrintModify "data" values.
#define Pp_FORCE_CLOSE	 	0
#define Pp_CHANGED_DEVICE 	1
#define Pp_CHANGED_FILENAME	2

// Print Properties Message subtypes
#define Pp_MSG_REQUEST 				0
#define Pp_MSG_REQUEST_REPLY_LOC 	1
#define Pp_MSG_REQUEST_REPLY_INT 	2
#define Pp_MSG_UPDATE				3
#define Pp_MSG_UPDATE_REPLY 		4
#define Pp_MSG_CANCEL				5
#define Pp_MSG_CANCEL_REPLY 		6

#define Pp_PM_CLOSE		0

// For use with PpPrintWidget()
#define Pt_PP_RESIZE_WIDGET	0
#define Pt_PP_RESIZE_PC		1
#define Pt_PP_NO_RESIZE		2

// Print Properties Message header
typedef struct 
{
	short type;
	short subtype;
} PpPrintMsgHeader_t;

#include <photon/PhPackPop.h>

#endif
