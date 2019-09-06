/*
	Copyright (C) 2018 Mihai Vasilian

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
