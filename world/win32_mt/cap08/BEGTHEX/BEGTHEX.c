/*
 * BEGTHEX.c
 *
 * You should always use the multithreaded C run-time library, along
 * with _beginthreadex() & _endthreadex(), if any thread other than
 * the primary thread does any of the following:
 *
 * 1) Uses malloc() or free() in C, or new or delete in C++
 * 2) Calls anything in stdio.h or io.h
 *    This includes fucntions such as fopen() and open(), getchar()
 *    write() and printf(). All of these functions use shared data
 *    structures as well as errno.
 * 3) Uses floating point variables or functions
 * 4) Calls any run-time functions that use a static buffer, such as
 *    asctime() strtok() rand()
 *
 * In order to be thread-safe the run-time C library must do some
 * bookkeeping for each thread that starts up and shuts down. Without
 * this bookkeeping, the run-time library would not know to allocate
 * a new block of thread-local data for each new thread. Therefore
 * there is a wrapper for CreateThread() called _beginthreadex() that
 * takes care of additional bookkeeping.
 */

#include <windows.h>
#include <stdio.h>
#include <process.h> // _beginthreadex()


unsigned __stdcall threadfunc(void* n);

int main()
{
	unsigned long	thd;
	unsigned		tid;

	thd = _beginthreadex(
					NULL,
					0,
					threadfunc,
					0,
					0,
					&tid);
	
	if((HANDLE)thd != NULL)
	{
		CloseHandle((HANDLE)thd);
	}

	printf("\n\tmain thread wait 1 sec...");

	Sleep(1000);

	printf("\n\tmain thread exit\n\n");

	return EXIT_SUCCESS;
} // main


unsigned __stdcall threadfunc(void* n)
{
	printf("\n\trunning threadfunc(%d)", n);
	return (unsigned) n;
}