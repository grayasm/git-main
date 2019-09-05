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
	along with this program; if not, write to the Free Software Foundation,
	Inc. 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

	contact: grayasm@gmail.com
*/

#ifndef __OHLCPrice_hpp__
#define __OHLCPrice_hpp__

#include "string.hpp"
#include "time.hpp"

namespace fx
{
	class OHLCPrice
	{
	public:
		OHLCPrice();
		OHLCPrice(
			const char* instrument,			// 'EUR/USD'
			const char* timeframe,			// m1 , H1 , ...
			sys::time time,				// UTC
			double BidOpen, double BidHigh, double BidLow, double BidClose,
			double AskOpen, double AskHigh, double AskLow, double AskClose,
			int volume);

		OHLCPrice(const OHLCPrice& tc);
		OHLCPrice& operator=(const OHLCPrice& tc);
		~OHLCPrice();

		const stl::string& GetInstrument() const;
		void SetInstrument(const char* instrument);

		const stl::string& GetTimeframe() const;
		void SetTimeframe(const char* timeframe);

		const sys::time& GetTime() const;
		void SetTime(const sys::time& val);

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
		void Init();

	private:
		stl::string m_instrument;
		stl::string m_timeframe;
		sys::time m_time;
		double m_bidOpen, m_bidHigh, m_bidLow, m_bidClose;
		double m_askOpen, m_askHigh, m_askLow, m_askClose;
		int m_volume;
	};
} // namespace

#endif // __OHLCPrice_hpp__
