/*
 * THRDTERM.c - Terminating a Thread in a safe way - sample.
 *
 * The approved way in Win32 to cause a thread to terminate is to 
 * set a flag in your code that asks the thread to terminate itself.
 * This technique has the obvious advantage that the target thread can
 * guarantee that it is in a safe and consistent state before it exits
 * compared with TerminateThread() which doesn't give any chance for
 * clean up, thread's stack is not deallocated causing large memory leak,
 * and any DLL attached to the thread will not be notified that the thread
 * is detaching.
 *
 * In this sample we will start 2 threads, which will periodically check
 * an event object to see if it is time to exit.
 *
 * Demonstrating how to request threads to exit.
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include "MtVerify.h"


DWORD WINAPI ThreadFunc(LPVOID);

HANDLE hRequestExitEvent = FALSE;

int main()
{
	HANDLE	hThreads[2];
	DWORD	threadId;
	int i;

	hRequestExitEvent = CreateEvent(
		NULL,
		TRUE,		// manual reset
		FALSE,		// initial state
		NULL);		// name

	
	for(i=0; i<2; ++i)
	{
		MTVERIFY( hThreads[i] = CreateThread(
									NULL,
									0,
									ThreadFunc,
									(LPVOID)i,
									0,
									&threadId)
									);

		printf("Launched thread %d\n", i);
	} // for

	
	printf("Sleep 1 sec\n");

	// wait around for awhile, make sure the thread is running.
	Sleep(1000);

	printf("Stop all threads\n");

	/* Request all threads to terminate */
	SetEvent(hRequestExitEvent);

	/* Get confirmation all threads finished */
	WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);

	/* Clean up */
	for(i=0; i<2; ++i)
		MTVERIFY( CloseHandle(hThreads[i]) );

	MTVERIFY( CloseHandle(hRequestExitEvent) );

	printf("All threads + event cleaned up\n");

	return EXIT_SUCCESS;
} // main



DWORD WINAPI ThreadFunc(LPVOID n)
{
	int i;
	int inside = 0;

	UNREFERENCED_PARAMETER(n);

	/* Seed the random-number generator */
	srand( (unsigned) time(NULL) );

	/* calculate the value of PI */
	for(i=0; i<1000000; ++i)
	{
		double x = (double) (rand())/RAND_MAX;
		double y = (double) (rand())/RAND_MAX;

		if((x*x + y*y) <= 1.0)
			inside++;

		/* Test for TERM condition */
		if( WaitForSingleObject(hRequestExitEvent, 0) != WAIT_TIMEOUT )
		{
			printf("Thread %d received request to terminate\n", n);
			return (DWORD)-1;
		}

		if(((int)n)%2) 
			Sleep(rand()%10); // slow down a bit
	}

	printf("PI = %.4g\n", (double)inside / i*4);

	return EXIT_SUCCESS;
} // ThreadFunc

















