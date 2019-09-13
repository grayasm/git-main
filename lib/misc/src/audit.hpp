/*
  Copyright (C) 2014 Mihai Vasilian

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


#ifndef __audit_hpp__
#define __audit_hpp__


#include <ios>
#include <time.h>
#include "autoptr.hpp"
#include "string.hpp"


namespace misc
{
	class audit
	{
	public:
		typedef stl::autoptr<audit> Ptr;

	public:
		audit();
		~audit();
		audit(
			const stl::string& filepath, 
			std::ios::openmode mode = std::ios::out | std::ios::trunc);
		audit(const audit& tc);
		audit& operator=(const audit& tc);
		
		void log(time_t time, const char* file, size_t lineno, const char* fn, const char* msg) const;
		void log(const char* file, size_t lineno,  const char* fn, const char* msg) const;
		void log(const char* msg) const;

	private:
		void reset();

	private:
		stl::string	m_filepath;
	};
}


#define AUDIT(a, msg) a.log(time(NULL), __FILE__, __LINE__, __FUNCTION__, msg);
#define AUDIT2(a, msg) a.log(__FILE__, __LINE__, __FUNCTION__, msg);
#define AUDIT3(a, msg) a.log(msg);


#endif // __audit_hpp__