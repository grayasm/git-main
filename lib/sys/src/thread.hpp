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
#endif




namespace sys
{
	/*	Abstract base class for a thread.
	 *	Derive own class from this and instantiate it with preferred constructor.
	 *	Implement own run() method for the separate thread entry point.
	 *	Call resume() to start the thread which will call back the run().
	 *	Thread cannot be:
	 *		- canceled
	 *		- detached
	 *
	 *	To cancel a thread implement your own cancellation mechanism which is
	 *	easy and safer than TerminateThread, pthread_cancel, etc.  
	 *		- add to the derived class a method "void cancel(bool enable)"
	 *		- set an internal member to true or false
	 *		- check it at convenient time from the thread
	 *		- if true then abort calculations and return as quick as possible
	 * 
	 *	Detaching is not supported because of the object oriented paradigm used
	 *	for this class. It requires to:
	 *		- control the life of this resource, thus
	 *		- join always the thread before deleting it
	 * 
	 *	A joined thread can be resumed again, if needed. It is not required to
	 *	delete this object and create another one to start it again.
	 */
	class thread
	{
	public:
		//! Thread is not running.
		thread();
		
		//! Destroys a thread that is not running, otherwise throws stl::exception.
		virtual ~thread();

		//! Called from the new thread.
		virtual unsigned long run() = 0;

		//! Starts a new thread and returns 0 if successful or otherwise throws
		//! stl::exception. A joined thread can be resumed again.
		int resume();
		
		/*! Joins a finished thread and returns 0 or 1 if timeout.
		 *! milliseconds possible values are: any > 0 or -1 for INFINITE
		 */
		int join(unsigned long milliseconds = (unsigned long)-1);

		//! Copies thread returned value to retval and returns 0 or 1 otherwise.
		int get_exit_code(unsigned long* retval);

		//! Cancellation of a thread is not supported.

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

	private:
#ifdef _WIN32		
		HANDLE			m_handle;
		unsigned int	m_threadID;
#else
		pthread_t		m_thread;
#endif
		bool			m_terminated;
		bool			m_joined;
		unsigned long	m_retval;
	};

}  // namespace


#endif  // __thread_hpp__
