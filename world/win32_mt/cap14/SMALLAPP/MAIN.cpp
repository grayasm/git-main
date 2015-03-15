/*
 * Main.cpp
 *
 * Driver to load the simple DLL, create a thread, call the DLL and exit.
 */

#include <windows.h>
#include <stdio.h>

_declspec(dllimport) BOOL TheFunction();
DWORD WINAPI ThreadFunc(LPVOID);

int main()
{
	HANDLE		hThrd;
	DWORD		dwThreadId;

	hThrd = CreateThread(
				NULL,
				0,
				ThreadFunc,
				NULL,
				0,
				&dwThreadId);

	if(hThrd)
		printf("\tThread launched\n");

	WaitForSingleObject(hThrd, INFINITE);
	CloseHandle(hThrd);

	return EXIT_SUCCESS;
} // main

/* Just call a function in the DLL and exit */
DWORD WINAPI ThreadFunc(LPVOID n)
{
	printf("\tThread running\n");

	TheFunction();

	return EXIT_SUCCESS;
} // ThreadFunc

