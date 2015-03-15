/*
 * Exclusive locks look great on paper, but they cause awful 
 * performance regressions forcing all access to be sequential.
 * In this case the benefit of multithreading would be lost.
 *
 * There is nothing wrong with every thread in the application
 * reading a data structure at the same time, as long as no other
 * thread tries to change it.
 * On the other hand, if a thread is writing a data structure, other
 * threads should be prevented from both reading and writing it.
 * It is possible to do the same thing in multithreading applications.
 * The trick is to make it properly.
 *
 * The following design "Concurrent Control with Readers and Writers",
 * Communications of the ACM, vol 10,pp. 667-668, Oct. 1971
 * gives preference to the readers.

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



#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "MtVerify.h"


#define MAX_TEXT		6
#define MAX_TIMEOUT		2000

typedef struct _Shared
{
	// threads share this text resource
	char		str[MAX_TEXT];

	// locking mechanism
	HANDLE		hMutex;
	HANDLE		hSemaphore;
	int			iReaders;
} Shared ;


Shared* NewShared()
{
	Shared* pSh;
	
	pSh = malloc( sizeof(Shared) );
	memset(pSh, 0, sizeof(Shared));
	// initialize locking
	MTVERIFY( pSh->hMutex = CreateMutex(NULL, FALSE, NULL) );
	MTVERIFY( pSh->hSemaphore = CreateSemaphore(NULL, 1, 1, NULL) );
	pSh->iReaders = 0;
	return pSh;
} // New

void DeleteShared(Shared* pSh)
{
	DWORD rc;
	MTVERIFY( (rc = WaitForSingleObject(pSh->hSemaphore, 0)) == WAIT_OBJECT_0 );

	MTVERIFY( CloseHandle(pSh->hMutex) );
	MTVERIFY( CloseHandle(pSh->hSemaphore) );
	
	free(pSh);
} // Delete

void ReadLock(Shared* pSh)
{
	DWORD rc;
	
	MTVERIFY( (rc = WaitForSingleObject(pSh->hMutex, MAX_TIMEOUT)) == WAIT_OBJECT_0 );
	pSh->iReaders++;
	if(pSh->iReaders == 1)
	{
		MTVERIFY( (rc = WaitForSingleObject(pSh->hSemaphore, MAX_TIMEOUT)) == WAIT_OBJECT_0 );
	}

	MTVERIFY( ReleaseMutex(pSh->hMutex) );
} // lock for read

void ReadUnlock(Shared* pSh)
{
	DWORD rc;

	MTVERIFY( (rc = WaitForSingleObject(pSh->hMutex, MAX_TIMEOUT)) == WAIT_OBJECT_0 );
	pSh->iReaders--;

	if(pSh->iReaders == 0)
	{
		MTVERIFY( ReleaseSemaphore(pSh->hSemaphore, 1, NULL) );
	}

	MTVERIFY( ReleaseMutex(pSh->hMutex) );
} // unlock last read

void WriteLock(Shared* pSh)
{
	MTVERIFY( WaitForSingleObject(pSh->hSemaphore, INFINITE) == WAIT_OBJECT_0 );
} // lock for write

void WriteUnlock(Shared* pSh)
{
	MTVERIFY( ReleaseSemaphore(pSh->hSemaphore, 1, NULL) );
} // unlock last write

//////////////////////////////////////////////////////////////////////////

#define MAX_THREADS		9
DWORD WINAPI ThreadFunc(LPVOID n);
Shared* gShared;


int main()
{
	int i;
	HANDLE hThrds[MAX_THREADS];
	DWORD threadId;
	DWORD rc;


	gShared = NewShared();
	strcpy(gShared->str, "abcdef");
	printf("\n\tMain thread: gShared: %s", gShared->str);

	for(i=0; i < MAX_THREADS; ++i)
	{
		MTVERIFY( hThrds[i] = CreateThread(
									NULL, 
									0,
									ThreadFunc,
									(LPVOID)i,
									0,
									&threadId) );

		printf("\n\tLaunched thread %d", i);
	}


	rc = WaitForMultipleObjects(
			MAX_THREADS,
			hThrds,
			TRUE,
			INFINITE);
	MTVERIFY(rc >= WAIT_OBJECT_0 && rc < WAIT_OBJECT_0 + MAX_THREADS);
	
	printf("\n\tAll threads finished\n\n");

	DeleteShared(gShared);

	return EXIT_SUCCESS;
} // main


DWORD WINAPI ThreadFunc(LPVOID n)
{
	srand( GetTickCount() );
	Sleep( (rand()%10)*300 + 500 );

	if(((int)n) % 2)
	{
		// Writer
		WriteLock(gShared);
		sprintf(gShared->str, "%d%d%d%d%d%c", n,n,n,n,n,'\0');
		printf("\n\tWriter Th: %d gShared: %s", n, gShared->str);
		WriteUnlock(gShared);
	}
	else
	{
		// Reader
		ReadLock(gShared);
		printf("\n\tReader Th: %d gShared: %s", n, gShared->str);
		ReadUnlock(gShared);
	}
	return (DWORD)n;
}