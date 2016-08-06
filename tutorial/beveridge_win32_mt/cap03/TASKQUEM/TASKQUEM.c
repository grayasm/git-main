/*
 * TASKQUEM.c
 * 
 * Call ThreadFunc NUM_TASKS times, using
 * no more than THREAD_POOL_SIZE threads.
 * This version uses WaitForMultipleObjects
 * to provide a more optimal solution.
 *
 * In TASKQUES.c the main thread waits for
 * threads notificationi in order of their 
 * creation.
 * Now the primary thread will be notified
 * immediately when a worker thread exits.
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "MtVerify.h"

DWORD WINAPI ThreadFunc(LPVOID);

#define THREAD_POOL_SIZE 3
#define MAX_THREAD_INDEX THREAD_POOL_SIZE-1
#define NUM_TASKS 6

int main()
{
	HANDLE hThrds[THREAD_POOL_SIZE];
	int slot = 0;
	DWORD threadId;
	int i;
	DWORD rc;
	
	for(i=1; i<=NUM_TASKS; i++)
	{
		/* Until we've used all threads in
		 * the pool, do not need to wait
		 * for one to exit.
		*/
		
		if(i>THREAD_POOL_SIZE)
		{
			/* Wait for one thread to terminate. */
			rc = WaitForMultipleObjects(
					THREAD_POOL_SIZE,
					hThrds,
					FALSE,
					INFINITE);
			
			slot = rc - WAIT_OBJECT_0;
			MTVERIFY( slot >= 0 && slot < THREAD_POOL_SIZE);
			printf("Slot %d terminated\n", slot);
			MTVERIFY( CloseHandle(hThrds[slot]) );
		}
		
		/* Create a new thread in the given available slot. */
		MTVERIFY( hThrds[slot] = CreateThread(NULL,
			0,
			ThreadFunc,
			(LPVOID)slot,
			0,
			&threadId) );
		printf("Launched thread #%d (slot %d)\n", i, slot++);
	}

	/* Now wait for all threads to terminate */
	rc = WaitForMultipleObjects(
		THREAD_POOL_SIZE,
		hThrds,
		TRUE,
		INFINITE);

	MTVERIFY( rc >= WAIT_OBJECT_0 && rc < WAIT_OBJECT_0 + THREAD_POOL_SIZE );
	
	for(slot=0; slot<THREAD_POOL_SIZE; slot++)
	  MTVERIFY( CloseHandle(hThrds[slot]) );
	
	printf("All slots terminated\n");

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
	srand( GetTickCount() );

	Sleep((rand()%10)*800+500);
	printf("Slot %d idle\n", n);
	return ((DWORD)n);
}























