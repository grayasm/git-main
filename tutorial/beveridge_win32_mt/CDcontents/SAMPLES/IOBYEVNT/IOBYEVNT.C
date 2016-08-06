/*
 * IoByEvnt.c
 *
 * Sample code for Multithreading Applications in Win32
 * This is from Chapter 6, Listing 6-2
 *
 * Demonstrates how to use event objects instead of
 * file handles to signal multiple outstanding
 * overlapped operation on a file.
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
int QueueRequest(int nIndex, DWORD dwLocation, DWORD dwAmount);
void CheckOsVersion();


//
// Global variables
//

// Need to keep the events in their own array
// so we can wait on them.
HANDLE  ghEvents[MAX_REQUESTS];
// Keep track of each individual I/O operation
OVERLAPPED gOverlapped[MAX_REQUESTS];
// Handle to the file of interest.
HANDLE ghFile;
// Need a place to put all this data
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

    for (i=0; i<MAX_REQUESTS; i++)
    {
        // Read some bytes every few K
        QueueRequest(i, i*16384, READ_SIZE);
    }

    printf("QUEUED!!\n");

    // Wait for all the operations to complete.
    MTVERIFY( WaitForMultipleObjects(
               MAX_REQUESTS, ghEvents, TRUE, INFINITE
        ) != WAIT_FAILED );

    // Describe what just happened.
    for (i=0; i<MAX_REQUESTS; i++)
    {
        DWORD dwNumread;

        rc = GetOverlappedResult(
                                ghFile,
                                &gOverlapped[i],
                                &dwNumread,
                                FALSE
                            );
        printf("Read #%d returned %d. %d bytes were read.\n",
                    i, rc, dwNumread);
        CloseHandle(gOverlapped[i].hEvent);
    }

    CloseHandle(ghFile);

    return EXIT_SUCCESS;
}


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
                     NULL,    // No security
                     TRUE,    // Manual reset - extremely important!
                     FALSE,   // Initially set Event to non-signaled state
                     NULL     // No name
                    )
    );
    gOverlapped[nIndex].hEvent = ghEvents[nIndex];
    gOverlapped[nIndex].Offset = dwLocation;

    for (i=0; i<MAX_TRY_COUNT; i++)
    {
        rc = ReadFile(
            ghFile,
            gBuffers[nIndex],
            dwAmount,
            &dwNumread,
            &gOverlapped[nIndex]
        );

        // Handle success
        if (rc)
        {
            printf("Read #%d completed immediately.\n", nIndex);
            return TRUE;
        }

        err = GetLastError();

        // Handle the error that isn't an error. rc is zero here.
        if (err == ERROR_IO_PENDING)
        {
            // asynchronous i/o is still in progress 
            printf("Read #%d queued for overlapped I/O.\n", nIndex);
            return TRUE;
        }

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

    printf("ReadFile failed.\n");
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
        fprintf(stderr, "IoByEvnt must be run under Windows NT.\n");
		exit(EXIT_FAILURE);
    }

}
