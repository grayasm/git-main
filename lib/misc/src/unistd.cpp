/*
  Copyright (C) 2013 Mihai Vasilian

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program. If not, see http://www.gnu.org/licenses/.

  contact: grayasm@gmail.com
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
	Sleep(milliseconds);
	return 0;	// error code not supported on WIN32
#else
	struct timespec req, rem;
	req.tv_sec = (time_t) (milliseconds / 1000);	// seconds
	req.tv_nsec = (milliseconds % 1000) * 1e6;		// nanoseconds
	return ::nanosleep(&req, &rem);
#endif
}

