/*
  Copyright (C) 2009 Mihai Vasilian

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



#ifndef __string_hpp__
#define __string_hpp__

//c
#include <locale.h>
#include <stdlib.h>
#ifdef _WIN32
#include <tchar.h>
#endif // _WIN32

#include <wchar.h>

//c++
#include <cstring>

//misc
#include "generic_string.hpp"


namespace misc
{
#if defined UNICODE
	typedef misc::generic_string<wchar_t>	string;
#else
	typedef misc::generic_string<char>		string ;	
#endif


#ifdef _WIN32
#	ifdef __MINGW32__
#		define U(t) t
		typedef char char_t;
#	else// #endif __MINGW32__
#		define U(t)   _T(t)
#		if defined UNICODE
			typedef wchar_t char_t ;
#		else //ASCII
			typedef char char_t ;
#		endif
#	endif
#else //LINUX
#	if defined UNICODE
		typedef wchar_t char_t ;
#		define U(t)  L##t				
#	else
		typedef char char_t ;
#		define U(t)  t
#	endif
#endif


#ifdef _WIN32
#   ifdef _UNICODE
#      define snwprintf _snwprintf
#   else
#      define snprintf _snprintf
#   endif
#else

#endif
}//namespace exp





#endif  //__string_hpp__
