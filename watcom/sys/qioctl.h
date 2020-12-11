/*
 *  qioctl.h    manifests and structures for common qnx_ioctl messages
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __QIOCTL_H_INCLUDED

#ifndef _LIMITS_H_INCLUDED
#   include <limits.h>
#endif

#ifndef __FSYS_H_INCLUDED
#   include <sys/fsys.h>
#endif

#ifndef __SYS_MSG_H_INCLUDED
#   include <sys/sys_msg.h>
#endif

#ifndef __SENDMX_H_INCLUDED
#   include <sys/sendmx.h>
#endif

/*
 * This header includes manifests and structures for common qnx_ioctl messages.
 *
 *  The messages are subdivided into the following ranges:
 *
 *      Quantum reserved        0x000 - 0x0ff
 *      common (all io servers) 0x101 - 0x1ff
 *      fsys                    0x201 - 0x2ff
 *      dev                     0x301 - 0x3ff
 *      Quantum reserved        0x400 - 0xfff
 */

enum __qioctl_type {
    QCTL_LOW_RSVD = 0,
    QCTL_LOW_RSVD_MAX = 0xff,

    QCTL_COMMON = 0x100,
    QCTL_COMM_GET_CAP,
    QCTL_COMM_GET_VER,
    QCTL_COMMON_MAX = 0x1ff,

    QCTL_FSYS = 0x200,
    QCTL_GET_DISK_PARMS,
    QCTL_SET_DISK_PARMS,
    QCTL_GET_PHYS_PARMS,
    QCTL_SET_PHYS_PARMS,
    QCTL_FMT_TRK,
    QCTL_FMT_DRIVE,
    QCTL_RAW_CMD,
    QCTL_ELEVEL,
    QCTL_RESET,
    QCTL_GET_LAST_ERR,
    QCTL_LOCK_PARMS,
    QCTL_UNLOCK_PARMS,
    QCTL_FSYS_MAX = 0x2ff,

    QCTL_DEV = 0x300,
    QCTL_DEV_OPEN,
    QCTL_DEV_CLOSE,
    QCTL_DEV_CTL,
    QCTL_DEV_MAX = 0x3ff,

    QCTL_MAX_RESERVED = 0xfff,          /*  user available go here... */
    };

/*
 * Device specific IOCTL's follow the following conventions:
 *
 * The ioctl type is QCTL_DEV_CTL  (0x0303)
 *
 * The send buffer consists of 8 bytes organized as two longs (bits, mask)
 * The returned buffer consists of 4 bytes representing a long (oldbits) 
 *
 * The ioctl returns the state of the device control bits as they
 * were found BEFORE the call was made (oldbits). The device control bits
 * are then modified using the rule:
 *   newbits = (oldbits & ~mask) | (bits & mask)
 *
 * The meaning of these 32 device control bits varies from device to
 * device as follows: (note: ':' means R/W, '=' means R/O)
 *
 * SERIAL devices   (all Dev.ser versions)
 * 0 : DTR           8 = Data Bits 0  16 - reserved     24 - reserved     
 * 1 : RTS           9 = Data Bits 1  17 - reserved     25 - reserved     
 * 2 = Out 1        10 = Stop Bits    18 - reserved     26 - reserved     
 * 3 = Int Enable   11 = Par Enable   19 - reserved     27 - reserved     
 * 4 = Loop         12 = Par Even     20 = CTS          28 - reserved     
 * 5 - reserved     13 = Par Stick    21 = DSR          29 - reserved     
 * 6 - reserved     14 : Break        22 = RI           30 - reserved     
 * 7 - reserved     15 = 0            23 = CD           31 - reserved     
 *
 * PARALLEL devices (all Dev.par versions)
 * 0 = reserved      8 : Strobe       16 - reserved     24 - reserved     
 * 1 = reserved      9 : Auto LF      17 - reserved     25 - reserved     
 * 2 = -IRQ Status  10 : -INIT        18 - reserved     26 - reserved     
 * 3 = -ERROR       11 : Select       19 - reserved     27 - reserved     
 * 4 = Select       12 : IRQ Enable   20 - reserved     28 - reserved     
 * 5 = PE           13 : Direction    21 - reserved     29 - reserved     
 * 6 = -ACK         14 - reserved     22 - reserved     30 - reserved     
 * 7 = -BUSY        15 - reserved     23 - reserved     31 - reserved     
 *
 * CONSOLE devices  (Dev.con version 4.01+)
 * 0 - ScrLock       8 - ScrLockLock  16 - Shift        24 - App Cursor (ANSI)
 * 1 - NumLock       9 - NumLockLock  17 - Ctrl         25 - App Keypad (ANSI)
 * 2 - CapsLock     10 - CapsLockLock 18 - Alt          26 - RUB => DEL (ANSI)
 * 3 - reserved     11 - reserved     19 - Extended     27 - Use 8-bit (ANSI)
 * 4 - reserved     12 - reserved     20 - reserved     28 - reserved
 * 5 - reserved     13 - reserved     21 - reserved     29 - reserved
 * 6 - reserved     14 - reserved     22 - reserved     30 - reserved
 * 7 - reserved     15 - reserved     23 - reserved     31 - reserved
 */

/*
 *  Common Structure Definitions
 *
 */

/*
 *  ioctl = QCTL_COMM_GET_CAP : get the qnx_ioctl capability list.
 */
struct  _qio_getcap {
    short   int     start_num;
    };
/*
 *  response to QCTL_COMM_GET_CAP: bit vector of available qnx_ioclt funs.
 */
struct  _qio_cap {
    short   int     len;
    unsigned char qctl_vect[(CHAR_MAX+1)/CHAR_BIT];
    };

#ifdef __cplusplus
extern "C" {
#endif
extern int qnx_ioctl(int __fd, unsigned __request,
        const void * __sbuf, unsigned __sbytes,
        void * __rbuf, unsigned rbytes);
extern int qnx_ioctlmx(int fd, unsigned request, int sparts, int rparts,
                const struct _mxfer_entry *sx, const struct _mxfer_entry *rx);
#ifdef __cplusplus
};
#endif


/*
 *    Structure Definitions
 *    for floppy drives.
 */
    
/*    sub-types
 */
#define FD_360        1            /*    360Kb drive */
#define FD_1200       2            /*    1.2Mb drive */
#define FD_720        3            /*    720Kb drive */
#define FD_1440       4            /*    1.44Mb drive */
#define FD_2880       6            /*    2.88Mb drive */
/*
 *    data sampling rates.
 */

#define FD_500KBS    0             /*    500 000 bits per second */
#define FD_300KBS    1             /*    300 000 bits per second */
#define FD_250KBS    2             /*    250 000 bits per second */

enum {
    FD_UNKNOWN = -1,
    FD_OK      = 0,
    FD_WRITE_PROTECT,
    FD_NOT_READY,
    FD_DATA_ERROR,
    FD_NOT_FOUND,
    FD_DMA_FAIL,
    };
    

struct    fd_parms {
        short    type;             /*    device type : _FLOPPY, _HARD, ... */
        short    subtype;          /*    subtype device specific              */
        short    heads;
        short    tracks;
        short    sectors;
        short    blocksize;        /*    bytes per atomic block            */
        long    blocks;
    };

struct    fd_phys_parms {
        short    dma_channel;
        short    read_gap;
        short    step_rate;
        short    shift_step;
        short    pll_clock;
        short    head_load_time;
        short    head_unload_time;
        short    format_gap;
    short    driveno;
    };
    
struct    fd_lock_parm {
        short    dtype;
    };    
    
#define FD_MAX_SECTOR   256
struct    fd_fmt_trk   {
        short    head;
        short    trackno;
        short    nsector;
        short    filler;
        short    sectsize;
        unsigned char xtab[FD_MAX_SECTOR]; /*    up to n sector    */
    };

struct  fd_req_err {
        short   driveno;
    };

struct  fd_last_err {               /* return from fd_fmt_trk OR fd_req_err */
        short    result;        
        short   head,
                track,
                sector;
    };


/*
**  QNX 4.0 - qic 02 tape driver defines
*/
#define     T_SELECT            0x01        /* qic 02 Standard Commands */
#define     T_BOT               0x21
#define     T_ERASE             0x22
#define     T_RETENSION         0x24
#define     T_WRITE             0x40
#define     T_WRITE_FM          0x60
#define     T_READ              0x80
#define     T_SEEK_FM           0xA0
#define     T_READ_STATUS       0xC0

#define     T_WRITE_FM_WRITE    0x62        /* Some Vendors Support */
#define     T_SKIP_FWD_A_BLOCK  0x81
#define     T_SKIP_BWD_A_BLOCK  0x89
#define     T_SEEK_EOD          0xA3
#define     T_SEEK_N_FM         0xB0
#define     T_SELF_TEST_1       0xC2
#define     T_SELF_TEST_2       0xCA

#define     T_READ_RESID_COUNT  0xC8        /* Extension provided by Archive */
#define     T_READ_BLOCK_NO     0xAE
#define     T_SEEK_BLOCK_N      0xAD

#define     T_LAST_ERROR        0xFFFC      /* Used as a field support tool */                                                                                                                                                                                
                                                                                                                                                                                                                                                              
 
#define     T_RESET             0xFFFD
#define     T_VERSION           0xFFFE
#define     T_DEBUG             0xFFFF


/*
**  qic 02 exception status bytes
**
**  Status Byte 0
*/
#define     E_FIL               0x01        /* File mark detected */
#define     E_BNL               0x02        /* Block not located */
#define     E_UDE               0x04        /* Unrecoverable data error */
#define     E_EOM               0x08        /* End of medium */
#define     E_WRP               0x10        /* Write protect cartridge */
#define     E_DFF               0x20        /* Device fault or SELF TEST failed */
#define     E_CNI               0x40        /* Cartridge not in place */
#define     E_ST0               0x80        /* Flags set in this byte */


/*
**  Status Byte 1
*/
#define     E_POR               0x01        /* Power on/RESET occurred */
#define     E_EOD               0x02        /* End of recorded data */
#define     E_PAR               0x04        /* Bus parity error */
#define     E_BOM               0x08        /* Beginning of medium */
#define     E_MBD               0x10        /* Marginal block detected */
#define     E_NDT               0x20        /* No data detected */
#define     E_ILL               0x40        /* Illegal command */
#define     E_ST1               0x80        /* Flags set in this byte */


#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

typedef struct
{   unsigned short          Command;
    short                   RetVal;

/*****************************************************************/
}   QIC02_HEADER_STRUCT;
/*****************************************************************/

typedef struct
{   unsigned char           Data[ _BLOCK_SIZE - sizeof (QIC02_HEADER_STRUCT) ];

/*****************************************************************/
}   QIC02_GENERIC_STRUCT;
/*****************************************************************/

typedef struct
{   unsigned char           Byte0;
    unsigned char           Byte1;
    unsigned char           ErrorCounth;
    unsigned char           ErrorCountl;
    unsigned char           UnderRunCounth;
    unsigned char           UnderRunCountl;

/*****************************************************************/
}   QIC02_STATUS_STRUCT;
/*****************************************************************/

typedef struct
{   short               Again;
    unsigned char       Msg[ _BLOCK_SIZE - sizeof (QIC02_HEADER_STRUCT) - sizeof (int) ];

/*****************************************************************/
}   QIC02_LOG_STRUCT;
/*****************************************************************/

typedef struct
{   char                    ErrorString[ _BLOCK_SIZE - sizeof (QIC02_HEADER_STRUCT) ];

/*****************************************************************/
}   QIC02_LAST_ERROR_STRUCT;
/*****************************************************************/

typedef struct
{   QIC02_HEADER_STRUCT                 Header;

    union
    {   QIC02_GENERIC_STRUCT            Generic;
        QIC02_LOG_STRUCT                Log;
        QIC02_STATUS_STRUCT             Status;
        struct _sysmsg_version_reply    Version;
        QIC02_LAST_ERROR_STRUCT         Error;

    }   Body;

/*****************************************************************/
}   QIC02_MSG_STRUCT;
/*****************************************************************/


#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __QIOCTL_H_INCLUDED
#endif
