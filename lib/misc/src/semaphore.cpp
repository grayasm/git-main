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


namespace misc
{	
	semaphore::semaphore(long available, long maxallowed, const char_t* name)
		: sync_base(name)
	{
		m_handle = ::CreateSemaphore(NULL, available, maxallowed, name);

		if(m_handle == NULL)
			throw misc::exception("Cannot create semaphore!");
	}

	semaphore::~semaphore()
	{
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
	}

	int semaphore::lock()
	{
		DWORD dwRet = ::WaitForSingleObject(m_handle, INFINITE);
		
		if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_ABANDONED)
			return 1;
		else
			return 0;	// WAIT_TIMEOUT
	}

	int semaphore::trylock(unsigned long milliseconds)
	{
		DWORD dwRet = ::WaitForSingleObject(m_handle, milliseconds);
		
		if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_ABANDONED)
			return 1;
		else
			return 0;	// WAIT_TIMEOUT

		/*	In the SEMAPHORE context:
			
			The function pthread_mutex_trylock() is identical to 
			pthread_mutex_lock() except that if the mutex object referenced 
			by mutex is currently locked (by any thread, including 
			the current thread), the call returns immediately. 
		*/		
	}

	int semaphore::unlock()
	{
		/*	Increases the count of the specified semaphore object
			by a specified amount.
		*/
		return ::ReleaseSemaphore(m_handle, 1, NULL);
	}

}; // namespace