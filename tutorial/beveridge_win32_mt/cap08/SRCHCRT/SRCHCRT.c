/*
 * SrchCrt.c
 *
 * Uses multiple threads to search the files "*.c" in the current directory for
 * the string given on the command line.
 * This example uses the multithreaded version of the C run-time library so as
 * to be able to use the FILE functions as well as calloc and free.
 *
 * Build this file with the command line: cl /MD SrchCrt.c
 */

#include <windows.h>
#include <process.h> /* _beginthreadex, _endthreadex */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "MtVerify.h"


DWORD WINAPI SearchProc(void* arg);

#define MAX_THREADS		3

HANDLE hThreadLimitSemaphore;
char szSearchFor[1024];

int main(int argc, char** argv)
{
	WIN32_FIND_DATA *lpFindData;
	HANDLE hFindFile;
	HANDLE hThread;
	DWORD dummy;
	int i;



	if(argc != 2)
	{
		printf("Usage: %s <search-string>\n", argv[0]);
		// Ex: SRCHCRT.exe #include
		return EXIT_FAILURE;
	}

	/* copy search string where everyone can see it */
	strcpy(szSearchFor, argv[1]);

	/* Each thread will be given its own results buffer */
	/* THIS SAMPLE ALLOCATES MEMORY IN MAIN THREAD AND RELEASES IT IN CHILD THREAD */
	lpFindData = calloc(1, sizeof(WIN32_FIND_DATA));

	/* Semaphore prevents too many threads from running */
	MTVERIFY( hThreadLimitSemaphore = CreateSemaphore(
										NULL,			// security
										MAX_THREADS,	// initial available threads
										MAX_THREADS,	// max threads that can lock it
										NULL)			// no name
			);

	hFindFile = FindFirstFile("*.c", lpFindData);

	if(hFindFile == INVALID_HANDLE_VALUE)
		return EXIT_FAILURE;

	do
	{
		/* Acquire lock on semaphore, and release it in child thread */
		WaitForSingleObject(hThreadLimitSemaphore, INFINITE);

		MTVERIFY( hThread = (HANDLE) _beginthreadex(
											NULL,
											0,
											SearchProc,
											lpFindData,
											0,
											&dummy)
				);

		MTVERIFY( CloseHandle(hThread) );

		/* Allocate memory in main thread and release it in child thread. 
		 */
		lpFindData = calloc(1, sizeof(WIN32_FIND_DATA));
	}
	while( FindNextFile(hFindFile, lpFindData) );

	FindClose(hFindFile);

	/* Waiting for all thread by acquiring lock on semaphore from main thread
	   until all slots are taken = all threads finished.
     */
	for(i=0; i < MAX_THREADS; ++i)
	{
		WaitForSingleObject(hThreadLimitSemaphore, INFINITE);
	}

	MTVERIFY( CloseHandle(hThreadLimitSemaphore) );

	return EXIT_SUCCESS;
} // main


DWORD WINAPI /* same as __stdcall */ SearchProc(void *arg)
{
	WIN32_FIND_DATA *lpFindData = (WIN32_FIND_DATA*) arg;
	char buf[1024];
	FILE* fp;


	fp = fopen(lpFindData->cFileName, "r");
	if(!fp)
		return EXIT_FAILURE;


	while(fgets(buf, sizeof(buf), fp))
	{
		/* Inefficient search strategy, but it's easy */
		if(strstr(buf, szSearchFor))
			printf("%s: %s", lpFindData->cFileName, buf);
	}

	fclose(fp);

	/* THE MEMORY ALLOCATED WITH CALLOC IN MAIN THREAD IS RELEASED IN CHILD THREAD
	 * This is good sample on memory allocation/releasing within different threads.
	 */
	free(lpFindData);


	MTVERIFY( ReleaseSemaphore(hThreadLimitSemaphore, 1, NULL) );

	return EXIT_SUCCESS;
}