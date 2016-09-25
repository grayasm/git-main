
#ifndef __driver_h__
#define __driver_h__


#ifdef __cplusplus
extern "C" {
#endif

#include <ntddk.h>
#include <wdm.h>

#ifdef __cplusplus
}
#endif


#define PAGEDCODE	code_seg("PAGE")
#define LOCKEDCODE	code_seg()
#define INITCODE	code_seg("INIT")

#define PAGEDDATA	data_seg("PAGEDATA")
#define LOCKEDDATA	data_seg()
#define INITDATA	data_seg("INITDATA")


#endif // __driver_h__
