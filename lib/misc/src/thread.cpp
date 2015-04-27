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
#include "exception.hpp"

#include <string>
#include <time.h>

#ifdef _WIN32
#include <process.h>
#else
#include <pthread.h>
#endif

#include <stdio.h>

namespace misc
{
	thread::thread()
	{
#ifdef _WIN32
		m_handle = (HANDLE)_beginthreadex(NULL, 
			0, 
			ThreadFunc, 
			(void*)this, 
			CREATE_SUSPENDED, 
			&m_threadID);

		if(m_handle == 0)
			throw misc::exception("_beginthreadex error");
#else
		// No API to create it in suspended mode. 
		// Suspend and resume require user implementation of condition variable
		// in the thread start_routine.
		m_thread = 0;
		m_terminated = false;
#endif
	}

	thread::~thread()
	{
#ifdef _WIN32
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
#else
		/*
			The pthread_detach() function is used to indicate to the 
			implementation that storage for the thread can be reclaimed 
			when that thread terminates. 
			If thread has not terminated, pthread_detach() will not 
			cause it to terminate.
			Either pthread_join or pthread_detach() should be called for each
			thread that an application creates, so that system resources for the
			thread can be released.
		*/
		if(m_thread && !m_terminated)
		{
			int ret = pthread_detach(m_thread);
			if(ret)
				throw misc::exception("pthread_detach error");
		}
#endif
	}

	int thread::resume()
	{
#ifdef _WIN32		
		if(::ResumeThread(m_handle) != -1)
			return 0;
		else
			return 1; // ERROR
#else
		// Default attribute set.
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
		
		int error = pthread_create(
			&m_thread,
			&attr,
			start_routine,
			(void*)this);
		
		if(error != 0)
			throw misc::exception("pthread_create error");
			
		pthread_attr_destroy(&attr);
		return 0;
#endif		
	}
	
	int thread::join(double seconds)
	{		
#ifdef _WIN32
		DWORD milliseconds = (DWORD)( 1000 * seconds );
		DWORD dwRet = ::WaitForSingleObject(m_handle, milliseconds);
		if (dwRet == WAIT_OBJECT_0)
			return 0;
		else
			return 1;	// WAIT_TIMEOUT, WAIT_FAILED, WAIT_ABANDONED
#else
		void* retval;
		if(seconds == INFINITE || m_terminated)
		{
			int error = pthread_join(m_thread, &retval);
			if(error)
				throw misc::exception("pthread_join error");
			return 0;
		}
		else
		{
			struct timespec req, rem;
			req.tv_sec = 0;
			req.tv_nsec = 1e9/5; // 0.2 sec
			double dtimeout = seconds;
			while(dtimeout > 0 && !m_terminated)
			{
				nanosleep(&req, &rem);
				dtimeout -= (req.tv_nsec / 1e9);
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
#endif		
	}

	int thread::get_exit_code(unsigned long* retval)
	{
#ifdef _WIN32
		if(WaitForSingleObject(m_handle, 0) != WAIT_OBJECT_0)// WAIT_TIMEOUT
			return 1;
		::GetExitCodeThread(m_handle, retval);
		return 0;
#else
		if(!m_terminated)
			return 1;
		
		*retval = m_retval;
		return 0;
#endif		
	}

#ifdef _WIN32
	unsigned int __stdcall thread::ThreadFunc(void* n)
	{
		thread* _this = (thread*)n;
		return _this->run();
	}
#else
	void* thread::start_routine(void* p)
	{
		thread* _this = (thread*)p;
		int ret = _this->run();
		
		//TODO: implement a condition_variable (has locking access)
		_this->m_terminated = true;
		_this->m_retval = ret;
		return 0;
	}
#endif
} // namespace



