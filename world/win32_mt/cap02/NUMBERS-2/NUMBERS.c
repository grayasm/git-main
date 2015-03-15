/*
 * Numbers.c
 * Start five threads and give visible feedback
 * of these threads running by printing a number
 * passed in from the primary thread.
 * Build with the command line: cl NUMBERS.c
 * Note: This program was purposely build without
 * the multithreaded run-time library for 
 * demonstration purposes.
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

DWORD WINAPI ThreadFunc(LPVOID);

int main()
{
	HANDLE hThrd;
	DWORD threadId;
	int i;

	for(i=0; i<5; ++i)
	{
		hThrd = CreateThread(NULL, 0,
			ThreadFunc,
			(LPVOID)i,
			0,
			&threadId);

		if(hThrd){
			printf("Thread launched\n");
			/* Addition to NUMBERS project */
			CloseHandle(hThrd);
		}
	}

	// Wait for the threads to complete.
	// We'll see a better way of doing this in Chapter 3.
	Sleep(2000);
	return EXIT_SUCCESS;
};


DWORD WINAPI ThreadFunc(LPVOID n)
{
	int i;
	for(i=0; i<10; ++i)
		printf("%d%d%d%d%d%d%d%d\n",
			n,n,n,n,n,n,n,n);
	return 0;
}