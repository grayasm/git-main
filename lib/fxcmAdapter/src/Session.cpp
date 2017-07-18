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
#include "ResponseListener.hpp"
#include "unistd.hpp"
#include "stream.hpp"



namespace fxcm
{
	Session::Session(const fxcm::LoginParams& loginParams,
					 const fxcm::IniParams& iniParams)
	{
		m_loginParams = loginParams;
		m_session = CO2GTransport::createSession();	// IO2GSession*
		m_sessionListener = new SessionStatusListener(
									m_session,
									true,
									m_loginParams.GetSessionID(),
									m_loginParams.GetPin());
		m_session->subscribeSessionStatus(m_sessionListener);
	}

	Session::~Session()
	{
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

	bool Session::GetOffers()
	{
		bool bWasError = false;

		if (m_sessionListener->IsDisconnected())
		{
			bWasError = true;
			return !bWasError;
		}

		ResponseListener* responseListener = new ResponseListener(m_session);
		responseListener->SetInstrument(m_iniParams.GetInstrument());
		m_session->subscribeResponse(responseListener);

		O2G2Ptr<IO2GLoginRules> loginRules = m_session->getLoginRules();
		if (loginRules)
		{
			O2G2Ptr<IO2GResponse> response = NULL;
			if (loginRules->isTableLoadedByDefault(Offers))
			{
				response = loginRules->getTableRefreshResponse(Offers);
				if (response)
					responseListener->PrintOffers(m_session, response, "");
			}
			else
			{
				O2G2Ptr<IO2GRequestFactory> requestFactory =
					m_session->getRequestFactory();
				if (requestFactory)
				{
					O2G2Ptr<IO2GRequest> offersRequest =
						requestFactory->createRefreshTableRequest(Offers);
					misc::string requestID(offersRequest->getRequestID());
					responseListener->SetRequestID(requestID);

					// Send a request to FXCM server!
					m_session->sendRequest(offersRequest);

					if (responseListener->WaitEvents())
					{
						response = responseListener->GetResponse();
						if (response)
							responseListener->PrintOffers(m_session, response, "");
					}
					else
					{
						misc::cout << __FUNCTION__
							<< "Response waiting timeout expired" << std::endl;
						bWasError = true;
					}
				}
			}

			// So nothing for 10 seconds, let offers print.
			sleep(10);
			misc::cout << "Done!" << std::endl;
		}
		else
		{
			misc::cout << "Cannot get login rules" << std::endl;
			bWasError = true;
		}

		m_session->unsubscribeResponse(responseListener);
		responseListener->release();

		return !bWasError;
	}


} // namespace