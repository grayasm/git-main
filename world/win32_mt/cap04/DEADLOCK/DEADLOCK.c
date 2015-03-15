/*
 * DEADLOCK.c sample
 *
 * The deadlock conditions are met when someone tries to acquire multiple
 * locks with more than ONE call. If a context switch happens between the
 * lock attempts the locking can be compromised.
 *
 * To avoid "the deadly embrace" all locks must be acquired at ONCE, usually
 * by mean of WaitForMultipleObjects
 *
 * See Swap function. 
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "MtVerify.h"


/* Some arbitrary named data structure */
typedef struct _Node
{
	HANDLE		hMutex;
	int			idata;
} Node;

Node* CreateNode()
{
	Node* nod = (Node*) malloc( sizeof(Node) );
	// create signaled (not locked / owned) Mutex
	MTVERIFY( nod->hMutex = CreateMutex(NULL, FALSE, NULL) );
	nod->idata = 0;
	return nod;
} // initialization

DeleteNode(Node* nod)
{
	// decrement kernel object reference to allow clean up
	MTVERIFY( CloseHandle(nod->hMutex) );
	free(nod);
} // clean up

void Swap(Node* nod1, Node* nod2, DWORD n)
{
	/* A deadlock scenario would be to attempt EnterCriticalSection 2 times
	 * once for each Node before swapping the internal value.
	 *
	 *		EnterCriticalSection(nod1->m_critical_section);
	 *		EnterCriticalSection(nod2->m_critical_section);
	 *
	 * The deadlock would happen when 2 threads call at the same time Swap:
	 *
	 * Thread 1:  Swap(nod1, nod2);
	 * Thread 2:  Swap(nod2, nod1);
	 *
	 * and a context switch happens after first EnterCriticalSection()
	 * Both threads would wait for the other to LeaveCriticalSection()
	 *
	 * Solution is to acquire the lock with ONE call only using 
	 * WaitForMultipleObjects and the Mutex.
	 */

	HANDLE handles[2];
	DWORD rc;
	int tmp;

	handles[0] = nod1->hMutex;
	handles[1] = nod2->hMutex;
	
	// equivalent of EnterCriticalSection, acquiring lock
	// on both mutexes at once
	rc = WaitForMultipleObjects(
		2,
		handles,
		TRUE,
		INFINITE);

	MTVERIFY( rc >= WAIT_OBJECT_0 && rc < 2 );

	printf("Thread %d swap: %d <-> %d\n", n, nod1->idata, nod2->idata);


	tmp = nod1->idata;
	nod1->idata = nod2->idata;
	nod2->idata = tmp;


	// release the lock, similar with LeaveCriticalSection()
	MTVERIFY( ReleaseMutex(handles[0]) );
	MTVERIFY( ReleaseMutex(handles[1]) );
} // Swap


Node *n1, *n2;
#define MAX_THREADS 6
DWORD WINAPI ThreadFunc(LPVOID);

int main()
{
	HANDLE hThrds[MAX_THREADS];
	int i;
	DWORD threadId;
	DWORD rc;
	
	// create 2 global Node data
	n1 = CreateNode();
	n2 = CreateNode();
	n1->idata = 100;
	n2->idata = 200;


	for(i=0; i<MAX_THREADS; ++i)
	{
		MTVERIFY( hThrds[i] = CreateThread(NULL,
			0,
			ThreadFunc,
			(LPVOID)i,
			0,
			&threadId) 
			);

		printf("Launched thread %d\n", i);
	}


	// wait for all threads to finish
	rc = WaitForMultipleObjects(
		MAX_THREADS,
		hThrds,
		TRUE,
		INFINITE);
	
	// close handles
	MTVERIFY( rc >= WAIT_OBJECT_0 && rc < MAX_THREADS );
	for(i=0; i<MAX_THREADS; ++i)
		MTVERIFY( CloseHandle(hThrds[i]) );

	// clean up (memory and mutex)
	DeleteNode(n1);
	DeleteNode(n2);

	printf("All threads + mutexes cleaned up\n");
	return EXIT_SUCCESS;
} // main



DWORD WINAPI ThreadFunc(LPVOID n)
{
	Sleep(1000);

	if(((int)n)%2)
	{	
		printf("Thread %d about to Swap(n1,n2)\n", n);
		Swap(n1, n2, (DWORD) n);		
	}
	else
	{
		printf("Thread %d about to Swap(n2,n1)\n", n);
		Swap(n2, n1, (DWORD) n);
	}

	printf("Thread %d idle\n", n);
	return (DWORD)n;
}

