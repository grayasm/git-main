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
		// m_trades; - empty
		// m_closedTrades; - empty
	}

	long ResponseListener4MarketOrders::addRef()
	{
		sys::autocritical_section autocs(m_CriticalSection);
		m_RefCount++;
		return m_RefCount;
	}

	long ResponseListener4MarketOrders::release()
	{
		// protect m_CriticalSection against 'delete this'
		{
			sys::autocritical_section autocs(m_CriticalSection);
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
			stl::cout << __FUNCTION__ 
				<< ": The request has been failed. ID: "
				<< requestId << " : " << error << std::endl;
			m_ResponseEvent.unlock();
		}
	}

	void ResponseListener4MarketOrders::onTablesUpdates(IO2GResponse* tablesUpdates)
	{
		if (!tablesUpdates)
		{
			stl::cout << __FUNCTION__
				<< ": IO2GResponse is NULL" << std::endl;
			return;
		}

		O2G2Ptr<IO2GResponseReaderFactory> readerFactory =
			m_Session->getResponseReaderFactory();
		if (!readerFactory)
		{
			stl::cout << __FUNCTION__
				<< ": Cannot create response reader factory" << std::endl;
			return; // ErrorCodes::ERR_NO_RESPONSE_READER_FACTORY;
		}
		
		O2G2Ptr<IO2GTablesUpdatesReader> reader =
			readerFactory->createTablesUpdatesReader(tablesUpdates);
		if (!reader)
		{
			stl::cout << __FUNCTION__
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
						stl::cout << "The order has been added. OrderID='" << order->getOrderID() << "', "
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
						stl::cout << "The order has been deleted. OrderID='" << order->getOrderID() << "'"
							<< std::endl;
						m_OrderMonitor->OnOrderDeleted(order);

						if (m_OrderMonitor->IsOrderCompleted())
						{
							SetResult();

							delete m_OrderMonitor;
							m_OrderMonitor = NULL;

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
							SetResult();

							delete m_OrderMonitor;
							m_OrderMonitor = NULL;

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
							SetResult();

							delete m_OrderMonitor;
							m_OrderMonitor = NULL;

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
							SetResult();

							delete m_OrderMonitor;
							m_OrderMonitor = NULL;

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

					stl::cout << "The balance has been changed. AccountID=" << account->getAccountID() << ", "
						<< "Balance=" << std::fixed << account->getBalance() << std::endl;
				}
			}
			break;
			} // switch
		} // for (int i,.)
	}

	void ResponseListener4MarketOrders::SetRequestID(const stl::string& requestID)
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

	const stl::vector<IO2GTradeRow*>& ResponseListener4MarketOrders::GetTrades() const
	{
		return m_trades;
	}

	const stl::vector<IO2GClosedTradeRow*> ResponseListener4MarketOrders::GetClosedTrades() const
	{
		return m_closedTrades;
	}

	void ResponseListener4MarketOrders::ClearResult()
	{
		for (size_t i = 0; i < m_trades.size(); ++i)
			m_trades[i]->release();

		for (size_t i = 0; i < m_closedTrades.size(); ++i)
			m_closedTrades[i]->release();

		m_trades.clear();
		m_closedTrades.clear();
	}

	void ResponseListener4MarketOrders::SetResult()
	{
		if (m_OrderMonitor)
		{
			// clear all previous trades (if any)
			ClearResult();

			// set the result
			OrderMonitor::ExecutionResult result = m_OrderMonitor->GetResult();
			O2G2Ptr<IO2GOrderRow> order = m_OrderMonitor->GetOrder();
			std::string orderID = order->getOrderID();
			

			switch (result)
			{
			case OrderMonitor::Canceled:
			{
				if (m_trades.size() > 0)
				{
					m_OrderMonitor->GetTrades(m_trades);
					m_OrderMonitor->GetClosedTrades(m_closedTrades);

					stl::cout << "A part of the order has been canceled. "
						<< "Amount = " << m_OrderMonitor->GetRejectAmount() << std::endl;
				}
				else
				{
					stl::cout << "The order: OrderID = " << orderID << " has been canceled" << std::endl;
					stl::cout << "The cancel amount = " << m_OrderMonitor->GetRejectAmount() << std::endl;
				}
			}
			break;
			case OrderMonitor::FullyRejected:
			{
				stl::cout << "The order has been rejected. OrderID = " << orderID << std::endl;
				stl::cout << "The rejected amount = " << m_OrderMonitor->GetRejectAmount() << std::endl;
				stl::cout << "Rejection cause: " << m_OrderMonitor->GetRejectMessage().c_str() << std::endl;
			}
			break;
			case OrderMonitor::PartialRejected:
			{
				m_OrderMonitor->GetTrades(m_trades);
				m_OrderMonitor->GetClosedTrades(m_closedTrades);

				stl::cout << "A part of the order has been rejected. "
					<< "Amount = " << m_OrderMonitor->GetRejectAmount() << std::endl;
				stl::cout << "Rejection cause: " << m_OrderMonitor->GetRejectMessage().c_str() << std::endl;
			}
			break;
			case OrderMonitor::Executed:
			{
				m_OrderMonitor->GetTrades(m_trades);
				m_OrderMonitor->GetClosedTrades(m_closedTrades);
			}
			break;
			}
		}
	} // SetResult
	
} // namespace
