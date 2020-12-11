#ifndef _TERMIO_H_INCLUDED
#define _TERMIO_H_INCLUDED

#ifndef _TERMIOS_H_INCLUDED
#include <termios.h>

#define ONLCR           0               /* not supported */

#define TANDEM          0x00000001      /* send stopc on out q full */
#define CBREAK          0x00000002      /* half-cooked mode */
#define LCASE           0x00000004      /* simulate lower case */
//      ECHO            0x00000008      /* echo input */
#define CRMOD           0x00000010      /* map \r to \r\n on output */
#define RAW             0x00000020      /* no i/o processing */
#define ODDP            0x00000040      /* get/send odd parity */
#define EVENP           0x00000080      /* get/send even parity */
#define ANYP            0x000000c0      /* get any parity/send none */
#define NLDELAY         0x00000300      /* \n delay */
#define     NL0         0x00000000
#define     NL1         0x00000100      /* tty 37 */
#define     NL2         0x00000200      /* vt05 */
#define     NL3         0x00000300
#define TBDELAY         0x00000c00      /* horizontal tab delay */
#define     TAB0        0x00000000
#define     TAB1        0x00000400      /* tty 37 */
#define     TAB2        0x00000800
#define XTABS           0x00000c00      /* expand tabs on output */
#define CRDELAY         0x00003000      /* \r delay */
#define     CR0         0x00000000
#define     CR1         0x00001000      /* tn 300 */
#define     CR2         0x00002000      /* tty 37 */
#define     CR3         0x00003000      /* concept 100 */
#define VTDELAY         0x00004000      /* vertical tab delay */
#define     FF0         0x00000000
#define     FF1         0x00004000      /* tty 37 */
#define BSDELAY         0x00008000      /* \b delay */
#define     BS0         0x00000000
#define     BS1         0x00008000
#define ALLDELAY        (NLDELAY|TBDELAY|CRDELAY|VTDELAY|BSDELAY)

#define B0               0
#undef  B50
#define B50              1
#undef  B75
#define B75              2
#undef  B110
#define B110             3
#undef  B134
#define B134             4
#undef  B150
#define B150             5
#undef  B200
#define B200             6
#undef  B300
#define B300             7
#undef  B600
#define B600             8
#undef  B1200
#define B1200            9
#undef  B1800
#define B1800           10
#undef  B2400
#define B2400           11
#undef  B4800
#define B4800           12
#undef  B9600
#define B9600           13
#undef  B19200
#define B19200          14
#undef  B38400
#define B38400          15


#undef  EXTA
#define EXTA            14
#undef  EXTB
#define EXTB            15

#undef  CBAUD
#define CBAUD           15              /* baud rate mask */

/*
 * Control characters
 */
#define VINTR           0               /* interrupt */
#define VQUIT           1               /* quit */
#define VERASE          2               /* erase */
#define VKILL           3               /* line kill */
#define VEOF            4               /* end of file */
#define VEOL            5               /* end of line */
#define VEOL2           6               /* alternate end of line */
#define VSWTCH          7               /* switch */

#define VMIN            16              /* minimum read request */
#define VTIME           17              /* read timeout */

#undef  NCC
#define NCC             18              /* number of control characters */
#else
#error termio/termios incompatibility
#endif

#ifndef _IOCTL_H_INCLUDED
#include <ioctl.h>
#endif

/*
 * TCGETA/TCSETA structure
 */
#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif
struct termio {
     unsigned short     c_iflag;        /* input modes */
     unsigned short     c_oflag;        /* output modes */
     unsigned short     c_cflag;        /* control modes */
     unsigned short     c_lflag;        /* line discipline modes */
     char               c_line;         /* line discipline */
     unsigned short     c_cc[NCC];      /* control chars */
};
#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif
#endif
