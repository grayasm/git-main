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


#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif




namespace misc
{	
	//! Forward declarations
	class sync_base;
	class mutex;
	class semaphore;
	class event;
	
	//! Visitor class.
	class sync_visitor
	{
	public:
		sync_visitor();
		virtual ~sync_visitor();
		virtual void visit(misc::sync_base& visit) = 0;
		virtual void visit(misc::mutex& visit) = 0;
		virtual void visit(misc::semaphore& visit) = 0;
		virtual void visit(misc::event& visit) = 0;
	};
	
	/*!	Base class for (some) synchronization objects.
	 *! All types deriving from this class have a corresponding visit function
	 *! in the sync_visitor.
	 */
	class sync_base
	{		
	public:
		//! Constructor
		sync_base();

		//! Destructor
		virtual ~sync_base();

		//! Locks the object and returns 0 or otherwise throws misc::exception.
		virtual int lock() = 0;
		
		/*! Locks the object and returns 0 or 1 if timeout.
		 *!	milliseconds possible values are: any > 0 or -1 for INFINITE
		 */
		virtual int trylock(unsigned long milliseconds = 0) = 0;
		
		//! Unlocks the object and returns 0 or otherwise throws misc::exception.
		virtual int unlock() = 0;
		
		//! Accepts a visitor
		virtual void accept(sync_visitor& visitor) = 0;
		

	private:
		//! non-copyable
		sync_base(const sync_base&);
		sync_base& operator=(const sync_base&);
		
		// friend class multi_lock;

	protected:
#ifdef _WIN32
		HANDLE			m_handle;
#else
#endif

	private:
	};
} // namespace



#endif // __sync_base_hpp__
