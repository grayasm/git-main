/* IoByEvnt.c - Overlapped I/O using Signaled Event Objects
 *
 * An obvious limitation to using file handles as the signaling mechanism is that
 * you cannot tell which operation has completed. This is not a problem when you
 * only have a single operation pending per file handle, but as I mentioned earlier
 * it is possible to simultaneously queue up several operations, all of which use
 * the same file handle. It is clear that calling GetOverlappedResult() on each
 * possible overlapped operation in progress is not a very efficient solution.
 * Win32 provides a better way to do it.
 *
 * The final member of OVERLAPPED structure is a handle to an event object. If you
 * are using a signaled file handle, this member is set to NULL. When this member
 * is set to an event object, the kernel will automatically signal the event object
 * when the overlapped I/O operation is completed. Because every overlapped I/O
 * operation has its own unique OVERLAPPED structure, each structure can have a unique
 * event object to represent the operation.
 *
 * It is very important that the event object you use be created as manual-reset and not
 * as auto-reset. If you use an auto-reset event, then a race condition arise because
 * the kernel could signal the object before you have a chance to wait on it. So
 * the event would be lost and your wait would never return.
 *
 * By using event objects and overlapped I/O, you can issue multiple read and writes
 * against the same file handle, each with its own event object, then do a 
 * WaitForMultipleObjects() to wait for one or all of them to finish.
 */


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "MtVerify.h"


#define MAX_REQUESTS	5
#define READ_SIZE		512
#define MAX_TRY_COUNT	5

int QueueRequest(int nIndex, DWORD dwLocation, DWORD dwAmount);
void CheckOsVersion();

// Event to wait for.
HANDLE ghEvents[MAX_REQUESTS];
// Individual I/O Operation
OVERLAPPED gOverlapped[MAX_REQUESTS];
HANDLE ghFile;
// I/O Buffers
char gBuffers[MAX_REQUESTS][READ_SIZE];




int main()
{
	int i;
	BOOL rc;
	char szPath[MAX_PATH];

	CheckOsVersion();

	GetWindowsDirectory(szPath, sizeof(szPath));
	strcat(szPath, "\\WINHLP32.EXE");

	// Open the file for overlapped reads
	ghFile = CreateFile(szPath,
				GENERIC_READ,
				FILE_SHARE_READ | FILE_SHARE_WRITE,
				NULL,
				OPEN_EXISTING,
				FILE_FLAG_OVERLAPPED,
				NULL);

	if(ghFile == INVALID_HANDLE_VALUE)
	{
		printf("Could not open %s\n", szPath);
		return -1;
	}

	for(i=0; i < MAX_REQUESTS; ++i)
	{
		// Read some bytes every few K
		QueueRequest(i, i*512, READ_SIZE);
	}

	printf("QUEUED!!\n");

	// Wait for all the operations to complete.
	MTVERIFY( WaitForMultipleObjects(
					MAX_REQUESTS,
					ghEvents,
					TRUE,
					INFINITE) != WAIT_FAILED );

	// Describe what just happened
	for(i=0; i < MAX_REQUESTS; ++i)
	{
		DWORD dwNumread;

		rc = GetOverlappedResult(
					ghFile,
					&gOverlapped[i],
					&dwNumread,
					FALSE);

		printf("Read #%d returned %d. %d bytes were read.\n",
			i, rc, dwNumread);
		MTVERIFY( CloseHandle(gOverlapped[i].hEvent) );
	}

	MTVERIFY( CloseHandle(ghFile) );

	return EXIT_SUCCESS;
} // main



/* 
 * Call ReadFile to start an overlapped request.
 * Make sure we handle errors that are recoverable.
 * Properly set up the event object for this operation.
 */

int QueueRequest(int nIndex, DWORD dwLocation, DWORD dwAmount)
{
	int i;
	BOOL rc;
	DWORD dwNumread;
	DWORD err;

	MTVERIFY(
		ghEvents[nIndex] = CreateEvent(
							NULL,		// No security
							TRUE,		// Manual reset - extremely important!
							FALSE,		// Initially set Event to non-signaled state
							NULL)		// No name
			); // MTVERIFY

	gOverlapped[nIndex].hEvent = ghEvents[nIndex];
	gOverlapped[nIndex].Offset = dwLocation;

	for(i=0; i < MAX_TRY_COUNT; ++i)
	{
		rc = ReadFile(
				ghFile,
				gBuffers[nIndex],
				dwAmount,
				&dwNumread,
				&gOverlapped[nIndex]);

		// Handle success
		if (rc)
		{
			printf("Read #%d completed immediately.\n", nIndex);
			return TRUE;
		}

		err = GetLastError();


		// Handle the error that isn't an error. rc is zero here.
		if(err == ERROR_IO_PENDING)
		{
			// asynchronous I/O is still in progress
			printf("Read #%d queued for overlapped I/O.\n", nIndex);
			return TRUE;
		}

		// Handle recoverable error
		if( err == ERROR_INVALID_USER_BUFFER ||
			err == ERROR_NOT_ENOUGH_QUOTA ||
			err == ERROR_NOT_ENOUGH_MEMORY )
		{
			Sleep(50); // Wait around and try later
			continue;
		}

		// Give up on fatal error
		break;
	}

	printf("ReadFile failed.\n");
	return -1;
}


/* Make sure we are running under an operating system that
 * supports overlapped I/O to files.
 */

void CheckOsVersion()
{
	OSVERSIONINFO	ver;
	BOOL			bResult;

	ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

	bResult = GetVersionEx((LPOSVERSIONINFO) &ver);

	if(!bResult || ver.dwPlatformId != VER_PLATFORM_WIN32_NT)
	{
		fprintf(stderr, "IoByEvnt must be run under Windows NT.\n");
		exit(EXIT_FAILURE);
	}
}