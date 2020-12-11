/*
 *  inline.h 
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */


#ifndef __INLINE_H_INCLUDED
#define __INLINE_H_INCLUDED

/*

void    ll_debug(void);
    -   issues an int f3h which puts you in to the low level debugger.

void    delay_8X(int count)
    -   delays approximately 8 clocks * count.
        useful for 'little' timing loops

unsigned    pswget(void);
    -   returns the current value of the flags register.

void    restore(unsigned psw)
    -   stores psw into flags register.

unsigned    disable(void);
    -   disables interrupts, and returns previous value of flags.

unsigned    enable(void);
    -   enables interrupts, and returns previous value of flags.

unsigned    str_forward(void);
    -   sets direction flag to forward and returns previous value of flags.

unsigned    str_reverse(void);
    -   sets direction flag to reverse and returns previous value of flags.

int segsize(ushort_t sel);
    -   return the size of the segment

int sldt(void);
    -   return descriptor for LDT.
    
unsigned    my_cs(void)
    -   returns current value of 'cs' register.

unsigned    my_ds(void)
    -   returns current value of 'ds' register.

void    io_safe(void);
    -   does 2 "jmp ." to avoid trashing io device.

long    swapw(int val)
    -   swaps byte ordering of a word

long    swapl(long lval)
    -   swaps byte ordering of a long


memcpy8(void far *dst, const void far *src, int nbytes);
memcpy16(void far *dst, const void far *src, int nbytes);
memcpy32(void far *dst, const void far *src, int nbytes);

    -   memcopies by 8,16 and 32 bits resp.
    -   note nbytes is BYTES and is expected to be an even
        multiple of the copy size (ie 16 or 32).
*/


#ifndef __TYPES_H_INCLUDED
#include <sys/types.h>
#endif


#ifdef __cplusplus
extern "C" {
#endif

extern ushort_t  inb(int port);
extern ushort_t  inw(int port);
extern ulong_t   inl(int port);
extern void      outb(int port, ushort_t val);
extern void      outw(int port, ushort_t val);
extern void      outl(int port, ulong_t val);
extern caddr_t   inws(caddr_t buffer, unsigned count, unsigned port);
extern caddr_t   outws(caddr_t buffer, unsigned count, unsigned port);
#define insw inws
#define outsw outws
extern inp_dwords(void __far *p, unsigned count, unsigned port);
extern inp_words(void __far *p, unsigned count, unsigned port);
extern inp_bytes(void __far *p, unsigned count, unsigned port);
extern outp_dwords(void __far *p, unsigned count, unsigned port);
extern outp_bytes(void __far *p, unsigned count, unsigned port);
extern outp_words(void __far *p, unsigned count, unsigned port);

extern void       delay_8X(unsigned count);
extern void       io_safe(void);
extern unsigned   pswget(void);
extern void       ll_debug(void);
extern unsigned   disable(void);
extern unsigned   enable(void);
extern unsigned   str_forward(void);
extern unsigned   str_reverse(void);
extern void       restore(unsigned flgs);

extern ushort_t _cs( void );
extern ushort_t _ds( void );
extern ushort_t _es(void);
extern ushort_t _ss(void);
extern ushort_t _fs(void);
extern ushort_t _gs(void);
extern unsigned _lsl(unsigned seg);
extern unsigned _sldt(void);
extern unsigned _verr(unsigned seg);
extern unsigned _verw(unsigned seg);

#define segsize(s) ((ulong_t)_lsl(s)+1)
#define my_cs _cs
#define my_ds _ds
#define my_es _es
#define my_ss _ss
#define my_fs _fs
#define my_gs _gs

extern ushort_t swapw(ushort_t val);
extern ulong_t  swapl(ulong_t val);


#ifdef __386__

#pragma aux inb = "xor ax,ax" "in  al,dx"\
    __parm __nomemory [edx] __modify __exact __nomemory [ax] __value [ax];
#pragma aux inw = "in  ax,dx"\
    __parm __nomemory [edx] __modify __exact __nomemory [ax] __value [ax];
#pragma aux inl = "in  eax,dx"\
    __parm __nomemory [edx] __modify __exact __nomemory [eax] __value [eax];
#pragma aux outb = "out  dx,al"\
    __parm __nomemory [edx] [ax] __modify __exact __nomemory [];
#pragma aux outw = "out  dx,ax"\
    __parm __nomemory [edx] [ax] __modify __exact __nomemory [];
#pragma aux outl = "out  dx,eax"\
    __parm __nomemory [edx] [eax] __modify __exact __nomemory [];

#pragma aux inws = "push ds" "cld" "pop es" "rep insw" "mov eax,edi"\
    __parm [edi] [ecx] [edx] __modify [es ecx edi] __value [eax];
#pragma aux outws = "cld" "rep outsw" "mov eax,edi"\
    __parm [esi] [ecx] [edx] __modify [ecx esi] __value [eax];

#pragma aux inp_dwords = \
        ".386p" \
        "cld" \
        "rep insd" \
        __parm [es edi] [ecx] [edx] __modify __exact [ecx edi];

#pragma aux inp_words = \
        ".386p" \
        "cld" \
        "rep insw" \
        "mov eax,edi" \
        __parm [es edi] [ecx] [edx] __modify __exact [ecx edi];

#pragma aux inp_bytes = \
        ".386p" \
        "cld" \
        "rep insb" \
        "mov eax,edi" \
        __parm [es edi] [ecx] [edx] __modify __exact [ecx edi];

#pragma aux outp_dwords =  \
        ".386p" \
        "jcxz l2" \
        "cld" \
        "l1:          " \
        "db 0x26, 0xad" /* es: lodsd */ \
        "out dx,eax   " \
        "loop l1      " \
        "l2:          " \
        __parm [es esi] [ecx] [edx] __modify __exact [ecx esi eax];

#pragma aux outp_words = \
        ".386p" \
        "jcxz l2" \
        "cld" \
        "l1:          " \
        "db 0x66, 0x26, 0xad" /* es: lodsw */ \
        "out dx, ax  " \
        "loop l1     " \
        "l2:          " \
        __parm [es esi] [ecx] [edx] __modify __exact [ecx esi eax];

#pragma aux outp_bytes =  \
        ".386p" \
        "jcxz l2" \
        "cld" \
        "l1:          " \
        "db 0x26, 0xac" /* es: lodsb */ \
        "out  dx, al " \
        "loop l1     " \
        "l2:          " \
        __parm [es esi] [ecx] [edx] __modify [ecx esi eax];



#pragma aux delay_8X = "here: loop here" parm [ecx] modify [ecx];
#pragma aux io_safe = \
        "jmp short l1"        \
        "l1: jmp short l2"    \
        "l2: nop"       \
        __parm __nomemory []                 \
        __modify __exact __nomemory [];

#pragma aux ll_debug    = "int 0f3h" __parm [] __modify __exact __nomemory [];

#pragma aux pswget      = "pushfd" "pop eax"       __parm [] __modify [eax];
#pragma aux disable     = "pushfd" "cli" "pop eax" __parm [] __modify [eax];
#pragma aux enable      = "pushfd" "sti" "pop eax" __parm [] __modify [eax];
#pragma aux str_forward = "pushfd" "cld" "pop eax" __parm [] __modify [eax];
#pragma aux str_reverse = "pushfd" "std" "pop eax" __parm [] __modify [eax];
#pragma aux restore     = "push eax" "popfd"       __parm [eax] __modify [];

#pragma aux _cs = "mov ax,cs" __parm [] __modify __exact __nomemory [ax];
#pragma aux _ds = "mov ax,ds" __parm [] __modify __exact __nomemory [ax];
#pragma aux _es = "mov ax,es" __parm [] __modify __exact __nomemory [ax];
#pragma aux _ss = "mov ax,ss" __parm [] __modify __exact __nomemory [ax];
#pragma aux _fs = "mov ax,fs" __parm [] __modify __exact __nomemory [ax];
#pragma aux _gs = "mov ax,gs" __parm [] __modify __exact __nomemory [ax];


#pragma aux _lsl = "lsl eax,eax" __parm [eax] __modify [eax];
#pragma aux _sldt = ".386p" "sldt ax" "movzx eax,ax" __parm [] __modify [eax];
#pragma aux _verr = ".386p" "verr ax" "lahf" "shr eax,14" "and eax,1"\
    __parm [eax] __modify [eax];
#pragma aux _verw = ".386p" "verw ax" "lahf" "shr eax,14" "and eax,1"\
    __parm [eax] __modify [eax];

#define fverr(s,p,len) (_verr(s) ? (!len ? 1 : _lsl(s) >= ((long)(p) + (len)-1)) : 0 ) 
#define fverw(s,p,len) (_verw(s) ? (!len ? 1 : _lsl(s) >= ((long)(p) + (len)-1)) : 0 )

#define verr(p,l)  fverr(FP_SEG(p), FP_OFF(p), l)
#define verw(p,l)  fverw(FP_SEG(p), FP_OFF(p), l)

#pragma aux swapw = "xchg ah,al" __parm __nomemory [ax] __value [ax] \
   __modify __exact __nomemory [ax];
#pragma aux swapl = "xchg ah,al" "rol eax,16" "xchg ah,al" \
        __parm __nomemory [eax] __value [eax] __modify __exact __nomemory [eax];


#define memcpy32 _fmemcpy

#else   /* if defined __386__ */

#pragma aux inb = \
          0x32 0xe4          /* xor ah,ah */\
          0xec               /* in  al,dx */\
          __parm __nomemory [dx] \
          __modify __exact __nomemory [ax];

#pragma aux inw = \
          0xed              /* in ax,dx   */\
          __parm __nomemory [dx] \
          __modify __exact __nomemory [ax] __value [ax];

#if __WATCOMC__ >= 900
#pragma aux inl =\
        ".386p"         \
        "in eax,dx" \
        "mov edx,eax" \
        "shr edx,16"  \
        "and eax,0ffffh" \
        __parm __nomemory [ DX ] __modify __exact __nomemory [ AX DX ] __value [ DX AX ];
#endif

#pragma aux outb = \
          0xee             /*  out dx,al   */\
          __parm __nomemory [dx] [ax] \
          __modify __exact __nomemory [];

#pragma aux outw = \
          0xef             /*  out dx,ax    */\
          __parm __nomemory [dx] [ax] \
          __modify __exact __nomemory [];

#if __WATCOMC__ >= 900
#pragma aux outl =\
        ".386p"         \
        "shl ecx,16" \
        "mov cx,ax" \
        "mov eax,ecx" \
        "out dx,eax" \
        __parm __nomemory [ DX ] [ AX CX ] __modify __exact __nomemory [ AX CX ];
#endif

#pragma aux delay_8X =          \
        0xe2 0xfe   /*  loop -2 */      \
        __parm __nomemory [cx]  \
        __modify __exact __nomemory [cx];

#pragma aux ll_debug = \
        0xcd 0xf3   /*  int 0f3h    */  \
        __parm []                 \
        __modify exact [];

#pragma aux io_safe = \
        0xeb 0x00   /*  jmp .   */  \
        0xeb 0x00   /*  jmp .   */  \
        __parm []                 \
        __modify __exact [];

#pragma aux pswget = \
        0x9c    /*  pushf   */ \
        0x58    /*  pop ax  */ \
        __parm __nomemory   []      \
        __modify __exact __nomemory [ AX ];

#pragma aux disable = \
        0x9c    /*  pushf   */ \
        0xfa    /*  cli     */ \
        0x58    /*  pop ax  */ \
        __parm []     \
        __modify __exact [ AX ];

#pragma aux enable = \
        0x9c    /*  pushf   */ \
        0xfb    /*  sti     */ \
        0x58    /*  pop ax  */ \
        __parm []     \
        __modify __exact [ AX ];
        

#pragma aux str_forward = \
        0x9c    /*  pushf   */ \
        0xfc    /*  cld     */ \
        0x58    /*  pop ax  */ \
        __parm nomemory   []      \
        __modify __exact __nomemory [ AX ];

#pragma aux cforward = \
        0x9c    /*  pushf   */ \
        0xfd    /*  cld     */ \
        0x58    /*  pop ax  */ \
        __parm __nomemory   []      \
        __modify __exact __nomemory [ AX ];

#pragma aux restore = \
        0x50    /*  push    ax  */ \
        0x9d    /*  popf        */ \
        __parm [ AX ]                 \
        __modify __exact [];

#pragma aux _cs = 0x8c 0xc8 __parm __nomemory [] __value [ AX ] \
        __modify __exact __nomemory [ AX ];
#pragma aux _ds = 0x8c 0xd8 __parm __nomemory [] __value [ AX ] \
        __modify __exact __nomemory [ AX ];
#pragma aux _es = 0x8c 0xc0 __parm __nomemory [] __value [ AX ] \
        __modify __exact __nomemory [ AX ];
#pragma aux _ss = "mov ax,ss" __parm __nomemory [] __value [ AX ] \
        __modify __exact __nomemory [ AX ];


    
#if __WATCOMC__ >= 900
#pragma aux insw = ".286p" "cld" "rep insw"\
    __parm [es di] [cx] [dx] \
    __modify [cx di] \
    __value [es di];

#pragma aux outsw = ".286p" "push ds" "cld" "mov ds,di" "rep outsw" "pop ds" \
    __parm [di si] [cx] [dx] \
    __modify [cx di ax] \
    __value [di si];
#endif  

#pragma aux inp_words = \
        0xfc    /* cld  */  \
        0xf2 0x6d   /* rep insw ; Read them in */   \
        __parm __nomemory [ ES DI ] [ CX ] [ DX ]       \
        __modify __exact __nomemory [ CX DI ];

#pragma aux outp_words =\
        0xfc    /* cld          */  \
        0x1e    /* push ds      */  \
        0x8e 0xdf /*    mov ds,di   ; Change        */  \
        0xf2 0x6f /*    rep outsw   ; Write them out    */  \
        0x1f    /*  pop ds      */  \
        __parm __nomemory [ SI DI ] [ CX ] [ DX ]       \
        __modify __exact __nomemory [ CX SI ];

/* most thanks to aboyd... */
 /* dx = selector   ax = offset     cx = length in bytes */
int verr(void __far *ptr, int len);
#pragma aux verr =      \
        0x0f 0x00 0xe2      /* verr dx        */ \
        0x75 0x13       /* jnz verr_bad   */ \
        0xe3 0x0c       /* jcxz verr_ok   */ \
        0x49    /* dec cx         */ \
        0x03 0xc8       /* add cx,ax      */ \
        0x72 0x0c       /* jc verr_bad    */ \
        0x0f 0x03 0xC2      /* lsl ax,dx      */ \
        0x3b 0xc1       /* cmp ax,cx      */ \
        0x72 0x05       /* jb verr_bad    */ \
        /* verr_ok:       */ \
        0xb8 0x01 0x00      /* mov ax,#1      */ \
        0xeb 0x02       /* jmp verr_done  */ \
        /* verr_bad:      */ \
        0x33 0xc0       /* xor ax,ax      */ \
        /* verr_done:     */ \
        __parm    __nomemory [dx ax] [cx] \
        __modify __exact __nomemory [ax cx];


#pragma aux sldt = \
    0x0f 0x00 0xc0          /* sldt ax         */\
    __parm __nomemory [] \
    __modify __exact __nomemory [ax];

#pragma aux swapw = \
            "xchg al,ah" \
            __parm __nomemory [ax] \
            __modify __exact __nomemory [ax];      
            
#pragma aux swapl = \
            "xchg al,ah" \
            "xchg dl,dh" \
            "xchg ax,dx" \
            __parm __nomemory [dx ax] \
            __modify __exact __nomemory [dx ax];
            
 /* dx = selector   ax = offset     cx = length in bytes */
int verw(void __far *ptr, int len);
#pragma aux verw =      \
        0x0f 0x00 0xea      /* verw dx        */ \
        0x75 0x13       /* jnz verr_bad   */ \
        0xe3 0x0c       /* jcxz verr_ok   */ \
        0x49    /* dec cx         */ \
        0x03 0xc8       /* add cx,ax      */ \
        0x72 0x0c       /* jc verr_bad    */ \
        0x0f 0x03 0xC2      /* lsl ax,dx      */ \
        0x3b 0xc1       /* cmp ax,cx      */ \
        0x72 0x05       /* jb verr_bad    */ \
        /* verr_ok:       */ \
        0xb8 0x01 0x00      /* mov ax,#1      */ \
        0xeb 0x02       /* jmp verr_done  */ \
        /* verr_bad:      */ \
        0x33 0xc0       /* xor ax,ax      */ \
        /* verr_done:     */ \
        __parm    __nomemory [dx ax] [cx] \
        __modify __exact __nomemory [ax cx];

memcpy8(void far *a, const void far *b, int nbytes);
#pragma aux memcpy8 =\
    0x1e        /*  push ds */  \
    0x8e 0xda   /*  mov ds,dx */ \
    0xf3 0xa4   /*  rep movsb */ \
    0x1f        /*  pop ds */ \
    __parm __nomemory [es di] [dx si] [cx] \
    __modify __exact [si di cx];
    
memcpy16(void far *a, const void far *b, int nbytes);
#pragma aux memcpy16 =  \
    0x1e        /*  push ds */  \
    0x8e 0xda   /*  mov ds,dx */ \
    0xc1 0xe9 0x01      /* shr cx,1 */ \
    0xf3 0xa5   /* rep movsw */     \
    0x1f        /*  pop ds */ \
    __parm __nomemory [es di] [dx si] [cx] \
    __modify __exact [si di cx];
    

memcpy32(void far *a, const void far *b, int nbytes);
#pragma aux memcpy32 =  \
    0x1e        /*  push ds */  \
    0x8e 0xda   /*  mov ds,dx */ \
    0xc1 0xe9 0x02      /* shr cx,2 */  \
    0x66 0xf3 0xa5      /* 32: rep movsw */  \
    0x1f        /*  pop ds */ \
    __parm __nomemory [es di] [dx si] [cx] \
    __modify __exact [si di cx];

#endif            /* 386 */

#ifdef __cplusplus
};
#endif

#endif            /* sys_inline_h */
