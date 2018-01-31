/*
	Copyright (C) 2018 Mihai Vasilian

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

#include "ResponseListener4MarketOrders.hpp"
#include "autocritical_section.hpp"
#include "stream.hpp"
#include <sstream>
#include "ErrorCodes.hpp"
#include "Utils.hpp"



namespace fxcm
{
	ResponseListener4MarketOrders::ResponseListener4MarketOrders(IO2GSession* session)
	{
		m_Session = session;
		m_Session->addRef();
		m_RefCount = 1;
		// m_ResponseEvent is non-signaled
		m_RequestID = "";
		m_Response = NULL;
		m_OrderMonitor = NULL;
		// m_CriticalSection - is unlocked
	}

	long ResponseListener4MarketOrders::addRef()
	{
		misc::autocritical_section autocs(m_CriticalSection);
		m_RefCount++;
		return m_RefCount;
	}

	long ResponseListener4MarketOrders::release()
	{
		// protect m_CriticalSection against 'delete this'
		{
			misc::autocritical_section autocs(m_CriticalSection);
			m_RefCount--;
			if (m_RefCount)
				return m_RefCount;
		}

		delete this;
		return 0;
	}

	void ResponseListener4MarketOrders::onRequestCompleted(const char* requestId, IO2GResponse* response)
	{
		if (response && m_RequestID == requestId)
		{
			m_Response = response;
			m_Response->addRef();
			if (response->getType() != CreateOrderResponse)
				m_ResponseEvent.unlock();
		}
	}

	void ResponseListener4MarketOrders::onRequestFailed(const char* requestId, const char* error)
	{
		if (m_RequestID == requestId)
		{
			misc::cout << __FUNCTION__ 
				<< ": The request has been failed. ID: "
				<< requestId << " : " << error << std::endl;
			m_ResponseEvent.unlock();
		}
	}

	void ResponseListener4MarketOrders::onTablesUpdates(IO2GResponse* tablesUpdates)
	{
		if (!tablesUpdates)
		{
			misc::cout << __FUNCTION__
				<< ": IO2GResponse is NULL" << std::endl;
			return;
		}

		O2G2Ptr<IO2GResponseReaderFactory> readerFactory =
			m_Session->getResponseReaderFactory();
		if (!readerFactory)
		{
			misc::cout << __FUNCTION__
				<< ": Cannot create response reader factory" << std::endl;
			return; // ErrorCodes::ERR_NO_RESPONSE_READER_FACTORY;
		}
		
		O2G2Ptr<IO2GTablesUpdatesReader> reader =
			readerFactory->createTablesUpdatesReader(tablesUpdates);
		if (!reader)
		{
			misc::cout << __FUNCTION__
				<< ": Cannot create tables response reader" << std::endl;
			return; // ErrorCodes::ERR_NO_RESPONSE_READER;
		}

		for (int i = 0; i < reader->size(); ++i)
		{
			O2GTable updateTable = reader->getUpdateTable(i);
			switch (updateTable)
			{
			case Orders:
			{
				O2G2Ptr<IO2GOrderRow> order = reader->getOrderRow(i);
				if (m_RequestID != order->getRequestID())
					break;

				if (reader->getUpdateType(i) == Insert)
				{
					if ((Utils::IsClosingOrder(order) || Utils::IsOpeningOrder(order)) &&
						m_OrderMonitor == NULL)
					{
						misc::cout << "The order has been added. OrderID='" << order->getOrderID() << "', "
							<< "Rate='" << order->getRate() << "', "
							<< "TimeInForce='" << order->getTimeInForce() << "'"
							<< std::endl;
						m_OrderMonitor = new OrderMonitor(order);
					}
				}
				else if (reader->getUpdateType(i) == Delete)
				{
					if (m_OrderMonitor)
					{
						misc::cout << "The order has been deleted. OrderID='" << order->getOrderID() << "'"
							<< std::endl;
						m_OrderMonitor->OnOrderDeleted(order);

						if (m_OrderMonitor->IsOrderCompleted())
						{
							PrintResult();
							m_ResponseEvent.unlock();
						}
					}
				}
			}
			break;
			case Trades:
			{
				if (reader->getUpdateType(i) == Insert)
				{
					O2G2Ptr<IO2GTradeRow> trade = reader->getTradeRow(i);
					if (m_OrderMonitor)
					{
						m_OrderMonitor->OnTradeAdded(trade);

						if (m_OrderMonitor->IsOrderCompleted())
						{
							PrintResult();
							m_ResponseEvent.unlock();
						}
					}
				}
			}
			break;
			case ClosedTrades:
			{
				if (reader->getUpdateType(i) == Insert)
				{
					O2G2Ptr<IO2GClosedTradeRow> closedTrade = reader->getClosedTradeRow(i);
					if (m_OrderMonitor)
					{
						m_OrderMonitor->OnClosedTradeAdded(closedTrade);

						if (m_OrderMonitor->IsOrderCompleted())
						{
							PrintResult();
							m_ResponseEvent.unlock();
						}
					}
				}
			}
			break;
			case Messages:
			{
				if (reader->getUpdateType(i) == Insert)
				{
					O2G2Ptr<IO2GMessageRow> message = reader->getMessageRow(i);
					if (m_OrderMonitor)
					{
						m_OrderMonitor->OnMessageAdded(message);

						if (m_OrderMonitor->IsOrderCompleted())
						{
							PrintResult();
							m_ResponseEvent.unlock();
						}
					}
				}
			}
			break;
			case Accounts:
			{
				if (reader->getUpdateType(i) == Update && reader->getUpdateTable(i) == Accounts)
				{
					O2G2Ptr<IO2GAccountRow> account = reader->getAccountRow(i);

					misc::cout << "The balance has been changed. AccountID=" << account->getAccountID() << ", "
						<< "Balance=" << std::fixed << account->getBalance() << std::endl;
				}
			}
			break;
			} // switch
		} // for (int i,.)
	}

	void ResponseListener4MarketOrders::SetRequestID(const misc::string& requestID)
	{
		m_RequestID = requestID;
		if (m_Response)
		{
			m_Response->release();
			m_Response = NULL;
		}
		m_ResponseEvent.unlock();
	}

	bool ResponseListener4MarketOrders::WaitEvents()
	{
		return (m_ResponseEvent.trylock(30000) == 0);
	}

	IO2GResponse* ResponseListener4MarketOrders::GetResponse()
	{
		if (m_Response)
			m_Response->addRef();
		return m_Response; // ~O2G2Ptr will release() it.
	}

	ResponseListener4MarketOrders::~ResponseListener4MarketOrders()
	{
		if (m_Response)
			m_Response->release();
		m_Session->release();
		// m_ResponseEvent will CloseHandle itself on ~dtor
	}

	void ResponseListener4MarketOrders::PrintResult() const
	{
		if (m_OrderMonitor)
		{
			misc::vector<IO2GTradeRow*> trades;
			misc::vector<IO2GClosedTradeRow*> closedTrades;

			OrderMonitor::ExecutionResult result = m_OrderMonitor->GetResult();
			O2G2Ptr<IO2GOrderRow> order = m_OrderMonitor->GetOrder();

			misc::string orderID = order->getOrderID();

			m_OrderMonitor->GetTrades(trades);
			m_OrderMonitor->GetClosedTrades(closedTrades);

			switch (result)
			{
			case OrderMonitor::Canceled:
			{
				if (trades.size() > 0)
				{
					PrintTrades(trades, orderID);
					PrintClosedTrades(closedTrades, orderID);

					misc::cout << "A part of the order has been canceled. "
						<< "Amount = " << m_OrderMonitor->GetRejectAmount() << std::endl;
				}
				else
				{
					misc::cout << "The order: OrderID = " << orderID << " has been canceled" << std::endl;
					misc::cout << "The cancel amount = " << m_OrderMonitor->GetRejectAmount() << std::endl;
				}
			}
			break;
			case OrderMonitor::FullyRejected:
			{
				misc::cout << "The order has been rejected. OrderID = " << orderID << std::endl;
				misc::cout << "The rejected amount = " << m_OrderMonitor->GetRejectAmount() << std::endl;
				misc::cout << "Rejection cause: " << m_OrderMonitor->GetRejectMessage() << std::endl;
			}
			break;
			case OrderMonitor::PartialRejected:
			{
				PrintTrades(trades, orderID);
				PrintClosedTrades(closedTrades, orderID);

				misc::cout << "A part of the order has been rejected. "
					<< "Amount = " << m_OrderMonitor->GetRejectAmount() << std::endl;
				misc::cout << "Rejection cause: " << m_OrderMonitor->GetRejectMessage() << std::endl;
			}
			break;
			case OrderMonitor::Executed:
			{
				PrintTrades(trades, orderID);
				PrintClosedTrades(closedTrades, orderID);
			}
			break;
			}
		}
	}

	void ResponseListener4MarketOrders::PrintTrades(const misc::vector<IO2GTradeRow*>& trades, const misc::string& sOrderID) const
	{
		if (trades.size() == 0)
			return;

		misc::cout << "For the order: OrderID=" << sOrderID
			<< " the following positions have been opened: " << std::endl;

		for (size_t i = 0; i < trades.size(); ++i)
		{
			O2G2Ptr<IO2GTradeRow> trade = trades[i];
			misc::string tradeID = trade->getTradeID();
			int amount = trade->getAmount();
			double rate = trade->getOpenRate();

			misc::cout << "Trade ID: " << tradeID << ", "
				<< "Amount: " << amount << ", "
				<< "Rate: " << rate << std::endl;
		}
	}

	void ResponseListener4MarketOrders::PrintClosedTrades(const misc::vector<IO2GClosedTradeRow*>& closedTrades, const misc::string& sOrderID) const
	{
		if (closedTrades.size() == 0)
			return;

		misc::cout << "For the order: OrderID=" << sOrderID
			<< " the following positions have been closed: " << std::endl;

		for (size_t i = 0; i < closedTrades.size(); ++i)
		{
			IO2GClosedTradeRow *closedTrade = closedTrades[i];
			misc::string tradeID = closedTrade->getTradeID();
			int amount = closedTrade->getAmount();
			double rate = closedTrade->getCloseRate();

			misc::cout << "Closed Trade ID: " << tradeID << ", "
				<< "Amount: " << amount << ", "
				<< "Closed Rate: " << rate << std::endl;
			closedTrade->release();
		}
	}

} // namespace
