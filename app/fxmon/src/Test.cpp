/*
  Copyright (C) 2014 Mihai Vasilian

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


#include "unistd.hpp"
#include "stream.hpp"
#include "math.hpp"
#include "time.hpp"

#include "LoginParams.hpp"
#include "IniParams.hpp"
#include "Session.hpp"
#include "Offer.hpp"
#include "Price.hpp"
#include "Position.hpp"
#include "Transaction.hpp"
#include "ErrorCodes.hpp"
#include "StrategySMACross.hpp"
#include "StrategyEMACross.hpp"
#include "MarketPlugin4backtest.hpp"
#include "HistoryPricesReader.hpp"
#include "HistdatacomReader.hpp"
#include "SMA.hpp"
#include "EMA.hpp"
#include "ATR.hpp"
#include "SAR.hpp"
#include "BAR.hpp"
#include "HABAR.hpp"
#include "LWMA.hpp"
#include "ADX.hpp"
#include <list>


static void OpenPosition(const fx::Offer& offer, int lots, bool buy, fx::Position& result);
static void ClosePosition(const fx::Offer& offer, fx::Position& curpos);


static void Time2DATE(time_t tt, DATE& dt);

int test2()
{
    fxcm::LoginParams::Ptr loginParams = new fxcm::LoginParams("monitor.ini");
    fxcm::IniParams::Ptr iniParams = new fxcm::IniParams("monitor.ini");

    // checkObligatoryParams
    if (loginParams->GetLogin().empty() ||
        loginParams->GetPassword().empty() ||
        loginParams->GetUrl().empty() ||
        loginParams->GetConnection().empty() ||
        iniParams->GetInstrument().empty())
        return -1;

    fxcm::Session session(*loginParams, *iniParams);
    session.Login();
    session.GetOffers();
    
    // session.GetOrders();
    
    msleep(2000);
    
    int ret = 0;

    fx::Offer offer;
    ret = session.GetLastOffer(offer, "EUR/USD");
    if (ret == fxcm::ErrorCodes::ERR_SUCCESS)
    {
        stl::vector<fx::Position> result;
        session.GetOpenPositions(offer, result);
        
        stl::cout << "\n";
        for (int i = 0; i < result.size(); ++i)
            stl::cout << result[i].ToString().c_str() << std::endl;
    }    

    session.Logout();    
    return 0;
}


int test3()
{
    // OffersReader oreader("EUR/USD");
    HistoryPricesReader oreader("EUR/USD");
    // HistdatacomReader oreader("EUR/USD");

    fx::Offer prev_offer, curr_offer;
    
    fx::SMA sma1("EUR/USD", 10, sys::time::hourSEC, fx::SMA::BT_BAR, fx::SMA::PRICE_CLOSE); // (F)ast
    fx::SMA sma2("EUR/USD", 70, sys::time::hourSEC, fx::SMA::BT_BAR, fx::SMA::PRICE_CLOSE); // (S)low

    double prevBuy1 = 0, currBuy1 = 0;
    double prevBuy2 = 0, currBuy2 = 0;
    
    fx::Price av1, av2;
    fx::Position pos;
    int lots = 1;

    double totalPL = 0;
    double totalGPL = 0;


    while (true)
    {
        if (!oreader.GetOffer(curr_offer))
            break;
        
        sma1.Update(curr_offer);
        sma2.Update(curr_offer);

        if (!sma1.IsValid() || !sma2.IsValid())
            continue;
        
        if (prev_offer.GetInstrument().empty())
        {
            prev_offer = curr_offer;
            continue;
        }
        
        sma1.GetValue(av1);
        sma2.GetValue(av2);

        currBuy1 = av1.GetBuy();
        currBuy2 = av2.GetBuy();

        if (prevBuy1 == 0)
        {
            prevBuy1 = currBuy1;
            prevBuy2 = currBuy2;
            continue;
        }

        bool noPos = pos.GetCurrency().GetSymbol().empty();
        
        bool bSell = (prevBuy1 > prevBuy2 && currBuy1 <= currBuy2);
        bool bBuy = (prevBuy1 < prevBuy2 && currBuy1 >= currBuy2);
        
        if (bBuy || bSell)
        {
            // must close existing position?
            if (!noPos)
            {
                ClosePosition(curr_offer, pos);
                double currPL = pos.GetPL();
                double currGPL = pos.GetGPL();

                totalPL += currPL;
                totalGPL += currGPL;

                stl::cout << "currPL=" << currPL
                    << " totalPL=" << totalPL << " totalGPL=" << totalGPL
                    << std::endl;
            }

            bool b_buy = (bSell == true ? false : (bBuy == true ? true : false));
            OpenPosition(curr_offer, lots, b_buy, pos);
        }
        
        // update offer
        prev_offer = curr_offer;
        prevBuy1 = currBuy1;
        prevBuy2 = currBuy2;
    }


    FILE *pf = fopen("TradeResult.txt", "a+");
    if (pf == NULL)
        return 0;

    stl::string slog;
    slog += "totalPL=";
    slog += stl::from_value(totalPL, 2);
    slog += " totalGPL=";
    slog += stl::from_value(totalGPL, 2);
    slog += "\n";

    fwrite(slog.c_str(), sizeof(char), slog.size(), pf);
    fclose(pf);
    return 0;
}

int test4()
{
    // OffersReader oreader("EUR/USD");
    // HistoryPricesReader oreader("EUR/USD");
    fx::Offer offer("0", "EUR/USD", 5, 0.0001, sys::time(), 0, 0, 0, true);
    HistdatacomReader oreader(offer, 2017);    
    fx::EMA ema("EUR/USD", 14, sys::time::hourSEC, fx::SMA::BT_BAR, fx::SMA::PRICE_CLOSE);
    fx::SMA sma("EUR/USD", 14, sys::time::hourSEC, fx::SMA::BT_BAR, fx::SMA::PRICE_CLOSE);

    stl::string emalog("EMA_2017.txt");
    stl::string smalog("SMA_2017.txt");
    time_t timeframe = sys::time::hourSEC;


    FILE* f1 = fopen(emalog.c_str(), "w+");
    if (f1) fclose(f1);
    FILE* f2 = fopen(smalog.c_str(), "w+");
    if (f2) fclose(f2);


    while (oreader.GetOffer(offer))
    {
        if (!ema.IsValid() || !sma.IsValid())
        {
            ema.Update(offer);
            sma.Update(offer);
            continue;
        }

        const sys::time& reftime = ema.GetRefTime();
        sys::time nexttime = reftime + timeframe;
        const sys::time& currtime = offer.GetTime();

        // inside current timeframe
        if (currtime < nexttime)
        {            
            ema.Update(offer);
            sma.Update(offer);
            continue;
        }


        // ---- EMA ----
        {
            FILE* pf = fopen(emalog.c_str(), "a+");
            if (pf == NULL)
                continue;

            std::stringstream ss;
            ss << reftime.tostring().c_str() << " ";
            fx::Price pr;
            ema.GetValue(pr);
            ss << "Bid=" << pr.GetSell() << " Ask=" << pr.GetBuy() <<
                std::endl;

            std::string str = ss.str();
            fwrite(str.c_str(), sizeof(char), str.size(), pf);
            fclose(pf);
        }

        // ---- SMA ----
        {
            FILE* pf = fopen(smalog.c_str(), "a+");
            if (pf == NULL)
                continue;

            std::stringstream ss;
            ss << reftime.tostring().c_str() << " ";
            fx::Price pr;
            sma.GetValue(pr);
            ss << "Bid=" << pr.GetSell() << " Ask=" << pr.GetBuy() <<
                std::endl;

            std::string str = ss.str();
            fwrite(str.c_str(), sizeof(char), str.size(), pf);
            fclose(pf);
        }
        
        ema.Update(offer);
        sma.Update(offer);        
    }

    return 0;
}


int test5()
{
    // OffersReader oreader("EUR/USD");
    // HistoryPricesReader oreader("EUR/USD");
    fx::Offer offer("0", "EUR/USD", 5, 0.0001, sys::time(), 0, 0, 0, true);
    HistdatacomReader oreader(offer, 2017);    
    fx::ATR atr("EUR/USD", 14, sys::time::hourSEC);
    size_t timeframe = sys::time::hourSEC;


    stl::string logfile("ATR_2017.txt");
    FILE* pf = fopen(logfile.c_str(), "w+");
    if (pf) fclose(pf);


    while (oreader.GetOffer(offer))
    {
        if (!atr.IsValid())
        {
            atr.Update(offer);
            continue;
        }
        
        const sys::time& reftime = atr.GetRefTime();
        sys::time nexttime = reftime + timeframe;
        const sys::time& currtime = offer.GetTime();

        // inside current timeframe
        if (currtime < nexttime)
        {
            atr.Update(offer);
            continue;
        }

        // ----- ATR -----
        pf = fopen(logfile.c_str(), "a+");
        if (pf == NULL)
            continue;

        std::stringstream ss;
        ss << reftime.tostring().c_str() << " ";
        double mid = 0;
        atr.GetValue(mid);
        mid *= 1 / (0.0001);

        ss << "ATR=" << mid << std::endl;

        std::string str = ss.str();
        fwrite(str.c_str(), sizeof(char), str.size(), pf);
        fclose(pf);
        

        // new candle
        atr.Update(offer);
    }

    return 0;
}


int test6()
{
    // OffersReader oreader("EUR/USD");
    // HistoryPricesReader oreader("EUR/USD");
    fx::Offer offer("0", "EUR/USD", 5, 0.0001, sys::time(), 0, 0, 0, true);
    HistdatacomReader oreader(offer, 2017);    
    fx::SAR sar("EUR/USD", 14, sys::time::hourSEC);
    time_t timeframe = sys::time::hourSEC;
    fx::Price sarp(0, 0), epp(0, 0);
    fx::OHLCPrice ohlc;
    bool isBuy = true;
    double af = 0;


    stl::string logfile("PSAR_2017.txt");
    FILE* pf = fopen(logfile.c_str(), "w+");
    if (pf) fclose(pf);


    while (oreader.GetOffer(offer))
    {
        if (!sar.IsValid())
        {
            sar.Update(offer);
            continue;
        }


        const sys::time& reftime = sar.GetRefTime();
        sys::time nexttime = reftime + timeframe;
        const sys::time& currtime = offer.GetTime();
        
        if (currtime < nexttime && isBuy == sar.GetIsBuy())
        {
            sar.Update(offer);
            continue;
        }


        // sar changed
        pf = fopen(logfile.c_str(), "a+");
        if (pf == NULL)
            continue;

        std::stringstream ss;
        ss << reftime.tostring().c_str() << " ";
        ss << (sar.GetIsBuy() == true ? "L " : "S ");
        ss << " SAR=";
        sar.GetValue(sarp);
        ss << sarp.GetBuy() << "," << sarp.GetSell();
        sar.GetOHLC(ohlc);
        ss << " AO:" << ohlc.GetAskOpen();
        ss << " AH:" << ohlc.GetAskHigh();
        ss << " AL:" << ohlc.GetAskLow();
        ss << " AC:" << ohlc.GetAskClose();
            
        sar.GetEP(epp);
        ss << " EP=" << epp.GetBuy() << "," << epp.GetSell();

        sar.GetAF(af);
        ss << " AF:" << af;
        ss << std::endl;

        std::string str = ss.str();
        fwrite(str.c_str(), sizeof(char), str.size(), pf);
        fclose(pf);        
        isBuy = sar.GetIsBuy();


        // paint a new candle (or buy/sell switch)
        sar.Update(offer);
    }

    return 0;
}

int test7()
{
    // OffersReader oreader("EUR/USD");
    // HistoryPricesReader oreader("EUR/USD");
    fx::Offer offer("0", "EUR/USD", 5, 0.0001, sys::time(), 0, 0, 0, true);
    HistdatacomReader oreader(offer, 2017);    
    fx::BAR bar("EUR/USD", 14, sys::time::hourSEC);
    time_t timeframe = sys::time::hourSEC;
    bool isNew = false;
    fx::OHLCPrice ohlc;
    sys::time bartime;
    

    stl::string logfile("BAR_2017.txt");
    FILE* f1 = fopen(logfile.c_str(), "w+");
    if (f1) fclose(f1);


    while (oreader.GetOffer(offer))
    {
        if (!bar.IsValid())
        {
            bar.Update(offer);
            continue;
        }
    
        isNew = bar.IsNew(offer);
        if (isNew)
        {
            ohlc = bar.GetOHLC();
            bartime = bar.GetRefTime();
        }            

        bar.Update(offer);

        if (isNew)
        {
            FILE* pf = fopen(logfile.c_str(), "a+");
            if (pf == NULL)
                continue;

            std::stringstream ss;
            ss << bartime.tostring().c_str() << " ";
            ss << " BAR";
            ss << " AO:" << ohlc.GetAskOpen();
            ss << " AH:" << ohlc.GetAskHigh();
            ss << " AL:" << ohlc.GetAskLow();
            ss << " AC:" << ohlc.GetAskClose();

            ss << std::endl;

            std::string str = ss.str();
            fwrite(str.c_str(), sizeof(char), str.size(), pf);
            fclose(pf);
        }
    }

    return 0;
}


int test8()
{
    // OffersReader oreader("EUR/USD");
    // HistoryPricesReader oreader("EUR/USD");
    fx::Offer offer("0", "EUR/USD", 5, 0.0001, sys::time(), 0, 0, 0, true);
    HistdatacomReader oreader(offer, 2017);    
    fx::HABAR habar("EUR/USD", 14, sys::time::hourSEC);
    time_t timeframe = sys::time::hourSEC;
    bool isNew = false;
    fx::OHLCPrice ohlc;
    sys::time hatime;
    

    stl::string logfile("HABAR_2017.txt");
    FILE* f1 = fopen(logfile.c_str(), "w+");
    if (f1) fclose(f1);


    while (oreader.GetOffer(offer))
    {
        if (!habar.IsValid())
        {
            habar.Update(offer);
            continue;
        }

        isNew = habar.IsNew(offer);
        if (isNew)
        {
            ohlc = habar.GetOHLC();
            hatime = habar.GetRefTime();
        }            

        habar.Update(offer);

        if (isNew)
        {
            FILE* pf = fopen(logfile.c_str(), "a+");
            if (pf == NULL)
                continue;

            std::stringstream ss;
            ss << hatime.tostring().c_str() << " ";
            ss << " BAR";
            ss << " AO:" << ohlc.GetAskOpen();
            ss << " AH:" << ohlc.GetAskHigh();
            ss << " AL:" << ohlc.GetAskLow();
            ss << " AC:" << ohlc.GetAskClose();

            ss << std::endl;

            std::string str = ss.str();
            fwrite(str.c_str(), sizeof(char), str.size(), pf);
            fclose(pf);
        }
    }

    return 0;
}


int test9()
{
    // OffersReader oreader("EUR/USD");
    // HistoryPricesReader oreader("EUR/USD");
    fx::Offer offer("0", "EUR/USD", 5, 0.0001, sys::time(), 0, 0, 0, true);
    HistdatacomReader oreader(offer, 2017);    
    fx::LWMA lwma("EUR/USD", 14, sys::time::hourSEC, fx::SMA::BT_BAR, fx::SMA::PRICE_CLOSE);
    time_t timeframe = sys::time::hourSEC;
    bool isNew = false;
    fx::Price average;
    sys::time matime;


    stl::string logfile("LWMA_2017.txt");
    FILE* f1 = fopen(logfile.c_str(), "w+");
    if (f1) fclose(f1);


    while (oreader.GetOffer(offer))
    {
        if (!lwma.IsValid())
        {
            lwma.Update(offer);
            continue;
        }

        const sys::time& reftime = lwma.GetRefTime();
        sys::time nexttime = reftime + timeframe;
        isNew =  (offer.GetTime() >= nexttime);

        if (isNew)
        {
            lwma.GetValue(average);
            matime = lwma.GetRefTime();
        }

        lwma.Update(offer);

        if (isNew)
        {
            FILE* pf = fopen(logfile.c_str(), "a+");
            if (pf == NULL)
                continue;

            std::stringstream ss;
            ss << matime.tostring().c_str() << " ";
            ss << " BAR";
            ss << " A:" << average.GetBuy();
            ss << " B:" << average.GetSell();
            
            ss << std::endl;

            std::string str = ss.str();
            fwrite(str.c_str(), sizeof(char), str.size(), pf);
            fclose(pf);
        }
    }

    return 0;
}


int test10()
{
    fx::Offer offer("0", "EUR/USD", 3, 0.01, sys::time(), 0, 0, 0, true);
    HistdatacomReader oreader(offer, 2017);
    
    time_t timeframe = sys::time::daySEC;
    fx::BAR  bar("EUR/USD", 14, timeframe);
    fx::HABAR habar("EUR/USD", 14, timeframe);
    fx::LWMA lwma("EUR/USD", 14, timeframe, fx::SMA::BT_HABAR, fx::SMA::PRICE_CLOSE);
    
    


    stl::string logbar("BAR_2017.txt");
    stl::string loghabar("HABAR_2017.txt");
    stl::string loglwma("LWMA_2017.txt");

    FILE* f1 = fopen(logbar.c_str(), "w+");
    FILE* f2 = fopen(loghabar.c_str(), "w+");
    FILE* f3 = fopen(loglwma.c_str(), "w+");
    if (f1) fclose(f1);
    if (f2) fclose(f2);
    if (f3) fclose(f3);


    while (oreader.GetOffer(offer))
    {
        if (!bar.IsValid() ||
            !habar.IsValid() ||
            !lwma.IsValid())
        {
            bar.Update(offer);
            habar.Update(offer);
            lwma.Update(offer);
            continue;
        }

        if (bar.GetRefTime() != habar.GetRefTime() ||
            bar.GetRefTime() != lwma.GetRefTime())
        {
            throw stl::exception("time is inconsistent");
        }

        const sys::time& reftime = bar.GetRefTime();
        sys::time nexttime = reftime + timeframe;
        bool isNew = (offer.GetTime() >= nexttime);

        if (isNew)
        {
            f1 = fopen(logbar.c_str(), "a+");
            f2 = fopen(loghabar.c_str(), "a+");
            f3 = fopen(loglwma.c_str(), "a+");

            // write bar data -------------
            fx::OHLCPrice ohlc = bar.GetOHLC();
            std::stringstream ss;
            ss << bar.GetRefTime().tostring().c_str() << " ";
            ss << " BAR";
            ss << " AO:" << ohlc.GetAskOpen();
            ss << " AH:" << ohlc.GetAskHigh();
            ss << " AL:" << ohlc.GetAskLow();
            ss << " AC:" << ohlc.GetAskClose();
            ss << std::endl;
            std::string str = ss.str();
            fwrite(str.c_str(), sizeof(char), str.size(), f1);
            fclose(f1);

            // write habar data -----------
            ohlc = habar.GetOHLC();
            // std::stringstream ss;
            ss = std::stringstream();
            ss << habar.GetRefTime().tostring().c_str() << " ";
            ss << " HA-BAR";
            ss << " AO:" << ohlc.GetAskOpen();
            ss << " AH:" << ohlc.GetAskHigh();
            ss << " AL:" << ohlc.GetAskLow();
            ss << " AC:" << ohlc.GetAskClose();
            ss << std::endl;
            str = ss.str();
            fwrite(str.c_str(), sizeof(char), str.size(), f2);
            fclose(f2);

            // write lwma data ------------
            fx::Price average;
            lwma.GetValue(average);
            // std::stringstream ss;
            ss = std::stringstream();
            ss << lwma.GetRefTime().tostring().c_str() << " ";
            ss << " LWMA";
            ss << " A:" << average.GetBuy();
            ss << " B:" << average.GetSell();
            ss << std::endl;
            str = ss.str();
            fwrite(str.c_str(), sizeof(char), str.size(), f3);
            fclose(f3);
        }


        bar.Update(offer);
        habar.Update(offer);
        lwma.Update(offer);
    }

    return 0;
}

int test11()
{
    stl::cout << "\n\n\n"
        "Testing a crossover strategy with 2 simple moving averages\n"
        "SMA(15D) and SMA(60D), using EUR/USD 2017 real tick data.\n"
        "To calculate the data for the instrument (PipCost,Margin,PointBase,...)\n"
        "this program will connect to a demo account.\n"
        "\n";


    fxcm::LoginParams::Ptr loginParams = new fxcm::LoginParams("monitor.ini");
    fxcm::IniParams::Ptr iniParams = new fxcm::IniParams("monitor.ini");
    fxcm::Session session(*loginParams, *iniParams);
    session.Login();

    MarketPlugin4backtest plugin(&session, *iniParams);

    fx::Offer offer("0", "EUR/USD", 3, 0.01, sys::time(), 0, 0, 0, true);
    HistdatacomReader oreader(offer, 2017);

    time_t timeframe = sys::time::daySEC;
    stl::string instrument("EUR/USD");
    fx::SMA sma1(instrument, 15, timeframe, fx::SMA::BT_BAR, fx::SMA::PRICE_CLOSE);  // fast moving average
    fx::SMA sma2(instrument, 60, timeframe, fx::SMA::BT_BAR, fx::SMA::PRICE_CLOSE);// slow moving average

    if (!oreader.GetOffer(offer))
        return -1; // cannot get the offer?

    sys::time reftime = offer.GetTime();
    stl::cout << reftime.tostring().c_str() << std::endl;

    stl::cout << "Initialize SMA indicators\n";
    // Feed the 2 SMA indicators with quotes until they become valid.
    while (oreader.GetOffer(offer))
    {
        if (reftime.mon_() != offer.GetTime().mon_())
        {
            reftime = offer.GetTime();
            // show some progress, otherwise confusing and very slow
            stl::cout << reftime.tostring().c_str() << std::endl;
        }

        if (sma1.IsValid() && sma2.IsValid())
            break;

        sma1.Update(offer);
        sma2.Update(offer);
    }

    stl::cout << "Running the strategy\n";

    // initialize the strategy
    fx::StrategySMACross strategy(
        &plugin,
        instrument,
        sma1,
        sma2);

    while (oreader.GetOffer(offer))
    {
        if (reftime.mon_() != offer.GetTime().mon_())
        {
            reftime = offer.GetTime();
            // show some progress, otherwise confusing and very slow
            stl::cout << reftime.tostring().c_str() << std::endl;
        }

        // check for outside trading hours
        sys::time tnow = offer.GetTime();
        if ((tnow.wday() == sys::time::SAT) ||
            (tnow.wday() == sys::time::FRI && tnow.hour_() >= 22) ||
            (tnow.wday() == sys::time::SUN && tnow.hour_() < 22))
        {
            continue;
        }
        
        strategy.Update(offer);
    }

    session.Logout();

    stl::cout << "PL=" << strategy.GetClosedGPL() << std::endl <<
                 "GPL=" << strategy.GetClosedGPL() << std::endl;
    return 0;
}

int test12()
{
    stl::cout << "\n\n\n"
        "Testing a crossover strategy with 3 exponential moving averages and rsi\n"
        "EMA(D5), EMA(D50), EMA(D100) and RSI(5) using EUR/USD real tick data.\n"
        "To calculate the data for the instrument (PipCost,Margin,PointBase,...)\n"
        "this program will connect to a demo account.\n"
        "\n";
    /*  This strategy was described here, like this:
        https://forums.babypips.com/t/strategy/252434/4

        Price above 100 ema.
        Price above 50 ema.
        rsi (5) >= 50
        D1 current candle is bullish (wait for close)
        Then place entry buy order at last D1 max+2 pips
        Cancel the entry if not triggered by the D1 candle.
        Exit at price crossing the 5ema (both TP/SL)
        Similar logic for going short.
        Which pairs and date interval did you test?
        I can at least confirm the 70% success rate.
    */


    fxcm::LoginParams::Ptr loginParams = new fxcm::LoginParams("monitor.ini");
    fxcm::IniParams::Ptr iniParams = new fxcm::IniParams("monitor.ini");
    fxcm::Session session(*loginParams, *iniParams);
    session.Login();

    MarketPlugin4backtest plugin(&session, *iniParams);

    fx::Offer offer("0", "EUR/USD", 5, 0.0001, sys::time(), 0, 0, 0, true);
    HistdatacomReader oreader(offer, 1900); // 1900=2014 -> 2019

    time_t timeframe = sys::time::daySEC;
    stl::string instrument("EUR/USD");
    fx::EMA ema5(instrument, 5, timeframe, fx::SMA::BT_BAR, fx::SMA::PRICE_CLOSE); //5
    fx::EMA ema50(instrument, 50, timeframe, fx::SMA::BT_BAR, fx::SMA::PRICE_CLOSE); //50
    fx::EMA ema100(instrument, 100, timeframe, fx::SMA::BT_BAR, fx::SMA::PRICE_CLOSE); //100


    if (!oreader.GetOffer(offer))
        return -1; // cannot get the offer?

    sys::time reftime = offer.GetTime();
    stl::cout << reftime.tostring().c_str() << std::endl;

    stl::cout << "Initialize EMA indicators\n";
    // Feed the 2 SMA indicators with quotes until they become valid.
    while (oreader.GetOffer(offer))
    {
        if (reftime.mon_() != offer.GetTime().mon_())
        {
            reftime = offer.GetTime();
            // show some progress, otherwise confusing and very slow
            stl::cout << reftime.tostring().c_str() << std::endl;
        }

        if (ema5.IsValid() && ema50.IsValid() && ema100.IsValid())
            break;

        ema5.Update(offer);
        ema50.Update(offer);
        ema100.Update(offer);
    }

    stl::cout << "Running the strategy\n";

    // initialize the strategy
    fx::StrategyEMACross strategy(
        &plugin,
        instrument,
        ema5,
        ema50,
        ema100);

    while (oreader.GetOffer(offer))
    {
        if (reftime.mon_() != offer.GetTime().mon_())
        {
            reftime = offer.GetTime();
            // show some progress, otherwise confusing and very slow
            stl::cout << reftime.tostring().c_str() << std::endl;
        }

        // check for outside trading hours
        sys::time tnow = offer.GetTime();
        if ((tnow.wday() == sys::time::SAT) ||
            (tnow.wday() == sys::time::FRI && tnow.hour_() >= 22) ||
            (tnow.wday() == sys::time::SUN && tnow.hour_() < 22))
        {
            continue;
        }

        strategy.Update(offer);
    }

    session.Logout();

    // Log PnL and GPL values
    if (iniParams->GetEnableLogging())
    {
        FILE *pf = fopen(iniParams->GetLoggingFile().c_str(), "a+");
        if (pf != NULL)
        {
            stl::string msg("PnL=");
            msg += stl::from_value(strategy.GetClosedPL(), 2);
            msg += " GPL=";
            msg += stl::from_value(strategy.GetClosedGPL(), 2);
            msg += "\n\n";

            fwrite(msg.c_str(), sizeof(char), msg.size(), pf);
            fclose(pf);
        }
    }

    // Output PnL and GPL values
    stl::cout << "PL=" << strategy.GetClosedPL() << std::endl <<
        "GPL=" << strategy.GetClosedGPL() << std::endl;

    return 0;
}

int test13()
{
    fx::ADX adx("EURUSD", 14, sys::time::hourSEC);

    sys::time time_("01.01.2019 00:00:00");

    // pag.41   (my Open), High, Low, Close
    double tab[42][4] = {
        {   274,    274,    272,    272.75  },
        {   272.75, 273.25, 270.25, 270.75  },
        {   270.75, 272,    269.75, 270     },
        {   270,    270.75, 268,    269.25  },
        {   269.25, 270,    269,    269.75  },
        {   269.75, 270.50, 268,    270     },
        {   268.50, 268.50, 266.50, 266.50  },
        {   265.50, 265.50, 263,    263.25  },
        {   262.50, 262.50, 259,    260.25  },
        {   260.25, 263.50, 260,    263     },
        {   263,    269.50, 263,    266.50  },
        {   266.50, 267.25, 265,    267     },
        {   267,    267.50, 265.50, 265.75  },
        {   266,    269.75, 266,    268.50  },
        //totals
        {   268.25, 268.25, 263.25, 264.25  },
        {   264,    264,    261.50, 264     },
        {   266.25, 268,    266.25, 266.50  },
        {   266,    266,    264.25, 265.25  },
        {   267,    274,    267,    273     },
        {   273.50, 277.50, 273.50, 276.75  },
        {   276.75, 277,    272.50, 273     },
        {   272,    272,    269.50, 270.25  },
        {   267.75, 267.75, 264,    266.75  },
        {   266.75, 269.25, 263,    263     },
        {   263.50, 266,    263.50, 265.50  },
        {   265,    265,    262,    262.25  },
        {   262.25, 264.75, 261.50, 262.75  },
        {   261,    261,    255.50, 255.50  },
        // total
        {   255.50, 257.50, 253,    253     },
        {   254,    259,    254,    257.50  },
        {   257.50, 259.75, 257.50, 257.50  },
        {   257.25, 257.25, 250,    250     },
        {   250,    250,    247,    249.75  },
        {   252.75, 254.25, 252.75, 253.75  },
        {   253.75, 254,    250.50, 251.25  },
        {   251.25, 253.25, 250.25, 250.50  },
        {   251,    253.25, 251,    253     },
        {   251.75, 251.75, 250.50, 251.50  },
        {   251.50, 253,    249.50, 250     },
        {   250,    251.50, 245.25, 245.75  },
        {   245.75, 246.25, 240,    242.75  },
        {   242.75, 244.25, 241.25, 243.50  }
    };

    
    fx::Offer offer[4];
    offer[0] = fx::Offer("0", "EURUSD", 4, 1000, time_,            tab[0][0], tab[0][0] + 0.01, 1, true); // open
    offer[1] = fx::Offer("0", "EURUSD", 4, 1000, time_ + 60*20,    tab[0][1], tab[0][1] + 0.01, 1, true); // high
    offer[2] = fx::Offer("0", "EURUSD", 4, 1000, time_ + 60*40,    tab[0][2], tab[0][2] + 0.01, 1, true); // low
    offer[3] = fx::Offer("0", "EURUSD", 4, 1000, time_ + 60*55,    tab[0][3], tab[0][3] + 0.01, 1, true); // close

    adx.Update(offer[0]);
    adx.Update(offer[1]);
    adx.Update(offer[2]);
    adx.Update(offer[3]);

    for (size_t i = 1; i < 42; ++i)
    {
        sys::time reftime = time_ + i * sys::time::hourSEC;

        offer[0].SetBid(tab[i][0]);         // open
        offer[0].SetAsk(tab[i][0] + 0.01);
        offer[0].SetTime(reftime);

        offer[1].SetBid(tab[i][1]);             // high
        offer[1].SetAsk(tab[i][1] + 0.01);
        offer[1].SetTime(reftime + 60 * 20);

        offer[2].SetBid(tab[i][2]);
        offer[2].SetAsk(tab[i][2] + 0.01);      // low
        offer[2].SetTime(reftime + 60 * 40);

        offer[3].SetBid(tab[i][3]);
        offer[3].SetAsk(tab[i][3] + 0.01);      // close
        offer[3].SetTime(reftime + 60 * 55);

        adx.Update(offer[0]);
        adx.Update(offer[1]);
        adx.Update(offer[2]);
        adx.Update(offer[3]);

        printf("\nADX=%.2f\tadx=%.2f", adx.GetADX(), adx.GetADX2());
    }

    return 0;
}

int test14()
{
    fx::Offer offer("0", "EUR/USD", 5, 0.0001, sys::time(), 0, 0, 0, true);
    HistdatacomReader oreader(offer, 2018);

    time_t timeframe = sys::time::daySEC;
    fx::ADX adx("EUR/USD", 14, timeframe);
    fx::BAR bar("EUR/USD", 14, timeframe);
    
    stl::string logadx("ADX_2018.txt");
    
    FILE* f1 = fopen(logadx.c_str(), "w+");
    if (f1) fclose(f1);
    
    while (oreader.GetOffer(offer))
    {
        bool isNew = bar.IsNew(offer);

        if (isNew && adx.IsValid())
        {
            f1 = fopen(logadx.c_str(), "a+");

            // write bar data -------------
            const fx::OHLCPrice& ohlc = bar.GetOHLC();
            std::stringstream ss;
            ss << bar.GetRefTime().tostring().c_str() << " ";
            ss << " BAR";
            ss << " AO:" << ohlc.GetAskOpen();
            ss << " AH:" << ohlc.GetAskHigh();
            ss << " AL:" << ohlc.GetAskLow();
            ss << " AC:" << ohlc.GetAskClose();
            ss << " ADX:" << adx.GetADX();
            ss << " ADX2:" << adx.GetADX2();
            ss << std::endl;
            std::string str = ss.str();
            fwrite(str.c_str(), sizeof(char), str.size(), f1);
            fclose(f1);
        }
        
        bar.Update(offer);
        adx.Update(offer);

        if (adx.GetRefTime() != bar.GetRefTime())
        {
            throw stl::exception("time is inconsistent");
        }        
    }

    return 0;
}

static void Time2DATE(time_t tt, DATE& dt)
{
    struct tm *tmNow = gmtime(&tt);
    CO2GDateUtils::CTimeToOleTime(tmNow, &dt);
}


void OpenPosition(const fx::Offer& offer, int lots, bool buy, fx::Position& result)
{
    static int orderID = 0;
    static int tradeID = 0;

    fx::Price price(offer.GetAsk(), offer.GetBid()); //buy@ask, sell@bid
    fx::Currency currency(
        offer.GetInstrument(),
        price,
        2.5,        // margin= EUR/USD: 2.5 let's say
        0.08,        // pipCost,
        1 / 0.0001);    // rate2pip

    result = fx::Position(
        stl::from_value(orderID++),
        stl::from_value(tradeID++),
        currency,
        buy,
        lots,    // K lots
        0,        // commission
        0,        // interest
        offer.GetTime().totime_t());

    FILE *pf = fopen("TradeResult.txt", "a+");
    if (pf == NULL)
        return;

    stl::string slog;
    slog += offer.GetTime().tostring();
    slog += (buy == true ? ", B:" : ", S:");
    slog += (buy == true ? stl::from_value(offer.GetAsk(), 5) :
        stl::from_value(offer.GetBid(), 5));
    slog += ", L(k)=";
    slog += stl::from_value(lots);
    slog += "\n";

    fwrite(slog.c_str(), sizeof(char), slog.size(), pf);
    fclose(pf);
}

void ClosePosition(const fx::Offer& offer, fx::Position& curpos)
{
    fx::Price price(offer.GetAsk(), offer.GetBid()); //buy@ask, sell@bid
    curpos.Close(price, offer.GetTime().totime_t());

    FILE *pf = fopen("TradeResult.txt", "a+");
    if (pf == NULL)
        return;


    bool buy = curpos.IsBuy();

    stl::string slog;
    slog += offer.GetTime().tostring();
    slog += (buy == true ? ", S:" : ", B:");
    slog += (buy == true ? stl::from_value(offer.GetBid(), 5) :
        stl::from_value(offer.GetAsk(), 5));
    slog += ", L(k)=";
    slog += stl::from_value(curpos.GetAmount(), 0);

    slog += ", PL(1k)=";
    slog += stl::from_value(curpos.GetPL(), 2);
    slog += ", GPL=";
    slog += stl::from_value(curpos.GetGPL(), 0);
    slog += "\n";

    fwrite(slog.c_str(), sizeof(char), slog.size(), pf);
    fclose(pf);
}
