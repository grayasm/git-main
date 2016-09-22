/*
	Main program for fputest driver
	Copyright (C) 1999 by Walter Oney
*/


#include "stddcls.h"
#include "driver.h"


NTSTATUS AddDevice(PDRIVER_OBJECT DriverObject, PDEVICE_OBJECT pdo);
VOID DriverUnload(PDRIVER_OBJECT fdo);

UNICODE_STRING servkey;



#pragma PAGEDCODE
extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	KdPrint((DRIVERNAME " - Entering DriverEntry: DriverObject %8.8lX\n", DriverObject));

	// This driver can't be run in Windows

	if (!IoIsWdmVersionAvailable(1, 0x10))
	{
		KdPrint((DRIVERNAME " - This sample requires Windows 2000 or Windows Xp\n"));
		return STATUS_UNSUCCESSFUL;
	}

	// Save the name of the service key

	servkey.Buffer = (PWSTR) ExAllocatePool(PagedPool, RegistryPath->Length + sizeof(WCHAR));
	if (!servkey.Buffer)
	{
		KdPrint((DRIVERNAME " - Unable to allocate %d bytes for copy of service key name\n", RegistryPath->Length + sizeof(WCHAR)));
		return STATUS_INSUFFICIENT_RESOURCES;
	}
	servkey.MaximumLength = RegistryPath->Length + sizeof(WCHAR);
	RtlCopyUnicodeString(&servkey, RegistryPath);
	servkey.Buffer[RegistryPath->Length / 2] = 0;

	// Initialize function pointers

	DriverObject->DriverUnload = DriverUnload;
	DriverObject->DriverExtension->AddDevice = AddDevice;

	DriverObject->MajorFunction[IRP_MJ_CREATE] = DispatchCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = DispatchClose;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DispatchControl;
	DriverObject->MajorFunction[IRP_MJ_POWER] = DispatchPower;
	DriverObject->MajorFunction[IRP_MJ_PNP] = DispatchPnp;
	DriverObject->MajorFunction[IRP_MJ_SYSTEM_CONTROL] = DispatchWmi;
	
	return STATUS_SUCCESS;
} // DriverEntry




#pragma PAGEDCODE
VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
	PAGED_CODE();

	KdPrint((DRIVERNAME " - Entering DriverUnload: DriverObject %8.8lX\n", DriverObject));
	RtlFreeUnicodeString(&servkey);
}



NTSTATUS AddDevice(PDRIVER_OBJECT DriverObject, PDEVICE_OBJECT pdo)
{
	PAGED_CODE();

	KdPrint((DRIVERNAME " - Entering AddDevice: DriverObject %8.8lX, pdo %8.8lX\n", DriverObject, pdo));

	NTSTATUS status;

	// Create a function device object to represent the hardware we're managing.

	PDEVICE_OBJECT fdo;

	ULONG dxsize = (sizeof(DEVICE_EXTENSION) + 7) & ~7;
	ULONG xsize = dxsize + GetSizeofGenericExtension();
	
	UNICODE_STRING devname;
	RtlInitUnicodeString(&devname, L"\\DosDevices\\FPUTEST");

	status = IoCreateDevice(DriverObject, xsize, &devname,
		FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &fdo);
	if (!NT_SUCCESS(status))
	{
		// can't create device object
		KdPrint((DRIVERNAME " - IoCreateDevice failed - %X\n", status));
		return status;
	}
	
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	// From this point forward, any error will have side effects that need to
	// be cleaned up.

	do
	{
		// finish initialization
		pdx->DeviceObject = fdo;
		pdx->Pdo = pdo;

		// Make a copy of the device name

		pdx->devname.Buffer = (PWCHAR) ExAllocatePool(NonPagedPool, devname.MaximumLength);
		if (!pdx->devname.Buffer)
		{
			// can't allocate buffer
			status = STATUS_INSUFFICIENT_RESOURCES;
			KdPrint((DRIVERNAME " - Unable to allocate %d bytes for copy of name\n", devname.MaximumLength));
			break;;
		}

		pdx->devname.MaximumLength = devname.MaximumLength;
		RtlCopyUnicodeString(&pdx->devname, &devname);

		// Link our device object into the stack leading to the PDO
		
		pdx->LowerDeviceObject = IoAttachDeviceToDeviceStack(fdo, pdo);
		if (!pdx->LowerDeviceObject)
		{
			// can't attach device
			KdPrint((DRIVERNAME " - IoAttachDeviceToDeviceStack failed\n"));
			status = STATUS_DEVICE_REMOVED;
			break;;
		}

		// Set power management flags in the device object

		fdo->Flags |= DO_POWER_PAGABLE;

		// Initialize to use the GENERIC.SYS library

		pdx->pgx = (PGENERIC_EXTENSION) ((PUCHAR) pdx + dxsize);

		GENERIC_INIT_STRUCT gis = {sizeof(GENERIC_INIT_STRUCT)};
		gis.DeviceObject = fdo;
		gis.Pdo = pdo;
		gis.Ldo = pdx->LowerDeviceObject;
		gis.RemoveLock = &pdx->RemoveLock;
		gis.StartDevice = StartDevice;
		gis.StopDevice = StopDevice;
		gis.RemoveDevice = RemoveDevice;
		RtlInitUnicodeString(&gis.DebugName, LDRIVERNAME);

		status = InitializeGenericExtension(pdx->pgx, &gis);
		if (!NT_SUCCESS(status))
		{
			KdPrint((DRIVERNAME " - InitializeGenericExtension failed - %X\n", status));
			break;;
		}

		// Clear the "initializing" flag so that we can get IRPs

		fdo->Flags &= ~DO_DEVICE_INITIALIZING;
	}
	while (FALSE);


	if (!NT_SUCCESS(status))
	{
		// need to cleanup
		if (pdx->devname.Buffer)
			RtlFreeUnicodeString(&pdx->devname);
		if (pdx->LowerDeviceObject)
			IoDetachDevice(pdx->LowerDeviceObject);
		IoDeleteDevice(fdo);
	}

	return status;
} // AddDevice




#pragma LOCKEDCODE
NTSTATUS CompleteRequest(IN PIRP Irp, IN NTSTATUS status, IN ULONG_PTR info)
{
	Irp->IoStatus.Status = status;
	Irp->IoStatus.Information = info;
	IoCompleteRequest(Irp, IO_NO_INCREMENT);
	return status;
}



#pragma PAGEDCODE
NTSTATUS DispatchPnp(PDEVICE_OBJECT fdo, PIRP Irp)
{
	PAGED_CODE();
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	return GenericDispatchPnp(pdx->pgx, Irp);
}


NTSTATUS DispatchPower(PDEVICE_OBJECT fdo, PIRP Irp)
{
	PAGED_CODE();
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	return GenericDispatchPower(pdx->pgx, Irp);
}


NTSTATUS DispatchWmi(PDEVICE_OBJECT fdo, PIRP Irp)
{
	PAGED_CODE();
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	IoSkipCurrentIrpStackLocation(Irp);
	return IoCallDriver(pdx->LowerDeviceObject, Irp);
}



#pragma PAGEDCODE
VOID RemoveDevice(IN PDEVICE_OBJECT fdo)
{
	PAGED_CODE();

	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	NTSTATUS status;

	RtlFreeUnicodeString(&pdx->devname);

	if (pdx->LowerDeviceObject)
		IoDetachDevice(pdx->LowerDeviceObject);

	IoDeleteDevice(fdo);
}

#pragma LOCKEDCODE				// force inline functions into locked code