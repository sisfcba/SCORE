/*
 * This will be for SCSI Ioctl commands
 */

#ifndef _USCSI_H_INCLUDED
#define _USCSI_H_INCLUDED

#ifndef _IOCTL_H_INCLUDED
 #include <ioctl.h>
#endif

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif
struct uscsi_cmd {
    caddr_t         uscsi_cdb;
    short           uscsi_cdblen;
    caddr_t         uscsi_bufaddr;
    unsigned short  uscsi_buflen;
    unsigned short  uscsi_flags;
    unsigned char   uscsi_status;
};

#define USCSI_SILENT        0x0001  /* no error messages */
#define USCSI_DIAGNOSE      0x0002  /* fail if any error occurs */
#define USCSI_ISOLATE       0x0004  /* isolate from normal commands */
#define USCSI_READ          0x0008  /* get data from device. */
#define USCSI_DIS_AUTOSENSE 0x0010  /* get data from device. */
#define USCSI_WRITE        ~USCSI_READ /* use to zero the READ bit in uscsi_flags */
#define USCSI_NOFLUSH       0x8000  /* Cache flushing before sending the */
                                    /* SCSI command is disabled */

#define USCSI_STATUS_GOOD           0x00
#define USCSI_STATUS_CHECK          0x02
#define USCSI_STATUS_MET            0x04
#define USCSI_STATUS_BUSY           0x08
#define USCSI_STATUS_INTERMEDIATE       0x10
#define USCSI_STATUS_RESERVATION_CONFLICT   \
    (USCSI_STATUS_INTERMEDIATE | USCSI_STATUS_BUSY)

/*
 *  Sense Keys (structure "sense", field "sd_sense")
 */
#define USCSI_SK_MASK           0x0F    /*  mask to sd_sense field for key */
#define USCSI_SK_NO_SENSE       0       /*  No sense data (no error) */
#define USCSI_SK_RECOVERED      1       /*  Recovered error */
#define USCSI_SK_NOT_RDY        2       /*  Device not ready */
#define USCSI_SK_MEDIUM         3       /*  Medium error */
#define USCSI_SK_HARDWARE       4       /*  Hardware error */
#define USCSI_SK_ILLEGAL        5       /*  Illegal Request (bad command) */
#define USCSI_SK_UNIT_ATN       6       /*  Unit Attention */
#define USCSI_SK_DATA_PROT      7       /*  Data Protect */
#define USCSI_SK_BLNK_CHK       8       /*  Blank Check */
#define USCSI_SK_VENDOR         9       /*  Vendor Specific */
#define USCSI_SK_CPY_ABORT      10      /*  Copy Aborted */
#define USCSI_SK_CMD_ABORT      11      /*  Aborted Command */
#define USCSI_SK_EQUAL          12      /*  Equal */
#define USCSI_SK_VOL_OFL        13      /*  Volume Overflow */
#define USCSI_SK_MISCMP         14      /*  Miscompare */
#define USCSI_SK_RESERVED       15      /*  Reserved */

/*
 *  Definition of the SCSI-2 Sense Data Structure
 *  (similar to SCSI-1 extended sense data)
 *
 *  Note: The field "sd_err" has the following format:
 *        bit    7  - Address valid bit
 *        bits 6-4  - Error class
 *        bits 3-0  - Error code 
 *
 *  Error classes 0-6 are vendor unique and also indicate that the
 *  sense data is in _nonextended_ format. (i.e. not usually used)
 *      struct uscsi_nonextended_sense {
 *          char    sd_err;
 *          long    sd_block_address;
 *      };
 *
 *  An error class of 7 and an error code of 0 (70H) indicate SCSI-1
 *  extended sense data format (or SCSI-2 sense data format).
 *
 *  An error class of 7 and an error code of 1 (71H) indicate SCSI-2
 *  deferred errors.
 *
 *  Error codes 72H to 7EH are reserved and error code 7FH indicates
 *  a vendor-specific sense data format.
 *
 */
struct uscsi_sense {
    char    sd_err;         /* Info Valid flag, Error Class and Error Code */
    char    sd_seg;         /* Segment number */
    char    sd_sense;       /* Sense key & Flags */
    long    sd_info;        /* Information */
    char    sd_asl;         /* Additional Sense Length */
    long    sd_csinfo;      /* Command-Specific Information */
    char    sd_asc;         /* Additional Sense Code */
    char    sd_ascq;        /* Additional Sense Code Qualifier */
    char    sd_fruc;        /* Field Replaceable Unit Code */
    char    sd_sks_flags;   /* Sense Key Specific Flags */
    short   sd_sks_data;    /* Sense Key Specific Data */
    char    sd_asb[2];      /* Additional Sense chars */
};

struct uscsi_info {
    short   path;           /* Path it identify the host bus adaptor */
    short   target;         /* Target id of the SCSI device */ 
    short   lun;            /* Logical unit number of the SCSI device */
    short   peripheral;     /* SCSI peripheral type */
    short   zero[12];
};
#ifdef __cplusplus
}
#endif

#define USCSICMD        _IOWR('u', 1, struct uscsi_cmd)
#define USCSISENSE      _IOR('u', 150, struct uscsi_sense)
#define USCSIINFO       _IOR('u', 151, struct uscsi_info)

#endif
