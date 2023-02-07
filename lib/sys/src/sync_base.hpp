/*
Copyright (C) 2013 Mihai Vasilian
*/


#ifndef __sync_base_hpp__
#define __sync_base_hpp__


#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif




namespace sys
{	
	//! Forward declarations
	class sync_base;
	class mutex;
	class semaphore;
	class event;
	
	//! Visitor class.
	class sync_visitor
	{
	public:
		sync_visitor();
		virtual ~sync_visitor();
		virtual void visit(sys::sync_base& visit) = 0;
		virtual void visit(sys::mutex& visit) = 0;
		virtual void visit(sys::semaphore& visit) = 0;
		virtual void visit(sys::event& visit) = 0;
	};
	
	/*!	Base class for (some) synchronization objects.
	 *! All types deriving from this class have a corresponding visit function
	 *! in the sync_visitor.
	 */
	class sync_base
	{		
	public:
		//! Constructor
		sync_base();

		//! Destructor
		virtual ~sync_base();

		//! Locks the object and returns 0 or otherwise throws stl::exception.
		virtual int lock() = 0;
		
		/*! Locks the object and returns 0 or 1 if timeout.
		 *!	milliseconds possible values are: any > 0 or -1 for INFINITE
		 */
		virtual int trylock(unsigned long milliseconds = 0) = 0;
		
		//! Unlocks the object and returns 0 or otherwise throws stl::exception.
		virtual int unlock() = 0;
		
		//! Accepts a visitor
		virtual void accept(sync_visitor& visitor) = 0;
		

	private:
		//! non-copyable
		sync_base(const sync_base&);
		sync_base& operator=(const sync_base&);
		
		// friend class multi_lock;

	protected:
#ifdef _WIN32
		HANDLE			m_handle;
#else
#endif

	private:
	};
} // namespace



#endif // __sync_base_hpp__
