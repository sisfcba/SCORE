#ifndef __SOCK_MSG_H_INCLUDED
#define __SOCK_MSG_H_INCLUDED

#include <sys/socket.h>
#include <netinet/in.h>

#ifdef __cplusplus
extern "C" {
#endif

#pragma pack(1)
/* int accept(int sd, struct sockaddr *peer, int *addrlen) */
#define _SOCK_ACCEPT 0x180
struct _sock_accept {
    msg_t code;
    short sd, nsd;
    short addrlen;
};
struct _sock_accept_reply {
    msg_t status;
    short _[2];
    short addrlen;
    struct sockaddr addr[];
};

/* int bind(int sd, struct sockaddr *addr, int addrlen) */
#define _SOCK_BIND 0x181
struct _sock_bind {
    msg_t code;
    short sd;
    short addrlen;
    struct sockaddr addr[];
};
struct _sock_bind_reply {
    msg_t status;
};

/* int connect(int sd, struct sockaddr *server, int addrlen) */
#define _SOCK_CONNECT 0x182
struct _sock_connect {
    msg_t code;
    short sd;
    short addrlen;
    struct sockaddr addr[];
};
struct _sock_connect_reply {
    msg_t status;
};

/* int getpeername(int sd, struct sockaddr *peer, int *addrlen) */
#define _SOCK_GETPEERNAME 0x183
struct _sock_getpeername {
    msg_t code;
    short sd;
    short addrlen;
};
struct _sock_getpeername_reply {
    msg_t status;
    short _[1];
    short addrlen;
    struct sockaddr addr[];
};

/* int getsockname(int sd, struct sockaddr *peer, int *addrlen) */
#define _SOCK_GETSOCKNAME 0x184
struct _sock_getsockname {
    msg_t code;
    short sd;
    short addrlen;
};
struct _sock_getsockname_reply {
    msg_t status;
    short _[1];
    short addrlen;
    struct sockaddr addr[];
};

/* int getsockopt(int sd, int level, int name, void *value, int *valuelen) */
#define _SOCK_GETSOCKOPT 0x185
struct _sock_getsockopt {
    msg_t code;
    short sd;
    short level;
    short name;
    short valuelen;
};
struct _sock_getsockopt_reply {
    msg_t status;
    short _[3];
    short valuelen;
    char value[];
};

/* int listen(int sd, int backlog) */
#define _SOCK_LISTEN 0x186
struct _sock_listen {
    msg_t code;
    short sd;
    short backlog;
};
struct _sock_listen_reply {
    msg_t status;
};

/* int recvfrom(int sd, void *buffer, int nbytes, int flags, struct sockaddr *addr, int *addrlen) */
#define _SOCK_RECVFROM 0x187
struct _sock_recvfrom {
    msg_t code;
    short sd;
    short flags;
    short addrlen;
    long nbytes;
};
struct _sock_recvfrom_reply {
    msg_t status;
    short _[2];
    short addrlen;
    long nbytes;
    struct sockaddr addr[];
//  char buffer[];
};

/* int recvmsg(int sd, struct msghdr msg[], int flags) */
#define _SOCK_RECVMSG 0x188
struct _sock_recvmsg {
    msg_t code;
    short sd;
    short flags;
    short namelen;
    long nbytes;
    short controllen;
    char name[];
//  char control[];
};
struct _sock_recvmsg_reply {
    msg_t status;
    short _[1];
    short flags;
    short namelen;
    long nbytes;
    short __[1];
    char name[];
//  char buffer[];
};

/* int sendmsg(int sd, struct msghdr msg[], int flags) */
#define _SOCK_SENDMSG 0x189
struct _sock_sendmsg {
    msg_t code;
    short sd;
    short flags;
    long nbytes;
    short namelen;
    short controllen;
    char name[];
//  char control[];
//  char buffer[];
};
struct _sock_sendmsg_reply {
    msg_t status;
    short _[1];
    short flags;
    long nbytes;
};

/* int sendto(int sd, const void *buffer, int nbytes, int flags, const struct sockaddr *addr, int addrlen) */
#define _SOCK_SENDTO 0x18a
struct _sock_sendto {
    msg_t code;
    short sd;
    short flags;
    long nbytes;
    short addrlen;
    struct sockaddr addr[];
//  char buffer[];
};
struct _sock_sendto_reply {
    msg_t status;
    short _[2];
    long nbytes;
};

/* int setsockopt(int sd, int level, int name, void *value, int valuelen) */
#define _SOCK_SETSOCKOPT 0x18b
struct _sock_setsockopt {
    msg_t code;
    short sd;
    short level;
    short name;
    short valuelen;
    char value[];
};
struct _sock_setsockopt_reply {
    msg_t status;
};

/* int shutdown(int sd, int how) */
#define _SOCK_SHUTDOWN 0x18c
struct _sock_shutdown {
    msg_t code;
    short sd;
    short how;
};
struct _sock_shutdown_reply {
    msg_t status;
};

/* int socket(int domain, int type, int protocol) */
#define _SOCK_SOCKET 0x18d
struct _sock_socket {
    msg_t code;
    short sd;
    short domain;
    short type;
    short protocol;
};
struct _sock_socket_reply {
    msg_t status;
};

/* int socketpair(int domain, int type, int protocol, int sockvec[2]) */
#define _SOCK_SOCKETPAIR 0x18e
struct _sock_socketpair {
    msg_t code;
    short sd[2];
    short domain;
    short type;
    short protocol;
};
struct _sock_socketpair_reply {
    msg_t status;
};

    /*
     * kernel statistics
     */

/* int nlist(char *name) */
#define _SOCK_NLIST 0x18f
struct _sock_nlist {
    msg_t code;
//  struct nlist nl[];
};

struct _sock_nlist_reply {
    msg_t status;
//  struct nlist nl[];
};

/* int getkerninfo(int op, caddr_t where, int *size, int arg) */
#define _SOCK_GETKERNINFO 0x190
struct _sock_getkerninfo {
    msg_t code;
    short op;
    short size;
    short arg;
    char where[];
};
struct _sock_getkerninfo_reply {
    msg_t status;
    short op;
    short needed;
    short arg;
    char where[];
};

    /*
     * Serial Line IP
     */

/* int slattach(char *tty, int flags) */
#define _SOCK_SLATTACH 0x191
struct _sock_slattach {
    msg_t code;
    short flags;
    char tty[];
};
struct _sock_slattach_reply {
    msg_t status;
    short unit;
};

/* int sldetach(int unit) */
#define _SOCK_SLDETACH 0x192
struct _sock_sldetach {
    msg_t code;
    short unit;
};
struct _sock_sldetach_reply {
    msg_t status;
};

    /*
     * hostname
     */

/* int gethostname(char *name, int namelen) */
#define _SOCK_GETHOSTNAME 0x193
struct _sock_gethostname {
    msg_t code;
    short namelen;
    char name[];
};
struct _sock_gethostname_reply {
    msg_t status;
    short namelen;
    char name[];
};

/* int sethostname(char *name, int namelen) */
#define _SOCK_SETHOSTNAME 0x194
struct _sock_sethostname {
    msg_t code;
    short namelen;
    char name[];
};
struct _sock_sethostname_reply {
    msg_t status;
    short namelen;
    char name[];
};

    /*
     * NFS
     */

/* int nfssvc(int sd, struct sockaddr *mskval, int msklen, struct sockaddr *mtchval, int mtchlen) */
#define _NFS_NFSSVC 0x195
struct _nfs_nfssvc {
    msg_t code;
    short sd;
    struct sockaddr mskval;
    short msklen;
    struct sockaddr mtchval;
    short mtchlen;
};
struct _nfs_nfssvc_reply {
    msg_t status;
};

/* int nfsbio(void) */
#define _NFS_NFSBIO 0x196
struct _nfs_nfsbio {
    msg_t code;
};
struct _nfs_nfsbio_reply {
    msg_t status;
};

    /*
     * VFS
     */
/* getfh(char *path) */
#define _VFS_GETFH 0x197
struct _vfs_getfh {
    msg_t code;
    short unit;
    char path[];
};
/* mount.h and sock_msg.h must be consistant re: fhandle_t */
#ifndef _FHANDLE_T
#define _FHANDLE_T
/*
 * File identifier.
 * These are unique per filesystem on a single machine.
 */
#define MAXFIDSZ    32

typedef struct { short val[2]; } fsid_t;
struct fid {
    char        fid_data[MAXFIDSZ]; /* data (variable length) */
};

/*
 * Generic file handle
 */
struct fhandle {
    fsid_t  fh_fsid;    /* File system id of mount point */
    struct  fid fh_fid; /* Id of file */
};
typedef struct fhandle  fhandle_t;
#endif
struct _vfs_getfh_reply {
    msg_t status;
    short zero;
    fhandle_t fh;
};

/* int getfsstat(char *mntbuf, int bufsize, int flags) */
#define _VFS_GETFSSTAT 0x198
struct _vfs_getfsstat {
    msg_t code;
    short bufsize;
    short flags;
};
struct _vfs_getfsstat_reply {
    msg_t status;
    short count;
    short _[1];
    char mntbuf[];
};

/* int mount(int type, char *name, int flags, void *args) */
#define _VFS_MOUNT 0x199
struct _vfs_mount {
    msg_t code;
    short type;
    short flags;
    char name[];
//  char args[];
};
struct _vfs_mount_reply {
    msg_t status;
};

#define _VFS_UNMOUNT 0x19a

    /*
     * Point to Point Protocol
     */

#ifndef __386__
/* int pppattach(char *tty, int flags) */
#define _SOCK_PPPATTACH 0x19b
struct _sock_pppattach {
    msg_t code;
    short flags;
    char tty[];
};
struct _sock_pppattach_reply {
    msg_t status;
    short unit;
};

/* int pppdetach(int unit) */
#define _SOCK_PPPDETACH 0x19c
struct _sock_pppdetach {
    msg_t code;
    short unit;
};
struct _sock_pppdetach_reply {
    msg_t status;
};

/* int pppread(int unit, char *buffer, int nbytes) */
#define _SOCK_PPPREAD 0x19d
struct _sock_pppread {
    msg_t type;
    short unit;
    short nbytes;
};
struct _sock_pppread_reply {
    msg_t status;
    short _[1];
    short nbytes;
    char data[];
};

/* int pppwrite(int unit, char *buffer, int nbytes) */
#define _SOCK_PPPWRITE 0x19e
struct _sock_pppwrite {
    msg_t type;
    short unit;
    short nbytes;
    char data[];
};
struct _sock_pppwrite_reply {
    msg_t status;
    short _[1];
    short nbytes;
};
#endif

/* int pppio(int op, int unit, char *buffer, int nbytes) */
#define _SOCK_PPPIO 0x19f
struct _sock_pppio {
    msg_t type;
    short op;
    short unit;
    long nbytes;
    char data[];
};
struct _sock_pppio_reply {
    msg_t status;
    short _[1];
    short unit;
    long nbytes;
    char data[];
};

#define _SOCK_NEW802MAC 0x1a0
struct _sock_new802mac {
    msg_t type;
    unsigned short lan;
    unsigned char mac[6];
};
struct _sock_new802mac_reply {
    msg_t status;
};

#define _SOCK_DELETEMAC 0x1a1
struct _sock_deletemac {
    msg_t type;
    unsigned short addrlen;
    unsigned char mac[6];
};

struct _sock_deletemac_reply {
    msg_t status;
};

#define _SOCK_FDINFO 0x1a2
struct _socket_fdinfo {
    msg_t           type;
    mpid_t          pid;
    short int       fd;
    };

struct _socket_info_entry {
    mpid_t          pid;
    short int       fd;
    short			socket_type;
	unsigned long	rcvq_count;
	unsigned long	sndq_count;
	struct in_addr	faddr;
	unsigned short	fport;
	struct in_addr  laddr;
	unsigned short 	lport;
	unsigned short	state;
    };


struct _socket_fdinfo_reply {
    msg_t                   status;
    struct _socket_info_entry info;
    };


/* Below are message for Dns -- 0x1fx */
#define _SOCK_DNS_GHBN 0x1f0
struct _sock_dns_ghbn 
{
	msg_t type;
	short fd;
	short len;		       /* total len of message --lines up with io_write */
	short sock;		       /* SOCK environment variable */
	pid_t proxy;
	char host[256];		       /* hostname to look up */
	/* set of environment variables in form x=y\0
	 * \0\0 terminates the list.
	 */
};

struct _sock_dns_ghbn_reply
{
	msg_t status;
};

/* this is returned by a read on the fd */
struct _sock_dns_read_reply
{
	int h_addrtype;
	int h_length;
	int num_aliases;
	int num_addrs;
	char name[];
	/* aliases laid out end to end with a zero after each */
	/* addresses laid out end to end */
};

#define _SOCK_DNS_GHBN_DATA 0x1f1
struct _sock_dns_ghbn_data
{
	msg_t type;
	msg_t status;
	struct _sock_dns_read_reply;
};

#define _SOCK_DNS_SET_ENV 0x1f2
struct _sock_dns_set_env
{
	msg_t type;
	/* <envvar>=<value> pairs until a 00 */
};

struct _sock_dns_set_env_reply
{
	msg_t status;
};
#pragma pack()

#ifdef __cplusplus
};
#endif
#endif
