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


// c
// c++
// local
#include "stream.hpp"
#include "strconv.hpp"
#include "fxcmOrderMonitor.hpp"



namespace fxcm
{
	bool isOpeningOrder(IO2GOrderRow *order)
	{
		const char* type = order->getType();
		return type[0] == 'O';
	}
	bool isClosingOrder(IO2GOrderRow *order)
	{
		const char* type = order->getType();
		return type[0] == 'C';
	}

	OrderMonitor::OrderMonitor()
	{
		m_order = 0;
		Reset();
		m_audit = misc::audit("responselistener.txt", std::ios::app | std::ios::out);
	}

	OrderMonitor::~OrderMonitor()
	{
		Reset();
	}

	void OrderMonitor::SetOrder(IO2GOrderRow* order)
	{
		Reset();
		m_order = order;
		m_order->addRef();
	}

	bool OrderMonitor::IsActive() const
	{
		return (m_order != 0);
	}

	void OrderMonitor::Reset()
	{
		MarketCondition = "5";
		m_result = OrderExecuting;
		m_rejectMessage.clear();

		for(size_t i = 0; i < m_trades.size(); ++i)
		{
			m_trades[i]->release();
		}
		m_trades.clear();

		for(size_t i = 0; i < m_closedTrades.size(); ++i)
		{
			m_closedTrades[i]->release();
		}
		m_closedTrades.clear();
		m_totalAmount = 0;
		m_rejectAmount = 0;

		if(m_order)
			m_order->release();
		m_order = 0;		
		m_orderState = Executing;
	}

	OrderMonitor::OrderResult OrderMonitor::getResult()
	{
		return m_result;
	}

	OrderMonitor::ExecutionState OrderMonitor::getState()
	{
		return m_orderState;
	}

	void OrderMonitor::onTradeAdded(IO2GTradeRow *trade)
	{
		misc::string tradeOrderID = trade->getOpenOrderID();
		misc::string orderID = m_order->getOrderID();
		if(tradeOrderID != orderID)
		{
			misc::string str("OrderID is incorrect! throw");
			AUDIT(m_audit, str.c_str());
			throw misc::exception(str.c_str());
		}
		
		//AUDIT(m_audit, "Added Open Trade.");

		trade->addRef();
		m_trades.push_back(trade);


		// Totally unpredictable the order of notifications!!!
		if(isOrderDeleted() && isAllTradesReceived())
		{
			m_result = OrderFinished;
		}
	}

	void OrderMonitor::onClosedTradeAdded(IO2GClosedTradeRow *closedTrade)
	{
		misc::string closedTradeOrderID = closedTrade->getCloseOrderID();
		misc::string orderID = m_order->getOrderID();
		if(closedTradeOrderID != orderID)
		{
			misc::string str("OrderID is incorrect! throw");
			AUDIT(m_audit, str.c_str());
			throw misc::exception(str.c_str());
		}


		//AUDIT(m_audit, "Added Closed Trade.");

		closedTrade->addRef();
		m_closedTrades.push_back(closedTrade);


		// Totally unpredictable the order of notifications!!!
		if(isOrderDeleted() && isAllTradesReceived())
		{
			m_result = OrderFinished;
		}
	}

	/*	The order must have the state: 
	 *	F - Executed    : the order has filled entire amount
	 *	C - Cancelled   : the order is not filled
	 *	
	 *	If the order state is anything else an exception is thrown.
	 *	Since the failed order is deleted, there will be no other update for
	 *	onOrderDelete.
	 */
	void OrderMonitor::onOrderDeleted(IO2GOrderRow *order)
	{
		misc::string deletedOrderID = order->getOrderID();

		if(deletedOrderID != m_order->getOrderID())
		{
			AUDIT(m_audit, "Incorrect order passed to OrderMonitor! throw");
			throw misc::exception("Incorrect order passed to OrderMonitor!");
		}

	
		// http://www.fxcodebase.com/documents/ForexConnectAPI/IO2GOrderRow.getStatus.html
		char status = *(order->getStatus());
		if( status == 'W' || 
			status == 'P' ||
			status == 'I' ||
			status == 'Q' ||
			status == 'U' ||
			status == 'E' ||
			status == 'R' ||
			status == 'T' ||
			status == 'G')
		{
			misc::string str("Unexpected order type! ");
			str += IO2GOrderRow2Status(order);
			str += " throw";
			AUDIT(m_audit, str.c_str());

			throw misc::exception("Unexpected order type!");
		}
		
			
		//AUDIT(m_audit, IO2GOrderRow2Status(order).c_str());

		if(status == 'C')
		{
			m_orderState = Cancelled;
			m_rejectAmount = order->getAmount();
			m_totalAmount = order->getOriginAmount() - m_rejectAmount;

			// obviously not the entire amount is executed.
			misc::string txt("OrderCanceled - ");
			txt += "Amount origin: ";
			txt += misc::from_value(order->getOriginAmount());
			txt += " executed: ";
			txt += misc::from_value(m_totalAmount);
			txt += " rejected: ";
			txt += misc::from_value(m_rejectAmount);

			AUDIT(m_audit, txt.c_str());
		}
		else if(status == 'R')
		{		
			m_orderState = Rejected;
			m_rejectAmount = order->getAmount();
			m_totalAmount = order->getOriginAmount() - m_rejectAmount;

			// rejected totally or partially
			misc::string txt("OrderRejected - ");
			txt += "Amount origin: ";
			txt += misc::from_value(order->getOriginAmount());
			txt += " executed: ";
			txt += misc::from_value(m_totalAmount);
			txt += " rejected: ";
			txt += misc::from_value(m_rejectAmount);

			AUDIT(m_audit, txt.c_str());

			if(m_rejectMessage.empty())
				AUDIT(m_audit, "Reject message did not arrive yet!");
		}
		else if(status == 'F')
		{
			m_orderState = Executed;
			m_rejectAmount = 0;
			m_totalAmount = order->getOriginAmount();			
		}
		else
		{
			misc::string txt("Unexpected Order Status! throw");
			AUDIT(m_audit, txt.c_str());
			throw misc::exception(txt.c_str());
		}

		if(isOrderDeleted() && isAllTradesReceived())
		{
			m_result = OrderFinished;
		}

		// success		
	}

	void OrderMonitor::onMessageAdded(IO2GMessageRow *message)
	{
		message;
		//if (m_result == OrderRejected ||
		//	m_result == OrderExecuting)
		//{
		//	bool isRejectMessage = checkAndStoreMessage(message);
		//	isRejectMessage;
		//	if (m_result == OrderRejected && isRejectMessage)
		//		setResult(true);
		//}
	}

	bool OrderMonitor::isOrderDeleted()
	{
		return	(m_orderState == Cancelled ||
			m_orderState == Rejected ||
			m_orderState == Executed);
	}

	bool OrderMonitor::checkAndStoreMessage(IO2GMessageRow *message)
	{
		misc::string feature;
		feature = message->getFeature();
		if(feature == MarketCondition)
		{
			misc::string text = message->getText();
			size_t findPos = text.find(m_order->getOrderID());
			if(findPos != misc::string::npos)
			{
				m_rejectMessage = message->getText();
				return true;
			}
		}
		return false;
	}

	misc::string OrderMonitor::IO2GOrderRow2Status(IO2GOrderRow* order)
	{
		switch(*(order->getStatus()))
		{
		case 'W': return "Order status 'W' is 'waiting'";
		case 'P': return "Order status 'P' is 'In process'";
		case 'I': return "Order status 'I' is 'Dealer intervention'";
		case 'Q': return "Order status 'Q' is 'Requoted'";
		case 'U': return "Order status 'U' is 'Pending calculated'";
		case 'E': return "Order status 'E' is 'Executing'";
		case 'C': return "Order status 'C' is 'Cancelled'";
		case 'R': return "Order status 'R' is 'Rejected'";
		case 'T': return "Order status 'T' is 'Expired'";
		case 'F': return "Order status 'F' is 'Executed'";
		case 'G': return "Order status 'G' is 'Not Available'";
		default:  return "Order status 'none' is in default section! throw";
		}
	}

	
	/*	Use: 
	 *	O2GPtr<IO2GOrderRow> order = m_orderMonitor->getOrder();
	 */
	IO2GOrderRow* OrderMonitor::getOrder()
	{
		// Order is NULL when request failed.
		if(m_order)
		{
			m_order->addRef();
		}		
		return m_order;
	}

	void OrderMonitor::getOpenTrades(misc::vector<IO2GTradeRow*>& trades)
	{
		trades.clear();
		trades.resize(m_trades.size());
		misc::copy(m_trades.begin(), m_trades.end(), trades.begin());
		for(size_t i = 0; i < m_trades.size(); ++i)
		{
			m_trades[i]->addRef();
		}
	}

	void OrderMonitor::getClosedTrades(misc::vector<IO2GClosedTradeRow*>& closedTrades)
	{
		closedTrades.clear();
		closedTrades.resize(m_closedTrades.size());
		misc::copy(m_closedTrades.begin(), m_closedTrades.end(), closedTrades.begin());
		for(size_t i = 0; i < m_closedTrades.size(); ++i)
		{
			m_closedTrades[i]->addRef();
		}
	}

	int OrderMonitor::getRejectAmount()
	{
		return m_rejectAmount;
	}

	misc::string OrderMonitor::getRejectMessage()
	{
		return m_rejectMessage;
	}

	bool OrderMonitor::isAllTradesReceived()
	{
		int currentTotalAmount = 0;
		for(size_t i = 0; i < m_trades.size(); ++i)
			currentTotalAmount += m_trades[i]->getAmount();

		for(size_t i = 0; i < m_closedTrades.size(); ++i)
			currentTotalAmount += m_closedTrades[i]->getAmount();

		return currentTotalAmount == m_totalAmount;
	}

}; // namespace