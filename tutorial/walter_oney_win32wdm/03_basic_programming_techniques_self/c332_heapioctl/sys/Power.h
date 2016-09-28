#ifndef __Power_h__
#define __Power_h__


#include "Driver.h"
#include "Device.h"
#include "Ioctl.h"
#include "Pnp.h"



#ifndef CTL_CODE
#pragma message("CTL_CODE undefined. Include winioctl.h or wdm.h")
#endif


/*	IOCTL interface for generic power management.	*/

#define IOCTL_GET_POWERINFO	CTL_CODE(FILE_DEVICE_UNKNOWN, 0xFF0, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_SET_POWERINFO CTL_CODE(FILE_DEVICE_UNKNOWN, 0xFF1, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_IDLENOW		CTL_CODE(FILE_DEVICE_UNKNOWN, 0xFF2, METHOD_NEITHER,  FILE_ANY_ACCESS)


typedef struct _POWERINFO
{
	unsigned long ulConservation;	// idle timeout in conservation mode
	unsigned long ulPerformance;	// idle timeout in performance mode
	unsigned char bWakeup;			// TRUE if wakeup feature should be armed
	unsigned char bCanWake;			// device capable of waking system
	unsigned char bCanIdle;			// device can be idled
	unsigned char bIdle;			// device is idle right now
} POWERINFO, *PPOWERINFO;


/*	Devices that use GENERIC.SYS for power management register an interface
with the following GUID:

{894A7461-A033-11d2-821E-444553540000}
*/
#include <InitGuid.h>
DEFINE_GUID(GUID_GENERIC_POWER, 0x894a7461, 0xa033, 0x11d2, 0x82, 0x1e, 0x44, 0x45, 0x53, 0x54, 0x0, 0x0);


VOID AdjustSpecialFileCounter(PGENERIC_EXTENSION pdx, BOOLEAN inpath, PLONG counter);
NTSTATUS GetPowerInfoFromRegistry(PGENERIC_EXTENSION pdx, PPOWERINFO pip);
NTSTATUS ImplementPowerPolicy(PGENERIC_EXTENSION pdx, PPOWERINFO pip);
BOOLEAN OkayToRemove(PGENERIC_EXTENSION pdx);
BOOLEAN OkayToStop(PGENERIC_EXTENSION pdx);
NTSTATUS SendDeviceSetPower(PGENERIC_EXTENSION pdx, DEVICE_POWER_STATE state, BOOLEAN wait = FALSE);
NTSTATUS WritePowerInfoToRegistry(PGENERIC_EXTENSION pdx, PPOWERINFO pip);


GENERICAPI NTSTATUS GENERIC_EXPORT GenericDispatchPower(PGENERIC_EXTENSION, PIRP);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericHandlePowerIoctl(PGENERIC_EXTENSION pdx, PIRP Irp);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericIdleDevice(PGENERIC_EXTENSION pdx, DEVICE_POWER_STATE state, BOOLEAN wait = FALSE);
GENERICAPI VOID		GENERIC_EXPORT GenericMarkDeviceBusy(PGENERIC_EXTENSION);
GENERICAPI VOID		GENERIC_EXPORT GenericRegisterForIdleDetection(PGENERIC_EXTENSION, ULONG ConservationTimeout, ULONG PerformanceTimeout, DEVICE_POWER_STATE State);
GENERICAPI VOID		GENERIC_EXPORT GenericSaveRestoreComplete(PVOID context);
GENERICAPI NTSTATUS	GENERIC_EXPORT GenericWakeupControl(PGENERIC_EXTENSION pdx, enum WAKEFUNCTION wf);
GENERICAPI NTSTATUS GENERIC_EXPORT GenericWakeupFromIdle(PGENERIC_EXTENSION pdx, BOOLEAN wait = FALSE);





#endif // __Power_h__
