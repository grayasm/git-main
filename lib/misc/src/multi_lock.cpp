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


namespace misc
{
//
//	multi_lock::multi_lock(sync_base* objects[], unsigned long objcount, bool lockitnow)
//	{
//		/*	Objects cannot be copied.
//			If they are not persistent during the life of this instance we will
//			access invalid memory addresses.
//		*/
//		if(objects == NULL || objcount == 0 || objcount > MAXIMUM_WAIT_OBJECTS)
//			throw misc::exception("Invalid argument.");
//
//		m_objects = (sync_base**)::calloc(objcount, sizeof(sync_base*));
//		if(m_objects == NULL)
//			throw misc::exception("Cannot allocate memory.");
//
//		for(unsigned long i = 0; i < objcount; ++i)
//		{
//			m_objects[i] = objects[i];
//		}
//		m_count = objcount;
//
//		if(lockitnow)
//			lock();
//	}
//
//	multi_lock::~multi_lock()
//	{
//		free(m_objects);
//		m_objects = NULL;
//		m_count = 0;
//	}
//
//	int multi_lock::lock()
//	{
//		/* lock all objects */
//		DWORD rc;
//		HANDLE* handles = (HANDLE*)::malloc(m_count * sizeof(HANDLE));
//		if(handles == NULL)
//			throw misc::exception("Cannot allocate memory.");
//
//		for(size_t i = 0; i < m_count; ++i)
//		{
//			handles[i] = m_objects[i]->m_handle;
//		}
//
//		// Wait for ALL with INIFINITE timeout.
//		rc = ::WaitForMultipleObjects(m_count, handles, TRUE, INFINITE);
//				
//		free(handles);
//		
//		return (rc >= WAIT_OBJECT_0 && rc < m_count);
//	}
//
//	int multi_lock::trylock(unsigned long milliseconds, bool wait_for_all)
//	{
//		/* trylock all objects */
//		DWORD rc;
//		HANDLE* handles = (HANDLE*)::malloc(m_count * sizeof(HANDLE));
//		if(handles == NULL)
//			throw misc::exception("Cannot allocate memory.");
//
//		for(size_t i = 0; i < m_count; ++i)
//		{
//			handles[i] = m_objects[i]->m_handle;
//		}
//
//		// Wait for ANY/ALL with specified timeout.
//		rc = ::WaitForMultipleObjects(m_count, handles, wait_for_all, milliseconds);		
//		
//		free(handles);
//
//		/* The function succeeded if the condition is met:
//			- any/all objects are signaled
//			- any/all objects are mutexes and are abandoned -> calling thread
//				gets the ownership of those objects.
//		*/
//		return (rc >= WAIT_OBJECT_0 && rc < WAIT_OBJECT_0 + m_count) ||
//			(rc >= WAIT_ABANDONED_0 && rc < WAIT_ABANDONED_0 + m_count);
//
//		/* Condition is not satisfied for WAIT_TIMEOUT or WAIT_FAILED. */
//	}
//
//	int multi_lock::unlock()
//	{
//		int ret = 1;
//		for(size_t i = 0; i < m_count; ++i)
//			if( !m_objects[i]->unlock() )
//				ret = 0;
//		return ret;
//	}
}; // namespace

