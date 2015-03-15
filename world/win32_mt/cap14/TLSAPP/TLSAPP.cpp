/*
 * Chapter 14 - Building DLLs - Thread Local Storage
 *
 *
 * TLS is a mechanism whereby a thread can keep a pointer to its own copy of a 
 * data structure. Both the C run-time library and MFC use of TLS.
 * The C run-time keeps values such as errno and the strtok() pointer in a thread
 * local structure because their state must be preserved between calls without
 * interference between threads.
 *
 * MFC uses TLS to keep track of handles to GDI and USER objects (CWnd, CPen, etc)
 * on a per thread basis, and verifies that objects are not being passed between
 * threads.
 *
 * TLS works by giving each thread an array of 4-byte slots, guaranteed to have
 * at least TLS_MINIMUM_AVAILABLE entries in it.
 *
 * Use: TlsAlloc(), TlsSetValue(), TlsGetValue(), TlsFree()
 * Listing 14-4
 *
 * Here the code calls a method of a DLL that uses TLS.
 */



#include <windows.h>
#include <stdio.h>
#include "MtVerify.h"

_declspec(dllimport) BOOL TheFunction();
DWORD WINAPI ThreadFunc(LPVOID);

#define MAX_THREADS 10
HANDLE hMutex;

int main()
{
	HANDLE		hThrds[MAX_THREADS];
	DWORD		threadId;
	int i;
	DWORD rc;

	MTVERIFY( hMutex = CreateMutex(NULL, FALSE, NULL) );

	for(i=0; i < MAX_THREADS; ++i)
	{
		MTVERIFY( hThrds[i] = CreateThread(
								NULL,
								0,
								ThreadFunc,
								(LPVOID)i,
								0,
								&threadId));
		
		printf("\n\tLaunched %d, id: %d", i, threadId);
	}

	rc = WaitForMultipleObjects(
			MAX_THREADS,
			hThrds, 
			TRUE,
			INFINITE);
	MTVERIFY( rc >= WAIT_OBJECT_0 && rc < WAIT_OBJECT_0 + MAX_THREADS );

	for(i=0; i < MAX_THREADS; ++i)
		MTVERIFY( CloseHandle(hThrds[i]) );

	MTVERIFY( CloseHandle(hMutex) );

	printf("\n\tExit\n\n");

	return EXIT_SUCCESS;
} // main



/* Just call a function in the DLL and exit */
DWORD WINAPI ThreadFunc(LPVOID n)
{
	Sleep( rand() % 1000 );

	MTVERIFY( WaitForSingleObject(hMutex, INFINITE) == WAIT_OBJECT_0 );

	printf("\n\trunning %d", n);
	
	TheFunction();

	printf("\n\tidle %d", n);

	MTVERIFY( ReleaseMutex(hMutex) );

	return EXIT_SUCCESS;
} // ThreadFunc

