/*
Copyright (C) 2013 Mihai Vasilian
*/


#ifndef __semaphore_hpp__
#define __semaphore_hpp__


#include "sync_base.hpp"

#ifdef _WIN32
#else
#include <semaphore.h>
#endif



namespace sys
{
	/*
	 *	Locking a semaphore sem(1) 2 times from the same thread will result in
	 *	deadlock.
	 */
	class semaphore : public sync_base
	{
	public:
		//! Semaphore supports maxlocks (>0) locks.
		semaphore(unsigned int maxlocks);
		
		//! Semaphore resource is released back to OS.
		~semaphore();		
		
		//! --- vtable begin ---
		//! Aquire a lock on the semaphore and returns 0 or 1 if interrupted by signal.
		int lock();
		
		/*! Aquire a lock on the semaphore and returns 0 or 1 if timeout.
		 *! milliseconds possible values are: any > 0 or -1 for INFINITE
		 */
		int trylock(unsigned long milliseconds = 0);
		
		//! Unlock a previous lock on the semaphore and returns 0 or throw otherwise.
		int unlock();
		
		//! Accepts a visitor
		void accept(sync_visitor& visitor);
		//! --- vtable end ---

	private:
		//non-copyable
		semaphore(const semaphore& tc);
		semaphore& operator=(const semaphore& tc);

#ifdef _WIN32
#else
		sem_t m_sem;
#endif
	};
} // namespace


#endif // __semaphore_hpp__


