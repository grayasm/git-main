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


#ifndef __critical_section_hpp__
#define __critical_section_hpp__


#include "sync_base.hpp"
#include "mutex.hpp"

#ifdef _WIN32
#else
#include <pthread.h>
#endif



namespace sys
{
	/*
	A critical section is that portion of the code that accesses a shared 
	resource. A resource in this case is not a resource from a resource file.
	The resource could be a single memory location, a data structure, a file, or
	anything else where mutual exclusion must be enforced so that only one
	thread is allowed to access the resource at a time.

	You declare a critical section for each resource that needs to be protected. 
	This object is the traffic light that allows only one thread at a time 
	into the critical section. 

	Note: On Windows a critical section is not a kernel object and it exist 
	only in the process's memory space. A disadvantage is that there is 
	no way to tell if the thread currently inside a critical section is 
	still alive. In other words, since the critical section is not 
	a kernel object, the kernel does not clean it up if a thread inside 
	the critical section exits or crashes without calling LeaveCriticalSection().
	If you need this functionality, you should use a mutex.
		
	Any time a section of code requires two or more resources, 
	there is a potential for deadlock. It is possible for deadlock situations
	to be quite complex, wherein many threads make up a complex pattern 
	of interdependencies.
	Although there are algorithms to detect and arbitrate deadlock situations, 
	they are quite complex. For most applications, the best policy is to find
	a way to make sure that deadlock will not happen by allocating all the 
	resources you need as a single operation with WaitForMultipleObjects()

	Whether on Win32, Unix, or any other operating system, there is one rule 
	you will hear over and over: 
	Don't lock a resource for a long time.	
	*/



	class critical_section
	{
	public:
		/*! ctor
			Initializes the critical section.
		*/
		critical_section();

		/*!	dtor
			Releases all resources used by an unowned critical section.
		*/
		~critical_section();

		/*!	lock
			Waits for ownership of the critical section.
			The function returns when the calling thread is granted ownership.
			\return The return value is nonzero.
		*/
		int lock();

		/*!	unlock
			Releases ownership of the critical section.
			\return The return value is nonzero.
		*/
		int unlock();		


	private:
		//non-copyable
		critical_section(const critical_section&);
		critical_section& operator=(const critical_section&);

	private:
#ifdef _WIN32
		CRITICAL_SECTION	m_section;
#else
		pthread_mutex_t		m_mtx;
#endif
	};
} // namespace

#endif // __critical_section_hpp__

