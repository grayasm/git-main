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

#include "fxcmSessionListener.hpp"


namespace fxcm
{
	SessionListener::SessionListener(IO2GSession* session, const fxcm::IniParams& iniParams)
	{
		m_iniParams = iniParams;
		m_session = session;
		m_session->addRef();		
		Reset();
		m_refCount = 1;
		// m_event
		// m_critical_section
	}

	SessionListener::~SessionListener()
	{
		m_session->release();
		// m_iniParams
		m_connected = false;
		m_disconnected = false;
		m_error = false;
	}

	void SessionListener::Reset()
	{
		m_connected = false;
		m_disconnected = false;
		m_error = false;
	}

	bool SessionListener::HasError() const
	{
		return m_error;
	}

	bool SessionListener::IsConnected() const
	{
		return m_connected;
	}

	bool SessionListener::IsDisconnected() const
	{
		return m_disconnected;
	}

	bool SessionListener::WaitEvents()
	{
		return (m_event.trylock(30000) == 1);
	}

	void SessionListener::onSessionStatusChanged(IO2GSessionStatus::O2GSessionStatus status)
	{
		switch(status)
		{
		case IO2GSessionStatus::Disconnected:
			{
				misc::cout << "\n\tstatus::disconnected";
				m_connected = false;
				m_disconnected = true;
				m_event.setevent();
			}
			break;
		case IO2GSessionStatus::Connecting:
			misc::cout << "\n\tstatus::connecting";
			break;
		case IO2GSessionStatus::TradingSessionRequested:
			{
				misc::cout << "\n\tstatus::trading session requested";
				O2G2Ptr<IO2GSessionDescriptorCollection> descriptors = 
					m_session->getTradingSessionDescriptors();
				bool found = false;
				if(descriptors)
				{
					misc::cout << "\n\tdescriptors available";
					for(int i=0; i < descriptors->size(); ++i)
					{
						O2G2Ptr<IO2GSessionDescriptor> descriptor = 
							descriptors->get(i);

						misc::cout << "\n\t\t id          = " << descriptor->getID();
						misc::cout << "\n\t\t name        = " << descriptor->getName();
						misc::cout << "\n\t\t description = " << descriptor->getDescription();
						if(descriptor->requiresPin())
							misc::cout << "\n\t\t requires pin";

						if(m_iniParams.GetSessionID() == descriptor->getID())
						{
							found = true;
							break;
						}
					}
				}

				if(!found)
				{
					onLoginFailed("The requested sessionID is not found.");
				}
				else
				{
					m_session->setTradingSession(
						m_iniParams.GetSessionID().c_str(), 
						m_iniParams.GetPin().c_str());
				}
			} // case
			break;
		case IO2GSessionStatus::Connected:
			{
				misc::cout << "\n\tstatus::connected";
				m_connected = true;
				m_disconnected = false;
				m_event.setevent();
			}
			break;
		case IO2GSessionStatus::Reconnecting:
			misc::cout << "\n\tstatus::reconnecting";
			break;
		case IO2GSessionStatus::Disconnecting:
			misc::cout << "\n\tstatus::disconnecting";
			break;
		case IO2GSessionStatus::SessionLost:
			misc::cout << "\n\tstatus::session lost";
			break;
		case IO2GSessionStatus::PriceSessionReconnecting:
			misc::cout << "\n\tstatus::price session reconnecting";
			break;
		case IO2GSessionStatus::ConnectedWithNeedToChangePassword:
			misc::cout << "\n\tstatus::connected with need to change password";
			break;
		}
	}

	void SessionListener::onLoginFailed(const char *error)
	{
		misc::cout << "Login error: " << error << "\n";
		m_error = true;
		m_event.setevent();
	}

	long SessionListener::addRef()
	{
		m_critical_section.lock();
		++m_refCount;
		m_critical_section.unlock();
		return m_refCount;
	}

	long SessionListener::release()
	{
		m_critical_section.lock();
		--m_refCount;
		m_critical_section.unlock();
		return m_refCount;
	}
} // namespace fxcm
