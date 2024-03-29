/*
	stddcls.h -- Precompiled headers for WDM drivers
	Copyright (C) 1999, 2000 by Walter Oney
*/



#ifdef __cplusplus
extern "C" {
#endif

#pragma warning(disable:4201)	// nameless struct/union
#define DEPRECATE_DDK_FUNCTIONS 1

#include <ntddk.h>
#include <stdio.h>

#ifdef __cplusplus
	}
#endif

#define PAGEDCODE	code_seg("PAGE")
#define LOCKEDCODE	code_seg()
#define INITCODE	code_seg("INIT")

#define PAGEDDATA	data_seg("PAGEDATA")
#define LOCKEDDATA	data_seg()
#define INITDATA	data_seg("INITDATA")

#define arraysize(p) (sizeof(p)/sizeof((p)[0]))

#if !DBG
#pragma warning(disable:4390)	// empty controlled stmt [e.g., if() KdPrint();]
#endif

#if DBG && defined(_AMD64_) // defined(_X86_)
	#undef ASSERT
	#define ASSERT(e) if(!(e)){DbgPrint("Assertion failure in "\
	__FILE__ ", line %d: " #e "\n", __LINE__);\
  }
#endif

// _asm int 3\