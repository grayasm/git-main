/*
 * List.c
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 7, Listing 7-1
 *
 * Demonstrates an implementation of the Readers/Writers algorithm.
 * This version gives preference to readers.
 */


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "READWRIT.h"




typedef struct _Node
{
	struct _Node *pNext;
	char	szBuffer[80];
} Node ;

typedef struct _List
{
	RWLock		lock;
	Node		*pHead;
} List ;


// Linked list prototypes
//
BOOL InitRWLock(RWLock *pLock);
BOOL DeleteList(List *pList);
BOOL AddHead(List *pList, Node *pNode);
BOOL DeleteHead(List *pList);
BOOL Insert(List *pList, Node *afterNode, Node *newNode);
Node *Next(List *pList, Node *pNode);


// Test functions prototypes
//

DWORD WINAPI LoadThreadFunc(LPVOID n);
DWORD WINAPI SearchThreadFunc(LPVOID n);
DWORD WINAPI DeleteThreadFunc(LPVOID n);


// Global variables
// List we use for testing
List *gpList;


List *CreateList()
{
	List *pList = GlobalAlloc(GPTR, sizeof(List));
	if(InitRWLock(&pList->lock) == FALSE)
	{
		GlobalFree(pList);
		pList = NULL;
	}
	return pList;
}


BOOL DeleteList(List *pList)
{
	AcquireWriteLock(&pList->lock);
	while(DeleteHead(pList))
		;
	ReleaseWriteLock(&pList->lock);

	DestroyRWLock(&gpList->lock);

	GlobalFree(pList);

	return TRUE;
}

BOOL AddHead(List *pList, Node *pNode)
{
	if(!WriteOK(&pList->lock))
		return FatalError("AddHead - not allowed to write!");

	pNode->pNext = pList->pHead;
	pList->pHead = pNode;

	return TRUE;
}

BOOL DeleteHead(List *pList)
{
	Node *pNode;

	if(!WriteOK(&pList->lock))
		return FatalError("AddHead - not allowed to write!");

	if(pList->pHead == NULL)
		return FALSE;

	pNode = pList->pHead->pNext;
	GlobalFree(pList->pHead);
	pList->pHead = pNode;
	return TRUE;
}

BOOL Insert(List *pList, Node *afterNode, Node *newNode)
{
	if(!WriteOK(&pList->lock))
		return FatalError("Insert - not allowed to write!");

	if(afterNode == NULL)
	{
		AddHead(pList, newNode);
	}
	else
	{
		newNode->pNext = afterNode->pNext;
		afterNode->pNext = newNode;
	}

	return TRUE;
}

Node *Next(List *pList, Node *pNode)
{
	if(!ReadOK(&pList->lock))
	{
		FatalError("Next - Now allowed to read!");
		return NULL;
	}

	if(pNode == NULL)
		return pList->pHead;
	else
		return pNode->pNext;
}

//////////////////////////////////////////////////////////////////////////

int main()
{
	HANDLE		hThrds[4];
	int			slot = 0;
	int			rc;
	int			nThreadCount = 0;
	DWORD		dwThreadId;


	gpList = CreateList();
	if(!gpList)
		FatalError("main - List creation failed!");

	hThrds[nThreadCount++] = CreateThread(NULL, 0, LoadThreadFunc, 0, 0, &dwThreadId);
	hThrds[nThreadCount++] = CreateThread(NULL, 0, SearchThreadFunc, (LPVOID)"pNode", 0, &dwThreadId);
	hThrds[nThreadCount++] = CreateThread(NULL, 0, SearchThreadFunc, (LPVOID)"pList", 0, &dwThreadId);
	hThrds[nThreadCount++] = CreateThread(NULL, 0, DeleteThreadFunc, 0, 0, &dwThreadId);

	// Now wait for all threads to terminate
	rc = WaitForMultipleObjects(
			nThreadCount,
			hThrds,
			TRUE,
			INFINITE);

	for(slot=0; slot < nThreadCount; ++slot)
	{
		CloseHandle(hThrds[slot]);
	}

	printf("\nProgram finished.\n");

	DeleteList(gpList);

	return EXIT_SUCCESS;
}


/*
 * Slowly load the contents of "List.c" into the linked list
 */

DWORD WINAPI LoadThreadFunc(LPVOID n)
{
	int nBatchCount;
	Node *pNode;

	FILE* fp = fopen("List.c", "r");
	if(!fp)
	{
		fprintf(stderr, "List.c not found\n");
		exit(EXIT_FAILURE);
	}

	pNode = GlobalAlloc(GPTR, sizeof(Node));
	nBatchCount = (rand() % 10) + 2;
	AcquireWriteLock(&gpList->lock);

	while(fgets(pNode->szBuffer, sizeof(Node), fp))
	{
		AddHead(gpList, pNode);

		// Try not to hog the lock
		if(--nBatchCount == 0)
		{
			ReleaseWriteLock(&gpList->lock);
			Sleep(rand() % 5);
			nBatchCount = (rand() %10 ) + 2;
			AcquireWriteLock(&gpList->lock);
		}

		pNode = GlobalAlloc(GPTR, sizeof(Node));
	}

	ReleaseWriteLock(&gpList->lock);
	return 0;
}


/*
 * Every so often, walked the linked lilst and figure out how many lines
 * one string appears (given as the startup param)
 */
DWORD WINAPI SearchThreadFunc(LPVOID n)
{
	int i;
	char *szSearch = (char *)n;

	for(i=0; i < 20; ++i)
	{
		int nFoundCount = 0;
		Node *next = NULL;

		AcquireReadLock(&gpList->lock);
		next = Next(gpList, next);

		while(next)
		{
			if(strstr(next->szBuffer, szSearch))
				nFoundCount++;
			next = Next(gpList, next);
		}

		ReleaseReadLock(&gpList->lock);

		printf("Found %d lines with '%s'\n", nFoundCount, szSearch);
		Sleep((rand() % 30));
	}

	return 0;
}


// Every so often, delete some entries in the list
//
DWORD WINAPI DeleteThreadFunc(LPVOID n)
{
	int i;

	for(i=0; i < 100; ++i)
	{
		Sleep(1);
		AcquireWriteLock(&gpList->lock);
		DeleteHead(gpList);
		DeleteHead(gpList);
		DeleteHead(gpList);
		ReleaseWriteLock(&gpList->lock);
	}

	return 0;
}