/*
	Ioctl.cpp - Ioctl functions.
	Copyright (C) 1999, 2000 by Walter Oney.
*/



#include "Ioctl.h"
#include "Pnp.h"


#pragma PAGEDCODE
GENERICAPI VOID GENERIC_EXPORT CleanupGenericExtension(PGENERIC_EXTENSION pdx)
{
	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	if (pdx->queues)
		ExFreePool(pdx->queues);

	pdx->queues = NULL;
	pdx->nqueues = 0;
}


#pragma LOCKEDCODE
GENERICAPI NTSTATUS GENERIC_EXPORT GenericCacheControlRequest(PGENERIC_EXTENSION pdx, PIRP Irp, PIRP* pIrp)
{
	ASSERT(KeGetCurrentIrql() <= DISPATCH_LEVEL);

	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));


	/*	Acquire the lock that guards pending IOCTL operations for this client. */
	KIRQL oldirql;
	KeAcquireSpinLock(&pdx->IoctlListLock, &oldirql);

	NTSTATUS status;

	if (*pIrp)
		status = STATUS_UNSUCCESSFUL;	// something already cached here
	else if (pdx->IoctlAbortStatus)
		status = pdx->IoctlAbortStatus;	// rejecting new IRPs for some reason
	else
	{
		/*	try to cache IRP

		Remember the IRP pointer cell and device extension pointers in
		DriverContext fields within the IRP. This is how our cancel routine
		knows which lock to claim and which pointer cell to nullify.
		It's important to set these fields *before* installing the
		cancel pointer.
		*/

		Irp->Tail.Overlay.DriverContext[0] = (PVOID)pIrp;
		Irp->Tail.Overlay.DriverContext[1] = (PVOID)pdx;
		*pIrp = Irp;

		/*	Install a cancel routine and check for this IRP having already
		been canceled.
		*/
		IoSetCancelRoutine(Irp, OnCancelPendingIoctl);
		if (Irp->Cancel && IoSetCancelRoutine(Irp, NULL))
			status = STATUS_CANCELLED; // already cancelled

									   /*	Put this IRP on our list of pending ICTLs. Note that our
									   cancel routine, if running, will be waiting for the spin
									   lock before completing the IRP.
									   */
		else
		{
			// try to cache IRP
			IoMarkIrpPending(Irp);
			status = STATUS_PENDING;
			InsertTailList(&pdx->PendingIoctlList, &Irp->Tail.Overlay.ListEntry);
		}
	}

	KeReleaseSpinLock(&pdx->IoctlListLock, oldirql);
	return status;

} // GenericCacheControlRequests


#pragma PAGEDCODE
GENERICAPI VOID GENERIC_EXPORT GenericCleanupAllRequests(PGENERIC_EXTENSION pdx, PFILE_OBJECT fop, NTSTATUS status)
{
	PAGED_CODE();

	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	CleanupAllRequests(pdx->queues, pdx->nqueues, fop, status);
	GenericCleanupControlRequests(pdx, status, fop);
}


#pragma LOCKEDCODE
GENERICAPI VOID GENERIC_EXPORT GenericCleanupControlRequests(PGENERIC_EXTENSION pdx, NTSTATUS status, PFILE_OBJECT fop)
{
	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	if (!(pdx->Flags & GENERIC_PENDING_IOCTLS))
		return; // didn't signup for pending ioctl service!

	LIST_ENTRY cancellist;
	InitializeListHead(&cancellist);

	/*	Create a list of IRPs that belong to the same file object. */
	KIRQL oldirql;
	KeAcquireSpinLock(&pdx->IoctlListLock, &oldirql);

	PLIST_ENTRY first = &pdx->PendingIoctlList;
	PLIST_ENTRY next;

	for (next = first->Flink; next != first; )
	{
		PIRP Irp = CONTAINING_RECORD(next, IRP, Tail.Overlay.ListEntry);
		PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

		/*	Follow the chain to the next IRP now (so that the next iteration
		of the loop is properly setup whether we dequeue this IRP or not)
		*/
		PLIST_ENTRY current = next;
		next = next->Flink;

		/*	Skip this IRP if it's not for the same file object as the
		current IRP_MJ_CLEANUP.
		*/
		if (fop && stack->FileObject != fop)
			continue;

		/*	Set the CancelRoutine pointer to NULL and remove the IRP from
		the queue.
		*/
		if (!IoSetCancelRoutine(Irp, NULL))
			continue;

		PIRP* pIrp = (PIRP*)Irp->Tail.Overlay.DriverContext[0];
		*pIrp = NULL;
		RemoveEntryList(current);
		InsertTailList(&cancellist, current);
	}

	/*	Release the spin lock. We're about to undertake a potentially
	time-consuming operation that might conceivably result in a
	deadlock if we keep the lock.
	*/
	KeReleaseSpinLock(&pdx->IoctlListLock, oldirql);

	/*	Complete the selected requests.	*/
	while (!IsListEmpty(&cancellist))
	{
		// cancel selected requests
		next = RemoveHeadList(&cancellist);
		PIRP Irp = CONTAINING_RECORD(next, IRP, Tail.Overlay.ListEntry);
		Irp->IoStatus.Status = STATUS_CANCELLED;
		IoCompleteRequest(Irp, IO_NO_INCREMENT);
	}

} // GenericCleanupControlRequests


#pragma LOCKEDCODE
GENERICAPI PVOID GENERIC_EXPORT GenericGetSystemAddressForMdl(PMDL mdl)
{
	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	if (!mdl)
		return NULL;

	CSHORT oldfail = mdl->MdlFlags & MDL_MAPPING_CAN_FAIL;
	mdl->MdlFlags |= MDL_MAPPING_CAN_FAIL;

	PVOID address = MmMapLockedPages(mdl, KernelMode);

	if (!oldfail)
		mdl->MdlFlags &= ~MDL_MAPPING_CAN_FAIL;

	return address;
}


#pragma LOCKEDCODE
GENERICAPI ULONG GENERIC_EXPORT GenericGetVersion()
{
	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	return (VERMAJOR << 16) | VERMINOR;
}


#pragma LOCKEDCODE
GENERICAPI PIRP GENERIC_EXPORT GenericUncacheControlRequest(PGENERIC_EXTENSION pdx, PIRP* pIrp)
{
	ASSERT(KeGetCurrentIrql() <= DISPATCH_LEVEL);

	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	if (!(pdx->Flags & GENERIC_PENDING_IOCTLS))
		return NULL;

	KIRQL oldirql;
	KeAcquireSpinLock(&pdx->IoctlListLock, &oldirql);

	/*	Uncache the request. Once we claim the spin lock, it's not necessary
	to further synchronize access to the pointer cell.
	*/
	PIRP Irp = *pIrp;
	*pIrp = NULL;

	if (Irp)
	{
		// an IRP was cached

		/*	Clear the cancel pointer for this IRP. Since both we and the
		completion routine use a spin lock, it cannot happen that this
		IRP pointer is suddenly invalid but the cache pointer cell
		wasn't already NULL.
		*/
		if (IoSetCancelRoutine(Irp, NULL))
		{
			RemoveEntryList(&Irp->Tail.Overlay.ListEntry); // uncache the IRP
		}
		else
		{
			Irp = NULL; // currently being cancelled
		}
	}

	KeReleaseSpinLock(&pdx->IoctlListLock, oldirql);
	return Irp;
} // GenericUncacheControlRequest


#pragma PAGEDCODE
GENERICAPI ULONG GENERIC_EXPORT GetSizeofGenericExtension()
{
	PAGED_CODE();

	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	ULONG size = (sizeof(GENERIC_EXTENSION) + 7) & ~7;
	return size;
}


#pragma PAGEDCODE
GENERICAPI NTSTATUS GENERIC_EXPORT InitializeGenericExtension(PGENERIC_EXTENSION pdx, PGENERIC_INIT_STRUCT isp)
{
	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	if (isp->Size < FIELD_OFFSET(GENERIC_INIT_STRUCT, Flags) ||
		!isp->DeviceObject ||
		!isp->Ldo ||
		!isp->Pdo ||
		!isp->StartDevice ||
		!isp->StopDevice ||
		!isp->RemoveDevice ||
		isp->DeviceQueue && !isp->StartIo)

		return STATUS_INVALID_PARAMETER;


	RtlZeroMemory(pdx, sizeof(GENERIC_EXTENSION));

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
		IoInitializeRemoveLock(pdx->RemoveLock, 0, 0, 0);

	pdx->state = STOPPED;

	pdx->devpower = PowerDeviceD0;
	pdx->syspower = PowerSystemWorking;
	POWER_STATE state;
	state.DeviceState = PowerDeviceD0;
	PoSetPowerState(pdx->DeviceObject, DevicePowerState, state);

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
		pdx->queues = (PDEVQUEUE*)ExAllocatePool(NonPagedPool, isp->NumberOfQueues * sizeof(PDEVQUEUE));
		if (!pdx->queues)
			return STATUS_INSUFFICIENT_RESOURCES;

		for (ULONG i = 0; i < isp->NumberOfQueues; ++i)
		{
			// for each queue
			pdx->queues[i] = isp->Queues[i].DeviceQueue;
			InitializeQueue(pdx->queues[i], isp->Queues[i].StartIo);
		}
	}
	else if (isp->DeviceQueue)
	{
		// single queue
		pdx->nqueues = 1;
		pdx->queues = (PDEVQUEUE*)ExAllocatePool(NonPagedPool, sizeof(PDEVQUEUE));
		if (!pdx->queues)
			return STATUS_INSUFFICIENT_RESOURCES;
		pdx->queues[0] = isp->DeviceQueue;
		InitializeQueue(pdx->queues[0], isp->StartIo);
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
		strcpy(pdx->DebugName, "GENERIC");
	else
	{
		ANSI_STRING asname = { 0, sizeof(pdx->DebugName) - 1, pdx->DebugName };
		RtlUnicodeStringToAnsiString(&asname, &isp->DebugName, FALSE);
		pdx->DebugName[asname.Length] = 0;
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

	InitializeListHead(&pdx->PendingIoctlList);
	pdx->IoctlAbortStatus = 0;
	KeInitializeSpinLock(&pdx->IoctlListLock);

	/*	Initialize to manage registered device interfaces.	*/

	KeInitializeEvent(&pdx->iflock, SynchronizationEvent, TRUE);
	InitializeListHead(&pdx->iflist);

	/*	Indicate we handle power IRPs at PASSIVE_LEVEL.	*/
	pdx->DeviceObject->Flags |= DO_POWER_PAGABLE;

	KdPrint(("GENERIC - Initializing for %s\n", pdx->DebugName));


	/*	If device honors paging-path notifications, initialize a synchronization
	event in the signalled state to act as a simple mutex (SP-7).
	*/

	if (pdx->Flags & GENERIC_USAGE_PAGING)
		KeInitializeEvent(&pdx->evPagingPath, SynchronizationEvent, TRUE);

	/*	If requested to do so, register an AutoLaunch interface.	*/

	if (pdx->Flags & GENERIC_AUTOLAUNCH)
		GenericRegisterInterface(pdx, &GUID_AUTOLAUNCH_NOTIFY);

	/*	Register a power management interface.	*/
	GenericRegisterInterface(pdx, &GUID_GENERIC_POWER);


	return STATUS_SUCCESS;
} // InitializeGenericExtension


#pragma LOCKEDCODE
VOID OnCancelPendingIoctl(PDEVICE_OBJECT junk, PIRP Irp)
{
	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	KIRQL oldirql = Irp->CancelIrql;
	IoReleaseCancelSpinLock(DISPATCH_LEVEL);

	/*	Remove the IRP from the pending IOCTL list. Also nullify the pointer cell
	that points to this IRP. The following weird possibility exists:

	1. Someone calls IoCancelIrp from this IRP.
	2. Someone calls UncacheControlRequest for this pointer cell, and it
	gets to the point of calling IoSetCancelRoutine, whereupon it sees
	that IoCancelIrp has already nulled the cancel pointer. It
	releases the spin lock and returns NULL to its caller.
	3. Someone calls CacheControlRequest for this pointer cell. It
	acquires the spin lock and sees that the pointer cell is NULL
	(from step 2), so it caches a new IRP and releases the spin lock.
	4. We acquire the spin lock.

	At this point, we need to be careful how we nullify the pointer cell
	to avoid wiping out what happened in step 3. The hypothetical other IRP
	cannot be at the same address as this one because we haven't completed
	this one yet.
	*/

	PIRP* pIrp = (PIRP*)Irp->Tail.Overlay.DriverContext[0];
	PGENERIC_EXTENSION pdx = (PGENERIC_EXTENSION)Irp->Tail.Overlay.DriverContext[1];

	KeAcquireSpinLockAtDpcLevel(&pdx->IoctlListLock);
	RemoveEntryList(&Irp->Tail.Overlay.ListEntry);

	if (*pIrp == Irp)
		*pIrp = NULL;	// no need for interlocked operation here

	KeReleaseSpinLock(&pdx->IoctlListLock, oldirql);

	/*	Complete the IRP.	*/
	Irp->IoStatus.Status = STATUS_CANCELLED;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
} // OnCancelPendingIoctl


#pragma PAGEDCODE
VOID AbortPendingIoctls(PGENERIC_EXTENSION pdx, NTSTATUS status)
{
	PAGED_CODE();

	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	if (!(pdx->Flags & GENERIC_PENDING_IOCTLS))
		return;

	InterlockedExchange(&pdx->IoctlAbortStatus, status);
	GenericCleanupControlRequests(pdx, status, NULL);
}
