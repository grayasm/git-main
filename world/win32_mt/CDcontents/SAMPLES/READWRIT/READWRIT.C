/*
 * ReadWrit.c
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 7, various listings.
 *
 * Demonstrates an implementation of the
 * Readers/Writers algorithm. This version
 * gives preference to readers.
 */

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "ReadWrit.h"

// If we wait more than 2 seconds, then something is probably wrong!
#define MAXIMUM_TIMEOUT 2000

// Here's the pseudocode for what is going on:
//
// Lock for Reader:
//  Lock the mutex
//  Bump the count of readers
//  If this is the first reader, lock the data
//  Release the mutex
//
// Unlock for Reader:
//  Lock the mutex
//  Decrement the count of readers
//  If this is the last reader, unlock the data
//  Release the mutex
//
// Lock for Writer:
//  Lock the data
//
// Unlock for Reader:
//  Unlock the data

///////////////////////////////////////////////////////

BOOL MyWaitForSingleObject(HANDLE hObject)
{
    DWORD result;

    result = WaitForSingleObject(hObject, MAXIMUM_TIMEOUT);
    // Comment this out if you want this to be non-fatal
    if (result != WAIT_OBJECT_0)
        FatalError("MyWaitForSingleObject - Wait failed, you probably forgot to call release!");
    return (result == WAIT_OBJECT_0);
}

BOOL InitRWLock(RWLock *pLock)
{
    pLock->nReaderCount = 0;
    pLock->hDataLock = CreateSemaphore(NULL, 1, 1, NULL);
    if (pLock->hDataLock == NULL)
        return FALSE;
    pLock->hMutex = CreateMutex(NULL, FALSE, NULL);
    if (pLock->hMutex == NULL)
    {
        CloseHandle(pLock->hDataLock);
        return FALSE;
    }
    return TRUE;
}

BOOL DestroyRWLock(RWLock *pLock)
{
    DWORD result = WaitForSingleObject(pLock->hDataLock, 0);
    if (result == WAIT_TIMEOUT)
        return FatalError("DestroyRWLock - Can't destroy object, it's locked!");

    CloseHandle(pLock->hMutex);
    CloseHandle(pLock->hDataLock);
    return TRUE;
}

BOOL AcquireReadLock(RWLock *pLock)
{
    BOOL result = TRUE;

    if (!MyWaitForSingleObject(pLock->hMutex))
        return FALSE;
 
    if(++pLock->nReaderCount == 1)
        result = MyWaitForSingleObject(pLock->hDataLock);

    ReleaseMutex(pLock->hMutex);
    return result;
}

BOOL ReleaseReadLock(RWLock *pLock)
{
    int result;
    LONG lPrevCount;

    if (!MyWaitForSingleObject(pLock->hMutex))
        return FALSE;

    if (--pLock->nReaderCount == 0)
        result = ReleaseSemaphore(pLock->hDataLock, 1, &lPrevCount);

    ReleaseMutex(pLock->hMutex);
    return result;
}

BOOL AcquireWriteLock(RWLock *pLock)
{
    return MyWaitForSingleObject(pLock->hDataLock);
}

BOOL ReleaseWriteLock(RWLock *pLock)
{
    int result;
    LONG lPrevCount;

    result = ReleaseSemaphore(pLock->hDataLock, 1, &lPrevCount);
    if (lPrevCount != 0)
        FatalError("ReleaseWriteLock - Semaphore was not locked!");
    return result;
}

BOOL ReadOK(RWLock *pLock)
{
    // This check is not perfect, because we
    // do not know for sure if we are one of
    // the readers.
    return (pLock->nReaderCount > 0);
}

BOOL WriteOK(RWLock *pLock)
{
    DWORD result;

    // The first reader may be waiting in the mutex,
    // but any more than that is an error.
    if (pLock->nReaderCount > 1)
        return FALSE;

    // This check is not perfect, because we
    // do not know for sure if this thread was
    // the one that had the semaphore locked.
    result = WaitForSingleObject(pLock->hDataLock, 0);
    if (result == WAIT_TIMEOUT)
        return TRUE;

    // a count is kept, which was incremented in Wait.
    result = ReleaseSemaphore(pLock->hDataLock, 1, NULL);
    if (result == FALSE)
        FatalError("WriteOK - ReleaseSemaphore failed");
    return FALSE;
}

///////////////////////////////////////////////////////

/*
 * Error handler
 */
BOOL FatalError(char *s)
{
    fprintf(stdout, "%s\n", s);
    // Comment out exit() to prevent termination
    exit(EXIT_FAILURE);
    return FALSE;
}
