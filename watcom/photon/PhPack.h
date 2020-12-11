
#if defined(PH_PACKING_IS_ON)
	#error PhPack.h included twice
#else
	#define PH_PACKING_IS_ON
#endif

#if defined(__QNXNTO__)
	#include <_pack64.h>
#else
	#if __WATCOMC__ > 1000
		#pragma pack(__push,1)
	#else
		#pragma pack(1)
	#endif
#endif

