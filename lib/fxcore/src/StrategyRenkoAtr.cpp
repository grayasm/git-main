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

#include "StrategyRenkoAtr.hpp"
#include "stream.hpp"


namespace fx
{
	StrategyRenkoAtr::StrategyRenkoAtr(
		fx::MarketPlugin* plugin,
		const misc::string& instrument,
		double renkoMin,
		int openHour,
		int closeHour)
	{
		m_plugin = plugin;
		m_instrument = instrument;
		m_renkoMin = renkoMin;
		m_atr = fx::ATR(m_instrument, 14, misc::time::hourSEC);
		m_sma = fx::SMA(m_instrument, 7, fx::SMA::PRICE_CLOSE, misc::time::hourSEC);
		/// ---------------------
		// m_tr - clean;
		// m_initialOffer - clean;
		// m_range - default with FLT_MAX;
		m_totalPL = 0;
		m_closedGPL = 0;
		m_openHour = 0;
		m_closeHour = 0;
		m_isCancelled = false;
	}

	StrategyRenkoAtr::~StrategyRenkoAtr()
	{
	}
	
	void StrategyRenkoAtr::Update(const fx::Offer& offer)
	{
		/*	In case the market plugin (session) encounters an error
			the strategy is disabled until the issue is fixed.
		*/
		if (m_isCancelled)
			return;

		// check the instrument
		if (offer.GetInstrument() != m_instrument)
			return;


		// update ATR, SMA
		m_atr.Update(offer);
		m_sma.Update(offer);

		if (!m_atr.IsValid())
			return;

		if (!m_sma.IsValid())
			return;

		// Renko brick is ATR(14)
		double price2pip = 1. / offer.GetPointSize();
		double pip2price = offer.GetPointSize();
		double renkoPL = 0;
		m_atr.GetValue(renkoPL);
		renkoPL *= price2pip;
		if (renkoPL < m_renkoMin)
			renkoPL = m_renkoMin;


		// Time of the offer
		misc::time tnow = offer.GetTime();
		bool canOpen = (tnow.hour_() >= m_openHour && tnow.hour_() < m_closeHour);

		
		// Over the night without position at market
		if (!canOpen && m_tr.IsEmpty())
		{
			// reset protective range over the night
			if (m_range.IsMinValid() || m_range.IsMaxValid())
				m_range = fx::Range();
			return;
		}


		// Waiting to enter the market
		if (m_tr.IsEmpty())
		{
			// start a new trading day?
			if (m_initialOffer.GetInstrument().empty())
			{
				m_initialOffer = offer;
				return;
			}

			double pips = (offer.GetAsk() - m_initialOffer.GetAsk()) * price2pip;

			if (pips > renkoPL && canOpen)
			{
				// check if range is in place
				canOpen = !m_range.IsMaxValid() ||
					(offer.GetAsk() > m_range.GetMax().GetBuy());

				// buy higher than SMA value
				if (canOpen && m_range.IsMaxValid())
				{
					fx::Price smaval;
					m_sma.GetValue(smaval);
					canOpen = offer.GetAsk() > smaval.GetBuy();
				}

				if (canOpen)
					OpenPosition(offer, true);

			}
			else if (pips < -renkoPL && canOpen)
			{
				// check if range is in place
				canOpen = !m_range.IsMinValid() ||
					(offer.GetAsk() < m_range.GetMin().GetBuy());

				// sell lower than SMA value
				if (canOpen && m_range.IsMinValid())
				{
					fx::Price smaval;
					m_sma.GetValue(smaval);
					canOpen = offer.GetAsk() < smaval.GetBuy();
				}

				if (canOpen)
					OpenPosition(offer, false);

			}
			
			m_totalPL = 0;
			return;
		}


		// A transaction is ongoing
		fx::Price curprice(offer.GetAsk(), offer.GetBid());
		double curPL = m_tr.GetPL(m_instrument, curprice);
		double curGPL = m_tr.GetGPL(m_instrument, curprice);
		double diffPL = curPL - m_totalPL;

		if (diffPL > renkoPL)
		{
			int inc = diffPL / renkoPL;
			m_totalPL += (inc * renkoPL);
			return;
		}

		if (diffPL < -2 * renkoPL)
		{
			bool buy = m_tr.GetBegin()->IsBuy();

			ClosePosition(offer);

			m_closedGPL += curGPL;
			misc::cout << "curPL=" << curPL << " closedGPL=" << m_closedGPL
				<< std::endl;


			if (!m_tr.IsEmpty())
				return; // error during ClosePosition!


			// if positive, reset previous range (if any)
			if (curPL > 0)
			{
				m_range = fx::Range();
			}
			else
			{
				if (buy)
				{
					fx::Price limprice(
						offer.GetAsk() + renkoPL * pip2price,
						offer.GetBid() + renkoPL * pip2price);
					m_range.SetMax(limprice);
				}
				else
				{
					fx::Price limprice(
						offer.GetAsk() - renkoPL * offer.GetPointSize(),
						offer.GetBid() - renkoPL * offer.GetPointSize());
					m_range.SetMin(limprice);
				}
			}


			// do not open in a range
			if (canOpen)
			{
				bool isBuy = !buy; // enter opposite direction
				if (isBuy && m_range.IsMaxValid())
				{
					canOpen = (offer.GetAsk() > m_range.GetMax().GetBuy());

					// buy higher than SMA value
					fx::Price smaval;
					m_sma.GetValue(smaval);
					if (canOpen)
						canOpen = offer.GetAsk() > smaval.GetBuy();
				}
				else if (!isBuy && m_range.IsMinValid())
				{
					canOpen = (offer.GetAsk() < m_range.GetMin().GetBuy());

					// sell lower than SMA value
					fx::Price smaval;
					m_sma.GetValue(smaval);
					if (canOpen)
						canOpen = offer.GetAsk() < smaval.GetBuy();
				}
			}

			// Either we are ranging or trading day has ended.
			if (!canOpen)
			{
				m_initialOffer = fx::Offer();
				m_totalPL = 0;
			}
			else
			{
				// Trading still possible
				buy = !buy;
				OpenPosition(offer, !buy);
				m_totalPL = 0;
			}
		} // (diffPL < -2 * renkoPL)
	} // Update(Offer)

	bool StrategyRenkoAtr::IsCanceled() const
	{
		return m_isCancelled;
	}

	void StrategyRenkoAtr::OpenPosition(const fx::Offer& offer, bool buy)
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

	void StrategyRenkoAtr::ClosePosition(const fx::Offer& offer)
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
} // namespace
