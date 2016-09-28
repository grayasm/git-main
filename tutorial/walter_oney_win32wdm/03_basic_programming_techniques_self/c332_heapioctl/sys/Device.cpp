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
		DoMemoryTest("PagedPool", PagedPool);
		DoMemoryTest("NonPagedPool", NonPagedPool);
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
VOID DoMemoryTest(char* poolname, POOL_TYPE pooltype)
{
	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	DbgPrint(DRIVERNAME " - Beginning test for %s\n", poolname);

	ULONG npages = 512 * 1024 * 1024 / PAGE_SIZE;	// start with 512 MB
	ULONG delta = npages / 2;
	ULONG biggest = 0;

	// Determine, to within 64 KB, the largest contiguous allocation from
	// this pool

	while (delta > 64 * 1024 / PAGE_SIZE)
	{
		// determine largest allocation
		PVOID p = ExAllocatePoolWithTagPriority(pooltype, npages * PAGE_SIZE - 512, 'YENO', LowPoolPriority);
		if (p)
			ExFreePool(p);

		if (p)
		{
			// success
			DbgPrint(DRIVERNAME " - Allocated %8.8X bytes okay\n", npages * PAGE_SIZE - 512);
			if (npages > biggest)
				biggest = npages;
			npages += delta;

		}
		else
		{
			// failure
			DbgPrint(DRIVERNAME " - Unable to allocate %8.8X bytes\n", npages * PAGE_SIZE - 512);
			npages -= delta;
		}

		delta /= 2;
	}

	DbgPrint(DRIVERNAME " - **** Largest allocation from %s was %8.8X bytes (%8.8X pages) ****\n",
		poolname, biggest * PAGE_SIZE - 512, biggest);
} // DoMemoryTest


//#pragma LOCKEDCODE
//NTSTATUS CompleteRequest(PIRP Irp, NTSTATUS status, ULONG_PTR info)
//{
//	Irp->IoStatus.Status = status;
//	Irp->IoStatus.Information = info;
//	IoCompleteRequest(Irp, IO_NO_INCREMENT);
//	return status;
//}




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