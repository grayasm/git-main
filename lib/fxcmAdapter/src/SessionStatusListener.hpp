/*
Copyright (C) 2017 Mihai Vasilian
*/

#ifndef __SessionStatusListener_hpp__
#define __SessionStatusListener_hpp__

#include <stddef.h>
#include <string>
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
		sys::critical_section	m_CriticalSection;
	};
} // namespace



#endif // __SessionStatusListener_hpp__
