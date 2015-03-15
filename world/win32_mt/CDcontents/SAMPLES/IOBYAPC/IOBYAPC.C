/*
 * IoByAPC.c
 *
 * Sample code for Multithreading Applications in Win32
 * This is from Chapter 6, Listing 6-3
 *
 * Demonstrates how to use APC's (asynchronous
 * procedure calls) instead of signaled objects
 * to service multiple outstanding overlapped
 * operations on a file.
 */

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "MtVerify.h"

//
// Constants
//
#define MAX_REQUESTS    5
#define READ_SIZE       512
#define MAX_TRY_COUNT   5

//
// Function prototypes
//
void CheckOsVersion();
int QueueRequest(int nIndex, DWORD dwLocation, DWORD dwAmount);


//
// Global variables
//

// Need a single event object so we know when all I/O is finished
HANDLE  ghEvent;
// Keep track of each individual I/O operation
OVERLAPPED gOverlapped[MAX_REQUESTS];
// Handle to the file of interest.
HANDLE ghFile;
// Need a place to put all this data
char gBuffers[MAX_REQUESTS][READ_SIZE];
int nCompletionCount;

/*
 * I/O Completion routine gets called
 * when app is alertable (in WaitForSingleObjectEx)
 * and an overlapped I/O operation has completed.
 */
VOID WINAPI FileIOCompletionRoutine(
    DWORD dwErrorCode,  // completion code 
    DWORD dwNumberOfBytesTransfered,    // number of bytes transferred 
    LPOVERLAPPED lpOverlapped   // pointer to structure with I/O information  
   )
{
    // The event handle is really the user defined data
    int nIndex = (int)(lpOverlapped->hEvent);
    printf("Read #%d returned %d. %d bytes were read.\n",
        nIndex,
        dwErrorCode,
        dwNumberOfBytesTransfered);

    if (++nCompletionCount == MAX_REQUESTS)
        SetEvent(ghEvent);  // Cause the wait to terminate
}


int main()
{
    int i;
    char szPath[MAX_PATH];

    CheckOsVersion();

    // Need to know when to stop
    MTVERIFY(
        ghEvent = CreateEvent(
                     NULL,    // No security
                     TRUE,    // Manual reset - extremely important!
                     FALSE,   // Initially set Event to non-signaled state
                     NULL     // No name
                    )
    );

    GetWindowsDirectory(szPath, sizeof(szPath));
    strcat(szPath, "\\WINHLP32.EXE");
    // Open the file for overlapped reads
    ghFile = CreateFile( szPath,
                    GENERIC_READ,
                    FILE_SHARE_READ|FILE_SHARE_WRITE,
                    NULL,
                    OPEN_EXISTING,
                    FILE_FLAG_OVERLAPPED,
                    NULL
                );
    if (ghFile == INVALID_HANDLE_VALUE)
    {
        printf("Could not open %s\n", szPath);
        return -1;
    }

    // Queue up a few requests
    for (i=0; i<MAX_REQUESTS; i++)
    {
        // Read some bytes every few K
        QueueRequest(i, i*16384, READ_SIZE);
    }

    printf("QUEUED!!\n");

    // Wait for all the operations to complete.
    for (;;)
    {
        DWORD rc;
        rc = WaitForSingleObjectEx(ghEvent, INFINITE, TRUE );
        if (rc == WAIT_OBJECT_0)
            break;
        MTVERIFY(rc == WAIT_IO_COMPLETION);
    }

    CloseHandle(ghFile);

    return EXIT_SUCCESS;
}


/*
 * Call ReadFileEx to start an overlapped request.
 * Make sure we handle errors that are recoverable.
 */
int QueueRequest(int nIndex, DWORD dwLocation, DWORD dwAmount)
{
    int i;
    BOOL rc;
    DWORD err;

    gOverlapped[nIndex].hEvent = (HANDLE)nIndex;
    gOverlapped[nIndex].Offset = dwLocation;

    for (i=0; i<MAX_TRY_COUNT; i++)
    {
        rc = ReadFileEx(
            ghFile,
            gBuffers[nIndex],
            dwAmount,
            &gOverlapped[nIndex],
            FileIOCompletionRoutine
        );

        // Handle success
        if (rc)
        {
            // asynchronous i/o is still in progress 
            printf("Read #%d queued for overlapped I/O.\n", nIndex);
            return TRUE;
        }

        err = GetLastError();

        // Handle recoverable error
        if ( err == ERROR_INVALID_USER_BUFFER ||
             err == ERROR_NOT_ENOUGH_QUOTA ||
             err == ERROR_NOT_ENOUGH_MEMORY )
        {
            Sleep(50);  // Wait around and try later
            continue;
        }

        // Give up on fatal error.
        break;
    }

    printf("ReadFileEx failed.\n");
    return -1;
}

//
// Make sure we are running under an operating
// system that supports overlapped I/O to files.
//
void CheckOsVersion()
{
    OSVERSIONINFO   ver;
    BOOL            bResult;

    ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    bResult = GetVersionEx((LPOSVERSIONINFO) &ver);

    if ( (!bResult) ||
         (ver.dwPlatformId != VER_PLATFORM_WIN32_NT) )
    {
        fprintf(stderr, "IoByAPC must be run under Windows NT.\n");
		exit(EXIT_FAILURE);
    }

}
