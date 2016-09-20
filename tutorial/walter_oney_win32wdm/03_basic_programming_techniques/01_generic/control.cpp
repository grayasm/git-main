/*
	Pending IOCTL support for generic.sys
	Copyright (C) 1999 by Walter Oney.
*/

#include "stddcls.h"
#include "driver.h"

VOID OnCancelPendingIoctl(PDEVICE_OBJECT junk, PIRP Irp);


#pragma PAGEDCODE
VOID AbortPendingIoctls(PGENERIC_EXTENSION pdx, NTSTATUS status)
{
	PAGED_CODE();
	if (!(pdx->Flags & GENERIC_PENDING_IOCTLS))
		return;

	InterlockedExchange(&pdx->IoctlAbortStatus, status);
	GenericCleanupControlRequests(pdx, status, NULL);
}


#pragma LOCKEDCODE
GENERICAPI NTSTATUS GENERIC_EXPORT GenericCacheControlRequest(PGENERIC_EXTENSION pdx, PIRP Irp, PIRP* pIrp)
{
	ASSERT(KeGetCurrentIrql() <= DISPATCH_LEVEL);

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

		Irp->Tail.Overlay.DriverContext[0] = (PVOID) pIrp;
		Irp->Tail.Overlay.DriverContext[1] = (PVOID) pdx;
		*pIrp = Irp;

		/*	Install a cancel routine and check for this IRP having already
			been canceled. 
		*/
		IoSetCancelRoutine(Irp, OnCancelPendingIoctl);
		if(Irp->Cancel && IoSetCancelRoutine(Irp, NULL))
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
	CleanupAllRequests(pdx->queues, pdx->nqueues, fop, status);
	GenericCleanupControlRequests(pdx, status, fop);
}


#pragma LOCKEDCODE
GENERICAPI VOID GENERIC_EXPORT GenericCleanupControlRequests(PGENERIC_EXTENSION pdx, NTSTATUS status, PFILE_OBJECT fop)
{
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

		PIRP* pIrp = (PIRP*) Irp->Tail.Overlay.DriverContext[0];
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
GENERICAPI PIRP GENERIC_EXPORT GenericUncacheControlRequest(PGENERIC_EXTENSION pdx, PIRP* pIrp)
{
	ASSERT(KeGetCurrentIrql() <= DISPATCH_LEVEL);

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



#pragma LOCKEDCODE
VOID OnCancelPendingIoctl(PDEVICE_OBJECT junk, PIRP Irp)
{
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

	PIRP* pIrp = (PIRP*) Irp->Tail.Overlay.DriverContext[0];
	PGENERIC_EXTENSION pdx = (PGENERIC_EXTENSION) Irp->Tail.Overlay.DriverContext[1];

	KeAcquireSpinLockAtDpcLevel(&pdx->IoctlListLock);
	RemoveEntryList(&Irp->Tail.Overlay.ListEntry);

	if (*pIrp == Irp)
		*pIrp = NULL;	// no need for interlocked operation here

	KeReleaseSpinLock(&pdx->IoctlListLock, oldirql);

	/*	Complete the IRP.	*/
	Irp->IoStatus.Status = STATUS_CANCELLED;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
} // OnCancelPendingIoctl
