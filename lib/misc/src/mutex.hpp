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


#ifndef __mutex_hpp__
#define __mutex_hpp__


#include "sync_base.hpp"

#ifdef _WIN32
#else
#include <pthread.h>
#endif


namespace misc
{
	/*
	A mutex in Win32 is used to do many of the same things as a critical section
	but it sacrifices speed for increased flexibility. As you may have guessed
	mutex stands for MUTual EXclusion. 	
	Only one thread at a time is allowed to own a mutex, just as only one 
	thread at a time can enter a critical section. Although mutexes and critical 
	sections do the same thing, there are some differences in how they operate:
	
	>> It takes almost 100 times longer to lock an unowned mutex
	than it does to lock an unowned critical section because the critical 
	section can be done in user mode without involving the kernel.

	>> Mutexes can be used between processes. Critical sections can only be
	used within the same process.

	>> You can specify a timeout when waiting on a mutex, but not a critical
	section.
	*/



	class mutex : public sync_base
	{
	public:
		//! Creates an unlocked mutex.
		mutex();
		
		//! Destructor
		~mutex();

		//! Locks the mutex and returns 0 or otherwise 1.
		int lock();

		//! Locks the mutex and returns 0 or 1 if timeout.
		int trylock(unsigned long milliseconds = INFINITE);

		//! Unlocks the mutex and returns 0 or 1 otherwise.
		int unlock();

	private:
		//non-copyable
		mutex(const mutex& tc);
		mutex& operator=(const mutex& tc);	
		
#ifdef _WIN32
#else
		pthread_mutex_t m_mtx;
#endif
	};
}  // namespace



#endif // __mutex_hpp__
