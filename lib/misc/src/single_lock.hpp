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
		/*!	ctor
			\param object the synchronization object to be accessed.
			Cannot be NULL.
			\param lockitnow specifies whether to initially attempt to access 
			the supplied object.
		*/
		explicit single_lock(sync_base* object, bool lockitnow = false);

		//!	dtor
		~single_lock();
		
		/*!	lock
			The function will return only when the object is signaled.
			\return If the state of the object is signaled the
			return value is nonzero.
		*/
		int lock();

		/*!	trylock
			Waits until the object is in the signaled state or the time-out 
			interval elapses.
		*/
		int trylock(unsigned long milliseconds);

		/*!	unlock
			Releases ownership of the object.
			\return If the function succeeds, the return value is nonzero.
		*/
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
