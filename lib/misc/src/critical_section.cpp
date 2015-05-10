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


#include "critical_section.hpp"

//libraries
#include "exception.hpp"


namespace misc
{
	critical_section::critical_section()
	{
#ifdef _WIN32
		::InitializeCriticalSection(&m_section);
#else
		pthread_mutexattr_t attr;
		pthread_mutexattr_init(&attr);
		/*	PTHREAD_MUTEX_ERRORCHECK:
		 *	This type of mutex provides error checking. 
		 *	A thread attempting to relock this mutex without first unlocking it
		 *	will return with an error.
		 *	A thread attempting to unlock a mutex which another thread has 
		 *	locked will return with an error. 
		 *	A thread attempting to unlock an unlocked mutex will return with 
		 *	an error.
		 */
		pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);
		/*	PTHREAD_PROCESS_PRIVATE:
		 *	The mutex will only be operated upon by threads created within 
		 *	the same process as the thread that initialised the mutex.
		 */
		pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_PRIVATE);
		
		int error = pthread_mutex_init(&m_mtx, &attr); // initialized and unlocked
		if(error)
			throw misc::exception("pthread_mutex_init error");
		
		pthread_mutexattr_destroy(&attr);
#endif
	}

	critical_section::~critical_section()
	{
#ifdef _WIN32
		::DeleteCriticalSection(&m_section);
#else
		/*	It is safe to destroy an initialised mutex that is unlocked. 
		 *	Attempting to destroy a locked mutex results in undefined behaviour.
		 */
		pthread_mutex_unlock(&m_mtx);
		int error = pthread_mutex_destroy(&m_mtx);
		if(error)
			throw misc::exception("pthread_mutex_destroy error");
#endif
	}

	int critical_section::lock()
	{
#ifdef _WIN32
		::EnterCriticalSection(&m_section);
		return 0;
#else
		int error = pthread_mutex_lock(&m_mtx);
		if(error)
			throw misc::exception("pthread_mutex_lock error");
		return 0;
#endif
	}

	int critical_section::unlock()
	{
#ifdef _WIN32
		::LeaveCriticalSection(&m_section);
		return 0;
#else
		int error = pthread_mutex_unlock(&m_mtx);
		if(error)
			throw misc::exception("pthread_mutex_unlock error");
		return 0;
#endif
	}
} // namespace



