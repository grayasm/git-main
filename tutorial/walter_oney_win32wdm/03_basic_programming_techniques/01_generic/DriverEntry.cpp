/*
	Main program for GENERIC.SYS driver.
	Copyright (C) 1999 by Walter Oney
*/

#include "stddcls.h"
#include "driver.h"
#include "version.h"


#include <InitGuid.h>
DEFINE_GUID(GUID_AUTOLAUNCH_NOTIFY, 0xba4ec740, 0xda8b, 0x11d2, 0x81, 0xb5, 0x0, 0xc0, 0x4f, 0xa3, 0x30, 0xa6);

#include "GenericPower.h"

NTSTATUS OnRequestComplete(PDEVICE_OBJECT junk, PIRP Irp, PKEVENT pev);

BOOLEAN win98 = FALSE;


/*	DriverEntry is not used in a kernel-mode DLL such as this one.
	It's only here to satisfy the build script.
*/

#pragma PAGEDCODE
extern "C" NTSTATUS DriverEntry(PDEVICE_OBJECT, PUNICODE_STRING RegistryPath)
{
	return STATUS_SUCCESS;
}


//////////////////////////////////////////////////////////////////////////
/*	DllInitialize is called when this module is first loaded.
	This function was added in version 1.7, part of SP-9.
	Note that RegistryPath just names a bogus service key that doesn't
	necessarily exist -- HKLM\...\Services\Generic.
*/

#ifndef WIN98SAFE	// see comment in driver.h
#pragma PAGEDCODE
extern "C" NTSTATUS DllInitialize(PUNICODE_STRING RegistryPath)
{
	KdPrint(("GENERIC - DllInitialize\n"));
	// Determine addresses of version-dependent routines

#define GETADDRESS(n) \
	RtlInitUnicodeString(&name, L#n); \
	p##n = (t##n) MmGetSystemRoutineAddress(&name); 

	UNICODE_STRING name;
	return STATUS_SUCCESS;
}

/*	DllUnload is called when all references to this module disappear.
	This function was added in version 1.7, part of SP-9
*/

#pragma PAGEDCODE
extern "C" NTSTATUS DllUnload()
{
	KdPrint(("GENERIC - DllUnload\n"));
	return STATUS_SUCCESS;
}

#endif // WIN98SAFE
//////////////////////////////////////////////////////////////////////////


#pragma PAGEDCODE
GENERICAPI VOID GENERIC_EXPORT CleanupGenericExtension(PGENERIC_EXTENSION pdx)
{
	if (pdx->queues)
		ExFreePool(pdx->queues);

	pdx->queues = NULL;
	pdx->nqueues = 0;
}


#pragma LOCKEDCODE
NTSTATUS CompleteRequest(PIRP Irp, NTSTATUS status, ULONG_PTR info)
{
	Irp->IoStatus.Status = status;
	Irp->IoStatus.Information = info;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return status;
}


/*	Overload variant that doesn't change IoStatus.Information -- use
	this for most PnP requests.
*/

NTSTATUS CompleteRequest(PIRP Irp, NTSTATUS status)
{
	Irp->IoStatus.Status = status;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return status;
}


#pragma PAGEDCODE
NTSTATUS ForwardAndWait(PGENERIC_EXTENSION pdx, PIRP Irp)
{
	PAGED_CODE();

	KEVENT event;
	KeInitializeEvent(&event, NotificationEvent, FALSE);

	IoCopyCurrentIrpStackLocationToNext(Irp);
	IoSetCompletionRoutine(Irp, (PIO_COMPLETION_ROUTINE) OnRequestComplete,
		(PVOID) &event, TRUE, TRUE, TRUE);

	IoCallDriver(pdx->LowerDeviceObject, Irp);
	KeWaitForSingleObject(&event, Executive, KernelMode, FALSE, NULL);
	return Irp->IoStatus.Status;
}



