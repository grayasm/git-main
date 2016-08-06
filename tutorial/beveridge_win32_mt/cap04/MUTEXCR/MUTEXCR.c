/*
 * MUTEX.c
 * Mutex stands for MUTual EXclusion.
 * Only one thread at a time is allowed to own a mutex.
 * It takes 100 times longer to lock a mutex in kernel space
 * than a critical section in user space.
 * Mutexes can be used between processes, CS only within the same
 * process. 
 * One can specify a timeout when waiting on a mutex, but not a 
 * critical section.
 *
 * Create and take ownership of the mutex in main thread,
 * than release it to allow children threads to complete.
 * Clean up in the end.
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "MtVerify.h"

DWORD WINAPI ThreadFunc(LPVOID);

#define MAX_THREADS 6
HANDLE gMutex;

int main()
{
	HANDLE hThrds[MAX_THREADS];
	int i;
	int slot;
	DWORD threadId;
	DWORD rc;
	DWORD exitCode;

	// create & lock mutex (take ownership)
	MTVERIFY( gMutex = CreateMutex(NULL, TRUE, NULL) );

	for(i=0; i<MAX_THREADS; i++)
	{
		MTVERIFY( hThrds[i] = CreateThread(NULL,
			0,
			ThreadFunc,
			(LPVOID)i,
			0,
			&threadId) );
		printf("Launched thread %d\n", i);
	}

	printf("Threads blocked for 3 sec\n");
	Sleep(3000);

	MTVERIFY( ReleaseMutex(gMutex) );


	for(i=0; i<MAX_THREADS; ++i)
	{
		/* Wait for one thread at a time to terminate.
		 * Not optimal, purpose is only to experiment.
		 * Handle array must contain ONLY VALID values,
		 * otherwise it will not wait and will return -1
		 */
		rc = WaitForMultipleObjects(
			MAX_THREADS - i, 
			hThrds,
			FALSE, 
			INFINITE);

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

	/*
		Q: Should I take ownership of the mutex to close its handle ?
		rc = WaitForSingleObject(gMutex, INFINITE);
		CloseHandle(gMutex);

		Ownership has nothing to do with determining when a mutex
		will be destroyed. Like most other kernel objects, a mutex
		is destroyed when its reference drops to zero.
		The reference count is decremented whenever a thread calls
		CloseHandle() with the handle to a mutex, or when the thread
		exits.
	*/
	
	MTVERIFY( CloseHandle(gMutex) );

	printf("All slots + mutex terminated\n");

	return EXIT_SUCCESS;		
} // main



/*
 * This function just calls Sleep for a random amount of time,
 * thereby simulating some task takes time.
 *
 * the param "n" is the index into the handle array kept for
 * informational purposes.
 */
DWORD WINAPI ThreadFunc(LPVOID n)
{	
	// acquire lock on the mutex - enter critical section
	MTVERIFY( WaitForSingleObject(gMutex, INFINITE) == WAIT_OBJECT_0 );

	printf("Thread %d allowed\n", n);
	srand( GetTickCount() );
	Sleep((rand()%10)*800+500);
	printf("Thread %d idle\n", n);

	// release mutex - leave critical section
	MTVERIFY( ReleaseMutex(gMutex) );

	return ((DWORD)n);
}