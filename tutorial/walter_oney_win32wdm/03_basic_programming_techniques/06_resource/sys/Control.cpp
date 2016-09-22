/*
	Control.cpp -- IOCTL handlers for resource driver
	Copyright (C) 1999, 2000 by Walter Oney
*/



#include "stddcls.h"
#include "driver.h"
#include "ioctls.h"
#include "KmdResource.h"

NTSTATUS GetDriverVersion(PDEVICE_EXTENSION pdx, PULONG pVersion);


#pragma PAGEDCODE

NTSTATUS DispatchControl(PDEVICE_OBJECT fdo, PIRP Irp)
{
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
	{
	case IOCTL_GET_VERSION: // code == 0x800
	{
		if (cbout < sizeof(ULONG))
		{
			status = STATUS_BUFFER_TOO_SMALL;
			break;
		}

		ULONG version;
		status = GetDriverVersion(pdx, &version);
		if (NT_SUCCESS(status))
		{
			*(PULONG) Irp->AssociatedIrp.SystemBuffer = version;
			info = sizeof(ULONG);
		}

		break;
	} // IOCTL_GET_VERSION

	default:
		status = STATUS_INVALID_DEVICE_REQUEST;
		break;

	} // switch

	IoReleaseRemoveLock(&pdx->RemoveLock, Irp);
	return CompleteRequest(Irp, status, info);	
} // DispatchControl




#pragma PAGEDCODE
NTSTATUS GetDriverVersion(PDEVICE_EXTENSION pdx, PULONG pVersion)
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

	*pVersion = 0x00010000;		// default to 1.0

	// Locate the version info

	ULONG junk;
	PVOID verres = GetDriverVersionInfo(hDriverResources);
	if (verres)
	{
		// get fixed info
		VS_FIXEDFILEINFO* verinfo = (VS_FIXEDFILEINFO*) VerQueryValue(verres, L"\\", junk);
		if (verinfo)
			*pVersion = verinfo->dwFileVersionMS;
	}

	/*
		This next bit of code is based on the MSDN code sample for how to use
		VerQueryValue in user mode. It first obtains an array of language/code-page
		codes describing the available string values. For each such, it prints the
		comment string. By hand, I put multiple language values into the version
		resource in order to make this an interesting test.
	*/

	typedef struct _LANGANDCODEPAGE
	{
		USHORT wLanguage;
		USHORT wCodePage;
	} LANGANDCODEPAGE, *PLANGANDCODEPAGE;

	PLANGANDCODEPAGE lcp = (PLANGANDCODEPAGE) VerQueryValue(verres, L"\\VarFileInfo\\Translation", junk);
	if (lcp)
	{
		// print comment strings
		ULONG n = junk / sizeof(LANGANDCODEPAGE);
		for (ULONG i = 0; i < n; ++i)
		{					
			// for each language and code page
			WCHAR valname[64];
			swprintf(valname, L"\\StringFileInfo\\%04x%04x\\Comments", lcp[i].wLanguage, lcp[i].wCodePage);
			PWCHAR comment = (PWCHAR)VerQueryValue(verres, valname, junk);
			if (comment)
				DbgPrint(DRIVERNAME " - (%04x %d) %ws\n", lcp[i].wLanguage, lcp[i].wCodePage, comment);
		}
	}

	CloseDriverResources(hDriverResources);
	return STATUS_SUCCESS;
} // GetDriverVersion
