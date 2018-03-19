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

	"New Concepts in Technical Trading Systems.pdf"
	by J. Welles Wilder Jr.

	PSAR formula:
	-------------
	SAR(i) = SAR(i-1) + AF ( EP - SAR(i-1));

	if position is buy: SAR(i) <= min(L(i-1), L(i-2));
	if position is sell: SAR(i) >= max(H(i-1), H(i-2));

	EP: extreme price of the trade (Highest for a buy, Lowest for a sell)
	AF: start with +0.02 and increment with +0.02 
		for each new High/Low up to maximum +0.2
	SAR:first SAR value is the EP of previous position
	OBS:never move SAR(i) higher than min of today and yesterday low (if buy)
		never move SAR(i) lower than max of today and yesterday high (if sell)
*/


#include "PSAR.hpp"

namespace fx
{
	PSAR::PSAR()
	{
		Init();
	}

	PSAR::PSAR(
		const misc::string& instrument,
		Timeframe sec,
		bool buy,
		const fx::Price& sar)
	{
		Init();
	
		m_instrument = instrument;
		m_timeframe = sec;
		m_buy = buy;
		m_AF = 0.02;
		m_SAR = sar;
	}

	PSAR::~PSAR()
	{
	}

	PSAR::PSAR(const PSAR& tc)
	{
		Init();

		*this = tc;
	}

	PSAR& PSAR::operator=(const PSAR& tc)
	{
		if (this != &tc)
		{
			
		}
		return *this;
	}

	const misc::string& PSAR::GetInstrument() const
	{
		return m_instrument;
	}

	int PSAR::GetPeriod() const
	{

	}

	PSAR::Timeframe PSAR::GetTimeframe() const
	{
		return m_timeframe;
	}

	bool PSAR::IsValid() const
	{

	}

	void PSAR::Update(const fx::Offer& offer)
	{
		// Normalize to last valid timeframe as PSAR is always active.
		if (m_reftime.totime_t() == 0)
		{
			m_reftime = offer.GetTime();
			if (m_timeframe >= misc::time::minSEC)
				m_reftime -= m_reftime.sec_();
			if (m_timeframe >= misc::time::hourSEC)
				m_reftime -= m_reftime.min_();
			if (m_timeframe >= misc::time::daySEC)
				m_reftime -= m_reftime.hour_();
		}

		misc::time nextt = m_reftime + m_timeframe;
		const misc::time& currtime = offer.GetTime();
		
		// inside current bar (timeframe) - we use SAR already calculated;
		if (currtime < nextt)
		{
			double bid = offer.GetBid();
			double ask = offer.GetAsk();

			if (m_ohlc[1].GetBidOpen() == 0) // uninitialized
			{
				m_ohlc[1].SetBidOpen(bid);
				m_ohlc[1].SetBidHigh(bid);
				m_ohlc[1].SetBidLow(bid);
				m_ohlc[1].SetBidClose(bid);

				m_ohlc[1].SetAskOpen(ask);				
				m_ohlc[1].SetAskHigh(ask);
				m_ohlc[1].SetAskLow(ask);				
				m_ohlc[1].SetAskClose(ask);

				m_EP = fx::Price(offer.GetAsk(), offer.GetBid());
			}
			else
			{
				m_ohlc[1].SetBidClose(bid);	// can close anytime soon
				m_ohlc[1].SetAskClose(ask);

				if (bid > m_ohlc[1].GetBidHigh())
				{
					m_ohlc[1].SetBidHigh(bid);
					m_ohlc[1].SetAskHigh(ask);
				}
				else if (bid < m_ohlc[1].GetBidLow())
				{
					m_ohlc[1].SetBidLow(bid);
					m_ohlc[1].SetAskLow(ask);
				}
			}
		}
		// we closed 1 bar (timeframe) - must calculate the SAR for next bar
		else if (currtime >= nextt)
		{
			// track EP & AF
			if (m_buy && m_ohlc[1].GetBidHigh() > m_EP.GetSell())
			{
				m_EP = fx::Price(m_ohlc[1].GetAskHigh(), m_ohlc[1].GetBidHigh());
				m_AF += 0.02;
			}
			else if (!m_buy && m_ohlc[1].GetAskLow() < m_EP.GetBuy())
			{
				m_EP = fx::Price(m_ohlc[1].GetAskLow(), m_ohlc[1].GetBidLow());
				m_AF += 0.02;
			}


			// track LP (limit price to adjust the SAR if needed)
			fx::Price LP(0, 0);
			if (m_ohlc[0].GetBidOpen() == 0)
			{
				if (m_buy)
					LP = fx::Price(m_ohlc[1].GetAskLow(), m_ohlc[1].GetBidLow());
				else
					LP = fx::Price(m_ohlc[1].GetAskHigh(), m_ohlc[1].GetBidHigh());
			}
			else
			{
				if (m_buy)
				{
					double 
				}
				else
				{

				}
			}

			
		}
		
		


		
		
		// track MP (minim or maxim price allowed for SAR)
		fx::Price MP(0, 0);

		// SAR = SARp + AF (EP - SARp);
		double bSAR = m_SAR.GetBuy() + m_AF * (m_EP.GetBuy() - m_SAR.GetBuy());
		double sSAR = m_SAR.GetSell() + m_AF * (m_EP.GetSell() - m_SAR.GetSell());
		fx::Price SAR2(bSAR, sSAR);
		
		// SAR not higher than LOW of previous 2 time frames (for buy)
		// SAR not lower than HIGH of previous 2 time frames (for sell)
		if ((m_buy && sSAR > MP.GetSell()) ||
			(!m_buy && bSAR < MP.GetBuy()))
			SAR2 = MP;
		
		m_SAR = SAR2;
	}

	const misc::time& PSAR::GetRefTime() const
	{
		return m_reftime;
	}

	void PSAR::Init()
	{

	}
} // namespace
