/*
Copyright (C) 2013 Mihai Vasilian
*/

#ifndef __single_lock_hpp__
#define __single_lock_hpp__

#include "sync_base.hpp"



namespace sys
{
	class single_lock
	{		
	public:
		//! Creates a wrapper around a valid synchronization object.
		single_lock(sync_base* object);

		//!	Destructor
		~single_lock();
		
		//! Locks the object and returns 0 if successful or otherwise throws
		//!	stl::exception.
		int lock();

		//! Locks the object and returns 0 if successful or 1 if timeout.
		int trylock(unsigned long milliseconds);

		//! Unlocks the object and returns 0 or otherwise throws stl::exception.
		int unlock();		
		
	private:
		// non-copyable
		single_lock(const single_lock&);
		single_lock& operator=(const single_lock&);
		
	protected:
		sync_base* m_object;
	};
}  // namespace



#endif // __single_lock_hpp__
