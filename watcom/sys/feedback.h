/*
 *  feedback.h
 *
 *  Copyright by QNX Software Systems Limited 1994. All rights reserved.
 */

#ifndef _SYS_FEEDBACK_H_INCLUDED
#define _SYS_FEEDBACK_H_INCLUDED

#ifndef _IOCTL_H_INCLUDED
 #include <sys/ioctl.h>
#endif

#pragma pack(1);

#define _FEEDBACK_LED_1             0x00000001
#define _FEEDBACK_LED_2             0x00000002
#define _FEEDBACK_LED_3             0x00000004
#define _FEEDBACK_LED_4             0x00000008
#define _FEEDBACK_LED_SCROLL        _FEEDBACK_LED_1
#define _FEEDBACK_LED_NUM           _FEEDBACK_LED_2
#define _FEEDBACK_LED_CAPS          _FEEDBACK_LED_3

struct _feedback_led {
        struct _interact_device type;
        int     value;
        int     mask;
};

struct _feedback_bell {
        struct _interact_device type;
    unsigned short          flags;              /* Flags */
    unsigned short          frequency;          /* In Hz, zero is rest */
    unsigned short          duration;           /* duration in ms */
    unsigned short          volume;             /* USHRT_MAX is full volume */
};

#define _FEEDBACK_BELL_FLAG_FREQ                0x0004
#define _FEEDBACK_BELL_FLAG_DURATION    0x0002
#define _FEEDBACK_BELL_FLAG_VOLUME              0x0001

#define _FEEDBACK_BELL_FLAG_FLUSH               0x0001      /* Flush pending bells */
#define _FEEDBACK_BELL_VOLUME_DFLT              (USHRT_MAX/2)

#define _FEEDBACK_STRING_MAX        255

#define _FEEDBACKSETLED         _IOW('I', 101, struct _feedback_led)
#define _FEEDBACKGETLED         _IOR('I', 102, struct _feedback_led)
#define _FEEDBACKGETLEDMASK             _IOR('I', 103, struct _feedback_led)
#define _FEEDBACKBELL           _IOW('I', 105, struct _feedback_bell)
#define _FEEDBACKINTEGER        _IOW('I', 110, long)
#define _FEEDBACKSTRING         _IOW("I", 115, char[_FEEDBACK_STRING_MAX])

#pragma pack();

#endif
