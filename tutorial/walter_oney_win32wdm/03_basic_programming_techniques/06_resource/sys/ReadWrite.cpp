/*
	Read/Write request processors for foo driver
	Copyright (C) 1999, 2000 by Walter Oney
*/


#include "stddcls.h"
#include "driver.h"
#include "KmdResource.h"

NTSTATUS LoadFirmware(PDEVICE_EXTENSION pdx);



#pragma PAGEDCODE
NTSTATUS DispatchCreate(PDEVICE_OBJECT fdo, PIRP Irp)
{
	PAGED_CODE();

	KdPrint((DRIVERNAME " - IRP_MJ_CREATE\n"));
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

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
} // DispatchCreate





#pragma PAGEDCODE
NTSTATUS DispatchClose(PDEVICE_OBJECT fdo, PIRP Irp)
{
	PAGED_CODE();

	KdPrint((DRIVERNAME " - IRP_MJ_CLOSE\n"));
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	if (InterlockedDecrement(&pdx->handles) == 0)
	{
		// no more open handles
	}

	return CompleteRequest(Irp, STATUS_SUCCESS, 0);
}



/*
	This function illustrates how you could load locale-appropriate firmware
	from a resource in the driver file
*/

#pragma PAGEDCODE
NTSTATUS LoadFirmware(PDEVICE_EXTENSION pdx)
{
	HANDLE hDriverResources;
	NTSTATUS status;

	// Open this driver file using the service key captured during DriverEntry

	status = OpenDriverResourcesFromRegistry(&servkey, &hDriverResources);
	if (!NT_SUCCESS(status))
	{
		KdPrint((DRIVERNAME " - Can't open driver file - %X\n", status));
		return status;
	}

	/*
		Look for a firmware resource. Specify a neutral language id to get the
		system locale by default. In this sample driver, the "firmware" is just
		a localized string.
	*/

	ULONG size;
	PWCHAR firmware = (PWCHAR) FindResourceEx(hDriverResources, L"FIRMWARE", L"TheFirmware", 0, size);
	if (firmware)
		DbgPrint(DRIVERNAME " - TheFirmware is \"%ws\"\n", firmware);
	else
		KdPrint((DRIVERNAME " - No FIRMWARE resources\n"));

	CloseDriverResources(hDriverResources);

	return STATUS_SUCCESS;
}




#pragma PAGEDCODE
NTSTATUS StartDevice(PDEVICE_OBJECT fdo, PCM_PARTIAL_RESOURCE_LIST raw, PCM_PARTIAL_RESOURCE_LIST translated)
{
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	LoadFirmware(pdx);

	return STATUS_SUCCESS;
}



#pragma PAGEDCODE
VOID StopDevice(IN PDEVICE_OBJECT fdo, BOOLEAN oktouch /* = FALSE */)
{
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
}
