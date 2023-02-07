/*
Copyright (C) 2009 Mihai Vasilian
*/


#include "exception.hpp"
#include <malloc.h>
#include <cstring>



namespace stl
{
	exception::exception()
	{
		m_str = 0;
	}

	exception::exception(const char* str)
	{
		size_t sz = ::strlen(str);
		if(sz)
		{
			m_str = (char*) malloc(sz + 1);
			::strncpy(m_str, str, sz+1);
		}
	}

	exception::~exception() throw()
	{
		if(m_str)
		{
			free(m_str);
			m_str = 0;
		}
	}

	const char* exception::what() const throw()
	{
		if(m_str)
			return m_str;
		else
			return "unknown";
	}
} // namespace
