/*
 *  mous_msg.h "Private" Definitions for the mouse driver
 *
 *  Copyright by QNX Software Systems Limited 1990-1993. All rights reserved.
 */
#ifndef __MOUS_MSG_H_INCLUDED

#ifndef __TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#ifndef __MOUSE_H_INCLUDED
 #include <sys/mouse.h>
#endif

#include <sys/dev.h>

#if __WATCOMC__ > 1000
#pragma pack(__push,1);
#else
#pragma pack(1);
#endif

/*
 *  Message types
 */

#define _MOUSE_OPEN                     0x03A0
#define _MOUSE_CLOSE                            0x03A1
#define _MOUSE_READ                     0x03A2
#define _MOUSE_FLUSH                            0x03A3
#define _MOUSE_GET                      0x03A4
#define _MOUSE_SET                      0x03A5
#define _MOUSE_STRANS                           0x03A6
#define _MOUSE_GTRANS                           0x03A7
#define _MOUSE_GETIDEV                          0x03A8

/*
 * Message formats
 */

struct _mouse_open {
    msg_t                   type;
    unsigned short          mode;
    short                   fd;
    short                       zero;
    char                    kbd_name[32];
    } ;

struct _mouse_open_reply {
    msg_t                   status;
    unsigned short          handle;
    long                    buttons;
    short                       zero[2];
    } ;

struct _mouse_set {
    msg_t                   type;
    unsigned short          handle;
    unsigned short          mode;
    unsigned short          threshold;
    unsigned short          gain;
    unsigned short          zero[13];
    } ;

struct _mouse_set_reply {
    msg_t                   status;
    unsigned short          zero[3];
    } ;

struct _mouse_get {
    msg_t                   type;
    unsigned short          handle;
    unsigned short          zero[2];
    } ;

struct _mouse_get_reply {
    msg_t                   status;
    char                    name[32];
    unsigned short          mode;
    unsigned short          threshold;
    unsigned short          gain;
    unsigned short          zero[13];
    } ;

struct  _touch_transformation {
        long    xx, xy;         /* fixed point rotation matrix, 16 bit frac */
        long    yx, yy;
        short   tx, ty;
};

struct _mouse_strans {
    msg_t                               type;
        struct _touch_transformation    tmatrix;
        unsigned short                                  zero[5];
    } ;

struct _mouse_strans_reply {
    msg_t                   status;
        unsigned short                  zero[3];
    } ;

struct _mouse_gtrans {
    msg_t                   type;
        unsigned short                  zero[3];
    } ;

struct _mouse_gtrans_reply {
    msg_t                                       status;
        struct _touch_transformation    tmatrix;
        unsigned short                                  zero[1];
    } ;

struct _mouse_close {
    msg_t                   type;
    unsigned short          handle;
    unsigned short          zero[2];
    } ;

struct _mouse_close_reply {
    msg_t                   status;
    unsigned short          zero[2];
    } ;

struct _mouse_read {
    msg_t                   type;
    unsigned short          handle;
    short                   nevents;
    mpid_t                   proxy;
    mpid_t                   proxy_spare;
    unsigned short          zero[3];
    } ;

struct _mouse_read_reply {
    msg_t                   status;
    unsigned short          nevents;
    unsigned short          empty;
    unsigned short          zero;
    struct mouse_event      data[1]; /* variable length */
    } ;

struct _mouse_flush {
    msg_t                   type;
    unsigned short          handle;
    unsigned short          zero[2];
    } ;

struct _mouse_flush_reply {
    msg_t                   status;
    unsigned short          zero[2];
    } ;
        
struct _mouse_getidev {
    msg_t                   type;
    unsigned short          zero[6];
    } ;

struct _mouse_getidev_reply {
    msg_t                   status;
        struct _dev_info_entry  dinfo;
    unsigned short          zero[2];
    } ;
        


#if __WATCOMC__ > 1000
#pragma pack(__pop);
#else
#pragma pack();
#endif

#define __MOUS_MSG_H_INCLUDED
#endif
