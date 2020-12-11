/*
 *  interact.h
 *
 *  Copyright by QNX Software Systems Limited 1994. All rights reserved.
 */

#ifndef _SYS_INTERACT_H_INCLUDED
#define _SYS_INTERACT_H_INCLUDED

#ifndef _IOCTL_H_INCLUDED
 #include <sys/ioctl.h>
#endif

#pragma pack(1);

#define _INTERACT_TYPE_POINTER       0x0001          /* pointer packet */
#define _INTERACT_TYPE_KEY           0x0002          /* keyboard packet */
#define _INTERACT_TYPE_FEEDBACK      0x0004          /* LED feedback */

struct _interact_device {
        void                                    *handle;
    unsigned short          type;
    unsigned short          feedback;
};

#define MAX_DEVS_PER_MGR        30
struct _interact_mgr {
        int                                             id;
        struct _interact_device devices[MAX_DEVS_PER_MGR];
};


#define _INTERACT_FEEDBACK_LED       0x00000001      /* LED displays */
#define _INTERACT_FEEDBACK_BELL      0x00000002      /* Freq, vol, dur */
#define _INTERACT_FEEDBACK_INTEGER   0x00000004      /* Integer display */
#define _INTERACT_FEEDBACK_STRING    0x00000008      /* string display */


/*
 * _INTERACTTYPE                'I' 0-1
 * _INTERACT_TYPE_POINTER       'I' 2-9
 * _INTERACT_TYPE_KEY           'I' 10-19
 * _INTERACT_FEEDBACK           'I' 100
 * _INTERACT_FEEDBACKLED        'I' 101-104
 * _INTERACT_FEEDBACKBELL       'I' 105-109
 * _INTERACT_FEEDBACKINTEGER    'I' 110-114
 * _INTERACT_FEEDBACKSTRING     'I' 115-119
 */

#define _INTERACTTYPE           _IOR('I', 0, struct _interact_device)
#define _INTERACTFEEDBACK       _IOR('I', 100, unsigned long)
#define _INTERACTASSOCIATE      _IOW('I', 20, char *conname)

#pragma pack();

#endif
