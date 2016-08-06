/*
 * INTERLOCK.c - Interlocked Variables Sample
 *
 * The simplest type of synchronization mechanism is using the interlocked
 * functions that operate on standard 32-bit long variables.
 * 64-bit functions have separate names (64 postfix)
 * These functions provide no ability to wait; they simply guarantee that
 * access to a particular variable will be sequential. 
 * 
 * To mentain mutual exclusion with access to a single 32-bit counter you
 * would need to create a critical section or a mutex, acquire ownership, 
 * do the operation and release ownership. This is quite a bit of work for a
 * 32-bit variable whose access time will be two or three machine operations.
 * The overhead is likely to be over two orders of magnitude compared to the
 * work that needs to be done.
 * A counter like these would need to be used for reference counting, such as
 * handles inside the kernel. Typically when a reference count drops to zero,
 * the object is destroyed. You could either decrement the variable or test
 * for equality with zero with a single operation, but not both. The function
 * InterlockedDecrement() does this all at once. It subtracts one from variable,
 * then compares the result with zero and returns the result of the comparison.
 *
 * InterlockedIncrement(), InterlockedDecrement(),InterlockedExchange()
 */



#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "MtVerify.h"


#define MAX_THREADS 3

HANDLE	gEvent;
LONG	gCounter;

DWORD WINAPI ThreadFunc(LPVOID);

int main()
{
	HANDLE hThrds[MAX_THREADS];
	DWORD threadId;
	int i;
	BOOL rc;
	
	
	/* Set value of the global counter */
	gCounter = 0;


	/* Event needs manual reset: ResetEvent to set "not signaled (busy)" state.
	 * Initial state not signaled - SetEvent() will unlock threads, "signaled (run)" state.
	 * Unnamed, it will be accessed by threads via global handle.
	 */
	MTVERIFY( gEvent = CreateEvent(
		NULL,
		TRUE,		// manual reset
		FALSE,		// initial state not signaled
		NULL)		// unnamed kernel object (Event)
		);

	/* Start all threads - all locked waiting for the Event to become signaled */
	for(i=0; i<MAX_THREADS; ++i)
	{
		MTVERIFY( hThrds[i] = CreateThread(
			NULL,
			0,
			ThreadFunc,
			(LPVOID)i,
			0,
			&threadId)
			);
		printf("Launched thread %d\n", i);
	}

	printf("Sleep 3 seconds before SetEvent()\n");
	Sleep(3000);

	/* Allow all threads waiting for gEvent to run */
	MTVERIFY( SetEvent(gEvent) );

	/* Wait for all threads to finish */
	rc = WaitForMultipleObjects(
			MAX_THREADS, 
			hThrds,
			TRUE, 
			INFINITE);

	MTVERIFY( rc >= WAIT_OBJECT_0 && rc < WAIT_OBJECT_0 + MAX_THREADS );
	
	for(i=0; i<MAX_THREADS; ++i)
		MTVERIFY( CloseHandle(hThrds[i]) );

	/* Clean up event (kernel) object */
	MTVERIFY( CloseHandle(gEvent) );

	printf("All threads + Event cleaned up\n");

	/* Check final gCount value */
	/* 3 threads += (100 + 200 + 300)
	             -= (50 +  100 + 150)
				 =  300
	 */
	printf("Final counter value= %d\n", gCounter);
	printf("Is it 300 ??\n");

	return EXIT_SUCCESS;
} // main


/*
 * InterlockedIncrement(&gCounter);
 * InterlockedDecrement(&gCounter);
 * InterlockedExchange() - not tested here.
 */

DWORD WINAPI ThreadFunc(LPVOID n)
{
	int count;
	int i;
	LONG prev;

	/* Wait for signal to run the job */
	WaitForSingleObject(gEvent, INFINITE);

	/* ready to use interlocked functions */
	printf("Running th: %d\n", n);

	/* Each thread increments with:
	 * Th:0 +100, Th:1 +200, Th:2 + 300
	 * gCounter = +600
	 */
	count = ((int)n+1) * 100;
	for(i=0; i<count; ++i)
	{
		prev = InterlockedIncrement(&gCounter);
		Sleep((rand())%10);
	}
	
	printf("Thread %d final inc: %d\n", n, prev);


	/* Each thread decrements with:
	 * Th:0 -50, Th:1 -100, Th:2 -150
	 * gCounter = +300
	 */
	count = ((int)n+1) * 50;
	for(i=0; i<count; ++i)
	{
		prev = InterlockedDecrement(&gCounter);
		Sleep((rand())%10);
	}

	printf("Thread %d final dec: %d\n", n, prev);

	/* Overall, final gCounter should be: +300 */
	return (DWORD) n;
}










