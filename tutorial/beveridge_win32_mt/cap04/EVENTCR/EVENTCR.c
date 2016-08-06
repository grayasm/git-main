/*
 * EVENTCR.c - CreateEvent sample
 *
 * The most flexible type of synchronization object in Win32 is the
 * EVENT OBJECT. The event object is a kernel object whose only purpose
 * is to be either signaled or non-signaled. This state is under direct
 * program control. It does not change as a side effect of calling
 * WaitForSingleObject/similar functions.
 *
 * With CreateEvent() it is specified whether the event resets itself 
 * automatically to non-signaled after waking up a single thread or
 * it needs manually ResetEvent() in which case all waiting threads
 * WaitForSingleObject/similar will be woken up until event is reset.
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "MtVerify.h"


#define MAX_THREADS 9

HANDLE gEvent;

DWORD WINAPI ThreadFunc(LPVOID);

int main()
{
	HANDLE hThrds[MAX_THREADS];
	DWORD threadId;
	int i;
	BOOL rc;
	
	
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

	return EXIT_SUCCESS;
} // main


DWORD WINAPI ThreadFunc(LPVOID n)
{
	WaitForSingleObject(gEvent, INFINITE);

	printf("Running thread %d\n", n);
	srand( GetTickCount() );
	Sleep((rand()%10)*800+500);
	printf("Idle thread %d\n", n);
	
	return ((DWORD)n);
}
