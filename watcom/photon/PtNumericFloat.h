/* PtNumericFloat.h - widget header file */

#ifndef __PT_NUMERIC_FLOAT_H_INCLUDED
#define __PT_NUMERIC_FLOAT_H_INCLUDED
	
#include <photon/PtNumeric.h>

#include <photon/PhPack.h>

#ifdef __cplusplus
extern "C" {
#endif

/* widget instance structure */
typedef struct numeric_float_widget{
	PtNumericWidget_t		numeric;
	double					increment;
	double					min;
	double					max;
	double					value;
	int						precision;
	PtCallbackList_t		*changed;
	long 					spare[2];
	double					d_spare;
}	PtNumericFloatWidget_t;

typedef struct PtNumericFloatCallback{
	double numeric_value;
}	PtNumericFloatCallback_t;

extern PtWidgetClassRef_t *PtNumericFloat;

#ifdef __cplusplus
};
#endif

#include <photon/PhPackPop.h>

#endif



