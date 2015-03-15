/*
  Copyright (C) 2014 Mihai Vasilian

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


#ifndef __fxcmSessionHelper_hpp__
#define __fxcmSessionHelper_hpp__

#include "autoptr.hpp"
#include "Position.hpp"

namespace fxcm
{
	class SessionHelper
	{
	public:
		//! types
		misc::autoptr<SessionHelper> Ptr;
	
	public:
		SessionHelper();
		~SessionHelper();

		//int GerOriginAmount(const fx::Position& pos);
	private:
		SessionHelper(const SessionHelper&);
		SessionHelper& operator=(const SessionHelper&);
	};
}

#endif // __fxcmSessionHelper_hpp__