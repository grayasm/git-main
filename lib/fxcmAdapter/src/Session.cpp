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
			OffersPrinter deals with locking, printing and updating the Offers.
		*/
		m_offersPrinter = new OffersPrinter(m_session);

		/*
			ResponseListener4Offers works as a separate thread to receive
			Offers table updates. I avoid thread contention with other table
			updates (Trades, ClosedTrades, Messages, etc) and reduce complexity
			e.g. easier to add DB storage for quotes, etc.
		*/
		m_responseListener4Offers = new ResponseListener4Offers(m_session);
		m_session->subscribeResponse(m_responseListener4Offers);

		// optional can print the offers (otherwise not useful)
		m_responseListener4Offers->SetOffersPrinter(m_offersPrinter);
	}

	Session::~Session()
	{
		if (m_offersPrinter)
			delete m_offersPrinter;
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
			return -100; // Disconnected
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
					if(m_offersPrinter)
						m_offersPrinter->PrintOffers(response);
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
						}
					}
					else
					{
						misc::cout << __FUNCTION__
							<< ": Response waiting timeout expired" << std::endl;
						return -101; // Timeout
					}
				}
			}
		}
		else
		{
			misc::cout << __FUNCTION__ 
				<< ": Cannot get login rules" << std::endl;
			return -102; // No login rules
		}

		return 0;
	}


} // namespace