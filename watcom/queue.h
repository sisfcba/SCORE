#ifndef _queueh
#define _queueh

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#define MAX_QUEUE_OPENS	  50
#define MAX_QUEUE_SIZE    2048

#define QUEUE_OPEN        1
#define QUEUE_CLOSE       2
#define QUEUE_KILL        3
#define QUEUE_WRITE       4
#define QUEUE_READ        5
#define QUEUE_WAIT        6
#define QUEUE_INFO        7
#define QUEUE_EXIT        8
#define QUEUE_PURGE       9
#define QUEUE_WAIT_SIG    10  
#define QUEUE_LAST_STATUS 11  

/* define queue wait macros */

#define QWAIT_NO_WAIT		0x0000
#define QWAIT_FOR_MSG		0x0001
#define QWAIT_WRITERS		0x0002
#define QWAIT_EMPTY			0x0004
#define QWAIT_READERS		0x0008
#define QWAIT_WINDOW		0x0010

#define QWAIT_TIMEOUT( secs )	( secs << 8 )

/* define sizes */
#define QNAME_SIZE          16
#define QMODE_SIZE          9
#ifdef __cplusplus
  #define QHDR_SIZE           15
#else
  #define QHDR_SIZE           (sizeof(struct queuehdr))	//15
#endif

struct queue_table_entry {
  char queue_id;
  nid_t queue_nid;
  pid_t queue_vid;
};

struct queue_msg_entry {
  struct queuehdr {
    signed char msg_type;
    char msg_queue_id;
    int msg_queue_wait;
    int msg_queue_size;
    char msg_queue_priority;
    pid_t msg_queue_proxy;
  } queuehdr;
  char msg_queue_data[MAX_QUEUE_SIZE];
};

struct queue_info {      /* Overlayed on msg_queue_data[..] */
  pid_t queue_info_tids[20];
  unsigned queue_info_nmsgs;
  char queue_info_name[QNAME_SIZE+1];
};


/* Error return codes
*/
#define QSTAT_WAITM      -1
#define QSTAT_WAITW      -2
#define QSTAT_WAITE      -3
#define QSTAT_WAITR      -4
#define QSTAT_WAITS      -5
#define QSTAT_WAITT      -6

#define QSTAT_BADMSG     -9
#define QSTAT_OPEN_MODE  -10
#define QSTAT_OPEN_PERMS -11
#define QSTAT_CREATE     -12
#define QSTAT_MEM        -13
#define QSTAT_EXIST      -14
#define QSTAT_WINDOW     -15
#define QSTAT_REPLY      -16
#define QSTAT_NAME       -17
#define QSTAT_FIND       -18
#define QSTAT_SLOT       -19
#define QSTAT_SEND       -20
#define QSTAT_MSGSIZE    -21
#define QSTAT_INTERNAL   -22

int queue_close(int);  /* qid */
int queue_info(nid_t, int, void *);  /* node, qid, buffer */
int queue_kill(int);  /* qid */
int queue_last_status(int);  /* qid */
int queue_open(char *, char *, unsigned int);  /* name, mode, create */
int queue_purge(int);  /* qid */
int queue_read(int, int, void *, int);  /* qid, wait, buffer, size */
int queue_wait(int, int);  /* qid, wait */
int queue_wait_sig(int, int, pid_t);  /* qid, wait, proxy */
int queue_write(int, void *, int, int);
int queue_release(int, char);
int queue_return_code_string(int, char *);

#ifdef __cplusplus
};
#endif

#endif  /* _queueh */

