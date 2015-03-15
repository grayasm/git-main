/*
 * Member2.cpp
 *
 * Sample code for "Multithreading Applications in Win32"
 * This is from Chapter 9, just after Listing 9-3.
 *
 * Shows how to start a thread based on
 * a class member function using
 * a C-style function.
 *
 * Build this file with the command line:
 *
 *    cl /MD Member2.cpp
 *
 */

#define WIN32_LEAN_AND_MEAN
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <process.h>

// Work around the buggy _beginthreadex() prototype
typedef unsigned (WINAPI *PBEGINTHREADEX_THREADFUNC)(
    LPVOID lpThreadParameter
    );
typedef unsigned *PBEGINTHREADEX_THREADID;

// Define the prototype for the function used
// to start the thread.
DWORD WINAPI ThreadFunc(LPVOID param);


class ThreadObject
{
public:
    ThreadObject();
    void StartThread();
    void WaitForExit();

    // Thread member function must be public
    // or the C-style function will not have
    // access rights.
    virtual DWORD ThreadMemberFunc();

protected:
    HANDLE  m_hThread;
    DWORD   m_ThreadId;
};

ThreadObject::ThreadObject()
{
    m_hThread = NULL;
    m_ThreadId = 0;
}

void ThreadObject::StartThread()
{
    m_hThread = (HANDLE)_beginthreadex(NULL,
        0,
        (PBEGINTHREADEX_THREADFUNC) ThreadFunc,
        (LPVOID)this,
        0,
        (PBEGINTHREADEX_THREADID) &m_ThreadId );
    if (m_hThread) {
        printf("Thread launched\n");
    }
}

void ThreadObject::WaitForExit()
{
    WaitForSingleObject(m_hThread, INFINITE);
    CloseHandle(m_hThread);
}


//
// This function is called first when
// the thread starts up.
//
DWORD WINAPI ThreadFunc(LPVOID param)
{
    // Use the param as the address of the object
    ThreadObject* pto = (ThreadObject*)param;
    // Call the member function. Since we have a
    // proper object pointer, even virtual functions
    // will be called properly.
    return pto->ThreadMemberFunc();
}

//
// This above function ThreadFunc() calls this
// function after the thread starts up.
//
DWORD ThreadObject::ThreadMemberFunc()
{
    // Do something useful ...

    return 0;
}

void main()
{
    ThreadObject obj;

    obj.StartThread();
    obj.WaitForExit();
}
