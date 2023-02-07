/*
Copyright (C) 2013 Mihai Vasilian
*/


#include "event.hpp"
#include "exception.hpp"
#include "unistd.hpp"
#include "string.hpp"


#ifdef _WIN32
#else
#include <errno.h>
#endif

namespace sys
{
    event::event()
        : sync_base()
    {
#ifdef _WIN32
		/*	Create an event that:
			(1) use manual reset and call ResetEvent after SetEvent (see unlock)
				because with automatic ResetEvent (bManualReset=false)
					- PulseEvent does not wake up all waiting threads
					- SetEvent will wake only 1 thread out of all waiting
			(2) not-signaled (unlocked) initially
			(3) not-named, not shared with other processes.
		*/
		bool bManualReset = true;
		bool bSignaled = false;        
        m_handle = ::CreateEvent(
                NULL, 
                bManualReset,
                bSignaled, 
                U(""));

        if(m_handle == NULL)
                throw stl::exception("Cannot create the event!");
#else
        int error = 0;
        pthread_mutexattr_t attr;
        pthread_mutexattr_init(&attr);
        /*  PTHREAD_MUTEX_ERRORCHECK
         *  A thread attempting to:
         *  (1) relock this mutex without first unlocking it will return with an error. 
         *  (2) unlock a mutex which another thread has locked will return with an error. 
         *  (3) unlock an unlocked mutex will return with an error.
         */
        pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);

        // Initialize the mutex associated to the condition variable.
        error = pthread_mutex_init(&m_mtx, &attr);
        if(error)
            throw stl::exception("pthread_mutex_init error");

        // Initialize the condition variable.
        error = pthread_cond_init(&m_cond, 0);
        if(error)
            throw stl::exception("pthread_cond_init error");

        pthread_mutexattr_destroy(&attr);
#endif
    }


    event::~event()
    {
#ifdef _WIN32
		if( ::CloseHandle(m_handle) == 0 )
			throw stl::exception("CloseHandle error");
		m_handle = NULL;
#else
        /*  The implementation has detected an attempt to destroy the object 
         *  referenced by cond while it is referenced, for example while being
         *  used in a pthread_cond_wait() or pthread_cond_timedwait()
         *  by another thread.
         */
        int error = pthread_cond_destroy(&m_cond);
        if(error)
            throw stl::exception("pthread_cond_destroy error");

        /*  The implementation has detected an attempt to destroy the object 
         *  referenced by mutex while it is locked or referenced 
         *  (for example, while being used in a pthread_cond_wait() or 
         *  pthread_cond_timedwait()) by another thread.
         */
        error = pthread_mutex_destroy(&m_mtx);
        if(error)
            throw stl::exception("pthread_mutex_destroy error");
#endif
    }


    int event::lock()
    {
#ifdef _WIN32
        DWORD dwRet = ::WaitForSingleObject(m_handle, INFINITE);
		// cannot get WAIT_TIMEOUT with INIFINITE
		// cannot get WAIT_ABANDONED (only for Mutexes)		
		if(dwRet != WAIT_OBJECT_0) //WAIT_FAILED
			throw stl::exception("WaitForSingleObject error");
		return 0;
#else
        /*  Waiting on a condition variable expects a locked mutex as parameter.
         */
        int error = pthread_mutex_lock(&m_mtx);
        if(error)
            throw stl::exception("pthread_mutex_lock error");


        /*  pthread_cond_wait is used to block on a condition variable. 
         *  It is called with mutex locked by the calling thread or 
         *  undefined behaviour will result.
         */
        error = pthread_cond_wait(&m_cond, &m_mtx);
        if(error)
            throw stl::exception("pthread_cond_wait error");
		
        /*  pthread_cond_wait returns when condition variable is signaled in
         *  another thread (pthread_cond_signal, pthread_cond_braodcast).
         *  At this point the mutex is locked (kernel), and should be unlocked
         *  to prevent a deadlock when other threads are waiting for the same
         *  condition.
         */
        error = pthread_mutex_unlock(&m_mtx);
        if(error)
            throw stl::exception("pthread_mutex_unlock error");
        
        return 0;
    #endif
    }

    int event::trylock(unsigned long milliseconds)
    {
#ifdef _WIN32
        DWORD dwRet = ::WaitForSingleObject(m_handle, milliseconds);
        // cannot get WAIT_ABANDONED (only for Mutexes)		
        if (dwRet == WAIT_OBJECT_0)
            return 0;
        else
            return 1; // WAIT_TIMEOUT
#else
        /*  Waiting on a condition variable expects a locked mutex 
         *  as parameter.
         */
        int mtx_error = pthread_mutex_lock(&m_mtx);
        if(mtx_error)
            throw stl::exception("pthread_mutex_lock error");
		
		
        struct timespec ts;
        if(clock_gettime(CLOCK_REALTIME, &ts) == -1)
            throw stl::exception("clock_gettime error");

        ts.tv_sec += (time_t) (milliseconds / 1000);// seconds
        ts.tv_nsec += (milliseconds % 1000) * 1e6;	// nanoseconds
		if(ts.tv_nsec >= 1e9)
		{
			ts.tv_sec += 1;
			ts.tv_nsec -= 1e9;
		}

        /* pthread_cond_timedwait is used to block on a condition variable. 
         * It is called with mutex locked by the calling thread or 
         * undefined behaviour will result.
         */
        int cond_error = pthread_cond_timedwait(&m_cond, &m_mtx, &ts);
		
        /*  Unlock independent of condition signal.
         *  Consecutive attempt to trylock will also attempt to lock the mutex,
         *  and this will be an error.
         */
        mtx_error = pthread_mutex_unlock(&m_mtx);
        if(mtx_error)
            throw stl::exception("pthread_mutex_unlock error");

        if(cond_error == 0)
        {
            /*  pthread_cond_timedwait returned due to condition variable 
             *  signaled in another thread (pthread_cond_signal, pthread_cond_braodcast).
             */
            return 0;
        }

        // The time specified by ts has passed.
        if(cond_error == ETIMEDOUT)
        {
            return 1;
        }			

        throw stl::exception("pthread_cond_timedwait error");
#endif
    }

    int event::unlock()
    {
#ifdef _WIN32
		/*	The state of a manual-reset event object remains signaled until 
			it is set explicitly to the nonsignaled state by the ResetEvent function.
			Any number of waiting threads, or threads that subsequently begin
			wait operations for the specified event object by calling one of the
			wait functions, can be released while the object's state is signaled.
		*/
        if( ::SetEvent(m_handle) == 0 )
			throw stl::exception("SetEvent error");

		// Hopefully no idling is needed here.
		// Tested with 600 threads waiting at the same time.
		if( ::ResetEvent(m_handle) == 0 )
			throw stl::exception("ResetEvent error");
		return 0;
#else
		/*	Lock the associated mutex. */
		int error = pthread_mutex_lock(&m_mtx);
		if(error)
			throw stl::exception("pthread_mutex_lock error");

		/*  pthread_cond_broadcast unblocks all threads currently blocked on 
		 *  the specified condition variable, one at a time, each returning
		 *  from the pthread_cond_wait() or pthread_cond_timedwait(),
		 *  as the owner of the associated mutex, with the mutex in locked state.
		 */
		error = pthread_cond_broadcast(&m_cond);
		if(error)
			throw stl::exception("pthread_cond_broadcast error");

		/*	To release the signal we need to unlock the associated mutex. */
		error = pthread_mutex_unlock(&m_mtx);
		if(error)
			throw stl::exception("pthread_mutex_unlock error");

        return 0;
#endif
    }
	
	void event::accept(sync_visitor& visitor)
	{
		visitor.visit(*this);
	}

    int event::setevent()
    {
        return unlock();
    }
} // namespace