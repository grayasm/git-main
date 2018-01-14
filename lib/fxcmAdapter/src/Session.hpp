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


#ifndef __Session_hpp__
#define __Session_hpp__

#include <stddef.h>
#include <ForexConnect.h>
#include <vector.hpp>

#include "LoginParams.hpp"
#include "IniParams.hpp"
#include "SessionStatusListener.hpp"
#include "ResponseListener4Offers.hpp"
#include "ResponseListener4Orders.hpp"
#include "ResponseListener4HistoryPrices.hpp"
#include "HistoryPricesUpdater.hpp"
#include "TradingSettings.hpp"
#include "TradingPermissions.hpp"

#include "Position.hpp"


namespace fxcm
{
	class Session
	{
	public:
		typedef misc::vector<TradingSettings> TradingSettingsVec;
		typedef misc::vector<HistoryPrice> HistoryPricesVec;

	public:
		Session(const fxcm::LoginParams& loginParams,
				const fxcm::IniParams& iniParams);
		~Session();

		bool Login();
		bool Logout();

		int GetOffers();
		int GetTradingSettings(TradingSettingsVec& tsvec, bool refresh = false);
		int GetTradingPermissions(const char* sInstrument, TradingPermissions& tp);
		int GetOrders();
		int GetLastOffer(Offer& offer, const char* sInstrument);
		int GetHistoryPrices(const char* sInstrument, const char* sTimeframe,
							 DATE dtFrom, DATE dtTo,
							 HistoryPricesVec& historyPricesVec);


	private:
		Session();
		Session(const Session&);
		Session& operator=(const Session&);

		// CommonSources.cpp
		IO2GAccountRow* GetAccount();


	private:
		fxcm::LoginParams					m_loginParams;
		fxcm::IniParams						m_iniParams;
		IO2GSession*						m_session;
		SessionStatusListener*				m_sessionListener;
		OffersPrinter*						m_offersPrinter;
		OffersUpdater*						m_offersUpdater;
		ResponseListener4Offers*			m_responseListener4Offers;
		ResponseListener4Orders*			m_responseListener4Orders;
		ResponseListener4HistoryPrices*		m_responseListener4HistoryPrices;
		HistoryPricesUpdater*				m_historyPricesUpdater;
		TradingSettingsVec					m_tradingSettingsVec;
	};
} // namespace


#endif // __Session_hpp__
