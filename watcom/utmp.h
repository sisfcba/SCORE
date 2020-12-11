/*
 *
 *  Copyright (C) by QNX Software Systems 1993.  All rights reserved.
 */
#ifndef __UTMP_H_INCLUDED
#define __UTMP_H_INCLUDED

#include <stdio.h>
#include <sys/types.h>

#define UTMP_FILE   "/etc/utmp"
#define WTMP_FILE   "/usr/adm/wtmp"

struct utmp
    {
        char    ut_user[L_cuserid]; /*  login name */
#define ut_name ut_user
        char    ut_id[4];           /*  line # */
        char    ut_line[12];        /*  device name (console) */
        mpid_t   ut_pid;             /*  process id */
        short   ut_type;            /*  entry type */
        struct exit_status {
            short   e_termination;      /* termination status */
            short   e_exit;             /* exit status */
        } ut_exit;
        time_t  ut_time;
    };

#define EMPTY           0
#define RUN_LVL         1
#define BOOT_TIME       2
#define OLD_TIME        3
#define NEW_TIME        4
#define INIT_PROCESS    5
#define LOGIN_PROCESS   6
#define USER_PROCESS    7
#define DEAD_PROCESS    8
#define ACCOUNTING      9


/* utmp access functions */
struct utmp *getutent(void);
struct utmp *getutid(struct utmp *id);
struct utmp *getutline(struct utmp *line);
void pututline(struct utmp *utmp);
void setutent(void);
void endutent(void);
void utmpname(char *filename);
int openutmp(int oflag, int mode);
int openwtmp(int oflag, int mode);

#endif
