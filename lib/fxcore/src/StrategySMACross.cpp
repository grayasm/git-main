/*
	Copyright (C) 2018 Mihai Vasilian

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

#include "StrategySMACross.hpp"
#include <math.h>
#include "stream.hpp"
#include "TimeUtils.hpp"



namespace fx
{
	StrategySMACross::StrategySMACross(
		fx::MarketPlugin* plugin,
		const misc::string& instrument,
		const fx::SMA& sma1,
		const fx::SMA& sma2)
	{
		m_plugin = plugin;
		m_instrument = instrument;
		m_sma1 = sma1;
		m_sma2 = sma2;
		// m_tr - default
		m_prevBid1 = 0;
		m_prevBid2 = 0;
		m_totalPL = 0;
		m_totalGPL = 0;
		m_isCancelled = false;
	}

	StrategySMACross::~StrategySMACross()
	{
	}

	void StrategySMACross::Update(const fx::Offer& offer)
	{
		/*	In case the market plugin (session) encounters an error
		the strategy is disabled until the issue is fixed.
		*/
		if (m_isCancelled)
			return;

		// check the instrument
		if (offer.GetInstrument() != m_instrument)
			return;

		// Build all indicators
		if (!m_sma1.IsValid() || !m_sma2.IsValid())
		{
			BuildAllIndicators(offer);
			return;
		}

		// update ATR, SMA
		m_sma1.Update(offer);
		m_sma2.Update(offer);

		fx::Price sma1P, sma2P;
		m_sma1.GetValue(sma1P);
		m_sma2.GetValue(sma2P);

		if (m_prevBid1 == 0)
		{
			m_prevBid1 = sma1P.GetSell();
			m_prevBid2 = sma2P.GetSell();
			return;
		}

		double bid1 = sma1P.GetSell();
		double bid2 = sma2P.GetSell();

		// check crossing SMA curves
		if (m_prevBid1 > m_prevBid2 && bid1 <= bid2)
		{
			if (!m_tr.IsEmpty())
				ClosePosition(offer);

			OpenPosition(offer, false); // sell
		}
		else if (m_prevBid1 < m_prevBid2 && bid1 >= bid2)
		{
			if (!m_tr.IsEmpty())
				ClosePosition(offer);

			OpenPosition(offer, true);	// buy
		}

		m_prevBid1 = sma1P.GetSell();
		m_prevBid2 = sma2P.GetSell();
	}

	bool StrategySMACross::IsCancelled() const
	{
		return m_isCancelled;
	}

	double StrategySMACross::GetClosedPL() const
	{
		return m_totalPL;
	}

	double StrategySMACross::GetClosedGPL() const
	{
		return m_totalGPL;
	}

	void StrategySMACross::OpenPosition(const fx::Offer& offer, bool buy)
	{
		misc::vector<fx::Position> result;
		int ret = m_plugin->OpenPosition(offer, 1, buy, result);

		if (ret != 0)
		{
			m_isCancelled = true;
			return;
		}

		for (size_t i = 0; i < result.size(); ++i)
			m_tr.Add(result[i]);
	}

	void StrategySMACross::ClosePosition(const fx::Offer& offer)
	{
		misc::vector<fx::Position>& npos =
			const_cast<misc::vector<fx::Position>&>(m_tr.GetPositions());

		misc::vector<fx::Position>::iterator it = npos.begin();
		for (; it != npos.end(); /*erase*/)
		{
			const fx::Position& pos = *it;

			misc::vector<fx::Position> result;
			int ret = m_plugin->ClosePosition(offer, pos, result);

			if (ret != 0)
			{
				m_isCancelled = true;
				return;
			}

			misc::vector<fx::Position>::iterator tmp = npos.erase(it);
			it = tmp;
		}
	}

	void StrategySMACross::BuildAllIndicators(const fx::Offer& offer)
	{
		// may not need to download history data
		if (m_sma1.IsValid() && m_sma2.IsValid())
			return;

		misc::time tnow = offer.GetTime();

		double sma1Sec = 1.5 * m_sma1.GetPeriod() * m_sma1.GetTimeframe();
		double sma2Sec = 1.5 * m_sma2.GetPeriod() * m_sma2.GetTimeframe();

		double maxSec = (sma1Sec < sma2Sec ? sma2Sec : sma1Sec);
		time_t totaltime = (time_t) ::ceil(maxSec);

		if (totaltime < misc::time::minSEC)
		{
			misc::cout << __FUNCTION__ <<
				": totaltime < misc::time::minSEC" << std::endl;
			m_isCancelled = true;
			return;
		}

		fx::TimeUtils::SetValidMarketTime(tnow, totaltime);

		for (time_t i = 0; i < totaltime; i += misc::time::hourSEC)
		{
			misc::time from = tnow - (totaltime - i);
			misc::time to = tnow - (totaltime - i - misc::time::hourSEC);

			// don't ask for history prices from outside trading hours
			if ((from.wday() == misc::time::SAT) ||
				(from.wday() == misc::time::FRI && from.hour_() >= 22) ||
				(from.wday() == misc::time::SUN && from.hour_() < 22))
				continue;

			// stop one candle before offer timestamp
			misc::time tvalid = tnow - misc::time::minSEC;
			if (to > tvalid)
				to = tvalid;

			// last interval too short?
			if (from + misc::time::minSEC > to)
				break;

			misc::vector<fx::OHLCPrice> result;
			int ret = m_plugin->GetOHLCPrices(m_instrument, "m1", from, to, result);

			if (ret != 0)
			{ // may get some weekend data, don't react for now.
			}

			misc::vector<fx::OHLCPrice>::iterator it = result.begin();
			for (; it != result.end(); ++it)
			{
				const fx::OHLCPrice& ohlc = *it;

				// Open
				fx::Offer openo(offer);
				openo.SetTime(ohlc.GetTime() - 59);
				openo.SetBid(ohlc.GetBidOpen());
				openo.SetAsk(ohlc.GetAskOpen());
				openo.SetVolume(ohlc.GetVolume() / 4);

				m_sma1.Update(openo);
				m_sma2.Update(openo);

				// High
				fx::Offer higho(offer);
				higho.SetBid(ohlc.GetBidHigh());
				higho.SetAsk(ohlc.GetAskHigh());
				higho.SetVolume(ohlc.GetVolume() / 4);

				// Low
				fx::Offer lowo(offer);
				lowo.SetBid(ohlc.GetBidLow());
				lowo.SetAsk(ohlc.GetAskLow());
				lowo.SetVolume(ohlc.GetVolume() / 4);

				// open above close
				if (ohlc.GetBidOpen() > ohlc.GetBidClose())
				{
					higho.SetTime(ohlc.GetTime() - 45);
					m_sma1.Update(higho);
					m_sma2.Update(higho);

					lowo.SetTime(ohlc.GetTime() - 30);
					m_sma1.Update(lowo);
					m_sma2.Update(lowo);
				}
				else  // open below close
				{
					lowo.SetTime(ohlc.GetTime() - 45);
					m_sma1.Update(lowo);
					m_sma2.Update(lowo);

					higho.SetTime(ohlc.GetTime() - 30);
					m_sma1.Update(higho);
					m_sma2.Update(higho);
				}


				// Close
				fx::Offer closeo(offer);
				closeo.SetTime(ohlc.GetTime());
				closeo.SetBid(ohlc.GetBidClose());
				closeo.SetAsk(ohlc.GetAskClose());
				closeo.SetVolume(ohlc.GetVolume() / 4);
				m_sma1.Update(closeo);
				m_sma2.Update(closeo);
			} // for(result)
		} // for(time_t i)


		// Check indicators
		if (!m_sma1.IsValid())
		{
			misc::cout << __FUNCTION__ <<
				": 1st SMA indicator could not be initialized" << std::endl;
			m_isCancelled = true;
			return;
		}

		if (!m_sma2.IsValid())
		{
			misc::cout << __FUNCTION__ <<
				": 2nd SMA indicator could not be initialized" << std::endl;
			m_isCancelled = true;
			return;
		}
	}
} // namespace
