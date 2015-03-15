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


#ifndef __sync_debug_hpp__
#define __sync_debug_hpp__

#include <stdlib.h>


#ifdef _WIN32
#include <windows.h>
#define dbgGetLastError GetLastError

// LINUX
#else
#define dbgGetLastError errno
#endif



/* DECLARATION ZONE */
#ifdef DEBUG

// available only with -DDEBUG
#	define MTVERIFY(a)												\
		if(!(a)) {													\
			PrintError(#a, __FILE__,__LINE__,dbgGetLastError());	\
		}

#else
#	define MTVERIFY(a) a
#endif


/* IMPLEMENTATION ZONE */

#ifdef _WIN32
void PrintError(LPSTR linedesc, LPSTR filename, int lineno, DWORD errnum)
{
	LPSTR lpBuffer;
	const size_t BUFFER_SIZE = 1500;
	char errbuf[BUFFER_SIZE];

	FormatMessageA(
		FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		errnum,
		LANG_NEUTRAL,
		(LPSTR)&lpBuffer,
		0,
		NULL);

	_snprintf(errbuf,
		BUFFER_SIZE,
		"\nThe following call failed at line %d in %s:\n\n"
		"    %s\n\n"
		"Reason: %s\n",
		lineno, filename, linedesc, lpBuffer);


	OutputDebugStringA(errbuf);

	/* Exit using a value appropriate for the operating system. */
	exit(EXIT_FAILURE);
}


//LINUX
#else
void PrintError(char* linedesc, char* filename, int lineno, long errnum)
{
	//TODO:
}
#endif



#endif // __sync_debug_hpp__