/*
	memtestapp application.
	Copyright (C) 1999 by Walter Oney
*/

#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

#include <stdio.h>
#include <windows.h>
#include <winioctl.h>
#include "..\sys\ioctls.h"

int main(int argc, char* argv[])
{
	HANDLE hdevice = CreateFile("\\\\.\\MEMTEST", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
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

