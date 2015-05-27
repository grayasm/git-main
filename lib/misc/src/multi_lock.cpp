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
		enum lock_state
		{
			NOT_RUNNING=1,
			NOT_LOCKED,
			LOCKED,
			UNLOCKED
		};
		object_locker(
			misc::sync_base* obj,		// to be locked
			misc::event* ev,			// signal to release the lock
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
				throw misc::exception("cannot destroy object_locker while locked");
		}
		unsigned long run()
		{
			m_state = NOT_LOCKED;
			printf("\n\t\t\tOL wait for %lu", m_msec);
			
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
				
				printf("\n\t\t\tOL locked");
				
				m_ev->lock();		// wait for signal to unlock				
				m_obj->unlock();	// unlock
				
				printf("\n\t\t\tOL unlocked");
				
				m_state = UNLOCKED;				
			}
			else
			{
				printf("\n\t\t\tOL timeout");
			}
			// else TIMEOUT
			return ret; 
		}
		misc::event* get_event()
		{
			return m_ev;
		}
		lock_state get_state() const
		{
			return m_state;
		}
	private:
		misc::sync_base*		m_obj;
		misc::event*			m_ev;
		unsigned long			m_msec; // in milliseconds
		lock_state				m_state;
	};
	//##########################################################################
	multi_lock::multi_lock(sync_base** objects, unsigned long count)
	{
		if(objects == NULL || count == 0)
			throw misc::exception("Invalid argument.");

		printf("\n\t\tmulti_lock(..)");
		
		m_objects = objects;
		m_count = count;
	}

	multi_lock::~multi_lock()
	{
		printf("\n\t\t~multi_lock(..)");
		if(m_locks.size())
			throw misc::exception("cannot destroy multi_lock with "
								  "objects in locked state");
		m_objects = NULL;
		m_count = 0;
	}

	int multi_lock::lock()
	{
		printf("\n\t\tlock()");
		
		if( !m_locks.empty() )
			throw misc::exception("multi_lock error");
		
		// separate the synchronization objects by their type
		type_visitor synctype;		
		misc::vector<sync_base**> events;
		misc::vector<sync_base**> nonevents;
		
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
				throw misc::exception("type not implemented");
		}
		
		printf("\n\t\tlock() events=%lu", events.size());
		printf("\n\t\tlock() non-ev=%lu", nonevents.size());
		
		unsigned long MSEC=50;	// 0.05 sec
		MSEC += (events.size() + nonevents.size()) * 2;
		
		// put all event objects in waiting state
		misc::vector<object_locker*> ev_locks;
		for(size_t i=0; i < events.size(); ++i)
		{
			sync_base** p = events[i];
			ev_locks.push_back(new object_locker(*p, new misc::event(), -1));
			ev_locks[i]->resume();
		}
		
		if(ev_locks.size())
			printf("\n\t\tlock() resumed %lu events", ev_locks.size());
		
		// put all non-event objects in a single array
		misc::vector<object_locker*> nonev_locks;
		for(size_t i=0; i < nonevents.size(); ++i)
		{
			sync_base** p = nonevents[i];
			nonev_locks.push_back(new object_locker(*p, new misc::event(), MSEC));
		}
		
		// lock and unlock until all of them are locked
		bool all_locked = false;
		while( !all_locked )
		{
			// if 1 lock fails, this variable will be reset to false
			all_locked = true;
			
			//1) resume threads for getting the locks
			for(size_t i=0; i < nonev_locks.size(); ++i)
				nonev_locks[i]->resume();
			
			printf("\n\t\tlock() resumed %lu non-events", nonev_locks.size());
			
			msleep(MSEC);
			
			// if one mutex or semaphore is not locked then retry
			for(size_t i=0; i < nonev_locks.size(); ++i)
			{
				object_locker* ol = nonev_locks[i];
				if( ol->get_state() != object_locker::LOCKED ) // failed to lock
				{
					all_locked = false;
					
					printf("\n\t\tnon-event %lu is not locked", i);
					
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
					
					printf("\n\t\t    event %lu is not locked", i);
					
					break;
				}
			}

			// event threads will remain in wait state
			// mutexes and semaphores will be unlocked for retry
			if( !all_locked )
			{
				printf("\n\t\tbailing out");
				
				for(size_t i=0; i < nonev_locks.size(); ++i)
				{
					printf("\n\t\ti=%lu", i);
					object_locker* ol = nonev_locks[i];
					misc::event* ev = ol->get_event();
					
					// avoid dead lock condition
					while( ol->join(0) != 0 )
						ev->setevent();
					
					printf("\n\t\tthread is joined");
				}				
				
				printf("\n\t\tretrying");
			}			
		}
		
		printf("\n\t\tALL LOCKED SUCCESSFULY");
		
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
		printf("\n\t\ttrylock()");
		
		if(milliseconds == (unsigned long)-1)
			return lock();
		
		if( !m_locks.empty() )
			throw misc::exception("multi_lock error");
		
		// separate the synchronization objects by their type
		type_visitor synctype;		
		misc::vector<sync_base**> events;
		misc::vector<sync_base**> nonevents;
		
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
				throw misc::exception("type not implemented");
		}
		
		printf("\n\t\ttrylock() events=%lu", events.size());
		printf("\n\t\ttrylock() non-ev=%lu", nonevents.size());
		
		
		unsigned long MSEC=50;	// 0.05 sec
		MSEC += (events.size() + nonevents.size()) * 2;
		MSEC = misc::min<unsigned long>(MSEC, milliseconds);
				
		// put all event objects in waiting state
		misc::vector<object_locker*> ev_locks;
		for(size_t i=0; i < events.size(); ++i)
		{
			sync_base** p = events[i];
			ev_locks.push_back(new object_locker(*p, new misc::event(), milliseconds));
			ev_locks[i]->resume();
		}
		
		if(ev_locks.size())
			printf("\n\t\ttrylock() resumed %lu events", ev_locks.size());
		
		// put all non-event objects in a single array
		misc::vector<object_locker*> nonev_locks;
		for(size_t i=0; i < nonevents.size(); ++i)
		{
			sync_base** p = nonevents[i];
			nonev_locks.push_back(new object_locker(*p, new misc::event(), MSEC));
		}
		
		// lock and unlock until all of them are locked
		bool all_locked = false;
		unsigned long elapsed=0;
		while( !all_locked && elapsed < milliseconds)
		{
			// if 1 lock fails, this variable will be reset to false
			all_locked = true;
			
			//1) resume threads for getting the locks
			for(size_t i=0; i < nonev_locks.size(); ++i)
				nonev_locks[i]->resume();
			
			printf("\n\t\ttrylock() resumed %lu non-events", nonev_locks.size());
						
			msleep(MSEC);
			elapsed += MSEC;
			
			// if one mutex or semaphore is not locked then retry
			for(size_t i=0; i < nonev_locks.size(); ++i)
			{
				object_locker* ol = nonev_locks[i];
				if( ol->get_state() != object_locker::LOCKED ) // failed to lock
				{
					all_locked = false;
					
					printf("\n\t\tnon-event %lu is not locked", i);
					
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
					
					printf("\n\t\t    event %lu is not locked", i);
					
					break;
				}
			}

			// event threads will remain in wait state
			// mutexes and semaphores will be unlocked for retry
			if( !all_locked )
			{
				printf("\n\t\tbailing out");
				
				for(size_t i=0; i < nonev_locks.size(); ++i)
				{
					printf("\n\t\ti=%lu", i);
					object_locker* ol = nonev_locks[i];
					misc::event* ev = ol->get_event();
					
					// avoid dead lock condition
					while( ol->join(0) != 0 )
						ev->setevent();
					
					printf("\n\t\tthread is joined");
				}				
				
				printf("\n\t\tretrying");
			}			
		}
		
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

		
		if(all_locked)
		{
			printf("\n\t\tALL LOCKED SUCCESSFULY");
			return 0;
		}
		else
		{
			printf("\n\t\tFAILED TO LOCK ALL OBJECTS");
			printf("\n\t\tunlocking to return clean");
			unlock();
			return 1;
		}
	}

	int multi_lock::unlock()
	{
		if(m_locks.empty())
			throw misc::exception("no object to unlock");
		
		for(size_t i=0; i < m_locks.size(); ++i)
		{
			object_locker* ol = m_locks[i];
			misc::event* ev = ol->get_event();
			// avoid dead lock condition
			while( ol->join(0) != 0 )
				ev->setevent();

			delete ev;
			delete ol;
			
			printf("\n\t\t\tunlock() object %lu", i);
		}
		
		m_locks.clear();
		
		return 0;
	}
} // namespace

