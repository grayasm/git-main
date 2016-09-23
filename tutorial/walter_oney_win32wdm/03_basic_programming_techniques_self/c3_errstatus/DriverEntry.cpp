/*
	c3_errstatus main program.
	Copyright (C) 2016 by Mihai Vasilian

	3.2.1 Status Codes
	
	31 30     29       28       27  -  16 15  -  0   : NTSTATUS bits
	severity  customer reserved facility  code



00000030	12.53567982	C3_ERRSTATUS - Entering DriverEntry
00000031	12.53586769	C3_ERRSTATUS - Entering AddDevice: DriverObject 07ABA060, pdo 06078770
00000032	12.53587246	C3_ERRSTATUS - RtlAppendUnicodeStringToString FAILED - c0000023
00000033	12.53598309	C3_ERRSTATUS - DriverUnload: DriverObject 07ABA060

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



#define DRIVERNAME "C3_ERRSTATUS"

NTSTATUS AddDevice(PDRIVER_OBJECT DriverObject, PDEVICE_OBJECT pdo);
VOID DriverUnload(PDRIVER_OBJECT DriverObject);

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	KdPrint((DRIVERNAME " - Entering DriverEntry\n"));

	DriverObject->DriverExtension->AddDevice = AddDevice;
	DriverObject->DriverUnload = DriverUnload;

	return STATUS_SUCCESS;
}


#pragma PAGEDCODE
NTSTATUS AddDevice(PDRIVER_OBJECT DriverObject, PDEVICE_OBJECT pdo)
{
	PAGED_CODE();
	KdPrint((DRIVERNAME " - Entering AddDevice: DriverObject %8.8lX, pdo %8.8lX\n", DriverObject, pdo));

	UNICODE_STRING us1, us2;
	RtlInitUnicodeString(&us1, L"012345");
	RtlInitUnicodeString(&us2, L"0123456789");

	NTSTATUS retval = STATUS_SUCCESS;
	retval = RtlAppendUnicodeStringToString(&us1, &us2);
	if (!NT_SUCCESS(retval))
		KdPrint((DRIVERNAME " - RtlAppendUnicodeStringToString FAILED - %x\n", retval));
	// return UNSUCCESSFUL intentionally
	else
		KdPrint((DRIVERNAME " - RtlAppendUnicodeStringToString SUCCEEDED, us1 is now %s\n", us1.Buffer));
	
	return STATUS_UNSUCCESSFUL;
}


#pragma PAGEDCODE
VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
	PAGED_CODE();
	KdPrint((DRIVERNAME " - DriverUnload: DriverObject %8.8lX\n", DriverObject));
}


