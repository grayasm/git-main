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


#include "event.hpp"


namespace misc
{
	event::event(bool bSignaled, bool bManualReset, const char_t* name)
		: sync_base(name)
	{
		// Creates or opens a named or unnamed event object.
		m_handle = ::CreateEvent(
			NULL, 
			bManualReset,
			bSignaled, 
			name);

		if(m_handle == NULL)
			throw misc::exception("Cannot create the event!");
	}


	event::~event()
	{
		if(m_handle != NULL)
		{
			::CloseHandle(m_handle);
			m_handle = NULL;
		}
	}


	int event::lock()
	{
		DWORD dwRet = ::WaitForSingleObject(m_handle, INFINITE);
		// cannot get WAIT_TIMEOUT with INIFINITE
		// cannot get WAIT_ABANDONED (only for Mutexes)		
		if (dwRet == WAIT_OBJECT_0)
			return 1;
		else
			return 0;
	}

	int event::trylock(unsigned long milliseconds)
	{
		DWORD dwRet = ::WaitForSingleObject(m_handle, milliseconds);
		// cannot get WAIT_ABANDONED (only for Mutexes)		
		if (dwRet == WAIT_OBJECT_0)
			return 1;
		else
			return 0; // WAIT_TIMEOUT

		/*	In the EVENT context:
			
			The function pthread_mutex_trylock() is identical to 
			pthread_mutex_lock() except that if the mutex object referenced 
			by mutex is currently locked (by any thread, including 
			the current thread), the call returns immediately. 
		*/		
	}

	int event::unlock()
	{		
		return ::SetEvent(m_handle);		
	}


	int event::setevent()
	{		
		return ::SetEvent(m_handle);
	}

	int event::pulseevent()
	{		
		return ::PulseEvent(m_handle);
	}

	int event::resetevent()
	{
		return ::ResetEvent(m_handle);
	}
	
}; // namespace