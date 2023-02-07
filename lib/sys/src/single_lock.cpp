/*
Copyright (C) 2013 Mihai Vasilian
*/


#include "single_lock.hpp"
#include "exception.hpp"

namespace sys
{
	single_lock::single_lock(sys::sync_base* object)
	{		
		if(object == NULL)
			throw stl::exception("single_lock invalid parameter");
		m_object = object;
	}

	single_lock::~single_lock()
	{
		// *this has no ownership of m_object.
	}

	int single_lock::lock()
	{
		return m_object->lock();
	}

	int single_lock::trylock(unsigned long milliseconds)
	{
		return m_object->trylock(milliseconds);
	}

	int single_lock::unlock()
	{
		return m_object->unlock();
	}

} // namespace