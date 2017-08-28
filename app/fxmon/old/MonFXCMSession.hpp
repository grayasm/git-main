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



#ifndef __MonFXCMSession_hpp__
#define __MonFXCMSession_hpp__



#include "autoptr.hpp"
#include "vector.hpp"
#include "string.hpp"

#include "fxcmIniParams.hpp"
#include "fxcmSession.hpp"

#include "MonitorIni.hpp"
#include "MarketPlugin.hpp"
#include "MarketDummyPlugin.hpp"


class MonFXCMSession
{
public:
	typedef misc::autoptr<MonFXCMSession> Ptr;
	MonFXCMSession();
	~MonFXCMSession();

	bool Create(
		const MonitorIni& monitorIni,
		const fxcm::IniParams& sessionIni);

	fx::MarketPlugin::Ptr GetMarketPlugin() const;

	bool GetInstruments(misc::vector<misc::string>& symbols);
	bool GetCurrencies(misc::vector<fx::Currency>& currencies);
	bool GetOffer(std::map<misc::string, fx::Price>& quotes);

private:
	//! non copyable
	MonFXCMSession(const MonFXCMSession&);
	MonFXCMSession& operator=(const MonFXCMSession&);

	//! Clear all data
	void Reset();

private:
	MonitorIni						m_monitorIni;
	fxcm::IniParams					m_sessionIni;
	fxcm::Session::Ptr				m_fxcmSession;
	fx::MarketDummyPlugin::Ptr		m_dummyPlugin;		// for testing session
	fx::MarketPlugin::Ptr			m_realPlugin;		// for real execution
};


#endif // MonFXCMSession_hpp__