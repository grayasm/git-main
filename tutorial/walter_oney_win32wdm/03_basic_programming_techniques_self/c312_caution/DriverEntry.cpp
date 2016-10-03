/*
	c3_caution main program.
	Copyright (C) 2016 by Mihai Vasilian

	3.1.2 A Caution About Side Effects

	Never use an expression that has side effects as an argument to a kernel-mode 
	service function.
	In other words we don't know for sure if a kernel-mode function is a MACRO or
	a function, which makes a difference, because macros expand and arguments can
	be executed multiple times, when expected otherwise.	

00000029	4.33602285	C3_NTSTRSAFE - Entering DriverEntry
00000030	4.33607817	C3_NTSTRSAFE - Entering AddDevice: DriverObject 099B6060, pdo 0999A9C0
00000031	4.33607960	C3_NTSTRSAFE - Expected value for a=4 is 3
00000032	4.33611202	C3_NTSTRSAFE - DriverUnload: DriverObject 099B6060


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

#define SomeKernelFunction_SafeMin(x,y) (((x) < (y)) ? (x) : (y))

#pragma PAGEDCODE
NTSTATUS AddDevice(PDRIVER_OBJECT DriverObject, PDEVICE_OBJECT pdo)
{
	PAGED_CODE();
	KdPrint((DRIVERNAME " - Entering AddDevice: DriverObject %8.8lX, pdo %8.8lX\n", DriverObject, pdo));

	int a = 2, b = 42, c;
	c = SomeKernelFunction_SafeMin(a++, b);

	KdPrint((DRIVERNAME " - Expected value for a=%d is 3\n", a));


	return STATUS_UNSUCCESSFUL;
}


#pragma PAGEDCODE
VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
	PAGED_CODE();
	KdPrint((DRIVERNAME " - DriverUnload: DriverObject %8.8lX\n", DriverObject));
}


