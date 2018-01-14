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


#include "HistoryPricesPrinter.hpp"
#include "ErrorCodes.hpp"
#include "autocritical_section.hpp"
#include "stream.hpp"
#include "algorithm.hpp"
#include <iomanip>


namespace fxcm
{
	HistoryPricesPrinter::HistoryPricesPrinter(IO2GSession* session, bool outputPrices)
	{
		m_session = session;
		m_session->addRef();
		m_outputPrices = outputPrices;
	}

	HistoryPricesPrinter::~HistoryPricesPrinter()
	{
		m_session->release();
	}

	int HistoryPricesPrinter::PrintPrices(IO2GResponse* response)
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
		for (int ii = reader->size() - 1; ii >= 0; ii--)
		{
			DATE dt = reader->getDate(ii);
			FormatDate(dt, sTime);
			if (reader->isBar())
			{
				misc::cout << "DateTime=" << sTime
					<< " BidOpen=" << reader->getBidOpen(ii)
					<< " BidHigh=" << reader->getBidHigh(ii)
					<< " BidLow=" << reader->getBidLow(ii)
					<< " BidClose=" << reader->getBidClose(ii)
					<< " AskOpen=" << reader->getAskOpen(ii)
					<< " AskHigh=" << reader->getAskHigh(ii)
					<< " AskLow=" << reader->getAskLow(ii)
					<< " AskClose=" << reader->getAskClose(ii)
					<< " Volume=" << reader->getVolume(ii) << std::endl;
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

	void HistoryPricesPrinter::FormatDate(DATE date, char* buf)
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
