// Main program for stupid driver
// Copyright (C) 2001 by Walter Oney
// All rights reserved

#include "stddcls.h"
#include "driver.h"
#include <initguid.h>
#include "guids.h"

NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT pdo);
VOID DriverUnload(IN PDRIVER_OBJECT DriverObject);

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

// before had IN both params
extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject,
								PUNICODE_STRING RegistryPath)
{							// DriverEntry
	KdPrint((DRIVERNAME " - Entering DriverEntry: DriverObject %8.8lX\n", DriverObject));

	// Initialize function pointers

	DriverObject->DriverUnload = DriverUnload;
	DriverObject->DriverExtension->AddDevice = AddDevice;

	return STATUS_SUCCESS;
}							// DriverEntry

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

VOID DriverUnload(IN PDRIVER_OBJECT DriverObject)
{							// DriverUnload
	PAGED_CODE();
	KdPrint((DRIVERNAME " - Entering DriverUnload: DriverObject %8.8lX\n", DriverObject));
}							// DriverUnload

///////////////////////////////////////////////////////////////////////////////

#pragma PAGEDCODE

NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT pdo)
	{							// AddDevice
	PAGED_CODE();
	KdPrint((DRIVERNAME " - Entering AddDevice: DriverObject %8.8lX, pdo %8.8lX\n", DriverObject, pdo));

	NTSTATUS status;

	// Create a function device object to represent the hardware we're managing.

	PDEVICE_OBJECT fdo;
	#define xsize sizeof(DEVICE_EXTENSION)
	status = IoCreateDevice(DriverObject, xsize, NULL,
		FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &fdo);
	if (!NT_SUCCESS(status))
		{						// can't create device object
		KdPrint((DRIVERNAME " - IoCreateDevice failed - %X\n", status));
		return status;
		}						// can't create device object
	
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	// From this point forward, any error will have side effects that need to
	// be cleaned up. Using a do-once block allows us to modify the program
	// easily without losing track of the side effects.

	do
		{						// finish initialization
		pdx->DeviceObject = fdo;
		pdx->Pdo = pdo;

		// Link our device object into the stack leading to the PDO
		
		pdx->LowerDeviceObject = IoAttachDeviceToDeviceStack(fdo, pdo);
		if (!pdx->LowerDeviceObject)
			{						// can't attach device
			KdPrint((DRIVERNAME " - IoAttachDeviceToDeviceStack failed\n"));
			status = STATUS_DEVICE_REMOVED;
			break;
			}						// can't attach device

		// Set power management flags in the device object

		fdo->Flags |= DO_POWER_PAGABLE;

		// Register a device interface

		status = IoRegisterDeviceInterface(pdo, &GUID_DEVINTERFACE_STUPID, NULL, &pdx->ifname);
		if (!NT_SUCCESS(status))
			{						// unable to register interface
			KdPrint((DRIVERNAME " - IoRegisterDeviceInterface failed - %8.8lX\n", status));
			break;
			}						// unable to register interface

		// Clear the "initializing" flag so that we can get IRPs

		fdo->Flags &= ~DO_DEVICE_INITIALIZING;

		// In a real driver, you would leave "status" alone at this point, or perhaps
		// change it to STATUS_SUCCESS. If we do that in this lame driver, we end up having
		// to reboot in order to get STUPID.SYS out of memory. Therefore, and simply as
		// an expedient for testing this driver that doesn't support PnP, fail this function

		status = STATUS_UNSUCCESSFUL;	// <== don't do this in a real driver!
		}						// finish initialization
	while (FALSE);

	if (!NT_SUCCESS(status))
		{					// need to cleanup
		if (pdx->ifname.Buffer)
			RtlFreeUnicodeString(&pdx->ifname);
		if (pdx->LowerDeviceObject)
			IoDetachDevice(pdx->LowerDeviceObject);
		IoDeleteDevice(fdo);
		}					// need to cleanup

	return status;
	}							// AddDevice
