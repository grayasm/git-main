// test.cpp : Defines the entry point for the console application.
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#include "stdafx.h"
#include <winioctl.h>
#include "..\sys\ioctls.h"

ULONG WINAPI ThreadRoutine(PVOID junk);
BOOL kill = FALSE;
HANDLE hevRunning;

///////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[])
	{
	OSVERSIONINFO vi = {sizeof(OSVERSIONINFO)};
	GetVersionEx(&vi);
	if (vi.dwPlatformId != VER_PLATFORM_WIN32_NT)
		{
		puts("This sample requires Windows 2000 or Windows Xp");
		return 1;
		}

	HANDLE hdevice = CreateFile("\\\\.\\FPUTEST", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hdevice == INVALID_HANDLE_VALUE)
		{
		printf("Unable to open FPUTEST device - error %d\n", GetLastError());
		return 1;
		}

	// Spawn a thread that will do a lot of floating point operations. We want to be sure there's
	// a context to save and restore when we call the driver.

	DWORD junk;

	hevRunning = CreateEvent(NULL, FALSE, FALSE, NULL);
	HANDLE hThread = CreateThread(NULL, 0, ThreadRoutine, NULL, 0, &junk);
	WaitForSingleObject(hevRunning, INFINITE);	// wait for thread to start
	CloseHandle(hevRunning);

	// Test the driver's use of floating point

	if (DeviceIoControl(hdevice, IOCTL_TEST_PASSIVE, NULL, 0, NULL, 0, &junk, NULL))
		puts("IOCTL_TEST_PASSIVE test succeeded");
	else
		printf("IOCTL_TEST_PASSIVE test failed - %8.8lX\n", GetLastError());

	if (DeviceIoControl(hdevice, IOCTL_TEST_DISPATCH, NULL, 0, NULL, 0, &junk, NULL))
		puts("IOCTL_TEST_DISPATCH test succeeded");
	else
		printf("IOCTL_TEST_DISPATCH test failed - %8.8lX\n", GetLastError());

	// Terminate the secondary thread

	kill = TRUE;
	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hdevice);
	return 0;
	}

///////////////////////////////////////////////////////////////////////////////

ULONG WINAPI ThreadRoutine(PVOID junk)
	{							// ThreadRoutine
	double random = 1.;
	BOOL firsttime = TRUE;

	while (!kill)
		{						// until told to quit
		random = random * 1.0000001;
		if (firsttime)
			SetEvent(hevRunning);	// release main thread once FPU in use
		firsttime = FALSE;
		}						// until told to quit

	printf("FPU loop terminated with %f\n", random);

	return 0;
	}							// ThreadRoutine