/*
	c3_ntstrsafe main program.
	Copyright (C) 2016 by Mihai Vasilian

	3.1.1 Using Standard Run-Time Library Functions

	RtlStringCchCopyA should be used instead of strcpy (wcscpy)
	See other functions in header: NtStrsafe.h
	
	Standard run-time library routines sometimes rely on initialization that can 
	happen only in a user-mode application and are sometimes implemented in a
	thread-unsafe or multiprocessor-unsafe way.

	THIS SAMPLE MOST PROBABLY THROWS EXCEPTION!!!!
	KDPRINT DOES NOT PRINT ANYTHING !!!
*/

#ifdef __cplusplus
extern "C" {
#endif

#include <wdm.h>
#include <ntstrsafe.h>

#ifdef __cplusplus
}
#endif



#define PAGEDCODE	code_seg("PAGE")
#define LOCKEDCODE	code_seg()
#define INITCODE	code_seg("INIT")

#define PAGEDDATA	data_seg("PAGEDATA")
#define LOCKEDDATA	data_seg()
#define INITDATA	data_seg("INITDATA")



#define DRIVERNAME "C3_NTSTRSAFE"

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

	// RtlStringCchCopyA
	NTSTRSAFE_PCSTR str1 = "Null terminated string.\0";
	char str2[100];
	if (RtlStringCchCopyA(str2, 99, str1) != STATUS_SUCCESS)
		KdPrint((DRIVERNAME " - RtlStringCchCopyA FAILED!"));
	else
		KdPrint((DRIVERNAME " - RtlStringCchCopyA SUCCEEDED, str2=%s\n", str2));


	// RtlStringCchPrintf
	char str3[100];
	if (RtlStringCchPrintfA(str3, 99, "RtlStringCchPrintfA(%s, %s, %s)", "Dest", "Size", "Src") != STATUS_SUCCESS)
		KdPrint((DRIVERNAME " - RtlStringCchPrintf FAILED!"));
	else
		KdPrint((DRIVERNAME " - RtlStringCchPrintf SUCCEEDED, str3=%s\n", str3));


	return STATUS_UNSUCCESSFUL;
}


#pragma PAGEDCODE
VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
	PAGED_CODE();
	KdPrint((DRIVERNAME " - DriverUnload: DriverObject %8.8lX\n", DriverObject));
}


