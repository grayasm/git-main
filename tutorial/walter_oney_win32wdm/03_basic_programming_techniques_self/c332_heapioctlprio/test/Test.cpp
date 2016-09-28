/*
	ExAllocatePoolWithTagPriority test sample.
	Copyright (C) 1999 by Walter Oney

00000028	7.10900784	C3_HEAPIOCTLPRIO - DispatchControl
00000029	7.10901117	C3_HEAPIOCTLPRIO - GenericAcquireRemoveLock
00000030	7.10901213	C3_HEAPIOCTLPRIO - DoMemoryTest
00000031	7.10901451	C3_HEAPIOCTLPRIO - ExAllocatePoolWithTagPriority succeeded!
00000032	7.10901594	C3_HEAPIOCTLPRIO - *(memptr + 0) = 0
00000033	7.10901785	C3_HEAPIOCTLPRIO - *(memptr + 1) = 1
00000034	7.10901880	C3_HEAPIOCTLPRIO - *(memptr + 2) = 2
00000035	7.10902071	C3_HEAPIOCTLPRIO - *(memptr + 3) = 3
00000036	7.10902166	C3_HEAPIOCTLPRIO - *(memptr + 4) = 4
00000037	7.10902309	C3_HEAPIOCTLPRIO - *(memptr + 5) = 5
00000038	7.10902405	C3_HEAPIOCTLPRIO - *(memptr + 6) = 6
00000039	7.10902548	C3_HEAPIOCTLPRIO - *(memptr + 7) = 7
00000040	7.10902643	C3_HEAPIOCTLPRIO - *(memptr + 8) = 8
00000041	7.10902739	C3_HEAPIOCTLPRIO - *(memptr + 9) = 9
00000042	7.10902977	C3_HEAPIOCTLPRIO - ExAllocatePoolWithTagPriority succeeded!
00000043	7.10903120	C3_HEAPIOCTLPRIO - GenericReleaseRemoveLock
00000044	7.10903215	C3_HEAPIOCTLPRIO - CompleteRequest
00000049	9.06664467	C3_HEAPIOCTLPRIO - DispatchClose
00000050	9.06664658	C3_HEAPIOCTLPRIO - CompleteRequest

*/

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <stdio.h>
#include <windows.h>
#include <winioctl.h>

#define IOCTL_DO_TEST CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_NEITHER, FILE_ANY_ACCESS)


int main(int argc, char* argv[])
{
	HANDLE hdevice = CreateFile("\\\\.\\C3_HEAPIOCTLPRIO", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hdevice == INVALID_HANDLE_VALUE)
	{
		printf("Unable to open C3_HEAPIOCTLPRIO device - error %d\n", GetLastError());
		return 1;
	}

	DWORD junk;
	DeviceIoControl(hdevice, IOCTL_DO_TEST, NULL, 0, NULL, 0, &junk, NULL);
	
	CloseHandle(hdevice);
	return 0;
}

