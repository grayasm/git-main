/*
 * SrchWin.c
 *
 * Uses multiple threads to search the files '*.c' in the current directory for
 * the string given on the command line.
 *
 * This example avoids most C run-time functions so that it can use the single
 * threaded C libraries.
 *
 * It is necessary to use a critical section to divvy up output to the screen
 * or the various threads end up with their output intermingled.
 * Normally the multithreaded C run-timme does this automatically if you use
 * printf.
 *
 */

#include <windows.h>
#include <process.h> /* _beginthreadex(), _endthreadex() */
#include <stdlib.h>
#include "MtVerify.h"

DWORD WINAPI SearchProc(void* arg);
BOOL GetLine( HANDLE hFile, LPSTR buf, DWORD size );

#define MAX_THREADS		3

HANDLE hThreadLimitSemaphore;		/* Counting semaphore */
HANDLE hConsoleOut;					/* Console output */
CRITICAL_SECTION ScreenCritical;	/* Lock screen updates */

char szSearchFor[1024];

int main(int argc, char** argv)
{
	WIN32_FIND_DATA *lpFindData;
	HANDLE hFindFile;
	HANDLE hThread;
	DWORD dummy;
	int i;
	
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if(argc != 2)
	{
		char errbuf[512];
		wsprintf(errbuf,
			"Usage: %s <search-string>\n",
			argv[0]);
		
		WriteFile(hConsoleOut,
			errbuf,
			strlen(errbuf),
			&dummy,
			FALSE);
		return EXIT_FAILURE;			
	}
	
	/* Put search string where everyone can see it */
	strcpy(szSearchFor, argv[1]);
	
	/* Allocate a find buffer to be handed to the first thread */
	lpFindData = HeapAlloc( GetProcessHeap(),
						HEAP_ZERO_MEMORY,
						sizeof(WIN32_FIND_DATA) );
	
	/* Semaphore prevents too many threads from running */
	MTVERIFY( hThreadLimitSemaphore = CreateSemaphore(NULL, MAX_THREADS, MAX_THREADS, NULL) );
	
	InitializeCriticalSection(&ScreenCritical);
	
	hFindFile = FindFirstFile("*.c", lpFindData);
	
	if(hFindFile == INVALID_HANDLE_VALUE)
		return EXIT_FAILURE;
		
	do
	{
		WaitForSingleObject(hThreadLimitSemaphore, INFINITE);
		
		MTVERIFY( hThread = CreateThread(NULL,
								0,
								SearchProc,
								lpFindData,
								0,
								&dummy) );
		
		MTVERIFY( CloseHandle(hThread) );
		
		lpFindData = HeapAlloc( GetProcessHeap(),
						HEAP_ZERO_MEMORY,
						sizeof(WIN32_FIND_DATA));
	}
	while( FindNextFile(hFindFile, lpFindData) );
	
	FindClose( hFindFile );
	hFindFile = INVALID_HANDLE_VALUE;
	
	for(i=0; i < MAX_THREADS; ++i)
		WaitForSingleObject( hThreadLimitSemaphore, INFINITE );
		
	MTVERIFY( CloseHandle( hThreadLimitSemaphore ) );
	
	return EXIT_SUCCESS;
} // main

DWORD WINAPI SearchProc(void* arg)
{
	WIN32_FIND_DATA *lpFindData = (WIN32_FIND_DATA*) arg;
	char buf[1024];
	HANDLE hFile;
	DWORD dummy;
	
	hFile = CreateFile(lpFindData->cFileName,
						GENERIC_READ,
						FILE_SHARE_READ,
						NULL,
						OPEN_EXISTING,
						FILE_FLAG_SEQUENTIAL_SCAN,
						NULL);
	
	if( !hFile )
		return 1; /* Silently ignore problem files */
	
	while( GetLine(hFile, buf, sizeof(buf)) )
	{
		/* Inefficient search strategy, but it's easy */
		if( strstr(buf, szSearchFor) )
		{
			/* Make sure that this thread is the only one writing to this handle */
			EnterCriticalSection( &ScreenCritical );
			
			WriteFile( hConsoleOut,
					lpFindData->cFileName,
					strlen(lpFindData->cFileName),
					&dummy,
					FALSE);
			
			WriteFile(hConsoleOut, ": ", 2, &dummy, FALSE);
			
			WriteFile(hConsoleOut, buf, strlen(buf), &dummy, FALSE);
			
			WriteFile(hConsoleOut, "\r\n", 2, &dummy, FALSE);
			
			LeaveCriticalSection( &ScreenCritical );
		}
	} // while
	
	CloseHandle( hFile );
	HeapFree( GetProcessHeap(), 0, lpFindData );
	
	MTVERIFY( ReleaseSemaphore( hThreadLimitSemaphore, 1, NULL ) );

	return EXIT_SUCCESS;
} // SearchProc


/*	Unlike fgets(), this routine throws away CR/LF automatically.
	Calling ReadFile() one character at a time is slow, but this
	illustrates the advantage of using stdio under some conditions
	(because buffering the stream yourself is difficult)
*/
BOOL GetLine(HANDLE hFile, LPSTR buf, DWORD size)
{
	DWORD total = 0;
	DWORD numread;
	int state = 0; /* 0 = Looking for non-newline
					  1 = Stop after first newline */
	
	for(;;)
	{
		if(total == size -1)
		{
			buf[size-1] = '\0';
			return TRUE;
		}
		
		if( !ReadFile(hFile, buf+total, 1, &numread, 0) || numread == 0)
		{
			buf[total] = '\0';
			return total != 0;
		}
		
		if( buf[total] == '\r' || buf[total] == '\n')
		{
			if(state == 0)
				continue;
			buf[total] = '\0';
			return TRUE;
		}
		
		state = 1;
		total++;
	}	
} // GetLine























