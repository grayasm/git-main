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


#ifndef __semaphore_hpp__
#define __semaphore_hpp__


#include "sync_base.hpp"



namespace misc
{
	class semaphore : public sync_base
	{
	public:
		/*!	semaphore
			\param available the initial count for the semaphore.
			This value must be greater than or equal to zero and less than 
			or equal to maxallowed. The state of a semaphore is signaled 
			when its count is greater than zero and non-signaled when it is zero.
			The count is decreased by one whenever a lock function releases
			a thread that was waiting for the semaphore.
			The count is increased by one by calling the unlock function.
			\param maxallowed the maximum count for the semaphore object.
			This value must be greater than zero.
			\param name the name of the semaphore. It is limited to MAX_PATH
			and name comparison is case sensitive.
		*/
		semaphore(long available, long maxallowed, const char_t* name="");

		/*!	destroys (releases) the semaphore. No threads should be waiting
			on the semaphore if its destruction is to succeed.
		*/
		~semaphore();		
		
		/*!	lock
			The function will return only when the semaphore is signaled.
			\return If the state of the specified object is signaled the
			return value is nonzero.
		*/
		int lock();

		/*!	trylock
			Waits until the semaphore is in the signaled state or the time-out 
			interval elapses.
		*/
		int trylock(unsigned long milliseconds = 0);		

		/*!	unlock
			Increments the count of the semaphore by 1.
			\return If the function succeeds, the return value is nonzero.
		*/
		int unlock();

	private:
		//non-copyable
		semaphore(const semaphore& tc);
		semaphore& operator=(const semaphore& tc);		
	};
} // namespace


#endif // __semaphore_hpp__


