/*
 * CppSkel.cpp
 *
 * Show how to cast the parameters to _beginthreadex() so that they will work
 * in Visual C++ with the new stricter type checking.
 */
#include <stdio.h>
#include <windows.h>
#include <process.h>

typedef unsigned (WINAPI *PTHREADFUNC)(void* n);
typedef unsigned *PTHREADID;

DWORD WINAPI ThreadFunc(LPVOID);

int main()
{
	DWORD threadId;
	HANDLE hThread = (HANDLE) _beginthreadex(
								NULL,
								0,
								(PTHREADFUNC)ThreadFunc,
								(LPVOID)0,
								0,
								(PTHREADID)&threadId);

	if(hThread)
	{
		printf("\n\tLaunched c++ thread");

		WaitForSingleObject(hThread, INFINITE);
		CloseHandle( hThread );
	}

	printf("\n\tAbout to exit\n\n");

	return EXIT_SUCCESS;
} // main

DWORD WINAPI ThreadFunc(LPVOID n)
{
	printf("\n\tRunning thread %d", n);
	Sleep(1000);
	printf("\n\tThread %d idle", n);
	return (DWORD) n;
}
