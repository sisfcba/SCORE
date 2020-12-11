/*
 *  termios.h   Terminal I/O system types
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 *  Copyright by WATCOM International Corp. 1988-1993.  All rights reserved.
 */
#ifndef _TERMIOS_H_INCLUDED

#define NCCS    40

typedef unsigned short  cc_t;
typedef long            speed_t;
typedef unsigned long   tcflag_t;
#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif
struct termios {
    tcflag_t        c_iflag;    /* Input Modes */
    tcflag_t        c_oflag;    /* Ouput modes */
    tcflag_t        c_cflag;    /* Control Modes */
    tcflag_t        c_lflag;    /* Local Modes */
    cc_t            c_cc[NCCS]; /* Control Characters */
    unsigned short  zero[3];
    unsigned short  c_status;   /* device status */
    unsigned short  c_qflag;    /* QNX Specific flags */
    unsigned short  handle;
    speed_t         c_ispeed;   /* Input Baud rate */
    speed_t         c_ospeed;   /* Output baud rate */
};
#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif
/*
 * Input modes
 */

#define IGNBRK      0x0001
#define BRKINT      0x0002
#define IGNPAR      0x0004
#define PARMRK      0x0008
#define INPCK       0x0010
#define ISTRIP      0x0020
#define INLCR       0x0040
#define IGNCR       0x0080
#define ICRNL       0x0100
#define IXON        0x0400
#define IXOFF       0x1000

#define TC_IPOSIX   (BRKINT|ICRNL|IGNBRK|IGNPAR|INLCR|INPCK|ISTRIP|IXOFF|IXON|PARMRK)

/*
 * Ouput Modes
 */

#define OPOST   0x0001

#define TC_OPOSIX (OPOST)

/*
 * Control Modes
 */

#define IHFLOW  0x0001
#define OHFLOW  0x0002
#define PARSTK  0x0004
#define IIDLE   0x0008

#define CSIZE   0x0030
#define CS5     0x0000
#define CS6     0x0010
#define CS7     0x0020
#define CS8     0x0030
#define CSTOPB  0x0040
#define CREAD   0x0080
#define PARENB  0x0100
#define PARODD  0x0200
#define HUPCL   0x0400
#define CLOCAL  0x0800

#define TC_CPOSIX (CLOCAL|CREAD|CSIZE|CSTOPB|HUPCL|PARENB|PARODD)

/*
 * Local Modes
 */

#define ISIG    0x0001
#define ICANON  0x0002
#define ECHO    0x0008
#define ECHOE   0x0010
#define ECHOK   0x0020
#define ECHONL  0x0040
#define NOFLSH  0x0080
#define TOSTOP  0x0100
#define IEXTEN  0x8000

#define TC_LPOSIX (ECHO|ECHOE|ECHOK|ECHONL|ICANON|IEXTEN|ISIG|NOFLSH|TOSTOP)

/*
 * Special Control Character indices into c_cc[]
 */

#define VINTR   0
#define VQUIT   1
#define VERASE  2
#define VKILL   3
#define VEOF    4
#define VEOL    5
#define VSTART  8
#define VSTOP   9
#define VSUSP   10
#define VDSUSP  11
#define VMIN    16
#define VTIME   17

#define VFWD    18
#define VLOGIN  19
#define VPREFIX 20
#define VSUFFIX 24
#define VLEFT   28
#define VRIGHT  29
#define VUP     30
#define VDOWN   31
#define VINS    32
#define VDEL    33
#define VRUB    34
#define VCAN    35
#define VHOME   36
#define VEND    37
#define VSPARE3 38
#define VSPARE4 39

/*
 * Pre-Defined Baud rates used by cfgetospeed(), etc.
 */

#define B0      0
#define B50     50
#define B75     75
#define B110    110
#define B134    134
#define B150    150
#define B200    200
#define B300    300
#define B600    600
#define B1200   1200
#define B1800   1800
#define B2400   2400
#define B4800   4800
#define B9600   9600
#define B19200  19200
#define EXTA    19200
#define B38400  38400u
#define EXTB    38400u

#define B57600  57600u
#define B76800  76800L
#define B115200 115200L

/*
 * Optional Actions for tcsetattr()
 */

#define TCSANOW     0x0001
#define TCSADRAIN   0x0002
#define TCSAFLUSH   0x0004

/*
 * queue_selectors for tcflush()
 */

#define TCIFLUSH    0x0000
#define TCOFLUSH    0x0001
#define TCIOFLUSH   0x0002

/*
 * Actions for tcflow()
 */

#define TCOOFF      0x0000
#define TCOON       0x0001
#define TCIOFF      0x0002
#define TCION       0x0003

#define TCOOFFHW    0x0004
#define TCOONHW     0x0005
#define TCIOFFHW    0x0006
#define TCIONHW     0x0007

/*
 * QNX device status's (c_status) (read-only)
 */

#define TC_ISFLOW   0x0001
#define TC_OSFLOW   0x0002
#define TC_IHFLOW   0x0004
#define TC_OHFLOW   0x0008

/*
 * Qnx flags (c_qflag)
 */

#define TC_PROTECT_HFLOW    0x0001
#define TC_PROTECT_SFLOW    0x0002
#define TC_WAIT_SFLOW       0x0004
#define TC_NOPGRP           0x0008
#define TC_ECHOI            0x0010
#define TC_IFWD             0x0020
#define TC_PROTECT_IEXTEN   0x0040

/*
 * Miscellaneous
 */

#define _POSIX_VDISABLE     0x00

/*
 *  POSIX 1003.1 Prototypes.
 */
#ifdef __cplusplus
extern "C" {
#endif
extern speed_t cfgetispeed( const struct termios * __termios_p );
extern speed_t cfgetospeed( const struct termios * __termios_p );
extern int     cfsetispeed( struct termios * __termios_p, speed_t __speed );
extern int     cfsetospeed( struct termios * __termios_p, speed_t __speed );
extern int     tcdrain( int __fildes );
extern int     tcdropline( int __fildes, int __duration );
extern int     tcflush( int __fildes, int __queue_selector );
extern int     tcflow( int __fildes, int __action );
extern int     tcgetattr( int __fildes, struct termios * __termios_p );
extern int     tcsetattr( int __fildes, int __opt_act, const struct termios * __termios_p );
extern int     tcsendbreak( int __fildes, int __duration );
#ifdef __cplusplus
};
#endif

#define _TERMIOS_H_INCLUDED

#endif
