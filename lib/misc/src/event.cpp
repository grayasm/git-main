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


#include "event.hpp"
#include "exception.hpp"


#ifdef _WIN32
#else
#include <errno.h>
#endif

namespace misc
{
    event::event()
        : sync_base()
    {
#ifdef _WIN32
        bool bSignaled = false;
        bool bManualReset = false;

        // Creates or opens a named or unnamed event object.
        m_handle = ::CreateEvent(
                NULL, 
                bManualReset,
                bSignaled, 
                "");

        if(m_handle == NULL)
                throw misc::exception("Cannot create the event!");
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
            throw misc::exception("pthread_mutex_init error");

        // Initialize the condition variable.
        error = pthread_cond_init(&m_cond, 0);
        if(error)
            throw misc::exception("pthread_cond_init error");

        pthread_mutexattr_destroy(&attr);
#endif
    }


    event::~event()
    {
#ifdef _WIN32
        ::CloseHandle(m_handle);
        m_handle = NULL;
#else
        /*  The implementation has detected an attempt to destroy the object 
         *  referenced by cond while it is referenced, for example while being
         *  used in a pthread_cond_wait() or pthread_cond_timedwait()
         *  by another thread.
         */
        int error = pthread_cond_destroy(&m_cond);
        if(error)
            throw misc::exception("pthread_cond_destroy error");

        /*  The implementation has detected an attempt to destroy the object 
         *  referenced by mutex while it is locked or referenced 
         *  (for example, while being used in a pthread_cond_wait() or 
         *  pthread_cond_timedwait()) by another thread.
         */
        error = pthread_mutex_destroy(&m_mtx);
        if(error)
            throw misc::exception("pthread_mutex_destroy error");
#endif
    }


    int event::lock()
    {
#ifdef _WIN32
        DWORD dwRet = ::WaitForSingleObject(m_handle, INFINITE);
        // cannot get WAIT_TIMEOUT with INIFINITE
        // cannot get WAIT_ABANDONED (only for Mutexes)		
        if (dwRet == WAIT_OBJECT_0)
            return 0;
        else
            return 1;
#else
        /*  Waiting on a condition variable expects a locked mutex as parameter.
         */
        int error = pthread_mutex_lock(&m_mtx);
        if(error)
            throw misc::exception("pthread_mutex_lock error");

        /*  pthread_cond_wait is used to block on a condition variable. 
         *  It is called with mutex locked by the calling thread or 
         *  undefined behaviour will result.
         */
        error = pthread_cond_wait(&m_cond, &m_mtx);
        if(error)
            throw misc::exception("pthread_cond_wait error");

        /*  pthread_cond_wait returns when condition variable is signaled in
         *  another thread (pthread_cond_signal, pthread_cond_braodcast).
         *  At this point the mutex is locked (kernel), and should be unlocked
         *  to prevent a deadlock when other threads are waiting for the same
         *  condition.
         */
        error = pthread_mutex_unlock(&m_mtx);
        if(error)
            throw misc::exception("pthread_mutex_unlock error");
        
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
            throw misc::exception("pthread_mutex_lock error");


        struct timespec ts;
        if(clock_gettime(CLOCK_REALTIME, &ts) == -1)
            throw misc::exception("clock_gettime error");

        ts.tv_sec += (time_t) (milliseconds / 1000);// seconds
        ts.tv_nsec += (milliseconds % 1000) * 1e6;	// nanoseconds

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
            throw misc::exception("pthread_mutex_unlock error");

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

        throw misc::exception("pthread_cond_timedwait error");
#endif
    }

    int event::unlock()
    {
#ifdef _WIN32
        if( ::SetEvent(m_handle) != 0 )
            return 0;
        
        throw misc::exception("SetEvent error");
#else
        /*  pthread_cond_broadcast unblocks all threads currently blocked on 
         *  the specified condition variable, one at a time, each returning
         *  from the pthread_cond_wait() or pthread_cond_timedwait(),
         *  as the owner of the associated mutex, with the mutex in locked state.
         */
        int error = pthread_cond_broadcast(&m_cond);
        if(error)
            throw misc::exception("pthread_cond_broadcast error");

        return 0;
#endif
    }


    int event::setevent()
    {
        return unlock();
    }	
} // namespace