/*
	c3_addrspaces main program.
	Copyright (C) 2016 by Mihai Vasilian

	3.3.1 User-Mode and Kernel-Mode Address Spaces



00000017	2.09402728	C3_ADDRSPACES - Entering DriverEntry
00000018	2.09412932	C3_ADDRSPACES - Entering AddDevice: DriverObject 92FA9C30, pdo 92F7BD80
00000019	2.09413195	C3_ADDRSPACES - PAGE_SIZE: hex=0x1000 dec=4096 bytes
00000020	2.09413362	C3_ADDRSPACES - 1 << PAGE_SHIFT is hex=0x1000 dec=4096 bytes
00000021	2.09413505	C3_ADDRSPACES - fire an ASSERT immediately.
00000022	2.09414005
00000023	2.09414077	*** Assertion failed: PAGE_SIZE != (1<<PAGE_SHIFT)
00000024	2.09414124	***   Source File: D:\workdir\GitHub\git-main\tutorial\walter_oney_win32wdm\03_basic_programming_techniques_self\c331_addrspaces\DriverEntry.cpp, line 75
00000025	2.09414172
00000026	2.09414363	C3_ADDRSPACES - ROUND_TO_PAGES(4095)= 4096 (dec)
00000027	2.09414506	C3_ADDRSPACES - ROUND_TO_PAGES(4097)= 8192 (dec)
00000028	2.09414649	C3_ADDRSPACES - BYTES_TO_PAGES(4095) = 1 (dec)
00000029	2.09414816	C3_ADDRSPACES - BYTES_TO_PAGES(4097) = 2 (dec)
00000030	2.09415030	C3_ADDRSPACES - BYTE_OFFSET(0xec346520) = 0x520 which means start is at=0xec346000
00000031	2.09415269	C3_ADDRSPACES - PAGE_ALIGN(0xec346520) = 0xec346000 which should be similar as above.
00000032	2.09415483	C3_ADDRSPACES - ADDRESS_AND_SIZE_TO_SPAN_PAGES(0xec346520, 4096) = 2
00000033	2.09421206	C3_ADDRSPACES - DriverUnload: DriverObject 92FA9C30


	Code executing at or above interrupt request level (IRQL) DISPATCH_LEVEL cannot cause page faults.
	
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



#define DRIVERNAME "C3_ADDRSPACES"

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

	KdPrint((DRIVERNAME " - PAGE_SIZE: hex=0x%x dec=%d bytes\n", PAGE_SIZE, PAGE_SIZE));
	KdPrint((DRIVERNAME " - 1 << PAGE_SHIFT is hex=0x%x dec=%d bytes\n", (1 << PAGE_SHIFT), (1 << PAGE_SHIFT)));
	KdPrint((DRIVERNAME " - fire an ASSERT immediately.\n"));
	ASSERT(PAGE_SIZE != (1<<PAGE_SHIFT));

	
	// ROUND_TO_PAGES(X) rounds a size in bytes to the next-higher page boundary.
	int _1page = 4095;
	int _2page = 4097;
	int _1bytes = ROUND_TO_PAGES(_1page);
	int _2bytes = ROUND_TO_PAGES(_2page);
	
	KdPrint((DRIVERNAME " - ROUND_TO_PAGES(4095)= %d (dec)\n", _1bytes));
	KdPrint((DRIVERNAME " - ROUND_TO_PAGES(4097)= %d (dec)\n", _2bytes));

	// BYTES_TO_PAGES(X) determines how many pages are required to hold a given
	//					 number of bytes BEGINNING at the start of a page.
	int _1pages = BYTES_TO_PAGES(_1page);
	int _2pages = BYTES_TO_PAGES(_2page);

	KdPrint((DRIVERNAME " - BYTES_TO_PAGES(4095) = %d (dec)\n", _1pages));
	KdPrint((DRIVERNAME " - BYTES_TO_PAGES(4097) = %d (dec)\n", _2pages));
	
	// BYTE_OFFSET(X) returns the byte offset portion of a virtual address.
	int _1offset = BYTE_OFFSET(&_1page);
	int _1start = (int)&_1page - _1offset;
	KdPrint((DRIVERNAME " - BYTE_OFFSET(0x%x) = 0x%x which means start is at=0x%x\n", &(_1page), _1offset, _1start));
	
	// PAGE_ALIGN(X) rounds a virtual address down to a page boundary.
	int* _2start = (int*)PAGE_ALIGN(&_1page);
	KdPrint((DRIVERNAME " - PAGE_ALIGN(0x%x) = 0x%x which should be similar as above.", &(_1page), _2start));

	// ADDRESS_AND_SIZE_TO_SPAN_PAGES(address, bytes) returns the number of page frames
	//												  occupied by a specified number of bytes
	//												  BEGINNING at a specified virtual address.
	// start + 4096 is always more than 1 page
	_1pages = ADDRESS_AND_SIZE_TO_SPAN_PAGES(&(_1page), 4096);
	KdPrint((DRIVERNAME " - ADDRESS_AND_SIZE_TO_SPAN_PAGES(0x%x, 4096) = %d\n", &(_1page), _1pages));


	return STATUS_UNSUCCESSFUL;
}


#pragma PAGEDCODE
VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
	PAGED_CODE();
	KdPrint((DRIVERNAME " - DriverUnload: DriverObject %8.8lX\n", DriverObject));
}


