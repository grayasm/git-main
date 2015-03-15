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



#include "thread.hpp"
#include <process.h>
#include <string>
#include "exception.hpp"



namespace misc
{
	thread::thread()
	{
		m_handle = (HANDLE)_beginthreadex(NULL, 
			0, 
			ThreadFunc, 
			(void*)this, 
			CREATE_SUSPENDED, 
			&m_threadID);

		if(m_handle == 0)
			throw misc::exception("Failed to create the thread!");
	}

	thread::~thread()
	{
		if(m_handle)
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
			m_handle	= NULL;
			m_threadID		= 0;
		}		
	}

	int thread::resume()
	{
		return ::ResumeThread(m_handle);
	}
	
	unsigned long thread::join(unsigned long timeout)
	{		
		DWORD dwRet = ::WaitForSingleObject(m_handle, timeout);
		if (dwRet == WAIT_OBJECT_0 || dwRet == WAIT_ABANDONED)
			return 1;
		else
			return 0;	// WAIT_TIMEOUT
	}

	int thread::get_exit_code(unsigned long* retval)
	{		
		return ::GetExitCodeThread(m_handle, retval);		
	}

	unsigned int __stdcall thread::ThreadFunc(void* n)
	{
		thread* _this = (thread*)n;
		return _this->run();
	}
}; // namespace



