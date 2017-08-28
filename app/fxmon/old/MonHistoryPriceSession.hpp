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

#ifndef __MonHistoryPriceSession_hpp__
#define __MonHistoryPriceSession_hpp__


#include <map>

#include "fxcmIniParams.hpp"
#include "fxcmSession.hpp"

#include "vector.hpp"
#include "string.hpp"
#include "MonitorIni.hpp"




class MonHistoryPriceSession
{
public:
	typedef misc::autoptr<MonHistoryPriceSession> Ptr;
	MonHistoryPriceSession();
	~MonHistoryPriceSession();	

	bool Create(
		const MonitorIni& monitorIni,		// history interval for testing
		const fxcm::IniParams& sessionIni);	// broker connection data

	bool GetInstruments(misc::vector<misc::string>& symbols);
	bool GetCurrencies(misc::vector<fx::Currency>& currencies);
	bool GetOffer(std::map<misc::string, fx::Price>& quotes);	
	bool GetHistPrices(
		const misc::string&		symbol,			// "EUR/USD"
		const misc::string&		sTimeFrame,		// m1 or H1
		const misc::string&		sDateFrom,		// m.d.Y H:M:S
		const misc::string&		sDateTo,		// m.d.Y H:M:S
		fxcm::HistPriceData&	retPriceData);	// prices

private:
	//! Reset clean (log out, etc)
	void Reset();
	// session create
	bool CreateFXCMSession();
	// session close
	bool DestroyFXCMSession();
	

	MonitorIni			m_monitorIni;
	fxcm::IniParams		m_sessionIni;
	fxcm::Session::Ptr	m_fxcmSession;
	bool				m_valid;
};


#endif // __MonHistoryPriceSession_hpp__

