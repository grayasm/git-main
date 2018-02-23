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

#ifndef __HistoryPrice_hpp__
#define __HistoryPrice_hpp__

#include "string.hpp"
#include "time.hpp"

namespace fxcm
{
	class HistoryPrice
	{
	public:
		HistoryPrice(
			const char* instrument,			// 'EUR/USD'
			const char* timeframe,			// m1 , H1 , ...
			misc::time time,				// UTC
			double BidOpen, double BidHigh, double BidLow, double BidClose,
			double AskOpen, double AskHigh, double AskLow, double AskClose,
			int volume);

		HistoryPrice(const HistoryPrice& tc);
		HistoryPrice& operator=(const HistoryPrice& tc);
		~HistoryPrice();

		const misc::string& GetInstrument() const;
		void SetInstrument(const char* instrument);

		const misc::string& GetTimeframe() const;
		void SetTimeframe(const char* timeframe);

		const misc::time& GetTime() const;
		void SetTime(const misc::time& val);

		double GetBidOpen() const;
		void SetBidOpen(double val);

		double GetBidHigh() const;
		void SetBidHigh(double val);

		double GetBidLow() const;
		void SetBidLow(double val);

		double GetBidClose() const;
		void SetBidClose(double val);

		double GetAskOpen() const;
		void SetAskOpen(double val);

		double GetAskHigh() const;
		void SetAskHigh(double val);

		double GetAskLow() const;
		void SetAskLow(double val);

		double GetAskClose() const;
		void SetAskClose(double val);

		int GetVolume() const;
		void SetVolume(int val);

	private:
		misc::string m_instrument;
		misc::string m_timeframe;
		misc::time m_time;
		double m_bidOpen, m_bidHigh, m_bidLow, m_bidClose;
		double m_askOpen, m_askHigh, m_askLow, m_askClose;
		int m_volume;
	};
} // namespace

#endif // __HistoryPrice_hpp__
