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
		//! thread is not running.
		thread();
		
		//!	detaches only if joinable and frees the resources.
		virtual ~thread();

		//! thread start method
		virtual int run() = 0;

		//! starts the thread and returns 0 if successful or 1 otherwise.
		int resume();
		
		//! joins a finished thread and returns 0 or 1 if timeout.
		unsigned long join(unsigned long timeout = INFINITE);

		//! copies thread returned value to retval and returns 0 or 1 otherwise.
		int get_exit_code(unsigned long* retval);

	private:
		//! non-copyable
		thread(const thread&);
		thread& operator=(const thread&);

		//! Thread start function
#ifdef _WIN32
		static unsigned int __stdcall ThreadFunc(void* lpParameter);
#else
		static void* start_routine(void* p);
#endif

	protected:
#ifdef _WIN32		
		HANDLE			m_handle;
		unsigned int	m_threadID;
#else
		pthread_t		m_thread;
		bool			m_terminated; //TODO: protect it with a critical_section
		int				m_retval;
#endif
	};

}  // namespace


#endif  // __thread_hpp__
