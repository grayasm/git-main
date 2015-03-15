/*
 * IoByFile.c
 * 
 * Sample code for Multi-threading Applications in Win32
 * This is from Chapter 06, Listing 6-1
 *
 * Demonstrates how a file handle becomes signaled when an
 * overlapped operation on the handle's file is completed.
 * Notice that sometimes the operation is completed immediately.
 * The operation is only queued, or pended, if ERROR_IO_PENDING 
 * is returned.
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "MtVerify.h"


#define READ_SIZE 512

void CheckOsVersion();

int main()
{
	char szPath[MAX_PATH];
	char buf[READ_SIZE];
	OVERLAPPED overlap;
	DWORD numread;
	HANDLE hFile;
	BOOL rc;


	CheckOsVersion();

	GetWindowsDirectory(szPath, sizeof(szPath));
	strcat(szPath, "\\WINHLP32.EXE");

	// Open the file for overlapped reads
	hFile = CreateFile(
				szPath, 
				GENERIC_READ, 
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				OPEN_EXISTING,
				FILE_FLAG_OVERLAPPED, 
				NULL);

	MTVERIFY( hFile != INVALID_HANDLE_VALUE );
	if(hFile == INVALID_HANDLE_VALUE)
	{
		printf("Could not open %s\n", szPath);
		return -1;
	}


	// Initialize the OVERLAPPED structure
	memset(&overlap, 0, sizeof(overlap));
	overlap.Offset = 1500;

	// Request the data
	rc = ReadFile(
			hFile,
			buf,
			READ_SIZE,
			&numread,
			&overlap
			);
	printf("Issue read request\n");

	// Was the operation queued ?
	if( rc )
	{
		// The data was read successfully 
		printf("Request was returned immediately\n");
	}
	else
	{
		/* If you ask for an operation to be overlapped, and the operating system
		 * queues the request for execution, then ReadFile() and WriteFile() return
		 * FALSE to indicate failure. This behavior is not intuitive. You need to call
		 * GetLastError() and make sure that it returns ERROR_IO_PENDING, which simply
		 * means that the overlapped I/O is queued and waiting to happen. It is 
		 * possible for GetLastError() to return other values, such as ERROR_HANDLE_EOF,
		 * which really is an error and must be treated as such.
		 */
		if( GetLastError() == ERROR_IO_PENDING )
		{
			// We could do something else for awhile here ...
			
			printf("Request queued, waiting ...\n");
			/* The example is oversimplified because a real-world application would 
			 * probably wait for multiple handles at the same tiem in a central part
			 * of the program.
			 */
			WaitForSingleObject(hFile, INFINITE);
			printf("Request completed.\n");

			MTVERIFY( rc = GetOverlappedResult(
								hFile,
								&overlap,
								&numread,
								FALSE)
								);
			printf("Result was %d\n", rc);
		}
		else
		{
			// We should check for memory and quota
			// errors here and retry.
			// See the samples IoByEvnt and IoByAPC.

			// Something went wrong.
			printf("Error reading file\n");
		}
	}


	MTVERIFY( CloseHandle(hFile) );

	return EXIT_SUCCESS;
}  // main



// Make sure that we are running under an operating
// system that supports overlapped I/O to files.
//
void CheckOsVersion()
{
	OSVERSIONINFO	ver;
	BOOL			bResult;

	ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	bResult = GetVersionEx((LPOSVERSIONINFO) &ver);

	if(!bResult || 
		ver.dwPlatformId != VER_PLATFORM_WIN32_NT)
	{
		fprintf(stderr, "IoByFile must be run under Windows NT.\n");
		exit(EXIT_FAILURE);
	}
} // check

