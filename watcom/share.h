/*
 *  share.h     Define file sharing modes for sopen()
 *
 *  Copyright by WATCOM International Corp. 1988-1996.  All rights reserved.
 */

#define SH_COMPAT   0x00    /* compatibility mode   */
#define SH_DENYRW   0x10    /* deny read/write mode */
#define SH_DENYWR   0x20    /* deny write mode      */
#define SH_DENYRD   0x30    /* deny read mode       */
#define SH_DENYNO   0x40    /* deny none mode       */

#define SH_MASK     0x70    /* mask for standard share modes    */

#define SH_DOS      0x01    /* DOS-like interpretation of open, locks, etc. */
