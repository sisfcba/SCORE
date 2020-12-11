#ifndef _SGTTY_H_INCLUDED
#define _SGTTY_H_INCLUDED
#include <termio.h>
#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

/*
 * TIOCGETP/TIOCSETP structure
 */
struct sgttyb {
    char sg_ispeed; /* input speed */
    char sg_ospeed; /* output speed */
    char sg_erase;  /* erase character */
    char sg_kill;   /* kill character */
    int  sg_flags;  /* mode flags */
};

/*
 * TIOCGETC/TIOCSETC structure
 */
struct tchars {
    char t_intrc;   /* interrupt */
    char t_quitc;   /* quit */
    char t_startc;  /* start output */
    char t_stopc;   /* stop output */
    char t_eofc;    /* end-of-file */
    char t_brkc;    /* input delimiter (like nl) */
};

/*
 * TIOCGLTC/TIOCSLTC structure
 */
struct ltchars {
    char    t_suspc;    /* stop process signal */
    char    t_dsuspc;   /* delayed stop process signal */
    char    t_rprntc;   /* reprint line */
    char    t_flushc;   /* flush output (toggles) */
    char    t_werasc;   /* word erase */
    char    t_lnextc;   /* literal next character */
};

#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif
#define gtty(fd, sg)    ioctl(fd, TIOCGETP, sg)
#define stty(fd, sg)    ioctl(fd, TIOCSETP, sg)
#endif
