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


#ifndef __multi_lock_hpp__
#define __multi_lock_hpp__


#include "sync_base.hpp"


namespace misc
{	
	class multi_lock
	{
	public:
		/*!	ctor
			\param objects[] array of pointers to the synchronization objects 
			to be waited on. Cannot be NULL.
			\param objcount number of objects in objects[] array. It must be
			greater than zero.
			\param lockitnow specifies whether to attempt locking objects 
			immediately.
		*/
		multi_lock(sync_base* objects[], unsigned long objcount, bool lockitnow = false);

		//!	dtor
		~multi_lock();

		/*!	lock
			The function will return only when the objects are signaled.
			\return	if the state of the objects is signaled the
			return value is nonzero.
		*/
		int lock();

		/*!	trylock
			Waits until the objects are in the signaled state or the time-out 
			interval elapses.
			\return if the function succeeded the return value is nonzero.
		*/
		int trylock(unsigned long milliseconds, bool wait_for_all);

		/*!	unlock
			Releases ownership of the objects.
			\return if the function succeeds, the return value is nonzero.
		*/
		int unlock();

	private:
		//! non-copyable
		multi_lock(const multi_lock&);
		multi_lock& operator=(const multi_lock&);
		
	protected:
		sync_base**		m_objects;
		unsigned long	m_count;
	};

}  // namespace


#endif // __multi_lock_hpp__





