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


#ifndef __fxcmSession_hpp__
#define __fxcmSession_hpp__


// c
// c++
#include <map>
// local
#include "autoptr.hpp"
#include "vector.hpp"
#include "string.hpp"
#include "audit.hpp"
#include "Position.hpp"
#include "MarketPlugin.hpp"

// adapter
#include "fxcmIniParams.hpp"
#include "fxcmHistory.hpp"


// fxcm
class IO2GSession;
class IO2GLoginRules;
class IO2GResponseReaderFactory;
class IO2GResponse;
class IO2GAccountRow;
class IO2GOfferRow;
class IO2GOrderRow;
class IO2GTradeRow;
class IO2GClosedTradeRow;
typedef double DATE;


namespace fxcm
{
	// adapter
	class SessionListener;
	class ResponseListener;
	class OrderMonitor;
	class TradingSettings;
	class Permission;

	

	class Session
	{
	public:
		typedef misc::autoptr<Session> Ptr;

	public:
		//! Create a session object.
		Session(const fxcm::IniParams& iniParams);

		//! Destroy the session object.
		~Session();

		//! Connect to broker.
		bool Connect();

		//! Disconnect from broker.
		bool Disconnect();

		//! Retrieves connection status
		bool IsConnected();

		//! Retrieves connections status
		bool IsDisconnected();

		//! Returns all instruments available to trade.
		bool GetInstruments(misc::vector<misc::string>& symbols);

		//! Returns all instruments as Currency objects.
		bool GetCurrencies(misc::vector<fx::Currency>& currencies);

		//! Retrieves the price offer available now.
		bool GetOffer(std::map<misc::string, fx::Price>& quotes);
		
		//! Retrieve market real plugin
		fx::MarketPlugin::Ptr GetMarketPlugin();

		//! Create an entry order without limits.
		bool CreateEntryOrder(
			const fx::Position& posin,		// position requested
			fx::Position& posout);			// position created (pending entry)

		//! Create an entry order with limits.
		bool CreateEntryOrder(
			const fx::Position& posin,		// position requested
			double rateLimit,				// 1.34120 (+2.0 limit on a buy entry)
			double rateStop,				// 1.34080 (-2.0 stop on a buy entry)
			fx::Position& posout);			// position created (pending entry)

		//! Removes the entry order with given id.
		bool RemoveEntryOrder(
			const fx::Position& posin);	// 40653838
		
		//! Retrieves history prices
		bool GetHistPrices(
			const misc::string&		symbol,			// "EUR/USD"
			const misc::string&		sTimeFrame,		// m1 or H1
			const misc::string&		sDateFrom,		// m.d.Y H:M:S
			const misc::string&		sDateTo,		// m.d.Y H:M:S
			fxcm::HistPriceData&	retPriceData);	// prices

		//! Creates a true market order.
		bool CreateMarketOrder(
			const fx::Position& posin,
			misc::vector<fx::Position>& outvec);	// 1 or more trades(tickets) depending on liquidity

		//! Closes a true market order.
		bool CloseMarketOrder(
			const fx::Position& posin,				// requested position to be closed
			misc::vector<fx::Position>& outvec);	// market execution (liquidity)

		//! Retrieves all trades opened in the market for given symbol
		bool GetMarketOrders(
			const fx::Position& posin,
			misc::vector<fx::Position>& outvec);

		//! Retrieves all pending entry orders for given symbol
		bool GetEntryOrders(
			const fx::Position& posin,
			misc::vector<fx::Position>& outvec);

		//! Set the log file
		void SetAuditFile(const misc::string& filepath);

	private:
		//! non copyable, no default
		Session();
		Session(const Session&);
		Session& operator=(const Session&);

		//! internal
		bool Login();
		bool Logout();

		IO2GAccountRow* GetAccount(
			IO2GLoginRules* loginRules,
			IO2GResponseReaderFactory* readerFactory);

		bool GetCurrenciesImpl(misc::vector<fx::Currency>& currencies);

		bool GetOfferImpl(std::map<misc::string, fx::Price>& quotes);

		bool GetOfferReq(std::map<misc::string, fx::Price>& quotes);

		IO2GOfferRow* GetOfferInt(
			IO2GLoginRules* loginRules,
			IO2GResponseReaderFactory* readerFactory,
			const misc::string& symbol);

		IO2GTradeRow* GetTrade(
			IO2GOfferRow* offer,
			const misc::string& orderID,
			const misc::string& tradeID);

		bool CreateEntryOrderImpl(
			const fx::Position& posin,
			double rateLimit,
			double rateStop,
			fx::Position& posout);

		bool CreateEntryOrderReq(
			const fx::Position& posin,
			double rateLimit,
			double rateStop,
			IO2GOfferRow* offer,
			fx::Position& posout);

		bool RemoveEntryOrderReq(
			const fx::Position& posin);

		bool CreateMarketOrderImpl(
			const fx::Position& posin,
			misc::vector<fx::Position>& outvec);		

		bool CreateMarketOrderReq(
			const fx::Position& posin,
			IO2GOfferRow* offer,
			misc::vector<fx::Position>& outvec);

		bool CreateMarketOrderRejected(
			const fx::Position& posin,
			misc::vector<fx::Position>& outvec);

		bool CloseMarketOrderImpl(
			const fx::Position& posin,
			misc::vector<fx::Position>& outvec);

		bool CloseMarketOrderReq(
			const fx::Position& posin,
			IO2GOfferRow* offer,
			misc::vector<fx::Position>& outvec);

		bool CloseMarketOrderRejected(
			const fx::Position& posin,
			misc::vector<fx::Position>& outvec);
		
		bool GetMarketOrdersImpl(
			const fx::Position& posin,
			misc::vector<fx::Position>& outvec);

		bool GetMarketOrdersReq(
			const fx::Position& posin,
			IO2GOfferRow* offer,
			misc::vector<fx::Position>& outvec);

		bool GetEntryOrders(
			const fx::Position& posin,
			IO2GOfferRow* offer,
			misc::vector<fx::Position>& outvec);

		bool UpdatePriceOffer(
			IO2GResponse* response,
			std::map<misc::string, fx::Price>& outvec);

		bool UpdateCurrencies(
			IO2GResponse* response,
			misc::vector<fx::Currency>& outvec);		

		//! Converts from Order (src) to Position (dest)
		bool Order2Position(IO2GOrderRow* src, fx::Position& dest);

		//! Collects all resulted trades into destination array.
		bool CollectAllTrades(
			const fx::Position& posin,
			OrderMonitor& orderMonitor,
			misc::vector<fx::Position>& outvec);

		//! Converts a Trade into a Position.
		bool OpenTrade2Position(IO2GTradeRow* src, fx::Position& dest);

		//! Converts a Closed trade into a Position.
		bool ClosedTrade2Position(IO2GClosedTradeRow* src, fx::Position& dest);

		//! Retrieve history prices
		bool ReadHistPrices(IO2GResponse* response, HistPriceData& retPriceData);

		//! Converts DATE into a readable format
		void FormatDate(DATE date, misc::string& buf);

		//! Try to fix the connection when getting timeouts.
		void HandleTimeOut();

		

	private:
		fxcm::IniParams					m_iniParams;
		misc::vector<misc::string>		m_symbols;
		IO2GSession*					m_session;
		SessionListener*				m_sessionListener;
		ResponseListener*				m_responseListener;
		TradingSettings*				m_tradingSettings;
		Permission*						m_permission;
		misc::audit						m_audit;
	};
}


#endif // __fxcmSession_hpp__

