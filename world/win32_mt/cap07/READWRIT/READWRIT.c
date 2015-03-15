/*
 * ReadWrit.c
 *
 * Sample code for "Mutithreading Applications in Win32"
 * This is from Chapter 7, various listings.
 *
 * Demonstrates an implementation of the Readers/Writers algorithm.
 * This version gives preference to readers.
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "READWRIT.h"
#include "MtVerify.h"



// If we wait more than 2 seconds, then something is probably wrong!
#define MAXIMUM_TIMEOUT		2000

/*
	Here's the pseudo code for what is going on:

	Lock for Reader:
		Lock the Mutex
		Bump the count of readers
		If this is the first reader, lock the Semaphore(left=0)
		Release the Mutex

	Unlock for Reader:
		Lock the Mutex
		Decrement the count of readers
		If this is the last reader, unlock the Semaphore(left=1)
		Release the Mutex

	Lock for Writer:
		Lock the Semaphore(left=0)

	Unlock for Writer
		Unlock the Semaphore(left=1)
 */

BOOL MyWaitForSingleObject(HANDLE hObject)
{
	DWORD result;

	result = WaitForSingleObject(hObject, MAXIMUM_TIMEOUT);
	
	if(result != WAIT_OBJECT_0)
		FatalError("MyWaitForSingleObject - Wait failed, you probably forgot to call release!");

	return (result == WAIT_OBJECT_0);
}


BOOL InitRWLock(RWLock *pLock)
{
	pLock->nReaderCount = 0;
	MTVERIFY( pLock->hDataLock = CreateSemaphore(
									NULL,		// default security
									1,			// initial count
									1,			// max count
									NULL)		// no name
									);
	
	if(pLock->hDataLock == NULL)
		return FALSE;

	MTVERIFY( pLock->hMutex = CreateMutex(
									NULL,		// default security
									FALSE,		// not owned (unlocked)
									NULL) );	// no name

	if(pLock->hMutex == NULL)
	{
		CloseHandle(pLock->hDataLock);
		return FALSE;
	}
	
	return TRUE;	
}


BOOL DestroyRWLock(RWLock *pLock)
{
	DWORD result = WaitForSingleObject(pLock->hDataLock, 0);
	if(result == WAIT_TIMEOUT)
		return FatalError("DestroyRWLock - Can't destroy object, it's locked!");

	CloseHandle(pLock->hMutex);
	CloseHandle(pLock->hDataLock);

	return TRUE;
}

BOOL AcquireReadLock(RWLock *pLock)
{
	BOOL result = TRUE;

	if(!MyWaitForSingleObject(pLock->hMutex))
		return FALSE;

	if(++pLock->nReaderCount == 1)
		result = MyWaitForSingleObject(pLock->hDataLock);

	ReleaseMutex(pLock->hMutex);

	return result;
}

BOOL ReleaseReadLock(RWLock *pLock)
{
	int result = 1;
	LONG lPrevCount;

	if(!MyWaitForSingleObject(pLock->hMutex))
		return FALSE;

	if(--pLock->nReaderCount == 0)
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
	if(lPrevCount != 0)
		FatalError("ReleaseWriteLock - Semaphore was not locked!");

	return result;
}

BOOL ReadOK(RWLock *pLock)
{
	// This check is not perfect, because we don't know for sure if we are
	// one of the readers
	//
	return (pLock->nReaderCount > 0);
}

BOOL WriteOK(RWLock *pLock)
{
	DWORD result;

	// The first reader may be waiting in the mutex,
	// but any more than that is an error.
	if(pLock->nReaderCount > 1)
		return FALSE;

	// This check is not perfect, because we do not know for sure if this
	// thread was the one that had the semaphore locked.
	result = WaitForSingleObject(pLock->hDataLock, 0);
	if(result == WAIT_TIMEOUT)
		return TRUE;

	// a count is kept, which was incremented in Wait.
	result = ReleaseSemaphore(pLock->hDataLock, 1, NULL);
	if(result == FALSE)
		FatalError("WriteOK - ReleaseSemaphore failed");

	return FALSE;
}

// Error handler
//
BOOL FatalError(char *s)
{
	fprintf(stdout, "%s\n", s);
	// comment out exit() to prevent termination
	exit(EXIT_FAILURE);
	return FALSE;
}