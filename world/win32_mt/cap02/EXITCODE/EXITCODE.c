/*
 * ExitCode.c
 * Start two threads and try to exit
 * when the user presses a key.
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

DWORD WINAPI ThreadFunc(LPVOID);

int main()
{
	HANDLE hThrd1;
	HANDLE hThrd2;
	DWORD exitCode1 = 0;
	DWORD exitCode2 = 0;
	DWORD threadId;

	hThrd1 = CreateThread(NULL,
		0,
		ThreadFunc,
		(LPVOID)1,
		0,
		&threadId);
	
	if(hThrd1)
		printf("\n\tThread 1 launched");

	hThrd2 = CreateThread(NULL,
		0,
		ThreadFunc,
		(LPVOID)2,
		0,
		&threadId);

	if(hThrd2)
		printf("\n\tThread 2 launched");

	// Keep waiting until both calls to GetExitCodeThread
	// succeed AND neither of them returns STILL_ACTIVE.
	// This method is not optimal - we'll see the correct
	// way in Chapter 3.

	for(;;)
	{
		printf("\n\tPress any key to exit ...");
		getch();

		GetExitCodeThread(hThrd1, &exitCode1);
		GetExitCodeThread(hThrd2, &exitCode2);

		if(exitCode1 == STILL_ACTIVE)
			puts("\n\tThread 1 is still running!");
		if(exitCode2 == STILL_ACTIVE)
			puts("\n\tThread 2 is still running!");
		if(exitCode1 != STILL_ACTIVE &&
			exitCode2 != STILL_ACTIVE)
			break;
	}

	CloseHandle(hThrd1);
	CloseHandle(hThrd2);

	printf("\n\tThread 1 returned %d", exitCode1);
	printf("\n\tThread 2 returned %d\n\n", exitCode2);

	return EXIT_SUCCESS;
}; // main


/*
 * Take the startup value, do some simple math on it,
 * and return the calculated value.
*/
DWORD WINAPI ThreadFunc(LPVOID n)
{
	Sleep((DWORD)n*1000*2);
	return (DWORD)n*10;
}