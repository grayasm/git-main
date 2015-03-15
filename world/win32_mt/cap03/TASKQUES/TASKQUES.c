/*
 * Call ThreadFunc NUM_TASKS times, using no more than
 * THREAD_POOL_SIZE threads. This version uses 
 * WaitForSingleObject which gives a very suboptimal
 * solution bacause it assumes that the threads will exit
 * in the order that they were started.
 * 
 * Each thread prints "Slot x idle" when it exits,
 * and the primary thread prints "Slot x terminated"
 * when it notices that a thread has terminated.
 *
 * Suboptimal because main thread waits in for loop
 * for slots in order 0,1,2 although slots become
 * free in totally random order as threads complete.
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
	DWORD exitCode;

	/*
	 *              i=   1 2 3 4 5 6 7 8 9
	 * Start Thread      x x x x x x
	 * Wait on thread          x x x x x x
	*/

	for(i=1; i<=NUM_TASKS+THREAD_POOL_SIZE; i++)
	//       i <= 9
	{
		if(i>THREAD_POOL_SIZE)
		//     i > 3
		{
			WaitForSingleObject(hThrds[slot], INFINITE);
			MTVERIFY( GetExitCodeThread(hThrds[slot], &exitCode) );
			printf("Slot %d terminated\n", exitCode);
			MTVERIFY( CloseHandle(hThrds[slot]) );
		}

		if(i<=NUM_TASKS)
		//    i <= 6
		{
			MTVERIFY( hThrds[slot] = CreateThread(NULL,
				0,
				ThreadFunc,
				(LPVOID)slot,
				0,
				&threadId) );
			printf("Launched thread #%d (slot %d)\n", i, slot);
		}
		if(++slot > MAX_THREAD_INDEX)
		//    slot > 2
			slot = 0;
	}

	return EXIT_SUCCESS;
}; // main

/*
 * This function just calls Sleep for a random amount of time,
 * thereby simulating some task that takes time.
 * 
 * The param "n" is the index into the handle array, kept for
 * informational purposes.
*/

DWORD WINAPI ThreadFunc(LPVOID n)
{
	srand( GetTickCount() );

	Sleep((rand()%10)*800+500);
	printf("Slot %d idle\n", n);
	return ((DWORD)n);
}