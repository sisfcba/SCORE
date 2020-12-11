/*
 *  ser_msg.h   Definitions for the serial driver
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __SER_MSG_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif
#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

/*
 *  Message types
 */

#define _SER_RESET              0x03C0
#define _SER_QUERY              0x03C1

/*
 * Message formats
 */

struct _ser_reset {
    msg_t                   type;
    short int               unit; /* 0..num_ser */
    short int               major;
    short unsigned          zero[3];
    } ;

struct _ser_reset_reply {
    msg_t                   status;
    short unsigned          zero[3];
    } ;

struct _ser_query {
    msg_t                   type;
    short int               unit; /* 0..num_ser */
    short int               major;
    short unsigned          zero[3];
    } ;

struct _ser_query_reply {
    msg_t                   status;
    short unsigned          iobase;
    short unsigned          irq;
    short unsigned          mode;
    short unsigned          slots;      /* Bitmask of possible pcmcia slots */
    short unsigned          slot;       /* Actual slot (1..16) used */
    unsigned long           rx_count;
    unsigned long           tx_count;
    short unsigned          cur_state;
    short unsigned          zero[9];
    } ;

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __SER_MSG_H_INCLUDED
#endif
