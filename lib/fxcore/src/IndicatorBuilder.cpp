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

		misc::time tnow = offer.GetTime();
		double maxSec = 0;
		misc::string stimeFrame("H1");

		for (size_t i = 0; i < indicators.size(); ++i)
		{
			fx::IND* ind = indicators[i];

			if (ind == NULL || ind->IsValid())
				throw misc::exception("IndicatorBuilder: indicator is NULL or valid");

			time_t tfval = ind->GetTimeframe();
			if (tfval < misc::time::hourSEC)
				stimeFrame = "m1";

			double indSec = (double)ind->GetPeriod() * tfval;
			maxSec = misc::max(maxSec, indSec);
		} // for(indicators)

		//	EMA always needs:
		//	1 full period x timeframe for first SMA
		//	1 full period x timeframe for itself (EMA)
		maxSec *= 2.0;

		time_t totaltime = (time_t) ::ceil(maxSec);
		int timeFrame = (stimeFrame == "H1" ?
			misc::time::hourSEC :
			misc::time::minSEC);
		int tinc = (stimeFrame == "H1" ?
			24 * misc::time::hourSEC :
			60 * misc::time::minSEC);

		if (totaltime < misc::time::minSEC)
			throw misc::exception("IndicatorBuilder: timeframe is invalid");

		fx::TimeUtils::SetValidMarketTime(tnow, totaltime);

		time_t ti = 0;
		while (ti < totaltime)
		{
			// out of valid range
			if (ti > totaltime - tinc)
				tinc = totaltime - ti;

			if (tinc <= timeFrame)
				break;

			misc::time from = tnow - (totaltime - ti);
			misc::time to = tnow - (totaltime - ti - tinc);

			// don't ask for history prices from outside trading hours
			misc::time::WDay wday = from.wday();
			if ((wday == misc::time::SAT) ||
				(wday == misc::time::FRI && from.hour_() >= 22) ||
				(wday == misc::time::SUN && from.hour_() < 22))
			{
				// adjust minutes to full hour (doesn't matter in weekend)
				int subMin = from.min_() * misc::time::minSEC;

				if (wday == misc::time::SUN)
				{
					int addHours = (22 - from.hour_()) * misc::time::hourSEC;
					ti += (addHours - subMin);
				}
				else
				{
					int addDays = (7 - (int)wday) * misc::time::daySEC;
					int addHours = (22 - from.hour_()) * misc::time::hourSEC;
					ti += (addDays + addHours - subMin);
				}

				continue;
			}

			misc::vector<fx::OHLCPrice> result;		
			int ret = plugin->GetOHLCPrices(offer.GetInstrument(), stimeFrame.c_str(), from, to, result);

			if (ret != 0)
			{ // may get some weekend data, don't react for now.
			}

			misc::vector<fx::OHLCPrice>::iterator it = result.begin();
			for (; it != result.end(); ++it)
			{
				const fx::OHLCPrice& ohlc = *it;

				Update(offer, ohlc, indicators);
			}

			ti += tinc;
			if (ti >= totaltime)
				break;
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