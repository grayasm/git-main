/*
	DriverEntry.cpp - driver entry function.
	Copyright (C) 1999, 2000 by Walter Oney.


00000018	4.50637484	C3_HEAPIOCTLPRIO - DriverEntry
00000019	4.50637865	C3_HEAPIOCTLPRIO - GenericGetVersion
00000020	4.50651217	C3_HEAPIOCTLPRIO - AddDevice
00000021	4.50651503	C3_HEAPIOCTLPRIO - GetSizeofGenericExtension
00000022	4.50654507	C3_HEAPIOCTLPRIO - InitializeGenericExtension
00000023	4.50654745	C3_HEAPIOCTLPRIO - GenericInitializeRemoveLock
00000024	4.50655127	GENERIC - Initializing for C3_HEAPIOCTLPRIO
00000025	4.50655365	C3_HEAPIOCTLPRIO - GenericRegisterInterface
00000026	4.50655603	C3_HEAPIOCTLPRIO - FindInterfaceRecord
00000027	4.50707769	C3_HEAPIOCTLPRIO - DispatchPnp
00000028	4.50708103	C3_HEAPIOCTLPRIO - GenericDispatchPnp
00000029	4.50708342	C3_HEAPIOCTLPRIO - GenericAcquireRemoveLock
00000030	4.50708628	C3_HEAPIOCTLPRIO - DefaultPnpHandler
00000031	4.50708914	C3_HEAPIOCTLPRIO - GenericReleaseRemoveLock
00000032	4.50717735	C3_HEAPIOCTLPRIO - DispatchPnp
00000033	4.50717926	C3_HEAPIOCTLPRIO - GenericDispatchPnp
00000034	4.50718164	C3_HEAPIOCTLPRIO - GenericAcquireRemoveLock
00000035	4.50718498	C3_HEAPIOCTLPRIO - PNP Request (IRP_MN_FILTER_RESOURCE_REQUIREMENTS)
00000036	4.50718689	C3_HEAPIOCTLPRIO - DefaultPnpHandler
00000037	4.50718975	C3_HEAPIOCTLPRIO - GenericReleaseRemoveLock
00000038	4.50725842	C3_HEAPIOCTLPRIO - DispatchPnp
00000039	4.50726080	C3_HEAPIOCTLPRIO - GenericDispatchPnp
00000040	4.50726414	C3_HEAPIOCTLPRIO - GenericAcquireRemoveLock
00000041	4.50726652	C3_HEAPIOCTLPRIO - PNP Request (IRP_MN_START_DEVICE)
00000042	4.50726891	C3_HEAPIOCTLPRIO - HandleStartDevice
00000043	4.50727129	C3_HEAPIOCTLPRIO - ForwardAndWait
00000044	4.50727367	C3_HEAPIOCTLPRIO - OnRequestComplete
00000045	4.50727654	C3_HEAPIOCTLPRIO - StartDevice
00000046	4.50727892	C3_HEAPIOCTLPRIO - To WORKING from STOPPED
00000047	4.50728130	C3_HEAPIOCTLPRIO - GetPowerInfoFromRegistry
00000048	4.50730038	C3_HEAPIOCTLPRIO - EnableAllInterfaces
00000049	4.50731182	C3_HEAPIOCTLPRIO - AllowAllRequests
00000050	4.50731373	C3_HEAPIOCTLPRIO - RestartAllRequests
00000051	4.50731611	C3_HEAPIOCTLPRIO - GenericWakeupControl
00000052	4.50731945	C3_HEAPIOCTLPRIO - CompleteRequest
00000053	4.50732374	C3_HEAPIOCTLPRIO - GenericReleaseRemoveLock
00000054	4.50739574	C3_HEAPIOCTLPRIO - DispatchPnp
00000055	4.50739813	C3_HEAPIOCTLPRIO - GenericDispatchPnp
00000056	4.50740051	C3_HEAPIOCTLPRIO - GenericAcquireRemoveLock
00000057	4.50740290	C3_HEAPIOCTLPRIO - PNP Request (IRP_MN_QUERY_CAPABILITIES)
00000058	4.50740576	C3_HEAPIOCTLPRIO - HandleQueryCapabilities
00000059	4.50740767	C3_HEAPIOCTLPRIO - ForwardAndWait
00000060	4.50742722	C3_HEAPIOCTLPRIO - OnRequestComplete
00000061	4.50743103	C3_HEAPIOCTLPRIO - AdjustDeviceCapabilities
00000062	4.50743484	C3_HEAPIOCTLPRIO - AdjustWakeCapabilities
00000063	4.50743818	C3_HEAPIOCTLPRIO - GenericWakeupControl
00000064	4.50744152	C3_HEAPIOCTLPRIO - CompleteRequest
00000065	4.50744581	C3_HEAPIOCTLPRIO - GenericReleaseRemoveLock
00000066	4.50747395	C3_HEAPIOCTLPRIO - DispatchPnp
00000067	4.50747728	C3_HEAPIOCTLPRIO - GenericDispatchPnp
00000068	4.50748062	C3_HEAPIOCTLPRIO - GenericAcquireRemoveLock
00000069	4.50748396	C3_HEAPIOCTLPRIO - PNP Request (IRP_MN_QUERY_PNP_DEVICE_STATE)
00000070	4.50748730	C3_HEAPIOCTLPRIO - HandleQueryState
00000071	4.50749016	C3_HEAPIOCTLPRIO - DefaultPnpHandler
00000072	4.50749302	C3_HEAPIOCTLPRIO - GenericReleaseRemoveLock
00000073	4.50752926	C3_HEAPIOCTLPRIO - DispatchPnp
00000074	4.50753260	C3_HEAPIOCTLPRIO - GenericDispatchPnp
00000075	4.50753593	C3_HEAPIOCTLPRIO - GenericAcquireRemoveLock
00000076	4.50754023	C3_HEAPIOCTLPRIO - PNP Request (IRP_MN_QUERY_DEVICE_RELATIONS)
00000077	4.50754356	C3_HEAPIOCTLPRIO - DefaultPnpHandler
00000078	4.50754786	C3_HEAPIOCTLPRIO - GenericReleaseRemoveLock

*/



#include "Driver.h"
#include "Device.h"
#include "Ioctl.h"
#include "Power.h"


NTSTATUS AddDevice(IN PDRIVER_OBJECT DriverObject, IN PDEVICE_OBJECT pdo);
VOID DriverUnload(IN PDRIVER_OBJECT DriverObject);

/*
TODO If your driver uses more than one DEVQUEUE, remove the comment from the
declaration of "morequeues" which follows, and adjust the array dimension to
equal the number of queues you use minus one.
*/

struct INIT_STRUCT : public _GENERIC_INIT_STRUCT
{
	//	QSIO morequeues[1];			// additional devqueue/sio pointers
};


// UNICODE_STRING servkey;



#pragma PAGEDCODE
extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	// Insist that OS support at least the WDM level of the DDK we use
	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));


	if (!IoIsWdmVersionAvailable(1, 0))
	{
		KdPrint((DRIVERNAME " - Expected version of WDM (%d.%2.2d) not available\n", 1, 0));
		return STATUS_UNSUCCESSFUL;
	}

	/*
	We require GENERIC.SYS 1.3 or later. If a version earlier than 1.3 is installed,
	GenericGetVersion won't be exported, and this driver won't load in the first place.
	Too bad I didn't think of including this function at the beginning!
	*/

	if (GenericGetVersion() < 0x00010003)
	{
		KdPrint((DRIVERNAME " - Required version (1.3) of GENERIC.SYS not installed\n"));
		return STATUS_UNSUCCESSFUL;
	}

	// Save the name of the service key

	// servkey.Buffer = (PWSTR)ExAllocatePool(PagedPool, RegistryPath->Length + sizeof(WCHAR));
	//if (!servkey.Buffer)
	//{
	//	KdPrint((DRIVERNAME " - Unable to allocate %d bytes for copy of service key name\n", RegistryPath->Length + sizeof(WCHAR)));
	//	return STATUS_INSUFFICIENT_RESOURCES;
	//}

	//servkey.MaximumLength = RegistryPath->Length + sizeof(WCHAR);
	//RtlCopyUnicodeString(&servkey, RegistryPath);
	//servkey.Buffer[RegistryPath->Length / 2] = 0;	// add a null terminator

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

	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	// RtlFreeUnicodeString(&servkey);
}



#pragma PAGEDCODE
NTSTATUS AddDevice(PDRIVER_OBJECT DriverObject, PDEVICE_OBJECT pdo)
{
	PAGED_CODE();

	KdPrint((DRIVERNAME " - %s\n", __FUNCTION__));

	NTSTATUS status;

	// Create a function device object to represent the hardware we're managing.

	PDEVICE_OBJECT fdo;

	ULONG dxsize = (sizeof(DEVICE_EXTENSION) + 7) & ~7;
	ULONG xsize = dxsize + GetSizeofGenericExtension();

	UNICODE_STRING devname;
	RtlInitUnicodeString(&devname, L"\\DosDevices\\C3_HEAPIOCTLPRIO");

	status = IoCreateDevice(DriverObject, 
							xsize,
							&devname,
							FILE_DEVICE_UNKNOWN,
							FILE_DEVICE_SECURE_OPEN, 
							FALSE, 
							&fdo);

	if (!NT_SUCCESS(status))
	{
		// can't create device object
		KdPrint((DRIVERNAME " - IoCreateDevice failed - %X\n", status));
		return status;
	}

	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION)fdo->DeviceExtension;
	BOOLEAN ginit = FALSE;

	/*
	From this point forward, any error will have side effects that need to
	be cleaned up.
	*/

	do
	{
		// finish initialization
		pdx->DeviceObject = fdo;
		pdx->Pdo = pdo;

		// Make a copy of the device name

		pdx->devname.Buffer = (PWCHAR)ExAllocatePool(NonPagedPool, devname.MaximumLength);
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

		pdx->pgx = (PGENERIC_EXTENSION)((PUCHAR)pdx + dxsize);

		INIT_STRUCT gis;
		RtlZeroMemory(&gis, sizeof(gis));
		gis.Size = sizeof(gis);
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
		ginit = TRUE;

		// Clear the "initializing" flag so that we can get IRPs

		fdo->Flags &= ~DO_DEVICE_INITIALIZING;
	} while (FALSE);


	if (!NT_SUCCESS(status))
	{
		// need to cleanup
		if (ginit)
			CleanupGenericExtension(pdx->pgx);
		if (pdx->devname.Buffer)
			RtlFreeUnicodeString(&pdx->devname);
		if (pdx->LowerDeviceObject)
			IoDetachDevice(pdx->LowerDeviceObject);
		IoDeleteDevice(fdo);
	}

	return status;
} // AddDevice


#pragma LOCKEDCODE		// force inline functions into locked code
