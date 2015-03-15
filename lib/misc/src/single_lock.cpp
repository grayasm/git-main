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


namespace misc
{
	single_lock::single_lock(misc::sync_base* object, bool lockitnow)
	{		
		if(object == NULL)
			throw misc::exception("Invalid argument");
		m_object = object;
		if(lockitnow)
			m_object->lock();
	}

	single_lock::~single_lock()
	{
		/*	unlock() may freeze temporarly the stack unwinding. 
			Most probably we need a timed-out, safe unlock attempt.
		*/
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

}; // namespace