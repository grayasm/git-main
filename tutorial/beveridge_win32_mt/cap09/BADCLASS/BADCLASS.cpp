/*
 * BadClass.cpp
 *
 * Shows the wrong way to start a thread based on a class member function.
 */

#include <windows.h>
#include <stdio.h>
#include <process.h>


typedef DWORD (WINAPI *PTHREADFUNC)(LPVOID n);


class ThreadObject
{
public:
	ThreadObject();
	void StartThread();
	virtual DWORD WINAPI ThreadFunc(LPVOID);
	void WaitForExit();
private:
	HANDLE	m_hThread;
	DWORD	m_threadId;
};

ThreadObject::ThreadObject()
{
	m_hThread = NULL;
	m_threadId = 0;
}

void ThreadObject::StartThread()
{
	m_hThread = (HANDLE) _beginthreadex(
							NULL,
							0,
							/* compilation	error C2440: 'type cast' : cannot convert from 'overloaded-function' to 'PTHREADFUNC' 
							 */
							(PTHREADFUNC) ThreadFunc,
							0,
							0,
							&m_threadId);

	if(m_hThread)
		printf("Thread launched\n");
}

void ThreadObject::WaitForExit()
{
	WaitForSingleObject(m_hThread, INFINITE);
	CloseHandle(m_hThread);
}

DWORD WINAPI ThreadObject::ThreadFunc(LPVOID param)
{
	printf("Entered thread routine\n");
	printf("Exit thread routine\n");
	return 0;
}

int main()
{
	ThreadObject obj;

	obj.StartThread();
	obj.WaitForExit();

	return 0;
}