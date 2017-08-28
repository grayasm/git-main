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


#ifndef __MonSession_hpp__
#define __MonSession_hpp__

// c/c++
#include <map>

// fxcm adapter
#include "fxcmSession.hpp"
#include "fxcmIniParams.hpp"

// local
#include "autoptr.hpp"
#include "MarketPlugin.hpp"
#include "MonitorIni.hpp"
#include "MonFXCMSession.hpp"
#include "MonHistoryPriceSession.hpp"
#include "MonPriceGeneratorSession.hpp"


class MonSession
{
public:
	typedef misc::autoptr<MonSession> Ptr;
	MonSession();
	~MonSession();
	MonSession(const MonSession& tc);
	MonSession& operator=(const MonSession&);

	bool CreateSession(
		const MonitorIni& monitorIni,
		const fxcm::IniParams& sessionIni);
	
	fx::MarketPlugin::Ptr GetMarketPlugin();

	bool GetOffer(std::map<misc::string, fx::Price>& quotes);

private:
	// clean reset
	void Reset();

	// session create functions
	bool CreateFXCMSession();
	bool CreateHistoryPricesSession();
	bool CreatePriceGeneratorSession();

	// session close functions
	bool DestroyFXCMSession();
	bool DestroyHistoryPriceSession();
	bool DestroyPriceGeneratorSession();
	

	// etc

private:
	MonitorIni						m_monitorIni;
	fxcm::IniParams					m_sessionIni;
	MonFXCMSession::Ptr				m_fxcmSession;
	MonHistoryPriceSession::Ptr		m_histPriceSession;
	MonPriceGeneratorSession::Ptr	m_priceGenSession;
	fx::MarketPlugin::Ptr			m_plugin;
	bool							m_valid;
};


#endif // __MonSession_hpp__