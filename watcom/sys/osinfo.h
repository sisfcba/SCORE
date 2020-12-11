/*
 *  osinfo.h
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __OSINFO_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif
#ifdef __cplusplus
extern "C" {
#endif
struct _osinfo {
    short unsigned  cpu_speed,          /*  A PC is around 960 */
                    num_procs,
                    tick_size,
                    version,
                    timesel,
                    totmemk,
                    freememk;
    char            primary_monitor,
                    secondary_monitor;
    short unsigned  machinesel;
    unsigned short  disksel;        /* pointer to _diskinfo structure */
    unsigned long   diskoff;
    unsigned long   ssinfo_offset;
    short unsigned  ssinfo_sel,
                    microkernel_size;
    char            release,
                    zero2;
    long            sflags;
    nid_t           nodename;
    long            cpu,
                    fpu;
    char            machine[16],
                    bootsrc,
                    zero3[9];
    short unsigned  num_names,
                    num_timers,
                    num_sessions,
                    num_handlers,
                    reserve64k,
                    num_semaphores,
                    prefix_len,
                    zero4[4],
                    max_nodes,
                    proc_freemem,
                    cpu_loadmask,
                    fd_freemem,
                    ldt_freemem,
                    num_fds[3],
                    pidmask,
                    name_freemem;
    long unsigned   top_of_mem;
    long unsigned   freepmem;
    long unsigned   freevmem;
    long unsigned   totpmem;
    long unsigned   totvmem;
    long unsigned   cpu_features;
    short unsigned  zero5[13];
    } ;


#ifndef __cplusplus
volatile
#endif
struct _timesel {
    long            nsec;
    long            seconds;
    long            nsec_inc;
    long unsigned   cycles_per_sec;
    long unsigned   cycle_lo;
    long unsigned   cycle_hi;
    long unsigned   cnt8254;    
    short unsigned  spare[2];
    } ;


struct _machinesel {
    char    primary_monitor;
    char    secondary_monitor;
    struct _cg_entry {
        short unsigned  offset,
                        segment;
        }   cg_table[10];
    } ;

struct _bios_dpt {
        unsigned short      dpt_ncyl;
        unsigned char       dpt_nhead;
        unsigned short      :16;
        unsigned short      dpt_precomp_cyl;
        unsigned char       dpt_ecc_blen; /* ecc burst lenght */
        unsigned char       dpt_ctrl;
#define _DPT_8HEADS     (1<<3)
#define _DPT_DEFECTMAP  (1<<5)
#define _DPT_RETRIES    (3<<6)
        unsigned char       :8,:8,:8;
        unsigned short      dpt_lzone; 
        unsigned char       dpt_nsect;
        unsigned char       :8;
};

struct _diskinfo {
        unsigned short      di_ntab;
        struct {
                unsigned short   di_valid;
                struct _bios_dpt di_bios;
        }                   di_tab[1];
};


struct _ssinfo {
    unsigned long   type;
    struct _ssentry_info {
        unsigned long   code_base;
        unsigned long   code_limit;
        unsigned long   entry_point;
        unsigned long   data_base;
        unsigned long   data_limit;
        unsigned long   data_offset;
        }           entry;
    } ;

/*
 *  System flag definitions
 */

#define _PSF_PROTECTED          0x0001
#define _PSF_NDP_INSTALLED      0x0002
#define _PSF_EMULATOR_INSTALLED 0x000c
#define _PSF_EMU16_INSTALLED    0x0004
#define _PSF_EMU32_INSTALLED    0x0008
#define _PSF_APM_INSTALLED      0x0010
#define _PSF_32BIT_KERNEL       0x1000
#define _PSF_PCI_BIOS           0x2000
#define _PSF_32BIT              0x4000
/*- deprecated -- 423+ sets RESERVE_DOS32 */
#define _PSF_RESERVE_DOS        0x8000
#define _PSF_RESERVE_DOS32      0x0080

/*
 *  Console monitor type definition.
 */
#define _MONITOR_NONE           0x00
#define _MONITOR_MONO           0x01
#define _MONITOR_CGA            0x02
#define _MONITOR_EGA_COLOR      0x04
#define _MONITOR_EGA_MONO       0x05
#define _MONITOR_PGS            0x06
#define _MONITOR_VGA_MONO       0x07
#define _MONITOR_VGA_COLOR      0x08
#define _MONITOR_PS30_MONO      0x0b
#define _MONITOR_PS30_COLOR     0x0c


extern int      qnx_sflags( nid_t, long, long, long *, long * );
extern int      qnx_osinfo( nid_t, struct _osinfo * );
#ifdef __cplusplus
};
#endif

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

/*-
 * This structure is passed as a far pointer on the stack of
 * the first process in the image.
 */

struct _bmachine_info {
        struct _machinesel    machine;
        struct _osinfo        osinfo;
        unsigned long         box;
        unsigned long         bus;

#define _BOX_ISA            0
#define _BOX_IBM_PS2_80    80
#define _BOX_IBM_PS2_60    60
#define _BOX_IBM_PS2_50    50
#define _BOX_IBM_7522      52

#define _BUS_ISA          0
#define _BUS_uCHANNEL     1
#define _BUS_PCI          2
#define _BUS_EISA         3

        unsigned long         memsegs;
        union {
                struct _pmemseg {
                        unsigned long    paddr;
                        unsigned long    nbytes;
                } far *pseg;
                unsigned long space[2];
        } mem;
        unsigned long         smsw;         /* initial msw */
        unsigned long         pci_entrypt;  /* pci-entry point */
        unsigned long         spare[6];
};

#define __OSINFO_H_INCLUDED
#endif
