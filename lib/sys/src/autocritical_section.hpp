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



#ifndef __autocritical_section_hpp__
#define __autocritical_section_hpp__

#include "autoptr.hpp"
#include "critical_section.hpp"

namespace sys
{
	class autocritical_section
	{
	public:
		typedef stl::autoptr<autocritical_section> Ptr;

	public:
		autocritical_section(critical_section& cs);
		~autocritical_section();

	private:
		//! non copy-able
		autocritical_section(const autocritical_section&);
		autocritical_section& operator=(const autocritical_section&);

	private:
		critical_section& m_critical_section;
	};
} // namespace


#endif // __autocritical_section_hpp__

