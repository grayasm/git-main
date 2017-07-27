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


#ifndef __fxcmResponseListener_hpp__
#define __fxcmResponseListener_hpp__


// c
#include <stdlib.h> // NULL undefined in io2gtable.h(101)
// c++
#include <map>
// fxcm
#include "ForexConnect.h"

// local
#include "autoptr.hpp"
#include "stream.hpp"
#include "audit.hpp"
#include "event.hpp"
#include "critical_section.hpp"
#include "fxcmOrderMonitor.hpp"
#include "Price.hpp"




namespace fxcm
{
	class ResponseListener : public IO2GResponseListener
	{
	public:
		// types
		typedef std::map<misc::string, fx::Price>	Quotes;
		typedef misc::vector<misc::string>			Tradables;
		enum RequestStatus
		{
			RequestReady = 0,
			RequestCompleted = 1,
			RequestFailed = 2
		};

	public:
		ResponseListener();
		ResponseListener(IO2GSession* session);
		~ResponseListener();

		//! virtual table
		virtual void onRequestCompleted(const char *requestId, IO2GResponse *response = 0);
		virtual void onRequestFailed(const char *requestId , const char *error);
		virtual void onTablesUpdates(IO2GResponse *data);
		virtual long addRef();
		virtual long release();
		// --- end virtual table ---
		
		void SetRequestID(const char *sRequestID);
		bool WaitEvents();
		IO2GResponse* GetResponse();
		OrderMonitor& GetOrderMonitor();
		misc::critical_section& GetCriticalSection();
		Quotes& GetQuotes();
		void Reset();
		RequestStatus GetRequestStatus();
		

	private:
		void Init();
		void Destroy();
		void UpdateOffers(IO2GTablesUpdatesReader* reader, int index);
		void UpdateOrders(IO2GTablesUpdatesReader* reader, int index);
		void UpdateEntryOrders(IO2GTablesUpdatesReader* reader, IO2GOrderRow* order, int index);
		void UpdateMarketOrders(IO2GTablesUpdatesReader* reader, IO2GOrderRow* order, int index);
		void UpdateOpenTrades(IO2GTablesUpdatesReader* reader, int index);
		void UpdateClosedTrades(IO2GTablesUpdatesReader* reader, int index);
		void UpdateMessages(IO2GTablesUpdatesReader* reader, int index);
		void UpdateAccounts(IO2GTablesUpdatesReader* reader, int index);


		void PrintResult();
		void PrintTrades(misc::vector<IO2GTradeRow*>& trades, const misc::string& sOrderID);
		void PrintClosedTrades(misc::vector<IO2GClosedTradeRow*>& trades, const misc::string& sOrderID);
		misc::string IO2GResponse2String(IO2GResponse* response) const;
		misc::string IO2GOfferRow2String(IO2GOfferRow* offer) const;
		misc::string IO2GOrderRow2String(IO2GOrderRow* order) const;
		misc::string O2GTableUpdateType2String(O2GTableUpdateType* type) const;
		bool Eq(IO2GOrderRow* l, IO2GOrderRow* r) const;
	public:
		// need these functions in Session also, to validate offer of refreshed table reader.
		bool IsOfferTradable(IO2GOfferRow* offer) const;
		bool IsOfferValid(IO2GOfferRow* offer) const;
	private:
		void InitTradables();


	private:
		long					m_refCount;
		IO2GSession*			m_session;
		misc::string			m_requestID;
		misc::event				m_event;
		misc::critical_section	m_refCriticalSection;
		OrderMonitor			m_orderMonitor;
		IO2GResponse*			m_response;
		RequestStatus			m_requestStatus;
		Quotes					m_quotes;
		bool					m_bAllowQuotes;
#define MAX_SLIPPAGE			300
#define MAX_SPREAD				20
		Tradables				m_tradables;
		misc::audit				m_audit;
	};
} // namespace

#endif // __fxcmResponseListener_hpp__