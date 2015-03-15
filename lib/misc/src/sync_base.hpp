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


#ifndef __sync_base_hpp__
#define __sync_base_hpp__



#include "string.hpp"

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif




namespace misc
{	
	class sync_base
	{		
	public:
		//!	sync_base
		sync_base(const char_t* name);

		//!	virtual destructor
		virtual ~sync_base();
	
		/*!	lock
			The function will return only when the object is signaled.
			\return If the state of the object is signaled the
			return value is nonzero.
		*/
		virtual int lock() = 0;

		/*!	trylock
			Waits until the object is in the signaled state or the time-out 
			interval elapses.
		*/
		virtual int trylock(unsigned long milliseconds) = 0;

		/*!	unlock
			Releases ownership of the object.
			\return If the function succeeds, the return value is nonzero.
		*/
		virtual int unlock() = 0;

	private:
		//! non-copyable
		sync_base(const sync_base&);
		sync_base& operator=(const sync_base&);
		
		friend class single_lock;
		friend class multi_lock;


	protected:
#ifdef _WIN32
		HANDLE			m_handle;
#endif
		misc::string	m_name;

	private:
	};
} // namespace




#endif // __sync_base_hpp__
