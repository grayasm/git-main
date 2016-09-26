/*
	c3_pagedmem main program.
	Copyright (C) 2016 by Mihai Vasilian

	3.3.1 User-Mode and Kernel-Mode Address Spaces

	It is possible to LOCK/UNLOCK virtual addresses for CODE and DATA with few functions like:
	MmLockPagableCodeSection, MmUnlockPagableImageSection
	MmLockPagableDataSection, MmUnlockPagableImageSection
	MmPageEntireDriver, MmResetDriverPaging



00000023	2.46164250	C3_PAGEDMEM - Entering DriverEntry
00000024	2.46165943	C3_PAGEDMEM - All MmLockPagable{Code,Data}Section executed.
00000025	2.46171236	C3_PAGEDMEM - MmPageEntireDriver, MmResetDriverPaging executed.
00000026	2.46171403	C3_PAGEDMEM - Exiting  DriverEntry
00000027	2.46179724	C3_PAGEDMEM - Entering AddDevice: DriverObject 9D5A8740, pdo 9B6DF8D0
00000028	2.46184564	C3_PAGEDMEM - DriverUnload: DriverObject 9D5A8740


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

#define DRIVERNAME "C3_PAGEDMEM"


typedef struct tagDEVQUEUE
{
} DEVQUEUE, *PDEVQUEUE;

typedef struct tagDEVICE_EXTENSION
{
	DEVQUEUE dqReadWrite;			// queues for reads and writes
} DEVICE_EXTENSION, *PDEVICE_EXTENSION;



NTSTATUS AddDevice(PDRIVER_OBJECT DriverObject, PDEVICE_OBJECT pdo);
VOID DriverUnload(PDRIVER_OBJECT DriverObject);
NTSTATUS DispatchReadWrite(PDEVICE_OBJECT fdo, PIRP Irp);
PVOID hPageIdleSection;
PVOID hPageDataSection;

#pragma PAGEDDATA
ULONG ulSomething;



extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	KdPrint((DRIVERNAME " - Entering DriverEntry\n"));

	DriverObject->DriverExtension->AddDevice = AddDevice;
	DriverObject->DriverUnload = DriverUnload;
	DriverObject->MajorFunction[IRP_MJ_READ] = DispatchReadWrite;
	DriverObject->MajorFunction[IRP_MJ_WRITE] = DispatchReadWrite;
	
	
	// *** FOR CODE ***
	// Lock your pageable sections.
	hPageIdleSection = MmLockPagableCodeSection((PVOID)DispatchReadWrite);
	// Unlock the pages containing the PAGEIDLE section and allow them to move in and out of memory on demand
	MmUnlockPagableImageSection(hPageIdleSection);

	// *** FOR DATA ***
	// The PAGEIDLE section will once again be in nonpaged memory(but not necessarily the same physical memory as previously).
	// MmLockPagableSectionByHandle(hPageIdleSection); - not available
	hPageDataSection = MmLockPagableDataSection((PVOID)&ulSomething);
	MmUnlockPagableImageSection(hPageDataSection);
	// MmLockPagableSectionByHandle(hPageDataSection);

	KdPrint((DRIVERNAME " - All MmLockPagable{Code,Data}Section executed.\n"));


	MmPageEntireDriver((PVOID)DriverEntry);
	MmResetDriverPaging((PVOID)DriverEntry);

	KdPrint((DRIVERNAME " - MmPageEntireDriver, MmResetDriverPaging executed."));
	KdPrint((DRIVERNAME " - Exiting  DriverEntry\n"));


	return STATUS_SUCCESS;
}


#pragma PAGEDCODE
NTSTATUS AddDevice(PDRIVER_OBJECT DriverObject, PDEVICE_OBJECT pdo)
{
	PAGED_CODE();
	KdPrint((DRIVERNAME " - Entering AddDevice: DriverObject %8.8lX, pdo %8.8lX\n", DriverObject, pdo));


	return STATUS_UNSUCCESSFUL;
}


#pragma PAGEDCODE
VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
	PAGED_CODE();
	KdPrint((DRIVERNAME " - DriverUnload: DriverObject %8.8lX\n", DriverObject));
}

#pragma PAGEDCODE
NTSTATUS DispatchReadWrite(PDEVICE_OBJECT fdo, PIRP Irp)
{
	PAGED_CODE();
	KdPrint((DRIVERNAME " - Entering DispatchReadWrite(0x%x, 0x%x)\n", fdo, Irp));

	PDEVICE_EXTENSION pdx = (PDEVICE_EXTENSION)fdo->DeviceExtension; //PVOID member
	IoMarkIrpPending(Irp);
	// ... more activity here :)
	return STATUS_PENDING;
}
