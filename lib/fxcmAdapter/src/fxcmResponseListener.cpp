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


#include "fxcmResponseListener.hpp"

// C / C++
#include <math.h>
#include <sstream>
#include <iomanip>

// local
#include "strconv.hpp"
#include "autocritical_section.hpp"
#include "fxcmOrderMonitor.hpp"


#define RESPONSETIMEOUT 120000

namespace fxcm
{
	/*	Use the autocritical_section to automatically lock/unlock access.
	 *	Broker calls only the virtual methods (need auto lock/unlock)
	 *	Main thread calls all the other methods, except the virtual ones (need
	 *	Lock/Unlock)
	 */
	ResponseListener::ResponseListener()
	{
		//	Can still call const functions of this instance.
		Init();
	}

	ResponseListener::ResponseListener(IO2GSession* session)
	{
		Init();

		m_session = session;
		m_session->addRef();
		m_refCount = 1;

		m_audit = misc::audit("responselistener.txt");
	}

	ResponseListener::~ResponseListener()
	{
		Destroy();
	}

	/** Request execution completed data handler. */
	void ResponseListener::onRequestCompleted(const char* requestId, IO2GResponse* response)
	{
		misc::autocritical_section lock(m_refCriticalSection);

		if(m_requestID != requestId)
			return ;

		misc::string txt("\nrequestId: ");
		txt += requestId;
		txt += " ";
		txt += IO2GResponse2String(response);

		// AUDIT(m_audit, txt.c_str());

		if(response && m_requestID == requestId)
		{
			m_response = response;
			m_response->addRef();
			m_requestStatus = RequestCompleted;
			
			O2GResponseType rtype = response->getType();
			if( rtype == GetOffers )
			{
				/* Since we got an official request for quotes, we can allow
				 * Quote Update from Offers Table to be updated from now on.
				 */
				m_bAllowQuotes = true;
			}


			/*	Respond only to certain types of requests.
			 *	Block everything else just to notice what and when it is requested.
			 */
			if( rtype == GetTrades ||
				rtype == GetOffers )
			{
				m_event.setevent();
			}
		}
	}

	/** Request execution failed data handler. */
	void ResponseListener::onRequestFailed(const char* requestId , const char* error)
	{
		misc::autocritical_section lock(m_refCriticalSection);

		if(m_requestID != requestId)
			return;

		m_requestStatus = RequestFailed;
		misc::string txt(requestId);
		if(error)
		{
			txt += " Error: ";
			txt += error;
		}

		AUDIT(m_audit, txt.c_str());

		misc::cout << "\nThe request has been failed. ID: " << requestId << " : " << error;

		// TODO: test with invalid order type, limit, stop, anything!!, and see if the order is deleted.
		m_event.setevent();
	}
	
	void ResponseListener::onTablesUpdates(IO2GResponse* response)
	{
		misc::autocritical_section lock(m_refCriticalSection);

		/*	Offers (EUR/USD, GBP/USD, ITA40, GER30, etc) are updated whenever
		 *	new quotes are available. Don't need a match on the request id.
		 *	
		 *	If another program opens a market order with this account, all
		 *	notifications are sent here too. We need a match for request id.
		 *	
		 *	Account balance updates are allowed but they don't mean anything,
		 *	so checking request id is not that important.
		 *	
		 *	Error Messages or any other messages are not that important. When
		 *	a request fails (request id matches) we inform the session immediately.
		 *	
		 *	Summary is not usually followed. Good to have it for UI but not for
		 *	core computation.
		 */

		misc::string txt;
		
		if(!response)
		{
			misc::cout << "\nonTablesUpdates(NULL) received null data!";
			txt += "IO2GResponse* data is NULL";
			AUDIT(m_audit, txt.c_str());
			
			return;
		}

		// factory
		O2G2Ptr<IO2GResponseReaderFactory> factory = m_session->getResponseReaderFactory();
		if(!factory)
		{
			misc::cout << "\ngetResponseReaderFactory() returned NULL";

			txt += " getResponseReaderFactory() returned NULL";
			AUDIT(m_audit, txt.c_str());

			return;
		}
		// reader
		O2G2Ptr<IO2GTablesUpdatesReader> reader = factory->createTablesUpdatesReader(response);
		if(!reader)
		{
			misc::cout << "\ncreateTablesUpdatesReader() returned NULL";
			txt += " createTablesUpdatesReader() returned NULL";
			AUDIT(m_audit, txt.c_str());

			return;
		}


		txt += "\n\tIO2GResponse* ";
		txt += IO2GResponse2String(response);
		txt += "\n\ttables update reader size = ";
		txt += misc::from_value(reader->size());

		// AUDIT(m_audit, txt.c_str());

		for(int i = 0; i < reader->size(); ++i)
		{
			misc::string txti;
			switch(reader->getUpdateTable(i))
			{
			case TableUnknown:	// -1
				{
					txti += "TableUnknown";
					AUDIT(m_audit, txti.c_str());
					break;
				}
			case Offers:		// = 0,
				{
					txti += "Offers";
					UpdateOffers(reader, i);
					break;
				}
			case Accounts:		// = 1,
				{
					txti += "Accounts";
					UpdateAccounts(reader, i);
					break;
				}
			case Orders:		// = 2,
				{
					txti += "Orders";
					UpdateOrders(reader, i);
					break;
				}
			case Trades:		// = 3,
				{
					txti += "Trades";
					UpdateOpenTrades(reader, i);
					break;
				}
			case ClosedTrades:	// = 4,
				{
					txti += "ClosedTrades";
					UpdateClosedTrades(reader, i);
					break;
				}
			case Messages:		// = 5,
				{
					txti += "Messages";
					UpdateMessages(reader, i);
					break;
				}	
			case Summary:		// = 6
				{
					txti += "Summary";
					break;
				}
			default:
				{
					txti += "Table not defined!! (critical)";
					AUDIT(m_audit, txti.c_str());
					break;
				}
			}
			// AUDIT(m_audit, txti.c_str());
		}
	}

	/** Increase reference counter. */
	long ResponseListener::addRef()
	{
		//AUDIT(m_audit, "");

		misc::autocritical_section lock(m_refCriticalSection);
		//m_refCriticalSection.lock();
		++m_refCount;
		//m_refCriticalSection.unlock();
		return m_refCount;
	}

	/** Decrease reference counter. */
	long ResponseListener::release()
	{
		//AUDIT(m_audit, "");

		misc::autocritical_section lock(m_refCriticalSection);
		//m_refCriticalSection.lock();
		--m_refCount;
		//m_refCriticalSection.unlock();
		return m_refCount;
	}

	void ResponseListener::SetRequestID(const char* sRequestID)
	{
		//misc::string txt(sRequestID);
		//AUDIT(m_audit, txt.c_str());
		
		Reset();
		m_requestID = sRequestID;
	}

	bool ResponseListener::WaitEvents()
	{
		return (m_event.trylock(RESPONSETIMEOUT) == 1);
	}


	// USE: O2G2Ptr<IO2GResponse> response = responseListener->GetResponse();
	IO2GResponse* ResponseListener::GetResponse()
	{
		if (m_response)
			m_response->addRef();
		return m_response;
	}

	OrderMonitor& ResponseListener::GetOrderMonitor()
	{
		return m_orderMonitor;
	}

	misc::critical_section& ResponseListener::GetCriticalSection()
	{
		return m_refCriticalSection;
	}

	ResponseListener::Quotes& ResponseListener::GetQuotes()
	{
		return m_quotes;
	}

	void ResponseListener::Reset()
	{
		m_requestID.clear();
		m_orderMonitor.Reset();
		if(m_response)
		{
			m_response->release();
			m_response = NULL;
		}
		m_requestStatus = RequestReady;
		m_event.resetevent();
	}

	ResponseListener::RequestStatus ResponseListener::GetRequestStatus()
	{
		return m_requestStatus;
	}

	void ResponseListener::Init()
	{
		m_refCount = 0;
		m_session = NULL;
		m_requestID.clear();
		m_response = NULL;
		m_requestStatus = RequestReady;
		m_bAllowQuotes = false;
		InitTradables();
	}

	void ResponseListener::Destroy()
	{
		if(m_response)
			m_response->release();
		m_requestStatus = RequestReady;
		if(m_session)
			m_session->release();
		m_refCount = 0;
		m_requestID = "";
	}

	void ResponseListener::UpdateOffers(IO2GTablesUpdatesReader* reader, int index)
	{
		/*	Quotes updates are allowed after an explicit request made first
		 *	from session. If the request is received, we have confirmation
		 *	that quotes are needed further in this session.
		 */
		if(!m_bAllowQuotes)
			return;

		O2G2Ptr<IO2GOfferRow> offer = reader->getOfferRow(index);
		// low spread, no slippage, Mon-Fri tradable
		if(!IsOfferTradable(offer))
			return;

		// has errors
		if(!IsOfferValid(offer))
		{
			// reset
			m_bAllowQuotes = false;
			m_quotes.clear();
			return;
		}

		// take the offer (considered valid)
		m_quotes[offer->getInstrument()] = fx::Price(offer->getAsk(), offer->getBid());
	}

	void ResponseListener::UpdateOrders(IO2GTablesUpdatesReader* reader, int index)
	{
		O2G2Ptr<IO2GOrderRow> order = reader->getOrderRow(index);

		//AUDIT(m_audit, IO2GOrderRow2String(order).c_str());

		/*	When 2 or more instances work on the same account, checking
		 *	the request ID is critical to reject orders that were not
		 *	requested here.
		 */
		if(m_requestID != order->getRequestID())
			return;

		misc::string type = order->getType();
		if(type == "SE" || type == "LE")
		{
			UpdateEntryOrders(reader, order, index);
		}
		else if(type == "OM" || type == "CM")
		{
			UpdateMarketOrders(reader, order, index);
		}
		else
		{
			misc::cout << "\nUnknown order type!";
		}
	}

	void ResponseListener::UpdateEntryOrders(IO2GTablesUpdatesReader* reader, IO2GOrderRow* order, int index)
	{
		O2GTableUpdateType type = reader->getUpdateType(index);
		if(type != Insert)
			return;

		if(m_requestID != order->getRequestID())
			return;

		misc::cout << "\nThe order has been added. " << 
						"OrderID='" << order->getOrderID() << "', " << 
						"Type='" << order->getType() << "', " << 
						"BuySell='" << order->getBuySell() << "', " << 
						"Rate='" << order->getRate() << "', " << 
						"TimeInForce='" << order->getTimeInForce() << "'";

		m_orderMonitor.SetOrder(order);

		m_event.setevent();
	}

	void ResponseListener::UpdateMarketOrders(IO2GTablesUpdatesReader* reader, IO2GOrderRow* order, int index)
	{
		O2GTableUpdateType type = reader->getUpdateType(index);
		//AUDIT(m_audit, O2GTableUpdateType2String(&type).c_str());

		if(type == Insert)
		{
			misc::cout << "\nThe order has been added." <<
							"OrderID='" << order->getOrderID() << "', " << 
							"Rate='" << order->getRate() << "', " << 
							"TimeInForce='" << order->getTimeInForce() << "'" << std::endl;
			
			// TODO: dereferencing members of OrderMonitor;
			m_orderMonitor.SetOrder(order);
		}
		else if(type == Delete)
		{
			if(!m_orderMonitor.IsActive())
			{
				misc::string txt("OrderMonitor::IsActive returned false! throw");
				AUDIT(m_audit, txt.c_str());
				throw misc::exception(txt.c_str());
			}

			if(!Eq(m_orderMonitor.getOrder(), order))
			{
				misc::string txt("OrderMonitor contains a different OrderID! throw");
				AUDIT(m_audit, txt.c_str());
				throw misc::exception(txt.c_str());
			}
			
			misc::cout << "\nThe order has been deleted. " << 
							"OrderID='" << order->getOrderID() << "'";

			m_orderMonitor.onOrderDeleted(order);
			if(m_orderMonitor.getResult() == OrderMonitor::OrderFinished)
			{
				PrintResult();
				m_event.setevent();
			}

			//if(m_orderMonitor.isOrderCompleted())
			//{
			//	PrintResult();
			//	m_event.setevent();
			//}
		
		}
		else if(type == Update)
		{
			if(!m_orderMonitor.IsActive())
			{
				misc::string str("Unexpected invalid OrderMonitor! throw");
				AUDIT(m_audit, str.c_str());
				throw misc::exception(str.c_str());
			}

			if(!Eq(m_orderMonitor.getOrder(), order))
			{
				misc::string str("OrderMonitor contains a different OrderID! throw");
				AUDIT(m_audit, str.c_str());
				throw misc::exception(str.c_str());
			}

			// TODO: what to update ?
		}
	}

	void ResponseListener::UpdateOpenTrades(IO2GTablesUpdatesReader* reader, int index)
	{
		O2GTableUpdateType type = reader->getUpdateType(index);
		//AUDIT(m_audit, O2GTableUpdateType2String(&type).c_str());
		if(type != Insert)
			return;

		O2G2Ptr<IO2GTradeRow> trade = reader->getTradeRow(index);
		if(!trade)
			return;

		/*	When another program (TS2, fxmon, MT4) operates on this account
		 *	opening trades will be notified here too. We need to find if
		 *	this incoming trade is requested by this process or not.
		 */
		if(!m_orderMonitor.IsActive())
			return;

		// m_requestId, OrderMonitor and Trade
		O2G2Ptr<IO2GOrderRow> order = m_orderMonitor.getOrder();
		misc::string requestId = order->getRequestID();
		if(m_requestID != requestId)
			return;
		misc::string tradeOORequestId = trade->getOpenOrderReqID();
		if(m_requestID != tradeOORequestId)
			return;

		// request is confirmed, proceed.

		m_orderMonitor.onTradeAdded(trade);

		if(m_orderMonitor.getResult() == OrderMonitor::OrderFinished)
		{
			PrintResult();
			m_event.setevent();
		}
	}

	void ResponseListener::UpdateClosedTrades(IO2GTablesUpdatesReader* reader, int index)
	{
		O2GTableUpdateType type = reader->getUpdateType(index);
		//AUDIT(m_audit, O2GTableUpdateType2String(&type).c_str());
		if(type != Insert)
			return;

		O2G2Ptr<IO2GClosedTradeRow> closedTrade = reader->getClosedTradeRow(index);
		if(!closedTrade)
			return;

		/*	When another program (TS2, fxmon, MT4) operates on this account
		 *	closing trades will be notified here too. We need to find if
		 *	this incoming trade is requested by this process or not.
		 */
		if(!m_orderMonitor.IsActive())
			return;

		O2G2Ptr<IO2GOrderRow> order = m_orderMonitor.getOrder();
		misc::string requestId = order->getRequestID();
		if(m_requestID != requestId)
			return;
		misc::string tradeCORequestId = closedTrade->getCloseOrderReqID();
		if(m_requestID != tradeCORequestId)
			return;

		// request is confirmed, proceed.
				
		m_orderMonitor.onClosedTradeAdded(closedTrade);

		if(m_orderMonitor.getResult() == OrderMonitor::OrderFinished)
		{
			PrintResult();
			m_event.setevent();
		}
	}

	void ResponseListener::UpdateMessages(IO2GTablesUpdatesReader* reader, int index)
	{
		O2GTableUpdateType type = reader->getUpdateType(index);
		if(type != Insert)
			return;

		AUDIT(m_audit, O2GTableUpdateType2String(&type).c_str());

		//O2G2Ptr<IO2GMessageRow> message = reader->getMessageRow(index);
		//if(!m_orderMonitor.IsActive())
		//{
		//	misc::string str("Invalid OrderMonitor member! throw");
		//	AUDIT(m_audit, str.c_str());
		//	throw misc::exception(str.c_str());
		//}
		//
		//m_orderMonitor.onMessageAdded(message);

		//if (m_orderMonitor.isOrderCompleted())
		//{
		//	PrintResult();
		//	m_event.setevent();
		//}
	}

	void ResponseListener::UpdateAccounts(IO2GTablesUpdatesReader* reader, int index)
	{
		O2GTableUpdateType type = reader->getUpdateType(index);

		//AUDIT(m_audit, O2GTableUpdateType2String(&type).c_str());

		if(type != Update)
			return;

		O2GTable table = reader->getUpdateTable(index);
		if(table != Accounts)
			return;

		O2G2Ptr<IO2GAccountRow> account = reader->getAccountRow(index);
		misc::cout << "\nThe balance has been changed. " << 
						"AccountID=" << account->getAccountID() << ", " << 
						"Balance=" << std::fixed << account->getBalance();
	}

	void ResponseListener::PrintResult()
	{
		if(m_orderMonitor.IsActive())
		{
			OrderMonitor::ExecutionState result = m_orderMonitor.getState();
			misc::vector<IO2GTradeRow*> trades;
			misc::vector<IO2GClosedTradeRow*> closedTrades;
			O2G2Ptr<IO2GOrderRow> order = m_orderMonitor.getOrder();
			misc::string orderID = order->getOrderID();
			m_orderMonitor.getOpenTrades(trades);
			m_orderMonitor.getClosedTrades(closedTrades);

			switch(result)
			{
			case OrderMonitor::Cancelled:
				{
					if(trades.size() > 0)
					{
						//PrintTrades(trades, orderID);
						//PrintClosedTrades(closedTrades, orderID);
						misc::string txt("\nA part of the order has been canceled. Amount= ");
						txt += misc::from_value(m_orderMonitor.getRejectAmount());
						misc::cout << txt.c_str();
						AUDIT(m_audit, txt.c_str());
					}
					else
					{
						misc::string txt("\nEntire Order= ");
						txt += orderID;
						txt += " has been canceled. Amount= ";
						txt += misc::from_value(m_orderMonitor.getRejectAmount());

						misc::cout << txt.c_str();
						AUDIT(m_audit, txt.c_str());
					}
				}
				break;
			case OrderMonitor::Rejected:
				{
					misc::string txt("\nOrder= ");
					txt += orderID;
					txt += " has been rejected. Amount= ";
					txt += misc::from_value(m_orderMonitor.getRejectAmount());
					txt += "\nRejection cause= ";
					txt += m_orderMonitor.getRejectMessage();

					misc::cout << txt.c_str();
					AUDIT(m_audit, txt.c_str());
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

	void ResponseListener::PrintTrades(misc::vector<IO2GTradeRow*>& trades, const misc::string& sOrderID)
	{
		if(trades.size() == 0)
			return;

		misc::cout << "\nPrintTrades";
		misc::cout << "\nNew Order: " << sOrderID << " New Trades: ";
		for(size_t i = 0; i < trades.size(); ++i)
		{
			O2G2Ptr<IO2GTradeRow> trade = trades[i];
			misc::string tradeID = trade->getTradeID();
			int amount = trade->getAmount();
			double rate = trade->getOpenRate();
			misc::cout << "\nTrade= " << tradeID << ", " << 
							"Amount= " << amount << ", " <<
							"Rate= " << rate;
		}
	}

	void ResponseListener::PrintClosedTrades(misc::vector<IO2GClosedTradeRow*>& closedTrades, const misc::string& sOrderID)
	{
		if(closedTrades.size() == 0)
			return;

		misc::cout << "\nPrintClosedTrades";
		misc::cout << "\nNew Order: " << sOrderID << " New Trades: ";
		for(size_t i = 0; i < closedTrades.size(); ++i)
		{
			IO2GClosedTradeRow *closedTrade = closedTrades[i];
			misc::string tradeID = closedTrade->getTradeID();
			int amount = closedTrade->getAmount();
			double rate = closedTrade->getCloseRate();
			misc::cout << "\nClosed Trade= " << tradeID << ", " <<
							"Amount= " << amount << ", " <<
							"Closed Rate= " << rate;
			closedTrade->release();
		}
	}

	misc::string ResponseListener::IO2GResponse2String(IO2GResponse* response) const
	{
		misc::string str;
		str += "IO2GResponse*";
		str += " ";

		if(!response)
		{
			str += " NULL";
			return str;
		}

		str += " type-";
		switch(response->getType())
		{
		case ResponseUnknown:		// = -1,
			{
				str += "ResponseUnknown";
				break;
			}
		case TablesUpdates:			// = 0,
			{
				str += "TablesUpdates";
				break;
			}
		case MarketDataSnapshot:	// = 1,
			{
				str += "MarketDataSnapshot";
				break;
			}
		case GetAccounts:			// = 2,
			{
				str += "GetAccounts";
				break;
			}
		case GetOffers:				// = 3,
			{
				str += "GetOffers";
				break;
			}
		case GetOrders:				// = 4,
			{
				str += "GetOrders";
				break;
			}
		case GetTrades:				// = 5,
			{
				str += "GetTrades";
				break;
			}
		case GetClosedTrades:		// = 6,
			{
				str += "GetClosedTrades";
				break;
			}
		case GetMessages:			// = 7,
			{
				str += "GetMessages";
				break;
			}
		case CreateOrderResponse:	// = 8,
			{
				str += "CreateOrderResponse";
				break;
			}
		case GetSystemProperties:	// = 9,
			{
				str += "GetSystemProperties";
				break;
			}
		case CommandResponse:		// = 10,
			{
				str += "CommandResponse";
				break;
			}
		case MarginRequirementsResponse:	// = 11,
			{
				str += "MarginRequirementsResponse";
				break;
			}
		case GetLastOrderUpdate:	// = 12,
			{
				str += "GetLastOrderUpdate";
				break;
			}
		default:
			{
				str += "default";
				break;
			}
		} // switch

		str += " - ";
		str += response->getRequestID();
		
		return str;
	}

	misc::string ResponseListener::IO2GOfferRow2String(IO2GOfferRow* offer) const
	{
		misc::string str("IO2GOfferRow* ");
		if(!offer)
		{
			str += " is NULL";
			return str;
		}
		
		str += offer->getInstrument();
		str += " B= ";
		str += misc::from_value(offer->getAsk(), 5);
		str += " S= ";
		str += misc::from_value(offer->getBid(), 5);
		return str;
	}

	misc::string ResponseListener::IO2GOrderRow2String(IO2GOrderRow* order) const
	{
		misc::string str("IO2GOrderRow* ");
		if(!order)
		{
			str += " is NULL";
			return str;
		}

		str += " type-";
		str += order->getType();
		str += " request-";
		str += order->getRequestID();
		str += " order-";
		str += order->getOrderID();
		str += " trade-";
		str += order->getTradeID();

		return str;
	}

	misc::string ResponseListener::O2GTableUpdateType2String(O2GTableUpdateType* type) const
	{
		misc::string str("We got Message !!!  O2GTableUpdateType-");
		switch(*type)
		{
		case UpdateUnknown:	// = - 1,
			{
				str += "UpdateUnknown";
				break;
			}
		case Insert:		// = 0,
			{
				str += "Insert";
				break;
			}
		case Update:		// = 1,
			{
				str += "Update";
				break;
			}
		case Delete:		// = 2
			{
				str += "Delete";
				break;
			}
		}

		return str;
	}

	bool ResponseListener::Eq(IO2GOrderRow* l, IO2GOrderRow* r) const
	{
		if(strcmp(l->getType(), r->getType()) != 0)
			return false;
		if(strcmp(l->getRequestID(), r->getRequestID()) != 0)
			return false;
		if(strcmp(l->getOrderID(), r->getOrderID()) != 0)
			return false;

		return true;
	}

	bool ResponseListener::IsOfferTradable(IO2GOfferRow* offer) const
	{
		if(offer == NULL)
			return false;
		
		// See InitTradables for explanation.
		Tradables::const_iterator it = 
			misc::find(m_tradables.begin(), m_tradables.end(), offer->getInstrument());
		
		return (it != m_tradables.end());
	}

	bool ResponseListener::IsOfferValid(IO2GOfferRow* offer) const
	{
		/*	Searching for errors from broker side such as wide spread, slippage, 
		 *	impossible values to reach in 1 tick or so, etc.
		 */
		if(offer == NULL)
			return false;

		// ------ validate fxcm broker data -----
		// buy
		bool isAskValid = offer->isAskValid();
		bool isAskTradableValid = offer->isAskTradableValid();
		misc::string askTradable = offer->getAskTradable();// T yes, I view only, N no
		// sell
		bool isBidValid = offer->isBidValid();
		bool isBidTradableValid = offer->isBidTradableValid();
		misc::string bidTradable = offer->getBidTradable();// T yes, I view only, N no
		// trading
		bool isTradingStatusValid = offer->isTradingStatusValid();
		misc::string tradingStatus = offer->getTradingStatus(); // O open, C closed
		bool isInstrumentValid = offer->isInstrumentValid();
		misc::string instrument = offer->getInstrument();

		// continue checking
		bool bValidOffer = true;
		misc::string txt("");
		if(!isBidValid || !isAskValid)
		{
			bValidOffer = false;
			txt += ("\nError: bid/ask invalid. ");
		}

		if(!isBidTradableValid || !isAskTradableValid)
		{
			bValidOffer = false;
			txt += "\nError: bid/askTradable invalid.";
		}

		if(bidTradable != "T" || askTradable != "T")
		{
			bValidOffer = false;
			txt += "\nError: bid/ask price not available for trading.";
		}

		if(!isTradingStatusValid)
		{
			bValidOffer = false;
			txt += "\nError: trading status invalid.";
		}

		if(tradingStatus != "O")
		{
			bValidOffer = false;
			txt += "\nError: trading is not Open.";
		}

		if(!isInstrumentValid)
		{
			bValidOffer = false;
			txt += "\nError: instrument is not valid.";
		}

		//---- validate against other errors (intentional or not) ----
		double pointSize = offer->getPointSize();
		if(!offer->isPointSizeValid())
		{
			bValidOffer = false;
			txt += "\nError: point size is not valid";
			// avoid division by zero
			pointSize = 1;
		}


		// 1) wide spread
		double spread = fabs(offer->getAsk() - offer->getBid()) / pointSize;
		if(spread > MAX_SPREAD)
		{
			bValidOffer = false;
			txt += "\nError: spread ";
			txt += misc::from_value(spread, 1);
			txt += " PL is too wide";
		}
		// 2) slippage - falling off, fail to maintain an expected level
		Quotes::const_iterator it = m_quotes.find(offer->getInstrument());
		if(it != m_quotes.end()) // first time after table is refreshed
		{			
			fx::Price price0 = it->second;
			fx::Price price2(offer->getAsk(), offer->getBid());
			double buyPL = fabs(price2.GetBuy() - price0.GetBuy())/pointSize;
			double sellPL = fabs(price2.GetSell() - price0.GetSell())/pointSize;

			// trying to catch errors in price feed (price manipulation)
			if(buyPL > MAX_SLIPPAGE || sellPL > MAX_SLIPPAGE)
			{
				/*	Discard all moves bigger than 300 PL from last level,
				 *	between 2 consecutive updates.
				 */
				bValidOffer = false;
				txt += "\nError: SLIPPAGE TOO BIG, BUY= ";
				txt += misc::from_value(buyPL, 1);
				txt += " SELL= ";
				txt += misc::from_value(sellPL, 1);
			}
		}

		
		//
		if(!bValidOffer)
		{
			txt += "\n";
			txt += IO2GOfferRow2String(offer);
			AUDIT(m_audit, txt.c_str());
		}

		return bValidOffer;
	}

	void ResponseListener::InitTradables()
	{
		/*	Some currencies have wide spread
		 *	EUR/NOK, USD/SEK, EUR/TRY, USD/MXN, etc
		 *	Other symbols are not traded Mon-Fri, but within some trading hours.
		 *	ESP35, FRA40, GER30, HKG33, ITA40, etc
		 *	
		 *	Only tested and working stable instruments are added to
		 *	tradeable variable, for keeping the plugin safe.
		 */
		m_tradables.clear();
		m_tradables.push_back("EUR/USD");
	}
}; // namespace
