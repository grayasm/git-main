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
