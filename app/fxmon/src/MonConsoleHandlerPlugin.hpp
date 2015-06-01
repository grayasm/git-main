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


#ifndef __MonConsoleHandlerPlugin_hpp__
#define __MonConsoleHandlerPlugin_hpp__

#include "MonNotificationPlugin.hpp"
#include "critical_section.hpp"


class MonEngine;

class MonConsoleHandlerPlugin : public MonNotificationPlugin
{
public:
	typedef misc::autoptr<MonConsoleHandlerPlugin> Ptr;
	MonConsoleHandlerPlugin();
	~MonConsoleHandlerPlugin();

	//! --- virtual table ---
	void OnUpdate();
	//! --- end of virtual table ---


	void SetEngine(MonEngine* engine);

private:
	//! copying disabled
	MonConsoleHandlerPlugin(const MonConsoleHandlerPlugin&);
	MonConsoleHandlerPlugin& operator=(const MonConsoleHandlerPlugin&);

#ifdef _WIN32
	// control handler
	friend BOOL ControlHandler(DWORD dwControlEvent);
#else
#endif
	
	misc::critical_section		m_critical_section;
	bool						m_CtrlC;
	// engine
	MonEngine*					m_engine;
};

#endif // __MonConsoleHandlerPlugin_hpp__

