// Control.cpp -- IOCTL handlers for memtest driver
// Copyright (C) 1999, 2000 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"
#include "ioctls.h"

VOID DoMemoryTest(char* poolname, POOL_TYPE pooltype);

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS DispatchControl(PDEVICE_OBJECT fdo, PIRP Irp)
	{							// DispatchControl
	PAGED_CODE();
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	NTSTATUS status = IoAcquireRemoveLock(&pdx->RemoveLock, Irp);
	if (!NT_SUCCESS(status))
		return CompleteRequest(Irp, status, 0);
	ULONG info = 0;

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	ULONG cbin = stack->Parameters.DeviceIoControl.InputBufferLength;
	ULONG cbout = stack->Parameters.DeviceIoControl.OutputBufferLength;
	ULONG code = stack->Parameters.DeviceIoControl.IoControlCode;

	switch (code)
		{						// process request

	case IOCTL_DO_TEST:				// code == 0x800
		{						// IOCTL_DO_TEST
		DoMemoryTest("PagedPool", PagedPool);
		DoMemoryTest("NonPagedPool", NonPagedPool);
		break;
		}						// IOCTL_DO_TEST

	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		break;

		}						// process request

	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	return CompleteRequest(Irp, status, info);
	}							// DispatchControl

///////////////////////////////////////////////////////////////////////////////

#pragma LOCKEDCODE

VOID DoMemoryTest(char* poolname, POOL_TYPE pooltype)
	{							// DoMemoryTest
	DbgPrint(DRIVERNAME " - Beginning test for %s\n", poolname);

	ULONG npages = 512 * 1024 * 1024 / PAGE_SIZE;	// start with 512 MB
	ULONG delta = npages / 2;
	ULONG biggest = 0;

	// Determine, to within 64 KB, the largest contiguous allocation from
	// this pool

	while (delta > 64 * 1024 / PAGE_SIZE)
		{						// determine largest allocation
		PVOID p = ExAllocatePoolWithTagPriority(pooltype, npages * PAGE_SIZE - 512, 'YENO', LowPoolPriority);
		if (p)
			ExFreePool(p);

		if (p)
			{					// success
			DbgPrint(DRIVERNAME " - Allocated %8.8X bytes okay\n", npages * PAGE_SIZE - 512);
			if (npages > biggest)
				biggest = npages;
			npages += delta;

			}					// success
		else
			{					// failure
			DbgPrint(DRIVERNAME " - Unable to allocate %8.8X bytes\n", npages * PAGE_SIZE - 512);
			npages -= delta;
			}					// failure

		delta /= 2;
		}						// determine largest allocation
	
	DbgPrint(DRIVERNAME " - **** Largest allocation from %s was %8.8X bytes (%8.8X pages) ****\n",
		poolname, biggest * PAGE_SIZE - 512, biggest);
	}							// DoMemoryTest

