/*
 *  errno.h     Error numbers
 *
 *  Copyright by WATCOM International Corp. 1988-1996.  All rights reserved.
 *  Copyright by QNX Software Systems Limited 1990-1996. All rights reserved.
 */
#ifndef _ERRNO_H_INCLUDED
#ifdef __cplusplus
extern "C" {
#endif

#ifndef errno
    #define errno (*__get_errno_ptr())
#endif
extern int errno;


/* --- Symbolic names of the error return conditions --- */

#define EOK              0  /* No error                                 */
#define EPERM            1  /* Not owner                                */
#define ENOENT           2  /* No such file or directory                */
#define ESRCH            3  /* No such process                          */
#define EINTR            4  /* Interrupted system call                  */
#define EIO              5  /* I/O error                                */
#define ENXIO            6  /* No such device or address                */
#define E2BIG            7  /* Arg list too big                         */
#define ENOEXEC          8  /* Exec format error                        */
#define EBADF            9  /* Bad file number                          */
#define ECHILD          10  /* No child processes                       */
#define EAGAIN          11  /* Resource unavailable, try again          */
#define ENOMEM          12  /* Not enough space                         */
#define EACCES          13  /* Permission denied                        */
#define EFAULT          14  /* Bad address                              */
#define ENOTBLK         15  /* Block device required                    */
#define EBUSY           16  /* Device or resource busy                  */
#define EEXIST          17  /* File exists                              */
#define EXDEV           18  /* Cross-device link                        */
#define ENODEV          19  /* No such device                           */
#define ENOTDIR         20  /* Not a directory                          */
#define EISDIR          21  /* Is a directory                           */
#define EINVAL          22  /* Invalid argument                         */
#define ENFILE          23  /* File table overflow                      */
#define EMFILE          24  /* Too many open files                      */
#define ENOTTY          25  /* Not a character device                   */
#define ETXTBSY         26  /* Text file busy                           */
#define EFBIG           27  /* File too large                           */
#define ENOSPC          28  /* No space left on device                  */
#define ESPIPE          29  /* Illegal seek                             */
#define EROFS           30  /* Read-only file system                    */
#define EMLINK          31  /* Too many links                           */
#define EPIPE           32  /* Broken pipe                              */
#define EDOM            33  /* Math argument out of domain of function  */
#define ERANGE          34  /* Result too large                         */
#define ENOMSG          35  /* No message of desired type               */
#define EIDRM           36  /* Identifier removed                       */
#define ECHRNG          37  /* Channel number out of range              */
#define EL2NSYNC        38  /* Level 2 not synchronized                 */
#define EL3HLT          39  /* Level 3 halted                           */
#define EL3RST          40  /* Level 3 reset                            */
#define ELNRNG          41  /* Link number out of range                 */
#define EUNATCH         42  /* Protocol driver not attached             */
#define ENOCSI          43  /* No CSI structure available               */
#define EL2HLT          44  /* Level 2 halted                           */
#define EDEADLK         45  /* Deadlock avoided                         */
#define ENOLCK          46  /* No locks available in system             */

#define ENOTSUP         77  /* Not supported (1003.4)                   */
#define ENAMETOOLONG    78  /* Name too long                            */

/* --- Shared library errors --- */

#define ELIBACC         83  /* Can't access shared library              */
#define ELIBBAD         84  /* Accessing a corrupted shared library     */
#define ELIBSCN         85  /* .lib section in a.out corrupted          */
#define ELIBMAX         86  /* Attempting to link in too many libraries */
#define ELIBEXEC        87  /* Attempting to exec a shared library      */

/* ----------------------------- */

#define ENOSYS          89  /* Unknown system call                      */
#define ELOOP           90  /* Too many symbolic link or prefix loops   */

#define ENOTEMPTY       93  /* Directory not empty                      */

#define EOPNOTSUPP      103 /* Operation not supported                  */

#define ESTALE          122 /* Potentially recoverable i/o error        */

/* --- Sockets --- */

/* non-blocking and interrupt i/o */
/*        EAGAIN           35        */    /* Resource temporarily unavailable */
/*        EWOULDBLOCK      35        */    /* Operation would block */
#define EWOULDBLOCK    EAGAIN              /* Operation would block */
#define EINPROGRESS       236              /* Operation now in progress */
/*        EALREADY         37        */    /* Operation already in progress */
#define EALREADY        EBUSY              /* Operation already in progress */

/* ipc/network software -- argument errors */
#define ENOTSOCK        238                /* Socket operation on non-socket */
#define EDESTADDRREQ    239                /* Destination address required */
#define EMSGSIZE        240                /* Message too long */
#define EPROTOTYPE      241                /* Protocol wrong type for socket */
#define ENOPROTOOPT     242                /* Protocol not available */
#define EPROTONOSUPPORT 243                /* Protocol not supported */
#define ESOCKTNOSUPPORT 244                /* Socket type not supported */
#define EPFNOSUPPORT    246                /* Protocol family not supported */
#define EAFNOSUPPORT    247                /* Address family not supported by protocol family */
#define EADDRINUSE      248                /* Address already in use */
#define EADDRNOTAVAIL   249                /* Can't assign requested address */

/* ipc/network software -- operational errors */
#define ENETDOWN        250                /* Network is down */
#define ENETUNREACH     251                /* Network is unreachable */
#define ENETRESET       252                /* Network dropped connection on reset */
#define ECONNABORTED    253                /* Software caused connection abort */
#define ECONNRESET      254                /* Connection reset by peer */
#define ENOBUFS         255                /* No buffer space available */
#define EISCONN         256                /* Socket is already connected */
#define ENOTCONN        257                /* Socket is not connected */
#define ESHUTDOWN       258                /* Can't send after socket shutdown */
#define ETOOMANYREFS    259                /* Too many references: can't splice */
#define ETIMEDOUT       260                /* Connection timed out */
#define ECONNREFUSED    261                /* Connection refused */

/*      ELOOP          62        */        /* Too many levels of symbolic links */
/*      ENAMETOOLONG   63        */        /* File name too long */

#define EHOSTDOWN        264                /* Host is down */
#define EHOSTUNREACH     265                /* No route to host */

/* Network File System */
/*      ESTALE           70     */          /* Stale NFS file handle */
#define EREMOTE         271                 /* Too many levels of remote in path */
#define EBADRPC         272                 /* RPC struct is bad */
#define ERPCMISMATCH    273                 /* RPC version wrong */
#define EPROGUNAVAIL    274                 /* RPC prog. not avail */
#define EPROGMISMATCH   275                 /* Program version wrong */
#define EPROCUNAVAIL    276                 /* Bad procedure for program */


/* --- QNX 4.0 specific --- */

#define ENOREMOTE       1000 /* Must be done on local machine           */
#define ENONDP          1001 /* Need an NDP (8087...) to run            */
#define EBADFSYS        1002 /* Corrupted file system detected          */
#define ENO32BIT        1003 /* 32-bit integer fields were used         */
#define ENOVPE          1004 /* No proc entry avail for virtual process */
#define ENONETQ         1005 /* Process manager-to-net enqueuing failed */
#define ENONETMAN       1006 /* Could not find net manager for node no. */
#define EVIDBUF2SML     1007 /* Told to allocate a vid buf too small    */
#define EVIDBUF2BIG     1008 /* Told to allocate a vid buf too big      */
#define EMORE           1009 /* More to do, send message again          */
#define ECTRLTERM       1010 /* Remap to the controlling terminal       */
#define ENOLIC          1011 /* No license                              */
#define EDSTFAULT       1012 /* Destination fault on msg pass           */

#define _ERRNO_H_INCLUDED
#ifdef __cplusplus
};
#endif
#endif
