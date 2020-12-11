#ifndef __TERMCAP_H_INCLUDED
#define __TERMCAP_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif
extern int tgetent(char *, char *);
extern char *tgetstr(char *, char **);
extern int tgetnum(char *);
extern int tgetflag(char *);
extern char *tgoto(char *, int, int);
extern int tputs(char *, int, int (*)());
#ifdef __cplusplus
};
#endif

#if !defined __386__
# if defined __SMALL__
#  pragma library (termcaps)
# elif defined __COMPACT__
#  pragma library (termcapc)
# elif defined __MEDIUM__
#  pragma library (termcapm)
# elif defined __LARGE__
#  pragma library (termcapl)
# endif
#endif

#endif
