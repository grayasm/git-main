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


namespace misc
{
	mutex::mutex(bool initiallyOwned, const char_t* name)
		: sync_base(name)
	{
#ifdef _WIN32
		// Creates or opens a named or unnamed mutex object.
		m_handle = ::CreateMutex(NULL, initiallyOwned, name);
		if(m_handle == NULL)
			throw misc::exception("Cannot create the mutex!");					
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
		/*	PTHREAD_PROCESS_SHARED:
		 *	Permits a mutex to be operated upon by any thread that has access to
		 *	the memory where the mutex is allocated, even if the mutex is
		 *	allocated in memory that is shared by multiple processes.
		 */
		pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);
		
		int error = pthread_mutex_init(&mutex, &attr); // initialized and unlocked
		if(error)
			throw misc::exception("pthread_mutex_init error");
		pthread_mutexattr_destroy(&attr);
		
		if(initiallyOwned)
		{
			error = pthread_mutex_lock(&mutex);
			if(error)
				throw misc::exception("pthread_mutex_lock error");
		}			
#endif
	}

	mutex::~mutex()
	{
#ifdef _WIN32		
		if (m_handle != NULL)
		{
			/*
			CloseHandle invalidates the specified object handle, decrements 
			the object's handle count, and performs object retention checks. 
			After the last handle to an object is closed, the object is removed 
			from the system.
			Closing a thread handle does not terminate the associated thread. 
			To remove a thread object, you must terminate the thread, 
			then close all handles to the thread.
			*/			
			::CloseHandle(m_handle);
			m_handle = NULL;
		}
#else
#endif		
	}

	int mutex::lock()
	{
#ifdef _WIN32		
		DWORD dwRet = ::WaitForSingleObject(m_handle, INFINITE);
		if (dwRet == WAIT_OBJECT_0)
			return 0;
		else
			return 1;	// WAIT_TIMEOUT, WAIT_FAILED, WAIT_ABANDONED
#else
		error = pthread_mutex_lock(&mutex);
		if(error)
			throw misc::exception("pthread_mutex_lock error");
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
		int error = pthread_mutex_trylock(&mutex);
		if(EBUSY)
			return 1;
		
		if(error)
			throw misc::exception("pthread_mutex_trylock error");
		////////////////////////////////////////////////////////////////////////
		throw error; // work in progress
		void* retval;
		if(milliseconds == (unsigned long)INFINITE)
		{
			int error = pthread_join(m_thread, &retval);
			if(error)
				throw misc::exception("pthread_join error");
			return 0;
		}
		else
		{
			unsigned long nanosec = milliseconds * 1e6;
			unsigned long nslice = 1e9/5;//0.2
			
			struct timespec req, rem;
			req.tv_sec = 0;
			req.tv_nsec = misc::min<unsigned long>(nslice, nanosec);
			double dtimeout = nanosec;
			while(dtimeout > 0 && !m_terminated)
			{
				nanosleep(&req, &rem);
				dtimeout -= req.tv_nsec;
			}
			if(!m_terminated)
			{
				return 1; // WAIT_TIMEOUT
			}
			
			int error = pthread_join(m_thread, &retval);
			if(error)
				throw misc::exception("pthread_join error");
			return 0;
		}		
		////////////////////////////////////////////////////////////////////////
#endif	
	}

	int mutex::unlock()
	{
#ifdef _WIN32		
		return ::ReleaseMutex(m_handle);
#else
#endif		
	}

}; // namespace


