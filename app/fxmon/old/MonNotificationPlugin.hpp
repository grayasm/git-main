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

#ifndef __MonNotificationPlugin_hpp__
#define __MonNotificationPlugin_hpp__

#include "autoptr.hpp"


class MonNotificationPlugin
{
public:
	typedef misc::autoptr<MonNotificationPlugin> Ptr;
	MonNotificationPlugin();
	virtual ~MonNotificationPlugin();

	//! Called after all strategies are updated one time.
	virtual void OnUpdate() = 0;
};


#endif // __MonNotificationPlugin_hpp__

