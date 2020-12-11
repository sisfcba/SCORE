
#ifndef __PT_PULSE_DELIVER_H_INCLUDED
#define __PT_PULSE_DELIVER_H_INCLUDED

#if defined(__QNXNTO__)
	#include <sys/neutrino.h>
#else
	#include <sys/types.h>
	#include <sys/kernel.h>
#endif

#if defined(__QNXNTO__)
	#ifndef __PT_T_H_INCLUDED
   	 	typedef struct sigevent PtPulseMsg_t;
	#endif
	#define PtPulseDeliver( rcvid, pulse ) MsgDeliverEvent( rcvid, pulse )
#else
	#ifndef __PT_T_H_INCLUDED
	typedef pid_t PtPulseMsg_t;
	#endif
	#define PtPulseDeliver( rcvid, pulse ) ( (void)(rcvid), Trigger( *(pulse) ) )
#endif

#endif
