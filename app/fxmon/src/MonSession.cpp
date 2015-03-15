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


#include "MonSession.hpp"
#include "stream.hpp"
#include "MarketDummyPlugin.hpp"


MonSession::MonSession()
{
	// m_monitorIni;
	// m_sessionIni;
	m_fxcmSession = 0;
	m_histPriceSession = 0;
	m_priceGenSession = 0;
	m_plugin = 0;
	m_valid = false;
}

MonSession::~MonSession()
{
	// clean exit (lot out, etc)
	Reset();
}

MonSession::MonSession(const MonSession& tc)
{
	*this = tc;
}

MonSession& MonSession::operator=(const MonSession& tc)
{
	if(this != &tc)
	{
		m_monitorIni = tc.m_monitorIni;
		m_sessionIni = tc.m_sessionIni;
		m_fxcmSession = tc.m_fxcmSession;
		m_histPriceSession = tc.m_histPriceSession;
		m_priceGenSession = tc.m_priceGenSession;
		m_plugin = tc.m_plugin;
		m_valid = tc.m_valid;
	}
	return *this;
}

bool MonSession::CreateSession(
	const MonitorIni& monitorIni,
	const fxcm::IniParams& sessionIni)
{
	Reset();

	m_monitorIni = monitorIni;
	m_sessionIni = sessionIni;
	
	if(m_monitorIni.GetConnection() == "Demo" ||
		m_monitorIni.GetConnection() == "Real")
	{
		return CreateFXCMSession();
	}
	
	if(m_monitorIni.GetConnection() == "HistoryPrices")
	{
		return CreateHistoryPricesSession();
	}

	if(m_monitorIni.GetConnection() == "PriceGenerator")
	{
		return CreatePriceGeneratorSession();
	}


	throw misc::exception("Unknown parameter");
}

fx::MarketPlugin::Ptr MonSession::GetMarketPlugin()
{
	return m_plugin;
}

bool MonSession::GetOffer(std::map<misc::string, fx::Price>& quotes)
{
	if(!m_valid)
		throw misc::exception("Invalid session.");

	if(m_fxcmSession.IsNotNull())
		return m_fxcmSession->GetOffer(quotes);

	if(m_histPriceSession.IsNotNull())
		return m_histPriceSession->GetOffer(quotes);

	if(m_priceGenSession.IsNotNull())
		return m_priceGenSession->GetOffer(quotes);

	throw misc::exception("Unknown exception.");
}

void MonSession::Reset()
{
	DestroyFXCMSession();
	DestroyHistoryPriceSession();
	DestroyPriceGeneratorSession();

	m_monitorIni = MonitorIni();
	m_sessionIni = fxcm::IniParams();
	m_fxcmSession = 0;
	m_priceGenSession = 0;
	m_histPriceSession = 0;
	m_plugin = 0;
	m_valid = false;
}

bool MonSession::CreateFXCMSession()
{
	m_fxcmSession = new MonFXCMSession();
	if(!m_fxcmSession->Create(m_monitorIni, m_sessionIni))
	{
		m_valid = false;
		return false;
	}

	m_plugin = m_fxcmSession->GetMarketPlugin();
	m_valid = true;
	return true;
}

bool MonSession::CreateHistoryPricesSession()
{
	m_histPriceSession = new MonHistoryPriceSession();
	m_plugin = new fx::MarketDummyPlugin();
	m_valid = true;
	return true;
}

bool MonSession::CreatePriceGeneratorSession()
{
	m_priceGenSession = new MonPriceGeneratorSession();
	fx::Currency currency = m_monitorIni.GetPriceGeneratorCurrency();
	int trendChance = m_monitorIni.GetPriceGeneratorTrendChance();
	int trendFragmentation = m_monitorIni.GetPriceGeneratorTrendFragmentation();
	double volatility = m_monitorIni.GetPriceGeneratorVolatility();
	fx::MarketDummyPlugin::Ptr plugin = new fx::MarketDummyPlugin();	
	m_priceGenSession->Create(currency, trendChance, trendFragmentation, volatility, plugin);

	m_plugin = plugin;	
	m_valid = true;
	return true;
}

bool MonSession::DestroyFXCMSession()
{
	if(m_fxcmSession.IsNotNull())
	{
		m_fxcmSession = 0;
		m_plugin = 0;
		m_valid = false;
	}

	return true;
}

bool MonSession::DestroyHistoryPriceSession()
{
	if(m_histPriceSession.IsNotNull())
	{
		m_histPriceSession = 0;
		m_plugin = 0;
		m_valid = false;
	}

	return true;
}

bool MonSession::DestroyPriceGeneratorSession()
{
	if(m_priceGenSession.IsNotNull())
	{
		m_priceGenSession = 0;
		m_plugin = 0; // dummy plugin
		m_valid = false;
	}
	
	return true;
}



