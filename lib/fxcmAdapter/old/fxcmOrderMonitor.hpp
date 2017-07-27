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


#ifndef __fxcmOrderMonitor_hpp__
#define __fxcmOrderMonitor_hpp__


// c/c++
// fxcm
#include "ForexConnect.h"
// local
#include "string.hpp"
#include "vector.hpp"
#include "audit.hpp"


namespace fxcm
{

	bool isOpeningOrder(IO2GOrderRow *order);
	bool isClosingOrder(IO2GOrderRow *order);

	/** Helper class for monitoring creation open positions using a open order.
		On no dealing desk more than one position can be create. It is depends on
		liquidity on forex market, The class stores all open positions 
	*/
	class OrderMonitor
	{
	public:
		// State values correspond to those documented here:
		// http://www.fxcodebase.com/documents/ForexConnectAPI/IO2GOrderRow.getStatus.html
		enum ExecutionState
		{
			Waiting,			// W
			InProcess,			// P
			DealerIntervention,	// I
			Requoted,			// Q
			PendingCalculated,	// U
			Executing,			// E
			Cancelled,			// C
			Rejected,			// R
			Expired,			// T
			Executed,			// F
			NotAvailable		// G
		};

		enum OrderResult
		{
			OrderExecuting,
			OrderFinished
		};

		OrderMonitor();
		~OrderMonitor();
		void SetOrder(IO2GOrderRow* order);
		bool IsActive() const;
		void Reset();
		
		void onTradeAdded(IO2GTradeRow* trade);
		void onOrderDeleted(IO2GOrderRow* order);
		void onMessageAdded(IO2GMessageRow* message);
		void onClosedTradeAdded(IO2GClosedTradeRow* closedTrade);

		OrderResult getResult();
		ExecutionState getState();
		bool isAllTradesReceived();
		IO2GOrderRow* getOrder();
		void getOpenTrades(misc::vector<IO2GTradeRow*>& trades);
		void getClosedTrades(misc::vector<IO2GClosedTradeRow*>& closedTrades);
		int getRejectAmount();
		misc::string getRejectMessage();


	private:
		bool isOrderDeleted();
		bool checkAndStoreMessage(IO2GMessageRow *message);
		misc::string IO2GOrderRow2Status(IO2GOrderRow* order);	
				
		
	private:
		char*								MarketCondition;
		IO2GOrderRow*						m_order;
		ExecutionState						m_orderState;
		misc::vector<IO2GTradeRow*>			m_trades;
		misc::vector<IO2GClosedTradeRow*>	m_closedTrades;
		int									m_totalAmount;
		int									m_rejectAmount;
		misc::string						m_rejectMessage;		
		OrderResult							m_result;
		misc::audit							m_audit;
	};
} // namespace



#endif // __fxcmOrderMonitor_hpp__



