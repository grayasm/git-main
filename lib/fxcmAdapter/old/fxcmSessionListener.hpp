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


#ifndef __fxcmSessionListener_hpp__
#define __fxcmSessionListener_hpp__


// c
#include <stdlib.h> // NULL undefined in io2gtable.h(101)
// c++
// fxcm
#include "ForexConnect.h"

// local
#include "autoptr.hpp"
#include "stream.hpp"
#include "event.hpp"
#include "critical_section.hpp"
#include "fxcmIniParams.hpp"



namespace fxcm
{
	class SessionListener : public IO2GSessionStatus
	{
	public:
		typedef misc::autoptr<SessionListener> Ptr;

	public:
		SessionListener(IO2GSession* session, const fxcm::IniParams& iniParams);
		~SessionListener();
		void Reset();
		bool HasError() const;
		bool IsConnected() const;
		bool IsDisconnected() const;
		bool WaitEvents();



		//! vtable
		void onSessionStatusChanged(IO2GSessionStatus::O2GSessionStatus status);
		void onLoginFailed(const char* error);
		long addRef();
		long release();
		// end vtable

	private:
		//! Non copy-able
		SessionListener(const SessionListener&);
		SessionListener& operator=(const SessionListener&);		

	private:
		long						m_refCount;
		IO2GSession*				m_session;
		fxcm::IniParams				m_iniParams;
		bool						m_connected;
		bool						m_disconnected;
		bool						m_error;
		misc::event					m_event;
		misc::critical_section		m_critical_section;
	};
}

#endif // __fxcmSessionListener_hpp__
