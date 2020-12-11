/*
 *  interact.h
 *
 *  Copyright by QNX Software Systems Limited 1994. All rights reserved.
 */

#ifndef _SYS_INTERACT_H_INCLUDED
#define _SYS_INTERACT_H_INCLUDED

#pragma pack(1);

#define _INTERACT_TYPE_POINTER       0x0000          /* pointer packet */
#define _INTERACT_TYPE_KEY           0x0001          /* keyboard packet */
#define _INTERACT_TYPE_FEEDBACK      0x0001          /* keyboard packet */

struct _interact_device {
    unsigned short          type;
    unsigned short          reserved;
};

#define _INTERACT_FEEDBACK_LED       0x00000001      /* LED displays */
#define _INTERACT_FEEDBACK_BELL      0x00000002      /* Freq, vol, dur */
#define _INTERACT_FEEDBACK_INTEGER   0x00000004      /* Integer display */
#define _INTERACT_FEEDBACK_STRING    0x00000008      /* string display */

#pragma pack();

#endif
