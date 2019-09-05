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

#ifndef __single_lock_hpp__
#define __single_lock_hpp__

#include "sync_base.hpp"



namespace misc
{
	class single_lock
	{		
	public:
		//! Creates a wrapper around a valid synchronization object.
		single_lock(sync_base* object);

		//!	Destructor
		~single_lock();
		
		//! Locks the object and returns 0 if successful or otherwise throws
		//!	misc::exception.
		int lock();

		//! Locks the object and returns 0 if successful or 1 if timeout.
		int trylock(unsigned long milliseconds);

		//! Unlocks the object and returns 0 or otherwise throws misc::exception.
		int unlock();		
		
	private:
		// non-copyable
		single_lock(const single_lock&);
		single_lock& operator=(const single_lock&);
		
	protected:
		sync_base* m_object;
	};
}  // namespace



#endif // __single_lock_hpp__
