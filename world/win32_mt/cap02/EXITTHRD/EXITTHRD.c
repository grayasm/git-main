/*
 * It is sometimes necessary to exit a thread without returning
 * all the way up to the thread function. In this case we can
 * use the API function ExitThread().
 * 
 * EXITTHRD.c
 * Demonstrate ExitThread
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

DWORD WINAPI ThreadFunc(LPVOID);
void AnotherFunc(void);

int main()
{
	HANDLE hThrd;
	DWORD exitCode = 0;
	DWORD threadId;

	hThrd = CreateThread(NULL,
		0,
		ThreadFunc,
		(LPVOID)1,
		0,
		&threadId);

	if(hThrd)
		printf("Thread launched\n");

	for(;;)
	{
		BOOL rc;
		rc = GetExitCodeThread(hThrd, &exitCode);
		if(rc && exitCode != STILL_ACTIVE)
			break;
	}

	CloseHandle(hThrd);

	printf("Thread returned %d\n", exitCode);

	return EXIT_SUCCESS;
}; // main

/*
 * Call a function to do something that terminates
 * the thread with ExitThread instead of returning.
*/
DWORD WINAPI ThreadFunc(LPVOID n)
{
	printf("Thread running\n");
	AnotherFunc();
	return 0;
}

void AnotherFunc()
{
	printf("About to exit thread\n");
	ExitThread(4);

	// It is impossible to get here, this line
	// will never be printed
	printf("This will never print\n");
}