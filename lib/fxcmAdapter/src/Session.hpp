/*
Copyright (C) 2017 Mihai Vasilian
*/


#ifndef __Session_hpp__
#define __Session_hpp__

#include <stddef.h>
#include <string>
#include <ForexConnect.h>
#include <vector.hpp>

#include "LoginParams.hpp"
#include "IniParams.hpp"
#include "SessionStatusListener.hpp"
#include "ResponseListener4Offers.hpp"
#include "ResponseListener4EntryOrders.hpp"
#include "ResponseListener4HistoryPrices.hpp"
#include "ResponseListener4MarketOrders.hpp"
#include "HistoryPricesUpdater.hpp"
#include "TradingSettings.hpp"
#include "TradingPermissions.hpp"
#include "Position.hpp"
#include "PipCost.hpp"


namespace fxcm
{
	class Session
	{
	public:
		typedef stl::vector<TradingSettings> TradingSettingsVec;
		typedef stl::vector<fx::OHLCPrice> HistoryPricesVec;
        typedef std::map<stl::string, fx::Offer> OffersMap;

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
		int GetLastOffer(fx::Offer& offer, const char* sInstrument);
        int GetAllOffers(OffersMap& offers);
		int GetHistoryPrices(const char* sInstrument, const char* sTimeframe,
							 DATE dtFrom, DATE dtTo,
							 HistoryPricesVec& historyPricesVec);
		int OpenPosition(const fx::Offer& offer, int lots, bool buy,
						stl::vector<fx::Position>& result);
		int ClosePosition(const fx::Offer& offer, const fx::Position& position,
						stl::vector<fx::Position>& result);
		int GetOpenPositions(const fx::Offer& offer,
						stl::vector<fx::Position>& result);
		

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
		OffersUpdater*						m_offersUpdater;
		OffersWriter*						m_offersWriter;
		ResponseListener4Offers*			m_responseListener4Offers;
		ResponseListener4EntryOrders*		m_responseListener4EntryOrders;
		ResponseListener4HistoryPrices*		m_responseListener4HistoryPrices;
		ResponseListener4MarketOrders*		m_responseListener4MarketOrders;
		HistoryPricesUpdater*				m_historyPricesUpdater;
		TradingSettingsVec					m_tradingSettingsVec;
        PipCost                             m_pipCost;
	};
} // namespace


#endif // __Session_hpp__
