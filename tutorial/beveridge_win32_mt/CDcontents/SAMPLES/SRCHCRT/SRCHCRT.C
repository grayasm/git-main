/*
 * SrchCrt.c
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 8, Listing 8-1
 *
 * Uses multiple threads to search the files 
 * "*.c" in the current directory for the string
 * given on the command line.
 *
 * This example uses the multithreaded version of
 * the C run-time library so as to be able to use
 * the FILE functions as well as calloc and free.
 *
 * Build this file with the command line: cl /MD SrchCrt.c
 *
 */

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>    /* _beginthreadex, _endthreadex */
#include <stddef.h>
#include "MtVerify.h"

DWORD WINAPI SearchProc( void *arg );

#define MAX_THREADS 3

HANDLE hThreadLimitSemaphore;
char szSearchFor[1024];

int main(int argc, char *argv[])
{
    WIN32_FIND_DATA *lpFindData;
    HANDLE hFindFile;
    HANDLE hThread;
    DWORD dummy;
    int i;

    if (argc != 2)
    {
        printf("Usage: %s <search-string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Put search string where everyone can see it */
    strcpy(szSearchFor, argv[1]);

    /* Each thread will be given its own results buffer */
    lpFindData = calloc( 1, sizeof(WIN32_FIND_DATA) );

    /* Semaphore prevents too many threads from running */
    MTVERIFY( hThreadLimitSemaphore = CreateSemaphore(
            NULL,   /* Security */
            MAX_THREADS,    /* Make all of them available */
            MAX_THREADS,    /* No more than MAX_THREADS */
            NULL )          /* Unnamed */
         );

    hFindFile = FindFirstFile( "*.c", lpFindData );

    if (hFindFile == INVALID_HANDLE_VALUE)
        return EXIT_FAILURE;

    do {
        WaitForSingleObject( hThreadLimitSemaphore,
            INFINITE );

        MTVERIFY( 
            hThread = (HANDLE)_beginthreadex(NULL,
                        0,
                        SearchProc,
                        lpFindData,
                        0,
                        &dummy
            )
        );
        MTVERIFY( CloseHandle( hThread ) );

        lpFindData = calloc( 1, sizeof(WIN32_FIND_DATA) );

    } while ( FindNextFile( hFindFile, lpFindData ));

    FindClose( hFindFile );

    for (i=0; i<MAX_THREADS; i++)
        WaitForSingleObject(
                    hThreadLimitSemaphore,
                    INFINITE );
    MTVERIFY( CloseHandle( hThreadLimitSemaphore ) );

    return EXIT_SUCCESS;
}


DWORD __stdcall SearchProc( void *arg )
{
    WIN32_FIND_DATA *lpFindData = (WIN32_FIND_DATA *)arg;
    char buf[1024];
    FILE* fp;

    fp = fopen(lpFindData->cFileName, "r");
    if (!fp)
        return EXIT_FAILURE;

    while (fgets(buf, sizeof(buf), fp))
    {
        /* Inefficient search strategy, but it's easy */
        if (strstr(buf, szSearchFor))
            printf("%s: %s", lpFindData->cFileName, buf);
    }

    fclose(fp);
    free(lpFindData);

    MTVERIFY( ReleaseSemaphore( hThreadLimitSemaphore,
                1,          // Add one to the count
                NULL ) );   // Do not need the old value
}
