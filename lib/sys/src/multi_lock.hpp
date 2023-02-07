/*
Copyright (C) 2013 Mihai Vasilian
*/


#ifndef __multi_lock_hpp__
#define __multi_lock_hpp__


#include "sync_base.hpp"
#include "vector.hpp"



namespace sys
{
	class object_locker;

	//! It will attempt to lock all passed objects, avoiding as much as possible
	//! a dead-lock.
	class multi_lock
	{
	public:
		multi_lock(sync_base** objects, unsigned long count);
		
		~multi_lock();

		//! Locks all objects and returns 0 or otherwise throws stl::exception.
		int lock();

		/*! Locks all objects and returns 0 or 1 if timeout.
		 *!	milliseconds possible values are: any > 0 or -1 for INFINITE
		 */
		int trylock(unsigned long milliseconds);

		int unlock();

	private:
		//! non-copyable
		multi_lock(const multi_lock&);
		multi_lock& operator=(const multi_lock&);
		
	protected:
		sync_base**						m_objects;
		unsigned long					m_count;
		stl::vector<object_locker*>	m_locks;
	};
}  // namespace


#endif // __multi_lock_hpp__
