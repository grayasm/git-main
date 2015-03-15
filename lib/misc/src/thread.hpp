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



#ifndef __thread_hpp__
#define __thread_hpp__




#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#define INFINITE -1
#endif




namespace misc
{
	class thread
	{
	public:
		//! ctor
		thread();
		
		//!	dtor
		virtual ~thread();

		/*!	run
			Thread starting function.
		*/
		virtual int run() = 0;

		/*!	resume
			Decrements a thread's suspend count. When the suspend count 
			is decremented to zero, the execution of the thread is resumed.
			\return value of the thread's previous suspend count. 
			If the function fails, the return value is -1. 
		*/
		int resume();
		
		/*!	join
			Waits until the thread is in the signaled state or the time-out 
			interval elapses.
		*/
		unsigned long join(unsigned long timeout = INFINITE);

		/*!	get_exit_code
		*/
		int get_exit_code(unsigned long* retval);


	protected:
#ifdef _WIN32		
		HANDLE			m_handle;
		unsigned int	m_threadID;
#endif
		

	private:
		//! non-copyable
		thread(const thread&);
		thread& operator=(const thread&);

#ifdef _WIN32
		//!	 start up function
		static unsigned int __stdcall ThreadFunc(void* lpParameter);
#endif
	};

}  // namespace


#endif  // __thread_hpp__
