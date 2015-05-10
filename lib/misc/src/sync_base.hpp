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
	class sync_base
	{		
	public:
		sync_base();

		virtual ~sync_base();

		virtual int lock() = 0;
		
		/*	milliseconds can have any > 0 value of -1 for INFINITE
		 */
		virtual int trylock(unsigned long milliseconds) = 0;
		virtual int unlock() = 0;

	private:
		//! non-copyable
		sync_base(const sync_base&);
		sync_base& operator=(const sync_base&);
		
		// friend class single_lock;
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
