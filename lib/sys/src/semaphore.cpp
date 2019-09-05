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


#include "semaphore.hpp"
#include "exception.hpp"

#ifdef _WIN32
#else
#include <time.h>
#include <errno.h>
#endif

namespace misc
{	
	semaphore::semaphore(unsigned int maxlocks)
		: sync_base()
	{
		if(maxlocks == 0)
			throw misc::exception("semaphore maxlocks must be > 0");
		
#ifdef _WIN32
		m_handle = ::CreateSemaphore(NULL, maxlocks, maxlocks, "");
		if(m_handle == NULL)
			throw misc::exception("CreateSemaphore error");
#else
		int pshared = 0; // not shared with other processes atm
		int error = sem_init(&m_sem, pshared, maxlocks);
		if(error)
			throw misc::exception("sem_init error");
#endif
	}

	semaphore::~semaphore()
	{
#ifdef _WIN32
		/*
		CloseHandle invalidates the specified object handle, decrements 
		the object's handle count, and performs object retention checks. 
		After the last handle to an object is closed, the object is removed 
		from the system.
		Closing a thread handle does not terminate the associated thread. 
		To remove a thread object, you must terminate the thread, 
		then close all handles to the thread.
		*/
		if( ::CloseHandle(m_handle) == 0 )
			throw misc::exception("CloseHandle error");
		m_handle = NULL;
#else
		int error = sem_destroy(&m_sem);
		if(error)
			throw misc::exception("sem_destroy error");
#endif
	}

	int semaphore::lock()
	{
#ifdef _WIN32
		DWORD dwRet = ::WaitForSingleObject(m_handle, INFINITE);
		if(dwRet != WAIT_OBJECT_0) // WAIT_TIMEOUT, WAIT_FAILED, WAIT_ABANDONED
			throw misc::exception("WaitForSingleObject error");
		return 0;
#else
		int error;
		
		// mutex cannot be interrupted by signals.
		// semaphore gets the same treatment here.		
		while((error = sem_wait(&m_sem)) == -1 && errno == EINTR)
			continue;
		
		if(error == 0)
			return 0;

		throw misc::exception("sem_wait error");
#endif
	}

	int semaphore::trylock(unsigned long milliseconds)
	{
#ifdef _WIN32		
		DWORD dwRet = ::WaitForSingleObject(m_handle, milliseconds);		
		if (dwRet == WAIT_OBJECT_0)
			return 0;
		else
			return 1;	// WAIT_TIMEOUT, WAIT_FAILED, WAIT_ABANDONED
#else
		int error;
		if(milliseconds == (unsigned long)-1)
		{
			// mutex cannot be interrupted by signals.
			// semaphore gets the same treatment here.		
			while((error = sem_wait(&m_sem)) == -1 && errno == EINTR)
				continue;
		
			if(error == 0)
				return 0;
			
			throw misc::exception("sem_wait error");
		}
		else
		{
			struct timespec ts;
			if(clock_gettime(CLOCK_REALTIME, &ts) == -1)
				throw misc::exception("clock_gettime error");
			
			ts.tv_sec += (time_t) (milliseconds / 1000);// seconds
			ts.tv_nsec += (milliseconds % 1000) * 1e6;	// nanoseconds
			if(ts.tv_nsec >= 1e9)
			{
				ts.tv_sec += 1;
				ts.tv_nsec -= 1e9;
			}
			
		
			// mutex cannot be interrupted by signals.
			// semaphore gets the same treatment here.
			while((error = sem_timedwait(&m_sem, &ts)) == -1 && errno == EINTR)
				continue;
			
			if(error == 0)
				return 0;	// success
			if(error == -1 && errno == ETIMEDOUT)
				return 1;	// timeout
			
			throw misc::exception("sem_timedwait error");
		}
#endif		
	}

	int semaphore::unlock()
	{
#ifdef _WIN32
		/*	Increases the count of the specified semaphore object
			by a specified amount.
		*/
		if( ::ReleaseSemaphore(m_handle, 1, NULL) == 0 )
			throw misc::exception("ReleaseSemaphore error");
		return 0;
#else
		/*	http://linux.die.net/man/3/sem_post
		 *	sem_post() increments (unlocks) the semaphore pointed to by sem.
		 * 
		 *	Currently in linux we can increment sem_t value above initial given
		 *	counter which is a bit strange.
		 *	Ex:
		 *	sem_init(&sem, 0, 0);	// locked, value=0
		 *  sem_post(&sem);			// unlocked, value=1 (1 thread may lock it)
		 *  sem_post(&sem);			// unlocked, value=2 (2 threads may lock it)
		 */
		int error = sem_post(&m_sem);
		if(error)
			throw misc::exception("sem_post error");
		return 0;
#endif
	}
	
	void semaphore::accept(sync_visitor& visitor)
	{
		visitor.visit(*this);
	}
} // namespace