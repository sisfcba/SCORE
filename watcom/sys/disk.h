/*
 *  disk.h      Non-portable file system definitions
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __DISK_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

#define _DRIVER_NAME_LEN   12

#ifndef _MAX_BLOCK_OPS
#define _MAX_BLOCK_OPS  127 /*  Largest atomic block_read or block_write    */
#endif

/*
 *  Disk types
 *  Types 10 up are available for user written drivers
 *  that don't exactly fit any of the standard types,
 *  however they are assumed to be fixed (non-removable) drive
 *  and cached blocks will not timeout.
 *  Types below 10 are reserved (even if not explicitly)
 *  for known types or expansion.
 *  If you have a removable disk which can be locked in the drive,
 *  call it _REMOVABLE (type 4).
 *  If the removable disk can be removed at any time, call it a _FLOPPY.
 */
#define _UNMOUNTED  0
#define _FLOPPY     1   /*  Cache times out after 2 seconds of inactivity   */
#define _HARD       2
#define _RAMDISK    3   /*  Built-in, not via a driver                      */
#define _REMOVABLE  4   /*  A removable hard disk, e.g. Iomega Bernoulli    */
#define _TAPE       5   /*  Streaming tape: it has no known size, so all    */
                        /*  writes are synchronous.  I/O errors are assumed */
                        /*  to be the end-of-tape.  Seeking is an error.    */
#define _CDROM      6
#define _WORM       7
#define _UNKNOWN    8   /*  catchall for things we don't know               */
#define _PRINTER    9   /*  SCSI (?) printer                                */
#define _COMMS      10  /*  SCSI (?) communications device                  */
#define _PROCESSOR  11  /*  SCSI (?) processor device                       */
#define _SCANNER    12  /*  SCSI (?) scanner                                */
#define _MEDIA_CHG  13  /*  SCSI (?) media changer                          */
#define _OPTICAL    14  /*  SCSI (?) optical memory device                  */


/*
 *  Info about a QNX drive.
 *
 *  NOTE:  It is possible that cylinders, heads and track_sectors may be 0,
 *          in which case only disk_sectors describes the physical disk size.
 */
struct _disk_entry {
    unsigned long   blk_offset,
                    num_sectors, /* Num sectors in logical drive (partition) */
                    disk_sectors;/* Num sectors on physical disk    */
    unsigned short  cylinders,
                    heads,
                    track_sectors;
    unsigned char   disk_type,
                    disk_drv;           /*  Drive number as known to driver */
    long            reserved[3];
    unsigned char   driver_name[_DRIVER_NAME_LEN];
    } ;


#ifdef __cplusplus
extern "C" {
#endif
extern int disk_get_entry( int __fd, struct _disk_entry *__d_bfr );
extern int disk_space( int __fd, long *__free_blocks, long *__tot_blocks );
extern int block_read( int __fd, long __block, unsigned __nblock, void *__buf );
extern int block_write( int __fd, long __block, unsigned __nblock,
                     const void *__buf );
#ifdef __cplusplus
};
#endif

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __DISK_H_INCLUDED
#endif
