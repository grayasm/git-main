/*
	DriverEntry.cpp - driver entry function.
	Copyright (C) 1999, 2000 by Walter Oney.


00000014	3.60364652	C3_HEAPIOCTL - DriverEntry
00000015	3.60364914	C3_HEAPIOCTL - GenericGetVersion
00000016	3.60374451	C3_HEAPIOCTL - AddDevice
00000017	3.60374570	C3_HEAPIOCTL - GetSizeofGenericExtension
00000018	3.60376215	C3_HEAPIOCTL - InitializeGenericExtension
00000019	3.60376310	C3_HEAPIOCTL - GenericInitializeRemoveLock
00000020	3.60376477	GENERIC - Initializing for C3_HEAPIOCTL
00000021	3.60376620	C3_HEAPIOCTL - GenericRegisterInterface
00000022	3.60376740	C3_HEAPIOCTL - FindInterfaceRecord
00000023	3.60408378	C3_HEAPIOCTL - DispatchPnp
00000024	3.60408568	C3_HEAPIOCTL - GenericDispatchPnp
00000025	3.60408735	C3_HEAPIOCTL - GenericAcquireRemoveLock
00000026	3.60408878	C3_HEAPIOCTL - DefaultPnpHandler
00000027	3.60409117	C3_HEAPIOCTL - GenericReleaseRemoveLock
00000028	3.60415077	C3_HEAPIOCTL - DispatchPnp
00000029	3.60415244	C3_HEAPIOCTL - GenericDispatchPnp
00000030	3.60415387	C3_HEAPIOCTL - GenericAcquireRemoveLock
00000031	3.60415554	C3_HEAPIOCTL - PNP Request (IRP_MN_FILTER_RESOURCE_REQUIREMENTS)
00000032	3.60415697	C3_HEAPIOCTL - DefaultPnpHandler
00000033	3.60415888	C3_HEAPIOCTL - GenericReleaseRemoveLock
00000034	3.60420394	C3_HEAPIOCTL - DispatchPnp
00000035	3.60420561	C3_HEAPIOCTL - GenericDispatchPnp
00000036	3.60420680	C3_HEAPIOCTL - GenericAcquireRemoveLock
00000037	3.60420871	C3_HEAPIOCTL - PNP Request (IRP_MN_START_DEVICE)
00000038	3.60421014	C3_HEAPIOCTL - HandleStartDevice
00000039	3.60421157	C3_HEAPIOCTL - ForwardAndWait
00000040	3.60421324	C3_HEAPIOCTL - OnRequestComplete
00000041	3.60421515	C3_HEAPIOCTL - StartDevice
00000042	3.60421658	C3_HEAPIOCTL - To WORKING from STOPPED
00000043	3.60421824	C3_HEAPIOCTL - GetPowerInfoFromRegistry
00000044	3.60423160	C3_HEAPIOCTL - EnableAllInterfaces
00000045	3.60423851	C3_HEAPIOCTL - AllowAllRequests
00000046	3.60423994	C3_HEAPIOCTL - RestartAllRequests
00000047	3.60424161	C3_HEAPIOCTL - GenericWakeupControl
00000048	3.60424304	C3_HEAPIOCTL - CompleteRequest
00000049	3.60424590	C3_HEAPIOCTL - GenericReleaseRemoveLock
00000050	3.60428572	C3_HEAPIOCTL - DispatchPnp
00000051	3.60428715	C3_HEAPIOCTL - GenericDispatchPnp
00000052	3.60428834	C3_HEAPIOCTL - GenericAcquireRemoveLock
00000053	3.60429025	C3_HEAPIOCTL - PNP Request (IRP_MN_QUERY_CAPABILITIES)
00000054	3.60429168	C3_HEAPIOCTL - HandleQueryCapabilities
00000055	3.60429287	C3_HEAPIOCTL - ForwardAndWait
00000056	3.60430598	C3_HEAPIOCTL - OnRequestComplete
00000057	3.60430765	C3_HEAPIOCTL - AdjustDeviceCapabilities
00000058	3.60430980	C3_HEAPIOCTL - AdjustWakeCapabilities
00000059	3.60431147	C3_HEAPIOCTL - GenericWakeupControl
00000060	3.60431266	C3_HEAPIOCTL - CompleteRequest
00000061	3.60431457	C3_HEAPIOCTL - GenericReleaseRemoveLock
00000062	3.60433149	C3_HEAPIOCTL - DispatchPnp
00000063	3.60433292	C3_HEAPIOCTL - GenericDispatchPnp
00000064	3.60433412	C3_HEAPIOCTL - GenericAcquireRemoveLock
00000065	3.60433602	C3_HEAPIOCTL - PNP Request (IRP_MN_QUERY_PNP_DEVICE_STATE)
00000066	3.60433769	C3_HEAPIOCTL - HandleQueryState
00000067	3.60433912	C3_HEAPIOCTL - DefaultPnpHandler
00000068	3.60434079	C3_HEAPIOCTL - GenericReleaseRemoveLock
00000069	3.60435987	C3_HEAPIOCTL - DispatchPnp
00000070	3.60436153	C3_HEAPIOCTL - GenericDispatchPnp
00000071	3.60436296	C3_HEAPIOCTL - GenericAcquireRemoveLock
00000072	3.60436463	C3_HEAPIOCTL - PNP Request (IRP_MN_QUERY_DEVICE_RELATIONS)
00000073	3.60436583	C3_HEAPIOCTL - DefaultPnpHandler
00000074	3.60436749	C3_HEAPIOCTL - GenericReleaseRemoveLock

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


UNICODE_STRING servkey;



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

	servkey.Buffer = (PWSTR)ExAllocatePool(PagedPool, RegistryPath->Length + sizeof(WCHAR));
	if (!servkey.Buffer)
	{
		KdPrint((DRIVERNAME " - Unable to allocate %d bytes for copy of service key name\n", RegistryPath->Length + sizeof(WCHAR)));
		return STATUS_INSUFFICIENT_RESOURCES;
	}

	servkey.MaximumLength = RegistryPath->Length + sizeof(WCHAR);
	RtlCopyUnicodeString(&servkey, RegistryPath);
	servkey.Buffer[RegistryPath->Length / 2] = 0;	// add a null terminator

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

	RtlFreeUnicodeString(&servkey);
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
	RtlInitUnicodeString(&devname, L"\\DosDevices\\C3_HEAPIOCTL");

	status = IoCreateDevice(DriverObject, xsize, &devname,
		FILE_DEVICE_UNKNOWN, FILE_DEVICE_SECURE_OPEN, FALSE, &fdo);
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
