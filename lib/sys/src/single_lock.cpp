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


#include "single_lock.hpp"
#include "exception.hpp"

namespace sys
{
	single_lock::single_lock(sys::sync_base* object)
	{		
		if(object == NULL)
			throw stl::exception("single_lock invalid parameter");
		m_object = object;
	}

	single_lock::~single_lock()
	{
		// *this has no ownership of m_object.
	}

	int single_lock::lock()
	{
		return m_object->lock();
	}

	int single_lock::trylock(unsigned long milliseconds)
	{
		return m_object->trylock(milliseconds);
	}

	int single_lock::unlock()
	{
		return m_object->unlock();
	}

} // namespace