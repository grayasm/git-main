/*
Copyright (C) 2013 Mihai Vasilian
*/



#include "unistd.hpp"
//c
#include <stdlib.h>     // system

#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>		// nanosleep
#endif

//c++
//misc

#ifdef _WIN32
unsigned int sleep(unsigned int seconds)
{
	/*	Returns zero if the requested time has elapsed, or the number of seconds
		left to sleep, if the call was interrupted by a signal handler.
	*/
	Sleep(seconds * 1000);
	return 0; // remainder not supported on Win32
}
#endif



void clrscr()
{
#if defined _WIN32
    //windows
    system("cls");
#else
    //linux
    system("clear");
#endif
}

// sleep for the specified number of milliseconds
int	msleep(unsigned long milliseconds)
{
#ifdef _WIN32
	/*	http://www.geisswerks.com/ryan/FAQS/timing.html
		Sleep(1) has a precision of 10ms without timeBeginPeriod/timeEndPeriod
		The 2 functions require linking with "winmm.lib"
	*/
	timeBeginPeriod(1);
	Sleep(milliseconds);
	timeEndPeriod(1);
	return 0;	// error code not supported on WIN32
#else
	struct timespec req, rem;
	req.tv_sec = (time_t) (milliseconds / 1000);	// seconds
	req.tv_nsec = (milliseconds % 1000) * 1e6;		// nanoseconds
	return ::nanosleep(&req, &rem);
#endif
}

