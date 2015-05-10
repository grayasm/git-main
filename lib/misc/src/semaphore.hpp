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


#ifndef __semaphore_hpp__
#define __semaphore_hpp__


#include "sync_base.hpp"

#ifdef _WIN32
#else
#include <semaphore.h>
#endif



namespace misc
{
	/*
	 *	Locking a semaphore sem(1) 2 times from the same thread will result in
	 *	deadlock.
	 */
	class semaphore : public sync_base
	{
	public:
		//! Semaphore supports maxlocks (>0) locks.
		semaphore(unsigned int maxlocks);
		
		//! Semaphore resource is released back to OS.
		~semaphore();		
		
		//! Aquire a lock on the semaphore and returns 0 or 1 if interrupted by signal.
		int lock();
		
		/*! Aquire a lock on the semaphore and returns 0 or 1 if timeout.
		 *! milliseconds possible values are: any > 0 or -1 for INFINITE
		 */
		int trylock(unsigned long milliseconds = 0);
		
		//! Unlock a previous lock on the semaphore and returns 0 or throw otherwise.
		int unlock();
		
		// get lock count would be nice here.

	private:
		//non-copyable
		semaphore(const semaphore& tc);
		semaphore& operator=(const semaphore& tc);

#ifdef _WIN32
#else
		sem_t m_sem;
#endif
	};
} // namespace


#endif // __semaphore_hpp__


