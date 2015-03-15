/*
 * EVENTOP.c - OpenEvent sample
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

DWORD WINAPI ThreadFunc(LPVOID);

int main()
{
	HANDLE hThrds[MAX_THREADS];
	HANDLE hEvent;
	DWORD threadId;
	int i;
	BOOL rc;
	DWORD slot;
	DWORD exitCode;
	
	
	/* Event resets automatically after first thread is unlocked.
	 * Initial state not signaled - SetEvent() will unlock a thread at a time.
	 * Named Event (kernel) object - each thread will OpenEvent() by its name.
	 */
	MTVERIFY( hEvent = CreateEvent(
		NULL,
		FALSE,					// automatically reset itself
		FALSE,					// initial state not signaled
		TEXT("EVENTOP"))		// named event (kernel) object
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


	/* SetEvent() will wake up only one thread. Event will be reset automatically.
	 * We need to follow the status of each thread individually until all finish.
	 */
	for(i=0; i<MAX_THREADS; ++i)
	{
		/* Wake up one thread at a time (random order presumably) */
		MTVERIFY( SetEvent(hEvent) );


		/* Wait for currently running thread to terminate.
		 * "hThrds" carefully changed to contain only valid handles,
		 * otherwise WaitForMultipleObject returns immediately -1
		 */
		rc = WaitForMultipleObjects(
			MAX_THREADS - i, 
			hThrds,
			FALSE, 
			INFINITE);

		/* Clean up */
		slot = rc - WAIT_OBJECT_0;				
		MTVERIFY( slot >= 0 && slot < MAX_THREADS );
		MTVERIFY( GetExitCodeThread(hThrds[slot], &exitCode) );
		MTVERIFY( CloseHandle(hThrds[slot]) );

		printf("Thread %d terminated\n", exitCode);		

		
		/* WaitForMultipleObjects() will wait and notify only 
		 * for handles of running threads.
		 * If an invalid/finished thread handle is passed 
		 * the function returns immediately -1
		 */ 
		for(; slot < MAX_THREADS-1; ++slot)
			hThrds[slot] = hThrds[slot+1];
	}

	/* Clean up event (kernel) object */
	MTVERIFY( CloseHandle(hEvent) );

	printf("All threads + Event cleaned up\n");

	return EXIT_SUCCESS;
} // main


DWORD WINAPI ThreadFunc(LPVOID n)
{
	HANDLE eventH;
	/* OpenEvent() by its name.
	 * Event can be opened by threads in other processes too.
	 * Retrieve event handle.
	 * Don't forget to CloseHandle()
	 */
	MTVERIFY( eventH = OpenEvent(
						EVENT_ALL_ACCESS, 
						FALSE, 
						TEXT("EVENTOP")) 
		);
	

	/* Wait for the event to become signaled */
	WaitForSingleObject(eventH, INFINITE);

	printf("Running thread %d\n", n);
	srand( GetTickCount() );
	Sleep((rand()%10)*800+500);
	printf("Idle thread %d\n", n);

	/* Release handle to event object */
	MTVERIFY( CloseHandle(eventH) );
	
	return ((DWORD)n);
}
