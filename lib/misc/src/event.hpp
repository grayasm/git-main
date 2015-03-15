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


#ifndef __event_hpp__
#define __event_hpp__



#include "sync_base.hpp"


namespace misc
{	
	class event : public sync_base
	{
	public:
		event(bool bSignaled = false, bool bManualReset = false,
				const char_t* name = "");

		~event();

		/*!	lock
			The function will return only when the mutex is signaled.
			\return If the state of the mutex is signaled the
			return value is nonzero.
		*/
		int lock();

		/*!	trylock
			Waits until the mutex is in the signaled state or the time-out 
			interval elapses.
		*/
		int trylock(unsigned long milliseconds = 0);		

		/*!	unlock
			Releases ownership of the mutex.
			\return If the function succeeds, the return value is nonzero.
		*/
		int unlock();

		/*! setevent
			Sets the state of the event to signaled, releasing any waiting 
			threads.
			\return If the function succeeds, the return value is nonzero.
		*/
		int setevent();

		/*!	pulseevent
			Sets the state of the event to signaled (available), 
			releases any waiting threads, 
			and resets it to nonsignaled (unavailable) automatically.
			\return If the function succeeds, the return value is nonzero.
		*/
		int pulseevent();


		/*!	resetevent
			Sets the state of the event to nonsignaled until explicitly
			set to signaled by the SetEvent member function.
			\return If the function succeeds, the return value is nonzero.
		*/
		int resetevent();

	private:		
		event(const event& tc);
		event& operator=(const event& tc);	
	};

}  // namespace



#endif // __event_hpp__


