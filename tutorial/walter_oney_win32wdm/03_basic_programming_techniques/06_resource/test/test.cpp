/*
	test.cpp : Defines the entry point for the console application.
	Copyright (C) 1999 by Walter Oney
*/


#include "stdafx.h"
#include <winioctl.h>
#include "..\sys\ioctls.h"

int main(int argc, char* argv[])
{
	HANDLE hdevice = CreateFile("\\\\.\\RESOURCE", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hdevice == INVALID_HANDLE_VALUE)
	{
		printf("Unable to open RESOURCE device - error %d\n", GetLastError());
		return 1;
	}

	DWORD junk;
	volatile DWORD version;

	version = 0;
	if (DeviceIoControl(hdevice, IOCTL_GET_VERSION, NULL, 0, (PVOID) &version, sizeof(version), &junk, NULL))
		printf("Using RESOURCE.SYS version %d.%2.2d\n", HIWORD(version), LOWORD(version));
	else
		printf("Error %d in IOCTL_GET_VERSION\n", GetLastError());

	CloseHandle(hdevice);
	return 0;
}
