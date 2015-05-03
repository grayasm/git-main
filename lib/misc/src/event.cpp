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
	event::event(bool bSignaled, bool bManualReset)
		: sync_base()
	{
#ifdef _WIN32
		// Creates or opens a named or unnamed event object.
		m_handle = ::CreateEvent(
			NULL, 
			bManualReset,
			bSignaled, 
			"");

		if(m_handle == NULL)
			throw misc::exception("Cannot create the event!");
#else
#endif
	}


	event::~event()
	{
#ifdef _WIN32
		if(m_handle != NULL)
		{
			::CloseHandle(m_handle);
			m_handle = NULL;
		}
#else
#endif
	}


	int event::lock()
	{
#ifdef _WIN32
		DWORD dwRet = ::WaitForSingleObject(m_handle, INFINITE);
		// cannot get WAIT_TIMEOUT with INIFINITE
		// cannot get WAIT_ABANDONED (only for Mutexes)		
		if (dwRet == WAIT_OBJECT_0)
			return 1;
		else
			return 0;
#else
		return 0;
#endif
	}

	int event::trylock(unsigned long milliseconds)
	{
#ifdef _WIN32
		DWORD dwRet = ::WaitForSingleObject(m_handle, milliseconds);
		// cannot get WAIT_ABANDONED (only for Mutexes)		
		if (dwRet == WAIT_OBJECT_0)
			return 1;
		else
			return 0; // WAIT_TIMEOUT
#else
		return 0;
#endif
	}

	int event::unlock()
	{
#ifdef _WIN32
		return ::SetEvent(m_handle);
#else
		return 0;
#endif
	}


	int event::setevent()
	{
#ifdef _WIN32
		return ::SetEvent(m_handle);
#else
		return 0;
#endif
	}

	int event::pulseevent()
	{
#ifdef _WIN32		
		return ::PulseEvent(m_handle);
#else
		return 0;
#endif
	}

	int event::resetevent()
	{
#ifdef _WIN32
		return ::ResetEvent(m_handle);
#else
		return 0;
#endif
	}	
} // namespace