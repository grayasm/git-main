/*
	Custom IRP queuing support.
	Copyright (C) 1999 by Walter Oney.
*/

#include "stddcls.h"
#include "driver.h"


typedef struct _NOTIFY_CONTEXT
{
	PQNOTIFYFUNC notify;			// real notification function
	PVOID context;					// context arg for notification function
	LONG count;						// number of busy queues
} NOTIFY_CONTEXT, *PNOTIFY_CONTEXT;


VOID NotificationCallback(PNOTIFY_CONTEXT ctx);


GENERICAPI VOID GENERIC_EXPORT AbortRequests(PDEVQUEUE pdq, NTSTATUS status)
{
	pdq->abortstatus = status;
	CleanupRequests(pdq, NULL, status);
}


GENERICAPI VOID GENERIC_EXPORT AbortAllRequests(PDEVQUEUE* q, ULONG nq, NTSTATUS status)
{
	for (ULONG i = 0; i < nq; ++i)
		AbortRequests(q[i], status);
}

GENERICAPI VOID GENERIC_EXPORT AllowRequests(PDEVQUEUE pdq)
{
	pdq->abortstatus = STATUS_SUCCESS;
}

GENERICAPI VOID GENERIC_EXPORT AllowAllRequests(PDEVQUEUE* q, ULONG nq)
{
	for (ULONG i = 0; i < nq; ++i)
		AllowRequests(q[i]);
}

GENERICAPI NTSTATUS GENERIC_EXPORT AreRequestsBeingAborted(PDEVQUEUE pdq)
{
	return pdq->abortstatus;
}


GENERICAPI VOID GENERIC_EXPORT CancelRequest(PDEVQUEUE pdq, PIRP Irp)
{
	KIRQL oldirql = Irp->CancelIrql;

	/*	Release the global cancel spin lock as soon as possible. */
	IoReleaseCancelSpinLock(DISPATCH_LEVEL);

	/*	Acquire our queue-specific queue lock. Note that we stayed at
		DISPATCH_LEVEL when we released the cancel spin lock.
	*/
	KeAcquireSpinLockAtDpcLevel(&pdq->lock);

	/*	After Peretz & Hanrahan) The IRP is guaranteed to be on *some*
		queue (maybe a degenerated one), so we unconditionally
		remove it and complete it.
	*/
	RemoveEntryList(&Irp->Tail.Overlay.ListEntry);
	KeReleaseSpinLock(&pdq->lock, oldirql);

	Irp->IoStatus.Status = STATUS_CANCELLED;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);

} // CancelRequest


GENERICAPI BOOLEAN GENERIC_EXPORT CheckBusyAndStall(PDEVQUEUE pdq)
{
	KIRQL oldirql;
	KeAcquireSpinLock(&pdq->lock, &oldirql);
	BOOLEAN busy = pdq->CurrentIrp != NULL;

	if (!busy)
		InterlockedIncrement(&pdq->stallcount);
	KeReleaseSpinLock(&pdq->lock, oldirql);
	return busy;
}


GENERICAPI BOOLEAN GENERIC_EXPORT CheckAnyBusyAndStall(PDEVQUEUE* q, ULONG nq, PDEVICE_OBJECT fdo)
{
	ULONG i;

	/*	Call CheckBusyAndStall for each queue.
		If one of them is busy, back out by uninstalling the queues we stalled.
	*/

	for (i = 0; i < nq; ++i)
	{
		if (CheckBusyAndStall(q[i]))
		{
			// a queue is busy
			for (--i; (int) i >= 0; --i)
				RestartRequests(q[i], fdo);

			return TRUE; // indicate at least one queue is busy
		}
	}

	/*	Return FALSE because no queue was busy and all are now stalled.	*/
	return FALSE;
} // CheckAnyBusyAndStall


GENERICAPI VOID GENERIC_EXPORT CleanupRequests(PDEVQUEUE pdq, PFILE_OBJECT fop, NTSTATUS status)
{
	LIST_ENTRY cancellist;
	InitializeListHead(&cancellist);

	/*	Create a list of IRPs that belong to the same file object.	*/

	KIRQL oldirql;
	KeAcquireSpinLock(&pdq->lock, &oldirql);

	PLIST_ENTRY first = &pdq->head;
	PLIST_ENTRY next;

	for (next = first->Flink; next != first; )
	{
		// for each queued IRP
		PIRP Irp = CONTAINING_RECORD(next, IRP, Tail.Overlay.ListEntry);
		PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

		/*	Follow the chain to the next IRP now (so that the next iteration
			of the loop is properly setup whether we dequeue this IRP or not).
		*/
		
		PLIST_ENTRY current = next;
		next = next->Flink;

		/*	Skip this IRP if it's not for the same file object as the
			current IRP_MJ_CLEANUP.
		*/

		if (fop && stack->FileObject != fop)
			continue;

		/*	(After Hanrahan) Set the CancelRoutine pointer to NULL.
			If it was already NULL, someone is trying to cancel this IRP
			right now, so just leave it on the queue and let them do it
			as soon as we release the spin lock.
		*/

		if (!IoSetCancelRoutine(Irp, NULL))
			continue;

		RemoveEntryList(current);
		InsertTailList(&cancellist, current);
	}


	/*	Release the spin lock. We're about to undertake a potentially
		time-consuming operation that might conceivably result in a
		deadlock if we keep the lock.
	*/

	KeReleaseSpinLock(&pdq->lock, oldirql);

	/*	Complete the selected requests.	*/
	while (!IsListEmpty(&cancellist))
	{
		// cancel selected requests
		next = RemoveHeadList(&cancellist);
		PIRP Irp = CONTAINING_RECORD(next, IRP, Tail.Overlay.ListEntry);
		Irp->IoStatus.Status = status;
		IoCompleteRequest(Irp, IO_NO_INCREMENT);
	}
} // CleanupRequests


GENERICAPI VOID GENERIC_EXPORT CleanupAllRequests(PDEVQUEUE* q, ULONG nq, PFILE_OBJECT fop, NTSTATUS status)
{
	for (ULONG i = 0; i < nq; ++i)
		CleanupRequests(q[i], fop, status);
}



GENERICAPI PIRP GENERIC_EXPORT GetCurrentIrp(PDEVQUEUE pdq)
{
	return pdq->CurrentIrp;
}


GENERICAPI VOID GENERIC_EXPORT InitializeQueue(PDEVQUEUE pdq, PDRIVER_STARTIO StartIo)
{
	InitializeListHead(&pdq->head);
	KeInitializeSpinLock(&pdq->lock);
	
	pdq->StartIo = StartIo;
	pdq->stallcount = 1;
	pdq->CurrentIrp = NULL;
	KeInitializeEvent(&pdq->evStop, NotificationEvent, FALSE);
	pdq->abortstatus = (NTSTATUS) 0;
	pdq->notify = NULL;
	pdq->notifycontext = 0;
}


VOID NotificationCallback(PNOTIFY_CONTEXT ctx)
{
	if (InterlockedDecrement(&ctx->count) > 0)
		return;

	(*ctx->notify)(ctx->context);

	ExFreePool(ctx);
}


GENERICAPI VOID GENERIC_EXPORT RestartRequests(PDEVQUEUE pdq, PDEVICE_OBJECT fdo)
{
	/*	The original version of this routine called StartNextPacket to restart
		the queue. Reader Sink Ho pointed out a race condition, such that
		an intervening call to StartPacket in another thread or on another
		CPU would cause StartNextPacket to end up dequeuing a second IRP.
	*/

	KIRQL oldirql;
	KeAcquireSpinLock(&pdq->lock, &oldirql);

	if (InterlockedDecrement(&pdq->stallcount) > 0)
	{
		// still stalled
		KeReleaseSpinLock(&pdq->lock, oldirql);
		return;
	}

	/*	Dequeue and start the IRP at the head of the list.
		See the comments in StartNextPacket for an explanation of the cancel logic.
	*/

	while (!pdq->stallcount && !pdq->CurrentIrp && !pdq->abortstatus && !IsListEmpty(&pdq->head))
	{

		PLIST_ENTRY next = RemoveHeadList(&pdq->head);
		PIRP Irp = CONTAINING_RECORD(next, IRP, Tail.Overlay.ListEntry);

		if (!IoSetCancelRoutine(Irp, NULL))
		{
			// IRP being cancelled right now, else CancelRoutine shouldn't be NULL!
			ASSERT(Irp->Cancel);
			InitializeListHead(&Irp->Tail.Overlay.ListEntry);
			continue;
		}

		pdq->CurrentIrp = Irp;
		KeReleaseSpinLockFromDpcLevel(&pdq->lock);
		(*pdq->StartIo)(fdo, Irp);
		KeLowerIrql(oldirql);
		return;
	}

	/*	No IRPs need to be started (or else all queued IRPs were being cancelled.	*/
	KeReleaseSpinLock(&pdq->lock, oldirql);
} // RestartRequests



GENERICAPI VOID GENERIC_EXPORT RestartAllRequests(PDEVQUEUE* q, ULONG nq, PDEVICE_OBJECT fdo)
{
	for (ULONG i = 0; i < nq; ++i)
		RestartRequests(q[i], fdo);
}


GENERICAPI VOID GENERIC_EXPORT StallRequests(PDEVQUEUE pdq)
{
	InterlockedIncrement(&pdq->stallcount);
}

GENERICAPI VOID GENERIC_EXPORT StallAllRequests(PDEVQUEUE* q, ULONG nq)
{
	for (ULONG i = 0; i < nq; ++i)
		StallRequests(q[i]);
}

GENERICAPI NTSTATUS GENERIC_EXPORT StallRequestsAndNotify(PDEVQUEUE pdq, PQNOTIFYFUNC notify, PVOID context)
{
	NTSTATUS status;
	KIRQL oldirql;
	KeAcquireSpinLock(&pdq->lock, &oldirql);

	if (pdq->notify)
		status = STATUS_INVALID_DEVICE_REQUEST;
	else
	{
		// valid request
		InterlockedIncrement(&pdq->stallcount);
		
		if (pdq->CurrentIrp)
		{
			// device is busy
			pdq->notify = notify;
			pdq->notifycontext = context;
			status = STATUS_PENDING;
		}
		else
		{
			// device is idle
			status = STATUS_SUCCESS;
		}
	}

	KeReleaseSpinLock(&pdq->lock, oldirql);
	return status;
} // StallRequestsAndNotify


GENERICAPI NTSTATUS GENERIC_EXPORT StallAllRequestsAndNotify(PDEVQUEUE* q, ULONG nq, PQNOTIFYFUNC notify, PVOID context)
{
	NTSTATUS status;
	KIRQL oldirql;
	ULONG i;

	/*	Acquire all of the queue locks. We're not worried about a deadlock
		because this is the only function that ever simultaneously locks
		more than one queue.
	*/

	KeRaiseIrql(DISPATCH_LEVEL, &oldirql);
	for (i = 0; i < nq; ++i)
		KeAcquireSpinLockAtDpcLevel(&q[i]->lock);


	/*	Examine each of the queues in a manner similar to the single-queue
		version of this function.
	*/
	ULONG nbusy = 0;		// number of busy devices
	ULONG ibusy;			// index of last busy device

	for (i = 0; i < nq; ++i)
	{
		// examine each queue
		PDEVQUEUE pdq = q[i];
		if (pdq->notify)
			break;
		else
		{
			// notify not pending
			InterlockedIncrement(&pdq->stallcount); // stall this queue
			if (pdq->CurrentIrp)
			{
				++nbusy;
				ibusy = i; // device busy with this queue
			}
		}
	} // for(i)


	/*	If we didn't finish the loop, we found a queue for which a
		notification is already pending, which is an error. Unstall any
		queues that we just stalled in order to backout from this
		function.
	*/

	if (i < nq)
	{
		for (--i; (int) i >= 0; --i)
			InterlockedDecrement(&q[i]->stallcount);

		status = STATUS_INVALID_DEVICE_REQUEST; // indicate we have an error
	}
	/*	If none of the queues is busy, we can just return STATUS_SUCCESS.	*/
	else if (nbusy == 0)
		status = STATUS_SUCCESS; // device not busy

	/*	If just one of the queue is busy, arrange for it call the
		notification procedure once the current IRP finishes
		(whereupon somebody will call StartNextPacket on this queue).
	*/
	else if (nbusy == 1)
	{
		q[ibusy]->notify = notify;
		q[ibusy]->notifycontext = context;
		status = STATUS_PENDING;
	}

	/*	More than one queue is currently busy. We need to arrange for each
		queue to finish before calling the callback function.
	*/
	else
	{
		PNOTIFY_CONTEXT ctx = (PNOTIFY_CONTEXT) ExAllocatePool(NonPagedPool, sizeof(NOTIFY_CONTEXT));

		if (!ctx)
		{
			// can't allocate context block
			for (i = 0; i < nq; ++i)
				InterlockedDecrement(&q[i]->stallcount); // unstall the queues we stalled

			status = STATUS_INSUFFICIENT_RESOURCES;
		}
		else
		{
			// arrange for notifications
			ctx->context = context;
			ctx->notify = notify;
			ctx->count = nbusy;

			for (i = 0; i < nq; ++i)
			{
				// for each queue
				PDEVQUEUE pdq = q[i];
				if (!pdq->CurrentIrp)
					continue;

				pdq->notify = (PQNOTIFYFUNC) NotificationCallback;
				pdq->notifycontext = (PVOID) ctx;
			}

			status = STATUS_PENDING;
		}
	}

	/*	Release all the queue locks. [Note: there used to be a rookie
		mistake in the following line of code -- "i" is unsigned, so
		the loop used to wrap it around to FFFFFFFF and led to a crash.
		Reader and past student Mike Rapp spent many hours isolating this
		problem.]
	*/

	for (i = nq - 1; (int) i >= 0; --i)
		KeReleaseSpinLockFromDpcLevel(&q[i]->lock);

	KeLowerIrql(oldirql);

	return status;
} // StallAllRequestsAndNotify


GENERICAPI PIRP GENERIC_EXPORT StartNextPacket(PDEVQUEUE pdq, PDEVICE_OBJECT fdo)
{
	KIRQL oldirql;
	KeAcquireSpinLock(&pdq->lock, &oldirql);

	/*	Nullify the current IRP pointer after remembering the current one.
		We'll return the current IRP pointer as our return value so that
		a DPC routine has a way to know whether an active request got
		aborted.
	*/

	PIRP CurrentIrp = (PIRP) InterlockedExchangePointer((PVOID*) &pdq->CurrentIrp, NULL);

	/*	If we just finished processing a request, set the event on which
		WaitForCurrentIrp may be waiting in some other thread.
	*/

	if (CurrentIrp)
		KeSetEvent(&pdq->evStop, 0, FALSE);

	/*	If someone is waiting for notification that this IRP has finished,
		we'll provide the notification after we release the spin lock.
		We shouldn't find the queue unstalled if there is a notification
		routine in place, by the way.
	*/

	PQNOTIFYFUNC notify = pdq->notify;
	PVOID notifycontext = pdq->notifycontext;
	pdq->notify = NULL;


	/*	Start the next IRP.	*/
	while (!pdq->stallcount && !pdq->abortstatus && !IsListEmpty(&pdq->head))
	{
		// start next packet
		PLIST_ENTRY next = RemoveHeadList(&pdq->head);
		PIRP Irp = CONTAINING_RECORD(next, IRP, Tail.Overlay.ListEntry);


		/*	(After Peretz & Hanrahan in part) Nullify the cancel pointer in
			this IRP. If it was already NULL, someone is trying to cancel
			this IRP right now. Reinitialize the link pointers so the
			cancel routine's call to RemoveEntryList won't do anything
			harmful and look for another IRP. The cancel routine will
			take over as soon as we release the spin lock.
		*/

		if (!IoSetCancelRoutine(Irp, NULL))
		{
			// IRP being cancelled right now, else CancelRoutine shouldn't be NULL!
			ASSERT(Irp->Cancel);
			InitializeListHead(&Irp->Tail.Overlay.ListEntry);
			continue;
		}


		pdq->CurrentIrp = Irp;
		KeReleaseSpinLockFromDpcLevel(&pdq->lock);
		(*pdq->StartIo)(fdo, Irp);
		KeLowerIrql(oldirql);
		return CurrentIrp;
	}

	KeReleaseSpinLock(&pdq->lock, oldirql);

	if (notify)
		(*notify)(notifycontext);

	return CurrentIrp;
} // StartNextPacket


GENERICAPI VOID GENERIC_EXPORT StartPacket(PDEVQUEUE pdq, PDEVICE_OBJECT fdo, PIRP Irp, PDRIVER_CANCEL cancel)
{
	KIRQL oldirql;
	KeAcquireSpinLock(&pdq->lock, &oldirql);

	ASSERT(cancel); // must supply a cancel routine
	ASSERT(Irp->CancelRoutine == NULL);  // maybe left over from a higher level?

	/*	If the device has been removed by surprise, complete IRP immediately.
		Do not pass GO. Do not collect $200.
	*/

	NTSTATUS abortstatus = pdq->abortstatus;
	if (abortstatus)
	{
		// aborting all requests now
		KeReleaseSpinLock(&pdq->lock, oldirql);
		Irp->IoStatus.Status = abortstatus;
		IoCompleteRequest(Irp, IO_NO_INCREMENT);
	}

	/*	If the device is busy with another request, or if the queue has
		been stalled due to some PnP or power event, just put the new
		IRP onto the queue and set a cancel routine pointer.
	*/
	else if (pdq->CurrentIrp || pdq->stallcount)
	{
		/*	(After Peretz) See if this IRP was cancelled before it got to us.
			If so, make sure either we or the cancel routine completes it.
		*/

		IoSetCancelRoutine(Irp, cancel);
		if (Irp->Cancel && IoSetCancelRoutine(Irp, NULL))
		{
			// IRP has already been cancelled
			KeReleaseSpinLock(&pdq->lock, oldirql);
			Irp->IoStatus.Status = STATUS_CANCELLED;
			IoCompleteRequest(Irp, IO_NO_INCREMENT);
		}
		else
		{
			// queue IRP
			InsertTailList(&pdq->head, &Irp->Tail.Overlay.ListEntry);
			KeReleaseSpinLock(&pdq->lock, oldirql);
		}
	}

	/*	If the device is idle and not stalled, pass the IRP to the StartIo
		routine associated with this queue.
	*/
	else
	{
		// start this IRP
		pdq->CurrentIrp = Irp;
		KeReleaseSpinLock(&pdq->lock, DISPATCH_LEVEL);
		(*pdq->StartIo)(fdo, Irp);
		KeLowerIrql(oldirql);
	}

} // StartPacket


GENERICAPI VOID GENERIC_EXPORT WaitForCurrentIrp(PDEVQUEUE pdq)
{
	/*	First reset the event that StartNextPacket sets each time.	*/
	KeClearEvent(&pdq->evStop);

	/*	Under protection of our spin lock, check to see if there's a current IRP.
		Since whoever called us should have stalled requests, no-one can sneak
		in after we release the spin lock and start a new request behind our back.
	*/

	ASSERT(pdq->stallcount != 0); // should be stalled now!


	KIRQL oldirql;
	KeAcquireSpinLock(&pdq->lock, &oldirql);
	BOOLEAN mustwait = pdq->CurrentIrp != NULL;
	KeReleaseSpinLock(&pdq->lock, oldirql);

	if (mustwait)
		KeWaitForSingleObject(&pdq->evStop, Executive, KernelMode, FALSE, NULL);

} // WaitForCurrentIrp


GENERICAPI VOID GENERIC_EXPORT WaitForCurrentIrps(PDEVQUEUE* q, ULONG nq)
{
	for (ULONG i = 0; i < nq; ++i)
		WaitForCurrentIrp(q[i]);
}
