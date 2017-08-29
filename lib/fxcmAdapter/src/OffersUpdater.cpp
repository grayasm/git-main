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
	along with this program; if not, write to the Free Software Foundation, Inc.
	51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

	contact: grayasm@gmail.com
*/


#include "OffersUpdater.hpp"
#include "autocritical_section.hpp"
#include "stream.hpp"
#include "algorithm.hpp"
#include "ErrorCodes.hpp"
#include <iomanip>



namespace fxcm
{
	class EqById : public misc::unary_function<Offer, bool>
	{
	public:
		EqById(const misc::string& id) : m_id(id) { }
		EqById(const char* id) : m_id(id) { }
		bool operator()(const Offer& tc) const
		{
			return (tc.GetId() == m_id);
		}
	private:
		misc::string	m_id;
	};

	class EqByInstrument : public misc::unary_function<Offer, bool>
	{
	public:
		EqByInstrument(const misc::string& instrument)
			: m_instrument(instrument) { }
		EqByInstrument(const char* sInstrument)
			: m_instrument(sInstrument) { }
		bool operator()(const Offer& tc) const
		{
			return (tc.GetInstrument() == m_instrument);
		}
	private:
		misc::string	m_instrument;
	};

	OffersUpdater::OffersUpdater(IO2GSession* session)
	{
		m_session = session;
		m_session->addRef();
	}

	OffersUpdater::~OffersUpdater()
	{
		m_session->release();
	}

	void OffersUpdater::UpdateOffers(IO2GResponse* response)
	{
		// synchronize access to internal resource
		misc::autocritical_section autoCS(m_criticalSection);
		
		O2G2Ptr<IO2GResponseReaderFactory> readerFactory =
			m_session->getResponseReaderFactory();

		if (!readerFactory)
		{
			misc::cout << __FUNCTION__
				<< ": Cannot create response reader factory" << std::endl;
			return;
		}

		O2G2Ptr<IO2GOffersTableResponseReader> offersResponseReader =
			readerFactory->createOffersTableReader(response);

		if (!offersResponseReader)
		{
			misc::cout << __FUNCTION__
				<< ": Cannot create offers table reader" << std::endl;
			return;
		}

		for (int i = 0; i < offersResponseReader->size(); ++i)
		{
			O2G2Ptr<IO2GOfferRow> offerRow = offersResponseReader->getRow(i);

			Offer* currOffer = NULL;

			EqById pred(offerRow->getOfferID());
			misc::vector<Offer>::iterator fndit = 
				misc::find_if(m_offers.begin(), m_offers.end(), pred);
			if (fndit == m_offers.end())
			{
				Offer newOffer(offerRow->getOfferID(),
					offerRow->getInstrument(), offerRow->getDigits(),
					offerRow->getPointSize(), offerRow->getTime(),
					offerRow->getBid(), offerRow->getAsk());
				m_offers.push_back(newOffer);

				currOffer = &(*m_offers.rbegin());
			}
			else
			{
				if (offerRow->isTimeValid() &&
					offerRow->isBidValid() && offerRow->isAskValid())
				{
					fndit->SetDate(offerRow->getTime());
					fndit->SetBid(offerRow->getBid());
					fndit->SetAsk(offerRow->getAsk());

					currOffer = &(*fndit);
				}
			}

			if (currOffer)
			{
				misc::cout << currOffer->GetId() << ", "
					<< currOffer->GetInstrument()
					<< ", Bid=" << std::fixed << currOffer->GetBid()
					<< ", Ask=" << std::fixed << currOffer->GetAsk() 
					<< std::endl;
			}
		}
	}

	int OffersUpdater::GetLastOffer(Offer& offer, const char* sInstrument)
	{
		// synchronize access to internal resource
		misc::autocritical_section autoCS(m_criticalSection);

		EqByInstrument pred(sInstrument);
		misc::vector<Offer>::iterator fndit =
			misc::find_if(m_offers.begin(), m_offers.end(), pred);
		if (fndit == m_offers.end())
		{
			misc::cout << __FUNCTION__
				<< ": Cannot find Offer for '" << sInstrument << "'" << std::endl;
			return ErrorCodes::ERR_NO_OFFER_AVAILABLE;
		}

		offer = *fndit;

		return ErrorCodes::ERR_SUCCESS;
	}

	void OffersUpdater::FormatDate(DATE date, char* buf)
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
} // namespace
