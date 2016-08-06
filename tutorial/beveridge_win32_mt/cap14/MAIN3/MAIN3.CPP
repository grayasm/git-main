/*
 * Main3.cpp
 *
 * Sample code for "Multithreading Applications in Win32"
 * This code is discussed in the text but does
 * not have its own listing.
 *
 * Driver to load the simple DLL using dynamic
 * linking with LoadLibrary(), then showing the
 * effect of loading the library AFTER creating
 * the thread.
 */
 
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "MtVerify.h"

 
DWORD WINAPI ThreadFunc(LPVOID);

typedef BOOL _declspec(dllimport) (*THEFUNCTION)();
THEFUNCTION pTheFunction; 

// Give the worker thread something to wait for.
HANDLE ghEvent;

int main(VOID) 
{ 
	HINSTANCE hinstLib; 
	HANDLE hThrd;
	DWORD threadId;

	// The new thread can't continue right away because
	// the library is not loaded yet. We'll set this
	// event when everythings ready to roll.
	ghEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	MTVERIFY(ghEvent != NULL);

	hThrd = CreateThread(NULL,
		0,
		ThreadFunc,
		NULL,
		0,
		&threadId );
	MTVERIFY(hThrd != NULL);
	if (hThrd)
		printf("\tThread launched\n");
 
	printf("\tCalling LoadLibrary()\n");

	// Get a handle to the DLL module.
	hinstLib = LoadLibrary("SmallDll"); 
	if (hinstLib == NULL) 
	{
		fprintf(stderr, "LoadLibrary failed. Could not find SmallDll.DLL\n");
		return 1;
	}

	// Find the entry point into the library. It is a
	// C++ function, so we use the decorated name.
	pTheFunction = (THEFUNCTION) GetProcAddress(hinstLib, "?TheFunction@@YAHXZ");
	if (pTheFunction == NULL)
	{
		fprintf(stderr, "\nGetProcAddress failed. There is probably a\n");
		fprintf(stderr, "calling convention or parameter mismatch.\n\n");
		return 1;
	}
 
	MTVERIFY( SetEvent(ghEvent) );

	MTVERIFY( WaitForSingleObject(hThrd, INFINITE) == WAIT_OBJECT_0 );
	MTVERIFY( CloseHandle(hThrd) );

	// Free the DLL module.
	printf("\tCalling FreeLibrary()\n");
	FreeLibrary(hinstLib);

	return 0;
}
 
/*
 * Call a function to do something that terminates
 * the thread with ExitThread instead of returning.
 */
DWORD WINAPI ThreadFunc(LPVOID n)
{
	printf("\tThread running\n");

	WaitForSingleObject(ghEvent, INFINITE);

	pTheFunction();

	return 0;
}

