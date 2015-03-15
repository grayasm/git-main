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
		// Creates or opens a named or unnamed mutex object.
		m_handle = ::CreateMutex(NULL, initiallyOwned, name);
		if(m_handle == NULL)
			throw misc::exception("Cannot create the mutex!");					
	}

	mutex::~mutex()
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

	int mutex::lock()
	{
		DWORD dwRet = ::WaitForSingleObject(m_handle, INFINITE);

		if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_ABANDONED)
			return 1;
		else
			return 0;	// WAIT_TIMEOUT
	}

	int mutex::trylock(unsigned long milliseconds)
	{
		DWORD dwRet = ::WaitForSingleObject(m_handle, milliseconds);
		
		if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_ABANDONED)
			return 1;
		else
			return 0;	// WAIT_TIMEOUT

		/*	The function pthread_mutex_trylock() is identical to 
			pthread_mutex_lock() except that if the mutex object referenced 
			by mutex is currently locked (by any thread, including 
			the current thread), the call returns immediately. 
		*/		
	}

	int mutex::unlock()
	{
		return ::ReleaseMutex(m_handle);
	}

}; // namespace


