/*
	IOCTL header file.
	Copyright (C) 1999, 2000 by Walter Oney.
*/


#ifndef __Ioctl_h__
#define __Ioctl_h__


#include "Driver.h"
#include "Device.h"


#include <InitGuid.h>
DEFINE_GUID(GUID_AUTOLAUNCH_NOTIFY, 0xba4ec740, 0xda8b, 0x11d2, 0x81, 0xb5, 0x0, 0xc0, 0x4f, 0xa3, 0x30, 0xa6);



#define GENERIC_AUTOLAUNCH			0x00000001  // register for AutoLaunch
#define GENERIC_USAGE_PAGING		0x00000002  // device supports DeviceUsageTypePaging
#define GENERIC_USAGE_DUMP			0x00000004	// device supports DeviceUsageTypeDumpFile
#define GENERIC_USAGE_HIBERNATE		0x00000008	// device supports DeviceUsageTypeHibernation
#define GENERIC_PENDING_IOCTLS		0x00000010	// driver may cache asynchronous IOCTLs
#define GENERIC_SURPRISE_REMOVAL_OK	0x00000020	// surprise removal of device is okay
#define GENERIC_IDLE_DETECT			0x00000040	// device supports generic idle detection scheme
#define GENERIC_CLIENT_FLAGS		0x0000007F	// mask to select client-controllable flags



/*	Enumeration for "wf" argument to GenericWakeupControl.	*/

enum WAKEFUNCTION
{
	EnableWakeup,				// enable system wakeup
	DisableWakeup,				// disable system wakeup
	ManageWaitWake,				// request or cancel WAIT_WAKE_IRP, as appropriate
	CancelWaitWake,				// unconditionally cancel WAIT_WAKE
	TestWaitWake				// test whether WAIT_WAKE enabled (ver 1.3)
};


/*	Exported functions.	*/
GENERICAPI VOID		GENERIC_EXPORT CleanupGenericExtension(PGENERIC_EXTENSION pdx); // 1.3
GENERICAPI NTSTATUS	GENERIC_EXPORT GenericCacheControlRequest(PGENERIC_EXTENSION pdx, PIRP Irp, PIRP* pIrp);
GENERICAPI VOID		GENERIC_EXPORT GenericCleanupAllRequests(PGENERIC_EXTENSION pdx, PFILE_OBJECT fop, NTSTATUS status);
GENERICAPI VOID		GENERIC_EXPORT GenericCleanupControlRequests(PGENERIC_EXTENSION pdx, NTSTATUS status, PFILE_OBJECT fop);
GENERICAPI PVOID	GENERIC_EXPORT GenericGetSystemAddressForMdl(PMDL mdl);
GENERICAPI ULONG	GENERIC_EXPORT GenericGetVersion(); // 1.3
GENERICAPI PIRP		GENERIC_EXPORT GenericUncacheControlRequest(PGENERIC_EXTENSION pdx, PIRP* pIrp);
GENERICAPI ULONG	GENERIC_EXPORT GetSizeofGenericExtension(VOID);
GENERICAPI NTSTATUS	GENERIC_EXPORT InitializeGenericExtension(PGENERIC_EXTENSION, PGENERIC_INIT_STRUCT);


VOID OnCancelPendingIoctl(PDEVICE_OBJECT junk, PIRP Irp);
VOID AbortPendingIoctls(PGENERIC_EXTENSION pdx, NTSTATUS status);


#endif // __Ioctl_h__
