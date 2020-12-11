/* PtNumericInteger.h - widget header file */

#ifndef __PT_NUMERIC_INTEGER_H_INCLUDED
#define __PT_NUMERIC_INTEGER_H_INCLUDED
	
#include <photon/PtNumeric.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/* widget instance structure */
typedef struct numeric_integer_widget{
	PtNumericWidget_t	numeric;
	int				increment;
	long			min;
	long			max;
	long			value;
	PtCallbackList_t	*changed;
	int				flags;
	long 			spare[1];
}	PtNumericIntegerWidget_t;

typedef struct PtNumericIntegerCallback{
	int numeric_value;
}	PtNumericIntegerCallback_t;

extern PtWidgetClassRef_t *PtNumericInteger;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif



