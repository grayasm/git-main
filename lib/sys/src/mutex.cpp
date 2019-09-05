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



#include "mutex.hpp"
#include <errno.h>
#include "exception.hpp"
#include "algorithm.hpp"



#include <stdio.h> // for printf

namespace sys
{
	mutex::mutex()
		: sync_base()
	{
#ifdef _WIN32
		// Create a mutex: now owned (unlocked) and unnamed (not shared with
		// other processes).
		m_handle = ::CreateMutex(NULL, false, "");
		if(m_handle == NULL)
			throw stl::exception("Cannot create the mutex!");					
#else
		pthread_mutexattr_t attr;
		pthread_mutexattr_init(&attr);
		/*	PTHREAD_MUTEX_RECURSIVE:
		 *	A thread attempting to relock this mutex without first unlocking it
		 *	will succeed in locking the mutex.
		 *	The relocking deadlock (see PTHREAD_MUTEX_NORMAL) cannot occur with
		 *	this type of mutex.
		 *	Multiple locks of this mutex require the same number of unlocks 
		 *	to release the mutex before another thread can acquire the mutex.
		 *	A thread attempting to unlock a mutex which another thread has locked
		 *	will return with an error. A thread attempting to unlock an unlocked
		 *	mutex will return with an error.
		 */
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
		/*	PTHREAD_PROCESS_PRIVATE:
		 *	The mutex will only be operated upon by threads created within 
		 *	the same process as the thread that initialised the mutex.
		 */
		pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_PRIVATE);
		
		int error = pthread_mutex_init(&m_mtx, &attr); // initialized and unlocked
		if(error)
			throw stl::exception("pthread_mutex_init error");
		
		pthread_mutexattr_destroy(&attr);
#endif
	}

	mutex::~mutex()
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
			throw stl::exception("CloseHandle error");
		m_handle = NULL;
	
#else
		/*	It is safe to destroy an initialised mutex that is unlocked. 
		 *	Attempting to destroy a locked mutex results in undefined behaviour.
		 */
		pthread_mutex_unlock(&m_mtx);
		int error = pthread_mutex_destroy(&m_mtx);
		if(error)
			throw stl::exception("pthread_mutex_destroy error");
#endif		
	}

	int mutex::lock()
	{
#ifdef _WIN32		
		DWORD dwRet = ::WaitForSingleObject(m_handle, INFINITE);
		if(dwRet != WAIT_OBJECT_0) // WAIT_TIMEOUT, WAIT_FAILED, WAIT_ABANDONED
			throw stl::exception("WaitForSingleObject error");
		return 0;
#else
		int error = pthread_mutex_lock(&m_mtx);
		if(error)
			throw stl::exception("pthread_mutex_lock error");
		return 0;
#endif		
	}

	int mutex::trylock(unsigned long milliseconds)
	{
#ifdef _WIN32		
		DWORD dwRet = ::WaitForSingleObject(m_handle, milliseconds);		
		if (dwRet == WAIT_OBJECT_0)
			return 0;
		else
			return 1;	// WAIT_TIMEOUT, WAIT_FAILED, WAIT_ABANDONED
#else
		/*	If the mutex object referenced by mutex is currently locked 
		 *	(by any thread, including the current thread), the call returns 
		 *	immediately.
		 */
		if(milliseconds == (unsigned long)-1)
		{
			int error = pthread_mutex_lock(&m_mtx);
			if(error)
			{
				throw stl::exception("pthread_mutex_lock error");
			}
			return 0;
		}
		else
		{
			int error = pthread_mutex_trylock(&m_mtx);
			if(error == 0)	// succeeded
			{
				return 0;	// LOCKED
			}
			
			unsigned long nanosec = milliseconds * 1e6;
			unsigned long nslice = 1e9/5;//0.2 sec
			
			struct timespec req, rem;
			req.tv_sec = 0;
			req.tv_nsec = stl::min<unsigned long>(nslice, nanosec);
			
			double dtimeout = nanosec;
			while(dtimeout > 0 && error == EBUSY)
			{
				nanosleep(&req, &rem);
				dtimeout -= req.tv_nsec;
				error = pthread_mutex_trylock(&m_mtx);
			}
			
			if(error == 0)
			{
				return 0; // LOCKED
			}
			
			if(error == EBUSY)
			{
				return 1; // WAIT_TIMEOUT
			}
			
			throw stl::exception("pthread_mutex_trylock error");
		}
#endif	
	}

	int mutex::unlock()
	{
#ifdef _WIN32		
		if( ::ReleaseMutex(m_handle) == 0 )
			throw stl::exception("ReleaseMutex error");
		return 0;
#else
		int error = pthread_mutex_unlock(&m_mtx);
		if(error)
			throw stl::exception("pthread_mutex_unlock error");
		return 0;
#endif		
	}
	
	void mutex::accept(sync_visitor& visitor)
	{
		visitor.visit(*this);
	}

} // namespace


