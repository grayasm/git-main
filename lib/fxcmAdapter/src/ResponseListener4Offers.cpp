/*
	Copyright (C) 2017 Mihai Vasilian

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

#include "ResponseListener4Offers.hpp"
#include "autocritical_section.hpp"
#include "stream.hpp"
#include <sstream>




namespace fxcm
{
	ResponseListener4Offers::ResponseListener4Offers(IO2GSession* session)
	{
		m_Session = session;
		m_Session->addRef();
		m_RefCount = 1;
		// m_ResponseEvent is non-signaled
		m_RequestID = "";
		m_Response = NULL;
		// m_CriticalSection - is unlocked
		m_offersPrinter = NULL;
		misc::cout.precision(6);
	}

	long ResponseListener4Offers::addRef()
	{
		misc::autocritical_section autocs(m_CriticalSection);
		m_RefCount++;
		return m_RefCount;
	}

	long ResponseListener4Offers::release()
	{
		misc::autocritical_section autocs(m_CriticalSection);
		m_RefCount--;
		if (m_RefCount == 0)	// see NonTableManagerSamples, any sample
			delete this;
		return m_RefCount;
	}

	void ResponseListener4Offers::onRequestCompleted(const char* requestId, IO2GResponse* response)
	{
		if (m_Response && m_RequestID == requestId)
		{
			m_Response = response;
			m_Response->addRef();
			if (response->getType() != CreateOrderResponse)
				m_ResponseEvent.unlock();
		}
	}

	void ResponseListener4Offers::onRequestFailed(const char* requestId, const char* error)
	{
		if (m_RequestID == requestId)
		{
			misc::cout << __FUNCTION__ 
				<< ": The request has been failed. ID: "
				<< requestId << " : " << error << std::endl;
			m_ResponseEvent.unlock();
		}
	}

	void ResponseListener4Offers::onTablesUpdates(IO2GResponse* tablesUpdates)
	{
		if (tablesUpdates == NULL)
			return;

		/*	When updating to new API, check if there are new enum ids. */
		O2GResponseType responseType = tablesUpdates->getType();
		switch (responseType)
		{
		case ResponseUnknown:
			misc::cout << __FUNCTION__ << " response::ResponseUnknown" << std::endl;
			break;

		case TablesUpdates:
			/*
				The table Offers is updated with this response type when
				initiated by - see Session.cpp, GetOffers:
					loginRules->isTableLoadedByDefault(Offers) +
					loginRules->getTableRefreshResponse(Offers)
			*/
			misc::cout << __FUNCTION__ << " response::TablesUpdates" << std::endl;
			if (m_offersPrinter)
				m_offersPrinter->PrintOffers(tablesUpdates);
			break;

		case MarketDataSnapshot:
			misc::cout << __FUNCTION__ << " response::MarketDataSnapshot" << std::endl;
			break;

		case GetAccounts:
			misc::cout << __FUNCTION__ << " response::GetAccounts" << std::endl;
			break;

		case GetOffers:
			misc::cout << __FUNCTION__ << " response::GetOffers" << std::endl;
			break;

		case GetOrders:
			misc::cout << __FUNCTION__ << " response::GetOrders" << std::endl;
			break;

		case GetTrades:
			misc::cout << __FUNCTION__ << " response::GetTrades" << std::endl;
			break;

		case GetClosedTrades:
			misc::cout << __FUNCTION__ << " response::GetClosedTrades" << std::endl;
			break;

		case GetMessages:
			misc::cout << __FUNCTION__ << " response::GetMessages" << std::endl;
			break;

		case CreateOrderResponse:
			misc::cout << __FUNCTION__ << " response::CreateOrderResponse" << std::endl;
			break;

		case GetSystemProperties:
			misc::cout << __FUNCTION__ << " response::GetSystemProperties" << std::endl;
			break;

		case CommandResponse:
			misc::cout << __FUNCTION__ << " response::CommandResponse" << std::endl;
			break;

		case MarginRequirementsResponse:
			misc::cout << __FUNCTION__ << " response::MarginRequirementsResponse" << std::endl;
			break;

		case GetLastOrderUpdate:
			misc::cout << __FUNCTION__ << " response::GetLastOrderUpdate" << std::endl;
			break;

		case MarketData:
			misc::cout << __FUNCTION__ << " response::MarketData" << std::endl;
			break;

		case Level2MarketData:
			misc::cout << __FUNCTION__ << " response::Level2MarketData" << std::endl;
			if(m_offersPrinter)
				m_offersPrinter->PrintLevel2MarketData(tablesUpdates);
			break;

		default:
			misc::cout << __FUNCTION__ << " O2GResponseType id does not exist"
				", is this a new API?" << std::endl;
			break;
		}
	}

	void ResponseListener4Offers::SetRequestID(const misc::string& requestID)
	{
		m_RequestID = requestID;
		if (m_Response)
		{
			m_Response->release();
			m_Response = NULL;
		}
		m_ResponseEvent.unlock();
	}

	bool ResponseListener4Offers::WaitEvents()
	{
		return (m_ResponseEvent.trylock(30000) == 0);
	}

	IO2GResponse* ResponseListener4Offers::GetResponse()
	{
		if (m_Response)
			m_Response->addRef();
		return m_Response; // ~O2G2Ptr will release() it.
	}

	void ResponseListener4Offers::SetOffersPrinter(OffersPrinter* op)
	{
		m_offersPrinter = op;
	}

	ResponseListener4Offers::~ResponseListener4Offers()
	{
		if (m_Response)
			m_Response->release();
		m_Session->release();
		// m_ResponseEvent will CloseHandle itself on ~dtor
		// m_offersPrinter is owned by the Session
	}

} // namespace