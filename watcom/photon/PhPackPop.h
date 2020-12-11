
#if defined(PH_PACKING_IS_ON)
	#undef PH_PACKING_IS_ON
#else
	#error PhPackPop.h without PhPack.h
#endif

#if defined(__QNXNTO__)
	#include <_packpop.h>
#else
	#if __WATCOMC__ > 1000
		#pragma pack(__pop)
	#else
		#pragma pack()
	#endif
#endif

