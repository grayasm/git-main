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



#ifdef _WIN32
#include <process.h>
#else
#endif

// c/c++
#include <time.h>	//nanosleep


// libraries
#include "thread.hpp"
#include "exception.hpp"
#include "algorithm.hpp"

namespace misc
{
	thread::thread()
	{
#ifdef _WIN32
		m_handle = 0;
		m_threadID = 0;
#else
		// pthread_t: No API to create it in suspended mode. 
		// Suspend and resume require user implementation of condition variable
		// in the thread start_routine.
		m_thread = 0;
#endif

		m_terminated = false;
		m_joined = false;
		m_retval = 0;
	}

	thread::~thread()
	{
#ifdef _WIN32
		if(m_handle)
		{
			if(!m_terminated)
				throw misc::exception("cannot destroy running thread");

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

			m_handle	= 0;
			m_threadID	= 0;
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
		if(m_thread)
		{
			if(!m_terminated)
				throw misc::exception("cannot destroy running thread");
			if(m_joined)
				return;
			int ret = pthread_detach(m_thread);
			if(ret)
				throw misc::exception("~dtor: pthread_detach error");
		}
#endif
	}

	int thread::resume()
	{
#ifdef _WIN32
		if( m_handle )
		{
			// _this can start a new thread only if the current one has
			// finished and was joined so the returned value is known.
			if( !m_joined )
				throw misc::exception("resume not joined thread error");
	
			if( ::CloseHandle(m_handle) == 0 )
				throw misc::exception("CloseHandle error");

			m_terminated = false;
			m_joined = false;
			m_retval = 0;
		}

		m_handle = (HANDLE) ::_beginthreadex(NULL, 
			0,
			ThreadFunc,
			(void*)this,
			0,	// 0 to start immediately or CREATE_SUSPENDED
			&m_threadID);

		if(m_handle == 0)
			throw misc::exception("_beginthreadex error");

		return 0;
#else
		if(m_thread)
		{
			// _this can start a new thread only if the current one has
			// finished and was joined so the returned value is known.
			if( !m_joined )
				throw misc::exception("resume not joined thread error");
	
			//pthread_detach(m_thread); -> SEGFAULT

			m_terminated = false;
			m_joined = false;
			m_retval = 0;
		}
				
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
	
	int thread::join(unsigned long milliseconds)
	{		
#ifdef _WIN32
		if(milliseconds == -1)
			milliseconds = INFINITE; // to be sure it has the correct value.

		DWORD dwRet = ::WaitForSingleObject(m_handle, milliseconds);
		if (dwRet == WAIT_OBJECT_0)
		{
			m_joined = true;
			return 0;
		}
		else
		{
			return 1;	// WAIT_TIMEOUT, WAIT_FAILED, WAIT_ABANDONED
		}
#else
		if(m_joined)
			throw misc::exception("pthread_join already joined");
		
		void* retval;
		if(milliseconds == (unsigned long)-1 || m_terminated)
		{
			int error = pthread_join(m_thread, &retval);
			if(error)
				throw misc::exception("pthread_join error");
			m_joined = true;
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
			m_joined = true;
			return 0;
		}		
#endif		
	}

	int thread::get_exit_code(unsigned long* retval)
	{
#ifdef _WIN32
		if( ::WaitForSingleObject(m_handle, 0) != WAIT_OBJECT_0 )
			return 1;	// WAIT_TIMEOUT
		
		*retval = m_retval;
		return 0;
#else
		if(!m_terminated)
			return 1;
		
		*retval = m_retval;
		return 0;
#endif		
	}

	
#ifdef _WIN32
	unsigned int __stdcall thread::ThreadFunc(void* lpParameter)
	{
		thread* _this = (thread*)lpParameter;
		unsigned long ret = _this->run();

		//	If _this is already destroyed then the following 
		//	will access invalid memory
		_this->m_retval = ret;
		_this->m_terminated = true;

		return 0;
	}
#else
	void* thread::start_routine(void* p)
	{
		thread* _this = (thread*)p;
		unsigned long ret = _this->run();

		//	If _this is already destroyed then the following 
		//	will access invalid memory.
		_this->m_retval = ret;
		_this->m_terminated = true;

		return 0;
	}
#endif
} // namespace



