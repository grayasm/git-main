
/*
 * MTVERIFY macro in action.
 * The call to CloseHandle has been switched around with
 * the call to GetExitCodeThread() in order to cause 
 * GetExitCodeThread() to fail.
 *
 * Demonstration of Error handler (MTVERIFY macro)
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "MtVerify.h"


DWORD WINAPI ThreadFunc(LPVOID);


int main()
{
	HANDLE hThrd;
	DWORD exitCode = 0;
	DWORD threadId;

	MTVERIFY( hThrd = CreateThread(NULL,
		0,
		ThreadFunc,
		(LPVOID)1,
		0,
		&threadId) );

	if(hThrd)
		printf("Thread launched\n");

	MTVERIFY( CloseHandle(hThrd) );

	for(;;)
	{
		BOOL rc;
		MTVERIFY( rc = GetExitCodeThread(hThrd, &exitCode) );
		if(!rc && exitCode != STILL_ACTIVE)
			break;
	}

	printf("Thread returned %d\n", exitCode);

	return EXIT_SUCCESS;
}

DWORD WINAPI ThreadFunc(LPVOID n)
{
	printf("Thread running\n");
	return 0;
}