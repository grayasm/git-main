/*
Copyright (C) 2017 Mihai Vasilian

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

#include "Session.hpp"
#include "unistd.hpp"
#include "stream.hpp"
#include <time.h>
#include <math.h>
#include <float.h>
#include "ResponseListener4Offers.hpp"
#include "OffersUpdater.hpp"
#include "OffersWriter.hpp"
#include "ErrorCodes.hpp"



namespace fxcm
{
	Session::Session(const fxcm::LoginParams& loginParams,
					 const fxcm::IniParams& iniParams)
	{
		m_loginParams = loginParams;
		m_iniParams = iniParams;

		m_session = CO2GTransport::createSession();	// IO2GSession*

		/*
			SessionStatusListener provides the session status as:
			Connected, Connecting, Disconnected, SessionLost, etc.
		*/
		m_sessionListener = new SessionStatusListener(
									m_session,
									true,
									m_loginParams.GetSessionID(),
									m_loginParams.GetPin());
		m_session->subscribeSessionStatus(m_sessionListener);



		/*
			Session as well as ResponseListener4Offers can output the Offers.
			OffersUpdater deals with locking, setting and getting the last Offers.
			OffersWriter deals with locking and writing all Offers to file.
		*/
		m_offersUpdater = new OffersUpdater(m_session);
		m_offersWriter = new OffersWriter(m_session, m_iniParams);

		/*
			ResponseListener4Offers works as a separate thread to receive
			Offers table updates. I avoid thread contention with other table
			updates (Trades, ClosedTrades, Messages, etc) and reduce complexity
			e.g. easier to add DB storage for quotes, etc.
		*/
		m_responseListener4Offers = new ResponseListener4Offers(m_session);
		m_session->subscribeResponse(m_responseListener4Offers);

		// optional can print the offers and save to file (otherwise not useful)
		m_responseListener4Offers->SetOffersUpdater(m_offersUpdater);
		m_responseListener4Offers->SetOffersWriter(m_offersWriter);


		/*
			ResponseListener4EntryOrders works as a separate thread to receive
			Orders table updates. This listener should be able to handle most
			common request for Orders table.
		*/
		m_responseListener4EntryOrders = new ResponseListener4EntryOrders(m_session);
		m_session->subscribeResponse(m_responseListener4EntryOrders);

		/*
			ResponseListener4HistoryPrices works as a separate thread to receive
			Orders table updates. The response is of type MarketDataSnapshot.
		*/
		m_responseListener4HistoryPrices = new ResponseListener4HistoryPrices(m_session);
		m_session->subscribeResponse(m_responseListener4HistoryPrices);

		// The listener does not use HistoryPricesUpdater. Only the Session does
		m_historyPricesUpdater = new HistoryPricesUpdater(m_session);


		/*
			ResponseListener4MarketOrders works as a separate thread to receive
			notifications about Market Orders/Positions tables updates. 
			This listener should be able to handle most common request related
			to posting the initial Market Order and getting the resulted trades.
		*/
		m_responseListener4MarketOrders = new ResponseListener4MarketOrders(m_session);
		m_session->subscribeResponse(m_responseListener4MarketOrders);
	}

	Session::~Session()
	{
		m_session->unsubscribeResponse(m_responseListener4Offers);
		m_responseListener4Offers->release();
		if (m_offersUpdater)
			delete m_offersUpdater;
		if (m_offersWriter)
			delete m_offersWriter;
		m_session->unsubscribeResponse(m_responseListener4EntryOrders);
		m_responseListener4EntryOrders->release();
		m_session->unsubscribeResponse(m_responseListener4HistoryPrices);
		m_responseListener4HistoryPrices->release();
		if (m_historyPricesUpdater)
			delete m_historyPricesUpdater;
		m_session->unsubscribeResponse(m_responseListener4MarketOrders);
		m_responseListener4MarketOrders->release();
		m_session->unsubscribeSessionStatus(m_sessionListener);
		m_sessionListener->release();
		m_session->release();
	}

	bool Session::Login()
	{
		m_sessionListener->reset();
		m_session->login(
			m_loginParams.GetLogin().c_str(),
			m_loginParams.GetPassword().c_str(),
			m_loginParams.GetUrl().c_str(),
			m_loginParams.GetConnection().c_str());
			
		return	m_sessionListener->WaitEvents() &&
				m_sessionListener->IsConnected();
	}

	bool Session::Logout()
	{
		bool waitEvents = m_sessionListener->IsConnected();
		m_sessionListener->reset();
		m_session->logout();
		/*  If account has expired or password is incorrect the session login
			errors out. In such cases the session listener is not notified
			on logout. Avoid a deadlock by returning immediately.
		*/
		if (!waitEvents)
			return m_sessionListener->IsDisconnected();

		return	m_sessionListener->WaitEvents() &&
				m_sessionListener->IsDisconnected();
	}

	int Session::GetOffers()
	{
		if (m_sessionListener->IsDisconnected())
		{
			misc::cout << __FUNCTION__
				<< ": Session disconnected" << std::endl;
			return ErrorCodes::ERR_DISCONNECTED;
		}
			

		/*
			As per FXCM 'GetOffers' example, we can get the Offers as either:
			(1) session login rules (here the table has all instruments), or
			(2) sending a session request (here the table has live updated instruments)
			After getting the response, in both cases all response listeners
			will get live updates for the Offers table until they are
			unsubscribed or session disconnected.
		*/
		O2G2Ptr<IO2GLoginRules> loginRules = m_session->getLoginRules();
		if (loginRules)
		{
			O2G2Ptr<IO2GResponse> response = NULL;
			if (loginRules->isTableLoadedByDefault(Offers))
			{
				response = loginRules->getTableRefreshResponse(Offers);
				if (response)
				{
					if (m_offersUpdater)
						m_offersUpdater->UpdateOffers(response);
					if (m_offersWriter)
						m_offersWriter->UpdateOffers(response);
				}
			}
			else
			{
				/*
					TODO:	So far the Offers table is loaded by default.
							This part is not tested.
				*/
				O2G2Ptr<IO2GRequestFactory> requestFactory =
					m_session->getRequestFactory();
				if (requestFactory)
				{
					O2G2Ptr<IO2GRequest> offersRequest =
						requestFactory->createRefreshTableRequest(Offers);
					misc::string requestID(offersRequest->getRequestID());
					m_responseListener4Offers->SetRequestID(requestID);

					m_session->sendRequest(offersRequest); // send REQUEST

					if (m_responseListener4Offers->WaitEvents())
					{
						response = m_responseListener4Offers->GetResponse();
						if (response)
						{
							if (m_offersUpdater)
								m_offersUpdater->UpdateOffers(response);
							if (m_offersWriter)
								m_offersWriter->UpdateOffers(response);
						}
					}
					else
					{
						misc::cout << __FUNCTION__
							<< ": Response waiting timeout expired" << std::endl;
						return ErrorCodes::ERR_TIMEOUT;
					}
				}
			}
		}
		else
		{
			misc::cout << __FUNCTION__ 
				<< ": Cannot get login rules" << std::endl;
			return ErrorCodes::ERR_NO_LOGIN_RULES;
		}

		return ErrorCodes::ERR_SUCCESS;
	} // GetOffers


	int Session::GetTradingSettings(TradingSettingsVec& tsvec, bool refresh/*= false*/)
	{
		if (!refresh && !m_tradingSettingsVec.empty())
		{
			tsvec = m_tradingSettingsVec;
			return ErrorCodes::ERR_SUCCESS;
		}

		m_tradingSettingsVec.clear();

		O2G2Ptr<IO2GLoginRules> loginRules = m_session->getLoginRules();
		if (!loginRules)
		{
			misc::cout << __FUNCTION__
				<< ": Cannot get login rules" << std::endl;
			return ErrorCodes::ERR_NO_LOGIN_RULES;
		}

		O2G2Ptr<IO2GResponse> accountsResponse =
			loginRules->getTableRefreshResponse(Accounts);
		if (!accountsResponse)
		{
			misc::cout << __FUNCTION__
				<< ": Cannot get Accounts response" << std::endl;
			return ErrorCodes::ERR_NO_ACOUNTS_RESPONSE;
		}

		O2G2Ptr<IO2GResponse> offersResponse =
			loginRules->getTableRefreshResponse(Offers);
		if (!offersResponse)
		{
			misc::cout << __FUNCTION__
				<< ": Cannot get Offers response" << std::endl;
			return ErrorCodes::ERR_NO_OFFERS_RESPONSE;
		}

		O2G2Ptr<IO2GTradingSettingsProvider> tradingSettingsProvider =
			loginRules->getTradingSettingsProvider();
		O2G2Ptr<IO2GResponseReaderFactory> factory =
			m_session->getResponseReaderFactory();
		if (!factory)
		{
			misc::cout << __FUNCTION__
				<< ": Cannot create response reader factory" << std::endl;
			return ErrorCodes::ERR_NO_RESPONSE_READER_FACTORY;
		}

		O2G2Ptr<IO2GAccountsTableResponseReader> accountsReader =
			factory->createAccountsTableReader(accountsResponse);
		O2G2Ptr<IO2GOffersTableResponseReader> instrumentsReader =
			factory->createOffersTableReader(offersResponse);
		O2G2Ptr<IO2GAccountRow>	account = accountsReader->getRow(0);
		for (int i = 0; i < instrumentsReader->size(); ++i)
		{
			O2G2Ptr<IO2GOfferRow> instrumentRow = instrumentsReader->getRow(i);
			const char* sInstrument = instrumentRow->getInstrument();
			int condDistStopForTrade =
				tradingSettingsProvider->getCondDistStopForTrade(sInstrument);
			int condDistLimitForTrade =
				tradingSettingsProvider->getCondDistLimitForTrade(sInstrument);
			int condDistEntryStop =
				tradingSettingsProvider->getCondDistEntryStop(sInstrument);
			int condDistEntryLimit =
				tradingSettingsProvider->getCondDistEntryLimit(sInstrument);
			int minQuantity =
				tradingSettingsProvider->getMinQuantity(sInstrument, account);
			int maxQuantity =
				tradingSettingsProvider->getMaxQuantity(sInstrument, account);
			int baseUnitSize =
				tradingSettingsProvider->getBaseUnitSize(sInstrument, account);
			O2GMarketStatus marketStatus =
				tradingSettingsProvider->getMarketStatus(sInstrument);

			int minTrailingStep = tradingSettingsProvider->getMinTrailingStep();
			int maxTrailingStep = tradingSettingsProvider->getMaxTrailingStep();

			double mmr = tradingSettingsProvider->getMMR(sInstrument, account);
			double mmr2 = 0, emr = 0, lmr = 0;
			bool b3LevelMargin =
				tradingSettingsProvider->getMargins(sInstrument,
													account,
													mmr2, emr, lmr);

			TradingSettings ts;
			ts.SetInstrument(sInstrument);
			ts.SetCondDistStopForTrade(condDistStopForTrade);
			ts.SetCondDistLimitForTrade(condDistLimitForTrade);
			ts.SetCondDistEntryStop(condDistEntryStop);
			ts.SetCondDistEntryLimit(condDistEntryLimit);
			ts.SetMinQuantity(minQuantity);
			ts.SetMaxQuantity(maxQuantity);
			ts.SetBaseUnitSize(baseUnitSize);
			ts.SetMarketStatus(marketStatus);
			ts.SetMinTrailingStep(minTrailingStep);
			ts.SetMaxTrailingStep(maxTrailingStep);
			ts.SetMMR(mmr);
			ts.SetMMR2(mmr2);
			ts.SetEMR(emr);
			ts.SetLMR(lmr);
			tsvec.push_back(ts);

			bool bDebug = false;
			if (bDebug)
			{
				std::string sMarketStatus = "unknown";
				switch (marketStatus)
				{
				case MarketStatusOpen:
					sMarketStatus = "Market Open";
					break;
				case MarketStatusClosed:
					sMarketStatus = "Market Close";
					break;
				}
				misc::cout << "Instrument: " << sInstrument << std::endl;
				misc::cout << "Status : " << sMarketStatus << std::endl;
				misc::cout << "Cond.Dist: ST=" << condDistStopForTrade
					<< "; LT=" << condDistLimitForTrade
					<< std::endl;
				misc::cout << "Cond.Dist entry stop=" << condDistEntryStop
					<< "; entry limit=" << condDistEntryLimit
					<< std::endl;
				misc::cout << "Quantity: Min=" << minQuantity
					<< "; Max=" << maxQuantity << std::endl;
				misc::cout << "Base unit size=" << baseUnitSize
					<< "; MMR=" << mmr << std::endl;

				if (b3LevelMargin)
				{
					misc::cout << "Three level maring: MMR=" << mmr2
						<< "; EMR=" << emr << "; LMR=" << lmr << std::endl;
				}
				else
				{
					misc::cout << "Single level margin: MMR=" << mmr2
						<< "; EMR=" << emr << "; LMR=" << lmr << std::endl;
				}
				misc::cout << "Trailing step: " << minTrailingStep
					<< "-" << maxTrailingStep << std::endl;
			}
		}

		return ErrorCodes::ERR_SUCCESS;
	} // GetTradingSettings


	int Session::GetTradingPermissions(const char* sInstrument, TradingPermissions& tp)
	{
		O2G2Ptr<IO2GLoginRules> loginRules = m_session->getLoginRules();
		if (!loginRules)
		{
			misc::cout << __FUNCTION__
				<< ": Cannot get login rules" << std::endl;
			return ErrorCodes::ERR_NO_LOGIN_RULES;
		}

		O2G2Ptr<IO2GPermissionChecker> permissionChecker =
			loginRules->getPermissionChecker();
		if (!permissionChecker)
		{
			misc::cout << __FUNCTION__
				<< ": Cannot get permission checker" << std::endl;
			return ErrorCodes::ERR_NO_PERMISSION_CHECKER;
		}

		if (strcmp(sInstrument, "") == 0)
			return ErrorCodes::ERR_NO_INSTRUMENT;

		tp.SetInstrument(sInstrument);
		tp.SetCanCreateMarketOpenOrder(permissionChecker->canCreateMarketOpenOrder(sInstrument));
		tp.SetCanChangeMarketOpenOrder(permissionChecker->canChangeMarketOpenOrder(sInstrument));
		tp.SetCanDeleteMarketOpenOrder(permissionChecker->canDeleteMarketOpenOrder(sInstrument));
		tp.SetCanCreateMarketCloseOrder(permissionChecker->canCreateMarketCloseOrder(sInstrument));		
		tp.SetCanChangeMarketCloseOrder(permissionChecker->canChangeMarketCloseOrder(sInstrument));		
		tp.SetCanDeleteMarketCloseOrder(permissionChecker->canDeleteMarketCloseOrder(sInstrument));		
		tp.SetCanCreateEntryOrder(permissionChecker->canCreateEntryOrder(sInstrument));		
		tp.SetCanChangeEntryOrder(permissionChecker->canChangeEntryOrder(sInstrument));		
		tp.SetCanDeleteEntryOrder(permissionChecker->canDeleteEntryOrder(sInstrument));		
		tp.SetCanCreateStopLimitOrder(permissionChecker->canCreateStopLimitOrder(sInstrument));		
		tp.SetCanChangeStopLimitOrder(permissionChecker->canChangeStopLimitOrder(sInstrument));		
		tp.SetCanDeleteStopLimitOrder(permissionChecker->canDeleteStopLimitOrder(sInstrument));		
		tp.SetCanRequestQuote(permissionChecker->canRequestQuote(sInstrument));		
		tp.SetCanAcceptQuote(permissionChecker->canAcceptQuote(sInstrument));		
		tp.SetCanDeleteQuote(permissionChecker->canDeleteQuote(sInstrument));		
		tp.SetCanCreateOCO(permissionChecker->canCreateOCO(sInstrument));		
		tp.SetCanCreateOTO(permissionChecker->canCreateOTO(sInstrument));		
		tp.SetCanJoinToNewContingencyGroup(permissionChecker->canJoinToNewContingencyGroup(sInstrument));		
		tp.SetCanJoinToExistingContingencyGroup(permissionChecker->canJoinToExistingContingencyGroup(sInstrument));		
		tp.SetCanRemoveFromContingencyGroup(permissionChecker->canRemoveFromContingencyGroup(sInstrument));		
		tp.SetCanChangeOfferSubscription(permissionChecker->canChangeOfferSubscription(sInstrument));		
		tp.SetCanCreateNetCloseOrder(permissionChecker->canCreateNetCloseOrder(sInstrument));		
		tp.SetCanChangeNetCloseOrder(permissionChecker->canChangeNetCloseOrder(sInstrument));		
		tp.SetCanDeleteNetCloseOrder(permissionChecker->canDeleteNetCloseOrder(sInstrument));		
		tp.SetCanCreateNetStopLimitOrder(permissionChecker->canCreateNetStopLimitOrder(sInstrument));
		tp.SetCanChangeNetStopLimitOrder(permissionChecker->canChangeNetStopLimitOrder(sInstrument));
		tp.SetCanDeleteNetStopLimitOrder(permissionChecker->canDeleteNetStopLimitOrder(sInstrument));
		tp.SetCanUseDynamicTrailingForStop(permissionChecker->canUseDynamicTrailingForStop());
		tp.SetCanUseDynamicTrailingForLimit(permissionChecker->canUseDynamicTrailingForLimit());
		tp.SetCanUseDynamicTrailingForEntryStop(permissionChecker->canUseDynamicTrailingForEntryStop());
		tp.SetCanUseDynamicTrailingForEntryLimit(permissionChecker->canUseDynamicTrailingForEntryLimit());
		tp.SetCanUseFluctuateTrailingForStop(permissionChecker->canUseFluctuateTrailingForStop());
		tp.SetCanUseFluctuateTrailingForLimit(permissionChecker->canUseFluctuateTrailingForLimit());
		tp.SetCanUseFluctuateTrailingForEntryStop(permissionChecker->canUseFluctuateTrailingForEntryStop());
		tp.SetCanUseFluctuateTrailingForEntryLimit(permissionChecker->canUseFluctuateTrailingForEntryLimit());

		return ErrorCodes::ERR_SUCCESS;
	} // GetTradingPermissions

	int Session::GetOrders()
	{
		O2G2Ptr<IO2GRequestFactory> requestFactory = m_session->getRequestFactory();
		if (!requestFactory)
		{
			misc::cout << __FUNCTION__
				<< ": Cannot create request factory" << std::endl;
			return ErrorCodes::ERR_NO_REQUEST_FACTORY;
		}

		const char* sAccountID = m_loginParams.GetAccount().c_str();
		O2G2Ptr<IO2GRequest> request =
			requestFactory->createRefreshTableRequestByAccount(Orders, sAccountID);
		if (!request)
		{
			misc::cout << __FUNCTION__
				<< ": Last error=" << requestFactory->getLastError() << std::endl;
			return ErrorCodes::ERR_NO_ORDERS_REQUEST;
		}

		m_responseListener4EntryOrders->SetRequestID(request->getRequestID());
		m_session->sendRequest(request);
		// asynchronous request sent to server, waiting
		if (!m_responseListener4EntryOrders->WaitEvents())
		{
			misc::cout << __FUNCTION__
				<< ": Response waiting timeout expired" << std::endl;
			return ErrorCodes::ERR_TIMEOUT;
		}

		O2G2Ptr<IO2GResponse> orderResponse =
			m_responseListener4EntryOrders->GetResponse();
		if (orderResponse)
		{
			if (orderResponse->getType() == O2GResponseType::GetOrders)
			{
				O2G2Ptr<IO2GResponseReaderFactory> responseReaderFactory =
					m_session->getResponseReaderFactory();
				O2G2Ptr<IO2GOrdersTableResponseReader> responseReader =
					responseReaderFactory->createOrdersTableReader(orderResponse);
				for (int i = 0; i < responseReader->size(); ++i)
				{
					O2G2Ptr<IO2GOrderRow> order = responseReader->getRow(i);

					misc::string orderId = order->getOrderID();
					misc::string accountId = order->getAccountID();
					misc::string orderType = order->getType();
					misc::string orderStatus = order->getStatus();
					misc::string orderOfferId = order->getOfferID();
					int orderAmount = order->getAmount();
					misc::string orderBuySell = order->getBuySell();
					double orderRate = order->getRate();
					misc::string orderTimeInForce = order->getTimeInForce();
					
					static bool bDebug = true;
					if (bDebug)
					{
						misc::cout << "OrderId=" << orderId.c_str()
							<< "AccountId=" << accountId.c_str() << ", "
							<< "Type=" << orderType.c_str() << ", "
							<< "Status=" << orderStatus.c_str() << ", "
							<< "OfferId=" << orderOfferId.c_str() << ", "
							<< "Amount=" << orderAmount << ", "
							<< "BuySell=" << orderBuySell.c_str() << ", "
							<< "Rate=" << orderRate << ", "
							<< "TimeInForce=" << orderTimeInForce << std::endl;
					}
				}
			}
		}

		return ErrorCodes::ERR_SUCCESS;
	} // GetOrders

	int Session::GetLastOffer(Offer& offer, const char* sInstrument)
	{
		if (m_offersUpdater)
			return m_offersUpdater->GetLastOffer(offer, sInstrument);

		misc::cout << __FUNCTION__
			<< ": OffersUpdater instance is not available" << std::endl;
		return ErrorCodes::ERR_NO_OFFER_AVAILABLE;
	} // GetLastOffer

	int Session::GetHistoryPrices(	const char* sInstrument, const char* sTimeframe,
									DATE dtFrom, DATE dtTo,
									HistoryPricesVec& historyPricesVec)
	{
		/* Start by validating the input data. */
		if (strlen(sTimeframe) == 0 ||
			(strcmp(sTimeframe, "m1") != 0 && strcmp(sTimeframe, "H1") != 0))
		{
			misc::cout << __FUNCTION__
				<< ": Error timeframe incorrect, use m1 or H1" << std::endl;
			return ErrorCodes::ERR_TIMEFRAME_INCORRECT;
		}

		if (dtFrom <= 0 || dtTo <= 0 || dtFrom >= dtTo)
		{
			misc::cout << __FUNCTION__
				<< ": DateFrom/DateTo data is incorrect" << std::endl;
			return ErrorCodes::ERR_DATE_INTERVAL_INCORRECT;
		}

		double _1H = 0.04167; // approximately 1h !!
		if (strcmp(sTimeframe, "m1") == 0 && dtTo - dtFrom > _1H)
		{
			misc::cout << __FUNCTION__
				<< ": Date interval must be <= 1h" << std::endl;
			return ErrorCodes::ERR_DATE_INTERVAL_INCORRECT;
		}
		
		if (strcmp(sTimeframe, "H1") == 0 && dtTo - dtFrom > _1H * 60)
		{
			misc::cout << __FUNCTION__
				<< ": Date interval must be <= 60h" << std::endl;
			return ErrorCodes::ERR_DATE_INTERVAL_INCORRECT;
		}


		/*	Instrument and Timeframe are not available to the market data reader
			so this needs to be set somewhere to reach the HistoryPrice.
			Clear prices on successive calls.
		*/
		if (m_historyPricesUpdater)
		{
			m_historyPricesUpdater->SetInstrument(sInstrument);
			m_historyPricesUpdater->SetTimeframe(sTimeframe);
			m_historyPricesUpdater->ClearPrices();
		}

		// get history prices
		O2G2Ptr<IO2GRequestFactory> requestFactory = m_session->getRequestFactory();
		if (!requestFactory)
		{
			misc::cout << __FUNCTION__
				<< ": Cannot create request factory" << std::endl;
			return ErrorCodes::ERR_NO_REQUEST_FACTORY;
		}

		// find timeframe by identifier
		O2G2Ptr<IO2GTimeframeCollection> timeframeCollection = 
			requestFactory->getTimeFrameCollection();
		O2G2Ptr<IO2GTimeframe> timeframe = timeframeCollection->get(sTimeframe);
		if (!timeframe)
		{
			misc::cout << __FUNCTION__
				<< ": Timeframe '" << sTimeframe << "' is incorrect!" << std::endl;
			return ErrorCodes::ERR_TIMEFRAME_INCORRECT;
		}

		O2G2Ptr<IO2GRequest> request =
			requestFactory->createMarketDataSnapshotRequestInstrument(
				sInstrument, timeframe, timeframe->getQueryDepth());
		DATE dtFirst = dtTo;
		// there is limit for returned candles amount
		do 
		{
			requestFactory->fillMarketDataSnapshotRequestTime(request, dtFrom, dtFirst, false);
			m_responseListener4HistoryPrices->SetRequestID(request->getRequestID());
			m_session->sendRequest(request);
			// asynchronous request sent to server, waiting
			if (!m_responseListener4HistoryPrices->WaitEvents())
			{
				misc::cout << __FUNCTION__
					<< ": Response waiting timeout expired" << std::endl;
				return ErrorCodes::ERR_TIMEOUT;
			}
			// shift "to" bound to oldest datetime of returned data
			O2G2Ptr<IO2GResponse> response = m_responseListener4HistoryPrices->GetResponse();
			if (!response || response->getType() != MarketDataSnapshot)
			{
				misc::cout << __FUNCTION__
					<< ": No market data snapshot response" << std::endl;
				return ErrorCodes::ERR_NO_MARKET_DATA_RESPONSE;
			}

			O2G2Ptr<IO2GResponseReaderFactory> readerFactory =
				m_session->getResponseReaderFactory();
			if (!readerFactory)
			{
				misc::cout << __FUNCTION__
					<< ": Cannot create response reader factory" << std::endl;
				return ErrorCodes::ERR_NO_RESPONSE_READER_FACTORY;
			}

			O2G2Ptr<IO2GMarketDataSnapshotResponseReader> reader =
				readerFactory->createMarketDataSnapshotReader(response);
			if (reader->size() > 0)
			{
				if (fabs(dtFirst - reader->getDate(0)) > 0.0001)
					dtFirst = reader->getDate(0); // earliest datetime of returned data
				else
					break;
			}
			else
			{
				misc::cout << "0 rows received" << std::endl;
				break;
			}

			if (m_historyPricesUpdater)
			{
				m_historyPricesUpdater->UpdatePrices(response);
			}

		} while (dtFirst - dtFrom > 0.0001);


		if (m_historyPricesUpdater)
		{
			historyPricesVec = m_historyPricesUpdater->GetPrices();
		}

		return ErrorCodes::ERR_SUCCESS;
	} // GetHistoryPrices

	int Session::OpenPosition(const Offer& offer, int lots, bool buy,
							  misc::vector<fx::Position>& result)
	{
		if (m_sessionListener->IsDisconnected())
		{
			misc::cout << __FUNCTION__
				<< ": Session disconnected" << std::endl;
			return ErrorCodes::ERR_DISCONNECTED;
		}

		O2G2Ptr<IO2GAccountRow> account = GetAccount();
		if (!account)
		{
			misc::cout << __FUNCTION__
				<< ": Error invalid account" << std::endl;
			return ErrorCodes::ERR_NO_ACCOUNT;
		}

		// must be 'netting account' -> maintenance type != 0
		if (strcmp(account->getMaintenanceType(), "0") == 0)
		{
			misc::cout << __FUNCTION__
				<< ": Error invalid account" << std::endl;
			return ErrorCodes::ERR_NO_ACCOUNT;
		}

		O2G2Ptr<IO2GLoginRules> loginRules = m_session->getLoginRules();
		if (!loginRules)
		{
			misc::cout << __FUNCTION__
				<< ": Cannot get login rules" << std::endl;
			return ErrorCodes::ERR_NO_LOGIN_RULES;
		}

		O2G2Ptr<IO2GTradingSettingsProvider> tradingSettingsProvider =
			loginRules->getTradingSettingsProvider();
		int iBaseUnitSize = tradingSettingsProvider->getBaseUnitSize(offer.GetInstrument().c_str(), account);
		int iAmount = iBaseUnitSize * lots;

		// create true market order request
		O2G2Ptr<IO2GRequestFactory> requestFactory = m_session->getRequestFactory();
		if (!requestFactory)
		{
			misc::cout << __FUNCTION__
				<< ": Cannot create request factory" << std::endl;
			return ErrorCodes::ERR_NO_REQUEST_FACTORY;
		}

		O2G2Ptr<IO2GValueMap> valuemap = requestFactory->createValueMap();
		valuemap->setString(Command, O2G2::Commands::CreateOrder);
		valuemap->setString(OrderType, O2G2::Orders::TrueMarketOpen);
		valuemap->setString(TimeInForce, O2G2::TIF::GTC);
		valuemap->setString(AccountID, account->getAccountID());
		valuemap->setString(OfferID, offer.GetOfferID().c_str());
		valuemap->setString(BuySell, (buy == true ? "B" : "S")); // "B" or "S"
		valuemap->setInt(Amount, iAmount);
		valuemap->setString(CustomID, "TrueMarketOrder");
		O2G2Ptr<IO2GRequest> request = requestFactory->createOrderRequest(valuemap);
		if (!request)
		{
			misc::cout << __FUNCTION__
				<< ": createOrderRequest failed with error: "
				<< requestFactory->getLastError() << std::endl;
			return ErrorCodes::ERR_NO_ORDERS_REQUEST;
		}


		m_responseListener4MarketOrders->SetRequestID(request->getRequestID());
		m_session->sendRequest(request);
		// asynchronous request sent to server, waiting
		if (!m_responseListener4MarketOrders->WaitEvents())
		{
			misc::cout << __FUNCTION__
				<< ": Response waiting timeout expired" << std::endl;
			return ErrorCodes::ERR_TIMEOUT;
		}



		// collect open trades
		const misc::vector<IO2GTradeRow*>& trades =
			m_responseListener4MarketOrders->GetTrades();

		result.clear();
		for (size_t i = 0; i < trades.size(); ++i)
		{
			IO2GTradeRow* trade = trades[i];

			misc::string openOrderID = trade->getOpenOrderID();
			misc::string tradeID = trade->getTradeID();
			misc::string symbol = offer.GetInstrument();
			bool isBuy = strcmp(trade->getBuySell(), O2G2::Buy) == 0;
			double openRate = trade->getOpenRate();
			double buyRate = (isBuy == true ? openRate : FLT_MAX); // @ask
			double sellRate = (isBuy == true ? FLT_MAX : openRate); // @bid
			fx::Price openQuote(buyRate, sellRate);
			double MMR = tradingSettingsProvider->getMMR(symbol.c_str(), account);
			double pipCost = m_pipCost.CalcPipCost(offer,
				m_iniParams.GetAccountSymbol(), iBaseUnitSize);
			double rate2pip = 1.0 / offer.GetPointSize();
			fx::Currency currency(symbol, openQuote, MMR, pipCost, rate2pip);
			int amount = trade->getAmount() / iBaseUnitSize;
			double commission = 2 * trade->getCommission(); // half at open, half at close
			double interest = trade->getRolloverInterest(); // TODO: adds up every day
			fx::Position position(openOrderID, tradeID, currency, isBuy,
				amount, commission, interest);
			result.push_back(position);
		}

		m_responseListener4MarketOrders->ClearResult();

		return ErrorCodes::ERR_SUCCESS;		
	} // OpenPosition


	int Session::ClosePosition(const Offer& offer, const fx::Position& position,
							   misc::vector<fx::Position>& result)
	{
		if (m_sessionListener->IsDisconnected())
		{
			misc::cout << __FUNCTION__
				<< ": Session disconnected" << std::endl;
			return ErrorCodes::ERR_DISCONNECTED;
		}

		O2G2Ptr<IO2GAccountRow> account = GetAccount();
		if (!account)
		{
			misc::cout << __FUNCTION__
				<< ": Error invalid account" << std::endl;
			return ErrorCodes::ERR_NO_ACCOUNT;
		}

		// must be 'netting account' -> maintenance type != 0
		if (strcmp(account->getMaintenanceType(), "0") == 0)
		{
			misc::cout << __FUNCTION__
				<< ": Error invalid account" << std::endl;
			return ErrorCodes::ERR_NO_ACCOUNT;
		}

		O2G2Ptr<IO2GRequestFactory> requestFactory = m_session->getRequestFactory();
		if (!requestFactory)
		{
			misc::cout << __FUNCTION__
				<< ": Cannot create request factory" << std::endl;
			return ErrorCodes::ERR_NO_REQUEST_FACTORY;
		}

		O2G2Ptr<IO2GLoginRules> loginRules = m_session->getLoginRules();
		if (!loginRules)
		{
			misc::cout << __FUNCTION__
				<< ": Cannot get login rules" << std::endl;
			return ErrorCodes::ERR_NO_LOGIN_RULES;
		}
		O2G2Ptr<IO2GTradingSettingsProvider> tradingSettingsProvider =
			loginRules->getTradingSettingsProvider();
		int iBaseUnitSize = tradingSettingsProvider->getBaseUnitSize(offer.GetInstrument().c_str(), account);
		int iAmount = iBaseUnitSize * position.GetAmount();

		O2G2Ptr<IO2GPermissionChecker> permissionChecker =
			loginRules->getPermissionChecker();

		O2G2Ptr<IO2GValueMap> valuemap = requestFactory->createValueMap();
		valuemap->setString(Command, O2G2::Commands::CreateOrder);
		const char* sInstrument = position.GetCurrency().GetSymbol().c_str();
		if (permissionChecker->canCreateMarketCloseOrder(sInstrument) != PermissionEnabled)
		{
			// in USA you need to use "OM" to close a position
			valuemap->setString(OrderType, O2G2::Orders::TrueMarketOpen);
		}
		else
		{
			valuemap->setString(OrderType, O2G2::Orders::TrueMarketClose);
			valuemap->setString(TradeID, position.GetTradeID().c_str());
		}	
		valuemap->setString(TimeInForce, O2G2::TIF::GTC);
		valuemap->setString(AccountID, account->getAccountID());
		valuemap->setString(OfferID, offer.GetOfferID().c_str());
		valuemap->setString(BuySell, position.IsBuy() ? O2G2::Sell : O2G2::Buy);
		valuemap->setInt(Amount, iAmount);
		valuemap->setString(CustomID, "CloseMarketOrder");

		O2G2Ptr<IO2GRequest> request = requestFactory->createOrderRequest(valuemap);
		if (!request)
		{
			misc::cout << __FUNCTION__
				<< ": createOrderRequest failed with error: "
				<< requestFactory->getLastError() << std::endl;
			return ErrorCodes::ERR_NO_ORDERS_REQUEST;
		}


		m_responseListener4MarketOrders->SetRequestID(request->getRequestID());
		m_session->sendRequest(request);
		// asynchronous request sent to server, waiting
		if (!m_responseListener4MarketOrders->WaitEvents())
		{
			misc::cout << __FUNCTION__
				<< ": Response waiting timeout expired" << std::endl;
			return ErrorCodes::ERR_TIMEOUT;
		}



		// collect closed trades
		const misc::vector<IO2GClosedTradeRow*>& closedTrades =
			m_responseListener4MarketOrders->GetClosedTrades();

		result.clear();
		for (size_t i = 0; i < closedTrades.size(); ++i)
		{
			IO2GClosedTradeRow* closedTrade = closedTrades[i];

			misc::string closeOrderID = closedTrade->getCloseOrderID();
			misc::string tradeID = closedTrade->getTradeID();
			misc::string symbol = offer.GetInstrument();
			bool isBuy = strcmp(closedTrade->getBuySell(), O2G2::Buy) == 0;
			double openRate = closedTrade->getOpenRate();
			double buyOpen = (isBuy == true ? openRate : FLT_MAX); // @ask
			double sellOpen = (isBuy == true ? FLT_MAX : openRate); // @bid
			fx::Price openQuote(buyOpen, sellOpen);
			double MMR = position.GetCurrency().GetMargin();
			double pipCost = position.GetCurrency().GetPipCost();
			double rate2pip = position.GetCurrency().GetRate2Pip();
			fx::Currency currency(symbol, openQuote, MMR, pipCost, rate2pip);
			int amount = closedTrade->getAmount() / iBaseUnitSize;
			double commission = closedTrade->getCommission(); // we got now the entire value
			double interest = closedTrade->getRolloverInterest(); // TODO: adds up every day
			fx::Position closeposition(closeOrderID, tradeID, currency, isBuy,
				iAmount, commission, interest);

			double closeRate = closedTrade->getCloseRate();
			double buyClose = (isBuy == true ? FLT_MAX : closeRate);
			double sellClose = (isBuy == true ? closeRate : FLT_MAX);
			fx::Price closeQuote(buyClose, sellClose);
			closeposition.Close(closeQuote);

			result.push_back(position);
		}

		m_responseListener4MarketOrders->ClearResult();

		return ErrorCodes::ERR_SUCCESS;
	} // ClosePosition

	IO2GAccountRow* Session::GetAccount()
	{
		O2G2Ptr<IO2GLoginRules> loginRules = m_session->getLoginRules();
		if (loginRules)
		{
			O2G2Ptr<IO2GResponse> response = loginRules->getTableRefreshResponse(Accounts);
			if (response)
			{
				O2G2Ptr<IO2GResponseReaderFactory> readerFactory =
					m_session->getResponseReaderFactory();
				if (readerFactory)
				{
					O2G2Ptr<IO2GAccountsTableResponseReader> reader =
						readerFactory->createAccountsTableReader(response);

					for (int i = 0; i < reader->size(); ++i)
					{
						O2G2Ptr<IO2GAccountRow> account = reader->getRow(i);
						if (account)
						{
							if (m_loginParams.GetAccount() == account->getAccountID())
							{
								if (strcmp(account->getMarginCallFlag(), "N") == 0 &&
									(strcmp(account->getAccountKind(), "32") == 0 ||
									strcmp(account->getAccountKind(), "36") == 0))
									return account.Detach();
							}
						}
					}
				}
			}
		}
		return NULL;
	} // GetAccount

} // namespace
