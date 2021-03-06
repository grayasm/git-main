/*
	Copyright (C) 2018 Mihai Vasilian

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


#include "OffersWriter.hpp"
#include "Utils.hpp"
#include "unistd.hpp"
#include "autocritical_section.hpp"
#include "stream.hpp"
#include "algorithm.hpp"
#include "ErrorCodes.hpp"
#include <iomanip>



namespace fxcm
{
	OffersWriter::OffersWriter(IO2GSession* session, const IniParams& iniParams)
	{
		m_session = session;
		m_session->addRef();
		// m_criticalSection - unlocked;
		m_iniParams = iniParams;
		// m_offersVec - empty;
		sys::filename offersfile(m_iniParams.GetOffersFile());
		m_isEnabled = offersfile.access(F_OK); // true/false
		// m_writeFile - empty;
	}

	OffersWriter::~OffersWriter()
	{
		m_session->release();

		// write the remaining quotes (if any)
		WriteOffers();
	}

	void OffersWriter::UpdateOffers(IO2GResponse* response)
	{
		// synchronize access to internal resource
		sys::autocritical_section autoCS(m_criticalSection);

		if (!m_isEnabled)
			return;

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

			stl::string tradingStatus(offerRow->getTradingStatus());
			bool isTradingOpen = (tradingStatus == "O"); // "O" or "C"

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

			m_offersVec.push_back(newOffer);
		}

		if (m_offersVec.size() > 500)
		{
			WriteOffers();
		}
	}

	void OffersWriter::WriteOffers()
	{
		// m_CriticalSection is already locked

		if (!m_isEnabled)
			return;

		sys::filename offersfile(m_writeFile);
		
		// initialize the file to save the live quotes
		static int counter = 0;
		if (counter == 0)
		{
			offersfile = sys::filename(m_iniParams.GetOffersFile());

			sys::time tnow(::time(NULL));
			char stamp[32];
			sprintf(stamp, "_%02d_%02d_%02d_%02d_%02d_%02d",
				tnow.year_(),
				tnow.mon_(),
				tnow.mday_(),
				tnow.hour_(),
				tnow.min_(),
				tnow.sec_());
			stl::string corename(offersfile.get_core_name());
			corename += stamp;
			offersfile.set_core_name(corename);

			m_writeFile = offersfile;
		}

		// increment and reset (if needed)
		if (counter++ > 700)
			counter = 0;


		FILE* pf = fopen(offersfile.get_path().c_str(), "a+");
		if (pf != NULL)
		{
			for (size_t i = 0; i < m_offersVec.size(); ++i)
			{
				const fx::Offer& offer = m_offersVec[i];
				std::stringstream ss;
				ss << "Id=" << offer.GetOfferID().c_str() << ", ";
				ss << "I=" << offer.GetInstrument().c_str() << ", ";
				ss << "Pr=" << offer.GetPrecision() << ", ";
				ss << "T=" << offer.GetTime().tostring().c_str() << ", ";
				ss << "PS=" << offer.GetPointSize() << ", ";
				ss << "B=" << offer.GetBid() << ", ";
				ss << "A=" << offer.GetAsk() << ", ";
				ss << "Vol=" << offer.GetVolume() << "\n";
				
				std::string str(ss.str());
				fwrite(str.c_str(), 1, str.size(), pf);
			}

			fclose(pf);
		}

		m_offersVec.resize(0);
	}
} // namespace
