
/*
 *  slib16.h    QNX 4.0+ 16-bit shared library entry points.
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __SLIB16_H_INCLUDED
#define __SLIB16_H_INCLUDED

#ifndef CHKNULL
#define CHKNULL(x)  ((x) ? (x) : (void __far *)0)
#endif

#ifdef __cplusplus
extern "C" {
#endif
extern int (__far * (__far *__f))();
#ifdef __cplusplus
};
#endif


#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif

#define __ctermid(a) ((char *(__far *) (char __far *)) \
 __f[2])(a)
#define __sopen_slib(a,b,c,d) ((int(__far *) \
    (const char __far *,int ,int ,mode_t)) \
 __f[3])(a,b,c,d)
/* 4? */
#define close(a) ((int(__far *) (int __fildes)) \
 __f[5])(a)
#define read(a,b,c) ((ssize_t(__far *) \
    (int __fildes,void __far *__buffer,size_t __len)) \
 __f[6])(a,b,c)
#define write(a,b,c) ((ssize_t(__far *) (int ,const void __far *,size_t)) \
 __f[7])(a,b,c)
#define creat(a,b) ((int(__far *) (const char __far *,mode_t)) \
 __f[8])(a,b)
#define lseek(a,b,c) ((off_t(__far *) (int,off_t,int)) \
 __f[9])(a,b,c)
#define __open_slib(a,b,c) ((int(__far *) (const char __far *,int,mode_t)) \
 __f[10])(a,b,c)
#define qnx_segment_alloc(a) ((unsigned(__far *) (long)) \
 __f[11])(a)
#define qnx_segment_alloc_flags(a,b) \
    ((unsigned(__far *) (long, unsigned)) \
 __f[12])(a,b)
#define qnx_segment_realloc(a,b) \
    ((unsigned(__far *) (unsigned, long)) \
 __f[13])(a,b)
#define qnx_segment_huge(a) \
    ((unsigned(__far *) (long)) \
 __f[14])(a)
#define qnx_segment_arm(a,b,c) \
    ((int(__far *) (pid_t,unsigned,unsigned)) \
 __f[15])(a,b,c)
#define qnx_segment_flags(a,b) \
    ((unsigned(__far *) (unsigned,unsigned)) \
 __f[16])(a,b)
#define qnx_segment_free(a) \
    ((int(__far *) (unsigned)) \
 __f[17])(a)
#define qnx_segment_get(a,b,c) \
    ((unsigned(__far *) (pid_t,unsigned,unsigned)) \
 __f[18])(a,b,c)
#define qnx_segment_index(a,b,c) \
    ((unsigned(__far *) (pid_t,pid_t,unsigned)) \
 __f[19])(a,b,c)
#define qnx_segment_info(a,b,c,d) ((unsigned(__far *) \
    (pid_t,pid_t,unsigned,struct _seginfo __far *)) \
 __f[20])(a,b,c,d)
#define qnx_segment_overlay(a,b) ((unsigned(__far *) (long,long)) \
 __f[21])(a,b)
#define qnx_segment_put(a,b,c) \
    ((unsigned(__far *) (pid_t,unsigned,unsigned)) \
 __f[22])(a,b,c)
#define qnx_osinfo(a,b) ((int(__far *) \
    (nid_t, struct _osinfo __far *)) \
 __f[23])(a,b)
/* ?? 24 ?? */  
#define qnx_fd_attach(a,b,c,d,e,f,g) ((int(__far *) \
        (pid_t, int, nid_t, pid_t, pid_t, unsigned, unsigned)) \
 __f[25])(a,b,c,d,e,f,g)
#define qnx_fd_detach(a) ((int(__far *) (int)) \
 __f[26])(a)
#define qnx_fd_query(a,b,c,d) ((int(__far *) \
        (pid_t, pid_t, int, struct _fd_entry __far *)) \
 __f[27])(a,b,c,d)
#define qnx_fullpath(a,b) ((char __far *(__far *) \
        (char __far *,char __far *)) \
 __f[28])(a,b)
#define qnx_hint_attach(a,b,c) ((int(__far *) \
        (unsigned, void __far *, unsigned)) \
 __f[29])(a,b,c)
#define qnx_hint_detach(a) ((int(__far *) (int)) \
 __f[30])(a)
#define qnx_hint_mask(a,b) ((int(__far *)(unsigned, unsigned)) \
 __f[31])(a,b)
#define qnx_hint_query(a,b,c) ((int(__far *) \
        (pid_t, int, struct _irqinfo __far *)) \
 __f[32])(a,b,c)
#define qnx_name_attach(a,b) ((int(__far *) (nid_t, char __far *)) \
 __f[33])(a,b)
#define qnx_name_detach(a,b) ((int(__far *) (nid_t, int)) \
 __f[34])(a,b)
#define qnx_name_locate(a,b,c,d) ((pid_t(__far *) \
    (nid_t, char __far *, unsigned, unsigned __far *)) \
 __f[35])(a,b,c,d)
#define qnx_name_query(a,b,c) ((int(__far *) \
    (pid_t, int, struct _nameinfo __far *)) \
 __f[36])(a,b,c)
#define qnx_prefix_attach(a,b,c) ((int(__far *) \
    (char __far *, char __far *, short unsigned)) \
 __f[37])(a,b,c)
#define qnx_prefix_detach(a) ((int(__far *) \
    (char __far *)) \
 __f[38])(a)
#define qnx_prefix_query(a,b,c,d) ((int(__far *) \
    (nid_t, char __far *, char __far *, int)) \
 __f[39])(a,b,c,d)
#define qnx_scheduler(a,b,c,d,e) ((int(__far *) \
    (pid_t, pid_t pid, int alg, int prio, int retalg) ) \
 __f[40])(a,b,c,d,e)
#define qnx_proxy_attach(a,b,c,d) ((pid_t(__far *) \
    (pid_t, char __far *, int, int)) \
 __f[41])(a,b,c,d)
#define qnx_proxy_detach(a) ((int(__far *) (pid_t)) \
 __f[42])(a)
#define qnx_vc_attach(a,b,c,d) ((pid_t(__far *) (nid_t, pid_t, unsigned, int)) \
 __f[43])(a,b,c,d)
#define qnx_vc_detach(a) ((int(__far *) (pid_t)) \
 __f[44])(a)
#define __fcntl_slib(a,b,c,d) ((int(__far *) (int,int,int,struct flock __far *)) \
 __f[45])(a,b,c,d)
#define dup(a) ((int(__far *) (int)) \
 __f[46])(a)
#define dup2(a,b) ((int(__far *) (int, int)) \
 __f[47])(a,b)
#define  __getopt(a,b,c,d,e,f,g,h,i,j,k,l) ((int(__far *) \
  (int, const void __far *, const char __far *, int, char __far * __far *, int __far *, \
  int __far *, int __far *, int __far *, char __far * __far *, int __far *, \
  char __far *)) \
  __f[48]) (a,b,c,d,e,f,g,h,i,j,k,l)
#define chroot(a) ((int(__far *) (const char __far *)) __f[49])(a)
#define __resolve_net(a,b,c,d,e,f) ((int(__far *) \
    (unsigned,int,struct _io_open __far *, const char __far *, \
    unsigned,char __far *)) \
 __f[50])(a,b,c,d,e,f)
#define stat(a,b) ((int(__far *) (const char __far *, struct stat __far *)) \
 __f[51])(a,b)
#define fstat(a,b) ((int(__far *) (int , struct stat __far *)) \
 __f[52])(a,b)
#define readv(a,b,c) ((int(__far *) (int, const struct iovec __far *, int)) \
 __f[53])(a,b,c)
#define writev(a,b,c) ((int(__far *) (int, const struct iovec __far *, int)) \
 __f[54])(a,b,c)
/* 55-57*/
#define __init_fd(a) ((void __far *(__far *) (pid_t)) \
 __f[58])(a)
#define __get_fd(a,b,c) ((unsigned(__far *) (pid_t, int, void __far *))\
 __f[59])(a,b,c)
#define __get_pid_info(a,b,c) ((int(__far *) \
        (pid_t, struct _psinfo3 __far *, void __far *)) \
 __f[60])(a,b,c)
#define slib_strtonid(a,b) ((nid_t(__far *) (const char __far *, char __far * __far *)) \
 __f[61])(a,b)
#define slib_nidtostr(a,b,c) \
 ((int(__far *) (nid_t, char __far *, int)) \
 __f[62])(a,b,c)
/* 63 ? */
#define qnx_segment_overlay_flags(a,b,c) \
    ((unsigned(__far *) (long,long,unsigned)) \
 __f[64])(a,b,c)
#define opendir(a)  ((struct _dir __far * (__far *) (const char __far *)) \
 __f[65])(a)
#define readdir(a) ((struct dirent __far *(__far *) (struct _dir __far *)) \
 __f[66])(a)
#define rewinddir(a) ((void(__far *) (struct _dir __far *)) \
 __f[67])(a)
#define closedir(a) ((int(__far *) (struct _dir __far *)) \
 __f[68])(a)
/* 68-70 */
#define __strerror(a,b,c) ((void(__far *) (int,int,char __far *)) \
 __f[71])(a,b,c)
#define lstat(a,b)  ((int(__far *) (const char __far *, struct stat __far *)) \
 __f[72])(a,b)
#define chdir(a) ((int (__far *) (char __far *)) \
 __f[73])(a)
#define __slib16_qnx_name_nodes(a,b,c,d) \
             ((int(far *) (pid_t, char far *,unsigned,nid_t far *)) \
              __f[74])(a,b,c,d)

#endif
