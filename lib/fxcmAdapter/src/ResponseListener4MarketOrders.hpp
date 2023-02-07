/*
Copyright (C) 2018 Mihai Vasilian
*/


#ifndef __ResponseListener4MarketOrders_hpp__
#define __ResponseListener4MarketOrders_hpp__

#include <stddef.h>
#include <string>
#include <ForexConnect.h>
#include "string.hpp"
#include "event.hpp"
#include "critical_section.hpp"
#include "vector.hpp"
#include "OrderMonitor.hpp"
#include "Position.hpp"



namespace fxcm
{
	class ResponseListener4MarketOrders : public IO2GResponseListener
	{
	public:
		ResponseListener4MarketOrders(IO2GSession* session);

		// vtable begin
		long addRef();
		long release();
		void onRequestCompleted(const char* requestId, IO2GResponse* response=0);
		void onRequestFailed(const char* requestId, const char* error);
		void onTablesUpdates(IO2GResponse* tablesUpdates);
		// vtable end

		void SetRequestID(const stl::string& requestID);
		bool WaitEvents();
		IO2GResponse* GetResponse();

		const stl::vector<IO2GTradeRow*>& GetTrades() const;
		const stl::vector<IO2GClosedTradeRow*> GetClosedTrades() const;
		void ClearResult();

	protected:
		~ResponseListener4MarketOrders();

	private:
		void SetResult();		

	private:
		long					m_RefCount;
		IO2GSession*			m_Session;
		stl::string			m_RequestID;
		sys::event				m_ResponseEvent;
		IO2GResponse*			m_Response;
		OrderMonitor*			m_OrderMonitor;
		sys::critical_section	m_CriticalSection;
		stl::vector<IO2GTradeRow*>	m_trades;
		stl::vector<IO2GClosedTradeRow*>	m_closedTrades;

	};
} // namespace


#endif // __ResponseListener4MarketOrders_hpp__
