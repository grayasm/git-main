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

#ifndef __MonQuoteUpdateTimeoutPlugin_hpp__
#define __MonQuoteUpdateTimeoutPlugin_hpp__



#include "MonNotificationPlugin.hpp"
#include "autoptr.hpp"


class MonQuoteUpdateTimeoutPlugin : public MonNotificationPlugin
{
public:
	typedef misc::autoptr<MonQuoteUpdateTimeoutPlugin> Ptr;
	MonQuoteUpdateTimeoutPlugin();
	~MonQuoteUpdateTimeoutPlugin();

	void SetTimeOut(double sec);

	//! --- virtual table ---
	void OnUpdate();
	//! --- end of virtual table ---


private:
	int			m_timeout; // seconds
};

#endif // __MonQuoteUpdateTimeoutPlugin_hpp__
