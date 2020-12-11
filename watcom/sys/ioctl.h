/*-
 * Copyright (c) 1982, 1986, 1990 The Regents of the University of California.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *      This product includes software developed by the University of
 *      California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *      @(#)ioctl.h     7.19 (Berkeley) 6/26/91
 */

#ifndef _IOCTL_H_INCLUDED
#define _IOCTL_H_INCLUDED

/*
 * Window/terminal size structure.  This information is stored by the kernel
 * in order to provide a consistent interface, but is not used by the kernel.
 */
#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif
struct winsize {
    unsigned short      ws_row;         /* rows, in characters */
    unsigned short      ws_col;         /* columns, in characters */
    unsigned short      ws_xpixel;      /* horizontal size, pixels */
    unsigned short      ws_ypixel;      /* vertical size, pixels */
};

/*
 * Pun for SUN.
 */
struct ttysize {
    unsigned short      ts_lines;
    unsigned short      ts_cols;
    unsigned short      ts_xxx;
    unsigned short      ts_yyy;
};
#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define TIOCGSIZE       TIOCGWINSZ
#define TIOCSSIZE       TIOCSWINSZ

/*
 * Ioctl's have the command encoded in the lower word, and the size of
 * any in or out parameters in the upper word.  The high 3 bits of the
 * upper word are used to encode the in/out status of the parameter.
 */
#define IOCPARM_MASK    0x1fff          /* parameter length, at most 13 bits */
#define IOCPARM_LEN(x)  (((x) >> 16) & IOCPARM_MASK)
#define IOCBASECMD(x)   ((x) & ~IOCPARM_MASK)
#define IOCGROUP(x)     (((short)(x)) >> 8)

#define IOCPARM_MAX     NBPG            /* max size of ioctl, mult. of NBPG */
#define IOC_VOID        0x20000000L     /* no parameters */
#define IOC_OUT         0x40000000L     /* copy out parameters */
#define IOC_IN          0x80000000L     /* copy in parameters */
#define IOC_INOUT       (IOC_IN|IOC_OUT)
#define IOC_DIRMASK     0xe0000000L     /* mask for IN/OUT/VOID */

#define _IOC(inout,group,num,len) \
        (inout | (((long)len & IOCPARM_MASK) << 16) | ((group) << 8) | (num))
#define _IO(g,n)        _IOC(IOC_VOID,  (g), (n), 0)
#define _IOR(g,n,t)     _IOC(IOC_OUT,   (g), (n), sizeof(t))
#define _IOW(g,n,t)     _IOC(IOC_IN,    (g), (n), sizeof(t))
#define _IOWR(g,n,t)    _IOC(IOC_INOUT, (g), (n), sizeof(t))

#define TCGETA          _IOR('T', 1, struct termio)
#define TCSETA          _IOW('T', 2, struct termio)
#define TCSETAW         _IOW('T', 3, struct termio)
#define TCSETAF         _IOW('T', 4, struct termio)
#define TCSBRK          _IO('T',  5)
#define TCXONC          _IO('T',  6)
#define TCFLSH          _IO('T',  7)
#define TCGETS          _IOR('T', 8, struct termios)
#define TCSETS          _IOW('T', 9, struct termios)
#define TCSETSW         _IOW('T', 10, struct termios)
#define TCSETSF         _IOW('T', 11, struct termios)

#define TIOCHPCL        _IO('t',  2)                    /* hang up on last close */
#define TIOCGETP        _IOR('t', 8, struct sgttyb)     /* get parameters -- gtty */
#define TIOCSETP        _IOW('t', 9, struct sgttyb)     /* set parameters -- stty */
#define TIOCSETN        _IOW('t',10, struct sgttyb)     /* as above, but no flushtty*/

#define TIOCSINUSE      TIOCEXCL

#define TIOCEXCL        _IO('t', 13)                    /* set exclusive use of tty */
#define TIOCNXCL        _IO('t', 14)                    /* reset exclusive use of tty */
                                                        /* 15 unused */
#define TIOCFLUSH       _IOW('t', 16, short)            /* flush buffers */
#define TIOCSETC        _IOW('t', 17, struct tchars)    /* set special characters */
#define TIOCGETC        _IOR('t', 18, struct tchars)    /* get special characters */
#define TIOCGETA        _IOR('t', 19, struct termios)   /* get termios struct */
#define TIOCSETA        _IOW('t', 20, struct termios)   /* set termios struct */
#define TIOCSETAW       _IOW('t', 21, struct termios)   /* drain output, set */
#define TIOCSETAF       _IOW('t', 22, struct termios)   /* drn out, fls in, set */
//      TIOCGETD        _IOR('t', 26, short)            /* get line discipline */
//      TIOCSETD        _IOW('t', 27, short)            /* set line discipline */
#define TIOCDRAIN       _IO('t',  94)                   /* wait till output drained */
//      TIOCSIG         _IO('t',  95)                   /* pty: generate signal */
//      TIOCEXT         _IOW('t', 96, short)            /* pty: external processing */
#define TIOCSCTTY       _IO('t',  97)                   /* become controlling tty */
//      TIOCCONS        _IOW('t', 98, short)            /* become virtual console */
//      TIOCUCNTL       _IOW('t', 102, short)           /* pty: set/clr usr cntl mode */
#define TIOCSWINSZ      _IOW('t', 103, struct winsize)  /* set window size */
#define TIOCGWINSZ      _IOR('t', 104, struct winsize)  /* get window size */
//      TIOCREMOTE      _IOW('t', 105, short)           /* remote input editing */
#define TIOCMGET        _IOR('t', 106, short)           /* get all modem bits */
#define TIOCMBIC        _IOW('t', 107, short)           /* bic modem bits */
#define TIOCMBIS        _IOW('t', 108, short)           /* bis modem bits */
#define TIOCMSET        _IOW('t', 109, short)           /* set all modem bits */
#define TIOCSTART       _IO('t',  110)                  /* start output, like ^Q */
#define TIOCSTOP        _IO('t',  111)                  /* stop output, like ^S */
#define TIOCPKT         _IOW('t', 112, short)           /* pty: set/clear packet mode */
#define         TIOCPKT_DATA            0x00            /* data packet */
#define         TIOCPKT_FLUSHREAD       0x01            /* flush packet */
#define         TIOCPKT_FLUSHWRITE      0x02            /* flush packet */
#define         TIOCPKT_STOP            0x04            /* stop output */
#define         TIOCPKT_START           0x08            /* start output */
#define         TIOCPKT_NOSTOP          0x10            /* no more ^S, ^Q */
#define         TIOCPKT_DOSTOP          0x20            /* now do ^S ^Q */
#define         TIOCPKT_IOCTL           0x40            /* state change of pty driver */
#define TIOCNOTTY       _IO('t', 113)                   /* void tty association */
#define TIOCSTI         _IOW('t', 114, char)            /* simulate terminal input */
#define TIOCOUTQ        _IOR('t', 115, short)           /* output queue size */
#define TIOCGLTC        _IOR('t', 116, struct ltchars)  /* get local special chars*/
#define TIOCSLTC        _IOW('t', 117, struct ltchars)  /* set local special chars*/
#define TIOCSPGRP       _IOW('t', 118, short)           /* set pgrp of tty */
#define TIOCGPGRP       _IOR('t', 119, short)           /* get pgrp of tty */
#define TIOCCDTR        _IO('t', 120)                   /* clear data terminal ready */
#define TIOCSDTR        _IO('t', 121)                   /* set data terminal ready */
#define TIOCCBRK        _IO('t', 122)                   /* clear break bit */
#define TIOCSBRK        _IO('t', 123)                   /* set break bit */
#define TIOCLGET        _IOR('t', 124, short)           /* get local modes */
#define TIOCLSET        _IOW('t', 125, short)           /* set entire local mode word */

#define TIOCSETPGRP     _IOW('t', 130, short)           /* set pgrp of tty (posix) */
#define TIOCGETPGRP     _IOR('t', 131, short)           /* get pgrp of tty (posix) */

#define         UIOCCMD(n)      _IO('u', n)             /* usr cntl op "n" */

#define FIOCLEX         _IO('f', 1)                     /* set close on exec on fd */
#define FIONCLEX        _IO('f', 2)                     /* remove close on exec */
#define FIOGETOWN       _IOR('f', 123, short)           /* get owner */
#define FIOSETOWN       _IOW('f', 124, short)           /* set owner */
#define FIOASYNC        _IOW('f', 125, short)           /* set/clear async i/o */
#define FIONBIO         _IOW('f', 126, short)           /* set/clear non-blocking i/o */
#define FIONREAD        _IOR('f', 127, short)           /* get # bytes to read */

/* socket i/o controls */
#define SIOCSHIWAT      _IOW('s',  0, short)            /* set high watermark */
#define SIOCGHIWAT      _IOR('s',  1, short)            /* get high watermark */
#define SIOCSLOWAT      _IOW('s',  2, short)            /* set low watermark */
#define SIOCGLOWAT      _IOR('s',  3, short)            /* get low watermark */
#define SIOCATMARK      _IOR('s',  7, short)            /* at oob mark? */
#define SIOCSPGRP       _IOW('s',  8, short)            /* set process group */
#define SIOCGPGRP       _IOR('s',  9, short)            /* get process group */

#define SIOCADDRT       _IOW('r', 10, struct ortentry)  /* add route */
#define SIOCDELRT       _IOW('r', 11, struct ortentry)  /* delete route */

#define SIOCSIFADDR     _IOW('i', 12, struct ifreq)     /* set ifnet address */
#define SIOCGIFADDR     _IOWR('i',33, struct ifreq)     /* get ifnet address */
#define SIOCSIFDSTADDR  _IOW('i', 14, struct ifreq)     /* set p-p address */
#define SIOCGIFDSTADDR  _IOWR('i',34, struct ifreq)     /* get p-p address */
#define SIOCSIFFLAGS    _IOW('i', 16, struct ifreq)     /* set ifnet flags */
#define SIOCGIFFLAGS    _IOWR('i',17, struct ifreq)     /* get ifnet flags */
#define SIOCGIFBRDADDR  _IOWR('i',35, struct ifreq)     /* get broadcast addr */
#define SIOCSIFBRDADDR  _IOW('i',19, struct ifreq)      /* set broadcast addr */
#define SIOCGIFCONF     _IOWR('i',36, struct ifconf)    /* get ifnet list */
#define SIOCGIFNETMASK  _IOWR('i',37, struct ifreq)     /* get net addr mask */
#define SIOCSIFNETMASK  _IOW('i',22, struct ifreq)      /* set net addr mask */
#define SIOCGIFMETRIC   _IOWR('i',23, struct ifreq)     /* get IF metric */
#define SIOCSIFMETRIC   _IOW('i',24, struct ifreq)      /* set IF metric */
#define SIOCDIFADDR     _IOW('i',25, struct ifreq)      /* delete IF addr */
#define SIOCAIFADDR     _IOW('i',26, struct ifaliasreq) /* add/chg IF alias */

#define SIOCSARP        _IOW('i', 30, struct arpreq)    /* set arp entry */
#define SIOCGARP        _IOWR('i',38, struct arpreq)    /* get arp entry */
#define SIOCDARP        _IOW('i', 32, struct arpreq)    /* delete arp entry */

/* PPP ioctls */
#define SIOCSIFCOMPAC   _IOW('i', 33, char)
#define SIOCSIFCOMPPROT _IOW('i', 34, char)
#define SIOCSIFMRU      _IOW('i', 35, long)
#define SIOCGIFMRU      _IOR('i', 36, long)
#define SIOCGIFASYNCMAP _IOR('i', 37, long)
#define SIOCSIFASYNCMAP _IOW('i', 38, long)
#define SIOCGETU        _IOR('i', 39, long)     /* get unit number */
#define SIOCSIFVJCOMP   _IOW('i', 40, char)     /* enable/disable VJ Compression */
#define SIOCSIFMTU      _IOW('i', 41, struct ifreq)
#define SIOCGIFMTU      _IOR('i', 41, struct ifreq)

#ifdef __cplusplus
extern "C" {
#endif
int     ioctl(short fd, long cmd, ...);
#ifdef __cplusplus
};
#endif

#if defined __386__
#  pragma library (unix3r)
#elif defined __SMALL__
#  pragma library (unixs)
#elif defined __COMPACT__
#  pragma library (unixc)
#elif defined __MEDIUM__
#  pragma library (unixm)
#elif defined __LARGE__
#  pragma library (unixl)
#endif

#endif
