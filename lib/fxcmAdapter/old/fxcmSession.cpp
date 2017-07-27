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

#include "fxcmSession.hpp"

// c
// c++
// #include <list>
#include <ctime>
#include <cmath>
#include <limits>
#include <iomanip>


// fxcm
#include "ForexConnect.h"
#include "sample_tools.h"


// local
#include "math.hpp"
#include "autocritical_section.hpp"
#include "strconv.hpp"
#include "unistd.hpp" // sleep
#include "fxcmIniParams.hpp"
#include "fxcmSessionListener.hpp"
#include "fxcmResponseListener.hpp"
#include "fxcmTradingSettings.hpp"
#include "fxcmPermission.hpp"
#include "fxcmPipCost.hpp"
#include "fxcmMarketPlugin.hpp"
#include "fxcmSessionHelper.hpp"



namespace fxcm
{
	/*
	 *	To avoid thread collision with ResponseListener we use a critical section.
	 *	This is locked while calling ForexConnect API, and unlocked while sending
	 *	the request, such that the ResponseListener can update its status.
	 */
	Session::Session(const fxcm::IniParams& iniParams)		
	{
		m_iniParams = iniParams;
		m_session = CO2GTransport::createSession();
		
		m_sessionListener = new fxcm::SessionListener(m_session, m_iniParams);
		m_session->subscribeSessionStatus(m_sessionListener);

		m_responseListener = new fxcm::ResponseListener(m_session);
		m_session->subscribeResponse(m_responseListener);

		m_tradingSettings = new fxcm::TradingSettings();
		m_permission = new fxcm::Permission();
	}

	Session::~Session()
	{
		if(!m_sessionListener->IsDisconnected())
		{
			Logout();
		}

		m_session->unsubscribeSessionStatus(m_sessionListener);			
		delete m_sessionListener;
		m_sessionListener = NULL;

		m_session->unsubscribeResponse(m_responseListener);
		delete m_responseListener;
		m_responseListener = NULL;

		delete m_tradingSettings;
		m_tradingSettings = NULL;

		delete m_permission;
		m_permission = NULL;
	}

	bool Session::Connect()
	{
		bool logged = Login();
		if(!logged)
		{
			AUDIT(m_audit, "Login() failed");
			return false;
		}

		if(!m_symbols.empty())
			throw misc::exception("Symbol table must be empty");

		bool bTradingSettings = m_tradingSettings->CheckTradingSettings(m_iniParams, m_session, m_symbols);
		if(!bTradingSettings)
		{
			AUDIT(m_audit, "tradingSettings->CheckTradingSettings failed.");
			return false;
		}

		bool bPermissions = m_permission->LoadPermissions(m_symbols, m_session);
		if(!bPermissions)
		{
			AUDIT(m_audit, "permission->LoadPermissions failed.");
			return false;
		}

		return true;
	}

	bool Session::Disconnect()
	{
		m_symbols.clear();
		m_tradingSettings->Clear();
		m_permission->Clear();
		return Logout();
	}

	bool Session::IsConnected()
	{
		return m_sessionListener->IsConnected();
	}

	bool Session::IsDisconnected()
	{
		return m_sessionListener->IsDisconnected();
	}

	bool Session::GetInstruments(misc::vector<misc::string>& symbols)
	{
		for(size_t i = 0; i < m_symbols.size(); ++i)
		{
			symbols.push_back(m_symbols[i]);
		}
		return true;
	}

	bool Session::GetCurrencies(misc::vector<fx::Currency>& currencies)
	{
		// success
		if(GetCurrenciesImpl(currencies))
			return true;

		// RequestFailed
		if(m_responseListener->GetRequestStatus() == ResponseListener::RequestFailed)
		{
			HandleTimeOut();
		}

		return false;
	}

	bool Session::GetOffer(std::map<misc::string, fx::Price>& quotes)
	{
		// success
		if(GetOfferImpl(quotes))
			return true;

		// RequestFailed
		if(m_responseListener->GetRequestStatus() == ResponseListener::RequestFailed)
		{
			HandleTimeOut();
		}

		return false;
	}

	fx::MarketPlugin::Ptr Session::GetMarketPlugin()
	{
		return new MarketRealPlugin(this);
	}

	bool Session::CreateEntryOrder(
		const fx::Position& posin,
		fx::Position& posout)
	{
		// success
		if(CreateEntryOrderImpl(posin, 0, 0, posout))
			return true;

		// RequestFailed
		if(m_responseListener->GetRequestStatus() == ResponseListener::RequestFailed)
		{
			HandleTimeOut();
		}

		return false;
	}


	bool Session::CreateEntryOrder(
		const fx::Position& posin,
		double rateLimit,
		double rateStop,
		fx::Position& posout)
	{
		// success
		if(CreateEntryOrderImpl(posin, rateLimit, rateStop, posout))
			return true;

		// RequestFailed
		if(m_responseListener->GetRequestStatus() == ResponseListener::RequestFailed)
		{
			HandleTimeOut();
		}

		return false;
	}

	
	bool Session::RemoveEntryOrder(const fx::Position& posin)
	{
		if(RemoveEntryOrderReq(posin))
			return true;

		// RequestFailed
		if(m_responseListener->GetRequestStatus() == ResponseListener::RequestFailed)
		{
			HandleTimeOut();
		}

		return false;
	}

	bool Session::GetHistPrices(
		const misc::string&	symbol,
		const misc::string&	sTimeFrame,
		const misc::string&	sDateFrom,
		const misc::string&	sDateTo,
		fxcm::HistPriceData& retPriceData
		)
	{
		double const NaN = std::numeric_limits<double>::quiet_NaN();
		struct tm tmBuf = {0};
		DATE mDateFrom = NaN;
		DATE mDateTo = NaN;
		O2G2Ptr<IO2GRequestFactory> requestFactory = NULL;
		O2G2Ptr<IO2GRequest> request = NULL;


		// Lock ResponseListener
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());


			if(!sDateFrom.empty())
			{
				strptime(sDateFrom.c_str(), "%m.%d.%Y %H:%M:%S", &tmBuf);
				CO2GDateUtils::CTimeToOleTime(&tmBuf, &mDateFrom);
			}

			if(!sDateTo.empty())
			{
				strptime(sDateTo.c_str(), "%m.%d.%Y %H:%M:%S", &tmBuf);
				CO2GDateUtils::CTimeToOleTime(&tmBuf, &mDateTo);
			}

			requestFactory = m_session->getRequestFactory();
			if (!requestFactory)
			{
				AUDIT(m_audit, "session->getRequestFactory failed.");
				return false;
			}

			//find time frame by identifier
			O2G2Ptr<IO2GTimeframeCollection> timeframeCollection = requestFactory->getTimeFrameCollection();
			if(!timeframeCollection)
			{
				misc::string msg("requestFactory->getTimeFrameCollection failed. Last error: ");
				msg += requestFactory->getLastError();
				AUDIT(m_audit, msg.c_str());
				return false;
			}

			O2G2Ptr<IO2GTimeframe> timeframe = timeframeCollection->get(sTimeFrame.c_str());
			if(!timeframe)
			{
				AUDIT(m_audit, "timeframeCollection->get failed.");
				return false;
			}

			request = requestFactory->createMarketDataSnapshotRequestInstrument(symbol.c_str(), timeframe, timeframe->getQueryDepth());
			if(!request)
			{
				AUDIT(m_audit, "requestFactory->createMarketDataSnapshotRequestInstrument failed.");
				return false;
			}
		}
		
				

		DATE mDateLast = mDateTo;
		// there is limit for returned candles amount
		do 
		{

			// Lock ResponseListener
			{
				misc::autocritical_section lock(m_responseListener->GetCriticalSection());


				requestFactory->fillMarketDataSnapshotRequestTime(request, mDateFrom, mDateLast, false);
				m_responseListener->SetRequestID(request->getRequestID());
			}
			
			//TODO: release OrderMonitor
			m_session->sendRequest(request);
			if(!m_responseListener->WaitEvents())
			{
				AUDIT(m_audit, "responseListener->WaitEvents failed.");
				return false;
			}


			// Lock ResponseListener
			{
				misc::autocritical_section lock(m_responseListener->GetCriticalSection());


				// shift "to" bound to oldest datetime of returned data
				O2G2Ptr<IO2GResponse> response = m_responseListener->GetResponse();
				if(!response)
				{
					AUDIT(m_audit, "responseListener->GetResponse failed.");
					return false;
				}

				if(response->getType() == MarketDataSnapshot)
				{
					O2G2Ptr<IO2GResponseReaderFactory> readerFactory = m_session->getResponseReaderFactory();
					if(!readerFactory)
					{
						AUDIT(m_audit, "session->getResponseReaderFactory failed");
						// previously only checking if pointer is valid
					}
					else
					{
						O2G2Ptr<IO2GMarketDataSnapshotResponseReader> reader = readerFactory->createMarketDataSnapshotReader(response);
						if(reader->size() > 0)
						{
							// [from .... ret3] [... ret2] [.... ret1] [..... to]
							if(abs(mDateLast - reader->getDate(0)) > 0.0001)
								mDateLast = reader->getDate(0);
							else
								break;
						}
						else
						{
							misc::cout << "0 rows received" << std::endl;
							break;
						}
					}

					// get the prices
					if(!ReadHistPrices(response, retPriceData))
					{
						AUDIT(m_audit, "ReadHistPrices failed");
						return false;
					}
				}
				else
				{
					AUDIT(m_audit, "response->getType() != MarketDataSnapshot");
					// previously only break
					break;
				}
			} // locked			
		}
		while(mDateLast - mDateFrom > 0.0001);

		// request completed, unknown outcome.
		return !retPriceData.empty();;		
	}

	bool Session::CreateMarketOrder(
		const fx::Position& posin,
		misc::vector<fx::Position>& outvec)
	{
		// success
		if(CreateMarketOrderImpl(posin, outvec))
			return true;

		// RequestFailed
		if(m_responseListener->GetRequestStatus() == ResponseListener::RequestFailed)
		{
			HandleTimeOut();
			/*	Cons - stack overflow
			 *	Pros - handle rejected amount
			 */
			return CreateMarketOrder(posin, outvec);
		}

		/*	Order can be finished in 3 situations :
		 *	Cancelled
		 *	Rejected total or partial
		 *	Executed (succeeded)
		 */
		OrderMonitor& orderMonitor = m_responseListener->GetOrderMonitor();
		if(orderMonitor.getResult() == OrderMonitor::OrderFinished &&
			(orderMonitor.getState() == OrderMonitor::Cancelled ||
			orderMonitor.getState() == OrderMonitor::Rejected))
		{
			return CreateMarketOrderRejected(posin, outvec);
		}

		return false;
	}

	bool Session::CloseMarketOrder(
		const fx::Position& posin,
		misc::vector<fx::Position>& outvec)
	{
		// success
		if(CloseMarketOrderImpl(posin, outvec))
			return true;

		// RequestFailed
		if(m_responseListener->GetRequestStatus() == ResponseListener::RequestFailed)
		{
			HandleTimeOut();
			/*	Cons - stack overflow
			 *	Pros - handle rejected amount
			 */
			return CloseMarketOrder(posin, outvec);
		}

		/*	Order can be finished in 3 situations :
		 *	Cancelled
		 *	Rejected total or partial
		 *	Executed (succeeded)
		 */
		OrderMonitor& orderMonitor = m_responseListener->GetOrderMonitor();
		if(orderMonitor.getResult() == OrderMonitor::OrderFinished &&
			(orderMonitor.getState() == OrderMonitor::Cancelled ||
			orderMonitor.getState() == OrderMonitor::Rejected))
		{
			return CloseMarketOrderRejected(posin, outvec);
		}

		return false;
	}
	

	bool Session::GetMarketOrders(const fx::Position& posin, misc::vector<fx::Position>& outvec)
	{
		// success
		if(GetMarketOrdersImpl(posin, outvec))
			return true;

		// RequestFailed
		if(m_responseListener->GetRequestStatus() == ResponseListener::RequestFailed)
		{
			/*	For getting market orders reconnect and let strategy/user 
			 *	to try again. 
			 */
			HandleTimeOut();
		}

		return false;
	}

	bool Session::GetEntryOrders(
		const fx::Position& posin,
		misc::vector<fx::Position>& outvec)
	{
		O2G2Ptr<IO2GOfferRow> offer = NULL;

		// login rules
		O2G2Ptr<IO2GLoginRules> loginRules = m_session->getLoginRules();
		if(!loginRules)
		{
			AUDIT(m_audit, "session->getLoginRules failed.");
			return false;
		}
		// reader factory
		O2G2Ptr<IO2GResponseReaderFactory> readerFactory = m_session->getResponseReaderFactory();
		if(!readerFactory)
		{
			AUDIT(m_audit, "session->getResponseReaderFactory failed.");
			return false;
		}
		// account
		O2G2Ptr<IO2GAccountRow> account = GetAccount(loginRules, readerFactory);
		if(!account)
		{
			AUDIT(m_audit, "GetAccount failed.");
			return false;
		}
		// market offer
		offer = GetOfferInt(loginRules, readerFactory, posin.GetCurrency().GetSymbol());
		if(!offer)
		{
			AUDIT(m_audit, "GetOffer failed.");
			return false;
		}

		// get pending entry orders
		if(GetEntryOrders(posin, offer, outvec))
		{
			misc::cout << "\n\tRetrieved pending entry orders." << std::endl;
			return true;
		}

		AUDIT(m_audit, "GetEntryOrders failed.");
		return false;
	}

	void Session::SetAuditFile(const misc::string& filepath)
	{
		m_audit = misc::audit(filepath);
	}


	bool Session::Login()
	{		
		m_sessionListener->Reset();

		m_session->login(
			m_iniParams.GetUser().c_str(),
			m_iniParams.GetPassword().c_str(),
			m_iniParams.GetUrl().c_str(),
			m_iniParams.GetConnection().c_str());

		m_sessionListener->WaitEvents();
		return m_sessionListener->IsConnected();
	}

	bool Session::Logout()
	{
		m_sessionListener->Reset();

		m_session->logout();
		m_sessionListener->WaitEvents();
		return m_sessionListener->IsDisconnected();
	}

	IO2GAccountRow* Session::GetAccount(
		IO2GLoginRules* loginRules,
		IO2GResponseReaderFactory* readerFactory)
	{		
		// Identify the given account.		
		O2G2Ptr<IO2GResponse> accountsTable = loginRules->getTableRefreshResponse(Accounts);
		if(!accountsTable)
		{
			AUDIT(m_audit, "loginRules->getTableRefreshResponse(Accounts) failed.");
			return NULL;
		}

		O2G2Ptr<IO2GAccountsTableResponseReader> accountsReader = readerFactory->createAccountsTableReader(accountsTable);
		if(!accountsReader)
		{
			AUDIT(m_audit, "readerFactory->createAccountsTableReader failed.");
			return NULL;
		}

		
		for(int i=0; i < accountsReader->size(); ++i)
		{
			O2G2Ptr<IO2GAccountRow> account = accountsReader->getRow(i);
			if(account)
			{
				const char* accountID = account->getAccountID();		// 2475538
				const char* accountKind = account->getAccountKind();	// 32

				if(m_iniParams.GetAccount() == accountID)
				{
					if( strcmp(account->getMarginCallFlag(), "N") == 0 &&
						(strcmp(accountKind, "32") == 0 || strcmp(accountKind, "36") == 0 ))
					{
						return account.Detach();						
					}
				}
			}
		}

		
		AUDIT(m_audit, "GetAccount failed.");
		return NULL;
	}

	bool Session::GetCurrenciesImpl(misc::vector<fx::Currency>& currencies)
	{
		O2G2Ptr<IO2GRequest> offersRequest = NULL;

		// Lock ResponseListener.
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());

			// login rules
			O2G2Ptr<IO2GLoginRules> loginRules = m_session->getLoginRules();
			if(!loginRules)
			{
				AUDIT(m_audit, "session->getLoginRules failed.");
				return false;
			}
			
			/*
			if(loginRules->isTableLoadedByDefault(Offers))
			{
				O2G2Ptr<IO2GResponse> response = loginRules->getTableRefreshResponse(Offers);
				// update currencies property
				return UpdateCurrencies(response, currencies);
			}		
			*/

			/* Refresh Offers Table to get all valid offers.
			 * Depending at what time we call broker, some instruments may not
			 * be tradable CFDs (UKOil) and Indexes (ITA40)
			 */
			O2G2Ptr<IO2GRequestFactory> requestFactory = m_session->getRequestFactory();
			if(!requestFactory)
			{
				AUDIT(m_audit, "session->getRequestFactory failed.");
				return false;
			}

			offersRequest = requestFactory->createRefreshTableRequest(Offers);
			if(!offersRequest)
			{
				misc::string msg("requestFactory->createRefreshTableRequest(Offers) failed. Last error: ");
				msg += requestFactory->getLastError();
				AUDIT(m_audit, msg.c_str());
				return false;
			}

			m_responseListener->SetRequestID(offersRequest->getRequestID());
		}

		
		m_session->sendRequest(offersRequest);
		if(!m_responseListener->WaitEvents())
		{
			AUDIT(m_audit, "responseListener->WaitEvents timeout.");
			return false;
		}


		// Lock ResponseListener
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());


			O2G2Ptr<IO2GResponse> response = m_responseListener->GetResponse();
			if(!response)
			{
				AUDIT(m_audit, "responseListener->GetResponse failed.");
				return false;
			}

			// update currencies property
			bool ret = UpdateCurrencies(response, currencies);

			m_responseListener->Reset();

			return ret;
		}
	}

	bool Session::GetOfferImpl(std::map<misc::string, fx::Price>& quotes)
	{
		// Lock ResponseListener to avoid surprises :)
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());

			ResponseListener::Quotes& rl_quotes = m_responseListener->GetQuotes();
			if(!rl_quotes.empty())
			{
				for(ResponseListener::Quotes::iterator it = rl_quotes.begin();
					it != rl_quotes.end(); ++it)
				{
					quotes[it->first] = it->second;
				}

				return true;
			}
		}

		return GetOfferReq(quotes);
	}


	bool Session::GetOfferReq(std::map<misc::string, fx::Price>& quotes)
	{
		O2G2Ptr<IO2GRequest> offersRequest = NULL;


		// Lock ResponseListener to avoid surprises.
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());


			// login rules
			O2G2Ptr<IO2GLoginRules> loginRules = m_session->getLoginRules();
			if(!loginRules)
			{
				AUDIT(m_audit, "session->getLoginRules failed.");
				return false;
			}
			/*	
			if(loginRules->isTableLoadedByDefault(Offers))
			{
				O2G2Ptr<IO2GResponse> response = loginRules->getTableRefreshResponse(Offers);
				// update price offer
				return UpdatePriceOffer(response, quotes);
			}
			*/

			/*	Default Offers table does not retrieve new data from market.
			 *	We need to ask for new quotes.
			 */
			O2G2Ptr<IO2GRequestFactory> requestFactory = m_session->getRequestFactory();
			if(!requestFactory)
			{
				AUDIT(m_audit, "session->getRequestFactory failed.");
				return false;
			}
			// request
			offersRequest = requestFactory->createRefreshTableRequest(Offers);
			if(!offersRequest)
			{
				misc::string msg("requestFactory->createRefreshTableRequest(Offers) failed. Last error: ");
				msg += requestFactory->getLastError();

				AUDIT(m_audit, msg.c_str());
				return false;
			}
			// set ID
			m_responseListener->SetRequestID(offersRequest->getRequestID());
		}


		//TODO: release OrderMonitor
		m_session->sendRequest(offersRequest);
		if(!m_responseListener->WaitEvents())
		{
			AUDIT(m_audit, "responseListener->WaitEvents timeout.");
			return false;
		}


		// Lock ResponseListener.
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());

			ResponseListener::RequestStatus requestStatus = m_responseListener->GetRequestStatus();
			if(requestStatus == ResponseListener::RequestFailed)
			{
				AUDIT(m_audit, "ResponseListener::RequestFailed");
				return false;
			}

			// response
			O2G2Ptr<IO2GResponse> response = m_responseListener->GetResponse();
			if(!response)
			{
				AUDIT(m_audit, "responseListener->GetResponse failed.");
				return false;
			}
			// update price offer
			bool ret = UpdatePriceOffer(response, quotes);

			// reset
			m_responseListener->Reset();

			return ret;
		}	
	}

	IO2GOfferRow* Session::GetOfferInt(
		IO2GLoginRules* loginRules,
		IO2GResponseReaderFactory* readerFactory,
		const misc::string& symbol)
	{
		O2G2Ptr<IO2GResponse> offersTable = loginRules->getTableRefreshResponse(Offers);
		if(!offersTable)
		{
			AUDIT(m_audit, "loginRules->getTableRefreshResponse(Offers) failed.");
			return NULL;
		}
		O2G2Ptr<IO2GOffersTableResponseReader> offersReader = readerFactory->createOffersTableReader(offersTable);
		if(!readerFactory)
		{
			AUDIT(m_audit, "readerFactory->createOffersTableReader failed.");
			return NULL;
		}
		
		for(int i=0; i < offersReader->size(); ++i)
		{
			O2G2Ptr<IO2GOfferRow> offer = offersReader->getRow(i);
			if(offer)
			{
				if(symbol == offer->getInstrument())
				{
					if(strcmp(offer->getSubscriptionStatus(), "T")==0)
					{
						return offer.Detach();
					}
				}
			}
		}

		AUDIT(m_audit, "GetOffer failed.");
		return NULL;
	}

	IO2GTradeRow* Session::GetTrade(IO2GOfferRow* offer, const misc::string& orderID, const misc::string& tradeID)
	{
		O2G2Ptr<IO2GRequest> request = NULL;


		// Lock ResponseListener to avoid surprises :)
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());


			// factory
			O2G2Ptr<IO2GRequestFactory> requestFactory = m_session->getRequestFactory();
			if(!requestFactory)
			{
				AUDIT(m_audit, "session->getRequestFactory failed.");
				return NULL;
			}
			// request
			request = requestFactory->createRefreshTableRequestByAccount(Trades, m_iniParams.GetAccount().c_str());
			if(!request)
			{
				misc::string msg("requestFactory->createRefreshTableRequestByAccount failed. Last error: ");
				msg += requestFactory->getLastError();
				AUDIT(m_audit, msg.c_str());
				return NULL;
			}
			// set ID
			m_responseListener->SetRequestID(request->getRequestID());
		}


		//TODO: release OrderMonitor
		m_session->sendRequest(request);
		if(!m_responseListener->WaitEvents())
		{
			AUDIT(m_audit, "responseListener->WaitEvents failed.");
			return NULL;
		}


		// Lock ResponseListener to avoid surprises :)
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());


			// response
			O2G2Ptr<IO2GResponse> response = m_responseListener->GetResponse();
			if(!response)
			{
				AUDIT(m_audit, "responseListener->GetResponse failed.");
				return NULL;
			}
			// reader
			O2G2Ptr<IO2GResponseReaderFactory> readerFactory = m_session->getResponseReaderFactory();
			if(!readerFactory)
			{
				AUDIT(m_audit, "session->getResponseReaderFactory failed.");
				return NULL;
			}
			// trades
			O2G2Ptr<IO2GTradesTableResponseReader> tradesResponseReader = readerFactory->createTradesTableReader(response);
			for(int i = 0; i < tradesResponseReader->size(); ++i)
			{
				O2G2Ptr<IO2GTradeRow> trade = tradesResponseReader->getRow(i);
				bool isOffer = (strcmp(trade->getOfferID(), offer->getOfferID()) == 0);
				bool isOrder = (strcmp(trade->getOpenOrderID(), orderID.c_str()) == 0);
	//			bool isTrade = (strcmp(trade->getTradeID(), tradeID.c_str()) == 0);
	//			isTrade;
				if( tradeID.empty() ) // no effect, to pass compile warning/error
					tradeID.empty();

				// TODO: add back tradeID identification
				//		 also add detection for partial close amount
				//		 also add detection for setting new tradeID for left amount
				
				/*	If a trade's amount get closed partially, that trade
				 *	keeps it's orderID but NOT the tradeID, which is assigned
				 *	a new Ticket.
				 */
				if(isOffer && isOrder)// && isTrade)
					return trade.Detach();
			}
		}
				
		AUDIT(m_audit, "GetTrade failed.");
		return NULL;
	}

	bool Session::CreateEntryOrderImpl(
		const fx::Position& posin,
		double rateLimit,
		double rateStop,
		fx::Position& posout)
	{

		O2G2Ptr<IO2GOfferRow> offer = NULL;

		// Lock ResponseListener
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());

			// login rules
			O2G2Ptr<IO2GLoginRules> loginRules = m_session->getLoginRules();
			if(!loginRules)
			{
				AUDIT(m_audit, "session->getLoginRules failed.");
				return false;
			}
			// reader factory
			O2G2Ptr<IO2GResponseReaderFactory> readerFactory = m_session->getResponseReaderFactory();
			if(!readerFactory)
			{
				AUDIT(m_audit, "session->getResponseReaderFactory failed.");
				return false;
			}
			// get account
			O2G2Ptr<IO2GAccountRow> account = GetAccount(loginRules, readerFactory);
			if(!account)
			{
				AUDIT(m_audit, "GetAccount failed.");
				return false;
			}
			// market offer
			offer = GetOfferInt(loginRules, readerFactory, posin.GetCurrency().GetSymbol());
			if(!offer)
			{
				AUDIT(m_audit, "GetOffer failed.");
				return false;
			}
		}


		if(CreateEntryOrderReq(posin, rateLimit, rateStop, offer, posout))
		{
			misc::cout << "\n\tEntry order is created." << std::endl;
			return true;
		}

		AUDIT(m_audit, "CreateEntryOrder failed.");
		return false;
	}

	bool Session::CreateEntryOrderReq(
		const fx::Position& posin,
		double rateLimit,
		double rateStop,
		IO2GOfferRow* offer,
		fx::Position& posout)
	{
		O2G2Ptr<IO2GRequest> request = NULL;

		// Lock ResponseListener
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());


			const misc::string& symbol = posin.GetCurrency().GetSymbol();
			int amount = (int)posin.GetAmount();
			bool isBuy = posin.IsBuy();
			double rate = (isBuy == true ? 
				posin.GetCurrency().GetPrice().GetBuy() :
			posin.GetCurrency().GetPrice().GetSell());

			const SymbolSettings& instrumentSettings = m_tradingSettings->GetTradingSettings(symbol);
			int iBaseUnitSize = instrumentSettings.m_baseUnitSize;
			int iAmount = iBaseUnitSize * amount;
			O2G2Ptr<IO2GRequestFactory> requestFactory = m_session->getRequestFactory();
			if(!requestFactory)
			{
				AUDIT(m_audit, "session->getRequestFactory failed.");
				return false;
			}
			O2G2Ptr<IO2GValueMap> valuemap = requestFactory->createValueMap();
			valuemap->setString(Command, O2G2::Commands::CreateOrder);
			valuemap->setString(OrderType, (isBuy == true ? "LE" : "SE"));
			valuemap->setString(TimeInForce, O2G2::TIF::GTC);
			valuemap->setString(AccountID, m_iniParams.GetAccount().c_str());
			valuemap->setString(OfferID, offer->getOfferID());
			valuemap->setString(BuySell, (isBuy == true ? "B" : "S"));
			valuemap->setInt(Amount, iAmount);
			valuemap->setDouble(Rate, rate);

			// Entry type.
			if(math::is_zero(rateLimit) && math::is_zero(rateStop))
			{
				valuemap->setString(CustomID, "EntryOrder");
			}
			else
			{
				valuemap->setDouble(RateLimit, rateLimit);
				valuemap->setDouble(RateStop, rateStop);
				valuemap->setString(CustomID, "EntryOrderWithStopLimit");
			}

			request = requestFactory->createOrderRequest(valuemap);
			if(!request)
			{
				misc::string msg("requestFactory->createOrderRequest. Last error: ");
				msg += requestFactory->getLastError();
				AUDIT(m_audit, msg.c_str());
				return false;
			}

			m_responseListener->SetRequestID(request->getRequestID());
		}


		m_session->sendRequest(request);
		if(!m_responseListener->WaitEvents())
		{
			AUDIT(m_audit, "responseListener->WaitEvents timeout.");
			return false;	
		}

		
		// Lock ResponseListener
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());


			O2G2Ptr<IO2GResponse> response = m_responseListener->GetResponse();
			if(!response)
			{
				AUDIT(m_audit, "responseListener->GetResponse failed.");
				return false;
			}

			OrderMonitor& orderMonitor = m_responseListener->GetOrderMonitor();
			O2G2Ptr<IO2GOrderRow> order = orderMonitor.getOrder();
			if(!order)
			{
				AUDIT(m_audit, "orderMonitor.getOrder() failed.");
				return false;
			}

			misc::string orderID = order->getOrderID();
			posout = posin;

			Order2Position(order, posout);

			// reset
			m_responseListener->Reset();

			return !orderID.empty();
		}
	}

	bool Session::RemoveEntryOrderReq(const fx::Position& posin)
	{
		O2G2Ptr<IO2GRequest> request = NULL;

		// Lock ResponseListener
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());

			// login rules
			O2G2Ptr<IO2GLoginRules> loginRules = m_session->getLoginRules();
			if(!loginRules)
			{
				AUDIT(m_audit, "session->getLoginRules failed.");
				return false;
			}
			// reader factory
			O2G2Ptr<IO2GResponseReaderFactory> readerFactory = m_session->getResponseReaderFactory();
			if(!readerFactory)
			{
				AUDIT(m_audit, "session->getResponseReaderFactory failed.");
				return false;
			}
			// account
			O2G2Ptr<IO2GAccountRow> account = GetAccount(loginRules, readerFactory);
			if(!account)
			{
				AUDIT(m_audit, "GetAccount failed.");
				return false;
			}
			// request
			O2G2Ptr<IO2GRequestFactory> requestFactory = m_session->getRequestFactory();
			if(!requestFactory)
			{
				AUDIT(m_audit, "session->getRequestFactory failed.");
				return false;
			}

			O2G2Ptr<IO2GValueMap> valuemap = requestFactory->createValueMap();
			valuemap->setString(Command, O2G2::Commands::DeleteOrder);
			valuemap->setString(TimeInForce, O2G2::TIF::GTC);
			valuemap->setString(AccountID, account->getAccountID());
			valuemap->setString(OrderID, posin.GetOrderID().c_str());
			valuemap->setString(CustomID, "RemoveEntryOrder");
			request = requestFactory->createOrderRequest(valuemap);
			if(!request)
			{
				misc::string msg("requestFactory->createOrderRequest failed. Last error: ");
				msg += requestFactory->getLastError();

				AUDIT(m_audit, msg.c_str());
				return false;
			}

			// send request
			m_responseListener->SetRequestID(request->getRequestID());
		}


		m_session->sendRequest(request);
		if(!m_responseListener->WaitEvents())
		{
			AUDIT(m_audit, "RemoveEntryOrder timeout.");
			return false;
		}

		// reset
		m_responseListener->Reset();

		misc::cout << "\n\tOrder is removed." << std::endl;
		return true;
	}

	bool Session::CreateMarketOrderImpl(
		const fx::Position& posin,
		misc::vector<fx::Position>& outvec)
	{

		O2G2Ptr<IO2GOfferRow> offer = NULL;

		// Lock ResponseListener to avoid surprises :)
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());


			// login rules
			O2G2Ptr<IO2GLoginRules> loginRules = m_session->getLoginRules();
			if(!loginRules)
			{
				AUDIT(m_audit, "session->getLoginRules failed.");
				return false;
			}
			// reader factory
			O2G2Ptr<IO2GResponseReaderFactory> readerFactory = m_session->getResponseReaderFactory();
			if(!readerFactory)
			{
				AUDIT(m_audit, "session->getResponseReaderFactory failed.");
				return false;
			}
			// account
			O2G2Ptr<IO2GAccountRow> account = GetAccount(loginRules, readerFactory);
			if(!account)
			{
				AUDIT(m_audit, "GetAccount failed.");
				return false;
			}

			// market offer
			offer = GetOfferInt(loginRules, readerFactory, posin.GetCurrency().GetSymbol());
			if(!offer)
			{
				AUDIT(m_audit, "GetOffer failed.");
				return false;
			}
		}
	

		// market order (no limit/stop attached)
		if(CreateMarketOrderReq(posin, offer, outvec))
		{			
			misc::cout << "\n\tEntry order is created." << std::endl;
			return true;
		}
		
		AUDIT(m_audit, "CreateMarketOrder failed.");
		return false;
	}


	bool Session::CreateMarketOrderReq(
		const fx::Position& posin,
		IO2GOfferRow* offer,
		misc::vector<fx::Position>& outvec)
	{
		O2G2Ptr<IO2GRequest> request = NULL;


		// Lock ResponseListener to avoid surprises :)
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());


			const misc::string& symbol = posin.GetCurrency().GetSymbol();
			bool buy = posin.IsBuy();
			int amount = (int)posin.GetAmount();

			const SymbolSettings& instrumentSettings = m_tradingSettings->GetTradingSettings(symbol);
			int iBaseUnitSize = instrumentSettings.m_baseUnitSize;
			int iAmount = iBaseUnitSize * amount;

			O2G2Ptr<IO2GRequestFactory> requestFactory = m_session->getRequestFactory();
			if(!requestFactory)
			{
				AUDIT(m_audit, "session->getRequestFactory failed.");
				return false;
			}

			O2G2Ptr<IO2GValueMap> valuemap = requestFactory->createValueMap();
			valuemap->setString(Command, O2G2::Commands::CreateOrder);
			valuemap->setString(OrderType, O2G2::Orders::TrueMarketOpen);
			valuemap->setString(TimeInForce, O2G2::TIF::GTC);
			valuemap->setString(AccountID, m_iniParams.GetAccount().c_str());
			valuemap->setString(OfferID, offer->getOfferID());
			valuemap->setString(BuySell, (buy == true ? O2G2::Buy : O2G2::Sell));
			valuemap->setInt(Amount, iAmount);
			valuemap->setString(CustomID, "TrueMarketOrder");

			request = requestFactory->createOrderRequest(valuemap);
			if(!request)
			{
				misc::string msg("requestFactory->createOrderRequest failed. Last error: ");
				msg += requestFactory->getLastError();
				AUDIT(m_audit, msg.c_str());
				return false;
			}

			m_responseListener->SetRequestID(request->getRequestID());
		}


		//TODO: release OrderMonitor
		m_session->sendRequest(request);		
		if(!m_responseListener->WaitEvents())
		{
			AUDIT(m_audit, "responseListener->WaitEvents failed.");
			return false;
		}
		
		// Sleep(500); // Wait for the balance update


		// Lock ResponseListener
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());


			ResponseListener::RequestStatus requestStatus = m_responseListener->GetRequestStatus();
			if(requestStatus == ResponseListener::RequestFailed)
			{
				AUDIT(m_audit, "responseListener->GetResponse failed.");
				return false;
			}

			O2G2Ptr<IO2GResponse> response = m_responseListener->GetResponse();
			if(!response)
			{
				AUDIT(m_audit, "responseListener->GetResponse failed.");
				return false;
			}

			OrderMonitor& orderMonitor = m_responseListener->GetOrderMonitor();
			O2G2Ptr<IO2GOrderRow> order = orderMonitor.getOrder();
			if(!order)
			{
				AUDIT(m_audit, "orderMonitor.getOrder() failed.");
				return false;
			}

			/*	Order is finished correctly with one the states :
			 *	F	-	Executed
			 *	C	-	Cancelled
			 *	R	-	Rejected
			 */
			if(orderMonitor.getResult() != OrderMonitor::OrderFinished)
			{
				// TODO: handle Rejected, PartialRejected or Cancelled Order
				AUDIT(m_audit, "orderMonitor.getResult() failed.");
				return false;
			}
			if(orderMonitor.getState() == OrderMonitor::Cancelled)			
			{
				return false;
			}

			misc::string orderID = order->getOrderID();						

			CollectAllTrades(posin, orderMonitor, outvec);

			// reset
			m_responseListener->Reset();

			return !orderID.empty();
		}		
	}

	bool Session::CreateMarketOrderRejected(
		const fx::Position& posin,
		misc::vector<fx::Position>& outvec)
	{

		/*	We get here into a recursive loop trying to get the entire rejected
		 *	amount filled at market.
		 */
		double remainedAmount = posin.GetAmount();		
		for(size_t i = 0; i < outvec.size(); ++i)
		{
			const fx::Position& posout = outvec[i];
			remainedAmount -= posout.GetAmount();
		}

		if(remainedAmount <= 0)
		{
			misc::string txt("Error: invalid remained amount= ");
			txt += misc::from_value(remainedAmount, 1);
			AUDIT(m_audit, txt.c_str());
			return true;
		}
		
		fx::Position posrem(
			"", "",
			posin.GetCurrency(),
			posin.IsBuy(),
			remainedAmount,
			0,
			0);
		misc::vector<fx::Position> remvec;

		// fill remained amount
		bool ret = CreateMarketOrder(posrem, remvec);
		for(size_t i = 0; i < remvec.size(); ++i)
			outvec.push_back(remvec[i]);


		misc::string txt("\nOpening MarketOrder's rejected amount = ");
		txt += misc::from_value(remainedAmount, 1);
		txt += (ret == true ? " SUCCEEDED" : " FAILED");
		AUDIT(m_audit, txt.c_str());

		return ret;
	}

	bool Session::CloseMarketOrderImpl(
		const fx::Position& posin,
		misc::vector<fx::Position>& outvec)
	{

		O2G2Ptr<IO2GOfferRow> offer = NULL;

		// Lock ResponseListener to avoid surprises :)
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());


			// login rules
			O2G2Ptr<IO2GLoginRules> loginRules = m_session->getLoginRules();
			if(!loginRules)
			{
				AUDIT(m_audit, "session->getLoginRules failed.");
				return false;
			}
			// reader factory
			O2G2Ptr<IO2GResponseReaderFactory> readerFactory = m_session->getResponseReaderFactory();
			if(!readerFactory)
			{
				AUDIT(m_audit, "session->getResponseReaderFactory failed.");
				return false;
			}
			// account
			O2G2Ptr<IO2GAccountRow> account = GetAccount(loginRules, readerFactory);
			if(!account)
			{
				AUDIT(m_audit, "GetAccount failed.");
				return false;
			}
			// market offer
			offer = GetOfferInt(loginRules, readerFactory, posin.GetCurrency().GetSymbol());
			if(!offer)
			{
				AUDIT(m_audit, "GetOffer failed.");
				return false;
			}
		}


		// close partially/totally a market order
		if(CloseMarketOrderReq(posin, offer, outvec))
		{
			misc::cout << "\n\tClosed market order." << std::endl;
			return true;
		}

		AUDIT(m_audit, "CloseMarketOrder failed.");
		return false;
	}


	bool Session::CloseMarketOrderReq(
		const fx::Position& posin,
		IO2GOfferRow* offer,
		misc::vector<fx::Position>& outvec)
	{
		misc::string symbol = posin.GetCurrency().GetSymbol();
		misc::string orderID = posin.GetOrderID();
		misc::string tradeID = posin.GetTradeID();
		int amount = (int)posin.GetAmount();


		const SymbolSettings& instrumentSettings = m_tradingSettings->GetTradingSettings(symbol);
		int iBaseUnitSize = instrumentSettings.m_baseUnitSize;
		int iAmount = iBaseUnitSize * amount;

		// !!! will lock the listener to retrieve the trade from server
		O2G2Ptr<IO2GTradeRow> trade = GetTrade(offer, orderID, tradeID);
		if(!trade)
		{
			misc::string msg("GetTrade failed. OrderID:");
			msg += orderID;
			msg += " Ticket:";
			msg + tradeID;

			AUDIT(m_audit, msg.c_str());
			return false;
		}


		O2G2Ptr<IO2GRequest> request = NULL;


		// Lock ResponseListener
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());

			
			//O2G2Ptr<IO2GLoginRules> loginRules = m_session->getLoginRules();
			//O2G2Ptr<IO2GPermissionChecker> permissionChecker = loginRules->getPermissionChecker();
			O2G2Ptr<IO2GRequestFactory> requestFactory = m_session->getRequestFactory();
			if(!requestFactory)
			{
				AUDIT(m_audit, "session->getRequestFactory failed.");
				return false;
			}
			const SymbolPermission& symbolPermission = m_permission->GetPermission(symbol);

			O2G2Ptr<IO2GValueMap> valuemap = requestFactory->createValueMap();
			valuemap->setString(Command, O2G2::Commands::CreateOrder);
			if(symbolPermission.m_canCreateMarketCloseOrder != PermissionEnabled)
			{
				// in USA you need to use "OM" to close a position
				// but I'm not in USA :)
				valuemap->setString(OrderType, O2G2::Orders::TrueMarketOpen);
			}
			else
			{
				valuemap->setString(OrderType, O2G2::Orders::TrueMarketClose);
				valuemap->setString(TradeID, trade->getTradeID());
			}
			valuemap->setString(TimeInForce, O2G2::TIF::GTC);
			valuemap->setString(AccountID, trade->getAccountID());
			valuemap->setString(OfferID, trade->getOfferID());
			valuemap->setString(BuySell, strcmp(trade->getBuySell(), O2G2::Buy) == 0 ? O2G2::Sell : O2G2::Buy);
			valuemap->setInt(Amount, iAmount);
			valuemap->setString(CustomID, "CloseMarketOrder");
			request = requestFactory->createOrderRequest(valuemap);
			if(!request)
			{
				misc::string msg("requestFactory->createOrderRequest failed. Last error: ");
				msg += requestFactory->getLastError();
				AUDIT(m_audit, msg.c_str());
				return false;
			}
			m_responseListener->SetRequestID(request->getRequestID());
		}


		//TODO: release OrderMonitor
		m_session->sendRequest(request);
		if(!m_responseListener->WaitEvents())
		{
			AUDIT(m_audit, "responseListener->WaitEvents timeout.");
			return false;
		}
		
		// Sleep(500); // Wait for the balance update


		// Lock ResponseListener
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());


			ResponseListener::RequestStatus requestStatus = m_responseListener->GetRequestStatus();
			if(requestStatus == ResponseListener::RequestFailed)
			{
				AUDIT(m_audit, "ResponseListener::RequestFailed");
				return false;
			}

			// response
			O2G2Ptr<IO2GResponse> response = m_responseListener->GetResponse();
			if(!response)
			{
				AUDIT(m_audit, "responseListener->GetResponse failed.");
				return false;
			}
			// monitor
			OrderMonitor& orderMonitor = m_responseListener->GetOrderMonitor();
			O2G2Ptr<IO2GOrderRow> order = orderMonitor.getOrder();
			if(!order)
			{
				AUDIT(m_audit, "orderMonitor.getOrder() failed.");
				return false;
			}
			/*	Order is finished correctly with one the states :
			 *	F	-	Executed
			 *	C	-	Cancelled
			 *	R	-	Rejected
			 */
			if(orderMonitor.getResult() != OrderMonitor::OrderFinished)
			{
				// TODO: handle Rejected, PartialRejected or Cancelled Order
				AUDIT(m_audit, "orderMonitor.getResult() failed.");
				return false;
			}
			if(orderMonitor.getState() == OrderMonitor::Cancelled)
			{
				return false;
			}

			misc::string orderID2 = order->getOrderID();

			CollectAllTrades(posin, orderMonitor, outvec);

			// reset
			m_responseListener->Reset();

			return !orderID2.empty();
		}
	}

	bool Session::CloseMarketOrderRejected(
		const fx::Position& posin,
		misc::vector<fx::Position>& outvec)
	{
		/*	We get here into a recursive loop trying to get the entire rejected
		 *	amount filled at market.
		 */
		double remainedAmount = posin.GetAmount();		
		for(size_t i = 0; i < outvec.size(); ++i)
		{
			const fx::Position& posout = outvec[i];
			remainedAmount -= posout.GetAmount();
		}

		if(remainedAmount <= 0)
		{
			misc::string txt("Error: invalid remained amount= ");
			txt += misc::from_value(remainedAmount, 1);
			AUDIT(m_audit, txt.c_str());
			return true;
		}

		fx::Position posrem(
			"", "",
			posin.GetCurrency(),
			posin.IsBuy(),
			remainedAmount,
			0,
			0);
		misc::vector<fx::Position> remvec;

		// fill remained amount
		bool ret = CloseMarketOrder(posrem, remvec);
		for(size_t i = 0; i < remvec.size(); ++i)
			outvec.push_back(remvec[i]);


		misc::string txt("\nClosing MarketOrder's rejected amount = ");
		txt += misc::from_value(remainedAmount, 1);
		txt += (ret == true ? " SUCCEEDED" : " FAILED");
		AUDIT(m_audit, txt.c_str());


		return ret;
	}

	bool Session::GetMarketOrdersImpl(
		const fx::Position& posin,
		misc::vector<fx::Position>& outvec)
	{
		O2G2Ptr<IO2GOfferRow> offer = NULL;


		// Lock ResponseListener
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());


			// login rules
			O2G2Ptr<IO2GLoginRules> loginRules = m_session->getLoginRules();
			if(!loginRules)
			{
				AUDIT(m_audit, "session->getLoginRules failed.");
				return false;
			}
			// reader factory
			O2G2Ptr<IO2GResponseReaderFactory> readerFactory = m_session->getResponseReaderFactory();
			if(!readerFactory)
			{
				AUDIT(m_audit, "session->getResponseReaderFactory failed.");
				return false;
			}
			// account
			O2G2Ptr<IO2GAccountRow> account = GetAccount(loginRules, readerFactory);
			if(!account)
			{
				AUDIT(m_audit, "GetAccount failed.");
				return false;
			}
			// market offer
			offer = GetOfferInt(loginRules, readerFactory, posin.GetCurrency().GetSymbol());
			if(!offer)
			{
				AUDIT(m_audit, "GetOffer failed.");
				return false;
			}
		}


		// close partially/totally a market order
		if(GetMarketOrdersReq(posin, offer, outvec))
		{
			misc::cout << "\n\tRetrieved market orders." << std::endl;
			return true;
		}

		AUDIT(m_audit, "GetMarketOrders failed.");
		return false;
	}

	bool Session::GetMarketOrdersReq(
		const fx::Position& posin,
		IO2GOfferRow* offer,
		misc::vector<fx::Position>& outvec)
	{		
		O2G2Ptr<IO2GRequest> request = NULL;

		// Lock ResponseListener.
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());


			O2G2Ptr<IO2GRequestFactory> requestFactory = m_session->getRequestFactory();
			if(!requestFactory)
			{
				AUDIT(m_audit, "session->getRequestFactory failed.");
				return false;
			}

			request = requestFactory->createRefreshTableRequestByAccount(Trades, m_iniParams.GetAccount().c_str());
			if(!request)
			{
				misc::string msg("requestFactory->createRefreshTableRequestByAccount failed. Last error: ");
				msg += requestFactory->getLastError();
				AUDIT(m_audit, msg.c_str());
				return false;
			}

			m_responseListener->SetRequestID(request->getRequestID());
		}

		
		m_session->sendRequest(request);
		if(!m_responseListener->WaitEvents())
		{
			AUDIT(m_audit, "responseListener->WaitEvents timeout.");
			return false;
		}


		// Lock ResponseListener
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());


			// response
			O2G2Ptr<IO2GResponse> response = m_responseListener->GetResponse();
			if(!response)
			{
				AUDIT(m_audit, "responseListener->GetResponse failed.");
				return false;
			}
			// factory
			O2G2Ptr<IO2GResponseReaderFactory> readerFactory = m_session->getResponseReaderFactory();
			if(!readerFactory)
			{
				AUDIT(m_audit, "session->getResponseReaderFactory failed.");			
				return false;
			}
			// reader
			O2G2Ptr<IO2GTradesTableResponseReader> tradesResponseReader = readerFactory->createTradesTableReader(response);
			for(int i = 0; i < tradesResponseReader->size(); ++i)
			{
				O2G2Ptr<IO2GTradeRow> trade = tradesResponseReader->getRow(i);
				bool isOffer = (strcmp(trade->getOfferID(), offer->getOfferID()) == 0);

				/*	TODO: attention, there may be trades for multiple instruments
				 *			we need to make distinction between EUR/USD and GBP/USD
				 *			for example.
				 */
				if(isOffer)
				{
					fx::Position posout = posin;
					OpenTrade2Position(trade, posout);
					outvec.push_back(posout);
				}
			}


			// reset
			m_responseListener->Reset();

			// can possibly be no order in the market
			return true;
		}
	}

	bool Session::GetEntryOrders(
		const fx::Position& posin,
		IO2GOfferRow* offer,
		misc::vector<fx::Position>& outvec)
	{
		O2G2Ptr<IO2GRequest> request = NULL;

		// Lock ResponseListener
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());

			// factory
			O2G2Ptr<IO2GRequestFactory> requestFactory = m_session->getRequestFactory();
			if(!requestFactory)
			{
				AUDIT(m_audit, "session->getRequestFactory failed.");
				return false;
			}
			// request
			request = requestFactory->createRefreshTableRequestByAccount(Orders, m_iniParams.GetAccount().c_str());
			if(!request)
			{
				misc::string msg("requestFactory->createRefreshTableRequestByAccount failed. Last error: ");
				msg += requestFactory->getLastError();
				AUDIT(m_audit, msg.c_str());
				return false;
			}
			// set ID
			m_responseListener->SetRequestID(request->getRequestID());
		}

		
		//TODO: release OrderMonitor
		m_session->sendRequest(request);
		if(!m_responseListener->WaitEvents())
		{
			AUDIT(m_audit, "responseListener->WaitEvents failed.");
			return false;
		}


		// Lock ResponseListener
		{
			misc::autocritical_section lock(m_responseListener->GetCriticalSection());

			// response
			O2G2Ptr<IO2GResponse> response = m_responseListener->GetResponse();
			if(!response)
			{
				AUDIT(m_audit, "responseListener->GetResponse failed.");
				return false;
			}
			// factory
			O2G2Ptr<IO2GResponseReaderFactory> readerFactory = m_session->getResponseReaderFactory();
			if(!readerFactory)
			{
				AUDIT(m_audit, "session->getResponseReaderFactory failed.");
				return false;
			}
			// reader
			O2G2Ptr<IO2GOrdersTableResponseReader> ordersReader = readerFactory->createOrdersTableReader(response);
			for(int i=0; i < ordersReader->size(); ++i)
			{
				O2G2Ptr<IO2GOrderRow> order = ordersReader->getRow(i);
				bool isOffer = (strcmp(order->getOfferID(), offer->getOfferID()) == 0);

				/*	TODO: attention, there may be orders for multiple instruments
				 *			we need to make distinction between EUR/USD and GBP/USD
				 *			for example.
				 */				
				if(isOffer)
				{
					fx::Position posout = posin;
					Order2Position(order, posout);
					outvec.push_back(posout);
				}
			}


			// reset
			m_responseListener->Reset();

			return true;
		}
	}



	bool Session::UpdatePriceOffer(
		IO2GResponse* response,
		std::map<misc::string, fx::Price>& outvec)
	{
		// factory
		O2G2Ptr<IO2GResponseReaderFactory> readerFactory = m_session->getResponseReaderFactory();
		if(!readerFactory)
		{
			AUDIT(m_audit, "session->getResponseReaderFactory failed.");
			return false;
		}
		// reader
		O2G2Ptr<IO2GOffersTableResponseReader> responseReader = readerFactory->createOffersTableReader(response);
		for(int i = 0; i < responseReader->size(); ++i)
		{
			O2G2Ptr<IO2GOfferRow> offer = responseReader->getRow(i);
			
			if(!m_responseListener->IsOfferTradable(offer))
				continue;
			
			if(!m_responseListener->IsOfferValid(offer))
				continue;
			
			// take the offer (considered valid)
			outvec[offer->getInstrument()] = fx::Price(offer->getAsk(), offer->getBid());
		}

		return true;
	}

	bool Session::UpdateCurrencies(IO2GResponse* response, misc::vector<fx::Currency>& outvec)
	{
		// factory
		O2G2Ptr<IO2GResponseReaderFactory> readerFactory = m_session->getResponseReaderFactory();
		if(!readerFactory)
		{
			AUDIT(m_audit, "session->getResponseReaderFactory failed.");
			return false;
		}
		// reader
		O2G2Ptr<IO2GOffersTableResponseReader> responseReader = readerFactory->createOffersTableReader(response);
		for(int i = 0; i < responseReader->size(); ++i)
		{
			O2G2Ptr<IO2GOfferRow> offer = responseReader->getRow(i);

			// low spread, no slippage, traded Mon-Fri
			if(!m_responseListener->IsOfferTradable(offer))
				continue;

			// has errors
			if(!m_responseListener->IsOfferValid(offer))
				continue;

			misc::string instrument = offer->getInstrument();
			const SymbolSettings& symbolSettings = m_tradingSettings->GetTradingSettings(instrument);
			
			bool bThreeLM = symbolSettings.m_ThreeLM;
			double margin = symbolSettings.m_MMR;
			if(!bThreeLM)
			{
				misc::string txt("\nThree Level Margin not valid for ");
				txt += instrument;
				AUDIT(m_audit, txt.c_str());
				continue;
			}

			double pointSize = offer->getPointSize();
			fx::Currency curr(
				instrument,
				fx::Price(offer->getAsk(), offer->getBid()),
				margin,
				0.,
				1. / pointSize
				);

			outvec.push_back(curr);
		}

		PipCost pipCostCalculator(m_iniParams, m_tradingSettings, outvec);
		for(int i = 0; i < responseReader->size(); ++i)
		{
			O2G2Ptr<IO2GOfferRow> offer = responseReader->getRow(i);

			// low spread, no slippage, traded Mon-Fri
			if(!m_responseListener->IsOfferTradable(offer))
				continue;

			// has errors
			if(!m_responseListener->IsOfferValid(offer))
				continue;

			double pipCost = pipCostCalculator.CalcPipCost(offer);
			
			misc::vector<fx::Currency>::iterator it = outvec.begin();
			for(; it != outvec.end(); ++it)
			{
				fx::Currency& curr = *it;
				if(curr.GetSymbol() == offer->getInstrument())
				{
					curr = fx::Currency(
						curr.GetSymbol(),
						curr.GetPrice(),
						curr.GetMargin(),
						pipCost,
						curr.GetRate2Pip());
					break;
				}				
			}
		}


		return !outvec.empty();
	}

	

	bool Session::Order2Position(IO2GOrderRow* src, fx::Position& dest)
	{
		const SymbolSettings& instrumentSettings = m_tradingSettings->GetTradingSettings(dest.GetCurrency().GetSymbol());
		int iBaseUnitSize = instrumentSettings.m_baseUnitSize;		

		misc::string orderID = src->getOrderID();
		misc::string tradeID = src->getTradeID(); // not opened in the market
		bool isBuy = (strcmp(src->getBuySell(), "LE") == 0);
		double rbuy = (isBuy == true ? src->getRate() : FLT_MAX);
		double rsell = (isBuy == true ? FLT_MAX : src->getRate());
		double amount = (double) src->getOriginAmount() / (double)iBaseUnitSize;
		fx::Price price(rbuy, rsell);
		const fx::Currency& currin = dest.GetCurrency();
		fx::Currency currency(currin.GetSymbol(), price, currin.GetMargin(), currin.GetPipCost(), currin.GetRate2Pip());
		double commission = 0;
		double interest = 0;
		dest = fx::Position(orderID, tradeID, currency, isBuy, amount, commission, interest);
		return true;
	}

	bool Session::CollectAllTrades(
		const fx::Position& posin,
		OrderMonitor& orderMonitor,
		misc::vector<fx::Position>& outvec)
	{
		// collect all open trades
		misc::vector<IO2GTradeRow*> openTrades;
		orderMonitor.getOpenTrades(openTrades);
		for(size_t i = 0; i < openTrades.size(); ++i)
		{
			IO2GTradeRow* tradeRow = openTrades[i];
			fx::Position openpos = posin;
			OpenTrade2Position(tradeRow, openpos);
			outvec.push_back(openpos);
			tradeRow->release();//decrement counter
		}

		// collect all closed trades		
		misc::vector<IO2GClosedTradeRow*> closedTrades;
		orderMonitor.getClosedTrades(closedTrades);
		for(size_t i = 0; i < closedTrades.size(); ++i)
		{
			IO2GClosedTradeRow* tradeRow = closedTrades[i];
			fx::Position closepos = posin;
			ClosedTrade2Position(tradeRow, closepos);
			outvec.push_back(closepos);
			tradeRow->release();//decrement counter
		}

		return true;
	}

	bool Session::OpenTrade2Position(IO2GTradeRow* src, fx::Position& dest)
	{
		/*	dest member has few fields correctly set (ex: currency).
		 *	For the rest of them we got the market response.
		 */
		misc::string orderID = src->getOpenOrderID();
		misc::string tradeID = src->getTradeID();
		const misc::string& symbol = dest.GetCurrency().GetSymbol();		
		bool isBuy = (strcmp(src->getBuySell(), O2G2::Buy) == 0);
		double openRate = src->getOpenRate();
		double buyRate = (isBuy == true ? openRate : FLT_MAX);
		double sellRate = (isBuy == true ? FLT_MAX : openRate);
		fx::Price openQuote(buyRate, sellRate);
		double MMR = dest.GetCurrency().GetMargin();
		double pipCost = dest.GetCurrency().GetPipCost();
		double rate2pip = dest.GetCurrency().GetRate2Pip();
		fx::Currency currency(symbol, openQuote, MMR, pipCost, rate2pip);

		const SymbolSettings& instrumentSettings = m_tradingSettings->GetTradingSettings(symbol);
		int iBaseUnitSize = instrumentSettings.m_baseUnitSize;
		int iAmount = src->getAmount() / iBaseUnitSize;

		double commission = 2 * src->getCommission();	// half at open, half at close time.
		double interest = src->getRolloverInterest();	// TODO: adds up every day

		dest = fx::Position(orderID, tradeID, currency, isBuy, iAmount, commission, interest);
		
		return true;
	}

	bool Session::ClosedTrade2Position(IO2GClosedTradeRow* src, fx::Position& dest)
	{
		misc::string orderID = src->getOpenOrderID();
		misc::string tradeID = src->getTradeID();
		const misc::string& symbol = dest.GetCurrency().GetSymbol();
		bool isBuy = (strcmp(src->getBuySell(), O2G2::Buy) == 0);
		double openRate = src->getOpenRate();
		double buyOpen = (isBuy == true ? openRate : FLT_MAX);
		double sellOpen = (isBuy == true ? FLT_MAX : openRate);
		fx::Price openQuote(buyOpen, sellOpen);
		double MMR = dest.GetCurrency().GetMargin();
		double pipCost = dest.GetCurrency().GetPipCost();
		double rate2pip = dest.GetCurrency().GetRate2Pip();
		fx::Currency currency(symbol, openQuote, MMR, pipCost, rate2pip);

		const SymbolSettings& instrumentSettings = m_tradingSettings->GetTradingSettings(symbol);
		int iBaseUnitSize = instrumentSettings.m_baseUnitSize;
		int iAmount = src->getAmount() / iBaseUnitSize; // matches exactly

		double commission = src->getCommission();		// we get now the entire value
		double interest = src->getRolloverInterest();	// TODO: adds up every day

		dest = fx::Position(orderID, tradeID, currency, isBuy, iAmount, commission, interest);

		double closeRate = src->getCloseRate();
		double buyClose = (isBuy == true ? FLT_MAX : closeRate);
		double sellClose = (isBuy == true ? closeRate : FLT_MAX);
		fx::Price closeQuote(buyClose, sellClose);
		dest.Close(closeQuote);

		return true;
	}

	bool Session::ReadHistPrices(IO2GResponse* response, HistPriceData& retPriceData)
	{
		if(!response)
		{
			AUDIT(m_audit, "IO2GResponse* parameter invalid.");
			return false;
		}

		if(response->getType() != MarketDataSnapshot)
		{
			AUDIT(m_audit, "response's type != MarketDataSnapshot.");
			return false;
		}

		O2G2Ptr<IO2GResponseReaderFactory> readerFactory = m_session->getResponseReaderFactory();
		if(!readerFactory)
		{
			AUDIT(m_audit, "session->getResponseReaderFactory failed.");
			return false;
		}
		
		O2G2Ptr<IO2GMarketDataSnapshotResponseReader> reader = readerFactory->createMarketDataSnapshotReader(response);
		if(!reader)
		{
			AUDIT(m_audit, "readerFactory->createMarketDataSnapshotReader failed.");
			return false;
		}

		size_t retpos = retPriceData.size();
		retPriceData.resize(retPriceData.size() + reader->size());

		misc::string sTime;
		for(int i = reader->size() - 1; i >=0; --i, ++retpos)
		{
			DATE dt = reader->getDate(i);
			FormatDate(dt, sTime);
			
			misc::cout << "\n\tdate= " << sTime;

			if(reader->isBar())
			{
				// DateTime
				// BidOpen
				// BidHigh
				// BidLow
				// BidClose
				// AskOpen
				// AskHigh
				// AskLow
				// AskClose
				// Volume
				HistoryPrice& hp = retPriceData[retpos];
				hp.EnableBar(true);
				hp.SetDate(dt);
				hp.SetCurrPrice(fx::Price(reader->getAsk(i), reader->getBid(i)));
				hp.SetOpenPrice(fx::Price(reader->getAskOpen(i), reader->getBidOpen(i)));
				hp.SetClosePrice(fx::Price(reader->getAskClose(i), reader->getBidClose(i)));
				hp.SetHighPrice(fx::Price(reader->getAskHigh(i), reader->getBidHigh(i)));
				hp.SetLowPrice(fx::Price(reader->getAskLow(i), reader->getBidLow(i)));
				hp.SetVolume(reader->getVolume(i));
			}
			else
			{
				HistoryPrice& hp = retPriceData[retpos];
				hp.EnableBar(false);
				hp.SetDate(dt);
				hp.SetCurrPrice(fx::Price(reader->getAsk(i), reader->getBid(i)));
			}
		}
		
		return true;
	}

	void Session::FormatDate(DATE date, misc::string& buf)
	{
		struct tm tmBuf = {0};
		CO2GDateUtils::OleTimeToCTime(date, &tmBuf);

		using namespace std;
		stringstream sstream;
		sstream << setw(2) << setfill('0') << tmBuf.tm_mon + 1 << "." \
			<< setw(2) << setfill('0') << tmBuf.tm_mday << "." \
			<< setw(4) << tmBuf.tm_year + 1900 << " " \
			<< setw(2) << setfill('0') << tmBuf.tm_hour << ":" \
			<< setw(2) << setfill('0') << tmBuf.tm_min << ":" \
			<< setw(2) << setfill('0') << tmBuf.tm_sec;
		//strcpy(buf, sstream.str().c_str());
		buf = sstream.str().c_str();
	}

	void Session::HandleTimeOut()
	{
		bool disconnected = true;
		while(disconnected)
		{
			bool bLogOut = Logout();
			sleep(2);
			disconnected = !Login();
			

			misc::string txt("\nLogout= ");
			txt += (bLogOut == true ? "OK" : "Failed");
			txt += "\nLogin= ";
			txt += (disconnected == false ? "OK" : "Failed");

			AUDIT(m_audit, txt.c_str());
		}		
	}

} // namespace fx

