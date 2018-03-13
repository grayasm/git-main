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

#include "IndicatorBuilder.hpp"
#include "stream.hpp"
#include "TimeUtils.hpp"


namespace fx
{
	void IndicatorBuilder::Build(
		fx::MarketPlugin* plugin,
		const fx::Offer& offer,
		misc::vector<fx::IND*>& indicators)
	{
		if (plugin == NULL)
			throw misc::exception("IndicatorBuilder: invalid plugin");

		if (offer.GetInstrument().empty() || offer.GetTime().totime_t() == 0)
			throw misc::exception("IndicatorBuilder: invalid offer");

		for (size_t i = 0; i < indicators.size(); ++i)
			if (indicators[i] == NULL || indicators[i]->IsValid())
				throw misc::exception("IndicatorBuilder: indicator is NULL or valid");

		misc::time tnow = offer.GetTime();
		double maxSec = 0;
		for (size_t i = 0; i < indicators.size(); ++i)
		{
			fx::IND* ind = indicators[i];
			double indSec = 1.5 * ind->GetPeriod() * ind->GetTimeframe();
			maxSec = misc::max(maxSec, indSec);
		}

		time_t totaltime = (time_t) ::ceil(maxSec);

		if (totaltime < misc::time::minSEC)
			throw misc::exception("IndicatorBuilder: timeframe is invalid");

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
			int ret = plugin->GetOHLCPrices(offer.GetInstrument(), "m1", from, to, result);

			if (ret != 0)
			{ // may get some weekend data, don't react for now.
			}

			misc::vector<fx::OHLCPrice>::iterator it = result.begin();
			for (; it != result.end(); ++it)
			{
				const fx::OHLCPrice& ohlc = *it;

				Update(offer, ohlc, indicators);
			}
		} // for(totaltime)


		Check(indicators);
	} // Build()


	void IndicatorBuilder::Update(
		const fx::Offer& offer,
		const fx::OHLCPrice& ohlc,
		misc::vector<fx::IND*>& indicators)
	{
		for (size_t i = 0; i < indicators.size(); ++i)
		{
			fx::IND* ind = indicators[i];

			// Open
			fx::Offer openo(offer);
			openo.SetTime(ohlc.GetTime() - 59);
			openo.SetBid(ohlc.GetBidOpen());
			openo.SetAsk(ohlc.GetAskOpen());
			openo.SetVolume(ohlc.GetVolume() / 4);
			ind->Update(openo);

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
				ind->Update(higho);
				

				lowo.SetTime(ohlc.GetTime() - 30);
				ind->Update(lowo);
			}
			else  // open below close
			{
				lowo.SetTime(ohlc.GetTime() - 45);
				ind->Update(lowo);

				higho.SetTime(ohlc.GetTime() - 30);
				ind->Update(higho);
			}


			// Close
			fx::Offer closeo(offer);
			closeo.SetTime(ohlc.GetTime());
			closeo.SetBid(ohlc.GetBidClose());
			closeo.SetAsk(ohlc.GetAskClose());
			closeo.SetVolume(ohlc.GetVolume() / 4);
			ind->Update(closeo);
		} // for(indicators)		
	} // Update(..)


	void IndicatorBuilder::Check(misc::vector<fx::IND*>& indicators)
	{
		for (size_t i = 0; i < indicators.size(); ++i)
		{
			fx::IND* ind = indicators[i];

			if (!ind->IsValid())
				throw misc::exception("IndicatorBuilder: Check failed");
		}
	}

} // namespace
