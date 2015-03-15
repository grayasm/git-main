/*
 * CRITICAL_SECTION is not a kernel object, so there is no
 * handle to a critical section. It exists in the process's
 * memory space. 
 * The shared resource is not a resource from a resource file.
 * The resource could be a single memory location, a data 
 * structure, a file, or anything else where MUTUAL EXCLUSION
 * must be enforced so that only one thread is allowed to 
 * access the resource at a time.
 *
 * CRITICAL_SECTION is a high-level mechanism for hardware
 * "Test and Set" instruction.
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "MtVerify.h"


DWORD WINAPI ThreadFunc(LPVOID);

#define MAX_THREADS 6
CRITICAL_SECTION gCritical_section;

int main()
{
	HANDLE hThreads[MAX_THREADS];
	int i;
	DWORD threadId;
	DWORD rc;

	// initialize critical section data
	InitializeCriticalSection(&gCritical_section);
	printf("Critical section: initialized\n");

	for(i=0; i<MAX_THREADS; i++)
	{
		MTVERIFY( hThreads[i] = CreateThread(NULL,
			0,
			ThreadFunc,
			(LPVOID)i,
			0,
			&threadId) 
			);

		printf("Launched thread %d\n", i);
	}

	/* Now wait for all threads to terminate */
	rc = WaitForMultipleObjects(
			MAX_THREADS, 
			hThreads, 
			TRUE, 
			INFINITE);

	MTVERIFY( rc >= WAIT_OBJECT_0 && rc < WAIT_OBJECT_0 + MAX_THREADS );
	
	for(i=0; i<MAX_THREADS; i++)
		MTVERIFY( CloseHandle(hThreads[i]) );

	printf("All threads terminated\n");

	// clean up
	DeleteCriticalSection(&gCritical_section);

	printf("Critical section: clean\n");

	return EXIT_SUCCESS;
} // main

DWORD WINAPI ThreadFunc(LPVOID n)
{	
	// ask permission to enter a critical section
	EnterCriticalSection(&gCritical_section);

	/*
	 * A thread is allowed to reenter a critical section multiple times given
	 * that every Enter... is matched by a coresponding Leave...
	 * Don't lock a resource for a long time.
	 * Never call Sleep() or WaitForSingleObject or similar inside a critical section.
	 * 
	 * Disavantage: there is no way to tell if the thread currently inside a critical
	 * section is still alive. Since the critical section is not a kernel object, the
	 * kernel does not clean up if a thread inside the critical section EXITS or 
	 * CRASHES without calling LeaveCriticalSection(). For this functionality a
	 * Mutex should be used instead.
	 */
	 
	printf("Thread %d allowed\n", n);
	srand( GetTickCount() );
	Sleep((rand()%10)*800+500);
	printf("Thread %d idle\n", n);

	// ready to leave the critical section
	LeaveCriticalSection(&gCritical_section);

	return ((DWORD)n);
}