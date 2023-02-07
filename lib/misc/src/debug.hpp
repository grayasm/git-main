/*
Copyright (C) 2014 Mihai Vasilian
*/

#ifndef __debug_hpp__
#define __debug_hpp__


#ifdef _WIN32
#	define DEBUG_VIEW(text)	\
		std::stringstream ss;	\
		ss << __FUNCTION__ << " line: " << __LINE__ << " [" << text << "]"; \
		OutputDebugString(ss.rdbuf()->str().c_str());
#else
#	define DEBUG_VIEW(text)	\
		std::cout << "\n" << __FUNCTION__ << " line: " << __LINE__ << " [" << a << "]";
#endif


#endif //__debug_hpp__
