/*
 * CSCPP.cpp - implementing a critical section in c++
 */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>
#include "MtVerify.h"



class CriticalSection
{
public:
	CriticalSection();
	~CriticalSection();
	void Enter();
	void Leave();
private:
	CRITICAL_SECTION m_CS;
};

CriticalSection::CriticalSection()
{
	InitializeCriticalSection( &m_CS );
}

CriticalSection::~CriticalSection()
{
	DeleteCriticalSection( &m_CS );
}

void CriticalSection::Enter()
{
	EnterCriticalSection( &m_CS );
}

void CriticalSection::Leave()
{
	LeaveCriticalSection( &m_CS );
}

// Shared variable and the lock object
const int MAX_STR = 6;
char gString[MAX_STR];
CriticalSection* gCS;

unsigned __stdcall ThreadFunc(void*);

#define MAX_THREADS 9

int main()
{
	unsigned int threadId;
	HANDLE hThreads[MAX_THREADS];
	int i;
	DWORD rc;

	gCS = new CriticalSection();

	for(i=0; i < MAX_THREADS; ++i)
	{
		MTVERIFY( hThreads[i] = (HANDLE) _beginthreadex(
											NULL,
											0,
											ThreadFunc,
											(void*)i,
											0,
											&threadId)
				);

		printf("\n\tLaunched thread %d", i);
	}

	rc = WaitForMultipleObjects(
			MAX_THREADS,
			hThreads,
			TRUE,
			INFINITE);
	MTVERIFY( rc >= WAIT_OBJECT_0 && rc < WAIT_OBJECT_0 + MAX_THREADS );

	for(i=0; i < MAX_THREADS; ++i)
		MTVERIFY( CloseHandle(hThreads[i]) );
	
	printf("\n\tAll threads exited\n\n");

	if(gCS) delete gCS;

	return EXIT_SUCCESS;
} // main


unsigned __stdcall ThreadFunc(void* n)
{
	srand((unsigned int) GetTickCount() );
	Sleep( (rand() % 10) * 800 + 500 );

	gCS->Enter();
	sprintf(gString, "%d%d%d%d%d%c", n,n,n,n,n,'\0');
	printf("\n\tthread %d -> %s", n, gString);
	gCS->Leave();
	return (unsigned) n;
}