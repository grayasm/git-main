/*
	heapioctlapp application.
	Copyright (C) 1999 by Walter Oney


00000019	2.11030054	C3_HEAPIOCTL - DispatchCreate
00000020	2.11030245	C3_HEAPIOCTL - CompleteRequest
00000021	2.11030674	C3_HEAPIOCTL - DispatchControl
00000022	2.11030793	C3_HEAPIOCTL - GenericAcquireRemoveLock
00000023	2.11030889	C3_HEAPIOCTL - DoMemoryTest
00000024	2.11031008	C3_HEAPIOCTL - Beginning test for PagedPool
00000025	2.11175752	C3_HEAPIOCTL - Allocated 1FFFFE00 bytes okay
00000026	2.11370993	C3_HEAPIOCTL - Allocated 2FFFFE00 bytes okay
00000027	2.11599398	C3_HEAPIOCTL - Allocated 37FFFE00 bytes okay
00000028	2.11843896	C3_HEAPIOCTL - Allocated 3BFFFE00 bytes okay
00000029	2.12092614	C3_HEAPIOCTL - Allocated 3DFFFE00 bytes okay
00000030	2.12340975	C3_HEAPIOCTL - Allocated 3EFFFE00 bytes okay
00000031	2.12593818	C3_HEAPIOCTL - Allocated 3F7FFE00 bytes okay
00000032	2.12845206	C3_HEAPIOCTL - Allocated 3FBFFE00 bytes okay
00000033	2.13096476	C3_HEAPIOCTL - Allocated 3FDFFE00 bytes okay
00000034	2.13351011	C3_HEAPIOCTL - Allocated 3FEFFE00 bytes okay
00000035	2.13612151	C3_HEAPIOCTL - Allocated 3FF7FE00 bytes okay
00000036	2.13866591	C3_HEAPIOCTL - Allocated 3FFBFE00 bytes okay
00000037	2.13866901	C3_HEAPIOCTL - **** Largest allocation from PagedPool was 3FFBFE00 bytes (0003FFC0 pages) ****
00000038	2.13867044	C3_HEAPIOCTL - DoMemoryTest
00000039	2.13867188	C3_HEAPIOCTL - Beginning test for NonPagedPool
00000040	2.20788074	C3_HEAPIOCTL - Allocated 1FFFFE00 bytes okay
00000042	2.33773375	C3_HEAPIOCTL - Allocated 2FFFFE00 bytes okay
00000043	2.47734594	C3_HEAPIOCTL - Allocated 37FFFE00 bytes okay
00000045	2.61805606	C3_HEAPIOCTL - Allocated 3BFFFE00 bytes okay
00000046	2.76503110	C3_HEAPIOCTL - Allocated 3DFFFE00 bytes okay
00000047	2.93230700	C3_HEAPIOCTL - Allocated 3EFFFE00 bytes okay
00000048	3.09126043	C3_HEAPIOCTL - Allocated 3F7FFE00 bytes okay
00000051	3.24785495	C3_HEAPIOCTL - Allocated 3FBFFE00 bytes okay
00000053	3.41463518	C3_HEAPIOCTL - Allocated 3FDFFE00 bytes okay
00000054	3.56523061	C3_HEAPIOCTL - Allocated 3FEFFE00 bytes okay
00000055	3.71703529	C3_HEAPIOCTL - Allocated 3FF7FE00 bytes okay
00000056	3.88590479	C3_HEAPIOCTL - Allocated 3FFBFE00 bytes okay
00000057	3.88590908	C3_HEAPIOCTL - **** Largest allocation from NonPagedPool was 3FFBFE00 bytes (0003FFC0 pages) ****
00000058	3.88591146	C3_HEAPIOCTL - GenericReleaseRemoveLock
00000059	3.88591290	C3_HEAPIOCTL - CompleteRequest
00000060	3.88592649	C3_HEAPIOCTL - DispatchClose
00000061	3.88592815	C3_HEAPIOCTL - CompleteRequest

*/

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <stdio.h>
#include <windows.h>
#include <winioctl.h>

#define IOCTL_DO_TEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_NEITHER, FILE_ANY_ACCESS)


int main(int argc, char* argv[])
{
	HANDLE hdevice = CreateFile("\\\\.\\C3_HEAPIOCTL", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hdevice == INVALID_HANDLE_VALUE)
	{
		printf("Unable to open MEMTEST device - error %d\n", GetLastError());
		return 1;
	}

	DWORD junk;
	DeviceIoControl(hdevice, IOCTL_DO_TEST, NULL, 0, NULL, 0, &junk, NULL);
	
	CloseHandle(hdevice);
	return 0;
}

