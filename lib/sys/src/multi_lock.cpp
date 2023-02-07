/*
Copyright (C) 2013 Mihai Vasilian
*/


#include "multi_lock.hpp"
#include "exception.hpp"
#include "vector.hpp"
#include "thread.hpp"
#include "mutex.hpp"
#include "semaphore.hpp"
#include "event.hpp"
#include "unistd.hpp"	// msleep


namespace sys
{
	//##########################################################################
	//! Helper class to get the type of a synchronization object.
	class type_visitor : public sys::sync_visitor
	{
	public:
		type_visitor() { reset(); }
		~type_visitor() {}
		void visit(sys::sync_base&)
		{
			throw stl::exception("Cannot visit sync_base type.");
		}
		void visit(sys::mutex&) 
		{
			reset();
			m_is_mutex = true;
		}
		void visit(sys::semaphore& visit) 
		{
			reset();
			m_is_semaphore = true;
		}
		void visit(sys::event&)
		{
			reset();
			m_is_event = true;
		}
		bool is_mutex() const { return m_is_mutex; }
		bool is_semaphore() const { return m_is_semaphore; }
		bool is_event() const { return m_is_event; }
	private:
		void reset()
		{
			m_is_mutex = false;
			m_is_semaphore = false;
			m_is_event = false;
		}		
	private:
		bool m_is_mutex;
		bool m_is_semaphore;
		bool m_is_event;
	};
	//##########################################################################
	//! Helper class to get a lock on the specified object.
	class object_locker : public sys::thread
	{
	public:
		enum lock_state
		{
			NOT_RUNNING=1,
			NOT_LOCKED,
			LOCKED,
			UNLOCKED
		};
		object_locker(
			sys::sync_base* obj,		// to be locked
			sys::event* ev,			// signal to release the lock
			unsigned long milliseconds)	// timeout
		{
			m_obj = obj;
			m_ev = ev;
			m_msec = milliseconds;
			m_state = NOT_RUNNING;
		}
		~object_locker() 
		{
			if(m_state == LOCKED)
				throw stl::exception("cannot destroy object_locker while locked");
		}
		unsigned long run()
		{
			m_state = NOT_LOCKED;
			int ret = 0;
			if(m_msec == (unsigned long)-1) // INFINITE
			{
				ret = m_obj->lock();
			}
			else
			{
				ret = m_obj->trylock(m_msec);
			}
			
			if(ret == 0) // locked
			{
				m_state = LOCKED;				
				m_ev->lock();		// wait for signal to unlock				
				m_obj->unlock();	// unlock				
				m_state = UNLOCKED;				
			}
			// else TIMEOUT
			return ret; 
		}
		sys::event* get_event()
		{
			return m_ev;
		}
		lock_state get_state() const
		{
			return m_state;
		}
	private:
		sys::sync_base*		m_obj;
		sys::event*			m_ev;
		unsigned long			m_msec;
		lock_state				m_state;
	};
	//##########################################################################
	multi_lock::multi_lock(sync_base** objects, unsigned long count)
	{
		if(objects == NULL || count == 0)
			throw stl::exception("multi_lock: Invalid argument.");
		m_objects = objects;
		m_count = count;
	}

	multi_lock::~multi_lock()
	{
		if(m_locks.size())
			throw stl::exception("~multi_lock: there are objects unlocked");
		m_objects = NULL;
		m_count = 0;
	}

	int multi_lock::lock()
	{
		if( !m_locks.empty() )
			throw stl::exception("multi_lock error");
		
		// separate the synchronization objects by their type
		type_visitor synctype;		
		stl::vector<sync_base**> events;
		stl::vector<sync_base**> nonevents;
		
		for(unsigned long i=0; i < m_count; ++i)
		{
			sync_base** p = m_objects + i;
			(*p)->accept(synctype);
			
			if( synctype.is_mutex() )
				nonevents.push_back(p);
			else if( synctype.is_semaphore() )
				nonevents.push_back(p);
			else if( synctype.is_event() )
				events.push_back(p);
			else
				throw stl::exception("sync_base type not implemented");
		}
		
		
		unsigned long MSEC=10;	// 0.01 sec
		MSEC += (events.size() + nonevents.size()) * 2;	// for scheduling
		
		// put all event objects in waiting state
		stl::vector<object_locker*> ev_locks;
		for(size_t i=0; i < events.size(); ++i)
		{
			sync_base** p = events[i];
			ev_locks.push_back(new object_locker(*p, new sys::event(), -1));
			ev_locks[i]->resume();
		}
		
		// put all non-event objects in a single array
		stl::vector<object_locker*> nonev_locks;
		for(size_t i=0; i < nonevents.size(); ++i)
		{
			sync_base** p = nonevents[i];
			nonev_locks.push_back(new object_locker(*p, new sys::event(), MSEC));
		}
		
		
		// repeat locking in a loop until all succeed
		bool all_locked = false;
		while( !all_locked )
		{
			// if 1 lock fails, this variable will be reset to false
			all_locked = true;
			
			//resume threads for getting the locks
			for(size_t i=0; i < nonev_locks.size(); ++i)
				nonev_locks[i]->resume();
			
			msleep(MSEC);
			
			// if one mutex or semaphore is not locked then retry
			for(size_t i=0; i < nonev_locks.size(); ++i)
			{
				object_locker* ol = nonev_locks[i];
				if( ol->get_state() != object_locker::LOCKED ) // failed to lock
				{
					all_locked = false;
					break;
				}
			}
			
			// if one event is not locked then retry
			for(size_t i=0; i < ev_locks.size() && all_locked; ++i)
			{
				object_locker* ol = ev_locks[i];
				if( ol->get_state() != object_locker::LOCKED ) // failed to lock
				{
					all_locked = false;
					break;
				}
			}

			// event threads will remain in wait state
			// mutexes and semaphores will be unlocked for retry
			if( !all_locked )
			{
				for(size_t i=0; i < nonev_locks.size(); ++i)
				{
					object_locker* ol = nonev_locks[i];
					sys::event* ev = ol->get_event();

					// avoid dead lock condition
					while( ol->join(0) != 0 )
						ev->setevent();
				}
			}
		}
		
		// LOCK ALL SUCCEEDED.
		// save all objects to be found by unlock method
		for(size_t i=0; i < ev_locks.size(); ++i)
		{
			object_locker* ol = ev_locks[i];
			m_locks.push_back(ol);
		}
		for(size_t i=0; i < nonev_locks.size(); ++i)
		{
			object_locker* ol = nonev_locks[i];
			m_locks.push_back(ol);
		}
		
		return 0;
	}

	int multi_lock::trylock(unsigned long milliseconds)
	{
		if(milliseconds == (unsigned long)-1)
			return lock();
		
		if( !m_locks.empty() )
			throw stl::exception("multi_lock error");
		
		// separate the synchronization objects by their type
		type_visitor synctype;		
		stl::vector<sync_base**> events;
		stl::vector<sync_base**> nonevents;
		
		for(unsigned long i=0; i < m_count; ++i)
		{
			sync_base** p = m_objects + i;
			(*p)->accept(synctype);
			
			if( synctype.is_mutex() )
				nonevents.push_back(p);
			else if( synctype.is_semaphore() )
				nonevents.push_back(p);
			else if( synctype.is_event() )
				events.push_back(p);
			else
				throw stl::exception("type not implemented");
		}
		
		unsigned long MSEC=10;	// 0.01 sec
		MSEC += (events.size() + nonevents.size()) * 2;
		MSEC = stl::min<unsigned long>(MSEC, milliseconds);
				
		// put all event objects in waiting state
		stl::vector<object_locker*> ev_locks;
		for(size_t i=0; i < events.size(); ++i)
		{
			sync_base** p = events[i];
			ev_locks.push_back(new object_locker(*p, new sys::event(), milliseconds));
			ev_locks[i]->resume();
		}
		
		// put all non-event objects in a single array
		stl::vector<object_locker*> nonev_locks;
		for(size_t i=0; i < nonevents.size(); ++i)
		{
			sync_base** p = nonevents[i];
			nonev_locks.push_back(new object_locker(*p, new sys::event(), MSEC));
		}
		
		// repeat locking in a loop until all succeed or time expires.
		bool all_locked = false;
		unsigned long elapsed=0;
		while( !all_locked && elapsed < milliseconds)
		{
			// if 1 lock fails, this variable will be reset to false
			all_locked = true;
			
			// resume threads for getting the locks
			for(size_t i=0; i < nonev_locks.size(); ++i)
				nonev_locks[i]->resume();
			
			msleep(MSEC);
			elapsed += MSEC;
			
			// if one mutex or semaphore is not locked then retry
			for(size_t i=0; i < nonev_locks.size(); ++i)
			{
				object_locker* ol = nonev_locks[i];
				if( ol->get_state() != object_locker::LOCKED ) // failed to lock
				{
					all_locked = false;
					break;
				}
			}
			
			// if one event is not locked then retry
			for(size_t i=0; i < ev_locks.size() && all_locked; ++i)
			{
				object_locker* ol = ev_locks[i];
				if( ol->get_state() != object_locker::LOCKED ) // failed to lock
				{
					all_locked = false;
					break;
				}
			}

			// event threads will remain in wait state
			// mutexes and semaphores will be unlocked for retry
			if( !all_locked )
			{
				for(size_t i=0; i < nonev_locks.size(); ++i)
				{
					object_locker* ol = nonev_locks[i];
					sys::event* ev = ol->get_event();
					
					// avoid dead lock condition
					while( ol->join(0) != 0 )
						ev->setevent();
				}
			}			
		}
		
		if(all_locked)
		{
			// save all objects to be found by unlock method
			for(size_t i=0; i < ev_locks.size(); ++i)
			{
				object_locker* ol = ev_locks[i];
				m_locks.push_back(ol);
			}
			for(size_t i=0; i < nonev_locks.size(); ++i)
			{
				object_locker* ol = nonev_locks[i];
				m_locks.push_back(ol);
			}
			return 0;
		}
		else
		{
			// delete event lockers
			for(size_t i=0; i < ev_locks.size(); ++i)
			{
				object_locker* ol = ev_locks[i];
				sys::event* ev = ol->get_event();
				// avoid dead lock condition
				while( ol->join(0) != 0 )
					ev->setevent();

				delete ev;
				delete ol;				
			}
			// delete non-event lockers
			for(size_t i=0; i < nonev_locks.size(); ++i)
			{
				object_locker* ol = nonev_locks[i];
				sys::event* ev = ol->get_event();
				// not running so no deadlock possible.
				delete ev;
				delete ol;
			}
			return 1;
		}
	}

	int multi_lock::unlock()
	{
		if(m_locks.empty())
			throw stl::exception("no object to unlock");
		
		for(size_t i=0; i < m_locks.size(); ++i)
		{
			object_locker* ol = m_locks[i];
			sys::event* ev = ol->get_event();
			// avoid dead lock condition
			while( ol->join(0) != 0 )
				ev->setevent();

			delete ev;
			delete ol;
		}
		
		m_locks.clear();

		return 0;
	}
} // namespace

