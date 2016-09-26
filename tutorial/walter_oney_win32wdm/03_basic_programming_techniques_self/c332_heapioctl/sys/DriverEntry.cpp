/*
	c3_heapioctl main program.
	Copyright (C) 2016 by Mihai Vasilian

	3.3.2 Heap Allocator

*/

#ifdef __cplusplus
extern "C" {
#endif

#include <wdm.h>

#ifdef __cplusplus
}
#endif


#define PAGEDCODE	code_seg("PAGE")
#define LOCKEDCODE	code_seg()
#define INITCODE	code_seg("INIT")

#define PAGEDDATA	data_seg("PAGEDATA")
#define LOCKEDDATA	data_seg()
#define INITDATA	data_seg("INITDATA")

#define DRIVERNAME "C3_HEAPIOCTL"


NTSTATUS AddDevice(PDRIVER_OBJECT, PDEVICE_OBJECT);
VOID DriverUnload(PDRIVER_OBJECT);


// begin I/O Request Handlers
NTSTATUS DispatchCreate(PDEVICE_OBJECT, PIRP);
NTSTATUS DispatchClose(PDEVICE_OBJECT, PIRP);
NTSTATUS DispatchControl(PDEVICE_OBJECT, PIRP);
NTSTATUS DispatchPower(PDEVICE_OBJECT, PIRP);
NTSTATUS DispatchPnp(PDEVICE_OBJECT, PIRP);
NTSTATUS DispatchWmi(PDEVICE_OBJECT, PIRP);
// end of I/O Request Handlers.




typedef struct tagGENERIC_EXTENSION
{

} GENERIC_EXTENSION, *PGENERIC_EXTENSION;

typedef struct tagDEVICE_EXTENSION
{
	PDEVICE_OBJECT			Fdo;			// our-created function device object
	PDEVICE_OBJECT			Pdo;			// the physical device object (top of the stack, can have layered drivers on top)
	PDEVICE_OBJECT			Ldo;			// next lower driver in same stack (where we hooked Fdo on top)
	UNICODE_STRING			devname;		// device name
	PGENERIC_EXTENSION		pgx;			// generic device extension
} DEVICE_EXTENSION, *PDEVICE_EXTENSION;




#pragma PAGEDCODE
extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	KdPrint((DRIVERNAME " - Entering DriverEntry\n"));

	// Check on WDM version (current available).
	if (!IoIsWdmVersionAvailable(1, 0))
	{
		KdPrint((DRIVERNAME " - WDM 1.0 is not available!\n"));
		return STATUS_UNSUCCESSFUL;
	}

	// Now this is mine, from MSDN.
	RTL_OSVERSIONINFOW wdmnfo;
	NTSTATUS ret = RtlGetVersion(&wdmnfo);
	if (!NT_SUCCESS(ret))
	{
		KdPrint((DRIVERNAME " - RtlGetVersion failed!\n"));
		return STATUS_UNSUCCESSFUL;
	}

	KdPrint((DRIVERNAME " - RtlGetVersion succeeded, here is the information:\n"));
	KdPrint((DRIVERNAME " - WMD:%d.%d Build:%d OSVersInfoSize:%d PlatfId:%d CSDVers:%d\n", 
		wdmnfo.dwMajorVersion, wdmnfo.dwMinorVersion, wdmnfo.dwBuildNumber,
		wdmnfo.dwOSVersionInfoSize, wdmnfo.dwPlatformId, wdmnfo.szCSDVersion));


	// Initialize function pointers
	DriverObject->DriverExtension->AddDevice = AddDevice;
	DriverObject->DriverUnload = DriverUnload;

	DriverObject->MajorFunction[IRP_MJ_CREATE] = DispatchCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = DispatchClose;
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DispatchControl;
	DriverObject->MajorFunction[IRP_MJ_POWER] = DispatchPower;
	DriverObject->MajorFunction[IRP_MJ_PNP] = DispatchPnp;
	DriverObject->MajorFunction[IRP_MJ_SYSTEM_CONTROL] = DispatchWmi;

	
	return STATUS_SUCCESS;
}


#pragma PAGEDCODE
NTSTATUS AddDevice(PDRIVER_OBJECT DriverObject, PDEVICE_OBJECT pdo)
{
	PAGED_CODE();
	KdPrint((DRIVERNAME " - Entering AddDevice: DriverObject %8.8lX, pdo %8.8lX\n", DriverObject, pdo));
	
	NTSTATUS status = STATUS_SUCCESS;

	// size rounded to multiple of 1 Byte ; Can it contain 1,2,3 bits data members? :)
	ULONG dxsize = (sizeof(DEVICE_EXTENSION) + 7) & ~7;
	ULONG gxsize = (sizeof(GENERIC_EXTENSION) + 7) & ~7;
	ULONG xsize = dxsize + gxsize;


	/*	Create a function device object to represent the hardware we are managing. */
	PDEVICE_OBJECT fdo;
	UNICODE_STRING devname;
	RtlInitUnicodeString(&devname, L"\\DosDevices\\C3_HEAPIOCTL");

	status = IoCreateDevice(DriverObject,
							xsize,
							&devname,
							FILE_DEVICE_UNKNOWN,
							FILE_DEVICE_SECURE_OPEN,
							FALSE,
							&fdo);

	if (!NT_SUCCESS(status))
	{
		KdPrint((DRIVERNAME " - IoCreateDevice failed - %X\n", status));
		return status;
	}

	// From this point forward, any error will have side effects that need to be cleaned up.
	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION)fdo->DeviceExtension;
	BOOLEAN ginit = FALSE;

	do 
	{
		pdx->Fdo = fdo;
		pdx->Pdo = pdo;

		// make a copy of the device name
		pdx->devname.Buffer = (PWCHAR)ExAllocatePoolWithTag(NonPagedPool, devname.MaximumLength, 'Tag1');
		if (!pdx->devname.Buffer)
		{
			status = STATUS_INSUFFICIENT_RESOURCES;
			KdPrint((DRIVERNAME " - ExAllocatePoolWithTag unable to allocate %d bytes to copy device name!\n", devname.MaximumLength));
			break;
		}
		pdx->devname.MaximumLength = devname.MaximumLength;
		RtlCopyUnicodeString(&pdx->devname, &devname);

		// link our device object into the stack leading to the PDO
		pdx->Ldo = IoAttachDeviceToDeviceStack(fdo, pdo);


	}
	while (FALSE);


	// check the status
	if (!NT_SUCCESS(status))
	{

	}




	return status;
}


#pragma PAGEDCODE
VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
	PAGED_CODE();
	KdPrint((DRIVERNAME " - DriverUnload: DriverObject %8.8lX\n", DriverObject));
}
