/*
Copyright (C) 2017 Mihai Vasilian

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

contact: grayasm@gmail.com
*/

#ifndef __SessionStatusListener_hpp__
#define __SessionStatusListener_hpp__

#include <stddef.h>
#include <ForexConnect.h>
#include "string.hpp"
#include "event.hpp"
#include "critical_section.hpp"


namespace fxcm
{
	class SessionStatusListener : public IO2GSessionStatus
	{
	public:
		SessionStatusListener(
			IO2GSession* session,
			bool printSubSessions,
			const stl::string& sessionID,
			const stl::string& pin);

		// vtable begin
		long addRef();
		long release();
		void onSessionStatusChanged(O2GSessionStatus status);
		void onLoginFailed(const char *error);		
		// vtable end

		bool HasError() const;
		bool IsConnected() const;
		bool IsDisconnected() const;
		void reset();
		bool WaitEvents();

	protected:
		~SessionStatusListener();


	private:
		long				m_RefCount;
		stl::string		m_SessionID;
		stl::string		m_Pin;
		bool				m_Error;
		bool				m_Connected;
		bool				m_Disconnected;
		bool				m_PrintSubsessions;
		IO2GSession*		m_Session;
		sys::event			m_SessionEvent;
		misc::critical_section	m_CriticalSection;
	};
} // namespace



#endif // __SessionStatusListener_hpp__
