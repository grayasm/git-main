/*
	Device.cpp - generic device extension.
	Copyright (C) 1999, 2000 by Walter Oney.
 */

#include "Device.h"
#include "Ioctl.h"
#include "Pnp.h"


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


//////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE
NTSTATUS DispatchControl(PDEVICE_OBJECT fdo, PIRP Irp)
{
	PAGED_CODE();

	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION)fdo->DeviceExtension;

	NTSTATUS status = IoAcquireRemoveLock(&pdx->RemoveLock, Irp);
	if (!NT_SUCCESS(status))
		return CompleteRequest(Irp, status, 0);
	ULONG info = 0;

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	ULONG cbin = stack->Parameters.DeviceIoControl.InputBufferLength;
	ULONG cbout = stack->Parameters.DeviceIoControl.OutputBufferLength;
	ULONG code = stack->Parameters.DeviceIoControl.IoControlCode;

	switch (code)
	{

	case IOCTL_DO_TEST: // code == 0x800
	{
		DoMemoryTest();
		break;
	}

	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		break;

	} // switch

	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	return CompleteRequest(Irp, status, info);
} // DispatchControl




#pragma LOCKEDCODE
VOID DoMemoryTest()
{
	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	const int BUFSIZE = 10;
	PVOID memptr = ExAllocatePoolWithTagPriority(PagedPool, BUFSIZE * sizeof(int), 'Tag1', NormalPoolPriority);
	if (memptr == NULL)
	{
		KdPrint((DRIVERNAME " - ExAllocatePoolWithTagPriority failed!\n"));
		return;
	}

	KdPrint((DRIVERNAME " - ExAllocatePoolWithTagPriority succeeded!"));

	for (int i = 0; i < BUFSIZE; ++i)
		*((int*)memptr + i) = i;
	for (int i = 0; i < BUFSIZE; ++i)
		KdPrint((DRIVERNAME " - *(memptr + %d) = %d\n", i, *((int*)memptr + i)));


	ExFreePoolWithTag(memptr, 'Tag1');
	KdPrint((DRIVERNAME " - ExAllocatePoolWithTagPriority succeeded!"));


} // DoMemoryTest





#pragma PAGEDCODE
NTSTATUS DispatchPnp(PDEVICE_OBJECT fdo, PIRP Irp)
{
	PAGED_CODE();

	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION)fdo->DeviceExtension;
	return GenericDispatchPnp(pdx->pgx, Irp);
}


NTSTATUS DispatchPower(PDEVICE_OBJECT fdo, PIRP Irp)
{
	PAGED_CODE();

	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION)fdo->DeviceExtension;
	return GenericDispatchPower(pdx->pgx, Irp);
}


NTSTATUS DispatchWmi(PDEVICE_OBJECT fdo, PIRP Irp)
{
	PAGED_CODE();

	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION)fdo->DeviceExtension;
	IoSkipCurrentIrpStackLocation(Irp);
	return IoCallDriver(pdx->LowerDeviceObject, Irp);
}



#pragma PAGEDCODE
VOID RemoveDevice(IN PDEVICE_OBJECT fdo)
{
	PAGED_CODE();

	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));


	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION)fdo->DeviceExtension;
	NTSTATUS status;

	if(pdx->devname.Buffer)
		RtlFreeUnicodeString(&pdx->devname);

	if (pdx->LowerDeviceObject)
		IoDetachDevice(pdx->LowerDeviceObject);

	IoDeleteDevice(fdo);
} // RemoveDevice



#pragma PAGEDCODE
NTSTATUS DispatchCreate(PDEVICE_OBJECT fdo, PIRP Irp)
{
	PAGED_CODE();

	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION)fdo->DeviceExtension;

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

	NTSTATUS status = STATUS_SUCCESS;

	if (NT_SUCCESS(status))
	{
		// okay to open
		if (InterlockedIncrement(&pdx->handles) == 1)
		{
			// first open handle
		}
	}

	return CompleteRequest(Irp, status, 0);
}



#pragma PAGEDCODE
NTSTATUS DispatchClose(PDEVICE_OBJECT fdo, PIRP Irp)
{
	PAGED_CODE();

	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION)fdo->DeviceExtension;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	if (InterlockedDecrement(&pdx->handles) == 0)
	{
		// no more open handles
	}

	return CompleteRequest(Irp, STATUS_SUCCESS, 0);
}



#pragma PAGEDCODE
NTSTATUS StartDevice(PDEVICE_OBJECT fdo, PCM_PARTIAL_RESOURCE_LIST raw, PCM_PARTIAL_RESOURCE_LIST translated)
{
	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION)fdo->DeviceExtension;

	return STATUS_SUCCESS;
}



#pragma PAGEDCODE
VOID StopDevice(IN PDEVICE_OBJECT fdo, BOOLEAN oktouch /* = FALSE */)
{
	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION)fdo->DeviceExtension;
}


//////////////////////////////////////////////////////////////////////////