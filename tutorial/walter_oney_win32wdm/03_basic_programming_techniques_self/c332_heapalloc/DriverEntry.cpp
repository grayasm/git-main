/*
	c3_heapalloc main program.
	Copyright (C) 2016 by Mihai Vasilian

	3.3.2 Heap Allocator

	The basic heap allocation service function in kernel mode is ExAllocatePoolWithTag.
	tag: a 4 character token within single quote.

	prototype is:	ExAllocatePoolWithTag (POOL_TYPE, bytes, tag)
					ExFreePoolWithTag(PVOID, tag);

	ExAllocatePoolWithTag (PagedPool, 32, 'Tag1');
	ExFreePoolWithTag(PVOID, 'Tag1')



00000022	2.67623734	C3_HEAPALLOC - Entering DriverEntry
00000023	2.67633104	C3_HEAPALLOC - Entering AddDevice: DriverObject 9E9DEE60, pdo 9EC3A080
00000024	2.67633343	C3_HEAPALLOC - ExAllocatePoolWithTag succeeded!
00000025	2.67633486	C3_HEAPALLOC - *(memptr + 0) = 0
00000026	2.67633605	C3_HEAPALLOC - *(memptr + 1) = 1
00000027	2.67633724	C3_HEAPALLOC - *(memptr + 2) = 2
00000028	2.67633843	C3_HEAPALLOC - *(memptr + 3) = 3
00000029	2.67633963	C3_HEAPALLOC - *(memptr + 4) = 4
00000030	2.67634082	C3_HEAPALLOC - *(memptr + 5) = 5
00000031	2.67634201	C3_HEAPALLOC - *(memptr + 6) = 6
00000032	2.67634344	C3_HEAPALLOC - *(memptr + 7) = 7
00000033	2.67634463	C3_HEAPALLOC - *(memptr + 8) = 8
00000034	2.67634583	C3_HEAPALLOC - *(memptr + 9) = 9
00000035	2.67634702	C3_HEAPALLOC - ExFreePoolWithTag succeeded!
00000036	2.67640114	C3_HEAPALLOC - DriverUnload: DriverObject 9E9DEE60

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

#define DRIVERNAME "C3_HEAPALLOC"


NTSTATUS AddDevice(PDRIVER_OBJECT, PDEVICE_OBJECT);
VOID DriverUnload(PDRIVER_OBJECT);


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
	
	const int BUFSIZE = 10;
	PVOID memptr = ExAllocatePoolWithTag(PagedPool, BUFSIZE * sizeof(int), 'Tag1'); // Raw1
	if (memptr == NULL)
	{
		KdPrint((DRIVERNAME " - ExAllocatePoolWithTag failed!\n"));
		return STATUS_UNSUCCESSFUL;
	}

	KdPrint((DRIVERNAME " - ExAllocatePoolWithTag succeeded!"));

	for (int i = 0; i < BUFSIZE; ++i)
		*((int*)memptr + i) = i;
	for (int i = 0; i < BUFSIZE; ++i)
		KdPrint((DRIVERNAME " - *(memptr + %d) = %d\n", i, *((int*)memptr + i)));


	ExFreePoolWithTag(memptr, 'Tag1');
	KdPrint((DRIVERNAME " - ExFreePoolWithTag succeeded!"));
	

	return STATUS_UNSUCCESSFUL;
}


#pragma PAGEDCODE
VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
	PAGED_CODE();
	KdPrint((DRIVERNAME " - DriverUnload: DriverObject %8.8lX\n", DriverObject));
}
