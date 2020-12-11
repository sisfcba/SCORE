#ifndef _SYS_CDROM_H_INCLUDED
#define _SYS_CDROM_H_INCLUDED

#ifndef _IOCTL_H_INCLUDED
 #include <sys/ioctl.h>
#endif

#pragma pack(1);

/* 
 * CDROM io controls type definitions
 */
struct cdrom_msf {
    unsigned char   cdmsf_min0;     /* starting minute */
    unsigned char   cdmsf_sec0;     /* starting second */
    unsigned char   cdmsf_frame0;   /* starting frame  */
    unsigned char   cdmsf_min1;     /* ending minute   */
    unsigned char   cdmsf_sec1;     /* ending second   */
    unsigned char   cdmsf_frame1;   /* ending frame    */
};

struct cdrom_ti {
    unsigned char   cdti_trk0;      /* starting track */
    unsigned char   cdti_ind0;      /* starting index */
    unsigned char   cdti_trk1;      /* ending track   */
    unsigned char   cdti_ind1;      /* ending index   */
};

struct cdrom_subchnl {
   unsigned char   cdsc_format;
   unsigned char   cdsc_audiostatus;       
   unsigned char   cdsc_adr:4;
   unsigned char   cdsc_ctrl:4;
   unsigned char   cdsc_trk;
   unsigned char   cdsc_ind;
   union {
       struct {
           unsigned char   minute;
           unsigned char   second;
           unsigned char   frame;
       } msf;
       long         lba;
   } cdsc_absaddr;
   union {
       struct {
           unsigned char   minute;
           unsigned char   second;
           unsigned char   frame;
       } msf;
       long         lba;
   } cdsc_reladdr;
};

/*
 * Definition for audio status returned from Read Sub-channel
 */
#define CDROM_AUDIO_INVALID     0x00    /* audio status not supported */
#define CDROM_AUDIO_PLAY        0x11    /* audio play operation in progress */
#define CDROM_AUDIO_PAUSED      0x12    /* audio play operation paused */
#define CDROM_AUDIO_COMPLETED   0x13    /* audio play successfully completed */
#define CDROM_AUDIO_ERROR       0x14    /* audio play stopped due to error */
#define CDROM_AUDIO_NO_STATUS   0x15    /* no current audio status to return */
        
struct cdrom_tochdr {
    unsigned char   cdth_trk0;      /* starting track */
    unsigned char   cdth_trk1;      /* ending track */
};

struct cdrom_tocentry {
    unsigned char   cdte_track;
    unsigned char   cdte_adr:4;
    unsigned char   cdte_ctrl:4;
    unsigned char   cdte_format;
    union {
        struct {
            unsigned char   minute;
            unsigned char   second;
            unsigned char   frame;
        } msf;
        long        lba;
    } cdte_addr;
    unsigned char   cdte_datamode;
};

/*
 * CDROM address format definition, for use with struct cdrom_tocentry 
 */
#define CDROM_LBA       0x01
#define CDROM_MSF       0x02

/*
 * Bitmask for CD-ROM data track in the cdte_ctrl field
 * A track is either data or audio.
 */
#define CDROM_DATA_TRACK        0x04

/*
 * For CDROMREADTOCENTRY, set the cdte_track to CDROM_LEADOUT to get
 * the information for the leadout track.
 */
#define CDROM_LEADOUT   0xAA

/* definition of audio volume control structure */
struct cdrom_volctrl {
    unsigned char   channel0;
    unsigned char   channel1;
    unsigned char   channel2;
    unsigned char   channel3;
};
        
struct cdrom_read {
    long    cdread_lba;
    void    *cdread_bufaddr;
    long    cdread_buflen;
};

struct cdrom_discinfo {
    short   changed_count; 
	short	flags;
    short   reserved[14];
};
#define CDROM_DISCINFO_NODISC	0x0001		/* There is no disc in the drive */

#define CDROM_MODE1_SIZE        2048
#define CDROM_MODE2_SIZE        2336

/*
 * CDROM io control commands 
 */
#define CDROMPAUSE              _IO('c', 10)
#define CDROMRESUME             _IO('c', 11)
#define CDROMPLAYMSF            _IOW('c', 12, struct cdrom_msf)
#define CDROMPLAYTRKIND         _IOW('c', 13, struct cdrom_ti)
#define CDROMREADTOCHDR         _IOR('c', 103, struct cdrom_tochdr)
#define CDROMREADTOCENTRY       _IOWR('c', 104, struct cdrom_tocentry)
#define CDROMSTOP               _IO('c', 105)
#define CDROMSTART              _IO('c', 106)
#define CDROMEJECT              _IO('c', 107)
#define CDROMVOLCTRL            _IOW('c', 14, struct cdrom_volctrl)
#define CDROMSUBCHNL            _IOWR('c', 108, struct cdrom_subchnl)
#define CDROMREADMODE2          _IOW('c', 110, struct cdrom_read)
#define CDROMREADMODE1          _IOW('c', 111, struct cdrom_read)
#define CDROMDISCINFO           _IOR('c', 150, struct cdrom_discinfo)
#define CDROMREADVOL            _IOR('c', 151, struct cdrom_volctrl)
#define CDROMLOAD               _IO('c', 152)

#define MSF2LBA(_min, _sec, _frame)     ((_min * 60 + _sec) * 75 + _frame - 150)
#define LBA2MIN(_lba)                   (((_lba + 150) / 75) / 60)
#define LBA2SEC(_lba)                   (((_lba + 150) / 75) % 60)
#define LBA2FRAME(_lba)                 ((_lba + 150) % 75)

/*
 * The following are for the Rock Ridge Interchange Protocol
 */

#define CD_MAXDMAP              50
#define CD_SETDMAP              1
#define CD_UNSETDMAP            2

#ifdef __cplusplus
extern "C" {
#endif

int cd_suf(char *path, int fsec, char signature[2], int index, char *buf, int buflen);
int cd_setdevmap(char *path, int cmd, int *new_major, int *new_minor);
int cd_getdevmap(char *path, int pathlen, int index, int *new_major, int *new_minor);

#ifdef __cplusplus
};
#endif

#pragma pack();

#endif
