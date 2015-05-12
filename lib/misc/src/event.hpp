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


#ifndef __event_hpp__
#define __event_hpp__



#include "sync_base.hpp"

namespace misc
{	
	/*	Win32: The most flexible type of synchronization object in Win32 is
	 *	the EVENT OBJECT. The event object is a kernel object whose only purpose
	 *	is to be either signaled or non-signaled.
	 *	With CreateEvent() it is specified whether the event resets itself
	 *	automatically to non-signaled after waking up a single thread or it 
	 *	needs manually ResetEvent() in which case all waiting threads 
	 *	WaitForSingleObject/similar will be woken up until event is reset.
	 * 
	 *	Pthreads (linux): A condition variable is a synchronization object that
	 *	can be signaled or non-signaled.
	 *	A condition variable resets itself automatically to non-signaled after
	 *	waking up one or more threads.
	 *	Waiting on a condition variable involves an additional mutex that can
	 *	be used in synchronization although it is not necessary.
	 *	The requirement is to pass to pthread_cond_wait, pthread_cond_timedwait
	 *	a locked mutex.
	 *	Signaling a condition variable is done with pthread_cond_signal (1 thread)
	 *	or pthread_cond_braodcast (wakes up all threads).
	 * 
	 *	The common ground is to use:
	 *	- a non-signaled initialized event/condition
	 *	- the event is reseting itself automatically after waking up
	 *	- lock is not interrupted by signals
	 *	- the event is not shared between processes
	 */
	class event : public sync_base
	{
	public:
		//! Creates a non-signaled event
		event();
		
		//! Destructor
		~event();
		
		/*! Locks the calling thread until event is signaled.
		 *! If event is signaled it returns 0 or otherwise throws misc::exception.
		 */
		int lock();	
		
		/*!	Locks the calling thread until event is signaled or time expires.
		 *!	milliseconds possible values are: any > 0 or -1 for INFINITE
		 *! If event is signaled it returns 0 or 1 for time out.
		 */
		int trylock(unsigned long milliseconds = 0);
		
		/*!	Signals the event and if successful return 0 or otherwise throws
		 *! misc::exception
		 */		
		int unlock();
		
		//! Similar with unlock.
		int setevent();

	private:		
		event(const event& tc);
		event& operator=(const event& tc);
		
	private:
#ifdef _WIN32
#else
		pthread_mutex_t		m_mtx;
		pthread_cond_t		m_cond;
#endif	
	};

}  // namespace



#endif // __event_hpp__


