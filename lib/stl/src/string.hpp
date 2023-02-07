/*
Copyright (C) 2009 Mihai Vasilian
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

//stl
#include "basic_string.hpp"


namespace stl
{
#if defined UNICODE
	typedef stl::basic_string<wchar_t>	string;
#else
	typedef stl::basic_string<char>		string ;	
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


#if defined(_WIN32) && _MSC_VER < 1910
#   ifdef _UNICODE
#      define snwprintf _snwprintf
#   else
#      define snprintf _snprintf
#   endif
#else

#endif
}//namespace exp





#endif  //__string_hpp__
