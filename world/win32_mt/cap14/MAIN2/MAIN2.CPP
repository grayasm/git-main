/*
 * Main2.cpp
 *
 * Sample code for "Multithreading Applications in Win32"
 * This code is discussed in the text but does
 * not have its own listing.
 *
 * Driver to load the simple DLL using dynamic
 * linking with LoadLibrary(), create a thread,
 * call a function in the DLL, and exit.
 */
 
#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "MtVerify.h"

 
DWORD WINAPI ThreadFunc(LPVOID);

typedef BOOL _declspec(dllimport) (*THEFUNCTION)();
THEFUNCTION pTheFunction; 

int main(VOID) 
{ 
	HINSTANCE hinstLib; 
    HANDLE hThrd;
    DWORD threadId;
 
    printf("\tCalling LoadLibrary()\n");

    // Get a handle to the DLL module.
    hinstLib = LoadLibrary("SmallDll"); 
 
    // If the handle is valid, try to get the function address.
 
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

	hThrd = CreateThread(NULL,
	    0,
	    ThreadFunc,
	    NULL,
	    0,
	    &threadId );
	MTVERIFY(hThrd != NULL);
	if (hThrd)
	    printf("\tThread launched\n");
 
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

	pTheFunction();

    return 0;
}

