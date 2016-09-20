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


#pragma LOCKEDCODE
GENERICAPI ULONG GENERIC_EXPORT GenericGetVersion()
{
	return (VERMAJOR << 16) | VERMINOR;
}


#pragma LOCKEDCODE
GENERICAPI PVOID GENERIC_EXPORT GenericGetSystemAddressForMdl(PMDL mdl)
{
	if (!mdl)
		return NULL;

	CSHORT oldfail = mdl->MdlFlags & MDL_MAPPING_CAN_FAIL;
	mdl->MdlFlags |= MDL_MAPPING_CAN_FAIL;

	PVOID address = MmMapLockedPages(mdl, KernelMode);

	if (!oldfail)
		mdl->MdlFlags &= ~MDL_MAPPING_CAN_FAIL;

	return address;
}


#pragma PAGEDCODE
GENERICAPI ULONG GENERIC_EXPORT GetSizeofGenericExtension()
{
	PAGED_CODE();
	ULONG size = (sizeof(GENERIC_EXTENSION) + 7) & ~7;
	return size;
}


#pragma PAGEDCODE
GENERICAPI NTSTATUS GENERIC_EXPORT InitializeGenericExtension(PGENERIC_EXTENSION pdx, PGENERIC_INIT_STRUCT isp)
{
	if (isp->Size < FIELD_OFFSET(GENERIC_INIT_STRUCT, Flags) ||
		!isp->DeviceObject ||
		!isp->Ldo	||
		!isp->Pdo	||
		!isp->StartDevice	||
		!isp->StopDevice	||
		!isp->RemoveDevice	||
		isp->DeviceQueue && !isp->StartIo)

		return STATUS_INVALID_PARAMETER;

	
	RtlZeroMemory (pdx, sizeof(GENERIC_EXTENSION));

	pdx->DeviceObject = isp->DeviceObject;
	pdx->LowerDeviceObject = isp->Ldo;
	pdx->Pdo = isp->Pdo;
	pdx->StartDevice = isp->StartDevice;
	pdx->StopDevice = isp->StopDevice;
	pdx->RemoveDevice = isp->RemoveDevice;

	if (isp->Size >= FIELD_OFFSET(GENERIC_INIT_STRUCT, OkayToRemove) + sizeof(PQUERYFUNCTION))
	{
		pdx->OkayToStop = isp->OkayToStop;
		pdx->OkayToRemove = isp->OkayToRemove;
	}


	if ((pdx->RemoveLock = isp->RemoveLock))
		IoInitializeRemoveLock (pdx->RemoveLock, 0, 0, 0);

	pdx->state = STOPPED;

	pdx->devpower = PowerDeviceD0;
	pdx->syspower = PowerSystemWorking;
	POWER_STATE state;
	state.DeviceState = PowerDeviceD0;
	PoSetPowerState (pdx->DeviceObject, DevicePowerState, state);

	/* In version 3.1, I added support for multiple IRP queues.	*/
	if (isp->Size >= FIELD_OFFSET(GENERIC_INIT_STRUCT, NumberOfQueues) + sizeof(ULONG) &&
		isp->NumberOfQueues)
	{
		// multiple queues
		if (isp->DeviceQueue || isp->StartIo)
			return STATUS_INVALID_PARAMETER;  // can't mix new and old ways of identify queues

		if (isp->Size < FIELD_OFFSET(GENERIC_INIT_STRUCT, Queues) + isp->NumberOfQueues * 2 * sizeof(PVOID))
			return STATUS_INVALID_PARAMETER;  // init structure not big enough

		for (ULONG i = 0; i < isp->NumberOfQueues; ++i)
			if (!isp->Queues[i].DeviceQueue || !isp->Queues[i].StartIo)
				return STATUS_INVALID_PARAMETER; // none of the entries can be NULL

		pdx->nqueues = isp->NumberOfQueues;
		pdx->queues = (PDEVQUEUE*) ExAllocatePool(NonPagedPool, isp->NumberOfQueues * sizeof(PDEVQUEUE));
		if (!pdx->queues)
			return STATUS_INSUFFICIENT_RESOURCES;

		for (ULONG i = 0; i < isp->NumberOfQueues; ++i)
		{
			// for each queue
			pdx->queues[i] = isp->Queues[i].DeviceQueue;
			InitializeQueue (pdx->queues[i], isp->Queues[i].StartIo);
		}
	}
	else if (isp->DeviceQueue)
	{
		// single queue
		pdx->nqueues = 1;
		pdx->queues = (PDEVQUEUE*) ExAllocatePool (NonPagedPool, sizeof(PDEVQUEUE));
		if (!pdx->queues)
			return STATUS_INSUFFICIENT_RESOURCES;
		pdx->queues[0] = isp->DeviceQueue;
		InitializeQueue (pdx->queues[0], isp->StartIo);
	}

	/*	In version 1.9, I added support for FlushPendingIo.
		In version 1.10, GetDevicePowerState.
	*/

	if (isp->Size >= FIELD_OFFSET(GENERIC_INIT_STRUCT, Queues))
	{
		// additional reserved fields
		pdx->FlushPendingIo = isp->FlushPendingIo;
		pdx->GetDevicePowerState = isp->GetDevicePowerState;
	}

	/*	Capture the mini-driver name for messages. This needs to be in ANSI
		because unicode conversions at or above DISPATCH_LEVEL are not allowed.
		In retrospect, I should have made the field in the INIT struct be
		in ANSI to start with ...
	*/

	if (!isp->DebugName.Length)
		strcpy (pdx->DebugName, "GENERIC");
	else
	{
		ANSI_STRING asname = {0, sizeof(pdx->DebugName) - 1, pdx->DebugName };
		RtlUnicodeStringToAnsiString (&asname, &isp->DebugName, FALSE);
		pdx->DebugName [asname.Length] = 0;
	}

	if (isp->Size >= FIELD_OFFSET(GENERIC_INIT_STRUCT, Flags) + sizeof(ULONG))
		pdx->Flags = isp->Flags & GENERIC_CLIENT_FLAGS;

	if (isp->Size >= FIELD_OFFSET(GENERIC_INIT_STRUCT, RestoreDeviceContext) + sizeof(PCONTEXTFUNCTION))
	{
		// get power functions
		pdx->QueryPower = isp->QueryPower;
		pdx->SaveDeviceContext = isp->SaveDeviceContext;
		pdx->RestoreDeviceContext = isp->RestoreDeviceContext;
	}

	if (isp->Size >= FIELD_OFFSET(GENERIC_INIT_STRUCT, PerfBoundary) + sizeof(DEVICE_POWER_STATE))
		pdx->PerfBoundary = isp->PerfBoundary;
	else 
		pdx->PerfBoundary = PowerDeviceUnspecified;

	
	if (pdx->PerfBoundary == PowerDeviceUnspecified)
		pdx->PerfBoundary = PowerDeviceMaximum;  // inhibit POWER_SEQUENCE optimization


	/*	Initialize variables related to asynchronous IOCTL management.
		In version 2.0, this is now always done rather than depending on a flag
		in the init struct.
	*/

	InitializeListHead (&pdx->PendingIoctlList);
	pdx->IoctlAbortStatus = 0;
	KeInitializeSpinLock (&pdx->IoctlListLock);

	/*	Initialize to manage registered device interfaces.	*/

	KeInitializeEvent (&pdx->iflock, SynchronizationEvent, TRUE);
	InitializeListHead (&pdx->iflist);

	/*	Indicate we handle power IRPs at PASSIVE_LEVEL.	*/
	pdx->DeviceObject->Flags |= DO_POWER_PAGABLE;

	KdPrint (("GENERIC - Initializing for %s\n", pdx->DebugName));


	/*	If device honors paging-path notifications, initialize a synchronization
		event in the signalled state to act as a simple mutex (SP-7).
	*/

	if (pdx->Flags & GENERIC_USAGE_PAGING)
		KeInitializeEvent(&pdx->evPagingPath, SynchronizationEvent, TRUE);

	/*	If requested to do so, register an AutoLaunch interface.	*/
	
	if (pdx->Flags & GENERIC_AUTOLAUNCH)
		GenericRegisterInterface (pdx, &GUID_AUTOLAUNCH_NOTIFY);

	/*	Register a power management interface.	*/
	GenericRegisterInterface(pdx, &GUID_GENERIC_POWER);


#ifdef _X86_
	win98 = IsWin98 ();
#endif

	return STATUS_SUCCESS;
} // InitializeGenericExtension



#pragma LOCKEDCODE
NTSTATUS OnRequestComplete(PDEVICE_OBJECT junk, PIRP Irp, PKEVENT pev)
{
	KeSetEvent (pev, 0, FALSE);
	return STATUS_MORE_PROCESSING_REQUIRED;
}


#pragma PAGEDCODE
GENERICAPI BOOLEAN GENERIC_EXPORT IsWin98()
{
#ifdef _X86_
	return !IoIsWdmVersionAvailable(1, 0x10);
#else
	return FALSE;
#endif
}


#pragma LOCKEDCODE		// force inline functions into locked code
