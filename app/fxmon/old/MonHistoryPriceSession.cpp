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


#include "MonHistoryPriceSession.hpp"
#include "stream.hpp"


MonHistoryPriceSession::MonHistoryPriceSession()
{
	// m_monitorIni;
	// m_sessionIni;
	m_fxcmSession = 0;
	m_valid = false;
}

MonHistoryPriceSession::~MonHistoryPriceSession()
{
	// Get out clean
	Reset();
}

bool MonHistoryPriceSession::Create(
	const MonitorIni& monitorIni,
	const fxcm::IniParams& sessionIni)
{
	m_monitorIni = monitorIni;
	m_sessionIni = sessionIni;

	return CreateFXCMSession();
}

bool MonHistoryPriceSession::GetInstruments(misc::vector<misc::string>& symbols)
{
	if(!m_valid)
		throw misc::exception("Session is not valid.");

	return m_fxcmSession->GetInstruments(symbols);
}

bool MonHistoryPriceSession::GetCurrencies(misc::vector<fx::Currency>& currencies)
{
	if(!m_valid)
		throw misc::exception("Session is not valid.");

	return m_fxcmSession->GetCurrencies(currencies);
}

bool MonHistoryPriceSession::GetOffer(std::map<misc::string, fx::Price>& quotes)
{
	if(!m_valid)
		throw misc::exception("Session is not valid.");

	return m_fxcmSession->GetOffer(quotes);
}

void MonHistoryPriceSession::Reset()
{
	DestroyFXCMSession();

	m_monitorIni = MonitorIni();
	m_sessionIni = fxcm::IniParams();
	m_fxcmSession = 0;
	m_valid = false;
}

bool MonHistoryPriceSession::CreateFXCMSession()
{
	if(m_sessionIni.GetUser().empty() ||
		m_sessionIni.GetPassword().empty() ||
		m_sessionIni.GetUrl().empty() ||
		m_sessionIni.GetAccount().empty() ||
		//!params.GetSessionID().empty() ||
		//!params.GetPin().empty() ||
		m_sessionIni.GetAccountSymbol().empty())
	{
		misc::cout << "\nCannot create FXCM session for History Prices.";
		m_valid = false;
		return false;
	}

	m_fxcmSession = new fxcm::Session(m_sessionIni);				
	bool connected = m_fxcmSession->Connect();
	misc::cout << "\nHistory Price's FXCM session";
	misc::cout << (connected ? " connected" : ": connection failed");

	if(!connected)
	{
		m_fxcmSession = 0;
		m_valid = false;
		return false;
	}

	return true;
}

bool MonHistoryPriceSession::DestroyFXCMSession()
{
	if(m_fxcmSession.IsNotNull())
	{
		bool bdisconn = false;
		if(m_fxcmSession->IsConnected())
			bdisconn = m_fxcmSession->Disconnect();
		misc::cout << "\nFXCM session";
		misc::cout << (bdisconn ? " disconnected" : ": disconnection failed");
		misc::cout << "\n\n";
		m_fxcmSession = 0;
		m_valid = false;
	}

	return true;
}
