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
#include "ResponseListener4Offers.hpp"
#include "OffersPrinter.hpp"
#include "OffersUpdater.hpp"
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
			OffersPrinter deals with locking, printing and updating the last Offers.
			OffersUpdater deals with locking, setting and getting the last Offers.
			m_outputOffers turns off/on printing offers on the console all the time.
		*/
		m_outputOffers = false;
		m_offersPrinter = new OffersPrinter(m_session, m_outputOffers);
		m_offersUpdater = new OffersUpdater(m_session);

		/*
			ResponseListener4Offers works as a separate thread to receive
			Offers table updates. I avoid thread contention with other table
			updates (Trades, ClosedTrades, Messages, etc) and reduce complexity
			e.g. easier to add DB storage for quotes, etc.
		*/
		m_responseListener4Offers = new ResponseListener4Offers(m_session, m_outputOffers);
		m_session->subscribeResponse(m_responseListener4Offers);

		// optional can print the offers (otherwise not useful)
		m_responseListener4Offers->SetOffersPrinter(m_offersPrinter);
		m_responseListener4Offers->SetOffersUpdater(m_offersUpdater);


		/*
			ResponseListener4Orders works as a separate thread to receive
			Orders table updates. This listener should be able to handle most
			common request for Orders table.
		*/
		m_responseListener4Orders = new ResponseListener4Orders(m_session);
		m_session->subscribeResponse(m_responseListener4Orders);
	}

	Session::~Session()
	{
		m_session->unsubscribeResponse(m_responseListener4Orders);
		m_responseListener4Offers->SetOffersPrinter(NULL);
		if (m_offersPrinter)
			delete m_offersPrinter;
		m_responseListener4Offers->SetOffersUpdater(NULL);
		if (m_offersUpdater)
			delete m_offersUpdater;
		m_session->unsubscribeResponse(m_responseListener4Offers);
		m_responseListener4Offers->release();
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
		m_sessionListener->reset();
		m_session->logout();
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
					if (m_offersPrinter)
						m_offersPrinter->PrintOffers(response);
					if (m_offersUpdater)
						m_offersUpdater->UpdateOffers(response);
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
							if (m_offersPrinter)
								m_offersPrinter->PrintOffers(response);
							if (m_offersUpdater)
								m_offersUpdater->UpdateOffers(response);
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
	}

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

		m_responseListener4Orders->SetRequestID(request->getRequestID());
		m_session->sendRequest(request);
		// asynchronous request sent to server, waiting
		if (!m_responseListener4Orders->WaitEvents())
		{
			misc::cout << __FUNCTION__
				<< ": Response waiting timeout expired" << std::endl;
			return ErrorCodes::ERR_TIMEOUT;
		}

		O2G2Ptr<IO2GResponse> orderResponse =
			m_responseListener4Orders->GetResponse();
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
	}

	int Session::GetLastOffer(Offer& offer, const char* sInstrument)
	{
		if (m_offersUpdater)
			return m_offersUpdater->GetLastOffer(offer, sInstrument);

		misc::cout << __FUNCTION__
			<< ": OffersUpdater instance is not available" << std::endl;
		return ErrorCodes::ERR_NO_OFFER_AVAILABLE;
	}

	int Session::CreateELS(fx::Position& entry)
	{
		O2G2Ptr<IO2GAccountRow> account = GetAccount();
		if (!account)
		{
			misc::cout << __FUNCTION__
				<< ": No valid accounts" << std::endl;
			return ErrorCodes::ERR_NO_ACOUNTS_RESPONSE;
		}



	} // CreateELS

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