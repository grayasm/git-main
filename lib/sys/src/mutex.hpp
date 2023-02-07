/*
Copyright (C) 2013 Mihai Vasilian
*/


#ifndef __mutex_hpp__
#define __mutex_hpp__


#include "sync_base.hpp"

#ifdef _WIN32
#else
#include <pthread.h>
#endif


namespace sys
{
	/*	Win32: A mutex is used to do many of the same things as a critical section
	 *	but it sacrifices speed for increased flexibility. As you may have guessed
	 *	mutex stands for MUTual EXclusion.
	 *	Only one thread at a time is allowed to own a mutex, just as only one 
	 *	thread at a time can enter a critical section. 
	 *	Although mutexes and critical sections do the same thing, there are some
	 *	differences in how they operate:
	 *	- It takes almost 100 times longer to lock an unowned mutex than it does
	 *    to lock an unowned critical section because the critical section can 
	 *    be done in user mode without involving the kernel.
	 *  - Mutexes can be used between processes. Critical sections can only be
	 *    used within the same process.
	 *  - You can specify a timeout when waiting on a mutex, but not a critical
	 *    section.
	 *  - Reentrant Mutex: the same thread can acquire the lock multiple times.
	 *    However, the lock must be released the same number of times or else 
	 *    other threads will be unable to acquire the lock.
	 * 
	 *	Pthreads (linux): Mutex variables are one of the primary means of
	 *	implementing thread synchronization and for protecting shared data
	 *	when multiple writes occur.
	 *	A mutex variable acts like a "lock" protecting access to a shared data
	 *	resource. The basic concept of a mutex as used in Pthreads is that only
	 *	one thread can lock (or own) a mutex variable at any given time.
	 *	Thus, even if several threads try to lock a mutex only one thread will
	 *	be successful. No other thread can own that mutex until the owning 
	 *	thread unlocks that mutex. Mutexes can be used to prevent "race"
	 *	conditions. 
	 * 
	 *	The common ground is to use:
	 *	- a recursive mutex
	 *  - lock is not interrupted by signals
	 *  - not shared between processes
	*/

	class mutex : public sync_base
	{
	public:
		//! Creates an unlocked mutex.
		mutex();
		
		//! Destructor
		~mutex();

		//! --- vtable begin ---
		//! Locks the mutex and returns 0 or otherwise throws stl::exception.
		int lock();

		/*! Locks the mutex and returns 0 or 1 if timeout.
		 *!	milliseconds possible values are: any > 0 or -1 for INFINITE
		 */
		int trylock(unsigned long milliseconds = 0);

		//! Unlocks the mutex and returns 0 or otherwise throws stl::exception.
		int unlock();
		
		//! Accepts a visitor
		void accept(sync_visitor& visitor);
		//! --- vtable end ---

	private:
		//non-copyable
		mutex(const mutex& tc);
		mutex& operator=(const mutex& tc);	
		
#ifdef _WIN32
#else
		pthread_mutex_t m_mtx;
#endif
	};
}  // namespace



#endif // __mutex_hpp__
