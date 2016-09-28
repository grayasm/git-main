#ifndef __Driver_h__
#define __Driver_h__


#ifdef __cplusplus
extern "C" {
#endif

#pragma warning(disable:4201) // nameless struct/union
#include <wdm.h>

#ifdef __cplusplus
}
#endif


#define PAGEDCODE		code_seg("PAGE")
#define LOCKEDCODE		code_seg()
#define INITCODE		code_seg("INIT")

#define PAGEDDATA		data_seg("PAGEDATA")
#define LOCKEDDATA		data_seg()
#define INITDATA		data_seg("INITDATA")

#define arraysize(p)	(sizeof(p)/sizeof(p[0]))

#define DRIVERNAME		"DRIVERNAME"
#define LDRIVERNAME		L"DRIVERNAME"



#define VERMAJOR 2
#define VERMINOR 0
#define BUILD 0
#define PRODVER "2, 0, 0, 0\0"


#define GENERICAPI
#define GENERIC_EXPORT
extern BOOLEAN win98;

#endif // __Driver_h__