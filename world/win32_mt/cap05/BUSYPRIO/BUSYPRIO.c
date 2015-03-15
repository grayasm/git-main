/*
 */




#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "MtVerify.h"


DWORD WINAPI ThreadFunc(LPVOID);

int main()
{
	HANDLE hThreads[2];
	int i;
	DWORD exitCode;
	DWORD threadId;
	DWORD elapsed, begin;
	DWORD rc;
	DWORD slot;


	for(i=0; i<2; ++i)
	{
		MTVERIFY( hThreads[i] = CreateThread(
									NULL,
									0,
									ThreadFunc,
									(LPVOID)i,
									CREATE_SUSPENDED,
									&threadId) 
									);

		printf("Launched suspended %d\n", i);
	}


	/*	PRIORITY-CLASS applies to a PROCESS not a thread
	 *
	 *	HIGH_PRIORITY_CLASS		=0X80
	 *	IDLE_PRIORITY_CLASS		=0X40
	 *	NORMAL_PRIORITY_CLASS	=0X20
	 *	REALTIME_PRIORITY_CLASS	=0x100
	 *
	 * SetPriorityClass(process, IDLE_PRIORITY_CLASS)
	 */


	/*	THREAD_PRIORITY_ABOVE_NORMAL	= +1
	 *	THREAD_PRIORITY_BELOW_NORMAL	= -1
	 *	THREAD_PRIORITY_HIGHEST			= +2
	 *	THREAD_PRIORITY_LOWEST			= -2
	 *	THREAD_PRIORITY_NORMAL			=  0
	 *  THREAD_PRIORITY_TIME_CRITICAL	=+15
	 */
	MTVERIFY( SetThreadPriority(hThreads[0], THREAD_PRIORITY_BELOW_NORMAL) );
	MTVERIFY( SetThreadPriority(hThreads[1], THREAD_PRIORITY_TIME_CRITICAL) );


	printf("Process priority class 0x%x\n", GetPriorityClass(GetCurrentProcess()));

	/* Run */
	begin = GetTickCount();

	ResumeThread(hThreads[0]);
	ResumeThread(hThreads[1]);


	for(i=0; i<2; ++i)
	{
		rc = WaitForMultipleObjects(
				2 - i, 
				hThreads, 
				FALSE, 
				INFINITE);

		MTVERIFY( rc >= WAIT_OBJECT_0 && rc < WAIT_OBJECT_0 + 2);
		elapsed = GetTickCount() - begin;
		slot = rc - WAIT_OBJECT_0;
		MTVERIFY( GetExitCodeThread(hThreads[slot], &exitCode) );
		MTVERIFY( CloseHandle(hThreads[slot]) );
		
		// move valid handle
		if(slot == 0)
			hThreads[0] = hThreads[1];

		//print info
		printf("Thread %d: %d.%.03d seconds\n", exitCode, elapsed/1000, elapsed%1000);
	}

	return EXIT_SUCCESS;
} // main


DWORD WINAPI ThreadFunc(LPVOID n)
{
	int i;
	int inside = 0;
	double val;


	printf("Priority level of worker thread %d: %d\n",
		n, 
		GetThreadPriority(GetCurrentThread()));

	/* Seed the random-number generator */
	srand( (unsigned)time( NULL ) );

	for (i=0; i<10000000; i++)
	{
		double x = (double)(rand())/RAND_MAX;
		double y = (double)(rand())/RAND_MAX;
		if ( (x*x + y*y) <= 1.0 )
			inside++;
	}
	val = (double)inside / i;
	printf("PI = %.4g\n", val*4);

	printf("Thread %d idle\n", n);
	return (DWORD) n;
}