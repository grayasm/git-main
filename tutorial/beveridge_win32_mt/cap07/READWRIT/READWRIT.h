#ifndef __READWRIT_h__
#define __READWRIT_h__

/*
 * ReadWrit.h
 *
 * Sample code for Multithreading Applications in Win32
 * This is from Chapter 7, Listing 7-1
 *
 * Demonstrates an implementation of the Readers/Writers algorithm.
 * This version gives preference to readers.
 */

typedef struct _RWLock
{
	// Handle to a mutex that allows a single reader at a time access
	// to the reader counter.
	HANDLE hMutex;

	// Handle to a semaphore that keeps the data locked for either the
	// readers or the writers
	HANDLE hDataLock;

	// The count of the number of readers. Can legally be zero or one
	// while a writer has the data locked.
	int nReaderCount;
} RWLock ;

// Reader / Writer prototypes
//
BOOL InitRWLock(RWLock *pLock);
BOOL DestroyRWLock(RWLock *pLock);
BOOL AcquireReadLock(RWLock *pLock);
int ReleaseReadLock(RWLock *pLock);
BOOL AcquireWriteLock(RWLock *pLock);
int ReleaseWriteLock(RWLock *pLock);
BOOL ReadOK(RWLock *pLock);
BOOL WriteOK(RWLock *pLock);
BOOL FatalError(char *s);



#endif // __READWRIT_h__