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
