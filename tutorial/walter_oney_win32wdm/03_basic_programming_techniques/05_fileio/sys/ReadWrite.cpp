/*
	Read/Write request processors for fileio driver
	Copyright (C) 1999 by Walter Oney
*/


#include "stddcls.h"
#include "driver.h"



#pragma PAGEDCODE
NTSTATUS DispatchCreate(PDEVICE_OBJECT fdo, PIRP Irp)
{
	PAGED_CODE();

	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;

	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);

	NTSTATUS status = STATUS_SUCCESS;
	InterlockedIncrement(&pdx->handles);
	return CompleteRequest(Irp, status, 0);
}



#pragma PAGEDCODE
NTSTATUS DispatchClose(PDEVICE_OBJECT fdo, PIRP Irp)
{
	PAGED_CODE();

	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	PIO_STACK_LOCATION stack = IoGetCurrentIrpStackLocation(Irp);
	InterlockedDecrement(&pdx->handles);
	return CompleteRequest(Irp, STATUS_SUCCESS, 0);
}



#pragma PAGEDCODE
NTSTATUS StartDevice(PDEVICE_OBJECT fdo, PCM_PARTIAL_RESOURCE_LIST raw, PCM_PARTIAL_RESOURCE_LIST translated)
{
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	NTSTATUS status;

	/*	A likely time to want to perform file I/O operations is during configuration of
		the device, in order to read a firmware file for downloading to the device. This
		stage is problematic in Win98 because the init order for CONFIGMG is before that
		of IFSMgr. The portable file I/O library solves that particular problem.
	*/
 
	DbgPrintEx(	DPFLTR_IHVDRIVER_ID,
				DPFLTR_ERROR_LEVEL,
				DRIVERNAME " - OpenFile %s",
				"fileio.jnk");


	HANDLE hfile;
	status = OpenFile(L"\\SystemRoot\\System32\\Drivers\\fileio.jnk", TRUE, &hfile);
	if (!NT_SUCCESS(status))
	{
		KdPrint((DRIVERNAME " - OpenFile failed - %X\n", status));
		return status;
	}

	PVOID buffer = NULL;

	__try
	{
		ULONG size = (ULONG) GetFileSize(hfile);
		if (!size)
			__leave;			// file is empty

		buffer = ExAllocatePool(PagedPool, size);
		if (!buffer)
		{
			KdPrint((DRIVERNAME " - Unable to allocate %d bytes for data buffer\n", size));
			status = STATUS_INSUFFICIENT_RESOURCES;
			__leave;
		}
		
		ULONG numread;
		status = ReadFile(hfile, buffer, size, &numread);

		if (!NT_SUCCESS(status))
		{
			KdPrint((DRIVERNAME " - ReadFile failed - %X\n", status));
			__leave;
		}

		KdPrint((DRIVERNAME " - ReadFile succeeded and read %d bytes\n", numread));

		// Preserve the data buffer for the associated test program

		pdx->RandomJunk = buffer;
		pdx->RandomJunkSize = numread;
		buffer = NULL;
	}
	__finally
	{
		CloseFile(hfile);
		if (buffer)
			ExFreePool(buffer);
	}

	return status;
} // StartDevice




#pragma PAGEDCODE
VOID StopDevice(IN PDEVICE_OBJECT fdo, BOOLEAN oktouch /* = FALSE */)
{
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION) fdo->DeviceExtension;
	if (pdx->RandomJunk)
		ExFreePool(pdx->RandomJunk);
	pdx->RandomJunk = NULL;
}
