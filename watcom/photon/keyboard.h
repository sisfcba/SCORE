/*
 *  keyboard.h
 *
 *  Copyright by QNX Software Systems Limited 1994. All rights reserved.
 */

#ifndef _SYS_KEYBOARD_H_INCLUDED
#define _SYS_KEYBOARD_H_INCLUDED

#ifndef _SYS_INTERACT_H_INCLUDED
#include <photon/interact.h>
#endif

#ifndef _TIME_H_INCLUDED
 #include <time.h>
#endif

#ifndef __KEYCODES_H_INCLUDED
#include <photon/keycodes.h>
#endif

#pragma pack(1);

struct _keyboard_data {
    unsigned long           modifiers;
    unsigned long           flags;
    unsigned long           key_cap;
    unsigned long           key_sym;
    unsigned long           key_scan;
};

struct _keyboard_packet {                   /* start of struct returned from read() */
    struct timespec         time;
    struct _keyboard_data   data;
};

#define _KEYBOARD_MODE_SCAN      0x0000     /* single byte scancodes are returned */
#define _KEYBOARD_MODE_PACKET    0x0001     /* _keyboard_packets are returned */
#define _KEYBOARD_MODE_UNICODE	 0x0002		// unicode (16 bit quantities) are returned
#define _KEYBOARD_MODE_MASK      0x0003
#define _KEYBOARD_MODE_SCREEN	 0x1000		// display screen keyboard

struct _keyboard_ctrl {
    struct _interact_device type;           /* Device type */
    unsigned long           flags;          /* Device type flags */
    unsigned long           mode;           /* Mode of currently read packets */
	unsigned short			rate;
	unsigned short			delay;
	unsigned long			zero[9];
};
#pragma pack();

#endif
