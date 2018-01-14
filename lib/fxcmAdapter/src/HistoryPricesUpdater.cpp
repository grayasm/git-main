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


#include "HistoryPricesUpdater.hpp"
#include "ErrorCodes.hpp"
#include "autocritical_section.hpp"
#include "stream.hpp"
#include "algorithm.hpp"
#include <iomanip>


namespace fxcm
{
	HistoryPricesUpdater::HistoryPricesUpdater(IO2GSession* session)
	{
		m_session = session;
		m_session->addRef();
	}

	HistoryPricesUpdater::~HistoryPricesUpdater()
	{
		m_session->release();
	}

	void HistoryPricesUpdater::SetInstrument(const char* sInstrument)
	{
		m_instrument = sInstrument;
	}

	void HistoryPricesUpdater::SetTimeframe(const char* sTimeframe)
	{
		m_timeframe = sTimeframe;
	}

	void HistoryPricesUpdater::ClearPrices()
	{
		m_historyPricesVec.clear();
	}

	int HistoryPricesUpdater::UpdatePrices(IO2GResponse* response)
	{
		misc::autocritical_section autoCS(m_criticalSection);

		if (!response)
		{
			misc::cout << __FUNCTION__
				<< ": No history prices response" << std::endl;
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
		if (!reader)
		{
			misc::cout << __FUNCTION__
				<< ": Cannot create market data table reader" << std::endl;
			return ErrorCodes::ERR_NO_MARKET_DATA_READER;
		}

		char sTime[20];
		misc::time mTime;
		/*	The customer sample reads the prices backward.
			
		for (int ii = reader->size() - 1; ii >= 0; ii--)
		*/		
		for (int ii = 0; ii < reader->size(); ++ii)
		{
			DATE dt = reader->getDate(ii);
			FormatDate(dt, sTime);
			FormatDate(dt, mTime);

			if (reader->isBar())
			{
				double bidOpen = reader->getBidOpen(ii);
				double bidHigh = reader->getBidHigh(ii);
				double bidLow = reader->getBidLow(ii);
				double bidClose = reader->getBidClose(ii);
				double askOpen = reader->getAskOpen(ii);
				double askHigh = reader->getAskHigh(ii);
				double askLow = reader->getAskLow(ii);
				double askClose = reader->getAskClose(ii);
				int volume = reader->getVolume(ii);

				HistoryPrice histPrice(
					m_instrument.c_str(),
					m_timeframe.c_str(),
					mTime,
					bidOpen, bidHigh, bidLow, bidClose,
					askOpen, askHigh, askLow, askClose,
					volume);
				m_historyPricesVec.push_back(histPrice);


				static bool debugOutput = true;
				if (debugOutput)
				{
					misc::cout << "DateTime=" << sTime
						<< " BidOpen=" << bidOpen
						<< " BidHigh=" << bidHigh
						<< " BidLow=" << bidLow
						<< " BidClose=" << bidClose
						<< " AskOpen=" << askOpen
						<< " AskHigh=" << askHigh
						<< " AskLow=" << askLow
						<< " AskClose=" << askClose
						<< " Volume=" << volume << std::endl;
				}
			}
			else
			{
				misc::cout << "DateTime=" << sTime
					<< " Bid=" << reader->getBid(ii)
					<< " Ask=" << reader->getAsk(ii) << std::endl;
			}
		}

		return ErrorCodes::ERR_SUCCESS;
	}

	const HistoryPricesUpdater::HistoryPricesVec& HistoryPricesUpdater::GetPrices() const
	{
		/*	If the prices are read backward, I may need to sort this vector
			in the oder of time increasing.
		*/
		return m_historyPricesVec;
	}

	void HistoryPricesUpdater::FormatDate(DATE date, char* buf)
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

	void HistoryPricesUpdater::FormatDate(DATE date, misc::time& mtime)
	{
		struct tm tmBuf = { 0 };
		CO2GDateUtils::OleTimeToCTime(date, &tmBuf);
	
		enum misc::time::Month month = (enum misc::time::Month)tmBuf.tm_mon;

		mtime = misc::time(
			tmBuf.tm_year + 1900,
			month,
			tmBuf.tm_mday,
			tmBuf.tm_hour,
			tmBuf.tm_min,
			tmBuf.tm_sec);

	}
} // namespace
