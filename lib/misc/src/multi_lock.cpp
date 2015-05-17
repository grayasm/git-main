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


#include "multi_lock.hpp"
#include "exception.hpp"
#include "vector.hpp"
#include "thread.hpp"
#include "mutex.hpp"
#include "semaphore.hpp"
#include "event.hpp"
#include "autocritical_section.hpp"
#include "unistd.hpp"	// msleep
#include <stdio.h>		// printf


namespace misc
{
	//##########################################################################
	//! Helper class to get the type of a synchronization object.
	class type_visitor : public misc::sync_visitor
	{
	public:
		type_visitor() { reset(); }
		~type_visitor() {}
		void visit(misc::sync_base&)
		{
			throw misc::exception("Cannot visit sync_base type.");
		}
		void visit(misc::mutex&) 
		{
			reset();
			m_is_mutex = true;
		}
		void visit(misc::semaphore& visit) 
		{
			reset();
			m_is_semaphore = true;
		}
		void visit(misc::event&)
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
	class object_locker : public misc::thread
	{
	public:
		object_locker(
			misc::sync_base* obj,		// to be locked
			misc::event* ev,			// signal to release the lock
			unsigned long milliseconds)	// timeout
		{
			m_obj = obj;
			m_ev = ev;
			m_msec = milliseconds;
			m_locked = false;
		}
		~object_locker() { }
		unsigned long run()
		{
			printf("\n\t\tobject_locker wait for %lu", m_msec);
			int ret = m_obj->trylock(m_msec);
			if(ret == 0) // locked
			{
				set_lock(true);
				printf("\n\t\tobject_locker locked, wait for signal");
				m_ev->lock();
				printf("\n\t\tobject_locker released lock");
			}
			printf("\n\t\tobject_locker ret %d", ret);
				
			return ret;
		}
		void set_lock(bool lock)
		{
			misc::autocritical_section acs(m_cs);
			m_locked = lock;
		}
		bool get_lock()
		{
			misc::autocritical_section acs(m_cs);
			bool ret = m_locked;
			return ret;
		}
		misc::event* get_event()
		{
			return m_ev;
		}		
	private:
		misc::sync_base*		m_obj;
		misc::event*			m_ev;
		unsigned long			m_msec; // 1e3
		// internal
		misc::critical_section	m_cs;
		bool					m_locked;
	};
	//##########################################################################
	multi_lock::multi_lock(sync_base** objects, unsigned long count)
	{
		if(objects == NULL || count == 0)
			throw misc::exception("Invalid argument.");

		m_objects = objects;
		m_count = count;
	}

	multi_lock::~multi_lock()
	{
		m_objects = NULL;
		m_count = 0;
	}

	int multi_lock::lock()
	{
		if( !m_locks.empty() )
			throw misc::exception("multi_lock::lock error");
		
		// separate the synchronization objects by their type
		type_visitor synctype;		
		misc::vector<sync_base**> mutexvec;
		misc::vector<sync_base**> semaphorevec;
		misc::vector<sync_base**> eventvec;
		
		for(unsigned long i=0; i < m_count; ++i)
		{
			sync_base** p = m_objects + i;
			(*p)->accept(synctype);
			
			if( synctype.is_mutex() )
				mutexvec.push_back(p);
			else if( synctype.is_semaphore() )
				semaphorevec.push_back(p);
			else if( synctype.is_event() )
				eventvec.push_back(p);
			else
				throw misc::exception("type not implemented");
		}
		printf("\n\t\tmultilock events: %lu mutex+sem: %lu", 
				eventvec.size(), mutexvec.size() + semaphorevec.size());
		
		const unsigned long NOSEC=500; // 0.5 sec
		// put all events in waiting state
		misc::vector<object_locker*> ev_locks;
		for(size_t i=0; i < eventvec.size(); ++i)
		{
			sync_base** p = eventvec[i];
			ev_locks.push_back(new object_locker(*p, new misc::event(), -1));
			ev_locks[i]->resume();
		}
		
		// put all semaphores and mutexes in a single array
		misc::vector<object_locker*> sm_locks;
		for(size_t i=0; i < semaphorevec.size(); ++i)
		{
			sync_base** p = semaphorevec[i];
			sm_locks.push_back(new object_locker(*p, new misc::event(), NOSEC));
		}
		for(size_t i=0; i < mutexvec.size(); ++i)
		{
			sync_base** p = mutexvec[i];
			sm_locks.push_back(new object_locker(*p, new misc::event(), NOSEC));
		}
		
		// lock and unlock until all of them are locked
		bool all_locked = false;
		while( !all_locked )
		{
			// if 1 lock fails, this variable will be reset to false
			all_locked = true;
			
			//1) resume threads for getting the locks
			for(size_t i=0; i < sm_locks.size(); ++i)
				sm_locks[i]->resume();
			
			msleep(NOSEC);
			
			// 
			for(size_t i=0; i < sm_locks.size(); ++i)
			{
				object_locker* ol = sm_locks[i];
				if( !ol->get_lock() )
				{
					all_locked = false;
					break;
				}
			}
			
			if( !all_locked )
			{
				// bail out and retry
				for(size_t i=0; i < sm_locks.size(); ++i)
				{
					object_locker* ol = sm_locks[i];
					misc::event* ev = ol->get_event();
					ev->setevent();
					ol->join();
				}
			}
		}
		
		
		return 0;
	}

	int multi_lock::trylock(unsigned long milliseconds, bool wait_for_all)
	{
		for(unsigned long i=0; i < m_count; ++i)
		{
			sync_base** p = m_objects + i;
			(*p)->trylock(milliseconds);
		}
		
		return 0;
	}

	int multi_lock::unlock()
	{
		for(unsigned long i=0; i < m_count; ++i)
		{
			sync_base** p = m_objects +i;
			(*p)->unlock();
		}
		return 0;
	}
} // namespace

