/*
Copyright (C) 2018 Mihai Vasilian
*/

#include "IndicatorBuilder.hpp"
#include "stream.hpp"
#include "TimeUtils.hpp"


namespace fx
{
    void IndicatorBuilder::Build(
        fx::MarketPlugin* plugin,
        const fx::Offer& offer,
        stl::vector<fx::IND*>& indicators)
    {
        if (plugin == NULL)
            throw stl::exception("IndicatorBuilder: invalid plugin");

        if (offer.GetInstrument().empty() || offer.GetTime().totime_t() == 0)
            throw stl::exception("IndicatorBuilder: invalid offer");

        sys::time tnow = offer.GetTime();
        double maxSec = 0;
        stl::string stimeFrame("H1");  // fxcm error for D1: use m1 or H1
        time_t min_tfval = sys::time::hourSEC;

        for (size_t i = 0; i < indicators.size(); ++i)
        {
            fx::IND* ind = indicators[i];

            if (ind == NULL || ind->IsValid())
                throw stl::exception("IndicatorBuilder: indicator is NULL or valid");

            time_t tfval = ind->GetTimeframe();
            min_tfval = stl::min(min_tfval, tfval);
            if (min_tfval < sys::time::hourSEC)
                stimeFrame = "m1";

            double indSec = (double)ind->GetPeriod() * tfval;
            maxSec = stl::max(maxSec, indSec);
        } // for(indicators)

        //    EMA always needs:
        //    1 full period x timeframe for first SMA
        //    1 full period x timeframe for itself (EMA)
        maxSec *= 2.0;

        time_t totaltime = (time_t) ::ceil(maxSec);
        int timeFrame = min_tfval;
        int tinc = (stimeFrame == "H1" ?
            24 * sys::time::hourSEC :
            60 * sys::time::minSEC);

        if (totaltime < sys::time::minSEC)
            throw stl::exception("IndicatorBuilder: timeframe is invalid");

        fx::TimeUtils::SetValidMarketTime(tnow, totaltime);

        time_t ti = 0;
        while (ti < totaltime)
        {
            // out of valid range
            if (ti > totaltime - tinc)
                tinc = totaltime - ti;

            if (tinc <= timeFrame)
                break;

            sys::time from = tnow - (totaltime - ti);
            sys::time to = tnow - (totaltime - ti - tinc);

            // don't ask for history prices from outside trading hours
            sys::time::WDay wday = from.wday();
            if ((wday == sys::time::SAT) ||
                (wday == sys::time::FRI && from.hour_() >= 22) ||
                (wday == sys::time::SUN && from.hour_() < 22))
            {
                // adjust minutes to full hour (doesn't matter in weekend)
                int subMin = from.min_() * sys::time::minSEC;

                if (wday == sys::time::SUN)
                {
                    int addHours = (22 - from.hour_()) * sys::time::hourSEC;
                    ti += (addHours - subMin);
                }
                else
                {
                    int addDays = (7 - (int)wday) * sys::time::daySEC;
                    int addHours = (22 - from.hour_()) * sys::time::hourSEC;
                    ti += (addDays + addHours - subMin);
                }

                continue;
            }

            stl::vector<fx::OHLCPrice> result;        
            int ret = plugin->GetOHLCPrices(offer.GetInstrument(), stimeFrame.c_str(), from, to, result);

            if (ret != 0)
            { // may get some weekend data, don't react for now.
            }

            stl::vector<fx::OHLCPrice>::iterator it = result.begin();
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
        stl::vector<fx::IND*>& indicators)
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


    void IndicatorBuilder::Check(stl::vector<fx::IND*>& indicators)
    {
        for (size_t i = 0; i < indicators.size(); ++i)
        {
            fx::IND* ind = indicators[i];

            if (!ind->IsValid())
                throw stl::exception("IndicatorBuilder: Check failed");
        }
    }

} // namespace
