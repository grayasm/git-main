/*
Copyright (C) 2017 Mihai Vasilian
*/


#include "OffersUpdater.hpp"
#include "Utils.hpp"
#include "autocritical_section.hpp"
#include "stream.hpp"
#include "algorithm.hpp"
#include "ErrorCodes.hpp"
#include <iomanip>



namespace fxcm
{
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
		sys::autocritical_section autoCS(m_criticalSection);
		
		O2G2Ptr<IO2GResponseReaderFactory> readerFactory =
			m_session->getResponseReaderFactory();

		if (!readerFactory)
		{
			stl::cout << __FUNCTION__
				<< ": Cannot create response reader factory" << std::endl;
			return;
		}

		O2G2Ptr<IO2GOffersTableResponseReader> offersResponseReader =
			readerFactory->createOffersTableReader(response);

		if (!offersResponseReader)
		{
			stl::cout << __FUNCTION__
				<< ": Cannot create offers table reader" << std::endl;
			return;
		}

		for (int i = 0; i < offersResponseReader->size(); ++i)
		{
			O2G2Ptr<IO2GOfferRow> offerRow = offersResponseReader->getRow(i);

			stl::string instrument(offerRow->getInstrument());
			stl::string tradingStatus(offerRow->getTradingStatus());
			bool isTradingOpen = (tradingStatus == "O"); // "O" or "C"

			// prevent to retain an invalid offer like:
			// Id=1, I=EUR/USD, Pr=0, T=1970-JAN-1 0:0:0, PS=0, B=0, A=0
			if (!offerRow->isTimeValid() ||
				!offerRow->isBidValid() ||
				!offerRow->isAskValid())
				continue;

			sys::time oftime;
			Utils::FormatDate(offerRow->getTime(), oftime);

			if (oftime.year_() == 1970)
				continue;
			if (offerRow->getPointSize() == 0)
				continue;

			// update the last offer map
			OffersMap::iterator it = m_offersMap.find(instrument);
			if (it == m_offersMap.end())
			{
				fx::Offer newOffer(
					offerRow->getOfferID(),
					offerRow->getInstrument(),
					offerRow->getDigits(),
					offerRow->getPointSize(),
					oftime,
					offerRow->getBid(),
					offerRow->getAsk(),
					offerRow->getVolume(),
					isTradingOpen);

				OffersMap::value_type ofpair(newOffer.GetInstrument(), newOffer);
				m_offersMap.insert(ofpair);
			}
			else
			{
				it->second.SetTime(oftime);
				it->second.SetBid(offerRow->getBid());
				it->second.SetAsk(offerRow->getAsk());
				it->second.SetVolume(offerRow->getVolume());
				it->second.SetIsTradingOpen(isTradingOpen);
			}

			static bool bDebug = false;
			if (bDebug)
			{
				char dateBuf[32] = { 0 };
				Utils::FormatDate(offerRow->getTime(), dateBuf);

				stl::cout
					<< "Id=" << offerRow->getOfferID() << ", "
					<< "I=" << offerRow->getInstrument() << ", "
					<< "T=" << dateBuf << ", "
					<< "Bid=" << std::fixed << offerRow->getBid() << ", "
					<< "Ask=" << std::fixed << offerRow->getAsk() << ", "
					<< "Vol=" << std::fixed << offerRow->getVolume() << ", "
					<< (isTradingOpen == true ? "TS-O" : "TS-C")
					<< std::endl;
			}
		}
	}

	int OffersUpdater::GetLastOffer(fx::Offer& offer, const char* sInstrument)
	{
		// synchronize access to internal resource
		sys::autocritical_section autoCS(m_criticalSection);

		stl::string instrument(sInstrument);
		OffersMap::iterator it = m_offersMap.find(instrument);
		if (it == m_offersMap.end())
		{
			stl::cout << __FUNCTION__
				<< ": Cannot find Offer for '" << sInstrument << "'" << std::endl;
			return ErrorCodes::ERR_NO_OFFER_AVAILABLE;
		}

		offer = it->second;

		return ErrorCodes::ERR_SUCCESS;
	}

    int OffersUpdater::GetAllOffers(OffersMap& offers)
    {
        // synchronize access to internal resource
        sys::autocritical_section autoCS(m_criticalSection);

        offers = m_offersMap;

        return ErrorCodes::ERR_SUCCESS;
    }
} // namespace
