/*
	Device.cpp - generic device extension.
	Copyright (C) 1999, 2000 by Walter Oney.
 */

#include "Device.h"


#pragma LOCKEDCODE
NTSTATUS CompleteRequest(PIRP Irp, NTSTATUS status, ULONG_PTR info)
{
	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	Irp->IoStatus.Status = status;
	Irp->IoStatus.Information = info;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return status;
}


/*	Overload variant that doesn't change IoStatus.
	Information -- use this for most PnP requests.
*/

NTSTATUS CompleteRequest(PIRP Irp, NTSTATUS status)
{
	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	Irp->IoStatus.Status = status;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return status;
}


#pragma PAGEDCODE
NTSTATUS ForwardAndWait(PGENERIC_EXTENSION pdx, PIRP Irp)
{
	PAGED_CODE();
	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	KEVENT event;
	KeInitializeEvent(&event, NotificationEvent, FALSE);

	IoCopyCurrentIrpStackLocationToNext(Irp);
	IoSetCompletionRoutine(Irp, (PIO_COMPLETION_ROUTINE)OnRequestComplete,
		(PVOID) &event, TRUE, TRUE, TRUE);

	IoCallDriver(pdx->LowerDeviceObject, Irp);
	KeWaitForSingleObject(&event, Executive, KernelMode, FALSE, NULL);
	return Irp->IoStatus.Status;
}


#pragma LOCKEDCODE
NTSTATUS OnRequestComplete(PDEVICE_OBJECT junk, PIRP Irp, PKEVENT pev)
{
	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	KeSetEvent(pev, 0, FALSE);
	return STATUS_MORE_PROCESSING_REQUIRED;
}