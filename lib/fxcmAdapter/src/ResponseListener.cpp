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


#include "ResponseListener.hpp"
#include "autocritical_section.hpp"
#include "stream.hpp"
#include <sstream>
#include <iomanip>


namespace fxcm
{
	ResponseListener::ResponseListener(IO2GSession* session)
	{
		m_Session = session;
		m_Session->addRef();
		m_RefCount = 1;
		// m_ResponseEvent is non-signaled
		m_RequestID = "";
		m_Instrument = "";
		m_Response = NULL;
		// m_Offers
		misc::cout.precision(2);
	}

	long ResponseListener::addRef()
	{
		misc::autocritical_section autocs(m_CriticalSection);
		m_RefCount++;
		return m_RefCount;
	}

	long ResponseListener::release()
	{
		misc::autocritical_section autocs(m_CriticalSection);
		m_RefCount--;
		if (m_RefCount == 0)	// see NonTableManagerSamples, any sample
			delete this;
		return m_RefCount;
	}

	void ResponseListener::onRequestCompleted(const char* requestId, IO2GResponse* response)
	{
		if (m_Response && m_RequestID == requestId)
		{
			m_Response = response;
			m_Response->addRef();
			if (response->getType() != CreateOrderResponse)
				m_ResponseEvent.unlock();
		}
	}

	void ResponseListener::onRequestFailed(const char* requestId, const char* error)
	{
		if (m_RequestID == requestId)
		{
			misc::cout << "The request has been failed. ID: "
				<< requestId << " : " << error << std::endl;
			m_ResponseEvent.unlock();
		}
	}

	void ResponseListener::onTablesUpdates(IO2GResponse* tablesUpdates)
	{
		if (tablesUpdates == NULL)
			return;

		/* When updating to new API, check if there are new enum ids. */
		O2GResponseType responseType = tablesUpdates->getType();
		switch (responseType)
		{
		case ResponseUnknown:
			misc::cout << __FUNCTION__ << " response::ResponseUnknown" << std::endl;
			break;

		case TablesUpdates:
			misc::cout << __FUNCTION__ << " response::TablesUpdates" << std::endl;
			PrintOffers(m_Session, tablesUpdates, m_Instrument);
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
			PrintLevel2MarketData(m_Session, tablesUpdates, m_Instrument);
			break;

		default:
			misc::cout << __FUNCTION__ << " O2GResponseType id does not exist"
				", is this a new API?" << std::endl;
			break;
		}
	}

	void ResponseListener::SetRequestID(const misc::string& requestID)
	{
		m_RequestID = requestID;
		if (m_Response)
		{
			m_Response->release();
			m_Response = NULL;
		}
		m_ResponseEvent.unlock();
	}

	void ResponseListener::SetInstrument(const misc::string& instrument)
	{
		m_Instrument = instrument;
	}

	bool ResponseListener::WaitEvents()
	{
		return (m_ResponseEvent.trylock(30000) == 0);
	}

	IO2GResponse* ResponseListener::GetResponse()
	{
		if (m_Response)
			m_Response->addRef();
		return m_Response;
	}

	void ResponseListener::PrintOffers(	IO2GSession* session,
										IO2GResponse* response,
										const misc::string& instrument)
	{
		misc::autocritical_section autocs(m_CriticalSection);

		O2G2Ptr<IO2GResponseReaderFactory> readerFactory =
			session->getResponseReaderFactory();

		if (!readerFactory)
		{
			misc::cout << __FUNCTION__
				<< "Cannot create response reader factory" << std::endl;
			return;
		}

		O2G2Ptr<IO2GOffersTableResponseReader> offersResponseReader =
			readerFactory->createOffersTableReader(response);

		if (!offersResponseReader)
		{
			misc::cout << __FUNCTION__
				<< "Cannot create offers table reader" << std::endl;
			return;
		}

		for (int i = 0; i < offersResponseReader->size(); ++i)
		{
			O2G2Ptr<IO2GOfferRow> offerRow = offersResponseReader->getRow(i);
			size_t index = m_Offers.FindOffer(offerRow->getOfferID());
			
			fx::Offer* offer = NULL;
			if (index != -1)
				offer = m_Offers.Get(index);
			
			if (offer)
			{
				if (offerRow->isTimeValid() &&
					offerRow->isBidValid() && offerRow->isAskValid())
				{
					offer->SetDate(offerRow->getTime());
					offer->SetBid(offerRow->getBid());
					offer->SetAsk(offerRow->getAsk());
				}
			}
			else
			{
				fx::Offer newOffer(offerRow->getOfferID(),
					offerRow->getInstrument(), offerRow->getDigits(),
					offerRow->getPointSize(), offerRow->getTime(),
					offerRow->getBid(), offerRow->getAsk());
				m_Offers.AddOffer(newOffer);
				
				// MT can screw the index
				index = m_Offers.FindOffer(offerRow->getOfferID());
				offer = m_Offers.Get(index);
			}

			if (!instrument.empty() || instrument.size() == 0 ||
				(instrument == offerRow->getInstrument()))
			{
				misc::cout << offer->GetId() << ", " << offer->GetInstrument()
					<< ", Bid=" << std::fixed << offer->GetBid()
					<< ", Ask=" << std::fixed << offer->GetAsk() << std::endl;
			}
		}
	}

	void ResponseListener::PrintLevel2MarketData(IO2GSession* session,
												IO2GResponse* response,
												const misc::string& instrument)
	{
		misc::autocritical_section autocs(m_CriticalSection);

		O2G2Ptr<IO2GResponseReaderFactory> readerFactory =
			session->getResponseReaderFactory();
		if (!readerFactory)
		{
			misc::cout << "Cannot create response reader factory" << std::endl;
			return;
		}

		O2G2Ptr<IO2GLevel2MarketDataUpdatesReader> level2ResponseReader =
			readerFactory->createLevel2MarketDataReader(response);
		if (!level2ResponseReader)
		{
			misc::cout << "Cannot create level 2 response reader" << std::endl;
			return;
		}

		char dateBuf[32] = { 0 };
		for (int i = 0; i < level2ResponseReader->getPriceQuotesCount(); ++i)
		{

		}
	}

	void ResponseListener::FormatDate(DATE date, char* buf)
	{
		struct tm tmBuf = { 0 };
		CO2GDateUtils::OleTimeToCTime(date, &tmBuf);

		using namespace std;
		stringstream sstream;
		sstream << setw(2) << setfill('0') << tmBuf.tm_mon + 1 << "." \
			<< setw(2) << setfill('0') << tmBuf.tm_mday << "." \
			<< setw(4) << tmBuf.tm_year + 1900 << " " \
			<< setw(2) << setfill('0') << tmBuf.tm_hour << ":" \
			<< setw(2) << setfill('0') << tmBuf.tm_min << ":" \
			<< setw(2) << setfill('0') << tmBuf.tm_sec;
		strcpy(buf, sstream.str().c_str());
	}

	ResponseListener::~ResponseListener()
	{
		if (m_Response)
			m_Response->release();
		m_Session->release();
		// m_ResponseEvent will CloseHandle itself on ~dtor
	}
} // namespace
