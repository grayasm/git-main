/*
 * IoByFile.c
 *
 * Sample code for Multithreading Applications in Win32
 * This is from Chapter 6, Listing 6-1
 *
 * Demonstrates how a file handle becomes signaled
 * when an overlapped operation on the handle's file
 * is completed.  Notice that sometimes the operation
 * is completed immediately. The operation is only
 * queued, or pended, if ERROR_IO_PENDING is returned.
 */

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

//
// Constants
//
#define READ_SIZE       512

//
// Function prototypes
//
void CheckOsVersion();


int main()
{
    BOOL rc;
    HANDLE hFile;
    DWORD numread;
    OVERLAPPED overlap;
    char buf[READ_SIZE];
    char szPath[MAX_PATH];

    CheckOsVersion();

    GetWindowsDirectory(szPath, sizeof(szPath));
    strcat(szPath, "\\WINHLP32.EXE");
    // Open the file for overlapped reads
    hFile = CreateFile( szPath,
                    GENERIC_READ,
                    FILE_SHARE_READ|FILE_SHARE_WRITE,
                    NULL,
                    OPEN_EXISTING,
                    FILE_FLAG_OVERLAPPED,
                    NULL
                );
    if (hFile == INVALID_HANDLE_VALUE)
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
    printf("Issued read request\n");

    // Was the operation queued?
    if (rc)
    {
        // The data was read successfully
        printf("Request was returned immediately\n");
    }
    else
    {
        if (GetLastError() == ERROR_IO_PENDING)
        {
            // We could do something else for awhile here...

            printf("Request queued, waiting...\n");
            WaitForSingleObject(hFile, INFINITE);
            printf("Request completed.\n");

            rc = GetOverlappedResult(
                                    hFile,
                                    &overlap,
                                    &numread,
                                    FALSE
                                );
            printf("Result was %d\n", rc);
        }
        else
        {
			// We should check for memory and quota
			// errors here and retry. See the samples
			// IoByEvnt and IoByAPC.

            // Something went wrong
            printf("Error reading file\n");
        }
    }

    CloseHandle(hFile);

    return EXIT_SUCCESS;
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
        fprintf(stderr, "IoByFile must be run under Windows NT.\n");
		exit(EXIT_FAILURE);
    }

}
