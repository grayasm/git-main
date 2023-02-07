/*
Copyright (C) 2013 Mihai Vasilian
*/


#include "critical_section.hpp"

//libraries
#include "exception.hpp"


namespace sys
{
	critical_section::critical_section()
	{
#ifdef _WIN32
		/*void*/::InitializeCriticalSection(&m_section);
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
			throw stl::exception("pthread_mutex_init error");
		
		pthread_mutexattr_destroy(&attr);
#endif
	}

	critical_section::~critical_section()
	{
#ifdef _WIN32
		/*void*/::DeleteCriticalSection(&m_section);
#else
		/*	It is safe to destroy an initialised mutex that is unlocked. 
		 *	Attempting to destroy a locked mutex results in undefined behaviour.
		 */
		pthread_mutex_unlock(&m_mtx);
		int error = pthread_mutex_destroy(&m_mtx);
		if(error)
			throw stl::exception("pthread_mutex_destroy error");
#endif
	}

	int critical_section::lock()
	{
#ifdef _WIN32
		/*void*/::EnterCriticalSection(&m_section);
		return 0;
#else
		int error = pthread_mutex_lock(&m_mtx);
		if(error)
			throw stl::exception("pthread_mutex_lock error");
		return 0;
#endif
	}

	int critical_section::unlock()
	{
#ifdef _WIN32
		/*void*/::LeaveCriticalSection(&m_section);
		return 0;
#else
		int error = pthread_mutex_unlock(&m_mtx);
		if(error)
			throw stl::exception("pthread_mutex_unlock error");
		return 0;
#endif
	}
} // namespace



