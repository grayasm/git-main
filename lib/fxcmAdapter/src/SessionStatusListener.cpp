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


#include "SessionStatusListener.hpp"
#include "autocritical_section.hpp"
#include "stream.hpp"



namespace fxcm
{
	SessionStatusListener::SessionStatusListener(
		IO2GSession* session,
		bool printSubSessions,
		const stl::string& sessionID,
		const stl::string& pin)
	{
		m_Session = session;
		m_PrintSubsessions = printSubSessions;
		m_SessionID = sessionID;
		m_Pin = pin;

		m_Session->addRef();
		reset();

		m_RefCount = 1;
		// m_SessionEvent is in non-signaled state.
	}

	long SessionStatusListener::addRef()
	{
		sys::autocritical_section autoCS(m_CriticalSection);
		m_RefCount++;
		return m_RefCount;
	}

	long SessionStatusListener::release()
	{
		sys::autocritical_section autoCS(m_CriticalSection);
		m_RefCount--;
		return m_RefCount;
	}

	void SessionStatusListener::onSessionStatusChanged(O2GSessionStatus status)
	{
		/* When updating to new API, check if there are new enum ids. */
		switch (status)
		{
		case Disconnected:
			stl::cout << "status::disconnected" << std::endl;
			m_Connected = false;
			m_Disconnected = true;
			m_SessionEvent.unlock();
			break;

		case Connecting:
			stl::cout << "status::connecting" << std::endl;
			break;

		case TradingSessionRequested:
		{
			stl::cout << "status:trading session requested" << std::endl;
			O2G2Ptr<IO2GSessionDescriptorCollection> descriptors =
				m_Session->getTradingSessionDescriptors();
			bool found = false;
			if (descriptors)
			{
				if (m_PrintSubsessions)
					std::cout << "descriptors available:" << std::endl;
				for (int i = 0; i < descriptors->size(); ++i)
				{
					O2G2Ptr<IO2GSessionDescriptor> descriptor =
						descriptors->get(i);
					if (m_PrintSubsessions)
						stl::cout 
						<< "  id:='" << descriptor->getID()
						<< "' name='" << descriptor->getName()
						<< "' description='" << descriptor->getDescription()
						<< "' " << (descriptor->requiresPin() ? "requires pin" : "")
						<< std::endl;
					
					if (m_SessionID == descriptor->getID())
					{
						found = true;
						break;
					}
				}
			}
			if (!found)
			{
				onLoginFailed("The specified sub session identifier is not found");
			}
			else
			{
				m_Session->setTradingSession(m_SessionID.c_str(), m_Pin.c_str());
			}
		}
			break;

		case Connected:
			stl::cout << "status::connected" << std::endl;
			m_Connected = true;
			m_Disconnected = false;
			m_SessionEvent.unlock();
			break;

		case Reconnecting:
			stl::cout << "status::reconnecting" << std::endl;
			break;

		case Disconnecting:
			stl::cout << "status::disconnecting" << std::endl;
			break;

		case SessionLost:
			stl::cout << "status::session lost" << std::endl;
			break;

		case PriceSessionReconnecting:
			stl::cout << "status::price session reconnecting" << std::endl;
			break;

		case ConnectedWithNeedToChangePassword:
			stl::cout << "status::connected with need to change password"
				<< std::endl;
			break;

		case ChartSessionReconnecting:
			stl::cout << "status::chart session reconnecting" << std::endl;
			break;

		default:
			stl::cout << __FUNCTION__ << " O2GSessionStatus id does not exist"
				", is this new API?" << std::endl;
			break;
		}
	}

	void SessionStatusListener::onLoginFailed(const char *error)
	{
		stl::cout << "Login error: " << error << std::endl;
		m_Error = true;
	}

	bool SessionStatusListener::HasError() const
	{
		return m_Error;
	}

	bool SessionStatusListener::IsConnected() const
	{
		return m_Connected;
	}

	bool SessionStatusListener::IsDisconnected() const
	{
		return m_Disconnected;
	}

	void SessionStatusListener::reset()
	{
		m_Connected = false;
		m_Disconnected = false;
		m_Error = false;
	}

	bool SessionStatusListener::WaitEvents()
	{
		// 0 for signaled, 1 for timeout
		return (m_SessionEvent.trylock(30000) == 0);
	}

	SessionStatusListener::~SessionStatusListener()
	{
		m_Session->release();
		m_SessionID.clear();
		m_Pin.clear();
		// m_SessionEvent will CloseHandle,etc on destructor.
	}
} // namespace
