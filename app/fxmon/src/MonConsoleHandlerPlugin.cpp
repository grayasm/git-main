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


#include "MonConsoleHandlerPlugin.hpp"
#include "MonEngine.hpp"


// control handler
MonConsoleHandlerPlugin* _thisMonConsoleHandlerPlugin;
BOOL ControlHandler(DWORD dwControlEvent);

MonConsoleHandlerPlugin::MonConsoleHandlerPlugin()
{
	m_CtrlC = false;
	_thisMonConsoleHandlerPlugin = this;
	SetConsoleCtrlHandler((PHANDLER_ROUTINE)ControlHandler, TRUE);

	//
	m_engine = 0;
}

MonConsoleHandlerPlugin::~MonConsoleHandlerPlugin()
{

}

void MonConsoleHandlerPlugin::OnUpdate()
{
	bool close = false;
	m_critical_section.lock();
	close = m_CtrlC;
	m_critical_section.unlock();

	//
	if(close && m_engine)
	{
		m_engine->Stop();
	}
}

void MonConsoleHandlerPlugin::SetEngine(MonEngine* engine)
{
	m_engine = engine;
}

//##############################################################################
BOOL ControlHandler(DWORD dwControlEvent) 
{ 
	switch (dwControlEvent) 
	{ 		
	case CTRL_SHUTDOWN_EVENT:		// User wants to shutdown.
	case CTRL_LOGOFF_EVENT:			// User wants to logoff
	case CTRL_C_EVENT:				// Ctrl + C
	case CTRL_CLOSE_EVENT:			// User wants to exit the "normal" way 
		{
			_thisMonConsoleHandlerPlugin->m_critical_section.lock();
			_thisMonConsoleHandlerPlugin->m_CtrlC = true;
			_thisMonConsoleHandlerPlugin->m_critical_section.unlock();
		}
		return TRUE; 
		
		// Everything else, just ignore it...
	default:
		return FALSE; 
	} 
} 