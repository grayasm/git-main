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


#include "MonFXCMSession.hpp"
#include "stream.hpp"


MonFXCMSession::MonFXCMSession()
{

}

MonFXCMSession::~MonFXCMSession()
{
	// exit clean
	Reset();
}

bool MonFXCMSession::Create(
		const MonitorIni& monitorIni,
		const fxcm::IniParams& sessionIni)
{
	Reset();

	m_monitorIni = monitorIni;
	m_sessionIni = sessionIni;


	if(m_sessionIni.GetUser().empty() ||
		m_sessionIni.GetPassword().empty() ||
		m_sessionIni.GetUrl().empty() ||
		m_sessionIni.GetAccount().empty() ||
		// m_sessionIni.GetSessionID().empty() ||
		// m_sessionIni.GetPin().empty() ||
		m_sessionIni.GetAccountSymbol().empty())
	{
		misc::cout << "\nInvalid parameters for FXCM session.";
		return false;
	}

	if(m_monitorIni.GetConnection() != m_sessionIni.GetConnection())
	{
		misc::cout << "\nFXCM connection '" << m_sessionIni.GetConnection().c_str() <<
			"' different from expected '" << m_monitorIni.GetConnection().c_str() << "'";
		return false;
	}	

	misc::string auditFile = m_monitorIni.GetAuditFile();

	// --- create FXCM session ---
	m_fxcmSession = new fxcm::Session(m_sessionIni);
	
	if(!auditFile.empty())
		m_fxcmSession->SetAuditFile(auditFile);

	bool connected = m_fxcmSession->Connect();
	misc::cout << "\nFXCM session";
	misc::cout << (connected ? " connected" : ": connection failed");

	if(!connected)
	{
		m_fxcmSession = 0;
		return false;
	}

	// --- create market plugin ---
	if(m_monitorIni.GetMarketPlugin() == "Dummy")
	{
		m_dummyPlugin = new fx::MarketDummyPlugin();
	}
	else if(m_monitorIni.GetMarketPlugin() == "Real")
	{
		m_realPlugin = m_fxcmSession->GetMarketPlugin();
	}
	else
	{
		throw misc::exception("Unknown plugin type.");
	}

	return true;
}

fx::MarketPlugin::Ptr MonFXCMSession::GetMarketPlugin() const
{
	if(m_dummyPlugin.IsNotNull())
		return m_dummyPlugin;
	else if(m_realPlugin.IsNotNull())
		return m_realPlugin;

	throw misc::exception("Invalid plugin.");
}

bool MonFXCMSession::GetInstruments(misc::vector<misc::string>& symbols)
{
	return m_fxcmSession->GetInstruments(symbols);
}

bool MonFXCMSession::GetCurrencies(misc::vector<fx::Currency>& currencies)
{
	return m_fxcmSession->GetCurrencies(currencies);
}

bool MonFXCMSession::GetOffer(std::map<misc::string, fx::Price>& quotes)
{
	if(m_realPlugin.IsNotNull())
		return m_fxcmSession->GetOffer(quotes);

	if(m_dummyPlugin.IsNotNull())
	{
		bool ret = m_fxcmSession->GetOffer(quotes);

		// TODO: hard coded "EUR/USD" instrument
		m_dummyPlugin->SetPrice(quotes["EUR/USD"]);

		return ret;
	}

	throw misc::exception("Unknown plugin type.");
}


void MonFXCMSession::Reset()
{
	// Attempt to close FXCM session (if any)
	if(m_fxcmSession.IsNotNull())
	{
		m_monitorIni = MonitorIni();
		m_sessionIni = fxcm::IniParams();

		bool bdisconn = false;
		if(m_fxcmSession->IsConnected())
			bdisconn = m_fxcmSession->Disconnect();
		misc::cout << "\nFXCM session";
		misc::cout << (bdisconn ? " disconnected" : ": disconnection failed");
		misc::cout << "\n\n";
		m_fxcmSession = 0;		

		m_dummyPlugin = 0;
		m_realPlugin = 0;
	}	
}
